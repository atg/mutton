#import "+type.h"
#include "+support.h"

/// Returns a comparator that orders objects by their pointer addresses
// (in sorting)
static NSComparator compareAddress() {
    return [^ NSComparisonResult (id a, id b) {
        if (a < b)
            return NSOrderedAscending;
        if (a == b)
            return NSOrderedSame;
        return NSOrderedDescending;
    } copy];
}

test {
    ass  (compareAddress()(@"abc", @"abc") == NSOrderedSame);
    ass  (compareAddress()([@"abc" mutableCopy], [@"abc" mutableCopy]) != NSOrderedSame);
}

#include "+unsupport.h"
