/* HASH CRC-32:0x6c19d896 */
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
#ifndef __local_spaces_defined
#define __local_spaces_defined
#include <__crt.h>
#if defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
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
#ifndef __local___localdep_mempset_defined
#define __local___localdep_mempset_defined
#ifdef __CRT_HAVE_mempset
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_mempset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),mempset,(__dst,__byte,__n_bytes))
#else /* __CRT_HAVE_mempset */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempset.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempset __LIBC_LOCAL_NAME(mempset)
#endif /* !__CRT_HAVE_mempset */
#endif /* !__local___localdep_mempset_defined */
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
__LOCAL_LIBC(spaces) __ATTR_WUNUSED char const *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(spaces))(__STDC_INT_AS_SIZE_T __count) {
	/* XXX: Race condition when one thread realloc-s while another is using the string */
	static char *__spaces_buf = __NULLPTR;
#if defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize)
	__SIZE_TYPE__ __buflen = (__NAMESPACE_LOCAL_SYM __localdep_malloc_usable_size)(__spaces_buf) / sizeof(char);
	if (__count >= __buflen) {
		__SIZE_TYPE__ __newlen;
		char *__newbuf = (char *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__spaces_buf, (__count + 1) * sizeof(char));
		if (!__newbuf)
			return __NULLPTR;
		__newlen = (__NAMESPACE_LOCAL_SYM __localdep_malloc_usable_size)(__newbuf) - 1; /* Exclude trailing NUL */
		*(char *)(__NAMESPACE_LOCAL_SYM __localdep_mempset)(__newbuf + __buflen, ' ', __newlen - __buflen) = '\0';
		__spaces_buf = __newbuf;
		__buflen     = __newlen;
	} else {
		--__buflen; /* Exclude trailing NUL */
	}
#else /* __CRT_HAVE_malloc_usable_size || __CRT_HAVE__msize */
	static __SIZE_TYPE__ __buflen = 0; /* # of space characters in `spaces_buf' (followed by NUL) */
	if (__count >= __buflen) {
		char *__newbuf = (char *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__spaces_buf, (__count + 1) * sizeof(char));
		if (!__newbuf)
			return __NULLPTR;
		*(char *)(__NAMESPACE_LOCAL_SYM __localdep_mempset)(__newbuf + __buflen, ' ', __count - __buflen) = '\0';
		__spaces_buf = __newbuf;
		__buflen     = __count;
	}
#endif /* !__CRT_HAVE_malloc_usable_size && !__CRT_HAVE__msize */
	return __spaces_buf + __buflen - __count;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_spaces_defined
#define __local___localdep_spaces_defined
#define __localdep_spaces __LIBC_LOCAL_NAME(spaces)
#endif /* !__local___localdep_spaces_defined */
#else /* __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc */
#undef __local_spaces_defined
#endif /* !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc */
#endif /* !__local_spaces_defined */
