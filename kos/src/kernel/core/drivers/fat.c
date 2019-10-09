/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_DRIVERS_FAT_C
#define GUARD_KERNEL_CORE_DRIVERS_FAT_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <drivers/fat.h>
#include <fs/node.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <kernel/user.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/bit.h>
#include <hybrid/byteswap.h>
#include <hybrid/minmax.h>
#include <hybrid/overflow.h>
#include <hybrid/unaligned.h>

#include <bits/confname.h>
#include <kos/dev.h>
#include <kos/except-inval.h>
#include <linux/magic.h>
#include <linux/msdos_fs.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <sys/statvfs.h>

#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <unicode.h>

DECL_BEGIN

#define FAT_ISSPACE(c)  (isspace(c) || iscntrl(c)/* || isblank(c)*/)


/* The fat get/set implementation for different table sizes. */
PRIVATE FatClusterIndex KCALL Fat12_GetFatIndirection(FatSuperblock *__restrict self, FatClusterIndex index);
PRIVATE FatClusterIndex KCALL Fat16_GetFatIndirection(FatSuperblock *__restrict self, FatClusterIndex index);
PRIVATE FatClusterIndex KCALL Fat32_GetFatIndirection(FatSuperblock *__restrict self, FatClusterIndex index);
PRIVATE void KCALL Fat16_SetFatIndirection(FatSuperblock *__restrict self, FatClusterIndex index, FatClusterIndex indirection_target);
PRIVATE void KCALL Fat12_SetFatIndirection(FatSuperblock *__restrict self, FatClusterIndex index, FatClusterIndex indirection_target);
PRIVATE void KCALL Fat32_SetFatIndirection(FatSuperblock *__restrict self, FatClusterIndex index, FatClusterIndex indirection_target);
PRIVATE FatSectorIndex KCALL Fat12_GetTableSector(FatSuperblock *__restrict self, FatClusterIndex id);
PRIVATE FatSectorIndex KCALL Fat16_GetTableSector(FatSuperblock *__restrict self, FatClusterIndex id);
PRIVATE FatSectorIndex KCALL Fat32_GetTableSector(FatSuperblock *__restrict self, FatClusterIndex id);

INTDEF struct inode_type Fat_FileNodeOperators;
INTDEF struct inode_type Fat_DirectoryNodeOperators;
INTDEF struct inode_type Fat16_RootDirectoryFileEntryNodeOperators;
INTDEF struct inode_type Fat16_RootDirectoryDirectoryEntryNodeOperators;
INTDEF struct inode_type Fat16_RootDirectoryNodeOperators;
INTDEF struct inode_type Fat32_RootDirectoryNodeOperators;












INTERN void KCALL
Fat32_VReadFromINode(struct inode *__restrict self,
                     CHECKED USER byte_t *buf,
                     size_t bufsize, pos_t pos) {
	FatSuperblock *fat = (FatSuperblock *)self->i_super;
	assert(fat != self || fat->f_type == FAT32);
	if (bufsize) {
		for (;;) {
			FatClusterIndex cluster;
			pos_t diskpos;
			size_t cluster_number = (size_t)(pos / fat->f_clustersize);
			size_t cluster_offset = (size_t)(pos % fat->f_clustersize);
			size_t max_io;
			cluster = Fat_GetFileCluster(self, cluster_number,
			                             FAT_GETCLUSTER_MODE_FNORMAL);
			if (cluster >= fat->f_cluster_eof) {
				/* Read all ZEROes after EOF. */
				memset(buf, 0, bufsize);
				return;
			}
			diskpos = FAT_CLUSTERADDR(fat, cluster);
			diskpos += cluster_offset;
			max_io = fat->f_clustersize - cluster_offset;
			/* Optimization: When reading large amounts of data, check if the
			 *               underlying disk chunks were allocated consecutively.
			 *               If they were, then we can simply do one continuous
			 *               read, processing more than one cluster at a time. */
			while (max_io < bufsize &&
			       Fat_GetFileCluster(self, cluster_number + 1,
			                          FAT_GETCLUSTER_MODE_FNORMAL) ==
			       cluster + 1) {
				max_io += fat->f_clustersize;
				++cluster_number;
				++cluster;
			}
			if (max_io > bufsize)
				max_io = bufsize;
			block_device_read(self->i_super->s_device,
			                  buf,
			                  max_io,
			                  diskpos);
			if (max_io >= bufsize)
				break;
			bufsize -= max_io;
			pos += max_io;
			buf += max_io;
		}
	}
}
INTERN size_t KCALL
Fat32_VTryReadFromINode(struct inode *__restrict self,
                        CHECKED USER byte_t *buf,
                        size_t bufsize, pos_t pos) {
	size_t result      = bufsize;
	FatSuperblock *fat = (FatSuperblock *)self->i_super;
	assert(fat != self || fat->f_type == FAT32);
	if (bufsize) {
		for (;;) {
			FatClusterIndex cluster;
			pos_t diskpos;
			size_t cluster_number = (size_t)(pos / fat->f_clustersize);
			size_t cluster_offset = (size_t)(pos % fat->f_clustersize);
			size_t max_io;
			cluster = Fat_GetFileCluster(self, cluster_number,
			                             FAT_GETCLUSTER_MODE_FNORMAL);
			if (cluster >= fat->f_cluster_eof)
				return result - bufsize;
			diskpos = FAT_CLUSTERADDR(fat, cluster);
			diskpos += cluster_offset;
			max_io = fat->f_clustersize - cluster_offset;
			/* Optimization: When reading large amounts of data, check if the
			 *               underlying disk chunks were allocated consecutively.
			 *               If they were, then we can simply do one continuous
			 *               read, processing more than one cluster at a time. */
			while (max_io < bufsize &&
			       Fat_GetFileCluster(self, cluster_number + 1,
			                          FAT_GETCLUSTER_MODE_FNORMAL) ==
			       cluster + 1) {
				max_io += fat->f_clustersize;
				++cluster_number;
				++cluster;
			}
			if (max_io > bufsize)
				max_io = bufsize;
			block_device_read(self->i_super->s_device,
			                  buf,
			                  max_io,
			                  diskpos);
			if (max_io >= bufsize)
				break;
			bufsize -= max_io;
			pos += max_io;
			buf += max_io;
		}
	}
	return result;
}
INTERN void KCALL
Fat32_VWriteToINode(struct inode *__restrict self,
                    CHECKED USER byte_t const *buf,
                    size_t bufsize, pos_t pos) {
	FatSuperblock *fat = (FatSuperblock *)self->i_super;
	assert(fat != self || fat->f_type == FAT32);
	if (bufsize) {
		for (;;) {
			FatClusterIndex cluster;
			pos_t diskpos;
			size_t cluster_number = (size_t)(pos / fat->f_clustersize);
			size_t cluster_offset = (size_t)(pos % fat->f_clustersize);
			size_t max_io;
			cluster = Fat_GetFileCluster(self, cluster_number,
			                             FAT_GETCLUSTER_MODE_FCREATE);
			diskpos = FAT_CLUSTERADDR(fat, cluster);
			diskpos += cluster_offset;
			max_io = fat->f_clustersize - cluster_offset;
			/* Optimization: When reading large amounts of data, check if the
			 *               underlying disk chunks were allocated consecutively.
			 *               If they were, then we can simply do one continuous
			 *               read, processing more than one cluster at a time. */
			while (max_io < bufsize &&
			       Fat_GetFileCluster(self, cluster_number + 1,
			                          FAT_GETCLUSTER_MODE_FCREATE) ==
			       cluster + 1) {
				max_io += fat->f_clustersize;
				++cluster_number, ++cluster;
			}
			if (max_io > bufsize)
				max_io = bufsize;
			block_device_write(self->i_super->s_device,
			                   buf,
			                   max_io,
			                   diskpos);
			if (max_io >= bufsize)
				break;
			bufsize -= max_io;
			pos += max_io;
			buf += max_io;
		}
	}
}


INTDEF void KCALL
Fat16_VReadFromRootDirectory(FatSuperblock *__restrict self,
                             CHECKED USER byte_t *buf,
                             size_t bufsize, pos_t pos) {
	size_t max_read;
	assert(self->i_super == self);
	assert(self->f_type != FAT32);
	max_read = self->i_fsdata->i16_root.f16_rootsiz;
	if (pos >= (pos_t)max_read) {
		memset(buf, 0, bufsize);
		return;
	}
	max_read -= (size_t)pos;
	/* Clear out trailing memory. */
	if (max_read < bufsize)
		memset(buf + max_read, 0, bufsize - max_read);
	else
		max_read = bufsize;
	/* Read actual data. */
	block_device_read(self->s_device,
	                  buf,
	                  max_read,
	                  self->i_fsdata->i16_root.f16_rootpos + pos);
}
INTDEF size_t KCALL
Fat16_VTryReadFromRootDirectory(FatSuperblock *__restrict self,
                                CHECKED USER byte_t *buf,
                                size_t bufsize, pos_t pos) {
	size_t max_read;
	assert(self->i_super == self);
	assert(self->f_type != FAT32);
	max_read = self->i_fsdata->i16_root.f16_rootsiz;
	if (pos >= (pos_t)max_read)
		return 0;
	max_read -= (size_t)pos;
	if (max_read > bufsize)
		max_read = bufsize;
	/* Read actual data. */
	block_device_read(self->s_device,
	                  buf,
	                  max_read,
	                  self->i_fsdata->i16_root.f16_rootpos + pos);
	return max_read;
}
INTDEF void KCALL
Fat16_VWriteToRootDirectory(FatSuperblock *__restrict self,
                            CHECKED USER byte_t const *buf,
                            size_t bufsize, pos_t pos) {
	size_t max_write;
	assert(self->i_super == self);
	assert(self->f_type != FAT32);
	max_write = self->i_fsdata->i16_root.f16_rootsiz;
	if (pos >= (pos_t)max_write)
		goto too_large;
	max_write -= (size_t)pos;
	if (max_write < bufsize)
		goto too_large;
	/* Write actual data. */
	block_device_write(self->i_super->s_device,
	                   buf,
	                   bufsize,
	                   self->i_fsdata->i16_root.f16_rootpos + pos);
	return;
too_large:
	THROW(E_FSERROR_DISK_FULL);
}

INTDEF void KCALL
Fat_VReadFromINode(struct inode *__restrict self,
                   CHECKED USER byte_t *buf,
                   size_t bufsize, pos_t pos) {
	if (self != self->i_super ||
	    ((FatSuperblock *)self)->f_type == FAT32) {
		Fat32_VReadFromINode(self, buf, bufsize, pos);
	} else {
		Fat16_VReadFromRootDirectory((FatSuperblock *)self, buf, bufsize, pos);
	}
}
INTDEF size_t KCALL
Fat_VTryReadFromINode(struct inode *__restrict self,
                      CHECKED USER byte_t *buf,
                      size_t bufsize, pos_t pos) {
	if (self != self->i_super ||
	    ((FatSuperblock *)self)->f_type == FAT32) {
		return Fat32_VTryReadFromINode(self, buf, bufsize, pos);
	} else {
		return Fat16_VTryReadFromRootDirectory((FatSuperblock *)self, buf, bufsize, pos);
	}
}
INTDEF void KCALL
Fat_VWriteToINode(struct inode *__restrict self,
                  CHECKED USER byte_t const *buf,
                  size_t bufsize, pos_t pos) {
	if (self != self->i_super ||
	    ((FatSuperblock *)self)->f_type == FAT32) {
		Fat32_VWriteToINode(self, buf, bufsize, pos);
	} else {
		Fat16_VWriteToRootDirectory((FatSuperblock *)self, buf, bufsize, pos);
	}
}






/* Returns the absolute on-disk position of `pos' in `self' */
INTERN pos_t KCALL
Fat_GetAbsDiskPos(struct inode *__restrict self, pos_t pos) {
	if (self != self->i_super ||
	    ((FatSuperblock *)self->i_super)->f_type == FAT32) {
		FatSuperblock *fat = (FatSuperblock *)self->i_super;
		FatClusterIndex cluster; pos_t diskpos;
		size_t cluster_number = (size_t)(pos / fat->f_clustersize);
		size_t cluster_offset = (size_t)(pos % fat->f_clustersize);
		cluster = Fat_GetFileCluster(self, cluster_number,
		                             FAT_GETCLUSTER_MODE_FCREATE);
		diskpos = FAT_CLUSTERADDR(fat, cluster);
		diskpos += cluster_offset;
		return diskpos;
	}
	pos += self->i_fsdata->i16_root.f16_rootpos;
	return pos;
}

LOCAL void KCALL
preallocate_cluster_vector_entries(struct inode *__restrict node,
                                   FatNode *__restrict data,
                                   FatSuperblock *__restrict fat,
                                   size_t min_num_clusters) {
	size_t new_alloc;
	assert(data == node->i_fsdata);
	assert(fat == (FatSuperblock *)node->i_super);
	assert(min_num_clusters >= data->i_clusterc);
	new_alloc = CEILDIV((size_t)node->i_filesize, fat->f_clustersize);
	if (new_alloc < min_num_clusters)
		new_alloc = min_num_clusters;
	if unlikely(new_alloc <= data->i_clustera)
		return; /* nothing to do here... */
	if unlikely(!new_alloc)
		new_alloc = 2;
	TRY {
		data->i_clusterv = (FatClusterIndex *)krealloc(data->i_clusterv,
		                                               new_alloc * sizeof(FatClusterIndex),
		                                               FS_GFP);
	} EXCEPT {
		if (!was_thrown(E_BADALLOC))
			RETHROW();
		goto allocate_smallest_possible;
	}
	__IF0 {
allocate_smallest_possible:
		/* Try to allocate the minimum increment. */
		if (min_num_clusters <= data->i_clustera)
			return;
		new_alloc = min_num_clusters;

		data->i_clusterv = (FatClusterIndex *)krealloc(data->i_clusterv,
		                                               new_alloc * sizeof(FatClusterIndex),
		                                               FS_GFP);
	}
	data->i_clustera = new_alloc;
}

LOCAL void KCALL
zero_initialize_cluster(FatSuperblock *__restrict fat,
                        FatClusterIndex cluster) {
	/* TODO */
}


/* Lookup (and potentially allocate the associated
 * chain for) the `nth_cluster' of the given `node' */
INTERN FatClusterIndex KCALL
Fat_GetFileCluster(struct inode *__restrict node,
                   size_t nth_cluster, unsigned int mode) {
	FatClusterIndex result;
	FatNode *data;
	FatSuperblock *fat;
	assert(sync_reading(node));
	data = node->i_fsdata;
	fat  = (FatSuperblock *)node->i_super;
	if unlikely(!data->i_clusterc) {
		/* Load the initial file cluster. */
		inode_loadattr(node);
		assert(data->i_clusterc != 0);
	}
	if (nth_cluster < data->i_clusterc) {
		result = data->i_clusterv[nth_cluster];
		if (result < fat->f_cluster_eof)
			return result; /* Simple case: cluster already cached. */
		assert(nth_cluster == data->i_clusterc - 1);
	} else {
		result = data->i_clusterv[data->i_clusterc - 1];
		if (result < fat->f_cluster_eof) {
			/* Not all clusters have been loaded, yet. -> load more now. */
			sync_write(node);
			TRY {
				preallocate_cluster_vector_entries(node, data, fat, nth_cluster + 1);
				for (;;) {
					result = Fat_GetFatIndirection(fat, result);
					data->i_clusterv[data->i_clusterc] = result;
					++data->i_clusterc;
					if (result >= fat->f_cluster_eof) {
						FatClusterIndex *new_vector;
						/* EOF reached before `nth_cluster' */
						if (mode & FAT_GETCLUSTER_MODE_FCREATE)
							goto create_more_clusters_already_locked;
						/* Try to free unused memory. */
						new_vector = (FatClusterIndex *)krealloc_nx(data->i_clusterv,
						                                            data->i_clusterc * sizeof(FatClusterIndex),
						                                            FS_GFP);
						if likely(new_vector)
							data->i_clusterv = new_vector;
						sync_endwrite(node);
						return result;
					}
					if (nth_cluster < data->i_clusterc) {
						/* The requested cluster was reached */
						assert(nth_cluster == data->i_clusterc - 1);
						assert(result == data->i_clusterv[nth_cluster]);
						break;
					}
				}
			} EXCEPT {
				sync_endwrite(node);
				RETHROW();
			}
			sync_endwrite(node);
			return result;
		}
	}
	/* All clusters are loaded, and the file potentially needs to be expanded. */
	assert(data->i_clusterv[data->i_clusterc - 1] >= fat->f_cluster_eof);
	if (!(mode & FAT_GETCLUSTER_MODE_FCREATE))
		return fat->f_cluster_eof_marker; /* EOF */
again_lock_node:
	sync_write(node);
	TRY {
		preallocate_cluster_vector_entries(node, data, fat, nth_cluster + 1);
	} EXCEPT {
		sync_endwrite(node);
		RETHROW();
	}
create_more_clusters_already_locked:
	if unlikely(!sync_trywrite(&fat->f_fat_lock)) {
		sync_endwrite(node);
		sync_write(&fat->f_fat_lock);
		sync_endwrite(&fat->f_fat_lock);
		goto again_lock_node;
	}
	TRY {
		assert(data->i_clusterv[data->i_clusterc - 1] >= fat->f_cluster_eof);
		assert(data->i_clustera >= nth_cluster + 1);
		/* Create more clusters. */
		for (;;) {
			result = Fat_FindFreeCluster(fat);
			/* Mark the new cluster as allocated. */
			Fat_SetFatIndirection(fat, result,
			                      fat->f_cluster_eof_marker);
			TRY {
				if (!(mode & FAT_GETCLUSTER_MODE_FNOZERO))
					zero_initialize_cluster(fat, result);
				data->i_clusterv[data->i_clusterc - 1] = result;
				data->i_clusterv[data->i_clusterc] = fat->f_cluster_eof_marker;
				++data->i_clusterc;
				TRY {
					if (data->i_clusterc == 2) {
						/* The pointer to the first cluster is stored in the INode.
						 * Since we've just written that pointer, mark the node as changed. */
						if (!(mode & FAT_GETCLUSTER_MODE_FNCHNGE))
							inode_changedattr(node);
					} else {
						/* Link the previous cluster onto the new one */
						assert(data->i_clusterc >= 3);
						/* -3: PREV_CLUSTER */
						/* -2: THIS_CLUSTER */
						/* -1: fat->f_cluster_eof_marker */
						Fat_SetFatIndirection(fat,
						                      data->i_clusterv[data->i_clusterc - 3],
						                      result);
					}
				} EXCEPT {
					--data->i_clusterc;
					assert(data->i_clusterv[data->i_clusterc - 1] == result);
					data->i_clusterv[data->i_clusterc - 1] = fat->f_cluster_eof_marker;
					RETHROW();
				}
			} EXCEPT {
				/* Free the new cluster on error. */
				Fat_SetFatIndirection(fat, result,
				                      FAT_CLUSTER_UNUSED);
				RETHROW();
			}
			if (nth_cluster < data->i_clusterc - 1) {
				/* The requested cluster was reached */
				assert(nth_cluster == data->i_clusterc - 2);
				assert(result == data->i_clusterv[nth_cluster]);
				break;
			}
		}
	} EXCEPT {
		sync_endwrite(&fat->f_fat_lock);
		sync_endwrite(node);
		RETHROW();
	}
	assert(result == data->i_clusterv[nth_cluster]);
	assert(result < fat->f_cluster_eof);
#ifndef NDEBUG
	{
		size_t i;
		assert(data->i_clusterv[data->i_clusterc - 1] >= fat->f_cluster_eof);
		for (i = 0; i < data->i_clusterc - 1; ++i) {
			FatClusterIndex curr, next, real_next;
			curr      = data->i_clusterv[i];
			next      = data->i_clusterv[i + 1];
			real_next = Fat_GetFatIndirection(fat, curr);
			assertf(next == real_next,
			        "Invalid indirection on cluster#%Iu (expected %#Ix -> %#Ix, but was %#Ix -> %#Ix)",
			        i, curr, next, curr, real_next);
		}
	}
#endif
	sync_endwrite(&fat->f_fat_lock);
	sync_endwrite(node);
	return result;
}




PRIVATE u32 KCALL
FatDirectory_AllocateFreeRange(struct directory_node *__restrict self,
                               u32 entry_count,
                               bool *pis_directory_end) {
	/* XXX: Search through available free ranges and return the first
	 *      one with at least `entry_count' free slots and set
	 *     `*pis_directory_end' to `false'.  Otherwise return the
	 *      index where the directory currently ends and set
	 *     `*pis_directory_end' to `true'. */

	/* Fallback: Manually search through the directory and check for empty ranges. */
	FatFile entry;
	u32 result = 0, i;
	for (i = 0;;) {
		if (Fat_VTryReadFromINode(self, (byte_t *)&entry, sizeof(entry),
		                          (pos_t)i * sizeof(FatFile)) < sizeof(FatFile) ||
		    entry.f_marker == MARKER_DIREND) {
			*pis_directory_end = true;
			return result;
		}
		if (entry.f_marker != MARKER_UNUSED) {
			result = ++i;
			continue;
		}
		++i;
		if (result + entry_count <= i) {
			*pis_directory_end = false;
			return result;
		}
	}
}

PRIVATE void
NOTHROW(KCALL FatDirectory_AddFreeRange)(struct directory_node *__restrict self,
                                         u32 first_entry_number, u32 entry_count) {
	/* XXX: Mark the given range as free, and panic of any entry is already marked as free. */
}
PRIVATE void
NOTHROW(KCALL FatDirectory_AddFreeFile)(struct directory_node *__restrict self,
                                        u32 entry_number) {
	/* XXX: Mark `entry_number' as free, but don't do anything if it was already marked as such. */
}
PRIVATE void
NOTHROW(KCALL FatDirectory_CheckTruncation)(struct directory_node *__restrict self) {
	if (self == self->i_super && ((FatSuperblock *)self)->f_type != FAT32)
		return; /* Fixed-length directory (cannot be truncated) */
	/* XXX: Check if the directory can be truncated.
	 *   -> A directory can be truncated whereever a free-entry
	 *      range is larger than one FAT-sector, in which case the
	 *      associated sector can simply be unlinked from the directory's
	 *      linked sector chain. */
}



PRIVATE u8 const dos8dot3_valid[256/8] = {
/*[[[deemon
#include <util>
function is_valid(ch) {
	if (ch <= 31 || ch == 127) return false;
	return string.chr(ch) !in "\"*+,/:;<=>?\\[]|.";
}
local valid_chars = [false] * 256;
for (local x: util.range(256))
	valid_chars[x] = is_valid(x);
local valid_bits = [0] * (256/8);
for (local x: util.range(256/8)) {
	local mask = 0;
	for (local y: util.range(8)) {
		if (valid_chars[x*8+y])
			mask = mask | (1 << y);
	}
	valid_bits[x] = mask;
}
for (local x: util.range(256/8)) {
	if ((x % 8) == 0) {
		print "\n    ",;
	}
	print "0x%.2I8x," % valid_bits[x],;
}
]]]*/
	0x00,0x00,0x00,0x00,0xfb,0x23,0xff,0x03,
	0xff,0xff,0xff,0xc7,0xff,0xff,0xff,0x6f,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
//[[[end]]]
};
#define dos8dot3_isvalid(ch) \
	(dos8dot3_valid[((u8)(ch)) / 8] & (1 << (((u8)(ch)) % 8)))



typedef struct ATTR_PACKED {
	u8      ffs_align;
	FatFile ffs_file;  /* The LFN characters are unaligned, so we manually align them here */
} FatFileStorage;

/* Even though the problem was fixed by `FatFileStorage' and forcing 2-byte alignment,
 * GCC still bickers about unaligned use of the LFN filename, even though that can't
 * happen anymore (just ignore the warning, maybe they'll fix this at some point...) */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Waddress-of-packed-member"

PRIVATE REF struct directory_entry *KCALL
Fat_ReadDirectory(struct directory_node *__restrict self,
                  pos_t *__restrict pentry_pos) {
	REF struct directory_entry *result;
	pos_t pos = *pentry_pos;
	ATTR_ALIGNED(2) FatFileStorage filestorage;
#ifdef __INTELLISENSE__
	FatFile &fatfile = filestorage.ffs_file;
#else
#define fatfile filestorage.ffs_file
#endif
continue_reading:
	Fat_VReadFromINode((struct inode *)self,
	                   (byte_t *)&fatfile,
	                   sizeof(FatFile),
	                   pos);
	if (fatfile.f_marker == MARKER_DIREND)
		return NULL; /* End of directory */
	if (fatfile.f_marker == MARKER_UNUSED) {
		/* Keep track of free directory entries. */
		if ((pos % sizeof(FatFile)) == 0)
			FatDirectory_AddFreeFile(self, (u32)(pos / sizeof(FatFile)));
		pos += sizeof(FatFile);
		goto continue_reading; /* Unused entry */
	}
	pos += sizeof(FatFile);
#if 1
#if 1
#define FILE_IS_LFN(x) ((x).f_attr == FAT_ATTR_LONGFILENAME)
#else
#define FILE_IS_LFN(x)                      \
	((x).f_attr == FAT_ATTR_LONGFILENAME && \
	 (x).lfn_clus == (le16)0 &&             \
	 (x).lfn_name_3[0] != (le16)0)
#endif
	if (FILE_IS_LFN(fatfile)) {
		char lfn_name[LFN_SEQNUM_MAXCOUNT * UNICODE_16TO8_MAXBUF(LFN_NAME)];
		u32 lfn_valid   = 0;
		pos_t lfn_start = pos - sizeof(FatFile);
		do {
			unsigned int index = (fatfile.lfn_seqnum & 0x1f) - 1;
			char *dst          = lfn_name + index * UNICODE_16TO8_MAXBUF(LFN_NAME);
			char *end          = dst + UNICODE_16TO8_MAXBUF(LFN_NAME);
			char16_t *textend;
			lfn_valid |= 1 << index;
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
			{
				unsigned int i;
				for (i = 0; i < LFN_NAME1; ++i)
					fatfile.lfn_name_1[i] = (le16)LESWAP16(fatfile.lfn_name_1[i]);
				for (i = 0; i < LFN_NAME2; ++i)
					fatfile.lfn_name_2[i] = (le16)LESWAP16(fatfile.lfn_name_2[i]);
				for (i = 0; i < LFN_NAME3; ++i)
					fatfile.lfn_name_3[i] = (le16)LESWAP16(fatfile.lfn_name_3[i]);
			}
#endif
			textend = (char16_t *)memchrw(fatfile.lfn_name_1, 0xffff, LFN_NAME1);
			if (textend) {
				dst = unicode_16to8(dst, (char16_t *)fatfile.lfn_name_1,
				                    textend - (char16_t *)fatfile.lfn_name_1);
			} else {
				dst     = unicode_16to8(dst, (char16_t *)fatfile.lfn_name_1, LFN_NAME1);
				textend = (char16_t *)memchrw(fatfile.lfn_name_2, 0xffff, LFN_NAME2);
				if (textend) {
					dst = unicode_16to8(dst, (char16_t *)fatfile.lfn_name_2,
					                    textend - (char16_t *)fatfile.lfn_name_2);
				} else {
					dst = unicode_16to8(dst, (char16_t *)fatfile.lfn_name_2, LFN_NAME2);
					dst = unicode_16to8(dst, (char16_t *)fatfile.lfn_name_3,
					                    memlenw(fatfile.lfn_name_3, 0xffff, LFN_NAME3));
				}
			}
			assert(dst <= end);
			memset(dst, 0, (size_t)(end - dst));
			for (;;) {
				Fat_VReadFromINode((struct inode *)self,
				                   (byte_t *)&fatfile,
				                   sizeof(FatFile),
				                   pos);
				pos += sizeof(FatFile);
				if (fatfile.f_marker != MARKER_UNUSED)
					break;
				if ((pos % sizeof(FatFile)) == 0)
					FatDirectory_AddFreeFile(self, (u32)(pos / sizeof(FatFile)) - 1);
			}
		} while (FILE_IS_LFN(fatfile));
		if unlikely(lfn_valid & (lfn_valid + 1)) {
			/* `lfn_valid' isn't a complete mask. (some part of the
			 * name might have been corrupted, or accidentally deleted?)
			 * Anyways: don't raise hell about this one and just delete
			 *          the string portions that were affected (that way
			 *          we at least preserve whatever portion of the
			 *          filename can still be recovered) */
			unsigned int index = 0;
			u32 mask;
			while ((mask = 1 << index, lfn_valid >= mask)) {
				if (lfn_valid & mask) {
					++index;
					continue;
				}
				memmove(lfn_name, lfn_name + UNICODE_16TO8_MAXBUF(LFN_NAME),
				        ((LFN_SEQNUM_MAXCOUNT - 1) - index) *
				        UNICODE_16TO8_MAXBUF(LFN_NAME));
				lfn_valid |= mask;
				lfn_valid >>= 1;
			}
		}
		/* Merge LFN filename segments. */
		{
			char *dst, *src, *end;
			dst = src = lfn_name;
			end = src + POPCOUNT(lfn_valid) * UNICODE_16TO8_MAXBUF(LFN_NAME);
			for (; src < end;) {
				size_t off = strnlen(src, (size_t)(end - src));
				if (dst != src)
					memcpy(dst, src, off * sizeof(char));
				dst += off;
				/* Skip ahead to the next segment. */
				off += (size_t)(src - lfn_name);
				off += UNICODE_16TO8_MAXBUF(LFN_NAME) - 1;
				off = off - (off % UNICODE_16TO8_MAXBUF(LFN_NAME));
				src = lfn_name + off;
			}
			/* Safety check: if the LFN filename ends up empty, use the 8.3 name instead! */
			if unlikely(dst == lfn_name)
				goto dos_8dot3;
			/* Allocate the directory entry. */
			result                     = directory_entry_alloc_s(lfn_name, dst - lfn_name);
			result->de_pos             = lfn_start;
			result->de_fsdata.de_start = pos - sizeof(FatFile);
			/* Use the absolute-ondisk position of the file's FatFile as INode number. */
			result->de_ino = (ino_t)Fat_GetAbsDiskPos(self, result->de_fsdata.de_start);
			/* Copy the dos 8.3 filename. */
			memcpy(FAT_DIRECTORY_ENTRY83(result),
			       fatfile.f_nameext, (8 + 3) * sizeof(char));
		}
		assertf(!memchr(result->de_name, 0, result->de_namelen),
		        "%$[hex]", (size_t)result->de_namelen, result->de_name);
	} else
#endif
	{
		char *iter, *dst, *end;
		unsigned int i;
		char orig_name[8 + 3];
		char entry_name[8 + 1 + 3 + 1];
		u16 name_length;
dos_8dot3:
		memcpy(orig_name, fatfile.f_nameext, (8 + 3) * sizeof(char));
		/* Fix lowercase filenames. */
		if (fatfile.f_ntflags & NTFLAG_LOWBASE) {
			for (i = 0; i < 8; ++i)
				fatfile.f_name[i] = tolower(fatfile.f_name[i]);
		}
		if (fatfile.f_ntflags & NTFLAG_LOWEXT) {
			for (i = 0; i < 3; ++i)
				fatfile.f_ext[i] = tolower(fatfile.f_ext[i]);
		}
		/* Deal with this one... */
		if unlikely(fatfile.f_marker == MARKER_IS0XE5)
			fatfile.f_name[0] = 0xe5;
		/* Convert the filename into a regular string. */
		dst  = entry_name;
		iter = fatfile.f_name, end = COMPILER_ENDOF(fatfile.f_name);
		while (iter != end && isspace(*iter))
			++iter;
		dst = (char *)mempcpy(dst, iter, (size_t)(end - iter));
		while (dst != entry_name && isspace(dst[-1]))
			--dst;
		*dst++ = '.';
		iter = fatfile.f_ext, end = COMPILER_ENDOF(fatfile.f_ext);
		while (iter != end && isspace(*iter))
			++iter;
		dst = (char *)mempcpy(dst, iter, (size_t)(end - iter));
		while (dst != entry_name && isspace(dst[-1]))
			--dst;
		if (dst != entry_name && dst[-1] == '.')
			--dst;
		*dst        = 0;
		name_length = (u16)(dst - entry_name);
		/* Make sure there aren't any illegal characters */
		for (i = 0; i < name_length; ++i) {
			char ch = entry_name[i];
			if (!dos8dot3_isvalid(ch) && ch != '.') {
				printk(KERN_ERR "[fat] Illegal character in filename %$q (skipping entry)\n",
				       (size_t)name_length, entry_name);
				goto continue_reading;
			}
		}
		/* Check for entries that we're supposed to skip over. */
		if (name_length <= 2 && entry_name[0] == '.') {
			/* The kernel implements these itself, so
			 * we don't actually want to emit them! */
			if (name_length == 1)
				goto continue_reading; /* Directory-self-reference. */
			if (entry_name[1] == '.')
				goto continue_reading; /* Directory-parent-reference. */
		}
		/* Create a short-directory entry. */
		result = directory_entry_alloc_s(entry_name, name_length);
		result->de_pos             = pos - sizeof(FatFile);
		result->de_fsdata.de_start = result->de_pos;
		/* Use the absolute on-disk position of the file's FatFile as INode number. */
		result->de_ino = (ino_t)Fat_GetAbsDiskPos(self, result->de_pos);
		/* Copy the unmodified, original DOS 8.3 filename. */
		memcpy(FAT_DIRECTORY_ENTRY83(result),
		       orig_name, (8 + 3) * sizeof(char));
		assertf(!memchr(result->de_name, 0, result->de_namelen),
		        "%$[hex]\n"
		        "orig_name:\n%$[hex]\n",
		        (size_t)result->de_namelen, result->de_name,
		        (8 + 3) * sizeof(char), orig_name);
	}
	/* Fill in the hash field. */
	result->de_type = (fatfile.f_attr & FAT_ATTR_DIRECTORY) ? DT_DIR : DT_REG;
	*pentry_pos     = pos;
	return result;
#undef fatfile
}

#pragma GCC diagnostic pop

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL Fat_FinalizeNode)(struct inode *__restrict self) {
	if (self->i_fsdata) {
		kfree(self->i_fsdata->i_directory.i_freev);
		kfree(self->i_fsdata->i_clusterv);
		kfree(self->i_fsdata);
	}
}

#define LINUX_TIME_START_YEAR  1970

#define SECONDS_PER_DAY        86400

#define DAYS2YEARS(n_days)   ((400*((n_days)+1))/146097)
#define YEARS2DAYS(n_years)  (((146097*(n_years))/400)/*-1*/) // rounding error?
#define ISLEAPYEAR(year) \
	(__builtin_constant_p(year)                                                   \
	 ? ((year) % 400 == 0 || ((year) % 100 != 0 && (year) % 4 == 0))              \
	 : XBLOCK({ __typeof__(year) const _year = (year);                            \
	            XRETURN _year % 400 == 0 || (_year % 100 != 0 && _year % 4 == 0); }))

PRIVATE time_t const time_monthstart_yday[2][13] = {
	{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
	{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
};

#define MONTH_STARTING_DAY_OF_YEAR(leap_year, month) \
	time_monthstart_yday[!!(leap_year)][month]


LOCAL time_t KCALL
Fat_DecodeFileDate(FatFileDate self) {
	time_t result;
	unsigned int year;
	year   = self.fd_year + 1980;
	result = YEARS2DAYS(year - LINUX_TIME_START_YEAR);
	result += MONTH_STARTING_DAY_OF_YEAR(ISLEAPYEAR(year), (self.fd_month - 1) % 12);
	result += self.fd_day - 1;
	return result * SECONDS_PER_DAY;
}
LOCAL FatFileDate KCALL
Fat_EncodeFileDate(time_t tmt) {
	FatFileDate result;
	unsigned int year;
	u8 i;
	time_t const *monthvec;
	tmt /= SECONDS_PER_DAY;
	tmt += YEARS2DAYS(LINUX_TIME_START_YEAR);
	year     = DAYS2YEARS(tmt);
	monthvec = time_monthstart_yday[ISLEAPYEAR(year)];
	tmt -= YEARS2DAYS(year);
	result.fd_year = year > 1980 ? year - 1980 : 0;
	/* Find the appropriate month. */
	for (i = 1; i < 12; ++i)
		if (monthvec[i] >= tmt)
			break;
	result.fd_month = i;
	result.fd_day   = (tmt - monthvec[i - 1]) + 1;
	return result;
}
LOCAL time_t KCALL Fat_DecodeFileTime(FatFileTime self) {
	return ((time_t)self.ft_hour * 60 * 60) +
	       ((time_t)self.ft_min * 60) +
	       ((time_t)self.ft_sec * 2);
}
LOCAL FatFileTime KCALL Fat_EncodeFileTime(time_t tmt) {
	FatFileTime result;
	result.ft_sec  = (tmt % 60) / 2;
	result.ft_min  = ((tmt / 60) % 60);
	result.ft_hour = ((tmt / (60 * 60)) % 24);
	return result;
}


PRIVATE NONNULL((1)) void(KCALL Fat_MaskINodeAttributes)(struct inode *__restrict self)
THROWS(E_FSERROR_UNSUPPORTED_OPERATION, ...) {
	FatSuperblock *super = (FatSuperblock *)self->i_super;
	{
		FatFileTime temp_time;
		FatFileDate temp_date;
		/* Truncate timestamps. */
		temp_date = Fat_EncodeFileDate(self->i_filemtime.tv_sec);
		temp_time = Fat_EncodeFileTime(self->i_filemtime.tv_sec);
		self->i_filemtime.tv_sec  = Fat_DecodeFileDate(temp_date);
		self->i_filemtime.tv_sec += Fat_DecodeFileTime(temp_time);
		self->i_filemtime.tv_nsec = 0;
		temp_date = Fat_EncodeFileDate(self->i_filemtime.tv_sec);
		temp_time = Fat_EncodeFileTime(self->i_filemtime.tv_sec);
		self->i_filemtime.tv_sec   = Fat_DecodeFileDate(temp_date);
		self->i_filemtime.tv_sec  += Fat_DecodeFileTime(temp_time);
		self->i_filemtime.tv_nsec -= self->i_filemtime.tv_nsec % (1000000000ul / 200ul);
	}
	/* Reset unix permissions. */
	if (!(super->f_features & FAT_FEATURE_ARB)) {
		/* Mask permissions other than write */
		self->i_filemode &= ~0555;
		self->i_filemode |= super->f_mode & 0555;
		/* Widen write permissions to all channels. */
		if (self->i_filemode & 0222)
			self->i_filemode |= 0222;
	}
	/* Reset owner and group. */
	if (super->f_features & FAT_FEATURE_UGID) {
		/* Truncate user/group IDs that are too large. */
		if (self->i_fileuid > (uid_t)0xff)
			self->i_fileuid = (uid_t)0;
		if (self->i_filegid > (gid_t)0xff)
			self->i_filegid = (gid_t)0;
		/* Without atime support, the last-access
		 * timestamp is always set to last-modified */
		self->i_fileatime = self->i_filemtime;
	} else {
		FatFileDate temp;
		/* Without uid/gid support, all files use a filesystem-global uid/gid pair */
		self->i_fileuid = super->f_uid;
		self->i_filegid = super->f_gid;
		/* Truncate last-accessed seconds to their valid range. */
		temp = Fat_EncodeFileDate(self->i_fileatime.tv_sec);
		self->i_fileatime.tv_sec  = Fat_DecodeFileDate(temp);
		self->i_fileatime.tv_nsec = 0;
	}
}

PRIVATE void KCALL
Fat_LoadINodeFromFatFile(struct inode *__restrict self,
                         FatFile const *__restrict file) {
	FatNode *data        = self->i_fsdata;
	FatSuperblock *super = (FatSuperblock *)self->i_super;
	/* file --> self */
	assert((data->i_clusterv != NULL) ==
	       (data->i_clustera != 0));
	if (!data->i_clustera) {
		data->i_clusterv = (FatClusterIndex *)kmalloc(2 * sizeof(FatClusterIndex),
		                                              FS_GFP);
		data->i_clustera = 2;
	}
	/* Setup the initial cluster. */
	data->i_clusterc    = 1;
	data->i_clusterv[0] = LESWAP16(file->f_clusterlo);
	memcpy(&data->i_file, &file->f_attr, sizeof(data->i_file));
	self->i_filesize = (pos_t)LESWAP32(file->f_size);

	self->i_filemode &= S_IFMT;
	if (super->f_features & FAT_FEATURE_ARB) {
		u16 arb = LESWAP16(file->f_arb);
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
		self->i_filemode |= unix_perm;
		data->i_file.f_arb = arb;
	} else {
		assert(!(super->f_mode & ~0777));
		/* 32-bit clusters */
		data->i_clusterv[0] |= (u32)LESWAP16(file->f_clusterhi) << 16;
		self->i_filemode |= 0222 | (super->f_mode & 0555);
	}
	/* Implement the read-only attribute. */
	if (file->f_attr & FAT_ATTR_READONLY)
		self->i_filemode &= ~0222;

	/* Convert timestamps. */
	self->i_filemtime.tv_sec  = Fat_DecodeFileDate(file->f_mtime.fc_date);
	self->i_filemtime.tv_sec += Fat_DecodeFileTime(file->f_mtime.fc_time);
	self->i_filemtime.tv_nsec = 0;
	self->i_filectime.tv_sec  = Fat_DecodeFileDate(file->f_ctime.fc_date);
	self->i_filectime.tv_sec += Fat_DecodeFileTime(file->f_ctime.fc_time);
	self->i_filectime.tv_nsec = file->f_ctime.fc_sectenth * (1000000000ul / 200ul);

	if (super->f_features & FAT_FEATURE_UGID) {
		/* In-built user/group ID support */
		self->i_fileuid = (uid_t)file->f_uid;
		self->i_filegid = (gid_t)file->f_gid;
		/* Re-use the last-modified timestamp for access time. */
		self->i_fileatime = self->i_filemtime;
	} else {
		self->i_fileuid = super->f_uid;
		self->i_filegid = super->f_gid;
		self->i_fileatime.tv_sec  = Fat_DecodeFileDate(file->f_atime);
		self->i_fileatime.tv_nsec = 0;
	}

}

PRIVATE void KCALL
Fat_SaveINodeToFatFile(struct inode const *__restrict self,
                       FatFile *__restrict file) {
	FatSuperblock *super = (FatSuperblock *)self->i_super;
	FatNode *data = self->i_fsdata;
	u32 cluster;
	/* self --> file */
	assert((data->i_clusterv != NULL) ==
	       (data->i_clustera != 0));
	if (!data->i_clusterc) {
		cluster = ((FatSuperblock *)self->i_super)->f_cluster_eof_marker;
	} else {
		cluster = data->i_clusterv[0];
	}
	/* Copy basic file data. */
	memcpy(&file->f_attr, &data->i_file, sizeof(data->i_file));
	file->f_clusterlo = (le16)LESWAP16(cluster & 0xffff);
	if (super->f_features & FAT_FEATURE_ARB) {
		u16 arb = data->i_file.f_arb;
		mode_t unix_perm = self->i_filemode;
		arb &= ~(FAT_ARB_NO_OX | FAT_ARB_NO_OW | FAT_ARB_NO_OR |
		         FAT_ARB_NO_GX | FAT_ARB_NO_GW | FAT_ARB_NO_GR |
		         FAT_ARB_NO_WX | FAT_ARB_NO_WW | FAT_ARB_NO_WR);
		/* Use the ARB to implement unix file permissions. */
		if (!(unix_perm & S_IXUSR))
			arb |= FAT_ARB_NO_OX; /* Disable: Execute by owner */
		if (!(unix_perm & S_IWUSR))
			arb |= FAT_ARB_NO_OW; /* Disable: Write by owner */
		if (!(unix_perm & S_IRUSR))
			arb |= FAT_ARB_NO_OR; /* Disable: Read by owner */

		if (!(unix_perm & S_IXGRP))
			arb |= FAT_ARB_NO_GX; /* Disable: Execute by group */
		if (!(unix_perm & S_IWGRP))
			arb |= FAT_ARB_NO_GW; /* Disable: Write by group */
		if (!(unix_perm & S_IRGRP))
			arb |= FAT_ARB_NO_GR; /* Disable: Read by group */

		if (!(unix_perm & S_IXOTH))
			arb |= FAT_ARB_NO_WX; /* Disable: Execute by world */
		if (!(unix_perm & S_IWOTH))
			arb |= FAT_ARB_NO_WW; /* Disable: Write by world */
		if (!(unix_perm & S_IROTH))
			arb |= FAT_ARB_NO_WR; /* Disable: Read by world */
		if (!(self->i_filemode & 0222)) {
			/* Preserve ARB flags for write permissions if those can
			 * already be represented through use of the READONLY flag. */
			arb &= ~(FAT_ARB_NO_OW | FAT_ARB_NO_GW | FAT_ARB_NO_WW);
			arb |= data->i_file.f_arb & (FAT_ARB_NO_OW | FAT_ARB_NO_GW | FAT_ARB_NO_WW);
		}
		file->f_arb = (le16)LESWAP16(arb);
	} else {
		/* 32-bit clusters */
		file->f_clusterhi = (le16)LESWAP16((u16)(cluster >> 16));
	}
	file->f_size = (le32)LESWAP32((u32)self->i_filesize);
	/* Implement the read-only attribute. */
	if (!(self->i_filemode & 0222))
		file->f_attr |= FAT_ATTR_READONLY;

	if (super->f_features & FAT_FEATURE_UGID) {
		/* UID/GID support */
		file->f_uid = (u8)self->i_fileuid;
		file->f_gid = (u8)self->i_filegid;
	} else {
		/* Last-access timestamp support */
		file->f_atime = Fat_EncodeFileDate(self->i_fileatime.tv_sec);
	}

	/* Convert timestamps. */
	file->f_mtime.fc_date     = Fat_EncodeFileDate(self->i_filemtime.tv_sec);
	file->f_mtime.fc_time     = Fat_EncodeFileTime(self->i_filemtime.tv_sec);
	file->f_ctime.fc_date     = Fat_EncodeFileDate(self->i_filectime.tv_sec);
	file->f_ctime.fc_time     = Fat_EncodeFileTime(self->i_filectime.tv_sec);
	file->f_ctime.fc_sectenth = (u8)(self->i_filectime.tv_nsec / (1000000000ul / 200ul));
	/* Set the ARCHIVE flag to indicate a file that has been modified. */
	file->f_attr |= FAT_ATTR_ARCHIVE;
}

PRIVATE NONNULL((1)) void KCALL
Fat32_LoadINodeAttributes(struct inode *__restrict self)
		THROWS(E_IOERROR, ...) {
	byte_t buf[sizeof(FatFile) - offsetof(FatFile, f_attr)];
	/* Read the FAT-FILE from disk. */
	block_device_read(self->i_super->s_device, buf, sizeof(buf),
	                  (pos_t)self->i_fileino + offsetof(FatFile, f_attr));
	/* Load Node data from the file. */
	Fat_LoadINodeFromFatFile(self, COMPILER_CONTAINER_OF((u8 *)buf, FatFile, f_attr));
}
PRIVATE NONNULL((1)) void KCALL
Fat32_SaveINodeAttributes(struct inode *__restrict self)
		THROWS(E_IOERROR, ...) {
	byte_t buf[sizeof(FatFile) - offsetof(FatFile, f_attr)];
	/* Save Node data to a fat-file. */
	Fat_SaveINodeToFatFile(self, COMPILER_CONTAINER_OF((u8 *)buf, FatFile, f_attr));
	/* Write the FAT-FILE to disk. */
	block_device_write(self->i_super->s_device, buf, sizeof(buf),
	                   (pos_t)self->i_fileino + offsetof(FatFile, f_attr));
}
PRIVATE NONNULL((1)) void KCALL
Fat16_LoadRootDirectoryEntryINodeAttributes(struct inode *__restrict self)
		THROWS(E_IOERROR, ...) {
	byte_t buf[sizeof(FatFile) - offsetof(FatFile, f_attr)];
	/* Read the FAT-FILE from disk. */
	block_device_read(self->i_super->s_device, buf, sizeof(buf),
	                  (pos_t)self->i_fileino + offsetof(FatFile, f_attr));
	/* Load Node data from the file. */
	Fat_LoadINodeFromFatFile(self, COMPILER_CONTAINER_OF((u8 *)buf, FatFile, f_attr));
}
PRIVATE NONNULL((1)) void KCALL
Fat16_SaveRootDirectoryEntryINodeAttributes(struct inode *__restrict self)
		THROWS(E_IOERROR, ...) {
	byte_t buf[sizeof(FatFile) - offsetof(FatFile, f_attr)];
	/* Save Node data to a fat-file. */
	Fat_SaveINodeToFatFile(self, COMPILER_CONTAINER_OF((u8 *)buf, FatFile, f_attr));
	/* Write the FAT-FILE to disk. */
	block_device_write(self->i_super->s_device, buf, sizeof(buf),
	                   (pos_t)self->i_fileino + offsetof(FatFile, f_attr));
}

PRIVATE NONNULL((1)) intptr_t KCALL
Fat_PathConf(struct inode *__restrict self, unsigned int name)
		THROWS(...) {
	intptr_t result;
	//FatSuperblock *super;
	//super = (FatSuperblock *)self->i_super;
	switch (name) {

	case _PC_NAME_MAX:
		result = LFN_SEQNUM_MAXCOUNT * LFN_NAME;
		break;

	default:
		result = INODE_PATHCONF_UNDEDEFINED;
		break;
	}
	return result;
}

PRIVATE NONNULL((1)) syscall_slong_t KCALL
Fat_Ioctl(struct inode *__restrict self, syscall_ulong_t cmd,
          USER UNCHECKED void *arg, iomode_t mode)
		THROWS(...) {
	switch (cmd) {

#if 0 /* TODO */
	case VFAT_IOCTL_READDIR_BOTH:
	case VFAT_IOCTL_READDIR_SHORT:
#endif

	case FAT_IOCTL_GET_ATTRIBUTES:
		validate_writable(arg, sizeof(u32));
		inode_loadattr(self);
		*(u32 *)arg = self->i_fsdata->i_file.f_attr;
		break;

	case FAT_IOCTL_SET_ATTRIBUTES: {
		u32 value;
		validate_readable(arg, sizeof(u32));
		inode_loadattr(self);
		COMPILER_READ_BARRIER();
		value = *(u32 *)arg;
		COMPILER_READ_BARRIER();
		if unlikely(value & ~0xff)
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_GENERIC, value);
		if unlikely(!!(value & FAT_ATTR_DIRECTORY) != !!INODE_ISDIR(self))
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_GENERIC, value);
		ATOMIC_WRITE(self->i_fsdata->i_file.f_attr, (u8)value);
		inode_changedattr(self);
	}	break;

	case FAT_IOCTL_GET_VOLUME_ID:
		validate_writable(arg, sizeof(u32));
		*(u32 *)arg = ((FatSuperblock *)self->i_super)->f_volid;
		break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
		      cmd);
		break;
	}
	return 0;
}



PRIVATE void KCALL
Fat_DoTruncateINode(struct inode *__restrict self, size_t new_cluster_count) {
	FatNode *node      = self->i_fsdata;
	FatSuperblock *fat = (FatSuperblock *)self->i_super;
	FatClusterIndex delete_start;
	delete_start = Fat_GetFileCluster(self, new_cluster_count,
	                                  FAT_GETCLUSTER_MODE_FNORMAL);
	if (delete_start >= fat->f_cluster_eof)
		return; /* Already truncated. */
	if (new_cluster_count != 0) {
		/* Cut off the previous cluster. */
		Fat_SetFatIndirection(fat,
		                      Fat_GetFileCluster(self, new_cluster_count - 1,
		                                         FAT_GETCLUSTER_MODE_FNORMAL),
		                      fat->f_cluster_eof_marker);
	} else {
		/* Upon success, the caller will mark the file as having changed.
		 * Unless what'll happen next is the file being removed from its
		 * containing directory, the updated index-0 cluster will be
		 * written to disk the next time `Fat_SaveINodeToFatFile()' is
		 * called, which is then invoked from `inode_sync()' */
	}
	/* Now delete the chain of clusters that just got truncated. */
	Fat_DeleteClusterChain(fat, delete_start);
	/* Mark the (now) latest cluster as an EOF cluster. */
	node->i_clusterv[new_cluster_count] = fat->f_cluster_eof_marker;
	node->i_clusterc                    = new_cluster_count + 1;
}

PRIVATE void KCALL
Fat_TruncateINode(struct inode *__restrict self, pos_t new_size) {
	if (new_size > self->i_filesize)
		return; /* File extending is done lazily. */
	Fat_DoTruncateINode(self,
	                    (size_t)CEILDIV(new_size,
	                                    ((FatSuperblock *)self->i_super)->f_clustersize));
}


PRIVATE NONNULL((1, 2, 3)) void KCALL
Fat_UnlinkFileFromParentDirectory(struct directory_node *__restrict containing_directory,
                                  struct directory_entry *__restrict containing_entry,
                                  struct inode *__restrict node_to_unlink)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION,
		       E_FSERROR_READONLY, E_IOERROR_READONLY,
		       E_IOERROR, ...) {
	pos_t min, max, i;
	assert(node_to_unlink->i_filesize == 0);
	assert(node_to_unlink->i_filenlink == (nlink_t)1);
	min = containing_entry->de_pos;
	max = containing_entry->de_fsdata.de_start;
	for (i = min; i <= max; i += sizeof(FatFile)) {
		/* Mark all affected entries as now being unused. */
		u8 marker = MARKER_UNUSED;
		Fat_VWriteToINode(containing_directory, &marker, 1, i);
	}
	/* Remember the newly freed entries. */
	FatDirectory_AddFreeRange(containing_directory,
	                          (u32)(min / sizeof(FatFile)),
	                          (u32)(((max - min) / sizeof(FatFile)) + 1));
	/* Check if the directory can now be truncated. */
	FatDirectory_CheckTruncation(containing_directory);
	node_to_unlink->i_filenlink = 0;
}

PRIVATE NONNULL((1, 2, 3)) void KCALL
Fat_RemoveDirectoryFromParentDirectory(struct directory_node *__restrict containing_directory,
                                       struct directory_entry *__restrict containing_entry,
                                       struct directory_node *__restrict node_to_unlink)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION,
		       E_FSERROR_READONLY, E_IOERROR_READONLY,
		       E_IOERROR, ...) {
	assert(node_to_unlink->d_parent == containing_directory);
	/* Make sure that all data clusters of the directory to remove have been deleted.
	 * NOTE: The caller already guaranties that it won't contain any ~actual~ entries,
	 *       however we know that it does actually still contain its self-entry, as
	 *       well as the parent-entry, meaning that we do actually have to ensure that
	 *       those get deallocated as well.
	 *       And even if it wasn't for them, the directory may still contain some unused
	 *       file entries that were left behind from when it was still in use. */
	Fat_DoTruncateINode(node_to_unlink, 0);
	/* The rest is the same as for regular files... */
	Fat_UnlinkFileFromParentDirectory(containing_directory,
	                                  containing_entry,
	                                  node_to_unlink);
}




LOCAL WUNUSED u8
NOTHROW(KCALL lfn_checksum)(char const *__restrict dos83_name) {
	unsigned int i;
	u8 result = 0;
	for (i = 0; i < 11; ++i)
		result = ((result & 1) << 7) + (result >> 1) + *dos83_name++;
	return result;
}


/* Generate the sequence of FAT file-entries required to represent the
 * given `new_node', using `target_dirent' as name in a FAT directory.
 * When LFN entires are required, those are generated as-needed, with
 * the final entry then describing a regular DOS 8.3 filename.
 * NOTE: Of the trailing 8.3 file entry, the caller must still initialize
 *       the `f_clusterhi', `f_clusterlo' and `f_size' fields!
 * @param: pbuffer_length: [in|out] The amount of allocated space for `FatFile'
 *                                  structures in `buffer' (bytes / sizeof(FatFile))
 *                                  Upon success, the amount of used entires is stored here.
 *                                  NOTE: Must be non-zero on entry!
 * @param: cookie: A cookie used to disambiguate the 8.3 filename
 * @param: inhert_heap_buffer: When true, inherit `buffer' as a kmalloc() pointer
 *                             that will be inherited upon success.
 * @return: * : A pointer to the first of `*pbuffer_length' FAT file-entries.
 *              When `buffer' is re-returned, `inhert_heap_buffer' is ignored.
 *              Otherwise, the returned buffer is allocated on the heap using
 *              kmalloc(), and must be freed by the caller. */
PRIVATE NOBLOCK ATTR_RETNONNULL FatFile *KCALL
Fat_GenerateFileEntries(FatFile *__restrict buffer,
                        u32 *__restrict pbuffer_length,
                        struct directory_entry *__restrict target_dirent,
                        struct inode *__restrict new_node, uintptr_t cookie,
                        bool inhert_heap_buffer) THROWS(E_BADALLOC) {
	FatFile dos83;
	char *name, *extstart;
	u16 namesize, extsize, basesize;
	bool need_lfn;
	assert(*pbuffer_length != 0);
	memset(dos83.f_nameext, ' ', sizeof(dos83.f_nameext));
	dos83.f_ntflags = NTFLAG_NONE;
	dos83.f_attr    = FAT_ATTR_ARCHIVE;
	if (INODE_ISDIR(new_node))
		dos83.f_attr |= FAT_ATTR_DIRECTORY;
	if (target_dirent->de_name[0] == '.')
		dos83.f_attr |= FAT_ATTR_HIDDEN;
	if (!(new_node->i_filemode & 0222))
		dos83.f_attr |= FAT_ATTR_READONLY;

	/* Convert timestamps. */
	dos83.f_atime             = Fat_EncodeFileDate(new_node->i_fileatime.tv_sec);
	dos83.f_mtime.fc_date     = Fat_EncodeFileDate(new_node->i_filemtime.tv_sec);
	dos83.f_mtime.fc_time     = Fat_EncodeFileTime(new_node->i_filemtime.tv_sec);
	dos83.f_ctime.fc_date     = Fat_EncodeFileDate(new_node->i_filectime.tv_sec);
	dos83.f_ctime.fc_time     = Fat_EncodeFileTime(new_node->i_filectime.tv_sec);
	dos83.f_ctime.fc_sectenth = (u8)(new_node->i_filectime.tv_nsec / (1000000000ul / 200ul));
//	dos83.f_clusterlo = ...; /* Initialized by the caller */
//	dos83.f_clusterhi = ...; /* Initialized by the caller */
//	dos83.f_size      = ...; /* Initialized by the caller */

	/* Strip leading+terminating dots & space. */
	name     = target_dirent->de_name;
	namesize = target_dirent->de_namelen;
	while (namesize && (FAT_ISSPACE(*name) || *name == '.'))
		++name, --namesize;
	while (namesize && (FAT_ISSPACE(name[namesize - 1])))
		--namesize;
	extstart = name + namesize;
	while (extstart > name && extstart[-1] != '.')
		--extstart;
	if (extstart == name) {
		extstart = name + namesize; /* No extension */
		extsize  = 0;
		basesize = namesize;
	} else {
		basesize = (size_t)(extstart - name) - 1;
		extsize  = (namesize - basesize) - 1;
	}

	/* Strip space characters before the extension and after the name. */
	while (namesize && FAT_ISSPACE(name[namesize - 1]))
		++name, --namesize;
	while (extsize && FAT_ISSPACE(*extstart))
		++extstart, --extsize;

	/* We already know that an LFN entry is needed if we had to do adjustments. */
	need_lfn = (name != target_dirent->de_name ||
	            (extsize ? (extstart != name + basesize + 1) ||
	                       (basesize + 1 + extsize != target_dirent->de_namelen)
	                     : (basesize != target_dirent->de_namelen)));

	/* Generate the extension */
	if (extsize) {
		char *dst, *iter, *end;
		u32 ch;
		dst = dos83.f_nameext + 8;
		end = (iter = extstart) + MIN(extsize, 3);
		dos83.f_ntflags |= NTFLAG_LOWEXT;
		while (iter < end) {
			ch = unicode_readutf8_n((char const **)&iter, end);
			if unlikely(ch > 0xff) {
				*dst++   = '~';
				need_lfn = true;
			} else {
				if (islower((u8)ch)) {
					if (!(dos83.f_ntflags & NTFLAG_LOWEXT))
						need_lfn = true;
					ch = toupper((u8)ch);
				} else {
					if ((dos83.f_ntflags & NTFLAG_LOWEXT) && iter != extstart)
						need_lfn = true;
					dos83.f_ntflags &= ~(NTFLAG_LOWEXT);
				}
				if unlikely(!dos8dot3_isvalid((u8)ch)) {
					ch       = '~';
					need_lfn = true;
				}
				*dst++ = (u8)ch;
			}
		}
	}

	/* Confirm that the name and extension fit DOS8.3 */
	if (basesize <= 8 && extsize <= 3 && !need_lfn) {
		char *iter, *end, *dst;
		u32 ch;
		/* We can generate a (possibly mixed-case) 8.3-compatible filename */
		end = (iter = name) + basesize, dst = dos83.f_name;
		dos83.f_ntflags |= NTFLAG_LOWBASE;
		while (iter < end) {
			ch = unicode_readutf8_n((char const **)&iter, end);
			if unlikely(ch > 0xff) {
				/* Unicode character. */
				*dst++   = '~';
				need_lfn = true;
			} else {
				if (islower((u8)ch)) {
					if (!(dos83.f_ntflags & NTFLAG_LOWBASE))
						need_lfn = true;
					ch = toupper((u8)ch);
				} else {
					if (dos83.f_ntflags & NTFLAG_LOWBASE && iter != extstart)
						need_lfn = true;
					dos83.f_ntflags &= ~NTFLAG_LOWBASE;
				}
				if unlikely(!dos8dot3_isvalid((u8)ch)) {
					ch = '~';
					need_lfn = true;
				}
				*dst++ = (u8)ch;
			}
		}
		/* Fix 0xe5 --> 0x05 */
		if (((u8 *)dos83.f_name)[0] == 0xe5)
			((u8 *)dos83.f_name)[0] = 0x05;
		if (!need_lfn) {
			/* We can use an 8.3 entry! */
			*pbuffer_length = 1;
			memcpy(buffer, &dos83, sizeof(dos83));
			return buffer;
		}
	}
	/* Need to use LFN entires! */
#define FAT_8DOT3_MAX_DISAMBIGUATION (0xffff * 9)
	{
		unsigned int matchsize;
		unsigned int retry_hex, retry_dig;
		char *dst, *iter, *end, ch;
		dos83.f_ntflags = NTFLAG_NONE;
		/* Must generate a long filename, also taking
		 * the value of 'retry' into consideration.
		 * Now for the hard part: The filename itself... */
		retry_hex = (cookie / 9);
		retry_dig = (cookie % 9);

		/* The first 2 short characters always match the
		 * first 2 characters of the original base (in uppercase).
		 * If no hex-range retries are needed, the first 6 match. */
		matchsize = retry_hex ? 2 : 6;
		if (matchsize > basesize)
			matchsize = basesize;
		end = (iter = name) + matchsize, dst = dos83.f_nameext;
		while (iter < end) {
			ch = unicode_readutf8_n((char const **)&iter, end);
			if (ch > 0xff)
				*dst++ = '~';
			else {
				ch     = toupper((u8)ch);
				*dst++ = (char)(dos8dot3_isvalid((u8)ch) ? (u8)ch : (u8)'~');
			}
		}
		if (retry_hex) {
			PRIVATE char const xch[16] = { '0', '1', '2', '3', '4', '5', '6', '7',
				                           '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
			/* Following the matching characters are 4 hex-chars
			 * whenever more than 9 retry attempts have failed
			 * >> This multiplies the amount of available names by 0xffff */
			*dst++ = xch[(retry_hex & 0xf000) >> 12];
			*dst++ = xch[(retry_hex & 0x0f00) >> 8];
			*dst++ = xch[(retry_hex & 0x00f0) >> 4];
			*dst++ = xch[(retry_hex & 0x000f)];
		}
		assert(dst <= dos83.f_nameext + 6);
		/* Following the shared name and the hex part is always a tilde '~' */
		*dst++ = '~';
		/* The last character then, is the non-hex digit (1..9) */
		*dst = '1' + retry_dig;
		/* Fix 0xe5 --> 0x05 */
		if (((u8 *)dos83.f_nameext)[0] == 0xe5)
			((u8 *)dos83.f_nameext)[0] = 0x05;
	}
	{
		char16_t lfn_name[LFN_SEQNUM_MAXCOUNT * LFN_NAME + UNICODE_UTF16_CURLEN - 1];
		char16_t *dst = lfn_name;
		char *iter, *end;
		size_t lfn_length;
		u32 req_files, avail_files, i;
		u8 checksum;
		/* Generate the LFN filename */
		end = (iter = target_dirent->de_name) + target_dirent->de_namelen;
		while (iter < end) {
			u32 ch;
			if unlikely(dst >= lfn_name + LFN_SEQNUM_MAXCOUNT * LFN_NAME)
				THROW(E_FSERROR_ILLEGAL_PATH);
			ch  = unicode_readutf8_n((char const **)&iter, end);
			dst = unicode_writeutf16_chk(dst, ch);
			if unlikely(!dst)
				THROW(E_FSERROR_ILLEGAL_PATH);
		}
		lfn_length = (size_t)(dst - lfn_name);
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		for (i = 0; i < lfn_length; ++i)
			lfn_name[i] = (char16_t)LESWAP16(lfn_name[i]);
#endif
		assert(lfn_length <= LFN_SEQNUM_MAXCOUNT * LFN_NAME);
		req_files = (u32)((lfn_length + (LFN_NAME - 1)) / LFN_NAME) + 1;
		assert((req_files - 1) <= LFN_SEQNUM_MAXCOUNT);
		/* Fill unused characters of the last file with `0xFFFF' */
		memsetw(&lfn_name[lfn_length], 0xffff,
		        (req_files * LFN_NAME) - lfn_length);
		/* Now to generate the LFN entires! */
		avail_files = *pbuffer_length;
		if (inhert_heap_buffer)
			avail_files = (u32)(kmalloc_usable_size(buffer) / sizeof(FatFile));
		assert(avail_files != 0);
		if (req_files > avail_files) {
			/* Need more files! */
			buffer = inhert_heap_buffer
			         ? (FatFile *)krealloc(buffer, req_files * sizeof(FatFile), FS_GFP)
			         : (FatFile *)kmalloc(req_files * sizeof(FatFile), FS_GFP);
		}
		*pbuffer_length = req_files;
		--req_files;

		/* Calculate the checksum for the 8.3 filename. */
		checksum = lfn_checksum(dos83.f_nameext);

		/* Fill in the LFN file entries. */
		for (i = 0; i < req_files; ++i) {
			FatFile *entry = &buffer[i];
			/* LFN sequence entries are written in reverse order (for whatever reason...) */
			size_t seqnum  = (req_files - 1) - i;
			size_t offset  = seqnum * LFN_NAME;
			memcpyw(entry->lfn_name_1, &lfn_name[offset + 0], LFN_NAME1);
			memcpyw(entry->lfn_name_2, &lfn_name[offset + LFN_NAME1], LFN_NAME2);
			memcpyw(entry->lfn_name_3, &lfn_name[offset + LFN_NAME1 + LFN_NAME2], LFN_NAME3);
			entry->lfn_seqnum = LFN_SEQNUM_MIN + (u8)seqnum;
			entry->lfn_attr   = FAT_ATTR_LONGFILENAME;
			entry->lfn_type   = 0;
			entry->lfn_clus   = (le16)0;
			entry->lfn_csum   = checksum;
		}
		/* Set the first-physical-last-logical bit for the first LFN sequence entry. */
		buffer[0].lfn_seqnum |= 0x40;

		/* Copy the 8.3 file entry. */
		memcpy(&buffer[req_files], &dos83, sizeof(FatFile));
	}
	return buffer;
}


LOCAL NOBLOCK bool
NOTHROW(KCALL directory_has_dos83)(struct directory_node *__restrict self,
                                   char *__restrict name) {
	size_t i;
	struct directory_entry *entry;
	for (i = 0; i <= self->d_mask; ++i) {
		entry = self->d_map[i];
		for (; entry; entry = entry->de_next) {
			if (memcmp(entry->de_fsdata.de_data, name, 8 + 3) == 0)
				return true;
		}
	}
	return false;
}

/* Same as `Fat_GenerateFileEntries()', but the givne `buffer' must be allocated
 * on the stack, and this function will automatically re-try when an 8.3 variant
 * of a long filename already exists. */
PRIVATE NOBLOCK ATTR_RETNONNULL FatFile *
(KCALL Fat_GenerateFileEntriesAuto)(struct directory_node *__restrict target_directory,
                                    FatFile *__restrict buffer,
                                    u32 *__restrict pbuffer_length,
                                    struct directory_entry *__restrict target_dirent,
                                    struct inode *__restrict new_node)
		THROWS(E_BADALLOC) {
	FatFile *result  = buffer;
	uintptr_t cookie = 0;
again:
	result = Fat_GenerateFileEntries(result,
	                                 pbuffer_length,
	                                 target_dirent,
	                                 new_node,
	                                 cookie,
	                                 result != buffer);
	TRY {
		/* Make sure not to re-use 8.3 file names. */
		if (*pbuffer_length > 1 &&
		    directory_has_dos83(target_directory,
		                        result[*pbuffer_length - 1].f_nameext)) {
			if unlikely(cookie >= FAT_8DOT3_MAX_DISAMBIGUATION) {
				/* TODO: Throw some kind of error. */
			}
			++cookie;
			goto again;
		}
	} EXCEPT {
		if (result != buffer)
			kfree(result);
		RETHROW();
	}
	return result;
}


PRIVATE FatFile const sential_fatfile = { 0 };


PRIVATE NONNULL((1, 2, 3)) void KCALL
Fat_AddFileToDirectory(struct directory_node *__restrict target_directory,
                       struct directory_entry *__restrict target_dirent,
                       struct inode *__restrict new_node)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ILLEGAL_PATH,
		       E_FSERROR_DISK_FULL, E_FSERROR_READONLY,
		       E_IOERROR_BADBOUNDS, E_IOERROR_READONLY,
		       E_IOERROR, ...) {
	FatFile buffer[4], *files;
	u32 target_index;
	pos_t target_position;
	u32 file_count = COMPILER_LENOF(buffer);
	bool is_directory_end;
	files = Fat_GenerateFileEntriesAuto(target_directory,
	                                    buffer,
	                                    &file_count,
	                                    target_dirent,
	                                    new_node);
	TRY {
		u32 first_cluster;
		struct inode_data *data;
		data = new_node->i_fsdata;
		assert(data);
		first_cluster = data->i_clusterc != 0
		                ? data->i_clusterv[0]
		                : ((FatSuperblock *)target_directory->i_super)->f_cluster_eof_marker;
		files[file_count - 1].f_clusterlo = (le16)LESWAP16((u16)first_cluster);
		files[file_count - 1].f_clusterhi = (le16)LESWAP16((u16)(first_cluster >> 16));
		files[file_count - 1].f_size      = (le32)0;
		/* Allocate space within the target directory. */
		target_index = FatDirectory_AllocateFreeRange(target_directory,
		                                              file_count,
		                                              &is_directory_end);
		target_position = (pos_t)target_index * sizeof(FatFile);
		TRY {
			/* Copy the file descriptors into the directory. */
			if (is_directory_end) {
				/* Write a new end-of-directory entry.
				 * NOTE: Do this before we write the actual new file to prevent
				 *       corrupting the end-of-directory marker if an error
				 *       occurs while we're writing the new files. */
				Fat_VWriteToINode(target_directory,
				                  (byte_t *)&sential_fatfile,
				                  sizeof(sential_fatfile),
				                  target_position + file_count * sizeof(FatFile));
			}
			Fat_VWriteToINode(target_directory,
			                  (byte_t *)files,
			                  file_count * sizeof(FatFile),
			                  target_position);
		} EXCEPT {
			if (!is_directory_end)
				FatDirectory_AddFreeRange(target_directory, target_index, file_count);
			RETHROW();
		}
		/* Fill in the position information for the new directory entry. */
		target_dirent->de_pos             = (pos_t)target_position;
		target_dirent->de_fsdata.de_start = (pos_t)target_position + (file_count - 1) * sizeof(FatFile);
		/* Fill in INode information for the location of the FatFile */
		target_dirent->de_ino = (ino_t)Fat_GetAbsDiskPos(target_directory,
		                                                 target_dirent->de_fsdata.de_start);
		new_node->i_fileino = target_dirent->de_ino;
		/* Fill in file attribute persistence data. */
		data->i_file.f_attr    = files[file_count - 1].f_attr;
		data->i_file.f_ntflags = files[file_count - 1].f_ntflags;
		data->i_file.f_arb     = 0;
	} EXCEPT {
		if (files != buffer)
			kfree(files);
		RETHROW();
	}
	if (files != buffer)
		kfree(files);
}


PRIVATE NONNULL((1, 2, 3)) void KCALL
Fat_CreateFileInDirectory(struct directory_node *__restrict target_directory,
                          struct directory_entry *__restrict target_dirent,
                          struct regular_node *__restrict new_node)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ILLEGAL_PATH,
		       E_FSERROR_DISK_FULL, E_FSERROR_READONLY,
		       E_IOERROR_BADBOUNDS, E_IOERROR_READONLY,
		       E_IOERROR, ...) {
	struct inode_data *node;
	new_node->i_type = &Fat_FileNodeOperators;
	if (target_directory == target_directory->i_super &&
	    ((FatSuperblock *)target_directory)->f_type != FAT32)
		new_node->i_type = &Fat16_RootDirectoryFileEntryNodeOperators;
	/* Allocate FS-specific INode data for the new file. */
	node = (struct inode_data *)kmalloc(sizeof(struct inode_data),
	                                    FS_GFP | GFP_CALLOC);
	TRY {
		new_node->i_fsdata  = node;
		node->i_clusterv    = (FatClusterIndex *)kmalloc(2 * sizeof(FatClusterIndex), FS_GFP);
		node->i_clustera    = 2;
		node->i_clusterc    = 1;
		node->i_clusterv[0] = ((FatSuperblock *)target_directory->i_super)->f_cluster_eof_marker;
		/* Add the file to its parent's directory. */
		Fat_AddFileToDirectory(target_directory, target_dirent, new_node);
	} EXCEPT {
		kfree(new_node->i_fsdata->i_clusterv);
		kfree(new_node->i_fsdata);
		RETHROW();
	}
	new_node->i_filenlink = (nlink_t)1;
}


PRIVATE FatFile const new_directory_pattern[3] = {
#ifndef __INTELLISENSE__
	[0] = { /* '.' */
		{{{{{.f_name    = { '.', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }},
			.f_ext     = { ' ', ' ', ' ' }}},
			.f_attr    = FAT_ATTR_DIRECTORY,
			.f_ntflags = NTFLAG_NONE }}},
	[1] = { /* '..' */
		{{{{{.f_name    = { '.', '.', ' ', ' ', ' ', ' ', ' ', ' ' }},
			.f_ext      = { ' ', ' ', ' ' }}},
			.f_attr     = FAT_ATTR_DIRECTORY,
			.f_ntflags  = NTFLAG_NONE }}},
	[2] = {{{{{{ .f_marker  = MARKER_DIREND }}}}}}
#endif
};



PRIVATE NONNULL((1, 2, 3)) void KCALL
Fat_CreateDirectoryInDirectory(struct directory_node *__restrict target_directory,
                               struct directory_entry *__restrict target_dirent,
                               struct directory_node *__restrict new_node)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ILLEGAL_PATH,
		       E_FSERROR_DISK_FULL, E_FSERROR_READONLY,
		       E_IOERROR_BADBOUNDS, E_IOERROR_READONLY,
		       E_IOERROR, ...) {
	struct inode_data *node;
	new_node->i_type = &Fat_DirectoryNodeOperators;
	if (target_directory == target_directory->i_super &&
	    ((FatSuperblock *)target_directory)->f_type != FAT32)
		new_node->i_type = &Fat16_RootDirectoryDirectoryEntryNodeOperators;
	/* Allocate FS-specific INode data for the new file. */
	node = (struct inode_data *)kmalloc(sizeof(struct inode_data),
	                                    FS_GFP | GFP_CALLOC);
	TRY {
		FatClusterIndex index;
		FatFile pattern[COMPILER_LENOF(new_directory_pattern)];
		new_node->i_fsdata  = node;
		node->i_clusterv    = (FatClusterIndex *)kmalloc(2 * sizeof(FatClusterIndex), FS_GFP);
		node->i_clustera    = 2;
		node->i_clusterc    = 1;
		node->i_clusterv[0] = ((FatSuperblock *)target_directory->i_super)->f_cluster_eof_marker;
		/* Allocate the initial contents of the directory. */
		memcpy(pattern, new_directory_pattern, sizeof(pattern));
		pattern[0].f_atime             = Fat_EncodeFileDate(new_node->i_fileatime.tv_sec);
		pattern[0].f_mtime.fc_date     = Fat_EncodeFileDate(new_node->i_filemtime.tv_sec);
		pattern[0].f_mtime.fc_time     = Fat_EncodeFileTime(new_node->i_filemtime.tv_sec);
		pattern[0].f_ctime.fc_date     = Fat_EncodeFileDate(new_node->i_filectime.tv_sec);
		pattern[0].f_ctime.fc_time     = Fat_EncodeFileTime(new_node->i_filectime.tv_sec);
		pattern[0].f_ctime.fc_sectenth = (u8)(new_node->i_filectime.tv_nsec / (1000000000ul / 200ul));
		pattern[1].f_atime             = pattern[0].f_atime;
		pattern[1].f_mtime.fc_date     = pattern[0].f_mtime.fc_date;
		pattern[1].f_mtime.fc_time     = pattern[0].f_mtime.fc_time;
		pattern[1].f_ctime.fc_date     = pattern[0].f_ctime.fc_date;
		pattern[1].f_ctime.fc_time     = pattern[0].f_ctime.fc_time;
		pattern[1].f_ctime.fc_sectenth = pattern[0].f_ctime.fc_sectenth;
		if (new_node->i_type != &Fat16_RootDirectoryDirectoryEntryNodeOperators) {
			index = Fat_GetFileCluster(target_directory, 0,
			                           FAT_GETCLUSTER_MODE_FCREATE |
			                           FAT_GETCLUSTER_MODE_FNOZERO);
			pattern[1].f_clusterlo = (le16)LESWAP16(index & 0xffff);
			pattern[1].f_clusterhi = (le16)LESWAP16((u16)(index >> 16));
		} else {
			/* 0x0000 -- Free Cluster; also used by DOS to refer to the parent directory starting cluster
			 *           in ".." entries of subdirectories of the root directory on FAT12/FAT16 volumes
			 *           https://en.wikipedia.org/wiki/Design_of_the_FAT_file_system */
		}
		/* Allocate the first cluster for the new directory, so
		 * we know where to point the directory self-reference. */
		index = Fat_GetFileCluster(new_node, 0,
		                           FAT_GETCLUSTER_MODE_FCREATE |
		                           FAT_GETCLUSTER_MODE_FNOZERO |
		                           FAT_GETCLUSTER_MODE_FNCHNGE);
		TRY {
			pattern[0].f_clusterlo = (le16)LESWAP16(index & 0xffff);
			pattern[0].f_clusterhi = (le16)LESWAP16((u16)(index >> 16));
			/* Write the directory content into the new directory node. */
			Fat32_VWriteToINode(new_node, (byte_t *)pattern, sizeof(pattern), 0);

			/* Add the new directory to its parent's directory. */
			Fat_AddFileToDirectory(target_directory, target_dirent, new_node);
		} EXCEPT {
			/* Try to free the already-written (and allocated) new-directory pattern. */
			Fat_DeleteClusterChain((FatSuperblock *)target_directory->i_super,
			                       new_node->i_fsdata->i_clusterv[0]);
			RETHROW();
		}
	} EXCEPT {
		kfree(new_node->i_fsdata->i_directory.i_freev);
		kfree(new_node->i_fsdata->i_clusterv);
		kfree(new_node->i_fsdata);
		RETHROW();
	}
	new_node->i_filenlink = (nlink_t)1;
}


PRIVATE NONNULL((1, 2, 3, 4, 5)) REF struct inode *KCALL
Fat_RenameFileInDirectory(struct directory_node *__restrict source_directory,
                          struct directory_entry *__restrict source_dirent,
                          struct directory_node *__restrict target_directory,
                          struct directory_entry *__restrict target_dirent,
                          struct inode *__restrict source_node)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ILLEGAL_PATH,
		       E_FSERROR_DISK_FULL, E_FSERROR_READONLY,
		       E_IOERROR_BADBOUNDS, E_IOERROR_READONLY,
		       E_IOERROR, ...) {
	/* Add the file to its new directory first.
	 * This way, even if we fail to unlink the file from its own directory,
	 * at no point will we run the risk of ending up with no file at all! */
	Fat_AddFileToDirectory(target_directory, target_dirent, source_node);
	TRY {
		/* With the file now apart of the target directory,
		 * we can now remove it from the source directory. */
		Fat_UnlinkFileFromParentDirectory(source_directory, source_dirent, source_node);
	} EXCEPT {
		/* If we couldn't remove the node from the source directory, try to
		 * remove it from the target directory, so we don't end up with the
		 * same file in 2 different locations, which could end _real_ bad,
		 * especially since FAT doesn't support hard links. */
		Fat_UnlinkFileFromParentDirectory(target_directory, target_dirent, source_node);
		RETHROW();
	}
	return (struct inode *)incref(source_node);
}





INTERN struct inode_type Fat_FileNodeOperators = {
	.it_fini = &Fat_FinalizeNode,
	.it_attr = {
		.a_loadattr   = &Fat32_LoadINodeAttributes,
		.a_saveattr   = &Fat32_SaveINodeAttributes,
		.a_maskattr   = &Fat_MaskINodeAttributes,
		.a_pathconf   = &Fat_PathConf,
		.a_ioctl      = &Fat_Ioctl,
		.a_clearcache = NULL,
	},
	.it_file = {
		.f_read     = &Fat32_ReadFromINode,
		.f_pread    = &Fat32_ReadFromINodePhys,
		.f_readv    = &Fat32_ReadFromINodeVector,
		.f_preadv   = &Fat32_ReadFromINodeVectorPhys,
		.f_write    = &Fat32_WriteToINode,
		.f_pwrite   = &Fat32_WriteToINodePhys,
		.f_writev   = &Fat32_WriteToINodeVector,
		.f_pwritev  = &Fat32_WriteToINodeVectorPhys,
		.f_truncate = &Fat_TruncateINode,
	},
};

INTERN struct inode_type Fat_DirectoryNodeOperators = {
	.it_fini = &Fat_FinalizeNode,
	.it_attr = {
		.a_loadattr   = &Fat32_LoadINodeAttributes,
		.a_saveattr   = &Fat32_SaveINodeAttributes,
		.a_maskattr   = &Fat_MaskINodeAttributes,
		.a_pathconf   = &Fat_PathConf,
		.a_ioctl      = &Fat_Ioctl,
		.a_clearcache = NULL,
	},
	.it_file = {
		.f_read     = NULL,
		.f_pread    = NULL,
		.f_readv    = NULL,
		.f_preadv   = NULL,
		.f_write    = NULL,
		.f_pwrite   = NULL,
		.f_writev   = NULL,
		.f_pwritev  = NULL,
		.f_truncate = NULL,
	},
	{
		.it_directory = {
			.d_readdir = &Fat_ReadDirectory,
			{ NULL },
			.d_creat   = &Fat_CreateFileInDirectory,
			.d_mkdir   = &Fat_CreateDirectoryInDirectory,
			.d_symlink = NULL,
			.d_mknod   = NULL,
			.d_link    = NULL,
			.d_rename  = &Fat_RenameFileInDirectory,
			.d_unlink  = &Fat_UnlinkFileFromParentDirectory,
			.d_rmdir   = &Fat_RemoveDirectoryFromParentDirectory,
		}
	}
};

INTERN struct inode_type Fat16_RootDirectoryFileEntryNodeOperators = {
	.it_fini = &Fat_FinalizeNode,
	.it_attr = {
		.a_loadattr   = &Fat16_LoadRootDirectoryEntryINodeAttributes,
		.a_saveattr   = &Fat16_SaveRootDirectoryEntryINodeAttributes,
		.a_maskattr   = &Fat_MaskINodeAttributes,
		.a_pathconf   = &Fat_PathConf,
		.a_ioctl      = &Fat_Ioctl,
		.a_clearcache = NULL,
	},
	.it_file = {
		.f_read     = &Fat32_ReadFromINode,
		.f_pread    = &Fat32_ReadFromINodePhys,
		.f_readv    = &Fat32_ReadFromINodeVector,
		.f_preadv   = &Fat32_ReadFromINodeVectorPhys,
		.f_write    = &Fat32_WriteToINode,
		.f_pwrite   = &Fat32_WriteToINodePhys,
		.f_writev   = &Fat32_WriteToINodeVector,
		.f_pwritev  = &Fat32_WriteToINodeVectorPhys,
		.f_truncate = &Fat_TruncateINode,
	},
};

INTERN struct inode_type Fat16_RootDirectoryDirectoryEntryNodeOperators = {
	.it_fini = &Fat_FinalizeNode,
	.it_attr = {
		.a_loadattr   = &Fat16_LoadRootDirectoryEntryINodeAttributes,
		.a_saveattr   = &Fat16_SaveRootDirectoryEntryINodeAttributes,
		.a_maskattr   = &Fat_MaskINodeAttributes,
		.a_pathconf   = &Fat_PathConf,
		.a_ioctl      = &Fat_Ioctl,
		.a_clearcache = NULL,
	},
	.it_file = {
		.f_read     = NULL,
		.f_pread    = NULL,
		.f_readv    = NULL,
		.f_preadv   = NULL,
		.f_write    = NULL,
		.f_pwrite   = NULL,
		.f_writev   = NULL,
		.f_pwritev  = NULL,
		.f_truncate = NULL,
	},
	{
		.it_directory = {
			.d_readdir = &Fat_ReadDirectory,
			{ NULL },
			.d_creat   = &Fat_CreateFileInDirectory,
			.d_mkdir   = &Fat_CreateDirectoryInDirectory,
			.d_symlink = NULL,
			.d_mknod   = NULL,
			.d_link    = NULL,
			.d_rename  = &Fat_RenameFileInDirectory,
			.d_unlink  = &Fat_UnlinkFileFromParentDirectory,
			.d_rmdir   = &Fat_RemoveDirectoryFromParentDirectory,
		}
	}
};

INTERN struct inode_type Fat16_RootDirectoryNodeOperators = {
	.it_fini = NULL,
	.it_attr = {
		.a_loadattr   = NULL,
		.a_saveattr   = NULL,
		.a_maskattr   = NULL,
		.a_pathconf   = &Fat_PathConf,
		.a_ioctl      = &Fat_Ioctl,
		.a_clearcache = NULL,
	},
	.it_file = {
		.f_read     = NULL,
		.f_pread    = NULL,
		.f_readv    = NULL,
		.f_preadv   = NULL,
		.f_write    = NULL,
		.f_pwrite   = NULL,
		.f_writev   = NULL,
		.f_pwritev  = NULL,
		.f_truncate = NULL,
	},
	{
		.it_directory = {
			.d_readdir = &Fat_ReadDirectory,
			{ NULL },
			.d_creat   = &Fat_CreateFileInDirectory,
			.d_mkdir   = &Fat_CreateDirectoryInDirectory,
			.d_symlink = NULL,
			.d_mknod   = NULL,
			.d_link    = NULL,
			.d_rename  = &Fat_RenameFileInDirectory,
			.d_unlink  = &Fat_UnlinkFileFromParentDirectory,
			.d_rmdir   = &Fat_RemoveDirectoryFromParentDirectory,
		}
	}
};

INTERN struct inode_type Fat32_RootDirectoryNodeOperators = {
	.it_fini = NULL,
	.it_attr = {
		.a_loadattr   = NULL,
		.a_saveattr   = NULL,
		.a_maskattr   = NULL,
		.a_pathconf   = &Fat_PathConf,
		.a_ioctl      = &Fat_Ioctl,
		.a_clearcache = NULL,
	},
	.it_file = {
		.f_read     = NULL,
		.f_pread    = NULL,
		.f_readv    = NULL,
		.f_preadv   = NULL,
		.f_write    = NULL,
		.f_pwrite   = NULL,
		.f_writev   = NULL,
		.f_pwritev  = NULL,
		.f_truncate = NULL,
	},
	{
		.it_directory = {
			.d_readdir = &Fat_ReadDirectory,
			{ NULL },
			.d_creat   = &Fat_CreateFileInDirectory,
			.d_mkdir   = &Fat_CreateDirectoryInDirectory,
			.d_symlink = NULL,
			.d_mknod   = NULL,
			.d_link    = NULL,
			.d_rename  = &Fat_RenameFileInDirectory,
			.d_unlink  = &Fat_UnlinkFileFromParentDirectory,
			.d_rmdir   = &Fat_RemoveDirectoryFromParentDirectory,
		}
	}
};












PRIVATE FatSectorIndex KCALL
Fat12_GetTableSector(FatSuperblock *__restrict self,
                     FatClusterIndex id) {
	return (id + (id / 2)) / self->f_sectorsize;
}
PRIVATE FatSectorIndex KCALL
Fat16_GetTableSector(FatSuperblock *__restrict self,
                     FatClusterIndex id) {
	return (id * 2) / self->f_sectorsize;
}
PRIVATE FatSectorIndex KCALL
Fat32_GetTableSector(FatSuperblock *__restrict self,
                     FatClusterIndex id) {
	return (id * 4) / self->f_sectorsize;
}

PRIVATE FatClusterIndex KCALL
Fat12_GetFatIndirection(FatSuperblock *__restrict self,
                        FatClusterIndex index) {
	u16 val;
	assertf(index < self->f_fat_length,
	        "Out-of-bounds FAT index: %I32u >= %I32u",
	        index, self->f_fat_length);
	val = *(u16 *)((uintptr_t)self->f_fat_table + (index + (index >> 1)));
	if (index & 1)
		val >>= 4;
	else
		val &= 0x0fff;
	return val;
}
PRIVATE void KCALL
Fat12_SetFatIndirection(FatSuperblock *__restrict self,
                        FatClusterIndex index,
                        FatClusterIndex indirection_target) {
	u16 *pval;
	assertf(index < self->f_fat_length,
	        "Out-of-bounds FAT index: %I32u >= %I32u",
	        index, self->f_fat_length);
	pval = ((u16 *)((uintptr_t)self->f_fat_table + (index + (index / 2))));
	if (index & 1)
		*pval = (*pval & 0xf) | (indirection_target << 4);
	else
		*pval |= indirection_target & 0xfff;
}

PRIVATE FatClusterIndex KCALL
Fat16_GetFatIndirection(FatSuperblock *__restrict self,
                        FatClusterIndex index) {
	assertf(index < self->f_fat_length,
	        "Out-of-bounds FAT index: %I32u >= %I32u",
	        index, self->f_fat_length);
	return ((u16 *)self->f_fat_table)[index];
}
PRIVATE void KCALL
Fat16_SetFatIndirection(FatSuperblock *__restrict self,
                        FatClusterIndex index,
                        FatClusterIndex indirection_target) {
	assertf(index < self->f_fat_length,
	        "Out-of-bounds FAT index: %I32u >= %I32u",
	        index, self->f_fat_length);
	((u16 *)self->f_fat_table)[index] = (u16)indirection_target;
}

PRIVATE FatClusterIndex KCALL
Fat32_GetFatIndirection(FatSuperblock *__restrict self,
                        FatClusterIndex index) {
	assertf(index < self->f_fat_length,
	        "Out-of-bounds FAT index: %I32u >= %I32u",
	        index, self->f_fat_length);
	return ((u32 *)self->f_fat_table)[index];
}
PRIVATE void KCALL
Fat32_SetFatIndirection(FatSuperblock *__restrict self,
                        FatClusterIndex index,
                        FatClusterIndex indirection_target) {
	assertf(index < self->f_fat_length,
	        "Out-of-bounds FAT index: %I32u >= %I32u",
	        index, self->f_fat_length);
	((u32 *)self->f_fat_table)[index] = indirection_target;
}

INTERN FatClusterIndex KCALL
Fat_GetFatIndirection(FatSuperblock *__restrict self,
                      FatClusterIndex index) {
	FatSectorIndex table_sector;
	table_sector = (*self->f_fat_sector)(self, index);
	assertf(table_sector < self->f_sec4fat,
	        "Out-of-bounds FAT sector index: %I32u >= %I32u",
	        table_sector, self->f_sec4fat);
	if (!FAT_META_GTLOAD(self, table_sector)) {
		/* Must load missing table sectors. */
		SCOPED_WRITELOCK(&self->f_fat_lock);
		/* Lazily load the fat table sector that hasn't been loaded yet. */
		block_device_read(self->s_device,
		                  (void *)((uintptr_t)self->f_fat_table + (table_sector * self->f_sectorsize)),
		                  self->f_sectorsize,
		                  FAT_SECTORADDR(self, self->f_fat_start + table_sector));
		FAT_META_STLOAD(self, table_sector);
	}
	/* Now just read the FAT entry. */
	return (*self->f_fat_get)(self, index);
}


INTERN void KCALL
Fat_SetFatIndirection(FatSuperblock *__restrict self,
                      FatClusterIndex index,
                      FatClusterIndex indirection_target) {
	FatSectorIndex table_sector;
	assert(sync_writing(&self->f_fat_lock));
	table_sector = (*self->f_fat_sector)(self, index);
	assertf(table_sector < self->f_sec4fat,
	        "Out-of-bounds FAT sector index: %I32u >= %I32u",
	        table_sector, self->f_sec4fat);
	if (!FAT_META_GTLOAD(self, table_sector)) {
		/* Must load missing table sectors. */
		block_device_read(self->s_device,
		                  (void *)((uintptr_t)self->f_fat_table + (table_sector * self->f_sectorsize)),
		                  self->f_sectorsize,
		                  FAT_SECTORADDR(self, self->f_fat_start + table_sector));
		FAT_META_STLOAD(self, table_sector);
	}
	/* Now just override the FAT entry. */
	(*self->f_fat_set)(self, index, indirection_target);
	/* Mark the metadata associated with the sector as changed. */
	FAT_META_STCHNG(self, table_sector);
	self->f_flags |= FAT_FCHANGED;
}


INTERN FatClusterIndex KCALL
Fat_FindFreeCluster(FatSuperblock *__restrict self) {
	FatClusterIndex result;
	assert(sync_reading(&self->f_fat_lock));
	result = self->f_free_pos;
	for (; result < self->f_cluster_eof; ++result) {
		if (Fat_GetFatIndirection(self, result) == FAT_CLUSTER_UNUSED)
			goto found_one;
	}
	/* Scan everything before our previous location. */
	result = 0;
	for (; result < self->f_free_pos; ++result) {
		if (Fat_GetFatIndirection(self, result) == FAT_CLUSTER_UNUSED)
			goto found_one;
	}
	/* Disk is full... */
	THROW(E_FSERROR_DISK_FULL);
found_one:
	self->f_free_pos = result;
	return result;
}

INTERN void KCALL
Fat_DeleteClusterChain(FatSuperblock *__restrict self,
                       FatClusterIndex first_delete_index) {
	SCOPED_WRITELOCK(&self->f_fat_lock);
	while (first_delete_index < self->f_cluster_eof &&
	       first_delete_index != FAT_CLUSTER_UNUSED) {
		FatClusterIndex next;
		/* Read the next link. */
		next = Fat_GetFatIndirection(self, first_delete_index);
		/* Mark the link as being unused now. */
		Fat_SetFatIndirection(self, first_delete_index, FAT_CLUSTER_UNUSED);
		/* Continue deleting all entries from the chain. */
		first_delete_index = next;
	}
}


PRIVATE void KCALL trimspecstring(char *__restrict buf, size_t size) {
	while (size && FAT_ISSPACE(*buf)) {
		memmove(buf, buf + 1, --size);
		buf[size] = '\0';
	}
	while (size && FAT_ISSPACE(buf[size - 1]))
		buf[--size] = '\0';
}


PRIVATE void KCALL
Fat_OpenSuperblock(FatSuperblock *__restrict self, UNCHECKED USER char *args)
		THROWS(E_FSERROR_WRONG_FILE_SYSTEM, E_FSERROR_CORRUPTED_FILE_SYSTEM,
		       E_IOERROR_BADBOUNDS, E_DIVIDE_BY_ZERO, E_OVERFLOW, E_INDEX_ERROR,
		       E_IOERROR, E_SEGFAULT, ...) {
	FatDiskHeader disk_header;
	(void)args; /* TODO: User-arguments. */

	/* Read the FAT disk header. */
	block_device_read(self->s_device,
	                  &disk_header,
	                  sizeof(disk_header),
	                  0);

	/* Validate the boot signature. */
	if unlikely(disk_header.fat32.f32_bootsig[0] != 0x55 ||
	            disk_header.fat32.f32_bootsig[1] != 0xAA)
		THROW(E_FSERROR_WRONG_FILE_SYSTEM);
	{
		u16 sector_size;
		/* Figure out how big sectors are. */
		if (!disk_header.bpb.bpb_sectors_per_cluster ||
		    !disk_header.bpb.bpb_reserved_sectors) /* What's the first sector, then? */
			THROW(E_FSERROR_WRONG_FILE_SYSTEM);
		sector_size = LESWAP16(disk_header.bpb.bpb_bytes_per_sector);
#if defined(PAGESIZE) && PAGESIZE < 512
#error "System page size is too small to support any FAT variation"
#endif
		if (sector_size == 512) {
			STATIC_ASSERT(1 << 9 == 512);
			self->db_pageshift = PAGESHIFT - 9;
		} else if (pagedir_pagesize() >= 1024 && sector_size == 1024) {
			STATIC_ASSERT(1 << 10 == 1024);
			self->db_pageshift = PAGESHIFT - 10;
		} else if (pagedir_pagesize() >= 2048 && sector_size == 2048) {
			STATIC_ASSERT(1 << 11 == 2048);
			self->db_pageshift = PAGESHIFT - 11;
		} else if (pagedir_pagesize() >= 4096 && sector_size == 4096) {
			STATIC_ASSERT(1 << 12 == 4096);
			self->db_pageshift = PAGESHIFT - 12;
		} else {
			THROW(E_FSERROR_WRONG_FILE_SYSTEM);
		}
#ifndef CONFIG_VM_DATABLOCK_MIN_PAGEINFO
		self->db_addrshift = PAGESHIFT - self->db_pageshift;
		self->db_pagealign = (size_t)1 << self->db_pageshift;
		self->db_pagemask  = self->db_pagealign - 1;
		self->db_pagesize  = sector_size;
#endif
	}
	/* Extract some common information. */
	self->f_fat_start   = (FatSectorIndex)LESWAP16(disk_header.bpb.bpb_reserved_sectors);
	self->f_sec4clus    = (size_t)disk_header.bpb.bpb_sectors_per_cluster;
	self->f_fat_count   = (u32)disk_header.bpb.bpb_fatc;
	self->f_clustersize = (size_t)(self->f_sec4clus << FAT_SECTORSHIFT(self));

	/* Figure out what kind of FAT filesystem this is. */
	if (!disk_header.bpb.bpb_sectors_per_fat || !disk_header.bpb.bpb_maxrootsize) {
		self->f_dat_start = self->f_fat_start + (LESWAP32(disk_header.fat32.f32_sectors_per_fat) *
		                                         disk_header.bpb.bpb_fatc);
		self->f_type      = FAT32;
	} else {
		u32 fat_size, root_sectors;
		u32 data_sectors, total_clusters;
		root_sectors = (LESWAP16(disk_header.bpb.bpb_maxrootsize) * sizeof(FatFile) +
		                (FAT_SECTORSIZE(self) - 1)) >>
		               FAT_SECTORSHIFT(self);
		fat_size          = (disk_header.bpb.bpb_fatc * LESWAP16(disk_header.bpb.bpb_sectors_per_fat));
		self->f_dat_start = LESWAP16(disk_header.bpb.bpb_reserved_sectors);
		self->f_dat_start += fat_size;
		self->f_dat_start += root_sectors;
		/* Calculate the total number of data sectors. */
		if (disk_header.bpb.bpb_shortsectorc) {
			data_sectors = (u32)LESWAP16(disk_header.bpb.bpb_shortsectorc);
		} else {
			data_sectors = LESWAP32(disk_header.bpb.bpb_longsectorc);
		}
		if (OVERFLOW_USUB(data_sectors, LESWAP16(disk_header.bpb.bpb_reserved_sectors), &data_sectors))
			THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);
		if (OVERFLOW_USUB(data_sectors, fat_size, &data_sectors))
			THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);
		if (OVERFLOW_USUB(data_sectors, root_sectors, &data_sectors))
			THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);
		/* Calculate the total number of data clusters. */
		total_clusters = data_sectors / disk_header.bpb.bpb_sectors_per_cluster;
		/**/ if (total_clusters > FAT16_MAXCLUSTERS)
			self->f_type = FAT32;
		else if (total_clusters > FAT12_MAXCLUSTERS)
			self->f_type = FAT16;
		else
			self->f_type = FAT12;
	}
	if (self->f_type == FAT32) {
		if (disk_header.fat32.f32_signature != 0x28 &&
		    disk_header.fat32.f32_signature != 0x29)
			THROW(E_FSERROR_WRONG_FILE_SYSTEM);
		self->f_volid = LESWAP32(disk_header.fat32.f32_volid);
		memcpy(self->f_label, disk_header.fat32.f32_label, sizeof(disk_header.fat32.f32_label));
		memcpy(self->f_sysname, disk_header.fat32.f32_sysname, sizeof(disk_header.fat32.f32_sysname));
		self->f_sec4fat            = LESWAP32(disk_header.fat32.f32_sectors_per_fat);
		self->f_cluster_eof        = (self->f_sec4fat << FAT_SECTORSHIFT(self)) / 4;
		self->f_cluster_eof_marker = 0xffffffff;
		/* Must lookup the cluster of the root directory. */
		self->f_root.i_clusterc    = 1;
		self->f_root.i_clustera    = 2;
		self->f_root.i_clusterv    = (FatClusterIndex *)kmalloc(2 * sizeof(FatClusterIndex), FS_GFP);
		self->f_root.i_clusterv[0] = LESWAP32(disk_header.fat32.f32_root_cluster);
		self->f_fat_get            = &Fat32_GetFatIndirection;
		self->f_fat_set            = &Fat32_SetFatIndirection;
		self->f_fat_sector         = &Fat32_GetTableSector;
	} else {
		if (self->f_type == FAT12) {
			self->f_cluster_eof_marker = 0xfff;
			self->f_fat_get            = &Fat12_GetFatIndirection;
			self->f_fat_set            = &Fat12_SetFatIndirection;
			self->f_fat_sector         = &Fat12_GetTableSector;
		} else {
			self->f_cluster_eof_marker = 0xffff;
			self->f_fat_get            = &Fat16_GetFatIndirection;
			self->f_fat_set            = &Fat16_SetFatIndirection;
			self->f_fat_sector         = &Fat16_GetTableSector;
		}
		if (disk_header.fat16.f16_signature != 0x28 &&
		    disk_header.fat16.f16_signature != 0x29)
			THROW(E_FSERROR_WRONG_FILE_SYSTEM);
		self->f_volid = LESWAP32(disk_header.fat16.f16_volid);
		memcpy(self->f_label, disk_header.fat16.f16_label, sizeof(disk_header.fat16.f16_label));
		memcpy(self->f_sysname, disk_header.fat16.f16_sysname, sizeof(disk_header.fat16.f16_sysname));
		self->f_root.i16_root.f16_rootpos = (pos_t)LESWAP16(disk_header.bpb.bpb_reserved_sectors);
		self->f_root.i16_root.f16_rootpos += (disk_header.bpb.bpb_fatc * LESWAP16(disk_header.bpb.bpb_sectors_per_fat));
		self->f_root.i16_root.f16_rootpos <<= FAT_SECTORSHIFT(self);
		self->f_sec4fat                   = LESWAP16(disk_header.bpb.bpb_sectors_per_fat);
		self->f_root.i16_root.f16_rootsiz = (u32)LESWAP16(disk_header.bpb.bpb_maxrootsize);
		self->f_root.i16_root.f16_rootsiz *= sizeof(FatFile);
		self->f_cluster_eof = (self->f_sec4fat << FAT_SECTORSHIFT(self)) / 2;
		/* It is possible to create a FAT16 filesystem with 0x10000 sectors.
		 * This is a special case since sector 0xffff still needs to be reserved
		 * as the special sector used for marking file EOF.
		 * Because of this, make sure not to allocate sectors above the EOF marker */
		if (self->f_cluster_eof > self->f_cluster_eof_marker)
			self->f_cluster_eof = self->f_cluster_eof_marker;
	}
	if (self->f_cluster_eof <= 0xffff)
		self->f_features |= FAT_FEATURE_ARB; /* 16-bit clusters --> high 16 bits are the ARB mask. */
	if (self->f_cluster_eof_marker < self->f_cluster_eof)
		self->f_cluster_eof_marker = self->f_cluster_eof;
	/* XXX: Detect `FAT_FEATURE_UGID' */

	self->f_fat_table = NULL;
	self->f_fat_meta  = NULL;
	COMPILER_WRITE_BARRIER();
	self->i_fsdata = &self->f_root;

	memcpy(&self->f_oem, disk_header.bpb.bpb_oem, 8 * sizeof(char));
	self->f_fat_size = (size_t)self->f_sec4fat << FAT_SECTORSHIFT(self);
	trimspecstring(self->f_oem, 8);
	trimspecstring(self->f_label, 11);
	trimspecstring(self->f_sysname, 8);

	self->f_uid  = 0;
	self->f_gid  = 0;
	self->f_mode = 0555; /* Read/Execute permissions for everyone. */
	self->i_filemode |= 0555;

	/* Setup operators */
	if (self->f_type == FAT32) {
		self->i_type = &Fat32_RootDirectoryNodeOperators;
	} else {
		self->i_type = &Fat16_RootDirectoryNodeOperators;
	}
	self->i_filenlink = (nlink_t)1;

	/* Set the attribute-loaded flag of the root directory node. */
	self->i_flags |= INODE_FATTRLOADED;
	self->i_fileino = 0;

	/* Allocate the metadata tables. */
	self->f_free_pos = 0;
	TRY {
		self->f_fat_table = kmalloc(self->f_fat_size, FS_GFP);
		self->f_fat_meta = (uintptr_t *)kmalloc(CEILDIV(self->f_sec4fat, BITS_PER_POINTER / FAT_METABITS) *
		                                        sizeof(uintptr_t),
		                                        FS_GFP | GFP_CALLOC);
	} EXCEPT {
		/*kfree(self->f_fat_meta);*/
		kfree(self->f_fat_table);
		if (self->f_type == FAT32)
			kfree(self->f_root.i_clusterv);
		RETHROW();
	}
	rwlock_cinit(&self->f_fat_lock);
	printk(KERN_INFO "Load FAT%u-filesystem on %.2x:%.2x (%q) [oem=%q] [label=%q] [sysname=%q]\n",
	       self->f_type == FAT12 ? 12 : self->f_type == FAT16 ? 16 : 32,
	       MAJOR(block_device_devno(self->s_device)),
	       MINOR(block_device_devno(self->s_device)),
	       self->s_device->bd_name,
	       self->f_oem, self->f_label, self->f_sysname);
}


PRIVATE NOBLOCK void
NOTHROW(KCALL Fat_FinalizeSuperblock)(FatSuperblock *__restrict self) {
	if (self->f_type == FAT32)
		kfree(self->f_root.i_clusterv);
	kfree(self->f_fat_table);
	kfree(self->f_fat_meta);
}

PRIVATE void KCALL
Fat_OpenINode(FatSuperblock *__restrict self,
              struct inode *__restrict node,
              struct directory_node *__restrict parent_directory,
              struct directory_entry *__restrict parent_directory_entry)
             THROWS(E_IOERROR, E_BADALLOC,...) {
	switch (node->i_filemode & S_IFMT) {

	case S_IFREG:
		node->i_type = &Fat_FileNodeOperators;
		break;

	case S_IFDIR:
		node->i_type = &Fat_DirectoryNodeOperators;
		break;

	default:
		/* Throw an unsupported-function error for any other type of node. */
		THROW(E_FSERROR_UNSUPPORTED_OPERATION);
	}

	node->i_filenlink = (nlink_t)1;
	node->i_fsdata = (FatNode *)kmalloc(sizeof(FatNode),
	                                    FS_GFP | GFP_CALLOC);
	if (self == parent_directory && self->f_type != FAT32) {
		/* FAT-16 root directory entries have special operators. */
		if ((node->i_filemode & S_IFMT) == S_IFREG) {
			node->i_type = &Fat16_RootDirectoryFileEntryNodeOperators;
		} else {
			node->i_type = &Fat16_RootDirectoryDirectoryEntryNodeOperators;
		}
	}
}


LOCAL void KCALL
Fat_WriteFatIndirectionTableSegment(FatSuperblock *__restrict self,
                                    FatSectorIndex fat_sector_index,
                                    size_t num_sectors) {
	FatSectorIndex sector_start;
	void *sector_buffer;
	size_t sector_bytes;
	u8 n = self->f_fat_count;
	assertf(fat_sector_index + num_sectors <= self->f_sec4fat,
	        "Out-of-bounds FAT sector index: %I32u+%I32u(%I32u) > %I32u",
	        fat_sector_index, num_sectors, fat_sector_index + num_sectors, self->f_sec4fat);
	sector_buffer = (void *)((uintptr_t)self->f_fat_table + (fat_sector_index * self->f_sectorsize));
	sector_bytes  = (size_t)(num_sectors * self->f_sectorsize);
	sector_start  = self->f_fat_start + fat_sector_index;
	printk(KERN_INFO "[fat] Saving modified meta-sectors %I32u..%I32u of 0..%I32u (%I32u..%I32u)\n",
	       fat_sector_index, fat_sector_index + num_sectors - 1, self->f_sec4fat - 1,
	       sector_start, sector_start + num_sectors - 1);
	/* Write to all redundant FAT copies. */
	while (n--) {
		block_device_write(self->s_device, sector_buffer, sector_bytes,
		                   FAT_SECTORADDR(self, sector_start + n * self->f_sec4fat));
	}
}

PRIVATE NONNULL((1, 2)) void KCALL
Fat_StatSuperblock(FatSuperblock *__restrict self,
                   USER CHECKED struct statfs *result)
		THROWS(E_IOERROR, E_SEGFAULT, ...) {
	memset(result, 0, sizeof(*result));
	result->f_type   = MSDOS_SUPER_MAGIC;
	result->f_bsize  = self->f_sectorsize;
	result->f_blocks = self->f_fat_length;
	result->f_bfree  = 0; /* TODO */
	result->f_bavail = 0; /* TODO */
	memcpy(&result->f_fsid, self->f_label, sizeof(result->f_fsid));
	result->f_namelen = LFN_SEQNUM_MAXCOUNT * LFN_NAME;
	result->f_frsize  = self->f_sectorsize; /* ??? */
}


PRIVATE void KCALL
Fat_SynchronizeSuperblock(FatSuperblock *__restrict self)
		THROWS(E_IOERROR, ...) {
	FatSectorIndex changed_begin, changed_end;
	if (!(self->f_flags & FAT_FCHANGED))
		return;
	SCOPED_WRITELOCK(&self->f_fat_lock);
	COMPILER_READ_BARRIER();
	if (self->f_flags & FAT_FCHANGED) {
		/* Let's do this! */
		changed_begin = 0;
		for (;;) {
			/* Search for chains for changed FAT entries and save them. */
			while (changed_begin != self->f_sec4fat &&
			       !FAT_META_GTCHNG(self, changed_begin))
				++changed_begin;
			changed_end = changed_begin;
			while (changed_end != self->f_sec4fat &&
			       FAT_META_GTCHNG(self, changed_end))
				++changed_end;
			if (changed_end == changed_begin) {
				assert(changed_begin == self->f_sec4fat);
				assert(changed_end == self->f_sec4fat);
				break;
			}
			Fat_WriteFatIndirectionTableSegment(self, changed_begin,
			                                    (size_t)(changed_end - changed_begin));
			/* If changes have been saved successfully, delete all the change bits. */
			while (changed_begin != changed_end) {
				FAT_META_UTCHNG(self, changed_begin);
				++changed_begin;
			}
		}
		self->f_flags &= ~FAT_FCHANGED;
	}
}


PRIVATE struct superblock_type Fat_SuperblockType = {
	/*.st_driver            = */&drv_self,
	/*.st_name              =*/ "fat",
	/*.st_flags             = */SUPERBLOCK_TYPE_FNORMAL,
	/*.st_sizeof_superblock = */sizeof(FatSuperblock),
	{
		/*.st_open = */(void(KCALL *)(struct superblock *__restrict,UNCHECKED USER char *))&Fat_OpenSuperblock
	},
	/*.st_functions = */{
		/*.f_fini     = */(void(KCALL *)(struct superblock *__restrict))&Fat_FinalizeSuperblock,
		/*.f_opennode = */(void(KCALL *)(struct superblock *__restrict,struct inode *__restrict,struct directory_node *__restrict,struct directory_entry *__restrict))&Fat_OpenINode,
		/*.f_sync     = */(void(KCALL *)(struct superblock *__restrict,USER CHECKED struct statfs *))&Fat_StatSuperblock,
		/*.f_sync     = */(void(KCALL *)(struct superblock *__restrict))&Fat_SynchronizeSuperblock
	}
};

INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_fat_driver)(void) {
	register_filesystem_type(&Fat_SuperblockType);
}

DECL_END

#ifndef __INTELLISENSE__

#undef IO_READ
#undef IO_WRITE
#undef IO_PHYS
#undef IO_VECTOR

/* Define FAT I/O functions */
#define IO_READ 1
#define IO_PHYS 1
#define IO_VECTOR 1
#include "fat-io.c.inl"
#define IO_READ 1
#define IO_VECTOR 1
#include "fat-io.c.inl"
#define IO_READ 1
#define IO_PHYS 1
#include "fat-io.c.inl"
#define IO_READ 1
#include "fat-io.c.inl"

#define IO_WRITE 1
#define IO_PHYS 1
#define IO_VECTOR 1
#include "fat-io.c.inl"
#define IO_WRITE 1
#define IO_VECTOR 1
#include "fat-io.c.inl"
#define IO_WRITE 1
#define IO_PHYS 1
#include "fat-io.c.inl"
#define IO_WRITE 1
#include "fat-io.c.inl"

#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_CORE_DRIVERS_FAT_C */
