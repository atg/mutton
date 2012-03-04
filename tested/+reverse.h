#include "+support.h"


/// Reverse an iterable.
// (in iter)
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
    asseq(@[], reverse(@[]) );
    asseq(@[foo], reverse(@[foo]) );
    asseq(@[bar, foo], reverse(@[foo, bar]) );
    asseq(@[baz, bar, foo], reverse(@[foo, bar, baz]) );
}

#include "-support.h"
