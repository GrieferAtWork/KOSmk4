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
#ifndef GUARD_KERNEL_SRC_USER_HANDLE_C
#define GUARD_KERNEL_SRC_USER_HANDLE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/aio.h>
#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/types.h>
#include <kernel/vm.h>

#include <kos/except/reason/fs.h>
#include <kos/except/reason/inval.h>
#include <kos/kernel/handle.h>

#include <assert.h>

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

for (local l: File.open("../../../../include/kos/kernel/handle.h")) {
	local name, id, tail;
	try name, id, tail = l.scanf(" # define HANDLE_TYPE_%[^ ] %[^ /] %[^]")...;
	catch (...) continue;
	if (name == "COUNT")
		continue;
	id = int(id);
	if (id >= #handle_types)
		handle_types.resize(id + 1, "undefined");
	tail = try tail.scanf(" /" "* `%[^']")[0] catch (...) "";
	handle_types[id] = (name.lower(), tail);
}

#define ARGS   name,attr,return_type,nothrow,cc,argv,throws,default_impl
local ops = HANDLE_OPERATOR_PROTOTYPES;

function needsPerTypeImpl(default_impl) {
	return "{HANDLE_TYPE}" in default_impl;
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
		print t,;
		if (!t.endswith("*"))
			print " ",;
		if (!needPerType && (n !in ["cmd"] || name !in ["ioctl", "hop"])) {
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
			"HANDLE_TYPE" : "HANDLE_TYPE_UNDEFINED"
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
for (local h_name, h_typ: handle_types) {
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
	for (local h_name, h_typ: handle_types) {
		if (!is_first)
			print ",";
		is_first = false;
		print "\t\t/" "* [HANDLE_TYPE_",;
		print h_name.upper(),;
		print "] ",;
		print " " * (longest_handle_name_length - #h_name),;
		print "= *" "/ (",;
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
				if (n == "self")
					t = h_typ + t.lsstrip("void");
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
				"HANDLE_TYPE" : "HANDLE_TYPE_" + h_name.upper()
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
INTERN NOBLOCK NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.tryincref") __BOOL NOTHROW(FCALL handle_undefined_tryincref)(void *__restrict UNUSED(self)) { return 1; }
INTERN NOBLOCK NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.incref") void NOTHROW(FCALL handle_undefined_incref)(void *__restrict UNUSED(self)) {  }
INTERN NOBLOCK NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.decref") void NOTHROW(FCALL handle_undefined_decref)(void *__restrict UNUSED(self)) {  }
INTERN NOBLOCK WUNUSED NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.refcnt") refcnt_t NOTHROW(FCALL handle_undefined_refcnt)(void const *__restrict UNUSED(self)) { return 0; }
INTERN WUNUSED NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.read") size_t KCALL handle_undefined_read(void *__restrict UNUSED(self), USER CHECKED void *UNUSED(dst), size_t UNUSED(num_bytes), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ); }
INTERN WUNUSED NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.write") size_t KCALL handle_undefined_write(void *__restrict UNUSED(self), USER CHECKED void const *UNUSED(src), size_t UNUSED(num_bytes), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE); }
INTERN WUNUSED NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.pread") size_t KCALL handle_undefined_pread(void *__restrict UNUSED(self), USER CHECKED void *UNUSED(dst), size_t UNUSED(num_bytes), pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ); }
INTERN WUNUSED NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.pwrite") size_t KCALL handle_undefined_pwrite(void *__restrict UNUSED(self), USER CHECKED void const *UNUSED(src), size_t UNUSED(num_bytes), pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE); }
INTERN WUNUSED NONNULL((1, 2)) ATTR_SECTION(".text.kernel.handle_undefined.readv") size_t KCALL handle_undefined_readv(void *__restrict UNUSED(self), struct aio_buffer *__restrict UNUSED(dst), size_t UNUSED(num_bytes), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ); }
INTERN WUNUSED NONNULL((1, 2)) ATTR_SECTION(".text.kernel.handle_undefined.writev") size_t KCALL handle_undefined_writev(void *__restrict UNUSED(self), struct aio_buffer *__restrict UNUSED(src), size_t UNUSED(num_bytes), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE); }
INTERN WUNUSED NONNULL((1, 2)) ATTR_SECTION(".text.kernel.handle_undefined.preadv") size_t KCALL handle_undefined_preadv(void *__restrict UNUSED(self), struct aio_buffer *__restrict UNUSED(dst), size_t UNUSED(num_bytes), pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ); }
INTERN WUNUSED NONNULL((1, 2)) ATTR_SECTION(".text.kernel.handle_undefined.pwritev") size_t KCALL handle_undefined_pwritev(void *__restrict UNUSED(self), struct aio_buffer *__restrict UNUSED(src), size_t UNUSED(num_bytes), pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE); }
INTERN WUNUSED NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.readdir") size_t KCALL handle_undefined_readdir(void *__restrict UNUSED(self), USER CHECKED struct dirent *UNUSED(buf), size_t UNUSED(bufsize), readdir_mode_t UNUSED(readdir_mode), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READDIR); }
INTERN NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.seek") pos_t KCALL handle_undefined_seek(void *__restrict UNUSED(self), off_t UNUSED(offset), unsigned int UNUSED(whence)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_SEEK); }
INTERN NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.ioctl") syscall_slong_t KCALL handle_undefined_ioctl(void *__restrict UNUSED(self), syscall_ulong_t cmd, USER UNCHECKED void *UNUSED(arg), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND, cmd); }
INTERN NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.truncate") void KCALL handle_undefined_truncate(void *__restrict UNUSED(self), pos_t UNUSED(new_size)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_TRUNC); }
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3, 4, 5)) ATTR_SECTION(".text.kernel.handle_undefined.mmap") REF struct vm_datablock *KCALL handle_undefined_mmap(void *__restrict UNUSED(self), pos_t *__restrict UNUSED(pminoffset), pos_t *__restrict UNUSED(pnumbytes), REF struct path **__restrict  UNUSED(pdatablock_fspath), REF struct directory_entry **__restrict UNUSED(pdatablock_fsname)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_MMAP); }
INTERN NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.allocate") pos_t KCALL handle_undefined_allocate(void *__restrict UNUSED(self), fallocate_mode_t UNUSED(mode), pos_t UNUSED(start), pos_t UNUSED(length)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_ALLOCATE); }
INTERN NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.sync") void KCALL handle_undefined_sync(void *__restrict UNUSED(self)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_SYNC); }
INTERN NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.datasync") void KCALL handle_undefined_datasync(void *__restrict UNUSED(self)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_DATASYNC); }
INTERN NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.stat") void KCALL handle_undefined_stat(void *__restrict UNUSED(self), USER CHECKED struct stat *UNUSED(result)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_STAT); }
INTERN WUNUSED NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.poll") poll_mode_t KCALL handle_undefined_poll(void *__restrict UNUSED(self), poll_mode_t UNUSED(what)) THROWS(...) { THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_POLL); }
INTERN NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.hop") syscall_slong_t KCALL handle_undefined_hop(void *__restrict UNUSED(self), syscall_ulong_t cmd, USER UNCHECKED void *UNUSED(arg), iomode_t UNUSED(mode)) THROWS(...) { THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND, cmd); }
INTERN NONNULL((1)) ATTR_SECTION(".text.kernel.handle_undefined.tryas") REF void *KCALL handle_undefined_tryas(void *__restrict UNUSED(self), uintptr_half_t UNUSED(wanted_type)) THROWS(E_WOULDBLOCK) { return NULL; }


/* Handle type database */
PUBLIC_CONST struct handle_types const handle_type_db = {
	/* .h_typename = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ "undefined",
		/* [HANDLE_TYPE_DATABLOCK]              = */ "datablock",
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ "blockdevice",
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ "directoryentry",
		/* [HANDLE_TYPE_FILE]                   = */ "file",
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ "oneshot_directory_file",
		/* [HANDLE_TYPE_PATH]                   = */ "path",
		/* [HANDLE_TYPE_FS]                     = */ "fs",
		/* [HANDLE_TYPE_VM]                     = */ "vm",
		/* [HANDLE_TYPE_TASK]                   = */ "task",
		/* [HANDLE_TYPE_CLOCK]                  = */ "clock",
		/* [HANDLE_TYPE_DRIVER]                 = */ "driver",
		/* [HANDLE_TYPE_PIPE]                   = */ "pipe",
		/* [HANDLE_TYPE_PIPE_READER]            = */ "pipe_reader",
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ "pipe_writer",
		/* [HANDLE_TYPE_PIDNS]                  = */ "pidns",
		/* [HANDLE_TYPE_DRIVER_STATE]           = */ "driver_state",
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ "characterdevice",
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ "eventfd_fence",
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ "eventfd_sema",
		/* [HANDLE_TYPE_SIGNALFD]               = */ "signalfd",
		/* [HANDLE_TYPE_DATAPART]               = */ "datapart",
		/* [HANDLE_TYPE_FUTEX]                  = */ "futex",
		/* [HANDLE_TYPE_FUTEXFD]                = */ "futexfd",
		/* [HANDLE_TYPE_DRIVER_SECTION]         = */ "driver_section",
		/* [HANDLE_TYPE_SOCKET]                 = */ "socket",
		/* [HANDLE_TYPE_UAIO]                   = */ "uaio",
		/* [HANDLE_TYPE_FIFO_USER]              = */ "fifo_user"
	},
	/* .h_tryincref = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (__BOOL (FCALL *)(void *__restrict))&handle_undefined_tryincref,
		/* [HANDLE_TYPE_DATABLOCK]              = */ (__BOOL (FCALL *)(void *__restrict))&handle_datablock_tryincref,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (__BOOL (FCALL *)(void *__restrict))&handle_blockdevice_tryincref,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (__BOOL (FCALL *)(void *__restrict))&handle_directoryentry_tryincref,
		/* [HANDLE_TYPE_FILE]                   = */ (__BOOL (FCALL *)(void *__restrict))&handle_file_tryincref,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (__BOOL (FCALL *)(void *__restrict))&handle_oneshot_directory_file_tryincref,
		/* [HANDLE_TYPE_PATH]                   = */ (__BOOL (FCALL *)(void *__restrict))&handle_path_tryincref,
		/* [HANDLE_TYPE_FS]                     = */ (__BOOL (FCALL *)(void *__restrict))&handle_fs_tryincref,
		/* [HANDLE_TYPE_VM]                     = */ (__BOOL (FCALL *)(void *__restrict))&handle_vm_tryincref,
		/* [HANDLE_TYPE_TASK]                   = */ (__BOOL (FCALL *)(void *__restrict))&handle_task_tryincref,
		/* [HANDLE_TYPE_CLOCK]                  = */ (__BOOL (FCALL *)(void *__restrict))&handle_clock_tryincref,
		/* [HANDLE_TYPE_DRIVER]                 = */ (__BOOL (FCALL *)(void *__restrict))&handle_driver_tryincref,
		/* [HANDLE_TYPE_PIPE]                   = */ (__BOOL (FCALL *)(void *__restrict))&handle_pipe_tryincref,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (__BOOL (FCALL *)(void *__restrict))&handle_pipe_reader_tryincref,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (__BOOL (FCALL *)(void *__restrict))&handle_pipe_writer_tryincref,
		/* [HANDLE_TYPE_PIDNS]                  = */ (__BOOL (FCALL *)(void *__restrict))&handle_pidns_tryincref,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */ (__BOOL (FCALL *)(void *__restrict))&handle_driver_state_tryincref,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (__BOOL (FCALL *)(void *__restrict))&handle_characterdevice_tryincref,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (__BOOL (FCALL *)(void *__restrict))&handle_eventfd_fence_tryincref,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (__BOOL (FCALL *)(void *__restrict))&handle_eventfd_sema_tryincref,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (__BOOL (FCALL *)(void *__restrict))&handle_signalfd_tryincref,
		/* [HANDLE_TYPE_DATAPART]               = */ (__BOOL (FCALL *)(void *__restrict))&handle_datapart_tryincref,
		/* [HANDLE_TYPE_FUTEX]                  = */ (__BOOL (FCALL *)(void *__restrict))&handle_futex_tryincref,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (__BOOL (FCALL *)(void *__restrict))&handle_futexfd_tryincref,
		/* [HANDLE_TYPE_DRIVER_SECTION]         = */ (__BOOL (FCALL *)(void *__restrict))&handle_driver_section_tryincref,
		/* [HANDLE_TYPE_SOCKET]                 = */ (__BOOL (FCALL *)(void *__restrict))&handle_socket_tryincref,
		/* [HANDLE_TYPE_UAIO]                   = */ (__BOOL (FCALL *)(void *__restrict))&handle_uaio_tryincref,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (__BOOL (FCALL *)(void *__restrict))&handle_fifo_user_tryincref
	},
	/* .h_incref = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (void (FCALL *)(void *__restrict))&handle_undefined_incref,
		/* [HANDLE_TYPE_DATABLOCK]              = */ (void (FCALL *)(void *__restrict))&handle_datablock_incref,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (void (FCALL *)(void *__restrict))&handle_blockdevice_incref,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (void (FCALL *)(void *__restrict))&handle_directoryentry_incref,
		/* [HANDLE_TYPE_FILE]                   = */ (void (FCALL *)(void *__restrict))&handle_file_incref,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (void (FCALL *)(void *__restrict))&handle_oneshot_directory_file_incref,
		/* [HANDLE_TYPE_PATH]                   = */ (void (FCALL *)(void *__restrict))&handle_path_incref,
		/* [HANDLE_TYPE_FS]                     = */ (void (FCALL *)(void *__restrict))&handle_fs_incref,
		/* [HANDLE_TYPE_VM]                     = */ (void (FCALL *)(void *__restrict))&handle_vm_incref,
		/* [HANDLE_TYPE_TASK]                   = */ (void (FCALL *)(void *__restrict))&handle_task_incref,
		/* [HANDLE_TYPE_CLOCK]                  = */ (void (FCALL *)(void *__restrict))&handle_clock_incref,
		/* [HANDLE_TYPE_DRIVER]                 = */ (void (FCALL *)(void *__restrict))&handle_driver_incref,
		/* [HANDLE_TYPE_PIPE]                   = */ (void (FCALL *)(void *__restrict))&handle_pipe_incref,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (void (FCALL *)(void *__restrict))&handle_pipe_reader_incref,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (void (FCALL *)(void *__restrict))&handle_pipe_writer_incref,
		/* [HANDLE_TYPE_PIDNS]                  = */ (void (FCALL *)(void *__restrict))&handle_pidns_incref,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */ (void (FCALL *)(void *__restrict))&handle_driver_state_incref,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (void (FCALL *)(void *__restrict))&handle_characterdevice_incref,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (void (FCALL *)(void *__restrict))&handle_eventfd_fence_incref,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (void (FCALL *)(void *__restrict))&handle_eventfd_sema_incref,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (void (FCALL *)(void *__restrict))&handle_signalfd_incref,
		/* [HANDLE_TYPE_DATAPART]               = */ (void (FCALL *)(void *__restrict))&handle_datapart_incref,
		/* [HANDLE_TYPE_FUTEX]                  = */ (void (FCALL *)(void *__restrict))&handle_futex_incref,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (void (FCALL *)(void *__restrict))&handle_futexfd_incref,
		/* [HANDLE_TYPE_DRIVER_SECTION]         = */ (void (FCALL *)(void *__restrict))&handle_driver_section_incref,
		/* [HANDLE_TYPE_SOCKET]                 = */ (void (FCALL *)(void *__restrict))&handle_socket_incref,
		/* [HANDLE_TYPE_UAIO]                   = */ (void (FCALL *)(void *__restrict))&handle_uaio_incref,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (void (FCALL *)(void *__restrict))&handle_fifo_user_incref
	},
	/* .h_decref = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (void (FCALL *)(void *__restrict))&handle_undefined_decref,
		/* [HANDLE_TYPE_DATABLOCK]              = */ (void (FCALL *)(void *__restrict))&handle_datablock_decref,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (void (FCALL *)(void *__restrict))&handle_blockdevice_decref,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (void (FCALL *)(void *__restrict))&handle_directoryentry_decref,
		/* [HANDLE_TYPE_FILE]                   = */ (void (FCALL *)(void *__restrict))&handle_file_decref,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (void (FCALL *)(void *__restrict))&handle_oneshot_directory_file_decref,
		/* [HANDLE_TYPE_PATH]                   = */ (void (FCALL *)(void *__restrict))&handle_path_decref,
		/* [HANDLE_TYPE_FS]                     = */ (void (FCALL *)(void *__restrict))&handle_fs_decref,
		/* [HANDLE_TYPE_VM]                     = */ (void (FCALL *)(void *__restrict))&handle_vm_decref,
		/* [HANDLE_TYPE_TASK]                   = */ (void (FCALL *)(void *__restrict))&handle_task_decref,
		/* [HANDLE_TYPE_CLOCK]                  = */ (void (FCALL *)(void *__restrict))&handle_clock_decref,
		/* [HANDLE_TYPE_DRIVER]                 = */ (void (FCALL *)(void *__restrict))&handle_driver_decref,
		/* [HANDLE_TYPE_PIPE]                   = */ (void (FCALL *)(void *__restrict))&handle_pipe_decref,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (void (FCALL *)(void *__restrict))&handle_pipe_reader_decref,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (void (FCALL *)(void *__restrict))&handle_pipe_writer_decref,
		/* [HANDLE_TYPE_PIDNS]                  = */ (void (FCALL *)(void *__restrict))&handle_pidns_decref,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */ (void (FCALL *)(void *__restrict))&handle_driver_state_decref,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (void (FCALL *)(void *__restrict))&handle_characterdevice_decref,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (void (FCALL *)(void *__restrict))&handle_eventfd_fence_decref,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (void (FCALL *)(void *__restrict))&handle_eventfd_sema_decref,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (void (FCALL *)(void *__restrict))&handle_signalfd_decref,
		/* [HANDLE_TYPE_DATAPART]               = */ (void (FCALL *)(void *__restrict))&handle_datapart_decref,
		/* [HANDLE_TYPE_FUTEX]                  = */ (void (FCALL *)(void *__restrict))&handle_futex_decref,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (void (FCALL *)(void *__restrict))&handle_futexfd_decref,
		/* [HANDLE_TYPE_DRIVER_SECTION]         = */ (void (FCALL *)(void *__restrict))&handle_driver_section_decref,
		/* [HANDLE_TYPE_SOCKET]                 = */ (void (FCALL *)(void *__restrict))&handle_socket_decref,
		/* [HANDLE_TYPE_UAIO]                   = */ (void (FCALL *)(void *__restrict))&handle_uaio_decref,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (void (FCALL *)(void *__restrict))&handle_fifo_user_decref
	},
	/* .h_refcnt = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_undefined_refcnt,
		/* [HANDLE_TYPE_DATABLOCK]              = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_datablock_refcnt,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_blockdevice_refcnt,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_directoryentry_refcnt,
		/* [HANDLE_TYPE_FILE]                   = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_file_refcnt,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_oneshot_directory_file_refcnt,
		/* [HANDLE_TYPE_PATH]                   = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_path_refcnt,
		/* [HANDLE_TYPE_FS]                     = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_fs_refcnt,
		/* [HANDLE_TYPE_VM]                     = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_vm_refcnt,
		/* [HANDLE_TYPE_TASK]                   = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_task_refcnt,
		/* [HANDLE_TYPE_CLOCK]                  = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_clock_refcnt,
		/* [HANDLE_TYPE_DRIVER]                 = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_driver_refcnt,
		/* [HANDLE_TYPE_PIPE]                   = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_pipe_refcnt,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_pipe_reader_refcnt,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_pipe_writer_refcnt,
		/* [HANDLE_TYPE_PIDNS]                  = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_pidns_refcnt,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_driver_state_refcnt,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_characterdevice_refcnt,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_eventfd_fence_refcnt,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_eventfd_sema_refcnt,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_signalfd_refcnt,
		/* [HANDLE_TYPE_DATAPART]               = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_datapart_refcnt,
		/* [HANDLE_TYPE_FUTEX]                  = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_futex_refcnt,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_futexfd_refcnt,
		/* [HANDLE_TYPE_DRIVER_SECTION]         = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_driver_section_refcnt,
		/* [HANDLE_TYPE_SOCKET]                 = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_socket_refcnt,
		/* [HANDLE_TYPE_UAIO]                   = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_uaio_refcnt,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (refcnt_t (FCALL *)(void const *__restrict))&handle_fifo_user_refcnt
	},
	/* .h_read = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_undefined_read,
		/* [HANDLE_TYPE_DATABLOCK]              = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_datablock_read,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_blockdevice_read,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_directoryentry_read,
		/* [HANDLE_TYPE_FILE]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_file_read,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_oneshot_directory_file_read,
		/* [HANDLE_TYPE_PATH]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_path_read,
		/* [HANDLE_TYPE_FS]                     = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_fs_read,
		/* [HANDLE_TYPE_VM]                     = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_vm_read,
		/* [HANDLE_TYPE_TASK]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_task_read,
		/* [HANDLE_TYPE_CLOCK]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_clock_read,
		/* [HANDLE_TYPE_DRIVER]                 = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_driver_read,
		/* [HANDLE_TYPE_PIPE]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_pipe_read,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_pipe_reader_read,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_pipe_writer_read,
		/* [HANDLE_TYPE_PIDNS]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_pidns_read,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_driver_state_read,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_characterdevice_read,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_eventfd_fence_read,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_eventfd_sema_read,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_signalfd_read,
		/* [HANDLE_TYPE_DATAPART]               = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_datapart_read,
		/* [HANDLE_TYPE_FUTEX]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_futex_read,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_futexfd_read,
		/* [HANDLE_TYPE_DRIVER_SECTION]         = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_driver_section_read,
		/* [HANDLE_TYPE_SOCKET]                 = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_socket_read,
		/* [HANDLE_TYPE_UAIO]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_uaio_read,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, iomode_t))&handle_fifo_user_read
	},
	/* .h_write = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_undefined_write,
		/* [HANDLE_TYPE_DATABLOCK]              = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_datablock_write,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_blockdevice_write,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_directoryentry_write,
		/* [HANDLE_TYPE_FILE]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_file_write,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_oneshot_directory_file_write,
		/* [HANDLE_TYPE_PATH]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_path_write,
		/* [HANDLE_TYPE_FS]                     = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_fs_write,
		/* [HANDLE_TYPE_VM]                     = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_vm_write,
		/* [HANDLE_TYPE_TASK]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_task_write,
		/* [HANDLE_TYPE_CLOCK]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_clock_write,
		/* [HANDLE_TYPE_DRIVER]                 = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_driver_write,
		/* [HANDLE_TYPE_PIPE]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_pipe_write,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_pipe_reader_write,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_pipe_writer_write,
		/* [HANDLE_TYPE_PIDNS]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_pidns_write,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_driver_state_write,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_characterdevice_write,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_eventfd_fence_write,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_eventfd_sema_write,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_signalfd_write,
		/* [HANDLE_TYPE_DATAPART]               = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_datapart_write,
		/* [HANDLE_TYPE_FUTEX]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_futex_write,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_futexfd_write,
		/* [HANDLE_TYPE_DRIVER_SECTION]         = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_driver_section_write,
		/* [HANDLE_TYPE_SOCKET]                 = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_socket_write,
		/* [HANDLE_TYPE_UAIO]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_uaio_write,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, iomode_t))&handle_fifo_user_write
	},
	/* .h_pread = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_undefined_pread,
		/* [HANDLE_TYPE_DATABLOCK]              = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_datablock_pread,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_blockdevice_pread,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_directoryentry_pread,
		/* [HANDLE_TYPE_FILE]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_file_pread,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_oneshot_directory_file_pread,
		/* [HANDLE_TYPE_PATH]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_path_pread,
		/* [HANDLE_TYPE_FS]                     = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_fs_pread,
		/* [HANDLE_TYPE_VM]                     = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_vm_pread,
		/* [HANDLE_TYPE_TASK]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_task_pread,
		/* [HANDLE_TYPE_CLOCK]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_clock_pread,
		/* [HANDLE_TYPE_DRIVER]                 = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_driver_pread,
		/* [HANDLE_TYPE_PIPE]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_pipe_pread,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_pipe_reader_pread,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_pipe_writer_pread,
		/* [HANDLE_TYPE_PIDNS]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_pidns_pread,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_driver_state_pread,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_characterdevice_pread,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_eventfd_fence_pread,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_eventfd_sema_pread,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_signalfd_pread,
		/* [HANDLE_TYPE_DATAPART]               = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_datapart_pread,
		/* [HANDLE_TYPE_FUTEX]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_futex_pread,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_futexfd_pread,
		/* [HANDLE_TYPE_DRIVER_SECTION]         = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_driver_section_pread,
		/* [HANDLE_TYPE_SOCKET]                 = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_socket_pread,
		/* [HANDLE_TYPE_UAIO]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_uaio_pread,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void *, size_t, pos_t, iomode_t))&handle_fifo_user_pread
	},
	/* .h_pwrite = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_undefined_pwrite,
		/* [HANDLE_TYPE_DATABLOCK]              = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_datablock_pwrite,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_blockdevice_pwrite,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_directoryentry_pwrite,
		/* [HANDLE_TYPE_FILE]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_file_pwrite,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_oneshot_directory_file_pwrite,
		/* [HANDLE_TYPE_PATH]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_path_pwrite,
		/* [HANDLE_TYPE_FS]                     = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_fs_pwrite,
		/* [HANDLE_TYPE_VM]                     = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_vm_pwrite,
		/* [HANDLE_TYPE_TASK]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_task_pwrite,
		/* [HANDLE_TYPE_CLOCK]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_clock_pwrite,
		/* [HANDLE_TYPE_DRIVER]                 = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_driver_pwrite,
		/* [HANDLE_TYPE_PIPE]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_pipe_pwrite,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_pipe_reader_pwrite,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_pipe_writer_pwrite,
		/* [HANDLE_TYPE_PIDNS]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_pidns_pwrite,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_driver_state_pwrite,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_characterdevice_pwrite,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_eventfd_fence_pwrite,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_eventfd_sema_pwrite,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_signalfd_pwrite,
		/* [HANDLE_TYPE_DATAPART]               = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_datapart_pwrite,
		/* [HANDLE_TYPE_FUTEX]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_futex_pwrite,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_futexfd_pwrite,
		/* [HANDLE_TYPE_DRIVER_SECTION]         = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_driver_section_pwrite,
		/* [HANDLE_TYPE_SOCKET]                 = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_socket_pwrite,
		/* [HANDLE_TYPE_UAIO]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_uaio_pwrite,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (size_t (KCALL *)(void *__restrict, USER CHECKED void const *, size_t, pos_t, iomode_t))&handle_fifo_user_pwrite
	},
	/* .h_readv = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_undefined_readv,
		/* [HANDLE_TYPE_DATABLOCK]              = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_datablock_readv,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_blockdevice_readv,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_directoryentry_readv,
		/* [HANDLE_TYPE_FILE]                   = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_file_readv,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_oneshot_directory_file_readv,
		/* [HANDLE_TYPE_PATH]                   = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_path_readv,
		/* [HANDLE_TYPE_FS]                     = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_fs_readv,
		/* [HANDLE_TYPE_VM]                     = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_vm_readv,
		/* [HANDLE_TYPE_TASK]                   = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_task_readv,
		/* [HANDLE_TYPE_CLOCK]                  = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_clock_readv,
		/* [HANDLE_TYPE_DRIVER]                 = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_driver_readv,
		/* [HANDLE_TYPE_PIPE]                   = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_pipe_readv,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_pipe_reader_readv,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_pipe_writer_readv,
		/* [HANDLE_TYPE_PIDNS]                  = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_pidns_readv,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_driver_state_readv,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_characterdevice_readv,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_eventfd_fence_readv,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_eventfd_sema_readv,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_signalfd_readv,
		/* [HANDLE_TYPE_DATAPART]               = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_datapart_readv,
		/* [HANDLE_TYPE_FUTEX]                  = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_futex_readv,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_futexfd_readv,
		/* [HANDLE_TYPE_DRIVER_SECTION]         = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_driver_section_readv,
		/* [HANDLE_TYPE_SOCKET]                 = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_socket_readv,
		/* [HANDLE_TYPE_UAIO]                   = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_uaio_readv,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_fifo_user_readv
	},
	/* .h_writev = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_undefined_writev,
		/* [HANDLE_TYPE_DATABLOCK]              = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_datablock_writev,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_blockdevice_writev,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_directoryentry_writev,
		/* [HANDLE_TYPE_FILE]                   = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_file_writev,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_oneshot_directory_file_writev,
		/* [HANDLE_TYPE_PATH]                   = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_path_writev,
		/* [HANDLE_TYPE_FS]                     = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_fs_writev,
		/* [HANDLE_TYPE_VM]                     = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_vm_writev,
		/* [HANDLE_TYPE_TASK]                   = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_task_writev,
		/* [HANDLE_TYPE_CLOCK]                  = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_clock_writev,
		/* [HANDLE_TYPE_DRIVER]                 = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_driver_writev,
		/* [HANDLE_TYPE_PIPE]                   = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_pipe_writev,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_pipe_reader_writev,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_pipe_writer_writev,
		/* [HANDLE_TYPE_PIDNS]                  = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_pidns_writev,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_driver_state_writev,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_characterdevice_writev,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_eventfd_fence_writev,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_eventfd_sema_writev,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_signalfd_writev,
		/* [HANDLE_TYPE_DATAPART]               = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_datapart_writev,
		/* [HANDLE_TYPE_FUTEX]                  = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_futex_writev,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_futexfd_writev,
		/* [HANDLE_TYPE_DRIVER_SECTION]         = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_driver_section_writev,
		/* [HANDLE_TYPE_SOCKET]                 = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_socket_writev,
		/* [HANDLE_TYPE_UAIO]                   = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_uaio_writev,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, iomode_t))&handle_fifo_user_writev
	},
	/* .h_preadv = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_undefined_preadv,
		/* [HANDLE_TYPE_DATABLOCK]              = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_datablock_preadv,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_blockdevice_preadv,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_directoryentry_preadv,
		/* [HANDLE_TYPE_FILE]                   = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_file_preadv,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_oneshot_directory_file_preadv,
		/* [HANDLE_TYPE_PATH]                   = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_path_preadv,
		/* [HANDLE_TYPE_FS]                     = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_fs_preadv,
		/* [HANDLE_TYPE_VM]                     = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_vm_preadv,
		/* [HANDLE_TYPE_TASK]                   = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_task_preadv,
		/* [HANDLE_TYPE_CLOCK]                  = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_clock_preadv,
		/* [HANDLE_TYPE_DRIVER]                 = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_driver_preadv,
		/* [HANDLE_TYPE_PIPE]                   = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_pipe_preadv,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_pipe_reader_preadv,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_pipe_writer_preadv,
		/* [HANDLE_TYPE_PIDNS]                  = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_pidns_preadv,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_driver_state_preadv,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_characterdevice_preadv,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_eventfd_fence_preadv,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_eventfd_sema_preadv,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_signalfd_preadv,
		/* [HANDLE_TYPE_DATAPART]               = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_datapart_preadv,
		/* [HANDLE_TYPE_FUTEX]                  = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_futex_preadv,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_futexfd_preadv,
		/* [HANDLE_TYPE_DRIVER_SECTION]         = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_driver_section_preadv,
		/* [HANDLE_TYPE_SOCKET]                 = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_socket_preadv,
		/* [HANDLE_TYPE_UAIO]                   = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_uaio_preadv,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_fifo_user_preadv
	},
	/* .h_pwritev = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_undefined_pwritev,
		/* [HANDLE_TYPE_DATABLOCK]              = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_datablock_pwritev,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_blockdevice_pwritev,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_directoryentry_pwritev,
		/* [HANDLE_TYPE_FILE]                   = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_file_pwritev,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_oneshot_directory_file_pwritev,
		/* [HANDLE_TYPE_PATH]                   = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_path_pwritev,
		/* [HANDLE_TYPE_FS]                     = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_fs_pwritev,
		/* [HANDLE_TYPE_VM]                     = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_vm_pwritev,
		/* [HANDLE_TYPE_TASK]                   = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_task_pwritev,
		/* [HANDLE_TYPE_CLOCK]                  = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_clock_pwritev,
		/* [HANDLE_TYPE_DRIVER]                 = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_driver_pwritev,
		/* [HANDLE_TYPE_PIPE]                   = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_pipe_pwritev,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_pipe_reader_pwritev,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_pipe_writer_pwritev,
		/* [HANDLE_TYPE_PIDNS]                  = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_pidns_pwritev,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_driver_state_pwritev,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_characterdevice_pwritev,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_eventfd_fence_pwritev,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_eventfd_sema_pwritev,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_signalfd_pwritev,
		/* [HANDLE_TYPE_DATAPART]               = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_datapart_pwritev,
		/* [HANDLE_TYPE_FUTEX]                  = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_futex_pwritev,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_futexfd_pwritev,
		/* [HANDLE_TYPE_DRIVER_SECTION]         = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_driver_section_pwritev,
		/* [HANDLE_TYPE_SOCKET]                 = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_socket_pwritev,
		/* [HANDLE_TYPE_UAIO]                   = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_uaio_pwritev,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (size_t (KCALL *)(void *__restrict, struct aio_buffer *__restrict, size_t, pos_t, iomode_t))&handle_fifo_user_pwritev
	},
	/* .h_readdir = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_undefined_readdir,
		/* [HANDLE_TYPE_DATABLOCK]              = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_datablock_readdir,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_blockdevice_readdir,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_directoryentry_readdir,
		/* [HANDLE_TYPE_FILE]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_file_readdir,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_oneshot_directory_file_readdir,
		/* [HANDLE_TYPE_PATH]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_path_readdir,
		/* [HANDLE_TYPE_FS]                     = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_fs_readdir,
		/* [HANDLE_TYPE_VM]                     = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_vm_readdir,
		/* [HANDLE_TYPE_TASK]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_task_readdir,
		/* [HANDLE_TYPE_CLOCK]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_clock_readdir,
		/* [HANDLE_TYPE_DRIVER]                 = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_driver_readdir,
		/* [HANDLE_TYPE_PIPE]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_pipe_readdir,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_pipe_reader_readdir,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_pipe_writer_readdir,
		/* [HANDLE_TYPE_PIDNS]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_pidns_readdir,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_driver_state_readdir,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_characterdevice_readdir,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_eventfd_fence_readdir,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_eventfd_sema_readdir,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_signalfd_readdir,
		/* [HANDLE_TYPE_DATAPART]               = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_datapart_readdir,
		/* [HANDLE_TYPE_FUTEX]                  = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_futex_readdir,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_futexfd_readdir,
		/* [HANDLE_TYPE_DRIVER_SECTION]         = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_driver_section_readdir,
		/* [HANDLE_TYPE_SOCKET]                 = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_socket_readdir,
		/* [HANDLE_TYPE_UAIO]                   = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_uaio_readdir,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (size_t (KCALL *)(void *__restrict, USER CHECKED struct dirent *, size_t, readdir_mode_t, iomode_t))&handle_fifo_user_readdir
	},
	/* .h_seek = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_undefined_seek,
		/* [HANDLE_TYPE_DATABLOCK]              = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_datablock_seek,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_blockdevice_seek,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_directoryentry_seek,
		/* [HANDLE_TYPE_FILE]                   = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_file_seek,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_oneshot_directory_file_seek,
		/* [HANDLE_TYPE_PATH]                   = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_path_seek,
		/* [HANDLE_TYPE_FS]                     = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_fs_seek,
		/* [HANDLE_TYPE_VM]                     = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_vm_seek,
		/* [HANDLE_TYPE_TASK]                   = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_task_seek,
		/* [HANDLE_TYPE_CLOCK]                  = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_clock_seek,
		/* [HANDLE_TYPE_DRIVER]                 = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_driver_seek,
		/* [HANDLE_TYPE_PIPE]                   = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_pipe_seek,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_pipe_reader_seek,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_pipe_writer_seek,
		/* [HANDLE_TYPE_PIDNS]                  = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_pidns_seek,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_driver_state_seek,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_characterdevice_seek,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_eventfd_fence_seek,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_eventfd_sema_seek,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_signalfd_seek,
		/* [HANDLE_TYPE_DATAPART]               = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_datapart_seek,
		/* [HANDLE_TYPE_FUTEX]                  = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_futex_seek,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_futexfd_seek,
		/* [HANDLE_TYPE_DRIVER_SECTION]         = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_driver_section_seek,
		/* [HANDLE_TYPE_SOCKET]                 = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_socket_seek,
		/* [HANDLE_TYPE_UAIO]                   = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_uaio_seek,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (pos_t (KCALL *)(void *__restrict, off_t, unsigned int))&handle_fifo_user_seek
	},
	/* .h_ioctl = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_undefined_ioctl,
		/* [HANDLE_TYPE_DATABLOCK]              = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_datablock_ioctl,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_blockdevice_ioctl,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_directoryentry_ioctl,
		/* [HANDLE_TYPE_FILE]                   = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_file_ioctl,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_oneshot_directory_file_ioctl,
		/* [HANDLE_TYPE_PATH]                   = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_path_ioctl,
		/* [HANDLE_TYPE_FS]                     = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_fs_ioctl,
		/* [HANDLE_TYPE_VM]                     = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_vm_ioctl,
		/* [HANDLE_TYPE_TASK]                   = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_task_ioctl,
		/* [HANDLE_TYPE_CLOCK]                  = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_clock_ioctl,
		/* [HANDLE_TYPE_DRIVER]                 = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_driver_ioctl,
		/* [HANDLE_TYPE_PIPE]                   = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_pipe_ioctl,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_pipe_reader_ioctl,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_pipe_writer_ioctl,
		/* [HANDLE_TYPE_PIDNS]                  = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_pidns_ioctl,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_driver_state_ioctl,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_characterdevice_ioctl,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_eventfd_fence_ioctl,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_eventfd_sema_ioctl,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_signalfd_ioctl,
		/* [HANDLE_TYPE_DATAPART]               = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_datapart_ioctl,
		/* [HANDLE_TYPE_FUTEX]                  = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_futex_ioctl,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_futexfd_ioctl,
		/* [HANDLE_TYPE_DRIVER_SECTION]         = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_driver_section_ioctl,
		/* [HANDLE_TYPE_SOCKET]                 = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_socket_ioctl,
		/* [HANDLE_TYPE_UAIO]                   = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_uaio_ioctl,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_fifo_user_ioctl
	},
	/* .h_truncate = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (void (KCALL *)(void *__restrict, pos_t))&handle_undefined_truncate,
		/* [HANDLE_TYPE_DATABLOCK]              = */ (void (KCALL *)(void *__restrict, pos_t))&handle_datablock_truncate,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (void (KCALL *)(void *__restrict, pos_t))&handle_blockdevice_truncate,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (void (KCALL *)(void *__restrict, pos_t))&handle_directoryentry_truncate,
		/* [HANDLE_TYPE_FILE]                   = */ (void (KCALL *)(void *__restrict, pos_t))&handle_file_truncate,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (void (KCALL *)(void *__restrict, pos_t))&handle_oneshot_directory_file_truncate,
		/* [HANDLE_TYPE_PATH]                   = */ (void (KCALL *)(void *__restrict, pos_t))&handle_path_truncate,
		/* [HANDLE_TYPE_FS]                     = */ (void (KCALL *)(void *__restrict, pos_t))&handle_fs_truncate,
		/* [HANDLE_TYPE_VM]                     = */ (void (KCALL *)(void *__restrict, pos_t))&handle_vm_truncate,
		/* [HANDLE_TYPE_TASK]                   = */ (void (KCALL *)(void *__restrict, pos_t))&handle_task_truncate,
		/* [HANDLE_TYPE_CLOCK]                  = */ (void (KCALL *)(void *__restrict, pos_t))&handle_clock_truncate,
		/* [HANDLE_TYPE_DRIVER]                 = */ (void (KCALL *)(void *__restrict, pos_t))&handle_driver_truncate,
		/* [HANDLE_TYPE_PIPE]                   = */ (void (KCALL *)(void *__restrict, pos_t))&handle_pipe_truncate,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (void (KCALL *)(void *__restrict, pos_t))&handle_pipe_reader_truncate,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (void (KCALL *)(void *__restrict, pos_t))&handle_pipe_writer_truncate,
		/* [HANDLE_TYPE_PIDNS]                  = */ (void (KCALL *)(void *__restrict, pos_t))&handle_pidns_truncate,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */ (void (KCALL *)(void *__restrict, pos_t))&handle_driver_state_truncate,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (void (KCALL *)(void *__restrict, pos_t))&handle_characterdevice_truncate,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (void (KCALL *)(void *__restrict, pos_t))&handle_eventfd_fence_truncate,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (void (KCALL *)(void *__restrict, pos_t))&handle_eventfd_sema_truncate,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (void (KCALL *)(void *__restrict, pos_t))&handle_signalfd_truncate,
		/* [HANDLE_TYPE_DATAPART]               = */ (void (KCALL *)(void *__restrict, pos_t))&handle_datapart_truncate,
		/* [HANDLE_TYPE_FUTEX]                  = */ (void (KCALL *)(void *__restrict, pos_t))&handle_futex_truncate,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (void (KCALL *)(void *__restrict, pos_t))&handle_futexfd_truncate,
		/* [HANDLE_TYPE_DRIVER_SECTION]         = */ (void (KCALL *)(void *__restrict, pos_t))&handle_driver_section_truncate,
		/* [HANDLE_TYPE_SOCKET]                 = */ (void (KCALL *)(void *__restrict, pos_t))&handle_socket_truncate,
		/* [HANDLE_TYPE_UAIO]                   = */ (void (KCALL *)(void *__restrict, pos_t))&handle_uaio_truncate,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (void (KCALL *)(void *__restrict, pos_t))&handle_fifo_user_truncate
	},
	/* .h_mmap = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_undefined_mmap,
		/* [HANDLE_TYPE_DATABLOCK]              = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_datablock_mmap,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_blockdevice_mmap,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_directoryentry_mmap,
		/* [HANDLE_TYPE_FILE]                   = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_file_mmap,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_oneshot_directory_file_mmap,
		/* [HANDLE_TYPE_PATH]                   = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_path_mmap,
		/* [HANDLE_TYPE_FS]                     = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_fs_mmap,
		/* [HANDLE_TYPE_VM]                     = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_vm_mmap,
		/* [HANDLE_TYPE_TASK]                   = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_task_mmap,
		/* [HANDLE_TYPE_CLOCK]                  = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_clock_mmap,
		/* [HANDLE_TYPE_DRIVER]                 = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_driver_mmap,
		/* [HANDLE_TYPE_PIPE]                   = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_pipe_mmap,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_pipe_reader_mmap,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_pipe_writer_mmap,
		/* [HANDLE_TYPE_PIDNS]                  = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_pidns_mmap,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_driver_state_mmap,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_characterdevice_mmap,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_eventfd_fence_mmap,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_eventfd_sema_mmap,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_signalfd_mmap,
		/* [HANDLE_TYPE_DATAPART]               = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_datapart_mmap,
		/* [HANDLE_TYPE_FUTEX]                  = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_futex_mmap,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_futexfd_mmap,
		/* [HANDLE_TYPE_DRIVER_SECTION]         = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_driver_section_mmap,
		/* [HANDLE_TYPE_SOCKET]                 = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_socket_mmap,
		/* [HANDLE_TYPE_UAIO]                   = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_uaio_mmap,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (REF struct vm_datablock *(KCALL *)(void *__restrict, pos_t *__restrict, pos_t *__restrict, REF struct path **__restrict , REF struct directory_entry **__restrict))&handle_fifo_user_mmap
	},
	/* .h_allocate = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_undefined_allocate,
		/* [HANDLE_TYPE_DATABLOCK]              = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_datablock_allocate,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_blockdevice_allocate,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_directoryentry_allocate,
		/* [HANDLE_TYPE_FILE]                   = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_file_allocate,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_oneshot_directory_file_allocate,
		/* [HANDLE_TYPE_PATH]                   = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_path_allocate,
		/* [HANDLE_TYPE_FS]                     = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_fs_allocate,
		/* [HANDLE_TYPE_VM]                     = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_vm_allocate,
		/* [HANDLE_TYPE_TASK]                   = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_task_allocate,
		/* [HANDLE_TYPE_CLOCK]                  = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_clock_allocate,
		/* [HANDLE_TYPE_DRIVER]                 = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_driver_allocate,
		/* [HANDLE_TYPE_PIPE]                   = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_pipe_allocate,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_pipe_reader_allocate,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_pipe_writer_allocate,
		/* [HANDLE_TYPE_PIDNS]                  = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_pidns_allocate,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_driver_state_allocate,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_characterdevice_allocate,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_eventfd_fence_allocate,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_eventfd_sema_allocate,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_signalfd_allocate,
		/* [HANDLE_TYPE_DATAPART]               = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_datapart_allocate,
		/* [HANDLE_TYPE_FUTEX]                  = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_futex_allocate,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_futexfd_allocate,
		/* [HANDLE_TYPE_DRIVER_SECTION]         = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_driver_section_allocate,
		/* [HANDLE_TYPE_SOCKET]                 = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_socket_allocate,
		/* [HANDLE_TYPE_UAIO]                   = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_uaio_allocate,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (pos_t (KCALL *)(void *__restrict, fallocate_mode_t, pos_t, pos_t))&handle_fifo_user_allocate
	},
	/* .h_sync = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (void (KCALL *)(void *__restrict))&handle_undefined_sync,
		/* [HANDLE_TYPE_DATABLOCK]              = */ (void (KCALL *)(void *__restrict))&handle_datablock_sync,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (void (KCALL *)(void *__restrict))&handle_blockdevice_sync,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (void (KCALL *)(void *__restrict))&handle_directoryentry_sync,
		/* [HANDLE_TYPE_FILE]                   = */ (void (KCALL *)(void *__restrict))&handle_file_sync,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (void (KCALL *)(void *__restrict))&handle_oneshot_directory_file_sync,
		/* [HANDLE_TYPE_PATH]                   = */ (void (KCALL *)(void *__restrict))&handle_path_sync,
		/* [HANDLE_TYPE_FS]                     = */ (void (KCALL *)(void *__restrict))&handle_fs_sync,
		/* [HANDLE_TYPE_VM]                     = */ (void (KCALL *)(void *__restrict))&handle_vm_sync,
		/* [HANDLE_TYPE_TASK]                   = */ (void (KCALL *)(void *__restrict))&handle_task_sync,
		/* [HANDLE_TYPE_CLOCK]                  = */ (void (KCALL *)(void *__restrict))&handle_clock_sync,
		/* [HANDLE_TYPE_DRIVER]                 = */ (void (KCALL *)(void *__restrict))&handle_driver_sync,
		/* [HANDLE_TYPE_PIPE]                   = */ (void (KCALL *)(void *__restrict))&handle_pipe_sync,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (void (KCALL *)(void *__restrict))&handle_pipe_reader_sync,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (void (KCALL *)(void *__restrict))&handle_pipe_writer_sync,
		/* [HANDLE_TYPE_PIDNS]                  = */ (void (KCALL *)(void *__restrict))&handle_pidns_sync,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */ (void (KCALL *)(void *__restrict))&handle_driver_state_sync,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (void (KCALL *)(void *__restrict))&handle_characterdevice_sync,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (void (KCALL *)(void *__restrict))&handle_eventfd_fence_sync,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (void (KCALL *)(void *__restrict))&handle_eventfd_sema_sync,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (void (KCALL *)(void *__restrict))&handle_signalfd_sync,
		/* [HANDLE_TYPE_DATAPART]               = */ (void (KCALL *)(void *__restrict))&handle_datapart_sync,
		/* [HANDLE_TYPE_FUTEX]                  = */ (void (KCALL *)(void *__restrict))&handle_futex_sync,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (void (KCALL *)(void *__restrict))&handle_futexfd_sync,
		/* [HANDLE_TYPE_DRIVER_SECTION]         = */ (void (KCALL *)(void *__restrict))&handle_driver_section_sync,
		/* [HANDLE_TYPE_SOCKET]                 = */ (void (KCALL *)(void *__restrict))&handle_socket_sync,
		/* [HANDLE_TYPE_UAIO]                   = */ (void (KCALL *)(void *__restrict))&handle_uaio_sync,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (void (KCALL *)(void *__restrict))&handle_fifo_user_sync
	},
	/* .h_datasync = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (void (KCALL *)(void *__restrict))&handle_undefined_datasync,
		/* [HANDLE_TYPE_DATABLOCK]              = */ (void (KCALL *)(void *__restrict))&handle_datablock_datasync,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (void (KCALL *)(void *__restrict))&handle_blockdevice_datasync,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (void (KCALL *)(void *__restrict))&handle_directoryentry_datasync,
		/* [HANDLE_TYPE_FILE]                   = */ (void (KCALL *)(void *__restrict))&handle_file_datasync,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (void (KCALL *)(void *__restrict))&handle_oneshot_directory_file_datasync,
		/* [HANDLE_TYPE_PATH]                   = */ (void (KCALL *)(void *__restrict))&handle_path_datasync,
		/* [HANDLE_TYPE_FS]                     = */ (void (KCALL *)(void *__restrict))&handle_fs_datasync,
		/* [HANDLE_TYPE_VM]                     = */ (void (KCALL *)(void *__restrict))&handle_vm_datasync,
		/* [HANDLE_TYPE_TASK]                   = */ (void (KCALL *)(void *__restrict))&handle_task_datasync,
		/* [HANDLE_TYPE_CLOCK]                  = */ (void (KCALL *)(void *__restrict))&handle_clock_datasync,
		/* [HANDLE_TYPE_DRIVER]                 = */ (void (KCALL *)(void *__restrict))&handle_driver_datasync,
		/* [HANDLE_TYPE_PIPE]                   = */ (void (KCALL *)(void *__restrict))&handle_pipe_datasync,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (void (KCALL *)(void *__restrict))&handle_pipe_reader_datasync,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (void (KCALL *)(void *__restrict))&handle_pipe_writer_datasync,
		/* [HANDLE_TYPE_PIDNS]                  = */ (void (KCALL *)(void *__restrict))&handle_pidns_datasync,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */ (void (KCALL *)(void *__restrict))&handle_driver_state_datasync,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (void (KCALL *)(void *__restrict))&handle_characterdevice_datasync,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (void (KCALL *)(void *__restrict))&handle_eventfd_fence_datasync,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (void (KCALL *)(void *__restrict))&handle_eventfd_sema_datasync,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (void (KCALL *)(void *__restrict))&handle_signalfd_datasync,
		/* [HANDLE_TYPE_DATAPART]               = */ (void (KCALL *)(void *__restrict))&handle_datapart_datasync,
		/* [HANDLE_TYPE_FUTEX]                  = */ (void (KCALL *)(void *__restrict))&handle_futex_datasync,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (void (KCALL *)(void *__restrict))&handle_futexfd_datasync,
		/* [HANDLE_TYPE_DRIVER_SECTION]         = */ (void (KCALL *)(void *__restrict))&handle_driver_section_datasync,
		/* [HANDLE_TYPE_SOCKET]                 = */ (void (KCALL *)(void *__restrict))&handle_socket_datasync,
		/* [HANDLE_TYPE_UAIO]                   = */ (void (KCALL *)(void *__restrict))&handle_uaio_datasync,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (void (KCALL *)(void *__restrict))&handle_fifo_user_datasync
	},
	/* .h_stat = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_undefined_stat,
		/* [HANDLE_TYPE_DATABLOCK]              = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_datablock_stat,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_blockdevice_stat,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_directoryentry_stat,
		/* [HANDLE_TYPE_FILE]                   = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_file_stat,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_oneshot_directory_file_stat,
		/* [HANDLE_TYPE_PATH]                   = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_path_stat,
		/* [HANDLE_TYPE_FS]                     = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_fs_stat,
		/* [HANDLE_TYPE_VM]                     = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_vm_stat,
		/* [HANDLE_TYPE_TASK]                   = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_task_stat,
		/* [HANDLE_TYPE_CLOCK]                  = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_clock_stat,
		/* [HANDLE_TYPE_DRIVER]                 = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_driver_stat,
		/* [HANDLE_TYPE_PIPE]                   = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_pipe_stat,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_pipe_reader_stat,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_pipe_writer_stat,
		/* [HANDLE_TYPE_PIDNS]                  = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_pidns_stat,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_driver_state_stat,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_characterdevice_stat,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_eventfd_fence_stat,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_eventfd_sema_stat,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_signalfd_stat,
		/* [HANDLE_TYPE_DATAPART]               = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_datapart_stat,
		/* [HANDLE_TYPE_FUTEX]                  = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_futex_stat,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_futexfd_stat,
		/* [HANDLE_TYPE_DRIVER_SECTION]         = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_driver_section_stat,
		/* [HANDLE_TYPE_SOCKET]                 = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_socket_stat,
		/* [HANDLE_TYPE_UAIO]                   = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_uaio_stat,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (void (KCALL *)(void *__restrict, USER CHECKED struct stat *))&handle_fifo_user_stat
	},
	/* .h_poll = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_undefined_poll,
		/* [HANDLE_TYPE_DATABLOCK]              = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_datablock_poll,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_blockdevice_poll,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_directoryentry_poll,
		/* [HANDLE_TYPE_FILE]                   = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_file_poll,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_oneshot_directory_file_poll,
		/* [HANDLE_TYPE_PATH]                   = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_path_poll,
		/* [HANDLE_TYPE_FS]                     = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_fs_poll,
		/* [HANDLE_TYPE_VM]                     = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_vm_poll,
		/* [HANDLE_TYPE_TASK]                   = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_task_poll,
		/* [HANDLE_TYPE_CLOCK]                  = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_clock_poll,
		/* [HANDLE_TYPE_DRIVER]                 = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_driver_poll,
		/* [HANDLE_TYPE_PIPE]                   = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_pipe_poll,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_pipe_reader_poll,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_pipe_writer_poll,
		/* [HANDLE_TYPE_PIDNS]                  = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_pidns_poll,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_driver_state_poll,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_characterdevice_poll,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_eventfd_fence_poll,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_eventfd_sema_poll,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_signalfd_poll,
		/* [HANDLE_TYPE_DATAPART]               = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_datapart_poll,
		/* [HANDLE_TYPE_FUTEX]                  = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_futex_poll,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_futexfd_poll,
		/* [HANDLE_TYPE_DRIVER_SECTION]         = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_driver_section_poll,
		/* [HANDLE_TYPE_SOCKET]                 = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_socket_poll,
		/* [HANDLE_TYPE_UAIO]                   = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_uaio_poll,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (poll_mode_t (KCALL *)(void *__restrict, poll_mode_t))&handle_fifo_user_poll
	},
	/* .h_hop = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_undefined_hop,
		/* [HANDLE_TYPE_DATABLOCK]              = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_datablock_hop,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_blockdevice_hop,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_directoryentry_hop,
		/* [HANDLE_TYPE_FILE]                   = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_file_hop,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_oneshot_directory_file_hop,
		/* [HANDLE_TYPE_PATH]                   = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_path_hop,
		/* [HANDLE_TYPE_FS]                     = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_fs_hop,
		/* [HANDLE_TYPE_VM]                     = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_vm_hop,
		/* [HANDLE_TYPE_TASK]                   = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_task_hop,
		/* [HANDLE_TYPE_CLOCK]                  = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_clock_hop,
		/* [HANDLE_TYPE_DRIVER]                 = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_driver_hop,
		/* [HANDLE_TYPE_PIPE]                   = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_pipe_hop,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_pipe_reader_hop,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_pipe_writer_hop,
		/* [HANDLE_TYPE_PIDNS]                  = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_pidns_hop,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_driver_state_hop,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_characterdevice_hop,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_eventfd_fence_hop,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_eventfd_sema_hop,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_signalfd_hop,
		/* [HANDLE_TYPE_DATAPART]               = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_datapart_hop,
		/* [HANDLE_TYPE_FUTEX]                  = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_futex_hop,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_futexfd_hop,
		/* [HANDLE_TYPE_DRIVER_SECTION]         = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_driver_section_hop,
		/* [HANDLE_TYPE_SOCKET]                 = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_socket_hop,
		/* [HANDLE_TYPE_UAIO]                   = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_uaio_hop,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (syscall_slong_t (KCALL *)(void *__restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&handle_fifo_user_hop
	},
	/* .h_tryas = */ {
		/* [HANDLE_TYPE_UNDEFINED]              = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_undefined_tryas,
		/* [HANDLE_TYPE_DATABLOCK]              = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_datablock_tryas,
		/* [HANDLE_TYPE_BLOCKDEVICE]            = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_blockdevice_tryas,
		/* [HANDLE_TYPE_DIRECTORYENTRY]         = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_directoryentry_tryas,
		/* [HANDLE_TYPE_FILE]                   = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_file_tryas,
		/* [HANDLE_TYPE_ONESHOT_DIRECTORY_FILE] = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_oneshot_directory_file_tryas,
		/* [HANDLE_TYPE_PATH]                   = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_path_tryas,
		/* [HANDLE_TYPE_FS]                     = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_fs_tryas,
		/* [HANDLE_TYPE_VM]                     = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_vm_tryas,
		/* [HANDLE_TYPE_TASK]                   = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_task_tryas,
		/* [HANDLE_TYPE_CLOCK]                  = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_clock_tryas,
		/* [HANDLE_TYPE_DRIVER]                 = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_driver_tryas,
		/* [HANDLE_TYPE_PIPE]                   = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_pipe_tryas,
		/* [HANDLE_TYPE_PIPE_READER]            = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_pipe_reader_tryas,
		/* [HANDLE_TYPE_PIPE_WRITER]            = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_pipe_writer_tryas,
		/* [HANDLE_TYPE_PIDNS]                  = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_pidns_tryas,
		/* [HANDLE_TYPE_DRIVER_STATE]           = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_driver_state_tryas,
		/* [HANDLE_TYPE_CHARACTERDEVICE]        = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_characterdevice_tryas,
		/* [HANDLE_TYPE_EVENTFD_FENCE]          = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_eventfd_fence_tryas,
		/* [HANDLE_TYPE_EVENTFD_SEMA]           = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_eventfd_sema_tryas,
		/* [HANDLE_TYPE_SIGNALFD]               = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_signalfd_tryas,
		/* [HANDLE_TYPE_DATAPART]               = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_datapart_tryas,
		/* [HANDLE_TYPE_FUTEX]                  = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_futex_tryas,
		/* [HANDLE_TYPE_FUTEXFD]                = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_futexfd_tryas,
		/* [HANDLE_TYPE_DRIVER_SECTION]         = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_driver_section_tryas,
		/* [HANDLE_TYPE_SOCKET]                 = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_socket_tryas,
		/* [HANDLE_TYPE_UAIO]                   = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_uaio_tryas,
		/* [HANDLE_TYPE_FIFO_USER]              = */ (REF void *(KCALL *)(void *__restrict, uintptr_half_t))&handle_fifo_user_tryas
	},
};



/* Weakly define operators for `HANDLE_TYPE_DATABLOCK' (`struct vm_datablock') */
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_datablock_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_BLOCKDEVICE' (`struct basic_block_device') */
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_refcnt, handle_undefined_refcnt);
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
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_blockdevice_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_DIRECTORYENTRY' (`struct directory_entry') */
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_refcnt, handle_undefined_refcnt);
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
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_directoryentry_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_FILE' (`struct file') */
DEFINE_INTERN_WEAK_ALIAS(handle_file_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_file_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_file_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_file_refcnt, handle_undefined_refcnt);
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
DEFINE_INTERN_WEAK_ALIAS(handle_file_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_file_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_file_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_ONESHOT_DIRECTORY_FILE' (`struct oneshot_directory_file') */
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_refcnt, handle_undefined_refcnt);
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
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_oneshot_directory_file_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_PATH' (`struct path') */
DEFINE_INTERN_WEAK_ALIAS(handle_path_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_path_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_path_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_path_refcnt, handle_undefined_refcnt);
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
DEFINE_INTERN_WEAK_ALIAS(handle_path_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_path_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_path_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_FS' (`struct fs') */
DEFINE_INTERN_WEAK_ALIAS(handle_fs_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_refcnt, handle_undefined_refcnt);
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
DEFINE_INTERN_WEAK_ALIAS(handle_fs_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_fs_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_VM' (`struct vm') */
DEFINE_INTERN_WEAK_ALIAS(handle_vm_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_vm_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_TASK' (`struct taskpid') */
DEFINE_INTERN_WEAK_ALIAS(handle_task_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_task_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_task_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_task_refcnt, handle_undefined_refcnt);
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
DEFINE_INTERN_WEAK_ALIAS(handle_task_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_task_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_task_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_CLOCK' (`struct realtime_clock_struct') */
DEFINE_INTERN_WEAK_ALIAS(handle_clock_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_clock_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_DRIVER' (`struct driver') */
DEFINE_INTERN_WEAK_ALIAS(handle_driver_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_PIPE' (`struct pipe') */
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_refcnt, handle_undefined_refcnt);
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
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_PIPE_READER' (`struct pipe_reader') */
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_refcnt, handle_undefined_refcnt);
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
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_reader_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_PIPE_WRITER' (`struct pipe_writer') */
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_refcnt, handle_undefined_refcnt);
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
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_pipe_writer_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_PIDNS' (`struct pidns') */
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_refcnt, handle_undefined_refcnt);
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
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_pidns_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_DRIVER_STATE' (`struct driver_state') */
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_state_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_CHARACTERDEVICE' (`struct character_device') */
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_refcnt, handle_undefined_refcnt);
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
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_characterdevice_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_EVENTFD_FENCE' (`struct eventfd') */
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_refcnt, handle_undefined_refcnt);
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
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_fence_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_EVENTFD_SEMA' (`struct eventfd') */
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_refcnt, handle_undefined_refcnt);
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
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_eventfd_sema_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_SIGNALFD' (`struct signalfd') */
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_refcnt, handle_undefined_refcnt);
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
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_signalfd_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_DATAPART' (`struct vm_datapart') */
DEFINE_INTERN_WEAK_ALIAS(handle_datapart_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_datapart_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_datapart_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_datapart_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_datapart_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_datapart_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_datapart_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_datapart_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_datapart_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_datapart_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_datapart_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_datapart_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_datapart_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_datapart_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_datapart_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_datapart_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_datapart_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_datapart_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_datapart_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_datapart_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_datapart_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_datapart_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_datapart_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_datapart_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_FUTEX' (`struct vm_futex') */
DEFINE_INTERN_WEAK_ALIAS(handle_futex_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_refcnt, handle_undefined_refcnt);
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
DEFINE_INTERN_WEAK_ALIAS(handle_futex_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_futex_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_FUTEXFD' (`struct vm_futexfd') */
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_refcnt, handle_undefined_refcnt);
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
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_futexfd_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_DRIVER_SECTION' (`struct driver_section') */
DEFINE_INTERN_WEAK_ALIAS(handle_driver_section_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_section_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_section_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_section_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_section_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_section_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_section_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_section_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_section_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_section_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_section_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_section_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_section_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_section_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_section_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_section_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_section_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_section_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_section_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_section_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_section_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_section_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_section_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_driver_section_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_SOCKET' (`struct socket') */
DEFINE_INTERN_WEAK_ALIAS(handle_socket_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_refcnt, handle_undefined_refcnt);
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
DEFINE_INTERN_WEAK_ALIAS(handle_socket_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_socket_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_UAIO' (`struct uaio_controller') */
DEFINE_INTERN_WEAK_ALIAS(handle_uaio_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_uaio_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_uaio_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_uaio_refcnt, handle_undefined_refcnt);
DEFINE_INTERN_WEAK_ALIAS(handle_uaio_read, handle_undefined_read);
DEFINE_INTERN_WEAK_ALIAS(handle_uaio_write, handle_undefined_write);
DEFINE_INTERN_WEAK_ALIAS(handle_uaio_pread, handle_undefined_pread);
DEFINE_INTERN_WEAK_ALIAS(handle_uaio_pwrite, handle_undefined_pwrite);
DEFINE_INTERN_WEAK_ALIAS(handle_uaio_readv, handle_undefined_readv);
DEFINE_INTERN_WEAK_ALIAS(handle_uaio_writev, handle_undefined_writev);
DEFINE_INTERN_WEAK_ALIAS(handle_uaio_preadv, handle_undefined_preadv);
DEFINE_INTERN_WEAK_ALIAS(handle_uaio_pwritev, handle_undefined_pwritev);
DEFINE_INTERN_WEAK_ALIAS(handle_uaio_readdir, handle_undefined_readdir);
DEFINE_INTERN_WEAK_ALIAS(handle_uaio_seek, handle_undefined_seek);
DEFINE_INTERN_WEAK_ALIAS(handle_uaio_ioctl, handle_undefined_ioctl);
DEFINE_INTERN_WEAK_ALIAS(handle_uaio_truncate, handle_undefined_truncate);
DEFINE_INTERN_WEAK_ALIAS(handle_uaio_mmap, handle_undefined_mmap);
DEFINE_INTERN_WEAK_ALIAS(handle_uaio_allocate, handle_undefined_allocate);
DEFINE_INTERN_WEAK_ALIAS(handle_uaio_sync, handle_undefined_sync);
DEFINE_INTERN_WEAK_ALIAS(handle_uaio_datasync, handle_undefined_datasync);
DEFINE_INTERN_WEAK_ALIAS(handle_uaio_stat, handle_undefined_stat);
DEFINE_INTERN_WEAK_ALIAS(handle_uaio_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_uaio_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_uaio_tryas, handle_undefined_tryas);

/* Weakly define operators for `HANDLE_TYPE_FIFO_USER' (`struct fifo_user') */
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_tryincref, handle_undefined_tryincref);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_incref, handle_undefined_incref);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_decref, handle_undefined_decref);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_refcnt, handle_undefined_refcnt);
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
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_poll, handle_undefined_poll);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_hop, handle_undefined_hop);
DEFINE_INTERN_WEAK_ALIAS(handle_fifo_user_tryas, handle_undefined_tryas);
//[[[end]]]



DECL_END

#endif /* !GUARD_KERNEL_SRC_USER_HANDLE_C */
