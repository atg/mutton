#import "+type.h"
#include "+support.h"

/// Applies a function over and over again to x until p(x) evaluates to true.
// (in iter)
static id until(Predicate p, Mapping f, id x) {
    while (!p(x))
        x = f(x);
    return x;
}


test {
    Predicate odd = ^BOOL(NSNumber* n) {
        return [n integerValue] % 2 == 1;
    };
    Mapping divideby2 = ^NSNumber*(NSNumber* n) {
        return [NSNumber numberWithInteger:[n integerValue] / 2];
    };
    
    asseq([NSNumber numberWithInteger:25], until(odd, divideby2, [NSNumber numberWithInteger:400]));
}

#include "+unsupport.h"
