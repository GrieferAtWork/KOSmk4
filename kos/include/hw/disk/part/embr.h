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
#ifndef _HW_DISK_PART_EMBR_H
#define _HW_DISK_PART_EMBR_H 1

#include <__stdinc.h>

#include <bits/types.h>

/* Extended Master Boot Record: http://www.fysnet.net/fysos_embr.htm */

__DECL_BEGIN

/* offsetof `struct mbr_data' within the first sector. */
#ifdef __CC__
struct __ATTR_PACKED embr_partition { /* "eMBR Partition" */
	__u8   embr_bootstrap[0x01f2];    /* Bootstrap code */
	__u8   embr_signature[8];         /* == { 'E', 'm', 'b', 'r', 'r', 'b', 'm', 'E' } */
	__le16 embr_hdrsector;            /* Header block sector index (relative to LBA=0 (!not 1!); in 512-byte chunks)
	                                   * Points at  a  sectored  starting with  a  `struct embr_parthdr'  structure. */
	__le16 embr_remsectors;           /* # of remaining sectors of boot code (only important for bootloaders) */
	__u8   embr_bootsig[2];           /* == { 0x55, 0xAA } */
};

#define EMBR_PARTENT_F_NORMAL __UINT32_C(0x00000000) /* No special flags. */

struct __ATTR_PACKED embr_partent { /* "eMBR Partition Entry" */
	__le32 epe_flags;    /* Partition flags (set of `EMBR_PARTENT_F_*') */
	__u8   epe_sig[4];   /* Another signature (== { 'e', 'M', 'B', 'R' }) */
	__le64 epe_lbastart; /* Starting LBA */
	__le64 epe_lbacount; /* # of sectors apart of this partition */
	char   epe_desc[64]; /* UTF-8 partition description */
	__le64 epe_tm_creat; /* Creation time (in seconds since 01.01.1980T00:00) */
	__le64 epe_tm_boot;  /* Last boot time (in seconds since 01.01.1980T00:00) */
	__u8   epe_ossig[8]; /* OS-specific signature */
	__u8   epe_res[16];  /* Reserved bytes... */
};

struct __ATTR_PACKED embr_parthdr { /* "eMBR Partition Header" */
	__u8   eph_sig1[4];   /* First signature == { 'E', 'M', 'B', 'R' } */
	__le32 eph_crc32;     /* CRC32 of header and entries. */
	__le16 eph_entcnt;    /* Total # of entries that follow */
	__u8   eph_bootdelay; /* Boot delay in seconds (only important for bootloaders) */
	__u8   eph_version;   /* EMBR version (major=1 * 32 + minor=4 --> 0x25) */
	__le64 eph_sector;    /* Total number of sections (starting at LBA=0) described by eMBR */
	__u8   eph_res[8];    /* Reserved bytes... */
	__u8   eph_sig2[4];   /* Second signature == { 'R', 'B', 'M', 'E' } */
};
#endif /* __CC__ */



__DECL_END

#endif /* !_HW_DISK_PART_EMBR_H */
