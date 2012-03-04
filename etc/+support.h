#ifndef MUTTON_SUPPORT
#define MUTTON_SUPPORT
#define test static void mutton_private_test_(void)
#define foo @"foo"
#define bar [NSNumber numberWithInteger:42]
#define baz [NSArray arrayWithObjects:foo, bar, nil]
#define muttoupper ^ id (id x) { return [x uppercaseString]; };

#define yield_start NSMutableArray* mutton_yield_v_ = [NSMutableArray array]
#define yield_stop return mutton_yield_v_
#define yield_from(v_) [mutton_yield_v_ addObjectsFromArray(v_)]
#define yield(v_) [mutton_yield_v_ addObject:(v_)]

// Nothing personal. 
#define ass(c_) NSAssert(!!(c), @"")
#define asseq(a_, b_) NSAssert(!!(a) && !!(b) && [(a) isEqual:(b)], @"")
#endif