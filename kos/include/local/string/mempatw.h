/* HASH CRC-32:0x93036d21 */
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
#ifndef __local_mempatw_defined
#define __local_mempatw_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <hybrid/__wordbits.h>
/* Dependency: "mempsetw" from "string" */
#ifndef ____localdep_mempsetw_defined
#define ____localdep_mempsetw_defined 1
#ifdef __fast_mempsetw_defined
/* Same as `memsetw', but return `DST + N_WORDS', rather than `DST' */
#define __localdep_mempsetw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetw))
#elif defined(__CRT_HAVE_mempsetw)
/* Same as `memsetw', but return `DST + N_WORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_mempsetw,(/*aligned(2)*/ void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),mempsetw,(__dst,__word,__n_words))
#else /* LIBC: mempsetw */
#include <local/string/mempsetw.h>
/* Same as `memsetw', but return `DST + N_WORDS', rather than `DST' */
#define __localdep_mempsetw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetw))
#endif /* mempsetw... */
#endif /* !____localdep_mempsetw_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `memsetw', but repeat a 2-byte pattern on aligned addresses. */
__LOCAL_LIBC(mempatw) __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mempatw))(void *__restrict __dst,
                                                     __UINT16_TYPE__ __pattern,
                                                     __SIZE_TYPE__ __n_bytes) {
#line 2818 "kos/src/libc/magic/string.c"
	__BYTE_TYPE__ *__iter = (__BYTE_TYPE__ *)__dst;
	if (__n_bytes && (__UINTPTR_TYPE__)__iter & 1) {
		*__iter = __INT16_BYTE(__pattern, 1);
		++__iter;
		--__n_bytes;
	}
	__iter = (__BYTE_TYPE__ *)__localdep_mempsetw(__iter, __pattern, __n_bytes / 2);
	if (__n_bytes & 1)
		*__iter = __INT16_BYTE(__pattern, 0);
	return __dst;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_mempatw_defined */
