/* HASH CRC-32:0xc1dbe495 */
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
#ifndef __local_vconcat_defined
#define __local_vconcat_defined
#include <__crt.h>
#if defined(__CRT_HAVE_xmalloc) || defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xcalloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mempcpyc_defined
#define __local___localdep_mempcpyc_defined
#ifdef __CRT_HAVE_mempcpyc
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,__localdep_mempcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),mempcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_mempcpyc */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempcpyc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempcpyc __LIBC_LOCAL_NAME(mempcpyc)
#endif /* !__CRT_HAVE_mempcpyc */
#endif /* !__local___localdep_mempcpyc_defined */
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
#ifndef __local___localdep_xmalloc_defined
#define __local___localdep_xmalloc_defined
#ifdef __CRT_HAVE_xmalloc
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_xmalloc,(__SIZE_TYPE__ __num_bytes),xmalloc,(__num_bytes))
#elif defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xcalloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))
__NAMESPACE_LOCAL_END
#include <libc/local/libiberty/xmalloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_xmalloc __LIBC_LOCAL_NAME(xmalloc)
#else /* ... */
#undef __local___localdep_xmalloc_defined
#endif /* !... */
#endif /* !__local___localdep_xmalloc_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vconcat) __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN_OPT(1) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(vconcat))(char const *__first, __builtin_va_list __args) {
	char *__result, *__ptr;
	__SIZE_TYPE__ __totlen = 0;
	__builtin_va_list __copy;
	__builtin_va_copy(__copy, __args);
	for (__ptr = (char *)__first; __ptr; __ptr = __builtin_va_arg(__copy, char *))
		__totlen += (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__ptr);
	__builtin_va_end(__copy);
	__ptr = __result = (char *)(__NAMESPACE_LOCAL_SYM __localdep_xmalloc)((__totlen + 1) * sizeof(char));
	for (; __first; __first = __builtin_va_arg(__args, char *))
		__ptr = (char *)(__NAMESPACE_LOCAL_SYM __localdep_mempcpyc)(__ptr, __first, (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__first), sizeof(char));
	*__ptr = '\0';
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vconcat_defined
#define __local___localdep_vconcat_defined
#define __localdep_vconcat __LIBC_LOCAL_NAME(vconcat)
#endif /* !__local___localdep_vconcat_defined */
#else /* __CRT_HAVE_xmalloc || __CRT_HAVE_xrealloc || __CRT_HAVE_xcalloc || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && __CRT_HAVE_xmalloc_failed) */
#undef __local_vconcat_defined
#endif /* !__CRT_HAVE_xmalloc && !__CRT_HAVE_xrealloc && !__CRT_HAVE_xcalloc && ((!__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) || !__CRT_HAVE_xmalloc_failed) */
#endif /* !__local_vconcat_defined */
