#import "+type.h"
#include "+support.h"

/// Glue together an array of arrays (or iterable of iterables) to make one big array.
// (in iter)
static NSArray* concat(Iter it) {
    if (!it)
        return nil;
    
    yield_start;
    for (Iter j in it) {
        if ([j isKindOfClass:[NSArray class]]) {
            yield_from((NSArray*)j);
        }
        else {
            for (id x in j) {
                yield(x);
            }
        }
    }
    yield_stop;
}


test {
    NSArray* a = list(foo, bar, baz);
    NSArray* b = [NSSet setWithObjects:foo, bar, nil];
    NSArray* c = emptylist();
    NSArray* d = [NSSet set];
    NSArray* e = list(baz);
        
    ass  ( !concat(nil) );
    ass  ( [concat(list(a, b, c, d, e)) count] == [a count] + [b count] + [c count] + [d count] + [e count] );
    asseq( list(foo, bar, baz, foo, bar, baz), concat(list(a, iter(b), c, d, e)) );
}

#include "+unsupport.h"
