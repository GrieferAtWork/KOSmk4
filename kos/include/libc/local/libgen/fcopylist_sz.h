/* HASH CRC-32:0xdcd1d6f0 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_fcopylist_sz_defined
#define __local_fcopylist_sz_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
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
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/malloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_malloc __LIBC_LOCAL_NAME(malloc)
#endif /* !... */
#endif /* !__local___localdep_malloc_defined */
#ifndef __local___localdep_memmovedown_defined
#define __local___localdep_memmovedown_defined
#ifdef __CRT_HAVE_memmovedown
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmovedown,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE_memmove)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmove,(__dst,__src,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memmovedown.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memmovedown __LIBC_LOCAL_NAME(memmovedown)
#endif /* !... */
#endif /* !__local___localdep_memmovedown_defined */
#ifndef __local___localdep_read_defined
#define __local___localdep_read_defined
#ifdef __CRT_HAVE_read
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__read)
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),_read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___read)
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),__read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___libc_read)
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),__libc_read,(__fd,__buf,__bufsize))
#else /* ... */
#undef __local___localdep_read_defined
#endif /* !... */
#endif /* !__local___localdep_read_defined */
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
__NAMESPACE_LOCAL_END
#include <asm/crt/malloc.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fcopylist_sz) __ATTR_FDREAD(1) __ATTR_OUT(2) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fcopylist_sz))(__fd_t __fd, __SIZE_TYPE__ *__p_filesize) {
	__SIZE_TYPE__ __reslen  = 0;
	__SIZE_TYPE__ __buflen  = 1024;
	__BYTE_TYPE__ *__result = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(__buflen);
	if __unlikely(!__result) {
		__buflen = 1;
		__result = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(1);
		if __unlikely(!__result)
			goto __err;
	}
	for (;;) {
		/* Ensure that buffer space is available. */
		__SIZE_TYPE__ __i, __insize;
		__SIZE_TYPE__ __freelen = __buflen - __reslen;
		__BYTE_TYPE__ *__bufptr;
		if __unlikely(!__freelen) {
			__BYTE_TYPE__ *__new_result;
			__SIZE_TYPE__ __newlen = __buflen * 2;
			if __unlikely(__newlen < __buflen)
				__newlen = __buflen + 1;
			__new_result = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__result, __newlen);
			if __unlikely(!__new_result) {
				__newlen = __buflen + 1;
				__new_result = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__result, __newlen);
				if __unlikely(!__new_result)
					goto __err_r;
			}
			__result  = __new_result;
			__buflen  = __newlen;
			__freelen = __buflen - __reslen;
		}
		__bufptr = __result + __reslen;
		__insize = (__SIZE_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_read)(__fd, __bufptr, __freelen);
		if ((__SSIZE_TYPE__)__insize <= 0) {
			if __unlikely((__SSIZE_TYPE__)__insize < 0)
				goto __err_r;
			break; /* End-of-file */
		}
		/* Replace all line-feeds within read text with '\0' */

		for (__i = 0; __i < __insize;) {
			char __ch = __bufptr[__i];
			if (__ch == '\r') {
				/* Universal linefeed support */
				__bufptr[__i] = '\0';
				++__i;
				if (__i >= __insize)
					break;
				if (__bufptr[__i] == '\n') {
					/* Collapse 2-byte linefeed into a single '\0' */
					--__insize;
					(__NAMESPACE_LOCAL_SYM __localdep_memmovedown)(&__bufptr[__i],
					            &__bufptr[__i + 1],
					            __insize - __i);
				}
			} else {
				if (__ch == '\n')
					__bufptr[__i] = '\0';
				++__i;
			}
		}






		__reslen += __insize;
	}

	/* Free unused memory */
	{
		__BYTE_TYPE__ *__new_result;
#ifdef __REALLOC_ZERO_IS_NONNULL
		__new_result = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__result, __reslen);
#else /* __REALLOC_ZERO_IS_NONNULL */
		__new_result = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__result, __reslen ? __reslen : 1);
#endif /* !__REALLOC_ZERO_IS_NONNULL */
		if __likely(__new_result)
			__result = __new_result;
	}
	*__p_filesize = __reslen;
	return (char *)__result;
__err_r:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__result);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
__err:
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fcopylist_sz_defined
#define __local___localdep_fcopylist_sz_defined
#define __localdep_fcopylist_sz __LIBC_LOCAL_NAME(fcopylist_sz)
#endif /* !__local___localdep_fcopylist_sz_defined */
#else /* (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#undef __local_fcopylist_sz_defined
#endif /* (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read) || (!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) */
#endif /* !__local_fcopylist_sz_defined */
