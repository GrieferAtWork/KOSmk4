/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_HOP_MFILE_H
#define _KOS_HOP_MFILE_H 1

#include "api.h"

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#include "openfd.h"

__DECL_BEGIN

#define HOP_SUPERBLOCK_FEAT_NORMAL   0x00000000
#define HOP_SUPERBLOCK_FEAT_SYMLINKS 0x00000001 /* The filesystem supports symbolic links (when clear, `sbs_symlink_max' is `0')
                                                 * s.a.: `pathconf(_PC_2_SYMLINKS)' */
#define HOP_SUPERBLOCK_FEAT_HRDLINKS 0x00000002 /* The filesystem supports hard links (when clear, `sbs_link_max' is `1') */

#define __OFFSET_HOP_SUPERBLOCK_FEATURES_STRUCT_SIZE        0
#define __OFFSET_HOP_SUPERBLOCK_FEATURES_FEATURES           4
#define __OFFSET_HOP_SUPERBLOCK_FEATURES_SECTOR_SIZE        8
#define __OFFSET_HOP_SUPERBLOCK_FEATURES_LINK_MAX           16
#define __OFFSET_HOP_SUPERBLOCK_FEATURES_NAME_MAX           24
#define __OFFSET_HOP_SUPERBLOCK_FEATURES_SYMLINK_MAX        32
#define __OFFSET_HOP_SUPERBLOCK_FEATURES_REC_INCR_XFER_SIZE 40
#define __OFFSET_HOP_SUPERBLOCK_FEATURES_REC_MAX_XFER_SIZE  44
#define __OFFSET_HOP_SUPERBLOCK_FEATURES_REC_MIN_XFER_SIZE  48
#define __OFFSET_HOP_SUPERBLOCK_FEATURES_REC_XFER_ALIGN     52
#define __OFFSET_HOP_SUPERBLOCK_FEATURES_FILESIZEBITS       56
#define __OFFSET_HOP_SUPERBLOCK_FEATURES_MAGIC              60
#define __SIZEOF_HOP_SUPERBLOCK_FEATURES                    64
#ifdef __CC__
struct hop_superblock_features /*[PREFIX(sbf_)]*/ {
	__uint32_t            sbf_struct_size;        /* [== sizeof(struct hop_superblock_features)]
	                                               * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                               * this value is too small  or doesn't match any  recognized
	                                               * structure version. */
	__uint32_t            sbf_features;           /* Filesystem features (Set of `HOP_SUPERBLOCK_FEAT_*') */
	__uint64_t            sbf_sector_size;        /* Sector/Fragment/Cluster/Frame/Page/whatever-you-want-to-call-it  size  of
	                                               * the filesystem. Calculated from `struct hop_datablock_stat::ds_pageshift'
	                                               * s.a.: `struct statfs::f_frsize' */
	__uint64_t            sbf_link_max;           /* Max # of links a file may have
	                                               * s.a.: `pathconf(_PC_LINK_MAX)' */
	__uint64_t            sbf_name_max;           /* Max # of chars in a file name
	                                               * s.a.: `struct statfs::f_namelen', `pathconf(_PC_NAME_MAX)' */
	__uint64_t            sbf_symlink_max;        /* Max length of text contained within symbolic links
	                                               * s.a.: `pathconf(_PC_SYMLINK_MAX)' */
	__uint32_t            sbf_rec_incr_xfer_size; /* Buffer size increments for efficient disk transfer operations
	                                               * s.a.: `pathconf(_PC_REC_INCR_XFER_SIZE)' */
	__uint32_t            sbf_rec_max_xfer_size;  /* Max buffer size for efficient disk transfer operations
	                                               * s.a.: `pathconf(_PC_REC_MAX_XFER_SIZE)' */
	__uint32_t            sbf_rec_min_xfer_size;  /* Min buffer size for efficient disk transfer operations
	                                               * s.a.: `struct statfs::f_bsize', `pathconf(_PC_REC_MIN_XFER_SIZE)' */
	__uint32_t            sbf_rec_xfer_align;     /* Required in-memory buffer alignment for efficient disk transfer operations */
	__uint8_t             sbf_filesizebits;       /* Max # of bits in a file's size field (usually 64 or 32) */
	__uint8_t           __sbf_pad1[3];            /* ... */
	__uint32_t            sbf_magic;              /* Filesystem ~magic~ (one of the constants from `<linux/magic.h>')
	                                               * s.a.: `struct statfs::f_type' */
};
#endif /* __CC__ */


/************************************************************************/
/* HANDLE_TYPE_MFILE                                                    */
/************************************************************************/

/* [struct hop_superblock_features *arg] Gather features of the superblock associated with a given fd.
 * NOTE: When the given fd isn't a super-block, a cast to a superblock is attempted. */
#define HOP_SUPERBLOCK_FEATURES HOP_CMD(HANDLE_TYPE_MFILE, 0x0504)

__DECL_END

#endif /* !_KOS_HOP_MFILE_H */
