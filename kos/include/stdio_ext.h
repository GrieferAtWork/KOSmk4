/* HASH CRC-32:0x4c1ec430 */
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
#ifndef _STDIO_EXT_H
#define _STDIO_EXT_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <stdio.h>

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

#undef FSETLOCKING_QUERY
#undef FSETLOCKING_INTERNAL
#undef FSETLOCKING_BYCALLER
#ifdef __CC__
enum {
	FSETLOCKING_QUERY    = 0, /* Query current state of the locking status. */
	FSETLOCKING_INTERNAL = 1, /* The library protects all uses of the stream functions, except for
	                           * uses of the *_unlocked functions, by calls equivalent to flockfile(). */
	FSETLOCKING_BYCALLER = 2 /* The user will take care of locking.
	                          * This is the equivalent of `__USE_STDIO_UNLOCKED' on a per-file basis. */
};
#endif /* __CC__ */
#ifdef __COMPILER_PREFERR_ENUMS
#define FSETLOCKING_QUERY    FSETLOCKING_QUERY    /* Query current state of the locking status. */
#define FSETLOCKING_INTERNAL FSETLOCKING_INTERNAL /* The library protects all uses of the stream functions, except for
                                                   * uses of the *_unlocked functions, by calls equivalent to flockfile(). */
#define FSETLOCKING_BYCALLER FSETLOCKING_BYCALLER /* The user will take care of locking.
                                                   * This is the equivalent of `__USE_STDIO_UNLOCKED' on a per-file basis. */
#else /* __COMPILER_PREFERR_ENUMS */
#define FSETLOCKING_QUERY    0 /* Query current state of the locking status. */
#define FSETLOCKING_INTERNAL 1 /* The library protects all uses of the stream functions, except for
                                * uses of the *_unlocked functions, by calls equivalent to flockfile(). */
#define FSETLOCKING_BYCALLER 2 /* The user will take care of locking.
                                * This is the equivalent of `__USE_STDIO_UNLOCKED' on a per-file basis. */
#endif /* !__COMPILER_PREFERR_ENUMS */

#ifdef __CC__

#if defined(__CRT_HAVE___fbufsize)
/* Return the size of the buffer of FP in bytes currently in use by the given stream */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__fbufsize,(__FILE *__fp),(__fp))
#endif /* __fbufsize... */
#if defined(__CRT_HAVE___freading)
/* Return non-zero value iff the stream FP is opened readonly,
 * or if the last operation on the stream was a read operation */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__freading,(__FILE *__fp),(__fp))
#endif /* __freading... */
#if defined(__CRT_HAVE___fwriting)
/* Return non-zero value iff the stream FP is opened write-only or
 * append-only, or if the last operation on the stream was a write
 * operation */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__fwriting,(__FILE *__fp),(__fp))
#endif /* __fwriting... */
#if defined(__CRT_HAVE___freadable)
/* Return non-zero value iff stream FP is not opened write-only or append-only */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__freadable,(__FILE *__fp),(__fp))
#endif /* __freadable... */
#if defined(__CRT_HAVE___fwritable)
/* Return non-zero value iff stream FP is not opened read-only */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__fwritable,(__FILE *__fp),(__fp))
#endif /* __fwritable... */
#if defined(__CRT_HAVE___flbf)
/* Return non-zero value iff the stream FP is line-buffered */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__flbf,(__FILE *__fp),(__fp))
#endif /* __flbf... */
#if defined(__CRT_HAVE___fpurge)
/* Discard all pending buffered I/O on the stream FP */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__fpurge,(__FILE *__fp),(__fp))
#endif /* __fpurge... */
#if defined(__CRT_HAVE___fpending)
/* Return amount of output in bytes pending on a stream FP */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,__fpending,(__FILE *__fp),(__fp))
#endif /* __fpending... */
#if defined(__CRT_HAVE__flushlbf)
/* Flush all line-buffered files */
__CDECLARE_VOID(,__NOTHROW_NCX,_flushlbf,(void),())
#endif /* _flushlbf... */
#if defined(__CRT_HAVE___fsetlocking)
/* Set locking status of stream FP to TYPE */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__fsetlocking,(__FILE *__fp, int __type),(__fp,__type))
#endif /* __fsetlocking... */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_STDIO_EXT_H */
