#import "+type.h"
#include "+support.h"

/// Converts a curried function (why on earth you would have such a thing is beyond me) into a normal-person function.
// (in func)
static BinaryMapping uncurry (Mapping(^f)(id)) {
    f = [f copy];
    return [^ id (id x, id y) {
        return f(x)(y);
    } copy];
}


test {
    // TODO: Add tests to me!
}

#include "+unsupport.h"
