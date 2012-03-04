#import "+type.h"

static Mapping byKey(NSString* k) {
    return [^ id (id obj) {
        if (responds(obj, @selector(objectForKey:)))
            [obj objectForKey:k];
        else
            [obj valueForKey:k];
    } copy];
}

static Mapping bySel(SEL sel) {
    return [^ id (id obj) {
        return [obj performSelector:sel];
    } copy];
}

static BinaryMapping binaryBySel(SEL sel) {
    return [^ id (id x, id y) {
        return [x performSelector:sel withObject:y];
    } copy];
}
// useful: binaryBySel(isEqual:), binaryBySel(@selector(stringByAppendingString:), etc
// useful in conjuction with fold

static Mapping bySelArg(SEL sel, id arg) {
    return [^ id (id obj) {
        return [obj performSelector:sel withObject:arg];
    } copy];
}

static Predicate byNot(Predicate p) {
    return [^ BOOL (id obj) {
        return !p(obj);
    } copy];
}

static Mapping byConst(id obj) {
    return [^ id (id x) {
        return obj;
    }];
}

static Mapping identity() {
    return [^ id (id x) {
        return x;
    }];
}
BinaryMapping exchange(BinaryMapping f) {
    return ^ id (id x, id y) {
        return f(y, x);
    };
}

// (.).(.) :: (b -> c) -> (a -> a1 -> b) -> a -> a1 -> c
static BinaryMapping boobs(Mapping f, BinaryMapping g) {
    return [^ id (id a, id b) {
        return f(g(a, b));
    } copy];
}


