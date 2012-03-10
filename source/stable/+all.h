#import "+type.h"
#include "+support.h"

/// ___
// (in iter)
static BOOL all(Iter it, id x) {
    // TODO: Implement me!
    if (!it)
      return nil;
    
    for (id y in it)
      if (![x isEqual:y])
        return NO;

    return YES;
}


test {
    // TODO: Add tests to me!

    ass( !all(nil, foo) );
    
    ass( all(emptylist(), foo) );
    ass( all(list(foo) , foo) );
    ass( all(list(foo,foo), foo) );
    ass( all(list(foo, foo, foo), foo) );

    ass( !all(list(foo, bar), foo) );
    ass( !all(list(bar, foo), foo) );

    ass( !all(list(foo, foo, bar), foo) );
    ass( !all(list(foo, bar, foo), foo) );
    ass( !all(list(bar, foo, foo), foo) );
}

#include "+unsupport.h"
