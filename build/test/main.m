#import "mutton.h"
#include "+support.h"


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


#pragma mark map (iter)
static void test_map_iter() {
    ass  ( !map(nil, muttoupper) );
    asseq( @[@"FOO", @"BAR", @"WOBBLE"],
        map(@[@"foo", @"bar", @"wobble"], muttoupper) );
}


#pragma mark responds (object)
static void test_responds_object() {
    ass( responds(foo, @selector(characterAtIndex:)) );
    ass( responds(bar, @selector(isEqualToNumber:)) );
    ass( responds(baz, @selector(objectAtIndex:)) );
}


#pragma mark main
int main(void) {
    test_isKind_object();
    test_map_iter();
    test_responds_object();
}
