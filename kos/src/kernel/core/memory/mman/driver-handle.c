/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_MEMORY_MMAN_DRIVER_HANDLE_C
#define GUARD_KERNEL_CORE_MEMORY_MMAN_DRIVER_HANDLE_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/fs.h>
#include <kernel/fs/path.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/handman.h>
#include <kernel/iovec.h>
#include <kernel/mman.h>
#include <kernel/mman/driver.h>
#include <kernel/mman/module.h>
#include <kernel/mman/rw.h>
#include <kernel/user.h>
#include <sched/cred.h>

#include <hybrid/overflow.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <kos/ioctl/mod.h>

#include <atomic.h>
#include <format-printer.h>
#include <string.h>

DECL_BEGIN

/* Driver-handle API */
DEFINE_HANDLE_REFCNT_FUNCTIONS_WITH_WEAKREF_SUPPORT(module, struct module);
DEFINE_HANDLE_REFCNT_FUNCTIONS(module_section, struct module_section);
DEFINE_HANDLE_REFCNT_FUNCTIONS(driver_loadlist, struct driver_loadlist);

PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1)) struct driver *FCALL
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


INTERN BLOCKING WUNUSED NONNULL((1)) size_t KCALL
handle_module_pread(struct module *__restrict self, NCX void *dst,
                    size_t num_bytes, pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	uintptr_t base;
	size_t max_io;
	if (OVERFLOW_USUB((uintptr_t)self->md_loadmin, addr, &base))
		return 0;
	if (OVERFLOW_USUB((uintptr_t)self->md_loadmax, base, &max_io))
		return 0;
	++max_io;
	if (max_io == 0 || max_io > num_bytes)
		max_io = num_bytes;
	if (!tryincref(self->md_mman))
		return 0;
	FINALLY_DECREF_UNLIKELY(self->md_mman);
	mman_read(self->md_mman, (void const *)base, dst, max_io, true);
	return max_io;
}

INTERN BLOCKING NONNULL((1)) size_t KCALL
handle_module_pwrite(struct module *__restrict self, NCX void const *src,
                     size_t num_bytes, pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	uintptr_t base;
	size_t max_io;
	if (OVERFLOW_USUB((uintptr_t)self->md_loadmin, addr, &base))
		return 0;
	if (OVERFLOW_USUB((uintptr_t)self->md_loadmax, base, &max_io))
		return 0;
	++max_io;
	if (max_io == 0 || max_io > num_bytes)
		max_io = num_bytes;
	if (!tryincref(self->md_mman))
		return 0;
	/* XXX: If we ever implement cryptographically signed drivers, and
	 *      `self' is such a driver, then  we must mark the kernel  as
	 *      poisoned at this point! */
	FINALLY_DECREF_UNLIKELY(self->md_mman);
	mman_write(self->md_mman, (void *)base, src, max_io, true);
	return max_io;
}

INTERN BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL
handle_module_preadv(struct module *__restrict self, struct iov_buffer *__restrict dst,
                     size_t UNUSED(num_bytes), pos_t addr, iomode_t mode) THROWS(...) {
	size_t result = 0;
	struct iov_entry ent;
	IOV_BUFFER_FOREACH(ent, dst) {
		size_t temp;
		temp = handle_module_pread(self, ent.ive_base, ent.ive_size, addr, mode);
		result += temp;
		if (temp < ent.ive_size)
			break;
		addr += temp;
	}
	return result;
}

INTERN BLOCKING NONNULL((1, 2)) size_t KCALL
handle_module_pwritev(struct module *__restrict self, struct iov_buffer *__restrict src,
                      size_t UNUSED(num_bytes), pos_t addr, iomode_t mode) THROWS(...) {
	size_t result = 0;
	struct iov_entry ent;
	IOV_BUFFER_FOREACH(ent, src) {
		size_t temp;
		temp = handle_module_pwrite(self, ent.ive_base, ent.ive_size, addr, mode);
		result += temp;
		if (temp < ent.ive_size)
			break;
		addr += temp;
	}
	return result;
}

PRIVATE NONNULL((1)) syscall_slong_t KCALL
driver_ioctl_getstring(struct module *__restrict self, uint64_t index,
                       NCX struct mod_string *info) {
	size_t result;
	struct format_snprintf_data pdat;
	pdat.sd_buffer = info->ms_buf;
	pdat.sd_bufsiz = (size_t)info->ms_size;
	COMPILER_READ_BARRIER();
	validate_writable(pdat.sd_buffer, pdat.sd_bufsiz);
	switch (index) {

	case MOD_STR_NAME:
		result = (size_t)module_printname(self, &format_snprintf_printer, &pdat);
		break;

	case MOD_STR_FILENAME: {
		if (self->md_fsname && self->md_fspath) {
			/* Special handling so we don't expose paths outside the caller's sysroot.
			 * Also: we want to emit paths using the relevant filesystem model! */
			REF struct path *root = fs_getroot(THIS_FS);
			FINALLY_DECREF_UNLIKELY(root);
			result = (size_t)path_printent(self->md_fspath,
			                               self->md_fsname->fd_name,
			                               self->md_fsname->fd_namelen,
			                               &format_snprintf_printer, &pdat,
			                               fs_atflags(0) | AT_PATHPRINT_INCTRAIL,
			                               root);
		} else {
			result = (size_t)module_printpath(self, &format_snprintf_printer, &pdat);
		}
	}	break;

	case MOD_STR_CMDLINE: {
		struct driver *me = require_driver(self);
		char const *cmdln = me->d_cmdline;
		char const *cmdep = cmdln;
		while (*cmdep)
			cmdep = strend(cmdep) + 1;
		result = (size_t)format_snprintf_printer(&pdat, cmdln, (size_t)(cmdep - cmdln));
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_MOD_IOC_GETSTRING_BADINDEX,
		      (uintptr_t)index);
		break;
	}
	/* Always append a trailing NUL */
	result += (size_t)format_snprintf_printer(&pdat, "", 1);
	COMPILER_WRITE_BARRIER();
	info->ms_size = result;
	return (syscall_slong_t)result;
}


INTERN BLOCKING NONNULL((1)) syscall_slong_t KCALL
handle_module_ioctl(struct module *__restrict self, ioctl_t cmd,
                    NCX UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	switch (cmd) {

	case MOD_IOC_GETOBJECT: {
		struct driver *me;
		struct handle hand;
		NCX struct mod_object *info;
		uint64_t index;
		validate_readwrite(arg, sizeof(*info));
		info  = (NCX struct mod_object *)arg;
		index = info->mo_index;
		COMPILER_READ_BARRIER();
		me = require_driver(self);
		if (index >= (uint64_t)me->d_depcnt)
			THROW(E_INDEX_ERROR_OUT_OF_BOUNDS, (size_t)index, 0, me->d_depcnt - 1);
		require(CAP_SYS_MODULE);
		hand.h_data = axref_get(&me->d_depvec[(size_t)index]);
		if (!hand.h_data)
			THROW(E_NO_SUCH_OBJECT);
		hand.h_type = HANDLE_TYPE_MODULE;
		hand.h_mode = mode;
		FINALLY_DECREF_UNLIKELY((struct driver *)hand.h_data);
		return handles_install_openfd(hand, &info->mo_result);
	}	break;

	case MOD_IOC_GETSTRING: {
		NCX struct mod_string *info;
		uint64_t index;
		validate_readwrite(arg, sizeof(*info));
		info  = (NCX struct mod_string *)arg;
		index = info->ms_index;
		COMPILER_READ_BARRIER();
		return driver_ioctl_getstring(self, index, info);
	}	break;

	case MOD_IOC_LOADINFO: {
		NCX struct mod_loadinfo *info;
		validate_readwrite(arg, sizeof(*info));
		info = (NCX struct mod_loadinfo *)arg;
		require(CAP_SYS_MODULE);
		COMPILER_WRITE_BARRIER();
		info->mli_loadaddr  = (uintptr_t)self->md_loadaddr;
		info->mli_loadstart = (uintptr_t)self->md_loadmin;
		info->mli_loadmax   = (uintptr_t)self->md_loadmax;
		return 0;
	}	break;

	case MOD_IOC_INIT: {
		require(CAP_SYS_MODULE);
		driver_initialize(require_driver(self));
		return 0;
	}	break;

	case MOD_IOC_FINI: {
		require(CAP_SYS_MODULE);
		driver_finalize(require_driver(self));
		return 0;
	}	break;

	default:
		break;
	}
	switch (_IO_WITHSIZE(cmd, 0)) {

	case _IO_WITHSIZE(MOD_IOC_GETCOUNT, 0): {
		struct driver *me = require_driver(self);
		return ioctl_intarg_setu64(cmd, arg, me->d_depcnt);
	}	break;

	case _IO_WITHSIZE(MOD_IOC_GETSTATE, 0): {
		struct driver *me = require_driver(self);
		uintptr_t state   = atomic_read(&me->d_state);
		return ioctl_intarg_setint(cmd, arg, ((int)state - DRIVER_STATE_LOADED));
	}	break;

	default:
		break;
	}
	THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
	      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
	      cmd);
}

INTERN BLOCKING NONNULL((1)) syscall_slong_t KCALL
handle_driver_loadlist_ioctl(struct driver_loadlist *__restrict self, ioctl_t cmd,
                             NCX UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	switch (cmd) {

	case MOD_IOC_GETOBJECT: {
		struct handle hand;
		NCX struct mod_object *info;
		uint64_t index;
		validate_readwrite(arg, sizeof(*info));
		info  = (NCX struct mod_object *)arg;
		index = info->mo_index;
		COMPILER_READ_BARRIER();
		if (index >= (uint64_t)self->dll_count)
			THROW(E_INDEX_ERROR_OUT_OF_BOUNDS, (size_t)index, 0, self->dll_count - 1);
		require(CAP_SYS_MODULE);
		hand.h_data = self->dll_drivers[(size_t)index];
		if (!tryincref((struct driver *)hand.h_data))
			THROW(E_NO_SUCH_OBJECT);
		hand.h_type = HANDLE_TYPE_MODULE;
		hand.h_mode = mode;
		FINALLY_DECREF_UNLIKELY((struct driver *)hand.h_data);
		return handles_install_openfd(hand, &info->mo_result);
	}	break;

	case MOD_IOC_GETSTRING: {
		REF struct driver *drv;
		NCX struct mod_string *info;
		uint64_t index;
		validate_readwrite(arg, sizeof(*info));
		info  = (NCX struct mod_string *)arg;
		index = info->ms_index;
		COMPILER_READ_BARRIER();
		if (index >= (uint64_t)self->dll_count)
			THROW(E_INDEX_ERROR_OUT_OF_BOUNDS, (size_t)index, 0, self->dll_count - 1);
		drv = self->dll_drivers[(size_t)index];
		if (!tryincref(drv))
			THROW(E_NO_SUCH_OBJECT);
		FINALLY_DECREF_UNLIKELY(drv);
		return driver_ioctl_getstring(drv, MOD_STR_NAME, info);
	}	break;

	default:
		break;
	}
	switch (_IO_WITHSIZE(cmd, 0)) {

	case _IO_WITHSIZE(MOD_IOC_GETCOUNT, 0):
		return ioctl_intarg_setu64(cmd, arg, self->dll_count);

	default:
		break;
	}
	THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
	      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
	      cmd);
}


INTERN BLOCKING NONNULL((1, 2)) ssize_t KCALL
handle_module_printlink(struct module *__restrict self,
                        pformatprinter printer, void *arg)
		THROWS(E_WOULDBLOCK, ...) {
	char const *name = module_getname(self);
	return format_printf(printer, arg, "%s:[%q]",
	                     module_isdriver(self) ? "driver" : "module",
	                     name ? name : "?");
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_MEMORY_MMAN_DRIVER_HANDLE_C */
