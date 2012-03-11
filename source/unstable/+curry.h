#import "+type.h"
#include "+support.h"

/// You'd have to have a serious neckbeard in order to want to use this.
// (in func)
static Mapping(^curry)(id) (BinaryMapping f) {
    f = [f copy];
    return [^ Mapping (id x) {
        return [^ id (id y){
            f(x, y);
        } copy];
    } copy];
}


test {
    // TODO: Add tests to me!
    // Oh god, do I have to...?
}

#include "+unsupport.h"
