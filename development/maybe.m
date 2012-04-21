// Sometimes you need to store nil in a collection
// There's NSNull, of course. But what if you need to store both nil AND NSNull in a collection?

@interface NSObject (MTMaybe)

- (id)fromMaybe;

@end

@implementation NSObject (MTMaybe)

- (id)fromMaybe {
    return self;
}

@end

@interface MTNothing : NSObject

- (id)fromMaybe;

@end

@implementation MTNothing

- (id)fromMaybe {
    return nil;
}

@end


id MTJust(id x) {
    if ([x isKindOfClass:[MTNothing class]])
        return 
    if (x)
        return x;
    
}
