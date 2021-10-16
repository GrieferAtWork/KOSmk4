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
#define _KOS_SOURCE 1

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
#include <kernel/printk.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <hw/disk/part/efi.h>
#include <hw/disk/part/mbr.h>
#include <kos/except.h>
#include <kos/except/reason/inval.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */


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
	blkdev_rdsectors(ms, addr, buf, num_bytes, aio);
}

PRIVATE NONNULL((1, 5)) void KCALL
blkpart_v_saveblocks(struct mfile *__restrict self, pos_t addr,
                     physaddr_t buf, size_t num_bytes,
                     struct aio_multihandle *__restrict aio) {
	struct blkdev *me = mfile_asblkdev(self);
	struct blkdev *ms = me->bd_partinfo.bp_master;
	addr += me->bd_partinfo.bp_partstart;
	blkdev_wrsectors(ms, addr, buf, num_bytes, aio);
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
#define blkdev_destroy_incomplete_part(self)         \
	(decref_nokill((self)->bd_partinfo.bp_master),   \
	 decref_nokill((self)->dv_driver),               \
	 destroy((self)->dv_dirent),                     \
	 decref_nokill(&devfs), /* for self->fn_super */ \
	 kfree(self))


/* Generate a list of partitions by reading MSB/EFI headers.
 * The following fields are left uninitialized for each of the returned devices:
 *  - self->_blkdev_dev_ _device_devnode_ _fdevnode_node_ fn_allnodes
 *  - self->_blkdev_dev_ _device_devnode_ _fdevnode_node_ fn_supent
 *  - self->_blkdev_dev_ dv_byname_node
 *  - self->bd_partinfo.bp_partlink     (Because of this, you must cannot just decref() these devices,
 *                                       must instead use `blkdev_destroy_incomplete_part()' if  you
 *                                       come into a situation where these new devices must go away) */
PRIVATE ATTR_NOINLINE WUNUSED struct REF blkdev_list FCALL
blkdev_makeparts(struct blkdev *__restrict self) {
	struct mbr_sector mbr;
	struct REF blkdev_list result;

	/* Read the MBR */
	/* TODO */

	LIST_INIT(&result);
	/* TODO */


	/* TODO: Sort partitions by base-address */
	return result;
}


PRIVATE NONNULL((1)) void
NOTHROW(FCALL blkdev_destroy_incomplete_parts)(struct blkdev_list const *__restrict self) {
	struct blkdev *dev;
	LIST_FOREACH_SAFE (dev, self, bd_partinfo.bp_partlink) {
		blkdev_destroy_incomplete_part(dev);
	}
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

	/* devfs.rs_dat.rdd_treelock... // read-only */
	if (!shared_rwlock_tryread(&devfs.rs_dat.rdd_treelock)) {
		_fsuper_nodes_endwrite(&devfs);
		_blkdev_root_partslock_release(self);
		_devfs_byname_endwrite();
		fsuper_nodes_reap(&devfs);
		blkdev_root_partslock_reap(self);
		devfs_byname_reap();
		shared_rwlock_read(&devfs.rs_dat.rdd_treelock);
		shared_rwlock_endread(&devfs.rs_dat.rdd_treelock);
		goto again;
	}

	/* fallnodes_lock... */
	if (!fallnodes_tryacquire()) {
		shared_rwlock_endread(&devfs.rs_dat.rdd_treelock);
		_fsuper_nodes_endwrite(&devfs);
		_blkdev_root_partslock_release(self);
		_devfs_byname_endwrite();
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
	if (self->fn_supent.rb_lhs != FSUPER_NODES_DELETED) {
		fsuper_nodes_removenode(&devfs, self);
		self->fn_supent.rb_lhs = FSUPER_NODES_DELETED;
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
			ATOMIC_WRITE(existing->fn_supent.rb_lhs, FSUPER_NODES_DELETED);
			break;
		}
		/* Create a new device number */
		++self->dn_devno;
		assert(S_ISBLK(self->fn_mode));
		self->fn_ino = devfs_devnode_makeino(S_IFBLK, self->dn_devno);
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

	/* Step #0: If `self' is a partition, return immediately. */
	if unlikely(!blkdev_isroot(self))
		return;

	/* Step #1: Construct new partitions and assign device IDs and names to partitions */
	newparts = blkdev_makeparts(self);

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
	shared_rwlock_endread(&devfs.rs_dat.rdd_treelock);
	_fsuper_nodes_endwrite(&devfs);

	/* Step #6: Drop references from all of the old partitions (Also mark then as unlinked). */
	while (!LIST_EMPTY(&oldparts)) {
		dev = LIST_FIRST(&oldparts);
		LIST_UNBIND(dev, bd_partinfo.bp_partlink);
		decref_unlikely(dev);
	}

	/* Step #7: Release lock to `self->bd_rootinfo.br_partslock' */
	_blkdev_root_partslock_release(self);

	/* Reap all of the locks released above (NOTE: `devfs.rs_dat.rdd_treelock' doesn't have lops!) */
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
	assert(LIST_EMPTY(&self->bd_rootinfo.br_parts));
	assert(blkdev_isroot(self));

	/* Construct new partitions and assign device IDs and names to partitions */
	newparts = blkdev_makeparts(self);

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
	shared_rwlock_endread(&devfs.rs_dat.rdd_treelock);
	_fsuper_nodes_endwrite(&devfs);
	_blkdev_root_partslock_release(self);

	/* Reap all of the locks released above (NOTE: `devfs.rs_dat.rdd_treelock' doesn't have lops!) */
	fallnodes_reap();
	devfs_byname_reap();
	fsuper_nodes_reap(&devfs);
	blkdev_root_partslock_reap(self);
}



DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_BLKDEV_C */
