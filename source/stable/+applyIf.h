#import "+type.h"
#include "+support.h"

/// If x is not null, gives f(x). Otherwise, gives nil without applying f. This is useful is f is not safe with a nil value.
// (in func)
static id applyIf(id x, Mapping f) {
    if (!x)
        return nil;
    return f(x);
}


test {
    ass  (!applyIf(nil, nil));
    ass  (!applyIf(nil, byIdentity()));
    asseq(foo, applyIf(foo, byIdentity()));
}

#include "+unsupport.h"
