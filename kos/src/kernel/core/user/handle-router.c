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
#ifndef GUARD_KERNEL_SRC_USER_HANDLE_C
#define GUARD_KERNEL_SRC_USER_HANDLE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/aio.h>
#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/types.h>

#include <kos/except/reason/fs.h>
#include <kos/except/reason/inval.h>
#include <kos/kernel/handle.h>

#include <assert.h>
#include <stddef.h>

/* This #include must be relative so that `deemon -F' can find it! */
#include "../../include/kernel/handle-proto.h"


#pragma GCC diagnostic ignored "-Wsuggest-attribute=pure"
#pragma GCC diagnostic ignored "-Wsuggest-attribute=const"
#pragma GCC diagnostic ignored "-Wsuggest-attribute=cold"

DECL_BEGIN

/*[[[deemon
import util;
import * from deemon;

@@List of (name, type)
local handle_types: {(string, string)...} = [];

function injectObjectType(type_expr: string, typename: string): string {
	if (!typename) typename = "void";
	switch (type_expr) {
	case "T *":                    return typename + " *";
	case "T *__restrict":          return typename + " *__restrict";
	case "T const *":              return typename + " const *";
	case "T const *__restrict":    return typename + " const *__restrict";
	case "REF T *":                return "REF " + typename + " *";
	case "REF T *__restrict":      return "REF " + typename + " *__restrict";
	case "WEAK REF T *":           return "WEAK REF " + typename + " *";
	case "WEAK REF T *__restrict": return "WEAK REF " + typename + " *__restrict";
	default: break;
	}
	return type_expr;
}

for (local l: File.open("../../../../include/kos/kernel/handle.h")) {
	local name, id, tail;
	try name, id, tail = l.scanf(" # define HANDLE_TYPE_%[^ ] %[^ /] %[^]")...;
	catch (...) continue;
	if (name == "COUNT")
		continue;
	id = int(id);
	if (id >= #handle_types)
		handle_types.resize(id + 1, ("undefined", ""));
	tail = try tail.scanf(" /" "* `%[^']")[0] catch (...) "";
	handle_types[id] = (name.lower(), tail);
}

#define ARGS   name,attr,return_type,nothrow,cc,argv,throws,default_impl
local ops = HANDLE_OPERATOR_PROTOTYPES;

function needsPerTypeImpl(default_impl) {
	return "{" in default_impl;
}

print "/" "* Fallback handle operators *" "/";
for (local ARGS: ops) {
	local needPerType = needsPerTypeImpl(default_impl);
	print "INTERN",;
	if (attr) {
		print " ",;
		print attr,;
	}
	print " ATTR_SECTION(\".text.kernel.handle_undefined.",;
	print name,;
	print "\") ",;
	return_type = injectObjectType(return_type, "void");
	print return_type,;
	if (!return_type.endswith("*"))
		print " ",;
	print nothrow,;
	if (nothrow)
		print "(",;
	print cc, "handle_undefined_",;
	print name,;
	if (nothrow)
		print ")",;
	print "(",;
	local is_first = true;
	for (local t, n: argv) {
		if (!is_first)
			print ", ",;
		t = injectObjectType(t, "void");
		print t,;
		if (!t.endswith("*"))
			print " ",;
		if (!needPerType && name !in ["weakgetref"] && (n !in ["cmd"] || name !in ["ioctl", "hop"])) {
			print "UNUSED(",;
			print n,;
			print ")",;
		} else {
			print n,;
		}
		is_first = false;
	}
	print ") ",;
	if (throws) {
		print throws,;
		print " ",;
	}
	print "{ ",;
	if (needPerType) {
		print default_impl.format({
			"HANDLE_TYPE" : "HANDLE_TYPE_UNDEFINED",
			"h_name" : "undefined"
		}),;
	} else {
		print default_impl,;
	}
	print " }";
}
print;

print;
print "/" "* Handle type database *" "/";
local longest_handle_name_length = 0;
for (local h_name, none: handle_types) {
	h_name = #h_name;
	if (longest_handle_name_length < h_name)
		longest_handle_name_length = h_name;
}

print "PUBLIC_CONST struct handle_types const handle_type_db = {";
print "\t/" "* .h_typename = *" "/ {";
local is_first = true;
for (local h_name, none: handle_types) {
	if (!is_first)
		print ",";
	is_first = false;
	print "\t\t/" "* [HANDLE_TYPE_",;
	print h_name.upper(),;
	print "] ",;
	print " " * (longest_handle_name_length - #h_name),;
	print "= *" "/ ",;
	print repr(h_name),;
}
print "\n\t},";

for (local ARGS: ops) {
	print "\t/" "* .h_",;
	print name,;
	print " = *" "/ {";
	local is_first = true;
	for (local h_name, none: handle_types) {
		if (!is_first)
			print ",";
		is_first = false;
		print "\t\t/" "* [HANDLE_TYPE_",;
		print h_name.upper(),;
		print "] ",;
		print " " * (longest_handle_name_length - #h_name),;
		print "= *" "/ (",;
		return_type = injectObjectType(return_type, "void");
		print return_type,;
		if (!return_type.endswith("*"))
			print " ",;
		print "(",;
		print cc,;
		print " *)(",;
		local is_first = true;
		for (local t, n: argv) {
			if (!is_first)
				print ", ",;
			t = injectObjectType(t, "void");
			print t,;
			is_first = false;
		}
		print "))&handle_",;
		print h_name,;
		print "_",;
		print name,;
	}
	print "\n\t},";
}
print "};";
print;
print;
print;


for (local h_name, h_typ: handle_types) {
	if (h_name in ["undefined"])
		continue;
	print "/" "* Weakly define operators for `HANDLE_TYPE_",;
	print h_name.upper(),;
	print "'",;
	if (h_typ) {
		print " (`",;
		print h_typ,;
		print "')",;
	}
	print " *" "/";
	for (local ARGS: ops) {
		if (needsPerTypeImpl(default_impl)) {
			print "INTERN",;
			if (attr) {
				print " ",;
				print attr,;
			}
			print " ATTR_WEAK ATTR_SECTION(\".text.kernel.handle_",;
			print h_name,;
			print ".",;
			print name,;
			print "\") ",;
			return_type = injectObjectType(return_type, h_typ);
			print return_type,;
			if (!return_type.endswith("*"))
				print " ",;
			print nothrow,;
			if (nothrow)
				print "(",;
			print cc;
			print "handle_",;
			print h_name,;
			print "_",;
			print name,;
			if (nothrow)
				print ")",;
			print "(",;
			local is_first = true;
			for (local t, n: argv) {
				t = injectObjectType(t, h_typ);
				if (!is_first)
					print ", ",;
				print t,;
				if (!t.endswith("*"))
					print " ",;
				print n,;
				is_first = false;
			}
			print ") ",;
			if (throws) {
				print throws,;
				print " ",;
			}
			print "{";
			print "\t",;
			print default_impl.format({
				"HANDLE_TYPE" : "HANDLE_TYPE_" + h_name.upper(),
				"h_name" : h_name
			});
			print "}";
			continue;
		}
		print "DEFINE_INTERN_WEAK_ALIAS(handle_",;
		print h_name,;
		print "_",;
		print name,;
		print ", ",;
		print "handle_undefined_",;
		print name,;
		print ");";
	}
	print;
}

]]]*/
/* Fallback handle operators */
INTERN NOBLOCK WUNUSED NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.refcnt") refcnt_t NOTHROW(FCALL handle_undefined_refcnt)(void const *__restrict UNUSED(self)) { return 0; }
INTERN NOBLOCK NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.incref") void NOTHROW(FCALL handle_undefined_incref)(void *__restrict UNUSED(self)) {  }
INTERN NOBLOCK NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.decref") void NOTHROW(FCALL handle_undefined_decref)(REF void *__restrict UNUSED(self)) {  }
INTERN NOBLOCK WUNUSED NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.tryincref") __BOOL NOTHROW(FCALL handle_undefined_tryincref)(void *__restrict UNUSED(self)) { return 1; }
INTERN NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.weakgetref") WEAK REF void *NOTHROW(FCALL handle_undefined_weakgetref)(void *__restrict self) { return self; }
INTERN NOBLOCK WUNUSED NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.weaklckref") REF void *NOTHROW(FCALL handle_undefined_weaklckref)(void *__restrict UNUSED(weakref_ptr)) { return NULL; }
INTERN NOBLOCK NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.weakdecref") void NOTHROW(FCALL handle_undefined_weakdecref)(WEAK REF void *__restrict UNUSED(weakref_ptr)) {  }
INTERN WUNUSED NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.read") size_t KCALL handle_undefined_read(void *__restrict UNUSED(self), USER CHECKED void *UNUSED(dst), size_t UNUSED(num_bytes), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ); }
INTERN WUNUSED NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.write") size_t KCALL handle_undefined_write(void *__restrict UNUSED(self), USER CHECKED void const *UNUSED(src), size_t UNUSED(num_bytes), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE); }
INTERN WUNUSED NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.pread") size_t KCALL handle_undefined_pread(void *__restrict UNUSED(self), USER CHECKED void *UNUSED(dst), size_t UNUSED(num_bytes), pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_PREAD); }
INTERN WUNUSED NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.pwrite") size_t KCALL handle_undefined_pwrite(void *__restrict UNUSED(self), USER CHECKED void const *UNUSED(src), size_t UNUSED(num_bytes), pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_PWRITE); }
INTERN WUNUSED NONNULL((1, 2)) ATTR_SECTION(".text.kernel.handle_undefined.readv") size_t KCALL handle_undefined_readv(void *__restrict UNUSED(self), struct iov_buffer *__restrict UNUSED(dst), size_t UNUSED(num_bytes), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ); }
INTERN WUNUSED NONNULL((1, 2)) ATTR_SECTION(".text.kernel.handle_undefined.writev") size_t KCALL handle_undefined_writev(void *__restrict UNUSED(self), struct iov_buffer *__restrict UNUSED(src), size_t UNUSED(num_bytes), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE); }
INTERN WUNUSED NONNULL((1, 2)) ATTR_SECTION(".text.kernel.handle_undefined.preadv") size_t KCALL handle_undefined_preadv(void *__restrict UNUSED(self), struct iov_buffer *__restrict UNUSED(dst), size_t UNUSED(num_bytes), pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_PREAD); }
INTERN WUNUSED NONNULL((1, 2)) ATTR_SECTION(".text.kernel.handle_undefined.pwritev") size_t KCALL handle_undefined_pwritev(void *__restrict UNUSED(self), struct iov_buffer *__restrict UNUSED(src), size_t UNUSED(num_bytes), pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_PWRITE); }
INTERN WUNUSED NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.readdir") size_t KCALL handle_undefined_readdir(void *__restrict UNUSED(self), USER CHECKED struct dirent *UNUSED(buf), size_t UNUSED(bufsize), readdir_mode_t UNUSED(readdir_mode), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READDIR); }
INTERN NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.seek") pos_t KCALL handle_undefined_seek(void *__restrict UNUSED(self), off_t UNUSED(offset), unsigned int UNUSED(whence)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_SEEK); }
INTERN NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.ioctl") syscall_slong_t KCALL handle_undefined_ioctl(void *__restrict UNUSED(self), syscall_ulong_t cmd, USER UNCHECKED void *UNUSED(arg), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND, cmd); }
INTERN NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.truncate") void KCALL handle_undefined_truncate(void *__restrict UNUSED(self), pos_t UNUSED(new_size)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_TRUNC); }
INTERN NONNULL((1, 2)) ATTR_SECTION(".text.kernel.handle_undefined.mmap") void KCALL handle_undefined_mmap(void *__restrict UNUSED(self), struct handle_mmap_info *__restrict UNUSED(info)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_MMAP); }
INTERN NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.allocate") pos_t KCALL handle_undefined_allocate(void *__restrict UNUSED(self), fallocate_mode_t UNUSED(mode), pos_t UNUSED(start), pos_t UNUSED(length)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_ALLOCATE); }
INTERN NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.sync") void KCALL handle_undefined_sync(void *__restrict UNUSED(self)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_SYNC); }
INTERN NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.datasync") void KCALL handle_undefined_datasync(void *__restrict UNUSED(self)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_DATASYNC); }
INTERN NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.stat") void KCALL handle_undefined_stat(void *__restrict UNUSED(self), USER CHECKED struct stat *UNUSED(result)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_STAT); }
INTERN NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.pollconnect") void KCALL handle_undefined_pollconnect(void *__restrict UNUSED(self), poll_mode_t UNUSED(what)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_POLL); }
INTERN WUNUSED NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.polltest") poll_mode_t KCALL handle_undefined_polltest(void *__restrict UNUSED(self), poll_mode_t UNUSED(what)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_POLL); }
INTERN NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.hop") syscall_slong_t KCALL handle_undefined_hop(void *__restrict UNUSED(self), syscall_ulong_t cmd, USER UNCHECKED void *UNUSED(arg), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND, cmd); }
INTERN NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.tryas") REF void *KCALL handle_undefined_tryas(void *__restrict UNUSED(self), uintptr_half_t UNUSED(wanted_type)) THROWS(E_WOULDBLOCK) { return NULL; }


/* Handle type database */
PUBLIC_CONST struct handle_types const handle_type_db = {
	/* .h_typename = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ "undefined",
		/* [HANDLE_TYPE_FILE]                   = */ "file",
		/* [HANDLE_TYPE_SOCKET]                 = */ "socket",
		/* [HANDLE_TYPE_EPOLL]                  = */ "epoll",
		/* [HANDLE_TYPE_PIPE]                   = */ "pipe",
		/* [HANDLE_TYPE_PIPE_READER]            = */ "pipe_reader",
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ "pipe_writer",
		/* [HANDLE_TYPE_FIFO_USER]              = */ "fifo_user",
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ "eventfd_fence",
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ "eventfd_sema",
		/* [HANDLE_TYPE_SIGNALFD]               = */ "signalfd",
		/* [HANDLE_TYPE_FUTEX]                  = */ "futex",
		/* [HANDLE_TYPE_FUTEXFD]                = */ "futexfd",
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ "oneshot_directory_file",
		/* [HANDLE_TYPE_MFILE]                  = */ "mfile",
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ "blockdevice",
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ "directoryentry",
		/* [HANDLE_TYPE_PATH]                   = */ "path",
		/* [HANDLE_TYPE_FS]                     = */ "fs",
		/* [HANDLE_TYPE_MMAN]                   = */ "mman",
		/* [HANDLE_TYPE_TASK]                   = */ "task",
		/* [HANDLE_TYPE_MODULE]                 = */ "module",
		/* [HANDLE_TYPE_PIDNS]                  = */ "pidns",
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ "driver_loadlist",
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ "characterdevice",
		/* [HANDLE_TYPE_MPART]                  = */ "mpart",
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ "module_section"
	},
	/* .h_refcnt = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_undefined_refcnt,
		/* [HANDLE_TYPE_FILE]                   = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_file_refcnt,
		/* [HANDLE_TYPE_SOCKET]                 = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_socket_refcnt,
		/* [HANDLE_TYPE_EPOLL]                  = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_epoll_refcnt,
		/* [HANDLE_TYPE_PIPE]                   = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_pipe_refcnt,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_pipe_reader_refcnt,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_pipe_writer_refcnt,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_fifo_user_refcnt,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_eventfd_fence_refcnt,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_eventfd_sema_refcnt,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_signalfd_refcnt,
		/* [HANDLE_TYPE_FUTEX]                  = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_futex_refcnt,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_futexfd_refcnt,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_oneshot_directory_file_refcnt,
		/* [HANDLE_TYPE_MFILE]                  = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_mfile_refcnt,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_blockdevice_refcnt,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_directoryentry_refcnt,
		/* [HANDLE_TYPE_PATH]                   = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_path_refcnt,
		/* [HANDLE_TYPE_FS]                     = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_fs_refcnt,
		/* [HANDLE_TYPE_MMAN]                   = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_mman_refcnt,
		/* [HANDLE_TYPE_TASK]                   = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_task_refcnt,
		/* [HANDLE_TYPE_MODULE]                 = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_module_refcnt,
		/* [HANDLE_TYPE_PIDNS]                  = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_pidns_refcnt,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_driver_loadlist_refcnt,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_characterdevice_refcnt,
		/* [HANDLE_TYPE_MPART]                  = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_mpart_refcnt,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_module_section_refcnt
	},
	/* .h_incref = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (void (FCALL *)(void *__restrict))&handle_undefined_incref,
		/* [HANDLE_TYPE_FILE]                   = */ (void (FCALL *)(void *__restrict))&handle_file_incref,
		/* [HANDLE_TYPE_SOCKET]                 = */ (void (FCALL *)(void *__restrict))&handle_socket_incref,
		/* [HANDLE_TYPE_EPOLL]                  = */ (void (FCALL *)(void *__restrict))&handle_epoll_incref,
		/* [HANDLE_TYPE_PIPE]                   = */ (void (FCALL *)(void *__restrict))&handle_pipe_incref,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (void (FCALL *)(void *__restrict))&handle_pipe_reader_incref,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (void (FCALL *)(void *__restrict))&handle_pipe_writer_incref,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (void (FCALL *)(void *__restrict))&handle_fifo_user_incref,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (void (FCALL *)(void *__restrict))&handle_eventfd_fence_incref,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (void (FCALL *)(void *__restrict))&handle_eventfd_sema_incref,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (void (FCALL *)(void *__restrict))&handle_signalfd_incref,
		/* [HANDLE_TYPE_FUTEX]                  = */ (void (FCALL *)(void *__restrict))&handle_futex_incref,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (void (FCALL *)(void *__restrict))&handle_futexfd_incref,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (void (FCALL *)(void *__restrict))&handle_oneshot_directory_file_incref,
		/* [HANDLE_TYPE_MFILE]                  = */ (void (FCALL *)(void *__restrict))&handle_mfile_incref,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (void (FCALL *)(void *__restrict))&handle_blockdevice_incref,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (void (FCALL *)(void *__restrict))&handle_directoryentry_incref,
		/* [HANDLE_TYPE_PATH]                   = */ (void (FCALL *)(void *__restrict))&handle_path_incref,
		/* [HANDLE_TYPE_FS]                     = */ (void (FCALL *)(void *__restrict))&handle_fs_incref,
		/* [HANDLE_TYPE_MMAN]                   = */ (void (FCALL *)(void *__restrict))&handle_mman_incref,
		/* [HANDLE_TYPE_TASK]                   = */ (void (FCALL *)(void *__restrict))&handle_task_incref,
		/* [HANDLE_TYPE_MODULE]                 = */ (void (FCALL *)(void *__restrict))&handle_module_incref,
		/* [HANDLE_TYPE_PIDNS]                  = */ (void (FCALL *)(void *__restrict))&handle_pidns_incref,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (void (FCALL *)(void *__restrict))&handle_driver_loadlist_incref,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (void (FCALL *)(void *__restrict))&handle_characterdevice_incref,
		/* [HANDLE_TYPE_MPART]                  = */ (void (FCALL *)(void *__restrict))&handle_mpart_incref,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (void (FCALL *)(void *__restrict))&handle_module_section_incref
	},
	/* .h_decref = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (void (FCALL *)(REF void *__restrict))&handle_undefined_decref,
		/* [HANDLE_TYPE_FILE]                   = */ (void (FCALL *)(REF void *__restrict))&handle_file_decref,
		/* [HANDLE_TYPE_SOCKET]                 = */ (void (FCALL *)(REF void *__restrict))&handle_socket_decref,
		/* [HANDLE_TYPE_EPOLL]                  = */ (void (FCALL *)(REF void *__restrict))&handle_epoll_decref,
		/* [HANDLE_TYPE_PIPE]                   = */ (void (FCALL *)(REF void *__restrict))&handle_pipe_decref,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (void (FCALL *)(REF void *__restrict))&handle_pipe_reader_decref,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (void (FCALL *)(REF void *__restrict))&handle_pipe_writer_decref,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (void (FCALL *)(REF void *__restrict))&handle_fifo_user_decref,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (void (FCALL *)(REF void *__restrict))&handle_eventfd_fence_decref,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (void (FCALL *)(REF void *__restrict))&handle_eventfd_sema_decref,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (void (FCALL *)(REF void *__restrict))&handle_signalfd_decref,
		/* [HANDLE_TYPE_FUTEX]                  = */ (void (FCALL *)(REF void *__restrict))&handle_futex_decref,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (void (FCALL *)(REF void *__restrict))&handle_futexfd_decref,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (void (FCALL *)(REF void *__restrict))&handle_oneshot_directory_file_decref,
		/* [HANDLE_TYPE_MFILE]                  = */ (void (FCALL *)(REF void *__restrict))&handle_mfile_decref,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (void (FCALL *)(REF void *__restrict))&handle_blockdevice_decref,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (void (FCALL *)(REF void *__restrict))&handle_directoryentry_decref,
		/* [HANDLE_TYPE_PATH]                   = */ (void (FCALL *)(REF void *__restrict))&handle_path_decref,
		/* [HANDLE_TYPE_FS]                     = */ (void (FCALL *)(REF void *__restrict))&handle_fs_decref,
		/* [HANDLE_TYPE_MMAN]                   = */ (void (FCALL *)(REF void *__restrict))&handle_mman_decref,
		/* [HANDLE_TYPE_TASK]                   = */ (void (FCALL *)(REF void *__restrict))&handle_task_decref,
		/* [HANDLE_TYPE_MODULE]                 = */ (void (FCALL *)(REF void *__restrict))&handle_module_decref,
		/* [HANDLE_TYPE_PIDNS]                  = */ (void (FCALL *)(REF void *__restrict))&handle_pidns_decref,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (void (FCALL *)(REF void *__restrict))&handle_driver_loadlist_decref,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (void (FCALL *)(REF void *__restrict))&handle_characterdevice_decref,
		/* [HANDLE_TYPE_MPART]                  = */ (void (FCALL *)(REF void *__restrict))&handle_mpart_decref,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (void (FCALL *)(REF void *__restrict))&handle_module_section_decref
	},
	/* .h_tryincref = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (__BOOL (FCALL *)(void *__restrict))&handle_undefined_tryincref,
		/* [HANDLE_TYPE_FILE]                   = */ (__BOOL (FCALL *)(void *__restrict))&handle_file_tryincref,
		/* [HANDLE_TYPE_SOCKET]                 = */ (__BOOL (FCALL *)(void *__restrict))&handle_socket_tryincref,
		/* [HANDLE_TYPE_EPOLL]                  = */ (__BOOL (FCALL *)(void *__restrict))&handle_epoll_tryincref,
		/* [HANDLE_TYPE_PIPE]                   = */ (__BOOL (FCALL *)(void *__restrict))&handle_pipe_tryincref,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (__BOOL (FCALL *)(void *__restrict))&handle_pipe_reader_tryincref,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (__BOOL (FCALL *)(void *__restrict))&handle_pipe_writer_tryincref,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (__BOOL (FCALL *)(void *__restrict))&handle_fifo_user_tryincref,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (__BOOL (FCALL *)(void *__restrict))&handle_eventfd_fence_tryincref,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (__BOOL (FCALL *)(void *__restrict))&handle_eventfd_sema_tryincref,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (__BOOL (FCALL *)(void *__restrict))&handle_signalfd_tryincref,
		/* [HANDLE_TYPE_FUTEX]                  = */ (__BOOL (FCALL *)(void *__restrict))&handle_futex_tryincref,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (__BOOL (FCALL *)(void *__restrict))&handle_futexfd_tryincref,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (__BOOL (FCALL *)(void *__restrict))&handle_oneshot_directory_file_tryincref,
		/* [HANDLE_TYPE_MFILE]                  = */ (__BOOL (FCALL *)(void *__restrict))&handle_mfile_tryincref,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (__BOOL (FCALL *)(void *__restrict))&handle_blockdevice_tryincref,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (__BOOL (FCALL *)(void *__restrict))&handle_directoryentry_tryincref,
		/* [HANDLE_TYPE_PATH]                   = */ (__BOOL (FCALL *)(void *__restrict))&handle_path_tryincref,
		/* [HANDLE_TYPE_FS]                     = */ (__BOOL (FCALL *)(void *__restrict))&handle_fs_tryincref,
		/* [HANDLE_TYPE_MMAN]                   = */ (__BOOL (FCALL *)(void *__restrict))&handle_mman_tryincref,
		/* [HANDLE_TYPE_TASK]                   = */ (__BOOL (FCALL *)(void *__restrict))&handle_task_tryincref,
		/* [HANDLE_TYPE_MODULE]                 = */ (__BOOL (FCALL *)(void *__restrict))&handle_module_tryincref,
		/* [HANDLE_TYPE_PIDNS]                  = */ (__BOOL (FCALL *)(void *__restrict))&handle_pidns_tryincref,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (__BOOL (FCALL *)(void *__restrict))&handle_driver_loadlist_tryincref,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (__BOOL (FCALL *)(void *__restrict))&handle_characterdevice_tryincref,
		/* [HANDLE_TYPE_MPART]                  = */ (__BOOL (FCALL *)(void *__restrict))&handle_mpart_tryincref,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (__BOOL (FCALL *)(void *__restrict))&handle_module_section_tryincref
	},
	/* .h_weakgetref = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_undefined_weakgetref,
		/* [HANDLE_TYPE_FILE]                   = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_file_weakgetref,
		/* [HANDLE_TYPE_SOCKET]                 = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_socket_weakgetref,
		/* [HANDLE_TYPE_EPOLL]                  = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_epoll_weakgetref,
		/* [HANDLE_TYPE_PIPE]                   = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_pipe_weakgetref,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_pipe_reader_weakgetref,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_pipe_writer_weakgetref,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_fifo_user_weakgetref,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_eventfd_fence_weakgetref,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_eventfd_sema_weakgetref,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_signalfd_weakgetref,
		/* [HANDLE_TYPE_FUTEX]                  = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_futex_weakgetref,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_futexfd_weakgetref,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_oneshot_directory_file_weakgetref,
		/* [HANDLE_TYPE_MFILE]                  = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_mfile_weakgetref,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_blockdevice_weakgetref,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_directoryentry_weakgetref,
		/* [HANDLE_TYPE_PATH]                   = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_path_weakgetref,
		/* [HANDLE_TYPE_FS]                     = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_fs_weakgetref,
		/* [HANDLE_TYPE_MMAN]                   = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_mman_weakgetref,
		/* [HANDLE_TYPE_TASK]                   = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_task_weakgetref,
		/* [HANDLE_TYPE_MODULE]                 = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_module_weakgetref,
		/* [HANDLE_TYPE_PIDNS]                  = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_pidns_weakgetref,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_driver_loadlist_weakgetref,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_characterdevice_weakgetref,
		/* [HANDLE_TYPE_MPART]                  = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_mpart_weakgetref,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (WEAK REF void *(FCALL *)(void *__restrict))&handle_module_section_weakgetref
	},
	/* .h_weaklckref = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (REF void *(FCALL *)(void *__restrict))&handle_undefined_weaklckref,
		/* [HANDLE_TYPE_FILE]                   = */ (REF void *(FCALL *)(void *__restrict))&handle_file_weaklckref,
		/* [HANDLE_TYPE_SOCKET]                 = */ (REF void *(FCALL *)(void *__restrict))&handle_socket_weaklckref,
		/* [HANDLE_TYPE_EPOLL]                  = */ (REF void *(FCALL *)(void *__restrict))&handle_epoll_weaklckref,
		/* [HANDLE_TYPE_PIPE]                   = */ (REF void *(FCALL *)(void *__restrict))&handle_pipe_weaklckref,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (REF void *(FCALL *)(void *__restrict))&handle_pipe_reader_weaklckref,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (REF void *(FCALL *)(void *__restrict))&handle_pipe_writer_weaklckref,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (REF void *(FCALL *)(void *__restrict))&handle_fifo_user_weaklckref,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (REF void *(FCALL *)(void *__restrict))&handle_eventfd_fence_weaklckref,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (REF void *(FCALL *)(void *__restrict))&handle_eventfd_sema_weaklckref,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (REF void *(FCALL *)(void *__restrict))&handle_signalfd_weaklckref,
		/* [HANDLE_TYPE_FUTEX]                  = */ (REF void *(FCALL *)(void *__restrict))&handle_futex_weaklckref,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (REF void *(FCALL *)(void *__restrict))&handle_futexfd_weaklckref,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (REF void *(FCALL *)(void *__restrict))&handle_oneshot_directory_file_weaklckref,
		/* [HANDLE_TYPE_MFILE]                  = */ (REF void *(FCALL *)(void *__restrict))&handle_mfile_weaklckref,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (REF void *(FCALL *)(void *__restrict))&handle_blockdevice_weaklckref,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (REF void *(FCALL *)(void *__restrict))&handle_directoryentry_weaklckref,
		/* [HANDLE_TYPE_PATH]                   = */ (REF void *(FCALL *)(void *__restrict))&handle_path_weaklckref,
		/* [HANDLE_TYPE_FS]                     = */ (REF void *(FCALL *)(void *__restrict))&handle_fs_weaklckref,
		/* [HANDLE_TYPE_MMAN]                   = */ (REF void *(FCALL *)(void *__restrict))&handle_mman_weaklckref,
		/* [HANDLE_TYPE_TASK]                   = */ (REF void *(FCALL *)(void *__restrict))&handle_task_weaklckref,
		/* [HANDLE_TYPE_MODULE]                 = */ (REF void *(FCALL *)(void *__restrict))&handle_module_weaklckref,
		/* [HANDLE_TYPE_PIDNS]                  = */ (REF void *(FCALL *)(void *__restrict))&handle_pidns_weaklckref,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (REF void *(FCALL *)(void *__restrict))&handle_driver_loadlist_weaklckref,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (REF void *(FCALL *)(void *__restrict))&handle_characterdevice_weaklckref,
		/* [HANDLE_TYPE_MPART]                  = */ (REF void *(FCALL *)(void *__restrict))&handle_mpart_weaklckref,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (REF void *(FCALL *)(void *__restrict))&handle_module_section_weaklckref
	},
	/* .h_weakdecref = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_undefined_weakdecref,
		/* [HANDLE_TYPE_FILE]                   = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_file_weakdecref,
		/* [HANDLE_TYPE_SOCKET]                 = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_socket_weakdecref,
		/* [HANDLE_TYPE_EPOLL]                  = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_epoll_weakdecref,
		/* [HANDLE_TYPE_PIPE]                   = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_pipe_weakdecref,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_pipe_reader_weakdecref,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_pipe_writer_weakdecref,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_fifo_user_weakdecref,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_eventfd_fence_weakdecref,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_eventfd_sema_weakdecref,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_signalfd_weakdecref,
		/* [HANDLE_TYPE_FUTEX]                  = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_futex_weakdecref,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_futexfd_weakdecref,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_oneshot_directory_file_weakdecref,
		/* [HANDLE_TYPE_MFILE]                  = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_mfile_weakdecref,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_blockdevice_weakdecref,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_directoryentry_weakdecref,
		/* [HANDLE_TYPE_PATH]                   = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_path_weakdecref,
		/* [HANDLE_TYPE_FS]                     = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_fs_weakdecref,
		/* [HANDLE_TYPE_MMAN]                   = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_mman_weakdecref,
		/* [HANDLE_TYPE_TASK]                   = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_task_weakdecref,
		/* [HANDLE_TYPE_MODULE]                 = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_module_weakdecref,
		/* [HANDLE_TYPE_PIDNS]                  = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_pidns_weakdecref,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_driver_loadlist_weakdecref,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_characterdevice_weakdecref,
		/* [HANDLE_TYPE_MPART]                  = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_mpart_weakdecref,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (void (FCALL *)(WEAK REF void *__restrict))&handle_module_section_weakdecref
	},
	/* .h_read = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_undefined_read,
		/* [HANDLE_TYPE_FILE]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_file_read,
		/* [HANDLE_TYPE_SOCKET]                 = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_socket_read,
		/* [HANDLE_TYPE_EPOLL]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_epoll_read,
		/* [HANDLE_TYPE_PIPE]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_pipe_read,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_pipe_reader_read,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_pipe_writer_read,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_fifo_user_read,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_eventfd_fence_read,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_eventfd_sema_read,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_signalfd_read,
		/* [HANDLE_TYPE_FUTEX]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_futex_read,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_futexfd_read,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_oneshot_directory_file_read,
		/* [HANDLE_TYPE_MFILE]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_mfile_read,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_blockdevice_read,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_directoryentry_read,
		/* [HANDLE_TYPE_PATH]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_path_read,
		/* [HANDLE_TYPE_FS]                     = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_fs_read,
		/* [HANDLE_TYPE_MMAN]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_mman_read,
		/* [HANDLE_TYPE_TASK]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_task_read,
		/* [HANDLE_TYPE_MODULE]                 = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_module_read,
		/* [HANDLE_TYPE_PIDNS]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_pidns_read,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_driver_loadlist_read,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_characterdevice_read,
		/* [HANDLE_TYPE_MPART]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_mpart_read,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_module_section_read
	},
	/* .h_write = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_undefined_write,
		/* [HANDLE_TYPE_FILE]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_file_write,
		/* [HANDLE_TYPE_SOCKET]                 = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_socket_write,
		/* [HANDLE_TYPE_EPOLL]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_epoll_write,
		/* [HANDLE_TYPE_PIPE]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_pipe_write,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_pipe_reader_write,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_pipe_writer_write,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_fifo_user_write,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_eventfd_fence_write,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_eventfd_sema_write,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_signalfd_write,
		/* [HANDLE_TYPE_FUTEX]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_futex_write,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_futexfd_write,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_oneshot_directory_file_write,
		/* [HANDLE_TYPE_MFILE]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_mfile_write,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_blockdevice_write,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_directoryentry_write,
		/* [HANDLE_TYPE_PATH]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_path_write,
		/* [HANDLE_TYPE_FS]                     = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_fs_write,
		/* [HANDLE_TYPE_MMAN]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_mman_write,
		/* [HANDLE_TYPE_TASK]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_task_write,
		/* [HANDLE_TYPE_MODULE]                 = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_module_write,
		/* [HANDLE_TYPE_PIDNS]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_pidns_write,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_driver_loadlist_write,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_characterdevice_write,
		/* [HANDLE_TYPE_MPART]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_mpart_write,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_module_section_write
	},
	/* .h_pread = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_undefined_pread,
		/* [HANDLE_TYPE_FILE]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_file_pread,
		/* [HANDLE_TYPE_SOCKET]                 = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_socket_pread,
		/* [HANDLE_TYPE_EPOLL]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_epoll_pread,
		/* [HANDLE_TYPE_PIPE]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_pipe_pread,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_pipe_reader_pread,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_pipe_writer_pread,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_fifo_user_pread,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_eventfd_fence_pread,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_eventfd_sema_pread,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_signalfd_pread,
		/* [HANDLE_TYPE_FUTEX]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_futex_pread,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_futexfd_pread,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_oneshot_directory_file_pread,
		/* [HANDLE_TYPE_MFILE]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_mfile_pread,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_blockdevice_pread,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_directoryentry_pread,
		/* [HANDLE_TYPE_PATH]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_path_pread,
		/* [HANDLE_TYPE_FS]                     = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_fs_pread,
		/* [HANDLE_TYPE_MMAN]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_mman_pread,
		/* [HANDLE_TYPE_TASK]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_task_pread,
		/* [HANDLE_TYPE_MODULE]                 = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_module_pread,
		/* [HANDLE_TYPE_PIDNS]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_pidns_pread,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_driver_loadlist_pread,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_characterdevice_pread,
		/* [HANDLE_TYPE_MPART]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_mpart_pread,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_module_section_pread
	},
	/* .h_pwrite = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_undefined_pwrite,
		/* [HANDLE_TYPE_FILE]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_file_pwrite,
		/* [HANDLE_TYPE_SOCKET]                 = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_socket_pwrite,
		/* [HANDLE_TYPE_EPOLL]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_epoll_pwrite,
		/* [HANDLE_TYPE_PIPE]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_pipe_pwrite,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_pipe_reader_pwrite,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_pipe_writer_pwrite,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_fifo_user_pwrite,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_eventfd_fence_pwrite,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_eventfd_sema_pwrite,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_signalfd_pwrite,
		/* [HANDLE_TYPE_FUTEX]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_futex_pwrite,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_futexfd_pwrite,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_oneshot_directory_file_pwrite,
		/* [HANDLE_TYPE_MFILE]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_mfile_pwrite,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_blockdevice_pwrite,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_directoryentry_pwrite,
		/* [HANDLE_TYPE_PATH]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_path_pwrite,
		/* [HANDLE_TYPE_FS]                     = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_fs_pwrite,
		/* [HANDLE_TYPE_MMAN]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_mman_pwrite,
		/* [HANDLE_TYPE_TASK]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_task_pwrite,
		/* [HANDLE_TYPE_MODULE]                 = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_module_pwrite,
		/* [HANDLE_TYPE_PIDNS]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_pidns_pwrite,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_driver_loadlist_pwrite,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_characterdevice_pwrite,
		/* [HANDLE_TYPE_MPART]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_mpart_pwrite,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_module_section_pwrite
	},
	/* .h_readv = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_undefined_readv,
		/* [HANDLE_TYPE_FILE]                   = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_file_readv,
		/* [HANDLE_TYPE_SOCKET]                 = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_socket_readv,
		/* [HANDLE_TYPE_EPOLL]                  = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_epoll_readv,
		/* [HANDLE_TYPE_PIPE]                   = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_pipe_readv,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_pipe_reader_readv,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_pipe_writer_readv,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_fifo_user_readv,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_eventfd_fence_readv,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_eventfd_sema_readv,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_signalfd_readv,
		/* [HANDLE_TYPE_FUTEX]                  = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_futex_readv,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_futexfd_readv,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_oneshot_directory_file_readv,
		/* [HANDLE_TYPE_MFILE]                  = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_mfile_readv,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_blockdevice_readv,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_directoryentry_readv,
		/* [HANDLE_TYPE_PATH]                   = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_path_readv,
		/* [HANDLE_TYPE_FS]                     = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_fs_readv,
		/* [HANDLE_TYPE_MMAN]                   = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_mman_readv,
		/* [HANDLE_TYPE_TASK]                   = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_task_readv,
		/* [HANDLE_TYPE_MODULE]                 = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_module_readv,
		/* [HANDLE_TYPE_PIDNS]                  = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_pidns_readv,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_driver_loadlist_readv,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_characterdevice_readv,
		/* [HANDLE_TYPE_MPART]                  = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_mpart_readv,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_module_section_readv
	},
	/* .h_writev = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_undefined_writev,
		/* [HANDLE_TYPE_FILE]                   = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_file_writev,
		/* [HANDLE_TYPE_SOCKET]                 = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_socket_writev,
		/* [HANDLE_TYPE_EPOLL]                  = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_epoll_writev,
		/* [HANDLE_TYPE_PIPE]                   = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_pipe_writev,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_pipe_reader_writev,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_pipe_writer_writev,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_fifo_user_writev,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_eventfd_fence_writev,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_eventfd_sema_writev,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_signalfd_writev,
		/* [HANDLE_TYPE_FUTEX]                  = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_futex_writev,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_futexfd_writev,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_oneshot_directory_file_writev,
		/* [HANDLE_TYPE_MFILE]                  = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_mfile_writev,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_blockdevice_writev,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_directoryentry_writev,
		/* [HANDLE_TYPE_PATH]                   = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_path_writev,
		/* [HANDLE_TYPE_FS]                     = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_fs_writev,
		/* [HANDLE_TYPE_MMAN]                   = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_mman_writev,
		/* [HANDLE_TYPE_TASK]                   = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_task_writev,
		/* [HANDLE_TYPE_MODULE]                 = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_module_writev,
		/* [HANDLE_TYPE_PIDNS]                  = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_pidns_writev,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_driver_loadlist_writev,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_characterdevice_writev,
		/* [HANDLE_TYPE_MPART]                  = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_mpart_writev,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_module_section_writev
	},
	/* .h_preadv = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_undefined_preadv,
		/* [HANDLE_TYPE_FILE]                   = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_file_preadv,
		/* [HANDLE_TYPE_SOCKET]                 = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_socket_preadv,
		/* [HANDLE_TYPE_EPOLL]                  = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_epoll_preadv,
		/* [HANDLE_TYPE_PIPE]                   = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_pipe_preadv,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_pipe_reader_preadv,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_pipe_writer_preadv,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_fifo_user_preadv,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_eventfd_fence_preadv,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_eventfd_sema_preadv,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_signalfd_preadv,
		/* [HANDLE_TYPE_FUTEX]                  = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_futex_preadv,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_futexfd_preadv,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_oneshot_directory_file_preadv,
		/* [HANDLE_TYPE_MFILE]                  = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_mfile_preadv,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_blockdevice_preadv,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_directoryentry_preadv,
		/* [HANDLE_TYPE_PATH]                   = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_path_preadv,
		/* [HANDLE_TYPE_FS]                     = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_fs_preadv,
		/* [HANDLE_TYPE_MMAN]                   = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_mman_preadv,
		/* [HANDLE_TYPE_TASK]                   = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_task_preadv,
		/* [HANDLE_TYPE_MODULE]                 = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_module_preadv,
		/* [HANDLE_TYPE_PIDNS]                  = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_pidns_preadv,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_driver_loadlist_preadv,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_characterdevice_preadv,
		/* [HANDLE_TYPE_MPART]                  = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_mpart_preadv,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_module_section_preadv
	},
	/* .h_pwritev = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_undefined_pwritev,
		/* [HANDLE_TYPE_FILE]                   = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_file_pwritev,
		/* [HANDLE_TYPE_SOCKET]                 = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_socket_pwritev,
		/* [HANDLE_TYPE_EPOLL]                  = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_epoll_pwritev,
		/* [HANDLE_TYPE_PIPE]                   = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_pipe_pwritev,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_pipe_reader_pwritev,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_pipe_writer_pwritev,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_fifo_user_pwritev,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_eventfd_fence_pwritev,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_eventfd_sema_pwritev,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_signalfd_pwritev,
		/* [HANDLE_TYPE_FUTEX]                  = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_futex_pwritev,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_futexfd_pwritev,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_oneshot_directory_file_pwritev,
		/* [HANDLE_TYPE_MFILE]                  = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_mfile_pwritev,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_blockdevice_pwritev,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_directoryentry_pwritev,
		/* [HANDLE_TYPE_PATH]                   = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_path_pwritev,
		/* [HANDLE_TYPE_FS]                     = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_fs_pwritev,
		/* [HANDLE_TYPE_MMAN]                   = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_mman_pwritev,
		/* [HANDLE_TYPE_TASK]                   = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_task_pwritev,
		/* [HANDLE_TYPE_MODULE]                 = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_module_pwritev,
		/* [HANDLE_TYPE_PIDNS]                  = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_pidns_pwritev,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_driver_loadlist_pwritev,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_characterdevice_pwritev,
		/* [HANDLE_TYPE_MPART]                  = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_mpart_pwritev,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_module_section_pwritev
	},
	/* .h_readdir = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_undefined_readdir,
		/* [HANDLE_TYPE_FILE]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_file_readdir,
		/* [HANDLE_TYPE_SOCKET]                 = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_socket_readdir,
		/* [HANDLE_TYPE_EPOLL]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_epoll_readdir,
		/* [HANDLE_TYPE_PIPE]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_pipe_readdir,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_pipe_reader_readdir,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_pipe_writer_readdir,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_fifo_user_readdir,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_eventfd_fence_readdir,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_eventfd_sema_readdir,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_signalfd_readdir,
		/* [HANDLE_TYPE_FUTEX]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_futex_readdir,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_futexfd_readdir,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_oneshot_directory_file_readdir,
		/* [HANDLE_TYPE_MFILE]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_mfile_readdir,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_blockdevice_readdir,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_directoryentry_readdir,
		/* [HANDLE_TYPE_PATH]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_path_readdir,
		/* [HANDLE_TYPE_FS]                     = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_fs_readdir,
		/* [HANDLE_TYPE_MMAN]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_mman_readdir,
		/* [HANDLE_TYPE_TASK]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_task_readdir,
		/* [HANDLE_TYPE_MODULE]                 = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_module_readdir,
		/* [HANDLE_TYPE_PIDNS]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_pidns_readdir,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_driver_loadlist_readdir,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_characterdevice_readdir,
		/* [HANDLE_TYPE_MPART]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_mpart_readdir,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_module_section_readdir
	},
	/* .h_seek = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_undefined_seek,
		/* [HANDLE_TYPE_FILE]                   = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_file_seek,
		/* [HANDLE_TYPE_SOCKET]                 = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_socket_seek,
		/* [HANDLE_TYPE_EPOLL]                  = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_epoll_seek,
		/* [HANDLE_TYPE_PIPE]                   = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_pipe_seek,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_pipe_reader_seek,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_pipe_writer_seek,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_fifo_user_seek,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_eventfd_fence_seek,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_eventfd_sema_seek,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_signalfd_seek,
		/* [HANDLE_TYPE_FUTEX]                  = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_futex_seek,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_futexfd_seek,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_oneshot_directory_file_seek,
		/* [HANDLE_TYPE_MFILE]                  = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_mfile_seek,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_blockdevice_seek,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_directoryentry_seek,
		/* [HANDLE_TYPE_PATH]                   = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_path_seek,
		/* [HANDLE_TYPE_FS]                     = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_fs_seek,
		/* [HANDLE_TYPE_MMAN]                   = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_mman_seek,
		/* [HANDLE_TYPE_TASK]                   = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_task_seek,
		/* [HANDLE_TYPE_MODULE]                 = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_module_seek,
		/* [HANDLE_TYPE_PIDNS]                  = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_pidns_seek,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_driver_loadlist_seek,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_characterdevice_seek,
		/* [HANDLE_TYPE_MPART]                  = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_mpart_seek,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_module_section_seek
	},
	/* .h_ioctl = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_undefined_ioctl,
		/* [HANDLE_TYPE_FILE]                   = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_file_ioctl,
		/* [HANDLE_TYPE_SOCKET]                 = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_socket_ioctl,
		/* [HANDLE_TYPE_EPOLL]                  = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_epoll_ioctl,
		/* [HANDLE_TYPE_PIPE]                   = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_pipe_ioctl,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_pipe_reader_ioctl,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_pipe_writer_ioctl,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_fifo_user_ioctl,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_eventfd_fence_ioctl,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_eventfd_sema_ioctl,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_signalfd_ioctl,
		/* [HANDLE_TYPE_FUTEX]                  = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_futex_ioctl,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_futexfd_ioctl,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_oneshot_directory_file_ioctl,
		/* [HANDLE_TYPE_MFILE]                  = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_mfile_ioctl,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_blockdevice_ioctl,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_directoryentry_ioctl,
		/* [HANDLE_TYPE_PATH]                   = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_path_ioctl,
		/* [HANDLE_TYPE_FS]                     = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_fs_ioctl,
		/* [HANDLE_TYPE_MMAN]                   = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_mman_ioctl,
		/* [HANDLE_TYPE_TASK]                   = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_task_ioctl,
		/* [HANDLE_TYPE_MODULE]                 = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_module_ioctl,
		/* [HANDLE_TYPE_PIDNS]                  = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_pidns_ioctl,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_driver_loadlist_ioctl,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_characterdevice_ioctl,
		/* [HANDLE_TYPE_MPART]                  = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_mpart_ioctl,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_module_section_ioctl
	},
	/* .h_truncate = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (void (KCALL *)(void *__restrict, pos_t))&handle_undefined_truncate,
		/* [HANDLE_TYPE_FILE]                   = */ (void (KCALL *)(void *__restrict, pos_t))&handle_file_truncate,
		/* [HANDLE_TYPE_SOCKET]                 = */ (void (KCALL *)(void *__restrict, pos_t))&handle_socket_truncate,
		/* [HANDLE_TYPE_EPOLL]                  = */ (void (KCALL *)(void *__restrict, pos_t))&handle_epoll_truncate,
		/* [HANDLE_TYPE_PIPE]                   = */ (void (KCALL *)(void *__restrict, pos_t))&handle_pipe_truncate,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (void (KCALL *)(void *__restrict, pos_t))&handle_pipe_reader_truncate,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (void (KCALL *)(void *__restrict, pos_t))&handle_pipe_writer_truncate,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (void (KCALL *)(void *__restrict, pos_t))&handle_fifo_user_truncate,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (void (KCALL *)(void *__restrict, pos_t))&handle_eventfd_fence_truncate,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (void (KCALL *)(void *__restrict, pos_t))&handle_eventfd_sema_truncate,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (void (KCALL *)(void *__restrict, pos_t))&handle_signalfd_truncate,
		/* [HANDLE_TYPE_FUTEX]                  = */ (void (KCALL *)(void *__restrict, pos_t))&handle_futex_truncate,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (void (KCALL *)(void *__restrict, pos_t))&handle_futexfd_truncate,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (void (KCALL *)(void *__restrict, pos_t))&handle_oneshot_directory_file_truncate,
		/* [HANDLE_TYPE_MFILE]                  = */ (void (KCALL *)(void *__restrict, pos_t))&handle_mfile_truncate,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (void (KCALL *)(void *__restrict, pos_t))&handle_blockdevice_truncate,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (void (KCALL *)(void *__restrict, pos_t))&handle_directoryentry_truncate,
		/* [HANDLE_TYPE_PATH]                   = */ (void (KCALL *)(void *__restrict, pos_t))&handle_path_truncate,
		/* [HANDLE_TYPE_FS]                     = */ (void (KCALL *)(void *__restrict, pos_t))&handle_fs_truncate,
		/* [HANDLE_TYPE_MMAN]                   = */ (void (KCALL *)(void *__restrict, pos_t))&handle_mman_truncate,
		/* [HANDLE_TYPE_TASK]                   = */ (void (KCALL *)(void *__restrict, pos_t))&handle_task_truncate,
		/* [HANDLE_TYPE_MODULE]                 = */ (void (KCALL *)(void *__restrict, pos_t))&handle_module_truncate,
		/* [HANDLE_TYPE_PIDNS]                  = */ (void (KCALL *)(void *__restrict, pos_t))&handle_pidns_truncate,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (void (KCALL *)(void *__restrict, pos_t))&handle_driver_loadlist_truncate,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (void (KCALL *)(void *__restrict, pos_t))&handle_characterdevice_truncate,
		/* [HANDLE_TYPE_MPART]                  = */ (void (KCALL *)(void *__restrict, pos_t))&handle_mpart_truncate,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (void (KCALL *)(void *__restrict, pos_t))&handle_module_section_truncate
	},
	/* .h_mmap = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_undefined_mmap,
		/* [HANDLE_TYPE_FILE]                   = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_file_mmap,
		/* [HANDLE_TYPE_SOCKET]                 = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_socket_mmap,
		/* [HANDLE_TYPE_EPOLL]                  = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_epoll_mmap,
		/* [HANDLE_TYPE_PIPE]                   = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_pipe_mmap,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_pipe_reader_mmap,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_pipe_writer_mmap,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_fifo_user_mmap,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_eventfd_fence_mmap,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_eventfd_sema_mmap,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_signalfd_mmap,
		/* [HANDLE_TYPE_FUTEX]                  = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_futex_mmap,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_futexfd_mmap,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_oneshot_directory_file_mmap,
		/* [HANDLE_TYPE_MFILE]                  = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_mfile_mmap,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_blockdevice_mmap,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_directoryentry_mmap,
		/* [HANDLE_TYPE_PATH]                   = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_path_mmap,
		/* [HANDLE_TYPE_FS]                     = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_fs_mmap,
		/* [HANDLE_TYPE_MMAN]                   = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_mman_mmap,
		/* [HANDLE_TYPE_TASK]                   = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_task_mmap,
		/* [HANDLE_TYPE_MODULE]                 = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_module_mmap,
		/* [HANDLE_TYPE_PIDNS]                  = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_pidns_mmap,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_driver_loadlist_mmap,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_characterdevice_mmap,
		/* [HANDLE_TYPE_MPART]                  = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_mpart_mmap,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_module_section_mmap
	},
	/* .h_allocate = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_undefined_allocate,
		/* [HANDLE_TYPE_FILE]                   = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_file_allocate,
		/* [HANDLE_TYPE_SOCKET]                 = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_socket_allocate,
		/* [HANDLE_TYPE_EPOLL]                  = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_epoll_allocate,
		/* [HANDLE_TYPE_PIPE]                   = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_pipe_allocate,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_pipe_reader_allocate,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_pipe_writer_allocate,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_fifo_user_allocate,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_eventfd_fence_allocate,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_eventfd_sema_allocate,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_signalfd_allocate,
		/* [HANDLE_TYPE_FUTEX]                  = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_futex_allocate,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_futexfd_allocate,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_oneshot_directory_file_allocate,
		/* [HANDLE_TYPE_MFILE]                  = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_mfile_allocate,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_blockdevice_allocate,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_directoryentry_allocate,
		/* [HANDLE_TYPE_PATH]                   = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_path_allocate,
		/* [HANDLE_TYPE_FS]                     = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_fs_allocate,
		/* [HANDLE_TYPE_MMAN]                   = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_mman_allocate,
		/* [HANDLE_TYPE_TASK]                   = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_task_allocate,
		/* [HANDLE_TYPE_MODULE]                 = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_module_allocate,
		/* [HANDLE_TYPE_PIDNS]                  = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_pidns_allocate,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_driver_loadlist_allocate,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_characterdevice_allocate,
		/* [HANDLE_TYPE_MPART]                  = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_mpart_allocate,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_module_section_allocate
	},
	/* .h_sync = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (void (KCALL *)(void *__restrict))&handle_undefined_sync,
		/* [HANDLE_TYPE_FILE]                   = */ (void (KCALL *)(void *__restrict))&handle_file_sync,
		/* [HANDLE_TYPE_SOCKET]                 = */ (void (KCALL *)(void *__restrict))&handle_socket_sync,
		/* [HANDLE_TYPE_EPOLL]                  = */ (void (KCALL *)(void *__restrict))&handle_epoll_sync,
		/* [HANDLE_TYPE_PIPE]                   = */ (void (KCALL *)(void *__restrict))&handle_pipe_sync,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (void (KCALL *)(void *__restrict))&handle_pipe_reader_sync,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (void (KCALL *)(void *__restrict))&handle_pipe_writer_sync,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (void (KCALL *)(void *__restrict))&handle_fifo_user_sync,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (void (KCALL *)(void *__restrict))&handle_eventfd_fence_sync,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (void (KCALL *)(void *__restrict))&handle_eventfd_sema_sync,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (void (KCALL *)(void *__restrict))&handle_signalfd_sync,
		/* [HANDLE_TYPE_FUTEX]                  = */ (void (KCALL *)(void *__restrict))&handle_futex_sync,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (void (KCALL *)(void *__restrict))&handle_futexfd_sync,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (void (KCALL *)(void *__restrict))&handle_oneshot_directory_file_sync,
		/* [HANDLE_TYPE_MFILE]                  = */ (void (KCALL *)(void *__restrict))&handle_mfile_sync,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (void (KCALL *)(void *__restrict))&handle_blockdevice_sync,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (void (KCALL *)(void *__restrict))&handle_directoryentry_sync,
		/* [HANDLE_TYPE_PATH]                   = */ (void (KCALL *)(void *__restrict))&handle_path_sync,
		/* [HANDLE_TYPE_FS]                     = */ (void (KCALL *)(void *__restrict))&handle_fs_sync,
		/* [HANDLE_TYPE_MMAN]                   = */ (void (KCALL *)(void *__restrict))&handle_mman_sync,
		/* [HANDLE_TYPE_TASK]                   = */ (void (KCALL *)(void *__restrict))&handle_task_sync,
		/* [HANDLE_TYPE_MODULE]                 = */ (void (KCALL *)(void *__restrict))&handle_module_sync,
		/* [HANDLE_TYPE_PIDNS]                  = */ (void (KCALL *)(void *__restrict))&handle_pidns_sync,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (void (KCALL *)(void *__restrict))&handle_driver_loadlist_sync,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (void (KCALL *)(void *__restrict))&handle_characterdevice_sync,
		/* [HANDLE_TYPE_MPART]                  = */ (void (KCALL *)(void *__restrict))&handle_mpart_sync,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (void (KCALL *)(void *__restrict))&handle_module_section_sync
	},
	/* .h_datasync = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (void (KCALL *)(void *__restrict))&handle_undefined_datasync,
		/* [HANDLE_TYPE_FILE]                   = */ (void (KCALL *)(void *__restrict))&handle_file_datasync,
		/* [HANDLE_TYPE_SOCKET]                 = */ (void (KCALL *)(void *__restrict))&handle_socket_datasync,
		/* [HANDLE_TYPE_EPOLL]                  = */ (void (KCALL *)(void *__restrict))&handle_epoll_datasync,
		/* [HANDLE_TYPE_PIPE]                   = */ (void (KCALL *)(void *__restrict))&handle_pipe_datasync,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (void (KCALL *)(void *__restrict))&handle_pipe_reader_datasync,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (void (KCALL *)(void *__restrict))&handle_pipe_writer_datasync,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (void (KCALL *)(void *__restrict))&handle_fifo_user_datasync,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (void (KCALL *)(void *__restrict))&handle_eventfd_fence_datasync,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (void (KCALL *)(void *__restrict))&handle_eventfd_sema_datasync,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (void (KCALL *)(void *__restrict))&handle_signalfd_datasync,
		/* [HANDLE_TYPE_FUTEX]                  = */ (void (KCALL *)(void *__restrict))&handle_futex_datasync,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (void (KCALL *)(void *__restrict))&handle_futexfd_datasync,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (void (KCALL *)(void *__restrict))&handle_oneshot_directory_file_datasync,
		/* [HANDLE_TYPE_MFILE]                  = */ (void (KCALL *)(void *__restrict))&handle_mfile_datasync,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (void (KCALL *)(void *__restrict))&handle_blockdevice_datasync,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (void (KCALL *)(void *__restrict))&handle_directoryentry_datasync,
		/* [HANDLE_TYPE_PATH]                   = */ (void (KCALL *)(void *__restrict))&handle_path_datasync,
		/* [HANDLE_TYPE_FS]                     = */ (void (KCALL *)(void *__restrict))&handle_fs_datasync,
		/* [HANDLE_TYPE_MMAN]                   = */ (void (KCALL *)(void *__restrict))&handle_mman_datasync,
		/* [HANDLE_TYPE_TASK]                   = */ (void (KCALL *)(void *__restrict))&handle_task_datasync,
		/* [HANDLE_TYPE_MODULE]                 = */ (void (KCALL *)(void *__restrict))&handle_module_datasync,
		/* [HANDLE_TYPE_PIDNS]                  = */ (void (KCALL *)(void *__restrict))&handle_pidns_datasync,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (void (KCALL *)(void *__restrict))&handle_driver_loadlist_datasync,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (void (KCALL *)(void *__restrict))&handle_characterdevice_datasync,
		/* [HANDLE_TYPE_MPART]                  = */ (void (KCALL *)(void *__restrict))&handle_mpart_datasync,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (void (KCALL *)(void *__restrict))&handle_module_section_datasync
	},
	/* .h_stat = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_undefined_stat,
		/* [HANDLE_TYPE_FILE]                   = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_file_stat,
		/* [HANDLE_TYPE_SOCKET]                 = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_socket_stat,
		/* [HANDLE_TYPE_EPOLL]                  = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_epoll_stat,
		/* [HANDLE_TYPE_PIPE]                   = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_pipe_stat,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_pipe_reader_stat,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_pipe_writer_stat,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_fifo_user_stat,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_eventfd_fence_stat,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_eventfd_sema_stat,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_signalfd_stat,
		/* [HANDLE_TYPE_FUTEX]                  = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_futex_stat,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_futexfd_stat,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_oneshot_directory_file_stat,
		/* [HANDLE_TYPE_MFILE]                  = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_mfile_stat,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_blockdevice_stat,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_directoryentry_stat,
		/* [HANDLE_TYPE_PATH]                   = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_path_stat,
		/* [HANDLE_TYPE_FS]                     = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_fs_stat,
		/* [HANDLE_TYPE_MMAN]                   = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_mman_stat,
		/* [HANDLE_TYPE_TASK]                   = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_task_stat,
		/* [HANDLE_TYPE_MODULE]                 = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_module_stat,
		/* [HANDLE_TYPE_PIDNS]                  = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_pidns_stat,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_driver_loadlist_stat,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_characterdevice_stat,
		/* [HANDLE_TYPE_MPART]                  = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_mpart_stat,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_module_section_stat
	},
	/* .h_pollconnect = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_undefined_pollconnect,
		/* [HANDLE_TYPE_FILE]                   = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_file_pollconnect,
		/* [HANDLE_TYPE_SOCKET]                 = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_socket_pollconnect,
		/* [HANDLE_TYPE_EPOLL]                  = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_epoll_pollconnect,
		/* [HANDLE_TYPE_PIPE]                   = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_pipe_pollconnect,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_pipe_reader_pollconnect,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_pipe_writer_pollconnect,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_fifo_user_pollconnect,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_eventfd_fence_pollconnect,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_eventfd_sema_pollconnect,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_signalfd_pollconnect,
		/* [HANDLE_TYPE_FUTEX]                  = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_futex_pollconnect,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_futexfd_pollconnect,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_oneshot_directory_file_pollconnect,
		/* [HANDLE_TYPE_MFILE]                  = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_mfile_pollconnect,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_blockdevice_pollconnect,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_directoryentry_pollconnect,
		/* [HANDLE_TYPE_PATH]                   = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_path_pollconnect,
		/* [HANDLE_TYPE_FS]                     = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_fs_pollconnect,
		/* [HANDLE_TYPE_MMAN]                   = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_mman_pollconnect,
		/* [HANDLE_TYPE_TASK]                   = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_task_pollconnect,
		/* [HANDLE_TYPE_MODULE]                 = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_module_pollconnect,
		/* [HANDLE_TYPE_PIDNS]                  = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_pidns_pollconnect,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_driver_loadlist_pollconnect,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_characterdevice_pollconnect,
		/* [HANDLE_TYPE_MPART]                  = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_mpart_pollconnect,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (void (KCALL *)(void *__restrict, poll_mode_t))&handle_module_section_pollconnect
	},
	/* .h_polltest = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_undefined_polltest,
		/* [HANDLE_TYPE_FILE]                   = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_file_polltest,
		/* [HANDLE_TYPE_SOCKET]                 = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_socket_polltest,
		/* [HANDLE_TYPE_EPOLL]                  = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_epoll_polltest,
		/* [HANDLE_TYPE_PIPE]                   = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_pipe_polltest,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_pipe_reader_polltest,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_pipe_writer_polltest,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_fifo_user_polltest,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_eventfd_fence_polltest,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_eventfd_sema_polltest,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_signalfd_polltest,
		/* [HANDLE_TYPE_FUTEX]                  = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_futex_polltest,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_futexfd_polltest,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_oneshot_directory_file_polltest,
		/* [HANDLE_TYPE_MFILE]                  = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_mfile_polltest,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_blockdevice_polltest,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_directoryentry_polltest,
		/* [HANDLE_TYPE_PATH]                   = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_path_polltest,
		/* [HANDLE_TYPE_FS]                     = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_fs_polltest,
		/* [HANDLE_TYPE_MMAN]                   = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_mman_polltest,
		/* [HANDLE_TYPE_TASK]                   = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_task_polltest,
		/* [HANDLE_TYPE_MODULE]                 = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_module_polltest,
		/* [HANDLE_TYPE_PIDNS]                  = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_pidns_polltest,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_driver_loadlist_polltest,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_characterdevice_polltest,
		/* [HANDLE_TYPE_MPART]                  = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_mpart_polltest,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_module_section_polltest
	},
	/* .h_hop = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_undefined_hop,
		/* [HANDLE_TYPE_FILE]                   = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_file_hop,
		/* [HANDLE_TYPE_SOCKET]                 = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_socket_hop,
		/* [HANDLE_TYPE_EPOLL]                  = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_epoll_hop,
		/* [HANDLE_TYPE_PIPE]                   = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_pipe_hop,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_pipe_reader_hop,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_pipe_writer_hop,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_fifo_user_hop,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_eventfd_fence_hop,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_eventfd_sema_hop,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_signalfd_hop,
		/* [HANDLE_TYPE_FUTEX]                  = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_futex_hop,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_futexfd_hop,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_oneshot_directory_file_hop,
		/* [HANDLE_TYPE_MFILE]                  = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_mfile_hop,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_blockdevice_hop,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_directoryentry_hop,
		/* [HANDLE_TYPE_PATH]                   = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_path_hop,
		/* [HANDLE_TYPE_FS]                     = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_fs_hop,
		/* [HANDLE_TYPE_MMAN]                   = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_mman_hop,
		/* [HANDLE_TYPE_TASK]                   = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_task_hop,
		/* [HANDLE_TYPE_MODULE]                 = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_module_hop,
		/* [HANDLE_TYPE_PIDNS]                  = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_pidns_hop,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_driver_loadlist_hop,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_characterdevice_hop,
		/* [HANDLE_TYPE_MPART]                  = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_mpart_hop,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_module_section_hop
	},
	/* .h_tryas = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_undefined_tryas,
		/* [HANDLE_TYPE_FILE]                   = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_file_tryas,
		/* [HANDLE_TYPE_SOCKET]                 = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_socket_tryas,
		/* [HANDLE_TYPE_EPOLL]                  = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_epoll_tryas,
		/* [HANDLE_TYPE_PIPE]                   = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_pipe_tryas,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_pipe_reader_tryas,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_pipe_writer_tryas,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_fifo_user_tryas,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_eventfd_fence_tryas,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_eventfd_sema_tryas,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_signalfd_tryas,
		/* [HANDLE_TYPE_FUTEX]                  = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_futex_tryas,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_futexfd_tryas,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_oneshot_directory_file_tryas,
		/* [HANDLE_TYPE_MFILE]                  = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_mfile_tryas,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_blockdevice_tryas,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_directoryentry_tryas,
		/* [HANDLE_TYPE_PATH]                   = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_path_tryas,
		/* [HANDLE_TYPE_FS]                     = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_fs_tryas,
		/* [HANDLE_TYPE_MMAN]                   = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_mman_tryas,
		/* [HANDLE_TYPE_TASK]                   = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_task_tryas,
		/* [HANDLE_TYPE_MODULE]                 = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_module_tryas,
		/* [HANDLE_TYPE_PIDNS]                  = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_pidns_tryas,
		/* [HANDLE_TYPE_DRIVER_LOADLIST]        = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_driver_loadlist_tryas,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_characterdevice_tryas,
		/* [HANDLE_TYPE_MPART]                  = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_mpart_tryas,
		/* [HANDLE_TYPE_MODULE_SECTION]         = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_module_section_tryas
	},
};



/* Weakly define operators for `HANDLE_TYPE_FILE' (`struct file') */
DEFINE_INTERN_WEAK_ALIAS(handle_file_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_file_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_file_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_file_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_file_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_file_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_file_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_file_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_file_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_file_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_file_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_file_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_file_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_file_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_file_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_file_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_file_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_file_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_file_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_file_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_file_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_file_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_file_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_file_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_file_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_file_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_file_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_file_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_SOCKET' (`struct socket') */
DEFINE_INTERN_WEAK_ALIAS(handle_socket_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_EPOLL' (`struct epoll_controller') */
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_PIPE' (`struct pipe') */
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_PIPE_READER' (`struct pipe_reader') */
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_PIPE_WRITER' (`struct pipe_writer') */
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_FIFO_USER' (`struct fifo_user') */
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_EVENTFD_FENCE' (`struct eventfd') */
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_EVENTFD_SEMA' (`struct eventfd') */
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_SIGNALFD' (`struct signalfd') */
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_FUTEX' (`struct mfutex') */
DEFINE_INTERN_WEAK_ALIAS(handle_futex_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_FUTEXFD' (`struct mfutexfd') */
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_ONESHOT_DIRECTORY_FILE' (`struct oneshot_directory_file') */
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_MFILE' (`struct mfile') */
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_BLOCKDEVICE' (`struct basic_block_device') */
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_DIRECTORYENTRY' (`struct directory_entry') */
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_PATH' (`struct path') */
DEFINE_INTERN_WEAK_ALIAS(handle_path_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_path_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_path_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_path_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_path_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_path_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_path_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_path_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_path_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_path_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_path_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_path_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_path_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_path_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_path_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_path_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_path_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_path_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_path_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_path_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_path_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_path_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_path_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_path_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_path_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_path_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_path_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_path_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_FS' (`struct fs') */
DEFINE_INTERN_WEAK_ALIAS(handle_fs_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_MMAN' (`struct mman') */
DEFINE_INTERN_WEAK_ALIAS(handle_mman_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_mman_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_TASK' (`struct taskpid') */
DEFINE_INTERN_WEAK_ALIAS(handle_task_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_task_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_task_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_task_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_task_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_task_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_task_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_task_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_task_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_task_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_task_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_task_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_task_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_task_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_task_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_task_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_task_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_task_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_task_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_task_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_task_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_task_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_task_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_task_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_task_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_task_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_task_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_task_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_MODULE' (`struct module') */
DEFINE_INTERN_WEAK_ALIAS(handle_module_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_module_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_module_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_module_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_module_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_module_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_module_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_module_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_module_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_module_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_module_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_module_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_module_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_module_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_module_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_module_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_module_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_module_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_module_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_module_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_module_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_module_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_module_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_module_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_module_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_module_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_module_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_module_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_PIDNS' (`struct pidns') */
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_DRIVER_LOADLIST' (`struct driver_loadlist') */
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_CHARACTERDEVICE' (`struct character_device') */
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_MPART' (`struct mpart') */
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_mpart_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_MODULE_SECTION' (`struct module_section') */
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_module_section_tryas, handle_undefined_tryas);
//[[[end]]]



DECL_END

#endif /* !GUARD_KERNEL_SRC_USER_HANDLE_C */
