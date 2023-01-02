# Copyright (c) 2019-2023 Griefer@Work
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
#    Portions Copyright (c) 2019-2023 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

if test -z "$TARGET_CONFIG_SIZEOF_POINTER"; then

case "$TARGET_CPUNAME" in

i*86)
	TARGET_CPUFAMILY="x86"
	TARGET_CONFIG_ALIGNOF_INT64="4"
	TARGET_CONFIG_ALIGNOF_DOUBLE="4"
	TARGET_CONFIG_ALIGNOF_LDOUBLE="4"
	TARGET_CONFIG_SIZEOF_LDOUBLE="12"
	TARGET_CONFIG_ILP32=1
	;;

x86_64)
	TARGET_CONFIG_LP64=1
	;;

arm)
	TARGET_CONFIG_ILP32=1
	;;


*)	echo "Unknown CPU name: '$TARGET_CPUNAME'"
	exit 1
	;;
esac


if test -z "$TARGET_CPUFAMILY"; then TARGET_CPUFAMILY="$TARGET_CPUNAME"; fi
if test -z "$TARGET_ENDIAN"; then TARGET_ENDIAN="little"; fi # Or "big", or "pdp"
if test -z "$TARGET_CONFIG_SIZEOF_POINTER"; then
	if ! test -z "$TARGET_CONFIG_LP64"; then
		TARGET_CONFIG_SIZEOF_POINTER="8"
	else
		TARGET_CONFIG_SIZEOF_POINTER="4"
	fi
fi
if test -z "$TARGET_CONFIG_SIZEOF_LLONG"; then TARGET_CONFIG_SIZEOF_LLONG="8"; fi
if test -z "$TARGET_CONFIG_SIZEOF_LONG"; then TARGET_CONFIG_SIZEOF_LONG="$TARGET_CONFIG_SIZEOF_POINTER"; fi
if test -z "$TARGET_CONFIG_SIZEOF_INT"; then TARGET_CONFIG_SIZEOF_INT="4"; fi
if test -z "$TARGET_CONFIG_SIZEOF_SHORT"; then TARGET_CONFIG_SIZEOF_SHORT="2"; fi
if test -z "$TARGET_CONFIG_SIZEOF_CHAR"; then TARGET_CONFIG_SIZEOF_CHAR="1"; fi
if test -z "$TARGET_CONFIG_SIZEOF_WCHAR_T"; then TARGET_CONFIG_SIZEOF_WCHAR_T="4"; fi
if test -z "$TARGET_CONFIG_SIZEOF_FLOAT"; then TARGET_CONFIG_SIZEOF_FLOAT="4"; fi
if test -z "$TARGET_CONFIG_SIZEOF_DOUBLE"; then TARGET_CONFIG_SIZEOF_DOUBLE="8"; fi
if test -z "$TARGET_CONFIG_SIZEOF_LDOUBLE"; then TARGET_CONFIG_SIZEOF_LDOUBLE="16"; fi
if test -z "$TARGET_CONFIG_ALIGNOF_FLOAT"; then TARGET_CONFIG_ALIGNOF_FLOAT="$TARGET_CONFIG_SIZEOF_FLOAT"; fi
if test -z "$TARGET_CONFIG_ALIGNOF_DOUBLE"; then TARGET_CONFIG_ALIGNOF_DOUBLE="$TARGET_CONFIG_SIZEOF_DOUBLE"; fi
if test -z "$TARGET_CONFIG_ALIGNOF_LDOUBLE"; then TARGET_CONFIG_ALIGNOF_LDOUBLE="$TARGET_CONFIG_SIZEOF_LDOUBLE"; fi
if test -z "$TARGET_CONFIG_ALIGNOF_INT8"; then TARGET_CONFIG_ALIGNOF_INT8="1"; fi
if test -z "$TARGET_CONFIG_ALIGNOF_INT16"; then TARGET_CONFIG_ALIGNOF_INT16="2"; fi
if test -z "$TARGET_CONFIG_ALIGNOF_INT32"; then TARGET_CONFIG_ALIGNOF_INT32="4"; fi
if test -z "$TARGET_CONFIG_ALIGNOF_INT64"; then TARGET_CONFIG_ALIGNOF_INT64="8"; fi
_TARGET_CONFIG_ALIGNOF_INT() {
	if [[ "$1" == "1" ]]; then
		echo "$TARGET_CONFIG_ALIGNOF_INT8"
	elif [[ "$1" == "2" ]]; then
		echo "$TARGET_CONFIG_ALIGNOF_INT16"
	elif [[ "$1" == "4" ]]; then
		echo "$TARGET_CONFIG_ALIGNOF_INT32"
	elif [[ "$1" == "8" ]]; then
		echo "$TARGET_CONFIG_ALIGNOF_INT64"
	else
		echo "_TARGET_CONFIG_ALIGNOF_INT: Invalid argument '$1'" > /dev/stderr
		exit 1
	fi
}

if test -z "$TARGET_CONFIG_ALIGNOF_POINTER"; then TARGET_CONFIG_ALIGNOF_POINTER="$(_TARGET_CONFIG_ALIGNOF_INT "$TARGET_CONFIG_SIZEOF_POINTER")"; fi
if test -z "$TARGET_CONFIG_ALIGNOF_LLONG"; then TARGET_CONFIG_ALIGNOF_LLONG="$(_TARGET_CONFIG_ALIGNOF_INT "$TARGET_CONFIG_SIZEOF_LLONG")"; fi
if test -z "$TARGET_CONFIG_ALIGNOF_LONG"; then TARGET_CONFIG_ALIGNOF_LONG="$(_TARGET_CONFIG_ALIGNOF_INT "$TARGET_CONFIG_SIZEOF_LONG")"; fi
if test -z "$TARGET_CONFIG_ALIGNOF_INT"; then TARGET_CONFIG_ALIGNOF_INT="$(_TARGET_CONFIG_ALIGNOF_INT "$TARGET_CONFIG_SIZEOF_INT")"; fi
if test -z "$TARGET_CONFIG_ALIGNOF_SHORT"; then TARGET_CONFIG_ALIGNOF_SHORT="$(_TARGET_CONFIG_ALIGNOF_INT "$TARGET_CONFIG_SIZEOF_SHORT")"; fi
if test -z "$TARGET_CONFIG_ALIGNOF_CHAR"; then TARGET_CONFIG_ALIGNOF_CHAR="$(_TARGET_CONFIG_ALIGNOF_INT "$TARGET_CONFIG_SIZEOF_CHAR")"; fi
if test -z "$TARGET_CONFIG_ALIGNOF_WCHAR_T"; then TARGET_CONFIG_ALIGNOF_WCHAR_T="$(_TARGET_CONFIG_ALIGNOF_INT "$TARGET_CONFIG_SIZEOF_WCHAR_T")"; fi
if test -z "$TARGET_CONFIG_ALIGNOF_MAXALIGN_T"; then TARGET_CONFIG_ALIGNOF_MAXALIGN_T="$TARGET_CONFIG_ALIGNOF_LDOUBLE"; fi
if test -z "$TARGET_CONFIG_STACK_DIRECTION"; then TARGET_CONFIG_STACK_DIRECTION="-1"; fi # Grows downwards

fi
