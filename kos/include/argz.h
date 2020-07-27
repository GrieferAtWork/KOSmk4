/* HASH CRC-32:0x3dd9f95b */
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

/*
 * Note that the KOS implementations of these functions was written entirely
 * from scratch, only using GLibc's implementation as a reference (which also
 * resulted in me discovering some bugs in GLibc's version that I'm not going
 * to report because at least in my mind, these are just suuuuch _absolute_
 * beginner's mistakes...)
 * The function's that I've fixed are:
 *  - argz_add_sep()
 *  - argz_insert()
 * By the way: GLibc guys: If you want to copy my (fixed) implementation, that
 *                         is licensed under the ZLib license, so if one of you
 *                         comes across this, don't forget to include my copyright
 *                         notice when pasting ;)
 */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __error_t_defined
#define __error_t_defined 1
typedef __errno_t error_t;
#endif /* !__error_t_defined */

#ifdef __CRT_HAVE_argz_create
/* Construct an ARGZ string from a given NULL-terminated `ARGV'-vector,
 * as is also passed to main(), and accepted by the exec() family of functions
 * An ARGZ string is imply a string of '\0'-seperated sub-strings, where each
 * sub-string represents one of the original strings from `ARGV'
 * The base-pointer to this string is stored in `*PARGZ'
 * The overall length of the ARGZ string is tracked at the offset from its base
 * pointer, to the first byte after a trailing '\0' character that follows the
 * last of the many sub-strings. An empty ARGZ string is thus represented as any
 * base-pointer in conjunction with ARGZ_LEN=0. (But note that GLibc seems to
 * suggest that certain APIs should be used under the assumption that an empty
 * ARGZ string can also be represented with the base pointer ARGZ=NULL. This
 * kind of behavior is _NOT_ actually supported by the API, and only implied by
 * some (apparently) badly worded documentation of `argz_next(3)')
 * When an ARGZ string is no longer needed, it can be destroyed by passing its
 * base pointer (as filled in at `*PARGZ' by this function, and updated by the
 * many other functions in this header) to `free(3)'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,argz_create,(char *const ___argv[], char **__restrict __pargz, size_t *__restrict __pargz_len),(___argv,__pargz,__pargz_len))
#elif defined(__CRT_HAVE___argz_create)
/* Construct an ARGZ string from a given NULL-terminated `ARGV'-vector,
 * as is also passed to main(), and accepted by the exec() family of functions
 * An ARGZ string is imply a string of '\0'-seperated sub-strings, where each
 * sub-string represents one of the original strings from `ARGV'
 * The base-pointer to this string is stored in `*PARGZ'
 * The overall length of the ARGZ string is tracked at the offset from its base
 * pointer, to the first byte after a trailing '\0' character that follows the
 * last of the many sub-strings. An empty ARGZ string is thus represented as any
 * base-pointer in conjunction with ARGZ_LEN=0. (But note that GLibc seems to
 * suggest that certain APIs should be used under the assumption that an empty
 * ARGZ string can also be represented with the base pointer ARGZ=NULL. This
 * kind of behavior is _NOT_ actually supported by the API, and only implied by
 * some (apparently) badly worded documentation of `argz_next(3)')
 * When an ARGZ string is no longer needed, it can be destroyed by passing its
 * base pointer (as filled in at `*PARGZ' by this function, and updated by the
 * many other functions in this header) to `free(3)'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,argz_create,(char *const ___argv[], char **__restrict __pargz, size_t *__restrict __pargz_len),__argz_create,(___argv,__pargz,__pargz_len))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <local/argz/argz_create.h>
/* Construct an ARGZ string from a given NULL-terminated `ARGV'-vector,
 * as is also passed to main(), and accepted by the exec() family of functions
 * An ARGZ string is imply a string of '\0'-seperated sub-strings, where each
 * sub-string represents one of the original strings from `ARGV'
 * The base-pointer to this string is stored in `*PARGZ'
 * The overall length of the ARGZ string is tracked at the offset from its base
 * pointer, to the first byte after a trailing '\0' character that follows the
 * last of the many sub-strings. An empty ARGZ string is thus represented as any
 * base-pointer in conjunction with ARGZ_LEN=0. (But note that GLibc seems to
 * suggest that certain APIs should be used under the assumption that an empty
 * ARGZ string can also be represented with the base pointer ARGZ=NULL. This
 * kind of behavior is _NOT_ actually supported by the API, and only implied by
 * some (apparently) badly worded documentation of `argz_next(3)')
 * When an ARGZ string is no longer needed, it can be destroyed by passing its
 * base pointer (as filled in at `*PARGZ' by this function, and updated by the
 * many other functions in this header) to `free(3)'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__NAMESPACE_LOCAL_USING_OR_IMPL(argz_create, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) error_t __NOTHROW_NCX(__LIBCCALL argz_create)(char *const ___argv[], char **__restrict __pargz, size_t *__restrict __pargz_len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_create))(___argv, __pargz, __pargz_len); })
#endif /* ... */
#ifdef __CRT_HAVE_argz_create
/* Construct an ARGZ string from a given NULL-terminated `ARGV'-vector,
 * as is also passed to main(), and accepted by the exec() family of functions
 * An ARGZ string is imply a string of '\0'-seperated sub-strings, where each
 * sub-string represents one of the original strings from `ARGV'
 * The base-pointer to this string is stored in `*PARGZ'
 * The overall length of the ARGZ string is tracked at the offset from its base
 * pointer, to the first byte after a trailing '\0' character that follows the
 * last of the many sub-strings. An empty ARGZ string is thus represented as any
 * base-pointer in conjunction with ARGZ_LEN=0. (But note that GLibc seems to
 * suggest that certain APIs should be used under the assumption that an empty
 * ARGZ string can also be represented with the base pointer ARGZ=NULL. This
 * kind of behavior is _NOT_ actually supported by the API, and only implied by
 * some (apparently) badly worded documentation of `argz_next(3)')
 * When an ARGZ string is no longer needed, it can be destroyed by passing its
 * base pointer (as filled in at `*PARGZ' by this function, and updated by the
 * many other functions in this header) to `free(3)'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,__argz_create,(char *const ___argv[], char **__restrict __pargz, size_t *__restrict __pargz_len),argz_create,(___argv,__pargz,__pargz_len))
#elif defined(__CRT_HAVE___argz_create)
/* Construct an ARGZ string from a given NULL-terminated `ARGV'-vector,
 * as is also passed to main(), and accepted by the exec() family of functions
 * An ARGZ string is imply a string of '\0'-seperated sub-strings, where each
 * sub-string represents one of the original strings from `ARGV'
 * The base-pointer to this string is stored in `*PARGZ'
 * The overall length of the ARGZ string is tracked at the offset from its base
 * pointer, to the first byte after a trailing '\0' character that follows the
 * last of the many sub-strings. An empty ARGZ string is thus represented as any
 * base-pointer in conjunction with ARGZ_LEN=0. (But note that GLibc seems to
 * suggest that certain APIs should be used under the assumption that an empty
 * ARGZ string can also be represented with the base pointer ARGZ=NULL. This
 * kind of behavior is _NOT_ actually supported by the API, and only implied by
 * some (apparently) badly worded documentation of `argz_next(3)')
 * When an ARGZ string is no longer needed, it can be destroyed by passing its
 * base pointer (as filled in at `*PARGZ' by this function, and updated by the
 * many other functions in this header) to `free(3)'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,__argz_create,(char *const ___argv[], char **__restrict __pargz, size_t *__restrict __pargz_len),(___argv,__pargz,__pargz_len))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <local/argz/argz_create.h>
/* Construct an ARGZ string from a given NULL-terminated `ARGV'-vector,
 * as is also passed to main(), and accepted by the exec() family of functions
 * An ARGZ string is imply a string of '\0'-seperated sub-strings, where each
 * sub-string represents one of the original strings from `ARGV'
 * The base-pointer to this string is stored in `*PARGZ'
 * The overall length of the ARGZ string is tracked at the offset from its base
 * pointer, to the first byte after a trailing '\0' character that follows the
 * last of the many sub-strings. An empty ARGZ string is thus represented as any
 * base-pointer in conjunction with ARGZ_LEN=0. (But note that GLibc seems to
 * suggest that certain APIs should be used under the assumption that an empty
 * ARGZ string can also be represented with the base pointer ARGZ=NULL. This
 * kind of behavior is _NOT_ actually supported by the API, and only implied by
 * some (apparently) badly worded documentation of `argz_next(3)')
 * When an ARGZ string is no longer needed, it can be destroyed by passing its
 * base pointer (as filled in at `*PARGZ' by this function, and updated by the
 * many other functions in this header) to `free(3)'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) error_t __NOTHROW_NCX(__LIBCCALL __argz_create)(char *const ___argv[], char **__restrict __pargz, size_t *__restrict __pargz_len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_create))(___argv, __pargz, __pargz_len); }
#endif /* ... */
#ifdef __CRT_HAVE_argz_create_sep
/* Create an ARGZ string from `string' by splitting that string at each
 * occurance of `sep'. This function behaves the same as the following
 * pseudo-code:
 *     [*pargz, *pargz_len] = string.replace(sep, "\0").replaceall("\0\0", "\0");
 * As can be seen in the pseudo-code, duplicate, successive instance of `sep'
 * are merged, such that no empty sub-strings will be present in the resulting
 * ARGZ string.
 * For more information on the semantics of ARGZ strings, see the
 * documentation of `argz_create()'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__CDECLARE(__ATTR_NONNULL((1, 3, 4)),error_t,__NOTHROW_NCX,argz_create_sep,(char const *__restrict __string, int __sep, char **__restrict __pargz, size_t *__restrict __pargz_len),(__string,__sep,__pargz,__pargz_len))
#elif defined(__CRT_HAVE___argz_create_sep)
/* Create an ARGZ string from `string' by splitting that string at each
 * occurance of `sep'. This function behaves the same as the following
 * pseudo-code:
 *     [*pargz, *pargz_len] = string.replace(sep, "\0").replaceall("\0\0", "\0");
 * As can be seen in the pseudo-code, duplicate, successive instance of `sep'
 * are merged, such that no empty sub-strings will be present in the resulting
 * ARGZ string.
 * For more information on the semantics of ARGZ strings, see the
 * documentation of `argz_create()'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),error_t,__NOTHROW_NCX,argz_create_sep,(char const *__restrict __string, int __sep, char **__restrict __pargz, size_t *__restrict __pargz_len),__argz_create_sep,(__string,__sep,__pargz,__pargz_len))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree))
#include <local/argz/argz_create_sep.h>
/* Create an ARGZ string from `string' by splitting that string at each
 * occurance of `sep'. This function behaves the same as the following
 * pseudo-code:
 *     [*pargz, *pargz_len] = string.replace(sep, "\0").replaceall("\0\0", "\0");
 * As can be seen in the pseudo-code, duplicate, successive instance of `sep'
 * are merged, such that no empty sub-strings will be present in the resulting
 * ARGZ string.
 * For more information on the semantics of ARGZ strings, see the
 * documentation of `argz_create()'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__NAMESPACE_LOCAL_USING_OR_IMPL(argz_create_sep, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3, 4)) error_t __NOTHROW_NCX(__LIBCCALL argz_create_sep)(char const *__restrict __string, int __sep, char **__restrict __pargz, size_t *__restrict __pargz_len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_create_sep))(__string, __sep, __pargz, __pargz_len); })
#endif /* ... */
#ifdef __CRT_HAVE_argz_create_sep
/* Create an ARGZ string from `string' by splitting that string at each
 * occurance of `sep'. This function behaves the same as the following
 * pseudo-code:
 *     [*pargz, *pargz_len] = string.replace(sep, "\0").replaceall("\0\0", "\0");
 * As can be seen in the pseudo-code, duplicate, successive instance of `sep'
 * are merged, such that no empty sub-strings will be present in the resulting
 * ARGZ string.
 * For more information on the semantics of ARGZ strings, see the
 * documentation of `argz_create()'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),error_t,__NOTHROW_NCX,__argz_create_sep,(char const *__restrict __string, int __sep, char **__restrict __pargz, size_t *__restrict __pargz_len),argz_create_sep,(__string,__sep,__pargz,__pargz_len))
#elif defined(__CRT_HAVE___argz_create_sep)
/* Create an ARGZ string from `string' by splitting that string at each
 * occurance of `sep'. This function behaves the same as the following
 * pseudo-code:
 *     [*pargz, *pargz_len] = string.replace(sep, "\0").replaceall("\0\0", "\0");
 * As can be seen in the pseudo-code, duplicate, successive instance of `sep'
 * are merged, such that no empty sub-strings will be present in the resulting
 * ARGZ string.
 * For more information on the semantics of ARGZ strings, see the
 * documentation of `argz_create()'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__CDECLARE(__ATTR_NONNULL((1, 3, 4)),error_t,__NOTHROW_NCX,__argz_create_sep,(char const *__restrict __string, int __sep, char **__restrict __pargz, size_t *__restrict __pargz_len),(__string,__sep,__pargz,__pargz_len))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree))
#include <local/argz/argz_create_sep.h>
/* Create an ARGZ string from `string' by splitting that string at each
 * occurance of `sep'. This function behaves the same as the following
 * pseudo-code:
 *     [*pargz, *pargz_len] = string.replace(sep, "\0").replaceall("\0\0", "\0");
 * As can be seen in the pseudo-code, duplicate, successive instance of `sep'
 * are merged, such that no empty sub-strings will be present in the resulting
 * ARGZ string.
 * For more information on the semantics of ARGZ strings, see the
 * documentation of `argz_create()'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3, 4)) error_t __NOTHROW_NCX(__LIBCCALL __argz_create_sep)(char const *__restrict __string, int __sep, char **__restrict __pargz, size_t *__restrict __pargz_len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_create_sep))(__string, __sep, __pargz, __pargz_len); }
#endif /* ... */
#ifdef __CRT_HAVE_argz_count
/* Count and return the # of strings in `ARGZ'
 * Simply count the number of`NUL-characters within `argz...+=argz_len' */
__CDECLARE(__ATTR_PURE,size_t,__NOTHROW_NCX,argz_count,(char const *__argz, size_t __argz_len),(__argz,__argz_len))
#elif defined(__CRT_HAVE___argz_count)
/* Count and return the # of strings in `ARGZ'
 * Simply count the number of`NUL-characters within `argz...+=argz_len' */
__CREDIRECT(__ATTR_PURE,size_t,__NOTHROW_NCX,argz_count,(char const *__argz, size_t __argz_len),__argz_count,(__argz,__argz_len))
#else /* ... */
#include <local/argz/argz_count.h>
/* Count and return the # of strings in `ARGZ'
 * Simply count the number of`NUL-characters within `argz...+=argz_len' */
__NAMESPACE_LOCAL_USING_OR_IMPL(argz_count, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE size_t __NOTHROW_NCX(__LIBCCALL argz_count)(char const *__argz, size_t __argz_len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_count))(__argz, __argz_len); })
#endif /* !... */
#ifdef __CRT_HAVE_argz_count
/* Count and return the # of strings in `ARGZ'
 * Simply count the number of`NUL-characters within `argz...+=argz_len' */
__CREDIRECT(__ATTR_PURE,size_t,__NOTHROW_NCX,__argz_count,(char const *__argz, size_t __argz_len),argz_count,(__argz,__argz_len))
#elif defined(__CRT_HAVE___argz_count)
/* Count and return the # of strings in `ARGZ'
 * Simply count the number of`NUL-characters within `argz...+=argz_len' */
__CDECLARE(__ATTR_PURE,size_t,__NOTHROW_NCX,__argz_count,(char const *__argz, size_t __argz_len),(__argz,__argz_len))
#else /* ... */
#include <local/argz/argz_count.h>
/* Count and return the # of strings in `ARGZ'
 * Simply count the number of`NUL-characters within `argz...+=argz_len' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE size_t __NOTHROW_NCX(__LIBCCALL __argz_count)(char const *__argz, size_t __argz_len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_count))(__argz, __argz_len); }
#endif /* !... */
#ifdef __CRT_HAVE_argz_extract
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ARGZ_H_PROTO)
extern "C++" {
/* Extend pointers to individual string from `ARGZ', and sequentially write them to
 * `ARGV', for which the caller is responsivle to provide sufficient space to hold them
 * all (i.e. `argv' must be able to hold AT least `argz_count(argz, argz_len)' elements) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,argz_extract,(char *__restrict __argz, size_t __argz_len, char **__restrict ___argv),argz_extract,(__argz,__argz_len,___argv))
/* Extend pointers to individual string from `ARGZ', and sequentially write them to
 * `ARGV', for which the caller is responsivle to provide sufficient space to hold them
 * all (i.e. `argv' must be able to hold AT least `argz_count(argz, argz_len)' elements) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,argz_extract,(char const *__restrict __argz, size_t __argz_len, char const **__restrict ___argv),argz_extract,(__argz,__argz_len,___argv))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ARGZ_H_PROTO */
/* Extend pointers to individual string from `ARGZ', and sequentially write them to
 * `ARGV', for which the caller is responsivle to provide sufficient space to hold them
 * all (i.e. `argv' must be able to hold AT least `argz_count(argz, argz_len)' elements) */
__CDECLARE_VOID(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,argz_extract,(char const *__restrict __argz, size_t __argz_len, char **__restrict ___argv),(__argz,__argz_len,___argv))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ARGZ_H_PROTO */
#elif defined(__CRT_HAVE___argz_extract)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ARGZ_H_PROTO)
extern "C++" {
/* Extend pointers to individual string from `ARGZ', and sequentially write them to
 * `ARGV', for which the caller is responsivle to provide sufficient space to hold them
 * all (i.e. `argv' must be able to hold AT least `argz_count(argz, argz_len)' elements) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,argz_extract,(char *__restrict __argz, size_t __argz_len, char **__restrict ___argv),__argz_extract,(__argz,__argz_len,___argv))
/* Extend pointers to individual string from `ARGZ', and sequentially write them to
 * `ARGV', for which the caller is responsivle to provide sufficient space to hold them
 * all (i.e. `argv' must be able to hold AT least `argz_count(argz, argz_len)' elements) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,argz_extract,(char const *__restrict __argz, size_t __argz_len, char const **__restrict ___argv),__argz_extract,(__argz,__argz_len,___argv))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ARGZ_H_PROTO */
/* Extend pointers to individual string from `ARGZ', and sequentially write them to
 * `ARGV', for which the caller is responsivle to provide sufficient space to hold them
 * all (i.e. `argv' must be able to hold AT least `argz_count(argz, argz_len)' elements) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,argz_extract,(char const *__restrict __argz, size_t __argz_len, char **__restrict ___argv),__argz_extract,(__argz,__argz_len,___argv))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ARGZ_H_PROTO */
#else /* ... */
#include <local/argz/argz_extract.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ARGZ_H_PROTO)
extern "C++" {
/* Extend pointers to individual string from `ARGZ', and sequentially write them to
 * `ARGV', for which the caller is responsivle to provide sufficient space to hold them
 * all (i.e. `argv' must be able to hold AT least `argz_count(argz, argz_len)' elements) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) void __NOTHROW_NCX(__LIBCCALL argz_extract)(char *__restrict __argz, size_t __argz_len, char **__restrict ___argv) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_extract))(__argz, __argz_len, ___argv); }
/* Extend pointers to individual string from `ARGZ', and sequentially write them to
 * `ARGV', for which the caller is responsivle to provide sufficient space to hold them
 * all (i.e. `argv' must be able to hold AT least `argz_count(argz, argz_len)' elements) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) void __NOTHROW_NCX(__LIBCCALL argz_extract)(char const *__restrict __argz, size_t __argz_len, char const **__restrict ___argv) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_extract))(__argz, __argz_len, (char **)___argv); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ARGZ_H_PROTO */
/* Extend pointers to individual string from `ARGZ', and sequentially write them to
 * `ARGV', for which the caller is responsivle to provide sufficient space to hold them
 * all (i.e. `argv' must be able to hold AT least `argz_count(argz, argz_len)' elements) */
__NAMESPACE_LOCAL_USING_OR_IMPL(argz_extract, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) void __NOTHROW_NCX(__LIBCCALL argz_extract)(char const *__restrict __argz, size_t __argz_len, char **__restrict ___argv) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_extract))(__argz, __argz_len, ___argv); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ARGZ_H_PROTO */
#endif /* !... */
#ifdef __CRT_HAVE_argz_extract
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ARGZ_H_PROTO)
extern "C++" {
/* Extend pointers to individual string from `ARGZ', and sequentially write them to
 * `ARGV', for which the caller is responsivle to provide sufficient space to hold them
 * all (i.e. `argv' must be able to hold AT least `argz_count(argz, argz_len)' elements) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,__argz_extract,(char *__restrict __argz, size_t __argz_len, char **__restrict ___argv),argz_extract,(__argz,__argz_len,___argv))
/* Extend pointers to individual string from `ARGZ', and sequentially write them to
 * `ARGV', for which the caller is responsivle to provide sufficient space to hold them
 * all (i.e. `argv' must be able to hold AT least `argz_count(argz, argz_len)' elements) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,__argz_extract,(char const *__restrict __argz, size_t __argz_len, char const **__restrict ___argv),argz_extract,(__argz,__argz_len,___argv))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ARGZ_H_PROTO */
/* Extend pointers to individual string from `ARGZ', and sequentially write them to
 * `ARGV', for which the caller is responsivle to provide sufficient space to hold them
 * all (i.e. `argv' must be able to hold AT least `argz_count(argz, argz_len)' elements) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,__argz_extract,(char const *__restrict __argz, size_t __argz_len, char **__restrict ___argv),argz_extract,(__argz,__argz_len,___argv))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ARGZ_H_PROTO */
#elif defined(__CRT_HAVE___argz_extract)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ARGZ_H_PROTO)
extern "C++" {
/* Extend pointers to individual string from `ARGZ', and sequentially write them to
 * `ARGV', for which the caller is responsivle to provide sufficient space to hold them
 * all (i.e. `argv' must be able to hold AT least `argz_count(argz, argz_len)' elements) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,__argz_extract,(char *__restrict __argz, size_t __argz_len, char **__restrict ___argv),__argz_extract,(__argz,__argz_len,___argv))
/* Extend pointers to individual string from `ARGZ', and sequentially write them to
 * `ARGV', for which the caller is responsivle to provide sufficient space to hold them
 * all (i.e. `argv' must be able to hold AT least `argz_count(argz, argz_len)' elements) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,__argz_extract,(char const *__restrict __argz, size_t __argz_len, char const **__restrict ___argv),__argz_extract,(__argz,__argz_len,___argv))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ARGZ_H_PROTO */
/* Extend pointers to individual string from `ARGZ', and sequentially write them to
 * `ARGV', for which the caller is responsivle to provide sufficient space to hold them
 * all (i.e. `argv' must be able to hold AT least `argz_count(argz, argz_len)' elements) */
__CDECLARE_VOID(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,__argz_extract,(char const *__restrict __argz, size_t __argz_len, char **__restrict ___argv),(__argz,__argz_len,___argv))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ARGZ_H_PROTO */
#else /* ... */
#include <local/argz/argz_extract.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ARGZ_H_PROTO)
extern "C++" {
/* Extend pointers to individual string from `ARGZ', and sequentially write them to
 * `ARGV', for which the caller is responsivle to provide sufficient space to hold them
 * all (i.e. `argv' must be able to hold AT least `argz_count(argz, argz_len)' elements) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) void __NOTHROW_NCX(__LIBCCALL __argz_extract)(char *__restrict __argz, size_t __argz_len, char **__restrict ___argv) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_extract))(__argz, __argz_len, ___argv); }
/* Extend pointers to individual string from `ARGZ', and sequentially write them to
 * `ARGV', for which the caller is responsivle to provide sufficient space to hold them
 * all (i.e. `argv' must be able to hold AT least `argz_count(argz, argz_len)' elements) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) void __NOTHROW_NCX(__LIBCCALL __argz_extract)(char const *__restrict __argz, size_t __argz_len, char const **__restrict ___argv) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_extract))(__argz, __argz_len, (char **)___argv); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ARGZ_H_PROTO */
/* Extend pointers to individual string from `ARGZ', and sequentially write them to
 * `ARGV', for which the caller is responsivle to provide sufficient space to hold them
 * all (i.e. `argv' must be able to hold AT least `argz_count(argz, argz_len)' elements) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) void __NOTHROW_NCX(__LIBCCALL __argz_extract)(char const *__restrict __argz, size_t __argz_len, char **__restrict ___argv) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_extract))(__argz, __argz_len, ___argv); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ARGZ_H_PROTO */
#endif /* !... */
#ifdef __CRT_HAVE_argz_stringify
/* Convert an `ARGZ' string into a NUL-terminated c-string
 * with a total `strlen(argz) == len - 1', by replacing all
 * of the NUL-characters separating the individual ARGZ strings
 * with `SEP'. */
__CDECLARE_VOID(,__NOTHROW_NCX,argz_stringify,(char *__argz, size_t __len, int __sep),(__argz,__len,__sep))
#elif defined(__CRT_HAVE___argz_stringify)
/* Convert an `ARGZ' string into a NUL-terminated c-string
 * with a total `strlen(argz) == len - 1', by replacing all
 * of the NUL-characters separating the individual ARGZ strings
 * with `SEP'. */
__CREDIRECT_VOID(,__NOTHROW_NCX,argz_stringify,(char *__argz, size_t __len, int __sep),__argz_stringify,(__argz,__len,__sep))
#else /* ... */
#include <local/argz/argz_stringify.h>
/* Convert an `ARGZ' string into a NUL-terminated c-string
 * with a total `strlen(argz) == len - 1', by replacing all
 * of the NUL-characters separating the individual ARGZ strings
 * with `SEP'. */
__NAMESPACE_LOCAL_USING_OR_IMPL(argz_stringify, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL argz_stringify)(char *__argz, size_t __len, int __sep) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_stringify))(__argz, __len, __sep); })
#endif /* !... */
#ifdef __CRT_HAVE_argz_stringify
/* Convert an `ARGZ' string into a NUL-terminated c-string
 * with a total `strlen(argz) == len - 1', by replacing all
 * of the NUL-characters separating the individual ARGZ strings
 * with `SEP'. */
__CREDIRECT_VOID(,__NOTHROW_NCX,__argz_stringify,(char *__argz, size_t __len, int __sep),argz_stringify,(__argz,__len,__sep))
#elif defined(__CRT_HAVE___argz_stringify)
/* Convert an `ARGZ' string into a NUL-terminated c-string
 * with a total `strlen(argz) == len - 1', by replacing all
 * of the NUL-characters separating the individual ARGZ strings
 * with `SEP'. */
__CDECLARE_VOID(,__NOTHROW_NCX,__argz_stringify,(char *__argz, size_t __len, int __sep),(__argz,__len,__sep))
#else /* ... */
#include <local/argz/argz_stringify.h>
/* Convert an `ARGZ' string into a NUL-terminated c-string
 * with a total `strlen(argz) == len - 1', by replacing all
 * of the NUL-characters separating the individual ARGZ strings
 * with `SEP'. */
__FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL __argz_stringify)(char *__argz, size_t __len, int __sep) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_stringify))(__argz, __len, __sep); }
#endif /* !... */
#ifdef __CRT_HAVE_argz_append
/* Increase allocated memory of `*PARGZ' and append `buf...+=buf_len'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__CDECLARE(__ATTR_NONNULL((1, 2)),error_t,__NOTHROW_NCX,argz_append,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __buf, size_t __buf_len),(__pargz,__pargz_len,__buf,__buf_len))
#elif defined(__CRT_HAVE___argz_create_sep)
/* Increase allocated memory of `*PARGZ' and append `buf...+=buf_len'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__CREDIRECT(__ATTR_NONNULL((1, 2)),error_t,__NOTHROW_NCX,argz_append,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __buf, size_t __buf_len),__argz_create_sep,(__pargz,__pargz_len,__buf,__buf_len))
#elif defined(__CRT_HAVE_realloc)
#include <local/argz/argz_append.h>
/* Increase allocated memory of `*PARGZ' and append `buf...+=buf_len'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__NAMESPACE_LOCAL_USING_OR_IMPL(argz_append, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) error_t __NOTHROW_NCX(__LIBCCALL argz_append)(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __buf, size_t __buf_len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_append))(__pargz, __pargz_len, __buf, __buf_len); })
#endif /* ... */
#ifdef __CRT_HAVE_argz_append
/* Increase allocated memory of `*PARGZ' and append `buf...+=buf_len'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__CREDIRECT(__ATTR_NONNULL((1, 2)),error_t,__NOTHROW_NCX,__argz_append,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __buf, size_t __buf_len),argz_append,(__pargz,__pargz_len,__buf,__buf_len))
#elif defined(__CRT_HAVE___argz_create_sep)
/* Increase allocated memory of `*PARGZ' and append `buf...+=buf_len'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__CREDIRECT(__ATTR_NONNULL((1, 2)),error_t,__NOTHROW_NCX,__argz_append,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __buf, size_t __buf_len),__argz_create_sep,(__pargz,__pargz_len,__buf,__buf_len))
#elif defined(__CRT_HAVE_realloc)
#include <local/argz/argz_append.h>
/* Increase allocated memory of `*PARGZ' and append `buf...+=buf_len'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) error_t __NOTHROW_NCX(__LIBCCALL __argz_append)(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __buf, size_t __buf_len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_append))(__pargz, __pargz_len, __buf, __buf_len); }
#endif /* ... */
#ifdef __CRT_HAVE_argz_add
/* Append `STR' (including the trailing NUL-character) to the argz string in `PARGZ...+=PARGZ_LEN'
 * This is the same as `argz_append(pargz, pargz_len, str, strlen(str) + 1)'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,argz_add,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __str),(__pargz,__pargz_len,__str))
#elif defined(__CRT_HAVE___argz_add)
/* Append `STR' (including the trailing NUL-character) to the argz string in `PARGZ...+=PARGZ_LEN'
 * This is the same as `argz_append(pargz, pargz_len, str, strlen(str) + 1)'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,argz_add,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __str),__argz_add,(__pargz,__pargz_len,__str))
#elif defined(__CRT_HAVE_argz_append) || defined(__CRT_HAVE___argz_create_sep) || defined(__CRT_HAVE_realloc)
#include <local/argz/argz_add.h>
/* Append `STR' (including the trailing NUL-character) to the argz string in `PARGZ...+=PARGZ_LEN'
 * This is the same as `argz_append(pargz, pargz_len, str, strlen(str) + 1)'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__NAMESPACE_LOCAL_USING_OR_IMPL(argz_add, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) error_t __NOTHROW_NCX(__LIBCCALL argz_add)(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_add))(__pargz, __pargz_len, __str); })
#endif /* ... */
#ifdef __CRT_HAVE_argz_add
/* Append `STR' (including the trailing NUL-character) to the argz string in `PARGZ...+=PARGZ_LEN'
 * This is the same as `argz_append(pargz, pargz_len, str, strlen(str) + 1)'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,__argz_add,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __str),argz_add,(__pargz,__pargz_len,__str))
#elif defined(__CRT_HAVE___argz_add)
/* Append `STR' (including the trailing NUL-character) to the argz string in `PARGZ...+=PARGZ_LEN'
 * This is the same as `argz_append(pargz, pargz_len, str, strlen(str) + 1)'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,__argz_add,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __str),(__pargz,__pargz_len,__str))
#elif defined(__CRT_HAVE_argz_append) || defined(__CRT_HAVE___argz_create_sep) || defined(__CRT_HAVE_realloc)
#include <local/argz/argz_add.h>
/* Append `STR' (including the trailing NUL-character) to the argz string in `PARGZ...+=PARGZ_LEN'
 * This is the same as `argz_append(pargz, pargz_len, str, strlen(str) + 1)'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) error_t __NOTHROW_NCX(__LIBCCALL __argz_add)(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_add))(__pargz, __pargz_len, __str); }
#endif /* ... */
#ifdef __CRT_HAVE_argz_add_sep
/* A combination of `argz_create_sep()' and `argz_append()' that will
 * append a duplication of `string' onto `*PARGZ', whilst replacing all
 * instances of `sep' with NUL-characters, thus turning them into the
 * markers between seperate strings. Note however that duplicate,
 * successive instance of `sep' are merged, such that no empty sub-
 * strings will be present in the resulting ARGZ string.
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,argz_add_sep,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __string, int __sep),(__pargz,__pargz_len,__string,__sep))
#elif defined(__CRT_HAVE___argz_add_sep)
/* A combination of `argz_create_sep()' and `argz_append()' that will
 * append a duplication of `string' onto `*PARGZ', whilst replacing all
 * instances of `sep' with NUL-characters, thus turning them into the
 * markers between seperate strings. Note however that duplicate,
 * successive instance of `sep' are merged, such that no empty sub-
 * strings will be present in the resulting ARGZ string.
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,argz_add_sep,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __string, int __sep),__argz_add_sep,(__pargz,__pargz_len,__string,__sep))
#elif defined(__CRT_HAVE_realloc)
#include <local/argz/argz_add_sep.h>
/* A combination of `argz_create_sep()' and `argz_append()' that will
 * append a duplication of `string' onto `*PARGZ', whilst replacing all
 * instances of `sep' with NUL-characters, thus turning them into the
 * markers between seperate strings. Note however that duplicate,
 * successive instance of `sep' are merged, such that no empty sub-
 * strings will be present in the resulting ARGZ string.
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__NAMESPACE_LOCAL_USING_OR_IMPL(argz_add_sep, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) error_t __NOTHROW_NCX(__LIBCCALL argz_add_sep)(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __string, int __sep) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_add_sep))(__pargz, __pargz_len, __string, __sep); })
#endif /* ... */
#ifdef __CRT_HAVE_argz_add_sep
/* A combination of `argz_create_sep()' and `argz_append()' that will
 * append a duplication of `string' onto `*PARGZ', whilst replacing all
 * instances of `sep' with NUL-characters, thus turning them into the
 * markers between seperate strings. Note however that duplicate,
 * successive instance of `sep' are merged, such that no empty sub-
 * strings will be present in the resulting ARGZ string.
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,__argz_add_sep,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __string, int __sep),argz_add_sep,(__pargz,__pargz_len,__string,__sep))
#elif defined(__CRT_HAVE___argz_add_sep)
/* A combination of `argz_create_sep()' and `argz_append()' that will
 * append a duplication of `string' onto `*PARGZ', whilst replacing all
 * instances of `sep' with NUL-characters, thus turning them into the
 * markers between seperate strings. Note however that duplicate,
 * successive instance of `sep' are merged, such that no empty sub-
 * strings will be present in the resulting ARGZ string.
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),error_t,__NOTHROW_NCX,__argz_add_sep,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __string, int __sep),(__pargz,__pargz_len,__string,__sep))
#elif defined(__CRT_HAVE_realloc)
#include <local/argz/argz_add_sep.h>
/* A combination of `argz_create_sep()' and `argz_append()' that will
 * append a duplication of `string' onto `*PARGZ', whilst replacing all
 * instances of `sep' with NUL-characters, thus turning them into the
 * markers between seperate strings. Note however that duplicate,
 * successive instance of `sep' are merged, such that no empty sub-
 * strings will be present in the resulting ARGZ string.
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) error_t __NOTHROW_NCX(__LIBCCALL __argz_add_sep)(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __string, int __sep) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_add_sep))(__pargz, __pargz_len, __string, __sep); }
#endif /* ... */
#ifdef __CRT_HAVE_argz_delete
/* Find the index of `ENTRY' inside of `PARGZ...+=PARGZ_LEN', and, if
 * found, remove that entry by shifting all following elements downwards
 * by one, as well as decrementing `*PARGZ_LEN' by one.
 * Note that `ENTRY' must be the actual pointer to one of the elements
 * of the given `PARGZ...+=PARGZ_LEN', and not just a string equal to one
 * of the elements... (took me a while to realize this one) */
__CDECLARE_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,argz_delete,(char **__restrict __pargz, size_t *__restrict __pargz_len, char *__entry),(__pargz,__pargz_len,__entry))
#elif defined(__CRT_HAVE___argz_add_sep)
/* Find the index of `ENTRY' inside of `PARGZ...+=PARGZ_LEN', and, if
 * found, remove that entry by shifting all following elements downwards
 * by one, as well as decrementing `*PARGZ_LEN' by one.
 * Note that `ENTRY' must be the actual pointer to one of the elements
 * of the given `PARGZ...+=PARGZ_LEN', and not just a string equal to one
 * of the elements... (took me a while to realize this one) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,argz_delete,(char **__restrict __pargz, size_t *__restrict __pargz_len, char *__entry),__argz_add_sep,(__pargz,__pargz_len,__entry))
#else /* ... */
#include <local/argz/argz_delete.h>
/* Find the index of `ENTRY' inside of `PARGZ...+=PARGZ_LEN', and, if
 * found, remove that entry by shifting all following elements downwards
 * by one, as well as decrementing `*PARGZ_LEN' by one.
 * Note that `ENTRY' must be the actual pointer to one of the elements
 * of the given `PARGZ...+=PARGZ_LEN', and not just a string equal to one
 * of the elements... (took me a while to realize this one) */
__NAMESPACE_LOCAL_USING_OR_IMPL(argz_delete, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) void __NOTHROW_NCX(__LIBCCALL argz_delete)(char **__restrict __pargz, size_t *__restrict __pargz_len, char *__entry) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_delete))(__pargz, __pargz_len, __entry); })
#endif /* !... */
#ifdef __CRT_HAVE_argz_delete
/* Find the index of `ENTRY' inside of `PARGZ...+=PARGZ_LEN', and, if
 * found, remove that entry by shifting all following elements downwards
 * by one, as well as decrementing `*PARGZ_LEN' by one.
 * Note that `ENTRY' must be the actual pointer to one of the elements
 * of the given `PARGZ...+=PARGZ_LEN', and not just a string equal to one
 * of the elements... (took me a while to realize this one) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,__argz_delete,(char **__restrict __pargz, size_t *__restrict __pargz_len, char *__entry),argz_delete,(__pargz,__pargz_len,__entry))
#elif defined(__CRT_HAVE___argz_add_sep)
/* Find the index of `ENTRY' inside of `PARGZ...+=PARGZ_LEN', and, if
 * found, remove that entry by shifting all following elements downwards
 * by one, as well as decrementing `*PARGZ_LEN' by one.
 * Note that `ENTRY' must be the actual pointer to one of the elements
 * of the given `PARGZ...+=PARGZ_LEN', and not just a string equal to one
 * of the elements... (took me a while to realize this one) */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,__argz_delete,(char **__restrict __pargz, size_t *__restrict __pargz_len, char *__entry),__argz_add_sep,(__pargz,__pargz_len,__entry))
#else /* ... */
#include <local/argz/argz_delete.h>
/* Find the index of `ENTRY' inside of `PARGZ...+=PARGZ_LEN', and, if
 * found, remove that entry by shifting all following elements downwards
 * by one, as well as decrementing `*PARGZ_LEN' by one.
 * Note that `ENTRY' must be the actual pointer to one of the elements
 * of the given `PARGZ...+=PARGZ_LEN', and not just a string equal to one
 * of the elements... (took me a while to realize this one) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) void __NOTHROW_NCX(__LIBCCALL __argz_delete)(char **__restrict __pargz, size_t *__restrict __pargz_len, char *__entry) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_delete))(__pargz, __pargz_len, __entry); }
#endif /* !... */
#ifdef __CRT_HAVE_argz_insert
/* When `before' is `NULL', do the same as `argz_add(PARGZ, PARGZ_LEN, ENTRY)'
 * Otherwise, `before' should point somewhere into the middle, or to the start
 * of an existing argument entry, who's beginning will first be located, before
 * this function will then allocate additional memory to insert a copy of `entry'
 * such that the copy will appear before the entry pointed to by `before'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory
 * @return: EINVAL: The given `before' is either NULL, or apart of the given ARGZ */
__CDECLARE(__ATTR_NONNULL((1, 2, 4)),error_t,__NOTHROW_NCX,argz_insert,(char **__restrict __pargz, size_t *__restrict __pargz_len, char *__before, char const *__restrict __entry),(__pargz,__pargz_len,__before,__entry))
#elif defined(__CRT_HAVE___argz_insert)
/* When `before' is `NULL', do the same as `argz_add(PARGZ, PARGZ_LEN, ENTRY)'
 * Otherwise, `before' should point somewhere into the middle, or to the start
 * of an existing argument entry, who's beginning will first be located, before
 * this function will then allocate additional memory to insert a copy of `entry'
 * such that the copy will appear before the entry pointed to by `before'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory
 * @return: EINVAL: The given `before' is either NULL, or apart of the given ARGZ */
__CREDIRECT(__ATTR_NONNULL((1, 2, 4)),error_t,__NOTHROW_NCX,argz_insert,(char **__restrict __pargz, size_t *__restrict __pargz_len, char *__before, char const *__restrict __entry),__argz_insert,(__pargz,__pargz_len,__before,__entry))
#elif defined(__CRT_HAVE_realloc)
#include <local/argz/argz_insert.h>
/* When `before' is `NULL', do the same as `argz_add(PARGZ, PARGZ_LEN, ENTRY)'
 * Otherwise, `before' should point somewhere into the middle, or to the start
 * of an existing argument entry, who's beginning will first be located, before
 * this function will then allocate additional memory to insert a copy of `entry'
 * such that the copy will appear before the entry pointed to by `before'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory
 * @return: EINVAL: The given `before' is either NULL, or apart of the given ARGZ */
__NAMESPACE_LOCAL_USING_OR_IMPL(argz_insert, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 4)) error_t __NOTHROW_NCX(__LIBCCALL argz_insert)(char **__restrict __pargz, size_t *__restrict __pargz_len, char *__before, char const *__restrict __entry) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_insert))(__pargz, __pargz_len, __before, __entry); })
#endif /* ... */
#ifdef __CRT_HAVE_argz_insert
/* When `before' is `NULL', do the same as `argz_add(PARGZ, PARGZ_LEN, ENTRY)'
 * Otherwise, `before' should point somewhere into the middle, or to the start
 * of an existing argument entry, who's beginning will first be located, before
 * this function will then allocate additional memory to insert a copy of `entry'
 * such that the copy will appear before the entry pointed to by `before'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory
 * @return: EINVAL: The given `before' is either NULL, or apart of the given ARGZ */
__CREDIRECT(__ATTR_NONNULL((1, 2, 4)),error_t,__NOTHROW_NCX,__argz_insert,(char **__restrict __pargz, size_t *__restrict __pargz_len, char *__before, char const *__restrict __entry),argz_insert,(__pargz,__pargz_len,__before,__entry))
#elif defined(__CRT_HAVE___argz_insert)
/* When `before' is `NULL', do the same as `argz_add(PARGZ, PARGZ_LEN, ENTRY)'
 * Otherwise, `before' should point somewhere into the middle, or to the start
 * of an existing argument entry, who's beginning will first be located, before
 * this function will then allocate additional memory to insert a copy of `entry'
 * such that the copy will appear before the entry pointed to by `before'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory
 * @return: EINVAL: The given `before' is either NULL, or apart of the given ARGZ */
__CDECLARE(__ATTR_NONNULL((1, 2, 4)),error_t,__NOTHROW_NCX,__argz_insert,(char **__restrict __pargz, size_t *__restrict __pargz_len, char *__before, char const *__restrict __entry),(__pargz,__pargz_len,__before,__entry))
#elif defined(__CRT_HAVE_realloc)
#include <local/argz/argz_insert.h>
/* When `before' is `NULL', do the same as `argz_add(PARGZ, PARGZ_LEN, ENTRY)'
 * Otherwise, `before' should point somewhere into the middle, or to the start
 * of an existing argument entry, who's beginning will first be located, before
 * this function will then allocate additional memory to insert a copy of `entry'
 * such that the copy will appear before the entry pointed to by `before'
 * @return: 0 :     Success
 * @return: ENOMEM: Insufficient heap memory
 * @return: EINVAL: The given `before' is either NULL, or apart of the given ARGZ */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 4)) error_t __NOTHROW_NCX(__LIBCCALL __argz_insert)(char **__restrict __pargz, size_t *__restrict __pargz_len, char *__before, char const *__restrict __entry) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_insert))(__pargz, __pargz_len, __before, __entry); }
#endif /* ... */
#ifdef __CRT_HAVE_argz_replace
/* Replace all matches of `STR' inside of every string or sub-string from `PARGZ...+=PARGZ_LEN'
 * with `WITH', and resize the ARGZ string if necessary. For every replacement that is done,
 * the given `REPLACE_COUNT' is incremented by one (if `REPLACE_COUNT' is non-NULL)
 * @return: 0:      Success
 * @return: ENOMEM: Insufficient heap memory (can only happen when `strlen(with) > strlen(str)',
 *                  but note that the GLibc implementation of this function is completely
 *                  unreadable and may be able to return this for other cases as well...) */
__CDECLARE(__ATTR_NONNULL((1, 2, 4)),error_t,__NOTHROW_NCX,argz_replace,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __str, char const *__restrict __with, unsigned int *__restrict __replace_count),(__pargz,__pargz_len,__str,__with,__replace_count))
#elif defined(__CRT_HAVE___argz_replace)
/* Replace all matches of `STR' inside of every string or sub-string from `PARGZ...+=PARGZ_LEN'
 * with `WITH', and resize the ARGZ string if necessary. For every replacement that is done,
 * the given `REPLACE_COUNT' is incremented by one (if `REPLACE_COUNT' is non-NULL)
 * @return: 0:      Success
 * @return: ENOMEM: Insufficient heap memory (can only happen when `strlen(with) > strlen(str)',
 *                  but note that the GLibc implementation of this function is completely
 *                  unreadable and may be able to return this for other cases as well...) */
__CREDIRECT(__ATTR_NONNULL((1, 2, 4)),error_t,__NOTHROW_NCX,argz_replace,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __str, char const *__restrict __with, unsigned int *__restrict __replace_count),__argz_replace,(__pargz,__pargz_len,__str,__with,__replace_count))
#elif defined(__CRT_HAVE_realloc) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree))
#include <local/argz/argz_replace.h>
/* Replace all matches of `STR' inside of every string or sub-string from `PARGZ...+=PARGZ_LEN'
 * with `WITH', and resize the ARGZ string if necessary. For every replacement that is done,
 * the given `REPLACE_COUNT' is incremented by one (if `REPLACE_COUNT' is non-NULL)
 * @return: 0:      Success
 * @return: ENOMEM: Insufficient heap memory (can only happen when `strlen(with) > strlen(str)',
 *                  but note that the GLibc implementation of this function is completely
 *                  unreadable and may be able to return this for other cases as well...) */
__NAMESPACE_LOCAL_USING_OR_IMPL(argz_replace, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 4)) error_t __NOTHROW_NCX(__LIBCCALL argz_replace)(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __str, char const *__restrict __with, unsigned int *__restrict __replace_count) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_replace))(__pargz, __pargz_len, __str, __with, __replace_count); })
#endif /* ... */
#ifdef __CRT_HAVE_argz_replace
/* Replace all matches of `STR' inside of every string or sub-string from `PARGZ...+=PARGZ_LEN'
 * with `WITH', and resize the ARGZ string if necessary. For every replacement that is done,
 * the given `REPLACE_COUNT' is incremented by one (if `REPLACE_COUNT' is non-NULL)
 * @return: 0:      Success
 * @return: ENOMEM: Insufficient heap memory (can only happen when `strlen(with) > strlen(str)',
 *                  but note that the GLibc implementation of this function is completely
 *                  unreadable and may be able to return this for other cases as well...) */
__CREDIRECT(__ATTR_NONNULL((1, 2, 4)),error_t,__NOTHROW_NCX,__argz_replace,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __str, char const *__restrict __with, unsigned int *__restrict __replace_count),argz_replace,(__pargz,__pargz_len,__str,__with,__replace_count))
#elif defined(__CRT_HAVE___argz_replace)
/* Replace all matches of `STR' inside of every string or sub-string from `PARGZ...+=PARGZ_LEN'
 * with `WITH', and resize the ARGZ string if necessary. For every replacement that is done,
 * the given `REPLACE_COUNT' is incremented by one (if `REPLACE_COUNT' is non-NULL)
 * @return: 0:      Success
 * @return: ENOMEM: Insufficient heap memory (can only happen when `strlen(with) > strlen(str)',
 *                  but note that the GLibc implementation of this function is completely
 *                  unreadable and may be able to return this for other cases as well...) */
__CDECLARE(__ATTR_NONNULL((1, 2, 4)),error_t,__NOTHROW_NCX,__argz_replace,(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __str, char const *__restrict __with, unsigned int *__restrict __replace_count),(__pargz,__pargz_len,__str,__with,__replace_count))
#elif defined(__CRT_HAVE_realloc) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree))
#include <local/argz/argz_replace.h>
/* Replace all matches of `STR' inside of every string or sub-string from `PARGZ...+=PARGZ_LEN'
 * with `WITH', and resize the ARGZ string if necessary. For every replacement that is done,
 * the given `REPLACE_COUNT' is incremented by one (if `REPLACE_COUNT' is non-NULL)
 * @return: 0:      Success
 * @return: ENOMEM: Insufficient heap memory (can only happen when `strlen(with) > strlen(str)',
 *                  but note that the GLibc implementation of this function is completely
 *                  unreadable and may be able to return this for other cases as well...) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 4)) error_t __NOTHROW_NCX(__LIBCCALL __argz_replace)(char **__restrict __pargz, size_t *__restrict __pargz_len, char const *__restrict __str, char const *__restrict __with, unsigned int *__restrict __replace_count) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_replace))(__pargz, __pargz_len, __str, __with, __replace_count); }
#endif /* ... */
#ifdef __CRT_HAVE_argz_next
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ARGZ_H_PROTO)
extern "C++" {
/* Iterate the individual strings that make up a given ARGZ vector.
 * This function is intended to be used in one of 2 ways:
 * >> char *my_entry = NULL;
 * >> while ((my_entry = argz_next(argz, argz_len, my_entry)) != NULL)
 * >>     handle_entry(my_entry);
 * or alternatively (if you like bloat):
 * >> char *entry;
 * >> for (entry = argz_len ? argz : NULL; entry != NULL;
 * >>      entry = argz_next(argz, argz_len, entry))
 * >>     handle_entry(my_entry);
 * Note that GLibc documents the second usage case slightly different, and
 * writes `for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))`,
 * thus assuming that an empty ARGZ string (i.e. `argz_len == 0') always has its
 * base pointer set to `NULL' (which isn't something consistently enforced, or
 * required by any of the other APIs, so I'd just suggest you use the first variant)
 *
 * Behavior:
 *  - When entry is `NULL', `return argz_len ? argz : NULL'
 *  - If `entry' points at, or past the end of ARGZ, return NULL
 *  - If the successor of `entry' points at, or past the end of ARGZ, return NULL
 *  - Return the successor of `entry' (i.e. `strend(entry) + 1') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,char *,__NOTHROW_NCX,argz_next,(char *__restrict __argz, size_t __argz_len, char *__restrict __entry),argz_next,(__argz,__argz_len,__entry))
/* Iterate the individual strings that make up a given ARGZ vector.
 * This function is intended to be used in one of 2 ways:
 * >> char *my_entry = NULL;
 * >> while ((my_entry = argz_next(argz, argz_len, my_entry)) != NULL)
 * >>     handle_entry(my_entry);
 * or alternatively (if you like bloat):
 * >> char *entry;
 * >> for (entry = argz_len ? argz : NULL; entry != NULL;
 * >>      entry = argz_next(argz, argz_len, entry))
 * >>     handle_entry(my_entry);
 * Note that GLibc documents the second usage case slightly different, and
 * writes `for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))`,
 * thus assuming that an empty ARGZ string (i.e. `argz_len == 0') always has its
 * base pointer set to `NULL' (which isn't something consistently enforced, or
 * required by any of the other APIs, so I'd just suggest you use the first variant)
 *
 * Behavior:
 *  - When entry is `NULL', `return argz_len ? argz : NULL'
 *  - If `entry' points at, or past the end of ARGZ, return NULL
 *  - If the successor of `entry' points at, or past the end of ARGZ, return NULL
 *  - Return the successor of `entry' (i.e. `strend(entry) + 1') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,char const *,__NOTHROW_NCX,argz_next,(char const *__restrict __argz, size_t __argz_len, char const *__restrict __entry),argz_next,(__argz,__argz_len,__entry))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ARGZ_H_PROTO */
/* Iterate the individual strings that make up a given ARGZ vector.
 * This function is intended to be used in one of 2 ways:
 * >> char *my_entry = NULL;
 * >> while ((my_entry = argz_next(argz, argz_len, my_entry)) != NULL)
 * >>     handle_entry(my_entry);
 * or alternatively (if you like bloat):
 * >> char *entry;
 * >> for (entry = argz_len ? argz : NULL; entry != NULL;
 * >>      entry = argz_next(argz, argz_len, entry))
 * >>     handle_entry(my_entry);
 * Note that GLibc documents the second usage case slightly different, and
 * writes `for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))`,
 * thus assuming that an empty ARGZ string (i.e. `argz_len == 0') always has its
 * base pointer set to `NULL' (which isn't something consistently enforced, or
 * required by any of the other APIs, so I'd just suggest you use the first variant)
 *
 * Behavior:
 *  - When entry is `NULL', `return argz_len ? argz : NULL'
 *  - If `entry' points at, or past the end of ARGZ, return NULL
 *  - If the successor of `entry' points at, or past the end of ARGZ, return NULL
 *  - Return the successor of `entry' (i.e. `strend(entry) + 1') */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,char *,__NOTHROW_NCX,argz_next,(char const *__restrict __argz, size_t __argz_len, char const *__restrict __entry),(__argz,__argz_len,__entry))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ARGZ_H_PROTO */
#elif defined(__CRT_HAVE___argz_next)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ARGZ_H_PROTO)
extern "C++" {
/* Iterate the individual strings that make up a given ARGZ vector.
 * This function is intended to be used in one of 2 ways:
 * >> char *my_entry = NULL;
 * >> while ((my_entry = argz_next(argz, argz_len, my_entry)) != NULL)
 * >>     handle_entry(my_entry);
 * or alternatively (if you like bloat):
 * >> char *entry;
 * >> for (entry = argz_len ? argz : NULL; entry != NULL;
 * >>      entry = argz_next(argz, argz_len, entry))
 * >>     handle_entry(my_entry);
 * Note that GLibc documents the second usage case slightly different, and
 * writes `for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))`,
 * thus assuming that an empty ARGZ string (i.e. `argz_len == 0') always has its
 * base pointer set to `NULL' (which isn't something consistently enforced, or
 * required by any of the other APIs, so I'd just suggest you use the first variant)
 *
 * Behavior:
 *  - When entry is `NULL', `return argz_len ? argz : NULL'
 *  - If `entry' points at, or past the end of ARGZ, return NULL
 *  - If the successor of `entry' points at, or past the end of ARGZ, return NULL
 *  - Return the successor of `entry' (i.e. `strend(entry) + 1') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,char *,__NOTHROW_NCX,argz_next,(char *__restrict __argz, size_t __argz_len, char *__restrict __entry),__argz_next,(__argz,__argz_len,__entry))
/* Iterate the individual strings that make up a given ARGZ vector.
 * This function is intended to be used in one of 2 ways:
 * >> char *my_entry = NULL;
 * >> while ((my_entry = argz_next(argz, argz_len, my_entry)) != NULL)
 * >>     handle_entry(my_entry);
 * or alternatively (if you like bloat):
 * >> char *entry;
 * >> for (entry = argz_len ? argz : NULL; entry != NULL;
 * >>      entry = argz_next(argz, argz_len, entry))
 * >>     handle_entry(my_entry);
 * Note that GLibc documents the second usage case slightly different, and
 * writes `for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))`,
 * thus assuming that an empty ARGZ string (i.e. `argz_len == 0') always has its
 * base pointer set to `NULL' (which isn't something consistently enforced, or
 * required by any of the other APIs, so I'd just suggest you use the first variant)
 *
 * Behavior:
 *  - When entry is `NULL', `return argz_len ? argz : NULL'
 *  - If `entry' points at, or past the end of ARGZ, return NULL
 *  - If the successor of `entry' points at, or past the end of ARGZ, return NULL
 *  - Return the successor of `entry' (i.e. `strend(entry) + 1') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,char const *,__NOTHROW_NCX,argz_next,(char const *__restrict __argz, size_t __argz_len, char const *__restrict __entry),__argz_next,(__argz,__argz_len,__entry))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ARGZ_H_PROTO */
/* Iterate the individual strings that make up a given ARGZ vector.
 * This function is intended to be used in one of 2 ways:
 * >> char *my_entry = NULL;
 * >> while ((my_entry = argz_next(argz, argz_len, my_entry)) != NULL)
 * >>     handle_entry(my_entry);
 * or alternatively (if you like bloat):
 * >> char *entry;
 * >> for (entry = argz_len ? argz : NULL; entry != NULL;
 * >>      entry = argz_next(argz, argz_len, entry))
 * >>     handle_entry(my_entry);
 * Note that GLibc documents the second usage case slightly different, and
 * writes `for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))`,
 * thus assuming that an empty ARGZ string (i.e. `argz_len == 0') always has its
 * base pointer set to `NULL' (which isn't something consistently enforced, or
 * required by any of the other APIs, so I'd just suggest you use the first variant)
 *
 * Behavior:
 *  - When entry is `NULL', `return argz_len ? argz : NULL'
 *  - If `entry' points at, or past the end of ARGZ, return NULL
 *  - If the successor of `entry' points at, or past the end of ARGZ, return NULL
 *  - Return the successor of `entry' (i.e. `strend(entry) + 1') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,char *,__NOTHROW_NCX,argz_next,(char const *__restrict __argz, size_t __argz_len, char const *__restrict __entry),__argz_next,(__argz,__argz_len,__entry))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ARGZ_H_PROTO */
#else /* ... */
#include <local/argz/argz_next.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ARGZ_H_PROTO)
extern "C++" {
/* Iterate the individual strings that make up a given ARGZ vector.
 * This function is intended to be used in one of 2 ways:
 * >> char *my_entry = NULL;
 * >> while ((my_entry = argz_next(argz, argz_len, my_entry)) != NULL)
 * >>     handle_entry(my_entry);
 * or alternatively (if you like bloat):
 * >> char *entry;
 * >> for (entry = argz_len ? argz : NULL; entry != NULL;
 * >>      entry = argz_next(argz, argz_len, entry))
 * >>     handle_entry(my_entry);
 * Note that GLibc documents the second usage case slightly different, and
 * writes `for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))`,
 * thus assuming that an empty ARGZ string (i.e. `argz_len == 0') always has its
 * base pointer set to `NULL' (which isn't something consistently enforced, or
 * required by any of the other APIs, so I'd just suggest you use the first variant)
 *
 * Behavior:
 *  - When entry is `NULL', `return argz_len ? argz : NULL'
 *  - If `entry' points at, or past the end of ARGZ, return NULL
 *  - If the successor of `entry' points at, or past the end of ARGZ, return NULL
 *  - Return the successor of `entry' (i.e. `strend(entry) + 1') */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL argz_next)(char *__restrict __argz, size_t __argz_len, char *__restrict __entry) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_next))(__argz, __argz_len, __entry); }
/* Iterate the individual strings that make up a given ARGZ vector.
 * This function is intended to be used in one of 2 ways:
 * >> char *my_entry = NULL;
 * >> while ((my_entry = argz_next(argz, argz_len, my_entry)) != NULL)
 * >>     handle_entry(my_entry);
 * or alternatively (if you like bloat):
 * >> char *entry;
 * >> for (entry = argz_len ? argz : NULL; entry != NULL;
 * >>      entry = argz_next(argz, argz_len, entry))
 * >>     handle_entry(my_entry);
 * Note that GLibc documents the second usage case slightly different, and
 * writes `for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))`,
 * thus assuming that an empty ARGZ string (i.e. `argz_len == 0') always has its
 * base pointer set to `NULL' (which isn't something consistently enforced, or
 * required by any of the other APIs, so I'd just suggest you use the first variant)
 *
 * Behavior:
 *  - When entry is `NULL', `return argz_len ? argz : NULL'
 *  - If `entry' points at, or past the end of ARGZ, return NULL
 *  - If the successor of `entry' points at, or past the end of ARGZ, return NULL
 *  - Return the successor of `entry' (i.e. `strend(entry) + 1') */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED char const *__NOTHROW_NCX(__LIBCCALL argz_next)(char const *__restrict __argz, size_t __argz_len, char const *__restrict __entry) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_next))(__argz, __argz_len, __entry); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ARGZ_H_PROTO */
/* Iterate the individual strings that make up a given ARGZ vector.
 * This function is intended to be used in one of 2 ways:
 * >> char *my_entry = NULL;
 * >> while ((my_entry = argz_next(argz, argz_len, my_entry)) != NULL)
 * >>     handle_entry(my_entry);
 * or alternatively (if you like bloat):
 * >> char *entry;
 * >> for (entry = argz_len ? argz : NULL; entry != NULL;
 * >>      entry = argz_next(argz, argz_len, entry))
 * >>     handle_entry(my_entry);
 * Note that GLibc documents the second usage case slightly different, and
 * writes `for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))`,
 * thus assuming that an empty ARGZ string (i.e. `argz_len == 0') always has its
 * base pointer set to `NULL' (which isn't something consistently enforced, or
 * required by any of the other APIs, so I'd just suggest you use the first variant)
 *
 * Behavior:
 *  - When entry is `NULL', `return argz_len ? argz : NULL'
 *  - If `entry' points at, or past the end of ARGZ, return NULL
 *  - If the successor of `entry' points at, or past the end of ARGZ, return NULL
 *  - Return the successor of `entry' (i.e. `strend(entry) + 1') */
__NAMESPACE_LOCAL_USING_OR_IMPL(argz_next, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL argz_next)(char const *__restrict __argz, size_t __argz_len, char const *__restrict __entry) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_next))(__argz, __argz_len, __entry); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ARGZ_H_PROTO */
#endif /* !... */
#ifdef __CRT_HAVE_argz_next
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ARGZ_H_PROTO)
extern "C++" {
/* Iterate the individual strings that make up a given ARGZ vector.
 * This function is intended to be used in one of 2 ways:
 * >> char *my_entry = NULL;
 * >> while ((my_entry = argz_next(argz, argz_len, my_entry)) != NULL)
 * >>     handle_entry(my_entry);
 * or alternatively (if you like bloat):
 * >> char *entry;
 * >> for (entry = argz_len ? argz : NULL; entry != NULL;
 * >>      entry = argz_next(argz, argz_len, entry))
 * >>     handle_entry(my_entry);
 * Note that GLibc documents the second usage case slightly different, and
 * writes `for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))`,
 * thus assuming that an empty ARGZ string (i.e. `argz_len == 0') always has its
 * base pointer set to `NULL' (which isn't something consistently enforced, or
 * required by any of the other APIs, so I'd just suggest you use the first variant)
 *
 * Behavior:
 *  - When entry is `NULL', `return argz_len ? argz : NULL'
 *  - If `entry' points at, or past the end of ARGZ, return NULL
 *  - If the successor of `entry' points at, or past the end of ARGZ, return NULL
 *  - Return the successor of `entry' (i.e. `strend(entry) + 1') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,char *,__NOTHROW_NCX,__argz_next,(char *__restrict __argz, size_t __argz_len, char *__restrict __entry),argz_next,(__argz,__argz_len,__entry))
/* Iterate the individual strings that make up a given ARGZ vector.
 * This function is intended to be used in one of 2 ways:
 * >> char *my_entry = NULL;
 * >> while ((my_entry = argz_next(argz, argz_len, my_entry)) != NULL)
 * >>     handle_entry(my_entry);
 * or alternatively (if you like bloat):
 * >> char *entry;
 * >> for (entry = argz_len ? argz : NULL; entry != NULL;
 * >>      entry = argz_next(argz, argz_len, entry))
 * >>     handle_entry(my_entry);
 * Note that GLibc documents the second usage case slightly different, and
 * writes `for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))`,
 * thus assuming that an empty ARGZ string (i.e. `argz_len == 0') always has its
 * base pointer set to `NULL' (which isn't something consistently enforced, or
 * required by any of the other APIs, so I'd just suggest you use the first variant)
 *
 * Behavior:
 *  - When entry is `NULL', `return argz_len ? argz : NULL'
 *  - If `entry' points at, or past the end of ARGZ, return NULL
 *  - If the successor of `entry' points at, or past the end of ARGZ, return NULL
 *  - Return the successor of `entry' (i.e. `strend(entry) + 1') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,char const *,__NOTHROW_NCX,__argz_next,(char const *__restrict __argz, size_t __argz_len, char const *__restrict __entry),argz_next,(__argz,__argz_len,__entry))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ARGZ_H_PROTO */
/* Iterate the individual strings that make up a given ARGZ vector.
 * This function is intended to be used in one of 2 ways:
 * >> char *my_entry = NULL;
 * >> while ((my_entry = argz_next(argz, argz_len, my_entry)) != NULL)
 * >>     handle_entry(my_entry);
 * or alternatively (if you like bloat):
 * >> char *entry;
 * >> for (entry = argz_len ? argz : NULL; entry != NULL;
 * >>      entry = argz_next(argz, argz_len, entry))
 * >>     handle_entry(my_entry);
 * Note that GLibc documents the second usage case slightly different, and
 * writes `for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))`,
 * thus assuming that an empty ARGZ string (i.e. `argz_len == 0') always has its
 * base pointer set to `NULL' (which isn't something consistently enforced, or
 * required by any of the other APIs, so I'd just suggest you use the first variant)
 *
 * Behavior:
 *  - When entry is `NULL', `return argz_len ? argz : NULL'
 *  - If `entry' points at, or past the end of ARGZ, return NULL
 *  - If the successor of `entry' points at, or past the end of ARGZ, return NULL
 *  - Return the successor of `entry' (i.e. `strend(entry) + 1') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,char *,__NOTHROW_NCX,__argz_next,(char const *__restrict __argz, size_t __argz_len, char const *__restrict __entry),argz_next,(__argz,__argz_len,__entry))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ARGZ_H_PROTO */
#elif defined(__CRT_HAVE___argz_next)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ARGZ_H_PROTO)
extern "C++" {
/* Iterate the individual strings that make up a given ARGZ vector.
 * This function is intended to be used in one of 2 ways:
 * >> char *my_entry = NULL;
 * >> while ((my_entry = argz_next(argz, argz_len, my_entry)) != NULL)
 * >>     handle_entry(my_entry);
 * or alternatively (if you like bloat):
 * >> char *entry;
 * >> for (entry = argz_len ? argz : NULL; entry != NULL;
 * >>      entry = argz_next(argz, argz_len, entry))
 * >>     handle_entry(my_entry);
 * Note that GLibc documents the second usage case slightly different, and
 * writes `for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))`,
 * thus assuming that an empty ARGZ string (i.e. `argz_len == 0') always has its
 * base pointer set to `NULL' (which isn't something consistently enforced, or
 * required by any of the other APIs, so I'd just suggest you use the first variant)
 *
 * Behavior:
 *  - When entry is `NULL', `return argz_len ? argz : NULL'
 *  - If `entry' points at, or past the end of ARGZ, return NULL
 *  - If the successor of `entry' points at, or past the end of ARGZ, return NULL
 *  - Return the successor of `entry' (i.e. `strend(entry) + 1') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,char *,__NOTHROW_NCX,__argz_next,(char *__restrict __argz, size_t __argz_len, char *__restrict __entry),__argz_next,(__argz,__argz_len,__entry))
/* Iterate the individual strings that make up a given ARGZ vector.
 * This function is intended to be used in one of 2 ways:
 * >> char *my_entry = NULL;
 * >> while ((my_entry = argz_next(argz, argz_len, my_entry)) != NULL)
 * >>     handle_entry(my_entry);
 * or alternatively (if you like bloat):
 * >> char *entry;
 * >> for (entry = argz_len ? argz : NULL; entry != NULL;
 * >>      entry = argz_next(argz, argz_len, entry))
 * >>     handle_entry(my_entry);
 * Note that GLibc documents the second usage case slightly different, and
 * writes `for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))`,
 * thus assuming that an empty ARGZ string (i.e. `argz_len == 0') always has its
 * base pointer set to `NULL' (which isn't something consistently enforced, or
 * required by any of the other APIs, so I'd just suggest you use the first variant)
 *
 * Behavior:
 *  - When entry is `NULL', `return argz_len ? argz : NULL'
 *  - If `entry' points at, or past the end of ARGZ, return NULL
 *  - If the successor of `entry' points at, or past the end of ARGZ, return NULL
 *  - Return the successor of `entry' (i.e. `strend(entry) + 1') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,char const *,__NOTHROW_NCX,__argz_next,(char const *__restrict __argz, size_t __argz_len, char const *__restrict __entry),__argz_next,(__argz,__argz_len,__entry))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ARGZ_H_PROTO */
/* Iterate the individual strings that make up a given ARGZ vector.
 * This function is intended to be used in one of 2 ways:
 * >> char *my_entry = NULL;
 * >> while ((my_entry = argz_next(argz, argz_len, my_entry)) != NULL)
 * >>     handle_entry(my_entry);
 * or alternatively (if you like bloat):
 * >> char *entry;
 * >> for (entry = argz_len ? argz : NULL; entry != NULL;
 * >>      entry = argz_next(argz, argz_len, entry))
 * >>     handle_entry(my_entry);
 * Note that GLibc documents the second usage case slightly different, and
 * writes `for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))`,
 * thus assuming that an empty ARGZ string (i.e. `argz_len == 0') always has its
 * base pointer set to `NULL' (which isn't something consistently enforced, or
 * required by any of the other APIs, so I'd just suggest you use the first variant)
 *
 * Behavior:
 *  - When entry is `NULL', `return argz_len ? argz : NULL'
 *  - If `entry' points at, or past the end of ARGZ, return NULL
 *  - If the successor of `entry' points at, or past the end of ARGZ, return NULL
 *  - Return the successor of `entry' (i.e. `strend(entry) + 1') */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,char *,__NOTHROW_NCX,__argz_next,(char const *__restrict __argz, size_t __argz_len, char const *__restrict __entry),(__argz,__argz_len,__entry))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ARGZ_H_PROTO */
#else /* ... */
#include <local/argz/argz_next.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_ARGZ_H_PROTO)
extern "C++" {
/* Iterate the individual strings that make up a given ARGZ vector.
 * This function is intended to be used in one of 2 ways:
 * >> char *my_entry = NULL;
 * >> while ((my_entry = argz_next(argz, argz_len, my_entry)) != NULL)
 * >>     handle_entry(my_entry);
 * or alternatively (if you like bloat):
 * >> char *entry;
 * >> for (entry = argz_len ? argz : NULL; entry != NULL;
 * >>      entry = argz_next(argz, argz_len, entry))
 * >>     handle_entry(my_entry);
 * Note that GLibc documents the second usage case slightly different, and
 * writes `for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))`,
 * thus assuming that an empty ARGZ string (i.e. `argz_len == 0') always has its
 * base pointer set to `NULL' (which isn't something consistently enforced, or
 * required by any of the other APIs, so I'd just suggest you use the first variant)
 *
 * Behavior:
 *  - When entry is `NULL', `return argz_len ? argz : NULL'
 *  - If `entry' points at, or past the end of ARGZ, return NULL
 *  - If the successor of `entry' points at, or past the end of ARGZ, return NULL
 *  - Return the successor of `entry' (i.e. `strend(entry) + 1') */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL __argz_next)(char *__restrict __argz, size_t __argz_len, char *__restrict __entry) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_next))(__argz, __argz_len, __entry); }
/* Iterate the individual strings that make up a given ARGZ vector.
 * This function is intended to be used in one of 2 ways:
 * >> char *my_entry = NULL;
 * >> while ((my_entry = argz_next(argz, argz_len, my_entry)) != NULL)
 * >>     handle_entry(my_entry);
 * or alternatively (if you like bloat):
 * >> char *entry;
 * >> for (entry = argz_len ? argz : NULL; entry != NULL;
 * >>      entry = argz_next(argz, argz_len, entry))
 * >>     handle_entry(my_entry);
 * Note that GLibc documents the second usage case slightly different, and
 * writes `for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))`,
 * thus assuming that an empty ARGZ string (i.e. `argz_len == 0') always has its
 * base pointer set to `NULL' (which isn't something consistently enforced, or
 * required by any of the other APIs, so I'd just suggest you use the first variant)
 *
 * Behavior:
 *  - When entry is `NULL', `return argz_len ? argz : NULL'
 *  - If `entry' points at, or past the end of ARGZ, return NULL
 *  - If the successor of `entry' points at, or past the end of ARGZ, return NULL
 *  - Return the successor of `entry' (i.e. `strend(entry) + 1') */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED char const *__NOTHROW_NCX(__LIBCCALL __argz_next)(char const *__restrict __argz, size_t __argz_len, char const *__restrict __entry) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_next))(__argz, __argz_len, __entry); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_ARGZ_H_PROTO */
/* Iterate the individual strings that make up a given ARGZ vector.
 * This function is intended to be used in one of 2 ways:
 * >> char *my_entry = NULL;
 * >> while ((my_entry = argz_next(argz, argz_len, my_entry)) != NULL)
 * >>     handle_entry(my_entry);
 * or alternatively (if you like bloat):
 * >> char *entry;
 * >> for (entry = argz_len ? argz : NULL; entry != NULL;
 * >>      entry = argz_next(argz, argz_len, entry))
 * >>     handle_entry(my_entry);
 * Note that GLibc documents the second usage case slightly different, and
 * writes `for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))`,
 * thus assuming that an empty ARGZ string (i.e. `argz_len == 0') always has its
 * base pointer set to `NULL' (which isn't something consistently enforced, or
 * required by any of the other APIs, so I'd just suggest you use the first variant)
 *
 * Behavior:
 *  - When entry is `NULL', `return argz_len ? argz : NULL'
 *  - If `entry' points at, or past the end of ARGZ, return NULL
 *  - If the successor of `entry' points at, or past the end of ARGZ, return NULL
 *  - Return the successor of `entry' (i.e. `strend(entry) + 1') */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL __argz_next)(char const *__restrict __argz, size_t __argz_len, char const *__restrict __entry) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(argz_next))(__argz, __argz_len, __entry); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_ARGZ_H_PROTO */
#endif /* !... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_ARGZ_H */
