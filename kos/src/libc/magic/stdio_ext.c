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

%[define_replacement(fd_t = __fd_t)]
%[default_impl_section(.text.crt.FILE.utility.ext)]

%{
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

/*[[[enum]]]*/
#ifdef __CC__
enum {
	FSETLOCKING_QUERY    = 0, /* Query current state of the locking status. */
	FSETLOCKING_INTERNAL = 1, /* The library protects all uses of the stream functions, except for
	                           * uses of the *_unlocked functions, by calls equivalent to flockfile(). */
	FSETLOCKING_BYCALLER = 2  /* The user will take care of locking.
	                           * This is the equivalent of `__USE_STDIO_UNLOCKED' on a per-file basis. */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
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
/*[[[end]]]*/

#ifdef __CC__

}

@@Return the size of the buffer of FP in bytes currently in use by the given stream
[ATTR_WUNUSED][ATTR_PURE] __fbufsize:([[nonnull]] $FILE *fp) -> $size_t;

@@Return non-zero value iff the stream FP is opened readonly,
@@or if the last operation on the stream was a read operation
[ATTR_WUNUSED][ATTR_PURE] __freading:([[nonnull]] $FILE *fp) -> int;

@@Return non-zero value iff the stream FP is opened write-only or
@@append-only, or if the last operation on the stream was a write
@@operation
[ATTR_WUNUSED][ATTR_PURE] __fwriting:([[nonnull]] $FILE *fp) -> int;

@@Return non-zero value iff stream FP is not opened write-only or append-only
[ATTR_WUNUSED][ATTR_PURE] __freadable:([[nonnull]] $FILE *fp) -> int;

@@Return non-zero value iff stream FP is not opened read-only
[ATTR_WUNUSED][ATTR_PURE] __fwritable:([[nonnull]] $FILE *fp) -> int;

@@Return non-zero value iff the stream FP is line-buffered
[ATTR_WUNUSED][ATTR_PURE] __flbf:([[nonnull]] $FILE *fp) -> int;

@@Discard all pending buffered I/O on the stream FP
__fpurge:([[nonnull]] $FILE *fp);

@@Return amount of output in bytes pending on a stream FP
[ATTR_WUNUSED][ATTR_PURE] __fpending:([[nonnull]] $FILE *fp) -> size_t;

@@Flush all line-buffered files
[export_alias(_IO_flush_all_linebuffere)]
_flushlbf:();

@@Set locking status of stream FP to TYPE
__fsetlocking:([[nonnull]] $FILE *fp, int type) -> int;

%{
#endif /* __CC__ */

__SYSDECL_END

}