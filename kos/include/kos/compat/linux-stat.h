/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_COMPAT_LINUX_STAT_H
#define _KOS_COMPAT_LINUX_STAT_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

/* Compatibility mode structures for linux's `stat' system calls. (which KOS emulates)
 * NOTE: KOS uses  different names  for these  system calls,  but  they
 *       numbers, as well as their behavior share binary compatibility:
 *
 *    - linux:`struct __old_kernel_stat' --> kos:`struct linux_oldstat'
 *    - linux:`__NR_oldstat'             --> kos:`__NR_linux_oldstat'
 *    - linux:`__NR_oldfstat'            --> kos:`__NR_linux_oldfstat'
 *    - linux:`__NR_oldlstat'            --> kos:`__NR_linux_oldlstat'
 *
 *    - linux:`struct stat'              --> kos:`struct linux_stat32'
 *    - linux:`__NR_stat'                --> kos:`__NR_linux_stat32'
 *    - linux:`__NR_fstat'               --> kos:`__NR_linux_fstat32'
 *    - linux:`__NR_lstat'               --> kos:`__NR_linux_lstat32'
 *    - linux:`__NR_newfstatat'          --> kos:`__NR_linux_fstatat32' (Only available on x86_64?)
 *
 *    - linux:`struct stat64'            --> kos:`struct linux_stat64'
 *    - linux:`__NR_stat64'              --> kos:`__NUR_linux_stat64'
 *    - linux:`__NR_lstat64'             --> kos:`__NUR_linux_lstat64'
 *    - linux:`__NR_fstat64'             --> kos:`__NUR_linux_fstat64'
 *    - linux:`__NR_fstatat64'           --> kos:`__NUR_linux_fstatat64'
 */

struct linux_oldstat {
	__UINT16_TYPE__  st_dev;
	__UINT16_TYPE__  st_ino;
	__UINT16_TYPE__  st_mode;
	__UINT16_TYPE__  st_nlink;
	__UINT16_TYPE__  st_uid;
	__UINT16_TYPE__  st_gid;
	__UINT16_TYPE__  st_rdev;
	__UINT16_TYPE__  __pad;    /* Hidden padding made visible */
	__ULONG32_TYPE__ st_size;
	__ULONG32_TYPE__ st_atime;
	__ULONG32_TYPE__ st_mtime;
	__ULONG32_TYPE__ st_ctime;
};

#define linux_stat linux_stat32

struct linux_stat32 {
	__ULONG32_TYPE__ st_dev;
	__ULONG32_TYPE__ st_ino;
	__UINT16_TYPE__  st_mode;
	__UINT16_TYPE__  st_nlink;
	__UINT16_TYPE__  st_uid;
	__UINT16_TYPE__  st_gid;
	__ULONG32_TYPE__ st_rdev;
	__ULONG32_TYPE__ st_size;
	__ULONG32_TYPE__ st_blksize;
	__ULONG32_TYPE__ st_blocks;
	__ULONG32_TYPE__ st_atime;
	__ULONG32_TYPE__ st_atime_nsec;
	__ULONG32_TYPE__ st_mtime;
	__ULONG32_TYPE__ st_mtime_nsec;
	__ULONG32_TYPE__ st_ctime;
	__ULONG32_TYPE__ st_ctime_nsec;
	__ULONG32_TYPE__ __unused4;
	__ULONG32_TYPE__ __unused5;
};

struct linux_stat64 {
	__ULONG64_TYPE__ st_dev;
	__BYTE_TYPE__    __pad0[4];
	__ULONG32_TYPE__ __st_ino;
#define _HAVE_LINUX_STAT64___ST_INO
	__UINT32_TYPE__  st_mode;
	__UINT32_TYPE__  st_nlink;
	__ULONG32_TYPE__ st_uid;
	__ULONG32_TYPE__ st_gid;
	__ULONG64_TYPE__ st_rdev;
	__BYTE_TYPE__    __pad3[4];
	__BYTE_TYPE__    __pad4[4]; /* Hidden padding made visible */
	__LONG64_TYPE__  st_size;
	__ULONG32_TYPE__ st_blksize;
	__BYTE_TYPE__    __pad5[4]; /* Hidden padding made visible */
	__ULONG64_TYPE__ st_blocks;
	__ULONG32_TYPE__ st_atime;
	__ULONG32_TYPE__ st_atime_nsec;
	__ULONG32_TYPE__ st_mtime;
	__UINT32_TYPE__  st_mtime_nsec;
	__ULONG32_TYPE__ st_ctime;
	__ULONG32_TYPE__ st_ctime_nsec;
	__ULONG64_TYPE__ st_ino;
};

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_COMPAT_LINUX_STAT_H */
