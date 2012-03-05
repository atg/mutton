#import "+type.h"
#include "+support.h"

/// ___
// (in iter)
static NSArray* chunk(Iter it, long n) {
    if (!it)
        return nil;
    
    NSArray* v = iter(it);
    if ([v count] == 0)
        return emptylist();
    
    if ([v count] >= n)
        return map(v, lambda(x, list(x)));
    
    long bigsize = ceil(((double)[v count]) / ((double)n));
    long smallsize = floor(((double)[v count]) / ((double)n));
    
    // First chunk is bigsize, next chunks are smallsize
    
}


test {
    // TODO: Add tests to me!
}

#include "+unsupport.h"
