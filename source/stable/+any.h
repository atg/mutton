#import "+type.h"
#include "+support.h"

/// ___
// (in iter)
static BOOL any(Iter it, id x) {
    // TODO: Implement me!
    if (!it)
      return nil;
    
    for (id y in it)
      if ([x isEqual:y])
        return YES;
    
    return NO;
}


test {
    // TODO: Add tests to me!
    ass( !any(nil, 0) );
    
    ass( any(list(foo, bar, baz), foo) );
    ass( any(list(foo, bar, baz), bar) );
    ass( any(list(baz, foo, bar, baz), baz) );
    
    ass( any(list(foo, bar), foo) );
    ass( any(list(bar, foo), foo) );
    
    ass( any(list(foo, foo, bar), bar) );
    ass( any(list(foo, bar, foo), bar) );
    ass( any(list(bar, foo, foo), bar) );
    
    ass( !any(emptylist(),         foo) );
    ass( !any(list(foo),           baz) );
    ass( !any(list(foo, bar),      baz) );
    ass( !any(list(foo, bar, bar), baz) );
}

#include "+unsupport.h"
