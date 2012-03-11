#import "+type.h"
#include "+support.h"

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


test {
    ass  ( !take(nil, 0) );
    ass  ( !take(nil, 1) );
    ass  ( !take(nil, 10) );
    
    asseq( emptylist(), take(emptylist(),           0) );
    asseq( emptylist(), take(list(foo),             0) );
    asseq( emptylist(), take(list(foo, bar),        0) );
    asseq( emptylist(), take(list(foo, bar, baz),   0) );

    asseq( emptylist(), take(emptylist(),  2) );
    asseq( emptylist(), take(emptylist(),  3) );
    asseq( emptylist(), take(emptylist(), 10) );
    
    asseq( list(foo),           take(list(foo),           1) );
    asseq( list(foo, bar),      take(list(foo, bar),      2) );
    asseq( list(foo, bar, baz), take(list(foo, bar, baz), 3) );
    
    asseq( list(foo),           take(list(foo, bar, baz), 1) );
    asseq( list(foo, bar),      take(list(foo, bar, baz), 2) );
    asseq( list(foo, bar, baz), take(list(foo, bar, baz), 3) );
    asseq( list(foo, bar, baz), take(list(foo, bar, baz), 4) );
}

#include "+unsupport.h"
