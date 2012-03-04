/// Iter: An iterable object
typedef id<NSFastEnumeration> Iter;

/// Mapping: An block that maps an object to another object
typedef id (^Mapping)(id);

/// BinaryMapping: An block that maps two objects to an object
typedef id (^BinaryMapping)(id, id);

/// Predicate: An block that maps an object to a boolean
typedef BOOL (^Predicate)(id);

/// BinaryPredicate: An block that maps two objects to a boolean
typedef BOOL (^BinaryPredicate)(id, id);
