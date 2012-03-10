#import "+type.h"
#include "+support.h"

/// Returns a comparator that applies a mapping on each object before comparing them.
// (in sorting)
static NSComparator compareThrough(Mapping f, NSComparator cmp) {
    f = [f copy];
    cmp = [cmp copy] ?: compareDefault();
    
    return [^ NSComparisonResult (id a, id b) {
        return cmp(f(a), f(b));
    } copy];
}


test {
    // TODO: Add tests to me!
}

#include "+unsupport.h"
