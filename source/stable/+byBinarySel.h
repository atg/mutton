#import "+type.h"
#import "+object.h"
#include "+support.h"

/// ___
// (in func)
static BinaryMapping byBinarySel(SEL sel) {
    return [^ id (id x, id y) {
        return performSel(x, sel, y);
    } copy];
}


test {
    // TODO: Add tests to me!
}

#include "+unsupport.h"
