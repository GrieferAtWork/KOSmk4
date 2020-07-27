/* HASH CRC-32:0xe174564f */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_envz_add_defined
#define __local_envz_add_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_realloc
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: argz_add from argz */
#ifndef __local___localdep_argz_add_defined
#define __local___localdep_argz_add_defined 1
#ifdef __CRT_HAVE_argz_add
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Append `STR' (including the trailing NUL-character) to the argz string in `PARGZ...+=PARGZ_LEN'
 * This is the same as `argz_append(pargz, pargz_len, str, strlen(str) + 1)'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__errno_t,__NOTHROW_NCX,__localdep_argz_add,(char **__restrict __pargz, __SIZE_TYPE__ *__restrict __pargz_len, char const *__restrict __str),argz_add,(__pargz,__pargz_len,__str))
#elif defined(__CRT_HAVE___argz_add)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Append `STR' (including the trailing NUL-character) to the argz string in `PARGZ...+=PARGZ_LEN'
 * This is the same as `argz_append(pargz, pargz_len, str, strlen(str) + 1)'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__errno_t,__NOTHROW_NCX,__localdep_argz_add,(char **__restrict __pargz, __SIZE_TYPE__ *__restrict __pargz_len, char const *__restrict __str),__argz_add,(__pargz,__pargz_len,__str))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/argz/argz_add.h>
__NAMESPACE_LOCAL_BEGIN
/* Append `STR' (including the trailing NUL-character) to the argz string in `PARGZ...+=PARGZ_LEN'
 * This is the same as `argz_append(pargz, pargz_len, str, strlen(str) + 1)'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
#define __localdep_argz_add __LIBC_LOCAL_NAME(argz_add)
#endif /* !... */
#endif /* !__local___localdep_argz_add_defined */
/* Dependency: envz_remove from envz */
#ifndef __local___localdep_envz_remove_defined
#define __local___localdep_envz_remove_defined 1
#ifdef __CRT_HAVE_envz_remove
/* Remove the entry for `NAME' from `ENVZ & ENVZ_LEN', if any */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 2, 3)),__NOTHROW_NCX,__localdep_envz_remove,(char **__restrict __penvz, __SIZE_TYPE__ *__restrict __penvz_len, char const *__restrict __name),envz_remove,(__penvz,__penvz_len,__name))
#else /* __CRT_HAVE_envz_remove */
__NAMESPACE_LOCAL_END
#include <local/envz/envz_remove.h>
__NAMESPACE_LOCAL_BEGIN
/* Remove the entry for `NAME' from `ENVZ & ENVZ_LEN', if any */
#define __localdep_envz_remove __LIBC_LOCAL_NAME(envz_remove)
#endif /* !__CRT_HAVE_envz_remove */
#endif /* !__local___localdep_envz_remove_defined */
/* Dependency: mempcpyc from string */
#ifndef __local___localdep_mempcpyc_defined
#define __local___localdep_mempcpyc_defined 1
#ifdef __CRT_HAVE_mempcpyc
/* Same as `memcpyc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),mempcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_mempcpyc */
__NAMESPACE_LOCAL_END
#include <local/string/mempcpyc.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `memcpyc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
#define __localdep_mempcpyc __LIBC_LOCAL_NAME(mempcpyc)
#endif /* !__CRT_HAVE_mempcpyc */
#endif /* !__local___localdep_mempcpyc_defined */
/* Dependency: realloc from stdlib */
#ifndef __local___localdep_realloc_defined
#define __local___localdep_realloc_defined 1
#if __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS)
__CEIREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,{ return __builtin_realloc(__mallptr, __num_bytes); })
#else /* __has_builtin(__builtin_realloc) && __LIBC_BIND_CRTBUILTINS */
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#endif /* !__has_builtin(__builtin_realloc) || !__LIBC_BIND_CRTBUILTINS */
#endif /* !__local___localdep_realloc_defined */
/* Dependency: strlen from string */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined 1
#ifdef __CRT_HAVE_strlen
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __string),strlen,(__string))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__NAMESPACE_LOCAL_END
#include <parts/errno.h>
__NAMESPACE_LOCAL_BEGIN
/* Adds an entry for `NAME' with value `VALUE' to `ENVZ & ENVZ_LEN'. If an entry
 * with the same name already exists in `ENVZ', it is removed. If `VALUE' is
 * `NULL', then the new entry will not have a value portion, meaning that `envz_get()'
 * will return `NULL', although `envz_entry()' will still return an entry. This is handy
 * because when merging with another envz, the null entry can override an
 * entry in the other one. Such entries can be removed with `envz_strip()' */
__LOCAL_LIBC(envz_add) __ATTR_NONNULL((1, 2, 3)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(envz_add))(char **__restrict __penvz, __SIZE_TYPE__ *__restrict __penvz_len, char const *__restrict __name, char const *__value) {
	char *__new_envz;
	__SIZE_TYPE__ __namelen, __valuelen, __morelen;
	__localdep_envz_remove(__penvz, __penvz_len, __name);
	if (!__value)
		return __localdep_argz_add(__penvz, __penvz_len, __name);
	/* Append a new string `name=value\0' */
	__namelen  = __localdep_strlen(__name);
	__valuelen = __localdep_strlen(__value);
	__morelen  = __namelen + 1 + __valuelen + 1;
	__new_envz = (char *)__localdep_realloc(*__penvz, (*__penvz_len + __morelen) * sizeof(char));
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
	__new_envz = (char *)__localdep_mempcpyc(__new_envz, __name, __namelen, sizeof(char));
	*__new_envz++ = '=';
	__new_envz = (char *)__localdep_mempcpyc(__new_envz, __value, __valuelen, sizeof(char));
	*__new_envz = '\0';
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_envz_add_defined
#define __local___localdep_envz_add_defined 1
#define __localdep_envz_add __LIBC_LOCAL_NAME(envz_add)
#endif /* !__local___localdep_envz_add_defined */
#else /* __CRT_HAVE_realloc */
#undef __local_envz_add_defined
#endif /* !__CRT_HAVE_realloc */
#endif /* !__local_envz_add_defined */
