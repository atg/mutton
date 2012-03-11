#import "+type.h"
#include "+support.h"

/// Returns true if the predicate validates to any of the elements, false otherwise.
// (in iter)
static BOOL any(Iter it, Predicate p) {
    if (!it)
      return NO;
    
    for (id x in it) {
      if (p(x))
        return YES;
    }
    
    return NO;
}


test {
    ass( !any(nil, 0) );
    
    ass( any(list(foo, bar, baz), ^ BOOL (id x) { return x == foo; }) );
    ass( any(list(foo, bar, baz), ^ BOOL (id x) { return x == bar; }) );
    ass( any(list(baz, foo, bar, baz), ^ BOOL (id x) { return [x isEqual:baz]; }) );
    
    ass( any(list(foo, bar), ^ BOOL (id x) { return x == foo; }) );
    ass( any(list(bar, foo), ^ BOOL (id x) { return x == foo; }) );
    
    ass( any(list(foo, foo, bar), ^ BOOL (id x) { return x == bar; }) );
    ass( any(list(foo, bar, foo), ^ BOOL (id x) { return x == bar; }) );
    ass( any(list(bar, foo, foo), ^ BOOL (id x) { return x == bar; }) );
    
    ass( !any(emptylist(),         ^ BOOL (id x) { return x == foo; }) );
    ass( !any(list(foo),           ^ BOOL (id x) { return x == baz; }) );
    ass( !any(list(foo, bar),      ^ BOOL (id x) { return x == baz; }) );
    ass( !any(list(foo, bar, bar), ^ BOOL (id x) { return x == baz; }) );
}

#include "+unsupport.h"
