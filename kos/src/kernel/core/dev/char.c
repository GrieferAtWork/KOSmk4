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
#ifndef GUARD_KERNEL_SRC_DEV_CHAR_C
#define GUARD_KERNEL_SRC_DEV_CHAR_C 1
#define _KOS_SOURCE 1
#define __WANT_CHRDEV_NEXTLINK

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_FS
#include <debugger/config.h>
#include <debugger/hook.h>
#include <debugger/io.h>
#include <dev/char.h>
#include <dev/keyboard.h>
#include <dev/mouse.h>
#include <dev/pty.h>
#include <dev/tty.h>
#include <fs/node.h>
#include <fs/ramfs.h>
#include <fs/vfs.h>
#include <kernel/aio.h>
#include <kernel/except.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/heap.h>
#include <kernel/iovec.h>
#include <kernel/malloc.h>
#include <kernel/mman/driver.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <kernel/user.h>

#include <hybrid/atomic.h>

#include <kos/dev.h>
#include <kos/except/reason/fs.h>
#include <kos/except/reason/inval.h>
#include <sys/stat.h>
#include <sys/types.h> /* loff_t */

#include <assert.h>
#include <errno.h>
#include <format-printer.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

/* Implement the ABI for the address tree used by chrdev. */
#define ATREE(x)      cdev_tree_##x
#define ATREE_CALL    KCALL
#define ATREE_NOTHROW NOTHROW
#define Tkey          dev_t
#define T             struct chrdev
#define N_NODEPATH    cd_devlink
#define ATREE_SINGLE  1
#include <hybrid/sequence/atree-abi.h>
#undef ATREE_SINGLE

DECL_BEGIN

#define CHARACTER_DEVICE_GFP     GFP_LOCKED
#if (CHARACTER_DEVICE_GFP & GFP_LOCKED) != 0
#define CHARACTER_DEVICE_HEAP   &kernel_locked_heap
#else /* (CHARACTER_DEVICE_GFP & GFP_LOCKED) != 0 */
#define CHARACTER_DEVICE_HEAP   &kernel_default_heap
#endif /* (CHARACTER_DEVICE_GFP & GFP_LOCKED) == 0 */


/* The tree used to quickly look up a character device from its ID */
PRIVATE /*REF_IF(!(->cd_flags & CHARACTER_DEVICE_FLAG_WEAKREG))*/
ATREE_HEAD(struct chrdev) chrdev_tree = NULL;
PRIVATE dev_t character_device_next_auto = MKDEV(DEV_MAJOR_AUTO,0);
PRIVATE struct atomic_rwlock character_device_lock = ATOMIC_RWLOCK_INIT;
DEFINE_DBG_BZERO_OBJECT(character_device_lock);

/* [0..1] Chain of weakly referenced, dead character devices.
 * These are serviced whenever a lock to `character_device_lock' is acquired. */
PRIVATE WEAK struct chrdev *dead_character_devices = NULL;
#define dead_character_devices_NEXTP(x) (x)->cd_nextdead

LOCAL NOBLOCK void
NOTHROW(KCALL character_device_free)(struct chrdev *__restrict self) {
	decref(self->cd_type.ct_driver);
	heap_free(CHARACTER_DEVICE_HEAP,
	          self,
	          self->cd_heapsize,
	          GFP_NORMAL);
}

LOCAL NOBLOCK void
NOTHROW(KCALL remove_character_device_from_tree)(struct chrdev *__restrict self) {
	struct chrdev *removed;
	if (self->cd_devlink.a_vaddr != DEV_UNSET) {
		removed = cdev_tree_remove(&chrdev_tree,
								   chrdev_devno(self));
		if unlikely(removed != self) {
			if likely(removed)
				cdev_tree_insert(&chrdev_tree, removed);
		}
	}
}

#define must_service_dead_character_devices() \
	(ATOMIC_READ(dead_character_devices) != NULL)
PRIVATE NOBLOCK ATTR_COLD void
NOTHROW(KCALL service_dead_character_devices)(void) {
	struct chrdev *chain, *next;
	chain = ATOMIC_XCH(dead_character_devices, NULL);
	while (chain) {
		next = dead_character_devices_NEXTP(chain);
		/* Remove the device from the tree. */
		remove_character_device_from_tree(chain);
		character_device_free(chain);
		chain = next;
	}
}

DECL_END

/* Define the LOCK api for accessing `character_device_lock' */
#define SERLOCK(name)         cdl_##name
#define SERLOCK_LOCK          &character_device_lock
#define SERLOCK_SERVICE()     service_dead_character_devices()
#define SERLOCK_MUSTSERVICE() must_service_dead_character_devices()
#include <hybrid/sync/service-lock.h>

DECL_BEGIN

/* Destroy a given character device. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL chrdev_destroy)(struct chrdev *__restrict self) {
	assert(self->cd_type.ct_driver);
	/* Invoke a custom finalizer callback */
	if (self->cd_type.ct_fini)
		(*self->cd_type.ct_fini)(self);
	/* Check if the device should be removed from devfs, and drop
	 * the references  held to  its  INode and  directory  entry. */
	if (self->cd_devfs_inode) {
		devfs_remove(self->cd_devfs_inode, /* No-op if already done... */
		             self->cd_devfs_entry);
		decref_likely(self->cd_devfs_inode);
		decref_likely(self->cd_devfs_entry);
	}
	if (self->cd_flags & CHARACTER_DEVICE_FLAG_WEAKREG) {
		if (self->cd_devlink.a_vaddr != DEV_UNSET) {
			if (cdl_trywrite()) {
				remove_character_device_from_tree(self);
				cdl_endwrite();
			} else {
				struct chrdev *next;
				/* Add the device to the chain of devices that are pending to be removed. */
				do {
					next = ATOMIC_READ(dead_character_devices);
					ATOMIC_WRITE(dead_character_devices_NEXTP(self), next);
				} while (!ATOMIC_CMPXCH_WEAK(dead_character_devices, next, self));
				/* Try to service the chain of pending devices (in case we've
				 * added ours after the tree had already been unlocked again) */
				cdl_service();
				return;
			}
		}
	} else {
		assert(self->cd_devlink.a_vaddr == DEV_UNSET);
	}
	character_device_free(self);
}

/* Allocate and initialize a new character device.
 * The caller must still initialize:
 *   >> return->cd_type;
 * As well as optionally:
 *   >> return->cd_name
 */
PUBLIC ATTR_MALLOC ATTR_RETNONNULL WUNUSED REF struct chrdev *KCALL
chrdev_alloc(struct driver *__restrict owner,
                       size_t structure_size,
                       size_t structure_align)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	REF struct chrdev *result;
	heapptr_t resptr;
	assert(structure_size >= sizeof(struct chrdev));
	assert(owner);
	resptr = heap_align(CHARACTER_DEVICE_HEAP,
	                    structure_align, 0,
	                    structure_size,
	                    CHARACTER_DEVICE_GFP |
	                    GFP_PREFLT |
	                    GFP_CALLOC);
	result                    = (REF struct chrdev *)heapptr_getptr(resptr);
	result->cd_refcnt         = 1;
	result->cd_heapsize       = heapptr_getsiz(resptr);
	result->cd_type.ct_driver = incref(owner);
	return result;
}

/* Lookup  a character device associated with `devno'  and return a reference to it.
 * When no character device is associated that device number, return `NULL' instead. */
PUBLIC WUNUSED REF struct chrdev *KCALL
chrdev_lookup(dev_t devno) THROWS(E_WOULDBLOCK) {
	REF struct chrdev *result;
	cdl_read();
	result = cdev_tree_locate(chrdev_tree, devno);
	/* Try to acquire a reference to the character device. */
	if (result && unlikely(!tryincref(result)))
		result = NULL;
	cdl_endread();
	return result;
}

/* Same as `chrdev_lookup()', but return `NULL'
 * if   the  lookup  would   have  caused  an  exception. */
PUBLIC WUNUSED REF struct chrdev *
NOTHROW(KCALL chrdev_lookup_nx)(dev_t devno) {
	REF struct chrdev *result;
	if (!cdl_read_nx())
		return NULL;
	result = cdev_tree_locate(chrdev_tree, devno);
	/* Try to acquire a reference to the character device. */
	if (result && unlikely(!tryincref(result)))
		result = NULL;
	cdl_endread();
	return result;
}


PRIVATE WUNUSED REF struct chrdev *KCALL
cdev_tree_search_name(struct chrdev *__restrict node,
                      char const *__restrict name) {
again:
	if (strcmp(node->cd_name, name) == 0)
		return likely(tryincref(node)) ? node : NULL;
	if (node->cd_devlink.a_min) {
		if (node->cd_devlink.a_max) {
			REF struct chrdev *result;
			result = cdev_tree_search_name(node->cd_devlink.a_max, name);
			if (result)
				return result;
		}
		node = node->cd_devlink.a_min;
		goto again;
	}
	if (node->cd_devlink.a_max) {
		node = node->cd_devlink.a_max;
		goto again;
	}
	return NULL;
}

/* Lookup a character device, given its `name`, with is its default filename
 * as  will appear  in the /dev/  directory, and may  optionally be prefixed
 * by a string `/dev/' that is stripped before comparison.
 * Alternatively, the given `name' may also be in the form of `MAJOR:MINOR',
 * an  encoding that is  always attempted first by  attempting to decode the
 * given name using `scanf("%u:%u")'
 * >> chrdev_lookup_name("3:64");      // MKDEV(3, 64)
 * >> chrdev_lookup_name("/dev/hdc1"); // MKDEV(22, 0) + 1
 * >> chrdev_lookup_name("hda2");      // MKDEV(3, 0)  + 2
 * @return: NULL: No device matching `name' exists. */
PUBLIC WUNUSED REF struct chrdev *KCALL
chrdev_lookup_name(USER CHECKED char const *name)
		THROWS(E_WOULDBLOCK, E_SEGFAULT) {
	REF struct chrdev *result = NULL;
	u32 dev_major, dev_minor;
	size_t name_len;
	char name_buf[COMPILER_LENOF(((struct chrdev *)0)->cd_name)];
	if (sscanf(name, "%u:%u", &dev_major, &dev_minor) == 2)
		return chrdev_lookup(MKDEV(dev_major, dev_minor));
	if (memcmp(name, "/dev/", 5 * sizeof(char)) == 0)
		name += 5;
	name_len = strnlen(name, COMPILER_LENOF(name_buf));
	if unlikely(name_len >= COMPILER_LENOF(name_buf))
		return NULL; /* Name is too long */
	memcpy(name_buf, name, name_len, sizeof(char));
	name_buf[name_len] = '\0';
	cdl_read();
	if likely(chrdev_tree)
		result = cdev_tree_search_name(chrdev_tree, name_buf);
	cdl_endread();
	return result;
}


PRIVATE NONNULL((1)) void KCALL
character_device_add_to_devfs_impl(struct chrdev *__restrict self) {
	/* Add the device's node to `/dev'
	 * NOTE: If the file already exists, ignore that fact, as
	 *      `devfs_insert()' will already set `self->cd_devfs_inode'
	 *       to `NULL' for us */
	printk(KERN_INFO "[chr] Register new character-device `/dev/%s'\n", self->cd_name);
	if likely(!self->cd_devfs_inode) {
		devfs_insert(self->cd_name,
		             S_IFCHR,
		             chrdev_devno(self),
		             &self->cd_devfs_inode, /* XXX: What about concurrent register() + unregister()? */
		             &self->cd_devfs_entry);
	}
}

PRIVATE NONNULL((1)) void KCALL
character_device_add_to_devfs(struct chrdev *__restrict self) {
	if (!self->cd_name[0]) {
		/* Auto-generate the name */
		sprintf(self->cd_name,
		        "%.2" PRIxN(__SIZEOF_MAJOR_T__) ":"
		        "%.2" PRIxN(__SIZEOF_MINOR_T__),
		        MAJOR(self->cd_devlink.a_vaddr),
		        MINOR(self->cd_devlink.a_vaddr));
	}
	character_device_add_to_devfs_impl(self);
}


/* Unregister  the given character-device from the character-device-id tree, as well as
 * removing its auto-generated entry from `/dev' (should that entry have been created).
 * @return: true:  Successfully unregistered the given.
 * @return: false: The device was never registered to begin with. */
PUBLIC NONNULL((1)) bool KCALL
chrdev_unregister(struct chrdev *__restrict self)
		THROWS(E_WOULDBLOCK) {
	bool result = false;
	printk(KERN_INFO "[chr] Removing character-device `/dev/%s'\n", self->cd_name);
	if likely(self->cd_devlink.a_vaddr != DEV_UNSET) {
		cdl_write();
		COMPILER_READ_BARRIER();
		if likely(self->cd_devlink.a_vaddr != DEV_UNSET) {
			struct chrdev *pop_dev;
			pop_dev = cdev_tree_remove(&chrdev_tree,
			                           self->cd_devlink.a_vaddr);
			assert(pop_dev == self);
			self->cd_devlink.a_vaddr = DEV_UNSET;
			cdl_endwrite();
			if (!(self->cd_flags & CHARACTER_DEVICE_FLAG_WEAKREG))
				decref_nokill(self);
			result = true;
		} else {
			cdl_endwrite();
		}
	}
	if (self->cd_devfs_inode) {
		devfs_remove(self->cd_devfs_inode,
		             self->cd_devfs_entry);
	}
	return result;
}

/* Register a character device with a fixed device number.
 * NOTE: When empty, `cd_name' will be set to `"%.2x:%.2x" % (MAJOR(devno),MINOR(devno))'
 * NOTE: This function will also cause the device to appear in `/dev' (unless the device's name is already taken) */
PUBLIC NONNULL((1)) void KCALL
chrdev_register(struct chrdev *__restrict self, dev_t devno)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	//assert(self->cd_type.ct_driver);
	cdl_write();
	/* Insert the new device into the character-device tree. */
	self->cd_devlink.a_vaddr = devno;
	if (!(self->cd_flags & CHARACTER_DEVICE_FLAG_WEAKREG))
		incref(self);
	cdev_tree_insert(&chrdev_tree, self);
	cdl_endwrite();
	TRY {
		character_device_add_to_devfs(self);
	} EXCEPT {
		struct chrdev *pop_dev;
		cdl_write();
		pop_dev = cdev_tree_remove(&chrdev_tree, devno);
		if likely(pop_dev == self) {
			cdl_endwrite();
			self->cd_devlink.a_vaddr = DEV_UNSET;
			decref_nokill(self); /* The caller still has a reference */
		} else {
			cdev_tree_insert(&chrdev_tree, pop_dev);
			cdl_endwrite();
		}
		RETHROW();
	}
}

PRIVATE void KCALL
pty_assign_name(struct chrdev *__restrict self,
                char prefix, minor_t id) {
	if (id >= PTY_DEVCNT) {
		/* KOS Extension: Since we allocate '20' bits for minor device numbers,
		 *                it's actually possible  to get _much_  more than  256
		 *                pty devices in KOS (1048576 to be exact).
		 *             >> But for all those additional nodes, we need a new
		 *                naming  scheme that isn't standardized due to its
		 *                nature of being an extension:
		 * MASTER: /dev/ptyX12345
		 * SLAVE:  /dev/ttyX12345
		 * NOTE: The 12345 is the hex value of the minor device number, using lower-case letters.
		 */
		STATIC_ASSERT(MINORBITS / 4 == 5);
		sprintf(self->cd_name, "%ctyX%.5" PRIx16, prefix, (u16)id);
	} else {
		/* Old (BSD-style) PTY master/slave device names. */
		self->cd_name[0] = prefix;
		self->cd_name[1] = 't';
		self->cd_name[2] = 'y';
		{
			char temp = 'p' + (id / 16);
			if (temp > 'z')
				temp = 'a' + (temp - 'z');
			self->cd_name[3] = temp;
		}
		id %= 16;
		self->cd_name[4] = id >= 10 ? 'a' + (id - 10) : '0' + id;
		self->cd_name[5] = '\0';
	}
}

/* Register a PTY master/slave pair within devfs, as well
 * as  assign matching character  device numbers to each. */
INTERN void KCALL
pty_register(struct pty_master *__restrict master,
             struct pty_slave *__restrict slave)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	minor_t used_minor;
	cdl_write();
	/* Insert the new device into the character-device tree. */
	used_minor = 0;
	while (cdev_tree_locate(chrdev_tree, MKDEV(MAJOR(PTY_MASTER(0)), used_minor)) ||
	       cdev_tree_locate(chrdev_tree, MKDEV(MAJOR(PTY_SLAVE(0)), used_minor))) {
		if unlikely(used_minor == (minor_t)-1) {
			cdl_endwrite();
			THROW(E_BADALLOC_INSUFFICIENT_DEVICE_NUMBERS,
			      E_NO_DEVICE_KIND_CHRDEV);
		}
		++used_minor;
	}
	master->cd_devlink.a_vaddr = MKDEV(MAJOR(PTY_MASTER(0)), used_minor);
	slave->cd_devlink.a_vaddr  = MKDEV(MAJOR(PTY_SLAVE(0)), used_minor);
	pty_assign_name(master, 'p', used_minor);
	pty_assign_name(slave, 't', used_minor);
	if (!(master->cd_flags & CHARACTER_DEVICE_FLAG_WEAKREG))
		incref(master);
	cdev_tree_insert(&chrdev_tree, master);
	if (!(slave->cd_flags & CHARACTER_DEVICE_FLAG_WEAKREG))
		incref(slave);
	cdev_tree_insert(&chrdev_tree, slave);
	cdl_endwrite();
	TRY {
		character_device_add_to_devfs_impl(master);
		TRY {
			character_device_add_to_devfs_impl(slave);
		} EXCEPT {
			if (master->cd_devfs_inode) {
				devfs_remove(master->cd_devfs_inode,
				             master->cd_devfs_entry);
			}
			RETHROW();
		}
	} EXCEPT {
		struct chrdev *pop_dev_a;
		struct chrdev *pop_dev_b;
		cdl_write();
		pop_dev_a = cdev_tree_remove(&chrdev_tree, master->cd_devlink.a_vaddr);
		pop_dev_b = cdev_tree_remove(&chrdev_tree, slave->cd_devlink.a_vaddr);
		if unlikely(pop_dev_a != master) {
			cdev_tree_insert(&chrdev_tree, pop_dev_a);
		}
		if unlikely(pop_dev_b != slave) {
			cdev_tree_insert(&chrdev_tree, pop_dev_b);
		}
		cdl_endwrite();
		if likely(pop_dev_a == master) {
			master->cd_devlink.a_vaddr = DEV_UNSET;
			if (!(master->cd_flags & CHARACTER_DEVICE_FLAG_WEAKREG))
				decref_nokill(master); /* The caller still has a reference */
		}
		if likely(pop_dev_b == slave) {
			slave->cd_devlink.a_vaddr = DEV_UNSET;
			if (!(slave->cd_flags & CHARACTER_DEVICE_FLAG_WEAKREG))
				decref_nokill(slave); /* The caller still has a reference */
		}
		RETHROW();
	}
}

/* Automatically   register  the  given   character-device,  assigning  it   an  auto-generated  device  ID.
 * All other devices are assigned some unique major device number `>= DEV_MAJOR_AUTO' with MINOR set to `0'.
 * NOTE: When empty, `cd_name' will be set to
 *       `"%.2" PRIxN(__SIZEOF_MAJOR_T__) ":%.2" PRIxN(__SIZEOF_MINOR_T__) % (MAJOR(devno),MINOR(devno))'
 * NOTE: This function will also cause the device to appear in `/dev' (unless the device's name is already taken) */
PUBLIC NONNULL((1)) void KCALL
chrdev_register_auto(struct chrdev *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	dev_t devno;
	cdl_write();
	devno = character_device_next_auto;
	character_device_next_auto += MKDEV(1, 0);
	self->cd_devlink.a_vaddr = devno;

	/* Insert the new device into the character-device tree. */
	if (!(self->cd_flags & CHARACTER_DEVICE_FLAG_WEAKREG))
		incref(self);
	cdev_tree_insert(&chrdev_tree, self);
	cdl_endwrite();
	TRY {
		character_device_add_to_devfs(self);
	} EXCEPT {
		struct chrdev *pop_dev;
		cdl_write();
		pop_dev = cdev_tree_remove(&chrdev_tree, devno);
		if likely(pop_dev == self) {
			self->cd_devlink.a_vaddr = DEV_UNSET;
			cdl_endwrite();
			decref_nokill(self); /* The caller still has a reference */
		} else {
			cdev_tree_insert(&chrdev_tree, pop_dev);
			cdl_endwrite();
		}
		RETHROW();
	}
}






DEFINE_HANDLE_REFCNT_FUNCTIONS(chrdev, struct chrdev);

INTERN size_t KCALL
handle_chrdev_read(struct chrdev *__restrict self,
                            USER CHECKED void *dst, size_t num_bytes,
                            iomode_t mode) {
	if likely(self->cd_type.ct_read)
		return (*self->cd_type.ct_read)(self, dst, num_bytes, mode);
	if likely(self->cd_type.ct_pread)
		return (*self->cd_type.ct_pread)(self, dst, num_bytes, 0, mode);
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_READ);
}

INTERN size_t KCALL
handle_chrdev_write(struct chrdev *__restrict self,
                             USER CHECKED void const *src, size_t num_bytes,
                             iomode_t mode) {
	if likely(self->cd_type.ct_write)
		return (*self->cd_type.ct_write)(self, src, num_bytes, mode);
	if likely(self->cd_type.ct_pwrite)
		return (*self->cd_type.ct_pwrite)(self, src, num_bytes, 0, mode);
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_WRITE);
}

INTERN size_t KCALL
handle_chrdev_pread(struct chrdev *__restrict self,
                             USER CHECKED void *dst, size_t num_bytes,
                             pos_t addr, iomode_t mode) {
	if likely(self->cd_type.ct_pread)
		return (*self->cd_type.ct_pread)(self, dst, num_bytes, addr, mode);
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_PREAD);
}

INTERN size_t KCALL
handle_chrdev_pwrite(struct chrdev *__restrict self,
                              USER CHECKED void const *src, size_t num_bytes,
                              pos_t addr, iomode_t mode) {
	if likely(self->cd_type.ct_pwrite)
		return (*self->cd_type.ct_pwrite)(self, src, num_bytes, addr, mode);
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_PWRITE);
}

INTERN size_t KCALL
handle_chrdev_readv(struct chrdev *__restrict self,
                             struct iov_buffer *__restrict dst,
                             size_t num_bytes, iomode_t mode) {
	struct iov_entry ent;
	size_t temp, result = 0;
	assert(num_bytes == iov_buffer_size(dst));
	(void)num_bytes;
	if likely(self->cd_type.ct_read) {
		IOV_BUFFER_FOREACH(ent, dst) {
			temp = (*self->cd_type.ct_read)(self,
			                                ent.ive_base,
			                                ent.ive_size,
			                                mode);
			result += temp;
			if (temp != ent.ive_size)
				break;
		}
	} else if likely(self->cd_type.ct_pread) {
		IOV_BUFFER_FOREACH(ent, dst) {
			temp = (*self->cd_type.ct_pread)(self,
			                                 ent.ive_base,
			                                 ent.ive_size,
			                                 (pos_t)result,
			                                 mode);
			result += temp;
			if (temp != ent.ive_size)
				break;
		}
	} else {
		THROW(E_FSERROR_UNSUPPORTED_OPERATION,
		      E_FILESYSTEM_OPERATION_READ);
	}
	return result;
}

INTERN size_t KCALL
handle_chrdev_writev(struct chrdev *__restrict self,
                              struct iov_buffer *__restrict src,
                              size_t num_bytes, iomode_t mode) {
	struct iov_entry ent;
	size_t temp, result = 0;
	assert(num_bytes == iov_buffer_size(src));
	(void)num_bytes;
	if likely(self->cd_type.ct_write) {
		IOV_BUFFER_FOREACH(ent, src) {
			temp = (*self->cd_type.ct_write)(self,
			                                 ent.ive_base,
			                                 ent.ive_size,
			                                 mode);
			result += temp;
			if (temp != ent.ive_size)
				break;
		}
	} else if likely(self->cd_type.ct_pwrite) {
		IOV_BUFFER_FOREACH(ent, src) {
			temp = (*self->cd_type.ct_pwrite)(self,
			                                  ent.ive_base,
			                                  ent.ive_size,
			                                  (pos_t)result,
			                                  mode);
			result += temp;
			if (temp != ent.ive_size)
				break;
		}
	} else {
		THROW(E_FSERROR_UNSUPPORTED_OPERATION,
		      E_FILESYSTEM_OPERATION_WRITE);
	}
	return result;
}

INTERN size_t KCALL
handle_chrdev_preadv(struct chrdev *__restrict self,
                              struct iov_buffer *__restrict dst,
                              size_t num_bytes, pos_t addr, iomode_t mode) {
	struct iov_entry ent;
	size_t result = 0;
	assert(num_bytes == iov_buffer_size(dst));
	(void)num_bytes;
	if likely(self->cd_type.ct_pread) {
		IOV_BUFFER_FOREACH(ent, dst) {
			size_t temp;
			temp = (*self->cd_type.ct_pread)(self,
			                                 ent.ive_base,
			                                 ent.ive_size,
			                                 addr,
			                                 mode);
			result += temp;
			if (temp != ent.ive_size)
				break;
			addr += temp;
		}
	} else {
		THROW(E_FSERROR_UNSUPPORTED_OPERATION,
		      E_FILESYSTEM_OPERATION_PREAD);
	}
	return result;
}

INTERN size_t KCALL
handle_chrdev_pwritev(struct chrdev *__restrict self,
                               struct iov_buffer *__restrict src,
                               size_t num_bytes, pos_t addr, iomode_t mode) {
	struct iov_entry ent;
	size_t result = 0;
	assert(num_bytes == iov_buffer_size(src));
	(void)num_bytes;
	if likely(self->cd_type.ct_pwrite) {
		IOV_BUFFER_FOREACH(ent, src) {
			size_t temp;
			temp = (*self->cd_type.ct_pwrite)(self,
			                                  ent.ive_base,
			                                  ent.ive_size,
			                                  addr,
			                                  mode);
			result += temp;
			if (temp != ent.ive_size)
				break;
			addr += temp;
		}
	} else {
		THROW(E_FSERROR_UNSUPPORTED_OPERATION,
		      E_FILESYSTEM_OPERATION_PWRITE);
	}
	return result;
}

INTERN syscall_slong_t KCALL
handle_chrdev_ioctl(struct chrdev *__restrict self, syscall_ulong_t cmd,
                             USER UNCHECKED void *arg, iomode_t mode) {
	if likely(self->cd_type.ct_ioctl)
		return (*self->cd_type.ct_ioctl)(self, cmd, arg, mode);
	THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
	      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
	      cmd);
}

INTERN NONNULL((1, 2)) void KCALL
handle_chrdev_mmap(struct chrdev *__restrict self,
                            struct handle_mmap_info *__restrict info)
		THROWS(...) {
	if unlikely(!self->cd_type.ct_mmap) {
		THROW(E_FSERROR_UNSUPPORTED_OPERATION,
		      E_FILESYSTEM_OPERATION_MMAP);
	}
	(*self->cd_type.ct_mmap)(self, info);
	if (!info->hmi_fsname && ATOMIC_READ(self->cd_devfs_inode) != NULL) {
		/* Fill in filesystem location information from devfs! */
		info->hmi_fsname = xincref(self->cd_devfs_entry);
		if (!info->hmi_fspath) {
			/* Try to lookup (one of) the mounting point(s) of devfs within the current namespace.
			 * If such  a mounting  point exists,  `superblock_find_mount_from_vfs()' will  return
			 * `NULL', which is allowed to happen, and will be dealt with by our caller. */
			info->hmi_fspath = superblock_find_mount_from_vfs(&devfs, THIS_VFS);
		}
	}
	return;
}

INTERN void KCALL
handle_chrdev_sync(struct chrdev *__restrict self) {
	if (self->cd_type.ct_sync)
		(*self->cd_type.ct_sync)(self);
}

INTERN void KCALL
handle_chrdev_stat(struct chrdev *__restrict self,
                            USER CHECKED struct stat *result) {
	struct inode *node;
	memset(result, 0, sizeof(*result));
	node = self->cd_devfs_inode;
	if (node)
		inode_stat(node, result);
	result->st_mode = (result->st_mode & ~S_IFMT) | S_IFCHR;
	result->st_dev  = (__dev_t)chrdev_devno(self);
	result->st_rdev = (__dev_t)chrdev_devno(self);
	if (self->cd_type.ct_stat)
		(*self->cd_type.ct_stat)(self, result);
}

INTERN void KCALL
handle_chrdev_pollconnect(struct chrdev *__restrict self,
                                   poll_mode_t what) {
	assert((self->cd_type.ct_pollconnect != NULL) ==
	       (self->cd_type.ct_polltest != NULL));
	if likely(self->cd_type.ct_pollconnect)
		(*self->cd_type.ct_pollconnect)(self, what);
}

INTERN poll_mode_t KCALL
handle_chrdev_polltest(struct chrdev *__restrict self,
                                poll_mode_t what) {
	assert((self->cd_type.ct_pollconnect != NULL) ==
	       (self->cd_type.ct_polltest != NULL));
	if unlikely(!self->cd_type.ct_polltest)
		return 0;
	return (*self->cd_type.ct_polltest)(self, what);
}

INTERN syscall_slong_t KCALL
handle_chrdev_hop(struct chrdev *__restrict self,
                           syscall_ulong_t cmd,
                           USER UNCHECKED void *arg,
                           iomode_t mode) {
	(void)self;
	(void)arg;
	(void)mode;
	COMPILER_IMPURE();
	switch (cmd) {

		/* TODO */

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND,
		      cmd);
		break;
	}
	return 0;
}

INTERN NONNULL((1)) REF void *KCALL
handle_chrdev_tryas(struct chrdev *__restrict self,
                             uintptr_half_t wanted_type)
		THROWS(E_WOULDBLOCK) {
	switch (wanted_type) {

	case HANDLE_TYPE_MFILE: {
		REF struct inode *result;
		result = ATOMIC_READ(self->cd_devfs_inode);
		if (result)
			return incref(result);
	}	break;

	case HANDLE_TYPE_FDIRENT: {
		if (ATOMIC_READ(self->cd_devfs_inode))
			return incref(self->cd_devfs_entry);
	}	break;

	default:
		break;
	}
	return NULL;
}




DEFINE_PUBLIC_ALIAS(chrdev_read, handle_chrdev_read);
DEFINE_PUBLIC_ALIAS(chrdev_write, handle_chrdev_write);
DEFINE_PUBLIC_ALIAS(chrdev_pread, handle_chrdev_pread);
DEFINE_PUBLIC_ALIAS(chrdev_pwrite, handle_chrdev_pwrite);
DEFINE_PUBLIC_ALIAS(chrdev_ioctl, handle_chrdev_ioctl);
DEFINE_PUBLIC_ALIAS(chrdev_mmap, handle_chrdev_mmap);
DEFINE_PUBLIC_ALIAS(chrdev_sync, handle_chrdev_sync);
DEFINE_PUBLIC_ALIAS(chrdev_stat, handle_chrdev_stat);
DEFINE_PUBLIC_ALIAS(chrdev_pollconnect, handle_chrdev_pollconnect);
DEFINE_PUBLIC_ALIAS(chrdev_polltest, handle_chrdev_polltest);


#ifdef CONFIG_HAVE_DEBUGGER
PRIVATE ATTR_DBGTEXT void KCALL
do_dump_character_device(struct chrdev *__restrict self,
                         size_t max_device_namelen,
                         size_t max_driver_namelen) {
	char const *kind;
	if (chrdev_istty(self))
		kind = ttybase_isapty((struct ttydev *)self)
		       ? DBGSTR("pty")
		       : DBGSTR("tty");
	else if (chrdev_iskbd(self))
		kind = DBGSTR("keyboard");
	else if (chrdev_ismouse(self))
		kind = DBGSTR("mouse");
	else {
		kind = DBGSTR("other");
	}
	dbg_printf(DBGSTR("/dev/" AC_WHITE("%-*s") "  "
	                  "%3.2" PRIxN(__SIZEOF_MAJOR_T__) ":"
	                  "%-3.2" PRIxN(__SIZEOF_MINOR_T__) "  "
	                  "%*-s  %-8s  "),
	           (unsigned int)max_device_namelen, self->cd_name,
	           (unsigned int)MAJOR(chrdev_devno(self)),
	           (unsigned int)MINOR(chrdev_devno(self)),
	           (unsigned int)max_driver_namelen,
	           self->cd_type.ct_driver ? self->cd_type.ct_driver->d_name
	                                   : DBGSTR("?"),
	           kind);
	dbg_putc(self->cd_type.ct_read ? 'r' : '-');
	dbg_putc(self->cd_type.ct_write ? 'w' : '-');
	dbg_putc(self->cd_type.ct_pread ? 'R' : '-');
	dbg_putc(self->cd_type.ct_pwrite ? 'W' : '-');
	dbg_putc(self->cd_type.ct_ioctl ? 'i' : '-');
	dbg_putc(self->cd_type.ct_mmap ? 'm' : '-');
	dbg_putc(self->cd_type.ct_sync ? 's' : '-');
	dbg_putc(self->cd_type.ct_stat ? 't' : '-');
	dbg_putc(self->cd_type.ct_pollconnect ? 'p' : '-');
	dbg_putc('\n');
}

PRIVATE ATTR_DBGTEXT void KCALL
dump_character_device(struct chrdev *__restrict self,
                      size_t max_device_namelen,
                      size_t max_driver_namelen) {
again:
	do_dump_character_device(self,
	                         max_device_namelen,
	                         max_driver_namelen);
	if (self->cd_devlink.a_min) {
		if (self->cd_devlink.a_max) {
			dump_character_device(self->cd_devlink.a_max,
			                      max_device_namelen,
			                      max_driver_namelen);
		}
		self = self->cd_devlink.a_min;
		goto again;
	}
	if (self->cd_devlink.a_max) {
		self = self->cd_devlink.a_max;
		goto again;
	}
}

PRIVATE ATTR_DBGTEXT void KCALL
gather_longest_name_lengths(struct chrdev *__restrict self,
                            size_t *__restrict pmax_device_namelen,
                            size_t *__restrict pmax_driver_namelen) {
	size_t namelen;
again:
	namelen = strlen(self->cd_name);
	if (*pmax_device_namelen < namelen)
		*pmax_device_namelen = namelen;
	if (ADDR_ISKERN(self->cd_type.ct_driver)) {
		namelen = strlen(self->cd_type.ct_driver->d_name);
		if (*pmax_driver_namelen < namelen)
			*pmax_driver_namelen = namelen;
	}
	if (self->cd_devlink.a_min) {
		if (self->cd_devlink.a_max) {
			gather_longest_name_lengths(self->cd_devlink.a_max,
			                            pmax_device_namelen,
			                            pmax_driver_namelen);
		}
		self = self->cd_devlink.a_min;
		goto again;
	}
	if (self->cd_devlink.a_max) {
		self = self->cd_devlink.a_max;
		goto again;
	}
}

DBG_COMMAND(lschr,
            "lschr\n"
            "\tList all defined character devices\n"
            "\tfeatures:\n"
            "\t\t" AC_WHITE("r") ": Supports " AC_WHITE("read") "\n"
            "\t\t" AC_WHITE("w") ": Supports " AC_WHITE("write") "\n"
            "\t\t" AC_WHITE("R") ": Supports " AC_WHITE("pread") "\n"
            "\t\t" AC_WHITE("W") ": Supports " AC_WHITE("pwrite") "\n"
            "\t\t" AC_WHITE("i") ": Supports " AC_WHITE("ioctl") "\n"
            "\t\t" AC_WHITE("m") ": Supports " AC_WHITE("mmap") "\n"
            "\t\t" AC_WHITE("s") ": Supports " AC_WHITE("sync") "\n"
            "\t\t" AC_WHITE("t") ": Supports " AC_WHITE("stat") "\n"
            "\t\t" AC_WHITE("p") ": Supports " AC_WHITE("poll") "\n") {
	size_t longest_device_name = COMPILER_STRLEN("name");
	size_t longest_driver_name = COMPILER_STRLEN("driver");
	if (chrdev_tree) {
		gather_longest_name_lengths(chrdev_tree,
		                            &longest_device_name,
		                            &longest_driver_name);
	}
	dbg_print(DBGSTR("     name"));
	if (longest_device_name > COMPILER_STRLEN("name"))
		format_repeat(&dbg_printer, NULL, ' ', longest_device_name - COMPILER_STRLEN("name"));
	dbg_print(DBGSTR("  devno    driver"));
	if (longest_driver_name > COMPILER_STRLEN("driver"))
		format_repeat(&dbg_printer, NULL, ' ', longest_driver_name - COMPILER_STRLEN("driver"));
	dbg_print(DBGSTR("  kind      features\n"));
	if (chrdev_tree) {
		dump_character_device(chrdev_tree,
		                      longest_device_name,
		                      longest_driver_name);
	}
	return 0;
}

#endif /* CONFIG_HAVE_DEBUGGER */


DECL_END
#endif /* !CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_SRC_DEV_CHAR_C */
