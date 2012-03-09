#include "+support.h"

/// A bit like componentsJoinedByString: but with general purpose iterables instead of strings.
// (in iter)
static NSArray* intersperse(Iter it, id glue) {
    if (!it)
        return nil;
    
    yield_start;
    
    for (id x in it) {
        yield(x);
        yield(glue);
    }
    
    [mutton_yield_v_ removeLastObject];

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
