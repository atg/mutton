template = """#import "+type.h"
#include "+support.h"

/// ___
// (in %s)
static ___ %s(___) {
    // TODO: Implement me!
}


test {
    // TODO: Add tests to me!
}

#include "+unsupport.h"
"""


import sys, os
if len(sys.argv) != 3:
    print 'Invalid arguments %s' % (sys.argv,)
else:
    os.chdir(os.path.split(os.path.abspath( __file__ ))[0])
    h = sys.argv[1]
    n = sys.argv[2]
    f = open('source/unstable/+%s.h' % n, 'a')
    f.write(template % (h, n))
    print 'Created %s/%s() in %s' % (h, n, 'source/unstable/+%s.h' % n)

