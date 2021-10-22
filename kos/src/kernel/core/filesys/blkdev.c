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
#ifndef GUARD_KERNEL_CORE_FILESYS_BLKDEV_C
#define GUARD_KERNEL_CORE_FILESYS_BLKDEV_C 1
#define __WANT_BLKDEV_bd_partinfo__bp_blkdevlop
#define __WANT_FNODE__fn_suplop
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/fs/allnodes.h>
#include <kernel/fs/blkdev.h>
#include <kernel/fs/devfs.h>
#include <kernel/fs/devnode.h>
#include <kernel/fs/ramfs.h>
#include <kernel/fs/super.h>
#include <kernel/malloc.h>
#include <kernel/mman/mfile.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/byteorder.h>
#include <hybrid/byteswap.h>
#include <hybrid/overflow.h>

#include <hw/disk/part/efi.h>
#include <hw/disk/part/mbr.h>
#include <kos/dev.h>
#include <kos/except.h>
#include <kos/except/reason/inval.h>

#include <alloca.h>
#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unicode.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* Assert that string buffers from `blkdev' are big enough for what they're meant to hold. */
STATIC_ASSERT(COMPILER_LENOF(((struct blkdev *)0)->bd_rootinfo.br_mbr_diskuid) >
              COMPILER_LENOF(((struct mbr_sector *)0)->mbr_diskuid));
STATIC_ASSERT(COMPILER_LENOF(((struct blkdev *)0)->bd_partinfo.bp_efi_name) >
              UNICODE_16TO8_MAXBUF(COMPILER_LENOF(((struct efi_partition *)0)->p_name)));

/* Check if 2 given ranges overlap (that is: share at least 1 common address) */
#define RANGE_OVERLAPS(a_min, a_max, b_min, b_max) \
	((a_max) >= (b_min) && (a_min) <= (b_max))


PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC blkpart_remove_from_master_postlop)(Tobpostlockop(blkdev) *__restrict self,
                                                      struct blkdev *__restrict UNUSED(obj)) {
	struct blkdev *me;
	me = container_of(self, struct blkdev, bd_partinfo._bp_blkdevplop);
	blkdev_v_destroy(me);
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(blkdev) *
NOTHROW(LOCKOP_CC blkpart_remove_from_master_lop)(Toblockop(blkdev) *__restrict self,
                                                  struct blkdev *__restrict UNUSED(obj)) {
	/* NOTE: `obj' here points to the original master block-device. */
	struct blkdev *me;
	me = container_of(self, struct blkdev, bd_partinfo._bp_blkdevlop);
	COMPILER_READ_BARRIER();
	if (LIST_ISBOUND(me, bd_partinfo.bp_partlink))
		LIST_REMOVE(me, bd_partinfo.bp_partlink);
	me->bd_partinfo._bp_blkdevplop.oplo_func = &blkpart_remove_from_master_postlop;
	return &me->bd_partinfo._bp_blkdevplop;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL blkpart_v_destroy)(struct mfile *__restrict self) {
	struct blkdev *me = mfile_asblkdev(self);
	REF struct blkdev *master;
	master = me->bd_partinfo.bp_master;

	COMPILER_READ_BARRIER();
	if (LIST_ISBOUND(me, bd_partinfo.bp_partlink)) {
		/* Remove `me' from the master device's list of partitions. */
		if (blkdev_root_partslock_tryacquire(master)) {
			COMPILER_READ_BARRIER();
			if (LIST_ISBOUND(me, bd_partinfo.bp_partlink))
				LIST_REMOVE(me, bd_partinfo.bp_partlink);
			blkdev_root_partslock_release(master);
		} else {
			/* Must make use of lock-ops to do the removal. */
			me->bd_partinfo._bp_blkdevlop.olo_func = &blkpart_remove_from_master_lop;
			oblockop_enqueue(&master->bd_rootinfo.br_partslops, &me->bd_partinfo._bp_blkdevlop);
			_blkdev_root_partslock_reap(master);
			decref_unlikely(master);
			return;
		}
	}

	decref_unlikely(master);
	blkdev_v_destroy(self);
}

PRIVATE NONNULL((1, 5)) void KCALL
blkpart_v_loadblocks(struct mfile *__restrict self, pos_t addr,
                     physaddr_t buf, size_t num_bytes,
                     struct aio_multihandle *__restrict aio) {
	struct blkdev *me = mfile_asblkdev(self);
	struct blkdev *ms = me->bd_partinfo.bp_master;
	addr += me->bd_partinfo.bp_partstart;
	blkdev_rdsectors_async(ms, addr, buf, num_bytes, aio);
}

PRIVATE NONNULL((1, 5)) void KCALL
blkpart_v_saveblocks(struct mfile *__restrict self, pos_t addr,
                     physaddr_t buf, size_t num_bytes,
                     struct aio_multihandle *__restrict aio) {
	struct blkdev *me = mfile_asblkdev(self);
	struct blkdev *ms = me->bd_partinfo.bp_master;
	/* Verify that the master device isn't set to read-only. */
	if unlikely(ms->mf_flags & MFILE_F_READONLY)
		THROW(E_FSERROR_READONLY);
	addr += me->bd_partinfo.bp_partstart;
	blkdev_wrsectors_async(ms, addr, buf, num_bytes, aio);
}


PRIVATE NONNULL((1)) void KCALL
blkpart_v_sync(struct blkdev *__restrict self)
		THROWS(...) {
	struct blkdev *master;
	struct blkdev_ops const *master_ops;
	master     = self->bd_partinfo.bp_master;
	master_ops = blkdev_getops(master);
	if (master_ops->bdo_sync != NULL)
		(*master_ops->bdo_sync)(master);
}

PRIVATE NONNULL((1)) syscall_slong_t KCALL
blkpart_v_ioctl(struct mfile *__restrict self, syscall_ulong_t cmd,
                USER UNCHECKED void *arg, iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, ...) {
	struct blkdev *me = mfile_asblkdev(self);
	struct mfile_stream_ops const *master_stream_ops;
	struct blkdev *master;
	master            = me->bd_partinfo.bp_master;
	master_stream_ops = master->mf_ops->mo_stream;
	if (master_stream_ops != NULL && master_stream_ops->mso_ioctl != NULL)
		return (*master_stream_ops->mso_ioctl)(master, cmd, arg, mode);
	THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
	      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
	      cmd);
}

PRIVATE NONNULL((1)) syscall_slong_t KCALL
blkpart_v_hop(struct mfile *__restrict self, syscall_ulong_t cmd,
              USER UNCHECKED void *arg, iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, ...) {
	struct blkdev *me = mfile_asblkdev(self);
	struct mfile_stream_ops const *master_stream_ops;
	struct blkdev *master;
	master            = me->bd_partinfo.bp_master;
	master_stream_ops = master->mf_ops->mo_stream;
	if (master_stream_ops != NULL && master_stream_ops->mso_hop != NULL)
		return (*master_stream_ops->mso_hop)(master, cmd, arg, mode);
	THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
	      E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND,
	      cmd);
}

PRIVATE NONNULL((1)) REF void *KCALL
blkpart_v_tryas(struct mfile *__restrict self, uintptr_half_t wanted_type)
		THROWS(...) {
	struct blkdev *me = mfile_asblkdev(self);
	struct mfile_stream_ops const *master_stream_ops;
	struct blkdev *master;
	master            = me->bd_partinfo.bp_master;
	master_stream_ops = master->mf_ops->mo_stream;
	if (master_stream_ops != NULL && master_stream_ops->mso_tryas != NULL)
		return (*master_stream_ops->mso_tryas)(master, wanted_type);
	return NULL;
}


/* Only needed for ioctl() and hop(); all other operators
 * are  already  implemented  inherently  via  fallbacks.
 * But since we're here, we also assign `mso_open',  even
 * though that one could have also been left as NULL with
 * the same behavior. */
PRIVATE struct mfile_stream_ops const blkpart_stream_ops = {
	/* NOTE: _DONT_ Implement mmap() as a custom wrapper for the master drive!
	 *
	 * If you do  this, you'll  cause inconsistencies and  problems with  blkdev
	 * documentation encouraging drivers to use `mfile_read()' / `mfile_write()'
	 * for gaining a buffered interface for the purpose of doing I/O with  block
	 * devices.
	 *
	 * Just leave everything as-is. There's no point in pondering about problems
	 * relating  to I/O buffers  of drive master vs  partition. Block device I/O
	 * buffers are already only meant to be used for out-of-band data access, in
	 * which case out-of-band for the master  mustn't be part of out-of-band  of
	 * any  of the partitions (or files within filesystems on those partitions).
	 * If they're used for anything else, something is wrong already. */
	.mso_open  = &mfile_v_open,
	.mso_ioctl = &blkpart_v_ioctl,
	.mso_hop   = &blkpart_v_hop,
	.mso_tryas = &blkpart_v_tryas, /* Shouldn't ever be used, but here for the same of completion */
};

/* Operators used for block device partitions */
PUBLIC struct blkdev_ops const blkpart_ops = {
	.bdo_dev = {
		.do_node = {
			.dno_node = {
				.no_file = {
					.mo_destroy    = &blkpart_v_destroy,
					.mo_loadblocks = &blkpart_v_loadblocks,
					.mo_saveblocks = &blkpart_v_saveblocks,
					.mo_changed    = &fnode_v_changed,
					.mo_stream     = &blkpart_stream_ops,
				},
				.no_wrattr = &blkdev_v_wrattr,
			},
		},
	},
	.bdo_sync = &blkpart_v_sync,
};



/* Helper to destroy the (mostly) initialized parts returned by `blkdev_makeparts()' */
#define blkdev_destroy_incomplete_part(self)                   \
	(decref_nokill((self)->bd_partinfo.bp_master),             \
	 decref_nokill((self)->dv_driver),                         \
	 (self)->dv_dirent ? destroy((self)->dv_dirent) : (void)0, \
	 decref_nokill(&devfs), /* for self->fn_super */           \
	 kfree(self))


PRIVATE NONNULL((1)) void
NOTHROW(FCALL blkdev_destroy_incomplete_parts)(struct blkdev_list const *__restrict self) {
	struct blkdev *dev;
	LIST_FOREACH_SAFE (dev, self, bd_partinfo.bp_partlink) {
		blkdev_destroy_incomplete_part(dev);
	}
}


/* Check if  a given  list  of partitions  contains  at
 * least one that overlaps with the given sector-range. */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL blkdev_list_overlaps)(struct blkdev_list const *__restrict self,
                                    uint64_t newpart_sectormin,
                                    uint64_t newpart_sectormax) {
	struct blkdev *dev;
	LIST_FOREACH (dev, self, bd_partinfo.bp_partlink) {
		uint64_t part_sector_min;
		uint64_t part_sector_max;
		assert(blkdev_ispart(dev));
		part_sector_min = blkdev_part_getsectormin(dev);
		part_sector_max = blkdev_part_getsectormax(dev);
		if (RANGE_OVERLAPS(part_sector_min, part_sector_max,
		                   newpart_sectormin, newpart_sectormax))
			return true;
	}
	return false;
}


struct blkdev_makeparts_info {
	/* New value for `struct blkdev::br_mbr_diskuid' */
	char br_mbr_diskuid[COMPILER_LENOF(((struct blkdev *)0)->bd_rootinfo.br_mbr_diskuid)];

	/* New value for `struct blkdev::br_efi_guid' */
	guid_t br_efi_guid;
};


/* Create a new partition and add  it to the `parts' (in  the
 * proper place), as well as return it. The caller must still
 * initialize the following fields:
 *  - return->_blkdev_dev_ _device_devnode_ _fdevnode_node_ fn_allnodes
 *  - return->_blkdev_dev_ _device_devnode_ _fdevnode_node_ fn_supent
 *  - return->_blkdev_dev_ _device_devnode_ _fdevnode_node_ fn_ino  (as `devfs_devnode_makeino(S_IFBLK, dn_devno)')
 *  - return->_blkdev_dev_ _device_devnode_ dn_devno
 *  - return->_blkdev_dev_ dv_dirent
 *  - return->_blkdev_dev_ dv_byname_node
 *  - return->bd_partinfo.bp_partno
 *  - return->bd_partinfo.bp_mbr_sysno
 *  - return->bd_partinfo.bp_efi_name
 *  - return->bd_partinfo.bp_active
 *  - return->bd_partinfo.bp_efi_typeguid
 *  - return->bd_partinfo.bp_efi_partguid */
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct blkdev *FCALL
blkdev_makeparts_create(struct blkdev *__restrict self,
                        struct blkdev_list *__restrict parts,
                        uint64_t part_sectormin,
                        uint64_t part_sectorcnt) {
	struct blkdev *dev;
	/* Must allocate as LOCKED since may end up being used for SWAP */
	dev = (struct blkdev *)kmalloc(offsetafter(struct blkdev, bd_partinfo),
	                               GFP_LOCKED | GFP_PREFLT);
	__blkdev_init_common(dev, &blkpart_ops);
	dev->mf_blockshift = self->mf_blockshift;
	dev->mf_part_amask = self->mf_part_amask;
	atomic64_init(&dev->mf_filesize, part_sectorcnt << self->mf_blockshift);
	dev->dv_dirent = NULL; /* Initialized later, but set to NULL (for now) for error cleanup. */
	dev->fn_mode   = self->fn_mode;
	dev->dv_driver = incref(self->dv_driver); /* Technically, we could also use `kernel_driver' here... */
	assert(S_ISBLK(self->fn_mode));

	/* Fill in part information. */
	dev->bd_partinfo.bp_master    = (REF struct blkdev *)incref(self);
	dev->bd_partinfo.bp_partstart = (pos_t)part_sectormin << self->mf_blockshift;

	/* sorted-insert into the list of parts. */
	{
		struct blkdev **pnext, *next;
		pnext = LIST_PFIRST(parts);
		while ((next = *pnext) != NULL &&
		       next->bd_partinfo.bp_partstart < part_sectormin)
			pnext = LIST_PNEXT(next, bd_partinfo.bp_partlink);
		LIST_P_INSERT_BEFORE(pnext, dev, bd_partinfo.bp_partlink);
	}

	/* Return the new device to the caller. */
	return dev;
}



/* Try  to decode EFI partitions. If the pointed sector(s) don't actually
 * contain a proper EFI partition table, return `false'. Otherwise, parse
 * the table and create partitions. */
PRIVATE ATTR_NOINLINE NONNULL((1, 2, 3)) bool FCALL
blkdev_makeparts_loadefi(struct blkdev *__restrict self,
                         struct blkdev_list *__restrict parts,
                         struct blkdev_makeparts_info *__restrict info,
                         uint64_t efipart_sectormin,
                         uint64_t efipart_sectorcnt) {
	struct efi_descriptor *efi;
	pos_t efi_pos;
	uint32_t efi_hdrsize;
	uint32_t efi_entcnt;
	uint32_t efi_entsize;
	pos_t efi_entbase;

	/* Read the EFI table */
	efi_pos = (pos_t)efipart_sectormin << blkdev_getsectorshift(self);
	if likely(blkdev_getsectorsize(self) == sizeof(struct mbr_sector)) {
		STATIC_ASSERT(sizeof(struct efi_descriptor) <= sizeof(struct mbr_sector));
		STATIC_ASSERT(sizeof(struct efi_partition) <= sizeof(struct mbr_sector));
		efi = (struct efi_descriptor *)aligned_alloca(sizeof(struct mbr_sector),
		                                              sizeof(struct mbr_sector));
		blkdev_rdsectors(self, efi_pos, pagedir_translate(efi), sizeof(struct mbr_sector));
	} else {
		efi = (struct efi_descriptor *)alloca(sizeof(struct efi_descriptor));
		mfile_read(self, efi, sizeof(struct efi_descriptor), efi_pos);
	}

	/* Validate the EFI signature magic. */
	if unlikely(efi->gpt_signature[0] != EFIMAG0)
		goto fail_badsig;
	if unlikely(efi->gpt_signature[1] != EFIMAG1)
		goto fail_badsig;
	if unlikely(efi->gpt_signature[2] != EFIMAG2)
		goto fail_badsig;
	if unlikely(efi->gpt_signature[3] != EFIMAG3)
		goto fail_badsig;
	if unlikely(efi->gpt_signature[4] != EFIMAG4)
		goto fail_badsig;
	if unlikely(efi->gpt_signature[5] != EFIMAG5)
		goto fail_badsig;
	if unlikely(efi->gpt_signature[6] != EFIMAG6)
		goto fail_badsig;
	if unlikely(efi->gpt_signature[7] != EFIMAG7)
		goto fail_badsig;

	/* Save partition GUID */
	memcpy(&info->br_efi_guid, &efi->gpt_guid, sizeof(guid_t));

	printk(KERN_INFO "[blk] EFI partition found at %#" PRIx64 "...%#" PRIx64 " on "
	                 "%.2" PRIxN(__SIZEOF_MAJOR_T__) ":"
	                 "%.2" PRIxN(__SIZEOF_MINOR_T__) " (%q)\n",
	       efipart_sectormin, efipart_sectormin + efipart_sectorcnt - 1,
	       MAJOR(self->dn_devno), MINOR(self->dn_devno),
	       device_getname(self));
	efi_hdrsize = LETOH32(efi->gpt_hdrsize);
	if unlikely(efi_hdrsize < offsetafter(struct efi_descriptor, gpt_partition_count))
		goto fail_hdr_toosmall;

	/* Substitute missing members. */
	if (efi_hdrsize < offsetafter(struct efi_descriptor, gpt_partition_entsz))
		efi->gpt_partition_entsz = HTOLE32(128);
	efi_entsize = LETOH32(efi->gpt_partition_entsz);
	if unlikely(efi_entsize < offsetafter(struct efi_partition, p_part_end))
		goto fail_ent_toosmall;

	efi_entbase = (pos_t)LETOH64(efi->gpt_partition_start);
	if (((efi_entbase >> blkdev_getsectorshift(self)) << blkdev_getsectorshift(self)) != efi_entbase)
		goto fail_bad_partition_vector;
	efi_entcnt = LETOH32(efi->gpt_partition_count);

	/* Load EFI partition entries. */
	for (; efi_entcnt; --efi_entcnt, efi_entbase += efi_entsize) {
		struct blkdev *dev;
		struct efi_partition part;
		uint64_t lba_min, lba_max, part_flags;
		char16_t part_name[COMPILER_LENOF(part.p_name)];
		unsigned int i;
		size_t part_name_len;

		/* Load the EFI partition descriptor from disk. */
		if likely(blkdev_getsectorsize(self) == sizeof(struct mbr_sector)) {
			size_t offset, avail;
			size_t sector_size  = blkdev_getsectorsize(self);
			pos_t efi_entsector = efi_entbase & ~(sector_size - 1);
			if (efi_pos != efi_entsector) {
				blkdev_rdsectors(self, efi_pos, pagedir_translate(efi), sizeof(struct mbr_sector));
				efi_pos = efi_entsector;
			}
			offset = (size_t)efi_entbase & (sector_size - 1);
			avail  = sector_size - offset;
			if (avail >= efi_entsize) {
				memcpy((byte_t *)&part, (byte_t *)efi + offset, efi_entsize);
			} else {
				/* Entry is split across multiple sectors. */
				size_t missing = efi_entsize - avail;
				memcpy((byte_t *)&part, (byte_t *)efi + offset, avail);
				efi_pos = efi_entsector + sector_size;
				blkdev_rdsectors(self, efi_pos, pagedir_translate(efi), sizeof(struct mbr_sector));
				memcpy((byte_t *)&part + avail, (byte_t *)efi, missing);
			}
		} else {
			mfile_read(self, &part, efi_entsize, efi_entbase);
		}

		/* At this point, the partition in question was loaded into `part'.
		 * Time to decode information. */
		lba_min    = LETOH64(part.p_part_min);
		lba_max    = LETOH64(part.p_part_end) - 1;
		part_flags = LETOH64(part.p_flags);
		if (efi_entsize < offsetafter(struct efi_partition, p_flags))
			part_flags = 0; /* Don't have flags */
		part_name_len = 0;
		if (efi_entsize > offsetof(struct efi_partition, p_name)) {
			part_name_len = (efi_entsize - offsetof(struct efi_partition, p_name)) / 2;
			if (part_name_len > COMPILER_LENOF(part.p_name))
				part_name_len = COMPILER_LENOF(part.p_name);
		}
		for (i = 0; i < part_name_len; ++i)
			part_name[i] = (char16_t)LETOH16(part.p_name[i]);

		/* Truncate LBA addresses based on block-shift. This is to make sure
		 * that all addresses can be  expressed as absolute byte  positions.
		 *
		 * Since pos_t is 64-bit, and `lba_*' variables are too, we don't need
		 * to do any additional casts here! */
		lba_min <<= blkdev_getsectorshift(self);
		lba_min >>= blkdev_getsectorshift(self);
		lba_max <<= blkdev_getsectorshift(self);
		lba_max >>= blkdev_getsectorshift(self);

		/* Verify partition info. */
		if (lba_min > lba_max) {
			if (lba_min == lba_max + 1)
				continue; /* Empty partition (allowed and ignored) */
			printk(KERN_ERR "[blk] EFI partition from EFI table in %#" PRIx64 "...%#" PRIx64 " on "
			                "%.2" PRIxN(__SIZEOF_MAJOR_T__) ":"
			                "%.2" PRIxN(__SIZEOF_MINOR_T__) " (%q) "
			                "ends at %" PRIu64 " before it starts at %" PRIu64 "\n",
			       efipart_sectormin, efipart_sectormin + efipart_sectorcnt - 1,
			       MAJOR(self->dn_devno), MINOR(self->dn_devno), device_getname(self),
			       lba_max + 1, lba_min);
			continue;
		}
		if (blkdev_list_overlaps(parts, lba_min, lba_max)) {
			printk(KERN_WARNING "[blk] EFI Partition of %q overlaps with another partition ("
			                    "part:%#" PRIx64 "-%#" PRIx64 ")\n",
			       device_getname(self), lba_min, lba_max);
			continue;
		}

		/* Create a new partition */
		dev = blkdev_makeparts_create(self, parts, lba_min, (lba_max - lba_min) + 1);

		/* Fill in partition information. */
		dev->bd_partinfo.bp_mbr_sysno = 0;
		*unicode_16to8(dev->bd_partinfo.bp_efi_name, part_name, part_name_len) = '\0';
#if EFI_PART_F_ACTIVE <= 0xff
		dev->bd_partinfo.bp_active = (part_flags & EFI_PART_F_ACTIVE);
#else /* EFI_PART_F_ACTIVE <= 0xff */
		dev->bd_partinfo.bp_active = (part_flags & EFI_PART_F_ACTIVE) != 0;
#endif /* EFI_PART_F_ACTIVE > 0xff */
		if (part_flags & EFI_PART_F_READONLY)
			dev->mf_flags |= MFILE_F_READONLY; /* Sure: let's respect this flag! */
		memcpy(&dev->bd_partinfo.bp_efi_typeguid, &part.p_type_guid, sizeof(guid_t));
		memcpy(&dev->bd_partinfo.bp_efi_partguid, &part.p_part_guid, sizeof(guid_t));
	}

	return true;
fail_bad_partition_vector:
	printk(KERN_ERR "[blk] EFI partition table address in %#" PRIx64 "...%#" PRIx64 " on "
	                "%.2" PRIxN(__SIZEOF_MAJOR_T__) ":"
	                "%.2" PRIxN(__SIZEOF_MINOR_T__) " (%q) overflows "
	                "(sector %" PRIu64 " * %" PRIuSIZ " bytes per sector)\n",
	       efipart_sectormin, efipart_sectormin + efipart_sectorcnt - 1,
	       MAJOR(self->dn_devno), MINOR(self->dn_devno),
	       device_getname(self), efi_entbase, blkdev_getsectorsize(self));
	return false;
fail_ent_toosmall:
	printk(KERN_ERR "[blk] EFI partition entires in %#" PRIx64 "...%#" PRIx64 " on "
	                "%.2" PRIxN(__SIZEOF_MAJOR_T__) ":"
	                "%.2" PRIxN(__SIZEOF_MINOR_T__) " (%q) are too small (%" PRIu32 " bytes)\n",
	       efipart_sectormin, efipart_sectormin + efipart_sectorcnt - 1,
	       MAJOR(self->dn_devno), MINOR(self->dn_devno),
	       device_getname(self), efi_entsize);
	return false;
fail_hdr_toosmall:
	printk(KERN_ERR "[blk] EFI header table at %#" PRIx64 "...%#" PRIx64 " on "
	                "%.2" PRIxN(__SIZEOF_MAJOR_T__) ":"
	                "%.2" PRIxN(__SIZEOF_MINOR_T__) " (%q) is too small (%" PRIu32 " bytes)\n",
	       efipart_sectormin, efipart_sectormin + efipart_sectorcnt - 1,
	       MAJOR(self->dn_devno), MINOR(self->dn_devno),
	       device_getname(self), efi_hdrsize);
	return false;
fail_badsig:
	printk(KERN_WARNING "[blk] Invalid EFI signature in EFI partition at "
	                    "%#" PRIx64 "...%#" PRIx64 " on "
	                    "%.2" PRIxN(__SIZEOF_MAJOR_T__) ":"
	                    "%.2" PRIxN(__SIZEOF_MINOR_T__) " (%q)\n",
	       efipart_sectormin, efipart_sectormin + efipart_sectorcnt - 1,
	       MAJOR(self->dn_devno), MINOR(self->dn_devno),
	       device_getname(self));
	return false;
}



/* Forward declaration... */
PRIVATE ATTR_NOINLINE NONNULL((1, 2)) void FCALL
blkdev_makeparts_loadmbr(struct blkdev *__restrict self,
                         struct blkdev_list *__restrict parts,
                         struct blkdev_makeparts_info *info,
                         uint64_t subpart_sectormin,
                         uint64_t subpart_sectorcnt);

PRIVATE NONNULL((1, 2, 4)) void FCALL
blkdev_makeparts_from_mbr(struct blkdev *__restrict self,
                          struct blkdev_list *__restrict parts,
                          struct blkdev_makeparts_info *info,
                          struct mbr_sector const *__restrict mbr,
                          uint64_t subpart_sectormin,
                          uint64_t subpart_sectorcnt) {
	unsigned int i;
	uint64_t subpart_sectormax;
	assert(subpart_sectorcnt != 0);
	subpart_sectormax = subpart_sectormin + subpart_sectorcnt - 1;

	/* Verify the MBR "valid bootsector" signature  */
	if unlikely(mbr->mbr_sig[0] != MBR_SIG0)
		return;
	if unlikely(mbr->mbr_sig[1] != MBR_SIG1)
		return;

	/* Save MBR's "diskuid" (and strip leading/trailing spaces) */
	{
		char *writer;
		writer = (char *)mempcpy(info->br_mbr_diskuid, mbr->mbr_diskuid, sizeof(mbr->mbr_diskuid));
		*writer = '\0';
		writer = strend(info->br_mbr_diskuid);
		while (writer > info->br_mbr_diskuid && isspace(writer[-1]))
			--writer;
		while (info->br_mbr_diskuid[0] && isspace(info->br_mbr_diskuid[0])) {
			memmovedown(&info->br_mbr_diskuid[0], &info->br_mbr_diskuid[1],
			            COMPILER_LENOF(info->br_mbr_diskuid) - 1,
			            sizeof(char));
		}
	}

	/* Load MBR partitions. */
	for (i = 0; i < COMPILER_LENOF(mbr->mbr_part); ++i) {
		/* NOTE: LBA is ADDR >> blkdev_getsectorshift(self) */
		uint64_t lba_min, lba_max, lba_cnt;
		if (mbr->mbr_part[i].pt.pt_sysid == MBR_SYSID_UNUSED)
			continue; /* Unused partition */
		if (mbr_partition_is48(&mbr->mbr_part[i])) {
			lba_min = LETOH32(mbr->mbr_part[i].pt_48.pt_lbastart);
			lba_min |= LETOH16(mbr->mbr_part[i].pt_48.pt_lbastarthi) << 32;
			lba_cnt = LETOH32(mbr->mbr_part[i].pt_48.pt_lbasize);
			lba_cnt |= LETOH16(mbr->mbr_part[i].pt_48.pt_lbasizehi) << 32;
		} else {
			lba_min = LETOH32(mbr->mbr_part[i].pt_32.pt_lbastart);
			lba_cnt = LETOH32(mbr->mbr_part[i].pt_32.pt_lbasize);
		}
		if unlikely(!lba_cnt) {
			bool has_other_partitions;
			/* Check if this is a whole-disk partition. */
			if (i != 0)
				continue; /* Nope... */
			has_other_partitions = false;
			for (i = 1; i < 4; ++i) {
				if (mbr_partition_is48(&mbr->mbr_part[i])
				    ? (mbr->mbr_part[i].pt_32.pt_lbasize != (__le32)0)
				    : (mbr->mbr_part[i].pt_48.pt_lbasize != (__le32)0 ||
				       mbr->mbr_part[i].pt_48.pt_lbasizehi != (__le16)0)) {
					has_other_partitions = true;
					break;
				}
			}
			if (has_other_partitions)
				continue;
			/* It is a whole-disk partition! */
			lba_cnt = subpart_sectorcnt - lba_min;
		}

		/* Adjust LBA addresses for sub-partition base */
		if unlikely(OVERFLOW_UADD(lba_min, subpart_sectormin, &lba_min))
			continue; /* Overflow */
		if unlikely(OVERFLOW_UADD(lba_min, lba_cnt - 1, &lba_max))
			lba_max = (uint64_t)-1;
		if unlikely(lba_max > subpart_sectormax) {
			printk(KERN_WARNING "[blk] MBR Partition #%u of %q expands past the end of the disk ("
			                    "part:%#" PRIx64 "-%#" PRIx64 ","
			                    "disk:%#" PRIx64 "-%#" PRIx64 ") (truncate it)\n",
			       i, device_getname(self), lba_min, lba_max,
			       subpart_sectormin, subpart_sectormax);
			lba_max = subpart_sectormax;
		}

		/* Truncate LBA addresses based on block-shift. This is to make sure
		 * that all addresses can be  expressed as absolute byte  positions.
		 *
		 * Since pos_t is 64-bit, and `lba_*' variables are too, we don't need
		 * to do any additional casts here! */
		lba_min <<= blkdev_getsectorshift(self);
		lba_min >>= blkdev_getsectorshift(self);
		lba_max <<= blkdev_getsectorshift(self);
		lba_max >>= blkdev_getsectorshift(self);
		lba_cnt = (lba_max - lba_min) + 1;

		/* Prevent negative-sized partitions */
		if unlikely(lba_min >= lba_max)
			continue;

		/* Verify that no other partition overlaps with this one. */
		if unlikely(blkdev_list_overlaps(parts, lba_min, lba_max)) {
			printk(KERN_WARNING "[blk] MBR Partition #%u of %q overlaps with another partition ("
			                    "part:%#" PRIx64 "-%#" PRIx64 ","
			                    "disk:%#" PRIx64 "-%#" PRIx64 ")\n",
			       i, device_getname(self), lba_min, lba_max,
			       subpart_sectormin, subpart_sectormax);
			continue;
		}

		/* Process the partition */
		switch (mbr->mbr_part[i].pt.pt_sysid) {

		case MBR_SYSID_EXT:
		case MBR_SYSID_EXT_ALT:
			/* Recursively load+parse an MBR */
			blkdev_makeparts_loadmbr(self, parts, NULL, lba_min, lba_cnt);
			break;

		case MBR_SYSID_EFI:
			if (info != NULL &&
			    blkdev_makeparts_loadefi(self, parts, info, lba_min, lba_cnt))
				break;
			/* Not a valid EFI partition; fall through to creating a normal partition. */
			ATTR_FALLTHROUGH
		default: {
			struct blkdev *dev;
			/* Create a normal MBR partition */
			dev = blkdev_makeparts_create(self, parts, lba_min, lba_cnt);

			/* Fill in partition information. */
			dev->bd_partinfo.bp_mbr_sysno = mbr->mbr_part[i].pt.pt_sysid;
			DBG_memset(dev->bd_partinfo.bp_efi_name, 0xcc, sizeof(dev->bd_partinfo.bp_efi_name));
			dev->bd_partinfo.bp_efi_name[0] = '\0';
			dev->bd_partinfo.bp_active      = mbr->mbr_part[i].pt.pt_bootable & PART_BOOTABLE_ACTICE;
			memset(&dev->bd_partinfo.bp_efi_typeguid, 0, sizeof(guid_t));
			memset(&dev->bd_partinfo.bp_efi_partguid, 0, sizeof(guid_t));
		}	break;

		}
	}
}

PRIVATE ATTR_NOINLINE NONNULL((1, 2)) void FCALL
blkdev_makeparts_loadmbr(struct blkdev *__restrict self,
                         struct blkdev_list *__restrict parts,
                         struct blkdev_makeparts_info *info,
                         uint64_t subpart_sectormin,
                         uint64_t subpart_sectorcnt) {
	struct mbr_sector *mbr;
	pos_t mbr_pos;

	/* Read the MBR */
	mbr_pos = (pos_t)subpart_sectormin << blkdev_getsectorshift(self);
	if likely(blkdev_getsectorsize(self) == sizeof(struct mbr_sector)) {
		mbr = (struct mbr_sector *)aligned_alloca(sizeof(struct mbr_sector),
		                                          sizeof(struct mbr_sector));
		blkdev_rdsectors(self, mbr_pos, pagedir_translate(mbr), sizeof(struct mbr_sector));
	} else {
		mbr = (struct mbr_sector *)alloca(sizeof(struct mbr_sector));
		mfile_read(self, mbr, sizeof(struct mbr_sector), mbr_pos);
	}

	/* Parse the MBR */
	blkdev_makeparts_from_mbr(self, parts, info, mbr,
	                          subpart_sectormin,
	                          subpart_sectorcnt);
}



/* Generate a list of partitions by reading MSB/EFI headers.
 * The following fields are left uninitialized for each of the returned devices:
 *  - self->_blkdev_dev_ _device_devnode_ _fdevnode_node_ fn_allnodes
 *  - self->_blkdev_dev_ _device_devnode_ _fdevnode_node_ fn_supent
 *  - self->_blkdev_dev_ dv_byname_node
 *  - self->bd_partinfo.bp_partlink     (Because of this, you must cannot just decref() these devices,
 *                                       must instead use `blkdev_destroy_incomplete_part()' if  you
 *                                       come into a situation where these new devices must go away) */
PRIVATE WUNUSED NONNULL((1, 2)) struct REF blkdev_list FCALL
blkdev_makeparts(struct blkdev *__restrict self,
                 struct blkdev_makeparts_info *__restrict info) {
	struct REF blkdev_list result;
	LIST_INIT(&result);

	/* Default to no additional information. */
	memset(info, 0, sizeof(*info));

	/* This should never fail, but is required for `blkdev_makeparts_from_mbr()'
	 * being allowed to assume that  its given `subpart_sectorcnt' is  non-zero! */
	if likely(blkdev_getsectorcount(self) != 0) {
		TRY {
			struct blkdev *part;
			struct fdevfsdirent *bname;
			minor_t index;

			/* Load+parse the MBR */
			blkdev_makeparts_loadmbr(self, &result, info, 0,
			                         blkdev_getsectorcount(self));

			/* Assign indices partition indices and dev_t-s. The functions above
			 * will have also added elements onto the list such that it was kept
			 * sorted. */
			bname = self->dv_dirent;
			index = 0;
			LIST_FOREACH (part, &result, bd_partinfo.bp_partlink) {
				REF struct fdevfsdirent *devname;
				char *writer;
#if __SIZEOF_MINOR_T__ == 4
				char numbuf[sizeof("4294967295")];
#elif __SIZEOF_MINOR_T__ == 8
				char numbuf[sizeof("18446744073709551615")];
#else /* __SIZEOF_MINOR_T__ == ... */
#error "Unsupported sizeof(minor_t)"
#endif /* __SIZEOF_MINOR_T__ != ... */
				size_t numlen, namlen;

				part->bd_partinfo.bp_partno = index;
				part->dn_devno = self->dn_devno + MKDEV(0, index);
				part->fn_ino   = devfs_devnode_makeino(S_IFBLK, part->dn_devno);
				++index;

				/* Allocate and assign `part->dv_dirent' */
				numlen = sprintf(numbuf, "%" PRIuN(__SIZEOF_MINOR_T__), index);
				namlen = bname->fdd_dirent.fd_namelen + numlen;

				devname = (REF struct fdevfsdirent *)kmalloc(offsetof(struct fdevfsdirent,
				                                                      fdd_dirent.fd_name) +
				                                             (namlen + 1) * sizeof(char),
				                                             GFP_NORMAL);
				awref_init(&devname->fdd_dev, part);
				devname->fdd_dirent.fd_refcnt  = 1; /* +1: part->dv_dirent */
				devname->fdd_dirent.fd_ops     = &fdevfsdirent_ops;
				devname->fdd_dirent.fd_ino     = part->fn_ino;
				devname->fdd_dirent.fd_namelen = (u16)namlen;
				devname->fdd_dirent.fd_type    = DT_BLK;

				/* Put together the name. */
				writer = devname->fdd_dirent.fd_name;
				writer = (char *)mempcpy(writer, bname->fdd_dirent.fd_name,
				                         bname->fdd_dirent.fd_namelen, sizeof(char));
				writer = (char *)mempcpy(writer, numbuf, numlen, sizeof(char));
				/* NUL-terminate */
				*writer = '\0';

				/* Calculate the hash for the name. */
				devname->fdd_dirent.fd_hash = fdirent_hash(devname->fdd_dirent.fd_name,
				                                           devname->fdd_dirent.fd_namelen);

				/* Inherit reference */
				part->dv_dirent = devname;
			}
		} EXCEPT {
			/* Destroy parts already created. */
			blkdev_destroy_incomplete_parts(&result);
			RETHROW();
		}
	}
	return result;
}


/* Acquire locks needed for reparting:
 * - self->bd_rootinfo.br_partslock
 * - devfs_byname_lock
 * - devfs.rs_sup.fs_nodeslock
 * - devfs.rs_dat.rdd_treelock  // read-only
 * - fallnodes_lock */
PRIVATE NONNULL((1)) void FCALL
blkdev_repart_locks_acquire(struct blkdev *__restrict self)
		THROWS(E_WOULDBLOCK) {
again:
	/* self->bd_rootinfo.br_partslock... */
	blkdev_root_partslock_acquire(self);

	/* devfs_byname_lock... */
	if (!devfs_byname_trywrite()) {
		blkdev_root_partslock_release(self);
		devfs_byname_write();
		devfs_byname_endwrite();
		goto again;
	}

	/* devfs.rs_sup.fs_nodeslock... */
	if (!fsuper_nodes_trywrite(&devfs)) {
		_blkdev_root_partslock_release(self);
		_devfs_byname_endwrite();
		blkdev_root_partslock_reap(self);
		devfs_byname_reap();
		while (!fsuper_nodes_canwrite(&devfs))
			task_yield();
		goto again;
	}

	/* This is needed to prevent instances of `fnode_add2sup_lop()' */
	if unlikely(fsuper_nodes_mustreap(&devfs)) {
		_fsuper_nodes_endwrite(&devfs);
		_blkdev_root_partslock_release(self);
		_devfs_byname_endwrite();
		_fsuper_nodes_reap(&devfs);
		blkdev_root_partslock_reap(self);
		devfs_byname_reap();
		goto again;
	}

	/* devfs.rs_dat.rdd_treelock... // read-only */
	if (!ramfs_dirdata_treelock_tryread(&devfs.rs_dat)) {
		_fsuper_nodes_endwrite(&devfs);
		_blkdev_root_partslock_release(self);
		_devfs_byname_endwrite();
		fsuper_nodes_reap(&devfs);
		blkdev_root_partslock_reap(self);
		devfs_byname_reap();
		ramfs_dirdata_treelock_read(&devfs.rs_dat);
		ramfs_dirdata_treelock_endread(&devfs.rs_dat);
		goto again;
	}

	/* fallnodes_lock... */
	if (!fallnodes_tryacquire()) {
		_ramfs_dirdata_treelock_endread(&devfs.rs_dat);
		_fsuper_nodes_endwrite(&devfs);
		_blkdev_root_partslock_release(self);
		_devfs_byname_endwrite();
		ramfs_dirdata_treelock_reap(&devfs.rs_dat);
		fsuper_nodes_reap(&devfs);
		blkdev_root_partslock_reap(self);
		devfs_byname_reap();
		while (!fallnodes_available())
			task_yield();
		goto again;
	}
}


/* If bound, remove `self' from the following global listings (caller must be holding locks):
 *  - devfs_byname_list
 *  - devfs.rs_sup.fs_nodes
 *  - fallnodes_list
 * For  every global  listing from with  `self' is removed,  also mark the
 * associated link as unbound such that no dangling links are left behind. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL device_unlink_from_globals)(struct device *__restrict self) {
	COMPILER_BARRIER();
	/* devfs_byname_list... */
	if (self->dv_byname_node.rb_lhs != DEVICE_BYNAME_DELETED) {
		devfs_byname_removenode(self);
		self->dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED;
	}

	/* devfs.rs_sup.fs_nodes... */
	assertf(self->_fn_suplop.olo_func != &fnode_add2sup_lop,
	        "Handled by the check for lock-operations in blkdev_repart_locks_acquire");
	if (self->fn_supent.rb_rhs != FSUPER_NODES_DELETED) {
		fsuper_nodes_removenode(&devfs, self);
		self->fn_supent.rb_rhs = FSUPER_NODES_DELETED;
	}

	/* fallnodes_list... */
	if (LIST_ISBOUND(self, fn_allnodes))
		LIST_UNBIND(self, fn_allnodes);
	COMPILER_BARRIER();
}


/* Check if a given filename is already in use in "/dev/". (Caller must be holding proper locks) */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL devfs_root_nameused)(struct fdevfsdirent const *__restrict name) {
	struct device *existing;
	if (ramfs_direnttree_locate(devfs.rs_dat.rdd_tree,
	                            name->fdd_dirent.fd_name,
	                            name->fdd_dirent.fd_namelen))
		return true; /* Another file with the same name already exists. */

	/* Check for another device file */
	existing = devfs_byname_locate(name->fdd_dirent.fd_name,
	                               name->fdd_dirent.fd_namelen);
	if (existing != NULL) {
		if (!wasdestroyed(existing))
			return true;

		/* Existing device is currently being destroyed. (do the unlink for it) */
		devfs_byname_removenode(existing);
		existing->dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED;
	}
	return false;
}


/* Force-insert `self' into the devfs INode tree. (Caller must be holding locks) */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) void
NOTHROW(FCALL devfs_insert_into_inode_tree)(struct device *__restrict self) {
	for (;;) {
		struct fnode *existing;
		assert(devfs.fs_nodes != FSUPER_NODES_DELETED);
		existing = fsuper_nodes_locate(&devfs, self->fn_ino);
		if likely(!existing)
			break;
		if (wasdestroyed(existing)) {
			/* Unlink destroyed device. */
			fsuper_nodes_removenode(&devfs, existing);
			ATOMIC_WRITE(existing->fn_supent.rb_rhs, FSUPER_NODES_DELETED);
			break;
		}
		/* Create a new device number */
		++self->dn_devno;
		assert(S_ISBLK(self->fn_mode));
		self->fn_ino = devfs_devnode_makeino(S_IFBLK, self->dn_devno);

		/* Also update the INO value stored in the associated  dirent.
		 * This is still thread-safe since the dirent hasn't been made
		 * globally visible, yet. */
		self->dv_dirent->fdd_dirent.fd_ino = self->fn_ino;
	}

	/* Do the actual insert */
	fsuper_nodes_insert(&devfs, self);
}



/* Reconstruct/Reload partitions of `self':
 *   - Step #0: If `self' is a partition, return immediately.
 *   - Step #1: Construct new partitions and assign device IDs and names to partitions
 *   - Step #2: Acquire locks to:
 *               - self->bd_rootinfo.br_partslock
 *               - devfs_byname_lock
 *               - devfs.rs_sup.fs_nodeslock
 *               - devfs.rs_dat.rdd_treelock  // read-only
 *               - fallnodes_lock
 *   - Step #3: Clear `self->bd_rootinfo.br_parts' and:
 *               - tryincref() every partition. Those for which this
 *                 fails are  immediately discarded  from the  list.
 *              Remove all old partitions from:
 *               - devfs_byname_list
 *               - devfs.rs_sup.fs_nodes
 *               - fallnodes_list
 *               - Also clear `MFILE_FN_GLOBAL_REF' and decref_nokill(partition) if it was set
 *   - Step #4: Register all of the new partitions:
 *               - self->bd_rootinfo.br_parts    -- Sort by partition start offset
 *               - devfs_byname_list             -- If same-named file already exists here (or in `devfs.rs_dat.rdd_tree'),
 *                                                  then simply don't add to the tree, but instead set:
 *                                                  >> `dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED'
 *               - devfs.rs_sup.fs_nodes         -- If another node with the same INO  exists, keep on adding +1 to  the
 *                                                  device's dev_t, before generating a new INO until no more collisions
 *                                                  happen.
 *               - fallnodes_list                -- Also set `MFILE_FN_GLOBAL_REF' for the new partition and incref() it
 *   - Step #5: Release locks from:
 *               - devfs_byname_lock
 *               - devfs.rs_sup.fs_nodeslock
 *               - devfs.rs_dat.rdd_treelock  // read-only
 *               - fallnodes_lock
 *   - Step #6: Drop references from all of the old partitions
 *   - Step #7: Release lock to `self->bd_rootinfo.br_partslock' */
PUBLIC NONNULL((1)) void KCALL
blkdev_repart(struct blkdev *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	struct blkdev *dev;
	struct REF blkdev_list oldparts;
	struct REF blkdev_list newparts;
	struct blkdev_makeparts_info info;

	/* Step #0: If `self' is a partition, return immediately. */
	if unlikely(!blkdev_isroot(self))
		return;

	/* Step #1: Construct new partitions and assign device IDs and names to partitions */
	newparts = blkdev_makeparts(self, &info);

	/* Step #2: Acquire locks */
	TRY {
		blkdev_repart_locks_acquire(self);
	} EXCEPT {
		blkdev_destroy_incomplete_parts(&newparts);
		RETHROW();
	}

	/* NOEXCEPT from here on... */

	/* Step #3: Clear `self->bd_rootinfo.br_parts' and unregister old partitions */
	oldparts = self->bd_rootinfo.br_parts;
	DBG_memset(&self->bd_rootinfo.br_parts, 0xcc,
	           sizeof(self->bd_rootinfo.br_parts));

	/* Acquire references to old parts, and unlink all that are already dead */
	LIST_FOREACH_SAFE (dev, &oldparts, bd_partinfo.bp_partlink) {
		if (!tryincref(dev))
			LIST_UNBIND(dev, bd_partinfo.bp_partlink);
	}

	/* Remove all old partitions from global listings */
	LIST_FOREACH (dev, &oldparts, bd_partinfo.bp_partlink) {
		device_unlink_from_globals(dev);
		/* Also clear `MFILE_FN_GLOBAL_REF' and decref_nokill(partition) if it was set */
		if (ATOMIC_FETCHAND(dev->mf_flags, ~MFILE_FN_GLOBAL_REF) & MFILE_FN_GLOBAL_REF)
			decref_nokill(dev);
	}

	/* Step #4: Register all of the new partitions */
	LIST_FOREACH (dev, &newparts, bd_partinfo.bp_partlink) {
		if (devfs_root_nameused(dev->dv_dirent)) {
			DBG_memset(&dev->dv_byname_node, 0xcc, sizeof(dev->dv_byname_node));
			dev->dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED;
		} else {
			/* Insert into the byname tree. */
			devfs_byname_insert(dev);
		}

		/* Insert into the INO tree of the devfs superblock. */
		devfs_insert_into_inode_tree(dev);

		/* Insert into the all-parts list. */
		LIST_INSERT_HEAD(&fallnodes_list, dev, fn_allnodes);
	}
	self->bd_rootinfo.br_parts = newparts;

	/* Step #5: Release locks. */
	_fallnodes_release();
	_devfs_byname_endwrite();
	_ramfs_dirdata_treelock_endread(&devfs.rs_dat);
	_fsuper_nodes_endwrite(&devfs);

	/* Step #6: Drop references from all of the old partitions (Also mark then as unlinked). */
	while (!LIST_EMPTY(&oldparts)) {
		dev = LIST_FIRST(&oldparts);
		LIST_UNBIND(dev, bd_partinfo.bp_partlink);
		decref_unlikely(dev);
	}

	/* Save updated information. */
	memcpy(self->bd_rootinfo.br_mbr_diskuid, info.br_mbr_diskuid, sizeof(info.br_mbr_diskuid));
	memcpy(&self->bd_rootinfo.br_efi_guid, &info.br_efi_guid, sizeof(info.br_efi_guid));

	/* Step #7: Release lock to `self->bd_rootinfo.br_partslock' */
	_blkdev_root_partslock_release(self);

	/* Reap all of the locks released above */
	ramfs_dirdata_treelock_reap(&devfs.rs_dat);
	fallnodes_reap();
	devfs_byname_reap();
	fsuper_nodes_reap(&devfs);
	blkdev_root_partslock_reap(self);
}


/* The  combination of `device_register()' and `blkdev_repart()', but implemented
 * in such a manner that either all of the new devices become visible at the same
 * time, or none of them do (in case of an exception).
 *
 * This prevents race conditions that would arise from the alternative:
 * >> device_register(self);
 * >> TRY {
 * >>     blkdev_repart(self);
 * >> } EXCEPT {
 * >>     // If we get here, device was globally visible for a short moment.
 * >>     // This can be prevented by using `blkdev_repart_and_register()'
 * >>     device_delete(self);
 * >>     RETHROW();
 * >> }
 *
 * This function assumes:
 *  - LIST_EMPTY(&self->bd_rootinfo.br_parts)
 *  - blkdev_isroot(self)
 * This function initializes (before making `self' globally visible):
 *  - self->_device_devnode_ _fdevnode_node_ fn_allnodes
 *  - self->_device_devnode_ _fdevnode_node_ fn_supent
 *  - self->dv_byname_node */
PUBLIC NONNULL((1)) void KCALL
blkdev_repart_and_register(struct blkdev *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	struct blkdev *dev;
	struct REF blkdev_list newparts;
	struct blkdev_makeparts_info info;
	assert(LIST_EMPTY(&self->bd_rootinfo.br_parts));
	assert(blkdev_isroot(self));

	/* Construct new partitions and assign device IDs and names to partitions */
	newparts = blkdev_makeparts(self, &info);

	/* Save root device information. */
	memcpy(self->bd_rootinfo.br_mbr_diskuid, info.br_mbr_diskuid, sizeof(info.br_mbr_diskuid));
	memcpy(&self->bd_rootinfo.br_efi_guid, &info.br_efi_guid, sizeof(info.br_efi_guid));

	/* Acquire locks */
	TRY {
		blkdev_repart_locks_acquire(self);
	} EXCEPT {
		blkdev_destroy_incomplete_parts(&newparts);
		RETHROW();
	}

	/* NOEXCEPT from here on... */

	/* Register the root device itself. */
	if (devfs_root_nameused(self->dv_dirent)) {
		DBG_memset(&self->dv_byname_node, 0xcc, sizeof(self->dv_byname_node));
		self->dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED;
	} else {
		devfs_byname_insert(self);
	}
	devfs_insert_into_inode_tree(self);
	LIST_INSERT_HEAD(&fallnodes_list, self, fn_allnodes);

	/* Register all of the new partitions */
	LIST_FOREACH (dev, &newparts, bd_partinfo.bp_partlink) {
		struct fdevfsdirent *name = dev->dv_dirent;
		if (devfs_root_nameused(dev->dv_dirent)) {
			DBG_memset(&dev->dv_byname_node, 0xcc, sizeof(dev->dv_byname_node));
			dev->dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED;
		} else {
			/* Insert into the byname tree. */
			devfs_byname_insert(dev);
		}

		/* Insert into the INO tree of the devfs superblock. */
		devfs_insert_into_inode_tree(dev);

		/* Insert into the all-parts list. */
		LIST_INSERT_HEAD(&fallnodes_list, dev, fn_allnodes);
	}
	self->bd_rootinfo.br_parts = newparts;

	/* Step #5: Release locks. */
	_fallnodes_release();
	_devfs_byname_endwrite();
	_ramfs_dirdata_treelock_endread(&devfs.rs_dat);
	_fsuper_nodes_endwrite(&devfs);
	_blkdev_root_partslock_release(self);

	/* Reap all of the locks released above */
	fallnodes_reap();
	devfs_byname_reap();
	ramfs_dirdata_treelock_reap(&devfs.rs_dat);
	fsuper_nodes_reap(&devfs);
	blkdev_root_partslock_reap(self);
}



DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_BLKDEV_C */
