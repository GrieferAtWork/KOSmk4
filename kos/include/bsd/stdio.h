/* HASH CRC-32:0x9f1242d7 */
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

#ifndef __fmtcheck_defined
#define __fmtcheck_defined
#ifdef __CRT_HAVE_fmtcheck
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
#else /* __CRT_HAVE_fmtcheck */
#include <libc/local/stdio/fmtcheck.h>
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
__NAMESPACE_LOCAL_USING_OR_IMPL(fmtcheck, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((2)) __ATTR_FORMAT_ARG(2) char const *__NOTHROW_NCX(__LIBCCALL fmtcheck)(char const *__user_format, char const *__good_format) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmtcheck))(__user_format, __good_format); })
#endif /* !__CRT_HAVE_fmtcheck */
#endif /* !__fmtcheck_defined */
#if !defined(__fgetln_defined) && defined(__CRT_HAVE_fgetln)
#define __fgetln_defined
/* >> fgetln(3)
 * A slightly more convenient (but way less portable) alternative to `fgets(3)'
 * This function automatically malloc's a  buffer of sufficient length for  the
 * next line in the given `stream', and stores its length in `*lenp'
 * NOTE: KOS adds the following extensions to this function:
 *  - We guaranty that "return[*lenp] == '\0'" upon a non-NULL return
 *  - You may pass `lenp == NULL', which simply ignores that argument
 * @return: NULL: The EOF flag of `stream' is set (fix this with `clearerr(3)'),
 *                or the underlying file has been fully read.
 * @return: * :   Pointer to an  automatically malloc'd  buffer (to-be  freed
 *                by  fclose(3)  once you  call  that function  on  the given
 *                `stream'). The buffer is re-used in subsequence invocations
 *                of this function, and documentation states that it may also
 *                be invalidated during any  other I/O operation relating  to
 *                `stream', tough this isn't the case under KOS. */
__CDECLARE(__ATTR_WUNUSED __ATTR_ACCESS_RW(1),char *,__NOTHROW_NCX,fgetln,(__FILE *__restrict __stream, __SIZE_TYPE__ *__restrict __lenp),(__stream,__lenp))
#endif /* !__fgetln_defined && __CRT_HAVE_fgetln */
#ifndef __fpurge_defined
#define __fpurge_defined
#ifdef __CRT_HAVE___fpurge
/* >> __fpurge(3)
 * Discard all modified, but unwritten data from `stream', as  well
 * as  all unread data previously buffered, but not yet read. After
 * a call to this function, the next `fread(3)' or `fwrite(3)' will
 * start off from a blank state. */
__CREDIRECT_VOID(,__NOTHROW_NCX,fpurge,(__FILE *__stream),__fpurge,(__stream))
#elif defined(__CRT_HAVE_fpurge)
/* >> __fpurge(3)
 * Discard all modified, but unwritten data from `stream', as  well
 * as  all unread data previously buffered, but not yet read. After
 * a call to this function, the next `fread(3)' or `fwrite(3)' will
 * start off from a blank state. */
__CDECLARE_VOID(,__NOTHROW_NCX,fpurge,(__FILE *__stream),(__stream))
#else /* ... */
#undef __fpurge_defined
#endif /* !... */
#endif /* !__fpurge_defined */
#ifndef __funopen_defined
#define __funopen_defined
#if defined(__CRT_HAVE_funopen) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__
/* >> funopen(3), funopen64(3) */
__CDECLARE(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,funopen,(void const *__cookie, int (__LIBKCALL *__readfn)(void *__cookie, char *__buf, int __num_bytes), int (__LIBKCALL *__writefn)(void *__cookie, char const *__buf, int __num_bytes), off_t (__LIBKCALL *__seekfn)(void *__cookie, off_t __off, int __whence), int (__LIBKCALL *__closefn)(void *__cookie)),(__cookie,__readfn,__writefn,__seekfn,__closefn))
#elif defined(__CRT_HAVE_funopen64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__
/* >> funopen(3), funopen64(3) */
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_NCX,funopen,(void const *__cookie, int (__LIBKCALL *__readfn)(void *__cookie, char *__buf, int __num_bytes), int (__LIBKCALL *__writefn)(void *__cookie, char const *__buf, int __num_bytes), off_t (__LIBKCALL *__seekfn)(void *__cookie, off_t __off, int __whence), int (__LIBKCALL *__closefn)(void *__cookie)),funopen64,(__cookie,__readfn,__writefn,__seekfn,__closefn))
#else /* ... */
#include <hybrid/typecore.h>
#if (__SIZEOF_INT__ == __SIZEOF_SIZE_T__ && ((defined(__CRT_HAVE_funopen2) && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__) || (defined(__CRT_HAVE_funopen2_64) && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && ((defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2))))) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2) || defined(__CRT_HAVE_fopencookie) || defined(__CRT_HAVE_funopen64) || defined(__CRT_HAVE_funopen)))
#include <libc/local/stdio/funopen.h>
/* >> funopen(3), funopen64(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(funopen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __FILE *__NOTHROW_NCX(__LIBCCALL funopen)(void const *__cookie, int (__LIBKCALL *__readfn)(void *__cookie, char *__buf, int __num_bytes), int (__LIBKCALL *__writefn)(void *__cookie, char const *__buf, int __num_bytes), off_t (__LIBKCALL *__seekfn)(void *__cookie, off_t __off, int __whence), int (__LIBKCALL *__closefn)(void *__cookie)) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(funopen))(__cookie, __readfn, __writefn, __seekfn, __closefn); })
#else /* (__SIZEOF_INT__ == __SIZEOF_SIZE_T__ && ((__CRT_HAVE_funopen2 && __FS_SIZEOF(OFF) == __SIZEOF_OFF32_T__) || (__CRT_HAVE_funopen2_64 && __FS_SIZEOF(OFF) == __SIZEOF_OFF64_T__) || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && ((__CRT_HAVE_funopen2 && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || __CRT_HAVE_funopen2_64 || __CRT_HAVE_funopen2)))) || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_funopen2_64 || __CRT_HAVE_funopen2 || __CRT_HAVE_fopencookie || __CRT_HAVE_funopen64 || __CRT_HAVE_funopen)) */
#undef __funopen_defined
#endif /* (__SIZEOF_INT__ != __SIZEOF_SIZE_T__ || ((!__CRT_HAVE_funopen2 || __FS_SIZEOF(OFF) != __SIZEOF_OFF32_T__) && (!__CRT_HAVE_funopen2_64 || __FS_SIZEOF(OFF) != __SIZEOF_OFF64_T__) && ((!__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) || (!__CRT_HAVE_funopen2_64 && !__CRT_HAVE_funopen2)))) && ((!__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) || (!__CRT_HAVE_funopen2_64 && !__CRT_HAVE_funopen2 && !__CRT_HAVE_fopencookie && !__CRT_HAVE_funopen64 && !__CRT_HAVE_funopen)) */
#endif /* !... */
#endif /* !__funopen_defined */
#ifdef __funopen_defined
#define fropen(cookie, fn) funopen(cookie, fn, __NULLPTR, __NULLPTR, __NULLPTR)
#define fwopen(cookie, fn) funopen(cookie, __NULLPTR, fn, __NULLPTR, __NULLPTR)
#endif /* __funopen_defined */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BSD_STDIO_H */
