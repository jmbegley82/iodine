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
3.1)    (unless CMake starts being harder to utilize than Autotools; then, Autotools will be used instead)
4)  Project will use libSDL2 for video display, audio playback and input.  Ideally, each platform will be using platform-specific
    timing code, but platforms where this becomes unreasonable could use libSDL2 for timing as well.
5)  Project will use libSDL2-image to load images from files, libSDL2-mixer for loading/playing audio files, and libSDL2-ttf
    for font rendering.
6)  Project will only read/write from/to reasonable locations, dependant upon OS used.
7)  Project will _absolutely_ not devolve into the mess that Atma became, where there are at least three different functions to
    resize the main window, some of which call each other recursively, and is a complete and utter mess that hurts to read.
    7.1)  Platform-specific code will go into separate files whenever possible.
    7.2)  Don't target extra platforms out of boredom.
    7.3)  Plan ahead to reduce spaghetti
    7.4)  Use actual diagrams and flowcharts
    7.5)  No seriously, plan ahead.  No more duct-tape patchwork nonsense.
    7.6)  Stop abusing the global variable.
    7.7)  Code will be threadsafe wherever possible, which means it needs to be as clean and legible as possible.
8)  This Planning section of the README will be updated in a timely manner.
9)  Project will be using Doxygen to generate documentation/call graphs/class diagrams/etc.  Doxygen-related comments should stay
    within header files whenever possible.
10) Project will steer away from performance-impacting C++ features like function overloading, particularly in objects which
    will be used within loops.
11) Project will attempt to stay within the confines of C++11.
