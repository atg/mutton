static id filter(Iter it, Predicate pred) {
    yield_start
    for (id x in it) {
        if (pred(it, x))
            yield(x);
    } 
    yield_stop
}

static id exclude(Iter it, Predicate pred) {
    yield_start
    for (id x in it) {
        if (!pred(it, x))
            yield(x);
    } 
    yield_stop
}

/// iter: coerce into an NSArray
static id iter(Iter it) {
    if (!it)
        return nil;

    if (isKind(it, [NSMutableArray class]))
        return [it copy];

    // If it's a non-mutable array, we're probably OK to not copy it
    if (isKind(it, [NSArray class]))
        return it;

    yield_start;
    for (id x in it) {
        yield(x);
    }
    yield_stop;
}

#pragma mark foldl: Bog standard left-handed fold/reduce function
#pragma mark foldl0: Like foldl, but take an argument for if the Iter is empty
static id foldl0(Iter it, id ifempty, BinaryMapping f) {
    id result = nil;
    BOOL isFirst = YES;
    for (id x in it) {
        if (result == nil) {
            result = x;
            isFirst = YES;
        }
        else {
            id y = f(result, x);
            if (!y)
                continue;
            result = y;
            isFirst = NO;
        }
    }
    
    if (isFirst)
        return ifempty;
    return result;
}
static id foldl(Iter it, BinaryMapping f) {
    return foldl(it, nil, f);
}
