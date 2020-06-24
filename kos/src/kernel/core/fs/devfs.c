/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_FS_DEVFS_C
#define GUARD_KERNEL_CORE_FS_DEVFS_C 1
#define CONFIG_WANT_FS_AS_STRUCT 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/ramfs.h>
#include <kernel/driver.h>
#include <kernel/types.h>
#include <kernel/vm.h>

#include <hybrid/atomic.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN


PRIVATE struct superblock_type devfs_type = {
	/* .st_driver            = */ &drv_self,
	/* .st_name              = */ "devfs",
	/* .st_flags             = */ (SUPERBLOCK_TYPE_FNODEV | SUPERBLOCK_TYPE_FSINGLE),
	/* .st_sizeof_superblock = */ sizeof(struct superblock),
	{
		.st_singleton = &devfs
	}
};

#define DEVFS_INITIAL_ROOTDIR_MASK  15
#define devfs_lock       devfs.s_rootdir.d_node.i_datablock.db_lock
PUBLIC struct superblock devfs = {
	/* .s_rootdir = */ {
		/* .d_node = */ {
			/* .i_datablock = */ {
				/* .db_refcnt = */ 2, /* +1: devfs, +1: devfs_type.st_singleton */
				/* .db_lock   = */ RWLOCK_INIT,
				/* .db_type   = */ &inode_datablock_type,
#ifdef LIBVIO_CONFIG_ENABLED
				/* .db_vio    = */ NULL,
#endif /* LIBVIO_CONFIG_ENABLED */
				/* .db_parts  = */ NULL,
				VM_DATABLOCK_INIT_PAGEINFO(0)
			},
			/* .i_type         = */ &ramfs_directory_type,
			/* .i_super        = */ &devfs,
			/* .i_fsdata       = */ NULL,
			/* .i_heapsize     = */ sizeof(devfs),
			/* .i_flags        = */ INODE_FNORMAL | INODE_FATTRLOADED | INODE_FDIRLOADED,
			/* .i_changed_next = */ (struct inode *)NULL,
			/* .i_recent       = */ { NULL, NULL },
			/* .i_filetree     = */ { NULL, NULL, (ino_t)0 },
#ifdef __INTELLISENSE__
			/* .i_fileino      = */ (ino_t)0,
#endif
			/* .i_filesize     = */ (pos_t)0,
			/* .i_filemode     = */ (mode_t)(S_IFDIR | 0755),
			/* .i_filenlink    = */ (nlink_t)0,
			/* .i_fileuid      = */ (uid_t)0,
			/* .i_filegid      = */ (gid_t)0,
			/* .i_fileatime    = */ { 0, 0 },
			/* .i_filemtime    = */ { 0, 0 },
			/* .i_filectime    = */ { 0, 0 },
			/* .i_filerdev     = */ (dev_t)0,
		},
		/* .d_parent    = */ NULL,
		/* .d_dirend    = */ NULL,
		/* .d_size      = */ 0,
		/* .d_mask      = */ DEVFS_INITIAL_ROOTDIR_MASK,
		/* .d_map       = */ NULL, /* Allocated during init */
		/* .d_bypos     = */ NULL,
		/* .d_bypos_end = */ NULL
	},
	/* .s_type         = */ &devfs_type,
	/* .s_device       = */ NULL,
	/* .s_driver       = */ &drv_self,
	/* .s_flags        = */ SUPERBLOCK_FNORMAL,
	/* .s_changed_lock = */ ATOMIC_RWLOCK_INIT,
	/* .s_changed      = */ NULL,
	/* .s_delnodes     = */ NULL,
	/* .s_unlinknodes  = */ NULL,
	/* .s_nodes_lock   = */ ATOMIC_RWLOCK_INIT,
	/* .s_nodes        = */ &devfs.s_rootdir.d_node,
	/* .s_mount_lock   = */ ATOMIC_RWLOCK_INIT,
	/* .s_mount        = */ LLIST_INIT,
	/* .s_cblock_next  = */ NULL,
	/* .s_umount_pend  = */ NULL,
	/* .s_filesystems  = */ SLIST_INITNODE
};



/* Insert a new device node into /dev, using `name' as the
 * filename of the file to-be placed under /dev.
 * NOTE: The caller is responsible to ensure that `name'
 *       is a valid filename, suitable to a directory entry.
 * @param: name:         The name of the file to-be placed under /dev
 * @param: kind:         The type of file to create (either `S_IFCHR' or `S_IFBLK')
 * @param: devno:        The character- or block-device number that should be referenced
 * @param: pdevfs_node:  When non-NULL, upon success place a reference to the created INode in here
 * @param: pdevfs_entry: When non-NULL, upon success place a reference to the created directory entry in here
 * @return: true:  Successfully created a new entry under /dev
 * @return: false: A file matching `name' already exists.
 *                 In this case, both `*pdevfs_node' and `*pdevfs_entry'
 *                 (if given) will have been set to `NULL'. */
PUBLIC bool KCALL
devfs_insert(USER CHECKED char const *name,
             mode_t kind, dev_t devno,
             REF struct inode **pdevfs_node,
             REF struct directory_entry **pdevfs_entry)
       THROWS(E_WOULDBLOCK, E_BADALLOC,E_SEGFAULT) {
	REF struct inode *node;
	assert(kind == S_IFCHR || kind == S_IFBLK);
	TRY {
		size_t len = strlen(name);
		node = directory_mknod(&devfs.s_rootdir,
		                       name,
		                       len,
		                       kind | 0644,
		                       (uid_t)0,
		                       (gid_t)0,
		                       devno,
		                       DIRECTORY_MKNOD_FNORMAL,
		                       pdevfs_entry);
	} EXCEPT {
		if (!was_thrown(E_FSERROR_FILE_ALREADY_EXISTS))
			RETHROW();
		if (pdevfs_node)
			*pdevfs_node = NULL;
		if (pdevfs_entry)
			*pdevfs_entry = NULL;
		return false;
	}
	if (pdevfs_node)
		*pdevfs_node = node;
	else {
		decref_unlikely(&node->i_datablock);
	}
	return true;
}


INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_devfs_driver)(void) {
	/* Allocate the initial directory map. */
	devfs.s_rootdir.d_map = (REF struct directory_entry **)kmalloc((DEVFS_INITIAL_ROOTDIR_MASK + 1) *
	                                                               sizeof(REF struct directory_entry *),
	                                                               FS_GFP | GFP_CALLOC);
	/* Register the devfs filesystem type */
	register_filesystem_type(&devfs_type);
	/* Register the devfs filesystem singleton */
	fs_filesystems_lock_write();
	SLIST_INSERT(fs_filesystems.f_superblocks, &devfs, s_filesystems);
	fs_filesystems_lock_endwrite();
}



INTDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL superblock_delete_inode)(struct superblock *__restrict super,
                                       struct inode *__restrict self);

#define DEVFS_PENDING_DELETE_NEXT(x) \
	(*(struct directory_entry **)(x)->de_fsdata.de_data)
PRIVATE ATTR_READMOSTLY REF struct directory_entry *devfs_pending_delete = NULL;

INTDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL directory_delentry)(struct directory_node *__restrict self,
                                  /*out*/ REF struct directory_entry *__restrict entry);

PRIVATE NOBLOCK void
NOTHROW(KCALL devfs_remove_directory_entry)(struct directory_entry *__restrict ent) {
	/* Check if the entry had already been removed. */
	if (ent->de_bypos.ln_pself != NULL) {
		/* Remove the entry from its parent directory. */
		directory_delentry(&devfs.s_rootdir, ent);
		ent->de_bypos.ln_pself = NULL;
		decref_nokill(ent); /* The reference returned by `directory_delentry()' */
	}
}

#define devfs_must_service_pending_delete() \
	(ATOMIC_READ(devfs_pending_delete) != NULL)
LOCAL NOBLOCK void
NOTHROW(KCALL devfs_service_pending_delete)(void) {
	REF struct directory_entry *pend, *next;
	COMPILER_READ_BARRIER();
	pend = ATOMIC_XCH(devfs_pending_delete, NULL);
	while (pend) {
		next = DEVFS_PENDING_DELETE_NEXT(pend);
		devfs_remove_directory_entry(pend);
		decref(pend);
		pend = next;
	}
}


/* Without blocking, remove an INode from the
 * root directory of the /dev filesystem */
PUBLIC NOBLOCK void
NOTHROW(KCALL devfs_remove)(struct inode *__restrict node,
                            struct directory_entry *__restrict entry) {
	/* Remove the given INode from the devfs superblock */
	superblock_delete_inode(&devfs, node);
	/* Try to remove the given node from the recent-cache */
	inode_recent_tryremove(node);
	/* Check if the directory entry had already been removed. */
	if (ATOMIC_READ(entry->de_bypos.ln_pself) == NULL)
		return;
	/* Remove the directory entry */
	if (devfs_lock_trywrite()) {
		devfs_remove_directory_entry(entry);
		devfs_lock_endwrite();
	} else {
		struct directory_entry *next;
		/* Schedule the entry for removal at the next convenient time */
		incref(entry);
		do {
			DEVFS_PENDING_DELETE_NEXT(entry) = next = ATOMIC_READ(devfs_pending_delete);
		} while (!ATOMIC_CMPXCH_WEAK(devfs_pending_delete, next, entry));
again_tryservice:
		if unlikely(sync_trywrite(&devfs_lock)) {
			devfs_service_pending_delete();
			devfs_lock_endwrite();
			COMPILER_READ_BARRIER();
			if unlikely(devfs_must_service_pending_delete())
				goto again_tryservice;
		}
	}
}



/* Devfs locking functions */
PUBLIC void (KCALL devfs_lock_read)(void)
		THROWS(E_BADALLOC, E_INTERRUPT, ...) {
	sync_read(&devfs_lock);
	if (devfs_must_service_pending_delete() &&
	    sync_tryupgrade(&devfs_lock)) {
		devfs_service_pending_delete();
		sync_downgrade(&devfs_lock);
	}
}

PUBLIC void (KCALL devfs_lock_write)(void)
		THROWS(E_INTERRUPT, ...) {
	sync_write(&devfs_lock);
	/* Read beforehand to prevent polluting the cache. */
	if unlikely(devfs_must_service_pending_delete())
		devfs_service_pending_delete();
}

PUBLIC bool (KCALL devfs_lock_upgrade)(void)
		THROWS(E_WOULDBLOCK,E_INTERRUPT,...) {
	bool result;
	result = sync_upgrade(&devfs_lock);
	/* Read beforehand to prevent polluting the cache. */
	if unlikely(devfs_must_service_pending_delete())
		devfs_service_pending_delete();
	return result;
}

PUBLIC bool NOTHROW(KCALL devfs_lock_read_nx)(void) {
	bool result;
	result = sync_read_nx(&devfs_lock);
	if (result &&
	    devfs_must_service_pending_delete() &&
	    sync_tryupgrade(&devfs_lock)) {
		devfs_service_pending_delete();
		sync_downgrade(&devfs_lock);
	}
	return result;
}

PUBLIC bool NOTHROW(KCALL devfs_lock_write_nx)(void) {
	bool result;
	result = sync_write_nx(&devfs_lock);
	if (result && unlikely(devfs_must_service_pending_delete()))
		devfs_service_pending_delete();
	return result;
}

PUBLIC unsigned int NOTHROW(KCALL devfs_lock_upgrade_nx)(void) {
	unsigned int result;
	result = sync_upgrade_nx(&devfs_lock);
	if (result != 0 && unlikely(devfs_must_service_pending_delete()))
		devfs_service_pending_delete();
	return result;
}

PUBLIC NOBLOCK bool NOTHROW(KCALL devfs_lock_tryread)(void) {
	bool result;
	result = sync_tryread(&devfs_lock);
	if (result &&
	    devfs_must_service_pending_delete() &&
	    sync_tryupgrade(&devfs_lock)) {
		devfs_service_pending_delete();
		sync_downgrade(&devfs_lock);
	}
	return result;
}

PUBLIC NOBLOCK bool NOTHROW(KCALL devfs_lock_trywrite)(void) {
	bool result;
	result = sync_trywrite(&devfs_lock);
	if (result && unlikely(devfs_must_service_pending_delete()))
		devfs_service_pending_delete();
	return result;
}

PUBLIC NOBLOCK bool NOTHROW(KCALL devfs_lock_tryupgrade)(void) {
	bool result;
	result = sync_tryupgrade(&devfs_lock);
	if (result && unlikely(devfs_must_service_pending_delete()))
		devfs_service_pending_delete();
	return result;
}

PUBLIC NOBLOCK void NOTHROW(KCALL devfs_lock_endwrite)(void) {
	if unlikely(devfs_must_service_pending_delete())
		goto do_service;
again:
	sync_endwrite(&devfs_lock);
	if unlikely(devfs_must_service_pending_delete()) {
		if (sync_trywrite(&devfs_lock)) {
do_service:
			devfs_service_pending_delete();
			goto again;
		}
	}
}

PUBLIC NOBLOCK bool NOTHROW(KCALL devfs_lock_endread)(void) {
	bool result;
	result = rwlock_endread(&devfs_lock);
again:
	if unlikely(devfs_must_service_pending_delete()) {
		if (sync_trywrite(&devfs_lock)) {
			devfs_service_pending_delete();
			sync_endwrite(&devfs_lock);
			goto again;
		}
	}
	return result;
}

PUBLIC NOBLOCK bool NOTHROW(KCALL devfs_lock_end)(void) {
	bool result;
	result = rwlock_end(&devfs_lock);
again:
	if unlikely(devfs_must_service_pending_delete()) {
		if (sync_trywrite(&devfs_lock)) {
			devfs_service_pending_delete();
			sync_endwrite(&devfs_lock);
			goto again;
		}
	}
	return result;
}

PUBLIC NOBLOCK bool NOTHROW(KCALL devfs_lock_downgrade)(void) {
	bool result;
	if unlikely(devfs_must_service_pending_delete())
		goto do_service;
again:
	result = rwlock_downgrade(&devfs_lock);
	if unlikely(devfs_must_service_pending_delete()) {
#ifndef __OPTIMIZE_SIZE__
		if unlikely(!result)
			goto again; /* We still have the write-lock (the downgrade failed) */
#endif              /* !__OPTIMIZE_SIZE__ */
		if (sync_tryupgrade(&devfs_lock)) {
do_service:
			devfs_service_pending_delete();
			goto again;
		}
	}
	return result;
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_FS_DEVFS_C */
