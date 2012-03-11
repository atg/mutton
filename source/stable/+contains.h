#import "+type.h"
#include "+support.h"

/// Tells if the array contains the object.
// (in iter)
static BOOL contains(Iter it, id x) {
  return any(it, ^ BOOL (id y) { return [y isEqual:x]; });
}


test {
    ass( !contains(nil, 0) );
    
    ass( contains(list(foo, bar, baz), foo) );
    ass( contains(list(foo, bar, baz), bar) );
    ass( contains(list(baz, foo, bar, baz), baz) );
    
    ass( contains(list(foo, bar), foo) );
    ass( contains(list(bar, foo), foo) );
    
    ass( contains(list(foo, foo, bar), bar) );
    ass( contains(list(foo, bar, foo), bar) );
    ass( contains(list(bar, foo, foo), bar) );
    
    ass( !contains(emptylist(),         foo) );
    ass( !contains(list(foo),           baz) );
    ass( !contains(list(foo, bar),      baz) );
    ass( !contains(list(foo, bar, bar), baz) );
}

#include "+unsupport.h"
