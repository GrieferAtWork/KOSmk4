#TEST: require_utility Xorg/libxcb "$PKG_CONFIG_PATH/xcb.pc"
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

require_utility Xorg/xcb-proto "$PKG_CONFIG_PATH/xcb-proto.pc"
require_utility Xorg/libXau    "$PKG_CONFIG_PATH/xau.pc"

# xorg-macros
. "$KOS_MISC/utilities/Xorg/misc/xorg-macros.sh"

VERSION="1.14"

SRCPATH="$KOS_ROOT/binutils/src/Xorg/libxcb-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/Xorg/libxcb-$VERSION"

require_program xsltproc

# libxcb has a dependency on a library `libpthread-stubs` that
# contains code to stub-out pthread functions not exposed from
# libc.
# However, on KOS libc already provides all of the functions
# that `libpthread-stubs` is there to stub out, so rather than
# actually building that library, we can stub _IT_ out.
install_rawfile_stdin "$PKG_CONFIG_PATH/pthread-stubs.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH

Name: pthread stubs
Description: Stubs missing from libc for standard pthread functions
Version: 0.3
Libs:
EOF


# libxcb
if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/src/.libs/libxcb.so.1.1.0" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd mkdir -p "$KOS_ROOT/binutils/src/Xorg"
			cmd cd "$KOS_ROOT/binutils/src/Xorg"
			cmd rm -rf "libxcb-$VERSION"
			download_file \
				"libxcb-$VERSION.tar.gz" \
				"https://www.x.org/releases/individual/lib/libxcb-$VERSION.tar.gz"
			cmd tar xvf "libxcb-$VERSION.tar.gz"
		fi
		cmd rm -rf "$OPTPATH"
		cmd mkdir -p "$OPTPATH"
		cmd cd "$OPTPATH"
		(
			export CC="${CROSS_PREFIX}gcc"
			export CPP="${CROSS_PREFIX}cpp"
			export CFLAGS="-ggdb"
			export CXX="${CROSS_PREFIX}g++"
			export CXXCPP="${CROSS_PREFIX}cpp"
			export CXXFLAGS="-ggdb"
			cmd bash "../../../../src/Xorg/libxcb-$VERSION/configure" \
				--prefix="$XORG_CONFIGURE_PREFIX" \
				--exec-prefix="$XORG_CONFIGURE_EXEC_PREFIX" \
				--bindir="$XORG_CONFIGURE_BINDIR" \
				--sbindir="$XORG_CONFIGURE_SBINDIR" \
				--libexecdir="$XORG_CONFIGURE_LIBEXECDIR" \
				--sysconfdir="$XORG_CONFIGURE_SYSCONFDIR" \
				--sharedstatedir="$XORG_CONFIGURE_SHAREDSTATEDIR" \
				--localstatedir="$XORG_CONFIGURE_LOCALSTATEDIR" \
				--libdir="$XORG_CONFIGURE_LIBDIR" \
				--includedir="$XORG_CONFIGURE_INCLUDEDIR" \
				--oldincludedir="$XORG_CONFIGURE_OLDINCLUDEDIR" \
				--datarootdir="$XORG_CONFIGURE_DATAROOTDIR" \
				--datadir="$XORG_CONFIGURE_DATADIR" \
				--infodir="$XORG_CONFIGURE_INFODIR" \
				--localedir="$XORG_CONFIGURE_LOCALEDIR" \
				--mandir="$XORG_CONFIGURE_MANDIR" \
				--docdir="$XORG_CONFIGURE_DOCDIR_PREFIX/libxcb" \
				--htmldir="$XORG_CONFIGURE_HTMLDIR_PREFIX/libxcb" \
				--dvidir="$XORG_CONFIGURE_DVIDIR_PREFIX/libxcb" \
				--pdfdir="$XORG_CONFIGURE_PDFDIR_PREFIX/libxcb" \
				--psdir="$XORG_CONFIGURE_PSDIR_PREFIX/libxcb" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--enable-shared      \
				--enable-static      \
				--enable-xinput      \
				--enable-xkb         \
				--enable-composite   \
				--enable-damage      \
				--enable-dpms        \
				--enable-dri2        \
				--enable-dri3        \
				--disable-ge         \
				--enable-glx         \
				--enable-present     \
				--enable-randr       \
				--enable-record      \
				--enable-render      \
				--enable-resource    \
				--enable-screensaver \
				--enable-shape       \
				--enable-shm         \
				--enable-sync        \
				--enable-xevie       \
				--enable-xfixes      \
				--enable-xfree86-dri \
				--enable-xinerama    \
				--enable-xinput      \
				--enable-xprint      \
				--disable-selinux    \
				--enable-xtest       \
				--enable-xv          \
				--enable-xvmc        \
				--with-gnu-ld
		) || exit $?
	fi
	if ! [ -f "$OPTPATH/src/.kos_patched_config" ]; then
		# Because we're acting like we're linux, libxcb thinks that KOS
		# supports linux's `HAVE_ABSTRACT_SOCKETS`, when in fact we don't.
		# Other Xorg components don't use configure to check this, but
		# instead check for `#ifdef linux` at compile-time, which correctly
		# handles the behavior on KOS.
		# However, libxcb uses configure, so we have to hack its config.h
		# to disable support for abstract sockets.
		echo ""                                        >> "$OPTPATH/src/config.h"
		echo "/* KOS doesn't actually support this */" >> "$OPTPATH/src/config.h"
		echo "#undef HAVE_ABSTRACT_SOCKETS"            >> "$OPTPATH/src/config.h"
		> "$OPTPATH/src/.kos_patched_config"
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi


# install_library name V1 V2 V3
install_library() {
	install_file /$TARGET_LIBPATH/$1.so.$2 "$OPTPATH/src/.libs/$1.so.$2.$3.$4"
	install_symlink /$TARGET_LIBPATH/$1.so.$2.$3.$4 $1.so.$2
	install_symlink /$TARGET_LIBPATH/$1.so $1.so.$2
	install_file_nodisk /$TARGET_LIBPATH/$1.a "$OPTPATH/src/.libs/$1.a"
}

# Install libraries
install_library libxcb 1 1 0
install_library libxcb-composite 0 0 0
install_library libxcb-damage 0 0 0
install_library libxcb-dpms 0 0 0
install_library libxcb-dri2 0 0 0
install_library libxcb-dri3 0 0 0
#install_library libxcb-glx 0 0 0
install_library libxcb-present 0 0 0
install_library libxcb-randr 0 1 0
install_library libxcb-record 0 0 0
install_library libxcb-render 0 0 0
install_library libxcb-res 0 0 0
install_library libxcb-screensaver 0 0 0
install_library libxcb-shape 0 0 0
install_library libxcb-shm 0 0 0
install_library libxcb-sync 1 0 0
install_library libxcb-xevie 0 0 0
install_library libxcb-xf86dri 0 0 0
install_library libxcb-xfixes 0 0 0
install_library libxcb-xinerama 0 0 0
install_library libxcb-xinput 0 1 0
install_library libxcb-xkb 1 0 0
install_library libxcb-xprint 0 0 0
#install_library libxcb-xselinux 0 0 0
install_library libxcb-xtest 0 0 0
install_library libxcb-xv 0 0 0
install_library libxcb-xvmc 0 0 0

# gen_pkg_conf    filename  name  requires  libs  [desc]
gen_pkg_conf() {
	local desc="$5"
	if [ -z "$desc" ]; then
		desc="XCB $2 Extension"
	fi
	install_rawfile_stdin "$PKG_CONFIG_PATH/$1" <<EOF
prefix=$XORG_CONFIGURE_PREFIX
exec_prefix=$XORG_CONFIGURE_EXEC_PREFIX
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: XCB $2
Description: $desc
Version: $VERSION
Requires.private: $3
Libs: $4
Cflags:
EOF
}

gen_pkg_conf "xcb-composite.pc"   "Composite"   "xcb xcb-xfixes"                    "-lxcb-composite"
gen_pkg_conf "xcb-damage.pc"      "Damage"      "xcb xcb-xfixes"                    "-lxcb-damage"
gen_pkg_conf "xcb-dpms.pc"        "DPMS"        "xcb"                               "-lxcb-dpms"
gen_pkg_conf "xcb-dri2.pc"        "DRI2"        "xcb"                               "-lxcb-dri2"
gen_pkg_conf "xcb-dri3.pc"        "DRI3"        "xcb"                               "-lxcb-dri3"
#gen_pkg_conf"xcb-glx.pc"         "GLX"         "xcb"                               "-lxcb-glx"
gen_pkg_conf "xcb-present.pc"     "Present"     "xcb xcb-randr xcb-xfixes xcb-sync" "-lxcb-present"
gen_pkg_conf "xcb-randr.pc"       "RandR"       "xcb xcb-render"                    "-lxcb-randr"
gen_pkg_conf "xcb-record.pc"      "Record"      "xcb"                               "-lxcb-record"
gen_pkg_conf "xcb-render.pc"      "Render"      "xcb"                               "-lxcb-render"
gen_pkg_conf "xcb-res.pc"         "Res"         "xcb"                               "-lxcb-res"          "XCB X-Resource Extension"
gen_pkg_conf "xcb-screensaver.pc" "Screensaver" "xcb"                               "-lxcb-screensaver"
gen_pkg_conf "xcb-shape.pc"       "Shape"       "xcb"                               "-lxcb-shape"
gen_pkg_conf "xcb-shm.pc"         "Shm"         "xcb"                               "-lxcb-shm"
gen_pkg_conf "xcb-sync.pc"        "Sync"        "xcb"                               "-lxcb-sync"
gen_pkg_conf "xcb-xevie.pc"       "Xevie"       "xcb"                               "-lxcb-xevie"
gen_pkg_conf "xcb-xf86dri.pc"     "XFree86-DRI" "xcb"                               "-lxcb-xf86dri"
gen_pkg_conf "xcb-xfixes.pc"      "XFixes"      "xcb xcb-render xcb-shape"          "-lxcb-xfixes"
gen_pkg_conf "xcb-xinerama.pc"    "Xinerama"    "xcb"                               "-lxcb-xinerama"
gen_pkg_conf "xcb-xinput.pc"      "XInput"      "xcb xcb-xfixes"                    "-lxcb-xinput"       "XCB XInput Extension (EXPERIMENTAL)"
gen_pkg_conf "xcb-xkb.pc"         "XKB"         "xcb"                               "-lxcb-xkb"          "XCB Keyboard Extension (EXPERIMENTAL)"
gen_pkg_conf "xcb-xprint.pc"      "Xprint"      "xcb"                               "-lxcb-xprint"
#gen_pkg_conf"xcb-xselinux.pc"    "SELinux"     "xcb"                               "-lxcb-xselinux"
gen_pkg_conf "xcb-xtest.pc"       "XTEST"       "xcb"                               "-lxcb-xtest"
gen_pkg_conf "xcb-xv.pc"          "Xv"          "xcb xcb-shm"                       "-lxcb-xv"
gen_pkg_conf "xcb-xvmc.pc"        "XvMC"        "xcb xcb-xv"                        "-lxcb-xvmc"

# Install headers
install_header() {
	install_rawfile \
		"$KOS_ROOT/kos/include/xcb/$1" \
		"$OPTPATH/src/$1"
}

install_rawfile "$KOS_ROOT/kos/include/xcb/xcb.h"    "$SRCPATH/src/xcb.h"
install_rawfile "$KOS_ROOT/kos/include/xcb/xcbext.h" "$SRCPATH/src/xcbext.h"
install_header "xproto.h"
install_header "bigreq.h"
install_header "xc_misc.h"
install_header "composite.h"
install_header "damage.h"
install_header "dpms.h"
install_header "dri2.h"
install_header "dri3.h"
#install_header "glx.h"
install_header "present.h"
install_header "randr.h"
install_header "record.h"
install_header "render.h"
install_header "res.h"
install_header "screensaver.h"
install_header "shape.h"
install_header "shm.h"
install_header "sync.h"
install_header "xevie.h"
install_header "xf86dri.h"
install_header "xfixes.h"
install_header "xinerama.h"
install_header "xinput.h"
install_header "xkb.h"
install_header "xprint.h"
#install_header "xselinux.h"
install_header "xtest.h"
install_header "xv.h"
install_header "xvmc.h"

# Install the PKG_CONFIG files
install_rawfile_stdin "$PKG_CONFIG_PATH/xcb.pc" <<EOF
prefix=$XORG_CONFIGURE_PREFIX
exec_prefix=$XORG_CONFIGURE_EXEC_PREFIX
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include
xcbproto_version=1.14.1

Name: XCB
Description: X-protocol C Binding
Version: $VERSION
Requires.private: xau >= 0.99.2
Libs: -lxcb
Libs.private:
Cflags:
EOF
