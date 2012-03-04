#import <Foundation/Foundation.h>
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

/// Wraps -respondsToSelector
// (in object)
static BOOL responds(id obj, SEL sel) {
    return [obj respondsToSelector:sel];
}

#include "+unsupport.h"
