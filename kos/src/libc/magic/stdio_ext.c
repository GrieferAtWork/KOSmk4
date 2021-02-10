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
%(c_prefix){
/* (#) Portability: Cygwin        (/newlib/libc/include/stdio_ext.h) */
/* (#) Portability: GNU C Library (/stdio-common/stdio_ext.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/stdio_ext.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/stdio_ext.h) */
/* (#) Portability: diet libc     (/include/stdio_ext.h) */
/* (#) Portability: musl libc     (/include/stdio_ext.h) */
/* (#) Portability: uClibc        (/include/stdio_ext.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.FILE.utility.ext")]

%{
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
	FSETLOCKING_INTERNAL = __FSETLOCKING_INTERNAL, /* The library protects  all uses  of the stream  functions, except  for
	                                                * uses of the *_unlocked functions, by calls equivalent to flockfile(). */
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
#define FSETLOCKING_INTERNAL FSETLOCKING_INTERNAL /* The library protects  all uses  of the stream  functions, except  for
                                                   * uses of the *_unlocked functions, by calls equivalent to flockfile(). */
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
#define FSETLOCKING_INTERNAL __FSETLOCKING_INTERNAL /* The library protects  all uses  of the stream  functions, except  for
                                                     * uses of the *_unlocked functions, by calls equivalent to flockfile(). */
#endif /* __FSETLOCKING_INTERNAL */
#ifdef __FSETLOCKING_BYCALLER
#define FSETLOCKING_BYCALLER __FSETLOCKING_BYCALLER /* The user will take care of locking.
                                                     * This is the equivalent of `__USE_STDIO_UNLOCKED' on a per-file basis. */
#endif /* __FSETLOCKING_BYCALLER */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */


#ifdef __CC__

}

@@Return the size of the buffer of FP in bytes currently in use by the given stream
[[wunused, ATTR_PURE]]
$size_t __fbufsize([[nonnull]] $FILE *fp);

@@Return non-zero value iff the stream FP is opened readonly,
@@or if the last operation on the stream was a read operation
[[wunused, ATTR_PURE]]
int __freading([[nonnull]] $FILE *fp);

@@Return non-zero value iff the stream FP is opened write-only or
@@append-only, or if the last operation on the stream was a write
@@operation
[[wunused, ATTR_PURE]]
int __fwriting([[nonnull]] $FILE *fp);

@@Return non-zero value iff stream FP is not opened write-only or append-only
[[wunused, ATTR_PURE]]
int __freadable([[nonnull]] $FILE *fp);

@@Return non-zero value iff stream FP is not opened read-only
[[wunused, ATTR_PURE]]
int __fwritable([[nonnull]] $FILE *fp);

@@Return non-zero value iff the stream FP is line-buffered
[[wunused, ATTR_PURE]]
int __flbf([[nonnull]] $FILE *fp);

@@Discard all pending buffered I/O on the stream FP
void __fpurge([[nonnull]] $FILE *fp);

@@Return amount of output in bytes pending on a stream FP
[[wunused, ATTR_PURE]]
size_t __fpending([[nonnull]] $FILE *fp);

@@Flush all line-buffered files
/* NOTE: I feel like this is a typo, but that's
 *       the  symbol that also exists in GLibC! */
[[cp_stdio, export_alias("_IO_flush_all_linebuffere")]]
void _flushlbf();

@@Set locking status of stream FP to TYPE
int __fsetlocking([[nonnull]] $FILE *fp, int type);

%{
#endif /* __CC__ */

/* Never actually needed */
#ifndef enable_extended_FILE_stdio
#define enable_extended_FILE_stdio(fd, act) 0
#endif /* !enable_extended_FILE_stdio */

__SYSDECL_END

}
