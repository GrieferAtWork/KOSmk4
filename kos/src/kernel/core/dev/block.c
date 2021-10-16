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
#ifndef GUARD_KERNEL_SRC_DEV_BLOCK_C
#define GUARD_KERNEL_SRC_DEV_BLOCK_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_FS
#include <debugger/config.h>
#include <debugger/hook.h>
#include <debugger/io.h>
#include <dev/block.h>
#include <fs/node.h>
#include <fs/ramfs.h>
#include <kernel/aio.h>
#include <kernel/cache.h>
#include <kernel/driver-param.h>
#include <kernel/except.h>
#include <kernel/heap.h>
#include <kernel/iovec.h>
#include <kernel/mman/driver.h>
#include <kernel/mman/phys-access.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <sched/cpu.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/minmax.h>
#include <hybrid/overflow.h>

#include <kos/dev.h>
#include <kos/except/reason/fs.h>
#include <kos/except/reason/inval.h>
#include <kos/except/reason/io.h>
#include <kos/guid.h>

#include <assert.h>
#include <format-printer.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/* Implement the ABI for the address tree used by block_device. */
#define ATREE(x)      bdev_tree_##x
#define ATREE_CALL    KCALL
#define ATREE_NOTHROW NOTHROW
#define Tkey          dev_t
#define T             struct blkdev
#define N_NODEPATH    bd_devlink
#define ATREE_SINGLE  1
#include <hybrid/sequence/atree-abi.h>
#undef ATREE_SINGLE

DECL_BEGIN

/* [0..1] The  block  device  / partition  from  which the  kernel  was booted.
 * Set to `(struct blkdev *)-1' if indeterminate during early boot. */
PUBLIC REF struct blkdev *boot_partition = NULL;

PRIVATE ATTR_USED ATTR_FREETEXT void KCALL
kernel_boot_option_handler(char *__restrict arg) {
	REF struct blkdev *new_boot;
	new_boot = block_device_lookup(arg);
	if unlikely(!new_boot) {
#ifdef CONFIG_HAVE_DEBUGGER
		kernel_panic(FREESTR("No such boot block device %q (use `lsblk' for detected devices)"), arg);
#else /* CONFIG_HAVE_DEBUGGER */
		kernel_panic(FREESTR("No such boot block device %q"), arg);
#endif /* !CONFIG_HAVE_DEBUGGER */
	}
	if (boot_partition != NULL &&
	    boot_partition != (REF struct blkdev *)-1)
		decref(boot_partition);
	boot_partition = new_boot; /* Inherit reference */
}
DEFINE_LATE_KERNEL_COMMANDLINE_OPTION(kernel_boot_option_handler,
                                      KERNEL_COMMANDLINE_OPTION_TYPE_FUNC, "boot");



PUBLIC NONNULL((1, 5)) void KCALL
block_device_partition_read(struct block_device *__restrict self,
                            USER CHECKED void *dst, size_t num_sectors,
                            lba_t addr, /*out*/ struct aio_handle *__restrict aio)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct block_device *master;
	master = ((struct block_device_partition *)self)->bp_master;
	assert(master);
	assert(master->bd_type.dt_read);
	(*master->bd_type.dt_read)(master, dst, num_sectors,
	                           addr + ((struct block_device_partition *)self)->bp_min,
	                           aio);
}

PUBLIC NONNULL((1, 5)) void KCALL
block_device_partition_write(struct block_device *__restrict self,
                             USER CHECKED void const *src, size_t num_sectors,
                             lba_t addr, /*out*/ struct aio_handle *__restrict aio)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct block_device *master;
	master = ((struct block_device_partition *)self)->bp_master;
	assert(master);
	assert(master->bd_type.dt_write);
	if unlikely(master->bd_flags & BLOCK_DEVICE_FLAG_READONLY)
		THROW(E_IOERROR_READONLY, (uintptr_t)E_IOERROR_SUBSYSTEM_HARDDISK);
	(*master->bd_type.dt_write)(master, src, num_sectors,
	                            addr + ((struct block_device_partition *)self)->bp_min,
	                            aio);
}

PUBLIC NONNULL((1, 5)) void KCALL
block_device_partition_readv(struct block_device *__restrict self,
                             struct iov_buffer *__restrict buf, size_t num_sectors,
                             lba_t addr, /*out*/ struct aio_handle *__restrict aio)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct block_device *master;
	master = ((struct block_device_partition *)self)->bp_master;
	assert(master);
	assert(master->bd_type.dt_readv);
	(*master->bd_type.dt_readv)(master, buf, num_sectors,
	                            addr + ((struct block_device_partition *)self)->bp_min,
	                            aio);
}

PUBLIC NONNULL((1, 5)) void KCALL
block_device_partition_writev(struct block_device *__restrict self,
                              struct iov_buffer *__restrict buf, size_t num_sectors,
                              lba_t addr, /*out*/ struct aio_handle *__restrict aio)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct block_device *master;
	master = ((struct block_device_partition *)self)->bp_master;
	assert(master);
	assert(master->bd_type.dt_writev);
	if unlikely(master->bd_flags & BLOCK_DEVICE_FLAG_READONLY)
		THROW(E_IOERROR_READONLY, (uintptr_t)E_IOERROR_SUBSYSTEM_HARDDISK);
	(*master->bd_type.dt_writev)(master, buf, num_sectors,
	                             addr + ((struct block_device_partition *)self)->bp_min,
	                             aio);
}

PUBLIC NONNULL((1, 5)) void KCALL
block_device_partition_read_phys(struct block_device *__restrict self,
                                 physaddr_t dst, size_t num_sectors,
                                 lba_t addr, /*out*/ struct aio_handle *__restrict aio)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct block_device *master;
	master = ((struct block_device_partition *)self)->bp_master;
	assert(master);
	assert(master->bd_type.dt_read_phys);
	(*master->bd_type.dt_read_phys)(master, dst, num_sectors,
	                                addr + ((struct block_device_partition *)self)->bp_min,
	                                aio);
}

PUBLIC NONNULL((1, 5)) void KCALL
block_device_partition_write_phys(struct block_device *__restrict self,
                                  physaddr_t src, size_t num_sectors,
                                  lba_t addr, /*out*/ struct aio_handle *__restrict aio)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct block_device *master;
	master = ((struct block_device_partition *)self)->bp_master;
	assert(master);
	assert(master->bd_type.dt_write_phys);
	if unlikely(master->bd_flags & BLOCK_DEVICE_FLAG_READONLY)
		THROW(E_IOERROR_READONLY, (uintptr_t)E_IOERROR_SUBSYSTEM_HARDDISK);
	(*master->bd_type.dt_write_phys)(master, src, num_sectors,
	                                 addr + ((struct block_device_partition *)self)->bp_min,
	                                 aio);
}

PUBLIC NONNULL((1, 5)) void KCALL
block_device_partition_readv_phys(struct block_device *__restrict self,
                                  struct iov_physbuffer *__restrict buf, size_t num_sectors,
                                  lba_t addr, /*out*/ struct aio_handle *__restrict aio)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct block_device *master;
	master = ((struct block_device_partition *)self)->bp_master;
	assert(master);
	assert(master->bd_type.dt_readv_phys);
	(*master->bd_type.dt_readv_phys)(master, buf, num_sectors,
	                                 addr + ((struct block_device_partition *)self)->bp_min,
	                                 aio);
}

PUBLIC NONNULL((1, 5)) void KCALL
block_device_partition_writev_phys(struct block_device *__restrict self,
                                   struct iov_physbuffer *__restrict buf, size_t num_sectors,
                                   lba_t addr, /*out*/ struct aio_handle *__restrict aio)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct block_device *master;
	master = ((struct block_device_partition *)self)->bp_master;
	assert(master);
	assert(master->bd_type.dt_writev_phys);
	if unlikely(master->bd_flags & BLOCK_DEVICE_FLAG_READONLY)
		THROW(E_IOERROR_READONLY, (uintptr_t)E_IOERROR_SUBSYSTEM_HARDDISK);
	(*master->bd_type.dt_writev_phys)(master, buf, num_sectors,
	                                  addr + ((struct block_device_partition *)self)->bp_min,
	                                  aio);
}

PUBLIC NONNULL((1)) syscall_slong_t KCALL
block_device_partition_ioctl(struct block_device *__restrict self,
                             struct block_device *__restrict partition,
                             syscall_ulong_t cmd, USER UNCHECKED void *arg,
                             iomode_t mode) THROWS(...) {
	struct block_device *master;
	assert(self == partition);
	assert(block_device_ispartition(self));
	master = ((struct block_device_partition *)self)->bp_master;
	if (master->bd_type.dt_ioctl)
		return (*master->bd_type.dt_ioctl)(master, self, cmd, arg, mode);
	THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
	      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
	      cmd);
}



/* Called to destroy a block device child partition after
 * the partition  has already  been finalized  otherwise. */
LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(KCALL block_device_clear_delparts)(struct block_device *__restrict self) {
	struct block_device_partition *iter, *next;
	iter = ATOMIC_XCH(self->bd_delparts, NULL);
	while (iter) {
		next = *(struct block_device_partition **)iter;
		SLIST_REMOVE(&self->bd_parts, iter, bp_parts);
		heap_free(&kernel_locked_heap,
		          iter,
		          iter->bd_heapsize,
		          GFP_NORMAL);
		iter = next;
	}
}

PUBLIC NONNULL((1)) void KCALL
block_device_acquire_partlock_read(struct block_device *__restrict self) {
	sync_read(&self->bd_parts_lock);
	if unlikely(ATOMIC_READ(self->bd_delparts) != NULL) {
		if (sync_tryupgrade(&self->bd_parts_lock)) {
			block_device_clear_delparts(self);
			sync_downgrade(&self->bd_parts_lock);
		}
	}
}
PUBLIC NONNULL((1)) void KCALL
block_device_acquire_partlock_write(struct block_device *__restrict self) {
	sync_write(&self->bd_parts_lock);
	block_device_clear_delparts(self);
}

PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(KCALL block_device_acquire_partlock_tryread)(struct block_device *__restrict self) {
	if (!sync_tryread(&self->bd_parts_lock))
		return false;
	if unlikely(ATOMIC_READ(self->bd_delparts) != NULL) {
		if (sync_tryupgrade(&self->bd_parts_lock)) {
			block_device_clear_delparts(self);
			sync_downgrade(&self->bd_parts_lock);
		}
	}
	return true;
}
PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(KCALL block_device_acquire_partlock_trywrite)(struct block_device *__restrict self) {
	if (!sync_trywrite(&self->bd_parts_lock))
		return false;
	block_device_clear_delparts(self);
	return true;
}


/* The tree used to quickly look up a block device from its ID */
PRIVATE REF ATREE_HEAD(struct blkdev) block_device_tree = NULL;
PRIVATE dev_t block_device_next_auto = MKDEV(DEV_MAJOR_AUTO,0);
PRIVATE struct atomic_rwlock block_device_lock = ATOMIC_RWLOCK_INIT;
DEFINE_DBG_BZERO_OBJECT(block_device_lock);


#ifndef CONFIG_NO_SMP
PRIVATE NOBLOCK struct icpustate *
NOTHROW(FCALL ipi_destroy_block_device)(struct icpustate *__restrict state,
                                        void *args[CPU_IPI_ARGCOUNT]) {
	struct blkdev *dev;
	dev = (struct blkdev *)args[0];
	block_device_destroy(dev);
	return state;
}
#endif /* !CONFIG_NO_SMP */

/* Destroy a given block device. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL block_device_destroy)(struct blkdev *__restrict self) {
	if (self->bd_type.dt_fini) {
#ifndef CONFIG_NO_SMP
		if (cpu_count > 1) {
			pflag_t was = PREEMPTION_PUSHOFF();
			if (THIS_CPU != &bootcpu) {
				/* Let the boot CPU do all of the cleanup asynchronously. */
				void *args[CPU_IPI_ARGCOUNT];
				args[0] = self;
				while (!cpu_sendipi(&bootcpu, &ipi_destroy_block_device, args, CPU_IPI_FWAKEUP))
					task_pause();
				return;
			}
			(*self->bd_type.dt_fini)((struct block_device *)self);
			PREEMPTION_POP(was);
		} else
#endif /* !CONFIG_NO_SMP */
		{
			(*self->bd_type.dt_fini)((struct block_device *)self);
		}
	}
	assert(self->bd_devlink.a_vaddr == DEV_UNSET);
	/* Check if the device should be removed from devfs, and drop
	 * the references  held to  its  INode and  directory  entry. */
	if (self->bd_devfs_inode) {
		devfs_remove(self->bd_devfs_inode, /* No-op if already done... */
		             self->bd_devfs_entry);
		decref_likely(self->bd_devfs_inode);
		decref_likely(self->bd_devfs_entry);
	}
	if (block_device_ispartition(self)) {
		struct block_device_partition *part;
		struct block_device *master;
		part   = (struct block_device_partition *)self;
		master = part->bp_master;
		if (!block_device_acquire_partlock_trywrite(master)) {
			/* Schedule the part for removal from the master */
			struct block_device_partition *next;
			do {
				next = ATOMIC_READ(master->bd_delparts);
				*(struct block_device_partition **)part = next;
			} while (!ATOMIC_CMPXCH_WEAK(master->bd_delparts, next, part));
			decref(master);
			return;
		}
		COMPILER_READ_BARRIER();
		SLIST_REMOVE(&master->bd_parts, part, bp_parts);
		sync_endwrite(&master->bd_parts_lock);
		decref(master);
	} else {
		struct block_device *me;
		me = (struct block_device *)self;
		/* Destroy any pending delete-parts. */
		block_device_clear_delparts(me);
		heap_free(&kernel_locked_heap,
		          me->bd_cache_base,
		          me->bd_cache_size,
		          GFP_NORMAL);
	}
	/* Actually free the structure. */
	heap_free(&kernel_locked_heap,
	          self,
	          self->bd_heapsize,
	          GFP_NORMAL);
}

/* Lookup  a block device associated with `devno'  and return a reference to it.
 * When no block device is associated that device number, return `NULL' instead. */
PUBLIC WUNUSED REF struct blkdev *KCALL
block_device_lookup(dev_t devno) THROWS(E_WOULDBLOCK) {
	REF struct blkdev *result;
	sync_read(&block_device_lock);
	result = bdev_tree_locate(block_device_tree, devno);
	/* Try to acquire a reference to the block device. */
	if (result && unlikely(!tryincref(result)))
		result = NULL;
	sync_endread(&block_device_lock);
	return result;
}


/* Same as `block_device_lookup()', but return `NULL' if the lookup would have caused an exception. */
PUBLIC WUNUSED REF struct blkdev *
NOTHROW(KCALL block_device_lookup_nx)(dev_t devno) {
	REF struct blkdev *result;
	if (!sync_read_nx(&block_device_lock))
		return NULL;
	result = bdev_tree_locate(block_device_tree, devno);
	/* Try to acquire a reference to the block device. */
	if (result && unlikely(!tryincref(result)))
		result = NULL;
	sync_endread(&block_device_lock);
	return result;
}



PRIVATE WUNUSED REF struct blkdev *KCALL
bdev_tree_search_name(struct blkdev *__restrict node,
                      char const *__restrict name) {
again:
	if (strcmp(node->bd_name, name) == 0)
		return (likely(tryincref(node))) ? node : NULL;
	if (node->bd_devlink.a_min) {
		if (node->bd_devlink.a_max) {
			REF struct blkdev *result;
			result = bdev_tree_search_name(node->bd_devlink.a_max, name);
			if (result)
				return result;
		}
		node = node->bd_devlink.a_min;
		goto again;
	}
	if (node->bd_devlink.a_max) {
		node = node->bd_devlink.a_max;
		goto again;
	}
	return NULL;
}

/* Lookup a block device, given its `name`, with is its default filename
 * as will appear in the /dev/ directory, and may optionally be prefixed
 * by a string `/dev/' that is stripped before comparison.
 * Alternatively, the given `name' may also be in the form of `MAJOR:MINOR',
 * an  encoding that is  always attempted first by  attempting to decode the
 * given name using `scanf("%u:%u")'
 * >> block_device_lookup_name("3:64");      // MKDEV(3, 64)
 * >> block_device_lookup_name("/dev/hdc1"); // MKDEV(22, 0) + 1
 * >> block_device_lookup_name("hda2");      // MKDEV(3, 0)  + 2
 * This function is mainly intended for decoding device names from commandline
 * arguments, such as  the kernel's `boot=<NAME>'  option which overrides  the
 * kernel's boot partition (in case the kernel can't auto-detect its partition
 * properly).
 * @return: NULL: No device matching `name' exists. */
PUBLIC WUNUSED REF struct blkdev *KCALL
block_device_lookup_name(USER CHECKED char const *name)
		THROWS(E_WOULDBLOCK) {
	REF struct blkdev *result = NULL;
	u32 dev_major, dev_minor;
	size_t name_len;
	char name_buf[COMPILER_LENOF(((struct blkdev *)0)->bd_name)];
	if (sscanf(name, "%u:%u", &dev_major, &dev_minor) == 2)
		return block_device_lookup(MKDEV(dev_major, dev_minor));
	if (memcmp(name, "/dev/", 5 * sizeof(char)) == 0)
		name += 5;
	name_len = strnlen(name, COMPILER_LENOF(name_buf));
	if unlikely(name_len >= COMPILER_LENOF(name_buf))
		return NULL; /* Name is too long */
	memcpy(name_buf, name, name_len, sizeof(char));
	name_buf[name_len] = '\0';
	sync_read(&block_device_lock);
	if likely(block_device_tree)
		result = bdev_tree_search_name(block_device_tree, name_buf);
	sync_endread(&block_device_lock);
	return result;
}


/* Allocate and initialize a new block device. */
PUBLIC ATTR_MALLOC ATTR_RETNONNULL WUNUSED REF struct block_device *KCALL
block_device_alloc(size_t sector_size, size_t structure_size)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	REF struct block_device *result;
	heapptr_t resptr;
	size_t sector_align;
	assert(sector_size != 0);
	assert(structure_size >= sizeof(struct block_device));
	resptr = heap_alloc(&kernel_locked_heap, structure_size,
	                    GFP_LOCKED | GFP_PREFLT | GFP_CALLOC);
	result                 = (REF struct block_device *)heapptr_getptr(resptr);
	result->bd_heapsize    = heapptr_getsiz(resptr);
	result->bd_refcnt      = 1;
	result->bd_max_retry   = 2;
	result->bd_sector_size = sector_size;
	atomic_rwlock_cinit(&result->bd_parts_lock);
	sector_align = PAGESIZE;
	if unlikely(sector_size >= sector_align)
		sector_align = CEIL_ALIGN(sector_size, sector_align);
	else {
		while ((sector_align / 2) >= sector_size)
			sector_align /= 2;
	}
	rwlock_cinit(&result->bd_cache_lock);
	assert(sector_align != 0);
	result->bd_cache_ssiz = sector_align;
	TRY {
		heapptr_t cacheptr;
		byte_t volatile *iter, *end;
		if unlikely(sector_size > PAGESIZE) {
			kernel_panic("TODO: Ensure that the cache is allocated as physically continuous memory");
		}
		cacheptr = heap_align(&kernel_locked_heap,
		                      result->bd_cache_ssiz,
		                      0,
		                      BD_MAX_CACHE_SECTORS *
		                      result->bd_cache_ssiz,
		                      GFP_LOCKED | GFP_PREFLT);
		/* Make sure that all cache pages have been pre-faulted. */
		iter = (byte_t *)heapptr_getptr(cacheptr);
		end  = iter + heapptr_getsiz(cacheptr);
		for (; iter < end; iter += PAGESIZE)
			*iter = 0xcc;

		result->bd_cache_base = (byte_t *)heapptr_getptr(cacheptr);
		result->bd_cache_size = heapptr_getsiz(cacheptr);
	} EXCEPT {
		heap_free(&kernel_locked_heap,
		          heapptr_getptr(resptr),
		          heapptr_getsiz(resptr),
		          GFP_NORMAL);
		RETHROW();
	}
	return result;
}



PRIVATE NONNULL((1)) void KCALL
block_device_add_to_devfs(struct blkdev *__restrict self) {
	if (!self->bd_name[0]) {
		struct block_device *master;
		/* Auto-generate the name */
		if (block_device_ispartition(self) &&
		    (master = ((struct block_device_partition *)self)->bp_master,
		     master->bd_name[0])) {
			snprintf(self->bd_name, sizeof(self->bd_name),
			         "%s%" PRIuN(__SIZEOF_MINOR_T__),
			         master->bd_name,
			         MINOR(block_device_devno(self)) -
			         MINOR(block_device_devno(master)));
			self->bd_name[COMPILER_LENOF(self->bd_name) - 1] = 0;
		} else {
			sprintf(self->bd_name,
			        "%.2" PRIxN(__SIZEOF_MAJOR_T__) ":"
			        "%.2" PRIxN(__SIZEOF_MINOR_T__),
			        MAJOR(self->bd_devlink.a_vaddr),
			        MINOR(self->bd_devlink.a_vaddr));
		}
	}
	if (block_device_ispartition(self) &&
	    ((struct block_device_partition *)self)->bp_label[0]) {
		printk(KERN_INFO "[blk] Register new block-device `/dev/%s' (labeled as %q)\n",
		       self->bd_name, ((struct block_device_partition *)self)->bp_label);
	} else {
		printk(KERN_INFO "[blk] Register new block-device `/dev/%s'\n", self->bd_name);
	}
	/* Add the device's node to `/dev'
	 * NOTE: If the file already exists, ignore that fact, as
	 *      `devfs_insert()' will already set `self->bd_devfs_inode'
	 *       to `NULL' for us */
	devfs_insert(self->bd_name,
	             S_IFBLK,
	             block_device_devno(self),
	             &self->bd_devfs_inode,
	             &self->bd_devfs_entry);
}


/* Unregister  the  given  block-device  from  the  block-device-id  tree,  as  well as
 * removing its auto-generated entry from `/dev' (should that entry have been created).
 * @return: true:  Successfully unregistered the given.
 * @return: false: The device was never registered to begin with. */
PUBLIC NONNULL((1)) bool KCALL
block_device_unregister(struct blkdev *__restrict self)
		THROWS(E_WOULDBLOCK) {
	bool result = false;
	/* FIXME: Running  `partprobe /dev/hda'  causes  the a  soft-lock  where the
	 *        kernel will continuously print `Removing block-device `/dev/hda1'' */
	printk(KERN_INFO "[blk] Removing block-device `/dev/%s'\n", self->bd_name);
	if likely(self->bd_devlink.a_vaddr != DEV_UNSET) {
		sync_write(&block_device_lock);
		COMPILER_READ_BARRIER();
		if likely(self->bd_devlink.a_vaddr != DEV_UNSET) {
			struct blkdev *pop_dev;
			pop_dev = bdev_tree_remove(&block_device_tree,
			                           self->bd_devlink.a_vaddr);
			assert(pop_dev == self);
			self->bd_devlink.a_vaddr = DEV_UNSET;
			sync_endwrite(&block_device_lock);
			decref(self);
			result = true;
		} else {
			sync_endwrite(&block_device_lock);
		}
	}
	if (self->bd_devfs_inode) {
		devfs_remove(self->bd_devfs_inode,
		             self->bd_devfs_entry);
	}
	return result;
}


/* Register a block device with a fixed device number.
 * NOTE: When empty, `bd_name' will be set to `"%.2x:%.2x" % (MAJOR(devno),MINOR(devno))'
 * NOTE: This function will also cause the device to appear in `/dev' (unless the device's name is already taken) */
PUBLIC NONNULL((1)) void KCALL
block_device_register(struct blkdev *__restrict self, dev_t devno)
       THROWS(E_WOULDBLOCK, E_BADALLOC) {
	sync_write(&block_device_lock);
	/* Insert the new device into the block-device tree. */
	self->bd_devlink.a_vaddr = devno;
	bdev_tree_insert(&block_device_tree, incref(self));
	sync_endwrite(&block_device_lock);
	TRY {
		block_device_add_to_devfs(self);
	} EXCEPT {
		struct blkdev *pop_dev;
		sync_write(&block_device_lock);
		pop_dev = bdev_tree_remove(&block_device_tree, devno);
		if likely(pop_dev == self) {
			sync_endwrite(&block_device_lock);
			self->bd_devlink.a_vaddr = DEV_UNSET;
			decref_nokill(self); /* The caller still has a reference */
		} else {
			bdev_tree_insert(&block_device_tree, pop_dev);
			sync_endwrite(&block_device_lock);
		}
		RETHROW();
	}
}


/* Automatically   register  the  given  block-device,  assigning  it  an  auto-generated  device  ID.
 * If   `self'   is  a   partition  (s.a.   `block_device_ispartition()'),   assign  based   on  other
 * preexisting partitions `MKDEV(MAJOR(bp_master),MINOR(EXISTING_PARTITION_WITH_GREATEST_MINOR) + 1)',
 * or assign `MKDEV(MAJOR(bp_master),MINOR(bp_master) + 1)'.
 * All other devices are assigned some unique major device number `>= DEV_MAJOR_AUTO' with MINOR set to `0'.
 * NOTE: When empty, `bd_name' will be set to `"%.2x:%.2x" % (MAJOR(devno),MINOR(devno))'
 * NOTE: This function will also cause the device to appear in `/dev' (unless the device's name is already taken) */
PUBLIC NONNULL((1)) void KCALL
block_device_register_auto(struct blkdev *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	dev_t devno;
	if (block_device_ispartition(self)) {
		struct block_device_partition *me;
		struct block_device *master;
		me     = (struct block_device_partition *)self;
		master = me->bp_master;
		assert(master);
again_master:
		sync_write(&block_device_lock);
		if unlikely(master->bd_devlink.a_vaddr == DEV_UNSET) {
			sync_endwrite(&block_device_lock);
			block_device_register_auto(master);
			goto again_master;
		}
		devno = master->bd_devlink.a_vaddr;
		/* Search the first smallest unused minor index. */
		do {
			devno += MKDEV(0, 1);
		} while (bdev_tree_locate(block_device_tree, devno));
	} else {
		sync_write(&block_device_lock);
		devno = block_device_next_auto;
		block_device_next_auto += MKDEV(1, 0);
	}
	self->bd_devlink.a_vaddr = devno;

	/* Insert the new device into the block-device tree. */
	bdev_tree_insert(&block_device_tree, incref(self));
	sync_endwrite(&block_device_lock);
	TRY {
		block_device_add_to_devfs(self);
	} EXCEPT {
		struct blkdev *pop_dev;
		sync_write(&block_device_lock);
		pop_dev = bdev_tree_remove(&block_device_tree, devno);
		if likely(pop_dev == self) {
			self->bd_devlink.a_vaddr = DEV_UNSET;
			sync_endwrite(&block_device_lock);
			decref_nokill(self); /* The caller still has a reference */
		} else {
			bdev_tree_insert(&block_device_tree, pop_dev);
			sync_endwrite(&block_device_lock);
		}
		RETHROW();
	}
}



PRIVATE NOBLOCK NONNULL((1)) REF struct block_device_partition *
NOTHROW(KCALL block_device_findpart)(struct block_device *__restrict self,
                                     lba_t part_min, lba_t part_max) {
	struct block_device_partition *result;
	SLIST_FOREACH (result, &self->bd_parts, bp_parts) {
		if (result->bp_min != part_min)
			continue;
		if (result->bp_max != part_max)
			continue;
		if (tryincref(result))
			break;
	}
	return result;
}


/* Create a new sub-partition for `master', placing it as the given address.
 * Following this, automatically register the new partition with `block_device_register_auto()',
 * after  assigning  the  name   `"%s%u" % (master->bd_name,MINOR(block_device_devno(return)))'.
 * NOTE: If another partition with the same `part_min' and `part_max', no new
 *       partition is created, and that  partition will be returned  instead.
 * @param: part_label:    The name of the partition, or `NULL'
 * @param: part_sysid:    The partition system ID, or `0'
 * @param: part_typeguid: The partition type GUID, or `NULL'
 * @param: part_partguid: The partition GUID, or `NULL' */
PUBLIC ATTR_RETNONNULL NONNULL((1)) REF struct block_device_partition *KCALL
block_device_makepart(struct blkdev *__restrict master,
                      lba_t part_min, lba_t part_max,
                      char const *part_label, size_t part_label_size,
                      u8 part_sysid, guid_t const *part_typeguid,
                      guid_t const *part_partguid, uintptr_half_t flags)
		THROWS(E_BADALLOC, E_WOULDBLOCK, ...) {
	struct block_device *dev;
	heapptr_t resptr;
	REF struct block_device_partition *result;
	assert(part_min <= part_max);
	assert(part_max <= master->bd_sector_count - (lba_t)1);
	dev = (struct block_device *)master;
	if (block_device_ispartition(dev)) {
		struct block_device_partition *master_part;
		master_part = (struct block_device_partition *)dev;
		part_min += master_part->bp_min;
		part_max += master_part->bp_min;
		dev = master_part->bp_master;
		assert(!block_device_ispartition(dev));
	}
	block_device_acquire_partlock_write(dev);
	result = block_device_findpart(dev, part_min, part_max);
	if likely(result) {
		sync_endwrite(&dev->bd_parts_lock);
		return result;
	}
	resptr = heap_alloc_nx(&kernel_locked_heap,
	                       sizeof(struct block_device_partition),
	                       GFP_LOCKED | GFP_CALLOC |
	                       GFP_PREFLT | GFP_ATOMIC);
	if unlikely(!heapptr_getsiz(resptr)) {
		sync_endwrite(&dev->bd_parts_lock);
		resptr = heap_alloc(&kernel_locked_heap,
		                    sizeof(struct block_device_partition),
		                    GFP_LOCKED | GFP_CALLOC | GFP_PREFLT);
		TRY {
			block_device_acquire_partlock_write(dev);
		} EXCEPT {
			heap_free(&kernel_locked_heap,
			          heapptr_getptr(resptr),
			          heapptr_getsiz(resptr),
			          GFP_CALLOC);
			RETHROW();
		}
		result = block_device_findpart(dev, part_min, part_max);
		if unlikely(result) {
			sync_endwrite(&dev->bd_parts_lock);
			heap_free(&kernel_locked_heap,
			          heapptr_getptr(resptr),
			          heapptr_getsiz(resptr),
			          GFP_CALLOC);
			return result;
		}
	}
	/* Setup the new partition. */
	result = (REF struct block_device_partition *)heapptr_getptr(resptr);
	result->bd_refcnt              = 1;
	result->bd_heapsize            = heapptr_getsiz(resptr);
	result->bd_type.dt_read        = &block_device_partition_read;
	result->bd_type.dt_write       = &block_device_partition_write;
	result->bd_type.dt_read_phys   = &block_device_partition_read_phys;
	result->bd_type.dt_write_phys  = &block_device_partition_write_phys;
	result->bd_type.dt_readv       = &block_device_partition_readv;
	result->bd_type.dt_writev      = &block_device_partition_writev;
	result->bd_type.dt_readv_phys  = &block_device_partition_readv_phys;
	result->bd_type.dt_writev_phys = &block_device_partition_writev_phys;
	result->bd_type.dt_ioctl       = &block_device_partition_ioctl;
	result->bd_flags               = flags | BLOCK_DEVICE_FLAG_PARTITION;
	result->bd_sector_size         = dev->bd_sector_size;
	result->bd_sector_count        = (part_max - part_min) + (lba_t)1;
	result->bd_total_bytes         = (pos_t)result->bd_sector_size * (pos_t)result->bd_sector_count;
	result->bp_master              = dev;
	result->bp_minaddr             = (pos_t)part_min * (pos_t)result->bd_sector_size;
	result->bp_min                 = part_min;
	result->bp_max                 = part_max;
	result->bp_sysid               = part_sysid;

	if (part_label) {
		memcpy(result->bp_label, part_label,
		       MIN(part_label_size, COMPILER_LENOF(result->bp_label) - 1),
		       sizeof(char));
	}
	if (part_typeguid)
		memcpy(&result->bp_typeguid, part_typeguid, sizeof(guid_t));
	if (part_partguid)
		memcpy(&result->bp_partguid, part_partguid, sizeof(guid_t));
	SLIST_INSERT(&dev->bd_parts, result, bp_parts);
	incref(dev);
	sync_endwrite(&dev->bd_parts_lock);
	/* Automatically register the newly created partition. */
	TRY {
		block_device_register_auto(result);
	} EXCEPT {
		decref(result);
		RETHROW();
	}
	return result;
}


/* Delete (unregister + unlink) all partitions of `self' */
PUBLIC NONNULL((1)) void KCALL
block_device_delparts(struct block_device *__restrict self)
		THROWS(E_WOULDBLOCK) {
	struct block_device_partition *part;
again:
	if (SLIST_EMPTY(&self->bd_parts))
		return;
	COMPILER_READ_BARRIER();
	block_device_acquire_partlock_write(self);
	SLIST_FOREACH (part, &self->bd_parts, bp_parts) {
		if (tryincref(part))
			break;
	}
	sync_endwrite(&self->bd_parts_lock);
	if (part) {
		FINALLY_DECREF_LIKELY(part);
		block_device_unregister(part);
		goto again;
	}
}

/* High-level  read/write  to/from  a  block-device,  on  a  per-byte   basis.
 * These functions are mainly intended for use by file-system drivers, as well
 * as for creating disk partitions.  - Regular user-space access usually  goes
 * through the VM data-block mapping interface,  which is backed by some  sort
 * of system which will call though to `block_device_(read|write)_async()', if
 * not `block_device_(read|write)_async_sector()'. */
FUNDEF NONNULL((1, 2)) void KCALL _block_device_read(struct block_device *__restrict self, VIRT CHECKED void *dst, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_BADALLOC, ...) ASMNAME("block_device_read");
FUNDEF NONNULL((1, 2)) void KCALL _block_device_write(struct block_device *__restrict self, VIRT CHECKED void const *src, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_IOERROR_READONLY, E_BADALLOC, ...) ASMNAME("block_device_write");
FUNDEF NONNULL((1)) size_t KCALL _block_device_sync(struct block_device *__restrict self) THROWS(E_IOERROR, E_IOERROR_READONLY, E_BADALLOC, ...) ASMNAME("block_device_sync");
FUNDEF NONNULL((1)) void KCALL _block_device_read_phys(struct block_device *__restrict self, physaddr_t dst, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_BADALLOC, ...) ASMNAME("block_device_read_phys");
FUNDEF NONNULL((1)) void KCALL _block_device_write_phys(struct block_device *__restrict self, physaddr_t src, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC, ...) ASMNAME("block_device_write_phys");
FUNDEF NONNULL((1, 2)) void KCALL _block_device_readv(struct block_device *__restrict self, struct iov_buffer *__restrict buf, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_BADALLOC, ...) ASMNAME("block_device_readv");
FUNDEF NONNULL((1, 2)) void KCALL _block_device_writev(struct block_device *__restrict self, struct iov_buffer *__restrict buf, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC, ...) ASMNAME("block_device_writev");
FUNDEF NONNULL((1, 2)) void KCALL _block_device_readv_phys(struct block_device *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_BADALLOC, ...) ASMNAME("block_device_readv_phys");
FUNDEF NONNULL((1, 2)) void KCALL _block_device_writev_phys(struct block_device *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC, ...) ASMNAME("block_device_writev_phys");



/* Read/write data to/from a block device or partition. */
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL _block_device_aread_sector)(struct block_device *__restrict self, USER CHECKED void *dst, size_t num_sectors, lba_t addr, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_BADALLOC, ...) ASMNAME("block_device_aread_sector");
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL _block_device_awrite_sector)(struct block_device *__restrict self, USER CHECKED void const *src, size_t num_sectors, lba_t addr, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC, ...) ASMNAME("block_device_awrite_sector");
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL _block_device_aread_phys_sector)(struct block_device *__restrict self, physaddr_t dst, size_t num_sectors, lba_t addr, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_BADALLOC, ...) ASMNAME("block_device_aread_phys_sector");
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL _block_device_awrite_phys_sector)(struct block_device *__restrict self, physaddr_t src, size_t num_sectors, lba_t addr, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC, ...) ASMNAME("block_device_awrite_phys_sector");
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL _block_device_areadv_sector)(struct block_device *__restrict self, struct iov_buffer *__restrict buf, size_t num_sectors, lba_t addr, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_BADALLOC, ...) ASMNAME("block_device_areadv_sector");
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL _block_device_awritev_sector)(struct block_device *__restrict self, struct iov_buffer *__restrict buf, size_t num_sectors, lba_t addr, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC, ...) ASMNAME("block_device_awritev_sector");
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL _block_device_areadv_phys_sector)(struct block_device *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_sectors, lba_t addr, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_BADALLOC, ...) ASMNAME("block_device_areadv_phys_sector");
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL _block_device_awritev_phys_sector)(struct block_device *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_sectors, lba_t addr, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC, ...) ASMNAME("block_device_awritev_phys_sector");
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL _block_device_aread)(struct block_device *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t device_position, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_BADALLOC, ...) ASMNAME("block_device_aread");
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL _block_device_awrite)(struct block_device *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t device_position, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC, ...) ASMNAME("block_device_awrite");
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL _block_device_aread_phys)(struct block_device *__restrict self, physaddr_t dst, size_t num_bytes, pos_t device_position, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_BADALLOC, ...) ASMNAME("block_device_aread_phys");
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL _block_device_awrite_phys)(struct block_device *__restrict self, physaddr_t src, size_t num_bytes, pos_t device_position, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC, ...) ASMNAME("block_device_awrite_phys");
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL _block_device_areadv)(struct block_device *__restrict self, struct iov_buffer *__restrict buf, size_t num_bytes, pos_t device_position, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_BADALLOC, ...) ASMNAME("block_device_areadv");
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL _block_device_awritev)(struct block_device *__restrict self, struct iov_buffer *__restrict buf, size_t num_bytes, pos_t device_position, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC, ...) ASMNAME("block_device_awritev");
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL _block_device_areadv_phys)(struct block_device *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_bytes, pos_t device_position, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_BADALLOC, ...) ASMNAME("block_device_areadv_phys");
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL _block_device_awritev_phys)(struct block_device *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_bytes, pos_t device_position, /*out*/ struct aio_handle *__restrict aio) THROWS_INDIRECT(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC, ...) ASMNAME("block_device_awritev_phys");
FUNDEF NONNULL((1)) void KCALL _block_device_read_sync(struct block_device *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_BADALLOC,E_SEGFAULT, ...) ASMNAME("block_device_read_sync");
FUNDEF NONNULL((1)) void KCALL _block_device_write_sync(struct block_device *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC,E_SEGFAULT, ...) ASMNAME("block_device_write_sync");
FUNDEF NONNULL((1)) void KCALL _block_device_read_phys_sync(struct block_device *__restrict self, physaddr_t dst, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_BADALLOC, ...) ASMNAME("block_device_read_phys_sync");
FUNDEF NONNULL((1)) void KCALL _block_device_write_phys_sync(struct block_device *__restrict self, physaddr_t src, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC, ...) ASMNAME("block_device_write_phys_sync");
FUNDEF NONNULL((1)) void KCALL _block_device_readv_sync(struct block_device *__restrict self, struct iov_buffer *__restrict buf, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_BADALLOC,E_SEGFAULT, ...) ASMNAME("block_device_readv_sync");
FUNDEF NONNULL((1)) void KCALL _block_device_writev_sync(struct block_device *__restrict self, struct iov_buffer *__restrict buf, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC,E_SEGFAULT, ...) ASMNAME("block_device_writev_sync");
FUNDEF NONNULL((1)) void KCALL _block_device_readv_phys_sync(struct block_device *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_BADALLOC, ...) ASMNAME("block_device_readv_phys_sync");
FUNDEF NONNULL((1)) void KCALL _block_device_writev_phys_sync(struct block_device *__restrict self, struct iov_physbuffer *__restrict buf, size_t num_bytes, pos_t device_position) THROWS(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC, ...) ASMNAME("block_device_writev_phys_sync");


#ifndef __INTELLISENSE__
DECL_END

#undef DEFINE_IO_READ
#undef DEFINE_IO_WRITE
#undef DEFINE_IO_SECTOR
#undef DEFINE_IO_PHYS
#undef DEFINE_IO_VECTOR

#define DEFINE_IO_READ 1
#define DEFINE_IO_SECTOR 1
#define DEFINE_IO_PHYS 1
#include "block-async-io.c.inl"
#define DEFINE_IO_READ 1
#define DEFINE_IO_SECTOR 1
#include "block-async-io.c.inl"
#define DEFINE_IO_WRITE 1
#define DEFINE_IO_SECTOR 1
#define DEFINE_IO_PHYS 1
#include "block-async-io.c.inl"
#define DEFINE_IO_WRITE 1
#define DEFINE_IO_SECTOR 1
#include "block-async-io.c.inl"

#define DEFINE_IO_VECTOR 1
#define DEFINE_IO_READ 1
#define DEFINE_IO_SECTOR 1
#define DEFINE_IO_PHYS 1
#include "block-async-io.c.inl"
#define DEFINE_IO_VECTOR 1
#define DEFINE_IO_READ 1
#define DEFINE_IO_SECTOR 1
#include "block-async-io.c.inl"
#define DEFINE_IO_VECTOR 1
#define DEFINE_IO_WRITE 1
#define DEFINE_IO_SECTOR 1
#define DEFINE_IO_PHYS 1
#include "block-async-io.c.inl"
#define DEFINE_IO_VECTOR 1
#define DEFINE_IO_WRITE 1
#define DEFINE_IO_SECTOR 1
#include "block-async-io.c.inl"

#define DEFINE_IO_READ 1
#define DEFINE_IO_PHYS 1
#include "block-async-io.c.inl"
#define DEFINE_IO_READ 1
#include "block-async-io.c.inl"
#define DEFINE_IO_WRITE 1
#define DEFINE_IO_PHYS 1
#include "block-async-io.c.inl"
#define DEFINE_IO_WRITE 1
#include "block-async-io.c.inl"

#define DEFINE_IO_VECTOR 1
#define DEFINE_IO_READ 1
#define DEFINE_IO_PHYS 1
#include "block-async-io.c.inl"
#define DEFINE_IO_READ 1
#define DEFINE_IO_VECTOR 1
#include "block-async-io.c.inl"
#define DEFINE_IO_VECTOR 1
#define DEFINE_IO_WRITE 1
#define DEFINE_IO_PHYS 1
#include "block-async-io.c.inl"
#define DEFINE_IO_VECTOR 1
#define DEFINE_IO_WRITE 1
#include "block-async-io.c.inl"

DECL_BEGIN
#endif



LOCAL NOBLOCK void
NOTHROW(KCALL log_sync)(struct block_device *__restrict self, lba_t sector_id) {
	printk(KERN_INFO "[blk:\"/dev/%#q\",devno="
	                 "%.2" PRIxN(__SIZEOF_MAJOR_T__) ":%.2" PRIxN(__SIZEOF_MINOR_T__) "]"
	                 " Syncing sector %#" PRIx64 " (%#" PRIx64 "-%#" PRIx64 ")\n",
	       self->bd_name,
	       MAJOR(block_device_devno(self)),
	       MINOR(block_device_devno(self)),
	       (u64)sector_id, (u64)(sector_id * self->bd_sector_size),
	       (u64)(((sector_id + 1) * self->bd_sector_size) - 1));
}


/* Synchronous all cached sectors that have been modified by prior calls to `block_device_write()' */
PUBLIC NONNULL((1)) size_t KCALL
_block_device_sync(struct block_device *__restrict self)
		THROWS(E_IOERROR, E_IOERROR_READONLY, E_BADALLOC, ...) {
	unsigned int i;
	size_t result = 0;
	struct aio_multihandle_generic hand;
	if (block_device_ispartition(self))
		self = ((struct block_device_partition *)self)->bp_master;
	assert(!block_device_ispartition(self));
	assert(!task_wasconnected());
	assert(self->bd_cache_ssiz != 0);
	SCOPED_WRITELOCK(&self->bd_cache_lock);
	aio_multihandle_generic_init(&hand);
	TRY {
		for (i = 0; i < BD_MAX_CACHE_SECTORS; ++i) {
			struct aio_handle *handle;
			byte_t *cache_addr;
			if ((self->bd_cache[i].cs_flags & (BD_CACHED_SECTOR_FPRESENT | BD_CACHED_SECTOR_FCHANGED)) !=
			    (BD_CACHED_SECTOR_FPRESENT | BD_CACHED_SECTOR_FCHANGED))
				continue;
			cache_addr = self->bd_cache_base + i * self->bd_cache_ssiz;
			handle     = aio_multihandle_allochandle(&hand);
			TRY {
				lba_t sector_id;
				sector_id = self->bd_cache[i].cs_addr;
				log_sync(self, sector_id);
				(*self->bd_type.dt_write)(self,
				                          cache_addr,
				                          1,
				                          sector_id,
				                          handle);
				++result;
			} EXCEPT {
				aio_handle_init_noop(handle, AIO_COMPLETION_FAILURE);
				break;
			}
		}
		aio_multihandle_done(&hand);
	} EXCEPT {
		aio_multihandle_fail(&hand);
	}
	TRY {
		aio_multihandle_generic_waitfor(&hand);
		aio_multihandle_generic_checkerror(&hand);
	} EXCEPT {
		aio_multihandle_generic_fini(&hand);
		RETHROW();
	}
	aio_multihandle_generic_fini(&hand);
	if (result != 0) {
		/* Clear all of the CHANGED bits. */
		for (i = 0; i < BD_MAX_CACHE_SECTORS; ++i) {
			if (!(self->bd_cache[i].cs_flags & BD_CACHED_SECTOR_FPRESENT))
				continue;
			self->bd_cache[i].cs_flags &= ~BD_CACHED_SECTOR_FCHANGED;
		}
		printk(KERN_NOTICE "[blk:\"/dev/%#q\",devno="
		                   "%.2" PRIxN(__SIZEOF_MAJOR_T__) ":"
		                   "%.2" PRIxN(__SIZEOF_MINOR_T__) "] "
		                   "Block device was synced\n",
		       self->bd_name,
		       MAJOR(block_device_devno(self)),
		       MINOR(block_device_devno(self)));
	}
	return result;
}


LOCAL NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL block_unset_modified)(struct block_device *__restrict self,
                                    unsigned int cache_index) {
	if ((self->bd_cache[cache_index].cs_flags & (BD_CACHED_SECTOR_FPRESENT | BD_CACHED_SECTOR_FCHANGED)) !=
	    (BD_CACHED_SECTOR_FPRESENT | BD_CACHED_SECTOR_FCHANGED))
		return false;
	self->bd_cache[cache_index].cs_flags &= ~BD_CACHED_SECTOR_FCHANGED;
	return true;
}


struct extended_save_handle {
	struct aio_handle_generic sh_handle; /* The handle used for saving. */
	unsigned int              sh_index;  /* Index of the cache that is being saved. */
};

PRIVATE NONNULL((1)) unsigned int KCALL
allocate_cache_sector(struct block_device *__restrict self, lba_t addr) {
	unsigned int result;
	byte_t *cache_addr;
	struct aio_handle_generic handle;
again:
	assert(!task_wasconnected());
	assert(self->bd_cache_ssiz >= self->bd_sector_size);
	assert(self->bd_sector_size != 0);
	/* Load a new sector from cache. */
	result = self->bd_cache_cnxt++;
	if (self->bd_cache_cnxt >= BD_MAX_CACHE_SECTORS)
		self->bd_cache_cnxt = 0;
	assert(self->bd_cache_ssiz >= self->bd_sector_size);
	assert(self->bd_sector_size != 0);
	assertf(result < BD_MAX_CACHE_SECTORS, "result = %u", result);
	if ((self->bd_cache[result].cs_flags & (BD_CACHED_SECTOR_FPRESENT | BD_CACHED_SECTOR_FCHANGED)) ==
	    (BD_CACHED_SECTOR_FPRESENT | BD_CACHED_SECTOR_FCHANGED)) {
		unsigned int i;
		struct extended_save_handle *ex_handles = NULL;
		unsigned int ex_handles_count           = 0;
		/* Must save the old contents of this sector. */
		cache_addr = self->bd_cache_base + result * self->bd_cache_ssiz;
		aio_handle_generic_init(&handle);
		assert(self->bd_type.dt_write);
		TRY {
			lba_t sector_id;
			sector_id = self->bd_cache[result].cs_addr;
			log_sync(self, sector_id);
			(*self->bd_type.dt_write)(self, cache_addr, 1,
			                          sector_id, &handle);
		} EXCEPT {
			aio_handle_init_noop(&handle, AIO_COMPLETION_FAILURE);
		}
		/* Search for additional sectors which may need saving, so we can improve
		 * performance  by  saving a  whole bunch  of  different blocks  at once. */
		for (i = 0; i < BD_MAX_CACHE_SECTORS; ++i) {
			struct extended_save_handle *new_handles;
			struct aio_handle_generic *my_handle;
			if (ATOMIC_READ(handle.hg_status) != 0)
				break; /* Stop once the initial write has been completed, so we don't waste any time. */
			if (i == result)
				continue;
			if ((self->bd_cache[i].cs_flags & (BD_CACHED_SECTOR_FPRESENT | BD_CACHED_SECTOR_FCHANGED)) !=
			    (BD_CACHED_SECTOR_FPRESENT | BD_CACHED_SECTOR_FCHANGED))
				continue;
			new_handles = (struct extended_save_handle *)krealloc_nx(ex_handles,
			                                                         (ex_handles_count + 1) *
			                                                         sizeof(struct extended_save_handle),
			                                                         GFP_LOCKED | GFP_PREFLT);
			if unlikely(!new_handles)
				continue; /* Failed to allocate more extended handles. */
			ex_handles = new_handles;
			my_handle  = &ex_handles[ex_handles_count].sh_handle;
			aio_handle_generic_init(my_handle);
			ex_handles[ex_handles_count].sh_index = i;
			cache_addr = self->bd_cache_base + i * self->bd_cache_ssiz;
			TRY {
				lba_t sector_id;
				sector_id = self->bd_cache[i].cs_addr;
				log_sync(self, sector_id);
				(*self->bd_type.dt_write)(self, cache_addr, 1,
				                          sector_id, my_handle);
			} EXCEPT {
				aio_handle_init_noop(my_handle, AIO_COMPLETION_FAILURE);
			}
			++ex_handles_count;
		}
		/* Wait for secondary task to be completed. */
		if (ex_handles) {
			TRY {
				while (ex_handles_count) {
					struct aio_handle_generic *my_handle;
					--ex_handles_count;
					my_handle = &ex_handles[ex_handles_count].sh_handle;
					aio_handle_generic_waitfor(my_handle);
					/* Mark this handle as having been successfully saved. */
					if likely(my_handle->hg_status == AIO_COMPLETION_SUCCESS)
						block_unset_modified(self, ex_handles[ex_handles_count].sh_index);
					aio_handle_generic_fini(my_handle);
				}
			} EXCEPT {
				/* Cancel all remaining I/O operations. */
				while (ex_handles_count) {
					struct aio_handle_generic *my_handle;
					--ex_handles_count;
					my_handle = &ex_handles[ex_handles_count].sh_handle;
					aio_handle_cancel(my_handle);
					aio_handle_generic_fini(my_handle);
				}
				kfree(ex_handles);
				RETHROW();
			}
			kfree(ex_handles);
		}
		TRY {
			/* Wait for the primary task to be completed. */
check_handle_state_for_save:
			switch (__builtin_expect(handle.hg_status, AIO_COMPLETION_SUCCESS)) {

			case AIO_COMPLETION_CANCEL:
				/* Shouldn't happen: If the operation was aborted, re-start. */
				goto again;

			case AIO_COMPLETION_SUCCESS:
				break;

			case AIO_COMPLETION_FAILURE:
				/* Propagate errors as exceptions. */
				memcpy(&THIS_EXCEPTION_DATA,
				       &handle.hg_error,
				       sizeof(handle.hg_error));
				error_throw_current();
				break;

			default:
				aio_handle_generic_waitfor(&handle);
				goto check_handle_state_for_save;
			}
		} EXCEPT {
			aio_handle_generic_fini(&handle);
			RETHROW();
		}
		aio_handle_generic_fini(&handle);
	}
	assert(self->bd_cache_ssiz >= self->bd_sector_size);
	assert(self->bd_sector_size != 0);
	assertf(result < BD_MAX_CACHE_SECTORS, "result = %u", result);
	/* Populate the new cache with the intended sector page. */
	self->bd_cache[result].cs_addr  = addr;
	self->bd_cache[result].cs_flags = BD_CACHED_SECTOR_FNORMAL;
	cache_addr                      = self->bd_cache_base + result * self->bd_cache_ssiz;
	assert(self->bd_cache_ssiz >= self->bd_sector_size);
	assert(self->bd_sector_size != 0);
	aio_handle_generic_init(&handle);
	COMPILER_BARRIER();
	TRY {
		assert(self->bd_type.dt_read);
		(*self->bd_type.dt_read)(self,
		                         cache_addr,
		                         1,
		                         addr,
		                         &handle);
	} EXCEPT {
		aio_handle_init_noop(&handle, AIO_COMPLETION_FAILURE);
	}
	COMPILER_BARRIER();
	TRY {
		/* Wait for the read to have completed. */
check_handle_state_for_load:
		switch (__builtin_expect(handle.hg_status, AIO_COMPLETION_SUCCESS)) {

		case AIO_COMPLETION_CANCEL:
			/* Shouldn't happen: If the operation was aborted, re-start. */
			goto again;

		case AIO_COMPLETION_SUCCESS:
			break;

		case AIO_COMPLETION_FAILURE:
			/* Propagate errors as exceptions. */
			memcpy(&THIS_EXCEPTION_DATA,
			       &handle.hg_error,
			       sizeof(handle.hg_error));
			error_throw_current();
			break;

		default:
			aio_handle_generic_waitfor(&handle);
			goto check_handle_state_for_load;
		}
	} EXCEPT {
		aio_handle_generic_fini(&handle);
		RETHROW();
	}
	aio_handle_generic_fini(&handle);
	/* Now that it's been loaded from disk, mark the cache-page as present */
	self->bd_cache[result].cs_flags = BD_CACHED_SECTOR_FPRESENT;
	return result;
}





PUBLIC NONNULL((1)) void KCALL
_block_device_read_phys(struct block_device *__restrict self,
                        physaddr_t dst, size_t num_bytes,
                        pos_t device_position)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	byte_t *buf;
	PHYS_VARS;
	IF_PHYS_IDENTITY(dst, num_bytes, {
		block_device_read(self, PHYS_TO_IDENTITY(dst),
		                  num_bytes, device_position);
		return;
	});
	if unlikely(!num_bytes)
		return;
	buf = phys_pushaddr(dst);
	TRY {
		for (;;) {
			size_t page_bytes;
			page_bytes = PAGESIZE - ((uintptr_t)buf & PAGEMASK);
			if (page_bytes > num_bytes)
				page_bytes = num_bytes;
			/* Copy memory. */
			block_device_read(self, buf, page_bytes, device_position);
			if (page_bytes >= num_bytes)
				break;
			num_bytes -= page_bytes;
			dst += page_bytes;
			device_position += (pos_t)page_bytes;
			buf = phys_loadpage(dst);
		}
	} EXCEPT {
		phys_pop();
		RETHROW();
	}
	phys_pop();
}

PUBLIC NONNULL((1)) void KCALL
_block_device_write_phys(struct block_device *__restrict self,
                         physaddr_t src, size_t num_bytes,
                         pos_t device_position)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	byte_t const *buf;
	PHYS_VARS;
	IF_PHYS_IDENTITY(src, num_bytes, {
		block_device_write(self, PHYS_TO_IDENTITY(src),
		                   num_bytes, device_position);
		return;
	});
	if unlikely(!num_bytes)
		return;
	buf = phys_pushaddr(src);
	TRY {
		for (;;) {
			size_t page_bytes;
			page_bytes = PAGESIZE - ((uintptr_t)buf & PAGEMASK);
			if (page_bytes > num_bytes)
				page_bytes = num_bytes;
			/* Copy memory. */
			block_device_write(self, buf, page_bytes, device_position);
			if (page_bytes >= num_bytes)
				break;
			num_bytes -= page_bytes;
			src += page_bytes;
			device_position += (pos_t)page_bytes;
			buf = phys_loadpage(src);
		}
	} EXCEPT {
		phys_pop();
		RETHROW();
	}
	phys_pop();
}


PUBLIC NONNULL((1, 2)) void KCALL
_block_device_readv(struct block_device *__restrict self,
                    struct iov_buffer *__restrict buf,
                    size_t num_bytes, pos_t device_position)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct iov_entry ent;
	assert(iov_buffer_size(buf) == num_bytes);
	(void)num_bytes;
	IOV_BUFFER_FOREACH(ent, buf) {
		_block_device_read(self,
		                   ent.ive_base,
		                   ent.ive_size,
		                   device_position);
		device_position += ent.ive_size;
	}
}

PUBLIC NONNULL((1, 2)) void KCALL
_block_device_writev(struct block_device *__restrict self,
                     struct iov_buffer *__restrict buf,
                     size_t num_bytes, pos_t device_position)
		THROWS(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC, ...) {
	struct iov_entry ent;
	assert(iov_buffer_size(buf) == num_bytes);
	(void)num_bytes;
	IOV_BUFFER_FOREACH(ent, buf) {
		_block_device_write(self,
		                    ent.ive_base,
		                    ent.ive_size,
		                    device_position);
		device_position += ent.ive_size;
	}
}

PUBLIC NONNULL((1, 2)) void KCALL
_block_device_readv_phys(struct block_device *__restrict self,
                         struct iov_physbuffer *__restrict buf,
                         size_t num_bytes, pos_t device_position)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct iov_physentry ent;
	assert(iov_physbuffer_size(buf) == num_bytes);
	(void)num_bytes;
	IOV_PHYSBUFFER_FOREACH(ent, buf) {
		_block_device_read_phys(self,
		                        ent.ive_base,
		                        ent.ive_size,
		                        device_position);
		device_position += ent.ive_size;
	}
}

PUBLIC NONNULL((1, 2)) void KCALL
_block_device_writev_phys(struct block_device *__restrict self,
                          struct iov_physbuffer *__restrict buf,
                          size_t num_bytes, pos_t device_position)
		THROWS(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC, ...) {
	struct iov_physentry ent;
	assert(iov_physbuffer_size(buf) == num_bytes);
	(void)num_bytes;
	IOV_PHYSBUFFER_FOREACH(ent, buf) {
		_block_device_write_phys(self,
		                         ent.ive_base,
		                         ent.ive_size,
		                         device_position);
		device_position += ent.ive_size;
	}
}



/* @return: BD_MAX_CACHE_SECTORS: The sector `addr' isn't being cached. */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) unsigned int
NOTHROW(KCALL find_cached_sector)(struct block_device const *__restrict self, lba_t addr) {
	unsigned int i;
	for (i = 0; i < BD_MAX_CACHE_SECTORS; ++i) {
		if (!(self->bd_cache[i].cs_flags & BD_CACHED_SECTOR_FPRESENT))
			continue;
		if (self->bd_cache[i].cs_addr != addr)
			continue;
		break;
	}
	return i;
}


PUBLIC NONNULL((1, 2)) void KCALL
_block_device_read(struct block_device *__restrict self,
                   VIRT CHECKED void *dst, size_t num_bytes,
                   pos_t device_position) {
	pos_t end_addr;
	if unlikely(!num_bytes)
		return;
	if unlikely(OVERFLOW_UADD(device_position, num_bytes, &end_addr) ||
	            end_addr >= self->bd_total_bytes) {
		size_t new_num_bytes;
		if (device_position >= self->bd_total_bytes) {
			memset(dst, 0, num_bytes);
			return;
		}
		new_num_bytes = (size_t)(self->bd_total_bytes - device_position);
		assert(num_bytes > new_num_bytes);
		memset((byte_t *)dst + new_num_bytes, 0, num_bytes - new_num_bytes);
		num_bytes = new_num_bytes;
	}
	assert(!task_wasconnected());
	/* Deal with partition offsets. */
	if likely(block_device_ispartition(self)) {
		device_position += ((struct block_device_partition *)self)->bp_minaddr;
		self = ((struct block_device_partition *)self)->bp_master;
		assert(!block_device_ispartition(self));
		/* Also check the drive master for being read-only. */
		if unlikely(self->bd_flags & BLOCK_DEVICE_FLAG_READONLY)
			THROW(E_IOERROR_READONLY, (uintptr_t)E_IOERROR_SUBSYSTEM_HARDDISK);
	}
again_read_cache:
	rwlock_read(&self->bd_cache_lock);
	TRY {
		for (;;) {
			lba_t block_lba;
			size_t block_offset, block_size;
			unsigned int cache_index;
			block_lba    = (lba_t)(device_position / self->bd_sector_size);
			block_offset = (size_t)(device_position % self->bd_sector_size);
			block_size   = self->bd_sector_size - block_offset;
			if (block_size > num_bytes)
				block_size = num_bytes;
			cache_index = find_cached_sector(self, block_lba);
			if (cache_index >= BD_MAX_CACHE_SECTORS) {
				assert(cache_index == BD_MAX_CACHE_SECTORS);
				rwlock_write(&self->bd_cache_lock);
				FINALLY_ENDWRITE(&self->bd_cache_lock);
				cache_index = allocate_cache_sector(self, block_lba);
				assert(cache_index < BD_MAX_CACHE_SECTORS);
			}
			/* Copy sector data. */
			memcpy(dst,
			       self->bd_cache_base + (cache_index * self->bd_cache_ssiz) + block_offset,
			       block_size);
			if (block_size >= num_bytes)
				break;
			dst = (byte_t *)dst + block_size;
			device_position += (pos_t)block_size;
			num_bytes -= block_size;
		}
	} EXCEPT {
		if (rwlock_endread(&self->bd_cache_lock))
			goto again_read_cache;
		RETHROW();
	}
	rwlock_endread(&self->bd_cache_lock);
}

PUBLIC NONNULL((1, 2)) void KCALL
_block_device_write(struct block_device *__restrict self,
                    VIRT CHECKED void const *src,
                    size_t num_bytes, pos_t device_position) {
	pos_t end_addr;
	if unlikely(!num_bytes)
		return;
	if unlikely(self->bd_flags & BLOCK_DEVICE_FLAG_READONLY)
		THROW(E_IOERROR_READONLY, (uintptr_t)E_IOERROR_SUBSYSTEM_HARDDISK);
	if unlikely(OVERFLOW_UADD(device_position, num_bytes, &end_addr) ||
	            end_addr >= self->bd_total_bytes)
		THROW(E_IOERROR_BADBOUNDS, (uintptr_t)E_IOERROR_SUBSYSTEM_HARDDISK);
	assert(!task_wasconnected());
	/* Deal with partition offsets. */
	if likely(block_device_ispartition(self)) {
		device_position += ((struct block_device_partition *)self)->bp_minaddr;
		self = ((struct block_device_partition *)self)->bp_master;
		assert(!block_device_ispartition(self));
		/* Also check the drive master for being read-only. */
		if unlikely(self->bd_flags & BLOCK_DEVICE_FLAG_READONLY)
			THROW(E_IOERROR_READONLY, (uintptr_t)E_IOERROR_SUBSYSTEM_HARDDISK);
	}
	{
		SCOPED_WRITELOCK(&self->bd_cache_lock);
		for (;;) {
			lba_t block_lba;
			size_t block_offset, block_size;
			unsigned int cache_index;
			block_lba    = (lba_t)(device_position / self->bd_sector_size);
			block_offset = (size_t)(device_position % self->bd_sector_size);
			block_size   = self->bd_sector_size - block_offset;
			if (block_size > num_bytes)
				block_size = num_bytes;
			cache_index = find_cached_sector(self, block_lba);
			if (cache_index >= BD_MAX_CACHE_SECTORS) {
				assert(cache_index == BD_MAX_CACHE_SECTORS);
				cache_index = allocate_cache_sector(self, block_lba);
				assert(cache_index < BD_MAX_CACHE_SECTORS);
			}
			assert(self->bd_cache[cache_index].cs_flags & BD_CACHED_SECTOR_FPRESENT);
			/* Copy sector data. */
			memcpy(self->bd_cache_base + (cache_index * self->bd_cache_ssiz) + block_offset,
			       src, block_size);
			/* Set the was-modified flag. */
			self->bd_cache[cache_index].cs_flags |= BD_CACHED_SECTOR_FCHANGED;
			if (block_size >= num_bytes)
				break;
			src = (byte_t const *)src + block_size;
			device_position += (pos_t)block_size;
			num_bytes -= block_size;
		}
	}
}

#ifdef CONFIG_HAVE_DEBUGGER
PRIVATE ATTR_DBGTEXT void KCALL
do_dump_block_device(struct blkdev *__restrict self,
                     size_t longest_device_name,
                     size_t longest_driver_name) {
	u64 total_bytes_adj = (u64)self->bd_total_bytes;
	char const *total_bytes_name = DBGSTR("b");
	REF struct driver *drv;
	if (total_bytes_adj >= (u64)1024 * 1024 * 1024) {
		total_bytes_adj /= (u64)1024 * 1024 * 1024;
		total_bytes_name = DBGSTR("GiB");
	} else if (total_bytes_adj >= (u64)1024 * 1024) {
		total_bytes_adj /= (u64)1024 * 1024;
		total_bytes_name = DBGSTR("MiB");
	} else if (total_bytes_adj >= (u64)1024) {
		total_bytes_adj /= (u64)1024;
		total_bytes_name = DBGSTR("KiB");
	}
	drv = driver_fromaddr(block_device_ispartition(self)
	                      ? (void *)((struct block_device_partition *)self)->bp_master->bd_type.dt_read
	                      : (void *)self->bd_type.dt_read);
	dbg_printf(DBGSTR("/dev/" AC_WHITE("%-*s") "  "
	                  "%3.2" PRIxN(__SIZEOF_MAJOR_T__) ":"
	                  "%-3.2" PRIxN(__SIZEOF_MINOR_T__) "  "
	                  "%*-s  "
	                  "%5" PRIu64 "%s  "
	                  "%-11" PRIu64 "  "
	                  "%" PRIuSIZ "\n"),
	           (unsigned int)longest_device_name, self->bd_name,
	           (unsigned int)MAJOR(block_device_devno(self)),
	           (unsigned int)MINOR(block_device_devno(self)),
	           (unsigned int)longest_driver_name,
	           drv ? drv->d_name : "?",
	           total_bytes_adj, total_bytes_name,
	           (u64)self->bd_sector_count,
	           (size_t)self->bd_sector_size);
	xdecref_nokill(drv);
}

PRIVATE ATTR_DBGTEXT void KCALL
dump_block_device(struct blkdev *__restrict self,
                  size_t longest_device_name,
                  size_t longest_driver_name) {
again:
	if (!block_device_ispartition(self)) {
		struct block_device *me;
		struct block_device_partition *parts;
		me = (struct block_device *)self;
		do_dump_block_device(self,
		                     longest_device_name,
		                     longest_driver_name);
		SLIST_FOREACH (parts, &me->bd_parts, bp_parts) {
			do_dump_block_device(parts,
			                     longest_device_name,
			                     longest_driver_name);
		}
	}
	if (self->bd_devlink.a_min) {
		if (self->bd_devlink.a_max) {
			dump_block_device(self->bd_devlink.a_max,
			                  longest_device_name,
			                  longest_driver_name);
		}
		self = self->bd_devlink.a_min;
		goto again;
	}
	if (self->bd_devlink.a_max) {
		self = self->bd_devlink.a_max;
		goto again;
	}
}

PRIVATE ATTR_DBGTEXT void KCALL
gather_longest_name_lengths(struct blkdev *__restrict self,
                            size_t *__restrict pmax_device_namelen,
                            size_t *__restrict pmax_driver_namelen) {
	REF struct driver *drv;
	size_t namelen;
again:
	namelen = strlen(self->bd_name);
	if (*pmax_device_namelen < namelen)
		*pmax_device_namelen = namelen;
	drv = driver_fromaddr(block_device_ispartition(self)
	                      ? (void *)((struct block_device_partition *)self)->bp_master->bd_type.dt_read
	                      : (void *)self->bd_type.dt_read);
	if (drv) {
		namelen = strlen(drv->d_name);
		if (*pmax_driver_namelen < namelen)
			*pmax_driver_namelen = namelen;
		decref_nokill(drv);
	}
	if (self->bd_devlink.a_min) {
		if (self->bd_devlink.a_max) {
			gather_longest_name_lengths(self->bd_devlink.a_max,
			                            pmax_device_namelen,
			                            pmax_driver_namelen);
		}
		self = self->bd_devlink.a_min;
		goto again;
	}
	if (self->bd_devlink.a_max) {
		self = self->bd_devlink.a_max;
		goto again;
	}
}

DBG_COMMAND(lsblk,
            "lsblk\n"
            "\tList all defined block devices\n") {
	size_t longest_device_name = COMPILER_STRLEN("name");
	size_t longest_driver_name = COMPILER_STRLEN("driver");
	if (block_device_tree) {
		gather_longest_name_lengths(block_device_tree,
		                            &longest_device_name,
		                            &longest_driver_name);
	}
	dbg_print(DBGSTR("     name"));
	if (longest_device_name > COMPILER_STRLEN("name"))
		format_repeat(&dbg_printer, NULL, ' ', longest_device_name - COMPILER_STRLEN("name"));
	dbg_print(DBGSTR("  devno    driver"));
	if (longest_driver_name > COMPILER_STRLEN("driver"))
		format_repeat(&dbg_printer, NULL, ' ', longest_driver_name - COMPILER_STRLEN("driver"));
	dbg_print(DBGSTR("  size      sectors      sector-size\n"));
	if (block_device_tree) {
		dump_block_device(block_device_tree,
		                  longest_device_name,
		                  longest_driver_name);
	}
	return 0;
}


#endif /* CONFIG_HAVE_DEBUGGER */

DECL_END
#endif /* !CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_SRC_DEV_BLOCK_C */
