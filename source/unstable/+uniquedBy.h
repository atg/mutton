#import "+type.h"
#include "+support.h"

/// Remove duplicate objects, as determined by a binary predicate. O(n^2).
// (in iter)
static NSArray* uniquedBy(Iter it, BinaryPredicate p) {
    yield_start;
    
    for (id x in it) {
        BOOL isDupe = NO;
        for (id y in mutton_yield_v) {
            if (p(x, y)) {
                isDupe = YES;
                break;
            }
        }
        
        if (!isDupe)
            yield(x);
    }
    
    yield_stop;
}


test {
    // TODO: Add tests to me!
}

#include "+unsupport.h"
