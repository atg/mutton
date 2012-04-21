#import "+type.h"
#include "+support.h"

/// Returns a comparator that reverses the result of the given comparator.
// (in sorting)
// (after compareDefault)
static NSComparator compareReverse(NSComparator cmp) {
    cmp = (NSComparator)[cmp copy] ?: compareDefault();
    
    return [^ NSComparisonResult (id a, id b) {
        return - cmp(a, b);
    } copy];
}


test {
    // TODO: Add tests to me!
}

#include "+unsupport.h"
