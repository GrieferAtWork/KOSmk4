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
#ifdef __INTELLISENSE__
#include "node.c"
#define DEFINE_DIRECTORY_CREATFILE 1
//#define DEFINE_DIRECTORY_SYMLINK 1
//#define DEFINE_DIRECTORY_MKNOD 1
//#define DEFINE_DIRECTORY_MKDIR 1
#endif

DECL_BEGIN

#if defined(DEFINE_DIRECTORY_CREATFILE)
/* Create a new file within the given directory.
 * NOTE: When `open_mode & O_EXCL' is set, only `struct regular_node' are ever returned.
 * NOTE: When `open_mode & O_DOSPATH' is set, ignore casing when checking for existing files.
 * @param: open_mode: Set of `O_CREAT | O_EXCL | O_DOSPATH'
 * @param: ptarget_dirent: When non-NULL, store a reference to the resulting node's directory entry here.
 * @param: pwas_newly_created: When non-NULL, write `true' if a new file was
 *                             created, or `false' when the file already existed.
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH: [...] (`target_directory' was deleted)
 * @throw: E_FSERROR_ILLEGAL_PATH:        [...]
 * @throw: E_FSERROR_ILLEGAL_PATH:        `target_namelen' was ZERO(0)
 * @throw: E_FSERROR_FILE_ALREADY_EXISTS: [...] (Only when `open_mode & O_EXCL' is set)
 * @throw: E_FSERROR_FILE_NOT_FOUND:      [...] (Only when `open_mode & O_CREAT' isn't set)
 * @throw: E_FSERROR_DISK_FULL:           [...]
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_CREAT:
 *                                        [...]
 * @throw: E_FSERROR_READONLY:            [...]
 * @throw: E_IOERROR:                     [...] */
PUBLIC ATTR_RETNONNULL NONNULL((1, 2)) REF struct inode *KCALL
directory_creatfile(struct directory_node *__restrict target_directory,
                    CHECKED USER /*utf-8*/ char const *__restrict target_name, u16 target_namelen,
                    oflag_t open_mode, uid_t owner, gid_t group, mode_t mode,
                    REF struct directory_entry **ptarget_dirent,
                    bool *pwas_newly_created)
		THROWS(E_FSERROR_DELETED, E_FSERROR_ILLEGAL_PATH, E_FSERROR_FILE_ALREADY_EXISTS,
		       E_FSERROR_FILE_NOT_FOUND, E_FSERROR_DISK_FULL, E_FSERROR_UNSUPPORTED_OPERATION,
		       E_FSERROR_READONLY, E_IOERROR, E_SEGFAULT, ...)
#define MODE_IS_NOCASE  ((open_mode & (O_DOSPATH | O_EXCL)) == O_DOSPATH)
#elif defined(DEFINE_DIRECTORY_SYMLINK)
/* Create a symbolic link and return its INode.
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_SYMLINK: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH: [...] (`target_directory' was deleted)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_FSERROR_ILLEGAL_PATH:        [...]
 * @throw: E_FSERROR_ILLEGAL_PATH:        `target_namelen' was ZERO(0)
 * @throw: E_FSERROR_FILE_ALREADY_EXISTS: [...]
 * @throw: E_FSERROR_DISK_FULL:           [...]
 * @throw: E_FSERROR_READONLY:            [...]
 * @throw: E_IOERROR:                     [...] */
PUBLIC WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 4)) REF struct symlink_node *KCALL
directory_symlink(struct directory_node *__restrict target_directory,
                  CHECKED USER /*utf-8*/ char const *target_name, u16 target_namelen,
                  CHECKED USER /*utf-8*/ char const *link_text, size_t link_text_size,
                  uid_t owner, gid_t group, mode_t mode, unsigned int symlink_mode,
                  /*out*/ REF struct directory_entry **ptarget_dirent)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_DELETED,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_FILE_ALREADY_EXISTS,
		       E_FSERROR_DISK_FULL, E_FSERROR_READONLY, E_IOERROR, E_SEGFAULT, ...)
#define MODE_IS_NOCASE   (symlink_mode & DIRECTORY_SYMLINK_FNOCASE)
#elif defined(DEFINE_DIRECTORY_MKNOD)
/* Create a file / device node.
 * @assume(S_ISREG(mode) || S_ISBLK(mode) || S_ISCHR(mode));
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_MKNOD: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH: [...] (`target_directory' was deleted)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_FSERROR_ILLEGAL_PATH:        [...]
 * @throw: E_FSERROR_ILLEGAL_PATH:        `target_namelen' was ZERO(0)
 * @throw: E_FSERROR_FILE_ALREADY_EXISTS: [...]
 * @throw: E_FSERROR_DISK_FULL:           [...]
 * @throw: E_FSERROR_READONLY:            [...]
 * @throw: E_IOERROR:                     [...] */
PUBLIC WUNUSED ATTR_RETNONNULL NONNULL((1, 2)) REF struct inode *KCALL
directory_mknod(struct directory_node *__restrict target_directory,
                CHECKED USER /*utf-8*/ char const *__restrict target_name,
                u16 target_namelen, mode_t mode, uid_t owner,
                gid_t group, dev_t referenced_device, unsigned int mknod_mode,
                /*out*/ REF struct directory_entry **ptarget_dirent)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_DELETED,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_FILE_ALREADY_EXISTS,
		       E_FSERROR_DISK_FULL, E_FSERROR_READONLY, E_IOERROR, E_SEGFAULT, ...)
#define MODE_IS_NOCASE   (mknod_mode & DIRECTORY_MKNOD_FNOCASE)
#elif defined(DEFINE_DIRECTORY_MKDIR)
/* Create a new directory node.
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_MKNOD: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH: [...] (`target_directory' was deleted)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_FSERROR_ILLEGAL_PATH:        [...]
 * @throw: E_FSERROR_ILLEGAL_PATH:        `target_namelen' was ZERO(0)
 * @throw: E_FSERROR_FILE_ALREADY_EXISTS: [...]
 * @throw: E_FSERROR_DISK_FULL:           [...]
 * @throw: E_FSERROR_READONLY:            [...]
 * @throw: E_IOERROR:                     [...] */
PUBLIC WUNUSED ATTR_RETNONNULL NONNULL((1, 2)) REF struct directory_node *KCALL
directory_mkdir(struct directory_node *__restrict target_directory,
                CHECKED USER /*utf-8*/ char const *__restrict target_name,
                u16 target_namelen, mode_t mode, uid_t owner, gid_t group,
                unsigned int mkdir_mode,
                /*out*/ REF struct directory_entry **ptarget_dirent)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_DELETED,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_FILE_ALREADY_EXISTS,
		       E_FSERROR_DISK_FULL, E_FSERROR_READONLY, E_IOERROR, E_SEGFAULT, ...)
#define MODE_IS_NOCASE   (mkdir_mode & DIRECTORY_MKDIR_FNOCASE)
#endif /* ... */
{
#ifdef DEFINE_DIRECTORY_CREATFILE
#define RETURN_NODE_TYPE  struct inode
	REF struct inode *result;
#elif defined(DEFINE_DIRECTORY_SYMLINK)
#define RETURN_NODE_TYPE  struct symlink_node
	REF struct symlink_node *result;
#elif defined(DEFINE_DIRECTORY_MKNOD)
#define RETURN_NODE_TYPE  struct inode
	REF struct inode *result;
#elif defined(DEFINE_DIRECTORY_MKDIR)
#define RETURN_NODE_TYPE  struct directory_node
	REF struct directory_node *result;
#endif /* ... */
	REF struct directory_entry *target_entry;
#ifdef DEFINE_DIRECTORY_CREATFILE
again:
	assert((mode & ~07777) == 0);
#elif defined(DEFINE_DIRECTORY_SYMLINK)
	assert((mode & ~07777) == 0);
	if unlikely(!target_directory->i_type->it_directory.d_symlink)
		THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_SYMLINK);
#elif defined(DEFINE_DIRECTORY_MKNOD)
	assert(S_ISREG(mode) || S_ISBLK(mode) || S_ISCHR(mode));
	if (S_ISREG(mode)) {
		return directory_creatfile(target_directory,
		                           target_name,
		                           target_namelen,
		                           (mknod_mode & DIRECTORY_MKNOD_FNOCASE) ? (O_CREAT | O_EXCL | O_DOSPATH)
		                                                                  : (O_CREAT | O_EXCL),
		                           owner,
		                           group,
		                           mode & 07777,
		                           ptarget_dirent,
		                           NULL);
	}
	if unlikely(!target_directory->i_type->it_directory.d_mknod)
		THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_MKNOD);
#elif defined(DEFINE_DIRECTORY_MKDIR)
	assert((mode & ~07777) == 0);
	if unlikely(!target_directory->i_type->it_directory.d_mkdir)
		THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_MKDIR);
#endif /* ... */

#ifdef DEFINE_DIRECTORY_CREATFILE
	sync_read(target_directory);
	TRY {
		inode_check_deleted(target_directory, E_FILESYSTEM_DELETED_PATH);
		if ((open_mode & (O_CREAT | O_EXCL)) != (O_CREAT | O_EXCL)) {
			uintptr_t hash;
			/* Check for existing files without creating a new directory entry. */
			hash  = directory_entry_hash(target_name, target_namelen);
			target_entry = open_mode & O_DOSPATH
			               ? directory_getcaseentry(target_directory, target_name, target_namelen, hash)
			               : directory_getentry(target_directory, target_name, target_namelen, hash);
			/* File already exists! */
			if (target_entry)
				goto return_existing_entry;
		}
	} EXCEPT {
		if (vm_datablock_lock_endread(target_directory))
			goto again;
		RETHROW();
	}
	/* When not in create-mode, throw a file-not-found exception. */
	if (!(open_mode & O_CREAT)) {
		sync_endread(target_directory);
		THROW(E_FSERROR_FILE_NOT_FOUND);
	}
	sync_upgrade(target_directory);
#else /* DEFINE_DIRECTORY_CREATFILE */
	sync_write(target_directory);
#endif /* !DEFINE_DIRECTORY_CREATFILE */

	TRY {
		inode_check_deleted(target_directory, E_FILESYSTEM_DELETED_PATH);
		/* Must create a new entry. */
		target_entry = directory_entry_alloc_s(target_name, target_namelen);
		TRY {
			struct heapptr resptr;
			REF struct directory_entry *existing_entry;
			/* Check for an existing entry. */
			existing_entry = MODE_IS_NOCASE
			                 ? directory_getcaseentry(target_directory,
			                                          target_entry->de_name,
			                                          target_namelen,
			                                          target_entry->de_hash)
			                 : directory_getentry(target_directory,
			                                      target_entry->de_name,
			                                      target_namelen,
			                                      target_entry->de_hash);
			if unlikely(existing_entry) {
#ifdef DEFINE_DIRECTORY_CREATFILE
				if (!(open_mode & O_EXCL)) {
					sync_endwrite(target_directory);
					assert(!isshared(target_entry));
					destroy(target_entry);
					target_entry = existing_entry;
					goto open_existing_entry;
				}
#endif /* DEFINE_DIRECTORY_CREATFILE */
				decref_unlikely(existing_entry);
				THROW(E_FSERROR_FILE_ALREADY_EXISTS);
			}
#ifdef DEFINE_DIRECTORY_CREATFILE
			/* Make sure the file-creation operator is provided. */
			if unlikely(!target_directory->i_type->it_directory.d_creat)
				THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_CREAT);
#endif /* DEFINE_DIRECTORY_CREATFILE */

			/* All right! Move ahead and construct the new, resulting INode. */
			resptr = heap_alloc(FS_HEAP,
#ifdef DEFINE_DIRECTORY_CREATFILE
			                    sizeof(struct regular_node)
#else /* DEFINE_DIRECTORY_CREATFILE */
			                    sizeof(RETURN_NODE_TYPE)
#endif /* !DEFINE_DIRECTORY_CREATFILE */
#ifdef DEFINE_DIRECTORY_SYMLINK
			                    + (link_text_size * sizeof(char))
#endif /* DEFINE_DIRECTORY_SYMLINK */
			                    ,
			                    FS_GFP | GFP_CALLOC);
			result = (RETURN_NODE_TYPE *)resptr.hp_ptr;

			TRY {
				//TODO:result->i_fileatime = wall_gettime(self->i_super->s_wall);
#ifdef DEFINE_DIRECTORY_SYMLINK
				memcpy(result->sl_stext, link_text, link_text_size * sizeof(char));
#elif defined(DEFINE_DIRECTORY_MKDIR)
				result->d_map = (REF struct directory_entry **)kmalloc((DIRECTORY_DEFAULT_MASK + 1) *
				                                                       sizeof(REF struct directory_entry *),
				                                                       FS_GFP | GFP_CALLOC);
#endif /* ... */
			} EXCEPT {
				heap_free(FS_HEAP, resptr.hp_ptr, resptr.hp_siz, FS_GFP);
				RETHROW();
			}

			/* Initialize the new INode */
			result->db_refcnt = 1;
			rwlock_cinit_write(&result->db_lock);
			result->db_type      = &inode_datablock_type;
			result->db_pageshift = target_directory->db_pageshift;
#ifndef CONFIG_VM_DATABLOCK_MIN_PAGEINFO
			result->db_addrshift = target_directory->db_addrshift;
			result->db_pagealign = target_directory->db_pagealign;
			result->db_pagemask  = target_directory->db_pagemask;
			result->db_pagesize  = target_directory->db_pagesize;
#endif /* CONFIG_VM_DATABLOCK_MIN_PAGEINFO */
			result->i_super    = target_directory->i_super; /* NOTE: Incref()'d below. */
			result->i_heapsize = resptr.hp_siz;
			result->i_flags    = INODE_FATTRLOADED;
			result->i_fileuid  = owner;
			result->i_filegid  = group;
#ifdef DEFINE_DIRECTORY_CREATFILE
			result->i_filemode = S_IFREG | mode;
#elif defined(DEFINE_DIRECTORY_SYMLINK)
			result->i_filemode = S_IFLNK | mode;
			result->i_filesize = (pos_t)link_text_size;
			result->sl_text    = result->sl_stext;
#elif defined(DEFINE_DIRECTORY_MKNOD)
			result->i_filemode = mode;
#elif defined(DEFINE_DIRECTORY_MKDIR)
			result->i_filemode = S_IFDIR | mode;
			result->d_parent   = target_directory; /* NOTE: Incref()'d below. */
			result->d_mask     = DIRECTORY_DEFAULT_MASK;
#endif /* ... */
			memcpy(&result->i_filemtime, &result->i_fileatime, sizeof(struct timespec));
			memcpy(&result->i_filectime, &result->i_fileatime, sizeof(struct timespec));
		} EXCEPT {
			assert(!isshared(target_entry));
			destroy(target_entry);
			RETHROW();
		}
	} EXCEPT {
		sync_endwrite(target_directory);
		RETHROW();
	}

	/* Acquire the secondary lock to the superblock's INode tree. */
	if unlikely(!superblock_nodeslock_trywrite(target_directory->i_super)) {
again_endwrite_self:
		sync_endwrite(target_directory);
		TRY {
			superblock_nodeslock_write(target_directory->i_super);
			if unlikely(!sync_trywrite(target_directory)) {
				superblock_nodeslock_endwrite(target_directory->i_super);
				sync_write(target_directory);
				if unlikely(!superblock_nodeslock_trywrite(target_directory->i_super))
					goto again_endwrite_self;
			}
			/* Must re-check if the file has appeared in the mean time. */
			TRY {
				REF struct directory_entry *existing_entry;
				existing_entry = MODE_IS_NOCASE
				                 ? directory_getcaseentry(target_directory,
				                                          target_entry->de_name,
				                                          target_namelen,
				                                          target_entry->de_hash)
				                 : directory_getentry(target_directory,
				                                      target_entry->de_name,
				                                      target_namelen,
				                                      target_entry->de_hash);
				if unlikely(existing_entry != NULL) {
#ifdef DEFINE_DIRECTORY_CREATFILE
					if (!(open_mode & O_EXCL)) {
						superblock_nodeslock_endwrite(target_directory->i_super);
						sync_endwrite(target_directory);
						assert(!isshared(result));
						heap_free(FS_HEAP, result, result->i_heapsize, FS_GFP);
						assert(!isshared(target_entry));
						destroy(target_entry);
						target_entry = existing_entry;
						goto open_existing_entry;
					}
#endif /* DEFINE_DIRECTORY_CREATFILE */
					decref_unlikely(existing_entry);
					THROW(E_FSERROR_FILE_ALREADY_EXISTS);
				}
			} EXCEPT {
				superblock_nodeslock_endwrite(target_directory->i_super);
				sync_endwrite(target_directory);
				RETHROW();
			}
		} EXCEPT {
			assert(!isshared(result));
#ifdef DEFINE_DIRECTORY_MKDIR
			kffree(result->d_map, GFP_CALLOC);
#endif /* DEFINE_DIRECTORY_MKDIR */
			heap_free(FS_HEAP, result, result->i_heapsize, FS_GFP);
			assert(!isshared(target_entry));
			destroy(target_entry);
			RETHROW();
		}
	}
#ifndef NDEBUG
	memset(&result->i_fileino, 0xcc, sizeof(ino_t));
	memset(&target_entry->de_ino, 0xdd, sizeof(ino_t));
#endif /* !NDEBUG */
#ifdef DEFINE_DIRECTORY_CREATFILE
	target_entry->de_type = DT_REG;
#elif defined(DEFINE_DIRECTORY_SYMLINK)
	target_entry->de_type = DT_LNK;
#elif defined(DEFINE_DIRECTORY_MKNOD)
	target_entry->de_type = IFTODT(mode);
#elif defined(DEFINE_DIRECTORY_MKDIR)
	target_entry->de_type = DT_DIR;
#endif /* ... */
	assert(sync_writing(result));
	assert(result->i_super == target_directory->i_super);
#ifdef DEFINE_DIRECTORY_MKDIR
	assert(result->d_parent == target_directory);
#endif /* DEFINE_DIRECTORY_MKDIR */
	incref(target_directory->i_super); /* Create the reference for the assignment to `result->i_super' above. */
#ifdef DEFINE_DIRECTORY_MKDIR
	incref(target_directory);          /* Create the reference for the assignment to `result->d_parent' above. */
#endif /* DEFINE_DIRECTORY_MKDIR */
	TRY {
		inode_check_deleted(target_directory, E_FILESYSTEM_DELETED_PATH);
		/* Actually invoke the file-creation operator. */
#ifdef DEFINE_DIRECTORY_CREATFILE
		(*target_directory->i_type->it_directory.d_creat)(target_directory,
		                                                  target_entry,
		                                                  (struct regular_node *)result);
#elif defined(DEFINE_DIRECTORY_SYMLINK)
		(*target_directory->i_type->it_directory.d_symlink)(target_directory,
		                                                    target_entry,
		                                                    result);
#elif defined(DEFINE_DIRECTORY_MKNOD)
		(*target_directory->i_type->it_directory.d_mknod)(target_directory,
		                                                  target_entry,
		                                                  result);
#elif defined(DEFINE_DIRECTORY_MKDIR)
		(*target_directory->i_type->it_directory.d_mkdir)(target_directory,
		                                                  target_entry,
		                                                  result);
#endif /* ... */
	} EXCEPT {
		superblock_nodeslock_endwrite(target_directory->i_super);
		sync_endwrite(target_directory);
		decref_unlikely(target_directory->i_super);
#ifdef DEFINE_DIRECTORY_MKDIR
		decref_unlikely(target_directory);
#endif /* DEFINE_DIRECTORY_MKDIR */
		assert(sync_writing(result));
		assert(!isshared(result));
#ifdef DEFINE_DIRECTORY_MKDIR
		kfree(result->d_map);
#endif /* DEFINE_DIRECTORY_MKDIR */
		heap_free(FS_HEAP, result, result->i_heapsize, FS_GFP);
		assert(!isshared(target_entry));
		destroy(target_entry);
		RETHROW();
	}
	assert(sync_writing(result));
	assert(result->i_type != NULL);
	assert(result->i_filenlink >= (nlink_t)1);
	assert(result->i_super == target_directory->i_super);
#ifdef DEFINE_DIRECTORY_MKDIR
	assert(result->d_parent == target_directory);
#endif /* DEFINE_DIRECTORY_MKDIR */
	assert(target_entry->de_ino == result->i_fileino);
#ifdef DEFINE_DIRECTORY_CREATFILE
	assert(target_entry->de_type == DT_REG);
#elif defined(DEFINE_DIRECTORY_SYMLINK)
	assert(target_entry->de_type == DT_LNK);
#elif defined(DEFINE_DIRECTORY_MKNOD)
	assert(target_entry->de_type == IFTODT(mode));
#elif defined(DEFINE_DIRECTORY_MKDIR)
	assert(target_entry->de_type == DT_DIR);
#endif /* ... */
	assert(target_entry->de_type == IFTODT(result->i_filemode));

	/* Insert the new INode into the file-tree of the superblock */
	if (result->i_flags & INODE_FPERSISTENT)
		incref(result); /* The reference kept for persistent INodes. */

	sync_endwrite(result);
	inode_tree_insert(&target_directory->i_super->s_nodes, result);
	superblock_nodeslock_endwrite(target_directory->i_super);
	/* Update our directory entry and add it to the directory node cache. */
	if (ptarget_dirent)
		*ptarget_dirent = incref(target_entry);
	directory_addentry(target_directory, target_entry); /* Add the new entry to our directory (inherit reference). */
	sync_endwrite(target_directory);
	/* Return the newly constructed node. */
#ifdef DEFINE_DIRECTORY_CREATFILE
	if (pwas_newly_created)
		*pwas_newly_created = true;
#endif /* DEFINE_DIRECTORY_CREATFILE */
	return result;
#ifdef DEFINE_DIRECTORY_CREATFILE
	return_existing_entry:
	vm_datablock_lock_endread(target_directory);
open_existing_entry:
	TRY {
		result = superblock_opennode(target_directory->i_super,
		                             target_directory,
		                             target_entry);
	} EXCEPT {
		decref(target_entry);
		RETHROW();
	}
	if (ptarget_dirent)
		*ptarget_dirent = target_entry;
	else {
		decref(target_entry);
	}
	if (pwas_newly_created)
		*pwas_newly_created = false;
	return result;
#endif /* DEFINE_DIRECTORY_CREATFILE */
}

#undef MODE_IS_NOCASE
#undef RETURN_NODE_TYPE
#undef DEFINE_DIRECTORY_CREATFILE
#undef DEFINE_DIRECTORY_SYMLINK
#undef DEFINE_DIRECTORY_MKNOD
#undef DEFINE_DIRECTORY_MKDIR

DECL_END

