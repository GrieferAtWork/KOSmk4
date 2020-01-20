/* HASH CRC-32:0xd0823740 */
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
#ifndef __local_memrlenw_defined
#define __local_memrlenw_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "memrendw" from "string" */
#ifndef ____localdep_memrendw_defined
#define ____localdep_memrendw_defined 1
#ifdef __fast_memrendw_defined
/* Same as `memrchrw', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_memrendw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memrendw))
#elif defined(__CRT_HAVE_memrendw)
/* Same as `memrchrw', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memrendw,(/*aligned(2)*/ void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),memrendw,(__haystack,__word,__n_words))
#else /* LIBC: memrendw */
#include <local/string/memrendw.h>
/* Same as `memrchrw', but return `HAYSTACK-1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_memrendw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memrendw))
#endif /* memrendw... */
#endif /* !____localdep_memrendw_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `memrendw', but return the offset from `HAYSTACK', rather than the actual address. */
__LOCAL_LIBC(memrlenw) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memrlenw))(/*aligned(2)*/ void const *__restrict __haystack,
                                                      __UINT16_TYPE__ __word,
                                                      __SIZE_TYPE__ __n_words) {
#line 1540 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_memrendw(__haystack, __word, __n_words) - (__UINT16_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_memrlenw_defined */
