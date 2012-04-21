var alldocs = {"sorting": [{"definition": "/// Returns a comparator that orders objects by their pointer addresses\n// (in sorting)\nstatic NSComparator compareAddress() {\n    return [^ NSComparisonResult (id a, id b) {\n        if (a < b)\n            return NSOrderedAscending;\n        if (a == b)\n            return NSOrderedSame;\n        return NSOrderedDescending;\n    } copy];\n}\n", "dependencies": ["+type.h"], "name": "compareAddress", "normal": true, "typesig": "(<strong></strong>) <span class=\"arr\">&rarr;</span> <strong>NSComparator</strong>", "afters": [], "module": "sorting", "description": "Returns a comparator that orders objects by their pointer addresses"}, {"definition": "/// Returns a comparator that calls compare: on the objects given to it.\n// (in sorting)\nstatic NSComparator compareDefault() {\n    return [^ NSComparisonResult (id a, id b) {\n        return [a compare:b];\n    } copy];\n}\n\n", "dependencies": ["+type.h"], "name": "compareDefault", "normal": true, "typesig": "(<strong></strong>) <span class=\"arr\">&rarr;</span> <strong>NSComparator</strong>", "afters": [], "module": "sorting", "description": "Returns a comparator that calls compare: on the objects given to it."}, {"definition": "/// Returns a comparator that compares by two comparators in turn\n// (in sorting)\n// (after compareDefault)\nstatic NSComparator compareBoth(NSComparator cmp1, NSComparator cmp2) {\n    cmp1 = (NSComparator)[cmp1 copy] ?: compareDefault();\n    cmp2 = (NSComparator)[cmp2 copy] ?: compareDefault();\n    \n    return [^ NSComparisonResult (id a, id b) {\n        return cmp1(a, b) ?: cmp2(a, b);\n    } copy];\n}\n\n", "dependencies": ["+type.h"], "name": "compareBoth", "normal": true, "typesig": "(<strong>NSComparator cmp1</strong>, <strong>NSComparator cmp2</strong>) <span class=\"arr\">&rarr;</span> <strong>NSComparator</strong>", "afters": ["compareDefault"], "module": "sorting", "description": "Returns a comparator that compares by two comparators in turn"}, {"definition": "/// Returns a comparator that reverses the result of the given comparator.\n// (in sorting)\n// (after compareDefault)\nstatic NSComparator compareReverse(NSComparator cmp) {\n    cmp = (NSComparator)[cmp copy] ?: compareDefault();\n    \n    return [^ NSComparisonResult (id a, id b) {\n        return - cmp(a, b);\n    } copy];\n}\n\n", "dependencies": ["+type.h"], "name": "compareReverse", "normal": true, "typesig": "(<strong>NSComparator cmp</strong>) <span class=\"arr\">&rarr;</span> <strong>NSComparator</strong>", "afters": ["compareDefault"], "module": "sorting", "description": "Returns a comparator that reverses the result of the given comparator."}, {"definition": "/// Returns a comparator that compares using a selector, such as compare:, caseInsensitiveCompare:, localizedStandardCompare:, etc.\n// (in sorting)\nstatic NSComparator compareSelector(SEL sel) {\n    sel = sel ?: @selector(compare:);\n    \n    return [^ NSComparisonResult (id a, id b) {\n        return (NSComparisonResult)[a performSelector:sel withObject:b];\n    } copy];\n}\n\n", "dependencies": ["+type.h"], "name": "compareSelector", "normal": true, "typesig": "(<strong>SEL sel</strong>) <span class=\"arr\">&rarr;</span> <strong>NSComparator</strong>", "afters": [], "module": "sorting", "description": "Returns a comparator that compares using a selector, such as compare:, caseInsensitiveCompare:, localizedStandardCompare:, etc."}, {"definition": "/// Returns a comparator that applies a mapping on each object before comparing them.\n// (in sorting)\n// (after compareDefault)\nstatic NSComparator compareThrough(Mapping f, NSComparator cmp) {\n    f = [f copy];\n    cmp = (NSComparator)[cmp copy] ?: compareDefault();\n    \n    return [^ NSComparisonResult (id a, id b) {\n        return cmp(f(a), f(b));\n    } copy];\n}\n\n", "dependencies": ["+type.h"], "name": "compareThrough", "normal": true, "typesig": "(<strong>Mapping f</strong>, <strong>NSComparator cmp</strong>) <span class=\"arr\">&rarr;</span> <strong>NSComparator</strong>", "afters": ["compareDefault"], "module": "sorting", "description": "Returns a comparator that applies a mapping on each object before comparing them."}, {"definition": "/// Sort an iterable using a comparator\n// (in sorting)\n// (after compareDefault)\nstatic NSArray* sortBy(Iter it, NSComparator cmp) {\n    if (!it)\n        return nil;\n    if (cmp == NULL)\n        cmp = compareDefault();\n    \n    NSArray* jt = iter(it);\n    \n    // Easy peasy\n    return [jt sortedArrayWithOptions:NSSortStable usingComparator:cmp];\n}\n\n", "dependencies": ["+type.h"], "name": "sortBy", "normal": true, "typesig": "(<strong>Iter it</strong>, <strong>NSComparator cmp</strong>) <span class=\"arr\">&rarr;</span> <strong>NSArray*</strong>", "afters": ["compareDefault"], "module": "sorting", "description": "Sort an iterable using a comparator"}, {"definition": "/// Stably sorts an iterable, using compare:\n// (in sorting)\n// (after sortBy)\nstatic NSArray* sort(Iter it) {\n    return sortBy(it, NULL);\n}\n\n", "dependencies": ["+type.h"], "name": "sort", "normal": true, "typesig": "(<strong>Iter it</strong>) <span class=\"arr\">&rarr;</span> <strong>NSArray*</strong>", "afters": ["sortBy"], "module": "sorting", "description": "Stably sorts an iterable, using compare:"}], "object": [{"definition": "/// Determines if two (possibly nil) objects are equal. This differs from -isEqual: because it considers the case where both objects are nil\n// (in object)\nstatic BOOL equals(id a, id b) {\n    return a == b || [a isEqual:b];\n}\n\n", "dependencies": ["+type.h"], "name": "equals", "normal": true, "typesig": "(<strong>id a</strong>, <strong>id b</strong>) <span class=\"arr\">&rarr;</span> <strong>BOOL</strong>", "afters": [], "module": "object", "description": "Determines if two (possibly nil) objects are equal. This differs from -isEqual: because it considers the case where both objects are nil"}, {"definition": "/// Wraps isKindOfClass. Accepts a string as the class argument.\n// (in object)\nstatic BOOL isKind(id obj, id class_or_classname) {\n\n    Class c = Nil;\n    if ([class_or_classname class] == class_or_classname)\n        c = class_or_classname;\n    else\n        c = NSClassFromString(class_or_classname);\n\n    if (!c)\n        return NO;\n    return [obj isKindOfClass:c];\n}\n\n", "dependencies": [], "name": "isKind", "normal": true, "typesig": "(<strong>id obj</strong>, <strong>id class_or_classname</strong>) <span class=\"arr\">&rarr;</span> <strong>BOOL</strong>", "afters": [], "module": "object", "description": "Wraps isKindOfClass. Accepts a string as the class argument."}, {"definition": "/// Same as performSelector:withObject:, but inhibits a warning under ARC (so make sure that the method returns an autoreleased value).\n// (in object)\nstatic id performSel(id obj, SEL sel, id arg) {\n    #pragma clang diagnostic push\n    #pragma clang diagnostic ignored \"-Warc-performSelector-leaks\"\n    return [obj performSelector:sel withObject:arg];\n    #pragma clang diagnostic pop\n}\n\n", "dependencies": ["+type.h"], "name": "performSel", "normal": true, "typesig": "(<strong>id obj</strong>, <strong>SEL sel</strong>, <strong>id arg</strong>) <span class=\"arr\">&rarr;</span> <strong>id</strong>", "afters": [], "module": "object", "description": "Same as performSelector:withObject:, but inhibits a warning under ARC (so make sure that the method returns an autoreleased value)."}, {"definition": "/// Wraps -respondsToSelector\n// (in object)\nstatic BOOL responds(id obj, SEL sel) {\n    return [obj respondsToSelector:sel];\n}\n\n", "dependencies": [], "name": "responds", "normal": true, "typesig": "(<strong>id obj</strong>, <strong>SEL sel</strong>) <span class=\"arr\">&rarr;</span> <strong>BOOL</strong>", "afters": [], "module": "object", "description": "Wraps -respondsToSelector"}], "iter": [{"definition": "/// Returns true if all \n// (in iter)\nstatic BOOL all(Iter it, Predicate p) {\n    if (!it)\n      return NO;\n    \n    for (id x in it) {\n      if (!p(x))\n        return NO;\n    }\n    \n    return YES;\n}\n\n", "dependencies": ["+type.h"], "name": "all", "normal": true, "typesig": "(<strong>Iter it</strong>, <strong>Predicate p</strong>) <span class=\"arr\">&rarr;</span> <strong>BOOL</strong>", "afters": [], "module": "iter", "description": "Returns true if all "}, {"definition": "/// Returns true if the predicate validates to any of the elements, false otherwise.\n// (in iter)\nstatic BOOL any(Iter it, Predicate p) {\n    if (!it)\n      return NO;\n    \n    for (id x in it) {\n      if (p(x))\n        return YES;\n    }\n    \n    return NO;\n}\n\n", "dependencies": ["+type.h"], "name": "any", "normal": true, "typesig": "(<strong>Iter it</strong>, <strong>Predicate p</strong>) <span class=\"arr\">&rarr;</span> <strong>BOOL</strong>", "afters": [], "module": "iter", "description": "Returns true if the predicate validates to any of the elements, false otherwise."}, {"definition": "/// Keep only the elements of a list for with the predicate is true.\n// (in iter)\nstatic NSArray* filter(Iter it, Predicate p) {\n    if (!it)\n        return nil;\n    yield_start;\n    for (id x in it) {\n        if (p(x))\n            yield(x);\n    }\n    yield_stop;\n}\n\n", "dependencies": ["+type.h"], "name": "filter", "normal": true, "typesig": "(<strong>Iter it</strong>, <strong>Predicate p</strong>) <span class=\"arr\">&rarr;</span> <strong>NSArray*</strong>", "afters": [], "module": "iter", "description": "Keep only the elements of a list for with the predicate is true."}, {"definition": "/// Glue together an array of arrays (or iterable of iterables) to make one big array.\n// (in iter)\nstatic NSArray* concat(Iter it) {\n    if (!it)\n        return nil;\n    \n    yield_start;\n    for (Iter j in it) {\n        if ([j isKindOfClass:[NSArray class]]) {\n            yield_from((NSArray*)j);\n        }\n        else {\n            for (id x in j) {\n                yield(x);\n            }\n        }\n    }\n    yield_stop;\n}\n\n", "dependencies": ["+type.h"], "name": "concat", "normal": true, "typesig": "(<strong>Iter it</strong>) <span class=\"arr\">&rarr;</span> <strong>NSArray*</strong>", "afters": [], "module": "iter", "description": "Glue together an array of arrays (or iterable of iterables) to make one big array."}, {"definition": "/// map(xs, f) is the list obtained by applying f to each element of xs\n// (in iter)\nstatic NSArray* map(Iter it, Mapping f) {\n    if (!it)\n        return nil;\n    yield_start;\n    for (id x in it) {\n        id y = f(x);\n        if (y)\n            yield(y);\n    } \n    yield_stop;\n}\n\n", "dependencies": ["+type.h"], "name": "map", "normal": true, "typesig": "(<strong>Iter it</strong>, <strong>Mapping f</strong>) <span class=\"arr\">&rarr;</span> <strong>NSArray*</strong>", "afters": [], "module": "iter", "description": "map(xs, f) is the list obtained by applying f to each element of xs"}, {"definition": "/// Tells if the array contains the object.\n// (in iter)\nstatic BOOL contains(Iter it, id x) {\n  return any(it, ^ BOOL (id y) { return [y isEqual:x]; });\n}\n\n", "dependencies": ["+type.h"], "name": "contains", "normal": true, "typesig": "(<strong>Iter it</strong>, <strong>id x</strong>) <span class=\"arr\">&rarr;</span> <strong>BOOL</strong>", "afters": [], "module": "iter", "description": "Tells if the array contains the object."}, {"definition": "/// Find the number of objects in an array or iterable.\n// (in iter)\nstatic long count(Iter it) {\n    if (responds(it, @selector(count)))\n        return [(NSArray*)it count];\n\n    long i = 0;\n    for (id x in it) {\n        i++;\n    }\n    return i;\n}\n\n", "dependencies": ["+type.h", "+object.h"], "name": "count", "normal": true, "typesig": "(<strong>Iter it</strong>) <span class=\"arr\">&rarr;</span> <strong>long</strong>", "afters": [], "module": "iter", "description": "Find the number of objects in an array or iterable."}, {"definition": "/// Removes the given number of objects from the front of the list.\n// (in iter)\nstatic NSArray* drop(Iter it, long n) {\n    if (n < 0)\n        [NSException raise:NSInvalidArgumentException format:@\"drop(%@, %ld) called with negative N\", it, n];\n    if (!it)\n        return nil;\n    \n    yield_start;\n    \n    long i = 0;\n    for (id x in it) {\n        if (i >= n)\n            yield(x);\n        else\n            i++;\n    }\n\n    yield_stop;\n}\n\n", "dependencies": ["+type.h"], "name": "drop", "normal": true, "typesig": "(<strong>Iter it</strong>, <strong>long n</strong>) <span class=\"arr\">&rarr;</span> <strong>NSArray*</strong>", "afters": [], "module": "iter", "description": "Removes the given number of objects from the front of the list."}, {"definition": "/// Removes falsy values from the array.\n// (in iter)\n// (after filter)\nstatic NSArray* compact(Iter it) {\n    return filter(it, ^ BOOL (id x) { return truthy(x); });\n}\n\n", "dependencies": ["+type.h"], "name": "compact", "normal": true, "typesig": "(<strong>Iter it</strong>) <span class=\"arr\">&rarr;</span> <strong>NSArray*</strong>", "afters": ["filter"], "module": "iter", "description": "Removes falsy values from the array."}, {"definition": "/// Find the first object of the iterable, or nil if it's empty.\n// (in iter)\nstatic id first(Iter it) {\n    for (id obj in it) {\n        return obj;\n    }\n    return nil;\n}\n\n", "dependencies": ["+type.h"], "name": "first", "normal": true, "typesig": "(<strong>Iter it</strong>) <span class=\"arr\">&rarr;</span> <strong>id</strong>", "afters": [], "module": "iter", "description": "Find the first object of the iterable, or nil if it's empty."}, {"definition": "/// Recursively flattens a tree of iterables into a single array.\n// (in iter)\nstatic NSArray* flatten(Iter it) {\n    if (!it)\n        return nil;\n    \n    yield_start;\n    \n    __block void(^_flatten)(id) = ^void(id y){\n        if (!y)\n            return;\n        for (id x in y) {\n            if ([x respondsToSelector:@selector(countByEnumeratingWithState:objects:count:)])\n                _flatten(x);\n            else\n                yield(x);\n        }\n    };\n    \n    _flatten(it);\n    \n    yield_stop;\n}\n\n", "dependencies": ["+type.h"], "name": "flatten", "normal": true, "typesig": "(<strong>Iter it</strong>) <span class=\"arr\">&rarr;</span> <strong>NSArray*</strong>", "afters": [], "module": "iter", "description": "Recursively flattens a tree of iterables into a single array."}, {"definition": "/// Groups similar objects using supplied predicate.\n// (in iter)\nstatic NSArray* groupBy(Iter it, BinaryPredicate eq) {\n  if (!it)\n    return nil;\n\n  yield_start;\n\n  for (id x in it) {\n\n    if (eq(x, [[mutton_yield_v_ lastObject] lastObject]))\n    {\n      [[mutton_yield_v_ lastObject] addObject:x];\n    } else {\n      yield([NSMutableArray arrayWithObject:x]);\n    }\n\n  }\n\n  yield_stop;\n}\n\n", "dependencies": ["+type.h"], "name": "groupBy", "normal": true, "typesig": "(<strong>Iter it</strong>, <strong>BinaryPredicate eq</strong>) <span class=\"arr\">&rarr;</span> <strong>NSArray*</strong>", "afters": [], "module": "iter", "description": "Groups similar objects using supplied predicate."}, {"definition": "/// Return all the elements of a list except the last one.\n// (in iter)\nstatic id initial(Iter it) {\n    if (!it)\n        return nil;\n\n    // TODO: Add a specialization for NSArray using subarrayWithRange:\n\n    // We don't know when the iterable ends, so we just have to add everything to an array, then remove the last object\n    yield_start;\n    for (id x in it) {\n        yield(x);\n    }\n\n    if ([mutton_yield_v_ count])\n        [mutton_yield_v_ removeLastObject];\n    yield_stop;\n}\n\n", "dependencies": ["+type.h"], "name": "initial", "normal": true, "typesig": "(<strong>Iter it</strong>) <span class=\"arr\">&rarr;</span> <strong>id</strong>", "afters": [], "module": "iter", "description": "Return all the elements of a list except the last one."}, {"definition": "/// A bit like componentsJoinedByString: but with general purpose iterables instead of strings.\n// (in iter)\nstatic NSArray* intersperse(Iter it, id glue) {\n    if (!it)\n        return nil;\n    \n    yield_start;\n    \n    for (id x in it) {\n        yield(x);\n        yield(glue);\n    }\n    \n    if ([mutton_yield_v_ count])\n        [mutton_yield_v_ removeLastObject];\n\n    yield_stop;\n}\n\n", "dependencies": [], "name": "intersperse", "normal": true, "typesig": "(<strong>Iter it</strong>, <strong>id glue</strong>) <span class=\"arr\">&rarr;</span> <strong>NSArray*</strong>", "afters": [], "module": "iter", "description": "A bit like componentsJoinedByString: but with general purpose iterables instead of strings."}, {"definition": "/// intercalate a b ==> concat $ intersperse a b\n// (in iter)\n// (after intersperse)\n// (after concat)\nstatic NSArray* intercalate(Iter a, Iter b) {\n    return concat(intersperse(a, b));\n}\n\n", "dependencies": ["+type.h"], "name": "intercalate", "normal": true, "typesig": "(<strong>Iter a</strong>, <strong>Iter b</strong>) <span class=\"arr\">&rarr;</span> <strong>NSArray*</strong>", "afters": ["intersperse", "concat"], "module": "iter", "description": "intercalate a b ==> concat $ intersperse a b"}, {"definition": "/// Convert a general purpose iterable to an NSArray*\n// (in iter)\nstatic NSArray* iter(Iter it) {\n    if (!it)\n        return nil;\n\n    if (isKind(it, [NSMutableArray class]))\n        return [(NSMutableArray*)it copy];\n\n    // If it's a non-mutable array, we're probably OK to not copy it\n    if (isKind(it, [NSArray class]))\n        return (NSArray*)it;\n\n    yield_start;\n    for (id x in it) {\n        yield(x);\n    }\n    yield_stop;\n}\n", "dependencies": ["+type.h", "+object.h"], "name": "iter", "normal": true, "typesig": "(<strong>Iter it</strong>) <span class=\"arr\">&rarr;</span> <strong>NSArray*</strong>", "afters": [], "module": "iter", "description": "Convert a general purpose iterable to an NSArray*"}, {"definition": "/// Find the last object of the iterable, or nil if it's empty.\n// (in iter)\nstatic id last(Iter it) {\n    if (responds(it, @selector(lastObject)))\n        return [(NSArray*)it lastObject];\n\n    id v = nil;\n    for (id x in it) {\n        v = x;\n    }\n    return v;\n}\n\n", "dependencies": ["+type.h", "+object.h"], "name": "last", "normal": true, "typesig": "(<strong>Iter it</strong>) <span class=\"arr\">&rarr;</span> <strong>id</strong>", "afters": [], "module": "iter", "description": "Find the last object of the iterable, or nil if it's empty."}, {"definition": "/// Map each element to a list of new elements (which may be empty), then glue the lists together. It's map, filter and a bit more on top.\n// (in iter)\n// (after concat)\n// (after map)\nstatic NSArray* concatMap(Iter it, Iter(^f)(id)) {\n    if (!it)\n        return nil;\n    return concat(map(it, f)); // Ahhhh the joys of functional programming at last\n}\n\n", "dependencies": ["+type.h"], "name": "concatMap", "normal": true, "typesig": "(<strong>Iter it</strong>, <strong>Iter(^f)(id)</strong>) <span class=\"arr\">&rarr;</span> <strong>NSArray*</strong>", "afters": ["map", "concat"], "module": "iter", "description": "Map each element to a list of new elements (which may be empty), then glue the lists together. It's map, filter and a bit more on top."}, {"definition": "/// Nests function calls such that nest(x, 3, f) ==> f(f(f(x)))\n// (in iter)\nstatic id nest(id x, long loops, Mapping f) {\n    if (!f)\n      return nil;\n    \n    if (loops < 0)\n      [NSException raise:@\"Negative nesting index\" format:@\"foo of %d is invalid\", loops];\n    \n    if (loops == 0)\n      return x;\n\n    return f( nest(x, loops-1, f) );\n}\n\n", "dependencies": ["+type.h"], "name": "nest", "normal": true, "typesig": "(<strong>id x</strong>, <strong>long loops</strong>, <strong>Mapping f</strong>) <span class=\"arr\">&rarr;</span> <strong>id</strong>", "afters": [], "module": "iter", "description": "Nests function calls such that nest(x, 3, f) ==> f(f(f(x)))"}, {"definition": "/// Like objectAtIndex: but works on general iterables, and returns nil if the index is out of bounds (instead of an exception).\n// (in iter)\nstatic id objectAt(Iter it, long n) {\n\n    if (!it)\n        return nil;\n    if (n < 0)\n        return nil;\n    \n    if (responds(it, @selector(count))) {\n        if (n >= [(NSArray*)it count])\n            return nil;\n        if (responds(it, @selector(objectAtIndex:))) {\n            return [(NSArray*)it objectAtIndex:n];\n        }\n    }\n\n    NSInteger i = 0;\n    for (id x in it) {\n        if (i == n)\n            return x;\n        i++;\n    }\n\n    return nil;\n}\n\n", "dependencies": ["+type.h", "+object.h"], "name": "objectAt", "normal": true, "typesig": "(<strong>Iter it</strong>, <strong>long n</strong>) <span class=\"arr\">&rarr;</span> <strong>id</strong>", "afters": [], "module": "iter", "description": "Like objectAtIndex: but works on general iterables, and returns nil if the index is out of bounds (instead of an exception)."}, {"definition": "/// Allows you to \"sow\" values, and \"reap\" them at the end. Pass a block to reap that takes a single Mapping argument (conventionally named \"sow\"). Do some work in this block, then call sow each time you want to save a value. Reap will run your block and return the values that you sowed.\n// (in iter)\nstatic NSArray* reap(void(^body)(Mapping sow)) {\n    yield_start;\n    Mapping sow = ^(id x){\n        if (x)\n            yield(x);\n        return x;\n    };\n\n    body(sow);\n    yield_stop;\n}\n\n", "dependencies": ["+type.h"], "name": "reap", "normal": true, "typesig": "(<strong>void(^body)(Mapping sow)</strong>) <span class=\"arr\">&rarr;</span> <strong>NSArray*</strong>", "afters": [], "module": "iter", "description": "Allows you to \"sow\" values, and \"reap\" them at the end. Pass a block to reap that takes a single Mapping argument (conventionally named \"sow\"). Do some work in this block, then call sow each time you want to save a value. Reap will run your block and return the values that you sowed."}, {"definition": "/// Build a list by repeating an element a given (non-negative) number of times.\n// (in iter)\nstatic NSArray* replicate(id v, long n) {\n    if (n < 0)\n        [NSException raise:NSInvalidArgumentException format:@\"replicate(%@, %ld) called with negative N\", v, n];\n    if (!v)\n        return nil;\n    \n    yield_start;\n    for (long i = 0; i < n; i++) {\n        yield(v);\n    }\n    yield_stop;\n}\n\n", "dependencies": ["+type.h"], "name": "replicate", "normal": true, "typesig": "(<strong>id v</strong>, <strong>long n</strong>) <span class=\"arr\">&rarr;</span> <strong>NSArray*</strong>", "afters": [], "module": "iter", "description": "Build a list by repeating an element a given (non-negative) number of times."}, {"definition": "/// Reverse an iterable.\n// (in iter)\n// (after iter)\nstatic id reverse(Iter it) {\n    if (!it)\n        return nil;\n\n    if (responds(it, @selector(reverseObjectEnumerator)))\n        return iter([(NSArray*)it reverseObjectEnumerator]);\n    else\n        return reverse(iter(it));\n}\n\n", "dependencies": ["+type.h", "+object.h"], "name": "reverse", "normal": true, "typesig": "(<strong>Iter it</strong>) <span class=\"arr\">&rarr;</span> <strong>id</strong>", "afters": ["iter"], "module": "iter", "description": "Reverse an iterable."}, {"definition": "/// A bit like componentsSeparatedByString: but with general purpose iterables instead of of strings\n// (in iter)\nstatic NSArray* split(Iter it, id token) {\n    if (!it)\n        return nil;\n    \n    BOOL isEmpty = YES;\n    \n    yield_start;\n    \n    NSMutableArray* temp = [[NSMutableArray alloc] init];\n    for (id x in it) {\n        isEmpty = NO;\n        if (x == token) {\n            yield(temp);\n            temp = [[NSMutableArray alloc] init];\n        } else {\n            [temp addObject:x];\n        }\n    }\n    \n    if (isEmpty)\n        return emptylist();\n    \n    yield(temp);\n    yield_stop;\n}\n\n", "dependencies": [], "name": "split", "normal": true, "typesig": "(<strong>Iter it</strong>, <strong>id token</strong>) <span class=\"arr\">&rarr;</span> <strong>NSArray*</strong>", "afters": [], "module": "iter", "description": "A bit like componentsSeparatedByString: but with general purpose iterables instead of of strings"}, {"definition": "/// Extract the elements after the head of a list.\n// (in iter)\nstatic id tail(Iter it) {\n    if (!it)\n        return nil;\n\n    // TODO: Add a specialization for NSArray using subarrayWithRange:\n\n    yield_start;\n    BOOL isFirst = YES;\n    for (id x in it) {\n        if (isFirst)\n            isFirst = NO;\n        else\n            yield(x);\n    } \n    yield_stop;\n}\n\n", "dependencies": ["+type.h"], "name": "tail", "normal": true, "typesig": "(<strong>Iter it</strong>) <span class=\"arr\">&rarr;</span> <strong>id</strong>", "afters": [], "module": "iter", "description": "Extract the elements after the head of a list."}, {"definition": "/// Returns the given number of objects from the front of the list.\n// (in iter)\nstatic NSArray* take(Iter it, long n) {\n    if (!it)\n        return nil;\n\n    yield_start;\n\n    long i = 0;\n    for (id x in it) {\n        if (i >= n)\n            break;\n        \n        yield(x);\n        i++;\n    }\n\n    yield_stop;\n}\n\n", "dependencies": ["+type.h"], "name": "take", "normal": true, "typesig": "(<strong>Iter it</strong>, <strong>long n</strong>) <span class=\"arr\">&rarr;</span> <strong>NSArray*</strong>", "afters": [], "module": "iter", "description": "Returns the given number of objects from the front of the list."}, {"definition": "/// Transposes the rows and columns of the matrix\n// (in iter)\nstatic NSArray* transpose(Iter it) {\n  if (!it)\n    return nil;\n  \n  NSMutableArray* normal = [[NSMutableArray alloc] init];\n  for (id x in it)\n    [normal addObject:[NSMutableArray arrayWithArray:x]];\n  \n  yield_start;\n  \n  for (long i = 0; i <= [normal count]; i++)\n  {\n    yield([NSMutableArray array]);\n    BOOL isEmpty = YES;\n\n    for (id x in normal)\n    {\n      if ([x count] == 0)\n        continue;\n      \n      isEmpty = NO;\n      \n      [[mutton_yield_v_ lastObject] addObject:[x objectAtIndex:0]];\n      [x removeObjectAtIndex:0];\n    }\n    \n    if (isEmpty)\n      [mutton_yield_v_ removeLastObject];\n  }\n  \n  yield_stop;\n}\n\n", "dependencies": ["+type.h"], "name": "transpose", "normal": true, "typesig": "(<strong>Iter it</strong>) <span class=\"arr\">&rarr;</span> <strong>NSArray*</strong>", "afters": [], "module": "iter", "description": "Transposes the rows and columns of the matrix"}, {"definition": "/// Remove duplicate objects, as determined by their -hash and isEqual: (i.e., the objects are inserted into an NSSet to determine equality). O(n).\n// (in iter)\nstatic NSArray* uniqued(Iter it) {\n    if (!it)\n        return nil;\n    \n    NSMutableSet* s = [NSMutableSet set];\n    yield_start;\n    for (id x in it) {\n        if (![s containsObject:x]) {\n            [s addObject:x];\n            yield(x);\n        }\n    }\n    yield_stop;\n}\n\n", "dependencies": ["+type.h"], "name": "uniqued", "normal": true, "typesig": "(<strong>Iter it</strong>) <span class=\"arr\">&rarr;</span> <strong>NSArray*</strong>", "afters": [], "module": "iter", "description": "Remove duplicate objects, as determined by their -hash and isEqual: (i.e., the objects are inserted into an NSSet to determine equality). O(n)."}, {"definition": "/// Applies a function over and over again to x until p(x) evaluates to true.\n// (in iter)\nstatic id until(Predicate p, Mapping f, id x) {\n    while (!p(x))\n        x = f(x);\n    return x;\n}\n\n", "dependencies": ["+type.h"], "name": "until", "normal": true, "typesig": "(<strong>Predicate p</strong>, <strong>Mapping f</strong>, <strong>id x</strong>) <span class=\"arr\">&rarr;</span> <strong>id</strong>", "afters": [], "module": "iter", "description": "Applies a function over and over again to x until p(x) evaluates to true."}, {"definition": "/// Zips both arrays using the BinaryMapping. That's what.\n// (in iter)\n// (after count)\n// (after objectAt)\nstatic NSArray* zipWith(Iter a, Iter b, BinaryMapping f) {\n    if (!a || !b)\n      return nil;\n\n    long tempa = count(a);\n    long tempb = count(b);\n    \n    long count = (tempa > tempb) ? tempb : tempa;\n    \n    yield_start;\n    \n    for (long i=0; i < count; ++i)\n    {\n      yield( f(objectAt(a, i), objectAt(b, i)) );\n    }\n    \n    yield_stop;\n}\n\n", "dependencies": ["+type.h"], "name": "zipWith", "normal": true, "typesig": "(<strong>Iter a</strong>, <strong>Iter b</strong>, <strong>BinaryMapping f</strong>) <span class=\"arr\">&rarr;</span> <strong>NSArray*</strong>", "afters": ["count", "objectAt"], "module": "iter", "description": "Zips both arrays using the BinaryMapping. That's what."}], "random": [{"definition": "/// Generate a random integer in a given range.\n// (in random)\nstatic long randint(long a, long b) {\n    long minv = MIN(a,b);\n    long maxv = MIN(a,b);\n    long len = maxv - minv + 1;\n    \n    return a + random() % len;\n}\n", "dependencies": ["+type.h"], "name": "randint", "normal": true, "typesig": "(<strong>long a</strong>, <strong>long b</strong>) <span class=\"arr\">&rarr;</span> <strong>long</strong>", "afters": [], "module": "random", "description": "Generate a random integer in a given range."}], "fold": [{"definition": "/// Combine a list of values into a single value. Takes an argument to use if the list is empty. Socialist version.\n// (in fold)\nstatic id foldl(Iter it, id ifempty, BinaryMapping f) {\n    if (!it)\n        return nil;\n    \n    id result = nil;\n    BOOL isFirst = YES;\n    for (id x in it) {\n        if (result == nil) {\n            result = x;\n            isFirst = YES;\n        }\n        else {\n            id y = f(result, x);\n            if (!y)\n                continue;\n            result = y;\n            isFirst = NO;\n        }\n    }\n\n    if (isFirst)\n        return ifempty;\n    return result;\n}\n\n", "dependencies": ["+type.h"], "name": "foldl", "normal": true, "typesig": "(<strong>Iter it</strong>, <strong>id ifempty</strong>, <strong>BinaryMapping f</strong>) <span class=\"arr\">&rarr;</span> <strong>id</strong>", "afters": [], "module": "fold", "description": "Combine a list of values into a single value. Takes an argument to use if the list is empty. Socialist version."}, {"definition": "/// Combine a list of values into a single value. Returns nil if the list is empty. Socialist version.\n// (in fold)\n// (after foldl)\nstatic id foldl1(Iter it, BinaryMapping f) {\n    return foldl(it, nil, f);\n}\n\n", "dependencies": ["+type.h"], "name": "foldl1", "normal": true, "typesig": "(<strong>Iter it</strong>, <strong>BinaryMapping f</strong>) <span class=\"arr\">&rarr;</span> <strong>id</strong>", "afters": ["foldl"], "module": "fold", "description": "Combine a list of values into a single value. Returns nil if the list is empty. Socialist version."}], "bool": [{"definition": "/// Determine if an object is empty or nil.\n// (in bool)\nstatic BOOL falsy(id x) {\n    if (!x)\n        return YES;\n    if (responds(x, @selector(count)))\n        return [(NSArray*)x count] == 0;\n    if (responds(x, @selector(length)))\n        return [(NSString*)x length] == 0;\n    return NO;\n}\n\n", "dependencies": ["+type.h", "+object.h"], "name": "falsy", "normal": true, "typesig": "(<strong>id x</strong>) <span class=\"arr\">&rarr;</span> <strong>BOOL</strong>", "afters": [], "module": "bool", "description": "Determine if an object is empty or nil."}, {"definition": "/// Determine if an object is not empty and not nil.\n// (in bool)\n// (after falsy)\nstatic BOOL truthy(id x) {\n    return !falsy(x);\n}\n\n", "dependencies": ["+type.h"], "name": "truthy", "normal": true, "typesig": "(<strong>id x</strong>) <span class=\"arr\">&rarr;</span> <strong>BOOL</strong>", "afters": ["falsy"], "module": "bool", "description": "Determine if an object is not empty and not nil."}], "func": [{"definition": "/// If x is not null, gives f(x). Otherwise, gives nil without applying f. This is useful is f is not safe with a nil value.\n// (in func)\nstatic id applyIf(id x, Mapping f) {\n    if (!x)\n        return nil;\n    return f(x);\n}\n\n", "dependencies": ["+type.h"], "name": "applyIf", "normal": true, "typesig": "(<strong>id x</strong>, <strong>Mapping f</strong>) <span class=\"arr\">&rarr;</span> <strong>id</strong>", "afters": [], "module": "func", "description": "If x is not null, gives f(x). Otherwise, gives nil without applying f. This is useful is f is not safe with a nil value."}, {"definition": "/// ___\n// (in func)\nstatic BinaryMapping byBinarySel(SEL sel) {\n    return [^ id (id x, id y) {\n        return performSel(x, sel, y);\n    } copy];\n}\n\n", "dependencies": ["+type.h", "+object.h"], "name": "byBinarySel", "normal": true, "typesig": "(<strong>SEL sel</strong>) <span class=\"arr\">&rarr;</span> <strong>BinaryMapping</strong>", "afters": [], "module": "func", "description": "___"}, {"definition": "/// A function h such that h(x) == f(g(x)) forall x\n// (in func)\nstatic Mapping byCompose(Mapping f, Mapping g) {\n    f = [f copy];\n    g = [g copy];\n    \n    return [^id(id x) {\n        return f(g(x));\n    } copy];\n}\n\n", "dependencies": ["+type.h"], "name": "byCompose", "normal": true, "typesig": "(<strong>Mapping f</strong>, <strong>Mapping g</strong>) <span class=\"arr\">&rarr;</span> <strong>Mapping</strong>", "afters": [], "module": "func", "description": "A function h such that h(x) == f(g(x)) forall x"}, {"definition": "/// The constant function f for a value y such that f(x) == y forall x\n// (in func)\nstatic Mapping byConst(id y) {\n    return [^ id (id x) {\n        return y;\n    } copy];\n}\n\n", "dependencies": ["+type.h"], "name": "byConst", "normal": true, "typesig": "(<strong>id y</strong>) <span class=\"arr\">&rarr;</span> <strong>Mapping</strong>", "afters": [], "module": "func", "description": "The constant function f for a value y such that f(x) == y forall x"}, {"definition": "/// A function g such that g(x, y) == f(y, x) forall x, y\n// (in func)\nstatic BinaryMapping byFlip(BinaryMapping f) {\n    f = [f copy];\n\n    return [^id(id x, id y) {\n        return f(y, x);\n    } copy];\n}\n\n", "dependencies": ["+type.h"], "name": "byFlip", "normal": true, "typesig": "(<strong>BinaryMapping f</strong>) <span class=\"arr\">&rarr;</span> <strong>BinaryMapping</strong>", "afters": [], "module": "func", "description": "A function g such that g(x, y) == f(y, x) forall x, y"}, {"definition": "/// Turn a function into a block\n// (in func)\nstatic Mapping byFunction(id (*f)(id)) {\n    if (f == NULL)\n        return nil;\n    return [^id(id x) {\n        return f(x);\n    } copy];\n}\n\n", "dependencies": ["+type.h"], "name": "byFunction", "normal": true, "typesig": "(<strong>id (*f)(id)</strong>) <span class=\"arr\">&rarr;</span> <strong>Mapping</strong>", "afters": [], "module": "func", "description": "Turn a function into a block"}, {"definition": "/// The identity function f such that f(x) == x\n// (in func)\nstatic Mapping byIdentity() {\n    return [^ id (id x) {\n        return x;\n    } copy];\n}\n\n", "dependencies": ["+type.h"], "name": "byIdentity", "normal": true, "typesig": "(<strong></strong>) <span class=\"arr\">&rarr;</span> <strong>Mapping</strong>", "afters": [], "module": "func", "description": "The identity function f such that f(x) == x"}]} ;