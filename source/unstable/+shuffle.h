#import "+type.h"
#include "+support.h"

/// Randomly shuffle an iterable.
// (in random)
static NSArray* shuffle(Iter it) {
    if (!it)
        return nil;
    NSMutableArray* population = [iter(it) mutableCopy];
    long n = [population count];
    if (!n)
        return population;
    
    for (long i = 0; i < n; i++) {
        long j = randint(0, ); // TODO: is this right?
        if (i != j)
            [population exchangeObjectAtIndex:i withObjectAtIndex:j];
    }
    return population;
}


test {
    // TODO: Add tests to me!
}

#include "+unsupport.h"
