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
#ifndef _LIBRT_BITS_MQUEUE_H
#define _LIBRT_BITS_MQUEUE_H 1

#include <__stdinc.h>

#include <bits/types.h>

/* Documentation derived from Glibc /usr/include/mqueue.h */
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

/*[[[struct]]]*/
#ifdef __CC__
typedef __fd_t mqd_t;
#endif /* __CC__ */
/*[[[end]]]*/

/*[[[struct]]]*/
#ifdef __CC__
struct mq_attr {
	__syscall_slong_t mq_flags;   /* Message queue flags.  */
	__syscall_slong_t mq_maxmsg;  /* Maximum number of messages.  */
	__syscall_slong_t mq_msgsize; /* Maximum message size.  */
	__syscall_slong_t mq_curmsgs; /* Number of messages currently queued.  */
	__syscall_slong_t __pad[4];   /* ... */
};
#endif /* __CC__ */
/*[[[end]]]*/

__SYSDECL_END

#endif /* !_LIBRT_BITS_MQUEUE_H */
