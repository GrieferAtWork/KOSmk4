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
#ifndef _LIBRT_ASM_AIO_H
#define _LIBRT_ASM_AIO_H 1

#include <__stdinc.h>

/* Documentation taken from Glibc /usr/include/aio.h */
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

__SYSDECL_BEGIN

/* Return values of cancellation function. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	AIO_CANCELED,
	AIO_NOTCANCELED,
	AIO_ALLDONE
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define AIO_CANCELED    AIO_CANCELED
#define AIO_NOTCANCELED AIO_NOTCANCELED
#define AIO_ALLDONE     AIO_ALLDONE
#else /* __COMPILER_PREFERR_ENUMS */
#define AIO_CANCELED    0
#define AIO_NOTCANCELED 1
#define AIO_ALLDONE     2
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

/* Operation codes for `aio_lio_opcode'. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	LIO_READ,
	LIO_WRITE,
	LIO_NOP
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define LIO_READ  LIO_READ
#define LIO_WRITE LIO_WRITE
#define LIO_NOP   LIO_NOP
#else /* __COMPILER_PREFERR_ENUMS */
#define LIO_READ  0
#define LIO_WRITE 1
#define LIO_NOP   2
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

/* Synchronization options for `lio_listio' function. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	LIO_WAIT,
	LIO_NOWAIT
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define LIO_WAIT   LIO_WAIT
#define LIO_NOWAIT LIO_NOWAIT
#else /* __COMPILER_PREFERR_ENUMS */
#define LIO_WAIT   0
#define LIO_NOWAIT 1
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

__SYSDECL_END

#endif /* !_LIBRT_ASM_AIO_H */
