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

# Helpers to automate configure+make+install of packages that use meson

# Extract the package filename from the URL
_PACKAGE_URL_FILENAME="${PACKAGE_URL##*/}"

# Extract the package name from its filename
if test -z "$PACKAGE_NAME"; then
	PACKAGE_NAME="$_PACKAGE_URL_FILENAME"
	if [[ "$PACKAGE_NAME" == *.tar* ]]; then
		PACKAGE_NAME="${PACKAGE_NAME%.tar*}"
	fi
	if [[ "$PACKAGE_NAME" == "$_PACKAGE_URL_FILENAME" ]]; then
		echo "Unable to determine PACKAGE_NAME from"
		echo "	PACKAGE_URL:           $PACKAGE_URL"
		echo "	_PACKAGE_URL_FILENAME: $_PACKAGE_URL_FILENAME"
		exit 1
	fi
fi

if test -z "$PACKAGE_RAWNAME"; then
	PACKAGE_RAWNAME="$PACKAGE_NAME"
	if [[ "$PACKAGE_RAWNAME" == *-* ]]; then
		PACKAGE_RAWNAME="${PACKAGE_RAWNAME%-*}"
	fi
	if [[ "$PACKAGE_RAWNAME" == "$PACKAGE_NAME" ]]; then
		echo "Unable to determine PACKAGE_RAWNAME from"
		echo "	PACKAGE_NAME:          $PACKAGE_NAME"
		echo "	PACKAGE_URL:           $PACKAGE_URL"
		echo "	_PACKAGE_URL_FILENAME: $_PACKAGE_URL_FILENAME"
		exit 1
	fi
fi

if test -z "$PACKAGE_VERSION"; then
	PACKAGE_VERSION="$PACKAGE_NAME"
	if [[ "$PACKAGE_VERSION" == *-* ]]; then
		PACKAGE_VERSION="${PACKAGE_VERSION#*-}"
	fi
	if [[ "$PACKAGE_VERSION" == "$PACKAGE_NAME" ]]; then
		echo "Unable to determine PACKAGE_VERSION from"
		echo "	PACKAGE_NAME:          $PACKAGE_NAME"
		echo "	PACKAGE_URL:           $PACKAGE_URL"
		echo "	_PACKAGE_URL_FILENAME: $_PACKAGE_URL_FILENAME"
		exit 1
	fi
fi

if test -z "$PACKAGE_PREFIX";         then PACKAGE_PREFIX="/"; fi
if test -z "$PACKAGE_EPREFIX";        then PACKAGE_EPREFIX="$PACKAGE_PREFIX"; fi
if test -z "$PACKAGE_BINDIR";         then PACKAGE_BINDIR="${PACKAGE_EPREFIX%/}/bin"; fi
if test -z "$PACKAGE_SBINDIR";        then PACKAGE_SBINDIR="${PACKAGE_EPREFIX%/}/bin"; fi
if test -z "$PACKAGE_LIBEXECDIR";     then PACKAGE_LIBEXECDIR="${PACKAGE_EPREFIX%/}/libexec"; fi
if test -z "$PACKAGE_SYSCONFDIR";     then PACKAGE_SYSCONFDIR="${PACKAGE_PREFIX%/}/etc"; fi
if test -z "$PACKAGE_SHAREDSTATEDIR"; then PACKAGE_SHAREDSTATEDIR="${PACKAGE_PREFIX%/}/usr/com"; fi
if test -z "$PACKAGE_LOCALSTATEDIR";  then PACKAGE_LOCALSTATEDIR="${PACKAGE_PREFIX%/}/var"; fi
if test -z "$PACKAGE_LIBDIR";         then PACKAGE_LIBDIR="${PACKAGE_EPREFIX%/}/$TARGET_LIBPATH"; fi
if test -z "$PACKAGE_INCLUDEDIR";     then PACKAGE_INCLUDEDIR="${PACKAGE_PREFIX%/}/usr/include"; fi
if test -z "$PACKAGE_DATAROOTDIR";    then PACKAGE_DATAROOTDIR="${PACKAGE_PREFIX%/}/usr/share"; fi
if test -z "$PACKAGE_DATADIR";        then PACKAGE_DATADIR="$PACKAGE_DATAROOTDIR"; fi
if test -z "$PACKAGE_INFODIR";        then PACKAGE_INFODIR="$PACKAGE_DATAROOTDIR/info"; fi
if test -z "$PACKAGE_LOCALEDIR";      then PACKAGE_LOCALEDIR="$PACKAGE_DATAROOTDIR/locale"; fi
if test -z "$PACKAGE_MANDIR";         then PACKAGE_MANDIR="$PACKAGE_DATAROOTDIR/man"; fi


echo "meson: PACKAGE_RAWNAME    '$PACKAGE_RAWNAME'"
echo "meson: PACKAGE_VERSION    '$PACKAGE_VERSION'"
echo "meson: PACKAGE_NAME       '$PACKAGE_NAME'"
if ! test -z "$PACKAGE_URL"; then
	echo "meson: PACKAGE_URL        '$PACKAGE_URL'"
elif ! test -z "$PACKAGE_GIT_URL"; then
	echo "meson: PACKAGE_GIT_URL    '$PACKAGE_GIT_URL'"
	if ! test -z "$PACKAGE_GIT_COMMIT"; then
		echo "meson: PACKAGE_GIT_COMMIT '$PACKAGE_GIT_COMMIT'"
	fi
fi

#echo "meson: PACKAGE_PREFIX         '$PACKAGE_PREFIX'"
#echo "meson: PACKAGE_EPREFIX        '$PACKAGE_EPREFIX'"
#echo "meson: PACKAGE_BINDIR         '$PACKAGE_BINDIR'"
#echo "meson: PACKAGE_SBINDIR        '$PACKAGE_SBINDIR'"
#echo "meson: PACKAGE_LIBEXECDIR     '$PACKAGE_LIBEXECDIR'"
#echo "meson: PACKAGE_SYSCONFDIR     '$PACKAGE_SYSCONFDIR'"
#echo "meson: PACKAGE_SHAREDSTATEDIR '$PACKAGE_SHAREDSTATEDIR'"
#echo "meson: PACKAGE_LOCALSTATEDIR  '$PACKAGE_LOCALSTATEDIR'"
#echo "meson: PACKAGE_LIBDIR         '$PACKAGE_LIBDIR'"
#echo "meson: PACKAGE_INCLUDEDIR     '$PACKAGE_INCLUDEDIR'"
#echo "meson: PACKAGE_DATAROOTDIR    '$PACKAGE_DATAROOTDIR'"
#echo "meson: PACKAGE_DATADIR        '$PACKAGE_DATADIR'"
#echo "meson: PACKAGE_INFODIR        '$PACKAGE_INFODIR'"
#echo "meson: PACKAGE_LOCALEDIR      '$PACKAGE_LOCALEDIR'"
#echo "meson: PACKAGE_MANDIR         '$PACKAGE_MANDIR'"


_UTILITY_RELPATH=""
if [[ "$UTILITY_NAME" == */* ]]; then
	_UTILITY_RELPATH="${UTILITY_NAME%/*}"
	if ! test -z "$_UTILITY_RELPATH"; then
		_UTILITY_RELPATH="$_UTILITY_RELPATH/"
	fi
fi
SRCPATH="$KOS_ROOT/binutils/src/${_UTILITY_RELPATH}$PACKAGE_NAME"
OPTPATH="$SYSROOT_BINUTILS_TARGET/opt/${_UTILITY_RELPATH}$PACKAGE_NAME"
DESTDIR="$SYSROOT_BINUTILS_TARGET/opt/${_UTILITY_RELPATH}${PACKAGE_NAME}-install"

MESON_CROSSFILE="$SYSROOT_BINUTILS_TARGET/opt/meson/cross.txt"
if ! [ -f "$MESON_CROSSFILE" ] || [ "$MESON_CROSSFILE" -ot "$KOS_MISC/utilities/misc/meson.sh" ]; then
	. "$KOS_MISC/utilities/misc/target-info.sh"
	cmd mkdir -p "$SYSROOT_BINUTILS_TARGET/opt/meson"
	cmd cat > "$MESON_CROSSFILE" <<EOF
[host_machine]
system = 'linux'
cpu_family = '$TARGET_CPUFAMILY'
cpu = '$TARGET_CPUNAME'
endian = '$TARGET_ENDIAN'

[binaries]
c = '${CROSS_PREFIX}gcc'
gcc = '${CROSS_PREFIX}gcc'
cpp = '${CROSS_PREFIX}g++'
ar = '${CROSS_PREFIX}ar'
as = '${CROSS_PREFIX}as'
ld = '${CROSS_PREFIX}ld'
nm = '${CROSS_PREFIX}nm'
objcopy = '${CROSS_PREFIX}objcopy'
objdump = '${CROSS_PREFIX}objdump'
readelf = '${CROSS_PREFIX}readelf'
size = '${CROSS_PREFIX}size'
strings = '${CROSS_PREFIX}strings'
strip = '${CROSS_PREFIX}strip'
pkgconfig = '$(which pkg-config 2> /dev/null || echo "pkg-config")'
cmake = '$(which cmake 2> /dev/null || echo "cmake")'

[properties]
sys_root = '$SYSROOT_BINUTILS_TARGET'
pkg_config_libdir = '$PKG_CONFIG_LIBDIR'
sizeof_char = $TARGET_CONFIG_SIZEOF_CHAR
sizeof_short = $TARGET_CONFIG_SIZEOF_SHORT
sizeof_int = $TARGET_CONFIG_SIZEOF_INT
sizeof_long = $TARGET_CONFIG_SIZEOF_LONG
sizeof_long_long = $TARGET_CONFIG_SIZEOF_LLONG
sizeof_void* = $TARGET_CONFIG_SIZEOF_POINTER
sizeof_float = $TARGET_CONFIG_SIZEOF_FLOAT
sizeof_double = $TARGET_CONFIG_SIZEOF_DOUBLE
sizeof_long_double = $TARGET_CONFIG_SIZEOF_LDOUBLE
alignment_char = $TARGET_CONFIG_ALIGNOF_CHAR
alignment_short = $TARGET_CONFIG_ALIGNOF_SHORT
alignment_int = $TARGET_CONFIG_ALIGNOF_INT
alignment_long = $TARGET_CONFIG_ALIGNOF_LONG
alignment_long_long = $TARGET_CONFIG_ALIGNOF_LLONG
alignment_void* = $TARGET_CONFIG_ALIGNOF_POINTER
alignment_float = $TARGET_CONFIG_ALIGNOF_FLOAT
alignment_double = $TARGET_CONFIG_ALIGNOF_DOUBLE
alignment_long_double = $TARGET_CONFIG_ALIGNOF_LDOUBLE

# System features used by programs:
#  - libglib
growing_stack = `if [[ "$TARGET_CONFIG_STACK_DIRECTION" == "-1" ]]; then echo "false"; else echo "true"; fi`
have_c99_vsnprintf = true
have_c99_snprintf = true
have_unix98_printf = true
have_strlcpy = true
have_proc_self_cmdline = true

EOF
fi

MESON="$(which meson 2>&1 || echo "meson")"

if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -d "$DESTDIR" ]; then
	if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/_didmake" ]; then
		if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/_didconf" ]; then
			if ! [ -f "$SRCPATH/configure" ]; then
				# Remove $SRCPATH if it's just an empty directory
				rmdir "$SRCPATH" > /dev/null 2>&1
				if ! [ -d "$SRCPATH" ]; then
					BINUTILS_SOURCES="$(dirname "$SRCPATH")"
					cmd mkdir -p "$BINUTILS_SOURCES"
					cmd cd "$BINUTILS_SOURCES"
					if ! test -z "$PACKAGE_URL"; then
						_PACKAGE_URL_FILENAME="${PACKAGE_URL##*/}"
						# Figure out how to download+unpack the package
						if [[ "$_PACKAGE_URL_FILENAME" == *.tar* ]]; then
							# Tar archive. Extract the filename of the file that will be downloaded
							# After downloading, make sure that filename becomes "$PACKAGE_NAME.tar[.gz|.xz|...]"
							_PACKAGE_URL_NAME="${_PACKAGE_URL_FILENAME%.tar*}"
							_PACKAGE_URL_FILENAME_EXT=".tar${_PACKAGE_URL_FILENAME#*.tar}"
							_PACKAGE_URL_WANTED_FILENAME="${PACKAGE_NAME}.tar${_PACKAGE_URL_FILENAME#*.tar}"
							if ! [ -f "$_PACKAGE_URL_WANTED_FILENAME" ]; then
								download_file "$_PACKAGE_URL_FILENAME" "$PACKAGE_URL"
								if [ "$_PACKAGE_URL_WANTED_FILENAME" != "$_PACKAGE_URL_FILENAME" ]; then
									cmd mv "$_PACKAGE_URL_FILENAME" "$_PACKAGE_URL_WANTED_FILENAME"
								fi
							fi
							rm -r "./$_PACKAGE_URL_NAME" > /dev/null 2>&1
							cmd mkdir -p "$SRCPATH"
							cmd tar xvf "$_PACKAGE_URL_WANTED_FILENAME" -C "$SRCPATH"
						else
							# Unrecognized package distribution format
							echo "No known way of extracting files from: '$_PACKAGE_URL_FILENAME'"
							exit 1
						fi
					elif ! test -z "$PACKAGE_GIT_URL"; then
						# Figure out the directory name that
						cmd mkdir -p "$SRCPATH"
						cmd cd "$SRCPATH"
						cmd git clone "$PACKAGE_GIT_URL"
						if ! test -z "$PACKAGE_GIT_COMMIT"; then
							# Checkout the requested git revision
							cmd cd "$(ls -A)"
							cmd git checkout -f "$PACKAGE_GIT_COMMIT"
						fi
					else
						echo "No way of downloading $PACKAGE_NAME"
					fi
				fi
				cmd cd "$SRCPATH"
				# Fix-up doubly-packaged packages
				while [[ `ls -A | wc -l` == 1 ]]; do
					subdirname=`ls -A`
					echo "Fix-up doubly-packed package '$subdirname' -> '${PACKAGE_NAME}'"
					rm -r "$BINUTILS_SOURCES/.${PACKAGE_NAME}-real" > /dev/null 2>&1
					cmd mv "$subdirname" "../.${PACKAGE_NAME}-real"
					cmd cd ".."
					cmd rmdir "${PACKAGE_NAME}"
					cmd mv ".${PACKAGE_NAME}-real" "${PACKAGE_NAME}"
					cmd cd "$SRCPATH"
				done
				# Ensure that this is a meson project
				if ! [ -f "$SRCPATH/meson.build" ]; then
					echo "Not a meson project (missing file: 'meson.build')"
					exit 1
				fi
			fi
			if [ -f "$KOS_PATCHES/$PACKAGE_NAME.patch" ]; then
				apply_patch "$SRCPATH" "$KOS_PATCHES/$PACKAGE_NAME.patch"
			fi

			rm -r "$OPTPATH" > /dev/null 2>&1
			cmd mkdir -p "$OPTPATH"
			cmd cd "$OPTPATH"

			# Configure project
			echo "meson: Now running $PACKAGE_NAME: 'meson setup'..."
			cmd "$MESON" setup \
				--prefix "$PACKAGE_PREFIX" \
				--bindir "$PACKAGE_BINDIR" \
				--datadir "$PACKAGE_DATADIR" \
				--includedir "$PACKAGE_INCLUDEDIR" \
				--infodir "$PACKAGE_INFODIR" \
				--libdir "$PACKAGE_LIBDIR" \
				--libexecdir "$PACKAGE_LIBEXECDIR" \
				--localedir "$PACKAGE_LOCALEDIR" \
				--localstatedir "$PACKAGE_LOCALSTATEDIR" \
				--mandir "$PACKAGE_MANDIR" \
				--sbindir "$PACKAGE_SBINDIR" \
				--sharedstatedir "$PACKAGE_SHAREDSTATEDIR" \
				--sysconfdir "$PACKAGE_SYSCONFDIR" \
				--cross-file "$MESON_CROSSFILE" \
				"${CONFIGURE[@]}" \
				"$SRCPATH" \
				"$OPTPATH"

			# Remember that setup was successful
			> "$OPTPATH/_didconf"
		fi # if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ];

		# Make project
		cmd cd "$SRCPATH"
		echo "meson: Now running $PACKAGE_NAME: 'meson compile'..."
		cmd "$MESON" compile -C "$OPTPATH"
		> "$OPTPATH/_didmake"
	fi     # if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/_didmake" ]

	# Install project
	rm -r "$DESTDIR-temp" > /dev/null 2>&1
	echo "meson: Now running $PACKAGE_NAME: 'meson install'..."
	(
		export DESTDIR="$DESTDIR-temp"
		cmd cd "$SRCPATH"
		${MS_HOOK_BEFORE_INSTALL:-:}
		cmd "$MESON" install -C "$OPTPATH"
	) || exit $?
	${MS_HOOK_AFTER_INSTALL:-:}
	rm -r "$DESTDIR" > /dev/null 2>&1
	cmd mv "$DESTDIR-temp" "$DESTDIR"
fi         # if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -d "$DESTDIR" ]

# Install to disk
. "$KOS_MISC/utilities/misc/install-DESTDIR.sh"
