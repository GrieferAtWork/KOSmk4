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

# depends xkbcomp

. "$KOS_MISC/utilities/misc/xorg-macros.sh"

# We need a secondary version of "/bin/xkbcomp" that is compiled
# for the host machine, as the process of making xkeyboard-config
# files inbokes the xkbcomp compiler.
# This is where we download+configure+make that second variant,
# as well as modify our $PATH such that it can be found below.
# Note that despite this, KOS still needs a secondary xkbcomp
# compiler at runtime, as xorg-server will execv("/bin/xkbcomp")
# in order to compile keyboard maps.
. "$KOS_MISC/utilities/misc/host-xkbcomp.sh"


# These two you have to install yourself on your host
# On cygwin, they're found in:
#    - intltool-update: intltool-0.51.0-1
#    - iconv:           libiconv-1.14-2
require_program intltool-update
require_program iconv

VERSION="2.6"

SRCPATH="$KOS_ROOT/binutils/src/x/xkeyboard-config-$VERSION"
OPTPATH="$BINUTILS_SYSROOT/opt/x/xkeyboard-config-$VERSION"

if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/rules/base" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src/x"
			cmd rm -rf "xkeyboard-config-$VERSION"
			download_file \
				"xkeyboard-config-$VERSION.tar.gz" \
				"https://www.x.org/releases/X11R7.7/src/everything/xkeyboard-config-$VERSION.tar.gz"
			cmd tar xvf "xkeyboard-config-$VERSION.tar.gz"
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
			cmd bash "../../../../src/x/xkeyboard-config-$VERSION/configure" \
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
				--docdir="/usr/share/doc/xkeyboard-config" \
				--htmldir="/usr/share/doc/xkeyboard-config" \
				--dvidir="/usr/share/doc/xkeyboard-config" \
				--pdfdir="/usr/share/doc/xkeyboard-config" \
				--psdir="/usr/share/doc/xkeyboard-config" \
				--build="$(gcc -dumpmachine)" \
				--host="$TARGET_NAME-linux-gnu" \
				--with-xkb-base="/usr/share/X11/xkb" \
				--without-libiconv-prefix \
				--without-libintl-prefix \
				--with-gnu-ld
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

# Install the PKG_CONFIG file
if ! [ -f "$PKG_CONFIG_PATH/xkeyboard-config.pc" ]; then
	cmd mkdir -p "$PKG_CONFIG_PATH"
	cat > "$PKG_CONFIG_PATH/xkeyboard-config.pc" <<EOF
prefix=/
datarootdir=/usr/share
datadir=/usr/share
xkb_base=/usr/share/X11/xkb

Name: XKeyboardConfig
Description: X Keyboard configuration data
Version: $VERSION
EOF
fi


# my_install_file WHERE [WHAT]
my_install_file() {
	DST="/usr/share/X11/xkb$1"
	SRC="$2"
	if test -z "$SRC"; then
		SRC="$SRCPATH/${1#/}"
	fi
	install_file "$DST" "$SRC"
}

my_install_file /compat/accessx
my_install_file /compat/basic
my_install_file /compat/caps
my_install_file /compat/complete
my_install_file /compat/iso9995
my_install_file /compat/japan
my_install_file /compat/ledcaps
my_install_file /compat/lednum
my_install_file /compat/ledscroll
my_install_file /compat/level5
my_install_file /compat/misc
my_install_file /compat/mousekeys
my_install_file /compat/olpc
my_install_file /compat/pc
my_install_file /compat/pc98
my_install_file /compat/README
my_install_file /compat/xfree86
my_install_file /compat/xtest
my_install_file /compat.dir                   "$SRCPATH/compat/compat.dir"
my_install_file /geometry/amiga
my_install_file /geometry/ataritt
my_install_file /geometry/chicony
my_install_file /geometry/dell
my_install_file /geometry/digital_vndr/lk
my_install_file /geometry/digital_vndr/pc
my_install_file /geometry/digital_vndr/unix
my_install_file /geometry/everex
my_install_file /geometry/fujitsu
my_install_file /geometry/hhk
my_install_file /geometry/hp
my_install_file /geometry/keytronic
my_install_file /geometry/kinesis
my_install_file /geometry/macintosh
my_install_file /geometry/microsoft
my_install_file /geometry/nec
my_install_file /geometry/nokia
my_install_file /geometry/northgate
my_install_file /geometry/pc
my_install_file /geometry/README
my_install_file /geometry/sanwa
my_install_file /geometry/sgi_vndr/indigo
my_install_file /geometry/sgi_vndr/indy
my_install_file /geometry/sgi_vndr/O2
my_install_file /geometry/sony
my_install_file /geometry/sun
my_install_file /geometry/thinkpad
my_install_file /geometry/typematrix
my_install_file /geometry/winbook
my_install_file /geometry.dir                 "$SRCPATH/geometry/geometry.dir"
my_install_file /keycodes/aliases
my_install_file /keycodes/amiga
my_install_file /keycodes/ataritt
my_install_file /keycodes/digital_vndr/lk
my_install_file /keycodes/digital_vndr/pc
my_install_file /keycodes/empty
my_install_file /keycodes/evdev
my_install_file /keycodes/fujitsu
my_install_file /keycodes/hp
my_install_file /keycodes/ibm
my_install_file /keycodes/macintosh
my_install_file /keycodes/README
my_install_file /keycodes/sgi_vndr/indigo
my_install_file /keycodes/sgi_vndr/indy
my_install_file /keycodes/sgi_vndr/iris
my_install_file /keycodes/sony
my_install_file /keycodes/sun
my_install_file /keycodes/xfree86
my_install_file /keycodes/xfree98
my_install_file /keycodes.dir                 "$SRCPATH/keycodes/keycodes.dir"
my_install_file /rules/base                   "$OPTPATH/rules/base"
my_install_file /rules/base.extras.xml        "$OPTPATH/rules/base.extras.xml"
my_install_file /rules/base.lst               "$OPTPATH/rules/base.lst"
my_install_file /rules/base.xml               "$OPTPATH/rules/base.xml"
my_install_file /rules/evdev.extras.xml       "$OPTPATH/rules/evdev.extras.xml"
my_install_file /rules/evdev.lst              "$OPTPATH/rules/evdev.lst"
my_install_file /rules/evdev.xml              "$OPTPATH/rules/evdev.xml"
my_install_file /rules/README
my_install_file /rules/xfree98
my_install_file /rules/xkb.dtd
my_install_file /symbols/ad
my_install_file /symbols/af
my_install_file /symbols/al
my_install_file /symbols/altwin
my_install_file /symbols/am
my_install_file /symbols/apl
my_install_file /symbols/ara
my_install_file /symbols/at
my_install_file /symbols/az
my_install_file /symbols/ba
my_install_file /symbols/bd
my_install_file /symbols/be
my_install_file /symbols/bg
my_install_file /symbols/br
my_install_file /symbols/brai
my_install_file /symbols/bt
my_install_file /symbols/bw
my_install_file /symbols/by
my_install_file /symbols/ca
my_install_file /symbols/capslock
my_install_file /symbols/cd
my_install_file /symbols/ch
my_install_file /symbols/cm
my_install_file /symbols/cn
my_install_file /symbols/compose
my_install_file /symbols/ctrl
my_install_file /symbols/cz
my_install_file /symbols/de
my_install_file /symbols/digital_vndr/lk
my_install_file /symbols/digital_vndr/pc
my_install_file /symbols/digital_vndr/us
my_install_file /symbols/digital_vndr/vt
my_install_file /symbols/dk
my_install_file /symbols/ee
my_install_file /symbols/empty
my_install_file /symbols/epo
my_install_file /symbols/es
my_install_file /symbols/et
my_install_file /symbols/eurosign
my_install_file /symbols/fi
my_install_file /symbols/fo
my_install_file /symbols/fr
my_install_file /symbols/fujitsu_vndr/jp
my_install_file /symbols/fujitsu_vndr/us
my_install_file /symbols/gb
my_install_file /symbols/ge
my_install_file /symbols/gh
my_install_file /symbols/gn
my_install_file /symbols/gr
my_install_file /symbols/group
my_install_file /symbols/hp_vndr/us
my_install_file /symbols/hr
my_install_file /symbols/hu
my_install_file /symbols/ie
my_install_file /symbols/il
my_install_file /symbols/in
my_install_file /symbols/inet
my_install_file /symbols/iq
my_install_file /symbols/ir
my_install_file /symbols/is
my_install_file /symbols/it
my_install_file /symbols/jp
my_install_file /symbols/ke
my_install_file /symbols/keypad
my_install_file /symbols/kg
my_install_file /symbols/kh
my_install_file /symbols/kpdl
my_install_file /symbols/kr
my_install_file /symbols/kz
my_install_file /symbols/la
my_install_file /symbols/latam
my_install_file /symbols/latin
my_install_file /symbols/level3
my_install_file /symbols/level5
my_install_file /symbols/lk
my_install_file /symbols/lt
my_install_file /symbols/lv
my_install_file /symbols/ma
my_install_file /symbols/macintosh_vndr/apple
my_install_file /symbols/macintosh_vndr/ch
my_install_file /symbols/macintosh_vndr/de
my_install_file /symbols/macintosh_vndr/dk
my_install_file /symbols/macintosh_vndr/fi
my_install_file /symbols/macintosh_vndr/fr
my_install_file /symbols/macintosh_vndr/gb
my_install_file /symbols/macintosh_vndr/is
my_install_file /symbols/macintosh_vndr/it
my_install_file /symbols/macintosh_vndr/jp
my_install_file /symbols/macintosh_vndr/latam
my_install_file /symbols/macintosh_vndr/nl
my_install_file /symbols/macintosh_vndr/no
my_install_file /symbols/macintosh_vndr/pt
my_install_file /symbols/macintosh_vndr/se
my_install_file /symbols/macintosh_vndr/us
my_install_file /symbols/mao
my_install_file /symbols/me
my_install_file /symbols/mk
my_install_file /symbols/ml
my_install_file /symbols/mm
my_install_file /symbols/mn
my_install_file /symbols/mt
my_install_file /symbols/mv
my_install_file /symbols/nbsp
my_install_file /symbols/nec_vndr/jp
my_install_file /symbols/ng
my_install_file /symbols/nl
my_install_file /symbols/no
my_install_file /symbols/nokia_vndr/rx-44
my_install_file /symbols/nokia_vndr/rx-51
my_install_file /symbols/nokia_vndr/su-8w
my_install_file /symbols/np
my_install_file /symbols/olpc
my_install_file /symbols/pc
my_install_file /symbols/ph
my_install_file /symbols/pk
my_install_file /symbols/pl
my_install_file /symbols/pt
my_install_file /symbols/ro
my_install_file /symbols/rs
my_install_file /symbols/ru
my_install_file /symbols/rupeesign
my_install_file /symbols/se
my_install_file /symbols/sgi_vndr/jp
my_install_file /symbols/shift
my_install_file /symbols/si
my_install_file /symbols/sk
my_install_file /symbols/sn
my_install_file /symbols/sony_vndr/us
my_install_file /symbols/srvr_ctrl
my_install_file /symbols/sun_vndr/ara
my_install_file /symbols/sun_vndr/be
my_install_file /symbols/sun_vndr/br
my_install_file /symbols/sun_vndr/ca
my_install_file /symbols/sun_vndr/ch
my_install_file /symbols/sun_vndr/cz
my_install_file /symbols/sun_vndr/de
my_install_file /symbols/sun_vndr/dk
my_install_file /symbols/sun_vndr/ee
my_install_file /symbols/sun_vndr/es
my_install_file /symbols/sun_vndr/fi
my_install_file /symbols/sun_vndr/fr
my_install_file /symbols/sun_vndr/gb
my_install_file /symbols/sun_vndr/gr
my_install_file /symbols/sun_vndr/it
my_install_file /symbols/sun_vndr/jp
my_install_file /symbols/sun_vndr/kr
my_install_file /symbols/sun_vndr/lt
my_install_file /symbols/sun_vndr/lv
my_install_file /symbols/sun_vndr/nl
my_install_file /symbols/sun_vndr/no
my_install_file /symbols/sun_vndr/pl
my_install_file /symbols/sun_vndr/pt
my_install_file /symbols/sun_vndr/ro
my_install_file /symbols/sun_vndr/ru
my_install_file /symbols/sun_vndr/se
my_install_file /symbols/sun_vndr/sk
my_install_file /symbols/sun_vndr/solaris
my_install_file /symbols/sun_vndr/tr
my_install_file /symbols/sun_vndr/tuv
my_install_file /symbols/sun_vndr/tw
my_install_file /symbols/sun_vndr/ua
my_install_file /symbols/sun_vndr/us
my_install_file /symbols/sy
my_install_file /symbols/terminate
my_install_file /symbols/th
my_install_file /symbols/tj
my_install_file /symbols/tm
my_install_file /symbols/tr
my_install_file /symbols/tw
my_install_file /symbols/typo
my_install_file /symbols/tz
my_install_file /symbols/ua
my_install_file /symbols/us
my_install_file /symbols/uz
my_install_file /symbols/vn
my_install_file /symbols/xfree68_vndr/amiga
my_install_file /symbols/xfree68_vndr/ataritt
my_install_file /symbols/za
my_install_file /symbols.dir                  "$SRCPATH/symbols/symbols.dir"
my_install_file /types/basic
my_install_file /types/cancel
my_install_file /types/caps
my_install_file /types/complete
my_install_file /types/default
my_install_file /types/extra
my_install_file /types/iso9995
my_install_file /types/level5
my_install_file /types/mousekeys
my_install_file /types/nokia
my_install_file /types/numpad
my_install_file /types/pc
my_install_file /types/README
my_install_file /types.dir                    "$SRCPATH/types/types.dir"
