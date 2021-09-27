/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_OS_KOS_STAT_H
#define _BITS_OS_KOS_STAT_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/os/timespec.h>
#include <bits/types.h>

#ifndef __WANT_FULL_STRUCT_STAT
#if !defined(__KERNEL__) || !defined(__KOS__)
#define __WANT_FULL_STRUCT_STAT 1
#endif /* !__KERNEL__ || !__KOS__ */
#endif /* !__WANT_FULL_STRUCT_STAT */

#ifdef __KOS__
#define __kos_stat                  stat
#define __OFFSET_STAT_DEV           __OFFSET_KOS_STAT_DEV
#define __OFFSET_STAT_INO           __OFFSET_KOS_STAT_INO
#define __OFFSET_STAT_MODE          __OFFSET_KOS_STAT_MODE
#define __OFFSET_STAT_NLINK         __OFFSET_KOS_STAT_NLINK
#define __OFFSET_STAT_UID           __OFFSET_KOS_STAT_UID
#define __OFFSET_STAT_GID           __OFFSET_KOS_STAT_GID
#define __OFFSET_STAT_RDEV          __OFFSET_KOS_STAT_RDEV
#define __OFFSET_STAT_SIZE          __OFFSET_KOS_STAT_SIZE
#define __OFFSET_STAT_BLKSIZE       __OFFSET_KOS_STAT_BLKSIZE
#define __OFFSET_STAT_BLOCKS        __OFFSET_KOS_STAT_BLOCKS
#define __OFFSET_STAT_ATIMESPEC32   __OFFSET_KOS_STAT_ATIMESPEC32
#define __OFFSET_STAT_ATIME32       __OFFSET_KOS_STAT_ATIME32
#define __OFFSET_STAT_ATIMENSEC32   __OFFSET_KOS_STAT_ATIMENSEC32
#define __OFFSET_STAT_MTIMESPEC32   __OFFSET_KOS_STAT_MTIMESPEC32
#define __OFFSET_STAT_MTIME32       __OFFSET_KOS_STAT_MTIME32
#define __OFFSET_STAT_MTIMENSEC32   __OFFSET_KOS_STAT_MTIMENSEC32
#define __OFFSET_STAT_CTIMESPEC32   __OFFSET_KOS_STAT_CTIMESPEC32
#define __OFFSET_STAT_CTIME32       __OFFSET_KOS_STAT_CTIME32
#define __OFFSET_STAT_CTIMENSEC32   __OFFSET_KOS_STAT_CTIMENSEC32
#define __OFFSET_STAT_ATIMESPEC64   __OFFSET_KOS_STAT_ATIMESPEC64
#define __OFFSET_STAT_ATIME64       __OFFSET_KOS_STAT_ATIME64
#define __OFFSET_STAT_ATIMENSEC64   __OFFSET_KOS_STAT_ATIMENSEC64
#define __OFFSET_STAT_MTIMESPEC64   __OFFSET_KOS_STAT_MTIMESPEC64
#define __OFFSET_STAT_MTIME64       __OFFSET_KOS_STAT_MTIME64
#define __OFFSET_STAT_MTIMENSEC64   __OFFSET_KOS_STAT_MTIMENSEC64
#define __OFFSET_STAT_CTIMESPEC64   __OFFSET_KOS_STAT_CTIMESPEC64
#define __OFFSET_STAT_CTIME64       __OFFSET_KOS_STAT_CTIME64
#define __OFFSET_STAT_CTIMENSEC64   __OFFSET_KOS_STAT_CTIMENSEC64
#define __OFFSET_STAT_ATIMESPEC     __OFFSET_KOS_STAT_ATIMESPEC
#define __OFFSET_STAT_ATIME         __OFFSET_KOS_STAT_ATIME
#define __OFFSET_STAT_ATIMENSEC     __OFFSET_KOS_STAT_ATIMENSEC
#define __OFFSET_STAT_MTIMESPEC     __OFFSET_KOS_STAT_MTIMESPEC
#define __OFFSET_STAT_MTIME         __OFFSET_KOS_STAT_MTIME
#define __OFFSET_STAT_MTIMENSEC     __OFFSET_KOS_STAT_MTIMENSEC
#define __OFFSET_STAT_CTIMESPEC     __OFFSET_KOS_STAT_CTIMESPEC
#define __OFFSET_STAT_CTIME         __OFFSET_KOS_STAT_CTIME
#define __OFFSET_STAT_CTIMENSEC     __OFFSET_KOS_STAT_CTIMENSEC
#define __SIZEOF_STAT               __SIZEOF_KOS_STAT

/* Even though `struct stat64'  is the same  as `struct stat', we  can't
 * simply `#define stat64 stat' because there function definitions using
 * the same name in <sys/stat.h>... */
#ifdef __USE_LARGEFILE64
#undef __kos_stat_alias64
#define __kos_stat_alias64 stat64
#define __OFFSET_STAT64_DEV         __OFFSET_KOS_STAT_DEV
#define __OFFSET_STAT64_INO         __OFFSET_KOS_STAT_INO
#define __OFFSET_STAT64_MODE        __OFFSET_KOS_STAT_MODE
#define __OFFSET_STAT64_NLINK       __OFFSET_KOS_STAT_NLINK
#define __OFFSET_STAT64_UID         __OFFSET_KOS_STAT_UID
#define __OFFSET_STAT64_GID         __OFFSET_KOS_STAT_GID
#define __OFFSET_STAT64_RDEV        __OFFSET_KOS_STAT_RDEV
#define __OFFSET_STAT64_SIZE        __OFFSET_KOS_STAT_SIZE
#define __OFFSET_STAT64_BLKSIZE     __OFFSET_KOS_STAT_BLKSIZE
#define __OFFSET_STAT64_BLOCKS      __OFFSET_KOS_STAT_BLOCKS
#define __OFFSET_STAT64_ATIMESPEC32 __OFFSET_KOS_STAT_ATIMESPEC32
#define __OFFSET_STAT64_ATIME32     __OFFSET_KOS_STAT_ATIME32
#define __OFFSET_STAT64_ATIMENSEC32 __OFFSET_KOS_STAT_ATIMENSEC32
#define __OFFSET_STAT64_MTIMESPEC32 __OFFSET_KOS_STAT_MTIMESPEC32
#define __OFFSET_STAT64_MTIME32     __OFFSET_KOS_STAT_MTIME32
#define __OFFSET_STAT64_MTIMENSEC32 __OFFSET_KOS_STAT_MTIMENSEC32
#define __OFFSET_STAT64_CTIMESPEC32 __OFFSET_KOS_STAT_CTIMESPEC32
#define __OFFSET_STAT64_CTIME32     __OFFSET_KOS_STAT_CTIME32
#define __OFFSET_STAT64_CTIMENSEC32 __OFFSET_KOS_STAT_CTIMENSEC32
#define __OFFSET_STAT64_ATIMESPEC64 __OFFSET_KOS_STAT_ATIMESPEC64
#define __OFFSET_STAT64_ATIME64     __OFFSET_KOS_STAT_ATIME64
#define __OFFSET_STAT64_ATIMENSEC64 __OFFSET_KOS_STAT_ATIMENSEC64
#define __OFFSET_STAT64_MTIMESPEC64 __OFFSET_KOS_STAT_MTIMESPEC64
#define __OFFSET_STAT64_MTIME64     __OFFSET_KOS_STAT_MTIME64
#define __OFFSET_STAT64_MTIMENSEC64 __OFFSET_KOS_STAT_MTIMENSEC64
#define __OFFSET_STAT64_CTIMESPEC64 __OFFSET_KOS_STAT_CTIMESPEC64
#define __OFFSET_STAT64_CTIME64     __OFFSET_KOS_STAT_CTIME64
#define __OFFSET_STAT64_CTIMENSEC64 __OFFSET_KOS_STAT_CTIMENSEC64
#define __OFFSET_STAT64_ATIMESPEC   __OFFSET_KOS_STAT_ATIMESPEC
#define __OFFSET_STAT64_ATIME       __OFFSET_KOS_STAT_ATIME
#define __OFFSET_STAT64_ATIMENSEC   __OFFSET_KOS_STAT_ATIMENSEC
#define __OFFSET_STAT64_MTIMESPEC   __OFFSET_KOS_STAT_MTIMESPEC
#define __OFFSET_STAT64_MTIME       __OFFSET_KOS_STAT_MTIME
#define __OFFSET_STAT64_MTIMENSEC   __OFFSET_KOS_STAT_MTIMENSEC
#define __OFFSET_STAT64_CTIMESPEC   __OFFSET_KOS_STAT_CTIMESPEC
#define __OFFSET_STAT64_CTIME       __OFFSET_KOS_STAT_CTIME
#define __OFFSET_STAT64_CTIMENSEC   __OFFSET_KOS_STAT_CTIMENSEC
#define __SIZEOF_STAT64             __SIZEOF_KOS_STAT
#endif /* __USE_LARGEFILE64 */

/* Define macros for available stat features. */
#ifdef __USE_XOPEN2K8
#define _STATBUF_ST_TIM      1
#endif /* __USE_XOPEN2K8 */
#define _STATBUF_ST_TIMESPEC 1 /* Apple extension? */
#define _STATBUF_ST_TIME     1 /* Always defined. */
#define _STATBUF_ST_NSEC     1
#define _STATBUF_ST_BLKSIZE  1
#define _STATBUF_ST_RDEV     1
#define _STATBUF_ST_BLOCKS   1
#if defined(__USE_KOS) && defined(__WANT_FULL_STRUCT_STAT)
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
#endif /* __USE_KOS && __WANT_FULL_STRUCT_STAT */

#endif /* __KOS__ */


#define __OFFSET_KOS_STAT_DEV          0
#define __OFFSET_KOS_STAT_INO          __SIZEOF_DEV_T__
#define __OFFSET_KOS_STAT_MODE         (__SIZEOF_DEV_T__ + __SIZEOF_INO64_T__)
#define __OFFSET_KOS_STAT_NLINK        (__SIZEOF_DEV_T__ + __SIZEOF_INO64_T__ + __SIZEOF_MODE_T__)
#define __OFFSET_KOS_STAT_UID          (__SIZEOF_DEV_T__ + __SIZEOF_INO64_T__ + __SIZEOF_MODE_T__ + __SIZEOF_NLINK_T__)
#define __OFFSET_KOS_STAT_GID          (__SIZEOF_DEV_T__ + __SIZEOF_INO64_T__ + __SIZEOF_MODE_T__ + __SIZEOF_NLINK_T__ + __SIZEOF_UID_T__)
#define __OFFSET_KOS_STAT_RDEV         (__SIZEOF_DEV_T__ + __SIZEOF_INO64_T__ + __SIZEOF_MODE_T__ + __SIZEOF_NLINK_T__ + __SIZEOF_UID_T__ + __SIZEOF_GID_T__)
#define __OFFSET_KOS_STAT_SIZE         (2 * __SIZEOF_DEV_T__ + __SIZEOF_INO64_T__ + __SIZEOF_MODE_T__ + __SIZEOF_NLINK_T__ + __SIZEOF_UID_T__ + __SIZEOF_GID_T__)
#define __OFFSET_KOS_STAT_BLKSIZE      (2 * __SIZEOF_DEV_T__ + __SIZEOF_INO64_T__ + __SIZEOF_MODE_T__ + __SIZEOF_NLINK_T__ + __SIZEOF_UID_T__ + __SIZEOF_GID_T__ + __SIZEOF_OFF64_T__)
#define __OFFSET_KOS_STAT_BLOCKS       (2 * __SIZEOF_DEV_T__ + __SIZEOF_INO64_T__ + __SIZEOF_MODE_T__ + __SIZEOF_NLINK_T__ + __SIZEOF_UID_T__ + __SIZEOF_GID_T__ + 2 * __SIZEOF_OFF64_T__)
#define __OFFSET_KOS_STAT_ATIMESPEC32  (2 * __SIZEOF_DEV_T__ + __SIZEOF_INO64_T__ + __SIZEOF_MODE_T__ + __SIZEOF_NLINK_T__ + __SIZEOF_UID_T__ + __SIZEOF_GID_T__ + 2 * __SIZEOF_OFF64_T__ + __SIZEOF_BLKCNT64_T__)
#define __OFFSET_KOS_STAT_MTIMESPEC32  (__OFFSET_KOS_STAT_ATIMESPEC32 + __SIZEOF_TIMESPEC32)
#define __OFFSET_KOS_STAT_CTIMESPEC32  (__OFFSET_KOS_STAT_ATIMESPEC32 + __SIZEOF_TIMESPEC32 * 2)
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define __SIZEOF_KOS_STAT              (__OFFSET_KOS_STAT_ATIMESPEC32 + __SIZEOF_TIMESPEC32 * 3 + __SIZEOF_TIMESPEC64 * 3)
#define __OFFSET_KOS_STAT_ATIMESPEC64  __OFFSET_KOS_STAT_ATIMESPEC32
#define __OFFSET_KOS_STAT_MTIMESPEC64  __OFFSET_KOS_STAT_MTIMESPEC32
#define __OFFSET_KOS_STAT_CTIMESPEC64  __OFFSET_KOS_STAT_CTIMESPEC32
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#define __OFFSET_KOS_STAT_ATIMESPEC64  (__OFFSET_KOS_STAT_ATIMESPEC32 + __SIZEOF_TIMESPEC32 * 3)
#define __OFFSET_KOS_STAT_MTIMESPEC64  (__OFFSET_KOS_STAT_ATIMESPEC32 + __SIZEOF_TIMESPEC32 * 3 + __SIZEOF_TIMESPEC64)
#define __OFFSET_KOS_STAT_CTIMESPEC64  (__OFFSET_KOS_STAT_ATIMESPEC32 + __SIZEOF_TIMESPEC32 * 3 + __SIZEOF_TIMESPEC64 * 2)
#define __SIZEOF_KOS_STAT              (__OFFSET_KOS_STAT_ATIMESPEC32 + __SIZEOF_TIMESPEC32 * 3 + __SIZEOF_TIMESPEC64 * 3)
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#define __OFFSET_KOS_STAT_ATIME32      (__OFFSET_KOS_STAT_ATIMESPEC32 + __OFFSET_TIMESPEC32_SEC)
#define __OFFSET_KOS_STAT_ATIMENSEC32  (__OFFSET_KOS_STAT_ATIMESPEC32 + __OFFSET_TIMESPEC32_NSEC)
#define __OFFSET_KOS_STAT_MTIME32      (__OFFSET_KOS_STAT_MTIMESPEC32 + __OFFSET_TIMESPEC32_SEC)
#define __OFFSET_KOS_STAT_MTIMENSEC32  (__OFFSET_KOS_STAT_MTIMESPEC32 + __OFFSET_TIMESPEC32_NSEC)
#define __OFFSET_KOS_STAT_CTIME32      (__OFFSET_KOS_STAT_CTIMESPEC32 + __OFFSET_TIMESPEC32_SEC)
#define __OFFSET_KOS_STAT_CTIMENSEC32  (__OFFSET_KOS_STAT_CTIMESPEC32 + __OFFSET_TIMESPEC32_NSEC)
#define __OFFSET_KOS_STAT_ATIME64      (__OFFSET_KOS_STAT_ATIMESPEC64 + __OFFSET_TIMESPEC32_SEC)
#define __OFFSET_KOS_STAT_ATIMENSEC64  (__OFFSET_KOS_STAT_ATIMESPEC64 + __OFFSET_TIMESPEC32_NSEC)
#define __OFFSET_KOS_STAT_MTIME64      (__OFFSET_KOS_STAT_MTIMESPEC64 + __OFFSET_TIMESPEC32_SEC)
#define __OFFSET_KOS_STAT_MTIMENSEC64  (__OFFSET_KOS_STAT_MTIMESPEC64 + __OFFSET_TIMESPEC32_NSEC)
#define __OFFSET_KOS_STAT_CTIME64      (__OFFSET_KOS_STAT_CTIMESPEC64 + __OFFSET_TIMESPEC32_SEC)
#define __OFFSET_KOS_STAT_CTIMENSEC64  (__OFFSET_KOS_STAT_CTIMESPEC64 + __OFFSET_TIMESPEC32_NSEC)
#if defined(__USE_TIME_BITS64) || (defined(__KERNEL__) && defined(__KOS__))
#define __OFFSET_KOS_STAT_ATIMESPEC    __OFFSET_KOS_STAT_ATIMESPEC64
#define __OFFSET_KOS_STAT_ATIME        __OFFSET_KOS_STAT_ATIME64
#define __OFFSET_KOS_STAT_ATIMENSEC    __OFFSET_KOS_STAT_ATIMENSEC64
#define __OFFSET_KOS_STAT_MTIMESPEC    __OFFSET_KOS_STAT_MTIMESPEC64
#define __OFFSET_KOS_STAT_MTIME        __OFFSET_KOS_STAT_MTIME64
#define __OFFSET_KOS_STAT_MTIMENSEC    __OFFSET_KOS_STAT_MTIMENSEC64
#define __OFFSET_KOS_STAT_CTIMESPEC    __OFFSET_KOS_STAT_CTIMESPEC64
#define __OFFSET_KOS_STAT_CTIME        __OFFSET_KOS_STAT_CTIME64
#define __OFFSET_KOS_STAT_CTIMENSEC    __OFFSET_KOS_STAT_CTIMENSEC64
#else /* __USE_TIME_BITS64 || (__KERNEL__ && __KOS__) */
#define __OFFSET_KOS_STAT_ATIMESPEC    __OFFSET_KOS_STAT_ATIMESPEC32
#define __OFFSET_KOS_STAT_ATIME        __OFFSET_KOS_STAT_ATIME32
#define __OFFSET_KOS_STAT_ATIMENSEC    __OFFSET_KOS_STAT_ATIMENSEC32
#define __OFFSET_KOS_STAT_MTIMESPEC    __OFFSET_KOS_STAT_MTIMESPEC32
#define __OFFSET_KOS_STAT_MTIME        __OFFSET_KOS_STAT_MTIME32
#define __OFFSET_KOS_STAT_MTIMENSEC    __OFFSET_KOS_STAT_MTIMENSEC32
#define __OFFSET_KOS_STAT_CTIMESPEC    __OFFSET_KOS_STAT_CTIMESPEC32
#define __OFFSET_KOS_STAT_CTIME        __OFFSET_KOS_STAT_CTIME32
#define __OFFSET_KOS_STAT_CTIMENSEC    __OFFSET_KOS_STAT_CTIMENSEC32
#endif /* !__USE_TIME_BITS64 && (!__KERNEL__ || !__KOS__) */

#ifdef __CC__
__DECL_BEGIN

#if defined(__KERNEL__) && defined(__KOS__)
#define __FS_INT64_FIELD(name, T32, T64) T64 name
#elif defined(__USE_FILE_OFFSET64) && defined(__USE_KOS)
#define __FS_INT64_FIELD(name, T32, T64) \
	union {                              \
		T64 name;                        \
		T32 name##32;                    \
		T64 name##64;                    \
	}
#elif defined(__USE_FILE_OFFSET64)
#define __FS_INT64_FIELD(name, T32, T64) T64 name
#elif defined(__USE_KOS)
#define __FS_INT64_FIELD(name, T32, T64) \
	union {                              \
		T32 name;                        \
		T32 name##32;                    \
		T64 name##64;                    \
	}
#else
#define __FS_INT64_FIELD(name, T32, T64) \
	union {                              \
		T32 name;                        \
		T64 __##name##64;                \
	}
#endif

struct __kos_stat /*[PREFIX(st_)][NAME(kos_stat)]*/ {
	__dev_t          st_dev;
	__FS_INT64_FIELD(st_ino, __ino32_t, __ino64_t);
	__mode_t         st_mode;
	__nlink_t        st_nlink;
	__uid_t          st_uid;
	__gid_t          st_gid;
	__dev_t          st_rdev;
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
	__FS_INT64_FIELD(st_size, __pos32_t, __pos64_t);
#else /* __USE_KOS || __USE_KOS_KERNEL */
	__FS_INT64_FIELD(st_size, __off32_t, __off64_t);
#endif /* !__USE_KOS && !__USE_KOS_KERNEL */
	__blksize_t      st_blksize;
#if __SIZEOF_BLKSIZE_T__ < __SIZEOF_OFF64_T__
	__byte_t       __st_pad[__SIZEOF_OFF64_T__ - __SIZEOF_BLKSIZE_T__];
#endif /* __SIZEOF_BLKSIZE_T__ < __SIZEOF_OFF64_T__ */
	__FS_INT64_FIELD(st_blocks, __blkcnt32_t, __blkcnt64_t);

#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
	union {
#ifdef __USE_XOPEN2K8
		struct timespec     st_atim;
#endif /* __USE_XOPEN2K8 */
		struct timespec     st_atimespec;
		struct {
			__TM_TYPE(time)   st_atime;
			__syscall_ulong_t st_atimensec;
		};
#if defined(__USE_KOS) && defined(__WANT_FULL_STRUCT_STAT)
#ifdef __USE_XOPEN2K8
		struct __timespec32 st_atim32;
		struct __timespec64 st_atim64;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32 st_atimespec32;
		struct __timespec64 st_atimespec64;
		struct {
			__time32_t        st_atime32;
			__syscall_ulong_t st_atimensec32;
		};
		struct {
			__time64_t        st_atime64;
			__syscall_ulong_t st_atimensec64;
		};
#endif /* __USE_KOS && __WANT_FULL_STRUCT_STAT */
	};
	union {
#ifdef __USE_XOPEN2K8
		struct timespec     st_mtim;
#endif /* __USE_XOPEN2K8 */
		struct timespec     st_mtimespec;
		struct {
			__TM_TYPE(time)   st_mtime;
			__syscall_ulong_t st_mtimensec;
		};
#if defined(__USE_KOS) && defined(__WANT_FULL_STRUCT_STAT)
#ifdef __USE_XOPEN2K8
		struct __timespec32 st_mtim32;
		struct __timespec64 st_mtim64;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32 st_mtimespec32;
		struct __timespec64 st_mtimespec64;
		struct {
			__time32_t        st_mtime32;
			__syscall_ulong_t st_mtimensec32;
		};
		struct {
			__time64_t        st_mtime64;
			__syscall_ulong_t st_mtimensec64;
		};
#endif /* __USE_KOS && __WANT_FULL_STRUCT_STAT */
	};
	union {
#ifdef __USE_XOPEN2K8
		struct timespec     st_ctim;
#endif /* __USE_XOPEN2K8 */
		struct timespec     st_ctimespec;
		struct {
			__TM_TYPE(time)   st_ctime;
			__syscall_ulong_t st_ctimensec;
		};
#if defined(__USE_KOS) && defined(__WANT_FULL_STRUCT_STAT)
#ifdef __USE_XOPEN2K8
		struct __timespec32 st_ctim32;
		struct __timespec64 st_ctim64;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32 st_ctimespec32;
		struct __timespec64 st_ctimespec64;
		struct {
			__time32_t        st_ctime32;
			__syscall_ulong_t st_ctimensec32;
		};
		struct {
			__time64_t        st_ctime64;
			__syscall_ulong_t st_ctimensec64;
		};
#endif /* __USE_KOS && __WANT_FULL_STRUCT_STAT */
	};
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#ifndef __WANT_FULL_STRUCT_STAT
	struct __timespec32 __st_atimespec32;
	struct __timespec32 __st_mtimespec32;
	struct __timespec32 __st_ctimespec32;
	union {
#ifdef __USE_XOPEN2K8
		struct __timespec64 st_atim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64 st_atimespec;
		struct {
			__time64_t        st_atime;
			__syscall_ulong_t st_atimensec;
		};
	};
	union {
#ifdef __USE_XOPEN2K8
		struct __timespec64 st_mtim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64 st_mtimespec;
		struct {
			__time64_t        st_mtime;
			__syscall_ulong_t st_mtimensec;
		};
	};
	union {
#ifdef __USE_XOPEN2K8
		struct __timespec64 st_ctim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64 st_ctimespec;
		struct {
			__time64_t        st_ctime;
			__syscall_ulong_t st_ctimensec;
		};
	};
#else /* __WANT_FULL_STRUCT_STAT */
	/* struct __timespec32 st_atimespec32; */
#if defined(__USE_KOS) || !defined(__USE_TIME_BITS64)
	union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec32 st_atim32;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32 st_atimespec32;
		struct {
			__time32_t        st_atime32;
			__syscall_ulong_t st_atimensec32;
		};
#endif /* __USE_KOS */
#ifndef __USE_TIME_BITS64
#ifdef __USE_XOPEN2K8
		struct __timespec32 st_atim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32 st_atimespec;
		struct {
			__time32_t        st_atime;
			__syscall_ulong_t st_atimensec;
		};
#endif /* !__USE_TIME_BITS64 */
	};
#else /* __USE_KOS || !__USE_TIME_BITS64 */
	struct __timespec32 __st_atimespec32;
#endif /* !__USE_KOS && __USE_TIME_BITS64 */
	/* struct __timespec32 st_mtimespec32; */
#if defined(__USE_KOS) || !defined(__USE_TIME_BITS64)
	union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec32 st_mtim32;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32 st_mtimespec32;
		struct {
			__time32_t        st_mtime32;
			__syscall_ulong_t st_mtimensec32;
		};
#endif /* __USE_KOS */
#ifndef __USE_TIME_BITS64
#ifdef __USE_XOPEN2K8
		struct __timespec32 st_mtim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32 st_mtimespec;
		struct {
			__time32_t        st_mtime;
			__syscall_ulong_t st_mtimensec;
		};
#endif /* !__USE_TIME_BITS64 */
	};
#else /* __USE_KOS || !__USE_TIME_BITS64 */
	struct __timespec32 __st_mtimespec32;
#endif /* !__USE_KOS && __USE_TIME_BITS64 */
	/* struct __timespec32 st_ctimespec32; */
#if defined(__USE_KOS) || !defined(__USE_TIME_BITS64)
	union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec32 st_ctim32;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32 st_ctimespec32;
		struct {
			__time32_t        st_ctime32;
			__syscall_ulong_t st_ctimensec32;
		};
#endif /* __USE_KOS */
#ifndef __USE_TIME_BITS64
#ifdef __USE_XOPEN2K8
		struct __timespec32 st_ctim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32 st_ctimespec;
		struct {
			__time32_t        st_ctime;
			__syscall_ulong_t st_ctimensec;
		};
#endif /* !__USE_TIME_BITS64 */
	};
#else /* __USE_KOS || !__USE_TIME_BITS64 */
	struct __timespec32 __st_ctimespec32;
#endif /* !__USE_KOS && __USE_TIME_BITS64 */
	/* struct __timespec64 st_atimespec64; */
#if defined(__USE_KOS) || defined(__USE_TIME_BITS64)
	union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec64 st_atim64;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64 st_atimespec64;
		struct {
			__time32_t        st_atime64;
			__syscall_ulong_t st_atimensec64;
		};
#endif /* __USE_KOS */
#ifdef __USE_TIME_BITS64
#ifdef __USE_XOPEN2K8
		struct __timespec64 st_atim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64 st_atimespec;
		struct {
			__time64_t        st_atime;
			__syscall_ulong_t st_atimensec;
		};
#endif /* __USE_TIME_BITS64 */
	};
#else /* __USE_KOS || !__USE_TIME_BITS64 */
	struct __timespec64 __st_atimespec64;
#endif /* !__USE_KOS && __USE_TIME_BITS64 */
	/* struct __timespec64 st_mtimespec64; */
#if defined(__USE_KOS) || defined(__USE_TIME_BITS64)
	union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec64 st_mtim64;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64 st_mtimespec64;
		struct {
			__time32_t        st_mtime64;
			__syscall_ulong_t st_mtimensec64;
		};
#endif /* __USE_KOS */
#ifdef __USE_TIME_BITS64
#ifdef __USE_XOPEN2K8
		struct __timespec64 st_mtim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64 st_mtimespec;
		struct {
			__time64_t        st_mtime;
			__syscall_ulong_t st_mtimensec;
		};
#endif /* __USE_TIME_BITS64 */
	};
#else /* __USE_KOS || !__USE_TIME_BITS64 */
	struct __timespec64 __st_mtimespec64;
#endif /* !__USE_KOS && __USE_TIME_BITS64 */
	/* struct __timespec64 st_ctimespec64; */
#if defined(__USE_KOS) || defined(__USE_TIME_BITS64)
	union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec64 st_ctim64;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64 st_ctimespec64;
		struct {
			__time32_t        st_ctime64;
			__syscall_ulong_t st_ctimensec64;
		};
#endif /* __USE_KOS */
#ifdef __USE_TIME_BITS64
#ifdef __USE_XOPEN2K8
		struct __timespec64 st_ctim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64 st_ctimespec;
		struct {
			__time64_t        st_ctime;
			__syscall_ulong_t st_ctimensec;
		};
#endif /* __USE_TIME_BITS64 */
	};
#else /* __USE_KOS || !__USE_TIME_BITS64 */
	struct __timespec64 __st_ctimespec64;
#endif /* !__USE_KOS && __USE_TIME_BITS64 */
#endif /* __WANT_FULL_STRUCT_STAT */
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
};

#undef __FS_INT64_FIELD



#ifdef __kos_stat_alias64
#if defined(__USE_KOS) && defined(__WANT_FULL_STRUCT_STAT)
#define __FS_INT64_FIELD(name, T32, T64) \
	union {                              \
		T64 name;                        \
		T32 name##32;                    \
		T64 name##64;                    \
	}
#else /* __USE_KOS && __WANT_FULL_STRUCT_STAT */
#define __FS_INT64_FIELD(name, T32, T64) T64 name
#endif /* !__USE_KOS || !__WANT_FULL_STRUCT_STAT */
struct __kos_stat_alias64 /*[PREFIX(st_)][NAME(kos_stat)]*/ {
	__dev_t          st_dev;
	__FS_INT64_FIELD(st_ino, __ino32_t, __ino64_t);
	__mode_t         st_mode;
	__nlink_t        st_nlink;
	__uid_t          st_uid;
	__gid_t          st_gid;
	__dev_t          st_rdev;
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
	__FS_INT64_FIELD(st_size, __pos32_t, __pos64_t);
#else /* __USE_KOS || __USE_KOS_KERNEL */
	__FS_INT64_FIELD(st_size, __off32_t, __off64_t);
#endif /* !__USE_KOS && !__USE_KOS_KERNEL */
	__blksize_t      st_blksize;
#if __SIZEOF_BLKSIZE_T__ < __SIZEOF_OFF64_T__
	__byte_t       __st_pad[__SIZEOF_OFF64_T__ - __SIZEOF_BLKSIZE_T__];
#endif /* __SIZEOF_BLKSIZE_T__ < __SIZEOF_OFF64_T__ */
	__FS_INT64_FIELD(st_blocks, __blkcnt32_t, __blkcnt64_t);

#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
	union {
#ifdef __USE_XOPEN2K8
		struct timespec     st_atim;
#endif /* __USE_XOPEN2K8 */
		struct timespec     st_atimespec;
		struct {
			__TM_TYPE(time)   st_atime;
			__syscall_ulong_t st_atimensec;
		};
#if defined(__USE_KOS) && defined(__WANT_FULL_STRUCT_STAT)
#ifdef __USE_XOPEN2K8
		struct __timespec32 st_atim32;
		struct __timespec64 st_atim64;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32 st_atimespec32;
		struct __timespec64 st_atimespec64;
		struct {
			__time32_t        st_atime32;
			__syscall_ulong_t st_atimensec32;
		};
		struct {
			__time64_t        st_atime64;
			__syscall_ulong_t st_atimensec64;
		};
#endif /* __USE_KOS && __WANT_FULL_STRUCT_STAT */
	};
	union {
#ifdef __USE_XOPEN2K8
		struct timespec     st_mtim;
#endif /* __USE_XOPEN2K8 */
		struct timespec     st_mtimespec;
		struct {
			__TM_TYPE(time)   st_mtime;
			__syscall_ulong_t st_mtimensec;
		};
#if defined(__USE_KOS) && defined(__WANT_FULL_STRUCT_STAT)
#ifdef __USE_XOPEN2K8
		struct __timespec32 st_mtim32;
		struct __timespec64 st_mtim64;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32 st_mtimespec32;
		struct __timespec64 st_mtimespec64;
		struct {
			__time32_t        st_mtime32;
			__syscall_ulong_t st_mtimensec32;
		};
		struct {
			__time64_t        st_mtime64;
			__syscall_ulong_t st_mtimensec64;
		};
#endif /* __USE_KOS && __WANT_FULL_STRUCT_STAT */
	};
	union {
#ifdef __USE_XOPEN2K8
		struct timespec     st_ctim;
#endif /* __USE_XOPEN2K8 */
		struct timespec     st_ctimespec;
		struct {
			__TM_TYPE(time)   st_ctime;
			__syscall_ulong_t st_ctimensec;
		};
#if defined(__USE_KOS) && defined(__WANT_FULL_STRUCT_STAT)
#ifdef __USE_XOPEN2K8
		struct __timespec32 st_ctim32;
		struct __timespec64 st_ctim64;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32 st_ctimespec32;
		struct __timespec64 st_ctimespec64;
		struct {
			__time32_t        st_ctime32;
			__syscall_ulong_t st_ctimensec32;
		};
		struct {
			__time64_t        st_ctime64;
			__syscall_ulong_t st_ctimensec64;
		};
#endif /* __USE_KOS && __WANT_FULL_STRUCT_STAT */
	};
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#ifndef __WANT_FULL_STRUCT_STAT
	struct __timespec32 __st_atimespec32;
	struct __timespec32 __st_mtimespec32;
	struct __timespec32 __st_ctimespec32;
	union {
#ifdef __USE_XOPEN2K8
		struct __timespec64 st_atim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64 st_atimespec;
		struct {
			__time64_t        st_atime;
			__syscall_ulong_t st_atimensec;
		};
	};
	union {
#ifdef __USE_XOPEN2K8
		struct __timespec64 st_mtim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64 st_mtimespec;
		struct {
			__time64_t        st_mtime;
			__syscall_ulong_t st_mtimensec;
		};
	};
	union {
#ifdef __USE_XOPEN2K8
		struct __timespec64 st_ctim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64 st_ctimespec;
		struct {
			__time64_t        st_ctime;
			__syscall_ulong_t st_ctimensec;
		};
	};
#else /* !__WANT_FULL_STRUCT_STAT */
	/* struct __timespec32 st_atimespec32; */
#if defined(__USE_KOS) || !defined(__USE_TIME_BITS64)
	union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec32 st_atim32;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32 st_atimespec32;
		struct {
			__time32_t        st_atime32;
			__syscall_ulong_t st_atimensec32;
		};
#endif /* __USE_KOS */
#ifndef __USE_TIME_BITS64
#ifdef __USE_XOPEN2K8
		struct __timespec32 st_atim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32 st_atimespec;
		struct {
			__time32_t        st_atime;
			__syscall_ulong_t st_atimensec;
		};
#endif /* !__USE_TIME_BITS64 */
	};
#else /* __USE_KOS || !__USE_TIME_BITS64 */
	struct __timespec32 __st_atimespec32;
#endif /* !__USE_KOS && __USE_TIME_BITS64 */
	/* struct __timespec32 st_mtimespec32; */
#if defined(__USE_KOS) || !defined(__USE_TIME_BITS64)
	union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec32 st_mtim32;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32 st_mtimespec32;
		struct {
			__time32_t        st_mtime32;
			__syscall_ulong_t st_mtimensec32;
		};
#endif /* __USE_KOS */
#ifndef __USE_TIME_BITS64
#ifdef __USE_XOPEN2K8
		struct __timespec32 st_mtim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32 st_mtimespec;
		struct {
			__time32_t        st_mtime;
			__syscall_ulong_t st_mtimensec;
		};
#endif /* !__USE_TIME_BITS64 */
	};
#else /* __USE_KOS || !__USE_TIME_BITS64 */
	struct __timespec32 __st_mtimespec32;
#endif /* !__USE_KOS && __USE_TIME_BITS64 */
	/* struct __timespec32 st_ctimespec32; */
#if defined(__USE_KOS) || !defined(__USE_TIME_BITS64)
	union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec32 st_ctim32;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32 st_ctimespec32;
		struct {
			__time32_t        st_ctime32;
			__syscall_ulong_t st_ctimensec32;
		};
#endif /* __USE_KOS */
#ifndef __USE_TIME_BITS64
#ifdef __USE_XOPEN2K8
		struct __timespec32 st_ctim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32 st_ctimespec;
		struct {
			__time32_t        st_ctime;
			__syscall_ulong_t st_ctimensec;
		};
#endif /* !__USE_TIME_BITS64 */
	};
#else /* __USE_KOS || !__USE_TIME_BITS64 */
	struct __timespec32 __st_ctimespec32;
#endif /* !__USE_KOS && __USE_TIME_BITS64 */
	/* struct __timespec64 st_atimespec64; */
#if defined(__USE_KOS) || defined(__USE_TIME_BITS64)
	union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec64 st_atim64;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64 st_atimespec64;
		struct {
			__time32_t        st_atime64;
			__syscall_ulong_t st_atimensec64;
		};
#endif /* __USE_KOS */
#ifdef __USE_TIME_BITS64
#ifdef __USE_XOPEN2K8
		struct __timespec64 st_atim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64 st_atimespec;
		struct {
			__time64_t        st_atime;
			__syscall_ulong_t st_atimensec;
		};
#endif /* __USE_TIME_BITS64 */
	};
#else /* __USE_KOS || !__USE_TIME_BITS64 */
	struct __timespec64 __st_atimespec64;
#endif /* !__USE_KOS && __USE_TIME_BITS64 */
	/* struct __timespec64 st_mtimespec64; */
#if defined(__USE_KOS) || defined(__USE_TIME_BITS64)
	union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec64 st_mtim64;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64 st_mtimespec64;
		struct {
			__time32_t        st_mtime64;
			__syscall_ulong_t st_mtimensec64;
		};
#endif /* __USE_KOS */
#ifdef __USE_TIME_BITS64
#ifdef __USE_XOPEN2K8
		struct __timespec64 st_mtim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64 st_mtimespec;
		struct {
			__time64_t        st_mtime;
			__syscall_ulong_t st_mtimensec;
		};
#endif /* __USE_TIME_BITS64 */
	};
#else /* __USE_KOS || !__USE_TIME_BITS64 */
	struct __timespec64 __st_mtimespec64;
#endif /* !__USE_KOS && __USE_TIME_BITS64 */
	/* struct __timespec64 st_ctimespec64; */
#if defined(__USE_KOS) || defined(__USE_TIME_BITS64)
	union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec64 st_ctim64;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64 st_ctimespec64;
		struct {
			__time32_t        st_ctime64;
			__syscall_ulong_t st_ctimensec64;
		};
#endif /* __USE_KOS */
#ifdef __USE_TIME_BITS64
#ifdef __USE_XOPEN2K8
		struct __timespec64 st_ctim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64 st_ctimespec;
		struct {
			__time64_t        st_ctime;
			__syscall_ulong_t st_ctimensec;
		};
#endif /* __USE_TIME_BITS64 */
	};
#else /* __USE_KOS || !__USE_TIME_BITS64 */
	struct __timespec64 __st_ctimespec64;
#endif /* !__USE_KOS && __USE_TIME_BITS64 */
#endif /* __WANT_FULL_STRUCT_STAT */
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
};
#undef __FS_INT64_FIELD
#endif /* __kos_stat_alias64 */


__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_KOS_STAT_H */
