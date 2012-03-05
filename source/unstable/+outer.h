#import "+type.h"
#include "+support.h"

/// ___
// (in zipping)
static NSArray* outer(BinaryMapping f, Iter i, Iter j) {
    return map(i, lambda(x, map(j, lambda(y, f(x, y)))));
}

test {
    // TODO: Add tests to me!
}

#include "+unsupport.h"
