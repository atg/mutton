#import "+type.h"
#include "+support.h"

/// Map each element to a list of new elements (which may be empty), then glue the lists together. It's map, filter and a bit more on top.
// (in iter)
// (after concat)
// (after map)
static NSArray* concatMap(Iter it, Iter(^f)(id)) {
    if (!it)
        return nil;
    return concat(map(it, f)); // Ahhhh the joys of functional programming at last
}


test {
    ass  ( !concatMap(nil, nil) );
}

#include "+unsupport.h"
