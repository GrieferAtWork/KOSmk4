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
#ifndef GUARD_KERNEL_SRC_USER_HANDLE_UTILITY_C
#define GUARD_KERNEL_SRC_USER_HANDLE_UTILITY_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <dev/block.h>
#include <dev/char.h>
#include <dev/keyboard.h>
#include <dev/mktty.h>
#include <dev/mouse.h>
#include <dev/pty.h>
#include <dev/tty.h>
#include <fs/fifo.h>
#include <fs/file.h>
#include <fs/node.h>
#include <fs/ramfs.h>
#include <fs/special-node.h>
#include <fs/vfs.h>
#include <kernel/fs/fifohandle.h>
#include <kernel/fs/fifonode.h>
#include <kernel/handle.h>
#include <kernel/mman/driver.h>
#include <kernel/mman/module.h>
#include <kernel/pipe.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/atomic64.h>
#include <sched/pid.h>

#include <hybrid/atomic.h>

#include <sys/stat.h>

#include <assert.h>
#include <format-printer.h>
#include <inttypes.h>
#include <stdint.h> /* UINT64_C */
#include <string.h>

DECL_BEGIN

/* Returns the type-kind code for `self' (One of `HANDLE_TYPEKIND_*') */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) uintptr_half_t
NOTHROW(KCALL handle_typekind)(struct handle const *__restrict self) {
	switch (self->h_type) {

	case HANDLE_TYPE_MFILE:
		if (vm_datablock_isinode((struct mfile *)self->h_data)) {
			if (INODE_ISSUPER((struct inode *)self->h_data))
				return HANDLE_TYPEKIND_MFILE_SUPERBLOCK;
			if (INODE_ISREG((struct inode *)self->h_data))
				return HANDLE_TYPEKIND_MFILE_REGULARNODE;
			if (INODE_ISDIR((struct inode *)self->h_data))
				return HANDLE_TYPEKIND_MFILE_DIRECTORY;
			if (INODE_ISLNK((struct inode *)self->h_data))
				return HANDLE_TYPEKIND_MFILE_SYMLINKNODE;
			if (INODE_ISFIFO((struct inode *)self->h_data))
				return HANDLE_TYPEKIND_MFILE_FIFONODE;
			if (INODE_ISSOCK((struct inode *)self->h_data))
				return HANDLE_TYPEKIND_MFILE_SOCKETNODE;
			return HANDLE_TYPEKIND_MFILE_INODE;
		}
		break;

#ifndef CONFIG_USE_NEW_FS
	case HANDLE_TYPE_BLKDEV:
		if (blkdev_ispart((struct block_device *)self->h_data))
			return HANDLE_TYPEKIND_BLKDEV_PARTITION;
		return HANDLE_TYPEKIND_BLKDEV_DRIVEROOT;
		break;

	case HANDLE_TYPE_CHRDEV: {
		struct chrdev *me;
		me = (struct chrdev *)self;
		if (chrdev_istty(me)) {
			if (ttydev_isptyslave((struct ttydev *)me))
				return HANDLE_TYPEKIND_CHRDEV_PTY;
			if (ttydev_ismktty((struct ttydev *)me))
				return HANDLE_TYPEKIND_CHRDEV_TTY;
			return HANDLE_TYPEKIND_CHRDEV_TTYBASE;
		}
		if (chrdev_iskbd(me))
			return HANDLE_TYPEKIND_CHRDEV_KEYBOARD;
		if (chrdev_ismouse(me))
			return HANDLE_TYPEKIND_CHRDEV_MOUSE;
	}	break;
#endif /* !CONFIG_USE_NEW_FS */

	case HANDLE_TYPE_PATH: {
		struct path *me = (struct path *)self->h_data;
#ifdef CONFIG_USE_NEW_FS
		if (path_isroot(me))
			return HANDLE_TYPEKIND_PATH_VFSROOT;
#else /* CONFIG_USE_NEW_FS */
		if (me->p_vfs == me)
			return HANDLE_TYPEKIND_PATH_VFSROOT;
#endif /* !CONFIG_USE_NEW_FS */
	}	break;

	case HANDLE_TYPE_MODULE: {
		struct module *me = (struct module *)self->h_data;
		if (module_isdriver(me))
			return HANDLE_TYPEKIND_MODULE_DRIVER;
	}	break;

	case HANDLE_TYPE_MODULE_SECTION: {
		struct module_section *me = (struct module_section *)self->h_data;
		struct module *mod        = me->ms_module;
		if (module_isdriver(mod))
			return HANDLE_TYPEKIND_MODULE_SECTION_DRIVER;
	}	break;

	default: break;
	}
	return HANDLE_TYPEKIND_GENERIC;
}


#ifndef CONFIG_USE_NEW_FS
LOCAL WUNUSED NONNULL((1, 2)) bool KCALL
chrdev_datasize(struct chrdev *__restrict self,
                pos_t *__restrict presult) {
	struct stat st;
	if (!self->cd_type.ct_stat)
		return false;
	/* Check if the stat-operator fills in the size-field. */
	st.st_size = UINT64_C(0xaaaaaaaaaaaaaaaa);
	(*self->cd_type.ct_stat)(self, &st);
	if (st.st_size == UINT64_C(0xaaaaaaaaaaaaaaaa)) {
		st.st_size = UINT64_C(0x5555555555555555);
		(*self->cd_type.ct_stat)(self, &st);
		if (st.st_size == UINT64_C(0x5555555555555555))
			return false; /* The size-field isn't filled in. */
	}
	*presult = (pos_t)st.st_size;
	return true;
}
#endif /* !CONFIG_USE_NEW_FS */

#ifdef CONFIG_USE_NEW_FS
LOCAL WUNUSED NONNULL((1)) pos_t KCALL
mfile_datasize(struct mfile *__restrict self) {
	pos_t result;
	result = (pos_t)atomic64_read(&self->mf_filesize);
	if (mfile_isanon(self))
		result = 0;
	if (self->mf_ops->mo_stream &&
	    self->mf_ops->mo_stream->mso_stat) {
		struct stat st;
		st.st_size = (typeof(st.st_size))result;
		(*self->mf_ops->mo_stream->mso_stat)(self, &st);
		result = (pos_t)st.st_size;
	}
	return result;
}
#endif /* CONFIG_USE_NEW_FS */


/* Try to determine the effective data size of the given handle (as returned by `FIOQSIZE')
 * @return: true:  The data size was stored in `*presult'.
 * @return: false: The data size could not be determined. */
PUBLIC WUNUSED NONNULL((1, 2)) bool KCALL
handle_datasize(struct handle const *__restrict self,
                pos_t *__restrict presult) {
	pos_t value;
	switch (self->h_type) {

	case HANDLE_TYPE_MFILE: {
#ifdef CONFIG_USE_NEW_FS
		struct mfile *me;
		me    = (struct mfile *)self->h_data;
		value = mfile_datasize(me);
#else /* CONFIG_USE_NEW_FS */
		struct inode *me;
		me = (struct inode *)self->h_data;
		if (!vm_datablock_isinode(me))
			goto badtype;
		inode_loadattr(me);
#ifdef CONFIG_ATOMIC64_SUPPORT_ALWAYS
		value = ATOMIC_READ(me->i_filesize);
#else /* CONFIG_ATOMIC64_SUPPORT_ALWAYS */
		{
			SCOPED_READLOCK(me);
			value = me->i_filesize;
		}
#endif /* !CONFIG_ATOMIC64_SUPPORT_ALWAYS */
#endif /* !CONFIG_USE_NEW_FS */
	}	break;

#ifndef CONFIG_USE_NEW_FS
	case HANDLE_TYPE_BLKDEV: {
		struct blkdev *me;
		me = (struct blkdev *)self->h_data;
		value = ((pos_t)me->bd_sector_count *
		         (pos_t)me->bd_sector_size);
	}	break;

	case HANDLE_TYPE_CHRDEV: {
		struct chrdev *me;
		me = (struct chrdev *)self->h_data;
		return chrdev_datasize(me, presult);
	}	break;
#endif /* !CONFIG_USE_NEW_FS */

	case HANDLE_TYPE_FDIRENT: {
		struct fdirent *me;
		me = (struct fdirent *)self->h_data;
		value = (pos_t)me->de_namelen;
	}	break;

	case HANDLE_TYPE_FILEHANDLE:
	case HANDLE_TYPE_DIRHANDLE: {
		struct filehandle *me;
		me = (struct filehandle *)self->h_data;
#ifdef CONFIG_USE_NEW_FS
		value = mfile_datasize(me->fh_file);
#else /* CONFIG_USE_NEW_FS */
		inode_loadattr(me->f_node);
#ifdef CONFIG_ATOMIC64_SUPPORT_ALWAYS
		value = ATOMIC_READ(me->f_node->i_filesize);
#else /* CONFIG_ATOMIC64_SUPPORT_ALWAYS */
		{
			SCOPED_READLOCK(me->f_node);
			value = me->f_node->i_filesize;
		}
#endif /* !CONFIG_ATOMIC64_SUPPORT_ALWAYS */
#endif /* !CONFIG_USE_NEW_FS */
	}	break;

	case HANDLE_TYPE_PATH: {
#ifdef CONFIG_USE_NEW_FS
		struct path *me;
		me    = (struct path *)self->h_data;
		value = mfile_datasize(me->p_dir);
#else /* CONFIG_USE_NEW_FS */
		struct path *me;
		REF struct inode *node;
		me = (struct path *)self->h_data;
		sync_read(me);
		node = (REF struct inode *)incref(me->p_inode);
		sync_endread(me);
		FINALLY_DECREF_UNLIKELY(node);
		inode_loadattr(node);
#ifdef CONFIG_ATOMIC64_SUPPORT_ALWAYS
		value = ATOMIC_READ(node->i_filesize);
#else /* CONFIG_ATOMIC64_SUPPORT_ALWAYS */
		{
			SCOPED_READLOCK(node);
			value = node->i_filesize;
		}
#endif /* !CONFIG_ATOMIC64_SUPPORT_ALWAYS */
#endif /* !CONFIG_USE_NEW_FS */
	}	break;

	case HANDLE_TYPE_MMAN:
		value = ((pos_t)(uintptr_t)-1) + 1;
		break;

	case HANDLE_TYPE_MODULE: {
		struct driver *me;
		me = (struct driver *)self->h_data;
		value = (pos_t)(me->md_loadmax - me->md_loadmin) + 1;
	}	break;

	case HANDLE_TYPE_PIPE: {
		struct pipe *me;
		me    = (struct pipe *)self->h_data;
		value = (pos_t)ATOMIC_READ(me->p_buffer.rb_avail);
	}	break;

	case HANDLE_TYPE_PIPE_READER:
	case HANDLE_TYPE_PIPE_WRITER: {
		struct pipe_reader *me;
		me    = (struct pipe_reader *)self->h_data;
		value = (pos_t)ATOMIC_READ(me->pr_pipe->p_buffer.rb_avail);
	}	break;

	case HANDLE_TYPE_PIDNS: {
		struct pidns *me;
		me    = (struct pidns *)self->h_data;
		value = (pos_t)ATOMIC_READ(me->pn_size);
	}	break;

	case HANDLE_TYPE_DRIVER_LOADLIST: {
		struct driver_loadlist *me;
		me    = (struct driver_loadlist *)self->h_data;
		value = (pos_t)me->dll_count;
	}	break;

	case HANDLE_TYPE_FIFOHANDLE: {
		struct fifohandle *me;
		me    = (struct fifohandle *)self->h_data;
#ifdef CONFIG_USE_NEW_FS
		value = (pos_t)ATOMIC_READ(me->fu_fifo->ff_buffer.rb_avail);
#else /* CONFIG_USE_NEW_FS */
		value = (pos_t)ATOMIC_READ(me->fu_fifo->f_fifo.ff_buffer.rb_avail);
#endif /* !CONFIG_USE_NEW_FS */
	}	break;

	default:
#ifndef CONFIG_USE_NEW_FS
badtype:
#endif /* !CONFIG_USE_NEW_FS */
		return false;
	}
	*presult = value;
	return true;
}

PRIVATE ATTR_COLD ATTR_NOINLINE ATTR_NORETURN void KCALL
throw_invalid_handle_type(struct handle const *__restrict self,
                          uintptr_half_t wanted_type,
                          uintptr_half_t wanted_kind)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	THROW(E_INVALID_HANDLE_FILETYPE,
	      /* fd:                 */ 0, /* Filled in the caller */
	      /* needed_handle_type: */ wanted_type,
	      /* actual_handle_type: */ self->h_type,
	      /* needed_handle_kind: */ wanted_kind,
	      /* actual_handle_kind: */ handle_typekind(self));
}


PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF void *FCALL
handle_as(/*inherit(on_success)*/ REF struct handle const *__restrict self,
          uintptr_half_t wanted_type)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	REF void *result;
	/* Special case: The handle already has the correct typing */
	if (self->h_type == wanted_type)
		return self->h_data;
	result = _handle_tryas(*self, wanted_type);
	if likely(result) {
		handle_decref(*self);
		return result;
	}
	throw_invalid_handle_type(self, wanted_type, HANDLE_TYPEKIND_GENERIC);
}


/* Complete a thrown exception, inherit a reference to
 * `hnd', and  rethrow the  already thrown  exception. */
PRIVATE ATTR_COLD ATTR_NOINLINE ATTR_NORETURN void FCALL
handle_getas_complete_except(unsigned int fd)
		THROWS(...) {
	if (was_thrown(E_INVALID_HANDLE_FILETYPE)) {
		if (!PERTASK_TEST(this_exception_args.e_invalid_handle.ih_fd))
			PERTASK_SET(this_exception_args.e_invalid_handle.ih_fd, fd);
	}
	RETHROW();
}



/* Directly translate handlers to references to objects of specific types. */
PUBLIC ATTR_RETNONNULL WUNUSED REF void *FCALL
handle_getas(unsigned int fd, uintptr_half_t wanted_type)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE,
		       E_INVALID_HANDLE_FILETYPE) {
	REF struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as(hnd, wanted_type);
	} EXCEPT {
		decref_unlikely(hnd);
		handle_getas_complete_except(fd);
	}
}

PUBLIC ATTR_RETNONNULL WUNUSED REF struct inode *FCALL
handle_get_fnode(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE,
		       E_INVALID_HANDLE_FILETYPE) {
	REF struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_fnode(hnd);
	} EXCEPT {
		decref_unlikely(hnd);
		handle_getas_complete_except(fd);
	}
}

PUBLIC ATTR_RETNONNULL WUNUSED REF struct regular_node *FCALL
handle_get_regnode(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE,
		       E_INVALID_HANDLE_FILETYPE) {
	REF struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_regnode(&hnd);
	} EXCEPT {
		decref_unlikely(hnd);
		handle_getas_complete_except(fd);
	}
}

PUBLIC ATTR_RETNONNULL WUNUSED REF struct directory_node *FCALL
handle_get_dirnode(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE,
		       E_INVALID_HANDLE_FILETYPE) {
	REF struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_dirnode(&hnd);
	} EXCEPT {
		decref_unlikely(hnd);
		handle_getas_complete_except(fd);
	}
}

PUBLIC ATTR_RETNONNULL WUNUSED REF struct superblock *FCALL
handle_get_super(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE,
		       E_INVALID_HANDLE_FILETYPE) {
	REF struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_super(&hnd);
	} EXCEPT {
		decref_unlikely(hnd);
		handle_getas_complete_except(fd);
	}
}

PUBLIC ATTR_RETNONNULL WUNUSED REF struct superblock *FCALL
handle_get_super_relaxed(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE,
		       E_INVALID_HANDLE_FILETYPE) {
	REF struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_super_relaxed(&hnd);
	} EXCEPT {
		decref_unlikely(hnd);
		handle_getas_complete_except(fd);
	}
}

/* @throw: E_PROCESS_EXITED: `fd' belongs to a task that is no longer allocated. */
PUBLIC ATTR_RETNONNULL WUNUSED REF struct task *FCALL
handle_get_task(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE,
		       E_INVALID_HANDLE_FILETYPE, E_PROCESS_EXITED) {
	REF struct handle hnd;
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
		decref_unlikely(hnd);
		handle_getas_complete_except(fd);
	}
}



/* Extended handle converted functions */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct inode *FCALL
handle_as_fnode(/*inherit(on_success)*/ REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	REF struct inode *result;
	/* Special case: The handle already has the correct typing */
	if (self->h_type == HANDLE_TYPE_MFILE) {
		result = (REF struct inode *)self->h_data;
		if likely(vm_datablock_isinode(result))
			return result; /* inherit */
	} else {
		result = (REF struct inode *)_handle_tryas(*self, HANDLE_TYPE_MFILE);
		if likely(result) {
			if likely(vm_datablock_isinode(result)) {
				handle_decref(*self); /* inherit: on_success */
				return result;
			}
			decref_unlikely(result);
		}
	}
	throw_invalid_handle_type(self,
	                          HANDLE_TYPE_MFILE,
	                          HANDLE_TYPEKIND_MFILE_INODE);
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct regular_node *FCALL
handle_as_regnode(/*inherit(on_success)*/ REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	REF struct regular_node *result;
	/* Special case: The handle already has the correct typing */
	if (self->h_type == HANDLE_TYPE_MFILE) {
		result = (REF struct regular_node *)self->h_data;
		if likely(vm_datablock_isinode(result) && INODE_ISREG(result))
			return result; /* inherit */
	} else {
		result = (REF struct regular_node *)_handle_tryas(*self, HANDLE_TYPE_MFILE);
		if likely(result) {
			if likely(vm_datablock_isinode(result) && INODE_ISREG(result)) {
				handle_decref(*self); /* inherit: on_success */
				return result;
			}
			decref_unlikely(result);
		}
	}
	throw_invalid_handle_type(self,
	                          HANDLE_TYPE_MFILE,
	                          HANDLE_TYPEKIND_MFILE_REGULARNODE);
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct directory_node *FCALL
handle_as_dirnode(/*inherit(on_success)*/ REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	REF struct directory_node *result;
	/* Special case: The handle already has the correct typing */
	if (self->h_type == HANDLE_TYPE_MFILE) {
		result = (REF struct directory_node *)self->h_data;
		if likely(vm_datablock_isinode(result) && INODE_ISDIR(result))
			return result; /* inherit */
	} else {
		result = (REF struct directory_node *)_handle_tryas(*self, HANDLE_TYPE_MFILE);
		if likely(result) {
			if likely(vm_datablock_isinode(result) && INODE_ISDIR(result)) {
				handle_decref(*self); /* inherit: on_success */
				return result;
			}
			decref_unlikely(result);
		}
	}
	throw_invalid_handle_type(self,
	                          HANDLE_TYPE_MFILE,
	                          HANDLE_TYPEKIND_MFILE_DIRECTORY);
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct superblock *FCALL
handle_as_super(/*inherit(on_success)*/ REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
#ifdef CONFIG_USE_NEW_FS
	/* Special case: The handle already has the correct typing */
	if (self->h_type == HANDLE_TYPE_MFILE) {
		struct mfile *mf = (struct mfile *)self->h_data;
		if (mfile_issuper(mf))
			return mfile_assuper(mf); /* inherit */
	} else {
		REF struct mfile *result;
		result = (REF struct mfile *)_handle_tryas(*self, HANDLE_TYPE_MFILE);
		if likely(result) {
			if (mfile_issuper(result)) {
				handle_decref(*self); /* inherit: on_success */
				return mfile_assuper(result);
			}
			decref_unlikely(result);
		}
	}
#else /* CONFIG_USE_NEW_FS */
	REF struct superblock *result;
	/* Special case: The handle already has the correct typing */
	if (self->h_type == HANDLE_TYPE_MFILE) {
		result = (REF struct superblock *)self->h_data;
		if likely(vm_datablock_isinode(result) && INODE_ISSUPER(result))
			return result; /* inherit */
	} else {
		result = (REF struct superblock *)_handle_tryas(*self, HANDLE_TYPE_MFILE);
		if likely(result) {
			if likely(vm_datablock_isinode(result) && INODE_ISSUPER(result)) {
				handle_decref(*self); /* inherit: on_success */
				return result;
			}
			decref_unlikely(result);
		}
	}
#endif /* !CONFIG_USE_NEW_FS */
	throw_invalid_handle_type(self,
	                          HANDLE_TYPE_MFILE,
	                          HANDLE_TYPEKIND_MFILE_SUPERBLOCK);
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct superblock *FCALL
handle_as_super_relaxed(/*inherit(on_success)*/ REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	REF struct superblock *result;
	REF struct inode *ino;
	/* Special case: The handle already has the correct typing */
	if (self->h_type == HANDLE_TYPE_MFILE) {
		ino = (REF struct inode *)self->h_data;
		if likely(vm_datablock_isinode(ino)) {
			result = (REF struct superblock *)incref(ino->i_super);
			decref_unlikely(ino); /* inherit: on_success */
			return result;
		}
	} else {
		ino = (REF struct inode *)_handle_tryas(*self, HANDLE_TYPE_MFILE);
		if likely(ino) {
			if likely(vm_datablock_isinode(ino)) {
				result = (REF struct superblock *)incref(ino->i_super);
				decref_unlikely(ino);
				handle_decref(*self); /* inherit: on_success */
				return result;
			}
			decref_unlikely(ino);
		}
	}
	throw_invalid_handle_type(self,
	                          HANDLE_TYPE_MFILE,
	                          HANDLE_TYPEKIND_MFILE_SUPERBLOCK);
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct symlink_node *FCALL
handle_as_lnknode(/*inherit(on_success)*/ REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	REF struct symlink_node *result;
	/* Special case: The handle already has the correct typing */
	if (self->h_type == HANDLE_TYPE_MFILE) {
		result = (REF struct symlink_node *)self->h_data;
		if likely(vm_datablock_isinode(result) && INODE_ISLNK(result))
			return result; /* inherit */
	} else {
		result = (REF struct symlink_node *)_handle_tryas(*self, HANDLE_TYPE_MFILE);
		if likely(result) {
			if likely(vm_datablock_isinode(result) && INODE_ISLNK(result)) {
				handle_decref(*self); /* inherit: on_success */
				return result;
			}
			decref_unlikely(result);
		}
	}
	throw_invalid_handle_type(self,
	                          HANDLE_TYPE_MFILE,
	                          HANDLE_TYPEKIND_MFILE_SYMLINKNODE);
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fifo_node *FCALL
handle_as_fifonode(/*inherit(on_success)*/ REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	REF struct fifo_node *result;
	/* Special case: The handle already has the correct typing */
	if (self->h_type == HANDLE_TYPE_MFILE) {
		result = (REF struct fifo_node *)self->h_data;
		if likely(vm_datablock_isinode(result) && INODE_ISFIFO(result))
			return result; /* inherit */
	} else {
		result = (REF struct fifo_node *)_handle_tryas(*self, HANDLE_TYPE_MFILE);
		if likely(result) {
			if likely(vm_datablock_isinode(result) && INODE_ISFIFO(result)) {
				handle_decref(*self); /* inherit: on_success */
				return result;
			}
			decref_unlikely(result);
		}
	}
	throw_invalid_handle_type(self,
	                          HANDLE_TYPE_MFILE,
	                          HANDLE_TYPEKIND_MFILE_FIFONODE);
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct socket_node *FCALL
handle_as_socketnode(/*inherit(on_success)*/ REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	REF struct socket_node *result;
	/* Special case: The handle already has the correct typing */
	if (self->h_type == HANDLE_TYPE_MFILE) {
		result = (REF struct socket_node *)self->h_data;
		if likely(vm_datablock_isinode(result) && INODE_ISSOCK(result))
			return result; /* inherit */
	} else {
		result = (REF struct socket_node *)_handle_tryas(*self, HANDLE_TYPE_MFILE);
		if likely(result) {
			if likely(vm_datablock_isinode(result) && INODE_ISSOCK(result)) {
				handle_decref(*self); /* inherit: on_success */
				return result;
			}
			decref_unlikely(result);
		}
	}
	throw_invalid_handle_type(self,
	                          HANDLE_TYPE_MFILE,
	                          HANDLE_TYPEKIND_MFILE_SOCKETNODE);
}

/* @throw: E_PROCESS_EXITED: `fd' belongs to a task that is no longer allocated. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct task *FCALL
handle_as_task(/*inherit(on_success)*/ REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE, E_PROCESS_EXITED) {
	/* Special case: The handle already has the correct typing */
	if (self->h_type == HANDLE_TYPE_TASK) {
		REF struct task *result;
		struct taskpid *tpid;
		tpid   = (REF struct taskpid *)self->h_data;
		result = taskpid_gettask_srch(tpid);
		decref_unlikely(tpid); /* inherit: on_success */
		return result;
	} else {
		REF struct taskpid *tpid;
		tpid = (REF struct taskpid *)_handle_tryas(*self, HANDLE_TYPE_TASK);
		if likely(tpid) {
			REF struct task *result;
			{
				FINALLY_DECREF_UNLIKELY(tpid);
				result = taskpid_gettask_srch(tpid);
			}
			decref_unlikely(self); /* inherit: on_success */
			return result;
		}
	}
	throw_invalid_handle_type(self,
	                          HANDLE_TYPE_TASK,
	                          HANDLE_TYPEKIND_GENERIC);
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_USER_HANDLE_UTILITY_C */
