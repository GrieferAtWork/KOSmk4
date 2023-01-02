/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_FD_ROUTER_C
#define GUARD_KERNEL_SRC_FD_ROUTER_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/aio.h>
#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/types.h>
#include <kernel/user.h>

#include <kos/except/reason/fs.h>
#include <kos/except/reason/inval.h>
#include <kos/kernel/handle.h>

#include <assert.h>
#include <format-printer.h>
#include <inttypes.h>
#include <stddef.h>

/* This #include must be relative so that `deemon -F' can find it! */
#include "../../include/kernel/handle-proto.h"


#pragma GCC diagnostic ignored "-Wsuggest-attribute=pure"
#pragma GCC diagnostic ignored "-Wsuggest-attribute=const"
#pragma GCC diagnostic ignored "-Wsuggest-attribute=cold"

DECL_BEGIN

PRIVATE WUNUSED NONNULL((1, 3)) ssize_t KCALL
handle_generic_printlink(void *ptr, uintptr_half_t type,
                         pformatprinter printer, void *arg) {
	return format_printf(printer, arg,
	                     "anon_inode:[%s:%" PRIuPTR "]",
	                     handle_type_db.h_typename[type],
	                     skew_kernel_pointer(ptr));
}

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
	name = name.decode("utf-8");
	tail = tail.decode("utf-8");
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
		if (!needPerType && name !in ["weakgetref"] && (n !in ["cmd"] || name !in ["ioctl"])) {
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
print "\t.h_typename = {";
local is_first = true;
for (local h_name, none: handle_types) {
	if (!is_first)
		print ",";
	is_first = false;
	print "\t\t[HANDLE_TYPE_",;
	print h_name.upper(),;
	print "] ",;
	print " " * (longest_handle_name_length - #h_name),;
	print "=  ",;
	print repr(h_name),;
}
print "\n\t},";

for (local ARGS: ops) {
	print "\t.h_",;
	print name,;
	print " = {";
	local is_first = true;
	for (local h_name, none: handle_types) {
		if (!is_first)
			print ",";
		is_first = false;
		print "\t\t[HANDLE_TYPE_",;
		print h_name.upper(),;
		print "] ",;
		print " " * (longest_handle_name_length - #h_name),;
		print "= (",;
		return_type = injectObjectType(return_type, "void");
		print return_type,;
		if (!return_type.endswith("*"))
			print " ",;
		if (nothrow)
			print(nothrow, "_T"),;
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
INTERN BLOCKING WUNUSED NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.read") size_t KCALL handle_undefined_read(void *__restrict UNUSED(self), USER CHECKED void *UNUSED(dst), size_t UNUSED(num_bytes), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ); }
INTERN BLOCKING NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.write") size_t KCALL handle_undefined_write(void *__restrict UNUSED(self), USER CHECKED void const *UNUSED(src), size_t UNUSED(num_bytes), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE); }
INTERN BLOCKING WUNUSED NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.pread") size_t KCALL handle_undefined_pread(void *__restrict UNUSED(self), USER CHECKED void *UNUSED(dst), size_t UNUSED(num_bytes), pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_PREAD); }
INTERN BLOCKING NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.pwrite") size_t KCALL handle_undefined_pwrite(void *__restrict UNUSED(self), USER CHECKED void const *UNUSED(src), size_t UNUSED(num_bytes), pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_PWRITE); }
INTERN BLOCKING WUNUSED NONNULL((1, 2)) ATTR_SECTION(".text.kernel.handle_undefined.readv") size_t KCALL handle_undefined_readv(void *__restrict UNUSED(self), struct iov_buffer *__restrict UNUSED(dst), size_t UNUSED(num_bytes), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ); }
INTERN BLOCKING NONNULL((1, 2)) ATTR_SECTION(".text.kernel.handle_undefined.writev") size_t KCALL handle_undefined_writev(void *__restrict UNUSED(self), struct iov_buffer *__restrict UNUSED(src), size_t UNUSED(num_bytes), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE); }
INTERN BLOCKING WUNUSED NONNULL((1, 2)) ATTR_SECTION(".text.kernel.handle_undefined.preadv") size_t KCALL handle_undefined_preadv(void *__restrict UNUSED(self), struct iov_buffer *__restrict UNUSED(dst), size_t UNUSED(num_bytes), pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_PREAD); }
INTERN BLOCKING NONNULL((1, 2)) ATTR_SECTION(".text.kernel.handle_undefined.pwritev") size_t KCALL handle_undefined_pwritev(void *__restrict UNUSED(self), struct iov_buffer *__restrict UNUSED(src), size_t UNUSED(num_bytes), pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_PWRITE); }
INTERN BLOCKING WUNUSED NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.readdir") size_t KCALL handle_undefined_readdir(void *__restrict UNUSED(self), USER CHECKED struct dirent *UNUSED(buf), size_t UNUSED(bufsize), readdir_mode_t UNUSED(readdir_mode), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READDIR); }
INTERN BLOCKING NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.seek") pos_t KCALL handle_undefined_seek(void *__restrict UNUSED(self), off_t UNUSED(offset), unsigned int UNUSED(whence)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_SEEK); }
INTERN BLOCKING NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.ioctl") syscall_slong_t KCALL handle_undefined_ioctl(void *__restrict UNUSED(self), ioctl_t cmd, USER UNCHECKED void *UNUSED(arg), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND, cmd); }
INTERN BLOCKING NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.truncate") void KCALL handle_undefined_truncate(void *__restrict UNUSED(self), pos_t UNUSED(new_size)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_TRUNC); }
INTERN BLOCKING NONNULL((1, 2)) ATTR_SECTION(".text.kernel.handle_undefined.mmap") void KCALL handle_undefined_mmap(void *__restrict UNUSED(self), struct handle_mmap_info *__restrict UNUSED(info)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_MMAP); }
INTERN BLOCKING NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.allocate") pos_t KCALL handle_undefined_allocate(void *__restrict UNUSED(self), fallocate_mode_t UNUSED(mode), pos_t UNUSED(start), pos_t UNUSED(length)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_ALLOCATE); }
INTERN BLOCKING NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.sync") void KCALL handle_undefined_sync(void *__restrict UNUSED(self)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_SYNC); }
INTERN BLOCKING NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.datasync") void KCALL handle_undefined_datasync(void *__restrict UNUSED(self)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_DATASYNC); }
INTERN BLOCKING NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.stat") void KCALL handle_undefined_stat(void *__restrict UNUSED(self), USER CHECKED struct stat *UNUSED(result)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_STAT); }
INTERN BLOCKING NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.pollconnect") void KCALL handle_undefined_pollconnect(void *__restrict UNUSED(self), poll_mode_t UNUSED(what)) THROWS(...) {  }
INTERN BLOCKING WUNUSED NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.polltest") poll_mode_t KCALL handle_undefined_polltest(void *__restrict UNUSED(self), poll_mode_t UNUSED(what)) THROWS(...) { return 0; }
INTERN BLOCKING NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.tryas") REF void *KCALL handle_undefined_tryas(void *__restrict UNUSED(self), uintptr_half_t UNUSED(wanted_type)) THROWS(E_WOULDBLOCK) { return NULL; }
INTERN BLOCKING NONNULL((1, 2)) ATTR_SECTION(".text.kernel.handle_undefined.printlink") ssize_t KCALL handle_undefined_printlink(void *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...) { return handle_generic_printlink(self, HANDLE_TYPE_UNDEFINED, printer, arg); }


/* Handle type database */
PUBLIC_CONST struct handle_types const handle_type_db = {
	.h_typename = {
		[HANDLE_TYPE_UNDEFINED]       =  "undefined",
		[HANDLE_TYPE_MFILE]           =  "mfile",
		[HANDLE_TYPE_DIRENT]          =  "dirent",
		[HANDLE_TYPE_PATH]            =  "path",
		[HANDLE_TYPE_FILEHANDLE]      =  "filehandle",
		[HANDLE_TYPE_TEMPHANDLE]      =  "temphandle",
		[HANDLE_TYPE_DIRHANDLE]       =  "dirhandle",
		[HANDLE_TYPE_FIFOHANDLE]      =  "fifohandle",
		[HANDLE_TYPE_SOCKET]          =  "socket",
		[HANDLE_TYPE_EPOLL]           =  "epoll",
		[HANDLE_TYPE_PIPE]            =  "pipe",
		[HANDLE_TYPE_PIPE_READER]     =  "pipe_reader",
		[HANDLE_TYPE_PIPE_WRITER]     =  "pipe_writer",
		[HANDLE_TYPE_EVENTFD_FENCE]   =  "eventfd_fence",
		[HANDLE_TYPE_EVENTFD_SEMA]    =  "eventfd_sema",
		[HANDLE_TYPE_SIGNALFD]        =  "signalfd",
		[HANDLE_TYPE_FUTEXFD]         =  "futexfd",
		[HANDLE_TYPE_PIDFD]           =  "pidfd",
		[HANDLE_TYPE_MODULE]          =  "module",
		[HANDLE_TYPE_DRIVER_LOADLIST] =  "driver_loadlist",
		[HANDLE_TYPE_REFCOUNTABLE]    =  "refcountable",
		[HANDLE_TYPE_NOTIFYFD]        =  "notifyfd",
		[HANDLE_TYPE_DIRHANDLEX]      =  "dirhandlex"
	},
	.h_refcnt = {
		[HANDLE_TYPE_UNDEFINED]       = (refcnt_t NOTHROW_T(FCALL *)(void const *__restrict))&handle_undefined_refcnt,
		[HANDLE_TYPE_MFILE]           = (refcnt_t NOTHROW_T(FCALL *)(void const *__restrict))&handle_mfile_refcnt,
		[HANDLE_TYPE_DIRENT]          = (refcnt_t NOTHROW_T(FCALL *)(void const *__restrict))&handle_dirent_refcnt,
		[HANDLE_TYPE_PATH]            = (refcnt_t NOTHROW_T(FCALL *)(void const *__restrict))&handle_path_refcnt,
		[HANDLE_TYPE_FILEHANDLE]      = (refcnt_t NOTHROW_T(FCALL *)(void const *__restrict))&handle_filehandle_refcnt,
		[HANDLE_TYPE_TEMPHANDLE]      = (refcnt_t NOTHROW_T(FCALL *)(void const *__restrict))&handle_temphandle_refcnt,
		[HANDLE_TYPE_DIRHANDLE]       = (refcnt_t NOTHROW_T(FCALL *)(void const *__restrict))&handle_dirhandle_refcnt,
		[HANDLE_TYPE_FIFOHANDLE]      = (refcnt_t NOTHROW_T(FCALL *)(void const *__restrict))&handle_fifohandle_refcnt,
		[HANDLE_TYPE_SOCKET]          = (refcnt_t NOTHROW_T(FCALL *)(void const *__restrict))&handle_socket_refcnt,
		[HANDLE_TYPE_EPOLL]           = (refcnt_t NOTHROW_T(FCALL *)(void const *__restrict))&handle_epoll_refcnt,
		[HANDLE_TYPE_PIPE]            = (refcnt_t NOTHROW_T(FCALL *)(void const *__restrict))&handle_pipe_refcnt,
		[HANDLE_TYPE_PIPE_READER]     = (refcnt_t NOTHROW_T(FCALL *)(void const *__restrict))&handle_pipe_reader_refcnt,
		[HANDLE_TYPE_PIPE_WRITER]     = (refcnt_t NOTHROW_T(FCALL *)(void const *__restrict))&handle_pipe_writer_refcnt,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (refcnt_t NOTHROW_T(FCALL *)(void const *__restrict))&handle_eventfd_fence_refcnt,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (refcnt_t NOTHROW_T(FCALL *)(void const *__restrict))&handle_eventfd_sema_refcnt,
		[HANDLE_TYPE_SIGNALFD]        = (refcnt_t NOTHROW_T(FCALL *)(void const *__restrict))&handle_signalfd_refcnt,
		[HANDLE_TYPE_FUTEXFD]         = (refcnt_t NOTHROW_T(FCALL *)(void const *__restrict))&handle_futexfd_refcnt,
		[HANDLE_TYPE_PIDFD]           = (refcnt_t NOTHROW_T(FCALL *)(void const *__restrict))&handle_pidfd_refcnt,
		[HANDLE_TYPE_MODULE]          = (refcnt_t NOTHROW_T(FCALL *)(void const *__restrict))&handle_module_refcnt,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (refcnt_t NOTHROW_T(FCALL *)(void const *__restrict))&handle_driver_loadlist_refcnt,
		[HANDLE_TYPE_REFCOUNTABLE]    = (refcnt_t NOTHROW_T(FCALL *)(void const *__restrict))&handle_refcountable_refcnt,
		[HANDLE_TYPE_NOTIFYFD]        = (refcnt_t NOTHROW_T(FCALL *)(void const *__restrict))&handle_notifyfd_refcnt,
		[HANDLE_TYPE_DIRHANDLEX]      = (refcnt_t NOTHROW_T(FCALL *)(void const *__restrict))&handle_dirhandlex_refcnt
	},
	.h_incref = {
		[HANDLE_TYPE_UNDEFINED]       = (void NOTHROW_T(FCALL *)(void *__restrict))&handle_undefined_incref,
		[HANDLE_TYPE_MFILE]           = (void NOTHROW_T(FCALL *)(void *__restrict))&handle_mfile_incref,
		[HANDLE_TYPE_DIRENT]          = (void NOTHROW_T(FCALL *)(void *__restrict))&handle_dirent_incref,
		[HANDLE_TYPE_PATH]            = (void NOTHROW_T(FCALL *)(void *__restrict))&handle_path_incref,
		[HANDLE_TYPE_FILEHANDLE]      = (void NOTHROW_T(FCALL *)(void *__restrict))&handle_filehandle_incref,
		[HANDLE_TYPE_TEMPHANDLE]      = (void NOTHROW_T(FCALL *)(void *__restrict))&handle_temphandle_incref,
		[HANDLE_TYPE_DIRHANDLE]       = (void NOTHROW_T(FCALL *)(void *__restrict))&handle_dirhandle_incref,
		[HANDLE_TYPE_FIFOHANDLE]      = (void NOTHROW_T(FCALL *)(void *__restrict))&handle_fifohandle_incref,
		[HANDLE_TYPE_SOCKET]          = (void NOTHROW_T(FCALL *)(void *__restrict))&handle_socket_incref,
		[HANDLE_TYPE_EPOLL]           = (void NOTHROW_T(FCALL *)(void *__restrict))&handle_epoll_incref,
		[HANDLE_TYPE_PIPE]            = (void NOTHROW_T(FCALL *)(void *__restrict))&handle_pipe_incref,
		[HANDLE_TYPE_PIPE_READER]     = (void NOTHROW_T(FCALL *)(void *__restrict))&handle_pipe_reader_incref,
		[HANDLE_TYPE_PIPE_WRITER]     = (void NOTHROW_T(FCALL *)(void *__restrict))&handle_pipe_writer_incref,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (void NOTHROW_T(FCALL *)(void *__restrict))&handle_eventfd_fence_incref,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (void NOTHROW_T(FCALL *)(void *__restrict))&handle_eventfd_sema_incref,
		[HANDLE_TYPE_SIGNALFD]        = (void NOTHROW_T(FCALL *)(void *__restrict))&handle_signalfd_incref,
		[HANDLE_TYPE_FUTEXFD]         = (void NOTHROW_T(FCALL *)(void *__restrict))&handle_futexfd_incref,
		[HANDLE_TYPE_PIDFD]           = (void NOTHROW_T(FCALL *)(void *__restrict))&handle_pidfd_incref,
		[HANDLE_TYPE_MODULE]          = (void NOTHROW_T(FCALL *)(void *__restrict))&handle_module_incref,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (void NOTHROW_T(FCALL *)(void *__restrict))&handle_driver_loadlist_incref,
		[HANDLE_TYPE_REFCOUNTABLE]    = (void NOTHROW_T(FCALL *)(void *__restrict))&handle_refcountable_incref,
		[HANDLE_TYPE_NOTIFYFD]        = (void NOTHROW_T(FCALL *)(void *__restrict))&handle_notifyfd_incref,
		[HANDLE_TYPE_DIRHANDLEX]      = (void NOTHROW_T(FCALL *)(void *__restrict))&handle_dirhandlex_incref
	},
	.h_decref = {
		[HANDLE_TYPE_UNDEFINED]       = (void NOTHROW_T(FCALL *)(REF void *__restrict))&handle_undefined_decref,
		[HANDLE_TYPE_MFILE]           = (void NOTHROW_T(FCALL *)(REF void *__restrict))&handle_mfile_decref,
		[HANDLE_TYPE_DIRENT]          = (void NOTHROW_T(FCALL *)(REF void *__restrict))&handle_dirent_decref,
		[HANDLE_TYPE_PATH]            = (void NOTHROW_T(FCALL *)(REF void *__restrict))&handle_path_decref,
		[HANDLE_TYPE_FILEHANDLE]      = (void NOTHROW_T(FCALL *)(REF void *__restrict))&handle_filehandle_decref,
		[HANDLE_TYPE_TEMPHANDLE]      = (void NOTHROW_T(FCALL *)(REF void *__restrict))&handle_temphandle_decref,
		[HANDLE_TYPE_DIRHANDLE]       = (void NOTHROW_T(FCALL *)(REF void *__restrict))&handle_dirhandle_decref,
		[HANDLE_TYPE_FIFOHANDLE]      = (void NOTHROW_T(FCALL *)(REF void *__restrict))&handle_fifohandle_decref,
		[HANDLE_TYPE_SOCKET]          = (void NOTHROW_T(FCALL *)(REF void *__restrict))&handle_socket_decref,
		[HANDLE_TYPE_EPOLL]           = (void NOTHROW_T(FCALL *)(REF void *__restrict))&handle_epoll_decref,
		[HANDLE_TYPE_PIPE]            = (void NOTHROW_T(FCALL *)(REF void *__restrict))&handle_pipe_decref,
		[HANDLE_TYPE_PIPE_READER]     = (void NOTHROW_T(FCALL *)(REF void *__restrict))&handle_pipe_reader_decref,
		[HANDLE_TYPE_PIPE_WRITER]     = (void NOTHROW_T(FCALL *)(REF void *__restrict))&handle_pipe_writer_decref,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (void NOTHROW_T(FCALL *)(REF void *__restrict))&handle_eventfd_fence_decref,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (void NOTHROW_T(FCALL *)(REF void *__restrict))&handle_eventfd_sema_decref,
		[HANDLE_TYPE_SIGNALFD]        = (void NOTHROW_T(FCALL *)(REF void *__restrict))&handle_signalfd_decref,
		[HANDLE_TYPE_FUTEXFD]         = (void NOTHROW_T(FCALL *)(REF void *__restrict))&handle_futexfd_decref,
		[HANDLE_TYPE_PIDFD]           = (void NOTHROW_T(FCALL *)(REF void *__restrict))&handle_pidfd_decref,
		[HANDLE_TYPE_MODULE]          = (void NOTHROW_T(FCALL *)(REF void *__restrict))&handle_module_decref,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (void NOTHROW_T(FCALL *)(REF void *__restrict))&handle_driver_loadlist_decref,
		[HANDLE_TYPE_REFCOUNTABLE]    = (void NOTHROW_T(FCALL *)(REF void *__restrict))&handle_refcountable_decref,
		[HANDLE_TYPE_NOTIFYFD]        = (void NOTHROW_T(FCALL *)(REF void *__restrict))&handle_notifyfd_decref,
		[HANDLE_TYPE_DIRHANDLEX]      = (void NOTHROW_T(FCALL *)(REF void *__restrict))&handle_dirhandlex_decref
	},
	.h_tryincref = {
		[HANDLE_TYPE_UNDEFINED]       = (__BOOL NOTHROW_T(FCALL *)(void *__restrict))&handle_undefined_tryincref,
		[HANDLE_TYPE_MFILE]           = (__BOOL NOTHROW_T(FCALL *)(void *__restrict))&handle_mfile_tryincref,
		[HANDLE_TYPE_DIRENT]          = (__BOOL NOTHROW_T(FCALL *)(void *__restrict))&handle_dirent_tryincref,
		[HANDLE_TYPE_PATH]            = (__BOOL NOTHROW_T(FCALL *)(void *__restrict))&handle_path_tryincref,
		[HANDLE_TYPE_FILEHANDLE]      = (__BOOL NOTHROW_T(FCALL *)(void *__restrict))&handle_filehandle_tryincref,
		[HANDLE_TYPE_TEMPHANDLE]      = (__BOOL NOTHROW_T(FCALL *)(void *__restrict))&handle_temphandle_tryincref,
		[HANDLE_TYPE_DIRHANDLE]       = (__BOOL NOTHROW_T(FCALL *)(void *__restrict))&handle_dirhandle_tryincref,
		[HANDLE_TYPE_FIFOHANDLE]      = (__BOOL NOTHROW_T(FCALL *)(void *__restrict))&handle_fifohandle_tryincref,
		[HANDLE_TYPE_SOCKET]          = (__BOOL NOTHROW_T(FCALL *)(void *__restrict))&handle_socket_tryincref,
		[HANDLE_TYPE_EPOLL]           = (__BOOL NOTHROW_T(FCALL *)(void *__restrict))&handle_epoll_tryincref,
		[HANDLE_TYPE_PIPE]            = (__BOOL NOTHROW_T(FCALL *)(void *__restrict))&handle_pipe_tryincref,
		[HANDLE_TYPE_PIPE_READER]     = (__BOOL NOTHROW_T(FCALL *)(void *__restrict))&handle_pipe_reader_tryincref,
		[HANDLE_TYPE_PIPE_WRITER]     = (__BOOL NOTHROW_T(FCALL *)(void *__restrict))&handle_pipe_writer_tryincref,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (__BOOL NOTHROW_T(FCALL *)(void *__restrict))&handle_eventfd_fence_tryincref,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (__BOOL NOTHROW_T(FCALL *)(void *__restrict))&handle_eventfd_sema_tryincref,
		[HANDLE_TYPE_SIGNALFD]        = (__BOOL NOTHROW_T(FCALL *)(void *__restrict))&handle_signalfd_tryincref,
		[HANDLE_TYPE_FUTEXFD]         = (__BOOL NOTHROW_T(FCALL *)(void *__restrict))&handle_futexfd_tryincref,
		[HANDLE_TYPE_PIDFD]           = (__BOOL NOTHROW_T(FCALL *)(void *__restrict))&handle_pidfd_tryincref,
		[HANDLE_TYPE_MODULE]          = (__BOOL NOTHROW_T(FCALL *)(void *__restrict))&handle_module_tryincref,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (__BOOL NOTHROW_T(FCALL *)(void *__restrict))&handle_driver_loadlist_tryincref,
		[HANDLE_TYPE_REFCOUNTABLE]    = (__BOOL NOTHROW_T(FCALL *)(void *__restrict))&handle_refcountable_tryincref,
		[HANDLE_TYPE_NOTIFYFD]        = (__BOOL NOTHROW_T(FCALL *)(void *__restrict))&handle_notifyfd_tryincref,
		[HANDLE_TYPE_DIRHANDLEX]      = (__BOOL NOTHROW_T(FCALL *)(void *__restrict))&handle_dirhandlex_tryincref
	},
	.h_weakgetref = {
		[HANDLE_TYPE_UNDEFINED]       = (WEAK REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_undefined_weakgetref,
		[HANDLE_TYPE_MFILE]           = (WEAK REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_mfile_weakgetref,
		[HANDLE_TYPE_DIRENT]          = (WEAK REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_dirent_weakgetref,
		[HANDLE_TYPE_PATH]            = (WEAK REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_path_weakgetref,
		[HANDLE_TYPE_FILEHANDLE]      = (WEAK REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_filehandle_weakgetref,
		[HANDLE_TYPE_TEMPHANDLE]      = (WEAK REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_temphandle_weakgetref,
		[HANDLE_TYPE_DIRHANDLE]       = (WEAK REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_dirhandle_weakgetref,
		[HANDLE_TYPE_FIFOHANDLE]      = (WEAK REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_fifohandle_weakgetref,
		[HANDLE_TYPE_SOCKET]          = (WEAK REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_socket_weakgetref,
		[HANDLE_TYPE_EPOLL]           = (WEAK REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_epoll_weakgetref,
		[HANDLE_TYPE_PIPE]            = (WEAK REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_pipe_weakgetref,
		[HANDLE_TYPE_PIPE_READER]     = (WEAK REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_pipe_reader_weakgetref,
		[HANDLE_TYPE_PIPE_WRITER]     = (WEAK REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_pipe_writer_weakgetref,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (WEAK REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_eventfd_fence_weakgetref,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (WEAK REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_eventfd_sema_weakgetref,
		[HANDLE_TYPE_SIGNALFD]        = (WEAK REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_signalfd_weakgetref,
		[HANDLE_TYPE_FUTEXFD]         = (WEAK REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_futexfd_weakgetref,
		[HANDLE_TYPE_PIDFD]           = (WEAK REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_pidfd_weakgetref,
		[HANDLE_TYPE_MODULE]          = (WEAK REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_module_weakgetref,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (WEAK REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_driver_loadlist_weakgetref,
		[HANDLE_TYPE_REFCOUNTABLE]    = (WEAK REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_refcountable_weakgetref,
		[HANDLE_TYPE_NOTIFYFD]        = (WEAK REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_notifyfd_weakgetref,
		[HANDLE_TYPE_DIRHANDLEX]      = (WEAK REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_dirhandlex_weakgetref
	},
	.h_weaklckref = {
		[HANDLE_TYPE_UNDEFINED]       = (REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_undefined_weaklckref,
		[HANDLE_TYPE_MFILE]           = (REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_mfile_weaklckref,
		[HANDLE_TYPE_DIRENT]          = (REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_dirent_weaklckref,
		[HANDLE_TYPE_PATH]            = (REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_path_weaklckref,
		[HANDLE_TYPE_FILEHANDLE]      = (REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_filehandle_weaklckref,
		[HANDLE_TYPE_TEMPHANDLE]      = (REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_temphandle_weaklckref,
		[HANDLE_TYPE_DIRHANDLE]       = (REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_dirhandle_weaklckref,
		[HANDLE_TYPE_FIFOHANDLE]      = (REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_fifohandle_weaklckref,
		[HANDLE_TYPE_SOCKET]          = (REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_socket_weaklckref,
		[HANDLE_TYPE_EPOLL]           = (REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_epoll_weaklckref,
		[HANDLE_TYPE_PIPE]            = (REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_pipe_weaklckref,
		[HANDLE_TYPE_PIPE_READER]     = (REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_pipe_reader_weaklckref,
		[HANDLE_TYPE_PIPE_WRITER]     = (REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_pipe_writer_weaklckref,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_eventfd_fence_weaklckref,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_eventfd_sema_weaklckref,
		[HANDLE_TYPE_SIGNALFD]        = (REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_signalfd_weaklckref,
		[HANDLE_TYPE_FUTEXFD]         = (REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_futexfd_weaklckref,
		[HANDLE_TYPE_PIDFD]           = (REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_pidfd_weaklckref,
		[HANDLE_TYPE_MODULE]          = (REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_module_weaklckref,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_driver_loadlist_weaklckref,
		[HANDLE_TYPE_REFCOUNTABLE]    = (REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_refcountable_weaklckref,
		[HANDLE_TYPE_NOTIFYFD]        = (REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_notifyfd_weaklckref,
		[HANDLE_TYPE_DIRHANDLEX]      = (REF void *NOTHROW_T(FCALL *)(void *__restrict))&handle_dirhandlex_weaklckref
	},
	.h_weakdecref = {
		[HANDLE_TYPE_UNDEFINED]       = (void NOTHROW_T(FCALL *)(WEAK REF void *__restrict))&handle_undefined_weakdecref,
		[HANDLE_TYPE_MFILE]           = (void NOTHROW_T(FCALL *)(WEAK REF void *__restrict))&handle_mfile_weakdecref,
		[HANDLE_TYPE_DIRENT]          = (void NOTHROW_T(FCALL *)(WEAK REF void *__restrict))&handle_dirent_weakdecref,
		[HANDLE_TYPE_PATH]            = (void NOTHROW_T(FCALL *)(WEAK REF void *__restrict))&handle_path_weakdecref,
		[HANDLE_TYPE_FILEHANDLE]      = (void NOTHROW_T(FCALL *)(WEAK REF void *__restrict))&handle_filehandle_weakdecref,
		[HANDLE_TYPE_TEMPHANDLE]      = (void NOTHROW_T(FCALL *)(WEAK REF void *__restrict))&handle_temphandle_weakdecref,
		[HANDLE_TYPE_DIRHANDLE]       = (void NOTHROW_T(FCALL *)(WEAK REF void *__restrict))&handle_dirhandle_weakdecref,
		[HANDLE_TYPE_FIFOHANDLE]      = (void NOTHROW_T(FCALL *)(WEAK REF void *__restrict))&handle_fifohandle_weakdecref,
		[HANDLE_TYPE_SOCKET]          = (void NOTHROW_T(FCALL *)(WEAK REF void *__restrict))&handle_socket_weakdecref,
		[HANDLE_TYPE_EPOLL]           = (void NOTHROW_T(FCALL *)(WEAK REF void *__restrict))&handle_epoll_weakdecref,
		[HANDLE_TYPE_PIPE]            = (void NOTHROW_T(FCALL *)(WEAK REF void *__restrict))&handle_pipe_weakdecref,
		[HANDLE_TYPE_PIPE_READER]     = (void NOTHROW_T(FCALL *)(WEAK REF void *__restrict))&handle_pipe_reader_weakdecref,
		[HANDLE_TYPE_PIPE_WRITER]     = (void NOTHROW_T(FCALL *)(WEAK REF void *__restrict))&handle_pipe_writer_weakdecref,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (void NOTHROW_T(FCALL *)(WEAK REF void *__restrict))&handle_eventfd_fence_weakdecref,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (void NOTHROW_T(FCALL *)(WEAK REF void *__restrict))&handle_eventfd_sema_weakdecref,
		[HANDLE_TYPE_SIGNALFD]        = (void NOTHROW_T(FCALL *)(WEAK REF void *__restrict))&handle_signalfd_weakdecref,
		[HANDLE_TYPE_FUTEXFD]         = (void NOTHROW_T(FCALL *)(WEAK REF void *__restrict))&handle_futexfd_weakdecref,
		[HANDLE_TYPE_PIDFD]           = (void NOTHROW_T(FCALL *)(WEAK REF void *__restrict))&handle_pidfd_weakdecref,
		[HANDLE_TYPE_MODULE]          = (void NOTHROW_T(FCALL *)(WEAK REF void *__restrict))&handle_module_weakdecref,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (void NOTHROW_T(FCALL *)(WEAK REF void *__restrict))&handle_driver_loadlist_weakdecref,
		[HANDLE_TYPE_REFCOUNTABLE]    = (void NOTHROW_T(FCALL *)(WEAK REF void *__restrict))&handle_refcountable_weakdecref,
		[HANDLE_TYPE_NOTIFYFD]        = (void NOTHROW_T(FCALL *)(WEAK REF void *__restrict))&handle_notifyfd_weakdecref,
		[HANDLE_TYPE_DIRHANDLEX]      = (void NOTHROW_T(FCALL *)(WEAK REF void *__restrict))&handle_dirhandlex_weakdecref
	},
	.h_read = {
		[HANDLE_TYPE_UNDEFINED]       = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_undefined_read,
		[HANDLE_TYPE_MFILE]           = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_mfile_read,
		[HANDLE_TYPE_DIRENT]          = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_dirent_read,
		[HANDLE_TYPE_PATH]            = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_path_read,
		[HANDLE_TYPE_FILEHANDLE]      = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_filehandle_read,
		[HANDLE_TYPE_TEMPHANDLE]      = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_temphandle_read,
		[HANDLE_TYPE_DIRHANDLE]       = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_dirhandle_read,
		[HANDLE_TYPE_FIFOHANDLE]      = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_fifohandle_read,
		[HANDLE_TYPE_SOCKET]          = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_socket_read,
		[HANDLE_TYPE_EPOLL]           = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_epoll_read,
		[HANDLE_TYPE_PIPE]            = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_pipe_read,
		[HANDLE_TYPE_PIPE_READER]     = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_pipe_reader_read,
		[HANDLE_TYPE_PIPE_WRITER]     = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_pipe_writer_read,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_eventfd_fence_read,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_eventfd_sema_read,
		[HANDLE_TYPE_SIGNALFD]        = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_signalfd_read,
		[HANDLE_TYPE_FUTEXFD]         = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_futexfd_read,
		[HANDLE_TYPE_PIDFD]           = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_pidfd_read,
		[HANDLE_TYPE_MODULE]          = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_module_read,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_driver_loadlist_read,
		[HANDLE_TYPE_REFCOUNTABLE]    = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_refcountable_read,
		[HANDLE_TYPE_NOTIFYFD]        = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_notifyfd_read,
		[HANDLE_TYPE_DIRHANDLEX]      = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_dirhandlex_read
	},
	.h_write = {
		[HANDLE_TYPE_UNDEFINED]       = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_undefined_write,
		[HANDLE_TYPE_MFILE]           = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_mfile_write,
		[HANDLE_TYPE_DIRENT]          = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_dirent_write,
		[HANDLE_TYPE_PATH]            = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_path_write,
		[HANDLE_TYPE_FILEHANDLE]      = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_filehandle_write,
		[HANDLE_TYPE_TEMPHANDLE]      = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_temphandle_write,
		[HANDLE_TYPE_DIRHANDLE]       = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_dirhandle_write,
		[HANDLE_TYPE_FIFOHANDLE]      = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_fifohandle_write,
		[HANDLE_TYPE_SOCKET]          = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_socket_write,
		[HANDLE_TYPE_EPOLL]           = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_epoll_write,
		[HANDLE_TYPE_PIPE]            = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_pipe_write,
		[HANDLE_TYPE_PIPE_READER]     = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_pipe_reader_write,
		[HANDLE_TYPE_PIPE_WRITER]     = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_pipe_writer_write,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_eventfd_fence_write,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_eventfd_sema_write,
		[HANDLE_TYPE_SIGNALFD]        = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_signalfd_write,
		[HANDLE_TYPE_FUTEXFD]         = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_futexfd_write,
		[HANDLE_TYPE_PIDFD]           = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_pidfd_write,
		[HANDLE_TYPE_MODULE]          = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_module_write,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_driver_loadlist_write,
		[HANDLE_TYPE_REFCOUNTABLE]    = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_refcountable_write,
		[HANDLE_TYPE_NOTIFYFD]        = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_notifyfd_write,
		[HANDLE_TYPE_DIRHANDLEX]      = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_dirhandlex_write
	},
	.h_pread = {
		[HANDLE_TYPE_UNDEFINED]       = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_undefined_pread,
		[HANDLE_TYPE_MFILE]           = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_mfile_pread,
		[HANDLE_TYPE_DIRENT]          = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_dirent_pread,
		[HANDLE_TYPE_PATH]            = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_path_pread,
		[HANDLE_TYPE_FILEHANDLE]      = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_filehandle_pread,
		[HANDLE_TYPE_TEMPHANDLE]      = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_temphandle_pread,
		[HANDLE_TYPE_DIRHANDLE]       = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_dirhandle_pread,
		[HANDLE_TYPE_FIFOHANDLE]      = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_fifohandle_pread,
		[HANDLE_TYPE_SOCKET]          = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_socket_pread,
		[HANDLE_TYPE_EPOLL]           = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_epoll_pread,
		[HANDLE_TYPE_PIPE]            = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_pipe_pread,
		[HANDLE_TYPE_PIPE_READER]     = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_pipe_reader_pread,
		[HANDLE_TYPE_PIPE_WRITER]     = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_pipe_writer_pread,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_eventfd_fence_pread,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_eventfd_sema_pread,
		[HANDLE_TYPE_SIGNALFD]        = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_signalfd_pread,
		[HANDLE_TYPE_FUTEXFD]         = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_futexfd_pread,
		[HANDLE_TYPE_PIDFD]           = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_pidfd_pread,
		[HANDLE_TYPE_MODULE]          = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_module_pread,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_driver_loadlist_pread,
		[HANDLE_TYPE_REFCOUNTABLE]    = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_refcountable_pread,
		[HANDLE_TYPE_NOTIFYFD]        = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_notifyfd_pread,
		[HANDLE_TYPE_DIRHANDLEX]      = (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_dirhandlex_pread
	},
	.h_pwrite = {
		[HANDLE_TYPE_UNDEFINED]       = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_undefined_pwrite,
		[HANDLE_TYPE_MFILE]           = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_mfile_pwrite,
		[HANDLE_TYPE_DIRENT]          = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_dirent_pwrite,
		[HANDLE_TYPE_PATH]            = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_path_pwrite,
		[HANDLE_TYPE_FILEHANDLE]      = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_filehandle_pwrite,
		[HANDLE_TYPE_TEMPHANDLE]      = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_temphandle_pwrite,
		[HANDLE_TYPE_DIRHANDLE]       = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_dirhandle_pwrite,
		[HANDLE_TYPE_FIFOHANDLE]      = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_fifohandle_pwrite,
		[HANDLE_TYPE_SOCKET]          = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_socket_pwrite,
		[HANDLE_TYPE_EPOLL]           = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_epoll_pwrite,
		[HANDLE_TYPE_PIPE]            = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_pipe_pwrite,
		[HANDLE_TYPE_PIPE_READER]     = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_pipe_reader_pwrite,
		[HANDLE_TYPE_PIPE_WRITER]     = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_pipe_writer_pwrite,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_eventfd_fence_pwrite,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_eventfd_sema_pwrite,
		[HANDLE_TYPE_SIGNALFD]        = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_signalfd_pwrite,
		[HANDLE_TYPE_FUTEXFD]         = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_futexfd_pwrite,
		[HANDLE_TYPE_PIDFD]           = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_pidfd_pwrite,
		[HANDLE_TYPE_MODULE]          = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_module_pwrite,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_driver_loadlist_pwrite,
		[HANDLE_TYPE_REFCOUNTABLE]    = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_refcountable_pwrite,
		[HANDLE_TYPE_NOTIFYFD]        = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_notifyfd_pwrite,
		[HANDLE_TYPE_DIRHANDLEX]      = (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_dirhandlex_pwrite
	},
	.h_readv = {
		[HANDLE_TYPE_UNDEFINED]       = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_undefined_readv,
		[HANDLE_TYPE_MFILE]           = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_mfile_readv,
		[HANDLE_TYPE_DIRENT]          = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_dirent_readv,
		[HANDLE_TYPE_PATH]            = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_path_readv,
		[HANDLE_TYPE_FILEHANDLE]      = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_filehandle_readv,
		[HANDLE_TYPE_TEMPHANDLE]      = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_temphandle_readv,
		[HANDLE_TYPE_DIRHANDLE]       = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_dirhandle_readv,
		[HANDLE_TYPE_FIFOHANDLE]      = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_fifohandle_readv,
		[HANDLE_TYPE_SOCKET]          = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_socket_readv,
		[HANDLE_TYPE_EPOLL]           = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_epoll_readv,
		[HANDLE_TYPE_PIPE]            = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_pipe_readv,
		[HANDLE_TYPE_PIPE_READER]     = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_pipe_reader_readv,
		[HANDLE_TYPE_PIPE_WRITER]     = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_pipe_writer_readv,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_eventfd_fence_readv,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_eventfd_sema_readv,
		[HANDLE_TYPE_SIGNALFD]        = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_signalfd_readv,
		[HANDLE_TYPE_FUTEXFD]         = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_futexfd_readv,
		[HANDLE_TYPE_PIDFD]           = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_pidfd_readv,
		[HANDLE_TYPE_MODULE]          = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_module_readv,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_driver_loadlist_readv,
		[HANDLE_TYPE_REFCOUNTABLE]    = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_refcountable_readv,
		[HANDLE_TYPE_NOTIFYFD]        = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_notifyfd_readv,
		[HANDLE_TYPE_DIRHANDLEX]      = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_dirhandlex_readv
	},
	.h_writev = {
		[HANDLE_TYPE_UNDEFINED]       = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_undefined_writev,
		[HANDLE_TYPE_MFILE]           = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_mfile_writev,
		[HANDLE_TYPE_DIRENT]          = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_dirent_writev,
		[HANDLE_TYPE_PATH]            = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_path_writev,
		[HANDLE_TYPE_FILEHANDLE]      = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_filehandle_writev,
		[HANDLE_TYPE_TEMPHANDLE]      = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_temphandle_writev,
		[HANDLE_TYPE_DIRHANDLE]       = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_dirhandle_writev,
		[HANDLE_TYPE_FIFOHANDLE]      = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_fifohandle_writev,
		[HANDLE_TYPE_SOCKET]          = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_socket_writev,
		[HANDLE_TYPE_EPOLL]           = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_epoll_writev,
		[HANDLE_TYPE_PIPE]            = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_pipe_writev,
		[HANDLE_TYPE_PIPE_READER]     = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_pipe_reader_writev,
		[HANDLE_TYPE_PIPE_WRITER]     = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_pipe_writer_writev,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_eventfd_fence_writev,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_eventfd_sema_writev,
		[HANDLE_TYPE_SIGNALFD]        = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_signalfd_writev,
		[HANDLE_TYPE_FUTEXFD]         = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_futexfd_writev,
		[HANDLE_TYPE_PIDFD]           = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_pidfd_writev,
		[HANDLE_TYPE_MODULE]          = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_module_writev,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_driver_loadlist_writev,
		[HANDLE_TYPE_REFCOUNTABLE]    = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_refcountable_writev,
		[HANDLE_TYPE_NOTIFYFD]        = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_notifyfd_writev,
		[HANDLE_TYPE_DIRHANDLEX]      = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, iomode_t))&handle_dirhandlex_writev
	},
	.h_preadv = {
		[HANDLE_TYPE_UNDEFINED]       = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_undefined_preadv,
		[HANDLE_TYPE_MFILE]           = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_mfile_preadv,
		[HANDLE_TYPE_DIRENT]          = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_dirent_preadv,
		[HANDLE_TYPE_PATH]            = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_path_preadv,
		[HANDLE_TYPE_FILEHANDLE]      = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_filehandle_preadv,
		[HANDLE_TYPE_TEMPHANDLE]      = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_temphandle_preadv,
		[HANDLE_TYPE_DIRHANDLE]       = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_dirhandle_preadv,
		[HANDLE_TYPE_FIFOHANDLE]      = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_fifohandle_preadv,
		[HANDLE_TYPE_SOCKET]          = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_socket_preadv,
		[HANDLE_TYPE_EPOLL]           = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_epoll_preadv,
		[HANDLE_TYPE_PIPE]            = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_pipe_preadv,
		[HANDLE_TYPE_PIPE_READER]     = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_pipe_reader_preadv,
		[HANDLE_TYPE_PIPE_WRITER]     = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_pipe_writer_preadv,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_eventfd_fence_preadv,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_eventfd_sema_preadv,
		[HANDLE_TYPE_SIGNALFD]        = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_signalfd_preadv,
		[HANDLE_TYPE_FUTEXFD]         = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_futexfd_preadv,
		[HANDLE_TYPE_PIDFD]           = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_pidfd_preadv,
		[HANDLE_TYPE_MODULE]          = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_module_preadv,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_driver_loadlist_preadv,
		[HANDLE_TYPE_REFCOUNTABLE]    = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_refcountable_preadv,
		[HANDLE_TYPE_NOTIFYFD]        = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_notifyfd_preadv,
		[HANDLE_TYPE_DIRHANDLEX]      = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_dirhandlex_preadv
	},
	.h_pwritev = {
		[HANDLE_TYPE_UNDEFINED]       = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_undefined_pwritev,
		[HANDLE_TYPE_MFILE]           = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_mfile_pwritev,
		[HANDLE_TYPE_DIRENT]          = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_dirent_pwritev,
		[HANDLE_TYPE_PATH]            = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_path_pwritev,
		[HANDLE_TYPE_FILEHANDLE]      = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_filehandle_pwritev,
		[HANDLE_TYPE_TEMPHANDLE]      = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_temphandle_pwritev,
		[HANDLE_TYPE_DIRHANDLE]       = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_dirhandle_pwritev,
		[HANDLE_TYPE_FIFOHANDLE]      = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_fifohandle_pwritev,
		[HANDLE_TYPE_SOCKET]          = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_socket_pwritev,
		[HANDLE_TYPE_EPOLL]           = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_epoll_pwritev,
		[HANDLE_TYPE_PIPE]            = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_pipe_pwritev,
		[HANDLE_TYPE_PIPE_READER]     = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_pipe_reader_pwritev,
		[HANDLE_TYPE_PIPE_WRITER]     = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_pipe_writer_pwritev,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_eventfd_fence_pwritev,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_eventfd_sema_pwritev,
		[HANDLE_TYPE_SIGNALFD]        = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_signalfd_pwritev,
		[HANDLE_TYPE_FUTEXFD]         = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_futexfd_pwritev,
		[HANDLE_TYPE_PIDFD]           = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_pidfd_pwritev,
		[HANDLE_TYPE_MODULE]          = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_module_pwritev,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_driver_loadlist_pwritev,
		[HANDLE_TYPE_REFCOUNTABLE]    = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_refcountable_pwritev,
		[HANDLE_TYPE_NOTIFYFD]        = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_notifyfd_pwritev,
		[HANDLE_TYPE_DIRHANDLEX]      = (size_t (KCALL *)(void *__restrict, struct iov_buffer *__restrict, size_t, pos_t, iomode_t))&handle_dirhandlex_pwritev
	},
	.h_readdir = {
		[HANDLE_TYPE_UNDEFINED]       = (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_undefined_readdir,
		[HANDLE_TYPE_MFILE]           = (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_mfile_readdir,
		[HANDLE_TYPE_DIRENT]          = (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_dirent_readdir,
		[HANDLE_TYPE_PATH]            = (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_path_readdir,
		[HANDLE_TYPE_FILEHANDLE]      = (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_filehandle_readdir,
		[HANDLE_TYPE_TEMPHANDLE]      = (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_temphandle_readdir,
		[HANDLE_TYPE_DIRHANDLE]       = (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_dirhandle_readdir,
		[HANDLE_TYPE_FIFOHANDLE]      = (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_fifohandle_readdir,
		[HANDLE_TYPE_SOCKET]          = (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_socket_readdir,
		[HANDLE_TYPE_EPOLL]           = (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_epoll_readdir,
		[HANDLE_TYPE_PIPE]            = (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_pipe_readdir,
		[HANDLE_TYPE_PIPE_READER]     = (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_pipe_reader_readdir,
		[HANDLE_TYPE_PIPE_WRITER]     = (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_pipe_writer_readdir,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_eventfd_fence_readdir,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_eventfd_sema_readdir,
		[HANDLE_TYPE_SIGNALFD]        = (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_signalfd_readdir,
		[HANDLE_TYPE_FUTEXFD]         = (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_futexfd_readdir,
		[HANDLE_TYPE_PIDFD]           = (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_pidfd_readdir,
		[HANDLE_TYPE_MODULE]          = (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_module_readdir,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_driver_loadlist_readdir,
		[HANDLE_TYPE_REFCOUNTABLE]    = (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_refcountable_readdir,
		[HANDLE_TYPE_NOTIFYFD]        = (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_notifyfd_readdir,
		[HANDLE_TYPE_DIRHANDLEX]      = (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_dirhandlex_readdir
	},
	.h_seek = {
		[HANDLE_TYPE_UNDEFINED]       = (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_undefined_seek,
		[HANDLE_TYPE_MFILE]           = (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_mfile_seek,
		[HANDLE_TYPE_DIRENT]          = (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_dirent_seek,
		[HANDLE_TYPE_PATH]            = (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_path_seek,
		[HANDLE_TYPE_FILEHANDLE]      = (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_filehandle_seek,
		[HANDLE_TYPE_TEMPHANDLE]      = (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_temphandle_seek,
		[HANDLE_TYPE_DIRHANDLE]       = (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_dirhandle_seek,
		[HANDLE_TYPE_FIFOHANDLE]      = (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_fifohandle_seek,
		[HANDLE_TYPE_SOCKET]          = (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_socket_seek,
		[HANDLE_TYPE_EPOLL]           = (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_epoll_seek,
		[HANDLE_TYPE_PIPE]            = (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_pipe_seek,
		[HANDLE_TYPE_PIPE_READER]     = (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_pipe_reader_seek,
		[HANDLE_TYPE_PIPE_WRITER]     = (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_pipe_writer_seek,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_eventfd_fence_seek,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_eventfd_sema_seek,
		[HANDLE_TYPE_SIGNALFD]        = (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_signalfd_seek,
		[HANDLE_TYPE_FUTEXFD]         = (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_futexfd_seek,
		[HANDLE_TYPE_PIDFD]           = (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_pidfd_seek,
		[HANDLE_TYPE_MODULE]          = (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_module_seek,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_driver_loadlist_seek,
		[HANDLE_TYPE_REFCOUNTABLE]    = (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_refcountable_seek,
		[HANDLE_TYPE_NOTIFYFD]        = (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_notifyfd_seek,
		[HANDLE_TYPE_DIRHANDLEX]      = (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_dirhandlex_seek
	},
	.h_ioctl = {
		[HANDLE_TYPE_UNDEFINED]       = (syscall_slong_t (KCALL *)(void *__restrict, ioctl_t, USER UNCHECKED void *, iomode_t))&handle_undefined_ioctl,
		[HANDLE_TYPE_MFILE]           = (syscall_slong_t (KCALL *)(void *__restrict, ioctl_t, USER UNCHECKED void *, iomode_t))&handle_mfile_ioctl,
		[HANDLE_TYPE_DIRENT]          = (syscall_slong_t (KCALL *)(void *__restrict, ioctl_t, USER UNCHECKED void *, iomode_t))&handle_dirent_ioctl,
		[HANDLE_TYPE_PATH]            = (syscall_slong_t (KCALL *)(void *__restrict, ioctl_t, USER UNCHECKED void *, iomode_t))&handle_path_ioctl,
		[HANDLE_TYPE_FILEHANDLE]      = (syscall_slong_t (KCALL *)(void *__restrict, ioctl_t, USER UNCHECKED void *, iomode_t))&handle_filehandle_ioctl,
		[HANDLE_TYPE_TEMPHANDLE]      = (syscall_slong_t (KCALL *)(void *__restrict, ioctl_t, USER UNCHECKED void *, iomode_t))&handle_temphandle_ioctl,
		[HANDLE_TYPE_DIRHANDLE]       = (syscall_slong_t (KCALL *)(void *__restrict, ioctl_t, USER UNCHECKED void *, iomode_t))&handle_dirhandle_ioctl,
		[HANDLE_TYPE_FIFOHANDLE]      = (syscall_slong_t (KCALL *)(void *__restrict, ioctl_t, USER UNCHECKED void *, iomode_t))&handle_fifohandle_ioctl,
		[HANDLE_TYPE_SOCKET]          = (syscall_slong_t (KCALL *)(void *__restrict, ioctl_t, USER UNCHECKED void *, iomode_t))&handle_socket_ioctl,
		[HANDLE_TYPE_EPOLL]           = (syscall_slong_t (KCALL *)(void *__restrict, ioctl_t, USER UNCHECKED void *, iomode_t))&handle_epoll_ioctl,
		[HANDLE_TYPE_PIPE]            = (syscall_slong_t (KCALL *)(void *__restrict, ioctl_t, USER UNCHECKED void *, iomode_t))&handle_pipe_ioctl,
		[HANDLE_TYPE_PIPE_READER]     = (syscall_slong_t (KCALL *)(void *__restrict, ioctl_t, USER UNCHECKED void *, iomode_t))&handle_pipe_reader_ioctl,
		[HANDLE_TYPE_PIPE_WRITER]     = (syscall_slong_t (KCALL *)(void *__restrict, ioctl_t, USER UNCHECKED void *, iomode_t))&handle_pipe_writer_ioctl,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (syscall_slong_t (KCALL *)(void *__restrict, ioctl_t, USER UNCHECKED void *, iomode_t))&handle_eventfd_fence_ioctl,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (syscall_slong_t (KCALL *)(void *__restrict, ioctl_t, USER UNCHECKED void *, iomode_t))&handle_eventfd_sema_ioctl,
		[HANDLE_TYPE_SIGNALFD]        = (syscall_slong_t (KCALL *)(void *__restrict, ioctl_t, USER UNCHECKED void *, iomode_t))&handle_signalfd_ioctl,
		[HANDLE_TYPE_FUTEXFD]         = (syscall_slong_t (KCALL *)(void *__restrict, ioctl_t, USER UNCHECKED void *, iomode_t))&handle_futexfd_ioctl,
		[HANDLE_TYPE_PIDFD]           = (syscall_slong_t (KCALL *)(void *__restrict, ioctl_t, USER UNCHECKED void *, iomode_t))&handle_pidfd_ioctl,
		[HANDLE_TYPE_MODULE]          = (syscall_slong_t (KCALL *)(void *__restrict, ioctl_t, USER UNCHECKED void *, iomode_t))&handle_module_ioctl,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (syscall_slong_t (KCALL *)(void *__restrict, ioctl_t, USER UNCHECKED void *, iomode_t))&handle_driver_loadlist_ioctl,
		[HANDLE_TYPE_REFCOUNTABLE]    = (syscall_slong_t (KCALL *)(void *__restrict, ioctl_t, USER UNCHECKED void *, iomode_t))&handle_refcountable_ioctl,
		[HANDLE_TYPE_NOTIFYFD]        = (syscall_slong_t (KCALL *)(void *__restrict, ioctl_t, USER UNCHECKED void *, iomode_t))&handle_notifyfd_ioctl,
		[HANDLE_TYPE_DIRHANDLEX]      = (syscall_slong_t (KCALL *)(void *__restrict, ioctl_t, USER UNCHECKED void *, iomode_t))&handle_dirhandlex_ioctl
	},
	.h_truncate = {
		[HANDLE_TYPE_UNDEFINED]       = (void (KCALL *)(void *__restrict, pos_t))&handle_undefined_truncate,
		[HANDLE_TYPE_MFILE]           = (void (KCALL *)(void *__restrict, pos_t))&handle_mfile_truncate,
		[HANDLE_TYPE_DIRENT]          = (void (KCALL *)(void *__restrict, pos_t))&handle_dirent_truncate,
		[HANDLE_TYPE_PATH]            = (void (KCALL *)(void *__restrict, pos_t))&handle_path_truncate,
		[HANDLE_TYPE_FILEHANDLE]      = (void (KCALL *)(void *__restrict, pos_t))&handle_filehandle_truncate,
		[HANDLE_TYPE_TEMPHANDLE]      = (void (KCALL *)(void *__restrict, pos_t))&handle_temphandle_truncate,
		[HANDLE_TYPE_DIRHANDLE]       = (void (KCALL *)(void *__restrict, pos_t))&handle_dirhandle_truncate,
		[HANDLE_TYPE_FIFOHANDLE]      = (void (KCALL *)(void *__restrict, pos_t))&handle_fifohandle_truncate,
		[HANDLE_TYPE_SOCKET]          = (void (KCALL *)(void *__restrict, pos_t))&handle_socket_truncate,
		[HANDLE_TYPE_EPOLL]           = (void (KCALL *)(void *__restrict, pos_t))&handle_epoll_truncate,
		[HANDLE_TYPE_PIPE]            = (void (KCALL *)(void *__restrict, pos_t))&handle_pipe_truncate,
		[HANDLE_TYPE_PIPE_READER]     = (void (KCALL *)(void *__restrict, pos_t))&handle_pipe_reader_truncate,
		[HANDLE_TYPE_PIPE_WRITER]     = (void (KCALL *)(void *__restrict, pos_t))&handle_pipe_writer_truncate,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (void (KCALL *)(void *__restrict, pos_t))&handle_eventfd_fence_truncate,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (void (KCALL *)(void *__restrict, pos_t))&handle_eventfd_sema_truncate,
		[HANDLE_TYPE_SIGNALFD]        = (void (KCALL *)(void *__restrict, pos_t))&handle_signalfd_truncate,
		[HANDLE_TYPE_FUTEXFD]         = (void (KCALL *)(void *__restrict, pos_t))&handle_futexfd_truncate,
		[HANDLE_TYPE_PIDFD]           = (void (KCALL *)(void *__restrict, pos_t))&handle_pidfd_truncate,
		[HANDLE_TYPE_MODULE]          = (void (KCALL *)(void *__restrict, pos_t))&handle_module_truncate,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (void (KCALL *)(void *__restrict, pos_t))&handle_driver_loadlist_truncate,
		[HANDLE_TYPE_REFCOUNTABLE]    = (void (KCALL *)(void *__restrict, pos_t))&handle_refcountable_truncate,
		[HANDLE_TYPE_NOTIFYFD]        = (void (KCALL *)(void *__restrict, pos_t))&handle_notifyfd_truncate,
		[HANDLE_TYPE_DIRHANDLEX]      = (void (KCALL *)(void *__restrict, pos_t))&handle_dirhandlex_truncate
	},
	.h_mmap = {
		[HANDLE_TYPE_UNDEFINED]       = (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_undefined_mmap,
		[HANDLE_TYPE_MFILE]           = (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_mfile_mmap,
		[HANDLE_TYPE_DIRENT]          = (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_dirent_mmap,
		[HANDLE_TYPE_PATH]            = (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_path_mmap,
		[HANDLE_TYPE_FILEHANDLE]      = (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_filehandle_mmap,
		[HANDLE_TYPE_TEMPHANDLE]      = (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_temphandle_mmap,
		[HANDLE_TYPE_DIRHANDLE]       = (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_dirhandle_mmap,
		[HANDLE_TYPE_FIFOHANDLE]      = (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_fifohandle_mmap,
		[HANDLE_TYPE_SOCKET]          = (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_socket_mmap,
		[HANDLE_TYPE_EPOLL]           = (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_epoll_mmap,
		[HANDLE_TYPE_PIPE]            = (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_pipe_mmap,
		[HANDLE_TYPE_PIPE_READER]     = (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_pipe_reader_mmap,
		[HANDLE_TYPE_PIPE_WRITER]     = (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_pipe_writer_mmap,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_eventfd_fence_mmap,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_eventfd_sema_mmap,
		[HANDLE_TYPE_SIGNALFD]        = (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_signalfd_mmap,
		[HANDLE_TYPE_FUTEXFD]         = (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_futexfd_mmap,
		[HANDLE_TYPE_PIDFD]           = (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_pidfd_mmap,
		[HANDLE_TYPE_MODULE]          = (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_module_mmap,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_driver_loadlist_mmap,
		[HANDLE_TYPE_REFCOUNTABLE]    = (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_refcountable_mmap,
		[HANDLE_TYPE_NOTIFYFD]        = (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_notifyfd_mmap,
		[HANDLE_TYPE_DIRHANDLEX]      = (void (KCALL *)(void *__restrict, struct handle_mmap_info *__restrict))&handle_dirhandlex_mmap
	},
	.h_allocate = {
		[HANDLE_TYPE_UNDEFINED]       = (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_undefined_allocate,
		[HANDLE_TYPE_MFILE]           = (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_mfile_allocate,
		[HANDLE_TYPE_DIRENT]          = (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_dirent_allocate,
		[HANDLE_TYPE_PATH]            = (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_path_allocate,
		[HANDLE_TYPE_FILEHANDLE]      = (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_filehandle_allocate,
		[HANDLE_TYPE_TEMPHANDLE]      = (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_temphandle_allocate,
		[HANDLE_TYPE_DIRHANDLE]       = (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_dirhandle_allocate,
		[HANDLE_TYPE_FIFOHANDLE]      = (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_fifohandle_allocate,
		[HANDLE_TYPE_SOCKET]          = (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_socket_allocate,
		[HANDLE_TYPE_EPOLL]           = (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_epoll_allocate,
		[HANDLE_TYPE_PIPE]            = (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_pipe_allocate,
		[HANDLE_TYPE_PIPE_READER]     = (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_pipe_reader_allocate,
		[HANDLE_TYPE_PIPE_WRITER]     = (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_pipe_writer_allocate,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_eventfd_fence_allocate,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_eventfd_sema_allocate,
		[HANDLE_TYPE_SIGNALFD]        = (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_signalfd_allocate,
		[HANDLE_TYPE_FUTEXFD]         = (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_futexfd_allocate,
		[HANDLE_TYPE_PIDFD]           = (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_pidfd_allocate,
		[HANDLE_TYPE_MODULE]          = (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_module_allocate,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_driver_loadlist_allocate,
		[HANDLE_TYPE_REFCOUNTABLE]    = (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_refcountable_allocate,
		[HANDLE_TYPE_NOTIFYFD]        = (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_notifyfd_allocate,
		[HANDLE_TYPE_DIRHANDLEX]      = (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_dirhandlex_allocate
	},
	.h_sync = {
		[HANDLE_TYPE_UNDEFINED]       = (void (KCALL *)(void *__restrict))&handle_undefined_sync,
		[HANDLE_TYPE_MFILE]           = (void (KCALL *)(void *__restrict))&handle_mfile_sync,
		[HANDLE_TYPE_DIRENT]          = (void (KCALL *)(void *__restrict))&handle_dirent_sync,
		[HANDLE_TYPE_PATH]            = (void (KCALL *)(void *__restrict))&handle_path_sync,
		[HANDLE_TYPE_FILEHANDLE]      = (void (KCALL *)(void *__restrict))&handle_filehandle_sync,
		[HANDLE_TYPE_TEMPHANDLE]      = (void (KCALL *)(void *__restrict))&handle_temphandle_sync,
		[HANDLE_TYPE_DIRHANDLE]       = (void (KCALL *)(void *__restrict))&handle_dirhandle_sync,
		[HANDLE_TYPE_FIFOHANDLE]      = (void (KCALL *)(void *__restrict))&handle_fifohandle_sync,
		[HANDLE_TYPE_SOCKET]          = (void (KCALL *)(void *__restrict))&handle_socket_sync,
		[HANDLE_TYPE_EPOLL]           = (void (KCALL *)(void *__restrict))&handle_epoll_sync,
		[HANDLE_TYPE_PIPE]            = (void (KCALL *)(void *__restrict))&handle_pipe_sync,
		[HANDLE_TYPE_PIPE_READER]     = (void (KCALL *)(void *__restrict))&handle_pipe_reader_sync,
		[HANDLE_TYPE_PIPE_WRITER]     = (void (KCALL *)(void *__restrict))&handle_pipe_writer_sync,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (void (KCALL *)(void *__restrict))&handle_eventfd_fence_sync,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (void (KCALL *)(void *__restrict))&handle_eventfd_sema_sync,
		[HANDLE_TYPE_SIGNALFD]        = (void (KCALL *)(void *__restrict))&handle_signalfd_sync,
		[HANDLE_TYPE_FUTEXFD]         = (void (KCALL *)(void *__restrict))&handle_futexfd_sync,
		[HANDLE_TYPE_PIDFD]           = (void (KCALL *)(void *__restrict))&handle_pidfd_sync,
		[HANDLE_TYPE_MODULE]          = (void (KCALL *)(void *__restrict))&handle_module_sync,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (void (KCALL *)(void *__restrict))&handle_driver_loadlist_sync,
		[HANDLE_TYPE_REFCOUNTABLE]    = (void (KCALL *)(void *__restrict))&handle_refcountable_sync,
		[HANDLE_TYPE_NOTIFYFD]        = (void (KCALL *)(void *__restrict))&handle_notifyfd_sync,
		[HANDLE_TYPE_DIRHANDLEX]      = (void (KCALL *)(void *__restrict))&handle_dirhandlex_sync
	},
	.h_datasync = {
		[HANDLE_TYPE_UNDEFINED]       = (void (KCALL *)(void *__restrict))&handle_undefined_datasync,
		[HANDLE_TYPE_MFILE]           = (void (KCALL *)(void *__restrict))&handle_mfile_datasync,
		[HANDLE_TYPE_DIRENT]          = (void (KCALL *)(void *__restrict))&handle_dirent_datasync,
		[HANDLE_TYPE_PATH]            = (void (KCALL *)(void *__restrict))&handle_path_datasync,
		[HANDLE_TYPE_FILEHANDLE]      = (void (KCALL *)(void *__restrict))&handle_filehandle_datasync,
		[HANDLE_TYPE_TEMPHANDLE]      = (void (KCALL *)(void *__restrict))&handle_temphandle_datasync,
		[HANDLE_TYPE_DIRHANDLE]       = (void (KCALL *)(void *__restrict))&handle_dirhandle_datasync,
		[HANDLE_TYPE_FIFOHANDLE]      = (void (KCALL *)(void *__restrict))&handle_fifohandle_datasync,
		[HANDLE_TYPE_SOCKET]          = (void (KCALL *)(void *__restrict))&handle_socket_datasync,
		[HANDLE_TYPE_EPOLL]           = (void (KCALL *)(void *__restrict))&handle_epoll_datasync,
		[HANDLE_TYPE_PIPE]            = (void (KCALL *)(void *__restrict))&handle_pipe_datasync,
		[HANDLE_TYPE_PIPE_READER]     = (void (KCALL *)(void *__restrict))&handle_pipe_reader_datasync,
		[HANDLE_TYPE_PIPE_WRITER]     = (void (KCALL *)(void *__restrict))&handle_pipe_writer_datasync,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (void (KCALL *)(void *__restrict))&handle_eventfd_fence_datasync,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (void (KCALL *)(void *__restrict))&handle_eventfd_sema_datasync,
		[HANDLE_TYPE_SIGNALFD]        = (void (KCALL *)(void *__restrict))&handle_signalfd_datasync,
		[HANDLE_TYPE_FUTEXFD]         = (void (KCALL *)(void *__restrict))&handle_futexfd_datasync,
		[HANDLE_TYPE_PIDFD]           = (void (KCALL *)(void *__restrict))&handle_pidfd_datasync,
		[HANDLE_TYPE_MODULE]          = (void (KCALL *)(void *__restrict))&handle_module_datasync,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (void (KCALL *)(void *__restrict))&handle_driver_loadlist_datasync,
		[HANDLE_TYPE_REFCOUNTABLE]    = (void (KCALL *)(void *__restrict))&handle_refcountable_datasync,
		[HANDLE_TYPE_NOTIFYFD]        = (void (KCALL *)(void *__restrict))&handle_notifyfd_datasync,
		[HANDLE_TYPE_DIRHANDLEX]      = (void (KCALL *)(void *__restrict))&handle_dirhandlex_datasync
	},
	.h_stat = {
		[HANDLE_TYPE_UNDEFINED]       = (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_undefined_stat,
		[HANDLE_TYPE_MFILE]           = (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_mfile_stat,
		[HANDLE_TYPE_DIRENT]          = (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_dirent_stat,
		[HANDLE_TYPE_PATH]            = (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_path_stat,
		[HANDLE_TYPE_FILEHANDLE]      = (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_filehandle_stat,
		[HANDLE_TYPE_TEMPHANDLE]      = (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_temphandle_stat,
		[HANDLE_TYPE_DIRHANDLE]       = (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_dirhandle_stat,
		[HANDLE_TYPE_FIFOHANDLE]      = (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_fifohandle_stat,
		[HANDLE_TYPE_SOCKET]          = (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_socket_stat,
		[HANDLE_TYPE_EPOLL]           = (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_epoll_stat,
		[HANDLE_TYPE_PIPE]            = (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_pipe_stat,
		[HANDLE_TYPE_PIPE_READER]     = (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_pipe_reader_stat,
		[HANDLE_TYPE_PIPE_WRITER]     = (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_pipe_writer_stat,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_eventfd_fence_stat,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_eventfd_sema_stat,
		[HANDLE_TYPE_SIGNALFD]        = (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_signalfd_stat,
		[HANDLE_TYPE_FUTEXFD]         = (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_futexfd_stat,
		[HANDLE_TYPE_PIDFD]           = (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_pidfd_stat,
		[HANDLE_TYPE_MODULE]          = (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_module_stat,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_driver_loadlist_stat,
		[HANDLE_TYPE_REFCOUNTABLE]    = (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_refcountable_stat,
		[HANDLE_TYPE_NOTIFYFD]        = (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_notifyfd_stat,
		[HANDLE_TYPE_DIRHANDLEX]      = (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_dirhandlex_stat
	},
	.h_pollconnect = {
		[HANDLE_TYPE_UNDEFINED]       = (void (KCALL *)(void *__restrict, poll_mode_t))&handle_undefined_pollconnect,
		[HANDLE_TYPE_MFILE]           = (void (KCALL *)(void *__restrict, poll_mode_t))&handle_mfile_pollconnect,
		[HANDLE_TYPE_DIRENT]          = (void (KCALL *)(void *__restrict, poll_mode_t))&handle_dirent_pollconnect,
		[HANDLE_TYPE_PATH]            = (void (KCALL *)(void *__restrict, poll_mode_t))&handle_path_pollconnect,
		[HANDLE_TYPE_FILEHANDLE]      = (void (KCALL *)(void *__restrict, poll_mode_t))&handle_filehandle_pollconnect,
		[HANDLE_TYPE_TEMPHANDLE]      = (void (KCALL *)(void *__restrict, poll_mode_t))&handle_temphandle_pollconnect,
		[HANDLE_TYPE_DIRHANDLE]       = (void (KCALL *)(void *__restrict, poll_mode_t))&handle_dirhandle_pollconnect,
		[HANDLE_TYPE_FIFOHANDLE]      = (void (KCALL *)(void *__restrict, poll_mode_t))&handle_fifohandle_pollconnect,
		[HANDLE_TYPE_SOCKET]          = (void (KCALL *)(void *__restrict, poll_mode_t))&handle_socket_pollconnect,
		[HANDLE_TYPE_EPOLL]           = (void (KCALL *)(void *__restrict, poll_mode_t))&handle_epoll_pollconnect,
		[HANDLE_TYPE_PIPE]            = (void (KCALL *)(void *__restrict, poll_mode_t))&handle_pipe_pollconnect,
		[HANDLE_TYPE_PIPE_READER]     = (void (KCALL *)(void *__restrict, poll_mode_t))&handle_pipe_reader_pollconnect,
		[HANDLE_TYPE_PIPE_WRITER]     = (void (KCALL *)(void *__restrict, poll_mode_t))&handle_pipe_writer_pollconnect,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (void (KCALL *)(void *__restrict, poll_mode_t))&handle_eventfd_fence_pollconnect,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (void (KCALL *)(void *__restrict, poll_mode_t))&handle_eventfd_sema_pollconnect,
		[HANDLE_TYPE_SIGNALFD]        = (void (KCALL *)(void *__restrict, poll_mode_t))&handle_signalfd_pollconnect,
		[HANDLE_TYPE_FUTEXFD]         = (void (KCALL *)(void *__restrict, poll_mode_t))&handle_futexfd_pollconnect,
		[HANDLE_TYPE_PIDFD]           = (void (KCALL *)(void *__restrict, poll_mode_t))&handle_pidfd_pollconnect,
		[HANDLE_TYPE_MODULE]          = (void (KCALL *)(void *__restrict, poll_mode_t))&handle_module_pollconnect,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (void (KCALL *)(void *__restrict, poll_mode_t))&handle_driver_loadlist_pollconnect,
		[HANDLE_TYPE_REFCOUNTABLE]    = (void (KCALL *)(void *__restrict, poll_mode_t))&handle_refcountable_pollconnect,
		[HANDLE_TYPE_NOTIFYFD]        = (void (KCALL *)(void *__restrict, poll_mode_t))&handle_notifyfd_pollconnect,
		[HANDLE_TYPE_DIRHANDLEX]      = (void (KCALL *)(void *__restrict, poll_mode_t))&handle_dirhandlex_pollconnect
	},
	.h_polltest = {
		[HANDLE_TYPE_UNDEFINED]       = (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_undefined_polltest,
		[HANDLE_TYPE_MFILE]           = (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_mfile_polltest,
		[HANDLE_TYPE_DIRENT]          = (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_dirent_polltest,
		[HANDLE_TYPE_PATH]            = (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_path_polltest,
		[HANDLE_TYPE_FILEHANDLE]      = (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_filehandle_polltest,
		[HANDLE_TYPE_TEMPHANDLE]      = (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_temphandle_polltest,
		[HANDLE_TYPE_DIRHANDLE]       = (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_dirhandle_polltest,
		[HANDLE_TYPE_FIFOHANDLE]      = (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_fifohandle_polltest,
		[HANDLE_TYPE_SOCKET]          = (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_socket_polltest,
		[HANDLE_TYPE_EPOLL]           = (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_epoll_polltest,
		[HANDLE_TYPE_PIPE]            = (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_pipe_polltest,
		[HANDLE_TYPE_PIPE_READER]     = (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_pipe_reader_polltest,
		[HANDLE_TYPE_PIPE_WRITER]     = (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_pipe_writer_polltest,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_eventfd_fence_polltest,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_eventfd_sema_polltest,
		[HANDLE_TYPE_SIGNALFD]        = (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_signalfd_polltest,
		[HANDLE_TYPE_FUTEXFD]         = (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_futexfd_polltest,
		[HANDLE_TYPE_PIDFD]           = (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_pidfd_polltest,
		[HANDLE_TYPE_MODULE]          = (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_module_polltest,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_driver_loadlist_polltest,
		[HANDLE_TYPE_REFCOUNTABLE]    = (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_refcountable_polltest,
		[HANDLE_TYPE_NOTIFYFD]        = (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_notifyfd_polltest,
		[HANDLE_TYPE_DIRHANDLEX]      = (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_dirhandlex_polltest
	},
	.h_tryas = {
		[HANDLE_TYPE_UNDEFINED]       = (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_undefined_tryas,
		[HANDLE_TYPE_MFILE]           = (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_mfile_tryas,
		[HANDLE_TYPE_DIRENT]          = (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_dirent_tryas,
		[HANDLE_TYPE_PATH]            = (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_path_tryas,
		[HANDLE_TYPE_FILEHANDLE]      = (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_filehandle_tryas,
		[HANDLE_TYPE_TEMPHANDLE]      = (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_temphandle_tryas,
		[HANDLE_TYPE_DIRHANDLE]       = (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_dirhandle_tryas,
		[HANDLE_TYPE_FIFOHANDLE]      = (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_fifohandle_tryas,
		[HANDLE_TYPE_SOCKET]          = (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_socket_tryas,
		[HANDLE_TYPE_EPOLL]           = (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_epoll_tryas,
		[HANDLE_TYPE_PIPE]            = (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_pipe_tryas,
		[HANDLE_TYPE_PIPE_READER]     = (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_pipe_reader_tryas,
		[HANDLE_TYPE_PIPE_WRITER]     = (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_pipe_writer_tryas,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_eventfd_fence_tryas,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_eventfd_sema_tryas,
		[HANDLE_TYPE_SIGNALFD]        = (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_signalfd_tryas,
		[HANDLE_TYPE_FUTEXFD]         = (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_futexfd_tryas,
		[HANDLE_TYPE_PIDFD]           = (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_pidfd_tryas,
		[HANDLE_TYPE_MODULE]          = (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_module_tryas,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_driver_loadlist_tryas,
		[HANDLE_TYPE_REFCOUNTABLE]    = (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_refcountable_tryas,
		[HANDLE_TYPE_NOTIFYFD]        = (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_notifyfd_tryas,
		[HANDLE_TYPE_DIRHANDLEX]      = (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_dirhandlex_tryas
	},
	.h_printlink = {
		[HANDLE_TYPE_UNDEFINED]       = (ssize_t (KCALL *)(void *__restrict, pformatprinter, void *))&handle_undefined_printlink,
		[HANDLE_TYPE_MFILE]           = (ssize_t (KCALL *)(void *__restrict, pformatprinter, void *))&handle_mfile_printlink,
		[HANDLE_TYPE_DIRENT]          = (ssize_t (KCALL *)(void *__restrict, pformatprinter, void *))&handle_dirent_printlink,
		[HANDLE_TYPE_PATH]            = (ssize_t (KCALL *)(void *__restrict, pformatprinter, void *))&handle_path_printlink,
		[HANDLE_TYPE_FILEHANDLE]      = (ssize_t (KCALL *)(void *__restrict, pformatprinter, void *))&handle_filehandle_printlink,
		[HANDLE_TYPE_TEMPHANDLE]      = (ssize_t (KCALL *)(void *__restrict, pformatprinter, void *))&handle_temphandle_printlink,
		[HANDLE_TYPE_DIRHANDLE]       = (ssize_t (KCALL *)(void *__restrict, pformatprinter, void *))&handle_dirhandle_printlink,
		[HANDLE_TYPE_FIFOHANDLE]      = (ssize_t (KCALL *)(void *__restrict, pformatprinter, void *))&handle_fifohandle_printlink,
		[HANDLE_TYPE_SOCKET]          = (ssize_t (KCALL *)(void *__restrict, pformatprinter, void *))&handle_socket_printlink,
		[HANDLE_TYPE_EPOLL]           = (ssize_t (KCALL *)(void *__restrict, pformatprinter, void *))&handle_epoll_printlink,
		[HANDLE_TYPE_PIPE]            = (ssize_t (KCALL *)(void *__restrict, pformatprinter, void *))&handle_pipe_printlink,
		[HANDLE_TYPE_PIPE_READER]     = (ssize_t (KCALL *)(void *__restrict, pformatprinter, void *))&handle_pipe_reader_printlink,
		[HANDLE_TYPE_PIPE_WRITER]     = (ssize_t (KCALL *)(void *__restrict, pformatprinter, void *))&handle_pipe_writer_printlink,
		[HANDLE_TYPE_EVENTFD_FENCE]   = (ssize_t (KCALL *)(void *__restrict, pformatprinter, void *))&handle_eventfd_fence_printlink,
		[HANDLE_TYPE_EVENTFD_SEMA]    = (ssize_t (KCALL *)(void *__restrict, pformatprinter, void *))&handle_eventfd_sema_printlink,
		[HANDLE_TYPE_SIGNALFD]        = (ssize_t (KCALL *)(void *__restrict, pformatprinter, void *))&handle_signalfd_printlink,
		[HANDLE_TYPE_FUTEXFD]         = (ssize_t (KCALL *)(void *__restrict, pformatprinter, void *))&handle_futexfd_printlink,
		[HANDLE_TYPE_PIDFD]           = (ssize_t (KCALL *)(void *__restrict, pformatprinter, void *))&handle_pidfd_printlink,
		[HANDLE_TYPE_MODULE]          = (ssize_t (KCALL *)(void *__restrict, pformatprinter, void *))&handle_module_printlink,
		[HANDLE_TYPE_DRIVER_LOADLIST] = (ssize_t (KCALL *)(void *__restrict, pformatprinter, void *))&handle_driver_loadlist_printlink,
		[HANDLE_TYPE_REFCOUNTABLE]    = (ssize_t (KCALL *)(void *__restrict, pformatprinter, void *))&handle_refcountable_printlink,
		[HANDLE_TYPE_NOTIFYFD]        = (ssize_t (KCALL *)(void *__restrict, pformatprinter, void *))&handle_notifyfd_printlink,
		[HANDLE_TYPE_DIRHANDLEX]      = (ssize_t (KCALL *)(void *__restrict, pformatprinter, void *))&handle_dirhandlex_printlink
	},
};



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
DEFINE_INTERN_WEAK_ALIAS(handle_mfile_tryas, handle_undefined_tryas);
INTERN BLOCKING NONNULL((1, 2)) ATTR_WEAK ATTR_SECTION(".text.kernel.handle_mfile.printlink") ssize_t KCALL
handle_mfile_printlink(struct mfile *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...) {
	return handle_generic_printlink(self, HANDLE_TYPE_MFILE, printer, arg);
}

/* Weakly define operators for `HANDLE_TYPE_DIRENT' (`struct fdirent') */
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_dirent_tryas, handle_undefined_tryas);
INTERN BLOCKING NONNULL((1, 2)) ATTR_WEAK ATTR_SECTION(".text.kernel.handle_dirent.printlink") ssize_t KCALL
handle_dirent_printlink(struct fdirent *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...) {
	return handle_generic_printlink(self, HANDLE_TYPE_DIRENT, printer, arg);
}

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
DEFINE_INTERN_WEAK_ALIAS(handle_path_tryas, handle_undefined_tryas);
INTERN BLOCKING NONNULL((1, 2)) ATTR_WEAK ATTR_SECTION(".text.kernel.handle_path.printlink") ssize_t KCALL
handle_path_printlink(struct path *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...) {
	return handle_generic_printlink(self, HANDLE_TYPE_PATH, printer, arg);
}

/* Weakly define operators for `HANDLE_TYPE_FILEHANDLE' (`struct filehandle') */
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_filehandle_tryas, handle_undefined_tryas);
INTERN BLOCKING NONNULL((1, 2)) ATTR_WEAK ATTR_SECTION(".text.kernel.handle_filehandle.printlink") ssize_t KCALL
handle_filehandle_printlink(struct filehandle *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...) {
	return handle_generic_printlink(self, HANDLE_TYPE_FILEHANDLE, printer, arg);
}

/* Weakly define operators for `HANDLE_TYPE_TEMPHANDLE' (`struct filehandle') */
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_temphandle_tryas, handle_undefined_tryas);
INTERN BLOCKING NONNULL((1, 2)) ATTR_WEAK ATTR_SECTION(".text.kernel.handle_temphandle.printlink") ssize_t KCALL
handle_temphandle_printlink(struct filehandle *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...) {
	return handle_generic_printlink(self, HANDLE_TYPE_TEMPHANDLE, printer, arg);
}

/* Weakly define operators for `HANDLE_TYPE_DIRHANDLE' (`struct dirhandle') */
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandle_tryas, handle_undefined_tryas);
INTERN BLOCKING NONNULL((1, 2)) ATTR_WEAK ATTR_SECTION(".text.kernel.handle_dirhandle.printlink") ssize_t KCALL
handle_dirhandle_printlink(struct dirhandle *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...) {
	return handle_generic_printlink(self, HANDLE_TYPE_DIRHANDLE, printer, arg);
}

/* Weakly define operators for `HANDLE_TYPE_FIFOHANDLE' (`struct fifohandle') */
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_fifohandle_tryas, handle_undefined_tryas);
INTERN BLOCKING NONNULL((1, 2)) ATTR_WEAK ATTR_SECTION(".text.kernel.handle_fifohandle.printlink") ssize_t KCALL
handle_fifohandle_printlink(struct fifohandle *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...) {
	return handle_generic_printlink(self, HANDLE_TYPE_FIFOHANDLE, printer, arg);
}

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
DEFINE_INTERN_WEAK_ALIAS(handle_socket_tryas, handle_undefined_tryas);
INTERN BLOCKING NONNULL((1, 2)) ATTR_WEAK ATTR_SECTION(".text.kernel.handle_socket.printlink") ssize_t KCALL
handle_socket_printlink(struct socket *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...) {
	return handle_generic_printlink(self, HANDLE_TYPE_SOCKET, printer, arg);
}

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
DEFINE_INTERN_WEAK_ALIAS(handle_epoll_tryas, handle_undefined_tryas);
INTERN BLOCKING NONNULL((1, 2)) ATTR_WEAK ATTR_SECTION(".text.kernel.handle_epoll.printlink") ssize_t KCALL
handle_epoll_printlink(struct epoll_controller *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...) {
	return handle_generic_printlink(self, HANDLE_TYPE_EPOLL, printer, arg);
}

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
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_tryas, handle_undefined_tryas);
INTERN BLOCKING NONNULL((1, 2)) ATTR_WEAK ATTR_SECTION(".text.kernel.handle_pipe.printlink") ssize_t KCALL
handle_pipe_printlink(struct pipe *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...) {
	return handle_generic_printlink(self, HANDLE_TYPE_PIPE, printer, arg);
}

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
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_tryas, handle_undefined_tryas);
INTERN BLOCKING NONNULL((1, 2)) ATTR_WEAK ATTR_SECTION(".text.kernel.handle_pipe_reader.printlink") ssize_t KCALL
handle_pipe_reader_printlink(struct pipe_reader *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...) {
	return handle_generic_printlink(self, HANDLE_TYPE_PIPE_READER, printer, arg);
}

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
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_tryas, handle_undefined_tryas);
INTERN BLOCKING NONNULL((1, 2)) ATTR_WEAK ATTR_SECTION(".text.kernel.handle_pipe_writer.printlink") ssize_t KCALL
handle_pipe_writer_printlink(struct pipe_writer *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...) {
	return handle_generic_printlink(self, HANDLE_TYPE_PIPE_WRITER, printer, arg);
}

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
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_tryas, handle_undefined_tryas);
INTERN BLOCKING NONNULL((1, 2)) ATTR_WEAK ATTR_SECTION(".text.kernel.handle_eventfd_fence.printlink") ssize_t KCALL
handle_eventfd_fence_printlink(struct eventfd *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...) {
	return handle_generic_printlink(self, HANDLE_TYPE_EVENTFD_FENCE, printer, arg);
}

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
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_tryas, handle_undefined_tryas);
INTERN BLOCKING NONNULL((1, 2)) ATTR_WEAK ATTR_SECTION(".text.kernel.handle_eventfd_sema.printlink") ssize_t KCALL
handle_eventfd_sema_printlink(struct eventfd *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...) {
	return handle_generic_printlink(self, HANDLE_TYPE_EVENTFD_SEMA, printer, arg);
}

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
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_tryas, handle_undefined_tryas);
INTERN BLOCKING NONNULL((1, 2)) ATTR_WEAK ATTR_SECTION(".text.kernel.handle_signalfd.printlink") ssize_t KCALL
handle_signalfd_printlink(struct signalfd *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...) {
	return handle_generic_printlink(self, HANDLE_TYPE_SIGNALFD, printer, arg);
}

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
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_tryas, handle_undefined_tryas);
INTERN BLOCKING NONNULL((1, 2)) ATTR_WEAK ATTR_SECTION(".text.kernel.handle_futexfd.printlink") ssize_t KCALL
handle_futexfd_printlink(struct mfutexfd *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...) {
	return handle_generic_printlink(self, HANDLE_TYPE_FUTEXFD, printer, arg);
}

/* Weakly define operators for `HANDLE_TYPE_PIDFD' (`struct taskpid') */
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_pidfd_tryas, handle_undefined_tryas);
INTERN BLOCKING NONNULL((1, 2)) ATTR_WEAK ATTR_SECTION(".text.kernel.handle_pidfd.printlink") ssize_t KCALL
handle_pidfd_printlink(struct taskpid *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...) {
	return handle_generic_printlink(self, HANDLE_TYPE_PIDFD, printer, arg);
}

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
DEFINE_INTERN_WEAK_ALIAS(handle_module_tryas, handle_undefined_tryas);
INTERN BLOCKING NONNULL((1, 2)) ATTR_WEAK ATTR_SECTION(".text.kernel.handle_module.printlink") ssize_t KCALL
handle_module_printlink(struct module *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...) {
	return handle_generic_printlink(self, HANDLE_TYPE_MODULE, printer, arg);
}

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
DEFINE_INTERN_WEAK_ALIAS(handle_driver_loadlist_tryas, handle_undefined_tryas);
INTERN BLOCKING NONNULL((1, 2)) ATTR_WEAK ATTR_SECTION(".text.kernel.handle_driver_loadlist.printlink") ssize_t KCALL
handle_driver_loadlist_printlink(struct driver_loadlist *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...) {
	return handle_generic_printlink(self, HANDLE_TYPE_DRIVER_LOADLIST, printer, arg);
}

/* Weakly define operators for `HANDLE_TYPE_REFCOUNTABLE' (`struct refcountable') */
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_refcountable_tryas, handle_undefined_tryas);
INTERN BLOCKING NONNULL((1, 2)) ATTR_WEAK ATTR_SECTION(".text.kernel.handle_refcountable.printlink") ssize_t KCALL
handle_refcountable_printlink(struct refcountable *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...) {
	return handle_generic_printlink(self, HANDLE_TYPE_REFCOUNTABLE, printer, arg);
}

/* Weakly define operators for `HANDLE_TYPE_NOTIFYFD' (`struct notifyfd') */
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_notifyfd_tryas, handle_undefined_tryas);
INTERN BLOCKING NONNULL((1, 2)) ATTR_WEAK ATTR_SECTION(".text.kernel.handle_notifyfd.printlink") ssize_t KCALL
handle_notifyfd_printlink(struct notifyfd *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...) {
	return handle_generic_printlink(self, HANDLE_TYPE_NOTIFYFD, printer, arg);
}

/* Weakly define operators for `HANDLE_TYPE_DIRHANDLEX' (`struct dirhandlex') */
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_weakgetref, handle_undefined_weakgetref);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_weaklckref, handle_undefined_weaklckref);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_weakdecref, handle_undefined_weakdecref);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_pollconnect, handle_undefined_pollconnect);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_polltest, handle_undefined_polltest);
DEFINE_INTERN_WEAK_ALIAS(handle_dirhandlex_tryas, handle_undefined_tryas);
INTERN BLOCKING NONNULL((1, 2)) ATTR_WEAK ATTR_SECTION(".text.kernel.handle_dirhandlex.printlink") ssize_t KCALL
handle_dirhandlex_printlink(struct dirhandlex *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...) {
	return handle_generic_printlink(self, HANDLE_TYPE_DIRHANDLEX, printer, arg);
}
//[[[end]]]



DECL_END

#endif /* !GUARD_KERNEL_SRC_FD_ROUTER_C */
