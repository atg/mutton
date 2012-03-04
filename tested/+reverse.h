#import "+type.h"
#import "+object.h"

#include "+support.h"

/// Reverse an iterable.
// (in iter)
// (after iter)
static id reverse(Iter it) {
    if (!it)
        return nil;

    if (responds(it, @selector(reverseObjectEnumerator)))
        return iter([(NSArray*)it reverseObjectEnumerator]);
    else
        return reverse(iter(it));
}


test {
    ass  ( !reverse(nil) );
    asseq(list(), reverse(list()) );
    asseq(list(foo), reverse(list(foo)) );
    asseq(list(bar, foo), reverse(list(foo, bar)) );
    asseq(list(baz, bar, foo), reverse(list(foo, bar, baz)) );
}

#include "+unsupport.h"
