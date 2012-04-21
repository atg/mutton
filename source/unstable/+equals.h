#import "+type.h"
#include "+support.h"

/// Determines if two (possibly nil) objects are equal. This differs from -isEqual: because it considers the case where both objects are nil
// (in object)
static id equals(id a, id b) {
    return a == b || [a isEqual:b];
}


test {
    // TODO: Add tests to me!
}

#include "+unsupport.h"
