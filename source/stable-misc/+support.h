#ifndef MUTTON_SUPPORT
#define MUTTON_SUPPORT

#import <objc/message.h>

#define test static void mutton_private_test_(void)
#define foo @"foo"
#define bar [NSNumber numberWithInteger:42]
#define baz [NSArray arrayWithObjects:foo, bar, nil]
#define muttoupper (^ id (id x) { return [x uppercaseString]; })

#define yield_start NSMutableArray* mutton_yield_v_ = [NSMutableArray array]
#define yield_stop return mutton_yield_v_
#define yield_from(v_) [mutton_yield_v_ addObjectsFromArray:(v_)]
#define yield(v_) [mutton_yield_v_ addObject:(v_)]

#define emptylist() [NSArray array]
#define list(...) [NSArray arrayWithObjects:__VA_ARGS__, nil]

// Nothing personal.
#define ass(c_) { mutton_all_assertion_count++; if (!(c_)) { mutton_failed_assertion_count++; NSLog(@"ASSERTION FAILURE %d\t%s\n  %s\n", __LINE__, __FILE__, #c_); } }
#define asseq(a_, b_) { mutton_all_assertion_count++; if (!(a_) || !(b_) || ![(a_) isEqual:(b_)]) { mutton_failed_assertion_count++; NSLog(@"ASSERTION FAILURE %d\t%s\n  %s is not equal to %s\na = %@\nb = %@\n", __LINE__, __FILE__, #a_, #b_, a_, b_); } }

#ifndef MUTTON_EVER_SUPPORT
#define MUTTON_EVER_SUPPORT
static int mutton_failed_assertion_count;
static int mutton_all_assertion_count;
#endif
#endif