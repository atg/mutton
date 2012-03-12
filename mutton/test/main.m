#import "mutton.h"
#include "+support.h"


#pragma mark all (iter)
static void test_all_iter() {
    ass( !all(nil, 0) );
    
    ass( all(emptylist(), ^ BOOL (id x) { return x == foo; }) );
    ass( all(list(foo) , ^ BOOL (id x) { return x == foo; }) );
    ass( all(list(foo,foo), ^ BOOL (id x) { return x == foo; }) );
    ass( all(list(foo, foo, foo), ^ BOOL (id x) { return x == foo; }) );

    ass( !all(list(foo, bar), ^ BOOL (id x) { return x == foo; }) );
    ass( !all(list(bar, foo), ^ BOOL (id x) { return x == foo; }) );

    ass( !all(list(foo, foo, bar), ^ BOOL (id x) { return x == foo; }) );
    ass( !all(list(foo, bar, foo), ^ BOOL (id x) { return x == foo; }) );
    ass( !all(list(bar, foo, foo), ^ BOOL (id x) { return x == foo; }) );
}


#pragma mark any (iter)
static void test_any_iter() {
    ass( !any(nil, 0) );
    
    ass( any(list(foo, bar, baz), ^ BOOL (id x) { return x == foo; }) );
    ass( any(list(foo, bar, baz), ^ BOOL (id x) { return x == bar; }) );
    ass( any(list(baz, foo, bar, baz), ^ BOOL (id x) { return [x isEqual:baz]; }) );
    
    ass( any(list(foo, bar), ^ BOOL (id x) { return x == foo; }) );
    ass( any(list(bar, foo), ^ BOOL (id x) { return x == foo; }) );
    
    ass( any(list(foo, foo, bar), ^ BOOL (id x) { return x == bar; }) );
    ass( any(list(foo, bar, foo), ^ BOOL (id x) { return x == bar; }) );
    ass( any(list(bar, foo, foo), ^ BOOL (id x) { return x == bar; }) );
    
    ass( !any(emptylist(),         ^ BOOL (id x) { return x == foo; }) );
    ass( !any(list(foo),           ^ BOOL (id x) { return x == baz; }) );
    ass( !any(list(foo, bar),      ^ BOOL (id x) { return x == baz; }) );
    ass( !any(list(foo, bar, bar), ^ BOOL (id x) { return x == baz; }) );
}


#pragma mark applyIf (func)
static void test_applyIf_func() {
    ass  (!applyIf(nil, nil));
    ass  (!applyIf(nil, byIdentity()));
    asseq(foo, applyIf(foo, byIdentity()));
}


#pragma mark byBinarySel (func)
static void test_byBinarySel_func() {
    // TODO: Add tests to me!
}


#pragma mark byCompose (func)
static void test_byCompose_func() {
    Mapping allocate = ^id(id x) { return [x alloc]; };
    Mapping initialize = ^id(id x) { return [x init]; };
    Mapping allocinit = byCompose(initialize, allocate);
    
    asseq(@"", allocinit([NSString class]));
}


#pragma mark byConst (func)
static void test_byConst_func() {
    ass  ( !byConst(nil)(nil) );
    ass  ( !byConst(nil)(foo) );
    asseq( foo, byConst(foo)(nil) );
    asseq( foo, byConst(foo)(foo) );
    asseq( foo, byConst(foo)(bar) );
}


#pragma mark byFlip (func)
static void test_byFlip_func() {
    BinaryMapping joinstr = ^id(id x, id y) { return [x stringByAppendingString:y]; };

    asseq(@"barfoo", byFlip(joinstr)(@"foo", @"bar"));
}


#pragma mark byFunction (func)
static void test_byFunction_func() {
    ass  (!byFunction(NULL));
    
    Mapping f = byFunction((id(*)(id))&byConst);
    Mapping g = f(foo);
    id h = g(bar);
    asseq(foo, h);
}


#pragma mark byIdentity (func)
static void test_byIdentity_func() {
    ass  ( !byIdentity()(nil) );
    asseq( foo, byIdentity()(foo) );
}


#pragma mark compact (iter)
static void test_compact_iter() {
    ass( !compact(nil) );
    
    asseq( emptylist(), compact(emptylist())    );
    asseq( emptylist(), compact(list(@""))      );
    asseq( emptylist(), compact(list(@"", @"")) );
    
    asseq( list(foo), compact(list(@"", foo)) );
    asseq( list(foo), compact(list(foo, @"")) );

    asseq( list(foo, bar, baz), compact(list(foo, @"", bar, @"", baz)) );
}


#pragma mark concat (iter)
static void test_concat_iter() {
    NSArray* a = list(foo, bar, baz);
    NSArray* b = [NSSet setWithObjects:foo, bar, nil];
    NSArray* c = emptylist();
    NSArray* d = [NSSet set];
    NSArray* e = list(baz);
        
    ass  ( !concat(nil) );
    ass  ( [concat(list(a, b, c, d, e)) count] == [a count] + [b count] + [c count] + [d count] + [e count] );
    asseq( list(foo, bar, baz, foo, bar, baz), concat(list(a, iter(b), c, d, e)) );
}


#pragma mark concatMap (iter)
static void test_concatMap_iter() {
    ass  ( !concatMap(nil, nil) );
}


#pragma mark contains (iter)
static void test_contains_iter() {
    ass( !contains(nil, 0) );
    
    ass( contains(list(foo, bar, baz), foo) );
    ass( contains(list(foo, bar, baz), bar) );
    ass( contains(list(baz, foo, bar, baz), baz) );
    
    ass( contains(list(foo, bar), foo) );
    ass( contains(list(bar, foo), foo) );
    
    ass( contains(list(foo, foo, bar), bar) );
    ass( contains(list(foo, bar, foo), bar) );
    ass( contains(list(bar, foo, foo), bar) );
    
    ass( !contains(emptylist(),         foo) );
    ass( !contains(list(foo),           baz) );
    ass( !contains(list(foo, bar),      baz) );
    ass( !contains(list(foo, bar, bar), baz) );
}


#pragma mark count (iter)
static void test_count_iter() {
    ass  ( !count(nil) );
    ass  ( !count(emptylist()) );
    ass  ( 1 == count(list(foo)) );
    ass  ( 2 == count(list(foo, bar)) );
    ass  ( 3 == count(list(foo, bar, baz)) );
}


#pragma mark drop (iter)
static void test_drop_iter() {
    ass  ( !drop(nil, 0) );
    ass  ( !drop(nil, 1) );
    ass  ( !drop(nil, 10) );
    
    asseq( emptylist(), drop(emptylist(), 0) );    
    asseq( emptylist(), drop(emptylist(), 1) );    
    asseq( emptylist(), drop(emptylist(), 10) );    
    
    asseq( emptylist(), drop(list(foo), 1) );    
    asseq( emptylist(), drop(list(foo), 2) );
    asseq( emptylist(), drop(list(foo), 10) );
    
    asseq( emptylist(), drop(list(foo, baz), 2) );
    asseq( emptylist(), drop(list(foo, bar), 3) );
    asseq( emptylist(), drop(list(foo), 10) );
    
    asseq( list(foo), drop(list(foo), 0) );
    asseq( list(foo), drop(list(bar, foo), 1) );
    asseq( list(baz), drop(list(bar, foo, baz), 2) );
    
    asseq( list(foo), drop(list(foo), 0) );
    asseq( list(foo), drop(list(bar, foo), 1) );
    asseq( list(foo), drop(list(bar, baz, foo), 2) );
    
    asseq( list(baz, foo), drop(list(bar, baz, foo), 1) );
}


#pragma mark falsy (bool)
static void test_falsy_bool() {
    ass  ( falsy(nil) );
    ass  ( falsy(emptylist()) );
    ass  ( falsy([NSSet set]) );
    ass  ( falsy([NSDictionary dictionary]) );
    ass  ( falsy(@"") );
    
    ass  ( !falsy([NSDate date]) );
    ass  ( !falsy(list(foo)) );
    ass  ( !falsy([NSSet setWithObject:foo]) );
    ass  ( !falsy(foo) );
}


#pragma mark filter (iter)
static void test_filter_iter() {
    BOOL (^p)(id) = ^BOOL(NSString* s) {
        return [s intValue] % 3 == 1;
    };
    ass  ( !filter(nil, p) );
    asseq( emptylist(), filter(emptylist(), p) );
    asseq( emptylist(), filter(list(@"2"), p) );
    asseq( list(@"7"), filter(list(@"7"), p) );
    asseq( list(@"1", @"4", @"7"), filter(list(@"1", @"2", @"3", @"4", @"5", @"6", @"7"), p) );
}


#pragma mark first (iter)
static void test_first_iter() {
    ass  ( !first(nil) );
    ass  ( !first(emptylist()) );
    asseq( bar, first(list(bar)) );
    asseq( foo, first(list(foo, bar, baz)) );
}


#pragma mark flatten (iter)
static void test_flatten_iter() {
    ass  ( !flatten(nil) );
    asseq( emptylist(), flatten(emptylist()) );
    asseq( list(@"foo", @"bar", @"baz"), flatten(list(@"foo", @"bar", @"baz")) );
    asseq( list(@"foo", @"bar", @"baz", @"foo", @"bar", @"baz", @"foo", @"bar", @"baz"), flatten(list(list(@"foo", @"bar", @"baz"), emptylist(), list(@"foo", emptylist(), @"bar", @"baz", list(@"foo", @"bar", @"baz", list(emptylist()))))) ); // if THAT doesn't do it, nothing will
}


#pragma mark foldl (fold)
static void test_foldl_fold() {
    BinaryMapping cc = byBinarySel(@selector(stringByAppendingString:));
    
    ass  ( !foldl(nil, @"", cc));
    asseq( @"foobarbaz", foldl(list(@"foo", @"bar", @"baz"), @"", cc));
    asseq( @"HELLO", foldl(emptylist(), @"HELLO", cc));
    ass  ( !foldl(emptylist(), nil, cc));
}


#pragma mark foldl1 (fold)
static void test_foldl1_fold() {
    // No tests necessary
}


#pragma mark initial (iter)
static void test_initial_iter() {
    ass  ( !initial(nil) );
    asseq(emptylist(), initial(emptylist()) );
    asseq(emptylist(), initial(list(foo)) );
    asseq(list(foo), initial(list(foo, bar)) );
    asseq(list(foo, bar), initial(list(foo, bar, baz)) );
}


#pragma mark intersperse (iter)
static void test_intersperse_iter() {
    ass  (! intersperse(nil, foo) );
    asseq(emptylist(), intersperse(emptylist(), foo) );
    asseq(list(bar), intersperse(list(bar), foo) );
    asseq(list(foo, foo, bar), intersperse(list(foo, bar), foo) );
    asseq(list(foo, foo, bar, foo, baz), intersperse(list(foo, bar, baz), foo) );
}


#pragma mark isKind (object)
static void test_isKind_object() {
    ass( isKind(foo, @"NSString") );
    ass( isKind(foo, [NSString class]) );
    ass( isKind(bar, @"NSNumber") );
    ass( isKind(bar, [NSNumber class]) );
    ass( isKind(baz, @"NSArray") );
    ass( isKind(baz, [NSArray class]) );
    ass( isKind([NSDate date], @"NSDate") );
    ass( isKind([NSDate date], [NSDate class]) );
}


#pragma mark iter (iter)
static void test_iter_iter() {
    ass  ( !iter(nil) );
    asseq( emptylist(), iter(emptylist()) );
    asseq( list(foo, bar, baz), iter(list(foo, bar, baz)) );
    asseq( list(baz, bar, foo), iter([list(foo, bar, baz) reverseObjectEnumerator]) );
}


#pragma mark last (iter)
static void test_last_iter() {
    ass  ( !last(nil) );
    ass  ( !last(emptylist()) );
    asseq( bar, last(list(bar)) );
    asseq( baz, last(list(foo, bar, baz)) );
}


#pragma mark map (iter)
static void test_map_iter() {
    ass  ( !map(nil, muttoupper) );
    asseq( list(@"FOO", @"BAR", @"WOBBLE"),
        map(list(@"foo", @"bar", @"wobble"), muttoupper) );
}


#pragma mark nest (iter)
static void test_nest_iter() {
  Mapping appends = ^ id (id x) { return [x stringByAppendingString: @"a"]; };

  // uncomment next line to throw exception
  // ass( nest(@"a", appends,  -1) );

  ass( !nest(nil, 0, appends) );
  ass( !nest(@"a", 0, nil) );
  
  asseq( @"", nest(@"", 0, appends));
  asseq( @"aaa", nest(@"", 3, appends));
}


#pragma mark objectAt (iter)
static void test_objectAt_iter() {
    ass  ( !objectAt(nil, 0) );
    ass  ( !objectAt(nil, 1) );
    ass  ( !objectAt(nil, -1) );
    
    asseq(foo, objectAt(list(foo), 0) );
    ass  ( !objectAt(list(foo), 1) );
    ass  ( !objectAt(list(foo), -1) );
    
    asseq(foo, objectAt(list(foo, bar, baz), 0) );
    asseq(bar, objectAt(list(foo, bar, baz), 1) );
    asseq(baz, objectAt(list(foo, bar, baz), 2) );
    ass  ( !objectAt(list(foo, bar, baz), -2) );
    ass  ( !objectAt(list(foo, bar, baz), -1) );
}


#pragma mark performSel (object)
static void test_performSel_object() {
    // TODO: Add tests to me!
}


#pragma mark randint (random)
static void test_randint_random() {
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


#pragma mark reap (iter)
static void test_reap_iter() {
    asseq( list(@"a", @"b", @"c"), reap(^void (Mapping sow) {
        sow(@"a"); sow(@"b"); sow(@"c");
    }) );
}


#pragma mark replicate (iter)
static void test_replicate_iter() {
    ass  ( !replicate(nil, 0) );
    ass  ( !replicate(nil, 10) );
    asseq( emptylist(), replicate(foo, 0) );
    asseq( list(foo), replicate(foo, 1) );
    asseq( list(foo, foo), replicate(foo, 2) );
    asseq( list(foo, foo, foo), replicate(foo, 3) );
}


#pragma mark responds (object)
static void test_responds_object() {
    ass( responds(foo, @selector(characterAtIndex:)) );
    ass( responds(bar, @selector(isEqualToNumber:)) );
    ass( responds(baz, @selector(objectAtIndex:)) );
}


#pragma mark reverse (iter)
static void test_reverse_iter() {
    ass  ( !reverse(nil) );
    asseq(emptylist(), reverse(emptylist()) );
    asseq(list(foo), reverse(list(foo)) );
    asseq(list(bar, foo), reverse(list(foo, bar)) );
    asseq(list(baz, bar, foo), reverse(list(foo, bar, baz)) );
}


#pragma mark split (iter)
static void test_split_iter() {
    ass  (! split(nil, foo) );
    asseq(emptylist(), split(emptylist(), foo) );
    asseq(list(list(@"a")), split(list(@"a"), foo) );
    asseq(list(list(@"a", @"b")), split(list(@"a", @"b"), foo) );
    asseq(list(list(@"a", @"b"), emptylist()), split(list(@"a", @"b", foo), foo) );
    asseq(list(emptylist(), list(@"a", @"b")), split(list(foo, @"a", @"b"), foo) );
    asseq(list(emptylist(), list(@"a", @"b"), emptylist()), split(list(foo, @"a", @"b", foo), foo) );
    asseq(list(list(@"a", @"b"), list(@"c", @"d", @"e")), split(list(@"a", @"b", foo, @"c", @"d", @"e"), foo) );
    asseq(
        list(
            emptylist(), 
            list(@"a", @"b"), 
            emptylist(),
            emptylist(),
            list(@"c", @"d", @"e") ),
        split(list(foo, @"a", @"b", foo, foo, foo, @"c", @"d", @"e"), foo) );
}


#pragma mark tail (iter)
static void test_tail_iter() {
    ass  ( !tail(nil) );
    asseq(emptylist(), tail(emptylist()) );
    asseq(emptylist(), tail(list(foo)) );
    asseq(list(bar), tail(list(foo, bar)) );
    asseq(list(bar, baz), tail(list(foo, bar, baz)) );
}


#pragma mark take (iter)
static void test_take_iter() {
    ass  ( !take(nil, 0) );
    ass  ( !take(nil, 1) );
    ass  ( !take(nil, 10) );
    
    asseq( emptylist(), take(emptylist(),           0) );
    asseq( emptylist(), take(list(foo),             0) );
    asseq( emptylist(), take(list(foo, bar),        0) );
    asseq( emptylist(), take(list(foo, bar, baz),   0) );

    asseq( emptylist(), take(emptylist(),  2) );
    asseq( emptylist(), take(emptylist(),  3) );
    asseq( emptylist(), take(emptylist(), 10) );
    
    asseq( list(foo),           take(list(foo),           1) );
    asseq( list(foo, bar),      take(list(foo, bar),      2) );
    asseq( list(foo, bar, baz), take(list(foo, bar, baz), 3) );
    
    asseq( list(foo),           take(list(foo, bar, baz), 1) );
    asseq( list(foo, bar),      take(list(foo, bar, baz), 2) );
    asseq( list(foo, bar, baz), take(list(foo, bar, baz), 3) );
    asseq( list(foo, bar, baz), take(list(foo, bar, baz), 4) );
}


#pragma mark transpose (iter)
static void test_transpose_iter() {
  ass( !transpose(nil) );
  
  asseq( emptylist(), transpose(emptylist()) );
  
  asseq( list(list(@"a")), transpose(list(list(@"a"))) );
  
  asseq(
    list(list(@"b",@"b")),
    transpose(list(list(@"b"),list(@"b"))) );
  
  asseq(
    list(list(@"a",@"a"), list(@"b",@"b"), list(@"c",@"c")),
    transpose(list(list(@"a",@"b",@"c"), list(@"a",@"b",@"c"))) );
  
  asseq(
    list(list(@"a", @"a", @"a"),
         list(@"b", @"b", @"b"),
         list(@"c", @"c")),
    transpose(list(list(@"a",@"b",@"c"),
                   list(@"a",@"b"),
                   list(@"a",@"b",@"c"))) );
}


#pragma mark truthy (bool)
static void test_truthy_bool() {
    // This hardly needs testing, does it?
}


#pragma mark uniqued (iter)
static void test_uniqued_iter() {
    ass  ( !uniqued(nil) );
    asseq( emptylist(), uniqued(emptylist()) );
    asseq( list(foo, bar, baz), uniqued(list(foo, bar, baz)) );
    
    NSString* foo2 = [foo mutableCopy];
    NSString* foo3 = [foo mutableCopy];
    NSString* foo4 = [foo mutableCopy];
    
    asseq( list(foo), uniqued(list(foo, foo2, foo3, foo4)) );
    asseq( list(bar, foo), uniqued(list(bar, foo, foo2, foo3, foo4)) );
}


#pragma mark until (iter)
static void test_until_iter() {
    Predicate odd = ^BOOL(NSNumber* n) {
        return [n integerValue] % 2 == 1;
    };
    Mapping divideby2 = ^NSNumber*(NSNumber* n) {
        return [NSNumber numberWithInteger:[n integerValue] / 2];
    };
    
    asseq([NSNumber numberWithInteger:25], until(odd, divideby2, [NSNumber numberWithInteger:400]));
}


#pragma mark zipWith (iter)
static void test_zipWith_iter() {
    BinaryMapping plussing = ^id(id x, id y) { return list(x,y); };
    
    ass( !zipWith(emptylist(), nil, plussing) );
    ass( !zipWith(nil, emptylist(), plussing) );
    
    asseq( emptylist(), zipWith(emptylist(), emptylist(), plussing) );
    
    asseq(
      list(list(@"a",@"a")),
      zipWith(list(@"a"), list(@"a"), plussing) );

    asseq(
      list(list(@"a",@"c"), list(@"b",@"d")),
      zipWith(list(@"a",@"b"), list(@"c",@"d"), plussing) );

    asseq(
      list(list(@"a",@"d"), list(@"b",@"e")),
      zipWith(list(@"a",@"b",@"c"), list(@"d",@"e"), plussing) );

    asseq(
      list(list(@"a",@"d"), list(@"b",@"e"), list(@"c",@"f")),
      zipWith(list(@"a",@"b",@"c"), list(@"d",@"e",@"f"), plussing) );
}


#pragma mark main
int main(void) {
  @autoreleasepool {
    test_all_iter();
    test_any_iter();
    test_applyIf_func();
    test_byBinarySel_func();
    test_byCompose_func();
    test_byConst_func();
    test_byFlip_func();
    test_byFunction_func();
    test_byIdentity_func();
    test_compact_iter();
    test_concat_iter();
    test_concatMap_iter();
    test_contains_iter();
    test_count_iter();
    test_drop_iter();
    test_falsy_bool();
    test_filter_iter();
    test_first_iter();
    test_flatten_iter();
    test_foldl_fold();
    test_foldl1_fold();
    test_initial_iter();
    test_intersperse_iter();
    test_isKind_object();
    test_iter_iter();
    test_last_iter();
    test_map_iter();
    test_nest_iter();
    test_objectAt_iter();
    test_performSel_object();
    test_randint_random();
    test_reap_iter();
    test_replicate_iter();
    test_responds_object();
    test_reverse_iter();
    test_split_iter();
    test_tail_iter();
    test_take_iter();
    test_transpose_iter();
    test_truthy_bool();
    test_uniqued_iter();
    test_until_iter();
    test_zipWith_iter();
  }
  int failed = mutton_failed_assertion_count;
  int allassertions = mutton_all_assertion_count;
  printf("\n\nFailed %d of %d assertions (%d%% passed)\n", failed, allassertions, 100 - (int)round((((double)failed) / ((double)allassertions)) * 100));
  
  return failed != 0;
}
