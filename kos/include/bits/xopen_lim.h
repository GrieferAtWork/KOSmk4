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
#ifndef _BITS_XOPEN_LIM_H
#define _BITS_XOPEN_LIM_H 1

/* DISCLAIMER: _STRONGLY_ Based on '/usr/include/i386-linux-gnu/bits/posix1_lim.h' */

#include <__stdinc.h>

#include <hybrid/limitcore.h>

#include <asm/pagesize.h>

/* Copyright (C) 1996-2016 Free Software Foundation, Inc.
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

/* We do not provide fixed values for
   ARG_MAX     Maximum length of argument to the `exec' function including environment data.
   ATEXIT_MAX  Maximum number of functions that may be registered with `atexit'.
   CHILD_MAX   Maximum number of simultaneous processes per real user ID.
   OPEN_MAX    Maximum number of files that one process can have open at anyone time.
   PASS_MAX    Maximum number of significant bytes in a password.
   We only provide a fixed limit for
   IOV_MAX     Maximum number of `iovec' structures that one process has available for use with `readv' or writev'.
   if this is indeed fixed by the underlying system. */

#ifndef PAGESIZE
#ifdef __ARCH_PAGESIZE
#define PAGESIZE __ARCH_PAGESIZE
#endif /* __ARCH_PAGESIZE */
#endif /* !PAGESIZE */

#ifndef PAGE_SIZE
#ifdef __ARCH_PAGESIZE
#define PAGE_SIZE __ARCH_PAGESIZE
#endif /* __ARCH_PAGESIZE */
#endif /* !PAGE_SIZE */

#ifndef IOV_MAX
#define IOV_MAX 1024
#endif /* !IOV_MAX */

#ifndef _XOPEN_IOV_MAX
#define _XOPEN_IOV_MAX _POSIX_UIO_MAXIOV /* Maximum number of `iovec' structures that one process has available for use with `readv' or writev'. */
#endif /* !_XOPEN_IOV_MAX */

#ifndef NL_ARGMAX
#define NL_ARGMAX _POSIX_ARG_MAX /* Maximum value of `digit' in calls to the `printf' and `scanf' functions. We have no limit, so return a reasonable value. */
#endif /* !NL_ARGMAX */

#ifndef NL_LANGMAX
#define NL_LANGMAX _POSIX2_LINE_MAX /* Maximum number of bytes in a `LANG' name. We have no limit. */
#endif /* !NL_LANGMAX */

#ifndef NL_MSGMAX
#define NL_MSGMAX __INT_MAX__ /* Maximum message number. We have no limit. */
#endif /* !NL_MSGMAX */

#ifndef NL_NMAX
#define NL_NMAX __INT_MAX__ /* Maximum number of bytes in N-to-1 collation mapping. We have no limit. */
#endif /* !NL_NMAX */

#ifndef NL_SETMAX
#define NL_SETMAX __INT_MAX__ /* Maximum set number. We have no limit. */
#endif /* !NL_SETMAX */

#ifndef NL_TEXTMAX
#define NL_TEXTMAX __INT_MAX__ /* Maximum number of bytes in a message. We have no limit. */
#endif /* !NL_TEXTMAX */

#ifndef NZERO
#define NZERO 20 /* Default process priority. */
#endif /* !NZERO */

#ifndef WORD_BIT
#if __INT_MAX__ == __INT8_MAX__
#define WORD_BIT 8 /* Number of bits in a word of type `int'. */
#elif __INT_MAX__ == __INT16_MAX__
#define WORD_BIT 16 /* Number of bits in a word of type `int'. */
#elif __INT_MAX__ == __INT32_MAX__
#define WORD_BIT 32 /* Number of bits in a word of type `int'. */
#elif __INT_MAX__ == __INT64_MAX__
#define WORD_BIT 64 /* Number of bits in a word of type `int'. */
#else
#define WORD_BIT (__SIZEOF_INT__ * 8) /* Number of bits in a word of type `int'. */
#endif
#endif /* !WORD_BIT */

#ifndef LONG_BIT
#if __LONG_MAX__ == __INT8_MAX__
#define LONG_BIT 8 /* Number of bits in a word of type `long int'. */
#elif __LONG_MAX__ == __INT16_MAX__
#define LONG_BIT 16 /* Number of bits in a word of type `long int'. */
#elif __LONG_MAX__ == __INT32_MAX__
#define LONG_BIT 32 /* Number of bits in a word of type `long int'. */
#elif __LONG_MAX__ == __INT64_MAX__
#define LONG_BIT 64 /* Number of bits in a word of type `long int'. */
#else
#define LONG_BIT (__SIZEOF_INT__ * 8) /* Number of bits in a word of type `long int'. */
#endif
#endif /* !LONG_BIT */

#endif /* !_BITS_XOPEN_LIM_H */
