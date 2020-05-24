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
#ifndef GUARD_KERNEL_CORE_FS_DRIVER_HANDLE_C
#define GUARD_KERNEL_CORE_FS_DRIVER_HANDLE_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/user.h>
#include <sched/cred.h>

#include <hybrid/atomic.h>

#include <kos/except/inval.h>
#include <kos/hop/driver.h>

#include <string.h>

DECL_BEGIN

/* Driver-handle API */
DEFINE_HANDLE_REFCNT_FUNCTIONS(driver, struct driver);
DEFINE_HANDLE_REFCNT_FUNCTIONS(driver_state, struct driver_state);
DEFINE_HANDLE_REFCNT_FUNCTIONS(driver_section, struct driver_section);

PRIVATE NOBLOCK uintptr_t
NOTHROW(KCALL hop_driver_getstate)(struct driver const *__restrict self) {
	STATIC_ASSERT(HOP_DRIVER_STATE_NORMAL == DRIVER_FLAG_NORMAL);
	STATIC_ASSERT(HOP_DRIVER_STATE_DEPLOADING == DRIVER_FLAG_DEPLOADING);
	STATIC_ASSERT(HOP_DRIVER_STATE_DEPLOADED == DRIVER_FLAG_DEPLOADED);
	STATIC_ASSERT(HOP_DRIVER_STATE_RELOCATING == DRIVER_FLAG_RELOCATING);
	STATIC_ASSERT(HOP_DRIVER_STATE_RELOCATED == DRIVER_FLAG_RELOCATED);
	STATIC_ASSERT(HOP_DRIVER_STATE_INITIALIZING == DRIVER_FLAG_INITIALIZING);
	STATIC_ASSERT(HOP_DRIVER_STATE_INITIALIZED == DRIVER_FLAG_INITIALIZED);
	STATIC_ASSERT(HOP_DRIVER_STATE_FINALIZING == DRIVER_FLAG_FINALIZING);
	STATIC_ASSERT(HOP_DRIVER_STATE_FINALIZED == DRIVER_FLAG_FINALIZED);
	STATIC_ASSERT(HOP_DRIVER_STATE_FINALIZED_C == DRIVER_FLAG_FINALIZED_C);
	return ATOMIC_READ(self->d_flags);
}

PRIVATE NOBLOCK uintptr_t KCALL
hop_driver_getflags(struct driver *__restrict self)
		THROWS(...) {
	uintptr_t result = 0;
	if (driver_getfile(self) != NULL)
		result |= HOP_DRIVER_FLAG_HAS_FILE;
	if (driver_getfilename(self) != NULL)
		result |= HOP_DRIVER_FLAG_HAS_FILENAME;
	if (self->d_eh_frame_start < self->d_eh_frame_end)
		result |= HOP_DRIVER_FLAG_HAS_EH_FRAME;
	if (self->d_dynsym_tab)
		result |= HOP_DRIVER_FLAG_HAS_DYNSYM;
	return result;
}

INTERN NONNULL((1)) syscall_slong_t KCALL
handle_driver_getstring(USER CHECKED struct hop_driver_string *data,
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

INTERN NONNULL((1)) syscall_slong_t KCALL
handle_driver_getstring0(USER UNCHECKED void *arg,
                         char const *__restrict str,
                         size_t str_len_with_nul)
		THROWS(...) {
	u64 index;
	size_t struct_size;
	USER CHECKED struct hop_driver_string *data;
	data = (USER CHECKED struct hop_driver_string *)arg;
	validate_writable(data, sizeof(*data));
	struct_size = ATOMIC_READ(data->ds_struct_size);
	if (struct_size != sizeof(*data))
		THROW(E_BUFFER_TOO_SMALL, sizeof(*data), struct_size);
	COMPILER_WRITE_BARRIER();
	index = ATOMIC_READ(data->ds_index);
	if unlikely(index != 0) {
		THROW(E_INVALID_ARGUMENT_RESERVED_ARGUMENT,
		      E_INVALID_ARGUMENT_CONTEXT_HOP_DRIVER_GETSTRING0,
		      index);
	}
	return handle_driver_getstring(data, str, str_len_with_nul);
}


/************************************************************************/
/* struct driver;                                                       */
/************************************************************************/
INTERN NONNULL((1)) syscall_slong_t KCALL
handle_driver_hop(struct driver *__restrict self,
                  syscall_ulong_t cmd,
                  USER UNCHECKED void *arg,
                  iomode_t mode)
		THROWS(...) {
	switch (cmd) {

	case HOP_DRIVER_STAT: {
		size_t struct_size;
		USER CHECKED struct hop_driver_stat *data;
		data = (USER CHECKED struct hop_driver_stat *)arg;
		validate_writable(data, sizeof(*data));
		struct_size = ATOMIC_READ(data->ds_struct_size);
		if (struct_size != sizeof(*data))
			THROW(E_BUFFER_TOO_SMALL, sizeof(*data), struct_size);
		cred_require_sysadmin();
		COMPILER_WRITE_BARRIER();
		data->ds_state      = hop_driver_getstate(self);
		data->ds_flags      = hop_driver_getflags(self);
		data->ds_loadaddr   = self->d_loadaddr;
		data->ds_loadstart  = self->d_loadstart;
		data->ds_loadend    = self->d_loadend;
		data->ds_argc       = self->d_argc;
		data->ds_depc       = self->d_depcnt;
		data->ds_symcnt     = self->d_dynsym_cnt;
		data->ds_shnum      = self->d_shnum;
		data->ds_strtabsz   = (size_t)(self->d_dynstr_end - self->d_dynstr);
		data->ds_shstrtabsz = (size_t)(self->d_shstrtab_end - self->d_shstrtab);
		COMPILER_WRITE_BARRIER();
	}	break;

	case HOP_DRIVER_GET_NAME: {
		char const *name;
		cred_require_sysadmin();
		name = driver_getname(self);
		return handle_driver_getstring0(arg, name, strlen(name) + 1);
	}	break;

	case HOP_DRIVER_GET_CMDLINE: {
		char *cmdline, *endptr;
		cred_require_sysadmin();
		cmdline = self->d_cmdline;
		endptr  = cmdline;
		do {
			endptr = strend(endptr) + 1;
		} while (*endptr);
		return handle_driver_getstring0(arg, cmdline,
		                                (size_t)(endptr - cmdline));
	}	break;

	case HOP_DRIVER_GET_FILENAME: {
		char const *filename;
		cred_require_sysadmin();
		filename = driver_getfilename(self);
		if unlikely(!filename)
			THROW(E_NO_SUCH_OBJECT);
		return handle_driver_getstring0(arg, filename, strlen(filename) + 1);
	}	break;

	case HOP_DRIVER_GET_ARGV: {
		u64 index;
		size_t struct_size;
		char const *argument_string;
		USER CHECKED struct hop_driver_string *data;
		data = (USER CHECKED struct hop_driver_string *)arg;
		validate_writable(data, sizeof(*data));
		struct_size = ATOMIC_READ(data->ds_struct_size);
		if (struct_size != sizeof(*data))
			THROW(E_BUFFER_TOO_SMALL, sizeof(*data), struct_size);
		COMPILER_WRITE_BARRIER();
		cred_require_sysadmin();
		index = ATOMIC_READ(data->ds_index);
		if unlikely(index >= (u64)self->d_argc) {
			THROW(E_INDEX_ERROR_OUT_OF_BOUNDS,
			      (intptr_t)(uintptr_t)index,
			      (intptr_t)(uintptr_t)0,
			      (intptr_t)(uintptr_t)self->d_argc - 1);
		}
		argument_string = self->d_argv[(size_t)index];
		return handle_driver_getstring(data, argument_string,
		                               strlen(argument_string) + 1);
	}	break;

	case HOP_DRIVER_OPEN_FILE: {
		struct handle d;
		struct regular_node *file;
		cred_require_sysadmin();
		file = driver_getfile(self);
		if unlikely(!file)
			THROW(E_NO_SUCH_OBJECT);
		d.h_type = HANDLE_TYPE_DATABLOCK;
		d.h_mode = mode;
		d.h_data = file;
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, d);
	}	break;

	case HOP_DRIVER_OPEN_DEPENDENCY: {
		size_t struct_size;
		u64 depno;
		struct handle d;
		USER CHECKED struct hop_driver_open_dependency *data;
		data = (USER CHECKED struct hop_driver_open_dependency *)arg;
		validate_readable(data, sizeof(*data));
		struct_size = ATOMIC_READ(data->dod_struct_size);
		if (struct_size != sizeof(*data))
			THROW(E_BUFFER_TOO_SMALL, sizeof(*data), struct_size);
		cred_require_sysadmin();
		COMPILER_READ_BARRIER();
		depno = data->dod_depno;
		COMPILER_READ_BARRIER();
		if unlikely(depno >= (u64)self->d_depcnt) {
			THROW(E_INDEX_ERROR_OUT_OF_BOUNDS,
			      (intptr_t)(uintptr_t)depno,
			      (intptr_t)(uintptr_t)0,
			      (intptr_t)(uintptr_t)self->d_depcnt - 1);
		}
		d.h_type = HANDLE_TYPE_DRIVER;
		d.h_mode = mode;
		d.h_data = self->d_depvec[(uintptr_t)depno];
		return handle_installhop(&data->dod_result, d);
	}	break;

	case HOP_DRIVER_INITIALIZE:
		cred_require_sysadmin();
		return driver_initialize(self);

	case HOP_DRIVER_FINALIZE:
		cred_require_sysadmin();
		return driver_finalize(self);

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND,
		      cmd);
		break;
	}
	return 0;
}


/************************************************************************/
/* struct driver_state;                                                 */
/************************************************************************/
INTERN NONNULL((1)) syscall_slong_t KCALL
handle_driver_state_hop(struct driver_state *__restrict self,
                        syscall_ulong_t cmd,
                        USER UNCHECKED void *arg,
                        iomode_t mode)
		THROWS(...) {
	switch (cmd) {

	case HOP_DRIVER_STATE_GET_COUNT: {
		USER CHECKED u64 *dest;
		dest = (USER CHECKED u64 *)arg;
		validate_writable(dest, sizeof(*dest));
		cred_require_sysadmin();
		ATOMIC_WRITE(*dest, (u64)self->ds_count);
	}	break;

	case HOP_DRIVER_STATE_GET_DRIVER: {
		size_t struct_size;
		u64 depno;
		struct handle d;
		USER CHECKED struct hop_driver_open_dependency *data;
		data = (USER CHECKED struct hop_driver_open_dependency *)arg;
		validate_readable(data, sizeof(*data));
		struct_size = ATOMIC_READ(data->dod_struct_size);
		if (struct_size != sizeof(*data))
			THROW(E_BUFFER_TOO_SMALL, sizeof(*data), struct_size);
		cred_require_sysadmin();
		COMPILER_READ_BARRIER();
		depno = data->dod_depno;
		COMPILER_READ_BARRIER();
		if unlikely(depno >= (u64)self->ds_count) {
			THROW(E_INDEX_ERROR_OUT_OF_BOUNDS,
			      (intptr_t)(uintptr_t)depno,
			      (intptr_t)(uintptr_t)0,
			      (intptr_t)(uintptr_t)self->ds_count - 1);
		}
		d.h_type = HANDLE_TYPE_DRIVER;
		d.h_mode = mode;
		d.h_data = self->ds_drivers[(uintptr_t)depno];
		return handle_installhop(&data->dod_result, d);
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

#endif /* !GUARD_KERNEL_CORE_FS_DRIVER_HANDLE_C */
