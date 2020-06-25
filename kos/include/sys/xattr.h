/* HASH CRC-32:0x397f7be3 */
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
#ifndef _SYS_XATTR_H
#define _SYS_XATTR_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/xattr.h>
#include <bits/types.h>

#ifdef __USE_GLIBC
#include <sys/types.h>
#endif /* __USE_GLIBC */

/* Documentation comments have been taken from GLibc: /usr/include/i386-linux-gnu/sys/xattr.h */
/* Copyright (C) 2002-2016 Free Software Foundation, Inc.
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

#ifndef __USE_KERNEL_XATTR_DEFS
#if (defined(__XATTR_CREATE) || defined(__XATTR_REPLACE))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __XATTR_CREATE
	XATTR_CREATE  = __XATTR_CREATE, /* set value, fail if attr already exists. */
#endif /* __XATTR_CREATE */
#ifdef __XATTR_REPLACE
	XATTR_REPLACE = __XATTR_REPLACE /* set value, fail if attr does not exist. */
#endif /* __XATTR_REPLACE */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __XATTR_CREATE
#define XATTR_CREATE  XATTR_CREATE  /* set value, fail if attr already exists. */
#endif /* __XATTR_CREATE */
#ifdef __XATTR_REPLACE
#define XATTR_REPLACE XATTR_REPLACE /* set value, fail if attr does not exist. */
#endif /* __XATTR_REPLACE */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __XATTR_CREATE
#define XATTR_CREATE  __XATTR_CREATE  /* set value, fail if attr already exists. */
#endif /* __XATTR_CREATE */
#ifdef __XATTR_REPLACE
#define XATTR_REPLACE __XATTR_REPLACE /* set value, fail if attr does not exist. */
#endif /* __XATTR_REPLACE */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */
#endif /* !__USE_KERNEL_XATTR_DEFS */

#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __size_t size_t;
#endif /* !__size_t_defined */

/* Set the attribute NAME of the file pointed to by PATH to VALUE
 * (which is SIZE bytes long). Return 0 on success, -1 for errors
 * @param: flags: 0, or a one of `XATTR_*' */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,setxattr,(char const *__path, char const *__name, void const *__buf, size_t __bufsize, __STDC_INT_AS_UINT_T __flags),(__path,__name,__buf,__bufsize,__flags))
/* Set the attribute NAME of the file pointed to by PATH to VALUE (which is
 * SIZE bytes long), not following symlinks for the last pathname component.
 * Return 0 on success, -1 for errors
 * @param: flags: 0, or a one of `XATTR_*' */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,lsetxattr,(char const *__path, char const *__name, void const *__buf, size_t __bufsize, __STDC_INT_AS_UINT_T __flags),(__path,__name,__buf,__bufsize,__flags))
/* Set the attribute NAME of the file descriptor FD to VALUE
 * (which is SIZE bytes long). Return 0 on success, -1 for errors
 * @param: flags: 0, or a one of `XATTR_*' */
__CDECLARE_OPT(__ATTR_NONNULL((2, 3)),int,__NOTHROW_RPC,fsetxattr,(__fd_t __fd, char const *__name, void const *__buf, size_t __bufsize, __STDC_INT_AS_UINT_T __flags),(__fd,__name,__buf,__bufsize,__flags))
/* Get the attribute NAME of the file pointed to by PATH to VALUE
 * (which is SIZE bytes long). Return 0 on success, -1 for errors */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2, 3)),ssize_t,__NOTHROW_RPC,getxattr,(char const *__path, char const *__name, void *__buf, size_t __bufsize),(__path,__name,__buf,__bufsize))
/* Get the attribute NAME of the file pointed to by PATH to VALUE (which is
 * SIZE bytes long), not following symlinks for the last pathname component.
 * Return 0 on success, -1 for errors */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2, 3)),ssize_t,__NOTHROW_RPC,lgetxattr,(char const *__path, char const *__name, void *__buf, size_t __bufsize),(__path,__name,__buf,__bufsize))
/* Get the attribute NAME of the file descriptor FD to VALUE
 * (which is SIZE bytes long). Return 0 on success, -1 for errors */
__CDECLARE_OPT(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,fgetxattr,(__fd_t __fd, char const *__name, void *__buf, size_t __bufsize),(__fd,__name,__buf,__bufsize))
/* List attributes of the file pointed to by PATH into the
 * user-supplied buffer LIST (which is SIZE bytes big).
 * Return 0 on success, -1 for errors */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),ssize_t,__NOTHROW_RPC,listxattr,(char const *__path, char *__listbuf, size_t __listbufsize),(__path,__listbuf,__listbufsize))
/* List attributes of the file pointed to by PATH into the user-supplied
 * buffer LIST (which is SIZE bytes big), not following symlinks for the
 * last pathname component. Return 0 on success, -1 for errors */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),ssize_t,__NOTHROW_RPC,llistxattr,(char const *__path, char *__listbuf, size_t __listbufsize),(__path,__listbuf,__listbufsize))
/* List attributes of the file descriptor FD into the user-supplied buffer
 * LIST (which is SIZE bytes big). Return 0 on success, -1 for errors */
__CDECLARE_OPT(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,flistxattr,(__fd_t __fd, char *__listbuf, size_t __listbufsize),(__fd,__listbuf,__listbufsize))
/* Remove the attribute NAME from the file pointed to by PATH.
 * Return 0 on success, -1 for errors */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,removexattr,(char const *__path, char const *__name),(__path,__name))
/* Remove the attribute NAME from the file pointed to by PATH, not
 * following symlinks for the last pathname component.
 * Return 0 on success, -1 for errors */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,lremovexattr,(char const *__path, char const *__name),(__path,__name))
/* Remove the attribute NAME from the file descriptor FD.
 * Return 0 on success, -1 for errors */
__CDECLARE_OPT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,fremovexattr,(__fd_t __fd, char const *__name),(__fd,__name))

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_XATTR_H */
