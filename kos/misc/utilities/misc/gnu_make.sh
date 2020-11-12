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

# Helpers to automate configure+make+install of packages that make
# use of GNU autoconf+automake

if test -z "$PACKAGE_URL"; then
	echo "Missing variable: PACKAGE_URL"
	exit 1
fi

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
if test -z "$PACKAGE_LIBDIR";         then PACKAGE_LIBDIR="${PACKAGE_EPREFIX%/}/lib"; fi
if test -z "$PACKAGE_INCLUDEDIR";     then PACKAGE_INCLUDEDIR="${PACKAGE_PREFIX%/}/usr/include"; fi
if test -z "$PACKAGE_OLDINCLUDEDIR";  then PACKAGE_OLDINCLUDEDIR="$PACKAGE_INCLUDEDIR"; fi
if test -z "$PACKAGE_DATAROOTDIR";    then PACKAGE_DATAROOTDIR="${PACKAGE_PREFIX%/}/usr/share"; fi
if test -z "$PACKAGE_DATADIR";        then PACKAGE_DATADIR="$PACKAGE_DATAROOTDIR"; fi
if test -z "$PACKAGE_INFODIR";        then PACKAGE_INFODIR="$PACKAGE_DATAROOTDIR/info"; fi
if test -z "$PACKAGE_LOCALEDIR";      then PACKAGE_LOCALEDIR="$PACKAGE_DATAROOTDIR/locale"; fi
if test -z "$PACKAGE_MANDIR";         then PACKAGE_MANDIR="$PACKAGE_DATAROOTDIR/man"; fi
if test -z "$PACKAGE_DOCDIR";         then PACKAGE_DOCDIR="$PACKAGE_DATAROOTDIR/doc/$PACKAGE_RAWNAME"; fi
if test -z "$PACKAGE_HTMLDIR";        then PACKAGE_HTMLDIR="$PACKAGE_DOCDIR"; fi
if test -z "$PACKAGE_DVIDIR";         then PACKAGE_DVIDIR="$PACKAGE_DOCDIR"; fi
if test -z "$PACKAGE_PDFDIR";         then PACKAGE_PDFDIR="$PACKAGE_DOCDIR"; fi
if test -z "$PACKAGE_PSDIR";          then PACKAGE_PSDIR="$PACKAGE_DOCDIR"; fi
if test -z "$PACKAGE_HOST";           then PACKAGE_HOST="$TARGET_NAME-linux-gnu"; fi
if test -z "$PACKAGE_TARGET";         then PACKAGE_TARGET="$PACKAGE_HOST"; fi


echo "gnu_make: PACKAGE_RAWNAME  '$PACKAGE_RAWNAME'"
echo "gnu_make: PACKAGE_VERSION  '$PACKAGE_VERSION'"
echo "gnu_make: PACKAGE_NAME     '$PACKAGE_NAME'"
echo "gnu_make: PACKAGE_URL      '$PACKAGE_URL'"
#echo "gnu_make: PACKAGE_PREFIX         '$PACKAGE_PREFIX'"
#echo "gnu_make: PACKAGE_EPREFIX        '$PACKAGE_EPREFIX'"
#echo "gnu_make: PACKAGE_BINDIR         '$PACKAGE_BINDIR'"
#echo "gnu_make: PACKAGE_SBINDIR        '$PACKAGE_SBINDIR'"
#echo "gnu_make: PACKAGE_LIBEXECDIR     '$PACKAGE_LIBEXECDIR'"
#echo "gnu_make: PACKAGE_SYSCONFDIR     '$PACKAGE_SYSCONFDIR'"
#echo "gnu_make: PACKAGE_SHAREDSTATEDIR '$PACKAGE_SHAREDSTATEDIR'"
#echo "gnu_make: PACKAGE_LOCALSTATEDIR  '$PACKAGE_LOCALSTATEDIR'"
#echo "gnu_make: PACKAGE_LIBDIR         '$PACKAGE_LIBDIR'"
#echo "gnu_make: PACKAGE_INCLUDEDIR     '$PACKAGE_INCLUDEDIR'"
#echo "gnu_make: PACKAGE_OLDINCLUDEDIR  '$PACKAGE_OLDINCLUDEDIR'"
#echo "gnu_make: PACKAGE_DATAROOTDIR    '$PACKAGE_DATAROOTDIR'"
#echo "gnu_make: PACKAGE_DATADIR        '$PACKAGE_DATADIR'"
#echo "gnu_make: PACKAGE_INFODIR        '$PACKAGE_INFODIR'"
#echo "gnu_make: PACKAGE_LOCALEDIR      '$PACKAGE_LOCALEDIR'"
#echo "gnu_make: PACKAGE_MANDIR         '$PACKAGE_MANDIR'"
#echo "gnu_make: PACKAGE_DOCDIR         '$PACKAGE_DOCDIR'"
#echo "gnu_make: PACKAGE_HTMLDIR        '$PACKAGE_HTMLDIR'"
#echo "gnu_make: PACKAGE_DVIDIR         '$PACKAGE_DVIDIR'"
#echo "gnu_make: PACKAGE_PDFDIR         '$PACKAGE_PDFDIR'"
#echo "gnu_make: PACKAGE_PSDIR          '$PACKAGE_PSDIR'"
#echo "gnu_make: PACKAGE_HOST   '$PACKAGE_HOST'"
#echo "gnu_make: PACKAGE_TARGET '$PACKAGE_TARGET'"

SRCPATH="$KOS_ROOT/binutils/src/$PACKAGE_NAME"
OPTPATH="$BINUTILS_SYSROOT/opt/$PACKAGE_NAME"
DESTDIR="$BINUTILS_SYSROOT/opt/${PACKAGE_NAME}-install"
DESTDIR2="$BINUTILS_SYSROOT/opt/${PACKAGE_NAME}-install-temp"

if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -d "$DESTDIR" ]; then
	rm -r "$DESTDIR" > /dev/null 2>&1
	rm -r "$DESTDIR2" > /dev/null 2>&1
	if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/_didmake" ]; then
		if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ]; then
			if ! [ -f "$SRCPATH/configure" ]; then
				if ! [ -f "$SRCPATH/configure.ac" ]; then
					rm -r "$SRCPATH" > /dev/null 2>&1
					cmd cd "$(dirname "$SRCPATH")"
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
						cmd tar xvf "$_PACKAGE_URL_WANTED_FILENAME"
						if [ "$_PACKAGE_URL_NAME" != "$PACKAGE_NAME" ]; then
							cmd mv "$_PACKAGE_URL_NAME" "$PACKAGE_NAME"
						fi
					else
						# Unrecognized package distribution format
						echo "No known way of extracting files from: '$_PACKAGE_URL_FILENAME'"
						exit 1
					fi
				fi
				if ! [ -f "$SRCPATH/Makefile.in" ]; then
					cmd cd "$SRCPATH"
					cmd automake
				fi
				if ! [ -f "$SRCPATH/configure" ]; then
					cmd cd "$SRCPATH"
					cmd autoconf
				fi
			fi
			if [ -f "$KOS_PATCHES/$PACKAGE_NAME.patch" ]; then
				apply_patch "$SRCPATH" "$KOS_PATCHES/$PACKAGE_NAME.patch"
			fi
			rm -r "$OPTPATH" > /dev/null 2>&1
			cmd mkdir -p "$OPTPATH"
			cmd cd "$OPTPATH"

			# Auto-configure arguments for ./configure
			if ! test -z "$PACKAGE_CONFIGURE"; then
				CONFIGURE="$PACKAGE_CONFIGURE $CONFIGURE"
				if ! test -z "$CONFIGURE"; then
					echo "Using given \$PACKAGE_CONFIGURE and \$CONFIGURE options:"
					for opt in $CONFIGURE; do
						echo "	option: $opt"
					done
				fi
			else
				_CONFHELP="$(bash $SRCPATH/configure --help 2>&1)"
				# Auto-detect supported, but unset options
				if ! [ -f "$SRCPATH/_configure_help" ]; then
					echo "Creating file: '$SRCPATH/_configure_help'"
					cmd bash "$SRCPATH/configure" --help > "$SRCPATH/_configure_help" 2>&1
				fi
				if ! test -z "$CONFIGURE"; then
					echo "Using given \$CONFIGURE options:"
					for opt in $CONFIGURE; do
						echo "	option: $opt"
					done
				fi
				echo "Scanning '$SRCPATH/configure --help' for additional options..."
				while IFS= read -r line; do
					case "$line" in
					*--prefix=*)         if ! [[ "$CONFIGURE" == *--prefix=*         ]]; then echo "	option: --prefix=$PACKAGE_PREFIX";                 CONFIGURE="$CONFIGURE --prefix=$PACKAGE_PREFIX"; fi ;;
					*--eprefix=*)        if ! [[ "$CONFIGURE" == *--eprefix=*        ]]; then echo "	option: --eprefix=$PACKAGE_EPREFIX";               CONFIGURE="$CONFIGURE --eprefix=$PACKAGE_EPREFIX"; fi ;;
					*--exec-prefix=*)    if ! [[ "$CONFIGURE" == *--exec-prefix=*    ]]; then echo "	option: --exec-prefix=$PACKAGE_EPREFIX";           CONFIGURE="$CONFIGURE --exec-prefix=$PACKAGE_EPREFIX"; fi ;;
					*--bindir=*)         if ! [[ "$CONFIGURE" == *--bindir=*         ]]; then echo "	option: --bindir=$PACKAGE_BINDIR";                 CONFIGURE="$CONFIGURE --bindir=$PACKAGE_BINDIR"; fi ;;
					*--sbindir=*)        if ! [[ "$CONFIGURE" == *--sbindir=*        ]]; then echo "	option: --sbindir=$PACKAGE_SBINDIR";               CONFIGURE="$CONFIGURE --sbindir=$PACKAGE_SBINDIR"; fi ;;
					*--libexecdir=*)     if ! [[ "$CONFIGURE" == *--libexecdir=*     ]]; then echo "	option: --libexecdir=$PACKAGE_SBINDIR";            CONFIGURE="$CONFIGURE --libexecdir=$PACKAGE_SBINDIR"; fi ;;
					*--sysconfdir=*)     if ! [[ "$CONFIGURE" == *--sysconfdir=*     ]]; then echo "	option: --sysconfdir=$PACKAGE_SYSCONFDIR";         CONFIGURE="$CONFIGURE --sysconfdir=$PACKAGE_SYSCONFDIR"; fi ;;
					*--sharedstatedir=*) if ! [[ "$CONFIGURE" == *--sharedstatedir=* ]]; then echo "	option: --sharedstatedir=$PACKAGE_SHAREDSTATEDIR"; CONFIGURE="$CONFIGURE --sharedstatedir=$PACKAGE_SHAREDSTATEDIR"; fi ;;
					*--localstatedir=*)  if ! [[ "$CONFIGURE" == *--localstatedir=*  ]]; then echo "	option: --localstatedir=$PACKAGE_LOCALSTATEDIR";   CONFIGURE="$CONFIGURE --localstatedir=$PACKAGE_LOCALSTATEDIR"; fi ;;
					*--libdir=*)         if ! [[ "$CONFIGURE" == *--libdir=*         ]]; then echo "	option: --libdir=$PACKAGE_LIBDIR";                 CONFIGURE="$CONFIGURE --libdir=$PACKAGE_LIBDIR"; fi ;;
					*--includedir=*)     if ! [[ "$CONFIGURE" == *--includedir=*     ]]; then echo "	option: --includedir=$PACKAGE_INCLUDEDIR";         CONFIGURE="$CONFIGURE --includedir=$PACKAGE_INCLUDEDIR"; fi ;;
					*--oldincludedir=*)  if ! [[ "$CONFIGURE" == *--oldincludedir=*  ]]; then echo "	option: --oldincludedir=$PACKAGE_OLDINCLUDEDIR";   CONFIGURE="$CONFIGURE --oldincludedir=$PACKAGE_OLDINCLUDEDIR"; fi ;;
					*--datarootdir=*)    if ! [[ "$CONFIGURE" == *--datarootdir=*    ]]; then echo "	option: --datarootdir=$PACKAGE_DATAROOTDIR";       CONFIGURE="$CONFIGURE --datarootdir=$PACKAGE_DATAROOTDIR"; fi ;;
					*--datadir=*)        if ! [[ "$CONFIGURE" == *--datadir=*        ]]; then echo "	option: --datadir=$PACKAGE_DATADIR";               CONFIGURE="$CONFIGURE --datadir=$PACKAGE_DATADIR"; fi ;;
					*--infodir=*)        if ! [[ "$CONFIGURE" == *--infodir=*        ]]; then echo "	option: --infodir=$PACKAGE_INFODIR";               CONFIGURE="$CONFIGURE --infodir=$PACKAGE_INFODIR"; fi ;;
					*--localedir=*)      if ! [[ "$CONFIGURE" == *--localedir=*      ]]; then echo "	option: --localedir=$PACKAGE_LOCALEDIR";           CONFIGURE="$CONFIGURE --localedir=$PACKAGE_LOCALEDIR"; fi ;;
					*--mandir=*)         if ! [[ "$CONFIGURE" == *--mandir=*         ]]; then echo "	option: --mandir=$PACKAGE_MANDIR";                 CONFIGURE="$CONFIGURE --mandir=$PACKAGE_MANDIR"; fi ;;
					*--docdir=*)         if ! [[ "$CONFIGURE" == *--docdir=*         ]]; then echo "	option: --docdir=$PACKAGE_DOCDIR";                 CONFIGURE="$CONFIGURE --docdir=$PACKAGE_DOCDIR"; fi ;;
					*--htmldir=*)        if ! [[ "$CONFIGURE" == *--htmldir=*        ]]; then echo "	option: --htmldir=$PACKAGE_HTMLDIR";               CONFIGURE="$CONFIGURE --htmldir=$PACKAGE_HTMLDIR"; fi ;;
					*--dvidir=*)         if ! [[ "$CONFIGURE" == *--dvidir=*         ]]; then echo "	option: --dvidir=$PACKAGE_DVIDIR";                 CONFIGURE="$CONFIGURE --dvidir=$PACKAGE_DVIDIR"; fi ;;
					*--pdfdir=*)         if ! [[ "$CONFIGURE" == *--pdfdir=*         ]]; then echo "	option: --pdfdir=$PACKAGE_PDFDIR";                 CONFIGURE="$CONFIGURE --pdfdir=$PACKAGE_PDFDIR"; fi ;;
					*--psdir=*)          if ! [[ "$CONFIGURE" == *--psdir=*          ]]; then echo "	option: --psdir=$PACKAGE_PSDIR";                   CONFIGURE="$CONFIGURE --psdir=$PACKAGE_PSDIR"; fi ;;
					*--host=*)           if ! [[ "$CONFIGURE" == *--host=*           ]]; then echo "	option: --host=$PACKAGE_HOST";                     CONFIGURE="$CONFIGURE --host=$PACKAGE_HOST"; fi ;;
					*--target=*)         if ! [[ "$CONFIGURE" == *--target=*         ]]; then echo "	option: --target=$PACKAGE_TARGET";                 CONFIGURE="$CONFIGURE --target=$PACKAGE_TARGET"; fi ;;

					# Misc options
					*--with-libiconv-prefix* | *--without-libiconv-prefix*)
						if ! [[ "$CONFIGURE" == *--with-libiconv-prefix* ]] && \
						   ! [[ "$CONFIGURE" == *--without-libiconv-prefix* ]]; then
							echo "	option: --without-libiconv-prefix"
							CONFIGURE="$CONFIGURE --without-libiconv-prefix";
						fi
						;;

					*--with-libintl-prefix* | *--without-libintl-prefix*)
						if ! [[ "$CONFIGURE" == *--with-libintl-prefix* ]] && \
						   ! [[ "$CONFIGURE" == *--without-libintl-prefix* ]]; then
							echo "	option: --without-libintl-prefix"
							CONFIGURE="$CONFIGURE --without-libintl-prefix";
						fi
						;;

					*--with-gnu-ld* | *--without-gnu-ld*)
						if ! [[ "$CONFIGURE" == *--with-gnu-ld* ]] && \
						   ! [[ "$CONFIGURE" == *--without-gnu-ld* ]]; then
							if test -z "$PACKAGE_WITHOUT_GNU_LD"; then
								echo "	option: --with-gnu-ld"
								CONFIGURE="$CONFIGURE --with-gnu-ld";
							else
								echo "	option: --without-gnu-ld"
								CONFIGURE="$CONFIGURE --without-gnu-ld";
							fi
						fi
						;;

					*--enable-rpath* | *--disable-rpath*)
						if ! [[ "$CONFIGURE" == *--enable-rpath* ]] && \
						   ! [[ "$CONFIGURE" == *--disable-rpath* ]]; then
							echo "	option: --disable-rpath"
							CONFIGURE="$CONFIGURE --disable-rpath";
						fi
						;;

					*) ;;
					esac
				done < "$SRCPATH/_configure_help"
			fi
			(
				export CC="${CROSS_PREFIX}gcc"
				export CPP="${CROSS_PREFIX}cpp"
				export CXX="${CROSS_PREFIX}g++"
				export CFLAGS="-ggdb"
				export CXXFLAGS="-ggdb"
				cmd bash ../../../src/$PACKAGE_NAME/configure $CONFIGURE
			) || exit $?
		fi # if [ "$MODE_FORCE_CONF" == yes ] || ! [ -f "$OPTPATH/Makefile" ];
		cmd cd "$OPTPATH"
		cmd make -j $MAKE_PARALLEL_COUNT
		> "$OPTPATH/_didmake"
	fi     # if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -f "$OPTPATH/_didmake" ]
	cmd cd "$OPTPATH"
	cmd make -j $MAKE_PARALLEL_COUNT DESTDIR="$DESTDIR2" install
	cmd mv "$DESTDIR2" "$DESTDIR"
fi         # if [ "$MODE_FORCE_MAKE" == yes ] || ! [ -d "$DESTDIR" ]


# Go over all all of the files that got installed, and select
# which of them we want to put on the KOS disk image(s).
cmd cd "$DESTDIR"
while IFS= read -r line; do
	line="${line#.}"
	if ! test -z "$line"; then
		case "$line" in

		# Ignored files (Don't install documentation on disk images (for now))
		$PACKAGE_INFODIR/* | \
		$PACKAGE_MANDIR/* | $PACKAGE_DOCDIR/* | $PACKAGE_HTMLDIR/* | \
		$PACKAGE_DVIDIR/* | $PACKAGE_PDFDIR/* | $PACKAGE_PSDIR/*)
			;;

		*)
			# Fallback: Install the file normally
			install_file $line "${DESTDIR}$line"
		esac
	fi
done < <(find . -type f 2>&1)
