/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_OS_DOS_STAT_H
#define _BITS_OS_DOS_STAT_H 1

#include <__crt.h> /* __CRT_DOS_PRIMARY */
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#ifdef __CRT_DOS_PRIMARY

#define __dos_bstat      stat
#define _STATBUF_ST_TIME 1 /* Always defined. */
#define _STATBUF_ST_RDEV 1

#ifdef __USE_LARGEFILE64
#define __dos_bstat64 stat64
#define __stat64      stat64
#else /* __USE_LARGEFILE64 */
#define __stat64      __dos_bstat64
#endif /* !__USE_LARGEFILE64 */

#endif /* __CRT_DOS_PRIMARY */

#ifdef __CC__
__DECL_BEGIN

struct __dos_bstat {
	__uint32_t     st_dev;
	__uint16_t     st_ino;
	__uint16_t     st_mode;
	__int16_t      st_nlink;
	__int16_t      st_uid;
	__int16_t      st_gid;
	__int16_t    __st_pad0;
	__uint32_t     st_rdev;
#ifdef __USE_FILE_OFFSET64
#ifdef __USE_KOS
	union {
#ifdef __USE_KOS_ALTERATIONS
		__UINT64_TYPE__ st_size;
#else /* __USE_KOS_ALTERATIONS */
		__INT64_TYPE__  st_size;
#endif /* !__USE_KOS_ALTERATIONS */
		__UINT64_TYPE__ st_size64;
		__UINT32_TYPE__ st_size32;
	};
#else /* __USE_KOS */
	__INT64_TYPE__ st_size;
#endif /* !__USE_KOS */
#elif defined(__USE_TIME_BITS64)
	__int32_t    __st_pad1;
	union { /* binary compatibility to `stat64i32' and `stat64'. */
#ifdef __USE_KOS_ALTERATIONS
		__UINT32_TYPE__ st_size;
#else /* __USE_KOS_ALTERATIONS */
		__INT32_TYPE__  st_size;
#endif /* !__USE_KOS_ALTERATIONS */
#ifdef __USE_KOS
		__UINT32_TYPE__ st_size32;
#endif /* !__USE_KOS */
		__INT64_TYPE__ __st_pad2;
	};
#elif defined(__USE_KOS)
	union {
#ifdef __USE_KOS_ALTERATIONS
		__UINT32_TYPE__ st_size;
#else /* __USE_KOS_ALTERATIONS */
		__INT32_TYPE__  st_size;
#endif /* !__USE_KOS_ALTERATIONS */
		__UINT32_TYPE__ st_size32;
	};
#elif defined(__USE_KOS_ALTERATIONS)
	__UINT32_TYPE__ st_size;
#else /* ... */
	__INT32_TYPE__  st_size;
#endif /* !... */
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
	__time_t st_atime;
	__time_t st_mtime;
	__time_t st_ctime;
#endif /* !__USE_KOS */
};

struct __dos_bstat64 {
	__uint32_t     st_dev;
	__uint16_t     st_ino;
	__uint16_t     st_mode;
	__int16_t      st_nlink;
	__int16_t      st_uid;
	__int16_t      st_gid;
	__int16_t    __st_pad0;
	__uint32_t     st_rdev;
#ifdef __USE_KOS
	union {
#ifdef __USE_KOS_ALTERATIONS
		__UINT64_TYPE__ st_size;
#else /* __USE_KOS_ALTERATIONS */
		__INT64_TYPE__  st_size;
#endif /* !__USE_KOS_ALTERATIONS */
		__UINT64_TYPE__ st_size64;
		__UINT32_TYPE__ st_size32;
	};
#elif defined(__USE_KOS_ALTERATIONS)
	__UINT64_TYPE__ st_size;
#else /* ... */
	__INT64_TYPE__ st_size;
#endif /* !... */
#ifdef __USE_KOS
	union { __time_t st_atime; __time32_t st_atime32; };
	union { __time_t st_mtime; __time32_t st_mtime32; };
	union { __time_t st_ctime; __time32_t st_ctime32; };
#else /* __USE_KOS */
	__time_t st_atime;
	__time_t st_mtime;
	__time_t st_ctime;
#endif /* !__USE_KOS */
};


#ifdef __DEFINE_DOS_STAT_STRUCTURES
#undef __DEFINE_DOS_STAT_STRUCTURES
struct __dos_stat32 {
	__uint32_t     st_dev;
	__uint16_t     st_ino;
	__uint16_t     st_mode;
	__int16_t      st_nlink;
	__int16_t      st_uid;
	__int16_t      st_gid;
	__int16_t    __st_pad0;
	__uint32_t     st_rdev;
#ifdef __USE_KOS
	union {
#ifdef __USE_KOS_ALTERATIONS
		__UINT32_TYPE__ st_size;
#else /* __USE_KOS_ALTERATIONS */
		__INT32_TYPE__  st_size;
#endif /* !__USE_KOS_ALTERATIONS */
		__UINT32_TYPE__ st_size32;
	};
	union { __time32_t st_atime; __time32_t st_atime32; };
	union { __time32_t st_mtime; __time32_t st_mtime32; };
	union { __time32_t st_ctime; __time32_t st_ctime32; };
#else /* __USE_KOS */
#ifdef __USE_KOS_ALTERATIONS
	__UINT32_TYPE__ st_size;
#else /* __USE_KOS_ALTERATIONS */
	__INT32_TYPE__ st_size;
#endif /* !__USE_KOS_ALTERATIONS */
	__time32_t     st_atime;
	__time32_t     st_mtime;
	__time32_t     st_ctime;
#endif /* !__USE_KOS */
};
struct __dos_stat32i64 {
	__uint32_t     st_dev;
	__uint16_t     st_ino;
	__uint16_t     st_mode;
	__int16_t      st_nlink;
	__int16_t      st_uid;
	__int16_t      st_gid;
	__int16_t    __st_pad0;
	__uint32_t     st_rdev;
	__int32_t    __st_pad1;
#ifdef __USE_KOS
	union {
#ifdef __USE_KOS_ALTERATIONS
		__UINT64_TYPE__ st_size;
#else /* __USE_KOS_ALTERATIONS */
		__INT64_TYPE__  st_size;
#endif /* !__USE_KOS_ALTERATIONS */
		__UINT32_TYPE__ st_size32;
		__UINT64_TYPE__ st_size64;
	};
	union { __time32_t st_atime; __time32_t st_atime32; };
	union { __time32_t st_mtime; __time32_t st_mtime32; };
	union { __time32_t st_ctime; __time32_t st_ctime32; };
#else /* __USE_KOS */
#ifdef __USE_KOS_ALTERATIONS
	__UINT64_TYPE__ st_size;
#else /* __USE_KOS_ALTERATIONS */
	__INT64_TYPE__ st_size;
#endif /* !__USE_KOS_ALTERATIONS */
	__time32_t     st_atime;
	__time32_t     st_mtime;
	__time32_t     st_ctime;
#endif /* !__USE_KOS */
	__int32_t    __st_pad2;
};
struct __dos_stat64i32 {
	__uint32_t     st_dev;
	__uint16_t     st_ino;
	__uint16_t     st_mode;
	__int16_t      st_nlink;
	__int16_t      st_uid;
	__int16_t      st_gid;
	__int16_t    __st_pad0;
	__uint32_t     st_rdev;
	__int32_t    __st_pad1;
#ifdef __USE_KOS
	union {
#ifdef __USE_KOS_ALTERATIONS
		__UINT32_TYPE__ st_size;
#else /* __USE_KOS_ALTERATIONS */
		__INT32_TYPE__  st_size;
#endif /* !__USE_KOS_ALTERATIONS */
		__UINT32_TYPE__ st_size32;
		__INT64_TYPE__ __st_pad2; /* This is what DOS silently does to match the
		                           * binary layout of `stat64i32' with `stat64'. */
	};
	union { __time64_t st_atime; __time64_t st_atime32; __time64_t st_atime64; };
	union { __time64_t st_mtime; __time64_t st_mtime32; __time64_t st_mtime64; };
	union { __time64_t st_ctime; __time64_t st_ctime32; __time64_t st_ctime64; };
#else /* __USE_KOS */
	union {
#ifdef __USE_KOS_ALTERATIONS
		__UINT32_TYPE__  st_size;
#else /* __USE_KOS_ALTERATIONS */
		__INT32_TYPE__   st_size;
#endif /* !__USE_KOS_ALTERATIONS */
		__INT64_TYPE__ __st_pad2; /* This is what DOS silently does to match the
		                           * binary layout of `stat64i32' with `stat64'. */
	};
	__time64_t     st_atime;
	__time64_t     st_mtime;
	__time64_t     st_ctime;
#endif /* !__USE_KOS */
};
struct __dos_stat64 {
	__uint32_t     st_dev;
	__uint16_t     st_ino;
	__uint16_t     st_mode;
	__int16_t      st_nlink;
	__int16_t      st_uid;
	__int16_t      st_gid;
	__int16_t    __st_pad0;
	__uint32_t     st_rdev;
	__int32_t    __st_pad1;
#ifdef __USE_KOS
	union {
#ifdef __USE_KOS_ALTERATIONS
		__UINT64_TYPE__ st_size;
#else /* __USE_KOS_ALTERATIONS */
		__INT64_TYPE__  st_size;
#endif /* !__USE_KOS_ALTERATIONS */
		__UINT32_TYPE__ st_size32;
		__UINT64_TYPE__ st_size64;
	};
	union { __time64_t st_atime; __time64_t st_atime32; __time64_t st_atime64; };
	union { __time64_t st_mtime; __time64_t st_mtime32; __time64_t st_mtime64; };
	union { __time64_t st_ctime; __time64_t st_ctime32; __time64_t st_ctime64; };
#else /* __USE_KOS */
#ifdef __USE_KOS_ALTERATIONS
	__UINT64_TYPE__ st_size;
#else /* __USE_KOS_ALTERATIONS */
	__INT64_TYPE__ st_size;
#endif /* !__USE_KOS_ALTERATIONS */
	__time64_t     st_atime;
	__time64_t     st_mtime;
	__time64_t     st_ctime;
#endif /* !__USE_KOS */
};
#endif /* __DEFINE_DOS_STAT_STRUCTURES */


__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_DOS_STAT_H */
