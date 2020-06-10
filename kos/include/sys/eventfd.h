/* HASH CRC-32:0x76aa099f */
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
#ifndef _SYS_EVENTFD_H
#define _SYS_EVENTFD_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <stdint.h>
#include <bits/types.h>
#include <bits/eventfd.h>


/* Documentation taken from Glibc /usr/include/i386-linux-gnu/sys/eventfd.h */
/* Copyright (C) 2007-2016 Free Software Foundation, Inc.
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

#ifdef __CC__

/* Type for event counter. */
#ifndef __eventfd_t_defined
#define __eventfd_t_defined 1
typedef uint64_t eventfd_t;
#endif /* !__eventfd_t_defined */

#ifdef __CRT_HAVE_eventfd
/* Return file descriptor for generic event channel. Set initial value to COUNT */
__CDECLARE(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,eventfd,(unsigned int __count, int __flags),(__count,__flags))
#endif /* __CRT_HAVE_eventfd */
#ifdef __CRT_HAVE_eventfd_read
/* Read event counter and possibly wait for events */
__CDECLARE(,int,__NOTHROW_RPC,eventfd_read,(__fd_t __fd, eventfd_t *__value),(__fd,__value))
#elif defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)
#include <local/sys.eventfd/eventfd_read.h>
/* Read event counter and possibly wait for events */
__NAMESPACE_LOCAL_USING_OR_IMPL(eventfd_read, __FORCELOCAL int __NOTHROW_RPC(__LIBCCALL eventfd_read)(__fd_t __fd, eventfd_t *__value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(eventfd_read))(__fd, __value); })
#endif /* ... */
#ifdef __CRT_HAVE_eventfd_write
/* Increment event counter */
__CDECLARE(,int,__NOTHROW_RPC,eventfd_write,(__fd_t __fd, eventfd_t __value),(__fd,__value))
#elif defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)
#include <local/sys.eventfd/eventfd_write.h>
/* Increment event counter */
__NAMESPACE_LOCAL_USING_OR_IMPL(eventfd_write, __FORCELOCAL int __NOTHROW_RPC(__LIBCCALL eventfd_write)(__fd_t __fd, eventfd_t __value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(eventfd_write))(__fd, __value); })
#endif /* ... */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_EVENTFD_H */
