/* HASH CRC-32:0xe837f2fe */
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
#ifndef __local__Getdays_defined
#define __local__Getdays_defined
#include <__crt.h>
#if defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_BEGIN
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
#ifndef __local___localdep_nl_langinfo_defined
#define __local___localdep_nl_langinfo_defined
#ifdef __CRT_HAVE_nl_langinfo
__NAMESPACE_LOCAL_END
#include <bits/crt/langinfo.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_RETNONNULL,char __KOS_FIXED_CONST *,__NOTHROW_NCX,__localdep_nl_langinfo,(__nl_item __item),nl_langinfo,(__item))
#else /* __CRT_HAVE_nl_langinfo */
__NAMESPACE_LOCAL_END
#include <libc/local/langinfo/nl_langinfo.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_nl_langinfo __LIBC_LOCAL_NAME(nl_langinfo)
#endif /* !__CRT_HAVE_nl_langinfo */
#endif /* !__local___localdep_nl_langinfo_defined */
#ifndef __local___localdep_stpcpy_defined
#define __local___localdep_stpcpy_defined
#if __has_builtin(__builtin_stpcpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_stpcpy)
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,__localdep_stpcpy,(char *__restrict __buf, char const *__restrict __src),stpcpy,{ return __builtin_stpcpy(__buf, __src); })
#elif defined(__CRT_HAVE_stpcpy)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,__localdep_stpcpy,(char *__restrict __buf, char const *__restrict __src),stpcpy,(__buf,__src))
#elif defined(__CRT_HAVE___stpcpy)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,__localdep_stpcpy,(char *__restrict __buf, char const *__restrict __src),__stpcpy,(__buf,__src))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/stpcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_stpcpy __LIBC_LOCAL_NAME(stpcpy)
#endif /* !... */
#endif /* !__local___localdep_stpcpy_defined */
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
#include <asm/crt/langinfo.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_Getdays) __ATTR_WUNUSED char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_Getdays))(void) {
	/* Essentially, we do:
	 * >> strdup(":Sun:Sunday:Mon:Monday:Tue:Tuesday:Wed:Wednesday:Thu:Thursday:Fri:Friday:Sat:Saturday") */
	__SIZE_TYPE__ __len = 0;
	unsigned int __i;
	char *__result;
	for (__i = 0; __i < 7; ++__i) {
		char const *__p;
		__len += 2; /* 2x ':' */
		if ((__p = (__NAMESPACE_LOCAL_SYM __localdep_nl_langinfo)(_NL_TIME_ABDAY_1 + __i)) != __NULLPTR)
			__len += (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__p);
		if ((__p = (__NAMESPACE_LOCAL_SYM __localdep_nl_langinfo)(_NL_TIME_DAY_1 + __i)) != __NULLPTR)
			__len += (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__p);
	}
	__result = (char *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)((__len + 1) * sizeof(char));
	if __likely(__result) {
		char *__dst = __result;
		for (__i = 0; __i < 7; ++__i) {
			char const *__p;
			*__dst++ = ':';
			if ((__p = (__NAMESPACE_LOCAL_SYM __localdep_nl_langinfo)(_NL_TIME_ABDAY_1 + __i)) != __NULLPTR)
				__dst = (__NAMESPACE_LOCAL_SYM __localdep_stpcpy)(__dst, __p);
			*__dst++ = ':';
			if ((__p = (__NAMESPACE_LOCAL_SYM __localdep_nl_langinfo)(_NL_TIME_DAY_1 + __i)) != __NULLPTR)
				__dst = (__NAMESPACE_LOCAL_SYM __localdep_stpcpy)(__dst, __p);
		}
		*__dst++ = '\0';
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__Getdays_defined
#define __local___localdep__Getdays_defined
#define __localdep__Getdays __LIBC_LOCAL_NAME(_Getdays)
#endif /* !__local___localdep__Getdays_defined */
#else /* __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign */
#undef __local__Getdays_defined
#endif /* !__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign */
#endif /* !__local__Getdays_defined */
