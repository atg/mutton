#include "+support.h"
#import "+type.h"


/// Like objectAtIndex: but works on general iterables, and returns nil if the index is out of bounds (instead of an exception).
// (in iter)
static id objectAt(Iter it, long n) {

    if (!it)
        return nil;
    if (n < 0)
        return nil;

    BOOL hasObjectAtIndex = responds(it, @selector(objectAtIndex:));
    BOOL hasCount = responds(it, @selector(count));

    if (hasCount) {
        if (n >= [it count])
            return nil;
        if (hasObjectAtIndex) {
            return [it objectAtIndex:n];
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
    
    asseq(foo, objectAt(@[foo], 0) );
    ass  ( !objectAt(@[foo], 1) );
    ass  ( !objectAt(@[foo], -1) );
    
    asseq(foo, objectAt(@[foo, bar, baz], 0) );
    asseq(bar, objectAt(@[foo, bar, baz], 1) );
    asseq(baz, objectAt(@[foo, bar, baz], 2) );
    ass  ( !objectAt(@[foo, bar, baz], -2) );
    ass  ( !objectAt(@[foo, bar, baz], -1) );
}

#include "-support.h"
