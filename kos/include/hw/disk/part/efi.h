/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _HW_DISK_PART_EFI_H
#define _HW_DISK_PART_EFI_H 1

#include <__stdinc.h>

#include <kos/uuid.h>
#include <bits/types.h>

__DECL_BEGIN

/************************************************************************/
/*   EFI PARTITION STRUCTURES                                           */
/************************************************************************/

#define SEFIMAG 8
#define EFIMAG0 0x45
#define EFIMAG1 0x46
#define EFIMAG2 0x49
#define EFIMAG3 0x20
#define EFIMAG4 0x50
#define EFIMAG5 0x41
#define EFIMAG6 0x52
#define EFIMAG7 0x54

#ifdef __CC__
/* NOTE: Information about EFI structures can be found here:
 * http://rawdisk.readthedocs.io/en/latest/filesystem_diagrams.html */
struct __ATTR_PACKED efi_descriptor {
	__u8     gpt_signature[SEFIMAG]; /* EFI boot magic */
	__le32   gpt_revision;           /* GPT revision number */
	__le32   gpt_hdrsize;            /* Header size (Usually 92) */
	__le32   gpt_hdrcrc32;           /* CRC-32 header checksum */
	__u32    gpt_reserved;           /* Reserved (must be ZERO(0)) */
	__le64   gpt_currlba;            /* Current LBA */
	__le64   gpt_backlba;            /* Backup LBA */
	__le64   gpt_firstpart;          /* First usable LBA for partitions */
	__le64   gpt_lastpart;           /* Last usable LBA for partitions */
	uuid_t   gpt_uuid;               /* Disk UUID */
	__le64   gpt_partition_start;    /* Starting LBA for partition entries */
	__le32   gpt_partition_count;    /* Size of the partition vector (in entries) */
	__le32   gpt_partition_entsz;    /* Size of a single partition entry (Usually 128) */
	__le32   gpt_partition_crc32;    /* CRC-32 checksum for the partition vector */
	/* NOTE: When creating a GPT partition table, remaining sector data is zeroed out */
};
#endif /* __CC__ */


/* Flags for `struct efi_partition::p_flags' */
#define EFI_PART_F_ACTIVE      (__UINT64_C(1) << 2)
#define EFI_PART_F_READONLY    (__UINT64_C(1) << 60)
#define EFI_PART_F_HIDDEN      (__UINT64_C(1) << 62)
#define EFI_PART_F_NOAUTOMOUNT (__UINT64_C(1) << 63)

#ifdef __CC__
struct __ATTR_PACKED efi_partition {
	uuid_t p_type_uuid; /* Partition type UUID */
	uuid_t p_part_uuid; /* Unique partition UUID */
	__le64 p_part_min;  /* [<= p_part_end] First partition LBA index. */
	__le64 p_part_end;  /* [>= p_part_min] Partition end LBA index. */
	__le64 p_flags;     /* Partition flags (Set of `EFI_PART_F_*') */
	__le16 p_name[36];  /* Partition name */
};
#endif /* __CC__ */

__DECL_END

#endif /* !_HW_DISK_PART_EFI_H */
