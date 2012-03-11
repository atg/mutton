#import "+type.h"
#include "+support.h"

/// Combine a list of values into a single value. Returns nil if the list is empty. Socialist version.
// (in fold)
// (after foldl)
static id foldl1(Iter it, BinaryMapping f) {
    return foldl(it, nil, f);
}


test {
    // No tests necessary
}

#include "+unsupport.h"
