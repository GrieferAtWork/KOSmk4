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
#ifndef GUARD_MODFAT_FAT_C
#define GUARD_MODFAT_FAT_C 1
#define _KOS_SOURCE        1
#define _GNU_SOURCE        1

#include <kernel/compiler.h>

#ifdef CONFIG_USE_NEW_FS
#include <kernel/driver-callbacks.h>
#include <kernel/fs/blkdev.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/filesys.h>
#include <kernel/fs/lnknode.h>
#include <kernel/fs/node.h>
#include <kernel/fs/regnode.h>
#include <kernel/fs/super.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/kram.h>
#include <kernel/mman/map.h>
#include <kernel/printk.h>

#include <hybrid/align.h>
#include <hybrid/bit.h>
#include <hybrid/byteorder.h>
#include <hybrid/byteswap.h>
#include <hybrid/overflow.h>

#include <kos/dev.h>
#include <kos/except.h>
#include <linux/magic.h>

#include <alloca.h>
#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "fat.h"

DECL_BEGIN

#define FAT_ISSPACE(c) (isspace(c) || iscntrl(c) /* || isblank(c)*/)

/************************************************************************/
/* FAT Timestamp encode/decode functions                                */
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

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) time_t
NOTHROW(FCALL FatFileDate_Decode)(struct fat_filedate const *__restrict self) {
	time_t result;
	unsigned int year;
	year   = self->fd_year + 1980;
	result = YEARS2DAYS(year) - YEARS2DAYS(UNIX_TIME_START_YEAR);
	result += MONTH_STARTING_DAY_OF_YEAR(ISLEAPYEAR(year), (self->fd_month - 1) % 12);
	result += self->fd_day - 1;
	return result * SECONDS_PER_DAY;
}

PRIVATE NONNULL((1)) void
NOTHROW(KCALL FatFileDate_Encode)(struct fat_filedate *__restrict self,
                                  time_t tmt) {
	unsigned int year;
	u8 i;
	time_t const *monthvec;
	tmt /= SECONDS_PER_DAY;
	tmt += YEARS2DAYS(UNIX_TIME_START_YEAR);
	year     = DAYS2YEARS(tmt);
	monthvec = time_monthstart_yday[ISLEAPYEAR(year)];
	tmt -= YEARS2DAYS(year);
	self->fd_year = year > 1980 ? year - 1980 : 0;
	/* Find the appropriate month. */
	for (i = 1; i < 12; ++i)
		if (monthvec[i] >= tmt)
			break;
	self->fd_month = i;
	self->fd_day   = (tmt - monthvec[i - 1]) + 1;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) time_t
NOTHROW(KCALL FatFileTime_Decode)(struct fat_filetime const *__restrict self) {
	return ((time_t)self->ft_hour * 60 * 60) +
	       ((time_t)self->ft_min * 60) +
	       ((time_t)self->ft_sec * 2);
}

PRIVATE NONNULL((1)) void
NOTHROW(KCALL FatFileTime_Encode)(struct fat_filetime *__restrict self,
                                  time_t tmt) {
	self->ft_sec  = (tmt % 60) / 2;
	self->ft_min  = ((tmt / 60) % 60);
	self->ft_hour = ((tmt / (60 * 60)) % 24);
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL FatFileCTime_Encode)(struct fat_filectime *__restrict self,
                                   struct timespec const *__restrict value) {
	FatFileDate_Encode(&self->fc_date, value->tv_sec);
	FatFileTime_Encode(&self->fc_time, value->tv_sec);
	self->fc_sectenth = (u8)(value->tv_nsec / (1000000000ul / 200ul));
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL FatFileCTime_Decode)(struct fat_filectime const *__restrict self,
                                   struct timespec *__restrict result) {
	result->tv_sec  = FatFileDate_Decode(&self->fc_date);
	result->tv_sec += FatFileTime_Decode(&self->fc_time);
	result->tv_nsec = (syscall_ulong_t)self->fc_sectenth * (1000000000ul / 200ul);
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL FatFileMTime_Encode)(struct fat_filemtime *__restrict self,
                                   struct timespec const *__restrict value) {
	FatFileDate_Encode(&self->fc_date, value->tv_sec);
	FatFileTime_Encode(&self->fc_time, value->tv_sec);
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL FatFileMTime_Decode)(struct fat_filemtime const *__restrict self,
                                   struct timespec *__restrict result) {
	result->tv_sec = FatFileDate_Decode(&self->fc_date);
	result->tv_sec += FatFileTime_Decode(&self->fc_time);
	result->tv_nsec = 0;
}
#define FatFileATime_Encode(self, value) \
	FatFileDate_Encode(self, (value)->tv_sec)
#define FatFileATime_Decode(self, result) \
	((result)->tv_sec = FatFileDate_Decode(self), (result)->tv_nsec = 0)




/************************************************************************/
/* FAT Cluster helper functions                                         */
/************************************************************************/
PRIVATE WUNUSED NONNULL((1)) FatClusterIndex KCALL
FatSuper_FindFreeCluster(struct fatsuper *__restrict self) {
	FatClusterIndex result;
	assert(fatsuper_fatlock_reading(self));
	result = self->ft_free_pos;
	for (; result < self->ft_cluster_eof; ++result) {
		if (Fat_GetFatIndirection(self, result) == FAT_CLUSTER_UNUSED)
			goto found_one;
	}
	/* Scan everything before our previous location. */
	result = 0;
	for (; result < self->ft_free_pos; ++result) {
		if (Fat_GetFatIndirection(self, result) == FAT_CLUSTER_UNUSED)
			goto found_one;
	}
	/* Disk is full... */
	THROW(E_FSERROR_DISK_FULL);
found_one:
	self->ft_free_pos = result;
	return result;
}

INTERN NONNULL((1)) void KCALL
FatSuper_DeleteClusterChain(struct fatsuper *__restrict self,
                            FatClusterIndex first_delete_index) {
	fatsuper_fatlock_write(self);
	TRY {
		while (first_delete_index < self->ft_cluster_eof &&
		       first_delete_index != FAT_CLUSTER_UNUSED) {
			FatClusterIndex next = Fat_GetFatIndirection(self, first_delete_index);
			Fat_SetFatIndirection(self, first_delete_index, FAT_CLUSTER_UNUSED);
			first_delete_index = next;
		}
	} EXCEPT {
		fatsuper_fatlock_endwrite(self);
		RETHROW();
	}
	fatsuper_fatlock_endwrite(self);
}



/************************************************************************/
/* FAT operator implementations.                                        */
/************************************************************************/

PRIVATE WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
FatDir_Lookup(struct fdirnode *__restrict self,
              struct flookup_info *__restrict info) {
	struct fatnode *me = fdirnode_asfatnode(self);
	/* TODO */
}

PRIVATE NONNULL((1, 2)) void KCALL
FatDir_Enum(struct fdirnode *__restrict self,
            struct fdirenum *__restrict result) {
	struct fatnode *me = fdirnode_asfatnode(self);
	/* TODO */
}

PRIVATE WUNUSED NONNULL((1, 2)) unsigned int KCALL
FatDir_MkFile(struct fdirnode *__restrict self,
              struct fmkfile_info *__restrict info)
		THROWS(E_FSERROR_ILLEGAL_PATH, E_FSERROR_DISK_FULL,
		       E_FSERROR_READONLY, E_FSERROR_TOO_MANY_HARD_LINKS,
		       E_FSERROR_UNSUPPORTED_OPERATION) {
	struct fatnode *me = fdirnode_asfatnode(self);
	/* TODO */
}

PRIVATE WUNUSED NONNULL((1, 2, 3)) unsigned int KCALL
FatDir_Unlink(struct fdirnode *__restrict self,
              struct fdirent *__restrict entry,
              struct fnode *__restrict file)
		THROWS(E_FSERROR_DIRECTORY_NOT_EMPTY,
		       E_FSERROR_READONLY) {
	struct fatnode *me = fdirnode_asfatnode(self);
	/* TODO */
}

PRIVATE WUNUSED NONNULL((1, 2)) unsigned int KCALL
FatDir_Rename(struct fdirnode *__restrict self,
              struct frename_info *__restrict info)
		THROWS(E_FSERROR_ILLEGAL_PATH, E_FSERROR_DISK_FULL, E_FSERROR_READONLY) {
	struct fatnode *me = fdirnode_asfatnode(self);
	/* TODO */
}



/************************************************************************/
/* FAT operator tables.                                                 */
/************************************************************************/
PRIVATE struct fdirent_ops const FatDirent_Ops;
PRIVATE struct fregnode_ops const FatNode_RegOps;

#ifdef CONFIG_FAT_CYGWIN_SYMLINKS
PRIVATE struct flnknode_ops const FatNode_LnkOps;
#endif /* CONFIG_FAT_CYGWIN_SYMLINKS */


/************************************************************************/
/* FAT Superblock operators.                                            */
/************************************************************************/
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL FatSuper_Destroy)(struct mfile *__restrict self) {
	struct fatsuper *me = mfile_asfatsuper(self);
	mman_unmap_kram_and_kfree(me->ft_fat_table, me->ft_fat_size, me->ft_freefat);
	fsuper_v_destroy(&me->ft_super.fs_root);
}

PRIVATE WUNUSED NONNULL((1)) bool
NOTHROW(KCALL FatSuper_ValidUid)(struct fsuper *__restrict self, uid_t uid) {
	struct fatsuper *me = fsuper_asfatsuper(self);
	return uid == me->ft_uid;
}

PRIVATE WUNUSED NONNULL((1)) bool
NOTHROW(KCALL FatSuper_ValidGid)(struct fsuper *__restrict self, gid_t gid) {
	struct fatsuper *me = fsuper_asfatsuper(self);
	return gid == me->ft_gid;
}

PRIVATE NONNULL((1, 2)) void
NOTHROW(KCALL FatSuper_TruncateATime)(struct fsuper *__restrict UNUSED(self),
                                      /*in|out*/ struct timespec *__restrict tms) {
	struct fat_fileatime ts;
	FatFileATime_Encode(&ts, tms);
	FatFileATime_Decode(&ts, tms);
}

PRIVATE NONNULL((1, 2)) void
NOTHROW(KCALL FatSuper_TruncateMTime)(struct fsuper *__restrict UNUSED(self),
                                      /*in|out*/ struct timespec *__restrict tms) {
	struct fat_filemtime ts;
	FatFileMTime_Encode(&ts, tms);
	FatFileMTime_Decode(&ts, tms);
}

PRIVATE NONNULL((1, 2)) void
NOTHROW(KCALL FatSuper_TruncateCTime)(struct fsuper *__restrict UNUSED(self),
                                      /*in|out*/ struct timespec *__restrict tms) {
	struct fat_filectime ts;
	FatFileCTime_Encode(&ts, tms);
	FatFileCTime_Decode(&ts, tms);
}


PRIVATE struct fsuper_ops const Fat16_SuperOps = {
	.so_validuid       = &FatSuper_ValidUid,
	.so_validgid       = &FatSuper_ValidGid,
	.so_truncate_atime = &FatSuper_TruncateATime,
	.so_truncate_mtime = &FatSuper_TruncateMTime,
	.so_truncate_ctime = &FatSuper_TruncateCTime,
	.so_fdir = {
		.dno_node = {
		},
	},
};
PRIVATE struct fsuper_ops const Fat32_SuperOps;







/************************************************************************/
/* The FAT get/set implementation for different table sizes.            */
/************************************************************************/
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) FatClusterIndex
NOTHROW(FCALL Fat12_GetFatIndirection)(struct fatsuper const *__restrict self,
                                       FatClusterIndex index) {
	u16 val;
	assertf(index < self->ft_fat_length,
	        "Out-of-bounds FAT index: %" PRIu32 " >= %" PRIu32 "",
	        index, self->ft_fat_length);
	val = *(u16 const *)((byte_t const *)self->ft_fat_table + (index + (index >> 1)));
	if (index & 1) {
		val >>= 4;
	} else {
		val &= 0x0fff;
	}
	return val;
}

PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) FatClusterIndex
NOTHROW(FCALL Fat16_GetFatIndirection)(struct fatsuper const *__restrict self,
                                       FatClusterIndex index) {
	assertf(index < self->ft_fat_length,
	        "Out-of-bounds FAT index: %" PRIu32 " >= %" PRIu32 "",
	        index, self->ft_fat_length);
	return ((u16 const *)self->ft_fat_table)[index];
}

PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) FatClusterIndex
NOTHROW(FCALL Fat32_GetFatIndirection)(struct fatsuper const *__restrict self,
                                       FatClusterIndex index) {
	assertf(index < self->ft_fat_length,
	        "Out-of-bounds FAT index: %" PRIu32 " >= %" PRIu32 "",
	        index, self->ft_fat_length);
	return ((u32 const *)self->ft_fat_table)[index];
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL Fat12_SetFatIndirection)(struct fatsuper *__restrict self,
                                       FatClusterIndex index,
                                       FatClusterIndex indirection_target) {
	u16 *pval;
	assertf(index < self->ft_fat_length,
	        "Out-of-bounds FAT index: %" PRIu32 " >= %" PRIu32 "",
	        index, self->ft_fat_length);
	pval = ((u16 *)((byte_t *)self->ft_fat_table + (index + (index / 2))));
	if (index & 1) {
		*pval = (*pval & 0xf) | (indirection_target << 4);
	} else {
		*pval |= indirection_target & 0xfff;
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL Fat16_SetFatIndirection)(struct fatsuper *__restrict self,
                                       FatClusterIndex index,
                                       FatClusterIndex indirection_target) {
	assertf(index < self->ft_fat_length,
	        "Out-of-bounds FAT index: %" PRIu32 " >= %" PRIu32 "",
	        index, self->ft_fat_length);
	((u16 *)self->ft_fat_table)[index] = (u16)indirection_target;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL Fat32_SetFatIndirection)(struct fatsuper *__restrict self,
                                       FatClusterIndex index,
                                       FatClusterIndex indirection_target) {
	assertf(index < self->ft_fat_length,
	        "Out-of-bounds FAT index: %" PRIu32 " >= %" PRIu32 "",
	        index, self->ft_fat_length);
	((u32 *)self->ft_fat_table)[index] = indirection_target;
}





/************************************************************************/
/* FAT Superblock: Open Filesystem                                      */
/************************************************************************/

PRIVATE NONNULL((1)) void KCALL
trimspecstring(char *__restrict buf, size_t size) {
	while (size && FAT_ISSPACE(*buf)) {
		--size;
		memmovedown(buf, buf + 1, size, sizeof(char));
		buf[size] = '\0';
	}
	while (size && FAT_ISSPACE(buf[size - 1])) {
		--size;
		buf[size] = '\0';
	}
}



PRIVATE WUNUSED NONNULL((1)) struct fsuper *KCALL
Fat_OpenFileSystem(struct ffilesys *__restrict filesys,
                   struct blkdev *dev, UNCHECKED USER char *args) {
	struct fatsuper *result;
	FatDiskHeader *disk;
	u16 sector_size;

	(void)args; /* TODO: User-arguments. */
	assert(dev);

	/* Read the FAT disk header. */
	if (blkdev_getsectorsize(dev) == sizeof(FatDiskHeader)) {
		disk = (FatDiskHeader *)aligned_alloca(sizeof(FatDiskHeader),
		                                       sizeof(FatDiskHeader));
		blkdev_rdsectors(dev, 0, pagedir_translate(disk), sizeof(FatDiskHeader));
	} else {
		disk = (FatDiskHeader *)alloca(sizeof(FatDiskHeader));
		mfile_readall(dev, disk, sizeof(FatDiskHeader), 0);
	}

	/* Validate the boot signature. */
	if unlikely(disk->fat32.f32_bootsig[0] != 0x55 ||
	            disk->fat32.f32_bootsig[1] != 0xAA)
		return NULL;

	if (!disk->bpb.bpb_sectors_per_cluster ||
	    !disk->bpb.bpb_reserved_sectors) /* What's the first sector, then? */
		return NULL;

	sector_size = LETOH16(disk->bpb.bpb_bytes_per_sector);
	if unlikely(!IS_POWER_OF_TWO(sector_size))
		return NULL;
	if unlikely(!sector_size)
		return NULL;

	/* Allocate the FAT superblock controller. */
	result = (struct fatsuper *)kmalloc(offsetof(struct fatsuper, ft_super) +
	                                  sizeof(struct fatnode),
	                                  GFP_NORMAL);
	TRY {
		struct fatnode *root;
		root                   = (struct fatnode *)&result->ft_super.fs_root;
		result->ft_sectorshift = CTZ(sector_size);

		/* Fill in filesystem info. */
		result->ft_sectorsize = sector_size;
		result->ft_uid        = 0;
		result->ft_gid        = 0;
		result->ft_mode       = 0755; /* Read/Execute permissions for everyone. */
		result->ft_features   = 0;
		shared_rwlock_init(&result->ft_fat_lock);
		result->ft_free_pos = 0;

		/* Extract some common information. */
		result->ft_fat_start   = (FatSectorIndex)LETOH16(disk->bpb.bpb_reserved_sectors);
		result->ft_sec4clus    = (size_t)disk->bpb.bpb_sectors_per_cluster;
		result->ft_fat_count   = (u32)disk->bpb.bpb_fatc;
		result->ft_clustersize = (size_t)result->ft_sec4clus << result->ft_sectorshift;

		/* Figure out what kind of FAT filesystem this is. */
		if (!disk->bpb.bpb_sectors_per_fat || !disk->bpb.bpb_maxrootsize) {
			result->ft_dat_start = result->ft_fat_start + (LETOH32(disk->fat32.f32_sectors_per_fat) *
			                                               disk->bpb.bpb_fatc);
			result->ft_type      = FAT32;
		} else {
			u32 fat_size, root_sectors;
			u32 data_sectors, total_clusters;
			root_sectors = (LETOH16(disk->bpb.bpb_maxrootsize) * sizeof(struct fat_dirent) +
			                (result->ft_sectorsize - 1)) >>
			               result->ft_sectorshift;
			fat_size             = (disk->bpb.bpb_fatc * LETOH16(disk->bpb.bpb_sectors_per_fat));
			result->ft_dat_start = LETOH16(disk->bpb.bpb_reserved_sectors);
			result->ft_dat_start += fat_size;
			result->ft_dat_start += root_sectors;
			/* Calculate the total number of data sectors. */
			if (disk->bpb.bpb_shortsectorc) {
				data_sectors = LETOH16(disk->bpb.bpb_shortsectorc);
			} else {
				data_sectors = LETOH32(disk->bpb.bpb_longsectorc);
			}
			if (OVERFLOW_USUB(data_sectors, LETOH16(disk->bpb.bpb_reserved_sectors), &data_sectors))
				THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);
			if (OVERFLOW_USUB(data_sectors, fat_size, &data_sectors))
				THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);
			if (OVERFLOW_USUB(data_sectors, root_sectors, &data_sectors))
				THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);
			/* Calculate the total number of data clusters. */
			total_clusters = data_sectors / disk->bpb.bpb_sectors_per_cluster;
			if (total_clusters > FAT16_MAXCLUSTERS)
				result->ft_type = FAT32;
			else if (total_clusters > FAT12_MAXCLUSTERS)
				result->ft_type = FAT16;
			else {
				result->ft_type = FAT12;
			}
		}

		if (result->ft_type == FAT32) {
			if (disk->fat32.f32_signature != 0x28 &&
			    disk->fat32.f32_signature != 0x29)
				THROW(E_FSERROR_WRONG_FILE_SYSTEM);
			result->ft_volid = LETOH32(disk->fat32.f32_volid);
			memcpy(result->ft_label, disk->fat32.f32_label, sizeof(disk->fat32.f32_label));
			memcpy(result->ft_sysname, disk->fat32.f32_sysname, sizeof(disk->fat32.f32_sysname));
			result->ft_sec4fat            = LETOH32(disk->fat32.f32_sectors_per_fat);
			result->ft_cluster_eof        = (result->ft_sec4fat << result->ft_sectorshift) / 4;
			result->ft_cluster_eof_marker = 0xffffffff;
			/* Must lookup the cluster of the root directory. */
			root->fn_clusterc     = 1;
			root->fn_clustera     = 2;
			root->fn_clusterv     = (FatClusterIndex *)kmalloc(2 * sizeof(FatClusterIndex), GFP_NORMAL);
			root->fn_clusterv[0]  = LETOH32(disk->fat32.f32_root_cluster);
			result->ft_fat_get    = &Fat32_GetFatIndirection;
			result->ft_fat_set    = &Fat32_SetFatIndirection;
		} else {
			if (result->ft_type == FAT12) {
				result->ft_cluster_eof_marker = 0xfff;
				result->ft_fat_get            = &Fat12_GetFatIndirection;
				result->ft_fat_set            = &Fat12_SetFatIndirection;
			} else {
				result->ft_cluster_eof_marker = 0xffff;
				result->ft_fat_get            = &Fat16_GetFatIndirection;
				result->ft_fat_set            = &Fat16_SetFatIndirection;
			}
			if (disk->fat16.f16_signature != 0x28 &&
			    disk->fat16.f16_signature != 0x29)
				THROW(E_FSERROR_WRONG_FILE_SYSTEM);
			result->ft_volid = LETOH32(disk->fat16.f16_volid);
			memcpy(result->ft_label, disk->fat16.f16_label, sizeof(disk->fat16.f16_label));
			memcpy(result->ft_sysname, disk->fat16.f16_sysname, sizeof(disk->fat16.f16_sysname));
			root->fn16_root.r16_rootpos = (pos_t)LETOH16(disk->bpb.bpb_reserved_sectors);
			root->fn16_root.r16_rootpos += (disk->bpb.bpb_fatc * LETOH16(disk->bpb.bpb_sectors_per_fat));
			root->fn16_root.r16_rootpos <<= result->ft_sectorshift;
			result->ft_sec4fat          = LETOH16(disk->bpb.bpb_sectors_per_fat);
			root->fn16_root.r16_rootsiz = (u32)LETOH16(disk->bpb.bpb_maxrootsize);
			root->fn16_root.r16_rootsiz *= sizeof(struct fat_dirent);
			result->ft_cluster_eof = (result->ft_sec4fat << result->ft_sectorshift) / 2;
			/* It is possible  to create  a FAT16 filesystem  with 0x10000  sectors.
			 * This is a special case since sector 0xffff still needs to be reserved
			 * as the special sector used for marking file EOF.
			 * Because of this, make sure not to allocate sectors above the EOF marker */
			if (result->ft_cluster_eof > result->ft_cluster_eof_marker)
				result->ft_cluster_eof = result->ft_cluster_eof_marker;
		}
		if (result->ft_cluster_eof <= 0xffff)
			result->ft_features |= FAT_FEATURE_ARB; /* 16-bit clusters --> high 16 bits are the ARB mask. */
		if (result->ft_cluster_eof_marker < result->ft_cluster_eof)
			result->ft_cluster_eof_marker = result->ft_cluster_eof;
		/* XXX: Detect `FAT_FEATURE_UGID' */

		memcpy(&result->ft_oem, disk->bpb.bpb_oem, 8, sizeof(char));
		result->ft_fat_size = (size_t)result->ft_sec4fat << result->ft_sectorshift;
		trimspecstring(result->ft_oem, 8);
		trimspecstring(result->ft_label, 11);
		trimspecstring(result->ft_sysname, 8);

		/* Map the FAT table into memory. */
		TRY {
			result->ft_freefat = (struct mman_unmap_kram_job *)kmalloc(sizeof(struct mman_unmap_kram_job), GFP_NORMAL);
			TRY {
				result->ft_fat_table = mman_map(/* self:        */ &mman_kernel,
				                                /* hint:        */ MHINT_GETADDR(KERNEL_MHINT_DEVICE),
				                                /* num_bytes:   */ 0x100,
				                                /* prot:        */ PROT_READ | PROT_WRITE | PROT_SHARED,
				                                /* flags:       */ MHINT_GETMODE(KERNEL_MHINT_DEVICE),
				                                /* file:        */ dev,
				                                /* file_fspath: */ NULL,
				                                /* file_fsname: */ NULL,
				                                /* file_pos:    */ FAT_SECTORADDR(result, result->ft_fat_start));
			} EXCEPT {
				kfree(result->ft_freefat);
				RETHROW();
			}
		} EXCEPT {
			if (result->ft_type == FAT32)
				kfree(root->fn_clusterv);
			RETHROW();
		}

		/* Fill in mandatory superblock fields. */
		/*result->ft_super.fs_root.mf_blockshift       = result->ft_sectorshift;*/ /* It's the same field! */
		result->ft_super.fs_root.mf_parts              = NULL;
		result->ft_super.fs_root.mf_flags              = MFILE_F_NORMAL;
		result->ft_super.fs_root.fn_ino                = 0;
		result->ft_super.fs_feat.sf_filesize_max       = (pos_t)UINT32_MAX;
		result->ft_super.fs_feat.sf_uid_max            = 0;
		result->ft_super.fs_feat.sf_gid_max            = 0;
		result->ft_super.fs_feat.sf_symlink_max        = 0;
		result->ft_super.fs_feat.sf_link_max           = 1;
		result->ft_super.fs_feat.sf_magic              = MSDOS_SUPER_MAGIC;
		result->ft_super.fs_feat.sf_rec_incr_xfer_size = 0;
		result->ft_super.fs_feat.sf_rec_max_xfer_size  = 0;
		result->ft_super.fs_feat.sf_rec_min_xfer_size  = 0;
		result->ft_super.fs_feat.sf_rec_xfer_align     = 0;
		result->ft_super.fs_feat.sf_name_max           = LFN_SEQNUM_MAXCOUNT * LFN_NAME;
		result->ft_super.fs_feat.sf_filesizebits       = 32;

		/* Select root directory operators. */
		result->ft_super.fs_root.mf_ops = result->ft_type == FAT32
		                                  ? &Fat32_SuperOps.so_fdir.dno_node.no_file
		                                  : &Fat16_SuperOps.so_fdir.dno_node.no_file;
	} EXCEPT {
		kfree(result);
		RETHROW();
	}
	printk(KERN_INFO "[fat] Load FAT%u-filesystem on "
	                 "%.2" PRIxN(__SIZEOF_MAJOR_T__) ":"
	                 "%.2" PRIxN(__SIZEOF_MINOR_T__) " "
	                 "[oem=%q] [label=%q] [sysname=%q]\n",
	       result->ft_type == FAT12 ? 12 : result->ft_type == FAT16 ? 16 : 32,
	       MAJOR(dev->dn_devno), MINOR(dev->dn_devno),
	       result->ft_oem, result->ft_label, result->ft_sysname);
	return &result->ft_super;
}



/************************************************************************/
/* FAT Filesystem Type                                                  */
/************************************************************************/
PRIVATE struct ffilesys Fat_Filesys = {
	.ffs_drv = &drv_self,
	{ .ffs_open = &Fat_OpenFileSystem },
	.ffs_flags = FFILESYS_F_NORMAL,
	.ffs_name  = "fat",
};




/************************************************************************/
/* Filesystem Type register/unregister                                  */
/************************************************************************/
#ifdef CONFIG_BUILDING_KERNEL_CORE
INTERN ATTR_FREETEXT void KCALL kernel_initialize_fat_driver(void)
#else  /* CONFIG_BUILDING_KERNEL_CORE */
PRIVATE DRIVER_INIT ATTR_FREETEXT void KCALL Fat_Init(void)
#endif /* !CONFIG_BUILDING_KERNEL_CORE */
{
	ffilesys_register(&Fat_Filesys);
}

#ifndef CONFIG_BUILDING_KERNEL_CORE
PRIVATE DRIVER_FINI void KCALL Fat_Fini(void) {
	ffilesys_unregister(&Fat_Filesys);
}
#endif /* !CONFIG_BUILDING_KERNEL_CORE */

DECL_END

#endif /* !CONFIG_USE_NEW_FS */

#endif /* !GUARD_MODFAT_FAT_C */
