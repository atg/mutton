#define func(from, ...) from (^)(__VA_ARGS__)
#define nfunc(name, from, ...) from (^name)(__VA_ARGS__)

