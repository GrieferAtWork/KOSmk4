/* HASH CRC-32:0x4e48df92 */
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
#ifndef __local_dyn_string_resize_defined
#define __local_dyn_string_resize_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xmalloc_failed))
#include <features.h>
#include <bits/crt/dyn-string.h>
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
#ifndef __local___localdep_xrealloc_defined
#define __local___localdep_xrealloc_defined
#ifdef __CRT_HAVE_xrealloc
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_xrealloc,(void *__ptr, __SIZE_TYPE__ __num_bytes),xrealloc,(__ptr,__num_bytes))
#elif defined(__CRT_HAVE_xmalloc_failed)
__NAMESPACE_LOCAL_END
#include <libc/local/libiberty/xrealloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_xrealloc __LIBC_LOCAL_NAME(xrealloc)
#else /* ... */
#undef __local___localdep_xrealloc_defined
#endif /* !... */
#endif /* !__local___localdep_xrealloc_defined */
__LOCAL_LIBC(dyn_string_resize) __ATTR_RETNONNULL __ATTR_INOUT(1) struct dyn_string *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(dyn_string_resize))(struct dyn_string *__self, __STDC_INT_AS_SIZE_T __min_chars) {
	char *__newbuf;
	__SIZE_TYPE__ __newalloc;
	++__min_chars; /* +1 for trailing NUL */
	if ((__SIZE_TYPE__)__self->allocated >= (__SIZE_TYPE__)__min_chars)
		return __self; /* Already enough space. */
	__newalloc = (__SIZE_TYPE__)__self->allocated;
	do {
		__newalloc = (__newalloc << 1) | 1;
	} while (__newalloc < (__SIZE_TYPE__)__min_chars);
	__newbuf = (char *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__self->s, __newalloc * sizeof(char));
	if (!__newbuf) {
		__newalloc = __min_chars;
		__newbuf = (char *)(__NAMESPACE_LOCAL_SYM __localdep_xrealloc)(__self->s, __newalloc * sizeof(char));
	}
#if (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize)) && !defined(__OPTIMIZE_SIZE__)
	__newalloc = (__NAMESPACE_LOCAL_SYM __localdep_malloc_usable_size)(__newbuf) / sizeof(char);
#endif /* (__CRT_HAVE_malloc_usable_size || __CRT_HAVE__msize) && !__OPTIMIZE_SIZE__ */
	__self->allocated = (__STDC_INT_AS_SIZE_T)__newalloc;
	__self->s         = __newbuf;
	return __self;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_dyn_string_resize_defined
#define __local___localdep_dyn_string_resize_defined
#define __localdep_dyn_string_resize __LIBC_LOCAL_NAME(dyn_string_resize)
#endif /* !__local___localdep_dyn_string_resize_defined */
#else /* (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_xrealloc || __CRT_HAVE_xmalloc_failed) */
#undef __local_dyn_string_resize_defined
#endif /* (!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_xrealloc && !__CRT_HAVE_xmalloc_failed) */
#endif /* !__local_dyn_string_resize_defined */
