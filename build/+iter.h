#import "+object.h"
#import "+type.h"

#import <Foundation/Foundation.h>
#include "+support.h"

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

/// Find the first object of the iterable, or nil if it's empty.
// (in iter)
static id first(Iter it) {
    for (id obj in it) {
        return obj;
    }
    return nil;
}

/// Return all the elements of a list except the last one.
// (in iter)
static id initial(Iter it) {
    if (!it)
        return nil;

    // TODO: Add a specialization for NSArray using subarrayWithRange:

    // We don't know when the iterable ends, so we just have to add everything to an array, then remove the last object
    yield_start;
    BOOL isFirst = YES;
    for (id x in it) {
        yield(x);
    }

    if ([mutton_yield_v_ count])
        [mutton_yield_v_ removeLastObject];
    yield_stop;
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

/// map(xs, f) is the list obtained by applying f to each element of xs
// (in iter)
static NSArray* map(Iter it, Mapping f) {
    yield_start;
    for (id x in it) {
        id y = f(x);
        if (y)
            yield(y);
    } 
    yield_stop;
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

#include "+unsupport.h"
