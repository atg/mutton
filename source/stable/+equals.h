#import "+type.h"
#include "+support.h"

/// Determines if two (possibly nil) objects are equal. This differs from -isEqual: because it considers the case where both objects are nil
// (in object)
static BOOL equals(id a, id b) {
    return a == b || [a isEqual:b];
}


test {
    ass  ( equals(nil, nil) );
    ass  ( !equals(@"", nil) );
    ass  ( !equals(nil, @"") );
    ass  ( equals(@"", @"") );
    ass  ( equals(@"hello", [@"hello" mutableCopy]) );
}

#include "+unsupport.h"
