#import "+type.h"
#include "+support.h"

/// intercalate a b ==> concat $ intersperse a b
// (in iter)
// (after intersperse)
// (after concat)
static NSArray* intercalate(Iter a, Iter b) {
    return concat(intersperse(a, b));
}


test {
    asseq( list(foo, baz, bar), intercalate(list(list(foo), list(bar)), list(baz)) );
    asseq( list(foo, baz, bar, baz, foo, baz, bar)
         , intercalate(list(list(foo), list(bar), list(foo), list(bar)), list(baz)) );
}

#include "+unsupport.h"
