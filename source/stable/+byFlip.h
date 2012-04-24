#import "+type.h"
#include "+support.h"

/// A function g such that <code>g(x, y) == f(y, x) forall x, y</code>.
// (in func)
static BinaryMapping byFlip(BinaryMapping f) {
    f = [f copy];

    return [^id(id x, id y) {
        return f(y, x);
    } copy];
}


test {
    BinaryMapping joinstr = ^id(id x, id y) { return [x stringByAppendingString:y]; };

    asseq(@"barfoo", byFlip(joinstr)(@"foo", @"bar"));
}

#include "+unsupport.h"
