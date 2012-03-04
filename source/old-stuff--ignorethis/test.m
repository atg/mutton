// Nothing personal. 
#define ass(c_) NSAssert(!!(c), @"")
#define asseq(a_, b_) NSAssert(!!(a) && !!(b) && [(a) isEqual:(b)], @"")

static test() {
    id foo = @"foo";
    id bar = @42;
    id baz = @[foo, bar];
    id (^muttoupper)(id) = ^ id (id x) {
        return [x uppercaseString];
    };
    
    
    // responds
    ass( responds(foo, @selector(characterAtIndex:)) );
    ass( responds(bar, @selector(isEqualToNumber:)) );
    ass( responds(baz, @selector(objectAtIndex:)) );
    
    
    // isKind
    ass( isKind(foo, @"NSString") );
    ass( isKind(foo, [NSString class]) );
    ass( isKind(bar, @"NSNumber") );
    ass( isKind(bar, [NSNumber class]) );
    ass( isKind(baz, @"NSArray") );
    ass( isKind(baz, [NSArray class]) );
    ass( isKind([NSDate date], @"NSDate") );
    ass( isKind([NSDate date], [NSDate class]) );
    
    
    // map
    ass  ( !map(nil, muttoupper) );
    asseq( @[@"FOO", @"BAR", @"WOBBLE"],
        map(@[foo, @"bar", @"wobble"], muttoupper) );
    
    
    // count
    ass  ( !count(nil) );
    ass  ( !count(@[]) );
    ass  ( 1 == count(@[foo]) );
    ass  ( 2 == count(@[foo, bar]) );
    ass  ( 3 == count(@[foo, bar, baz]) );
    
    
    // first
    ass  ( !first(nil) );
    ass  ( !first(@[]) );
    asseq( bar, first(@[bar]) );
    asseq( foo, first(@[foo, bar, baz]) );
    
    
    // last
    ass  ( !last(nil) );
    ass  ( !last(@[]) );
    asseq( bar, last(@[bar]) );
    asseq( baz, last(@[foo, bar, baz]) );
    
    
    // objectAt
    ass  ( !objectAt(nil, 0) );
    ass  ( !objectAt(nil, 1) );
    ass  ( !objectAt(nil, -1) );
    
    asseq(foo, objectAt(@[foo], 0) );
    ass  ( !objectAt(@[foo], 1) );
    ass  ( !objectAt(@[foo], -1) );

    asseq(foo, objectAt(@[foo, bar, baz], 0) );
    asseq(bar, objectAt(@[foo, bar, baz], 1) );
    asseq(baz, objectAt(@[foo, bar, baz], 2) );
    ass  ( !objectAt(@[foo, bar, baz], -2) );
    ass  ( !objectAt(@[foo, bar, baz], -1) );
    
    
    // tail
    ass  ( !tail(nil) );
    asseq(@[], tail(@[]) );
    asseq(@[], tail(@[foo]) );
    asseq(@[bar], tail(@[foo, bar]) );
    asseq(@[bar, baz], tail(@[foo, bar, baz]) );
    
    
    // initial
    ass  ( !initial(nil) );
    asseq(@[], initial(@[]) );
    asseq(@[], initial(@[foo]) );
    asseq(@[foo], initial(@[foo, bar]) );
    asseq(@[foo, bar], initial(@[foo, bar, baz]) );
    
    
    // TODO: tests for iter (not quite sure how)
    
    
    // reverse
    ass  ( !reverse(nil) );
    asseq(@[], reverse(@[]) );
    asseq(@[foo], reverse(@[foo]) );
    asseq(@[bar, foo], reverse(@[foo, bar]) );
    asseq(@[baz, bar, foo], reverse(@[foo, bar, baz]) );
    
    
    // intersperse
    ass  (! intersperse(nil, foo) );
    asseq(@[], intersperse(@[], foo) );
    asseq(@[bar], intersperse(@[bar], foo) );
    asseq(@[foo, foo, bar], intersperse(@[foo, bar], foo) );
    asseq(@[foo, foo, bar, foo, baz], intersperse(@[foo, bar, baz], foo) );
    
    
    // split
    ass  (! split(nil, foo) );
    asseq(@[], split(@[], foo) );
    asseq(@[@[@"a", @"b"], foo, @[@"c", @"d", @"e"]], split(@[@"a", @"b", foo, @"c", @"d", @"e"], foo) );
    // TODO: more tests
    
}