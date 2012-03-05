// Usage:
//   ZtoZ twice = lambdaZ(x, x + x)
//   twice(6) --> 12

//   RtoR cuberoot = lambdaR(x, pow(x, 1.0/3.0))
//   cuberoot(27.0) --> 3.0

typedef long (^ZtoZ)(long);
#define lambdaZ(var, body) (^ long (long var) { body })

typedef double (^RtoR)(double);
#define lambdaR(var, body) (^ double (double var) { body })

