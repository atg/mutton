#import "+type.h"
#import "+object.h"
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


test {
    ass  ( falsy(nil) );
    ass  ( falsy(emptylist()) );
    ass  ( falsy([NSSet set]) );
    ass  ( falsy([NSDictionary dictionary]) );
    ass  ( falsy(@"") );
    
    ass  ( !falsy([NSDate date]) );
    ass  ( !falsy(list(foo)) );
    ass  ( !falsy([NSSet setWithObject:foo]) );
    ass  ( !falsy(foo) );
}

#include "+unsupport.h"
