/* HASH CRC-32:0x2dd18da */
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
#ifndef _STROPTS_H
#define _STROPTS_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <bits/types.h>
#include <bits/xtitypes.h>
#include <bits/stropts.h>

/* Documentation taken from Glibc /usr/include/stropts.h */
/* Copyright (C) 1998-2016 Free Software Foundation, Inc.
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

#ifndef __gid_t_defined
#define __gid_t_defined 1
typedef __gid_t gid_t;
#endif /* !__gid_t_defined */

#ifndef __uid_t_defined
#define __uid_t_defined 1
typedef __uid_t uid_t;
#endif /* !__uid_t_defined */

typedef __t_scalar_t  t_scalar_t;
typedef __t_uscalar_t t_uscalar_t;

/* Test whether FILDES is associated with a STREAM-based file */
__CDECLARE_OPT(,int,__NOTHROW,isastream,(__fd_t __fildes),(__fildes))
/* Receive next message from a STREAMS file */
__CDECLARE_OPT(,int,__NOTHROW_RPC,getmsg,(__fd_t __fildes, struct strbuf *__restrict __ctlptr, struct strbuf *__restrict __dataptr, __STDC_INT_AS_UINT_T *__restrict __flagsp),(__fildes,__ctlptr,__dataptr,__flagsp))
/* Receive next message from a STREAMS file, with *FLAGSP allowing to control which message. */
__CDECLARE_OPT(,int,__NOTHROW_RPC,getpmsg,(__fd_t __fildes, struct strbuf *__restrict __ctlptr, struct strbuf *__restrict __dataptr, int *__restrict __bandp, __STDC_INT_AS_UINT_T *__restrict __flagsp),(__fildes,__ctlptr,__dataptr,__bandp,__flagsp))
#ifndef __ioctl_defined
#define __ioctl_defined 1
#ifdef __CRT_HAVE_ioctl
/* Perform the I/O control operation specified by REQUEST on FD.
 * One argument may follow; its presence and type depend on REQUEST.
 * Return value depends on REQUEST. Usually -1 indicates error */
__LIBC __STDC_INT_AS_SSIZE_T __NOTHROW_RPC(__VLIBCCALL ioctl)(__fd_t __fd, __ULONGPTR_TYPE__ __request, ...) __CASMNAME_SAME("ioctl");
#else /* __CRT_HAVE_ioctl */
#undef __ioctl_defined
#endif /* !__CRT_HAVE_ioctl */
#endif /* !__ioctl_defined */
/* Send a message on a STREAM */
__CDECLARE_OPT(,int,__NOTHROW_RPC,putmsg,(__fd_t __fildes, struct strbuf const *__ctlptr, struct strbuf const *__dataptr, __STDC_INT_AS_UINT_T __flags),(__fildes,__ctlptr,__dataptr,__flags))
/* Send a message on a STREAM to the BAND */
__CDECLARE_OPT(,int,__NOTHROW_RPC,putpmsg,(__fd_t __fildes, struct strbuf const *__ctlptr, struct strbuf const *__dataptr, __STDC_INT_AS_UINT_T __band, __STDC_INT_AS_UINT_T __flags),(__fildes,__ctlptr,__dataptr,__band,__flags))
/* Attach a STREAMS-based file descriptor FILDES to a file PATH in the file system name space */
__CDECLARE_OPT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC_KOS,fattach,(__fd_t __fildes, char const *__restrict __path),(__fildes,__path))
/* Detach a name PATH from a STREAMS-based file descriptor */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC_KOS,fdetach,(char const *__restrict __path),(__path))
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_STROPTS_H */
