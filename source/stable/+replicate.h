#import "+type.h"
#include "+support.h"

/// Build a list by repeating an element a given (non-negative) number of times.
// (in iter)
static NSArray* replicate(id v, long n) {
    if (n < 0)
        [NSException raise:NSInvalidArgumentException format:@"replicate(%@, %ld) called with negative N", v, n];
    if (!v)
        return nil;
    
    yield_start;
    for (long i = 0; i < n; i++) {
        yield(v);
    }
    yield_stop;
}


test {
    ass  ( !replicate(nil, 0) );
    ass  ( !replicate(nil, 10) );
    asseq( emptylist(), replicate(foo, 0) );
    asseq( list(foo), replicate(foo, 1) );
    asseq( list(foo, foo), replicate(foo, 2) );
    asseq( list(foo, foo, foo), replicate(foo, 3) );
}

#include "+unsupport.h"
