// TODO
// pchunk -- chunk an array
// pfold

NSArray* penumerate(NSArray* it, void f) {
    
    // TODO ...
    // enumerateObjectsWithOptions:usingBlock:
}

NSArray* pmap(Iter it, Mapping f) {
    
    // TODO: Another way to do this would be to divide the array into 16 or so subarrays, then map all of on a separate thread, and wait using a group. This is probably more efficient than what we have here (not sure though). One downside is that it requires an array, so we would have to coerce with iter() first
    
    // Create an NSMutableArray and a queue, then penumerate using the block, and insert on the queue
    NSMutableArray* temp = [NSMutableArray array];
    dispatch_queue_t queue = dispatch_queue_create("mutton.pmap", NULL);
    dispatch_group_t group = dispatch_group_create();
        
    for (id x in it) {
        dispatch_group_async(group, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_NORMAL, 0), ^{
            id y = f(x);
            
            dispatch_sync(queue, ^{
                [temp addObject:y];
            }];
        });
    }
    
    dispatch_group_wait(group, DISPATCH_TIME_FOREVER);
    dispatch_release(group);
    dispatch_release(queue);
    
    return temp;
}

/// pnotify: turn a function that returns a value into one that runs async and passes by continuation
void (^pcps)(id, void (^)(id)) (dispatch_queue_t asyncq, dispatch_queue_t resultq, Mapping f) {
    // ^^^ makes sense really
    // declare pnotify as block (id, block (id) returning void) returning function (block (id) returning id, dispatch_queue_t, dispatch_queue_t) returning void
    
    return ^ void (id arg, void (^out)(id)) {
        dispatch_async(asyncq, ^{
            id y = f(arg);
            dispatch_async(resultq, ^{
                out(y);
            });
        });
    }
}


/* Example:
auto f = pcps(dispatch_get_global_queue(0,0), dispatch_get_main_queue(), ^id (id x){
    // Some expensive operation on x
    return ...;
});

f(@10, ^(id result) {
    
});
*/
