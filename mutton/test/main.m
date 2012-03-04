#import "mutton.h"
#include "+support.h"


#pragma mark count (iter)
static void test_count_iter() {
    ass  ( !count(nil) );
    ass  ( !count(emptylist()) );
    ass  ( 1 == count(list(foo)) );
    ass  ( 2 == count(list(foo, bar)) );
    ass  ( 3 == count(list(foo, bar, baz)) );
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


#pragma mark initial (iter)
static void test_initial_iter() {
    ass  ( !initial(nil) );
    asseq(emptylist(), initial(emptylist()) );
    asseq(emptylist(), initial(list(foo)) );
    asseq(list(foo), initial(list(foo, bar)) );
    asseq(list(foo, bar), initial(list(foo, bar, baz)) );
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


#pragma mark tail (iter)
static void test_tail_iter() {
    ass  ( !tail(nil) );
    asseq(emptylist(), tail(emptylist()) );
    asseq(emptylist(), tail(list(foo)) );
    asseq(list(bar), tail(list(foo, bar)) );
    asseq(list(bar, baz), tail(list(foo, bar, baz)) );
}


#pragma mark main
int main(void) {
  @autoreleasepool {
    test_count_iter();
    test_filter_iter();
    test_first_iter();
    test_initial_iter();
    test_isKind_object();
    test_iter_iter();
    test_last_iter();
    test_map_iter();
    test_objectAt_iter();
    test_responds_object();
    test_reverse_iter();
    test_tail_iter();
  }
  int failed = mutton_failed_assertion_count;
  int allassertions = mutton_all_assertion_count;
  printf("\n\nFailed %d of %d assertions (%d%% passed)\n", failed, allassertions, 100 - (int)round((((double)failed) / ((double)allassertions)) * 100));
  
  return failed != 0;
}
