/* HASH CRC-32:0x8122bf18 */
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
#ifndef __local_c32memset_defined
#define __local_c32memset_defined 1
#include <__crt.h>
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
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memsetw,(/*aligned(2)*/ void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),memsetw,(__dst,__word,__n_words))
#else /* LIBC: memsetw */
#include <local/string/memsetw.h>
/* Fill memory with a given word */
#define __localdep_memsetw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetw))
#endif /* memsetw... */
#endif /* !____localdep_memsetw_defined */

/* Dependency: "memsetl" from "string" */
#ifndef ____localdep_memsetl_defined
#define ____localdep_memsetl_defined 1
#ifdef __fast_memsetl_defined
/* Fill memory with a given dword */
#define __localdep_memsetl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memsetl))
#elif defined(__CRT_HAVE_memsetl)
/* Fill memory with a given dword */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memsetl,(/*aligned(4)*/ void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),memsetl,(__dst,__dword,__n_dwords))
#else /* LIBC: memsetl */
#include <local/string/memsetl.h>
/* Fill memory with a given dword */
#define __localdep_memsetl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetl))
#endif /* memsetl... */
#endif /* !____localdep_memsetl_defined */

/* Dependency: "memset" from "string" */
#ifndef ____localdep_memset_defined
#define ____localdep_memset_defined 1
#ifdef __fast_memset_defined
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
#define __localdep_memset (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memset))
#elif defined(__CRT_HAVE_memset)
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),memset,(__dst,__byte,__n_bytes))
#else /* LIBC: memset */
#include <local/string/memset.h>
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
#define __localdep_memset (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memset))
#endif /* memset... */
#endif /* !____localdep_memset_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32memset) __ATTR_RETNONNULL __ATTR_NONNULL((1)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c32memset))(__CHAR32_TYPE__ *__dst,
                                                       __CHAR32_TYPE__ __filler,
                                                       __SIZE_TYPE__ __num_chars) {
#line 426 "kos/src/libc/magic/wchar.c"
#if __SIZEOF_WCHAR_T__ == 2
	return (__CHAR32_TYPE__ *)__localdep_memsetw(__dst, (__UINT16_TYPE__)__filler, __num_chars);
#elif __SIZEOF_WCHAR_T__ == 4
	return (__CHAR32_TYPE__ *)__localdep_memsetl(__dst, (__UINT32_TYPE__)__filler, __num_chars);
#else
	return (__CHAR32_TYPE__ *)__localdep_memset(__dst, (int)__filler, __num_chars * sizeof(__CHAR32_TYPE__));
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c32memset_defined */
