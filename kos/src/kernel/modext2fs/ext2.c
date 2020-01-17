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
#ifndef GUARD_MODEXT2FS_EXT2_C
#define GUARD_MODEXT2FS_EXT2_C 1
#define _KOS_SOURCE 1

#include "ext2.h"

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/printk.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/byteorder.h>
#include <hybrid/byteswap.h>

#include <bits/confname.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN


INTERN void KCALL
Ext2_VReadFromINode(struct inode *__restrict self,
                    CHECKED USER void *buf,
                    size_t bufsize, pos_t pos) {
	(void)self;
	(void)buf;
	(void)bufsize;
	(void)pos;
	THROW(E_NOT_IMPLEMENTED_TODO);
}

INTERN void KCALL
Ext2_VWriteToINode(struct inode *__restrict self,
                   CHECKED USER void const *buf,
                   size_t bufsize, pos_t pos) {
	(void)self;
	(void)buf;
	(void)bufsize;
	(void)pos;
	COMPILER_IMPURE();
	THROW(E_NOT_IMPLEMENTED_TODO);
}

INTERN void KCALL
Ext2_ReadFromINode(struct inode *__restrict self,
                   CHECKED USER void *buf, size_t bufsize,
                   pos_t pos, struct aio_multihandle *__restrict aio) {
	(void)self;
	(void)buf;
	(void)bufsize;
	(void)pos;
	(void)aio;
	COMPILER_IMPURE();
	THROW(E_NOT_IMPLEMENTED_TODO);
}

INTERN void KCALL
Ext2_WriteToINode(struct inode *__restrict self,
                  CHECKED USER void const *buf, size_t bufsize,
                  pos_t pos, struct aio_multihandle *__restrict aio) {
	(void)self;
	(void)buf;
	(void)bufsize;
	(void)pos;
	(void)aio;
	COMPILER_IMPURE();
	THROW(E_NOT_IMPLEMENTED_TODO);
}

INTERN void KCALL
Ext2_ReadFromINodePhys(struct inode *__restrict self,
                       vm_phys_t dst, size_t bufsize,
                       pos_t pos, struct aio_multihandle *__restrict aio) {
	(void)self;
	(void)dst;
	(void)bufsize;
	(void)pos;
	(void)aio;
	COMPILER_IMPURE();
	THROW(E_NOT_IMPLEMENTED_TODO);
}

INTERN void KCALL
Ext2_WriteToINodePhys(struct inode *__restrict self,
                      vm_phys_t src, size_t bufsize,
                      pos_t pos, struct aio_multihandle *__restrict aio) {
	(void)self;
	(void)src;
	(void)bufsize;
	(void)pos;
	(void)aio;
	COMPILER_IMPURE();
	THROW(E_NOT_IMPLEMENTED_TODO);
}

INTERN void KCALL
Ext2_ReadFromINodeVector(struct inode *__restrict self,
                         struct aio_buffer *__restrict buf, size_t bufsize,
                         pos_t pos, struct aio_multihandle *__restrict aio) {
	(void)self;
	(void)buf;
	(void)bufsize;
	(void)pos;
	(void)aio;
	COMPILER_IMPURE();
	THROW(E_NOT_IMPLEMENTED_TODO);
}

INTERN void KCALL
Ext2_WriteToINodeVector(struct inode *__restrict self,
                        struct aio_buffer *__restrict buf, size_t bufsize,
                        pos_t pos, struct aio_multihandle *__restrict aio) {
	(void)self;
	(void)buf;
	(void)bufsize;
	(void)pos;
	(void)aio;
	COMPILER_IMPURE();
	THROW(E_NOT_IMPLEMENTED_TODO);
}

INTERN void KCALL
Ext2_ReadFromINodeVectorPhys(struct inode *__restrict self,
                             struct aio_pbuffer *__restrict buf, size_t bufsize,
                             pos_t pos, struct aio_multihandle *__restrict aio) {
	(void)self;
	(void)buf;
	(void)bufsize;
	(void)pos;
	(void)aio;
	COMPILER_IMPURE();
	THROW(E_NOT_IMPLEMENTED_TODO);
}

INTERN void KCALL
Ext2_WriteToINodeVectorPhys(struct inode *__restrict self,
                            struct aio_pbuffer *__restrict buf, size_t bufsize,
                            pos_t pos, struct aio_multihandle *__restrict aio) {
	(void)self;
	(void)buf;
	(void)bufsize;
	(void)pos;
	(void)aio;
	COMPILER_IMPURE();
	THROW(E_NOT_IMPLEMENTED_TODO);
}




/* Return a pointer to (and lazily initialize) the block group
 * associated with the given `index'.
 * @assume(index < self->sd_bgroups_cnt); */
INTERN ATTR_RETNONNULL WUNUSED Ext2BlockGroup *KCALL
Ext2_Group(Ext2Superblock *__restrict self, ext2_bgroup_t index)
		THROWS(E_IOERROR, E_BADALLOC, E_WOULDBLOCK, E_INTERRUPT) {
	Ext2BlockGroup *result;
	assert(index < self->sd_bgroups_cnt);
	result = &self->sd_groups[index];
	if (!(ATOMIC_READ(result->bg_flags) & BLOCK_GROUP_FLOADED)) {
		Ext2DiskBlockGroup group;
		block_device_read(self->s_device, &group, sizeof(group),
		                  self->sd_bgroups_pos + (index * EXT2_BLOCKGROUP_SIZE));
		sync_write(&result->bg_lock);
		COMPILER_READ_BARRIER();
		if likely(!(ATOMIC_READ(result->bg_flags) & BLOCK_GROUP_FLOADED)) {
			assert(!result->bg_busage);
			assert(!result->bg_iusage);
			/* Fill in the block groups data fields. */
			result->bg_busage_addr = LESWAP32(group.bg_busage);
			result->bg_iusage_addr = LESWAP32(group.bg_iusage);
			result->bg_inodes      = LESWAP32(group.bg_inodes);
			result->bg_free_blocks = LESWAP16(group.bg_free_blocks);
			result->bg_free_inodes = LESWAP16(group.bg_free_inodes);
			result->bg_num_dirs    = LESWAP16(group.bg_num_dirs);
			result->bg_flags |= BLOCK_GROUP_FLOADED;
		}
		sync_endwrite(&result->bg_lock);
	}
	return result;
}

/* Return the absolute on-disk position of the `Ext2DiskINode'
 * structure used to store descriptor data for the given `ino'. */
INTERN WUNUSED pos_t KCALL
Ext2_InoAddr(Ext2Superblock *__restrict self, ext2_ino_t ino)
		THROWS(E_IOERROR_BADBOUNDS, E_IOERROR, E_BADALLOC, E_WOULDBLOCK, E_INTERRUPT) {
	Ext2BlockGroup *block; pos_t result;
	ext2_bgroup_t group; ext2_ino_t offset;
	if unlikely(ino < 1 || ino > self->sd_total_inodes)
		THROW(E_IOERROR_BADBOUNDS);
	group   = EXT2_INO_BGRP_INDEX(self, ino);
	offset  = EXT2_INO_BGRP_OFFSET(self, ino);
	block   = Ext2_Group(self, group);
	result  = EXT2_BLOCK2ADDR(self, block->bg_inodes);
	result += offset * self->sd_inode_size;
	return result;
}

#ifndef __INTELLISENSE__
STATIC_ASSERT(sizeof(Ext2DiskINode) == 128);
#endif /* !__INTELLISENSE__ */

/* Read the descriptor for the given `ino' from disk */
INTERN void KCALL
Ext2_ReadINodeDiskDescriptor(Ext2Superblock *__restrict self, ext2_ino_t ino,
                             Ext2DiskINode *__restrict buf)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	pos_t addr;
	addr = Ext2_InoAddr(self, ino);
	block_device_read(self->s_device, buf, 128, addr);
}

/* Write the descriptor for the given `ino' to disk */
INTERN void KCALL
Ext2_WriteINodeDiskDescriptor(Ext2Superblock *__restrict self, ext2_ino_t ino,
                              Ext2DiskINode const *__restrict buf)
		THROWS(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC, ...) {
	pos_t addr;
	addr = Ext2_InoAddr(self, ino);
	block_device_write(self->s_device, buf, 128, addr);
}

INTERN void KCALL
ExtINode_LoadAttr(struct inode *__restrict self) {
	Ext2DiskINode data;
	Ext2Superblock *super;
	struct inode_data *node;
	unsigned int i; mode_t real_mode;
	super = (Ext2Superblock *)self->i_super;
	Ext2_ReadINodeDiskDescriptor(super, (ext2_ino_t)self->i_fileino, &data);
	if ((node = self->i_fsdata) == NULL) {
		/* Lazily allocate INode-specific data. */
		node = (struct inode_data *)kmalloc(sizeof(struct inode_data),
		                                    FS_GFP | GFP_CALLOC);
		self->i_fsdata = node;
	}
	assert(!node->i_siblock);
	assert(!node->i_diblock);
	assert(!node->i_tiblock);
	/* Copy unused, but cached fields. */
	node->i_dtime      = data.i_dtime;
	node->i_flags      = data.i_flags;
	node->i_os1        = data.i_os1;
	node->i_generation = data.i_generation;
	node->i_acl        = data.i_acl;
	node->i_fragment   = data.i_fragment;
	node->i_os2[0]     = data.i_os2[0];
	node->i_os2[1]     = data.i_os2[1];
	node->i_os2[2]     = data.i_os2[2];
	/* Copy block pointers. */
	for (i = 0; i < EXT2_DIRECT_BLOCK_COUNT; ++i)
		node->i_dblock[i] = LESWAP32(data.i_dblock[i]);
	node->i_siblock_addr = LESWAP32(data.i_siblock);
	node->i_diblock_addr = LESWAP32(data.i_diblock);
	node->i_tiblock_addr = LESWAP32(data.i_tiblock);
	/* Read general-purpose INode attributes. */
	self->i_filenlink = (nlink_t)LESWAP16(data.i_nlink);
	real_mode         = LESWAP16(data.i_mode);
	/* Race condition: The file got deleted and another node with the
	 *                 same ID, but of a different type may have been
	 *                 created in the mean time.
	 *                 Handle this case by acting as though the file
	 *                 had been deleted.
	 * (XXX: This really shouldn't have happened though, unless user-space
	 *       has manually been writing to the underlying partitions, because
	 *       otherwise the file should still be of the same type, as an
	 *       API call going through the kernel would have marked our INode
	 *       as deleted, meaning that there'd be no situation where its
	 *       attributes could still be loadable... At least I think there
	 *       isn't a way, although this behavior might be allowed?)
	 *       Anyways: Just handle miss-matching INode types as missing files. */
	if ((self->i_filemode & S_IFMT) != (real_mode & S_IFMT))
		THROW(E_FSERROR_FILE_NOT_FOUND);
	self->i_filemode          = real_mode;
	self->i_fileuid           = (uid_t)LESWAP16(data.i_uid);
	self->i_filegid           = (gid_t)LESWAP16(data.i_gid);
	self->i_filesize          = (pos_t)LESWAP32(data.i_size_low);
	self->i_fileatime.tv_sec  = LESWAP32(data.i_atime);
	self->i_fileatime.tv_nsec = 0;
	self->i_filemtime.tv_sec  = LESWAP32(data.i_mtime);
	self->i_filemtime.tv_nsec = 0;
	self->i_filectime.tv_sec  = LESWAP32(data.i_ctime);
	self->i_filectime.tv_nsec = 0;
	node->i_block_count       = LESWAP32(data.i_blocks);

	/* Parse Version-specific fields. */
	if (super->sd_feat_mountro & EXT2_FEAT_MRO_FSIZE64)
		self->i_filesize |= (pos_t)((u64)LESWAP32(data.i_size_high) << 32);
	/* Parse OS-specific fields. */
	switch (super->sd_os) {

	case EXT2_OS_FGNU_HURD:
		self->i_filemode |= LESWAP16(data.i_os_hurd.h_mode_high) << 16;
		/* Linux-specific fields are also implemented by HURD, so just fallthrough */
		ATTR_FALLTHROUGH
	case EXT2_OS_FLINUX:
		self->i_fileuid |= LESWAP16(data.i_os_linux.l_uid_high) << 16;
		self->i_filegid |= LESWAP16(data.i_os_linux.l_gid_high) << 16;
		break;

	default: break;
	}
}

INTERN void KCALL
ExtINode_SaveAttr(struct inode *__restrict self) {
	Ext2DiskINode data;
	unsigned int i;
	Ext2Superblock *super;
	struct inode_data *node = self->i_fsdata;
	assert(node != NULL);
	/* Copy unused, but cached fields. */
	data.i_dtime      = node->i_dtime;
	data.i_flags      = node->i_flags;
	data.i_os1        = node->i_os1;
	data.i_generation = node->i_generation;
	data.i_acl        = node->i_acl;
	data.i_fragment   = node->i_fragment;
	data.i_os2[0]     = node->i_os2[0];
	data.i_os2[1]     = node->i_os2[1];
	data.i_os2[2]     = node->i_os2[2];
	/* Copy block pointers. */
	for (i = 0; i < EXT2_DIRECT_BLOCK_COUNT; ++i)
		data.i_dblock[i] = (le32)LESWAP32((u32)node->i_dblock[i]);
	data.i_siblock = (le32)LESWAP32((u32)node->i_siblock_addr);
	data.i_diblock = (le32)LESWAP32((u32)node->i_diblock_addr);
	data.i_tiblock = (le32)LESWAP32((u32)node->i_tiblock_addr);
	/* Write general-purpose INode attributes. */
	data.i_nlink    = (le16)LESWAP16((u16)self->i_filenlink);
	data.i_mode     = (le16)LESWAP16((u16)self->i_filemode);
	data.i_uid      = (le16)LESWAP16((u16)self->i_fileuid);
	data.i_gid      = (le16)LESWAP16((u16)self->i_filegid);
	data.i_size_low = (le32)LESWAP32((u32)self->i_filesize);
	data.i_atime    = (le32)LESWAP32((u32)self->i_fileatime.tv_sec);
	data.i_mtime    = (le32)LESWAP32((u32)self->i_filemtime.tv_sec);
	data.i_ctime    = (le32)LESWAP32((u32)self->i_filectime.tv_sec);
	data.i_blocks   = (le32)LESWAP32((u32)node->i_block_count);

	super = (Ext2Superblock *)self->i_super;

	/* Parse Version-specific fields. */
	if (super->sd_feat_mountro & EXT2_FEAT_MRO_FSIZE64)
		data.i_size_high = (le32)LESWAP32((u32)(self->i_filesize >> 32));
	else
		data.i_size_high = (le32)0;

	/* Encode OS-specific fields. */
	switch (super->sd_os) {

	case EXT2_OS_FGNU_HURD:
		data.i_os_hurd.h_mode_high = (le16)LESWAP16((u16)(self->i_filemode >> 16));
		/* Linux-specific fields are also implemented by HURD, so just fallthrough */
		ATTR_FALLTHROUGH
	case EXT2_OS_FLINUX:
		data.i_os_linux.l_uid_high = (le16)LESWAP16((u16)(self->i_fileuid >> 16));
		data.i_os_linux.l_gid_high = (le16)LESWAP16((u16)(self->i_filegid >> 16));
		break;

	default: break;
	}

	/* Write the new INode descriptor to disk. */
	Ext2_WriteINodeDiskDescriptor(super,
	                             (ext2_ino_t)self->i_fileino,
	                             &data);
}



PRIVATE void KCALL
free_x2_table(struct block_table_x2 *__restrict self, size_t size) {
	size_t i;
	assert(self->b2_tables);
	for (i = 0; i < size; ++i)
		kfree(self->b2_tables[i]);
	kfree(self->b2_tables);
	kfree(self);
}

PRIVATE void KCALL
free_x3_table(struct block_table_x3 *__restrict self, size_t size) {
	size_t i;
	assert(self->b3_tables);
	for (i = 0; i < size; ++i) {
		if (self->b3_tables[i])
			free_x2_table(self->b3_tables[i], size);
	}
	kfree(self->b3_tables);
	kfree(self);
}

PRIVATE void KCALL
ExtINode_Fini(struct inode *__restrict self) {
	struct inode_data *node;
	node = self->i_fsdata;
	if (node) {
		kfree(node->i_siblock);
		if (node->i_diblock)
			free_x2_table(node->i_diblock, ((Ext2Superblock *)self->i_super)->sd_ind_blocksize);
		if (node->i_tiblock)
			free_x3_table(node->i_tiblock, ((Ext2Superblock *)self->i_super)->sd_ind_blocksize);
		kfree(node);
	}
}

INTERN REF struct directory_entry *KCALL
ExtDir_ReadDir(struct directory_node *__restrict self,
               pos_t *__restrict pentry_pos) {
	Ext2DiskDirent entry;
	u16 entsize, namlen;
	REF struct directory_entry *result;
	unsigned char entry_type;
	pos_t entry_pos;
	inode_loadattr(self);
again:
	entry_pos = *pentry_pos;
	Ext2_VReadFromINode(self, &entry, sizeof(Ext2DiskDirent), entry_pos);
	entsize = LESWAP16(entry.d_entsize);
	if (entsize <= sizeof(Ext2DiskDirent))
		return NULL; /* End of directory */
	*pentry_pos += entsize;
	if (!entry.d_ino)
		goto again; /* Unused entry. */
	if (((Ext2Superblock *)self->i_super)->sd_feat_required & EXT2_FEAT_REQ_FDIRENT_TYPE) {
		entry_type = entry.d_type;
		namlen     = entry.d_namlen_low;
		if ((entsize - sizeof(Ext2DiskDirent)) > 0xff) {
			/* The filename is longer than 255 characters, and
			 * we only have the least significant 8 bits of its
			 * actual length.
			 * To deal with this, we must scan ahead and read a byte at every
			 * `entry_pos + sizeof(Ext2Dirent) + entry.d_namlen_low + N * 256'
			 * that is still located below `entry_pos + entsize' until we find
			 * a NUL-character. */
			pos_t name_endpos, name_endpos_max;
			name_endpos = entry_pos;
			name_endpos += sizeof(Ext2DiskDirent);
			name_endpos += entry.d_namlen_low;
			name_endpos += 256 * sizeof(char);
			name_endpos_max = entry_pos;
			name_endpos_max += entsize;
			while (name_endpos < name_endpos_max) {
				char ch;
				Ext2_VReadFromINode(self, &ch, sizeof(char), name_endpos);
				if (!ch)
					break;
				name_endpos += 256 * sizeof(char);
			}
			namlen = (u16)((name_endpos - sizeof(Ext2DiskDirent)) - entry_pos) / sizeof(char);
		}
	} else {
		pos_t ino_addr;
		le16 ino_type;
		ino_addr = Ext2_InoAddr((Ext2Superblock *)self->i_super,
		                        LESWAP32(entry.d_ino));
		/* Read the directory entry type from its INode. */
		block_device_read(self->i_super->s_device, &ino_type, 2,
		                  ino_addr + offsetof(Ext2DiskINode, i_mode));
		entry_type = IFTODT(LESWAP16(ino_type));
		namlen     = LESWAP16(entry.d_namlen);
	}
	/* Construct the resulting directory entry. */
	result = directory_entry_alloc(namlen);
	TRY {
		result->de_pos  = entry_pos;
		result->de_ino  = (ino_t)LESWAP32(entry.d_ino);
		result->de_type = entry_type;
		/* Read in the directory entry's name. */
		Ext2_VReadFromINode(self,
		                    result->de_name,
		                    namlen * sizeof(char),
		                    entry_pos + sizeof(Ext2DiskDirent));
		switch (namlen) {
		case 2:
			if (result->de_name[1] != '.')
				break;
			ATTR_FALLTHROUGH
		case 1:
			if (result->de_name[0] != '.')
				break;
			/* Skip `.' and `..' -- Those are emulated by the VFS layer. */
			kfree(result);
			goto again;
		default: break;
		}

		/* Ensure NUL-termination, and generate the hash. */
		result->de_hash = directory_entry_hash(result->de_name,
		                                       namlen);
	} EXCEPT {
		kfree(result);
		RETHROW();
	}
	return result;
}

INTERN void KCALL
Ext2_ReadSymLink(struct symlink_node *__restrict self) {
	char *text;
	size_t textlen;
	/* Make sure that INode attributes have been loaded.
	 * -> Required for the `a_size' field. */
	inode_loadattr(self);
	textlen = (size_t)self->i_filesize;
	text    = (char *)kmalloc(textlen * sizeof(char), FS_GFP);
	TRY {
		struct inode_data *node;
		node = self->i_fsdata;
#if 0 /* XXX: ASCII data is usually written in a way that causes this check to succeed, \
       *      but what about 1 or 2-character links? This is little endian after all,   \
       *      so that would end up with a really small number that might be lower       \
       *      that the actual number block blocks...                                    \
       * LATER: From what little I can gather, at some point Ext2 just started placing  \
       *        symlink data that was small enough within the INode itself.             \
       *        Although sources state that prior to this data was written in actual    \
       *        blocks, what isn't stated is anything about how to differentiate        \
       *        these two cases other than the link size (which is ambiguous for small
       *        links). */
		if (textlen * sizeof(char) <= (EXT2_DIRECT_BLOCK_COUNT + 3) * 4 &&
		    node->i_dblock[0] >= ((Ext2Superblock *)self->i_super)->sd_total_blocks)
#else
		if (textlen * sizeof(char) <= (EXT2_DIRECT_BLOCK_COUNT + 3) * 4)
#endif
		{
			/* XXX: Is this really how we discern between the 2 methods?
			 *      Shouldn't there be some kind of flag somewhere? */
			memcpy(text, &node->i_dblock, textlen, sizeof(char));
		} else {
			/* Read the symlink text. */
			Ext2_VReadFromINode(self, text, textlen, 0);
		}
		/* Save the symlink text in its designated location. */
		self->sl_text = text;
	} EXCEPT {
		kfree(text);
		RETHROW();
	}
}


INTERN struct inode_type Ext2_DirOps = {
	/*.it_fini = */ &ExtINode_Fini,
	/*.it_attr = */ {
		/*.a_loadattr   = */ &ExtINode_LoadAttr,
		/*.a_saveattr   = */ &ExtINode_SaveAttr,
		/*.a_maskattr   = */ NULL,
		/*.a_pathconf   = */ NULL,
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
			/*.d_readdir = */ &ExtDir_ReadDir,
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

INTERN struct inode_type Ext2_RegOps = {
	/*.it_fini = */ &ExtINode_Fini,
	/*.it_attr = */ {
		/*.a_loadattr   = */ &ExtINode_LoadAttr,
		/*.a_saveattr   = */ &ExtINode_SaveAttr,
		/*.a_maskattr   = */ NULL,
		/*.a_pathconf   = */ NULL,
		/*.a_clearcache = */ NULL,
	},
	/*.it_file = */ {
		/*.f_read     = */ &Ext2_ReadFromINode,
		/*.f_pread    = */ &Ext2_ReadFromINodePhys,
		/*.f_readv    = */ &Ext2_ReadFromINodeVector,
		/*.f_preadv   = */ &Ext2_ReadFromINodeVectorPhys,
		/*.f_write    = */ &Ext2_WriteToINode,
		/*.f_pwrite   = */ &Ext2_WriteToINodePhys,
		/*.f_writev   = */ &Ext2_WriteToINodeVector,
		/*.f_pwritev  = */ &Ext2_WriteToINodeVectorPhys,
		/*.f_truncate = */ NULL,
	}
};
INTERN struct inode_type Ext2_DevOps = {
	/*.it_fini = */ &ExtINode_Fini,
	/*.it_attr = */ {
		/*.a_loadattr   = */ &ExtINode_LoadAttr,
		/*.a_saveattr   = */ &ExtINode_SaveAttr,
		/*.a_maskattr   = */ NULL,
		/*.a_pathconf   = */ NULL,
		/*.a_clearcache = */ NULL,
	}
};
INTERN struct inode_type Ext2_LnkOps = {
	/*.it_fini = */ &ExtINode_Fini,
	/*.it_attr = */ {
		/*.a_loadattr   = */ &ExtINode_LoadAttr,
		/*.a_saveattr   = */ &ExtINode_SaveAttr,
		/*.a_maskattr   = */ NULL,
		/*.a_pathconf   = */ NULL,
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
		.it_symlink = {
			/*.sl_readlink = */ &Ext2_ReadSymLink,
		}
	}
};




INTERN void KCALL
Ext2_OpenSuperblock(Ext2Superblock *__restrict self, UNCHECKED USER char *args)
		THROWS(E_FSERROR_WRONG_FILE_SYSTEM, E_FSERROR_CORRUPTED_FILE_SYSTEM,
		       E_IOERROR_BADBOUNDS, E_DIVIDE_BY_ZERO, E_OVERFLOW, E_INDEX_ERROR,
		       E_IOERROR, E_SEGFAULT, ...) {
	Ext2DiskSuperblock super;
	u32 num_block_groups, temp;
	bool must_mount_ro = false;

	/* XXX: Mount arguments? */
	(void)args;

	/* Read the Ext2 disk header. */
	block_device_read(self->s_device, &super, sizeof(super),
	                 (pos_t)EXT2_SUPERBLOCK_OFFSET);

	/* Do some basic verification to check if this is really an EXT2 filesystem. */
	if (LESWAP16(super.e_signature) != EXT2_SIGNATURE)
		THROW(E_FSERROR_WRONG_FILE_SYSTEM);

	/* Do some validation on the superblock state. */
	if unlikely(LESWAP32(super.e_free_inodes) > LESWAP32(super.e_total_inodes) ||
	            LESWAP32(super.e_free_blocks) > LESWAP32(super.e_total_blocks))
		THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);
	if unlikely(!super.e_blocks_per_group || !super.e_inodes_per_group)
		THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);

	num_block_groups = CEILDIV(LESWAP32(super.e_total_blocks), LESWAP32(super.e_blocks_per_group));
	temp             = CEILDIV(LESWAP32(super.e_total_inodes), LESWAP32(super.e_inodes_per_group));
	if unlikely(num_block_groups != temp)
		THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);
	if unlikely(!num_block_groups)
		THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);

	self->sd_block_shift = 10 + LESWAP32(super.e_log2_blocksz);
	if unlikely(self->sd_block_shift >= PAGESHIFT)
		THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);

	self->sd_blocksize     = (size_t)1 << self->sd_block_shift;
	self->sd_blockmask     = self->sd_blocksize - 1;
	self->sd_ind_blocksize = self->sd_blocksize / 4;
	self->db_pageshift     = PAGESHIFT - self->sd_block_shift;
#ifndef CONFIG_VM_DATABLOCK_MIN_PAGEINFO
	self->db_pagealign     = (size_t)1 << self->db_pageshift;
	self->db_pagemask      = self->db_pagealign - 1;
#endif /* !CONFIG_VM_DATABLOCK_MIN_PAGEINFO */


#if 1 /* I'm guessing this is the right answer, but the wiki really isn't clear...                \
       * [...] The table is located in the block immediately following the Superblock             \
       *    -> That would mean a fixed partition offset of `2048'                                 \
       * [...] the Block Group Descriptor Table will begin at block 2 [for 1024 bytes per block]. \
       *       For any other block size, it will begin at block 1                                 \
       * I'm going with the later variant here, since that seems to make the most sense. */
	if (self->sd_block_shift <= 10)
		self->sd_bgroups_pos = EXT2_BLOCK2ADDR(self, 2);
	else {
		self->sd_bgroups_pos = EXT2_BLOCK2ADDR(self, 1);
	}
#else
	self->sd_bgroups_pos = EXT2_SUPERBLOCK_OFFSET + 1024;
#endif
	self->sd_bgroups_cnt  = num_block_groups;
	self->sd_ino_per_bgrp = LESWAP32(super.e_inodes_per_group);
	self->sd_blk_per_bgrp = LESWAP32(super.e_blocks_per_group);
	self->sd_total_inodes = LESWAP32(super.e_total_inodes);
	self->sd_total_blocks = LESWAP32(super.e_total_blocks);
	self->sd_version      = ((u32)LESWAP16(super.e_version_major) << 16 |
	                         (u32)LESWAP16(super.e_version_minor));
	if (self->sd_version >= EXT2_VERSION_1) {
		self->sd_feat_optional = LESWAP32(super.e_feat_optional);
		self->sd_feat_required = LESWAP32(super.e_feat_required);
		self->sd_feat_mountro  = LESWAP32(super.e_feat_mountro);
		self->sd_inode_size    = LESWAP16(super.e_inode_size);
		/* Make sure that the specified INode size isn't too small. */
		if unlikely(self->sd_inode_size < 128)
			THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);

		/* Check if we're implementing all the required features.
		 * NOTE: Just to improve compatibility, we treat journaling
		 *       as a mount-ro feature. */
		if (self->sd_feat_required & ~(EXT2_FEAT_REQ_FDIRENT_TYPE |
		                               EXT2_FEAT_REQ_FREPLAY_JOURNAL |
		                               EXT2_FEAT_REQ_FJOURNAL))
			THROW(E_FSERROR_CORRUPTED_FILE_SYSTEM);
		if (self->sd_feat_required & (EXT2_FEAT_REQ_FREPLAY_JOURNAL |
		                              EXT2_FEAT_REQ_FJOURNAL))
			must_mount_ro = true;
		if (self->sd_feat_mountro & ~(EXT2_FEAT_MRO_FSIZE64))
			must_mount_ro = true;
	} else {
		self->sd_inode_size = 128;
	}

	/* On EXT2 filesystem, the root directory is always Inode number #2 */
	self->i_fileino = (ino_t)EXT2_ROOT_DIRECTORY_INO;
	self->i_type    = &Ext2_DirOps;

	(void)must_mount_ro; /* TODO */

	/* Allocate Ext2-specific superblock data. */
	self->sd_groups = (struct block_group *)kmalloc(num_block_groups *
	                                                sizeof(struct block_group),
	                                                FS_GFP | GFP_CALLOC);
}

INTERN NOBLOCK void
NOTHROW(KCALL Ext2_FinalizeSuperblock)(Ext2Superblock *__restrict self) {
	if (self->sd_groups) {
		ext2_bgroup_t i;
		/* Free lazily allocated block group buffers. */
		for (i = 0; i < self->sd_bgroups_cnt; ++i) {
			kfree(self->sd_groups[i].bg_busage);
			kfree(self->sd_groups[i].bg_iusage);
		}
		kfree(self->sd_groups);
	}
}

INTERN void KCALL
Ext2_OpenINode(Ext2Superblock *__restrict UNUSED(self),
               struct inode *__restrict node,
               struct directory_node *__restrict UNUSED(parent_directory),
               struct directory_entry *__restrict UNUSED(parent_directory_entry))
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	switch (node->i_filemode & S_IFMT) {

	case S_IFREG:
		node->i_type = &Ext2_RegOps;
		break;

	case S_IFCHR:
	case S_IFBLK:
		node->i_type = &Ext2_DevOps;
		break;

	case S_IFDIR:
		node->i_type = &Ext2_DirOps;
		break;

	case S_IFLNK:
		node->i_type = &Ext2_LnkOps;
		break;

	default:
		/* Throw an unsupported-function error for any other type of node. */
		THROW(E_FSERROR_UNSUPPORTED_OPERATION);
	}
}

INTERN NONNULL((1)) void KCALL
Ext2_StatSuperblock(Ext2Superblock *__restrict self,
                    USER CHECKED struct statfs *result)
		THROWS(E_IOERROR, E_SEGFAULT, ...) {
	(void)self;
	(void)result;
	THROW(E_NOT_IMPLEMENTED_TODO);
}

INTERN void KCALL
Ext2_SynchronizeSuperblock(Ext2Superblock *__restrict self)
		THROWS(E_IOERROR, ...) {
	/* TODO */
	(void)self;
}



INTERN struct superblock_type Ext2_SuperblockType = {
	/*.st_driver            = */ &drv_self,
	/*.st_name              =*/ "ext2",
	/*.st_flags             = */ SUPERBLOCK_TYPE_FNORMAL,
	/*.st_sizeof_superblock = */ sizeof(Ext2Superblock),
	{
		/*.st_open = */ (void(KCALL *)(struct superblock *__restrict, UNCHECKED USER char *))&Ext2_OpenSuperblock
	},
	/*.st_functions = */ {
		/*.f_fini     = */ (void(KCALL *)(struct superblock *__restrict))&Ext2_FinalizeSuperblock,
		/*.f_opennode = */ (void(KCALL *)(struct superblock *__restrict, struct inode *__restrict, struct directory_node *__restrict, struct directory_entry *__restrict))&Ext2_OpenINode,
		/*.f_sync     = */ (void(KCALL *)(struct superblock *__restrict, USER CHECKED struct statfs *))&Ext2_StatSuperblock,
		/*.f_sync     = */ (void(KCALL *)(struct superblock *__restrict))&Ext2_SynchronizeSuperblock
	}
};

PRIVATE ATTR_FREETEXT DRIVER_INIT void init(void) {
	register_filesystem_type(&Ext2_SuperblockType);
}
PRIVATE DRIVER_FINI void fini(void) {
	unregister_filesystem_type(&Ext2_SuperblockType);
}


#if 0
PRIVATE ATTR_FREETEXT DRIVER_INIT void init2(void) {
	printk(KERN_DEBUG "ext2fs-- constructor\n");
	printk(KERN_DEBUG "drv_self          = %p\n", &drv_self);
	printk(KERN_DEBUG "d_eh_frame_start  = %p\n", drv_self.d_eh_frame_start);
	printk(KERN_DEBUG "d_eh_frame_end    = %p\n", drv_self.d_eh_frame_end);
	printk(KERN_DEBUG "drv_loadaddr      = %p\n", drv_loadaddr);
	printk(KERN_DEBUG "drv_start         = %p\n", drv_start);
	printk(KERN_DEBUG "drv_end           = %p\n", drv_end);
	printk(KERN_DEBUG "drv_name          = %q\n", drv_name);
	printk(KERN_DEBUG "drv_filename      = %q\n", drv_filename);
	printk(KERN_DEBUG "drv_file          = %p\n", drv_file);
	printk(KERN_DEBUG "drv_commandline   = %q\n", drv_commandline);
	printk(KERN_DEBUG "drv_argc          = %Iu\n", drv_argc);
	for (size_t i = 0; i < drv_argc; ++i)
		printk(KERN_DEBUG "drv_argv[%Iu] = %q\n", i, drv_argv[i]);
}

PRIVATE DRIVER_FINI void fini2(void) {
	printk(KERN_DEBUG "ext2fs destructor\n");
}
#endif


DECL_END

#endif /* !GUARD_MODEXT2FS_EXT2_C */
