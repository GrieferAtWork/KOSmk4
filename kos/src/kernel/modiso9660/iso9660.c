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
#ifndef GUARD_MODISO9660_ISO9660_C
#define GUARD_MODISO9660_ISO9660_C 1
#define __WANT_FNODE_FSDATAINT
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include "iso9660.h"
/**/

#include <kernel/compiler.h>

#include <kernel/driver-callbacks.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/filesys.h>
#include <kernel/fs/flat.h>
#include <kernel/fs/node.h>
#include <kernel/fs/regnode.h>
#include <kernel/fs/super.h>
#include <kernel/malloc.h>
#include <sched/tsc.h>

#include <hybrid/bit.h>
#include <hybrid/byteorder.h>

#include <kos/except.h>
#include <linux/magic.h>

#include <alloca.h>
#include <dirent.h>
#include <stddef.h>
#include <string.h>
#include <time.h>

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define GET_LEBE(x) (x##_le)
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define GET_LEBE(x) (x##_be)
#endif


DECL_BEGIN

/************************************************************************/
/* Timestamp helpers                                                    */
/************************************************************************/
#define UNIX_TIME_START_YEAR 1970
#define SECONDS_PER_DAY      86400
#define DAYS2YEARS(n_days)   __daystoyears(n_days)
#define YEARS2DAYS(n_years)  __yearstodays(n_years)
#define ISLEAPYEAR(year)     __isleap(year)

PRIVATE time_t const time_monthstart_yday[2][13] = {
	{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
	{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
};

#define MONTH_STARTING_DAY_OF_YEAR(leap_year, month) \
	time_monthstart_yday[!!(leap_year)][month]


PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL RecordDateTime_Decode)(RecordDateTime const *__restrict self,
                                     struct timespec *__restrict result) {
	time_t sec;
	unsigned int year;
	/* Calculate days since 01.01.1970 */
	year = 1900 + self->rdt_year;
	sec = YEARS2DAYS(year) - YEARS2DAYS(UNIX_TIME_START_YEAR);
	sec += MONTH_STARTING_DAY_OF_YEAR(ISLEAPYEAR(year), (self->rdt_month - 1) % 12);
	sec += self->rdt_day - 1;

	/* Calculate seconds since 01.01.1970T00:00 */
	sec *= SECONDS_PER_DAY;
	sec += self->rdt_hour * 60 * 60;
	sec += self->rdt_minute * 60;
	sec += self->rdt_second;

	/* Timezone addend */
	sec += (((s16)self->rdt_timezone - 48) * 15 * 60);

	/* Write-back results. */
	result->tv_sec  = sec;
	result->tv_nsec = 0;
}



/************************************************************************/
/* Common Iso9660 operators                                             */
/************************************************************************/
PRIVATE NONNULL((1, 5)) void KCALL
iso9660_v_loadblocks(struct mfile *__restrict self, pos_t addr,
                     physaddr_t buf, size_t num_bytes,
                     struct aio_multihandle *__restrict aio) {
	struct fnode *me   = mfile_asnode(self);
	pos_t diskaddr     = fnode_getdiskaddr(me, addr);
	struct fsuper *sup = me->fn_super;
	fsuper_dev_rdsectors_async_chk(sup, diskaddr, buf, num_bytes, aio);
}



/************************************************************************/
/* Iso9660 directory entry                                              */
/************************************************************************/
struct iso9660_dirent {
	RecordDateTime    id_rec; /* [const] Record timestamp. */
	u32               id_sec; /* [const] File starting sector. */
	u32               id_siz; /* [const] File size. */
	struct flatdirent id_ent; /* Underlying directory entry. */
};
#define flatdirent_asiso9660(self) \
	container_of(self, struct iso9660_dirent, id_ent)

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL iso9660_dirent_v_destroy)(struct fdirent *__restrict self) {
	struct iso9660_dirent *me;
	me = flatdirent_asiso9660(fdirent_asflat(self));
	kfree(me);
}

/* Operators for `struct iso9660_dirent' */
PRIVATE struct fdirent_ops const iso9660_dirent_ops = {
	.fdo_destroy  = &iso9660_dirent_v_destroy,
	.fdo_opennode = flatdirent_v_opennode,
};



/* Read a entry from an ISO9660 directory. */
PRIVATE WUNUSED struct flatdirent *KCALL
iso9660_v_readdir(struct flatdirnode *__restrict self, pos_t pos)
		THROWS(E_BADALLOC, E_IOERROR) {
	struct iso9660_dirent *result;
	DirectoryEntry ent;
	size_t read_size;

	/* Read the next directory entry. */
again:
	read_size = mfile_read(self, &ent, sizeof(ent), pos);
	if unlikely(read_size < offsetof(DirectoryEntry, de_name))
		return NULL; /* Forced end-of-directory */
	if (ent.de_length == 0)
		return NULL; /* Graceful end-of-directory */
	if unlikely(ent.de_length > read_size)
		ent.de_length = (u8)read_size;
	if unlikely(ent.de_length < offsetof(DirectoryEntry, de_name))
		return NULL; /* ??? */

	/* Restrict file name length to allowed range. */
	if unlikely(ent.de_namelen > ent.de_length - offsetof(DirectoryEntry, de_name))
		ent.de_namelen = ent.de_length - offsetof(DirectoryEntry, de_name);
	ent.de_namelen = strnlen(ent.de_name, ent.de_namelen);
	if (ent.de_namelen == 0 ||                            /* Directory self-reference */
	   (ent.de_namelen == 1 && ent.de_name[0] == '\1')) { /* Parent-directory reference */
		pos += ent.de_length;
		goto again;
	}

	/* Allocate a new directory entry object. */
	result = (struct iso9660_dirent *)kmalloc(offsetof(struct iso9660_dirent, id_ent.fde_ent.fd_name) +
	                                          (ent.de_namelen + 1) * sizeof(char), GFP_NORMAL);
	memcpy(result->id_ent.fde_ent.fd_name, ent.de_name, ent.de_namelen, sizeof(char));
	result->id_rec                 = ent.de_rectime;
	result->id_sec                 = (u32)GET_LEBE(ent.de_datasec);
	result->id_siz                 = (u32)GET_LEBE(ent.de_datasiz);
	result->id_ent.fde_ent.fd_type = DT_REG;
	if (ent.de_fileflags & FILE_FLAG_DIRECTORY)
		result->id_ent.fde_ent.fd_type = DT_DIR;
	result->id_ent.fde_ent.fd_namelen = ent.de_namelen;
	result->id_ent.fde_ent.fd_ops     = &iso9660_dirent_ops;
	result->id_ent.fde_ent.fd_ino     = (ino_t)fnode_getdiskaddr(self, pos);
	result->id_ent.fde_pos            = pos;
	result->id_ent.fde_size           = ent.de_length;
	return &result->id_ent;
}

/* Stream operators for directory nodes.
 * Note that we don't override the stat operator to fill in a  constant
 * value for st_size since iso9660 directories assign meaningful values
 * to the size of directory files! */
PRIVATE struct mfile_stream_ops const iso9660_dir_v_stream_ops = {
	.mso_open  = &fdirnode_v_open,
	.mso_stat  = NULL, /* Explicit! */
	.mso_ioctl = &fdirnode_v_ioctl,
};

PRIVATE struct fregnode_ops const iso9660_reg_ops = {
	.rno_node = {
		.no_file = {
			.mo_destroy    = &fregnode_v_destroy,
			.mo_loadblocks = &iso9660_v_loadblocks,
			.mo_changed    = &fregnode_v_changed,
		},
		.no_wrattr = &fnode_v_wrattr_noop,
	},
};
PRIVATE struct flatdirnode_ops const iso9660_dir_ops = {
	.fdno_dir = {
		.dno_node = {
			.no_file = {
				.mo_destroy    = &flatdirnode_v_destroy,
				.mo_loadblocks = &iso9660_v_loadblocks,
				.mo_changed    = &flatdirnode_v_changed,
				.mo_stream     = &iso9660_dir_v_stream_ops,
			},
			.no_wrattr = &fnode_v_wrattr_noop,
		},
		.dno_lookup = &flatdirnode_v_lookup,
		.dno_enumsz = flatdirnode_v_enumsz,
		.dno_enum   = &flatdirnode_v_enum,
	},
	.fdno_flat = {
		.fdnx_readdir = &iso9660_v_readdir,
	},
};


PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) struct fnode *KCALL
iso9660_v_makenode(struct flatsuper *__restrict UNUSED(self),
                   struct flatdirent *__restrict ent_,
                   struct flatdirnode *__restrict UNUSED(dir))
		THROWS(E_BADALLOC, E_IOERROR) {
	struct iso9660_dirent *ent = flatdirent_asiso9660(ent_);
	struct fnode *result;

	switch (ent->id_ent.fde_ent.fd_type) {

	case DT_REG: {
		struct fregnode *node;
		node = (struct fregnode *)kmalloc(sizeof(struct fregnode), GFP_NORMAL);
		node->mf_ops   = &iso9660_reg_ops.rno_node.no_file;
		node->mf_flags = MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE | MFILE_FN_ATTRREADONLY;
		result = node;
	}	break;

	case DT_DIR: {
		struct flatdirnode *node;
		node = (struct flatdirnode *)kmalloc(sizeof(struct flatdirnode), GFP_NORMAL);
		flatdirdata_init(&node->fdn_data);
		node->mf_ops   = &iso9660_reg_ops.rno_node.no_file;
		node->mf_flags = MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE | MFILE_FN_ATTRREADONLY |
		                 MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO;
		result = node;
	}	break;

	default: __builtin_unreachable();
	}

	/* Fill in common fields. */
	result->mf_parts = NULL;
	SLIST_INIT(&result->mf_changed);
	atomic64_init(&result->mf_filesize, ent->id_siz);
	result->fn_fsdataint = ent->id_sec;
	result->fn_nlink     = 1;
	result->fn_mode      = DTTOIF(ent->id_ent.fde_ent.fd_type) | 0555;
	result->fn_uid       = 0;
	result->fn_gid       = 0;

	/* Fill in timestamp. */
	RecordDateTime_Decode(&ent->id_rec, &result->mf_atime);
	result->mf_mtime = result->mf_atime;
	result->mf_ctime = result->mf_atime;
	result->mf_btime = result->mf_atime;
	return result;
}


PRIVATE struct flatsuper_ops const iso9660_super_ops = {
	.ffso_makenode = &iso9660_v_makenode,
	.ffso_super = {
		.so_fdir = {
			.dno_node = {
				.no_file = {
					.mo_destroy    = &flatsuper_v_destroy,
					.mo_loadblocks = &iso9660_v_loadblocks,
					.mo_changed    = &fsuper_v_changed,
					.mo_stream     = &iso9660_dir_v_stream_ops,
				},
				.no_free   = &flatsuper_v_free,
				.no_wrattr = &fnode_v_wrattr_noop,
			},
			.dno_lookup = &flatdirnode_v_lookup,
			.dno_enumsz = flatdirnode_v_enumsz,
			.dno_enum   = &flatdirnode_v_enum,
		},
	},
	.ffso_flat = {
		.fdnx_readdir = &iso9660_v_readdir,
	},
};


PRIVATE WUNUSED NONNULL((1, 2)) struct fsuper *KCALL
iso9660_openfs(struct ffilesys *__restrict UNUSED(filesys),
               struct mfile *dev, NCX UNCHECKED char *args) {
	struct flatsuper *result;
	VolumeDescriptor *desc;
	pos_t offset, second_volume_offset;
	shift_t sector_shift;

	/* XXX: User-arguments? */
	(void)args;

	/* Allocate disk data buffer. */
#if PAGESHIFT >= ISO9660_SECTOR_SHIFT
	desc = (dev->mf_blockshift <= ISO9660_SECTOR_SHIFT)
	       ? (VolumeDescriptor *)aligned_alloca(ISO9660_SECTOR_SIZE,
	                                            ISO9660_SECTOR_SIZE)
	       : (VolumeDescriptor *)alloca(sizeof(VolumeDescriptor));
#else /* PAGESHIFT >= ISO9660_SECTOR_SHIFT */
	desc = (VolumeDescriptor *)alloca(sizeof(VolumeDescriptor));
#endif /* PAGESHIFT < ISO9660_SECTOR_SHIFT */

	/* Search for the `VOLUME_DESCRIPTOR_TYPE_PRIMARY_VOLUME' descriptor. */
	offset               = (pos_t)0x8000;
	second_volume_offset = (pos_t)-1;
	for (;;) {
		/* Load the volume descriptor. */
#if PAGESHIFT >= ISO9660_SECTOR_SHIFT
		if (dev->mf_blockshift <= ISO9660_SECTOR_SHIFT) {
			mfile_rdblocks(dev, offset, pagedir_translate(desc), ISO9660_SECTOR_SIZE);
		} else
#endif /* PAGESHIFT >= ISO9660_SECTOR_SHIFT */
		{
			mfile_readall(dev, desc, sizeof(VolumeDescriptor), offset);
		}
		if (desc->vd_ident[0] != 'C' || desc->vd_ident[1] != 'D' ||
		    desc->vd_ident[2] != '0' || desc->vd_ident[3] != '0' ||
		    desc->vd_ident[4] != '1' || desc->vd_version != 0x01)
			return NULL; /* Not an iso9660 filesystem */
		if (desc->vd_type == VOLUME_DESCRIPTOR_TYPE_EOF) {
			if (second_volume_offset != (pos_t)-1) {
				/* Fallback to using the second desc. */
				offset = second_volume_offset;
#if PAGESHIFT >= ISO9660_SECTOR_SHIFT
				if (dev->mf_blockshift <= ISO9660_SECTOR_SHIFT) {
					mfile_rdblocks(dev, offset, pagedir_translate(desc), ISO9660_SECTOR_SIZE);
				} else
#endif /* PAGESHIFT >= ISO9660_SECTOR_SHIFT */
				{
					mfile_readall(dev, desc, sizeof(VolumeDescriptor), offset);
				}
				break;
			}
			/* There's no primary volume descriptor... */
			THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);
		}
		if (desc->vd_type == VOLUME_DESCRIPTOR_TYPE_PRIMARY_VOLUME)
			break; /* Found it! */
		if (desc->vd_type == VOLUME_DESCRIPTOR_TYPE_SUPPLEMENTARY_VOLUME &&
		    second_volume_offset == (pos_t)-1)
			second_volume_offset = offset;
		offset += ISO9660_SECTOR_SIZE;
	}
	if (desc->vd_prim_volume.pv_fs_version != 0x01)
		THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);

	{
		u32 sector_size;
		sector_size = (u32)GET_LEBE(desc->vd_prim_volume.pv_sectorsize);
		if unlikely(!sector_size || (sector_size & (sector_size - 1)) != 0)
			THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);
		sector_shift = CTZ(sector_size);
	}

	/* Allocate the new superblock. */
	result = (struct flatsuper *)kmalloc(sizeof(struct flatsuper), GFP_NORMAL);

	/* Remember the on-disk address of the root directory. */
	{
		DirectoryEntry *root;
		root = (DirectoryEntry *)desc->vd_prim_volume.pv_rootdir;
		if unlikely(!(root->de_fileflags & FILE_FLAG_DIRECTORY)) {
			kfree(result);
			THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM); /* It has to be a root _DIRECTORY_ */
		}
		/* Similar to FAT, we use the address of directory entries for INode numbers. */
		result->ffs_super.fs_root.fn_ino       = (ino_t)offset + offsetof(VolumeDescriptor, vd_prim_volume.pv_rootdir);
		result->ffs_super.fs_root.fn_fsdataint = (u32)GET_LEBE(root->de_datasec);
		atomic64_init(&result->ffs_super.fs_root.mf_filesize, (u32)GET_LEBE(root->de_datasiz));
		result->ffs_super.fs_root.fn_mode = S_IFDIR | 0555;
	}

	/* Fill in fields. */
	result->ffs_super.fs_root.mf_ops   = &iso9660_super_ops.ffso_super.so_fdir.dno_node.no_file;
	result->ffs_super.fs_root.mf_parts = NULL;
	SLIST_INIT(&result->ffs_super.fs_root.mf_changed);
	result->ffs_super.fs_root.mf_blockshift = sector_shift;
	result->ffs_super.fs_root.mf_iobashift  = dev->mf_iobashift;
	result->ffs_features = FFLATSUPER_FEAT_NORMAL;
	flatdirdata_init(&result->ffs_rootdata);

	/* Set flags as appropriate for a read-only filesystem */
	result->ffs_super.fs_root.mf_flags = (MFILE_F_READONLY | MFILE_F_NOATIME | MFILE_F_NOMTIME |
	                                      MFILE_FN_NODIRATIME | MFILE_FN_ATTRREADONLY);

	/* TODO: Decode this information from the volume descriptor:
	 *   - volume.vd_prim_volume.pv_creation_time
	 *   - volume.vd_prim_volume.pv_modification_time */
	result->ffs_super.fs_root.mf_atime = realtime();
	result->ffs_super.fs_root.mf_mtime = result->ffs_super.fs_root.mf_atime;
	result->ffs_super.fs_root.mf_ctime = result->ffs_super.fs_root.mf_atime;
	result->ffs_super.fs_root.mf_btime = result->ffs_super.fs_root.mf_atime;
	result->ffs_super.fs_root.fn_nlink = 1;
	result->ffs_super.fs_root.fn_uid   = 0;
	result->ffs_super.fs_root.fn_gid   = 0;

	/* Fill in features. */
	result->ffs_super.fs_feat.sf_filesize_max       = (pos_t)(u32)-1;
	result->ffs_super.fs_feat.sf_uid_max            = 0;
	result->ffs_super.fs_feat.sf_gid_max            = 0;
	result->ffs_super.fs_feat.sf_symlink_max        = 0;
	result->ffs_super.fs_feat.sf_link_max           = 1;
	result->ffs_super.fs_feat.sf_magic              = ISOFS_SUPER_MAGIC;
	result->ffs_super.fs_feat.sf_rec_incr_xfer_size = (u32)1 << sector_shift;
	result->ffs_super.fs_feat.sf_rec_max_xfer_size  = (u32)1 << sector_shift;
	result->ffs_super.fs_feat.sf_rec_min_xfer_size  = (u32)1 << sector_shift;
	result->ffs_super.fs_feat.sf_rec_xfer_align     = (u32)1 << dev->mf_iobashift;
	result->ffs_super.fs_feat.sf_name_max           = 223;
	result->ffs_super.fs_feat.sf_filesizebits       = 32;

	return &result->ffs_super;
}


PRIVATE struct ffilesys iso9660_filesys = {
	.ffs_drv = &drv_self,
	{ .ffs_open = &iso9660_openfs },
	.ffs_flags = FFILESYS_F_NORMAL,
	/* .ffs_name = */ "iso9660",
};


PRIVATE ATTR_FREETEXT DRIVER_INIT void init(void) {
	ffilesys_register(&iso9660_filesys);
}

PRIVATE DRIVER_FINI void fini(void) {
	ffilesys_unregister(&iso9660_filesys);
}

DECL_END

#endif /* !GUARD_MODISO9660_ISO9660_C */
