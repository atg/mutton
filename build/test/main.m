#import "mutton.h"
#include "+support.h"


#pragma mark map (iter)
static void test_map_iter() {
    ass  ( !map(nil, muttoupper) );
    asseq( @[@"FOO", @"BAR", @"WOBBLE"],
        map(@[@"foo", @"bar", @"wobble"], muttoupper) );
}


#pragma mark main
int main(void) {
    test_map_iter();
}
