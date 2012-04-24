#import "+type.h"
#include "+support.h"

/// Returns the index of <code>el</code> in <code>it</code> or <code>-1</code> if it wasn't found.
// (in iter)
static long elemIndex(Iter it, id e) {
    long idx = -1;
    long i = 0;
    for (id x in it) {
        if (equals(e, x))
            return idx;
        i++;
    }
    return idx;
}


test {
    ass ( 0 == elemIndex(list(@"a", @"b", @"c"), @"a") );
    ass ( 1 == elemIndex(list(@"a", @"b", @"c"), @"b") );
    ass ( 2 == elemIndex(list(@"a", @"b", @"c"), @"c") );
    ass ( -1 == elemIndex(list(@"a", @"b", @"c"), @"d") );
    ass ( -1 == elemIndex(emptylist(), @"a") );
    ass ( -1 == elemIndex(nil, @"a") );
}

#include "+unsupport.h"
