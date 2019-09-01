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

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(atflag_t = __atflag_t)]
%[define_replacement(mode_t = __mode_t)]
%[define_replacement(dev_t = __dev_t)]
%[define_replacement(timespec = __TM_TYPE(timespec))]
%[define_replacement(timespec32 = __timespec32)]
%[define_replacement(timespec64 = __timespec64)]
%[define_replacement(time_t = __TM_TYPE(time))]
%[define_replacement(time32_t = __time32_t)]
%[define_replacement(time64_t = __time64_t)]

%[declare_known_section(.text.crt.fs.stat)]
%[declare_known_section(.text.crt.fs.stat_glc)]

%{
#include <features.h>
#include <bits/types.h>
#include <bits/stat.h>
#include <bits/timespec.h>

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#include <time.h>
#endif /* __USE_XOPEN || __USE_XOPEN2K */

__SYSDECL_BEGIN

#ifdef __CC__

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#ifndef __dev_t_defined
#define __dev_t_defined 1
typedef __typedef_dev_t dev_t;
#endif /* __dev_t_defined */

#ifndef __gid_t_defined
#define __gid_t_defined 1
typedef __gid_t gid_t;
#endif /* __gid_t_defined */

#ifndef __ino_t_defined
#define __ino_t_defined 1
typedef __typedef_ino_t ino_t;
#endif /* __ino_t_defined */

#ifndef __mode_t_defined
#define __mode_t_defined 1
typedef __mode_t mode_t;
#endif /* __mode_t_defined */

#ifndef __nlink_t_defined
#define __nlink_t_defined 1
typedef __nlink_t nlink_t;
#endif /* __nlink_t_defined */

#ifndef __off_t_defined
#define __off_t_defined 1
typedef __typedef_off_t off_t;
#endif /* __off_t_defined */

#ifndef __uid_t_defined
#define __uid_t_defined 1
typedef __uid_t uid_t;
#endif /* __uid_t_defined */
#endif /* __USE_XOPEN || __USE_XOPEN2K */

#ifdef __USE_UNIX98
#ifndef __blkcnt_t_defined
#define __blkcnt_t_defined 1
typedef __FS_TYPE(blkcnt)   blkcnt_t;
#endif /* __blkcnt_t_defined */

#ifndef __blksize_t_defined
#define __blksize_t_defined 1
typedef __blksize_t blksize_t;
#endif /* __blksize_t_defined */
#endif /* __USE_UNIX98 */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifndef S_IFMT
#define S_IFMT     __S_IFMT
#define S_IFDIR    __S_IFDIR
#define S_IFCHR    __S_IFCHR
#define S_IFBLK    __S_IFBLK
#define S_IFREG    __S_IFREG
#endif /* !S_IFMT */
#if !defined(S_IFIFO) && defined(__S_IFIFO)
#define S_IFIFO    __S_IFIFO
#endif
#if !defined(S_IFLNK) && defined(__S_IFLNK)
#define S_IFLNK    __S_IFLNK
#endif
#if (defined(__USE_MISC) || defined(__USE_UNIX98)) && \
    !defined(S_IFSOCK) && defined(__S_IFSOCK)
#define S_IFSOCK   __S_IFSOCK
#endif
#endif /* __USE_MISC || __USE_XOPEN */

#ifndef __S_ISTYPE
#define __S_ISTYPE(mode, mask)   (((mode)&__S_IFMT)==(mask))
#endif /* !__S_ISTYPE */

#ifndef S_ISDIR
#define S_ISDIR(mode)  __S_ISTYPE((mode), __S_IFDIR)
#define S_ISCHR(mode)  __S_ISTYPE((mode), __S_IFCHR)
#define S_ISBLK(mode)  __S_ISTYPE((mode), __S_IFBLK)
#define S_ISREG(mode)  __S_ISTYPE((mode), __S_IFREG)
#endif /* !S_ISDIR */

#if defined(__USE_KOS) && !defined(S_ISDEV)
#define S_ISDEV(mode)  __S_ISDEV(mode)
#endif /* __USE_KOS && !S_ISDEV */
#if defined(__S_IFIFO) && !defined(S_ISFIFO)
#define S_ISFIFO(mode) __S_ISTYPE((mode), __S_IFIFO)
#endif /* __S_IFIFO && !S_ISFIFO */
#if defined(__S_IFLNK) && !defined(S_ISLNK)
#define S_ISLNK(mode)  __S_ISTYPE((mode), __S_IFLNK)
#endif /* __S_IFLNK && !S_ISLNK */
#if defined(__USE_MISC) && !defined(S_ISLNK)
#define S_ISLNK(mode)  0
#endif /* __USE_MISC && !S_ISLNK */

#ifndef S_ISSOCK
#if (defined(__USE_UNIX98) || defined(__USE_XOPEN2K)) && \
     defined(__S_IFSOCK)
#define S_ISSOCK(mode) __S_ISTYPE((mode), __S_IFSOCK)
#elif defined(__USE_XOPEN2K)
#define S_ISSOCK(mode) 0
#endif
#endif /* !S_ISSOCK */

#ifdef __USE_POSIX199309
#ifndef S_TYPEISMQ
#define S_TYPEISMQ(buf)  __S_TYPEISMQ(buf)
#endif
#ifndef S_TYPEISSEM
#define S_TYPEISSEM(buf) __S_TYPEISSEM(buf)
#endif
#ifndef S_TYPEISSHM
#define S_TYPEISSHM(buf) __S_TYPEISSHM(buf)
#endif
#endif /* __USE_POSIX199309 */

#ifndef S_ISUID
#define S_ISUID __S_ISUID /* Set user ID on execution. */
#define S_ISGID __S_ISGID /* Set group ID on execution. */
#endif

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifndef S_ISVTX
#define S_ISVTX __S_ISVTX
#endif
#endif

#ifndef S_IRUSR
#define S_IRUSR  __S_IREAD  /* Read by owner. */
#define S_IWUSR  __S_IWRITE /* Write by owner. */
#define S_IXUSR  __S_IEXEC  /* Execute by owner. */
#endif
#ifndef S_IRWXU
#define S_IRWXU (__S_IREAD|__S_IWRITE|__S_IEXEC)
#endif

#ifdef __USE_MISC
#ifndef S_IREAD
#define S_IREAD  S_IRUSR
#define S_IWRITE S_IWUSR
#define S_IEXEC  S_IXUSR
#endif
#endif /* __USE_MISC */

#ifndef S_IRGRP
#define S_IRGRP (S_IRUSR >> 3) /* Read by group. */
#define S_IWGRP (S_IWUSR >> 3) /* Write by group. */
#define S_IXGRP (S_IXUSR >> 3) /* Execute by group. */
#endif
#ifndef S_IRWXG
#define S_IRWXG (S_IRWXU >> 3)
#endif
#ifndef S_IROTH
#define S_IROTH (S_IRGRP >> 3) /* Read by others. */
#define S_IWOTH (S_IWGRP >> 3) /* Write by others. */
#define S_IXOTH (S_IXGRP >> 3) /* Execute by others. */
#endif
#ifndef S_IRWXO
#define S_IRWXO (S_IRWXG >> 3)
#endif



#ifdef __USE_KOS
/* As also seen in the linux kernel headers. */
#ifndef S_IRWXUGO
#define S_IRWXUGO (S_IRWXU|S_IRWXG|S_IRWXO)
#endif /* !S_IRWXUGO */
#ifndef S_IALLUGO
#define S_IALLUGO (S_ISUID|S_ISGID|S_ISVTX|S_IRWXUGO)
#endif /* !S_IALLUGO */
#ifndef S_IRUGO
#define S_IRUGO   (S_IRUSR|S_IRGRP|S_IROTH)
#endif /* !S_IRUGO */
#ifndef S_IWUGO
#define S_IWUGO   (S_IWUSR|S_IWGRP|S_IWOTH)
#endif /* !S_IWUGO */
#ifndef S_IXUGO
#define S_IXUGO   (S_IXUSR|S_IXGRP|S_IXOTH)
#endif /* !S_IXUGO */
#endif /* __USE_KOS */

#ifdef __USE_MISC
#ifndef ACCESSPERMS
#define ACCESSPERMS (S_IRWXU|S_IRWXG|S_IRWXO) /* 0777 */
#endif /* !ACCESSPERMS */
#ifndef ALLPERMS
#define ALLPERMS    (S_ISUID|S_ISGID|S_ISVTX|S_IRWXU|S_IRWXG|S_IRWXO)/* 07777 */
#endif /* !ALLPERMS */
#ifndef DEFFILEMODE
#define DEFFILEMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)/* 0666*/
#endif /* !DEFFILEMODE */
#ifndef S_BLKSIZE
#define S_BLKSIZE    512 /* Block size for `st_blocks'. */
#endif /* !S_BLKSIZE */
#endif /* __USE_MISC */

#ifdef __USE_DOS
#define _S_IFMT   __S_IFMT
#define _S_IFDIR  __S_IFDIR
#define _S_IFCHR  __S_IFCHR
#define _S_IFIFO  __S_IFIFO
#define _S_IFREG  __S_IFREG
#define _S_IREAD  __S_IREAD
#define _S_IWRITE __S_IWRITE
#define _S_IEXEC  __S_IEXEC
#endif /* __USE_DOS */

#undef stat
#undef fstat
#undef lstat
#ifdef __USE_LARGEFILE64
#undef stat64
#undef fstat64
#undef lstat64
#endif /* __USE_LARGEFILE64 */

}

/* Recognized & known stat() structures and assembly names.
 *
 * __CRT_KOS: (Used by default)
 * >> int CDECL kfstat(fd_t fd, struct __kos_stat *buf);
 * >> int CDECL kfstat64(fd_t fd, struct __kos_stat *buf);
 * >> int CDECL kstat(char const *filename, struct __kos_stat *buf);
 * >> int CDECL kstat64(char const *filename, struct __kos_stat *buf);
 * >> int CDECL kfstatat(fd_t dirfd, char const *filename, struct __kos_stat *buf, atflag_t flags);
 * >> int CDECL kfstatat64(fd_t dirfd, char const *filename, struct __kos_stat *buf, atflag_t flags);
 * >> int CDECL klstat(char const *filename, struct __kos_stat *buf);
 * >> int CDECL klstat64(char const *filename, struct __kos_stat *buf);
 *
 * __CRT_GLC: (__GLC_COMPAT__)
 * >> int CDECL fstat(fd_t fd, struct __glc_stat *buf);
 * >> int CDECL fstat64(fd_t fd, struct __glc_stat64 *buf);
 * >> int CDECL stat(char const *filename, struct __glc_stat *buf);
 * >> int CDECL stat64(char const *filename, struct __glc_stat64 *buf);
 * >> int CDECL fstatat(fd_t dirfd, char const *filename, struct __glc_stat *buf, atflag_t flags);
 * >> int CDECL fstatat64(fd_t dirfd, char const *filename, struct __glc_stat64 *buf, atflag_t flags);
 * >> int CDECL lstat(char const *filename, struct __glc_stat *buf);
 * >> int CDECL lstat64(char const *filename, struct __glc_stat64 *buf);
 *
 * __CRT_DOS: (__DOS_COMPAT__)
 * >> int CDECL [OLD: _fstat,    NEW:_fstat32] (fd_t fd, struct __dos_stat32 *buf);
 * >> int CDECL [OLD: _fstati64, NEW:_fstat32i64] (fd_t fd, struct __dos_stat32i64 *buf);
 * >> int CDECL [OLD: _stat,     NEW:_stat32] (char const *filename, struct __dos_stat32 *buf);
 * >> int CDECL [OLD: _stati64,  NEW:_stat32i64] (char const *filename, struct __dos_stat32i64 *buf);
 * >> int CDECL _fstat64(fd_t fd, struct __dos_stat64 *buf);
 * >> int CDECL _stat64(char const *filename, struct __dos_stat64 *buf);
 * >> int CDECL [NEW: _fstat64i32](fd_t fd, struct __dos_stat64i32 *buf) = _fstat64;
 * >> int CDECL [NEW: _stat64i32](char const *filename, struct __dos_stat64i32 *buf) = _stat64;
 *
 * NOTE: Since KOS uses a different `stat' buffer than glibc, but still wants to
 *       maintain binary compatibility, the `stat()' function provided internally
 *       accepts a glibc-compatible stat buffer, while the functions making use
 *       of what we (and the kernel) defines as its stat()-buffer are actually
 *       named 'kstat()' */


/* When running as `__CRT_DOS_PRIMARY':
 *   `struct stat' is:
 *       [                                       ] = struct __dos_stat32
 *       [__USE_TIME_BITS64                      ] = struct __dos_stat64i32 == struct __dos_stat64
 *       [__USE_FILE_OFFSET64                    ] = struct __dos_stat32i64
 *       [__USE_TIME_BITS64 + __USE_FILE_OFFSET64] = struct __dos_stat64
 *   `struct stat64' is:
 *       [                 ]                       = struct __dos_stat32i64
 *       [__USE_TIME_BITS64]                       = struct __dos_stat64
 * When running as `__CRT_KOS_PRIMARY':
 *   `struct stat' is:                             = struct __kos_stat
 *   `struct stat64' is:                           = struct __kos_stat
 * When running as `__CRT_GLC_PRIMARY':
 *   `struct stat' is:
 *       [                   ]                     = struct __cyg_stat
 *       [__USE_FILE_OFFSET64]                     = struct __glc_stat64
 *   `struct stat64' is:                           = struct __glc_stat64
 * When running as `__CRT_CYG_PRIMARY':
 *   `struct stat' is:                             = struct __cyg_stat
 *   `struct stat64' is:                           = struct __cyg_stat
 * Otherwise, `struct stat' uses a totally generic layout.
 */

%[default_impl_section(.text.crt.fs.stat)]

/* Name format: `<N_TIME_BITS>i<N_FILE_BITS>' */
[ignore][alias(_stat32)]     dos_stat32i32:([nonnull] char const *__restrict filename, [nonnull] struct __dos_stat32 *__restrict buf) -> int = _stat?;
[ignore][alias(_stat32i64)]  dos_stat32i64:([nonnull] char const *__restrict filename, [nonnull] struct __dos_stat32i64 *__restrict buf) -> int = _stati64?;
[ignore][alias(_stat64i32)]  dos_stat64i32:([nonnull] char const *__restrict filename, [nonnull] struct __dos_stat64i32 *__restrict buf) -> int = _stat64?;
[ignore][alias(_stat64i32)]  dos_stat64i64:([nonnull] char const *__restrict filename, [nonnull] struct __dos_stat64 *__restrict buf) -> int = _stat64?;
[ignore][alias(_fstat32)]    dos_fstat32i32:($fd_t fd, [nonnull] struct __dos_stat32 *__restrict buf) -> int = _fstat?;
[ignore][alias(_fstat32i64)] dos_fstat32i64:($fd_t fd, [nonnull] struct __dos_stat32i64 *__restrict buf) -> int = _fstati64?;
[ignore][alias(_fstat64i32)] dos_fstat64i32:($fd_t fd, [nonnull] struct __dos_stat64i32 *__restrict buf) -> int = _fstat64?;
[ignore][alias(_fstat64i32)] dos_fstat64i64:($fd_t fd, [nonnull] struct __dos_stat64 *__restrict buf) -> int = _fstat64?;

//[ignore] glibc_stat:([nonnull] char const *__restrict filename, [nonnull] struct __glc_stat *__restrict buf) -> int = stat?;
//[ignore] glibc_stat64:([nonnull] char const *__restrict filename, [nonnull] struct __glc_stat64 *__restrict buf) -> int = stat64?;
//[ignore] glibc_lstat:([nonnull] char const *__restrict filename, [nonnull] struct __glc_stat *__restrict buf) -> int = lstat?;
//[ignore] glibc_lstat64:([nonnull] char const *__restrict filename, [nonnull] struct __glc_stat64 *__restrict buf) -> int = lstat64?;
//[ignore] glibc_fstat:($fd_t fd, [nonnull] struct __glc_stat *__restrict buf) -> int = fstat?;
//[ignore] glibc_fstat64:($fd_t fd, [nonnull] struct __glc_stat64 *__restrict buf) -> int = fstat64?;


[nouser]
[if(defined(__CRT_KOS_PRIMARY)), preferred_alias(kstat, kstat64)]
[if(defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)), preferred_alias(_stat64, _stat64i32)]
[if(defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)), preferred_alias(_stati64, _stat32i64)]
[if(defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)), preferred_alias(_stat, _stat32)]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(stat64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(stat)]
[noexport] stat:([nonnull] char const *__restrict filename, [nonnull] struct stat *__restrict buf) -> int;
/* TODO: Emulate stat() for __USE_TIME_BITS64 compatibility! */


%
[nouser][noexport]
[if(defined(__CRT_KOS_PRIMARY)), preferred_alias(kfstat, kfstat64)]
[if(defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)), preferred_alias(_fstat64, _fstat64i32)]
[if(defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)), preferred_alias(_fstati64, _fstat32i64)]
[if(defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)), preferred_alias(_fstat, _fstat32)]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(fstat64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(fstat)]
fstat:($fd_t fd, [nonnull] struct stat *__restrict buf) -> int;

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
[nouser][noexport]
[if(defined(__CRT_KOS_PRIMARY)), preferred_alias(klstat, klstat64)]
[if(defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)), preferred_alias(_stat64, _stat64i32)]
[if(defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)), preferred_alias(_stati64, _stat32i64)]
[if(defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)), preferred_alias(_stat, _stat32)]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(lstat64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(lstat)]
lstat:([nonnull] char const *__restrict filename, [nonnull] struct stat *__restrict buf) -> int;
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

%
%#ifdef __USE_LARGEFILE64
[if(defined(__CRT_KOS_PRIMARY)), preferred_alias(kstat, kstat64)]
[if(defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)), preferred_alias(_stat64, _stat64i32)]
[if(defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)), preferred_alias(_stati64, _stat32i64)]
[preferred_alias(stat64)][noexport][nouser]
stat64:([nonnull] char const *__restrict filename, [nonnull] struct stat64 *__restrict buf) -> int;

%
[if(defined(__CRT_KOS_PRIMARY)), preferred_alias(kfstat, kfstat64)]
[if(defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)), preferred_alias(_fstat64, _fstat64i32)]
[if(defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)), preferred_alias(_fstati64, _fstat32i64)]
[preferred_alias(fstat64)][noexport][nouser]
fstat64:($fd_t fd, [nonnull] struct stat64 *__restrict buf) -> int;

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
[if(defined(__CRT_KOS_PRIMARY)), preferred_alias(klstat, klstat64)]
[if(defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)), preferred_alias(_stat64, _stat64i32)]
[if(defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)), preferred_alias(_stati64, _stat32i64)]
[preferred_alias(lstat64)][noexport][nouser]
lstat64:([nonnull] char const *__restrict filename, [nonnull] struct stat64 *__restrict buf) -> int;
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */
%#endif /* __USE_LARGEFILE64 */

%
%

%(user){
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_kos_fstat)(fd_t fd, struct __kos_stat *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_kos_stat)(char const *__restrict filename, struct __kos_stat *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_kos_lstat)(char const *__restrict filename, struct __kos_stat *__restrict buf);
INTDEF NONNULL((2, 3)) int NOTHROW_NCX(LIBCCALL libc_kos_fstatat)(fd_t dirfd, char const *__restrict filename, struct __kos_stat *__restrict buf, atflag_t flags);

INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_cyg_fstat)(fd_t fd, struct __cyg_stat *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_cyg_stat)(char const *__restrict filename, struct __cyg_stat *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_cyg_lstat)(char const *__restrict filename, struct __cyg_stat *__restrict buf);
INTDEF NONNULL((2, 3)) int NOTHROW_NCX(LIBCCALL libc_cyg_fstatat)(fd_t dirfd, char const *__restrict filename, struct __cyg_stat *__restrict buf, atflag_t flags);

INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_glc_fstat)(fd_t fd, struct __glc_stat *__restrict buf);
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_glc_fstat64)(fd_t fd, struct __glc_stat64 *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_glc_stat)(char const *__restrict filename, struct __glc_stat *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_glc_stat64)(char const *__restrict filename, struct __glc_stat64 *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_glc_lstat)(char const *__restrict filename, struct __glc_stat *__restrict buf);
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_glc_lstat64)(char const *__restrict filename, struct __glc_stat64 *__restrict buf);
INTDEF NONNULL((2, 3)) int NOTHROW_NCX(LIBCCALL libc_glc_fstatat)(fd_t dirfd, char const *__restrict filename, struct __glc_stat *__restrict buf, atflag_t flags);
INTDEF NONNULL((2, 3)) int NOTHROW_NCX(LIBCCALL libc_glc_fstatat64)(fd_t dirfd, char const *__restrict filename, struct __glc_stat64 *__restrict buf, atflag_t flags);

INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_dos_fstat32)(fd_t fd, struct __dos_stat32 *__restrict buf); /* _fstat, _fstat32 */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_dos_fstat32i64)(fd_t fd, struct __dos_stat32i64 *__restrict buf); /* _fstati64, _fstat32i64 */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_dos_fstat64)(fd_t fd, struct __dos_stat64 *__restrict buf); /* _fstat64, _fstat64i32 */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_dos_stat32)(char const *__restrict filename, struct __dos_stat32 *__restrict buf); /* _stat, _stat32 */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_dos_stat32i64)(char const *__restrict filename, struct __dos_stat32i64 *__restrict buf); /* _stati64, _stat32i64 */
INTDEF NONNULL((1, 2)) int NOTHROW_NCX(LIBCCALL libc_dos_stat64)(char const *__restrict filename, struct __dos_stat64 *__restrict buf); /* _stat64, _stat64i32 */


}


%
%#ifdef __USE_ATFILE

@@@param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH'
[if(defined(__CRT_KOS_PRIMARY)), preferred_alias(kfstatat, kfstatat64)]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(fstatat64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(fstatat)]
[noexport][nouser]
fstatat:($fd_t dirfd, [nonnull] char const *__restrict filename,
         [nonnull] struct stat *__restrict buf, $atflag_t flags) -> int;

%#ifdef __USE_LARGEFILE64
@@@param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH'
[if(defined(__CRT_KOS_PRIMARY)), preferred_alias(kfstatat, kfstatat64)]
[noexport][nouser]
fstatat64:($fd_t dirfd, [nonnull] char const *__restrict filename,
           [nonnull] struct stat *__restrict buf, $atflag_t flags) -> int;
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_ATFILE */

%[default_impl_section(.text.crt.fs.modify)]

[cp][ignore] dos_mkdir:([nonnull] char const *pathname) -> int = _mkdir?;

%
[cp][guard][noexport]
[requires(defined(__CRT_DOS_PRIMARY) && defined(__CRT_HAVE__mkdir))]
mkdir:([nonnull] char const *pathname, $mode_t mode) -> int {
	(void)mode;
	return dos_mkdir(pathname);
}

%
[cp][guard][alias(_chmod)]
chmod:([nonnull] char const *filename, $mode_t mode) -> int;


%
%#ifdef __USE_MISC
[cp][guard]
[if(defined(__CRT_DOS_PRIMARY)), alias(_chmod, chmod)]
lchmod:([nonnull] char const *filename, $mode_t mode) -> int;
%#endif /* __USE_MISC */

%[default_impl_section(.text.crt.fs.basic_property)]

%
[guard][alias(_umask)] umask:($mode_t mode) -> $mode_t;

%
%#ifdef __USE_GNU
@@Return the current umask.
@@WARNING: This function isn't thread-safe
[requires(defined(__CRT_HAVE_umask) || defined(__CRT_HAVE__umask))]
getumask:() -> $mode_t {
	$mode_t result;
	result = umask(0);
	umask(result);
	return result;
}
%#endif /* __USE_GNU */

%[default_impl_section(.text.crt.fs.modify)]

%
%#if defined(__USE_KOS) && defined(__USE_ATFILE)
@@@param flags: Set of `0|AT_DOSPATH'
[cp] fmkdirat:($fd_t dirfd, [nonnull] char const *pathname, $mode_t mode, $atflag_t flags) -> int;

@@@param flags: Set of `0|AT_DOSPATH'
[cp] fmknodat:($fd_t dirfd, [nonnull] char const *nodename, $mode_t mode, $dev_t dev, $atflag_t flags) -> int;
%#endif


%
[cp] mkfifo:([nonnull] char const *fifoname, $mode_t mode) -> int;

%
%#ifdef __USE_ATFILE
@@@param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH'
[cp] fchmodat:($fd_t dirfd, [nonnull] char const *filename, $mode_t mode, $atflag_t flags) -> int;
[cp] mkdirat:($fd_t dirfd, [nonnull] char const *pathname, $mode_t mode) -> int;
[cp] mkfifoat:($fd_t dirfd, [nonnull] char const *fifoname, $mode_t mode) -> int;
%#endif /* __USE_ATFILE */

%
%#ifdef __USE_POSIX
[cp] fchmod:($fd_t fd, $mode_t mode) -> int;
%#endif /* __USE_POSIX */

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
[cp] mknod:([nonnull] char const *nodename, $mode_t mode, $dev_t dev) -> int;
%#ifdef __USE_ATFILE
[cp] mknodat:($fd_t dirfd, [nonnull] char const *nodename, $mode_t mode, $dev_t dev) -> int;
%#endif /* __USE_ATFILE */
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

%[default_impl_section(.text.crt.fs.modify_time)]
@@@param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH'
[cp][ignore]
utimensat32:($fd_t dirfd, [nonnull] char const *filename,
             [nullable] struct timespec const times[2/*or:3*/], $atflag_t flags) -> int = utimensat?;

%
%#ifdef __USE_ATFILE
@@@param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH'
[if(defined(__USE_TIME_BITS64)), preferred_alias(utimensat64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(utimensat)]
[cp][noexport][requires(defined(__CRT_HAVE_utimensat) || defined(__CRT_HAVE_utimensat64))]
utimensat:($fd_t dirfd, [nonnull] char const *filename,
           [nullable] struct timespec const times[2/*or:3*/], $atflag_t flags) -> int {
#ifdef __CRT_HAVE_utimensat64
#if defined(__KOS__) && __KOS_VERSION__ >= 300
	struct timespec64 tms[3];
	if (!times)
		return utimensat64(dirfd, filename, NULL, flags);
	tms[0].@tv_sec@  = (__time64_t)times[0].@tv_sec@;
	tms[0].@tv_nsec@ = times[0].@tv_nsec@;
	tms[1].@tv_sec@  = (__time64_t)times[1].@tv_sec@;
	tms[1].@tv_nsec@ = times[1].@tv_nsec@;
	if (flags & 0x0200) /* AT_CHANGE_CTIME */ {
		tms[2].@tv_sec@  = (__time64_t)times[2].@tv_sec@;
		tms[2].@tv_nsec@ = times[2].@tv_nsec@;
	}
	return utimensat64(dirfd, filename, tms, flags);
#else
	struct timespec64 tms[2];
	if (!times)
		return utimensat64(dirfd, filename, NULL, flags);
	tms[0].@tv_sec@  = (__time64_t)times[0].@tv_sec@;
	tms[0].@tv_nsec@ = times[0].@tv_nsec@;
	tms[1].@tv_sec@  = (__time64_t)times[1].@tv_sec@;
	tms[1].@tv_nsec@ = times[1].@tv_nsec@;
	return utimensat64(dirfd, filename, tms, flags);
#endif
#else /* __CRT_HAVE_utimensat64 */
#if defined(__KOS__) && __KOS_VERSION__ >= 300
	struct @__timespec32@ tms[3];
	if (!times)
		return utimensat32(dirfd, filename, NULL, flags);
	tms[0].@tv_sec@  = (__time32_t)times[0].@tv_sec@;
	tms[0].@tv_nsec@ = times[0].@tv_nsec@;
	tms[1].@tv_sec@  = (__time32_t)times[1].@tv_sec@;
	tms[1].@tv_nsec@ = times[1].@tv_nsec@;
	if (flags & 0x0200) /* AT_CHANGE_CTIME */ {
		tms[2].@tv_sec@  = (__time32_t)times[2].@tv_sec@;
		tms[2].@tv_nsec@ = times[2].@tv_nsec@;
	}
	return utimensat32(dirfd, filename, tms, flags);
#else
	struct @__timespec32@ tms[2];
	if (!times)
		return utimensat32(dirfd, filename, NULL, flags);
	tms[0].@tv_sec@  = (__time32_t)times[0].@tv_sec@;
	tms[0].@tv_nsec@ = times[0].@tv_nsec@;
	tms[1].@tv_sec@  = (__time32_t)times[1].@tv_sec@;
	tms[1].@tv_nsec@ = times[1].@tv_nsec@;
	return utimensat32(dirfd, filename, tms, flags);
#endif
#endif /* !__CRT_HAVE_utimensat64 */
}

%#ifdef __USE_TIME64
[time64_variant_of(utimensat)]
[cp][noexport][requires(defined(__CRT_HAVE_utimensat))]
utimensat64:($fd_t dirfd, [nonnull] char const *filename,
             [nullable] struct timespec64 const times[2/*or:3*/], $atflag_t flags) -> int {
#if defined(__KOS__) && __KOS_VERSION__ >= 300
	struct timespec32 tms[3];
	if (!times)
		return utimensat32(dirfd, filename, NULL, flags);
	tms[0].@tv_sec@  = (__time32_t)times[0].@tv_sec@;
	tms[0].@tv_nsec@ = times[0].@tv_nsec@;
	tms[1].@tv_sec@  = (__time32_t)times[1].@tv_sec@;
	tms[1].@tv_nsec@ = times[1].@tv_nsec@;
	if (flags & 0x0200) /* AT_CHANGE_CTIME */ {
		tms[2].@tv_sec@  = (__time32_t)times[2].@tv_sec@;
		tms[2].@tv_nsec@ = times[2].@tv_nsec@;
	}
	return utimensat32(dirfd, filename, tms, flags);
#else
	struct timespec32 tms[2];
	if (!times)
		return utimensat32(dirfd, filename, NULL, flags);
	tms[0].@tv_sec@  = (__time32_t)times[0].@tv_sec@;
	tms[0].@tv_nsec@ = times[0].@tv_nsec@;
	tms[1].@tv_sec@  = (__time32_t)times[1].@tv_sec@;
	tms[1].@tv_nsec@ = times[1].@tv_nsec@;
	return utimensat32(dirfd, filename, tms, flags);
#endif
}
%#endif /* __USE_TIME64 */
%#endif /* __USE_ATFILE */

[cp][ignore] futimens32:($fd_t fd, [nullable] struct timespec const times[2/*or:3*/]) -> int = futimens?;

%
%#ifdef __USE_XOPEN2K8
[cp][noexport]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futimens64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futimens)]
[requires(defined(__CRT_HAVE_futimens) || defined(__CRT_HAVE_futimens64))]
futimens:($fd_t fd, [nullable] struct timespec const times[2/*or:3*/]) -> int {
#ifdef __CRT_HAVE_utimensat64
	struct timespec64 tms[2];
	if (!times)
		return futimens64(fd, NULL);
	tms[0].@tv_sec@  = (__time64_t)times[0].@tv_sec@;
	tms[0].@tv_nsec@ = times[0].@tv_nsec@;
	tms[1].@tv_sec@  = (__time64_t)times[1].@tv_sec@;
	tms[1].@tv_nsec@ = times[1].@tv_nsec@;
	return futimens64(fd, tms);
#else /* __CRT_HAVE_utimensat64 */
	struct timespec32 tms[2];
	if (!times)
		return futimens32(fd, NULL);
	tms[0].@tv_sec@  = (__time32_t)times[0].@tv_sec@;
	tms[0].@tv_nsec@ = times[0].@tv_nsec@;
	tms[1].@tv_sec@  = (__time32_t)times[1].@tv_sec@;
	tms[1].@tv_nsec@ = times[1].@tv_nsec@;
	return futimens32(fd, tms);
#endif /* !__CRT_HAVE_utimensat64 */
}

%#ifdef __USE_TIME64
[time64_variant_of(futimens)]
[cp][noexport][requires(defined(__CRT_HAVE_futimens))]
futimens64:($fd_t fd, [nullable] struct timespec64 const times[2/*or:3*/]) -> int {
	struct timespec32 tms[2];
	if (!times)
		return futimens32(fd, NULL);
	tms[0].@tv_sec@  = (__time32_t)times[0].@tv_sec@;
	tms[0].@tv_nsec@ = times[0].@tv_nsec@;
	tms[1].@tv_sec@  = (__time32_t)times[1].@tv_sec@;
	tms[1].@tv_nsec@ = times[1].@tv_nsec@;
	return futimens32(fd, tms);
}
%#endif /* __USE_TIME64 */
%#endif /* __USE_XOPEN2K8 */

%
%
%/* Define DOS's redundant stat() functions. */
%#ifdef __USE_DOS

%[default_impl_section(.text.crt.dos.wchar.fs.stat)]

/* TODO: Emulate these functions when not running under DOS-CRT */
[alias(_stat32)]     _stat32:([nonnull] char const *__restrict filename, [nonnull] struct __dos_stat32 *__restrict buf) -> int = _stat?;
[alias(_stat32i64)]  _stat32i64:([nonnull] char const *__restrict filename, [nonnull] struct __dos_stat32i64 *__restrict buf) -> int = _stati64?;
[alias(_stat64i32)]  _stat64i32:([nonnull] char const *__restrict filename, [nonnull] struct __dos_stat64i32 *__restrict buf) -> int = _stat64?;
[alias(_stat64i32)]  _stat64:([nonnull] char const *__restrict filename, [nonnull] struct __dos_stat64 *__restrict buf) -> int = _stat64?;
[alias(_fstat32)]    _fstat32:($fd_t fd, [nonnull] struct __dos_stat32 *__restrict buf) -> int = _fstat?;
[alias(_fstat32i64)] _fstat32i64:($fd_t fd, [nonnull] struct __dos_stat32i64 *__restrict buf) -> int = _fstati64?;
[alias(_fstat64i32)] _fstat64i32:($fd_t fd, [nonnull] struct __dos_stat64i32 *__restrict buf) -> int = _fstat64?;
[alias(_fstat64i32)] _fstat64:($fd_t fd, [nonnull] struct __dos_stat64 *__restrict buf) -> int = _fstat64?;
[wchar]             _wstat32:([nonnull] $wchar_t const *filename, [nonnull] struct __dos_stat32 *buf) -> int;
[wchar]             _wstat64:([nonnull] $wchar_t const *filename, [nonnull] struct __dos_stat64 *buf) -> int;
[wchar]             _wstat32i64:([nonnull] $wchar_t const *filename, [nonnull] struct __dos_stat32i64 *buf) -> int;
[wchar]             _wstat64i32:([nonnull] $wchar_t const *filename, [nonnull] struct __dos_stat64i32 *buf) -> int;

%#endif /* __USE_DOS */


%{

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_KOS
#if defined(_WCHAR_H) && !defined(_PARTS_WCHAR_SYS_STAT_H)
#include <parts/wchar/sys/stat.h>
#endif
#endif /* __USE_KOS */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_SYS_STAT_H)
#include <parts/uchar/sys/stat.h>
#endif
#endif /* __USE_UTF */

}