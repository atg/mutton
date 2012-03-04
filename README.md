# Mutton: Practical functional programming tools for ObjC

Mutton makes ObjC more consise and less error-prone by giving it some common functional programming tools.

## Usage

The `mutton/` directory contains an up-to-date *stable* snapshot of Mutton.

Add it to your include path somehow, or copy the files out of it, then do `#import "mutton.h"`.

* You can compile xcode/mutton-test.xcodeproj if you want to check that Mutton is in tip-top condition.
* If you want an *unstable* build for some reason, do `python compile.py --unstable`, but be aware that it will be replaced with a stable build if you `git commit`.

## Compatibility

Mutton requires either ARC or GC.

Mutton uses lots of identifiers that may already be used for variables, so you may experience some clashes. Mutton is split into several different header files, so you can simply `#import` only the header files that you want to use (instead of doing a blanket #import "mutton.h").

Alternatively, each function is in its own header file for development purposes, so just grab the headers you want out the dev repo. Be careful though, since you'll get all the testing stuff too.

All the Python scripts require Python 2.7. You're using 10.7+, right?

## Contributing

Ideas:

* Finish a function in `source/unstable`, by fixing bugs or adding tests.
* Check wishlist.txt a desired function and implement it. Run `python createfile.py <+modulename> <+functionname>`.
* Check the issue tracker and fix a bug.
* Fix a TODO somewhere
* More tests are always welcome.

I'm [@alextgordon](http://twitter.com/alextgordon) if you want to ask me something. Don't bother with GitHub's messaging system: I have 680 unread notifications.

Note that there is a pre-commit hook that runs `compile.py`, which will clobber any previous build and replace it with a fresh **stable** aggregation.

## Naming

We usually defer to Haskell when deciding what to call things. We do change the argument order quite a bit though, to suit the expectations of Objective-C programmers (Verb-Subject-Object instead of Verb-Object-Subject).

## License

Mutton is licensed under the WTFPL.
