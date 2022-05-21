/* HASH CRC-32:0x6107e5cb */
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
#ifndef __local_spaces_defined
#define __local_spaces_defined
#include <__crt.h>
#if defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memset_defined
#define __local___localdep_memset_defined
#ifdef __CRT_HAVE_memset
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_ACCESS_WRS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),memset,(__dst,__byte,__n_bytes))
#else /* __CRT_HAVE_memset */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memset.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memset __LIBC_LOCAL_NAME(memset)
#endif /* !__CRT_HAVE_memset */
#endif /* !__local___localdep_memset_defined */
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
	static char *__buf = __NULLPTR;
	static __SIZE_TYPE__ __buflen = 0; /* # of space characters in `buf' (followed by NUL) */
	if (__buflen < __count) {
		char *__newbuf = (char *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__buf, (__count + 1) * sizeof(char));
		if (!__newbuf)
			return __NULLPTR;
		(__NAMESPACE_LOCAL_SYM __localdep_memset)(__newbuf + __buflen, ' ', __count - __buflen);
		__buf    = __newbuf;
		__buflen = __count;
	}
	return __buf + __buflen - __count;
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
