/* HASH CRC-32:0x8b4dc137 */
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
#ifndef __local_cuserid_defined
#define __local_cuserid_defined
#include <__crt.h>
#include <libc/template/environ.h>
#if defined(__CRT_HAVE_getlogin_r) || defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ) || (defined(__CRT_HAVE_getpwuid_r) && (defined(__CRT_HAVE_geteuid) || defined(__CRT_HAVE___geteuid) || defined(__CRT_HAVE___libc_geteuid) || defined(__CRT_HAVE_getresuid)))
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
#ifndef __local___localdep_getlogin_r_defined
#define __local___localdep_getlogin_r_defined
#ifdef __CRT_HAVE_getlogin_r
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUTS(1, 2),int,__NOTHROW_RPC,__localdep_getlogin_r,(char *__name, __SIZE_TYPE__ __name_len),getlogin_r,(__name,__name_len))
#elif defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ) || (defined(__CRT_HAVE_getpwuid_r) && (defined(__CRT_HAVE_geteuid) || defined(__CRT_HAVE___geteuid) || defined(__CRT_HAVE___libc_geteuid) || defined(__CRT_HAVE_getresuid)))
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/getlogin_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_getlogin_r __LIBC_LOCAL_NAME(getlogin_r)
#else /* ... */
#undef __local___localdep_getlogin_r_defined
#endif /* !... */
#endif /* !__local___localdep_getlogin_r_defined */
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
__NAMESPACE_LOCAL_END
#include <asm/crt/stdio.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(cuserid) __ATTR_OUT_OPT(1) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(cuserid))(char *__s) {
#if defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#ifdef __L_cuserid
#define __LOCAL___L_cuserid __L_cuserid
#else /* __L_cuserid */
#define __LOCAL___L_cuserid 9
#endif /* !__L_cuserid */
	/* Buffer is typed as `void *' so it can be re-used for `wcuserid(3)' */
	static void *__cuserid_buf;
	__errno_t __error;
	__SIZE_TYPE__ __bufsize;

	/* Special case for when the caller is providing the buffer. */
	if (__s != __NULLPTR)
		return (__NAMESPACE_LOCAL_SYM __localdep_getlogin_r)(__s, __LOCAL___L_cuserid) ? __NULLPTR : __s;

	/* Use the TLS buffer. */
#if defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize)
	__bufsize = (__NAMESPACE_LOCAL_SYM __localdep_malloc_usable_size)(__cuserid_buf) / sizeof(char);
#else /* __CRT_HAVE_malloc_usable_size || __CRT_HAVE__msize */
	__bufsize = __cuserid_buf ? __LOCAL___L_cuserid : 0;
#endif /* !__CRT_HAVE_malloc_usable_size && !__CRT_HAVE__msize */
	if (__bufsize < __LOCAL___L_cuserid) {
		void *__newbuf;
		__bufsize = __LOCAL___L_cuserid;
		__newbuf  = (__NAMESPACE_LOCAL_SYM __localdep_realloc)(__cuserid_buf, __bufsize * sizeof(char));
		if __unlikely(!__newbuf)
			goto __err;
		__cuserid_buf = __newbuf;
	}
#ifdef __ERANGE
__again:
#endif /* __ERANGE */
	__error = (__NAMESPACE_LOCAL_SYM __localdep_getlogin_r)((char *)__cuserid_buf, __bufsize);
	if __likely(__error == 0) {
		/* Trim unused memory (if a certain threshold is exceeded) */
		__SIZE_TYPE__ __retlen = (__NAMESPACE_LOCAL_SYM __localdep_strlen)((char *)__cuserid_buf) + 1;
		if (__retlen < __LOCAL___L_cuserid)
			__retlen = __LOCAL___L_cuserid; /* Retain minimal buffer size */
		if __likely((__retlen + 32) < __bufsize) {
			void *__retbuf = (__NAMESPACE_LOCAL_SYM __localdep_realloc)(__cuserid_buf, __retlen * sizeof(char));
			if __likely(__retbuf)
				__cuserid_buf = __retbuf;
		}
		return (char *)__cuserid_buf;
	}
#ifdef __ERANGE
	if (__error == __ERANGE && __bufsize < 1024) {
		void *__newbuf;
		__bufsize *= 2;
		__newbuf = (__NAMESPACE_LOCAL_SYM __localdep_realloc)(__cuserid_buf, __bufsize * sizeof(char));
		if __unlikely(!__newbuf)
			goto __err;
		__cuserid_buf = __newbuf;
		goto __again;
	}
#endif /* __ERANGE */
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__cuserid_buf);
	__cuserid_buf = __NULLPTR;
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
__err:
	return __NULLPTR;
#undef __LOCAL___L_cuserid
#else /* __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc */
#ifdef __L_cuserid
	static char __cuserid_buffer[__L_cuserid];
#else /* __L_cuserid */
	static char __cuserid_buffer[9];
#endif /* !__L_cuserid */
	if (__s == __NULLPTR)
		__s = __cuserid_buffer;
	return (__NAMESPACE_LOCAL_SYM __localdep_getlogin_r)(__s, sizeof(__cuserid_buffer)) ? __NULLPTR : __s;
#endif /* !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cuserid_defined
#define __local___localdep_cuserid_defined
#define __localdep_cuserid __LIBC_LOCAL_NAME(cuserid)
#endif /* !__local___localdep_cuserid_defined */
#else /* __CRT_HAVE_getlogin_r || __CRT_HAVE_getenv || __LOCAL_environ || (__CRT_HAVE_getpwuid_r && (__CRT_HAVE_geteuid || __CRT_HAVE___geteuid || __CRT_HAVE___libc_geteuid || __CRT_HAVE_getresuid)) */
#undef __local_cuserid_defined
#endif /* !__CRT_HAVE_getlogin_r && !__CRT_HAVE_getenv && !__LOCAL_environ && (!__CRT_HAVE_getpwuid_r || (!__CRT_HAVE_geteuid && !__CRT_HAVE___geteuid && !__CRT_HAVE___libc_geteuid && !__CRT_HAVE_getresuid)) */
#endif /* !__local_cuserid_defined */
