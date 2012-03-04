#import "+type.h"
#import "+object.h"

#include "+support.h"

/// Convert a general purpose iterable to an NSArray*
// (in iter)
static NSArray* iter(Iter it) {
    if (!it)
        return nil;

    if (isKind(it, [NSMutableArray class]))
        return [(NSMutableArray*)it copy];

    // If it's a non-mutable array, we're probably OK to not copy it
    if (isKind(it, [NSArray class]))
        return (NSArray*)it;

    yield_start;
    for (id x in it) {
        yield(x);
    }
    yield_stop;
}

test {
    ass  ( !iter(nil) );
    asseq( emptylist(), iter(emptylist()) );
    asseq( list(foo, bar, baz), iter(list(foo, bar, baz)) );
    asseq( list(baz, bar, foo), iter([list(foo, bar, baz) reverseObjectEnumerator]) );
}

#include "+unsupport.h"
