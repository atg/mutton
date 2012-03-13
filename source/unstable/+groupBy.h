#import "+type.h"
#include "+support.h"

/// Groups similar objects using supplied predicate.
// (in iter)
static NSArray* groupBy(Iter it, BinaryPredicate eq) {
  if (!it)
    return nil;

  yield_start;
  
  [mutton_yield_v_ addObject:[NSMutableArray array];
  
  for (id x in it) {
  
    if (eq([[mutton_yield_v_ lastObject] lastObject], x))
      [[mutton_yield_v_ lastObject] addObject:x];
    else
      [mutton_yield_v_ addObject:[NSMutableArray array]];
  }
  
  yield_stop;
}


test {
  BinaryPredicate ident = ^ id (id x, id y) { return [x isEquals:y ]}
  asseq( list(@"M",@"i",@"ss",@"i",@"ss",@"i",@"pp",@"i"), groupBy(@"Mississipi", ident) );
}

#include "+unsupport.h"
