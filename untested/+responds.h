#import "+support.h"


/// Wraps -respondsToSelector
// (in object)
static BOOL responds(id obj, SEL sel) {
    return [obj respondsToSelector:sel];
}


test {
    ass( responds(foo, @selector(characterAtIndex:)) );
    ass( responds(bar, @selector(isEqualToNumber:)) );
    ass( responds(baz, @selector(objectAtIndex:)) );
}

#import "-support.h"
