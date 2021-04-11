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
#ifndef GUARD_KERNEL_CORE_FS_DRIVER_HANDLE_C
#define GUARD_KERNEL_CORE_FS_DRIVER_HANDLE_C 1
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
#include <kos/hop/driver.h>

#include <string.h>

DECL_BEGIN

/* Driver-handle API */
DEFINE_HANDLE_REFCNT_FUNCTIONS_WITH_WEAKREF_SUPPORT(driver, struct driver);
DEFINE_HANDLE_REFCNT_FUNCTIONS(driver_section, struct driver_section);
DEFINE_HANDLE_REFCNT_FUNCTIONS(driver_loadlist, struct driver_loadlist);


#ifndef CONFIG_USE_NEW_DRIVER
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
#endif /* !CONFIG_USE_NEW_DRIVER */

PRIVATE NOBLOCK uintptr_t KCALL
hop_driver_getflags(struct driver *__restrict self)
		THROWS(...) {
	uintptr_t result = 0;
	if (driver_getfile(self) != NULL)
		result |= HOP_DRIVER_FLAG_HAS_FILE;
#ifndef CONFIG_USE_NEW_DRIVER
	if (driver_getfilename(self) != NULL)
		result |= HOP_DRIVER_FLAG_HAS_FILENAME;
#endif /* !CONFIG_USE_NEW_DRIVER */
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
		validate_readwrite(data, sizeof(*data));
		COMPILER_READ_BARRIER();
		struct_size = data->ds_struct_size;
		COMPILER_READ_BARRIER();
		if (struct_size != sizeof(*data))
			THROW(E_BUFFER_TOO_SMALL, sizeof(*data), struct_size);
		COMPILER_WRITE_BARRIER();
#ifdef CONFIG_USE_NEW_DRIVER
		data->ds_state      = 0;
#else /* CONFIG_USE_NEW_DRIVER */
		data->ds_state      = hop_driver_getstate(self);
#endif /* !CONFIG_USE_NEW_DRIVER */
		data->ds_flags      = hop_driver_getflags(self);
#ifdef CONFIG_USE_NEW_DRIVER
		data->ds_loadaddr   = self->md_loadaddr;
		data->ds_loadstart  = (uintptr_t)self->md_loadmin;
		data->ds_loadend    = (uintptr_t)self->md_loadmax + 1;
#else /* CONFIG_USE_NEW_DRIVER */
		data->ds_loadaddr   = self->d_loadaddr;
		data->ds_loadstart  = self->d_loadstart;
		data->ds_loadend    = self->d_loadend;
#endif /* !CONFIG_USE_NEW_DRIVER */
		data->ds_argc       = self->d_argc;
		data->ds_depc       = self->d_depcnt;
		data->ds_symcnt     = self->d_dynsym_cnt;
		data->ds_shnum      = self->d_shnum;
		data->ds_strtabsz   = (size_t)(self->d_dynstr_end - self->d_dynstr);
#ifdef CONFIG_USE_NEW_DRIVER
		data->ds_shstrtabsz = self->d_shstrsiz;
#else /* CONFIG_USE_NEW_DRIVER */
		data->ds_shstrtabsz = (size_t)(self->d_shstrtab_end - self->d_shstrtab);
#endif /* !CONFIG_USE_NEW_DRIVER */
		COMPILER_WRITE_BARRIER();
	}	break;

	case HOP_DRIVER_GET_NAME: {
		char const *name;
		name = driver_getname(self);
		return handle_driver_getstring0(arg, name, strlen(name) + 1);
	}	break;

	case HOP_DRIVER_GET_CMDLINE: {
		char *cmdline, *endptr;
		cmdline = self->d_cmdline;
		endptr  = cmdline;
		do {
			endptr = strend(endptr) + 1;
		} while (*endptr);
		return handle_driver_getstring0(arg, cmdline,
		                                (size_t)(endptr - cmdline));
	}	break;

#ifndef CONFIG_USE_NEW_DRIVER
	case HOP_DRIVER_GET_FILENAME: {
		char const *filename;
		filename = driver_getfilename(self);
		if unlikely(!filename)
			THROW(E_NO_SUCH_OBJECT);
		return handle_driver_getstring0(arg, filename, strlen(filename) + 1);
	}	break;
#endif /* !CONFIG_USE_NEW_DRIVER */

	case HOP_DRIVER_GET_ARGV: {
		u64 index;
		size_t struct_size;
		char const *argument_string;
		USER CHECKED struct hop_driver_string *data;
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
#ifdef CONFIG_USE_NEW_DRIVER
		struct mfile *file;
#else /* CONFIG_USE_NEW_DRIVER */
		struct regular_node *file;
#endif /* !CONFIG_USE_NEW_DRIVER */
		require(CAP_DRIVER_QUERY);
		file = driver_getfile(self);
		if unlikely(!file)
			THROW(E_NO_SUCH_OBJECT);
		d.h_type = HANDLE_TYPE_MFILE;
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
		COMPILER_READ_BARRIER();
		struct_size = data->dod_struct_size;
		COMPILER_READ_BARRIER();
		if (struct_size != sizeof(*data))
			THROW(E_BUFFER_TOO_SMALL, sizeof(*data), struct_size);
		require(CAP_DRIVER_QUERY);
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
#ifdef CONFIG_USE_NEW_DRIVER
		d.h_data = axref_get(&self->d_depvec[(uintptr_t)depno]);
#else /* CONFIG_USE_NEW_DRIVER */
		d.h_data = self->d_depvec[(uintptr_t)depno];
#endif /* !CONFIG_USE_NEW_DRIVER */
		if unlikely(!d.h_data)
			THROW(E_NO_SUCH_OBJECT);
		return handle_installhop(&data->dod_result, d);
	}	break;

	case HOP_DRIVER_INITIALIZE:
		require(CAP_DRIVER_CONTROL);
#ifdef CONFIG_USE_NEW_DRIVER
		driver_initialize(self);
		break;
#else /* CONFIG_USE_NEW_DRIVER */
		return driver_initialize(self);
#endif /* !CONFIG_USE_NEW_DRIVER */

	case HOP_DRIVER_FINALIZE:
		require(CAP_DRIVER_CONTROL);
#ifdef CONFIG_USE_NEW_DRIVER
		driver_finalize(self);
		break;
#else /* CONFIG_USE_NEW_DRIVER */
		return driver_finalize(self);
#endif /* !CONFIG_USE_NEW_DRIVER */

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

	case HOP_DRIVER_STATE_GET_COUNT: {
		USER CHECKED u64 *dest;
		dest = (USER CHECKED u64 *)arg;
		validate_writable(dest, sizeof(*dest));
		COMPILER_READ_BARRIER();
		*dest = (u64)self->dll_count;
		COMPILER_READ_BARRIER();
	}	break;

	case HOP_DRIVER_STATE_GET_DRIVER: {
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
		d.h_type = HANDLE_TYPE_DRIVER;
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

#endif /* !GUARD_KERNEL_CORE_FS_DRIVER_HANDLE_C */
