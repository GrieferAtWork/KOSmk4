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
#ifndef GUARD_KERNEL_CORE_MEMORY_MMAN_DRIVER_HANDLE_C
#define GUARD_KERNEL_CORE_MEMORY_MMAN_DRIVER_HANDLE_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/except.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/mman/driver.h>
#include <kernel/user.h>
#include <sched/cred.h>

#include <hybrid/atomic.h>

#include <kos/except/reason/inval.h>
#include <kos/hop/module.h>

#include <string.h>

/* TODO: Re-design the driver HOP-system from scratch */

DECL_BEGIN

/* Driver-handle API */
DEFINE_HANDLE_REFCNT_FUNCTIONS_WITH_WEAKREF_SUPPORT(module, struct module);
DEFINE_HANDLE_REFCNT_FUNCTIONS(module_section, struct module_section);
DEFINE_HANDLE_REFCNT_FUNCTIONS(driver_loadlist, struct driver_loadlist);


PRIVATE NOBLOCK uintptr_t KCALL
hop_driver_getflags(struct driver *__restrict self)
		THROWS(...) {
	uintptr_t result = 0;
	if (driver_getfile(self) != NULL)
		result |= HOP_DRIVER_FLAG_HAS_FILE;
	if (self->d_eh_frame_start < self->d_eh_frame_end)
		result |= HOP_DRIVER_FLAG_HAS_EH_FRAME;
	if (self->d_dynsym_tab)
		result |= HOP_DRIVER_FLAG_HAS_DYNSYM;
	return result;
}

PRIVATE NONNULL((1)) syscall_slong_t KCALL
get_driver_string(USER CHECKED struct hop_driver_string *data,
                  char const *__restrict str, size_t str_len_with_nul)
		THROWS(...) {
	USER UNCHECKED char *buf;
	size_t buflen;
	buf    = data->ds_buf;
	buflen = data->ds_size;
	data->ds_size = str_len_with_nul * sizeof(char);
	COMPILER_BARRIER();
	validate_writable(buf, buflen);
	memcpy(buf, str, str_len_with_nul, sizeof(char));
	return 0;
}

PRIVATE NONNULL((1)) syscall_slong_t KCALL
get_driver_string0(USER UNCHECKED void *arg,
                   char const *__restrict str,
                   size_t str_len_with_nul)
		THROWS(...) {
	u64 index;
	size_t struct_size;
	USER CHECKED struct hop_driver_string *data;
	data = (USER CHECKED struct hop_driver_string *)arg;
	validate_writable(data, sizeof(*data));
	COMPILER_READ_BARRIER();
	struct_size = data->ds_struct_size;
	COMPILER_READ_BARRIER();
	if (struct_size != sizeof(*data))
		THROW(E_BUFFER_TOO_SMALL, sizeof(*data), struct_size);
	COMPILER_WRITE_BARRIER();
	index = data->ds_index;
	COMPILER_READ_BARRIER();
	if unlikely(index != 0) {
		THROW(E_INVALID_ARGUMENT_RESERVED_ARGUMENT,
		      E_INVALID_ARGUMENT_CONTEXT_HOP_DRIVER_GETSTRING0,
		      index);
	}
	return get_driver_string(data, str, str_len_with_nul);
}


/************************************************************************/
/* struct driver;                                                       */
/************************************************************************/
PRIVATE struct driver *FCALL
require_driver(struct module *__restrict self) {
	if (!module_isdriver(self)) {
		THROW(E_INVALID_HANDLE_FILETYPE,
		      /* fd:                 */ 0, /* Filled in the caller */
		      /* needed_handle_type: */ HANDLE_TYPE_MODULE,
		      /* actual_handle_type: */ HANDLE_TYPE_MODULE,
		      /* needed_handle_kind: */ HANDLE_TYPEKIND_MODULE_DRIVER,
		      /* actual_handle_kind: */ HANDLE_TYPEKIND_MODULE_GENERIC);
	}
	return (struct driver *)self;
}

INTERN NONNULL((1)) syscall_slong_t KCALL
handle_module_hop(struct module *__restrict self,
                  syscall_ulong_t cmd,
                  USER UNCHECKED void *arg,
                  iomode_t mode)
		THROWS(...) {
	switch (cmd) {

	case HOP_DRIVER_STAT: {
		size_t struct_size;
		struct driver *me = require_driver(self);
		USER CHECKED struct hop_driver_stat *data;
		data = (USER CHECKED struct hop_driver_stat *)arg;
		validate_readwrite(data, sizeof(*data));
		COMPILER_READ_BARRIER();
		struct_size = data->ds_struct_size;
		COMPILER_READ_BARRIER();
		if (struct_size != sizeof(*data))
			THROW(E_BUFFER_TOO_SMALL, sizeof(*data), struct_size);
		COMPILER_WRITE_BARRIER();
		data->ds_state      = 0;
		data->ds_flags      = hop_driver_getflags(me);
		data->ds_loadaddr   = me->md_loadaddr;
		data->ds_loadstart  = (uintptr_t)me->md_loadmin;
		data->ds_loadend    = (uintptr_t)me->md_loadmax + 1;
		data->ds_argc       = me->d_argc;
		data->ds_depc       = me->d_depcnt;
		data->ds_symcnt     = me->d_dynsym_cnt;
		data->ds_shnum      = me->d_shnum;
		data->ds_strtabsz   = (size_t)(me->d_dynstr_end - me->d_dynstr);
		data->ds_shstrtabsz = me->d_shstrsiz;
		COMPILER_WRITE_BARRIER();
	}	break;

	case HOP_DRIVER_GET_NAME: {
		char const *name;
		struct driver *me;
		me   = require_driver(self);
		name = driver_getname(me);
		return get_driver_string0(arg, name, strlen(name) + 1);
	}	break;

	case HOP_DRIVER_GET_CMDLINE: {
		struct driver *me = require_driver(self);
		char *cmdline, *endptr;
		cmdline = me->d_cmdline;
		endptr  = cmdline;
		do {
			endptr = strend(endptr) + 1;
		} while (*endptr);
		return get_driver_string0(arg, cmdline, (size_t)(endptr - cmdline));
	}	break;

	case HOP_DRIVER_GET_ARGV: {
		struct driver *me = require_driver(self);
		USER CHECKED struct hop_driver_string *data;
		char const *argument_string;
		size_t struct_size;
		u64 index;
		data = (USER CHECKED struct hop_driver_string *)arg;
		validate_readwrite(data, sizeof(*data));
		COMPILER_READ_BARRIER();
		struct_size = data->ds_struct_size;
		COMPILER_READ_BARRIER();
		if (struct_size != sizeof(*data))
			THROW(E_BUFFER_TOO_SMALL, sizeof(*data), struct_size);
		COMPILER_WRITE_BARRIER();
		index = data->ds_index;
		COMPILER_READ_BARRIER();
		if unlikely(index >= (u64)me->d_argc) {
			THROW(E_INDEX_ERROR_OUT_OF_BOUNDS,
			      (intptr_t)(uintptr_t)index,
			      (intptr_t)(uintptr_t)0,
			      (intptr_t)(uintptr_t)me->d_argc - 1);
		}
		argument_string = me->d_argv[(size_t)index];
		return get_driver_string(data, argument_string,
		                               strlen(argument_string) + 1);
	}	break;

	case HOP_DRIVER_OPEN_FILE: {
		struct driver *me = require_driver(self);
		struct handle d;
		struct mfile *file;
		require(CAP_DRIVER_QUERY);
		file = driver_getfile(me);
		if unlikely(!file)
			THROW(E_NO_SUCH_OBJECT);
		d.h_type = HANDLE_TYPE_MFILE;
		d.h_mode = mode;
		d.h_data = file;
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, d);
	}	break;

	case HOP_DRIVER_OPEN_DEPENDENCY: {
		struct driver *me = require_driver(self);
		struct handle d;
		size_t struct_size;
		u64 depno;
		USER CHECKED struct hop_driver_open_dependency *data;
		data = (USER CHECKED struct hop_driver_open_dependency *)arg;
		validate_readable(data, sizeof(*data));
		COMPILER_READ_BARRIER();
		struct_size = data->dod_struct_size;
		COMPILER_READ_BARRIER();
		if (struct_size != sizeof(*data))
			THROW(E_BUFFER_TOO_SMALL, sizeof(*data), struct_size);
		require(CAP_DRIVER_QUERY);
		COMPILER_READ_BARRIER();
		depno = data->dod_depno;
		COMPILER_READ_BARRIER();
		if unlikely(depno >= (u64)me->d_depcnt) {
			THROW(E_INDEX_ERROR_OUT_OF_BOUNDS,
			      (intptr_t)(uintptr_t)depno,
			      (intptr_t)(uintptr_t)0,
			      (intptr_t)(uintptr_t)me->d_depcnt - 1);
		}
		d.h_type = HANDLE_TYPE_MODULE;
		d.h_mode = mode;
		d.h_data = axref_get(&me->d_depvec[(uintptr_t)depno]);
		if unlikely(!d.h_data)
			THROW(E_NO_SUCH_OBJECT);
		return handle_installhop(&data->dod_result, d);
	}	break;

	case HOP_DRIVER_INITIALIZE: {
		struct driver *me = require_driver(self);
		require(CAP_DRIVER_CONTROL);
		driver_initialize(me);
	}	break;

	case HOP_DRIVER_FINALIZE: {
		struct driver *me = require_driver(self);
		require(CAP_DRIVER_CONTROL);
		driver_finalize(me);
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND,
		      cmd);
		break;
	}
	return 0;
}


/************************************************************************/
/* struct driver_loadlist;                                                 */
/************************************************************************/
INTERN NONNULL((1)) syscall_slong_t KCALL
handle_driver_loadlist_hop(struct driver_loadlist *__restrict self,
                           syscall_ulong_t cmd,
                           USER UNCHECKED void *arg,
                           iomode_t mode)
		THROWS(...) {
	switch (cmd) {

	case HOP_DRIVER_LOADLIST_GET_COUNT: {
		USER CHECKED u64 *dest;
		dest = (USER CHECKED u64 *)arg;
		validate_writable(dest, sizeof(*dest));
		COMPILER_READ_BARRIER();
		*dest = (u64)self->dll_count;
		COMPILER_READ_BARRIER();
	}	break;

	case HOP_DRIVER_LOADLIST_GET_DRIVER: {
		size_t struct_size;
		u64 depno;
		struct handle d;
		syscall_slong_t result;
		REF struct driver *result_driver;
		USER CHECKED struct hop_driver_open_dependency *data;
		data = (USER CHECKED struct hop_driver_open_dependency *)arg;
		validate_readable(data, sizeof(*data));
		COMPILER_READ_BARRIER();
		struct_size = data->dod_struct_size;
		COMPILER_READ_BARRIER();
		if (struct_size != sizeof(*data))
			THROW(E_BUFFER_TOO_SMALL, sizeof(*data), struct_size);
		require(CAP_DRIVER_QUERY);
		COMPILER_READ_BARRIER();
		depno = data->dod_depno;
		COMPILER_READ_BARRIER();
		if unlikely(depno >= (u64)self->dll_count) {
			THROW(E_INDEX_ERROR_OUT_OF_BOUNDS,
			      (intptr_t)(uintptr_t)depno,
			      (intptr_t)(uintptr_t)0,
			      (intptr_t)(uintptr_t)self->dll_count - 1);
		}
		result_driver = self->dll_drivers[(uintptr_t)depno];
		d.h_type = HANDLE_TYPE_MODULE;
		d.h_mode = mode;
		d.h_data = result_driver;
		if unlikely(!tryincref(result_driver))
			THROW(E_NO_SUCH_OBJECT); /* Dead driver */
		{
			FINALLY_DECREF_UNLIKELY(result_driver);
			result = handle_installhop(&data->dod_result, d);
		}
		return result;
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND,
		      cmd);
		break;
	}
	return 0;
}


/************************************************************************/
/* struct driver_section;                                               */
/************************************************************************/
INTERN NONNULL((1)) syscall_slong_t KCALL
handle_driver_section_hop(struct driver_section *__restrict self,
                          syscall_ulong_t cmd,
                          USER UNCHECKED void *arg,
                          iomode_t mode)
		THROWS(...) {
	switch (cmd) {

		/* TODO */
		(void)self;
		(void)arg;
		(void)mode;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND,
		      cmd);
		break;
	}
	return 0;
}



DECL_END

#endif /* !GUARD_KERNEL_CORE_MEMORY_MMAN_DRIVER_HANDLE_C */
