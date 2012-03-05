import sys, os, subprocess, re
from pprint import pprint

os.chdir(os.path.split(os.path.abspath( __file__ ))[0])

unstable = '--unstable' in sys.argv

# Remove everything in build
subprocess.check_output(['rm', '-rf', 'mutton'])

# Create build
subprocess.check_output(['mkdir', 'mutton'])
subprocess.check_output(['mkdir', 'mutton/test'])

# Read files
def readfiles(dirname, shouldParse = False):
    paths = os.listdir(dirname)
    for p in paths:
        if not p[0] == '+':
            continue
        p1 = '%s/%s' % (dirname, p)
        content = open(p1, 'r').read()
        
        d = {
            'name': p[1:-2],
            'dirname': dirname,
            'path': p1,
            'content': content,
            'parsed': shouldParse,
        }
        
        if shouldParse:
            d['dependencies'] = re.findall(r'#import "(\+[^"\n]+.h)"', content)
            d['dependencies'] = [dep for dep in d['dependencies'] if dep != '+support.h']
            
            d['module'] = re.findall(r'// \(in ([^\)]+)\)', content)[0]
            d['description'] = re.findall(r'/// ([^\)]+)', content)[0]
            d['definition'] = re.findall(r'(/// [\s\S]+)\ntest \{', content)[0]
            d['test'] = re.findall(r'\ntest (\{[\s\S]+\})', content)[0]
            d['afters'] = set(re.findall(r'// \(after ([^\)]+)\)', content))
        yield d

allfiles = list(readfiles('source/stable', True))
if unstable:
    allfiles.extend(list(readfiles('source/unstable', True)))

def aftercmp(a, b):
    if a['name'] in b['afters']:
        return -1
    elif b['name'] in a['afters']:
        return 1
    else:
        return 0 # Can't do this, it conflicts with the comparison above: cmp(a['name'], b['name'])

processedfiles = allfiles[:]

# We can't use python's sort here because it's assumes the comparator is transitive
for i in xrange(len(processedfiles)):
    for j in xrange(len(processedfiles)):
        if i == j:
            continue
        c = aftercmp(processedfiles[i], processedfiles[j])
        if c == 0:
           continue
        if (i < j and c == 1) or (i > j and c == -1):
            processedfiles[i], processedfiles[j] = processedfiles[j], processedfiles[i]
# print [p['name'] for p in processedfiles]

miscfiles = list(readfiles('source/stable-misc', False))
allfiles.extend(miscfiles)

modules = sorted(set(f['module'] for f in processedfiles))
muttonh = '''// mutton: functional programming tools for Objective-C
// Copyright something or other. I don't really care. Seriously, just take the code and use it in your program.
// I'm not going to sue you, I'm poor and I live in a foreign land.

'''
for m in modules:
    muttonh += '#import "+%s.h"\n' % m

def put(p, content):
    f = open('mutton/' + p, 'a')
    f.write(content)
    f.close()

for miscfile in miscfiles:
    put('+%s.h' % miscfile['name'], miscfile['content'])
    if miscfile['name'] == 'support' or miscfile['name'] == 'unsupport':
        continue
    muttonh += '#import "+%s.h"\n' % miscfile['name']

put('mutton.h', muttonh)
for m in modules:
    hdeps = set()
    hcontent = '#import <Foundation/Foundation.h>\n#include "+support.h"\n\n'
    for pf in processedfiles:
        if pf['module'] == m:
            hcontent += pf['definition']
            hdeps |= set(pf['dependencies'])
    hdep = '\n'.join(['#import "%s"' % d for d in sorted(hdeps)]) + '\n\n'
    if not list(hdeps):
        hdep = ''
    
    hcontent += '#include "+unsupport.h"\n'
    if hcontent.strip():
        put('+%s.h' % m, hdep + hcontent)

testm = '#import "mutton.h"\n#include "+support.h"\n\n\n'
spfs = sorted(processedfiles, key=lambda x: x['name'])
for pf in spfs:
    testm += '#pragma mark %s (%s)\nstatic void test_%s_%s() %s\n\n\n' % (pf['name'], pf['module'], pf['name'], pf['module'], pf['test'])
testm += '#pragma mark main\nint main(void) {\n  @autoreleasepool {\n'
for pf in spfs:
    testm += '    test_%s_%s();\n' % (pf['name'], pf['module'])
testm += '''  }
  int failed = mutton_failed_assertion_count;
  int allassertions = mutton_all_assertion_count;
  printf("\\n\\nFailed %d of %d assertions (%d%% passed)\\n", failed, allassertions, 100 - (int)round((((double)failed) / ((double)allassertions)) * 100));
  
  return failed != 0;\n}\n'''

put('test/main.m', testm)

# pprint(allfiles)
