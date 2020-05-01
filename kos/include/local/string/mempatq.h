/* HASH CRC-32:0xdeadef5e */
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
#ifndef __local_mempatq_defined
#define __local_mempatq_defined 1
#include <__crt.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <hybrid/__wordbits.h>
/* Dependency: "mempsetq" from "string" */
#ifndef ____localdep_mempsetq_defined
#define ____localdep_mempsetq_defined 1
#ifdef __fast_mempsetq_defined
/* Same as `memsetq', but return `DST + N_QWORDS', rather than `DST' */
#define __localdep_mempsetq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetq))
#elif defined(__CRT_HAVE_mempsetq)
/* Same as `memsetq', but return `DST + N_QWORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_mempsetq,(/*aligned(8)*/ void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),mempsetq,(__dst,__qword,__n_qwords))
#else /* LIBC: mempsetq */
#include <local/string/mempsetq.h>
/* Same as `memsetq', but return `DST + N_QWORDS', rather than `DST' */
#define __localdep_mempsetq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetq))
#endif /* mempsetq... */
#endif /* !____localdep_mempsetq_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `memsetq', but repeat an 8-byte pattern on aligned addresses. */
__LOCAL_LIBC(mempatq) __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mempatq))(void *__restrict __dst,
                                                     __UINT64_TYPE__ __pattern,
                                                     __SIZE_TYPE__ __n_bytes) {
#line 2848 "kos/src/libc/magic/string.c"
	__BYTE_TYPE__ *__iter = (__BYTE_TYPE__ *)__dst;
	for (; __n_bytes && (__UINTPTR_TYPE__)__iter & 7; ++__iter, --__n_bytes)
		*__iter = __INT64_BYTE(__pattern, (__UINTPTR_TYPE__)__iter & 7);
	__iter = (__BYTE_TYPE__ *)__localdep_mempsetq(__iter, __pattern, __n_bytes / 8);
	for (__n_bytes &= 7; __n_bytes; ++__iter, --__n_bytes)
		*__iter = __INT64_BYTE(__pattern, (__UINTPTR_TYPE__)__iter & 7);
	return __dst;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_mempatq_defined */
