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

#define emptylist() [NSArray array]
#define list(...) [NSArray arrayWithObjects:__VA_ARGS__, nil]

// Nothing personal. 
#define ass(c_) { if (!(c_)) { printf("ASSERTION FAILURE %d\t%s\n  %s", __LINE__, __FILE__, #c_); } }
#define asseq(a_, b_) { if (!(a_) || !(b_) || ![(a_) isEqual:(b_)]) { printf("ASSERTION FAILURE %d\t%s\n  %s is not equal to %s", __LINE__, __FILE__, #a_, #b_); } }
#endif