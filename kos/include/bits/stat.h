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
#ifndef _BITS_STAT_H
#define _BITS_STAT_H 1

#include <__stdinc.h>
#include <features.h>
#include <bits/types.h>
#include <bits/timespec.h>

__SYSDECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("stat")
#ifdef __USE_LARGEFILE64
#pragma push_macro("stat64")
#endif /* __USE_LARGEFILE64 */
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#undef stat
#ifdef __USE_LARGEFILE64
#undef stat64
#endif /* __USE_LARGEFILE64 */

#define __S_IFMT           0170000 /* These bits determine file type. */
#define __S_IFDIR          0040000 /* Directory. */
#define __S_IFCHR          0020000 /* Character device. */
#define __S_IFBLK          0060000 /* Block device. */
#define __S_IFREG          0100000 /* Regular file. */
#define __S_IFIFO          0010000 /* FIFO. */
#define __S_IFLNK          0120000 /* Symbolic link. */
#define __S_IFSOCK         0140000 /* Socket. */

#define __S_ISDIR(x)  (((x)&__S_IFMT) == __S_IFDIR)
#define __S_ISCHR(x)  (((x)&__S_IFMT) == __S_IFCHR)
#define __S_ISBLK(x)  (((x)&__S_IFMT) == __S_IFBLK)
#define __S_ISREG(x)  (((x)&__S_IFMT) == __S_IFREG)
#define __S_ISFIFO(x) (((x)&__S_IFMT) == __S_IFIFO)
#define __S_ISLNK(x)  (((x)&__S_IFMT) == __S_IFLNK)
#define __S_ISDEV(x)  (((x)&0130000) == 0020000) /* __S_IFCHR|__S_IFBLK */

#define __S_TYPEISMQ(buf)  ((buf)->st_mode - (buf)->st_mode)
#define __S_TYPEISSEM(buf) ((buf)->st_mode - (buf)->st_mode)
#define __S_TYPEISSHM(buf) ((buf)->st_mode - (buf)->st_mode)

#define __S_ISUID  04000 /* Set user ID on execution. */
#define __S_ISGID  02000 /* Set group ID on execution. */
#define __S_ISVTX  01000 /* Save swapped text after use (sticky). */
#define __S_IREAD  00400 /* Read by owner. */
#define __S_IWRITE 00200 /* Write by owner. */
#define __S_IEXEC  00100 /* Execute by owner. */

#ifdef __USE_ATFILE
#define UTIME_NOW  ((1l << 30) - 1l)
#define UTIME_OMIT ((1l << 30) - 2l)
#endif /* __USE_ATFILE */

#undef _STATBUF_ST_TIM      /* .st_atim, .st_ctim, .st_mtim */
#undef _STATBUF_ST_TIME     /* .st_atime, .st_ctime, .st_mtime */
#undef _STATBUF_ST_NSEC     /* .st_atimensec, .st_ctimensec, .st_mtimensec */
#undef _STATBUF_ST_TIMESPEC /* .st_atimespec, .st_ctimespec, .st_mtimespec */
#undef _STATBUF_ST_BLKSIZE  /* .st_blksize */
#undef _STATBUF_ST_RDEV     /* .st_rdev */
#undef _STATBUF_ST_INO32    /* .st_ino32 */
#undef _STATBUF_ST_INO64    /* .st_ino64 */

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


#define __USE_ST_TIMESPEC_FIELDS 1

#if defined(__USE_XOPEN2K8) && defined(__USE_ST_TIMESPEC_FIELDS)
#ifdef __USE_TIME_BITS64
#ifdef __USE_KOS
#if __SIZEOF_SYSCALL_LONG_T__ > 4
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtim##32; struct { __time32_t st_xtime##32; __UINT32_TYPE__ __##st_xtime##_pad32; __syscall_ulong_t st_xtimensec##32; }; };
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim; struct __timespec64 st_xtimespec; struct { __time64_t st_xtime; __syscall_ulong_t st_xtimensec; }; \
	        struct __timespec64 st_xtim##64; struct { __time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64; }; };
#define __DEFINE_TIMESPEC64_NO32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim; struct __timespec64 st_xtimespec; struct { union { __time32_t st_xtime##32; __time64_t st_xtime; }; union { __syscall_ulong_t st_xtimensec##32; __syscall_ulong_t st_xtimensec; }; }; \
	        struct __timespec64 st_xtim##64; struct { __time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64; }; };
#else /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtim##32; struct { __time32_t st_xtime##32; __syscall_ulong_t st_xtimensec##32; }; };
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim; struct __timespec64 st_xtimespec; struct { __time64_t st_xtime; __syscall_ulong_t st_xtimensec; __UINT32_TYPE__ __##st_xtime##_pad; }; \
	        struct __timespec64 st_xtim##64; struct { __time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64; __UINT32_TYPE__ __##st_xtime##_pad64; }; };
#define __DEFINE_TIMESPEC64_NO32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim; struct __timespec64 st_xtimespec; struct { union { __time32_t st_xtime##32; __time64_t st_xtime; }; union { __syscall_ulong_t st_xtimensec##32; __syscall_ulong_t st_xtimensec; }; __UINT32_TYPE__ __##st_xtime##_pad; }; \
	        struct __timespec64 st_xtim##64; struct { __time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64; __UINT32_TYPE__ __##st_xtime##_pad64; }; };
#endif /* __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#else /* __USE_KOS */
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	struct __timespec32 __##st_xtim##32;
#if __SIZEOF_SYSCALL_LONG_T__ > 4
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim; struct __timespec64 st_xtimespec; struct { __time64_t st_xtime; __syscall_ulong_t st_xtimensec; }; };
#else /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim; struct __timespec64 st_xtimespec; struct { __time64_t st_xtime; __syscall_ulong_t st_xtimensec; __UINT32_TYPE__ __##st_xtime##_pad; }; };
#endif /* __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#define __DEFINE_TIMESPEC64_NO32 __DEFINE_TIMESPEC64
#endif /* !__USE_KOS */
#else /* __USE_TIME_BITS64 */
#ifdef __USE_KOS
#if __SIZEOF_SYSCALL_LONG_T__ > 4
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtim; struct __timespec32 st_xtimespec; struct { __time32_t st_xtime; __UINT32_TYPE__ __##st_xtime##_pad; __syscall_ulong_t st_xtimensec; }; \
	        struct __timespec32 st_xtim##32; struct { __time32_t st_xtime##32; __UINT32_TYPE__ __##st_xtime##_pad32; __syscall_ulong_t st_xtimensec##32; }; };
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim##64; struct { __time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64; }; };
#define __DEFINE_TIMESPEC64_NO32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim##64; struct { union { __time32_t st_xtime; __time32_t st_xtime##32; __time64_t st_xtime##64; }; union { __syscall_ulong_t st_xtimensec; __syscall_ulong_t st_xtimensec##32; __syscall_ulong_t st_xtimensec##64; }; }; };
#else /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtim; struct __timespec32 st_xtimespec; struct { __time32_t st_xtime; __syscall_ulong_t st_xtimensec; }; \
	        struct __timespec32 st_xtim##32; struct { __time32_t st_xtime##32; __syscall_ulong_t st_xtimensec##32; }; };
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim##64; struct { __time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64; __UINT32_TYPE__ __##st_xtime##_pad64; }; };
#define __DEFINE_TIMESPEC64_NO32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim##64; struct { union { __time32_t st_xtime; __time32_t st_xtime##32; __time64_t st_xtime##64; }; union { __syscall_ulong_t st_xtimensec; __syscall_ulong_t st_xtimensec##32; __syscall_ulong_t st_xtimensec##64; }; __UINT32_TYPE__ __##st_xtime##_pad64; }; };
#endif /* __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#else /* __USE_KOS */
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	struct __timespec64 __##st_xtim##64;
#if __SIZEOF_SYSCALL_LONG_T__ > 4
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtim; struct __timespec32 st_xtimespec; struct { __time32_t st_xtime; __UINT32_TYPE__ __##st_xtime##_pad; __syscall_ulong_t st_xtimensec; }; };
#define __DEFINE_TIMESPEC64_NO32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { __time32_t st_xtime; __time64_t __#st_xtime##64; }; __syscall_ulong_t st_xtimensec;
#else /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtim; struct __timespec32 st_xtimespec; struct { __time32_t st_xtime; __syscall_ulong_t st_xtimensec; }; };
#define __DEFINE_TIMESPEC64_NO32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { __time32_t st_xtime; __time64_t __##st_xtime##64; }; __syscall_ulong_t st_xtimensec; __UINT32_TYPE__ __##st_xtime##_pad64;
#endif /* __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#endif /* !__USE_KOS */
#endif /* !__USE_TIME_BITS64 */
#ifdef __USE_KOS
#if __SIZEOF_SYSCALL_LONG_T__ > 4
#define __DEFINE_TIMESPEC32_ALT(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	struct __timespec32 st_xtim##32;
#define __DEFINE_TIMESPEC64_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim; struct __timespec64 st_xtimespec; struct { union { __time32_t st_xtime##32; __time64_t st_xtime; }; union { __syscall_ulong_t st_xtimensec##32; __syscall_ulong_t st_xtimensec; }; }; \
	        struct __timespec64 st_xtim##64; struct { __time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64; }; };
#define __DEFINE_TIMESPEC32_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtim; struct __timespec32 st_xtimespec; struct { __time32_t st_xtime; __UINT32_TYPE__ __##st_xtime##_pad; __syscall_ulong_t st_xtimensec; }; \
	        struct __timespec32 st_xtim##32; struct { __time32_t st_xtime##32; __UINT32_TYPE__ __##st_xtime##_pad32; __syscall_ulong_t st_xtimensec##32; }; };
#else /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __DEFINE_TIMESPEC32_ALT(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	struct __timespec32 st_xtim##32;
#define __DEFINE_TIMESPEC64_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim; struct __timespec64 st_xtimespec; struct { union { __time32_t st_xtime##32; __time64_t st_xtime; }; union { __syscall_ulong_t st_xtimensec##32; __syscall_ulong_t st_xtimensec; }; __UINT32_TYPE__ __##st_xtime##_pad; }; \
	        struct __timespec64 st_xtim##64; struct { __time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64; __UINT32_TYPE__ __##st_xtime##_pad64; }; };
#define __DEFINE_TIMESPEC32_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtim; struct __timespec32 st_xtimespec; struct { __time32_t st_xtime; __syscall_ulong_t st_xtimensec; }; \
	        struct __timespec32 st_xtim##32; struct { __time32_t st_xtime##32; __syscall_ulong_t st_xtimensec##32; }; };
#endif /* __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#else /* __USE_KOS */
#define __DEFINE_TIMESPEC32_ALT(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	struct __timespec32 __##st_xtim##32;
#if __SIZEOF_SYSCALL_LONG_T__ > 4
#define __DEFINE_TIMESPEC64_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim; struct __timespec64 st_xtimespec; struct { __time64_t st_xtime; __syscall_ulong_t st_xtimensec; }; };
#define __DEFINE_TIMESPEC32_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtim; struct __timespec32 st_xtimespec; struct { __time32_t st_xtime; __UINT32_TYPE__ __##st_xtime##_pad; __syscall_ulong_t st_xtimensec; }; };
#else /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __DEFINE_TIMESPEC64_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim; struct __timespec64 st_xtimespec; struct { __time64_t st_xtime; __syscall_ulong_t st_xtimensec; __UINT32_TYPE__ __##st_xtime##_pad; }; };
#define __DEFINE_TIMESPEC32_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtim; struct __timespec32 st_xtimespec; struct { __time32_t st_xtime; __syscall_ulong_t st_xtimensec; }; };
#endif /* __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#endif /* !__USE_KOS */
#elif defined(__USE_ST_TIMESPEC_FIELDS)
#ifdef __USE_TIME_BITS64
#ifdef __USE_KOS
#if __SIZEOF_SYSCALL_LONG_T__ > 4
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	__time32_t st_xtime##32; __UINT32_TYPE__ __##st_xtime##_pad32; __syscall_ulong_t st_xtimensec##32;
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtimespec; struct { __time64_t st_xtime; __syscall_ulong_t st_xtimensec; }; \
	        struct { __time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64; }; };
#define __DEFINE_TIMESPEC64_NO32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtimespec; struct { union { __time32_t st_xtime##32; __time64_t st_xtime; }; union { __syscall_ulong_t st_xtimensec##32; __syscall_ulong_t st_xtimensec; }; }; \
	        struct { __time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64; }; };
#else /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	__time32_t st_xtime##32; __syscall_ulong_t st_xtimensec##32;
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtimespec; struct { __time64_t st_xtime; __syscall_ulong_t st_xtimensec; __UINT32_TYPE__ __##st_xtime##_pad; }; \
	        struct { __time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64; __UINT32_TYPE__ __##st_xtime##_pad64; }; };
#define __DEFINE_TIMESPEC64_NO32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtimespec; struct { union { __time32_t st_xtime##32; __time64_t st_xtime; }; union { __syscall_ulong_t st_xtimensec##32; __syscall_ulong_t st_xtimensec; }; __UINT32_TYPE__ __##st_xtime##_pad; }; \
	        struct { __time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64; __UINT32_TYPE__ __##st_xtime##_pad64; }; };
#endif /* __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#else /* __USE_KOS */
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	struct __timespec32 __##st_xtim##32;
#if __SIZEOF_SYSCALL_LONG_T__ > 4
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtimespec; struct { __time64_t st_xtime; __syscall_ulong_t st_xtimensec; }; };
#else /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtimespec; struct { __time64_t st_xtime; __syscall_ulong_t st_xtimensec; __UINT32_TYPE__ __##st_xtime##_pad; }; };
#endif /* __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#define __DEFINE_TIMESPEC64_NO32 __DEFINE_TIMESPEC64
#endif /* !__USE_KOS */
#else /* __USE_TIME_BITS64 */
#ifdef __USE_KOS
#if __SIZEOF_SYSCALL_LONG_T__ > 4
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtimespec; struct { __time32_t st_xtime; __UINT32_TYPE__ __##st_xtime##_pad; __syscall_ulong_t st_xtimensec; }; \
	        struct { __time32_t st_xtime##32; __UINT32_TYPE__ __##st_xtime##_pad32; __syscall_ulong_t st_xtimensec##32; }; };
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	__time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64;
#define __DEFINE_TIMESPEC64_NO32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { __time32_t st_xtime; __time32_t st_xtime##32; __time64_t st_xtime##64; }; \
	union { __syscall_ulong_t st_xtimensec; __syscall_ulong_t st_xtimensec##32; __syscall_ulong_t st_xtimensec##64; };
#else /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtimespec; struct { __time32_t st_xtime; __syscall_ulong_t st_xtimensec; }; \
	        struct { __time32_t st_xtime##32; __syscall_ulong_t st_xtimensec##32; }; };
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	__time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64; __UINT32_TYPE__ __##st_xtime##_pad64;
#define __DEFINE_TIMESPEC64_NO32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { __time32_t st_xtime; __time32_t st_xtime##32; __time64_t st_xtime##64; }; \
	union { __syscall_ulong_t st_xtimensec; __syscall_ulong_t st_xtimensec##32; __syscall_ulong_t st_xtimensec##64; }; \
	__UINT32_TYPE__ __##st_xtime##_pad64;
#endif /* __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#else /* __USE_KOS */
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	struct __timespec64 __##st_xtim##64;
#if __SIZEOF_SYSCALL_LONG_T__ > 4
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtimespec; struct { __time32_t st_xtime; __UINT32_TYPE__ __##st_xtime##_pad; __syscall_ulong_t st_xtimensec; }; };
#define __DEFINE_TIMESPEC64_NO32(st_xtim, st_xtime, st_xtimensec) \
	union { __time32_t st_xtime; __time64_t __#st_xtime##64; }; __syscall_ulong_t st_xtimensec;
#else /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtimespec; struct { __time32_t st_xtime; __syscall_ulong_t st_xtimensec; }; };
#define __DEFINE_TIMESPEC64_NO32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { __time32_t st_xtime; __time64_t __##st_xtime##64; }; __syscall_ulong_t st_xtimensec; __UINT32_TYPE__ __##st_xtime##_pad64;
#endif /* __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#endif /* !__USE_KOS */
#endif /* !__USE_TIME_BITS64 */
#ifdef __USE_KOS
#if __SIZEOF_SYSCALL_LONG_T__ > 4
#define __DEFINE_TIMESPEC32_ALT(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	struct __timespec32 st_xtim##32;
#define __DEFINE_TIMESPEC64_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtimespec; struct { union { __time32_t st_xtime##32; __time64_t st_xtime; }; union { __syscall_ulong_t st_xtimensec##32; __syscall_ulong_t st_xtimensec; }; }; \
	        struct { __time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64; }; };
#define __DEFINE_TIMESPEC32_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtimespec; struct { __time32_t st_xtime; __UINT32_TYPE__ __##st_xtime##_pad; __syscall_ulong_t st_xtimensec; }; \
	        struct { __time32_t st_xtime##32; __UINT32_TYPE__ __##st_xtime##_pad32; __syscall_ulong_t st_xtimensec##32; }; };
#else /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __DEFINE_TIMESPEC32_ALT(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	struct __timespec32 st_xtim##32;
#define __DEFINE_TIMESPEC64_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtimespec; struct { union { __time32_t st_xtime##32; __time64_t st_xtime; }; union { __syscall_ulong_t st_xtimensec##32; __syscall_ulong_t st_xtimensec; }; __UINT32_TYPE__ __##st_xtime##_pad; }; \
	        struct { __time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64; __UINT32_TYPE__ __##st_xtime##_pad64; }; };
#define __DEFINE_TIMESPEC32_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtimespec; struct { __time32_t st_xtime; __syscall_ulong_t st_xtimensec; }; \
	        struct { __time32_t st_xtime##32; __syscall_ulong_t st_xtimensec##32; }; };
#endif /* __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#else /* __USE_KOS */
#define __DEFINE_TIMESPEC32_ALT(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	struct __timespec32 __##st_xtim##32;
#if __SIZEOF_SYSCALL_LONG_T__ > 4
#define __DEFINE_TIMESPEC64_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtimespec; struct { __time64_t st_xtime; __syscall_ulong_t st_xtimensec; }; };
#define __DEFINE_TIMESPEC32_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtimespec; struct { __time32_t st_xtime; __UINT32_TYPE__ __##st_xtime##_pad; __syscall_ulong_t st_xtimensec; }; };
#else /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __DEFINE_TIMESPEC64_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtimespec; struct { __time64_t st_xtime; __syscall_ulong_t st_xtimensec; __UINT32_TYPE__ __##st_xtime##_pad; }; };
#define __DEFINE_TIMESPEC32_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtimespec; struct { __time32_t st_xtime; __syscall_ulong_t st_xtimensec; }; };
#endif /* __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#endif /* !__USE_KOS */
#elif defined(__USE_XOPEN2K8)
#ifdef __USE_TIME_BITS64
#ifdef __USE_KOS
#if __SIZEOF_SYSCALL_LONG_T__ > 4
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtim##32; struct { __time32_t st_xtime##32; __UINT32_TYPE__ __##st_xtime##_pad32; __syscall_ulong_t st_xtimensec##32; }; };
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim; struct { __time64_t st_xtime; __syscall_ulong_t st_xtimensec; }; \
	        struct __timespec64 st_xtim##64; struct { __time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64; }; };
#define __DEFINE_TIMESPEC64_NO32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim; struct { union { __time32_t st_xtime##32; __time64_t st_xtime; }; union { __syscall_ulong_t st_xtimensec##32; __syscall_ulong_t st_xtimensec; }; }; \
	        struct __timespec64 st_xtim##64; struct { __time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64; }; };
#else /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtim##32; struct { __time32_t st_xtime##32; __syscall_ulong_t st_xtimensec##32; }; };
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim; struct { __time64_t st_xtime; __syscall_ulong_t st_xtimensec; __UINT32_TYPE__ __##st_xtime##_pad; }; \
	        struct __timespec64 st_xtim##64; struct { __time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64; __UINT32_TYPE__ __##st_xtime##_pad64; }; };
#define __DEFINE_TIMESPEC64_NO32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim; struct { union { __time32_t st_xtime##32; __time64_t st_xtime; }; union { __syscall_ulong_t st_xtimensec##32; __syscall_ulong_t st_xtimensec; }; __UINT32_TYPE__ __##st_xtime##_pad; }; \
	        struct __timespec64 st_xtim##64; struct { __time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64; __UINT32_TYPE__ __##st_xtime##_pad64; }; };
#endif /* __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#else /* __USE_KOS */
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	struct __timespec32 __##st_xtim##32;
#if __SIZEOF_SYSCALL_LONG_T__ > 4
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim; struct { __time64_t st_xtime; __syscall_ulong_t st_xtimensec; }; };
#else /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim; struct { __time64_t st_xtime; __syscall_ulong_t st_xtimensec; __UINT32_TYPE__ __##st_xtime##_pad; }; };
#endif /* __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#define __DEFINE_TIMESPEC64_NO32 __DEFINE_TIMESPEC64
#endif /* !__USE_KOS */
#else /* __USE_TIME_BITS64 */
#ifdef __USE_KOS
#if __SIZEOF_SYSCALL_LONG_T__ > 4
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtim; struct { __time32_t st_xtime; __UINT32_TYPE__ __##st_xtime##_pad; __syscall_ulong_t st_xtimensec; }; \
	        struct __timespec32 st_xtim##32; struct { __time32_t st_xtime##32; __UINT32_TYPE__ __##st_xtime##_pad32; __syscall_ulong_t st_xtimensec##32; }; };
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim##64; struct { __time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64; }; };
#define __DEFINE_TIMESPEC64_NO32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim##64; struct { union { __time32_t st_xtime; __time32_t st_xtime##32; __time64_t st_xtime##64; }; union { __syscall_ulong_t st_xtimensec; __syscall_ulong_t st_xtimensec##32; __syscall_ulong_t st_xtimensec##64; }; }; };
#else /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtim; struct { __time32_t st_xtime; __syscall_ulong_t st_xtimensec; }; \
	        struct __timespec32 st_xtim##32; struct { __time32_t st_xtime##32; __syscall_ulong_t st_xtimensec##32; }; };
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim##64; struct { __time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64; __UINT32_TYPE__ __##st_xtime##_pad64; }; };
#define __DEFINE_TIMESPEC64_NO32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim##64; struct { union { __time32_t st_xtime; __time32_t st_xtime##32; __time64_t st_xtime##64; }; union { __syscall_ulong_t st_xtimensec; __syscall_ulong_t st_xtimensec##32; __syscall_ulong_t st_xtimensec##64; }; __UINT32_TYPE__ __##st_xtime##_pad64; }; };
#endif /* __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#else /* __USE_KOS */
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	struct __timespec64 __##st_xtim##64;
#if __SIZEOF_SYSCALL_LONG_T__ > 4
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtim; struct { __time32_t st_xtime; __UINT32_TYPE__ __##st_xtime##_pad; __syscall_ulong_t st_xtimensec; }; };
#define __DEFINE_TIMESPEC64_NO32(st_xtim, st_xtime, st_xtimensec) \
	union { __time32_t st_xtime; __time64_t __#st_xtime##64; }; __syscall_ulong_t st_xtimensec;
#else /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtim; struct { __time32_t st_xtime; __syscall_ulong_t st_xtimensec; }; };
#define __DEFINE_TIMESPEC64_NO32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { __time32_t st_xtime; __time64_t __##st_xtime##64; }; __syscall_ulong_t st_xtimensec; __UINT32_TYPE__ __##st_xtime##_pad64;
#endif /* __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#endif /* !__USE_KOS */
#endif /* !__USE_TIME_BITS64 */
#ifdef __USE_KOS
#if __SIZEOF_SYSCALL_LONG_T__ > 4
#define __DEFINE_TIMESPEC32_ALT(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	struct __timespec32 st_xtim##32;
#define __DEFINE_TIMESPEC64_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim; struct { union { __time32_t st_xtime##32; __time64_t st_xtime; }; union { __syscall_ulong_t st_xtimensec##32; __syscall_ulong_t st_xtimensec; }; }; \
	        struct __timespec64 st_xtim##64; struct { __time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64; }; };
#define __DEFINE_TIMESPEC32_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtim; struct { __time32_t st_xtime; __UINT32_TYPE__ __##st_xtime##_pad; __syscall_ulong_t st_xtimensec; }; \
	        struct __timespec32 st_xtim##32; struct { __time32_t st_xtime##32; __UINT32_TYPE__ __##st_xtime##_pad32; __syscall_ulong_t st_xtimensec##32; }; };
#else /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __DEFINE_TIMESPEC32_ALT(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	struct __timespec32 st_xtim##32;
#define __DEFINE_TIMESPEC64_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim; struct { union { __time32_t st_xtime##32; __time64_t st_xtime; }; union { __syscall_ulong_t st_xtimensec##32; __syscall_ulong_t st_xtimensec; }; __UINT32_TYPE__ __##st_xtime##_pad; }; \
	        struct __timespec64 st_xtim##64; struct { __time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64; __UINT32_TYPE__ __##st_xtime##_pad64; }; };
#define __DEFINE_TIMESPEC32_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtim; struct { __time32_t st_xtime; __syscall_ulong_t st_xtimensec; }; \
	        struct __timespec32 st_xtim##32; struct { __time32_t st_xtime##32; __syscall_ulong_t st_xtimensec##32; }; };
#endif /* __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#else /* __USE_KOS */
#define __DEFINE_TIMESPEC32_ALT(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	struct __timespec32 __##st_xtim##32;
#if __SIZEOF_SYSCALL_LONG_T__ > 4
#define __DEFINE_TIMESPEC64_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim; struct { __time64_t st_xtime; __syscall_ulong_t st_xtimensec; }; };
#define __DEFINE_TIMESPEC32_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtim; struct { __time32_t st_xtime; __UINT32_TYPE__ __##st_xtime##_pad; __syscall_ulong_t st_xtimensec; }; };
#else /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __DEFINE_TIMESPEC64_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec64 st_xtim; struct { __time64_t st_xtime; __syscall_ulong_t st_xtimensec; __UINT32_TYPE__ __##st_xtime##_pad; }; };
#define __DEFINE_TIMESPEC32_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct __timespec32 st_xtim; struct { __time32_t st_xtime; __syscall_ulong_t st_xtimensec; }; };
#endif /* __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#endif /* !__USE_KOS */
#else /* Fields... */
#ifdef __USE_TIME_BITS64
#ifdef __USE_KOS
#if __SIZEOF_SYSCALL_LONG_T__ > 4
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	__time32_t st_xtime##32; __UINT32_TYPE__ __##st_xtime##_pad32; __syscall_ulong_t st_xtimensec##32;
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct { __time64_t st_xtime; __syscall_ulong_t st_xtimensec; }; \
	        struct { __time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64; }; };
#else /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	__time32_t st_xtime##32; __syscall_ulong_t st_xtimensec##32;
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct { __time64_t st_xtime; __syscall_ulong_t st_xtimensec; __UINT32_TYPE__ __##st_xtime##_pad; }; \
	        struct { __time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64; __UINT32_TYPE__ __##st_xtime##_pad64; }; };
#endif /* __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#else /* __USE_KOS */
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	struct __timespec32 __##st_xtim##32;
#if __SIZEOF_SYSCALL_LONG_T__ > 4
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	__time64_t st_xtime; __syscall_ulong_t st_xtimensec;
#else /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	__time64_t st_xtime; __syscall_ulong_t st_xtimensec; __UINT32_TYPE__ __##st_xtime##_pad;
#endif /* __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#endif /* !__USE_KOS */
#else /* __USE_TIME_BITS64 */
#ifdef __USE_KOS
#if __SIZEOF_SYSCALL_LONG_T__ > 4
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct { __time32_t st_xtime; __UINT32_TYPE__ __##st_xtime##_pad; __syscall_ulong_t st_xtimensec; }; \
	        struct { __time32_t st_xtime##32; __UINT32_TYPE__ __##st_xtime##_pad32; __syscall_ulong_t st_xtimensec##32; }; };
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	__time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64;
#else /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct { __time32_t st_xtime; __syscall_ulong_t st_xtimensec; }; \
	        struct { __time32_t st_xtime##32; __syscall_ulong_t st_xtimensec##32; }; };
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	__time64_t st_xtime##64; __syscall_ulong_t st_xtimensec##64; __UINT32_TYPE__ __##st_xtime##_pad64;
#endif /* __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#else /* __USE_KOS */
#define __DEFINE_TIMESPEC64(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	struct __timespec64 __##st_xtim##64;
#if __SIZEOF_SYSCALL_LONG_T__ > 4
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	__time32_t st_xtime; __UINT32_TYPE__ __##st_xtime##_pad; __syscall_ulong_t st_xtimensec;
#else /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __DEFINE_TIMESPEC32(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	__time32_t st_xtime; __syscall_ulong_t st_xtimensec;
#endif /* __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#endif /* !__USE_KOS */
#endif /* !__USE_TIME_BITS64 */


#ifdef __USE_KOS
#if __SIZEOF_SYSCALL_LONG_T__ > 4
#define __DEFINE_TIMESPEC32_ALT(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	__time32_t __##st_xtime##32; __UINT32_TYPE__ __##st_xtime##_pad32; __syscall_ulong_t __##st_xtimensec##32;
#define __DEFINE_TIMESPEC64_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { __time64_t st_xtime; __time32_t st_xtime##32; __time64_t st_xtime##64; }; \
	union { __syscall_ulong_t st_xtimensec; __syscall_ulong_t st_xtimensec##32; __syscall_ulong_t st_xtimensec##64; };
#define __DEFINE_TIMESPEC32_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct { __time32_t st_xtime; __UINT32_TYPE__ __##st_xtime##_pad; __syscall_ulong_t st_xtimensec; }; \
	        struct { __time32_t st_xtime##32; __UINT32_TYPE__ __##st_xtime##_pad32; __syscall_ulong_t st_xtimensec##32; }; };
#else /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __DEFINE_TIMESPEC32_ALT(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	__time32_t __##st_xtime##32; __syscall_ulong_t __##st_xtimensec##32;
#define __DEFINE_TIMESPEC64_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { __time64_t st_xtime; __time32_t st_xtime##32; __time64_t st_xtime##64; }; \
	union { __syscall_ulong_t st_xtimensec; __syscall_ulong_t st_xtimensec##32; __syscall_ulong_t st_xtimensec##64; }; \
	__UINT32_TYPE__ __##st_xtime##_pad64;
#define __DEFINE_TIMESPEC32_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	union { struct { __time32_t st_xtime; __syscall_ulong_t st_xtimensec; }; \
	        struct { __time32_t st_xtime##32; __syscall_ulong_t st_xtimensec##32; }; };
#endif /* __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#else /* __USE_KOS */
#define __DEFINE_TIMESPEC32_ALT(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	struct __timespec32 __##st_xtim##32;
#if __SIZEOF_SYSCALL_LONG_T__ > 4
#define __DEFINE_TIMESPEC64_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	__time64_t st_xtime; __syscall_ulong_t st_xtimensec;
#define __DEFINE_TIMESPEC32_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	__time32_t st_xtime; __UINT32_TYPE__ __##st_xtime##_pad; __syscall_ulong_t st_xtimensec;
#else /* __SIZEOF_SYSCALL_LONG_T__ > 4 */
#define __DEFINE_TIMESPEC64_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	__time64_t st_xtime; __syscall_ulong_t st_xtimensec; __UINT32_TYPE__ __##st_xtime##_pad;
#define __DEFINE_TIMESPEC32_ONLY(st_xtim, st_xtimespec, st_xtime, st_xtimensec) \
	__time32_t st_xtime; __syscall_ulong_t st_xtimensec;
#endif /* __SIZEOF_SYSCALL_LONG_T__ <= 4 */
#endif /* !__USE_KOS */
#endif /* fields... */



#ifdef __CRT_DOS_PRIMARY

#define _STATBUF_ST_TIME 1 /* Always defined. */
#define _STATBUF_ST_RDEV 1
#ifdef __CC__
#ifndef __stat_defined
#define __stat_defined 1
struct stat {
	__dos_dev_t    st_dev;
	__dos_ino_t    st_ino;
	__uint16_t     st_mode;
	__int16_t      st_nlink;
	__int16_t      st_uid;
	__int16_t      st_gid;
	__int16_t    __st_pad0;
	__dos_dev_t    st_rdev;
#ifdef __USE_FILE_OFFSET64
#ifdef __USE_KOS
	union {
		__UINT64_TYPE__ st_size;
		__UINT64_TYPE__ st_size64;
		__UINT32_TYPE__ st_size32;
	};
#else /* __USE_KOS */
	__INT64_TYPE__ st_size;
#endif /* !__USE_KOS */
#elif defined(__USE_TIME_BITS64)
	__int32_t    __st_pad1;
	union { /* binary compatibility to `stat64i32' and `stat64'. */
#ifdef __USE_KOS
		__UINT32_TYPE__ st_size;
		__UINT32_TYPE__ st_size32;
#else /* __USE_KOS */
		__dos_off_t    st_size;
#endif /* !__USE_KOS */
		__INT64_TYPE__ __st_pad2;
	};
#elif defined(__USE_KOS)
	union {
		__UINT32_TYPE__ st_size;
		__UINT32_TYPE__ st_size32;
	};
#else
	__dos_off_t    st_size;
#endif
#ifdef __USE_KOS
#ifdef __USE_TIME_BITS64
	union { __time64_t st_atime; __time32_t st_atime32; __time64_t st_atime64; };
	union { __time64_t st_mtime; __time32_t st_mtime32; __time64_t st_mtime64; };
	union { __time64_t st_ctime; __time32_t st_ctime32; __time64_t st_ctime64; };
#else /* __USE_TIME_BITS64 */
	union { __time32_t st_atime; __time32_t st_atime32; };
	union { __time32_t st_mtime; __time32_t st_mtime32; };
	union { __time32_t st_ctime; __time32_t st_ctime32; };
#endif /* !__USE_TIME_BITS64 */
#else /* __USE_KOS */
	__TM_TYPE(time) st_atime;
	__TM_TYPE(time) st_mtime;
	__TM_TYPE(time) st_ctime;
#endif /* !__USE_KOS */
};
#endif /* !__stat_defined */
#ifdef __USE_LARGEFILE64
#ifndef __stat64_defined
#define __stat64_defined 1
struct stat64 {
	__dos_dev_t    st_dev;
	__dos_ino_t    st_ino;
	__uint16_t     st_mode;
	__int16_t      st_nlink;
	__int16_t      st_uid;
	__int16_t      st_gid;
	__int16_t    __st_pad0;
	__dos_dev_t    st_rdev;
#ifdef __USE_KOS
	union {
		__UINT64_TYPE__ st_size;
		__UINT64_TYPE__ st_size64;
		__UINT32_TYPE__ st_size32;
	};
#else /* __USE_KOS */
	__INT64_TYPE__ st_size;
#endif /* !__USE_KOS */
#ifdef __USE_KOS
	union { __TM_TYPE(time) st_atime; __time32_t st_atime32; };
	union { __TM_TYPE(time) st_mtime; __time32_t st_mtime32; };
	union { __TM_TYPE(time) st_ctime; __time32_t st_ctime32; };
#else /* __USE_KOS */
	__TM_TYPE(time) st_atime;
	__TM_TYPE(time) st_mtime;
	__TM_TYPE(time) st_ctime;
#endif /* !__USE_KOS */
};
#endif /* !__stat64_defined */
#endif /* __USE_LARGEFILE64 */
#endif /* __CC__ */

#elif defined(__CRT_KOS_PRIMARY)

/* Optional stat features. */
#ifdef __USE_XOPEN2K8
#define _STATBUF_ST_TIM      1
#endif /* __USE_XOPEN2K8 */
#ifdef __USE_ST_TIMESPEC_FIELDS
#define _STATBUF_ST_TIMESPEC 1 /* Apple extension? */
#endif /* __USE_ST_TIMESPEC_FIELDS */
#define _STATBUF_ST_TIME     1 /* Always defined. */
#define _STATBUF_ST_NSEC     1
#define _STATBUF_ST_BLKSIZE  1
#define _STATBUF_ST_RDEV     1
#ifdef __USE_KOS
#define _STATBUF_ST_INO32    1
#define _STATBUF_ST_INO64    1
#endif /* __USE_KOS */

#ifdef __CC__
#ifndef __stat_defined
#define __stat_defined 1
struct stat {
	__dev_t             st_dev;
	union {
		__FS_TYPE(ino)  st_ino;
#ifdef __USE_KOS
		__ino32_t       st_ino32;
		__ino64_t       st_ino64;
#else /* __USE_KOS */
		__ino64_t     __st_ino64;
#endif /* !__USE_KOS */
	};
	__mode_t            st_mode;
	__nlink_t           st_nlink;
	__uid_t             st_uid;
	__gid_t             st_gid;
	__dev_t             st_rdev;
	union {
		__FS_TYPE(pos)  st_size;
#ifdef __USE_KOS
		__pos32_t       st_size32;
		__pos64_t       st_size64;
#else /* __USE_KOS */
		__pos64_t     __st_size64;
#endif /* !__USE_KOS */
	};
	__blksize_t         st_blksize;
	union {
		__FS_TYPE(blkcnt) st_blocks;
#ifdef __USE_KOS
		__blkcnt32_t    st_blocks32;
		__blkcnt64_t    st_blocks64;
#else /* __USE_KOS */
		__blkcnt64_t  __st_blocks64;
#endif /* !__USE_KOS */
	};
	__DEFINE_TIMESPEC32(st_atim, st_atimespec, st_atime, st_atimensec)
	__DEFINE_TIMESPEC32(st_mtim, st_mtimespec, st_mtime, st_mtimensec)
	__DEFINE_TIMESPEC32(st_ctim, st_ctimespec, st_ctime, st_ctimensec)
	__DEFINE_TIMESPEC64(st_atim, st_atimespec, st_atime, st_atimensec)
	__DEFINE_TIMESPEC64(st_mtim, st_mtimespec, st_mtime, st_mtimensec)
	__DEFINE_TIMESPEC64(st_ctim, st_ctimespec, st_ctime, st_ctimensec)
};
#endif /* !__stat_defined */
#ifdef __USE_LARGEFILE64
#ifndef __stat64_defined
#define __stat64_defined 1
struct stat64 {
	__dev_t             st_dev;
#ifdef __USE_KOS
	union {
		__ino64_t       st_ino;
		__ino32_t       st_ino32;
		__ino64_t       st_ino64;
	};
#else /* __USE_KOS */
	__ino64_t           st_ino;
#endif /* !__USE_KOS */
	__mode_t            st_mode;
	__nlink_t           st_nlink;
	__uid_t             st_uid;
	__gid_t             st_gid;
	__dev_t             st_rdev;
#ifdef __USE_KOS
	union {
		__pos64_t       st_size;
		__pos32_t       st_size32;
		__pos64_t       st_size64;
	};
#else /* __USE_KOS */
	__pos64_t           st_size;
#endif /* !__USE_KOS */
	__blksize_t         st_blksize;
#ifdef __USE_KOS
	union {
		__blkcnt64_t    st_blocks;
		__blkcnt32_t    st_blocks32;
		__blkcnt64_t    st_blocks64;
	};
#else /* __USE_KOS */
	__blkcnt64_t        st_blocks;
#endif /* !__USE_KOS */
	__DEFINE_TIMESPEC32_ALT(st_atim, st_atimespec, st_atime, st_atimensec)
	__DEFINE_TIMESPEC32_ALT(st_mtim, st_mtimespec, st_mtime, st_mtimensec)
	__DEFINE_TIMESPEC32_ALT(st_ctim, st_ctimespec, st_ctime, st_ctimensec)
	__DEFINE_TIMESPEC64_ONLY(st_atim, st_atimespec, st_atime, st_atimensec)
	__DEFINE_TIMESPEC64_ONLY(st_mtim, st_mtimespec, st_mtime, st_mtimensec)
	__DEFINE_TIMESPEC64_ONLY(st_ctim, st_ctimespec, st_ctime, st_ctimensec)
};
#endif /* !__stat64_defined */
#endif /* __USE_LARGEFILE64 */
#endif /* __CC__ */

#elif defined(__CRT_GLC_PRIMARY)

#ifdef __USE_XOPEN2K8
#define _STATBUF_ST_TIM      1
#endif /* __USE_XOPEN2K8 */
#ifdef __USE_ST_TIMESPEC_FIELDS
#define _STATBUF_ST_TIMESPEC 1 /* Apple extension? */
#endif /* __USE_ST_TIMESPEC_FIELDS */
#define _STATBUF_ST_TIME     1 /* Always defined. */
#define _STATBUF_ST_NSEC     1
#define _STATBUF_ST_BLKSIZE  1
#define _STATBUF_ST_RDEV     1

#ifdef __CC__
#ifndef __stat_defined
#define __stat_defined 1
struct stat {
	/* +0  */ __UINT64_TYPE__   st_dev;
	/* +8  */ __UINT32_TYPE__ __pad0;
#if defined(__USE_KOS) && !defined(__USE_FILE_OFFSET64)
	union {
		/* +12 */ __UINT32_TYPE__   st_ino32;
		/* +12 */ __UINT32_TYPE__   st_ino;
	};
#elif defined(__USE_KOS)
	/* +12 */ __UINT32_TYPE__   st_ino32;
#elif defined(__USE_FILE_OFFSET64)
	/* +12 */ __UINT32_TYPE__ __st_ino32;
#else /* ... */
	/* +12 */ __UINT32_TYPE__   st_ino;
#endif /* !... */
	/* +16 */ __UINT32_TYPE__   st_mode;
	/* +20 */ __UINT32_TYPE__   st_nlink;
	/* +24 */ __UINT32_TYPE__   st_uid;
	/* +28 */ __UINT32_TYPE__   st_gid;
	/* +32 */ __UINT64_TYPE__   st_rdev;
	/* +40 */ __UINT32_TYPE__ __pad1;
#ifdef __USE_FILE_OFFSET64
#ifdef __USE_KOS
	union {
		/* +44 */ __UINT64_TYPE__   st_size;
		/* +44 */ __UINT32_TYPE__   st_size32;
		/* +44 */ __UINT64_TYPE__   st_size64;
	};
#else /* __USE_KOS */
	/* +44 */ __INT64_TYPE__    st_size;
#endif /* !__USE_KOS */
	/* +52 */ __INT32_TYPE__    st_blksize;
	/* +56 */ __INT64_TYPE__    st_blocks;
	/* +64 */ __DEFINE_TIMESPEC32_ONLY(st_atim, st_atimespec, st_atime, st_atimensec)
	/* +72 */ __DEFINE_TIMESPEC32_ONLY(st_mtim, st_mtimespec, st_mtime, st_mtimensec)
	/* +80 */ __DEFINE_TIMESPEC32_ONLY(st_ctim, st_ctimespec, st_ctime, st_ctimensec)
#ifdef __USE_KOS
	union {
		/* +88 */ __UINT64_TYPE__ st_ino;
		/* +88 */ __UINT64_TYPE__ st_ino64;
	};
#else /* __USE_KOS */
	/* +88 */ __UINT64_TYPE__   st_ino;
#endif /* !__USE_KOS */
#else /* __USE_FILE_OFFSET64 */
#ifdef __USE_KOS
	union {
		/* +44 */ __INT32_TYPE__    st_size;
		/* +44 */ __INT32_TYPE__    st_size32;
	};
#else
	/* +44 */ __INT32_TYPE__    st_size;
#endif
	/* +48 */ __INT32_TYPE__    st_blksize;
	/* +52 */ __INT32_TYPE__    st_blocks;
	/* +56 */ __DEFINE_TIMESPEC32_ONLY(st_atim, st_atimespec, st_atime, st_atimensec)
	/* +64 */ __DEFINE_TIMESPEC32_ONLY(st_mtim, st_mtimespec, st_mtime, st_mtimensec)
	/* +72 */ __DEFINE_TIMESPEC32_ONLY(st_ctim, st_ctimespec, st_ctime, st_ctimensec)
	/* +80 */ __UINT32_TYPE__ __pad2;
	/* +84 */ __UINT32_TYPE__ __pad3;
#endif /* !__USE_FILE_OFFSET64 */
};
#endif /* !__stat_defined */
#ifdef __USE_LARGEFILE64
#ifndef __stat64_defined
#define __stat64_defined 1
struct stat64 {
	/* +0  */ __UINT64_TYPE__   st_dev;
	/* +8  */ __UINT32_TYPE__ __pad0;
#ifdef __USE_KOS
	/* +12 */ __UINT32_TYPE__   st_ino32;
#else /* __USE_KOS */
	/* +12 */ __UINT32_TYPE__ __st_ino32;
#endif /* !__USE_KOS */
	/* +16 */ __UINT32_TYPE__   st_mode;
	/* +20 */ __UINT32_TYPE__   st_nlink;
	/* +24 */ __UINT32_TYPE__   st_uid;
	/* +28 */ __UINT32_TYPE__   st_gid;
	/* +32 */ __UINT64_TYPE__   st_rdev;
	/* +40 */ __UINT32_TYPE__ __pad1;
#ifdef __USE_KOS
	union {
		/* +44 */ __UINT64_TYPE__ st_size;
		/* +44 */ __UINT32_TYPE__ st_size32;
		/* +44 */ __UINT64_TYPE__ st_size64;
	};
#else /* __USE_KOS */
	/* +44 */ __INT64_TYPE__    st_size;
#endif /* !__USE_KOS */
	/* +52 */ __INT32_TYPE__    st_blksize;
	/* +56 */ __INT64_TYPE__    st_blocks;
	/* +64 */ __DEFINE_TIMESPEC32_ONLY(st_atim, st_atimespec, st_atime, st_atimensec)
	/* +72 */ __DEFINE_TIMESPEC32_ONLY(st_mtim, st_mtimespec, st_mtime, st_mtimensec)
	/* +80 */ __DEFINE_TIMESPEC32_ONLY(st_ctim, st_ctimespec, st_ctime, st_ctimensec)
#ifdef __USE_KOS
	union {
		/* +88 */ __UINT64_TYPE__ st_ino;
		/* +88 */ __UINT64_TYPE__ st_ino64;
	};
#else /* __USE_KOS */
	/* +88 */ __UINT64_TYPE__   st_ino;
#endif /* !__USE_KOS */
};
#endif /* !__stat64_defined */
#endif /* __USE_LARGEFILE64 */
#endif /* __CC__ */

#elif defined(__CRT_CYG_PRIMARY)

#ifdef __USE_TIME_BITS64
#ifdef __USE_XOPEN2K8
#define _STATBUF_ST_TIM      1
#endif /* __USE_XOPEN2K8 */
#ifdef __USE_ST_TIMESPEC_FIELDS
#define _STATBUF_ST_TIMESPEC 1 /* Apple extension? */
#endif /* __USE_ST_TIMESPEC_FIELDS */
#endif /* __USE_TIME_BITS64 */
#define _STATBUF_ST_TIME     1 /* Always defined. */
#define _STATBUF_ST_NSEC     1
#define _STATBUF_ST_BLKSIZE  1
#define _STATBUF_ST_RDEV     1

#ifdef __CC__
#ifndef __stat_defined
#define __stat_defined 1
struct stat {
	/* +0   */ __UINT32_TYPE__     st_dev;
	/* +4   */ __UINT32_TYPE__   __st_pad0;
#ifdef __USE_KOS
	union {
		/* +8   */ __UINT32_TYPE__ st_ino;
		/* +8   */ __UINT64_TYPE__ st_ino64;
		/* +8   */ __UINT32_TYPE__ st_ino32;
	};
#else /* __USE_KOS */
	/* +8   */ __UINT64_TYPE__     st_ino;
#endif /* !__USE_KOS */
	/* +16  */ __UINT32_TYPE__     st_mode;
	/* +20  */ __UINT16_TYPE__     st_nlink;
	/* +22  */ __UINT16_TYPE__   __st_pad1;
	/* +24  */ __UINT32_TYPE__     st_uid;
	/* +28  */ __UINT32_TYPE__     st_gid;
	/* +32  */ __UINT32_TYPE__     st_rdev;
	/* +36  */ __UINT32_TYPE__   __st_pad2;
#ifdef __USE_KOS
	union {
		/* +40  */ __UINT32_TYPE__ st_size;
		/* +40  */ __UINT64_TYPE__ st_size64;
		/* +40  */ __UINT32_TYPE__ st_size32;
	};
#else /* __USE_KOS */
	/* +40  */ __UINT32_TYPE__     st_size;
	/* +44  */ __UINT32_TYPE__   __st_padsize;
#endif /* !__USE_KOS */
	/* +48  */ __DEFINE_TIMESPEC64_NO32(st_atim, st_atimespec, st_atime, st_atimensec)
	/* +64  */ __DEFINE_TIMESPEC64_NO32(st_mtim, st_mtimespec, st_mtime, st_mtimensec)
	/* +80  */ __DEFINE_TIMESPEC64_NO32(st_ctim, st_ctimespec, st_ctime, st_ctimensec)
	/* +96  */ __UINT32_TYPE__     st_blksize;
	/* +100 */ __UINT32_TYPE__   __st_pad3;
#ifdef __USE_KOS
	union {
		/* +104 */ __UINT32_TYPE__ st_blocks;
		/* +104 */ __UINT64_TYPE__ st_blocks64;
		/* +104 */ __UINT32_TYPE__ st_blocks32;
	};
#else /* __USE_KOS */
	/* +104 */ __UINT32_TYPE__     st_blocks;
	/* +108 */ __UINT32_TYPE__   __st_padblocks;
#endif /* !__USE_KOS */
	/* +112 */ __DEFINE_TIMESPEC64_NO32(st_birthtim, st_birthtimespec, st_birthtime, st_birthtimensec)
};
#endif /* !__stat_defined */
#ifdef __USE_LARGEFILE64
#ifndef __stat64_defined
#define __stat64_defined 1
struct stat64 {
	/* +0   */ __UINT32_TYPE__     st_dev;
	/* +4   */ __UINT32_TYPE__   __st_pad0;
#ifdef __USE_KOS
	union {
		/* +8   */ __UINT64_TYPE__ st_ino;
		/* +8   */ __UINT64_TYPE__ st_ino64;
		/* +8   */ __UINT32_TYPE__ st_ino32;
	};
#else /* __USE_KOS */
	/* +8   */ __UINT64_TYPE__     st_ino;
#endif /* !__USE_KOS */
	/* +16  */ __UINT32_TYPE__     st_mode;
	/* +20  */ __UINT16_TYPE__     st_nlink;
	/* +22  */ __UINT16_TYPE__   __st_pad1;
	/* +24  */ __UINT32_TYPE__     st_uid;
	/* +28  */ __UINT32_TYPE__     st_gid;
	/* +32  */ __UINT32_TYPE__     st_rdev;
	/* +36  */ __UINT32_TYPE__   __st_pad2;
#ifdef __USE_KOS
	union {
		/* +40  */ __UINT64_TYPE__ st_size;
		/* +40  */ __UINT64_TYPE__ st_size64;
		/* +40  */ __UINT32_TYPE__ st_size32;
	};
#else /* __USE_KOS */
	/* +40  */ __UINT64_TYPE__     st_size;
#endif /* !__USE_KOS */
	/* +48  */ __DEFINE_TIMESPEC64_ONLY(st_atim, st_atimespec, st_atime, st_atimensec)
	/* +64  */ __DEFINE_TIMESPEC64_ONLY(st_mtim, st_mtimespec, st_mtime, st_mtimensec)
	/* +80  */ __DEFINE_TIMESPEC64_ONLY(st_ctim, st_ctimespec, st_ctime, st_ctimensec)
	/* +96  */ __UINT32_TYPE__     st_blksize;
	/* +100 */ __UINT32_TYPE__   __st_pad3;
#ifdef __USE_KOS
	union {
		/* +104 */ __UINT64_TYPE__ st_blocks;
		/* +104 */ __UINT64_TYPE__ st_blocks64;
		/* +104 */ __UINT32_TYPE__ st_blocks32;
	};
#else /* __USE_KOS */
	/* +104 */ __UINT64_TYPE__     st_blocks;
#endif /* !__USE_KOS */
	/* +112 */ __DEFINE_TIMESPEC64_ONLY(st_birthtim, st_birthtimespec, st_birthtime, st_birthtimensec)
};
#endif /* !__stat64_defined */
#endif /* __USE_LARGEFILE64 */
#endif /* __CC__ */

#elif defined(__CRT_GENERIC)

#define _STATBUF_ST_TIME     1 /* Always defined. */
#define _STATBUF_ST_BLKSIZE  1
#define _STATBUF_ST_RDEV     1
#ifdef __CC__
#ifndef __stat_defined
#define __stat_defined 1
struct stat {
#if defined(__CRT_HAVE_stat64)
	__dev_t           st_dev;     /* ID of device containing file */
	__FS_TYPE(ino)    st_ino;     /* inode number */
	__mode_t          st_mode;    /* protection */
	__nlink_t         st_nlink;   /* number of hard links */
	__uid_t           st_uid;     /* user ID of owner */
	__gid_t           st_gid;     /* group ID of owner */
	__dev_t           st_rdev;    /* device ID (if special file) */
	__FS_TYPE(off)    st_size;    /* total size, in bytes */
	__blksize_t       st_blksize; /* blocksize for file system I/O */
	__FS_TYPE(blkcnt) st_blocks;  /* number of 512B blocks allocated */
	__TM_TYPE(time)   st_atime;   /* time of last access */
	__TM_TYPE(time)   st_mtime;   /* time of last modification */
	__TM_TYPE(time)   st_ctime;   /* time of last status change */
#else /* 64-bit support */
	__dev_t           st_dev;     /* ID of device containing file */
	__ino32_t         st_ino;     /* inode number */
	__mode_t          st_mode;    /* protection */
	__nlink_t         st_nlink;   /* number of hard links */
	__uid_t           st_uid;     /* user ID of owner */
	__gid_t           st_gid;     /* group ID of owner */
	__dev_t           st_rdev;    /* device ID (if special file) */
	__off32_t         st_size;    /* total size, in bytes */
	__blksize_t       st_blksize; /* blocksize for file system I/O */
	__blkcnt32_t      st_blocks;  /* number of 512B blocks allocated */
	__time32_t        st_atime;   /* time of last access */
	__time32_t        st_mtime;   /* time of last modification */
	__time32_t        st_ctime;   /* time of last status change */
#endif /* no 64-bit support */
};
#endif /* !__stat_defined */
#ifdef __USE_LARGEFILE64
#ifndef __stat64_defined
#define __stat64_defined 1
struct stat64 {
	__dev_t           st_dev;     /* ID of device containing file */
	__ino64_t         st_ino;     /* inode number */
	__mode_t          st_mode;    /* protection */
	__nlink_t         st_nlink;   /* number of hard links */
	__uid_t           st_uid;     /* user ID of owner */
	__gid_t           st_gid;     /* group ID of owner */
	__dev_t           st_rdev;    /* device ID (if special file) */
	__off64_t         st_size;    /* total size, in bytes */
	__blksize_t       st_blksize; /* blocksize for file system I/O */
	__blkcnt64_t      st_blocks;  /* number of 512B blocks allocated */
	__time64_t        st_atime;   /* time of last access */
	__time64_t        st_mtime;   /* time of last modification */
	__time64_t        st_ctime;   /* time of last status change */
};
#endif /* !__stat64_defined */
#endif /* __USE_LARGEFILE64 */
#endif /* __CC__ */


#endif /* Generic... */


#undef __DEFINE_TIMESPEC64
#undef __DEFINE_TIMESPEC64_ONLY
#undef __DEFINE_TIMESPEC64_NO32
#undef __DEFINE_TIMESPEC32
#undef __DEFINE_TIMESPEC32_ALT
#undef __DEFINE_TIMESPEC32_ONLY




#ifdef __CC__
#ifdef __DEFINE_DOS_STAT_STRUCTURES
#undef __DEFINE_DOS_STAT_STRUCTURES
struct __dos_stat32 {
	__dos_dev_t    st_dev;
	__dos_ino_t    st_ino;
	__uint16_t     st_mode;
	__int16_t      st_nlink;
	__int16_t      st_uid;
	__int16_t      st_gid;
	__int16_t    __st_pad0;
	__dos_dev_t    st_rdev;
#ifdef __USE_KOS
	union {
		__UINT32_TYPE__ st_size;
		__UINT32_TYPE__ st_size32;
	};
	union { __time32_t st_atime; __time32_t st_atime32; };
	union { __time32_t st_mtime; __time32_t st_mtime32; };
	union { __time32_t st_ctime; __time32_t st_ctime32; };
#else /* __USE_KOS */
	__dos_off_t    st_size;
	__time32_t     st_atime;
	__time32_t     st_mtime;
	__time32_t     st_ctime;
#endif /* !__USE_KOS */
};
struct __dos_stat32i64 {
	__dos_dev_t    st_dev;
	__dos_ino_t    st_ino;
	__uint16_t     st_mode;
	__int16_t      st_nlink;
	__int16_t      st_uid;
	__int16_t      st_gid;
	__int16_t    __st_pad0;
	__dos_dev_t    st_rdev;
	__int32_t    __st_pad1;
#ifdef __USE_KOS
	union {
		__UINT64_TYPE__ st_size;
		__UINT32_TYPE__ st_size32;
		__UINT64_TYPE__ st_size64;
	};
	union { __time32_t st_atime; __time32_t st_atime32; };
	union { __time32_t st_mtime; __time32_t st_mtime32; };
	union { __time32_t st_ctime; __time32_t st_ctime32; };
#else /* __USE_KOS */
	__INT64_TYPE__ st_size;
	__time32_t     st_atime;
	__time32_t     st_mtime;
	__time32_t     st_ctime;
#endif /* !__USE_KOS */
	__int32_t    __st_pad2;
};
struct __dos_stat64i32 {
	__dos_dev_t    st_dev;
	__dos_ino_t    st_ino;
	__uint16_t     st_mode;
	__int16_t      st_nlink;
	__int16_t      st_uid;
	__int16_t      st_gid;
	__int16_t    __st_pad0;
	__dos_dev_t    st_rdev;
	__int32_t    __st_pad1;
#ifdef __USE_KOS
	union {
		__UINT32_TYPE__ st_size;
		__UINT32_TYPE__ st_size32;
		__INT64_TYPE__ __st_pad2; /* This is what DOS silently does to match the
		                           * binary layout of `stat64i32' with `stat64'. */
	};
	union { __time64_t st_atime; __time64_t st_atime32; __time64_t st_atime64; };
	union { __time64_t st_mtime; __time64_t st_mtime32; __time64_t st_mtime64; };
	union { __time64_t st_ctime; __time64_t st_ctime32; __time64_t st_ctime64; };
#else /* __USE_KOS */
	union {
		__dos_off_t    st_size;
		__INT64_TYPE__ __st_pad2; /* This is what DOS silently does to match the
		                           * binary layout of `stat64i32' with `stat64'. */
	};
	__time64_t     st_atime;
	__time64_t     st_mtime;
	__time64_t     st_ctime;
#endif /* !__USE_KOS */
};
struct __dos_stat64 {
	__dos_dev_t    st_dev;
	__dos_ino_t    st_ino;
	__uint16_t     st_mode;
	__int16_t      st_nlink;
	__int16_t      st_uid;
	__int16_t      st_gid;
	__int16_t    __st_pad0;
	__dos_dev_t    st_rdev;
	__int32_t    __st_pad1;
#ifdef __USE_KOS
	union {
		__UINT64_TYPE__ st_size;
		__UINT32_TYPE__ st_size32;
		__UINT64_TYPE__ st_size64;
	};
	union { __time64_t st_atime; __time64_t st_atime32; __time64_t st_atime64; };
	union { __time64_t st_mtime; __time64_t st_mtime32; __time64_t st_mtime64; };
	union { __time64_t st_ctime; __time64_t st_ctime32; __time64_t st_ctime64; };
#else /* __USE_KOS */
	__INT64_TYPE__ st_size;
	__time64_t     st_atime;
	__time64_t     st_mtime;
	__time64_t     st_ctime;
#endif /* !__USE_KOS */
};
#endif /* __DEFINE_DOS_STAT_STRUCTURES */

#ifdef __DEFINE_KOS_STAT_STRUCTURES
#undef __DEFINE_KOS_STAT_STRUCTURES
struct __kos_stat {
	__dev_t             st_dev;
	union {
		__ino32_t       st_ino32;
		__ino64_t       st_ino64;
	};
	__mode_t            st_mode;
	__nlink_t           st_nlink;
	__uid_t             st_uid;
	__gid_t             st_gid;
	__dev_t             st_rdev;
	union {
		__pos32_t       st_size32;
		__pos64_t       st_size64;
	};
	__blksize_t         st_blksize;
	union {
		__blkcnt32_t    st_blocks32;
		__blkcnt64_t    st_blocks64;
	};
	struct __timespec32 st_atim32;
	struct __timespec32 st_mtim32;
	struct __timespec32 st_ctim32;
	struct __timespec64 st_atim64;
	struct __timespec64 st_mtim64;
	struct __timespec64 st_ctim64;
};
#endif /* __DEFINE_KOS_STAT_STRUCTURES */

#ifdef __DEFINE_GLC_STAT_STRUCTURES
#undef __DEFINE_GLC_STAT_STRUCTURES
struct __glc_stat {
	/* +0  */ __UINT64_TYPE__   st_dev;
	/* +8  */ __UINT32_TYPE__ __st_pad0;
	/* +12 */ __UINT32_TYPE__   st_ino;
	/* +16 */ __UINT32_TYPE__   st_mode;
	/* +20 */ __UINT32_TYPE__   st_nlink;
	/* +24 */ __UINT32_TYPE__   st_uid;
	/* +28 */ __UINT32_TYPE__   st_gid;
	/* +32 */ __UINT64_TYPE__   st_rdev;
	/* +40 */ __UINT32_TYPE__ __st_pad1;
#ifdef __USE_KOS
	/* +44 */ __UINT32_TYPE__   st_size;
	/* +48 */ __UINT32_TYPE__   st_blksize;
	/* +52 */ __UINT32_TYPE__   st_blocks;
#else /* __USE_KOS */
	/* +44 */ __INT32_TYPE__    st_size;
	/* +48 */ __INT32_TYPE__    st_blksize;
	/* +52 */ __INT32_TYPE__    st_blocks;
#endif /* !__USE_KOS */
	/* +56 */ struct __timespec32 st_atim;
	/* +64 */ struct __timespec32 st_mtim;
	/* +72 */ struct __timespec32 st_ctim;
	/* +80 */ __UINT32_TYPE__ __st_pad2;
	/* +84 */ __UINT32_TYPE__ __st_pad3;
};
struct __glc_stat64 {
	/* +0  */ __UINT64_TYPE__   st_dev;
	/* +8  */ __UINT32_TYPE__ __st_pad0;
	/* +12 */ __UINT32_TYPE__   st_ino32;
	/* +16 */ __UINT32_TYPE__   st_mode;
	/* +20 */ __UINT32_TYPE__   st_nlink;
	/* +24 */ __UINT32_TYPE__   st_uid;
	/* +28 */ __UINT32_TYPE__   st_gid;
	/* +32 */ __UINT64_TYPE__   st_rdev;
	/* +40 */ __UINT32_TYPE__ __st_pad1;
#ifdef __USE_KOS
	/* +44 */ __UINT64_TYPE__   st_size64;
	/* +52 */ __UINT32_TYPE__   st_blksize;
	/* +56 */ __UINT64_TYPE__   st_blocks;
#else
	/* +44 */ __INT64_TYPE__    st_size64;
	/* +52 */ __INT32_TYPE__    st_blksize;
	/* +56 */ __INT64_TYPE__    st_blocks;
#endif
	/* +64 */ struct __timespec32 st_atim;
	/* +72 */ struct __timespec32 st_mtim;
	/* +80 */ struct __timespec32 st_ctim;
	/* +88 */ __UINT64_TYPE__   st_ino64;
};
#endif /* __DEFINE_GLC_STAT_STRUCTURES */

#ifdef __DEFINE_CYG_STAT_STRUCTURES
#undef __DEFINE_CYG_STAT_STRUCTURES
struct __cyg_stat {
	/* +0   */ __UINT32_TYPE__     st_dev;
	/* +4   */ __UINT32_TYPE__   __st_pad0;
	/* +8   */ __UINT64_TYPE__     st_ino;
	/* +16  */ __UINT32_TYPE__     st_mode;
	/* +20  */ __UINT16_TYPE__     st_nlink;
	/* +22  */ __UINT16_TYPE__   __st_pad1;
	/* +24  */ __UINT32_TYPE__     st_uid;
	/* +28  */ __UINT32_TYPE__     st_gid;
	/* +32  */ __UINT32_TYPE__     st_rdev;
	/* +36  */ __UINT32_TYPE__   __st_pad2;
	/* +40  */ __UINT64_TYPE__     st_size;
	/* +48  */ struct __timespec64 st_atim;
	/* +64  */ struct __timespec64 st_mtim;
	/* +80  */ struct __timespec64 st_ctim;
	/* +96  */ __UINT32_TYPE__     st_blksize;
	/* +100 */ __UINT32_TYPE__   __st_pad3;
	/* +104 */ __UINT64_TYPE__     st_blocks;
	/* +112 */ struct __timespec64 st_birthtim;
};
#endif /* __DEFINE_CYG_STAT_STRUCTURES */

#ifdef __DEFINE_GEN_STAT_STRUCTURES
#undef __DEFINE_GEN_STAT_STRUCTURES
struct __gen_stat {
#if defined(__CRT_HAVE_stat64)
	__dev_t           st_dev;     /* ID of device containing file */
	__FS_TYPE(ino)    st_ino;     /* inode number */
	__mode_t          st_mode;    /* protection */
	__nlink_t         st_nlink;   /* number of hard links */
	__uid_t           st_uid;     /* user ID of owner */
	__gid_t           st_gid;     /* group ID of owner */
	__dev_t           st_rdev;    /* device ID (if special file) */
	__FS_TYPE(off)    st_size;    /* total size, in bytes */
	__blksize_t       st_blksize; /* blocksize for file system I/O */
	__FS_TYPE(blkcnt) st_blocks;  /* number of 512B blocks allocated */
	__TM_TYPE(time)   st_atime;   /* time of last access */
	__TM_TYPE(time)   st_mtime;   /* time of last modification */
	__TM_TYPE(time)   st_ctime;   /* time of last status change */
#else /* 64-bit support */
	__dev_t           st_dev;     /* ID of device containing file */
	__ino32_t         st_ino;     /* inode number */
	__mode_t          st_mode;    /* protection */
	__nlink_t         st_nlink;   /* number of hard links */
	__uid_t           st_uid;     /* user ID of owner */
	__gid_t           st_gid;     /* group ID of owner */
	__dev_t           st_rdev;    /* device ID (if special file) */
	__off32_t         st_size;    /* total size, in bytes */
	__blksize_t       st_blksize; /* blocksize for file system I/O */
	__blkcnt32_t      st_blocks;  /* number of 512B blocks allocated */
	__time32_t        st_atime;   /* time of last access */
	__time32_t        st_mtime;   /* time of last modification */
	__time32_t        st_ctime;   /* time of last status change */
#endif /* no 64-bit support */
};
#endif /* __DEFINE_GEN_STAT_STRUCTURES */


#endif /* __CC__ */


__SYSDECL_END

#endif /* !_BITS_STAT_H */
