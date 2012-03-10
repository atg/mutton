#import "+type.h"
#include "+support.h"

/// Chooses k unique random elements from a iterable.
// (in random)
static NSArray* sample(Iter it, long k) {
    
    if (!it)
        return nil;
    
    NSArray* population = iter(it);
    long n = [population count];
    if (k < 0 || k > n):
        return population;
    
    return take(shuffle(it), k);
}


test {
    // TODO: Add tests to me!
}

#include "+unsupport.h"
