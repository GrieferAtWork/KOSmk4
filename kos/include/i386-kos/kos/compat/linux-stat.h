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
#ifndef _I386_KOS_KOS_COMPAT_LINUX_STAT_H
#define _I386_KOS_KOS_COMPAT_LINUX_STAT_H 1

#include <__stdinc.h>
#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

/* Compatibility mode structures for linux's `stat' system calls. (which KOS emulates)
 * NOTE: KOS uses different names for these system calls, but they numbers,
 *       as well as their behavior share binary compatibility:
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


/* From: https://elixir.bootlin.com/linux/latest/source/arch/x86/include/uapi/asm/stat.h#L117 */
struct linux_oldstat {
	__uint16_t st_dev;
	__uint16_t st_ino;
	__uint16_t st_mode;
	__uint16_t st_nlink;
	__uint16_t st_uid;
	__uint16_t st_gid;
	__uint16_t st_rdev;
	__uint16_t __pad;    /* Hidden padding made visible */
	__uint32_t st_size;
	__uint32_t st_atime;
	__uint32_t st_mtime;
	__uint32_t st_ctime;
};

/* From: https://elixir.bootlin.com/linux/latest/source/arch/x86/include/uapi/asm/stat.h#L10 */
struct linux_stat32 {
	__uint32_t st_dev;
	__uint32_t st_ino;
	__uint16_t st_mode;
	__uint16_t st_nlink;
	__uint16_t st_uid;
	__uint16_t st_gid;
	__uint32_t st_rdev;
	__uint32_t st_size;
	__uint32_t st_blksize;
	__uint32_t st_blocks;
	__uint32_t st_atime;
	__uint32_t st_atime_nsec;
	__uint32_t st_mtime;
	__uint32_t st_mtime_nsec;
	__uint32_t st_ctime;
	__uint32_t st_ctime_nsec;
	__uint32_t __unused4;
	__uint32_t __unused5;
};

/* From: https://elixir.bootlin.com/linux/latest/source/arch/x86/include/uapi/asm/stat.h#L42 */
struct linux_stat64 {
	__uint64_t st_dev;
	__uint8_t  __pad0[4];
	__uint32_t __st_ino;
	__uint32_t st_mode;
	__uint32_t st_nlink;
	__uint32_t st_uid;
	__uint32_t st_gid;
	__uint64_t st_rdev;
	__uint8_t  __pad3[4];
	__uint8_t  __pad4[4]; /* Hidden padding made visible */
	__int64_t  st_size;
	__uint32_t st_blksize;
	__uint8_t  __pad5[4]; /* Hidden padding made visible */
	__uint64_t st_blocks;
	__uint32_t st_atime;
	__uint32_t st_atime_nsec;
	__uint32_t st_mtime;
	__uint32_t st_mtime_nsec;
	__uint32_t st_ctime;
	__uint32_t st_ctime_nsec;
	__uint64_t st_ino;
};


__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_KOS_COMPAT_LINUX_STAT_H */
