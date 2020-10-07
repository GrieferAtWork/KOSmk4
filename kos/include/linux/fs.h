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
#define BLKBSZSET    __BLKBSZSET    /* [size_t *arg] */
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

#if !defined(FS_IOC_GETFLAGS) && defined(__FS_IOC_GETFLAGS)
#define FS_IOC_GETFLAGS     __FS_IOC_GETFLAGS     /* ??? */
#endif /* !FS_IOC_GETFLAGS && __FS_IOC_GETFLAGS */
#if !defined(FS_IOC_SETFLAGS) && defined(__FS_IOC_SETFLAGS)
#define FS_IOC_SETFLAGS     __FS_IOC_SETFLAGS     /* ??? */
#endif /* !FS_IOC_SETFLAGS && __FS_IOC_SETFLAGS */
#if !defined(FS_IOC_GETVERSION) && defined(__FS_IOC_GETVERSION)
#define FS_IOC_GETVERSION   __FS_IOC_GETVERSION   /* ??? */
#endif /* !FS_IOC_GETVERSION && __FS_IOC_GETVERSION */
#if !defined(FS_IOC_SETVERSION) && defined(__FS_IOC_SETVERSION)
#define FS_IOC_SETVERSION   __FS_IOC_SETVERSION   /* ??? */
#endif /* !FS_IOC_SETVERSION && __FS_IOC_SETVERSION */
#if !defined(FS_IOC_FIEMAP) && defined(__FS_IOC_FIEMAP)
#define FS_IOC_FIEMAP       __FS_IOC_FIEMAP       /* ??? */
#endif /* !FS_IOC_FIEMAP && __FS_IOC_FIEMAP */
#if !defined(FS_IOC32_GETFLAGS) && defined(__FS_IOC32_GETFLAGS)
#define FS_IOC32_GETFLAGS   __FS_IOC32_GETFLAGS   /* ??? */
#endif /* !FS_IOC32_GETFLAGS && __FS_IOC32_GETFLAGS */
#if !defined(FS_IOC32_SETFLAGS) && defined(__FS_IOC32_SETFLAGS)
#define FS_IOC32_SETFLAGS   __FS_IOC32_SETFLAGS   /* ??? */
#endif /* !FS_IOC32_SETFLAGS && __FS_IOC32_SETFLAGS */
#if !defined(FS_IOC32_GETVERSION) && defined(__FS_IOC32_GETVERSION)
#define FS_IOC32_GETVERSION __FS_IOC32_GETVERSION /* ??? */
#endif /* !FS_IOC32_GETVERSION && __FS_IOC32_GETVERSION */
#if !defined(FS_IOC32_SETVERSION) && defined(__FS_IOC32_SETVERSION)
#define FS_IOC32_SETVERSION __FS_IOC32_SETVERSION /* ??? */
#endif /* !FS_IOC32_SETVERSION && __FS_IOC32_SETVERSION */

/* Inode flags (FS_IOC_GETFLAGS / FS_IOC_SETFLAGS) */
#if !defined(FS_SECRM_FL) && defined(__FS_SECRM_FL)
#define FS_SECRM_FL           __FS_SECRM_FL           /* ??? */
#endif /* !FS_SECRM_FL && __FS_SECRM_FL */
#if !defined(FS_UNRM_FL) && defined(__FS_UNRM_FL)
#define FS_UNRM_FL            __FS_UNRM_FL            /* ??? */
#endif /* !FS_UNRM_FL && __FS_UNRM_FL */
#if !defined(FS_COMPR_FL) && defined(__FS_COMPR_FL)
#define FS_COMPR_FL           __FS_COMPR_FL           /* ??? */
#endif /* !FS_COMPR_FL && __FS_COMPR_FL */
#if !defined(FS_SYNC_FL) && defined(__FS_SYNC_FL)
#define FS_SYNC_FL            __FS_SYNC_FL            /* ??? */
#endif /* !FS_SYNC_FL && __FS_SYNC_FL */
#if !defined(FS_IMMUTABLE_FL) && defined(__FS_IMMUTABLE_FL)
#define FS_IMMUTABLE_FL       __FS_IMMUTABLE_FL       /* ??? */
#endif /* !FS_IMMUTABLE_FL && __FS_IMMUTABLE_FL */
#if !defined(FS_APPEND_FL) && defined(__FS_APPEND_FL)
#define FS_APPEND_FL          __FS_APPEND_FL          /* ??? */
#endif /* !FS_APPEND_FL && __FS_APPEND_FL */
#if !defined(FS_NODUMP_FL) && defined(__FS_NODUMP_FL)
#define FS_NODUMP_FL          __FS_NODUMP_FL          /* ??? */
#endif /* !FS_NODUMP_FL && __FS_NODUMP_FL */
#if !defined(FS_NOATIME_FL) && defined(__FS_NOATIME_FL)
#define FS_NOATIME_FL         __FS_NOATIME_FL         /* ??? */
#endif /* !FS_NOATIME_FL && __FS_NOATIME_FL */
#if !defined(FS_DIRTY_FL) && defined(__FS_DIRTY_FL)
#define FS_DIRTY_FL           __FS_DIRTY_FL           /* for compression: ??? */
#endif /* !FS_DIRTY_FL && __FS_DIRTY_FL */
#if !defined(FS_COMPRBLK_FL) && defined(__FS_COMPRBLK_FL)
#define FS_COMPRBLK_FL        __FS_COMPRBLK_FL        /* for compression: ??? */
#endif /* !FS_COMPRBLK_FL && __FS_COMPRBLK_FL */
#if !defined(FS_NOCOMP_FL) && defined(__FS_NOCOMP_FL)
#define FS_NOCOMP_FL          __FS_NOCOMP_FL          /* for compression: ??? */
#endif /* !FS_NOCOMP_FL && __FS_NOCOMP_FL */
#if !defined(FS_ECOMPR_FL) && defined(__FS_ECOMPR_FL)
#define FS_ECOMPR_FL          __FS_ECOMPR_FL          /* for compression: ??? */
#endif /* !FS_ECOMPR_FL && __FS_ECOMPR_FL */
#if !defined(FS_BTREE_FL) && defined(__FS_BTREE_FL)
#define FS_BTREE_FL           __FS_BTREE_FL           /* ??? */
#endif /* !FS_BTREE_FL && __FS_BTREE_FL */
#if !defined(FS_INDEX_FL) && defined(__FS_INDEX_FL)
#define FS_INDEX_FL           __FS_INDEX_FL           /* ??? */
#endif /* !FS_INDEX_FL && __FS_INDEX_FL */
#if !defined(FS_IMAGIC_FL) && defined(__FS_IMAGIC_FL)
#define FS_IMAGIC_FL          __FS_IMAGIC_FL          /* ??? */
#endif /* !FS_IMAGIC_FL && __FS_IMAGIC_FL */
#if !defined(FS_JOURNAL_DATA_FL) && defined(__FS_JOURNAL_DATA_FL)
#define FS_JOURNAL_DATA_FL    __FS_JOURNAL_DATA_FL    /* ??? */
#endif /* !FS_JOURNAL_DATA_FL && __FS_JOURNAL_DATA_FL */
#if !defined(FS_NOTAIL_FL) && defined(__FS_NOTAIL_FL)
#define FS_NOTAIL_FL          __FS_NOTAIL_FL          /* ??? */
#endif /* !FS_NOTAIL_FL && __FS_NOTAIL_FL */
#if !defined(FS_DIRSYNC_FL) && defined(__FS_DIRSYNC_FL)
#define FS_DIRSYNC_FL         __FS_DIRSYNC_FL         /* ??? */
#endif /* !FS_DIRSYNC_FL && __FS_DIRSYNC_FL */
#if !defined(FS_TOPDIR_FL) && defined(__FS_TOPDIR_FL)
#define FS_TOPDIR_FL          __FS_TOPDIR_FL          /* ??? */
#endif /* !FS_TOPDIR_FL && __FS_TOPDIR_FL */
#if !defined(FS_EXTENT_FL) && defined(__FS_EXTENT_FL)
#define FS_EXTENT_FL          __FS_EXTENT_FL          /* ??? */
#endif /* !FS_EXTENT_FL && __FS_EXTENT_FL */
#if !defined(FS_DIRECTIO_FL) && defined(__FS_DIRECTIO_FL)
#define FS_DIRECTIO_FL        __FS_DIRECTIO_FL        /* ??? */
#endif /* !FS_DIRECTIO_FL && __FS_DIRECTIO_FL */
#if !defined(FS_NOCOW_FL) && defined(__FS_NOCOW_FL)
#define FS_NOCOW_FL           __FS_NOCOW_FL           /* ??? */
#endif /* !FS_NOCOW_FL && __FS_NOCOW_FL */
#if !defined(FS_PROJINHERIT_FL) && defined(__FS_PROJINHERIT_FL)
#define FS_PROJINHERIT_FL     __FS_PROJINHERIT_FL     /* ??? */
#endif /* !FS_PROJINHERIT_FL && __FS_PROJINHERIT_FL */
#if !defined(FS_RESERVED_FL) && defined(__FS_RESERVED_FL)
#define FS_RESERVED_FL        __FS_RESERVED_FL        /* ??? */
#endif /* !FS_RESERVED_FL && __FS_RESERVED_FL */
#if !defined(FS_FL_USER_VISIBLE) && defined(__FS_FL_USER_VISIBLE)
#define FS_FL_USER_VISIBLE    __FS_FL_USER_VISIBLE    /* ??? */
#endif /* !FS_FL_USER_VISIBLE && __FS_FL_USER_VISIBLE */
#if !defined(FS_FL_USER_MODIFIABLE) && defined(__FS_FL_USER_MODIFIABLE)
#define FS_FL_USER_MODIFIABLE __FS_FL_USER_MODIFIABLE /* ??? */
#endif /* !FS_FL_USER_MODIFIABLE && __FS_FL_USER_MODIFIABLE */

#endif /* _LINUX_FS_H */
