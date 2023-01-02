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
/* (#) Portability: Linux (/usr/include/linux/fs.h) */
#ifndef _LINUX_FS_H
#define _LINUX_FS_H 1

#include <__stdinc.h>

#include <asm/ioctl.h>
#include <asm/os/block.h>
#include <linux/types.h>

#if !defined(BLKROSET) && defined(__BLKROSET)
#define BLKROSET     __BLKROSET     /* [int const *arg] Set device read-only (0 = read-write) */
#endif /* !BLKROSET && __BLKROSET */
#if !defined(BLKROGET) && defined(__BLKROGET)
#define BLKROGET     __BLKROGET     /* [int *arg] Get read-only status (0 = read_write) */
#endif /* !BLKROGET && __BLKROGET */
#if !defined(BLKRRPART) && defined(__BLKRRPART)
#define BLKRRPART    __BLKRRPART    /* Re-read partition table */
#endif /* !BLKRRPART && __BLKRRPART */
#if !defined(BLKGETSIZE) && defined(__BLKGETSIZE)
#define BLKGETSIZE   __BLKGETSIZE   /* [long *arg] Return device size/512 */
#endif /* !BLKGETSIZE && __BLKGETSIZE */
#if !defined(BLKFLSBUF) && defined(__BLKFLSBUF)
#define BLKFLSBUF    __BLKFLSBUF    /* Flush buffer cache */
#endif /* !BLKFLSBUF && __BLKFLSBUF */
#if !defined(BLKRASET) && defined(__BLKRASET)
#define BLKRASET     __BLKRASET     /* [unsigned long const *arg] Set read ahead for block device */
#endif /* !BLKRASET && __BLKRASET */
#if !defined(BLKRAGET) && defined(__BLKRAGET)
#define BLKRAGET     __BLKRAGET     /* [unsigned long *arg] Get current read ahead setting */
#endif /* !BLKRAGET && __BLKRAGET */
#if !defined(BLKFRASET) && defined(__BLKFRASET)
#define BLKFRASET    __BLKFRASET    /* [unsigned long const *arg] Set filesystem read-ahead. */
#endif /* !BLKFRASET && __BLKFRASET */
#if !defined(BLKFRAGET) && defined(__BLKFRAGET)
#define BLKFRAGET    __BLKFRAGET    /* [unsigned long *arg] Get filesystem read-ahead. */
#endif /* !BLKFRAGET && __BLKFRAGET */
#if !defined(BLKSECTSET) && defined(__BLKSECTSET)
#define BLKSECTSET   __BLKSECTSET   /* [u16 const *arg] Set max sectors per request. */
#endif /* !BLKSECTSET && __BLKSECTSET */
#if !defined(BLKSECTGET) && defined(__BLKSECTGET)
#define BLKSECTGET   __BLKSECTGET   /* [u16 *arg] Get max sectors per request. */
#endif /* !BLKSECTGET && __BLKSECTGET */
#if !defined(BLKSSZGET) && defined(__BLKSSZGET)
#define BLKSSZGET    __BLKSSZGET    /* Get block device sector size */
#endif /* !BLKSSZGET && __BLKSSZGET */
#if !defined(BLKBSZGET) && defined(__BLKBSZGET)
#define BLKBSZGET    __BLKBSZGET    /* [size_t *arg] */
#endif /* !BLKBSZGET && __BLKBSZGET */
#if !defined(BLKBSZSET) && defined(__BLKBSZSET)
#define BLKBSZSET    __BLKBSZSET    /* [size_t const *arg] */
#endif /* !BLKBSZSET && __BLKBSZSET */
#if !defined(BLKGETSIZE64) && defined(__BLKGETSIZE64)
#define BLKGETSIZE64 __BLKGETSIZE64 /* [u64 *arg] return device size in bytes */
#endif /* !BLKGETSIZE64 && __BLKGETSIZE64 */

#if !defined(BLKTRACESETUP) && defined(__BLKTRACESETUP)
#define BLKTRACESETUP    __BLKTRACESETUP    /* ??? */
#endif /* !BLKTRACESETUP && __BLKTRACESETUP */
#if !defined(BLKTRACESTART) && defined(__BLKTRACESTART)
#define BLKTRACESTART    __BLKTRACESTART    /* ??? */
#endif /* !BLKTRACESTART && __BLKTRACESTART */
#if !defined(BLKTRACESTOP) && defined(__BLKTRACESTOP)
#define BLKTRACESTOP     __BLKTRACESTOP     /* ??? */
#endif /* !BLKTRACESTOP && __BLKTRACESTOP */
#if !defined(BLKTRACETEARDOWN) && defined(__BLKTRACETEARDOWN)
#define BLKTRACETEARDOWN __BLKTRACETEARDOWN /* ??? */
#endif /* !BLKTRACETEARDOWN && __BLKTRACETEARDOWN */
#if !defined(BLKDISCARD) && defined(__BLKDISCARD)
#define BLKDISCARD       __BLKDISCARD       /* ??? */
#endif /* !BLKDISCARD && __BLKDISCARD */
#if !defined(BLKIOMIN) && defined(__BLKIOMIN)
#define BLKIOMIN         __BLKIOMIN         /* ??? */
#endif /* !BLKIOMIN && __BLKIOMIN */
#if !defined(BLKIOOPT) && defined(__BLKIOOPT)
#define BLKIOOPT         __BLKIOOPT         /* ??? */
#endif /* !BLKIOOPT && __BLKIOOPT */
#if !defined(BLKALIGNOFF) && defined(__BLKALIGNOFF)
#define BLKALIGNOFF      __BLKALIGNOFF      /* ??? */
#endif /* !BLKALIGNOFF && __BLKALIGNOFF */
#if !defined(BLKPBSZGET) && defined(__BLKPBSZGET)
#define BLKPBSZGET       __BLKPBSZGET       /* ??? */
#endif /* !BLKPBSZGET && __BLKPBSZGET */
#if !defined(BLKDISCARDZEROES) && defined(__BLKDISCARDZEROES)
#define BLKDISCARDZEROES __BLKDISCARDZEROES /* ??? */
#endif /* !BLKDISCARDZEROES && __BLKDISCARDZEROES */
#if !defined(BLKSECDISCARD) && defined(__BLKSECDISCARD)
#define BLKSECDISCARD    __BLKSECDISCARD    /* ??? */
#endif /* !BLKSECDISCARD && __BLKSECDISCARD */
#if !defined(BLKROTATIONAL) && defined(__BLKROTATIONAL)
#define BLKROTATIONAL    __BLKROTATIONAL    /* ??? */
#endif /* !BLKROTATIONAL && __BLKROTATIONAL */
#if !defined(BLKZEROOUT) && defined(__BLKZEROOUT)
#define BLKZEROOUT       __BLKZEROOUT       /* ??? */
#endif /* !BLKZEROOUT && __BLKZEROOUT */

#if !defined(FIBMAP) && defined(__FIBMAP)
#define FIBMAP   __FIBMAP   /* [int *arg] bmap access */
#endif /* !FIBMAP && __FIBMAP */
#if !defined(FIGETBSZ) && defined(__FIGETBSZ)
#define FIGETBSZ __FIGETBSZ /* [int *arg] get the block size used for bmap */
#endif /* !FIGETBSZ && __FIGETBSZ */
#if !defined(FIFREEZE) && defined(__FIFREEZE)
#define FIFREEZE __FIFREEZE /* TODO:Freeze */
#endif /* !FIFREEZE && __FIFREEZE */
#if !defined(FITHAW) && defined(__FITHAW)
#define FITHAW   __FITHAW   /* TODO:Thaw */
#endif /* !FITHAW && __FITHAW */
#if !defined(FITRIM) && defined(__FITRIM)
#define FITRIM   __FITRIM   /* TODO:Trim */
#endif /* !FITRIM && __FITRIM */

#if defined(__linux__) || defined(__KOS__)
#define FS_IOC_GETFLAGS     _IOR('f', 1, long) /* Get INode flags (set of `FS_*') */
#define FS_IOC_SETFLAGS     _IOW('f', 2, long) /* Set INode flags (set of `FS_*') */
#define FS_IOC32_GETFLAGS   _IOR('f', 1, int)  /* Get INode flags (set of `FS_*') */
#define FS_IOC32_SETFLAGS   _IOW('f', 2, int)  /* Set INode flags (set of `FS_*') */

#ifdef __linux__ /* XXX: KOS? */
#define FS_IOC_GETVERSION   _IOR('v', 1, long)            /* ??? */
#define FS_IOC_SETVERSION   _IOW('v', 2, long)            /* ??? */
#define FS_IOC32_GETVERSION _IOR('v', 1, int)             /* ??? */
#define FS_IOC32_SETVERSION _IOW('v', 2, int)             /* ??? */
#define FS_IOC_FIEMAP       _IOWR('f', 11, struct fiemap) /* ??? */
#define FS_IOC_FSGETXATTR   _IOR('X', 31, struct fsxattr) /* ??? */
#define FS_IOC_FSSETXATTR   _IOW('X', 32, struct fsxattr) /* ??? */
#endif /* __linux__ */

#define FSLABEL_MAX       256 /* Max chars for the interface; each fs may differ */
#define FS_IOC_GETFSLABEL _IOR(0x94, 49, char[FSLABEL_MAX]) /* Get volume label */
#define FS_IOC_SETFSLABEL _IOW(0x94, 50, char[FSLABEL_MAX]) /* Set volume label */


/* Inode flags (FS_IOC_GETFLAGS / FS_IOC_SETFLAGS)
 * These  flags are no  necessarily persistent; once  the associate mfile is
 * unloaded due to no-one holding any more references, the next time another
 * access is made, these flags are set based on superblock mount flags! */
#define FS_SECRM_FL           0x00000001 /* 's': Ignored. */
#define FS_UNRM_FL            0x00000002 /* 'u': Ignored. */
#define FS_COMPR_FL           0x00000004 /* 'c': [KOS:Unsupported] Store on-disk in compressed format (if supported by FS) */
#define FS_SYNC_FL            0x00000008 /* 'S': [KOS:Unsupported] Per-file state of `MS_SYNC' */
#define FS_IMMUTABLE_FL       0x00000010 /* 'i': `MFILE_F_READONLY | MFILE_FN_ATTRREADONLY' (need `CAP_LINUX_IMMUTABLE' to modify) */
#define FS_APPEND_FL          0x00000020 /* 'a': [KOS:Unsupported] File can only be opened with O_APPEND */
#define FS_NODUMP_FL          0x00000040 /* 'd': [KOS:Unsupported] Don't include in backups by `dump(8)'. */
#define FS_NOATIME_FL         0x00000080 /* 'A': `MFILE_F_NOATIME' */
#define FS_DIRTY_FL           0x00000100 /* ??? */
#define FS_COMPRBLK_FL        0x00000200 /* ??? */
#define FS_NOCOMP_FL          0x00000400 /* ??? */
#define FS_ECOMPR_FL          0x00000800 /* ??? */
#define FS_BTREE_FL           0x00001000 /* ??? */
#define FS_INDEX_FL           0x00001000 /* ??? */
#define FS_IMAGIC_FL          0x00002000 /* ??? */
#define FS_JOURNAL_DATA_FL    0x00004000 /* 'j': [KOS:Unsupported] Enable/disable journaling on a per-file basis. */
#define FS_NOTAIL_FL          0x00008000 /* 't': [KOS:Unsupported] Disable Reiserfs tail-packing feature (if supported by FS) */
#define FS_DIRSYNC_FL         0x00010000 /* 'D': [KOS:Unsupported] Per-directory state of `MS_DIRSYNC' */
#define FS_TOPDIR_FL          0x00020000 /* 'T': [KOS:Unsupported] ??? */
/*      FS_                   0x00040000  * ... */
#define FS_EXTENT_FL          0x00080000 /* ??? */
#define FS_DIRECTIO_FL        0x00100000 /* ??? */
/*      FS_                   0x00200000  * ... */
/*      FS_                   0x00400000  * ... */
#define FS_NOCOW_FL           0x00800000 /* 'C': [KOS:Unsupported] Disable copy-on-write (if supported by FS) */
/*      FS_                   0x01000000  * ... */
/*      FS_                   0x02000000  * ... */
/*      FS_                   0x04000000  * ... */
/*      FS_                   0x08000000  * ... */
/*      FS_                   0x10000000  * ... */
#define FS_PROJINHERIT_FL     0x20000000 /* 'P': [KOS:Unsupported] Inherit the quota project ID (???) */
/*      FS_                   0x40000000  * ... */
#define FS_RESERVED_FL        0x80000000 /* ??? */
#define FS_FL_USER_VISIBLE    0x0003dfff /* ??? */
#define FS_FL_USER_MODIFIABLE 0x000380ff /* ??? */
#endif /* __linux__ || __KOS__ */

#endif /* _LINUX_FS_H */
