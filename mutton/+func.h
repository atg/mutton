#import "+object.h"
#import "+type.h"

#import <Foundation/Foundation.h>
#include "+support.h"

/// If x is not null, gives f(x). Otherwise, gives nil without applying f. This is useful is f is not safe with a nil value.
// (in func)
static id applyIf(id x, Mapping f) {
    if (!x)
        return nil;
    return f(x);
}

/// ___
// (in func)
static BinaryMapping byBinarySel(SEL sel) {
    return [^ id (id x, id y) {
        return performSel(x, sel, y);
    } copy];
}

/// A function h such that h(x) == f(g(x)) forall x
// (in func)
static Mapping byCompose(Mapping f, Mapping g) {
    f = [f copy];
    g = [g copy];
    
    return [^id(id x) {
        return f(g(x));
    } copy];
}

/// The constant function f for a value y such that f(x) == y forall x
// (in func)
static Mapping byConst(id y) {
    return [^ id (id x) {
        return y;
    } copy];
}

/// A function g such that g(x, y) == f(y, x) forall x, y
// (in func)
static BinaryMapping byFlip(BinaryMapping f) {
    f = [f copy];

    return [^id(id x, id y) {
        return f(y, x);
    } copy];
}

/// Turn a function into a block
// (in func)
static Mapping byFunction(id (*f)(id)) {
    if (f == NULL)
        return nil;
    return [^id(id x) {
        return f(x);
    } copy];
}

/// The identity function f such that f(x) == x
// (in func)
static Mapping byIdentity() {
    return [^ id (id x) {
        return x;
    } copy];
}

#include "+unsupport.h"
