/* HASH CRC-32:0xbeabb0f7 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_argz_count_defined
#define __local_argz_count_defined 1
#include <__crt.h>
/* Dependency: "strlen" from "string" */
#ifndef ____localdep_strlen_defined
#define ____localdep_strlen_defined 1
#ifdef __CRT_HAVE_strlen
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __string),strlen,(__string))
#else /* LIBC: strlen */
#include <local/string/strlen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_strlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlen))
#endif /* strlen... */
#endif /* !____localdep_strlen_defined */

__NAMESPACE_LOCAL_BEGIN
/* Returns the number of strings in `ARGZ'
 * Simply count the number of`NUL-characters within `argz...+=argz_len' */
__LOCAL_LIBC(argz_count) __ATTR_PURE __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(argz_count))(char const *__argz,
                                                        __SIZE_TYPE__ __argz_len) {
#line 182 "kos/src/libc/magic/argz.c"
	__SIZE_TYPE__ __result = 0;
	if __likely(__argz_len) {
		for (;;) {
			__SIZE_TYPE__ __temp;
			++__result;
			__temp = __localdep_strlen(__argz) + 1;
			if (__temp >= __argz_len)
				break;
			__argz_len -= __temp;
			__argz     += __temp;
		}
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_argz_count_defined */
