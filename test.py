import sys, os, subprocess, re
from pprint import pprint

os.chdir(os.path.split(os.path.abspath( __file__ ))[0])

subprocess.check_output(['python', 'compile.py'])
subprocess.check_output('clang -Ibuild -o build/test/mutton build/test/main.m', shell=True)
