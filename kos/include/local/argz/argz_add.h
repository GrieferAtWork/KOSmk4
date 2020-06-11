/* HASH CRC-32:0x38fe94a6 */
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
#ifndef __local_argz_add_defined
#define __local_argz_add_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_argz_append) || defined(__CRT_HAVE___argz_create_sep) || defined(__CRT_HAVE_realloc)
__NAMESPACE_LOCAL_BEGIN
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
/* Dependency: argz_append from argz */
#ifndef __local___localdep_argz_append_defined
#define __local___localdep_argz_append_defined 1
#ifdef __CRT_HAVE_argz_append
/* Append `BUF', of length `BUF_LEN' to the argz vector in `PARGZ & PARGZ_LEN' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,__localdep_argz_append,(char **__restrict __pargz, __SIZE_TYPE__ *__restrict __pargz_len, char const *__restrict __buf, __SIZE_TYPE__ __buf_len),argz_append,(__pargz,__pargz_len,__buf,__buf_len))
#elif defined(__CRT_HAVE___argz_create_sep)
/* Append `BUF', of length `BUF_LEN' to the argz vector in `PARGZ & PARGZ_LEN' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,__localdep_argz_append,(char **__restrict __pargz, __SIZE_TYPE__ *__restrict __pargz_len, char const *__restrict __buf, __SIZE_TYPE__ __buf_len),__argz_create_sep,(__pargz,__pargz_len,__buf,__buf_len))
#elif defined(__CRT_HAVE_realloc)
__NAMESPACE_LOCAL_END
#include <local/argz/argz_append.h>
__NAMESPACE_LOCAL_BEGIN
/* Append `BUF', of length `BUF_LEN' to the argz vector in `PARGZ & PARGZ_LEN' */
#define __localdep_argz_append __LIBC_LOCAL_NAME(argz_append)
#else /* ... */
#undef __local___localdep_argz_append_defined
#endif /* !... */
#endif /* !__local___localdep_argz_append_defined */
/* Append `STR' to the argz vector in `PARGZ & PARGZ_LEN' */
__LOCAL_LIBC(argz_add) __ATTR_NONNULL((1, 2, 3)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(argz_add))(char **__restrict __pargz, __SIZE_TYPE__ *__restrict __pargz_len, char const *__restrict __str) {
	return __localdep_argz_append(__pargz, __pargz_len, __str, __localdep_strlen(__str) + 1);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_argz_add_defined
#define __local___localdep_argz_add_defined 1
#define __localdep_argz_add __LIBC_LOCAL_NAME(argz_add)
#endif /* !__local___localdep_argz_add_defined */
#else /* __CRT_HAVE_argz_append || __CRT_HAVE___argz_create_sep || __CRT_HAVE_realloc */
#undef __local_argz_add_defined
#endif /* !__CRT_HAVE_argz_append && !__CRT_HAVE___argz_create_sep && !__CRT_HAVE_realloc */
#endif /* !__local_argz_add_defined */
