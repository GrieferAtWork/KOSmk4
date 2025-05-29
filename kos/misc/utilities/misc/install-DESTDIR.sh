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

# Helpers to automatically install files from $DESTDIR to disk
# Variables:
#   $INSTALL_NONE:      If non-empty, don't install anything
#   $DESTDIR:           Sysroot of files that should be installed
#   $INSTALL_SKIP:      NL-separated list of files to never install
#   $PACKAGE_*:         Generic package information variables



# Defaults for package paths
if test -z "$PACKAGE_PREFIX";         then PACKAGE_PREFIX="/"; fi
if test -z "$PACKAGE_EPREFIX";        then PACKAGE_EPREFIX="$PACKAGE_PREFIX"; fi
if test -z "$PACKAGE_LIBDIR";         then PACKAGE_LIBDIR="${PACKAGE_EPREFIX%/}/$TARGET_LIBPATH"; fi
if test -z "$PACKAGE_INCLUDEDIR";     then PACKAGE_INCLUDEDIR="${PACKAGE_PREFIX%/}/usr/include"; fi
if test -z "$PACKAGE_OLDINCLUDEDIR";  then PACKAGE_OLDINCLUDEDIR="$PACKAGE_INCLUDEDIR"; fi
if test -z "$PACKAGE_INFODIR";        then PACKAGE_INFODIR="$PACKAGE_DATAROOTDIR/info"; fi
if test -z "$PACKAGE_MANDIR";         then PACKAGE_MANDIR="$PACKAGE_DATAROOTDIR/man"; fi
if test -z "$PACKAGE_DOCDIR";         then PACKAGE_DOCDIR="$PACKAGE_DATAROOTDIR/doc/$PACKAGE_RAWNAME"; fi
if test -z "$PACKAGE_HTMLDIR";        then PACKAGE_HTMLDIR="$PACKAGE_DOCDIR"; fi
if test -z "$PACKAGE_DVIDIR";         then PACKAGE_DVIDIR="$PACKAGE_DOCDIR"; fi
if test -z "$PACKAGE_PDFDIR";         then PACKAGE_PDFDIR="$PACKAGE_DOCDIR"; fi
if test -z "$PACKAGE_PSDIR";          then PACKAGE_PSDIR="$PACKAGE_DOCDIR"; fi

if test -z "$INSTALL_NONE"; then
	${HOOK_BEFORE_INSTALL_DISK:-:}

	# Go over all of the files that got installed, and select
	# which of them we want to put on the KOS disk image(s).
	cmd cd "$DESTDIR"
	while IFS= read -r line; do
		line="${line#.}"
		if ! test -z "$line"; then
			if ! test -z "$INSTALL_SKIP"; then
				if [[ "$INSTALL_SKIP" == *"
$line
"* ]]; then
					continue
				fi
				scan="${line%/*}"
				should_skip=""
				while ! test -z "$scan"; do
					if [[ "$INSTALL_SKIP" == *"
$scan
"* ]]; then should_skip=yes; break; fi
					scan="${scan%/*}"
				done
				if ! test -z "$should_skip"; then
					continue
				fi
			fi
			src_filename="${DESTDIR}$line"
			case "$line" in

			# Ignored files (Don't install documentation on disk images (for now))
			$PACKAGE_INFODIR/* | \
			$PACKAGE_MANDIR/* | $PACKAGE_DOCDIR/* | $PACKAGE_HTMLDIR/* | \
			$PACKAGE_DVIDIR/* | $PACKAGE_PDFDIR/* | $PACKAGE_PSDIR/*)
				;;

			$PACKAGE_LIBDIR/*.la)
				# Skip libtool instruction files
				;;

			$PACKAGE_LIBDIR/*.a)
				# Don't install static libraries on-disk. - Only install them in the lib-path
				install_file_nodisk "$line" "$src_filename"
				;;

			*.so.*)
				# NOTE: All of the following is a work-around to get shared library symlinks
				#       working properly, as KOS's disk images currently don't support symbolic
				#       links due to the fact that they're using FAT
				dst_path="${line%/*}"
				src_name="${line##*/}"
				raw_name="${src_name%.so.*}.so"
				# Versioned shared libraries are kind-of special:
				#    lrwxrwxrwx [...] libuuid.so -> libuuid.so.1.0.0
				#    lrwxrwxrwx [...] libuuid.so.1 -> libuuid.so.1.0.0
				#    -rwxr-xr-x [...] libuuid.so.1.0.0
				# Since we're only enumerating regular files, we'll only get here once for "libuuid.so.1.0.0".
				# To install this file correctly, we must do the following:
				# $ install_file           /$TARGET_LIBPATH/libuuid.so.1      libuuid.so.1.0.0
				# $ install_symlink_nodisk /$TARGET_LIBPATH/libuuid.so.1.0.0  libuuid.so.1
				# $ install_symlink_nodisk /$TARGET_LIBPATH/libuuid.so        libuuid.so.1
				so_name=""
				while IFS= read -r readelf_line; do
					if [[ "$readelf_line" == *"Library soname: ["* ]]; then
						readelf_line="${readelf_line##*Library soname: [}"
						if [[ "$readelf_line" == *"]"* ]]; then
							so_name="${readelf_line%]*}"
						fi
					fi
				done < <(readelf -d -W "$src_filename")
				if test -z "$so_name"; then so_name="$src_name"; fi
				if [ -L "${DESTDIR}$dst_path/$so_name" ]; then
					# Install the shared library under its SO_NAME
					install_file "$dst_path/$so_name" "$src_filename"
					if [[ "$so_name" != "$src_name" ]]; then
						install_symlink_nodisk "$line" "$so_name";
					fi
				else
					# Install the shared library under its original name
					install_file "$line" "$src_filename"
				fi
				if [[ "$so_name" != "$raw_name" ]] && [ -L "${DESTDIR}$dst_path/$raw_name" ]; then
					# install_symlink_nodisk /$TARGET_LIBPATH/libuuid.so libuuid.so.1
					install_symlink_nodisk "$dst_path/$raw_name" "$so_name"
				fi
				;;

			$PACKAGE_INCLUDEDIR/* | $PACKAGE_OLDINCLUDEDIR/* | /include/*)
				if [[ "$line" == "$PACKAGE_INCLUDEDIR/"* ]]; then
					rel_filename="${line:${#PACKAGE_INCLUDEDIR}}"
				elif [[ "$line" == "$PACKAGE_OLDINCLUDEDIR/"* ]]; then
					rel_filename="${line:${#PACKAGE_OLDINCLUDEDIR}}"
				else
					rel_filename="${line:8}"
				fi
				# Install a 3rd party header file
				install_rawfile "$KOS_ROOT/kos/include$rel_filename" "$src_filename"
				;;


			*/aclocal/*.m4)
				m4_filename="${line##*/}"
				dst_filename="$SYSROOT_BINUTILS_TARGET/usr/local/share/aclocal/$m4_filename"
				if test x"$MODE_DRYRUN" != xno; then
					echo "> aclocal_m4_config '$src_filename'" >&2
				else
					short_dst_filename="$dst_filename"
					if [[ "$short_dst_filename" == "$KOS_ROOT/"* ]]; then
						short_dst_filename="\$KOS_ROOT${short_dst_filename:${#KOS_ROOT}}"
					fi
					printf "\e[${UI_COLCFG_FILETYPE}mm4 \e[m \e[${UI_COLCFG_PATH_RAW}m%-${UI_PATHCOL_WIDTH}s\e[m [raw]" "$short_dst_filename" >&2
					if ! [ -f "$dst_filename" ] || [ "$src_filename" -nt "$dst_filename" ]; then
						unlink "$dst_filename" > /dev/null 2>&1
						cmd mkdir -p "$SYSROOT_BINUTILS_TARGET/usr/local/share/aclocal"
						cmd cp "$src_filename" "$dst_filename"
						echo -e "\e[${UI_COLCFG_OK}m ok\e[m" >&2
					else
						echo -e "\e[${UI_COLCFG_OK}m already installed\e[m" >&2
					fi
				fi
				;;

			*/pkgconfig/*.pc | */pkg_config/*.pc)
				pc_filename="${line##*/}"
				dst_filename="$PKG_CONFIG_PATH/$pc_filename"
				if test x"$MODE_DRYRUN" != xno; then
					echo "> pkg_config '$src_filename'"
				else
					short_dst_filename="$dst_filename"
					if [[ "$short_dst_filename" == "$KOS_ROOT/"* ]]; then
						short_dst_filename="\$KOS_ROOT${short_dst_filename:${#KOS_ROOT}}"
					fi
					printf "\e[${UI_COLCFG_FILETYPE}mpkg\e[m \e[${UI_COLCFG_PATH_RAW}m%-${UI_PATHCOL_WIDTH}s\e[m [raw]" "$short_dst_filename" >&2
					if ! [ -f "$dst_filename" ] || [ "$src_filename" -nt "$dst_filename" ]; then
						unlink "$dst_filename" > /dev/null 2>&1
						while IFS= read -r pc_line; do
							case "$pc_line" in

							prefix=*)              pc_line="prefix=$PACKAGE_PREFIX" ;;
							exec_prefix=*)         pc_line="exec_prefix=$PACKAGE_EPREFIX" ;;
							libdir=*)              pc_line="libdir=$KOS_ROOT/bin/$TARGET_NAME-kos$PACKAGE_LIBDIR" ;;
							includedir=*)          pc_line="includedir=$KOS_ROOT/kos/include" ;;

							# These are needed for Xorg
							sdkdir=/include)       pc_line="sdkdir=$KOS_ROOT/kos/include" ;;
							sdkdir=/include/*)     pc_line="sdkdir=$KOS_ROOT/kos/include/${pc_line:16}" ;;
							sdkdir=/usr/include)   pc_line="sdkdir=$KOS_ROOT/kos/include" ;;
							sdkdir=/usr/include/*) pc_line="sdkdir=$KOS_ROOT/kos/include/${pc_line:20}" ;;

							Cflags:*)
								pc_line="${pc_line:7}"
								new_pc_line=""
								for arg in $pc_line; do
									case "$arg" in
									-I\${includedir})
										arg=""
										;;
									-I\${includedir}/*)
										arg="-I$KOS_ROOT/kos/include/${arg:16}"
										;;
									"-I${KOS_ROOT}/*")
										# This is allowed
										;;
									-I/*)
										# Don't point at build system paths
										arg=""
										;;
									*)
										;;
									esac
									if ! test -z "$arg"; then
										new_pc_line="$new_pc_line $arg"
									fi
								done
								pc_line="Cflags:$new_pc_line"
								;;

							Libs:*)
								pc_line="${pc_line:5}"
								new_pc_line=""
								for arg in $pc_line; do
									case "$arg" in
									-L\${libdir})
										arg=""
										;;
									"-L${KOS_ROOT}/*")
										# This is allowed
										;;
									-L/*)
										# Don't point at build system paths (I'm looking at you, *ncurses*...)
										arg=""
										;;
									*)
										;;
									esac
									if ! test -z "$arg"; then
										new_pc_line="$new_pc_line $arg"
									fi
								done
								pc_line="Libs:$new_pc_line"
								;;

							*)
								;;
							esac
							echo "$pc_line" >> "$dst_filename"
						done < "$src_filename"
						echo -e "\e[${UI_COLCFG_OK}m ok\e[m" >&2
					else
						echo -e "\e[${UI_COLCFG_OK}m already installed\e[m" >&2
					fi
				fi
				;;

			*)
				# Fallback: Install the file normally
				install_file "$line" "$src_filename"
				;;
			esac
		fi
	done < <(find . -type f 2>&1)
fi
