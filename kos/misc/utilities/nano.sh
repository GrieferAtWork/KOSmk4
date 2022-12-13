#TEST: require_utility nano "$SYSROOT_BIN_TARGET_COMMON/bin/nano"
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

require_utility libncurses "$SYSROOT_BIN_TARGET_COMMON/$TARGET_LIBPATH/libncursesw.so"
require_utility file       "$PKG_CONFIG_PATH/libmagic.pc"
PACKAGE_URL="https://nano-editor.org/dist/v4/nano-4.4.tar.xz"

# Additions configure options
CONFIGURE=(
	"--enable-largefile"
	"--disable-threads"   # Why? You're a single-threaded, single-user text editor...
	"--enable-nls"
	"--enable-browser"
	"--enable-color"
	"--enable-comment"
	"--enable-extra"
	"--enable-help"
	"--enable-histories"
	"--enable-justify"
	"--enable-libmagic"
	"--enable-linenumbers"
	"--enable-mouse"
	"--enable-multibuffer"
	"--enable-nanorc"
	"--enable-operatingdir"
	"--enable-speller"
	"--enable-tabcomp"
	"--enable-wordcomp"
	"--enable-wrapping"
	"--disable-debug"
	"--disable-tiny"
	"--enable-utf8"
)

#
# Force-enable 64-bit time because gnulib laiks 2 suc dix and p00p itself
#
# DID ANYONE EVEN TEST ALL OF YOUR NONSENSE, GNULIB!?!?!
#
# As an explaination: there is some really strange non-sense going on with
# its detection of `struct stat::st_birthtime' somehow (incorrectly) being
# intermangled with the other fields. Essentially, when `stat::st_*_tim'
# exists, but isn't actually a `struct timespec' (as is the case when using
# 32-bit time_t on i386), then you'll get compile-time errors. But not for
# a lack of this not being supported. This is actually something that gnulib
# tries to support, with dediced code just for this case. - Problem is that
# said code is broken, and -- to quote the above -- "laiks 2 suc dix"
#
# PS: f*ck you gnulib
#
PACKAGE_CCFLAGS="-D_TIME_T_BITS=64"


# Automatically build+install using autoconf
. "$KOS_MISC/utilities/misc/gnu_make.sh"

#TODO: Improve integration:
# checking for glob_pattern_p... no
