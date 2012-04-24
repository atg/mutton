#import "+type.h"
#import "+object.h"
#include "+support.h"

/// Returns a block that sends a "binary" message (i.e a message with one argument). For instance <code>byBinarySel(@selector(stringByAppendingString:))</code>.
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
