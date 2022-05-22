/* HASH CRC-32:0xc9b6916f */
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
/* (>) Standard: POSIX.1b (Issue 2, IEEE Std 1003.1b-1993) */
/* (#) Portability: Cygwin        (/newlib/libc/include/dirent.h) */
/* (#) Portability: DJGPP         (/include/dirent.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/dirent.h) */
/* (#) Portability: FreeBSD       (/include/dirent.h) */
/* (#) Portability: GNU C Library (/dirent/dirent.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/dirent.h) */
/* (#) Portability: NetBSD        (/include/dirent.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/dirent.h) */
/* (#) Portability: OpenBSD       (/include/dirent.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/dirent.h) */
/* (#) Portability: diet libc     (/include/dirent.h) */
/* (#) Portability: libc4/5       (/include/dirent.h) */
/* (#) Portability: libc6         (/include/dirent.h) */
/* (#) Portability: libcmini      (/include/dirent.h) */
/* (#) Portability: mintlib       (/include/dirent.h) */
/* (#) Portability: musl libc     (/include/dirent.h) */
/* (#) Portability: uClibc        (/include/dirent.h) */
#ifndef _DIRENT_H
#define _DIRENT_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/os/dirent.h>
#include <bits/os/dirent.h>
#include <bits/types.h>

__SYSDECL_BEGIN

#ifdef __USE_MISC
#ifndef DT_UNKNOWN
#if (defined(__DT_UNKNOWN) || defined(__DT_FIFO) || \
     defined(__DT_CHR) || defined(__DT_DIR) ||      \
     defined(__DT_BLK) || defined(__DT_REG) ||      \
     defined(__DT_LNK) || defined(__DT_SOCK) ||     \
     defined(__DT_WHT))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __DT_UNKNOWN
	DT_UNKNOWN = __DT_UNKNOWN, /* Unknown file type */
#endif /* __DT_UNKNOWN */
#ifdef __DT_FIFO
	DT_FIFO    = __DT_FIFO,    /* FistInFirstOut (pipe) file (s.a. `S_ISFIFO()', `S_IFMT & S_IFIFO') */
#endif /* __DT_FIFO */
#ifdef __DT_CHR
	DT_CHR     = __DT_CHR,     /* Character device file      (s.a. `S_ISCHR()', `S_IFMT & S_IFCHR') */
#endif /* __DT_CHR */
#ifdef __DT_DIR
	DT_DIR     = __DT_DIR,     /* Directory                  (s.a. `S_ISDIR()', `S_IFMT & S_IFDIR') */
#endif /* __DT_DIR */
#ifdef __DT_BLK
	DT_BLK     = __DT_BLK,     /* Block device file          (s.a. `S_ISBLK()', `S_IFMT & S_IFBLK') */
#endif /* __DT_BLK */
#ifdef __DT_REG
	DT_REG     = __DT_REG,     /* Regular text file          (s.a. `S_ISREG()', `S_IFMT & S_IFREG') */
#endif /* __DT_REG */
#ifdef __DT_LNK
	DT_LNK     = __DT_LNK,     /* Symbolic link              (s.a. `S_ISLNK()', `S_IFMT & S_IFLNK') */
#endif /* __DT_LNK */
#ifdef __DT_SOCK
	DT_SOCK    = __DT_SOCK,    /* Socket file                (s.a. `S_ISSOCK()', `S_IFMT & S_IFSOCK') */
#endif /* __DT_SOCK */
#ifdef __DT_WHT
	DT_WHT     = __DT_WHT,     /* Mounting point? */
#endif /* __DT_WHT */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __DT_UNKNOWN
#define DT_UNKNOWN DT_UNKNOWN /* Unknown file type */
#endif /* __DT_UNKNOWN */
#ifdef __DT_FIFO
#define DT_FIFO    DT_FIFO    /* FistInFirstOut (pipe) file (s.a. `S_ISFIFO()', `S_IFMT & S_IFIFO') */
#endif /* __DT_FIFO */
#ifdef __DT_CHR
#define DT_CHR     DT_CHR     /* Character device file      (s.a. `S_ISCHR()', `S_IFMT & S_IFCHR') */
#endif /* __DT_CHR */
#ifdef __DT_DIR
#define DT_DIR     DT_DIR     /* Directory                  (s.a. `S_ISDIR()', `S_IFMT & S_IFDIR') */
#endif /* __DT_DIR */
#ifdef __DT_BLK
#define DT_BLK     DT_BLK     /* Block device file          (s.a. `S_ISBLK()', `S_IFMT & S_IFBLK') */
#endif /* __DT_BLK */
#ifdef __DT_REG
#define DT_REG     DT_REG     /* Regular text file          (s.a. `S_ISREG()', `S_IFMT & S_IFREG') */
#endif /* __DT_REG */
#ifdef __DT_LNK
#define DT_LNK     DT_LNK     /* Symbolic link              (s.a. `S_ISLNK()', `S_IFMT & S_IFLNK') */
#endif /* __DT_LNK */
#ifdef __DT_SOCK
#define DT_SOCK    DT_SOCK    /* Socket file                (s.a. `S_ISSOCK()', `S_IFMT & S_IFSOCK') */
#endif /* __DT_SOCK */
#ifdef __DT_WHT
#define DT_WHT     DT_WHT     /* Mounting point? */
#endif /* __DT_WHT */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __DT_UNKNOWN
#define DT_UNKNOWN __DT_UNKNOWN /* Unknown file type */
#endif /* __DT_UNKNOWN */
#ifdef __DT_FIFO
#define DT_FIFO    __DT_FIFO    /* FistInFirstOut (pipe) file (s.a. `S_ISFIFO()', `S_IFMT & S_IFIFO') */
#endif /* __DT_FIFO */
#ifdef __DT_CHR
#define DT_CHR     __DT_CHR     /* Character device file      (s.a. `S_ISCHR()', `S_IFMT & S_IFCHR') */
#endif /* __DT_CHR */
#ifdef __DT_DIR
#define DT_DIR     __DT_DIR     /* Directory                  (s.a. `S_ISDIR()', `S_IFMT & S_IFDIR') */
#endif /* __DT_DIR */
#ifdef __DT_BLK
#define DT_BLK     __DT_BLK     /* Block device file          (s.a. `S_ISBLK()', `S_IFMT & S_IFBLK') */
#endif /* __DT_BLK */
#ifdef __DT_REG
#define DT_REG     __DT_REG     /* Regular text file          (s.a. `S_ISREG()', `S_IFMT & S_IFREG') */
#endif /* __DT_REG */
#ifdef __DT_LNK
#define DT_LNK     __DT_LNK     /* Symbolic link              (s.a. `S_ISLNK()', `S_IFMT & S_IFLNK') */
#endif /* __DT_LNK */
#ifdef __DT_SOCK
#define DT_SOCK    __DT_SOCK    /* Socket file                (s.a. `S_ISSOCK()', `S_IFMT & S_IFSOCK') */
#endif /* __DT_SOCK */
#ifdef __DT_WHT
#define DT_WHT     __DT_WHT     /* Mounting point? */
#endif /* __DT_WHT */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */
#endif /* !DT_UNKNOWN */

/* Convert between stat structure types and directory types. */
#ifndef IFTODT
#ifdef __IFTODT
#define IFTODT(mode) __IFTODT(mode)
#endif /* __IFTODT */
#ifdef __DTTOIF
#define DTTOIF(dirtype) __DTTOIF(dirtype)
#endif /* __DTTOIF */
#endif /* !IFTODT */

#if defined(__USE_XOPEN2K8) && !defined(MAXNAMLEN)
#include <asm/os/limits.h>
#if defined(__NAME_MAX) && (__NAME_MAX + 0) != -1
#define MAXNAMLEN __NAME_MAX /* Max # of chars in a file name */
#else /* __NAME_MAX != -1 */
#define MAXNAMLEN 255        /* Max # of chars in a file name */
#endif /* __NAME_MAX == -1 */
#endif /* __USE_XOPEN2K8 && !MAXNAMLEN */
#endif /* __USE_MISC */


#ifdef __CC__
#ifdef _DIRENT_HAVE_D_NAMLEN
#define _D_EXACT_NAMLEN(d) ((d)->d_namlen)
#define _D_ALLOC_NAMLEN(d) (_D_EXACT_NAMLEN(d) + 1)
#else /* _DIRENT_HAVE_D_NAMLEN */
__SYSDECL_END
#include <libc/string.h>
__SYSDECL_BEGIN
#define _D_EXACT_NAMLEN(d) __libc_strlen((d)->d_name)
#ifdef _DIRENT_HAVE_D_RECLEN
#define _D_ALLOC_NAMLEN(d) (((char *)(d) + (d)->d_reclen) - &(d)->d_name[0])
#else /* _DIRENT_HAVE_D_RECLEN */
#define _D_ALLOC_NAMLEN(d) (sizeof((d)->d_name) > 1 ? sizeof((d)->d_name) : _D_EXACT_NAMLEN(d) + 1)
#endif /* !_DIRENT_HAVE_D_RECLEN */
#endif /* !_DIRENT_HAVE_D_NAMLEN */

#ifdef __USE_XOPEN
#ifndef __ino_t_defined
#define __ino_t_defined
typedef __FS_TYPE(ino) ino_t; /* INode number */
#endif /* !__ino_t_defined */
#ifdef __USE_LARGEFILE64
#ifndef __ino64_t_defined
#define __ino64_t_defined
typedef __ino64_t ino64_t; /* INode number */
#endif /* !__ino64_t_defined */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN */

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __DIR_defined
#define __DIR_defined
typedef struct __dirstream DIR;
#endif /* !__DIR_defined */

#ifdef __CRT_HAVE_opendir
/* >> opendir(3)
 * Open and return a new directory stream for reading, referring to `name' */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),DIR *,__NOTHROW_RPC,opendir,(char const *__name),(__name))
#elif defined(__CRT_HAVE___libc_opendir)
/* >> opendir(3)
 * Open and return a new directory stream for reading, referring to `name' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),DIR *,__NOTHROW_RPC,opendir,(char const *__name),__libc_opendir,(__name))
#else /* ... */
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#if (defined(__AT_FDCWD) && (defined(__CRT_HAVE_opendirat) || defined(__CRT_HAVE_fopendirat) || (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))) || (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))) || defined(__USE_DOS_DIRENT)
#include <libc/local/dirent/opendir.h>
/* >> opendir(3)
 * Open and return a new directory stream for reading, referring to `name' */
__NAMESPACE_LOCAL_USING_OR_IMPL(opendir, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) DIR *__NOTHROW_RPC(__LIBCCALL opendir)(char const *__name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(opendir))(__name); })
#endif /* (__AT_FDCWD && (__CRT_HAVE_opendirat || __CRT_HAVE_fopendirat || (__CRT_HAVE_fdopendir && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)))) || (__CRT_HAVE_fdopendir && (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)))) || __USE_DOS_DIRENT */
#endif /* !... */

#if defined(__USE_KOS) && defined(__USE_ATFILE)
#ifdef __CRT_HAVE_fopendirat
/* >> fopendirat(3)
 * Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(2),DIR *,__NOTHROW_RPC,fopendirat,(__fd_t __dirfd, char const *__name, __oflag_t __oflags),(__dirfd,__name,__oflags))
#else /* __CRT_HAVE_fopendirat */
#include <asm/os/oflags.h>
#if defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))
#include <libc/local/dirent/fopendirat.h>
/* >> fopendirat(3)
 * Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fopendirat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) DIR *__NOTHROW_RPC(__LIBCCALL fopendirat)(__fd_t __dirfd, char const *__name, __oflag_t __oflags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fopendirat))(__dirfd, __name, __oflags); })
#endif /* __CRT_HAVE_fdopendir && (__CRT_HAVE_openat64 || __CRT_HAVE_openat) */
#endif /* !__CRT_HAVE_fopendirat */
#ifdef __CRT_HAVE_opendirat
/* >> opendirat(3)
 * Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(2),DIR *,__NOTHROW_RPC,opendirat,(__fd_t __dirfd, char const *__name),(__dirfd,__name))
#else /* __CRT_HAVE_opendirat */
#include <asm/os/oflags.h>
#if defined(__CRT_HAVE_fopendirat) || (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#include <libc/local/dirent/opendirat.h>
/* >> opendirat(3)
 * Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(opendirat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) DIR *__NOTHROW_RPC(__LIBCCALL opendirat)(__fd_t __dirfd, char const *__name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(opendirat))(__dirfd, __name); })
#endif /* __CRT_HAVE_fopendirat || (__CRT_HAVE_fdopendir && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
#endif /* !__CRT_HAVE_opendirat */
#endif /* __USE_KOS && __USE_ATFILE */

#ifdef __CRT_HAVE_closedir
/* >> closedir(3)
 * Close a directory stream previously returned by `opendir(3)' and friends */
__CDECLARE(__ATTR_INOUT(1),int,__NOTHROW_NCX,closedir,(DIR *__dirp),(__dirp))
#elif defined(__CRT_HAVE___libc_closedir)
/* >> closedir(3)
 * Close a directory stream previously returned by `opendir(3)' and friends */
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_NCX,closedir,(DIR *__dirp),__libc_closedir,(__dirp))
#elif defined(__USE_DOS_DIRENT)
#include <libc/local/dirent/closedir.h>
/* >> closedir(3)
 * Close a directory stream previously returned by `opendir(3)' and friends */
__NAMESPACE_LOCAL_USING_OR_IMPL(closedir, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL closedir)(DIR *__dirp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(closedir))(__dirp); })
#endif /* ... */

#ifdef __USE_BSD
/* >> fdclosedir(3)
 * Same as `closedir()', but instead of also closing the underlying file descriptor, return it */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_INOUT(1),__fd_t,__NOTHROW_NCX,fdclosedir,(DIR *__dirp),(__dirp))
#endif /* __USE_BSD */

#if defined(__CRT_HAVE_readdirk) && defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> readdir(3), readdir64(3)
 * Read and return the next pending directory entry of the given directory stream `dirp'
 * @except: Returns `NULL' for end-of-directory; throws an error if something else went wrong */
__CREDIRECT(__ATTR_INOUT(1),struct dirent *,__NOTHROW_RPC,readdir,(DIR *__restrict __dirp),readdirk,(__dirp))
#elif defined(__CRT_HAVE_readdirk64) && defined(__CRT_KOS) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> readdir(3), readdir64(3)
 * Read and return the next pending directory entry of the given directory stream `dirp'
 * @except: Returns `NULL' for end-of-directory; throws an error if something else went wrong */
__CREDIRECT(__ATTR_INOUT(1),struct dirent *,__NOTHROW_RPC,readdir,(DIR *__restrict __dirp),readdirk64,(__dirp))
#elif defined(__CRT_HAVE_readdir) && !defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> readdir(3), readdir64(3)
 * Read and return the next pending directory entry of the given directory stream `dirp'
 * @except: Returns `NULL' for end-of-directory; throws an error if something else went wrong */
__CDECLARE(__ATTR_INOUT(1),struct dirent *,__NOTHROW_RPC,readdir,(DIR *__restrict __dirp),(__dirp))
#elif defined(__CRT_HAVE___libc_readdir) && !defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> readdir(3), readdir64(3)
 * Read and return the next pending directory entry of the given directory stream `dirp'
 * @except: Returns `NULL' for end-of-directory; throws an error if something else went wrong */
__CREDIRECT(__ATTR_INOUT(1),struct dirent *,__NOTHROW_RPC,readdir,(DIR *__restrict __dirp),__libc_readdir,(__dirp))
#elif defined(__CRT_HAVE_readdir64) && !defined(__CRT_KOS) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> readdir(3), readdir64(3)
 * Read and return the next pending directory entry of the given directory stream `dirp'
 * @except: Returns `NULL' for end-of-directory; throws an error if something else went wrong */
__CREDIRECT(__ATTR_INOUT(1),struct dirent *,__NOTHROW_RPC,readdir,(DIR *__restrict __dirp),readdir64,(__dirp))
#elif defined(__USE_DOS_DIRENT)
#include <libc/local/dirent/readdir.h>
/* >> readdir(3), readdir64(3)
 * Read and return the next pending directory entry of the given directory stream `dirp'
 * @except: Returns `NULL' for end-of-directory; throws an error if something else went wrong */
__NAMESPACE_LOCAL_USING_OR_IMPL(readdir, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) struct dirent *__NOTHROW_RPC(__LIBCCALL readdir)(DIR *__restrict __dirp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(readdir))(__dirp); })
#endif /* ... */

#ifdef __CRT_HAVE_rewinddir
/* >> rewinddir(3)
 * Rewind the given directory stream in such a way that the next call
 * to `readdir(3)' will once again  return the first directory  entry */
__CDECLARE_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,rewinddir,(DIR *__restrict __dirp),(__dirp))
#elif defined(__CRT_HAVE___libc_rewinddir)
/* >> rewinddir(3)
 * Rewind the given directory stream in such a way that the next call
 * to `readdir(3)' will once again  return the first directory  entry */
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,rewinddir,(DIR *__restrict __dirp),__libc_rewinddir,(__dirp))
#endif /* ... */

#ifdef __USE_XOPEN2K8
/* >> fdopendir(3)
 * Create a new directory stream by inheriting the given `fd' as stream handle */
__CDECLARE_OPT(__ATTR_WUNUSED,DIR *,__NOTHROW_NCX,fdopendir,(__fd_t __fd),(__fd))
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_readdirk) && defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)
/* >> readdir(3), readdir64(3)
 * Read and return the next pending directory entry of the given directory stream `dirp'
 * @except: Returns `NULL' for end-of-directory; throws an error if something else went wrong */
__CREDIRECT(__ATTR_INOUT(1),struct dirent64 *,__NOTHROW_RPC,readdir64,(DIR *__restrict __dirp),readdirk,(__dirp))
#elif defined(__CRT_HAVE_readdirk64) && defined(__CRT_KOS)
/* >> readdir(3), readdir64(3)
 * Read and return the next pending directory entry of the given directory stream `dirp'
 * @except: Returns `NULL' for end-of-directory; throws an error if something else went wrong */
__CREDIRECT(__ATTR_INOUT(1),struct dirent64 *,__NOTHROW_RPC,readdir64,(DIR *__restrict __dirp),readdirk64,(__dirp))
#elif defined(__CRT_HAVE_readdir) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)
/* >> readdir(3), readdir64(3)
 * Read and return the next pending directory entry of the given directory stream `dirp'
 * @except: Returns `NULL' for end-of-directory; throws an error if something else went wrong */
__CREDIRECT(__ATTR_INOUT(1),struct dirent64 *,__NOTHROW_RPC,readdir64,(DIR *__restrict __dirp),readdir,(__dirp))
#elif defined(__CRT_HAVE___libc_readdir) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)
/* >> readdir(3), readdir64(3)
 * Read and return the next pending directory entry of the given directory stream `dirp'
 * @except: Returns `NULL' for end-of-directory; throws an error if something else went wrong */
__CREDIRECT(__ATTR_INOUT(1),struct dirent64 *,__NOTHROW_RPC,readdir64,(DIR *__restrict __dirp),__libc_readdir,(__dirp))
#elif defined(__CRT_HAVE_readdir64) && !defined(__CRT_KOS)
/* >> readdir(3), readdir64(3)
 * Read and return the next pending directory entry of the given directory stream `dirp'
 * @except: Returns `NULL' for end-of-directory; throws an error if something else went wrong */
__CDECLARE(__ATTR_INOUT(1),struct dirent64 *,__NOTHROW_RPC,readdir64,(DIR *__restrict __dirp),(__dirp))
#elif defined(__USE_DOS_DIRENT) && defined(_DIRENT_MATCHES_DIRENT64)
#include <libc/local/dirent/readdir.h>
/* >> readdir(3), readdir64(3)
 * Read and return the next pending directory entry of the given directory stream `dirp'
 * @except: Returns `NULL' for end-of-directory; throws an error if something else went wrong */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) struct dirent64 *__NOTHROW_RPC(__LIBCCALL readdir64)(DIR *__restrict __dirp) { return (struct dirent64 *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(readdir))(__dirp); }
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#ifdef __USE_POSIX
#if defined(__CRT_HAVE_readdirk_r) && defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> readdir_r(3), readdir64_r(3)
 * Reentrant version of `readdir(3)'
 * NOTE: This ~reentrant~ version of readdir()  is strongly discouraged from being  used in KOS, as  the
 *       kernel does not impose a limit on the length of a single directory entry name (s.a. 'kreaddir')
 * >> Instead, simply use `readdir()' / `readdir64()', which will automatically (re-)allocate an internal,
 *    per-directory  buffer  of sufficient  size to  house any  directory entry  (s.a.: `READDIR_DEFAULT') */
__CREDIRECT(__ATTR_INOUT(1) __ATTR_OUT(2) __ATTR_OUT(3),int,__NOTHROW_RPC,readdir_r,(DIR *__restrict __dirp, struct dirent *__restrict __entry, struct dirent **__restrict __result),readdirk_r,(__dirp,__entry,__result))
#elif defined(__CRT_HAVE_readdirk64_r) && defined(__CRT_KOS) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> readdir_r(3), readdir64_r(3)
 * Reentrant version of `readdir(3)'
 * NOTE: This ~reentrant~ version of readdir()  is strongly discouraged from being  used in KOS, as  the
 *       kernel does not impose a limit on the length of a single directory entry name (s.a. 'kreaddir')
 * >> Instead, simply use `readdir()' / `readdir64()', which will automatically (re-)allocate an internal,
 *    per-directory  buffer  of sufficient  size to  house any  directory entry  (s.a.: `READDIR_DEFAULT') */
__CREDIRECT(__ATTR_INOUT(1) __ATTR_OUT(2) __ATTR_OUT(3),int,__NOTHROW_RPC,readdir_r,(DIR *__restrict __dirp, struct dirent *__restrict __entry, struct dirent **__restrict __result),readdirk64_r,(__dirp,__entry,__result))
#elif defined(__CRT_HAVE_readdir_r) && !defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> readdir_r(3), readdir64_r(3)
 * Reentrant version of `readdir(3)'
 * NOTE: This ~reentrant~ version of readdir()  is strongly discouraged from being  used in KOS, as  the
 *       kernel does not impose a limit on the length of a single directory entry name (s.a. 'kreaddir')
 * >> Instead, simply use `readdir()' / `readdir64()', which will automatically (re-)allocate an internal,
 *    per-directory  buffer  of sufficient  size to  house any  directory entry  (s.a.: `READDIR_DEFAULT') */
__CDECLARE(__ATTR_INOUT(1) __ATTR_OUT(2) __ATTR_OUT(3),int,__NOTHROW_RPC,readdir_r,(DIR *__restrict __dirp, struct dirent *__restrict __entry, struct dirent **__restrict __result),(__dirp,__entry,__result))
#elif defined(__CRT_HAVE___libc_readdir_r) && !defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> readdir_r(3), readdir64_r(3)
 * Reentrant version of `readdir(3)'
 * NOTE: This ~reentrant~ version of readdir()  is strongly discouraged from being  used in KOS, as  the
 *       kernel does not impose a limit on the length of a single directory entry name (s.a. 'kreaddir')
 * >> Instead, simply use `readdir()' / `readdir64()', which will automatically (re-)allocate an internal,
 *    per-directory  buffer  of sufficient  size to  house any  directory entry  (s.a.: `READDIR_DEFAULT') */
__CREDIRECT(__ATTR_INOUT(1) __ATTR_OUT(2) __ATTR_OUT(3),int,__NOTHROW_RPC,readdir_r,(DIR *__restrict __dirp, struct dirent *__restrict __entry, struct dirent **__restrict __result),__libc_readdir_r,(__dirp,__entry,__result))
#elif defined(__CRT_HAVE_readdir64_r) && !defined(__CRT_KOS) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> readdir_r(3), readdir64_r(3)
 * Reentrant version of `readdir(3)'
 * NOTE: This ~reentrant~ version of readdir()  is strongly discouraged from being  used in KOS, as  the
 *       kernel does not impose a limit on the length of a single directory entry name (s.a. 'kreaddir')
 * >> Instead, simply use `readdir()' / `readdir64()', which will automatically (re-)allocate an internal,
 *    per-directory  buffer  of sufficient  size to  house any  directory entry  (s.a.: `READDIR_DEFAULT') */
__CREDIRECT(__ATTR_INOUT(1) __ATTR_OUT(2) __ATTR_OUT(3),int,__NOTHROW_RPC,readdir_r,(DIR *__restrict __dirp, struct dirent *__restrict __entry, struct dirent **__restrict __result),readdir64_r,(__dirp,__entry,__result))
#endif /* ... */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_readdirk_r) && defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)
/* >> readdir(3), readdir64(3)
 * Read and return the next pending directory entry of the given directory stream `dirp'
 * @except: Returns `NULL' for end-of-directory; throws an error if something else went wrong */
__CREDIRECT(__ATTR_INOUT(1) __ATTR_OUT(2) __ATTR_OUT(3),int,__NOTHROW_RPC,readdir64_r,(DIR *__restrict __dirp, struct dirent64 *__restrict __entry, struct dirent64 **__restrict __result),readdirk_r,(__dirp,__entry,__result))
#elif defined(__CRT_HAVE_readdirk64_r) && defined(__CRT_KOS)
/* >> readdir(3), readdir64(3)
 * Read and return the next pending directory entry of the given directory stream `dirp'
 * @except: Returns `NULL' for end-of-directory; throws an error if something else went wrong */
__CREDIRECT(__ATTR_INOUT(1) __ATTR_OUT(2) __ATTR_OUT(3),int,__NOTHROW_RPC,readdir64_r,(DIR *__restrict __dirp, struct dirent64 *__restrict __entry, struct dirent64 **__restrict __result),readdirk64_r,(__dirp,__entry,__result))
#elif defined(__CRT_HAVE_readdir_r) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)
/* >> readdir(3), readdir64(3)
 * Read and return the next pending directory entry of the given directory stream `dirp'
 * @except: Returns `NULL' for end-of-directory; throws an error if something else went wrong */
__CREDIRECT(__ATTR_INOUT(1) __ATTR_OUT(2) __ATTR_OUT(3),int,__NOTHROW_RPC,readdir64_r,(DIR *__restrict __dirp, struct dirent64 *__restrict __entry, struct dirent64 **__restrict __result),readdir_r,(__dirp,__entry,__result))
#elif defined(__CRT_HAVE___libc_readdir_r) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)
/* >> readdir(3), readdir64(3)
 * Read and return the next pending directory entry of the given directory stream `dirp'
 * @except: Returns `NULL' for end-of-directory; throws an error if something else went wrong */
__CREDIRECT(__ATTR_INOUT(1) __ATTR_OUT(2) __ATTR_OUT(3),int,__NOTHROW_RPC,readdir64_r,(DIR *__restrict __dirp, struct dirent64 *__restrict __entry, struct dirent64 **__restrict __result),__libc_readdir_r,(__dirp,__entry,__result))
#elif defined(__CRT_HAVE_readdir64_r) && !defined(__CRT_KOS)
/* >> readdir(3), readdir64(3)
 * Read and return the next pending directory entry of the given directory stream `dirp'
 * @except: Returns `NULL' for end-of-directory; throws an error if something else went wrong */
__CDECLARE(__ATTR_INOUT(1) __ATTR_OUT(2) __ATTR_OUT(3),int,__NOTHROW_RPC,readdir64_r,(DIR *__restrict __dirp, struct dirent64 *__restrict __entry, struct dirent64 **__restrict __result),(__dirp,__entry,__result))
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_POSIX */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifdef __CRT_HAVE_seekdir
/* >> seekdir(3)
 * Get the directory stream position */
__CDECLARE_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,seekdir,(DIR *__restrict __dirp, __LONGPTR_TYPE__ __pos),(__dirp,__pos))
#elif defined(__CRT_HAVE___libc_seekdir)
/* >> seekdir(3)
 * Get the directory stream position */
__CREDIRECT_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,seekdir,(DIR *__restrict __dirp, __LONGPTR_TYPE__ __pos),__libc_seekdir,(__dirp,__pos))
#endif /* ... */
#ifdef __CRT_HAVE_telldir
/* >> telldir(3)
 * Get the directory stream position */
__CDECLARE(__ATTR_INOUT(1),__LONGPTR_TYPE__,__NOTHROW_NCX,telldir,(DIR *__restrict __dirp),(__dirp))
#elif defined(__CRT_HAVE___libc_telldir)
/* >> telldir(3)
 * Get the directory stream position */
__CREDIRECT(__ATTR_INOUT(1),__LONGPTR_TYPE__,__NOTHROW_NCX,telldir,(DIR *__restrict __dirp),__libc_telldir,(__dirp))
#endif /* ... */
#endif /* __USE_MISC || __USE_XOPEN */

#ifdef __USE_XOPEN2K8
/* >> dirfd(3)
 * Return the underlying file descriptor of the given directory stream */
__CDECLARE_OPT(__ATTR_PURE __ATTR_IN(1),__fd_t,__NOTHROW_NCX,dirfd,(DIR __KOS_FIXED_CONST *__restrict __dirp),(__dirp))
#if defined(__CRT_HAVE_scandirk) && defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> scandir(3), scandir64(3)
 * Scan a directory `dir' for all contained directory entries */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,scandir,(char const *__restrict __dir, struct dirent ***__restrict __namelist, int (__LIBKCALL *__selector)(struct dirent const *__entry), int (__LIBKCALL *__cmp)(struct dirent const **__a, struct dirent const **__b)),scandirk,(__dir,__namelist,__selector,__cmp))
#elif defined(__CRT_HAVE_scandirk64) && defined(__CRT_KOS) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> scandir(3), scandir64(3)
 * Scan a directory `dir' for all contained directory entries */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,scandir,(char const *__restrict __dir, struct dirent ***__restrict __namelist, int (__LIBKCALL *__selector)(struct dirent const *__entry), int (__LIBKCALL *__cmp)(struct dirent const **__a, struct dirent const **__b)),scandirk64,(__dir,__namelist,__selector,__cmp))
#elif defined(__CRT_HAVE_scandir) && !defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> scandir(3), scandir64(3)
 * Scan a directory `dir' for all contained directory entries */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,scandir,(char const *__restrict __dir, struct dirent ***__restrict __namelist, int (__LIBKCALL *__selector)(struct dirent const *__entry), int (__LIBKCALL *__cmp)(struct dirent const **__a, struct dirent const **__b)),(__dir,__namelist,__selector,__cmp))
#elif defined(__CRT_HAVE_scandir64) && !defined(__CRT_KOS) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> scandir(3), scandir64(3)
 * Scan a directory `dir' for all contained directory entries */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,scandir,(char const *__restrict __dir, struct dirent ***__restrict __namelist, int (__LIBKCALL *__selector)(struct dirent const *__entry), int (__LIBKCALL *__cmp)(struct dirent const **__a, struct dirent const **__b)),scandir64,(__dir,__namelist,__selector,__cmp))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && ((defined(__CRT_HAVE_scandiratk) && defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))) || (defined(__CRT_HAVE_scandiratk64) && defined(__CRT_KOS) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))) || (defined(__CRT_HAVE_scandirat) && !defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))) || (defined(__CRT_HAVE_scandirat64) && !defined(__CRT_KOS) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))))
#include <libc/local/dirent/scandir.h>
/* >> scandir(3), scandir64(3)
 * Scan a directory `dir' for all contained directory entries */
__NAMESPACE_LOCAL_USING_OR_IMPL(scandir, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) __STDC_INT_AS_SSIZE_T __NOTHROW_RPC(__LIBCCALL scandir)(char const *__restrict __dir, struct dirent ***__restrict __namelist, int (__LIBKCALL *__selector)(struct dirent const *__entry), int (__LIBKCALL *__cmp)(struct dirent const **__a, struct dirent const **__b)) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scandir))(__dir, __namelist, __selector, __cmp); })
#endif /* __AT_FDCWD && ((__CRT_HAVE_scandiratk && __CRT_KOS && (!__USE_FILE_OFFSET64 || _DIRENT_MATCHES_DIRENT64)) || (__CRT_HAVE_scandiratk64 && __CRT_KOS && (__USE_FILE_OFFSET64 || _DIRENT_MATCHES_DIRENT64)) || (__CRT_HAVE_scandirat && !__CRT_KOS && (!__USE_FILE_OFFSET64 || _DIRENT_MATCHES_DIRENT64)) || (__CRT_HAVE_scandirat64 && !__CRT_KOS && (__USE_FILE_OFFSET64 || _DIRENT_MATCHES_DIRENT64))) */
#endif /* !... */
#if defined(__CRT_HAVE_alphasortk) && defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> alphasort(3), alphasort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strcmp(3)' would */
__CREDIRECT(__ATTR_PURE __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,alphasort,(struct dirent const **__e1, struct dirent const **__e2),alphasortk,(__e1,__e2))
#elif defined(__CRT_HAVE_alphasortk64) && defined(__CRT_KOS) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> alphasort(3), alphasort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strcmp(3)' would */
__CREDIRECT(__ATTR_PURE __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,alphasort,(struct dirent const **__e1, struct dirent const **__e2),alphasortk64,(__e1,__e2))
#elif defined(__CRT_HAVE_alphasort) && !defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> alphasort(3), alphasort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strcmp(3)' would */
__CDECLARE(__ATTR_PURE __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,alphasort,(struct dirent const **__e1, struct dirent const **__e2),(__e1,__e2))
#elif defined(__CRT_HAVE_alphasort64) && !defined(__CRT_KOS) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> alphasort(3), alphasort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strcmp(3)' would */
__CREDIRECT(__ATTR_PURE __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,alphasort,(struct dirent const **__e1, struct dirent const **__e2),alphasort64,(__e1,__e2))
#else /* ... */
#include <libc/local/dirent/alphasort.h>
/* >> alphasort(3), alphasort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strcmp(3)' would */
__NAMESPACE_LOCAL_USING_OR_IMPL(alphasort, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL alphasort)(struct dirent const **__e1, struct dirent const **__e2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(alphasort))(__e1, __e2); })
#endif /* !... */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_alphasortk) && defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)
/* >> alphasort(3), alphasort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strcmp(3)' would */
__CREDIRECT(__ATTR_PURE __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,alphasort64,(struct dirent64 const **__e1, struct dirent64 const **__e2),alphasortk,(__e1,__e2))
#elif defined(__CRT_HAVE_alphasortk64) && defined(__CRT_KOS)
/* >> alphasort(3), alphasort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strcmp(3)' would */
__CREDIRECT(__ATTR_PURE __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,alphasort64,(struct dirent64 const **__e1, struct dirent64 const **__e2),alphasortk64,(__e1,__e2))
#elif defined(__CRT_HAVE_alphasort) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)
/* >> alphasort(3), alphasort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strcmp(3)' would */
__CREDIRECT(__ATTR_PURE __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,alphasort64,(struct dirent64 const **__e1, struct dirent64 const **__e2),alphasort,(__e1,__e2))
#elif defined(__CRT_HAVE_alphasort64) && !defined(__CRT_KOS)
/* >> alphasort(3), alphasort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strcmp(3)' would */
__CDECLARE(__ATTR_PURE __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,alphasort64,(struct dirent64 const **__e1, struct dirent64 const **__e2),(__e1,__e2))
#else /* ... */
#include <libc/local/dirent/alphasort64.h>
/* >> alphasort(3), alphasort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strcmp(3)' would */
__NAMESPACE_LOCAL_USING_OR_IMPL(alphasort64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL alphasort64)(struct dirent64 const **__e1, struct dirent64 const **__e2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(alphasort64))(__e1, __e2); })
#endif /* !... */
#endif /* __USE_LARGEFILE64 */

#ifdef __USE_GNU
#if defined(__CRT_HAVE_scandiratk) && defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> scandirat(3), scandirat64(3)
 * Scan a directory `dirfd:dir' for all contained directory entries */
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,scandirat,(__fd_t __dirfd, char const *__restrict __dir, struct dirent ***__restrict __namelist, int (__LIBKCALL *__selector)(struct dirent const *__entry), int (__LIBKCALL *__cmp)(struct dirent const **__a, struct dirent const **__b)),scandiratk,(__dirfd,__dir,__namelist,__selector,__cmp))
#elif defined(__CRT_HAVE_scandiratk64) && defined(__CRT_KOS) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> scandirat(3), scandirat64(3)
 * Scan a directory `dirfd:dir' for all contained directory entries */
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,scandirat,(__fd_t __dirfd, char const *__restrict __dir, struct dirent ***__restrict __namelist, int (__LIBKCALL *__selector)(struct dirent const *__entry), int (__LIBKCALL *__cmp)(struct dirent const **__a, struct dirent const **__b)),scandiratk64,(__dirfd,__dir,__namelist,__selector,__cmp))
#elif defined(__CRT_HAVE_scandirat) && !defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> scandirat(3), scandirat64(3)
 * Scan a directory `dirfd:dir' for all contained directory entries */
__CDECLARE(__ATTR_IN(2) __ATTR_OUT(3),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,scandirat,(__fd_t __dirfd, char const *__restrict __dir, struct dirent ***__restrict __namelist, int (__LIBKCALL *__selector)(struct dirent const *__entry), int (__LIBKCALL *__cmp)(struct dirent const **__a, struct dirent const **__b)),(__dirfd,__dir,__namelist,__selector,__cmp))
#elif defined(__CRT_HAVE_scandirat64) && !defined(__CRT_KOS) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> scandirat(3), scandirat64(3)
 * Scan a directory `dirfd:dir' for all contained directory entries */
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,scandirat,(__fd_t __dirfd, char const *__restrict __dir, struct dirent ***__restrict __namelist, int (__LIBKCALL *__selector)(struct dirent const *__entry), int (__LIBKCALL *__cmp)(struct dirent const **__a, struct dirent const **__b)),scandirat64,(__dirfd,__dir,__namelist,__selector,__cmp))
#endif /* ... */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_scandirk) && defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)
/* >> scandir(3), scandir64(3)
 * Scan a directory `dir' for all contained directory entries */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,scandir64,(char const *__restrict __dir, struct dirent64 ***__restrict __namelist, int (__LIBKCALL *__selector)(struct dirent64 const *__entry), int (__LIBKCALL *__cmp)(struct dirent64 const **__a, struct dirent64 const **__b)),scandirk,(__dir,__namelist,__selector,__cmp))
#elif defined(__CRT_HAVE_scandirk64) && defined(__CRT_KOS)
/* >> scandir(3), scandir64(3)
 * Scan a directory `dir' for all contained directory entries */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,scandir64,(char const *__restrict __dir, struct dirent64 ***__restrict __namelist, int (__LIBKCALL *__selector)(struct dirent64 const *__entry), int (__LIBKCALL *__cmp)(struct dirent64 const **__a, struct dirent64 const **__b)),scandirk64,(__dir,__namelist,__selector,__cmp))
#elif defined(__CRT_HAVE_scandir) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)
/* >> scandir(3), scandir64(3)
 * Scan a directory `dir' for all contained directory entries */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,scandir64,(char const *__restrict __dir, struct dirent64 ***__restrict __namelist, int (__LIBKCALL *__selector)(struct dirent64 const *__entry), int (__LIBKCALL *__cmp)(struct dirent64 const **__a, struct dirent64 const **__b)),scandir,(__dir,__namelist,__selector,__cmp))
#elif defined(__CRT_HAVE_scandir64) && !defined(__CRT_KOS)
/* >> scandir(3), scandir64(3)
 * Scan a directory `dir' for all contained directory entries */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,scandir64,(char const *__restrict __dir, struct dirent64 ***__restrict __namelist, int (__LIBKCALL *__selector)(struct dirent64 const *__entry), int (__LIBKCALL *__cmp)(struct dirent64 const **__a, struct dirent64 const **__b)),(__dir,__namelist,__selector,__cmp))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && ((defined(__CRT_HAVE_scandiratk) && defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE_scandiratk64) && defined(__CRT_KOS)) || (defined(__CRT_HAVE_scandirat) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE_scandirat64) && !defined(__CRT_KOS)))
#include <libc/local/dirent/scandir64.h>
/* >> scandir(3), scandir64(3)
 * Scan a directory `dir' for all contained directory entries */
__NAMESPACE_LOCAL_USING_OR_IMPL(scandir64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) __STDC_INT_AS_SSIZE_T __NOTHROW_RPC(__LIBCCALL scandir64)(char const *__restrict __dir, struct dirent64 ***__restrict __namelist, int (__LIBKCALL *__selector)(struct dirent64 const *__entry), int (__LIBKCALL *__cmp)(struct dirent64 const **__a, struct dirent64 const **__b)) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scandir64))(__dir, __namelist, __selector, __cmp); })
#endif /* __AT_FDCWD && ((__CRT_HAVE_scandiratk && __CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE_scandiratk64 && __CRT_KOS) || (__CRT_HAVE_scandirat && !__CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE_scandirat64 && !__CRT_KOS)) */
#endif /* !... */
#if defined(__CRT_HAVE_scandiratk) && defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)
/* >> scandirat(3), scandirat64(3)
 * Scan a directory `dirfd:dir' for all contained directory entries */
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,scandirat64,(__fd_t __dirfd, char const *__restrict __dir, struct dirent64 ***__restrict __namelist, int (__LIBKCALL *__selector)(struct dirent64 const *__entry), int (__LIBKCALL *__cmp)(struct dirent64 const **__a, struct dirent64 const **__b)),scandiratk,(__dirfd,__dir,__namelist,__selector,__cmp))
#elif defined(__CRT_HAVE_scandiratk64) && defined(__CRT_KOS)
/* >> scandirat(3), scandirat64(3)
 * Scan a directory `dirfd:dir' for all contained directory entries */
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,scandirat64,(__fd_t __dirfd, char const *__restrict __dir, struct dirent64 ***__restrict __namelist, int (__LIBKCALL *__selector)(struct dirent64 const *__entry), int (__LIBKCALL *__cmp)(struct dirent64 const **__a, struct dirent64 const **__b)),scandiratk64,(__dirfd,__dir,__namelist,__selector,__cmp))
#elif defined(__CRT_HAVE_scandirat) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)
/* >> scandirat(3), scandirat64(3)
 * Scan a directory `dirfd:dir' for all contained directory entries */
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,scandirat64,(__fd_t __dirfd, char const *__restrict __dir, struct dirent64 ***__restrict __namelist, int (__LIBKCALL *__selector)(struct dirent64 const *__entry), int (__LIBKCALL *__cmp)(struct dirent64 const **__a, struct dirent64 const **__b)),scandirat,(__dirfd,__dir,__namelist,__selector,__cmp))
#elif defined(__CRT_HAVE_scandirat64) && !defined(__CRT_KOS)
/* >> scandirat(3), scandirat64(3)
 * Scan a directory `dirfd:dir' for all contained directory entries */
__CDECLARE(__ATTR_IN(2) __ATTR_OUT(3),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,scandirat64,(__fd_t __dirfd, char const *__restrict __dir, struct dirent64 ***__restrict __namelist, int (__LIBKCALL *__selector)(struct dirent64 const *__entry), int (__LIBKCALL *__cmp)(struct dirent64 const **__a, struct dirent64 const **__b)),(__dirfd,__dir,__namelist,__selector,__cmp))
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_GNU */
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_MISC
#if defined(__CRT_HAVE_getdirentries) && (!defined(__USE_FILE_OFFSET64) || (defined(_DIRENT_MATCHES_DIRENT64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__))
/* >> getdirentries(2), getdirentries64(2)
 * Linux's underlying system call for reading the entries of a directory */
__CDECLARE(__ATTR_INOUT(4) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,getdirentries,(__fd_t __fd, char *__restrict __buf, size_t __nbytes, __FS_TYPE(off) *__restrict __basep),(__fd,__buf,__nbytes,__basep))
#elif defined(__CRT_HAVE___getdirentries) && (!defined(__USE_FILE_OFFSET64) || (defined(_DIRENT_MATCHES_DIRENT64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__))
/* >> getdirentries(2), getdirentries64(2)
 * Linux's underlying system call for reading the entries of a directory */
__CREDIRECT(__ATTR_INOUT(4) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,getdirentries,(__fd_t __fd, char *__restrict __buf, size_t __nbytes, __FS_TYPE(off) *__restrict __basep),__getdirentries,(__fd,__buf,__nbytes,__basep))
#elif defined(__CRT_HAVE___libc_getdirentries) && (!defined(__USE_FILE_OFFSET64) || (defined(_DIRENT_MATCHES_DIRENT64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__))
/* >> getdirentries(2), getdirentries64(2)
 * Linux's underlying system call for reading the entries of a directory */
__CREDIRECT(__ATTR_INOUT(4) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,getdirentries,(__fd_t __fd, char *__restrict __buf, size_t __nbytes, __FS_TYPE(off) *__restrict __basep),__libc_getdirentries,(__fd,__buf,__nbytes,__basep))
#elif defined(__CRT_HAVE_getdirentries64) && (defined(__USE_FILE_OFFSET64) || (defined(_DIRENT_MATCHES_DIRENT64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__))
/* >> getdirentries(2), getdirentries64(2)
 * Linux's underlying system call for reading the entries of a directory */
__CREDIRECT(__ATTR_INOUT(4) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,getdirentries,(__fd_t __fd, char *__restrict __buf, size_t __nbytes, __FS_TYPE(off) *__restrict __basep),getdirentries64,(__fd,__buf,__nbytes,__basep))
#endif /* ... */
#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_getdirentries) && defined(__DIRENT32_MATCHES_DIRENT64)
/* >> getdirentries(2), getdirentries64(2)
 * Linux's underlying system call for reading the entries of a directory */
__CREDIRECT(__ATTR_INOUT(4) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,getdirentries64,(__fd_t __fd, char *__restrict __buf, size_t __nbytes, __off64_t *__restrict __basep),getdirentries,(__fd,__buf,__nbytes,__basep))
#elif defined(__CRT_HAVE___getdirentries) && defined(_DIRENT_MATCHES_DIRENT64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> getdirentries(2), getdirentries64(2)
 * Linux's underlying system call for reading the entries of a directory */
__CREDIRECT(__ATTR_INOUT(4) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,getdirentries64,(__fd_t __fd, char *__restrict __buf, size_t __nbytes, __off64_t *__restrict __basep),__getdirentries,(__fd,__buf,__nbytes,__basep))
#elif defined(__CRT_HAVE___libc_getdirentries) && defined(_DIRENT_MATCHES_DIRENT64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> getdirentries(2), getdirentries64(2)
 * Linux's underlying system call for reading the entries of a directory */
__CREDIRECT(__ATTR_INOUT(4) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,getdirentries64,(__fd_t __fd, char *__restrict __buf, size_t __nbytes, __off64_t *__restrict __basep),__libc_getdirentries,(__fd,__buf,__nbytes,__basep))
#elif defined(__CRT_HAVE_getdirentries64)
/* >> getdirentries(2), getdirentries64(2)
 * Linux's underlying system call for reading the entries of a directory */
__CDECLARE(__ATTR_INOUT(4) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,getdirentries64,(__fd_t __fd, char *__restrict __buf, size_t __nbytes, __off64_t *__restrict __basep),(__fd,__buf,__nbytes,__basep))
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_MISC */

#ifdef __USE_GNU
#if defined(__CRT_HAVE_versionsortk) && defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> versionsort(3), versionsort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strvercmp(3)' would. */
__CREDIRECT(__ATTR_PURE __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,versionsort,(struct dirent const **__e1, struct dirent const **__e2),versionsortk,(__e1,__e2))
#elif defined(__CRT_HAVE_versionsortk64) && defined(__CRT_KOS) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> versionsort(3), versionsort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strvercmp(3)' would. */
__CREDIRECT(__ATTR_PURE __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,versionsort,(struct dirent const **__e1, struct dirent const **__e2),versionsortk64,(__e1,__e2))
#elif defined(__CRT_HAVE_versionsort) && !defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> versionsort(3), versionsort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strvercmp(3)' would. */
__CDECLARE(__ATTR_PURE __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,versionsort,(struct dirent const **__e1, struct dirent const **__e2),(__e1,__e2))
#elif defined(__CRT_HAVE_versionsort64) && !defined(__CRT_KOS) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> versionsort(3), versionsort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strvercmp(3)' would. */
__CREDIRECT(__ATTR_PURE __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,versionsort,(struct dirent const **__e1, struct dirent const **__e2),versionsort64,(__e1,__e2))
#else /* ... */
#include <libc/local/dirent/versionsort.h>
/* >> versionsort(3), versionsort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strvercmp(3)' would. */
__NAMESPACE_LOCAL_USING_OR_IMPL(versionsort, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL versionsort)(struct dirent const **__e1, struct dirent const **__e2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(versionsort))(__e1, __e2); })
#endif /* !... */
#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_versionsortk) && defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)
/* >> versionsort(3), versionsort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strvercmp(3)' would. */
__CREDIRECT(__ATTR_PURE __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,versionsort64,(struct dirent64 const **__e1, struct dirent64 const **__e2),versionsortk,(__e1,__e2))
#elif defined(__CRT_HAVE_versionsortk64) && defined(__CRT_KOS)
/* >> versionsort(3), versionsort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strvercmp(3)' would. */
__CREDIRECT(__ATTR_PURE __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,versionsort64,(struct dirent64 const **__e1, struct dirent64 const **__e2),versionsortk64,(__e1,__e2))
#elif defined(__CRT_HAVE_versionsort) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)
/* >> versionsort(3), versionsort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strvercmp(3)' would. */
__CREDIRECT(__ATTR_PURE __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,versionsort64,(struct dirent64 const **__e1, struct dirent64 const **__e2),versionsort,(__e1,__e2))
#elif defined(__CRT_HAVE_versionsort64) && !defined(__CRT_KOS)
/* >> versionsort(3), versionsort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strvercmp(3)' would. */
__CDECLARE(__ATTR_PURE __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,versionsort64,(struct dirent64 const **__e1, struct dirent64 const **__e2),(__e1,__e2))
#else /* ... */
#include <libc/local/dirent/versionsort64.h>
/* >> versionsort(3), versionsort64(3)
 * Sort the 2 given directory entries `e1' and `e2' the same way `strvercmp(3)' would. */
__NAMESPACE_LOCAL_USING_OR_IMPL(versionsort64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL versionsort64)(struct dirent64 const **__e1, struct dirent64 const **__e2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(versionsort64))(__e1, __e2); })
#endif /* !... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_GNU */

#if defined(__USE_KOS) && defined(__KOS__) && defined(__CRT_KOS)
#ifdef __CRT_HAVE_kreaddir
/* >> kreaddir(2), kreaddirf(2), kreaddir64(2), kreaddirf64(2)
 * The KOS-specific system call for reading a single directory entry
 * from  a file  descriptor referring  to an  open directory stream.
 * @param: mode: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When  `READDIR_DEFAULT' was passed for `mode', the directory
 *                    stream will only be advanced when this value is >= 'bufsize'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
__CDECLARE(__ATTR_WUNUSED,__SSIZE_TYPE__,__NOTHROW_RPC,kreaddir,(__fd_t __fd, struct dirent *__buf, size_t __bufsize, unsigned int __mode),(__fd,__buf,__bufsize,__mode))
#elif defined(__CRT_HAVE_kreaddir64) && defined(_DIRENT_MATCHES_DIRENT64)
/* >> kreaddir(2), kreaddirf(2), kreaddir64(2), kreaddirf64(2)
 * The KOS-specific system call for reading a single directory entry
 * from  a file  descriptor referring  to an  open directory stream.
 * @param: mode: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When  `READDIR_DEFAULT' was passed for `mode', the directory
 *                    stream will only be advanced when this value is >= 'bufsize'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
__CREDIRECT(__ATTR_WUNUSED,__SSIZE_TYPE__,__NOTHROW_RPC,kreaddir,(__fd_t __fd, struct dirent *__buf, size_t __bufsize, unsigned int __mode),kreaddir64,(__fd,__buf,__bufsize,__mode))
#elif (defined(__CRT_HAVE_kreaddirf) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))) || (defined(__CRT_HAVE_kreaddirf64) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64)))
#include <libc/local/dirent/kreaddir.h>
/* >> kreaddir(2), kreaddirf(2), kreaddir64(2), kreaddirf64(2)
 * The KOS-specific system call for reading a single directory entry
 * from  a file  descriptor referring  to an  open directory stream.
 * @param: mode: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When  `READDIR_DEFAULT' was passed for `mode', the directory
 *                    stream will only be advanced when this value is >= 'bufsize'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(kreaddir, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __SSIZE_TYPE__ __NOTHROW_RPC(__LIBCCALL kreaddir)(__fd_t __fd, struct dirent *__buf, size_t __bufsize, unsigned int __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(kreaddir))(__fd, __buf, __bufsize, __mode); })
#endif /* ... */
#if defined(__CRT_HAVE_kreaddirf) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> kreaddir(2), kreaddirf(2), kreaddir64(2), kreaddirf64(2)
 * The KOS-specific system call for reading a single directory entry
 * from  a file  descriptor referring  to an  open directory stream.
 * @param: mode: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When  `READDIR_DEFAULT' was passed for `mode', the directory
 *                    stream will only be advanced when this value is >= 'bufsize'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
__CDECLARE(__ATTR_WUNUSED,__SSIZE_TYPE__,__NOTHROW_RPC,kreaddirf,(__fd_t __fd, struct dirent *__buf, size_t __bufsize, unsigned int __mode, __oflag_t __flags),(__fd,__buf,__bufsize,__mode,__flags))
#elif defined(__CRT_HAVE_kreaddirf64) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* >> kreaddir(2), kreaddirf(2), kreaddir64(2), kreaddirf64(2)
 * The KOS-specific system call for reading a single directory entry
 * from  a file  descriptor referring  to an  open directory stream.
 * @param: mode: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When  `READDIR_DEFAULT' was passed for `mode', the directory
 *                    stream will only be advanced when this value is >= 'bufsize'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
__CREDIRECT(__ATTR_WUNUSED,__SSIZE_TYPE__,__NOTHROW_RPC,kreaddirf,(__fd_t __fd, struct dirent *__buf, size_t __bufsize, unsigned int __mode, __oflag_t __flags),kreaddirf64,(__fd,__buf,__bufsize,__mode,__flags))
#endif /* ... */
#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_kreaddir) && defined(__DIRENT32_MATCHES_DIRENT64)
/* >> kreaddir(2), kreaddirf(2), kreaddir64(2), kreaddirf64(2)
 * The KOS-specific system call for reading a single directory entry
 * from  a file  descriptor referring  to an  open directory stream.
 * @param: mode: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When  `READDIR_DEFAULT' was passed for `mode', the directory
 *                    stream will only be advanced when this value is >= 'bufsize'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
__CREDIRECT(__ATTR_WUNUSED,__SSIZE_TYPE__,__NOTHROW_RPC,kreaddir64,(__fd_t __fd, struct dirent64 *__buf, size_t __bufsize, unsigned int __mode),kreaddir,(__fd,__buf,__bufsize,__mode))
#elif defined(__CRT_HAVE_kreaddir64)
/* >> kreaddir(2), kreaddirf(2), kreaddir64(2), kreaddirf64(2)
 * The KOS-specific system call for reading a single directory entry
 * from  a file  descriptor referring  to an  open directory stream.
 * @param: mode: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When  `READDIR_DEFAULT' was passed for `mode', the directory
 *                    stream will only be advanced when this value is >= 'bufsize'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
__CDECLARE(__ATTR_WUNUSED,__SSIZE_TYPE__,__NOTHROW_RPC,kreaddir64,(__fd_t __fd, struct dirent64 *__buf, size_t __bufsize, unsigned int __mode),(__fd,__buf,__bufsize,__mode))
#elif defined(__CRT_HAVE_kreaddir) && defined(_DIRENT_MATCHES_DIRENT64)
/* >> kreaddir(2), kreaddirf(2), kreaddir64(2), kreaddirf64(2)
 * The KOS-specific system call for reading a single directory entry
 * from  a file  descriptor referring  to an  open directory stream.
 * @param: mode: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When  `READDIR_DEFAULT' was passed for `mode', the directory
 *                    stream will only be advanced when this value is >= 'bufsize'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
__CREDIRECT(__ATTR_WUNUSED,__SSIZE_TYPE__,__NOTHROW_RPC,kreaddir64,(__fd_t __fd, struct dirent64 *__buf, size_t __bufsize, unsigned int __mode),kreaddir,(__fd,__buf,__bufsize,__mode))
#elif (defined(__CRT_HAVE_kreaddirf) && defined(__DIRENT32_MATCHES_DIRENT64)) || defined(__CRT_HAVE_kreaddirf64)
#include <libc/local/dirent/kreaddir64.h>
/* >> kreaddir(2), kreaddirf(2), kreaddir64(2), kreaddirf64(2)
 * The KOS-specific system call for reading a single directory entry
 * from  a file  descriptor referring  to an  open directory stream.
 * @param: mode: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When  `READDIR_DEFAULT' was passed for `mode', the directory
 *                    stream will only be advanced when this value is >= 'bufsize'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(kreaddir64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __SSIZE_TYPE__ __NOTHROW_RPC(__LIBCCALL kreaddir64)(__fd_t __fd, struct dirent64 *__buf, size_t __bufsize, unsigned int __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(kreaddir64))(__fd, __buf, __bufsize, __mode); })
#endif /* ... */
#if defined(__CRT_HAVE_kreaddirf) && defined(__DIRENT32_MATCHES_DIRENT64)
/* >> kreaddir(2), kreaddirf(2), kreaddir64(2), kreaddirf64(2)
 * The KOS-specific system call for reading a single directory entry
 * from  a file  descriptor referring  to an  open directory stream.
 * @param: mode: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When  `READDIR_DEFAULT' was passed for `mode', the directory
 *                    stream will only be advanced when this value is >= 'bufsize'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
__CREDIRECT(__ATTR_WUNUSED,__SSIZE_TYPE__,__NOTHROW_RPC,kreaddirf64,(__fd_t __fd, struct dirent64 *__buf, size_t __bufsize, unsigned int __mode, __oflag_t __flags),kreaddirf,(__fd,__buf,__bufsize,__mode,__flags))
#elif defined(__CRT_HAVE_kreaddirf64)
/* >> kreaddir(2), kreaddirf(2), kreaddir64(2), kreaddirf64(2)
 * The KOS-specific system call for reading a single directory entry
 * from  a file  descriptor referring  to an  open directory stream.
 * @param: mode: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When  `READDIR_DEFAULT' was passed for `mode', the directory
 *                    stream will only be advanced when this value is >= 'bufsize'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
__CDECLARE(__ATTR_WUNUSED,__SSIZE_TYPE__,__NOTHROW_RPC,kreaddirf64,(__fd_t __fd, struct dirent64 *__buf, size_t __bufsize, unsigned int __mode, __oflag_t __flags),(__fd,__buf,__bufsize,__mode,__flags))
#endif /* ... */
#endif /* __USE_LARGEFILE64 */

#ifndef READDIR_DEFAULT
#define READDIR_DEFAULT  0x0000 /* Yield to next entry when `buf' was of sufficient size. */
#define READDIR_CONTINUE 0x0001 /* Always yield to next entry. */
#define READDIR_PEEK     0x0002 /* Never yield to next entry. */
#if __KOS_VERSION__ >= 300
#define READDIR_SKIPREL  0x4000 /* Skip reading the `.' and `..' directory entries. */
#define READDIR_WANTEOF  0x8000 /* Minor optimization for `READDIR_MULTIPLE':
                                 * The system is allowed to append an empty directory entry
                                 * (with  `d_namlen = 0' and `d_name[0] = '\0''; other fields are undefined).
                                 * If there isn't enough space for such an entry, no such entry will be emit.
                                 * Since no other  directory entry can  ever have a  length of ZERO(0),  this
                                 * allows  user-space  to detect  end-of-directory  without the  need  of re-
                                 * invoking  the kreaddir() system  call and inspecting  its return value for
                                 * being equal to ZERO(0).
                                 * However, that check is still required, as this flag may be ignored for no
                                 * reason immediately apparent (if the EOF entry can't fit into the  buffer,
                                 * there's  no way of knowing if there's  a missing entry that's supposed to
                                 * go into the buffer, or if it was actually an EOF entry). Additionally, no
                                 * EOF  entry may be written if kreaddir()  is invoked on a directory handle
                                 * who's stream position is at the end of the directory.
                                 * For usage, see the example below, as well as `READDIR_MULTIPLE_ISEOF()' */
#define READDIR_MODEMASK 0x001f /* Mask for the kreaddir() mode. */
#define READDIR_FLAGMASK 0xc000 /* Mask of known kreaddir() flags. */
#define READDIR_MODEMAX  0x0003 /* Mask recognized mode ID. */
#define READDIR_MULTIPLE 0x0003 /* Read as many directory entries as can fit into the buffer. If at
                                 * least one entry could be read,  return the combined size of  all
                                 * read entries (in bytes) (in this case, `return <= bufsize').  If
                                 * the buffer was too small to  contain the next entry, return  the
                                 * required size to house that  pending entry, but don't yield  it,
                                 * the  same way `READDIR_DEFAULT'  wouldn't. To enumerate multiple
                                 * directories in some buffer, use the macros below. */
#ifdef __CC__
/* READDIR_MULTIPLE buffer helpers:
 * >> for (;;) {
 * >>     char buffer[2048]; size_t bufsize;
 * >>     struct dirent *iter = (struct dirent *)buffer;
 * >>     // Read as many entries as our buffer can fit
 * >>     bufsize = kreaddir(fd, iter, sizeof(buffer),
 * >>                        READDIR_MULTIPLE|
 * >>                        READDIR_WANTEOF);
 * >>     if (!bufsize)
 * >>         break; // End of directory
 * >>     if (bufsize > sizeof(buffer)) {
 * >>         printf("The next directory entry larger than the buffer\n");
 * >>         break;
 * >>     }
 * >>     // Process successfully read entries
 * >>     do {
 * >>         // This check is only required when `READDIR_WANTEOF' is passed.
 * >>         if (READDIR_MULTIPLE_ISEOF(iter))
 * >>             goto done;
 * >>         printf("Entry: %q\n", iter->d_name);
 * >>         iter = READDIR_MULTIPLE_GETNEXT(iter);
 * >>     } while (READDIR_MULTIPLE_ISVALID(iter, buffer, bufsize));
 * >> }
 * >>done:
 */
#define READDIR_MULTIPLE_GETNEXT(p)                                      \
	((struct dirent *)(((uintptr_t)((p)->d_name + ((p)->d_namlen + 1)) + \
	                    (sizeof(__ino64_t) - 1)) &                       \
	                   ~(sizeof(__ino64_t) - 1)))
#define READDIR_MULTIPLE_ISVALID(p, buf, bufsize)                               \
	(((__BYTE_TYPE__ *)((p)->d_name)) < ((__BYTE_TYPE__ *)(buf) + (bufsize)) && \
	 ((__BYTE_TYPE__ *)((p)->d_name + (p)->d_namlen)) < ((__BYTE_TYPE__ *)(buf) + (bufsize)))
#define READDIR_MULTIPLE_ISEOF(p) ((p)->d_namlen == 0)
#ifdef __USE_LARGEFILE64
#define READDIR_MULTIPLE_GETNEXT64(p) ((struct dirent64 *)READDIR_MULTIPLE_GETNEXT(p))
#endif /* __USE_LARGEFILE64 */
#endif /* __CC__ */
#endif /* __KOS_VERSION__ >= 300 */
#endif /* !READDIR_DEFAULT */
#endif /* __USE_KOS && __KOS__ && __CRT_KOS */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_DIRENT_H */
