/* HASH CRC-32:0x3e364025 */
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
#ifndef _ARGZ_H
#define _ARGZ_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>

/* Documentation is derived from GLibc: /usr/include/argz.h
 * Note that _ONLY_ the documentation was taken (and in places modified),
 * but the implementations were written from scratch, using GLibc's
 * implementation only as a reference (which also resulted in me discovering
 * some bugs in GLibc's version that I'm not going to report because at least
 * in my mind, these are just suuuuch _absolute_ beginner's mistakes...)
 * The function's that I've fixed are:
 *  - argz_add_sep()
 *  - argz_insert()
 * By the way: GLibc guys: If you want to copy my (fixed) implementation, that
 *                         is licensed under the ZLib license, so if one of you
 *                         comes across this, don't forget to include my copyright
 *                         notice when pasting ;)
 */
/* Routines for dealing with '\0' separated arg vectors.
   Copyright (C) 1995-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __error_t_defined
#define __error_t_defined 1
typedef __errno_t error_t;
#endif /* !__error_t_defined */

#ifdef __CRT_HAVE_argz_create
/* Make a '\0' separated arg vector from a unix argv vector, returning it in
 * `PARGZ', and the total length in `PLEN'. If a memory allocation error occurs,
 * `ENOMEM' is returned, otherwise `0'. The result can be destroyed using `free()' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,argz_create,(char *const ___argv[], char **__restrict __pargz, size_t *__restrict __pargz_len),(___argv,__pargz,__pargz_len))
#elif defined(__CRT_HAVE___argz_create)
/* Make a '\0' separated arg vector from a unix argv vector, returning it in
 * `PARGZ', and the total length in `PLEN'. If a memory allocation error occurs,
 * `ENOMEM' is returned, otherwise `0'. The result can be destroyed using `free()' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,argz_create,(char *const ___argv[], char **__restrict __pargz, size_t *__restrict __pargz_len),__argz_create,(___argv,__pargz,__pargz_len))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <local/argz/argz_create.h>
/* Make a '\0' separated arg vector from a unix argv vector, returning it in
 * `PARGZ', and the total length in `PLEN'. If a memory allocation error occurs,
 * `ENOMEM' is returned, otherwise `0'. The result can be destroyed using `free()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(argz_create, __FORCELOCAL __ATTR_NONNULL((1, 2, 3)) error_t __NOTHROW_NCX(__LIBCCALL argz_create)(char *const ___argv[], char **__restrict __pargz, size_t *__restrict __pargz_len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_create))(___argv, __pargz, __pargz_len); })
#endif /* ... */
#ifndef ____argz_create_defined
#define ____argz_create_defined 1
#ifdef __CRT_HAVE_argz_create
/* Make a '\0' separated arg vector from a unix argv vector, returning it in
 * `PARGZ', and the total length in `PLEN'. If a memory allocation error occurs,
 * `ENOMEM' is returned, otherwise `0'. The result can be destroyed using `free()' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,__argz_create,(char *const ___argv[], char **__restrict __pargz, size_t *__restrict __pargz_len),argz_create,(___argv,__pargz,__pargz_len))
#elif defined(__CRT_HAVE___argz_create)
/* Make a '\0' separated arg vector from a unix argv vector, returning it in
 * `PARGZ', and the total length in `PLEN'. If a memory allocation error occurs,
 * `ENOMEM' is returned, otherwise `0'. The result can be destroyed using `free()' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,__argz_create,(char *const ___argv[], char **__restrict __pargz, size_t *__restrict __pargz_len),(___argv,__pargz,__pargz_len))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <local/argz/argz_create.h>
/* Make a '\0' separated arg vector from a unix argv vector, returning it in
 * `PARGZ', and the total length in `PLEN'. If a memory allocation error occurs,
 * `ENOMEM' is returned, otherwise `0'. The result can be destroyed using `free()' */
__FORCELOCAL __ATTR_NONNULL((1, 2, 3)) error_t __NOTHROW_NCX(__LIBCCALL __argz_create)(char *const ___argv[], char **__restrict __pargz, size_t *__restrict __pargz_len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_create))(___argv, __pargz, __pargz_len); }
#else /* ... */
#undef ____argz_create_defined
#endif /* !... */
#endif /* !____argz_create_defined */
#ifdef __CRT_HAVE_argz_create_sep
/* Make a '\0' separated arg vector from a `SEP' separated list in
 * `STRING', returning it in `PARGZ', and the total length in `PLEN'.
 * If a memory allocation error occurs, `ENOMEM' is returned, otherwise `0'.
 * The result can be destroyed using `free()' */
__CDECLARE(__ATTR_NONNULL((1, 3, 4)),error_t,__NOTHROW_NCX,argz_create_sep,(char const *__restrict __string, int __sep, char **__restrict __pargz, size_t *__restrict __pargz_len),(__string,__sep,__pargz,__pargz_len))
#elif defined(__CRT_HAVE___argz_create_sep)
/* Make a '\0' separated arg vector from a `SEP' separated list in
 * `STRING', returning it in `PARGZ', and the total length in `PLEN'.
 * If a memory allocation error occurs, `ENOMEM' is returned, otherwise `0'.
 * The result can be destroyed using `free()' */
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),error_t,__NOTHROW_NCX,argz_create_sep,(char const *__restrict __string, int __sep, char **__restrict __pargz, size_t *__restrict __pargz_len),__argz_create_sep,(__string,__sep,__pargz,__pargz_len))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree))
#include <local/argz/argz_create_sep.h>
/* Make a '\0' separated arg vector from a `SEP' separated list in
 * `STRING', returning it in `PARGZ', and the total length in `PLEN'.
 * If a memory allocation error occurs, `ENOMEM' is returned, otherwise `0'.
 * The result can be destroyed using `free()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(argz_create_sep, __FORCELOCAL __ATTR_NONNULL((1, 3, 4)) error_t __NOTHROW_NCX(__LIBCCALL argz_create_sep)(char const *__restrict __string, int __sep, char **__restrict __pargz, size_t *__restrict __pargz_len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_create_sep))(__string, __sep, __pargz, __pargz_len); })
#endif /* ... */
#ifndef ____argz_create_sep_defined
#define ____argz_create_sep_defined 1
#ifdef __CRT_HAVE_argz_create_sep
/* Make a '\0' separated arg vector from a `SEP' separated list in
 * `STRING', returning it in `PARGZ', and the total length in `PLEN'.
 * If a memory allocation error occurs, `ENOMEM' is returned, otherwise `0'.
 * The result can be destroyed using `free()' */
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),error_t,__NOTHROW_NCX,__argz_create_sep,(char const *__restrict __string, int __sep, char **__restrict __pargz, size_t *__restrict __pargz_len),argz_create_sep,(__string,__sep,__pargz,__pargz_len))
#elif defined(__CRT_HAVE___argz_create_sep)
/* Make a '\0' separated arg vector from a `SEP' separated list in
 * `STRING', returning it in `PARGZ', and the total length in `PLEN'.
 * If a memory allocation error occurs, `ENOMEM' is returned, otherwise `0'.
 * The result can be destroyed using `free()' */
__CDECLARE(__ATTR_NONNULL((1, 3, 4)),error_t,__NOTHROW_NCX,__argz_create_sep,(char const *__restrict __string, int __sep, char **__restrict __pargz, size_t *__restrict __pargz_len),(__string,__sep,__pargz,__pargz_len))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree))
#include <local/argz/argz_create_sep.h>
/* Make a '\0' separated arg vector from a `SEP' separated list in
 * `STRING', returning it in `PARGZ', and the total length in `PLEN'.
 * If a memory allocation error occurs, `ENOMEM' is returned, otherwise `0'.
 * The result can be destroyed using `free()' */
__FORCELOCAL __ATTR_NONNULL((1, 3, 4)) error_t __NOTHROW_NCX(__LIBCCALL __argz_create_sep)(char const *__restrict __string, int __sep, char **__restrict __pargz, size_t *__restrict __pargz_len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_create_sep))(__string, __sep, __pargz, __pargz_len); }
#else /* ... */
#undef ____argz_create_sep_defined
#endif /* !... */
#endif /* !____argz_create_sep_defined */
#ifdef __CRT_HAVE_argz_count
/* Returns the number of strings in `ARGZ'
 * Simply count the number of`NUL-characters within `argz...+=argz_len' */
__CDECLARE(__ATTR_PURE,size_t,__NOTHROW_NCX,argz_count,(char const *__argz, size_t __argz_len),(__argz,__argz_len))
#elif defined(__CRT_HAVE___argz_count)
/* Returns the number of strings in `ARGZ'
 * Simply count the number of`NUL-characters within `argz...+=argz_len' */
__CREDIRECT(__ATTR_PURE,size_t,__NOTHROW_NCX,argz_count,(char const *__argz, size_t __argz_len),__argz_count,(__argz,__argz_len))
#else /* ... */
#include <local/argz/argz_count.h>
/* Returns the number of strings in `ARGZ'
 * Simply count the number of`NUL-characters within `argz...+=argz_len' */
__NAMESPACE_LOCAL_USING_OR_IMPL(argz_count, __FORCELOCAL __ATTR_PURE size_t __NOTHROW_NCX(__LIBCCALL argz_count)(char const *__argz, size_t __argz_len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_count))(__argz, __argz_len); })
#endif /* !... */
#ifndef ____argz_count_defined
#define ____argz_count_defined 1
#ifdef __CRT_HAVE_argz_count
/* Returns the number of strings in `ARGZ'
 * Simply count the number of`NUL-characters within `argz...+=argz_len' */
__CREDIRECT(__ATTR_PURE,size_t,__NOTHROW_NCX,__argz_count,(char const *__argz, size_t __argz_len),argz_count,(__argz,__argz_len))
#elif defined(__CRT_HAVE___argz_count)
/* Returns the number of strings in `ARGZ'
 * Simply count the number of`NUL-characters within `argz...+=argz_len' */
__CDECLARE(__ATTR_PURE,size_t,__NOTHROW_NCX,__argz_count,(char const *__argz, size_t __argz_len),(__argz,__argz_len))
#else /* ... */
#include <local/argz/argz_count.h>
/* Returns the number of strings in `ARGZ'
 * Simply count the number of`NUL-characters within `argz...+=argz_len' */
__FORCELOCAL __ATTR_PURE size_t __NOTHROW_NCX(__LIBCCALL __argz_count)(char const *__argz, size_t __argz_len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_count))(__argz, __argz_len); }
#endif /* !... */
#endif /* !____argz_count_defined */
#ifdef __CRT_HAVE_argz_extract
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ARGZ_H_PROTO)
extern "C++" {
/* Puts pointers to each string in `ARGZ' into `ARGV', which must be large enough
 * to hold them all (aka: have space for at least `argz_count()' elements) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,argz_extract,(char *__restrict __argz, size_t __argz_len, char **__restrict ___argv),argz_extract,(__argz,__argz_len,___argv))
/* Puts pointers to each string in `ARGZ' into `ARGV', which must be large enough
 * to hold them all (aka: have space for at least `argz_count()' elements) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,argz_extract,(char const *__restrict __argz, size_t __argz_len, char const **__restrict ___argv),argz_extract,(__argz,__argz_len,___argv))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ARGZ_H_PROTO */
/* Puts pointers to each string in `ARGZ' into `ARGV', which must be large enough
 * to hold them all (aka: have space for at least `argz_count()' elements) */
__CDECLARE_VOID(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,argz_extract,(char const *__restrict __argz, size_t __argz_len, char **__restrict ___argv),(__argz,__argz_len,___argv))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ARGZ_H_PROTO */
#elif defined(__CRT_HAVE___argz_extract)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ARGZ_H_PROTO)
extern "C++" {
/* Puts pointers to each string in `ARGZ' into `ARGV', which must be large enough
 * to hold them all (aka: have space for at least `argz_count()' elements) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,argz_extract,(char *__restrict __argz, size_t __argz_len, char **__restrict ___argv),__argz_extract,(__argz,__argz_len,___argv))
/* Puts pointers to each string in `ARGZ' into `ARGV', which must be large enough
 * to hold them all (aka: have space for at least `argz_count()' elements) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,argz_extract,(char const *__restrict __argz, size_t __argz_len, char const **__restrict ___argv),__argz_extract,(__argz,__argz_len,___argv))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ARGZ_H_PROTO */
/* Puts pointers to each string in `ARGZ' into `ARGV', which must be large enough
 * to hold them all (aka: have space for at least `argz_count()' elements) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,argz_extract,(char const *__restrict __argz, size_t __argz_len, char **__restrict ___argv),__argz_extract,(__argz,__argz_len,___argv))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ARGZ_H_PROTO */
#else /* ... */
#include <local/argz/argz_extract.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ARGZ_H_PROTO)
extern "C++" {
/* Puts pointers to each string in `ARGZ' into `ARGV', which must be large enough
 * to hold them all (aka: have space for at least `argz_count()' elements) */
__FORCELOCAL __ATTR_NONNULL((1, 3)) void __NOTHROW_NCX(__LIBCCALL argz_extract)(char *__restrict __argz, size_t __argz_len, char **__restrict ___argv) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_extract))(__argz, __argz_len, ___argv); }
/* Puts pointers to each string in `ARGZ' into `ARGV', which must be large enough
 * to hold them all (aka: have space for at least `argz_count()' elements) */
__FORCELOCAL __ATTR_NONNULL((1, 3)) void __NOTHROW_NCX(__LIBCCALL argz_extract)(char const *__restrict __argz, size_t __argz_len, char const **__restrict ___argv) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_extract))(__argz, __argz_len, (char **)___argv); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ARGZ_H_PROTO */
/* Puts pointers to each string in `ARGZ' into `ARGV', which must be large enough
 * to hold them all (aka: have space for at least `argz_count()' elements) */
__NAMESPACE_LOCAL_USING_OR_IMPL(argz_extract, __FORCELOCAL __ATTR_NONNULL((1, 3)) void __NOTHROW_NCX(__LIBCCALL argz_extract)(char const *__restrict __argz, size_t __argz_len, char **__restrict ___argv) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_extract))(__argz, __argz_len, ___argv); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ARGZ_H_PROTO */
#endif /* !... */
#ifndef ____argz_extract_defined
#define ____argz_extract_defined 1
#ifdef __CRT_HAVE_argz_extract
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ARGZ_H_PROTO)
extern "C++" {
/* Puts pointers to each string in `ARGZ' into `ARGV', which must be large enough
 * to hold them all (aka: have space for at least `argz_count()' elements) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,__argz_extract,(char *__restrict __argz, size_t __argz_len, char **__restrict ___argv),argz_extract,(__argz,__argz_len,___argv))
/* Puts pointers to each string in `ARGZ' into `ARGV', which must be large enough
 * to hold them all (aka: have space for at least `argz_count()' elements) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,__argz_extract,(char const *__restrict __argz, size_t __argz_len, char const **__restrict ___argv),argz_extract,(__argz,__argz_len,___argv))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ARGZ_H_PROTO */
/* Puts pointers to each string in `ARGZ' into `ARGV', which must be large enough
 * to hold them all (aka: have space for at least `argz_count()' elements) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,__argz_extract,(char const *__restrict __argz, size_t __argz_len, char **__restrict ___argv),argz_extract,(__argz,__argz_len,___argv))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ARGZ_H_PROTO */
#elif defined(__CRT_HAVE___argz_extract)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ARGZ_H_PROTO)
extern "C++" {
/* Puts pointers to each string in `ARGZ' into `ARGV', which must be large enough
 * to hold them all (aka: have space for at least `argz_count()' elements) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,__argz_extract,(char *__restrict __argz, size_t __argz_len, char **__restrict ___argv),__argz_extract,(__argz,__argz_len,___argv))
/* Puts pointers to each string in `ARGZ' into `ARGV', which must be large enough
 * to hold them all (aka: have space for at least `argz_count()' elements) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,__argz_extract,(char const *__restrict __argz, size_t __argz_len, char const **__restrict ___argv),__argz_extract,(__argz,__argz_len,___argv))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ARGZ_H_PROTO */
/* Puts pointers to each string in `ARGZ' into `ARGV', which must be large enough
 * to hold them all (aka: have space for at least `argz_count()' elements) */
__CDECLARE_VOID(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,__argz_extract,(char const *__restrict __argz, size_t __argz_len, char **__restrict ___argv),(__argz,__argz_len,___argv))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ARGZ_H_PROTO */
#else /* ... */
#include <local/argz/argz_extract.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ARGZ_H_PROTO)
extern "C++" {
/* Puts pointers to each string in `ARGZ' into `ARGV', which must be large enough
 * to hold them all (aka: have space for at least `argz_count()' elements) */
__FORCELOCAL __ATTR_NONNULL((1, 3)) void __NOTHROW_NCX(__LIBCCALL __argz_extract)(char *__restrict __argz, size_t __argz_len, char **__restrict ___argv) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_extract))(__argz, __argz_len, ___argv); }
/* Puts pointers to each string in `ARGZ' into `ARGV', which must be large enough
 * to hold them all (aka: have space for at least `argz_count()' elements) */
__FORCELOCAL __ATTR_NONNULL((1, 3)) void __NOTHROW_NCX(__LIBCCALL __argz_extract)(char const *__restrict __argz, size_t __argz_len, char const **__restrict ___argv) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_extract))(__argz, __argz_len, (char **)___argv); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ARGZ_H_PROTO */
/* Puts pointers to each string in `ARGZ' into `ARGV', which must be large enough
 * to hold them all (aka: have space for at least `argz_count()' elements) */
__FORCELOCAL __ATTR_NONNULL((1, 3)) void __NOTHROW_NCX(__LIBCCALL __argz_extract)(char const *__restrict __argz, size_t __argz_len, char **__restrict ___argv) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_extract))(__argz, __argz_len, ___argv); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ARGZ_H_PROTO */
#endif /* !... */
#endif /* !____argz_extract_defined */
#ifdef __CRT_HAVE_argz_stringify
/* Make '\0' separated arg vector `ARGZ' printable by converting
 * all the '\0's except the last into the character `SEP' */
__CDECLARE_VOID(,__NOTHROW_NCX,argz_stringify,(char *__argz, size_t __len, int __sep),(__argz,__len,__sep))
#elif defined(__CRT_HAVE___argz_stringify)
/* Make '\0' separated arg vector `ARGZ' printable by converting
 * all the '\0's except the last into the character `SEP' */
__CREDIRECT_VOID(,__NOTHROW_NCX,argz_stringify,(char *__argz, size_t __len, int __sep),__argz_stringify,(__argz,__len,__sep))
#else /* ... */
#include <local/argz/argz_stringify.h>
/* Make '\0' separated arg vector `ARGZ' printable by converting
 * all the '\0's except the last into the character `SEP' */
__NAMESPACE_LOCAL_USING_OR_IMPL(argz_stringify, __FORCELOCAL void __NOTHROW_NCX(__LIBCCALL argz_stringify)(char *__argz, size_t __len, int __sep) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_stringify))(__argz, __len, __sep); })
#endif /* !... */
#ifndef ____argz_stringify_defined
#define ____argz_stringify_defined 1
#ifdef __CRT_HAVE_argz_stringify
/* Make '\0' separated arg vector `ARGZ' printable by converting
 * all the '\0's except the last into the character `SEP' */
__CREDIRECT_VOID(,__NOTHROW_NCX,__argz_stringify,(char *__argz, size_t __len, int __sep),argz_stringify,(__argz,__len,__sep))
#elif defined(__CRT_HAVE___argz_stringify)
/* Make '\0' separated arg vector `ARGZ' printable by converting
 * all the '\0's except the last into the character `SEP' */
__CDECLARE_VOID(,__NOTHROW_NCX,__argz_stringify,(char *__argz, size_t __len, int __sep),(__argz,__len,__sep))
#else /* ... */
#include <local/argz/argz_stringify.h>
/* Make '\0' separated arg vector `ARGZ' printable by converting
 * all the '\0's except the last into the character `SEP' */
__FORCELOCAL void __NOTHROW_NCX(__LIBCCALL __argz_stringify)(char *__argz, size_t __len, int __sep) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_stringify))(__argz, __len, __sep); }
#endif /* !... */
#endif /* !____argz_stringify_defined */
#ifdef __CRT_HAVE_argz_append
/* Append `BUF', of length `BUF_LEN' to the argz vector in `PARGZ & PARGZ_LEN' */
__CDECLARE(__ATTR_NONNULL((1, 2)),error_t,__NOTHROW_NCX,argz_append,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __buf, size_t __buf_len),(__pargz,__pargz_len,__buf,__buf_len))
#elif defined(__CRT_HAVE___argz_create_sep)
/* Append `BUF', of length `BUF_LEN' to the argz vector in `PARGZ & PARGZ_LEN' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),error_t,__NOTHROW_NCX,argz_append,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __buf, size_t __buf_len),__argz_create_sep,(__pargz,__pargz_len,__buf,__buf_len))
#elif defined(__CRT_HAVE_realloc)
#include <local/argz/argz_append.h>
/* Append `BUF', of length `BUF_LEN' to the argz vector in `PARGZ & PARGZ_LEN' */
__NAMESPACE_LOCAL_USING_OR_IMPL(argz_append, __FORCELOCAL __ATTR_NONNULL((1, 2)) error_t __NOTHROW_NCX(__LIBCCALL argz_append)(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __buf, size_t __buf_len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_append))(__pargz, __pargz_len, __buf, __buf_len); })
#endif /* ... */
#ifndef ____argz_append_defined
#define ____argz_append_defined 1
#ifdef __CRT_HAVE_argz_append
/* Append `BUF', of length `BUF_LEN' to the argz vector in `PARGZ & PARGZ_LEN' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),error_t,__NOTHROW_NCX,__argz_append,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __buf, size_t __buf_len),argz_append,(__pargz,__pargz_len,__buf,__buf_len))
#elif defined(__CRT_HAVE___argz_create_sep)
/* Append `BUF', of length `BUF_LEN' to the argz vector in `PARGZ & PARGZ_LEN' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),error_t,__NOTHROW_NCX,__argz_append,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __buf, size_t __buf_len),__argz_create_sep,(__pargz,__pargz_len,__buf,__buf_len))
#elif defined(__CRT_HAVE_realloc)
#include <local/argz/argz_append.h>
/* Append `BUF', of length `BUF_LEN' to the argz vector in `PARGZ & PARGZ_LEN' */
__FORCELOCAL __ATTR_NONNULL((1, 2)) error_t __NOTHROW_NCX(__LIBCCALL __argz_append)(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __buf, size_t __buf_len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_append))(__pargz, __pargz_len, __buf, __buf_len); }
#else /* ... */
#undef ____argz_append_defined
#endif /* !... */
#endif /* !____argz_append_defined */
#ifdef __CRT_HAVE_argz_add
/* Append `STR' to the argz vector in `PARGZ & PARGZ_LEN' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,argz_add,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __str),(__pargz,__pargz_len,__str))
#elif defined(__CRT_HAVE___argz_add)
/* Append `STR' to the argz vector in `PARGZ & PARGZ_LEN' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,argz_add,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __str),__argz_add,(__pargz,__pargz_len,__str))
#elif defined(__CRT_HAVE_argz_append) || defined(__CRT_HAVE___argz_create_sep) || defined(__CRT_HAVE_realloc)
#include <local/argz/argz_add.h>
/* Append `STR' to the argz vector in `PARGZ & PARGZ_LEN' */
__NAMESPACE_LOCAL_USING_OR_IMPL(argz_add, __FORCELOCAL __ATTR_NONNULL((1, 2, 3)) error_t __NOTHROW_NCX(__LIBCCALL argz_add)(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_add))(__pargz, __pargz_len, __str); })
#endif /* ... */
#ifndef ____argz_add_defined
#define ____argz_add_defined 1
#ifdef __CRT_HAVE_argz_add
/* Append `STR' to the argz vector in `PARGZ & PARGZ_LEN' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,__argz_add,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __str),argz_add,(__pargz,__pargz_len,__str))
#elif defined(__CRT_HAVE___argz_add)
/* Append `STR' to the argz vector in `PARGZ & PARGZ_LEN' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,__argz_add,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __str),(__pargz,__pargz_len,__str))
#elif defined(__CRT_HAVE_argz_append) || defined(__CRT_HAVE___argz_create_sep) || defined(__CRT_HAVE_realloc)
#include <local/argz/argz_add.h>
/* Append `STR' to the argz vector in `PARGZ & PARGZ_LEN' */
__FORCELOCAL __ATTR_NONNULL((1, 2, 3)) error_t __NOTHROW_NCX(__LIBCCALL __argz_add)(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_add))(__pargz, __pargz_len, __str); }
#else /* ... */
#undef ____argz_add_defined
#endif /* !... */
#endif /* !____argz_add_defined */
#ifdef __CRT_HAVE_argz_add_sep
/* Append `SEP' separated list in `STRING' to the argz vector in `PARGZ & PARGZ_LEN' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,argz_add_sep,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __string, int __sep),(__pargz,__pargz_len,__string,__sep))
#elif defined(__CRT_HAVE___argz_add_sep)
/* Append `SEP' separated list in `STRING' to the argz vector in `PARGZ & PARGZ_LEN' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,argz_add_sep,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __string, int __sep),__argz_add_sep,(__pargz,__pargz_len,__string,__sep))
#elif defined(__CRT_HAVE_realloc)
#include <local/argz/argz_add_sep.h>
/* Append `SEP' separated list in `STRING' to the argz vector in `PARGZ & PARGZ_LEN' */
__NAMESPACE_LOCAL_USING_OR_IMPL(argz_add_sep, __FORCELOCAL __ATTR_NONNULL((1, 2, 3)) error_t __NOTHROW_NCX(__LIBCCALL argz_add_sep)(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __string, int __sep) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_add_sep))(__pargz, __pargz_len, __string, __sep); })
#endif /* ... */
#ifndef ____argz_add_sep_defined
#define ____argz_add_sep_defined 1
#ifdef __CRT_HAVE_argz_add_sep
/* Append `SEP' separated list in `STRING' to the argz vector in `PARGZ & PARGZ_LEN' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,__argz_add_sep,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __string, int __sep),argz_add_sep,(__pargz,__pargz_len,__string,__sep))
#elif defined(__CRT_HAVE___argz_add_sep)
/* Append `SEP' separated list in `STRING' to the argz vector in `PARGZ & PARGZ_LEN' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,__argz_add_sep,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __string, int __sep),(__pargz,__pargz_len,__string,__sep))
#elif defined(__CRT_HAVE_realloc)
#include <local/argz/argz_add_sep.h>
/* Append `SEP' separated list in `STRING' to the argz vector in `PARGZ & PARGZ_LEN' */
__FORCELOCAL __ATTR_NONNULL((1, 2, 3)) error_t __NOTHROW_NCX(__LIBCCALL __argz_add_sep)(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __string, int __sep) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_add_sep))(__pargz, __pargz_len, __string, __sep); }
#else /* ... */
#undef ____argz_add_sep_defined
#endif /* !... */
#endif /* !____argz_add_sep_defined */
#ifdef __CRT_HAVE_argz_delete
/* Delete `ENTRY' from `PARGZ & PARGZ_LEN', if it appears there
 * Note that `ENTRY' must be the actual pointer to one of the elements
 * of the given `PARGZ & PARGZ_LEN', and not just a string equal to one
 * of the elements... (took me a while to realize this one) */
__CDECLARE_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,argz_delete,(char **__restrict __pargz, size_t *__restrict __pargz_len, char *__entry),(__pargz,__pargz_len,__entry))
#elif defined(__CRT_HAVE___argz_add_sep)
/* Delete `ENTRY' from `PARGZ & PARGZ_LEN', if it appears there
 * Note that `ENTRY' must be the actual pointer to one of the elements
 * of the given `PARGZ & PARGZ_LEN', and not just a string equal to one
 * of the elements... (took me a while to realize this one) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,argz_delete,(char **__restrict __pargz, size_t *__restrict __pargz_len, char *__entry),__argz_add_sep,(__pargz,__pargz_len,__entry))
#else /* ... */
#include <local/argz/argz_delete.h>
/* Delete `ENTRY' from `PARGZ & PARGZ_LEN', if it appears there
 * Note that `ENTRY' must be the actual pointer to one of the elements
 * of the given `PARGZ & PARGZ_LEN', and not just a string equal to one
 * of the elements... (took me a while to realize this one) */
__NAMESPACE_LOCAL_USING_OR_IMPL(argz_delete, __FORCELOCAL __ATTR_NONNULL((1, 2)) void __NOTHROW_NCX(__LIBCCALL argz_delete)(char **__restrict __pargz, size_t *__restrict __pargz_len, char *__entry) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_delete))(__pargz, __pargz_len, __entry); })
#endif /* !... */
#ifndef ____argz_delete_defined
#define ____argz_delete_defined 1
#ifdef __CRT_HAVE_argz_delete
/* Delete `ENTRY' from `PARGZ & PARGZ_LEN', if it appears there
 * Note that `ENTRY' must be the actual pointer to one of the elements
 * of the given `PARGZ & PARGZ_LEN', and not just a string equal to one
 * of the elements... (took me a while to realize this one) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,__argz_delete,(char **__restrict __pargz, size_t *__restrict __pargz_len, char *__entry),argz_delete,(__pargz,__pargz_len,__entry))
#elif defined(__CRT_HAVE___argz_add_sep)
/* Delete `ENTRY' from `PARGZ & PARGZ_LEN', if it appears there
 * Note that `ENTRY' must be the actual pointer to one of the elements
 * of the given `PARGZ & PARGZ_LEN', and not just a string equal to one
 * of the elements... (took me a while to realize this one) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,__argz_delete,(char **__restrict __pargz, size_t *__restrict __pargz_len, char *__entry),__argz_add_sep,(__pargz,__pargz_len,__entry))
#else /* ... */
#include <local/argz/argz_delete.h>
/* Delete `ENTRY' from `PARGZ & PARGZ_LEN', if it appears there
 * Note that `ENTRY' must be the actual pointer to one of the elements
 * of the given `PARGZ & PARGZ_LEN', and not just a string equal to one
 * of the elements... (took me a while to realize this one) */
__FORCELOCAL __ATTR_NONNULL((1, 2)) void __NOTHROW_NCX(__LIBCCALL __argz_delete)(char **__restrict __pargz, size_t *__restrict __pargz_len, char *__entry) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_delete))(__pargz, __pargz_len, __entry); }
#endif /* !... */
#endif /* !____argz_delete_defined */
#ifdef __CRT_HAVE_argz_insert
/* Insert `ENTRY' into `ARGZ & ARGZ_LEN' before `BEFORE', which should be an
 * existing entry in `ARGZ'; if `BEFORE' is `NULL', `ENTRY' is appended to the end.
 * Since `ARGZ's first entry is the same as `ARGZ', `argz_insert(ARGZ, ARGZ_LEN, ARGZ, ENTRY)'
 * will insert `ENTRY' at the beginning of `ARGZ'. If `BEFORE' is not in `ARGZ', `EINVAL'
 * is returned, else if memory can't be allocated for the new `ARGZ', `ENOMEM' is returned.
 * On success, `0' is returned */
__CDECLARE(__ATTR_NONNULL((1, 2, 4)),error_t,__NOTHROW_NCX,argz_insert,(char **__restrict __pargz, size_t *__restrict __pargz_len, char *__before, char const *__restrict __entry),(__pargz,__pargz_len,__before,__entry))
#elif defined(__CRT_HAVE___argz_insert)
/* Insert `ENTRY' into `ARGZ & ARGZ_LEN' before `BEFORE', which should be an
 * existing entry in `ARGZ'; if `BEFORE' is `NULL', `ENTRY' is appended to the end.
 * Since `ARGZ's first entry is the same as `ARGZ', `argz_insert(ARGZ, ARGZ_LEN, ARGZ, ENTRY)'
 * will insert `ENTRY' at the beginning of `ARGZ'. If `BEFORE' is not in `ARGZ', `EINVAL'
 * is returned, else if memory can't be allocated for the new `ARGZ', `ENOMEM' is returned.
 * On success, `0' is returned */
__CREDIRECT(__ATTR_NONNULL((1, 2, 4)),error_t,__NOTHROW_NCX,argz_insert,(char **__restrict __pargz, size_t *__restrict __pargz_len, char *__before, char const *__restrict __entry),__argz_insert,(__pargz,__pargz_len,__before,__entry))
#elif defined(__CRT_HAVE_realloc)
#include <local/argz/argz_insert.h>
/* Insert `ENTRY' into `ARGZ & ARGZ_LEN' before `BEFORE', which should be an
 * existing entry in `ARGZ'; if `BEFORE' is `NULL', `ENTRY' is appended to the end.
 * Since `ARGZ's first entry is the same as `ARGZ', `argz_insert(ARGZ, ARGZ_LEN, ARGZ, ENTRY)'
 * will insert `ENTRY' at the beginning of `ARGZ'. If `BEFORE' is not in `ARGZ', `EINVAL'
 * is returned, else if memory can't be allocated for the new `ARGZ', `ENOMEM' is returned.
 * On success, `0' is returned */
__NAMESPACE_LOCAL_USING_OR_IMPL(argz_insert, __FORCELOCAL __ATTR_NONNULL((1, 2, 4)) error_t __NOTHROW_NCX(__LIBCCALL argz_insert)(char **__restrict __pargz, size_t *__restrict __pargz_len, char *__before, char const *__restrict __entry) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_insert))(__pargz, __pargz_len, __before, __entry); })
#endif /* ... */
#ifndef ____argz_insert_defined
#define ____argz_insert_defined 1
#ifdef __CRT_HAVE_argz_insert
/* Insert `ENTRY' into `ARGZ & ARGZ_LEN' before `BEFORE', which should be an
 * existing entry in `ARGZ'; if `BEFORE' is `NULL', `ENTRY' is appended to the end.
 * Since `ARGZ's first entry is the same as `ARGZ', `argz_insert(ARGZ, ARGZ_LEN, ARGZ, ENTRY)'
 * will insert `ENTRY' at the beginning of `ARGZ'. If `BEFORE' is not in `ARGZ', `EINVAL'
 * is returned, else if memory can't be allocated for the new `ARGZ', `ENOMEM' is returned.
 * On success, `0' is returned */
__CREDIRECT(__ATTR_NONNULL((1, 2, 4)),error_t,__NOTHROW_NCX,__argz_insert,(char **__restrict __pargz, size_t *__restrict __pargz_len, char *__before, char const *__restrict __entry),argz_insert,(__pargz,__pargz_len,__before,__entry))
#elif defined(__CRT_HAVE___argz_insert)
/* Insert `ENTRY' into `ARGZ & ARGZ_LEN' before `BEFORE', which should be an
 * existing entry in `ARGZ'; if `BEFORE' is `NULL', `ENTRY' is appended to the end.
 * Since `ARGZ's first entry is the same as `ARGZ', `argz_insert(ARGZ, ARGZ_LEN, ARGZ, ENTRY)'
 * will insert `ENTRY' at the beginning of `ARGZ'. If `BEFORE' is not in `ARGZ', `EINVAL'
 * is returned, else if memory can't be allocated for the new `ARGZ', `ENOMEM' is returned.
 * On success, `0' is returned */
__CDECLARE(__ATTR_NONNULL((1, 2, 4)),error_t,__NOTHROW_NCX,__argz_insert,(char **__restrict __pargz, size_t *__restrict __pargz_len, char *__before, char const *__restrict __entry),(__pargz,__pargz_len,__before,__entry))
#elif defined(__CRT_HAVE_realloc)
#include <local/argz/argz_insert.h>
/* Insert `ENTRY' into `ARGZ & ARGZ_LEN' before `BEFORE', which should be an
 * existing entry in `ARGZ'; if `BEFORE' is `NULL', `ENTRY' is appended to the end.
 * Since `ARGZ's first entry is the same as `ARGZ', `argz_insert(ARGZ, ARGZ_LEN, ARGZ, ENTRY)'
 * will insert `ENTRY' at the beginning of `ARGZ'. If `BEFORE' is not in `ARGZ', `EINVAL'
 * is returned, else if memory can't be allocated for the new `ARGZ', `ENOMEM' is returned.
 * On success, `0' is returned */
__FORCELOCAL __ATTR_NONNULL((1, 2, 4)) error_t __NOTHROW_NCX(__LIBCCALL __argz_insert)(char **__restrict __pargz, size_t *__restrict __pargz_len, char *__before, char const *__restrict __entry) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_insert))(__pargz, __pargz_len, __before, __entry); }
#else /* ... */
#undef ____argz_insert_defined
#endif /* !... */
#endif /* !____argz_insert_defined */
#ifdef __CRT_HAVE_argz_replace
/* Replace any occurrences of the string `STR' in `PARGZ' with `WITH', reallocating
 * `PARGZ' as necessary. If `PREPLACE_COUNT' is non-NULL, `*PREPLACE_COUNT' will be
 * incremented by number of replacements performed */
__CDECLARE(__ATTR_NONNULL((1, 2, 4)),error_t,__NOTHROW_NCX,argz_replace,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __str, char const *__restrict __with, unsigned int *__restrict __replace_count),(__pargz,__pargz_len,__str,__with,__replace_count))
#elif defined(__CRT_HAVE___argz_replace)
/* Replace any occurrences of the string `STR' in `PARGZ' with `WITH', reallocating
 * `PARGZ' as necessary. If `PREPLACE_COUNT' is non-NULL, `*PREPLACE_COUNT' will be
 * incremented by number of replacements performed */
__CREDIRECT(__ATTR_NONNULL((1, 2, 4)),error_t,__NOTHROW_NCX,argz_replace,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __str, char const *__restrict __with, unsigned int *__restrict __replace_count),__argz_replace,(__pargz,__pargz_len,__str,__with,__replace_count))
#elif defined(__CRT_HAVE_realloc) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree))
#include <local/argz/argz_replace.h>
/* Replace any occurrences of the string `STR' in `PARGZ' with `WITH', reallocating
 * `PARGZ' as necessary. If `PREPLACE_COUNT' is non-NULL, `*PREPLACE_COUNT' will be
 * incremented by number of replacements performed */
__NAMESPACE_LOCAL_USING_OR_IMPL(argz_replace, __FORCELOCAL __ATTR_NONNULL((1, 2, 4)) error_t __NOTHROW_NCX(__LIBCCALL argz_replace)(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __str, char const *__restrict __with, unsigned int *__restrict __replace_count) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_replace))(__pargz, __pargz_len, __str, __with, __replace_count); })
#endif /* ... */
#ifndef ____argz_replace_defined
#define ____argz_replace_defined 1
#ifdef __CRT_HAVE_argz_replace
/* Replace any occurrences of the string `STR' in `PARGZ' with `WITH', reallocating
 * `PARGZ' as necessary. If `PREPLACE_COUNT' is non-NULL, `*PREPLACE_COUNT' will be
 * incremented by number of replacements performed */
__CREDIRECT(__ATTR_NONNULL((1, 2, 4)),error_t,__NOTHROW_NCX,__argz_replace,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __str, char const *__restrict __with, unsigned int *__restrict __replace_count),argz_replace,(__pargz,__pargz_len,__str,__with,__replace_count))
#elif defined(__CRT_HAVE___argz_replace)
/* Replace any occurrences of the string `STR' in `PARGZ' with `WITH', reallocating
 * `PARGZ' as necessary. If `PREPLACE_COUNT' is non-NULL, `*PREPLACE_COUNT' will be
 * incremented by number of replacements performed */
__CDECLARE(__ATTR_NONNULL((1, 2, 4)),error_t,__NOTHROW_NCX,__argz_replace,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __str, char const *__restrict __with, unsigned int *__restrict __replace_count),(__pargz,__pargz_len,__str,__with,__replace_count))
#elif defined(__CRT_HAVE_realloc) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree))
#include <local/argz/argz_replace.h>
/* Replace any occurrences of the string `STR' in `PARGZ' with `WITH', reallocating
 * `PARGZ' as necessary. If `PREPLACE_COUNT' is non-NULL, `*PREPLACE_COUNT' will be
 * incremented by number of replacements performed */
__FORCELOCAL __ATTR_NONNULL((1, 2, 4)) error_t __NOTHROW_NCX(__LIBCCALL __argz_replace)(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __str, char const *__restrict __with, unsigned int *__restrict __replace_count) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_replace))(__pargz, __pargz_len, __str, __with, __replace_count); }
#else /* ... */
#undef ____argz_replace_defined
#endif /* !... */
#endif /* !____argz_replace_defined */
#ifdef __CRT_HAVE_argz_next
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ARGZ_H_PROTO)
extern "C++" {
/* Returns the next entry in ARGZ & ARGZ_LEN after ENTRY, or NULL if there
 * are no more. If entry is NULL, then the first entry is returned. This
 * behavior allows two convenient iteration styles:
 * >> char *entry = NULL;
 * >> while ((entry = argz_next(argz, argz_len, entry)) != NULL)
 * >>     ...;
 * or
 * >> char *entry;
 * >> for (entry = NULL; entry; entry = argz_next(argz, argz_len, entry))
 * >>     ...; */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,char *,__NOTHROW_NCX,argz_next,(char *__restrict __argz, size_t __argz_len, char *__restrict __entry),argz_next,(__argz,__argz_len,__entry))
/* Returns the next entry in ARGZ & ARGZ_LEN after ENTRY, or NULL if there
 * are no more. If entry is NULL, then the first entry is returned. This
 * behavior allows two convenient iteration styles:
 * >> char *entry = NULL;
 * >> while ((entry = argz_next(argz, argz_len, entry)) != NULL)
 * >>     ...;
 * or
 * >> char *entry;
 * >> for (entry = NULL; entry; entry = argz_next(argz, argz_len, entry))
 * >>     ...; */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,char const *,__NOTHROW_NCX,argz_next,(char const *__restrict __argz, size_t __argz_len, char const *__restrict __entry),argz_next,(__argz,__argz_len,__entry))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ARGZ_H_PROTO */
/* Returns the next entry in ARGZ & ARGZ_LEN after ENTRY, or NULL if there
 * are no more. If entry is NULL, then the first entry is returned. This
 * behavior allows two convenient iteration styles:
 * >> char *entry = NULL;
 * >> while ((entry = argz_next(argz, argz_len, entry)) != NULL)
 * >>     ...;
 * or
 * >> char *entry;
 * >> for (entry = NULL; entry; entry = argz_next(argz, argz_len, entry))
 * >>     ...; */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,char *,__NOTHROW_NCX,argz_next,(char const *__restrict __argz, size_t __argz_len, char const *__restrict __entry),(__argz,__argz_len,__entry))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ARGZ_H_PROTO */
#elif defined(__CRT_HAVE___argz_next)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ARGZ_H_PROTO)
extern "C++" {
/* Returns the next entry in ARGZ & ARGZ_LEN after ENTRY, or NULL if there
 * are no more. If entry is NULL, then the first entry is returned. This
 * behavior allows two convenient iteration styles:
 * >> char *entry = NULL;
 * >> while ((entry = argz_next(argz, argz_len, entry)) != NULL)
 * >>     ...;
 * or
 * >> char *entry;
 * >> for (entry = NULL; entry; entry = argz_next(argz, argz_len, entry))
 * >>     ...; */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,char *,__NOTHROW_NCX,argz_next,(char *__restrict __argz, size_t __argz_len, char *__restrict __entry),__argz_next,(__argz,__argz_len,__entry))
/* Returns the next entry in ARGZ & ARGZ_LEN after ENTRY, or NULL if there
 * are no more. If entry is NULL, then the first entry is returned. This
 * behavior allows two convenient iteration styles:
 * >> char *entry = NULL;
 * >> while ((entry = argz_next(argz, argz_len, entry)) != NULL)
 * >>     ...;
 * or
 * >> char *entry;
 * >> for (entry = NULL; entry; entry = argz_next(argz, argz_len, entry))
 * >>     ...; */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,char const *,__NOTHROW_NCX,argz_next,(char const *__restrict __argz, size_t __argz_len, char const *__restrict __entry),__argz_next,(__argz,__argz_len,__entry))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ARGZ_H_PROTO */
/* Returns the next entry in ARGZ & ARGZ_LEN after ENTRY, or NULL if there
 * are no more. If entry is NULL, then the first entry is returned. This
 * behavior allows two convenient iteration styles:
 * >> char *entry = NULL;
 * >> while ((entry = argz_next(argz, argz_len, entry)) != NULL)
 * >>     ...;
 * or
 * >> char *entry;
 * >> for (entry = NULL; entry; entry = argz_next(argz, argz_len, entry))
 * >>     ...; */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,char *,__NOTHROW_NCX,argz_next,(char const *__restrict __argz, size_t __argz_len, char const *__restrict __entry),__argz_next,(__argz,__argz_len,__entry))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ARGZ_H_PROTO */
#else /* ... */
#include <local/argz/argz_next.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ARGZ_H_PROTO)
extern "C++" {
/* Returns the next entry in ARGZ & ARGZ_LEN after ENTRY, or NULL if there
 * are no more. If entry is NULL, then the first entry is returned. This
 * behavior allows two convenient iteration styles:
 * >> char *entry = NULL;
 * >> while ((entry = argz_next(argz, argz_len, entry)) != NULL)
 * >>     ...;
 * or
 * >> char *entry;
 * >> for (entry = NULL; entry; entry = argz_next(argz, argz_len, entry))
 * >>     ...; */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL argz_next)(char *__restrict __argz, size_t __argz_len, char *__restrict __entry) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_next))(__argz, __argz_len, __entry); }
/* Returns the next entry in ARGZ & ARGZ_LEN after ENTRY, or NULL if there
 * are no more. If entry is NULL, then the first entry is returned. This
 * behavior allows two convenient iteration styles:
 * >> char *entry = NULL;
 * >> while ((entry = argz_next(argz, argz_len, entry)) != NULL)
 * >>     ...;
 * or
 * >> char *entry;
 * >> for (entry = NULL; entry; entry = argz_next(argz, argz_len, entry))
 * >>     ...; */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED char const *__NOTHROW_NCX(__LIBCCALL argz_next)(char const *__restrict __argz, size_t __argz_len, char const *__restrict __entry) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_next))(__argz, __argz_len, __entry); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ARGZ_H_PROTO */
/* Returns the next entry in ARGZ & ARGZ_LEN after ENTRY, or NULL if there
 * are no more. If entry is NULL, then the first entry is returned. This
 * behavior allows two convenient iteration styles:
 * >> char *entry = NULL;
 * >> while ((entry = argz_next(argz, argz_len, entry)) != NULL)
 * >>     ...;
 * or
 * >> char *entry;
 * >> for (entry = NULL; entry; entry = argz_next(argz, argz_len, entry))
 * >>     ...; */
__NAMESPACE_LOCAL_USING_OR_IMPL(argz_next, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL argz_next)(char const *__restrict __argz, size_t __argz_len, char const *__restrict __entry) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_next))(__argz, __argz_len, __entry); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ARGZ_H_PROTO */
#endif /* !... */
#ifndef ____argz_next_defined
#define ____argz_next_defined 1
#ifdef __CRT_HAVE_argz_next
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ARGZ_H_PROTO)
extern "C++" {
/* Returns the next entry in ARGZ & ARGZ_LEN after ENTRY, or NULL if there
 * are no more. If entry is NULL, then the first entry is returned. This
 * behavior allows two convenient iteration styles:
 * >> char *entry = NULL;
 * >> while ((entry = argz_next(argz, argz_len, entry)) != NULL)
 * >>     ...;
 * or
 * >> char *entry;
 * >> for (entry = NULL; entry; entry = argz_next(argz, argz_len, entry))
 * >>     ...; */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,char *,__NOTHROW_NCX,__argz_next,(char *__restrict __argz, size_t __argz_len, char *__restrict __entry),argz_next,(__argz,__argz_len,__entry))
/* Returns the next entry in ARGZ & ARGZ_LEN after ENTRY, or NULL if there
 * are no more. If entry is NULL, then the first entry is returned. This
 * behavior allows two convenient iteration styles:
 * >> char *entry = NULL;
 * >> while ((entry = argz_next(argz, argz_len, entry)) != NULL)
 * >>     ...;
 * or
 * >> char *entry;
 * >> for (entry = NULL; entry; entry = argz_next(argz, argz_len, entry))
 * >>     ...; */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,char const *,__NOTHROW_NCX,__argz_next,(char const *__restrict __argz, size_t __argz_len, char const *__restrict __entry),argz_next,(__argz,__argz_len,__entry))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ARGZ_H_PROTO */
/* Returns the next entry in ARGZ & ARGZ_LEN after ENTRY, or NULL if there
 * are no more. If entry is NULL, then the first entry is returned. This
 * behavior allows two convenient iteration styles:
 * >> char *entry = NULL;
 * >> while ((entry = argz_next(argz, argz_len, entry)) != NULL)
 * >>     ...;
 * or
 * >> char *entry;
 * >> for (entry = NULL; entry; entry = argz_next(argz, argz_len, entry))
 * >>     ...; */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,char *,__NOTHROW_NCX,__argz_next,(char const *__restrict __argz, size_t __argz_len, char const *__restrict __entry),argz_next,(__argz,__argz_len,__entry))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ARGZ_H_PROTO */
#elif defined(__CRT_HAVE___argz_next)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ARGZ_H_PROTO)
extern "C++" {
/* Returns the next entry in ARGZ & ARGZ_LEN after ENTRY, or NULL if there
 * are no more. If entry is NULL, then the first entry is returned. This
 * behavior allows two convenient iteration styles:
 * >> char *entry = NULL;
 * >> while ((entry = argz_next(argz, argz_len, entry)) != NULL)
 * >>     ...;
 * or
 * >> char *entry;
 * >> for (entry = NULL; entry; entry = argz_next(argz, argz_len, entry))
 * >>     ...; */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,char *,__NOTHROW_NCX,__argz_next,(char *__restrict __argz, size_t __argz_len, char *__restrict __entry),__argz_next,(__argz,__argz_len,__entry))
/* Returns the next entry in ARGZ & ARGZ_LEN after ENTRY, or NULL if there
 * are no more. If entry is NULL, then the first entry is returned. This
 * behavior allows two convenient iteration styles:
 * >> char *entry = NULL;
 * >> while ((entry = argz_next(argz, argz_len, entry)) != NULL)
 * >>     ...;
 * or
 * >> char *entry;
 * >> for (entry = NULL; entry; entry = argz_next(argz, argz_len, entry))
 * >>     ...; */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,char const *,__NOTHROW_NCX,__argz_next,(char const *__restrict __argz, size_t __argz_len, char const *__restrict __entry),__argz_next,(__argz,__argz_len,__entry))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ARGZ_H_PROTO */
/* Returns the next entry in ARGZ & ARGZ_LEN after ENTRY, or NULL if there
 * are no more. If entry is NULL, then the first entry is returned. This
 * behavior allows two convenient iteration styles:
 * >> char *entry = NULL;
 * >> while ((entry = argz_next(argz, argz_len, entry)) != NULL)
 * >>     ...;
 * or
 * >> char *entry;
 * >> for (entry = NULL; entry; entry = argz_next(argz, argz_len, entry))
 * >>     ...; */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,char *,__NOTHROW_NCX,__argz_next,(char const *__restrict __argz, size_t __argz_len, char const *__restrict __entry),(__argz,__argz_len,__entry))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ARGZ_H_PROTO */
#else /* ... */
#include <local/argz/argz_next.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ARGZ_H_PROTO)
extern "C++" {
/* Returns the next entry in ARGZ & ARGZ_LEN after ENTRY, or NULL if there
 * are no more. If entry is NULL, then the first entry is returned. This
 * behavior allows two convenient iteration styles:
 * >> char *entry = NULL;
 * >> while ((entry = argz_next(argz, argz_len, entry)) != NULL)
 * >>     ...;
 * or
 * >> char *entry;
 * >> for (entry = NULL; entry; entry = argz_next(argz, argz_len, entry))
 * >>     ...; */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL __argz_next)(char *__restrict __argz, size_t __argz_len, char *__restrict __entry) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_next))(__argz, __argz_len, __entry); }
/* Returns the next entry in ARGZ & ARGZ_LEN after ENTRY, or NULL if there
 * are no more. If entry is NULL, then the first entry is returned. This
 * behavior allows two convenient iteration styles:
 * >> char *entry = NULL;
 * >> while ((entry = argz_next(argz, argz_len, entry)) != NULL)
 * >>     ...;
 * or
 * >> char *entry;
 * >> for (entry = NULL; entry; entry = argz_next(argz, argz_len, entry))
 * >>     ...; */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED char const *__NOTHROW_NCX(__LIBCCALL __argz_next)(char const *__restrict __argz, size_t __argz_len, char const *__restrict __entry) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_next))(__argz, __argz_len, __entry); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ARGZ_H_PROTO */
/* Returns the next entry in ARGZ & ARGZ_LEN after ENTRY, or NULL if there
 * are no more. If entry is NULL, then the first entry is returned. This
 * behavior allows two convenient iteration styles:
 * >> char *entry = NULL;
 * >> while ((entry = argz_next(argz, argz_len, entry)) != NULL)
 * >>     ...;
 * or
 * >> char *entry;
 * >> for (entry = NULL; entry; entry = argz_next(argz, argz_len, entry))
 * >>     ...; */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL __argz_next)(char const *__restrict __argz, size_t __argz_len, char const *__restrict __entry) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_next))(__argz, __argz_len, __entry); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ARGZ_H_PROTO */
#endif /* !... */
#endif /* !____argz_next_defined */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_ARGZ_H */
