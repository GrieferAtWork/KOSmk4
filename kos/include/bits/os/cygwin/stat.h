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
/*!replace_with_include <sys/stat.h>*/
#ifndef _BITS_OS_CYGWIN_STAT_H
#define _BITS_OS_CYGWIN_STAT_H 1

#include <__crt.h> /* __CRT_CYG_PRIMARY */
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/os/timespec.h>
#include <bits/types.h>

#ifdef __CRT_CYG_PRIMARY

#define __cyg_stat   stat

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
#define _STATBUF_ST_BLOCKS   1

#ifdef __USE_LARGEFILE64
#define __cyg_stat_alias64 stat64
#define __stat64           stat64
#else /* __USE_LARGEFILE64 */
#define __stat64 stat
#endif /* !__USE_LARGEFILE64 */

#endif /* __CRT_CYG_PRIMARY */

#ifdef __CC__
__DECL_BEGIN

struct __cyg_stat {
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

	/* struct __timespec64 st_atimespec64; */
	/* +48  */ union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec64   st_atim64;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64   st_atimespec64;
		struct {
			__time64_t        st_atime64;
			__syscall_ulong_t st_atimensec64;
		};
#endif /* __USE_KOS */
#ifdef __USE_XOPEN2K8
		struct __timespec64   st_atim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64   st_atimespec;
		struct {
			__time64_t        st_atime;
			__syscall_ulong_t st_atimensec;
		};
	};

	/* struct __timespec64 st_atimespec64; */
	/* +64  */ union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec64   st_mtim64;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64   st_mtimespec64;
		struct {
			__time64_t        st_mtime64;
			__syscall_ulong_t st_mtimensec64;
		};
#endif /* __USE_KOS */
#ifdef __USE_XOPEN2K8
		struct __timespec64   st_mtim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64   st_mtimespec;
		struct {
			__time64_t        st_mtime;
			__syscall_ulong_t st_mtimensec;
		};
	};

	/* struct __timespec64 st_ctimespec64; */
	/* +80  */ union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec64   st_ctim64;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64   st_ctimespec64;
		struct {
			__time64_t        st_ctime64;
			__syscall_ulong_t st_ctimensec64;
		};
#endif /* __USE_KOS */
#ifdef __USE_XOPEN2K8
		struct __timespec64   st_ctim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64   st_ctimespec;
		struct {
			__time64_t        st_ctime;
			__syscall_ulong_t st_ctimensec;
		};
	};

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
	/* +112 */ union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec64   st_birthtim64;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64   st_birthtimespec64;
		struct {
			__time64_t        st_birthtime64;
			__syscall_ulong_t st_birthtimensec64;
		};
#endif /* __USE_KOS */
#ifdef __USE_XOPEN2K8
		struct __timespec64   st_birthtim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64   st_birthtimespec;
		struct {
			__time64_t        st_birthtime;
			__syscall_ulong_t st_birthtimensec;
		};
	};
};


#ifdef __cyg_stat_alias64
struct __cyg_stat_alias64 {
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

	/* struct __timespec64 st_atimespec64; */
	/* +48  */ union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec64   st_atim64;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64   st_atimespec64;
		struct {
			__time64_t        st_atime64;
			__syscall_ulong_t st_atimensec64;
		};
#endif /* __USE_KOS */
#ifdef __USE_XOPEN2K8
		struct __timespec64   st_atim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64   st_atimespec;
		struct {
			__time64_t        st_atime;
			__syscall_ulong_t st_atimensec;
		};
	};

	/* struct __timespec64 st_atimespec64; */
	/* +64  */ union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec64   st_mtim64;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64   st_mtimespec64;
		struct {
			__time64_t        st_mtime64;
			__syscall_ulong_t st_mtimensec64;
		};
#endif /* __USE_KOS */
#ifdef __USE_XOPEN2K8
		struct __timespec64   st_mtim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64   st_mtimespec;
		struct {
			__time64_t        st_mtime;
			__syscall_ulong_t st_mtimensec;
		};
	};

	/* struct __timespec64 st_ctimespec64; */
	/* +80  */ union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec64   st_ctim64;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64   st_ctimespec64;
		struct {
			__time64_t        st_ctime64;
			__syscall_ulong_t st_ctimensec64;
		};
#endif /* __USE_KOS */
#ifdef __USE_XOPEN2K8
		struct __timespec64   st_ctim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64   st_ctimespec;
		struct {
			__time64_t        st_ctime;
			__syscall_ulong_t st_ctimensec;
		};
	};

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
	/* +112 */ union {
#ifdef __USE_KOS
#ifdef __USE_XOPEN2K8
		struct __timespec64   st_birthtim64;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64   st_birthtimespec64;
		struct {
			__time64_t        st_birthtime64;
			__syscall_ulong_t st_birthtimensec64;
		};
#endif /* __USE_KOS */
#ifdef __USE_XOPEN2K8
		struct __timespec64   st_birthtim;
#endif /* __USE_XOPEN2K8 */
		struct __timespec64   st_birthtimespec;
		struct {
			__time64_t        st_birthtime;
			__syscall_ulong_t st_birthtimensec;
		};
	};
};
#endif /* __cyg_stat_alias64 */


__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_CYGWIN_STAT_H */
