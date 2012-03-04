#include "+support.h"
#import "+type.h"


/// Find the last object of the iterable, or nil if it's empty.
// (in iter)
static id last(Iter it) {
    if (responds(it, @selector(lastObject)))
        return [(NSArray*)it lastObject];

    id v = nil;
    for (id x in it) {
        v = x;
    }
    return v;
}


test {
    ass  ( !last(nil) );
    ass  ( !last(@[]) );
    asseq( bar, last(@[bar]) );
    asseq( baz, last(@[foo, bar, baz]) );
}

#include "+unsupport.h"
