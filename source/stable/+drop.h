#import "+type.h"
#include "+support.h"

/// Removes the given number of objects from the array
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


test {
    ass  ( !drop(nil, 0) );
    ass  ( !drop(nil, 1) );
    ass  ( !drop(nil, 10) );
    
    asseq( emptylist(), drop(list(foo), 2) );
    asseq( emptylist(), drop(list(foo), 10) );
    
    asseq( emptylist(), drop(list(foo, baz), 2) );
    asseq( emptylist(), drop(list(foo, bar), 3) );
    asseq( emptylist(), drop(list(foo), 10) );
    
    asseq( list(foo), drop(list(foo), 0) );
    asseq( list(foo), drop(list(bar, foo), 1) );
    asseq( list(baz), drop(list(bar, foo, baz), 2) );
    
    asseq( list(foo), drop(list(foo), 0) );
    asseq( list(foo), drop(list(bar, foo), 1) );
    asseq( list(foo), drop(list(bar, baz, foo), 2) );

    asseq( list(baz, foo), drop(list(bar, baz, foo), 1) );
}

#include "+unsupport.h"
