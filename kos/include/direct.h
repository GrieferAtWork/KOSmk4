/* HASH CRC-32:0x5589e438 */
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
#ifndef _DIRECT_H
#define _DIRECT_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef _DISKFREE_T_DEFINED
#define _DISKFREE_T_DEFINED 1
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("total_clusters")
#pragma push_macro("avail_clusters")
#pragma push_macro("sectors_per_cluster")
#pragma push_macro("bytes_per_sector")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef total_clusters
#undef avail_clusters
#undef sectors_per_cluster
#undef bytes_per_sector
struct _diskfree_t {
	__UINT32_TYPE__ total_clusters;
	__UINT32_TYPE__ avail_clusters;
	__UINT32_TYPE__ sectors_per_cluster;
	__UINT32_TYPE__ bytes_per_sector;
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("bytes_per_sector")
#pragma pop_macro("sectors_per_cluster")
#pragma pop_macro("avail_clusters")
#pragma pop_macro("total_clusters")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* !_DISKFREE_T_DEFINED */

#if defined(__CRT_HAVE__getcwd)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CDECLARE(,char *,__NOTHROW_RPC,_getcwd,(char *__buf, size_t __bufsize),(__buf,__bufsize))
#elif defined(__CRT_HAVE_getcwd)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT(,char *,__NOTHROW_RPC,_getcwd,(char *__buf, size_t __bufsize),getcwd,(__buf,__bufsize))
#endif /* _getcwd... */
#if defined(__CRT_HAVE__chdir)
/* >> chdir(2)
 * Change the current working directory to `PATH' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,_chdir,(char const *__path),(__path))
#elif defined(__CRT_HAVE_chdir)
/* >> chdir(2)
 * Change the current working directory to `PATH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,_chdir,(char const *__path),chdir,(__path))
#endif /* _chdir... */
#if defined(__CRT_HAVE__rmdir)
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,_rmdir,(char const *__path),(__path))
#elif defined(__CRT_HAVE_rmdir)
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,_rmdir,(char const *__path),rmdir,(__path))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
#include <local/unistd/rmdir.h>
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL _rmdir)(char const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rmdir))(__path); }
#endif /* _rmdir... */
#define _getdcwd_nolock _getdcwd
#if defined(__CRT_HAVE__getdcwd)
__CDECLARE(,char *,__NOTHROW_RPC,_getdcwd,(int __drive, char *__buf, size_t __size),(__drive,__buf,__size))
#endif /* _getdcwd... */
#if defined(__CRT_HAVE__chdrive)
__CDECLARE(,int,__NOTHROW_RPC,_chdrive,(int __drive),(__drive))
#endif /* _chdrive... */
#if defined(__CRT_HAVE__getdrive)
__CDECLARE(,int,__NOTHROW_RPC,_getdrive,(void),())
#endif /* _getdrive... */
#if defined(__CRT_HAVE__getdrives)
__CDECLARE(,__ULONG32_TYPE__,__NOTHROW_RPC,_getdrives,(void),())
#endif /* _getdrives... */

#ifndef _GETDISKFREE_DEFINED
#define _GETDISKFREE_DEFINED 1
#ifndef ___getdiskfree_defined
#define ___getdiskfree_defined 1
#if defined(__CRT_HAVE__getdiskfree)
__CDECLARE(,unsigned int,__NOTHROW_RPC,_getdiskfree,(unsigned int __drive, struct _diskfree_t *__diskfree),(__drive,__diskfree))
#else /* LIBC: _getdiskfree */
#undef ___getdiskfree_defined
#endif /* _getdiskfree... */
#endif /* !___getdiskfree_defined */
#endif /* !_GETDISKFREE_DEFINED */
#ifndef __getcwd_defined
#define __getcwd_defined 1
#if defined(__CRT_HAVE_getcwd)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CDECLARE(,char *,__NOTHROW_RPC,getcwd,(char *__buf, size_t __bufsize),(__buf,__bufsize))
#elif defined(__CRT_HAVE__getcwd)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT(,char *,__NOTHROW_RPC,getcwd,(char *__buf, size_t __bufsize),_getcwd,(__buf,__bufsize))
#else /* LIBC: getcwd */
#undef __getcwd_defined
#endif /* getcwd... */
#endif /* !__getcwd_defined */
#ifndef __rmdir_defined
#define __rmdir_defined 1
#if defined(__CRT_HAVE_rmdir)
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,rmdir,(char const *__path),(__path))
#elif defined(__CRT_HAVE__rmdir)
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,rmdir,(char const *__path),_rmdir,(__path))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
#include <local/unistd/rmdir.h>
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rmdir, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL rmdir)(char const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rmdir))(__path); })
#else /* CUSTOM: rmdir */
#undef __rmdir_defined
#endif /* rmdir... */
#endif /* !__rmdir_defined */
#if defined(__CRT_HAVE__mkdir)
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,_mkdir,(char const *__path),(__path))
#elif defined(__CRT_HAVE_mkdir)
#include <local/direct/_mkdir.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_mkdir, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL _mkdir)(char const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mkdir))(__path); })
#endif /* _mkdir... */
#ifndef __mkdir_defined
#define __mkdir_defined 1
#if defined(__CRT_HAVE_mkdir)
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,mkdir,(char const *__path),(__path))
#elif defined(__CRT_HAVE__mkdir)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,mkdir,(char const *__path),_mkdir,(__path))
#elif defined(__CRT_HAVE_mkdir)
#include <local/direct/_mkdir.h>
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL mkdir)(char const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_mkdir))(__path); }
#else /* CUSTOM: _mkdir */
#undef __mkdir_defined
#endif /* mkdir... */
#endif /* !__mkdir_defined */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_DIRECT_H */
