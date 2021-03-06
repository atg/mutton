#import "+type.h"
#include "+support.h"

/// Returns a comparator that compares using a selector, such as compare:, caseInsensitiveCompare:, localizedStandardCompare:, etc.
// (in sorting)
static NSComparator compareSelector(SEL sel) {
    sel = sel ?: @selector(compare:);
    
    return [^ NSComparisonResult (id a, id b) {
        return (NSComparisonResult)objc_msgSend(a, sel, b);
    } copy];
}


test {
    // TODO: Add tests to me!
}

#include "+unsupport.h"
