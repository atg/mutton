#import "+type.h"
#include "+support.h"

/// Returns a comparator that calls compare: on the objects given to it.
// (in sorting)
static NSComparator compareDefault() {
    return [^ NSComparisonResult (id a, id b) {
        return [a compare:b];
    } copy];
}


test {
    // TODO: Add tests to me!
}

#include "+unsupport.h"
