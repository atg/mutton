#import "+type.h"
#include "+support.h"

/// Allows you to "sow" values, and "reap" them at the end. Pass a block to reap that takes a single Mapping argument (conventionally named "sow"). Do some work in this block, then call sow each time you want to save a value. Reap will run your block and return the values that you sowed.
// (in iter)
static NSArray* reap(void(^body)(Mapping sow)) {
    yield_start;
    Mapping sow = ^(id x){
        if (x)
            yield(x);
        return x;
    };

    body(sow);
    yield_stop;
}


test {
    asseq( list(@"a", @"b", @"c"), reap(^void (Mapping sow) {
        sow(@"a"); sow(@"b"); sow(@"c");
    }) );
}

#include "+unsupport.h"
