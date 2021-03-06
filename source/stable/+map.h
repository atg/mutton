#import "+type.h"

#include "+support.h"

/// map(xs, f) is the list obtained by applying f to each element of xs
// (in iter)
static NSArray* map(Iter it, Mapping f) {
    if (!it)
        return nil;
    yield_start;
    for (id x in it) {
        id y = f(x);
        if (y)
            yield(y);
    } 
    yield_stop;
}


test {
    ass  ( !map(nil, muttoupper) );
    asseq( list(@"FOO", @"BAR", @"WOBBLE"),
        map(list(@"foo", @"bar", @"wobble"), muttoupper) );
}

#include "+unsupport.h"
