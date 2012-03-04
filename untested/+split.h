#include "+support.h"

/// A bit like componentsSeparatedByString: but with general purpose iterables instead of of strings
// (in iter)
static NSArray* split(Iter it) {
    // TODO: Implement me!
}


test {
    ass  (! split(nil, foo) );
    asseq(list(), split(list(), foo) );
    asseq(list(list(@"a")), split(list(@"a"), foo) );
    asseq(list(list(@"a", @"b")), split(list(@"a", @"b"), foo) );
    asseq(list(list(@"a", @"b"), list()), split(list(@"a", @"b", foo), foo) );
    asseq(list(list(), list(@"a", @"b")), split(list(foo, @"a", @"b"), foo) );
    asseq(list(list(), list(@"a", @"b"), list()), split(list(foo, @"a", @"b", foo), foo) );
    asseq(list(list(@"a", @"b"), list(@"c", @"d", @"e")), split(list(@"a", @"b", foo, @"c", @"d", @"e"), foo) );
    asseq(list(list(), list(@"a", @"b"), list(), list() list(@"c", @"d", @"e"), list()), split(list(foo, @"a", @"b", foo, foo, foo, @"c", @"d", @"e"), foo) );
}

#include "+unsupport.h"
