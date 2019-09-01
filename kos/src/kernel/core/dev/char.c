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
#ifndef GUARD_KERNEL_SRC_DEV_CHAR_C
#define GUARD_KERNEL_SRC_DEV_CHAR_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/char.h>
#include <dev/pty.h>
#include <dev/ttybase.h>
#include <dev/mouse.h>
#include <dev/keyboard.h>
#include <fs/node.h>
#include <fs/ramfs.h>
#include <kernel/aio.h>
#include <kernel/user.h>
#include <kernel/debugger.h>
#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/printk.h>
#include <kernel/types.h>

#include <kos/dev.h>
#include <sys/stat.h>
#include <sys/types.h> /* loff_t */

#include <stdio.h>
#include <string.h>
#include <errno.h>

/* Implement the ABI for the address tree used by character_device. */
#define ATREE(x)                  cdev_tree_##x
#define ATREE_CALL                KCALL
#define Tkey                      dev_t
#define T                         struct character_device
#define N_NODEPATH                cd_devlink
#define ATREE_SINGLE 1
#include <hybrid/sequence/atree-abi.h>
#undef ATREE_SINGLE

DECL_BEGIN

#define CHARACTER_DEVICE_GFP     GFP_LOCKED
#if !!(CHARACTER_DEVICE_GFP & GFP_LOCKED)
#define CHARACTER_DEVICE_HEAP   &kernel_locked_heap
#else
#define CHARACTER_DEVICE_HEAP   &kernel_default_heap
#endif

/* Destroy a given character device. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL character_device_destroy)(struct character_device *__restrict self) {
	assert(self->cd_type.ct_driver);
	/* Invoke a custom finalizer callback */
	if (self->cd_type.ct_fini)
		(*self->cd_type.ct_fini)(self);
	assert(self->cd_devlink.a_vaddr == DEV_UNSET);
	/* Check if the device should be removed from devfs, and drop
	 * the references held to its INode and directory entry. */
	if (self->cd_devfs_inode) {
		devfs_remove(self->cd_devfs_inode, /* No-op if already done... */
		             self->cd_devfs_entry);
		decref_likely(self->cd_devfs_inode);
		decref_likely(self->cd_devfs_entry);
	}
	decref(self->cd_type.ct_driver);
	heap_free(CHARACTER_DEVICE_HEAP,
	          self,
	          self->cd_heapsize,
	          GFP_NORMAL);
}

/* Allocate and initialize a new character device.
 * The caller must still initialize:
 *   >> return->cd_type;
 * As well as optionally:
 *   >> return->cd_name
 * This function will initialize the following memory to non-zero values:
 *   >> return->cd_max_retry = 2;
 */
PUBLIC WUNUSED ATTR_RETNONNULL ATTR_MALLOC REF struct character_device *KCALL
character_device_alloc(struct driver *__restrict owner, size_t structure_size)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	REF struct character_device *result;
	struct heapptr resptr;
	assert(structure_size >= sizeof(struct character_device));
	assert(owner);
	resptr = heap_alloc(CHARACTER_DEVICE_HEAP,
	                    structure_size,
	                    CHARACTER_DEVICE_GFP |
	                    GFP_PREFLT |
	                    GFP_CALLOC);
	result                    = (REF struct character_device *)resptr.hp_ptr;
	result->cd_refcnt         = 1;
	result->cd_heapsize       = resptr.hp_siz;
	result->cd_type.ct_driver = incref(owner);
	return result;
}

/* The tree used to quickly look up a character device from its ID */
PRIVATE REF ATREE_HEAD(struct character_device) character_device_tree = NULL;
PRIVATE dev_t character_device_next_auto = MKDEV(DEV_MAJOR_AUTO,0);
PRIVATE DEFINE_ATOMIC_RWLOCK(character_device_lock);
DEFINE_DBG_BZERO_OBJECT(character_device_lock);


/* Lookup a character device associated with `devno' and return a reference to it.
 * When no character device is associated that device number, return `NULL' instead. */
PUBLIC WUNUSED REF struct character_device *KCALL
character_device_lookup(dev_t devno) THROWS(E_WOULDBLOCK) {
	REF struct character_device *result;
	sync_read(&character_device_lock);
	result = cdev_tree_locate(character_device_tree, devno);
	/* Try to acquire a reference to the character device. */
	if (result && unlikely(!tryincref(result)))
		result = NULL;
	sync_endread(&character_device_lock);
	return result;
}

/* Same as `character_device_lookup()', but return `NULL'
 * if the lookup would have caused an exception. */
PUBLIC WUNUSED REF struct character_device *
NOTHROW(KCALL character_device_lookup_nx)(dev_t devno) {
	REF struct character_device *result;
	if (!sync_read_nx(&character_device_lock))
		return NULL;
	result = cdev_tree_locate(character_device_tree, devno);
	/* Try to acquire a reference to the character device. */
	if (result && unlikely(!tryincref(result)))
		result = NULL;
	sync_endread(&character_device_lock);
	return result;
}


PRIVATE WUNUSED REF struct character_device *KCALL
cdev_tree_search_name(struct character_device *__restrict node,
                      char const *__restrict name) {
again:
	if (strcmp(node->cd_name, name) == 0)
		return likely(tryincref(node)) ? node : NULL;
	if (node->cd_devlink.a_min) {
		if (node->cd_devlink.a_max) {
			REF struct character_device *result;
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
 * as will appear in the /dev/ directory, and may optionally be prefixed
 * by a string `/dev/' that is stripped before comparison.
 * Alternatively, the given `name' may also be in the form of `MAJOR:MINOR',
 * an encoding that is always attempted first by attempting to decode the
 * given name using `scanf("%u:%u")'
 * >> // TODO: Use well-known character devices this example!
 * >> character_device_lookup_name("3:64");      // MKDEV(3,64)
 * >> character_device_lookup_name("/dev/hdc1"); // MKDEV(22,0) + 1
 * >> character_device_lookup_name("hda2");      // MKDEV(3,0)  + 2
 * @return: NULL: No device matching `name' exists. */
PUBLIC WUNUSED REF struct character_device *KCALL
character_device_lookup_name(USER CHECKED char const *name)
		THROWS(E_WOULDBLOCK, E_SEGFAULT) {
	REF struct character_device *result = NULL;
	u32 dev_major, dev_minor;
	size_t name_len;
	char name_buf[COMPILER_LENOF(((struct character_device *)0)->cd_name)];
	if (sscanf(name, "%u:%u", &dev_major, &dev_minor) == 2)
		return character_device_lookup(MKDEV(dev_major, dev_minor));
	if (memcmp(name, "/dev/", 5 * sizeof(char)) == 0)
		name += 5;
	name_len = strnlen(name, COMPILER_LENOF(name_buf));
	if unlikely(name_len >= COMPILER_LENOF(name_buf))
		return NULL; /* Name is too long */
	memcpy(name_buf, name, name_len);
	name_buf[name_len] = '\0';
	sync_read(&character_device_lock);
	if likely(character_device_tree) {
		result = cdev_tree_search_name(character_device_tree, name_buf);
	}
	sync_endread(&character_device_lock);
	return result;
}


PRIVATE NONNULL((1)) void KCALL
character_device_add_to_devfs_impl(struct character_device *__restrict self) {
	/* Add the device's node to `/dev'
	 * NOTE: If the file already exists, ignore that fact, as
	 *      `devfs_insert()' will already set `self->cd_devfs_inode'
	 *       to `NULL' for us */
	printk(KERN_INFO "Register new character-device `/dev/%s'\n", self->cd_name);
	if likely(!self->cd_devfs_inode) {
		devfs_insert(self->cd_name,
		             S_IFCHR,
		             character_device_devno(self),
		             &self->cd_devfs_inode, /* XXX: What about concurrent register() + unregister()? */
		             &self->cd_devfs_entry);
	}
}

PRIVATE NONNULL((1)) void KCALL
character_device_add_to_devfs(struct character_device *__restrict self) {
	if (!self->cd_name[0]) {
		/* Auto-generate the name */
		sprintf(self->cd_name,
		        "%.2x:%.2x",
		        MAJOR(self->cd_devlink.a_vaddr),
		        MINOR(self->cd_devlink.a_vaddr));
	}
	character_device_add_to_devfs_impl(self);
}


/* Unregister the given character-device from the character-device-id tree, as well as
 * removing its auto-generated entry from `/dev' (should that entry have been created).
 * @return: true:  Successfully unregistered the given.
 * @return: false: The device was never registered to begin with. */
PUBLIC NONNULL((1)) bool KCALL
character_device_unregister(struct character_device *__restrict self)
		THROWS(E_WOULDBLOCK) {
	bool result = false;
	struct character_device *pop_dev;
	printk(KERN_INFO "Removing character-device `/dev/%s'\n", self->cd_name);
	if likely(self->cd_devlink.a_vaddr != DEV_UNSET) {
		sync_write(&character_device_lock);
		COMPILER_READ_BARRIER();
		if likely(self->cd_devlink.a_vaddr != DEV_UNSET) {
			pop_dev = cdev_tree_remove(&character_device_tree,
			                           self->cd_devlink.a_vaddr);
			assert(pop_dev == self);
			self->cd_devlink.a_vaddr = DEV_UNSET;
			sync_endwrite(&character_device_lock);
			decref(self);
			result = true;
		} else {
			sync_endwrite(&character_device_lock);
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
character_device_register(struct character_device *__restrict self, dev_t devno)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	//assert(self->cd_type.ct_driver);
	sync_write(&character_device_lock);
	/* Insert the new device into the character-device tree. */
	self->cd_devlink.a_vaddr = devno;
	cdev_tree_insert(&character_device_tree, incref(self));
	sync_endwrite(&character_device_lock);
	TRY {
		character_device_add_to_devfs(self);
	} EXCEPT {
		struct character_device *pop_dev;
		sync_write(&character_device_lock);
		pop_dev = cdev_tree_remove(&character_device_tree, devno);
		if likely(pop_dev == self) {
			sync_endwrite(&character_device_lock);
			self->cd_devlink.a_vaddr = DEV_UNSET;
			decref_nokill(self); /* The caller still has a reference */
		} else {
			cdev_tree_insert(&character_device_tree, pop_dev);
			sync_endwrite(&character_device_lock);
		}
		RETHROW();
	}
}

PRIVATE void KCALL
pty_assign_name(struct character_device *__restrict self,
                char prefix, minor_t id) {
	if (id >= PTY_DEVCNT) {
		/* KOS Extension: Since we allocate '20' bits for minor device numbers,
		 *                it's actually possible to get _much_ more than 256
		 *                pty devices in KOS (1048576 to be exact).
		 *             >> But for all those additional nodes, we need a new
		 *                naming scheme that isn't standardized due to its
		 *                nature of being an extension:
		 * MASTER: /dev/ptyX12345
		 * SLAVE:  /dev/ttyX12345
		 * NOTE: The 12345 is the hex value of the minor device number, using lower-case letters.
		 */
		STATIC_ASSERT(MINORBITS / 4 == 5);
		sprintf(self->cd_name, "%ctyX%.5I16x", prefix, (u16)id);
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
 * as assign matching character device numbers to each. */
PUBLIC void KCALL
pty_register(struct pty_master *__restrict master,
             struct pty_slave *__restrict slave)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	minor_t used_minor;
	sync_write(&character_device_lock);
	/* Insert the new device into the character-device tree. */
	used_minor = 0;
	while (cdev_tree_locate(character_device_tree, MKDEV(MAJOR(PTY_MASTER(0)), used_minor)) ||
	       cdev_tree_locate(character_device_tree, MKDEV(MAJOR(PTY_SLAVE(0)), used_minor))) {
		if unlikely(used_minor == (minor_t)-1) {
			sync_endwrite(&character_device_lock);
			THROW(E_BADALLOC_INSUFFICIENT_DEVICE_NUMBERS,
			      E_NO_DEVICE_KIND_CHARACTER_DEVICE);
		}
		++used_minor;
	}
	master->cd_devlink.a_vaddr = MKDEV(MAJOR(PTY_MASTER(0)), used_minor);
	slave->cd_devlink.a_vaddr  = MKDEV(MAJOR(PTY_SLAVE(0)), used_minor);
	pty_assign_name(master, 'p', used_minor);
	pty_assign_name(slave, 't', used_minor);
	cdev_tree_insert(&character_device_tree, incref(master));
	cdev_tree_insert(&character_device_tree, incref(slave));
	sync_endwrite(&character_device_lock);
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
		struct character_device *pop_dev_a;
		struct character_device *pop_dev_b;
		sync_write(&character_device_lock);
		pop_dev_a = cdev_tree_remove(&character_device_tree, master->cd_devlink.a_vaddr);
		pop_dev_b = cdev_tree_remove(&character_device_tree, slave->cd_devlink.a_vaddr);
		if unlikely(pop_dev_a != master) {
			cdev_tree_insert(&character_device_tree, pop_dev_a);
		}
		if unlikely(pop_dev_b != slave) {
			cdev_tree_insert(&character_device_tree, pop_dev_b);
		}
		sync_endwrite(&character_device_lock);
		if likely(pop_dev_a == master) {
			master->cd_devlink.a_vaddr = DEV_UNSET;
			decref_nokill(master); /* The caller still has a reference */
		}
		if likely(pop_dev_b == slave) {
			slave->cd_devlink.a_vaddr = DEV_UNSET;
			decref_nokill(slave); /* The caller still has a reference */
		}
		RETHROW();
	}
}

/* Automatically register the given character-device, assigning it an auto-generated device ID.
 * All other devices are assigned some unique major device number `>= DEV_MAJOR_AUTO' with MINOR set to `0'.
 * NOTE: When empty, `cd_name' will be set to `"%.2x:%.2x" % (MAJOR(devno),MINOR(devno))'
 * NOTE: This function will also cause the device to appear in `/dev' (unless the device's name is already taken) */
PUBLIC NONNULL((1)) void KCALL
character_device_register_auto(struct character_device *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	dev_t devno;
	sync_write(&character_device_lock);
	devno = character_device_next_auto;
	character_device_next_auto += MKDEV(1, 0);
	self->cd_devlink.a_vaddr = devno;

	/* Insert the new device into the character-device tree. */
	cdev_tree_insert(&character_device_tree, incref(self));
	sync_endwrite(&character_device_lock);
	TRY {
		character_device_add_to_devfs(self);
	} EXCEPT {
		struct character_device *pop_dev;
		sync_write(&character_device_lock);
		pop_dev = cdev_tree_remove(&character_device_tree, devno);
		if likely(pop_dev == self) {
			self->cd_devlink.a_vaddr = DEV_UNSET;
			sync_endwrite(&character_device_lock);
			decref_nokill(self); /* The caller still has a reference */
		} else {
			cdev_tree_insert(&character_device_tree, pop_dev);
			sync_endwrite(&character_device_lock);
		}
		RETHROW();
	}
}






DEFINE_HANDLE_REFCNT_FUNCTIONS(characterdevice, struct character_device)

INTERN size_t KCALL
handle_characterdevice_read(struct character_device *__restrict self,
                            USER CHECKED void *dst, size_t num_bytes,
                            iomode_t mode) {
	if (self->cd_type.ct_read)
		return (*self->cd_type.ct_read)(self, dst, num_bytes, mode);
	if (self->cd_type.ct_pread)
		return (*self->cd_type.ct_pread)(self, dst, num_bytes, 0, mode);
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_READ);
}

INTERN size_t KCALL
handle_characterdevice_write(struct character_device *__restrict self,
                             USER CHECKED void const *src, size_t num_bytes,
                             iomode_t mode) {
	if (self->cd_type.ct_write)
		return (*self->cd_type.ct_write)(self, src, num_bytes, mode);
	if (self->cd_type.ct_pwrite)
		return (*self->cd_type.ct_pwrite)(self, src, num_bytes, 0, mode);
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_WRITE);
}

INTERN size_t KCALL
handle_characterdevice_pread(struct character_device *__restrict self,
                             USER CHECKED void *dst, size_t num_bytes,
                             pos_t addr, iomode_t mode) {
	if (self->cd_type.ct_pread)
		return (*self->cd_type.ct_pread)(self, dst, num_bytes, addr, mode);
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_READ);
}

INTERN size_t KCALL
handle_characterdevice_pwrite(struct character_device *__restrict self,
                              USER CHECKED void const *src, size_t num_bytes,
                              pos_t addr, iomode_t mode) {
	if (self->cd_type.ct_pwrite)
		return (*self->cd_type.ct_pwrite)(self, src, num_bytes, addr, mode);
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_WRITE);
}

INTERN size_t KCALL
handle_characterdevice_readv(struct character_device *__restrict self,
                             struct aio_buffer *__restrict dst,
                             size_t UNUSED(num_bytes), iomode_t mode) {
	struct aio_buffer_entry ent;
	size_t temp, result = 0;
	if (self->cd_type.ct_read) {
		AIO_BUFFER_FOREACH(ent, dst) {
			temp = (*self->cd_type.ct_read)(self,
			                                ent.ab_base,
			                                ent.ab_size,
			                                mode);
			result += temp;
			if (temp != ent.ab_size)
				break;
		}
	} else if (self->cd_type.ct_pread) {
		AIO_BUFFER_FOREACH(ent, dst) {
			temp = (*self->cd_type.ct_pread)(self,
			                                 ent.ab_base,
			                                 ent.ab_size,
			                                 (pos_t)result,
			                                 mode);
			result += temp;
			if (temp != ent.ab_size)
				break;
		}
	} else {
		THROW(E_FSERROR_UNSUPPORTED_OPERATION,
		      E_FILESYSTEM_OPERATION_READ);
	}
	return result;
}

INTERN size_t KCALL
handle_characterdevice_writev(struct character_device *__restrict self,
                              struct aio_buffer *__restrict src,
                              size_t num_bytes, iomode_t mode) {
	struct aio_buffer_entry ent;
	size_t temp, result = 0;
	if (self->cd_type.ct_write) {
		AIO_BUFFER_FOREACH(ent, src) {
			temp = (*self->cd_type.ct_write)(self,
			                                 ent.ab_base,
			                                 ent.ab_size,
			                                 mode);
			result += temp;
			if (temp != ent.ab_size)
				break;
		}
	} else if (self->cd_type.ct_pwrite) {
		AIO_BUFFER_FOREACH(ent, src) {
			temp = (*self->cd_type.ct_pwrite)(self,
			                                  ent.ab_base,
			                                  ent.ab_size,
			                                  (pos_t)result,
			                                  mode);
			result += temp;
			if (temp != ent.ab_size)
				break;
		}
	} else {
		THROW(E_FSERROR_UNSUPPORTED_OPERATION,
		      E_FILESYSTEM_OPERATION_WRITE);
	}
	return result;
}

INTERN size_t KCALL
handle_characterdevice_preadv(struct character_device *__restrict self,
                              struct aio_buffer *__restrict dst,
                              size_t num_bytes, pos_t addr, iomode_t mode) {
	struct aio_buffer_entry ent;
	size_t temp, result = 0;
	if (self->cd_type.ct_pread) {
		AIO_BUFFER_FOREACH(ent, dst) {
			temp = (*self->cd_type.ct_pread)(self,
			                                 ent.ab_base,
			                                 ent.ab_size,
			                                 addr,
			                                 mode);
			result += temp;
			if (temp != ent.ab_size)
				break;
			addr += temp;
		}
	} else {
		THROW(E_FSERROR_UNSUPPORTED_OPERATION,
		      E_FILESYSTEM_OPERATION_READ);
	}
	return result;
}

INTERN size_t KCALL
handle_characterdevice_pwritev(struct character_device *__restrict self,
                               struct aio_buffer *__restrict src,
                               size_t num_bytes, pos_t addr, iomode_t mode) {
	struct aio_buffer_entry ent;
	size_t temp, result = 0;
	if (self->cd_type.ct_pwrite) {
		AIO_BUFFER_FOREACH(ent, src) {
			temp = (*self->cd_type.ct_pwrite)(self,
			                                  ent.ab_base,
			                                  ent.ab_size,
			                                  addr,
			                                  mode);
			result += temp;
			if (temp != ent.ab_size)
				break;
			addr += temp;
		}
	} else {
		THROW(E_FSERROR_UNSUPPORTED_OPERATION,
		      E_FILESYSTEM_OPERATION_READ);
	}
	return result;
}

INTERN size_t KCALL
handle_characterdevice_aread(struct character_device *__restrict self,
                             USER CHECKED void *dst, size_t num_bytes,
                             iomode_t mode,
                             struct aio_multihandle *__restrict aio) {
	size_t result;
	result = handle_characterdevice_read(self, dst, num_bytes, mode);
	aio_multihandle_done(aio);
	return result;
}

INTERN size_t KCALL
handle_characterdevice_awrite(struct character_device *__restrict self,
                              USER CHECKED void const *src, size_t num_bytes,
                              iomode_t mode,
                              struct aio_multihandle *__restrict aio) {
	size_t result;
	result = handle_characterdevice_write(self, src, num_bytes, mode);
	aio_multihandle_done(aio);
	return result;
}

INTERN size_t KCALL
handle_characterdevice_areadv(struct character_device *__restrict self,
                              struct aio_buffer *__restrict dst,
                              size_t num_bytes, iomode_t mode,
                              struct aio_multihandle *__restrict aio) {
	size_t result;
	result = handle_characterdevice_readv(self, dst, num_bytes, mode);
	aio_multihandle_done(aio);
	return result;
}

INTERN size_t KCALL
handle_characterdevice_awritev(struct character_device *__restrict self,
                               struct aio_buffer *__restrict src,
                               size_t num_bytes, iomode_t mode,
                               struct aio_multihandle *__restrict aio) {
	size_t result;
	result = handle_characterdevice_writev(self, src, num_bytes, mode);
	aio_multihandle_done(aio);
	return result;
}

INTERN size_t KCALL
handle_characterdevice_apread(struct character_device *__restrict self,
                              USER CHECKED void *dst,
                              size_t num_bytes, pos_t addr, iomode_t mode,
                              struct aio_multihandle *__restrict aio) {
	size_t result;
	result = handle_characterdevice_pread(self, dst, num_bytes, addr, mode);
	aio_multihandle_done(aio);
	return result;
}

INTERN size_t KCALL
handle_characterdevice_apwrite(struct character_device *__restrict self,
                               USER CHECKED void const *src,
                               size_t num_bytes, pos_t addr, iomode_t mode,
                               struct aio_multihandle *__restrict aio) {
	size_t result;
	result = handle_characterdevice_pwrite(self, src, num_bytes, addr, mode);
	aio_multihandle_done(aio);
	return result;
}

INTERN size_t KCALL
handle_characterdevice_apreadv(struct character_device *__restrict self,
                               struct aio_buffer *__restrict dst,
                               size_t num_bytes, pos_t addr, iomode_t mode,
                               struct aio_multihandle *__restrict aio) {
	size_t result;
	result = handle_characterdevice_preadv(self, dst, num_bytes, addr, mode);
	aio_multihandle_done(aio);
	return result;
}
INTERN size_t KCALL
handle_characterdevice_apwritev(struct character_device *__restrict self,
                                struct aio_buffer *__restrict src,
                                size_t num_bytes, pos_t addr, iomode_t mode,
                                struct aio_multihandle *__restrict aio) {
	size_t result;
	result = handle_characterdevice_pwritev(self, src, num_bytes, addr, mode);
	aio_multihandle_done(aio);
	return result;
}

INTERN syscall_slong_t KCALL
handle_characterdevice_ioctl(struct character_device *__restrict self, syscall_ulong_t cmd,
                             USER UNCHECKED void *arg, iomode_t mode) {
	if (self->cd_type.ct_ioctl)
		return (*self->cd_type.ct_ioctl)(self, cmd, arg, mode);
	THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
	      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
	      cmd);
}

INTERN NONNULL((1)) REF struct vm_datablock *KCALL
handle_characterdevice_mmap(struct character_device *__restrict self,
                            vm_vpage64_t *__restrict pminpage,
                            vm_vpage64_t *__restrict pmaxpage) THROWS(...) {
	if (self->cd_type.ct_mmap)
		return (*self->cd_type.ct_mmap)(self, pminpage, pmaxpage);
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_MMAP);
}

INTERN void KCALL
handle_characterdevice_sync(struct character_device *__restrict self) {
	if (self->cd_type.ct_sync)
		(*self->cd_type.ct_sync)(self);
}

INTERN void KCALL
handle_characterdevice_stat(struct character_device *__restrict self,
                            USER CHECKED struct stat *result) {
	memset(result, 0, sizeof(*result));
	result->st_mode = S_IFCHR;
	result->st_dev  = (__dev_t)character_device_devno(self);
	result->st_rdev = (__dev_t)character_device_devno(self);
	if unlikely(self->cd_type.ct_stat) {
		(*self->cd_type.ct_stat)(self, result);
	}
}

INTERN poll_mode_t KCALL
handle_characterdevice_poll(struct character_device *__restrict self,
                            poll_mode_t what) {
	if unlikely(!self->cd_type.ct_poll)
		return 0;
	return (*self->cd_type.ct_poll)(self, what);
}

INTERN syscall_slong_t KCALL
handle_characterdevice_hop(struct character_device *__restrict self,
                           syscall_ulong_t cmd,
                           USER UNCHECKED void *arg,
                           iomode_t mode) {
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


DEFINE_PUBLIC_ALIAS(character_device_read, handle_characterdevice_read);
DEFINE_PUBLIC_ALIAS(character_device_write, handle_characterdevice_write);
DEFINE_PUBLIC_ALIAS(character_device_pread, handle_characterdevice_pread);
DEFINE_PUBLIC_ALIAS(character_device_pwrite, handle_characterdevice_pwrite);
DEFINE_PUBLIC_ALIAS(character_device_ioctl, handle_characterdevice_ioctl);
DEFINE_PUBLIC_ALIAS(character_device_mmap, handle_characterdevice_mmap);
DEFINE_PUBLIC_ALIAS(character_device_sync, handle_characterdevice_sync);
DEFINE_PUBLIC_ALIAS(character_device_stat, handle_characterdevice_stat);
DEFINE_PUBLIC_ALIAS(character_device_poll, handle_characterdevice_poll);


#ifndef CONFIG_NO_DEBUGGER
PRIVATE void KCALL
do_dump_character_device(struct character_device *__restrict self) {
	char const *kind;
	if (character_device_isattybase(self))
		kind = ttybase_isapty((struct ttybase_device *)self) ? "pty" : "tty";
	else if (character_device_isakeyboard(self))
		kind = "keyboard";
	else if (character_device_isamouse(self))
		kind = "mouse";
	else {
		kind = "other";
	}
	dbg_printf("/dev/" DF_WHITE("%s") "\t%u:%-2u\t%s\t%s\t",
	           self->cd_name,
	           (unsigned int)MAJOR(character_device_devno(self)),
	           (unsigned int)MINOR(character_device_devno(self)),
	           self->cd_type.ct_driver ? self->cd_type.ct_driver->d_name : "?",
	           kind);
	dbg_putc(self->cd_type.ct_read ? 'r' : '-');
	dbg_putc(self->cd_type.ct_write ? 'w' : '-');
	dbg_putc(self->cd_type.ct_pread ? 'R' : '-');
	dbg_putc(self->cd_type.ct_pwrite ? 'W' : '-');
	dbg_putc(self->cd_type.ct_ioctl ? 'i' : '-');
	dbg_putc(self->cd_type.ct_mmap ? 'm' : '-');
	dbg_putc(self->cd_type.ct_sync ? 's' : '-');
	dbg_putc(self->cd_type.ct_stat ? 't' : '-');
	dbg_putc(self->cd_type.ct_poll ? 'p' : '-');
	dbg_putc('\n');
}

PRIVATE void KCALL
dump_character_device(struct character_device *__restrict self) {
again:
	do_dump_character_device(self);
	if (self->cd_devlink.a_min) {
		if (self->cd_devlink.a_max)
			dump_character_device(self->cd_devlink.a_max);
		self = self->cd_devlink.a_min;
		goto again;
	}
	if (self->cd_devlink.a_max) {
		self = self->cd_devlink.a_max;
		goto again;
	}
}

DEFINE_DEBUG_FUNCTION(
		"lschr",
		"lschr\n"
		"\tList all defined character devices\n"
		, argc, argv) {
	dbg_print("     name\tdevno\tdriver\tkind\tfeatures\n");
	if (character_device_tree)
		dump_character_device(character_device_tree);
	return 0;
}

#endif /* !CONFIG_NO_DEBUGGER */


DECL_END

#endif /* !GUARD_KERNEL_SRC_DEV_CHAR_C */
