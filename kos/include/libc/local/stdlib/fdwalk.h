/* HASH CRC-32:0x31bdcf1e */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_fdwalk_defined
#define __local_fdwalk_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#include <asm/os/features.h>
#include <bits/os/dirent.h>
#include <features.h>
#include <asm/os/oflags.h>
#if ((defined(__CRT_HAVE_fcntl) || defined(__CRT_HAVE___fcntl) || defined(__CRT_HAVE___libc_fcntl)) && defined(__F_NEXT)) || (defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_opendir) || defined(__CRT_HAVE___libc_opendir) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_opendirat) || defined(__CRT_HAVE_fopendirat) || (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))) || (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))) || defined(__USE_DOS_DIRENT)) && ((defined(__CRT_HAVE_readdirk) && defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))) || (defined(__CRT_HAVE_readdirk64) && defined(__CRT_KOS) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))) || (defined(__CRT_HAVE_readdir) && !defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))) || (defined(__CRT_HAVE___libc_readdir) && !defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))) || (defined(__CRT_HAVE_readdir64) && !defined(__CRT_KOS) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))) || defined(__USE_DOS_DIRENT)))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_atoi_defined
#define __local___localdep_atoi_defined
#ifdef __CRT_HAVE_atoi
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,__localdep_atoi,(char const *__restrict __nptr),atoi,(__nptr))
#else /* __CRT_HAVE_atoi */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_atol) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,__localdep_atoi,(char const *__restrict __nptr),atol,(__nptr))
#elif defined(__CRT_HAVE_atoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,__localdep_atoi,(char const *__restrict __nptr),atoll,(__nptr))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/atoi.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_atoi __LIBC_LOCAL_NAME(atoi)
#endif /* !... */
#endif /* !__CRT_HAVE_atoi */
#endif /* !__local___localdep_atoi_defined */
#ifndef __local___localdep_closedir_defined
#define __local___localdep_closedir_defined
#ifdef __CRT_HAVE_closedir
__NAMESPACE_LOCAL_END
struct __dirstream;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_NCX,__localdep_closedir,(struct __dirstream *__dirp),closedir,(__dirp))
#elif defined(__CRT_HAVE___libc_closedir)
__NAMESPACE_LOCAL_END
struct __dirstream;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_NCX,__localdep_closedir,(struct __dirstream *__dirp),__libc_closedir,(__dirp))
#elif defined(__USE_DOS_DIRENT)
__NAMESPACE_LOCAL_END
#include <libc/local/dirent/closedir.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_closedir __LIBC_LOCAL_NAME(closedir)
#else /* ... */
#undef __local___localdep_closedir_defined
#endif /* !... */
#endif /* !__local___localdep_closedir_defined */
#ifndef __local___localdep_fcntl_defined
#define __local___localdep_fcntl_defined
#ifdef __CRT_HAVE_fcntl
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep_fcntl,(__fd_t __fd, __fcntl_t __cmd),fcntl,(__fd,__cmd),__cmd,1,(void *))
#elif defined(__CRT_HAVE___fcntl)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep_fcntl,(__fd_t __fd, __fcntl_t __cmd),__fcntl,(__fd,__cmd),__cmd,1,(void *))
#elif defined(__CRT_HAVE___libc_fcntl)
__CVREDIRECT(__ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep_fcntl,(__fd_t __fd, __fcntl_t __cmd),__libc_fcntl,(__fd,__cmd),__cmd,1,(void *))
#else /* ... */
#undef __local___localdep_fcntl_defined
#endif /* !... */
#endif /* !__local___localdep_fcntl_defined */
#ifndef __local___localdep_opendir_defined
#define __local___localdep_opendir_defined
#ifdef __CRT_HAVE_opendir
__NAMESPACE_LOCAL_END
struct __dirstream;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),struct __dirstream *,__NOTHROW_RPC,__localdep_opendir,(char const *__name),opendir,(__name))
#elif defined(__CRT_HAVE___libc_opendir)
__NAMESPACE_LOCAL_END
struct __dirstream;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),struct __dirstream *,__NOTHROW_RPC,__localdep_opendir,(char const *__name),__libc_opendir,(__name))
#elif (defined(__AT_FDCWD) && (defined(__CRT_HAVE_opendirat) || defined(__CRT_HAVE_fopendirat) || (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))) || (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))) || defined(__USE_DOS_DIRENT)
__NAMESPACE_LOCAL_END
#include <libc/local/dirent/opendir.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_opendir __LIBC_LOCAL_NAME(opendir)
#else /* ... */
#undef __local___localdep_opendir_defined
#endif /* !... */
#endif /* !__local___localdep_opendir_defined */
#ifndef __local___localdep_readdir_defined
#define __local___localdep_readdir_defined
#if defined(__CRT_HAVE_readdirk) && defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
__NAMESPACE_LOCAL_END
struct __dirstream;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(1),struct dirent *,__NOTHROW_RPC,__localdep_readdir,(struct __dirstream *__restrict __dirp),readdirk,(__dirp))
#elif defined(__CRT_HAVE_readdirk64) && defined(__CRT_KOS) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
__NAMESPACE_LOCAL_END
struct __dirstream;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(1),struct dirent *,__NOTHROW_RPC,__localdep_readdir,(struct __dirstream *__restrict __dirp),readdirk64,(__dirp))
#elif defined(__CRT_HAVE_readdir) && !defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
__NAMESPACE_LOCAL_END
struct __dirstream;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(1),struct dirent *,__NOTHROW_RPC,__localdep_readdir,(struct __dirstream *__restrict __dirp),readdir,(__dirp))
#elif defined(__CRT_HAVE___libc_readdir) && !defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
__NAMESPACE_LOCAL_END
struct __dirstream;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(1),struct dirent *,__NOTHROW_RPC,__localdep_readdir,(struct __dirstream *__restrict __dirp),__libc_readdir,(__dirp))
#elif defined(__CRT_HAVE_readdir64) && !defined(__CRT_KOS) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
__NAMESPACE_LOCAL_END
struct __dirstream;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(1),struct dirent *,__NOTHROW_RPC,__localdep_readdir,(struct __dirstream *__restrict __dirp),readdir64,(__dirp))
#elif defined(__USE_DOS_DIRENT)
__NAMESPACE_LOCAL_END
#include <libc/local/dirent/readdir.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_readdir __LIBC_LOCAL_NAME(readdir)
#else /* ... */
#undef __local___localdep_readdir_defined
#endif /* !... */
#endif /* !__local___localdep_readdir_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
#include <hybrid/__overflow.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fdwalk) __ATTR_NONNULL((1)) int
__NOTHROW_CB_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fdwalk))(int (__LIBCCALL *__walk)(void *__arg, __fd_t __fd), void *__arg) {
	int __result = 0;
#ifdef __libc_geterrno
	__errno_t __saved_err;
#endif /* __libc_geterrno */
#if (defined(__CRT_HAVE_fcntl) || defined(__CRT_HAVE___fcntl) || defined(__CRT_HAVE___libc_fcntl)) && defined(__F_NEXT)
	__fd_t __fd = 0;
	for (;;) {
#ifdef __libc_geterrno
		__saved_err = __libc_geterrno();
#endif /* __libc_geterrno */
		/* fcntl(F_NEXT) returns the next valid  (i.e.
		 * currently open) fd that is >= the given fd. */
		__fd = (__NAMESPACE_LOCAL_SYM __localdep_fcntl)(__fd, __F_NEXT);
		if (__fd < 0) {
#ifdef __libc_geterrno
			(void)__libc_seterrno(__saved_err);
#endif /* __libc_geterrno */
			break;
		}
		__result = (*__walk)(__arg, __fd);
		if (__result != 0)
			break;
		if (__hybrid_overflow_sadd(__fd, 1, &__fd))
			break;
	}
#else /* (__CRT_HAVE_fcntl || __CRT_HAVE___fcntl || __CRT_HAVE___libc_fcntl) && __F_NEXT */
	/* Implementation alternative using `opendir("/proc/self/fd")' */
	struct __dirstream *__dir = (__NAMESPACE_LOCAL_SYM __localdep_opendir)("/proc/self/fd");
	if __likely(__dir) {
		struct dirent *__ent;
#ifdef __libc_geterrno
		__saved_err = __libc_geterrno();
#endif /* __libc_geterrno */
		__ent = (__NAMESPACE_LOCAL_SYM __localdep_readdir)(__dir);
		if (!__ent) {
#ifdef __libc_geterrno
			(void)__libc_seterrno(__saved_err);
#endif /* __libc_geterrno */
			break;
		}
		__result = (*__walk)(__arg, (__NAMESPACE_LOCAL_SYM __localdep_atoi)(__ent->d_name));
	}
#if defined(__CRT_HAVE_closedir) || defined(__CRT_HAVE___libc_closedir) || defined(__USE_DOS_DIRENT)
	(__NAMESPACE_LOCAL_SYM __localdep_closedir)(__dir);
#endif /* __CRT_HAVE_closedir || __CRT_HAVE___libc_closedir || __USE_DOS_DIRENT */
#endif /* (!__CRT_HAVE_fcntl && !__CRT_HAVE___fcntl && !__CRT_HAVE___libc_fcntl) || !__F_NEXT */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fdwalk_defined
#define __local___localdep_fdwalk_defined
#define __localdep_fdwalk __LIBC_LOCAL_NAME(fdwalk)
#endif /* !__local___localdep_fdwalk_defined */
#else /* ((__CRT_HAVE_fcntl || __CRT_HAVE___fcntl || __CRT_HAVE___libc_fcntl) && __F_NEXT) || (__OS_HAVE_PROCFS_SELF_FD && (__CRT_HAVE_opendir || __CRT_HAVE___libc_opendir || (__AT_FDCWD && (__CRT_HAVE_opendirat || __CRT_HAVE_fopendirat || (__CRT_HAVE_fdopendir && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)))) || (__CRT_HAVE_fdopendir && (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)))) || __USE_DOS_DIRENT) && ((__CRT_HAVE_readdirk && __CRT_KOS && (!__USE_FILE_OFFSET64 || _DIRENT_MATCHES_DIRENT64)) || (__CRT_HAVE_readdirk64 && __CRT_KOS && (__USE_FILE_OFFSET64 || _DIRENT_MATCHES_DIRENT64)) || (__CRT_HAVE_readdir && !__CRT_KOS && (!__USE_FILE_OFFSET64 || _DIRENT_MATCHES_DIRENT64)) || (__CRT_HAVE___libc_readdir && !__CRT_KOS && (!__USE_FILE_OFFSET64 || _DIRENT_MATCHES_DIRENT64)) || (__CRT_HAVE_readdir64 && !__CRT_KOS && (__USE_FILE_OFFSET64 || _DIRENT_MATCHES_DIRENT64)) || __USE_DOS_DIRENT)) */
#undef __local_fdwalk_defined
#endif /* ((!__CRT_HAVE_fcntl && !__CRT_HAVE___fcntl && !__CRT_HAVE___libc_fcntl) || !__F_NEXT) && (!__OS_HAVE_PROCFS_SELF_FD || (!__CRT_HAVE_opendir && !__CRT_HAVE___libc_opendir && (!__AT_FDCWD || (!__CRT_HAVE_opendirat && !__CRT_HAVE_fopendirat && (!__CRT_HAVE_fdopendir || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)))) && (!__CRT_HAVE_fdopendir || (!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)))) && !__USE_DOS_DIRENT) || ((!__CRT_HAVE_readdirk || !__CRT_KOS || (__USE_FILE_OFFSET64 && !_DIRENT_MATCHES_DIRENT64)) && (!__CRT_HAVE_readdirk64 || !__CRT_KOS || (!__USE_FILE_OFFSET64 && !_DIRENT_MATCHES_DIRENT64)) && (!__CRT_HAVE_readdir || __CRT_KOS || (__USE_FILE_OFFSET64 && !_DIRENT_MATCHES_DIRENT64)) && (!__CRT_HAVE___libc_readdir || __CRT_KOS || (__USE_FILE_OFFSET64 && !_DIRENT_MATCHES_DIRENT64)) && (!__CRT_HAVE_readdir64 || __CRT_KOS || (!__USE_FILE_OFFSET64 && !_DIRENT_MATCHES_DIRENT64)) && !__USE_DOS_DIRENT)) */
#endif /* !__local_fdwalk_defined */
