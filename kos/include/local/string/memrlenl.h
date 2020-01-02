/* HASH CRC-32:0x249465df */
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
#ifndef __local_memrlenl_defined
#define __local_memrlenl_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "memrendl" from "string" */
#ifndef ____localdep_memrendl_defined
#define ____localdep_memrendl_defined 1
#ifdef __fast_memrendl_defined
/* Same as `memrchrl', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_memrendl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendl))
#elif defined(__CRT_HAVE_memrendl)
/* Same as `memrchrl', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memrendl,(/*aligned(4)*/ void const *__restrict __haystack, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),memrendl,(__haystack,__dword,__n_dwords))
#else /* LIBC: memrendl */
#include <local/string/memrendl.h>
/* Same as `memrchrl', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_memrendl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendl))
#endif /* memrendl... */
#endif /* !____localdep_memrendl_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `memrendl', but return the offset from `HAYSTACK', rather than the actual address. */
__LOCAL_LIBC(memrlenl) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memrlenl))(/*aligned(4)*/ void const *__restrict __haystack,
                                                      __UINT32_TYPE__ __dword,
                                                      __SIZE_TYPE__ __n_dwords) {
#line 1528 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_memrendl(__haystack, __dword, __n_dwords) - (__UINT32_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_memrlenl_defined */
