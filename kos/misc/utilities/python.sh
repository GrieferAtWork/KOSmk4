# Copyright (c) 2019-2020 Griefer@Work
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
#    Portions Copyright (c) 2019-2020 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

# depends libffi
# depends libexpat
# depends libzlib   (optional)

PYTHON_VERSION_MAJOR="2"
PYTHON_VERSION_MINOR="7"
PYTHON_VERSION_PATCH="16"
PYTHON_VERSION="${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}.${PYTHON_VERSION_PATCH}"
SRCPATH="$KOS_ROOT/binutils/src/Python-$PYTHON_VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/Python-$PYTHON_VERSION"
if [ "$MODE_FORCE_MAKE" == yes ] || {
	! [ -f "$OPTPATH/python" ] &&
	! [ -f "$OPTPATH/python.exe" ]
}; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src"
			download_file \
				"Python-$PYTHON_VERSION.tar.xz" \
				https://www.python.org/ftp/python/$PYTHON_VERSION/Python-$PYTHON_VERSION.tar.xz
			cmd tar xvf "Python-$PYTHON_VERSION.tar.xz"
		fi
		rm -rf "$OPTPATH" > /dev/null 2>&1
		cmd mkdir -p "$OPTPATH"
		cmd cd "$OPTPATH"
		export CC="${CROSS_PREFIX}gcc"
		export CPP="${CROSS_PREFIX}cpp"
		export CXX="${CROSS_PREFIX}g++"
		export CFLAGS="-ggdb"
		export CXXFLAGS="-ggdb"
		cat > "$OPTPATH/config.site" <<EOF
ac_cv_file__dev_ptmx=no
ac_cv_file__dev_ptc=no
ac_cv_broken_sem_getvalue=no
EOF
		export CONFIG_SITE="$OPTPATH/config.site"
		cmd bash "../../../src/Python-$PYTHON_VERSION/configure" \
			--prefix="/" \
			--exec-prefix="/" \
			--bindir="/bin" \
			--sbindir="/bin" \
			--sysconfdir="/etc" \
			--libexecdir="/usr/libexec" \
			--sharedstatedir="/usr/com" \
			--localstatedir="/usr/var" \
			--libdir="/$TARGET_LIBPATH" \
			--includedir="/usr/include" \
			--oldincludedir="/usr/include" \
			--datarootdir="/usr/share" \
			--infodir="/usr/share/info" \
			--localedir="/usr/share/locale" \
			--mandir="/usr/share/man" \
			--build="$(gcc -dumpmachine)" \
			--host="$TARGET_NAME-linux-gnu" \
			--target="$TARGET_NAME-linux-gnu" \
			--enable-shared \
			--enable-ipv6 \
			--enable-unicode=ucs4 \
			--with-suffix="" \
			--with-system-ffi=yes \
			--with-system-expat \
			--with-signal-module \
			--with-threads \
			--with-wctype-functions \
			--with-libm="" \
			--with-libc=-lc \
			--with-computed-gotos
	fi
	cmd cd "$OPTPATH"
	# This is needed to appease python's annoying build system, which
	# doesn't seem to understand that due to multi-arch (which is something
	# that's quite standartized now-a-days), KOS (just like linux) has
	# multiple system include paths ('/kos/include/i386-kos/' and '/kos/include/')
	# As such, it only searches the later, and even more annoyingly, it also
	# searches it for a line that starts with `#define LIBFFI_H`...
	# Anyways. Make it happy by defining that file while we're running make...
	cat > "$KOS_ROOT/kos/include/ffi.h" <<EOF
#include <$TARGET_INCPATH/ffi.h>
#if 0
#define LIBFFI_H
#endif
EOF
	# Another annoying thing with python+libffi: Python checks which libraries
	# exist in a specific order, in which `libffi_convenience` comes before
	# the actual `libffi`. Problem here is that ffi_convenience only comes as
	# a static library, so if we let python see it, we'd end up linking libffi
	# statically (which would completely counteract the whole idea behind using
	# the system libffi, rather than python's builtin, static one)
	mv	"$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH/libffi_convenience.a" \
		"$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH/.libffi_convenience.a" \
		2>&1 > /dev/null
	make -j $MAKE_PARALLEL_COUNT
	error=$?
	unlink "$KOS_ROOT/kos/include/ffi.h" 2>&1 > /dev/null
	mv	"$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH/.libffi_convenience.a" \
		"$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH/libffi_convenience.a" \
		2>&1 > /dev/null
	[ $error == 0 ] || {
		echo "ERROR: Command failed 'make -j $MAKE_PARALLEL_COUNT' -> '$error'";
		exit $error;
	}
fi

MODPATH="${OPTPATH}/build/lib.linux2-${TARGET_NAME}-${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}"

# Python doesn't want to built `imageop.so`, unless the host
# (that is: the machine you're calling this build script from)
# is a 32-bit machine.
# Whilst I don't know what's the deal with this module and only
# being meant to be built for 32-bit machines, I can't stand the
# idea that Python once again spits the idea of cross-compiling
# in its face, so I'm just going to built this module manually,
# if it wasn't already built.
if ! [ -f "$MODPATH/imageop.so" ] && [ -f "$SRCPATH/Modules/imageop.c" ]; then
	cmd cd "$OPTPATH"
	vcmd "${CROSS_PREFIX}gcc" \
		-shared -fno-strict-aliasing -ggdb -DNDEBUG \
		-g -fwrapv -O3 -Wall -Wstrict-prototypes -L. \
		-I"$SRCPATH/Include" -I. \
		-o "$MODPATH/imageop.so" "$SRCPATH/Modules/imageop.c" \
		-lpython${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}
fi

PYTHON_EXE="$OPTPATH/python"
if [ -f "$OPTPATH/python.exe" ]; then
	PYTHON_EXE="$OPTPATH/python.exe"
fi

# Install the PKG_CONFIG file
if ! [ -f "$PKG_CONFIG_PATH/python-${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}.pc" ]; then
	cmd mkdir -p "$PKG_CONFIG_PATH"
	cat > "$PKG_CONFIG_PATH/python-${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: Python
Description: Python library
Requires:
Version: ${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}
Libs.private: -ldl
Libs: -lpython${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}
Cflags: -I$KOS_ROOT/kos/include/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}
EOF
fi

# Install the python core
install_file /bin/python "$PYTHON_EXE"
PYTHON_LIB="libpython${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}"

install_file /$TARGET_LIBPATH/${PYTHON_LIB}.so.1.0 "$OPTPATH/${PYTHON_LIB}.so.1.0"
install_symlink /$TARGET_LIBPATH/${PYTHON_LIB}.so ${PYTHON_LIB}.so.1.0
install_file_nodisk /$TARGET_LIBPATH/${PYTHON_LIB}.a "$OPTPATH/${PYTHON_LIB}.a"

# Install modules under `/lib/python2.7/[os.py...]'
install_path_hardcopy /$TARGET_LIBPATH/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR} "${SRCPATH}/Lib"
install_path /$TARGET_LIBPATH/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}/lib-dynload "$MODPATH"

# Install headers
INCPATH="$KOS_ROOT/kos/include/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}"
install_header() {
	install_rawfile "$INCPATH/$1" "$SRCPATH/include/$1"
}

if [ "$TARGET_NAME" == "i386" ] || [ "$TARGET_NAME" == "x86_64" ]; then
	if [ "$TARGET_NAME" == "i386" ]; then
		install_rawfile \
			"$KOS_ROOT/kos/include/$TARGET_INCPATH/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}/pyconfig32.h" \
			"$OPTPATH/pyconfig.h"
	else
		install_rawfile \
			"$KOS_ROOT/kos/include/$TARGET_INCPATH/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}/pyconfig64.h" \
			"$OPTPATH/pyconfig.h"
	fi
	if ! [ -f "$KOS_ROOT/kos/include/$TARGET_INCPATH/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}/pyconfig.h" ]; then
		echo "Installing file $KOS_ROOT/kos/include/$TARGET_INCPATH/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}/pyconfig.h"
		cat > "$KOS_ROOT/kos/include/$TARGET_INCPATH/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}/pyconfig.h" <<EOF
#ifndef _I386_KOS_PYTHON${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR}_PYCONFIG_H
#define _I386_KOS_PYTHON${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR}_PYCONFIG_H 1

#include <hybrid/host.h>

#ifdef __x86_64__
#include "pyconfig64.h"
#else /* __x86_64__ */
#include "pyconfig32.h"
#endif /* !__x86_64__ */

#endif /* !_I386_KOS_PYTHON${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR}_PYCONFIG_H */
EOF
	else
		echo "Installing file $KOS_ROOT/kos/include/$TARGET_INCPATH/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}/pyconfig.h (up to date)"
	fi
else
	install_rawfile \
		"$KOS_ROOT/kos/include/$TARGET_INCPATH/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}/pyconfig.h" \
		"$OPTPATH/pyconfig.h"
fi
if ! [ -f "$KOS_ROOT/kos/include/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}/pyconfig.h" ]; then
	echo "Installing file $KOS_ROOT/kos/include/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}/pyconfig.h"
	cat > "$KOS_ROOT/kos/include/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}/pyconfig.h" <<EOF
#ifndef _PYTHON${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR}_PYCONFIG_H
#define _PYTHON${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR}_PYCONFIG_H 1
#include <python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}/pyconfig.h>
#endif /* !_KOS_PYTHON${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR}_PYCONFIG_H */
EOF
else
	echo "Installing file $KOS_ROOT/kos/include/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}/pyconfig.h (up to date)"
fi

install_header "Python-ast.h"
install_header "Python.h"
install_header "abstract.h"
install_header "asdl.h"
install_header "ast.h"
install_header "bitset.h"
install_header "boolobject.h"
install_header "bufferobject.h"
install_header "bytearrayobject.h"
install_header "bytes_methods.h"
install_header "bytesobject.h"
install_header "cStringIO.h"
install_header "cellobject.h"
install_header "ceval.h"
install_header "classobject.h"
install_header "cobject.h"
install_header "code.h"
install_header "codecs.h"
install_header "compile.h"
install_header "complexobject.h"
install_header "datetime.h"
install_header "descrobject.h"
install_header "dictobject.h"
install_header "dtoa.h"
install_header "enumobject.h"
install_header "errcode.h"
install_header "eval.h"
install_header "fileobject.h"
install_header "floatobject.h"
install_header "frameobject.h"
install_header "funcobject.h"
install_header "genobject.h"
install_header "graminit.h"
install_header "grammar.h"
install_header "import.h"
install_header "intobject.h"
install_header "intrcheck.h"
install_header "iterobject.h"
install_header "listobject.h"
install_header "longintrepr.h"
install_header "longobject.h"
install_header "marshal.h"
install_header "memoryobject.h"
install_header "metagrammar.h"
install_header "methodobject.h"
install_header "modsupport.h"
install_header "moduleobject.h"
install_header "node.h"
install_header "object.h"
install_header "objimpl.h"
install_header "opcode.h"
install_header "osdefs.h"
install_header "parsetok.h"
install_header "patchlevel.h"
install_header "pgen.h"
install_header "pgenheaders.h"
install_header "py_curses.h"
install_header "pyarena.h"
install_header "pycapsule.h"
install_header "pyctype.h"
install_header "pydebug.h"
install_header "pyerrors.h"
install_header "pyexpat.h"
install_header "pyfpe.h"
install_header "pygetopt.h"
install_header "pymacconfig.h"
install_header "pymactoolbox.h"
install_header "pymath.h"
install_header "pymem.h"
install_header "pyport.h"
install_header "pystate.h"
install_header "pystrcmp.h"
install_header "pystrtod.h"
install_header "pythonrun.h"
install_header "pythread.h"
install_header "rangeobject.h"
install_header "setobject.h"
install_header "sliceobject.h"
install_header "stringobject.h"
install_header "structmember.h"
install_header "structseq.h"
install_header "symtable.h"
install_header "sysmodule.h"
install_header "timefuncs.h"
install_header "token.h"
install_header "traceback.h"
install_header "tupleobject.h"
install_header "ucnhash.h"
install_header "unicodeobject.h"
install_header "warnings.h"
install_header "weakrefobject.h"
