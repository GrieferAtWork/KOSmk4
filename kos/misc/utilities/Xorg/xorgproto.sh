#TEST: require_utility Xorg/xorgproto "$PKG_CONFIG_PATH/xproto.pc"
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

VERSION="2020.1"

SRCPATH="$KOS_ROOT/binutils/src/Xorg/xorgproto-$VERSION"

if ! [ -f "$SRCPATH/configure" ]; then
	cmd mkdir -p "$KOS_ROOT/binutils/src/Xorg"
	cmd cd "$KOS_ROOT/binutils/src/Xorg"
	cmd rm -rf "xorgproto-$VERSION"
	download_file "xorgproto-$VERSION.tar.gz" \
		"https://www.x.org/releases/individual/proto/xorgproto-$VERSION.tar.gz"
	cmd tar xvf "xorgproto-$VERSION.tar.gz"
fi
apply_patch "$SRCPATH" "$KOS_PATCHES/xorgproto-$VERSION.patch"

# Install headers
install_headers() {
	cmd cd "$2"
	for FILE in *; do
		if [[ "$FILE" == "meson.build" ]]; then
			:
		elif [[ "$FILE" == "Xpoll.h.in" ]]; then
			install_rawfile "$1/Xpoll.h" "$2/Xpoll.h.in"
		elif [ -d "$2/$FILE" ]; then
			install_headers "$1/$FILE" "$2/$FILE"
		else
			install_rawfile "$1/$FILE" "$2/$FILE"
		fi
	done
}

install_headers "$KOS_ROOT/kos/include" "$SRCPATH/include"

make_pkg_config() {
	USED_NAME="$3"
	USED_DESC="$4"
	if test -z "$USED_DESC"; then
		USED_DESC="${USED_NAME} extension headers"
		USED_NAME="${USED_NAME}Proto"
	fi
	if test -z "$5"; then
		install_rawfile_stdin "$PKG_CONFIG_PATH/$1" <<EOF
prefix=$XORG_CONFIGURE_PREFIX
exec_prefix=$XORG_CONFIGURE_EXEC_PREFIX
includedir=$KOS_ROOT/kos/include

Name: $USED_NAME
Description: $USED_DESC
Version: $2
Cflags:
EOF
	else
		install_rawfile_stdin "$PKG_CONFIG_PATH/$1" <<EOF
prefix=$XORG_CONFIGURE_PREFIX
exec_prefix=$XORG_CONFIGURE_EXEC_PREFIX
includedir=$KOS_ROOT/kos/include

Name: $USED_NAME
Description: $USED_DESC
Version: $2
$5
Cflags:
EOF
	fi
}

# Install the PKG_CONFIG files
make_pkg_config "applewmproto.pc"     "1.4.2"  "AppleWM"
make_pkg_config "bigreqsproto.pc"     "1.1.2"  "BigReqs"
make_pkg_config "compositeproto.pc"   "0.4.2"  "CompositeExt" "Composite extension headers"
make_pkg_config "damageproto.pc"      "1.2.1"  "Damage"
make_pkg_config "dmxproto.pc"         "2.3.1"  "DMX"
make_pkg_config "dpmsproto.pc"        "1.2"    "DPMS"
make_pkg_config "dri2proto.pc"        "2.8"    "DRI2"
make_pkg_config "dri3proto.pc"        "1.2"    "DRI3"
make_pkg_config "evieproto.pc"        "1.1.1"  "EvIEExt" "EvIE extension headers"
make_pkg_config "fixesproto.pc"       "5.0"    "FixesProto" "X Fixes extension headers"
make_pkg_config "fontcacheproto.pc"   "0.1.3"  "Fontcache"
make_pkg_config "fontsproto.pc"       "2.1.3"  "Fonts"
make_pkg_config "glproto.pc"          "1.4.17" "GL"
make_pkg_config "inputproto.pc"       "2.3.2"  "Input"
make_pkg_config "kbproto.pc"          "1.0.7"  "KB"
make_pkg_config "lg3dproto.pc"        "5.0"    "Lg3dProto" "LGE extension headers"
make_pkg_config "presentproto.pc"     "1.2"    "Present"
make_pkg_config "printproto.pc"       "1.0.5"  "Print" "" "Requires.private: xau"
make_pkg_config "randrproto.pc"       "1.6.0"  "Randr"
make_pkg_config "recordproto.pc"      "1.14.2" "Record"
make_pkg_config "renderproto.pc"      "0.11.1" "Render"
make_pkg_config "resourceproto.pc"    "1.2.0"  "Resource"
make_pkg_config "scrnsaverproto.pc"   "1.2.3"  "ScrnSaver"
make_pkg_config "trapproto.pc"        "3.4.3"  "Trap" "" "Requires: xt"
make_pkg_config "videoproto.pc"       "2.3.3"  "Video"
make_pkg_config "windowswmproto.pc"   "1.0.4"  "WindowsWM"
make_pkg_config "xcalibrateproto.pc"  "0.1.0"  "XCalibrate" "XCalibrate extension headers"
make_pkg_config "xcmiscproto.pc"      "1.2.2"  "XCMisc"
make_pkg_config "xextproto.pc"        "7.3.0"  "XExt"
make_pkg_config "xf86bigfontproto.pc" "1.2.0"  "XF86BigFont"
make_pkg_config "xf86dgaproto.pc"     "2.1"    "XF86DGA"
install_rawfile_stdin "$PKG_CONFIG_PATH/xf86driproto.pc" <<EOF
prefix=$XORG_CONFIGURE_PREFIX
exec_prefix=$XORG_CONFIGURE_EXEC_PREFIX
includedir=$KOS_ROOT/kos/include

Name: XF86DRIProto
Description: XF86DRI extension headers
Version: 2.1.1
Cflags: -I$KOS_ROOT/kos/include/X11/dri
EOF
make_pkg_config "xf86miscproto.pc"    "0.9.3"  "XF86Misc"
make_pkg_config "xf86rushproto.pc"    "1.1.2"  "XF86Rush"
make_pkg_config "xf86vidmodeproto.pc" "2.3.1"  "XF86VidMode"
make_pkg_config "xineramaproto.pc"    "1.2.1"  "Xinerama"
make_pkg_config "xproxymngproto.pc"   "1.0.3"  "XProxyManagementProtocol" "X Proxy Management Protocol headers"

# NOTE: Install this one last!
make_pkg_config "xproto.pc"           "7.0.32" "Xproto" "Xproto headers"
