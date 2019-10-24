/* HASH CRC-32:0xc63fc5d */
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
#ifndef __local_memrlen_defined
#define __local_memrlen_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "memrend" from "string" */
#ifndef ____localdep_memrend_defined
#define ____localdep_memrend_defined 1
#if defined(__fast_memrend_defined)
/* Same as `memrchr', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_memrend (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrend))
#elif defined(__CRT_HAVE_memrend)
/* Same as `memrchr', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memrend,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrend,(__haystack,__needle,__n_bytes))
#else /* LIBC: memrend */
#include <local/string/memrend.h>
/* Same as `memrchr', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_memrend (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrend))
#endif /* memrend... */
#endif /* !____localdep_memrend_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `memrend', but return the offset from `HAYSTACK', rather than the actual address. */
__LOCAL_LIBC(memrlen) __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memrlen))(void const *__restrict __haystack,
                                                     int __needle,
                                                     __SIZE_TYPE__ __n_bytes) {
#line 2276 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)((__BYTE_TYPE__ *)__localdep_memrend(__haystack, __needle, __n_bytes) - (__BYTE_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_memrlen_defined */
