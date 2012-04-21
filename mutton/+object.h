#import "+type.h"

#import <Foundation/Foundation.h>
#include "+support.h"

/// Determines if two (possibly nil) objects are equal. This differs from -isEqual: because it considers the case where both objects are nil
// (in object)
static BOOL equals(id a, id b) {
    return a == b || [a isEqual:b];
}

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

/// Same as performSelector:withObject:, but inhibits a warning under ARC (so make sure that the method returns an autoreleased value).
// (in object)
static id performSel(id obj, SEL sel, id arg) {
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Warc-performSelector-leaks"
    return [obj performSelector:sel withObject:arg];
    #pragma clang diagnostic pop
}

/// Wraps -respondsToSelector
// (in object)
static BOOL responds(id obj, SEL sel) {
    return [obj respondsToSelector:sel];
}

#include "+unsupport.h"
