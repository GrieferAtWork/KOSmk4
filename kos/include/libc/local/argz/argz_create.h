/* HASH CRC-32:0x59019545 */
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
#ifndef __local_argz_create_defined
#define __local_argz_create_defined
#include <__crt.h>
#if defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <bits/types.h>
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
#ifndef __local___localdep_stpcpy_defined
#define __local___localdep_stpcpy_defined
#if __has_builtin(__builtin_stpcpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_stpcpy)
__CEIREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),char *,__NOTHROW_NCX,__localdep_stpcpy,(char *__restrict __buf, char const *__restrict __src),stpcpy,{ return __builtin_stpcpy(__buf, __src); })
#elif defined(__CRT_HAVE_stpcpy)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),char *,__NOTHROW_NCX,__localdep_stpcpy,(char *__restrict __buf, char const *__restrict __src),stpcpy,(__buf,__src))
#elif defined(__CRT_HAVE___stpcpy)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),char *,__NOTHROW_NCX,__localdep_stpcpy,(char *__restrict __buf, char const *__restrict __src),__stpcpy,(__buf,__src))
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
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
#include <hybrid/__assert.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(argz_create) __ATTR_NONNULL((1, 2, 3)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(argz_create))(char *const ___argv[], char **__restrict __pargz, __SIZE_TYPE__ *__restrict __pargz_len) {
	__SIZE_TYPE__ __i, ___argc, __total_len = 0;
	for (___argc = 0; ___argv[___argc] != __NULLPTR; ++___argc)
		__total_len += (__NAMESPACE_LOCAL_SYM __localdep_strlen)(___argv[___argc]) + 1;
	if __unlikely(__total_len == 0) {
		*__pargz = __NULLPTR;
	} else {
		char *__argz_string;
		__argz_string = (char *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(__total_len * sizeof(char));
		if __unlikely(!__argz_string) {
			*__pargz = __NULLPTR;
			*__pargz_len  = 0;
#ifdef __ENOMEM
			return __ENOMEM;
#else /* __ENOMEM */
			return 1;
#endif /* !__ENOMEM */
		}
		*__pargz = __argz_string;
		for (__i = 0; __i < ___argc; ++__i) {
			__argz_string = (__NAMESPACE_LOCAL_SYM __localdep_stpcpy)(__argz_string, ___argv[___argc]) + 1;
		}
		__hybrid_assert(__argz_string == *__pargz + __total_len);
	}
	*__pargz_len = __total_len;
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_argz_create_defined
#define __local___localdep_argz_create_defined
#define __localdep_argz_create __LIBC_LOCAL_NAME(argz_create)
#endif /* !__local___localdep_argz_create_defined */
#else /* __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign */
#undef __local_argz_create_defined
#endif /* !__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign */
#endif /* !__local_argz_create_defined */
