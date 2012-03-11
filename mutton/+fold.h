#import "+type.h"

#import <Foundation/Foundation.h>
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

/// Combine a list of values into a single value. Returns nil if the list is empty. Socialist version.
// (in fold)
// (after foldl)
static id foldl1(Iter it, BinaryMapping f) {
    return foldl(it, nil, f);
}

#include "+unsupport.h"
