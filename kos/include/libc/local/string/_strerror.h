/* HASH CRC-32:0x94ae8661 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__strerror_defined
#define __local__strerror_defined
#include <__crt.h>
#include <libc/errno.h>
#if defined(__CRT_HAVE__strerror_s) || defined(__libc_geterrno)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__strerror_s_defined
#define __local___localdep__strerror_s_defined
#ifdef __CRT_HAVE__strerror_s
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(3) __ATTR_OUTS(1, 2),__errno_t,__NOTHROW_RPC,__localdep__strerror_s,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__message),_strerror_s,(__buf,__buflen,__message))
#elif defined(__libc_geterrno)
__NAMESPACE_LOCAL_END
#include <libc/local/string/_strerror_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__strerror_s __LIBC_LOCAL_NAME(_strerror_s)
#else /* ... */
#undef __local___localdep__strerror_s_defined
#endif /* !... */
#endif /* !__local___localdep__strerror_s_defined */
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
#ifndef __local___localdep_malloc_usable_size_defined
#define __local___localdep_malloc_usable_size_defined
#ifdef __CRT_HAVE_malloc_usable_size
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_malloc_usable_size,(void *__restrict __mallptr),malloc_usable_size,(__mallptr))
#elif defined(__CRT_HAVE__msize)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_malloc_usable_size,(void *__restrict __mallptr),_msize,(__mallptr))
#else /* ... */
#undef __local___localdep_malloc_usable_size_defined
#endif /* !... */
#endif /* !__local___localdep_malloc_usable_size_defined */
#ifndef __local___localdep_realloc_defined
#define __local___localdep_realloc_defined
#if __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,{ return __builtin_realloc(__mallptr, __num_bytes); })
#elif defined(__CRT_HAVE_realloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE___libc_realloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),__libc_realloc,(__mallptr,__num_bytes))
#else /* ... */
#undef __local___localdep_realloc_defined
#endif /* !... */
#endif /* !__local___localdep_realloc_defined */
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
__LOCAL_LIBC(_strerror) __ATTR_WUNUSED __ATTR_IN_OPT(1) char *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(_strerror))(char const *__message) {
#if defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
	/* Buffer is typed as `void *' so it can be re-used for `_wcserror(3)' */
	static void *___strerror_buf = __NULLPTR;
	__errno_t __error;
#if defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize)
	__SIZE_TYPE__ __bufsize = (__NAMESPACE_LOCAL_SYM __localdep_malloc_usable_size)(___strerror_buf) / sizeof(char);
#else /* __CRT_HAVE_malloc_usable_size || __CRT_HAVE__msize */
	__SIZE_TYPE__ __bufsize = ___strerror_buf ? 64 : 0;
#endif /* !__CRT_HAVE_malloc_usable_size && !__CRT_HAVE__msize */
	if (__bufsize < 64) {
		void *__newbuf;
		__bufsize = 64;
		__newbuf  = (__NAMESPACE_LOCAL_SYM __localdep_realloc)(___strerror_buf, __bufsize * sizeof(char));
		if __unlikely(!__newbuf)
			goto __err;
		___strerror_buf = __newbuf;
	}
#ifdef __ERANGE
__again:
#endif /* __ERANGE */
	__error = (__NAMESPACE_LOCAL_SYM __localdep__strerror_s)((char *)___strerror_buf, __bufsize, __message);
	if __likely(__error == 0) {
		/* Trim unused memory (if a certain threshold is exceeded) */
		__SIZE_TYPE__ __retlen = (__NAMESPACE_LOCAL_SYM __localdep_strlen)((char *)___strerror_buf) + 1;
		if (__retlen < 64)
			__retlen = 64; /* Retain minimal buffer size */
		if __likely((__retlen + 32) < __bufsize) {
			void *__retbuf = (__NAMESPACE_LOCAL_SYM __localdep_realloc)(___strerror_buf, __retlen * sizeof(char));
			if __likely(__retbuf)
				___strerror_buf = __retbuf;
		}
		return (char *)___strerror_buf;
	}
#ifdef __ERANGE
	if (__error == __ERANGE && __bufsize < 1024) {
		void *__newbuf;
		__bufsize *= 2;
		__newbuf = (__NAMESPACE_LOCAL_SYM __localdep_realloc)(___strerror_buf, __bufsize * sizeof(char));
		if __unlikely(!__newbuf)
			goto __err;
		___strerror_buf = __newbuf;
		goto __again;
	}
#endif /* __ERANGE */
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(___strerror_buf);
	___strerror_buf = __NULLPTR;
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
__err:
	return __NULLPTR;
#else /* __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc */
	static char ___strerror_buf[64];
	if __likely((__NAMESPACE_LOCAL_SYM __localdep__strerror_s)(___strerror_buf, __COMPILER_LENOF(___strerror_buf), __message) == 0)
		return ___strerror_buf;
	return __NULLPTR;
#endif /* !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__strerror_defined
#define __local___localdep__strerror_defined
#define __localdep__strerror __LIBC_LOCAL_NAME(_strerror)
#endif /* !__local___localdep__strerror_defined */
#else /* __CRT_HAVE__strerror_s || __libc_geterrno */
#undef __local__strerror_defined
#endif /* !__CRT_HAVE__strerror_s && !__libc_geterrno */
#endif /* !__local__strerror_defined */
