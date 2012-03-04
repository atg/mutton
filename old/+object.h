static BOOL responds(id obj, SEL sel) {
    return [obj respondsToSelector:sel];
}

static BOOL isKind(id obj, id class_or_classname) {
    
    Class c = Nil;
    if ([class_or_classname class] == class_or_classname)
        c = [obj isKindOfClass:class_or_classname];
    else
        c = NSClassFromString(class_or_classname);
    
    if (!c)
        return NO;
    return [obj isKindOfClass:c];
}
