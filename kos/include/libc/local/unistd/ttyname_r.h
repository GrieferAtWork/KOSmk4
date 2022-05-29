/* HASH CRC-32:0x6fea8103 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_ttyname_r_defined
#define __local_ttyname_r_defined
#include <__crt.h>
#include <paths.h>
#include <asm/os/fcntl.h>
#include <bits/os/dirent.h>
#include <features.h>
#include <asm/os/oflags.h>
#include <bits/os/stat.h>
#if defined(__CRT_HAVE_frealpath4) || ((defined(__CRT_HAVE_opendir) || defined(__CRT_HAVE___libc_opendir) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_opendirat) || defined(__CRT_HAVE_fopendirat) || (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))) || (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))) || defined(__USE_DOS_DIRENT)) && ((defined(__CRT_HAVE_readdirk) && defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE_readdirk64) && defined(__CRT_KOS)) || (defined(__CRT_HAVE_readdir) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE___libc_readdir) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE_readdir64) && !defined(__CRT_KOS)) || (defined(__USE_DOS_DIRENT) && defined(_DIRENT_MATCHES_DIRENT64))) && ((defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__fstat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE_fstat) && defined(__STAT32_MATCHES_STAT64)) || defined(__CRT_HAVE_fstat64)) && ((defined(__CRT_HAVE_klstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_klstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE_lstat) && defined(__STAT32_MATCHES_STAT64)) || defined(__CRT_HAVE_lstat64)) && defined(_PATH_DEV))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
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
#if !defined(__local___localdep_dirfd_defined) && defined(__CRT_HAVE_dirfd)
#define __local___localdep_dirfd_defined
__NAMESPACE_LOCAL_END
struct __dirstream;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_IN(1),__fd_t,__NOTHROW_NCX,__localdep_dirfd,(struct __dirstream __KOS_FIXED_CONST *__restrict __dirp),dirfd,(__dirp))
#endif /* !__local___localdep_dirfd_defined && __CRT_HAVE_dirfd */
#if !defined(__local___localdep_frealpath4_defined) && defined(__CRT_HAVE_frealpath4)
#define __local___localdep_frealpath4_defined
__CREDIRECT(__ATTR_WUNUSED __ATTR_OUT_OPT(2),char *,__NOTHROW_RPC,__localdep_frealpath4,(__fd_t __fd, char *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags),frealpath4,(__fd,__resolved,__buflen,__flags))
#endif /* !__local___localdep_frealpath4_defined && __CRT_HAVE_frealpath4 */
#ifndef __local___localdep_fstat64_defined
#define __local___localdep_fstat64_defined
#if defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat64,(__fd_t __fd, struct __stat64 *__restrict __buf),kfstat,(__fd,__buf))
#elif defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat64,(__fd_t __fd, struct __stat64 *__restrict __buf),kfstat64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat64,(__fd_t __fd, struct __stat64 *__restrict __buf),_fstat64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat64,(__fd_t __fd, struct __stat64 *__restrict __buf),_fstat64i32,(__fd,__buf))
#elif defined(__CRT_HAVE__fstati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat64,(__fd_t __fd, struct __stat64 *__restrict __buf),_fstati64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat64,(__fd_t __fd, struct __stat64 *__restrict __buf),_fstat32i64,(__fd,__buf))
#elif defined(__CRT_HAVE_fstat) && defined(__STAT32_MATCHES_STAT64)
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat64,(__fd_t __fd, struct __stat64 *__restrict __buf),fstat,(__fd,__buf))
#elif defined(__CRT_HAVE_fstat64)
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat64,(__fd_t __fd, struct __stat64 *__restrict __buf),fstat64,(__fd,__buf))
#else /* ... */
#undef __local___localdep_fstat64_defined
#endif /* !... */
#endif /* !__local___localdep_fstat64_defined */
#ifndef __local___localdep_fstatat64_defined
#define __local___localdep_fstatat64_defined
#if defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),int,__NOTHROW_NCX,__localdep_fstatat64,(__fd_t __dirfd, char const *__restrict __filename, struct __stat64 *__restrict __buf, __atflag_t __flags),kfstatat,(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),int,__NOTHROW_NCX,__localdep_fstatat64,(__fd_t __dirfd, char const *__restrict __filename, struct __stat64 *__restrict __buf, __atflag_t __flags),kfstatat64,(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE_fstatat) && defined(__STAT32_MATCHES_STAT64)
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),int,__NOTHROW_NCX,__localdep_fstatat64,(__fd_t __dirfd, char const *__restrict __filename, struct __stat64 *__restrict __buf, __atflag_t __flags),fstatat,(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE_fstatat64)
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),int,__NOTHROW_NCX,__localdep_fstatat64,(__fd_t __dirfd, char const *__restrict __filename, struct __stat64 *__restrict __buf, __atflag_t __flags),fstatat64,(__dirfd,__filename,__buf,__flags))
#else /* ... */
#undef __local___localdep_fstatat64_defined
#endif /* !... */
#endif /* !__local___localdep_fstatat64_defined */
#ifndef __local___localdep_isatty_defined
#define __local___localdep_isatty_defined
#ifdef __CRT_HAVE_isatty
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isatty,(__fd_t __fd),isatty,(__fd))
#elif defined(__CRT_HAVE__isatty)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isatty,(__fd_t __fd),_isatty,(__fd))
#elif defined(__CRT_HAVE___isatty)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_isatty,(__fd_t __fd),__isatty,(__fd))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <asm/os/tty.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/isatty.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isatty __LIBC_LOCAL_NAME(isatty)
#else /* __CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA) */
#undef __local___localdep_isatty_defined
#endif /* !__CRT_HAVE_tcgetattr && !__CRT_HAVE___tcgetattr && ((!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl) || !__TCGETA) */
#endif /* !... */
#endif /* !__local___localdep_isatty_defined */
#ifndef __local___localdep_lstat64_defined
#define __local___localdep_lstat64_defined
#if defined(__CRT_HAVE_klstat) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat64,(char const *__restrict __filename, struct __stat64 *__restrict __buf),klstat,(__filename,__buf))
#elif defined(__CRT_HAVE_klstat64) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat64,(char const *__restrict __filename, struct __stat64 *__restrict __buf),klstat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat64,(char const *__restrict __filename, struct __stat64 *__restrict __buf),_stat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat64,(char const *__restrict __filename, struct __stat64 *__restrict __buf),_stat64i32,(__filename,__buf))
#elif defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat64,(char const *__restrict __filename, struct __stat64 *__restrict __buf),_stati64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat64,(char const *__restrict __filename, struct __stat64 *__restrict __buf),_stat32i64,(__filename,__buf))
#elif defined(__CRT_HAVE_lstat) && defined(__STAT32_MATCHES_STAT64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat64,(char const *__restrict __filename, struct __stat64 *__restrict __buf),lstat,(__filename,__buf))
#elif defined(__CRT_HAVE_lstat64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_lstat64,(char const *__restrict __filename, struct __stat64 *__restrict __buf),lstat64,(__filename,__buf))
#else /* ... */
#undef __local___localdep_lstat64_defined
#endif /* !... */
#endif /* !__local___localdep_lstat64_defined */
#ifndef __local___localdep_memcpy_defined
#define __local___localdep_memcpy_defined
#ifdef __CRT_HAVE_memcpy
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpy __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#endif /* !__local___localdep_memcpy_defined */
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
#ifndef __local___localdep_readdir64_defined
#define __local___localdep_readdir64_defined
#if defined(__CRT_HAVE_readdirk) && defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)
__NAMESPACE_LOCAL_END
struct __dirstream;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(1),struct __dirent64 *,__NOTHROW_RPC,__localdep_readdir64,(struct __dirstream *__restrict __dirp),readdirk,(__dirp))
#elif defined(__CRT_HAVE_readdirk64) && defined(__CRT_KOS)
__NAMESPACE_LOCAL_END
struct __dirstream;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(1),struct __dirent64 *,__NOTHROW_RPC,__localdep_readdir64,(struct __dirstream *__restrict __dirp),readdirk64,(__dirp))
#elif defined(__CRT_HAVE_readdir) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)
__NAMESPACE_LOCAL_END
struct __dirstream;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(1),struct __dirent64 *,__NOTHROW_RPC,__localdep_readdir64,(struct __dirstream *__restrict __dirp),readdir,(__dirp))
#elif defined(__CRT_HAVE___libc_readdir) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)
__NAMESPACE_LOCAL_END
struct __dirstream;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(1),struct __dirent64 *,__NOTHROW_RPC,__localdep_readdir64,(struct __dirstream *__restrict __dirp),__libc_readdir,(__dirp))
#elif defined(__CRT_HAVE_readdir64) && !defined(__CRT_KOS)
__NAMESPACE_LOCAL_END
struct __dirstream;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(1),struct __dirent64 *,__NOTHROW_RPC,__localdep_readdir64,(struct __dirstream *__restrict __dirp),readdir64,(__dirp))
#elif defined(__USE_DOS_DIRENT) && defined(_DIRENT_MATCHES_DIRENT64)
__NAMESPACE_LOCAL_END
#include <libc/local/dirent/readdir.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_readdir64 __NAMESPACE_LOCAL_TYPEHAX(struct __dirent64 *(__LIBCCALL*)(struct __dirstream *__restrict),struct __dirent64 *(__LIBCCALL&)(struct __dirstream *__restrict),readdir)
#else /* ... */
#undef __local___localdep_readdir64_defined
#endif /* !... */
#endif /* !__local___localdep_readdir64_defined */
#ifndef __local___localdep_strcmp_defined
#define __local___localdep_strcmp_defined
#if __has_builtin(__builtin_strcmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,{ return __builtin_strcmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,(__s1,__s2))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strcmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strcmp __LIBC_LOCAL_NAME(strcmp)
#endif /* !... */
#endif /* !__local___localdep_strcmp_defined */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
#include <asm/os/dirent.h>
#include <asm/os/stat.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ttyname_r) __ATTR_OUTS(2, 3) __errno_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(ttyname_r))(__fd_t __fd, char *__buf, __SIZE_TYPE__ __buflen) {

	/* Ensure that it's actually a TTY */
#if defined(__CRT_HAVE_isatty) || defined(__CRT_HAVE__isatty) || defined(__CRT_HAVE___isatty) || defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))
	if __unlikely(!(__NAMESPACE_LOCAL_SYM __localdep_isatty)(__fd)) {
#ifdef __ENOTTY
		__libc_seterrno(__ENOTTY);
		return __ENOTTY;
#else /* __ENOTTY */
		__libc_seterrno(1);
		return 1;
#endif /* !__ENOTTY */
	}
#endif /* __CRT_HAVE_isatty || __CRT_HAVE__isatty || __CRT_HAVE___isatty || __CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA) */

	/* Simply try to realpath() the given `fd' */
#ifdef __CRT_HAVE_frealpath4
	if __unlikely(!__buf || !__buflen) {
#ifdef __ERANGE
		__libc_seterrno(__ERANGE);
		return __ERANGE;
#else /* __ERANGE */
		__libc_seterrno(1);
		return 1;
#endif /* !__ERANGE */
	}
	if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_frealpath4)(__fd, __buf, __buflen, 0))
		return 0; /* Found it! */
	if (__libc_geterrno() == __ERANGE)
		return __ERANGE;
#endif /* __CRT_HAVE_frealpath4 */

	/* Fallback: Search `/dev' for the proper file */
#if (defined(__CRT_HAVE_opendir) || defined(__CRT_HAVE___libc_opendir) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_opendirat) || defined(__CRT_HAVE_fopendirat) || (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))) || (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))) || defined(__USE_DOS_DIRENT)) && ((defined(__CRT_HAVE_readdirk) && defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE_readdirk64) && defined(__CRT_KOS)) || (defined(__CRT_HAVE_readdir) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE___libc_readdir) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE_readdir64) && !defined(__CRT_KOS)) || (defined(__USE_DOS_DIRENT) && defined(_DIRENT_MATCHES_DIRENT64))) && ((defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__fstat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE_fstat) && defined(__STAT32_MATCHES_STAT64)) || defined(__CRT_HAVE_fstat64)) && ((defined(__CRT_HAVE_klstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_klstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE_lstat) && defined(__STAT32_MATCHES_STAT64)) || defined(__CRT_HAVE_lstat64)) && defined(_PATH_DEV)
	{
		struct __stat64 __st;
		struct __dirent64 *__d;
		struct __dirstream *__dirstream;
		__dev_t __rdev;
		__ino64_t __ino;
#ifdef __libc_geterrno
		__errno_t __saved_errno;
#endif /* __libc_geterrno */
		if __unlikely(__buflen < __COMPILER_STRLEN(_PATH_DEV) * sizeof(char)) {
			__libc_seterrno(__ERANGE);
			return __ERANGE;
		}
		if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_fstat64)(__fd, &__st) < 0)
			return __libc_geterrno();
		if ((__dirstream = (__NAMESPACE_LOCAL_SYM __localdep_opendir)(_PATH_DEV)) == __NULLPTR)
			return __libc_geterrno();
		(__NAMESPACE_LOCAL_SYM __localdep_memcpy)(__buf, _PATH_DEV, __COMPILER_STRLEN(_PATH_DEV) * sizeof(char));
		__buflen -= __COMPILER_STRLEN(_PATH_DEV) * sizeof(char);
#ifdef __libc_geterrno
		__saved_errno = __libc_geterrno();
#endif /* __libc_geterrno */
		__rdev = __st.st_dev;
		__ino  = __st.st_ino;
		while ((__d = (__NAMESPACE_LOCAL_SYM __localdep_readdir64)(__dirstream)) != __NULLPTR) {
			__SIZE_TYPE__ __needed;
	
			/* We're looking for character devices. */
			if (__d->d_type != __DT_CHR)
				continue;
			if (__d->d_ino != __ino)
				continue;
	
#ifndef __KOS__
			/* On KOS, these are symlinks (DT_LNK), so we've already skipped them ;) */
			if ((__NAMESPACE_LOCAL_SYM __localdep_strcmp)(__d->d_name, "stdin") == 0)
				continue; /* Ignore the /dev/std(in|out|err) aliases */
			if ((__NAMESPACE_LOCAL_SYM __localdep_strcmp)(__d->d_name, "stdout") == 0)
				continue; /* *ditto* */
			if ((__NAMESPACE_LOCAL_SYM __localdep_strcmp)(__d->d_name, "stderr") == 0)
				continue; /* *ditto* */
#endif /* !__KOS__ */

			/* Load the length of the directory entry's filename. */
#ifdef _DIRENT_HAVE_D_NAMLEN
			__needed = __d->d_namlen;
#else /* _DIRENT_HAVE_D_NAMLEN */
			__needed = (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__d->d_name);
#endif /* !_DIRENT_HAVE_D_NAMLEN */

			/* Check that the user-supplied buffer is large enough. */
			if (__needed >= __buflen) {
#if defined(__CRT_HAVE_closedir) || defined(__CRT_HAVE___libc_closedir) || defined(__USE_DOS_DIRENT)
				(__NAMESPACE_LOCAL_SYM __localdep_closedir)(__dirstream);
#endif /* __CRT_HAVE_closedir || __CRT_HAVE___libc_closedir || __USE_DOS_DIRENT */
#ifdef __ERANGE
				__libc_seterrno(__ERANGE);
				return __ERANGE;
#else /* __ERANGE */
				__libc_seterrno(1);
				return 1;
#endif /* !__ERANGE */
			}
			(__NAMESPACE_LOCAL_SYM __localdep_memcpy)(__buf + __COMPILER_STRLEN(_PATH_DEV),
			       __d->d_name, (__needed + 1) * sizeof(char));

			/* Load attributes of the file being enumerated */
#if ((defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_fstatat) && defined(__STAT32_MATCHES_STAT64)) || defined(__CRT_HAVE_fstatat64)) && defined(__CRT_HAVE_dirfd) && defined(__AT_SYMLINK_NOFOLLOW)
			if ((__NAMESPACE_LOCAL_SYM __localdep_fstatat64)((__NAMESPACE_LOCAL_SYM __localdep_dirfd)(__dirstream), __d->d_name, &__st, __AT_SYMLINK_NOFOLLOW) != 0)
				continue;
#else /* ((__CRT_HAVE_kfstatat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstatat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE_fstatat && __STAT32_MATCHES_STAT64) || __CRT_HAVE_fstatat64) && __CRT_HAVE_dirfd && __AT_SYMLINK_NOFOLLOW */
			if ((__NAMESPACE_LOCAL_SYM __localdep_lstat64)(__buf, &__st) != 0)
				continue;
#endif /* ((!__CRT_HAVE_kfstatat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kfstatat64 || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_fstatat || !__STAT32_MATCHES_STAT64) && !__CRT_HAVE_fstatat64) || !__CRT_HAVE_dirfd || !__AT_SYMLINK_NOFOLLOW */

			/* Verify that this is the file we're looking for. */
			if (__st.st_rdev != __rdev)
				continue;
			if __unlikely(__st.st_ino != __ino)
				continue;
			if __unlikely(!__S_ISCHR(__st.st_mode))
				continue;
	
			/* Found it! */
#if defined(__CRT_HAVE_closedir) || defined(__CRT_HAVE___libc_closedir) || defined(__USE_DOS_DIRENT)
			(__NAMESPACE_LOCAL_SYM __localdep_closedir)(__dirstream);
#endif /* __CRT_HAVE_closedir || __CRT_HAVE___libc_closedir || __USE_DOS_DIRENT */
#ifdef __libc_geterrno
			__libc_seterrno(__saved_errno);
#endif /* __libc_geterrno */
			return 0;
		}
#if defined(__CRT_HAVE_closedir) || defined(__CRT_HAVE___libc_closedir) || defined(__USE_DOS_DIRENT)
		(__NAMESPACE_LOCAL_SYM __localdep_closedir)(__dirstream);
#endif /* __CRT_HAVE_closedir || __CRT_HAVE___libc_closedir || __USE_DOS_DIRENT */
#ifdef __libc_geterrno
		__libc_seterrno(__saved_errno);
#endif /* __libc_geterrno */
	}
#endif /* (__CRT_HAVE_opendir || __CRT_HAVE___libc_opendir || (__AT_FDCWD && (__CRT_HAVE_opendirat || __CRT_HAVE_fopendirat || (__CRT_HAVE_fdopendir && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)))) || (__CRT_HAVE_fdopendir && (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)))) || __USE_DOS_DIRENT) && ((__CRT_HAVE_readdirk && __CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE_readdirk64 && __CRT_KOS) || (__CRT_HAVE_readdir && !__CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE___libc_readdir && !__CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE_readdir64 && !__CRT_KOS) || (__USE_DOS_DIRENT && _DIRENT_MATCHES_DIRENT64)) && ((__CRT_HAVE_kfstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__fstat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__fstat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__fstati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE__fstat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE_fstat && __STAT32_MATCHES_STAT64) || __CRT_HAVE_fstat64) && ((__CRT_HAVE_klstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_klstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__stat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE__stat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE_lstat && __STAT32_MATCHES_STAT64) || __CRT_HAVE_lstat64) && _PATH_DEV */

	/* Fallback: indicate that this isn't a terminal... */
#ifdef __ENOTTY
	return __ENOTTY;
#else /* __ENOTTY */
	return 1;
#endif /* !__ENOTTY */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ttyname_r_defined
#define __local___localdep_ttyname_r_defined
#define __localdep_ttyname_r __LIBC_LOCAL_NAME(ttyname_r)
#endif /* !__local___localdep_ttyname_r_defined */
#else /* __CRT_HAVE_frealpath4 || ((__CRT_HAVE_opendir || __CRT_HAVE___libc_opendir || (__AT_FDCWD && (__CRT_HAVE_opendirat || __CRT_HAVE_fopendirat || (__CRT_HAVE_fdopendir && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)))) || (__CRT_HAVE_fdopendir && (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)))) || __USE_DOS_DIRENT) && ((__CRT_HAVE_readdirk && __CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE_readdirk64 && __CRT_KOS) || (__CRT_HAVE_readdir && !__CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE___libc_readdir && !__CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE_readdir64 && !__CRT_KOS) || (__USE_DOS_DIRENT && _DIRENT_MATCHES_DIRENT64)) && ((__CRT_HAVE_kfstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__fstat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__fstat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__fstati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE__fstat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE_fstat && __STAT32_MATCHES_STAT64) || __CRT_HAVE_fstat64) && ((__CRT_HAVE_klstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_klstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__stat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE__stat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE_lstat && __STAT32_MATCHES_STAT64) || __CRT_HAVE_lstat64) && _PATH_DEV) */
#undef __local_ttyname_r_defined
#endif /* !__CRT_HAVE_frealpath4 && ((!__CRT_HAVE_opendir && !__CRT_HAVE___libc_opendir && (!__AT_FDCWD || (!__CRT_HAVE_opendirat && !__CRT_HAVE_fopendirat && (!__CRT_HAVE_fdopendir || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)))) && (!__CRT_HAVE_fdopendir || (!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)))) && !__USE_DOS_DIRENT) || ((!__CRT_HAVE_readdirk || !__CRT_KOS || !_DIRENT_MATCHES_DIRENT64) && (!__CRT_HAVE_readdirk64 || !__CRT_KOS) && (!__CRT_HAVE_readdir || __CRT_KOS || !_DIRENT_MATCHES_DIRENT64) && (!__CRT_HAVE___libc_readdir || __CRT_KOS || !_DIRENT_MATCHES_DIRENT64) && (!__CRT_HAVE_readdir64 || __CRT_KOS) && (!__USE_DOS_DIRENT || !_DIRENT_MATCHES_DIRENT64)) || ((!__CRT_HAVE_kfstat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kfstat64 || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE__fstat64 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__fstat64i32 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__fstati64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64) && (!__CRT_HAVE__fstat32i64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64) && (!__CRT_HAVE_fstat || !__STAT32_MATCHES_STAT64) && !__CRT_HAVE_fstat64) || ((!__CRT_HAVE_klstat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_klstat64 || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE__stat64 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__stat64i32 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__stati64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64) && (!__CRT_HAVE__stat32i64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64) && (!__CRT_HAVE_lstat || !__STAT32_MATCHES_STAT64) && !__CRT_HAVE_lstat64) || !_PATH_DEV) */
#endif /* !__local_ttyname_r_defined */
