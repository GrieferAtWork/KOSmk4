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
#ifndef GUARD_KERNEL_SRC_USER_HANDLE_AS_C
#define GUARD_KERNEL_SRC_USER_HANDLE_AS_C 1
#define NO_HANDLE_AS_CXX_OVERLOADS 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <fs/file.h>
#include <fs/node.h>
#include <fs/pipe.h>
#include <fs/vfs.h>
#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/vm.h>
#include <sched/pid.h>
#include <sched/task.h>

#include <kos/except/fs.h>

DECL_BEGIN

PRIVATE ATTR_NORETURN ATTR_COLD ATTR_NOINLINE void KCALL
throw_bad_handle_type(uintptr_half_t excepted_type,
                      uintptr_half_t excepted_kind) {
	THROW(E_INVALID_HANDLE_FILETYPE,
	      0, /* Filled in the caller */
	      excepted_type,
	      0, /* Filled in the caller */
	      excepted_kind);
}


/* Convert handle types */
PUBLIC WUNUSED ATTR_RETNONNULL REF struct inode *FCALL
handle_as_inode(REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	switch (self->h_type) {

	case HANDLE_TYPE_DATABLOCK:
		if (vm_datablock_isinode((struct vm_datablock *)self->h_data))
			return (REF struct inode *)self->h_data;
		break;

	case HANDLE_TYPE_FILE: {
		REF struct inode *resnode;
		resnode = (REF struct inode *)incref(((struct file *)self->h_data)->f_node);
		decref_unlikely((struct file *)self->h_data);
		return resnode;
	}	break;

	case HANDLE_TYPE_ONESHOT_DIRECTORY_FILE: {
		REF struct directory_node *resnode;
		resnode = (REF struct directory_node *)incref(((struct oneshot_directory_file *)self->h_data)->d_node);
		decref_unlikely((struct oneshot_directory_file *)self->h_data);
		return resnode;
	}	break;

	case HANDLE_TYPE_PATH: {
		REF struct inode *resnode;
		sync_read((struct path *)self->h_data);
		resnode = ((struct path *)self->h_data)->p_inode;
		if unlikely(!resnode) {
			sync_endread((struct path *)self->h_data);
			THROW(E_FSERROR_DELETED,
			      E_FILESYSTEM_DELETED_UNMOUNTED);
		}
		incref(resnode);
		sync_endread((struct path *)self->h_data);
		decref_unlikely(self);
		return resnode;
	}	break;

	default: break;
	}
	throw_bad_handle_type(HANDLE_TYPE_DATABLOCK,
	                      HANDLE_TYPEKIND_DATABLOCK_INODE);
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct regular_node *FCALL
handle_as_regular_node(REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	switch (self->h_type) {

	case HANDLE_TYPE_DATABLOCK:
		if (vm_datablock_isinode((struct vm_datablock *)self->h_data) &&
		    INODE_ISREG((struct inode *)self->h_data))
			return (REF struct regular_node *)self->h_data;
		break;

	case HANDLE_TYPE_FILE: {
		REF struct inode *resnode;
		resnode = ((struct file *)self->h_data)->f_node;
		if (INODE_ISREG(resnode)) {
			incref(resnode);
			decref_unlikely((struct file *)self->h_data);
			return (REF struct regular_node *)resnode;
		}
	}	break;

	default: break;
	}
	throw_bad_handle_type(HANDLE_TYPE_DATABLOCK,
	                      HANDLE_TYPEKIND_DATABLOCK_REGULARNODE);
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct directory_node *FCALL
handle_as_directory_node(REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	switch (self->h_type) {

	case HANDLE_TYPE_DATABLOCK:
		if (vm_datablock_isinode((struct vm_datablock *)self->h_data) &&
		    INODE_ISDIR((struct inode *)self->h_data))
			return (REF struct directory_node *)self->h_data;
		break;

	case HANDLE_TYPE_FILE: {
		REF struct inode *resnode;
		resnode = ((struct file *)self->h_data)->f_node;
		if (INODE_ISDIR(resnode)) {
			incref(resnode);
			decref_unlikely((struct file *)self->h_data);
			return (REF struct directory_node *)resnode;
		}
	}	break;

	case HANDLE_TYPE_ONESHOT_DIRECTORY_FILE: {
		REF struct directory_node *resnode;
		resnode = (REF struct directory_node *)incref(((struct oneshot_directory_file *)self->h_data)->d_node);
		decref_unlikely((struct oneshot_directory_file *)self->h_data);
		return resnode;
	}	break;

	case HANDLE_TYPE_PATH: {
		REF struct directory_node *resnode;
		sync_read((struct path *)self->h_data);
		resnode = ((struct path *)self->h_data)->p_inode;
		if unlikely(!resnode) {
			sync_endread((struct path *)self->h_data);
			THROW(E_FSERROR_DELETED,
			      E_FILESYSTEM_DELETED_UNMOUNTED);
		}
		incref(resnode);
		sync_endread((struct path *)self->h_data);
		decref_unlikely((struct path *)self->h_data);
		return resnode;
	}	break;

	default: break;
	}
	throw_bad_handle_type(HANDLE_TYPE_DATABLOCK,
	                      HANDLE_TYPEKIND_DATABLOCK_DIRECTORY);
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct directory_entry *FCALL
handle_as_directory_entry(REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	switch (self->h_type) {

	case HANDLE_TYPE_DIRECTORYENTRY:
		return (REF struct directory_entry *)self->h_data;

	case HANDLE_TYPE_FILE:
	case HANDLE_TYPE_ONESHOT_DIRECTORY_FILE: {
		REF struct directory_entry *resent;
		STATIC_ASSERT(offsetof(struct file, f_dirent) ==
		              offsetof(struct oneshot_directory_file, d_dirent));
		resent = ((struct file *)self->h_data)->f_dirent;
		if (resent) {
			incref(resent);
			decref_unlikely(self);
			return resent;
		}
	}	break;

	case HANDLE_TYPE_PATH: {
		REF struct directory_entry *resent;
		sync_read((struct path *)self->h_data);
		if unlikely(!((struct path *)self->h_data)->p_inode) {
			sync_endread((struct path *)self->h_data);
			THROW(E_FSERROR_DELETED,
			      E_FILESYSTEM_DELETED_UNMOUNTED);
		}
		resent = incref(((struct path *)self->h_data)->p_dirent);
		sync_endread((struct path *)self->h_data);
		decref_unlikely((REF struct path *)self->h_data);
		return resent;
	}	break;

	default: break;
	}
	throw_bad_handle_type(HANDLE_TYPE_DIRECTORYENTRY,
	                      HANDLE_TYPEKIND_GENERIC);
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct vm_datablock *FCALL
handle_as_datablock(REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	switch (self->h_type) {

	case HANDLE_TYPE_DATABLOCK:
		return (REF struct vm_datablock *)self->h_data;

	case HANDLE_TYPE_FILE: {
		REF struct inode *resnode;
		resnode = (REF struct inode *)incref(((struct file *)self->h_data)->f_node);
		decref_unlikely((struct file *)self->h_data);
		return resnode;
	}	break;

	case HANDLE_TYPE_ONESHOT_DIRECTORY_FILE: {
		REF struct directory_node *resnode;
		resnode = (REF struct directory_node *)incref(((struct oneshot_directory_file *)self->h_data)->d_node);
		decref_unlikely((struct oneshot_directory_file *)self->h_data);
		return resnode;
	}	break;

	case HANDLE_TYPE_PATH: {
		REF struct inode *resnode;
		struct path *mypath;
		mypath = (struct path *)self->h_data;
		sync_read(mypath);
		resnode = (mypath)->p_inode;
		if unlikely(!resnode) {
			sync_endread(mypath);
			THROW(E_FSERROR_DELETED,
			      E_FILESYSTEM_DELETED_UNMOUNTED);
		}
		incref(resnode);
		sync_endread(mypath);
		decref_unlikely(mypath);
		return resnode;
	}	break;

	default: break;
	}
	throw_bad_handle_type(HANDLE_TYPE_DATABLOCK,
	                      HANDLE_TYPEKIND_DATABLOCK_GENERIC);
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct superblock *FCALL
handle_as_superblock(REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	switch (self->h_type) {

	case HANDLE_TYPE_DATABLOCK:
		if (vm_datablock_isinode((struct vm_datablock *)self->h_data) &&
		    INODE_ISSUPER((struct inode *)self->h_data))
			return (REF struct superblock *)self->h_data;
		break;

	case HANDLE_TYPE_FILE: {
		REF struct inode *resnode;
		resnode = ((struct file *)self->h_data)->f_node;
		if (INODE_ISSUPER(resnode)) {
			incref(resnode);
			decref_unlikely((struct file *)self->h_data);
			return (REF struct superblock *)resnode;
		}
	}	break;

	case HANDLE_TYPE_ONESHOT_DIRECTORY_FILE: {
		REF struct directory_node *resnode;
		resnode = ((struct oneshot_directory_file *)self->h_data)->d_node;
		if (INODE_ISSUPER(resnode)) {
			incref(resnode);
			decref_unlikely((struct oneshot_directory_file *)self->h_data);
			return (REF struct superblock *)resnode;
		}
	}	break;

	case HANDLE_TYPE_PATH: {
		REF struct inode *resnode;
		sync_read((struct path *)self->h_data);
		resnode = ((struct path *)self->h_data)->p_inode;
		if unlikely(!resnode) {
			sync_endread((struct path *)self->h_data);
			THROW(E_FSERROR_DELETED,
			      E_FILESYSTEM_DELETED_UNMOUNTED);
		}
		if unlikely(!INODE_ISSUPER(resnode)) {
			sync_endread((struct path *)self->h_data);
			break;
		}
		incref(resnode);
		sync_endread((struct path *)self->h_data);
		decref_unlikely((struct path *)self->h_data);
		return (REF struct superblock *)resnode;
	}	break;

	default: break;
	}
	throw_bad_handle_type(HANDLE_TYPE_DATABLOCK,
	                      HANDLE_TYPEKIND_DATABLOCK_SUPERBLOCK);
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct superblock *FCALL
handle_as_superblock_relaxed(REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	REF struct superblock *resblock;
	switch (self->h_type) {

	case HANDLE_TYPE_DATABLOCK:
		if (vm_datablock_isinode((struct vm_datablock *)self->h_data)) {
			resblock = ((struct inode *)self->h_data)->i_super;
			incref(resblock);
			decref_unlikely((struct inode *)self->h_data);
			return resblock;
		}
		break;

	case HANDLE_TYPE_FILE: {
		REF struct superblock *resnode;
		resnode = (REF struct superblock *)incref(((struct file *)self->h_data)->f_node->i_super);
		decref_unlikely((struct file *)self->h_data);
		return resnode;
	}	break;

	case HANDLE_TYPE_ONESHOT_DIRECTORY_FILE: {
		REF struct superblock *resnode;
		resnode = (REF struct superblock *)incref(((struct oneshot_directory_file *)self->h_data)->d_node->i_super);
		decref_unlikely((struct oneshot_directory_file *)self->h_data);
		return resnode;
	}	break;

	case HANDLE_TYPE_PATH: {
		REF struct inode *resnode;
		sync_read((struct path *)self->h_data);
		resnode = ((struct path *)self->h_data)->p_inode;
		if unlikely(!resnode) {
			sync_endread((struct path *)self->h_data);
			THROW(E_FSERROR_DELETED,
			      E_FILESYSTEM_DELETED_UNMOUNTED);
		}
		resblock = resnode->i_super;
		incref(resblock);
		sync_endread((struct path *)self->h_data);
		decref_unlikely((struct path *)self->h_data);
		return (REF struct superblock *)resblock;
	}	break;

	default: break;
	}
	throw_bad_handle_type(HANDLE_TYPE_DATABLOCK,
	                      HANDLE_TYPEKIND_DATABLOCK_SUPERBLOCK);
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct path *FCALL
handle_as_path(REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	switch (self->h_type) {

	case HANDLE_TYPE_FILE: {
		REF struct path *respath;
		respath = incref(((struct file *)self->h_data)->f_path);
		decref_unlikely((struct file *)self->h_data);
		return respath;
	}	break;

	case HANDLE_TYPE_ONESHOT_DIRECTORY_FILE: {
		REF struct path *respath;
		respath = incref(((struct oneshot_directory_file *)self->h_data)->d_path);
		decref_unlikely((struct oneshot_directory_file *)self->h_data);
		return respath;
	}	break;

	case HANDLE_TYPE_PATH:
		return (REF struct path *)self->h_data;

	default: break;
	}
	throw_bad_handle_type(HANDLE_TYPE_PATH,
	                      HANDLE_TYPEKIND_PATH_GENERIC);
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct taskpid *FCALL
handle_as_taskpid(REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	switch (self->h_type) {

	case HANDLE_TYPE_TASK:
		return (REF struct taskpid *)self->h_data;

	default: break;
	}
	throw_bad_handle_type(HANDLE_TYPE_TASK,
	                      HANDLE_TYPEKIND_GENERIC);
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct task *FCALL
handle_as_task(REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE, E_PROCESS_EXITED) {
	switch (self->h_type) {

	case HANDLE_TYPE_TASK: {
		REF struct task *restask;
		restask = taskpid_gettask((struct taskpid *)self->h_data);
		if unlikely(!restask) {
			THROW(E_PROCESS_EXITED,
			      taskpid_getpid((struct taskpid *)self->h_data,
			                     THIS_PIDNS));
		}
		decref_unlikely((struct taskpid *)self->h_data);
		return restask;
	}	break;

	default: break;
	}
	throw_bad_handle_type(HANDLE_TYPE_TASK,
	                      HANDLE_TYPEKIND_GENERIC);
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct vm *FCALL
handle_as_vm(REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	switch (self->h_type) {

	case HANDLE_TYPE_VM:
		return (REF struct vm *)self->h_data;

	case HANDLE_TYPE_TASK:
		if (self->h_data == THIS_TASKPID) {
			decref_unlikely((struct taskpid *)self->h_data);
			return incref(THIS_VM);
		}
		break;

	default: break;
	}
	throw_bad_handle_type(HANDLE_TYPE_VM,
	                      HANDLE_TYPEKIND_GENERIC);
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct fs *FCALL
handle_as_fs(REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	switch (self->h_type) {

	case HANDLE_TYPE_FS:
		return (REF struct fs *)self->h_data;

	case HANDLE_TYPE_TASK:
		if (self->h_data == THIS_TASKPID) {
			decref_unlikely((struct taskpid *)self->h_data);
			return incref(THIS_FS);
		}
		break;

	default: break;
	}
	throw_bad_handle_type(HANDLE_TYPE_FS,
	                      HANDLE_TYPEKIND_GENERIC);
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct vfs *FCALL
handle_as_vfs(REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	switch (self->h_type) {

	case HANDLE_TYPE_PATH:
		if (((struct path *)self->h_data)->p_vfs == (struct path *)self->h_data)
			return (REF struct vfs *)self->h_data;
		break;

	case HANDLE_TYPE_TASK:
		if (self->h_data == THIS_TASKPID) {
			decref_unlikely((struct taskpid *)self->h_data);
			return (REF struct vfs *)incref(THIS_VFS);
		}
		break;

	default: break;
	}
	throw_bad_handle_type(HANDLE_TYPE_PATH,
	                      HANDLE_TYPEKIND_PATH_VFSROOT);
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct pipe *FCALL
handle_as_pipe(REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	switch (self->h_type) {

	case HANDLE_TYPE_PIPE:
		return (REF struct pipe *)self->h_data;

	case HANDLE_TYPE_PIPE_READER:
	case HANDLE_TYPE_PIPE_WRITER: {
		REF struct pipe *respipe;
		respipe = incref(((struct pipe_reader *)self->h_data)->pr_pipe);
		decref_unlikely(self);
		return respipe;
	}

	default: break;
	}
	throw_bad_handle_type(HANDLE_TYPE_PIPE,
	                      HANDLE_TYPEKIND_PATH_VFSROOT);
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct driver *FCALL
handle_as_driver(REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	switch (self->h_type) {

	case HANDLE_TYPE_DRIVER:
		return (REF struct driver *)self->h_data;

	default: break;
	}
	throw_bad_handle_type(HANDLE_TYPE_DRIVER,
	                      HANDLE_TYPEKIND_GENERIC);
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct pidns *FCALL
handle_as_pidns(REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	switch (self->h_type) {

	case HANDLE_TYPE_PIDNS:
		return (REF struct pidns *)self->h_data;

	case HANDLE_TYPE_TASK:
		if (self->h_data == THIS_TASKPID) {
			decref_unlikely((struct taskpid *)self->h_data);
			return incref(THIS_PIDNS);
		}
		break;

	default: break;
	}
	throw_bad_handle_type(HANDLE_TYPE_PIDNS,
	                      HANDLE_TYPEKIND_GENERIC);
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct socket *FCALL
handle_as_socket(REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	switch (self->h_type) {

	case HANDLE_TYPE_SOCKET:
		return (REF struct socket *)self->h_data;

	default: break;
	}
	throw_bad_handle_type(HANDLE_TYPE_SOCKET,
	                      HANDLE_TYPEKIND_GENERIC);
}



/* Complete a thrown exception, inherit a reference to
 * `hnd', and rethrow the already thrown exception. */
PRIVATE ATTR_COLD ATTR_NOINLINE ATTR_NORETURN NONNULL((2)) void FCALL
handle_get_complete_except(unsigned int fd, REF struct handle *__restrict hnd) {
	if (was_thrown(E_INVALID_HANDLE_FILETYPE)) {
		if (!PERTASK_GET(this_exception_pointers[0]))
			PERTASK_SET(this_exception_pointers[0], (uintptr_t)fd);
		if (!PERTASK_GET(this_exception_pointers[2]))
			PERTASK_SET(this_exception_pointers[2], (uintptr_t)hnd->h_type);
		if (!PERTASK_GET(this_exception_pointers[4]))
			PERTASK_SET(this_exception_pointers[4], (uintptr_t)handle_typekind(hnd));
	}
	RETHROW();
}



PUBLIC WUNUSED ATTR_RETNONNULL REF struct inode *FCALL handle_get_inode(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE) {
	struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_inode(&hnd);
	} EXCEPT {
		handle_get_complete_except(fd, &hnd);
	}
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct regular_node *FCALL
handle_get_regular_node(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE) {
	struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_regular_node(&hnd);
	} EXCEPT {
		handle_get_complete_except(fd, &hnd);
	}
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct directory_node *FCALL
handle_get_directory_node(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE) {
	struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_directory_node(&hnd);
	} EXCEPT {
		handle_get_complete_except(fd, &hnd);
	}
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct directory_entry *FCALL
handle_get_directory_entry(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE) {
	struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_directory_entry(&hnd);
	} EXCEPT {
		handle_get_complete_except(fd, &hnd);
	}
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct vm_datablock *FCALL
handle_get_datablock(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE) {
	struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_datablock(&hnd);
	} EXCEPT {
		handle_get_complete_except(fd, &hnd);
	}
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct superblock *FCALL
handle_get_superblock(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE) {
	struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_superblock(&hnd);
	} EXCEPT {
		handle_get_complete_except(fd, &hnd);
	}
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct superblock *FCALL
handle_get_superblock_relaxed(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE) {
	struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_superblock_relaxed(&hnd);
	} EXCEPT {
		handle_get_complete_except(fd, &hnd);
	}
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct path *FCALL
handle_get_path(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE) {
	struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_path(&hnd);
	} EXCEPT {
		handle_get_complete_except(fd, &hnd);
	}
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct taskpid *FCALL
handle_get_taskpid(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE) {
	struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_taskpid(&hnd);
	} EXCEPT {
		handle_get_complete_except(fd, &hnd);
	}
}

/* @throw: E_PROCESS_EXITED: `fd' belongs to a task that is no longer allocated. */
PUBLIC WUNUSED ATTR_RETNONNULL REF struct task *FCALL
handle_get_task(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE, E_PROCESS_EXITED) {
	struct handle hnd;
	switch (fd) {

	case HANDLE_SYMBOLIC_THISTASK:
		return incref(THIS_TASK);

	case HANDLE_SYMBOLIC_THISPROCESS:
		return incref(task_getprocess());

	case HANDLE_SYMBOLIC_GROUPLEADER:
		return task_getprocessgroupleader_srch();

	case HANDLE_SYMBOLIC_SESSIONLEADER:
		return task_getsessionleader_srch();

	case HANDLE_SYMBOLIC_PARENTPROCESS: {
		REF struct task *temp;
		temp = task_getprocessparent();
		if likely(temp)
			return temp;
	}	break;

	default: break;
	}
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_task(&hnd);
	} EXCEPT {
		handle_get_complete_except(fd, &hnd);
	}
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct vm *FCALL
handle_get_vm(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE) {
	struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_vm(&hnd);
	} EXCEPT {
		handle_get_complete_except(fd, &hnd);
	}
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct fs *FCALL
handle_get_fs(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE) {
	struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_fs(&hnd);
	} EXCEPT {
		handle_get_complete_except(fd, &hnd);
	}
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct vfs *FCALL
handle_get_vfs(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE) {
	struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_vfs(&hnd);
	} EXCEPT {
		handle_get_complete_except(fd, &hnd);
	}
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct pipe *FCALL
handle_get_pipe(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE) {
	struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_pipe(&hnd);
	} EXCEPT {
		handle_get_complete_except(fd, &hnd);
	}
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct driver *FCALL
handle_get_driver(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE) {
	struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_driver(&hnd);
	} EXCEPT {
		handle_get_complete_except(fd, &hnd);
	}
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct pidns *FCALL
handle_get_pidns(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE) {
	struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_pidns(&hnd);
	} EXCEPT {
		handle_get_complete_except(fd, &hnd);
	}
}

PUBLIC WUNUSED ATTR_RETNONNULL REF struct socket *FCALL
handle_get_socket(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE) {
	struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_socket(&hnd);
	} EXCEPT {
		handle_get_complete_except(fd, &hnd);
	}
}




typedef WUNUSED ATTR_RETNONNULL REF void *(FCALL *PHANDLE_AS_CB_T)(REF struct handle const *__restrict self) THROWS(E_INVALID_HANDLE_FILETYPE);
PRIVATE WUNUSED ATTR_RETNONNULL REF void *FCALL
handle_as_error(REF struct handle const *__restrict UNUSED(self))
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	throw_bad_handle_type(HANDLE_TYPE_UNDEFINED,
	                      HANDLE_TYPEKIND_GENERIC);
}

/* Vector of handle-as converter function callbacks */
PRIVATE PHANDLE_AS_CB_T const handle_as_cbs[] = {
	[HANDLE_TYPE_UNDEFINED]              = (PHANDLE_AS_CB_T)&handle_as_error,
	[HANDLE_TYPE_DATABLOCK]              = (PHANDLE_AS_CB_T)&handle_as_datablock,
	[HANDLE_TYPE_BLOCKDEVICE]            = (PHANDLE_AS_CB_T)&handle_as_error,
	[HANDLE_TYPE_DIRECTORYENTRY]         = (PHANDLE_AS_CB_T)&handle_as_directory_entry,
	[HANDLE_TYPE_FILE]                   = (PHANDLE_AS_CB_T)&handle_as_error,
	[HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = (PHANDLE_AS_CB_T)&handle_as_error,
	[HANDLE_TYPE_PATH]                   = (PHANDLE_AS_CB_T)&handle_as_path,
	[HANDLE_TYPE_FS]                     = (PHANDLE_AS_CB_T)&handle_as_fs,
	[HANDLE_TYPE_VM]                     = (PHANDLE_AS_CB_T)&handle_as_vm,
	[HANDLE_TYPE_TASK]                   = (PHANDLE_AS_CB_T)&handle_as_taskpid,
	[HANDLE_TYPE_CLOCK]                  = (PHANDLE_AS_CB_T)&handle_as_error,
	[HANDLE_TYPE_DRIVER]                 = (PHANDLE_AS_CB_T)&handle_as_driver,
	[HANDLE_TYPE_PIPE]                   = (PHANDLE_AS_CB_T)&handle_as_pipe,
	[HANDLE_TYPE_PIPE_READER]            = (PHANDLE_AS_CB_T)&handle_as_error,
	[HANDLE_TYPE_PIPE_WRITER]            = (PHANDLE_AS_CB_T)&handle_as_error,
	[HANDLE_TYPE_PIDNS]                  = (PHANDLE_AS_CB_T)&handle_as_pidns,
	[HANDLE_TYPE_DRIVER_STATE]           = (PHANDLE_AS_CB_T)&handle_as_error,
	[HANDLE_TYPE_CHARACTERDEVICE]        = (PHANDLE_AS_CB_T)&handle_as_error,
	[HANDLE_TYPE_EVENTFD_FENCE]          = (PHANDLE_AS_CB_T)&handle_as_error,
	[HANDLE_TYPE_EVENTFD_SEMA]           = (PHANDLE_AS_CB_T)&handle_as_error,
	[HANDLE_TYPE_SIGNALFD]               = (PHANDLE_AS_CB_T)&handle_as_error,
	[HANDLE_TYPE_DATAPART]               = (PHANDLE_AS_CB_T)&handle_as_error,
	[HANDLE_TYPE_FUTEX]                  = (PHANDLE_AS_CB_T)&handle_as_error,
	[HANDLE_TYPE_FUTEXFD]                = (PHANDLE_AS_CB_T)&handle_as_error,
	[HANDLE_TYPE_DRIVER_SECTION]         = (PHANDLE_AS_CB_T)&handle_as_error,
	[HANDLE_TYPE_SOCKET]                 = (PHANDLE_AS_CB_T)&handle_as_socket,
/*	[HANDLE_TYPE_UAIO]                   = (PHANDLE_AS_CB_T)&handle_as_error, */
};


PUBLIC WUNUSED ATTR_RETNONNULL NONNULL((1)) REF void *FCALL
handle_as(REF struct handle const *__restrict self, uintptr_half_t wanted_type)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	/* Optimization for simple case: The handle already has the correct typing */
	if (self->h_type == wanted_type)
		return self->h_data;
	if likely(wanted_type < COMPILER_LENOF(handle_as_cbs)) {
		TRY {
			return (*handle_as_cbs[wanted_type])(self);
		} EXCEPT {
			if (was_thrown(E_INVALID_HANDLE_FILETYPE)) {
				if (!PERTASK_GET(this_exception_pointers[1]))
					PERTASK_SET(this_exception_pointers[1], (uintptr_t)wanted_type);
			}
			RETHROW();
		}
	}
	throw_bad_handle_type(wanted_type, HANDLE_TYPEKIND_GENERIC);
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_USER_HANDLE_AS_C */
