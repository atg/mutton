#import "+type.h"
#include "+support.h"

/// A function h such that h(x) == f(g(x)) forall x
// (in func)
static Mapping byCompose(Mapping f, Mapping g) {
    f = [f copy];
    g = [g copy];
    
    return [^id(id x) {
        return f(g(x));
    } copy];
}


test {
    Mapping allocate = ^id(id x) { return [x alloc]; };
    Mapping initialize = ^id(id x) { return [x init]; };
    Mapping allocinit = byCompose(initialize, allocate);
    
    asseq(@"", allocinit([NSString class]));
}

#include "+unsupport.h"
