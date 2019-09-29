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
#ifndef GUARD_KERNEL_INCLUDE_FS_NODE_H
#define GUARD_KERNEL_INCLUDE_FS_NODE_H 1

#include <kernel/compiler.h>

#include <dev/block.h>
#include <kernel/driver.h>
#include <kernel/types.h>
#include <kernel/vm.h>

#include <hybrid/sequence/atree.h>

#include <kos/io.h>

#ifdef __cplusplus
#include <kernel/except.h>

#include <libc/string.h>
#endif /* __cplusplus */

DECL_BEGIN



#ifdef __CC__
struct path;
struct inode;
struct inode_data;
struct superblock;
struct directory_entry;
struct directory_node;
struct symlink_node;
struct driver;
struct wall_clock;
struct aio_buffer;
struct aio_pbuffer;

typedef uintptr_t fsmode_t; /* Set of `FS_MODE_F*' */

/* The callback invoked by directory enumerators. */
typedef NONNULL((1)) void
(KCALL *directory_enum_callback_t)(void *arg, /*utf-8*/ char const *__restrict name,
                                   u16 namelen, unsigned char type, ino_t ino);


struct inode_type {
	/* [0..1] Finalizer callback. */
	NOBLOCK NONNULL((1)) void /*NOTHROW*/(KCALL *it_fini)(struct inode *__restrict self);

	struct {
		/* [1..1][locked(WRITE(self))] Load INode attributes.
		 * Upon success, the caller will set `INODE_FATTRLOADED'.
		 * NOTE: Nodes that are only ever constructed with the `INODE_FATTRLOADED'
		 *       flag already set (often such nodes are filesystem root nodes),
		 *       do not need to implement this operator.
		 * REMINDER: This operator is also responsible to load the `i_filenlink' field!
		 * @throw: E_IOERROR: Failed to load INode attributes. */
		NONNULL((1))
		void (KCALL *a_loadattr)(struct inode *__restrict self)
				THROWS(E_IOERROR, ...);

		/* [0..1][locked(WRITE(self))] Save INode attributes.
		 * Upon success, the caller will clear `INODE_FATTRCHANGED'.
		 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_WRATTR:
		 *                             [...] (Same as not implementing this function)
		 * @throw: E_FSERROR_READONLY: [...]
		 * @throw: E_IOERROR:          Failed to read/write data to/from disk. */
		NONNULL((1))
		void (KCALL *a_saveattr)(struct inode *__restrict self)
				THROWS(E_FSERROR_UNSUPPORTED_OPERATION,
				       E_FSERROR_READONLY, E_IOERROR, ...);


		/* [0..1][locked(WRITE(self))]
		 * Mask INode attributes not supported by the filesystem by restoring their
		 * default default as would have been initialized by `a_loadattr()'.
		 * When this operator isn't implemented, all attributes are assumed supported
		 * by the filesystem.
		 * Otherwise, this operator is invoked for `chmod()' and `chown()' in order
		 * to check if changes to attributes would become undone once the node is saved.
		 * If changes would become undone, this function will do that before they could
		 * become visible in user-space, as well as allow the caller to detect those
		 * changes and throw an `E_FSERROR_UNSUPPORTED_OPERATION'.
		 * However, if chmod() or chown() is used to keep previous values (or as with
		 * the case of `chmod()', filesystem types like FAT still implement a way of
		 * setting a read-only attribute), this function deciphers such uses when the
		 * underlying superblock supports attributes only partially.
		 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_CHMOD:
		 *                        The new attributes cannot be stored by the file system. */
		NONNULL((1))
		void (KCALL *a_maskattr)(struct inode *__restrict self)
				THROWS(E_FSERROR_UNSUPPORTED_OPERATION, ...);

		/* [0..1]
		 * Query information about hard limits on various filesystem objects.
		 * @param: name: One of `_PC_*' from `<bits/confname.h>'
		 * @return: INODE_PATHCONF_UNDEDEFINED: The given `name' is not implemented by the underlying filesystem.
		 * For more details on how this operator is invoked, see the documentation of `inode_pathconf()' */
		NONNULL((1))
		intptr_t (KCALL *a_pathconf)(struct inode *__restrict self, unsigned int name)
				THROWS(...);
#define INODE_PATHCONF_UNDEDEFINED  (-22) /* -EINVAL */

		/* [0..1] General-purpose handler for ioctl() requests */
		NONNULL((1))
		syscall_slong_t (KCALL *a_ioctl)(struct inode *__restrict self, syscall_ulong_t cmd,
		                                 USER UNCHECKED void *arg, iomode_t mode)
				THROWS(...);

		/* [0..1][locked(WRITE(self))]
		 * An optional callback that is invoked when kernel caches are being cleared. */
		NOBLOCK NONNULL((1))
		size_t /*NOTHROW*/(KCALL *a_clearcache)(struct inode *__restrict self);

	} it_attr;


	struct {
		/* [0..1][locked(READ(self))] Read function.
		 * This function must either perform the read directly, before broadcasting the
		 * given `completed' signal and returning normally, or must schedule the read to
		 * be performed asynchronously, with `completed' being broadcast once that finishes.
		 * Errors can also be indicated in one of 2 ways:
		 *  - Either by throwing the error directly before this function returns,
		 *    in which `completed' must still be invoked with something other than
		 *    `BD_ASYNC_COMPLETED_SUCCESS' before actually returning.
		 *  - Or by only invoking `completed' with something other than
		 *    `BD_ASYNC_COMPLETED_SUCCESS', which can also be done at any
		 *    point after this function has already returned normally.
		 *    I.e.: It is done asynchronously!
		 * NOTE: Don't call `aio_multihandle_done(aio)' from within these callbacks!
		 *       It is the responsibility of whoever declared the multihandle to indicate
		 *       that all async operations to-be performed with it have been started!
		 * @assume(self->i_flags & INODE_FATTRLOADED);
		 * @assume(num_bytes != 0);
		 * @assume(file_position + num_bytes <= self->i_filesize);
		 * @param: self:          The Inode being addressed.
		 * @param: file_position: The in-file position to read/write.
		 * @param: num_bytes:     The amount of bytes to read.
		 * @param: completed:     A function invoked upon I/O completion.
		 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_READ:
		 *                        [...] (Same as not implementing)
		 * @throw: E_IOERROR:     Failed to read data from disk. */
		NONNULL((1, 5))
		void (KCALL *f_read)(struct inode *__restrict self,
		                     USER CHECKED void *dst,
		                     size_t num_bytes, pos_t file_position,
		                     struct aio_multihandle *__restrict aio)
				THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...);
		NONNULL((1, 5))
		void (KCALL *f_pread)(struct inode *__restrict self,
		                      vm_phys_t dst,
		                      size_t num_bytes, pos_t file_position,
		                      struct aio_multihandle *__restrict aio)
				THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...);
		NONNULL((1, 2, 5))
		void (KCALL *f_readv)(struct inode *__restrict self,
		                      struct aio_buffer *__restrict buf,
		                      size_t num_bytes, pos_t file_position,
		                      struct aio_multihandle *__restrict aio)
				THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...);
		NONNULL((1, 2, 5))
		void (KCALL *f_preadv)(struct inode *__restrict self,
		                       struct aio_pbuffer *__restrict buf,
		                       size_t num_bytes, pos_t file_position,
		                       struct aio_multihandle *__restrict aio)
				THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...);

		/* [0..1][locked(WRITE(self))] Write function.
		 * Same as `f_read', but used for writing data instead.
		 * NOTE: Don't call `aio_multihandle_done(aio)' from within these callbacks!
		 *       It is the responsibility of whoever declared the multihandle to indicate
		 *       that all async operations to-be performed with it have been started!
		 * @assume(self->i_flags & INODE_FATTRLOADED);
		 * @assume(num_bytes != 0);
		 * @assume(file_position + num_bytes <= self->i_filesize);
		 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_WRITE:
		 *                        [...] (Same as not implementing)
		 * @throw: E_FSERROR_DISK_FULL: [...]
		 * @throw: E_FSERROR_READONLY:  [...]
		 * @throw: E_IOERROR_BADBOUNDS: Translated to `E_FSERROR_DISK_FULL'
		 * @throw: E_IOERROR_READONLY:  Translated to `E_FSERROR_READONLY'
		 * @throw: E_IOERROR:     Failed to read/write data to/from disk. */
		NONNULL((1, 5))
		void (KCALL *f_write)(struct inode *__restrict self,
		                      USER CHECKED void const *src,
		                      size_t num_bytes, pos_t file_position,
		                      struct aio_multihandle *__restrict aio)
				THROWS(E_FSERROR_UNSUPPORTED_OPERATION,
				       E_FSERROR_DISK_FULL, E_FSERROR_READONLY,
				       E_IOERROR_BADBOUNDS, E_IOERROR_READONLY,
				       E_IOERROR, ...);
		NONNULL((1, 5))
		void (KCALL *f_pwrite)(struct inode *__restrict self,
		                       vm_phys_t src,
		                       size_t num_bytes, pos_t file_position,
		                       struct aio_multihandle *__restrict aio)
				THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...);
		NONNULL((1, 2, 5))
		void (KCALL *f_writev)(struct inode *__restrict self,
		                       struct aio_buffer *__restrict buf,
		                       size_t num_bytes, pos_t file_position,
		                       struct aio_multihandle *__restrict aio)
				THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...);
		NONNULL((1, 2, 5))
		void (KCALL *f_pwritev)(struct inode *__restrict self,
		                        struct aio_pbuffer *__restrict buf,
		                        size_t num_bytes, pos_t file_position,
		                        struct aio_multihandle *__restrict aio)
				THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...);

		/* [0..1][locked(WRITE(self))]
		 * Truncate or increment the length of `self' to `new_size' bytes.
		 * Upon success, the caller will update `self->i_filesize',
		 * by setting it to be equal to `new_size'.
		 * NOTE: When ZERO(0) is passed for `new_size', this function must
		 *       deallocate any blocks allocated for the file. (These semantics
		 *       are required during `unlink()' before removing the last reference
		 *       to a regular file; however, empty directories are removed through
		 *       use of the `d_rmdir()' operator when applied to the hosting
		 *       directory)
		 * @assume(self->i_flags & INODE_FATTRLOADED);
		 * @assume(self->i_filesize != new_size);
		 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_TRUNC:
		 *                              [...] (Same as not implementing)
		 * @throw: E_FSERROR_DISK_FULL: [...]
		 * @throw: E_FSERROR_READONLY:  [...]
		 * @throw: E_IOERROR_BADBOUNDS: Translated to `E_FSERROR_DISK_FULL'
		 * @throw: E_IOERROR_READONLY:  Translated to `E_FSERROR_READONLY'
		 * @throw: E_IOERROR:           Failed to read/write data to/from disk. */
		NONNULL((1))
		void (KCALL *f_truncate)(struct inode *__restrict self, pos_t new_size)
				THROWS(E_FSERROR_UNSUPPORTED_OPERATION,
				       E_FSERROR_DISK_FULL, E_FSERROR_READONLY,
				       E_IOERROR_BADBOUNDS, E_IOERROR_READONLY,
				       E_IOERROR, ...);

		/* [0..1] Flexible read operator.
		 * This function can be used in place of the more low-level read operators
		 * defined above, and allows the implementing filesystem to dynamically
		 * control the behavior of the read(2) system call when invoked on this
		 * INode. (mainly intended for configuration files found in places such
		 * as the procfs) */
		NONNULL((1))
		size_t (KCALL *f_flexread)(struct inode *__restrict self,
		                           USER CHECKED void *dst, size_t num_bytes,
		                           pos_t file_position)
				THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...);

#ifdef CONFIG_VIO
		/* [0..1][locked(READ(self) / WRITE(self))]
		 * VIO file data access interface.
		 * Since INodes are derived from data blocks, they can also implement the VIO
		 * interface, with this pointer being usable as hook for implementing file I/O,
		 * as well as memory mappings through virtual I/O callbacks. */
		struct vm_datablock_type_vio *f_vio;
#endif /* CONFIG_VIO */
	} it_file;

	union {
		struct {
			/* [0..1][locked(READ(self))]
			 * NOTE: This function should not yield entries for `.'
			 *       and `..', as those are created by the VFS overlay.
			 * Read a new directory entry from the data stream of `self', starting at
			 * data offset `*pentry_pos'. Upon success, return a reference to the newly
			 * allocated directory entry and update `*pentry_pos' to point to the next
			 * directory entry (which can then be re-used in further calls to this function).
			 * When the directory has ended, return `NULL' instead to indicate EOF.
			 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_READDIR:
			 *                        [...] (Same as not implementing)
			 * @throw: E_IOERROR_BADBOUNDS: Same as returning `NULL'
			 * @throw: E_IOERROR:     Failed to read data from disk. */
			NONNULL((1, 2))
			REF struct directory_entry *(KCALL *d_readdir)(struct directory_node *__restrict self,
			                                               pos_t *__restrict pentry_pos)
					THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...);

			/* One-shot directory enumeration operators.
			 * These can be provided as an alternative when `d_readdir'
			 * isn't implemented, and are best suited for dynamic
			 * directories such as `/proc'. */
			struct {
				/* [0..1][locked(READ(self))]
				 * Optional operator that can be implemented to
				 * accommodate dynamically allocated directory entries.
				 * When implemented, this operator is used during
				 * path traversion instead of using `d_readdir' for that.
				 * @return: NULL: No file with the given name exists.
				 * @param: mode: Set of `FS_MODE_F*' (Most notably `FS_MODE_FDOSPATH')
				 * @throw: E_SEGFAULT:    Failed to access the given `name'.
				 * @throw: E_FSERROR_FILE_NOT_FOUND: [...] (Same as returning NULL)
				 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_READDIR:
				 *                        [...] (Same as not implementing)
				 * @throw: E_IOERROR:     Failed to read data from disk. */
				NONNULL((1, 2))
				REF struct directory_entry *(KCALL *o_lookup)(struct directory_node *__restrict self,
				                                              CHECKED USER /*utf-8*/char const *__restrict name,
				                                              u16 namelen, uintptr_t hash, fsmode_t mode)
						THROWS(E_SEGFAULT, E_FSERROR_FILE_NOT_FOUND,
						       E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...);
				/* [0..1][locked(READ(self))]
				 * Enumerate all entries of a dynamic directory `node':
				 * >> (*callback)(arg, "foo", DT_REG, 42);
				 * >> (*callback)(arg, "bar", DT_REG, 43);
				 * >> (*callback)(arg, "baz", DT_REG, 44);
				 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_READDIR:
				 *                        [...] (Same as not implementing)
				 * @throw: E_IOERROR:     Failed to read data from disk. */
				NONNULL((1, 2))
				void (KCALL *o_enum)(struct directory_node *__restrict node,
				                     directory_enum_callback_t callback,
				                     void *arg)
						THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...);
			} d_oneshot;


			/* [0..1]
			 * [locked(WRITE(target_directory))]
			 * [locked(WRITE(target_directory->i_super->s_nodes_lock))]
			 * Allocate a new regular (`S_IFREG') INode referred to by a single link
			 * that is created within `target_directory', using `target_dirent'
			 * as INode directory entry.
			 * This function must initialize the following members of `target_dirent':
			 *     - de_fsdata (optionally, depending on filesystem implementation)
			 *     - de_pos
			 *     - de_ino
			 * This function must initialize the following members of `new_node':
			 *     - i_fileino (Same as `target_dirent->de_ino')
			 *     - i_type
			 *     - i_filenlink (To `>= 1')
			 *     - i_fsdata (Optionally; pre-initialized to `NULL')
			 * During this operation, the new directory entry should be
			 * constructed on-disk, or scheduled for such an allocation.
			 * NOTE: This function may also choose to set the `INODE_FCHANGED' flag
			 *       of `new_node', in which case the caller will add the node to
			 *       the set of changed nodes of the accompanying superblock, meaning
			 *       that filesystem implementations may choose to lazily set save
			 *       attributes of newly constructed nodes to disk once the disk
			 *       is supposed to be synchronized.
			 * @assume(new_node->db_refcnt == 1); (Exclusive user)
			 * @assume(new_node->i_flags & INODE_FATTRLOADED);
			 * @assume(new_node->i_super == target_directory->i_super);
			 * @assume(new_node->i_filesize == 0);
			 * @assume(INODE_ISREG(new_node));
			 * @assume(!directory_getentry(target_directory,target_dirent...));
			 * @assume(target_dirent->de_namelen != 0);
			 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_CREAT:
			 *                                 [...] (Same as not implementing)
			 * @throw: E_FSERROR_ILLEGAL_PATH: [...]
			 * @throw: E_FSERROR_DISK_FULL:    [...]
			 * @throw: E_FSERROR_READONLY:     [...]
			 * @throw: E_IOERROR_BADBOUNDS:    Translated to `E_FSERROR_DISK_FULL'
			 * @throw: E_IOERROR_READONLY:     Translated to `E_FSERROR_READONLY'
			 * @throw: E_IOERROR:              Failed to read/write data to/from disk. */
			NONNULL((1, 2, 3))
			void (KCALL *d_creat)(struct directory_node *__restrict target_directory,
			                      struct directory_entry *__restrict target_dirent,
			                      struct regular_node *__restrict new_node)
					THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ILLEGAL_PATH,
					       E_FSERROR_DISK_FULL, E_FSERROR_READONLY,
					       E_IOERROR_BADBOUNDS, E_IOERROR_READONLY,
					       E_IOERROR, ...);

			/* [0..1]
			 * [locked(WRITE(target_directory))]
			 * [locked(WRITE(target_directory->i_super->s_nodes_lock))]
			 * Allocate a new directory INode referred to by a single link
			 * that is created within `target_directory', using `target_dirent'
			 * as INode directory entry.
			 * This function must initialize the following members of `target_dirent':
			 *     - de_fsdata (optionally, depending on filesystem implementation)
			 *     - de_pos
			 *     - de_ino
			 * This function must initialize the following members of `new_directory':
			 *     - i_fileino (Same as `target_dirent->de_ino')
			 *     - i_type
			 *     - i_filenlink (To `>= 1')
			 *     - i_fsdata (Optionally; pre-initialized to `NULL')
			 * During this operation, the new directory entry should be
			 * constructed on-disk, or scheduled for such an allocation.
			 * NOTE: This function may also choose to set the `INODE_FCHANGED' flag
			 *       of `new_directory', in which case the caller will add the node to
			 *       the set of changed nodes of the accompanying superblock, meaning
			 *       that filesystem implementations may choose to lazily set save
			 *       attributes of newly constructed nodes to disk once the disk
			 *       is supposed to be synchronized.
			 * @assume(new_directory->db_refcnt == 1); (Exclusive user)
			 * @assume(new_directory->i_super == target_directory->i_super);
			 * @assume(new_directory->i_flags & INODE_FATTRLOADED);
			 * @assume(S_ISDIR(new_directory->i_filemode));
			 * @assume(!directory_getentry(target_directory,target_dirent...));
			 * @assume(target_dirent->de_namelen != 0);
			 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_MKDIR:
			 *                                 [...] (Same as not implementing)
			 * @throw: E_FSERROR_ILLEGAL_PATH: [...]
			 * @throw: E_FSERROR_DISK_FULL:    [...]
			 * @throw: E_FSERROR_READONLY:     [...]
			 * @throw: E_IOERROR_BADBOUNDS:    Translated to `E_FSERROR_DISK_FULL'
			 * @throw: E_IOERROR_READONLY:     Translated to `E_FSERROR_READONLY'
			 * @throw: E_IOERROR:              Failed to read/write data to/from disk. */
			NONNULL((1, 2, 3))
			void (KCALL *d_mkdir)(struct directory_node *__restrict target_directory,
			                      struct directory_entry *__restrict target_dirent,
			                      struct directory_node *__restrict new_directory)
					THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ILLEGAL_PATH,
					       E_FSERROR_DISK_FULL, E_FSERROR_READONLY,
					       E_IOERROR_BADBOUNDS, E_IOERROR_READONLY,
					       E_IOERROR, ...);

			/* [0..1]
			 * [locked(WRITE(target_directory))]
			 * [locked(WRITE(target_directory->i_super->s_nodes_lock))]
			 * Insert the given symbolic-link node `link_node' into the given
			 * target directory `target_directory' under `target_dirent', while
			 * initializing the following members of `link_node':
			 *    - i_fileino
			 *    - i_type
			 *    - i_filenlink (To `>= 1')
			 *    - i_fsdata (Optionally; pre-initialized to `NULL')
			 * This function must initialize the following members of `target_dirent':
			 *    - de_fsdata (optionally, depending on filesystem implementation)
			 *    - de_pos
			 *    - de_ino (Same as `link_node->i_fileino')
			 * Upon success, this operator must fill in `target_dirent->de_pos'
			 * @assume(link_node->db_refcnt == 1); (Exclusive user)
			 * @assume(link_node->i_flags & INODE_FATTRLOADED);
			 * @assume(link_node->sl_text != NULL);
			 * @assume(!directory_getentry(target_directory,target_dirent...));
			 * @assume(target_dirent->de_namelen != 0);
			 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_SYMLINK:
			 *                                 [...] (Same as not implementing)
			 * @throw: E_FSERROR_ILLEGAL_PATH: [...]
			 * @throw: E_FSERROR_DISK_FULL:    [...]
			 * @throw: E_FSERROR_READONLY:     [...]
			 * @throw: E_IOERROR_BADBOUNDS:    Translated to `E_FSERROR_DISK_FULL'
			 * @throw: E_IOERROR_READONLY:     Translated to `E_FSERROR_READONLY'
			 * @throw: E_IOERROR:              Failed to read/write data to/from disk. */
			NONNULL((1, 2, 3))
			void (KCALL *d_symlink)(struct directory_node *__restrict target_directory,
			                        struct directory_entry *__restrict target_dirent,
			                        struct symlink_node *__restrict link_node)
					THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ILLEGAL_PATH,
					       E_FSERROR_DISK_FULL, E_FSERROR_READONLY,
					       E_IOERROR_BADBOUNDS, E_IOERROR_READONLY,
					       E_IOERROR, ...);

			/* [0..1]
			 * [locked(WRITE(target_directory))]
			 * [locked(WRITE(target_directory->i_super->s_nodes_lock))]
			 * Allocate a new device node referred to by a single link that
			 * is created within `target_directory', using `target_dirent'
			 * as INode directory entry.
			 * This function must initialize the following members of `target_dirent':
			 *    - de_fsdata (optionally, depending on filesystem implementation)
			 *    - de_pos
			 *    - de_ino
			 * This function must initialize the following members of `device_node':
			 *    - i_fileino (Same as `target_dirent->de_ino')
			 *    - i_type
			 *    - i_filenlink (To `>= 1')
			 *    - i_fsdata (Optionally; pre-initialized to `NULL')
			 * During this operation, the new directory entry should be
			 * constructed on-disk, or scheduled for such an allocation.
			 * NOTE: This function may also choose to set the `INODE_FCHANGED' flag
			 *       of `device_node', in which case the caller will add the node to
			 *       the set of changed nodes of the accompanying superblock, meaning
			 *       that filesystem implementations may choose to lazily set save
			 *       attributes of newly constructed nodes to disk once the disk
			 *       is supposed to be synchronized.
			 * @assume(device_node->db_refcnt == 1); (Exclusive user)
			 * @assume(device_node->i_flags & INODE_FATTRLOADED);
			 * @assume(device_node->i_super  == target_directory->i_super);
			 * @assume(S_ISBLK(device_node->i_filemode) || S_ISCHR(device_node->i_filemode));
			 * @assume(!directory_getentry(target_directory,target_dirent...));
			 * @assume(target_dirent->de_namelen != 0);
			 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_MKNOD:
			 *                                 [...] (Same as not implementing)
			 * @throw: E_FSERROR_ILLEGAL_PATH: [...]
			 * @throw: E_FSERROR_DISK_FULL:    [...]
			 * @throw: E_FSERROR_READONLY:     [...]
			 * @throw: E_IOERROR_BADBOUNDS:    Translated to `E_FSERROR_DISK_FULL'
			 * @throw: E_IOERROR_READONLY:     Translated to `E_FSERROR_READONLY'
			 * @throw: E_IOERROR:              Failed to read/write data to/from disk. */
			NONNULL((1, 2, 3))
			void (KCALL *d_mknod)(struct directory_node *__restrict target_directory,
			                      struct directory_entry *__restrict target_dirent,
			                      struct inode *__restrict device_node)
					THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ILLEGAL_PATH,
					       E_FSERROR_DISK_FULL, E_FSERROR_READONLY,
					       E_IOERROR_BADBOUNDS, E_IOERROR_READONLY,
					       E_IOERROR, ...);

			/* [0..1]
			 * [locked(WRITE(link_target))]
			 * [locked(WRITE(target_directory))]
			 * Construct a new hardlink to `link_target' as a new directory
			 * entry `target_dirent' within `target_directory'.
			 * This function must initialize the following members of `target_dirent':
			 *    - de_fsdata (optionally, depending on filesystem implementation)
			 *    - de_pos
			 * @assume(link_target->i_flags & INODE_FATTRLOADED);
			 * @assume(target_directory->i_super == link_target->i_super);
			 * @assume(!directory_getentry(target_directory,target_dirent...));
			 * @assume(target_dirent->de_namelen != 0);
			 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_LINK:
			 *                                 [...] (Same as not implementing)
			 * @throw: E_FSERROR_ILLEGAL_PATH: [...]
			 * @throw: E_FSERROR_DISK_FULL:    [...]
			 * @throw: E_FSERROR_READONLY:     [...]
			 * @throw: E_FSERROR_TOO_MANY_HARD_LINKS: [...]
			 * @throw: E_IOERROR_BADBOUNDS:    Translated to `E_FSERROR_DISK_FULL'
			 * @throw: E_IOERROR_READONLY:     Translated to `E_FSERROR_READONLY'
			 * @throw: E_IOERROR:              Failed to read/write data to/from disk. */
			NONNULL((1, 2, 3))
			void (KCALL *d_link)(struct directory_node *__restrict target_directory,
			                     struct directory_entry *__restrict target_dirent,
			                     struct inode *__restrict link_target)
					THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ILLEGAL_PATH,
					       E_FSERROR_DISK_FULL, E_FSERROR_READONLY,
					       E_FSERROR_TOO_MANY_HARD_LINKS,
					       E_IOERROR_BADBOUNDS, E_IOERROR_READONLY,
					       E_IOERROR, ...);

			/* [0..1]
			 * [locked(WRITE(target_directory))]
			 * [locked(WRITE(source_directory))]
			 * [locked(WRITE(source_node))]
			 * [locked(WRITE(source_node->i_super->s_nodes_lock))]
			 * Move the given `source_node' from one directory into another.
			 * This operation may construct a new INode for the target directory
			 * and have it inherit all data from the old node, in which case that
			 * new node must be returned, with the caller then marking `source_node'
			 * as deleted and removing it from the associated superblock's INode tree.
			 * Otherwise, a reference to `source_node' should be re-returned, and the
			 * caller will proceed to only remove `source_dirent' from `source_directory'
			 * (if it was created by something other than `o_lookup'), before adding
			 * `target_dirent' to the target directory (unless that directory implements
			 * the one-shot interface)
			 * NOTE: When a new INode is returned, `source_node' must
			 *       _NOT_ be marked as having changed by this function!
			 *
			 * This function must initialize the following members of `target_dirent':
			 *    - de_fsdata (optionally, depending on filesystem implementation)
			 *    - de_pos
			 *    - de_ino
			 *
			 * If the filesystem supports hardlinks, this operator can be left
			 * as `NULL', as it must then be possible to emulate it through use
			 * of `d_link(target_directory,target_dirent,source_node)', followed
			 * by `d_unlink(source_directory,source_dirent,source_node)'.
			 * NOTE: The invoked `d_rename' operator is always the one of `source_directory'
			 * @assume(INODE_ISDIR(source_directory));                                 // Source is a directory
			 * @assume(INODE_ISDIR(target_directory));                                 // Target is a directory
			 * @assume(source_directory->i_super == target_directory->i_super);        // Same superblocks
			 * @assume(!directory_getentry(target_directory,target_dirent...));        // The target doesn't contain an identical file
			 * @assume(source_dirent->de_namelen != 0);                                // Non-empty source name
			 * @assume(target_dirent->de_namelen != 0);                                // Non-empty target name
			 * @assume(!(source_node->i_flags & (INODE_FCHANGED|INODE_FATTRCHANGED))); // The source node is synced
			 * @assume(source_directory != target_directory || source_dirent != target_dirent); // The source and target locations differ
			 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_RENAME:
			 *                                 [...] (Same as not implementing)
			 * @throw: E_FSERROR_ILLEGAL_PATH: [...] (in `target_dirent')
			 * @throw: E_FSERROR_DISK_FULL:    [...]
			 * @throw: E_FSERROR_READONLY:     [...]
			 * @throw: E_IOERROR_BADBOUNDS:    Translated to `E_FSERROR_DISK_FULL'
			 * @throw: E_IOERROR_READONLY:     Translated to `E_FSERROR_READONLY'
			 * @throw: E_IOERROR:              Failed to read/write data to/from disk. */
			NONNULL((1, 2, 3, 4, 5))
			REF struct inode *(KCALL *d_rename)(struct directory_node *__restrict source_directory,
			                                    struct directory_entry *__restrict source_dirent,
			                                    struct directory_node *__restrict target_directory,
			                                    struct directory_entry *__restrict target_dirent,
			                                    struct inode *__restrict source_node)
					THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ILLEGAL_PATH,
					       E_FSERROR_DISK_FULL, E_FSERROR_READONLY,
					       E_IOERROR_BADBOUNDS, E_IOERROR_READONLY,
					       E_IOERROR, ...);

			/* [0..1]
			 * [locked(WRITE(containing_directory))]
			 * [locked(WRITE(node_to_unlink))]
			 * Unlink a given `node_to_unlink' from `containing_entry' in `containing_directory'.
			 * NOTE: The given `containing_entry' may be another directory,
			 *       in which case the caller is responsible to ensure that
			 *      `i_filenlink' is greater than ZERO(0).
			 * NOTE: This function is not responsible to deallocate file data
			 *       allocated for the INode. If the INode has a non-ZERO(0)
			 *       `i_filesize' value prior to the caller choosing to invoke
			 *       this operator, the `f_truncate' operator will be invoked
			 *       first, making it its responsibility to deallocate any file
			 *       data associated with the INode before it goes away.
			 * NOTE: Upon success, this function must decrement `i_filenlink'.
			 * @assume(containing_entry->i_filesize == 0);
			 * @assume(INODE_ISDIR(containing_directory));
			 * @assume(containing_entry->de_namelen != 0);
			 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_UNLINK:
			 *                                 [...] (Same as not implementing)
			 * @throw: E_FSERROR_READONLY:     [...]
			 * @throw: E_IOERROR_READONLY:     Translated to `E_FSERROR_READONLY'
			 * @throw: E_IOERROR:              Failed to read/write data to/from disk. */
			NONNULL((1, 2, 3))
			void (KCALL *d_unlink)(struct directory_node *__restrict containing_directory,
			                       struct directory_entry *__restrict containing_entry,
			                       struct inode *__restrict node_to_unlink)
					THROWS(E_FSERROR_UNSUPPORTED_OPERATION,
					       E_FSERROR_READONLY, E_IOERROR_READONLY,
					       E_IOERROR, ...);

			/* [0..1]
			 * [locked(WRITE(containing_directory))]
			 * [locked(WRITE(node_to_unlink))]
			 * Same as `d_unlink', but called when `node_to_unlink' is a directory.
			 * @assume(IS_EMPTY_DIRECTORY_EXCEPT_FOR_PARENT_AND_SELF_LINKS(containing_entry))
			 * @assume(node_to_unlink->i_filenlink == 1); // Last link (Must be decremented upon success)
			 * @assume(node_to_unlink->d_size      == 2); // Only special directory entries are remaining.
			 * @assume(containing_entry->de_namelen != 0);
			 * @assume(INODE_ISDIR(containing_directory));
			 * @assume(INODE_ISDIR(node_to_unlink));
			 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_RMDIR:
			 *                                 [...] (Same as not implementing)
			 * @throw: E_FSERROR_READONLY:     [...]
			 * @throw: E_IOERROR_READONLY:     Translated to `E_FSERROR_READONLY'
			 * @throw: E_IOERROR:              Failed to read/write data to/from disk. */
			NONNULL((1, 2, 3))
			void (KCALL *d_rmdir)(struct directory_node *__restrict containing_directory,
			                      struct directory_entry *__restrict containing_entry,
			                      struct directory_node *__restrict node_to_unlink)
					THROWS(E_FSERROR_UNSUPPORTED_OPERATION,
					       E_FSERROR_READONLY, E_IOERROR_READONLY,
					       E_IOERROR, ...);

		} it_directory;

		struct {
			/* [0..1][locked(WRITE(self))]
			 * Load the link text of the given symlink node.
			 * This operator must fill in the following members of `self':
			 *   - sl_text
			 *   - i_filesize  (to the intended `strlen(sl_text)')
			 * NOTE: When this operator isn't implemented, `sl_readlink_dynamic'
			 *       _MUST_ be implemented instead.
			 * @throw: E_BADALLOC: Insufficient memory to allocate the node text.
			 * @throw: E_IOERROR:  Failed to read data from disk. */
			NONNULL((1))
			void (KCALL *sl_readlink)(struct symlink_node *__restrict self)
					THROWS(E_BADALLOC, E_IOERROR, ...);

			/* [if(sl_readlink == NULL,[1..1]) else([0..1])]
			 * [locked(READ(self))]
			 * Used when `sl_readlink' isn't implemented to dynamically generate
			 * the symlink text of a given INode. This operator is used by symlinks
			 * that can arbitrarily change their text, or who's text depends on the
			 * calling thread (e.g. `/proc/self')
			 * NOTE: This function is not required to append a terminating NUL-character,
			 *       and even if it does, it mustn't include its memory requirement in
			 *       the required buffer size returned.
			 * @return: * : The required buffer size. (EXCLUDING a terminating
			 *              NUL-character that can even be OMITTED)
			 * @throw: E_SEGFAULT: The given user-buffer is faulty.
			 * @throw: E_IOERROR:  Failed to read data from disk. */
			NONNULL((1))
			size_t (KCALL *sl_readlink_dynamic)(struct symlink_node *__restrict self,
			                                    USER CHECKED /*utf-8*/char *buf,
			                                    size_t bufsize)
					THROWS(E_SEGFAULT, E_IOERROR, ...);
		} it_symlink;
	};
};
#endif /* __CC__ */


#define INODE_FNORMAL      0x0000 /* Normal INode flags. */
#define INODE_FPERSISTENT  0x0001 /* [const] This INode is persistent and must not be unloaded in order to
                                   * free available memory. While INodes of regular file systems, such as
                                   * FAT or EXT2 can simply be saved and unloaded once no longer used
                                   * anywhere but by the associated superblock, RAM-based file systems,
                                   * such as DEVFS keep all of their data in memory, meaning that they
                                   * must set this flag for their nodes.
                                   *  - When set, the associated superblock's INODE table holds a reference
                                   *    to this INode, thereby (intentionally) causing a reference loop due
                                   *    to `self->i_super->INODE_TABLE->self'
                                   *  - As a consequence the this, when unlinking the INode, it is also
                                   *    necessary to decrement the INode's reference counter after it has
                                   *    been removed from the superblock's INODE table. */
#define INODE_FCHANGED     0x0002 /* The INode's file contents (as cached through the underlying datablock's
                                   * data parts) have changed. - This flag, as well as `INODE_FATTRCHANGED'
                                   * are atomically set in order to safely insert the node into the chain of
                                   * changed nodes found in its superblock. */
#define INODE_FATTRCHANGED 0x0004 /* Similar to `INODE_FCHANGED', but indicates that only the node's
                                   * attributes (size, time stamps, permissions, etc.) have changed.
                                   * This flag is set atomically in conjunction with the node being chained
                                   * to the list of changed nodes found in the superblock. (s.a. `i_changed_next') */
#define INODE_FATTRLOADED  0x0008 /* [lock(WRITE_ONCE)] The node's attributes have been loaded. */
#define INODE_FDIRLOADED   0x0010 /* [lock(WRITE_ONCE)] The entires of a directory INode has been fully loaded. */
#define INODE_FLNKLOADED   0x0010 /* [lock(WRITE_ONCE)] A symbolic link node's text has been loaded. */
#define INODE_FDELETED     0x8000 /* FLAG: The INode has been deleted.
                                   * When this flag is set, it is illegal to set any of the following flags:
                                   *  - INODE_FCHANGED
                                   *  - INODE_FATTRCHANGED
                                   * Additionally, it is illegal to perform any of the following operations,
                                   * with the addition that the INode no longer appears, or is currently being
                                   * removed from its containing directory, as well as the VFS dentry cache:
                                   *  - read(2)
                                   *  - write(2)
                                   *  - truncate(2)
                                   *  - mmap(2)
                                   * Attempting do use them anyways will cause `E_FSERROR_DELETED' to be thrown.
                                   * NOTE: This flag is set atomically, and is checked before any kind of operation
                                   *       is performed on the node, thus allowing it to prevent any such operation
                                   *       from occurring in the future. */
#define INODE_FSUPERDEL    0x4000 /* Set alongside `INODE_FDELETED' when the INode was closed because of the
                                   * superblock being unmounted, when `superblock_set_unmounted()' was called.
                                   * If `superblock_set_unmounted()' then fails to synchronize outstanding changes,
                                   * nodes with this bit set will have their `INODE_FDELETED' flags cleared again. */



#ifdef __CC__
struct inode
#if defined(__cplusplus) && !defined(CONFIG_WANT_FS_AS_STRUCT)
	: vm_datablock
#endif
{
#if !defined(__cplusplus) || defined(CONFIG_WANT_FS_AS_STRUCT)
#define __inode_as_datablock(x) (&(x)->i_datablock)
	struct vm_datablock i_datablock;    /* The underlying data-block. */
#else
#define __inode_as_datablock(x)   (x)
#endif
	struct inode_type  *i_type;         /* [1..1][const] INode type. */
	REF struct superblock *i_super;     /* [1..1][const][REF_IF(!= this)] The associated superblock. */
	struct inode_data  *i_fsdata;       /* [?..?][lock(this)] A pointer to inode-specific user-data. */
	size_t              i_heapsize;     /* [1..1][const] Allocated heap size of this INode. */
	uintptr_t           i_flags;        /* INode flags (Set of `INODE_F*'). */
	WEAK REF struct inode
	                   *i_changed_next; /* [0..1] Next changed INode (chained through `i_super->s_changed'). */
	LLIST_NODE(REF struct inode)
	                    i_recent;       /* [0..1][lock(INTERNAL(inodes_recent_lock))]
	                                     * Chain of recently used INodes. */
	ATREE_NODE_SINGLE(struct inode,ino_t)
	                    i_filetree;     /* File tree. */
#ifdef __INTELLISENSE__
	ino_t               i_fileino;      /* [const] File INode number (used to unambiguously identify an INode).
	                                     * NOTE: This chain holds a reference to nodes with the `INODE_FPERSISTENT' flag set. */
#else
#define i_fileino       i_filetree.a_vaddr
#endif
	pos_t               i_filesize;     /* [lock(.)][valid_if(INODE_FATTRLOADED)] Size of the file (in bytes)
	                                     * NOTE: Before `INODE_FATTRLOADED' is set, this field is set to ZERO(0)! */
	mode_t              i_filemode;     /* [lock(.)][valid_if(INODE_FATTRLOADED)][const(MASK(S_IFMT))]
	                                     * File type and permissions (see `S_*' above).
	                                     * NOTE: The bits masked by `S_IFMT' are always valid and constant. */
	nlink_t             i_filenlink;    /* [lock(.)][valid_if(INODE_FATTRLOADED)]
	                                     * Link counter of this INode.
	                                     * When this counter reaches ZERO(0), data of the node is
	                                     * deleted and the node can no longer be operated upon. */
	uid_t               i_fileuid;      /* [lock(.)][valid_if(INODE_FATTRLOADED)] File user ID */
	gid_t               i_filegid;      /* [lock(.)][valid_if(INODE_FATTRLOADED)] File group ID */
	struct timespec     i_fileatime;    /* [lock(.)][valid_if(INODE_FATTRLOADED)] Last accessed time. */
	struct timespec     i_filemtime;    /* [lock(.)][valid_if(INODE_FATTRLOADED)] Last modified time. */
	struct timespec     i_filectime;    /* [lock(.)][valid_if(INODE_FATTRLOADED)] File creation time. */
	dev_t               i_filerdev;     /* [lock(.)][valid_if(INODE_FATTRLOADED && S_ISDEV(i_filemode))] Referenced device number. */
};

#define INODE_ISSUPER(x) ((x)->i_super == (struct superblock *)(x)) /* Check if `x' is actually a superblock root directory node. */
#define INODE_ISREG(x)   S_ISREG((x)->i_filemode) /* Check if `x' is a `struct regular_node' */
#define INODE_ISDIR(x)   S_ISDIR((x)->i_filemode) /* Check if `x' is a `struct directory_node' */
#define INODE_ISLNK(x)   S_ISLNK((x)->i_filemode) /* Check if `x' is a `struct symlink_node' */


#if !defined(__INTELLISENSE__) || \
    !defined(__cplusplus) || defined(CONFIG_WANT_FS_AS_STRUCT)

/* When locking an INode, it is no longer unlikely that that Inode is devfs.
 * For this reason, re-define sync functions for INodes to explicitly get
 * rid of the unlikely() for the DEVFS comparison. */
#define inode_lock_read(self)       (__inode_as_datablock(self) == &__devfs_datablock ? devfs_lock_read()       : (void)rwlock_read(&__inode_as_datablock(self)->db_lock))
#define inode_lock_write(self)      (__inode_as_datablock(self) == &__devfs_datablock ? devfs_lock_write()      : (void)rwlock_write(&__inode_as_datablock(self)->db_lock))
#define inode_lock_upgrade(self)    (__inode_as_datablock(self) == &__devfs_datablock ? devfs_lock_upgrade()    : rwlock_upgrade(&__inode_as_datablock(self)->db_lock))
#define inode_lock_read_nx(self)    (__inode_as_datablock(self) == &__devfs_datablock ? devfs_lock_read_nx()    : rwlock_read_nx(&__inode_as_datablock(self)->db_lock))
#define inode_lock_write_nx(self)   (__inode_as_datablock(self) == &__devfs_datablock ? devfs_lock_write_nx()   : rwlock_write_nx(&__inode_as_datablock(self)->db_lock))
#define inode_lock_upgrade_nx(self) (__inode_as_datablock(self) == &__devfs_datablock ? devfs_lock_upgrade_nx() : rwlock_upgrade_nx(&__inode_as_datablock(self)->db_lock))
#define inode_lock_tryread(self)    (__inode_as_datablock(self) == &__devfs_datablock ? devfs_lock_tryread()    : rwlock_tryread(&__inode_as_datablock(self)->db_lock))
#define inode_lock_trywrite(self)   (__inode_as_datablock(self) == &__devfs_datablock ? devfs_lock_trywrite()   : rwlock_trywrite(&__inode_as_datablock(self)->db_lock))
#define inode_lock_tryupgrade(self) (__inode_as_datablock(self) == &__devfs_datablock ? devfs_lock_tryupgrade() : rwlock_tryupgrade(&__inode_as_datablock(self)->db_lock))
#define inode_lock_endwrite(self)   (__inode_as_datablock(self) == &__devfs_datablock ? devfs_lock_endwrite()   : rwlock_endwrite(&__inode_as_datablock(self)->db_lock))
#define inode_lock_endread(self)    (__inode_as_datablock(self) == &__devfs_datablock ? devfs_lock_endread()    : rwlock_endread(&__inode_as_datablock(self)->db_lock))
#define inode_lock_end(self)        (__inode_as_datablock(self) == &__devfs_datablock ? devfs_lock_end()        : rwlock_end(&__inode_as_datablock(self)->db_lock))
#define inode_lock_downgrade(self)  (__inode_as_datablock(self) == &__devfs_datablock ? devfs_lock_downgrade()  : rwlock_downgrade(&__inode_as_datablock(self)->db_lock))
#define inode_lock_reading(self)    rwlock_reading(&__inode_as_datablock(self)->db_lock)
#define inode_lock_writing(self)    rwlock_writing(&__inode_as_datablock(self)->db_lock)
#define inode_lock_canread(self)    rwlock_canread(&__inode_as_datablock(self)->db_lock)
#define inode_lock_canwrite(self)   rwlock_canwrite(&__inode_as_datablock(self)->db_lock)
#define inode_lock_pollread(self)   rwlock_pollread(&__inode_as_datablock(self)->db_lock)
#define inode_lock_pollwrite(self)  rwlock_pollwrite(&__inode_as_datablock(self)->db_lock)
__DEFINE_SYNC_RWLOCK(struct inode,
                     inode_lock_tryread,
                     inode_lock_read,
                     inode_lock_read_nx,
                     inode_lock_endread,
                     inode_lock_reading,
                     inode_lock_canread,
                     inode_lock_trywrite,
                     inode_lock_write,
                     inode_lock_write_nx,
                     inode_lock_endwrite,
                     inode_lock_writing,
                     inode_lock_canwrite,
                     inode_lock_end,
                     inode_lock_tryupgrade,
                     inode_lock_upgrade,
                     inode_lock_upgrade_nx,
                     inode_lock_downgrade)
__DEFINE_SYNC_POLL(struct inode,
                   inode_lock_pollread,
                   inode_lock_pollwrite)
#endif /* !__INTELLISENSE__ */





struct directory_entry {
	WEAK refcnt_t                      de_refcnt;  /* Reference counter for this data structure. */
	size_t                             de_heapsize;/* [const] Allocated heap size. */
	struct directory_entry            *de_next;    /* [0..1][lock(this)] Next directory entry with the same hash. */
	LLIST_NODE(struct directory_entry) de_bypos;   /* [lock(this)] Chain of directory entires, sorted by their in-directory position.
	                                                * NOTE: When a directory entry is removed, this link is set to NULL,
	                                                *       meaning that enumerating a directory is as simple as taking
	                                                *      `:d_bypos' of the directory node while holding `this'
	                                                *       and acquire a reference.
	                                                *       Then to continue enumeration, simply re-acquire the `this'
	                                                *       lock and traverse the `de_bypos' chain, stopping when NULL is encountered.
	                                                *       When `NULL' is encountered, you may check if your current node
	                                                *       is `d_bypos_end'. If it isn't, enumeration was halted because your
	                                                *       current node was deleted. It it was, make use of a secondary entry
	                                                *       index you've been keeping track of to skip to the next entry.
	                                                * NOTE: If you reach EOF normally, check the `INODE_FDIRLOADED' flag to see
	                                                *       if additional directory entries exist that haven't been loaded yet. */
	struct ATTR_PACKED { /* Optional, filesystem-specific data. */
		pos_t                         de_start;   /* [const][valid_if(?)]
		                                           * Filesystem-specific starting position of data for this directory entry.
		                                           * Filesystem where the actual name of the file is located before the its
		                                           * data block (such as FAT's long file names), use this to point to the
		                                           * start of such data.
		                                           * NOTE: The filesystem is allowed to use this location for whatever it chooses. */
		unsigned char                 de_data[16];/* Arbitrary, filesystem-specific data. (in FAT, this is the 8.3 version of the filename) */
	}                                 de_fsdata;
	pos_t                             de_pos;     /* [const] Filesystem-specific position with the INode's data
	                                               *         block where data for this directory entry can be found. */
	ino_t                             de_ino;     /* [const] INode number of this directory entry. */
	uintptr_t                         de_hash;    /* [const] Hash of this directory entry. */
	u16                               de_namelen; /* [const][!0] Length of the directory entry name (in characters). */
	unsigned char                     de_type;    /* [const] Directory entry type (one of `DT_*') */
	COMPILER_FLEXIBLE_ARRAY(/*utf-8*/char, de_name); /* [const][de_namelen] Directory entry name. (NUL-terminated) */
};

DATDEF struct directory_entry empty_directory_entry;

FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL directory_entry_destroy)(struct directory_entry *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct directory_entry, de_refcnt, directory_entry_destroy)

/* Allocate a new directory entry.
 * The caller must still initialize:
 *   - de_next
 *   - de_bypos
 *   - de_fsdata (as needed)
 *   - de_pos
 *   - de_ino
 *   - de_hash   (`directory_entry_alloc' only)
 *   - de_type
 *   - de_name   (`directory_entry_alloc' only)
 * NOTE: These functions will have already ensured that
 *       `return->de_name[namelen] == '\0''
 */
FUNDEF ATTR_MALLOC ATTR_RETNONNULL WUNUSED REF struct directory_entry *KCALL
directory_entry_alloc(u16 namelen) THROWS(E_BADALLOC);
FUNDEF ATTR_MALLOC ATTR_RETNONNULL NONNULL((1)) WUNUSED REF struct directory_entry *KCALL
directory_entry_alloc_s(USER CHECKED /*utf-8*/char const *name, u16 namelen) THROWS(E_BADALLOC,E_SEGFAULT);



/* Return the hash of a given directory entry name.
 * @throw: E_SEGFAULT: Failed to access the given `name'. */
FUNDEF WUNUSED NONNULL((1)) uintptr_t KCALL
directory_entry_hash(CHECKED USER /*utf-8*/char const *__restrict name, u16 namelen)
		THROWS(E_SEGFAULT);
#define DIRECTORY_ENTRY_EMPTY_HASH 0 /* == directory_entry_hash("",0) */



struct module;
struct regular_node
#if defined(__cplusplus) && !defined(CONFIG_WANT_FS_AS_STRUCT)
	: inode
#endif
{
#if !defined(__cplusplus) || defined(CONFIG_WANT_FS_AS_STRUCT)
	struct inode     r_node;        /* [OVERRIDE(.i_filemode,[S_ISREF(.)])]
	                                 * [OVERRIDE(.i_filerdev,[== 0])]
	                                 * The underlying node. */
#endif
};

#if !defined(__cplusplus) || defined(CONFIG_WANT_FS_AS_STRUCT)
__DEFINE_SYNC_PROXY(struct regular_node,r_node)
#endif



#define DIRECTORY_DEFAULT_MASK  7
struct directory_node
#if defined(__cplusplus) && !defined(CONFIG_WANT_FS_AS_STRUCT)
	: inode
#endif
{
	/* Directory INode (When `S_ISDIR(a_mode)' is true) */
#if !defined(__cplusplus) || defined(CONFIG_WANT_FS_AS_STRUCT)
	struct inode                 d_node;     /* [OVERRIDE(.i_filemode,[S_ISDIR(.)])]
	                                          * [OVERRIDE(.i_filerdev,[== 0])]
	                                          * The underlying node. */
#endif
	REF struct directory_node   *d_parent;   /* [0..1][const] Parent directory (or `NULL' for the superblock root). */
	pos_t                        d_dirend;   /* [lock(this)] Starting address of the next directory entry which hasn't been read yet. */
	size_t                       d_size;     /* [lock(this)] Amount of directory entries. */
	size_t                       d_mask;     /* [!0][lock(this)] Allocated directory entry hash-map mask. */
	REF struct directory_entry **d_map;      /* [0..1][lock(this)][1..d_mask+1][owned] Hash-map of directory entries. */
	struct directory_entry      *d_bypos;    /* [lock(this)][0..1] Chain of all known directory entries, ordered by address. */
	struct directory_entry      *d_bypos_end;/* [lock(this)][0..1] Last directory entry that marks the end of the directory. */
};

#if !defined(__cplusplus) || defined(CONFIG_WANT_FS_AS_STRUCT)
__DEFINE_SYNC_PROXY(struct directory_node,d_node)
#endif


struct symlink_node
#if defined(__cplusplus) && !defined(CONFIG_WANT_FS_AS_STRUCT)
	: inode
#endif
{
	/* Symbolic link INode (When `S_ISLNK(a_mode)' is true) */
#if !defined(__cplusplus) || defined(CONFIG_WANT_FS_AS_STRUCT)
	struct inode          sl_node; /* [OVERRIDE(.i_filemode,[S_ISLNK(.)])]
	                                * [OVERRIDE(.i_filesize,[const])]
	                                * [OVERRIDE(.i_filerdev,[== 0])]
	                                * The underlying node. */
#endif
	KERNEL /*utf-8*/char *sl_text; /* [0..i_filesize][owned_if(!= sl_stext)]
	                                * [valid_if(INODE_FLNKLOADED)] Symbolic link text.
	                                * NOTE: Not required to be NUL-terminated! */
	COMPILER_FLEXIBLE_ARRAY(/*utf-8*/char,sl_stext); /* Inline-text. */
};

#if !defined(__cplusplus) || defined(CONFIG_WANT_FS_AS_STRUCT)
__DEFINE_SYNC_PROXY(struct symlink_node,sl_node)
#endif


/* The data block type used to identify INodes. */
DATDEF struct vm_datablock_type inode_datablock_type;

/* Check if a given `struct vm_datablock *x' is an INode. */
#define vm_datablock_isinode(x) ((x)->db_type == &inode_datablock_type)


/* Indicate that `self' has been used recently, allowing the INode to be cached
 * such that it will remain allocated for a while, even when not referenced elsewhere. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL inode_recent)(struct inode *__restrict self);

/* Clear the cache of recently used INodes. */
FUNDEF size_t KCALL inode_recent_clear(void) THROWS(E_WOULDBLOCK);
FUNDEF size_t NOTHROW(KCALL inode_recent_clear_nx)(void);
FUNDEF NOBLOCK size_t NOTHROW(KCALL inode_recent_tryclear)(void);

/* Try to remove the given INode `self' from the recent-cache.
 * @return: * : One of `INODE_RECENT_TRYREMOVE_*' */
FUNDEF NOBLOCK unsigned int
NOTHROW(KCALL inode_recent_tryremove)(struct inode *__restrict self);
#define INODE_RECENT_TRYREMOVE_SUCCESS    0 /* Successfully removed `self' from the cache. */
#define INODE_RECENT_TRYREMOVE_NOTRECENT  1 /* The given INode was not cached as recent. */
#define INODE_RECENT_TRYREMOVE_WOULDBLOCK 2 /* The operation would have blocked. */

/* Return the number of INodes current stored within the recent-cache. */
FUNDEF NOBLOCK size_t NOTHROW(KCALL inode_recent_getcur)(void);

/* [lock(atomic)] Max number of INodes to keep cached as recent */
DATDEF WEAK size_t inodes_recent_lim;

/* Read/write data to/from the given INode.
 * NOTE: These functions automatically do everything required to safely read/modify
 *       INode data, searching through the memory mapping cache containing all of the
 *       node's possible data parts, as well as creating missing parts and unsharing
 *       copy-on-write mappings when writing.
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_READ: [...]
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_WRITE: [...]
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_TRUNC: [...] (When trying to extend a file by using `write()')
 * @throw: E_FSERROR_DISK_FULL:             [...]
 * @throw: E_FSERROR_READONLY:              [...]
 * @throw: E_IOERROR:                       [...] */
FUNDEF NONNULL((1, 2)) size_t KCALL inode_readk(struct inode *__restrict self, void *__restrict dst, size_t num_bytes, pos_t file_position) THROWS_INDIRECT(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_IOERROR,E_SEGFAULT,...);
FUNDEF NONNULL((1)) size_t KCALL inode_read(struct inode *__restrict self, CHECKED USER void *dst, size_t num_bytes, pos_t file_position) THROWS(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_IOERROR,E_SEGFAULT,...);
FUNDEF NONNULL((1)) size_t KCALL inode_read_phys(struct inode *__restrict self, vm_phys_t dst, size_t num_bytes, pos_t file_position) THROWS(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_IOERROR,...);
FUNDEF NONNULL((1, 2)) size_t KCALL inode_readv(struct inode *__restrict self, struct aio_buffer *__restrict buf, size_t num_bytes, pos_t file_position) THROWS(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_IOERROR,E_SEGFAULT,...);
FUNDEF NONNULL((1, 2)) size_t KCALL inode_readv_phys(struct inode *__restrict self, struct aio_pbuffer *__restrict buf, size_t num_bytes, pos_t file_position) THROWS(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_IOERROR,E_SEGFAULT,...);
FUNDEF NONNULL((1, 2)) void KCALL inode_writek(struct inode *__restrict self, void const *__restrict dst, size_t num_bytes, pos_t file_position) THROWS_INDIRECT(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_IOERROR,E_SEGFAULT,...);
FUNDEF NONNULL((1)) void KCALL inode_write(struct inode *__restrict self, CHECKED USER void const *src, size_t num_bytes, pos_t file_position) THROWS(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_FSERROR_DISK_FULL,E_FSERROR_READONLY,E_IOERROR,E_SEGFAULT,...);
FUNDEF NONNULL((1)) void KCALL inode_write_phys(struct inode *__restrict self, vm_phys_t src, size_t num_bytes, pos_t file_position) THROWS(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_FSERROR_DISK_FULL,E_FSERROR_READONLY,E_IOERROR,...);
FUNDEF NONNULL((1, 2)) void KCALL inode_writev(struct inode *__restrict self, struct aio_buffer *__restrict buf, size_t num_bytes, pos_t file_position) THROWS(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_FSERROR_DISK_FULL,E_FSERROR_READONLY,E_IOERROR,E_SEGFAULT,...);
FUNDEF NONNULL((1, 2)) void KCALL inode_writev_phys(struct inode *__restrict self, struct aio_pbuffer *__restrict buf, size_t num_bytes, pos_t file_position) THROWS(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_FSERROR_DISK_FULL,E_FSERROR_READONLY,E_IOERROR,E_SEGFAULT,...);
FUNDEF NONNULL((1, 2, 5)) size_t NOTHROW(KCALL inode_areadk)(struct inode *__restrict self, void *__restrict dst, size_t num_bytes, pos_t file_position, struct aio_multihandle *__restrict aio) THROWS_INDIRECT(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_IOERROR,E_SEGFAULT,...);
FUNDEF NONNULL((1, 5)) size_t NOTHROW(KCALL inode_aread)(struct inode *__restrict self, CHECKED USER void *dst, size_t num_bytes, pos_t file_position, struct aio_multihandle *__restrict aio) THROWS_INDIRECT(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_IOERROR,E_SEGFAULT,...);
FUNDEF NONNULL((1, 5)) size_t NOTHROW(KCALL inode_aread_phys)(struct inode *__restrict self, vm_phys_t dst, size_t num_bytes, pos_t file_position, struct aio_multihandle *__restrict aio) THROWS_INDIRECT(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_IOERROR,...);
FUNDEF NONNULL((1, 2, 5)) size_t NOTHROW(KCALL inode_areadv)(struct inode *__restrict self, struct aio_buffer *__restrict buf, size_t num_bytes, pos_t file_position, struct aio_multihandle *__restrict aio) THROWS_INDIRECT(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_IOERROR,E_SEGFAULT,...);
FUNDEF NONNULL((1, 2, 5)) size_t NOTHROW(KCALL inode_areadv_phys)(struct inode *__restrict self, struct aio_pbuffer *__restrict buf, size_t num_bytes, pos_t file_position, struct aio_multihandle *__restrict aio) THROWS_INDIRECT(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_IOERROR,E_SEGFAULT,...);
FUNDEF NONNULL((1, 2, 5)) void NOTHROW(KCALL inode_awritek)(struct inode *__restrict self, void const *__restrict dst, size_t num_bytes, pos_t file_position, struct aio_multihandle *__restrict aio) THROWS_INDIRECT(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_IOERROR,E_SEGFAULT,...);
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL inode_awrite)(struct inode *__restrict self, CHECKED USER void const *src, size_t num_bytes, pos_t file_position, struct aio_multihandle *__restrict aio) THROWS_INDIRECT(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_FSERROR_DISK_FULL,E_FSERROR_READONLY,E_IOERROR,E_SEGFAULT,...);
FUNDEF NONNULL((1, 5)) void NOTHROW(KCALL inode_awrite_phys)(struct inode *__restrict self, vm_phys_t src, size_t num_bytes, pos_t file_position, struct aio_multihandle *__restrict aio) THROWS_INDIRECT(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_FSERROR_DISK_FULL,E_FSERROR_READONLY,E_IOERROR,...);
FUNDEF NONNULL((1, 2, 5)) void NOTHROW(KCALL inode_awritev)(struct inode *__restrict self, struct aio_buffer *__restrict buf, size_t num_bytes, pos_t file_position, struct aio_multihandle *__restrict aio) THROWS_INDIRECT(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_FSERROR_DISK_FULL,E_FSERROR_READONLY,E_IOERROR,E_SEGFAULT,...);
FUNDEF NONNULL((1, 2, 5)) void NOTHROW(KCALL inode_awritev_phys)(struct inode *__restrict self, struct aio_pbuffer *__restrict buf, size_t num_bytes, pos_t file_position, struct aio_multihandle *__restrict aio) THROWS_INDIRECT(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION,E_FSERROR_DISK_FULL,E_FSERROR_READONLY,E_IOERROR,E_SEGFAULT,...);
/* Same as `inode_read()', but throw an `E_IOERROR_BADBOUNDS' error if not all data could be read. */
FUNDEF NONNULL((1, 2)) void KCALL inode_readallk(struct inode *__restrict self, void *__restrict dst, size_t num_bytes, pos_t file_position) THROWS(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR_BADBOUNDS,E_IOERROR,E_SEGFAULT,...);
FUNDEF NONNULL((1)) void KCALL inode_readall(struct inode *__restrict self, CHECKED USER void *dst, size_t num_bytes, pos_t file_position) THROWS(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR_BADBOUNDS,E_IOERROR,E_SEGFAULT,...);
FUNDEF NONNULL((1)) void KCALL inode_readall_phys(struct inode *__restrict self, vm_phys_t dst, size_t num_bytes, pos_t file_position) THROWS(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR_BADBOUNDS,E_IOERROR,...);
FUNDEF NONNULL((1, 2)) void KCALL inode_readallv(struct inode *__restrict self, struct aio_buffer *__restrict buf, size_t num_bytes, pos_t file_position) THROWS(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR_BADBOUNDS,E_IOERROR,E_SEGFAULT,...);
FUNDEF NONNULL((1, 2)) void KCALL inode_readallv_phys(struct inode *__restrict self, struct aio_pbuffer *__restrict buf, size_t num_bytes, pos_t file_position) THROWS(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR_BADBOUNDS,E_IOERROR,E_SEGFAULT,...);
FUNDEF NONNULL((1, 2)) void NOTHROW(KCALL inode_areadallk)(struct inode *__restrict self, void *__restrict dst, size_t num_bytes, pos_t file_position, struct aio_multihandle *__restrict aio) THROWS_INDIRECT(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR_BADBOUNDS,E_IOERROR,E_SEGFAULT,...);
FUNDEF NONNULL((1)) void NOTHROW(KCALL inode_areadall)(struct inode *__restrict self, CHECKED USER void *dst, size_t num_bytes, pos_t file_position, struct aio_multihandle *__restrict aio) THROWS_INDIRECT(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR_BADBOUNDS,E_IOERROR,E_SEGFAULT,...);
FUNDEF NONNULL((1)) void NOTHROW(KCALL inode_areadall_phys)(struct inode *__restrict self, vm_phys_t dst, size_t num_bytes, pos_t file_position, struct aio_multihandle *__restrict aio) THROWS_INDIRECT(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR_BADBOUNDS,E_IOERROR,...);
FUNDEF NONNULL((1, 2)) void NOTHROW(KCALL inode_areadallv)(struct inode *__restrict self, struct aio_buffer *__restrict buf, size_t num_bytes, pos_t file_position, struct aio_multihandle *__restrict aio) THROWS_INDIRECT(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR_BADBOUNDS,E_IOERROR,E_SEGFAULT,...);
FUNDEF NONNULL((1, 2)) void NOTHROW(KCALL inode_areadallv_phys)(struct inode *__restrict self, struct aio_pbuffer *__restrict buf, size_t num_bytes, pos_t file_position, struct aio_multihandle *__restrict aio) THROWS_INDIRECT(E_FSERROR_DELETED,E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR_BADBOUNDS,E_IOERROR,E_SEGFAULT,...);

/* Same as the read functions above, but if no data could be read (because the read
 * happened to be performed beyond the file's allocated size), block until data can be read.
 * If some data could be read (regardless of how much), do not block, and return even
 * when `return < num_bytes'.
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION: [...]
 * @throw: E_FSERROR_DISK_FULL:             [...]
 * @throw: E_FSERROR_READONLY:              [...]
 * @throw: E_IOERROR:                       [...] */
FUNDEF NONNULL((1, 2)) size_t KCALL
inode_read_blocking(struct inode *__restrict self,
                    CHECKED USER void *dst,
                    size_t num_bytes, pos_t file_position)
		THROWS(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) size_t KCALL
inode_pread_blocking(struct inode *__restrict self, vm_phys_t dst,
                     size_t num_bytes, pos_t file_position)
		THROWS(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...);
FUNDEF NONNULL((1)) size_t KCALL
inode_readv_blocking(struct inode *__restrict self,
                     struct aio_buffer *__restrict buf,
                     size_t num_bytes, pos_t file_position)
		THROWS(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) size_t KCALL
inode_preadv_blocking(struct inode *__restrict self,
                      struct aio_pbuffer *__restrict buf,
                      size_t num_bytes, pos_t file_position)
		THROWS(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...);

/* Atomically set the `INODE_FCHANGED' or `INODE_FATTRCHANGED' flags
 * and chain the node as part of the associated superblock's list of
 * changed INodes.
 * @param: what:   Set of `INODE_FCHANGED|INODE_FATTRCHANGED',
 *                 of which at least one must be given.
 * @return: true:  Successfully marked the INode for having been changed,
 *                 or the node had already been scheduled as having been
 *                 changed.
 * @return: false: The `INODE_FDELETED' bit has been set for `self' */
FUNDEF NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL inode_changed)(struct inode *__restrict self,
                             uintptr_t what DFL(INODE_FCHANGED));
FORCELOCAL NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL inode_changedattr)(struct inode *__restrict self) {
	return inode_changed(self, INODE_FATTRCHANGED);
}

/* Same as `inode_changed()', but the caller is required to be holding
 * a lock on `self', whilst this function will also update the file's
 * modified timestamp, before setting both `INODE_FCHANGED|INODE_FATTRCHANGED'
 * bits the same way a call to `inode_changed(self,INODE_FCHANGED|INODE_FATTRCHANGED)'
 * would. */
FUNDEF NONNULL((1)) bool KCALL
inode_changed_chmtime(struct inode *__restrict self);

/* Ensure that attributes have been loaded for the given INode.
 * Upon return, it is guarantied that the `INODE_FATTRLOADED' flag will be set. */
FUNDEF NONNULL((1)) void KCALL
inode_loadattr(struct inode *__restrict self)
		THROWS(E_IOERROR, ...);


/* Assert that the calling thread is allowed to access the given
 * the specified file, throwing an `E_FSERROR_ACCESS_DENIED' if not.
 * @param: type: Set of `R_OK | W_OK | X_OK' */
FUNDEF NONNULL((1)) void KCALL
inode_access(struct inode *__restrict self, unsigned int type)
		THROWS(E_FSERROR_ACCESS_DENIED, E_IOERROR, ...);
FUNDEF NONNULL((1)) bool KCALL
inode_tryaccess(struct inode *__restrict self, unsigned int type)
		THROWS(E_IOERROR, ...);


struct stat;

/* Collect stat-information about the given INode `self', implementing
 * the behavior of the `stat(2)' system call for INodes, as well as many
 * other handle types, including PATH and FILE objects. */
FUNDEF NONNULL((1)) void KCALL
inode_stat(struct inode *__restrict self,
           USER CHECKED struct stat *result)
		THROWS(E_IOERROR, ...);


/* ================================================================================ */
/* INODE INVOCATION API                                                             */
/* ================================================================================ */

/* Change the size (in bytes) of the given INode.
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_TRUNC:
 *                              [...]
 * @throw: E_FSERROR_DISK_FULL: [...]
 * @throw: E_FSERROR_READONLY:  [...]
 * @throw: E_IOERROR:           Failed to read/write data to/from disk. */
FUNDEF NONNULL((1)) void KCALL
inode_truncate(struct inode *__restrict self, pos_t new_size)
		THROWS(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION,
		       E_FSERROR_DISK_FULL, E_FSERROR_READONLY, E_IOERROR, ...);

/* Perform an ioctl() command on the given INode. */
FUNDEF NONNULL((1)) syscall_slong_t KCALL
inode_ioctl(struct inode *__restrict self, syscall_ulong_t cmd,
            USER UNCHECKED void *arg, iomode_t mode)
		THROWS(...);

/* Return information on hard limits for the given INode.
 * @param: name: One of `_PC_*' from `<bits/confname.h>'
 * @return: INODE_PATHCONF_UNDEDEFINED: The given `name' is not implemented by the underlying filesystem.
 * NOTE: This function invokes the `io_pathconf' operator of given INode `self'.
 *       If that operator isn't implemented or returns `INODE_PATHCONF_UNDEDEFINED',
 *       the same operator is re-invoked on `self->i_super->s_rootdir'.
 *       If that operator isn't implemented, or returns `INODE_PATHCONF_UNDEDEFINED'
 *       too, the following values are returned for specific `name's,
 *       or `INODE_PATHCONF_UNDEDEFINED' for any other name:
 * - _PC_LINK_MAX:           LINK_MAX     (From <linux/limits.h>)  (or `1' when the link operator isn't implemented for the INode itself, or the filesystem root)
 * - _PC_MAX_CANON:          MAX_CANON    (From <linux/limits.h>)
 * - _PC_MAX_INPUT:          MAX_INPUT    (From <linux/limits.h>)
 * - _PC_NAME_MAX:           65535
 * - _PC_PATH_MAX:           LONG_MAX
 * - _PC_PIPE_BUF:           PIPE_BUF     (From <linux/limits.h>)
 * - _PC_CHOWN_RESTRICTED:   0
 * - _PC_NO_TRUNC:           1
 * - _PC_VDISABLE:           '\0'
 * - _PC_FILESIZEBITS:       64
 * - _PC_REC_INCR_XFER_SIZE: VM_DATABLOCK_PAGESIZE(self)
 * - _PC_REC_MAX_XFER_SIZE:  VM_DATABLOCK_PAGESIZE(self) * (BITS_PER_POINTER / VM_DATAPART_PPP_BITS)
 * - _PC_REC_MIN_XFER_SIZE:  VM_DATABLOCK_PAGESIZE(self)
 * - _PC_REC_XFER_ALIGN:     VM_DATABLOCK_PAGESIZE(self)
 * - _PC_ALLOC_SIZE_MIN:     VM_DATABLOCK_PAGESIZE(self)
 * - _PC_SYMLINK_MAX:        self->i_type->it_directory.d_symlink != NULL ? LONG_MAX : 0
 * - _PC_2_SYMLINKS:         self->i_type->it_directory.d_symlink != NULL ? 1 : 0
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_IOERROR:  Failed to read/write data to/from disk. */
FUNDEF WUNUSED NONNULL((1)) intptr_t KCALL
inode_pathconf(struct inode *__restrict self, unsigned int name)
		THROWS(E_FSERROR_DELETED, E_IOERROR, ...);

/* Change all non-NULL the timestamp that are given.
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_FSERROR_READONLY: [...]
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_WRATTR: [...] */
FUNDEF NONNULL((1)) void KCALL
inode_chtime(struct inode *__restrict self,
             struct timespec const *new_atime,
             struct timespec const *new_mtime,
             struct timespec const *new_ctime)
		THROWS(E_FSERROR_DELETED, E_FSERROR_READONLY,
		       E_FSERROR_UNSUPPORTED_OPERATION, ...);

/* Change permissions, SUID/SGID and the sticky
 * bit of the given INode (flags mask: 07777)
 * The new file mode is calculated as `(old_mode & perm_mask) | perm_flag',
 * before being masked by what the underlying filesystem is capable of
 * representing.
 * @return: * : The old file mode
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_FSERROR_READONLY: [...]
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_ATTRIB: [...]
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_WRATTR: [...] */
FUNDEF NONNULL((1)) mode_t KCALL
inode_chmod(struct inode *__restrict self,
            mode_t perm_mask, mode_t perm_flag)
		THROWS(E_FSERROR_DELETED, E_FSERROR_READONLY,
		       E_FSERROR_UNSUPPORTED_OPERATION, ...);
#ifdef __cplusplus
extern "C++" {
FORCELOCAL NONNULL((1)) mode_t KCALL
inode_chmod(struct inode *__restrict self, mode_t new_perm)
		THROWS(E_FSERROR_DELETED, E_FSERROR_READONLY,
		       E_FSERROR_UNSUPPORTED_OPERATION, ...) {
	return inode_chmod(self, 0, new_perm);
}
}
#endif /* __cplusplus */


/* Change the owner and group of the given file.
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_FSERROR_READONLY: [...]
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_ATTRIB: [...]
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_WRATTR: [...] */
FUNDEF NONNULL((1)) void KCALL
inode_chown(struct inode *__restrict self,
            uid_t owner, gid_t group,
            uid_t *pold_owner DFL(__NULLPTR),
            gid_t *pold_group DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_FSERROR_READONLY,
		       E_FSERROR_UNSUPPORTED_OPERATION, ...);

/* Synchronize data of the given INode and attributes.
 * NOTE: This function is allowed to be called after a node has been
 *       deleted, though only if
 * @param: what: Set of `INODE_FCHANGED|INODE_FATTRCHANGED',
 *               of which at least one must be given.
 * @return: * :  Set of `INODE_FCHANGED|INODE_FATTRCHANGED' describing what was actually synced
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_IOERROR: Failed to read/write data to/from disk. */
FUNDEF NONNULL((1)) uintptr_t KCALL
inode_sync(struct inode *__restrict self,
           uintptr_t what DFL(INODE_FCHANGED | INODE_FATTRCHANGED))
		THROWS(E_FSERROR_DELETED, E_IOERROR, ...);

/* Ensure that the given symbolic-link INode has been loaded.
 * This function is a no-op when `self->sl_text != NULL' upon entry,
 * and guaranties that `self->sl_text' will be non-NULL upon success.
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_BADALLOC: [...]
 * @throw: E_IOERROR:  [...]
 * @return: true:  The symlink text is now loaded.
 * @return: false: The INode uses the dynamic symlink interface,
 *                 meaning the caller must invoke the `sl_readlink_dynamic'
 *                 operator with their own buffer. */
FUNDEF NONNULL((1)) bool KCALL
symlink_node_load(struct symlink_node *__restrict self)
		THROWS(E_FSERROR_DELETED, E_BADALLOC, E_IOERROR, ...);

/* Wrapper around `symlink_node_load()' for reading the text of a symbolic
 * link into a user-supplied user-space buffer, whilst returning the number
 * of required bytes of memory (EXCLUDING a trailing NUL-character, which
 * this function will _NOT_ append to the supplied buffer!) */
FUNDEF NONNULL((1)) size_t KCALL
symlink_node_readlink(struct symlink_node *__restrict self,
                      USER CHECKED char *buf, size_t buflen)
		THROWS(E_FSERROR_DELETED, E_BADALLOC, E_IOERROR, E_SEGFAULT, ...);

/* Read the next directory entry from `self' that hasn't been loaded, yet.
 * Return NULL and set the `INODE_FDIRLOADED' flag once the entirety of
 * the directory has been loaded.
 * NOTE: The caller must be holding a read-lock on `self'.
 * @assume(sync_reading(self));
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_READDIR:
 *                             [...]
 * @throw: E_IOERROR:          [...] */
FUNDEF NONNULL((1)) struct directory_entry *KCALL
directory_readnext(struct directory_node *__restrict self)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...);

/* Same as `directory_readnext()', but return the
 * self-pointer of the newly read directory entry. */
FUNDEF WUNUSED NONNULL((1)) struct directory_entry **KCALL
directory_readnext_p(struct directory_node *__restrict self)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...);

/* Lookup a directory item, given its name.
 * NOTE: The caller must be holding a read-lock on `self'
 * @assume(sync_reading(self));
 * @return: * :   A reference to the associated INode.
 * @return: NULL: No INode with the given `name' exists.
 *              (`E_FSERROR_(FILE|PATH)_NOT_FOUND'-style)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_SEGFAULT: Failed to access the given `name'.
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_READDIR:
 *                             [...]
 * @throw: E_IOERROR:          [...] */
FUNDEF WUNUSED NONNULL((1)) REF struct directory_entry *KCALL
directory_getentry(struct directory_node *__restrict self,
                   CHECKED USER /*utf-8*/ char const *name,
                   u16 namelen, uintptr_t hash)
		THROWS(E_FSERROR_DELETED, E_SEGFAULT,
		       E_FSERROR_UNSUPPORTED_OPERATION,
		       E_IOERROR, ...);

FUNDEF WUNUSED NONNULL((1)) REF struct directory_entry *KCALL
directory_getcaseentry(struct directory_node *__restrict self,
                       CHECKED USER /*utf-8*/ char const *name,
                       u16 namelen, uintptr_t hash)
		THROWS(E_FSERROR_DELETED, E_SEGFAULT,
		       E_FSERROR_UNSUPPORTED_OPERATION,
		       E_IOERROR, ...);

#ifdef __cplusplus
extern "C++" {
FORCELOCAL WUNUSED NONNULL((1)) REF struct directory_entry *KCALL
directory_getentry(struct directory_node *__restrict self,
                   CHECKED USER /*utf-8*/ char const *name, u16 namelen)
		THROWS(E_FSERROR_DELETED, E_SEGFAULT,
		       E_FSERROR_UNSUPPORTED_OPERATION,
		       E_IOERROR, ...) {
	return directory_getentry(self, name, namelen, directory_entry_hash(name, namelen));
}

FORCELOCAL WUNUSED NONNULL((1)) REF struct directory_entry *KCALL
directory_getcaseentry(struct directory_node *__restrict self,
                       CHECKED USER /*utf-8*/ char const *name, u16 namelen)
		THROWS(E_FSERROR_DELETED, E_SEGFAULT,
		       E_FSERROR_UNSUPPORTED_OPERATION,
		       E_IOERROR, ...) {
	return directory_getcaseentry(self, name, namelen, directory_entry_hash(name, namelen));
}

FORCELOCAL WUNUSED NONNULL((1)) REF struct directory_entry *KCALL
directory_getentry(struct directory_node *__restrict self,
                   CHECKED USER /*utf-8*/ char const *name)
		THROWS(E_FSERROR_DELETED, E_SEGFAULT,
		       E_FSERROR_UNSUPPORTED_OPERATION,
		       E_IOERROR, ...) {
	return directory_getentry(self, name, __libc_strlen(name));
}

FORCELOCAL WUNUSED NONNULL((1)) REF struct directory_entry *KCALL
directory_getcaseentry(struct directory_node *__restrict self,
                       CHECKED USER /*utf-8*/ char const *name)
		THROWS(E_FSERROR_DELETED, E_SEGFAULT,
		       E_FSERROR_UNSUPPORTED_OPERATION,
		       E_IOERROR, ...) {
	return directory_getcaseentry(self, name, __libc_strlen(name));
}

}
#endif /* __cplusplus */

/* Same as the function above, but return the entry's self-pointer within the directory node.
 * @param: poneshot_entry:  A storage location for directories implementing the one-shot interface.
 * @return: poneshot_entry: The directory implements the one-shot interface, and the
 *                          located directory entry has been stored in `*poneshot_entry'.
 *                          In this case, `*poneshot_entry' is a reference that must be
 *                          inherited by the caller.
 * @return: * :   The directory entries self-pointer (NOT A REFERENCE!).
 *                In this case, `*poneshot_entry' will have been set to `NULL'
 * @return: NULL: No INode with the given `name' exists.
 *              (`E_FSERROR_(FILE|PATH)_NOT_FOUND'-style)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_SEGFAULT: Failed to access the given `name'.
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_READDIR:
 *                             [...]
 * @throw: E_IOERROR:          [...] */
FUNDEF WUNUSED NONNULL((1, 5)) struct directory_entry **KCALL
directory_getentry_p(struct directory_node *__restrict self,
                     CHECKED USER /*utf-8*/ char const *name,
                     u16 namelen, uintptr_t hash,
                     /*out*/ REF struct directory_entry **__restrict poneshot_entry)
		THROWS(E_FSERROR_DELETED, E_SEGFAULT,
		       E_FSERROR_UNSUPPORTED_OPERATION,
		       E_IOERROR, E_SEGFAULT, ...);
FUNDEF WUNUSED NONNULL((1, 5)) struct directory_entry **KCALL
directory_getcaseentry_p(struct directory_node *__restrict self,
                         CHECKED USER /*utf-8*/ char const *name,
                         u16 namelen, uintptr_t hash,
                         /*out*/ REF struct directory_entry **__restrict poneshot_entry)
		THROWS(E_FSERROR_DELETED, E_SEGFAULT,
		       E_FSERROR_UNSUPPORTED_OPERATION,
		       E_IOERROR, E_SEGFAULT, ...);

#ifdef __cplusplus
extern "C++" {
FORCELOCAL WUNUSED NONNULL((1, 4)) struct directory_entry **KCALL
directory_getentry_p(struct directory_node *__restrict self,
                     CHECKED USER /*utf-8*/ char const *name, u16 namelen,
                     /*out*/ REF struct directory_entry **__restrict poneshot_entry)
		THROWS(E_FSERROR_DELETED, E_SEGFAULT,
		       E_FSERROR_UNSUPPORTED_OPERATION,
		       E_IOERROR, E_SEGFAULT, ...) {
	return directory_getentry_p(self, name, namelen,
	                            directory_entry_hash(name, namelen),
	                            poneshot_entry);
}

FORCELOCAL WUNUSED NONNULL((1, 4)) struct directory_entry **KCALL
directory_getcaseentry_p(struct directory_node *__restrict self,
                         CHECKED USER /*utf-8*/ char const *name, u16 namelen,
                         /*out*/ REF struct directory_entry **__restrict poneshot_entry)
		THROWS(E_FSERROR_DELETED, E_SEGFAULT,
		       E_FSERROR_UNSUPPORTED_OPERATION,
		       E_IOERROR, E_SEGFAULT, ...) {
	return directory_getcaseentry_p(self, name, namelen,
	                                directory_entry_hash(name, namelen),
	                                poneshot_entry);
}

FORCELOCAL WUNUSED NONNULL((1, 3)) struct directory_entry **KCALL
directory_getentry_p(struct directory_node *__restrict self,
                     CHECKED USER /*utf-8*/ char const *name,
                     /*out*/ REF struct directory_entry **__restrict poneshot_entry)
		THROWS(E_FSERROR_DELETED, E_SEGFAULT,
		       E_FSERROR_UNSUPPORTED_OPERATION,
		       E_IOERROR, E_SEGFAULT, ...) {
	return directory_getentry_p(self, name, __libc_strlen(name), poneshot_entry);
}

FORCELOCAL WUNUSED NONNULL((1, 3)) struct directory_entry **KCALL
directory_getcaseentry_p(struct directory_node *__restrict self,
                         CHECKED USER /*utf-8*/ char const *name,
                         /*out*/ REF struct directory_entry **__restrict poneshot_entry)
		THROWS(E_FSERROR_DELETED, E_SEGFAULT,
		       E_FSERROR_UNSUPPORTED_OPERATION,
		       E_IOERROR, E_SEGFAULT, ...) {
	return directory_getcaseentry_p(self, name, __libc_strlen(name), poneshot_entry);
}
}
#endif /* __cplusplus */


/* Same as `directory_getentry()', but automatically dereference
 * the directory entry to retrieve the associated INode.
 * Additionally, the caller isn't required to already be holding
 * a read-lock for the given directory.
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_SEGFAULT: Failed to access the given `name'.
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_READDIR:
 *                             [...]
 * @throw: E_IOERROR:          [...] */
FUNDEF WUNUSED NONNULL((1)) REF struct inode *KCALL
directory_getnode(struct directory_node *__restrict self,
                  CHECKED USER /*utf-8*/ char const *name,
                  u16 namelen, uintptr_t hash,
                  REF struct directory_entry **pentry DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_SEGFAULT,
		       E_FSERROR_UNSUPPORTED_OPERATION,
		       E_IOERROR, E_SEGFAULT, ...);

FUNDEF WUNUSED NONNULL((1)) REF struct inode *KCALL
directory_getcasenode(struct directory_node *__restrict self,
                      CHECKED USER /*utf-8*/ char const *name,
                      u16 namelen, uintptr_t hash,
                      REF struct directory_entry **pentry DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_SEGFAULT,
		       E_FSERROR_UNSUPPORTED_OPERATION,
		       E_IOERROR, E_SEGFAULT, ...);

#ifdef __cplusplus
extern "C++" {
FORCELOCAL WUNUSED NONNULL((1)) REF struct inode *KCALL
directory_getnode(struct directory_node *__restrict self,
                  CHECKED USER /*utf-8*/ char const *name, u16 namelen,
                  REF struct directory_entry **pentry DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_SEGFAULT,
		       E_FSERROR_UNSUPPORTED_OPERATION,
		       E_IOERROR, E_SEGFAULT, ...) {
	return directory_getnode(self, name, namelen,
							 directory_entry_hash(name, namelen),
							 pentry);
}

FORCELOCAL WUNUSED NONNULL((1)) REF struct inode *KCALL
directory_getcasenode(struct directory_node *__restrict self,
                      CHECKED USER /*utf-8*/ char const *name, u16 namelen,
                      REF struct directory_entry **pentry DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_SEGFAULT,
		       E_FSERROR_UNSUPPORTED_OPERATION,
		       E_IOERROR, E_SEGFAULT, ...) {
	return directory_getcasenode(self, name, namelen,
								 directory_entry_hash(name, namelen),
								 pentry);
}

FORCELOCAL WUNUSED NONNULL((1)) REF struct inode *KCALL
directory_getnode(struct directory_node *__restrict self,
                  CHECKED USER /*utf-8*/ char const *name,
                  REF struct directory_entry **pentry DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_SEGFAULT,
		       E_FSERROR_UNSUPPORTED_OPERATION,
		       E_IOERROR, E_SEGFAULT, ...) {
	return directory_getnode(self, name, __libc_strlen(name), pentry);
}

FORCELOCAL WUNUSED NONNULL((1)) REF struct inode *KCALL
directory_getcasenode(struct directory_node *__restrict self,
                      CHECKED USER /*utf-8*/ char const *name,
                      REF struct directory_entry **pentry DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_SEGFAULT,
		       E_FSERROR_UNSUPPORTED_OPERATION,
		       E_IOERROR, E_SEGFAULT, ...) {
	return directory_getcasenode(self, name, __libc_strlen(name), pentry);
}
}
#endif /* __cplusplus */


/* Create a new file within the given directory.
 * NOTE: When `open_mode & O_EXCL' is set, only `struct regular_node' are ever returned.
 * NOTE: When `open_mode & O_DOSPATH' is set, ignore casing when checking for existing files.
 * @param: open_mode: Set of `O_CREAT|O_EXCL|O_DOSPATH'
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
FUNDEF ATTR_RETNONNULL NONNULL((1, 2)) REF struct inode *KCALL
directory_creatfile(struct directory_node *__restrict target_directory,
                    CHECKED USER /*utf-8*/ char const *__restrict target_name, u16 target_namelen,
                    oflag_t open_mode, uid_t owner, gid_t group, mode_t mode,
                    REF struct directory_entry **ptarget_dirent DFL(__NULLPTR),
                    bool *pwas_newly_created DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_FSERROR_ILLEGAL_PATH, E_FSERROR_FILE_ALREADY_EXISTS,
		       E_FSERROR_FILE_NOT_FOUND, E_FSERROR_DISK_FULL, E_FSERROR_UNSUPPORTED_OPERATION,
		       E_FSERROR_READONLY, E_IOERROR, E_SEGFAULT, ...);



#define DIRECTORY_REMOVE_FREGULAR   0x0001 /* Remove regular files (`unlink()') */
#define DIRECTORY_REMOVE_FDIRECTORY 0x0002 /* Remove directories (`rmdir()') */
#define DIRECTORY_REMOVE_FCHKPMOUNT 0x2000 /* Check if `containing_path' has been re-mounted before actually removing anything.
                                            * If it has been, don't perform the removal and return `DIRECTORY_REMOVE_STATUS_REMOUNT'
                                            * NOTE: This flag may only be set when `containing_path' is non-NULL, and the
                                            *       check itself will only be performed when removing child directories. */
#define DIRECTORY_REMOVE_FCHKACCESS 0x4000 /* Check access permissions of the calling thread, and throw `E_FSERROR_ACCESS_DENIED'
                                            * if the calling thread may not delete the affected file.
                                            * NOTE: Only what would eventually become `*premoved_inode' is
                                            *       checked for permissions. - The containing directory is
                                            *       not checked for anything, leaving this task to the caller. */
#define DIRECTORY_REMOVE_FNOCASE    0x8000 /* Ignore casing. */

/* Status code flags returned by `directory_remove()' */
#define DIRECTORY_REMOVE_STATUS_REMOUNT  0x0000 /* Only returned when `DIRECTORY_REMOVE_FCHKPMOUNT' is set: the containing path has been re-mounted. */
#define DIRECTORY_REMOVE_STATUS_UNLINK   0x0001 /* The operation has removed or unlinked a file. */
#define DIRECTORY_REMOVE_STATUS_RMDIR    0x0002 /* The operation has removed or unlinked a directory. */
#define DIRECTORY_REMOVE_STATUS_FDELETED 0x4000 /* FLAG: The associated node has been deleted.
                                                 * This flag is set when the node's NLINK counter has reached
                                                 * ZERO(0) as a result of the remove operation, at which point
                                                 * the `INODE_FDELETED' flag is set, and the node is removed
                                                 * from the INode tree of the associated superblock. */

/* Remove an entry from this directory.
 * @param: mode: Set of `DIRECTORY_REMOVE_F*', or which at least one of
 *              `DIRECTORY_REMOVE_FREGULAR' or `DIRECTORY_REMOVE_FDIRECTORY'
 *               must be given.
 * @param: premoved_inode:  Upon success, store a reference to the removed INode here.
 * @param: premoved_dirent: Upon success, store a reference to the removed INode's directory entry here.
 * @param: containing_path: When non-NULL, try to remove a child directory from this path node upon success.
 * @param: premoved_path:   When non-NULL, store the child directory removed from `containing_path' here, otherwise set to `NULL'.
 * @return: * : Set of `DIRECTORY_REMOVE_STATUS_*'
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...] (the specified file was already deleted)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH: [...] (self was deleted)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_FSERROR_FILE_NOT_FOUND:      The specified `name' could not be found
 * @throw: E_FSERROR_ACCESS_DENIED:       `DIRECTORY_REMOVE_FCHKACCESS' was set, and the calling thread is not allowed to delete the file.
 * @throw: E_FSERROR_NOT_A_DIRECTORY:E_FILESYSTEM_NOT_A_DIRECTORY_RMDIR:  The given `name' refers to a regular file, but `DIRECTORY_REMOVE_FREGULAR' isn't set
 * @throw: E_FSERROR_IS_A_DIRECTORY:E_FILESYSTEM_IS_A_DIRECTORY_UNLINK:   The given `name' refers to a directory, but `DIRECTORY_REMOVE_FDIRECTORY' isn't set
 * @throw: E_FSERROR_IS_A_MOUNTING_POINT:                                 The given `name' refers to a mounting point when a child directory is being removed, and `containing_path' is given
 * @throw: E_FSERROR_DIRECTORY_NOT_EMPTY:                                 Attempted to remove a non-empty directory.
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_UNLINK: Cannot unlink files within `self'
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_RMDIR:  Cannot remove sub-directories of `self'
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_TRUNC:  Cannot truncate non-empty files to 0 bytes in order to delete their data
 * @throw: E_FSERROR_READONLY:            [...]
 * @throw: E_IOERROR:                     [...] */
FUNDEF NONNULL((1, 2)) unsigned int KCALL
directory_remove(struct directory_node *__restrict self,
                 CHECKED USER /*utf-8*/ char const *__restrict name, u16 namelen, uintptr_t hash,
                 unsigned int mode DFL(DIRECTORY_REMOVE_FREGULAR | DIRECTORY_REMOVE_FDIRECTORY),
                 /*out*/ REF struct inode **premoved_inode DFL(__NULLPTR),
                 /*out*/ REF struct directory_entry **premoved_dirent DFL(__NULLPTR),
                 struct path *containing_path DFL(__NULLPTR),
                 /*out*/ REF struct path **premoved_path DFL(__NULLPTR))
		THROWS(E_FSERROR_DELETED, E_FSERROR_DIRECTORY_NOT_EMPTY,
		       E_FSERROR_FILE_NOT_FOUND, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_NOT_A_DIRECTORY, E_FSERROR_IS_A_DIRECTORY,
		       E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_READONLY,
		       E_IOERROR, E_SEGFAULT, ...);



#define DIRECTORY_RENAME_FNORMAL    0x0000 /* Normal rename flags. */
#define DIRECTORY_RENAME_FCHKPMOUNT 0x2000 /* Check if `source_path' has been re-mounted before actually removing anything.
                                            * If it has been, don't perform the removal and return `DIRECTORY_RENAME_STATUS_REMOUNT'
                                            * NOTE: This flag may only be set when `source_path' is non-NULL, and the
                                            *       check itself will only be performed when removing child directories. */
#define DIRECTORY_RENAME_FCHKACCESS 0x4000 /* Check access permissions of the calling thread, and throw `E_FSERROR_ACCESS_DENIED'
                                            * if the calling thread may not rename the affected file.
                                            * NOTE: Only what would eventually become `*premoved_inode' is
                                            *       checked for permissions. - The containing directory is
                                            *       not checked for anything, leaving this task to the caller. */
#define DIRECTORY_RENAME_FNOCASE    0x8000 /* Ignore casing. */

#define DIRECTORY_RENAME_STATUS_REMOUNT 0x0000 /* Only returned when `DIRECTORY_RENAME_FCHKPMOUNT' is set: the containing path has been re-mounted. */
#define DIRECTORY_RENAME_STATUS_RENAMED 0x0001 /* Successfully renamed the directory. */

/* Rename/move an entry from one directory to another.
 * NOTE: This function will try to emulate an unsupported `rename()' using `link()' + `unlink()'
 * @param: mode: Set of `DIRECTORY_RENAME_F*'
 * @param: source_path:   When non-NULL, try to remove a child directory from this path node upon success.
 * @param: premoved_path: When non-NULL, store the child directory removed from `source_path' here, otherwise set to `NULL'.
 * @return: * : Set of `DIRECTORY_RENAME_STATUS_*'
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_RENAME: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...] (the specified source file was deleted)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH: [...] (`source_directory' or `target_directory' was deleted)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_FSERROR_IS_A_MOUNTING_POINT:  The given `source_name' refers to a mounting point when a child directory is being removed, and `source_path' is given
 * @throw: E_FSERROR_FILE_NOT_FOUND:      `source_name' wasn't found
 * @throw: E_FSERROR_CROSS_DEVICE_LINK:   [...]
 * @throw: E_FSERROR_ILLEGAL_PATH:        [...]
 * @throw: E_FSERROR_ILLEGAL_PATH:        `target_namelen' was ZERO(0)
 * @throw: E_FSERROR_FILE_ALREADY_EXISTS: [...]
 * @throw: E_FSERROR_DISK_FULL:           [...]
 * @throw: E_FSERROR_TOO_MANY_HARD_LINKS: [...] (Only when emulated using `link()' + `unlink()')
 * @throw: E_FSERROR_DIRECTORY_MOVE_TO_CHILD: [...]
 * @throw: E_FSERROR_ACCESS_DENIED:       [...]
 * @throw: E_FSERROR_READONLY:            [...]
 * @throw: E_IOERROR:                     [...] */
FUNDEF NONNULL((1, 2, 5, 6)) unsigned int KCALL
directory_rename(struct directory_node *__restrict source_directory,
                 CHECKED USER /*utf-8*/ char const *__restrict source_name,
                 u16 source_namelen, uintptr_t source_namehash,
                 struct directory_node *__restrict target_directory,
                 CHECKED USER /*utf-8*/ char const *__restrict target_name,
                 u16 target_namelen, unsigned int mode DFL(DIRECTORY_RENAME_FNORMAL),
                 /*out*/ REF struct directory_entry **psource_dirent DFL(__NULLPTR),
                 /*out*/ REF struct directory_entry **ptarget_dirent DFL(__NULLPTR),
                 /*out*/ REF struct inode **psource_inode DFL(__NULLPTR),
                 /*out*/ REF struct inode **ptarget_inode DFL(__NULLPTR),
                 struct path *source_path DFL(__NULLPTR),
                 /*out*/ REF struct path **premoved_path DFL(__NULLPTR))
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_DELETED,
		       E_FSERROR_CROSS_DEVICE_LINK, E_FSERROR_FILE_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_FILE_ALREADY_EXISTS,
		       E_FSERROR_DISK_FULL, E_FSERROR_TOO_MANY_HARD_LINKS,
		       E_FSERROR_DIRECTORY_MOVE_TO_CHILD, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_IS_A_MOUNTING_POINT, E_FSERROR_READONLY,
		       E_IOERROR, E_SEGFAULT, ...);



#define DIRECTORY_LINK_FNORMAL    0x0000 /* Normal link flags. */
#define DIRECTORY_LINK_FNOCASE    0x8000 /* Ignore casing when checking for existing files. */

/* Create a hardlink.
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_LINK: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...] (`link_target' was deleted)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH: [...] (`target_directory' was deleted)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_FSERROR_CROSS_DEVICE_LINK:   [...]
 * @throw: E_FSERROR_ILLEGAL_PATH:        [...]
 * @throw: E_FSERROR_ILLEGAL_PATH:        `target_namelen' was ZERO(0)
 * @throw: E_FSERROR_FILE_ALREADY_EXISTS: [...]
 * @throw: E_FSERROR_DISK_FULL:           [...]
 * @throw: E_FSERROR_TOO_MANY_HARD_LINKS: [...]
 * @throw: E_FSERROR_READONLY:            [...]
 * @throw: E_IOERROR:                     [...] */
FUNDEF NONNULL((1, 2, 4)) void KCALL
directory_link(struct directory_node *__restrict target_directory,
               CHECKED USER /*utf-8*/ char const *__restrict target_name,
               u16 target_namelen, struct inode *__restrict link_target,
               unsigned int link_mode DFL(DIRECTORY_LINK_FNORMAL),
               /*out*/ REF struct directory_entry **ptarget_dirent DFL(__NULLPTR))
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_DELETED,
		       E_FSERROR_CROSS_DEVICE_LINK, E_FSERROR_ILLEGAL_PATH,
		       E_FSERROR_FILE_ALREADY_EXISTS, E_FSERROR_DISK_FULL,
		       E_FSERROR_TOO_MANY_HARD_LINKS, E_FSERROR_READONLY,
		       E_IOERROR, E_SEGFAULT, ...);


#define DIRECTORY_SYMLINK_FNORMAL    0x0000 /* Normal symlink flags. */
#define DIRECTORY_SYMLINK_FNOCASE    0x8000 /* Ignore casing when checking for existing files. */

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
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 4)) REF struct symlink_node *KCALL
directory_symlink(struct directory_node *__restrict target_directory,
                  CHECKED USER /*utf-8*/ char const *target_name, u16 target_namelen,
                  CHECKED USER /*utf-8*/ char const *link_text, size_t link_text_size,
                  uid_t owner, gid_t group, mode_t mode,
                  unsigned int symlink_mode DFL(DIRECTORY_SYMLINK_FNORMAL),
                  /*out*/ REF struct directory_entry **ptarget_dirent DFL(__NULLPTR))
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_DELETED,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_FILE_ALREADY_EXISTS,
		       E_FSERROR_DISK_FULL, E_FSERROR_READONLY, E_IOERROR, E_SEGFAULT, ...);

#define DIRECTORY_MKNOD_FNORMAL    0x0000 /* Normal mknod flags. */
#define DIRECTORY_MKNOD_FNOCASE    0x8000 /* Ignore casing when checking for existing files. */

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
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2)) REF struct inode *KCALL
directory_mknod(struct directory_node *__restrict target_directory,
                CHECKED USER /*utf-8*/ char const *__restrict target_name,
                u16 target_namelen, mode_t mode, uid_t owner,
                gid_t group, dev_t referenced_device,
                unsigned int mknod_mode DFL(DIRECTORY_MKNOD_FNORMAL),
                /*out*/ REF struct directory_entry **ptarget_dirent DFL(__NULLPTR))
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_DELETED,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_FILE_ALREADY_EXISTS,
		       E_FSERROR_DISK_FULL, E_FSERROR_READONLY, E_IOERROR, E_SEGFAULT, ...);


#define DIRECTORY_MKDIR_FNORMAL    0x0000 /* Normal mkdir flags. */
#define DIRECTORY_MKDIR_FNOCASE    0x8000 /* Ignore casing when checking for existing files. */

/* Create a new directory node.
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_MKDIR: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH: [...] (`target_directory' was deleted)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_FSERROR_ILLEGAL_PATH:        [...]
 * @throw: E_FSERROR_ILLEGAL_PATH:        `target_namelen' was ZERO(0)
 * @throw: E_FSERROR_FILE_ALREADY_EXISTS: [...]
 * @throw: E_FSERROR_DISK_FULL:           [...]
 * @throw: E_FSERROR_READONLY:            [...]
 * @throw: E_IOERROR:                     [...] */
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2)) REF struct directory_node *KCALL
directory_mkdir(struct directory_node *__restrict target_directory,
                CHECKED USER /*utf-8*/ char const *__restrict target_name,
                u16 target_namelen, mode_t mode, uid_t owner, gid_t group,
                unsigned int mkdir_mode DFL(DIRECTORY_MKDIR_FNORMAL),
                /*out*/ REF struct directory_entry **ptarget_dirent DFL(__NULLPTR))
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_DELETED,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_FILE_ALREADY_EXISTS,
		       E_FSERROR_DISK_FULL, E_FSERROR_READONLY, E_IOERROR, E_SEGFAULT, ...);





struct statfs;

#define SUPERBLOCK_TYPE_NAME_MAX  15
struct superblock_type {
	REF struct driver *st_driver;             /* [1..1][const] The implementing driver application. */
	char   st_name[SUPERBLOCK_TYPE_NAME_MAX]; /* [const] Name of the superblock type (As passed to `mount' using
	                                           *         the `-t' option, as well as appearing in `/dev/filesystems') */
#define SUPERBLOCK_TYPE_FNORMAL          0x00 /* Normal superblock type flags. */
#define SUPERBLOCK_TYPE_FNODEV           0x01 /* The superblock should be constructed without a device. */
#define SUPERBLOCK_TYPE_FSINGLE          0x80 /* This type of superblock is a singleton (e.g. the `devfs' superblock) */
	u8     st_flags;                          /* [const] Superblock type flags (Set of `SUPERBLOCK_TYPE_F*') */
	size_t st_sizeof_superblock;              /* [const] == sizeof(struct superblock) + sizeof(FS_SPECIFIC_SUPERBLOCK_DATA)
	                                           * The heap size to which a superblock is allocated before `st_open()' is called. */
	union ATTR_PACKED {
		/* [1..1][const]
		 * [valid_if(!(st_flags & SUPERBLOCK_TYPE_FSINGLE))]
		 * [locked(WRITE(fs_filesystems.f_superlock))]
		 * Open a new superblock for `dev'.
		 * NOTE: To prevent race conditions, or hardware damage, this
		 *       function should not attempt to modify on-disk data,
		 *       as it may be called, only to have the return value
		 *       discarded when multiple tasks attempt to open a
		 *       given device as a superblock at the same time.
		 * This function must initialize the following members of `self':
		 *   - i_fileino
		 *   - i_type
		 *   - i_fsdata      (Optionally; pre-initialized to `NULL')
		 *   - db_pageshift
		 * After this, the caller will add the superblock to the global chain
		 * of existing superblocks through use of the `s_filesystems' field.
		 * @param: args: Type-specific user-space data passed to the constructor.
		 *               When non-NULL, most filesystem types expect this to point
		 *               to a comma-separated string of ~flags~ describing special
		 *               mounting behavior, as pass to the `mount' command using
		 *               the `-o' option.
		 * @throw: E_FSERROR_WRONG_FILE_SYSTEM:     [...]
		 * @throw: E_FSERROR_CORRUPTED_FILE_SYSTEM: [...]
		 * @throw: E_FSERROR_READONLY:              [...]
		 * @throw: E_IOERROR_READONLY:              Same as `E_FSERROR_READONLY'
		 * @throw: E_IOERROR_BADBOUNDS:             Same as `E_FSERROR_CORRUPTED_FILE_SYSTEM'
		 * @throw: E_DIVIDE_BY_ZERO:                Same as `E_FSERROR_CORRUPTED_FILE_SYSTEM'
		 * @throw: E_OVERFLOW:                      Same as `E_FSERROR_CORRUPTED_FILE_SYSTEM'
		 * @throw: E_INDEX_ERROR:                   Same as `E_FSERROR_CORRUPTED_FILE_SYSTEM'
		 * @throw: E_IOERROR:                       [...]
		 * @throw: E_SEGFAULT:                      [...] */
		NONNULL((1))
		void (KCALL *st_open)(struct superblock *__restrict self, UNCHECKED USER char *args)
				THROWS(E_FSERROR_WRONG_FILE_SYSTEM, E_FSERROR_CORRUPTED_FILE_SYSTEM,
				       E_IOERROR_BADBOUNDS, E_DIVIDE_BY_ZERO, E_OVERFLOW, E_INDEX_ERROR,
				       E_IOERROR, E_SEGFAULT, ...);
		/* [1..1][valid_if(st_flags & SUPERBLOCK_TYPE_FSINGLE)] The superblock singleton. */
		struct superblock *st_singleton;
	};

	struct ATTR_PACKED {

		/* [0..1][const] Called during `superblock_destroy'. */
		NONNULL((1))
		NOBLOCK void /*NOTHROW*/(KCALL *f_fini)(struct superblock *__restrict self);

		/* [1..1][const]
		 * [locked(WRITE(self->s_nodes_lock))]
		 * Perform additional initialization for loading a given `node'.
		 * The caller has already initialize the following members of `node':
		 *    - i_attr.a_ino
		 *    - i_attr.a_mode & I_FMT
		 *    - ... (Generic inode attributes except for `i_type')
		 * This function must then initialize the following members of `node':
		 *    - i_type
		 *    - i_fsdata (Optionally; pre-initialized to `NULL')
		 * Optionally, INode attributes may be initialized, as would also be
		 * done with a call to `a_loadattr()'. If this is done, this operator
		 * should set the `INODE_FATTRLOADED' flag before returning. */
		NONNULL((1, 2, 3, 4))
		void (KCALL *f_opennode)(struct superblock *__restrict self,
		                         struct inode *__restrict node,
		                         struct directory_node *__restrict parent_directory,
		                         struct directory_entry *__restrict parent_directory_entry)
				THROWS(E_IOERROR, E_BADALLOC, ...);

		/* [0..1][const]
		 * Gather information about the filesystem and store that information in `*result' */
		NONNULL((1))
		void (KCALL *f_statfs)(struct superblock *__restrict self,
		                       USER CHECKED struct statfs *result)
				THROWS(E_IOERROR, E_SEGFAULT, ...);

		/* [0..1][const]
		 * Synchronize all unwritten data of this superblock.
		 * NOTE: This function is called when `superblock_sync()'
		 *       finishes flushing the data of all changed INodes. */
		NONNULL((1))
		void (KCALL *f_sync)(struct superblock *__restrict self)
				THROWS(E_IOERROR, ...);

		/* [0..1][const]
		 * An optional callback that is invoked when kernel caches are being cleared. */
		NOBLOCK NONNULL((1))
		size_t /*NOTHROW*/(KCALL *f_clearcache)(struct superblock *__restrict self);

	} st_functions;

	/* [lock(fs_filesystem_types.ft_typelock)] Chain of filesystem types. */
	SLIST_NODE(struct superblock_type) st_chain;
};

#define __private_superblock_type_destroy(self)  driver_destroy((self)->st_driver)
DEFINE_REFCOUNT_FUNCTIONS(struct superblock_type, st_driver->d_refcnt, __private_superblock_type_destroy);


#define SUPERBLOCK_FNORMAL      0x0000 /* Normal superblock flags. */
#define SUPERBLOCK_FDOATIME     0x0001 /* [lock(atomic,weak)] Keep track of last-accessed timestamps (when opening streams to files). */
#define SUPERBLOCK_FNOMTIME     0x0002 /* [lock(atomic,weak)] Do not update last-modified timestamps. */
#define SUPERBLOCK_FUNMOUNTED   0x4000 /* [lock(WRITE_ONCE)] The superblock has been unmounted. */
#define SUPERBLOCK_FMUSTUNMOUNT 0x8000 /* [lock(WRITE_ONCE)] The superblock has been prepared to be unmounted (used internally). */

#define SUPERBLOCK_DEFAULT_NODES_MASK 63
struct superblock
#if defined(__cplusplus) && !defined(CONFIG_WANT_FS_AS_STRUCT)
	: directory_node /* The underlying superblock root directory. */
#endif
{
#if !defined(__cplusplus) || defined(CONFIG_WANT_FS_AS_STRUCT)
	struct directory_node         s_rootdir;      /* The underlying superblock root directory. */
#endif
	struct superblock_type const *s_type;         /* [1..1][const] Superblock type & operations. */
	REF struct basic_block_device*s_device;       /* [0..1][const] The device supposedly carrying the data of this superblock. */
	REF struct driver            *s_driver;       /* [1..1][const] The driver implementing this superblock. */
	struct atomic_rwlock          s_wall_lock;    /* Lock for `s_wall' */
	REF struct wall_clock        *s_wall;         /* [1..1][lock(s_lock)] WALL-clock used to generate filesystem timestamps. */
	uintptr_t                     s_flags;        /* Superblock flags (Set of `SUPERBLOCK_F*') */
	struct atomic_rwlock          s_changed_lock; /* Lock that must be held when removing nodes from, or clearing `s_changed' */
	WEAK REF struct inode        *s_changed;      /* [0..1][CHAIN(->i_changed_next)]
	                                               * Chain of modified INodes. (atomically exchanged with `NULL' to perform a SYNC() operation)
	                                               * NOTE: Every node apart of this chain must have either the
	                                               *      `INODE_FCHANGED' or `INODE_FATTRCHANGED' flag set. */
	WEAK struct inode            *s_delnodes;     /* [0..1][CHAIN(->i_changed_next)]
	                                               * Chain of nodes that are pending deletion and wish to be removed
	                                               * from the `s_nodes' tree, but couldn't do so themself after failing
	                                               * to acquire a lock to `s_nodes_lock'
	                                               * This chain must atomically be exchanged with `NULL' every time
	                                               * a write-lock is acquired to `s_nodes_lock'. */
	WEAK REF struct inode        *s_unlinknodes;  /* [0..1][CHAIN(->i_changed_next)]
	                                               * Same as `s_delnodes', but used for nodes that have been deleted. */
	struct rwlock                 s_nodes_lock;   /* Lock for `s_nodes' */
	ATREE_HEAD(struct inode)      s_nodes;        /* [1..1][lock(s_nodes_lock)] Address tree of Inodes.
	                                               * WARNING: This tree may contain INodes with a reference counter of ZERO(0).
	                                               * NOTE: This tree is holding a reference (causing an intentional
	                                               *       reference loop) for nodes with the `INODE_FPERSISTENT' flag set.
	                                               * NOTE: This tree _always_ contains the superblock
	                                               *       root node (which is the superblock itself) */
	struct atomic_rwlock          s_mount_lock;   /* Lock for `s_mount'. */
	LLIST(struct path)            s_mount;        /* [0..1][lock(s_mount_lock)] Chain of mounting points. */
	void                         *s_cblock_next;  /* [?..?] Used internally to chain blocking cleanup operations... */
	WEAK REF struct path         *s_umount_pend;  /* [0..1] Chain of paths which are pending to be removed from `s_mount'
	                                               * [CHAIN(->p_mount->mp_pending)] Chain of paths that are pending to be removed from `s_mount'. */
	SLIST_NODE(struct superblock) s_filesystems;  /* [lock(fs_filesystems.f_superlock)] Chain of known filesystems. */
	/* Filesystem-specific superblock data goes here! */
};

#if !defined(__cplusplus) || defined(CONFIG_WANT_FS_AS_STRUCT)
__DEFINE_SYNC_PROXY(struct superblock, s_rootdir.d_node)
#endif


/* Functions for acquiring the `s_nodes_lock' for reading/writing. */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) bool NOTHROW(KCALL superblock_nodeslock_tryread)(struct superblock *__restrict self);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) bool NOTHROW(KCALL superblock_nodeslock_trywrite)(struct superblock *__restrict self);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) bool NOTHROW(KCALL superblock_nodeslock_tryupgrade)(struct superblock *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) bool NOTHROW(KCALL superblock_nodeslock_endread)(struct superblock *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL superblock_nodeslock_endwrite)(struct superblock *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL superblock_nodeslock_downgrade)(struct superblock *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL superblock_nodeslock_tryservice)(struct superblock *__restrict self);
FUNDEF NONNULL((1)) void KCALL superblock_nodeslock_read(struct superblock *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF NONNULL((1)) void KCALL superblock_nodeslock_write(struct superblock *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF NONNULL((1)) bool KCALL superblock_nodeslock_upgrade(struct superblock *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF NONNULL((1)) WUNUSED bool NOTHROW(KCALL superblock_nodeslock_read_nx)(struct superblock *__restrict self);
FUNDEF NONNULL((1)) WUNUSED bool NOTHROW(KCALL superblock_nodeslock_write_nx)(struct superblock *__restrict self);
FUNDEF NONNULL((1)) WUNUSED unsigned int NOTHROW(KCALL superblock_nodeslock_upgrade_nx)(struct superblock *__restrict self);

/* Functions for acquiring the `s_mount_lock' for reading/writing. */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) bool NOTHROW(KCALL superblock_mountlock_tryread)(struct superblock *__restrict self);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) bool NOTHROW(KCALL superblock_mountlock_trywrite)(struct superblock *__restrict self);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) bool NOTHROW(KCALL superblock_mountlock_tryupgrade)(struct superblock *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL superblock_mountlock_endread)(struct superblock *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL superblock_mountlock_endwrite)(struct superblock *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL superblock_mountlock_downgrade)(struct superblock *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL superblock_mountlock_tryservice)(struct superblock *__restrict self);
FUNDEF NONNULL((1)) void KCALL superblock_mountlock_read(struct superblock *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF NONNULL((1)) void KCALL superblock_mountlock_write(struct superblock *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF NONNULL((1)) bool KCALL superblock_mountlock_upgrade(struct superblock *__restrict self) THROWS(E_WOULDBLOCK);
FUNDEF NONNULL((1)) WUNUSED bool NOTHROW(KCALL superblock_mountlock_read_nx)(struct superblock *__restrict self);
FUNDEF NONNULL((1)) WUNUSED bool NOTHROW(KCALL superblock_mountlock_write_nx)(struct superblock *__restrict self);
FUNDEF NONNULL((1)) WUNUSED unsigned int NOTHROW(KCALL superblock_mountlock_upgrade_nx)(struct superblock *__restrict self);



/* Open the given block-device as a superblock.
 * NOTE: If the given `device' has already been opened, return the existing
 *       filesystem or throw an `E_FSERROR_DEVICE_ALREADY_MOUNTED'
 *       error if the given type doesn't match the existing association.
 * @param: flags:                   Set of `SUPERBLOCK_F*'
 * @param: pnew_superblock_created: When non-NULL, set to `true' if a new
 *                                  superblock was created, otherwise set to `false'
 * @throws: E_FSERROR_DEVICE_ALREADY_MOUNTED: [...]
 * @throws: E_FSERROR_UNKNOWN_FILE_SYSTEM:    The driver associated with `type' is finalizing
 * @throws: E_FSERROR_NO_BLOCK_DEVICE:        [...]
 * @throws: E_FSERROR_WRONG_FILE_SYSTEM:      [...]
 * @throws: E_FSERROR_CORRUPTED_FILE_SYSTEM:  [...]
 * @throws: E_IOERROR:                        [...]
 * @throws: E_BADALLOC:                       [...] */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct superblock *KCALL
superblock_open(struct superblock_type *__restrict type,
                struct basic_block_device *device,
                uintptr_t flags DFL(SUPERBLOCK_FNORMAL),
                UNCHECKED USER char *args DFL(__NULLPTR),
                bool *pnew_superblock_created DFL(__NULLPTR))
		THROWS(E_FSERROR_DEVICE_ALREADY_MOUNTED, E_FSERROR_UNKNOWN_FILE_SYSTEM,
		       E_FSERROR_WRONG_FILE_SYSTEM, E_FSERROR_NO_BLOCK_DEVICE,
		       E_FSERROR_CORRUPTED_FILE_SYSTEM, E_IOERROR, E_BADALLOC,
		       E_SEGFAULT, E_WOULDBLOCK, ...);


/* Synchronize all modified nodes within the given superblock
 * NOTE: This function is allowed to be called after `SUPERBLOCK_FUNMOUNTED' has been set!
 * @param: sync_device: When `true', also synchronize the underlying
 *                      block-device (if any) before returning. */
FUNDEF NONNULL((1)) void KCALL
superblock_sync(struct superblock *__restrict self,
                bool sync_device DFL(true))
		THROWS(E_IOERROR, ...);

/* Call `superblock_sync()' for all system-wide existing superblock.
 * NOTE: Underlying block-devices will be synced as well. */
FUNDEF void KCALL superblock_syncall(void) THROWS(E_IOERROR, ...);


/* #1: Set the `SUPERBLOCK_FUNMOUNTED' flag
 * #2: Set the DELETED flag for all nodes.
 * #3: Synchronize the superblock (`superblock_sync(self)')
 * Future attempts to create new nodes with `superblock_opennode()' will
 * cause an `E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED' to be thrown.
 * WARNING: This function will _NOT_ remove existing mounting points of
 *          the superblock, however is used to implement `path_umount()'
 * @return: true:  Successfully unmounted the superblock.
 * @return: false: The superblock had already been set to an unmounted state. */
FUNDEF NONNULL((1)) bool KCALL
superblock_set_unmounted(struct superblock *__restrict self)
		THROWS(E_WOULDBLOCK, E_IOERROR, ...);

/* Clear all of the caches associated with the given superblock. */
FUNDEF NOBLOCK NONNULL((1)) size_t
NOTHROW(KCALL superblock_clear_caches)(struct superblock *__restrict self);


/* Open the INode associated with a given directory entry.
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: The superblock has been unmounted.
 * @throws: E_IOERROR:   [...]
 * @throws: E_BADALLOC:  [...] */
FUNDEF ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct inode *KCALL
superblock_opennode(struct superblock *__restrict self,
                    struct directory_node *__restrict parent_directory,
                    struct directory_entry *__restrict parent_directory_entry)
		THROWS(E_FSERROR_DELETED, E_IOERROR, E_BADALLOC, ...);


/* Gather information about the filesystem and store that information in `*result' */
FUNDEF NONNULL((1, 2)) void KCALL
superblock_statfs(struct superblock *__restrict self,
                  USER CHECKED struct statfs *result)
		THROWS(E_IOERROR, E_SEGFAULT, ...);



struct filesystem_types {
	/* TODO: Replace with a reference counted vector using `ATOMIC_REF()' */
	struct atomic_rwlock          ft_typelock; /* Lock for the chain of known filesystem types. */
	SLIST(struct superblock_type) ft_types;    /* [lock(ft_typelock)][CHAIN(->st_chain)] Chain of known filesystem types. */
};
struct filesystems {
	struct rwlock               f_superlock;   /* Lock for the chain of known superblocks. */
	SLIST(struct superblock)    f_superblocks; /* [lock(f_superlock)][CHAIN(->s_filesystems)][0..1] Chain of known filesystems. */
};

DATDEF struct filesystem_types fs_filesystem_types; /* Global tracking of known filesystem types. */
DATDEF struct filesystems      fs_filesystems;      /* Global tracking of existing filesystems (superblocks). */

/* [CHAIN(*(struct superblock **).)][0..1]
 * Chain of superblocks that are pending deletion. */
DATDEF WEAK REF struct superblock *fs_filesystems_delblocks;

/* Acquire a lock to `fs_filesystems.f_superlock', ensuring that any
 * superblocks that are pending deletion will have actually been deleted. */
FUNDEF void KCALL fs_filesystems_lock_read(void) THROWS(E_WOULDBLOCK);
FUNDEF void KCALL fs_filesystems_lock_write(void) THROWS(E_WOULDBLOCK);
FUNDEF bool KCALL fs_filesystems_lock_upgrade(void) THROWS(E_WOULDBLOCK);
FUNDEF NOBLOCK WUNUSED bool NOTHROW(KCALL fs_filesystems_lock_tryread)(void);
FUNDEF NOBLOCK WUNUSED bool NOTHROW(KCALL fs_filesystems_lock_trywrite)(void);
FUNDEF NOBLOCK WUNUSED bool NOTHROW(KCALL fs_filesystems_lock_tryupgrade)(void);
FUNDEF NOBLOCK bool NOTHROW(KCALL fs_filesystems_lock_endread)(void);
FUNDEF NOBLOCK void NOTHROW(KCALL fs_filesystems_lock_endwrite)(void);

/* Remove the given `block' from `fs_filesystems'
 * NOTE: The caller is required to be holding a lock to `fs_filesystems.f_superlock' */
FUNDEF NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL fs_filesystems_remove)(struct superblock *__restrict block);

/* Fill `buffer' (with _length_ (in elements, not bytes) available locations) with
 * all loaded filesystems. When `buffer' isn't large enough, don't load any actual
 * references into it and return the required length. - Otherwise, return the used
 * length and incref() all populated buffer entries. */
FUNDEF WUNUSED size_t KCALL
fs_filesystems_loadall(REF struct superblock **buffer, size_t buffer_length)
		THROWS(E_WOULDBLOCK);



/* Returns a reference to (the driver of the) filesystem type, given its `name'.
 * XXX: Returning a reference to a driver isn't safe here!
 *      The driver may have allocate the superblock_type on the heap, whilst another
 *      thread is currently performing driver finalization, which is now freeing
 *      the superblock type returned by this function
 *      The solution would be to add a reference counter to `superblock_type', and
 *      have this function return 2 references (one to the superblock_type, and one
 *      to the driver)
 * @return: NULL: No filesystem type matching the given `name' was found. */
FUNDEF NONNULL((1)) REF struct superblock_type *
(KCALL lookup_filesystem_type)(USER CHECKED char const *name)
		THROWS(E_SEGFAULT, E_WOULDBLOCK);

/* Register a filesystem type. */
FUNDEF NONNULL((1)) void KCALL
register_filesystem_type(struct superblock_type *__restrict type)
		THROWS(E_WOULDBLOCK);
FUNDEF NONNULL((1)) void KCALL
unregister_filesystem_type(struct superblock_type *__restrict type)
		THROWS(E_WOULDBLOCK);



#ifdef __cplusplus
extern "C++" {
/* Convenience overloads */
FORCELOCAL ATTR_RETNONNULL WUNUSED REF struct superblock *
(KCALL superblock_open)(USER CHECKED char const *filesystem_type_name,
                        struct basic_block_device *device,
                        uintptr_t flags DFL(SUPERBLOCK_FNORMAL),
                        UNCHECKED USER char *args DFL(__NULLPTR),
                        bool *pnew_superblock_created DFL(__NULLPTR))
		THROWS(E_FSERROR_DEVICE_ALREADY_MOUNTED, E_FSERROR_UNKNOWN_FILE_SYSTEM,
		       E_FSERROR_WRONG_FILE_SYSTEM, E_FSERROR_NO_BLOCK_DEVICE,
		       E_FSERROR_CORRUPTED_FILE_SYSTEM, E_IOERROR, E_BADALLOC,
		       E_SEGFAULT, E_WOULDBLOCK, ...) {
	REF struct superblock_type *type;
	type = lookup_filesystem_type(filesystem_type_name);
	if unlikely(!type)
		THROW(E_FSERROR_UNKNOWN_FILE_SYSTEM);
	FINALLY_DECREF_UNLIKELY(type);
	return superblock_open(type, device, flags, args, pnew_superblock_created);
}
FORCELOCAL ATTR_RETNONNULL WUNUSED REF struct superblock *
(KCALL superblock_open)(USER CHECKED char const *filesystem_type_name,
                        USER CHECKED char const *device_name,
                        uintptr_t flags DFL(SUPERBLOCK_FNORMAL),
                        UNCHECKED USER char *args DFL(__NULLPTR),
                        bool *pnew_superblock_created DFL(__NULLPTR))
		THROWS(E_FSERROR_DEVICE_ALREADY_MOUNTED, E_FSERROR_UNKNOWN_FILE_SYSTEM,
		       E_FSERROR_WRONG_FILE_SYSTEM, E_FSERROR_NO_BLOCK_DEVICE,
		       E_FSERROR_CORRUPTED_FILE_SYSTEM, E_IOERROR, E_BADALLOC,
		       E_SEGFAULT, E_WOULDBLOCK, ...) {
	REF struct basic_block_device *dev;
	dev = block_device_lookup_name(device_name);
	if unlikely(!dev)
		THROW(E_FSERROR_NOT_A_BLOCK_DEVICE);
	FINALLY_DECREF_UNLIKELY(dev);
	return superblock_open(filesystem_type_name, dev, flags, args, pnew_superblock_created);
}
FORCELOCAL ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct superblock *
(KCALL superblock_open)(struct superblock_type *__restrict type,
                        USER CHECKED char const *device_name,
                        uintptr_t flags DFL(SUPERBLOCK_FNORMAL),
                        UNCHECKED USER char *args DFL(__NULLPTR),
                        bool *pnew_superblock_created DFL(__NULLPTR))
		THROWS(E_FSERROR_DEVICE_ALREADY_MOUNTED, E_FSERROR_UNKNOWN_FILE_SYSTEM,
		       E_FSERROR_WRONG_FILE_SYSTEM, E_FSERROR_NO_BLOCK_DEVICE,
		       E_FSERROR_CORRUPTED_FILE_SYSTEM, E_IOERROR, E_BADALLOC,
		       E_SEGFAULT, E_WOULDBLOCK, ...) {
	REF struct basic_block_device *dev;
	dev = block_device_lookup_name(device_name);
	if unlikely(!dev)
		THROW(E_FSERROR_NOT_A_BLOCK_DEVICE);
	FINALLY_DECREF_UNLIKELY(dev);
	return superblock_open(type, dev, flags, args, pnew_superblock_created);
}
FORCELOCAL ATTR_RETNONNULL WUNUSED REF struct superblock *
(KCALL superblock_open)(USER CHECKED char const *filesystem_type_name,
                        uintptr_t flags DFL(SUPERBLOCK_FNORMAL),
                        UNCHECKED USER char *args DFL(__NULLPTR),
                        bool *pnew_superblock_created DFL(__NULLPTR))
		THROWS(E_FSERROR_DEVICE_ALREADY_MOUNTED, E_FSERROR_UNKNOWN_FILE_SYSTEM,
		       E_FSERROR_WRONG_FILE_SYSTEM, E_FSERROR_NO_BLOCK_DEVICE,
		       E_FSERROR_CORRUPTED_FILE_SYSTEM, E_IOERROR, E_BADALLOC,
		       E_SEGFAULT, E_WOULDBLOCK, ...) {
	return superblock_open(filesystem_type_name,
	                       (struct basic_block_device *)NULL,
	                       flags,
	                       args,
	                       pnew_superblock_created);
}
FORCELOCAL ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct superblock *
(KCALL superblock_open)(struct superblock_type *__restrict type,
                        uintptr_t flags DFL(SUPERBLOCK_FNORMAL),
                        UNCHECKED USER char *args DFL(__NULLPTR),
                        bool *pnew_superblock_created DFL(__NULLPTR))
		THROWS(E_FSERROR_DEVICE_ALREADY_MOUNTED, E_FSERROR_UNKNOWN_FILE_SYSTEM,
		       E_FSERROR_WRONG_FILE_SYSTEM, E_FSERROR_NO_BLOCK_DEVICE,
		       E_FSERROR_CORRUPTED_FILE_SYSTEM, E_IOERROR, E_BADALLOC,
		       E_SEGFAULT, E_WOULDBLOCK, ...) {
	return superblock_open(type,
	                       (struct basic_block_device *)NULL,
	                       flags,
	                       args,
	                       pnew_superblock_created);
}
}
#endif /* __cplusplus */


#if 1
#define FS_HEAP  (&kernel_default_heap)
#define FS_GFP   (GFP_NORMAL)
#else
#define FS_HEAP  (&kernel_locked_heap)
#define FS_GFP   (GFP_LOCKED)
#endif


#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_FS_NODE_H */
