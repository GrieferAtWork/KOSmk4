#TEST: require_utility Xorg/libxcb "$PKG_CONFIG_PATH/xcb.pc"
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

require_utility Xorg/xcb-proto "$PKG_CONFIG_PATH/xcb-proto.pc"
require_utility Xorg/libXau    "$PKG_CONFIG_PATH/xau.pc"

PACKAGE_URL="https://www.x.org/releases/individual/lib/libxcb-1.14.tar.gz"

CONFIGURE=(
	"--enable-xinput"
	"--enable-xkb"
	"--enable-composite"
	"--enable-damage"
	"--enable-dpms"
	"--enable-dri2"
	"--enable-dri3"
	"--disable-ge"
	"--enable-glx"
	"--enable-present"
	"--enable-randr"
	"--enable-record"
	"--enable-render"
	"--enable-resource"
	"--enable-screensaver"
	"--enable-shape"
	"--enable-shm"
	"--enable-sync"
	"--enable-xevie"
	"--enable-xfixes"
	"--enable-xfree86-dri"
	"--enable-xinerama"
	"--enable-xinput"
	"--enable-xprint"
	"--disable-selinux"
	"--enable-xtest"
	"--enable-xv"
	"--enable-xvmc"
)

# libxcb has a dependency on a library `libpthread-stubs` that
# contains code to stub-out pthread functions not exposed from
# libc.
# However, on KOS libc already provides all of the functions
# that `libpthread-stubs` is there to stub out, so rather than
# actually building that library, we can stub _IT_ out.
if ! [ -f "$PKG_CONFIG_PATH/pthread-stubs.pc" ]; then
	echo "Creating file: '$PKG_CONFIG_PATH/pthread-stubs.pc'"
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

GM_HOOK_BEFORE_MAKE=_libxcb_path_optpath_config
_libxcb_path_optpath_config() {
	if ! [ -f "$OPTPATH/src/.kos_patched_config" ]; then
		#
		# Because we're acting like we're linux, libxcb thinks that KOS
		# supports linux's `HAVE_ABSTRACT_SOCKETS`, when in fact we don't.
		#
		# Other Xorg components don't use configure to check this, but
		# instead check for `#ifdef linux` at compile-time, which correctly
		# handles the behavior on KOS.
		#
		# However, libxcb uses configure, so we have to hack its config.h
		# to disable support for abstract sockets.
		#
		cmd [ -f "$OPTPATH/src/config.h" ]
		echo ""                                        >> "$OPTPATH/src/config.h"
		echo "/* KOS doesn't actually support this */" >> "$OPTPATH/src/config.h"
		echo "#undef HAVE_ABSTRACT_SOCKETS"            >> "$OPTPATH/src/config.h"
		> "$OPTPATH/src/.kos_patched_config"
	fi
}

# This one needs python modules installed by `Xorg/xcb-proto`
export PYTHONPATH="$PYTHONPATH $(echo $SYSROOT_BINUTILS_TARGET/usr/local/lib/python*/site-packages)"

# Automatically build+install using autoconf
. "$KOS_MISC/utilities/misc/gnu_make.sh"
