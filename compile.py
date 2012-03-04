import sys, os, subprocess, re
from pprint import pprint

os.chdir(os.path.split(os.path.abspath( __file__ ))[0])

unstable = '--unstable' in sys.argv

# Remove everything in build
subprocess.check_output(['rm', '-rf', 'build'])

# Create build
subprocess.check_output(['mkdir', 'build'])
subprocess.check_output(['mkdir', 'build/test'])

# Read files
def readfiles(dirname, shouldParse = False):
    paths = os.listdir(dirname)
    for p in paths:
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
            
        yield d

allfiles = list(readfiles('tested', True))
if unstable:
    allfiles.extend(list(readfiles('untested', True)))

processedfiles = allfiles[:]
allfiles.extend(list(readfiles('tested-misc', False)))

modules = sorted(set(f['module'] for f in processedfiles))
muttonh = '''// mutton: functional programming tools for Objective-C
// Copyright something or other. I don't really care. Seriously, just take the code and use it in your program.
// I'm not going to sue you, I'm poor and I live in a foreign land.

'''
for m in modules:
    muttonh += '#import "+%s.h"\n' % m

def put(p, content):
    f = open('build/' + p, 'a')
    f.write(content)
    f.close()

put('mutton.h', muttonh)
for m in modules:
    hdeps = set()
    hcontent = ''
    for pf in processedfiles:
        if pf['module'] == m:
            hcontent += pf['definition']
            hdeps |= set(pf['dependencies'])
    hdep = '\n'.join(['#import "%s"' % d for d in sorted(hdeps)]) + '\n\n'
    if not list(hdeps):
        hdep = ''
    
    if hcontent.strip():
        put('+%s.h' % m, hdep + hcontent)

testm = '#import "mutton.h"\n'
spfs = sorted(processedfiles, key=lambda x: x['name'])
for pf in spfs:
    testm += '#pragma mark %s (%s)\n\nstatic void test_%s_%s() %s\n' % (pf['name'], pf['module'], pf['name'], pf['module'], pf['test'])
testm += '\n\n\n#pragma mark main\n\nint main(void) {\n'
for pf in spfs:
    testm += '    test_%s_%s();\n' % (pf['name'], pf['module'])
testm += '}\n'

put('test/main.m', testm)

pprint(allfiles)
