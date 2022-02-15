#TEST: require_utility nano "$TARGET_SYSROOT/bin/nano"
# Copyright (c) 2019-2022 Griefer@Work
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgement (see the following) in the product
#    documentation is required:
#    Portions Copyright (c) 2019-2022 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

require_utility libncurses "$TARGET_SYSROOT/$TARGET_LIBPATH/libncursesw.so"
require_utility file       "$PKG_CONFIG_PATH/libmagic.pc"
PACKAGE_URL="https://nano-editor.org/dist/v4/nano-4.4.tar.xz"

# Additions configure options
CONFIGURE=""
CONFIGURE="$CONFIGURE --enable-largefile"
CONFIGURE="$CONFIGURE --disable-threads"
CONFIGURE="$CONFIGURE --disable-nls"
CONFIGURE="$CONFIGURE --enable-browser"
CONFIGURE="$CONFIGURE --enable-color"
CONFIGURE="$CONFIGURE --enable-comment"
CONFIGURE="$CONFIGURE --enable-extra"
CONFIGURE="$CONFIGURE --enable-help"
CONFIGURE="$CONFIGURE --enable-histories"
CONFIGURE="$CONFIGURE --enable-justify"
CONFIGURE="$CONFIGURE --enable-libmagic"
CONFIGURE="$CONFIGURE --enable-linenumbers"
CONFIGURE="$CONFIGURE --enable-mouse"
CONFIGURE="$CONFIGURE --enable-multibuffer"
CONFIGURE="$CONFIGURE --enable-nanorc"
CONFIGURE="$CONFIGURE --enable-operatingdir"
CONFIGURE="$CONFIGURE --enable-speller"
CONFIGURE="$CONFIGURE --enable-tabcomp"
CONFIGURE="$CONFIGURE --enable-wordcomp"
CONFIGURE="$CONFIGURE --enable-wrapping"
CONFIGURE="$CONFIGURE --disable-debug"
CONFIGURE="$CONFIGURE --disable-tiny"
CONFIGURE="$CONFIGURE --enable-utf8"

# gnulib is a piece work:
#  - checking for working GNU getopt function... guessing no
#  - checking whether memchr works... guessing no
#  - checking whether the utimes function works... guessing no
#  - checking for working POSIX fnmatch... guessing no
#  - checking whether futimens works... guessing no
#  - checking whether mbrtowc works on empty input... guessing no
#  - checking whether the C locale is free of encoding errors... guessing no
#    >> This it actually guesses correctly; C local means utf-8, and
#       only bytes 00-7F can be encoded 1-on-1, but 80-FF are incomplete
#       and partly even invalid.
#  - checking for working re_compile_pattern... guessing no
#    >> Maybe some day...
PACKAGE_CONFIG_SITE="
gl_cv_func_getopt_gnu=yes
gl_cv_func_memchr_works=yes
gl_cv_func_working_utimes=yes
gl_fnmatch_cache_var=yes
gl_cv_func_futimens_works=yes
gl_cv_func_mbrtowc_empty_input=yes
"


# Automatically build+install using autoconf
. "$KOS_MISC/utilities/misc/gnu_make.sh"
