#import "mutton.h"
#include "+support.h"


#pragma mark count (iter)
static void test_count_iter() {
    ass  ( !count(nil) );
    ass  ( !count(@[]) );
    ass  ( 1 == count(@[foo]) );
    ass  ( 2 == count(@[foo, bar]) );
    ass  ( 3 == count(@[foo, bar, baz]) );
}


#pragma mark first (iter)
static void test_first_iter() {
    ass  ( !first(nil) );
    ass  ( !first(@[]) );
    asseq( bar, first(@[bar]) );
    asseq( foo, first(@[foo, bar, baz]) );
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


#pragma mark last (iter)
static void test_last_iter() {
    ass  ( !last(nil) );
    ass  ( !last(@[]) );
    asseq( bar, last(@[bar]) );
    asseq( baz, last(@[foo, bar, baz]) );
}


#pragma mark map (iter)
static void test_map_iter() {
    ass  ( !map(nil, muttoupper) );
    asseq( @[@"FOO", @"BAR", @"WOBBLE"],
        map(@[@"foo", @"bar", @"wobble"], muttoupper) );
}


#pragma mark objectAt (iter)
static void test_objectAt_iter() {
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
}


#pragma mark responds (object)
static void test_responds_object() {
    ass( responds(foo, @selector(characterAtIndex:)) );
    ass( responds(bar, @selector(isEqualToNumber:)) );
    ass( responds(baz, @selector(objectAtIndex:)) );
}


#pragma mark main
int main(void) {
    test_count_iter();
    test_first_iter();
    test_isKind_object();
    test_last_iter();
    test_map_iter();
    test_objectAt_iter();
    test_responds_object();
}
