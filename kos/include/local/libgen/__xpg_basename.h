/* HASH CRC-32:0x705349e8 */
/* Copyright (c) 2019 Griefer@Work                                            *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local___xpg_basename_defined
#define __local___xpg_basename_defined 1
/* Dependency: "strrchr" from "string" */
#ifndef ____localdep_strrchr_defined
#define ____localdep_strrchr_defined 1
#if __has_builtin(__builtin_strrchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strrchr)
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL __localdep_strrchr)(char const *__restrict __haystack, int __needle) { return __builtin_strrchr(__haystack, __needle); }
#elif defined(__CRT_HAVE_strrchr)
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strrchr,(char const *__restrict __haystack, int __needle),strrchr,(__haystack,__needle))
#else /* LIBC: strrchr */
#include <local/string/strrchr.h>
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
#define __localdep_strrchr (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strrchr))
#endif /* strrchr... */
#endif /* !____localdep_strrchr_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return final component of PATH.
 * This is the weird XPG version of this function. It sometimes will
 * modify its argument. Therefore we normally use the GNU version (in
 * <string.h>) and only if this header is included make the XPG
 * version available under the real name */
__LOCAL_LIBC(__xpg_basename) __ATTR_RETNONNULL char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__xpg_basename))(char *__filename) {
#line 91 "kos/src/libc/magic/libgen.c"
	/* NOTE: This implementation is taken from GLibc */
	/* Return basename of given pathname according to the weird XPG specification.
	   Copyright (C) 1997-2017 Free Software Foundation, Inc.
	   This file is part of the GNU C Library.
	   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1997.
	
	   The GNU C Library is free software; you can redistribute it and/or
	   modify it under the terms of the GNU Lesser General Public
	   License as published by the Free Software Foundation; either
	   version 2.1 of the License, or (at your option) any later version.
	
	   The GNU C Library is distributed in the hope that it will be useful,
	   but WITHOUT ANY WARRANTY; without even the implied warranty of
	   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	   Lesser General Public License for more details.
	
	   You should have received a copy of the GNU Lesser General Public
	   License along with the GNU C Library; if not, see
	   <http://www.gnu.org/licenses/>.  */
	char *__result;
	if (!__filename || !__filename[0])
		__result = (char *)".";
	else {
		__result = __localdep_strrchr(__filename, '/');
		if (!__result)
			__result = __filename;
		else if (!__result[1]) {
			while (__result > __filename && __result[-1] == '/')
				--__result;
			if (__result > __filename) {
				*__result-- = '\0';
				while (__result > __filename && __result[-1] != '/')
					--__result;
			} else {
				while (__result[1] != '\0')
					++__result;
			}
		} else {
			++__result;
		}
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__local___xpg_basename_defined */
