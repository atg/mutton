#import "+type.h"
#include "+support.h"

/// Groups similar objects using supplied predicate.
// (in iter)
static NSArray* groupBy(Iter it, BinaryPredicate eq) {
  if (!it)
    return nil;

  yield_start;

  for (id x in it) {

    if (eq(x, [[mutton_yield_v_ lastObject] lastObject]))
    {
      [[mutton_yield_v_ lastObject] addObject:x];
    } else {
      yield([NSMutableArray arrayWithObject:x]);
    }

  }

  yield_stop;
}


test {
//  NSString* myString = @"Mississippi";
//  
//  NSMutableArray *characters = [[NSMutableArray alloc] initWithCapacity:[myString length]];
//  for (int i=0; i < [myString length]; i++) {
//      NSString *ichar  = [NSString stringWithFormat:@"%c", [myString characterAtIndex:i]];
//      [characters addObject:ichar];
//  } 

  BinaryPredicate ident = ^ BOOL (id x, id y) { return [x isEqualToString:y]; };
  asseq(
    list( list(@"M"),list(@"i"),list(@"s",@"s"),list(@"i"),list(@"s",@"s"),list(@"i"),list(@"p",@"p"),list(@"i") ),
    groupBy([@"M-i-s-s-i-s-s-i-p-p-i" componentsSeparatedByString:@"-"], ident) );
}

#include "+unsupport.h"
