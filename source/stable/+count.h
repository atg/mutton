#import "+type.h"
#import "+object.h"

#include "+support.h"

/// Find the number of objects in an array or iterable.
// (in iter)
static long count(Iter it) {
    if (responds(it, @selector(count)))
        return [(NSArray*)it count];

    long i = 0;
    for (id x in it) {
        i++;
    }
    return i;
}


test {
    ass  ( !count(nil) );
    ass  ( !count(emptylist()) );
    ass  ( 1 == count(list(foo)) );
    ass  ( 2 == count(list(foo, bar)) );
    ass  ( 3 == count(list(foo, bar, baz)) );
}

#include "+unsupport.h"
