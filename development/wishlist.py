import sys, os, subprocess, re, json
from pprint import pprint

os.chdir(os.path.split(os.path.abspath( __file__ ))[0])

def clean(ls):
    return set(x[1:-2] for x in ls)


wl = open("wishlist2.txt", 'r').read()
allfuncs = set(wl.splitlines())

stable = set(x for x in clean(os.listdir('../source/stable')) if x != 'DS_Sto')
unstable = set(x for x in clean(os.listdir('../source/unstable')) if x != 'DS_Sto')
desired = set(x for x in (allfuncs - stable - unstable) if x != '')

fl = open("wishlist_computed.txt", 'w')
fl.write("DESIRED functions\n  ")
fl.write('\n  '.join(sorted(desired)) + '\n\n')
fl.write("UNSTABLE functions\n  ")
fl.write('\n  '.join(sorted(unstable)) + '\n\n')
fl.write("STABLE functions\n  ")
fl.write('\n  '.join(sorted(stable)) + '\n\n')

desired