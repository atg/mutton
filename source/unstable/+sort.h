#import "+type.h"
#include "+support.h"

/// Stably sorts an iterable, using compare:
// (in sorting)
static NSArray* sort(Iter it) {
    return sortBy(it, NULL);
}


test {
    
}

#include "+unsupport.h"
