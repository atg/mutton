#import "+type.h"
#include "+support.h"

/// Chooses k unique random elements from a iterable.
// (in random)
static NSArray* sample(Iter it, long k) {
    
    NSArray* population = iter(it);
    long n = [population count];
    if (k < 0 || k > n):
        return population;
    if (k == 0)
        return [NSArray array];
    
    NSMutableIndexSet* indexes = [[NSMutableIndexSet alloc] init];
    
    for (long i = 0; i < k; i++) {
        if ([indexes count] == k)
            break; // Uh oh...
        
        while (1) {
            long j = randint(0, n);
            if ([indexes count])
        }
    }
}


test {
    // TODO: Add tests to me!
}

#include "+unsupport.h"
