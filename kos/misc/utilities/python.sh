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

PYTHON_VERSION_MAJOR="2"
PYTHON_VERSION_MINOR="7"
PYTHON_VERSION_PATCH="16"
PYTHON_VERSION="$PYTHON_VERSION_MAJOR.$PYTHON_VERSION_MINOR.$PYTHON_VERSION_PATCH"
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
			--with-signal-module \
			--with-threads \
			--with-wctype-functions \
			--with-libm=-lm \
			--with-libc=-lc \
			--with-computed-gotos
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

PYTHON_EXE="$OPTPATH/python"
if [ -f "$OPTPATH/python.exe" ]; then
	PYTHON_EXE="$OPTPATH/python.exe"
fi

# Install the python core
install_file /bin/python "$PYTHON_EXE"
PYTHON_LIB="libpython${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}"

install_file /$TARGET_LIBPATH/${PYTHON_LIB}.so.1.0 "$OPTPATH/${PYTHON_LIB}.so.1.0"
install_symlink /$TARGET_LIBPATH/${PYTHON_LIB}.so ${PYTHON_LIB}.so.1.0
install_file_nodisk /$TARGET_LIBPATH/${PYTHON_LIB}.a "$OPTPATH/${PYTHON_LIB}.a"

# Install modules under `/lib/python2.7/[os.py...]'
install_path_hardcopy /$TARGET_LIBPATH/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR} "${SRCPATH}/Lib"
install_path /$TARGET_LIBPATH/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}/lib-dynload "${OPTPATH}/build/lib.linux2-${TARGET_NAME}-${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}"

