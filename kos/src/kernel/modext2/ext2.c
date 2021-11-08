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
#ifndef GUARD_MODEXT2_EXT2_C
#define GUARD_MODEXT2_EXT2_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#ifdef CONFIG_USE_NEW_FS
#include "ext2.h"
/**/

#include <kernel/driver-callbacks.h>
#include <kernel/fs/blkdev.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/filesys.h>
#include <kernel/fs/flat.h>
#include <kernel/fs/node.h>
#include <kernel/fs/regnode.h>
#include <kernel/fs/super.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/kram.h>
#include <kernel/mman/map.h>
#include <kernel/mman/phys.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/byteorder.h>
#include <hybrid/byteswap.h>
#include <hybrid/overflow.h>

#include <kos/except.h>
#include <linux/magic.h>

#include <alloca.h>
#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

DECL_BEGIN

/* Return  the absolute on-disk position of the `Ext2DiskINode'
 * structure used to store descriptor data for the given `ino'. */
PRIVATE BLOCKING WUNUSED NONNULL((1)) pos_t KCALL
ext2_inoaddr(struct ext2super *__restrict self, ext2_ino_t ino) {
	pos_t result;
	ext2_bgroup_t group;
	ext2_ino_t offset;
	u32 bg_inodes;
	if unlikely(ino < 1 || ino > self->es_total_inodes)
		THROW(E_IOERROR_BADBOUNDS);
	group     = EXT2_INO_BGRP_INDEX(self, ino);
	offset    = EXT2_INO_BGRP_OFFSET(self, ino);
	bg_inodes = LETOH32(self->es_bgroupv[group].bg_inodes);
	result    = EXT2_BLOCK2ADDR(self, bg_inodes);
	result += offset * self->es_inode_size;
	return result;
}



/* Allocate physically continuous memory. */
PRIVATE WUNUSED ATTR_RETNONNULL void *FCALL
kmemalign_offset_physcont(size_t min_alignment, ptrdiff_t offset,
                          size_t num_bytes, gfp_t gfp) {
	/* TODO: Do this via a proper kernel API
	 * Idea: Instead of having a physical memory allocator function,
	 *       we should have mman functions that can be used to force
	 *       a block of kernel RAM to be physically continuous until
	 *       a phys-cont-release function is called.
	 * - Can only be used on memory allocated by mman_map_kram()
	 * - Locking is allowed to fail if locking isn't possible due
	 *   to other phys-cont-locks that  are already held on  some
	 *   overlapping pages. This way,  one such lock won't  block
	 *   if it collides with another, but we're able to  allocate
	 *   a different block and try to lock that one in that  case */
	struct s_delme { struct s_delme *next; };
	struct s_delme *delme = NULL;
	void *result;
	size_t pagebytes;
	RAII_FINALLY {
		while (delme) {
			struct s_delme *next;
			next = delme->next;
			kfree(delme);
			delme = next;
		}
	};
again:
	result = kmemalign_offset(min_alignment, offset, num_bytes,
	                          gfp | GFP_LOCKED | GFP_PREFLT);

	pagebytes = num_bytes + ((uintptr_t)result & PAGEMASK);
	if (pagebytes >= PAGESIZE) {
		size_t i        = PAGESIZE;
		physaddr_t base = pagedir_translate(result);
		do {
			physaddr_t next = pagedir_translate((byte_t *)result + i);
			if (base + i != next) {
				struct s_delme *d;
				d       = (struct s_delme *)result;
				d->next = delme;
				delme   = d;
				goto again;
			}
			i += PAGESIZE;
		} while (i < pagebytes);
	}
	return result;
}

PRIVATE NONNULL((1)) void FCALL
kfree_physcont(void *ptr) {
	/* TODO: Do this via a proper kernel API */
	kfree(ptr);
}



#define ext2iblock_free(self)   kfree_physcont(self)
#define ext2iiblock_free(self)  kfree_physcont(self)
#define ext2iiiblock_free(self) kfree_physcont(self)
PRIVATE WUNUSED ATTR_RETNONNULL NONNULL((1)) struct ext2iblock *FCALL
ext2iblock_alloc(struct ext2super *__restrict super, ext2_blocki_t addr) {
	struct ext2iblock *result;
	result = (struct ext2iblock *)kmemalign_offset_physcont(super->es_iobalign,
	                                                        offsetof(struct ext2iblock, eib_blocks),
	                                                        super->es_blocksize,
	                                                        GFP_NORMAL);
	TRY {
		fsuper_dev_rdsectors(&super->es_super.ffs_super,
		                     EXT2_BLOCK2ADDR(super, addr),
		                     pagedir_translate(ext2iblock_blocks(result)),
		                     super->es_blocksize);
	} EXCEPT {
		kfree_physcont(result);
		RETHROW();
	}
	return result;
}

PRIVATE WUNUSED ATTR_RETNONNULL NONNULL((1)) struct ext2iiblock *FCALL
ext2iiblock_alloc(struct ext2super *__restrict super, ext2_blockii_t addr) {
	struct ext2iiblock *result;
	result = (struct ext2iiblock *)kmemalign_offset_physcont(super->es_iobalign,
	                                                         super->es_ind_blocksize * sizeof(struct ext2iblock *),
	                                                         ext2iiblock_sizeof(super->es_ind_blocksize),
	                                                         GFP_CALLOC);
	TRY {
		fsuper_dev_rdsectors(&super->es_super.ffs_super,
		                     EXT2_BLOCK2ADDR(super, addr),
		                     pagedir_translate(ext2iiblock_blocks(result, super->es_ind_blocksize)),
		                     super->es_blocksize);
	} EXCEPT {
		kfree_physcont(result);
		RETHROW();
	}
	return result;
}
#define ext2iiiblock_alloc(super, /*ext2_blockiii_t*/ addr) \
	((struct ext2iiiblock *)ext2iiblock_alloc(super, addr))



/* Special return values for `ext2_blockaddr()' */
#define EXT2_BLOCKADDR_ST_NOTALLOC 0 /* Block isn't allocated. (Not returned for `EXT2_BLOCKADDR_F_ALLOC') */
#define EXT2_BLOCKADDR_ST_WRLOCK   1 /* Need a write-lock but cannot upgrade; caller must acquire lock and try again */

/* Flags for `ext2_blockaddr()' */
#define EXT2_BLOCKADDR_F_NORMAL 0x0000 /* Normal flags */
#define EXT2_BLOCKADDR_F_WRLOCK 0x0001 /* Caller is holding a write-lock to `self' */
#define EXT2_BLOCKADDR_F_ALLOC  0x0002 /* Allocate missing blocks. */

/* Return the on-disk block number (which can be converted into an on-disk
 * address with `EXT2_BLOCK2ADDR()') of  the `blockno'th block of  `self'.
 * The caller must be holding (at least) a read-lock to `self'.
 * @param: flags: Set of `EXT2_BLOCKADDR_F_*' */
PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) ext2_block_t KCALL
ext2_blockindex(struct ext2idat *__restrict self,
                struct ext2super *__restrict super,
                ext2_blockid_t blockno, unsigned int flags) {
	ext2_block_t result;

	/* Simple case: direct block pointer */
	if (blockno < EXT2_DIRECT_BLOCK_COUNT) {
		result = self->ei_dblock[blockno];
		if (result == 0 && (flags & EXT2_BLOCKADDR_F_ALLOC))
			THROW(E_NOT_IMPLEMENTED_TODO); /* TODO: Alloc */
		return result;
	}
	blockno -= EXT2_DIRECT_BLOCK_COUNT;

	/* Singly-indirect block table. */
	if (blockno < super->es_ind_blocksize) {
		struct ext2iblock *sib = self->ei_siblock_c;
		if (sib == NULL) {
			if unlikely(self->ei_siblock == 0) {
				if (flags & EXT2_BLOCKADDR_F_ALLOC)
					THROW(E_NOT_IMPLEMENTED_TODO); /* TODO: Alloc */
				return EXT2_BLOCKADDR_ST_NOTALLOC; /* SIB not allocated */
			}
			sib = ext2iblock_alloc(super, self->ei_siblock);
			if (!(flags & EXT2_BLOCKADDR_F_WRLOCK) && !ext2idat_tryupgrade(self)) {
				ext2iblock_free(sib);
				return EXT2_BLOCKADDR_ST_WRLOCK;
			}
			self->ei_siblock_c = sib;
			if (!(flags & EXT2_BLOCKADDR_F_WRLOCK))
				ext2idat_downgrade(self);
		}
		result = LETOH32(sib->eib_blocks[blockno]);
		if (result == 0 && (flags & EXT2_BLOCKADDR_F_ALLOC))
			THROW(E_NOT_IMPLEMENTED_TODO); /* TODO: Alloc */
		return result;
	}
	blockno -= super->es_ind_blocksize;

	/* Doubly-indirect block table. */
	if (blockno < super->es_ind_blocksize_p2) {
		struct ext2iblock *sib;
		struct ext2iiblock *dib = self->ei_diblock_c;
		ext2_blockid_t subindex;
		if (dib == NULL) {
			if unlikely(self->ei_diblock == 0) {
				if (flags & EXT2_BLOCKADDR_F_ALLOC)
					THROW(E_NOT_IMPLEMENTED_TODO); /* TODO: Alloc */
				return EXT2_BLOCKADDR_ST_NOTALLOC; /* DIB not allocated */
			}
			dib = ext2iiblock_alloc(super, self->ei_diblock);
			if (!(flags & EXT2_BLOCKADDR_F_WRLOCK) && !ext2idat_tryupgrade(self)) {
				ext2iiblock_free(dib);
				return EXT2_BLOCKADDR_ST_WRLOCK;
			}
			self->ei_diblock_c = dib;
			if (!(flags & EXT2_BLOCKADDR_F_WRLOCK))
				ext2idat_downgrade(self);
		}
		subindex = blockno / super->es_ind_blocksize;
		blockno %= super->es_ind_blocksize;
		sib = dib->eiib_blocks_c[subindex];
		if (sib == NULL) {
			ext2_blocki_t sib_block;
			sib_block = LETOH32(ext2iiblock_blocks(dib, super->es_ind_blocksize)[subindex]);
			if unlikely(sib_block == 0) {
				if (flags & EXT2_BLOCKADDR_F_ALLOC)
					THROW(E_NOT_IMPLEMENTED_TODO); /* TODO: Alloc */
				return EXT2_BLOCKADDR_ST_NOTALLOC; /* DIB->SIB not allocated */
			}
			sib = ext2iblock_alloc(super, sib_block);
			if (!(flags & EXT2_BLOCKADDR_F_WRLOCK) && !ext2idat_tryupgrade(self)) {
				ext2iblock_free(sib);
				return EXT2_BLOCKADDR_ST_WRLOCK;
			}
			dib->eiib_blocks_c[subindex] = sib;
			if (!(flags & EXT2_BLOCKADDR_F_WRLOCK))
				ext2idat_downgrade(self);
		}
		result = LETOH32(sib->eib_blocks[blockno]);
		if (result == 0 && (flags & EXT2_BLOCKADDR_F_ALLOC))
			THROW(E_NOT_IMPLEMENTED_TODO); /* TODO: Alloc */
		return result;
	}
	blockno -= super->es_ind_blocksize_p2;

	/* Triply-indirect block table. */
	if (blockno < super->es_ind_blocksize_p3) {
		struct ext2iblock *sib;
		struct ext2iiblock *dib;
		struct ext2iiiblock *tib = self->ei_tiblock_c;
		ext2_blockid_t subindex;
		if (tib == NULL) {
			if unlikely(self->ei_tiblock == 0) {
				if (flags & EXT2_BLOCKADDR_F_ALLOC)
					THROW(E_NOT_IMPLEMENTED_TODO); /* TODO: Alloc */
				return EXT2_BLOCKADDR_ST_NOTALLOC; /* TIB not allocated */
			}
			tib = ext2iiiblock_alloc(super, self->ei_tiblock);
			if (!(flags & EXT2_BLOCKADDR_F_WRLOCK) && !ext2idat_tryupgrade(self)) {
				ext2iiiblock_free(tib);
				return EXT2_BLOCKADDR_ST_WRLOCK;
			}
			self->ei_tiblock_c = tib;
			if (!(flags & EXT2_BLOCKADDR_F_WRLOCK))
				ext2idat_downgrade(self);
		}
		subindex = blockno / super->es_ind_blocksize_p2;
		blockno %= super->es_ind_blocksize_p2;
		dib = tib->eiiib_blocks_c[subindex];
		if (dib == NULL) {
			ext2_blockii_t dib_block;
			dib_block = LETOH32(ext2iiiblock_blocks(tib, super->es_ind_blocksize)[subindex]);
			if unlikely(dib_block == 0) {
				if (flags & EXT2_BLOCKADDR_F_ALLOC)
					THROW(E_NOT_IMPLEMENTED_TODO); /* TODO: Alloc */
				return EXT2_BLOCKADDR_ST_NOTALLOC; /* TIB->DIB not allocated */
			}
			dib = ext2iiblock_alloc(super, dib_block);
			if (!(flags & EXT2_BLOCKADDR_F_WRLOCK) && !ext2idat_tryupgrade(self)) {
				ext2iiblock_free(dib);
				return EXT2_BLOCKADDR_ST_WRLOCK;
			}
			tib->eiiib_blocks_c[subindex] = dib;
			if (!(flags & EXT2_BLOCKADDR_F_WRLOCK))
				ext2idat_downgrade(self);
		}
		subindex = blockno / super->es_ind_blocksize;
		blockno %= super->es_ind_blocksize;
		sib = dib->eiib_blocks_c[subindex];
		if (sib == NULL) {
			ext2_blocki_t sib_block;
			sib_block = LETOH32(ext2iiblock_blocks(dib, super->es_ind_blocksize)[subindex]);
			if unlikely(sib_block == 0) {
				if (flags & EXT2_BLOCKADDR_F_ALLOC)
					THROW(E_NOT_IMPLEMENTED_TODO); /* TODO: Alloc */
				return EXT2_BLOCKADDR_ST_NOTALLOC; /* TIB->DIB->SIB not allocated */
			}
			sib = ext2iblock_alloc(super, sib_block);
			if (!(flags & EXT2_BLOCKADDR_F_WRLOCK) && !ext2idat_tryupgrade(self)) {
				ext2iblock_free(sib);
				return EXT2_BLOCKADDR_ST_WRLOCK;
			}
			dib->eiib_blocks_c[subindex] = sib;
			if (!(flags & EXT2_BLOCKADDR_F_WRLOCK))
				ext2idat_downgrade(self);
		}
		result = LETOH32(sib->eib_blocks[blockno]);
		if (result == 0 && (flags & EXT2_BLOCKADDR_F_ALLOC))
			THROW(E_NOT_IMPLEMENTED_TODO); /* TODO: Alloc */
		return result;
	}

	/* Anything beyond this point cannot be allocated. */
	if (flags & EXT2_BLOCKADDR_F_ALLOC)
		THROW(E_FSERROR_FILE_TOO_BIG);
	return EXT2_BLOCKADDR_ST_NOTALLOC;
}

/* Decode INode data (excluding file size fields)
 * This function initializes:
 *  - node->mf_atime
 *  - node->mf_mtime
 *  - node->mf_ctime
 *  - node->fn_nlink
 *  - node->fn_uid
 *  - node->fn_gid
 *  - node->fn_mode
 *  - node->fn_fsdata->ei_blocks
 *  - node->fn_fsdata->ei_dblock
 *  - node->fn_fsdata->ei_siblock
 *  - node->fn_fsdata->ei_diblock
 *  - node->fn_fsdata->ei_tiblock
 * Regarding fields from `struct ext2idat', the caller must still initialize:
 *  - node->fn_fsdata->ei_inoaddr */
PRIVATE NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL ext2_diskinode_decode)(Ext2DiskINode const *__restrict self,
                                     struct fnode *__restrict node,
                                     struct ext2super *__restrict super,
                                     ext2_ino_t ino) {
	struct ext2idat *idat = node->fn_fsdata;
	unsigned int i;

	/* Basic fields. */
	node->mf_atime.tv_sec  = LETOH32(self->i_atime);
	node->mf_atime.tv_nsec = 0;
	node->mf_mtime.tv_sec  = LETOH32(self->i_mtime);
	node->mf_mtime.tv_nsec = 0;
	node->mf_ctime.tv_sec  = LETOH32(self->i_ctime);
	node->mf_ctime.tv_nsec = 0;
	node->fn_nlink         = LETOH16(self->i_nlink);
	node->fn_uid           = (uid_t)LETOH16(self->i_uid);
	node->fn_gid           = (gid_t)LETOH16(self->i_gid);
	node->fn_mode          = LETOH16(self->i_mode);
	if (super->es_os == EXT2_OS_FLINUX || super->es_os == EXT2_OS_FGNU_HURD) {
		node->fn_uid |= (uid_t)LETOH16(self->i_os_linux.l_uid_high) << 16;
		node->fn_gid |= (gid_t)LETOH16(self->i_os_linux.l_gid_high) << 16;
	}
	for (i = 0; i < EXT2_DIRECT_BLOCK_COUNT; ++i)
		idat->ei_dblock[i] = LETOH32(self->i_dblock[i]);
	idat->ei_siblock = LETOH32(self->i_siblock);
	idat->ei_diblock = LETOH32(self->i_diblock);
	idat->ei_tiblock = LETOH32(self->i_tiblock);
	idat->ei_blocks  = ext2super_sectors2blocks(super, LETOH32(self->i_nsectors));

	/* Safety check */
	if unlikely(node->fn_nlink == 0) {
		printk(KERN_WARNING "[ext2] Inode %#" PRIx32 " has nlink=0 "
		                    "on-disk (acting as though it had 1)\n",
		       (uint32_t)ino);
		node->fn_nlink = 1;
	}

	/* Initialize some common IData fields. */
	shared_rwlock_init(&idat->ei_lock);
	idat->ei_siblock_c = NULL;
	idat->ei_diblock_c = NULL;
	idat->ei_tiblock_c = NULL;
}





/************************************************************************/
/* Ext2 file operators                                                  */
/************************************************************************/
PRIVATE BLOCKING NONNULL((1, 5)) void KCALL
ext2_v_loadblocks(struct mfile *__restrict self, pos_t addr,
                  physaddr_t buf, size_t num_bytes,
                  struct aio_multihandle *__restrict aio) {
	struct fnode *me        = mfile_asnode(self);
	struct ext2idat *idat   = me->fn_fsdata;
	struct ext2super *super = fsuper_asext2(me->fn_super);
	ext2_blockid_t block    = (ext2_blockid_t)(addr >> me->mf_blockshift);
	size_t num_blocks       = num_bytes >> me->mf_blockshift;
	assertf((buf & super->es_blockmask) == 0, "Unaligned `buf = %#" PRIx64 "'", (uint64_t)buf);
	assertf((addr & super->es_blockmask) == 0, "Unaligned `addr = %#" PRIx64 "'", (uint64_t)addr);
	assertf((num_bytes & super->es_blockmask) == 0, "Unaligned `num_bytes = %#" PRIxSIZ "'", num_bytes);
	if unlikely(!num_bytes)
		return;
again:
	ext2idat_read(idat);
	{
		RAII_FINALLY { ext2idat_endread(idat); };
		while (num_blocks) {
			size_t num_cont = 1;
			size_t io_bytes;
			ext2_block_t blockindex;
			blockindex = ext2_blockindex(idat, super, block, EXT2_BLOCKADDR_F_NORMAL);
			if (blockindex == EXT2_BLOCKADDR_ST_WRLOCK)
				goto waitwrite;
			if (blockindex == EXT2_BLOCKADDR_ST_NOTALLOC) {
				/* Unallocated blocks. */
				while (num_cont < num_blocks) {
					ext2_block_t next;
					next = ext2_blockindex(idat, super, block + num_cont, EXT2_BLOCKADDR_F_NORMAL);
					if (next == EXT2_BLOCKADDR_ST_WRLOCK)
						goto waitwrite;
					if (next != EXT2_BLOCKADDR_ST_NOTALLOC)
						break;
					++num_cont;
				}
				io_bytes = num_cont << me->mf_blockshift;
				bzerophyscc(buf, io_bytes);
			} else {
				/* Check for continuous blocks. */
				while (num_cont < num_blocks) {
					ext2_block_t next;
					next = ext2_blockindex(idat, super, block + num_cont, EXT2_BLOCKADDR_F_NORMAL);
					if (next == EXT2_BLOCKADDR_ST_WRLOCK)
						goto waitwrite;
					if (next != blockindex + num_cont)
						break;
					++num_cont;
				}
				io_bytes = num_cont << me->mf_blockshift;

				/* Do disk I/O */
				fsuper_dev_rdsectors_async(&super->es_super.ffs_super,
				                           (pos_t)blockindex << me->mf_blockshift,
				                           buf, io_bytes, aio);
			}

			/* Advance to the next part. */
			buf += io_bytes;
			block += num_cont;
			num_blocks -= num_cont;
		}
	}
	return;
waitwrite:
	ext2idat_waitwrite(idat);
	goto again;
}

PRIVATE BLOCKING NONNULL((1)) void KCALL
ext2_v_wrattr(struct fnode *__restrict self)
		THROWS(E_IOERROR, ...) {
	struct ext2idat *idat   = self->fn_fsdata;
	struct ext2super *super = fsuper_asext2(self->fn_super);
	Ext2DiskINode disk_inode;
	uint64_t filesize;
	/* Read... */
	mfile_readall(super->es_super.ffs_super.fs_dev, &disk_inode,
	              super->es_inode_io_size, idat->ei_inoaddr);

	/* Modify... */
	mfile_tslock_acquire(self);
	if unlikely(self->mf_flags & MFILE_F_DELETED) {
		mfile_tslock_release_br(self);
		return;
	}
	disk_inode.i_atime = HTOLE32((u32)self->mf_atime.tv_sec);
	disk_inode.i_mtime = HTOLE32((u32)self->mf_mtime.tv_sec);
	disk_inode.i_ctime = HTOLE32((u32)self->mf_ctime.tv_sec);
	if (!mfile_issuper(self))
		disk_inode.i_nlink = HTOLE16((u16)self->fn_nlink);
	disk_inode.i_uid  = HTOLE16((u16)self->fn_uid);
	disk_inode.i_gid  = HTOLE16((u16)self->fn_gid);
	disk_inode.i_mode = HTOLE16((u16)self->fn_mode);
	if (super->es_os == EXT2_OS_FLINUX || super->es_os == EXT2_OS_FGNU_HURD) {
		disk_inode.i_os_linux.l_uid_high = HTOLE16((u16)(self->fn_uid >> 16));
		disk_inode.i_os_linux.l_gid_high = HTOLE16((u16)(self->fn_gid >> 16));
	}
	disk_inode.i_nsectors = HTOLE32(ext2super_blocks2sectors(super, idat->ei_blocks));
	filesize              = atomic64_read(&self->mf_filesize);
	mfile_tslock_release(self);
	if (!mfile_isdir(self)) {
		disk_inode.i_size_low  = HTOLE32((u32)filesize);
		disk_inode.i_size_high = HTOLE32((u32)(filesize >> 32));
	}

	/* Write... */
	mfile_writeall(super->es_super.ffs_super.fs_dev, &disk_inode,
	               super->es_inode_io_size, idat->ei_inoaddr);
}




/************************************************************************/
/* Directory operators                                                  */
/************************************************************************/

/* Mapping from `EXT2_FT_*' to `DT_*' */
PRIVATE unsigned char const ext_ft2dt[] = {
	[EXT2_FT_UNKNOWN]  = DT_UNKNOWN,
	[EXT2_FT_REG_FILE] = DT_REG,
	[EXT2_FT_DIR]      = DT_DIR,
	[EXT2_FT_CHRDEV]   = DT_CHR,
	[EXT2_FT_BLKDEV]   = DT_BLK,
	[EXT2_FT_FIFO]     = DT_FIFO,
	[EXT2_FT_SOCK]     = DT_SOCK,
	[EXT2_FT_SYMLINK]  = DT_LNK,
};

PRIVATE BLOCKING WUNUSED struct flatdirent *KCALL
ext2_dir_v_readdir(struct flatdirnode *__restrict self, pos_t pos)
		THROWS(E_BADALLOC, E_IOERROR, ...) {
	struct ext2super *super = fsuper_asext2(self->fn_super);
	Ext2DiskDirent entry;
	u16 entsize, entused, fd_namelen;
	REF struct flatdirent *result;
	unsigned char fd_type;
again:
	if (mfile_read(self, &entry, sizeof(entry), pos) < sizeof(entry))
		return NULL; /* Forced EOF */
	entsize = LETOH16(entry.d_entsize);
	if (entsize <= sizeof(Ext2DiskDirent))
		return NULL; /* End of directory */
	if (!entry.d_ino) {
		pos += entsize;
		goto again; /* Unused entry. */
	}
	if (super->es_feat_required & EXT2_FEAT_REQ_FDIRENT_TYPE) {
		fd_type = DT_UNKNOWN;
		if likely(entry.d_type < COMPILER_LENOF(ext_ft2dt))
			fd_type = ext_ft2dt[entry.d_type];
		fd_namelen = entry.d_namlen_low;
	} else {
		pos_t ino_addr = ext2_inoaddr(super, LETOH32(entry.d_ino));
		le16 ino_type;
		/* Read the directory entry type from its INode. */
		mfile_readall(super->es_super.ffs_super.fs_dev, &ino_type, 2,
		              ino_addr + offsetof(Ext2DiskINode, i_mode));
		fd_type    = IFTODT(LETOH16(ino_type));
		fd_namelen = LETOH16(entry.d_namlen);
	}
	entused = sizeof(Ext2DiskDirent) + fd_namelen;
	if unlikely(entsize < entused) {
		/* Log an error if the directory entry's size doesn't make any sense. */
		printk(KERN_ERR "[ext2] Directory entry at offset %#" PRIx64 " in inode %#" PRIx32 " "
		                "has recuse=%#" PRIx16 " > reclen=%#" PRIx16 "\n",
		       (uint64_t)pos, (uint32_t)self->fn_ino, entused, entsize);
		fd_namelen = entsize - sizeof(Ext2DiskDirent);
	} else if (entsize > entused) {
		/* TODO: In this case,  the trailing `entsize - entused'  bytes of the  directory
		 *       entry can be used to allocate more directory entries. However, according
		 *       to  the specs, only until the start of the next block, and only starting
		 *       at the next 4-byte aligned addr:
		 * >> size_t avail = entsize - entused;                // Available space for next entry (before align)
		 * >> pos_t  strt  = CEIL_ALIGN(pos + entused, 4);     // Lowest aligned starting address of next entry
		 * >> size_t align = (size_t)(strt - (pos + entused)); // # of bytes lost due to alignment
		 * >> if (OVERFLOW_USUB(avail, align, &avail))         // Available space for next entry (after align)
		 * >>     avail = 0;
		 * >> pos_t  end  = CEIL_ALIGN(strt, mfile_getblocksize(self)); // End of block containing next entry
		 * >> size_t free = (size_t)(end - strt);                       // Space in block for next entry
		 * >> if (free > avail)                                         // Limit space until delta to next record
		 * >>     free = avail;
		 * >> INDICATE_AVAILABLE_SPACE_FOR_NEW_ENTRIES(base: strt, num_bytes: free); */
	}

	/* Construct the resulting directory entry. */
	result = _flatdirent_alloc(fd_namelen);
	TRY {
		mfile_readall(self, result->fde_ent.fd_name,
		              fd_namelen * sizeof(char),
		              pos + sizeof(Ext2DiskDirent));
		switch (fd_namelen) {
		case 2:
			if (result->fde_ent.fd_name[1] != '.')
				break;
			ATTR_FALLTHROUGH
		case 1:
			if (result->fde_ent.fd_name[0] != '.')
				break;
			/* Skip `.' and `..' -- Those are emulated by the VFS layer. */
			kfree(result);
			pos += entsize;
			goto again;
		default: break;
		}
	} EXCEPT {
		kfree(result);
		RETHROW();
	}

	/* Fill in missing fields of the new directory entry. */
	result->fde_pos            = pos;
	result->fde_size           = entsize;
	result->fde_ent.fd_ino     = (ino_t)LETOH32(entry.d_ino);
	result->fde_ent.fd_type    = fd_type;
	result->fde_ent.fd_ops     = &flatdirent_ops;
	result->fde_ent.fd_namelen = fd_namelen;
	return result;
}






/************************************************************************/
/* File node operators                                                  */
/************************************************************************/
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ext2iiblock_delete)(struct ext2iiblock *__restrict self,
                                  size_t es_ind_blocksize) {
	size_t i;
	for (i = 0; i < es_ind_blocksize; ++i)
		ext2iblock_free(self->eiib_blocks_c[i]);
	ext2iiblock_free(self);
}
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ext2iiiblock_delete)(struct ext2iiiblock *__restrict self,
                                   size_t es_ind_blocksize) {
	size_t i;
	for (i = 0; i < es_ind_blocksize; ++i) {
		struct ext2iiblock *inner;
		inner = self->eiiib_blocks_c[i];
		if (inner != NULL)
			ext2iiblock_delete(inner, es_ind_blocksize);
	}
	ext2iiiblock_free(self);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ext2idat_fini)(struct ext2idat *__restrict self,
                             size_t es_ind_blocksize) {
	/* Free lazily allocated indirect block tables. */
	if (self->ei_siblock_c)
		ext2iblock_free(self->ei_siblock_c);
	if (self->ei_diblock_c)
		ext2iiblock_delete(self->ei_diblock_c, es_ind_blocksize);
	if (self->ei_tiblock_c)
		ext2iiiblock_delete(self->ei_tiblock_c, es_ind_blocksize);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ext2_reg_v_destroy)(struct mfile *__restrict self) {
	struct ext2regnode *me  = (struct ext2regnode *)mfile_asreg(self);
	struct ext2super *super = fsuper_asext2(me->fn_super);
	ext2idat_fini(&me->ern_fdat, super->es_ind_blocksize);
	fregnode_v_destroy(self);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ext2_lnk_v_destroy)(struct mfile *__restrict self) {
	struct ext2lnknode *me  = (struct ext2lnknode *)mfile_aslnk(self);
	struct ext2super *super = fsuper_asext2(me->fn_super);
	ext2idat_fini(&me->eln_fdat, super->es_ind_blocksize);
	flnknode_v_destroy(self);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ext2_dir_v_destroy)(struct mfile *__restrict self) {
	struct ext2dirnode *me  = (struct ext2dirnode *)mfile_aslnk(self);
	struct ext2super *super = fsuper_asext2(me->fn_super);
	ext2idat_fini(&me->edn_fdat, super->es_ind_blocksize);
	flatdirnode_v_destroy(self);
}

PRIVATE BLOCKING WUNUSED NONNULL((1)) size_t KCALL
ext2_lnk_v_readlink(struct flnknode *__restrict self,
                    USER CHECKED /*utf-8*/ char *buf,
                    size_t bufsize)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	size_t lnksize = (size_t)__atomic64_val(self->mf_filesize);
	if (bufsize > lnksize)
		bufsize = lnksize;
	/* As per the specs, symbolic links with lengths less than 60 (yes: "<" and NOT "<=",
	 * even though symlink texts don't traditionally have trailing NULs, and the in-inode
	 * space  would be enough for 60 characters, even though only up to 59 get saved, but
	 * whatever...)
	 *
	 * ref: linux:/fs/ext2/namei.c:ext2_symlink: `if (l > sizeof (EXT2_I(inode)->i_data))'
	 *      This  condition tests if a newly created symlink is "slow" (that is: it's text
	 *      is not stored  in-line). `l' is  the strlen()+1  of the link's  text, and  the
	 *      other `sizeof (EXT2_I(inode)->i_data))' equates to `60' */
	if (lnksize <= 59) {
		struct ext2idat *idat = self->fn_fsdata;
		memcpy(buf, &idat->ei_dblock, lnksize);
	} else {
		mfile_readall(self, buf, bufsize, 0);
	}
	return lnksize;
}







/************************************************************************/
/* File node operator tables                                            */
/************************************************************************/
PRIVATE struct fregnode_ops const ext2_regops = {
	.rno_node = {
		.no_file = {
			.mo_destroy    = &ext2_reg_v_destroy,
			.mo_loadblocks = &ext2_v_loadblocks,
//TODO:		.mo_saveblocks = &ext2_v_saveblocks,
			.mo_changed    = &fregnode_v_changed,
#ifdef fregnode_v_stream_ops
			.mo_stream     = &fregnode_v_stream_ops,
#endif /* fregnode_v_stream_ops */
		},
		.no_wrattr = &ext2_v_wrattr,
	},
};
PRIVATE struct flatdirnode_ops const ext2_dirops = {
	.fdno_dir = {
		.dno_node = {
			.no_file = {
				.mo_destroy    = &ext2_dir_v_destroy,
				.mo_loadblocks = &ext2_v_loadblocks,
//TODO:			.mo_saveblocks = &ext2_v_saveblocks,
				.mo_changed    = &flatdirnode_v_changed,
				.mo_stream     = &flatdirnode_v_stream_ops,
			},
			.no_wrattr = &ext2_v_wrattr,
		},
		.dno_lookup = &flatdirnode_v_lookup,
		.dno_enum   = &flatdirnode_v_enum,
		.dno_mkfile = &flatdirnode_v_mkfile,
		.dno_unlink = &flatdirnode_v_unlink,
		.dno_rename = &flatdirnode_v_rename,
	},
	.fdno_flat = {
		.fdnx_readdir       = &ext2_dir_v_readdir,
//TODO:	.fdnx_writedir      = &ext2_dir_v_writedir,
//TODO:	.fdnx_deleteent     = &ext2_dir_v_deleteent,
//TODO:	.fdnx_mkfile        = &ext2_dir_v_mkfile,
//TODO:	.fdnx_mkent         = &ext2_dir_v_mkent,
//TODO:	.fdnx_allocfile     = &ext2_dir_v_allocfile,
//TODO:	.fdnx_deletefile    = &ext2_dir_v_deletefile,
//TODO:	.fdnx_direntchanged = &ext2_dir_v_direntchanged,
	},
};
PRIVATE struct flnknode_ops const ext2_lnkops = {
	.lno_node = {
		.no_file = {
			.mo_destroy    = &ext2_lnk_v_destroy,
			.mo_loadblocks = &ext2_v_loadblocks,
//TODO:		.mo_saveblocks = &ext2_v_saveblocks,
			.mo_changed    = &flnknode_v_changed,
#ifdef flnknode_v_stream_ops
			.mo_stream     = &flnknode_v_stream_ops,
#endif /* flnknode_v_stream_ops */
		},
		.no_wrattr = &ext2_v_wrattr,
	},
	.lno_readlink = &ext2_lnk_v_readlink,
};






/************************************************************************/
/* Superblock operator table                                            */
/************************************************************************/
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) struct fnode *KCALL
ext2_super_v_makenode(struct flatsuper *__restrict self,
                      struct flatdirent *__restrict ent,
                      struct flatdirnode *__restrict UNUSED(dir))
		THROWS(E_BADALLOC, E_IOERROR) {
	struct ext2super *super = flatsuper_asext2(self);
	struct fnode *result;
	Ext2DiskINode disk_inode;

	/* Read the on-disk INode */
	pos_t inoaddr = ext2_inoaddr(super, (ext2_ino_t)ent->fde_ent.fd_ino);
	mfile_readall(super->es_super.ffs_super.fs_dev, &disk_inode,
	              super->es_inode_io_size, inoaddr);
	if (!(super->es_feat_mountro & EXT2_FEAT_MRO_FSIZE64))
		disk_inode.i_size_high = HTOLE32(0);

	/* Validate that the on-disk INode type matches what we're expecting. */
	if unlikely(ent->fde_ent.fd_type != IFTODT(LETOH16(disk_inode.i_mode)))
		THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);
	switch (ent->fde_ent.fd_type) {

	case DT_REG: {
		struct ext2regnode *node;
		node = (struct ext2regnode *)kmalloc(sizeof(struct ext2regnode), GFP_NORMAL);
		node->mf_flags  = MFILE_F_NORMAL;
		node->mf_ops    = &ext2_regops.rno_node.no_file;
		node->fn_fsdata = &node->ern_fdat;
		atomic64_init(&node->mf_filesize, (uint64_t)LETOH32(disk_inode.i_size_low) |
		                                  (uint64_t)LETOH32(disk_inode.i_size_high) << 32);
		result = node;
	}	break;

	case DT_DIR: {
		struct ext2dirnode *node;
		node = (struct ext2dirnode *)kmalloc(sizeof(struct ext2dirnode), GFP_NORMAL);
		node->mf_flags  = MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO | MFILE_F_FIXEDFILESIZE;
		node->mf_ops    = &ext2_dirops.fdno_dir.dno_node.no_file;
		node->fn_fsdata = &node->edn_fdat;
		flatdirdata_init(&node->fdn_data);
		atomic64_init(&node->mf_filesize, (uint64_t)-1);
		atomic64_init(&node->edn_1dot, (uint64_t)-1);
		atomic64_init(&node->edn_2dot, (uint64_t)-1);
		result = node;
	}	break;

	case DT_LNK: {
		struct ext2lnknode *node;
		node = (struct ext2lnknode *)kmalloc(sizeof(struct ext2lnknode), GFP_NORMAL);
		node->mf_flags  = MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO | MFILE_F_FIXEDFILESIZE;
		node->mf_ops    = &ext2_lnkops.lno_node.no_file;
		node->fn_fsdata = &node->eln_fdat;
		atomic64_init(&node->mf_filesize, (uint64_t)LETOH32(disk_inode.i_size_low) |
		                                  (uint64_t)LETOH32(disk_inode.i_size_high) << 32);
		result = node;
	}	break;

	default:
		THROW(E_FSERROR_UNSUPPORTED_OPERATION);
	}
	result->mf_parts = NULL;
	SLIST_INIT(&result->mf_changed);
	result->fn_fsdata->ei_inoaddr = inoaddr;
	/* Decode generic INode data. */
	ext2_diskinode_decode(&disk_inode, result, super,
	                      (ext2_ino_t)ent->fde_ent.fd_ino);
	return result;
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ext2_super_v_destroy)(struct mfile *__restrict self) {
	struct ext2super *me = mfile_asext2super(self);
	mman_unmap_kram_and_kfree(me->es_bgroupv,
	                          me->es_bgroupc * sizeof(Ext2DiskBlockGroup),
	                          me->es_freebgroupv);
	ext2idat_fini(&me->es_fdat, me->es_ind_blocksize);
	flatsuper_v_destroy(self);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ext2_super_v_free)(struct fnode *__restrict self) {
	struct ext2super *me = fnode_asext2super(self);
	kfree(me);
}

PRIVATE struct flatsuper_ops const ext2_super_ops = {
	.ffso_makenode = &ext2_super_v_makenode,
	.ffso_super = {
//TODO:	.so_truncate_atime = &ext2_super_v_truncate_atime,
//TODO:	.so_truncate_mtime = &ext2_super_v_truncate_mtime,
//TODO:	.so_truncate_ctime = &ext2_super_v_truncate_ctime,
		.so_fdir = {
			.dno_node = {
				.no_file = {
					.mo_destroy    = &ext2_super_v_destroy,
					.mo_loadblocks = &ext2_v_loadblocks,
//TODO:				.mo_saveblocks = &ext2_v_saveblocks,
					.mo_changed    = &flatsuper_v_changed,
					.mo_stream     = &flatsuper_v_stream_ops,
				},
				.no_free   = &ext2_super_v_free,
				.no_wrattr = &ext2_v_wrattr,
			},
			.dno_lookup = &flatdirnode_v_lookup,
			.dno_enum   = &flatdirnode_v_enum,
			.dno_mkfile = &flatdirnode_v_mkfile,
			.dno_unlink = &flatdirnode_v_unlink,
			.dno_rename = &flatdirnode_v_rename,
		},
	},
	.ffso_flat = {
		.fdnx_readdir    = &ext2_dir_v_readdir,
//TODO:	.fdnx_writedir   = &ext2_dir_v_writedir,
//TODO:	.fdnx_deleteent  = &ext2_dir_v_deleteent,
//TODO:	.fdnx_mkfile     = &ext2_dir_v_mkfile,
//TODO:	.fdnx_mkent      = &ext2_dir_v_mkent,
//TODO:	.fdnx_allocfile  = &ext2_dir_v_allocfile,
//TODO:	.fdnx_deletefile = &ext2_dir_v_deletefile,
	},
};








/************************************************************************/
/* Superblock open                                                      */
/************************************************************************/
PRIVATE BLOCKING WUNUSED NONNULL((1)) struct fsuper *KCALL
ext2_openfs(struct ffilesys *__restrict UNUSED(filesys),
            struct mfile *dev, UNCHECKED USER char *args) {
	struct ext2super *result;
	Ext2DiskSuperblock *desc;
	u32 num_block_groups;
	bool must_mount_ro = false;
	shift_t blockshift;

	/* XXX: Mount arguments? */
	(void)args;

	/* Read the Ext2 disk header. */
#if PAGESIZE >= 256
	if (mfile_getblocksize(dev) <= 256) {
		STATIC_ASSERT((EXT2_SUPERBLOCK_OFFSET % 256) == 0);
		STATIC_ASSERT(sizeof(Ext2DiskSuperblock) > 128 && sizeof(Ext2DiskSuperblock) <= 256);
		desc = (Ext2DiskSuperblock *)aligned_alloca(256, 256);
		mfile_rdblocks(dev, (pos_t)EXT2_SUPERBLOCK_OFFSET,
		               pagedir_translate(desc), 256);
	} else
#endif /* PAGESIZE >= 256 */
	{
		desc = (Ext2DiskSuperblock *)alloca(sizeof(Ext2DiskSuperblock));
		mfile_readall(dev, desc, sizeof(Ext2DiskSuperblock), (pos_t)EXT2_SUPERBLOCK_OFFSET);
	}

	/* Do some basic verification to check if this is really an EXT2 filesystem. */
	if (LETOH16(desc->e_signature) != EXT2_SIGNATURE)
		return NULL;
	if unlikely(LETOH32(desc->e_free_inodes) > LETOH32(desc->e_total_inodes) ||
	            LETOH32(desc->e_free_blocks) > LETOH32(desc->e_total_blocks))
		return NULL;
	if unlikely(!desc->e_blocks_per_group || !desc->e_inodes_per_group)
		return NULL;

	num_block_groups = CEILDIV(LETOH32(desc->e_total_blocks), LETOH32(desc->e_blocks_per_group));

	/* Figure out the block-shift. */
	{
		u32 shift  = LETOH32(desc->e_log2_blocksz);
		blockshift = (shift_t)shift;
		if unlikely(blockshift != (shift_t)shift)
			return NULL;
		if unlikely(OVERFLOW_UADD(blockshift, 10, &blockshift))
			return NULL;
		if unlikely(blockshift >= 24)
			return NULL; /* That would be _way_ too big */
	}

	/* Allocate the FAT superblock controller. */
	result = (struct ext2super *)kmalloc(sizeof(struct ext2super), GFP_NORMAL);
	TRY {
		pos_t bgroup_addr; /* [const] On-disk address of `es_bgroupv'. */
		Ext2DiskINode rootnode;

		/* Fill in (most) ext2-specific superblock fields. */
		result->es_blk_per_bgrp     = LETOH32(desc->e_blocks_per_group);
		result->es_ino_per_bgrp     = LETOH32(desc->e_inodes_per_group);
		result->es_total_blocks     = LETOH32(desc->e_total_blocks);
		result->es_inode_size       = 128;
		result->es_total_inodes     = LETOH32(desc->e_total_inodes);
		result->es_version_maj      = LETOH32(desc->e_version_major);
		result->es_version_min      = LETOH16(desc->e_version_minor);
		result->es_feat_optional    = 0;
		result->es_feat_required    = 0;
		result->es_feat_mountro     = 0;
		result->es_os               = LETOH32(desc->e_os_id);
		result->es_blockshift       = blockshift;
		result->es_blocksize        = (size_t)1 << blockshift;
		result->es_blockmask        = result->es_blocksize - 1;
		result->es_iobalign         = (size_t)1 << dev->mf_iobashift;
		result->es_ind_blocksize    = result->es_blocksize / 4;
		result->es_ind_blocksize_p2 = result->es_ind_blocksize * result->es_ind_blocksize;
		result->es_ind_blocksize_p3 = result->es_ind_blocksize * result->es_ind_blocksize_p2;
		result->es_bgroupc          = num_block_groups;

		if (result->es_version_maj >= 1) {
			result->es_feat_optional = LETOH32(desc->e_feat_optional);
			result->es_feat_required = LETOH32(desc->e_feat_required);
			result->es_feat_mountro  = LETOH32(desc->e_feat_mountro);
			result->es_inode_size    = LETOH16(desc->e_inode_size);

			/* Make sure that the specified INode size isn't too small. */
			if unlikely(result->es_inode_size < 128)
				THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);

			/* Check if we're implementing all the required features.
			 * NOTE: Just to improve compatibility, we treat journaling
			 *       as a mount-ro feature. */
			if (result->es_feat_required & ~(EXT2_FEAT_REQ_FDIRENT_TYPE |
			                                 EXT2_FEAT_REQ_FREPLAY_JOURNAL |
			                                 EXT2_FEAT_REQ_FJOURNAL)) {
				kfree(result);
				return NULL;
			}
			if (result->es_feat_required & (EXT2_FEAT_REQ_FREPLAY_JOURNAL |
			                                EXT2_FEAT_REQ_FJOURNAL))
				must_mount_ro = true;
			if (result->es_feat_mountro & ~(EXT2_FEAT_MRO_FSIZE64))
				must_mount_ro = true;
		}
		result->es_inode_io_size = result->es_inode_size;
		if (result->es_inode_io_size > sizeof(Ext2DiskINode))
			result->es_inode_io_size = sizeof(Ext2DiskINode);

		if (result->es_blockshift <= 10) {
			/* 3rd block (0,1,2) for 1KiB block sizes */
			bgroup_addr = EXT2_BLOCK2ADDR(result, 2);
		} else {
			/* 2nd block (0,1) for 2KiB+ block sizes */
			bgroup_addr = EXT2_BLOCK2ADDR(result, 1);
		}

		/* Map the block group vector. */
		result->es_freebgroupv = mman_unmap_kram_cookie_alloc();
		TRY {
			result->es_bgroupv = (Ext2DiskBlockGroup *)mman_map(/* self:        */ &mman_kernel,
			                                                    /* hint:        */ MHINT_GETADDR(KERNEL_MHINT_DEVICE),
			                                                    /* num_bytes:   */ result->es_bgroupc * sizeof(Ext2DiskBlockGroup),
			                                                    /* prot:        */ PROT_READ | PROT_WRITE | PROT_SHARED | PROT_FORCEWRITE,
			                                                    /* flags:       */ MHINT_GETMODE(KERNEL_MHINT_DEVICE),
			                                                    /* file:        */ dev,
			                                                    /* file_fspath: */ NULL,
			                                                    /* file_fsname: */ NULL,
			                                                    /* file_pos:    */ bgroup_addr);
		} EXCEPT {
			mman_unmap_kram_cookie_free(result->es_freebgroupv);
			RETHROW();
		}

		/* Load+decode the root directory INode */
		TRY {
			result->es_fdat.ei_inoaddr = ext2_inoaddr(result, 2); /* 2: INode number of root directory */
			mfile_readall(dev, &rootnode, result->es_inode_io_size, result->es_fdat.ei_inoaddr);

			/* Decode the root INode */
			result->es_super.ffs_super.fs_root.fn_fsdata = &result->es_fdat; /* Needed for `ext2_diskinode_decode' */
			result->es_super.ffs_super.fs_dev            = dev;              /* Needed for `ext2_diskinode_decode' */
			ext2_diskinode_decode(&rootnode, &result->es_super.ffs_super.fs_root, result, 2);
			if unlikely(!S_ISDIR(result->es_super.ffs_super.fs_root.fn_mode))
				THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);
		} EXCEPT {
			mman_unmap_kram_and_kfree(result->es_bgroupv,
			                          result->es_bgroupc * sizeof(Ext2DiskBlockGroup),
			                          result->es_freebgroupv);
			RETHROW();
		}

		/* Fill in remaining ext2-specific data for the root node. */
		atomic64_init(&result->_es_1dot, (uint64_t)-1);
		atomic64_init(&result->_es_2dot, (uint64_t)-1);
	} EXCEPT {
		kfree(result);
		RETHROW();
	}

	/* Fill in filesystem features. */
	result->es_super.ffs_super.fs_feat.sf_filesizebits = 32;
	if (result->es_feat_mountro & EXT2_FEAT_MRO_FSIZE64)
		result->es_super.ffs_super.fs_feat.sf_filesizebits = 64;
	result->es_super.ffs_super.fs_feat.sf_filesize_max = ((pos_t)1 << result->es_super.ffs_super.fs_feat.sf_filesizebits) - 1;
	result->es_super.ffs_super.fs_feat.sf_symlink_max  = result->es_super.ffs_super.fs_feat.sf_filesize_max;
	result->es_super.ffs_super.fs_feat.sf_uid_max      = (uid_t)UINT16_MAX;
	result->es_super.ffs_super.fs_feat.sf_gid_max      = (gid_t)UINT16_MAX;
	if (result->es_os == EXT2_OS_FLINUX || result->es_os == EXT2_OS_FGNU_HURD) {
		result->es_super.ffs_super.fs_feat.sf_uid_max = (uid_t)UINT32_MAX;
		result->es_super.ffs_super.fs_feat.sf_gid_max = (gid_t)UINT32_MAX;
	}
	result->es_super.ffs_super.fs_feat.sf_link_max           = UINT16_MAX;
	result->es_super.ffs_super.fs_feat.sf_magic              = EXT2_SUPER_MAGIC;
	result->es_super.ffs_super.fs_feat.sf_rec_incr_xfer_size = result->es_blocksize;
	result->es_super.ffs_super.fs_feat.sf_rec_max_xfer_size  = result->es_blocksize;
	result->es_super.ffs_super.fs_feat.sf_rec_min_xfer_size  = result->es_blocksize;
	result->es_super.ffs_super.fs_feat.sf_rec_xfer_align     = (u32)1 << dev->mf_iobashift;
	result->es_super.ffs_super.fs_feat.sf_name_max           = UINT8_MAX;
	if (!(result->es_feat_required & EXT2_FEAT_REQ_FDIRENT_TYPE))
		result->es_super.ffs_super.fs_feat.sf_name_max = UINT16_MAX;

	/* Fill in generic superblock fields. */
	result->es_super.ffs_features = FFLATSUPER_FEAT_NORMAL;
	result->es_super.ffs_super.fs_root.mf_ops    = &ext2_super_ops.ffso_super.so_fdir.dno_node.no_file;
	result->es_super.ffs_super.fs_root.mf_parts  = NULL;
	SLIST_INIT(&result->es_super.ffs_super.fs_root.mf_changed);
	result->es_super.ffs_super.fs_root.mf_iobashift = dev->mf_iobashift;
	result->es_super.ffs_super.fs_root.mf_flags     = MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO | MFILE_F_FIXEDFILESIZE;
	atomic64_init(&result->es_super.ffs_super.fs_root.mf_filesize, (uint64_t)-1);
	result->es_super.ffs_super.fs_root.fn_ino       = (ino_t)2; /* On EXT2 filesystem, the root directory is always Inode number #2 */
	flatdirdata_init(&result->es_super.ffs_rootdata);

	/* If necessary, mount as read-only */
	if (must_mount_ro)
		result->es_super.ffs_super.fs_root.mf_flags |= MFILE_F_READONLY;
	return &result->es_super.ffs_super;
}


PRIVATE struct ffilesys ext2_filesys = {
	.ffs_drv = &drv_self,
	{ .ffs_open = &ext2_openfs },
	.ffs_flags = FFILESYS_F_NORMAL,
	/* .ffs_name = */ "ext2",
};


#ifdef CONFIG_BUILDING_KERNEL_CORE
INTERN ATTR_FREETEXT void KCALL kernel_initialize_ext2_driver(void) {
	ffilesys_register(&ext2_filesys);
}
#else /* CONFIG_BUILDING_KERNEL_CORE */
PRIVATE ATTR_FREETEXT DRIVER_INIT void init(void) {
	ffilesys_register(&ext2_filesys);
}

PRIVATE DRIVER_FINI void fini(void) {
	ffilesys_unregister(&ext2_filesys);
}
#endif /* !CONFIG_BUILDING_KERNEL_CORE */



DECL_END

#else /* CONFIG_USE_NEW_FS */
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/printk.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/byteorder.h>
#include <hybrid/byteswap.h>

#include <asm/crt/confname.h>
#include <linux/magic.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

/**/
#include "ext2.h"

DECL_BEGIN


INTERN void KCALL
Ext2_VReadFromINode(struct inode *__restrict self,
                    CHECKED USER void *buf,
                    size_t bufsize, pos_t pos) {
	(void)self;
	(void)buf;
	(void)bufsize;
	(void)pos;
	THROW(E_NOT_IMPLEMENTED_TODO);
}

INTERN void KCALL
Ext2_VWriteToINode(struct inode *__restrict self,
                   CHECKED USER void const *buf,
                   size_t bufsize, pos_t pos) {
	(void)self;
	(void)buf;
	(void)bufsize;
	(void)pos;
	COMPILER_IMPURE();
	THROW(E_NOT_IMPLEMENTED_TODO);
}

INTERN void KCALL
Ext2_ReadFromINode(struct inode *__restrict self,
                   CHECKED USER void *buf, size_t bufsize,
                   pos_t pos, struct aio_multihandle *__restrict aio) {
	(void)self;
	(void)buf;
	(void)bufsize;
	(void)pos;
	(void)aio;
	COMPILER_IMPURE();
	THROW(E_NOT_IMPLEMENTED_TODO);
}

INTERN void KCALL
Ext2_WriteToINode(struct inode *__restrict self,
                  CHECKED USER void const *buf, size_t bufsize,
                  pos_t pos, struct aio_multihandle *__restrict aio) {
	(void)self;
	(void)buf;
	(void)bufsize;
	(void)pos;
	(void)aio;
	COMPILER_IMPURE();
	THROW(E_NOT_IMPLEMENTED_TODO);
}

INTERN void KCALL
Ext2_ReadFromINodePhys(struct inode *__restrict self,
                       physaddr_t dst, size_t bufsize,
                       pos_t pos, struct aio_multihandle *__restrict aio) {
	(void)self;
	(void)dst;
	(void)bufsize;
	(void)pos;
	(void)aio;
	COMPILER_IMPURE();
	THROW(E_NOT_IMPLEMENTED_TODO);
}

INTERN void KCALL
Ext2_WriteToINodePhys(struct inode *__restrict self,
                      physaddr_t src, size_t bufsize,
                      pos_t pos, struct aio_multihandle *__restrict aio) {
	(void)self;
	(void)src;
	(void)bufsize;
	(void)pos;
	(void)aio;
	COMPILER_IMPURE();
	THROW(E_NOT_IMPLEMENTED_TODO);
}

INTERN void KCALL
Ext2_ReadFromINodeVector(struct inode *__restrict self,
                         struct iov_buffer *__restrict buf, size_t bufsize,
                         pos_t pos, struct aio_multihandle *__restrict aio) {
	(void)self;
	(void)buf;
	(void)bufsize;
	(void)pos;
	(void)aio;
	COMPILER_IMPURE();
	THROW(E_NOT_IMPLEMENTED_TODO);
}

INTERN void KCALL
Ext2_WriteToINodeVector(struct inode *__restrict self,
                        struct iov_buffer *__restrict buf, size_t bufsize,
                        pos_t pos, struct aio_multihandle *__restrict aio) {
	(void)self;
	(void)buf;
	(void)bufsize;
	(void)pos;
	(void)aio;
	COMPILER_IMPURE();
	THROW(E_NOT_IMPLEMENTED_TODO);
}

INTERN void KCALL
Ext2_ReadFromINodeVectorPhys(struct inode *__restrict self,
                             struct iov_physbuffer *__restrict buf, size_t bufsize,
                             pos_t pos, struct aio_multihandle *__restrict aio) {
	(void)self;
	(void)buf;
	(void)bufsize;
	(void)pos;
	(void)aio;
	COMPILER_IMPURE();
	THROW(E_NOT_IMPLEMENTED_TODO);
}

INTERN void KCALL
Ext2_WriteToINodeVectorPhys(struct inode *__restrict self,
                            struct iov_physbuffer *__restrict buf, size_t bufsize,
                            pos_t pos, struct aio_multihandle *__restrict aio) {
	(void)self;
	(void)buf;
	(void)bufsize;
	(void)pos;
	(void)aio;
	COMPILER_IMPURE();
	THROW(E_NOT_IMPLEMENTED_TODO);
}




/* Return a pointer to (and lazily initialize) the block group
 * associated with the given `index'.
 * @assume(index < self->es_bgroupc); */
INTERN ATTR_RETNONNULL WUNUSED Ext2BlockGroup *KCALL
Ext2_Group(Ext2Superblock *__restrict self, ext2_bgroup_t index)
		THROWS(E_IOERROR, E_BADALLOC, E_WOULDBLOCK, E_INTERRUPT) {
	Ext2BlockGroup *result;
	assert(index < self->es_bgroupc);
	result = &self->es_bgroupv[index];
	if (!(ATOMIC_READ(result->bg_flags) & BLOCK_GROUP_FLOADED)) {
		Ext2DiskBlockGroup group;
		block_device_read(self->s_device, &group, sizeof(group),
		                  self->es_bgroups_pos + (index * EXT2_BLOCKGROUP_SIZE));
		sync_write(&result->bg_lock);
		COMPILER_READ_BARRIER();
		if likely(!(ATOMIC_READ(result->bg_flags) & BLOCK_GROUP_FLOADED)) {
			assert(!result->bg_busage);
			assert(!result->bg_iusage);
			/* Fill in the block groups data fields. */
			result->bg_busage_addr = LETOH32(group.bg_busage);
			result->bg_iusage_addr = LETOH32(group.bg_iusage);
			result->bg_inodes      = LETOH32(group.bg_inodes);
			result->bg_free_blocks = LETOH16(group.bg_free_blocks);
			result->bg_free_inodes = LETOH16(group.bg_free_inodes);
			result->bg_num_dirs    = LETOH16(group.bg_num_dirs);
			result->bg_flags |= BLOCK_GROUP_FLOADED;
		}
		sync_endwrite(&result->bg_lock);
	}
	return result;
}

/* Return  the absolute on-disk position of the `Ext2DiskINode'
 * structure used to store descriptor data for the given `ino'. */
INTERN WUNUSED pos_t KCALL
Ext2_InoAddr(Ext2Superblock *__restrict self, ext2_ino_t ino)
		THROWS(E_IOERROR_BADBOUNDS, E_IOERROR, E_BADALLOC, E_WOULDBLOCK, E_INTERRUPT) {
	Ext2BlockGroup *block; pos_t result;
	ext2_bgroup_t group; ext2_ino_t offset;
	if unlikely(ino < 1 || ino > self->es_total_inodes)
		THROW(E_IOERROR_BADBOUNDS);
	group   = EXT2_INO_BGRP_INDEX(self, ino);
	offset  = EXT2_INO_BGRP_OFFSET(self, ino);
	block   = Ext2_Group(self, group);
	result  = EXT2_BLOCK2ADDR(self, block->bg_inodes);
	result += offset * self->es_inode_size;
	return result;
}

#ifndef __INTELLISENSE__
STATIC_ASSERT(sizeof(Ext2DiskINode) == 128);
#endif /* !__INTELLISENSE__ */

/* Read the descriptor for the given `ino' from disk */
INTERN void KCALL
Ext2_ReadINodeDiskDescriptor(Ext2Superblock *__restrict self, ext2_ino_t ino,
                             Ext2DiskINode *__restrict buf)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	pos_t addr;
	addr = Ext2_InoAddr(self, ino);
	block_device_read(self->s_device, buf, 128, addr);
}

/* Write the descriptor for the given `ino' to disk */
INTERN void KCALL
Ext2_WriteINodeDiskDescriptor(Ext2Superblock *__restrict self, ext2_ino_t ino,
                              Ext2DiskINode const *__restrict buf)
		THROWS(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC, ...) {
	pos_t addr;
	addr = Ext2_InoAddr(self, ino);
	block_device_write(self->s_device, buf, 128, addr);
}

INTERN void KCALL
ExtINode_LoadAttr(struct inode *__restrict self) {
	Ext2DiskINode data;
	Ext2Superblock *super;
	struct inode_data *node;
	unsigned int i; mode_t real_mode;
	super = (Ext2Superblock *)self->i_super;
	Ext2_ReadINodeDiskDescriptor(super, (ext2_ino_t)self->i_fileino, &data);
	if ((node = self->i_fsdata) == NULL) {
		/* Lazily allocate INode-specific data. */
		node = (struct inode_data *)kmalloc(sizeof(struct inode_data),
		                                    FS_GFP | GFP_CALLOC);
		self->i_fsdata = node;
	}
	assert(!node->i_siblock);
	assert(!node->i_diblock);
	assert(!node->i_tiblock);
	/* Copy unused, but cached fields. */
	node->i_dtime      = data.i_dtime;
	node->i_flags      = data.i_flags;
	node->i_os1        = data.i_os1;
	node->i_generation = data.i_generation;
	node->i_acl        = data.i_acl;
	node->i_fragment   = data.i_fragment;
	node->i_os2[0]     = data.i_os2[0];
	node->i_os2[1]     = data.i_os2[1];
	node->i_os2[2]     = data.i_os2[2];
	/* Copy block pointers. */
	for (i = 0; i < EXT2_DIRECT_BLOCK_COUNT; ++i)
		node->i_dblock[i] = LETOH32(data.i_dblock[i]);
	node->i_siblock_addr = LETOH32(data.i_siblock);
	node->i_diblock_addr = LETOH32(data.i_diblock);
	node->i_tiblock_addr = LETOH32(data.i_tiblock);
	/* Read general-purpose INode attributes. */
	self->i_filenlink = (nlink_t)LETOH16(data.i_nlink);
	real_mode         = LETOH16(data.i_mode);
	/* Race condition: The file got deleted and another node with the
	 *                 same ID, but of a different type may have been
	 *                 created in the mean time.
	 *                 Handle this case by acting as though the file
	 *                 had been deleted.
	 * (XXX: This  really shouldn't have  happened though, unless user-space
	 *       has manually been writing to the underlying partitions, because
	 *       otherwise the file  should still  be of  the same  type, as  an
	 *       API call going through the  kernel would have marked our  INode
	 *       as deleted,  meaning that  there'd be  no situation  where  its
	 *       attributes could still  be loadable... At  least I think  there
	 *       isn't a way, although this behavior might be allowed?)
	 *       Anyways: Just handle miss-matching INode types as missing files. */
	if ((self->i_filemode & S_IFMT) != (real_mode & S_IFMT))
		THROW(E_FSERROR_FILE_NOT_FOUND);
	self->i_filemode          = real_mode;
	self->i_fileuid           = (uid_t)LETOH16(data.i_uid);
	self->i_filegid           = (gid_t)LETOH16(data.i_gid);
	self->i_filesize          = (pos_t)LETOH32(data.i_size_low);
	self->i_fileatime.tv_sec  = LETOH32(data.i_atime);
	self->i_fileatime.tv_nsec = 0;
	self->i_filemtime.tv_sec  = LETOH32(data.i_mtime);
	self->i_filemtime.tv_nsec = 0;
	self->i_filectime.tv_sec  = LETOH32(data.i_ctime);
	self->i_filectime.tv_nsec = 0;
	node->i_block_count       = LETOH32(data.i_nsectors);

	/* Parse Version-specific fields. */
	if (super->es_feat_mountro & EXT2_FEAT_MRO_FSIZE64)
		self->i_filesize |= (pos_t)((u64)LETOH32(data.i_size_high) << 32);
	/* Parse OS-specific fields. */
	switch (super->es_os) {

	case EXT2_OS_FGNU_HURD:
		self->i_filemode |= LETOH16(data.i_os_hurd.h_mode_high) << 16;
		/* Linux-specific fields are also implemented by HURD, so just fallthrough */
		ATTR_FALLTHROUGH
	case EXT2_OS_FLINUX:
		self->i_fileuid |= LETOH16(data.i_os_linux.l_uid_high) << 16;
		self->i_filegid |= LETOH16(data.i_os_linux.l_gid_high) << 16;
		break;

	default: break;
	}
}

INTERN void KCALL
ExtINode_SaveAttr(struct inode *__restrict self) {
	Ext2DiskINode data;
	unsigned int i;
	Ext2Superblock *super;
	struct inode_data *node = self->i_fsdata;
	assert(node != NULL);
	/* Copy unused, but cached fields. */
	data.i_dtime      = node->i_dtime;
	data.i_flags      = node->i_flags;
	data.i_os1        = node->i_os1;
	data.i_generation = node->i_generation;
	data.i_acl        = node->i_acl;
	data.i_fragment   = node->i_fragment;
	data.i_os2[0]     = node->i_os2[0];
	data.i_os2[1]     = node->i_os2[1];
	data.i_os2[2]     = node->i_os2[2];
	/* Copy block pointers. */
	for (i = 0; i < EXT2_DIRECT_BLOCK_COUNT; ++i)
		data.i_dblock[i] = HTOLE32(node->i_dblock[i]);
	data.i_siblock = HTOLE32(node->i_siblock_addr);
	data.i_diblock = HTOLE32(node->i_diblock_addr);
	data.i_tiblock = HTOLE32(node->i_tiblock_addr);
	/* Write general-purpose INode attributes. */
	data.i_nlink    = HTOLE16((u16)self->i_filenlink);
	data.i_mode     = HTOLE16((u16)self->i_filemode);
	data.i_uid      = HTOLE16((u16)self->i_fileuid);
	data.i_gid      = HTOLE16((u16)self->i_filegid);
	data.i_size_low = HTOLE32((u32)self->i_filesize);
	data.i_atime    = HTOLE32((u32)self->i_fileatime.tv_sec);
	data.i_mtime    = HTOLE32((u32)self->i_filemtime.tv_sec);
	data.i_ctime    = HTOLE32((u32)self->i_filectime.tv_sec);
	data.i_nsectors   = HTOLE32((u32)node->i_block_count);

	super = (Ext2Superblock *)self->i_super;

	/* Parse Version-specific fields. */
	if (super->es_feat_mountro & EXT2_FEAT_MRO_FSIZE64)
		data.i_size_high = HTOLE32((u32)(self->i_filesize >> 32));
	else
		data.i_size_high = (le32)0;

	/* Encode OS-specific fields. */
	switch (super->es_os) {

	case EXT2_OS_FGNU_HURD:
		data.i_os_hurd.h_mode_high = HTOLE16((u16)(self->i_filemode >> 16));
		/* Linux-specific fields are also implemented by HURD, so just fallthrough */
		ATTR_FALLTHROUGH
	case EXT2_OS_FLINUX:
		data.i_os_linux.l_uid_high = HTOLE16((u16)(self->i_fileuid >> 16));
		data.i_os_linux.l_gid_high = HTOLE16((u16)(self->i_filegid >> 16));
		break;

	default: break;
	}

	/* Write the new INode descriptor to disk. */
	Ext2_WriteINodeDiskDescriptor(super,
	                             (ext2_ino_t)self->i_fileino,
	                             &data);
}



PRIVATE void KCALL
free_x2_table(struct block_table_x2 *__restrict self, size_t size) {
	size_t i;
	assert(self->b2_tables);
	for (i = 0; i < size; ++i)
		kfree(self->b2_tables[i]);
	kfree(self->b2_tables);
	kfree(self);
}

PRIVATE void KCALL
free_x3_table(struct block_table_x3 *__restrict self, size_t size) {
	size_t i;
	assert(self->b3_tables);
	for (i = 0; i < size; ++i) {
		if (self->b3_tables[i])
			free_x2_table(self->b3_tables[i], size);
	}
	kfree(self->b3_tables);
	kfree(self);
}

PRIVATE void KCALL
ExtINode_Fini(struct inode *__restrict self) {
	struct inode_data *node;
	node = self->i_fsdata;
	if (node) {
		kfree(node->i_siblock);
		if (node->i_diblock)
			free_x2_table(node->i_diblock, ((Ext2Superblock *)self->i_super)->es_ind_blocksize);
		if (node->i_tiblock)
			free_x3_table(node->i_tiblock, ((Ext2Superblock *)self->i_super)->es_ind_blocksize);
		kfree(node);
	}
}

INTERN REF struct fdirent *KCALL
ExtDir_ReadDir(struct directory_node *__restrict self,
               pos_t *__restrict pentry_pos) {
	Ext2DiskDirent entry;
	u16 entsize, namlen;
	REF struct fdirent *result;
	unsigned char entry_type;
	pos_t entry_pos;
	inode_loadattr(self);
again:
	entry_pos = *pentry_pos;
	Ext2_VReadFromINode(self, &entry, sizeof(Ext2DiskDirent), entry_pos);
	entsize = LETOH16(entry.d_entsize);
	if (entsize <= sizeof(Ext2DiskDirent))
		return NULL; /* End of directory */
	*pentry_pos += entsize;
	if (!entry.d_ino)
		goto again; /* Unused entry. */
	if (((Ext2Superblock *)self->i_super)->es_feat_required & EXT2_FEAT_REQ_FDIRENT_TYPE) {
		entry_type = entry.d_type;
		namlen     = entry.d_namlen_low;
		if ((entsize - sizeof(Ext2DiskDirent)) > 0xff) {
			/* The  filename is longer than 255 characters, and
			 * we only have the least significant 8 bits of its
			 * actual length.
			 * To  deal with this, we must scan ahead and read a byte at every
			 * `entry_pos + sizeof(Ext2Dirent) + entry.d_namlen_low + N * 256'
			 * that is still located below `entry_pos + entsize' until we find
			 * a NUL-character. */
			pos_t name_endpos, name_endpos_max;
			name_endpos = entry_pos;
			name_endpos += sizeof(Ext2DiskDirent);
			name_endpos += entry.d_namlen_low;
			name_endpos += 256 * sizeof(char);
			name_endpos_max = entry_pos;
			name_endpos_max += entsize;
			while (name_endpos < name_endpos_max) {
				char ch;
				Ext2_VReadFromINode(self, &ch, sizeof(char), name_endpos);
				if (!ch)
					break;
				name_endpos += 256 * sizeof(char);
			}
			namlen = (u16)((name_endpos - sizeof(Ext2DiskDirent)) - entry_pos) / sizeof(char);
		}
	} else {
		pos_t ino_addr;
		le16 ino_type;
		ino_addr = Ext2_InoAddr((Ext2Superblock *)self->i_super,
		                        LETOH32(entry.d_ino));
		/* Read the directory entry type from its INode. */
		block_device_read(self->i_super->s_device, &ino_type, 2,
		                  ino_addr + offsetof(Ext2DiskINode, i_mode));
		entry_type = IFTODT(LETOH16(ino_type));
		namlen     = LETOH16(entry.d_namlen);
	}
	/* Construct the resulting directory entry. */
	result = fdirent_alloc(namlen);
	TRY {
		result->de_pos  = entry_pos;
		result->de_ino  = (ino_t)LETOH32(entry.d_ino);
		result->de_type = entry_type;
		/* Read in the directory entry's name. */
		Ext2_VReadFromINode(self,
		                    result->de_name,
		                    namlen * sizeof(char),
		                    entry_pos + sizeof(Ext2DiskDirent));
		switch (namlen) {
		case 2:
			if (result->de_name[1] != '.')
				break;
			ATTR_FALLTHROUGH
		case 1:
			if (result->de_name[0] != '.')
				break;
			/* Skip `.' and `..' -- Those are emulated by the VFS layer. */
			kfree(result);
			goto again;
		default: break;
		}

		/* Ensure NUL-termination, and generate the hash. */
		result->de_hash = fdirent_hash(result->de_name,
		                                       namlen);
	} EXCEPT {
		kfree(result);
		RETHROW();
	}
	return result;
}

INTERN void KCALL
Ext2_ReadSymLink(struct symlink_node *__restrict self) {
	char *text;
	size_t textlen;
	textlen = (size_t)self->i_filesize;
	text    = (char *)kmalloc(textlen * sizeof(char), FS_GFP);
	TRY {
		struct inode_data *node;
		node = self->i_fsdata;
#if 0 /* XXX: ASCII data is usually written in a way that causes this check to succeed, \
       *      but  what about 1 or 2-character links?  This is little endian after all, \
       *      so that would  end up  with a  really small  number that  might be  lower \
       *      that the actual number block blocks...                                    \
       * LATER: From what little I can gather, at some point Ext2 just started placing  \
       *        symlink  data  that  was  small   enough  within  the  INode   itself.  \
       *        Although sources state that prior to  this data was written in  actual  \
       *        blocks,  what  isn't stated  is  anything about  how  to differentiate  \
       *        these two cases other than the link size (which is ambiguous for small  \
       *        links). */
		if (textlen * sizeof(char) <= (EXT2_DIRECT_BLOCK_COUNT + 3) * 4 &&
		    node->i_dblock[0] >= ((Ext2Superblock *)self->i_super)->es_total_blocks)
#else
		if (textlen * sizeof(char) <= (EXT2_DIRECT_BLOCK_COUNT + 3) * 4)
#endif
		{
			/* XXX: Is this really how we discern between the 2 methods?
			 *      Shouldn't  there  be  some kind  of  flag somewhere? */
			memcpy(text, &node->i_dblock, textlen, sizeof(char));
		} else {
			/* Read the symlink text. */
			Ext2_VReadFromINode(self, text, textlen, 0);
		}
	} EXCEPT {
		kfree(text);
		RETHROW();
	}
	/* Save the symlink text in its designated location. */
	self->sl_text = text;
}


INTERN struct inode_type Ext2_DirOps = {
	/*.it_fini = */ &ExtINode_Fini,
	/*.it_attr = */ {
		/*.a_loadattr   = */ &ExtINode_LoadAttr,
		/*.a_saveattr   = */ &ExtINode_SaveAttr,
		/*.a_maskattr   = */ NULL,
		/*.a_clearcache = */ NULL,
	},
	/*.it_file = */ {
		/*.f_read     = */ NULL,
		/*.f_pread    = */ NULL,
		/*.f_readv    = */ NULL,
		/*.f_preadv   = */ NULL,
		/*.f_write    = */ NULL,
		/*.f_pwrite   = */ NULL,
		/*.f_writev   = */ NULL,
		/*.f_pwritev  = */ NULL,
		/*.f_truncate = */ NULL,
	},
	{
		/*.it_directory = */ {
			/*.d_readdir = */ &ExtDir_ReadDir,
			{ NULL },
			/*.d_creat   = */ NULL,
			/*.d_mkdir   = */ NULL,
			/*.d_symlink = */ NULL,
			/*.d_mknod   = */ NULL,
			/*.d_link    = */ NULL,
			/*.d_rename  = */ NULL,
			/*.d_unlink  = */ NULL,
			/*.d_rmdir   = */ NULL,
		}
	}
};

INTERN struct inode_type Ext2_RegOps = {
	/*.it_fini = */ &ExtINode_Fini,
	/*.it_attr = */ {
		/*.a_loadattr   = */ &ExtINode_LoadAttr,
		/*.a_saveattr   = */ &ExtINode_SaveAttr,
		/*.a_maskattr   = */ NULL,
		/*.a_clearcache = */ NULL,
	},
	/*.it_file = */ {
		/*.f_read     = */ &Ext2_ReadFromINode,
		/*.f_pread    = */ &Ext2_ReadFromINodePhys,
		/*.f_readv    = */ &Ext2_ReadFromINodeVector,
		/*.f_preadv   = */ &Ext2_ReadFromINodeVectorPhys,
		/*.f_write    = */ &Ext2_WriteToINode,
		/*.f_pwrite   = */ &Ext2_WriteToINodePhys,
		/*.f_writev   = */ &Ext2_WriteToINodeVector,
		/*.f_pwritev  = */ &Ext2_WriteToINodeVectorPhys,
		/*.f_truncate = */ NULL,
	}
};
INTERN struct inode_type Ext2_DevOps = {
	/*.it_fini = */ &ExtINode_Fini,
	/*.it_attr = */ {
		/*.a_loadattr   = */ &ExtINode_LoadAttr,
		/*.a_saveattr   = */ &ExtINode_SaveAttr,
		/*.a_maskattr   = */ NULL,
		/*.a_clearcache = */ NULL,
	}
};
INTERN struct inode_type Ext2_LnkOps = {
	/*.it_fini = */ &ExtINode_Fini,
	/*.it_attr = */ {
		/*.a_loadattr   = */ &ExtINode_LoadAttr,
		/*.a_saveattr   = */ &ExtINode_SaveAttr,
		/*.a_maskattr   = */ NULL,
		/*.a_clearcache = */ NULL,
	},
	/*.it_file = */ {
		/*.f_read     = */ NULL,
		/*.f_pread    = */ NULL,
		/*.f_readv    = */ NULL,
		/*.f_preadv   = */ NULL,
		/*.f_write    = */ NULL,
		/*.f_pwrite   = */ NULL,
		/*.f_writev   = */ NULL,
		/*.f_pwritev  = */ NULL,
		/*.f_truncate = */ NULL,
	},
	{
		.it_symlink = {
			/*.sl_readlink = */ &Ext2_ReadSymLink,
		}
	}
};




INTERN void KCALL
Ext2_OpenSuperblock(Ext2Superblock *__restrict self, UNCHECKED USER char *args)
		THROWS(E_FSERROR_WRONG_FILE_SYSTEM, E_FSERROR_CORRUPTED_FILE_SYSTEM,
		       E_IOERROR_BADBOUNDS, E_DIVIDE_BY_ZERO, E_OVERFLOW, E_INDEX_ERROR,
		       E_IOERROR, E_SEGFAULT, ...) {
	Ext2DiskSuperblock super;
	u32 num_block_groups, temp;
	bool must_mount_ro = false;
	self->s_features.sf_magic = EXT2_SUPER_MAGIC;

	/* XXX: Mount arguments? */
	(void)args;

	/* Read the Ext2 disk header. */
	block_device_read(self->s_device, &super, sizeof(super),
	                 (pos_t)EXT2_SUPERBLOCK_OFFSET);

	/* Do some basic verification to check if this is really an EXT2 filesystem. */
	if (LETOH16(super.e_signature) != EXT2_SIGNATURE)
		THROW(E_FSERROR_WRONG_FILE_SYSTEM);

	/* Do some validation on the superblock state. */
	if unlikely(LETOH32(super.e_free_inodes) > LETOH32(super.e_total_inodes) ||
	            LETOH32(super.e_free_blocks) > LETOH32(super.e_total_blocks))
		THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);
	if unlikely(!super.e_blocks_per_group || !super.e_inodes_per_group)
		THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);

	num_block_groups = CEILDIV(LETOH32(super.e_total_blocks), LETOH32(super.e_blocks_per_group));
	temp             = CEILDIV(LETOH32(super.e_total_inodes), LETOH32(super.e_inodes_per_group));
	if unlikely(num_block_groups != temp)
		THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);
	if unlikely(!num_block_groups)
		THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);

	_mfile_init_blockshift(self, 10 + LETOH32(super.e_log2_blocksz));
	if unlikely(self->es_blockshift >= PAGESHIFT)
		THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);
	self->es_ind_blocksize = ((size_t)1 << self->es_blockshift) / 4;


#if 1 /* I'm guessing this is  the right answer, but  the wiki really isn't  clear...             \
       * [...] The table is located in the block immediately following the Superblock             \
       *    -> That would mean a fixed partition offset of `2048'                                 \
       * [...] the Block Group Descriptor Table will begin at block 2 [for 1024 bytes per block]. \
       *       For any other block size, it will begin at block 1                                 \
       * I'm going with the later variant here, since that seems to make the most sense. */
	if (self->es_blockshift <= 10)
		self->es_bgroups_pos = EXT2_BLOCK2ADDR(self, 2);
	else {
		self->es_bgroups_pos = EXT2_BLOCK2ADDR(self, 1);
	}
#else
	self->es_bgroups_pos = EXT2_SUPERBLOCK_OFFSET + 1024;
#endif
	self->es_bgroupc  = num_block_groups;
	self->es_ino_per_bgrp = LETOH32(super.e_inodes_per_group);
	self->es_blk_per_bgrp = LETOH32(super.e_blocks_per_group);
	self->es_total_inodes = LETOH32(super.e_total_inodes);
	self->es_total_blocks = LETOH32(super.e_total_blocks);
	self->es_version      = ((u32)LETOH16(super.e_version_major) << 16 |
	                         (u32)LETOH16(super.e_version_minor));
	if (self->es_version >= EXT2_VERSION_1) {
		self->es_feat_optional = LETOH32(super.e_feat_optional);
		self->es_feat_required = LETOH32(super.e_feat_required);
		self->es_feat_mountro  = LETOH32(super.e_feat_mountro);
		self->es_inode_size    = LETOH16(super.e_inode_size);
		/* Make sure that the specified INode size isn't too small. */
		if unlikely(self->es_inode_size < 128)
			THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);

		/* Check if we're implementing all the required features.
		 * NOTE: Just to improve compatibility, we treat journaling
		 *       as a mount-ro feature. */
		if (self->es_feat_required & ~(EXT2_FEAT_REQ_FDIRENT_TYPE |
		                               EXT2_FEAT_REQ_FREPLAY_JOURNAL |
		                               EXT2_FEAT_REQ_FJOURNAL))
			THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);
		if (self->es_feat_required & (EXT2_FEAT_REQ_FREPLAY_JOURNAL |
		                              EXT2_FEAT_REQ_FJOURNAL))
			must_mount_ro = true;
		if (self->es_feat_mountro & ~(EXT2_FEAT_MRO_FSIZE64))
			must_mount_ro = true;
	} else {
		self->es_inode_size = 128;
	}

	/* On EXT2 filesystem, the root directory is always Inode number #2 */
	self->i_fileino = (ino_t)EXT2_ROOT_DIRECTORY_INO;
	self->i_type    = &Ext2_DirOps;

	(void)must_mount_ro; /* TODO */

	/* Allocate Ext2-specific superblock data. */
	self->es_bgroupv = (struct block_group *)kmalloc(num_block_groups *
	                                                sizeof(struct block_group),
	                                                FS_GFP | GFP_CALLOC);
}

INTERN NOBLOCK void
NOTHROW(KCALL Ext2_FinalizeSuperblock)(Ext2Superblock *__restrict self) {
	if (self->es_bgroupv) {
		ext2_bgroup_t i;
		/* Free lazily allocated block group buffers. */
		for (i = 0; i < self->es_bgroupc; ++i) {
			kfree(self->es_bgroupv[i].bg_busage);
			kfree(self->es_bgroupv[i].bg_iusage);
		}
		kfree(self->es_bgroupv);
	}
}

INTERN void KCALL
Ext2_OpenINode(Ext2Superblock *__restrict UNUSED(self),
               struct inode *__restrict node,
               struct directory_node *__restrict UNUSED(parent_directory),
               struct fdirent *__restrict UNUSED(parent_dirent))
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	switch (node->i_filemode & S_IFMT) {

	case S_IFREG:
		node->i_type = &Ext2_RegOps;
		break;

	case S_IFCHR:
	case S_IFBLK:
		node->i_type = &Ext2_DevOps;
		break;

	case S_IFDIR:
		node->i_type = &Ext2_DirOps;
		break;

	case S_IFLNK:
		node->i_type = &Ext2_LnkOps;
		break;

	default:
		/* Throw an unsupported-function error for any other type of node. */
		THROW(E_FSERROR_UNSUPPORTED_OPERATION);
	}
}

INTERN NONNULL((1)) void KCALL
Ext2_StatSuperblock(Ext2Superblock *__restrict self,
                    USER CHECKED struct statfs *result)
		THROWS(E_IOERROR, E_SEGFAULT, ...) {
	(void)self;
	(void)result;
	THROW(E_NOT_IMPLEMENTED_TODO);
}

INTERN void KCALL
Ext2_SynchronizeSuperblock(Ext2Superblock *__restrict self)
		THROWS(E_IOERROR, ...) {
	/* TODO */
	(void)self;
}



INTERN struct superblock_type Ext2_SuperblockType = {
	/*.st_driver            = */ &drv_self,
	/*.st_name              =*/ "ext2",
	/*.st_flags             = */ SUPERBLOCK_TYPE_FNORMAL,
	/*.st_sizeof_superblock = */ sizeof(Ext2Superblock),
	{
		/*.st_open = */ (void(KCALL *)(struct superblock *__restrict, UNCHECKED USER char *))&Ext2_OpenSuperblock
	},
	/*.st_functions = */ {
		/*.f_fini     = */ (void(KCALL *)(struct superblock *__restrict))&Ext2_FinalizeSuperblock,
		/*.f_opennode = */ (void(KCALL *)(struct superblock *__restrict, struct inode *__restrict, struct directory_node *__restrict, struct fdirent *__restrict))&Ext2_OpenINode,
		/*.f_sync     = */ (void(KCALL *)(struct superblock *__restrict, USER CHECKED struct statfs *))&Ext2_StatSuperblock,
		/*.f_sync     = */ (void(KCALL *)(struct superblock *__restrict))&Ext2_SynchronizeSuperblock
	}
};

PRIVATE ATTR_FREETEXT DRIVER_INIT void init(void) {
	register_filesystem_type(&Ext2_SuperblockType);
}
PRIVATE DRIVER_FINI void fini(void) {
	unregister_filesystem_type(&Ext2_SuperblockType);
}


#if 0
PRIVATE ATTR_FREETEXT DRIVER_INIT void init2(void) {
	printk(KERN_DEBUG "ext2fs-- constructor\n");
	printk(KERN_DEBUG "drv_self          = %p\n", &drv_self);
	printk(KERN_DEBUG "d_eh_frame_start  = %p\n", drv_self.d_eh_frame_start);
	printk(KERN_DEBUG "d_eh_frame_end    = %p\n", drv_self.d_eh_frame_end);
	printk(KERN_DEBUG "drv_loadaddr      = %p\n", drv_loadaddr);
	printk(KERN_DEBUG "drv_start         = %p\n", drv_start);
	printk(KERN_DEBUG "drv_end           = %p\n", drv_end);
	printk(KERN_DEBUG "drv_name          = %q\n", drv_name);
	printk(KERN_DEBUG "drv_file          = %p\n", drv_file);
	printk(KERN_DEBUG "drv_commandline   = %q\n", drv_commandline);
	printk(KERN_DEBUG "drv_argc          = %Iu\n", drv_argc);
	for (size_t i = 0; i < drv_argc; ++i)
		printk(KERN_DEBUG "drv_argv[%Iu] = %q\n", i, drv_argv[i]);
}

PRIVATE DRIVER_FINI void fini2(void) {
	printk(KERN_DEBUG "ext2fs destructor\n");
}
#endif


DECL_END
#endif /* !CONFIG_USE_NEW_FS */

#endif /* !GUARD_MODEXT2_EXT2_C */
