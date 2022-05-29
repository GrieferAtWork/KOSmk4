/* HASH CRC-32:0xe2ed2149 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_wttyname_r_defined
#define __local_wttyname_r_defined
#include <__crt.h>
#ifdef __CRT_HAVE_ttyname_r
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#elif defined(__CRT_HAVE___libc_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),__libc_free,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
#ifndef __local___localdep_malloc_defined
#define __local___localdep_malloc_defined
#if __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,{ return __builtin_malloc(__num_bytes); })
#elif defined(__CRT_HAVE_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,(__num_bytes))
#elif defined(__CRT_HAVE___libc_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),__libc_malloc,(__num_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/malloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_malloc __LIBC_LOCAL_NAME(malloc)
#else /* ... */
#undef __local___localdep_malloc_defined
#endif /* !... */
#endif /* !__local___localdep_malloc_defined */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
#ifndef __local___localdep_ttyname_r_defined
#define __local___localdep_ttyname_r_defined
__CREDIRECT(__ATTR_OUTS(2, 3),__errno_t,__NOTHROW_RPC,__localdep_ttyname_r,(__fd_t __fd, char *__buf, __SIZE_TYPE__ __buflen),ttyname_r,(__fd,__buf,__buflen))
#endif /* !__local___localdep_ttyname_r_defined */
#ifndef __local___localdep_unicode_8to16_n_defined
#define __local___localdep_unicode_8to16_n_defined
#ifdef __CRT_HAVE_unicode_8to16_n
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(3, 4) __ATTR_OUTS(1, 2),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_unicode_8to16_n,(__CHAR16_TYPE__ *__restrict __utf16_dst, __SIZE_TYPE__ __utf16_maxwords, char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_bytes),unicode_8to16_n,(__utf16_dst,__utf16_maxwords,__utf8_text,__utf8_bytes))
#else /* __CRT_HAVE_unicode_8to16_n */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/unicode_8to16_n.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unicode_8to16_n __LIBC_LOCAL_NAME(unicode_8to16_n)
#endif /* !__CRT_HAVE_unicode_8to16_n */
#endif /* !__local___localdep_unicode_8to16_n_defined */
#ifndef __local___localdep_unicode_8to32_n_defined
#define __local___localdep_unicode_8to32_n_defined
#ifdef __CRT_HAVE_unicode_8to32_n
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(3, 4) __ATTR_OUTS(1, 2),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_unicode_8to32_n,(__CHAR32_TYPE__ *__restrict __utf32_dst, __SIZE_TYPE__ __utf32_maxwords, char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_bytes),unicode_8to32_n,(__utf32_dst,__utf32_maxwords,__utf8_text,__utf8_bytes))
#else /* __CRT_HAVE_unicode_8to32_n */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/unicode_8to32_n.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unicode_8to32_n __LIBC_LOCAL_NAME(unicode_8to32_n)
#endif /* !__CRT_HAVE_unicode_8to32_n */
#endif /* !__local___localdep_unicode_8to32_n_defined */
#ifndef __local___localdep_unicode_len8to16_defined
#define __local___localdep_unicode_len8to16_defined
#ifdef __CRT_HAVE_unicode_len8to16
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_INS(1, 2),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_unicode_len8to16,(char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_bytes),unicode_len8to16,(__utf8_text,__utf8_bytes))
#else /* __CRT_HAVE_unicode_len8to16 */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/unicode_len8to16.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unicode_len8to16 __LIBC_LOCAL_NAME(unicode_len8to16)
#endif /* !__CRT_HAVE_unicode_len8to16 */
#endif /* !__local___localdep_unicode_len8to16_defined */
#ifndef __local___localdep_unicode_len8to32_defined
#define __local___localdep_unicode_len8to32_defined
#ifdef __CRT_HAVE_unicode_len8to32
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_INS(1, 2),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_unicode_len8to32,(char const *__restrict __utf8_text, __SIZE_TYPE__ __utf8_bytes),unicode_len8to32,(__utf8_text,__utf8_bytes))
#else /* __CRT_HAVE_unicode_len8to32 */
__NAMESPACE_LOCAL_END
#include <libc/local/unicode/unicode_len8to32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unicode_len8to32 __LIBC_LOCAL_NAME(unicode_len8to32)
#endif /* !__CRT_HAVE_unicode_len8to32 */
#endif /* !__local___localdep_unicode_len8to32_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wttyname_r) __ATTR_OUTS(2, 3) __errno_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(wttyname_r))(__fd_t __fd, __WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __buflen) {
	__errno_t __result;
#if __SIZEOF_WCHAR_T__ == 4
	__SIZE_TYPE__ __utf8_buflen = __buflen * 7; /* s.a. `UNICODE_32TO8_MAXBUF()' */
#else /* __SIZEOF_WCHAR_T__ == 4 */
	__SIZE_TYPE__ __utf8_buflen = __buflen * 3; /* s.a. `UNICODE_16TO8_MAXBUF()' */
#endif /* __SIZEOF_WCHAR_T__ != 4 */
	char *__utf8_buf = (char *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(__utf8_buflen * sizeof(char));
	if __unlikely(!__utf8_buf) {
#ifdef __ENOMEM
		return __ENOMEM;
#else /* __ENOMEM */
		return 1;
#endif /* !__ENOMEM */
	}
	__result = (__NAMESPACE_LOCAL_SYM __localdep_ttyname_r)(__fd, __utf8_buf, __utf8_buflen);
	if (__result == 0) {
		__SIZE_TYPE__ __reqlen;
		__utf8_buflen = (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__utf8_buf) + 1; /* +1 for trailing NUL */
#if __SIZEOF_WCHAR_T__ == 4
		__reqlen = (__NAMESPACE_LOCAL_SYM __localdep_unicode_len8to32)(__utf8_buf, __utf8_buflen);
#else /* __SIZEOF_WCHAR_T__ == 4 */
		__reqlen = (__NAMESPACE_LOCAL_SYM __localdep_unicode_len8to16)(__utf8_buf, __utf8_buflen);
#endif /* __SIZEOF_WCHAR_T__ != 4 */
		if (__reqlen > __buflen) {
#ifdef __ERANGE
			__result = __ERANGE;
#else /* __ERANGE */
			__result = 1;
#endif /* !__ERANGE */
		} else {
#if __SIZEOF_WCHAR_T__ == 4
			__buf = (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_unicode_8to32_n)((__CHAR32_TYPE__ *)__buf, __buflen, __utf8_buf, __reqlen);
#else /* __SIZEOF_WCHAR_T__ == 4 */
			__buf = (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_unicode_8to16_n)((__CHAR16_TYPE__ *)__buf, __buflen, __utf8_buf, __reqlen);
#endif /* __SIZEOF_WCHAR_T__ != 4 */
			*__buf = '\0'; /* NUL-terminate */
		}
	}
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_buf);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wttyname_r_defined
#define __local___localdep_wttyname_r_defined
#define __localdep_wttyname_r __LIBC_LOCAL_NAME(wttyname_r)
#endif /* !__local___localdep_wttyname_r_defined */
#else /* __CRT_HAVE_ttyname_r */
#undef __local_wttyname_r_defined
#endif /* !__CRT_HAVE_ttyname_r */
#endif /* !__local_wttyname_r_defined */
