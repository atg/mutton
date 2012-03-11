#import "+type.h"
#include "+support.h"

/// ___
// (in iter)
static NSArray* chunk(Iter it, long n) {
    if (!it)
        return nil;
    if (n < 1)
        return nil;
    
    NSArray* v = iter(it);
    if ([v count] == 0)
        return emptylist();
    
    if ([v count] >= n)
        return map(v, lambda(x, list(x)));
    
    long smallsize = floor(((double)[v count]) / ((double)n));
    long lastsize = [v count] % smallsize;
    
    yield_start;
    
    NSMutableArray* v = [NSMutableArray array];
    for (id x in it) {
        [v addObject:x];
        if ([v count] == smallsize)
    }
    
    yield_stop;
}


test {
    // ass  ( !chunk() );
    ass  ( !chunk(list(foo), 0) );
    asseq( emptylist(), chunk(emptylist(), 10) );
    asseq( list(list(foo)), chunk(list(foo), 1) );
    // TODO: Add more tests to me!
}

#include "+unsupport.h"
