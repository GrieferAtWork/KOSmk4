#TEST: require_utility tcc "$SYSROOT_BIN_TARGET_COMMON/bin/tcc"
# Copyright (c) 2019-2025 Griefer@Work
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
#    Portions Copyright (c) 2019-2025 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

if [ -z "$VERSION" ]; then VERSION="0.9.27"; fi

SRCPATH="$KOS_ROOT/binutils/src/tcc-$VERSION"
OPTPATH="$SYSROOT_BINUTILS_TARGET/opt/tcc-$VERSION"
if [ "$MODE_FORCE_MAKE" == yes ] || \
   [ "$MODE_FORCE_CONF" == yes ] || ! \
   [ -f "$OPTPATH/$TARGET_NAME-tcc" ]; then
	set_archpath
	if ! [ -f "$SRCPATH/configure" ]; then
		cmd cd "$KOS_ROOT/binutils/src"
		download_file \
			"tcc-$VERSION.tar.bz2" \
			http://download.savannah.gnu.org/releases/tinycc/tcc-$VERSION.tar.bz2
		cmd tar jxvf "tcc-$VERSION.tar.bz2"
	fi
	rm -rf "$OPTPATH" > /dev/null 2>&1
	cmd cp -R "$SRCPATH" "$SYSROOT_BINUTILS_TARGET/opt/"
	cmd cd "$OPTPATH"
	apply_patch "$OPTPATH" "$KOS_PATCHES/tcc-$VERSION.patch"
	cmd bash configure \
		--with-libgcc \
		--with-selinux \
		--cpu="$TARGET_NAME" \
		--enable-cross \
		--cross-prefix="$CROSS_PREFIX" \
		--bindir="/bin" \
		--includedir="/usr/include" \
		--sysincludepaths="/usr/include/${TARGET_NAME}-kos:/usr/include" \
		--libpaths="/usr/$TARGET_LIBPATH:/$TARGET_LIBPATH" \
		--crtprefix="/usr/$TARGET_LIBPATH" \
		--elfinterp="/$TARGET_LIBPATH/libdl.so" \
		--config-mingw32=no
	cat > config-extra.mak <<EOF
NATIVE_DEFINES += -DTCC_TARGET_KOS
NATIVE_DEFINES += -DCONFIG_TCCDIR="\\"/usr/$TARGET_LIBPATH\\""
NATIVE_DEFINES += -DCONFIG_LDDIR="\\"$TARGET_LIBPATH\\""
EOF
	cmd make cross-$TARGET_NAME $TARGET_NAME-libtcc1-usegcc=yes
	cat > "$OPTPATH/hello-world.c" <<EOF
/* A simple hello-world example which you can compile & run from inside of KOS:
 * $ cd /usr/src
 * $ tcc hello-world.c
 * $ ./a.out
 * >> Hello World
 */
extern int printf(char const *format, ...);

int main() {
	printf("Hello %s\n", "World");
	return 0;
}
EOF
fi

install_file /bin/tcc                                    "$OPTPATH/$TARGET_NAME-tcc"
install_file /usr/$TARGET_LIBPATH/$TARGET_NAME-libtcc1.a "$OPTPATH/$TARGET_NAME-libtcc1.a"
install_file /usr/$TARGET_LIBPATH/crt0S.o                "${KOS_ROOT}/bin/${TARGET_NAME}-kos/$TARGET_LIBPATH/crt0S.o"
install_file /usr/$TARGET_LIBPATH/crt0.o                 "${KOS_ROOT}/bin/${TARGET_NAME}-kos/$TARGET_LIBPATH/crt0.o"
install_file /usr/src/hello-world.c                      "$OPTPATH/hello-world.c"
