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
#ifndef GUARD_MODISO9660_ISO9660_C
#define GUARD_MODISO9660_ISO9660_C 1
#define _KOS_SOURCE 1

#include "iso9660.h"

#include <kernel/compiler.h>

#include <dev/block.h>
#include <kernel/aio.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/printk.h>

#include <hybrid/byteorder.h>

#include <linux/magic.h>

#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define GET_LEBE(x) (x##_le)
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define GET_LEBE(x) (x##_be)
#endif

#define INODE_GETADDR(self, pos) \
	(((pos_t)(u32)(uintptr_t)(self)->i_fsdata << (self)->mf_blockshift) + (pos))


/* Read/Write data to/from an iso9660 INode. */
INTERN void KCALL
Iso9660_ReadFromINode(struct inode *__restrict self,
                      CHECKED USER void *buf, size_t bufsize,
                      pos_t pos, struct aio_multihandle *__restrict aio) {
	block_device_aread(self->i_super->s_device,
	                   buf,
	                   bufsize,
	                   INODE_GETADDR(self, pos),
	                   aio_multihandle_allochandle(aio));
}

INTERN void KCALL
Iso9660_ReadFromINodePhys(struct inode *__restrict self,
                          physaddr_t dst, size_t bufsize,
                          pos_t pos, struct aio_multihandle *__restrict aio) {
	block_device_aread_phys(self->i_super->s_device,
	                        dst,
	                        bufsize,
	                        INODE_GETADDR(self, pos),
	                        aio_multihandle_allochandle(aio));
}

INTERN void KCALL
Iso9660_ReadFromINodeVector(struct inode *__restrict self,
                            struct iov_buffer *__restrict buf,
                            size_t bufsize, pos_t pos,
                            struct aio_multihandle *__restrict aio) {
	block_device_areadv(self->i_super->s_device,
	                    buf,
	                    bufsize,
	                    INODE_GETADDR(self, pos),
	                    aio_multihandle_allochandle(aio));
}

INTERN void KCALL
Iso9660_ReadFromINodeVectorPhys(struct inode *__restrict self,
                                struct iov_physbuffer *__restrict buf,
                                size_t bufsize, pos_t pos,
                                struct aio_multihandle *__restrict aio) {
	block_device_areadv_phys(self->i_super->s_device,
	                         buf,
	                         bufsize,
	                         INODE_GETADDR(self, pos),
	                         aio_multihandle_allochandle(aio));
}


INTERN void KCALL
Iso9660INode_LoadAttr(struct inode *__restrict self) {
	byte_t dent_data[offsetafter(DirectoryEntry, de_fileflags)];
	DirectoryEntry *dent = (DirectoryEntry *)dent_data;
	block_device_read(self->i_super->s_device,
	                  dent_data,
	                  sizeof(dent_data),
	                  (pos_t)self->i_fileino);
	self->i_filesize = (pos_t)(u32)GET_LEBE(dent->de_datasiz);
	self->i_filemode = S_IFREG | 0555;
	if (dent->de_fileflags & FILE_FLAG_DIRECTORY)
		self->i_filemode = S_IFDIR | 0555;
	self->i_fsdata    = (struct inode_data *)(uintptr_t)(u32)GET_LEBE(dent->de_datasec);
	self->i_filenlink = (nlink_t)1;
	self->i_fileuid   = self->i_super->i_fileuid;
	self->i_filegid   = self->i_super->i_filegid;
	self->i_fileatime = self->i_super->i_fileatime;
	self->i_filemtime = self->i_super->i_filemtime;
	self->i_filectime = self->i_super->i_filectime;
	self->i_filerdev  = 0;
}

STATIC_ASSERT(sizeof(DirectoryEntry) == 256);
INTERN REF struct directory_entry *KCALL
Iso9660Inode_ReadDir(struct directory_node *__restrict self,
                     pos_t *__restrict pentry_pos) {
	DirectoryEntry ent;
	pos_t entry_pos;
	REF struct directory_entry *result;
	entry_pos = *pentry_pos;
	inode_loadattr(self);
again:
	if (entry_pos >= self->i_filesize)
		return NULL; /* End of directory */
	/* Read the next directory entry. */
	block_device_read(self->i_super->s_device, &ent, 256,
	                  INODE_GETADDR(self, entry_pos));
	if (ent.de_length == 0)
		return NULL; /* End of directory */
	if unlikely(ent.de_namelen > 223)
		ent.de_namelen = 223;
	ent.de_namelen = strnlen(ent.de_name, ent.de_namelen);
	if (ent.de_namelen == 0 ||                            /* Directory self-reference */
	   (ent.de_namelen == 1 && ent.de_name[0] == '\1')) { /* Parent-directory reference */
		entry_pos += ent.de_length;
		goto again;
	}
	result = directory_entry_alloc(ent.de_namelen);
	result->de_pos                        = entry_pos;
	result->de_ino                        = (ino_t)entry_pos; /* INO == Address of directory entry. */
	result->de_type                       = DT_REG;
	*(u32 *)&result->de_fsdata.de_data[0] = (u32)GET_LEBE(ent.de_datasec);
	*(u32 *)&result->de_fsdata.de_data[4] = (u32)GET_LEBE(ent.de_datasiz);
	if (ent.de_fileflags & FILE_FLAG_DIRECTORY)
		result->de_type = DT_DIR;
	memcpy(result->de_name, ent.de_name, ent.de_namelen, sizeof(char));

	/* Ensure NUL-termination, and generate the hash. */
	result->de_hash = directory_entry_hash(result->de_name,
	                                       ent.de_namelen);

	entry_pos += ent.de_length;
	*pentry_pos = entry_pos;
	return result;
}

INTERN void KCALL
Iso9660_OpenINode(Iso9660Superblock *__restrict self,
                  struct inode *__restrict node,
                  struct directory_node *__restrict UNUSED(parent_directory),
                  struct directory_entry *__restrict parent_directory_entry)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	/* Load INode attributes from fs-specific directory entry data. */
	node->i_filesize  = (pos_t)(*(u32 const *)&parent_directory_entry->de_fsdata.de_data[4]);
	node->i_fsdata    = (struct inode_data *)(uintptr_t)(*(u32 const *)&parent_directory_entry->de_fsdata.de_data[0]);
	node->i_filenlink = (nlink_t)1;
	node->i_fileuid   = self->i_fileuid;
	node->i_filegid   = self->i_filegid;
	node->i_fileatime = self->i_fileatime;
	node->i_filemtime = self->i_filemtime;
	node->i_filectime = self->i_filectime;
	node->i_filerdev  = 0;
	node->i_flags |= INODE_FATTRLOADED;
	switch (node->i_filemode & S_IFMT) {

	case S_IFDIR:
		node->i_type = &Iso9660_DirType;
		break;

	case S_IFREG:
		node->i_type = &Iso9660_RegType;
		break;

	default:
		/* Throw an unsupported-function error for any other type of node. */
		THROW(E_FSERROR_UNSUPPORTED_OPERATION);
	}
}

PRIVATE NONNULL((1)) void KCALL
Iso9660_StatFs(Iso9660Superblock *__restrict self,
               USER CHECKED struct statfs *result)
		THROWS(E_IOERROR, E_SEGFAULT, ...) {
	(void)self;
	(void)result;
	THROW(E_NOT_IMPLEMENTED_TODO);
}




INTERN struct inode_type Iso9660_RegType = {
	/*.it_fini = */ NULL,
	/*.it_attr = */ {
		/*.a_loadattr   = */ &Iso9660INode_LoadAttr,
		/*.a_saveattr   = */ NULL,
		/*.a_maskattr   = */ NULL,
		/*.a_clearcache = */ NULL,
	},
	/*.it_file = */ {
		/*.f_read     = */ &Iso9660_ReadFromINode,
		/*.f_pread    = */ &Iso9660_ReadFromINodePhys,
		/*.f_readv    = */ &Iso9660_ReadFromINodeVector,
		/*.f_preadv   = */ &Iso9660_ReadFromINodeVectorPhys,
		/*.f_write    = */ NULL,
		/*.f_pwrite   = */ NULL,
		/*.f_writev   = */ NULL,
		/*.f_pwritev  = */ NULL,
		/*.f_truncate = */ NULL,
	}
};
INTERN struct inode_type Iso9660_DirType = {
	/*.it_fini = */ NULL,
	/*.it_attr = */ {
		/*.a_loadattr   = */ &Iso9660INode_LoadAttr,
		/*.a_saveattr   = */ NULL,
		/*.a_maskattr   = */ NULL,
		/*.a_clearcache = */ NULL,
	},
	/*.it_file = */ {
		/*.f_read     = */ NULL,
		/*.f_pread    = */ NULL,
		/*.f_readv    = */ NULL,
		/*.f_preadv   = */ NULL,
		/*.f_write    = */ NULL,
		/*.f_pwrite   = */ NULL,
		/*.f_writev   = */ NULL,
		/*.f_pwritev  = */ NULL,
		/*.f_truncate = */ NULL,
	},
	{
		/*.it_directory = */ {
			/*.d_readdir = */ &Iso9660Inode_ReadDir,
			{ NULL },
			/*.d_creat   = */ NULL,
			/*.d_mkdir   = */ NULL,
			/*.d_symlink = */ NULL,
			/*.d_mknod   = */ NULL,
			/*.d_link    = */ NULL,
			/*.d_rename  = */ NULL,
			/*.d_unlink  = */ NULL,
			/*.d_rmdir   = */ NULL,
		}
	}
};


INTERN void KCALL
Iso9660_OpenSuperblock(Iso9660Superblock *__restrict self, UNCHECKED USER char *args)
		THROWS(E_FSERROR_WRONG_FILE_SYSTEM, E_FSERROR_CORRUPTED_FILE_SYSTEM,
		       E_IOERROR_BADBOUNDS, E_DIVIDE_BY_ZERO, E_OVERFLOW, E_INDEX_ERROR,
		       E_IOERROR, E_SEGFAULT, ...) {
	VolumeDescriptor volume;
	pos_t offset               = (pos_t)0x8000;
	pos_t second_volume_offset = (pos_t)-1;
	self->s_features.sf_magic = ISOFS_SUPER_MAGIC;
	/* XXX: Mount arguments for iso9660? */
	(void)args;

	/* Search for the `VOLUME_DESCRIPTOR_TYPE_PRIMARY_VOLUME' descriptor. */
	for (;;) {
		block_device_read(self->s_device, &volume, sizeof(volume), offset);
		if (volume.vd_ident[0] != 'C' || volume.vd_ident[1] != 'D' ||
		    volume.vd_ident[2] != '0' || volume.vd_ident[3] != '0' ||
		    volume.vd_ident[4] != '1' || volume.vd_version != 0x01)
			THROW(E_FSERROR_WRONG_FILE_SYSTEM); /* Not an iso9660 filesystem */
		if (volume.vd_type == VOLUME_DESCRIPTOR_TYPE_EOF) {
			if (second_volume_offset != (pos_t)-1) {
				/* Fallback to using the second volume. */
				offset = second_volume_offset;
				block_device_read(self->s_device,
				                  &volume,
				                  sizeof(volume),
				                  offset);
				break;
			}
			THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM); /* There's no primary volume descriptor... */
		}
		if (volume.vd_type == VOLUME_DESCRIPTOR_TYPE_PRIMARY_VOLUME)
			break; /* Found it! */
		if (volume.vd_type == VOLUME_DESCRIPTOR_TYPE_SUPPLEMENTARY_VOLUME &&
		    second_volume_offset == (pos_t)-1)
			second_volume_offset = offset;
		offset += ISO9660_SECTOR_SIZE;
	}
#if 0 /* Better not assert this. - It doesn't matter, and I may have misunderstood how this works... */
	if ((u16)GET_LEBE(volume.vd_prim_volume.pv_volumeset_id) >=
	    (u16)GET_LEBE(volume.vd_prim_volume.pv_volumeset_sz))
		THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);
#endif
	if (volume.vd_prim_volume.pv_fs_version != 0x01)
		THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);

	{
		u32 sector_size;
		unsigned int block_shift;
		sector_size = (u32)GET_LEBE(volume.vd_prim_volume.pv_sectorsize);
		switch (sector_size) {
		case 1: block_shift = 0; break;
		case 2: block_shift = 1; break;
		case 4: block_shift = 2; break;
		case 8: block_shift = 3; break;
		case 16: block_shift = 4; break;
		case 32: block_shift = 5; break;
		case 64: block_shift = 6; break;
		case 128: block_shift = 7; break;
		case 256: block_shift = 8; break;
		case 512: block_shift = 9; break;
		case 1024: block_shift = 10; break;
		case 2048: block_shift = 11; break;
		case 4096: block_shift = 12; break;
		default: THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);
		}
		_mfile_init_blockshift(self, block_shift);
	}
	{
		DirectoryEntry *root;
		root = (DirectoryEntry *)volume.vd_prim_volume.pv_rootdir;
		if unlikely(!(root->de_fileflags & FILE_FLAG_DIRECTORY))
			THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM); /* It has to be a root _DIRECTORY_ */
		/* Similar to FAT, we use the address of the directory entry as Inode */
		self->i_fileino  = (ino_t)offset + offsetof(VolumeDescriptor, vd_prim_volume.pv_rootdir);
		self->i_filesize = (pos_t)(u32)GET_LEBE(root->de_datasiz);
		self->i_fsdata   = (struct inode_data *)(uintptr_t)(u32)GET_LEBE(root->de_datasec);
		self->i_filemode = S_IFDIR | 0555; /* Execute+read permissions */
	}
	/* TODO: Decode this information from the volume descriptor:
	 *   - volume.vd_prim_volume.pv_creation_time
	 *   - volume.vd_prim_volume.pv_modification_time */
	self->i_filectime.tv_sec  = 0;
	self->i_filectime.tv_nsec = 0;
	self->i_filemtime.tv_sec  = 0;
	self->i_filemtime.tv_nsec = 0;
	self->i_fileatime.tv_sec  = 0; /* TODO: Set current time */
	self->i_fileatime.tv_nsec = 0; /* TODO: Set current time */
	self->i_filenlink         = (nlink_t)1;
	self->i_filerdev          = (dev_t)0;
	self->i_flags |= INODE_FATTRLOADED; /* Indicate that attributes have been loaded. */
	self->i_fileuid = 0;                /* ??? */
	self->i_filegid = 0;                /* ??? */
	/* Set the directory type */
	self->i_type = &Iso9660_DirType;
}


INTERN struct superblock_type Iso9660_SuperblockType = {
	/* .st_driver            = */ &drv_self,
	/* .st_name              = */ "iso9660",
	/* .st_flags             = */ SUPERBLOCK_TYPE_FNORMAL,
	/* .st_sizeof_superblock = */ sizeof(Iso9660Superblock),
	{
		/* .st_open = */ (void(KCALL *)(struct superblock *__restrict, UNCHECKED USER char *))&Iso9660_OpenSuperblock
	},
	/* .st_functions = */ {
		/* .f_fini     = */ NULL,
		/* .f_opennode = */ (void(KCALL *)(struct superblock *__restrict, struct inode *__restrict, struct directory_node *__restrict, struct directory_entry *__restrict))&Iso9660_OpenINode,
		/* .f_statfs   = */ (void(KCALL *)(struct superblock *__restrict, USER CHECKED struct statfs *))&Iso9660_StatFs,
		/* .f_sync     = */ NULL
	}
};

PRIVATE ATTR_FREETEXT DRIVER_INIT void init(void) {
	register_filesystem_type(&Iso9660_SuperblockType);
}

PRIVATE DRIVER_FINI void fini(void) {
	unregister_filesystem_type(&Iso9660_SuperblockType);
}

DECL_END

#endif /* !GUARD_MODISO9660_ISO9660_C */
