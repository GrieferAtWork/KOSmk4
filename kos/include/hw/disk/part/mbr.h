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
#ifndef _HW_DISK_PART_MBR_H
#define _HW_DISK_PART_MBR_H 1

#include <__stdinc.h>

#include <bits/types.h>

__DECL_BEGIN

/* Flags used by pt_bootable */
#define PART_BOOTABLE_NONE   0x00
#define PART_BOOTABLE_ACTICE 0x80
#define PART_BOOTABLE_LBA48  0x01

#ifdef __CC__
/* http://wiki.osdev.org/Partition_Table */
struct __ATTR_PACKED mbr_partition_common {
	/* HDD Partition */
	__u8         pt_bootable;  /* Boot indicator bit flag: 0 = no, 0x80 = bootable (or "active") */
	__u8       __pt_data1[3];
	__u8         pt_sysid;     /* System ID (s.a.: `BLKSYS_*') */
	__u8       __pt_data2[11];
};

struct __ATTR_PACKED mbr_partition_32 {
	/* HDD Partition */
	__u8         pt_bootable;       /* Boot indicator bit flag: 0 = no, 0x80 = bootable (or "active") */
	__u8         pt_headstart;      /* Starting Head */
	unsigned int pt_sectstart : 6;  /* Starting Sector */
	unsigned int pt_cylistart : 10; /* Starting Cylinder */
	__u8         pt_sysid;          /* System ID (s.a.: `BLKSYS_*') */
	__u8         pt_headend;        /* Ending Head */
	unsigned int pt_sectend : 6;    /* Ending Sector */
	unsigned int pt_cyliend : 10;   /* Ending Cylinder */
	__le32       pt_lbastart;       /* Relative Sector (to start of partition -- also equals the partition's starting LBA value) */
	__le32       pt_lbasize;        /* Total Sectors in partition */
};
#endif /* __CC__ */

/* NOTE: This one should really be a standard!
 *      (Though some say it isn't, this kernel uses it) */
#define PART48_SIG1 0x14
#define PART48_SIG2 0xeb
#ifdef __CC__
struct __ATTR_PACKED mbr_partition_48 {
	/* LBA-48 HDD Partition */
	__u8         pt_bootable;   /* Boot indicator bit flag: 1 = no, 0x81 = bootable (or "active") */
	__u8         pt_sig1;       /* Signature #1 (== 0x14) */
	__le16       pt_lbastarthi; /* High 2 bytes for pt_lbastart */
	__u8         pt_sysid;      /* System ID (s.a.: `BLKSYS_*') */
	__u8         pt_sig2;       /* Signature #2 (== 0xeb) */
	__le16       pt_lbasizehi;  /* High 2 bytes for pt_lbasize */
	__le32       pt_lbastart;   /* Relative Sector (to start of partition -- also equals the partition's starting LBA value) */
	__le32       pt_lbasize;    /* Total Sectors in partition */
};

union __ATTR_PACKED mbr_partition {
	struct mbr_partition_common pt;
	struct mbr_partition_32     pt_32;
	struct mbr_partition_48     pt_48;
};
#endif /* __CC__ */



/* offsetof `struct mbr_data' within the first sector. */
#define MBR_DATA_OFFSET 436
#ifdef __CC__
/* http://wiki.osdev.org/MBR_(x86) */
struct __ATTR_PACKED mbr_data {          /* Master boot record */
	char                mbr_diskuid[10]; /* Optional "unique" disk ID */
	union mbr_partition mbr_part[4];     /* Partition table entries */
	__u8                mbr_sig[2];      /* "Valid bootsector" signature bytes (== 0x55, 0xAA) */
};

/* http://wiki.osdev.org/MBR_(x86) */
struct __ATTR_PACKED mbr_sector {           /* Master boot record */
	__u8                mbr_bootstrap[436]; /* MBR Bootstrap (flat binary executable code) */
	char                mbr_diskuid[10];    /* Optional "unique" disk ID */
	union mbr_partition mbr_part[4];        /* Partition table entries */
	__u8                mbr_sig[2];         /* "Valid bootsector" signature bytes (== 0x55, 0xAA) */
};
#endif /* __CC__ */



__DECL_END

#endif /* !_HW_DISK_PART_MBR_H */
