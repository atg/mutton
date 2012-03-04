#import "+type.h"

#include "+support.h"

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


test {
    ass  ( !tail(nil) );
    asseq(emptylist(), tail(emptylist()) );
    asseq(emptylist(), tail(list(foo)) );
    asseq(list(bar), tail(list(foo, bar)) );
    asseq(list(bar, baz), tail(list(foo, bar, baz)) );
}

#include "+unsupport.h"
