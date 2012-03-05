#import "+type.h"
#include "+support.h"

/// The constant function f for a value y such that f(x) == y forall x
// (in func)
static Mapping byConst(id y) {
    return [^ id (id x) {
        return y;
    } copy];
}


test {
    ass  ( !byConst(nil)(nil) );
    ass  ( !byConst(nil)(foo) );
    asseq( foo, byConst(foo)(nil) );
    asseq( foo, byConst(foo)(foo) );
    asseq( foo, byConst(foo)(bar) );
}

#include "+unsupport.h"
