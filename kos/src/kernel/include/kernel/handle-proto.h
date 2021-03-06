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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_HANDLE_PROTO_H
#define GUARD_KERNEL_INCLUDE_KERNEL_HANDLE_PROTO_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <kos/io.h>

#if defined(__CC__) || defined(__DEEMON__)
DECL_BEGIN

#ifdef __DEEMON__
#define HANDLE_OPERATOR_PROTOTYPES                                                                            \
	{                                                                                                         \
		("refcnt", "NOBLOCK WUNUSED NONNULL((1))", "refcnt_t", "NOTHROW", "FCALL",                            \
		 { ("T const *__restrict", "self") },                                                                 \
		 "", "return 0;"),                                                                                    \
		("incref", "NOBLOCK NONNULL((1))", "void", "NOTHROW", "FCALL",                                        \
		 { ("T *__restrict", "self") },                                                                       \
		 "", ""),                                                                                             \
		("decref", "NOBLOCK NONNULL((1))", "void", "NOTHROW", "FCALL",                                        \
		 { ("REF T *__restrict", "self") },                                                                   \
		 "", ""),                                                                                             \
		("tryincref", "NOBLOCK WUNUSED NONNULL((1))", "__BOOL", "NOTHROW", "FCALL",                           \
		 { ("T *__restrict", "self") },                                                                       \
		 "", "return 1;"),                                                                                    \
		("weakgetref", "NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1))", "WEAK REF void *", "NOTHROW", "FCALL", \
		 { ("T *__restrict", "self") },                                                                       \
		 "", "return self;"),                                                                                 \
		("weaklckref", "NOBLOCK WUNUSED NONNULL((1))", "REF T *", "NOTHROW", "FCALL",                         \
		 { ("void *__restrict", "weakref_ptr") },                                                             \
		 "", "return NULL;"),                                                                                 \
		("weakdecref", "NOBLOCK NONNULL((1))", "void", "NOTHROW", "FCALL",                                    \
		 { ("WEAK REF void *__restrict", "weakref_ptr") },                                                    \
		 "", ""),                                                                                             \
		("read", "WUNUSED NONNULL((1))", "size_t", "", "KCALL",                                               \
		 { ("T *__restrict", "self"),                                                                         \
		   ("USER CHECKED void *", "dst"),                                                                    \
		   ("size_t", "num_bytes"),                                                                           \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ);"),                             \
		("write", "WUNUSED NONNULL((1))", "size_t", "", "KCALL",                                              \
		 { ("T *__restrict", "self"),                                                                         \
		   ("USER CHECKED void const *", "src"),                                                              \
		   ("size_t", "num_bytes"),                                                                           \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE);"),                            \
		("pread", "WUNUSED NONNULL((1))", "size_t", "", "KCALL",                                              \
		 { ("T *__restrict", "self"),                                                                         \
		   ("USER CHECKED void *", "dst"),                                                                    \
		   ("size_t", "num_bytes"),                                                                           \
		   ("pos_t", "addr"),                                                                                 \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ);"),                             \
		("pwrite", "WUNUSED NONNULL((1))", "size_t", "", "KCALL",                                             \
		 { ("T *__restrict", "self"),                                                                         \
		   ("USER CHECKED void const *", "src"),                                                              \
		   ("size_t", "num_bytes"),                                                                           \
		   ("pos_t", "addr"),                                                                                 \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE);"),                            \
		("readv", "WUNUSED NONNULL((1, 2))", "size_t", "", "KCALL",                                           \
		 { ("T *__restrict", "self"),                                                                         \
		   ("struct iov_buffer *__restrict", "dst"),                                                          \
		   ("size_t", "num_bytes"),                                                                           \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ);"),                             \
		("writev", "WUNUSED NONNULL((1, 2))", "size_t", "", "KCALL",                                          \
		 { ("T *__restrict", "self"),                                                                         \
		   ("struct iov_buffer *__restrict", "src"),                                                          \
		   ("size_t", "num_bytes"),                                                                           \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE);"),                            \
		("preadv", "WUNUSED NONNULL((1, 2))", "size_t", "", "KCALL",                                          \
		 { ("T *__restrict", "self"),                                                                         \
		   ("struct iov_buffer *__restrict", "dst"),                                                          \
		   ("size_t", "num_bytes"),                                                                           \
		   ("pos_t", "addr"),                                                                                 \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ);"),                             \
		("pwritev", "WUNUSED NONNULL((1, 2))", "size_t", "", "KCALL",                                         \
		 { ("T *__restrict", "self"),                                                                         \
		   ("struct iov_buffer *__restrict", "src"),                                                          \
		   ("size_t", "num_bytes"),                                                                           \
		   ("pos_t", "addr"),                                                                                 \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE);"),                            \
		("readdir", "WUNUSED NONNULL((1))", "size_t", "", "KCALL",                                            \
		 { ("T *__restrict", "self"),                                                                         \
		   ("USER CHECKED struct dirent *", "buf"),                                                           \
		   ("size_t", "bufsize"),                                                                             \
		   ("readdir_mode_t", "readdir_mode"),                                                                \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READDIR);"),                          \
		("seek", "NONNULL((1))", "pos_t", "", "KCALL",                                                        \
		 { ("T *__restrict", "self"),                                                                         \
		   ("off_t", "offset"),                                                                               \
		   ("unsigned int", "whence") },                                                                      \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_SEEK);"),                             \
		("ioctl", "NONNULL((1))", "syscall_slong_t", "", "KCALL",                                             \
		 { ("T *__restrict", "self"),                                                                         \
		   ("syscall_ulong_t", "cmd"),                                                                        \
		   ("USER UNCHECKED void *", "arg"),                                                                  \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND, cmd);"),        \
		("truncate", "NONNULL((1))", "void", "", "KCALL",                                                     \
		 { ("T *__restrict", "self"),                                                                         \
		   ("pos_t", "new_size") },                                                                           \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_TRUNC);"),                            \
		("mmap", "NONNULL((1, 2))", "void", "", "KCALL",                                                      \
		 { ("T *__restrict", "self"),                                                                         \
		   ("struct handle_mmap_info *__restrict", "info") },                                                 \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_MMAP);"),                             \
		("allocate", "NONNULL((1))", "pos_t", "", "KCALL",                                                    \
		 { ("T *__restrict", "self"),                                                                         \
		   ("fallocate_mode_t", "mode"),                                                                      \
		   ("pos_t", "start"),                                                                                \
		   ("pos_t", "length") },                                                                             \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_ALLOCATE);"),                         \
		("sync", "NONNULL((1))", "void", "", "KCALL",                                                         \
		 { ("T *__restrict", "self") },                                                                       \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_SYNC);"),                             \
		("datasync", "NONNULL((1))", "void", "", "KCALL",                                                     \
		 { ("T *__restrict", "self") },                                                                       \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_DATASYNC);"),                         \
		("stat", "NONNULL((1))", "void", "", "KCALL",                                                         \
		 { ("T *__restrict", "self"),                                                                         \
		   ("USER CHECKED struct stat *", "result") },                                                        \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_STAT);"),                             \
		("pollconnect", "NONNULL((1))", "void", "", "KCALL",                                                  \
		 { ("T *__restrict", "self"),                                                                         \
		   ("poll_mode_t", "what") },                                                                         \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_POLL);"),                             \
		("polltest", "WUNUSED NONNULL((1))", "poll_mode_t", "", "KCALL",                                      \
		 { ("T *__restrict", "self"),                                                                         \
		   ("poll_mode_t", "what") },                                                                         \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_POLL);"),                             \
		("hop", "NONNULL((1))", "syscall_slong_t", "", "KCALL",                                               \
		 { ("T *__restrict", "self"),                                                                         \
		   ("syscall_ulong_t", "cmd"),                                                                        \
		   ("USER UNCHECKED void *", "arg"),                                                                  \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND, cmd);"),          \
		("tryas", "NONNULL((1))", "REF void *", "", "KCALL",                                                  \
		 { ("T *__restrict", "self"),                                                                         \
		   ("uintptr_half_t", "wanted_type") },                                                               \
		 "THROWS(E_WOULDBLOCK)",                                                                              \
		 "return NULL;"),                                                                                     \
	}
#endif /* __DEEMON__ */

/* Prototypes for handle operators. */

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

print "#ifdef CONFIG_BUILDING_KERNEL_CORE";
print "#ifdef __CC__";
{
	local knownTypes = HashSet();
	for (local name, typ: handle_types) {
		if (!typ || typ in knownTypes)
			continue;
		if (!typ.startswith("struct"))
			continue;
		print typ,;
		print ";";
		knownTypes.insert(typ);
	}
}

print;
print;
print;
for (local h_name, h_typ: handle_types) {
	if (h_name in ["undefined"])
		continue;
	print "/" "* Handle operators for `HANDLE_TYPE_",;
	print h_name.upper(),;
	print "'",;
	if (h_typ) {
		print " (`",;
		print h_typ,;
		print "')",;
	}
	print " *" "/";
	for (local ARGS: ops) {
		print "INTDEF ",;
		if (attr) {
			print attr,;
			print " ",;
		}
		return_type = injectObjectType(return_type, h_typ);
		print return_type,;
		if (!return_type.endswith("*"))
			print " ",;
		print nothrow,;
		if (nothrow)
			print "(",;
		print cc, "handle_",;
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
		print ")",;
		if (throws) {
			print " ",;
			print throws,;
		}
		print ";";
	}
	print;
}
print "#endif /" "* __CC__ *" "/";
print "#endif /" "* CONFIG_BUILDING_KERNEL_CORE *" "/";

]]]*/
#ifdef CONFIG_BUILDING_KERNEL_CORE
#ifdef __CC__
struct file;
struct socket;
struct epoll_controller;
struct pipe;
struct pipe_reader;
struct pipe_writer;
struct fifo_user;
struct eventfd;
struct signalfd;
struct uaio_controller;
struct mfutex;
struct mfutexfd;
struct oneshot_directory_file;
struct mfile;
struct basic_block_device;
struct directory_entry;
struct path;
struct fs;
struct mman;
struct taskpid;
struct module;
struct pidns;
struct driver_loadlist;
struct character_device;
struct mpart;
struct module_section;



/* Handle operators for `HANDLE_TYPE_FILE' (`struct file') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_file_refcnt)(struct file const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_file_incref)(struct file *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_file_decref)(REF struct file *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_file_tryincref)(struct file *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_file_weakgetref)(struct file *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct file *NOTHROW(FCALL handle_file_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_file_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_file_read(struct file *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_file_write(struct file *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_file_pread(struct file *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_file_pwrite(struct file *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_file_readv(struct file *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_file_writev(struct file *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_file_preadv(struct file *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_file_pwritev(struct file *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_file_readdir(struct file *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_file_seek(struct file *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_file_ioctl(struct file *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_file_truncate(struct file *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_file_mmap(struct file *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_file_allocate(struct file *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_file_sync(struct file *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_file_datasync(struct file *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_file_stat(struct file *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_file_pollconnect(struct file *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_file_polltest(struct file *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_file_hop(struct file *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_file_tryas(struct file *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_SOCKET' (`struct socket') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_socket_refcnt)(struct socket const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_socket_incref)(struct socket *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_socket_decref)(REF struct socket *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_socket_tryincref)(struct socket *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_socket_weakgetref)(struct socket *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct socket *NOTHROW(FCALL handle_socket_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_socket_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_socket_read(struct socket *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_socket_write(struct socket *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_socket_pread(struct socket *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_socket_pwrite(struct socket *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_socket_readv(struct socket *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_socket_writev(struct socket *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_socket_preadv(struct socket *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_socket_pwritev(struct socket *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_socket_readdir(struct socket *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_socket_seek(struct socket *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_socket_ioctl(struct socket *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_socket_truncate(struct socket *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_socket_mmap(struct socket *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_socket_allocate(struct socket *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_socket_sync(struct socket *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_socket_datasync(struct socket *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_socket_stat(struct socket *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_socket_pollconnect(struct socket *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_socket_polltest(struct socket *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_socket_hop(struct socket *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_socket_tryas(struct socket *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_EPOLL' (`struct epoll_controller') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_epoll_refcnt)(struct epoll_controller const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_epoll_incref)(struct epoll_controller *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_epoll_decref)(REF struct epoll_controller *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_epoll_tryincref)(struct epoll_controller *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_epoll_weakgetref)(struct epoll_controller *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct epoll_controller *NOTHROW(FCALL handle_epoll_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_epoll_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_epoll_read(struct epoll_controller *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_epoll_write(struct epoll_controller *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_epoll_pread(struct epoll_controller *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_epoll_pwrite(struct epoll_controller *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_epoll_readv(struct epoll_controller *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_epoll_writev(struct epoll_controller *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_epoll_preadv(struct epoll_controller *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_epoll_pwritev(struct epoll_controller *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_epoll_readdir(struct epoll_controller *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_epoll_seek(struct epoll_controller *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_epoll_ioctl(struct epoll_controller *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_epoll_truncate(struct epoll_controller *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_epoll_mmap(struct epoll_controller *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_epoll_allocate(struct epoll_controller *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_epoll_sync(struct epoll_controller *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_epoll_datasync(struct epoll_controller *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_epoll_stat(struct epoll_controller *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_epoll_pollconnect(struct epoll_controller *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_epoll_polltest(struct epoll_controller *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_epoll_hop(struct epoll_controller *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_epoll_tryas(struct epoll_controller *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_PIPE' (`struct pipe') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_pipe_refcnt)(struct pipe const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_incref)(struct pipe *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_decref)(REF struct pipe *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_pipe_tryincref)(struct pipe *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_pipe_weakgetref)(struct pipe *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct pipe *NOTHROW(FCALL handle_pipe_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_read(struct pipe *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_write(struct pipe *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_pread(struct pipe *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_pwrite(struct pipe *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_readv(struct pipe *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_writev(struct pipe *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_preadv(struct pipe *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_pwritev(struct pipe *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_readdir(struct pipe *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_pipe_seek(struct pipe *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_pipe_ioctl(struct pipe *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_truncate(struct pipe *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_pipe_mmap(struct pipe *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_pipe_allocate(struct pipe *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_sync(struct pipe *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_datasync(struct pipe *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_stat(struct pipe *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_pollconnect(struct pipe *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_pipe_polltest(struct pipe *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_pipe_hop(struct pipe *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_pipe_tryas(struct pipe *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_PIPE_READER' (`struct pipe_reader') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_pipe_reader_refcnt)(struct pipe_reader const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_reader_incref)(struct pipe_reader *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_reader_decref)(REF struct pipe_reader *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_pipe_reader_tryincref)(struct pipe_reader *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_pipe_reader_weakgetref)(struct pipe_reader *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct pipe_reader *NOTHROW(FCALL handle_pipe_reader_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_reader_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_reader_read(struct pipe_reader *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_reader_write(struct pipe_reader *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_reader_pread(struct pipe_reader *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_reader_pwrite(struct pipe_reader *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_reader_readv(struct pipe_reader *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_reader_writev(struct pipe_reader *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_reader_preadv(struct pipe_reader *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_reader_pwritev(struct pipe_reader *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_reader_readdir(struct pipe_reader *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_pipe_reader_seek(struct pipe_reader *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_pipe_reader_ioctl(struct pipe_reader *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_reader_truncate(struct pipe_reader *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_pipe_reader_mmap(struct pipe_reader *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_pipe_reader_allocate(struct pipe_reader *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_reader_sync(struct pipe_reader *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_reader_datasync(struct pipe_reader *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_reader_stat(struct pipe_reader *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_reader_pollconnect(struct pipe_reader *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_pipe_reader_polltest(struct pipe_reader *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_pipe_reader_hop(struct pipe_reader *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_pipe_reader_tryas(struct pipe_reader *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_PIPE_WRITER' (`struct pipe_writer') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_pipe_writer_refcnt)(struct pipe_writer const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_writer_incref)(struct pipe_writer *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_writer_decref)(REF struct pipe_writer *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_pipe_writer_tryincref)(struct pipe_writer *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_pipe_writer_weakgetref)(struct pipe_writer *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct pipe_writer *NOTHROW(FCALL handle_pipe_writer_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_writer_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_writer_read(struct pipe_writer *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_writer_write(struct pipe_writer *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_writer_pread(struct pipe_writer *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_writer_pwrite(struct pipe_writer *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_writer_readv(struct pipe_writer *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_writer_writev(struct pipe_writer *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_writer_preadv(struct pipe_writer *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_writer_pwritev(struct pipe_writer *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_writer_readdir(struct pipe_writer *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_pipe_writer_seek(struct pipe_writer *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_pipe_writer_ioctl(struct pipe_writer *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_writer_truncate(struct pipe_writer *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_pipe_writer_mmap(struct pipe_writer *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_pipe_writer_allocate(struct pipe_writer *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_writer_sync(struct pipe_writer *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_writer_datasync(struct pipe_writer *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_writer_stat(struct pipe_writer *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_writer_pollconnect(struct pipe_writer *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_pipe_writer_polltest(struct pipe_writer *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_pipe_writer_hop(struct pipe_writer *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_pipe_writer_tryas(struct pipe_writer *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_FIFO_USER' (`struct fifo_user') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_fifo_user_refcnt)(struct fifo_user const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_fifo_user_incref)(struct fifo_user *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_fifo_user_decref)(REF struct fifo_user *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_fifo_user_tryincref)(struct fifo_user *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_fifo_user_weakgetref)(struct fifo_user *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct fifo_user *NOTHROW(FCALL handle_fifo_user_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_fifo_user_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_fifo_user_read(struct fifo_user *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_fifo_user_write(struct fifo_user *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_fifo_user_pread(struct fifo_user *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_fifo_user_pwrite(struct fifo_user *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_fifo_user_readv(struct fifo_user *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_fifo_user_writev(struct fifo_user *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_fifo_user_preadv(struct fifo_user *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_fifo_user_pwritev(struct fifo_user *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_fifo_user_readdir(struct fifo_user *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_fifo_user_seek(struct fifo_user *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_fifo_user_ioctl(struct fifo_user *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_fifo_user_truncate(struct fifo_user *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_fifo_user_mmap(struct fifo_user *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_fifo_user_allocate(struct fifo_user *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_fifo_user_sync(struct fifo_user *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_fifo_user_datasync(struct fifo_user *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_fifo_user_stat(struct fifo_user *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_fifo_user_pollconnect(struct fifo_user *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_fifo_user_polltest(struct fifo_user *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_fifo_user_hop(struct fifo_user *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_fifo_user_tryas(struct fifo_user *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_EVENTFD_FENCE' (`struct eventfd') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_eventfd_fence_refcnt)(struct eventfd const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_eventfd_fence_incref)(struct eventfd *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_eventfd_fence_decref)(REF struct eventfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_eventfd_fence_tryincref)(struct eventfd *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_eventfd_fence_weakgetref)(struct eventfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct eventfd *NOTHROW(FCALL handle_eventfd_fence_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_eventfd_fence_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_fence_read(struct eventfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_fence_write(struct eventfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_fence_pread(struct eventfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_fence_pwrite(struct eventfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_fence_readv(struct eventfd *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_fence_writev(struct eventfd *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_fence_preadv(struct eventfd *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_fence_pwritev(struct eventfd *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_fence_readdir(struct eventfd *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_eventfd_fence_seek(struct eventfd *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_eventfd_fence_ioctl(struct eventfd *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_fence_truncate(struct eventfd *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_eventfd_fence_mmap(struct eventfd *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_eventfd_fence_allocate(struct eventfd *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_fence_sync(struct eventfd *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_fence_datasync(struct eventfd *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_fence_stat(struct eventfd *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_fence_pollconnect(struct eventfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_eventfd_fence_polltest(struct eventfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_eventfd_fence_hop(struct eventfd *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_eventfd_fence_tryas(struct eventfd *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_EVENTFD_SEMA' (`struct eventfd') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_eventfd_sema_refcnt)(struct eventfd const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_eventfd_sema_incref)(struct eventfd *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_eventfd_sema_decref)(REF struct eventfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_eventfd_sema_tryincref)(struct eventfd *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_eventfd_sema_weakgetref)(struct eventfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct eventfd *NOTHROW(FCALL handle_eventfd_sema_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_eventfd_sema_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_sema_read(struct eventfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_sema_write(struct eventfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_sema_pread(struct eventfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_sema_pwrite(struct eventfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_sema_readv(struct eventfd *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_sema_writev(struct eventfd *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_sema_preadv(struct eventfd *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_sema_pwritev(struct eventfd *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_sema_readdir(struct eventfd *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_eventfd_sema_seek(struct eventfd *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_eventfd_sema_ioctl(struct eventfd *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_sema_truncate(struct eventfd *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_eventfd_sema_mmap(struct eventfd *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_eventfd_sema_allocate(struct eventfd *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_sema_sync(struct eventfd *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_sema_datasync(struct eventfd *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_sema_stat(struct eventfd *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_sema_pollconnect(struct eventfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_eventfd_sema_polltest(struct eventfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_eventfd_sema_hop(struct eventfd *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_eventfd_sema_tryas(struct eventfd *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_SIGNALFD' (`struct signalfd') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_signalfd_refcnt)(struct signalfd const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_signalfd_incref)(struct signalfd *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_signalfd_decref)(REF struct signalfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_signalfd_tryincref)(struct signalfd *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_signalfd_weakgetref)(struct signalfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct signalfd *NOTHROW(FCALL handle_signalfd_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_signalfd_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_signalfd_read(struct signalfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_signalfd_write(struct signalfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_signalfd_pread(struct signalfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_signalfd_pwrite(struct signalfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_signalfd_readv(struct signalfd *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_signalfd_writev(struct signalfd *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_signalfd_preadv(struct signalfd *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_signalfd_pwritev(struct signalfd *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_signalfd_readdir(struct signalfd *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_signalfd_seek(struct signalfd *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_signalfd_ioctl(struct signalfd *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_signalfd_truncate(struct signalfd *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_signalfd_mmap(struct signalfd *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_signalfd_allocate(struct signalfd *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_signalfd_sync(struct signalfd *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_signalfd_datasync(struct signalfd *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_signalfd_stat(struct signalfd *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_signalfd_pollconnect(struct signalfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_signalfd_polltest(struct signalfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_signalfd_hop(struct signalfd *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_signalfd_tryas(struct signalfd *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_UAIO' (`struct uaio_controller') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_uaio_refcnt)(struct uaio_controller const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_uaio_incref)(struct uaio_controller *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_uaio_decref)(REF struct uaio_controller *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_uaio_tryincref)(struct uaio_controller *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_uaio_weakgetref)(struct uaio_controller *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct uaio_controller *NOTHROW(FCALL handle_uaio_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_uaio_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_uaio_read(struct uaio_controller *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_uaio_write(struct uaio_controller *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_uaio_pread(struct uaio_controller *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_uaio_pwrite(struct uaio_controller *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_uaio_readv(struct uaio_controller *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_uaio_writev(struct uaio_controller *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_uaio_preadv(struct uaio_controller *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_uaio_pwritev(struct uaio_controller *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_uaio_readdir(struct uaio_controller *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_uaio_seek(struct uaio_controller *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_uaio_ioctl(struct uaio_controller *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_uaio_truncate(struct uaio_controller *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_uaio_mmap(struct uaio_controller *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_uaio_allocate(struct uaio_controller *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_uaio_sync(struct uaio_controller *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_uaio_datasync(struct uaio_controller *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_uaio_stat(struct uaio_controller *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_uaio_pollconnect(struct uaio_controller *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_uaio_polltest(struct uaio_controller *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_uaio_hop(struct uaio_controller *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_uaio_tryas(struct uaio_controller *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_FUTEX' (`struct mfutex') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_futex_refcnt)(struct mfutex const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_futex_incref)(struct mfutex *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_futex_decref)(REF struct mfutex *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_futex_tryincref)(struct mfutex *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_futex_weakgetref)(struct mfutex *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct mfutex *NOTHROW(FCALL handle_futex_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_futex_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futex_read(struct mfutex *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futex_write(struct mfutex *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futex_pread(struct mfutex *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futex_pwrite(struct mfutex *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_futex_readv(struct mfutex *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_futex_writev(struct mfutex *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_futex_preadv(struct mfutex *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_futex_pwritev(struct mfutex *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futex_readdir(struct mfutex *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_futex_seek(struct mfutex *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_futex_ioctl(struct mfutex *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futex_truncate(struct mfutex *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_futex_mmap(struct mfutex *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_futex_allocate(struct mfutex *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futex_sync(struct mfutex *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futex_datasync(struct mfutex *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futex_stat(struct mfutex *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futex_pollconnect(struct mfutex *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_futex_polltest(struct mfutex *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_futex_hop(struct mfutex *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_futex_tryas(struct mfutex *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_FUTEXFD' (`struct mfutexfd') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_futexfd_refcnt)(struct mfutexfd const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_futexfd_incref)(struct mfutexfd *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_futexfd_decref)(REF struct mfutexfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_futexfd_tryincref)(struct mfutexfd *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_futexfd_weakgetref)(struct mfutexfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct mfutexfd *NOTHROW(FCALL handle_futexfd_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_futexfd_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futexfd_read(struct mfutexfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futexfd_write(struct mfutexfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futexfd_pread(struct mfutexfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futexfd_pwrite(struct mfutexfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_futexfd_readv(struct mfutexfd *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_futexfd_writev(struct mfutexfd *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_futexfd_preadv(struct mfutexfd *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_futexfd_pwritev(struct mfutexfd *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futexfd_readdir(struct mfutexfd *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_futexfd_seek(struct mfutexfd *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_futexfd_ioctl(struct mfutexfd *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futexfd_truncate(struct mfutexfd *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_futexfd_mmap(struct mfutexfd *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_futexfd_allocate(struct mfutexfd *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futexfd_sync(struct mfutexfd *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futexfd_datasync(struct mfutexfd *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futexfd_stat(struct mfutexfd *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futexfd_pollconnect(struct mfutexfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_futexfd_polltest(struct mfutexfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_futexfd_hop(struct mfutexfd *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_futexfd_tryas(struct mfutexfd *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_ONESHOT_DIRECTORY_FILE' (`struct oneshot_directory_file') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_oneshot_directory_file_refcnt)(struct oneshot_directory_file const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_oneshot_directory_file_incref)(struct oneshot_directory_file *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_oneshot_directory_file_decref)(REF struct oneshot_directory_file *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_oneshot_directory_file_tryincref)(struct oneshot_directory_file *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_oneshot_directory_file_weakgetref)(struct oneshot_directory_file *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct oneshot_directory_file *NOTHROW(FCALL handle_oneshot_directory_file_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_oneshot_directory_file_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_oneshot_directory_file_read(struct oneshot_directory_file *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_oneshot_directory_file_write(struct oneshot_directory_file *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_oneshot_directory_file_pread(struct oneshot_directory_file *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_oneshot_directory_file_pwrite(struct oneshot_directory_file *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_oneshot_directory_file_readv(struct oneshot_directory_file *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_oneshot_directory_file_writev(struct oneshot_directory_file *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_oneshot_directory_file_preadv(struct oneshot_directory_file *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_oneshot_directory_file_pwritev(struct oneshot_directory_file *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_oneshot_directory_file_readdir(struct oneshot_directory_file *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_oneshot_directory_file_seek(struct oneshot_directory_file *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_oneshot_directory_file_ioctl(struct oneshot_directory_file *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_oneshot_directory_file_truncate(struct oneshot_directory_file *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_oneshot_directory_file_mmap(struct oneshot_directory_file *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_oneshot_directory_file_allocate(struct oneshot_directory_file *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_oneshot_directory_file_sync(struct oneshot_directory_file *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_oneshot_directory_file_datasync(struct oneshot_directory_file *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_oneshot_directory_file_stat(struct oneshot_directory_file *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_oneshot_directory_file_pollconnect(struct oneshot_directory_file *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_oneshot_directory_file_polltest(struct oneshot_directory_file *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_oneshot_directory_file_hop(struct oneshot_directory_file *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_oneshot_directory_file_tryas(struct oneshot_directory_file *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_MFILE' (`struct mfile') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_mfile_refcnt)(struct mfile const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_mfile_incref)(struct mfile *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_mfile_decref)(REF struct mfile *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_mfile_tryincref)(struct mfile *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_mfile_weakgetref)(struct mfile *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct mfile *NOTHROW(FCALL handle_mfile_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_mfile_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_mfile_read(struct mfile *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_mfile_write(struct mfile *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_mfile_pread(struct mfile *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_mfile_pwrite(struct mfile *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_mfile_readv(struct mfile *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_mfile_writev(struct mfile *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_mfile_preadv(struct mfile *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_mfile_pwritev(struct mfile *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_mfile_readdir(struct mfile *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_mfile_seek(struct mfile *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_mfile_ioctl(struct mfile *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_mfile_truncate(struct mfile *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_mfile_mmap(struct mfile *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_mfile_allocate(struct mfile *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_mfile_sync(struct mfile *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_mfile_datasync(struct mfile *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_mfile_stat(struct mfile *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_mfile_pollconnect(struct mfile *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_mfile_polltest(struct mfile *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_mfile_hop(struct mfile *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_mfile_tryas(struct mfile *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_BLOCKDEVICE' (`struct basic_block_device') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_blockdevice_refcnt)(struct basic_block_device const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_blockdevice_incref)(struct basic_block_device *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_blockdevice_decref)(REF struct basic_block_device *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_blockdevice_tryincref)(struct basic_block_device *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_blockdevice_weakgetref)(struct basic_block_device *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct basic_block_device *NOTHROW(FCALL handle_blockdevice_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_blockdevice_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_blockdevice_read(struct basic_block_device *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_blockdevice_write(struct basic_block_device *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_blockdevice_pread(struct basic_block_device *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_blockdevice_pwrite(struct basic_block_device *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_blockdevice_readv(struct basic_block_device *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_blockdevice_writev(struct basic_block_device *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_blockdevice_preadv(struct basic_block_device *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_blockdevice_pwritev(struct basic_block_device *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_blockdevice_readdir(struct basic_block_device *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_blockdevice_seek(struct basic_block_device *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_blockdevice_ioctl(struct basic_block_device *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_blockdevice_truncate(struct basic_block_device *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_blockdevice_mmap(struct basic_block_device *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_blockdevice_allocate(struct basic_block_device *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_blockdevice_sync(struct basic_block_device *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_blockdevice_datasync(struct basic_block_device *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_blockdevice_stat(struct basic_block_device *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_blockdevice_pollconnect(struct basic_block_device *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_blockdevice_polltest(struct basic_block_device *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_blockdevice_hop(struct basic_block_device *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_blockdevice_tryas(struct basic_block_device *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_DIRECTORYENTRY' (`struct directory_entry') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_directoryentry_refcnt)(struct directory_entry const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_directoryentry_incref)(struct directory_entry *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_directoryentry_decref)(REF struct directory_entry *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_directoryentry_tryincref)(struct directory_entry *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_directoryentry_weakgetref)(struct directory_entry *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct directory_entry *NOTHROW(FCALL handle_directoryentry_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_directoryentry_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_directoryentry_read(struct directory_entry *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_directoryentry_write(struct directory_entry *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_directoryentry_pread(struct directory_entry *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_directoryentry_pwrite(struct directory_entry *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_directoryentry_readv(struct directory_entry *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_directoryentry_writev(struct directory_entry *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_directoryentry_preadv(struct directory_entry *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_directoryentry_pwritev(struct directory_entry *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_directoryentry_readdir(struct directory_entry *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_directoryentry_seek(struct directory_entry *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_directoryentry_ioctl(struct directory_entry *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_directoryentry_truncate(struct directory_entry *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_directoryentry_mmap(struct directory_entry *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_directoryentry_allocate(struct directory_entry *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_directoryentry_sync(struct directory_entry *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_directoryentry_datasync(struct directory_entry *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_directoryentry_stat(struct directory_entry *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_directoryentry_pollconnect(struct directory_entry *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_directoryentry_polltest(struct directory_entry *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_directoryentry_hop(struct directory_entry *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_directoryentry_tryas(struct directory_entry *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_PATH' (`struct path') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_path_refcnt)(struct path const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_path_incref)(struct path *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_path_decref)(REF struct path *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_path_tryincref)(struct path *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_path_weakgetref)(struct path *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct path *NOTHROW(FCALL handle_path_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_path_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_path_read(struct path *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_path_write(struct path *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_path_pread(struct path *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_path_pwrite(struct path *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_path_readv(struct path *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_path_writev(struct path *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_path_preadv(struct path *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_path_pwritev(struct path *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_path_readdir(struct path *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_path_seek(struct path *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_path_ioctl(struct path *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_path_truncate(struct path *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_path_mmap(struct path *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_path_allocate(struct path *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_path_sync(struct path *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_path_datasync(struct path *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_path_stat(struct path *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_path_pollconnect(struct path *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_path_polltest(struct path *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_path_hop(struct path *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_path_tryas(struct path *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_FS' (`struct fs') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_fs_refcnt)(struct fs const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_fs_incref)(struct fs *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_fs_decref)(REF struct fs *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_fs_tryincref)(struct fs *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_fs_weakgetref)(struct fs *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct fs *NOTHROW(FCALL handle_fs_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_fs_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_fs_read(struct fs *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_fs_write(struct fs *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_fs_pread(struct fs *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_fs_pwrite(struct fs *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_fs_readv(struct fs *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_fs_writev(struct fs *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_fs_preadv(struct fs *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_fs_pwritev(struct fs *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_fs_readdir(struct fs *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_fs_seek(struct fs *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_fs_ioctl(struct fs *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_fs_truncate(struct fs *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_fs_mmap(struct fs *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_fs_allocate(struct fs *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_fs_sync(struct fs *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_fs_datasync(struct fs *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_fs_stat(struct fs *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_fs_pollconnect(struct fs *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_fs_polltest(struct fs *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_fs_hop(struct fs *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_fs_tryas(struct fs *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_MMAN' (`struct mman') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_mman_refcnt)(struct mman const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_mman_incref)(struct mman *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_mman_decref)(REF struct mman *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_mman_tryincref)(struct mman *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_mman_weakgetref)(struct mman *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct mman *NOTHROW(FCALL handle_mman_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_mman_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_mman_read(struct mman *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_mman_write(struct mman *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_mman_pread(struct mman *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_mman_pwrite(struct mman *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_mman_readv(struct mman *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_mman_writev(struct mman *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_mman_preadv(struct mman *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_mman_pwritev(struct mman *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_mman_readdir(struct mman *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_mman_seek(struct mman *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_mman_ioctl(struct mman *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_mman_truncate(struct mman *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_mman_mmap(struct mman *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_mman_allocate(struct mman *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_mman_sync(struct mman *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_mman_datasync(struct mman *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_mman_stat(struct mman *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_mman_pollconnect(struct mman *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_mman_polltest(struct mman *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_mman_hop(struct mman *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_mman_tryas(struct mman *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_TASK' (`struct taskpid') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_task_refcnt)(struct taskpid const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_task_incref)(struct taskpid *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_task_decref)(REF struct taskpid *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_task_tryincref)(struct taskpid *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_task_weakgetref)(struct taskpid *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct taskpid *NOTHROW(FCALL handle_task_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_task_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_task_read(struct taskpid *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_task_write(struct taskpid *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_task_pread(struct taskpid *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_task_pwrite(struct taskpid *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_task_readv(struct taskpid *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_task_writev(struct taskpid *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_task_preadv(struct taskpid *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_task_pwritev(struct taskpid *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_task_readdir(struct taskpid *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_task_seek(struct taskpid *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_task_ioctl(struct taskpid *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_task_truncate(struct taskpid *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_task_mmap(struct taskpid *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_task_allocate(struct taskpid *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_task_sync(struct taskpid *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_task_datasync(struct taskpid *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_task_stat(struct taskpid *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_task_pollconnect(struct taskpid *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_task_polltest(struct taskpid *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_task_hop(struct taskpid *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_task_tryas(struct taskpid *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_MODULE' (`struct module') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_module_refcnt)(struct module const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_module_incref)(struct module *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_module_decref)(REF struct module *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_module_tryincref)(struct module *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_module_weakgetref)(struct module *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct module *NOTHROW(FCALL handle_module_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_module_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_module_read(struct module *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_module_write(struct module *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_module_pread(struct module *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_module_pwrite(struct module *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_module_readv(struct module *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_module_writev(struct module *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_module_preadv(struct module *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_module_pwritev(struct module *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_module_readdir(struct module *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_module_seek(struct module *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_module_ioctl(struct module *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_module_truncate(struct module *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_module_mmap(struct module *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_module_allocate(struct module *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_module_sync(struct module *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_module_datasync(struct module *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_module_stat(struct module *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_module_pollconnect(struct module *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_module_polltest(struct module *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_module_hop(struct module *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_module_tryas(struct module *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_PIDNS' (`struct pidns') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_pidns_refcnt)(struct pidns const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pidns_incref)(struct pidns *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pidns_decref)(REF struct pidns *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_pidns_tryincref)(struct pidns *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_pidns_weakgetref)(struct pidns *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct pidns *NOTHROW(FCALL handle_pidns_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pidns_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pidns_read(struct pidns *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pidns_write(struct pidns *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pidns_pread(struct pidns *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pidns_pwrite(struct pidns *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pidns_readv(struct pidns *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pidns_writev(struct pidns *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pidns_preadv(struct pidns *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pidns_pwritev(struct pidns *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pidns_readdir(struct pidns *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_pidns_seek(struct pidns *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_pidns_ioctl(struct pidns *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pidns_truncate(struct pidns *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_pidns_mmap(struct pidns *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_pidns_allocate(struct pidns *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pidns_sync(struct pidns *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pidns_datasync(struct pidns *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pidns_stat(struct pidns *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pidns_pollconnect(struct pidns *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_pidns_polltest(struct pidns *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_pidns_hop(struct pidns *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_pidns_tryas(struct pidns *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_DRIVER_LOADLIST' (`struct driver_loadlist') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_driver_loadlist_refcnt)(struct driver_loadlist const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_driver_loadlist_incref)(struct driver_loadlist *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_driver_loadlist_decref)(REF struct driver_loadlist *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_driver_loadlist_tryincref)(struct driver_loadlist *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_driver_loadlist_weakgetref)(struct driver_loadlist *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct driver_loadlist *NOTHROW(FCALL handle_driver_loadlist_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_driver_loadlist_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_loadlist_read(struct driver_loadlist *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_loadlist_write(struct driver_loadlist *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_loadlist_pread(struct driver_loadlist *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_loadlist_pwrite(struct driver_loadlist *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_loadlist_readv(struct driver_loadlist *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_loadlist_writev(struct driver_loadlist *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_loadlist_preadv(struct driver_loadlist *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_loadlist_pwritev(struct driver_loadlist *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_loadlist_readdir(struct driver_loadlist *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_driver_loadlist_seek(struct driver_loadlist *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_driver_loadlist_ioctl(struct driver_loadlist *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_loadlist_truncate(struct driver_loadlist *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_driver_loadlist_mmap(struct driver_loadlist *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_driver_loadlist_allocate(struct driver_loadlist *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_loadlist_sync(struct driver_loadlist *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_loadlist_datasync(struct driver_loadlist *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_loadlist_stat(struct driver_loadlist *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_loadlist_pollconnect(struct driver_loadlist *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_driver_loadlist_polltest(struct driver_loadlist *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_driver_loadlist_hop(struct driver_loadlist *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_driver_loadlist_tryas(struct driver_loadlist *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_CHARACTERDEVICE' (`struct character_device') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_characterdevice_refcnt)(struct character_device const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_characterdevice_incref)(struct character_device *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_characterdevice_decref)(REF struct character_device *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_characterdevice_tryincref)(struct character_device *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_characterdevice_weakgetref)(struct character_device *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct character_device *NOTHROW(FCALL handle_characterdevice_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_characterdevice_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_characterdevice_read(struct character_device *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_characterdevice_write(struct character_device *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_characterdevice_pread(struct character_device *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_characterdevice_pwrite(struct character_device *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_characterdevice_readv(struct character_device *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_characterdevice_writev(struct character_device *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_characterdevice_preadv(struct character_device *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_characterdevice_pwritev(struct character_device *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_characterdevice_readdir(struct character_device *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_characterdevice_seek(struct character_device *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_characterdevice_ioctl(struct character_device *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_characterdevice_truncate(struct character_device *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_characterdevice_mmap(struct character_device *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_characterdevice_allocate(struct character_device *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_characterdevice_sync(struct character_device *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_characterdevice_datasync(struct character_device *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_characterdevice_stat(struct character_device *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_characterdevice_pollconnect(struct character_device *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_characterdevice_polltest(struct character_device *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_characterdevice_hop(struct character_device *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_characterdevice_tryas(struct character_device *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_MPART' (`struct mpart') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_mpart_refcnt)(struct mpart const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_mpart_incref)(struct mpart *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_mpart_decref)(REF struct mpart *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_mpart_tryincref)(struct mpart *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_mpart_weakgetref)(struct mpart *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct mpart *NOTHROW(FCALL handle_mpart_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_mpart_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_mpart_read(struct mpart *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_mpart_write(struct mpart *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_mpart_pread(struct mpart *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_mpart_pwrite(struct mpart *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_mpart_readv(struct mpart *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_mpart_writev(struct mpart *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_mpart_preadv(struct mpart *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_mpart_pwritev(struct mpart *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_mpart_readdir(struct mpart *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_mpart_seek(struct mpart *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_mpart_ioctl(struct mpart *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_mpart_truncate(struct mpart *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_mpart_mmap(struct mpart *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_mpart_allocate(struct mpart *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_mpart_sync(struct mpart *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_mpart_datasync(struct mpart *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_mpart_stat(struct mpart *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_mpart_pollconnect(struct mpart *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_mpart_polltest(struct mpart *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_mpart_hop(struct mpart *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_mpart_tryas(struct mpart *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

/* Handle operators for `HANDLE_TYPE_MODULE_SECTION' (`struct module_section') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_module_section_refcnt)(struct module_section const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_module_section_incref)(struct module_section *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_module_section_decref)(REF struct module_section *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_module_section_tryincref)(struct module_section *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_module_section_weakgetref)(struct module_section *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct module_section *NOTHROW(FCALL handle_module_section_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_module_section_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_module_section_read(struct module_section *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_module_section_write(struct module_section *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_module_section_pread(struct module_section *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_module_section_pwrite(struct module_section *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_module_section_readv(struct module_section *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_module_section_writev(struct module_section *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_module_section_preadv(struct module_section *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_module_section_pwritev(struct module_section *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_module_section_readdir(struct module_section *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_module_section_seek(struct module_section *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_module_section_ioctl(struct module_section *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_module_section_truncate(struct module_section *__restrict self, pos_t new_size) THROWS(...);
INTDEF NONNULL((1, 2)) void KCALL handle_module_section_mmap(struct module_section *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_module_section_allocate(struct module_section *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_module_section_sync(struct module_section *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_module_section_datasync(struct module_section *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_module_section_stat(struct module_section *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_module_section_pollconnect(struct module_section *__restrict self, poll_mode_t what) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_module_section_polltest(struct module_section *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_module_section_hop(struct module_section *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) REF void *KCALL handle_module_section_tryas(struct module_section *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);

#endif /* __CC__ */
#endif /* CONFIG_BUILDING_KERNEL_CORE */
//[[[end]]]




#ifdef CONFIG_BUILDING_KERNEL_CORE
#ifdef __CC__

/* `name' must be the lower-case form of the `*' in one of the `HANDLE_TYPE_*' macros.
 * `T' must be the actual object type (one implementing the refcnt protocol or deriving from another that does) */
#define DEFINE_HANDLE_REFCNT_FUNCTIONS(name, T)                                  \
	INTERN NOBLOCK WUNUSED NONNULL((1)) refcnt_t                                 \
	NOTHROW(FCALL handle_##name##_refcnt)(T const *__restrict self) {            \
		return getrefcnt(self);                                                  \
	}                                                                            \
	INTERN NOBLOCK NONNULL((1)) WEAK REF void *                                  \
	NOTHROW(FCALL handle_##name##_weakgetref)(T *__restrict self) {              \
		return incref(self);                                                     \
	}                                                                            \
	INTERN NOBLOCK NONNULL((1)) void                                             \
	NOTHROW(FCALL handle_##name##_decref)(REF T *__restrict self) {              \
		decref(self);                                                            \
	}                                                                            \
	INTERN NOBLOCK NONNULL((1)) __BOOL                                           \
	NOTHROW(FCALL handle_##name##_tryincref)(T *__restrict self) {               \
		return tryincref(self);                                                  \
	}                                                                            \
	DEFINE_INTERN_ALIAS(handle_##name##_incref, handle_##name##_weakgetref);     \
	DEFINE_INTERN_ALIAS(handle_##name##_weaklckref, handle_##name##_weakgetref); \
	DEFINE_INTERN_ALIAS(handle_##name##_weakdecref, handle_##name##_decref)


/* Same as `DEFINE_HANDLE_REFCNT_FUNCTIONS', but include dedicated weak referencing support
 * in terms of `weakincref()'  and friends. The regular  `DEFINE_HANDLE_REFCNT_FUNCTIONS()'
 * will implement those  functions in  terms of the  regular reference  counter, such  that
 * anyone  holding a weak reference is actually  holding a regular reference. This behavior
 * is ok in most  cases, however objects which  can exist as handles  and could be made  to
 * form reference  loops should  only ever  store  weak references  to other  handles,  and
 * should themself  have a  dedicated weakref  mechanism.  One example  of such  an  object
 * is `struct epoll_controller' * */
#define DEFINE_HANDLE_REFCNT_FUNCTIONS_WITH_WEAKREF_SUPPORT(name, T)            \
	INTERN NOBLOCK WUNUSED NONNULL((1)) refcnt_t                                \
	NOTHROW(FCALL handle_##name##_refcnt)(T const *__restrict self) {           \
		return getrefcnt(self);                                                 \
	}                                                                           \
	INTERN NOBLOCK NONNULL((1)) void                                            \
	NOTHROW(FCALL handle_##name##_incref)(T *__restrict self) {                 \
		incref(self);                                                           \
	}                                                                           \
	INTERN NOBLOCK NONNULL((1)) void                                            \
	NOTHROW(FCALL handle_##name##_decref)(REF T *__restrict self) {             \
		decref(self);                                                           \
	}                                                                           \
	INTERN NOBLOCK NONNULL((1)) __BOOL                                          \
	NOTHROW(FCALL handle_##name##_tryincref)(T *__restrict self) {              \
		return tryincref(self);                                                 \
	}                                                                           \
	INTERN NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *         \
	NOTHROW(FCALL handle_##name##_weakgetref)(T *__restrict self) {             \
		return weakincref(self);                                                \
	}                                                                           \
	INTERN NOBLOCK WUNUSED NONNULL((1)) REF T *                                 \
	NOTHROW(FCALL handle_##name##_weaklckref)(void *__restrict weakref_ptr) {   \
		return tryincref((T *)weakref_ptr) ? (T *)weakref_ptr : __NULLPTR;      \
	}                                                                           \
	INTERN NOBLOCK NONNULL((1)) void                                            \
	NOTHROW(FCALL handle_##name##_weakdecref)(WEAK REF void *__restrict self) { \
		weakdecref((T *)self);                                                  \
	}

#endif /* __CC__ */
#endif /* CONFIG_BUILDING_KERNEL_CORE */



DECL_END
#endif /* __CC__ || __DEEMON__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_HANDLE_PROTO_H */
