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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBRT_BITS_AIOINIT_H
#define _LIBRT_BITS_AIOINIT_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

/* Documentation derived from Glibc /usr/include/aio.h */
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

/* To customize the implementation one can use the following struct.
 * This implementation follows the one in Irix. */
/*[[[struct]]]*/
#ifdef __CC__
struct aioinit {
	__INT32_TYPE__ aio_threads;   /* Maximal number of threads. */
	__INT32_TYPE__ aio_num;       /* Number of expected simultaneous requests. */
	__INT32_TYPE__ aio_locks;     /* Not used. */
	__INT32_TYPE__ aio_usedba;    /* Not used. */
	__INT32_TYPE__ aio_debug;     /* Not used. */
	__INT32_TYPE__ aio_numusers;  /* Not used. */
	__INT32_TYPE__ aio_idle_time; /* Number of seconds before idle thread terminates. */
	__INT32_TYPE__ aio_reserved;  /* ... */
};
#endif /* __CC__ */
/*[[[end]]]*/

__SYSDECL_END

#endif /* !_LIBRT_BITS_AIOINIT_H */
