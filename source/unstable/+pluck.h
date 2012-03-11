#import "+type.h"
#include "+support.h"

/// Maps an array of objects by a given key.
// (in iter)
static NSArray* pluck(Iter it, NSString* key) {
    return map(it, byKey(key));
}


test {
    // TODO: Add tests to me!
}

#include "+unsupport.h"
