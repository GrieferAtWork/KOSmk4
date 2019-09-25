/* HASH CRC-32:0xd16603f */
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
#ifndef __local_memlenq_defined
#define __local_memlenq_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "memendq" from "string" */
#ifndef ____localdep_memendq_defined
#define ____localdep_memendq_defined 1
#if defined(__fast_memendq_defined)
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_memendq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memendq))
#elif defined(__CRT_HAVE_memendq)
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_memendq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_bytes),memendq,(__haystack,__qword,__n_bytes))
#else /* LIBC: memendq */
#include <local/string/memendq.h>
/* Same as `memchrq', but return `HAYSTACK+N_QWORDS', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_memendq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memendq))
#endif /* memendq... */
#endif /* !____localdep_memendq_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `memendq', but return the offset from `HAYSTACK', rather than the actual address. */
__LOCAL_LIBC(memlenq) __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memlenq))(void const *__restrict __haystack,
                                                     __UINT64_TYPE__ __qword,
                                                     __SIZE_TYPE__ __n_qwords) {
#line 1518 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_memendq(__haystack, __qword, __n_qwords) - (__UINT64_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_memlenq_defined */
