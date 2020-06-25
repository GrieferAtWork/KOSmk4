/* HASH CRC-32:0xf3348e52 */
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
#ifndef _ULIMIT_H
#define _ULIMIT_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <asm/ulimit.h>

__SYSDECL_BEGIN

/* Some documentation comments are taken from /usr/include/ulimit.h on a linux machine.
 * The following copyright notice can be found at the top of that file: */
/* Copyright (C) 1997-2016 Free Software Foundation, Inc.
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



#if (defined(__UL_GETFSIZE) || defined(__UL_SETFSIZE))
/* Constants used as the first parameter for `ulimit'.
 * They denote limits which can be set or retrieved using this function. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __UL_GETFSIZE
	UL_GETFSIZE = __UL_GETFSIZE, /* Return limit on the size of a file, in units of 512 bytes. */
#endif /* __UL_GETFSIZE */
#ifdef __UL_SETFSIZE
	UL_SETFSIZE = __UL_SETFSIZE, /* Set limit on the size of a file to second argument. */
#endif /* __UL_SETFSIZE */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __UL_GETFSIZE
#define UL_GETFSIZE UL_GETFSIZE /* Return limit on the size of a file, in units of 512 bytes. */
#endif /* __UL_GETFSIZE */
#ifdef __UL_SETFSIZE
#define UL_SETFSIZE UL_SETFSIZE /* Set limit on the size of a file to second argument. */
#endif /* __UL_SETFSIZE */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __UL_GETFSIZE
#define UL_GETFSIZE __UL_GETFSIZE /* Return limit on the size of a file, in units of 512 bytes. */
#endif /* __UL_GETFSIZE */
#ifdef __UL_SETFSIZE
#define UL_SETFSIZE __UL_SETFSIZE /* Set limit on the size of a file to second argument. */
#endif /* __UL_SETFSIZE */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */

#ifdef __CC__
#ifdef __CRT_HAVE_ulimit
/* Control process limits according to CMD
 * @param: cmd: One OF `UL_*' */
__LIBC __LONGPTR_TYPE__ __NOTHROW_NCX(__VLIBCCALL ulimit)(__STDC_INT_AS_UINT_T __cmd, ...) __CASMNAME_SAME("ulimit");
#endif /* __CRT_HAVE_ulimit */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_ULIMIT_H */
