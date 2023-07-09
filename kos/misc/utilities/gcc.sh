#TEST: require_utility gcc "$SYSROOT_BIN_TARGET_COMMON/bin/gcc"
# Copyright (c) 2019-2023 Griefer@Work
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
#    Portions Copyright (c) 2019-2023 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

require_utility binutils "$SYSROOT_BIN_TARGET_COMMON/bin/ld"
require_utility libzlib "$PKG_CONFIG_PATH/zlib.pc"
require_utility libmpfr "$PKG_CONFIG_PATH/mpfr.pc"
require_utility libmpc "$SYSROOT_BIN_TARGET_COMMON/$TARGET_LIBPATH/libmpc.so.3"
require_utility libgmp "$PKG_CONFIG_PATH/gmp.pc"

PACKAGE_URL="https://ftp.gnu.org/gnu/gcc/gcc-12.1.0/gcc-12.1.0.tar.gz"

# Binutils and gcc are special, in that we actually don't fake being linux for them!
case "$TARGET_NAME" in
i?86)
	USED_TARGET_NAME="i686"
	;;
*)
	USED_TARGET_NAME="$TARGET_NAME"
	;;
esac

PACKAGE_HOST="$USED_TARGET_NAME-kos"
PACKAGE_TARGET="$USED_TARGET_NAME-kos"

PACKAGE_CONFIGURE=(
	--prefix=/
	--exec-prefix=/lib
	--bindir=/bin
	--sbindir=/bin
	--libexecdir=/usr/libexec
	--sysconfdir=/etc
	--sharedstatedir=/usr/com
	--localstatedir=/var
	#--runstatedir=/var/run
	--libdir=/lib
	--includedir=/usr/include
	--oldincludedir=/usr/include
	--datarootdir=/usr/share
	--datadir=/usr/share
	--infodir=/usr/share/info
	--localedir=/usr/share/locale
	--mandir=/usr/share/man
	--docdir=/usr/share/doc/gcc
	--htmldir=/usr/share/doc/gcc
	--dvidir=/usr/share/doc/gcc
	--pdfdir=/usr/share/doc/gcc
	--psdir=/usr/share/doc/gcc
	--build="$(gcc -dumpmachine)"
	--host="$PACKAGE_HOST"
	--target="$PACKAGE_TARGET"
	--disable-werror
	--with-system-zlib
	--with-gnu-ld
	--with-gnu-as
	--with-dwarf2
	--enable-gnu-unique-object
	--disable-vtable-verify
	--enable-threads=single
	--enable-targets=all # TODO
	--enable-languages=c,c++
	--enable-multiarch
	--enable-initfini-array
	--enable-__cxa_atexit
	--enable-multilib
	--enable-gnu-indirect-function
)

if false; then
	# This works perfectly, but is horribly slow... (because it has to scan so many files)
	CONFIGURE_SITE_SCANNED_FILES=(
		"configure"
		"c++tools/configure"
		"fixincludes/configure"
		"gcc/configure"
		"gnattools/configure"
		"gotools/configure"
		"intl/configure"
		"libada/configure"
		"libatomic/configure"
		"libbacktrace/configure"
		"libcc1/configure"
		"libcody/configure"
		"libcpp/configure"
		"libdecnumber/configure"
		"libffi/configure"
		"libgcc/configure"
		"libgfortran/configure"
		"libgo/configure"
		"libgomp/configure"
		"libiberty/configure"
		"libitm/configure"
		"libobjc/configure"
		"liboffloadmic/configure"
		"liboffloadmic/plugin/configure"
		"libphobos/configure"
		"libquadmath/configure"
		"libsanitizer/configure"
		"libssp/configure"
		"libstdc++-v3/configure"
		"libvtv/configure"
		"lto-plugin/configure"
		"zlib/configure"
	)
else
	PACKAGE_CONFIGURE_SITE_SCANNED_FILES=""
	_hook_config_site() {
		export CONFIG_SITE="$OPTPATH/config.site"
		cat > "$CONFIG_SITE" <<EOF
gcc_cv_func_mbstowcs_works=no
ac_cv_func_vfork_works=yes
ac_cv_func_fork_works=yes
gcc_cv_initfini_array=yes
ac_cv_func_mmap_fixed_mapped=yes
gt_cv_int_divbyzero_sigfpe=yes
libgfor_cv_have_working_stat=yes
libgfor_cv_have_unlink_open_file=yes
libgfor_cv_have_crlf=no
libgo_cv_lib_setcontext_clobbers_tls=no
gcc_cv_have_tls=yes
ac_cv_func_strncmp_works=yes
ac_cv_have_elf_style_weakref=yes
EOF
	}

	GM_HOOK_BEFORE_CONFIGURE=_hook_config_site
fi

# Prevent system headers from automatically `using namespace std;' in
# order to work around a GCC bug related to bloated debug information.
# Usually, this helps to reduce debug info sizes, but gcc breaks since
# it defines types like `remove_pointer' and `is_same' in the global
# namespace, which then causes declaration duplication errors.
PACKAGE_CCFLAGS="-D__COMPILER_HAVE_BUG_BLOATY_CXX_USING=0"

# Just like libstdc++ (which we already handle by the `defined(_GLIBCXX_SHARED)`
# in `<features.h>`), gcc also assumes that `<cstring>` defines all of the string
# function both in the `std`-namespace, as well as the global namespace.
# So we have to enable the compatibility-mode for programs that make this *FALSE*
# assumpision (though in the case of gcc, it *might* be understandable, since it
# probably believes that it is using its own libstdc++'s c-wrapper-headers (which
# *have* to define everything in the global namespace, since they just include the
# normal C header, then import all of the STDC functions into the `std` namespace))
PACKAGE_CCFLAGS="$PACKAGE_CCFLAGS -D_BROKEN_CCOMPAT_SOURCE"

# GCC is a *huge* program, so try to optimize for size
PACKAGE_CCFLAGS="$PACKAGE_CCFLAGS -Os"

# GCC's .debug_info section is a whopping 100MiB!!! - So at least try to compress it...
PACKAGE_CCFLAGS="$PACKAGE_CCFLAGS -gz"
PACKAGE_LDFLAGS="-gz"

# Because we *only* want to install gcc (and not its support libs,
# since those were already installed by the cross compiler), we
# have to set some custom targets for the make invocations.
MAKE_TARGET="all-gcc"
MAKE_TARGET_INSTALL="install-gcc"


# At one point during the build process, gcc wants to directly
# invoke a program `i686-kos-gcc` without an path prefix. I don't
# know why, but because of that we need to make that possible.
_hook_target_gcc_into_path() {
	export PATH="$PATH:$SYSROOT_BINUTILS_TARGET/bin"
}
GM_HOOK_BEFORE_MAKE=_hook_target_gcc_into_path

# Skip some files during install
INSTALL_SKIP="
/bin/i686-kos-c++
/bin/i686-kos-g++
/bin/i686-kos-gcc
/bin/i686-kos-gcc-12.1.0
/bin/i686-kos-gcc-ar
/bin/i686-kos-gcc-nm
/bin/i686-kos-gcc-ranlib
/bin/lto-dump
/lib/gcc/i686-kos/12.1.0/include/unwind.h
/lib/gcc/i686-kos/12.1.0/include/stddef.h
/lib/gcc/i686-kos/12.1.0/include/stdbool.h
/lib/gcc/i686-kos/12.1.0/include/stdarg.h
/lib/gcc/i686-kos/12.1.0/include/stdatomic.h
/lib/gcc/i686-kos/12.1.0/include/stdnoreturn.h
/lib/gcc/i686-kos/12.1.0/include/stdalign.h
/lib/gcc/i686-kos/12.1.0/include/float.h
/lib/gcc/i686-kos/12.1.0/include/iso646.h
/lib/gcc/i686-kos/12.1.0/include/varargs.h
/lib/gcc/i686-kos/12.1.0/include-fixed
/lib/gcc/i686-kos/12.1.0/install-tools
/usr/libexec/gcc/i686-kos/12.1.0/install-tools
/usr/libexec/gcc/i686-kos/12.1.0/liblto_plugin.a
/usr/libexec/gcc/i686-kos/12.1.0/liblto_plugin.la
/usr/libexec/gcc/i686-kos/12.1.0/lto1
/usr/libexec/gcc/i686-kos/12.1.0/lto-wrapper
/usr/libexec/gcc/i686-kos/12.1.0/NULL
"

# Automatically build+install using autoconf
. "$KOS_MISC/utilities/misc/gnu_make.sh"
