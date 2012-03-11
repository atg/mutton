#import "+type.h"
#include "+support.h"

/// Turn a function into a block
// (in func)
static Mapping byFunction(id (*f)(id)) {
    if (f == NULL)
        return nil;
    return [^id(id x) {
        return f(x);
    } copy];
}


test {
    ass  (!byFunction(NULL));
    
    Mapping f = byFunction((id(*)(id))&byConst);
    Mapping g = f(foo);
    id h = g(bar);
    asseq(foo, h);
}

#include "+unsupport.h"
