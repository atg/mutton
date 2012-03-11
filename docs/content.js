var alldocs = {"object": [{"definition": "/// Wraps isKindOfClass. Accepts a string as the class argument.\n// (in object)\nstatic BOOL isKind(id obj, id class_or_classname) {\n\n    Class c = Nil;\n    if ([class_or_classname class] == class_or_classname)\n        c = class_or_classname;\n    else\n        c = NSClassFromString(class_or_classname);\n\n    if (!c)\n        return NO;\n    return [obj isKindOfClass:c];\n}\n\n", "dependencies": [], "name": "isKind", "normal": true, "typesig": "(<strong>id obj</strong>, <strong>id class_or_classname</strong>) -> <strong>BOOL</strong>", "afters": [], "module": "object", "description": "Wraps isKindOfClass. Accepts a string as the class argument."}, {"definition": "/// Wraps -respondsToSelector\n// (in object)\nstatic BOOL responds(id obj, SEL sel) {\n    return [obj respondsToSelector:sel];\n}\n\n", "dependencies": [], "name": "responds", "normal": true, "typesig": "(<strong>id obj</strong>, <strong>SEL sel</strong>) -> <strong>BOOL</strong>", "afters": [], "module": "object", "description": "Wraps -respondsToSelector"}], "bool": [{"definition": "/// Determine if an object is empty or nil.\n// (in bool)\nstatic BOOL falsy(id x) {\n    if (!x)\n        return YES;\n    if (responds(x, @selector(count)))\n        return [(NSArray*)x count] == 0;\n    if (responds(x, @selector(length)))\n        return [(NSString*)x length] == 0;\n    return NO;\n}\n\n", "dependencies": ["+type.h", "+object.h"], "name": "falsy", "normal": true, "typesig": "(<strong>id x</strong>) -> <strong>BOOL</strong>", "afters": [], "module": "bool", "description": "Determine if an object is empty or nil."}, {"definition": "/// Determine if an object is not empty and not nil.\n// (in bool)\n// (after falsy)\nstatic BOOL truthy(id x) {\n    return !falsy(x);\n}\n\n", "dependencies": ["+type.h"], "name": "truthy", "normal": true, "typesig": "(<strong>id x</strong>) -> <strong>BOOL</strong>", "afters": ["falsy"], "module": "bool", "description": "Determine if an object is not empty and not nil."}], "func": [{"definition": "/// If x is not null, gives f(x). Otherwise, gives nil without applying f. This is useful is f is not safe with a nil value.\n// (in func)\nstatic id applyIf(id x, Mapping f) {\n    if (!x)\n        return nil;\n    return f(x);\n}\n\n", "dependencies": ["+type.h"], "name": "applyIf", "normal": true, "typesig": "(<strong>id x</strong>, <strong>Mapping f</strong>) -> <strong>id</strong>", "afters": [], "module": "func", "description": "If x is not null, gives f(x). Otherwise, gives nil without applying f. This is useful is f is not safe with a nil value."}, {"definition": "/// A function h such that h(x) == f(g(x)) forall x\n// (in func)\nstatic Mapping byCompose(Mapping f, Mapping g) {\n    f = [f copy];\n    g = [g copy];\n    \n    return [^id(id x) {\n        return f(g(x));\n    } copy];\n}\n\n", "dependencies": ["+type.h"], "name": "byCompose", "normal": true, "typesig": "(<strong>Mapping f</strong>, <strong>Mapping g</strong>) -> <strong>Mapping</strong>", "afters": [], "module": "func", "description": "A function h such that h(x) == f(g(x)) forall x"}, {"definition": "/// The constant function f for a value y such that f(x) == y forall x\n// (in func)\nstatic Mapping byConst(id y) {\n    return [^ id (id x) {\n        return y;\n    } copy];\n}\n\n", "dependencies": ["+type.h"], "name": "byConst", "normal": true, "typesig": "(<strong>id y</strong>) -> <strong>Mapping</strong>", "afters": [], "module": "func", "description": "The constant function f for a value y such that f(x) == y forall x"}, {"definition": "/// A function g such that g(x, y) == f(y, x) forall x, y\n// (in func)\nstatic BinaryMapping byFlip(BinaryMapping f) {\n    f = [f copy];\n\n    return [^id(id x, id y) {\n        return f(y, x);\n    } copy];\n}\n\n", "dependencies": ["+type.h"], "name": "byFlip", "normal": true, "typesig": "(<strong>BinaryMapping f</strong>) -> <strong>BinaryMapping</strong>", "afters": [], "module": "func", "description": "A function g such that g(x, y) == f(y, x) forall x, y"}, {"definition": "/// Turn a function into a block\n// (in func)\nstatic Mapping byFunction(id (*f)(id)) {\n    if (f == NULL)\n        return nil;\n    return [^id(id x) {\n        return f(x);\n    } copy];\n}\n\n", "dependencies": ["+type.h"], "name": "byFunction", "normal": true, "typesig": "(<strong>id (*f)(id)</strong>) -> <strong>Mapping</strong>", "afters": [], "module": "func", "description": "Turn a function into a block"}, {"definition": "/// The identity function f such that f(x) == x\n// (in func)\nstatic Mapping byIdentity() {\n    return [^ id (id x) {\n        return x;\n    } copy];\n}\n\n", "dependencies": ["+type.h"], "name": "byIdentity", "normal": true, "typesig": "(<strong></strong>) -> <strong>Mapping</strong>", "afters": [], "module": "func", "description": "The identity function f such that f(x) == x"}], "iter": [{"definition": "/// Returns true if all \n// (in iter)\nstatic BOOL all(Iter it, Predicate p) {\n    // TODO: Implement me!\n    if (!it)\n      return nil;\n    \n    for (id x in it)\n      if (!p(x))\n        return NO;\n\n    return YES;\n}\n\n", "dependencies": ["+type.h"], "name": "all", "normal": true, "typesig": "(<strong>Iter it</strong>, <strong>Predicate p</strong>) -> <strong>BOOL</strong>", "afters": [], "module": "iter", "description": "Returns true if all "}, {"definition": "/// Returns true if the predicate validates to any of the elements, false otherwise.\n// (in iter)\nstatic BOOL any(Iter it, Predicate p) {\n    if (!it)\n      return nil;\n    \n    for (id x in it)\n      if (p(x))\n        return YES;\n    \n    return NO;\n}\n\n", "dependencies": ["+type.h"], "name": "any", "normal": true, "typesig": "(<strong>Iter it</strong>, <strong>Predicate p</strong>) -> <strong>BOOL</strong>", "afters": [], "module": "iter", "description": "Returns true if the predicate validates to any of the elements, false otherwise."}, {"definition": "/// Keep only the elements of a list for with the predicate is true.\n// (in iter)\nstatic NSArray* filter(Iter it, Predicate p) {\n    if (!it)\n        return nil;\n    yield_start;\n    for (id x in it) {\n        if (p(x))\n            yield(x);\n    }\n    yield_stop;\n}\n\n", "dependencies": ["+type.h"], "name": "filter", "normal": true, "typesig": "(<strong>Iter it</strong>, <strong>Predicate p</strong>) -> <strong>NSArray*</strong>", "afters": [], "module": "iter", "description": "Keep only the elements of a list for with the predicate is true."}, {"definition": "/// Glue together an array of arrays (or iterable of iterables) to make one big array.\n// (in iter)\nstatic NSArray* concat(Iter it) {\n    if (!it)\n        return nil;\n    \n    yield_start;\n    for (Iter j in it) {\n        if ([j isKindOfClass:[NSArray class]]) {\n            yield_from((NSArray*)j);\n        }\n        else {\n            for (id x in j) {\n                yield(x);\n            }\n        }\n    }\n    yield_stop;\n}\n\n", "dependencies": ["+type.h"], "name": "concat", "normal": true, "typesig": "(<strong>Iter it</strong>) -> <strong>NSArray*</strong>", "afters": [], "module": "iter", "description": "Glue together an array of arrays (or iterable of iterables) to make one big array."}, {"definition": "/// map(xs, f) is the list obtained by applying f to each element of xs\n// (in iter)\nstatic NSArray* map(Iter it, Mapping f) {\n    if (!it)\n        return nil;\n    yield_start;\n    for (id x in it) {\n        id y = f(x);\n        if (y)\n            yield(y);\n    } \n    yield_stop;\n}\n\n", "dependencies": ["+type.h"], "name": "map", "normal": true, "typesig": "(<strong>Iter it</strong>, <strong>Mapping f</strong>) -> <strong>NSArray*</strong>", "afters": [], "module": "iter", "description": "map(xs, f) is the list obtained by applying f to each element of xs"}, {"definition": "/// Tells if the array contains the object.\n// (in iter)\nstatic BOOL contains(Iter it, id x) {\n  return any(it, ^ BOOL (id y) { return [y isEqual:x]; });\n}\n\n", "dependencies": ["+type.h"], "name": "contains", "normal": true, "typesig": "(<strong>Iter it</strong>, <strong>id x</strong>) -> <strong>BOOL</strong>", "afters": [], "module": "iter", "description": "Tells if the array contains the object."}, {"definition": "/// Find the number of objects in an array or iterable.\n// (in iter)\nstatic long count(Iter it) {\n    if (responds(it, @selector(count)))\n        return [(NSArray*)it count];\n\n    long i = 0;\n    for (id x in it) {\n        i++;\n    }\n    return i;\n}\n\n", "dependencies": ["+type.h", "+object.h"], "name": "count", "normal": true, "typesig": "(<strong>Iter it</strong>) -> <strong>long</strong>", "afters": [], "module": "iter", "description": "Find the number of objects in an array or iterable."}, {"definition": "/// Removes the given number of objects from the array\n// (in iter)\nstatic NSArray* drop(Iter it, long n) {\n    if (n < 0)\n        [NSException raise:NSInvalidArgumentException format:@\"drop(%@, %ld) called with negative N\", it, n];\n    if (!it)\n        return nil;\n    \n    yield_start;\n    \n    long i = 0;\n    for (id x in it) {\n        if (i >= n)\n            yield(x);\n        else\n            i++;\n    }\n\n    yield_stop;\n}\n\n", "dependencies": ["+type.h"], "name": "drop", "normal": true, "typesig": "(<strong>Iter it</strong>, <strong>long n</strong>) -> <strong>NSArray*</strong>", "afters": [], "module": "iter", "description": "Removes the given number of objects from the array"}, {"definition": "/// Removes falsy values from the array.\n// (in iter)\n// (after filter)\nstatic NSArray* compact(Iter it) {\n    return filter(it, ^ BOOL (id x) { return truthy(x); });\n}\n\n", "dependencies": ["+type.h"], "name": "compact", "normal": true, "typesig": "(<strong>Iter it</strong>) -> <strong>NSArray*</strong>", "afters": ["filter"], "module": "iter", "description": "Removes falsy values from the array."}, {"definition": "/// Find the first object of the iterable, or nil if it's empty.\n// (in iter)\nstatic id first(Iter it) {\n    for (id obj in it) {\n        return obj;\n    }\n    return nil;\n}\n\n", "dependencies": ["+type.h"], "name": "first", "normal": true, "typesig": "(<strong>Iter it</strong>) -> <strong>id</strong>", "afters": [], "module": "iter", "description": "Find the first object of the iterable, or nil if it's empty."}, {"definition": "/// Return all the elements of a list except the last one.\n// (in iter)\nstatic id initial(Iter it) {\n    if (!it)\n        return nil;\n\n    // TODO: Add a specialization for NSArray using subarrayWithRange:\n\n    // We don't know when the iterable ends, so we just have to add everything to an array, then remove the last object\n    yield_start;\n    for (id x in it) {\n        yield(x);\n    }\n\n    if ([mutton_yield_v_ count])\n        [mutton_yield_v_ removeLastObject];\n    yield_stop;\n}\n\n", "dependencies": ["+type.h"], "name": "initial", "normal": true, "typesig": "(<strong>Iter it</strong>) -> <strong>id</strong>", "afters": [], "module": "iter", "description": "Return all the elements of a list except the last one."}, {"definition": "/// A bit like componentsJoinedByString: but with general purpose iterables instead of strings.\n// (in iter)\nstatic NSArray* intersperse(Iter it, id glue) {\n    if (!it)\n        return nil;\n    \n    yield_start;\n    \n    for (id x in it) {\n        yield(x);\n        yield(glue);\n    }\n    \n    if ([mutton_yield_v_ count])\n        [mutton_yield_v_ removeLastObject];\n\n    yield_stop;\n}\n\n", "dependencies": [], "name": "intersperse", "normal": true, "typesig": "(<strong>Iter it</strong>, <strong>id glue</strong>) -> <strong>NSArray*</strong>", "afters": [], "module": "iter", "description": "A bit like componentsJoinedByString: but with general purpose iterables instead of strings."}, {"definition": "/// Convert a general purpose iterable to an NSArray*\n// (in iter)\nstatic NSArray* iter(Iter it) {\n    if (!it)\n        return nil;\n\n    if (isKind(it, [NSMutableArray class]))\n        return [(NSMutableArray*)it copy];\n\n    // If it's a non-mutable array, we're probably OK to not copy it\n    if (isKind(it, [NSArray class]))\n        return (NSArray*)it;\n\n    yield_start;\n    for (id x in it) {\n        yield(x);\n    }\n    yield_stop;\n}\n", "dependencies": ["+type.h", "+object.h"], "name": "iter", "normal": true, "typesig": "(<strong>Iter it</strong>) -> <strong>NSArray*</strong>", "afters": [], "module": "iter", "description": "Convert a general purpose iterable to an NSArray*"}, {"definition": "/// Find the last object of the iterable, or nil if it's empty.\n// (in iter)\nstatic id last(Iter it) {\n    if (responds(it, @selector(lastObject)))\n        return [(NSArray*)it lastObject];\n\n    id v = nil;\n    for (id x in it) {\n        v = x;\n    }\n    return v;\n}\n\n", "dependencies": ["+type.h", "+object.h"], "name": "last", "normal": true, "typesig": "(<strong>Iter it</strong>) -> <strong>id</strong>", "afters": [], "module": "iter", "description": "Find the last object of the iterable, or nil if it's empty."}, {"definition": "/// Map each element to a list of new elements (which may be empty), then glue the lists together. It's map, filter and a bit more on top.\n// (in iter)\n// (after concat)\n// (after map)\nstatic NSArray* concatMap(Iter it, Iter(^f)(id)) {\n    if (!it)\n        return nil;\n    return concat(map(it, f)); // Ahhhh the joys of functional programming at last\n}\n\n", "dependencies": ["+type.h"], "name": "concatMap", "normal": true, "typesig": "(<strong>Iter it</strong>, <strong>Iter(^f)(id)</strong>) -> <strong>NSArray*</strong>", "afters": ["map", "concat"], "module": "iter", "description": "Map each element to a list of new elements (which may be empty), then glue the lists together. It's map, filter and a bit more on top."}, {"definition": "/// Like objectAtIndex: but works on general iterables, and returns nil if the index is out of bounds (instead of an exception).\n// (in iter)\nstatic id objectAt(Iter it, long n) {\n\n    if (!it)\n        return nil;\n    if (n < 0)\n        return nil;\n    \n    if (responds(it, @selector(count))) {\n        if (n >= [(NSArray*)it count])\n            return nil;\n        if (responds(it, @selector(objectAtIndex:))) {\n            return [(NSArray*)it objectAtIndex:n];\n        }\n    }\n\n    NSInteger i = 0;\n    for (id x in it) {\n        if (i == n)\n            return x;\n        i++;\n    }\n\n    return nil;\n}\n\n", "dependencies": ["+type.h", "+object.h"], "name": "objectAt", "normal": true, "typesig": "(<strong>Iter it</strong>, <strong>long n</strong>) -> <strong>id</strong>", "afters": [], "module": "iter", "description": "Like objectAtIndex: but works on general iterables, and returns nil if the index is out of bounds (instead of an exception)."}, {"definition": "/// Build a list by repeating an element a given (non-negative) number of times.\n// (in iter)\nstatic NSArray* replicate(id v, long n) {\n    if (n < 0)\n        [NSException raise:NSInvalidArgumentException format:@\"replicate(%@, %ld) called with negative N\", v, n];\n    if (!v)\n        return nil;\n    \n    yield_start;\n    for (long i = 0; i < n; i++) {\n        yield(v);\n    }\n    yield_stop;\n}\n\n", "dependencies": ["+type.h"], "name": "replicate", "normal": true, "typesig": "(<strong>id v</strong>, <strong>long n</strong>) -> <strong>NSArray*</strong>", "afters": [], "module": "iter", "description": "Build a list by repeating an element a given (non-negative) number of times."}, {"definition": "/// Reverse an iterable.\n// (in iter)\n// (after iter)\nstatic id reverse(Iter it) {\n    if (!it)\n        return nil;\n\n    if (responds(it, @selector(reverseObjectEnumerator)))\n        return iter([(NSArray*)it reverseObjectEnumerator]);\n    else\n        return reverse(iter(it));\n}\n\n", "dependencies": ["+type.h", "+object.h"], "name": "reverse", "normal": true, "typesig": "(<strong>Iter it</strong>) -> <strong>id</strong>", "afters": ["iter"], "module": "iter", "description": "Reverse an iterable."}, {"definition": "/// A bit like componentsSeparatedByString: but with general purpose iterables instead of of strings\n// (in iter)\nstatic NSArray* split(Iter it, id token) {\n    if (!it)\n        return nil;\n    \n    BOOL isEmpty = YES;\n    \n    yield_start;\n    \n    NSMutableArray* temp = [[NSMutableArray alloc] init];\n    for (id x in it) {\n        isEmpty = NO;\n        if (x == token) {\n            yield(temp);\n            temp = [[NSMutableArray alloc] init];\n        } else {\n            [temp addObject:x];\n        }\n    }\n    \n    if (isEmpty)\n        return emptylist();\n    \n    yield(temp);\n    yield_stop;\n}\n\n", "dependencies": [], "name": "split", "normal": true, "typesig": "(<strong>Iter it</strong>, <strong>id token</strong>) -> <strong>NSArray*</strong>", "afters": [], "module": "iter", "description": "A bit like componentsSeparatedByString: but with general purpose iterables instead of of strings"}, {"definition": "/// Extract the elements after the head of a list.\n// (in iter)\nstatic id tail(Iter it) {\n    if (!it)\n        return nil;\n\n    // TODO: Add a specialization for NSArray using subarrayWithRange:\n\n    yield_start;\n    BOOL isFirst = YES;\n    for (id x in it) {\n        if (isFirst)\n            isFirst = NO;\n        else\n            yield(x);\n    } \n    yield_stop;\n}\n\n", "dependencies": ["+type.h"], "name": "tail", "normal": true, "typesig": "(<strong>Iter it</strong>) -> <strong>id</strong>", "afters": [], "module": "iter", "description": "Extract the elements after the head of a list."}, {"definition": "/// ___\n// (in iter)\nstatic NSArray* take(Iter it, long n) {\n    if (!it)\n        return nil;\n\n    yield_start;\n\n    long i = 0;\n    for (id x in it) {\n        if (i >= n)\n            break;\n        \n        yield(x);\n        i++;\n    }\n\n    yield_stop;\n}\n\n", "dependencies": ["+type.h"], "name": "take", "normal": true, "typesig": "(<strong>Iter it</strong>, <strong>long n</strong>) -> <strong>NSArray*</strong>", "afters": [], "module": "iter", "description": "___"}, {"definition": "/// ___\n// (in iter)\n// (after count)\n// (after objectAt)\nstatic NSArray* transpose(Iter it) {\n  if (!it)\n    return nil;\n  \n  NSMutableArray* normal = [[NSMutableArray alloc] init];\n  for (id x in it)\n    [normal addObject:[NSMutableArray arrayWithArray:x]];\n  \n  yield_start;\n  \n  for (long i = 0; i <= [normal count]; i++)\n  {\n    yield([NSMutableArray array]);\n    BOOL isEmpty = YES;\n\n    for (id x in normal)\n    {\n      if ([x count] == 0)\n        continue;\n      \n      isEmpty = NO;\n      \n      [[mutton_yield_v_ lastObject] addObject:[x objectAtIndex:0]];\n      [x removeObjectAtIndex:0];\n    }\n    \n    if (isEmpty)\n      [mutton_yield_v_ removeLastObject];\n  }\n  \n  yield_stop;\n}\n\n", "dependencies": ["+type.h"], "name": "transpose", "normal": true, "typesig": "(<strong>Iter it</strong>) -> <strong>NSArray*</strong>", "afters": ["count", "objectAt"], "module": "iter", "description": "___"}, {"definition": "/// Remove duplicate objects, as determined by their -hash and isEqual: (i.e., the objects are inserted into an NSSet to determine equality). O(n).\n// (in iter)\nstatic NSArray* uniqued(Iter it) {\n    if (!it)\n        return nil;\n    \n    NSMutableSet* s = [NSMutableSet set];\n    yield_start;\n    for (id x in it) {\n        if (![s containsObject:x]) {\n            [s addObject:x];\n            yield(x);\n        }\n    }\n    yield_stop;\n}\n\n", "dependencies": ["+type.h"], "name": "uniqued", "normal": true, "typesig": "(<strong>Iter it</strong>) -> <strong>NSArray*</strong>", "afters": [], "module": "iter", "description": "Remove duplicate objects, as determined by their -hash and isEqual: (i.e., the objects are inserted into an NSSet to determine equality). O(n)."}, {"definition": "/// Applies a function over and over again to x until p(x) evaluates to true.\n// (in iter)\nstatic id until(Predicate p, Mapping f, id x) {\n    while (!p(x))\n        x = f(x);\n    return x;\n}\n\n", "dependencies": ["+type.h"], "name": "until", "normal": true, "typesig": "(<strong>Predicate p</strong>, <strong>Mapping f</strong>, <strong>id x</strong>) -> <strong>id</strong>", "afters": [], "module": "iter", "description": "Applies a function over and over again to x until p(x) evaluates to true."}]} ;