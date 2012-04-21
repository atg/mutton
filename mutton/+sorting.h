#import "+type.h"

#import <Foundation/Foundation.h>
#include "+support.h"

/// Returns a comparator that orders objects by their pointer addresses
// (in sorting)
static NSComparator compareAddress() {
    return [^ NSComparisonResult (id a, id b) {
        if (a < b)
            return NSOrderedAscending;
        if (a == b)
            return NSOrderedSame;
        return NSOrderedDescending;
    } copy];
}
/// Returns a comparator that calls compare: on the objects given to it.
// (in sorting)
static NSComparator compareDefault() {
    return [^ NSComparisonResult (id a, id b) {
        return [a compare:b];
    } copy];
}

/// Returns a comparator that compares by two comparators in turn
// (in sorting)
// (after compareDefault)
static NSComparator compareBoth(NSComparator cmp1, NSComparator cmp2) {
    cmp1 = (NSComparator)[cmp1 copy] ?: compareDefault();
    cmp2 = (NSComparator)[cmp2 copy] ?: compareDefault();
    
    return [^ NSComparisonResult (id a, id b) {
        return cmp1(a, b) ?: cmp2(a, b);
    } copy];
}

/// Returns a comparator that reverses the result of the given comparator.
// (in sorting)
// (after compareDefault)
static NSComparator compareReverse(NSComparator cmp) {
    cmp = (NSComparator)[cmp copy] ?: compareDefault();
    
    return [^ NSComparisonResult (id a, id b) {
        return - cmp(a, b);
    } copy];
}

/// Returns a comparator that compares using a selector, such as compare:, caseInsensitiveCompare:, localizedStandardCompare:, etc.
// (in sorting)
static NSComparator compareSelector(SEL sel) {
    sel = sel ?: @selector(compare:);
    
    return [^ NSComparisonResult (id a, id b) {
        return (NSComparisonResult)[a performSelector:sel withObject:b];
    } copy];
}

/// Returns a comparator that applies a mapping on each object before comparing them.
// (in sorting)
// (after compareDefault)
static NSComparator compareThrough(Mapping f, NSComparator cmp) {
    f = [f copy];
    cmp = (NSComparator)[cmp copy] ?: compareDefault();
    
    return [^ NSComparisonResult (id a, id b) {
        return cmp(f(a), f(b));
    } copy];
}

/// Sort an iterable using a comparator
// (in sorting)
// (after compareDefault)
static NSArray* sortBy(Iter it, NSComparator cmp) {
    if (!it)
        return nil;
    if (cmp == NULL)
        cmp = compareDefault();
    
    NSArray* jt = iter(it);
    
    // Easy peasy
    return [jt sortedArrayWithOptions:NSSortStable usingComparator:cmp];
}

/// Stably sorts an iterable, using compare:
// (in sorting)
// (after sortBy)
static NSArray* sort(Iter it) {
    return sortBy(it, NULL);
}

#include "+unsupport.h"
