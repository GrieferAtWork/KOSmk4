Please note that many of the C++ header files are heavily derived from files
found in the GLIBCXX headers installed when building the libstdc++ package
from the GCC source tree.
This is required to provide compatibility with the g++ compiler, while still
providing all of the extensions and features from upcoming releases of the C++
standard already provided by GLIBCXX.
For this purpose, the contents of various C++ headers should be taken with a
grain of salt, especially when it comes to subsequent use of them, as one could
argue that parts of them still fall under the jurisdiction of GLIBCXX, rather
than that of KOS.
However, I would argue that sufficient changes have been made: mainly in the
area of attempting to add compatibility for older c++ compilers, as well as
rewriting headers to make use of the <features.h>-system already used in C, as
well as added more fine-grained checks for which features are provided by the
compiler, rather than blindly assuming that the compiler is able to do everything
