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


OPTS=""
if [ "$MODE_FORCE_CONF" == yes ]; then OPTS="$OPTS --force-configure"; fi
if [ "$MODE_FORCE_MAKE" == yes ]; then OPTS="$OPTS --force-make"; fi
if [ "$MODE_FORCE_DISK" == yes ]; then OPTS="$OPTS --force-disk"; fi

#>> makepart <UTILITY_NAME>
makepart() {
	echo "MakePart: bash $KOS_MISC/make_utility.sh $OPTS $TARGET_NAME $1"
	cmd bash "$KOS_MISC/make_utility.sh" $OPTS "$TARGET_NAME" $1
}

BLACKLIST=" all "

# Build libraries first!
for name in ncurses zlib libffi; do
	BLACKLIST="$BLACKLIST $name "
	makepart $name
done

# Build all of the remaining utilities
cd "$(dirname $(readlink -f "$0"))/utilities"
for name in *.sh; do
	name="${name::-3}"
	if ! [[ "$BLACKLIST" == *" $name "* ]]; then
		makepart $name
	fi
done
