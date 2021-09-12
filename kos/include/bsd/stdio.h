/* HASH CRC-32:0x1bf93071 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: libbsd (/include/bsd/stdio.h) */
#ifndef _BSD_STDIO_H
#define _BSD_STDIO_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <stdio.h>
#include <features.h>
#include <bits/types.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef ____funopen_types_defined
#define ____funopen_types_defined 1
typedef int (__LIBKCALL *__funopen_readfn_t)(void *__cookie, char *__buf, int __num_bytes);
typedef int (__LIBKCALL *__funopen_writefn_t)(void *__cookie, char const *__buf, int __num_bytes);
typedef __FS_TYPE(off) (__LIBKCALL *__funopen_seekfn_t)(void *__cookie, __FS_TYPE(off) __off, int __whence);
typedef int (__LIBKCALL *__funopen_closefn_t)(void *__cookie);
#endif /* !____funopen_types_defined */

#if !defined(__fmtcheck_defined) && defined(__CRT_HAVE_fmtcheck)
#define __fmtcheck_defined 1
/* >> fmtcheck(3)
 * Check if `user_format' may be used as a drop-in replacement for `good_format'
 * in the context of a call to `printf(3)' (or `format_printf()'), such that all
 * contained format qualifiers reference the  same (or compatible) underlying  C
 * types, and in the same order.
 * If all of this is the  case, simply re-return `user_format'. Otherwise  (i.e.
 * when `user_format' isn't compatible with `good_format'), return `good_format'
 * instead. This function is meant to  be used to validate user-provided  printf
 * format strings before actually using them, after they've been read from  lang
 * config files: `printf(fmtcheck(get_user_fmt(), "%s %s"), "Foo", "Bar");' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((2)) __ATTR_FORMAT_ARG(2),char const *,__NOTHROW_NCX,fmtcheck,(char const *__user_format, char const *__good_format),(__user_format,__good_format))
#endif /* !__fmtcheck_defined && __CRT_HAVE_fmtcheck */
#if !defined(__fgetln_defined) && defined(__CRT_HAVE_fgetln)
#define __fgetln_defined 1
/* >> fgetln(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,fgetln,(__FILE *__restrict __fp, __SIZE_TYPE__ *__restrict __lenp),(__fp,__lenp))
#endif /* !__fgetln_defined && __CRT_HAVE_fgetln */
#ifndef __fpurge_defined
#define __fpurge_defined 1
#ifdef __CRT_HAVE___fpurge
/* >> __fpurge(3)
 * Discard all pending buffered I/O on `stream' */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,fpurge,(__FILE *__stream),__fpurge,(__stream))
#elif defined(__CRT_HAVE_fpurge)
/* >> __fpurge(3)
 * Discard all pending buffered I/O on `stream' */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,fpurge,(__FILE *__stream),(__stream))
#else /* ... */
#undef __fpurge_defined
#endif /* !... */
#endif /* !__fpurge_defined */
#ifndef __funopen_defined
#define __funopen_defined 1
#if defined(__CRT_HAVE_funopen) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__
/* >> funopen(3), funopen64(3) */
__CDECLARE(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,funopen,(void const *__cookie, __funopen_readfn_t __readfn, __funopen_writefn_t __writefn, __funopen_seekfn_t __seekfn, __funopen_closefn_t __closefn),(__cookie,__readfn,__writefn,__seekfn,__closefn))
#elif defined(__CRT_HAVE_funopen64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> funopen(3), funopen64(3) */
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,funopen,(void const *__cookie, __funopen_readfn_t __readfn, __funopen_writefn_t __writefn, __funopen_seekfn_t __seekfn, __funopen_closefn_t __closefn),funopen64,(__cookie,__readfn,__writefn,__seekfn,__closefn))
#else /* ... */
#include <hybrid/typecore.h>
#if (__SIZEOF_INT__ == __SIZEOF_SIZE_T__ && ((defined(__CRT_HAVE_funopen2) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__) || (defined(__CRT_HAVE_funopen2_64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && ((defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2))))) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2) || defined(__CRT_HAVE_fopencookie) || defined(__CRT_HAVE_funopen64) || defined(__CRT_HAVE_funopen)))
#include <libc/local/stdio/funopen.h>
/* >> funopen(3), funopen64(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(funopen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __FILE *__NOTHROW_NCX(__LIBCCALL funopen)(void const *__cookie, __funopen_readfn_t __readfn, __funopen_writefn_t __writefn, __funopen_seekfn_t __seekfn, __funopen_closefn_t __closefn) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(funopen)(__cookie, __readfn, __writefn, __seekfn, __closefn); })
#else /* (__SIZEOF_INT__ == __SIZEOF_SIZE_T__ && ((__CRT_HAVE_funopen2 && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__) || (__CRT_HAVE_funopen2_64 && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__) || ((__CRT_HAVE_malloc || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign) && ((__CRT_HAVE_funopen2 && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || __CRT_HAVE_funopen2_64 || __CRT_HAVE_funopen2)))) || ((__CRT_HAVE_malloc || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_funopen2_64 || __CRT_HAVE_funopen2 || __CRT_HAVE_fopencookie || __CRT_HAVE_funopen64 || __CRT_HAVE_funopen)) */
#undef __funopen_defined
#endif /* (__SIZEOF_INT__ != __SIZEOF_SIZE_T__ || ((!__CRT_HAVE_funopen2 || __FS_SIZEOF(OFF) != __SIZEOF_OFF32_T__) && (!__CRT_HAVE_funopen2_64 || __FS_SIZEOF(OFF) != __SIZEOF_OFF64_T__) && ((!__CRT_HAVE_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE_posix_memalign) || (!__CRT_HAVE_funopen2_64 && !__CRT_HAVE_funopen2)))) && ((!__CRT_HAVE_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE_posix_memalign) || (!__CRT_HAVE_funopen2_64 && !__CRT_HAVE_funopen2 && !__CRT_HAVE_fopencookie && !__CRT_HAVE_funopen64 && !__CRT_HAVE_funopen)) */
#endif /* !... */
#endif /* !__funopen_defined */
#ifdef __funopen_defined
#define fropen(cookie, fn) funopen(cookie, fn, __NULLPTR, __NULLPTR, __NULLPTR)
#define fwopen(cookie, fn) funopen(cookie, __NULLPTR, fn, __NULLPTR, __NULLPTR)
#endif /* __funopen_defined */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BSD_STDIO_H */
