#TEST: require_utility Xorg/xorg-server "$PKG_CONFIG_PATH/xorg-server.pc"
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

CONFIGURE=(
	"--disable-listen-tcp"
	"--enable-listen-unix"
	"--enable-listen-local"
	"--disable-sparkle"
	"--enable-visibility"
	"--enable-composite"
	"--enable-mitshm"
	"--enable-xres"
	"--enable-record"
	"--enable-xv"
	"--enable-xvmc"
	"--enable-dga"
	"--enable-screensaver"
	"--disable-xdmcp"
	"--disable-xdm-auth-1"
	"--disable-glx"  # TODO
	"--disable-dri"  # TODO
	"--disable-dri2" # TODO
	"--disable-dri3" # TODO
	"--enable-present"
	"--disable-xinerama" # Multi-monitor extension
	"--enable-xf86vidmode"
	"--disable-xace" # X-Access-Control-Extension
	"--disable-xselinux"
	"--disable-xcsecurity"
	"--enable-dbe" # Double-Buffer-Extension
	"--enable-xf86bigfont"
	"--enable-dpms"             # Display-Power-Management-Signaling
	"--disable-config-udev"     # Don't have -ludev
	"--disable-config-udev-kms" # ???
	"--disable-config-hal"      # Don't have -lhal
	"--disable-config-wscons"   # BSD-specific thingy
	"--enable-xfree86-utils"
	"--enable-vgahw"
	"--enable-vbe"
	"--enable-int10-module"
	"--disable-windowswm " # Only needed for_ X-window-on-cygwin
	"--disable-windowsdri" # Only needed for_ X-window-on-cygwin
	"--enable-libdrm"
	"--enable-clientids"
	"--enable-pciaccess"
	"--disable-linux-acpi" # TODO
	"--disable-linux-apm " # TODO
	"--disable-systemd-logind"
	"--disable-suid-wrapper"
	"--enable-xorg"     # Yes, we want the actual server!
	"--disable-dmx"     # X-window proxy server? (seems related to xinerama)
	"--disable-xvfb"    # It´s a dummy X-window server (no need)
	"--disable-xnest"   # Nested windowing? (might wanna enable this in the future)
	"--disable-xquartz" # OS-X-specific thingy
	"--disable-xwayland"
	"--disable-xwayland-eglstream"
	"--disable-standalone-xpbproxy"
	"--disable-xwin"   # Only needed for_ X-window-on-cygwin
	"--disable-glamor" # ???
	"--disable-kdrive"
	"--disable-xephyr"
	"--disable-libunwind" # Can/will never be ported due to incompatibility with KOS´s native libunwind
	"--enable-xshmfence"
	"--disable-install-setuid" # Wouldn´t matter; We do our own install
	"--enable-unix-transport"  # Unix domain socket support
	"--disable-tcp-transport"  # Not needed
	"--disable-ipv6"           # Not needed
	"--enable-local-transport"
	"--disable-secure-rpc"
	"--enable-input-thread"
	"--enable-xtrans-send-fds"
)

CONFIGURE+=(
	"--without-dtrace"
	"--with-int10=x86emu" # TODO: vm86 (dispatch to libvm86 from libc)
	"--with-vendor-name=Griefer@Work"
	"--with-vendor-name-short=G@W"
	"--with-vendor-web=https://github.com/GrieferAtWork/KOSmk4"
	"--with-module-dir=$X_module_dir"
	"--with-log-dir=$X_log_dir"
	"--with-builder-addr=Griefer@Work"
	"--with-os-name=KOS"
	"--with-os-vendor=Griefer@Work"
	"--with-fontrootdir=$X_fontrootdir"
	"--with-fontmiscdir=$X_fontrootdir/misc"
	"--with-fontotfdir=$X_fontrootdir/OTF"
	"--with-fontttfdir=$X_fontrootdir/TTF"
	"--with-fonttype1dir=$X_fontrootdir/Type1"
	"--with-font75dpidir=$X_fontrootdir/75dpi"
	"--with-font100dpidir=$X_fontrootdir/100dpi"
)

CONFIGURE+=(
	"--with-default-font-path=\
built-ins,$X_fontrootdir/misc/,$X_fontrootdir/ttf/,$X_fontrootdir/otf/,\
$X_fontrootdir/Type1/,$X_fontrootdir/100dpi/,$X_fontrootdir/75dpi/"
)

CONFIGURE+=(
	"--with-xkb-path=$X_xkb_path"
	"--with-xkb-output=$X_xkb_output"
	"--with-fallback-input-driver=" # ???
	"--with-default-xkb-rules=base"
	"--with-default-xkb-model=pc105" # ???
	"--with-default-xkb-layout=us"
	"--with-default-xkb-variant="
	"--with-default-xkb-options="
	"--with-serverconfig-path=$X_serverconfig_path"
	"--with-xkb-bin-directory=$X_xkb_bin_directory"
	"--without-systemd-daemon"
	"--with-sha1=libcrypto"
)


# Automatically build+install using autoconf
. "$KOS_MISC/utilities/misc/gnu_make.sh"

# Make sure that the /var/log directory has been created on-disk
install_mkdir $X_log_dir
