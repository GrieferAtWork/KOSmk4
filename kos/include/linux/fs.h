/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LINUX_FS_H
#define _LINUX_FS_H 1

#include <__stdinc.h>
#include <linux/ioctl.h>
#include <linux/types.h>

__DECL_BEGIN

#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("start")
#pragma push_macro("len")
#pragma push_macro("minlen")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef start
#undef len
#undef minlen
struct fstrim_range {
	__u64 start;
	__u64 len;
	__u64 minlen;
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("minlen")
#pragma pop_macro("len")
#pragma pop_macro("start")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __CC__ */

/* NOTE: These ioctls can also be found in <sys/mount.h> */
#ifndef BLKROSET
#define BLKROSET      _IO(0x12, 93)  /* [int const *arg] Set device read-only (0 = read-write) */
#define BLKROGET      _IO(0x12, 94)  /* [int *arg] Get read-only status (0 = read_write) */
#define BLKRRPART     _IO(0x12, 95)  /* Re-read partition table */
#define BLKGETSIZE    _IO(0x12, 96)  /* [long *arg] Return device size/512 */
#define BLKFLSBUF     _IO(0x12, 97)  /* Flush buffer cache */
#define BLKRASET      _IO(0x12, 98)  /* [unsigned long const *arg] Set read ahead for block device */
#define BLKRAGET      _IO(0x12, 99)  /* [unsigned long *arg] Get current read ahead setting */
#define BLKFRASET     _IO(0x12, 100) /* [unsigned long const *arg] Set filesystem read-ahead. */
#define BLKFRAGET     _IO(0x12, 101) /* [unsigned long *arg] Get filesystem read-ahead. */
#define BLKSECTSET    _IO(0x12, 102) /* [u16 const *arg] Set max sectors per request. */
#define BLKSECTGET    _IO(0x12, 103) /* [u16 *arg] Get max sectors per request. */
#define BLKSSZGET     _IO(0x12, 104) /* Get block device sector size */
#define BLKBSZGET    _IOR(0x12, 112, size_t) /* [size_t *arg] */
#define BLKBSZSET    _IOW(0x12, 113, size_t) /* [size_t *arg] */
#define BLKGETSIZE64 _IOR(0x12, 114, size_t) /* [u64 *arg] return device size in bytes */
#endif /* !BLKROSET */

#define BLKTRACESETUP    _IOWR(0x12, 115, struct blk_user_trace_setup)
#define BLKTRACESTART    _IO(0x12, 116)
#define BLKTRACESTOP     _IO(0x12, 117)
#define BLKTRACETEARDOWN _IO(0x12, 118)
#define BLKDISCARD       _IO(0x12, 119)
#define BLKIOMIN         _IO(0x12, 120)
#define BLKIOOPT         _IO(0x12, 121)
#define BLKALIGNOFF      _IO(0x12, 122)
#define BLKPBSZGET       _IO(0x12, 123)
#define BLKDISCARDZEROES _IO(0x12, 124)
#define BLKSECDISCARD    _IO(0x12, 125)
#define BLKROTATIONAL    _IO(0x12, 126)
#define BLKZEROOUT       _IO(0x12, 127)


#if 0 /* TODO */
#define FIBMAP   _IO(0x00, 1) /* [int *arg] bmap access */
#endif
#define FIGETBSZ _IO(0x00, 2) /* [int *arg] get the block size used for bmap */
#define FIFREEZE _IOWR('X', 119, int) /* TODO:Freeze */
#define FITHAW   _IOWR('X', 120, int) /* TODO:Thaw */
#define FITRIM   _IOWR('X', 121, struct fstrim_range) /* TODO:Trim */

#if 0 /* TODO */
#define FS_IOC_GETFLAGS     _IOR('f', 1, long)
#define FS_IOC_SETFLAGS     _IOW('f', 2, long)
#define FS_IOC_GETVERSION   _IOR('v', 1, long)
#define FS_IOC_SETVERSION   _IOW('v', 2, long)
#define FS_IOC_FIEMAP       _IOWR('f', 11, struct fiemap)
#define FS_IOC32_GETFLAGS   _IOR('f', 1, int)
#define FS_IOC32_SETFLAGS   _IOW('f', 2, int)
#define FS_IOC32_GETVERSION _IOR('v', 1, int)
#define FS_IOC32_SETVERSION _IOW('v', 2, int)

/* Inode flags (FS_IOC_GETFLAGS / FS_IOC_SETFLAGS) */
#define FS_SECRM_FL           0x00000001 /* Secure deletion */
#define FS_UNRM_FL            0x00000002 /* Undelete */
#define FS_COMPR_FL           0x00000004 /* Compress file */
#define FS_SYNC_FL            0x00000008 /* Synchronous updates */
#define FS_IMMUTABLE_FL       0x00000010 /* Immutable file */
#define FS_APPEND_FL          0x00000020 /* writes to file may only append */
#define FS_NODUMP_FL          0x00000040 /* do not dump file */
#define FS_NOATIME_FL         0x00000080 /* do not update atime */
/* Reserved for compression usage... */
#define FS_DIRTY_FL           0x00000100
#define FS_COMPRBLK_FL        0x00000200 /* One or more compressed clusters */
#define FS_NOCOMP_FL          0x00000400 /* Don't compress */
#define FS_ECOMPR_FL          0x00000800 /* Compression error */
/* End compression flags --- maybe not all used */
#define FS_BTREE_FL           0x00001000 /* btree format dir */
#define FS_INDEX_FL           0x00001000 /* hash-indexed directory */
#define FS_IMAGIC_FL          0x00002000 /* AFS directory */
#define FS_JOURNAL_DATA_FL    0x00004000 /* Reserved for ext3 */
#define FS_NOTAIL_FL          0x00008000 /* file tail should not be merged */
#define FS_DIRSYNC_FL         0x00010000 /* dirsync behaviour (directories only) */
#define FS_TOPDIR_FL          0x00020000 /* Top of directory hierarchies*/
#define FS_EXTENT_FL          0x00080000 /* Extents */
#define FS_DIRECTIO_FL        0x00100000 /* Use direct i/o */
#define FS_NOCOW_FL           0x00800000 /* Do not cow file */
#define FS_PROJINHERIT_FL     0x20000000 /* Create with parents projid */
#define FS_RESERVED_FL        0x80000000 /* reserved for ext2 lib */
#define FS_FL_USER_VISIBLE    0x0003dfff /* User visible flags */
#define FS_FL_USER_MODIFIABLE 0x000380ff /* User modifiable flags */
#endif

__DECL_END

#endif /* _LINUX_FS_H */
