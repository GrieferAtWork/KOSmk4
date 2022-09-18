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
#ifndef GUARD_MODFAT_FAT_C
#define GUARD_MODFAT_FAT_C 1
#define __WANT_FNODE__fn_suplop
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include "fat.h"
/**/

#include <kernel/compiler.h>

#include <kernel/driver-callbacks.h>
#include <kernel/except.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/filesys.h>
#include <kernel/fs/lnknode.h>
#include <kernel/fs/node.h>
#include <kernel/fs/notify-config.h> /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
#include <kernel/fs/regnode.h>
#include <kernel/fs/super.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/cc.h>
#include <kernel/mman/kram.h>
#include <kernel/mman/map.h>
#include <kernel/mman/phys.h>
#include <kernel/printk.h>
#include <kernel/user.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/bit.h>
#include <hybrid/byteorder.h>
#include <hybrid/byteswap.h>
#include <hybrid/overflow.h>
#include <hybrid/unaligned.h>

#include <compat/config.h>
#include <kos/except.h>
#include <kos/except/reason/fs.h>
#include <kos/except/reason/inval.h>
#include <linux/magic.h>
#include <linux/msdos_fs.h>
#include <sys/stat.h>

#include <alloca.h>
#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unicode.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/linux/msdos_fs.h>
#ifndef __COMPAT_FAT_DIRENT_MATCHES_FAT_DIRENT
#define NEED_COMPAT_IOCTL_FAT_READDIR
#endif /* !__COMPAT_FAT_DIRENT_MATCHES_FAT_DIRENT */
#endif /* __ARCH_HAVE_COMPAT */

#ifdef NEED_COMPAT_IOCTL_FAT_READDIR
#include <kernel/compat.h>

#include <compat/kos/types.h>
#endif /* NEED_COMPAT_IOCTL_FAT_READDIR */

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

#define FAT_ISSPACE(c) (isspace(c) || iscntrl(c) /* || isblank(c)*/)

static_assert(sizeof(struct fat_dirent) == 32);

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
NOTHROW(FCALL FatFileBTime_Encode)(struct fat_filebtime *__restrict self,
                                   struct timespec const *__restrict value) {
	FatFileDate_Encode(&self->fb_date, value->tv_sec);
	FatFileTime_Encode(&self->fb_time, value->tv_sec);
	self->fb_sectenth = (u8)(value->tv_nsec / (1000000000ul / 200ul));
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL FatFileBTime_Decode)(struct fat_filebtime const *__restrict self,
                                   struct timespec *__restrict result) {
	result->tv_sec  = FatFileDate_Decode(&self->fb_date);
	result->tv_sec += FatFileTime_Decode(&self->fb_time);
	result->tv_nsec = (syscall_ulong_t)self->fb_sectenth * (1000000000ul / 200ul);
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
/* FAT directory entry helper functions                                 */
/************************************************************************/
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fatdirent_v_destroy)(struct fdirent *__restrict self) {
	struct fatdirent *me;
	me = fdirent_asfat(self);
	_fatdirent_free(me);
}
#define _fatdirent_destroy(self) fatdirent_v_destroy(&(self)->fad_ent.fde_ent)
DEFINE_REFCNT_FUNCTIONS(struct fatdirent, fad_ent.fde_ent.fd_refcnt, _fatdirent_destroy)
PRIVATE struct fdirent_ops const fatdirent_ops = {
	.fdo_destroy  = &fatdirent_v_destroy,
	.fdo_opennode = &flatdirent_v_opennode,
};





/************************************************************************/
/* FAT Cluster helper functions                                         */
/************************************************************************/
PRIVATE WUNUSED NONNULL((1)) FatClusterIndex KCALL
Fat_FindFreeCluster(FatSuperblock *__restrict self) {
	FatClusterIndex result;
	assert(FatSuper_FatLockReading(self));
	result = self->ft_free_pos;
	for (; result < self->ft_cluster_eof; ++result) {
		if (Fat_GetFatIndirection(self, result) == FAT_CLUSTER_UNUSED)
			goto found_one;
	}
	/* Scan everything before our previous location. */
	static_assert(FAT_CLUSTER_UNUSED == 0);
	result = 1; /* 1: Don't allow use of `FAT_CLUSTER_UNUSED' (which is `0') */
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
Fat_DeleteClusterChain(FatSuperblock *__restrict self,
                       FatClusterIndex first_delete_index) {
	FatSuper_FatLockWrite(self);
	RAII_FINALLY { FatSuper_FatLockEndWrite(self); };
	while (first_delete_index < self->ft_cluster_eof &&
	       first_delete_index != FAT_CLUSTER_UNUSED) {
		FatClusterIndex next = Fat_GetFatIndirection(self, first_delete_index);
		Fat_SetFatIndirection(self, first_delete_index, FAT_CLUSTER_UNUSED);
		first_delete_index = next;
	}
}


PRIVATE NONNULL((1, 2, 3)) void KCALL
preallocate_cluster_vector_entries(struct fnode *__restrict node,
                                   FatNodeData *__restrict data,
                                   FatSuperblock *__restrict fat,
                                   size_t min_num_clusters)
		THROWS(...) {
	size_t new_alloc, old_alloc;
	FatClusterIndex *newvec;
	assert(min_num_clusters >= data->fn_clusterc);
	new_alloc = (size_t)CEILDIV(atomic64_read(&node->mf_filesize), fat->ft_clustersize);
	if (new_alloc < min_num_clusters)
		new_alloc = min_num_clusters;
	if unlikely(new_alloc <= 0)
		new_alloc = 2;
	old_alloc = kmalloc_usable_size(data->fn_clusterv) / sizeof(FatClusterIndex);
	assert(old_alloc >= 1);
	if unlikely(new_alloc <= old_alloc)
		return; /* nothing to do here... */
	newvec = (FatClusterIndex *)krealloc_nx(data->fn_clusterv,
	                                        new_alloc * sizeof(FatClusterIndex),
	                                        GFP_NORMAL);
	if (!newvec) {
		new_alloc = min_num_clusters;
		if unlikely(new_alloc <= 0)
			new_alloc = 2;
		if unlikely(new_alloc <= old_alloc)
			return; /* nothing to do here... */
		newvec = (FatClusterIndex *)krealloc(data->fn_clusterv,
		                                     new_alloc * sizeof(FatClusterIndex),
		                                     GFP_NORMAL);
	}
	data->fn_clusterv = newvec;
}

LOCAL NONNULL((1)) void KCALL
zero_initialize_cluster(FatSuperblock *__restrict fat,
                        FatClusterIndex cluster)
		THROWS(...) {
	/* XXX: Implement me? */
	(void)fat;
	(void)cluster;
}


/* Flags for `Fat_GetFileCluster::mode' */
#define FAT_GETCLUSTER_MODE_FNORMAL 0x0000 /* If that cluster hasn't been  loaded yet, load it now.  If
                                            * the cluster doesn't exist, return `ft_cluster_eof_marker' */
#define FAT_GETCLUSTER_MODE_FCREATE 0x0001 /* Allocate missing clusters. */
#define FAT_GETCLUSTER_MODE_FNCHNGE 0x0002 /* Don't mark the node as changed if the initial cluster was allocated. */
#define FAT_GETCLUSTER_MODE_WRLOCK  0x0004 /* Caller is holding a write-lock to `self->fn_fsdata->fn_lock' */

/* Special return value for `Fat_GetFileCluster()' */
#define FAT_GETFILECLUSTER_NEED_WRLOCK FAT_CLUSTER_UNUSED

/* Returns the cluster index of the `nth_cluster' cluster that is allocated for `self'.
 * NOTE: The caller must be holding at least a read-lock to `self->fn_fsdata->fn_lock'
 * @param: mode: Set of `FAT_GETCLUSTER_MODE_F*'
 * @return: * : The value of the `nth_cluster' cluster.
 * @return: FAT_GETFILECLUSTER_NEED_WRLOCK: `FAT_GETCLUSTER_MODE_WRLOCK' isn't  given,
 *                                          and  a read-lock could  not be upgraded to
 *                                          a write-lock. - Release read-lock and wait
 *                                          for write to become available. Then retry. */
PRIVATE NONNULL((1)) FatClusterIndex KCALL
Fat_GetFileCluster(struct fnode *__restrict self,
                   size_t nth_cluster, unsigned int mode) {
	FatClusterIndex result;
	FatNodeData *dat     = self->fn_fsdata;
	FatSuperblock *super = fsuper_asfat(self->fn_super);
	assert(FatNodeData_Reading(dat));
	assert(dat->fn_clusterc != 0);
	if (nth_cluster < dat->fn_clusterc) {
		result = dat->fn_clusterv[nth_cluster];
		assert(result != FAT_CLUSTER_UNUSED);
		if (result < super->ft_cluster_eof)
			return result; /* Simple case: cluster already cached. */
		assert(nth_cluster == dat->fn_clusterc - 1);
	} else {
		result = dat->fn_clusterv[dat->fn_clusterc - 1];
		assert(result != FAT_CLUSTER_UNUSED);
		if (result < super->ft_cluster_eof) {
			/* Not all clusters have been loaded, yet. -> load more now. */
			if (!(mode & FAT_GETCLUSTER_MODE_WRLOCK)) {
				if (!FatNodeData_TryUpgrade(dat))
					return FAT_GETFILECLUSTER_NEED_WRLOCK;
			}
			TRY {
				preallocate_cluster_vector_entries(self, dat, super, nth_cluster + 1);
				for (;;) {
					result = Fat_GetFatIndirection(super, result);
					if unlikely(result == FAT_CLUSTER_UNUSED)
						THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);
					dat->fn_clusterv[dat->fn_clusterc] = result;
					++dat->fn_clusterc;
					if (result >= super->ft_cluster_eof) {
						FatClusterIndex *new_vector;
						/* EOF reached before `nth_cluster' */
						if (mode & FAT_GETCLUSTER_MODE_FCREATE)
							goto create_more_clusters_already_locked;
						/* Try to free unused memory. */
						new_vector = (FatClusterIndex *)krealloc_nx(dat->fn_clusterv,
						                                            dat->fn_clusterc *
						                                            sizeof(FatClusterIndex),
						                                            GFP_NORMAL);
						if likely(new_vector)
							dat->fn_clusterv = new_vector;
						if (!(mode & FAT_GETCLUSTER_MODE_WRLOCK))
							FatNodeData_Downgrade(dat);
						return result;
					}
					if (nth_cluster < dat->fn_clusterc) {
						/* The requested cluster was reached */
						assert(nth_cluster == dat->fn_clusterc - 1);
						assert(result == dat->fn_clusterv[nth_cluster]);
						assert(result != FAT_CLUSTER_UNUSED);
						break;
					}
				}
			} EXCEPT {
				if (!(mode & FAT_GETCLUSTER_MODE_WRLOCK))
					FatNodeData_Downgrade(dat);
				RETHROW();
			}
			if (!(mode & FAT_GETCLUSTER_MODE_WRLOCK))
				FatNodeData_Downgrade(dat);
			return result;
		}
	}

	/* All clusters are loaded, and the file potentially needs to be expanded. */
	assert(dat->fn_clusterv[dat->fn_clusterc - 1] >= super->ft_cluster_eof);
	if (!(mode & FAT_GETCLUSTER_MODE_FCREATE))
		return super->ft_cluster_eof_marker; /* EOF */

	/* Not all clusters have been loaded, yet. -> load more now. */
	if (!(mode & FAT_GETCLUSTER_MODE_WRLOCK)) {
		if (!FatNodeData_TryUpgrade(dat))
			return FAT_GETFILECLUSTER_NEED_WRLOCK;
	}
create_more_clusters_already_locked:
	TRY {
		preallocate_cluster_vector_entries(self, dat, super, nth_cluster + 2);
		FatSuper_FatLockWrite(super);
		RAII_FINALLY { FatSuper_FatLockEndWrite(super); };
		assert(dat->fn_clusterv[dat->fn_clusterc - 1] >= super->ft_cluster_eof);
		/* Create more clusters. */
		for (;;) {
			result = Fat_FindFreeCluster(super);
			assert(result != FAT_CLUSTER_UNUSED);
			/* Mark the new cluster as allocated. */
			Fat_SetFatIndirection(super, result,
			                      super->ft_cluster_eof_marker);
			TRY {
				/* Initialize new clusters with all zeroes for new files. */
				if (fnode_isreg(self))
					zero_initialize_cluster(super, result);
				assert(super->ft_cluster_eof_marker != FAT_CLUSTER_UNUSED);
				assert((kmalloc_usable_size(dat->fn_clusterv)) >=
				       (dat->fn_clusterc + 1) * sizeof(FatClusterIndex));
				dat->fn_clusterv[dat->fn_clusterc - 1] = result;
				dat->fn_clusterv[dat->fn_clusterc] = super->ft_cluster_eof_marker;
				++dat->fn_clusterc;
				TRY {
					if (dat->fn_clusterc == 2) {
						/* The pointer  to  the  first  cluster is  stored  in  the  INode.
						 * Since we've just written that pointer, mark the node as changed. */
						if (!(mode & FAT_GETCLUSTER_MODE_FNCHNGE))
							mfile_changed(self, MFILE_F_ATTRCHANGED);
					} else {
						/* Link the previous cluster onto the new one */
						assert(dat->fn_clusterc >= 3);
						/* -3: PREV_CLUSTER */
						/* -2: THIS_CLUSTER */
						/* -1: fat->ft_cluster_eof_marker */
						Fat_SetFatIndirection(super,
						                      dat->fn_clusterv[dat->fn_clusterc - 3],
						                      result);
					}
				} EXCEPT {
					--dat->fn_clusterc;
					assert(dat->fn_clusterv[dat->fn_clusterc - 1] == result);
					assert(super->ft_cluster_eof_marker != FAT_CLUSTER_UNUSED);
					dat->fn_clusterv[dat->fn_clusterc - 1] = super->ft_cluster_eof_marker;
					RETHROW();
				}
			} EXCEPT {
				/* Free the new cluster on error. */
				{
					NESTED_EXCEPTION;
					Fat_SetFatIndirection(super, result, FAT_CLUSTER_UNUSED);
				}
				RETHROW();
			}
			if (nth_cluster < dat->fn_clusterc - 1) {
				/* The requested cluster was reached */
				assert(nth_cluster == dat->fn_clusterc - 2);
				assert(result == dat->fn_clusterv[nth_cluster]);
				break;
			}
		}
	} EXCEPT {
		if (!(mode & FAT_GETCLUSTER_MODE_WRLOCK))
			FatNodeData_Downgrade(dat);
		RETHROW();
	}
	assert(result == dat->fn_clusterv[nth_cluster]);
	assert(result < super->ft_cluster_eof);
	assert(result != FAT_CLUSTER_UNUSED);
	if (!(mode & FAT_GETCLUSTER_MODE_WRLOCK))
		FatNodeData_Downgrade(dat);
	return result;
}



/* Returns the absolute on-disk (read: on-partition) position of `pos' in `self'
 * Caller  must be  holding at  least a  read-lock to `self->fn_fsdata->fn_lock'
 * @return: 0 : s.a. `FAT_GETFILECLUSTER_NEED_WRLOCK' */
PRIVATE NONNULL((1)) pos_t KCALL
Fat_GetAbsDiskPosWithClusters(struct fnode *__restrict self, pos_t pos,
                              unsigned int mode = FAT_GETCLUSTER_MODE_FCREATE) THROWS(...) {
	pos_t diskpos;
	FatSuperblock *super = fsuper_asfat(self->fn_super);
	FatClusterIndex cluster;
	size_t cluster_number = (size_t)(pos / super->ft_clustersize);
	size_t cluster_offset = (size_t)(pos % super->ft_clustersize);
	cluster = Fat_GetFileCluster(self, cluster_number, mode);
	if (cluster == FAT_GETFILECLUSTER_NEED_WRLOCK)
		return 0;
	diskpos = FAT_CLUSTERADDR(super, cluster);
	diskpos += cluster_offset;
	return diskpos;
}
#define fnode_has_fat_clusters(self) \
	(!fnode_issuper(self) || fnode_asfatsup(self)->ft_type == FAT32)
#define Fat_GetAbsDiskPosWithoutFatClusters(self, pos) \
	((pos) + fnode_asfatsup(self)->ft_fdat.fn16_root.r16_rootpos)

PRIVATE NONNULL((1)) pos_t KCALL
Fat_GetAbsDiskPos(struct fnode *__restrict self, pos_t pos) THROWS(...) {
	FatNodeData *dat = self->fn_fsdata;
	pos_t result;
	if (fnode_has_fat_clusters(self)) {
		for (;;) {
			FatNodeData_Read(dat);
			{
				RAII_FINALLY { FatNodeData_EndRead(dat); };
				result = Fat_GetAbsDiskPosWithClusters(self, pos, FAT_GETCLUSTER_MODE_FCREATE);
			}
			if (result != 0)
				break;

			/* Wait for writing to become possible. */
			FatNodeData_WaitWrite(dat);
		}
	} else {
		result = Fat_GetAbsDiskPosWithoutFatClusters(self, pos);
	}
	return result;
}





/************************************************************************/
/* FAT operator implementations.                                        */
/************************************************************************/
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL FatNodeData_Fini)(FatNodeData *__restrict self) {
	xdecref(self->fn_ent);
	xdecref(self->fn_dir);
	kfree(self->fn_clusterv);
}

PRIVATE NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1)) void
NOTHROW(KCALL fat_v_cc)(struct mfile *__restrict self,
                        struct ccinfo *__restrict info) {
	size_t usable, needed;
	struct fnode *me = mfile_asnode(self);
	FatNodeData *dat = me->fn_fsdata;
	if (fnode_issuper(me) && fnode_asfatsup(me)->ft_type != FAT32)
		return; /* Special case in which the cluster-vector isn't valid. */
	if (!FatNodeData_TryWrite(dat)) {
		if (ccinfo_noblock(info))
			return;
		if (!FatNodeData_WriteNx(dat))
			return;
	}

	/* Try to truncate the cluster vector. */
	usable = kmalloc_usable_size(dat->fn_clusterv);
	needed = dat->fn_clusterc * sizeof(FatClusterIndex);
	assert(usable >= needed);
	if (usable > needed) {
		FatClusterIndex *newvec;
		newvec = (FatClusterIndex *)krealloc_nx(dat->fn_clusterv, needed, info->ci_gfp);
		if (newvec != NULL) {
			size_t new_usable;
			dat->fn_clusterv = newvec;
			/* Account for how much memory we're now saving. */
			new_usable = kmalloc_usable_size(dat->fn_clusterv);
			if (usable > new_usable)
				ccinfo_account(info, usable - new_usable);
		}
	}
	FatNodeData_EndWrite(dat);
}


PRIVATE NONNULL((1, 5)) void KCALL
fat_v_loadblocks(struct mfile *__restrict self, pos_t addr,
                 physaddr_t buf, size_t num_bytes,
                 struct aio_multihandle *__restrict aio) {
	struct fnode *me     = mfile_asnode(self);
	FatNodeData *dat     = me->fn_fsdata;
	FatSuperblock *super = fsuper_asfat(me->fn_super);
	assertf((addr & super->ft_sectormask) == 0, "Unaligned `addr = %#" PRIx64 "'", (uint64_t)addr);
	assertf((num_bytes & super->ft_sectormask) == 0, "Unaligned `num_bytes = %#" PRIxSIZ "'", num_bytes);
	assert(num_bytes != 0);
again:
	FatNodeData_Read(dat);
	{
		RAII_FINALLY { FatNodeData_EndRead(dat); };
		for (;;) {
			FatClusterIndex cluster;
			pos_t diskpos;
			size_t cluster_number = (size_t)(addr / super->ft_clustersize);
			size_t cluster_offset = (size_t)(addr % super->ft_clustersize);
			size_t max_io;
			cluster = Fat_GetFileCluster(me, cluster_number, FAT_GETCLUSTER_MODE_FNORMAL);
			if unlikely(cluster == FAT_GETFILECLUSTER_NEED_WRLOCK)
				goto waitfor_write_lock;
			if (cluster >= super->ft_cluster_eof) {
				/* Read all ZEROes after EOF. */
				bzerophyscc(buf, num_bytes);
				return;
			}
			diskpos = FAT_CLUSTERADDR(super, cluster);
			diskpos += cluster_offset;
			max_io = super->ft_clustersize - cluster_offset;
			/* Optimization: When reading  large amounts  of data,  check if  the
			 *               underlying disk chunks were allocated consecutively.
			 *               If they are,  then we can  simply do one  continuous
			 *               read, processing more  than one cluster  at a  time. */
			while (max_io < num_bytes) {
				FatClusterIndex next_cluster;
				next_cluster = Fat_GetFileCluster(me, cluster_number + 1, FAT_GETCLUSTER_MODE_FNORMAL);
				if (next_cluster != cluster + 1) {
					if unlikely(next_cluster == FAT_GETFILECLUSTER_NEED_WRLOCK)
						goto waitfor_write_lock;
					break;
				}
				max_io += super->ft_clustersize;
				++cluster_number;
				++cluster;
			}
			if (max_io > num_bytes)
				max_io = num_bytes;
			/* Do disk I/O */
			fsuper_dev_rdsectors_async_chk(&super->ft_super.ffs_super,
			                               diskpos, buf, max_io, aio);
			if (max_io >= num_bytes)
				break;
			num_bytes -= max_io;
			addr += max_io;
			buf += max_io;
		}
	}
	return;
waitfor_write_lock:
	FatNodeData_WaitWrite(dat);
	goto again;
}

PRIVATE NONNULL((1, 5)) void KCALL
fat_v_saveblocks(struct mfile *__restrict self, pos_t addr,
                 physaddr_t buf, size_t num_bytes,
                 struct aio_multihandle *__restrict aio) {
	struct fnode *me     = mfile_asnode(self);
	FatNodeData *dat     = me->fn_fsdata;
	FatSuperblock *super = fsuper_asfat(me->fn_super);
	assertf((addr & super->ft_sectormask) == 0, "Unaligned `addr = %#" PRIx64 "'", (uint64_t)addr);
	assertf((num_bytes & super->ft_sectormask) == 0, "Unaligned `num_bytes = %#" PRIxSIZ "'", num_bytes);
	assert(num_bytes != 0);
again:
	/* Yes: We only need a read-lock  here since this lock isn't  used
	 *      to guard the actual file-contents, but only the vector  of
	 *      cluster indices (if said vector needs to be modified, this
	 *      lock is later upgraded as necessary) */
	FatNodeData_Read(dat);
	{
		RAII_FINALLY { FatNodeData_EndRead(dat); };
		for (;;) {
			FatClusterIndex cluster;
			pos_t diskpos;
			size_t cluster_number = (size_t)(addr / super->ft_clustersize);
			size_t cluster_offset = (size_t)(addr % super->ft_clustersize);
			size_t max_io;
			cluster = Fat_GetFileCluster(me, cluster_number, FAT_GETCLUSTER_MODE_FCREATE);
			if unlikely(cluster == FAT_GETFILECLUSTER_NEED_WRLOCK)
				goto waitfor_write_lock;
			diskpos = FAT_CLUSTERADDR(super, cluster);
			diskpos += cluster_offset;
			max_io = super->ft_clustersize - cluster_offset;
			/* Optimization: When writing  large amounts  of data,  check if  the
			 *               underlying disk chunks were allocated consecutively.
			 *               If they are,  then we can  simply do one  continuous
			 *               write, processing more than  one cluster at a  time. */
			while (max_io < num_bytes) {
				FatClusterIndex next_cluster;
				next_cluster = Fat_GetFileCluster(me, cluster_number + 1, FAT_GETCLUSTER_MODE_FCREATE);
				if (next_cluster != cluster + 1) {
					if unlikely(next_cluster == FAT_GETFILECLUSTER_NEED_WRLOCK)
						goto waitfor_write_lock;
					break;
				}
				max_io += super->ft_clustersize;
				++cluster_number;
				++cluster;
			}
			if (max_io > num_bytes)
				max_io = num_bytes;

			/* Do disk I/O */
			if unlikely(super->ft_super.ffs_super.fs_dev->mf_flags & MFILE_F_READONLY)
				THROW(E_FSERROR_READONLY);
			fsuper_dev_wrsectors_async_chk(&super->ft_super.ffs_super,
			                               diskpos, buf, max_io, aio);
			if (max_io >= num_bytes)
				break;
			num_bytes -= max_io;
			addr += max_io;
			buf += max_io;
		}
	}
	return;
waitfor_write_lock:
	FatNodeData_WaitWrite(dat);
	goto again;
}

PRIVATE NONNULL((1)) void KCALL
fat_v_wrattr(struct fnode *__restrict self)
		THROWS(E_IOERROR, ...) {
	FatNodeData *dat     = self->fn_fsdata;
	FatSuperblock *super = fsuper_asfat(self->fn_super);
	REF struct fatdirent *ent;
	REF FatDirNode *dir;

again:
	mfile_tslock_acquire(self);
	assert((dat->fn_ent != NULL) == (dat->fn_dir != NULL));
	dir = dat->fn_dir;
	if unlikely(!dir) {
		/* File was deleted. */
		mfile_tslock_release_br(self);
		return;
	}
	ent = dat->fn_ent;
	incref(dir);
	incref(ent);
	mfile_tslock_release(self);
	FINALLY_DECREF_UNLIKELY(dir);
	FINALLY_DECREF_UNLIKELY(ent);

	/* Acquire a lock to the directory stream buffer. */
	flatdirnode_write(dir);
	RAII_FINALLY { flatdirnode_endwrite(dir); };

	/* Re-check that nothing's changed (and `dir' is still correct) */
	mfile_tslock_acquire(self);
	if unlikely(dir != dat->fn_dir || ent != dat->fn_ent) {
		mfile_tslock_release_br(self);
		goto again;
	}
	mfile_tslock_release(self);

	if likely(!flatdirent_wasdeleted(&ent->fad_ent)) {
		FatClusterIndex first_cluster;
		mode_t fmode;
		struct timespec atm, mtm, btm;
		gid_t gid;
		uid_t uid;

		/* Load file attributes */
		mfile_tslock_acquire(self);
		fmode = self->fn_mode;
		atm   = self->mf_atime;
		mtm   = self->mf_mtime;
		btm   = self->mf_btime;
		gid   = self->fn_gid;
		uid   = self->fn_uid;
		mfile_tslock_release(self);

		/* Check if loaded attributes are valid */
		if unlikely(ATOMIC_READ(self->mf_flags) & MFILE_F_DELETED)
			return;

		/* Update the contents of `ent->fad_dos' */
		first_cluster = dat->fn_clusterv[0];

		/* Copy basic file data. */
		ent->fad_dos.f_clusterlo = HTOLE16(first_cluster & 0xffff);
		if (super->ft_features & FAT_FEATURE_ARB) {
			u16 arb = 0;
			/* Use the ARB to implement unix file permissions. */
			if (!(fmode & S_IXUSR))
				arb |= FAT_ARB_NO_OX; /* Disable: Execute by owner */
			if (!(fmode & S_IWUSR))
				arb |= FAT_ARB_NO_OW; /* Disable: Write by owner */
			if (!(fmode & S_IRUSR))
				arb |= FAT_ARB_NO_OR; /* Disable: Read by owner */

			if (!(fmode & S_IXGRP))
				arb |= FAT_ARB_NO_GX; /* Disable: Execute by group */
			if (!(fmode & S_IWGRP))
				arb |= FAT_ARB_NO_GW; /* Disable: Write by group */
			if (!(fmode & S_IRGRP))
				arb |= FAT_ARB_NO_GR; /* Disable: Read by group */

			if (!(fmode & S_IXOTH))
				arb |= FAT_ARB_NO_WX; /* Disable: Execute by world */
			if (!(fmode & S_IWOTH))
				arb |= FAT_ARB_NO_WW; /* Disable: Write by world */
			if (!(fmode & S_IROTH))
				arb |= FAT_ARB_NO_WR; /* Disable: Read by world */
			if (!(fmode & 0222)) {
				/* Preserve ARB flags  for write permissions  if those  can
				 * already be represented through use of the READONLY flag. */
				arb &= ~(FAT_ARB_NO_OW | FAT_ARB_NO_GW | FAT_ARB_NO_WW);
				arb |= LETOH16(ent->fad_dos.f_arb) & (FAT_ARB_NO_OW | FAT_ARB_NO_GW | FAT_ARB_NO_WW);
			}
			ent->fad_dos.f_arb = HTOLE16(arb);
		} else {
			/* 32-bit clusters */
			ent->fad_dos.f_clusterhi = HTOLE16((u16)(first_cluster >> 16));
		}
		ent->fad_dos.f_size = HTOLE32((u32)atomic64_read(&self->mf_filesize));
		if (fnode_isdir(self)) /* Directories should have size=0 */
			ent->fad_dos.f_size = HTOLE32(0);

		/* Implement the read-only attribute. */
		if (!(fmode & 0222))
			ent->fad_dos.f_attr |= FATATTR_RO;

		if (super->ft_features & FAT_FEATURE_UGID) {
			/* UID/GID support */
			ent->fad_dos.f_uid = (u8)uid;
			ent->fad_dos.f_gid = (u8)gid;
		} else {
			/* Last-access timestamp support */
			FatFileATime_Encode(&ent->fad_dos.f_atime, &atm);
		}

		/* Convert timestamps. */
		FatFileMTime_Encode(&ent->fad_dos.f_mtime, &mtm);
		FatFileBTime_Encode(&ent->fad_dos.f_btime, &btm);

		/* Set the ARCHIVE flag to indicate a file that has been modified. */
		ent->fad_dos.f_attr |= FATATTR_ARCH;

		/* Write `ent->fad_dos' back into the directory stream. */
		mfile_write(dir, &ent->fad_dos, sizeof(struct fat_dirent),
		            fatdirent_dosaddr(ent));
	}
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fatreg_v_destroy)(struct mfile *__restrict self) {
	FatRegNode *me = mfile_asfatreg(self);
	FatNodeData_Fini(&me->frn_fdat);
	fregnode_v_destroy(self);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fatdir_v_destroy)(struct mfile *__restrict self) {
	FatDirNode *me = mfile_asfatdir(self);
	FatNodeData_Fini(&me->fdn_fdat);
	flatdirnode_v_destroy(self);
}

#ifdef CONFIG_HAVE_MODFAT_CYGWIN_SYMLINKS
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fatlnk_v_destroy)(struct mfile *__restrict self) {
	FatLnkNode *me = mfile_asfatlnk(self);
	FatNodeData_Fini(&me->fln_fdat);
	flnknode_v_destroy(self);
}

PRIVATE byte_t const Fat_CygwinSymlinkMagic[] = { '!', '<', 's', 'y', 'm', 'l', 'i', 'n', 'k', '>' };

/* Minimum size requirement for symbolic links. */
#define FAT_SYMLINK_FILE_TEXTOFF          (sizeof(Fat_CygwinSymlinkMagic))
#define FAT_SYMLINK_FILE_MINSIZE          (sizeof(Fat_CygwinSymlinkMagic) + 1)
#define FAT_SYMLINK_FILE_TEXTLEN(filesiz) ((filesiz) - FAT_SYMLINK_FILE_MINSIZE)

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
fatlnk_v_readlink(struct flnknode *__restrict self,
                  USER CHECKED /*utf-8*/ char *buf,
                  size_t bufsize)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	size_t result;
	FatLnkNode *me = flnknode_asfat(self);
	pos_t filepos;
	result = (size_t)_atomic64_val(me->mf_filesize);
	assert(result >= FAT_SYMLINK_FILE_MINSIZE);
	result = FAT_SYMLINK_FILE_TEXTLEN(result);
	if (bufsize > result)
		bufsize = result;
	filepos = (pos_t)FAT_SYMLINK_FILE_TEXTOFF;

	/* Try to make use of the cache already loaded during `fatdir_v_readdir()'
	 * As such, anything that falls into the first file sect we read  directly
	 * from disk.
	 *
	 * NOTE: Must  _ONLY_ do so if the symlink content hasn't already been
	 *       allocated within the unified I/O cache of the symlink itself.
	 *       The  later would be the case for freshly created symlinks, as
	 *       opposed to ones that were already present on-disk. */
#if 1
	if (ATOMIC_READ(me->mf_parts) == NULL) {
		if likely(mfile_getblocksize(me) >= FAT_SYMLINK_FILE_TEXTOFF) {
			pos_t diskpos;
			size_t disksiz;
			diskpos = Fat_GetAbsDiskPos(self, filepos);
			disksiz = mfile_getblocksize(me) - (size_t)filepos;
			if (disksiz > bufsize)
				disksiz = bufsize;
			mfile_readall(me->fn_super->fs_dev, buf, disksiz, diskpos);
			if likely(disksiz >= bufsize)
				return result;
			buf = (USER CHECKED char *)((byte_t *)buf + disksiz);
			bufsize -= disksiz;
			filepos += disksiz;
		}
	}
#endif

	/* Read file contents */
	mfile_readall(me, buf, bufsize, filepos);
	return result;
}

PRIVATE NONNULL((1)) void KCALL
fatlnk_v_stat(struct mfile *__restrict self,
              USER CHECKED struct stat *result)
		THROWS(...) {
	FatLnkNode *me  = flnknode_asfat(self);
	result->st_size = _atomic64_val(me->mf_filesize) -
	                  (sizeof(Fat_CygwinSymlinkMagic) + 1);
}
#endif /* CONFIG_HAVE_MODFAT_CYGWIN_SYMLINKS */

PRIVATE NONNULL((1)) void
NOTHROW(FCALL strlwrz)(char *__restrict str, size_t len) {
	size_t i;
	for (i = 0; i < len; ++i)
		str[i] = tolower(str[i]);
}

PRIVATE NONNULL((1, 2)) /*utf-8*/ char *
NOTHROW(FCALL decode_latin1)(/*utf-8*/ char *__restrict dest,
                             /*latin-1*/ char const *__restrict text,
                             size_t len) {
	size_t i;
	for (i = 0; i < len; ++i)
		dest = unicode_writeutf8(dest, (unsigned char)text[i]);
	return dest;
}



#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Waddress-of-packed-member"
#endif /* __GNUC__ */

PRIVATE WUNUSED struct flatdirent *KCALL
fatdir_v_readdir(struct flatdirnode *__restrict self, pos_t pos)
		THROWS(E_BADALLOC, E_IOERROR) {
	struct fatdirent *result;
	struct fat_dirent ent;
	FatDirNode *me = flatdirnode_asfat(self);
	assert((pos % sizeof(struct fat_dirent)) == 0);

	/* Read the next entry from disk. */
readnext:
	if (mfile_read(self, &ent, sizeof(struct fat_dirent), pos) < sizeof(struct fat_dirent))
		return NULL; /* Forced EOF */

	/* Check for special markers. */
	if (ent.f_marker == MARKER_DIREND)
		return NULL; /* End of directory */
	if (ent.f_marker == MARKER_UNUSED) {
		pos += sizeof(struct fat_dirent);
		goto readnext;
	}

	/* Check for LFN entries. */
	if (ent.f_attr == FATATTR_LFN) {
		char lfn_name[LFN_SEQNUM_MAXCOUNT * UNICODE_16TO8_MAXBUF(LFN_NAME)];
		u32 lfn_valid   = 0;
		pos_t lfn_start = pos;
		pos += sizeof(struct fat_dirent);
		do {
			shift_t index = (ent.lfn_seqnum & 0x1f) - 1;
			char *dst     = lfn_name + (size_t)index * UNICODE_16TO8_MAXBUF(LFN_NAME);
			char *end     = dst + UNICODE_16TO8_MAXBUF(LFN_NAME);
			char16_t *textend;
			lfn_valid |= 1 << index;
#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
			{
				unsigned int i;
				for (i = 0; i < LFN_NAME1; ++i)
					ent.lfn_name_1[i] = HTOLE16((u16)ent.lfn_name_1[i]);
				for (i = 0; i < LFN_NAME2; ++i)
					ent.lfn_name_2[i] = HTOLE16((u16)ent.lfn_name_2[i]);
				for (i = 0; i < LFN_NAME3; ++i)
					ent.lfn_name_3[i] = HTOLE16((u16)ent.lfn_name_3[i]);
			}
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
			textend = (char16_t *)memchrw(ent.lfn_name_1, 0xffff, LFN_NAME1);
			if (textend) {
				dst = unicode_16to8(dst, (char16_t *)ent.lfn_name_1,
				                    textend - (char16_t *)ent.lfn_name_1);
			} else {
				dst     = unicode_16to8(dst, (char16_t *)ent.lfn_name_1, LFN_NAME1);
				textend = (char16_t *)memchrw(ent.lfn_name_2, 0xffff, LFN_NAME2);
				if (textend) {
					dst = unicode_16to8(dst, (char16_t *)ent.lfn_name_2,
					                    textend - (char16_t *)ent.lfn_name_2);
				} else {
					dst = unicode_16to8(dst, (char16_t *)ent.lfn_name_2, LFN_NAME2);
					dst = unicode_16to8(dst, (char16_t *)ent.lfn_name_3,
					                    memlenw(ent.lfn_name_3, 0xffff, LFN_NAME3));
				}
			}
			assert(dst <= end);
			bzero(dst, (size_t)(end - dst));
			do {
				mfile_readall(self, &ent, sizeof(struct fat_dirent), pos);
				pos += sizeof(struct fat_dirent);
			} while (ent.f_marker == MARKER_UNUSED);

			/* This really shouldn't  happen, but also  deal
			 * with end-of-directory inside of LFN sequence. */
			if unlikely(ent.f_marker == MARKER_DIREND)
				return NULL;
		} while (ent.f_attr == FATATTR_LFN);

		if unlikely(lfn_valid & (lfn_valid + 1)) {
			/* `lfn_valid' isn't  a complete  mask.  (some part  of  the
			 * name might have been corrupted, or accidentally deleted?)
			 * Anyways: don't raise hell about this one and just  delete
			 *          the string portions that were affected (that way
			 *          we  at  least preserve  whatever portion  of the
			 *          filename can still be recovered) */
			unsigned int index = 0;
			u32 mask;
			while ((mask = (u32)1 << index, lfn_valid >= mask)) {
				if (lfn_valid & mask) {
					++index;
					continue;
				}
				memmovedown(lfn_name, lfn_name + UNICODE_16TO8_MAXBUF(LFN_NAME),
				            (size_t)(LFN_SEQNUM_MAXCOUNT - 1) - index,
				            UNICODE_16TO8_MAXBUF(LFN_NAME) * sizeof(char));
				lfn_valid |= mask;
				lfn_valid >>= 1;
			}
		}
		/* Merge LFN filename segments. */
		{
			char *dst, *src, *end;
			size_t len;
			dst = src = lfn_name;
			end = src + (size_t)POPCOUNT(lfn_valid) * UNICODE_16TO8_MAXBUF(LFN_NAME);
			for (; src < end;) {
				size_t off = strnlen(src, (size_t)(end - src));
				if (dst != src)
					memcpy(dst, src, off, sizeof(char));
				dst += off;
				/* Skip ahead to the next segment. */
				off += (size_t)(src - lfn_name);
				off += UNICODE_16TO8_MAXBUF(LFN_NAME) - 1;
				off = off - (off % UNICODE_16TO8_MAXBUF(LFN_NAME));
				src = lfn_name + off;
			}

			/* Safety check: if the LFN filename ends up empty, use the 8.3 name instead! */
			if unlikely(dst <= lfn_name)
				goto dos_8dot3;

			/* Allocate the directory entry. */
			len    = (size_t)(dst - lfn_name);
			result = _fatdirent_alloc(len);
			result->fad_ent.fde_ent.fd_namelen = (u16)len;
			memcpy(result->fad_ent.fde_ent.fd_name, lfn_name, len, sizeof(char));
			result->fad_ent.fde_pos  = lfn_start;
			result->fad_ent.fde_size = (size_t)(pos - lfn_start);
		}

		/* Use the position of the DOS file entry as INode number. */
		pos -= sizeof(struct fat_dirent);
	} else {
		uint8_t usedname_len;
		char usedname[11 * 2 + 2], *dstptr;
		char fixedname[11], *srcptr;
dos_8dot3:
		memcpy(fixedname, ent.f_nameext, 11);

		/* Fix lowercase filenames. */
		if (ent.f_ntflags & NTFLAG_LOWBASE)
			strlwrz(fixedname, 8);
		if (ent.f_ntflags & NTFLAG_LOWEXT)
			strlwrz(fixedname + 8, 3);
		/* Deal with this one... */
		if unlikely(ent.f_marker == MARKER_IS0XE5)
			fixedname[0] = 0xe5;

		/* Construct the proper, human-readable filename. */
		dstptr = usedname;
		srcptr = fixedname;
		while (srcptr < fixedname + 8 && isspace(*srcptr))
			++srcptr;
		dstptr = decode_latin1(dstptr, srcptr, (size_t)((fixedname + 8) - srcptr));
		while (dstptr > usedname && isspace(dstptr[-1]))
			--dstptr;
		*dstptr++ = '.';
		srcptr = fixedname + 8;
		while (srcptr < fixedname + 11 && isspace(*srcptr))
			++srcptr;
		dstptr = decode_latin1(dstptr, srcptr, (size_t)((fixedname + 11) - srcptr));
		while (dstptr > usedname && isspace(dstptr[-1]))
			--dstptr;
		if (dstptr > usedname && dstptr[-1] == '.')
			--dstptr;
		*dstptr = 0;
		usedname_len = (uint8_t)(dstptr - usedname);

		/* Check for entries that we're _supposed_ to skip over. */
		if (usedname_len <= 2) {
			if unlikely(!usedname_len) {
				/* Empty name? (well... this shouldn't happen!) */
				printk(KERN_ERR "[fat] Unnamed directory entry at "
				                "ino:%#" PRIxN(__SIZEOF_INO_T__) ","
				                "off=%" PRIuN(__SIZEOF_POS_T__) "\n",
				       self->fn_ino, pos);
				pos += sizeof(struct fat_dirent);
				goto readnext;
			}
			if (usedname[0] == '.') {
				/* The kernel implements these itself, so we don't actually want to emit them! */
				if (usedname_len == 1) {
					ATOMIC_CMPXCH(me->fdn_1dot, (uint32_t)-1, (uint32_t)pos);
					pos += sizeof(struct fat_dirent);
					goto readnext; /* Directory-self-reference. */
				}
				if (usedname[1] == '.') {
					ATOMIC_CMPXCH(me->fdn_2dot, (uint32_t)-1, (uint32_t)pos);
					pos += sizeof(struct fat_dirent);
					goto readnext; /* Directory-parent-reference. */
				}
			}
		}

		/* Create a short-directory entry. */
		result = _fatdirent_alloc(usedname_len);

		/* Fill in remaining. */
		result->fad_ent.fde_ent.fd_ops  = &fatdirent_ops;
		memcpy(result->fad_ent.fde_ent.fd_name, usedname, usedname_len, sizeof(char));
		result->fad_ent.fde_ent.fd_namelen = usedname_len;
		result->fad_ent.fde_pos  = pos;
		result->fad_ent.fde_size = sizeof(struct fat_dirent);
	}

	/* Use the absolute on-disk position of the file's struct fat_dirent as INode number. */
	TRY {
		result->fad_ent.fde_ent.fd_ino = (ino_t)Fat_GetAbsDiskPos(self, pos);
	} EXCEPT {
		_fatdirent_free(result);
		RETHROW();
	}

	/* Fill in generic fields. */
	result->fad_ent.fde_ent.fd_ops = &fatdirent_ops;
	memcpy(&result->fad_dos, &ent, sizeof(struct fat_dirent));
	if (ent.f_attr & FATATTR_DIR) {
		result->fad_ent.fde_ent.fd_type = DT_DIR;
	} else {
		result->fad_ent.fde_ent.fd_type = DT_REG;

#ifdef CONFIG_HAVE_MODFAT_CYGWIN_SYMLINKS
		/* Check if this is actually a symbolic link. */
		if ((ent.f_attr & FATATTR_SYS) &&
		    LETOH32(ent.f_size) >= FAT_SYMLINK_FILE_MINSIZE) {
			FatSuperblock *super = fsuper_asfat(me->fn_super);
			if (!(super->ft_features & FAT_FEATURE_NO_CYGWIN_SYMLINK)) {
				FatClusterIndex cluster = LETOH16(ent.f_clusterlo);
				if (!(super->ft_features & FAT_FEATURE_ARB))
					cluster |= (u32)LETOH16(ent.f_clusterhi) << 16;
				if (cluster < super->ft_cluster_eof) {
					byte_t hdr[sizeof(Fat_CygwinSymlinkMagic)];
					pos_t diskpos = FAT_CLUSTERADDR(super, cluster);
					TRY {
						mfile_readall(super->ft_super.ffs_super.fs_dev, hdr, sizeof(hdr), diskpos);
					} EXCEPT {
						kfree(result);
						RETHROW();
					}
					if (bcmp(hdr, Fat_CygwinSymlinkMagic, sizeof(hdr)) == 0) {
						/* Jup! It sure looks like a symlink to me :) */
						result->fad_ent.fde_ent.fd_type = DT_LNK;
					}
				}
			}
		}
#endif /* CONFIG_HAVE_MODFAT_CYGWIN_SYMLINKS */
	}

	return &result->fad_ent;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif /* __GNUC__ */


PRIVATE struct fat_dirent const new_directory_pattern[3] = {
#ifndef __INTELLISENSE__
	[0] = { /* '.' */
		{{{{{.f_name    = { '.', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }},
			.f_ext     = { ' ', ' ', ' ' }}},
			.f_attr    = FATATTR_DIR,
			.f_ntflags = NTFLAG_NONE }}},
	[1] = { /* '..' */
		{{{{{.f_name    = { '.', '.', ' ', ' ', ' ', ' ', ' ', ' ' }},
			.f_ext      = { ' ', ' ', ' ' }}},
			.f_attr     = FATATTR_DIR,
			.f_ntflags  = NTFLAG_NONE }}},
	[2] = {{{{{{ .f_marker  = MARKER_DIREND }}}}}}
#endif /* !__INTELLISENSE__ */
};


PRIVATE u8 const Fat_AcceptedCharacters[128 / 4] = {
/*[[[deemon
import * from deemon;
function isValid83(ord) {
	if (ord >= "A".ord() && ord <= "Z".ord())
		return true;
	if (ord >= "0".ord() && ord <= "9".ord())
		return true;
	return ord in " !#$%&'()-@^_`{}~".ordinals;
}
function isValidLFN(ord) {
	if (isValid83(ord))
		return true;
	if (ord >= "a".ord() && ord <= "z".ord())
		return true;
	if (ord in "+,.;=[]".ordinals)
		return true;
	return false;
}

local BITS_PER_CHAR = 2;

function makeByte(i) {
	local result = 0;
	for (local x: [:(8 / BITS_PER_CHAR)]) {
		local ord = (i * (8 / BITS_PER_CHAR) + x);
		local mask = 0;
		if (isValid83(ord))
			mask |= 1;
		if (isValidLFN(ord))
			mask |= 2;
		mask <<= x * BITS_PER_CHAR;
		result |= mask;
	}
	return result;
}

for (local x: [:128/(8 / BITS_PER_CHAR)]) {
	if ((x % 8) == 0)
		print("\t"),;
	print("0x%.2I8x," % makeByte(x)),;
	if ((x % 8) == 7) {
		print;
	} else {
		print(" "),;
	}
}
]]]*/
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xcf, 0xff, 0x8f, 0x2e, 0xff, 0xff, 0x8f, 0x08,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xf8,
	0xab, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xea, 0x3c,
/*[[[end]]]*/
};
#define Fat_IsAccepted83(ord) \
	((char32_t)(ord) <= 127 && ((Fat_AcceptedCharacters[(ord) / 4] >> (((ord) % 4) * 2)) & 1))
#define Fat_IsAcceptedLFN(ord) \
	((char32_t)(ord) > 127 || ((Fat_AcceptedCharacters[(ord) / 4] >> (((ord) % 4) * 2)) & 2))


PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL FatDir_Contains83Filename)(FatDirNode const *__restrict self,
                                         struct fatdirent *__restrict newent) {
	size_t i;
	for (i = 0; i <= self->fdn_data.fdd_filesmask; ++i) {
		struct flatdirent *ent;
		struct fatdirent *fatent;
		ent = self->fdn_data.fdd_fileslist[i].ffdb_ent;
		if (ent == NULL || ent == &flatdirnode_deleted_dirent)
			continue; /* Unused slot */
		assert(!flatdirent_wasdeleted(ent));
		fatent = flatdirent_asfat(ent);
		if (fatent == newent)
			continue; /* Don't collide with our own entry! */
		if (bcmp(fatent->fad_dos.f_nameext,
		         newent->fad_dos.f_nameext,
		         8 + 3, sizeof(char)) == 0)
			return true;
	}
	return false;
}

LOCAL ATTR_PURE WUNUSED NONNULL((1)) u8
NOTHROW(FCALL lfn_checksum)(char const dos83_name[8 + 3]) {
	u8 result = 0;
	unsigned int i;
	for (i = 0; i < 8 + 3; ++i)
		result = ((result & 1) << 7) + (result >> 1) + dos83_name[i];
	return result;
}

/* The max # of `struct fat_dirent' possibly used for a single file entry. */
#define FAT_DIRENT_PER_FILE_MAXCOUNT (LFN_SEQNUM_MAXCOUNT + 1)

/* Generate FAT file entries and return the # generated. */
PRIVATE NOBLOCK WUNUSED NONNULL((1, 2, 3, 4)) size_t KCALL
Fat_GenerateFileEntries(struct fat_dirent files[FAT_DIRENT_PER_FILE_MAXCOUNT],
                        FatDirNode const *__restrict dir,
                        struct fatdirent *__restrict ent,
                        struct fnode *__restrict file)
		THROWS(E_FSERROR_ILLEGAL_PATH, E_FSERROR_FILE_ALREADY_EXISTS) {
	FatSuperblock const *super = fsuper_asfat(file->fn_super);
	FatClusterIndex first_cluster;
	mode_t fmode;

	/* Construct the DOS 8.3 directory entry. */
	memset(ent->fad_dos.f_nameext, ' ', sizeof(ent->fad_dos.f_nameext));
	ent->fad_dos.f_ntflags = NTFLAG_NONE;
	ent->fad_dos.f_attr    = FATATTR_ARCH;
	if (fnode_isdir(file))
		ent->fad_dos.f_attr |= FATATTR_DIR;
#ifdef CONFIG_HAVE_MODFAT_CYGWIN_SYMLINKS
	if (fnode_islnk(file))
		ent->fad_dos.f_attr |= FATATTR_SYS;
#endif /* CONFIG_HAVE_MODFAT_CYGWIN_SYMLINKS */
	if (ent->fad_ent.fde_ent.fd_name[0] == '.')
		ent->fad_dos.f_attr |= FATATTR_HIDDEN;
	mfile_tslock_acquire(file);
	if (super->ft_features & FAT_FEATURE_UGID) {
		ent->fad_dos.f_uid = (u8)file->fn_uid;
		ent->fad_dos.f_gid = (u8)file->fn_gid;
	} else {
		FatFileATime_Encode(&ent->fad_dos.f_atime, &file->mf_atime);
	}
	FatFileMTime_Encode(&ent->fad_dos.f_mtime, &file->mf_mtime);
	FatFileBTime_Encode(&ent->fad_dos.f_btime, &file->mf_btime);
	fmode = file->fn_mode;
	mfile_tslock_release(file);

	if (!(fmode & 0222))
		ent->fad_dos.f_attr |= FATATTR_RO;
	first_cluster = file->fn_fsdata->fn_clusterv[0];
	ent->fad_dos.f_clusterlo = HTOLE16(first_cluster & 0xffff);
	if (super->ft_features & FAT_FEATURE_ARB) {
		u16 arb = 0;
		/* Use the ARB to implement unix file permissions. */
		if (!(fmode & S_IXUSR))
			arb |= FAT_ARB_NO_OX; /* Disable: Execute by owner */
		if (!(fmode & S_IWUSR))
			arb |= FAT_ARB_NO_OW; /* Disable: Write by owner */
		if (!(fmode & S_IRUSR))
			arb |= FAT_ARB_NO_OR; /* Disable: Read by owner */
		if (!(fmode & S_IXGRP))
			arb |= FAT_ARB_NO_GX; /* Disable: Execute by group */
		if (!(fmode & S_IWGRP))
			arb |= FAT_ARB_NO_GW; /* Disable: Write by group */
		if (!(fmode & S_IRGRP))
			arb |= FAT_ARB_NO_GR; /* Disable: Read by group */
		if (!(fmode & S_IXOTH))
			arb |= FAT_ARB_NO_WX; /* Disable: Execute by world */
		if (!(fmode & S_IWOTH))
			arb |= FAT_ARB_NO_WW; /* Disable: Write by world */
		if (!(fmode & S_IROTH))
			arb |= FAT_ARB_NO_WR; /* Disable: Read by world */
		if (!(fmode & 0222))
			arb &= ~(FAT_ARB_NO_OW | FAT_ARB_NO_GW | FAT_ARB_NO_WW);
		ent->fad_dos.f_arb = HTOLE16(arb);
	} else {
		/* 32-bit clusters */
		ent->fad_dos.f_clusterhi = HTOLE16((u16)(first_cluster >> 16));
	}

	/* Fill in the file size attribute of the entry. */
	ent->fad_dos.f_size = HTOLE32((u32)atomic64_read(&file->mf_filesize));
	if (fnode_isdir(file)) /* Directories should have size=0 */
		ent->fad_dos.f_size = HTOLE32(0);

	/* Figure out if `ent' can be encoded as a DOS 8.3 filename. */
	if unlikely(ent->fad_ent.fde_ent.fd_namelen == 0)
		THROW(E_FSERROR_ILLEGAL_PATH);
	{
		char const *reader, *rdend;
		char *writer;
		unsigned int flags = 0;
#define HAVE_LOWER_BASE 0x01
#define HAVE_UPPER_BASE 0x02
#define HAVE_LOWER_EXT  0x04
#define HAVE_UPPER_EXT  0x08
		reader = ent->fad_ent.fde_ent.fd_name;
		rdend  = reader + ent->fad_ent.fde_ent.fd_namelen;
		writer = ent->fad_dos.f_nameext;
		for (;;) {
			char32_t ch;
			ch = unicode_readutf8_n(&reader, rdend);
			if (!ch) {
				if (reader >= rdend)
					break;
				THROW(E_FSERROR_ILLEGAL_PATH);
			}
			if (writer >= COMPILER_ENDOF(ent->fad_dos.f_nameext))
				goto need_lfn; /* Filename is too long */
			if (ch >= 'A' && ch <= 'Z') {
				shift_t shift = 0;
				if (writer >= ent->fad_dos.f_ext)
					shift = 2;
				if (flags & (HAVE_LOWER_BASE << shift))
					goto need_lfn; /* Mixed case */
				flags |= (HAVE_UPPER_BASE << shift);
			} else if (ch >= 'a' && ch <= 'z') {
				shift_t shift = 0;
				if (writer >= ent->fad_dos.f_ext)
					shift = 2;
				if (flags & (HAVE_UPPER_BASE << shift))
					goto need_lfn; /* Mixed case */
				ch += ('A' - 'a'); /* Convert to uppercase */
				flags |= (HAVE_LOWER_BASE << shift);
			} else if (ch == '.') {
				if (writer >= ent->fad_dos.f_ext)
					goto need_lfn; /* Multiple dots */
				/* NOTE: The space-padding was already done. */
				writer = ent->fad_dos.f_ext;
				continue;
			} else {
				if (!Fat_IsAccepted83(ch))
					goto need_lfn; /* Not accepted by 8.3 */
			}
			*writer++ = (char)(unsigned char)ch;
			if (writer == ent->fad_dos.f_ext) {
				/* Next character _must_ be end-of-name or '.' */
				ch = unicode_readutf8_n(&reader, rdend);
				if (!ch) {
					if (reader >= rdend)
						break;
					THROW(E_FSERROR_ILLEGAL_PATH);
				}
				if (ch != '.')
					goto need_lfn; /* Base name is too long. */
			}
		}
		/* Finalize the DOS directory entry. */
		if (flags & HAVE_LOWER_BASE)
			ent->fad_dos.f_ntflags |= NTFLAG_LOWBASE;
		if (flags & HAVE_LOWER_EXT)
			ent->fad_dos.f_ntflags |= NTFLAG_LOWEXT;
		/* Fix 0xe5 --> 0x05 */
		if ((unsigned char)ent->fad_dos.f_nameext[0] == 0xe5)
			ent->fad_dos.f_nameext[0] = (char)MARKER_IS0XE5;
	} /* Scope... */
	memcpy(&files[0], &ent->fad_dos, sizeof(struct fat_dirent));
	return 1;
	{
		uint32_t cookie;
		size_t i, matchsize;
		size_t retry_hex, retry_dig;
		char const *reader, *rdend;
		char *writer;
need_lfn:
		cookie = 0;

		/* Generate the 8.3 filename used for the LFN entry. */
		memset(ent->fad_dos.f_nameext, ' ', sizeof(ent->fad_dos.f_nameext));
		ent->fad_dos.f_ntflags = NTFLAG_NONE;

retry_lfn:
		/* Must generate  a long  filename, also  taking
		 * the  value  of  'retry'  into  consideration.
		 * Now for the hard part: The filename itself... */
		retry_hex = (cookie / 9);
		retry_dig = (cookie % 9);

		/* The first 2 short characters always match the  first
		 * 2 characters of the original base (in uppercase). If
		 * no hex-range retries are needed, the first 6 match. */
		matchsize = retry_hex ? 2 : 6;
		reader = ent->fad_ent.fde_ent.fd_name;
		rdend  = reader + ent->fad_ent.fde_ent.fd_namelen;
		while (reader < rdend && (*reader == '.' || isspace(*reader)))
			++reader; /* Skip leading dots and spaces for conversion */
		writer = ent->fad_dos.f_name;
		for (i = 0; i < matchsize; ++i) {
			char32_t ch;
			ch = unicode_readutf8_n(&reader, rdend);
			if (ch >= 'a' && ch <= 'z')
				ch += ('A' - 'a'); /* Force ASCII lower to uppercase. */
			if (!Fat_IsAccepted83(ch)) {
				if (!ch)
					break; /* Allow 8.3 alternates that are shorter than 8 characters */
				ch = '~'; /* Replace illegals with '~' */
			}
			*writer++ = (char)(unsigned char)ch;
		}
		if (retry_hex) {
			/* Following the matching characters are 4 hex-chars
			 * whenever  more than 9  retry attempts have failed
			 * >> This multiplies the amount of available names by 0xffff */
			*writer++ = _itoa_upper_digits[(retry_hex & 0xf000) >> 12];
			*writer++ = _itoa_upper_digits[(retry_hex & 0x0f00) >> 8];
			*writer++ = _itoa_upper_digits[(retry_hex & 0x00f0) >> 4];
			*writer++ = _itoa_upper_digits[(retry_hex & 0x000f)];
		}
		assert(writer <= ent->fad_dos.f_name + 6);

		/* Following the shared name and the hex part is always a tilde '~' */
		*writer++ = '~';

		/* The last character then, is the non-hex digit (1..9) */
		*writer++ = '1' + retry_dig;

		/* Fill the rest with space characters. */
		while (writer < COMPILER_ENDOF(ent->fad_dos.f_name))
			*writer++ = ' ';

		/* Fix 0xe5 --> 0x05 */
		if (ent->fad_dos.f_marker == 0xe5) /* f_marker <===> f_name[0] */
			ent->fad_dos.f_marker = MARKER_IS0XE5;

		/* If the 8.3 filename already exists, then try to generate another one. */
		if unlikely(FatDir_Contains83Filename(dir, ent)) {
			if unlikely(cookie >= (0xffff * 9))
				THROW(E_FSERROR_FILE_ALREADY_EXISTS);
			++cookie;
			goto retry_lfn;
		}
	} /* Scope... */
	{
		char16_t lfn_name[LFN_SEQNUM_MAXCOUNT * LFN_NAME + UNICODE_UTF16_CURLEN - 1], *writer;
		char const *reader, *rdend;
		size_t i, lfn_length, result;
		uint8_t checksum;

		/* Generate the LFN filename */
		reader = ent->fad_ent.fde_ent.fd_name;
		rdend  = reader + ent->fad_ent.fde_ent.fd_namelen;
		writer = lfn_name;
		for (;;) {
			char32_t ch;
			ch = unicode_readutf8_n(&reader, rdend);
			if (ch == 0) {
				if (reader >= rdend)
					break;
				THROW(E_FSERROR_ILLEGAL_PATH);
			}
			if unlikely(!Fat_IsAcceptedLFN(ch))
				THROW(E_FSERROR_ILLEGAL_PATH); /* Character isn't allowed, even in LFN */
			if unlikely(writer >= (lfn_name + LFN_SEQNUM_MAXCOUNT * LFN_NAME) - 1)
				THROW(E_FSERROR_ILLEGAL_PATH); /* Filename too long */
			writer = unicode_writeutf16_chk(writer, ch);
			if unlikely(!writer)
				THROW(E_FSERROR_ILLEGAL_PATH); /* Character cannot be encoded */
		}
		if unlikely(writer >= (lfn_name + LFN_SEQNUM_MAXCOUNT * LFN_NAME) - 1)
			THROW(E_FSERROR_ILLEGAL_PATH); /* Filename too long */

		/* Append trailing NUL character. */
		*writer++ = 0;

		lfn_length = (size_t)(writer - lfn_name);
		assert(lfn_length <= LFN_SEQNUM_MAXCOUNT * LFN_NAME);
#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
		for (i = 0; i < lfn_length; ++i)
			lfn_name[i] = (char16_t)(u16)HTOLE16((u16)lfn_name[i]);
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
		result = CEILDIV(lfn_length, LFN_NAME);
		assert((result + 1) <= FAT_DIRENT_PER_FILE_MAXCOUNT);

		/* Fill unused characters of the last file with `0xFFFF' */
		memsetw(&lfn_name[lfn_length], 0xffff,
		        (result * LFN_NAME) - lfn_length);

		/* Calculate the checksum for the 8.3 filename. */
		checksum = lfn_checksum(ent->fad_dos.f_nameext);

		/* Fill in the LFN file entries. */
		for (i = 0; i < result; ++i) {
			/* LFN sequence entries are written in reverse order (for whatever reason...) */
			size_t seqnum = (result - 1) - i;
			size_t offset = seqnum * LFN_NAME;
			memcpyw(files[i].lfn_name_1, &lfn_name[offset + 0], LFN_NAME1);
			memcpyw(files[i].lfn_name_2, &lfn_name[offset + LFN_NAME1], LFN_NAME2);
			memcpyw(files[i].lfn_name_3, &lfn_name[offset + LFN_NAME1 + LFN_NAME2], LFN_NAME3);
			files[i].lfn_seqnum = LFN_SEQNUM_MIN + (u8)seqnum;
			files[i].lfn_attr   = FATATTR_LFN;
			files[i].lfn_type   = 0;
			files[i].lfn_clus   = (le16)0;
			files[i].lfn_csum   = checksum;
		}

		/* Set the first-physical-last-logical bit for the first LFN sequence entry. */
		files[0].lfn_seqnum |= 0x40;

		/* Append the trailing "normal" DOS 8.3 file entry. */
		memcpy(&files[result], &ent->fad_dos, sizeof(struct fat_dirent));
		++result;
		return result;
	} /* Scope... */
}


PRIVATE WUNUSED NONNULL((1, 2, 3)) bool KCALL
fatdir_v_writedir(struct flatdirnode *__restrict self,
                  struct flatdirent *__restrict ent_,
                  struct fnode *__restrict file,
                  bool at_end_of_dir)
		THROWS(E_IOERROR, E_FSERROR_DISK_FULL, E_FSERROR_ILLEGAL_PATH) {
	ino_t ino;
	size_t num_files;
	struct fat_dirent files[FAT_DIRENT_PER_FILE_MAXCOUNT + 1];
	REF struct fatdirent *oldent;
	struct fatdirent *ent = flatdirent_asfat(ent_);
	FatDirNode *me        = flatdirnode_asfat(self);
	assert((ent->fad_ent.fde_pos % sizeof(struct fat_dirent)) == 0);
	assert(file->fn_fsdata->fn_dir == me);

	/* Deal with reserved positions (the "." and ".." entries).
	 * NOTE: No need for atomic reads here, or worrying about
	 *       these entries already  having been  encountered:
	 * Assuming  the caller did  everything right, a directory
	 * write should never happen at some random position,  but
	 * only at a known gap  (which are produced as the  result
	 * of address ranges returned by `fatdir_v_readdir()'), or
	 * at  the end of the directory (which can only be reached
	 * once `fatdir_v_readdir()' says it has been been).
	 *
	 * Furthermore, assuming that the directory doesn't contain
	 * more than one "." or ".." entry each, we can pretty much
	 * act as though `fdn_1dot' and `fdn_2dot' were [const]  at
	 * this point! */
	while (ent->fad_ent.fde_pos == me->fdn_1dot || ent->fad_ent.fde_pos == me->fdn_2dot) {
		ent->fad_ent.fde_pos += sizeof(struct fat_dirent);
		if (OVERFLOW_USUB(ent->fad_ent.fde_size, sizeof(struct fat_dirent), &ent->fad_ent.fde_size))
			ent->fad_ent.fde_size = 0;
	}

	/* Build directory entries. */
	num_files = Fat_GenerateFileEntries(files, me, ent, file);

	/* Check available space. */
	{
		bool spaceok;
		size_t reqsize;
		reqsize = num_files * sizeof(struct fat_dirent);
		spaceok = ent->fad_ent.fde_size >= reqsize;
		ent->fad_ent.fde_size = reqsize;
		if (!spaceok)
			return false; /* Insufficient buffer space. */
	}

	if (at_end_of_dir) {
		/* Append another trailing end-of-directory marker file. */
		memcpy(&files[num_files], &new_directory_pattern[2],
		       sizeof(struct fat_dirent));
		++num_files;
	}

	/* Write directory entries. */
	ino = (ino_t)Fat_GetAbsDiskPos(me, ent->fad_ent.fde_pos);
	mfile_writeall(me, files, num_files * sizeof(struct fat_dirent),
	               ent->fad_ent.fde_pos);

	/* Fill in INode numbers */
	incref(ent);                       /* For `file->fn_fsdata->fn_ent' */
	ent->fad_ent.fde_ent.fd_ino = ino; /* Also fill in the directory entry's INode number */
again_check_supent:
	if (ATOMIC_READ(file->fn_supent.rb_rhs) != FSUPER_NODES_DELETED) {
		struct fsuper *super = file->fn_super;
		/* Because  we're changing the Inode, we must re-insert
		 * the file into the superblock's INode tree. Otherwise
		 * stuff will become inconsistent. */
		TRY {
			fsuper_nodes_write(super);
		} EXCEPT {
			{
				NESTED_EXCEPTION;
				/* Delete the stuff that was written above. */
				memset(files, at_end_of_dir ? MARKER_DIREND : MARKER_UNUSED,
				       num_files * sizeof(struct fat_dirent));
				mfile_writeall(me, files, num_files * sizeof(struct fat_dirent),
				               ent->fad_ent.fde_pos);
			}
			RETHROW();
		}

		/* Check that the file is actually properly inserted into the superblock. */
		if unlikely(file->fn_supent.rb_rhs == FSUPER_NODES_DELETED ||
		            me->_fn_suplop.olo_func == &fnode_add2sup_lop) {
			fsuper_nodes_endwrite(super);
			goto again_check_supent;
		}
		fsuper_nodes_removenode(super, file);
		mfile_tslock_acquire(file);
		file->fn_ino = ino;
		oldent = file->fn_fsdata->fn_ent; /* Inherit reference */
		file->fn_fsdata->fn_ent = ent;    /* Inherit reference */
		mfile_tslock_release(file);
		fsuper_nodes_insert(super, file);
		fsuper_nodes_endwrite(super);
	} else {
		mfile_tslock_acquire(file);
		/* Interlock another check for `fn_supent' with the TSLOCK */
		if unlikely(ATOMIC_READ(file->fn_supent.rb_rhs) != FSUPER_NODES_DELETED) {
			mfile_tslock_release_br(file);
			goto again_check_supent;
		}
		file->fn_ino = ino;
		oldent = file->fn_fsdata->fn_ent; /* Inherit reference */
		file->fn_fsdata->fn_ent = ent;    /* Inherit reference */
		mfile_tslock_release(file);
	}
	/* NOTE: If changed, the new directory is saved in  `fn_dir'
	 *       during `fatdir_v_direntchanged()', as only that one
	 *       guaranties being called while holding locks to both
	 *       the old and new directory. */

	/* Drop reference from a possible old entry. */
	xdecref_unlikely(oldent);

	/* Success! */
	return true;
}

PRIVATE NONNULL((1, 2, 3)) void KCALL
fatdir_v_deleteent(struct flatdirnode *__restrict self,
                   struct flatdirent *__restrict ent_,
                   struct fnode *__restrict file,
                   bool at_end_of_dir)
		THROWS(E_IOERROR) {
	uint8_t used_marker;
	pos_t ptr, end;
	FatDirNode *me        = flatdirnode_asfat(self);
	struct fatdirent *ent = flatdirent_asfat(ent_);
	FatNodeData *dat      = file->fn_fsdata;
	assert(ent->fad_ent.fde_size != 0);
	assert((ent->fad_ent.fde_size % sizeof(struct fat_dirent)) == 0);
	ptr = flatdirent_basaddr(&ent->fad_ent);
	end = flatdirent_endaddr(&ent->fad_ent);

	mfile_tslock_acquire(file);
	/* This  may differ  if we got  here after the  file was renamed
	 * and the caller is currently deleting its old directory entry. */
	if (dat->fn_ent == ent) {
		/* Clear the saved dir/dirent from `file' */
		assert(dat->fn_dir == self);
		dat->fn_dir = NULL;
		dat->fn_ent = NULL;
		decref_nokill(self);
		decref_nokill(ent);
	}
	mfile_tslock_release(file);

	/* Mark directory entries as deleted. */
	used_marker = MARKER_UNUSED;
	if (at_end_of_dir)
		used_marker = MARKER_DIREND;
	for (; ptr < end; ptr += sizeof(struct fat_dirent)) {
		struct fat_dirent ent;
		/* Save deleted first byte at offset 0x0d
		 * https://en.wikipedia.org/wiki/Design_of_the_FAT_file_system#Directory_entry */
		mfile_readall(me, &ent, sizeof(ent), ptr);
		ent.f_delchr = ent.f_marker;
		ent.f_marker = used_marker;
		mfile_writeall(me, &ent, sizeof(ent), ptr);
		used_marker = MARKER_UNUSED;
	}

	if (at_end_of_dir) {
		/* TODO: Free unused clusters. */
	}
}

PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct fnode *KCALL
fatdir_v_mkfile(struct flatdirnode *__restrict self,
                struct fmkfile_info const *__restrict info)
		THROWS(E_BADALLOC, E_IOERROR, E_FSERROR_UNSUPPORTED_OPERATION);

PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) struct flatdirent *KCALL
fatdir_v_mkent(struct flatdirnode *__restrict UNUSED(self),
               struct fmkfile_info const *__restrict info,
               struct fnode *__restrict UNUSED(file))
		THROWS(E_BADALLOC, E_IOERROR) {
	/* Allocate the new entry (the dos entry will be initialized by `fatdir_v_writedir') */
	struct fatdirent *result;
	result = _fatdirent_alloc(info->mkf_namelen);
	result->fad_ent.fde_ent.fd_ops = &fatdirent_ops;
	DBG_memset(&result->fad_dos, 0xcc, sizeof(result->fad_dos));
	return &result->fad_ent;
}

PRIVATE NONNULL((1)) FatClusterIndex KCALL
FatNode_GetFirstCluster(struct fnode *__restrict self)
		THROWS(E_BADALLOC, E_IOERROR) {
	FatNodeData *dat = self->fn_fsdata;
	FatClusterIndex result;
	for (;;) {
		FatNodeData_Read(dat);
		{
			RAII_FINALLY { FatNodeData_EndRead(dat); };
			result = Fat_GetFileCluster(self, 0, FAT_GETCLUSTER_MODE_FCREATE);
		}
		if likely(result != FAT_GETFILECLUSTER_NEED_WRLOCK)
			break;
		FatNodeData_WaitWrite(dat);
	}
	return result;
}

PRIVATE NONNULL((1, 2, 3, 4)) void KCALL
fatdir_v_allocfile(struct flatdirnode *__restrict self,
                   struct flatdirent *__restrict ent,
                   struct fnode *__restrict file,
                   struct fmkfile_info const *__restrict info)
		THROWS(E_BADALLOC, E_IOERROR) {
	FatDirNode *me       = flatdirnode_asfat(self);
	FatNodeData *dat     = file->fn_fsdata;
	FatSuperblock *super = fsuper_asfat(file->fn_super);
	assert(dat->fn_dir == self);
	assert(dat->fn_ent == flatdirent_asfat(ent));
	if (fnode_isdir(file)) {
		/* Allocate template for `file'. */
		struct fat_dirent hdr[3];
		FatClusterIndex fil_cluster;
		FatDirNode *fdir = fnode_asfatdir(file);

		/* Determine the initial cluster of `fdir' */
		fil_cluster = FatNode_GetFirstCluster(fdir);

		/* Initialize the header template. */
		memcpy(hdr, new_directory_pattern, sizeof(hdr));
		hdr[0].f_clusterlo = HTOLE16(fil_cluster & 0xffff);
		if (!(super->ft_features & FAT_FEATURE_ARB))
			hdr[0].f_clusterhi = HTOLE16((u16)(fil_cluster >> 16));
		if (fnode_has_fat_clusters(me)) {
			FatClusterIndex par_cluster;
			par_cluster = FatNode_GetFirstCluster(me);
			hdr[1].f_clusterlo = HTOLE16(par_cluster & 0xffff);
			if (!(super->ft_features & FAT_FEATURE_ARB))
				hdr[1].f_clusterhi = HTOLE16((u16)(par_cluster >> 16));
		} else {
			/* 0x0000 -- Free Cluster; also used by DOS to refer to the parent directory starting cluster
			 *           in ".." entries of subdirectories of  the root directory on FAT12/FAT16  volumes
			 *           https://en.wikipedia.org/wiki/Design_of_the_FAT_file_system */
		}

		mfile_tslock_acquire(fdir);
		if (super->ft_features & FAT_FEATURE_UGID) {
			/* UID/GID support */
			hdr[0].f_uid = (u8)fdir->fn_uid;
			hdr[0].f_gid = (u8)fdir->fn_gid;
		} else {
			/* Last-access timestamp support */
			FatFileATime_Encode(&hdr[0].f_atime, &fdir->mf_atime);
		}
		FatFileMTime_Encode(&hdr[0].f_mtime, &fdir->mf_mtime);
		FatFileBTime_Encode(&hdr[0].f_btime, &fdir->mf_btime);
		mfile_tslock_release(fdir);
		hdr[1].f_atime             = hdr[0].f_atime;
		hdr[1].f_mtime.fc_date     = hdr[0].f_mtime.fc_date;
		hdr[1].f_mtime.fc_time     = hdr[0].f_mtime.fc_time;
		hdr[1].f_btime.fb_date     = hdr[0].f_btime.fb_date;
		hdr[1].f_btime.fb_time     = hdr[0].f_btime.fb_time;
		hdr[1].f_btime.fb_sectenth = hdr[0].f_btime.fb_sectenth;

		/* Write the directory header into the directory stream file. */
		mfile_writeall(fdir, hdr, sizeof(hdr), 0);

		/* Remember offsets of "." and ".." */
		ATOMIC_WRITE(fdir->fdn_1dot, 0 * sizeof(struct fat_dirent));
		ATOMIC_WRITE(fdir->fdn_2dot, 1 * sizeof(struct fat_dirent));
	}
#ifdef CONFIG_HAVE_MODFAT_CYGWIN_SYMLINKS
	else if (fnode_islnk(file)) {
		/* Write the link's file contents (the string from `info'). */
		pos_t ptr = 0;
		mfile_writeall(file, Fat_CygwinSymlinkMagic, sizeof(Fat_CygwinSymlinkMagic), ptr);
		ptr += sizeof(Fat_CygwinSymlinkMagic);
		mfile_writeall(file, info->mkf_creat.c_symlink.s_text, info->mkf_creat.c_symlink.s_size, ptr);
		ptr += info->mkf_creat.c_symlink.s_size;
		mfile_writeall(file, "", 1, ptr); /* Trailing NUL */
	}
#endif /* CONFIG_HAVE_MODFAT_CYGWIN_SYMLINKS */
}

PRIVATE NONNULL((1, 2, 3)) void KCALL
fatdir_v_deletefile(struct flatdirnode *__restrict self,
                    struct flatdirent *__restrict UNUSED(last_deleted_ent),
                    struct fnode *__restrict file)
		THROWS(E_IOERROR) {
	FatDirNode *me       = flatdirnode_asfat(self);
	FatNodeData *dat     = file->fn_fsdata;
	FatSuperblock *super = fsuper_asfat(me->fn_super);
	FatClusterIndex *newvec;
	assertf(dat->fn_dir == NULL, "This should have been set by `fatdir_v_deleteent()'");
	assertf(dat->fn_ent == NULL, "This should have been set by `fatdir_v_deleteent()'");
	FatNodeData_Write(dat);
	assert(dat->fn_clusterc >= 1);
	if (dat->fn_clusterv[0] < super->ft_cluster_eof) {
		/* Delete the cluster chain. */
		TRY {
			Fat_DeleteClusterChain(super, dat->fn_clusterv[0]);
		} EXCEPT {
			FatNodeData_EndWrite(dat);
			RETHROW();
		}
	}

	/* Truncate unused vector space. */
	newvec = (FatClusterIndex *)krealloc_nx(dat->fn_clusterv,
	                                        1 * sizeof(FatClusterIndex),
	                                        GFP_NORMAL);
	if likely(newvec != NULL)
		dat->fn_clusterv = newvec;

	/* Modify cluster information of `self' to indicate no allocation */
	dat->fn_clusterv[0] = super->ft_cluster_eof_marker;
	dat->fn_clusterc    = 1;
	FatNodeData_EndWrite(dat);

	/* Technically, we'd have to do `mfile_changed(me, MFILE_F_ATTRCHANGED)'
	 * at this point, but this operator is  only called to deal with a  file
	 * being deleted as result of its NLINK counter hitting 0. iow: once  we
	 * get here, there's nowhere the file could (or should) be synced  _TO_. */
}

PRIVATE NONNULL((1, 2, 3, 4, 5)) void KCALL
fatdir_v_direntchanged(struct fnode *__restrict self,
                       struct flatdirnode *oldparent,
                       struct flatdirnode *newparent,
                       struct flatdirent *__restrict UNUSED(old_ent),
                       struct flatdirent *__restrict new_ent)
		THROWS(E_IOERROR) {
	FatNodeData *dat = self->fn_fsdata;
	assert(dat->fn_ent == flatdirent_asfat(new_ent)); /* New entry was already set by `fatdir_v_writedir()' */
	assert(dat->fn_dir == flatdirnode_asfat(oldparent));

	/* Update saved meta-data values. */
	incref(newparent);
	mfile_tslock_acquire(self);
	dat->fn_dir = flatdirnode_asfat(newparent); /* Inherit reference */
	mfile_tslock_release(self);
	decref_nokill(oldparent); /* Old value of `dat->fn_dir' */

	if (fnode_isdir(self) && oldparent != newparent) {
		/* TODO: Re-write the parent-cluster value within the directory header (the ".." entry) */
	}
}


/************************************************************************/
/* FAT ioctl(2) integration                                             */
/************************************************************************/
PRIVATE BLOCKING NONNULL((1)) syscall_slong_t KCALL
fat_v_ioctl(struct mfile *__restrict self, ioctl_t cmd,
            USER UNCHECKED void *arg, iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, ...) {
	struct fnode *me = mfile_asnode(self);
	switch (cmd) {

	case FAT_IOCTL_GET_ATTRIBUTES: {
		u8 attr;
		struct fatdirent *ent;
		FatNodeData *dat = me->fn_fsdata;
		validate_writable(arg, sizeof(u32));
		mfile_tslock_acquire(me);
		ent = dat->fn_ent;
		if unlikely(!ent) {
			mfile_tslock_release_br(me);
			THROW(E_FSERROR_DELETED, E_FILESYSTEM_DELETED_FILE);
		}
		/* Read attributes. */
		attr = ent->fad_dos.f_attr;
		mfile_tslock_release(me);
		UNALIGNED_SET32((USER CHECKED u32 *)arg, attr);
	}	break;

	case FAT_IOCTL_SET_ATTRIBUTES: {
		struct fatdirent *ent;
		FatNodeData *dat = me->fn_fsdata;
		REF FatDirNode *dir;
		u32 newflags;
		validate_readable(arg, sizeof(u32));
		newflags = UNALIGNED_GET32((u32 const *)arg);
		VALIDATE_FLAGSET(newflags,
		                 FATATTR_RO | FATATTR_HIDDEN | FATATTR_SYS |
		                 FATATTR_VOLUME | FATATTR_DIR | FATATTR_ARCH,
		                 E_INVALID_ARGUMENT_CONTEXT_FAT_IOCTL_SET_ATTRIBUTES_ATTR);
		if unlikely((newflags & FATATTR_LFN) == FATATTR_LFN) {
			THROW(E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION,
			      E_INVALID_ARGUMENT_CONTEXT_FAT_IOCTL_SET_ATTRIBUTES_ATTR,
			      newflags, FATATTR_LFN, FATATTR_LFN);
		}

		/* In order to change attributes, the calling thread
		 * needs write-access to  the containing  directory. */
		mfile_tslock_acquire(me);
		dir = dat->fn_dir;
		xincref(dir);
		mfile_tslock_release(me);
		if unlikely(!dir)
			THROW(E_FSERROR_DELETED, E_FILESYSTEM_DELETED_FILE);
		{
			FINALLY_DECREF_UNLIKELY(dir);
			fnode_access(dir, W_OK);
		}

		mfile_tslock_acquire(me);
		ent = dat->fn_ent;
		if unlikely(!ent) {
			mfile_tslock_release_br(me);
			THROW(E_FSERROR_DELETED, E_FILESYSTEM_DELETED_FILE);
		}

		/* Check if it's even possible to change attributes. */
		if unlikely((me->mf_flags & MFILE_FN_ATTRREADONLY) ||
		            (me->fn_super->fs_root.mf_flags & MFILE_F_READONLY) ||
		            (me->fn_super->fs_dev->mf_flags & MFILE_F_READONLY)) {
			mfile_tslock_release_br(me);
			THROW(E_FSERROR_READONLY);
		}

		/* Check if the caller is trying to change `ATTR_VOLUME' or `ATTR_DIR' */
		if unlikely((newflags & (FATATTR_VOLUME | FATATTR_DIR)) !=
		            (ent->fad_dos.f_attr & (FATATTR_VOLUME | FATATTR_DIR))) {
			u8 oldflags = ent->fad_dos.f_attr;
			mfile_tslock_release_br(me);
			THROW(E_INVALID_ARGUMENT_RESERVED_FLAG,
			      E_INVALID_ARGUMENT_CONTEXT_FAT_IOCTL_SET_ATTRIBUTES_ATTR,
			      newflags, FATATTR_VOLUME | FATATTR_DIR,
			      (oldflags & (FATATTR_VOLUME | FATATTR_DIR)));
		}

		/* Set attributes. */
		ent->fad_dos.f_attr = (u8)newflags;
		mfile_tslock_release(me);

		/* Mark file attributes as having changed. */
		mfile_changed(me, MFILE_F_ATTRCHANGED);
	}	break;

	case FAT_IOCTL_GET_VOLUME_ID: {
		FatSuperblock *super = fsuper_asfat(me->fn_super);
		validate_writable(arg, sizeof(u32));
		UNALIGNED_SET32((USER CHECKED u32 *)arg, super->ft_volid);
	}	break;

	case VFAT_IOCTL_READDIR_BOTH:
	case VFAT_IOCTL_READDIR_SHORT:
		/* As  documented,  these throw  not-a-directory when
		 * attempting to use them without an offset-argument. */
		THROW(E_FSERROR_NOT_A_DIRECTORY,
		      E_FILESYSTEM_NOT_A_DIRECTORY_IOCTL);
		break;

	default: {
		BLOCKING NONNULL_T((1)) syscall_slong_t
		(KCALL *super_ioctl)(struct mfile *__restrict self, ioctl_t cmd,
		                     USER UNCHECKED void *arg, iomode_t mode)
				THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, ...);

		/* Invoke the super-type's ioctl() operator. */
		if (fnode_isdir(me)) {
			super_ioctl = &flatdirnode_v_ioctl;
			if (fnode_issuper(me))
				super_ioctl = &flatsuper_v_ioctl;
		} else if (fnode_isreg(me)) {
			super_ioctl = &fregnode_v_ioctl;
		} else
#ifdef CONFIG_HAVE_MODFAT_CYGWIN_SYMLINKS
		if (fnode_islnk(me)) {
			super_ioctl = &flnknode_v_ioctl;
		} else
#endif /* CONFIG_HAVE_MODFAT_CYGWIN_SYMLINKS */
		{
			super_ioctl = &fnode_v_ioctl;
		}
		return (*super_ioctl)(me, cmd, arg, mode);
	}	break;

	}
	return 0;
}



/************************************************************************/
/* FAT Directory enumeration (same as flatdir, but w/ ioctl)            */
/************************************************************************/
#define FATDIRENUM_IOCTL_READDIR_F_BOTH   0x01
#ifdef NEED_COMPAT_IOCTL_FAT_READDIR
#define FATDIRENUM_IOCTL_READDIR_F_COMPAT 0x02
#endif /* NEED_COMPAT_IOCTL_FAT_READDIR */
PRIVATE NONNULL((1)) void KCALL
fatdirenum_do_ioctl_readdir(struct fatdirent *__restrict ent,
                            USER CHECKED struct __fat_dirent *result,
                            unsigned int flags) {
	uint8_t usedname_len;
	char usedname[11 * 2 + 2], *dstptr;
	char fixedname[11], *srcptr;

	memcpy(fixedname, ent->fad_dos.f_nameext, 11);

	/* Fix lowercase filenames. */
	if (ent->fad_dos.f_ntflags & NTFLAG_LOWBASE)
		strlwrz(fixedname, 8);
	if (ent->fad_dos.f_ntflags & NTFLAG_LOWEXT)
		strlwrz(fixedname + 8, 3);
	/* Deal with this one... */
	if unlikely(ent->fad_dos.f_marker == MARKER_IS0XE5)
		fixedname[0] = 0xe5;

	/* Construct the proper, human-readable filename. */
	dstptr = usedname;
	srcptr = fixedname;
	while (srcptr < fixedname + 8 && isspace(*srcptr))
		++srcptr;
	dstptr = decode_latin1(dstptr, srcptr, (size_t)((fixedname + 8) - srcptr));
	while (dstptr > usedname && isspace(dstptr[-1]))
		--dstptr;
	*dstptr++ = '.';
	srcptr = fixedname + 8;
	while (srcptr < fixedname + 11 && isspace(*srcptr))
		++srcptr;
	dstptr = decode_latin1(dstptr, srcptr, (size_t)((fixedname + 11) - srcptr));
	while (dstptr > usedname && isspace(dstptr[-1]))
		--dstptr;
	if (dstptr > usedname && dstptr[-1] == '.')
		--dstptr;
	*dstptr = 0;
	usedname_len = (uint8_t)(dstptr - usedname);

	/* Fill in info about the DOS filename. */
#ifdef NEED_COMPAT_IOCTL_FAT_READDIR
	if (flags & FATDIRENUM_IOCTL_READDIR_F_COMPAT) {
		USER CHECKED struct __compat_fat_dirent *compat_result;
		compat_result = (USER CHECKED struct __compat_fat_dirent *)result;
		compat_result[0].d_ino    = 0;
		compat_result[0].d_off    = 0;
		compat_result[0].d_reclen = usedname_len;
		memcpy(compat_result[0].d_name, usedname, usedname_len + 1, sizeof(char));
		if (flags & FATDIRENUM_IOCTL_READDIR_F_BOTH) {
			uint16_t longlen = ent->fad_ent.fde_ent.fd_namelen;
			if (longlen > 255)
				longlen = 255;
			compat_result[1].d_ino    = (compat_ulongptr_t)(uint64_t)ent->fad_ent.fde_ent.fd_ino;
			compat_result[1].d_off    = (compat_longptr_t)(compat_ulongptr_t)(uint64_t)ent->fad_ent.fde_pos;
			compat_result[1].d_reclen = longlen;
			*(char *)mempcpy(compat_result[1].d_name, ent->fad_ent.fde_ent.fd_name, longlen, sizeof(char)) = '\0';
		}
	} else
#endif /* NEED_COMPAT_IOCTL_FAT_READDIR */
	{
		result[0].d_ino    = 0;            /* Linux says this doesn't exist for short entries. */
		result[0].d_off    = 0;            /* *ditto* */
		result[0].d_reclen = usedname_len; /* Contrary to the name, this is the length of the filename! */
		memcpy(result[0].d_name, usedname, usedname_len + 1, sizeof(char));

		if (flags & FATDIRENUM_IOCTL_READDIR_F_BOTH) {
			/* Fill in the second entry with the long filename. */
			uint16_t longlen = ent->fad_ent.fde_ent.fd_namelen;
			if (longlen > 255) {
				/* We're dealing with fixed buffers, meaning we're limited to this many characters.
				 * Linux doesn't say what should happen if  the long filename is longer than  this,
				 * and I would like to mention that yes: IT CAN BE LONGER THAN THIS. As a matter of
				 * fact, the longest theoretical name is 780 characters long:
				 * >> 780 == LFN_SEQNUM_MAXCOUNT * UNICODE_16TO8_MAXBUF(LFN_NAME)
				 * >> 780 == 20                  * UNICODE_16TO8_MAXBUF(13)
				 * >> 780 == 20                  * 3 * 13
				 * >> 780 == 20                  * 39
				 * >> 780 == 780
				 *
				 * So lets just make it easy and truncate the name when this happens. */
				longlen = 255;
			}
			result[1].d_ino    = (ulongptr_t)(uint64_t)ent->fad_ent.fde_ent.fd_ino;
			result[1].d_off    = (longptr_t)(ulongptr_t)(uint64_t)ent->fad_ent.fde_pos;
			result[1].d_reclen = longlen; /* Contrary to the name, this is the length of the filename! */
			*(char *)mempcpy(result[1].d_name, ent->fad_ent.fde_ent.fd_name, longlen, sizeof(char)) = '\0';
		}
	}
}

PRIVATE NONNULL((1)) syscall_slong_t KCALL
fatdirenum_ioctl_readdir(struct flatdirenum *__restrict self,
                         USER CHECKED struct __fat_dirent *result,
                         unsigned int flags) {
	pos_t oldpos, real_oldpos;
	FatDirNode *dir;
	REF struct flatdirent *ent, *oldent;
	dir = fdirnode_asfat(self->de_dir);
again:
	flatdirenum_lock_acquire(self);
	ent    = self->ffde_next;
	oldpos = self->ffde_pos;
	if (ent) {
		incref(ent);
		oldpos = flatdirent_basaddr(ent);
	}
	flatdirenum_lock_release(self);
	if (!ent) {
		/* load directory entries, or find the one most suitable for `oldpos' */
next_next_ent:
		ent = flatdirnode_entafter(dir, oldpos);
		/* Check for end-of-directory */
		if (!ent) {
			/* This is another indicator that the end of the directory has been reached! */
#ifdef NEED_COMPAT_IOCTL_FAT_READDIR
			if (flags & FATDIRENUM_IOCTL_READDIR_F_COMPAT) {
				bzero(result, 2 * sizeof(struct __compat_fat_dirent));
			} else
#endif /* NEED_COMPAT_IOCTL_FAT_READDIR */
			{
				bzero(result, 2 * sizeof(struct __fat_dirent));
			}
			return 0;
		}
	} else if (flatdirent_wasdeleted_atomic(ent)) {
		decref_unlikely(ent);
		goto next_next_ent;
	}

	/* Yield `ent' to user-space. */
	FINALLY_DECREF_UNLIKELY(ent);
	fatdirenum_do_ioctl_readdir(flatdirent_asfat(ent), result, flags);

	/* Yield to the next entry. */
	flatdirnode_read(dir);
	flatdirenum_lock_acquire(self);
	real_oldpos = self->ffde_pos;
	oldent      = self->ffde_next; /* Inherit reference (on success) */
	if (oldent)
		real_oldpos = flatdirent_basaddr(oldent);

	/* Check if the enumerator position changed during the read. */
	if unlikely(oldpos != real_oldpos) {
		flatdirenum_lock_release_br(self);
		flatdirnode_endread(dir);
		goto again;
	}

	/* Update the enumerator position. */
	self->ffde_pos = flatdirent_endaddr(ent);
	if unlikely(flatdirent_wasdeleted(ent)) {
		self->ffde_next = NULL;
	} else {
		self->ffde_next = TAILQ_NEXT(ent, fde_bypos);
		if (self->ffde_next) {
			incref(self->ffde_next);
			DBG_memset(&self->ffde_pos, 0xcc, sizeof(self->ffde_pos));
		}
	}
	flatdirenum_lock_release(self);
	flatdirnode_endread(dir);
	xdecref_unlikely(oldent);
	return 1;
}

PRIVATE BLOCKING NONNULL((1)) syscall_slong_t KCALL
fatdirenum_v_ioctl(struct fdirenum *__restrict self, ioctl_t cmd,
                   USER UNCHECKED void *arg, iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, ...) {
	struct flatdirenum *me = fdirenum_asflat(self);

	/* Custom override so we can implement `deo_ioctl' for `VFAT_IOCTL_READDIR_(BOTH|SHORT)' */
	switch (cmd) {

	case VFAT_IOCTL_READDIR_BOTH:
	case VFAT_IOCTL_READDIR_SHORT: {
		unsigned int flags;
		USER CHECKED struct __fat_dirent *data;
		validate_writable(arg, 2 * sizeof(struct __fat_dirent));
		data = (USER CHECKED struct __fat_dirent *)arg;
		if unlikely(!IO_CANREAD(mode))
			THROW(E_INVALID_HANDLE_OPERATION, 0, E_INVALID_HANDLE_OPERATION_READ, mode);
		flags = 0;
		if (cmd == VFAT_IOCTL_READDIR_BOTH)
			flags = FATDIRENUM_IOCTL_READDIR_F_BOTH;
		return fatdirenum_ioctl_readdir(me, data, flags);
	}	break;

#ifdef NEED_COMPAT_IOCTL_FAT_READDIR
	case _IO_WITHTYPE(VFAT_IOCTL_READDIR_BOTH, struct __compat_fat_dirent[2]):
	case _IO_WITHTYPE(VFAT_IOCTL_READDIR_SHORT, struct __compat_fat_dirent[2]): {
		unsigned int flags;
		USER CHECKED struct __compat_fat_dirent *data;
		validate_writable(arg, 2 * sizeof(struct __compat_fat_dirent));
		data = (USER CHECKED struct __compat_fat_dirent *)arg;
		if unlikely(!IO_CANREAD(mode))
			THROW(E_INVALID_HANDLE_OPERATION, 0, E_INVALID_HANDLE_OPERATION_READ, mode);
		flags = FATDIRENUM_IOCTL_READDIR_F_COMPAT;
		if (cmd == _IO_WITHTYPE(VFAT_IOCTL_READDIR_BOTH, struct __compat_fat_dirent[2]))
			flags = FATDIRENUM_IOCTL_READDIR_F_BOTH | FATDIRENUM_IOCTL_READDIR_F_COMPAT;
		return fatdirenum_ioctl_readdir(me, (USER CHECKED struct __fat_dirent *)data, flags);
	}	break;
#endif /* NEED_COMPAT_IOCTL_FAT_READDIR */

	default:
		break;
	}

	/* Fallback: service a normal FAT ioctl */
	return fat_v_ioctl(me->de_dir, cmd, arg, mode);
}


PRIVATE struct fdirenum_ops const fatdirenum_ops = {
	.deo_fini    = &flatdirenum_v_fini,
	.deo_readdir = &flatdirenum_v_readdir,
	.deo_seekdir = &flatdirenum_v_seekdir,
	.deo_ioctl   = &fatdirenum_v_ioctl,
};

#define fatdir_v_enumsz flatdirnode_v_enumsz
PRIVATE BLOCKING NONNULL((1)) void KCALL
fatdir_v_enum(struct fdirenum *__restrict result)
		THROWS(E_IOERROR, ...) {
	struct flatdirenum *rt = (struct flatdirenum *)result;
	struct flatdirnode *me = fdirnode_asflat(rt->de_dir);

	/* Fill in the enumerator. (copy+pasted from `flatdirnode_v_enum') */
#ifndef CONFIG_NO_SMP
	atomic_lock_init(&rt->ffde_lock);
#endif /* !CONFIG_NO_SMP */
	rt->ffde_pos = 0;
	flatdirnode_read(me);
	rt->ffde_next = xincref(TAILQ_FIRST(&me->fdn_data.fdd_bypos));
	flatdirnode_endread(me);
	rt->de_ops = &fatdirenum_ops;
}

PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) ssize_t KCALL
fat_v_printlink_begin(struct mfile *__restrict self, __pformatprinter printer, void *arg)
		THROWS(E_WOULDBLOCK, ...) {
	ssize_t result, temp;
	FatNodeData *dat = mfile_asnode(self)->fn_fsdata;
	FatSuperblock *super;
	REF struct fatdirent *file_ent;
	REF FatDirNode *file_dir;
	FatNodeData_Read(dat);
	file_ent = dat->fn_ent;
	file_dir = dat->fn_dir;
	xincref(file_ent);
	xincref(file_dir);
	FatNodeData_EndRead(dat);
	if (file_dir) {
		FINALLY_DECREF_UNLIKELY(file_dir);
		FINALLY_XDECREF_UNLIKELY(file_ent);
		result = fat_v_printlink_begin(file_dir, printer, arg);
		if unlikely(result < 0)
			return result;
		temp = (*printer)(arg, "/", 1);
		if unlikely(temp < 0)
			goto err;
		result += temp;
		if likely(file_ent) {
			temp = (*printer)(arg,
			                  file_ent->fad_ent.fde_ent.fd_name,
			                  file_ent->fad_ent.fde_ent.fd_namelen);
		} else {
			temp = (*printer)(arg, "?", 1);
		}
		if unlikely(temp < 0)
			goto err;
		result += temp;
		return result;
	}
	xdecref_unlikely(file_ent);
	super  = fsuper_asfat(mfile_asnode(self)->fn_super);
	result = (*printer)(arg, "inode:[fatfs:", 13);
	if unlikely(result < 0)
		return result;
	temp = mfile_uprintlink(super->ft_super.ffs_super.fs_dev, printer, arg);
	if unlikely(temp < 0)
		goto err;
	result += temp;
	temp = (*printer)(arg, ":", 1);
	if unlikely(temp < 0)
		goto err;
	result += temp;
	return result;
err:
	return temp;
}

PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) ssize_t KCALL
fat_v_printlink(struct mfile *__restrict self, __pformatprinter printer, void *arg)
		THROWS(E_WOULDBLOCK, ...) {
	ssize_t result;
	result = fat_v_printlink_begin(self, printer, arg);
	if likely(result >= 0) {
		ssize_t temp;
		if (mfile_issuper(self)) {
			temp = (*printer)(arg, "/", 1);
			if unlikely(temp < 0)
				return temp;
			result += temp;
		}
		temp = (*printer)(arg, "]", 1);
		if unlikely(temp < 0)
			return temp;
		result += temp;
	}
	return result;
}




/************************************************************************/
/* FAT operator tables.                                                 */
/************************************************************************/
PRIVATE struct mfile_stream_ops const fatreg_v_stream_ops = {
	/* TODO: Truncate operator (call the underlying truncate before freeing out-of-bounds clusters) */
	.mso_ioctl     = &fat_v_ioctl,
	.mso_printlink = &fat_v_printlink,
	.mso_cc        = &fat_v_cc,
};

PRIVATE struct fregnode_ops const Fat_RegOps = {
	.rno_node = {
		.no_file = {
			.mo_destroy    = &fatreg_v_destroy,
			.mo_loadblocks = &fat_v_loadblocks,
			.mo_saveblocks = &fat_v_saveblocks,
			.mo_changed    = &fregnode_v_changed,
			.mo_stream     = &fatreg_v_stream_ops,
		},
		.no_wrattr = &fat_v_wrattr,
	},
};

PRIVATE struct mfile_stream_ops const fatdir_v_stream_ops = {
	.mso_open      = &flatdirnode_v_open,
	.mso_stat      = &flatdirnode_v_stat,
	.mso_ioctl     = &fat_v_ioctl,
	.mso_printlink = &fat_v_printlink,
	.mso_cc        = &fat_v_cc,
};
PRIVATE struct flatdirnode_ops const Fat_DirOps = {
	.fdno_dir = {
		.dno_node = {
			.no_file = {
				.mo_destroy    = &fatdir_v_destroy,
				.mo_loadblocks = &fat_v_loadblocks,
				.mo_saveblocks = &fat_v_saveblocks,
				.mo_changed    = &flatdirnode_v_changed,
				.mo_stream     = &fatdir_v_stream_ops,
			},
			.no_wrattr = &fat_v_wrattr,
		},
		.dno_lookup = &flatdirnode_v_lookup,
		.dno_enumsz = fatdir_v_enumsz,
		.dno_enum   = &fatdir_v_enum,
		.dno_mkfile = &flatdirnode_v_mkfile,
		.dno_unlink = &flatdirnode_v_unlink,
		.dno_rename = &flatdirnode_v_rename,
#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
		.dno_attach_notify = &flatdirnode_v_attach_notify,
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
	},
	.fdno_flat = {
		.fdnx_readdir       = &fatdir_v_readdir,
		.fdnx_writedir      = &fatdir_v_writedir,
		.fdnx_deleteent     = &fatdir_v_deleteent,
		.fdnx_mkfile        = &fatdir_v_mkfile,
		.fdnx_mkent         = &fatdir_v_mkent,
		.fdnx_allocfile     = &fatdir_v_allocfile,
		.fdnx_deletefile    = &fatdir_v_deletefile,
		.fdnx_direntchanged = &fatdir_v_direntchanged,
	},
};
#ifdef CONFIG_HAVE_MODFAT_CYGWIN_SYMLINKS
PRIVATE struct mfile_stream_ops const fatlnk_v_stream_ops = {
	.mso_stat      = &fatlnk_v_stat,
	.mso_ioctl     = &fat_v_ioctl,
	.mso_printlink = &fat_v_printlink,
	.mso_cc        = &fat_v_cc,
};
PRIVATE struct flnknode_ops const Fat_LnkOps = {
	.lno_node = {
		.no_file = {
			.mo_destroy    = &fatlnk_v_destroy,
			.mo_loadblocks = &fat_v_loadblocks,
			.mo_saveblocks = &fat_v_saveblocks,
			.mo_changed    = &flnknode_v_changed,
			.mo_stream     = &fatlnk_v_stream_ops,
		},
		.no_wrattr = &fat_v_wrattr,
	},
	.lno_readlink = &fatlnk_v_readlink,
};
#endif /* CONFIG_HAVE_MODFAT_CYGWIN_SYMLINKS */


/************************************************************************/
/* FAT Superblock operators.                                            */
/************************************************************************/
struct multifat_sync_file: mfile {
	REF struct mfile *mfsf_dev;              /* Underlying device. */
	uint64_t          mfsf_fat_delta;        /* [const] Relative on-disk delta between different FAT copies. */
	u8                mfsf_fat_count;        /* [const] Total # of FAT copies. */
	bool              mfsf_delta_is_aligned; /* [const] `true' if `mfsf_fat_delta' is aligned according to `mfsf_dev' */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL multifat_sync_file_v_destroy)(struct mfile *__restrict self) {
	struct multifat_sync_file *me = (struct multifat_sync_file *)self;
	decref_unlikely(me->mfsf_dev);
	kfree(me);
}

PRIVATE NONNULL((1, 5)) void KCALL
multifat_sync_file_v_loadblocks(struct mfile *__restrict self, pos_t addr,
                                physaddr_t buf, size_t num_bytes,
                                struct aio_multihandle *__restrict aio) {
	struct multifat_sync_file *me = (struct multifat_sync_file *)self;
	/* The initial FAT is always properly aligned. */
	mfile_rdblocks_async(me->mfsf_dev, addr, buf, num_bytes, aio);
}

PRIVATE NONNULL((1, 5)) void KCALL
multifat_sync_file_v_saveblocks(struct mfile *__restrict self, pos_t addr,
                                physaddr_t buf, size_t num_bytes,
                                struct aio_multihandle *__restrict aio) {
	u8 i;
	struct multifat_sync_file *me = (struct multifat_sync_file *)self;
	if ((me->mfsf_dev->mf_flags & MFILE_F_READONLY) ||
	    (me->mfsf_dev->mf_ops->mo_saveblocks == NULL))
		THROW(E_FSERROR_READONLY);

	/* The initial FAT is always properly aligned. */
	mfile_wrblocks_async(me->mfsf_dev, addr, buf, num_bytes, aio);
	for (i = 1; i < me->mfsf_fat_count; ++i) {
		addr += me->mfsf_fat_delta;
		if likely(me->mfsf_delta_is_aligned) {
			mfile_wrblocks_async(me->mfsf_dev, addr, buf, num_bytes, aio);
		} else {
			/* oof... Have to use buffered I/O... */
			mfile_write_p(me->mfsf_dev, buf, num_bytes, addr);
		}
	}
}

PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) ssize_t KCALL
multifat_sync_file_v_printlink(struct mfile *__restrict self, __pformatprinter printer, void *arg)
		THROWS(E_WOULDBLOCK, ...) {
	ssize_t result, temp;
	static char const prefix[]    = "anon_inode:[fatfs:multifat_sync:";
	struct multifat_sync_file *me = (struct multifat_sync_file *)self;
	result = (*printer)(arg, prefix, COMPILER_STRLEN(prefix));
	if unlikely(result < 0)
		goto done;
	temp = mfile_uprintlink(me->mfsf_dev, printer, arg);
	if unlikely(temp < 0)
		goto err;
	result += temp;
	temp = (*printer)(arg, "]", 1);
	if unlikely(temp < 0)
		goto err;
	result += temp;
done:
	return result;
err:
	return temp;
}

PRIVATE struct mfile_stream_ops const multifat_sync_file_v_stream_ops = {
	.mso_printlink = &multifat_sync_file_v_printlink,
};

PRIVATE struct mfile_ops const multifat_sync_file_ops = {
	.mo_destroy    = &multifat_sync_file_v_destroy,
	.mo_loadblocks = &multifat_sync_file_v_loadblocks,
	.mo_saveblocks = &multifat_sync_file_v_saveblocks,
	.mo_stream     = &multifat_sync_file_v_stream_ops,
};

PRIVATE NONNULL((1, 5)) void KCALL
fat16root_loadblocks(struct mfile *__restrict self, pos_t addr,
                     physaddr_t buf, size_t num_bytes,
                     struct aio_multihandle *__restrict aio) {
	size_t maxio;
	FatSuperblock *me = mfile_asfatsup(self);
	/* Adjust for absolute on-disk addresses. */
	if (OVERFLOW_USUB(me->ft_fdat.fn16_root.r16_rootsiz, addr, &maxio))
		maxio = 0;
	if unlikely(num_bytes > maxio) {
		/* Some part of the tail cannot be read. Instead, initialize to 0 */
		bzerophyscc(buf + maxio, num_bytes - maxio);
		num_bytes = maxio;
	}
	addr += me->ft_fdat.fn16_root.r16_rootpos;

	/* Do disk I/O */
	fsuper_dev_rdsectors_async_chk(&me->ft_super.ffs_super,
	                               addr, buf, num_bytes, aio);
}

PRIVATE NONNULL((1, 5)) void KCALL
fat16root_v_saveblocks(struct mfile *__restrict self, pos_t addr,
                       physaddr_t buf, size_t num_bytes,
                       struct aio_multihandle *__restrict aio) {
	size_t maxio;
	FatSuperblock *me = mfile_asfatsup(self);
	/* Adjust for absolute on-disk addresses. */
	if (OVERFLOW_USUB(me->ft_fdat.fn16_root.r16_rootsiz, addr, &maxio))
		maxio = 0;
	if unlikely(num_bytes > maxio)
		num_bytes = maxio; /* Some part of the tail cannot be written. */
	addr += me->ft_fdat.fn16_root.r16_rootpos;

	/* Do disk I/O */
	if unlikely(me->ft_super.ffs_super.fs_dev->mf_flags & MFILE_F_READONLY)
		THROW(E_FSERROR_READONLY);
	fsuper_dev_wrsectors_async_chk(&me->ft_super.ffs_super,
	                               addr, buf, num_bytes, aio);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fatsuper_v_destroy)(struct mfile *__restrict self) {
	FatSuperblock *me = mfile_asfatsup(self);
	if (me->ft_type == FAT32)
		kfree(me->ft_fdat.fn_clusterv);
	mman_unmap_kram_and_kfree(me->ft_fat_table,
	                          me->ft_fat_size,
	                          me->ft_freefat);
	/* If the fat file is an instance of the special multifat  wrapper,
	 * then we must delete it when the superblock is closed. Otherwise,
	 * its mem-parts will continue to  remain dangling within the  list
	 * of all mem-parts!
	 *
	 * Only do this for the multifat case. - The other case where the
	 * fat file is a proper device must not result in the file  being
	 * deleted (anonymized). */
	if (me->ft_fat_file->mf_ops == &multifat_sync_file_ops)
		mfile_delete(me->ft_fat_file);
	decref(me->ft_fat_file);
	flatsuper_v_destroy(self);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fatsuper_v_free)(struct fnode *__restrict self) {
	kfree(fnode_asfatsup(self));
}

PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct fnode *KCALL
fatdir_v_mkfile(struct flatdirnode *__restrict self,
                struct fmkfile_info const *__restrict info)
		THROWS(E_BADALLOC, E_IOERROR, E_FSERROR_UNSUPPORTED_OPERATION) {
	struct fnode *result;
	FatSuperblock *super = fsuper_asfat(self->fn_super);
	FatDirNode *me       = flatdirnode_asfat(self);
	FatNodeData *dat;

	/* Allocate a new file-node with FAT operators */
	switch (info->mkf_fmode & S_IFMT) {

	case S_IFREG: {
		FatRegNode *node;
		node = (FatRegNode *)kmalloc(sizeof(FatRegNode), GFP_NORMAL);
		node->mf_ops   = &Fat_RegOps.rno_node.no_file;
		node->mf_flags = MFILE_F_NORMAL;
		atomic64_init(&node->mf_filesize, 0);
		node->fn_fsdata = &node->frn_fdat;
		result = node;
	}	break;

	case S_IFDIR: {
		FatDirNode *node;
		node = (FatDirNode *)kmalloc(sizeof(FatDirNode), GFP_NORMAL);
		node->mf_ops   = &Fat_DirOps.fdno_dir.dno_node.no_file;
		node->mf_flags = MFILE_F_NOUSRIO | MFILE_F_NOUSRMMAP;
		atomic64_init(&node->mf_filesize, (uint64_t)-1);
		node->fn_fsdata = &node->fdn_fdat;
		flatdirdata_init(&node->fdn_data);
		node->fdn_1dot = (uint32_t)-1;
		node->fdn_2dot = (uint32_t)-1;
		result = node;
	}	break;

#ifdef CONFIG_HAVE_MODFAT_CYGWIN_SYMLINKS
	case S_IFLNK: {
		FatLnkNode *node;
		node = (FatLnkNode *)kmalloc(sizeof(FatLnkNode), GFP_NORMAL);
		node->mf_ops   = &Fat_LnkOps.lno_node.no_file;
		node->mf_flags = MFILE_F_NOUSRIO | MFILE_F_NOUSRMMAP;
		atomic64_init(&node->mf_filesize, 0);
		node->fn_fsdata = &node->fln_fdat;
		result = node;
	}	break;
#endif /* CONFIG_HAVE_MODFAT_CYGWIN_SYMLINKS */

	default:
		THROW(E_FSERROR_UNSUPPORTED_OPERATION);
		break;
	}
	dat = result->fn_fsdata;
	TRY {
		dat->fn_clusterv = (FatClusterIndex *)kmalloc(sizeof(FatClusterIndex), GFP_NORMAL);
	} EXCEPT {
		kfree(result);
		RETHROW();
	}
	dat->fn_clusterc    = 1;
	dat->fn_clusterv[0] = super->ft_cluster_eof_marker;
	dat->fn_ent = NULL; /* Initialized by `fatdir_v_writedir()' */
	dat->fn_dir = mfile_asfatdir(incref(me));
	shared_rwlock_init(&dat->fn_lock);

	result->mf_parts = NULL;
	SLIST_INIT(&result->mf_changed);
	result->fn_ino = 0; /* Allocated later. */
	return result;
}

PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) struct fnode *KCALL
fatsuper_v_makenode(struct flatsuper *__restrict self,
                    struct flatdirent *__restrict ent_,
                    struct flatdirnode *__restrict dir_)
		THROWS(E_BADALLOC, E_IOERROR) {
	struct fnode *result;
	struct fatdirent *ent = flatdirent_asfat(ent_);
	FatDirNode *dir       = flatdirnode_asfat(dir_);
	FatSuperblock *super  = flatsuper_asfat(self);
	FatNodeData *dat;

	/* Allocate a new file-node with FAT operators */
	switch (ent->fad_ent.fde_ent.fd_type) {

	case DT_REG: {
		FatRegNode *node;
		node = (FatRegNode *)kmalloc(sizeof(FatRegNode), GFP_NORMAL);
		node->mf_ops    = &Fat_RegOps.rno_node.no_file;
		node->mf_flags  = MFILE_F_NORMAL;
		node->fn_fsdata = &node->frn_fdat;
		result = node;
	}	break;

	case DT_DIR: {
		FatDirNode *node;
		node = (FatDirNode *)kmalloc(sizeof(FatDirNode), GFP_NORMAL);
		node->mf_ops    = &Fat_DirOps.fdno_dir.dno_node.no_file;
		node->mf_flags  = MFILE_F_NOUSRIO | MFILE_F_NOUSRMMAP;
		node->fn_fsdata = &node->fdn_fdat;
		flatdirdata_init(&node->fdn_data);
		node->fdn_1dot = (uint32_t)-1;
		node->fdn_2dot = (uint32_t)-1;
		result = node;
	}	break;

#ifdef CONFIG_HAVE_MODFAT_CYGWIN_SYMLINKS
	case DT_LNK: {
		FatLnkNode *node;
		node = (FatLnkNode *)kmalloc(sizeof(FatLnkNode), GFP_NORMAL);
		node->mf_ops    = &Fat_LnkOps.lno_node.no_file;
		node->mf_flags  = MFILE_F_NOUSRIO | MFILE_F_NOUSRMMAP;
		node->fn_fsdata = &node->fln_fdat;
		result = node;
	}	break;
#endif /* CONFIG_HAVE_MODFAT_CYGWIN_SYMLINKS */

	default: __builtin_unreachable();
	}
	dat = result->fn_fsdata;
	TRY {
		/* FAT uses the absolute on-disk position of file entries as INode number */
		result->fn_ino = (ino_t)Fat_GetAbsDiskPos(dir, ent->fad_ent.fde_pos);

		/* Allocate the initial cluster vector. */
		dat->fn_clusterv = (FatClusterIndex *)kmalloc(sizeof(FatClusterIndex), GFP_NORMAL);
	} EXCEPT {
		kfree(result);
		RETHROW();
	}

	/* Load file cluster number. */
	dat->fn_clusterc    = 1;
	dat->fn_clusterv[0] = LETOH16(ent->fad_dos.f_clusterlo);

	/* Fill in common fields from the DOS directory entry. */
	atomic64_init(&result->mf_filesize, LETOH32(ent->fad_dos.f_size));
	if (ent->fad_ent.fde_ent.fd_type == DT_DIR)
		atomic64_init(&result->mf_filesize, (uint64_t)-1);
	result->fn_mode = DTTOIF(ent->fad_ent.fde_ent.fd_type);
	if (super->ft_features & FAT_FEATURE_ARB) {
		u16 arb = LETOH16(ent->fad_dos.f_arb);
		mode_t unix_perm = 0777;
		/* Use the ARB to implement unix file permissions. */
		if (arb & FAT_ARB_NO_OX)
			unix_perm &= ~S_IXUSR; /* Disable: Execute by owner */
		if (arb & FAT_ARB_NO_OW)
			unix_perm &= ~S_IWUSR; /* Disable: Write by owner */
		if (arb & FAT_ARB_NO_OR)
			unix_perm &= ~S_IRUSR; /* Disable: Read by owner */

		if (arb & FAT_ARB_NO_GX)
			unix_perm &= ~S_IXGRP; /* Disable: Execute by group */
		if (arb & FAT_ARB_NO_GW)
			unix_perm &= ~S_IWGRP; /* Disable: Write by group */
		if (arb & FAT_ARB_NO_GR)
			unix_perm &= ~S_IRGRP; /* Disable: Read by group */

		if (arb & FAT_ARB_NO_WX)
			unix_perm &= ~S_IXOTH; /* Disable: Execute by world */
		if (arb & FAT_ARB_NO_WW)
			unix_perm &= ~S_IWOTH; /* Disable: Write by world */
		if (arb & FAT_ARB_NO_WR)
			unix_perm &= ~S_IROTH; /* Disable: Read by world */
		result->fn_mode |= unix_perm;
	} else {
		assert(!(super->ft_mode & ~0777));
		/* 32-bit clusters */
		dat->fn_clusterv[0] |= (u32)LETOH16(ent->fad_dos.f_clusterhi) << 16;
		result->fn_mode |= 0222 | (super->ft_mode & 0555);
	}

	/* Implement the read-only attribute via unix permissions. */
	if (ent->fad_dos.f_attr & FATATTR_RO)
		result->fn_mode &= ~0222;

	/* FAT files always have exactly 1 link (unless they've been deleted) */
	result->fn_nlink = 1;

	/* Convert timestamps. */
	FatFileMTime_Decode(&ent->fad_dos.f_mtime, &result->mf_mtime);
	FatFileBTime_Decode(&ent->fad_dos.f_btime, &result->mf_btime);
	if (super->ft_features & FAT_FEATURE_UGID) {
		/* In-built user/group ID support */
		result->fn_uid = (uid_t)ent->fad_dos.f_uid;
		result->fn_gid = (gid_t)ent->fad_dos.f_gid;
		/* Re-use the last-modified timestamp for access time. */
		result->mf_atime.tv_sec  = result->mf_mtime.tv_sec;
		result->mf_atime.tv_nsec = result->mf_mtime.tv_nsec;
	} else {
		result->fn_uid = super->ft_uid;
		result->fn_gid = super->ft_gid;
		FatFileATime_Decode(&ent->fad_dos.f_atime,
		                    &result->mf_atime);
	}

	/* Fill in remaining fields. */
	result->mf_parts = NULL;
	SLIST_INIT(&result->mf_changed);
	dat->fn_ent = incref(ent);
	dat->fn_dir = mfile_asfatdir(incref(dir));
	shared_rwlock_init(&dat->fn_lock);
	return result;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(KCALL fatsuper_v_validuid)(struct fsuper *__restrict self, uid_t uid) {
	FatSuperblock *me = fsuper_asfat(self);
	if (me->ft_features & FAT_FEATURE_UGID)
		return uid >= 0 && uid <= 0xff;
	return uid == me->ft_uid;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(KCALL fatsuper_v_validgid)(struct fsuper *__restrict self, gid_t gid) {
	FatSuperblock *me = fsuper_asfat(self);
	if (me->ft_features & FAT_FEATURE_UGID)
		return gid >= 0 && gid <= 0xff;
	return gid == me->ft_gid;
}

PRIVATE NONNULL((1, 2)) void
NOTHROW(KCALL fatsuper_v_truncate_atime)(struct fsuper *__restrict UNUSED(self),
                                         /*in|out*/ struct timespec *__restrict tms) {
	struct fat_fileatime ts;
	/* TODO: atime only exists when `FAT_FEATURE_ATIME' is available.
	 *       Otherwise, we set it equal to mtime.
	 * To support something  like this, all  timestamps
	 * must be truncated at the same time by a singular
	 * operator! */
	FatFileATime_Encode(&ts, tms);
	FatFileATime_Decode(&ts, tms);
}

PRIVATE NONNULL((1, 2)) void
NOTHROW(KCALL fatsuper_v_truncate_mtime)(struct fsuper *__restrict UNUSED(self),
                                         /*in|out*/ struct timespec *__restrict tms) {
	struct fat_filemtime ts;
	FatFileMTime_Encode(&ts, tms);
	FatFileMTime_Decode(&ts, tms);
}

PRIVATE NONNULL((1, 2)) void
NOTHROW(KCALL fatsuper_v_truncate_ctime)(struct fsuper *__restrict UNUSED(self),
                                         /*in|out*/ struct timespec *__restrict tms) {
	COMPILER_IMPURE();
	(void)tms;
	/* TODO: Truncation must set `ctime = mtime'
	 *       For this purpose, the timestamp-truncate interface must be redesigned! */
}

PRIVATE NONNULL((1, 2)) void
NOTHROW(KCALL fatsuper_v_truncate_btime)(struct fsuper *__restrict UNUSED(self),
                                         /*in|out*/ struct timespec *__restrict tms) {
	struct fat_filebtime ts;
	FatFileBTime_Encode(&ts, tms);
	FatFileBTime_Decode(&ts, tms);
}

PRIVATE NONNULL((1)) void KCALL
fatsuper_v_sync(struct fsuper *__restrict self)
		THROWS(E_IOERROR, ...) {
	FatSuperblock *me = fsuper_asfat(self);
	/* When using a custom file for accessing the FAT, that file must be synced */
	if (me->ft_fat_file != me->ft_super.ffs_super.fs_dev)
		mfile_sync(me->ft_fat_file);
}


PRIVATE BLOCKING WUNUSED NONNULL((1)) bool KCALL
fatsuper_v_getlabel(struct fsuper *__restrict self,
                    USER CHECKED char buf[FSLABEL_MAX])
		THROWS(E_IOERROR, E_SEGFAULT, ...) {
	static_assert(FSLABEL_MAX >= 12);
	FatSuperblock *me = fsuper_asfat(self);
	char label[12];

	/* Load current label */
	atomic_lock_acquire_smp(&me->fs_stringslock);
	memcpy(label, me->ft_label, 12);
	atomic_lock_release_smp(&me->fs_stringslock);

	/* Copy label to user-space.  */
	strcpy(buf, label);
	return true;
}

PRIVATE BLOCKING WUNUSED NONNULL((1)) bool KCALL
fatsuper_v_setlabel(struct fsuper *__restrict self,
                    USER CHECKED char const *name, size_t namelen)
		THROWS(E_IOERROR, E_FSERROR_READONLY, E_SEGFAULT,
		       E_INVALID_ARGUMENT_BAD_VALUE, ...) {
	unsigned int i;
	char newlabel[12];
	FatSuperblock *me = fsuper_asfat(self);
	pos_t diskaddr;
	if unlikely(namelen >= 12)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE, E_INVALID_ARGUMENT_CONTEXT_FSLABEL_TOO_LONG, namelen);
	*(char *)mempcpy(newlabel, name, namelen) = '\0';

	/* Write the updated label string to disk. */
	for (i = 0; i < 11; ++i) {
		if (newlabel[i] == '\0')
			newlabel[i] = ' ';
	}
	diskaddr = (pos_t)(me->ft_type == FAT32 ? offsetof(FatDiskHeader, fat32.f32_label)
	                                        : offsetof(FatDiskHeader, fat16.f16_label));
	mfile_writeall(me->ft_super.ffs_super.fs_dev, newlabel, 11 * sizeof(char), diskaddr);
	mfile_sync(me->ft_super.ffs_super.fs_dev);

	/* Save the new label */
	atomic_lock_acquire_smp(&me->fs_stringslock);
	memcpy(me->ft_label, newlabel, 12);
	atomic_lock_release_smp(&me->fs_stringslock);

	return true;
}


PRIVATE struct flatsuper_ops const Fat16_SuperOps = {
	.ffso_makenode = &fatsuper_v_makenode,
	.ffso_super = {
		.so_getlabel       = &fatsuper_v_getlabel,
		.so_setlabel       = &fatsuper_v_setlabel,
		.so_validuid       = &fatsuper_v_validuid,
		.so_validgid       = &fatsuper_v_validgid,
		.so_truncate_atime = &fatsuper_v_truncate_atime,
		.so_truncate_mtime = &fatsuper_v_truncate_mtime,
		.so_truncate_ctime = &fatsuper_v_truncate_ctime,
		.so_truncate_btime = &fatsuper_v_truncate_btime,
		.so_sync           = &fatsuper_v_sync,
		.so_fdir = {
			.dno_node = {
				.no_file = {
					.mo_destroy    = &fatsuper_v_destroy,
					.mo_loadblocks = &fat16root_loadblocks,
					.mo_saveblocks = &fat16root_v_saveblocks,
					.mo_changed    = &flatsuper_v_changed,
					.mo_stream     = &fatdir_v_stream_ops,
				},
				.no_free   = &fatsuper_v_free,
				.no_wrattr = &fnode_v_wrattr_noop,
			},
			.dno_lookup = &flatdirnode_v_lookup,
			.dno_enumsz = fatdir_v_enumsz,
			.dno_enum   = &fatdir_v_enum,
			.dno_mkfile = &flatdirnode_v_mkfile,
			.dno_unlink = &flatdirnode_v_unlink,
			.dno_rename = &flatdirnode_v_rename,
#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
			.dno_attach_notify = &flatdirnode_v_attach_notify,
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
		},
	},
	.ffso_flat = {
		.fdnx_readdir    = &fatdir_v_readdir,
		.fdnx_writedir   = &fatdir_v_writedir,
		.fdnx_deleteent  = &fatdir_v_deleteent,
		.fdnx_mkfile     = &fatdir_v_mkfile,
		.fdnx_mkent      = &fatdir_v_mkent,
		.fdnx_allocfile  = &fatdir_v_allocfile,
		.fdnx_deletefile = &fatdir_v_deletefile,
	},
};
PRIVATE struct flatsuper_ops const Fat32_SuperOps = {
	.ffso_makenode = &fatsuper_v_makenode,
	.ffso_super = {
		.so_getlabel       = &fatsuper_v_getlabel,
		.so_setlabel       = &fatsuper_v_setlabel,
		.so_validuid       = &fatsuper_v_validuid,
		.so_validgid       = &fatsuper_v_validgid,
		.so_truncate_atime = &fatsuper_v_truncate_atime,
		.so_truncate_mtime = &fatsuper_v_truncate_mtime,
		.so_truncate_ctime = &fatsuper_v_truncate_ctime,
		.so_truncate_btime = &fatsuper_v_truncate_btime,
		.so_sync           = &fatsuper_v_sync,
		.so_fdir = {
			.dno_node = {
				.no_file = {
					.mo_destroy    = &fatsuper_v_destroy,
					.mo_loadblocks = &fat_v_loadblocks,
					.mo_saveblocks = &fat_v_saveblocks,
					.mo_changed    = &flatsuper_v_changed,
					.mo_stream     = &fatdir_v_stream_ops,
				},
				.no_free   = &fatsuper_v_free,
				.no_wrattr = &fnode_v_wrattr_noop,
			},
			.dno_lookup = &flatdirnode_v_lookup,
			.dno_enumsz = fatdir_v_enumsz,
			.dno_enum   = &fatdir_v_enum,
			.dno_mkfile = &flatdirnode_v_mkfile,
			.dno_unlink = &flatdirnode_v_unlink,
			.dno_rename = &flatdirnode_v_rename,
#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
			.dno_attach_notify = &flatdirnode_v_attach_notify,
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
		},
	},
	.ffso_flat = {
		.fdnx_readdir    = &fatdir_v_readdir,
		.fdnx_writedir   = &fatdir_v_writedir,
		.fdnx_deleteent  = &fatdir_v_deleteent,
		.fdnx_mkfile     = &fatdir_v_mkfile,
		.fdnx_mkent      = &fatdir_v_mkent,
		.fdnx_allocfile  = &fatdir_v_allocfile,
		.fdnx_deletefile = &fatdir_v_deletefile,
	},
};







/************************************************************************/
/* The FAT get/set implementation for different table sizes.            */
/************************************************************************/
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) FatClusterIndex FCALL
Fat12_GetFatIndirection(FatSuperblock const *__restrict self,
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

PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) FatClusterIndex FCALL
Fat16_GetFatIndirection(FatSuperblock const *__restrict self,
                        FatClusterIndex index) {
	assertf(index < self->ft_fat_length,
	        "Out-of-bounds FAT index: %" PRIu32 " >= %" PRIu32 "",
	        index, self->ft_fat_length);
	return ((u16 const *)self->ft_fat_table)[index];
}

PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) FatClusterIndex FCALL
Fat32_GetFatIndirection(FatSuperblock const *__restrict self,
                        FatClusterIndex index) {
	assertf(index < self->ft_fat_length,
	        "Out-of-bounds FAT index: %" PRIu32 " >= %" PRIu32 "",
	        index, self->ft_fat_length);
	return ((u32 const *)self->ft_fat_table)[index];
}

PRIVATE NOBLOCK NONNULL((1)) void FCALL
Fat12_SetFatIndirection(FatSuperblock *__restrict self,
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

PRIVATE NOBLOCK NONNULL((1)) void FCALL
Fat16_SetFatIndirection(FatSuperblock *__restrict self,
                        FatClusterIndex index,
                        FatClusterIndex indirection_target) {
	assertf(index < self->ft_fat_length,
	        "Out-of-bounds FAT index: %" PRIu32 " >= %" PRIu32 "",
	        index, self->ft_fat_length);
	((u16 *)self->ft_fat_table)[index] = (u16)indirection_target;
}

PRIVATE NOBLOCK NONNULL((1)) void FCALL
Fat32_SetFatIndirection(FatSuperblock *__restrict self,
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
	}
	while (size && FAT_ISSPACE(buf[size - 1]))
		--size;
	buf[size] = '\0';
}

PRIVATE WUNUSED NONNULL((1)) struct fsuper *KCALL
fatfs_open(struct ffilesys *__restrict UNUSED(filesys),
           struct mfile *dev, UNCHECKED USER char *args) {
	FatSuperblock *result;
	FatDiskHeader *disk;
	u16 sector_size;

	(void)args; /* XXX: User-arguments. */
	assert(dev);

	/* Read the FAT disk header. */
	(mfile_getblocksize(dev) == sizeof(FatDiskHeader))
	? (disk = (FatDiskHeader *)aligned_alloca(sizeof(FatDiskHeader),
	                                          sizeof(FatDiskHeader)),
	   mfile_rdblocks(dev, 0, pagedir_translate(disk), sizeof(FatDiskHeader)))
	: (disk = (FatDiskHeader *)alloca(sizeof(FatDiskHeader)),
	   mfile_readall(dev, disk, sizeof(FatDiskHeader), 0));

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
	result = (FatSuperblock *)kmalloc(sizeof(FatSuperblock), GFP_NORMAL);
	TRY {
		result->ft_sectorshift = CTZ(sector_size);

		/* Fill in filesystem info. */
		result->ft_sectormask = sector_size - 1;
		result->ft_uid        = 0;
		result->ft_gid        = 0;
		result->ft_mode       = 0755; /* Read/Execute permissions for everyone. */
		result->ft_features   = 0;
		shared_rwlock_init(&result->ft_fat_lock);
		result->ft_free_pos = 0;

		/* Configure root directory behavior. */
		atomic64_init(&result->ft_super.ffs_super.fs_root.mf_filesize, (uint64_t)-1);
		result->ft_super.ffs_super.fs_root.mf_parts = NULL;
		SLIST_INIT(&result->ft_super.ffs_super.fs_root.mf_changed);
		result->ft_super.ffs_super.fs_root.mf_flags = MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO | MFILE_F_FIXEDFILESIZE;
		result->ft_super.ffs_super.fs_root.fn_mode  = S_IFDIR | 0777;

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
			root_sectors = (LETOH16(disk->bpb.bpb_maxrootsize) *
			                sizeof(struct fat_dirent) +
			                result->ft_sectormask) >>
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
			if (total_clusters > FAT16_MAXCLUSTERS) {
				result->ft_type = FAT32;
			} else if (total_clusters > FAT12_MAXCLUSTERS) {
				result->ft_type = FAT16;
			} else {
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
			shared_rwlock_init(&result->ft_fdat.fn_lock);
			result->ft_fdat.fn_clusterc    = 1;
			result->ft_fdat.fn_clusterv    = (FatClusterIndex *)kmalloc(sizeof(FatClusterIndex), GFP_NORMAL);
			result->ft_fdat.fn_clusterv[0] = LETOH32(disk->fat32.f32_root_cluster);
			result->ft_fat_get = &Fat32_GetFatIndirection;
			result->ft_fat_set = &Fat32_SetFatIndirection;
		} else {
			if (result->ft_type == FAT12) {
				result->ft_cluster_eof_marker = 0xfff;
				result->ft_fat_get = &Fat12_GetFatIndirection;
				result->ft_fat_set = &Fat12_SetFatIndirection;
			} else {
				result->ft_cluster_eof_marker = 0xffff;
				result->ft_fat_get = &Fat16_GetFatIndirection;
				result->ft_fat_set = &Fat16_SetFatIndirection;
			}
			if (disk->fat16.f16_signature != 0x28 &&
			    disk->fat16.f16_signature != 0x29)
				THROW(E_FSERROR_WRONG_FILE_SYSTEM);
			result->ft_volid = LETOH32(disk->fat16.f16_volid);
			memcpy(result->ft_label, disk->fat16.f16_label, sizeof(disk->fat16.f16_label));
			memcpy(result->ft_sysname, disk->fat16.f16_sysname, sizeof(disk->fat16.f16_sysname));
			result->ft_fdat.fn16_root.r16_rootpos = (pos_t)LETOH16(disk->bpb.bpb_reserved_sectors);
			result->ft_fdat.fn16_root.r16_rootpos += (disk->bpb.bpb_fatc * LETOH16(disk->bpb.bpb_sectors_per_fat));
			result->ft_fdat.fn16_root.r16_rootpos <<= result->ft_sectorshift;
			result->ft_sec4fat                    = LETOH16(disk->bpb.bpb_sectors_per_fat);
			result->ft_fdat.fn16_root.r16_rootsiz = (u32)LETOH16(disk->bpb.bpb_maxrootsize);
			result->ft_fdat.fn16_root.r16_rootsiz *= sizeof(struct fat_dirent);
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

		memcpy(&result->ft_oem, disk->bpb.bpb_oem, sizeof(disk->bpb.bpb_oem));
		result->ft_fat_size = (size_t)result->ft_sec4fat << result->ft_sectorshift;
		trimspecstring(result->ft_oem, 8);
		trimspecstring(result->ft_label, 11);
		trimspecstring(result->ft_sysname, 8);
#ifndef CONFIG_NO_SMP
		atomic_lock_init(&result->fs_stringslock);
#endif /* !CONFIG_NO_SMP */

		/* Map the FAT table into memory. */
		TRY {
			result->ft_freefat = mman_unmap_kram_cookie_alloc();
			TRY {
				/* In case there are multiple FAT copies, modifications made to the FAT table must
				 * be synced in multiple locations across  the block-device. For this purpose,  we
				 * make use of a custom mem-file that does this job for us. */
				if (result->ft_fat_count > 1) {
					struct multifat_sync_file *fatfile;
					uint64_t fat_delta;

					/* Calculate the delta between different FAT copies. */
					fat_delta = (uint64_t)result->ft_sec4fat << result->ft_sectorshift;

					/* Allocate the sync file. */
					fatfile = (struct multifat_sync_file *)kmalloc(sizeof(struct multifat_sync_file), GFP_NORMAL);

					/* Initialize the mfile-portion of the sync file. */
					_mfile_init(fatfile, &multifat_sync_file_ops,
					            dev->mf_blockshift, dev->mf_iobashift);
					fatfile->mf_parts = NULL;
					SLIST_INIT(&fatfile->mf_changed);
					fatfile->mf_flags = MFILE_F_NORMAL;
					atomic64_init(&fatfile->mf_filesize, atomic64_read(&dev->mf_filesize));

					/* Timestamps don't matter here; this file isn't exposed to user-space. */
					DBG_memset(&fatfile->mf_atime, 0xcc, sizeof(fatfile->mf_atime));
					DBG_memset(&fatfile->mf_mtime, 0xcc, sizeof(fatfile->mf_mtime));
					DBG_memset(&fatfile->mf_ctime, 0xcc, sizeof(fatfile->mf_ctime));
					DBG_memset(&fatfile->mf_btime, 0xcc, sizeof(fatfile->mf_btime));

					/* Initialize custom fields. */
					fatfile->mfsf_dev              = incref(dev);
					fatfile->mfsf_delta_is_aligned = ((fat_delta >> dev->mf_blockshift) << dev->mf_blockshift) == fat_delta;
					fatfile->mfsf_fat_delta        = fat_delta;
					fatfile->mfsf_fat_count        = result->ft_fat_count;

					/* Use this custom file for mapping the FAT table. */
					result->ft_fat_file = fatfile; /* Inherit reference */
				} else {
					result->ft_fat_file = incref(dev);
				}
				TRY {
					/* Map the FAT table into memory. */
					result->ft_fat_table = mman_map(/* self:        */ &mman_kernel,
					                                /* hint:        */ MHINT_GETADDR(KERNEL_MHINT_DEVICE),
					                                /* num_bytes:   */ result->ft_fat_size,
					                                /* prot:        */ PROT_READ | PROT_WRITE | PROT_SHARED | PROT_FORCEWRITE,
					                                /* flags:       */ MHINT_GETMODE(KERNEL_MHINT_DEVICE),
					                                /* file:        */ result->ft_fat_file,
					                                /* file_fspath: */ NULL,
					                                /* file_fsname: */ NULL,
					                                /* file_pos:    */ FAT_SECTORADDR(result, result->ft_fat_start));
				} EXCEPT {
					decref_unlikely(result->ft_fat_file);
					RETHROW();
				}
			} EXCEPT {
				mman_unmap_kram_cookie_free(result->ft_freefat);
				RETHROW();
			}
		} EXCEPT {
			if (result->ft_type == FAT32)
				kfree(result->ft_fdat.fn_clusterv);
			RETHROW();
		}
	} EXCEPT {
		kfree(result);
		RETHROW();
	}

	/* Fill in mandatory superblock fields. */
	/*result->ft_super.ffs_super.fs_root.mf_blockshift       = result->ft_sectorshift;*/ /* It's the same field! */
	result->ft_super.ffs_super.fs_root.mf_iobashift          = dev->mf_iobashift;
	result->ft_super.ffs_super.fs_root.fn_ino                = 0;
	result->ft_super.ffs_super.fs_feat.sf_filesize_max       = (pos_t)UINT32_MAX;
	result->ft_super.ffs_super.fs_feat.sf_uid_max            = 0;
	result->ft_super.ffs_super.fs_feat.sf_gid_max            = 0;
	result->ft_super.ffs_super.fs_feat.sf_symlink_max        = 0;
	result->ft_super.ffs_super.fs_feat.sf_link_max           = 1;
	result->ft_super.ffs_super.fs_feat.sf_magic              = MSDOS_SUPER_MAGIC;
	result->ft_super.ffs_super.fs_feat.sf_rec_incr_xfer_size = result->ft_sectormask + 1;
	result->ft_super.ffs_super.fs_feat.sf_rec_max_xfer_size  = result->ft_sectormask + 1;
	result->ft_super.ffs_super.fs_feat.sf_rec_min_xfer_size  = result->ft_sectormask + 1;
	result->ft_super.ffs_super.fs_feat.sf_rec_xfer_align     = (u32)1 << dev->mf_iobashift;
	result->ft_super.ffs_super.fs_feat.sf_name_max           = LFN_SEQNUM_MAXCOUNT * LFN_NAME;
	result->ft_super.ffs_super.fs_feat.sf_filesizebits       = 32;
	result->ft_super.ffs_super.fs_root.fn_fsdata             = &result->ft_fdat;
	result->ft_super.ffs_super.fs_root.mf_atime              = realtime();
	result->ft_super.ffs_super.fs_root.mf_mtime              = result->ft_super.ffs_super.fs_root.mf_atime;
	result->ft_super.ffs_super.fs_root.mf_ctime              = result->ft_super.ffs_super.fs_root.mf_atime;
	result->ft_super.ffs_super.fs_root.mf_btime              = result->ft_super.ffs_super.fs_root.mf_atime;
	result->ft_super.ffs_super.fs_root.fn_nlink              = 1;
	result->ft_super.ffs_super.fs_root.fn_uid                = 0;
	result->ft_super.ffs_super.fs_root.fn_gid                = 0;
	result->ft_fdat.fn_ent                                   = NULL;
	result->ft_fdat.fn_dir                                   = NULL;
	result->_ft_1dot                                         = (uint32_t)-1;
	result->_ft_2dot                                         = (uint32_t)-1;

	/* Special case for when uid/gid support is available. */
	if (result->ft_features & FAT_FEATURE_UGID) {
		result->ft_super.ffs_super.fs_feat.sf_uid_max = (uid_t)0xff;
		result->ft_super.ffs_super.fs_feat.sf_gid_max = (gid_t)0xff;
	}
#ifdef CONFIG_HAVE_MODFAT_CYGWIN_SYMLINKS
	if (!(result->ft_features & FAT_FEATURE_NO_CYGWIN_SYMLINK))
		result->ft_super.ffs_super.fs_feat.sf_symlink_max = (pos_t)FAT_SYMLINK_FILE_TEXTLEN(UINT32_MAX);
#endif /* CONFIG_HAVE_MODFAT_CYGWIN_SYMLINKS */

	/* Select root directory operators. */
	result->ft_super.ffs_super.fs_root.mf_ops = result->ft_type == FAT32
	                                            ? &Fat32_SuperOps.ffso_super.so_fdir.dno_node.no_file
	                                            : &Fat16_SuperOps.ffso_super.so_fdir.dno_node.no_file;

	/* Fill in fields relating to `flatsuper' */
	result->ft_super.ffs_features = FFLATSUPER_FEAT_WRITEDIR_CHANGES_INO;
	flatdirdata_init(&result->ft_super.ffs_rootdata);


	printk(KERN_INFO "[fat] Loaded FAT%u-filesystem "
	                 "[oem=%q] [label=%q] [sysname=%q]\n",
	       result->ft_type == FAT12 ? 12 : result->ft_type == FAT16 ? 16 : 32,
	       result->ft_oem, result->ft_label, result->ft_sysname);
	return &result->ft_super.ffs_super;
}



/************************************************************************/
/* FAT Filesystem Type                                                  */
/************************************************************************/
PRIVATE struct ffilesys fat_filesys = {
	.ffs_drv = &drv_self,
	{ .ffs_open = &fatfs_open },
	.ffs_flags = FFILESYS_F_NORMAL,
	/* .ffs_name = */ "fat",
};

static_assert((offsetof(FatSuperblock, ft_super.ffs_rootdata) -
               offsetof(FatSuperblock, ft_super.ffs_super.fs_root)) ==
              offsetof(FatDirNode, fdn_data));
static_assert((offsetof(FatSuperblock, ft_fdat) -
               offsetof(FatSuperblock, ft_super.ffs_super.fs_root)) ==
              offsetof(FatDirNode, fdn_fdat));



/************************************************************************/
/* Filesystem Type register/unregister                                  */
/************************************************************************/
#ifdef BUILDING_KERNEL_CORE
INTERN ATTR_FREETEXT void KCALL kernel_initialize_fat_driver(void)
#else /* BUILDING_KERNEL_CORE */
PRIVATE DRIVER_INIT ATTR_FREETEXT void KCALL init(void)
#endif /* !BUILDING_KERNEL_CORE */
{
	ffilesys_register(&fat_filesys);
}

#ifndef BUILDING_KERNEL_CORE
PRIVATE DRIVER_FINI void KCALL fini(void) {
	ffilesys_unregister(&fat_filesys);
}
#endif /* !BUILDING_KERNEL_CORE */

DECL_END

#endif /* !GUARD_MODFAT_FAT_C */
