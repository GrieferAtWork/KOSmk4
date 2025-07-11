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

# Helpers to automate configure+make+install of packages that make
# use of GNU autoconf+automake

# Extract the package filename from the URL
if test -z "$PACKAGE_URL_FILENAME"; then
	PACKAGE_URL_FILENAME="${PACKAGE_URL##*/}"
	if test -z "$PACKAGE_URL_FILENAME"; then
		PACKAGE_URL_FILENAME="${PACKAGE_GIT_URL##*/}"
	fi
fi

# Extract the package name from its filename
if test -z "$PACKAGE_NAME"; then
	PACKAGE_NAME="$PACKAGE_URL_FILENAME"
	if [[ "$PACKAGE_NAME" == *".tar"* ]]; then
		PACKAGE_NAME="${PACKAGE_NAME%.tar*}"
	elif [[ "$PACKAGE_NAME" == *".git"* ]]; then
		PACKAGE_NAME="${PACKAGE_NAME%.git*}"
	fi
	if test "$PACKAGE_NAME" == "$PACKAGE_URL_FILENAME"; then
		echo -e "\e[${UI_COLCFG_ERR}mUnable to determine PACKAGE_NAME\e[m from" >&2
		echo -e "	PACKAGE_URL:           '\e[${UI_COLCFG_NAME}m$PACKAGE_URL\e[m'" >&2
		echo -e "	PACKAGE_GIT_URL:       '\e[${UI_COLCFG_NAME}m$PACKAGE_GIT_URL\e[m'" >&2
		echo -e "	PACKAGE_URL_FILENAME: '\e[${UI_COLCFG_NAME}m$PACKAGE_URL_FILENAME\e[m'" >&2
		exit 1
	fi
fi

if test -z "$PACKAGE_RAWNAME"; then
	PACKAGE_RAWNAME="$PACKAGE_NAME"
	if [[ "$PACKAGE_RAWNAME" == *"-"* ]]; then
		PACKAGE_RAWNAME="${PACKAGE_RAWNAME%-*}"
	fi
#	if test "$PACKAGE_RAWNAME" == "$PACKAGE_NAME"; then
#		echo "Unable to determine PACKAGE_RAWNAME from" >&2
#		echo -e "	PACKAGE_NAME:          '\e[${UI_COLCFG_NAME}m$PACKAGE_NAME\e[m'" >&2
#		echo -e "	PACKAGE_URL:           '\e[${UI_COLCFG_NAME}m$PACKAGE_URL\e[m'" >&2
#		echo -e "	PACKAGE_GIT_URL:       '\e[${UI_COLCFG_NAME}m$PACKAGE_GIT_URL\e[m'" >&2
#		echo -e "	PACKAGE_URL_FILENAME: '\e[${UI_COLCFG_NAME}m$PACKAGE_URL_FILENAME\e[m'" >&2
#		exit 1
#	fi
fi

if test -z "${PACKAGE_VERSION+x}"; then
	PACKAGE_VERSION="$PACKAGE_NAME"
	if [[ "$PACKAGE_VERSION" == *"-"* ]]; then
		PACKAGE_VERSION="${PACKAGE_VERSION#*-}"
	fi
	if test "$PACKAGE_VERSION" == "$PACKAGE_NAME"; then
		PACKAGE_VERSION=""
#		echo "Unable to determine PACKAGE_VERSION from" >&2
#		echo -e "	PACKAGE_NAME:          '\e[${UI_COLCFG_NAME}m$PACKAGE_NAME\e[m'" >&2
#		echo -e "	PACKAGE_URL:           '\e[${UI_COLCFG_NAME}m$PACKAGE_URL\e[m'" >&2
#		echo -e "	PACKAGE_URL_FILENAME: '\e[${UI_COLCFG_NAME}m$PACKAGE_URL_FILENAME\e[m'" >&2
#		exit 1
	fi
fi

if test -z "${PACKAGE_PREFIX+x}";         then PACKAGE_PREFIX="/"; fi
if test -z "${PACKAGE_EPREFIX+x}";        then PACKAGE_EPREFIX="$PACKAGE_PREFIX"; fi
if test -z "${PACKAGE_BINDIR+x}";         then PACKAGE_BINDIR="${PACKAGE_EPREFIX%/}/bin"; fi
if test -z "${PACKAGE_SBINDIR+x}";        then PACKAGE_SBINDIR="${PACKAGE_EPREFIX%/}/bin"; fi
if test -z "${PACKAGE_LIBEXECDIR+x}";     then PACKAGE_LIBEXECDIR="${PACKAGE_EPREFIX%/}/usr/libexec"; fi
if test -z "${PACKAGE_SYSCONFDIR+x}";     then PACKAGE_SYSCONFDIR="${PACKAGE_PREFIX%/}/etc"; fi
if test -z "${PACKAGE_SHAREDSTATEDIR+x}"; then PACKAGE_SHAREDSTATEDIR="${PACKAGE_PREFIX%/}/usr/com"; fi
if test -z "${PACKAGE_LOCALSTATEDIR+x}";  then PACKAGE_LOCALSTATEDIR="${PACKAGE_PREFIX%/}/var"; fi
if test -z "${PACKAGE_RUNSTATEDIR+x}";    then PACKAGE_RUNSTATEDIR="${PACKAGE_LOCALSTATEDIR}/run"; fi
if test -z "${PACKAGE_LIBDIR+x}";         then PACKAGE_LIBDIR="${PACKAGE_EPREFIX%/}/$TARGET_LIBPATH"; fi
if test -z "${PACKAGE_INCLUDEDIR+x}";     then PACKAGE_INCLUDEDIR="${PACKAGE_PREFIX%/}/usr/include"; fi
if test -z "${PACKAGE_OLDINCLUDEDIR+x}";  then PACKAGE_OLDINCLUDEDIR="$PACKAGE_INCLUDEDIR"; fi
if test -z "${PACKAGE_DATAROOTDIR+x}";    then PACKAGE_DATAROOTDIR="${PACKAGE_PREFIX%/}/usr/share"; fi
if test -z "${PACKAGE_DATADIR+x}";        then PACKAGE_DATADIR="$PACKAGE_DATAROOTDIR"; fi
if test -z "${PACKAGE_INFODIR+x}";        then PACKAGE_INFODIR="$PACKAGE_DATAROOTDIR/info"; fi
if test -z "${PACKAGE_LOCALEDIR+x}";      then PACKAGE_LOCALEDIR="$PACKAGE_DATAROOTDIR/locale"; fi
if test -z "${PACKAGE_MANDIR+x}";         then PACKAGE_MANDIR="$PACKAGE_DATAROOTDIR/man"; fi
if test -z "${PACKAGE_DOCDIR+x}";         then PACKAGE_DOCDIR="$PACKAGE_DATAROOTDIR/doc/$PACKAGE_RAWNAME"; fi
if test -z "${PACKAGE_HTMLDIR+x}";        then PACKAGE_HTMLDIR="$PACKAGE_DOCDIR"; fi
if test -z "${PACKAGE_DVIDIR+x}";         then PACKAGE_DVIDIR="$PACKAGE_DOCDIR"; fi
if test -z "${PACKAGE_PDFDIR+x}";         then PACKAGE_PDFDIR="$PACKAGE_DOCDIR"; fi
if test -z "${PACKAGE_PSDIR+x}";          then PACKAGE_PSDIR="$PACKAGE_DOCDIR"; fi
if test -z "${PACKAGE_HOST+x}";           then PACKAGE_HOST="$TARGET_NAME-linux-gnu"; fi
if test -z "${PACKAGE_TARGET+x}";         then PACKAGE_TARGET="$PACKAGE_HOST"; fi


echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_RAWNAME    '\e[${UI_COLCFG_NAME}m$PACKAGE_RAWNAME\e[m'" >&2
echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_VERSION    '\e[${UI_COLCFG_NAME}m$PACKAGE_VERSION\e[m'" >&2
echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_NAME       '\e[${UI_COLCFG_NAME}m$PACKAGE_NAME\e[m'" >&2
if ! test -z "$PACKAGE_URL"; then
	echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_URL        '\e[${UI_COLCFG_NAME}m$PACKAGE_URL\e[m'" >&2
elif ! test -z "$PACKAGE_GIT_URL"; then
	echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_GIT_URL    '\e[${UI_COLCFG_NAME}m$PACKAGE_GIT_URL\e[m'" >&2
	if ! test -z "$PACKAGE_GIT_COMMIT"; then
		echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_GIT_COMMIT '\e[${UI_COLCFG_NAME}m$PACKAGE_GIT_COMMIT\e[m'" >&2
	fi
fi

#echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_PREFIX         '\e[${UI_COLCFG_NAME}m$PACKAGE_PREFIX\e[m'" >&2
#echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_EPREFIX        '\e[${UI_COLCFG_NAME}m$PACKAGE_EPREFIX\e[m'" >&2
#echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_BINDIR         '\e[${UI_COLCFG_NAME}m$PACKAGE_BINDIR\e[m'" >&2
#echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_SBINDIR        '\e[${UI_COLCFG_NAME}m$PACKAGE_SBINDIR\e[m'" >&2
#echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_LIBEXECDIR     '\e[${UI_COLCFG_NAME}m$PACKAGE_LIBEXECDIR\e[m'" >&2
#echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_SYSCONFDIR     '\e[${UI_COLCFG_NAME}m$PACKAGE_SYSCONFDIR\e[m'" >&2
#echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_SHAREDSTATEDIR '\e[${UI_COLCFG_NAME}m$PACKAGE_SHAREDSTATEDIR\e[m'" >&2
#echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_LOCALSTATEDIR  '\e[${UI_COLCFG_NAME}m$PACKAGE_LOCALSTATEDIR\e[m'" >&2
#echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_LIBDIR         '\e[${UI_COLCFG_NAME}m$PACKAGE_LIBDIR\e[m'" >&2
#echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_INCLUDEDIR     '\e[${UI_COLCFG_NAME}m$PACKAGE_INCLUDEDIR\e[m'" >&2
#echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_OLDINCLUDEDIR  '\e[${UI_COLCFG_NAME}m$PACKAGE_OLDINCLUDEDIR\e[m'" >&2
#echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_DATAROOTDIR    '\e[${UI_COLCFG_NAME}m$PACKAGE_DATAROOTDIR\e[m'" >&2
#echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_DATADIR        '\e[${UI_COLCFG_NAME}m$PACKAGE_DATADIR\e[m'" >&2
#echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_INFODIR        '\e[${UI_COLCFG_NAME}m$PACKAGE_INFODIR\e[m'" >&2
#echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_LOCALEDIR      '\e[${UI_COLCFG_NAME}m$PACKAGE_LOCALEDIR\e[m'" >&2
#echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_MANDIR         '\e[${UI_COLCFG_NAME}m$PACKAGE_MANDIR\e[m'" >&2
#echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_DOCDIR         '\e[${UI_COLCFG_NAME}m$PACKAGE_DOCDIR\e[m'" >&2
#echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_HTMLDIR        '\e[${UI_COLCFG_NAME}m$PACKAGE_HTMLDIR\e[m'" >&2
#echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_DVIDIR         '\e[${UI_COLCFG_NAME}m$PACKAGE_DVIDIR\e[m'" >&2
#echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_PDFDIR         '\e[${UI_COLCFG_NAME}m$PACKAGE_PDFDIR\e[m'" >&2
#echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_PSDIR          '\e[${UI_COLCFG_NAME}m$PACKAGE_PSDIR\e[m'" >&2
#echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_HOST   '\e[${UI_COLCFG_NAME}m$PACKAGE_HOST\e[m'" >&2
#echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: PACKAGE_TARGET '\e[${UI_COLCFG_NAME}m$PACKAGE_TARGET\e[m'" >&2


_UTILITY_RELPATH=""
if [[ "$UTILITY_NAME" == *"/"* ]]; then
	_UTILITY_RELPATH="${UTILITY_NAME%/*}"
	if ! test -z "$_UTILITY_RELPATH"; then
		_UTILITY_RELPATH="$_UTILITY_RELPATH/"
	fi
fi
SRCPATH="$KOS_ROOT/binutils/src/${_UTILITY_RELPATH}$PACKAGE_NAME"
OPTPATH="$SYSROOT_BINUTILS_TARGET/opt/${_UTILITY_RELPATH}$PACKAGE_NAME"
DESTDIR="$SYSROOT_BINUTILS_TARGET/opt/${_UTILITY_RELPATH}${PACKAGE_NAME}-install"

# libtool tends to be buggy when using DESTDIR install, and tries to
# include host system libraries during linking when it really shouldn't
# s.a. http://metastatic.org/text/libtool.html
#
# As a work-around, don't directly invoke gcc & friends, but use a set of
# hack-wrappers that will filter out attempts to bind system libraries or
# headers.
. "$KOS_MISC/utilities/misc/gcc_hack.sh"

if test x"$MODE_FORCE_MAKE" == xyes || ! [ -d "$DESTDIR" ]; then
	if test x"$MODE_FORCE_MAKE" == xyes || ! [ -f "$OPTPATH/_didmake" ]; then
		if test x"$MODE_FORCE_CONF" == xyes || ! [ -f "$OPTPATH/Makefile" ]; then
			if ! [ -f "$SRCPATH/configure" ]; then
				# Remove $SRCPATH if it's just an empty directory
				rmdir "$SRCPATH" > /dev/null 2>&1
				if ! [ -d "$SRCPATH" ]; then
					BINUTILS_SOURCES="$(dirname "$SRCPATH")"
					cmd mkdir -p "$BINUTILS_SOURCES"
					cmd cd "$BINUTILS_SOURCES"
					if ! test -z "$PACKAGE_URL"; then
						#PACKAGE_URL_FILENAME="${PACKAGE_URL##*/}"
						# Figure out how to download+unpack the package
						if [[ "$PACKAGE_URL_FILENAME" == *.tar* ]]; then
							# Tar archive. Extract the filename of the file that will be downloaded
							# After downloading, make sure that filename becomes "$PACKAGE_NAME.tar[.gz|.xz|...]"
							_PACKAGE_URL_NAME="${PACKAGE_URL_FILENAME%.tar*}"
							PACKAGE_URL_FILENAME_EXT=".tar${PACKAGE_URL_FILENAME#*.tar}"
							_PACKAGE_URL_WANTED_FILENAME="${PACKAGE_NAME}.tar${PACKAGE_URL_FILENAME#*.tar}"
							if ! [ -f "$_PACKAGE_URL_WANTED_FILENAME" ]; then
								download_file "$PACKAGE_URL_FILENAME" "$PACKAGE_URL"
								if [ "$_PACKAGE_URL_WANTED_FILENAME" != "$PACKAGE_URL_FILENAME" ]; then
									cmd mv "$PACKAGE_URL_FILENAME" "$_PACKAGE_URL_WANTED_FILENAME"
								fi
							fi
							rm -r "./$_PACKAGE_URL_NAME" > /dev/null 2>&1
							cmd mkdir -p "$SRCPATH"
							cmd tar xvf "$_PACKAGE_URL_WANTED_FILENAME" -C "$SRCPATH"
						else
							# Unrecognized package distribution format
							echo -e "\e[${UI_COLCFG_ERR}mNo known way of extracting files\e[m from: '\e[${UI_COLCFG_NAME}m$PACKAGE_URL_FILENAME\e[m'" >&2
							exit 1
						fi
					elif ! test -z "$PACKAGE_GIT_URL"; then
						# Figure out the directory name that
						cmd mkdir -p "$SRCPATH"
						cmd cd "$SRCPATH"
						if ! test -z "$PACKAGE_GIT_COMMIT"; then
							# https://stackoverflow.com/questions/3489173/how-to-clone-git-repository-with-specific-revision-changeset
							cmd git init
							cmd git remote add origin "$PACKAGE_GIT_URL"
							cmd git fetch origin "$PACKAGE_GIT_COMMIT"
							cmd git reset --hard FETCH_HEAD
						else
							cmd git clone "$PACKAGE_GIT_URL"
						fi
					else
						echo -e "\e[${UI_COLCFG_ERR}mNo way of downloading\e[m \e[${UI_COLCFG_NAME}m$PACKAGE_NAME\e[m" >&2
					fi
				fi
				cmd cd "$SRCPATH"
				# Fix-up doubly-packaged packages
				while [[ `ls -A | wc -l` == 1 ]]; do
					subdirname=`ls -A`
					echo -e "Fix-up doubly-packed package '\e[${UI_COLCFG_NAME}m$subdirname\e[m' -> '\e[${UI_COLCFG_NAME}m${PACKAGE_NAME}\e[m'" >&2
					rm -r "$BINUTILS_SOURCES/.${PACKAGE_NAME}-real" > /dev/null 2>&1
					cmd mv "$subdirname" "../.${PACKAGE_NAME}-real"
					cmd cd ".."
					cmd rmdir "${PACKAGE_NAME}"
					cmd mv ".${PACKAGE_NAME}-real" "${PACKAGE_NAME}"
					cmd cd "$SRCPATH"
				done
				if ! test -z "$PACKAGE_GIT_URL"; then
					# Delete unnecessary .git history data
					rm -rf "$SRCPATH/.git" > /dev/null 2>&1
				fi

				# (Try to) generate configure (if it's missing)
				if ! [ -f "$SRCPATH/configure" ]; then
					${GM_HOOK_BEFORE_AUTOCONF:-:}
					if ! [ -f "$SRCPATH/configure" ]; then
						if [ -f "$SRCPATH/configure.ac" ]; then
							_PACKAGE_AUTOCONF_INPUT="$SRCPATH/configure.ac"
						elif [ -f "$SRCPATH/configure.in" ]; then
							_PACKAGE_AUTOCONF_INPUT="$SRCPATH/configure.in"
						else
							echo -e "\e[${UI_COLCFG_ERR}mNot a GNU autoconf project\e[m (missing file: '\e[${UI_COLCFG_NAME}mconfigure\e[m')" >&2
							exit 1
						fi
						# Check for autoconf dependencies of this project
						ac_requires_xorg=no
						while IFS= read -r line; do
							case "$line" in

							*XORG_MACROS_VERSION*)
								ac_requires_xorg=yes
								;;

							*) ;;
							esac
						done < "$_PACKAGE_AUTOCONF_INPUT"
						# Bind xorg-macros
						if test x"$ac_requires_xorg" != xno; then
							. "$KOS_MISC/utilities/Xorg/misc/xorg-macros.sh"
						fi
						# Generate all of the missing files.
						cmd autoreconf -i
						if ! [ -f "$SRCPATH/Makefile.in" ] && [ -f "$SRCPATH/Makefile.am" ]; then
							cmd cd "$SRCPATH"
							cmd automake
						fi
						if ! [ -f "$SRCPATH/configure" ]; then
							cmd cd "$SRCPATH"
							cmd autoconf
						fi
						# Try to conserve disk space by getting rid of cache files created by autoreconf.
						rm -r "$SRCPATH/autom4te.cache" > /dev/null 2>&1
					fi
				fi
			fi
			if [ -f "$KOS_PATCHES/$PACKAGE_NAME.patch" ]; then
				apply_patch "$SRCPATH" "$KOS_PATCHES/$PACKAGE_NAME.patch"
			fi

			${GM_HOOK_BEFORE_CONFARGS:-:}

			rm -r "$OPTPATH" > /dev/null 2>&1
			cmd mkdir -p "$OPTPATH"
			cmd cd "$OPTPATH"

			# Auto-configure arguments for ./configure
			if ! test -z "$PACKAGE_CONFIGURE"; then
				if test -z "$CONFIGURE"; then CONFIGURE=(); fi
				CONFIGURE+=("${PACKAGE_CONFIGURE[@]}")
				if ! test -z "$CONFIGURE"; then
					echo -e "\e[${UI_COLCFG_ACTION}mscan\e[m: Using given \e[${UI_COLCFG_NAME}m\$PACKAGE_CONFIGURE\e[m and \e[${UI_COLCFG_NAME}m\$CONFIGURE\e[m options:" >&2
					for opt in "${CONFIGURE[@]}"; do
						echo -e "	option: \e[${UI_COLCFG_NAME}m$opt\e[m" >&2
					done
				fi
			else
				# Auto-detect supported, but unset options
				if ! [ -f "$SRCPATH/._configure_help" ]; then
					echo -e "\e[${UI_COLCFG_ACTION}mhelp\e[m: '\e[${UI_COLCFG_NAME}m$SRCPATH/._configure_help\e[m'" >&2
					cmd "$SH" "$SRCPATH/configure" --help > "$SRCPATH/._configure_help.temp" 2>&1
					cmd mv "$SRCPATH/._configure_help.temp" "$SRCPATH/._configure_help"
				fi
				if ! test -z "$CONFIGURE"; then
					echo -e "\e[${UI_COLCFG_ACTION}mscan\e[m: Using given \e[${UI_COLCFG_NAME}m\$CONFIGURE\e[m options:" >&2
					for opt in "${CONFIGURE[@]}"; do
						echo -e "	option: \e[${UI_COLCFG_NAME}m$opt\e[m" >&2
					done
				else
					CONFIGURE=()
				fi
				hasconf() {
					printf -v _CONFSTR -- ',,%q' "${CONFIGURE[@]}"
					[[ "${_CONFSTR},," =~ .*,,"$1".* ]]
				}
				hasconfx() {
					printf -v _CONFSTR -- ',,%q' "${CONFIGURE[@]}"
					[[ "${_CONFSTR},," =~ ,,"$1",, ]]
				}
				addconf() {
					if ! hasconf "$1"; then
						echo -e "	option: \e[${UI_COLCFG_NAME}m$1$2\e[m" >&2
						CONFIGURE+=("$1$2");
					fi
				}
				addconfx() {
					if ! hasconfx "$1"; then
						echo -e "	option: \e[${UI_COLCFG_NAME}m$1\e[m" >&2
						CONFIGURE+=("$1");
					fi
				}

				echo -e "\e[${UI_COLCFG_ACTION}mscan\e[m: options from '\e[${UI_COLCFG_NAME}m$SRCPATH/configure --help\e[m'..." >&2
				while IFS= read -r line; do
					case "$line" in
					*--prefix=*)             addconf "--prefix="         "$PACKAGE_PREFIX"; ;;
					*--eprefix=*)            addconf "--eprefix="        "$PACKAGE_EPREFIX"; ;;
					*--exec-prefix=*)        addconf "--exec-prefix="    "$PACKAGE_EPREFIX"; ;;
					*--bindir=*)             addconf "--bindir="         "$PACKAGE_BINDIR"; ;;
					*--sbindir=*)            addconf "--sbindir="        "$PACKAGE_SBINDIR"; ;;
					*--libexecdir=*)         addconf "--libexecdir="     "$PACKAGE_LIBEXECDIR"; ;;
					*--sysconfdir=*)         addconf "--sysconfdir="     "$PACKAGE_SYSCONFDIR"; ;;
					*--sharedstatedir=*)     addconf "--sharedstatedir=" "$PACKAGE_SHAREDSTATEDIR"; ;;
					*--localstatedir=*)      addconf "--localstatedir="  "$PACKAGE_LOCALSTATEDIR"; ;;
					*--runstatedir=*)        addconf "--runstatedir="    "$PACKAGE_RUNSTATEDIR"; ;;
					*--libdir=*)             addconf "--libdir="         "$PACKAGE_LIBDIR"; ;;
					*--includedir=*)         addconf "--includedir="     "$PACKAGE_INCLUDEDIR"; ;;
					*--oldincludedir=*)      addconf "--oldincludedir="  "$PACKAGE_OLDINCLUDEDIR"; ;;
					*--datarootdir=*)        addconf "--datarootdir="    "$PACKAGE_DATAROOTDIR"; ;;
					*--datadir=*)            addconf "--datadir="        "$PACKAGE_DATADIR"; ;;
					*--infodir=*)            addconf "--infodir="        "$PACKAGE_INFODIR"; ;;
					*--localedir=*)          addconf "--localedir="      "$PACKAGE_LOCALEDIR"; ;;
					*--mandir=*)             addconf "--mandir="         "$PACKAGE_MANDIR"; ;;
					*--docdir=*)             addconf "--docdir="         "$PACKAGE_DOCDIR"; ;;
					*--htmldir=*)            addconf "--htmldir="        "$PACKAGE_HTMLDIR"; ;;
					*--dvidir=*)             addconf "--dvidir="         "$PACKAGE_DVIDIR"; ;;
					*--pdfdir=*)             addconf "--pdfdir="         "$PACKAGE_PDFDIR"; ;;
					*--psdir=*)              addconf "--psdir="          "$PACKAGE_PSDIR"; ;;
					*--host=*)               addconf "--host="           "$PACKAGE_HOST"; ;;
					*--target=*)             addconf "--target="         "$PACKAGE_TARGET"; ;;

					# System root
					*--with-sysroot*)
						addconf "--with-sysroot=" "$SYSROOT_BINUTILS_TARGET"
						;;

					# Install location
					*--with-install-prefix*)
						addconf "--with-install-prefix=" "$DESTDIR-temp"
						;;

					# PKG_CONFIG directory
					*--with-crosspkgdir=*)
						addconf "--with-crosspkgdir=" "$PKG_CONFIG_LIBDIR"
						;;

					# Name of the host machine
					*--build=*)
						if test -z "$PACKAGE_BUILD"; then PACKAGE_BUILD="$(gcc -dumpmachine)"; fi
						addconf "--build=" "$PACKAGE_BUILD"
						;;

					# Misc default feature selection
					*--disable-largefile* | *--enable-largefile*)
						if test -z "$PACKAGE_WITHOUT_LARGEFILE"; then
							addconfx "--enable-largefile"
						else
							addconfx "--disable-largefile"
						fi
						;;

					*--disable-nls* | *--enable-nls*)
						addconfx "--enable-nls"
						;;

					*--enable-malloc0returnsnull* | *--disable-malloc0returnsnull*)
						# Used by (some) Xorg utilities
						addconfx "--disable-malloc0returnsnull"
						;;

					*--disable-specs* | *--enable-specs*)
						# Used by Xorg utilities
						if test -z "$PACKAGE_WITH_SPECS"; then
							addconfx "--disable-specs"
						else
							addconfx "--enable-specs"
						fi
						;;

					*--disable-docs* | *--enable-docs*)
						if test -z "$PACKAGE_WITH_DOCS"; then
							addconfx "--disable-docs"
						else
							addconfx "--enable-docs"
						fi
						;;

					*--disable-doc* | *--enable-doc*)
						if test -z "$PACKAGE_WITH_DOCS"; then
							addconfx "--disable-doc"
						else
							addconfx "--enable-doc"
						fi
						;;

					*--without-docs* | *--with-docs*)
						if test -z "$PACKAGE_WITH_DOCS"; then
							addconfx "--without-docs"
						else
							addconfx "--with-docs"
						fi
						;;

					*--disable-devel-docs* | *--enable-devel-docs*)
						if test -z "$PACKAGE_WITH_DOCS"; then
							addconfx "--disable-devel-docs"
						else
							addconfx "--enable-devel-docs"
						fi
						;;

					*--without-manpages* | *--with-manpages*)
						if test -z "$PACKAGE_WITH_DOCS"; then
							addconfx "--without-manpages"
						else
							addconfx "--with-manpages"
						fi
						;;

					*--without-examples* | *--with-examples*)
						addconfx "--without-examples"
						;;

					*--without-doxygen* | *--with-doxygen*)
						addconfx "--without-doxygen"
						;;

					*--without-tests* | *--with-tests*)
						addconfx "--without-tests"
						;;

					*--disable-tests* | *--enable-tests*)
						addconfx "--disable-tests"
						;;

					*--disable-unit-tests* | *--enable-unit-tests*)
						addconfx "--disable-unit-tests"
						;;

					*--without-xmlto* | *--with-xmlto*)
						addconfx "--without-xmlto"
						;;

					*--without-fop* | *--with-fop*)
						addconfx "--without-fop"
						;;

					*--without-lint* | *--with-lint*)
						addconfx "--without-lint"
						;;

					*--without-launchd* | *--with-launchd*)
						addconfx "--without-launchd"
						;;

					# Misc options
					*--with-libiconv-prefix* | *--without-libiconv-prefix*)
						addconfx "--without-libiconv-prefix"
						;;

					*--with-libintl-prefix* | *--without-libintl-prefix*)
						addconfx "--without-libintl-prefix"
						;;

					*--with-gnu-ld* | *--without-gnu-ld*)
						if test -z "$PACKAGE_WITHOUT_GNU_LD"; then
							addconfx "--with-gnu-ld"
						else
							addconfx "--without-gnu-ld"
						fi
						;;

					*--enable-rpath* | *--disable-rpath*)
						addconfx "--disable-rpath"
						;;

					*--enable-shared* | *--disable-shared*)
						addconfx "--enable-shared"
						;;

					*--enable-static* | *--disable-static*)
						addconfx "--enable-static"
						;;

					*--with-shared* | *--without-shared*)
						# Alternate name for --enable-shared
						addconfx "--with-shared"
						;;

					*--with-normal* | *--without-normal*)
						# Alternate name for --enable-static
						addconfx "--with-normal"
						;;

					*--with-debug* | *--without-debug*)
						# Enable debug features (KOS is still young, so any debug
						# features offered by hosted applications should be enabled
						# by default)
						addconfx "--with-debug"
						;;

					*--with-profile* | *--without-profile*)
						# Disable profiling features by default
						addconfx "--without-profile"
						;;

					*--enable-stripping* | *--disable-stripping*)
						# Prevent debug symbols from being stripped
						addconfx "--disable-stripping"
						;;

					*--enable-pc-files* | *--disable-pc-files*)
						# Instruct to generate *.pc (PKG_CONFIG) files
						addconfx "--enable-pc-files"
						;;

					*--enable-lint-library* | *--disable-lint-library*)
						addconfx "--disable-lint-library"
						;;

					*--with-xsltproc* | *--without-xsltproc*)
						addconfx "--without-xsltproc"
						;;

					*--disable-doxygen-doc* | *--enable-doxygen-doc*)
						addconfx "--disable-doxygen-doc"
						;;

					*--disable-doxygen-dot* | *--enable-doxygen-dot*)
						addconfx "--disable-doxygen-dot"
						;;

					*--disable-doxygen-man* | *--enable-doxygen-man*)
						addconfx "--disable-doxygen-man"
						;;

					*--disable-doxygen-rtf* | *--enable-doxygen-rtf*)
						addconfx "--disable-doxygen-rtf"
						;;

					*--disable-doxygen-xml* | *--enable-doxygen-xml*)
						addconfx "--disable-doxygen-xml"
						;;

					*--disable-doxygen-chm* | *--enable-doxygen-chm*)
						addconfx "--disable-doxygen-chm"
						;;

					*--disable-doxygen-chi* | *--enable-doxygen-chi*)
						addconfx "--disable-doxygen-chi"
						;;

					*--disable-doxygen-html* | *--enable-doxygen-html*)
						addconfx "--disable-doxygen-html"
						;;

					*--disable-doxygen-ps* | *--enable-doxygen-ps*)
						addconfx "--disable-doxygen-ps"
						;;

					*--disable-doxygen-pdf* | *--enable-doxygen-pdf*)
						addconfx "--disable-doxygen-pdf"
						;;

					*--disable-year2038* | *--enable-year2038*)
						addconfx "--enable-year2038"
						;;

					*--enable-cross-guesses=*)
						addconf "--enable-cross-guesses=" "risky"
						;;

					*--disable-acl* | *--enable-acl*)
						# KOS doesn't have ACLs (and I don't plan on adding support for them anytime soon)
						addconfx "--disable-acl"
						;;

					*--disable-xattr* | *--enable-xattr*)
						addconfx "--enable-xattr"
						;;

					*--disable-install-examples* | *--enable-install-examples*)
						addconfx "--disable-install-examples"
						;;

					*--with-packager-bug-reports*)
						addconf "--with-packager-bug-reports=" "https://github.com/GrieferAtWork/KOSmk4"
						;;

					*--with-packager*)
						addconf "--with-packager=" "Griefer@Work"
						;;

					*) ;;
					esac
				done < "$SRCPATH/._configure_help"
			fi

			# Auto-configure a custom config.site for ./configure
			if ! test -z "${PACKAGE_CONFIG_SITE_CONTENT+x}"; then
				CONFIG_SITE_CONTENT="$PACKAGE_CONFIG_SITE_CONTENT
$CONFIG_SITE_CONTENT"
				if ! test -z "$CONFIG_SITE_CONTENT"; then
					echo -e "Using given \e[${UI_COLCFG_NAME}m\$PACKAGE_CONFIG_SITE_CONTENT\e[m and \e[${UI_COLCFG_NAME}m\$CONFIG_SITE_CONTENT\e[m options:" >&2
					while IFS= read -r line; do
						echo -e "	>> \e[${UI_COLCFG_NAME}m$line\e[m" >&2
					done <<< "$CONFIG_SITE_CONTENT"
				fi
			else
				# Auto-detect necessary config.site options
				if ! test -z "${CONFIG_SITE_CONTENT+x}"; then
					echo -e "Using given \e[${UI_COLCFG_NAME}m\$CONFIG_SITE_CONTENT\e[m options:" >&2
					while IFS= read -r line; do
						echo -e "	>> \e[${UI_COLCFG_NAME}m$line\e[m" >&2
					done <<< "$CONFIG_SITE_CONTENT"
					CONFIG_SITE_CONTENT="
$CONFIG_SITE_CONTENT"
				fi
				_config_site_option() {
					if ! [[ "$CONFIG_SITE_CONTENT" == *"
$1="* ]]; then
						echo -e "	config.site: \e[${UI_COLCFG_NAME}m$1=$2\e[m" >&2
						CONFIG_SITE_CONTENT="$CONFIG_SITE_CONTENT
$1=$2"
					fi
				}
				_test_links() {
					"${CROSS_PREFIX}gcc" -o "$OPTPATH/_gm_outfile" -x c - > /dev/null 2>&1
					local error="$?"
					unlink "$OPTPATH/_gm_outfile" > /dev/null 2>&1
					return "$error"
				}
				_test_expr() {
					_test_links <<< "$2
					static int a[($1) ? 1 : -1] = { 42 };
					int main() { return a[0]; }
					"
				}
				_eval_conf_line() {
					# NOTE: Options were discovered by searching through 3rd party packages for:
					#   - AC_TRY_RUN
					#   - AC_RUN_IFELSE
					# Matches were then individually looked at for use of AC_CACHE_CHECK

					local line="$1"
					case "$line" in

					*ac_cv_c_stack_direction*)
						# Stack growth direction
						. "$KOS_MISC/utilities/misc/target-info.sh"
						_config_site_option "ac_cv_c_stack_direction" "$TARGET_CONFIG_STACK_DIRECTION"
						;;

					*ac_cv_func_chown_works*)
						# Check if chown() accepts "(uid_t)-1, (gid_t)-1" (which it does on KOS)
						_config_site_option "ac_cv_func_chown_works" "yes"
						;;

					*ac_cv_func_fnmatch_works*)
						# "Define to 1 if your system has a working POSIX `fnmatch' function."
						_config_site_option "ac_cv_func_fnmatch_works" "yes"
						;;

					*ac_cv_func_fnmatch_gnu*)
						# "Define to 1 if your system has a working GNU `fnmatch' function."
						_config_site_option "ac_cv_func_fnmatch_gnu" "yes"
						;;

					*ac_cv_func_getgroups_works*)
						# >> assert(getgroups(0, 0) != -1)
						_config_site_option "ac_cv_func_getgroups_works" "yes"
						;;

					*ac_cv_func_lstat_dereferences_slashed_symlink*)
						# "... whether lstat correctly handles trailing slash"
						_config_site_option "ac_cv_func_lstat_dereferences_slashed_symlink" "yes"
						;;

					*ac_cv_func_malloc_0_nonnull*)
						# >> assert(malloc(0) != NULL)
						_config_site_option "ac_cv_func_malloc_0_nonnull" "yes"
						;;

					*ac_cv_func_memcmp_working*)
						# "... for working memcmp"
						_config_site_option "ac_cv_func_memcmp_working" "yes"
						;;

					*ac_cv_func_working_mktime*)
						# "... for working mktime"
						_config_site_option "ac_cv_func_working_mktime" "yes"
						;;

					*ac_cv_func_mmap_fixed_mapped*)
						# When cross-compiling, `AC_FUNC_MMAP' defaults to `no', even
						# though KOS has a fully working mmap(2) system call that would
						# pass all of autoconf's tests (at least I hope...)
						# Anyways: Just hammer it home to autoconf and manually tell it
						#          what we're capable of via a custom config.site entry.
						_config_site_option "ac_cv_func_mmap_fixed_mapped" "yes"
						;;

					*ac_cv_func_realloc_0_nonnull*)
						# >> assert(realloc(0) != NULL)
						_config_site_option "ac_cv_func_realloc_0_nonnull" "yes"
						;;

					*ac_cv_func_stat_empty_string_bug*)
						# >> assert(stat("", &st) == -1)
						_config_site_option "ac_cv_func_stat_empty_string_bug" "no"
						;;

					*ac_cv_func_lstat_empty_string_bug*)
						# >> assert(lstat("", &st) == -1)
						_config_site_option "ac_cv_func_lstat_empty_string_bug" "no"
						;;

					*ac_cv_func_strtod*)
						# "... for working strtod"
						_config_site_option "ac_cv_func_strtod" "yes"
						;;

					*ac_cv_func_strnlen_working*)
						# "... for working strnlen"
						_config_site_option "ac_cv_func_strnlen_working" "yes"
						;;

					*ac_cv_func_strcoll_works*)
						# "... for working strcoll"
						_config_site_option "ac_cv_func_strcoll_works" "yes"
						;;

					*ac_cv_func_utime_null*)
						# >> assert(IS_WORKING(utime(file, NULL)))
						_config_site_option "ac_cv_func_utime_null" "yes"
						;;

					*ac_cv_func_fork_works*)
						# >> assert(IS_WORKING(fork()))
						_config_site_option "ac_cv_func_fork_works" "yes"
						;;

					*ac_cv_func_vfork_works*)
						# >> assert(IS_WORKING(vfork()))
						_config_site_option "ac_cv_func_vfork_works" "yes"
						;;

					*ac_cv_func_wait3_rusage*)
						# "... for wait3 that fills in rusage"
						_config_site_option "ac_cv_func_wait3_rusage" "yes"
						;;

					*ac_cv_c_bigendian*)
						# "... whether byte ordering is bigendian"
						. "$KOS_MISC/utilities/misc/target-info.sh"
						if [[ "$TARGET_ENDIAN" == "big" ]]; then
							_config_site_option "ac_cv_c_bigendian" "yes"
						else
							_config_site_option "ac_cv_c_bigendian" "no"
						fi
						;;

					*ac_cv_c_little_endian*)
						# "... to see if this is a little endian host"
						. "$KOS_MISC/utilities/misc/target-info.sh"
						if [[ "$TARGET_ENDIAN" == "little" ]]; then
							_config_site_option "ac_cv_c_little_endian" "yes"
						else
							_config_site_option "ac_cv_c_little_endian" "no"
						fi
						;;

					*ac_cv_type_getgroups*)
						# "... type of array argument to getgroups"
						_config_site_option "ac_cv_type_getgroups" "gid_t"
						;;

					*ac_cv_func_closedir_void*)    _config_site_option "ac_cv_func_closedir_void"    "no";  ;; # DECLARED(void closedir(DIR *))
					*ac_cv_func_getpgrp_void*)     _config_site_option "ac_cv_func_getpgrp_void"     "yes"; ;; # DECLARED(pid_t getpgrp(void))
					*ac_cv_func_setpgrp_void*)     _config_site_option "ac_cv_func_setpgrp_void"     "yes"; ;; # DECLARED(pid_t setpgrp(void))
					*ac_cv_func_setvbuf_reversed*) _config_site_option "ac_cv_func_setvbuf_reversed" "no";  ;; # DECLARED(setvbuf(FILE *, int, char *, size_t))
					*ac_cv_func_memcmp_clean*)     _config_site_option "ac_cv_func_memcmp_clean"     "yes"; ;;
					*ac_cv_c_long_double*)         _config_site_option "ac_cv_c_long_double"         "yes"; ;; # Assuming gcc from toolchain
					*ac_cv_sys_restartable_syscalls*)
						_config_site_option "ac_cv_sys_restartable_syscalls" "yes"; ;;

					# Misc stuff from gnulib
					*ac_cv_func__set_invalid_parameter_handler*) # We might emulate it, but not by default; plus: this tends to screw up a bunch of stuff...
						_config_site_option "ac_cv_func__set_invalid_parameter_handler" "no"; ;;

					*gl_cv_func_aligned_alloc_works*) # aligned_alloc()
						_config_site_option "gl_cv_func_aligned_alloc_works" "yes"; ;;
					*gl_cv_func_btowc_nul*) # assert(btowc(0) == 0)
						_config_site_option "gl_cv_func_btowc_nul" "yes"; ;;
					*gl_cv_func_btowc_eof*) # assert(btowc(EOF) == WEOF)
						_config_site_option "gl_cv_func_btowc_eof" "yes"; ;;
					*gl_cv_func_c32rtomb_retval*) # assert(c32rtomb (NULL, 0, NULL) == 1)
						_config_site_option "gl_cv_func_c32rtomb_retval" "yes"; ;;
					*ac_cv_func_calloc_0_nonnull*) # assert(calloc(0, 0) != NULL)
						_config_site_option "ac_cv_func_calloc_0_nonnull" "yes"; ;;
					*gl_cv_func_realpath_works*) # realpath(3)
						_config_site_option "gl_cv_func_realpath_works" "yes"; ;;
					*gl_cv_func_cbrtf_works*)
						_config_site_option "gl_cv_func_cbrtf_works" "yes"; ;;
					*gl_cv_func_cbrtl_ieee*)
						_config_site_option "gl_cv_func_cbrtl_ieee" "yes"; ;;
					*gl_cv_func_cbrtl_works*)
						_config_site_option "gl_cv_func_cbrtl_works" "yes"; ;;
					*gl_cv_func_ceil_ieee*)
						_config_site_option "gl_cv_func_ceil_ieee" "yes"; ;;
					*gl_cv_func_ceilf_ieee*)
						_config_site_option "gl_cv_func_ceilf_ieee" "yes"; ;;
					*gl_cv_func_ceill_ieee*)
						_config_site_option "gl_cv_func_ceill_ieee" "yes"; ;;
					*gl_cv_func_ceill_works*)
						_config_site_option "gl_cv_func_ceill_works" "yes"; ;;
					*gl_cv_func_chown_slash_works*) # symlink(\"file\", \"link\"); assert(chown(\"link/\") != 0)
						_config_site_option "gl_cv_func_chown_slash_works" "yes"; ;;
					*gl_cv_func_chown_ctime_works*) # chown(3) updates st_ctime (yes it does, but the timestamp may not be persistent...)
						_config_site_option "gl_cv_func_chown_ctime_works" "yes"; ;;
					*gl_cv_func_chown_follows_symlink*)
						_config_site_option "gl_cv_func_chown_follows_symlink" "yes"; ;;
					*gl_cv_struct_dirent_d_ino*)
						_config_site_option "gl_cv_struct_dirent_d_ino" "yes"; ;;
					*gl_cv_func_dup_works*)
						_config_site_option "gl_cv_func_dup_works" "yes"; ;;
					*gl_cv_func_dup2_works*)
						_config_site_option "gl_cv_func_dup2_works" "yes"; ;;
					*gl_cv_func_duplocale_works*)
						_config_site_option "gl_cv_func_duplocale_works" "yes"; ;;
					*gl_cv_func_exp2_works*)
						_config_site_option "gl_cv_func_exp2_works" "yes"; ;;
					*gl_cv_func_exp2l_works*)
						_config_site_option "gl_cv_func_exp2l_works" "yes"; ;;
					*gl_cv_func_exp2l_ieee*)
						_config_site_option "gl_cv_func_exp2l_ieee" "yes"; ;;
					*gl_cv_func_expl_works*)
						_config_site_option "gl_cv_func_expl_works" "yes"; ;;
					*gl_cv_func_expm1_ieee*)
						_config_site_option "gl_cv_func_expm1_ieee" "yes"; ;;
					*gl_cv_func_expm1f_ieee*)
						_config_site_option "gl_cv_func_expm1f_ieee" "yes"; ;;
					*gl_cv_func_expm1f_works*)
						_config_site_option "gl_cv_func_expm1f_works" "yes"; ;;
					*gl_cv_func_expm1l_works*)
						_config_site_option "gl_cv_func_expm1l_works" "yes"; ;;
					*gl_cv_func_fabsl_works*)
						_config_site_option "gl_cv_func_fabsl_works" "yes"; ;;
					*gl_cv_func_open_directory_works*) # assert(open(\".\", O_RDONLY) != -1)
						_config_site_option "gl_cv_func_open_directory_works" "yes"; ;;
					*gl_cv_func_fchmodat_works*)
						_config_site_option "gl_cv_func_fchmodat_works" "yes"; ;;
					*gl_cv_func_fchownat_nofollow_works*) # AT_SYMLINK_NOFOLLOW
						_config_site_option "gl_cv_func_fchownat_nofollow_works" "yes"; ;;
					*gl_cv_func_fchownat_empty_filename_works*) # assert(fchownat(fd, \"\", ...) != 0)
						_config_site_option "gl_cv_func_fchownat_empty_filename_works" "yes"; ;;
					*gl_cv_func_fclose_stdin*)
						_config_site_option "gl_cv_func_fclose_stdin" "yes"; ;;
					*gl_cv_func_fcntl_f_dupfd_works*)
						_config_site_option "gl_cv_func_fcntl_f_dupfd_works" "yes"; ;;
					*gl_cv_func_fcntl_f_dupfd_cloexec*)
						_config_site_option "gl_cv_func_fcntl_f_dupfd_cloexec" "yes"; ;;
					*gl_cv_header_working_fcntl_h*)
						_config_site_option "gl_cv_header_working_fcntl_h" "yes"; ;;
					*gl_cv_func_fdopen_works*)
						_config_site_option "gl_cv_func_fdopen_works" "yes"; ;;
					*gl_cv_func_fdopendir_works*)
						_config_site_option "gl_cv_func_fdopendir_works" "yes"; ;;
					*gl_cv_func_fflush_stdin*)
						_config_site_option "gl_cv_func_fflush_stdin" "yes"; ;;
					*gl_cv_func_ffsll_works*)
						_config_site_option "gl_cv_func_ffsll_works" "yes"; ;;
					*gl_cv_func_floor_ieee*)
						_config_site_option "gl_cv_func_floor_ieee" "yes"; ;;
					*gl_cv_func_floorf_ieee*)
						_config_site_option "gl_cv_func_floorf_ieee" "yes"; ;;
					*gl_cv_func_fma_works*)
						_config_site_option "gl_cv_func_fma_works" "yes"; ;;
					*gl_cv_func_fmaf_works*)
						_config_site_option "gl_cv_func_fmaf_works" "yes"; ;;
					*gl_cv_func_fmal_works*)
						_config_site_option "gl_cv_func_fmal_works" "yes"; ;;
					*gl_cv_func_fmod_ieee*)
						_config_site_option "gl_cv_func_fmod_ieee" "yes"; ;;
					*gl_cv_func_fmodf_ieee*)
						_config_site_option "gl_cv_func_fmodf_ieee" "yes"; ;;
					*gl_cv_func_fmodl_ieee*)
						_config_site_option "gl_cv_func_fmodl_ieee" "yes"; ;;
					*gl_cv_func_fnmatch_* | *gl_fnmatch_required_lowercase* | *gl_fnmatch_cache_var*)
						_config_site_option "gl_cv_func_fnmatch_posix" "yes"
						_config_site_option "gl_cv_func_fnmatch_gnu" "yes"    # GNU extensions (s.a. __USE_GNU in <fnmatch.h>)
						;;
					*gl_cv_func_fopen_slash*) # assert(fopen(\"foo/\") == NULL)
						_config_site_option "gl_cv_func_fopen_slash" "yes"; ;;
					*gl_cv_func_fopen_mode_x*) # Support for \"x\" option
						_config_site_option "gl_cv_func_fopen_mode_x" "yes"; ;;
					*gl_cv_func_fopen_mode_e*) # Support for \"e\" option
						_config_site_option "gl_cv_func_fopen_mode_e" "yes"; ;;
					*gl_cv_func_fpurge_works*)
						_config_site_option "gl_cv_func_fpurge_works" "yes"; ;;
					*gl_cv_func_freopen_works_on_closed*) # freopen() works after close(fileno())
						_config_site_option "gl_cv_func_freopen_works_on_closed" "yes"; ;;
					*gl_cv_func_frexp_works*)
						_config_site_option "gl_cv_func_frexp_works" "yes"; ;;
					*gl_cv_func_frexpf_works*)
						_config_site_option "gl_cv_func_frexpf_works" "yes"; ;;
					*gl_cv_func_frexpl_works*)
						_config_site_option "gl_cv_func_frexpl_works" "yes"; ;;
					*gl_cv_func_fstatat_zero_flag*) # assert(fstatat(AT_FDCWD, \".\", atflags: 0) == 0)
						_config_site_option "gl_cv_func_fstatat_zero_flag" "yes"; ;;
					*fu_cv_sys_stat_statfs2_frsize*) # DECLARED(statfs(char const *file, struct statfs *buf)) && EXISTS(struct statfs::f_frsize)
						_config_site_option "fu_cv_sys_stat_statfs2_frsize" "yes"; ;;
					*fu_cv_sys_stat_statfs3_osf1*) # Some other statfs() variant
						_config_site_option "fu_cv_sys_stat_statfs3_osf1" "no"; ;;
					*fu_cv_sys_stat_statfs2_bsize*) # DECLARED(statfs(char const *file, struct statfs *buf)) && EXISTS(struct statfs::f_bsize)
						_config_site_option "fu_cv_sys_stat_statfs2_bsize" "yes"; ;;
					*fu_cv_sys_stat_statfs4*) # Some other statfs() variant
						_config_site_option "fu_cv_sys_stat_statfs4" "no"; ;;
					*fu_cv_sys_stat_statfs2_fsize*) # DECLARED(statfs(char const *file, struct statfs *buf)) && EXISTS(struct statfs::f_fsize)
						_config_site_option "fu_cv_sys_stat_statfs2_fsize" "no"; ;;
					*gl_cv_func_ftello_works*)
						_config_site_option "gl_cv_func_ftello_works" "yes"; ;;
					*gl_cv_func_futimens_works*)
						_config_site_option "gl_cv_func_futimens_works" "yes"; ;;
					*gl_cv_func_getcwd_null*) # assert(getcwd(NULL, 0) != NULL)   -- malloc'd buffer
						_config_site_option "gl_cv_func_getcwd_null" "yes"; ;;
					*gl_cv_func_getcwd_succeeds_beyond_4k*) # getcwd() with strlen(\$PWD) >= 4096 works  (KOS never imposes path limits, so: yes)
						_config_site_option "gl_cv_func_getcwd_succeeds_beyond_4k" "yes"; ;;
					*gl_cv_func_getcwd_path_max*) # getcwd() works for paths > PATH_MAX        (KOS never imposes path limits, so: yes)
						_config_site_option "gl_cv_func_getcwd_path_max" "yes"; ;;
					*gl_cv_func_working_getdelim*)
						_config_site_option "gl_cv_func_working_getdelim" "yes"; ;;
					*gl_cv_func_getdtablesize_works*)
						_config_site_option "gl_cv_func_getdtablesize_works" "yes"; ;;
					*gl_cv_func_getgroups_works*) # assert(getgroups(-1, list) == -1)
						_config_site_option "gl_cv_func_getgroups_works" "yes"; ;;
					*am_cv_func_working_getline*)
						_config_site_option "am_cv_func_working_getline" "yes"; ;;
					*gl_cv_func_getlogin_r_works*)
						_config_site_option "gl_cv_func_getlogin_r_works" "yes"; ;;
					*gl_cv_func_getopt_posix*)
						_config_site_option "gl_cv_func_getopt_posix" "yes"; ;;
					*gl_cv_func_getopt_gnu*)
						_config_site_option "gl_cv_func_getopt_gnu" "yes"; ;;
					*gl_cv_func_getopt_long_gnu*)
						_config_site_option "gl_cv_func_getopt_long_gnu" "yes"; ;;
					*gl_cv_glob_lists_symlinks*) # If a program ever needs it, _I_ want to implement it!
						_config_site_option "gl_cv_glob_lists_symlinks" "yes"; ;;
					*gl_cv_func_hypot_ieee*)
						_config_site_option "gl_cv_func_hypot_ieee" "yes"; ;;
					*gl_cv_func_hypotf_ieee*)
						_config_site_option "gl_cv_func_hypotf_ieee" "yes"; ;;
					*gl_cv_func_hypotf_works*)
						_config_site_option "gl_cv_func_hypotf_works" "yes"; ;;
					*gl_cv_func_hypotl_ieee*)
						_config_site_option "gl_cv_func_hypotl_ieee" "yes"; ;;
					*gl_cv_func_hypotl_works*)
						_config_site_option "gl_cv_func_hypotl_works" "yes"; ;;
					*am_cv_func_iconv_works*)
						_config_site_option "am_cv_func_iconv_works" "yes"; ;;
					*gl_cv_func_iconv_supports_utf*)
						_config_site_option "gl_cv_func_iconv_supports_utf" "yes"; ;;
					*gl_cv_func_ilogb_works*)
						_config_site_option "gl_cv_func_ilogb_works" "yes"; ;;
					*gl_cv_func_ilogbf_works*)
						_config_site_option "gl_cv_func_ilogbf_works" "yes"; ;;
					*gl_cv_func_ilogbl_works*)
						_config_site_option "gl_cv_func_ilogbl_works" "yes"; ;;
					*gl_cv_func_itold_works*)
						_config_site_option "gl_cv_func_itold_works" "yes"; ;;
					*gt_cv_locale_fake*)
						_config_site_option "gt_cv_locale_fake" "no"; ;;
					*gt_cv_func_uselocale_works*)
						_config_site_option "gt_cv_func_uselocale_works" "yes"; ;;
					*gl_cv_pipes_are_fifos*) # fstate(pipe()) --> S_IFIFO
						_config_site_option "gl_cv_pipes_are_fifos" "yes"; ;;
					*gl_cv_func_isfinitel_works*)
						_config_site_option "gl_cv_func_isfinitel_works" "yes"; ;;
					*gl_cv_func_isinfl_works*)
						_config_site_option "gl_cv_func_isinfl_works" "yes"; ;;
					*gl_cv_func_isnanf_works*)
						_config_site_option "gl_cv_func_isnanf_works" "yes"; ;;
					*gl_cv_func_isnanl_works*)
						_config_site_option "gl_cv_func_isnanl_works" "yes"; ;;
					*gl_cv_func_iswdigit_works*)
						_config_site_option "gl_cv_func_iswdigit_works" "yes"; ;;
					*gl_cv_func_iswxdigit_works*)
						_config_site_option "gl_cv_func_iswxdigit_works" "yes"; ;;
					*gl_cv_func_ldexpl_works*)
						_config_site_option "gl_cv_func_ldexpl_works" "yes"; ;;
					*gl_cv_func_link_works*)
						_config_site_option "gl_cv_func_link_works" "yes"; ;;
					*gl_cv_func_linkat_nofollow*)
						_config_site_option "gl_cv_func_linkat_nofollow" "yes"; ;;
					*gl_cv_func_linkat_slash*)
						_config_site_option "gl_cv_func_linkat_slash" "yes"; ;;
					*gl_cv_func_link_follows_symlink*) # link(symlink) creates hard-links of symlinks; use AT_SYMLINK_FOLLOW to follow them
						_config_site_option "gl_cv_func_link_follows_symlink" "no"; ;;
					*gl_cv_func_log_ieee*)
						_config_site_option "gl_cv_func_log_ieee" "yes"; ;;
					*gl_cv_func_log_works*)
						_config_site_option "gl_cv_func_log_works" "yes"; ;;
					*gl_cv_func_log1p_ieee*)
						_config_site_option "gl_cv_func_log1p_ieee" "yes"; ;;
					*gl_cv_func_log1pf_ieee*)
						_config_site_option "gl_cv_func_log1pf_ieee" "yes"; ;;
					*gl_cv_func_log1pf_works*)
						_config_site_option "gl_cv_func_log1pf_works" "yes"; ;;
					*gl_cv_func_log1pl_ieee*)
						_config_site_option "gl_cv_func_log1pl_ieee" "yes"; ;;
					*gl_cv_func_log1pl_works*)
						_config_site_option "gl_cv_func_log1pl_works" "yes"; ;;
					*gl_cv_func_log2_ieee*)
						_config_site_option "gl_cv_func_log2_ieee" "yes"; ;;
					*gl_cv_func_log2_works*)
						_config_site_option "gl_cv_func_log2_works" "yes"; ;;
					*gl_cv_func_log2f_ieee*)
						_config_site_option "gl_cv_func_log2f_ieee" "yes"; ;;
					*gl_cv_func_log2f_works*)
						_config_site_option "gl_cv_func_log2f_works" "yes"; ;;
					*gl_cv_func_log2l_works*)
						_config_site_option "gl_cv_func_log2l_works" "yes"; ;;
					*gl_cv_func_log10_ieee*)
						_config_site_option "gl_cv_func_log10_ieee" "yes"; ;;
					*gl_cv_func_log10_works*)
						_config_site_option "gl_cv_func_log10_works" "yes"; ;;
					*gl_cv_func_log10f_ieee*)
						_config_site_option "gl_cv_func_log10f_ieee" "yes"; ;;
					*gl_cv_func_log10f_works*)
						_config_site_option "gl_cv_func_log10f_works" "yes"; ;;
					*gl_cv_func_log10l_works*)
						_config_site_option "gl_cv_func_log10l_works" "yes"; ;;
					*gl_cv_func_logb_works*)
						_config_site_option "gl_cv_func_logb_works" "yes"; ;;
					*gl_cv_func_logbf_works*)
						_config_site_option "gl_cv_func_logbf_works" "yes"; ;;
					*gl_cv_func_logbl_works*)
						_config_site_option "gl_cv_func_logbl_works" "yes"; ;;
					*gl_cv_func_logf_ieee*)
						_config_site_option "gl_cv_func_logf_ieee" "yes"; ;;
					*gl_cv_func_logf_works*)
						_config_site_option "gl_cv_func_logf_works" "yes"; ;;
					*gl_cv_func_logl_works*)
						_config_site_option "gl_cv_func_logl_works" "yes"; ;;
					*ac_cv_type_long_long_int*) # At least with gcc
						_config_site_option "ac_cv_type_long_long_int" "yes"; ;;
					*gl_cv_func_lstat_dereferences_slashed_symlink*) # lstat(\"symlink/\") still dereferences (yes, it does on KOS)
						_config_site_option "gl_cv_func_lstat_dereferences_slashed_symlink" "yes"; ;;
					*gl_cv_malloc_alignment*)
						. "$KOS_MISC/utilities/misc/target-info.sh"
						_config_site_option "gl_cv_malloc_alignment" "$TARGET_CONFIG_ALIGNOF_MAXALIGN_T"; ;;
					*gl_cv_func_mbrlen_incomplete_state*)
						_config_site_option "gl_cv_func_mbrlen_incomplete_state" "yes"; ;;
					*gl_cv_func_mbrlen_retval*)
						_config_site_option "gl_cv_func_mbrlen_retval" "yes"; ;;
					*gl_cv_func_mbrlen_nul_retval*)
						_config_site_option "gl_cv_func_mbrlen_nul_retval" "yes"; ;;
					*gl_cv_func_mbrlen_empty_input*)
						_config_site_option "gl_cv_func_mbrlen_empty_input" "yes"; ;;
					*gl_cv_func_mbrtoc32_empty_input*)
						_config_site_option "gl_cv_func_mbrtoc32_empty_input" "yes"; ;;
					*gl_cv_func_mbrtoc32_sanitycheck*)
						_config_site_option "gl_cv_func_mbrtoc32_sanitycheck" "yes"; ;;
					*gl_cv_func_mbrtowc_incomplete_state*)
						_config_site_option "gl_cv_func_mbrtowc_incomplete_state" "yes"; ;;
					*gl_cv_func_mbrtowc_sanitycheck*)
						_config_site_option "gl_cv_func_mbrtowc_sanitycheck" "yes"; ;;
					*gl_cv_func_mbrtowc_null_arg1*)
						_config_site_option "gl_cv_func_mbrtowc_null_arg1" "yes"; ;;
					*gl_cv_func_mbrtowc_null_arg2*)
						_config_site_option "gl_cv_func_mbrtowc_null_arg2" "yes"; ;;
					*gl_cv_func_mbrtowc_retval*)
						_config_site_option "gl_cv_func_mbrtowc_retval" "yes"; ;;
					*gl_cv_func_mbrtowc_nul_retval*)
						_config_site_option "gl_cv_func_mbrtowc_nul_retval" "yes"; ;;
					*gl_cv_func_mbrtowc_stores_incomplete*)
						_config_site_option "gl_cv_func_mbrtowc_stores_incomplete" "yes"; ;;
					*gl_cv_func_mbrtowc_empty_input*)
						_config_site_option "gl_cv_func_mbrtowc_empty_input" "yes"; ;;
					*gl_cv_func_mbsnrtowcs_works_in_traditional_locale*)
						_config_site_option "gl_cv_func_mbsnrtowcs_works_in_traditional_locale" "yes"; ;;
					*gl_cv_func_mbsrtowcs_works*)
						_config_site_option "gl_cv_func_mbsrtowcs_works" "yes"; ;;
					*gl_cv_func_memalign_works*)
						_config_site_option "gl_cv_func_memalign_works" "yes"; ;;
					*gl_cv_func_memchr_works*)
						_config_site_option "gl_cv_func_memchr_works" "yes"; ;;
					*gl_cv_func_memcmp_working*)
						_config_site_option "gl_cv_func_memcmp_working" "yes"; ;;
					*gl_cv_func_memmem_works_always*) # Yes: memmem() works
						_config_site_option "gl_cv_func_memmem_works_always" "yes"; ;;
					*gl_cv_func_memmem_works_fast*) # Yes: our memmem() does a memchr(needle[0]) to filter candidates, so its the \"fast\" variant
						_config_site_option "gl_cv_func_memmem_works_fast" "yes"; ;;
					*gl_cv_func_mkdir_trailing_slash_works*) # assert(mkdir(\"foo/\") == 0)
						_config_site_option "gl_cv_func_mkdir_trailing_slash_works" "yes"; ;;
					*gl_cv_func_mkdir_trailing_dot_works*) # assert(mkdir(\"foo/./\") != 0)
						_config_site_option "gl_cv_func_mkdir_trailing_dot_works" "yes"; ;;
					*gl_cv_func_mkfifo_works*) # assert(mkfifo(\"foo/\") != 0)
						_config_site_option "gl_cv_func_mkfifo_works" "yes"; ;;
					*gl_cv_func_mkfifoat_works*) # assert(mkfifoat(\"foo/\") != 0)
						_config_site_option "gl_cv_func_mkfifoat_works" "yes"; ;;
					*gl_cv_func_mknod_works*) # mknod() can create FIFO w/o root (yes; that works on KOS)
						_config_site_option "gl_cv_func_mknod_works" "yes"; ;;
					*gl_cv_func_working_mkstemp*)
						_config_site_option "gl_cv_func_working_mkstemp" "yes"; ;;
					*gl_cv_func_working_mktime*)
						_config_site_option "gl_cv_func_working_mktime" "yes"; ;;
					*gl_cv_func_modf_ieee*)
						_config_site_option "gl_cv_func_modf_ieee" "yes"; ;;
					*gl_cv_func_modff_ieee*)
						_config_site_option "gl_cv_func_modff_ieee" "yes"; ;;
					*gl_cv_func_modfl_ieee*)
						_config_site_option "gl_cv_func_modfl_ieee" "yes"; ;;
					*gl_cv_func_mprotect_works*)
						_config_site_option "gl_cv_func_mprotect_works" "yes"; ;;
					*gl_cv_func_nanosleep*)
						_config_site_option "gl_cv_func_nanosleep" "yes"; ;;
					*gl_cv_func_nl_langinfo_yesexpr_works*) # assert(strcmp(nl_langinfo(YESEXPR), \"\") != 0)
						_config_site_option "gl_cv_func_nl_langinfo_yesexpr_works" "yes"; ;;
					*gl_cv_func_open_slash*) # assert(open(\"file/\") == -1)
						_config_site_option "gl_cv_func_open_slash" "yes"; ;;
					*gl_cv_func_perror_works*)
						_config_site_option "gl_cv_func_perror_works" "yes"; ;;
					*ac_cv_func_poll*)
						_config_site_option "ac_cv_func_poll" "yes"; ;;
					*gl_cv_func_poll*)
						_config_site_option "gl_cv_func_poll" "yes"; ;;
					*gl_cv_func_popen_works*)
						_config_site_option "gl_cv_func_popen_works" "yes"; ;;
					*gl_cv_func_posix_memalign_works*)
						_config_site_option "gl_cv_func_posix_memalign_works" "yes"; ;;
					*gl_cv_func_posix_spawn_works*)
						_config_site_option "gl_cv_func_posix_spawn_works" "yes"; ;;
					*gl_cv_func_posix_spawn_secure_exec*) # Yes, our posix_spawn() doesn't accept shell-scripts w/o #!-marker
						_config_site_option "gl_cv_func_posix_spawn_secure_exec" "yes"; ;;
					*gl_cv_func_posix_spawnp_secure_exec*) # *ditto*
						_config_site_option "gl_cv_func_posix_spawnp_secure_exec" "yes"; ;;
					*gl_cv_func_posix_spawn_file_actions_addclose_works*)
						_config_site_option "gl_cv_func_posix_spawn_file_actions_addclose_works" "yes"; ;;
					*gl_cv_func_posix_spawn_file_actions_adddup2_works*)
						_config_site_option "gl_cv_func_posix_spawn_file_actions_adddup2_works" "yes"; ;;
					*gl_cv_func_posix_spawn_file_actions_addopen_works*)
						_config_site_option "gl_cv_func_posix_spawn_file_actions_addopen_works" "yes"; ;;
					*gl_cv_func_pread_works*)
						_config_site_option "gl_cv_func_pread_works" "yes"; ;;
					*gl_cv_func_printf_sizes_c99*)
						_config_site_option "gl_cv_func_printf_sizes_c99" "yes"; ;;
					*gl_cv_func_printf_long_double*)
						_config_site_option "gl_cv_func_printf_long_double" "yes"; ;;
					*gl_cv_func_printf_infinite_long_double*)
						_config_site_option "gl_cv_func_printf_infinite_long_double" "yes"; ;;
					*gl_cv_func_printf_infinite*)
						_config_site_option "gl_cv_func_printf_infinite" "yes"; ;;
					*gl_cv_func_printf_directive_a*)
						_config_site_option "gl_cv_func_printf_directive_a" "yes"; ;;
					*gl_cv_func_printf_directive_f*)
						_config_site_option "gl_cv_func_printf_directive_f" "yes"; ;;
					*gl_cv_func_printf_directive_n*)
						_config_site_option "gl_cv_func_printf_directive_n" "yes"; ;;
					*gl_cv_func_printf_directive_ls*)
						_config_site_option "gl_cv_func_printf_directive_ls" "yes"; ;;
					*gl_cv_func_printf_positions*) # Yes: KOS has had support for these added a while ago!
						_config_site_option "gl_cv_func_printf_positions" "yes"; ;;
					*gl_cv_func_printf_flag_grouping*)
						_config_site_option "gl_cv_func_printf_flag_grouping" "yes"; ;;
					*gl_cv_func_printf_flag_leftadjust*)
						_config_site_option "gl_cv_func_printf_flag_leftadjust" "yes"; ;;
					*gl_cv_func_printf_flag_zero*)
						_config_site_option "gl_cv_func_printf_flag_zero" "yes"; ;;
					*gl_cv_func_printf_precision*)
						_config_site_option "gl_cv_func_printf_precision" "yes"; ;;
					*gl_cv_func_snprintf_truncation_c99*) # Yes, we do this now. But once-upon-a-time, this was a bug (s.a. snprintf(3))
						_config_site_option "gl_cv_func_snprintf_truncation_c99" "yes"; ;;
					*gl_cv_func_snprintf_retval_c99*)
						_config_site_option "gl_cv_func_snprintf_retval_c99" "yes"; ;;
					*gl_cv_func_snprintf_directive_n*)
						_config_site_option "gl_cv_func_snprintf_directive_n" "yes"; ;;
					*gl_cv_func_snprintf_size1*)
						_config_site_option "gl_cv_func_snprintf_size1" "yes"; ;;
					*gl_cv_func_vsnprintf_zerosize_c99*)
						_config_site_option "gl_cv_func_vsnprintf_zerosize_c99" "yes"; ;;
					*gl_cv_func_pselect_detects_ebadf*)
						_config_site_option "gl_cv_func_pselect_detects_ebadf" "yes"; ;;
					*gl_cv_pthread_rwlock_rdlock_prefer_writer*) # No, on KOS readers are preferred
						_config_site_option "gl_cv_pthread_rwlock_rdlock_prefer_writer" "no"; ;;
					*gl_cv_func_pthread_sigmask_in_libc_works*) # Yes, we have pthread_sigmask() w/o -lpthread (actually, we don't have -lpthread)
						_config_site_option "gl_cv_func_pthread_sigmask_in_libc_works" "yes"; ;;
					*gl_cv_func_pthread_sigmask_return_works*)
						_config_site_option "gl_cv_func_pthread_sigmask_return_works" "yes"; ;;
					*gl_cv_func_pthread_sigmask_unblock_works*)
						_config_site_option "gl_cv_func_pthread_sigmask_unblock_works" "yes"; ;;
					*gl_cv_func_ptsname_sets_errno*)
						_config_site_option "gl_cv_func_ptsname_sets_errno" "yes"; ;;
					*gl_cv_func_ptsname_r_retval_ok*)
						_config_site_option "gl_cv_func_ptsname_r_retval_ok" "yes"; ;;
					*gl_cv_func_isatty_sets_errno*)
						_config_site_option "gl_cv_func_isatty_sets_errno" "yes"; ;;
					*gl_cv_func_svid_putenv*)
						_config_site_option "gl_cv_func_svid_putenv" "yes"; ;;
					*gl_cv_func_pwrite_works*)
						_config_site_option "gl_cv_func_pwrite_works" "yes"; ;;
					*gl_cv_func_readlink_trailing_slash*) # assert(readlink(\"file/\") == -1)
						_config_site_option "gl_cv_func_readlink_trailing_slash" "yes"; ;;
					*gl_cv_func_readlink_truncate*) # Oof; don't remind me (s.a. AT_READLINK_REQSIZE)
						_config_site_option "gl_cv_func_readlink_truncate" "yes"; ;;
					*ac_cv_func_realloc_0_nonnull*) # assert(realloc(NULL, 0) != NULL)
						_config_site_option "ac_cv_func_realloc_0_nonnull" "yes"; ;;
					*gl_cv_func_re_compile_pattern_working*)
						_config_site_option "gl_cv_func_re_compile_pattern_working" "yes"; ;;
					*gl_cv_func_remainder_ieee*)
						_config_site_option "gl_cv_func_remainder_ieee" "yes"; ;;
					*gl_cv_func_remainderf_ieee*)
						_config_site_option "gl_cv_func_remainderf_ieee" "yes"; ;;
					*gl_cv_func_remainderf_works*)
						_config_site_option "gl_cv_func_remainderf_works" "yes"; ;;
					*gl_cv_func_remainderl_ieee*)
						_config_site_option "gl_cv_func_remainderl_ieee" "yes"; ;;
					*gl_cv_func_remainderl_works*)
						_config_site_option "gl_cv_func_remainderl_works" "yes"; ;;
					*gl_cv_func_remove_dir_works*) # Yes, remove() also removes directories (s.a. AT_REMOVEREG | AT_REMOVEDIR)
						_config_site_option "gl_cv_func_remove_dir_works" "yes"; ;;
					*gl_cv_func_rename_slash_dst_works*) # FIXME: yeah, this one's not 100% (s.a. sys_renameat2_impl)
						_config_site_option "gl_cv_func_rename_slash_dst_works" "yes"; ;;
					*gl_cv_func_rename_slash_src_works*) # FIXME: *ditto*
						_config_site_option "gl_cv_func_rename_slash_src_works" "yes"; ;;
					*gl_cv_func_rename_link_works*)
						_config_site_option "gl_cv_func_rename_link_works" "yes"; ;;
					*gl_cv_func_rename_dest_works*)
						_config_site_option "gl_cv_func_rename_dest_works" "yes"; ;;
					*gl_cv_func_rintl_works*)
						_config_site_option "gl_cv_func_rintl_works" "yes"; ;;
					*gl_cv_func_rmdir_works*)
						_config_site_option "gl_cv_func_rmdir_works" "yes"; ;;
					*gl_cv_func_rmdir_errno_not_empty*)
						_config_site_option "gl_cv_func_rmdir_errno_not_empty" "ENOTEMPTY"; ;;
					*gl_cv_func_round_works*)
						_config_site_option "gl_cv_func_round_works" "yes"; ;;
					*gl_cv_func_round_ieee*)
						_config_site_option "gl_cv_func_round_ieee" "yes"; ;;
					*gl_cv_func_roundf_works*)
						_config_site_option "gl_cv_func_roundf_works" "yes"; ;;
					*gl_cv_func_roundf_ieee*)
						_config_site_option "gl_cv_func_roundf_ieee" "yes"; ;;
					*gl_cv_func_roundl_ieee*)
						_config_site_option "gl_cv_func_roundl_ieee" "yes"; ;;
					*gl_cv_func_select_supports0*) # select(0, NULL, NULL, NULL, ...) works
						_config_site_option "gl_cv_func_select_supports0" "yes"; ;;
					*gl_cv_func_select_detects_ebadf*)
						_config_site_option "gl_cv_func_select_detects_ebadf" "yes"; ;;
					*gl_cv_func_setenv_works*)
						_config_site_option "gl_cv_func_setenv_works" "yes"; ;;
					*gl_cv_func_unsetenv_works*)
						_config_site_option "gl_cv_func_unsetenv_works" "yes"; ;;
					*gl_cv_func_setlocale_works*)
						_config_site_option "gl_cv_func_setlocale_works" "yes"; ;;
					*sv_cv_sigaltstack*)
						_config_site_option "sv_cv_sigaltstack" "yes"; ;;
					*sv_cv_sigaltstack_low_base*)
						_config_site_option "sv_cv_sigaltstack_low_base" "yes"; ;;
					*gl_cv_func_signbit*)
						_config_site_option "gl_cv_func_signbit" "yes"; ;;
					*gl_cv_func_signbit_builtins*) # At least on gcc
						_config_site_option "gl_cv_func_signbit_builtins" "yes"; ;;
					*gl_cv_func_signbit_gcc*) # Alias used by older gnulibs
						_config_site_option "gl_cv_func_signbit_gcc" "yes"; ;;
					*gl_cv_func_sleep_works*)
						_config_site_option "gl_cv_func_sleep_works" "yes"; ;;
					*gl_cv_func_sqrtl_works*)
						_config_site_option "gl_cv_func_sqrtl_works" "yes"; ;;
					*gl_cv_func_stat_file_slash*) # assert(stat(\"file/\") == -1)
						_config_site_option "gl_cv_func_stat_file_slash" "yes"; ;;
					*gl_cv_header_working_stdint_h*)
						_config_site_option "gl_cv_header_working_stdint_h" "yes"; ;;
					*gl_cv_func_stpncpy*)
						_config_site_option "gl_cv_func_stpncpy" "yes"; ;;
					*gl_cv_func_strcasestr_works_always*)
						_config_site_option "gl_cv_func_strcasestr_works_always" "yes"; ;;
					*gl_cv_func_strcasestr_linear*)
						_config_site_option "gl_cv_func_strcasestr_linear" "yes"; ;;
					*gl_cv_func_strchrnul_works*)
						_config_site_option "gl_cv_func_strchrnul_works" "yes"; ;;
					*gl_cv_func_working_strerror*)
						_config_site_option "gl_cv_func_working_strerror" "yes"; ;;
					*gl_cv_func_strerror_0_works*)
						_config_site_option "gl_cv_func_strerror_0_works" "yes"; ;;
					*gl_cv_func_strerror_r_works*)
						_config_site_option "gl_cv_func_strerror_r_works" "yes"; ;;
					*gl_cv_func_strerrorname_np_works*)
						_config_site_option "gl_cv_func_strerrorname_np_works" "yes"; ;;
					*gl_cv_strfmon_l_works*) # It doesn't, but I don't want it to be substituted; if it ends up needed, _I'll_ implement it
						_config_site_option "gl_cv_strfmon_l_works" "yes"; ;;
					*gl_cv_func_strncat_works*)
						_config_site_option "gl_cv_func_strncat_works" "yes"; ;;
					*gl_cv_func_strndup_works*)
						_config_site_option "gl_cv_func_strndup_works" "yes"; ;;
					*gl_cv_func_working_strsignal*)
						_config_site_option "gl_cv_func_working_strsignal" "yes"; ;;
					*gl_cv_func_strstr_works_always*)
						_config_site_option "gl_cv_func_strstr_works_always" "yes"; ;;
					*gl_cv_func_strstr_linear*)
						_config_site_option "gl_cv_func_strstr_linear" "yes"; ;;
					*gl_cv_func_strtod_works*)
						_config_site_option "gl_cv_func_strtod_works" "yes"; ;;
					*gl_cv_func_strtoimax*)
						_config_site_option "gl_cv_func_strtoimax" "yes"; ;;
					*gl_cv_func_strtok_r_works*)
						_config_site_option "gl_cv_func_strtok_r_works" "yes"; ;;
					*gl_cv_func_strtol_works*)
						_config_site_option "gl_cv_func_strtol_works" "yes"; ;;
					*gl_cv_func_strtold_works*)
						_config_site_option "gl_cv_func_strtold_works" "yes"; ;;
					*gl_cv_func_strtoll_works*)
						_config_site_option "gl_cv_func_strtoll_works" "yes"; ;;
					*gl_cv_func_strtoul_works*)
						_config_site_option "gl_cv_func_strtoul_works" "yes"; ;;
					*gl_cv_func_strtoull_works*)
						_config_site_option "gl_cv_func_strtoull_works" "yes"; ;;
					*gl_cv_func_symlink_works*) # assert(symlink(\"content\", \"file/\") == -1)
						_config_site_option "gl_cv_func_symlink_works" "yes"; ;;
					*gl_cv_func_symlinkat_works*) # assert(symlinkat(\"content\", \"file/\") == -1)
						_config_site_option "gl_cv_func_symlinkat_works" "yes"; ;;
					*gl_cv_func_thrd_join_works*)
						_config_site_option "gl_cv_func_thrd_join_works" "yes"; ;;
					*gl_cv_have_weak*) # KOS uses ELF, so yes
						_config_site_option "gl_cv_have_weak" "yes"; ;;
					*gl_cv_func_localtime_works*)
						_config_site_option "gl_cv_func_localtime_works" "yes"; ;;
					*gl_cv_func_tmpfile_works*)
						_config_site_option "gl_cv_func_tmpfile_works" "yes"; ;;
					*gl_cv_func_trunc_ieee*)
						_config_site_option "gl_cv_func_trunc_ieee" "yes"; ;;
					*gl_cv_func_truncate_works*) # assert(truncate(\"file/\") == -1)
						_config_site_option "gl_cv_func_truncate_works" "yes"; ;;
					*gl_cv_func_truncf_ieee*)
						_config_site_option "gl_cv_func_truncf_ieee" "yes"; ;;
					*gl_cv_func_truncl_works*)
						_config_site_option "gl_cv_func_truncl_works" "yes"; ;;
					*gl_cv_func_truncl_ieee*)
						_config_site_option "gl_cv_func_truncl_ieee" "yes"; ;;
					*gl_cv_func_tdelete_works*)
						_config_site_option "gl_cv_func_tdelete_works" "yes"; ;;
					*gl_cv_func_ttyname_r_not_stub*)
						_config_site_option "gl_cv_func_ttyname_r_not_stub" "yes"; ;;
					*gl_cv_func_ttyname_r_works*)
						_config_site_option "gl_cv_func_ttyname_r_works" "yes"; ;;
					*gl_cv_func_ungetc_works*)
						_config_site_option "gl_cv_func_ungetc_works" "yes"; ;;
					*gl_cv_func_unlink_honors_slashes*) # assert(unlink(\"file/\") == -1)
						_config_site_option "gl_cv_func_unlink_honors_slashes" "yes"; ;;
					*gl_cv_func_unlink_parent_fails*) # assert(unlink(\"..\") == -1)
						_config_site_option "gl_cv_func_unlink_parent_fails" "yes"; ;;
					*gl_cv_func_unlink_busy_text*) # assert(unlink(readlink(\"/proc/self/exe\")) == 0)   (yes: this works on KOS)
						_config_site_option "gl_cv_func_unlink_busy_text" "yes"; ;;
					*gl_cv_func_usleep_works*)
						_config_site_option "gl_cv_func_usleep_works" "yes"; ;;
					*gl_cv_func_utime_file_slash*) # assert(utime(\"file/\") == -1)
						_config_site_option "gl_cv_func_utime_file_slash" "yes"; ;;
					*gl_cv_func_futimesat_works*) # assert(futimesat(fd, NULL, NULL) == 0)
						_config_site_option "gl_cv_func_futimesat_works" "yes"; ;;
					*gl_cv_func_utimensat_works*)
						_config_site_option "gl_cv_func_utimensat_works" "yes"; ;;
					*gl_cv_func_working_utimes*)
						_config_site_option "gl_cv_func_working_utimes" "yes"; ;;
					*gl_cv_func_wcrtomb_works*)
						_config_site_option "gl_cv_func_wcrtomb_works" "yes"; ;;
					*gl_cv_func_wcrtomb_retval*)
						_config_site_option "gl_cv_func_wcrtomb_retval" "yes"; ;;
					*gl_cv_func_wcsnrtombs_works_in_traditional_locale*)
						_config_site_option "gl_cv_func_wcsnrtombs_works_in_traditional_locale" "yes"; ;;
					*gl_cv_func_wcsrtombs_termination*)
						_config_site_option "gl_cv_func_wcsrtombs_termination" "yes"; ;;
					*gl_cv_func_wcsrtombs_null*)
						_config_site_option "gl_cv_func_wcsrtombs_null" "yes"; ;;
					*gl_cv_func_wctob_works*)
						_config_site_option "gl_cv_func_wctob_works" "yes"; ;;
					*gl_cv_func_iswcntrl_works*)
						_config_site_option "gl_cv_func_iswcntrl_works" "yes"; ;;
					*gl_cv_func_wcwidth_works*)
						_config_site_option "gl_cv_func_wcwidth_works" "yes"; ;;
					*gl_cv_have_unlimited_file_name_length*)
						_config_site_option "gl_cv_have_unlimited_file_name_length" "yes"; ;;
					*gl_cv_func_free_preserves_errno*)
						_config_site_option "gl_cv_func_free_preserves_errno" "yes"; ;;
					*gl_cv_double_slash_root*) # It's complicated (s.a. `\\unix\...')
						_config_site_option "gl_cv_double_slash_root" "yes"; ;;
					*gl_cv_have_proc_uptime*)
						_config_site_option "gl_cv_have_proc_uptime" "yes"; ;;

					*gl_cv_func_mbrtoc32_C_locale_sans_EILSEQ* | \
					*gl_cv_func_mbrtowc_C_locale_sans_EILSEQ* | \
					*gl_cv_C_locale_sans_EILSEQ*)
						# Technically, we would have to say "no" here, because our C locale is utf-8, so
						# e.g.: mbrtowc(&wc, \"\\x80\", 1, &mbs) == (size_t)-2  (-2: incomplete sequence)
						# Meaning that our "C" locale isn't "free of encoding errors".
						#
						# For reference, here's gnulib's test program:
						# >> #include <limits.h>
						# >> #include <locale.h>
						# >> #include <wchar.h>
						# >> int main() {
						# >>     int i;
						# >>     char *locale = setlocale (LC_ALL, "C");
						# >>     if (!locale)
						# >>         return 2;
						# >>     for (i = CHAR_MIN; i <= CHAR_MAX; i++) {
						# >>         char c = i;
						# >>         wchar_t wc;
						# >>         mbstate_t mbs = { 0, };
						# >>         size_t ss = mbrtowc(&wc, &c, 1, &mbs);
						# >>         if (1 < ss)
						# >>             return 3;
						# >>     }
						# >>     return 0;
						# >> }
						# And yes: running this program under KOS returns "$? == 3", which
						# would indicate a failure.
						#
						# However, because gnulib >>>𝐒𝐔𝐗 𝐃𝟏𝐗<<<, guess what happens when
						# you use its own replacement for our perfectly working "mbrtowc",
						# after configuring it for utf-8 (as it also would if ran natively
						# under KOS)
						#
						# THATS RIGHT! IT RETURNS INCOMPLTE SEQUENCE ERRORS JUST LIKE OURS
						# DOES, MEANING THAT THIS FEATURE TEST IS TOTALLY SCREWED UP AND
						# WRONG!
						#
						# As a matter of fact, this test only normally succeeds on systems
						# with BROKEN (or non-utf-8) C locale environments.
						if false; then
							_config_site_option "gl_cv_func_mbrtoc32_C_locale_sans_EILSEQ" "no"
							_config_site_option "gl_cv_func_mbrtowc_C_locale_sans_EILSEQ" "no"
							_config_site_option "gl_cv_C_locale_sans_EILSEQ" "no"
							# NOTE: With these options, "gl_FUNC_MBRTOWC" would do:
							# >> case $gl_cv_C_locale_sans_EILSEQ in
							# >>   *yes) ;;
							# >>   *) AC_DEFINE([C_LOCALE_MAYBE_EILSEQ], [1],
							# >>        [Define to 1 if the C locale may have encoding errors.])
							# >>      REPLACE_MBRTOWC=1
							# >>      ;;
							# >> esac
							# Turning on "REPLACE_MBRTOWC=1", which is something we don't want
						else
							# Prevent gnulib from replacing perfectly operational functions
							# with a bloated replacement that exhibits the same "bugs" it was
							# meant to "fix" in the first place (though I wouldn't call them
							# "bugs", since THEY'RE INTENDED, CORRECT, DOCUMENTED, AND EXPECTED
							# BEHAVIOR!!!!)
							_config_site_option "gl_cv_func_mbrtoc32_C_locale_sans_EILSEQ" "yes"
							_config_site_option "gl_cv_func_mbrtowc_C_locale_sans_EILSEQ" "yes"
							_config_site_option "gl_cv_C_locale_sans_EILSEQ" "yes"
						fi
						;;
					############################################################################
					# Options we intentionally don't set (because they're too CPU-specific):
					# - gl_cv_cc_double_expbit0
					# - gl_cv_cc_float_expbit0
					# - gl_cv_cc_long_double_expbit0
					# - ac_cv_x87_double_rounding
					############################################################################

					############################################################################
					# Detection of type sizes always takes forever, so we speed it up
					*ac_cv_sizeof_*)
						. "$KOS_MISC/utilities/misc/target-info.sh"
						_config_site_option "ac_cv_sizeof_char" "$TARGET_CONFIG_SIZEOF_CHAR"
						_config_site_option "ac_cv_sizeof_short" "$TARGET_CONFIG_SIZEOF_SHORT"
						_config_site_option "ac_cv_sizeof_int" "$TARGET_CONFIG_SIZEOF_INT"
						_config_site_option "ac_cv_sizeof_long" "$TARGET_CONFIG_SIZEOF_LONG"
						_config_site_option "ac_cv_sizeof_long_long" "$TARGET_CONFIG_SIZEOF_LLONG"
						_config_site_option "ac_cv_sizeof_wchar_t" "$TARGET_CONFIG_SIZEOF_WCHAR_T"
						_config_site_option "ac_cv_sizeof_float" "$TARGET_CONFIG_SIZEOF_FLOAT"
						_config_site_option "ac_cv_sizeof_double" "$TARGET_CONFIG_SIZEOF_DOUBLE"
						_config_site_option "ac_cv_sizeof_long_double" "$TARGET_CONFIG_SIZEOF_LDOUBLE"
						_config_site_option "ac_cv_sizeof_void_p" "$TARGET_CONFIG_SIZEOF_POINTER"
						_config_site_option "ac_cv_sizeof_size_t" "$TARGET_CONFIG_SIZEOF_POINTER"
						_config_site_option "ac_cv_sizeof_ssize_t" "$TARGET_CONFIG_SIZEOF_POINTER"
						_config_site_option "ac_cv_sizeof_ptrdiff_t" "$TARGET_CONFIG_SIZEOF_POINTER"
						_config_site_option "ac_cv_sizeof_intptr_t" "$TARGET_CONFIG_SIZEOF_POINTER"
						_config_site_option "ac_cv_sizeof_uintptr_t" "$TARGET_CONFIG_SIZEOF_POINTER"
						;;
					*ac_cv_alignof_*)
						. "$KOS_MISC/utilities/misc/target-info.sh"
						_config_site_option "ac_cv_alignof_char" "$TARGET_CONFIG_ALIGNOF_CHAR"
						_config_site_option "ac_cv_alignof_short" "$TARGET_CONFIG_ALIGNOF_SHORT"
						_config_site_option "ac_cv_alignof_int" "$TARGET_CONFIG_ALIGNOF_INT"
						_config_site_option "ac_cv_alignof_long" "$TARGET_CONFIG_ALIGNOF_LONG"
						_config_site_option "ac_cv_alignof_long_long" "$TARGET_CONFIG_ALIGNOF_LLONG"
						_config_site_option "ac_cv_alignof_wchar_t" "$TARGET_CONFIG_ALIGNOF_WCHAR_T"
						_config_site_option "ac_cv_alignof_float" "$TARGET_CONFIG_ALIGNOF_FLOAT"
						_config_site_option "ac_cv_alignof_double" "$TARGET_CONFIG_ALIGNOF_DOUBLE"
						_config_site_option "ac_cv_alignof_long_double" "$TARGET_CONFIG_ALIGNOF_LDOUBLE"
						_config_site_option "ac_cv_alignof_void_p" "$TARGET_CONFIG_ALIGNOF_POINTER"
						_config_site_option "ac_cv_alignof_size_t" "$TARGET_CONFIG_ALIGNOF_POINTER"
						_config_site_option "ac_cv_alignof_ssize_t" "$TARGET_CONFIG_ALIGNOF_POINTER"
						_config_site_option "ac_cv_alignof_ptrdiff_t" "$TARGET_CONFIG_ALIGNOF_POINTER"
						_config_site_option "ac_cv_alignof_intptr_t" "$TARGET_CONFIG_ALIGNOF_POINTER"
						_config_site_option "ac_cv_alignof_uintptr_t" "$TARGET_CONFIG_ALIGNOF_POINTER"
						_config_site_option "ac_cv_alignof_maxalign_t" "$TARGET_CONFIG_ALIGNOF_MAXALIGN_T"
						;;
					############################################################################


					# Some more found in misc programs

					# nano
					*gl_cv_func_printf_enomem*) # printf() still works after ENOMEM
						_config_site_option "gl_cv_func_printf_enomem" "yes"; ;;
					*gt_cv_func_printf_posix*) # printf() is POSIX compliant
						_config_site_option "gt_cv_func_printf_posix" "yes"; ;;
					*gl_cv_func_gettimeofday_clobber*) # No, our gettimeofday() doesn't clobber localtime(3)'s buffer
						_config_site_option "gl_cv_func_gettimeofday_clobber" "no"; ;;
					*gt_cv_int_divbyzero_sigfpe*) # integer divide-by-zero raises SIGFPE (as long as you don't do a c++ `catch(...)' that doesn't rethrow the KOS exception)
						_config_site_option "gt_cv_int_divbyzero_sigfpe" "yes"; ;;

					# Xorg
					*xorg_cv_malloc0_returns_null*)
						_config_site_option "xorg_cv_malloc0_returns_null" "no"; ;;

					# Python
					*ac_cv_pthread_is_default*) # <pthread.h> works even without passing "-pthread" (yes: it does)
						_config_site_option "ac_cv_pthread_is_default" "yes"; ;;
					*ac_cv_pthread*)
						# Yes, our gcc does define "-pthread", but it only does "-D_REENTRANT"
						# This in turn turns on "__USE_REENTRANT", which is used to expose a
						# couple of functions here and there, but doesn't affect <pthread.h>
						_config_site_option "ac_cv_pthread" "yes"; ;;
					*ac_cv_kpthread*) # No, our gcc doesn't accept "-Kpthread"
						_config_site_option "ac_cv_kpthread" "no"; ;;
					*ac_cv_kthread*) # No, our gcc doesn't accept "-Kthread"
						_config_site_option "ac_cv_kthread" "no"; ;;
					*ac_cv_pthread_system_supported*) # pthread_attr_setscope(PTHREAD_SCOPE_SYSTEM) doesn't return an error
						_config_site_option "ac_cv_pthread_system_supported" "yes"; ;;
					*ac_cv_have_chflags*) # As for right now, we don't have this function. But it may be added someday
						_config_site_option "ac_cv_have_chflags" "no"; ;;
					*ac_cv_have_lchflags*) # As for right now, we don't have this function. But it may be added someday
						_config_site_option "ac_cv_have_lchflags" "no"; ;;
					*ac_cv_buggy_getaddrinfo*)
						_config_site_option "ac_cv_buggy_getaddrinfo" "no"; ;;
					*ac_cv_little_endian_double* | *ac_cv_big_endian_double* | *ac_cv_mixed_endian_double*)
						if _test_expr "__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__" "#include <ieee754.h>"; then
							_config_site_option "ac_cv_little_endian_double" "no"
							_config_site_option "ac_cv_big_endian_double" "yes"
							_config_site_option "ac_cv_mixed_endian_double" "no"
						elif _test_expr "__FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__" "#include <ieee754.h>"; then
							_config_site_option "ac_cv_little_endian_double" "no"
							_config_site_option "ac_cv_big_endian_double" "no"
							_config_site_option "ac_cv_mixed_endian_double" "yes"
						else
							_config_site_option "ac_cv_little_endian_double" "yes"
							_config_site_option "ac_cv_big_endian_double" "no"
							_config_site_option "ac_cv_mixed_endian_double" "no"
						fi
						;;
					*ac_cv_tanh_preserves_zero_sign*)
						_config_site_option "ac_cv_tanh_preserves_zero_sign" "yes"; ;;
					*ac_cv_posix_semaphores_enabled*)
						_config_site_option "ac_cv_posix_semaphores_enabled" "yes"; ;;
					*ac_cv_broken_sem_getvalue*)
						_config_site_option "ac_cv_broken_sem_getvalue" "no"; ;;
					*ac_cv_file__dev_ptmx*)
						_config_site_option "ac_cv_file__dev_ptmx" "no"; ;;
					*ac_cv_file__dev_ptc*)
						_config_site_option "ac_cv_file__dev_ptc" "no"; ;;
					*ac_cv_wchar_t_signed*)
						# s.a. __WCHAR_UNSIGNED__
						if _test_expr "(wchar_t)-1 < (wchar_t)0" "#include <wchar.h>"; then
							_config_site_option "ac_cv_wchar_t_signed" "yes"
						else
							_config_site_option "ac_cv_wchar_t_signed" "no"
						fi
						;;
					*ac_cv_c_char_unsigned*)
						# s.a. __CHAR_UNSIGNED__
						if _test_expr "(char)-1 < (char)0" ""; then
							_config_site_option "ac_cv_c_char_unsigned" "no"
						else
							_config_site_option "ac_cv_c_char_unsigned" "yes"
						fi
						;;
					*ac_cv_rshift_extends_sign*)
						# s.a. __ARCH_SIGNED_SHIFT_IS_SDIV
						if _test_links <<< "
							#include <asm/signed-shift.h>
							#ifndef __ARCH_SIGNED_SHIFT_IS_SDIV
							#error choke me
							#endif
							int main() { return 0; }
						"; then
							_config_site_option "ac_cv_rshift_extends_sign" "yes"
						else
							_config_site_option "ac_cv_rshift_extends_sign" "no"
						fi
						;;
					*ac_cv_broken_nice*)
						_config_site_option "ac_cv_broken_nice" "no"; ;;
					*ac_cv_broken_poll*)
						_config_site_option "ac_cv_broken_poll" "no"; ;;
					*ac_cv_working_tzset*)
						_config_site_option "ac_cv_working_tzset" "yes"; ;;
					*ac_cv_have_long_long_format*) # printf("%lld")
						_config_site_option "ac_cv_have_long_long_format" "yes"; ;;
					*ac_cv_have_size_t_format*) # printf("%zd")
						_config_site_option "ac_cv_have_size_t_format" "yes"; ;;
					*ac_cv_computed_gotos*) # At least under GCC
						_config_site_option "ac_cv_computed_gotos" "yes"; ;;

					# GMP
					*gmp_cv_func_vsnprintf*)
						_config_site_option "gmp_cv_func_vsnprintf" "yes"; ;;
					*gmp_cv_asm_underscore*)
						_config_site_option "gmp_cv_asm_underscore" "no"; ;;

					# binutils
					*ac_cv_func_strncmp_works*)
						_config_site_option "ac_cv_func_strncmp_works" "yes"; ;;
					*tcl_cv_api_serial*)
						_config_site_option "tcl_cv_api_serial" "termios"; ;;
					*tcl_cv_strtod_buggy*)
						_config_site_option "tcl_cv_strtod_buggy" "ok"; ;;
					*gcc_cv_have_tls*)
						_config_site_option "gcc_cv_have_tls" "yes"; ;;
					*ac_cv_have_elf_style_weakref*)
						_config_site_option "ac_cv_have_elf_style_weakref" "yes"; ;;

					# gcc
					*gcc_cv_initfini_array*)
						_config_site_option "gcc_cv_initfini_array" "yes"; ;;
					*gcc_cv_func_mbstowcs_works*) # assert(!CRASHES(mbstowcs(0, "", 0)))  (standards don't mandate this to work, so it doesn't on KOS)
						_config_site_option "gcc_cv_func_mbstowcs_works" "no"; ;;
					*libgfor_cv_have_unlink_open_file*) # "...whether the target can unlink an open file"
						_config_site_option "libgfor_cv_have_unlink_open_file" "yes"; ;;
					*libgfor_cv_have_crlf*) # No, KOS likes to use "\n" (but we do accept "\r\n" in most places, including `fgets(3)')
						_config_site_option "libgfor_cv_have_crlf" "no"; ;;
					*libgfor_cv_have_working_stat*)
						_config_site_option "libgfor_cv_have_working_stat" "yes"; ;;
					*libgo_cv_lib_setcontext_clobbers_tls*)
						_config_site_option "libgo_cv_lib_setcontext_clobbers_tls" "no"; ;;

					# libncurses
					*cf_cv_good_bcopy*) # bcopy() allows overlapping, like memmove()
						_config_site_option "cf_cv_good_bcopy" "yes"; ;;
					*cf_cv_func_nanosleep*)
						_config_site_option "cf_cv_func_nanosleep" "yes"; ;;
					*cf_cv_working_poll*)
						_config_site_option "cf_cv_working_poll" "yes"; ;;
					*cf_cv_link_funcs*)
						_config_site_option "cf_cv_link_funcs" "yes"; ;;
					*cf_cv_func_mkstemp*)
						_config_site_option "cf_cv_func_mkstemp" "yes"; ;;

					# mc
					*samba_cv_have_longlong*)
						_config_site_option "samba_cv_have_longlong" "yes"; ;;
					*samba_cv_HAVE_GETTIMEOFDAY_TZ*)
						_config_site_option "samba_cv_HAVE_GETTIMEOFDAY_TZ" "yes"; ;;
					*samba_cv_HAVE_BROKEN_READDIR*)
						_config_site_option "samba_cv_HAVE_BROKEN_READDIR" "no"; ;;

					# bash
					*bash_cv_sys_errlist*)
						# This test is broken because it needlessly tries to `extern char *sys_errlist[];'
						# (which fails because of how we `#define sys_errlist')
						_config_site_option "bash_cv_sys_errlist" "yes"; ;;
					*bash_cv_sys_siglist*)
						_config_site_option "bash_cv_sys_siglist" "yes"; ;;
					*bash_cv_under_sys_siglist*)
						_config_site_option "bash_cv_under_sys_siglist" "yes"; ;;
					*bash_cv_dup2_broken*)
						_config_site_option "bash_cv_dup2_broken" "no"; ;;
					*bash_cv_func_ctype_nonascii*)
						_config_site_option "bash_cv_func_ctype_nonascii" "yes"; ;;
					*bash_cv_printf_declared*)
						_config_site_option "bash_cv_printf_declared" "yes"; ;;
					*bash_cv_opendir_not_robust*)
						_config_site_option "bash_cv_opendir_not_robust" "no"; ;;
					*bash_cv_type_rlimit*)
						_config_site_option "bash_cv_type_rlimit" "rlim_t"; ;;
					*bash_cv_getenv_redef*) # Please don't redefine stuff from libc ~_~
						_config_site_option "bash_cv_getenv_redef" "no"; ;;
					*bash_cv_ulimit_maxfds*)
						_config_site_option "bash_cv_ulimit_maxfds" "yes"; ;;
					*bash_cv_getcwd_malloc*)
						_config_site_option "bash_cv_getcwd_malloc" "yes"; ;;
					*bash_cv_fnm_extmatch*)
						_config_site_option "bash_cv_fnm_extmatch" "yes"; ;;
					*bash_cv_func_sigsetjmp*)
						_config_site_option "bash_cv_func_sigsetjmp" "present"; ;;
					*bash_cv_func_strcoll_broken*)
						_config_site_option "bash_cv_func_strcoll_broken" "no"; ;;
					*bash_cv_printf_a_format*)
						_config_site_option "bash_cv_printf_a_format" "yes"; ;;
					*bash_cv_pgrp_pipe*)
						_config_site_option "bash_cv_pgrp_pipe" "no"; ;;
					*bash_cv_must_reinstall_sighandlers*)
						_config_site_option "bash_cv_must_reinstall_sighandlers" "no"; ;;
					*bash_cv_sys_named_pipes*)
						_config_site_option "bash_cv_sys_named_pipes" "yes"; ;;
					*bash_cv_unusable_rtsigs*)
						_config_site_option "bash_cv_unusable_rtsigs" "no"; ;;
					*bash_cv_wcwidth_broken*)
						_config_site_option "bash_cv_wcwidth_broken" "no"; ;;
					*ac_cv_rl_version*)
						READLINE_VERSION="?"
						while IFS= read -r readline_config_line; do
							case "$readline_config_line" in
							"Version: "*) READLINE_VERSION="${readline_config_line:9}"; ;;
							"Version:"*)  READLINE_VERSION="${readline_config_line:8}"; ;;
							*) ;;
							esac
						done < "$SYSROOT_BINUTILS_TARGET/opt/pkg_config/readline.pc"
						_config_site_option "ac_cv_rl_version" "$READLINE_VERSION"; ;;
					*bash_cv_wcontinued_broken*)
						_config_site_option "bash_cv_wcontinued_broken" "no"; ;;
					*bash_cv_func_snprintf*)
						_config_site_option "bash_cv_func_snprintf" "yes"; ;;
					*bash_cv_func_vsnprintf*)
						_config_site_option "bash_cv_func_vsnprintf" "yes"; ;;
					*bash_cv_wexitstatus_offset*) # This "8" is the same 8 as in `__WEXITSTATUS` from <asm/os/kos/wait.h>
						_config_site_option "bash_cv_wexitstatus_offset" "8"; ;;
					*bash_cv_func_sbrk*)
						_config_site_option "bash_cv_func_sbrk" "yes"; ;;
					*bash_cv_fnmatch_equiv_fallback*) # TODO: Add support for this
						_config_site_option "bash_cv_fnmatch_equiv_fallback" "no"; ;;

					*) ;;
					esac
				}

				# PACKAGE_CONFIGURE_SITE_SCANNED_FILES: Master override for list of files scanned for config.site options (absolute)
				# CONFIGURE_SITE_SCANNED_FILES:         Like $PACKAGE_CONFIGURE_SITE_SCANNED_FILES, but files are src-relative
				# EXTRA_CONFIGURE_SITE_SCANNED_FILES:   Like $CONFIGURE_SITE_SCANNED_FILES, but don't override default; only append
				if test -z "${PACKAGE_CONFIGURE_SITE_SCANNED_FILES+x}"; then
					PACKAGE_CONFIGURE_SITE_SCANNED_FILES=("$SRCPATH/configure")
					if ! test -z "${CONFIGURE_SITE_SCANNED_FILES+x}"; then
						PACKAGE_CONFIGURE_SITE_SCANNED_FILES=()
						if test -z "$EXTRA_CONFIGURE_SITE_SCANNED_FILES"; then EXTRA_CONFIGURE_SITE_SCANNED_FILES=(); fi
						EXTRA_CONFIGURE_SITE_SCANNED_FILES+=("${CONFIGURE_SITE_SCANNED_FILES[@]}")
					fi
					if ! test -z "${EXTRA_CONFIGURE_SITE_SCANNED_FILES+x}"; then
						for extra_configure_site_scan_file in "${EXTRA_CONFIGURE_SITE_SCANNED_FILES[@]}"; do
							PACKAGE_CONFIGURE_SITE_SCANNED_FILES+=("$SRCPATH/$extra_configure_site_scan_file")
						done
					fi
				fi
				if ! test -z "$PACKAGE_CONFIGURE_SITE_SCANNED_FILES"; then
					for configure_site_scan_filename in "${PACKAGE_CONFIGURE_SITE_SCANNED_FILES[@]}"; do
						echo -e "\e[${UI_COLCFG_ACTION}mscan\e[m: for needed \e[${UI_COLCFG_NAME}mconfig.site\e[m options '\e[${UI_COLCFG_NAME}m${configure_site_scan_filename}\e[m'..." >&2
						while IFS= read -r line; do
							_eval_conf_line "$line"
						done < "${configure_site_scan_filename}"
					done
				fi
			fi
			(
				export CC="${CROSS_PREFIX}gcc"
				export CFLAGS="-ggdb"
				export CXX="${CROSS_PREFIX}g++"
				export CXXFLAGS="-ggdb"
				if ! test -z "${PACKAGE_CFLAGS+x}"; then export CFLAGS="$CFLAGS $PACKAGE_CFLAGS"; fi
				if ! test -z "${PACKAGE_CXXFLAGS+x}"; then export CXXFLAGS="$CXXFLAGS $PACKAGE_CXXFLAGS"; fi
				if ! test -z "${PACKAGE_LDFLAGS+x}"; then export LDFLAGS="$PACKAGE_LDFLAGS"; fi
				if ! test -z "${PACKAGE_CCFLAGS+x}"; then
					export CFLAGS="$CFLAGS $PACKAGE_CCFLAGS";
					export CXXFLAGS="$CXXFLAGS $PACKAGE_CCFLAGS";
				fi
				export CPP="${CROSS_PREFIX}cpp"
				export CXXCPP="${CROSS_PREFIX}cpp"
				export NM="${CROSS_PREFIX}nm"
				export LD="${CROSS_PREFIX}ld"
				export OBJCOPY="${CROSS_PREFIX}objcopy"
				export OBJDUMP="${CROSS_PREFIX}objdump"
				export READELF="${CROSS_PREFIX}readelf"
#				export SIZE="${CROSS_PREFIX}size"
				export STRIP="${CROSS_PREFIX}strip"
				export AR="${CROSS_PREFIX}ar"
				if ! test -z "${CONFIG_SITE_CONTENT+x}"; then
					cat > "$OPTPATH/config.site" <<< "$CONFIG_SITE_CONTENT"
					export CONFIG_SITE="$OPTPATH/config.site"
				fi
				${GM_HOOK_BEFORE_CONFIGURE:-:}
				cmd cd "$OPTPATH"
				if ! test -z "${CONFIG_SITE+x}"; then
					echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: Using \e[${UI_COLCFG_NAME}m${CONFIG_SITE}\e[m for '\e[${UI_COLCFG_NAME}m./configure\e[m'..." >&2
				fi
				echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: Now running \e[${UI_COLCFG_NAME}m$PACKAGE_NAME\e[m: '\e[${UI_COLCFG_NAME}m./configure\e[m'..." >&2
				cmd "$SH" "$SRCPATH/configure" "${CONFIGURE[@]}"
			) || exit $?
			${GM_HOOK_AFTER_CONFIGURE:-:}
		fi # if test x"$MODE_FORCE_CONF" == xyes || ! [ -f "$OPTPATH/Makefile" ];
		cmd cd "$OPTPATH"
		if [ -f "config.site" ]; then
			# If present, also set the config.site
			export CONFIG_SITE="$OPTPATH/config.site"
		fi
		${GM_HOOK_BEFORE_MAKE:-:}
		if ! test -z "${CONFIG_SITE+x}"; then
			echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: Using \e[${UI_COLCFG_NAME}m${CONFIG_SITE}\e[m for '\e[${UI_COLCFG_NAME}mmake\e[m'..." >&2
		fi
		echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: Now running \e[${UI_COLCFG_NAME}m$PACKAGE_NAME\e[m: '\e[${UI_COLCFG_NAME}mmake\e[m'..." >&2
		if ! test -z "${MAKE_TARGET+x}"; then
			#cmd make "${MAKE_TARGET}"
			cmd make -j "$MAKE_PARALLEL_COUNT" "${MAKE_TARGET}"
		else
			cmd make -j "$MAKE_PARALLEL_COUNT"
		fi
		${GM_HOOK_AFTER_MAKE:-:}
		> "$OPTPATH/_didmake"
	fi     # if test x"$MODE_FORCE_MAKE" == xyes || ! [ -f "$OPTPATH/_didmake" ]
	cmd cd "$OPTPATH"
	# Don't directly install to $DESTDIR to prevent a successful install
	# from being detected when "make install" fails, or get interrupted.
	rm -r "$DESTDIR-temp" > /dev/null 2>&1
	echo -e "\e[${UI_COLCFG_ACTION}mgnu_make\e[m: Now running \e[${UI_COLCFG_NAME}m$PACKAGE_NAME\e[m: '\e[${UI_COLCFG_NAME}mmake install\e[m'..." >&2
	(
		export DESTDIR="$DESTDIR-temp"
		${GM_HOOK_BEFORE_INSTALL:-:}
		cmd make -j "$MAKE_PARALLEL_COUNT" DESTDIR="$DESTDIR" "${MAKE_TARGET_INSTALL:-install}"
	) || exit $?
	${GM_HOOK_AFTER_INSTALL:-:}
	rm -r "$DESTDIR" > /dev/null 2>&1
	cmd mv "$DESTDIR-temp" "$DESTDIR"
fi         # if test x"$MODE_FORCE_MAKE" == xyes || ! [ -d "$DESTDIR" ]

# Install to disk
. "$KOS_MISC/utilities/misc/install-DESTDIR.sh"
