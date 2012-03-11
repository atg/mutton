#import "+type.h"
#include "+support.h"

/// Zips both arrays using the BinaryMapping. That's what.
// (in iter)
// (after count)
// (after objectAt)
static NSArray* zipWith(Iter a, Iter b, BinaryMapping f) {
    if (!a || !b)
      return nil;

    long tempa = count(a);
    long tempb = count(b);
    
    long count = (tempa > tempb) ? tempb : tempa;
    
    yield_start;
    
    for (long i=0; i < count; ++i)
    {
      yield( f(objectAt(a, i), objectAt(b, i)) );
    }
    
    yield_stop;
}


test {
    BinaryMapping plussing = ^id(id x, id y) { return list(x,y); };
    
    ass( !zipWith(emptylist(), nil, plussing) );
    ass( !zipWith(nil, emptylist(), plussing) );
    
    asseq( emptylist(), zipWith(emptylist(), emptylist(), plussing) );
    
    asseq(
      list(list(@"a",@"a")),
      zipWith(list(@"a"), list(@"a"), plussing) );

    asseq(
      list(list(@"a",@"c"), list(@"b",@"d")),
      zipWith(list(@"a",@"b"), list(@"c",@"d"), plussing) );

    asseq(
      list(list(@"a",@"d"), list(@"b",@"e")),
      zipWith(list(@"a",@"b",@"c"), list(@"d",@"e"), plussing) );

    asseq(
      list(list(@"a",@"d"), list(@"b",@"e"), list(@"c",@"f")),
      zipWith(list(@"a",@"b",@"c"), list(@"d",@"e",@"f"), plussing) );
}

#include "+unsupport.h"
