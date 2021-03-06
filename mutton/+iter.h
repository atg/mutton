#import "+object.h"
#import "+type.h"

#import <Foundation/Foundation.h>
#include "+support.h"

/// Returns true if all 
// (in iter)
static BOOL all(Iter it, Predicate p) {
    if (!it)
      return NO;
    
    for (id x in it) {
      if (!p(x))
        return NO;
    }
    
    return YES;
}

/// Returns true if the predicate validates to any of the elements, false otherwise.
// (in iter)
static BOOL any(Iter it, Predicate p) {
    if (!it)
      return NO;
    
    for (id x in it) {
      if (p(x))
        return YES;
    }
    
    return NO;
}

/// Keep only the elements of a list for with the predicate is true.
// (in iter)
static NSArray* filter(Iter it, Predicate p) {
    if (!it)
        return nil;
    yield_start;
    for (id x in it) {
        if (p(x))
            yield(x);
    }
    yield_stop;
}

/// Glue together an array of arrays (or iterable of iterables) to make one big array.
// (in iter)
static NSArray* concat(Iter it) {
    if (!it)
        return nil;
    
    yield_start;
    for (Iter j in it) {
        if ([j isKindOfClass:[NSArray class]]) {
            yield_from((NSArray*)j);
        }
        else {
            for (id x in j) {
                yield(x);
            }
        }
    }
    yield_stop;
}

/// map(xs, f) is the list obtained by applying f to each element of xs
// (in iter)
static NSArray* map(Iter it, Mapping f) {
    if (!it)
        return nil;
    yield_start;
    for (id x in it) {
        id y = f(x);
        if (y)
            yield(y);
    } 
    yield_stop;
}

/// Tells if the array contains the object.
// (in iter)
static BOOL contains(Iter it, id x) {
  return any(it, ^ BOOL (id y) { return [y isEqual:x]; });
}

/// Find the number of objects in an array or iterable.
// (in iter)
static long count(Iter it) {
    if (responds(it, @selector(count)))
        return [(NSArray*)it count];

    long i = 0;
    for (id x in it) {
        i++;
    }
    return i;
}

/// Removes the given number of objects from the front of the list.
// (in iter)
static NSArray* drop(Iter it, long n) {
    if (n < 0)
        [NSException raise:NSInvalidArgumentException format:@"drop(%@, %ld) called with negative N", it, n];
    if (!it)
        return nil;
    
    yield_start;
    
    long i = 0;
    for (id x in it) {
        if (i >= n)
            yield(x);
        else
            i++;
    }

    yield_stop;
}

/// Removes falsy values from the array.
// (in iter)
// (after filter)
static NSArray* compact(Iter it) {
    return filter(it, ^ BOOL (id x) { return truthy(x); });
}

/// Find the first object of the iterable, or nil if it's empty.
// (in iter)
static id first(Iter it) {
    for (id obj in it) {
        return obj;
    }
    return nil;
}

/// Recursively flattens a tree of iterables into a single array.
// (in iter)
static NSArray* flatten(Iter it) {
    if (!it)
        return nil;
    
    yield_start;
    
    __block void(^_flatten)(id) = ^void(id y){
        if (!y)
            return;
        for (id x in y) {
            if ([x respondsToSelector:@selector(countByEnumeratingWithState:objects:count:)])
                _flatten(x);
            else
                yield(x);
        }
    };
    
    _flatten(it);
    
    yield_stop;
}

/// Groups similar objects using supplied predicate.
// (in iter)
static NSArray* groupBy(Iter it, BinaryPredicate eq) {
  if (!it)
    return nil;

  yield_start;

  for (id x in it) {

    if (eq(x, [[mutton_yield_v_ lastObject] lastObject]))
    {
      [[mutton_yield_v_ lastObject] addObject:x];
    } else {
      yield([NSMutableArray arrayWithObject:x]);
    }

  }

  yield_stop;
}

/// Return all the elements of a list except the last one.
// (in iter)
static id initial(Iter it) {
    if (!it)
        return nil;

    // TODO: Add a specialization for NSArray using subarrayWithRange:

    // We don't know when the iterable ends, so we just have to add everything to an array, then remove the last object
    yield_start;
    for (id x in it) {
        yield(x);
    }

    if ([mutton_yield_v_ count])
        [mutton_yield_v_ removeLastObject];
    yield_stop;
}

/// A bit like componentsJoinedByString: but with general purpose iterables instead of strings.
// (in iter)
static NSArray* intersperse(Iter it, id glue) {
    if (!it)
        return nil;
    
    yield_start;
    
    for (id x in it) {
        yield(x);
        yield(glue);
    }
    
    if ([mutton_yield_v_ count])
        [mutton_yield_v_ removeLastObject];

    yield_stop;
}

/// intercalate a b ==> concat $ intersperse a b
// (in iter)
// (after intersperse)
// (after concat)
static NSArray* intercalate(Iter a, Iter b) {
    return concat(intersperse(a, b));
}

/// Convert a general purpose iterable to an NSArray*
// (in iter)
static NSArray* iter(Iter it) {
    if (!it)
        return nil;

    if (isKind(it, [NSMutableArray class]))
        return [(NSMutableArray*)it copy];

    // If it's a non-mutable array, we're probably OK to not copy it
    if (isKind(it, [NSArray class]))
        return (NSArray*)it;

    yield_start;
    for (id x in it) {
        yield(x);
    }
    yield_stop;
}
/// Find the last object of the iterable, or nil if it's empty.
// (in iter)
static id last(Iter it) {
    if (responds(it, @selector(lastObject)))
        return [(NSArray*)it lastObject];

    id v = nil;
    for (id x in it) {
        v = x;
    }
    return v;
}

/// Map each element to a list of new elements (which may be empty), then glue the lists together. It's map, filter and a bit more on top.
// (in iter)
// (after concat)
// (after map)
static NSArray* concatMap(Iter it, Iter(^f)(id)) {
    if (!it)
        return nil;
    return concat(map(it, f)); // Ahhhh the joys of functional programming at last
}

/// Nests function calls such that nest(x, 3, f) ==> f(f(f(x)))
// (in iter)
static id nest(id x, long loops, Mapping f) {
    if (!f)
      return nil;
    
    if (loops < 0)
      [NSException raise:@"Negative nesting index" format:@"foo of %d is invalid", loops];
    
    if (loops == 0)
      return x;

    return f( nest(x, loops-1, f) );
}

/// Like objectAtIndex: but works on general iterables, and returns nil if the index is out of bounds (instead of an exception).
// (in iter)
static id objectAt(Iter it, long n) {

    if (!it)
        return nil;
    if (n < 0)
        return nil;
    
    if (responds(it, @selector(count))) {
        if (n >= [(NSArray*)it count])
            return nil;
        if (responds(it, @selector(objectAtIndex:))) {
            return [(NSArray*)it objectAtIndex:n];
        }
    }

    NSInteger i = 0;
    for (id x in it) {
        if (i == n)
            return x;
        i++;
    }

    return nil;
}

/// Allows you to "sow" values, and "reap" them at the end. Pass a block to reap that takes a single Mapping argument (conventionally named "sow"). Do some work in this block, then call sow each time you want to save a value. Reap will run your block and return the values that you sowed.
// (in iter)
static NSArray* reap(void(^body)(Mapping sow)) {
    yield_start;
    Mapping sow = ^(id x){
        if (x)
            yield(x);
        return x;
    };

    body(sow);
    yield_stop;
}

/// Build a list by repeating an element a given (non-negative) number of times.
// (in iter)
static NSArray* replicate(id v, long n) {
    if (n < 0)
        [NSException raise:NSInvalidArgumentException format:@"replicate(%@, %ld) called with negative N", v, n];
    if (!v)
        return nil;
    
    yield_start;
    for (long i = 0; i < n; i++) {
        yield(v);
    }
    yield_stop;
}

/// Reverse an iterable.
// (in iter)
// (after iter)
static id reverse(Iter it) {
    if (!it)
        return nil;

    if (responds(it, @selector(reverseObjectEnumerator)))
        return iter([(NSArray*)it reverseObjectEnumerator]);
    else
        return reverse(iter(it));
}

/// A bit like componentsSeparatedByString: but with general purpose iterables instead of of strings
// (in iter)
static NSArray* split(Iter it, id token) {
    if (!it)
        return nil;
    
    BOOL isEmpty = YES;
    
    yield_start;
    
    NSMutableArray* temp = [[NSMutableArray alloc] init];
    for (id x in it) {
        isEmpty = NO;
        if (x == token) {
            yield(temp);
            temp = [[NSMutableArray alloc] init];
        } else {
            [temp addObject:x];
        }
    }
    
    if (isEmpty)
        return emptylist();
    
    yield(temp);
    yield_stop;
}

/// Extract the elements after the head of a list.
// (in iter)
static id tail(Iter it) {
    if (!it)
        return nil;

    // TODO: Add a specialization for NSArray using subarrayWithRange:

    yield_start;
    BOOL isFirst = YES;
    for (id x in it) {
        if (isFirst)
            isFirst = NO;
        else
            yield(x);
    } 
    yield_stop;
}

/// Returns the given number of objects from the front of the list.
// (in iter)
static NSArray* take(Iter it, long n) {
    if (!it)
        return nil;

    yield_start;

    long i = 0;
    for (id x in it) {
        if (i >= n)
            break;
        
        yield(x);
        i++;
    }

    yield_stop;
}

/// Transposes the rows and columns of the matrix
// (in iter)
static NSArray* transpose(Iter it) {
  if (!it)
    return nil;
  
  NSMutableArray* normal = [[NSMutableArray alloc] init];
  for (id x in it)
    [normal addObject:[NSMutableArray arrayWithArray:x]];
  
  yield_start;
  
  for (long i = 0; i <= [normal count]; i++)
  {
    yield([NSMutableArray array]);
    BOOL isEmpty = YES;

    for (id x in normal)
    {
      if ([x count] == 0)
        continue;
      
      isEmpty = NO;
      
      [[mutton_yield_v_ lastObject] addObject:[x objectAtIndex:0]];
      [x removeObjectAtIndex:0];
    }
    
    if (isEmpty)
      [mutton_yield_v_ removeLastObject];
  }
  
  yield_stop;
}

/// Remove duplicate objects, as determined by their -hash and isEqual: (i.e., the objects are inserted into an NSSet to determine equality). O(n).
// (in iter)
static NSArray* uniqued(Iter it) {
    if (!it)
        return nil;
    
    NSMutableSet* s = [NSMutableSet set];
    yield_start;
    for (id x in it) {
        if (![s containsObject:x]) {
            [s addObject:x];
            yield(x);
        }
    }
    yield_stop;
}

/// Applies a function over and over again to x until p(x) evaluates to true.
// (in iter)
static id until(Predicate p, Mapping f, id x) {
    while (!p(x))
        x = f(x);
    return x;
}

/// Zips both arrays using the BinaryMapping. That's what.
// (in iter)
// (after count)
// (after objectAt)
static NSArray* zipWith(Iter a, Iter b, BinaryMapping f) {
    if (!a || !b)
      return nil;

    long tempa = count(a);
    long tempb = count(b);
    
    long count = (tempa > tempb) ? tempb : tempa;
    
    yield_start;
    
    for (long i=0; i < count; ++i)
    {
      yield( f(objectAt(a, i), objectAt(b, i)) );
    }
    
    yield_stop;
}

#include "+unsupport.h"
