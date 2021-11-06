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
#ifndef GUARD_KERNEL_CORE_FILESYS_ROOTFS_C
#define GUARD_KERNEL_CORE_FILESYS_ROOTFS_C 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver-param.h>
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

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

INTERN ATTR_FREEDATA char const *kernel_root_partition = NULL;
DEFINE_KERNEL_COMMANDLINE_OPTION(kernel_root_partition, KERNEL_COMMANDLINE_OPTION_TYPE_STRING, "boot");

/* Search criteria for KOS auto-detecting the KOS root partition
 * - Sorted in order of descending priority. */
#define FIND_UNIQUE_BLKDEV_BYACTIVE    0
#define FIND_UNIQUE_BLKDEV_BYPARTNAME  1
#define FIND_UNIQUE_BLKDEV_BYDISKNAME  2
#define FIND_UNIQUE_BLKDEV_BYPARTNAME2 3
#define FIND_UNIQUE_BLKDEV_BYDISKNAME2 4
/* TODO: Another criteria that tries to do `ffilesys_opendev()' for every partition that was detected.
 *       If a filesystem could be mounted, check if it contains a file "/os/kernel.bin", and if so, if
 *       that file is an  ELF binary with  a build timestamp (XXX:  add a build  timestamp to the  KOS
 *       kernel) that matches the timestamp of the loaded kernel.
 * NOTE: Also don't hardcode "/os/kernel.bin" here; use `module_getname(&kernel_driver)' */
#define FIND_UNIQUE_BLKDEV_COUNT       5


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

		case FIND_UNIQUE_BLKDEV_BYDISKNAME:
			ismatch = LIST_NEXT(me, bd_partinfo.bp_partlink) == NULL &&
			          LIST_FIRST(&me->bd_partinfo.bp_master->bd_rootinfo.br_parts) == me &&
			          strcasecmp(me->bd_partinfo.bp_master->bd_rootinfo.br_mbr_diskuid, "kos") == 0;
			break;

		case FIND_UNIQUE_BLKDEV_BYPARTNAME2:
			ismatch = strcasestr(me->bd_partinfo.bp_efi_name, "kos") != NULL;
			break;

		case FIND_UNIQUE_BLKDEV_BYDISKNAME2:
			ismatch = LIST_NEXT(me, bd_partinfo.bp_partlink) == NULL &&
			          LIST_FIRST(&me->bd_partinfo.bp_master->bd_rootinfo.br_parts) == me &&
			          strcasestr(me->bd_partinfo.bp_master->bd_rootinfo.br_mbr_diskuid, "kos") != NULL;
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
	if unlikely(!devfs.fs_nodes)
		result = NULL;
	else {
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
PRIVATE ATTR_FREETEXT ATTR_RETNONNULL WUNUSED REF struct blkdev *
NOTHROW(KCALL kernel_get_root_partition)(void) {
	REF struct blkdev *result;
	unsigned int criteria;
again:

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

	/* Fallback: cause kernel panic */
	kernel_panic(FREESTR("Boot partition not found or ambiguous (reboot with `boot=...')"));
	goto again;
}

INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_rootfs)(void) {
	REF struct blkdev *root;
	struct pathmount *mount;
	REF struct fsuper *super;
	bool newly_created;

	/* Lookup the root partition. */
	root = kernel_get_root_partition();

	/* Open the filesystem of the partition */
	super = ffilesys_opendev(&newly_created, root, NULL);

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
		vfs_rootlock_write(&vfs_kernel);
		vfs_rootlock_endwrite(&vfs_kernel);
		goto again_acquire_locks;
	}
	if (!vfs_mountslock_tryacquire(&vfs_kernel)) {
		fsuper_mounts_endwrite(super);
		vfs_rootlock_endwrite(&vfs_kernel);
		vfs_mountslock_acquire(&vfs_kernel);
		vfs_mountslock_release(&vfs_kernel);
		goto again_acquire_locks;
	}
	if (!fs_pathlock_trywrite(&fs_kernel)) {
		vfs_mountslock_release(&vfs_kernel);
		fsuper_mounts_endwrite(super);
		vfs_rootlock_endwrite(&vfs_kernel);
		fs_pathlock_write(&fs_kernel);
		fs_pathlock_endwrite(&fs_kernel);
		goto again_acquire_locks;
	}

	/* Install hooks. */
	assert(super->fs_mounts.lh_first != FSUPER_MOUNTS_DELETED);
	LIST_INSERT_HEAD(&super->fs_mounts, mount, pm_fsmount);
	LIST_INSERT_HEAD(&vfs_kernel.vf_mounts, mount, pm_vsmount); /* Inherit reference */
	vfs_kernel.vf_root = mount;                                 /* Inherit reference */
	fs_kernel.fs_root  = mount;                                 /* Inherit reference */
	fs_kernel.fs_cwd   = mount;                                 /* Inherit reference */

	/* Release locks. */
	fsuper_mounts_endwrite(super);
	fs_pathlock_endwrite(&fs_kernel);
	vfs_mountslock_release(&vfs_kernel);
	vfs_rootlock_endwrite(&vfs_kernel);

	/* Indicate completion of the mount operation. */
	ffilesys_open_done(root);
	decref_unlikely(root);
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_ROOTFS_C */
