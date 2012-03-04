#import "+type.h"

#include "+support.h"

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


test {
    ass  ( !initial(nil) );
    asseq(list(), initial(list()) );
    asseq(list(), initial(list(foo)) );
    asseq(list(foo), initial(list(foo, bar)) );
    asseq(list(foo, bar), initial(list(foo, bar, baz)) );
}

#include "+unsupport.h"
