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
#ifndef _I386_KOS_KOS_COMPAT_LINUX_STAT_CONVERT_H
#define _I386_KOS_KOS_COMPAT_LINUX_STAT_CONVERT_H 1

#include <__stdinc.h>

#include <hybrid/host.h>

#include <bits/os/kos/stat.h>
#include <kos/compat/linux-stat.h>

#ifdef __CC__
__DECL_BEGIN

__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(stat_to_linux_oldstat)(struct __kos_stat const *__restrict __self,
                                     struct linux_oldstat *__restrict __result) {
	__result->st_dev   = (__UINT16_TYPE__)__self->st_dev;
	__result->st_ino   = (__UINT16_TYPE__)__self->st_ino;
	__result->st_mode  = (__UINT16_TYPE__)__self->st_mode;
	__result->st_nlink = (__UINT16_TYPE__)__self->st_nlink;
	__result->st_uid   = (__UINT16_TYPE__)__self->st_uid;
	__result->st_gid   = (__UINT16_TYPE__)__self->st_gid;
	__result->st_rdev  = (__UINT16_TYPE__)__self->st_rdev;
	__result->st_size  = (__ULONG32_TYPE__)__self->st_size;
	__result->st_atime = (__ULONG32_TYPE__)__self->st_atime;
	__result->st_mtime = (__ULONG32_TYPE__)__self->st_mtime;
	__result->st_ctime = (__ULONG32_TYPE__)__self->st_ctime;
}

__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(stat_to_linux_statx32)(struct __kos_stat const *__restrict __self,
                                     struct linux_statx32 *__restrict __result) {
	__result->st_dev        = (__ULONG32_TYPE__)__self->st_dev;
	__result->st_ino        = (__ULONG32_TYPE__)__self->st_ino;
	__result->st_mode       = (__UINT16_TYPE__)__self->st_mode;
	__result->st_nlink      = (__UINT16_TYPE__)__self->st_nlink;
	__result->st_uid        = (__UINT16_TYPE__)__self->st_uid;
	__result->st_gid        = (__UINT16_TYPE__)__self->st_gid;
	__result->st_rdev       = (__ULONG32_TYPE__)__self->st_rdev;
	__result->st_size       = (__ULONG32_TYPE__)__self->st_size;
	__result->st_blksize    = (__ULONG32_TYPE__)__self->st_blksize;
	__result->st_blocks     = (__ULONG32_TYPE__)__self->st_blocks;
	__result->st_atime      = (__ULONG32_TYPE__)__self->st_atime;
	__result->st_atime_nsec = (__ULONG32_TYPE__)__self->st_atimensec;
	__result->st_mtime      = (__ULONG32_TYPE__)__self->st_mtime;
	__result->st_mtime_nsec = (__ULONG32_TYPE__)__self->st_mtimensec;
	__result->st_ctime      = (__ULONG32_TYPE__)__self->st_ctime;
	__result->st_ctime_nsec = (__ULONG32_TYPE__)__self->st_ctimensec;
}

__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(stat_to_linux_statx32_64)(struct __kos_stat const *__restrict __self,
                                        struct linux_statx32_64 *__restrict __result) {
	__result->st_dev        = (__ULONG64_TYPE__)__self->st_dev;
	__result->__st_ino      = (__ULONG32_TYPE__)__self->st_ino;
	__result->st_mode       = (__UINT32_TYPE__)__self->st_mode;
	__result->st_nlink      = (__UINT32_TYPE__)__self->st_nlink;
	__result->st_uid        = (__ULONG32_TYPE__)__self->st_uid;
	__result->st_gid        = (__ULONG32_TYPE__)__self->st_gid;
	__result->st_rdev       = (__ULONG64_TYPE__)__self->st_rdev;
	__result->st_size       = (__LONG64_TYPE__)__self->st_size;
	__result->st_blksize    = (__ULONG32_TYPE__)__self->st_blksize;
	__result->st_blocks     = (__ULONG64_TYPE__)__self->st_blocks;
	__result->st_atime      = (__ULONG32_TYPE__)__self->st_atime;
	__result->st_atime_nsec = (__ULONG32_TYPE__)__self->st_atimensec;
	__result->st_mtime      = (__ULONG32_TYPE__)__self->st_mtime;
	__result->st_mtime_nsec = (__UINT32_TYPE__)__self->st_mtimensec;
	__result->st_ctime      = (__ULONG32_TYPE__)__self->st_ctime;
	__result->st_ctime_nsec = (__ULONG32_TYPE__)__self->st_ctimensec;
	__result->st_ino        = (__ULONG64_TYPE__)__self->st_ino;
}

__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(stat_to_linux_statx64)(struct __kos_stat const *__restrict __self,
                                     struct linux_statx64 *__restrict __result) {
	__result->st_dev        = (__ULONG64_TYPE__)__self->st_dev;
	__result->st_ino        = (__ULONG64_TYPE__)__self->st_ino;
	__result->st_nlink      = (__ULONG64_TYPE__)__self->st_nlink;
	__result->st_mode       = (__UINT32_TYPE__)__self->st_mode;
	__result->st_uid        = (__UINT32_TYPE__)__self->st_uid;
	__result->st_gid        = (__UINT32_TYPE__)__self->st_gid;
	__result->st_rdev       = (__ULONG64_TYPE__)__self->st_rdev;
	__result->st_size       = (__LONG64_TYPE__)__self->st_size;
	__result->st_blksize    = (__LONG64_TYPE__)__self->st_blksize;
	__result->st_blocks     = (__LONG64_TYPE__)__self->st_blocks;
	__result->st_atime      = (__ULONG64_TYPE__)__self->st_atime;
	__result->st_atime_nsec = (__ULONG64_TYPE__)__self->st_atimensec;
	__result->st_mtime      = (__ULONG64_TYPE__)__self->st_mtime;
	__result->st_mtime_nsec = (__ULONG64_TYPE__)__self->st_mtimensec;
	__result->st_ctime      = (__ULONG64_TYPE__)__self->st_ctime;
	__result->st_ctime_nsec = (__ULONG64_TYPE__)__self->st_ctimensec;
}

#ifdef __x86_64__
#define stat_to_linux_stat   stat_to_linux_statx64
#define stat_to_linux_stat32 stat_to_linux_statx64
#define stat_to_linux_stat64 stat_to_linux_statx64
#else /* __x86_64__ */
#define stat_to_linux_stat   stat_to_linux_statx32
#define stat_to_linux_stat32 stat_to_linux_statx32
#define stat_to_linux_stat64 stat_to_linux_statx32_64
#endif /* !__x86_64__ */

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_KOS_COMPAT_LINUX_STAT_CONVERT_H */
