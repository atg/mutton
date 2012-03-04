#import "+type.h"
#import "+object.h"

#pragma mark (Private array-building macros)
#define yield_start NSMutableArray* mutton_yield_v_ = [NSMutableArray array]
#define yield_stop return mutton_yield_v_
#define yield_from(v_) [mutton_yield_v_ addObjectsFromArray(v_)]
#define yield(v_) [mutton_yield_v_ addObject:(v_)]






#pragma mark count: find the number of objects in an array or iterable
static long count(Iter it) {
    if (responds(it, @selector(count)))
        return [(NSArray*)it count];
    
    long i = 0;
    for (id x in it) {
        i++;
    }
    return i;
}

#pragma mark first: find the first object of the iterable, or nil if it's empty
static id first(Iter it) {
    for (id obj in it) {
        return obj;
    }
    return nil;
}

#pragma mark: last: find the last object of the iterable, or nil if it's empty
static id last(Iter it) {
    if (responds(it, @selector(lastObject)))
        return [(NSArray*)it lastObject];
    
    id v = nil;
    for (id x in it) {
        v = x;
    }
    return v;
}

#pragma mark objectAt: provides "soft" objectAtIndex: functionality
// Indexes which are out of bounds will return `nil` instead of an exception
static id objectAt(Iter it, long n) {
    
    if (!it)
        return nil;
    if (n < 0)
        return nil;
    
    BOOL hasObjectAtIndex = responds(it, @selector(objectAtIndex:));
    BOOL hasCount = responds(it, @selector(count));

    if (hasCount) {
        if (n >= [it count])
            return nil;
        if (hasObjectAtIndex) {
            return [it objectAtIndex:n];
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


#pragma mark tail: Extract the elements after the head of a list.
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


#pragma mark initial: Return all the elements of a list except the last one.
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


#pragma mark reverse: Reverse an iterable
static id reverse(Iter it) {
    if (!it)
        return nil;
    
    if (responds(it, @selector(reverseObjectEnumerator)))
        return iter([(NSArray*)it reverseObjectEnumerator]);
    else
        return reverse(iter(it));
}




#undef yield_start
#undef yield_stop
#undef yield_from
#undef yield
