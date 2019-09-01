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
#ifndef GUARD_KERNEL_INCLUDE_DEV_CHAR_H
#define GUARD_KERNEL_INCLUDE_DEV_CHAR_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/sequence/atree.h>

#include <kos/io.h>

DECL_BEGIN

#ifdef __CC__
struct character_device;
struct character_device_type;
struct aio_multihandle;

struct character_device_type {
	REF struct driver *ct_driver; /* [1..1] The associated, implementing driver. */
	/* [0..1] Finalizer callback. */
	NOBLOCK NONNULL((1)) void /*NOTHROW*/(KCALL *ct_fini)(struct character_device *__restrict self);
	/* All of these are [0..1] */
	NONNULL((1)) size_t (KCALL *ct_read)(struct character_device *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
	NONNULL((1)) size_t (KCALL *ct_write)(struct character_device *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
	NONNULL((1)) size_t (KCALL *ct_pread)(struct character_device *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
	NONNULL((1)) size_t (KCALL *ct_pwrite)(struct character_device *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
	NONNULL((1)) syscall_slong_t (KCALL *ct_ioctl)(struct character_device *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
	NONNULL((1)) REF struct vm_datablock *(KCALL *ct_mmap)(struct character_device *__restrict self, vm_vpage64_t *__restrict pminpage, vm_vpage64_t *__restrict pmaxpage) THROWS(...);
	NONNULL((1)) void (KCALL *ct_sync)(struct character_device *__restrict self) THROWS(...);
	NONNULL((1)) void (KCALL *ct_stat)(struct character_device *__restrict self, USER CHECKED struct stat *result) THROWS(...);
	/* @return: * : Set of available signals. */
	NONNULL((1)) poll_mode_t (KCALL *ct_poll)(struct character_device *__restrict self, poll_mode_t what);
};

struct character_device {
	WEAK refcnt_t                cd_refcnt;      /* Reference counter. */
	size_t                       cd_heapsize;    /* [const] Allocated heap-size of this character-device. */
	struct character_device_type cd_type;        /* [1..1] Character device type. */
	ATREE_NODE_SINGLE(struct character_device, dev_t)
	                             cd_devlink;     /* [lock(WRITE_ONCE)] Device number / tree (`DEV_UNSET' if unset). */
	REF struct inode            *cd_devfs_inode; /* [lock(WRITE_ONCE)][0..1] Device INode under /dev, or NULL if not created */
	REF struct directory_entry  *cd_devfs_entry; /* [lock(WRITE_ONCE)][1..1][valid_if(cd_devfs_inode)] Directory entry under /dev */
	char                         cd_name[16];    /* [const] Name of the device (auto-generated when unset during device registration)
	                                              * This is the name by which the device can be discovered within the `/dev' directory. */
};

/* Destroy a given character device. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL character_device_destroy)(struct character_device *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct character_device, cd_refcnt, character_device_destroy)

/* Allocate and initialize a new character device.
 * The caller must still initialize:
 *   >> return->cd_type;
 * As well as optionally:
 *   >> return->cd_name
 * This function will initialize the following memory to non-zero values:
 *   >> return->cd_max_retry = 2;
 */
FUNDEF WUNUSED ATTR_RETNONNULL ATTR_MALLOC REF struct character_device *KCALL
character_device_alloc(struct driver *__restrict owner,
                       size_t structure_size DFL(sizeof(struct character_device)))
		THROWS(E_BADALLOC, E_WOULDBLOCK);
#define CHARACTER_DEVICE_ALLOC(T) ((REF T *)character_device_alloc(&drv_self, sizeof(T)))


/* Returns the device number of `self', or `DEV_UNSET' if not set. */
#define character_device_devno(self) ((self)->cd_devlink.a_vaddr)


/* Lookup a character device associated with `devno' and return a reference to it.
 * When no character device is associated that device number, return `NULL' instead. */
FUNDEF WUNUSED REF struct character_device *KCALL
character_device_lookup(dev_t devno) THROWS(E_WOULDBLOCK);

/* Same as `character_device_lookup()', but return `NULL'
 * if the lookup would have caused an exception. */
FUNDEF WUNUSED REF struct character_device *
NOTHROW(KCALL character_device_lookup_nx)(dev_t devno);

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
FUNDEF WUNUSED REF struct character_device *KCALL
character_device_lookup_name(USER CHECKED char const *name)
		THROWS(E_WOULDBLOCK, E_SEGFAULT);
#ifdef __cplusplus
extern "C++" {
FUNDEF WUNUSED REF struct character_device *KCALL
character_device_lookup(USER CHECKED char const *name)
		ASMNAME("character_device_lookup_name")
		THROWS(E_WOULDBLOCK, E_SEGFAULT);
}
#endif /* __cplusplus */


/* Unregister the given character-device from the character-device-id tree, as well as
 * removing its auto-generated entry from `/dev' (should that entry have been created).
 * @return: true:  Successfully unregistered the given.
 * @return: false: The device was never registered to begin with. */
FUNDEF NONNULL((1)) bool KCALL
character_device_unregister(struct character_device *__restrict self)
		THROWS(E_WOULDBLOCK);

/* Register a character device with a fixed device number.
 * NOTE: When empty, `cd_name' will be set to `"%.2x:%.2x" % (MAJOR(devno),MINOR(devno))'
 * NOTE: This function will also cause the device to appear in `/dev' (unless the device's name is already taken) */
FUNDEF NONNULL((1)) void KCALL
character_device_register(struct character_device *__restrict self, dev_t devno)
		THROWS(E_WOULDBLOCK, E_BADALLOC);


/* Automatically register the given character-device, assigning it an auto-generated device ID.
 * All other devices are assigned some unique major device number `>= DEV_MAJOR_AUTO' with MINOR set to `0'.
 * NOTE: When empty, `cd_name' will be set to `"%.2x:%.2x" % (MAJOR(devno),MINOR(devno))'
 * NOTE: This function will also cause the device to appear in `/dev' (unless the device's name is already taken) */
FUNDEF NONNULL((1)) void KCALL
character_device_register_auto(struct character_device *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC);


/* Character device I/O functions. */
FUNDEF NONNULL((1)) size_t KCALL character_device_read(struct character_device *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
FUNDEF NONNULL((1)) size_t KCALL character_device_write(struct character_device *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
FUNDEF NONNULL((1)) size_t KCALL character_device_pread(struct character_device *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
FUNDEF NONNULL((1)) size_t KCALL character_device_pwrite(struct character_device *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
FUNDEF NONNULL((1)) syscall_slong_t KCALL character_device_ioctl(struct character_device *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
FUNDEF NONNULL((1)) REF struct vm_datablock *KCALL character_device_mmap(struct character_device *__restrict self, vm_vpage64_t *__restrict pminpage, vm_vpage64_t *__restrict pmaxpage) THROWS(...);
FUNDEF NONNULL((1)) void KCALL character_device_sync(struct character_device *__restrict self) THROWS(...);
FUNDEF NONNULL((1)) void KCALL character_device_stat(struct character_device *__restrict self, USER CHECKED struct stat *result) THROWS(...);
FUNDEF NONNULL((1)) poll_mode_t KCALL character_device_poll(struct character_device *__restrict self, poll_mode_t what) THROWS(...);


#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_DEV_CHAR_H */
