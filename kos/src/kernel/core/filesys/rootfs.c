/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_FILESYS_ROOTFS_C
#define GUARD_KERNEL_CORE_FILESYS_ROOTFS_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver-param.h>
#include <kernel/fs/allnodes.h>
#include <kernel/fs/blkdev.h>
#include <kernel/fs/devfs.h>
#include <kernel/fs/filesys.h>
#include <kernel/fs/fs.h>
#include <kernel/fs/path.h>
#include <kernel/fs/ramfs.h>
#include <kernel/fs/super.h>
#include <kernel/fs/vfs.h>
#include <kernel/malloc.h>
#include <kernel/mman/driver.h>
#include <kernel/panic.h>
#include <kernel/printk.h>

#include <linux/fs.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

INTERN ATTR_FREEDATA char const *kernel_root_partition = NULL;
DEFINE_KERNEL_COMMANDLINE_OPTION(kernel_root_partition, KERNEL_COMMANDLINE_OPTION_TYPE_STRING, "boot");

/* Search criteria for KOS auto-detecting the KOS root partition
 * - Sorted in order of descending priority. */
#define FIND_UNIQUE_BLKDEV_BYACTIVE    0
#define FIND_UNIQUE_BLKDEV_BYPARTNAME  1
#define FIND_UNIQUE_BLKDEV_BYPARTNAME2 2
#define FIND_UNIQUE_BLKDEV_COUNT       3


/* Search the devfs device tree for a unique block-device matching `criteria' */
PRIVATE ATTR_FREETEXT WUNUSED NONNULL((1)) struct blkdev *
NOTHROW(KCALL find_unique_blkdev_intree)(struct fnode *__restrict root,
                                         unsigned int criteria) {
	struct blkdev *result = NULL;
again:
	if (device_isblkpart(root) && !wasdestroyed(root)) {
		bool ismatch;
		struct blkdev *me = device_asblk(root);
		switch (criteria) {

		case FIND_UNIQUE_BLKDEV_BYACTIVE:
			ismatch = me->bd_partinfo.bp_active != 0;
			break;

		case FIND_UNIQUE_BLKDEV_BYPARTNAME:
			ismatch = strcasecmp(me->bd_partinfo.bp_efi_name, "kos") == 0;
			break;

		case FIND_UNIQUE_BLKDEV_BYPARTNAME2:
			ismatch = strcasestr(me->bd_partinfo.bp_efi_name, "kos") != NULL;
			break;

		default: __builtin_unreachable();
		}
		if (ismatch) {
			if (result) /* Ambiguous... */
				return (struct blkdev *)-1;
			result = me;
		}
	}
	if (root->fn_supent.rb_lhs) {
		if (root->fn_supent.rb_rhs) {
			struct blkdev *new_result;
			new_result = find_unique_blkdev_intree(root->fn_supent.rb_rhs, criteria);
			if (new_result) {
				if (result || new_result == (struct blkdev *)-1)
					return (struct blkdev *)-1;
				result = new_result;
			}
		}
		root = root->fn_supent.rb_lhs;
		goto again;
	}
	if (root->fn_supent.rb_rhs) {
		root = root->fn_supent.rb_rhs;
		goto again;
	}
	return result;
}

/* Search the devfs device tree for a unique block-device matching `criteria' */
PRIVATE ATTR_FREETEXT WUNUSED REF struct blkdev *
NOTHROW(KCALL find_unique_blkdev)(unsigned int criteria) {
	struct blkdev *result;
	fsuper_nodes_read(&devfs);
	if unlikely(!devfs.fs_nodes) {
		result = NULL;
	} else {
		do {
			result = find_unique_blkdev_intree(devfs.fs_nodes, criteria);
			if (result == (struct blkdev *)-1)
				result = NULL; /* Ambiguous */
		} while (result && !tryincref(result));
	}
	fsuper_nodes_endread(&devfs);
	return result;
}


/* Return the partition device which should be mounted as the filesystem root. */
PRIVATE ATTR_FREETEXT WUNUSED REF struct blkdev *
NOTHROW(KCALL kernel_get_root_partition)(void) {
	REF struct blkdev *result;
	unsigned int criteria;
	/* Highest priority: kernel_root_partition (commandline option) */
	if (kernel_root_partition) {
		result = (REF struct blkdev *)device_lookup_bystring(kernel_root_partition,
		                                                     strlen(kernel_root_partition),
		                                                     S_IFBLK);
		if (!result)
			kernel_panic(FREESTR("Unknown device: %q"), kernel_root_partition);
		return result;
	}

	/* Search for the root partition via a set of criteria */
	for (criteria = 0; criteria < FIND_UNIQUE_BLKDEV_COUNT; ++criteria) {
		result = find_unique_blkdev(criteria);
		if (result)
			return result;
	}

	/* Default search criteria didn't yield any results. */
	return NULL;
}



/* Open and return the `/os/kernel.bin' file (if present within `self') */
PRIVATE ATTR_FREETEXT WUNUSED NONNULL((1)) bool KCALL
fsuper_open_os_kernel_bin(struct fsuper *__restrict self) {
	REF struct fnode *kbin;
	kbin = fdirnode_lookup_path(&self->fs_root, kernel_driver.md_fsname->fd_name);
	if (!kbin)
		return false;
	FINALLY_DECREF_UNLIKELY(kbin);
	if unlikely(!fnode_isreg(kbin) ||
	            !mfile_hasrawio(kbin))
		return false;

	/* TODO: Verify that `kbin' is an ELF binary, and that it contains
	 *       a build timestamp that matches the build timestamp of our
	 *       loaded kernel. */

	return true;
}



/* Flags for `kernel_open_rootfs_bydev()' */
#define KERNEL_OPEN_ROOTFS_BYDEV_F_PARTS 0x0001 /* Mount partitions (as opposed to drive roots) */
#define KERNEL_OPEN_ROOTFS_BYDEV_F_LABEL 0x0002 /* Check for "KOS" in filesystem labels. */
#define KERNEL_OPEN_ROOTFS_BYDEV_F_EQLBL 0x0004 /* Label must equal "KOS" (case-insensitive) */
typedef u8 kernel_open_rootfs_bydev_flag_t; /* Set of `KERNEL_OPEN_ROOTFS_BYDEV_F_*' */


/* Go through all block devices and try to open them as superblocks.
 * When able to do the open, check if the filesystem contains a file
 * "/os/kernel.bin" that is a regular file
 * @param: flags: Set of `KERNEL_OPEN_ROOTFS_BYDEV_F_*' */
PRIVATE ATTR_FREETEXT WUNUSED NONNULL((1, 2)) REF struct fsuper *
NOTHROW(KCALL kernel_open_rootfs_trydev)(struct blkdev *__restrict dev,
                                         bool *__restrict pnewly_created,
                                         kernel_open_rootfs_bydev_flag_t flags) {
	REF struct fsuper *result = NULL;
	TRY {
		/* Try to open the superblock. */
		result = ffilesys_opendev(pnewly_created, dev, NULL);
		if (result) {
			printk(FREESTR(KERN_INFO "[boot] Opened \"/dev/%#q\" as %s-filesystem while searching for rootfs\n"),
			       dev->dv_dirent->dd_dirent.fd_name, result->fs_sys->ffs_name);
			if (flags & KERNEL_OPEN_ROOTFS_BYDEV_F_LABEL) {
				/* If the filesystem defines a label-field (like seen in FAT), then
				 * we  also check if that field contains  a string "KOS", and if it
				 * does, we can skip the open-os-kernel-bin test below. */
				char label[FSLABEL_MAX];
				bool haslabel;
				TRY {
					haslabel = fsuper_getlabel(result, label);
				} EXCEPT {
					haslabel = false;
				}
				if (haslabel && ((flags & KERNEL_OPEN_ROOTFS_BYDEV_F_EQLBL) ? strcasecmp(label, "KOS") == 0
				                                                            : strcasestr(label, "KOS") != NULL)) {
					printk(FREESTR(KERN_INFO "[boot] %s-filesystem loaded from \"/dev/%#q\" "
					                         "has label %q referencing 'KOS'\n"),
					       result->fs_sys->ffs_name,
					       dev->dv_dirent->dd_dirent.fd_name, label);
					return result; /* Found it! */
				}
			}

			/* Try to open "/os/kernel.bin" on this filesystem. */
			if (fsuper_open_os_kernel_bin(result)) {
				printk(FREESTR(KERN_INFO "[boot] Found %q on %s-filesystem loaded from \"/dev/%#q\"\n"),
				       kernel_driver.md_fsname->fd_name, result->fs_sys->ffs_name,
				       dev->dv_dirent->dd_dirent.fd_name);
				return result; /* Found it! */
			}
		}
	} EXCEPT {
		except_printf(FREESTR("Opening blkdev \"/dev/%#q\""),
		              dev->dv_dirent->dd_dirent.fd_name);
	}
	if (result) {
		if (*pnewly_created)
			ffilesys_open_done(dev);
		fsuper_delete(result);
		decref_likely(result);
	}
	return NULL;
}


/* Try to find the root filesystem by opening drives and checking if
 * they contain a filesystem that matches what we expect to see as a
 * normal KOS rootfs.
 * @param: flags: Set of `KERNEL_OPEN_ROOTFS_BYDEV_F_*' */
PRIVATE ATTR_FREETEXT WUNUSED NONNULL((1)) REF struct fsuper *
NOTHROW(KCALL kernel_open_rootfs_bydev)(bool *__restrict pnewly_created,
                                        kernel_open_rootfs_bydev_flag_t flags) {
	bool result_newly_created = false;
	REF struct fsuper *result = NULL;
	REF struct fnode *iter    = fsuper_nodeafter(&devfs, NULL);
	while (iter) {
		FINALLY_DECREF_UNLIKELY(iter);
		if ((flags & KERNEL_OPEN_ROOTFS_BYDEV_F_PARTS) ? fnode_isblkpart(iter)
		                                               : fnode_isblkroot(iter)) {
			REF struct fsuper *new_result;
			new_result = kernel_open_rootfs_trydev(fnode_asblkdev(iter),
			                                       pnewly_created, flags);
			if (new_result) {
				/* Found a good-looking candidate. */
				if (result) {
					/* Ambiguous... :( */
					if (result_newly_created)
						ffilesys_open_done(result->fs_dev);
					fsuper_delete(result);
					decref_likely(result);
					if (*pnewly_created)
						ffilesys_open_done(new_result->fs_dev);
					fsuper_delete(new_result);
					decref_likely(new_result);
					return NULL;
				}
				result               = new_result;
				result_newly_created = *pnewly_created;
			}
		}
		iter = fsuper_nodeafter(&devfs, iter);
	}
	*pnewly_created = result_newly_created;
	return result;
}


/* Return an opened superblock for the boot=... root partition. */
PRIVATE ATTR_FREETEXT ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fsuper *
NOTHROW(KCALL kernel_open_rootfs)(bool *__restrict pnewly_created) {
	REF struct fsuper *result;
	REF struct blkdev *rootpart;
again:
	rootpart = kernel_get_root_partition();

	/* Open the filesystem of the partition */
	if (rootpart) {
		FINALLY_DECREF_UNLIKELY(rootpart);
		result = ffilesys_opendev(pnewly_created, rootpart, NULL);
		if unlikely(!result) {
			kernel_panic(FREESTR("No driver to open boot parition \"/dev/%#q\" "
			                     "(reboot with relevant fs-driver or different `boot=...')"),
			             rootpart->dv_dirent->dd_dirent.fd_name);
			goto again;
		}
		return result;
	}

	/* Tell the user what's going on. */
	printk(FREESTR(KERN_WARNING "[boot] Boot partition not found or ambiguous. Consider booting with `boot=...'\n"
	                            "[boot] Trying to find root filesystem by opening all block devices in search of %q\n"),
	       kernel_driver.md_fsname->fd_name);

	/* Try to tell the root filesystem by the presence of `/os/kernel.bin' */
	{
		static kernel_open_rootfs_bydev_flag_t const flags[] = {
			KERNEL_OPEN_ROOTFS_BYDEV_F_PARTS | KERNEL_OPEN_ROOTFS_BYDEV_F_LABEL | KERNEL_OPEN_ROOTFS_BYDEV_F_EQLBL,
			KERNEL_OPEN_ROOTFS_BYDEV_F_PARTS | KERNEL_OPEN_ROOTFS_BYDEV_F_LABEL,
			KERNEL_OPEN_ROOTFS_BYDEV_F_PARTS,
			KERNEL_OPEN_ROOTFS_BYDEV_F_LABEL | KERNEL_OPEN_ROOTFS_BYDEV_F_EQLBL,
			KERNEL_OPEN_ROOTFS_BYDEV_F_LABEL,
			0,
		};
		unsigned int i;
		for (i = 0; i < lengthof(flags); ++i) {
			result = kernel_open_rootfs_bydev(pnewly_created, flags[i]);
			if (result) {
				printk(FREESTR(KERN_NOTICE "[boot] Boot partition found the hard way. "
				                           "Consider adding 'boot=/dev/%#q' to the kernel "
				                           "cmdline to speed-up booting in the future.\n"),
				       mfile_asdevice(result->fs_dev)->dv_dirent->dd_dirent.fd_name);
				return result;
			}
		}
	}

	/* Fallback: cause kernel panic (but if the user CRTL+D-s the message, repeat the search) */
	kernel_panic(FREESTR("Boot partition not found or ambiguous (load "
	                     "missing drivers and/or reboot with `boot=...')"));
	goto again;
}

INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_rootfs)(void) {
	struct pathmount *mount;
	REF struct fsuper *super;
	bool newly_created;

	/* Open the filesystem of the partition */
	super = kernel_open_rootfs(&newly_created);

	/* Create the root mounting point descriptor. */
	mount = _pathmount_alloc();
	mount->p_refcnt = 4; /* +1: vfs_kernel.vf_root, +1: vfs_kernel.vf_mounts,
	                      * +1: fs_kernel.fs_root, +1: fs_kernel.fs_cwd */
	mount->p_flags  = PATH_F_ISMOUNT | PATH_F_ISROOT;
	mount->_p_vfs   = weakincref(&vfs_kernel);
	mount->p_name   = incref(&fdirent_empty);
	mount->p_dir    = &super->fs_root; /* Inherit reference */
	TAILQ_ENTRY_UNBOUND_INIT(&mount->p_recent);
	shared_rwlock_init(&mount->p_cldlock);
	SLIST_INIT(&mount->p_cldlops);
	mount->p_cldused = 0;
	mount->p_cldsize = 0;
	mount->p_cldmask = 0;
	mount->p_cldlist = path_empty_cldlist;

	/* This is the reference that will be held by `mount->pm_fsmount' */
	incref(super->fs_sys->ffs_drv);

	/* Hook the mounting point
	 *
	 * NOTE: You could argue that we don't need to care about locks here,
	 *       and  you might be right on that one. However, custom drivers
	 *       may have already been loaded  at this point, and some  other
	 *       thread may currently be doing  reads from FS structures,  in
	 *       which case our writes cannot be unprotected. */
again_acquire_locks:
	fsuper_mounts_write(super);
	if (!vfs_rootlock_trywrite(&vfs_kernel)) {
		fsuper_mounts_endwrite(super);
		vfs_rootlock_waitwrite(&vfs_kernel);
		goto again_acquire_locks;
	}
	if (!vfs_mountslock_tryacquire(&vfs_kernel)) {
		fsuper_mounts_endwrite(super);
		vfs_rootlock_endwrite(&vfs_kernel);
		vfs_mountslock_waitfor(&vfs_kernel);
		goto again_acquire_locks;
	}
	if (!fs_pathlock_trywrite(&fs_kernel)) {
		vfs_mountslock_release(&vfs_kernel);
		fsuper_mounts_endwrite(super);
		vfs_rootlock_endwrite(&vfs_kernel);
		fs_pathlock_waitwrite(&fs_kernel);
		goto again_acquire_locks;
	}
	if (!fallsuper_tryacquire()) {
		fs_pathlock_endwrite(&fs_kernel);
		vfs_mountslock_release(&vfs_kernel);
		fsuper_mounts_endwrite(super);
		vfs_rootlock_endwrite(&vfs_kernel);
		fallsuper_waitfor();
		goto again_acquire_locks;
	}

	/* Install hooks. */
	assert(super->fs_mounts.lh_first != FSUPER_MOUNTS_DELETED);
	LIST_INSERT_HEAD(&super->fs_mounts, mount, pm_fsmount);
	LIST_INSERT_HEAD(&vfs_kernel.vf_mounts, mount, pm_vsmount); /* Inherit reference */
	vfs_kernel.vf_root = mount;                                 /* Inherit reference */
	fs_kernel.fs_root  = mount;                                 /* Inherit reference */
	fs_kernel.fs_cwd   = mount;                                 /* Inherit reference */
	fallsuper_insert(super);

	/* Release locks. */
	fallsuper_release();
	fsuper_mounts_endwrite(super);
	fs_pathlock_endwrite(&fs_kernel);
	vfs_mountslock_release(&vfs_kernel);
	vfs_rootlock_endwrite(&vfs_kernel);

	/* Indicate completion of the mount operation. */
	if (newly_created)
		ffilesys_open_done(super->fs_dev);
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_ROOTFS_C */
