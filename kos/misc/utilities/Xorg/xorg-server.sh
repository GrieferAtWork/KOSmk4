#TEST: require_utility Xorg/xorg-server "$PKG_CONFIG_PATH/xorg-server.pc"
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

# Prototypes
require_utility Xorg/xorgproto "$PKG_CONFIG_PATH/xproto.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/randrproto.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/renderproto.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/xextproto.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/inputproto.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/kbproto.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/fontsproto.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/fixesproto.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/damageproto.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/xcmiscproto.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/bigreqsproto.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/presentproto.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/xtrans.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/compositeproto.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/recordproto.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/resourceproto.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/scrnsaverproto.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/videoproto.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/xf86bigfontproto.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/xf86vidmodeproto.pc"
#equire_utility Xorg/xorgproto "$PKG_CONFIG_PATH/xf86dgaproto.pc"

# Libraries
require_utility libpciaccess      "$PKG_CONFIG_PATH/pciaccess.pc"
require_utility libdrm            "$PKG_CONFIG_PATH/libdrm.pc"
require_utility openssl           "$PKG_CONFIG_PATH/openssl.pc"
require_utility libpixman         "$PKG_CONFIG_PATH/pixman-1.pc"
require_utility Xorg/libXfont2    "$PKG_CONFIG_PATH/xfont2.pc"
require_utility Xorg/libxkbfile   "$PKG_CONFIG_PATH/xkbfile.pc"
require_utility Xorg/libXau       "$PKG_CONFIG_PATH/xau.pc"
require_utility Xorg/libxshmfence "$PKG_CONFIG_PATH/xshmfence.pc"

# Run-time dependencies
require_utility Xorg/xkbcomp          "$PKG_CONFIG_PATH/xkbcomp.pc"
require_utility Xorg/xkeyboard-config "$PKG_CONFIG_PATH/xkeyboard-config.pc"

# xorg-macros
. "$KOS_MISC/utilities/Xorg/misc/xorg-macros.sh"

VERSION="1.20.9"

SRCPATH="$KOS_ROOT/binutils/src/Xorg/xorg-server-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/Xorg/xorg-server-$VERSION"

X_module_dir="$XORG_CONFIGURE_LIBDIR/xorg/modules"      # Should be: ${libdir}/xorg/modules
X_log_dir="$XORG_CONFIGURE_LOCALSTATEDIR/log"           # Should be: ${localstatedir}/log
X_fontrootdir="$XORG_CONFIGURE_DATADIR/fonts/X11"       # Should be: ${datadir}/fonts/X11
X_xkb_path="$XORG_CONFIGURE_DATADIR/X11/xkb"            # Should be: ${datadir}/X11/xkb
X_xkb_output="$XORG_CONFIGURE_DATADIR/X11/xkb/compiled" # Should be: ${datadir}/X11/xkb/compiled
X_serverconfig_path="$XORG_CONFIGURE_LIBDIR/xorg"       # Should be: ${libdir}/xorg
X_xkb_bin_directory="$XORG_CONFIGURE_BINDIR"            # Should be: ${bindir}


# xorg-server
if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/hw/xfree86/Xorg" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src/Xorg"
			cmd rm -rf "xorg-server-$VERSION"
			download_file \
				"xorg-server-$VERSION.tar.gz" \
				"https://www.x.org/releases/individual/xserver/xorg-server-$VERSION.tar.gz"
			cmd tar xvf "xorg-server-$VERSION.tar.gz"
		fi
		cmd cd "$SRCPATH"
		apply_patch "$SRCPATH" "$KOS_PATCHES/xorg-server-$VERSION.patch"
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
			cmd bash "../../../../src/Xorg/xorg-server-$VERSION/configure" \
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
				--docdir="$XORG_CONFIGURE_DOCDIR_PREFIX/xorg-server" \
				--htmldir="$XORG_CONFIGURE_HTMLDIR_PREFIX/xorg-server" \
				--dvidir="$XORG_CONFIGURE_DVIDIR_PREFIX/xorg-server" \
				--pdfdir="$XORG_CONFIGURE_PDFDIR_PREFIX/xorg-server" \
				--psdir="$XORG_CONFIGURE_PSDIR_PREFIX/xorg-server" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
\
				--disable-docs \
				--disable-devel-docs \
				--disable-unit-tests \
\
				--disable-static \
				--enable-shared \
\
				--disable-listen-tcp \
				--enable-listen-unix \
				--enable-listen-local \
				--disable-sparkle \
				--enable-visibility \
				--enable-composite \
				--enable-mitshm \
				--enable-xres \
				--enable-record \
				--enable-xv \
				--enable-xvmc \
				--enable-dga \
				--enable-screensaver \
				--disable-xdmcp \
				--disable-xdm-auth-1 \
				--disable-glx `# TODO` \
				--disable-dri `# TODO` \
				--disable-dri2 `# TODO` \
				--disable-dri3 `# TODO` \
				--disable-present `# TODO` \
				--disable-xinerama `# Multi-monitor extension` \
				--enable-xf86vidmode \
				--disable-xace `# X-Access-Control-Extension` \
				--disable-xselinux \
				--disable-xcsecurity \
				--enable-dbe `# Double-Buffer-Extension` \
				--enable-xf86bigfont \
				--enable-dpms `# Display-Power-Management-Signaling ` \
				--disable-config-udev     `# Don´t have -ludev` \
				--disable-config-udev-kms `# ???` \
				--disable-config-hal      `# Don´t have -lhal` \
				--disable-config-wscons   `# BSD-specific thingy` \
				--enable-xfree86-utils \
				--enable-vgahw \
				--enable-vbe \
				--enable-int10-module \
				--disable-windowswm  `# Only needed for_ X-window-on-cygwin` \
				--disable-windowsdri `# Only needed for_ X-window-on-cygwin` \
				--enable-libdrm \
				--enable-clientids \
				--enable-pciaccess \
				--disable-linux-acpi `# TODO` \
				--disable-linux-apm  `# TODO` \
				--disable-systemd-logind \
				--disable-suid-wrapper \
				--enable-xorg `# Yes, we want the actual server!` \
				--disable-dmx `# X-window proxy server? (seems related to xinerama)` \
				--disable-xvfb `# It´s a dummy X-window server (no need)` \
				--disable-xnest `# Nested windowing? (might wanna enable this in the future)` \
				--disable-xquartz `# OS-X-specific thingy` \
				--disable-xwayland \
				--disable-xwayland-eglstream \
				--disable-standalone-xpbproxy \
				--disable-xwin `# Only needed for_ X-window-on-cygwin` \
				--disable-glamor `# ???` \
				--disable-kdrive \
				--disable-xephyr \
				--enable-libunwind \
				--enable-xshmfence \
				--disable-install-setuid `# Wouldn´t matter; We do our own install` \
				--enable-unix-transport `# Unix domain socket support` \
				--disable-tcp-transport `# Not needed` \
				--disable-ipv6 `# Not needed` \
				--enable-local-transport \
				--disable-secure-rpc \
				--enable-input-thread \
				--enable-xtrans-send-fds \
\
				--without-doxygen \
				--without-xmlto \
				--without-fop \
				--with-gnu-ld \
				--without-dtrace \
				--with-int10=x86emu `# TODO: vm86 (dispatch to libvm86 from libc)` \
				--with-vendor-name="Griefer@Work" \
				--with-vendor-name-short="G@W" \
				--with-vendor-web="https://github.com/GrieferAtWork/KOSmk4" \
				--with-module-dir="$X_module_dir" \
				--with-log-dir="$X_log_dir" \
				--with-builder-addr="Griefer@Work" \
				--with-os-name="KOS" \
				--with-os-vendor="Griefer@Work" \
				--with-fontrootdir="$X_fontrootdir" \
				--with-fontmiscdir="$X_fontrootdir/misc" \
				--with-fontotfdir="$X_fontrootdir/OTF" \
				--with-fontttfdir="$X_fontrootdir/TTF" \
				--with-fonttype1dir="$X_fontrootdir/Type1" \
				--with-font75dpidir="$X_fontrootdir/75dpi" \
				--with-font100dpidir="$X_fontrootdir/100dpi" \
				--with-default-font-path="\
built-ins,$X_fontrootdir/misc/,$X_fontrootdir/ttf/,$X_fontrootdir/otf/,\
$X_fontrootdir/Type1/,$X_fontrootdir/100dpi/,$X_fontrootdir/75dpi/" \
				--with-xkb-path="$X_xkb_path" \
				--with-xkb-output="$X_xkb_output" \
				--with-fallback-input-driver="" `# ???` \
				--with-default-xkb-rules="base" \
				--with-default-xkb-model="pc105" `# ???` \
				--with-default-xkb-layout="us" \
				--with-default-xkb-variant="" \
				--with-default-xkb-options="" \
				--with-serverconfig-path="$X_serverconfig_path" \
				--with-xkb-bin-directory="$X_xkb_bin_directory" \
				--without-systemd-daemon \
				--with-sha1=libcrypto
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

exit 0


# This file is needed in order to run `autoreconf` on X server extensions
# From what I understand, properly configured extensions should be able to
# find this file via `${datarootdir}/aclocal/xorg-server.m4`, where `datarootdir`
# originates from the PKG_CONFIG file above.
install_rawfile \
	"$BINUTILS_SYSROOT/usr/local/share/aclocal/xorg-server.m4" \
	"$SRCPATH/xorg-server.m4"


# Install libraries and executables
install_file    $X_xkb_bin_directory/cvt                "$OPTPATH/hw/xfree86/utils/cvt/cvt"
install_file    $X_xkb_bin_directory/gtf                "$OPTPATH/hw/xfree86/utils/gtf/gtf"
install_symlink $X_xkb_bin_directory/X                  "Xorg"
install_file    $X_xkb_bin_directory/Xorg               "$OPTPATH/hw/xfree86/Xorg"
install_file    $X_module_dir/extensions/libdbe.so      "$OPTPATH/hw/xfree86/dixmods/.libs/libdbe.so"
install_file    $X_module_dir/extensions/libextmod.so   "$OPTPATH/hw/xfree86/dixmods/extmod/.libs/libextmod.so"
install_file    $X_module_dir/extensions/librecord.so   "$OPTPATH/hw/xfree86/dixmods/.libs/librecord.so"
install_file    $X_module_dir/libexa.so                 "$OPTPATH/hw/xfree86/exa/.libs/libexa.so"
install_file    $X_module_dir/libfb.so                  "$OPTPATH/hw/xfree86/dixmods/.libs/libfb.so"
install_file    $X_module_dir/libfbdevhw.so             "$OPTPATH/hw/xfree86/fbdevhw/.libs/libfbdevhw.so"
install_file    $X_module_dir/libint10.so               "$OPTPATH/hw/xfree86/int10/.libs/libint10.so"
install_file    $X_module_dir/libshadow.so              "$OPTPATH/hw/xfree86/dixmods/.libs/libshadow.so"
install_file    $X_module_dir/libshadowfb.so            "$OPTPATH/hw/xfree86/shadowfb/.libs/libshadowfb.so"
install_file    $X_module_dir/libvbe.so                 "$OPTPATH/hw/xfree86/vbe/.libs/libvbe.so"
install_file    $X_module_dir/libvgahw.so               "$OPTPATH/hw/xfree86/vgahw/.libs/libvgahw.so"
install_file    $X_module_dir/libwfb.so                 "$OPTPATH/hw/xfree86/dixmods/.libs/libwfb.so"
install_file    $X_module_dir/libxaa.so                 "$OPTPATH/hw/xfree86/xaa/.libs/libxaa.so"
install_file    $X_module_dir/multimedia/bt829_drv.so   "$OPTPATH/hw/xfree86/i2c/.libs/bt829_drv.so"
install_file    $X_module_dir/multimedia/fi1236_drv.so  "$OPTPATH/hw/xfree86/i2c/.libs/fi1236_drv.so"
install_file    $X_module_dir/multimedia/msp3430_drv.so "$OPTPATH/hw/xfree86/i2c/.libs/msp3430_drv.so"
install_file    $X_module_dir/multimedia/tda8425_drv.so "$OPTPATH/hw/xfree86/i2c/.libs/tda8425_drv.so"
install_file    $X_module_dir/multimedia/tda9850_drv.so "$OPTPATH/hw/xfree86/i2c/.libs/tda9850_drv.so"
install_file    $X_module_dir/multimedia/tda9885_drv.so "$OPTPATH/hw/xfree86/i2c/.libs/tda9885_drv.so"
install_file    $X_module_dir/multimedia/uda1380_drv.so "$OPTPATH/hw/xfree86/i2c/.libs/uda1380_drv.so"
install_file    $X_serverconfig_path/protocol.txt       "$SRCPATH/dix/protocol.txt"
install_file    $X_xkb_output/README.compiled           "$SRCPATH/xkb/README.compiled"
install_mkdir   $X_log_dir


# Install system headers
INCPATH="$KOS_ROOT/kos/include/xorg"
install_header() {
	install_rawfile "$INCPATH/$1" "$SRCPATH/include/$1"
}
install_rawfile "$INCPATH/xorg-server.h" "$OPTPATH/include/xorg-server.h"
install_header "XIstubs.h"
install_header "Xprintf.h"
install_header "callback.h"
install_header "client.h"
install_header "closestr.h"
install_header "closure.h"
install_header "colormap.h"
install_header "colormapst.h"
install_header "cursor.h"
install_header "cursorstr.h"
install_header "dix.h"
install_header "dixaccess.h"
install_header "dixevents.h"
install_header "dixfont.h"
install_header "dixfontstr.h"
install_header "dixgrabs.h"
install_header "dixstruct.h"
install_header "events.h"
install_header "exevents.h"
install_header "extension.h"
install_header "extinit.h"
install_header "extnsionst.h"
install_header "gc.h"
install_header "gcstruct.h"
install_header "globals.h"
install_header "hotplug.h"
install_header "input.h"
install_header "inputstr.h"
install_header "list.h"
install_header "misc.h"
install_header "miscstruct.h"
install_header "opaque.h"
install_header "optionstr.h"
install_header "os.h"
install_header "pixmap.h"
install_header "pixmapstr.h"
install_header "privates.h"
install_header "property.h"
install_header "propertyst.h"
install_header "ptrveloc.h"
install_header "region.h"
install_header "regionstr.h"
install_header "registry.h"
install_header "resource.h"
install_header "rgb.h"
install_header "screenint.h"
install_header "scrnintstr.h"
install_header "selection.h"
install_header "servermd.h"
install_header "site.h"
install_header "swaprep.h"
install_header "swapreq.h"
install_header "validate.h"
install_header "window.h"
install_header "windowstr.h"
install_header "xkbfile.h"
install_header "xkbrules.h"
install_header "xkbsrv.h"
install_header "xkbstr.h"
install_header "xserver-properties.h"

# Headers from extensions
install_rawfile "$INCPATH/geext.h"          "$SRCPATH/Xext/geext.h"
install_rawfile "$INCPATH/geint.h"          "$SRCPATH/Xext/geint.h"
install_rawfile "$INCPATH/shmint.h"         "$SRCPATH/Xext/shmint.h"
install_rawfile "$INCPATH/syncsdk.h"        "$SRCPATH/Xext/syncsdk.h"
install_rawfile "$INCPATH/xvdix.h"          "$SRCPATH/Xext/xvdix.h"
install_rawfile "$INCPATH/xvmcext.h"        "$SRCPATH/Xext/xvmcext.h"
install_rawfile "$INCPATH/compositeext.h"   "$SRCPATH/composite/compositeext.h"
install_rawfile "$INCPATH/dbestruct.h"      "$SRCPATH/dbe/dbestruct.h"
install_rawfile "$INCPATH/exa.h"            "$SRCPATH/exa/exa.h"
install_rawfile "$INCPATH/fb.h"             "$SRCPATH/fb/fb.h"
install_rawfile "$INCPATH/fboverlay.h"      "$SRCPATH/fb/fboverlay.h"
install_rawfile "$INCPATH/fbpict.h"         "$SRCPATH/fb/fbpict.h"
install_rawfile "$INCPATH/fbrop.h"          "$SRCPATH/fb/fbrop.h"
install_rawfile "$INCPATH/wfbrename.h"      "$SRCPATH/fb/wfbrename.h"
install_rawfile "$INCPATH/compiler.h"       "$SRCPATH/hw/xfree86/common/compiler.h"
install_rawfile "$INCPATH/fourcc.h"         "$SRCPATH/hw/xfree86/common/fourcc.h"
install_rawfile "$INCPATH/vidmodeproc.h"    "$SRCPATH/hw/xfree86/common/vidmodeproc.h"
install_rawfile "$INCPATH/xf86.h"           "$SRCPATH/hw/xfree86/common/xf86.h"
install_rawfile "$INCPATH/xf86Module.h"     "$SRCPATH/hw/xfree86/common/xf86Module.h"
install_rawfile "$INCPATH/xf86Opt.h"        "$SRCPATH/hw/xfree86/common/xf86Opt.h"
install_rawfile "$INCPATH/xf86Optionstr.h"  "$SRCPATH/hw/xfree86/common/xf86Optionstr.h"
install_rawfile "$INCPATH/xf86PciInfo.h"    "$SRCPATH/hw/xfree86/common/xf86PciInfo.h"
install_rawfile "$INCPATH/xf86Priv.h"       "$SRCPATH/hw/xfree86/common/xf86Priv.h"
install_rawfile "$INCPATH/xf86Privstr.h"    "$SRCPATH/hw/xfree86/common/xf86Privstr.h"
install_rawfile "$INCPATH/xf86VGAarbiter.h" "$SRCPATH/hw/xfree86/common/xf86VGAarbiter.h"
install_rawfile "$INCPATH/xf86Xinput.h"     "$SRCPATH/hw/xfree86/common/xf86Xinput.h"
install_rawfile "$INCPATH/xf86cmap.h"       "$SRCPATH/hw/xfree86/common/xf86cmap.h"
install_rawfile "$INCPATH/xf86fbman.h"      "$SRCPATH/hw/xfree86/common/xf86fbman.h"
install_rawfile "$INCPATH/xf86sbusBus.h"    "$SRCPATH/hw/xfree86/common/xf86sbusBus.h"
install_rawfile "$INCPATH/xf86str.h"        "$SRCPATH/hw/xfree86/common/xf86str.h"
install_rawfile "$INCPATH/xf86xv.h"         "$SRCPATH/hw/xfree86/common/xf86xv.h"
install_rawfile "$INCPATH/xf86xvmc.h"       "$SRCPATH/hw/xfree86/common/xf86xvmc.h"
install_rawfile "$INCPATH/xf86xvpriv.h"     "$SRCPATH/hw/xfree86/common/xf86xvpriv.h"
install_rawfile "$INCPATH/xisb.h"           "$SRCPATH/hw/xfree86/common/xisb.h"
install_rawfile "$INCPATH/xorgVersion.h"    "$SRCPATH/hw/xfree86/common/xorgVersion.h"
install_rawfile "$INCPATH/edid.h"           "$SRCPATH/hw/xfree86/ddc/edid.h"
install_rawfile "$INCPATH/xf86DDC.h"        "$SRCPATH/hw/xfree86/ddc/xf86DDC.h"
install_rawfile "$INCPATH/dgaproc.h"        "$SRCPATH/hw/xfree86/dixmods/extmod/dgaproc.h"
install_rawfile "$INCPATH/fbdevhw.h"        "$SRCPATH/hw/xfree86/fbdevhw/fbdevhw.h"
install_rawfile "$INCPATH/bt829.h"          "$SRCPATH/hw/xfree86/i2c/bt829.h"
install_rawfile "$INCPATH/fi1236.h"         "$SRCPATH/hw/xfree86/i2c/fi1236.h"
install_rawfile "$INCPATH/i2c_def.h"        "$SRCPATH/hw/xfree86/i2c/i2c_def.h"
install_rawfile "$INCPATH/msp3430.h"        "$SRCPATH/hw/xfree86/i2c/msp3430.h"
install_rawfile "$INCPATH/tda8425.h"        "$SRCPATH/hw/xfree86/i2c/tda8425.h"
install_rawfile "$INCPATH/tda9850.h"        "$SRCPATH/hw/xfree86/i2c/tda9850.h"
install_rawfile "$INCPATH/tda9885.h"        "$SRCPATH/hw/xfree86/i2c/tda9885.h"
install_rawfile "$INCPATH/uda1380.h"        "$SRCPATH/hw/xfree86/i2c/uda1380.h"
install_rawfile "$INCPATH/xf86i2c.h"        "$SRCPATH/hw/xfree86/i2c/xf86i2c.h"
install_rawfile "$INCPATH/xf86int10.h"      "$SRCPATH/hw/xfree86/int10/xf86int10.h"
install_rawfile "$INCPATH/xf86Crtc.h"       "$SRCPATH/hw/xfree86/modes/xf86Crtc.h"
install_rawfile "$INCPATH/xf86Modes.h"      "$SRCPATH/hw/xfree86/modes/xf86Modes.h"
install_rawfile "$INCPATH/xf86RandR12.h"    "$SRCPATH/hw/xfree86/modes/xf86RandR12.h"
install_rawfile "$INCPATH/xf86Rename.h"     "$SRCPATH/hw/xfree86/modes/xf86Rename.h"
install_rawfile "$INCPATH/xf86Pci.h"        "$SRCPATH/hw/xfree86/os-support/bus/xf86Pci.h"
install_rawfile "$INCPATH/xf86_OSlib.h"     "$SRCPATH/hw/xfree86/os-support/xf86_OSlib.h"
install_rawfile "$INCPATH/xf86_OSproc.h"    "$SRCPATH/hw/xfree86/os-support/xf86_OSproc.h"
install_rawfile "$INCPATH/xf86Optrec.h"     "$SRCPATH/hw/xfree86/parser/xf86Optrec.h"
install_rawfile "$INCPATH/xf86Parser.h"     "$SRCPATH/hw/xfree86/parser/xf86Parser.h"
install_rawfile "$INCPATH/BT.h"             "$SRCPATH/hw/xfree86/ramdac/BT.h"
install_rawfile "$INCPATH/IBM.h"            "$SRCPATH/hw/xfree86/ramdac/IBM.h"
install_rawfile "$INCPATH/TI.h"             "$SRCPATH/hw/xfree86/ramdac/TI.h"
install_rawfile "$INCPATH/xf86Cursor.h"     "$SRCPATH/hw/xfree86/ramdac/xf86Cursor.h"
install_rawfile "$INCPATH/xf86RamDac.h"     "$SRCPATH/hw/xfree86/ramdac/xf86RamDac.h"
install_rawfile "$INCPATH/shadowfb.h"       "$SRCPATH/hw/xfree86/shadowfb/shadowfb.h"
install_rawfile "$INCPATH/vbe.h"            "$SRCPATH/hw/xfree86/vbe/vbe.h"
install_rawfile "$INCPATH/vbeModes.h"       "$SRCPATH/hw/xfree86/vbe/vbeModes.h"
install_rawfile "$INCPATH/vgaHW.h"          "$SRCPATH/hw/xfree86/vgahw/vgaHW.h"
install_rawfile "$INCPATH/xaa.h"            "$SRCPATH/hw/xfree86/xaa/xaa.h"
install_rawfile "$INCPATH/xaalocal.h"       "$SRCPATH/hw/xfree86/xaa/xaalocal.h"
install_rawfile "$INCPATH/xaarop.h"         "$SRCPATH/hw/xfree86/xaa/xaarop.h"
install_rawfile "$INCPATH/mi.h"             "$SRCPATH/mi/mi.h"
install_rawfile "$INCPATH/mibstore.h"       "$SRCPATH/mi/mibstore.h"
install_rawfile "$INCPATH/micmap.h"         "$SRCPATH/mi/micmap.h"
install_rawfile "$INCPATH/micoord.h"        "$SRCPATH/mi/micoord.h"
install_rawfile "$INCPATH/mifillarc.h"      "$SRCPATH/mi/mifillarc.h"
install_rawfile "$INCPATH/mifpoly.h"        "$SRCPATH/mi/mifpoly.h"
install_rawfile "$INCPATH/migc.h"           "$SRCPATH/mi/migc.h"
install_rawfile "$INCPATH/miline.h"         "$SRCPATH/mi/miline.h"
install_rawfile "$INCPATH/mioverlay.h"      "$SRCPATH/mi/mioverlay.h"
install_rawfile "$INCPATH/mipointer.h"      "$SRCPATH/mi/mipointer.h"
install_rawfile "$INCPATH/mipointrst.h"     "$SRCPATH/mi/mipointrst.h"
install_rawfile "$INCPATH/mispans.h"        "$SRCPATH/mi/mispans.h"
install_rawfile "$INCPATH/mistruct.h"       "$SRCPATH/mi/mistruct.h"
install_rawfile "$INCPATH/miwideline.h"     "$SRCPATH/mi/miwideline.h"
install_rawfile "$INCPATH/mizerarc.h"       "$SRCPATH/mi/mizerarc.h"
install_rawfile "$INCPATH/damage.h"         "$SRCPATH/miext/damage/damage.h"
install_rawfile "$INCPATH/damagestr.h"      "$SRCPATH/miext/damage/damagestr.h"
install_rawfile "$INCPATH/shadow.h"         "$SRCPATH/miext/shadow/shadow.h"
install_rawfile "$INCPATH/misync.h"         "$SRCPATH/miext/sync/misync.h"
install_rawfile "$INCPATH/misyncstr.h"      "$SRCPATH/miext/sync/misyncstr.h"
install_rawfile "$INCPATH/randrstr.h"       "$SRCPATH/randr/randrstr.h"
install_rawfile "$INCPATH/rrtransform.h"    "$SRCPATH/randr/rrtransform.h"
install_rawfile "$INCPATH/glyphstr.h"       "$SRCPATH/render/glyphstr.h"
install_rawfile "$INCPATH/mipict.h"         "$SRCPATH/render/mipict.h"
install_rawfile "$INCPATH/picture.h"        "$SRCPATH/render/picture.h"
install_rawfile "$INCPATH/picturestr.h"     "$SRCPATH/render/picturestr.h"
install_rawfile "$INCPATH/xfixes.h"         "$SRCPATH/xfixes/xfixes.h"





# Install the PKG_CONFIG file
install_rawfile_stdin "$PKG_CONFIG_PATH/xorg-server.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include
datarootdir=$BINUTILS_SYSROOT/usr/local/share
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
moduledir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH/xorg/modules
sdkdir=$KOS_ROOT/kos/include/xorg
sysconfigdir=$KOS_ROOT/bin/$TARGET_NAME-kos/usr/share/X11/xorg.conf.d

abi_ansic=0.4
abi_videodrv=12.0
abi_xinput=16.0
abi_extension=6.0

Name: xorg-server
Description: Modular X.Org X Server
Version: $VERSION
Requires.private: xproto >= 7.0.22 randrproto >= 1.2.99.3 renderproto >= 0.11 xextproto >= 7.1.99 inputproto >= 2.1.99.6 kbproto >= 1.0.3 fontsproto pixman-1 >= 0.21.8 videoproto pciaccess >= 0.12.901
Cflags: -I$KOS_ROOT/kos/include/xorg -fvisibility=hidden
Libs:
EOF
