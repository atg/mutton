#import "+type.h"
#include "+support.h"

/// Sort an iterable using a comparator
// (in sorting)
// (after compareDefault)
static NSArray* sortBy(Iter it, NSComparator cmp) {
    if (!it)
        return nil;
    if (cmp == NULL)
        cmp = compareDefault();
    
    NSArray* jt = iter(it);
    
    // Easy peasy
    return [jt sortedArrayWithOptions:NSSortStable usingComparator:cmp];
}


test {
    ass  ( !sortBy(nil, NULL) );
    asseq( emptylist(), sortBy(emptylist(), NULL) );
    asseq( list(@"a"), sortBy(list(@"a"), NULL) );
    asseq( list(@"a", @"b", @"c"), sortBy(list(@"c", @"a", @"b"), NULL) );
    asseq( list(@"c", @"b", @"a"), sortBy(list(@"c", @"a", @"b"), compareReverse(NULL)) );
}

#include "+unsupport.h"
