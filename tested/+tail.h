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
    asseq(@[], tail(@[]) );
    asseq(@[], tail(@[foo]) );
    asseq(@[bar], tail(@[foo, bar]) );
    asseq(@[bar, baz], tail(@[foo, bar, baz]) );
}

#include "+unsupport.h"
