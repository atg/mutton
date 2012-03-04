#include "+support.h"

/// Wraps isKindOfClass. Accepts a string as the class argument.
// (in object)
static BOOL isKind(id obj, id class_or_classname) {

    Class c = Nil;
    if ([class_or_classname class] == class_or_classname)
        c = class_or_classname;
    else
        c = NSClassFromString(class_or_classname);

    if (!c)
        return NO;
    return [obj isKindOfClass:c];
}


test {
    ass( isKind(foo, @"NSString") );
    ass( isKind(foo, [NSString class]) );
    ass( isKind(bar, @"NSNumber") );
    ass( isKind(bar, [NSNumber class]) );
    ass( isKind(baz, @"NSArray") );
    ass( isKind(baz, [NSArray class]) );
    ass( isKind([NSDate date], @"NSDate") );
    ass( isKind([NSDate date], [NSDate class]) );
}

#include "+unsupport.h"
