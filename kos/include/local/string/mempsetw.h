/* HASH CRC-32:0xcf8ad7 */
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
#ifndef __local_mempsetw_defined
#define __local_mempsetw_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "memsetw" from "string" */
#ifndef ____localdep_memsetw_defined
#define ____localdep_memsetw_defined 1
#ifdef __fast_memsetw_defined
/* Fill memory with a given word */
#define __localdep_memsetw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetw))
#elif defined(__CRT_HAVE_memsetw)
/* Fill memory with a given word */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),memsetw,(__dst,__word,__n_words))
#else /* LIBC: memsetw */
#include <local/string/memsetw.h>
/* Fill memory with a given word */
#define __localdep_memsetw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetw))
#endif /* memsetw... */
#endif /* !____localdep_memsetw_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `memsetw', but return `DST+N_WORDS', rather than `DST' */
__LOCAL_LIBC(mempsetw) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mempsetw))(void *__restrict __dst,
                                                      __UINT16_TYPE__ __word,
                                                      __SIZE_TYPE__ __n_words) {
#line 1067 "kos/src/libc/magic/string.c"
	return (__UINT16_TYPE__ *)__localdep_memsetw(__dst, __word, __n_words) + __n_words;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_mempsetw_defined */
