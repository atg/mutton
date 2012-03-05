#import "+type.h"
#include "+support.h"

/// Remove duplicate objects, as determined by a binary predicate. O(n^2).
// (in iter)
static NSArray* uniquedBy(Iter it, BinaryPredicate p) {
    NSMutableArray* result = [NSMutableArray array];
    
    
    
    for (id x in it) {
        BOOL isDupe = NO;
        for (id y in result) {
            if (p(x, y)) {
                isDupe = YES;
                break;
            }
        }
        
        if (!isDupe)
            [result addObject:x];
    }
    
    return result;
}


test {
    // TODO: Add tests to me!
}

#include "+unsupport.h"
