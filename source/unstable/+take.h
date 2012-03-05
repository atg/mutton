#import "+type.h"
#include "+support.h"

/// ___
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
    // TODO: Add tests to me!
}

#include "+unsupport.h"
