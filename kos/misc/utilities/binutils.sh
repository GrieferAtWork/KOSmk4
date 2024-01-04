#TEST: require_utility binutils "$SYSROOT_BIN_TARGET_COMMON/bin/ld"
# Copyright (c) 2019-2024 Griefer@Work
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
#    Portions Copyright (c) 2019-2024 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

require_utility libzlib "$PKG_CONFIG_PATH/zlib.pc"

PACKAGE_URL="https://ftp.gnu.org/gnu/binutils/binutils-2.38.tar.gz"

# Binutils and gcc are special, in that we actually don't fake being linux for them!
case "$TARGET_NAME" in
i?86)
	USED_TARGET_NAME="i686"
	;;
*)
	USED_TARGET_NAME="$TARGET_NAME"
	;;
esac

PACKAGE_HOST="$USED_TARGET_NAME-kos"
PACKAGE_TARGET="$USED_TARGET_NAME-kos"

PACKAGE_CONFIGURE=(
	--prefix=/
	--exec-prefix=/lib
	--bindir=/bin
	--sbindir=/bin
	--libexecdir=/usr/libexec
	--sysconfdir=/etc
	--sharedstatedir=/usr/com
	--localstatedir=/var
	#--runstatedir=/var/run
	--libdir=/lib
	--includedir=/usr/include
	--oldincludedir=/usr/include
	--datarootdir=/usr/share
	--datadir=/usr/share
	--infodir=/usr/share/info
	--localedir=/usr/share/locale
	--mandir=/usr/share/man
	--docdir=/usr/share/doc/binutils
	--htmldir=/usr/share/doc/binutils
	--dvidir=/usr/share/doc/binutils
	--pdfdir=/usr/share/doc/binutils
	--psdir=/usr/share/doc/binutils
	--build="$(gcc -dumpmachine)"
	--host="$PACKAGE_HOST"
	--target="$PACKAGE_TARGET"
	--disable-werror
	--with-system-zlib
)

if false; then
	# This works perfectly, but is horribly slow... (because it has to scan so many files)
	CONFIGURE_SITE_SCANNED_FILES=(
		"configure"
		"bfd/configure"
		"binutils/configure"
		"etc/configure"
		"gas/configure"
		"gold/configure"
		"gprof/configure"
		"intl/configure"
		"ld/configure"
		"libctf/configure"
		"libiberty/configure"
		"opcodes/configure"
		"zlib/configure"
	)
else
	PACKAGE_CONFIGURE_SITE_SCANNED_FILES=""
	_hook_config_site() {
		export CONFIG_SITE="$OPTPATH/config.site"
		cat > "$CONFIG_SITE" <<EOF
ac_cv_func_mmap_fixed_mapped=yes
gt_cv_int_divbyzero_sigfpe=yes
ac_cv_func_vfork_works=yes
ac_cv_func_fork_works=yes
ac_cv_func_strncmp_works=yes
EOF
	}

	GM_HOOK_BEFORE_CONFIGURE=_hook_config_site
fi


# Skip some files during install
INSTALL_SKIP="
/lib/$USED_TARGET_NAME-kos/bin
/usr/include/ansidecl.h
/usr/include/symcat.h
"

# Automatically build+install using autoconf
. "$KOS_MISC/utilities/misc/gnu_make.sh"
