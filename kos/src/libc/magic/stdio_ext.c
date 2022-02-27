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
%(c_prefix){
/* (#) Portability: Cygwin        (/newlib/libc/include/stdio_ext.h) */
/* (#) Portability: GNU C Library (/include/stdio_ext.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/stdio_ext.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/stdio_ext.h) */
/* (#) Portability: diet libc     (/include/stdio_ext.h) */
/* (#) Portability: libc6         (/include/stdio_ext.h) */
/* (#) Portability: musl libc     (/include/stdio_ext.h) */
/* (#) Portability: uClibc        (/include/stdio_ext.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.FILE.utility.ext")]

%{
}%[insert:prefix(
#include <stdio.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%[insert:prefix(
#include <asm/crt/stdio_ext.h>
)]%{

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

}

@@>> __fbufsize(3)
@@Return the size of the buffer of `stream' in
@@bytes  currently in use  by the given stream
[[pure, wunused, decl_include("<features.h>")]]
$size_t __fbufsize([[nonnull]] $FILE __KOS_FIXED_CONST *stream);

@@>> __freading(3)
@@Return  non-zero value when  `stream' is opened readonly,
@@or if the last operation on `stream' was a read operation
[[pure, wunused, decl_include("<features.h>")]]
int __freading([[nonnull]] $FILE __KOS_FIXED_CONST *stream);

@@>> __fwriting(3)
@@Return non-zero value when  `stream' is opened write-only  or
@@append-only, or if the last operation on `stream' was a write
@@operation
[[pure, wunused, decl_include("<features.h>")]]
int __fwriting([[nonnull]] $FILE __KOS_FIXED_CONST *stream);

@@>> __freadable(3)
@@Return non-zero value when `stream' is not opened write-only or append-only
[[pure, wunused, decl_include("<features.h>")]]
int __freadable([[nonnull]] $FILE __KOS_FIXED_CONST *stream);

@@>> __fwritable(3)
@@Return non-zero value when `stream' is not opened read-only
[[pure, wunused, decl_include("<features.h>")]]
int __fwritable([[nonnull]] $FILE __KOS_FIXED_CONST *stream);

@@>> __flbf(3)
@@Return non-zero value when `stream' is line-buffered
[[pure, wunused, decl_include("<features.h>")]]
int __flbf([[nonnull]] $FILE *stream); /* Can't be const because lazily determined on KOS... */

@@>> __fpurge(3)
@@Discard all pending buffered I/O on `stream'
[[export_alias("fpurge")]]
void __fpurge([[nonnull]] $FILE *stream);

@@>> __fpending(3)
@@Return amount of output in bytes pending on a `stream'
[[pure, wunused, decl_include("<features.h>", "<hybrid/typecore.h>")]]
size_t __fpending([[nonnull]] $FILE __KOS_FIXED_CONST *stream);

@@>> _flushlbf(3)
@@Flush all line-buffered files
[[cp_stdio, export_alias("_IO_flush_all_linebuffered")]]
void _flushlbf();

@@>> __fsetlocking(3)
@@Set locking status of `stream' to `type'
@@@param: type: One of `FSETLOCKING_*'
int __fsetlocking([[nonnull]] $FILE *stream, int type);

@@>> __fseterr(3)
@@Set the error indicator for the given `stream' (s.a. `ferror()')
void __fseterr([[nonnull]] $FILE *stream);

%{
#endif /* __CC__ */

/* Never actually needed */
#ifndef enable_extended_FILE_stdio
#define enable_extended_FILE_stdio(fd, act) 0
#endif /* !enable_extended_FILE_stdio */

__SYSDECL_END

}
