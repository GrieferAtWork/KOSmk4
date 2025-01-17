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
#ifndef _BITS_OS_KOS_STATVFS_H
#define _BITS_OS_KOS_STATVFS_H 1

#include <__stdinc.h>
#include <features.h>

#include <bits/types.h>

#if __SIZEOF_SYSCALL_LONG_T__ == 4
#define _STATVFSBUF_F_UNUSED 1
#endif /* __SIZEOF_SYSCALL_LONG_T__ == 4 */

#ifdef __CC__
__DECL_BEGIN

struct statvfs {
	__ULONGPTR_TYPE__   f_bsize;    /* ??? */
	__ULONGPTR_TYPE__   f_frsize;   /* ??? */
	__fsblkcnt_t        f_blocks;   /* ??? */
	__fsblkcnt_t        f_bfree;    /* ??? */
	__fsblkcnt_t        f_bavail;   /* ??? */
	__fsfilcnt_t        f_files;    /* ??? */
	__fsfilcnt_t        f_ffree;    /* ??? */
	__fsfilcnt_t        f_favail;   /* ??? */
	__ULONGPTR_TYPE__   f_fsid;     /* ??? */
#ifdef _STATVFSBUF_F_UNUSED
	__ULONGPTR_TYPE__ __f_unused;   /* ... */
//	__INT32_TYPE__    __f_unused;
#endif /* _STATVFSBUF_F_UNUSED */
	__ULONGPTR_TYPE__   f_flag;     /* ??? */
	__ULONGPTR_TYPE__   f_namemax;  /* ??? */
	__INT32_TYPE__    __f_spare[6]; /* ... */
};

#ifdef __USE_LARGEFILE64
struct statvfs64 {
	__ULONGPTR_TYPE__   f_bsize;    /* ??? */
	__ULONGPTR_TYPE__   f_frsize;   /* ??? */
	__fsblkcnt64_t      f_blocks;   /* ??? */
	__fsblkcnt64_t      f_bfree;    /* ??? */
	__fsblkcnt64_t      f_bavail;   /* ??? */
	__fsfilcnt64_t      f_files;    /* ??? */
	__fsfilcnt64_t      f_ffree;    /* ??? */
	__fsfilcnt64_t      f_favail;   /* ??? */
	__ULONGPTR_TYPE__   f_fsid;     /* ??? */
#ifdef _STATVFSBUF_F_UNUSED
	__ULONGPTR_TYPE__ __f_unused;   /* ... */
//	__INT32_TYPE__    __f_unused;
#endif /* _STATVFSBUF_F_UNUSED */
	__ULONGPTR_TYPE__   f_flag;     /* ??? */
	__ULONGPTR_TYPE__   f_namemax;  /* ??? */
	__INT32_TYPE__    __f_spare[6]; /* ... */
};
#endif /* __USE_LARGEFILE64 */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_KOS_STATVFS_H */
