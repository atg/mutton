#import "+type.h"
#include "+support.h"

/// Same as performSelector:withObject:, but inhibits a warning under ARC (so make sure that the method returns an autoreleased value).
// (in object)
static id performSel(id obj, SEL sel, id arg) {
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Warc-performSelector-leaks"
    return [obj performSelector:sel withObject:arg];
    #pragma clang diagnostic pop
}


test {
    ass  ( !performSel(nil, @selector(doesntExist), nil) );
    asseq( performSel(@"abc", @selector(stringByAppendingString:), @"def"), @"abcdef" );
}

#include "+unsupport.h"
