#include "+support.h"


/// Find the first object of the iterable, or nil if it's empty.
// (in iter)
static id first(Iter it) {
    for (id obj in it) {
        return obj;
    }
    return nil;
}


test {
    ass  ( !first(nil) );
    ass  ( !first(@[]) );
    asseq( bar, first(@[bar]) );
    asseq( foo, first(@[foo, bar, baz]) );
}

#include "-support.h"
