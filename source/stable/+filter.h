#import "+type.h"
#include "+support.h"

/// ___
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


test {
    BOOL (^p)(id) = ^BOOL(NSString* s) {
        return [s intValue] % 3 == 1;
    };
    ass  ( !filter(nil, p) );
    asseq( emptylist(), filter(emptylist(), p) );
    asseq( emptylist(), filter(list(@"2"), p) );
    asseq( list(@"7"), filter(list(@"7"), p) );
    asseq( list(@"1", @"4", @"7"), filter(list(@"1", @"2", @"3", @"4", @"5", @"6", @"7"), p) );
}

#include "+unsupport.h"
