#import "+type.h"
#include "+support.h"

/// The identity function f such that f(x) == x
// (in func)
static Mapping byIdentity() {
    return [^ id (id x) {
        return x;
    } copy];
}


test {
    ass  ( !byIdentity()(nil) );
    asseq( foo, byIdentity()(foo) );
}

#include "+unsupport.h"
