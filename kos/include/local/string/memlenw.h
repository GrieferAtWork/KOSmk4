/* HASH CRC-32:0x3b790a54 */
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
#ifndef __local_memlenw_defined
#define __local_memlenw_defined 1
#include <__crt.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "memendw" from "string" */
#ifndef ____localdep_memendw_defined
#define ____localdep_memendw_defined 1
#ifdef __fast_memendw_defined
/* Same as `memchrw', but return `HAYSTACK + N_WORDS * 2', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_memendw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendw))
#elif defined(__CRT_HAVE_memendw)
/* Same as `memchrw', but return `HAYSTACK + N_WORDS * 2', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memendw,(/*aligned(2)*/ void const *__restrict __haystack, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_bytes),memendw,(__haystack,__word,__n_bytes))
#else /* LIBC: memendw */
#include <local/string/memendw.h>
/* Same as `memchrw', but return `HAYSTACK + N_WORDS * 2', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_memendw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendw))
#endif /* memendw... */
#endif /* !____localdep_memendw_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `memendw', but return the offset from `HAYSTACK', rather than the actual address.
 * Returns `HAYSTACK + N_DWORDS * 2' if the given `NEEDLE' wasn't found */
__LOCAL_LIBC(memlenw) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memlenw))(/*aligned(2)*/ void const *__restrict __haystack,
                                                     __UINT16_TYPE__ __word,
                                                     __SIZE_TYPE__ __n_words) {
#line 1534 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_memendw(__haystack, __word, __n_words) - (__UINT16_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_memlenw_defined */
