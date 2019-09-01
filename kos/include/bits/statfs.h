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
#ifndef _BITS_STATFS_H
#define _BITS_STATFS_H 1

#include <__stdinc.h>
#include <features.h>

#include <bits/types.h>

#ifdef __CC__
__SYSDECL_BEGIN

/* NOTE: Documentation taken from https://linux.die.net/man/2/fstatfs */

struct statfs {
	__syscall_ulong_t   f_type;     /* Type of file system (one of the constants from <linux/magic.h>) */
	__syscall_ulong_t   f_bsize;    /* Optimal transfer block size */
	__FS_TYPE(fsblkcnt) f_blocks;   /* Total data blocks in file system */
	__FS_TYPE(fsblkcnt) f_bfree;    /* Free blocks in fs */
	__FS_TYPE(fsblkcnt) f_bavail;   /* Free blocks available to unprivileged user */
	__FS_TYPE(fsfilcnt) f_files;    /* Total file nodes in file system */
	__FS_TYPE(fsfilcnt) f_ffree;    /* Free file nodes in fs */
	__fsid_t            f_fsid;     /* File system id */
	__syscall_ulong_t   f_namelen;  /* Maximum length of filenames */
	__syscall_ulong_t   f_frsize;   /* Fragment size (since Linux 2.6) */
	__syscall_ulong_t   f_flags;    /* Mount flags (set of `ST_*' from <sys/statvfs.h>) */
	__syscall_ulong_t   f_spare[4]; /* ??? */
};

struct __statfs32 {
	__syscall_ulong_t f_type;     /* Type of file system (one of the constants from <linux/magic.h>) */
	__syscall_ulong_t f_bsize;    /* Optimal transfer block size */
	__fsblkcnt32_t    f_blocks;   /* Total data blocks in file system */
	__fsblkcnt32_t    f_bfree;    /* Free blocks in fs */
	__fsblkcnt32_t    f_bavail;   /* Free blocks available to unprivileged user */
	__fsfilcnt32_t    f_files;    /* Total file nodes in file system */
	__fsfilcnt32_t    f_ffree;    /* Free file nodes in fs */
	__fsid_t          f_fsid;     /* File system id */
	__syscall_ulong_t f_namelen;  /* Maximum length of filenames */
	__syscall_ulong_t f_frsize;   /* Fragment size (since Linux 2.6) */
	__syscall_ulong_t f_flags;    /* Mount flags (set of `ST_*' from <sys/statvfs.h>) */
	__syscall_ulong_t f_spare[4]; /* ??? */
};

#ifdef __USE_LARGEFILE64
struct statfs64 {
	__syscall_ulong_t f_type;     /* Type of file system (one of the constants from <linux/magic.h>) */
	__syscall_ulong_t f_bsize;    /* Optimal transfer block size */
	__fsblkcnt64_t    f_blocks;   /* Total data blocks in file system */
	__fsblkcnt64_t    f_bfree;    /* Free blocks in fs */
	__fsblkcnt64_t    f_bavail;   /* Free blocks available to unprivileged user */
	__fsfilcnt64_t    f_files;    /* Total file nodes in file system */
	__fsfilcnt64_t    f_ffree;    /* Free file nodes in fs */
	__fsid_t          f_fsid;     /* File system id */
	__syscall_ulong_t f_namelen;  /* Maximum length of filenames */
	__syscall_ulong_t f_frsize;   /* Fragment size (since Linux 2.6) */
	__syscall_ulong_t f_flags;    /* Mount flags (set of `ST_*' from <sys/statvfs.h>) */
	__syscall_ulong_t f_spare[4]; /* ??? */
};
#endif /* __USE_LARGEFILE64 */

__SYSDECL_END
#endif /* __CC__ */

#define _STATFS_F_NAMELEN 1
#define _STATFS_F_FRSIZE 1
#define _STATFS_F_FLAGS 1


#endif /* !_BITS_STATFS_H */
