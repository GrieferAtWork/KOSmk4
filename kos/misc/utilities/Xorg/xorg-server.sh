#TEST: require_utility Xorg/xorg-server "$PKG_CONFIG_PATH/xorg-server.pc"
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

X_module_dir="/$TARGET_LIBPATH/xorg/modules" # Should be: ${libdir}/xorg/modules
X_log_dir="/var/log"                         # Should be: ${localstatedir}/log
X_fontrootdir="/usr/share/fonts/X11"         # Should be: ${datadir}/fonts/X11
X_xkb_path="/usr/share/X11/xkb"              # Should be: ${datadir}/X11/xkb
X_xkb_output="/usr/share/X11/xkb/compiled"   # Should be: ${datadir}/X11/xkb/compiled
X_serverconfig_path="/$TARGET_LIBPATH/xorg"  # Should be: ${libdir}/xorg
X_xkb_bin_directory="/bin"                   # Should be: ${bindir}

PACKAGE_URL="https://www.x.org/releases/individual/xserver/xorg-server-1.20.9.tar.gz"

CONFIGURE=""
CONFIGURE="$CONFIGURE --disable-listen-tcp"
CONFIGURE="$CONFIGURE --enable-listen-unix"
CONFIGURE="$CONFIGURE --enable-listen-local"
CONFIGURE="$CONFIGURE --disable-sparkle"
CONFIGURE="$CONFIGURE --enable-visibility"
CONFIGURE="$CONFIGURE --enable-composite"
CONFIGURE="$CONFIGURE --enable-mitshm"
CONFIGURE="$CONFIGURE --enable-xres"
CONFIGURE="$CONFIGURE --enable-record"
CONFIGURE="$CONFIGURE --enable-xv"
CONFIGURE="$CONFIGURE --enable-xvmc"
CONFIGURE="$CONFIGURE --enable-dga"
CONFIGURE="$CONFIGURE --enable-screensaver"
CONFIGURE="$CONFIGURE --disable-xdmcp"
CONFIGURE="$CONFIGURE --disable-xdm-auth-1"
CONFIGURE="$CONFIGURE --disable-glx"  # TODO
CONFIGURE="$CONFIGURE --disable-dri"  # TODO
CONFIGURE="$CONFIGURE --disable-dri2" # TODO
CONFIGURE="$CONFIGURE --disable-dri3" # TODO
CONFIGURE="$CONFIGURE --enable-present"
CONFIGURE="$CONFIGURE --disable-xinerama" # Multi-monitor extension
CONFIGURE="$CONFIGURE --enable-xf86vidmode"
CONFIGURE="$CONFIGURE --disable-xace" # X-Access-Control-Extension
CONFIGURE="$CONFIGURE --disable-xselinux"
CONFIGURE="$CONFIGURE --disable-xcsecurity"
CONFIGURE="$CONFIGURE --enable-dbe" # Double-Buffer-Extension
CONFIGURE="$CONFIGURE --enable-xf86bigfont"
CONFIGURE="$CONFIGURE --enable-dpms"             # Display-Power-Management-Signaling
CONFIGURE="$CONFIGURE --disable-config-udev"     # Don't have -ludev
CONFIGURE="$CONFIGURE --disable-config-udev-kms" # ???
CONFIGURE="$CONFIGURE --disable-config-hal"      # Don't have -lhal
CONFIGURE="$CONFIGURE --disable-config-wscons"   # BSD-specific thingy
CONFIGURE="$CONFIGURE --enable-xfree86-utils"
CONFIGURE="$CONFIGURE --enable-vgahw"
CONFIGURE="$CONFIGURE --enable-vbe"
CONFIGURE="$CONFIGURE --enable-int10-module"
CONFIGURE="$CONFIGURE --disable-windowswm " # Only needed for_ X-window-on-cygwin
CONFIGURE="$CONFIGURE --disable-windowsdri" # Only needed for_ X-window-on-cygwin
CONFIGURE="$CONFIGURE --enable-libdrm"
CONFIGURE="$CONFIGURE --enable-clientids"
CONFIGURE="$CONFIGURE --enable-pciaccess"
CONFIGURE="$CONFIGURE --disable-linux-acpi" # TODO
CONFIGURE="$CONFIGURE --disable-linux-apm " # TODO
CONFIGURE="$CONFIGURE --disable-systemd-logind"
CONFIGURE="$CONFIGURE --disable-suid-wrapper"
CONFIGURE="$CONFIGURE --enable-xorg"     # Yes, we want the actual server!
CONFIGURE="$CONFIGURE --disable-dmx"     # X-window proxy server? (seems related to xinerama)
CONFIGURE="$CONFIGURE --disable-xvfb"    # It´s a dummy X-window server (no need)
CONFIGURE="$CONFIGURE --disable-xnest"   # Nested windowing? (might wanna enable this in the future)
CONFIGURE="$CONFIGURE --disable-xquartz" # OS-X-specific thingy
CONFIGURE="$CONFIGURE --disable-xwayland"
CONFIGURE="$CONFIGURE --disable-xwayland-eglstream"
CONFIGURE="$CONFIGURE --disable-standalone-xpbproxy"
CONFIGURE="$CONFIGURE --disable-xwin"   # Only needed for_ X-window-on-cygwin
CONFIGURE="$CONFIGURE --disable-glamor" # ???
CONFIGURE="$CONFIGURE --disable-kdrive"
CONFIGURE="$CONFIGURE --disable-xephyr"
CONFIGURE="$CONFIGURE --disable-libunwind" # Can/will never be ported due to incompatibility with KOS´s native libunwind
CONFIGURE="$CONFIGURE --enable-xshmfence"
CONFIGURE="$CONFIGURE --disable-install-setuid" # Wouldn´t matter; We do our own install
CONFIGURE="$CONFIGURE --enable-unix-transport"  # Unix domain socket support
CONFIGURE="$CONFIGURE --disable-tcp-transport"  # Not needed
CONFIGURE="$CONFIGURE --disable-ipv6"           # Not needed
CONFIGURE="$CONFIGURE --enable-local-transport"
CONFIGURE="$CONFIGURE --disable-secure-rpc"
CONFIGURE="$CONFIGURE --enable-input-thread"
CONFIGURE="$CONFIGURE --enable-xtrans-send-fds"

CONFIGURE="$CONFIGURE --without-dtrace"
CONFIGURE="$CONFIGURE --with-int10=x86emu" # TODO: vm86 (dispatch to libvm86 from libc)
CONFIGURE="$CONFIGURE --with-vendor-name=Griefer@Work"
CONFIGURE="$CONFIGURE --with-vendor-name-short=G@W"
CONFIGURE="$CONFIGURE --with-vendor-web=https://github.com/GrieferAtWork/KOSmk4"
CONFIGURE="$CONFIGURE --with-module-dir=$X_module_dir"
CONFIGURE="$CONFIGURE --with-log-dir=$X_log_dir"
CONFIGURE="$CONFIGURE --with-builder-addr=Griefer@Work"
CONFIGURE="$CONFIGURE --with-os-name=KOS"
CONFIGURE="$CONFIGURE --with-os-vendor=Griefer@Work"
CONFIGURE="$CONFIGURE --with-fontrootdir=$X_fontrootdir"
CONFIGURE="$CONFIGURE --with-fontmiscdir=$X_fontrootdir/misc"
CONFIGURE="$CONFIGURE --with-fontotfdir=$X_fontrootdir/OTF"
CONFIGURE="$CONFIGURE --with-fontttfdir=$X_fontrootdir/TTF"
CONFIGURE="$CONFIGURE --with-fonttype1dir=$X_fontrootdir/Type1"
CONFIGURE="$CONFIGURE --with-font75dpidir=$X_fontrootdir/75dpi"
CONFIGURE="$CONFIGURE --with-font100dpidir=$X_fontrootdir/100dpi"
CONFIGURE="$CONFIGURE --with-default-font-path=\
built-ins,$X_fontrootdir/misc/,$X_fontrootdir/ttf/,$X_fontrootdir/otf/,\
$X_fontrootdir/Type1/,$X_fontrootdir/100dpi/,$X_fontrootdir/75dpi/"

CONFIGURE="$CONFIGURE --with-xkb-path=$X_xkb_path"
CONFIGURE="$CONFIGURE --with-xkb-output=$X_xkb_output"
CONFIGURE="$CONFIGURE --with-fallback-input-driver=" # ???
CONFIGURE="$CONFIGURE --with-default-xkb-rules=base"
CONFIGURE="$CONFIGURE --with-default-xkb-model=pc105" # ???
CONFIGURE="$CONFIGURE --with-default-xkb-layout=us"
CONFIGURE="$CONFIGURE --with-default-xkb-variant="
CONFIGURE="$CONFIGURE --with-default-xkb-options="
CONFIGURE="$CONFIGURE --with-serverconfig-path=$X_serverconfig_path"
CONFIGURE="$CONFIGURE --with-xkb-bin-directory=$X_xkb_bin_directory"
CONFIGURE="$CONFIGURE --without-systemd-daemon"
CONFIGURE="$CONFIGURE --with-sha1=libcrypto"

# Automatically build+install using autoconf
. "$KOS_MISC/utilities/misc/gnu_make.sh"

# Make sure that the /var/log directory has been created on-disk
install_mkdir $X_log_dir
