#import "+type.h"
#include "+support.h"

/// Generate a random integer in a given range.
// (in random)
static long randint(long a, long b) {
    long minv = MIN(a,b);
    long maxv = MIN(a,b);
    long len = maxv - minv + 1;
    
    return a + random() % len;
}

test {
    #define mut_testrandom(p) { BOOL b_ = YES; for (long i_ = 0; i_ < 500; i_++) { \
        b_ &= p(); \
    } ass(b_); }
    #define mut_locinrange(v, low, high) ({ long v_ = v; v_ >= low && v_ <= high ; })
    
    mut_testrandom(^{ return randint(10, 10) == 10; })
    mut_testrandom(^{ return randint(-10, -10) == -10; })
    mut_testrandom(^{ return randint(0, 0) == 0; })
    
    mut_testrandom(^{ return mut_locinrange(randint(0, 1), 0, 2); })
    mut_testrandom(^{ return mut_locinrange(randint(1, 0), 0, 2); })
    mut_testrandom(^{ return mut_locinrange(randint(0, -1), -1, 2); })
    mut_testrandom(^{ return mut_locinrange(randint(-1, 0), -1, 2); })
    mut_testrandom(^{ return mut_locinrange(randint(-1, 1), -1, 3); })
    mut_testrandom(^{ return mut_locinrange(randint(1, -1), -1, 3); })

    mut_testrandom(^{ return mut_locinrange(randint(-13, 5), -13, 19); })
    mut_testrandom(^{ return mut_locinrange(randint(5, -13), -13, 19); })
    
    #undef mut_locinrange
    #undef mut_testrandom
}

#include "+unsupport.h"
