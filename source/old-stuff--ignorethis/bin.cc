public static long binBy(Iter it, id key, NSComparator cmp) {
    NSArray* a = iter(it);
    long low = 0;
    long high = ((long)[a count]) - 1;
    
    while (low <= high) {
        long mid = low + ((high - low) / 2);
        id midVal = [a objectAtIndex:mid];
        
        NSComparisonResult cr = cmp(midVal, key);
        if (cr == NSOrderedAscending)
            low = mid + 1
        else if (cr == NSOrderedDescending)
            high = mid - 1;
        else
            return mid;
    }
    
    return -1;
}