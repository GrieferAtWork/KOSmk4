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
#ifndef GUARD_MODPROCFS_PROCFS_C
#define GUARD_MODPROCFS_PROCFS_C 1
#define CONFIG_WANT_FS_AS_STRUCT 1

#include "procfs.h"

#include <kernel/compiler.h>

#include <fs/node.h>
#include <kernel/printk.h>
#include <kernel/driver.h>

#include <libvio/api.h>

DECL_BEGIN

INTERN struct superblock_type ProcFS_Type = {
	/* .st_driver            = */ &drv_self,
	/* .st_name              = */ "procfs",
	/* .st_flags             = */ (SUPERBLOCK_TYPE_FNODEV | SUPERBLOCK_TYPE_FSINGLE),
	/* .st_sizeof_superblock = */ sizeof(struct superblock),
	{
		.st_singleton = &ProcFS
	},
	/* .st_functions = */ {
		/* .f_fini     = */ NULL,
		/* .f_opennode = */ &ProcFS_OpenNode
	}
};

#define PROCFS_INITIAL_ROOTDIR_MASK  15
INTERN struct superblock ProcFS = {
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
			/* .i_type         = */ &ProcFS_RootDirectory_Type,
			/* .i_super        = */ &ProcFS,
			/* .i_fsdata       = */ (struct inode_data *)&ProcFS_RootDirectory_FsData,
			/* .i_heapsize     = */ sizeof(ProcFS),
			/* .i_flags        = */ INODE_FNORMAL | INODE_FATTRLOADED | INODE_FDIRLOADED,
			/* .i_changed_next = */ (struct inode *)NULL,
			/* .i_recent       = */ { NULL, NULL },
			/* .i_filetree     = */ { NULL, NULL, (ino_t)PROCFS_INOMAKE_SINGLETON(PROCFS_SINGLETON_ROOT) },
#ifdef __INTELLISENSE__
			/* .i_fileino      = */ (ino_t)PROCFS_INOMAKE_SINGLETON(PROCFS_SINGLETON_ROOT),
#endif /* __INTELLISENSE__ */
			/* .i_filesize     = */ (pos_t)0,
			/* .i_filemode     = */ (mode_t)(S_IFDIR | 0555),
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
		/* .d_mask      = */ PROCFS_INITIAL_ROOTDIR_MASK,
		/* .d_map       = */ NULL, /* Allocated during init */
		/* .d_bypos     = */ NULL,
		/* .d_bypos_end = */ NULL
	},
	/* .s_type         = */ &ProcFS_Type,
	/* .s_device       = */ NULL,
	/* .s_driver       = */ &drv_self,
	/* .s_flags        = */ SUPERBLOCK_FNORMAL,
	/* .s_changed_lock = */ ATOMIC_RWLOCK_INIT,
	/* .s_changed      = */ NULL,
	/* .s_delnodes     = */ NULL,
	/* .s_unlinknodes  = */ NULL,
	/* .s_nodes_lock   = */ ATOMIC_RWLOCK_INIT,
	/* .s_nodes        = */ &ProcFS.s_rootdir.d_node,
	/* .s_mount_lock   = */ ATOMIC_RWLOCK_INIT,
	/* .s_mount        = */ LLIST_INIT,
	/* .s_cblock_next  = */ NULL,
	/* .s_umount_pend  = */ NULL,
	/* .s_filesystems  = */ SLIST_INITNODE
};


PRIVATE ATTR_FREETEXT DRIVER_INIT void KCALL ProcFS_Init(void) {
	/* Allocate the initial directory map. */
	ProcFS.s_rootdir.d_map = (REF struct directory_entry **)kmalloc((PROCFS_INITIAL_ROOTDIR_MASK + 1) *
	                                                                sizeof(REF struct directory_entry *),
	                                                                FS_GFP | GFP_CALLOC);
	/* Register the procfs filesystem type */
	register_filesystem_type(&ProcFS_Type);
	/* Register the procfs filesystem singleton */
	fs_filesystems_lock_write();
	SLIST_INSERT(fs_filesystems.f_superblocks, &ProcFS, s_filesystems);
	fs_filesystems_lock_endwrite();
}

PRIVATE DRIVER_FINI void KCALL ProcFS_Fini(void) {
	/* Unregister the procfs filesystem singleton. */
	fs_filesystems_lock_write();
	fs_filesystems_remove(&ProcFS);
	fs_filesystems_lock_endwrite();
	/* Unregister the procfs filesystem type. */
	unregister_filesystem_type(&ProcFS_Type);
	/* Allocate the initial directory map. */
	kfree(ProcFS.s_rootdir.d_map);
	ProcFS.s_rootdir.d_map = NULL;
}


DECL_END

#endif /* !GUARD_MODPROCFS_PROCFS_C */
