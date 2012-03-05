#import "+object.h"
#import "+type.h"

#import <Foundation/Foundation.h>
#include "+support.h"

/// Determine if an object is empty or nil.
// (in bool)
static BOOL falsy(id x) {
    if (!x)
        return YES;
    if (responds(x, @selector(count)))
        return [(NSArray*)x count] == 0;
    if (responds(x, @selector(length)))
        return [(NSString*)x length] == 0;
    return NO;
}

/// Determine if an object is not empty or nil
// (in bool)
// (after falsy)
static BOOL truthy(id x) {
    return !falsy(x);
}

#include "+unsupport.h"
