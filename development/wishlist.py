import sys, os, subprocess, re, json
from pprint import pprint

os.chdir(os.path.split(os.path.abspath( __file__ ))[0])

def clean(ls):
    return set(x[1:-2] for x in ls)


wl = open("wishlist2.txt", 'r').read()
allfuncs = set(wl.splitlines())

stable = clean(os.listdir('../source/stable'))
unstable = clean(os.listdir('../source/unstable'))
desired = set(x for x in (allfuncs - stable - unstable) if x != '')

fl = open("wishlist_computed.txt", 'w')
fl.write("DESIRED functions\n  ")
fl.write('\n  '.join(desired) + '\n\n')
fl.write("UNSTABLE functions\n  ")
fl.write('\n  '.join(unstable) + '\n\n')
fl.write("STABLE functions\n  ")
fl.write('\n  '.join(stable) + '\n\n')

desired