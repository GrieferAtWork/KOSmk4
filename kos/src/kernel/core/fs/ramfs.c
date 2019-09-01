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
#ifndef GUARD_KERNEL_CORE_FS_RAMFS_C
#define GUARD_KERNEL_CORE_FS_RAMFS_C 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/ramfs.h>
#include <kernel/aio.h>
#include <kernel/driver.h>
#include <kernel/types.h>
#include <kernel/vm.h>

#include <hybrid/atomic.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN

PRIVATE NONNULL((1)) void KCALL
ramfs_saveattr(struct inode *__restrict UNUSED(self))
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_READONLY,
		       E_IOERROR, ...) {
	/* No-op to support changing INode attributes. */
}

PRIVATE NONNULL((1, 5)) void KCALL
ramfs_read(struct inode *__restrict UNUSED(self),
           USER CHECKED void *dst,
           size_t num_bytes, pos_t UNUSED(file_position),
           struct aio_multihandle *__restrict aio)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	/* Initialize data to all zeroes. (This function shouldn't actually be called) */
	memset(dst, 0, num_bytes);
	aio_multihandle_done(aio);
}

PRIVATE NONNULL((1, 5)) void KCALL
ramfs_pread(struct inode *__restrict UNUSED(self),
            vm_phys_t dst,
            size_t num_bytes, pos_t UNUSED(file_position),
            struct aio_multihandle *__restrict aio)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	vm_memsetphys(dst, 0, num_bytes);
	aio_multihandle_done(aio);
}

PRIVATE NONNULL((1, 2, 5)) void KCALL
ramfs_readv(struct inode *__restrict UNUSED(self),
            struct aio_buffer *__restrict buf,
            size_t UNUSED(num_bytes), pos_t UNUSED(file_position),
            struct aio_multihandle *__restrict aio)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	struct aio_buffer_entry ent;
	AIO_BUFFER_FOREACH(ent, buf) {
		memset(ent.ab_base, 0, ent.ab_size);
	}
	aio_multihandle_done(aio);
}

PRIVATE NONNULL((1, 2, 5)) void KCALL
ramfs_preadv(struct inode *__restrict UNUSED(self),
             struct aio_pbuffer *__restrict buf,
             size_t UNUSED(num_bytes), pos_t UNUSED(file_position),
             struct aio_multihandle *__restrict aio)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	struct aio_pbuffer_entry ent;
	AIO_PBUFFER_FOREACH(ent, buf) {
		vm_memsetphys(ent.ab_base, 0, ent.ab_size);
	}
	aio_multihandle_done(aio);
}


PRIVATE NONNULL((1, 5)) void KCALL
ramfs_write(struct inode *__restrict UNUSED(self),
             USER CHECKED void const *UNUSED(src),
             size_t UNUSED(num_bytes), pos_t UNUSED(file_position),
             struct aio_multihandle *__restrict aio)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	aio_multihandle_done(aio);
}

PRIVATE NONNULL((1, 5)) void KCALL
ramfs_pwrite(struct inode *__restrict UNUSED(self),
             vm_phys_t UNUSED(src),
             size_t UNUSED(num_bytes), pos_t UNUSED(file_position),
             struct aio_multihandle *__restrict aio)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	aio_multihandle_done(aio);
}

PRIVATE NONNULL((1, 2, 5)) void KCALL
ramfs_writev(struct inode *__restrict UNUSED(self),
             struct aio_buffer *__restrict UNUSED(buf),
             size_t UNUSED(num_bytes), pos_t UNUSED(file_position),
             struct aio_multihandle *__restrict aio)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	aio_multihandle_done(aio);
}

PRIVATE NONNULL((1, 2, 5)) void KCALL
ramfs_pwritev(struct inode *__restrict UNUSED(self),
              struct aio_pbuffer *__restrict UNUSED(buf),
              size_t UNUSED(num_bytes), pos_t UNUSED(file_position),
              struct aio_multihandle *__restrict aio)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	aio_multihandle_done(aio);
}

PRIVATE NONNULL((1)) void KCALL
ramfs_truncate(struct inode *__restrict UNUSED(self), pos_t UNUSED(new_size))
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION,
		       E_FSERROR_DISK_FULL, E_FSERROR_READONLY,
		       E_IOERROR_BADBOUNDS, E_IOERROR_READONLY,
		       E_IOERROR, ...) {
	/* no-op */
}



PRIVATE NONNULL((1, 2)) REF struct directory_entry *KCALL
ramfs_readdir(struct directory_node *__restrict UNUSED(self),
              pos_t *__restrict UNUSED(pentry_pos))
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	/* Indicate end-of-directory */
	return NULL;
}

PRIVATE NONNULL((1, 2, 3)) void KCALL
ramfs_creat(struct directory_node *__restrict UNUSED(target_directory),
            struct directory_entry *__restrict target_dirent,
            struct regular_node *__restrict new_node)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ILLEGAL_PATH,
		       E_FSERROR_DISK_FULL, E_FSERROR_READONLY,
		       E_IOERROR_BADBOUNDS, E_IOERROR_READONLY,
		       E_IOERROR, ...) {
	target_dirent->de_pos         = (pos_t)(uintptr_t)target_dirent;
	target_dirent->de_ino         = (ino_t)(uintptr_t)new_node;
	new_node->i_fileino           = (ino_t)(uintptr_t)new_node;
	new_node->i_type              = &ramfs_regular_type;
	new_node->i_filemode          = S_IFREG | 0644;
	new_node->i_filenlink         = (nlink_t)1;
	new_node->i_fileuid           = 0;
	new_node->i_filegid           = 0;
	new_node->i_fileatime.tv_sec  = 0; /* TODO: Current time... */
	new_node->i_fileatime.tv_nsec = 0;
	new_node->i_filemtime         = new_node->i_fileatime;
	new_node->i_filectime         = new_node->i_fileatime;
	new_node->i_flags |= (INODE_FATTRLOADED | INODE_FPERSISTENT);
}

PRIVATE NONNULL((1, 2, 3)) void KCALL
ramfs_mkdir(struct directory_node *__restrict UNUSED(target_directory),
            struct directory_entry *__restrict target_dirent,
            struct directory_node *__restrict new_directory)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ILLEGAL_PATH,
		       E_FSERROR_DISK_FULL, E_FSERROR_READONLY,
		       E_IOERROR_BADBOUNDS, E_IOERROR_READONLY,
		       E_IOERROR, ...) {
	target_dirent->de_pos              = (pos_t)(uintptr_t)target_dirent;
	target_dirent->de_ino              = (ino_t)(uintptr_t)new_directory;
	new_directory->i_fileino           = (ino_t)(uintptr_t)new_directory;
	new_directory->i_type              = &ramfs_regular_type;
	new_directory->i_filemode          = S_IFDIR | 0755;
	new_directory->i_filenlink         = (nlink_t)1;
	new_directory->i_fileuid           = 0;
	new_directory->i_filegid           = 0;
	new_directory->i_fileatime.tv_sec  = 0; /* TODO: Current time... */
	new_directory->i_fileatime.tv_nsec = 0;
	new_directory->i_filemtime         = new_directory->i_fileatime;
	new_directory->i_filectime         = new_directory->i_fileatime;
	new_directory->i_flags |= (INODE_FATTRLOADED | INODE_FPERSISTENT | INODE_FDIRLOADED);
}

PRIVATE NONNULL((1, 2, 3)) void KCALL
ramfs_symlink(struct directory_node *__restrict UNUSED(target_directory),
              struct directory_entry *__restrict target_dirent,
              struct symlink_node *__restrict link_node)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ILLEGAL_PATH,
		       E_FSERROR_DISK_FULL, E_FSERROR_READONLY,
		       E_IOERROR_BADBOUNDS, E_IOERROR_READONLY,
		       E_IOERROR, ...) {
	target_dirent->de_pos          = (pos_t)(uintptr_t)target_dirent;
	target_dirent->de_ino          = (ino_t)(uintptr_t)link_node;
	link_node->i_fileino           = (ino_t)(uintptr_t)link_node;
	link_node->i_type              = &ramfs_regular_type;
	link_node->i_filemode          = S_IFLNK | 0777;
	link_node->i_filenlink         = (nlink_t)1;
	link_node->i_fileuid           = 0;
	link_node->i_filegid           = 0;
	link_node->i_fileatime.tv_sec  = 0; /* TODO: Current time... */
	link_node->i_fileatime.tv_nsec = 0;
	link_node->i_filemtime         = link_node->i_fileatime;
	link_node->i_filectime         = link_node->i_fileatime;
	link_node->i_flags |= (INODE_FATTRLOADED | INODE_FPERSISTENT | INODE_FLNKLOADED);
}

PRIVATE NONNULL((1, 2, 3)) void KCALL
ramfs_mknod(struct directory_node *__restrict UNUSED(target_directory),
            struct directory_entry *__restrict target_dirent,
            struct inode *__restrict device_node)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ILLEGAL_PATH,
		       E_FSERROR_DISK_FULL, E_FSERROR_READONLY,
		       E_IOERROR_BADBOUNDS, E_IOERROR_READONLY,
		       E_IOERROR, ...) {
	target_dirent->de_pos  = (pos_t)(uintptr_t)target_dirent;
	target_dirent->de_ino  = (ino_t)(uintptr_t)device_node;
	device_node->i_fileino = (ino_t)(uintptr_t)device_node;
	device_node->i_type    = &ramfs_regular_type;
	device_node->i_filemode |= 0644;
	device_node->i_filenlink         = (nlink_t)1;
	device_node->i_fileuid           = 0;
	device_node->i_filegid           = 0;
	device_node->i_fileatime.tv_sec  = 0; /* TODO: Current time... */
	device_node->i_fileatime.tv_nsec = 0;
	device_node->i_filemtime         = device_node->i_fileatime;
	device_node->i_filectime         = device_node->i_fileatime;
	device_node->i_flags |= (INODE_FATTRLOADED | INODE_FPERSISTENT);
}

PRIVATE NONNULL((1, 2, 3)) void KCALL
ramfs_link(struct directory_node *__restrict UNUSED(target_directory),
           struct directory_entry *__restrict target_dirent,
           struct inode *__restrict link_target)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ILLEGAL_PATH,
		       E_FSERROR_DISK_FULL, E_FSERROR_READONLY,
		       E_FSERROR_TOO_MANY_HARD_LINKS,
		       E_IOERROR_BADBOUNDS, E_IOERROR_READONLY,
		       E_IOERROR, ...) {
	target_dirent->de_pos = (pos_t)(uintptr_t)target_dirent;
	++link_target->i_filenlink;
}

PRIVATE NONNULL((1, 2, 3)) void KCALL
ramfs_unlink(struct directory_node *__restrict UNUSED(containing_directory),
             struct directory_entry *__restrict UNUSED(containing_entry),
             struct inode *__restrict node_to_unlink)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION,
		       E_FSERROR_READONLY, E_IOERROR_READONLY,
		       E_IOERROR, ...) {
	assert(node_to_unlink->i_filenlink != 0);
	/* Just decrement the link counter */
	--node_to_unlink->i_filenlink;
}

PRIVATE NONNULL((1, 2, 3)) void KCALL
ramfs_rmdir(struct directory_node *__restrict containing_directory,
            struct directory_entry *__restrict containing_entry,
            struct directory_node *__restrict node_to_unlink)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION,
		       E_FSERROR_READONLY, E_IOERROR_READONLY,
		       E_IOERROR, ...) {
	ramfs_unlink(containing_directory,
	             containing_entry,
	             node_to_unlink);
}

PRIVATE NONNULL((1)) void KCALL
ramfs_readlink(struct symlink_node *__restrict UNUSED(self))
		THROWS(E_BADALLOC, E_IOERROR, ...) {
	/* This function shouldn't be called */
	THROW(E_FSERROR_UNSUPPORTED_OPERATION,
	      E_FILESYSTEM_OPERATION_SYMLINK);
}




PUBLIC struct inode_type ramfs_dev_type = {
	/* .it_fini = */NULL,
	/* .it_attr = */{
		/* .a_loadattr   = */NULL, /* All nodes are created with attributes already loaded */
		/* .a_saveattr   = */&ramfs_saveattr,
		/* .a_maskattr   = */NULL,
		/* .a_pathconf   = */NULL,
		/* .a_clearcache = */NULL
	},
};
PUBLIC struct inode_type ramfs_regular_type = {
	/* .it_fini = */NULL,
	/* .it_attr = */{
		/* .a_loadattr   = */NULL, /* All nodes are created with attributes already loaded */
		/* .a_saveattr   = */&ramfs_saveattr,
		/* .a_maskattr   = */NULL,
		/* .a_pathconf   = */NULL,
		/* .a_clearcache = */NULL
	},
	/* .it_file = */{
		/* .f_read     = */&ramfs_read,
		/* .f_pread    = */&ramfs_pread,
		/* .f_readv    = */&ramfs_readv,
		/* .f_preadv   = */&ramfs_preadv,
		/* .f_write    = */&ramfs_write,
		/* .f_pwrite   = */&ramfs_pwrite,
		/* .f_writev   = */&ramfs_writev,
		/* .f_pwritev  = */&ramfs_pwritev,
		/* .f_truncate = */&ramfs_truncate,
	},
};

PUBLIC struct inode_type ramfs_directory_type = {
	/* .it_fini = */NULL,
	/* .it_attr = */{
		/* .a_loadattr   = */NULL, /* All nodes are created with attributes already loaded */
		/* .a_saveattr   = */&ramfs_saveattr,
		/* .a_maskattr   = */NULL,
		/* .a_pathconf   = */NULL,
		/* .a_clearcache = */NULL
	},
	/* .it_file = */{ /* NULL... */ },
	{
		/* .it_directory = */{
			/* .d_readdir = */&ramfs_readdir,
			{ NULL },
			/* .d_creat   = */&ramfs_creat,
			/* .d_mkdir   = */&ramfs_mkdir,
			/* .d_symlink = */&ramfs_symlink,
			/* .d_mknod   = */&ramfs_mknod,
			/* .d_link    = */&ramfs_link,
			/* .d_rename  = */NULL, /* Emulated using link() + unlink() */
			/* .d_unlink  = */&ramfs_unlink,
			/* .d_rmdir   = */&ramfs_rmdir,
		}
	}
};

PUBLIC struct inode_type ramfs_symlink_type = {
	/* .it_fini = */NULL,
	/* .it_attr = */{
		/* .a_loadattr   = */NULL, /* All nodes are created with attributes already loaded */
		/* .a_saveattr   = */&ramfs_saveattr,
		/* .a_maskattr   = */NULL,
		/* .a_pathconf   = */NULL,
		/* .a_clearcache = */NULL
	},
	/* .it_file = */{ /* NULL... */ },
	{
		.it_symlink = {
			/* .sl_readlink = */&ramfs_readlink
		}
	}
};

PRIVATE NONNULL((1)) void KCALL
ramfs_open(struct superblock *__restrict self,
           UNCHECKED USER char *UNUSED(args))
		THROWS(E_FSERROR_WRONG_FILE_SYSTEM, E_FSERROR_CORRUPTED_FILE_SYSTEM,
		       E_IOERROR_BADBOUNDS, E_DIVIDE_BY_ZERO, E_OVERFLOW, E_INDEX_ERROR,
		       E_IOERROR, E_SEGFAULT, ...) {
	self->i_type       = &ramfs_directory_type;
	self->db_pageshift = 0;
#ifndef CONFIG_VM_DATABLOCK_MIN_PAGEINFO
	self->db_addrshift = PAGESHIFT;
	self->db_pagealign = 1;
	self->db_pagemask  = 0;
	self->db_pagesize  = pagedir_pagesize();
#endif /* !CONFIG_VM_DATABLOCK_MIN_PAGEINFO */
	self->i_fileino           = (ino_t)(uintptr_t)self;
	self->i_filesize          = 0;
	self->i_filemode          = S_IFDIR | 0755;
	self->i_filenlink         = (nlink_t)1;
	self->i_fileuid           = 0;
	self->i_filegid           = 0;
	self->i_fileatime.tv_sec  = 0; /* TODO: Current time... */
	self->i_fileatime.tv_nsec = 0;
	self->i_filemtime         = self->i_fileatime;
	self->i_filectime         = self->i_fileatime;
	self->i_flags |= INODE_FATTRLOADED;
}

PRIVATE NONNULL((1, 2, 3, 4)) void KCALL
ramfs_opennode(struct superblock *__restrict UNUSED(self),
               struct inode *__restrict UNUSED(node),
               struct directory_node *__restrict UNUSED(parent_directory),
               struct directory_entry *__restrict UNUSED(parent_directory_entry))
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	/* INode are only ever created newly and exist solely in-cache!
	 * This function would be used to open a persistent node stored on-disk,
	 * however such nodes don't exist in a ram-filesystem, so we actually
	 * shouldn't ever get here.
	 * But just to be save, indicate that this operation isn't supported.
	 * NOTE: We can get here if an INode was removed from the superblock,
	 *       but is still referenced by a remaining directory entry! */
	THROW(E_FSERROR_DELETED);
}


PUBLIC struct superblock_type ramfs_type = {
	/* .st_driver            = */&drv_self,
	/* .st_name              = */"ramfs",
	/* .st_flags             = */SUPERBLOCK_TYPE_FNODEV,
	/* .st_sizeof_superblock = */sizeof(struct superblock),
	{
		/* .st_open = */&ramfs_open
	},
	/* .st_functions = */{
		/* .f_fini     = */NULL,
		/* .f_opennode = */&ramfs_opennode,
	}
};

DECL_END

#endif /* !GUARD_KERNEL_CORE_FS_RAMFS_C */
