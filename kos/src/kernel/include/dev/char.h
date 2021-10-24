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
#ifndef GUARD_KERNEL_INCLUDE_DEV_CHAR_H
#define GUARD_KERNEL_INCLUDE_DEV_CHAR_H 1

#include <kernel/compiler.h>

#ifdef CONFIG_USE_NEW_FS
#include <kernel/fs/chrdev.h>
#define chrdev_devno device_getdevno
#else /* CONFIG_USE_NEW_FS */
#include <kernel/types.h>

#include <hybrid/sequence/atree.h>

#include <kos/io.h>

DECL_BEGIN

#ifdef __CC__
struct chrdev;
struct chrdev_ops;
struct aio_multihandle;
struct handle;
struct handle_mmap_info;

struct chrdev_ops {
	REF struct driver *ct_driver; /* [1..1] The associated, implementing driver. */
	/* [0..1] Finalizer callback. */
	NOBLOCK NONNULL((1)) void
	/*NOTHROW*/ (KCALL *ct_fini)(struct chrdev *__restrict self);

	/* All of these are [0..1] */
	NONNULL((1)) size_t
	(KCALL *ct_read)(struct chrdev *__restrict self,
	                 USER CHECKED void *dst, size_t num_bytes,
	                 iomode_t mode)
			THROWS(...);
	NONNULL((1)) size_t
	(KCALL *ct_write)(struct chrdev *__restrict self,
	                  USER CHECKED void const *src, size_t num_bytes,
	                  iomode_t mode)
			THROWS(...);
	NONNULL((1)) size_t
	(KCALL *ct_pread)(struct chrdev *__restrict self,
	                  USER CHECKED void *dst, size_t num_bytes,
	                  pos_t addr, iomode_t mode)
			THROWS(...);
	NONNULL((1)) size_t
	(KCALL *ct_pwrite)(struct chrdev *__restrict self,
	                   USER CHECKED void const *src, size_t num_bytes,
	                   pos_t addr, iomode_t mode)
			THROWS(...);

	NONNULL((1)) syscall_slong_t
	(KCALL *ct_ioctl)(struct chrdev *__restrict self,
	                  syscall_ulong_t cmd,
	                  USER UNCHECKED void *arg, iomode_t mode)
			THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, ...);

	NONNULL((1, 2)) void
	(KCALL *ct_mmap)(struct chrdev *__restrict self,
	                 struct handle_mmap_info *__restrict info)
			THROWS(...);

	NONNULL((1)) void
	(KCALL *ct_sync)(struct chrdev *__restrict self)
			THROWS(...);

	NONNULL((1)) void
	(KCALL *ct_stat)(struct chrdev *__restrict self,
	                 USER CHECKED struct stat *result)
			THROWS(...);

	NONNULL((1)) void
	(KCALL *ct_pollconnect)(struct chrdev *__restrict self,
	                        poll_mode_t what)
			THROWS(...);
	/* @return: * : Set of available signals. */
	NONNULL((1)) poll_mode_t
	(KCALL *ct_polltest)(struct chrdev *__restrict self,
	                     poll_mode_t what)
			THROWS(...);

	/* [0..1] Optional callback that is invoked when the device is opened by user-space.
	 * @param: hand: [in|out] Upon   input,  this  handle  describes  the  already-initialized
	 *                        handle that will be made available to user-space. This  callback
	 *                        is allowed to modify that handle, however it must also take care
	 *                        to  account  for the  fact  that `hand->h_data'  must  contain a
	 *                        reference both on entry and exit!
	 * HINT: `hand' is initialized as follows upon entry:
	 * >> hand->h_type = HANDLE_TYPE_CHRDEV;
	 * >> hand->h_mode = ...; // Depending on o-flags passed to open(2).
	 * >> hand->h_data = incref(self);
	 * NOTE: `h_data' is reference on entry (when modified, you must
	 *       `decref_nokill(self)'  and  assign   `incref(new_obj)') */
	NONNULL((1, 2)) void (KCALL *ct_open)(struct chrdev *__restrict self,
	                                      struct handle *__restrict hand);
};

#define CHARACTER_DEVICE_FLAG_NORMAL  0x0000 /* Normal flags. */
#define CHARACTER_DEVICE_FLAG_WEAKREG 0x0001 /* [const] The device is weakly registered within the character device tree.
                                              * This  means  that the  character device  tree does  not hold  a reference
                                              * to  the device,  and that the  device will automatically  be removed from
                                              * the character device tree once all other references go away. */

struct chrdev {
	WEAK refcnt_t                cd_refcnt;      /* Reference counter. */
	size_t                       cd_heapsize;    /* [const] Allocated heap-size of this character-device. */
	struct chrdev_ops            cd_type;        /* [1..1] Character device type. */
	ATREE_NODE_SINGLE(struct chrdev, dev_t)
	                             cd_devlink;     /* [lock(WRITE_ONCE)] Device number / tree (`DEV_UNSET' if unset). */
	uintptr_t                    cd_flags;       /* Character device flags (Set of `CHARACTER_DEVICE_FLAG_*') */
#ifdef __WANT_CHRDEV_NEXTLINK
	union {
		struct chrdev *cd_nextdead;    /* Used internally during destruction */
		REF struct inode        *cd_devfs_inode; /* [lock(WRITE_ONCE)][0..1] Device INode under /dev, or NULL if not created */
	};
#else /* __WANT_CHRDEV_NEXTLINK */
	REF struct inode            *cd_devfs_inode; /* [lock(WRITE_ONCE)][0..1] Device INode under /dev, or NULL if not created */
#endif /* !__WANT_CHRDEV_NEXTLINK */
	REF struct fdirent  *cd_devfs_entry; /* [lock(WRITE_ONCE)][1..1][valid_if(cd_devfs_inode)] Directory entry under /dev */
	char                         cd_name[16];    /* [const] Name of the device (auto-generated  when unset during device  registration)
	                                              * This is the name by which the device can be discovered within the `/dev' directory. */
};

/* Destroy a given character device. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL chrdev_destroy)(struct chrdev *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct chrdev, cd_refcnt, chrdev_destroy)

/* Allocate and initialize a new character device.
 * The caller must still initialize:
 *   >> return->cd_type;
 * As well as optionally:
 *   >> return->cd_name;
 */
FUNDEF ATTR_MALLOC ATTR_RETNONNULL WUNUSED REF struct chrdev *KCALL
chrdev_alloc(struct driver *__restrict owner,
             size_t structure_size DFL(sizeof(struct chrdev)),
             size_t structure_align DFL(COMPILER_ALIGNOF(struct chrdev)))
		THROWS(E_BADALLOC, E_WOULDBLOCK);
#define CHRDEV_ALLOC(T) \
	((REF T *)chrdev_alloc(&drv_self, sizeof(T), COMPILER_ALIGNOF(T)))

/* Returns the device number of `self', or `DEV_UNSET' if not set. */
#define chrdev_devno(self) ((self)->cd_devlink.a_vaddr)

/* Lookup  a character device associated with `devno'  and return a reference to it.
 * When no character device is associated that device number, return `NULL' instead. */
FUNDEF WUNUSED REF struct chrdev *KCALL
chrdev_lookup(dev_t devno) THROWS(E_WOULDBLOCK);

/* Same as `chrdev_lookup()', but return `NULL'
 * if   the  lookup  would   have  caused  an  exception. */
FUNDEF WUNUSED REF struct chrdev *
NOTHROW(KCALL chrdev_lookup_nx)(dev_t devno);

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
FUNDEF WUNUSED REF struct chrdev *KCALL
chrdev_lookup_name(USER CHECKED char const *name)
		THROWS(E_WOULDBLOCK, E_SEGFAULT);
#ifdef __cplusplus
extern "C++" {
FUNDEF WUNUSED REF struct chrdev *KCALL
chrdev_lookup(USER CHECKED char const *name)
		THROWS(E_WOULDBLOCK, E_SEGFAULT)
		ASMNAME("chrdev_lookup_name");
}
#endif /* __cplusplus */


/* Unregister  the given character-device from the character-device-id tree, as well as
 * removing its auto-generated entry from `/dev' (should that entry have been created).
 * @return: true:  Successfully unregistered the given.
 * @return: false: The device was never registered to begin with. */
FUNDEF NONNULL((1)) bool KCALL
chrdev_unregister(struct chrdev *__restrict self)
		THROWS(E_WOULDBLOCK);

/* Register a character device with a fixed device number.
 * NOTE: When empty, `cd_name' will be set to `"%.2x:%.2x" % (MAJOR(devno),MINOR(devno))'
 * NOTE: This function will also cause the device to appear in `/dev' (unless the device's name is already taken) */
FUNDEF NONNULL((1)) void KCALL
chrdev_register(struct chrdev *__restrict self, dev_t devno)
		THROWS(E_WOULDBLOCK, E_BADALLOC);


/* Automatically   register  the  given   character-device,  assigning  it   an  auto-generated  device  ID.
 * All other devices are assigned some unique major device number `>= DEV_MAJOR_AUTO' with MINOR set to `0'.
 * NOTE: When empty, `cd_name' will be set to
 *       `"%.2" PRIxN(__SIZEOF_MAJOR_T__) ":%.2" PRIxN(__SIZEOF_MINOR_T__) % (MAJOR(devno),MINOR(devno))'
 * NOTE: This function will also cause the device to appear in `/dev' (unless the device's name is already taken) */
FUNDEF NONNULL((1)) void KCALL
chrdev_register_auto(struct chrdev *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC);


/* Character device I/O functions. */
FUNDEF NONNULL((1)) size_t KCALL
chrdev_read(struct chrdev *__restrict self, USER CHECKED void *dst,
            size_t num_bytes, iomode_t mode)
		THROWS(...);

FUNDEF NONNULL((1)) size_t KCALL
chrdev_write(struct chrdev *__restrict self, USER CHECKED void const *src,
             size_t num_bytes, iomode_t mode)
		THROWS(...);

FUNDEF NONNULL((1)) size_t KCALL
chrdev_pread(struct chrdev *__restrict self, USER CHECKED void *dst,
             size_t num_bytes, pos_t addr, iomode_t mode)
		THROWS(...);

FUNDEF NONNULL((1)) size_t KCALL
chrdev_pwrite(struct chrdev *__restrict self, USER CHECKED void const *src,
              size_t num_bytes, pos_t addr, iomode_t mode)
		THROWS(...);


FUNDEF NONNULL((1)) syscall_slong_t KCALL
chrdev_ioctl(struct chrdev *__restrict self,
             syscall_ulong_t cmd, USER UNCHECKED void *arg,
             iomode_t mode)
		THROWS(...);

/* Invoke the `ct_mmap' operator fails to fill in `*pdatablock_fspath'
 * and/or  `*pdatablock_fsname', then this function will automatically
 * make fill in these pointers through use of  `self->cd_devfs_entry',
 * as well as `superblock_find_mount_from_vfs(&devfs, THIS_VFS)' */
FUNDEF NONNULL((1, 2)) void KCALL
chrdev_mmap(struct chrdev *__restrict self,
            struct handle_mmap_info *__restrict info)
		THROWS(...);

FUNDEF NONNULL((1)) void KCALL
chrdev_sync(struct chrdev *__restrict self)
		THROWS(...);

FUNDEF NONNULL((1)) void KCALL
chrdev_stat(struct chrdev *__restrict self,
            USER CHECKED struct stat *result)
		THROWS(...);

FUNDEF NONNULL((1)) void KCALL
chrdev_pollconnect(struct chrdev *__restrict self,
                   poll_mode_t what)
		THROWS(...);

FUNDEF NONNULL((1)) poll_mode_t KCALL
chrdev_polltest(struct chrdev *__restrict self,
                poll_mode_t what)
		THROWS(...);


#endif /* __CC__ */

DECL_END
#endif /* !CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_DEV_CHAR_H */
