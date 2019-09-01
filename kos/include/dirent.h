/* HASH 0x7a7b7b8e */
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
#ifndef _DIRENT_H
#define _DIRENT_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>

#ifdef __CC__

__SYSDECL_BEGIN

#ifdef __USE_XOPEN
#ifndef __ino_t_defined
#define __ino_t_defined 1
typedef __typedef_ino_t ino_t;
#endif /* !__ino_t_defined */
#ifdef __USE_LARGEFILE64
#ifndef __ino64_t_defined
#define __ino64_t_defined 1
typedef __ino64_t ino64_t;
#endif /* !__ino64_t_defined */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN */

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */
#endif /* __CC__ */

__SYSDECL_END

#ifdef __CRT_DOS_PRIMARY

/* TODO: Emulate using the _find* functions. */

#else /* __CRT_DOS_PRIMARY */
#include <bits/dirent.h>

#ifdef _DIRENT_HAVE_D_NAMLEN
#   define _D_EXACT_NAMLEN(d) ((d)->d_namlen)
#   define _D_ALLOC_NAMLEN(d) (_D_EXACT_NAMLEN(d)+1)
#else /* _DIRENT_HAVE_D_NAMLEN */
#   include <libc/string.h>
#   define _D_EXACT_NAMLEN(d) __libc_strlen((d)->d_name)
#ifdef _DIRENT_HAVE_D_RECLEN
#   define _D_ALLOC_NAMLEN(d) (((char *)(d)+(d)->d_reclen)-&(d)->d_name[0])
#else /* _DIRENT_HAVE_D_RECLEN */
#   define _D_ALLOC_NAMLEN(d) (sizeof((d)->d_name) > 1 ? sizeof((d)->d_name) : _D_EXACT_NAMLEN(d)+1)
#endif /* !_DIRENT_HAVE_D_RECLEN */
#endif /* !_DIRENT_HAVE_D_NAMLEN */

__SYSDECL_BEGIN

#ifdef __USE_MISC
#undef DT_UNKNOWN
#undef DT_FIFO
#undef DT_CHR
#undef DT_DIR
#undef DT_BLK
#undef DT_REG
#undef DT_LNK
#undef DT_SOCK
#undef DT_WHT
#ifdef __CC__
enum {
	DT_UNKNOWN = 0,
	DT_FIFO    = 1,
	DT_CHR     = 2,
	DT_DIR     = 4,
	DT_BLK     = 6,
	DT_REG     = 8,
	DT_LNK     = 10,
	DT_SOCK    = 12,
	DT_WHT     = 14
};
#endif /* __CC__ */
#ifdef __COMPILER_PREFERR_ENUMS
#define DT_UNKNOWN DT_UNKNOWN
#define DT_FIFO    DT_FIFO
#define DT_CHR     DT_CHR
#define DT_DIR     DT_DIR
#define DT_BLK     DT_BLK
#define DT_REG     DT_REG
#define DT_LNK     DT_LNK
#define DT_SOCK    DT_SOCK
#define DT_WHT     DT_WHT
#else /* __COMPILER_PREFERR_ENUMS */
#define DT_UNKNOWN 0
#define DT_FIFO    1
#define DT_CHR     2
#define DT_DIR     4
#define DT_BLK     6
#define DT_REG     8
#define DT_LNK     10
#define DT_SOCK    12
#define DT_WHT     14
#endif /* !__COMPILER_PREFERR_ENUMS */

/* Convert between stat structure types and directory types. */
#ifndef IFTODT
#define IFTODT(mode)    (((mode) & 0170000) >> 12)
#define DTTOIF(dirtype) ((dirtype) << 12)
#endif /* !IFTODT */

#if defined(__USE_XOPEN2K8) && !defined(MAXNAMLEN)
#define MAXNAMLEN    255 /* == 'NAME_MAX' from <linux/limits.h> */
#endif /* __USE_XOPEN2K8 && !MAXNAMLEN */
#endif /* __USE_MISC */


#ifdef __CC__
#ifndef __DIR_defined
#define __DIR_defined 1
typedef struct __dirstream DIR;
#endif /* !__DIR_defined */

#if defined(__CRT_HAVE_opendir)
/* Open and return a new directory stream for reading, referring to `name' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),DIR *,__NOTHROW_RPC,opendir,(char const *__name),(__name))
#elif defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_fopendirat) || defined(__CRT_HAVE_opendirat))
#include <local/dirent/opendir.h>
/* Open and return a new directory stream for reading, referring to `name' */
__NAMESPACE_LOCAL_USING_OR_IMPL(opendir, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) DIR *__NOTHROW_RPC(__LIBCCALL opendir)(char const *__name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(opendir))(__name); })
#endif /* opendir... */

#if defined(__USE_KOS) && defined(__USE_ATFILE)
#if defined(__CRT_HAVE_fopendirat)
/* Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),DIR *,__NOTHROW_RPC,fopendirat,(__fd_t __dirfd, char const *__name, __oflag_t __oflags),(__dirfd,__name,__oflags))
#endif /* fopendirat... */
#if defined(__CRT_HAVE_opendirat)
/* Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),DIR *,__NOTHROW_RPC,opendirat,(__fd_t __dirfd, char const *__name),(__dirfd,__name))
#elif defined(__CRT_HAVE_fopendirat)
#include <local/dirent/opendirat.h>
/* Directory-handle-relative, and flags-enabled versions of `opendir(3)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(opendirat, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((2)) DIR *__NOTHROW_RPC(__LIBCCALL opendirat)(__fd_t __dirfd, char const *__name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(opendirat))(__dirfd, __name); })
#endif /* opendirat... */
#endif /* __USE_KOS && __USE_ATFILE */

#if defined(__CRT_HAVE_closedir)
/* Close a directory stream previously returned by `opendir(3)' and friends */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,closedir,(DIR *__dirp),(__dirp))
#endif /* closedir... */

#if defined(__CRT_HAVE_readdir) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* Read and return the next pending directory entry of the given directory stream `DIRP'
 * @EXCEPT: Returns NULL for end-of-directory; throws an error if something else went wrong */
__CDECLARE(__ATTR_NONNULL((1)),struct dirent *,__NOTHROW_RPC,readdir,(DIR *__restrict __dirp),(__dirp))
#elif defined(__CRT_HAVE_readdir64) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* Read and return the next pending directory entry of the given directory stream `DIRP'
 * @EXCEPT: Returns NULL for end-of-directory; throws an error if something else went wrong */
__CREDIRECT(__ATTR_NONNULL((1)),struct dirent *,__NOTHROW_RPC,readdir,(DIR *__restrict __dirp),readdir64,(__dirp))
#endif /* readdir... */

#if defined(__CRT_HAVE_rewinddir)
/* Rewind the given directory stream in such a way that the next call
 * to `readdir(3)' will once again return the first directory entry */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,rewinddir,(DIR *__restrict __dirp),(__dirp))
#endif /* rewinddir... */

#ifdef __USE_XOPEN2K8
#if defined(__CRT_HAVE_fdopendir)
/* Create a new directory stream by inheriting the given `FD' as stream handle */
__CDECLARE(__ATTR_WUNUSED,DIR *,__NOTHROW_NCX,fdopendir,(__fd_t __fd),(__fd))
#endif /* fdopendir... */
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_readdir64)
/* 64-bit equivalent of `readdir(3)'
 * @EXCEPT: Returns NULL for end-of-directory; throws an error if something else went wrong */
__CDECLARE(__ATTR_NONNULL((1)),struct dirent64 *,__NOTHROW_RPC,readdir64,(DIR *__restrict __dirp),(__dirp))
#elif defined(__CRT_HAVE_readdir) && (defined(_DIRENT_MATCHES_DIRENT64))
/* 64-bit equivalent of `readdir(3)'
 * @EXCEPT: Returns NULL for end-of-directory; throws an error if something else went wrong */
__CREDIRECT(__ATTR_NONNULL((1)),struct dirent64 *,__NOTHROW_RPC,readdir64,(DIR *__restrict __dirp),readdir,(__dirp))
#endif /* readdir64... */
#endif /* __USE_LARGEFILE64 */
#ifdef __USE_POSIX
#if defined(__CRT_HAVE_readdir_r) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* Reentrant version of `readdir(3)' (Using this is not recommended in KOS) */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,readdir_r,(DIR *__restrict __dirp, struct dirent *__restrict __entry, struct dirent **__restrict __result),(__dirp,__entry,__result))
#elif defined(__CRT_HAVE_readdir64_r) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* Reentrant version of `readdir(3)' (Using this is not recommended in KOS) */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,readdir_r,(DIR *__restrict __dirp, struct dirent *__restrict __entry, struct dirent **__restrict __result),readdir64_r,(__dirp,__entry,__result))
#endif /* readdir_r... */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_readdir64_r)
/* NOTE: This ~reentrant~ version of readdir() is strongly discouraged from being used in KOS, as the
 *       kernel does not impose a limit on the length of a single directory entry name (s.a. 'kreaddir')
 * >> Instead, simply use `readdir()' / `readdir64()', which will automatically (re-)allocate an internal,
 *    per-directory buffer of sufficient size to house any directory entry (s.a.: `READDIR_DEFAULT') */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,readdir64_r,(DIR *__restrict __dirp, struct dirent64 *__restrict __entry, struct dirent64 **__restrict __result),(__dirp,__entry,__result))
#elif defined(__CRT_HAVE_readdir_r) && (defined(_DIRENT_MATCHES_DIRENT64))
/* NOTE: This ~reentrant~ version of readdir() is strongly discouraged from being used in KOS, as the
 *       kernel does not impose a limit on the length of a single directory entry name (s.a. 'kreaddir')
 * >> Instead, simply use `readdir()' / `readdir64()', which will automatically (re-)allocate an internal,
 *    per-directory buffer of sufficient size to house any directory entry (s.a.: `READDIR_DEFAULT') */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,readdir64_r,(DIR *__restrict __dirp, struct dirent64 *__restrict __entry, struct dirent64 **__restrict __result),readdir_r,(__dirp,__entry,__result))
#endif /* readdir64_r... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_POSIX */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#if defined(__CRT_HAVE_seekdir)
/* Get the directory stream position */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,seekdir,(DIR *__restrict __dirp, long int __pos),(__dirp,__pos))
#endif /* seekdir... */
#if defined(__CRT_HAVE_telldir)
/* Get the directory stream position */
__CDECLARE(__ATTR_NONNULL((1)),long int,__NOTHROW_NCX,telldir,(DIR *__restrict __dirp),(__dirp))
#endif /* telldir... */
#endif /* __USE_MISC || __USE_XOPEN */

#ifdef __USE_XOPEN2K8
#if defined(__CRT_HAVE_dirfd)
/* Return the underlying file descriptor of the given directory stream */
__CDECLARE(__ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,dirfd,(DIR *__restrict __dirp),(__dirp))
#endif /* dirfd... */
typedef int (*__scandir_selector_t)(struct dirent const *);
typedef int (*__scandir_cmp_t)(struct dirent const **, struct dirent const **);

#if defined(__CRT_HAVE_scandir) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* Scan a directory `DIR' for all contained directory entries */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,scandir,(char const *__restrict __dir, struct dirent ***__restrict __namelist, __scandir_selector_t __selector, __scandir_cmp_t __cmp),(__dir,__namelist,__selector,__cmp))
#elif defined(__CRT_HAVE_scandir64) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* Scan a directory `DIR' for all contained directory entries */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,scandir,(char const *__restrict __dir, struct dirent ***__restrict __namelist, __scandir_selector_t __selector, __scandir_cmp_t __cmp),scandir64,(__dir,__namelist,__selector,__cmp))
#elif defined(__CRT_AT_FDCWD) && ((defined(__CRT_HAVE_scandirat) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))) || (defined(__CRT_HAVE_scandirat64) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))))
#include <local/dirent/scandir.h>
/* Scan a directory `DIR' for all contained directory entries */
__NAMESPACE_LOCAL_USING_OR_IMPL(scandir, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL scandir)(char const *__restrict __dir, struct dirent ***__restrict __namelist, __scandir_selector_t __selector, __scandir_cmp_t __cmp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scandir))(__dir, __namelist, __selector, __cmp); })
#endif /* scandir... */

#if defined(__CRT_HAVE_alphasort)
/* Sort the 2 given directory entries `E1' and `E2' the same way `strcmp(3)' would */
__CDECLARE(__ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,alphasort,(struct dirent const **__e1, struct dirent const **__e2),(__e1,__e2))
#elif defined(__CRT_HAVE_alphasort64) && (defined(_DIRENT_MATCHES_DIRENT64))
/* Sort the 2 given directory entries `E1' and `E2' the same way `strcmp(3)' would */
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,alphasort,(struct dirent const **__e1, struct dirent const **__e2),alphasort64,(__e1,__e2))
#else /* LIBC: alphasort */
#include <local/dirent/alphasort.h>
/* Sort the 2 given directory entries `E1' and `E2' the same way `strcmp(3)' would */
__NAMESPACE_LOCAL_USING_OR_IMPL(alphasort, __FORCELOCAL __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL alphasort)(struct dirent const **__e1, struct dirent const **__e2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(alphasort))(__e1, __e2); })
#endif /* alphasort... */
#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_alphasort64)
/* 64-bit variant of `alphasort()' */
__CDECLARE(__ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,alphasort64,(struct dirent64 const **__e1, struct dirent64 const **__e2),(__e1,__e2))
#elif defined(__CRT_HAVE_alphasort) && (defined(_DIRENT_MATCHES_DIRENT64))
/* 64-bit variant of `alphasort()' */
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,alphasort64,(struct dirent64 const **__e1, struct dirent64 const **__e2),alphasort,(__e1,__e2))
#else /* LIBC: alphasort64 */
#include <local/dirent/alphasort64.h>
/* 64-bit variant of `alphasort()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(alphasort64, __FORCELOCAL __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL alphasort64)(struct dirent64 const **__e1, struct dirent64 const **__e2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(alphasort64))(__e1, __e2); })
#endif /* alphasort64... */
#endif /* __USE_LARGEFILE64 */

#ifdef __USE_GNU
#if defined(__CRT_HAVE_scandirat) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* Scan a directory `DIRFD:DIR' for all contained directory entries */
__CDECLARE(__ATTR_NONNULL((2, 3)),int,__NOTHROW_RPC,scandirat,(__fd_t __dirfd, char const *__restrict __dir, struct dirent ***__restrict __namelist, __scandir_selector_t __selector, __scandir_cmp_t __cmp),(__dirfd,__dir,__namelist,__selector,__cmp))
#elif defined(__CRT_HAVE_scandirat64) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* Scan a directory `DIRFD:DIR' for all contained directory entries */
__CREDIRECT(__ATTR_NONNULL((2, 3)),int,__NOTHROW_RPC,scandirat,(__fd_t __dirfd, char const *__restrict __dir, struct dirent ***__restrict __namelist, __scandir_selector_t __selector, __scandir_cmp_t __cmp),scandirat64,(__dirfd,__dir,__namelist,__selector,__cmp))
#endif /* scandirat... */

#ifdef __USE_LARGEFILE64
typedef int (*__scandir64_selector_t)(struct dirent64 const *);
typedef int (*__scandir64_cmp_t)(struct dirent64 const **, struct dirent64 const **);
#if defined(__CRT_HAVE_scandir64)
/* 64-bit variant of `scandir()' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,scandir64,(char const *__restrict __dir, struct dirent64 ***__restrict __namelist, __scandir64_selector_t __selector, __scandir64_cmp_t __cmp),(__dir,__namelist,__selector,__cmp))
#elif defined(__CRT_HAVE_scandir) && (defined(_DIRENT_MATCHES_DIRENT64))
/* 64-bit variant of `scandir()' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,scandir64,(char const *__restrict __dir, struct dirent64 ***__restrict __namelist, __scandir64_selector_t __selector, __scandir64_cmp_t __cmp),scandir,(__dir,__namelist,__selector,__cmp))
#elif defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_scandirat64) || (defined(__CRT_HAVE_scandirat) && defined(_DIRENT_MATCHES_DIRENT64)))
#include <local/dirent/scandir64.h>
/* 64-bit variant of `scandir()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(scandir64, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL scandir64)(char const *__restrict __dir, struct dirent64 ***__restrict __namelist, __scandir64_selector_t __selector, __scandir64_cmp_t __cmp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scandir64))(__dir, __namelist, __selector, __cmp); })
#endif /* scandir64... */
#if defined(__CRT_HAVE_scandirat64)
/* 64-bit variant of `scandirat()' */
__CDECLARE(__ATTR_NONNULL((2, 3)),int,__NOTHROW_RPC,scandirat64,(__fd_t __dirfd, char const *__restrict __dir, struct dirent64 ***__restrict __namelist, __scandir64_selector_t __selector, __scandir64_cmp_t __cmp),(__dirfd,__dir,__namelist,__selector,__cmp))
#elif defined(__CRT_HAVE_scandirat) && (defined(_DIRENT_MATCHES_DIRENT64))
/* 64-bit variant of `scandirat()' */
__CREDIRECT(__ATTR_NONNULL((2, 3)),int,__NOTHROW_RPC,scandirat64,(__fd_t __dirfd, char const *__restrict __dir, struct dirent64 ***__restrict __namelist, __scandir64_selector_t __selector, __scandir64_cmp_t __cmp),scandirat,(__dirfd,__dir,__namelist,__selector,__cmp))
#endif /* scandirat64... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_GNU */
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_MISC
#if defined(__CRT_HAVE_getdirentries) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* Linux's underlying system call for reading the entries of a directory */
__CDECLARE(__ATTR_NONNULL((2, 4)),__SSIZE_TYPE__,__NOTHROW_RPC,getdirentries,(__fd_t __fd, char *__restrict __buf, size_t __nbytes, __off32_t *__restrict __basep),(__fd,__buf,__nbytes,__basep))
#elif defined(__CRT_HAVE_getdirentries64) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
/* Linux's underlying system call for reading the entries of a directory */
__CREDIRECT(__ATTR_NONNULL((2, 4)),__SSIZE_TYPE__,__NOTHROW_RPC,getdirentries,(__fd_t __fd, char *__restrict __buf, size_t __nbytes, __off64_t *__restrict __basep),getdirentries64,(__fd,__buf,__nbytes,__basep))
#endif /* getdirentries... */
#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_getdirentries64)
/* 64-bit variant of `getdirentries()' */
__CDECLARE(__ATTR_NONNULL((2, 4)),__SSIZE_TYPE__,__NOTHROW_RPC,getdirentries64,(__fd_t __fd, char *__restrict __buf, size_t __nbytes, __off64_t *__restrict __basep),(__fd,__buf,__nbytes,__basep))
#elif defined(__CRT_HAVE_getdirentries) && (defined(_DIRENT_MATCHES_DIRENT64))
/* 64-bit variant of `getdirentries()' */
__CREDIRECT(__ATTR_NONNULL((2, 4)),__SSIZE_TYPE__,__NOTHROW_RPC,getdirentries64,(__fd_t __fd, char *__restrict __buf, size_t __nbytes, __off64_t *__restrict __basep),getdirentries,(__fd,__buf,__nbytes,__basep))
#endif /* getdirentries64... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_MISC */

#ifdef __USE_GNU
#if defined(__CRT_HAVE_versionsort)
/* Sort the 2 given directory entries `E1' and `E2' the same way `strvercmp(3)' would. */
__CDECLARE(__ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,versionsort,(struct dirent const **__e1, struct dirent const **__e2),(__e1,__e2))
#elif defined(__CRT_HAVE_versionsort64) && (defined(_DIRENT_MATCHES_DIRENT64))
/* Sort the 2 given directory entries `E1' and `E2' the same way `strvercmp(3)' would. */
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,versionsort,(struct dirent const **__e1, struct dirent const **__e2),versionsort64,(__e1,__e2))
#else /* LIBC: versionsort */
#include <local/dirent/versionsort.h>
/* Sort the 2 given directory entries `E1' and `E2' the same way `strvercmp(3)' would. */
__NAMESPACE_LOCAL_USING_OR_IMPL(versionsort, __FORCELOCAL __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL versionsort)(struct dirent const **__e1, struct dirent const **__e2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(versionsort))(__e1, __e2); })
#endif /* versionsort... */
#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_versionsort64)
/* 64-bit variant of `versionsort()' */
__CDECLARE(__ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,versionsort64,(struct dirent64 const **__e1, struct dirent64 const **__e2),(__e1,__e2))
#elif defined(__CRT_HAVE_versionsort) && (defined(_DIRENT_MATCHES_DIRENT64))
/* 64-bit variant of `versionsort()' */
__CREDIRECT(__ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,versionsort64,(struct dirent64 const **__e1, struct dirent64 const **__e2),versionsort,(__e1,__e2))
#else /* LIBC: versionsort64 */
#include <local/dirent/versionsort64.h>
/* 64-bit variant of `versionsort()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(versionsort64, __FORCELOCAL __ATTR_PURE __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL versionsort64)(struct dirent64 const **__e1, struct dirent64 const **__e2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(versionsort64))(__e1, __e2); })
#endif /* versionsort64... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_GNU */

#if defined(__USE_KOS) && defined(__KOS__)
#if defined(__CRT_HAVE_kreaddir)
/* The KOS-specific system call for reading a single directory entry
 * from a file descriptor referring to an open directory stream.
 * @param: MODE: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When `READDIR_DEFAULT' was passed for `MODE', the directory
 *                    stream will only be advanced when this value is >= 'BUFSIZE'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
__CDECLARE(__ATTR_WUNUSED,__SSIZE_TYPE__,__NOTHROW_RPC,kreaddir,(__fd_t __fd, struct dirent *__buf, size_t __bufsize, unsigned int __mode),(__fd,__buf,__bufsize,__mode))
#elif defined(__CRT_HAVE_kreaddir64) && (defined(_DIRENT_MATCHES_DIRENT64))
/* The KOS-specific system call for reading a single directory entry
 * from a file descriptor referring to an open directory stream.
 * @param: MODE: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When `READDIR_DEFAULT' was passed for `MODE', the directory
 *                    stream will only be advanced when this value is >= 'BUFSIZE'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
__CREDIRECT(__ATTR_WUNUSED,__SSIZE_TYPE__,__NOTHROW_RPC,kreaddir,(__fd_t __fd, struct dirent *__buf, size_t __bufsize, unsigned int __mode),kreaddir64,(__fd,__buf,__bufsize,__mode))
#elif defined(__CRT_HAVE_kreaddirf) || (defined(__CRT_HAVE_kreaddirf64) && defined(_DIRENT_MATCHES_DIRENT64))
#include <local/dirent/kreaddir.h>
/* The KOS-specific system call for reading a single directory entry
 * from a file descriptor referring to an open directory stream.
 * @param: MODE: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When `READDIR_DEFAULT' was passed for `MODE', the directory
 *                    stream will only be advanced when this value is >= 'BUFSIZE'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(kreaddir, __FORCELOCAL __ATTR_WUNUSED __SSIZE_TYPE__ __NOTHROW_RPC(__LIBCCALL kreaddir)(__fd_t __fd, struct dirent *__buf, size_t __bufsize, unsigned int __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(kreaddir))(__fd, __buf, __bufsize, __mode); })
#endif /* kreaddir... */
#if defined(__CRT_HAVE_kreaddirf)
/* The KOS-specific system call for reading a single directory entry
 * from a file descriptor referring to an open directory stream.
 * @param: MODE: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When `READDIR_DEFAULT' was passed for `MODE', the directory
 *                    stream will only be advanced when this value is >= 'BUFSIZE'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
__CDECLARE(__ATTR_WUNUSED,__SSIZE_TYPE__,__NOTHROW_RPC,kreaddirf,(__fd_t __fd, struct dirent *__buf, size_t __bufsize, unsigned int __mode, __oflag_t __flags),(__fd,__buf,__bufsize,__mode,__flags))
#elif defined(__CRT_HAVE_kreaddirf64) && (defined(_DIRENT_MATCHES_DIRENT64))
/* The KOS-specific system call for reading a single directory entry
 * from a file descriptor referring to an open directory stream.
 * @param: MODE: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When `READDIR_DEFAULT' was passed for `MODE', the directory
 *                    stream will only be advanced when this value is >= 'BUFSIZE'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
__CREDIRECT(__ATTR_WUNUSED,__SSIZE_TYPE__,__NOTHROW_RPC,kreaddirf,(__fd_t __fd, struct dirent *__buf, size_t __bufsize, unsigned int __mode, __oflag_t __flags),kreaddirf64,(__fd,__buf,__bufsize,__mode,__flags))
#endif /* kreaddirf... */
#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_kreaddir64)
/* 64-bit variant of `kreaddir()' */
__CDECLARE(__ATTR_WUNUSED,__SSIZE_TYPE__,__NOTHROW_RPC,kreaddir64,(__fd_t __fd, struct dirent64 *__buf, size_t __bufsize, unsigned int __mode),(__fd,__buf,__bufsize,__mode))
#elif defined(__CRT_HAVE_kreaddir) && (defined(_DIRENT_MATCHES_DIRENT64))
/* 64-bit variant of `kreaddir()' */
__CREDIRECT(__ATTR_WUNUSED,__SSIZE_TYPE__,__NOTHROW_RPC,kreaddir64,(__fd_t __fd, struct dirent64 *__buf, size_t __bufsize, unsigned int __mode),kreaddir,(__fd,__buf,__bufsize,__mode))
#elif defined(__CRT_HAVE_kreaddirf64) || (defined(__CRT_HAVE_kreaddirf) && defined(_DIRENT_MATCHES_DIRENT64))
#include <local/dirent/kreaddir64.h>
/* 64-bit variant of `kreaddir()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(kreaddir64, __FORCELOCAL __ATTR_WUNUSED __SSIZE_TYPE__ __NOTHROW_RPC(__LIBCCALL kreaddir64)(__fd_t __fd, struct dirent64 *__buf, size_t __bufsize, unsigned int __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(kreaddir64))(__fd, __buf, __bufsize, __mode); })
#endif /* kreaddir64... */
#if defined(__CRT_HAVE_kreaddirf64)
/* 64-bit variant of `kreaddirf()' */
__CDECLARE(__ATTR_WUNUSED,__SSIZE_TYPE__,__NOTHROW_RPC,kreaddirf64,(__fd_t __fd, struct dirent64 *__buf, size_t __bufsize, unsigned int __mode, __oflag_t __flags),(__fd,__buf,__bufsize,__mode,__flags))
#elif defined(__CRT_HAVE_kreaddirf) && (defined(_DIRENT_MATCHES_DIRENT64))
/* 64-bit variant of `kreaddirf()' */
__CREDIRECT(__ATTR_WUNUSED,__SSIZE_TYPE__,__NOTHROW_RPC,kreaddirf64,(__fd_t __fd, struct dirent64 *__buf, size_t __bufsize, unsigned int __mode, __oflag_t __flags),kreaddirf,(__fd,__buf,__bufsize,__mode,__flags))
#endif /* kreaddirf64... */
#endif /* __USE_LARGEFILE64 */

#ifndef READDIR_DEFAULT
#define READDIR_DEFAULT  0x0000 /* Yield to next entry when `buf' was of sufficient size. */
#define READDIR_CONTINUE 0x0001 /* Always yield to next entry. */
#define READDIR_PEEK     0x0002 /* Never yield to next entry. */
#if __KOS_VERSION__ >= 300
#define READDIR_SKIPREL  0x4000 /* Skip reading the `.' and `..' directory entries. */
#define READDIR_WANTEOF  0x8000 /* Minor optimization for `READDIR_MULTIPLE':
                                 * The system is allowed to append an empty directory entry
                                 * (with `d_namlen = 0' and `d_name[0] = '\0''; other fields are undefined).
                                 * If there isn't enough space for such an entry, no such entry will be emit.
                                 * Since no other directory entry can ever have a length of ZERO(0),
                                 * this allows user-space to detect end-of-directory without the need
                                 * of re-invoking the kreaddir() system call and inspecting its return
                                 * value for being equal to ZERO(0).
                                 * However, that check is still required, as this flag may be ignored
                                 * for no reason immediately apparent (if the EOF entry can't fit into
                                 * the buffer, there's no way of knowing if there's a missing entry that's
                                 * supposed to go into the buffer, or if it was actually an EOF entry).
                                 * Additionally, no eof entry may be written if kreaddir() is invoked
                                 * on a directory handle who's stream position is at the end of the directory.
                                 * For usage, see the example below, as well as `READDIR_MULTIPLE_ISEOF()' */
#define READDIR_MODEMASK 0x001f /* Mask for the kreaddir() mode. */
#define READDIR_FLAGMASK 0xc000 /* Mask of known kreaddir() flags. */
#define READDIR_MODEMAX  0x0003 /* Mask recognized mode ID. */
#define READDIR_MULTIPLE 0x0003 /* Read as many directory entries as can fit into the buffer.
                                 * If at least one entry could be read, return the combined size
                                 * of all read entries (in bytes) (in this case, `return <= bufsize')
                                 * If the buffer was too small to contain the next entry,
                                 * return the required size to house that pending entry,
                                 * but don't yield it, the same way `READDIR_DEFAULT' wouldn't.
                                 * To enumerate multiple directories in some buffer, use the
                                 * macros below. */
#ifdef __CC__
/* READDIR_MULTIPLE buffer helpers:
 * >> for (;;) {
 * >>     char buffer[2048]; size_t bufsize;
 * >>     struct dirent *iter = (struct dirent *)buffer;
 * >>     // Read as many entries as our buffer can fit
 * >>     bufsize = kreaddir(fd, iter, sizeof(buffer),
 * >>                        READDIR_MULTIPLE|
 * >>                        READDIR_WANTEOF);
 * >>     if (!bufsize) break; // End of directory
 * >>     if (bufsize > sizeof(buffer)) {
 * >>         printf("The next directory entry is too larger for the buffer\n");
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
#define READDIR_MULTIPLE_GETNEXT(p) \
   ((struct dirent *)(((uintptr_t)((p)->d_name+((p)->d_namlen+1))+ \
                       (sizeof(__ino64_t)-1)) & ~(sizeof(__ino64_t)-1)))
#define READDIR_MULTIPLE_ISVALID(p, buf, bufsize) \
   (((__BYTE_TYPE__ *)((p)->d_name)) < ((__BYTE_TYPE__ *)(buf)+(bufsize)) && \
    ((__BYTE_TYPE__ *)((p)->d_name+(p)->d_namlen)) < ((__BYTE_TYPE__ *)(buf)+(bufsize)))
#define READDIR_MULTIPLE_ISEOF(p) ((p)->d_namlen == 0)
#ifdef __USE_LARGEFILE64
#define READDIR_MULTIPLE_GETNEXT64(p) ((struct dirent64 *)READDIR_MULTIPLE_GETNEXT(p))
#endif /* __USE_LARGEFILE64 */
#endif /* __CC__ */
#endif /* __KOS_VERSION__ >= 300 */
#endif /* !READDIR_DEFAULT */
#endif /* __USE_KOS */

#endif /* __CC__ */

__SYSDECL_END
#endif /* !__CRT_DOS_PRIMARY */

#endif /* !_DIRENT_H */
