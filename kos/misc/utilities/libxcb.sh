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

# depends: xcb-proto
# depends: libXau

# xorg-macros
. "$KOS_MISC/utilities/misc/xorg-macros.sh"

VERSION="1.8.1"

SRCPATH="$KOS_ROOT/binutils/src/x/libxcb-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/x/libxcb-$VERSION"

require_program xsltproc

# libxcb has a dependency on a library `libpthread-stubs` that
# contains code to stub-out pthread functions not exposed from
# libc.
# However, on KOS libc already provides all of the functions
# that `libpthread-stubs` is there to stub out, so rather than
# actually building that library, we can stub _IT_ out.
if ! [ -f "$PKG_CONFIG_PATH/pthread-stubs.pc" ]; then
	cmd mkdir -p "$PKG_CONFIG_PATH"
	cat > "$PKG_CONFIG_PATH/pthread-stubs.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH

Name: pthread stubs
Description: Stubs missing from libc for standard pthread functions
Version: 0.3
Libs:
EOF
fi

# libxcb
if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/src/.libs/libxcb.so.1.1.0" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src/x"
			cmd rm -rf "libxcb-$VERSION"
			download_file \
				"libxcb-$VERSION.tar.gz" \
				"https://www.x.org/releases/X11R7.7/src/everything/libxcb-$VERSION.tar.gz"
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
			cmd bash "../../../../src/x/libxcb-$VERSION/configure" \
				--prefix="/" \
				--exec-prefix="/" \
				--bindir="/bin" \
				--sbindir="/bin" \
				--libexecdir="/libexec" \
				--sysconfdir="/etc" \
				--sharedstatedir="/usr/com" \
				--localstatedir="/var" \
				--libdir="/$TARGET_LIBPATH" \
				--includedir="/usr/include" \
				--oldincludedir="/usr/include" \
				--datarootdir="/usr/share" \
				--datadir="/usr/share" \
				--infodir="/usr/share/info" \
				--localedir="/usr/share/locale" \
				--mandir="/usr/share/man" \
				--docdir="/usr/share/doc/libxcb" \
				--htmldir="/usr/share/doc/libxcb" \
				--dvidir="/usr/share/doc/libxcb" \
				--pdfdir="/usr/share/doc/libxcb" \
				--psdir="/usr/share/doc/libxcb" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--enable-shared \
				--enable-static \
				--enable-xinput \
				--enable-xkb \
				--with-gnu-ld
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi


# Install the PKG_CONFIG files
if ! [ -f "$PKG_CONFIG_PATH/xcb.pc" ]; then
	cmd mkdir -p "$PKG_CONFIG_PATH"
	cat > "$PKG_CONFIG_PATH/xcb.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include
xcbproto_version=1.7.1

Name: XCB
Description: X-protocol C Binding
Version: $VERSION
Requires.private: pthread-stubs xau >= 0.99.2
Libs: -lxcb
Libs.private:
Cflags:
EOF
fi

# gen_pkg_conf    filename  name  requires  libs  [desc]
gen_pkg_conf() {
	if ! [ -f "$PKG_CONFIG_PATH/$1" ]; then
		cmd mkdir -p "$PKG_CONFIG_PATH"
		local desc="$5"
		if [ -z "$desc" ]; then
			desc="XCB $2 Extension"
		fi
		cat > "$PKG_CONFIG_PATH/$1" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: XCB $2
Description: $desc
Version: $VERSION
Requires: $3
Libs: $4
Cflags:
EOF
	fi
}

gen_pkg_conf "xcb-composite.pc"   "Composite"   "xcb xcb-xfixes"   "-lxcb-composite"
gen_pkg_conf "xcb-damage.pc"      "Damage"      "xcb xcb-xfixes"   "-lxcb-damage"
gen_pkg_conf "xcb-dpms.pc"        "DPMS"        "xcb"              "-lxcb-dpms"
gen_pkg_conf "xcb-dri2.pc"        "DRI2"        "xcb"              "-lxcb-dri2"
gen_pkg_conf "xcb-glx.pc"         "GLX"         "xcb"              "-lxcb-glx"
gen_pkg_conf "xcb-randr.pc"       "RandR"       "xcb"              "-lxcb-randr"
gen_pkg_conf "xcb-record.pc"      "Record"      "xcb"              "-lxcb-record"
gen_pkg_conf "xcb-render.pc"      "Render"      "xcb"              "-lxcb-render"
gen_pkg_conf "xcb-res.pc"         "Res"         "xcb"              "-lxcb-res"          "XCB X-Resource Extension"
gen_pkg_conf "xcb-screensaver.pc" "Screensaver" "xcb"              "-lxcb-screensaver"
gen_pkg_conf "xcb-shape.pc"       "Shape"       "xcb"              "-lxcb-shape"
gen_pkg_conf "xcb-shm.pc"         "Shm"         "xcb"              "-lxcb-shm"
gen_pkg_conf "xcb-sync.pc"        "Sync"        "xcb"              "-lxcb-sync"
gen_pkg_conf "xcb-xevie.pc"       "Xevie"       "xcb"              "-lxcb-xevie"
gen_pkg_conf "xcb-xf86dri.pc"     "XFree86-DRI" "xcb"              "-lxcb-xf86dri"
gen_pkg_conf "xcb-xfixes.pc"      "XFixes"      "xcb xcb-render xcb-shape"  "-lxcb-xfixes"
gen_pkg_conf "xcb-xinerama.pc"    "Xinerama"    "xcb"              "-lxcb-xinerama"
gen_pkg_conf "xcb-xinput.pc"      "XInput"      "xcb"              "-lxcb-xinput"       "XCB XInput Extension (EXPERIMENTAL)"
gen_pkg_conf "xcb-xkb.pc"         "XKB"         "xcb"              "-lxcb-xkb"          "XCB Keyboard Extension (EXPERIMENTAL)"
gen_pkg_conf "xcb-xprint.pc"      "Xprint"      "xcb"              "-lxcb-xprint"
#gen_pkg_conf"xcb-xselinux.pc"    "SELinux"     "xcb"              "-lxcb-xselinux"
gen_pkg_conf "xcb-xtest.pc"       "XTEST"       "xcb"              "-lxcb-xtest"
gen_pkg_conf "xcb-xv.pc"          "Xv"          "xcb xcb-shm"      "-lxcb-xv"
gen_pkg_conf "xcb-xvmc.pc"        "XvMC"        "xcb xcb-xv"       "-lxcb-xvmc"

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
install_library libxcb-glx 0 0 0
install_library libxcb-randr 0 1 0
install_library libxcb-record 0 0 0
install_library libxcb-render 0 0 0
install_library libxcb-res 0 0 0
install_library libxcb-screensaver 0 0 0
install_library libxcb-shape 0 0 0
install_library libxcb-shm 0 0 0
install_library libxcb-sync 0 0 0
install_library libxcb-xevie 0 0 0
install_library libxcb-xf86dri 0 0 0
install_library libxcb-xfixes 0 0 0
install_library libxcb-xinerama 0 0 0
install_library libxcb-xinput 0 0 0
install_library libxcb-xkb 0 0 0
install_library libxcb-xprint 0 0 0
#install_library libxcb-xselinux 0 0 0
install_library libxcb-xtest 0 0 0
install_library libxcb-xv 0 0 0
install_library libxcb-xvmc 0 0 0

# Install headers
install_header() {
	install_rawfile \
		"$KOS_ROOT/kos/include/xcb/$1" \
		"$OPTPATH/src/$1"
}

install_rawfile "$KOS_ROOT/kos/include/xcb/xcb.h" "$SRCPATH/src/xcb.h"
install_rawfile "$KOS_ROOT/kos/include/xcb/xcbext.h" "$SRCPATH/src/xcbext.h"
install_header "xproto.h"
install_header "bigreq.h"
install_header "xc_misc.h"
install_header "composite.h"
install_header "damage.h"
install_header "dpms.h"
install_header "dri2.h"
install_header "glx.h"
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
