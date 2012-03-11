#import "+type.h"
#include "+support.h"

/// ___
// (in func)
static Mapping byKey(NSString* k) {
    return [^ id (id obj) {
        if (responds(obj, @selector(objectForKey:)))
            [obj objectForKey:k];
        else
            [obj valueForKey:k];
    } copy];
}


test {
    // TODO: Add tests to me!
}

#include "+unsupport.h"
