#import "+type.h"
#include "+support.h"

/// ___
// (in iter)
static NSArray* intercalate(Iter a, Iter b) {
  return concat(intersperse(a, b));
}


test {
    // TODO: Add tests to me!
}

#include "+unsupport.h"
