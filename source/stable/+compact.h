#import "+type.h"
#include "+support.h"

/// Removes falsy values from the array.
// (in iter)
// (after filter)
static NSArray* compact(Iter it) {
    return filter(it, ^ BOOL (id x) { return truthy(x); });
}


test {
    ass( !compact(nil) );
    
    asseq( emptylist(), compact(emptylist())    );
    asseq( emptylist(), compact(list(@""))      );
    asseq( emptylist(), compact(list(@"", @"")) );
    
    asseq( list(foo), compact(list(@"", foo)) );
    asseq( list(foo), compact(list(foo, @"")) );

    asseq( list(foo, bar, baz), compact(list(foo, @"", bar, @"", baz)) );
}

#include "+unsupport.h"
