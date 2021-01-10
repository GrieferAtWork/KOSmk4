# Copyright (c) 2019-2021 Griefer@Work
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
#    Portions Copyright (c) 2019-2021 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.


if ! which xkbcomp > /dev/null 2>&1; then

	VERSION_XKBCOMP="1.4.3"
	SRCPATH_XKBCOMP="$KOS_ROOT/binutils/src/Xorg/xkbcomp-$VERSION_XKBCOMP"
	OPTPATH_XKBCOMP="$KOS_ROOT/binutils/misc/opt/xkbcomp-$VERSION_XKBCOMP"

	VERSION_LIBXKBFILE="1.1.0"
	SRCPATH_LIBXKBFILE="$KOS_ROOT/binutils/src/Xorg/libxkbfile-$VERSION_LIBXKBFILE"
	OPTPATH_LIBXKBFILE="$KOS_ROOT/binutils/misc/opt/libxkbfile-$VERSION_LIBXKBFILE"

	if ! [ -f "$KOS_ROOT/binutils/misc/bin/xkbcomp" ] && \
	   ! [ -f "$KOS_ROOT/binutils/misc/bin/xkbcomp.exe" ]; then
		if ! [ -f "$OPTPATH_XKBCOMP/xkbcomp" ] && \
		   ! [ -f "$OPTPATH_XKBCOMP/xkbcomp.exe" ]; then
			# libxkbfile
			if ! [ -f "$KOS_ROOT/binutils/misc/lib/libxkbfile.a" ]; then
				if ! [ -f "$OPTPATH_LIBXKBFILE/src/.libs/libxkbfile.a" ]; then
					if ! [ -f "$OPTPATH_LIBXKBFILE/Makefile" ]; then
						if ! [ -f "$SRCPATH_LIBXKBFILE/configure" ]; then
							cmd mkdir -p "$KOS_ROOT/binutils/src/Xorg"
							cmd cd "$KOS_ROOT/binutils/src/Xorg"
							cmd rm -rf "libxkbfile-$VERSION_LIBXKBFILE"
							download_file \
								"libxkbfile-$VERSION_LIBXKBFILE.tar.gz" \
								"https://www.x.org/releases/individual/lib/libxkbfile-$VERSION_LIBXKBFILE.tar.gz"
							cmd tar xvf "libxkbfile-$VERSION_LIBXKBFILE.tar.gz"
						fi
						cmd rm -rf "$OPTPATH_LIBXKBFILE"
						cmd mkdir -p "$OPTPATH_LIBXKBFILE/X11-include"
						cmd ln -s "$KOS_ROOT/kos/include/X11"  "$OPTPATH_LIBXKBFILE/X11-include/X11"
						cmd ln -s "$KOS_ROOT/kos/include/xcb"  "$OPTPATH_LIBXKBFILE/X11-include/xcb"
						cmd ln -s "$KOS_ROOT/kos/include/xorg" "$OPTPATH_LIBXKBFILE/X11-include/xorg"
						cmd cd "$OPTPATH_LIBXKBFILE"
						(
							unset PKG_CONFIG_PATH
							unset PKG_CONFIG_LIBDIR
							export CFLAGS="-I$OPTPATH_LIBXKBFILE/X11-include"
							export CXXFLAGS="-I$OPTPATH_LIBXKBFILE/X11-include"
							cmd bash "../../../src/Xorg/libxkbfile-$VERSION_LIBXKBFILE/configure" \
								--prefix="$KOS_ROOT/binutils/misc"
						) || exit $?
					fi
					cmd cd "$OPTPATH_LIBXKBFILE"
					cmd make -j $MAKE_PARALLEL_COUNT
				fi
				cmd make -j $MAKE_PARALLEL_COUNT install
			fi

			# xkbcomp
			if ! [ -f "$OPTPATH_XKBCOMP/Makefile" ]; then
				if ! [ -f "$SRCPATH_XKBCOMP/configure" ]; then
					cmd cd "$KOS_ROOT/binutils/src/Xorg"
					cmd rm -rf "xkbcomp-$VERSION_XKBCOMP"
					download_file \
						"xkbcomp-$VERSION_XKBCOMP.tar.gz" \
						"https://www.x.org/releases/individual/app/xkbcomp-$VERSION_XKBCOMP.tar.gz"
					cmd tar xvf "xkbcomp-$VERSION_XKBCOMP.tar.gz"
				fi
				cmd rm -rf "$OPTPATH_XKBCOMP"
				cmd mkdir -p "$OPTPATH_XKBCOMP/X11-include"
				cmd ln -s "$KOS_ROOT/kos/include/X11"  "$OPTPATH_XKBCOMP/X11-include/X11"
				cmd ln -s "$KOS_ROOT/kos/include/xcb"  "$OPTPATH_XKBCOMP/X11-include/xcb"
				cmd ln -s "$KOS_ROOT/kos/include/xorg" "$OPTPATH_XKBCOMP/X11-include/xorg"
				cmd cd "$OPTPATH_XKBCOMP"
				(
					unset PKG_CONFIG_PATH
					unset PKG_CONFIG_LIBDIR
					export CFLAGS="-I$OPTPATH_XKBCOMP/X11-include"
					export CXXFLAGS="-I$OPTPATH_XKBCOMP/X11-include"
					export LDFLAGS="-L$OPTPATH_LIBXKBFILE/src/.libs -Wl,-rpath=$OPTPATH_XKBCOMP/bin"
					cmd bash "../../../src/Xorg/xkbcomp-$VERSION_XKBCOMP/configure" \
						--with-xkb-config-root="/usr/share/X11/xkb" \
						--prefix="$KOS_ROOT/binutils/misc"
				) || exit $?
			fi
			cmd cd "$OPTPATH_XKBCOMP"
			cmd make -j $MAKE_PARALLEL_COUNT
		fi
		cmd cd "$OPTPATH_XKBCOMP"
		cmd make -j $MAKE_PARALLEL_COUNT install
	fi

	# Make sure that `xkbcomp' appears in $PATH
	export PATH="$KOS_ROOT/binutils/misc/bin:$PATH"
fi
