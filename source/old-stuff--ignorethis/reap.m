
NSArray* reap(void(^body)(Sowing f)) {
    yield_start;
    Sowing sow = ^(id x){
        yield(x);
    };
    
    body(sow);
    yield_stop;
}

NSArray* reap(^void (Sowing sow){
    sow(@"a");
    // ...
    sow(@"c");
    sow(@"d");
    // ...
});

// -> @[@"a", @"c", @"d"]