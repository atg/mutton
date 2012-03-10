#import "+type.h"
#include "+support.h"

/// Returns a comparator that compares by two comparators in turn
// (in sorting)
static NSComparator compareBoth(NSComparator cmp1, NSComparator cmp2) {
    cmp1 = [cmp1 copy] ?: compareDefault();
    cmp2 = [cmp2 copy] ?: compareDefault();
    
    return [^ NSComparisonResult (id a, id b) {
        return cmp1(a, b) ?: cmp2(a, b);
    } copy];
}


test {
    // TODO: Add tests to me!
}

#include "+unsupport.h"
