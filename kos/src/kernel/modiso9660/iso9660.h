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
#ifndef GUARD_MODISO9660_ISO9660_H
#define GUARD_MODISO9660_ISO9660_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

DECL_BEGIN

#define ISO9660_SECTOR_SIZE  2048
#define ISO9660_SECTOR_SHIFT 11

#define VOLUME_DESCRIPTOR_TYPE_BOOT_RECORD          0 /* Boot Record */
#define VOLUME_DESCRIPTOR_TYPE_PRIMARY_VOLUME       1 /* Primary Volume Descriptor */
#define VOLUME_DESCRIPTOR_TYPE_SUPPLEMENTARY_VOLUME 2 /* Supplementary Volume Descriptor */
#define VOLUME_DESCRIPTOR_TYPE_VOLUME_PARITION      3 /* Volume Partition Descriptor */
#define VOLUME_DESCRIPTOR_TYPE_EOF                  255 /* Volume Descriptor Set Terminator */

typedef struct ATTR_PACKED {
	u8    br_type;           /* [== VOLUME_DESCRIPTOR_TYPE_BOOT_RECORD] */
	char  br_ident[5];       /* Volume descriptor identifier (should always be `CD001') */
	u8    br_version;        /* Volume descriptor version (should always be 0x01) */
	char  br_bootsys_id[32]; /* System ID which can boot??? */
	char  br_boot_id[32];    /* ID of the boot system defined??? */
//	u8    br_data[1977];     /* Boot system data??? */
} BootRecordVolumeDescriptor;

typedef struct ATTR_PACKED {
	char    dt_year[4];       /* Year (0000-9999) */
	char    dt_month[2];      /* Month (01-12)*/
	char    dt_day[2];        /* Day (01-31) */
	char    dt_hour[2];       /* Hour (00-23) */
	char    dt_minute[2];     /* Minute (00-59) */
	char    dt_second[2];     /* Seconds (00-59) */
	char    dt_hundredths[2]; /* 1/100th seconds (00-99) */
	uint8_t dt_timezone;      /* Timezone offset from GMT (in 15-minute intervals), with 0 meaning -48 (aka. GMT-12 hours) */
} DateTime;


typedef struct ATTR_PACKED {
	u8       pv_type;               /* [== VOLUME_DESCRIPTOR_TYPE_PRIMARY_VOLUME] */
	char     pv_ident[5];           /* Volume descriptor identifier (should always be `CD001') */
	u8       pv_version;            /* Volume descriptor version (should always be 0x01) */
	u8       pv_pad0;               /* ... */
	char     pv_system_id[32];      /* Name of the system intended to work with sectors 0x00-0x0f of this volume */
	char     pv_volume_id[32];      /* Identification for this volume. */
	u8       pv_pad1[8];            /* ... */
	le32     pv_volume_space_le;    /* Number of Logical Blocks in which the volume is recorded */
	be32     pv_volume_space_be;    /* Number of Logical Blocks in which the volume is recorded */
	u8       pv_pad2[32];           /* ... */
	le16     pv_volumeset_sz_le;    /* Number of CDs in this volume (for multi-disk volumes) */
	be16     pv_volumeset_sz_be;    /* Number of CDs in this volume (for multi-disk volumes) */
	le16     pv_volumeset_id_le;    /* ID of this CDs (for multi-disk volumes) */
	be16     pv_volumeset_id_be;    /* ID of this CDs (for multi-disk volumes) */
	le16     pv_sectorsize_le;      /* Size of a sector (usually `ISO9660_SECTOR_SIZE') */
	be16     pv_sectorsize_be;      /* Size of a sector (usually `ISO9660_SECTOR_SIZE') */
	le32     pv_pathtabsz_le;       /* Size of the path table (in bytes) */
	be32     pv_pathtabsz_be;       /* Size of the path table (in bytes) */
	le32     pv_pathtabsec_le;      /* Sector of the le-path table. */
	le32     pv_pathtabsec_opt_le;  /* Sector of the optional le-path table??? */
	be32     pv_pathtabsec_be;      /* Sector of the be-path table. */
	be32     pv_pathtabsec_opt_be;  /* Sector of the optional be-path table??? */
	byte_t   pv_rootdir[34];        /* Directory entry descriptor for the root directory (this is actually a `DirectoryEntry'). */
	char     pv_volumeset_name[128];/* Name of the volume set that this CD is apart of */
	char     pv_volumeset_publ[128];/* Name of the publisher of the volume set that this CD is apart of */
	char     pv_datapreb_name[128]; /* Name/id for the person(s) that prepared this volume, or 0x5f+filename in root directory, or all 0x20 if empty. */
	char     pv_app_name[128];      /* Name/id of how data is recorded on the CD???, or 0x5f+filename in root directory, or all 0x20 if empty. */
	char     pv_copyright_file[38]; /* Filename for a file containing copyright information (or all 0x20 if empty) */
	char     pv_abstrinfo_file[36]; /* Filename for a file containing abstract information for the volume set??? (or all 0x20 if empty) */
	char     pv_bibliogrp_file[37]; /* Filename for a file containing bibliographic information for the volume set??? (or all 0x20 if empty) */
	DateTime pv_creation_time;      /* Volume creation timestamp. */
	DateTime pv_modification_time;  /* Volume last-modified timestamp. */
	DateTime pv_expiration_time;    /* Volume expiration timestamp??? (don't use after) (Well, here's something I won't be honoring...) */
	DateTime pv_activation_time;    /* Volume activation timestamp??? (don't use before) (Well, here's something I won't be honoring...) */
	u8       pv_fs_version;         /* File structure version (always 0x01) */
//	u8       pv_pad0;               /* ... */
//	u8       pv_appdata[512];       /* ... */
//	u8       pv_reserved[653];      /* ... */
} PrimaryVolumeDescriptor;

typedef struct ATTR_PACKED {
	u8       ev_type;           /* [== VOLUME_DESCRIPTOR_TYPE_EOF] */
	char     ev_ident[5];       /* Volume descriptor identifier (should always be `CD001') */
	u8       ev_version;        /* Volume descriptor version (should always be 0x01) */
} EofVolumeDescriptor;

typedef struct ATTR_PACKED {
	union ATTR_PACKED {
		struct ATTR_PACKED {
			u8                     vd_type;        /* Volume descriptor type code (One of `VOLUME_DESCRIPTOR_TYPE_*') */
			char                   vd_ident[5];    /* Volume descriptor identifier (should always be `CD001') */
			u8                     vd_version;     /* Volume descriptor version (should always be 0x01) */
//			u8                     vd_data[2041];  /* Volume descriptor data (meaning depends on `vd_type') */
		};
		BootRecordVolumeDescriptor vd_boot_record; /* VOLUME_DESCRIPTOR_TYPE_BOOT_RECORD */
		PrimaryVolumeDescriptor    vd_prim_volume; /* VOLUME_DESCRIPTOR_TYPE_PRIMARY_VOLUME */
		EofVolumeDescriptor        vd_eof;         /* VOLUME_DESCRIPTOR_TYPE_EOF */
	};
} VolumeDescriptor;

typedef struct ATTR_PACKED {
	uint8_t rdt_year;     /* Number of years since 1900 */
	uint8_t rdt_month;    /* Month (1-12) */
	uint8_t rdt_day;      /* Day (1-31) */
	uint8_t rdt_hour;     /* Hour (0-23) */
	uint8_t rdt_minute;   /* Minute (0-59) */
	uint8_t rdt_second;   /* Second (0-59) */
	uint8_t rdt_timezone; /* Timezone (same as `DateTime::dt_timezone') */
} RecordDateTime;


#define FILE_FLAG_HIDDEN      0x01 /* File is hidden */
#define FILE_FLAG_DIRECTORY   0x02 /* File is a directory */
#define FILE_FLAG_ASSOCIATED  0x04 /* File is an "associated file" ??? */
#define FILE_FLAG_EXTENDED    0x08 /* The extended record contains more information (s.a. `de_extlength') */
#define FILE_FLAG_PERMISSIONS 0x10 /* Owner and group information are set in the extended record (s.a. `de_extlength') */
#define FILE_FLAG_CONTINUES   0x80 /* The next directory entry also belongs to this file (for files bigger than 4Gib) */

typedef struct ATTR_PACKED {
	u8             de_length;            /* Length of the directory entry. */
	u8             de_extlength;         /* Length of the extended attribute record. */
	le32           de_datasec_le;        /* Starting sector number for data of the file associated with this directory entry. */
	be32           de_datasec_be;        /* Starting sector number for data of the file associated with this directory entry. */
	le32           de_datasiz_le;        /* Size of the file associated with this directory entry (in bytes). */
	be32           de_datasiz_be;        /* Size of the file associated with this directory entry (in bytes). */
	RecordDateTime de_rectime;           /* Recording date/time */
	u8             de_fileflags;         /* File flags (Set of `FILE_FLAG_*') */
	u8             de_interleaved_unit;  /* File unit size in interleaved mode (multi-disk support???) */
	u8             de_interleaved_gap;   /* Interleaved gap size (multi-disk support???) */
	le16           de_volumeset_id_le;   /* The volume on which this file's data is stored (multi-disk support) */
	be16           de_volumeset_id_be;   /* The volume on which this file's data is stored (multi-disk support) */
	u8             de_namelen;           /* Length of the file name (terminates with a ';', followed by the file ID as ASCII-decimal???) */
	char           de_name[223];         /* File name (variable-length) */
//	u8             de_pad;               /* [exists_if((de_namelen & 1) == 0)] Padding byte */
//	u8             de_extdat[];          /* Extended data table (located as `256-de_length'???) */
//System Use - The remaining bytes up to the maximum record size of 255 may be used for extensions of ISO 9660. The most common one is the System Use Share Protocol (SUSP) and its application, t
} DirectoryEntry;


/* Return the on-disk address of a given file-node. */
#define fnode_getdiskaddr(self, filepos) \
	(((pos_t)(u32)(self)->fn_fsdataint << (self)->mf_blockshift) + (filepos))

DECL_END

#endif /* !GUARD_MODISO9660_ISO9660_H */
