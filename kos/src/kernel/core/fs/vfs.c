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
#ifndef GUARD_KERNEL_CORE_FS_VFS_C
#define GUARD_KERNEL_CORE_FS_VFS_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/cache.h>
#include <kernel/except.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/sync.h>

#include <hybrid/atomic.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <kos/except/fs.h>
#include <kos/except/inval.h>
#include <kos/hop/path.h>
#include <limits.h> /* SYMLOOP_MAX */

#include <assert.h>
#include <format-printer.h>
#include <sched.h>
#include <string.h>

DECL_BEGIN

/* Path allocation functions. (using a cache, because of how
 * often path objects can potentially be allocated and freed) */
DEFINE_PREALLOCATION_CACHE(PUBLIC, path, struct path, 256)


DEFINE_HANDLE_REFCNT_FUNCTIONS(path, struct path)

INTERN NONNULL((1)) REF void *KCALL
handle_path_tryas(struct path *__restrict self,
                  uintptr_half_t wanted_type)
		THROWS(E_WOULDBLOCK) {
	switch (wanted_type) {

	case HANDLE_TYPE_DATABLOCK: {
		REF struct directory_node *result;
		sync_read(self);
		result = (REF struct directory_node *)xincref(self->p_inode);
		sync_endread(self);
		return result;
	}	break;

	case HANDLE_TYPE_DIRECTORYENTRY:
		return incref(self->p_dirent);

	default:
		break;
	}
	return NULL;
}


INTERN void KCALL
handle_path_truncate(struct path *__restrict self, pos_t new_size) {
	REF struct inode *node;
	sync_read(self);
	node = (REF struct inode *)incref(self->p_inode);
	sync_endread(self);
	TRY {
		inode_truncate(node, new_size);
	} EXCEPT {
		decref(node);
		RETHROW();
	}
	decref(node);
}

INTERN pos_t KCALL /* TODO */
handle_path_allocate(struct path *__restrict self,
                     fallocate_mode_t mode,
                     pos_t start, pos_t length);

INTERN void KCALL handle_path_sync(struct path *__restrict self) {
	REF struct inode *node;
	sync_read(self);
	node = (REF struct inode *)incref(self->p_inode);
	sync_endread(self);
	TRY {
		inode_sync(node);
	} EXCEPT {
		decref(node);
		RETHROW();
	}
	decref(node);
}

INTERN void KCALL handle_path_datasync(struct path *__restrict self) {
	REF struct inode *node;
	sync_read(self);
	node = (REF struct inode *)incref(self->p_inode);
	sync_endread(self);
	TRY {
		vm_datablock_sync(node);
	} EXCEPT {
		decref(node);
		RETHROW();
	}
	decref(node);
}

INTERN void KCALL
handle_path_stat(struct path *__restrict self,
                 USER CHECKED struct stat *result) {
	REF struct inode *node;
	sync_read(self);
	node = (REF struct inode *)incref(self->p_inode);
	sync_endread(self);
	TRY {
		inode_stat(node, result);
	} EXCEPT {
		decref(node);
		RETHROW();
	}
	decref(node);
}

INTERN poll_mode_t KCALL
handle_path_poll(struct path *__restrict self,
                 poll_mode_t what) {
	REF struct inode *node;
	poll_mode_t result = 0;
	sync_read(self);
	node = (REF struct inode *)incref(self->p_inode);
	sync_endread(self);
	TRY {
		if (what & POLLOUT) {
			if (rwlock_pollwrite(&node->db_lock))
				result = POLLOUT | POLLIN;
		} else if (what & POLLIN) {
			/* TODO: Poll until the file is larger than the current read-pointer. */
			if (rwlock_pollread(&node->db_lock))
				result = POLLIN;
		}
		return 0;
	} EXCEPT {
		decref(node);
		RETHROW();
	}
	decref(node);
	return result;
}

INTERN syscall_slong_t KCALL
handle_path_hop(struct path *__restrict self,
                syscall_ulong_t cmd,
                USER UNCHECKED void *arg,
                iomode_t mode) {
	switch (cmd) {

	case HOP_PATH_RECENT:
		require(CAP_MARK_PATH_AS_RECENT);
		path_recent(self);
		break;

	case HOP_PATH_OPENPARENT: {
		struct handle temp;
		if (!self->p_parent || self == ATOMIC_READ(THIS_FS->f_root))
			THROW(E_NO_SUCH_OBJECT);
		temp.h_type = HANDLE_TYPE_PATH;
		temp.h_mode = mode;
		temp.h_data = self->p_parent;
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, temp);
	}	break;

	case HOP_PATH_OPENVFS: {
		struct handle temp;
		if (self->p_vfs != ATOMIC_READ(THIS_FS->f_root))
			THROW(E_NO_SUCH_OBJECT);
		temp.h_type = HANDLE_TYPE_PATH;
		temp.h_mode = mode;
		temp.h_data = self->p_vfs;
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, temp);
	}	break;

	case HOP_PATH_OPENNODE: {
		struct handle temp;
		unsigned int result;
		temp.h_type = HANDLE_TYPE_DATABLOCK;
		temp.h_mode = mode;
		sync_read(self);
		temp.h_data = incref(self->p_inode);
		sync_endread(self);
		TRY {
			inode_access_accmode((struct inode *)temp.h_data, mode);
			result = handle_installhop((USER UNCHECKED struct hop_openfd *)arg, temp);
		} EXCEPT {
			decref((struct inode *)temp.h_data);
			RETHROW();
		}
		decref((struct inode *)temp.h_data);
		return result;
	}	break;

	case HOP_PATH_OPENDENTRY: {
		struct handle temp;
		temp.h_type = HANDLE_TYPE_DIRECTORYENTRY;
		temp.h_mode = mode;
		temp.h_data = self->p_dirent;
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, temp);
	}	break;

	case HOP_PATH_ISDRIVE:
		validate_writable(arg, sizeof(uint32_t));
		COMPILER_BARRIER();
		*(uint32_t *)arg = (uint32_t)ATOMIC_READ(self->p_isdrive);
		COMPILER_BARRIER();
		break;

	//TODO:HOP_PATH_GETNAME    0x00060007 /* [struct hop_path_getname *data] Read the name of the given path */
	//TODO:HOP_PATH_OPENCHILD  0x00060008 /* [struct hop_path_openchild *data] Open a child of the given path */
	//TODO:HOP_PATH_RENAME     0x00060009 /* [struct hop_path_rename *data] Rename a child entry within a given path (wrapper for `path_rename()') */
	//TODO:HOP_PATH_TRAVERSE   0x0006000a /* [struct hop_path_traverse *data] Traverse the filesystem, starting at the given path (wrapper for `path_traverse_ex()') */

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND,
		      cmd);
		break;
	}
	return 0;
}




DEFINE_HANDLE_REFCNT_FUNCTIONS(fs, struct fs)
/* TODO: Other handle operators */



/* Print the location of a given path+entry.
 * @param: mode: Set of `PATH_PRINT_MODE_DOSPATH|PATH_PRINT_MODE_EXCDRIVE' */
PUBLIC NONNULL((1, 4)) ssize_t KCALL
path_printentex(struct path *__restrict self,
                USER CHECKED char const *dentry_name, u16 dentry_namelen,
                pformatprinter printer, void *arg,
                unsigned int mode,
                struct path *__restrict root) {
	ssize_t result, temp;
	assertf(!(mode & ~(PATH_PRINT_MODE_DOSPATH | PATH_PRINT_MODE_EXCDRIVE)), "mode = %x", mode);
	result = path_printex(self, printer, arg,
	                      mode | PATH_PRINT_MODE_INCTRAIL,
	                      root);
	if likely(result >= 0) {
		/* Print the name of the associated directory entry. */
		temp = (*printer)(arg,
		                  dentry_name,
		                  dentry_namelen);
		if unlikely(temp < 0)
			goto err_temp;
		result += temp;
	}
	return result;
err_temp:
	return temp;
}

/* Same as path_printentex(), using the current FS-mode & root. */
PUBLIC NONNULL((1, 4)) ssize_t KCALL
path_printent(struct path *__restrict self,
              USER CHECKED char const *dentry_name, u16 dentry_namelen,
              pformatprinter printer, void *arg) {
	ssize_t result;
	struct fs *f = THIS_FS;
	REF struct path *root;
	unsigned int mode;
	sync_read(&f->f_pathlock);
	root = incref(f->f_root);
	sync_endread(&f->f_pathlock);
#if PATH_PRINT_MODE_DOSPATH == FS_MODE_FDOSPATH
	mode = ATOMIC_READ(f->f_atflag) & PATH_PRINT_MODE_DOSPATH;
#else
	mode = PATH_PRINT_MODE_NORMAL;
	if (ATOMIC_READ(f->f_atflag) & FS_MODE_FDOSPATH)
		mode |= PATH_PRINT_MODE_DOSPATH;
#endif
	TRY {
		result = path_printentex(self,
		                         dentry_name,
		                         dentry_namelen,
		                         printer,
		                         arg,
		                         mode,
		                         root);
	} EXCEPT {
		decref(root);
		RETHROW();
	}
	decref(root);
	return result;
}


/* Same as path_printex() with `PATH_PRINT_MODE_INCTRAIL',
 * and using the current FS-mode & root. */
PUBLIC NONNULL((1, 2)) ssize_t KCALL
path_print(struct path *__restrict self,
           pformatprinter printer, void *arg) {
	ssize_t result;
	struct fs *f = THIS_FS;
	REF struct path *root;
	unsigned int mode;
	sync_read(&f->f_pathlock);
	root = incref(f->f_root);
	sync_endread(&f->f_pathlock);
	mode = PATH_PRINT_MODE_INCTRAIL;
#if PATH_PRINT_MODE_DOSPATH == FS_MODE_FDOSPATH
	mode |= ATOMIC_READ(f->f_atflag) & PATH_PRINT_MODE_DOSPATH;
#else
	if (ATOMIC_READ(f->f_atflag) & FS_MODE_FDOSPATH)
		mode |= PATH_PRINT_MODE_DOSPATH;
#endif
	TRY {
		result = path_printex(self,
		                      printer,
		                      arg,
		                      mode,
		                      root);
	} EXCEPT {
		decref(root);
		RETHROW();
	}
	decref(root);
	return result;
}

/* Print the location of a given path. */
PUBLIC NONNULL((1, 2, 5)) ssize_t KCALL
path_printex(struct path *__restrict self,
             pformatprinter printer, void *arg,
             unsigned int mode,
             struct path *__restrict root) {
	ssize_t temp, result;
	if ((mode & PATH_PRINT_MODE_DOSPATH) &&
	    ATOMIC_READ(self->p_isdrive) != 0) {
		struct vfs *v = self->p_vfs;
		sync_read(&v->v_drives_lock);
		if likely(ATOMIC_READ(self->p_isdrive) != 0) {
			unsigned int i;
			char prefix[3];
			/* Drive root encountered. */
			if (mode & PATH_PRINT_MODE_EXCDRIVE) {
				sync_endread(&v->v_drives_lock);
				if (!(mode & PATH_PRINT_MODE_INCTRAIL))
					return 0;
				return (*printer)(arg, "\\", 1);
			}
			for (i = 0; i < VFS_DRIVECOUNT; ++i) {
				if (v->v_drives[i] == self)
					goto got_drive_root;
			}
			i = (unsigned int)(int)('?' - 'A');
got_drive_root:
			sync_endread(&v->v_drives_lock);
			prefix[0] = (char)('A' + i);
			prefix[1] = ':';
			return (*printer)(arg, prefix,
			                  mode & PATH_PRINT_MODE_INCTRAIL ? (prefix[2] = '\\', 3) : 2);
		}
		sync_endread(&v->v_drives_lock);
	}
	if (self == root || !self->p_parent) {
		/* Last path segment reached. */
		if (mode & PATH_PRINT_MODE_DOSPATH) {
			return (*printer)(arg, "\\\\unix\\",
			                  mode & PATH_PRINT_MODE_INCTRAIL ? 7 : 6);
		}
		if (!(mode & PATH_PRINT_MODE_INCTRAIL))
			return 0;
		return (*printer)(arg, "/", 1);
	}
	result = path_printex(self->p_parent, printer, arg,
	                      mode | PATH_PRINT_MODE_INCTRAIL,
	                      root);
	if unlikely(result < 0)
		goto done;
	temp = (*printer)(arg,
	                  self->p_dirent->de_name,
	                  self->p_dirent->de_namelen);
	if unlikely(temp < 0)
		goto err;
	result += temp;
	if (mode & PATH_PRINT_MODE_INCTRAIL) {
		temp = (*printer)(arg, "/", 1);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
done:
	return result;
err:
	return temp;
}



/* Helper functions for printing a path into a user-space buffer. */
PUBLIC NONNULL((3, 7)) size_t KCALL
path_sprintentex(USER CHECKED char *buffer, size_t buflen,
                 struct path *__restrict self,
                 USER CHECKED char const *dentry_name, u16 dentry_namelen,
                 unsigned int mode, struct path *__restrict root)
		THROWS(E_SEGFAULT) {
	size_t result;
	struct format_snprintf_data data;
	format_snprintf_init(&data, buffer, buflen);
	result = (size_t)path_printentex(self,
	                                 dentry_name, dentry_namelen,
	                                 &format_snprintf_printer,
	                                 &data,
	                                 mode,
	                                 root);
	if (result < buflen)
		buffer[result] = '\0';
	++result;
	return result;
}

PUBLIC NONNULL((3)) size_t KCALL
path_sprintent(USER CHECKED char *buffer, size_t buflen,
               struct path *__restrict self,
               USER CHECKED char const *dentry_name, u16 dentry_namelen)
		THROWS(E_SEGFAULT) {
	size_t result;
	struct format_snprintf_data data;
	format_snprintf_init(&data, buffer, buflen);
	result = (size_t)path_printent(self,
	                               dentry_name, dentry_namelen,
	                               &format_snprintf_printer,
	                               &data);
	if (result < buflen)
		buffer[result] = '\0';
	++result;
	return result;
}

PUBLIC NONNULL((3, 5)) size_t KCALL
path_sprintex(USER CHECKED char *buffer, size_t buflen,
              struct path *__restrict self,
              unsigned int mode, struct path *__restrict root)
		THROWS(E_SEGFAULT) {
	size_t result;
	struct format_snprintf_data data;
	format_snprintf_init(&data, buffer, buflen);
	result = (size_t)path_printex(self,
	                              &format_snprintf_printer,
	                              &data,
	                              mode,
	                              root);
	if (result < buflen)
		buffer[result] = '\0';
	++result;
	return result;
}

PUBLIC NONNULL((3)) size_t KCALL
path_sprint(USER CHECKED char *buffer, size_t buflen,
            struct path *__restrict self)
		THROWS(E_SEGFAULT) {
	size_t result;
	struct format_snprintf_data data;
	format_snprintf_init(&data, buffer, buflen);
	result = (size_t)path_print(self,
	                            &format_snprintf_printer,
	                            &data);
	if (result < buflen)
		buffer[result] = '\0';
	++result;
	return result;
}



INTDEF NONNULL((1)) void KCALL
superblock_set_unmounted_impl(struct superblock *__restrict self)
		THROWS(E_WOULDBLOCK, E_IOERROR, ...);

INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL superblock_schedule_set_unmounted)(struct superblock *__restrict self);


PUBLIC void KCALL
path_mount(struct path *__restrict self,
           struct directory_node *__restrict node,
           bool override_existing)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_FSERROR_PATH_ALREADY_MOUNTED,
		       E_FSERROR_DELETED, ...) {
	struct vfs *v                  = self->p_vfs;
	struct superblock *super       = node->i_super;
	struct mounted_path *new_mount = NULL;
	if (self != v && ATOMIC_READ(self->p_mount) == NULL)
		new_mount = (struct mounted_path *)kmalloc(sizeof(struct mounted_path), FS_GFP);
again_acquire_locks:
	TRY {
		/* Must acquire locks to:
		 *  `self->p_lock'        (sync_write(self))
		 *  `v->v_mount_lock'     (sync_write(&v->v_mount_lock))
		 *  `super->s_mount_lock' (superblock_mountlock_write(super)) */
		SYNC_ACQUIRE3(sync_trywrite(self),
		              sync_write(self),
		              sync_endwrite(self),

		              sync_trywrite(&v->v_mount_lock),
		              sync_write(&v->v_mount_lock),
		              sync_endwrite(&v->v_mount_lock),

		              superblock_mountlock_trywrite(super),
		              superblock_mountlock_write(super),
		              superblock_mountlock_endwrite(super));
	} EXCEPT {
		kfree(new_mount);
		RETHROW();
	}
	COMPILER_READ_BARRIER();
	/* Check if the new superblock has already been marked as being unmounted. */
	if unlikely(ATOMIC_READ(super->s_flags) &
	            (SUPERBLOCK_FUNMOUNTED | SUPERBLOCK_FMUSTUNMOUNT)) {
		superblock_mountlock_endwrite(super);
		sync_endwrite(&v->v_mount_lock);
		sync_endwrite(self);
		kfree(new_mount);
		THROW(E_FSERROR_DELETED, E_FILESYSTEM_DELETED_UNMOUNTED);
	}
	/* All right! we've got all the required locks! */
	if unlikely(self->p_mount) {
		struct superblock *old_super;
		struct directory_node *old_node;
		if (new_mount) {
			kfree(new_mount);
			new_mount = NULL;
		}
		sync_endwrite(&v->v_mount_lock);
		if (!override_existing) {
			superblock_mountlock_endwrite(super);
			old_node = self->p_inode;
			sync_endwrite(self);
			if (old_node == node)
				return; /* No-op (same mounting location) */
			THROW(E_FSERROR_PATH_ALREADY_MOUNTED);
		}
		/* Must remove an existing mounting point. */
		old_super = self->p_mount->mp_super;
		if (old_super == super) {
			/* Simple case: same super-block. */
			superblock_mountlock_endwrite(super);
			old_node      = self->p_inode;
			self->p_inode = (REF struct directory_node *)incref(node);
			sync_endwrite(self);
			xdecref(old_node);
			return;
		}
		/* Difficult case: must unmount the old superblock! */
		if unlikely(!superblock_mountlock_trywrite(old_super)) {
			incref(old_super);
			superblock_mountlock_endwrite(super);
			sync_endwrite(self);
			TRY {
				superblock_mountlock_write(old_super);
			} EXCEPT {
				decref_unlikely(old_super);
				RETHROW();
			}
			superblock_mountlock_endwrite(old_super);
			decref_unlikely(old_super);
			goto again_acquire_locks;
		}
		if (self == old_super->s_mount &&
		    self->p_mount->mp_fsmount.ln_next == NULL &&
		    !(ATOMIC_READ(old_super->s_flags) & SUPERBLOCK_FUNMOUNTED)) {
			assert(self->p_mount->mp_fsmount.ln_pself == &old_super->s_mount);
			/* This will be the last mounting point, but the superblock
			 * hasn't been marked as being unmounted, yet. */
			if unlikely(!superblock_nodeslock_trywrite(old_super)) {
				superblock_mountlock_endwrite(super);
				incref(old_super);
				sync_endwrite(self);
				superblock_mountlock_endwrite(old_super);
				TRY {
					superblock_nodeslock_write(old_super);
				} EXCEPT {
					decref_unlikely(old_super);
					RETHROW();
				}
				superblock_nodeslock_endwrite(old_super);
				decref_unlikely(old_super);
				goto again_acquire_locks;
			}
			if (!(ATOMIC_FETCHOR(old_super->s_flags, SUPERBLOCK_FUNMOUNTED) & SUPERBLOCK_FUNMOUNTED)) {
				superblock_mountlock_endwrite(super);
				incref(old_super);
				sync_endwrite(self);
				superblock_mountlock_endwrite(old_super);
				TRY {
					superblock_set_unmounted_impl(old_super);
				} EXCEPT {
					superblock_nodeslock_endwrite(old_super);
					decref_unlikely(old_super);
					RETHROW();
				}
				superblock_nodeslock_endwrite(old_super);
				/* Clear recently used INodes, thus uncaching any that were apart of `old_super' */
				FINALLY_DECREF_UNLIKELY(old_super);
				inode_recent_clear();
				goto again_acquire_locks;
			}
			superblock_nodeslock_endwrite(old_super);
		}
		/* The old superblock has now been set to be unmounted (if it had to be) */
		COMPILER_READ_BARRIER();
		if (ATOMIC_READ(self->p_mount->mp_fsmount.ln_pself) != NULL)
			LLIST_REMOVE(self, p_mount->mp_fsmount);
		new_mount = self->p_mount;
		/* Drop references stored in the old new_mount structure. */
		new_mount->mp_super = (REF struct superblock *)incref(super); /* Inherit old reference into `old_super' */
		/* Set the new mounting as part of the associated superblock. */
		LLIST_INSERT(super->s_mount, self, p_mount->mp_fsmount);
		superblock_mountlock_endwrite(super);
		/* Update the effectively mounted INode within out path segment. */
		old_node      = self->p_inode;
		self->p_inode = (REF struct directory_node *)incref(node);
		sync_endwrite(self);
		decref(old_super); /* mp_super */
		xdecref(old_node); /* p_inode */
		return;
	}
	assert(!self->p_mount);
	if (!new_mount) {
		/* Allocate missing mounting points. */
		if (v == self)
			new_mount = &((struct vfs *)self)->v_rootmount;
		else {
			/* Try to allocate the missing mounted_path structure without blocking. */
			new_mount = (struct mounted_path *)kmalloc_nx(sizeof(struct mounted_path),
			                                              FS_GFP | GFP_ATOMIC);
			/* If that fails, release all locks, allocate it w/ blocking, and start over. */
			if unlikely(!new_mount) {
				superblock_mountlock_endwrite(super);
				sync_endwrite(&v->v_mount_lock);
				sync_endwrite(self);
				new_mount = (struct mounted_path *)kmalloc(sizeof(struct mounted_path), FS_GFP);
				/* Do another pass where `new_mount' has actually been allocated. */
				goto again_acquire_locks;
			}
		}
	}
	/* Fill in the new mounting point structure. */
	new_mount->mp_path  = self;
	new_mount->mp_orig  = self->p_inode; /* Inherit reference. */
	new_mount->mp_super = (REF struct superblock *)incref(super);
	self->p_inode       = (REF struct directory_node *)incref(node);
	self->p_mount       = new_mount;

	LLIST_INSERT(super->s_mount, self, p_mount->mp_fsmount);
	{
		struct path *next_mount;
		new_mount->mp_vfsmount.ln_pself = &v->v_mount;
		/* The reference stored within the `v->v_mount' chain. */
		if (self != v)
			incref(self);
		for (;;) {
			next_mount = ATOMIC_READ(v->v_mount);
			if unlikely(next_mount == VFS_MOUNT_ILLEGAL) {
				/* Mounting has become illegal. */
				LLIST_REMOVE(self, p_mount->mp_fsmount);
				self->p_mount = NULL;
				self->p_inode = new_mount->mp_orig; /* Inherit reference. */
				superblock_mountlock_endwrite(super);
				sync_endwrite(&v->v_mount_lock);
				sync_endwrite(self);
				if (new_mount != &((struct vfs *)self)->v_rootmount)
					kfree(new_mount);
				decref(super);
				decref(node);
				if (self != v)
					decref_nokill(self);
				THROW(E_FSERROR_DELETED, E_FILESYSTEM_DELETED_UNMOUNTED);
			}
			new_mount->mp_vfsmount.ln_next = next_mount;
			COMPILER_WRITE_BARRIER();
			if (ATOMIC_CMPXCH_WEAK(v->v_mount, next_mount, self))
				break;
		}
	}
	/* Release all the locks we've acquired previously. */
	superblock_mountlock_endwrite(super);
	sync_endwrite(&v->v_mount_lock);
	sync_endwrite(self);
}


PRIVATE NOBLOCK void
NOTHROW(KCALL path_clear_cldlist)(struct path *__restrict self) {
	assert(sync_writing(self));
	if (self->p_cldlist) {
		self->p_cldmask = 0;
		self->p_cldsize = 0;
		kfree(self->p_cldlist);
		self->p_cldlist = NULL;
	}
}


PUBLIC void KCALL path_umount(struct path *__restrict self)
		THROWS(E_WOULDBLOCK, E_FSERROR_NOT_A_MOUNTING_POINT, E_IOERROR, ...) {
	struct vfs *v = self->p_vfs;
	struct superblock *super;
	REF struct inode *old_node;
	struct mounted_path *mount;
again_acquire_locks:
	sync_write(self);
	if unlikely((mount = self->p_mount) == NULL) {
		sync_endwrite(self);
		THROW(E_FSERROR_NOT_A_MOUNTING_POINT);
	}
	super = mount->mp_super;
	if unlikely(!superblock_mountlock_trywrite(super)) {
again_acquire_super:
		incref(super);
		sync_endwrite(self);
		TRY {
			superblock_mountlock_write(super);
		} EXCEPT {
			decref_unlikely(super);
			RETHROW();
		}
		decref_unlikely(super);
		goto again_acquire_locks;
	}
	if unlikely(!sync_trywrite(&v->v_mount_lock)) {
		superblock_mountlock_endwrite(super);
		sync_endwrite(self);
		sync_write(&v->v_mount_lock);
		if unlikely(!sync_trywrite(self)) {
			sync_endwrite(&v->v_mount_lock);
			goto again_acquire_locks;
		}
		if unlikely((mount = self->p_mount) == NULL) {
			sync_endwrite(self);
			sync_endwrite(&v->v_mount_lock);
			THROW(E_FSERROR_NOT_A_MOUNTING_POINT);
		}
		super = mount->mp_super;
		if unlikely(!superblock_mountlock_trywrite(super)) {
			sync_endwrite(&v->v_mount_lock);
			goto again_acquire_super;
		}
	}
	/* Must remove an existing mounting point. */
	if (self == super->s_mount &&
	    self->p_mount->mp_fsmount.ln_next == NULL &&
	    !(ATOMIC_READ(super->s_flags) & SUPERBLOCK_FUNMOUNTED)) {
		assert(self->p_mount->mp_fsmount.ln_pself == &super->s_mount);
		/* This will be the last mounting point, but the superblock
		 * hasn't been marked as being unmounted, yet. */
		if unlikely(!superblock_nodeslock_trywrite(super)) {
			sync_endwrite(&v->v_mount_lock);
			superblock_mountlock_endwrite(super);
			incref(super);
			sync_endwrite(self);
			TRY {
				superblock_nodeslock_write(super);
			} EXCEPT {
				decref_unlikely(super);
				RETHROW();
			}
			superblock_nodeslock_endwrite(super);
			decref_unlikely(super);
			goto again_acquire_locks;
		}
		if (!(ATOMIC_FETCHOR(super->s_flags, SUPERBLOCK_FUNMOUNTED) & SUPERBLOCK_FUNMOUNTED)) {
			sync_endwrite(&v->v_mount_lock);
			superblock_mountlock_endwrite(super);
			incref(super);
			sync_endwrite(self);
			TRY {
				superblock_set_unmounted_impl(super);
			} EXCEPT {
				superblock_nodeslock_endwrite(super);
				decref_unlikely(super);
				RETHROW();
			}
			superblock_nodeslock_endwrite(super);
			/* Clear recently used INodes, thus uncaching any that were apart of `super' */
			FINALLY_DECREF_UNLIKELY(super);
			inode_recent_clear();
			goto again_acquire_locks;
		}
	}
	/* The old superblock has now been set to be unmounted (if it had to be) */
	COMPILER_READ_BARRIER();
	if (ATOMIC_READ(mount->mp_fsmount.ln_pself) != NULL)
		LLIST_REMOVE(self, p_mount->mp_fsmount);
	superblock_mountlock_endwrite(super);
	if (ATOMIC_READ(mount->mp_vfsmount.ln_pself) != NULL) {
		LLIST_REMOVE(self, p_mount->mp_vfsmount);
		/* The reference stored within the `v->v_mount' chain. */
		if (self != v)
			decref_nokill(self);
	}
	sync_endwrite(&v->v_mount_lock);
	old_node      = self->p_inode;          /* Inherit reference. */
	self->p_inode = self->p_mount->mp_orig; /* Inherit reference. */
	self->p_mount = NULL;
	path_clear_cldlist(self); /* Clear the list of known child-paths of our directory. */
	sync_endwrite(self);
	if (mount != &((struct vfs *)self)->v_rootmount)
		kfree(mount);
	xdecref(old_node); /* p_inode */
	decref(super);     /* mp_super */
	/* Clear all recently used paths, thus doing our best
	 * to remove any that were apart of the deleted path.
	 * Note that there does exist a race condition where
	 * another thread may have walked a sub-path of the old
	 * mounting point, and hasn't yet marked their final path
	 * segment as recently used, in which case a non-existent
	 * path may show in cache. - But that's OK, since this is
	 * only a cache that is meant to keep paths alive between
	 * individual accesses, so keeping a deleted path alive for
	 * longer than necessarily is unnecessary, but not dangerous. */
	path_recent_clear(v);
}

PUBLIC void KCALL
path_movemount(struct path *__restrict dst,
               struct path *__restrict src,
               bool override_existing)
		THROWS(E_WOULDBLOCK, E_FSERROR_NOT_A_MOUNTING_POINT,
		       E_FSERROR_PATH_ALREADY_MOUNTED, E_IOERROR, ...) {
	struct vfs *v = dst->p_vfs;
	struct directory_node *src_node;
	struct superblock *src_super;
	struct mounted_path *src_mount;
	struct mounted_path *dst_mount = NULL;
	if (dst != src && ATOMIC_READ(dst->p_mount) == NULL && src == v)
		dst_mount = (struct mounted_path *)kmalloc(sizeof(struct mounted_path), FS_GFP);
	assert(dst->p_vfs == src->p_vfs);
again_acquire_locks:
	sync_write(src);
	if unlikely((src_mount = src->p_mount) == NULL) {
		sync_endwrite(src);
		THROW(E_FSERROR_NOT_A_MOUNTING_POINT);
	}
	if unlikely(dst == src) {
		/* Special case: Don't actually move, the check that `src' is a
		 *               mounting point was all we really had to do. */
		sync_endwrite(src);
		kfree(dst_mount);
		return;
	}
	src_super = src_mount->mp_super;
	if unlikely(!superblock_mountlock_trywrite(src_super)) {
again_acquire_super:
		incref(src_super);
		sync_endwrite(src);
		TRY {
			superblock_mountlock_write(src_super);
		} EXCEPT {
			decref_unlikely(src_super);
			RETHROW();
		}
		decref_unlikely(src_super);
		goto again_acquire_locks;
	}
	if unlikely(!sync_trywrite(&v->v_mount_lock)) {
again_acquire_mount_lock:
		superblock_mountlock_endwrite(src_super);
		sync_endwrite(src);
		sync_write(&v->v_mount_lock);
		if unlikely(!sync_trywrite(src)) {
			sync_endwrite(&v->v_mount_lock);
			goto again_acquire_locks;
		}
		if unlikely((src_mount = src->p_mount) == NULL) {
			sync_endwrite(src);
			sync_endwrite(&v->v_mount_lock);
			THROW(E_FSERROR_NOT_A_MOUNTING_POINT);
		}
		src_super = src_mount->mp_super;
		if unlikely(!superblock_mountlock_trywrite(src_super)) {
			sync_endwrite(&v->v_mount_lock);
			goto again_acquire_super;
		}
	}
	if (!sync_trywrite(dst)) {
		sync_endwrite(&v->v_mount_lock);
		superblock_mountlock_endwrite(src_super);
		sync_endwrite(src);
		sync_write(dst);
		if unlikely(!sync_trywrite(src)) {
			sync_endwrite(dst);
			goto again_acquire_locks;
		}
		if unlikely((src_mount = src->p_mount) == NULL) {
			sync_endwrite(dst);
			sync_endwrite(src);
			sync_endwrite(&v->v_mount_lock);
			THROW(E_FSERROR_NOT_A_MOUNTING_POINT);
		}
		src_super = src_mount->mp_super;
		if unlikely(!superblock_mountlock_trywrite(src_super)) {
			sync_endwrite(dst);
			goto again_acquire_super;
		}
		if unlikely(!sync_trywrite(&v->v_mount_lock)) {
			sync_endwrite(dst);
			goto again_acquire_mount_lock;
		}
	}
	/* All right! At this point we've got all of the necessary locks:
	 *   - sync_write(dst);
	 *   - sync_write(&v->v_mount_lock);
	 *   - superblock_mountlock_write(src_super);
	 *   - sync_write(src);
	 * Now quickly check if `dst' is already a mounting point. */
	src_node = src->p_inode;
	if (dst->p_mount != NULL) {
		/* `dst' _is_ already a mounting point... */
		struct superblock *dst_old_super;
		struct directory_node *dst_old_node;
		if (dst_mount) {
			kfree(dst_mount);
			dst_mount = NULL;
		}
		dst_old_node = dst->p_inode;
		if (!override_existing) {
			sync_endwrite(&v->v_mount_lock);
			superblock_mountlock_endwrite(src_super);
			sync_endwrite(dst);
			sync_endwrite(src);
			if (dst_old_node == src_node)
				return; /* No-op (same mounted object location) */
			THROW(E_FSERROR_PATH_ALREADY_MOUNTED);
		}
		/* Must remove an existing mounting point. */
		dst_old_super = dst->p_mount->mp_super;
		if (dst_old_super == src_super) {
			/* Simple case: same super-block. */
			assert(src_node == src->p_inode);
			dst->p_inode = src_node; /* Inherit reference */
			sync_endwrite(dst);
			/* Must still remove the existing mounting point from `src' */
			COMPILER_READ_BARRIER();
			if (ATOMIC_READ(src_mount->mp_fsmount.ln_pself) != NULL)
				LLIST_REMOVE(src, p_mount->mp_fsmount);
			superblock_mountlock_endwrite(src_super);
			if (ATOMIC_READ(src_mount->mp_vfsmount.ln_pself) != NULL)
				LLIST_REMOVE(src, p_mount->mp_vfsmount);
			/* The reference stored within the `v->v_mount' chain. */
			if (src != v)
				decref_nokill(src);
			sync_endwrite(&v->v_mount_lock);
			assert(src_node == src->p_inode);
			assert(src->p_mount == src_mount);
			src->p_inode = src_mount->mp_orig; /* Inherit reference. */
			src->p_mount = NULL;
			path_clear_cldlist(src); /* Clear the list of known child-paths of our directory. */
			sync_endwrite(src);
			if (src_mount != &v->v_rootmount)
				kfree(src_mount);
			xdecref(dst_old_node);      /* dst->p_inode */
			decref_unlikely(src_super); /* src->p_mount->mp_super */
			path_recent_clear(v);
			return;
		}
		/* Difficult case: must unmount the old superblock! */
		if unlikely(!superblock_mountlock_trywrite(dst_old_super)) {
			incref(dst_old_super);
			sync_endwrite(dst);
			sync_endwrite(&v->v_mount_lock);
			superblock_mountlock_endwrite(src_super);
			sync_endwrite(src);
			TRY {
				superblock_mountlock_write(dst_old_super);
			} EXCEPT {
				decref_unlikely(dst_old_super);
				RETHROW();
			}
			superblock_mountlock_endwrite(dst_old_super);
			decref_unlikely(dst_old_super);
			goto again_acquire_locks;
		}
		if (dst == dst_old_super->s_mount &&
		    dst->p_mount->mp_fsmount.ln_next == NULL &&
		    !(ATOMIC_READ(dst_old_super->s_flags) & SUPERBLOCK_FUNMOUNTED)) {
			assert(dst->p_mount->mp_fsmount.ln_pself == &dst_old_super->s_mount);
			/* This will be the last mounting point, but the superblock
			 * hasn't been marked as being unmounted, yet. */
			if unlikely(!superblock_nodeslock_trywrite(dst_old_super)) {
				incref(dst_old_super);
				sync_endwrite(dst);
				sync_endwrite(&v->v_mount_lock);
				superblock_mountlock_endwrite(src_super);
				sync_endwrite(src);
				superblock_mountlock_endwrite(dst_old_super);
				TRY {
					superblock_nodeslock_write(dst_old_super);
				} EXCEPT {
					decref_unlikely(dst_old_super);
					RETHROW();
				}
				superblock_nodeslock_endwrite(dst_old_super);
				decref_unlikely(dst_old_super);
				goto again_acquire_locks;
			}
			if (!(ATOMIC_FETCHOR(dst_old_super->s_flags, SUPERBLOCK_FUNMOUNTED) & SUPERBLOCK_FUNMOUNTED)) {
				incref(dst_old_super);
				superblock_mountlock_endwrite(dst_old_super);
				superblock_mountlock_endwrite(src_super);
				sync_endwrite(&v->v_mount_lock);
				sync_endwrite(src);
				sync_endwrite(dst);
				TRY {
					superblock_set_unmounted_impl(dst_old_super);
				} EXCEPT {
					superblock_nodeslock_endwrite(dst_old_super);
					decref_unlikely(dst_old_super);
					RETHROW();
				}
				superblock_nodeslock_endwrite(dst_old_super);
				/* Clear recently used INodes, thus uncaching any that were apart of `old_super' */
				FINALLY_DECREF_UNLIKELY(dst_old_super);
				inode_recent_clear();
				goto again_acquire_locks;
			}
			superblock_nodeslock_endwrite(dst_old_super);
		}
		/* The old superblock has now been set to be unmounted (if it had to be) */
		COMPILER_READ_BARRIER();
		assert(!dst_mount);
		dst_mount = dst->p_mount;
		assert(dst_mount->mp_super == dst_old_super);
		if (ATOMIC_READ(dst_mount->mp_fsmount.ln_pself) != NULL)
			LLIST_REMOVE(dst, p_mount->mp_fsmount);
		superblock_mountlock_endwrite(dst_old_super);
		/* Drop references stored in the old new_mount structure. */
		dst_mount->mp_super = src_super; /* Inherit reference (from `src_mount->mp_super') */
		/* Set the new mounting as part of the associated superblock. */
		LLIST_INSERT(src_super->s_mount, dst, p_mount->mp_fsmount);
		assert(src->p_mount == src_mount);
		if (ATOMIC_READ(src_mount->mp_fsmount.ln_pself) != NULL)
			LLIST_REMOVE(src, p_mount->mp_fsmount);
		superblock_mountlock_endwrite(src_super);
		/* Update the effectively mounted INode within out path segment. */
		assert(dst_old_node == dst->p_inode);
		dst->p_inode = src_node; /* Inherit reference. */
		sync_endwrite(dst);
		sync_endwrite(&v->v_mount_lock);
		assert(src->p_mount == src_mount);
		assert(src->p_inode == src_node);
		src->p_inode = src_mount->mp_orig; /* Inherit reference. */
		src->p_mount = NULL;
		path_clear_cldlist(src); /* Clear the list of known child-paths of our directory. */
		sync_endwrite(src);
		if (src_mount != &v->v_rootmount)
			kfree(src_mount);
		decref(dst_old_super); /* mp_super */
		xdecref(dst_old_node); /* p_inode */
		/* Clear all recently used paths, thus doing our best
		 * to remove any that were apart of the deleted path.
		 * Note that there does exist a race condition where
		 * another thread may have walked a sub-path of the old
		 * mounting point, and hasn't yet marked their final path
		 * segment as recently used, in which case a non-existent
		 * path may show in cache. - But that's OK, since this is
		 * only a cache that is meant to keep paths alive between
		 * individual accesses, so keeping a deleted path alive for
		 * longer than necessarily is wasteful, but not dangerous. */
		path_recent_clear(v);
		return;
	}
	/* Simple case: We can just move the mounting point. */
	if (dst == v) {
		assert(!dst_mount);
		dst_mount = &v->v_rootmount;
	} else if (src != v) {
		/* Re-use the mount entry of `src' */
		assert(!dst_mount);
		assert(src_node == src->p_inode);
		src->p_inode       = src_mount->mp_orig; /* Inherit reference */
		src_mount->mp_orig = dst->p_inode;       /* Inherit reference */
		dst->p_inode       = src_node;           /* Inherit reference */
		dst->p_mount       = src_mount;
		src->p_mount       = NULL;
		src_mount->mp_path = dst;
		sync_endwrite(dst);
		sync_endwrite(&v->v_mount_lock);
		superblock_mountlock_endwrite(src_super);
		sync_endwrite(src);
		return;
	} else if unlikely(!dst_mount) {
		dst_mount = (struct mounted_path *)kmalloc_nx(sizeof(struct mounted_path),
		                                              FS_GFP | GFP_ATOMIC);
		if (!dst_mount) {
			sync_endwrite(dst);
			sync_endwrite(&v->v_mount_lock);
			superblock_mountlock_endwrite(src_super);
			sync_endwrite(src);
			dst_mount = (struct mounted_path *)kmalloc(sizeof(struct mounted_path),
			                                           FS_GFP);
			goto again_acquire_locks;
		}
	}
	assert(!dst->p_mount);
	/* Add `dst' to the chain of mounted paths of the associated VFS */
	if (dst != v)
		incref(dst);
	dst->p_mount = dst_mount;
	for (;;) {
		struct path *next_mount;
		next_mount = ATOMIC_READ(v->v_mount);
		if unlikely(next_mount == VFS_MOUNT_ILLEGAL) {
			/* Mounting has become illegal. */
			dst->p_mount = NULL;
			sync_endwrite(dst);
			sync_endwrite(&v->v_mount_lock);
			superblock_mountlock_endwrite(src_super);
			sync_endwrite(src);
			if (dst_mount != &v->v_rootmount)
				kfree(dst_mount);
			if (dst != v)
				decref_nokill(dst);
			THROW(E_FSERROR_DELETED, E_FILESYSTEM_DELETED_UNMOUNTED);
		}
		dst_mount->mp_vfsmount.ln_next = next_mount;
		COMPILER_WRITE_BARRIER();
		if (ATOMIC_CMPXCH_WEAK(v->v_mount, next_mount, dst))
			break;
	}
	dst_mount->mp_orig    = dst->p_inode;       /* Inherit reference. */
	dst->p_inode          = src->p_inode;       /* Inherit reference. */
	src->p_inode          = src_mount->mp_orig; /* Inherit reference. */
	src->p_mount          = NULL;
	dst_mount->mp_path    = dst;
	dst_mount->mp_super   = src_super;             /* Inherit reference. */
	dst_mount->mp_fsmount = src_mount->mp_fsmount; /* Inherit link. */
	/* XXX: Whenever accessing the `mp_fsmount' chain, wouldn't we
	 *      need to acquire a lock to the neighboring paths, too? */
	if likely(dst_mount->mp_fsmount.ln_pself)
		*dst_mount->mp_fsmount.ln_pself = dst;
	if (dst_mount->mp_fsmount.ln_next)
		dst_mount->mp_fsmount.ln_next->p_mount->mp_fsmount.ln_pself = &dst_mount->mp_fsmount.ln_next;
	sync_endwrite(dst);
	sync_endwrite(&v->v_mount_lock);
	superblock_mountlock_endwrite(src_super);
	sync_endwrite(src);
	if (src_mount != &v->v_rootmount)
		kfree(src_mount);
	/* The reference stored within the `v->v_mount' chain. */
	if (src != v)
		decref_nokill(src);
}



/* Remove an entry from a given path.
 * @param: mode: Set of `DIRECTORY_REMOVE_F*', or which at least one of
 *              `DIRECTORY_REMOVE_FREGULAR' or `DIRECTORY_REMOVE_FDIRECTORY'
 *               must be given.
 * @param: premoved_inode:  Upon success, store a reference to the removed INode here.
 * @param: premoved_dirent: Upon success, store a reference to the removed INode's directory entry here.
 * @param: pcontaining_directory: Upon success, store a reference to the directory node from which an element got removed here.
 *                                Since `self->p_inode' can arbitrarily change due to mounting, this is the
 *                                only save way to determine the exact directory from which the element got removed.
 * @param: premoved_path:         Upon success, store a reference to the removed path here (or `NULL' if it wasn't
 *                                a directory that got removed, or if that directory didn't have a path node)
 * @return: * : Set of `DIRECTORY_REMOVE_STATUS_*'
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...] (the specified file was already deleted)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH: [...] (self was deleted)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_FSERROR_FILE_NOT_FOUND:      The specified `name' could not be found
 * @throw: E_FSERROR_ACCESS_DENIED:       `DIRECTORY_REMOVE_FCHKACCESS' was set, and the calling thread is not allowed to delete the file.
 * @throw: E_FSERROR_NOT_A_DIRECTORY:E_FILESYSTEM_NOT_A_DIRECTORY_RMDIR:  The given `name' refers to a regular file, but `DIRECTORY_REMOVE_FREGULAR' isn't set
 * @throw: E_FSERROR_IS_A_DIRECTORY:E_FILESYSTEM_IS_A_DIRECTORY_UNLINK:   The given `name' refers to a directory, but `DIRECTORY_REMOVE_FDIRECTORY' isn't set
 * @throw: E_FSERROR_IS_A_MOUNTING_POINT:                                 The given `name' refers to a mounting point
 * @throw: E_FSERROR_DIRECTORY_NOT_EMPTY: Attempted to remove a non-empty directory.
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_UNLINK: Cannot unlink files within `self'
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_RMDIR:  Cannot remove sub-directories of `self'
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_TRUNC:  Cannot truncate non-empty files to 0 bytes in order to delete their data
 * @throw: E_FSERROR_READONLY:            [...]
 * @throw: E_IOERROR:                     [...] */
PUBLIC NONNULL((1, 2)) unsigned int KCALL
path_remove(struct path *__restrict self,
            CHECKED USER /*utf-8*/ char const *__restrict name,
            u16 namelen, uintptr_t hash, unsigned int mode,
            /*out*/ REF struct inode **premoved_inode,
            /*out*/ REF struct directory_entry **premoved_dirent,
            /*out*/ REF struct directory_node **pcontaining_directory,
            /*out*/ REF struct path **premoved_path)
		THROWS(E_FSERROR_DELETED, E_FSERROR_DIRECTORY_NOT_EMPTY,
		       E_FSERROR_FILE_NOT_FOUND, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_NOT_A_DIRECTORY, E_FSERROR_IS_A_DIRECTORY,
		       E_FSERROR_IS_A_MOUNTING_POINT, E_FSERROR_UNSUPPORTED_OPERATION,
		       E_FSERROR_READONLY, E_IOERROR, E_SEGFAULT, ...) {
	REF struct directory_node *mynode;
	unsigned int result;
again:
	sync_read(self);
	mynode = (REF struct directory_node *)incref(self->p_inode);
	sync_endread(self);
	TRY {
		result = directory_remove(mynode,
		                          name,
		                          namelen,
		                          hash,
		                          mode | DIRECTORY_REMOVE_FCHKPMOUNT,
		                          premoved_inode,
		                          premoved_dirent,
		                          self,
		                          premoved_path);
	} EXCEPT {
		decref(mynode);
		RETHROW();
	}
	/* Deal with the rare case of a re-mount. */
	if unlikely(result == DIRECTORY_REMOVE_STATUS_REMOUNT) {
		decref(mynode);
		goto again;
	}
	if (pcontaining_directory)
		*pcontaining_directory = mynode;
	else
		decref(mynode);
	return result;
}


/* Rename/move an entry from one path to another.
 * NOTE: This function will try to emulate an unsupported `rename()' using `link()' + `unlink()'
 * @param: mode: Set of `DIRECTORY_RENAME_F*'
 * @param: psource_dirent:    When non-NULL, store a reference to the source directory entry here.
 * @param: ptarget_dirent:    When non-NULL, store a reference to the target directory entry here.
 * @param: psource_inode:     When non-NULL, store a reference to the source INode here.
 * @param: ptarget_inode:     When non-NULL, store a reference to the target INode here.
 * @param: psource_directory: When non-NULL, store a reference to the source directory from which an element got removed here.
 * @param: ptarget_directory: When non-NULL, store a reference to the target directory to which an element got added here.
 * @param: premoved_path:     When non-NULL, store a reference to the removed child-path
 *                            of `source_path' here, or `NULL' if no path got removed.
 * @return: * : Set of `DIRECTORY_RENAME_STATUS_*', though never `DIRECTORY_RENAME_STATUS_REMOUNT'
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
PUBLIC NONNULL((1, 2, 5, 6)) unsigned int KCALL
path_rename(struct path *__restrict source_path,
            CHECKED USER /*utf-8*/ char const *__restrict source_name,
            u16 source_namelen, uintptr_t source_namehash,
            struct path *__restrict target_path,
            CHECKED USER /*utf-8*/ char const *__restrict target_name,
            u16 target_namelen, unsigned int mode,
            /*out*/ REF struct directory_entry **psource_dirent,
            /*out*/ REF struct directory_entry **ptarget_dirent,
            /*out*/ REF struct inode **psource_inode,
            /*out*/ REF struct inode **ptarget_inode,
            /*out*/ REF struct directory_node **psource_directory,
            /*out*/ REF struct directory_node **ptarget_directory,
            /*out*/ REF struct path **premoved_path)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_DELETED,
		       E_FSERROR_CROSS_DEVICE_LINK, E_FSERROR_FILE_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_FILE_ALREADY_EXISTS,
		       E_FSERROR_DISK_FULL, E_FSERROR_TOO_MANY_HARD_LINKS,
		       E_FSERROR_DIRECTORY_MOVE_TO_CHILD, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_IS_A_MOUNTING_POINT, E_FSERROR_READONLY,
		       E_IOERROR, E_SEGFAULT, ...) {
	unsigned int result;
	REF struct directory_node *source_directory;
	REF struct directory_node *target_directory;
again:
	sync_read(source_path);
	source_directory = (REF struct directory_node *)incref(source_path->p_inode);
	sync_endread(source_path);
	TRY {
		if (source_path == target_path) {
			target_directory = (REF struct directory_node *)incref(source_directory);
		} else {
			sync_read(target_path);
			target_directory = (REF struct directory_node *)incref(target_path->p_inode);
			sync_endread(target_path);
		}
		TRY {
			result = directory_rename(source_directory,
			                          source_name,
			                          source_namelen,
			                          source_namehash,
			                          target_directory,
			                          target_name,
			                          target_namelen,
			                          mode | DIRECTORY_RENAME_FCHKPMOUNT,
			                          psource_dirent,
			                          ptarget_dirent,
			                          psource_inode,
			                          ptarget_inode,
			                          source_path,
			                          premoved_path);
		} EXCEPT {
			decref(source_directory);
			RETHROW();
		}
	} EXCEPT {
		decref(source_directory);
		RETHROW();
	}
	/* If the intended directory was remounted due to a race condition, try again. */
	if unlikely(result == DIRECTORY_RENAME_STATUS_REMOUNT) {
		decref(target_directory);
		decref(source_directory);
		goto again;
	}
	if (ptarget_directory)
		*ptarget_directory = target_directory;
	else {
		decref(target_directory);
	}
	if (psource_directory)
		*psource_directory = source_directory;
	else {
		decref(source_directory);
	}
	return result;
}





INTDEF NOBLOCK void
NOTHROW(KCALL path_rehash_smaller_nx)(struct path *__restrict self);


LOCAL NOBLOCK void
NOTHROW(KCALL path_mounted_destroy_after_vfs_umount)(struct path *__restrict self,
                                                     struct mounted_path *__restrict src_mount) {
	struct superblock *super;
	assert(src_mount->mp_path == self);
	super = src_mount->mp_super;
	if (ATOMIC_READ(src_mount->mp_fsmount.ln_pself) != NULL) {
		if unlikely(!superblock_mountlock_trywrite(super)) {
			struct path *next;
			do {
				next = ATOMIC_READ(super->s_umount_pend);
				src_mount->mp_pending = next;
			} while (!ATOMIC_CMPXCH_WEAK(super->s_umount_pend, next, self));
			superblock_mountlock_tryservice(super);
			decref(super);
			return;
		}
		if (ATOMIC_READ(src_mount->mp_fsmount.ln_pself) != NULL) {
			LLIST_REMOVE(self, p_mount->mp_fsmount);
			if (!super->s_mount &&
			    !(ATOMIC_FETCHOR(super->s_flags, SUPERBLOCK_FMUSTUNMOUNT) & SUPERBLOCK_FMUSTUNMOUNT))
				superblock_schedule_set_unmounted(super);
		}
		superblock_mountlock_endwrite(super);
	}
	decref(super);
	if (src_mount != &((struct vfs *)self)->v_rootmount)
		kfree(src_mount);
	if (self == self->p_vfs)
		kfree(self);
	else {
		path_free(self);
	}
}

LOCAL NOBLOCK void
NOTHROW(KCALL path_destroy_after_delpend)(struct path *__restrict self) {
	/* Already done: `p_parent', `p_inode', `p_cldlist', `p_delpend' */
	/* Still missing: `p_mount', `p_dirent' */
	struct mounted_path *mount;
	/* NOTE: We wait with decref()-ing `self->p_dirent' until now, so that
	 *       the path_child() functions don't need to tryincref() before
	 *       being able to access `p_dirent' when searching for some specific
	 *       entry. */
	decref(self->p_dirent);
	mount = self->p_mount;
	if likely(!mount) {
		if (self == self->p_vfs)
			kfree(self);
		else {
			path_free(self);
		}
		return;
	}
	assert(mount->mp_path == self);
	assertf(mount->mp_vfsmount.ln_pself == NULL,
	        "But the `struct vfs::v_mount' should have been holding a reference...");
	xdecref(mount->mp_orig);
	path_mounted_destroy_after_vfs_umount(self, mount);
}


#define PATH_LOCK_MUST_SERVICE(self) \
	(ATOMIC_READ((self)->p_delpend) != NULL)

LOCAL NOBLOCK void
NOTHROW(KCALL path_lock_do_service)(struct path *__restrict self) {
	struct path *pend, *next;
	pend = ATOMIC_XCH(self->p_delpend, NULL);
	while (pend) {
		next = pend->p_delpend;
		if (ATOMIC_READ(pend->p_dirnext.ln_pself) != NULL) {
			LLIST_REMOVE(pend, p_dirnext);
			assert(self->p_cldsize != 0);
			--self->p_cldsize;
			if (self->p_cldsize < (self->p_cldmask / 3))
				path_rehash_smaller_nx(self);
		}
		path_destroy_after_delpend(pend);
		pend = next;
	}
}

PUBLIC void KCALL
path_lock_read(struct path *__restrict self) THROWS(E_WOULDBLOCK) {
	sync_read(&self->p_lock);
	if (PATH_LOCK_MUST_SERVICE(self)) {
		if (sync_tryupgrade(&self->p_lock)) {
			path_lock_do_service(self);
			sync_downgrade(&self->p_lock);
		}
	}
}

PUBLIC void KCALL
path_lock_write(struct path *__restrict self) THROWS(E_WOULDBLOCK) {
	sync_write(&self->p_lock);
	path_lock_do_service(self);
}

PUBLIC bool KCALL
path_lock_upgrade(struct path *__restrict self) THROWS(E_WOULDBLOCK) {
	bool result;
	result = sync_upgrade(&self->p_lock);
	path_lock_do_service(self);
	return result;
}

PUBLIC WUNUSED bool
NOTHROW(KCALL path_lock_read_nx)(struct path *__restrict self) {
	if (!sync_read_nx(&self->p_lock))
		return false;
	if (PATH_LOCK_MUST_SERVICE(self)) {
		if (sync_tryupgrade(&self->p_lock)) {
			path_lock_do_service(self);
			sync_downgrade(&self->p_lock);
		}
	}
	return true;
}

PUBLIC WUNUSED bool
NOTHROW(KCALL path_lock_write_nx)(struct path *__restrict self) {
	if (!sync_write_nx(&self->p_lock))
		return false;
	path_lock_do_service(self);
	return true;
}

PUBLIC WUNUSED unsigned int
NOTHROW(KCALL path_lock_upgrade_nx)(struct path *__restrict self) {
	unsigned int result;
	result = sync_upgrade_nx(&self->p_lock);
	if (result != 0)
		path_lock_do_service(self);
	return result;
}

PUBLIC NOBLOCK WUNUSED bool
NOTHROW(KCALL path_lock_tryread)(struct path *__restrict self) {
	if (!sync_tryread(&self->p_lock))
		return false;
	if (PATH_LOCK_MUST_SERVICE(self)) {
		if (sync_tryupgrade(&self->p_lock)) {
			path_lock_do_service(self);
			sync_downgrade(&self->p_lock);
		}
	}
	return true;
}

PUBLIC NOBLOCK WUNUSED bool
NOTHROW(KCALL path_lock_trywrite)(struct path *__restrict self) {
	if (!sync_trywrite(&self->p_lock))
		return false;
	path_lock_do_service(self);
	return true;
}

PUBLIC NOBLOCK WUNUSED bool
NOTHROW(KCALL path_lock_tryupgrade)(struct path *__restrict self) {
	if (!sync_tryupgrade(&self->p_lock))
		return false;
	path_lock_do_service(self);
	return true;
}

PUBLIC NOBLOCK void
NOTHROW(KCALL path_lock_endread)(struct path *__restrict self) {
again:
	sync_endread(&self->p_lock);
	if (PATH_LOCK_MUST_SERVICE(self)) {
		if (sync_trywrite(&self->p_lock)) {
			path_lock_do_service(self);
			sync_downgrade(&self->p_lock);
			goto again;
		}
	}
}

PUBLIC NOBLOCK void
NOTHROW(KCALL path_lock_endwrite)(struct path *__restrict self) {
again:
	sync_endwrite(&self->p_lock);
	if (PATH_LOCK_MUST_SERVICE(self)) {
		if (sync_trywrite(&self->p_lock)) {
			path_lock_do_service(self);
			goto again;
		}
	}
}

PUBLIC NOBLOCK void
NOTHROW(KCALL path_lock_end)(struct path *__restrict self) {
again:
	sync_end(&self->p_lock);
	if (PATH_LOCK_MUST_SERVICE(self)) {
		if (sync_trywrite(&self->p_lock)) {
			path_lock_do_service(self);
			goto again;
		}
	}
}

PUBLIC NOBLOCK void
NOTHROW(KCALL path_lock_downgrade)(struct path *__restrict self) {
again:
	sync_downgrade(&self->p_lock);
	if (PATH_LOCK_MUST_SERVICE(self)) {
		if (sync_tryupgrade(&self->p_lock)) {
			path_lock_do_service(self);
			goto again;
		}
	}
}

PUBLIC NOBLOCK void
NOTHROW(KCALL path_lock_tryservice)(struct path *__restrict self) {
	do {
		if (!sync_trywrite(&self->p_lock))
			break;
		path_lock_do_service(self);
		sync_endwrite(&self->p_lock);
	} while unlikely(PATH_LOCK_MUST_SERVICE(self));
}



/* Destroy (and free) a given path `self' */
PUBLIC NOBLOCK void
NOTHROW(KCALL path_destroy)(struct path *__restrict self) {
	struct path *parent;
	path_lock_do_service(self);
	assertf(self->p_recent.ln_pself == NULL,
	        "The recently-used cache should have kept us alive!");
	assertf(self->p_cldsize == 0,
	        "Child path nodes should have kept us alive!");
	kfree(self->p_cldlist);
	xdecref(self->p_inode);
	if ((parent = self->p_parent) != NULL) {
		if (ATOMIC_READ(self->p_dirnext.ln_pself) != NULL) {
			if unlikely(!sync_trywrite(parent)) {
				struct path *next;
				do {
					next = ATOMIC_READ(parent->p_delpend);
					self->p_delpend = next;
				} while (!ATOMIC_CMPXCH_WEAK(parent->p_delpend, next, self));
				path_lock_tryservice(parent);
				decref(parent);
				return;
			}
			/* Unlink the entry from the parent directory. */
			COMPILER_READ_BARRIER();
			if (ATOMIC_READ(self->p_dirnext.ln_pself) != NULL) {
				LLIST_REMOVE(self, p_dirnext);
				assert(parent->p_cldsize != 0);
				--parent->p_cldsize;
				if (parent->p_cldsize < (parent->p_cldmask / 3))
					path_rehash_smaller_nx(parent);
			}
			sync_endwrite(parent);
		}
		decref(parent);
	}
	path_destroy_after_delpend(self);
}



/* Called when `v_fscount' reaches ZERO(0): Clear all remaining mounting points.
 * NOTE: This function also sets `v_mount' to `VFS_MOUNT_ILLEGAL'. */
PUBLIC NOBLOCK void
NOTHROW(KCALL vfs_clearmounts)(struct vfs *__restrict self) {
	unsigned int i;
	REF struct path *mounting_points, *next;
	assertf(self->v_fscount == 0,
	        "This function must only be called once `v_fscount' hits ZERO(0)");
	mounting_points = ATOMIC_XCH(self->v_mount, VFS_MOUNT_ILLEGAL);
	assertf(mounting_points != VFS_MOUNT_ILLEGAL,
	        "vfs_clearmounts() called more than once");
	/* (lazily) get rid of all mounting points.
	 * Before, each mounting point was a reference loop:
	 *   PATH -> PARENT... -> VFS -> v_mount -> PATH
	 * Here, we break that cycle between `VFS' and `v_mount',
	 * meaning that any remaining mounting points will go away
	 * as soon as their associated paths stop being used. */
	while (mounting_points) {
		assert(mounting_points->p_mount);
		next = mounting_points->p_mount->mp_vfsmount.ln_next;
		LLIST_REMOVE(mounting_points, p_mount->mp_vfsmount);
		mounting_points->p_mount->mp_vfsmount.ln_pself = NULL;
		decref(mounting_points);
		mounting_points = next;
	}
	/* Clear all of the DOS drive bindings. */
	for (i = 0; i < VFS_DRIVECOUNT; ++i) {
		REF struct path *path;
		path = ATOMIC_XCH(self->v_drives[i], VFS_MOUNT_ILLEGAL);
		assert(path != VFS_MOUNT_ILLEGAL);
		if likely(!path)
			continue;
		assert(path->p_isdrive != 0);
		ATOMIC_FETCHDEC(path->p_isdrive);
		decref(path);
	}
	/* Clear all recently used paths. */
	path_recent_clear(self);
}

#if defined(NDEBUG) || 1
#define vfs_assert_recent_integrity(self) (void)0
#else /* NDEBUG */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vfs_assert_recent_integrity)(struct vfs *__restrict self) {
	size_t i;
	struct path *iter, **piter;
	assert((self->v_recent_list != NULL) == (self->v_recent_size != 0));
	assert((self->v_recent_list != NULL) == (self->v_recent_back != NULL));
	if (!self->v_recent_size)
		return;
	for (piter = &self->v_recent_list, i = 0;
	     (iter = *piter) != NULL;
	     piter = &iter->p_recent.ln_next, ++i) {
		assert(i < self->v_recent_size);
		assert(piter == iter->p_recent.ln_pself);
	}
	assert(i == self->v_recent_size);
}
#endif /* !NDEBUG */

/* Indicate that `self' has been used recently, allowing the path to be cached
 * such that it will remain allocated for a while, even when not referenced elsewhere.
 * NOTE: When `self->p_vfs->v_fscount' is ZERO(0) upon entry, or drops to ZERO(0) before
 *       returning, `self' will not be cached as recently used, and the call
 *       behaves as a no-op.
 * NOTE: Always re-returns `self' */
FUNDEF NOBLOCK ATTR_RETNONNULL NONNULL((1)) struct path *
NOTHROW(KCALL path_recent)(struct path *__restrict self) {
	struct vfs *v = self->p_vfs;
	if unlikely(v == self)
		goto done; /* No need to cache the VFS root itself... */
	if (self->p_recent.ln_pself != NULL)
		goto done;
	if (sync_trywrite(&v->v_recent_lock)) {
		COMPILER_READ_BARRIER();
		vfs_assert_recent_integrity(v);
		if (self->p_recent.ln_pself == NULL) {
			incref(self);
			if (v->v_recent_size < v->v_recent_limit) {
				assert((v->v_recent_list != NULL) ==
				       (v->v_recent_back != NULL));
				LLIST_INSERT(v->v_recent_list, self, p_recent);
				if (!v->v_recent_back) {
					assert(!v->v_recent_size);
					v->v_recent_back = self;
				}
				++v->v_recent_size;
			} else {
				struct path *oldest_path;
				/* Pop nodes from the back. */
				oldest_path = v->v_recent_back;
				assert(oldest_path != NULL);
				if unlikely(v->v_recent_back == v->v_recent_list) {
					assert(v->v_recent_limit == 1);
					v->v_recent_list        = self;
					v->v_recent_back        = self;
					self->p_recent.ln_pself = &v->v_recent_list;
					self->p_recent.ln_next  = NULL;
				} else {
					struct path *prev;
					assert(oldest_path->p_recent.ln_pself != &v->v_recent_list);
					prev = COMPILER_CONTAINER_OF(oldest_path->p_recent.ln_pself,
					                             struct path, p_recent.ln_next);
					v->v_recent_back = prev;
					assert(prev->p_recent.ln_next == oldest_path);
					prev->p_recent.ln_next = NULL;
					LLIST_INSERT(v->v_recent_list, self, p_recent);
				}
				oldest_path->p_recent.ln_pself = NULL;
#ifndef NDEBUG
				memset(&oldest_path->p_recent.ln_next, 0xcc,
				       sizeof(oldest_path->p_recent.ln_next));
#endif /* !NDEBUG */
				vfs_assert_recent_integrity(v);
				sync_endwrite(&v->v_recent_lock);
				decref(oldest_path);
				goto done;
			}
		} else {
			assertf(getrefcnt(self) >= 2,
			        "+1: Reference held by the caller\n"
			        "+1: Reference stored in the recent cache");
			/* Bring this path back to the front. */
			if unlikely(self == v->v_recent_back) {
				/* Handle the special case where the path
				 * was at the back of the recent-cache. */
				struct path *prev;
				assert(self->p_recent.ln_next == NULL);
				assert((self == v->v_recent_list) ==
				       (self->p_recent.ln_pself == &v->v_recent_list));
				if unlikely(self == v->v_recent_list)
					goto done_bring_to_front;
				/* Make the predecessor the last element.
				 * NOTE: The next-link of the predecessor will be
				 *       cleared by the call to `LLIST_REMOVE()'! */
				assert(self->p_recent.ln_pself != &v->v_recent_list);
				prev = COMPILER_CONTAINER_OF(self->p_recent.ln_pself,
				                             struct path, p_recent.ln_next);
				assert(prev != self);
				v->v_recent_back = prev;
			}
			LLIST_REMOVE(self, p_recent);
			LLIST_INSERT(v->v_recent_list, self, p_recent);
		}
done_bring_to_front:
		vfs_assert_recent_integrity(v);
		sync_endwrite(&v->v_recent_lock);
	}
done:
	return self;
}

/* Clear the cache of recently used paths. */
PUBLIC NOBLOCK void
NOTHROW(KCALL path_recent_clear)(struct vfs *__restrict v) {
	for (;;) {
		REF struct path *p;
		if (!sync_trywrite(&v->v_recent_lock))
			break;
		vfs_assert_recent_integrity(v);
		p = v->v_recent_list;
		if (!p) {
			assert(!v->v_recent_back);
			assert(!v->v_recent_size);
			sync_endwrite(&v->v_recent_lock);
			break;
		}
		/* Remove the path from the recent-path cache. */
		v->v_recent_list = p->p_recent.ln_next;
		if (!v->v_recent_list) {
			assert(v->v_recent_back == p);
			v->v_recent_back = NULL;
		} else {
			assert(v->v_recent_back != p);
			v->v_recent_list->p_recent.ln_pself = &v->v_recent_list;
		}
		assert(v->v_recent_size);
		--v->v_recent_size;
		assert((v->v_recent_size != 0) == (v->v_recent_list != NULL));
		assert((v->v_recent_size != 0) == (v->v_recent_back != NULL));
		p->p_recent.ln_pself = NULL;
#ifndef NDEBUG
		memset(&p->p_recent.ln_next, 0xcc,
		       sizeof(p->p_recent.ln_next));
#endif /* !NDEBUG */
		vfs_assert_recent_integrity(v);
		sync_endwrite(&v->v_recent_lock);
		decref(p);
	}
}

PRIVATE NONNULL((1)) void
NOTHROW(KCALL path_rehash_nx)(struct path *__restrict self) {
	REF struct path **new_map;
	REF struct path *iter, *next;
	size_t i, new_mask;
	assert(sync_writing(self));
	new_mask = (self->p_cldmask << 1) | 1;
	/* Allocate the new directory map. */
	/*printk("path_rehash_nx(%p)\n",self);*/
	new_map = (REF struct path **)kmalloc_nx((new_mask + 1) *
	                                         sizeof(REF struct path *),
	                                         FS_GFP | GFP_CALLOC);
	if unlikely(!new_map)
		return; /* Ignore failure to allocate a larger map. */
	/* Rehash all the entries. */
	for (i = 0; i <= self->p_cldmask; ++i) {
		iter = self->p_cldlist[i];
		while (iter) {
			struct path **pentry;
			next = iter->p_dirnext.ln_next;
			/* Insert the entry into the new map. */
			pentry = &new_map[iter->p_dirent->de_hash & new_mask];
			LLIST_INSERT(*pentry, iter, p_dirnext);
			iter = next;
		}
	}
	/* Free the old map and setup the new mask. */
	kfree(self->p_cldlist);
	self->p_cldlist = new_map;
	self->p_cldmask = new_mask;
}

INTERN NOBLOCK void
NOTHROW(KCALL path_rehash_smaller_nx)(struct path *__restrict self) {
	REF struct path **new_map;
	REF struct path *iter, *next;
	size_t i, new_mask;
	assert(sync_writing(self));
	new_mask = (self->p_cldmask >> 1);
	/* Allocate the new directory map. */
	new_map = (REF struct path **)kmalloc_nx((new_mask + 1) *
	                                         sizeof(REF struct path *),
	                                         FS_GFP | GFP_ATOMIC | GFP_CALLOC);
	if unlikely(!new_map)
		return; /* Ignore failure to allocate a larger map. */
	/* Rehash all the entries. */
	for (i = 0; i <= self->p_cldmask; ++i) {
		iter = self->p_cldlist[i];
		while (iter) {
			struct path **pentry;
			next = iter->p_dirnext.ln_next;
			/* Insert the entry into the new map. */
			pentry = &new_map[iter->p_dirent->de_hash & new_mask];
			LLIST_INSERT(*pentry, iter, p_dirnext);
			iter = next;
		}
	}
	/* Free the old map and setup the new mask. */
	kfree(self->p_cldlist);
	self->p_cldlist = new_map;
	self->p_cldmask = new_mask;
}



/* Create or lookup the path or a given `child_dir' within `self'
 * NOTE: This function is meant to be used to instantiate paths that could not
 *       be found before (aka.: those for which `path_(case)child()' returned false) */
PUBLIC ATTR_RETNONNULL WUNUSED REF struct path *KCALL
path_newchild(struct path *__restrict self,
              struct directory_node *__restrict child_dir,
              struct directory_entry *__restrict child_entry)
		THROWS(E_BADALLOC) {
	REF struct path *result;
	result = path_alloc(FS_GFP);
	TRY {
		/* Now to cache the new child (but make sure not to create duplicates!) */
		sync_write(self);
		if (self->p_cldlist) {
			struct path *new_result;
search_existing_list:
			new_result = self->p_cldlist[child_entry->de_hash & self->p_cldmask];
			for (; new_result; new_result = new_result->p_dirnext.ln_next) {
				if (new_result->p_dirent == child_entry)
					goto is_a_duplicate;
				if (new_result->p_dirent->de_hash != child_entry->de_hash)
					continue;
				if (new_result->p_dirent->de_namelen != child_entry->de_namelen)
					continue;
				if (memcmp(new_result->p_dirent->de_name,
				           child_entry->de_name,
				           child_entry->de_namelen * sizeof(char)) != 0)
					continue;
is_a_duplicate:
				incref(new_result);
				sync_endwrite(self);
				path_free(result);
				return new_result;
			}
		} else {
			/* Must allocate the initial hash map. */
			self->p_cldlist = (LLIST(struct path) *)kmalloc_nx(sizeof(LLIST(struct path)) *
			                                                   (PATH_DEFAULT_MASK + 1),
			                                                   FS_GFP | GFP_CALLOC | GFP_ATOMIC);
			if likely(!self->p_cldlist) {
				self->p_cldmask = PATH_DEFAULT_MASK;
			} else {
				LLIST(struct path) * new_map;
				sync_endwrite(self);
				new_map = (LLIST(struct path) *)kmalloc(sizeof(LLIST(struct path)) *
				                                        (PATH_DEFAULT_MASK + 1),
				                                        FS_GFP | GFP_CALLOC);
				TRY {
					sync_write(self);
				} EXCEPT {
					kfree(new_map);
					RETHROW();
				}
				if unlikely(self->p_cldlist) {
					kfree(new_map);
					/* Must search the list that has appeared in the mean time. */
					goto search_existing_list;
				}
				/* Save the new list as current. */
				self->p_cldmask = PATH_DEFAULT_MASK;
				self->p_cldlist = new_map;
			}
		}
	} EXCEPT {
		path_free(result);
		RETHROW();
	}
	/* Initialize the new path. */
	result->p_refcnt = 1;
	result->p_vfs    = self->p_vfs;
	result->p_parent = incref(self);
	atomic_rwlock_init(&result->p_lock);
	result->p_inode           = (REF struct directory_node *)incref(child_dir);
	result->p_mount           = NULL;
	result->p_dirent          = incref(child_entry);
	result->p_cldmask         = 0;
	result->p_cldsize         = 0;
	result->p_cldlist         = NULL;
	result->p_delpend         = NULL;
	result->p_recent.ln_pself = NULL;

	/* Add the resulting entry to the new hash-map. */
	{
		struct path **presult = &self->p_cldlist[child_entry->de_hash & self->p_cldmask];
		LLIST_INSERT(*presult, result, p_dirnext);
	}
	++self->p_cldsize;
	if (self->p_cldsize >= (self->p_cldmask / 3) * 2)
		path_rehash_nx(self);
	sync_endwrite(self);
	return result;
}


#ifndef __INTELLISENSE__
DECL_END

#undef ALWAYS_GET_PARENT_INODE
#undef PATH_GETCASECHILD
#include "vfs-getchild-impl.c.inl"
#define ALWAYS_GET_PARENT_INODE 1
#include "vfs-getchild-impl.c.inl"

#define PATH_GETCASECHILD 1
#include "vfs-getchild-impl.c.inl"
#define PATH_GETCASECHILD 1
#define ALWAYS_GET_PARENT_INODE 1
#include "vfs-getchild-impl.c.inl"

DECL_BEGIN
#endif /* !__INTELLISENSE__ */




/* Allocate a new VFS object */
PUBLIC ATTR_RETNONNULL WUNUSED ATTR_MALLOC
REF struct vfs *(KCALL vfs_alloc)(void) THROWS(E_BADALLOC) {
	REF struct vfs *result;
	result = (REF struct vfs *)kmalloc(sizeof(struct vfs),
	                                   FS_GFP | GFP_CALLOC);
	result->p_refcnt = 1;
	result->p_vfs    = result;
	atomic_rwlock_cinit(&result->p_lock);
	result->v_fscount = 1;
	atomic_rwlock_cinit(&result->v_mount_lock);
	atomic_rwlock_cinit(&result->v_recent_lock);
	atomic_rwlock_cinit(&result->v_drives_lock);
	result->v_recent_limit = VFS_DEFAULT_RECENT_LIMIT;
	return result;
}


/* Clone the given VFS */
PUBLIC ATTR_RETNONNULL WUNUSED ATTR_MALLOC REF struct vfs *KCALL
vfs_clone(struct vfs *__restrict self) THROWS(E_BADALLOC) {
	(void)self;
	COMPILER_IMPURE();
	THROW(E_NOT_IMPLEMENTED_TODO);
}



/* Allocate a new FS object. */
PUBLIC ATTR_RETNONNULL WUNUSED ATTR_MALLOC
REF struct fs *(KCALL fs_alloc)(void) THROWS(E_BADALLOC) {
	struct heapptr resptr;
	REF struct fs *result;
	REF struct vfs *result_vfs;
	resptr = heap_alloc(FS_HEAP, sizeof(struct fs),
	                    FS_GFP | GFP_CALLOC);
	TRY {
		result_vfs = vfs_alloc();
	} EXCEPT {
		heap_free(FS_HEAP,
		          resptr.hp_ptr,
		          resptr.hp_siz,
		          FS_GFP | GFP_CALLOC);
		RETHROW();
	}
	result = (REF struct fs *)resptr.hp_ptr;
	result->f_refcnt   = 1;
	result->f_heapsize = resptr.hp_siz;
	result->f_vfs      = result_vfs;
	atomic_rwlock_cinit(&result->f_pathlock);
	result->f_root = incref(result_vfs);
	result->f_cwd  = incref(result_vfs);
#if CONFIG_FS_UMASK_DEFAULT != 0
	result->f_umask = CONFIG_FS_UMASK_DEFAULT;
#endif /* CONFIG_FS_UMASK_DEFAULT != 0 */
	result->f_lnkmax = SYMLOOP_MAX;
	result->f_atmask = FS_MODE_FALWAYS1MASK | (~FS_MODE_FALWAYS0MASK);
#if FS_MODE_FALWAYS1FLAG != 0
	result->f_atflag = FS_MODE_FALWAYS1FLAG;
#endif /* FS_MODE_FALWAYS1FLAG != 0 */
	return result;
}

PRIVATE WUNUSED NONNULL((1, 2, 3)) struct path *
NOTHROW(KCALL vfs_findpath_nolock)(struct vfs *__restrict new_vfs,
                                   struct vfs *old_vfs,
                                   struct path *old_path) {
	struct path *parent;
	assert(new_vfs);
	assert(old_vfs);
	assert(old_path);
	assert(new_vfs != old_vfs);
	if (old_path == old_vfs)
		return new_vfs;
	parent = vfs_findpath_nolock(new_vfs, old_vfs, old_path->p_parent);
	if likely(parent) {
		struct path *result;
		struct directory_entry *dent;
		dent = old_path->p_dirent;
		result = parent->p_cldlist[dent->de_hash & parent->p_cldmask];
		for (; result; result = result->p_dirnext.ln_next) {
			if (result->p_dirent != dent)
				continue;
			return result; /* Found it! */
		}
	}
	return NULL;
}

/* Clone the given FS
 * @param: clone_vfs: When true, clone the VFS, else share the same one. */
PUBLIC ATTR_RETNONNULL WUNUSED ATTR_MALLOC REF struct fs *KCALL
fs_clone(struct fs *__restrict self, bool clone_vfs) THROWS(E_BADALLOC) {
	struct heapptr resptr;
	REF struct fs *result;
	REF struct vfs *result_vfs;
	resptr = heap_alloc(FS_HEAP, sizeof(struct fs),
	                    FS_GFP | GFP_CALLOC);
	if (clone_vfs) {
		unsigned int i;
		struct path *newpath;
again_clone:
		TRY {
			result_vfs = vfs_clone(self->f_vfs);
			TRY {
				sync_read(&self->f_pathlock);
			} EXCEPT {
				decref(result_vfs);
				RETHROW();
			}
		} EXCEPT {
			heap_free(FS_HEAP,
			          resptr.hp_ptr,
			          resptr.hp_siz,
			          FS_GFP | GFP_CALLOC);
			RETHROW();
		}
		result = (REF struct fs *)resptr.hp_ptr;
		newpath = vfs_findpath_nolock(result_vfs, self->f_vfs, self->f_root);
		if unlikely(!newpath) {
			sync_endread(&self->f_pathlock);
			decref(result_vfs);
			goto again_clone;
		}
		result->f_root = incref(newpath);
		newpath = vfs_findpath_nolock(result_vfs, self->f_vfs, self->f_cwd);
		if unlikely(!newpath) {
			sync_endread(&self->f_pathlock);
			decref(result->f_root);
			decref(result_vfs);
			goto again_clone;
		}
		result->f_cwd = incref(newpath);
		for (i = 0; i < VFS_DRIVECOUNT; ++i) {
			struct path *o = self->f_dcwd[i];
			if (!o) {
				result->f_dcwd[i] = NULL;
				continue;
			}
			newpath = vfs_findpath_nolock(result_vfs, self->f_vfs, o);
			if unlikely(!newpath) {
				sync_endread(&self->f_pathlock);
				while (i--)
					xdecref(result->f_dcwd[i]);
				decref(result->f_cwd);
				decref(result->f_root);
				decref(result_vfs);
				goto again_clone;
			}
			result->f_dcwd[i] = incref(newpath);
		}
		sync_endread(&self->f_pathlock);
	} else {
		unsigned int i;
		result = (REF struct fs *)resptr.hp_ptr;
		TRY {
			sync_read(&self->f_pathlock);
		} EXCEPT {
			heap_free(FS_HEAP,
			          resptr.hp_ptr,
			          resptr.hp_siz,
			          FS_GFP | GFP_CALLOC);
			RETHROW();
		}
		result->f_root = incref(self->f_root);
		result->f_cwd  = incref(self->f_cwd);
		for (i = 0; i < VFS_DRIVECOUNT; ++i) {
			result->f_dcwd[i] = xincref(self->f_dcwd[i]);
		}
		sync_endread(&self->f_pathlock);
		result_vfs = (REF struct vfs *)incref(self->f_vfs);
		vfs_inc_fscount(result_vfs);
	}
	result->f_umask  = ATOMIC_READ(self->f_umask);
	result->f_lnkmax = ATOMIC_READ(self->f_lnkmax);
	result->f_fsuid  = ATOMIC_READ(self->f_fsuid);
	result->f_fsgid  = ATOMIC_READ(self->f_fsgid);
	result->f_mode   = ATOMIC_READ(self->f_mode);
	result->f_refcnt   = 1;
	result->f_heapsize = resptr.hp_siz;
	result->f_vfs      = result_vfs; /* Inherit reference. */
	atomic_rwlock_cinit(&result->f_pathlock);
	return result;
}



PUBLIC NOBLOCK void
NOTHROW(KCALL fs_destroy)(struct fs *__restrict self) {
	unsigned int i;
	decref(self->f_root);
	decref(self->f_cwd);
	for (i = 0; i < VFS_DRIVECOUNT; ++i)
		xdecref(self->f_dcwd[i]);
	vfs_dec_fscount(self->f_vfs);
	decref(self->f_vfs);
	heap_free(FS_HEAP,
	          self,
	          self->f_heapsize,
	          FS_GFP);
}


/* [1..1] Per-thread filesystem information.
 * NOTE: Initialized to NULL. - Must be initialized before the task is started. */
PUBLIC ATTR_PERTASK REF struct fs *this_fs = NULL;

DEFINE_PERTASK_FINI(fini_this_fs);
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fini_this_fs)(struct task *__restrict self) {
	xdecref(FORTASK(self, this_fs));
}

DEFINE_PERTASK_CLONE(clone_this_fs);
INTERN NONNULL((1)) void KCALL
clone_this_fs(struct task *__restrict new_thread, uintptr_t flags) {
	struct fs *f;
	f = THIS_FS;
	if (flags & CLONE_FS) {
		incref(f); /* Re-use the same fs. */
	} else {
		/* Clone the old fs. */
		f = fs_clone(f, (flags & CLONE_NEWNS) != 0);
	}
	assert(!FORTASK(new_thread, this_fs));
	FORTASK(new_thread, this_fs) = f; /* Inherit reference */
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_FS_VFS_C */
