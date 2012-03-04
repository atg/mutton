#include "+support.h"


/// A bit like componentsSeparatedByString: but with general purpose iterables instead of of strings
// (in iter)
static NSArray* split(Iter it) {
    // TODO: Implement me!
}


test {
    ass  (! split(nil, foo) );
    asseq(@[], split(@[], foo) );
    asseq(@[@[@"a"]], split(@[@"a"], foo) );
    asseq(@[@[@"a", @"b"]], split(@[@"a", @"b"], foo) );
    asseq(@[@[@"a", @"b"], @[]], split(@[@"a", @"b", foo], foo) );
    asseq(@[@[], @[@"a", @"b"]], split(@[foo, @"a", @"b"], foo) );
    asseq(@[@[], @[@"a", @"b"], @[]], split(@[foo, @"a", @"b", foo], foo) );
    asseq(@[@[@"a", @"b"], @[@"c", @"d", @"e"]], split(@[@"a", @"b", foo, @"c", @"d", @"e"], foo) );
    asseq(@[@[], @[@"a", @"b"], @[], @[] @[@"c", @"d", @"e"], @[]], split(@[foo, @"a", @"b", foo, foo, foo, @"c", @"d", @"e"], foo) );
}

#include "-support.h"
