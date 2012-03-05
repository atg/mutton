
id               :: a -> a
    Mapping byIdentity();
const            :: a -> b -> a
    Mapping byConst(id x);
(.)              :: (b -> c) -> (a -> b) -> a -> c
    Mapping byCompose(Mapping f, Mapping g);
flip             :: (a -> b -> c) -> b -> a -> c
    BinaryMapping byFlip(BinaryMapping f);   
maybe              :: b -> (a -> b) -> Maybe a -> b
    id applyIf(id x, Mapping f);
    // returns f(x) if x is not nil, or nil otherwise
map :: (a -> b) -> [a] -> [b]
    NSArray* map(Iter i, Mapping f);
filter :: (a -> Bool) -> [a] -> [a]
    NSArray* map(Iter i, Predicate p);
concat :: [[a]] -> [a]
    NSArray* concat(Iter i);
concatMap :: (a -> [b]) -> [a] -> [b]
    NSArray* concatMap(Iter it, Iter(^f)(id x));
replicate        :: Int -> a -> [a]
    NSArray* replicate(id v, long n);
reverse          :: [a] -> [a]
    NSArray* reverse(Iter it);
until            :: (a -> Bool) -> (a -> a) -> a -> a
    id until(Predicate p, Mapping f, id x);




-- either               :: (a -> c) -> (b -> c) -> Either a b -> c
fst              :: (a,b) -> a
    id fst(Iter it);
snd              :: (a,b) -> b
    id snd(Iter it);
    id thrd(Iter it);
    id forth(Iter it);
    id fifth(Iter it);
    id sixth(Iter it);
    id seventh(Iter it);
curry            :: ((a, b) -> c) -> a -> b -> c
    Mapping(^curry)(id) (BinaryMaping f);
uncurry          :: (a -> b -> c) -> ((a, b) -> c)
    BinaryMaping uncurry (Mapping(^f)(id));
-- error            :: String -> a
-- undefined        :: a
(++) :: [a] -> [a] -> [a]
    NSArray* extend(Iter i, Iter j);
head             :: [a] -> a
    id first(Iter it);
tail             :: [a] -> [a]
    NSArray* rest(Iter it);
last             :: [a] -> a
    id last(Iter it);
init             :: [a] -> [a]
    NSArray* initial(Iter it);
null             :: [a] -> Bool
    BOOL falsy(id x);
    BOOL truthy(id x);
-- length           :: [a] -> Int
-- (!!)                :: [a] -> Int -> a
foldl            :: (a -> b -> a) -> a -> [b] -> a
    id foldl(Iter it, id x, BinaryMapping f);
foldl1           :: (a -> a -> a) -> [a] -> a
    id foldl1(Iter it, BinaryMapping f);
scanl            :: (a -> b -> a) -> a -> [b] -> [a]
    NSArray* scanl(Iter it, id x, BinaryMapping f);
scanl1           :: (a -> a -> a) -> [a] -> [a]
    NSArray* scanl1(Iter it, BinaryMapping f);
foldr            :: (a -> b -> b) -> b -> [a] -> b
    id foldr(Iter it, id x, BinaryMapping f);
foldr1           :: (a -> a -> a) -> [a] -> a
    id foldr1(Iter it, BinaryMapping f);
scanr             :: (a -> b -> b) -> b -> [a] -> [b]
    NSArray* scanr(Iter it, id x, BinaryMapping f);
scanr1          :: (a -> a -> a) -> [a] -> [a]
    NSArray* scanr1(Iter it, BinaryMapping f);
iterate          :: (a -> a) -> a -> [a]
    NSArray* nest(id v, long n, Mapping f);
    NSArray* nestList(id v, long n, Mapping f);
-- repeat           :: a -> [a]
-- cycle            :: [a] -> [a]
take                   :: Int -> [a] -> [a]
    NSArray* take(Iter it, long n);
drop                   :: Int -> [a] -> [a]
    NSArray* drop(Iter it, long n);
splitAt                  :: Int -> [a] -> ([a],[a])
    Tuple2 splitAt(Iter it, long n);
takeWhile               :: (a -> Bool) -> [a] -> [a]
    NSArray* takeWhile(Iter it, Predicate p);
dropWhile               :: (a -> Bool) -> [a] -> [a]
    NSArray* dropWhile(Iter it, Predicate p);
span, break             :: (a -> Bool) -> [a] -> ([a],[a])
    Tuple2 spanWith(Iter it, Predicate p);
    Tuple2 breakWith(Iter it, Predicate p);
-- lines            :: String -> [String]
-- words            :: String -> [String]
-- unlines          :: [String] -> String
-- unwords          :: [String] -> String
and, or          :: [Bool] -> Bool
    BOOL allTruthy(Iter it);
    BOOL anyTruthy(Iter it);
any, all         :: (a -> Bool) -> [a] -> Bool
    BOOL all(Iter it, Predicate p);
    BOOL any(Iter it, Predicate p);
elem, notElem    :: (Eq a) => a -> [a] -> Bool
lookup           :: (Eq a) => a -> [(a,b)] -> Maybe b
sum, product     :: (Num a) => [a] -> a
maximum, minimum :: (Ord a) => [a] -> a
zip              :: [a] -> [b] -> [(a,b)]
    NSArray* zip(Iter a, Iter b);
-- zip3             :: [a] -> [b] -> [c] -> [(a,b,c)]
zipWith          :: (a->b->c) -> [a]->[b]->[c]
    NSArray* zipWith(Iter it, BinaryMapping f);
-- zipWith3         :: (a->b->c->d) -> [a]->[b]->[c]->[d]
unzip            :: [(a,b)] -> ([a],[b])
    Tuple2 unzip(Iter it);
-- unzip3           :: [(a,b,c)] -> ([a],[b],[c])
    NSArray* unzipWith(Iter it, BinaryMapping f);


-- (==), (/=) :: a -> a -> Bool
-- compare              :: a -> a -> Ordering
-- (<), (<=), (>=), (>) :: a -> a -> Bool
-- max, min             :: a -> a -> a
-- succ, pred       :: a -> a
-- toEnum           :: Int -> a
-- fromEnum         :: a -> Int
-- enumFrom         :: a -> [a]             -- [n..]
-- enumFromThen     :: a -> a -> [a]        -- [n,n'..]
-- enumFromTo       :: a -> a -> [a]        -- [n..m]
-- enumFromThenTo   :: a -> a -> a -> [a]   -- [n,n'..m]
-- minBound         :: a
-- maxBound         :: a
-- (+), (-), (*)    :: a -> a -> a
-- negate           :: a -> a
-- abs, signum      :: a -> a
-- fromInteger      :: Integer -> a
-- toRational       ::  a -> Rational
-- quot, rem        :: a -> a -> a   
-- div, mod         :: a -> a -> a
-- quotRem, divMod  :: a -> a -> (a,a)
-- toInteger        :: a -> Integer
-- (/)              :: a -> a -> a
-- recip            :: a -> a
-- fromRational     :: Rational -> a
-- pi                  :: a
-- exp, log, sqrt      :: a -> a
-- (**), logBase       :: a -> a -> a
-- sin, cos, tan       :: a -> a
-- asin, acos, atan    :: a -> a
-- sinh, cosh, tanh    :: a -> a
-- asinh, acosh, atanh :: a -> a
-- properFraction   :: (Integral b) => a -> (b,a)
-- truncate, round  :: (Integral b) => a -> b
-- ceiling, floor   :: (Integral b) => a -> b
-- floatRadix       :: a -> Integer
-- floatDigits      :: a -> Int
-- floatRange       :: a -> (Int,Int)
-- decodeFloat      :: a -> (Integer,Int)
-- encodeFloat      :: Integer -> Int -> a
-- exponent         :: a -> Int
-- significand      :: a -> a
-- scaleFloat       :: Int -> a -> a
                 -- :: a -> Bool
-- atan2            :: a -> a -> a
-- subtract         :: (Num a) => a -> a -> a
even, odd        :: (Integral a) => a -> Bool
gcd              :: (Integral a) => a -> a -> a
lcm              :: (Integral a) => a -> a -> a
-- (^)              :: (Num a, Integral b) => a -> b -> a
-- (^^)             :: (Fractional a, Integral b) => a -> b -> a
-- fromIntegral     :: (Integral a, Num b) => a -> b
-- realToFrac     :: (Real a, Fractional b) => a -> b
    -- fmap              :: (a -> b) -> f a -> f b
    -- (>>=)  :: m a -> (a -> m b) -> m b
    -- (>>)   :: m a -> m b -> m b
    -- return :: a -> m a
    -- fail   :: String -> m a
-- sequence       :: Monad m => [m a] -> m [a] 
-- sequence_      :: Monad m => [m a] -> m () 
-- mapM             :: Monad m => (a -> m b) -> [a] -> m [b]
-- mapM_            :: Monad m => (a -> m b) -> [a] -> m ()
-- (=<<)            :: Monad m => (a -> m b) -> m a -> m b
-- seq :: a -> b -> b
-- ($), ($!) :: (a -> b) -> a -> b
-- (&&), (||)       :: Bool -> Bool -> Bool
-- not              :: Bool -> Bool
-- otherwise        :: Bool
                      -- where lastChar :: Char
-- numericEnumFrom         :: (Fractional a) => a -> [a]
-- numericEnumFromThen     :: (Fractional a) => a -> a -> [a]
-- numericEnumFromTo       :: (Fractional a, Ord a) => a -> a -> [a]
-- numericEnumFromThenTo   :: (Fractional a, Ord a) => a -> a -> a -> [a]
-- asTypeOf         :: a -> a -> a

    -- readsPrec        :: Int -> ReadS a
    -- readList         :: ReadS [a]
    -- showsPrec        :: Int -> a -> ShowS
    -- show             :: a -> String 
    -- showList         :: [a] -> ShowS
-- reads            :: (Read a) => ReadS a
-- shows            :: (Show a) => a -> ShowS
-- read             :: (Read a) => String -> a
-- showChar         :: Char -> ShowS
-- showString       :: String -> ShowS
-- showParen        :: Bool -> ShowS -> ShowS
-- readParen        :: Bool -> ReadS a -> ReadS a
-- lex              :: ReadS String
-- ioError    ::  IOError -> IO a 
-- userError  ::  String -> IOError
-- catch      ::  IO a -> (IOError -> IO a) -> IO a 
-- putChar    :: Char -> IO ()
-- putStr     :: String -> IO ()
-- putStrLn   :: String -> IO ()
-- print      :: Show a => a -> IO ()
-- getChar    :: IO Char
-- getLine    :: IO String
-- getContents :: IO String
-- interact    ::  (String -> String) -> IO ()
-- readFile   :: FilePath -> IO String
-- writeFile  :: FilePath -> String -> IO ()
-- appendFile :: FilePath -> String -> IO ()
-- readIO   :: Read a => String -> IO a
-- readLn :: Read a => IO a
