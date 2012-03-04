/// map(xs, f) is the list obtained by applying f to each element of xs
// (in iter)
static NSArray* map(Iter it, Mapping f) {
    yield_start;
    for (id x in it) {
        id y = f(x);
        if (y)
            yield(y);
    } 
    yield_stop;
}

