#include "+support.h"


/// A bit like componentsJoinedByString: but with general purpose iterables instead of strings.
// (in iter)
static NSArray* intersperse(Iter it) {
    // TODO: Implement me!
}


test {
    ass  (! intersperse(nil, foo) );
    asseq(@[], intersperse(@[], foo) );
    asseq(@[bar], intersperse(@[bar], foo) );
    asseq(@[foo, foo, bar], intersperse(@[foo, bar], foo) );
    asseq(@[foo, foo, bar, foo, baz], intersperse(@[foo, bar, baz], foo) );
}

#include "-support.h"
