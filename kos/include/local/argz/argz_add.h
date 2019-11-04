/* HASH CRC-32:0x189c72a6 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_argz_add_defined
#if defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_argz_append) || defined(__CRT_HAVE___argz_create_sep)
#define __local_argz_add_defined 1
/* Dependency: "argz_append" from "argz" */
#ifndef ____localdep_argz_append_defined
#define ____localdep_argz_append_defined 1
#if defined(__CRT_HAVE_argz_append)
/* Append `BUF', of length `BUF_LEN' to the argz vector in `PARGZ & PARGZ_LEN' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,__localdep_argz_append,(char **__restrict __pargz, __SIZE_TYPE__ *__restrict __pargz_len, char const *__restrict __buf, __SIZE_TYPE__ __buf_len),argz_append,(__pargz,__pargz_len,__buf,__buf_len))
#elif defined(__CRT_HAVE___argz_create_sep)
/* Append `BUF', of length `BUF_LEN' to the argz vector in `PARGZ & PARGZ_LEN' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,__localdep_argz_append,(char **__restrict __pargz, __SIZE_TYPE__ *__restrict __pargz_len, char const *__restrict __buf, __SIZE_TYPE__ __buf_len),__argz_create_sep,(__pargz,__pargz_len,__buf,__buf_len))
#elif defined(__CRT_HAVE_realloc)
#include <local/argz/argz_append.h>
/* Append `BUF', of length `BUF_LEN' to the argz vector in `PARGZ & PARGZ_LEN' */
#define __localdep_argz_append (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_append))
#else /* CUSTOM: argz_append */
#undef ____localdep_argz_append_defined
#endif /* argz_append... */
#endif /* !____localdep_argz_append_defined */

/* Dependency: "strlen" from "string" */
#ifndef ____localdep_strlen_defined
#define ____localdep_strlen_defined 1
#if defined(__CRT_HAVE_strlen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __string),strlen,(__string))
#else /* LIBC: strlen */
#include <local/string/strlen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_strlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlen))
#endif /* strlen... */
#endif /* !____localdep_strlen_defined */

__NAMESPACE_LOCAL_BEGIN
/* Append `STR' to the argz vector in `PARGZ & PARGZ_LEN' */
__LOCAL_LIBC(argz_add) __ATTR_NONNULL((1, 2, 3)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(argz_add))(char **__restrict __pargz,
                                                      __SIZE_TYPE__ *__restrict __pargz_len,
                                                      char const *__restrict __str) {
#line 270 "kos/src/libc/magic/argz.c"
	return __localdep_argz_append(__pargz, __pargz_len, __str, __localdep_strlen(__str) + 1);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_argz_append) || defined(__CRT_HAVE___argz_create_sep) */
#endif /* !__local_argz_add_defined */
