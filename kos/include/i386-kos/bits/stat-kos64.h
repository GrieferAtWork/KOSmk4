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
#ifndef _I386_KOS_BITS_STAT_KOS64_H
#define _I386_KOS_BITS_STAT_KOS64_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <bits/timespec64.h>
#include <bits/types.h>

#ifdef __x86_64__
#define __kos_stat __kos_statx64
#endif /* __x86_64__ */

#if defined(__KOS__) && defined(__x86_64__)
#ifndef __stat_defined
#define __stat_defined 1
#define __kos_statx64 stat
#define __OFFSET_STAT_DEV           __OFFSET_KOS_STATX64_DEV
#define __OFFSET_STAT_INO           __OFFSET_KOS_STATX64_INO
#define __OFFSET_STAT_MODE          __OFFSET_KOS_STATX64_MODE
#define __OFFSET_STAT_NLINK         __OFFSET_KOS_STATX64_NLINK
#define __OFFSET_STAT_UID           __OFFSET_KOS_STATX64_UID
#define __OFFSET_STAT_GID           __OFFSET_KOS_STATX64_GID
#define __OFFSET_STAT_RDEV          __OFFSET_KOS_STATX64_RDEV
#define __OFFSET_STAT_SIZE          __OFFSET_KOS_STATX64_SIZE
#define __OFFSET_STAT_BLKSIZE       __OFFSET_KOS_STATX64_BLKSIZE
#define __OFFSET_STAT_BLOCKS        __OFFSET_KOS_STATX64_BLOCKS
#define __OFFSET_STAT_ATIMESPEC32   __OFFSET_KOS_STATX64_ATIMESPEC32
#define __OFFSET_STAT_ATIME32       __OFFSET_KOS_STATX64_ATIME32
#define __OFFSET_STAT_ATIMENSEC32   __OFFSET_KOS_STATX64_ATIMENSEC32
#define __OFFSET_STAT_MTIMESPEC32   __OFFSET_KOS_STATX64_MTIMESPEC32
#define __OFFSET_STAT_MTIME32       __OFFSET_KOS_STATX64_MTIME32
#define __OFFSET_STAT_MTIMENSEC32   __OFFSET_KOS_STATX64_MTIMENSEC32
#define __OFFSET_STAT_CTIMESPEC32   __OFFSET_KOS_STATX64_CTIMESPEC32
#define __OFFSET_STAT_CTIME32       __OFFSET_KOS_STATX64_CTIME32
#define __OFFSET_STAT_CTIMENSEC32   __OFFSET_KOS_STATX64_CTIMENSEC32
#define __OFFSET_STAT_ATIMESPEC64   __OFFSET_KOS_STATX64_ATIMESPEC64
#define __OFFSET_STAT_ATIME64       __OFFSET_KOS_STATX64_ATIME64
#define __OFFSET_STAT_ATIMENSEC64   __OFFSET_KOS_STATX64_ATIMENSEC64
#define __OFFSET_STAT_MTIMESPEC64   __OFFSET_KOS_STATX64_MTIMESPEC64
#define __OFFSET_STAT_MTIME64       __OFFSET_KOS_STATX64_MTIME64
#define __OFFSET_STAT_MTIMENSEC64   __OFFSET_KOS_STATX64_MTIMENSEC64
#define __OFFSET_STAT_CTIMESPEC64   __OFFSET_KOS_STATX64_CTIMESPEC64
#define __OFFSET_STAT_CTIME64       __OFFSET_KOS_STATX64_CTIME64
#define __OFFSET_STAT_CTIMENSEC64   __OFFSET_KOS_STATX64_CTIMENSEC64
#define __OFFSET_STAT_ATIMESPEC     __OFFSET_KOS_STATX64_ATIMESPEC
#define __OFFSET_STAT_ATIME         __OFFSET_KOS_STATX64_ATIME
#define __OFFSET_STAT_ATIMENSEC     __OFFSET_KOS_STATX64_ATIMENSEC
#define __OFFSET_STAT_MTIMESPEC     __OFFSET_KOS_STATX64_MTIMESPEC
#define __OFFSET_STAT_MTIME         __OFFSET_KOS_STATX64_MTIME
#define __OFFSET_STAT_MTIMENSEC     __OFFSET_KOS_STATX64_MTIMENSEC
#define __OFFSET_STAT_CTIMESPEC     __OFFSET_KOS_STATX64_CTIMESPEC
#define __OFFSET_STAT_CTIME         __OFFSET_KOS_STATX64_CTIME
#define __OFFSET_STAT_CTIMENSEC     __OFFSET_KOS_STATX64_CTIMENSEC
#define __SIZEOF_STAT               __SIZEOF_KOS_STATX64

/* Define macros for available stat features. */
#ifdef __USE_XOPEN2K8
#define _STATBUF_ST_TIM      1
#endif /* __USE_XOPEN2K8 */
#define _STATBUF_ST_TIMESPEC 1 /* Apple extension? */
#define _STATBUF_ST_TIME     1 /* Always defined. */
#define _STATBUF_ST_NSEC     1
#define _STATBUF_ST_BLKSIZE  1
#define _STATBUF_ST_RDEV     1
#if defined(__USE_KOS) && !(defined(__KERNEL__) && defined(__KOS__))
#define _STATBUF_ST_INO32      1
#define _STATBUF_ST_INO64      1
#define _STATBUF_ST_SIZE32     1
#define _STATBUF_ST_SIZE64     1
#define _STATBUF_ST_BLOCKS32   1
#define _STATBUF_ST_BLOCKS64   1
#ifdef __USE_XOPEN2K8
#define _STATBUF_ST_TIM32      1
#define _STATBUF_ST_TIM64      1
#endif /* __USE_XOPEN2K8 */
#define _STATBUF_ST_TIMESPEC32 1
#define _STATBUF_ST_TIMESPEC64 1
#define _STATBUF_ST_TIME32     1
#define _STATBUF_ST_TIME64     1
#define _STATBUF_ST_NSEC32     1
#define _STATBUF_ST_NSEC64     1
#endif /* __USE_KOS && !(__KERNEL__ && __KOS__) */
#endif /* !__stat_defined */

/* Even though `struct stat64' is the same as `struct stat', we can't
 * simply `#define stat64 stat' because there function definitions using
 * the same name in <sys/stat.h>... */
#ifdef __USE_LARGEFILE64
#ifndef __stat64_defined
#define __stat64_defined 1
#define __kos_statx64_alias64 stat64
#define __OFFSET_STAT64_DEV         __OFFSET_KOS_STATX64_DEV
#define __OFFSET_STAT64_INO         __OFFSET_KOS_STATX64_INO
#define __OFFSET_STAT64_MODE        __OFFSET_KOS_STATX64_MODE
#define __OFFSET_STAT64_NLINK       __OFFSET_KOS_STATX64_NLINK
#define __OFFSET_STAT64_UID         __OFFSET_KOS_STATX64_UID
#define __OFFSET_STAT64_GID         __OFFSET_KOS_STATX64_GID
#define __OFFSET_STAT64_RDEV        __OFFSET_KOS_STATX64_RDEV
#define __OFFSET_STAT64_SIZE        __OFFSET_KOS_STATX64_SIZE
#define __OFFSET_STAT64_BLKSIZE     __OFFSET_KOS_STATX64_BLKSIZE
#define __OFFSET_STAT64_BLOCKS      __OFFSET_KOS_STATX64_BLOCKS
#define __OFFSET_STAT64_ATIMESPEC32 __OFFSET_KOS_STATX64_ATIMESPEC
#define __OFFSET_STAT64_ATIME32     __OFFSET_KOS_STATX64_ATIME
#define __OFFSET_STAT64_ATIMENSEC32 __OFFSET_KOS_STATX64_ATIMENSEC
#define __OFFSET_STAT64_MTIMESPEC32 __OFFSET_KOS_STATX64_MTIMESPEC
#define __OFFSET_STAT64_MTIME32     __OFFSET_KOS_STATX64_MTIME
#define __OFFSET_STAT64_MTIMENSEC32 __OFFSET_KOS_STATX64_MTIMENSEC
#define __OFFSET_STAT64_CTIMESPEC32 __OFFSET_KOS_STATX64_CTIMESPEC
#define __OFFSET_STAT64_CTIME32     __OFFSET_KOS_STATX64_CTIME
#define __OFFSET_STAT64_CTIMENSEC32 __OFFSET_KOS_STATX64_CTIMENSEC
#define __OFFSET_STAT64_ATIMESPEC64 __OFFSET_KOS_STATX64_ATIMESPEC
#define __OFFSET_STAT64_ATIME64     __OFFSET_KOS_STATX64_ATIME
#define __OFFSET_STAT64_ATIMENSEC64 __OFFSET_KOS_STATX64_ATIMENSEC
#define __OFFSET_STAT64_MTIMESPEC64 __OFFSET_KOS_STATX64_MTIMESPEC
#define __OFFSET_STAT64_MTIME64     __OFFSET_KOS_STATX64_MTIME
#define __OFFSET_STAT64_MTIMENSEC64 __OFFSET_KOS_STATX64_MTIMENSEC
#define __OFFSET_STAT64_CTIMESPEC64 __OFFSET_KOS_STATX64_CTIMESPEC
#define __OFFSET_STAT64_CTIME64     __OFFSET_KOS_STATX64_CTIME
#define __OFFSET_STAT64_CTIMENSEC64 __OFFSET_KOS_STATX64_CTIMENSEC
#define __OFFSET_STAT64_ATIMESPEC   __OFFSET_KOS_STATX64_ATIMESPEC
#define __OFFSET_STAT64_ATIME       __OFFSET_KOS_STATX64_ATIME
#define __OFFSET_STAT64_ATIMENSEC   __OFFSET_KOS_STATX64_ATIMENSEC
#define __OFFSET_STAT64_MTIMESPEC   __OFFSET_KOS_STATX64_MTIMESPEC
#define __OFFSET_STAT64_MTIME       __OFFSET_KOS_STATX64_MTIME
#define __OFFSET_STAT64_MTIMENSEC   __OFFSET_KOS_STATX64_MTIMENSEC
#define __OFFSET_STAT64_CTIMESPEC   __OFFSET_KOS_STATX64_CTIMESPEC
#define __OFFSET_STAT64_CTIME       __OFFSET_KOS_STATX64_CTIME
#define __OFFSET_STAT64_CTIMENSEC   __OFFSET_KOS_STATX64_CTIMENSEC
#define __SIZEOF_STAT64             __SIZEOF_KOS_STATX64
#endif /* !__stat64_defined */
#endif /* __USE_LARGEFILE64 */

#endif /* __KOS__ && __x86_64__ */


#define __OFFSET_KOS_STATX64_DEV          0
#define __OFFSET_KOS_STATX64_INO          8
#define __OFFSET_KOS_STATX64_MODE         16
#define __OFFSET_KOS_STATX64_NLINK        20
#define __OFFSET_KOS_STATX64_UID          24
#define __OFFSET_KOS_STATX64_GID          28
#define __OFFSET_KOS_STATX64_RDEV         32
#define __OFFSET_KOS_STATX64_SIZE         40
#define __OFFSET_KOS_STATX64_BLKSIZE      48
#define __OFFSET_KOS_STATX64_BLOCKS       56
#define __OFFSET_KOS_STATX64_ATIMESPEC    64
#define __OFFSET_KOS_STATX64_ATIME        64
#define __OFFSET_KOS_STATX64_ATIMENSEC    72
#define __OFFSET_KOS_STATX64_MTIMESPEC    80
#define __OFFSET_KOS_STATX64_MTIME        80
#define __OFFSET_KOS_STATX64_MTIMENSEC    88
#define __OFFSET_KOS_STATX64_CTIMESPEC    96
#define __OFFSET_KOS_STATX64_CTIME        96
#define __OFFSET_KOS_STATX64_CTIMENSEC    104
#define __SIZEOF_KOS_STATX64              112

#ifdef __CC__
__DECL_BEGIN

#if defined(__USE_KOS) && !(defined(__KERNEL__) && defined(__KOS__))
#define __FS_INT64_FIELD(name, T) \
	union {                       \
		T name;                   \
		T name##32;               \
		T name##64;               \
	}
#else /* __USE_KOS && !(__KERNEL__ && __KOS__) */
#define __FS_INT64_FIELD(name, T) T name
#endif /* !__USE_KOS || (__KERNEL__ && __KOS__) */

struct __kos_statx64 /*[PREFIX(st_)]*/ {
	__UINT64_TYPE__  st_dev;
	__FS_INT64_FIELD(st_ino, __ULONG64_TYPE__);
	__UINT32_TYPE__  st_mode;
	__ULONG32_TYPE__ st_nlink;
	__UINT32_TYPE__  st_uid;
	__UINT32_TYPE__  st_gid;
	__UINT64_TYPE__  st_rdev;
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
	__FS_INT64_FIELD(st_size, __ULONG64_TYPE__);
	__ULONG64_TYPE__ st_blksize;
	__FS_INT64_FIELD(st_blocks, __ULONG64_TYPE__);
#else /* __USE_KOS || __USE_KOS_KERNEL */
	__FS_INT64_FIELD(st_size, __LONG64_TYPE__);
	__LONG64_TYPE__  st_blksize;
	__FS_INT64_FIELD(st_blocks, __LONG64_TYPE__);
#endif /* !__USE_KOS && !__USE_KOS_KERNEL */
	union {
#ifdef __USE_XOPEN2K8
		struct __timespecx64 st_atim;
#endif /* __USE_XOPEN2K8 */
		struct __timespecx64 st_atimespec;
		struct {
			__INT64_TYPE__  st_atime;
			__UINT64_TYPE__ st_atimensec;
		};
#if defined(__USE_KOS) && !(defined(__KERNEL__) && defined(__KOS__))
#ifdef __USE_XOPEN2K8
		struct __timespecx64 st_atim32;
		struct __timespecx64 st_atim64;
#endif /* __USE_XOPEN2K8 */
		struct __timespecx64 st_atimespec32;
		struct __timespecx64 st_atimespec64;
		struct {
			__INT64_TYPE__  st_atime32;
			__UINT64_TYPE__ st_atimensec32;
		};
		struct {
			__INT64_TYPE__  st_atime64;
			__UINT64_TYPE__ st_atimensec64;
		};
#endif /* __USE_KOS && !(__KERNEL__ && __KOS__) */
	};
	union {
#ifdef __USE_XOPEN2K8
		struct __timespecx64 st_mtim;
#endif /* __USE_XOPEN2K8 */
		struct __timespecx64 st_mtimespec;
		struct {
			__INT64_TYPE__  st_mtime;
			__UINT64_TYPE__ st_mtimensec;
		};
#if defined(__USE_KOS) && !(defined(__KERNEL__) && defined(__KOS__))
#ifdef __USE_XOPEN2K8
		struct __timespecx64 st_mtim32;
		struct __timespecx64 st_mtim64;
#endif /* __USE_XOPEN2K8 */
		struct __timespecx64 st_mtimespec32;
		struct __timespecx64 st_mtimespec64;
		struct {
			__INT64_TYPE__  st_mtime32;
			__UINT64_TYPE__ st_mtimensec32;
		};
		struct {
			__INT64_TYPE__  st_mtime64;
			__UINT64_TYPE__ st_mtimensec64;
		};
#endif /* __USE_KOS && !(__KERNEL__ && __KOS__) */
	};
	union {
#ifdef __USE_XOPEN2K8
		struct __timespecx64 st_ctim;
#endif /* __USE_XOPEN2K8 */
		struct __timespecx64 st_ctimespec;
		struct {
			__INT64_TYPE__  st_ctime;
			__UINT64_TYPE__ st_ctimensec;
		};
#if defined(__USE_KOS) && !(defined(__KERNEL__) && defined(__KOS__))
#ifdef __USE_XOPEN2K8
		struct __timespecx64 st_ctim32;
		struct __timespecx64 st_ctim64;
#endif /* __USE_XOPEN2K8 */
		struct __timespecx64 st_ctimespec32;
		struct __timespecx64 st_ctimespec64;
		struct {
			__INT64_TYPE__  st_ctime32;
			__UINT64_TYPE__ st_ctimensec32;
		};
		struct {
			__INT64_TYPE__  st_ctime64;
			__UINT64_TYPE__ st_ctimensec64;
		};
#endif /* __USE_KOS && !(__KERNEL__ && __KOS__) */
	};
};

#ifdef __kos_statx64_alias64
struct __kos_statx64_alias64 /*[PREFIX(st_)]*/ {
	__UINT64_TYPE__  st_dev;
	__FS_INT64_FIELD(st_ino, __ULONG64_TYPE__);
	__UINT32_TYPE__  st_mode;
	__ULONG32_TYPE__ st_nlink;
	__UINT32_TYPE__  st_uid;
	__UINT32_TYPE__  st_gid;
	__UINT64_TYPE__  st_rdev;
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
	__FS_INT64_FIELD(st_size, __ULONG64_TYPE__);
	__ULONG64_TYPE__ st_blksize;
	__FS_INT64_FIELD(st_blocks, __ULONG64_TYPE__);
#else /* __USE_KOS || __USE_KOS_KERNEL */
	__FS_INT64_FIELD(st_size, __LONG64_TYPE__);
	__LONG64_TYPE__  st_blksize;
	__FS_INT64_FIELD(st_blocks, __LONG64_TYPE__);
#endif /* !__USE_KOS && !__USE_KOS_KERNEL */
	union {
#ifdef __USE_XOPEN2K8
		struct __timespecx64 st_atim;
#endif /* __USE_XOPEN2K8 */
		struct __timespecx64 st_atimespec;
		struct {
			__INT64_TYPE__  st_atime;
			__UINT64_TYPE__ st_atimensec;
		};
#if defined(__USE_KOS) && !(defined(__KERNEL__) && defined(__KOS__))
#ifdef __USE_XOPEN2K8
		struct __timespecx64 st_atim32;
		struct __timespecx64 st_atim64;
#endif /* __USE_XOPEN2K8 */
		struct __timespecx64 st_atimespec32;
		struct __timespecx64 st_atimespec64;
		struct {
			__INT64_TYPE__  st_atime32;
			__UINT64_TYPE__ st_atimensec32;
		};
		struct {
			__INT64_TYPE__  st_atime64;
			__UINT64_TYPE__ st_atimensec64;
		};
#endif /* __USE_KOS && !(__KERNEL__ && __KOS__) */
	};
	union {
#ifdef __USE_XOPEN2K8
		struct __timespecx64 st_mtim;
#endif /* __USE_XOPEN2K8 */
		struct __timespecx64 st_mtimespec;
		struct {
			__INT64_TYPE__  st_mtime;
			__UINT64_TYPE__ st_mtimensec;
		};
#if defined(__USE_KOS) && !(defined(__KERNEL__) && defined(__KOS__))
#ifdef __USE_XOPEN2K8
		struct __timespecx64 st_mtim32;
		struct __timespecx64 st_mtim64;
#endif /* __USE_XOPEN2K8 */
		struct __timespecx64 st_mtimespec32;
		struct __timespecx64 st_mtimespec64;
		struct {
			__INT64_TYPE__  st_mtime32;
			__UINT64_TYPE__ st_mtimensec32;
		};
		struct {
			__INT64_TYPE__  st_mtime64;
			__UINT64_TYPE__ st_mtimensec64;
		};
#endif /* __USE_KOS && !(__KERNEL__ && __KOS__) */
	};
	union {
#ifdef __USE_XOPEN2K8
		struct __timespecx64 st_ctim;
#endif /* __USE_XOPEN2K8 */
		struct __timespecx64 st_ctimespec;
		struct {
			__INT64_TYPE__  st_ctime;
			__UINT64_TYPE__ st_ctimensec;
		};
#if defined(__USE_KOS) && !(defined(__KERNEL__) && defined(__KOS__))
#ifdef __USE_XOPEN2K8
		struct __timespecx64 st_ctim32;
		struct __timespecx64 st_ctim64;
#endif /* __USE_XOPEN2K8 */
		struct __timespecx64 st_ctimespec32;
		struct __timespecx64 st_ctimespec64;
		struct {
			__INT64_TYPE__  st_ctime32;
			__UINT64_TYPE__ st_ctimensec32;
		};
		struct {
			__INT64_TYPE__  st_ctime64;
			__UINT64_TYPE__ st_ctimensec64;
		};
#endif /* __USE_KOS && !(__KERNEL__ && __KOS__) */
	};
};
#endif /* __kos_statx64_alias64 */

#undef __FS_INT64_FIELD
__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_BITS_STAT_KOS64_H */
