/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_OS_GENERIC_STAT_H
#define _BITS_OS_GENERIC_STAT_H 1

#include <__crt.h> /* __CRT_GENERIC */
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/os/timespec.h>
#include <bits/types.h>

#ifdef __CRT_GENERIC


#define _STATBUF_ST_TIME     1 /* Always defined. */
#define _STATBUF_ST_BLKSIZE  1
#define _STATBUF_ST_RDEV     1
#define _STATBUF_ST_BLOCKS   1

#define __gen_stat stat
#ifdef __USE_LARGEFILE64
#define __gen_stat64 stat64
#define __stat64     stat64
#else /* __USE_LARGEFILE64 */
#define __stat64 __gen_stat64
#endif /* !__USE_LARGEFILE64 */

#endif /* __CRT_GENERIC */

#ifdef __CC__
__DECL_BEGIN

struct __gen_stat {
#ifdef __CRT_HAVE_stat64
	__dev_t           st_dev;     /* ID of device containing file */
	__ino_t           st_ino;     /* inode number */
	__mode_t          st_mode;    /* protection */
	__nlink_t         st_nlink;   /* number of hard links */
	__uid_t           st_uid;     /* user ID of owner */
	__gid_t           st_gid;     /* group ID of owner */
	__dev_t           st_rdev;    /* device ID (if special file) */
	__off_t           st_size;    /* total size, in bytes */
	__blksize_t       st_blksize; /* blocksize for file system I/O */
	__blkcnt_t        st_blocks;  /* number of 512B blocks allocated */
	__time32_t        st_atime;   /* time of last access */
	__time32_t        st_mtime;   /* time of last modification */
	__time32_t        st_ctime;   /* time of last status change */
#else /* 64-bit support */
	__dev_t           st_dev;     /* ID of device containing file */
	__ino32_t         st_ino;     /* inode number */
	__mode_t          st_mode;    /* protection */
	__nlink_t         st_nlink;   /* number of hard links */
	__uid_t           st_uid;     /* user ID of owner */
	__gid_t           st_gid;     /* group ID of owner */
	__dev_t           st_rdev;    /* device ID (if special file) */
	__off32_t         st_size;    /* total size, in bytes */
	__blksize_t       st_blksize; /* blocksize for file system I/O */
	__blkcnt32_t      st_blocks;  /* number of 512B blocks allocated */
	__time32_t        st_atime;   /* time of last access */
	__time32_t        st_mtime;   /* time of last modification */
	__time32_t        st_ctime;   /* time of last status change */
#endif /* no 64-bit support */
};

struct __gen_stat64 {
#ifdef __CRT_HAVE_stat64
	__dev_t           st_dev;     /* ID of device containing file */
	__ino64_t         st_ino;     /* inode number */
	__mode_t          st_mode;    /* protection */
	__nlink_t         st_nlink;   /* number of hard links */
	__uid_t           st_uid;     /* user ID of owner */
	__gid_t           st_gid;     /* group ID of owner */
	__dev_t           st_rdev;    /* device ID (if special file) */
	__off64_t         st_size;    /* total size, in bytes */
	__blksize_t       st_blksize; /* blocksize for file system I/O */
	__blkcnt64_t      st_blocks;  /* number of 512B blocks allocated */
	__time32_t        st_atime;   /* time of last access */
	__time32_t        st_mtime;   /* time of last modification */
	__time32_t        st_ctime;   /* time of last status change */
#else /* 64-bit support */
	__dev_t           st_dev;     /* ID of device containing file */
	__ino32_t         st_ino;     /* inode number */
	__mode_t          st_mode;    /* protection */
	__nlink_t         st_nlink;   /* number of hard links */
	__uid_t           st_uid;     /* user ID of owner */
	__gid_t           st_gid;     /* group ID of owner */
	__dev_t           st_rdev;    /* device ID (if special file) */
	__off32_t         st_size;    /* total size, in bytes */
	__blksize_t       st_blksize; /* blocksize for file system I/O */
	__blkcnt32_t      st_blocks;  /* number of 512B blocks allocated */
	__time32_t        st_atime;   /* time of last access */
	__time32_t        st_mtime;   /* time of last modification */
	__time32_t        st_ctime;   /* time of last status change */
#endif /* no 64-bit support */
};


__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_GENERIC_STAT_H */
