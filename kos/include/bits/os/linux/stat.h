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
#ifndef _BITS_OS_LINUX_STAT_H
#define _BITS_OS_LINUX_STAT_H 1

/* NOTE: GLIBC stat structures! */

#include <__crt.h> /* __CRT_GLC_PRIMARY */
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/os/timespec.h>
#include <bits/types.h>

#ifdef __CRT_GLC_PRIMARY

#define __glc_stat   stat

#ifdef __USE_XOPEN2K8
#define _STATBUF_ST_TIM      1
#endif /* __USE_XOPEN2K8 */
#define _STATBUF_ST_TIMESPEC 1 /* Apple extension? */
#define _STATBUF_ST_TIME     1 /* Always defined. */
#define _STATBUF_ST_NSEC     1
#define _STATBUF_ST_BLKSIZE  1
#define _STATBUF_ST_RDEV     1
#define _STATBUF_ST_BLOCKS   1

#ifdef __USE_LARGEFILE64
#define __glc_stat64 stat64
#define __stat64     stat64
#else /* __USE_LARGEFILE64 */
#define __stat64 __glc_stat64
#endif /* !__USE_LARGEFILE64 */

#endif /* __CRT_GLC_PRIMARY */

#ifdef __CC__
__DECL_BEGIN

struct __glc_stat /*[PREFIX(st_)]*/ {
	/* +0  */ __UINT64_TYPE__   st_dev;
	/* +8  */ __UINT32_TYPE__ __st_pad0;
#if defined(__USE_KOS) && !defined(__USE_FILE_OFFSET64)
	union {
		/* +12 */ __UINT32_TYPE__ st_ino32;
		/* +12 */ __UINT32_TYPE__ st_ino;
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
#ifdef __USE_KOS_ALTERATIONS
		/* +44 */ __UINT64_TYPE__   st_size;
#else /* __USE_KOS_ALTERATIONS */
		/* +44 */ __INT64_TYPE__    st_size;
#endif /* !__USE_KOS_ALTERATIONS */
		/* +44 */ __UINT32_TYPE__   st_size32;
		/* +44 */ __UINT64_TYPE__   st_size64;
	};
#elif defined(__USE_KOS_ALTERATIONS)
	/* +44 */ __UINT64_TYPE__   st_size;
#else /* __USE_KOS */
	/* +44 */ __INT64_TYPE__    st_size;
#endif /* !__USE_KOS */
#ifdef __USE_KOS_ALTERATIONS
	/* +52 */ __UINT32_TYPE__   st_blksize;
	/* +56 */ __UINT64_TYPE__   st_blocks;
#else /* __USE_KOS_ALTERATIONS */
	/* +52 */ __INT32_TYPE__    st_blksize;
	/* +56 */ __INT64_TYPE__    st_blocks;
#endif /* !__USE_KOS_ALTERATIONS */

	/* struct __timespec32 st_atimespec32; */
	/* +64 */ union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec32   st_atim32;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32   st_atimespec32;
		struct {
			__time32_t        st_atime32;
			__syscall_ulong_t st_atimensec32;
		};
#endif /* __USE_KOS */
#ifdef __USE_XOPEN2K8
		struct __timespec32   st_atim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32   st_atimespec;
		struct {
			__time32_t        st_atime;
			__syscall_ulong_t st_atimensec;
		};
	};

	/* struct __timespec32 st_mtimespec32; */
	/* +72 */ union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec32   st_mtim32;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32   st_mtimespec32;
		struct {
			__time32_t        st_mtime32;
			__syscall_ulong_t st_mtimensec32;
		};
#endif /* __USE_KOS */
#ifdef __USE_XOPEN2K8
		struct __timespec32   st_mtim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32   st_mtimespec;
		struct {
			__time32_t        st_mtime;
			__syscall_ulong_t st_mtimensec;
		};
	};

	/* struct __timespec32 st_ctimespec32; */
	/* +80 */ union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec32   st_ctim32;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32   st_ctimespec32;
		struct {
			__time32_t        st_ctime32;
			__syscall_ulong_t st_ctimensec32;
		};
#endif /* __USE_KOS */
#ifdef __USE_XOPEN2K8
		struct __timespec32   st_ctim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32   st_ctimespec;
		struct {
			__time32_t        st_ctime;
			__syscall_ulong_t st_ctimensec;
		};
	};

#ifdef __USE_KOS
	union {
		/* +88 */ __UINT64_TYPE__ st_ino;
		/* +88 */ __UINT64_TYPE__ st_ino64;
	};
#else /* __USE_KOS */
	/* +88 */ __UINT64_TYPE__ st_ino;
#endif /* !__USE_KOS */
#else /* __USE_FILE_OFFSET64 */
#ifdef __USE_KOS
	union {
#ifdef __USE_KOS_ALTERATIONS
		/* +44 */ __UINT32_TYPE__   st_size;
#else /* __USE_KOS_ALTERATIONS */
		/* +44 */ __INT32_TYPE__    st_size;
#endif /* !__USE_KOS_ALTERATIONS */
		/* +44 */ __UINT32_TYPE__   st_size32;
	};
#elif defined(__USE_KOS_ALTERATIONS)
	/* +44 */ __UINT32_TYPE__   st_size;
#else /* ... */
	/* +44 */ __INT32_TYPE__    st_size;
#endif /* !... */
#ifdef __USE_KOS_ALTERATIONS
	/* +48 */ __UINT32_TYPE__   st_blksize;
	/* +52 */ __UINT32_TYPE__   st_blocks;
#else /* __USE_KOS_ALTERATIONS */
	/* +48 */ __INT32_TYPE__    st_blksize;
	/* +52 */ __INT32_TYPE__    st_blocks;
#endif /* !__USE_KOS_ALTERATIONS */
	/* struct __timespec32 st_atimespec32; */
	/* +56 */ union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec32   st_atim32;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32   st_atimespec32;
		struct {
			__time32_t        st_atime32;
			__syscall_ulong_t st_atimensec32;
		};
#endif /* __USE_KOS */
#ifdef __USE_XOPEN2K8
		struct __timespec32   st_atim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32   st_atimespec;
		struct {
			__time32_t        st_atime;
			__syscall_ulong_t st_atimensec;
		};
	};

	/* struct __timespec32 st_mtimespec32; */
	/* +64 */ union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec32   st_mtim32;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32   st_mtimespec32;
		struct {
			__time32_t        st_mtime32;
			__syscall_ulong_t st_mtimensec32;
		};
#endif /* __USE_KOS */
#ifdef __USE_XOPEN2K8
		struct __timespec32   st_mtim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32   st_mtimespec;
		struct {
			__time32_t        st_mtime;
			__syscall_ulong_t st_mtimensec;
		};
	};

	/* struct __timespec32 st_ctimespec32; */
	/* +72 */  union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec32   st_ctim32;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32   st_ctimespec32;
		struct {
			__time32_t        st_ctime32;
			__syscall_ulong_t st_ctimensec32;
		};
#endif /* __USE_KOS */
#ifdef __USE_XOPEN2K8
		struct __timespec32   st_ctim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32   st_ctimespec;
		struct {
			__time32_t        st_ctime;
			__syscall_ulong_t st_ctimensec;
		};
	};

	/* +80 */ __UINT32_TYPE__ __pad2;
	/* +84 */ __UINT32_TYPE__ __pad3;
#endif /* !__USE_FILE_OFFSET64 */
};

struct __glc_stat64 /*[PREFIX(st_)]*/ {
	/* +0  */ __UINT64_TYPE__   st_dev;
	/* +8  */ __UINT32_TYPE__ __st_pad0;
#ifdef __USE_KOS
	/* +12 */ __UINT32_TYPE__   st_ino32;
#else
	/* +12 */ __UINT32_TYPE__ __st_ino32;
#endif /* !... */
	/* +16 */ __UINT32_TYPE__   st_mode;
	/* +20 */ __UINT32_TYPE__   st_nlink;
	/* +24 */ __UINT32_TYPE__   st_uid;
	/* +28 */ __UINT32_TYPE__   st_gid;
	/* +32 */ __UINT64_TYPE__   st_rdev;
	/* +40 */ __UINT32_TYPE__ __pad1;
#ifdef __USE_KOS
	union {
#ifdef __USE_KOS_ALTERATIONS
		/* +44 */ __UINT64_TYPE__   st_size;
#else /* __USE_KOS_ALTERATIONS */
		/* +44 */ __INT64_TYPE__    st_size;
#endif /* !__USE_KOS_ALTERATIONS */
		/* +44 */ __UINT32_TYPE__   st_size32;
		/* +44 */ __UINT64_TYPE__   st_size64;
	};
#elif defined(__USE_KOS_ALTERATIONS)
	/* +44 */ __UINT64_TYPE__   st_size;
#else /* ... */
	/* +44 */ __INT64_TYPE__    st_size;
#endif /* !... */
#ifdef __USE_KOS_ALTERATIONS
	/* +52 */ __UINT32_TYPE__   st_blksize;
	/* +56 */ __UINT64_TYPE__   st_blocks;
#else /* __USE_KOS_ALTERATIONS */
	/* +52 */ __INT32_TYPE__    st_blksize;
	/* +56 */ __INT64_TYPE__    st_blocks;
#endif /* !__USE_KOS_ALTERATIONS */

	/* struct __timespec32 st_atimespec32; */
	/* +64 */ union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec32   st_atim32;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32   st_atimespec32;
		struct {
			__time32_t        st_atime32;
			__syscall_ulong_t st_atimensec32;
		};
#endif /* __USE_KOS */
#ifdef __USE_XOPEN2K8
		struct __timespec32   st_atim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32   st_atimespec;
		struct {
			__time32_t        st_atime;
			__syscall_ulong_t st_atimensec;
		};
	};

	/* struct __timespec32 st_mtimespec32; */
	/* +72 */ union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec32   st_mtim32;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32   st_mtimespec32;
		struct {
			__time32_t        st_mtime32;
			__syscall_ulong_t st_mtimensec32;
		};
#endif /* __USE_KOS */
#ifdef __USE_XOPEN2K8
		struct __timespec32   st_mtim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32   st_mtimespec;
		struct {
			__time32_t        st_mtime;
			__syscall_ulong_t st_mtimensec;
		};
	};

	/* struct __timespec32 st_ctimespec32; */
	/* +80 */ union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec32   st_ctim32;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32   st_ctimespec32;
		struct {
			__time32_t        st_ctime32;
			__syscall_ulong_t st_ctimensec32;
		};
#endif /* __USE_KOS */
#ifdef __USE_XOPEN2K8
		struct __timespec32   st_ctim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec32   st_ctimespec;
		struct {
			__time32_t        st_ctime;
			__syscall_ulong_t st_ctimensec;
		};
	};

#ifdef __USE_KOS
	union {
		/* +88 */ __UINT64_TYPE__ st_ino;
		/* +88 */ __UINT64_TYPE__ st_ino64;
	};
#else /* __USE_KOS */
	/* +88 */ __UINT64_TYPE__ st_ino;
#endif /* !__USE_KOS */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_LINUX_STAT_H */
