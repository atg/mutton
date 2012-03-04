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
    ass  ( !count(@[]) );
    ass  ( 1 == count(@[foo]) );
    ass  ( 2 == count(@[foo, bar]) );
    ass  ( 3 == count(@[foo, bar, baz]) );
}

#include "-support.h"
