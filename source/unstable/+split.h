#include "+support.h"

/// A bit like componentsSeparatedByString: but with general purpose iterables instead of of strings
// (in iter)
static NSArray* split(Iter it) {
    // TODO: Implement me!
}


test {
    ass  (! split(nil, foo) );
    asseq(emptylist(), split(emptylist(), foo) );
    asseq(list(list(@"a")), split(list(@"a"), foo) );
    asseq(list(list(@"a", @"b")), split(list(@"a", @"b"), foo) );
    asseq(list(list(@"a", @"b"), emptylist()), split(list(@"a", @"b", foo), foo) );
    asseq(list(emptylist(), list(@"a", @"b")), split(list(foo, @"a", @"b"), foo) );
    asseq(list(emptylist(), list(@"a", @"b"), emptylist()), split(list(foo, @"a", @"b", foo), foo) );
    asseq(list(list(@"a", @"b"), list(@"c", @"d", @"e")), split(list(@"a", @"b", foo, @"c", @"d", @"e"), foo) );
    asseq(list(emptylist(), list(@"a", @"b"), emptylist(), emptylist() list(@"c", @"d", @"e"), emptylist()), split(list(foo, @"a", @"b", foo, foo, foo, @"c", @"d", @"e"), foo) );
}

#include "+unsupport.h"
