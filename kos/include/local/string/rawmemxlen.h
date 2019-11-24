/* HASH CRC-32:0xdd5f191b */
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
#ifndef __local_rawmemxlen_defined
#define __local_rawmemxlen_defined 1
/* Dependency: "rawmemxchr" from "string" */
#ifndef ____localdep_rawmemxchr_defined
#define ____localdep_rawmemxchr_defined 1
#ifdef __CRT_HAVE_rawmemxchr
/* Same as `rawmemchr', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_rawmemxchr,(void const *__restrict __haystack, int __needle),rawmemxchr,(__haystack,__needle))
#else /* LIBC: rawmemxchr */
#include <local/string/rawmemxchr.h>
/* Same as `rawmemchr', but search for non-matching locations. */
#define __localdep_rawmemxchr (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchr))
#endif /* rawmemxchr... */
#endif /* !____localdep_rawmemxchr_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `rawmemlen', but search for non-matching locations. */
__LOCAL_LIBC(rawmemxlen) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(rawmemxlen))(void const *__restrict __haystack,
                                                        int __needle) {
#line 1964 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)((__BYTE_TYPE__ *)__localdep_rawmemxchr(__haystack, __needle) - (__BYTE_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_rawmemxlen_defined */
