#import "+type.h"
#include "+support.h"

/// Enumerate an iterable, where each element is given with its index.
// (in iter)
static void enumerate(Iter it, void(^f)(long i, id x)) {
    long i = 0;
    for (id x in it) {
        f(i, x);
        i++;
    }
}


test {
    // TODO: Add tests to me!
}

#include "+unsupport.h"
