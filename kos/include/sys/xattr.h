/* HASH CRC-32:0x2b0e0d80 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/xattr.h) */
/* (#) Portability: GNU C Library (/misc/sys/xattr.h) */
/* (#) Portability: NetBSD        (/sys/sys/xattr.h) */
/* (#) Portability: diet libc     (/include/sys/xattr.h) */
/* (#) Portability: musl libc     (/include/sys/xattr.h) */
/* (#) Portability: uClibc        (/include/sys/xattr.h) */
#ifndef _SYS_XATTR_H
#define _SYS_XATTR_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/os/xattr.h>
#include <bits/types.h>

#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>
#endif /* __USE_GLIBC_BLOAT */

#if !defined(XATTR_CREATE) && defined(__XATTR_CREATE)
#define XATTR_CREATE  __XATTR_CREATE  /* set value, fail if attr already exists. */
#endif /* !XATTR_CREATE && __XATTR_CREATE */
#if !defined(XATTR_REPLACE) && defined(__XATTR_REPLACE)
#define XATTR_REPLACE __XATTR_REPLACE /* set value, fail if attr does not exist. */
#endif /* !XATTR_REPLACE && __XATTR_REPLACE */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __ssize_t_defined
#define __ssize_t_defined
typedef __ssize_t ssize_t;
#endif /* !__ssize_t_defined */

/* >> setxattr(2)
 * @param: flags: One of `XATTR_*', or `0' */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_INS(3, 4),int,__NOTHROW_RPC,setxattr,(char const *__path, char const *__name, void const *__buf, size_t __bufsize, __STDC_INT_AS_UINT_T __flags),(__path,__name,__buf,__bufsize,__flags))
/* >> lsetxattr(2)
 * @param: flags: One of `XATTR_*', or `0' */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_INS(3, 4),int,__NOTHROW_RPC,lsetxattr,(char const *__path, char const *__name, void const *__buf, size_t __bufsize, __STDC_INT_AS_UINT_T __flags),(__path,__name,__buf,__bufsize,__flags))
/* >> fsetxattr(2)
 * @param: flags: One of `XATTR_*', or `0' */
__CDECLARE_OPT(__ATTR_FDARG(1) __ATTR_IN(2) __ATTR_INS(3, 4),int,__NOTHROW_RPC,fsetxattr,(__fd_t __fd, char const *__name, void const *__buf, size_t __bufsize, __STDC_INT_AS_UINT_T __flags),(__fd,__name,__buf,__bufsize,__flags))
/* >> getxattr(2) */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_OUTS(3, 4),ssize_t,__NOTHROW_RPC,getxattr,(char const *__path, char const *__name, void *__buf, size_t __bufsize),(__path,__name,__buf,__bufsize))
/* >> lgetxattr(2) */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_OUTS(3, 4),ssize_t,__NOTHROW_RPC,lgetxattr,(char const *__path, char const *__name, void *__buf, size_t __bufsize),(__path,__name,__buf,__bufsize))
/* >> fgetxattr(2) */
__CDECLARE_OPT(__ATTR_FDARG(1) __ATTR_IN(2) __ATTR_OUTS(3, 4),ssize_t,__NOTHROW_RPC,fgetxattr,(__fd_t __fd, char const *__name, void *__buf, size_t __bufsize),(__fd,__name,__buf,__bufsize))
/* >> listxattr(2) */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_OUTS(2, 3),ssize_t,__NOTHROW_RPC,listxattr,(char const *__path, char *__listbuf, size_t __listbufsize),(__path,__listbuf,__listbufsize))
/* >> llistxattr(2) */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_OUTS(2, 3),ssize_t,__NOTHROW_RPC,llistxattr,(char const *__path, char *__listbuf, size_t __listbufsize),(__path,__listbuf,__listbufsize))
/* >> flistxattr(2) */
__CDECLARE_OPT(__ATTR_FDARG(1) __ATTR_OUTS(2, 3),ssize_t,__NOTHROW_RPC,flistxattr,(__fd_t __fd, char *__listbuf, size_t __listbufsize),(__fd,__listbuf,__listbufsize))
/* >> removexattr(2) */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_RPC,removexattr,(char const *__path, char const *__name),(__path,__name))
/* >> lremovexattr(2) */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_RPC,lremovexattr,(char const *__path, char const *__name),(__path,__name))
/* >> fremovexattr(2) */
__CDECLARE_OPT(__ATTR_FDARG(1) __ATTR_IN(2),int,__NOTHROW_RPC,fremovexattr,(__fd_t __fd, char const *__name),(__fd,__name))

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_XATTR_H */
