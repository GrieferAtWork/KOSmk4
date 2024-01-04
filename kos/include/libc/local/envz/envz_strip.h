/* HASH CRC-32:0x3673ef72 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_envz_strip_defined
#define __local_envz_strip_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memmovedownc_defined
#define __local___localdep_memmovedownc_defined
#ifdef __CRT_HAVE_memmovedownc
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,__localdep_memmovedownc,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memmovedownc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memmovedownc */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memmovedownc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memmovedownc __LIBC_LOCAL_NAME(memmovedownc)
#endif /* !__CRT_HAVE_memmovedownc */
#endif /* !__local___localdep_memmovedownc_defined */
#ifndef __local___localdep_realloc_defined
#define __local___localdep_realloc_defined
#if __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__CEIREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,{ return __builtin_realloc(__mallptr, __num_bytes); })
#elif defined(__CRT_HAVE_realloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE___libc_realloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),__libc_realloc,(__mallptr,__num_bytes))
#else /* ... */
#undef __local___localdep_realloc_defined
#endif /* !... */
#endif /* !__local___localdep_realloc_defined */
#ifndef __local___localdep_strchrnul_defined
#define __local___localdep_strchrnul_defined
#ifdef __CRT_HAVE_strchrnul
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchrnul,(char const *__restrict __haystack, int __needle),strchrnul,(__haystack,__needle))
#else /* __CRT_HAVE_strchrnul */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strchrnul.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strchrnul __LIBC_LOCAL_NAME(strchrnul)
#endif /* !__CRT_HAVE_strchrnul */
#endif /* !__local___localdep_strchrnul_defined */
#ifndef __local___localdep_strend_defined
#define __local___localdep_strend_defined
#ifdef __CRT_HAVE_strend
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strend,(char const *__restrict __str),strend,(__str))
#else /* __CRT_HAVE_strend */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strend.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strend __LIBC_LOCAL_NAME(strend)
#endif /* !__CRT_HAVE_strend */
#endif /* !__local___localdep_strend_defined */
__LOCAL_LIBC(envz_strip) __ATTR_INOUT(1) __ATTR_INOUT(2) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(envz_strip))(char **__restrict __penvz, __SIZE_TYPE__ *__restrict __penvz_len) {
	char *__start, *__ptr, *__end;
	__SIZE_TYPE__ __oldlen, __newlen;
	__ptr = __start = *__penvz;
	__end = __ptr + (__oldlen = *__penvz_len);
	while (__ptr < __end) {
		char *__next;
		__SIZE_TYPE__ __partlen;
		__next = (__NAMESPACE_LOCAL_SYM __localdep_strchrnul)(__ptr, '=');
		if (*__next) {
			__ptr = (__NAMESPACE_LOCAL_SYM __localdep_strend)(__next) + 1;
			continue;
		}
		/* Remove this entry. */
		__next = (__NAMESPACE_LOCAL_SYM __localdep_strend)(__next) + 1;
		__partlen = (__SIZE_TYPE__)(__end - __next);
		(__NAMESPACE_LOCAL_SYM __localdep_memmovedownc)(__ptr, __next, __partlen, sizeof(char));
		__end -= __partlen;
	}
	__newlen = (__SIZE_TYPE__)(__end - __start);
	if (__newlen < __oldlen) {
		*__penvz_len = __newlen;
#if defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
		__start = (char *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__start, __newlen);
		if __likely(__start)
			*__penvz = __start;
#endif /* __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc */
	}
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_envz_strip_defined
#define __local___localdep_envz_strip_defined
#define __localdep_envz_strip __LIBC_LOCAL_NAME(envz_strip)
#endif /* !__local___localdep_envz_strip_defined */
#endif /* !__local_envz_strip_defined */
