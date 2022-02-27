/* HASH CRC-32:0xb9093ba9 */
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
/* (#) Portability: Cygwin        (/newlib/libc/include/stdio_ext.h) */
/* (#) Portability: GNU C Library (/include/stdio_ext.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/stdio_ext.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/stdio_ext.h) */
/* (#) Portability: diet libc     (/include/stdio_ext.h) */
/* (#) Portability: libc6         (/include/stdio_ext.h) */
/* (#) Portability: musl libc     (/include/stdio_ext.h) */
/* (#) Portability: uClibc        (/include/stdio_ext.h) */
#ifndef _STDIO_EXT_H
#define _STDIO_EXT_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <stdio.h>
#include <kos/anno.h>
#include <asm/crt/stdio_ext.h>

__SYSDECL_BEGIN

/* Documentation taken from Glibc /usr/include/stdio_ext.h, before (some) being modified/extended. */
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
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

#if (defined(__FSETLOCKING_QUERY) || defined(__FSETLOCKING_INTERNAL) || \
     defined(__FSETLOCKING_BYCALLER))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __FSETLOCKING_QUERY
	FSETLOCKING_QUERY    = __FSETLOCKING_QUERY,    /* Query current state of the locking status. */
#endif /* __FSETLOCKING_QUERY */
#ifdef __FSETLOCKING_INTERNAL
	FSETLOCKING_INTERNAL = __FSETLOCKING_INTERNAL, /* The library protects all uses of the stream functions, except for uses
	                                                * of the *_unlocked  functions, by calls  equivalent to  `flockfile(3)'. */
#endif /* __FSETLOCKING_INTERNAL */
#ifdef __FSETLOCKING_BYCALLER
	FSETLOCKING_BYCALLER = __FSETLOCKING_BYCALLER  /* The user will take care of locking.
	                                                * This is the equivalent of `__USE_STDIO_UNLOCKED' on a per-file basis. */
#endif /* __FSETLOCKING_BYCALLER */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __FSETLOCKING_QUERY
#define FSETLOCKING_QUERY    FSETLOCKING_QUERY    /* Query current state of the locking status. */
#endif /* __FSETLOCKING_QUERY */
#ifdef __FSETLOCKING_INTERNAL
#define FSETLOCKING_INTERNAL FSETLOCKING_INTERNAL /* The library protects all uses of the stream functions, except for uses
                                                   * of the *_unlocked  functions, by calls  equivalent to  `flockfile(3)'. */
#endif /* __FSETLOCKING_INTERNAL */
#ifdef __FSETLOCKING_BYCALLER
#define FSETLOCKING_BYCALLER FSETLOCKING_BYCALLER /* The user will take care of locking.
                                                   * This is the equivalent of `__USE_STDIO_UNLOCKED' on a per-file basis. */
#endif /* __FSETLOCKING_BYCALLER */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __FSETLOCKING_QUERY
#define FSETLOCKING_QUERY    __FSETLOCKING_QUERY    /* Query current state of the locking status. */
#endif /* __FSETLOCKING_QUERY */
#ifdef __FSETLOCKING_INTERNAL
#define FSETLOCKING_INTERNAL __FSETLOCKING_INTERNAL /* The library protects all uses of the stream functions, except for uses
                                                     * of the *_unlocked  functions, by calls  equivalent to  `flockfile(3)'. */
#endif /* __FSETLOCKING_INTERNAL */
#ifdef __FSETLOCKING_BYCALLER
#define FSETLOCKING_BYCALLER __FSETLOCKING_BYCALLER /* The user will take care of locking.
                                                     * This is the equivalent of `__USE_STDIO_UNLOCKED' on a per-file basis. */
#endif /* __FSETLOCKING_BYCALLER */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */


#ifdef __CC__

/* >> __fbufsize(3)
 * Return the size of the buffer of `stream' in
 * bytes  currently in use  by the given stream */
__CDECLARE_OPT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__fbufsize,(__FILE __KOS_FIXED_CONST *__stream),(__stream))
/* >> __freading(3)
 * Return  non-zero value when  `stream' is opened readonly,
 * or if the last operation on `stream' was a read operation */
__CDECLARE_OPT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__freading,(__FILE __KOS_FIXED_CONST *__stream),(__stream))
/* >> __fwriting(3)
 * Return non-zero value when  `stream' is opened write-only  or
 * append-only, or if the last operation on `stream' was a write
 * operation */
__CDECLARE_OPT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__fwriting,(__FILE __KOS_FIXED_CONST *__stream),(__stream))
/* >> __freadable(3)
 * Return non-zero value when `stream' is not opened write-only or append-only */
__CDECLARE_OPT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__freadable,(__FILE __KOS_FIXED_CONST *__stream),(__stream))
/* >> __fwritable(3)
 * Return non-zero value when `stream' is not opened read-only */
__CDECLARE_OPT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__fwritable,(__FILE __KOS_FIXED_CONST *__stream),(__stream))
/* >> __flbf(3)
 * Return non-zero value when `stream' is line-buffered */
__CDECLARE_OPT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__flbf,(__FILE *__stream),(__stream))
#ifdef __CRT_HAVE___fpurge
/* >> __fpurge(3)
 * Discard all pending buffered I/O on `stream' */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__fpurge,(__FILE *__stream),(__stream))
#elif defined(__CRT_HAVE_fpurge)
/* >> __fpurge(3)
 * Discard all pending buffered I/O on `stream' */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__fpurge,(__FILE *__stream),fpurge,(__stream))
#endif /* ... */
/* >> __fpending(3)
 * Return amount of output in bytes pending on a `stream' */
__CDECLARE_OPT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,__fpending,(__FILE __KOS_FIXED_CONST *__stream),(__stream))
#ifdef __CRT_HAVE__flushlbf
/* >> _flushlbf(3)
 * Flush all line-buffered files */
__CDECLARE_VOID(,__THROWING,_flushlbf,(void),())
#elif defined(__CRT_HAVE__IO_flush_all_linebuffered)
/* >> _flushlbf(3)
 * Flush all line-buffered files */
__CREDIRECT_VOID(,__THROWING,_flushlbf,(void),_IO_flush_all_linebuffered,())
#endif /* ... */
/* >> __fsetlocking(3)
 * Set locking status of `stream' to `type'
 * @param: type: One of `FSETLOCKING_*' */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__fsetlocking,(__FILE *__stream, int __type),(__stream,__type))
/* >> __fseterr(3)
 * Set the error indicator for the given `stream' (s.a. `ferror()') */
__CDECLARE_VOID_OPT(__ATTR_NONNULL((1)),__NOTHROW_NCX,__fseterr,(__FILE *__stream),(__stream))
#endif /* __CC__ */

/* Never actually needed */
#ifndef enable_extended_FILE_stdio
#define enable_extended_FILE_stdio(fd, act) 0
#endif /* !enable_extended_FILE_stdio */

__SYSDECL_END

#endif /* !_STDIO_EXT_H */
