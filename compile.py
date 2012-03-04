import sys, os, subprocess, re

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
            'name': p,
            'dirname': dirname,
            'path': p1,
            'content': content,
        }
        
        if shouldParse:
            d['module'] = re.findall(r'// \(in ([^\)]+)\)')[0]
            d['description'] = re.findall(r'/// ([^\)]+)')[0]
            d['definition'] = re.findall(r'(/// .+)\ntest \{')[0]
        
        yield d

allfiles = list(readfiles('tested', True))
if unstable:
    allfiles.extend(list(readfiles('untested', True)))

processedfiles = allfiles[:]
allfiles.extend(list(readfiles('tested-misc', False)))

print allfiles
