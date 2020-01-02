/* HASH CRC-32:0xdb088ab4 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_memxlen_defined
#define __local_memxlen_defined 1
/* Dependency: "memxend" from "string" */
#ifndef ____localdep_memxend_defined
#define ____localdep_memxend_defined 1
#ifdef __CRT_HAVE_memxend
/* Same as `memend', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memxend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memxend,(__haystack,__needle,__n_bytes))
#else /* LIBC: memxend */
#include <local/string/memxend.h>
/* Same as `memend', but search for non-matching locations. */
#define __localdep_memxend (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memxend))
#endif /* memxend... */
#endif /* !____localdep_memxend_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `memlen', but search for non-matching locations. */
__LOCAL_LIBC(memxlen) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memxlen))(void const *__restrict __haystack,
                                                     int __needle,
                                                     __SIZE_TYPE__ __n_bytes) {
#line 1952 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)((__BYTE_TYPE__ *)__localdep_memxend(__haystack, __needle, __n_bytes) - (__BYTE_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_memxlen_defined */
