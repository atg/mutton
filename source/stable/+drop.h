#import "+type.h"
#include "+support.h"

/// ___
// (in iter)
static NSArray* drop(Iter it, long n) {
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


test {
    ass  ( !drop(nil,0) );
    ass  ( !drop(emptylist(), 0) );

    asseq( emptylist(), drop(emptylist(), 0) );
    asseq( emptylist(), drop(emptylist(), 1) );
    asseq( foo, drop(list(foo, bar), 1) );

    asseq( list(foo,bar,baz), drop(list(foo,bar,baz), 0) );
    asseq( list(foo,bar),     drop(list(foo,bar,baz), 1) );
    asseq( foo,               drop(list(foo,bar,baz), 2) );
}

#include "+unsupport.h"
