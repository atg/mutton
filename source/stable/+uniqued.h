#import "+type.h"
#include "+support.h"

/// Remove duplicate objects, as determined by their -hash and isEqual: (i.e., the objects are inserted into an NSSet to determine equality). O(n).
// (in iter)
static NSArray* uniqued(Iter it) {
    if (!it)
        return nil;
    
    NSMutableSet* s = [NSMutableSet set];
    yield_start;
    for (id x in it) {
        if (![s containsObject:x]) {
            [s addObject:x];
            yield(x);
        }
    }
    yield_stop;
}


test {
    ass  ( !uniqued(nil) );
    asseq( emptylist(), uniqued(emptylist()) );
    asseq( list(foo, bar, baz), uniqued(list(foo, bar, baz)) );
    
    NSString* foo2 = [foo mutableCopy];
    NSString* foo3 = [foo mutableCopy];
    NSString* foo4 = [foo mutableCopy];
    
    asseq( list(foo), uniqued(list(foo, foo2, foo3, foo4)) );
    asseq( list(bar, foo), uniqued(list(bar, foo, foo2, foo3, foo4)) );
}

#include "+unsupport.h"
