#import "+type.h"
#include "+support.h"

/// Determine if an object is not empty and not nil.
// (in bool)
// (after falsy)
static BOOL truthy(id x) {
    return !falsy(x);
}


test {
    // This hardly needs testing, does it?
}

#include "+unsupport.h"
