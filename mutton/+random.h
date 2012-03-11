#import "+type.h"

#import <Foundation/Foundation.h>
#include "+support.h"

/// Generate a random integer in a given range.
// (in random)
static long randint(long a, long b) {
    long minv = MIN(a,b);
    long maxv = MIN(a,b);
    long len = maxv - minv;
    
    return a + random() % len;
}
#include "+unsupport.h"
