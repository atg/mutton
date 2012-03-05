#import "+type.h"
#include "+support.h"

/// ___
// (in zipping)
static id inner(Mapping outside_f, Mapping inside_f, Iter i, Iter j) {
    return outside_f(map(zip(i, j), inside_f));
}


test {
    // TODO: Add tests to me!
}

#include "+unsupport.h"
