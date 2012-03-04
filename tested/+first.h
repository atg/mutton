#import "+type.h"

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
    ass  ( !first(list()) );
    asseq( bar, first(list(bar)) );
    asseq( foo, first(list(foo, bar, baz)) );
}

#include "+unsupport.h"
