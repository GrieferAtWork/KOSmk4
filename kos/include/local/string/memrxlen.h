/* HASH CRC-32:0x67a016f9 */
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
#ifndef __local_memrxlen_defined
#define __local_memrxlen_defined 1
/* Dependency: "memrxend" from "string" */
#ifndef ____localdep_memrxend_defined
#define ____localdep_memrxend_defined 1
#ifdef __CRT_HAVE_memrxend
/* Same as `memrend', but search for non-matching locations. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memrxend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrxend,(__haystack,__needle,__n_bytes))
#else /* LIBC: memrxend */
#include <local/string/memrxend.h>
/* Same as `memrend', but search for non-matching locations. */
#define __localdep_memrxend (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrxend))
#endif /* memrxend... */
#endif /* !____localdep_memrxend_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `memrlen', but search for non-matching locations. */
__LOCAL_LIBC(memrxlen) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memrxlen))(void const *__restrict __haystack,
                                                      int __needle,
                                                      __SIZE_TYPE__ __n_bytes) {
#line 1727 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)((__BYTE_TYPE__ *)__localdep_memrxend(__haystack, __needle, __n_bytes) - (__BYTE_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_memrxlen_defined */
