#TEST: require_utility libpcre "$PKG_CONFIG_PATH/libpcre.pc"
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

require_utility libzlib "$PKG_CONFIG_PATH/zlib.pc"
require_utility libbzip2 "$PKG_CONFIG_PATH/bzip2.pc"

PACKAGE_URL="https://sourceforge.net/projects/pcre/files/pcre/8.37/pcre-8.37.tar.bz2"
PACKAGE_NAME="libpcre-8.37"

# Additions configure options
CONFIGURE=(
	"--enable-utf"
	"--enable-newline-is-anycrlf"
	"--enable-pcregrep-libz"
	"--enable-pcregrep-libbz2"
)

INSTALL_SKIP="
/bin/pcre-config
"

# Automatically build+install using autoconf
. "$KOS_MISC/utilities/misc/gnu_make.sh"

cmd mkdir -p "$BINUTILS_CONFIG_BIN"
cmd cat > "$BINUTILS_CONFIG_BIN/pcre-config" <<EOF
#!/bin/sh
if test \$# -eq 0; then exit 1; fi
while test \$# -gt 0; do
	case \$1 in
	--prefix=*)      ;;
	--prefix)        echo "$PACKAGE_PREFIX"; ;;
	--exec-prefix=*) ;;
	--exec-prefix)   echo "$PACKAGE_EPREFIX"; ;;
	--version)       echo "$PACKAGE_VERSION"; ;;
	--cflags)        echo ""; ;;
	--cflags-posix)  echo ""; ;;
	--libs-posix)    echo "-lpcreposix -lpcre"; ;;
	--libs)          echo "-lpcre"; ;;
	--libs16)        echo "-lpcre16"; ;;
	--libs32)        echo "-lpcre32"; ;;
	--libs-cpp)      echo "-lpcrecpp -lpcre"; ;;
	*)               exit 1; ;;
	esac
	shift
done
EOF
cmd chmod +x "$BINUTILS_CONFIG_BIN/pcre-config"
