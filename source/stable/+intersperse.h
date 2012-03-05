#include "+support.h"

/// A bit like componentsJoinedByString: but with general purpose iterables instead of strings.
// (in iter)
// (after count)
static NSArray* intersperse(Iter it, id x) {
    if (!it)
        return nil;
    yield_start;
    BOOL isFirst = YES;
    for (id y in it) {
        if (isFirst)
            isFirst = NO;
        else
            yield(x);
        yield(y);
    }
    yield_stop;
}


test {
    ass  (! intersperse(nil, foo) );
    asseq(emptylist(), intersperse(emptylist(), foo) );
    asseq(list(bar), intersperse(list(bar), foo) );
    asseq(list(foo, foo, bar), intersperse(list(foo, bar), foo) );
    asseq(list(foo, foo, bar, foo, baz), intersperse(list(foo, bar, baz), foo) );
}

#include "+unsupport.h"
