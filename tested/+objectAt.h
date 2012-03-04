#import "+type.h"
#import "+object.h"

#include "+support.h"

/// Like objectAtIndex: but works on general iterables, and returns nil if the index is out of bounds (instead of an exception).
// (in iter)
static id objectAt(Iter it, long n) {

    if (!it)
        return nil;
    if (n < 0)
        return nil;
    
    if (responds(it, @selector(count))) {
        if (n >= [(NSArray*)it count])
            return nil;
        if (responds(it, @selector(objectAtIndex:))) {
            return [(NSArray*)it objectAtIndex:n];
        }
    }

    NSInteger i = 0;
    for (id x in it) {
        if (i == n)
            return x;
        i++;
    }

    return nil;
}


test {
    ass  ( !objectAt(nil, 0) );
    ass  ( !objectAt(nil, 1) );
    ass  ( !objectAt(nil, -1) );
    
    asseq(foo, objectAt(list(foo), 0) );
    ass  ( !objectAt(list(foo), 1) );
    ass  ( !objectAt(list(foo), -1) );
    
    asseq(foo, objectAt(list(foo, bar, baz), 0) );
    asseq(bar, objectAt(list(foo, bar, baz), 1) );
    asseq(baz, objectAt(list(foo, bar, baz), 2) );
    ass  ( !objectAt(list(foo, bar, baz), -2) );
    ass  ( !objectAt(list(foo, bar, baz), -1) );
}

#include "+unsupport.h"
