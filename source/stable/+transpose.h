#import "+type.h"
#include "+support.h"

/// Transposes the rows and columns of the matrix
// (in iter)
static NSArray* transpose(Iter it) {
  if (!it)
    return nil;
  
  NSMutableArray* normal = [[NSMutableArray alloc] init];
  for (id x in it)
    [normal addObject:[NSMutableArray arrayWithArray:x]];
  
  yield_start;
  
  for (long i = 0; i <= [normal count]; i++)
  {
    yield([NSMutableArray array]);
    BOOL isEmpty = YES;

    for (id x in normal)
    {
      if ([x count] == 0)
        continue;
      
      isEmpty = NO;
      
      [[mutton_yield_v_ lastObject] addObject:[x objectAtIndex:0]];
      [x removeObjectAtIndex:0];
    }
    
    if (isEmpty)
      [mutton_yield_v_ removeLastObject];
  }
  
  yield_stop;
}


test {
  ass( !transpose(nil) );
  
  asseq( emptylist(), transpose(emptylist()) );
  
  asseq( list(list(@"a")), transpose(list(list(@"a"))) );
  
  asseq(
    list(list(@"b",@"b")),
    transpose(list(list(@"b"),list(@"b"))) );
  
  asseq(
    list(list(@"a",@"a"), list(@"b",@"b"), list(@"c",@"c")),
    transpose(list(list(@"a",@"b",@"c"), list(@"a",@"b",@"c"))) );
  
  asseq(
    list(list(@"a", @"a", @"a"),
         list(@"b", @"b", @"b"),
         list(@"c", @"c")),
    transpose(list(list(@"a",@"b",@"c"),
                   list(@"a",@"b"),
                   list(@"a",@"b",@"c"))) );
}

#include "+unsupport.h"
