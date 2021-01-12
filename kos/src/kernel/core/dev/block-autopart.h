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
#ifndef GUARD_KERNEL_SRC_DEV_BLOCK_AUTOPART_H
#define GUARD_KERNEL_SRC_DEV_BLOCK_AUTOPART_H 1

#include <kernel/compiler.h>

#include <dev/block.h>
#include <kernel/types.h>

DECL_BEGIN

/* Flags used by pt_bootable */
#define PART_BOOTABLE_NONE   0x00
#define PART_BOOTABLE_ACTICE 0x80
#define PART_BOOTABLE_LBA48  0x01

/* http://wiki.osdev.org/Partition_Table */
struct ATTR_PACKED mbr_partition_common {
	/* HDD Partition */
	u8           pt_bootable;  /* Boot indicator bit flag: 0 = no, 0x80 = bootable (or "active") */
	u8         __pt_data1[3];
	u8           pt_sysid;     /* System ID (s.a.: `BLKSYS_*') */
	u8         __pt_data2[11];
};

struct ATTR_PACKED mbr_partition_32 {
	/* HDD Partition */
	u8           pt_bootable;       /* Boot indicator bit flag: 0 = no, 0x80 = bootable (or "active") */
	u8           pt_headstart;      /* Starting Head */
	unsigned int pt_sectstart : 6;  /* Starting Sector */
	unsigned int pt_cylistart : 10; /* Starting Cylinder */
	u8           pt_sysid;          /* System ID (s.a.: `BLKSYS_*') */
	u8           pt_headend;        /* Ending Head */
	unsigned int pt_sectend : 6;    /* Ending Sector */
	unsigned int pt_cyliend : 10;   /* Ending Cylinder */
	le32         pt_lbastart;       /* Relative Sector (to start of partition -- also equals the partition's starting LBA value) */
	le32         pt_lbasize;        /* Total Sectors in partition */
};

/* NOTE: This one should really be a standard!
	*      (Though some say it isn't, this kernel uses it) */
#define PART48_SIG1 0x14
#define PART48_SIG2 0xeb
struct ATTR_PACKED mbr_partition_48 {
	/* LBA-48 HDD Partition */
	u8           pt_bootable;   /* Boot indicator bit flag: 1 = no, 0x81 = bootable (or "active") */
	u8           pt_sig1;       /* Signature #1 (== 0x14) */
	le16         pt_lbastarthi; /* High 2 bytes for pt_lbastart */
	u8           pt_sysid;      /* System ID (s.a.: `BLKSYS_*') */
	u8           pt_sig2;       /* Signature #2 (== 0xeb) */
	le16         pt_lbasizehi;  /* High 2 bytes for pt_lbasize */
	le32         pt_lbastart;   /* Relative Sector (to start of partition -- also equals the partition's starting LBA value) */
	le32         pt_lbasize;    /* Total Sectors in partition */
};

union ATTR_PACKED mbr_partition {
	struct mbr_partition_common pt;
	struct mbr_partition_32     pt_32;
	struct mbr_partition_48     pt_48;
};


#define MBR_DATA_OFFSET  436

/* http://wiki.osdev.org/MBR_(x86) */
struct ATTR_PACKED mbr_data {            /* Master boot record */
	char                mbr_diskuid[10]; /* Optional "unique" disk ID */
	union mbr_partition mbr_part[4];     /* Partition table entries */
	u8                  mbr_sig[2];      /* "Valid bootsector" signature bytes (== 0x55, 0xAA) */
};

/* http://wiki.osdev.org/MBR_(x86) */
struct ATTR_PACKED mbr_sector {             /* Master boot record */
	u8                  mbr_bootstrap[436]; /* MBR Bootstrap (flat binary executable code) */
	char                mbr_diskuid[10];    /* Optional "unique" disk ID */
	union mbr_partition mbr_part[4];        /* Partition table entries */
	u8                  mbr_sig[2];         /* "Valid bootsector" signature bytes (== 0x55, 0xAA) */
};



/* ========================================================================================
 *   EFI PARTITION STRUCTURES
 * ======================================================================================== */


#define SEFIMAG 8
#define EFIMAG0 0x45
#define EFIMAG1 0x46
#define EFIMAG2 0x49
#define EFIMAG3 0x20
#define EFIMAG4 0x50
#define EFIMAG5 0x41
#define EFIMAG6 0x52
#define EFIMAG7 0x54

/* NOTE: Information about EFI structures can be found here:
	* http://rawdisk.readthedocs.io/en/latest/filesystem_diagrams.html */
struct ATTR_PACKED efi_descriptor {
	u8     gpt_signature[SEFIMAG]; /* EFI boot magic */
	le32   gpt_revision;           /* GPT revision number */
	le32   gpt_hdrsize;            /* Header size (Usually 92) */
	le32   gpt_hdrcrc32;           /* CRC-32 header checksum */
	u32    gpt_reserved;           /* Reserved (must be ZERO(0)) */
	le64   gpt_currlba;            /* Current LBA */
	le64   gpt_backlba;            /* Backup LBA */
	le64   gpt_firstpart;          /* First usable LBA for partitions */
	le64   gpt_lastpart;           /* Last usable LBA for partitions */
	guid_t gpt_guid;               /* Disk GUID */
	le64   gpt_partition_start;    /* Starting LBA for partition entries */
	le32   gpt_partition_count;    /* Size of the partition vector (in entires) */
	le32   gpt_partition_entsz;    /* Size of a single partition entry (Usually 128) */
	le32   gpt_partition_crc32;    /* CRC-32 checksum for the partition vector */
	/* NOTE: When creating a GPT partition table, remaining sector data is zeroed out */
};


struct ATTR_PACKED efi_partition {
	guid_t p_type_guid; /* Partition type GUID */
	guid_t p_part_guid; /* Unique partition GUID */
	le64   p_part_min;  /* [<= p_part_end] First partition LBA index. */
	le64   p_part_end;  /* [>= p_part_min] Partition end LBA index. */
#define EFI_PART_F_ACTIVE      (__UINT64_C(1) << 2)
#define EFI_PART_F_READONLY    (__UINT64_C(1) << 60)
#define EFI_PART_F_HIDDEN      (__UINT64_C(1) << 62)
#define EFI_PART_F_NOAUTOMOUNT (__UINT64_C(1) << 63)
	le64   p_flags;     /* Partition flags (Set of `EFI_PART_F_*') */
	le16   p_name[36];  /* Partition name */
};


DECL_END

#endif /* !GUARD_KERNEL_SRC_DEV_BLOCK_AUTOPART_H */
