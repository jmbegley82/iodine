# Iodine
There is currently no license, implied or otherwise, for anything in this repo.  Its purpose is educational only!

# Building:
    Generic target:
        Instructions:
            Edit Makefile.testing CC and CXX variables as appropriate
            For binary:         make (or gmake) -f Makefile.testing
            For docs:           make (or gmake) -f Makefile.testing doc
                                    (or just run doxygen)
            Binaries are in:    ./build
            Docs are in:        ./doc
            No (un)install script.
        Full build requires:
            GNU Make (tested with 4.2.1 and 4.3)
            C and C++ compilers with support for C++11 (tested with GCC 9.3.0 and Clang 8.0.1 and 9.0.1)
            Doxygen (tested with 1.8.17)

# Planning:
1)  Project will be test-driven
2)  Project will implement a scripting language and objects which can communicate with each other using it during runtime.
3)  Project will target the following OS/architecture/build systems:
    - Linux 3.2.0+/x86 and amd64/GNU Make + CMake
    - Windows 7+/x86 and amd64/Visual Studio (version TBD, probably VS2019)
    - Windows 7+/x86 and amd64/MinGW + CMake
    - MacOS 10.8+/amd64/Xcode (version TBD, probably 7)
    - iOS 11+/arm64/Xcode (probably 7)
    - Android ICS+/arm?/Android Studio (version TBD)
    - FreeBSD 11+/amd64/GNU Make (+ maybe CMake)
    - OpenBSD 6.7+/amd64/GNU Make (+ maybe CMake)
    - A Generic target using a very plain GNU Makefile for testing purposes
4)  Project will use libSDL2 for video display, audio playback and input.  Ideally, each platform will be using
    platform-specific timing code, but platforms where this becomes unreasonable could use libSDL2 for timing as well.
5)  Project will use libSDL2-image to load images from files, libSDL2-mixer for loading/playing audio files, and libSDL2-ttf
    for font rendering.
6)  Project will only read/write from/to platform-appropriate locations.
7)  Project will _absolutely_ not devolve into the mess that Atma became, where there are at least three different functions
    to resize the main window, some of which call each other recursively, and is a complete and utter mess that hurts to read.
    - Platform-specific code will go into separate files whenever possible.
    - Don't target extra platforms out of boredom.
    - Plan ahead to reduce spaghetti
    - Use actual diagrams and flowcharts
    - No seriously, plan ahead.  No more duct-tape patchwork nonsense.
    - Stop abusing the global variable.
    - Code will be threadsafe wherever possible, which means it needs to be as clean and legible as possible.
8)  This Planning section of the README will be updated in a timely manner.
9)  Project will be using Doxygen to generate documentation/call graphs/class diagrams/etc.
    - All C++ classes' (and their members') Doxygen comments will be confined to their respective header files.
    - All C++ free functions (those not part of a class) and C functions that are declared within header files will have their
    Doxygen comments there as well.
    - Non-exported functions (those which are not declared within header files) will have their Doxygen comments (if
    necessary) within their source files.
10) Project will steer away from performance-impacting C++ features like function overloading, particularly in objects which
    will be used within loops.
11) Project will attempt to stay within the confines of C11/C++11.
12) Texts will be formatted for display on devices that can display 128 columns.
13) Before any version is finalized, it must:
    - Build without warnings
    - Pass all built-in tests
    - valgrind memcheck and helgrind should be as clean as possible

# Current Tasks (as of 2020/07/19):
- Reduce number of valgrind complains on OpenBSD (back burner, may be due to libpthread?)
- Container base class for objects which will contain multiple Atoms (needs more testing)
- A class for the storage/retrieval of variables (needs more testing)
- Determine how best to approach a layered screen system
    - One approach is to give each on-screen entity's class a layer index, since Atma's layered system eventually evolved to
    have objects in different layers interacting anyway
    - There's the Atma method, which separated layers into distinct collections of objects, and had the advantages of easy
    implementation of a menu overlay on top of scrolling/repeating/tiled/different-resolution/etc. backgrounds
- The dreaded collision detection/handling mechanisms
- Classes/structs for single animation cels, collections of cels (animations), collections of animations (in progress)

# Scripting language (name tbd)
Future objects which will accept text commands should a) adhere to the existing examples and b) be detailed below.  VarSet
came first.  Introspector came next and was modeled after VarSet.  New objects that require a Command(string) function are
currently planned to begin as a copy of VarSet's or Introspector's Command(string).

- VarSet commands (terminology/syntax unstable):
  - <subject> <operator> <target>
    - var = 1
    - var += 1
    - var -= 1
    - str = "Words and/or phrases"
    - str += "additional words and/or phrases"
  - <command> <subject>
    - delete var
  - Valid operators:  = += -= \*= /= ^=
  - Valid commands:  delete
- Introspector (\*Reference) commands:
  - <subject> <operator> <target>
    - var = 1
    - var = #othervar
    - var -= 3.14159
  - Numeric only
  - Valid operators:  = += -= \*= /= ^=
  - Valid commands:  (n/a)
- Animation commands:
  - <subject> <operator> <target>
    - texture = Data/texture.png
    - delay = 60
    - cel += 0,0,64,64

Future:
- Full order-of-operations in expressions
  - var = #a ^ 2 * #b ^ 2

# Animation
Whereas Atma used individual image files for each Cel, Iodine will be using 'spritesheets', where a given animated object has
all its animation cels stored in one large image file.  For now, we will be sticking to .png files with 8-bit r,g,b channels
and one-bit alpha.

(unofficial terminology follows)

Classes:
- Sprite
- AnimationSet
- Animation
- Cel

Class descriptions:
- Sprite:
  - AnimationSet\* anim
  - Set/GetAnimationSet(const string& name)
  - Set/GetAnimation(const string& name)
  - void Draw()
- AnimationSet:
  - Texture image
  - std::map\<string,Animation\*\> anims
- Animation:
  - const unsigned int animationDelayinMsec
  - std::queue\<Cel\*\> cels
- Cel:
  - unsigned int x, y //position of upper-left pixel of cel
  - unsigned int w, h //width and height of cel (lower-right pixel = (x+w,y+h))


Cels will generally be stored sequentially within a list/queue/etc. within Animations.  Animations will generally be stored in
maps (by string) within their respective AnimationSets.  AnimationSets will be contained within a globally-accessible cache,
possibly also within a map by string.  A Sprite class will be used in place of multiple instances of AnimationSet.

# Screen
Screen needs to be implemented before anything else graphical can be completed.  Screen will be a static object.  Screen should
defer window creation until a function is called; this way Logger will definitely be started beforehand, which will make debug
output availability more reliable.  It is currently done during construction and this needs to be changed.

# System.h,cpp
The System class will be our sole static class; this will hypothetically make the transition from a testing main executable to
a library smoother, and keep the chain of initialization of different parts of the codebase easier to understand and debug.
