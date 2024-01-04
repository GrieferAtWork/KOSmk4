/* HASH CRC-32:0xbcb58fc7 */
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
#ifndef __local_envz_add_defined
#define __local_envz_add_defined
#include <__crt.h>
#if defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_argz_add_defined
#define __local___localdep_argz_add_defined
#ifdef __CRT_HAVE_argz_add
__CREDIRECT(__ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2),__errno_t,__NOTHROW_NCX,__localdep_argz_add,(char **__restrict __pargz, __SIZE_TYPE__ *__restrict __pargz_len, char const *__restrict __str),argz_add,(__pargz,__pargz_len,__str))
#elif defined(__CRT_HAVE___argz_add)
__CREDIRECT(__ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2),__errno_t,__NOTHROW_NCX,__localdep_argz_add,(char **__restrict __pargz, __SIZE_TYPE__ *__restrict __pargz_len, char const *__restrict __str),__argz_add,(__pargz,__pargz_len,__str))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/argz/argz_add.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_argz_add __LIBC_LOCAL_NAME(argz_add)
#endif /* !... */
#endif /* !__local___localdep_argz_add_defined */
#ifndef __local___localdep_envz_remove_defined
#define __local___localdep_envz_remove_defined
#ifdef __CRT_HAVE_envz_remove
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2),__NOTHROW_NCX,__localdep_envz_remove,(char **__restrict __penvz, __SIZE_TYPE__ *__restrict __penvz_len, char const *__restrict __name),envz_remove,(__penvz,__penvz_len,__name))
#else /* __CRT_HAVE_envz_remove */
__NAMESPACE_LOCAL_END
#include <libc/local/envz/envz_remove.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_envz_remove __LIBC_LOCAL_NAME(envz_remove)
#endif /* !__CRT_HAVE_envz_remove */
#endif /* !__local___localdep_envz_remove_defined */
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
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(envz_add) __ATTR_IN(3) __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_IN_OPT(4) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(envz_add))(char **__restrict __penvz, __SIZE_TYPE__ *__restrict __penvz_len, char const *__restrict __name, char const *___value) {
	char *__new_envz;
	__SIZE_TYPE__ __namelen, __valuelen, __morelen;
	(__NAMESPACE_LOCAL_SYM __localdep_envz_remove)(__penvz, __penvz_len, __name);
	if (!___value)
		return (__NAMESPACE_LOCAL_SYM __localdep_argz_add)(__penvz, __penvz_len, __name);
	/* Append a new string `name=value\0' */
	__namelen  = (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__name);
	__valuelen = (__NAMESPACE_LOCAL_SYM __localdep_strlen)(___value);
	__morelen  = __namelen + 1 + __valuelen + 1;
	__new_envz = (char *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(*__penvz, (*__penvz_len + __morelen) * sizeof(char));
	if __unlikely(!__new_envz) {
#ifdef __ENOMEM
		return __ENOMEM;
#else /* __ENOMEM */
		return 1;
#endif /* !__ENOMEM */
	}
	*__penvz = __new_envz;
	__new_envz += *__penvz_len;
	*__penvz_len += __morelen;
	__new_envz = (char *)(__NAMESPACE_LOCAL_SYM __localdep_mempcpyc)(__new_envz, __name, __namelen, sizeof(char));
	*__new_envz++ = '=';
	__new_envz = (char *)(__NAMESPACE_LOCAL_SYM __localdep_mempcpyc)(__new_envz, ___value, __valuelen, sizeof(char));
	*__new_envz = '\0';
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_envz_add_defined
#define __local___localdep_envz_add_defined
#define __localdep_envz_add __LIBC_LOCAL_NAME(envz_add)
#endif /* !__local___localdep_envz_add_defined */
#else /* __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc */
#undef __local_envz_add_defined
#endif /* !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc */
#endif /* !__local_envz_add_defined */
