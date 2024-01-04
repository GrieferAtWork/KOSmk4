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

if test -z "$_INSTALL_SH_SETUP_DONE"; then
	if test -z "$DESTDIR"; then
		echo "ERROR: No \$DESTDIR given" >&2
		exit 1
	fi
	mkdir -p "$DESTDIR"

	# Check if we're installing to a FAT filesystem
	if LANG=en df -T "$DESTDIR" | grep -i 'fat' > /dev/null; then
		ln() {
			echo -n -e "!<symlink>$2\0" > "$3" || return $?
			fatattr +s "$3" || return $?
		}
	fi
	_INSTALL_SH_SETUP_DONE=yes

	set -e # Abort if a command fails
	set -x # Print commands as they're executed
fi
