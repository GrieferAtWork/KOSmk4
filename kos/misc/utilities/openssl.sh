#TEST: require_utility openssl "$PKG_CONFIG_PATH/openssl.pc"
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

VERSION="1.1.1g"
SO_VERSION="1.1"

SRCPATH="$KOS_ROOT/binutils/src/openssl-$VERSION"
OPTPATH="$SYSROOT_BINUTILS_TARGET/opt/openssl-$VERSION"

# NOTE: This is the path within the KOS disk image!
OPENSSLDIR="/usr/lib/ssl"

require_program perl

if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/libssl.so.$SO_VERSION" ]; then
	if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
		if ! [ -f "$SRCPATH/Configure" ]; then
			cmd cd "$KOS_ROOT/binutils/src"
			cmd rm -rf "openssl-$VERSION"
			download_file \
				"openssl-$VERSION.tar.gz" \
				"https://www.openssl.org/source/openssl-$VERSION.tar.gz"
			cmd tar xvf "openssl-$VERSION.tar.gz"
		fi
		apply_patch "${SRCPATH}" \
			"$KOS_PATCHES/openssl-$VERSION.patch"
		cmd rm -rf "$OPTPATH"
		cmd mkdir -p "$OPTPATH"
		cmd cd "$OPTPATH"
		(
			export CFLAGS="-ggdb"
			export CXXFLAGS="-ggdb"
			OSS_OSNAME="linux-elf"
			OSS_OPT386=""
			if [ "$TARGET_NAME" == "i386" ]; then
				OSS_OSNAME="linux-x86"
				OSS_OPT386="386"
			elif [ "$TARGET_NAME" == "x86_64" ]; then
				OSS_OSNAME="linux-x86_64"
			fi
			cmd perl ../../../src/openssl-$VERSION/Configure \
				--prefix="/" \
				--openssldir="$OPENSSLDIR" \
				--cross-compile-prefix="$CROSS_PREFIX" \
				shared zlib-dynamic \
				"$OSS_OPT386" "$OSS_OSNAME"
		) || exit $?
	fi
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT
fi

# Install libraries:
install_file        /bin/c_rehash                                   "$OPTPATH/tools/c_rehash"
install_file        /bin/openssl                                    "$OPTPATH/apps/openssl"
install_file        /$TARGET_LIBPATH/engines-$SO_VERSION/capi.so    "$OPTPATH/engines/capi.so"
install_file        /$TARGET_LIBPATH/engines-$SO_VERSION/padlock.so "$OPTPATH/engines/padlock.so"
install_file        /$TARGET_LIBPATH/libcrypto.so.$SO_VERSION       "$OPTPATH/libcrypto.so.$SO_VERSION"
install_symlink_nodisk  /$TARGET_LIBPATH/libcrypto.so                   libcrypto.so.$SO_VERSION_MAJOR
install_file_nodisk /$TARGET_LIBPATH/libcrypto.a                    "$OPTPATH/libcrypto.a"
install_file        /$TARGET_LIBPATH/libssl.so.$SO_VERSION          "$OPTPATH/libssl.so.$SO_VERSION"
install_symlink_nodisk  /$TARGET_LIBPATH/libssl.so                      libssl.so.$SO_VERSION_MAJOR
install_file_nodisk /$TARGET_LIBPATH/libssl.a                       "$OPTPATH/libssl.a"

# Install config files:
install_file    $OPENSSLDIR/ct_log_list.cnf       "$SRCPATH/apps/ct_log_list.cnf"
install_file    $OPENSSLDIR/ct_log_list.cnf.dist  "$SRCPATH/apps/ct_log_list.cnf"
install_file    $OPENSSLDIR/misc/CA.pl            "$OPTPATH/apps/CA.pl"
install_symlink $OPENSSLDIR/misc/tsget            "tsget.pl"
install_file    $OPENSSLDIR/misc/tsget.pl         "$OPTPATH/apps/tsget.pl"
install_file    $OPENSSLDIR/openssl.cnf           "$SRCPATH/apps/openssl.cnf"
install_file    $OPENSSLDIR/openssl.cnf.dist      "$SRCPATH/apps/openssl.cnf"


# Install headers:
if [ "$TARGET_NAME" == "i386" ] || [ "$TARGET_NAME" == "x86_64" ]; then
	TARGET_EXT="32"
	if [ "$TARGET_NAME" == "x86_64" ]; then
		TARGET_EXT="64"
	fi
	install_rawfile \
		"$KOS_ROOT/kos/include/$TARGET_INCPATH/openssl/opensslconf$TARGET_EXT.h" \
		"$OPTPATH/include/openssl/opensslconf.h"
	install_rawfile_stdin "$KOS_ROOT/kos/include/$TARGET_INCPATH/openssl/opensslconf.h" <<EOF
#include <hybrid/host.h>
#ifdef __x86_64__
#include "opensslconf64.h"
#else /* __x86_64__ */
#include "opensslconf32.h"
#endif /* !__x86_64__ */
EOF
else
	install_rawfile \
		"$KOS_ROOT/kos/include/$TARGET_INCPATH/openssl/opensslconf.h" \
		"$OPTPATH/include/openssl/opensslconf.h"
fi

install_header() {
	install_rawfile "$KOS_ROOT/kos/include/$1" "$SRCPATH/include/$1"
}
install_header "openssl/aes.h"
install_header "openssl/asn1.h"
install_header "openssl/asn1err.h"
install_header "openssl/asn1t.h"
# install_header "openssl/asn1_mac.h"  # Stub-header that only contains #error
install_header "openssl/async.h"
install_header "openssl/asyncerr.h"
install_header "openssl/bio.h"
install_header "openssl/bioerr.h"
install_header "openssl/blowfish.h"
install_header "openssl/bn.h"
install_header "openssl/bnerr.h"
install_header "openssl/buffer.h"
install_header "openssl/buffererr.h"
install_header "openssl/camellia.h"
install_header "openssl/cast.h"
install_header "openssl/cmac.h"
install_header "openssl/cms.h"
install_header "openssl/cmserr.h"
install_header "openssl/comp.h"
install_header "openssl/comperr.h"
install_header "openssl/conf.h"
install_header "openssl/conferr.h"
install_header "openssl/conf_api.h"
install_header "openssl/crypto.h"
install_header "openssl/cryptoerr.h"
install_header "openssl/ct.h"
install_header "openssl/cterr.h"
install_header "openssl/des.h"
install_header "openssl/dh.h"
install_header "openssl/dherr.h"
install_header "openssl/dsa.h"
install_header "openssl/dsaerr.h"
install_header "openssl/dtls1.h"
install_header "openssl/ebcdic.h"
install_header "openssl/ec.h"
install_header "openssl/ecdh.h"
install_header "openssl/ecdsa.h"
install_header "openssl/ecerr.h"
install_header "openssl/engine.h"
install_header "openssl/engineerr.h"
install_header "openssl/err.h"
install_header "openssl/evp.h"
install_header "openssl/evperr.h"
install_header "openssl/e_os2.h"
install_header "openssl/hmac.h"
install_header "openssl/idea.h"
install_header "openssl/kdf.h"
install_header "openssl/kdferr.h"
install_header "openssl/lhash.h"
install_header "openssl/md2.h"
install_header "openssl/md4.h"
install_header "openssl/md5.h"
install_header "openssl/mdc2.h"
install_header "openssl/modes.h"
install_header "openssl/objects.h"
install_header "openssl/objectserr.h"
install_header "openssl/obj_mac.h"
install_header "openssl/ocsp.h"
install_header "openssl/ocsperr.h"
install_header "openssl/opensslv.h"
install_header "openssl/ossl_typ.h"
install_header "openssl/pem.h"
install_header "openssl/pem2.h"
install_header "openssl/pemerr.h"
install_header "openssl/pkcs12.h"
install_header "openssl/pkcs12err.h"
install_header "openssl/pkcs7.h"
install_header "openssl/pkcs7err.h"
install_header "openssl/rand.h"
install_header "openssl/randerr.h"
install_header "openssl/rand_drbg.h"
install_header "openssl/rc2.h"
install_header "openssl/rc4.h"
install_header "openssl/rc5.h"
install_header "openssl/ripemd.h"
install_header "openssl/rsa.h"
install_header "openssl/rsaerr.h"
install_header "openssl/safestack.h"
install_header "openssl/seed.h"
install_header "openssl/sha.h"
install_header "openssl/srp.h"
install_header "openssl/srtp.h"
install_header "openssl/ssl.h"
install_header "openssl/ssl2.h"
install_header "openssl/ssl3.h"
install_header "openssl/sslerr.h"
install_header "openssl/stack.h"
install_header "openssl/store.h"
install_header "openssl/storeerr.h"
install_header "openssl/symhacks.h"
install_header "openssl/tls1.h"
install_header "openssl/ts.h"
install_header "openssl/tserr.h"
install_header "openssl/txt_db.h"
install_header "openssl/ui.h"
install_header "openssl/uierr.h"
install_header "openssl/whrlpool.h"
install_header "openssl/x509.h"
install_header "openssl/x509err.h"
install_header "openssl/x509v3.h"
install_header "openssl/x509v3err.h"
install_header "openssl/x509_vfy.h"

# Install the PKG_CONFIG files
install_rawfile_stdin "$PKG_CONFIG_PATH/openssl.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: OpenSSL
Description: Secure Sockets Layer and cryptography libraries and tools
Version: $VERSION
Requires: libssl libcrypto
EOF

install_rawfile_stdin "$PKG_CONFIG_PATH/libssl.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: OpenSSL-libssl
Description: Secure Sockets Layer and cryptography libraries
Version: $VERSION
Requires.private: libcrypto
Libs: -lssl
Cflags:
EOF

install_rawfile_stdin "$PKG_CONFIG_PATH/libcrypto.pc" <<EOF
prefix=/
exec_prefix=/
libdir=$KOS_ROOT/bin/$TARGET_NAME-kos/$TARGET_LIBPATH
includedir=$KOS_ROOT/kos/include

Name: OpenSSL-libcrypto
Description: OpenSSL cryptography library
Version: $VERSION
Libs: -lcrypto
Libs.private: -ldl -pthread
Cflags:
EOF
