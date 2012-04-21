#import "+type.h"
#include "+support.h"

/// Nests function calls such that nest(x, 3, f) ==> f(f(f(x)))
// (in iter)
static id nest(id x, long loops, Mapping f) {
    if (!f)
      return nil;
    
    if (loops < 0)
      [NSException raise:@"Negative nesting index" format:@"foo of %d is invalid", loops];
    
    if (loops == 0)
      return x;

    return f( nest(x, loops-1, f) );
}


test {
  Mapping appends = ^ id (id x) { return [x stringByAppendingString: @"a"]; };

  // uncomment next line to throw exception
  // ass( nest(@"a", appends,  -1) );

  ass( !nest(nil, 0, appends) );
  ass( !nest(@"a", 0, nil)    );
  
  asseq( @"", nest(@"", 0, appends)    );
  asseq( @"aaa", nest(@"", 3, appends) );
}

#include "+unsupport.h"
