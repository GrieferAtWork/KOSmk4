/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_FD_UTILS_C
#define GUARD_KERNEL_SRC_FD_UTILS_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <dev/keyboard.h>
#include <dev/mktty.h>
#include <dev/mouse.h>
#include <dev/pty.h>
#include <dev/tty.h>
#include <kernel/except.h>
#include <kernel/fs/dirhandle.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/fifohandle.h>
#include <kernel/fs/fifonode.h>
#include <kernel/fs/filehandle.h>
#include <kernel/fs/lnknode.h>
#include <kernel/fs/node.h>
#include <kernel/fs/path.h>
#include <kernel/fs/regnode.h>
#include <kernel/fs/super.h>
#include <kernel/handle.h>
#include <kernel/mman/driver.h>
#include <kernel/mman/module.h>
#include <kernel/pipe.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/atomic64.h>
#include <sched/group.h>
#include <sched/rpc.h>
#include <sched/task.h>

#include <kos/except.h>
#include <sys/stat.h>

#include <assert.h>
#include <atomic.h>
#include <fcntl.h>
#include <format-printer.h>
#include <inttypes.h>
#include <stdint.h> /* UINT64_C */
#include <string.h>

DECL_BEGIN

PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) uintptr_half_t
NOTHROW(KCALL mfile_typekind)(struct mfile const *__restrict self) {
	if (mfile_isnode(self)) {
		struct fnode *node = mfile_asnode(self);
		/* TODO: With all of the subclasses that exist now, this really needs to be rethought! */
		if (fnode_issuper(node))
			return HANDLE_TYPEKIND_MFILE_FSUPER;
		if (fnode_isreg(node))
			return HANDLE_TYPEKIND_MFILE_FREGNODE;
		if (fnode_isdir(node))
			return HANDLE_TYPEKIND_MFILE_FDIRNODE;
		if (fnode_islnk(node))
			return HANDLE_TYPEKIND_MFILE_FLNKNODE;
		if (fnode_isfifo(node))
			return HANDLE_TYPEKIND_MFILE_FFIFONODE;
		if (fnode_issock(node))
			return HANDLE_TYPEKIND_MFILE_FSOCKNODE;
		return HANDLE_TYPEKIND_MFILE_FNODE;
	}
	return HANDLE_TYPEKIND_MFILE_GENERIC;
}

/* Returns the type-kind code for `self' (One of `HANDLE_TYPEKIND_*') */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) uintptr_half_t
NOTHROW(KCALL handle_typekind)(struct handle const *__restrict self) {
	switch (self->h_type) {

	case HANDLE_TYPE_MFILE:
		return mfile_typekind((struct mfile *)self->h_data);

	case HANDLE_TYPE_MODULE: {
		struct module *me = (struct module *)self->h_data;
		if (module_isdriver(me))
			return HANDLE_TYPEKIND_MODULE_DRIVER;
	}	break;

	default: break;
	}
	return HANDLE_TYPEKIND_GENERIC;
}


LOCAL WUNUSED NONNULL((1)) pos_t KCALL
mfile_datasize(struct mfile *__restrict self) {
	pos_t result;
	result = mfile_getsize(self);
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


/* Try to determine the effective data size of the given handle (as returned by `FIOQSIZE')
 * @return: true:  The data size was stored in `*presult'.
 * @return: false: The data size could not be determined. */
PUBLIC BLOCKING WUNUSED NONNULL((1, 2)) bool KCALL
handle_datasize(struct handle const *__restrict self,
                pos_t *__restrict presult) {
	pos_t value;
	switch (self->h_type) {

	case HANDLE_TYPE_MFILE: {
		struct mfile *me;
		me    = (struct mfile *)self->h_data;
		value = mfile_datasize(me);
	}	break;

	case HANDLE_TYPE_DIRENT: {
		struct fdirent *me;
		me    = (struct fdirent *)self->h_data;
		value = (pos_t)me->fd_namelen;
	}	break;

	case HANDLE_TYPE_FILEHANDLE:
	case HANDLE_TYPE_TEMPHANDLE: {
		struct filehandle *me;
		me = (struct filehandle *)self->h_data;
		value = mfile_datasize(me->fh_file);
	}	break;

	case HANDLE_TYPE_DIRHANDLE: {
		struct dirhandle *me;
		me = (struct dirhandle *)self->h_data;
		value = mfile_datasize(me->dh_enum.de_dir);
	}	break;

	case HANDLE_TYPE_PATH: {
		struct path *me;
		me    = (struct path *)self->h_data;
		value = mfile_datasize(me->p_dir);
	}	break;

	case HANDLE_TYPE_MODULE: {
		struct driver *me;
		me = (struct driver *)self->h_data;
		value = (pos_t)(me->md_loadmax - me->md_loadmin) + 1;
	}	break;

	case HANDLE_TYPE_PIPE: {
		struct pipe *me;
		me    = (struct pipe *)self->h_data;
		value = (pos_t)atomic_read(&me->p_buffer.rb_avail);
	}	break;

	case HANDLE_TYPE_PIPE_READER:
	case HANDLE_TYPE_PIPE_WRITER: {
		struct pipe_reader *me;
		me    = (struct pipe_reader *)self->h_data;
		value = (pos_t)atomic_read(&me->pr_pipe->p_buffer.rb_avail);
	}	break;

	case HANDLE_TYPE_DRIVER_LOADLIST: {
		struct driver_loadlist *me;
		me    = (struct driver_loadlist *)self->h_data;
		value = (pos_t)me->dll_count;
	}	break;

	case HANDLE_TYPE_FIFOHANDLE: {
		struct fifohandle *me;
		me    = (struct fifohandle *)self->h_data;
		value = (pos_t)atomic_read(&me->fu_fifo->ff_buffer.rb_avail);
	}	break;

	default:
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


PUBLIC BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1)) REF void *FCALL
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

PUBLIC BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1)) REF void *FCALL
handle_as_noinherit(struct handle const *__restrict self, uintptr_half_t wanted_type)
		THROWS(E_INVALID_HANDLE_FILETYPE) {
	REF void *result;
	/* Special case: The handle already has the correct typing */
	if (self->h_type == wanted_type) {
		handle_incref(*self);
		return self->h_data;
	}
	result = _handle_tryas(*self, wanted_type);
	if likely(result)
		return result;
	throw_invalid_handle_type(self, wanted_type, HANDLE_TYPEKIND_GENERIC);
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_FD_UTILS_C */
