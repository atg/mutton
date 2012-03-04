# Mutton: Practical functional programming tools for ObjC

Mutton makes ObjC more consise and less error-prone by giving it some common functional programming tools.

## Naming

We usually defer to Haskell when deciding what to call things. We do change the argument order quite a bit though, to suit the expectations of Objective-C programmers (Verb-Subject-Object instead of Verb-Object-Subject).

## Compatibility

Mutton requires either ARC or GC.

Mutton uses lots of identifiers that may already be used for variables, so you may experience some clashes. Mutton is split into several different header files, so you can simply `#import` only the header files that you want to use (instead of doing a blanket #import "mutton.h").

Alternatively, each function is in its own header file for development purposes, so just grab the headers you want out the dev repo. Be careful though, since you'll get all the testing stuff too.

## Contributing

Ideas:

* Check wishlist.txt for desired functions.
* Check the issue tracker.
* Fix a TODO somewhere
* More tests are always welcome.

I'm [@alextgordon](http://twitter.com/alextgordon) if you want to ask me something. Don't bother with GitHub's messaging system: I have 680 unread notifications.

Oh, and could you please run `compile.py` (with no arguments) before submitting a pull request? Makes my job a lot easier.

## License

Mutton is licensed under the WTFPL.
