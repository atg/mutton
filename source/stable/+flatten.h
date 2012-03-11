#import "+type.h"
#include "+support.h"

/// Recursively flattens a tree of iterables into a single array.
// (in iter)
static NSArray* flatten(Iter it) {
    if (!it)
        return nil;
    
    yield_start;
    
    __block void(^_flatten)(id) = ^void(id y){
        if (!y)
            return;
        for (id x in y) {
            if ([x respondsToSelector:@selector(countByEnumeratingWithState:objects:count:)])
                _flatten(x);
            else
                yield(x);
        }
    };
    
    _flatten(it);
    
    yield_stop;
}


test {
    ass  ( !flatten(nil) );
    asseq( emptylist(), flatten(emptylist()) );
    asseq( list(@"foo", @"bar", @"baz"), flatten(list(@"foo", @"bar", @"baz")) );
    asseq( list(@"foo", @"bar", @"baz", @"foo", @"bar", @"baz", @"foo", @"bar", @"baz"), flatten(list(list(@"foo", @"bar", @"baz"), emptylist(), list(@"foo", emptylist(), @"bar", @"baz", list(@"foo", @"bar", @"baz", list(emptylist()))))) ); // if THAT doesn't do it, nothing will
}

#include "+unsupport.h"
