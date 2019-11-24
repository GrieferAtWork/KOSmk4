/* HASH CRC-32:0xe5d53d22 */
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
#ifndef __local_c16mempset_defined
#define __local_c16mempset_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
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

/* Dependency: "mempsetl" from "string" */
#ifndef ____localdep_mempsetl_defined
#define ____localdep_mempsetl_defined 1
#ifdef __fast_mempsetl_defined
/* Same as `memsetl', but return `DST + N_DWORDS', rather than `DST' */
#define __localdep_mempsetl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetl))
#elif defined(__CRT_HAVE_mempsetl)
/* Same as `memsetl', but return `DST + N_DWORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempsetl,(/*aligned(4)*/ void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),mempsetl,(__dst,__dword,__n_dwords))
#else /* LIBC: mempsetl */
#include <local/string/mempsetl.h>
/* Same as `memsetl', but return `DST + N_DWORDS', rather than `DST' */
#define __localdep_mempsetl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetl))
#endif /* mempsetl... */
#endif /* !____localdep_mempsetl_defined */

/* Dependency: "mempset" from "string" */
#ifndef ____localdep_mempset_defined
#define ____localdep_mempset_defined 1
#ifdef __fast_mempset_defined
/* Same as `memset', but return `DST + N_BYTES', rather than `DST' */
#define __localdep_mempset (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempset))
#elif defined(__CRT_HAVE_mempset)
/* Same as `memset', but return `DST + N_BYTES', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_mempset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),mempset,(__dst,__byte,__n_bytes))
#else /* LIBC: mempset */
#include <local/string/mempset.h>
/* Same as `memset', but return `DST + N_BYTES', rather than `DST' */
#define __localdep_mempset (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempset))
#endif /* mempset... */
#endif /* !____localdep_mempset_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as wmemset, but return a pointer after the last written character */
__LOCAL_LIBC(c16mempset) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16mempset))(__CHAR16_TYPE__ *__dst,
                                                        __CHAR16_TYPE__ __filler,
                                                        __SIZE_TYPE__ __num_chars) {
#line 1369 "kos/src/libc/magic/wchar.c"
#if 2 == 2
	return (__CHAR16_TYPE__ *)__localdep_mempsetw(__dst, (__UINT16_TYPE__)__filler, __num_chars);
#elif 2 == 4
	return (__CHAR16_TYPE__ *)__localdep_mempsetl(__dst, (__UINT32_TYPE__)__filler, __num_chars);
#else
	return (__CHAR16_TYPE__ *)__localdep_mempset(__dst, (int)__filler, __num_chars * sizeof(__CHAR16_TYPE__));
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c16mempset_defined */
