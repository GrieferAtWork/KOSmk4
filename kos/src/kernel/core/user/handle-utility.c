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
#include <dev/mouse.h>
#include <dev/pty.h>
#include <dev/tty.h>
#include <dev/ttybase.h>
#include <fs/fifo.h>
#include <fs/file.h>
#include <fs/node.h>
#include <fs/ramfs.h>
#include <fs/special-node.h>
#include <fs/vfs.h>
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
				return HANDLE_TYPEKIND_DATABLOCK_SUPERBLOCK;
			if (INODE_ISREG((struct inode *)self->h_data))
				return HANDLE_TYPEKIND_DATABLOCK_REGULARNODE;
			if (INODE_ISDIR((struct inode *)self->h_data))
				return HANDLE_TYPEKIND_DATABLOCK_DIRECTORY;
			if (INODE_ISLNK((struct inode *)self->h_data))
				return HANDLE_TYPEKIND_DATABLOCK_SYMLINKNODE;
			if (INODE_ISFIFO((struct inode *)self->h_data))
				return HANDLE_TYPEKIND_DATABLOCK_FIFONODE;
			if (INODE_ISSOCK((struct inode *)self->h_data))
				return HANDLE_TYPEKIND_DATABLOCK_SOCKETNODE;
			return HANDLE_TYPEKIND_DATABLOCK_INODE;
		}
		break;

	case HANDLE_TYPE_BLOCKDEVICE:
		if (block_device_ispartition((struct block_device *)self->h_data))
			return HANDLE_TYPEKIND_BLOCKDEVICE_PARTITION;
		return HANDLE_TYPEKIND_BLOCKDEVICE_DRIVEROOT;
		break;

	case HANDLE_TYPE_CHARACTERDEVICE: {
		struct character_device *me;
		me = (struct character_device *)self;
		if (character_device_isattybase(me)) {
			if (ttybase_isapty((struct ttybase_device *)me))
				return HANDLE_TYPEKIND_CHARACTERDEVICE_PTY;
			if (ttybase_isatty((struct ttybase_device *)me))
				return HANDLE_TYPEKIND_CHARACTERDEVICE_TTY;
			return HANDLE_TYPEKIND_CHARACTERDEVICE_TTYBASE;
		}
		if (character_device_isakeyboard(me))
			return HANDLE_TYPEKIND_CHARACTERDEVICE_KEYBOARD;
		if (character_device_isamouse(me))
			return HANDLE_TYPEKIND_CHARACTERDEVICE_MOUSE;
	}	break;

	case HANDLE_TYPE_PATH: {
		struct path *me = (struct path *)self->h_data;
		if (me->p_vfs == me)
			return HANDLE_TYPEKIND_PATH_VFSROOT;
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


LOCAL WUNUSED NONNULL((1, 2)) bool KCALL
character_device_datasize(struct character_device *__restrict self,
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


/* Try to determine the effective data size of the given handle (as returned by `FIOQSIZE')
 * @return: true:  The data size was stored in `*presult'.
 * @return: false: The data size could not be determined. */
PUBLIC WUNUSED NONNULL((1, 2)) bool KCALL
handle_datasize(struct handle const *__restrict self,
                pos_t *__restrict presult) {
	pos_t value;
	switch (self->h_type) {

	case HANDLE_TYPE_MFILE: {
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
	}	break;

	case HANDLE_TYPE_BLOCKDEVICE: {
		struct basic_block_device *me;
		me = (struct basic_block_device *)self->h_data;
		value = ((pos_t)me->bd_sector_count *
		         (pos_t)me->bd_sector_size);
	}	break;

	case HANDLE_TYPE_CHARACTERDEVICE: {
		struct character_device *me;
		me = (struct character_device *)self->h_data;
		return character_device_datasize(me, presult);
	}	break;

	case HANDLE_TYPE_FDIRENT: {
		struct fdirent *me;
		me = (struct fdirent *)self->h_data;
		value = (pos_t)me->de_namelen;
	}	break;

	case HANDLE_TYPE_FILEHANDLE:
	case HANDLE_TYPE_DIRHANDLE: {
		struct filehandle *me;
		me = (struct filehandle *)self->h_data;
		inode_loadattr(me->f_node);
#ifdef CONFIG_ATOMIC64_SUPPORT_ALWAYS
		value = ATOMIC_READ(me->f_node->i_filesize);
#else /* CONFIG_ATOMIC64_SUPPORT_ALWAYS */
		{
			SCOPED_READLOCK(me->f_node);
			value = me->f_node->i_filesize;
		}
#endif /* !CONFIG_ATOMIC64_SUPPORT_ALWAYS */
	}	break;

	case HANDLE_TYPE_PATH: {
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

	case HANDLE_TYPE_FIFO_USER: {
		struct fifo_user *me;
		me    = (struct fifo_user *)self->h_data;
		value = (pos_t)ATOMIC_READ(me->fu_fifo->f_fifo.ff_buffer.rb_avail);
	}	break;

	default:
badtype:
		return false;
	}
	*presult = value;
	return true;
}

/* Print the text that should result from `readlink("/proc/[pid]/fd/[fdno]")' */
PUBLIC NONNULL((1, 2)) ssize_t KCALL
handle_print(struct handle const *__restrict self,
             pformatprinter printer, void *arg) {
	size_t result;
	switch (self->h_type) {

	case HANDLE_TYPE_MFILE: {
		struct mfile *b = (struct mfile *)self->h_data;
		if (vm_datablock_isinode(b)) {
			result = format_printf(printer, arg,
			                       "anon_inode:[inode:%" PRIuN(__SIZEOF_INO_T__) "]",
			                       ((struct inode *)b)->i_fileino);
		} else {
			result = format_printf(printer, arg,
			                       "anon_inode:[datablock:%" PRIuPTR "]",
			                       skew_kernel_pointer(b));
		}
	}	break;

	case HANDLE_TYPE_BLOCKDEVICE:
	case HANDLE_TYPE_CHARACTERDEVICE: {
		REF struct path *mount;
		char const *devname;
		if (self->h_type == HANDLE_TYPE_CHARACTERDEVICE) {
			struct character_device *me;
			me      = (struct character_device *)self->h_data;
			devname = me->cd_name;
		} else {
			struct block_device *me;
			me      = (struct block_device *)self->h_data;
			devname = me->bd_name;
		}
		mount = superblock_getmountloc(&devfs, THIS_VFS);
		if unlikely(!mount) {
			result = format_printf(printer, arg, "devfs:%s", devname);
		} else {
			FINALLY_DECREF_UNLIKELY(mount);
			result = path_printent(mount,
			                       devname,
			                       strlen(devname),
			                       printer, arg);
		}
	}	break;

	case HANDLE_TYPE_FDIRENT: {
		struct fdirent *ent = (struct fdirent *)self->h_data;
		result = format_printf(printer, arg, "anon_inode:[dirent:%$s]",
		                       ent->de_namelen, ent->de_name);
	}	break;

	case HANDLE_TYPE_FILEHANDLE: {
		struct filehandle *f = (struct filehandle *)self->h_data;
		if (f->f_path && f->f_dirent) {
			result = path_printent(f->f_path,
			                       f->f_dirent->de_name,
			                       f->f_dirent->de_namelen,
			                       printer, arg);
		} else {
			result = format_printf(printer, arg,
			                       "anon_inode:[file:inode:%" PRIuN(__SIZEOF_INO_T__) "]",
			                       f->f_node->i_fileino);
		}
	}	break;

	case HANDLE_TYPE_DIRHANDLE: {
		struct dirhandle *f = (struct dirhandle *)self->h_data;
		if (f->d_path && f->d_dirent) {
			result = path_printent(f->d_path,
			                       f->d_dirent->de_name,
			                       f->d_dirent->de_namelen,
			                       printer, arg);
		} else {
			result = format_printf(printer, arg,
			                       "anon_inode:[dirhandle:"
			                       "inode:%" PRIuN(__SIZEOF_INO_T__) "]",
			                       f->d_node->i_fileino);
		}
	}	break;

	case HANDLE_TYPE_PATH: {
		struct path *p = (struct path *)self->h_data;
		result = path_print(p, printer, arg);
	}	break;

	case HANDLE_TYPE_FS: {
		struct fs *f = (struct fs *)self->h_data;
		result = format_printf(printer, arg,
		                       "anon_inode:[fs:%" PRIuPTR "]",
		                       skew_kernel_pointer(f));
	}	break;

	case HANDLE_TYPE_MMAN: {
		struct mman *mm = (struct mman *)self->h_data;
		result = format_printf(printer, arg,
		                       "anon_inode:[mman:%" PRIuPTR "]",
		                       skew_kernel_pointer(mm));
	}	break;

	case HANDLE_TYPE_TASK: {
		struct taskpid *t = (struct taskpid *)self->h_data;
		result = format_printf(printer, arg,
		                       "anon_inode:[task:%" PRIuN(__SIZEOF_PID_T__) "]",
		                       taskpid_getpid_s(t));
	}	break;

	case HANDLE_TYPE_PIPE: {
		struct pipe *p = (struct pipe *)self->h_data;
		result = format_printf(printer, arg,
		                       "anon_inode:[pipe:%" PRIuPTR "]",
		                       skew_kernel_pointer(p));
	}	break;

	case HANDLE_TYPE_PIPE_READER: {
		struct pipe_reader *p = (struct pipe_reader *)self->h_data;
		result = format_printf(printer, arg,
		                       "anon_inode:[reader:pipe:%" PRIuPTR "]",
		                       skew_kernel_pointer(p->pr_pipe));
	}	break;

	case HANDLE_TYPE_PIPE_WRITER: {
		struct pipe_writer *p = (struct pipe_writer *)self->h_data;
		result = format_printf(printer, arg,
		                       "anon_inode:[writer:pipe:%" PRIuPTR "]",
		                       skew_kernel_pointer(p->pw_pipe));
	}	break;

	case HANDLE_TYPE_FIFO_USER: {
		struct fifo_user *f = (struct fifo_user *)self->h_data;
		if (f->fu_path && f->fu_dirent) {
			result = path_printent(f->fu_path,
			                       f->fu_dirent->de_name,
			                       f->fu_dirent->de_namelen,
			                       printer, arg);
		} else {
			result = format_printf(printer, arg,
			                       "anon_inode:[%s:named_pipe:%" PRIuN(__SIZEOF_INO_T__) "]",
			                       f->fu_accmode == IO_RDONLY
			                       ? "reader"
			                       : f->fu_accmode == IO_WRONLY
			                         ? "writer"
			                         : "reader+writer",
			                       f->fu_fifo->i_fileino);
		}
	}	break;

	case HANDLE_TYPE_PIDNS: {
		struct pidns *ns = (struct pidns *)self->h_data;
		result = format_printf(printer, arg,
		                       "anon_inode:[pidns:%" PRIuPTR "]",
		                       skew_kernel_pointer(ns));
	}	break;

	case HANDLE_TYPE_EVENTFD_FENCE: {
		struct eventfd *efd = (struct eventfd *)self->h_data;
		result = format_printf(printer, arg,
		                       "anon_inode:[eventfd:fence:%" PRIuPTR "]",
		                       skew_kernel_pointer(efd));
	}	break;

	case HANDLE_TYPE_EVENTFD_SEMA: {
		struct eventfd *efd = (struct eventfd *)self->h_data;
		result = format_printf(printer, arg,
		                       "anon_inode:[eventfd:semaphore:%" PRIuPTR "]",
		                       skew_kernel_pointer(efd));
	}	break;

	case HANDLE_TYPE_SIGNALFD: {
		struct signalfd *sfd = (struct signalfd *)self->h_data;
		result = format_printf(printer, arg,
		                       "anon_inode:[signalfd:%" PRIuPTR "]",
		                       skew_kernel_pointer(sfd));
	}	break;

	case HANDLE_TYPE_MODULE: {
		struct module *mod = (struct module *)self->h_data;
		static char const prefix[] = "anon_inode:[module:";
		result = (*printer)(arg, prefix, COMPILER_STRLEN(prefix));
		if likely(result >= 0) {
			ssize_t temp;
			temp = module_haspath_or_name(mod)
			       ? module_printpath_or_name(mod, printer, arg)
			       : (*printer)(arg, "?", 1);
			if unlikely(temp < 0)
				return temp;
			result += temp;
			temp = (*printer)(arg, "]", 1);
			if unlikely(temp < 0)
				return temp;
			result += temp;
		}
	}	break;

	case HANDLE_TYPE_MODULE_SECTION: {
		struct driver_section *sect;
		char const *name;
		REF struct module *mod;
		name = NULL;
		sect = (struct driver_section *)self->h_data;
		mod  = sect->ms_module;
		if (tryincref(mod))
			name = module_section_getname(sect);
		FINALLY_DECREF_UNLIKELY(mod);
		if (!name)
			name = "?";
		result = format_printf(printer, arg,
		                       "anon_inode:[module_section:%s]",
		                       name);
	}	break;

	case HANDLE_TYPE_DRIVER_LOADLIST: {
		struct driver_state *st = (struct driver_state *)self->h_data;
		result = format_printf(printer, arg,
		                       "anon_inode:[driver_state:%" PRIuPTR "]",
		                       skew_kernel_pointer(st));
	}	break;

	default:
		result = format_printf(printer, arg, "anon_inode:[%s:%" PRIuPTR "]",
		                       handle_typename(*self),
		                       skew_kernel_pointer(self->h_data));
		break;
	}
	return result;
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
		handle_getas_complete_except(fd);
	}
}

PUBLIC ATTR_RETNONNULL WUNUSED REF struct inode *FCALL
handle_get_inode(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE,
		       E_INVALID_HANDLE_FILETYPE) {
	REF struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_inode(hnd);
	} EXCEPT {
		handle_getas_complete_except(fd);
	}
}

PUBLIC ATTR_RETNONNULL WUNUSED REF struct regular_node *FCALL
handle_get_regular_node(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE,
		       E_INVALID_HANDLE_FILETYPE) {
	REF struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_regular_node(&hnd);
	} EXCEPT {
		handle_getas_complete_except(fd);
	}
}

PUBLIC ATTR_RETNONNULL WUNUSED REF struct directory_node *FCALL
handle_get_directory_node(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE,
		       E_INVALID_HANDLE_FILETYPE) {
	REF struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_directory_node(&hnd);
	} EXCEPT {
		handle_getas_complete_except(fd);
	}
}

PUBLIC ATTR_RETNONNULL WUNUSED REF struct superblock *FCALL
handle_get_superblock(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE,
		       E_INVALID_HANDLE_FILETYPE) {
	REF struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_superblock(&hnd);
	} EXCEPT {
		handle_getas_complete_except(fd);
	}
}

PUBLIC ATTR_RETNONNULL WUNUSED REF struct superblock *FCALL
handle_get_superblock_relaxed(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE,
		       E_INVALID_HANDLE_FILETYPE) {
	REF struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_superblock_relaxed(&hnd);
	} EXCEPT {
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
		handle_getas_complete_except(fd);
	}
}

PUBLIC ATTR_RETNONNULL WUNUSED REF struct vfs *FCALL
handle_get_vfs(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE,
		       E_INVALID_HANDLE_FILETYPE) {
	REF struct handle hnd;
	hnd = handle_lookup(fd);
	TRY {
		return handle_as_vfs(&hnd);
	} EXCEPT {
		handle_getas_complete_except(fd);
	}
}



/* Extended handle converted functions */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct inode *FCALL
handle_as_inode(/*inherit(on_success)*/ REF struct handle const *__restrict self)
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
	                          HANDLE_TYPEKIND_DATABLOCK_INODE);
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct regular_node *FCALL
handle_as_regular_node(/*inherit(on_success)*/ REF struct handle const *__restrict self)
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
	                          HANDLE_TYPEKIND_DATABLOCK_REGULARNODE);
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct directory_node *FCALL
handle_as_directory_node(/*inherit(on_success)*/ REF struct handle const *__restrict self)
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
	                          HANDLE_TYPEKIND_DATABLOCK_DIRECTORY);
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct superblock *FCALL
handle_as_superblock(/*inherit(on_success)*/ REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
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
	throw_invalid_handle_type(self,
	                          HANDLE_TYPE_MFILE,
	                          HANDLE_TYPEKIND_DATABLOCK_SUPERBLOCK);
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct superblock *FCALL
handle_as_superblock_relaxed(/*inherit(on_success)*/ REF struct handle const *__restrict self)
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
	                          HANDLE_TYPEKIND_DATABLOCK_SUPERBLOCK);
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct symlink_node *FCALL
handle_as_symlink_node(/*inherit(on_success)*/ REF struct handle const *__restrict self)
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
	                          HANDLE_TYPEKIND_DATABLOCK_SYMLINKNODE);
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fifo_node *FCALL
handle_as_fifo_node(/*inherit(on_success)*/ REF struct handle const *__restrict self)
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
	                          HANDLE_TYPEKIND_DATABLOCK_FIFONODE);
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct socket_node *FCALL
handle_as_socket_node(/*inherit(on_success)*/ REF struct handle const *__restrict self)
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
	                          HANDLE_TYPEKIND_DATABLOCK_SOCKETNODE);
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

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct vfs *FCALL
handle_as_vfs(/*inherit(on_success)*/ REF struct handle const *__restrict self)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	REF struct vfs *result;
	/* Special case: The handle already has the correct typing */
	if (self->h_type == HANDLE_TYPE_PATH) {
		result = (REF struct vfs *)self->h_data;
		if likely(result->p_vfs == result)
			return result; /* inherit */
	} else {
		result = (REF struct vfs *)_handle_tryas(*self, HANDLE_TYPE_PATH);
		if likely(result) {
			if likely(result->p_vfs == result) {
				decref_unlikely(self); /* inherit: on_success */
				return result;
			}
			decref_unlikely(result);
		}
	}
	throw_invalid_handle_type(self,
	                          HANDLE_TYPE_PATH,
	                          HANDLE_TYPEKIND_PATH_VFSROOT);
}




DECL_END

#endif /* !GUARD_KERNEL_SRC_USER_HANDLE_UTILITY_C */
