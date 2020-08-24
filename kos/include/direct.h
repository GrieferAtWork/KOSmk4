/* HASH CRC-32:0xb2ce5a02 */
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
#ifndef _DIRECT_H
#define _DIRECT_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <hybrid/typecore.h>
#include <bits/crt/_diskfree_t.h>

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifdef __CRT_HAVE_getcwd
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT(,char *,__NOTHROW_RPC,_getcwd,(char *__buf, size_t __bufsize),getcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE__getcwd)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CDECLARE(,char *,__NOTHROW_RPC,_getcwd,(char *__buf, size_t __bufsize),(__buf,__bufsize))
#endif /* ... */
#ifdef __CRT_HAVE_chdir
/* >> chdir(2)
 * Change the current working directory to `PATH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,_chdir,(char const *__path),chdir,(__path))
#elif defined(__CRT_HAVE__chdir)
/* >> chdir(2)
 * Change the current working directory to `PATH' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,_chdir,(char const *__path),(__path))
#endif /* ... */
#ifdef __CRT_HAVE_rmdir
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,_rmdir,(char const *__path),rmdir,(__path))
#elif defined(__CRT_HAVE__rmdir)
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,_rmdir,(char const *__path),(__path))
#else /* ... */
#include <asm/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
#include <local/unistd/rmdir.h>
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL _rmdir)(char const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rmdir))(__path); }
#endif /* __AT_FDCWD && __CRT_HAVE_unlinkat */
#endif /* !... */
#define _getdcwd_nolock _getdcwd
__CDECLARE_OPT(,char *,__NOTHROW_RPC,_getdcwd,(int __drive, char *__buf, size_t __size),(__drive,__buf,__size))
__CDECLARE_OPT(,int,__NOTHROW_RPC,_chdrive,(int __drive),(__drive))
__CDECLARE_OPT(,int,__NOTHROW_RPC,_getdrive,(void),())
__CDECLARE_OPT(,__ULONG32_TYPE__,__NOTHROW_RPC,_getdrives,(void),())

#ifndef _GETDISKFREE_DEFINED
#define _GETDISKFREE_DEFINED 1
#ifdef __CRT_HAVE__getdiskfree
__CDECLARE(,unsigned int,__NOTHROW_RPC,_getdiskfree,(unsigned int __drive, struct _diskfree_t *__diskfree),(__drive,__diskfree))
#else /* __CRT_HAVE__getdiskfree */
#undef _GETDISKFREE_DEFINED
#endif /* !__CRT_HAVE__getdiskfree */
#endif /* !_GETDISKFREE_DEFINED */
#ifndef __getcwd_defined
#define __getcwd_defined 1
#ifdef __CRT_HAVE_getcwd
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CDECLARE(,char *,__NOTHROW_RPC,getcwd,(char *__buf, size_t __bufsize),(__buf,__bufsize))
#elif defined(__CRT_HAVE__getcwd)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT(,char *,__NOTHROW_RPC,getcwd,(char *__buf, size_t __bufsize),_getcwd,(__buf,__bufsize))
#else /* ... */
#undef __getcwd_defined
#endif /* !... */
#endif /* !__getcwd_defined */
#ifndef __rmdir_defined
#define __rmdir_defined 1
#ifdef __CRT_HAVE_rmdir
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,rmdir,(char const *__path),(__path))
#elif defined(__CRT_HAVE__rmdir)
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,rmdir,(char const *__path),_rmdir,(__path))
#else /* ... */
#include <asm/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
#include <local/unistd/rmdir.h>
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rmdir, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL rmdir)(char const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rmdir))(__path); })
#else /* __AT_FDCWD && __CRT_HAVE_unlinkat */
#undef __rmdir_defined
#endif /* !__AT_FDCWD || !__CRT_HAVE_unlinkat */
#endif /* !... */
#endif /* !__rmdir_defined */
#ifdef __CRT_HAVE__mkdir
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,_mkdir,(char const *__path),(__path))
#elif defined(__CRT_HAVE_mkdir)
#include <local/direct/_mkdir.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mkdir, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL _mkdir)(char const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mkdir))(__path); })
#endif /* ... */
#ifndef __mkdir_defined
#define __mkdir_defined 1
#ifdef __CRT_HAVE__mkdir
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,mkdir,(char const *__path),_mkdir,(__path))
#elif defined(__CRT_HAVE_mkdir)
#include <local/direct/_mkdir.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL mkdir)(char const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mkdir))(__path); }
#else /* ... */
#undef __mkdir_defined
#endif /* !... */
#endif /* !__mkdir_defined */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_DIRECT_H */
