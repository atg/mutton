#import "+type.h"
#include "+support.h"

/// Returns true if all 
// (in iter)
static BOOL all(Iter it, Predicate p) {
    // TODO: Implement me!
    if (!it)
      return nil;
    
    for (id x in it)
      if (!p(x))
        return NO;

    return YES;
}


test {
    ass( !all(nil, 0) );
    
    ass( all(emptylist(), ^ BOOL (id x) { return x == foo; }) );
    ass( all(list(foo) , ^ BOOL (id x) { return x == foo; }) );
    ass( all(list(foo,foo), ^ BOOL (id x) { return x == foo; }) );
    ass( all(list(foo, foo, foo), ^ BOOL (id x) { return x == foo; }) );

    ass( !all(list(foo, bar), ^ BOOL (id x) { return x == foo; }) );
    ass( !all(list(bar, foo), ^ BOOL (id x) { return x == foo; }) );

    ass( !all(list(foo, foo, bar), ^ BOOL (id x) { return x == foo; }) );
    ass( !all(list(foo, bar, foo), ^ BOOL (id x) { return x == foo; }) );
    ass( !all(list(bar, foo, foo), ^ BOOL (id x) { return x == foo; }) );
}

#include "+unsupport.h"
