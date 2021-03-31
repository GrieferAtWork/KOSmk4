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
#ifndef GUARD_KERNEL_SRC_MEMORY_DATABLOCK_HANDLE_C
#define GUARD_KERNEL_SRC_MEMORY_DATABLOCK_HANDLE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/fifo.h>
#include <fs/node.h>
#include <fs/special-node.h>
#include <fs/vfs.h>
#include <kernel/aio.h>
#include <kernel/except.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/mman/mpartmeta.h>
#include <kernel/user.h>
#include <kernel/vm.h>
#include <sched/cred.h>

#include <hybrid/atomic.h>

#include <kos/except/reason/fs.h>
#include <kos/except/reason/inval.h>
#include <kos/hop/datablock.h>
#include <sys/stat.h>

#include <assert.h>
#include <errno.h>
#include <string.h>

DECL_BEGIN

/* DATABLOCK HANDLE OPERATIONS */
DEFINE_HANDLE_REFCNT_FUNCTIONS(datablock, struct vm_datablock);

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_datablock_read(struct vm_datablock *__restrict self,
                      USER CHECKED void *dst,
                      size_t num_bytes, iomode_t mode) THROWS(...) {
	size_t result;
	if unlikely(!self->db_type->mo_stream_read) {
		THROW(E_FSERROR_UNSUPPORTED_OPERATION,
		      E_FILESYSTEM_OPERATION_READ);
	}
	result = (*self->db_type->mo_stream_read)(self, dst, num_bytes, mode);
	return result;
}

INTERN NONNULL((1)) size_t KCALL
handle_datablock_write(struct vm_datablock *__restrict self,
                       USER CHECKED void const *src,
                       size_t num_bytes, iomode_t mode) THROWS(...) {
	size_t result;
	if unlikely(!self->db_type->mo_stream_write) {
		THROW(E_FSERROR_UNSUPPORTED_OPERATION,
		      E_FILESYSTEM_OPERATION_WRITE);
	}
	result = (*self->db_type->mo_stream_write)(self, src, num_bytes, mode);
	return result;
}

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_datablock_pread(struct vm_datablock *__restrict self,
                       USER CHECKED void *dst,
                       size_t num_bytes, pos_t addr, iomode_t mode) {
	if (vm_datablock_isinode(self)) {
		/* TODO: Support for `IO_NONBLOCK' */
		(void)mode;
		return inode_read((struct inode *)self, dst, num_bytes, addr);
	}
	return 0;
}

INTERN NONNULL((1)) size_t KCALL
handle_datablock_pwrite(struct vm_datablock *__restrict self,
                        USER CHECKED void const *src,
                        size_t num_bytes, pos_t addr, iomode_t mode) {
	if (vm_datablock_isinode(self)) {
		/* TODO: Support for `IO_NONBLOCK' */
		(void)mode;
		inode_write((struct inode *)self, src, num_bytes, addr);
		return num_bytes;
	}
	return 0;
}

INTERN WUNUSED NONNULL((1)) size_t KCALL
handle_datablock_preadv(struct vm_datablock *__restrict self,
                        struct iov_buffer *__restrict dst, size_t num_bytes,
                        pos_t addr, iomode_t mode) {
	if (vm_datablock_isinode(self)) {
		/* TODO: Support for `IO_NONBLOCK' */
		(void)mode;
		return inode_readv((struct inode *)self, dst, num_bytes, addr);
	}
	return 0;
}

INTERN NONNULL((1)) size_t KCALL
handle_datablock_pwritev(struct vm_datablock *__restrict self,
                         struct iov_buffer *__restrict src, size_t num_bytes,
                         pos_t addr, iomode_t mode) {
	if (vm_datablock_isinode(self)) {
		/* TODO: Support for `IO_NONBLOCK' */
		(void)mode;
		inode_writev((struct inode *)self, src, num_bytes, addr);
		return num_bytes;
	}
	return 0;
}



INTERN NONNULL((1)) void KCALL
handle_datablock_truncate(struct vm_datablock *__restrict self,
                          pos_t new_size) {
	if (vm_datablock_isinode(self)) {
		inode_truncate((struct inode *)self, new_size);
	} else {
		/* TODO: Anonymize the parts of this data block. */
	}
}

/* TODO */
INTERN NONNULL((1)) pos_t KCALL
handle_datablock_allocate(struct vm_datablock *__restrict self,
                          fallocate_mode_t mode,
                          pos_t start, pos_t length);

INTERN NONNULL((1)) void KCALL
handle_datablock_sync(struct vm_datablock *__restrict self) {
	if (vm_datablock_isinode(self))
		inode_sync((struct inode *)self);
	else {
		vm_datablock_sync(self);
	}
}

INTERN NONNULL((1)) void KCALL
handle_datablock_datasync(struct vm_datablock *__restrict self) {
	vm_datablock_sync(self);
}

INTERN NONNULL((1)) void KCALL
handle_datablock_pollconnect(struct vm_datablock *__restrict self,
                             poll_mode_t what) {
	assert((self->db_type->dt_handle_pollconnect != NULL) ==
	       (self->db_type->dt_handle_polltest != NULL));
	if (self->db_type->dt_handle_pollconnect) {
		(*self->db_type->dt_handle_pollconnect)(self, what);
	} else if (what & (POLLOUTMASK | POLLINMASK)) {
		if (vm_datablock_isinode(self))
			rwlock_pollconnect(__inode_lock((struct inode *)self));
	}
}

INTERN NONNULL((1)) poll_mode_t KCALL
handle_datablock_polltest(struct vm_datablock *__restrict self,
                          poll_mode_t what) {
	assert((self->db_type->dt_handle_pollconnect != NULL) ==
	       (self->db_type->dt_handle_polltest != NULL));
	if (self->db_type->dt_handle_polltest)
		return (*self->db_type->dt_handle_polltest)(self, what);
	if (what & POLLOUTMASK) {
		if (vm_datablock_isinode(self)) {
			if (rwlock_canwrite(__inode_lock((struct inode *)self)))
				return POLLOUTMASK | POLLINMASK;
		} else {
			return POLLOUTMASK | POLLINMASK;
		}
	} else if (what & POLLINMASK) {
		if (vm_datablock_isinode(self)) {
			if (rwlock_canread(__inode_lock((struct inode *)self)))
				return POLLINMASK;
		} else {
			return POLLINMASK;
		}
	}
	return 0;
}


INTERN NONNULL((1)) syscall_slong_t KCALL
handle_datablock_ioctl(struct vm_datablock *__restrict self,
                       syscall_ulong_t cmd,
                       USER UNCHECKED void *arg,
                       iomode_t mode) {
	if (vm_datablock_isinode(self))
		return inode_ioctl((struct inode *)self, cmd, arg, mode);
	THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
	      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
	      cmd);
}

INTERN NONNULL((1)) syscall_slong_t KCALL
handle_datablock_hop(struct vm_datablock *__restrict self,
                     syscall_ulong_t cmd,
                     USER UNCHECKED void *arg,
                     iomode_t mode) {
	switch (cmd) {

	case HOP_DATABLOCK_SYNCALL: {
		datapage_t count;
		count = vm_datablock_sync(self);
		if (arg) {
			validate_writable(arg, sizeof(u64));
			*(u64 *)arg = (u64)count;
		}
	}	break;

	case HOP_DATABLOCK_ANONYMIZE:
		/* Need write permissions. */
		if ((mode & IO_ACCMODE) == IO_RDONLY)
			THROW(E_INVALID_HANDLE_OPERATION, 0, E_INVALID_HANDLE_OPERATION_TRUNC, mode);
		validate_writable(arg, sizeof(int));
		*(int *)arg = vm_datablock_anonymize(self) ? 1 : 0;
		break;

	case HOP_DATABLOCK_OPEN_FUTEX:
	case HOP_DATABLOCK_OPEN_FUTEX_EXISTING: {
		size_t struct_size;
		struct hop_datablock_open_futex *data;
		REF struct vm_futex *ftx;
		struct handle hnd;
		/* [struct hop_datablock_open_futex *result] Return an existing a futex for the given address. */
		validate_readwrite(arg, sizeof(struct hop_datablock_open_futex));
		data        = (struct hop_datablock_open_futex *)arg;
		struct_size = ATOMIC_READ(data->dof_struct_size);
		if (struct_size != sizeof(struct hop_datablock_open_futex))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_datablock_open_futex), struct_size);
		if (cmd == HOP_DATABLOCK_OPEN_FUTEX_EXISTING) {
			ftx = mfile_lookupfutex(self, (pos_t)data->dof_address);
			if (!ftx)
				return -ENOENT;
		} else {
			ftx = mfile_createfutex(self, (pos_t)data->dof_address);
		}
		FINALLY_DECREF_UNLIKELY(ftx);
		hnd.h_type = HANDLE_TYPE_FUTEX;
		hnd.h_mode = mode;
		hnd.h_data = ftx;
		return handle_installhop(&data->dof_openfd, hnd);
	}	break;

	case HOP_INODE_OPEN_SUPERBLOCK: {
		struct handle result_handle;
		if (!vm_datablock_isinode(self)) {
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_DATABLOCK,
			      0,
			      HANDLE_TYPEKIND_DATABLOCK_INODE,
			      0);
		}
		result_handle.h_mode = mode;
		result_handle.h_type = HANDLE_TYPE_DATABLOCK;
		result_handle.h_data = ((struct inode *)self)->i_super;
		inode_access_accmode((struct inode *)result_handle.h_data, mode);
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, result_handle);
	}	break;

	case HOP_INODE_CHMOD: {
		size_t struct_size;
		mode_t mask, flag;
		struct hop_inode_chmod *data;
		struct inode *me;
		if (!vm_datablock_isinode(self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_DATABLOCK,
			      0,
			      HANDLE_TYPEKIND_DATABLOCK_INODE,
			      0);
		validate_readwrite(arg, sizeof(struct hop_inode_chmod));
		data        = (struct hop_inode_chmod *)arg;
		struct_size = ATOMIC_READ(data->icm_struct_size);
		if (struct_size != sizeof(struct hop_inode_chmod))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_inode_chmod), struct_size);
		me   = (struct inode *)self;
		mask = ATOMIC_READ(data->icm_perm_mask);
		flag = ATOMIC_READ(data->icm_perm_flag);
		data->icm_perm_old = inode_chmod(me, mask, flag);
	}	break;

	case HOP_INODE_CHOWN: {
		size_t struct_size;
		struct hop_inode_chown *data;
		uid_t old_owner;
		gid_t old_group;
		if (!vm_datablock_isinode(self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_DATABLOCK,
			      0,
			      HANDLE_TYPEKIND_DATABLOCK_INODE,
			      0);
		validate_readwrite(arg, sizeof(struct hop_inode_chown));
		data        = (struct hop_inode_chown *)arg;
		struct_size = ATOMIC_READ(data->ico_struct_size);
		if (struct_size != sizeof(struct hop_inode_chown))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_inode_chown), struct_size);
		inode_chown((struct inode *)self,
		            (uid_t)ATOMIC_READ(data->ico_newowner),
		            (gid_t)ATOMIC_READ(data->ico_newgroup),
		            &old_owner,
		            &old_group);
		COMPILER_WRITE_BARRIER();
		data->ico_oldowner = (u32)old_owner;
		data->ico_oldgroup = (u32)old_group;
	}	break;

	case HOP_DIRECTORY_OPENNODE: {
		size_t struct_size;
		struct hop_directory_opennode *data;
		USER UNCHECKED char const *name;
		u16 namelen, openflags;
		uintptr_t hash;
		REF struct inode *child_node;
		REF struct directory_entry *child_entry;
		struct handle temp;
		struct directory_node *me;
		if (!vm_datablock_isinode(self) || !INODE_ISDIR((struct inode *)self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_DATABLOCK,
			      0,
			      HANDLE_TYPEKIND_DATABLOCK_DIRECTORY,
			      0);
		me = (struct directory_node *)self;
		validate_readwrite(arg, sizeof(struct hop_directory_opennode));
		data        = (struct hop_directory_opennode *)arg;
		struct_size = ATOMIC_READ(data->don_struct_size);
		if (struct_size != sizeof(struct hop_directory_opennode))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_directory_opennode), struct_size);
		COMPILER_READ_BARRIER();
		name      = data->don_name;
		namelen   = data->don_len;
		openflags = data->don_flags;
		COMPILER_READ_BARRIER();
		validate_readable(name, namelen);
		VALIDATE_FLAGSET(openflags,
		                 HOP_DIRECTORY_OPENNODE_FNOCASE,
		                 E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_OPENNODE_FLAGS);
		hash = directory_entry_hash(name, namelen);
		if (!capable(CAP_DAC_READ_SEARCH)) {
			inode_loadattr(me);
			inode_access(me, R_OK | X_OK);
		}
		child_node = openflags & HOP_DIRECTORY_OPENNODE_FNOCASE
		             ? directory_getcasenode(me, name, namelen, hash, &child_entry)
		             : directory_getnode(me, name, namelen, hash, &child_entry);
		if unlikely(!child_node)
			THROW(E_FSERROR_FILE_NOT_FOUND);
		{
			struct hop_openfd *fd;
			FINALLY_DECREF(child_entry);
			FINALLY_DECREF(child_node);
			/* Install handles for objects that the caller wants to open */
			fd = ATOMIC_READ(data->don_node);
			if (fd) {
				temp.h_type = HANDLE_TYPE_DATABLOCK;
				temp.h_mode = mode;
				temp.h_data = child_node;
				handle_installhop(fd, temp);
			}
			fd = ATOMIC_READ(data->don_dent);
			if (fd) {
				temp.h_type = HANDLE_TYPE_DIRECTORYENTRY;
				temp.h_mode = mode;
				temp.h_data = child_entry;
				handle_installhop(fd, temp);
			}
		}
	}	break;

	case HOP_DIRECTORY_CREATFILE: {
		size_t struct_size;
		struct hop_directory_creatfile *data;
		USER UNCHECKED char const *name;
		u16 namelen;
		oflag_t oflags;
		REF struct inode *child_node;
		REF struct directory_entry *child_entry;
		struct handle temp;
		mode_t newfile_mode;
		uid_t newfile_owner;
		gid_t newfile_group;
		bool was_newly_created;
		if (!vm_datablock_isinode(self) || !INODE_ISDIR((struct inode *)self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_DATABLOCK,
			      0,
			      HANDLE_TYPEKIND_DATABLOCK_DIRECTORY,
			      0);
		validate_readwrite(arg, sizeof(struct hop_directory_creatfile));
		data        = (struct hop_directory_creatfile *)arg;
		struct_size = ATOMIC_READ(data->dcf_struct_size);
		if (struct_size != sizeof(struct hop_directory_creatfile))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_directory_creatfile), struct_size);
		COMPILER_READ_BARRIER();
		name          = data->dcf_name;
		namelen       = data->dcf_len;
		oflags        = (oflag_t)data->dcf_oflags;
		newfile_mode  = (mode_t)data->dcf_mode;
		newfile_owner = (uid_t)data->dcf_owner;
		newfile_group = (gid_t)data->dcf_group;
		COMPILER_READ_BARRIER();
		validate_readable(name, namelen);
		VALIDATE_FLAGSET(oflags,
		                 O_CREAT | O_EXCL | O_DOSPATH,
		                 E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_CREATFILE_OFLAGS);
		VALIDATE_FLAGSET(newfile_mode, 07777,
		                 E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_CREATFILE_MODE);
		if (newfile_owner == (uid_t)-1)
			newfile_owner = fs_getuid(THIS_FS);
		if (newfile_group == (gid_t)-1)
			newfile_group = fs_getgid(THIS_FS);
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		child_node = directory_creatfile((struct directory_node *)self,
		                                 name,
		                                 namelen,
		                                 oflags,
		                                 newfile_owner,
		                                 newfile_group,
		                                 newfile_mode & ~ATOMIC_READ(THIS_FS->f_umask),
		                                 &child_entry,
		                                 &was_newly_created);
		{
			struct hop_openfd *fd;
			FINALLY_DECREF(child_entry);
			FINALLY_DECREF(child_node);
			ATOMIC_WRITE(data->dcf_status, was_newly_created
			                               ? HOP_DIRECTORY_CREATFILE_STATUS_CREATED_NEW
			                               : HOP_DIRECTORY_CREATFILE_STATUS_ALREADY_EXISTED);
			/* Install handles for objects that the caller wants to open */
			fd = ATOMIC_READ(data->dcf_node);
			if (fd) {
				temp.h_type = HANDLE_TYPE_DATABLOCK;
				temp.h_mode = mode;
				temp.h_data = child_node;
				handle_installhop(fd, temp);
			}
			fd = ATOMIC_READ(data->dcf_dent);
			if (fd) {
				temp.h_type = HANDLE_TYPE_DIRECTORYENTRY;
				temp.h_mode = mode;
				temp.h_data = child_entry;
				handle_installhop(fd, temp);
			}
		}
	}	break;

	case HOP_DIRECTORY_REMOVE: {
		STATIC_ASSERT(HOP_DIRECTORY_REMOVE_FLAG_REGULAR == DIRECTORY_REMOVE_FREGULAR);
		STATIC_ASSERT(HOP_DIRECTORY_REMOVE_FLAG_DIRECTORY == DIRECTORY_REMOVE_FDIRECTORY);
		STATIC_ASSERT(HOP_DIRECTORY_REMOVE_FLAG_NOCASE == DIRECTORY_REMOVE_FNOCASE);
		STATIC_ASSERT(HOP_DIRECTORY_REMOVE_STATUS_UNLINK == DIRECTORY_REMOVE_STATUS_UNLINK);
		STATIC_ASSERT(HOP_DIRECTORY_REMOVE_STATUS_RMDIR == DIRECTORY_REMOVE_STATUS_RMDIR);
		STATIC_ASSERT(HOP_DIRECTORY_REMOVE_STATUS_FDELETED == DIRECTORY_REMOVE_STATUS_FDELETED);
		size_t struct_size;
		struct hop_directory_remove *data;
		USER UNCHECKED char const *name;
		u16 namelen;
		uintptr_t hash;
		unsigned int remove_mode;
		unsigned int remove_status;
		REF struct inode *child_node;
		REF struct directory_entry *child_entry;
		struct handle temp;
		if (!vm_datablock_isinode(self) || !INODE_ISDIR((struct inode *)self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_DATABLOCK,
			      0,
			      HANDLE_TYPEKIND_DATABLOCK_DIRECTORY,
			      0);
		validate_readwrite(arg, sizeof(struct hop_directory_remove));
		data        = (struct hop_directory_remove *)arg;
		struct_size = ATOMIC_READ(data->drm_struct_size);
		if (struct_size != sizeof(struct hop_directory_remove))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_directory_remove), struct_size);
		COMPILER_READ_BARRIER();
		name        = data->drm_name;
		namelen     = data->drm_len;
		remove_mode = data->drm_flags;
		COMPILER_READ_BARRIER();
		validate_readable(name, namelen);
		VALIDATE_FLAGSET(remove_mode,
		                 HOP_DIRECTORY_REMOVE_FLAG_REGULAR |
		                 HOP_DIRECTORY_REMOVE_FLAG_DIRECTORY |
		                 HOP_DIRECTORY_REMOVE_FLAG_NOCASE,
		                 E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_REMOVE_FLAGS);
		if (!(remove_mode & (HOP_DIRECTORY_REMOVE_FLAG_REGULAR | HOP_DIRECTORY_REMOVE_FLAG_DIRECTORY))) {
			THROW(E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION,
			      E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_REMOVE_FLAGS,
			      remove_mode,
			      HOP_DIRECTORY_REMOVE_FLAG_REGULAR | HOP_DIRECTORY_REMOVE_FLAG_DIRECTORY,
			      0);
		}
		hash = directory_entry_hash(name, namelen);
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		remove_status = directory_remove((struct directory_node *)self,
		                                 name,
		                                 namelen,
		                                 hash,
		                                 remove_mode,
		                                 &child_node,
		                                 &child_entry,
		                                 NULL,
		                                 NULL);
		{
			struct hop_openfd *fd;
			FINALLY_DECREF(child_entry);
			FINALLY_DECREF(child_node);
			/* Install handles for objects that the caller wants to open */
			ATOMIC_WRITE(data->drm_status, (u16)remove_status);
			fd = ATOMIC_READ(data->drm_node);
			if (fd) {
				temp.h_type = HANDLE_TYPE_DATABLOCK;
				temp.h_mode = mode;
				temp.h_data = child_node;
				handle_installhop(fd, temp);
			}
			fd = ATOMIC_READ(data->drm_dent);
			if (fd) {
				temp.h_type = HANDLE_TYPE_DIRECTORYENTRY;
				temp.h_mode = mode;
				temp.h_data = child_entry;
				handle_installhop(fd, temp);
			}
		}
	}	break;


	case HOP_DIRECTORY_RENAME: {
		STATIC_ASSERT(HOP_DIRECTORY_RENAME_FNORMAL == DIRECTORY_RENAME_FNORMAL);
		STATIC_ASSERT(HOP_DIRECTORY_RENAME_FNOCASE == DIRECTORY_RENAME_FNOCASE);
		size_t struct_size;
		struct hop_directory_rename *data;
		USER UNCHECKED char const *srcname;
		USER UNCHECKED char const *dstname;
		u16 srcnamelen, dstnamelen;
		unsigned int rename_mode, dstdir;
		REF struct inode *srcchild_node;
		REF struct inode *dstchild_node;
		REF struct directory_entry *srcchild_entry;
		REF struct directory_entry *dstchild_entry;
		REF struct directory_node *target_dir;
		struct handle temp;
		if (!vm_datablock_isinode(self) || !INODE_ISDIR((struct inode *)self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_DATABLOCK,
			      0,
			      HANDLE_TYPEKIND_DATABLOCK_DIRECTORY,
			      0);
		validate_readwrite(arg, sizeof(struct hop_directory_rename));
		data        = (struct hop_directory_rename *)arg;
		struct_size = ATOMIC_READ(data->drn_struct_size);
		if (struct_size != sizeof(struct hop_directory_rename))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_directory_rename), struct_size);
		COMPILER_READ_BARRIER();
		srcname     = data->drn_srcname;
		srcnamelen  = data->drn_srclen;
		dstname     = data->drn_dstname;
		dstnamelen  = data->drn_dstlen;
		rename_mode = data->drn_flags;
		dstdir      = (unsigned int)data->drn_dstdir;
		COMPILER_READ_BARRIER();
		validate_readable(srcname, srcnamelen);
		validate_readable(dstname, dstnamelen);
		VALIDATE_FLAGSET(rename_mode,
		                 HOP_DIRECTORY_RENAME_FNORMAL |
		                 HOP_DIRECTORY_RENAME_FNOCASE,
		                 E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_RENAME_FLAGS);
		if (dstdir == (unsigned int)-1) {
			target_dir = (REF struct directory_node *)incref(self);
		} else {
			target_dir = handle_get_directory_node(dstdir);
		}
		{
			FINALLY_DECREF(target_dir);
			cred_require_sysadmin(); /* TODO: More finely grained access! */
			directory_rename((struct directory_node *)self,
			                 srcname,
			                 srcnamelen,
			                 directory_entry_hash(srcname, srcnamelen),
			                 target_dir,
			                 dstname,
			                 dstnamelen,
			                 rename_mode,
			                 &srcchild_entry,
			                 &dstchild_entry,
			                 &srcchild_node,
			                 &dstchild_node,
			                 NULL,
			                 NULL);
		}
		{
			struct hop_openfd *fd;
			FINALLY_DECREF(srcchild_entry);
			FINALLY_DECREF(dstchild_entry);
			FINALLY_DECREF(srcchild_node);
			FINALLY_DECREF(dstchild_node);
			/* Install handles for objects that the caller wants to open */
			if ((fd = ATOMIC_READ(data->drn_srcnode)) != NULL) {
				temp.h_type = HANDLE_TYPE_DATABLOCK;
				temp.h_mode = mode;
				temp.h_data = srcchild_node;
				handle_installhop(fd, temp);
			}
			if ((fd = ATOMIC_READ(data->drn_srcdent)) != NULL) {
				temp.h_type = HANDLE_TYPE_DIRECTORYENTRY;
				temp.h_mode = mode;
				temp.h_data = srcchild_entry;
				handle_installhop(fd, temp);
			}
			if ((fd = ATOMIC_READ(data->drn_dstnode)) != NULL) {
				temp.h_type = HANDLE_TYPE_DATABLOCK;
				temp.h_mode = mode;
				temp.h_data = dstchild_node;
				handle_installhop(fd, temp);
			}
			if ((fd = ATOMIC_READ(data->drn_dstdent)) != NULL) {
				temp.h_type = HANDLE_TYPE_DIRECTORYENTRY;
				temp.h_mode = mode;
				temp.h_data = dstchild_entry;
				handle_installhop(fd, temp);
			}
		}
	}	break;

	case HOP_DIRECTORY_LINK: {
		STATIC_ASSERT(HOP_DIRECTORY_LINK_FNORMAL == DIRECTORY_LINK_FNORMAL);
		STATIC_ASSERT(HOP_DIRECTORY_LINK_FNOCASE == DIRECTORY_LINK_FNOCASE);
		size_t struct_size;
		struct hop_directory_link *data;
		USER UNCHECKED char const *name;
		u16 namelen;
		unsigned int link_mode;
		REF struct inode *link_node;
		REF struct directory_entry *child_entry;
		unsigned int link_nodefd;
		struct handle temp;
		if (!vm_datablock_isinode(self) || !INODE_ISDIR((struct inode *)self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_DATABLOCK,
			      0,
			      HANDLE_TYPEKIND_DATABLOCK_DIRECTORY,
			      0);
		validate_readwrite(arg, sizeof(struct hop_directory_link));
		data        = (struct hop_directory_link *)arg;
		struct_size = ATOMIC_READ(data->dli_struct_size);
		if (struct_size != sizeof(struct hop_directory_link))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_directory_link), struct_size);
		COMPILER_READ_BARRIER();
		name        = data->dli_name;
		namelen     = data->dli_len;
		link_mode   = data->dli_flags;
		link_nodefd = data->dli_linknode;
		COMPILER_READ_BARRIER();
		validate_readable(name, namelen);
		VALIDATE_FLAGSET(link_mode,
		                 HOP_DIRECTORY_LINK_FNOCASE,
		                 E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_LINK_FLAGS);
		link_node = handle_get_inode(link_nodefd);
		{
			FINALLY_DECREF(link_node);
			cred_require_sysadmin(); /* TODO: More finely grained access! */
			directory_link((struct directory_node *)self,
			               name,
			               namelen,
			               link_node,
			               link_mode,
			               &child_entry);
		}
		{
			struct hop_openfd *fd;
			FINALLY_DECREF(child_entry);
			/* Install handles for objects that the caller wants to open */
			if ((fd = ATOMIC_READ(data->dli_dent)) != NULL) {
				temp.h_type = HANDLE_TYPE_DIRECTORYENTRY;
				temp.h_mode = mode;
				temp.h_data = child_entry;
				handle_installhop(fd, temp);
			}
		}
	}	break;

	case HOP_DIRECTORY_SYMLINK: {
		STATIC_ASSERT(HOP_DIRECTORY_SYMLINK_FNORMAL == DIRECTORY_SYMLINK_FNORMAL);
		STATIC_ASSERT(HOP_DIRECTORY_SYMLINK_FNOCASE == DIRECTORY_SYMLINK_FNOCASE);
		size_t struct_size;
		struct hop_directory_symlink *data;
		USER UNCHECKED char const *name;
		u16 namelen;
		USER UNCHECKED char const *text;
		size_t textlen;
		unsigned int symlink_createmode;
		REF struct symlink_node *child_node;
		REF struct directory_entry *child_entry;
		struct handle temp;
		mode_t symlink_mode;
		uid_t symlink_owner;
		gid_t symlink_group;
		if (!vm_datablock_isinode(self) || !INODE_ISDIR((struct inode *)self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_DATABLOCK,
			      0,
			      HANDLE_TYPEKIND_DATABLOCK_DIRECTORY,
			      0);
		validate_readwrite(arg, sizeof(struct hop_directory_symlink));
		data        = (struct hop_directory_symlink *)arg;
		struct_size = ATOMIC_READ(data->dsl_struct_size);
		if (struct_size != sizeof(struct hop_directory_symlink))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_directory_symlink), struct_size);
		COMPILER_READ_BARRIER();
		name               = data->dsl_name;
		namelen            = data->dsl_len;
		symlink_createmode = data->dsl_flags;
		text               = data->dsl_text;
		textlen            = data->dsl_textlen;
		symlink_mode       = (mode_t)data->dsl_mode;
		symlink_owner      = (uid_t)data->dsl_owner;
		symlink_group      = (gid_t)data->dsl_group;
		COMPILER_READ_BARRIER();
		validate_readable(name, namelen);
		validate_readable(text, textlen);
		VALIDATE_FLAGSET(symlink_createmode,
		                 HOP_DIRECTORY_SYMLINK_FNOCASE,
		                 E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_SYMLINK_FLAGS);
		VALIDATE_FLAGSET(symlink_mode, 07777,
		                 E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_SYMLINK_MODE);
		if (symlink_owner == (uid_t)-1)
			symlink_owner = fs_getuid(THIS_FS);
		if (symlink_group == (gid_t)-1)
			symlink_group = fs_getgid(THIS_FS);
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		child_node = directory_symlink((struct directory_node *)self,
		                               name,
		                               namelen,
		                               text,
		                               textlen,
		                               symlink_owner,
		                               symlink_group,
		                               symlink_mode,
		                               symlink_createmode,
		                               &child_entry);
		{
			struct hop_openfd *fd;
			FINALLY_DECREF(child_entry);
			FINALLY_DECREF(child_node);
			/* Install handles for objects that the caller wants to open */
			if ((fd = ATOMIC_READ(data->dsl_node)) != NULL) {
				temp.h_type = HANDLE_TYPE_DATABLOCK;
				temp.h_mode = mode;
				temp.h_data = child_node;
				handle_installhop(fd, temp);
			}
			if ((fd = ATOMIC_READ(data->dsl_dent)) != NULL) {
				temp.h_type = HANDLE_TYPE_DIRECTORYENTRY;
				temp.h_mode = mode;
				temp.h_data = child_entry;
				handle_installhop(fd, temp);
			}
		}
	}	break;

	case HOP_DIRECTORY_MKNOD: {
		STATIC_ASSERT(HOP_DIRECTORY_MKNOD_FNORMAL == DIRECTORY_MKNOD_FNORMAL);
		STATIC_ASSERT(HOP_DIRECTORY_MKNOD_FNOCASE == DIRECTORY_MKNOD_FNOCASE);
		size_t struct_size;
		struct hop_directory_mknod *data;
		USER UNCHECKED char const *name;
		u16 namelen;
		unsigned int mknod_mode;
		REF struct inode *child_node;
		REF struct directory_entry *child_entry;
		struct handle temp;
		mode_t newfile_mode;
		uid_t newfile_owner;
		gid_t newfile_group;
		dev_t mknod_dev;
		if (!vm_datablock_isinode(self) || !INODE_ISDIR((struct inode *)self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_DATABLOCK,
			      0,
			      HANDLE_TYPEKIND_DATABLOCK_DIRECTORY,
			      0);
		validate_readwrite(arg, sizeof(struct hop_directory_mknod));
		data        = (struct hop_directory_mknod *)arg;
		struct_size = ATOMIC_READ(data->dmn_struct_size);
		if (struct_size != sizeof(struct hop_directory_mknod))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_directory_mknod), struct_size);
		COMPILER_READ_BARRIER();
		name          = data->dmn_name;
		namelen       = data->dmn_len;
		mknod_mode    = data->dmn_flags;
		newfile_mode  = (mode_t)data->dmn_mode;
		newfile_owner = (uid_t)data->dmn_owner;
		newfile_group = (gid_t)data->dmn_group;
		mknod_dev     = (dev_t)data->dmn_device;
		COMPILER_READ_BARRIER();
		validate_readable(name, namelen);
		newfile_mode &= ~ATOMIC_READ(THIS_FS->f_umask);
		VALIDATE_FLAGSET(mknod_mode,
		                 HOP_DIRECTORY_MKNOD_FNOCASE,
		                 E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKNOD_FLAGS);
		VALIDATE_FLAGSET(newfile_mode, 07777 | S_IFMT,
		                 E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKNOD_MODE);
		if ((newfile_mode & S_IFMT) != S_IFREG &&
		    (newfile_mode & S_IFMT) != S_IFCHR &&
		    (newfile_mode & S_IFMT) != S_IFBLK) {
			THROW(E_INVALID_ARGUMENT_BAD_FLAG_MASK,
			      E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKNOD_MODE,
			      newfile_mode,
			      S_IFMT);
		}
		if (newfile_owner == (uid_t)-1)
			newfile_owner = fs_getuid(THIS_FS);
		if (newfile_group == (gid_t)-1)
			newfile_group = fs_getgid(THIS_FS);
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		child_node = directory_mknod((struct directory_node *)self,
		                             name,
		                             namelen,
		                             newfile_mode,
		                             newfile_owner,
		                             newfile_group,
		                             mknod_dev,
		                             mknod_mode,
		                             &child_entry);
		{
			struct hop_openfd *fd;
			FINALLY_DECREF(child_entry);
			FINALLY_DECREF(child_node);
			/* Install handles for objects that the caller wants to open */
			if ((fd = ATOMIC_READ(data->dmn_node)) != NULL) {
				temp.h_type = HANDLE_TYPE_DATABLOCK;
				temp.h_mode = mode;
				temp.h_data = child_node;
				handle_installhop(fd, temp);
			}
			if ((fd = ATOMIC_READ(data->dmn_dent)) != NULL) {
				temp.h_type = HANDLE_TYPE_DIRECTORYENTRY;
				temp.h_mode = mode;
				temp.h_data = child_entry;
				handle_installhop(fd, temp);
			}
		}
	}	break;

	case HOP_DIRECTORY_MKDIR: {
		STATIC_ASSERT(HOP_DIRECTORY_MKDIR_FNORMAL == DIRECTORY_MKDIR_FNORMAL);
		STATIC_ASSERT(HOP_DIRECTORY_MKDIR_FNOCASE == DIRECTORY_MKDIR_FNOCASE);
		size_t struct_size;
		struct hop_directory_mkdir *data;
		USER UNCHECKED char const *name;
		u16 namelen;
		unsigned int mkdir_mode;
		REF struct directory_node *child_node;
		REF struct directory_entry *child_entry;
		struct handle temp;
		mode_t newfile_mode;
		uid_t newfile_owner;
		gid_t newfile_group;
		if (!vm_datablock_isinode(self) || !INODE_ISDIR((struct inode *)self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_DATABLOCK,
			      0,
			      HANDLE_TYPEKIND_DATABLOCK_DIRECTORY,
			      0);
		validate_readwrite(arg, sizeof(struct hop_directory_mkdir));
		data        = (struct hop_directory_mkdir *)arg;
		struct_size = ATOMIC_READ(data->dmd_struct_size);
		if (struct_size != sizeof(struct hop_directory_mkdir))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_directory_mkdir), struct_size);
		COMPILER_READ_BARRIER();
		name          = data->dmd_name;
		namelen       = data->dmd_len;
		mkdir_mode    = data->dmd_flags;
		newfile_mode  = (mode_t)data->dmd_mode;
		newfile_owner = (uid_t)data->dmd_owner;
		newfile_group = (gid_t)data->dmd_group;
		COMPILER_READ_BARRIER();
		validate_readable(name, namelen);
		VALIDATE_FLAGSET(mkdir_mode,
		                 HOP_DIRECTORY_MKDIR_FNOCASE,
		                 E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKDIR_FLAGS);
		VALIDATE_FLAGSET(newfile_mode, 07777,
		                 E_INVALID_ARGUMENT_CONTEXT_HOP_DIRECTORY_MKDIR_MODE);
		if (newfile_owner == (uid_t)-1)
			newfile_owner = fs_getuid(THIS_FS);
		if (newfile_group == (gid_t)-1)
			newfile_group = fs_getgid(THIS_FS);
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		child_node = directory_mkdir((struct directory_node *)self,
		                             name,
		                             namelen,
		                             newfile_mode & ~ATOMIC_READ(THIS_FS->f_umask),
		                             newfile_owner,
		                             newfile_group,
		                             mkdir_mode,
		                             &child_entry);
		{
			struct hop_openfd *fd;
			FINALLY_DECREF(child_entry);
			FINALLY_DECREF(child_node);
			/* Install handles for objects that the caller wants to open */
			if ((fd = ATOMIC_READ(data->dmd_node)) != NULL) {
				temp.h_type = HANDLE_TYPE_DATABLOCK;
				temp.h_mode = mode;
				temp.h_data = child_node;
				handle_installhop(fd, temp);
			}
			if ((fd = ATOMIC_READ(data->dmd_dent)) != NULL) {
				temp.h_type = HANDLE_TYPE_DIRECTORYENTRY;
				temp.h_mode = mode;
				temp.h_data = child_entry;
				handle_installhop(fd, temp);
			}
		}
	}	break;

	case HOP_SUPERBLOCK_OPEN_BLOCKDEVICE: {
		struct handle result_handle;
		if (!vm_datablock_isinode(self) || !INODE_ISSUPER((struct inode *)self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_DATABLOCK,
			      0,
			      HANDLE_TYPEKIND_DATABLOCK_SUPERBLOCK,
			      0);
		cred_require_sysadmin(); /* TODO: More finely grained access! */
		result_handle.h_data = ((struct superblock *)self)->s_device;
		if (!result_handle.h_data)
			THROW(E_NO_SUCH_BLOCKDEVICE);
		result_handle.h_mode = mode;
		result_handle.h_type = HANDLE_TYPE_BLOCKDEVICE;
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, result_handle);
	}	break;

	case HOP_SUPERBLOCK_OPEN_DRIVER: {
		struct handle result_handle;
		if (!vm_datablock_isinode(self) || !INODE_ISSUPER((struct inode *)self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_DATABLOCK,
			      0,
			      HANDLE_TYPEKIND_DATABLOCK_SUPERBLOCK,
			      0);
		cred_require_sysadmin();
		result_handle.h_type = HANDLE_TYPE_DRIVER;
		result_handle.h_mode = mode;
		result_handle.h_data = ((struct superblock *)self)->s_driver;
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, result_handle);
	}	break;

	case HOP_SUPERBLOCK_SYNC:
		if (!vm_datablock_isinode(self) || !INODE_ISSUPER((struct inode *)self))
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_DATABLOCK,
			      0,
			      HANDLE_TYPEKIND_DATABLOCK_SUPERBLOCK,
			      0);
		superblock_sync((struct superblock *)self,
		                (unsigned int)(uintptr_t)arg != 0);
		break;

	case HOP_SUPERBLOCK_FEATURES: {
		struct superblock *super;
		struct hop_superblock_features *data;
		size_t struct_size;
		u32 feat_flags;
		if (!vm_datablock_isinode(self)) {
			THROW(E_INVALID_HANDLE_FILETYPE,
			      0, /* Filled in by the caller */
			      HANDLE_TYPE_DATABLOCK,
			      0,
			      HANDLE_TYPEKIND_DATABLOCK_INODE,
			      0);
		}
		validate_readwrite(arg, sizeof(struct hop_superblock_features));
		data        = (struct hop_superblock_features *)arg;
		struct_size = ATOMIC_READ(data->sbf_struct_size);
		if (struct_size != sizeof(struct hop_superblock_features))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_superblock_features), struct_size);
		super = ((struct inode *)self)->i_super;
		feat_flags = 0;
		if (superblock_features_has_symlink(&super->s_features))
			feat_flags |= HOP_SUPERBLOCK_FEAT_SYMLINKS;
		if (superblock_features_has_hrdlink(&super->s_features))
			feat_flags |= HOP_SUPERBLOCK_FEAT_HRDLINKS;
		COMPILER_READ_BARRIER();
		/* Copy features info to user-space. */
		data->sbf_features           = feat_flags;
		data->sbf_sector_size        = VM_DATABLOCK_PAGESIZE(self);
		data->sbf_link_max           = (u64)super->s_features.sf_link_max;
		data->sbf_name_max           = (u64)super->s_features.sf_name_max;
		data->sbf_symlink_max        = (u64)super->s_features.sf_symlink_max;
		data->sbf_rec_incr_xfer_size = (u32)super->s_features.sf_rec_incr_xfer_size;
		data->sbf_rec_max_xfer_size  = (u32)super->s_features.sf_rec_max_xfer_size;
		data->sbf_rec_min_xfer_size  = (u32)super->s_features.sf_rec_min_xfer_size;
		data->sbf_rec_xfer_align     = (u32)super->s_features.sf_rec_xfer_align;
		data->sbf_filesizebits       = super->s_features.sf_filesizebits;
		data->sbf_magic              = super->s_features.sf_magic;
		COMPILER_READ_BARRIER();
	}	break;

		/* TODO: HOP for using `inode_read_blocking()' */
		/* TODO: HOP for using `inode_readv_blocking()' */

	default:
		/* Handle FIFO control operations if we are referring to one. */
		if (vm_datablock_isinode(self) && INODE_ISFIFO((struct inode *)self))
			return fifo_hop((struct fifo_node *)self, cmd, arg, mode);
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND,
		      cmd);
		break;
	}
	return 0;
}

PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) size_t
NOTHROW(KCALL vm_datablock_count_part)(struct vm_datapart const *__restrict self) {
	size_t result = 0;
again:
	++result;
	assert(!mpart_isanon(self));
	if (self->mp_filent.rb_lhs) {
		if (self->mp_filent.rb_rhs)
			result += vm_datablock_count_part(self->mp_filent.rb_rhs);
		self = self->mp_filent.rb_lhs;
		goto again;
	}
	if (self->mp_filent.rb_rhs) {
		self = self->mp_filent.rb_rhs;
		goto again;
	}
	return result;
}

INTERN NONNULL((1)) void KCALL
handle_datablock_stat(struct vm_datablock *__restrict self,
                      USER CHECKED struct stat *result) {
	if (vm_datablock_isinode(self)) {
		/* INode stat! */
		inode_stat((struct inode *)self, result);
	} else {
		/* Generic data-block stat */
		size_t partcount = 0;
		mfile_lock_read(self);
		if (self->db_parts && self->db_parts != MFILE_PARTS_ANONYMOUS)
			partcount = vm_datablock_count_part(self->db_parts);
		mfile_lock_endread(self);
		COMPILER_BARRIER();
		memset(result, 0, sizeof(*result));
		result->st_blksize = VM_DATABLOCK_PAGESIZE(self);
		result->st_blocks  = partcount;
	}
}

INTERN NONNULL((1, 2)) void KCALL
handle_datablock_mmap(struct vm_datablock *__restrict self,
                      struct handle_mmap_info *__restrict info)
		THROWS(...) {
	info->hmi_file = incref(self);
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_DATABLOCK_HANDLE_C */
