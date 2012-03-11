#import "+type.h"
#include "+support.h"

/// Combine a list of values into a single value. Takes an argument to use if the list is empty. Socialist version.
// (in fold)
static id foldl(Iter it, id ifempty, BinaryMapping f) {
    if (!it)
        return nil;
    
    id result = nil;
    BOOL isFirst = YES;
    for (id x in it) {
        if (result == nil) {
            result = x;
            isFirst = YES;
        }
        else {
            id y = f(result, x);
            if (!y)
                continue;
            result = y;
            isFirst = NO;
        }
    }

    if (isFirst)
        return ifempty;
    return result;
}


test {
    BinaryMapping cc = byBinarySel(@selector(stringByAppendingString:));
    
    ass  ( !foldl(nil, @"", cc));
    asseq( @"foobarbaz", foldl(list(@"foo", @"bar", @"baz"), @"", cc));
    asseq( @"HELLO", foldl(emptylist(), @"HELLO", cc));
    ass  ( !foldl(emptylist(), nil, cc));
}

#include "+unsupport.h"
