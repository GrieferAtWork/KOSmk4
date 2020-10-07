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
#ifndef _ASM_OS_KOS_BLOCK_H
#define _ASM_OS_KOS_BLOCK_H 1

#include <hybrid/typecore.h>

#include <asm/ioctl.h>

#define __BLKROSET      _IO(0x12, 93)  /* [int const *arg] Set device read-only (0 = read-write) */
#define __BLKROGET      _IO(0x12, 94)  /* [int *arg] Get read-only status (0 = read_write) */
#define __BLKRRPART     _IO(0x12, 95)  /* Re-read partition table */
#define __BLKGETSIZE    _IO(0x12, 96)  /* [long *arg] Return device size/512 */
#define __BLKFLSBUF     _IO(0x12, 97)  /* Flush buffer cache */
#define __BLKRASET      _IO(0x12, 98)  /* [unsigned long const *arg] Set read ahead for block device */
#define __BLKRAGET      _IO(0x12, 99)  /* [unsigned long *arg] Get current read ahead setting */
#define __BLKFRASET     _IO(0x12, 100) /* [unsigned long const *arg] Set filesystem read-ahead. */
#define __BLKFRAGET     _IO(0x12, 101) /* [unsigned long *arg] Get filesystem read-ahead. */
#define __BLKSECTSET    _IO(0x12, 102) /* [u16 const *arg] Set max sectors per request. */
#define __BLKSECTGET    _IO(0x12, 103) /* [u16 *arg] Get max sectors per request. */
#define __BLKSSZGET     _IO(0x12, 104) /* Get block device sector size */
#define __BLKBSZGET    _IOR(0x12, 112, __SIZE_TYPE__) /* [size_t *arg] */
#define __BLKBSZSET    _IOW(0x12, 113, __SIZE_TYPE__) /* [size_t *arg] */
#define __BLKGETSIZE64 _IOR(0x12, 114, __SIZE_TYPE__) /* [u64 *arg] return device size in bytes */

#define __BLKTRACESETUP    _IOWR(0x12, 115, struct blk_user_trace_setup) /* ??? */
#define __BLKTRACESTART    _IO(0x12, 116) /* ??? */
#define __BLKTRACESTOP     _IO(0x12, 117) /* ??? */
#define __BLKTRACETEARDOWN _IO(0x12, 118) /* ??? */
#define __BLKDISCARD       _IO(0x12, 119) /* ??? */
#define __BLKIOMIN         _IO(0x12, 120) /* ??? */
#define __BLKIOOPT         _IO(0x12, 121) /* ??? */
#define __BLKALIGNOFF      _IO(0x12, 122) /* ??? */
#define __BLKPBSZGET       _IO(0x12, 123) /* ??? */
#define __BLKDISCARDZEROES _IO(0x12, 124) /* ??? */
#define __BLKSECDISCARD    _IO(0x12, 125) /* ??? */
#define __BLKROTATIONAL    _IO(0x12, 126) /* ??? */
#define __BLKZEROOUT       _IO(0x12, 127) /* ??? */

#ifdef __linux__ /* TODO */
#define __FIBMAP   _IO(0x00, 1) /* [int *arg] bmap access */
#endif /* __linux__ -- TODO */
#define __FIGETBSZ _IO(0x00, 2) /* [int *arg] get the block size used for bmap */
#define __FIFREEZE _IOWR('X', 119, int) /* TODO:Freeze */
#define __FITHAW   _IOWR('X', 120, int) /* TODO:Thaw */
#define __FITRIM   _IOWR('X', 121, struct fstrim_range) /* TODO:Trim */

#ifdef __linux__ /* TODO */
#define __FS_IOC_GETFLAGS     _IOR('f', 1, long)            /* ??? */
#define __FS_IOC_SETFLAGS     _IOW('f', 2, long)            /* ??? */
#define __FS_IOC_GETVERSION   _IOR('v', 1, long)            /* ??? */
#define __FS_IOC_SETVERSION   _IOW('v', 2, long)            /* ??? */
#define __FS_IOC_FIEMAP       _IOWR('f', 11, struct fiemap) /* ??? */
#define __FS_IOC32_GETFLAGS   _IOR('f', 1, int)             /* ??? */
#define __FS_IOC32_SETFLAGS   _IOW('f', 2, int)             /* ??? */
#define __FS_IOC32_GETVERSION _IOR('v', 1, int)             /* ??? */
#define __FS_IOC32_SETVERSION _IOW('v', 2, int)             /* ??? */

/* Inode flags (FS_IOC_GETFLAGS / FS_IOC_SETFLAGS) */
#define __FS_SECRM_FL           0x00000001 /* ??? */
#define __FS_UNRM_FL            0x00000002 /* ??? */
#define __FS_COMPR_FL           0x00000004 /* ??? */
#define __FS_SYNC_FL            0x00000008 /* ??? */
#define __FS_IMMUTABLE_FL       0x00000010 /* ??? */
#define __FS_APPEND_FL          0x00000020 /* ??? */
#define __FS_NODUMP_FL          0x00000040 /* ??? */
#define __FS_NOATIME_FL         0x00000080 /* ??? */
#define __FS_DIRTY_FL           0x00000100 /* for compression: ??? */
#define __FS_COMPRBLK_FL        0x00000200 /* for compression: ??? */
#define __FS_NOCOMP_FL          0x00000400 /* for compression: ??? */
#define __FS_ECOMPR_FL          0x00000800 /* for compression: ??? */
#define __FS_BTREE_FL           0x00001000 /* ??? */
#define __FS_INDEX_FL           0x00001000 /* ??? */
#define __FS_IMAGIC_FL          0x00002000 /* ??? */
#define __FS_JOURNAL_DATA_FL    0x00004000 /* ??? */
#define __FS_NOTAIL_FL          0x00008000 /* ??? */
#define __FS_DIRSYNC_FL         0x00010000 /* ??? */
#define __FS_TOPDIR_FL          0x00020000 /* ??? */
#define __FS_EXTENT_FL          0x00080000 /* ??? */
#define __FS_DIRECTIO_FL        0x00100000 /* ??? */
#define __FS_NOCOW_FL           0x00800000 /* ??? */
#define __FS_PROJINHERIT_FL     0x20000000 /* ??? */
#define __FS_RESERVED_FL        0x80000000 /* ??? */
#define __FS_FL_USER_VISIBLE    0x0003dfff /* ??? */
#define __FS_FL_USER_MODIFIABLE 0x000380ff /* ??? */
#endif /* __linux__ -- TODO */

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("start")
#pragma push_macro("len")
#pragma push_macro("minlen")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef start
#undef len
#undef minlen
struct fstrim_range {
	__UINT64_TYPE__ start;
	__UINT64_TYPE__ len;
	__UINT64_TYPE__ minlen;
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("minlen")
#pragma pop_macro("len")
#pragma pop_macro("start")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* !_ASM_OS_KOS_BLOCK_H */
