/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_HANDLE_PROTO_H
#define GUARD_KERNEL_INCLUDE_KERNEL_HANDLE_PROTO_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <bits/crt/format-printer.h>
#include <kos/io.h>

#if defined(__CC__) || defined(__DEEMON__)
DECL_BEGIN

#ifndef __pformatprinter_defined
#define __pformatprinter_defined
typedef __pformatprinter pformatprinter;
typedef __pformatgetc pformatgetc;
typedef __pformatungetc pformatungetc;
#endif /* !__pformatprinter_defined */


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
		("read", "BLOCKING WUNUSED NONNULL((1))", "size_t", "", "KCALL",                                      \
		 { ("T *__restrict", "self"),                                                                         \
		   ("USER CHECKED void *", "dst"),                                                                    \
		   ("size_t", "num_bytes"),                                                                           \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ);"),                             \
		("write", "BLOCKING NONNULL((1))", "size_t", "", "KCALL",                                             \
		 { ("T *__restrict", "self"),                                                                         \
		   ("USER CHECKED void const *", "src"),                                                              \
		   ("size_t", "num_bytes"),                                                                           \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE);"),                            \
		("pread", "BLOCKING WUNUSED NONNULL((1))", "size_t", "", "KCALL",                                     \
		 { ("T *__restrict", "self"),                                                                         \
		   ("USER CHECKED void *", "dst"),                                                                    \
		   ("size_t", "num_bytes"),                                                                           \
		   ("pos_t", "addr"),                                                                                 \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_PREAD);"),                            \
		("pwrite", "BLOCKING NONNULL((1))", "size_t", "", "KCALL",                                            \
		 { ("T *__restrict", "self"),                                                                         \
		   ("USER CHECKED void const *", "src"),                                                              \
		   ("size_t", "num_bytes"),                                                                           \
		   ("pos_t", "addr"),                                                                                 \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_PWRITE);"),                           \
		("readv", "BLOCKING WUNUSED NONNULL((1, 2))", "size_t", "", "KCALL",                                  \
		 { ("T *__restrict", "self"),                                                                         \
		   ("struct iov_buffer *__restrict", "dst"),                                                          \
		   ("size_t", "num_bytes"),                                                                           \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ);"),                             \
		("writev", "BLOCKING NONNULL((1, 2))", "size_t", "", "KCALL",                                         \
		 { ("T *__restrict", "self"),                                                                         \
		   ("struct iov_buffer *__restrict", "src"),                                                          \
		   ("size_t", "num_bytes"),                                                                           \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE);"),                            \
		("preadv", "BLOCKING WUNUSED NONNULL((1, 2))", "size_t", "", "KCALL",                                 \
		 { ("T *__restrict", "self"),                                                                         \
		   ("struct iov_buffer *__restrict", "dst"),                                                          \
		   ("size_t", "num_bytes"),                                                                           \
		   ("pos_t", "addr"),                                                                                 \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_PREAD);"),                            \
		("pwritev", "BLOCKING NONNULL((1, 2))", "size_t", "", "KCALL",                                        \
		 { ("T *__restrict", "self"),                                                                         \
		   ("struct iov_buffer *__restrict", "src"),                                                          \
		   ("size_t", "num_bytes"),                                                                           \
		   ("pos_t", "addr"),                                                                                 \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_PWRITE);"),                           \
		("readdir", "BLOCKING WUNUSED NONNULL((1))", "size_t", "", "KCALL",                                   \
		 { ("T *__restrict", "self"),                                                                         \
		   ("USER CHECKED struct dirent *", "buf"),                                                           \
		   ("size_t", "bufsize"),                                                                             \
		   ("readdir_mode_t", "readdir_mode"),                                                                \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READDIR);"),                          \
		("seek", "BLOCKING NONNULL((1))", "pos_t", "", "KCALL",                                               \
		 { ("T *__restrict", "self"),                                                                         \
		   ("off_t", "offset"),                                                                               \
		   ("unsigned int", "whence") },                                                                      \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_SEEK);"),                             \
		("ioctl", "BLOCKING NONNULL((1))", "syscall_slong_t", "", "KCALL",                                    \
		 { ("T *__restrict", "self"),                                                                         \
		   ("ioctl_t", "cmd"),                                                                                \
		   ("USER UNCHECKED void *", "arg"),                                                                  \
		   ("iomode_t", "mode") },                                                                            \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND, cmd);"),        \
		("truncate", "BLOCKING NONNULL((1))", "void", "", "KCALL",                                            \
		 { ("T *__restrict", "self"),                                                                         \
		   ("pos_t", "new_size") },                                                                           \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_TRUNC);"),                            \
		("mmap", "BLOCKING NONNULL((1, 2))", "void", "", "KCALL",                                             \
		 { ("T *__restrict", "self"),                                                                         \
		   ("struct handle_mmap_info *__restrict", "info") },                                                 \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_MMAP);"),                             \
		("allocate", "BLOCKING NONNULL((1))", "pos_t", "", "KCALL",                                           \
		 { ("T *__restrict", "self"),                                                                         \
		   ("fallocate_mode_t", "mode"),                                                                      \
		   ("pos_t", "start"),                                                                                \
		   ("pos_t", "length") },                                                                             \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_ALLOCATE);"),                         \
		("sync", "BLOCKING NONNULL((1))", "void", "", "KCALL",                                                \
		 { ("T *__restrict", "self") },                                                                       \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_SYNC);"),                             \
		("datasync", "BLOCKING NONNULL((1))", "void", "", "KCALL",                                            \
		 { ("T *__restrict", "self") },                                                                       \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_DATASYNC);"),                         \
		("stat", "BLOCKING NONNULL((1))", "void", "", "KCALL",                                                \
		 { ("T *__restrict", "self"),                                                                         \
		   ("USER CHECKED struct stat *", "result") },                                                        \
		 "THROWS(...)",                                                                                       \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_STAT);"),                             \
		("pollconnect", "BLOCKING NONNULL((1))", "void", "", "KCALL",                                         \
		 { ("T *__restrict", "self"),                                                                         \
		   ("poll_mode_t", "what") },                                                                         \
		 "THROWS(...)",                                                                                       \
		 ""),                                                                                                 \
		("polltest", "BLOCKING WUNUSED NONNULL((1))", "poll_mode_t", "", "KCALL",                             \
		 { ("T *__restrict", "self"),                                                                         \
		   ("poll_mode_t", "what") },                                                                         \
		 "THROWS(...)",                                                                                       \
		 "return 0;"),                                                                                        \
		("tryas", "BLOCKING NONNULL((1))", "REF void *", "", "KCALL",                                         \
		 { ("T *__restrict", "self"),                                                                         \
		   ("uintptr_half_t", "wanted_type") },                                                               \
		 "THROWS(E_WOULDBLOCK)",                                                                              \
		 "return NULL;"),                                                                                     \
		("printlink", "BLOCKING NONNULL((1, 2))", "ssize_t", "", "KCALL",                                     \
		 { ("T *__restrict", "self"),                                                                         \
		   ("pformatprinter", "printer"),                                                                     \
		   ("void *", "arg") },                                                                               \
		 "THROWS(E_WOULDBLOCK, ...)",                                                                         \
		 "return handle_generic_printlink(self, {HANDLE_TYPE}, printer, arg);"),                              \
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
struct mfile;
struct fdirent;
struct path;
struct filehandle;
struct dirhandle;
struct fifohandle;
struct socket;
struct epoll_controller;
struct pipe;
struct pipe_reader;
struct pipe_writer;
struct eventfd;
struct signalfd;
struct mfutexfd;
struct taskpid;
struct module;
struct driver_loadlist;
struct refcountable;
struct notifyfd;
struct dirhandlex;



/* Handle operators for `HANDLE_TYPE_MFILE' (`struct mfile') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_mfile_refcnt)(struct mfile const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_mfile_incref)(struct mfile *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_mfile_decref)(REF struct mfile *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_mfile_tryincref)(struct mfile *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_mfile_weakgetref)(struct mfile *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct mfile *NOTHROW(FCALL handle_mfile_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_mfile_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_mfile_read(struct mfile *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_mfile_write(struct mfile *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_mfile_pread(struct mfile *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_mfile_pwrite(struct mfile *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_mfile_readv(struct mfile *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_mfile_writev(struct mfile *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_mfile_preadv(struct mfile *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_mfile_pwritev(struct mfile *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_mfile_readdir(struct mfile *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_mfile_seek(struct mfile *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF BLOCKING NONNULL((1)) syscall_slong_t KCALL handle_mfile_ioctl(struct mfile *__restrict self, ioctl_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_mfile_truncate(struct mfile *__restrict self, pos_t new_size) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) void KCALL handle_mfile_mmap(struct mfile *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_mfile_allocate(struct mfile *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_mfile_sync(struct mfile *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_mfile_datasync(struct mfile *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_mfile_stat(struct mfile *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_mfile_pollconnect(struct mfile *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL handle_mfile_polltest(struct mfile *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING NONNULL((1)) REF void *KCALL handle_mfile_tryas(struct mfile *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);
INTDEF BLOCKING NONNULL((1, 2)) ssize_t KCALL handle_mfile_printlink(struct mfile *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...);

/* Handle operators for `HANDLE_TYPE_DIRENT' (`struct fdirent') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_dirent_refcnt)(struct fdirent const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_dirent_incref)(struct fdirent *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_dirent_decref)(REF struct fdirent *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_dirent_tryincref)(struct fdirent *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_dirent_weakgetref)(struct fdirent *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct fdirent *NOTHROW(FCALL handle_dirent_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_dirent_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_dirent_read(struct fdirent *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_dirent_write(struct fdirent *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_dirent_pread(struct fdirent *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_dirent_pwrite(struct fdirent *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_dirent_readv(struct fdirent *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_dirent_writev(struct fdirent *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_dirent_preadv(struct fdirent *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_dirent_pwritev(struct fdirent *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_dirent_readdir(struct fdirent *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_dirent_seek(struct fdirent *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF BLOCKING NONNULL((1)) syscall_slong_t KCALL handle_dirent_ioctl(struct fdirent *__restrict self, ioctl_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_dirent_truncate(struct fdirent *__restrict self, pos_t new_size) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) void KCALL handle_dirent_mmap(struct fdirent *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_dirent_allocate(struct fdirent *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_dirent_sync(struct fdirent *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_dirent_datasync(struct fdirent *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_dirent_stat(struct fdirent *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_dirent_pollconnect(struct fdirent *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL handle_dirent_polltest(struct fdirent *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING NONNULL((1)) REF void *KCALL handle_dirent_tryas(struct fdirent *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);
INTDEF BLOCKING NONNULL((1, 2)) ssize_t KCALL handle_dirent_printlink(struct fdirent *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...);

/* Handle operators for `HANDLE_TYPE_PATH' (`struct path') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_path_refcnt)(struct path const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_path_incref)(struct path *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_path_decref)(REF struct path *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_path_tryincref)(struct path *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_path_weakgetref)(struct path *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct path *NOTHROW(FCALL handle_path_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_path_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_path_read(struct path *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_path_write(struct path *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_path_pread(struct path *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_path_pwrite(struct path *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_path_readv(struct path *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_path_writev(struct path *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_path_preadv(struct path *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_path_pwritev(struct path *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_path_readdir(struct path *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_path_seek(struct path *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF BLOCKING NONNULL((1)) syscall_slong_t KCALL handle_path_ioctl(struct path *__restrict self, ioctl_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_path_truncate(struct path *__restrict self, pos_t new_size) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) void KCALL handle_path_mmap(struct path *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_path_allocate(struct path *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_path_sync(struct path *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_path_datasync(struct path *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_path_stat(struct path *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_path_pollconnect(struct path *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL handle_path_polltest(struct path *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING NONNULL((1)) REF void *KCALL handle_path_tryas(struct path *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);
INTDEF BLOCKING NONNULL((1, 2)) ssize_t KCALL handle_path_printlink(struct path *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...);

/* Handle operators for `HANDLE_TYPE_FILEHANDLE' (`struct filehandle') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_filehandle_refcnt)(struct filehandle const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_filehandle_incref)(struct filehandle *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_filehandle_decref)(REF struct filehandle *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_filehandle_tryincref)(struct filehandle *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_filehandle_weakgetref)(struct filehandle *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct filehandle *NOTHROW(FCALL handle_filehandle_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_filehandle_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_filehandle_read(struct filehandle *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_filehandle_write(struct filehandle *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_filehandle_pread(struct filehandle *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_filehandle_pwrite(struct filehandle *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_filehandle_readv(struct filehandle *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_filehandle_writev(struct filehandle *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_filehandle_preadv(struct filehandle *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_filehandle_pwritev(struct filehandle *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_filehandle_readdir(struct filehandle *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_filehandle_seek(struct filehandle *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF BLOCKING NONNULL((1)) syscall_slong_t KCALL handle_filehandle_ioctl(struct filehandle *__restrict self, ioctl_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_filehandle_truncate(struct filehandle *__restrict self, pos_t new_size) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) void KCALL handle_filehandle_mmap(struct filehandle *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_filehandle_allocate(struct filehandle *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_filehandle_sync(struct filehandle *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_filehandle_datasync(struct filehandle *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_filehandle_stat(struct filehandle *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_filehandle_pollconnect(struct filehandle *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL handle_filehandle_polltest(struct filehandle *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING NONNULL((1)) REF void *KCALL handle_filehandle_tryas(struct filehandle *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);
INTDEF BLOCKING NONNULL((1, 2)) ssize_t KCALL handle_filehandle_printlink(struct filehandle *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...);

/* Handle operators for `HANDLE_TYPE_TEMPHANDLE' (`struct filehandle') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_temphandle_refcnt)(struct filehandle const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_temphandle_incref)(struct filehandle *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_temphandle_decref)(REF struct filehandle *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_temphandle_tryincref)(struct filehandle *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_temphandle_weakgetref)(struct filehandle *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct filehandle *NOTHROW(FCALL handle_temphandle_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_temphandle_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_temphandle_read(struct filehandle *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_temphandle_write(struct filehandle *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_temphandle_pread(struct filehandle *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_temphandle_pwrite(struct filehandle *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_temphandle_readv(struct filehandle *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_temphandle_writev(struct filehandle *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_temphandle_preadv(struct filehandle *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_temphandle_pwritev(struct filehandle *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_temphandle_readdir(struct filehandle *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_temphandle_seek(struct filehandle *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF BLOCKING NONNULL((1)) syscall_slong_t KCALL handle_temphandle_ioctl(struct filehandle *__restrict self, ioctl_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_temphandle_truncate(struct filehandle *__restrict self, pos_t new_size) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) void KCALL handle_temphandle_mmap(struct filehandle *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_temphandle_allocate(struct filehandle *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_temphandle_sync(struct filehandle *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_temphandle_datasync(struct filehandle *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_temphandle_stat(struct filehandle *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_temphandle_pollconnect(struct filehandle *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL handle_temphandle_polltest(struct filehandle *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING NONNULL((1)) REF void *KCALL handle_temphandle_tryas(struct filehandle *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);
INTDEF BLOCKING NONNULL((1, 2)) ssize_t KCALL handle_temphandle_printlink(struct filehandle *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...);

/* Handle operators for `HANDLE_TYPE_DIRHANDLE' (`struct dirhandle') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_dirhandle_refcnt)(struct dirhandle const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_dirhandle_incref)(struct dirhandle *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_dirhandle_decref)(REF struct dirhandle *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_dirhandle_tryincref)(struct dirhandle *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_dirhandle_weakgetref)(struct dirhandle *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct dirhandle *NOTHROW(FCALL handle_dirhandle_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_dirhandle_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_dirhandle_read(struct dirhandle *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_dirhandle_write(struct dirhandle *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_dirhandle_pread(struct dirhandle *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_dirhandle_pwrite(struct dirhandle *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_dirhandle_readv(struct dirhandle *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_dirhandle_writev(struct dirhandle *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_dirhandle_preadv(struct dirhandle *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_dirhandle_pwritev(struct dirhandle *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_dirhandle_readdir(struct dirhandle *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_dirhandle_seek(struct dirhandle *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF BLOCKING NONNULL((1)) syscall_slong_t KCALL handle_dirhandle_ioctl(struct dirhandle *__restrict self, ioctl_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_dirhandle_truncate(struct dirhandle *__restrict self, pos_t new_size) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) void KCALL handle_dirhandle_mmap(struct dirhandle *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_dirhandle_allocate(struct dirhandle *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_dirhandle_sync(struct dirhandle *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_dirhandle_datasync(struct dirhandle *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_dirhandle_stat(struct dirhandle *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_dirhandle_pollconnect(struct dirhandle *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL handle_dirhandle_polltest(struct dirhandle *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING NONNULL((1)) REF void *KCALL handle_dirhandle_tryas(struct dirhandle *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);
INTDEF BLOCKING NONNULL((1, 2)) ssize_t KCALL handle_dirhandle_printlink(struct dirhandle *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...);

/* Handle operators for `HANDLE_TYPE_FIFOHANDLE' (`struct fifohandle') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_fifohandle_refcnt)(struct fifohandle const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_fifohandle_incref)(struct fifohandle *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_fifohandle_decref)(REF struct fifohandle *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_fifohandle_tryincref)(struct fifohandle *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_fifohandle_weakgetref)(struct fifohandle *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct fifohandle *NOTHROW(FCALL handle_fifohandle_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_fifohandle_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_fifohandle_read(struct fifohandle *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_fifohandle_write(struct fifohandle *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_fifohandle_pread(struct fifohandle *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_fifohandle_pwrite(struct fifohandle *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_fifohandle_readv(struct fifohandle *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_fifohandle_writev(struct fifohandle *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_fifohandle_preadv(struct fifohandle *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_fifohandle_pwritev(struct fifohandle *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_fifohandle_readdir(struct fifohandle *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_fifohandle_seek(struct fifohandle *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF BLOCKING NONNULL((1)) syscall_slong_t KCALL handle_fifohandle_ioctl(struct fifohandle *__restrict self, ioctl_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_fifohandle_truncate(struct fifohandle *__restrict self, pos_t new_size) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) void KCALL handle_fifohandle_mmap(struct fifohandle *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_fifohandle_allocate(struct fifohandle *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_fifohandle_sync(struct fifohandle *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_fifohandle_datasync(struct fifohandle *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_fifohandle_stat(struct fifohandle *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_fifohandle_pollconnect(struct fifohandle *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL handle_fifohandle_polltest(struct fifohandle *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING NONNULL((1)) REF void *KCALL handle_fifohandle_tryas(struct fifohandle *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);
INTDEF BLOCKING NONNULL((1, 2)) ssize_t KCALL handle_fifohandle_printlink(struct fifohandle *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...);

/* Handle operators for `HANDLE_TYPE_SOCKET' (`struct socket') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_socket_refcnt)(struct socket const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_socket_incref)(struct socket *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_socket_decref)(REF struct socket *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_socket_tryincref)(struct socket *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_socket_weakgetref)(struct socket *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct socket *NOTHROW(FCALL handle_socket_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_socket_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_socket_read(struct socket *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_socket_write(struct socket *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_socket_pread(struct socket *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_socket_pwrite(struct socket *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_socket_readv(struct socket *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_socket_writev(struct socket *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_socket_preadv(struct socket *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_socket_pwritev(struct socket *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_socket_readdir(struct socket *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_socket_seek(struct socket *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF BLOCKING NONNULL((1)) syscall_slong_t KCALL handle_socket_ioctl(struct socket *__restrict self, ioctl_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_socket_truncate(struct socket *__restrict self, pos_t new_size) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) void KCALL handle_socket_mmap(struct socket *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_socket_allocate(struct socket *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_socket_sync(struct socket *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_socket_datasync(struct socket *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_socket_stat(struct socket *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_socket_pollconnect(struct socket *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL handle_socket_polltest(struct socket *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING NONNULL((1)) REF void *KCALL handle_socket_tryas(struct socket *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);
INTDEF BLOCKING NONNULL((1, 2)) ssize_t KCALL handle_socket_printlink(struct socket *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...);

/* Handle operators for `HANDLE_TYPE_EPOLL' (`struct epoll_controller') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_epoll_refcnt)(struct epoll_controller const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_epoll_incref)(struct epoll_controller *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_epoll_decref)(REF struct epoll_controller *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_epoll_tryincref)(struct epoll_controller *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_epoll_weakgetref)(struct epoll_controller *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct epoll_controller *NOTHROW(FCALL handle_epoll_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_epoll_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_epoll_read(struct epoll_controller *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_epoll_write(struct epoll_controller *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_epoll_pread(struct epoll_controller *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_epoll_pwrite(struct epoll_controller *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_epoll_readv(struct epoll_controller *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_epoll_writev(struct epoll_controller *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_epoll_preadv(struct epoll_controller *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_epoll_pwritev(struct epoll_controller *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_epoll_readdir(struct epoll_controller *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_epoll_seek(struct epoll_controller *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF BLOCKING NONNULL((1)) syscall_slong_t KCALL handle_epoll_ioctl(struct epoll_controller *__restrict self, ioctl_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_epoll_truncate(struct epoll_controller *__restrict self, pos_t new_size) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) void KCALL handle_epoll_mmap(struct epoll_controller *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_epoll_allocate(struct epoll_controller *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_epoll_sync(struct epoll_controller *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_epoll_datasync(struct epoll_controller *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_epoll_stat(struct epoll_controller *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_epoll_pollconnect(struct epoll_controller *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL handle_epoll_polltest(struct epoll_controller *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING NONNULL((1)) REF void *KCALL handle_epoll_tryas(struct epoll_controller *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);
INTDEF BLOCKING NONNULL((1, 2)) ssize_t KCALL handle_epoll_printlink(struct epoll_controller *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...);

/* Handle operators for `HANDLE_TYPE_PIPE' (`struct pipe') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_pipe_refcnt)(struct pipe const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_incref)(struct pipe *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_decref)(REF struct pipe *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_pipe_tryincref)(struct pipe *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_pipe_weakgetref)(struct pipe *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct pipe *NOTHROW(FCALL handle_pipe_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_pipe_read(struct pipe *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_pipe_write(struct pipe *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_pipe_pread(struct pipe *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_pipe_pwrite(struct pipe *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_readv(struct pipe *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_pipe_writev(struct pipe *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_preadv(struct pipe *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_pipe_pwritev(struct pipe *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_pipe_readdir(struct pipe *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_pipe_seek(struct pipe *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF BLOCKING NONNULL((1)) syscall_slong_t KCALL handle_pipe_ioctl(struct pipe *__restrict self, ioctl_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_pipe_truncate(struct pipe *__restrict self, pos_t new_size) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) void KCALL handle_pipe_mmap(struct pipe *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_pipe_allocate(struct pipe *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_pipe_sync(struct pipe *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_pipe_datasync(struct pipe *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_pipe_stat(struct pipe *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_pipe_pollconnect(struct pipe *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL handle_pipe_polltest(struct pipe *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING NONNULL((1)) REF void *KCALL handle_pipe_tryas(struct pipe *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);
INTDEF BLOCKING NONNULL((1, 2)) ssize_t KCALL handle_pipe_printlink(struct pipe *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...);

/* Handle operators for `HANDLE_TYPE_PIPE_READER' (`struct pipe_reader') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_pipe_reader_refcnt)(struct pipe_reader const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_reader_incref)(struct pipe_reader *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_reader_decref)(REF struct pipe_reader *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_pipe_reader_tryincref)(struct pipe_reader *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_pipe_reader_weakgetref)(struct pipe_reader *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct pipe_reader *NOTHROW(FCALL handle_pipe_reader_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_reader_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_pipe_reader_read(struct pipe_reader *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_pipe_reader_write(struct pipe_reader *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_pipe_reader_pread(struct pipe_reader *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_pipe_reader_pwrite(struct pipe_reader *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_reader_readv(struct pipe_reader *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_pipe_reader_writev(struct pipe_reader *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_reader_preadv(struct pipe_reader *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_pipe_reader_pwritev(struct pipe_reader *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_pipe_reader_readdir(struct pipe_reader *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_pipe_reader_seek(struct pipe_reader *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF BLOCKING NONNULL((1)) syscall_slong_t KCALL handle_pipe_reader_ioctl(struct pipe_reader *__restrict self, ioctl_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_pipe_reader_truncate(struct pipe_reader *__restrict self, pos_t new_size) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) void KCALL handle_pipe_reader_mmap(struct pipe_reader *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_pipe_reader_allocate(struct pipe_reader *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_pipe_reader_sync(struct pipe_reader *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_pipe_reader_datasync(struct pipe_reader *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_pipe_reader_stat(struct pipe_reader *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_pipe_reader_pollconnect(struct pipe_reader *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL handle_pipe_reader_polltest(struct pipe_reader *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING NONNULL((1)) REF void *KCALL handle_pipe_reader_tryas(struct pipe_reader *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);
INTDEF BLOCKING NONNULL((1, 2)) ssize_t KCALL handle_pipe_reader_printlink(struct pipe_reader *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...);

/* Handle operators for `HANDLE_TYPE_PIPE_WRITER' (`struct pipe_writer') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_pipe_writer_refcnt)(struct pipe_writer const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_writer_incref)(struct pipe_writer *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_writer_decref)(REF struct pipe_writer *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_pipe_writer_tryincref)(struct pipe_writer *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_pipe_writer_weakgetref)(struct pipe_writer *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct pipe_writer *NOTHROW(FCALL handle_pipe_writer_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_writer_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_pipe_writer_read(struct pipe_writer *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_pipe_writer_write(struct pipe_writer *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_pipe_writer_pread(struct pipe_writer *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_pipe_writer_pwrite(struct pipe_writer *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_writer_readv(struct pipe_writer *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_pipe_writer_writev(struct pipe_writer *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_writer_preadv(struct pipe_writer *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_pipe_writer_pwritev(struct pipe_writer *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_pipe_writer_readdir(struct pipe_writer *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_pipe_writer_seek(struct pipe_writer *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF BLOCKING NONNULL((1)) syscall_slong_t KCALL handle_pipe_writer_ioctl(struct pipe_writer *__restrict self, ioctl_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_pipe_writer_truncate(struct pipe_writer *__restrict self, pos_t new_size) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) void KCALL handle_pipe_writer_mmap(struct pipe_writer *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_pipe_writer_allocate(struct pipe_writer *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_pipe_writer_sync(struct pipe_writer *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_pipe_writer_datasync(struct pipe_writer *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_pipe_writer_stat(struct pipe_writer *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_pipe_writer_pollconnect(struct pipe_writer *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL handle_pipe_writer_polltest(struct pipe_writer *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING NONNULL((1)) REF void *KCALL handle_pipe_writer_tryas(struct pipe_writer *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);
INTDEF BLOCKING NONNULL((1, 2)) ssize_t KCALL handle_pipe_writer_printlink(struct pipe_writer *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...);

/* Handle operators for `HANDLE_TYPE_EVENTFD_FENCE' (`struct eventfd') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_eventfd_fence_refcnt)(struct eventfd const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_eventfd_fence_incref)(struct eventfd *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_eventfd_fence_decref)(REF struct eventfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_eventfd_fence_tryincref)(struct eventfd *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_eventfd_fence_weakgetref)(struct eventfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct eventfd *NOTHROW(FCALL handle_eventfd_fence_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_eventfd_fence_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_fence_read(struct eventfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_eventfd_fence_write(struct eventfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_fence_pread(struct eventfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_eventfd_fence_pwrite(struct eventfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_fence_readv(struct eventfd *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_eventfd_fence_writev(struct eventfd *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_fence_preadv(struct eventfd *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_eventfd_fence_pwritev(struct eventfd *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_fence_readdir(struct eventfd *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_eventfd_fence_seek(struct eventfd *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF BLOCKING NONNULL((1)) syscall_slong_t KCALL handle_eventfd_fence_ioctl(struct eventfd *__restrict self, ioctl_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_eventfd_fence_truncate(struct eventfd *__restrict self, pos_t new_size) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) void KCALL handle_eventfd_fence_mmap(struct eventfd *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_eventfd_fence_allocate(struct eventfd *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_eventfd_fence_sync(struct eventfd *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_eventfd_fence_datasync(struct eventfd *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_eventfd_fence_stat(struct eventfd *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_eventfd_fence_pollconnect(struct eventfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL handle_eventfd_fence_polltest(struct eventfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING NONNULL((1)) REF void *KCALL handle_eventfd_fence_tryas(struct eventfd *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);
INTDEF BLOCKING NONNULL((1, 2)) ssize_t KCALL handle_eventfd_fence_printlink(struct eventfd *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...);

/* Handle operators for `HANDLE_TYPE_EVENTFD_SEMA' (`struct eventfd') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_eventfd_sema_refcnt)(struct eventfd const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_eventfd_sema_incref)(struct eventfd *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_eventfd_sema_decref)(REF struct eventfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_eventfd_sema_tryincref)(struct eventfd *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_eventfd_sema_weakgetref)(struct eventfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct eventfd *NOTHROW(FCALL handle_eventfd_sema_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_eventfd_sema_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_sema_read(struct eventfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_eventfd_sema_write(struct eventfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_sema_pread(struct eventfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_eventfd_sema_pwrite(struct eventfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_sema_readv(struct eventfd *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_eventfd_sema_writev(struct eventfd *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_sema_preadv(struct eventfd *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_eventfd_sema_pwritev(struct eventfd *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_sema_readdir(struct eventfd *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_eventfd_sema_seek(struct eventfd *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF BLOCKING NONNULL((1)) syscall_slong_t KCALL handle_eventfd_sema_ioctl(struct eventfd *__restrict self, ioctl_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_eventfd_sema_truncate(struct eventfd *__restrict self, pos_t new_size) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) void KCALL handle_eventfd_sema_mmap(struct eventfd *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_eventfd_sema_allocate(struct eventfd *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_eventfd_sema_sync(struct eventfd *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_eventfd_sema_datasync(struct eventfd *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_eventfd_sema_stat(struct eventfd *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_eventfd_sema_pollconnect(struct eventfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL handle_eventfd_sema_polltest(struct eventfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING NONNULL((1)) REF void *KCALL handle_eventfd_sema_tryas(struct eventfd *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);
INTDEF BLOCKING NONNULL((1, 2)) ssize_t KCALL handle_eventfd_sema_printlink(struct eventfd *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...);

/* Handle operators for `HANDLE_TYPE_SIGNALFD' (`struct signalfd') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_signalfd_refcnt)(struct signalfd const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_signalfd_incref)(struct signalfd *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_signalfd_decref)(REF struct signalfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_signalfd_tryincref)(struct signalfd *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_signalfd_weakgetref)(struct signalfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct signalfd *NOTHROW(FCALL handle_signalfd_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_signalfd_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_signalfd_read(struct signalfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_signalfd_write(struct signalfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_signalfd_pread(struct signalfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_signalfd_pwrite(struct signalfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_signalfd_readv(struct signalfd *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_signalfd_writev(struct signalfd *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_signalfd_preadv(struct signalfd *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_signalfd_pwritev(struct signalfd *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_signalfd_readdir(struct signalfd *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_signalfd_seek(struct signalfd *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF BLOCKING NONNULL((1)) syscall_slong_t KCALL handle_signalfd_ioctl(struct signalfd *__restrict self, ioctl_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_signalfd_truncate(struct signalfd *__restrict self, pos_t new_size) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) void KCALL handle_signalfd_mmap(struct signalfd *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_signalfd_allocate(struct signalfd *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_signalfd_sync(struct signalfd *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_signalfd_datasync(struct signalfd *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_signalfd_stat(struct signalfd *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_signalfd_pollconnect(struct signalfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL handle_signalfd_polltest(struct signalfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING NONNULL((1)) REF void *KCALL handle_signalfd_tryas(struct signalfd *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);
INTDEF BLOCKING NONNULL((1, 2)) ssize_t KCALL handle_signalfd_printlink(struct signalfd *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...);

/* Handle operators for `HANDLE_TYPE_FUTEXFD' (`struct mfutexfd') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_futexfd_refcnt)(struct mfutexfd const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_futexfd_incref)(struct mfutexfd *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_futexfd_decref)(REF struct mfutexfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_futexfd_tryincref)(struct mfutexfd *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_futexfd_weakgetref)(struct mfutexfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct mfutexfd *NOTHROW(FCALL handle_futexfd_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_futexfd_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_futexfd_read(struct mfutexfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_futexfd_write(struct mfutexfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_futexfd_pread(struct mfutexfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_futexfd_pwrite(struct mfutexfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_futexfd_readv(struct mfutexfd *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_futexfd_writev(struct mfutexfd *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_futexfd_preadv(struct mfutexfd *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_futexfd_pwritev(struct mfutexfd *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_futexfd_readdir(struct mfutexfd *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_futexfd_seek(struct mfutexfd *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF BLOCKING NONNULL((1)) syscall_slong_t KCALL handle_futexfd_ioctl(struct mfutexfd *__restrict self, ioctl_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_futexfd_truncate(struct mfutexfd *__restrict self, pos_t new_size) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) void KCALL handle_futexfd_mmap(struct mfutexfd *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_futexfd_allocate(struct mfutexfd *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_futexfd_sync(struct mfutexfd *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_futexfd_datasync(struct mfutexfd *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_futexfd_stat(struct mfutexfd *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_futexfd_pollconnect(struct mfutexfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL handle_futexfd_polltest(struct mfutexfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING NONNULL((1)) REF void *KCALL handle_futexfd_tryas(struct mfutexfd *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);
INTDEF BLOCKING NONNULL((1, 2)) ssize_t KCALL handle_futexfd_printlink(struct mfutexfd *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...);

/* Handle operators for `HANDLE_TYPE_PIDFD' (`struct taskpid') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_pidfd_refcnt)(struct taskpid const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pidfd_incref)(struct taskpid *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pidfd_decref)(REF struct taskpid *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_pidfd_tryincref)(struct taskpid *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_pidfd_weakgetref)(struct taskpid *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct taskpid *NOTHROW(FCALL handle_pidfd_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pidfd_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_pidfd_read(struct taskpid *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_pidfd_write(struct taskpid *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_pidfd_pread(struct taskpid *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_pidfd_pwrite(struct taskpid *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_pidfd_readv(struct taskpid *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_pidfd_writev(struct taskpid *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_pidfd_preadv(struct taskpid *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_pidfd_pwritev(struct taskpid *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_pidfd_readdir(struct taskpid *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_pidfd_seek(struct taskpid *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF BLOCKING NONNULL((1)) syscall_slong_t KCALL handle_pidfd_ioctl(struct taskpid *__restrict self, ioctl_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_pidfd_truncate(struct taskpid *__restrict self, pos_t new_size) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) void KCALL handle_pidfd_mmap(struct taskpid *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_pidfd_allocate(struct taskpid *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_pidfd_sync(struct taskpid *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_pidfd_datasync(struct taskpid *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_pidfd_stat(struct taskpid *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_pidfd_pollconnect(struct taskpid *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL handle_pidfd_polltest(struct taskpid *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING NONNULL((1)) REF void *KCALL handle_pidfd_tryas(struct taskpid *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);
INTDEF BLOCKING NONNULL((1, 2)) ssize_t KCALL handle_pidfd_printlink(struct taskpid *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...);

/* Handle operators for `HANDLE_TYPE_MODULE' (`struct module') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_module_refcnt)(struct module const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_module_incref)(struct module *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_module_decref)(REF struct module *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_module_tryincref)(struct module *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_module_weakgetref)(struct module *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct module *NOTHROW(FCALL handle_module_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_module_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_module_read(struct module *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_module_write(struct module *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_module_pread(struct module *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_module_pwrite(struct module *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_module_readv(struct module *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_module_writev(struct module *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_module_preadv(struct module *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_module_pwritev(struct module *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_module_readdir(struct module *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_module_seek(struct module *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF BLOCKING NONNULL((1)) syscall_slong_t KCALL handle_module_ioctl(struct module *__restrict self, ioctl_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_module_truncate(struct module *__restrict self, pos_t new_size) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) void KCALL handle_module_mmap(struct module *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_module_allocate(struct module *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_module_sync(struct module *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_module_datasync(struct module *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_module_stat(struct module *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_module_pollconnect(struct module *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL handle_module_polltest(struct module *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING NONNULL((1)) REF void *KCALL handle_module_tryas(struct module *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);
INTDEF BLOCKING NONNULL((1, 2)) ssize_t KCALL handle_module_printlink(struct module *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...);

/* Handle operators for `HANDLE_TYPE_DRIVER_LOADLIST' (`struct driver_loadlist') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_driver_loadlist_refcnt)(struct driver_loadlist const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_driver_loadlist_incref)(struct driver_loadlist *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_driver_loadlist_decref)(REF struct driver_loadlist *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_driver_loadlist_tryincref)(struct driver_loadlist *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_driver_loadlist_weakgetref)(struct driver_loadlist *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct driver_loadlist *NOTHROW(FCALL handle_driver_loadlist_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_driver_loadlist_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_driver_loadlist_read(struct driver_loadlist *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_driver_loadlist_write(struct driver_loadlist *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_driver_loadlist_pread(struct driver_loadlist *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_driver_loadlist_pwrite(struct driver_loadlist *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_loadlist_readv(struct driver_loadlist *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_driver_loadlist_writev(struct driver_loadlist *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_loadlist_preadv(struct driver_loadlist *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_driver_loadlist_pwritev(struct driver_loadlist *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_driver_loadlist_readdir(struct driver_loadlist *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_driver_loadlist_seek(struct driver_loadlist *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF BLOCKING NONNULL((1)) syscall_slong_t KCALL handle_driver_loadlist_ioctl(struct driver_loadlist *__restrict self, ioctl_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_driver_loadlist_truncate(struct driver_loadlist *__restrict self, pos_t new_size) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) void KCALL handle_driver_loadlist_mmap(struct driver_loadlist *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_driver_loadlist_allocate(struct driver_loadlist *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_driver_loadlist_sync(struct driver_loadlist *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_driver_loadlist_datasync(struct driver_loadlist *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_driver_loadlist_stat(struct driver_loadlist *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_driver_loadlist_pollconnect(struct driver_loadlist *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL handle_driver_loadlist_polltest(struct driver_loadlist *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING NONNULL((1)) REF void *KCALL handle_driver_loadlist_tryas(struct driver_loadlist *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);
INTDEF BLOCKING NONNULL((1, 2)) ssize_t KCALL handle_driver_loadlist_printlink(struct driver_loadlist *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...);

/* Handle operators for `HANDLE_TYPE_REFCOUNTABLE' (`struct refcountable') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_refcountable_refcnt)(struct refcountable const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_refcountable_incref)(struct refcountable *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_refcountable_decref)(REF struct refcountable *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_refcountable_tryincref)(struct refcountable *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_refcountable_weakgetref)(struct refcountable *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct refcountable *NOTHROW(FCALL handle_refcountable_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_refcountable_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_refcountable_read(struct refcountable *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_refcountable_write(struct refcountable *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_refcountable_pread(struct refcountable *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_refcountable_pwrite(struct refcountable *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_refcountable_readv(struct refcountable *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_refcountable_writev(struct refcountable *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_refcountable_preadv(struct refcountable *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_refcountable_pwritev(struct refcountable *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_refcountable_readdir(struct refcountable *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_refcountable_seek(struct refcountable *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF BLOCKING NONNULL((1)) syscall_slong_t KCALL handle_refcountable_ioctl(struct refcountable *__restrict self, ioctl_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_refcountable_truncate(struct refcountable *__restrict self, pos_t new_size) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) void KCALL handle_refcountable_mmap(struct refcountable *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_refcountable_allocate(struct refcountable *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_refcountable_sync(struct refcountable *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_refcountable_datasync(struct refcountable *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_refcountable_stat(struct refcountable *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_refcountable_pollconnect(struct refcountable *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL handle_refcountable_polltest(struct refcountable *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING NONNULL((1)) REF void *KCALL handle_refcountable_tryas(struct refcountable *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);
INTDEF BLOCKING NONNULL((1, 2)) ssize_t KCALL handle_refcountable_printlink(struct refcountable *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...);

/* Handle operators for `HANDLE_TYPE_NOTIFYFD' (`struct notifyfd') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_notifyfd_refcnt)(struct notifyfd const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_notifyfd_incref)(struct notifyfd *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_notifyfd_decref)(REF struct notifyfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_notifyfd_tryincref)(struct notifyfd *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_notifyfd_weakgetref)(struct notifyfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct notifyfd *NOTHROW(FCALL handle_notifyfd_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_notifyfd_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_notifyfd_read(struct notifyfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_notifyfd_write(struct notifyfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_notifyfd_pread(struct notifyfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_notifyfd_pwrite(struct notifyfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_notifyfd_readv(struct notifyfd *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_notifyfd_writev(struct notifyfd *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_notifyfd_preadv(struct notifyfd *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_notifyfd_pwritev(struct notifyfd *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_notifyfd_readdir(struct notifyfd *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_notifyfd_seek(struct notifyfd *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF BLOCKING NONNULL((1)) syscall_slong_t KCALL handle_notifyfd_ioctl(struct notifyfd *__restrict self, ioctl_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_notifyfd_truncate(struct notifyfd *__restrict self, pos_t new_size) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) void KCALL handle_notifyfd_mmap(struct notifyfd *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_notifyfd_allocate(struct notifyfd *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_notifyfd_sync(struct notifyfd *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_notifyfd_datasync(struct notifyfd *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_notifyfd_stat(struct notifyfd *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_notifyfd_pollconnect(struct notifyfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL handle_notifyfd_polltest(struct notifyfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING NONNULL((1)) REF void *KCALL handle_notifyfd_tryas(struct notifyfd *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);
INTDEF BLOCKING NONNULL((1, 2)) ssize_t KCALL handle_notifyfd_printlink(struct notifyfd *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...);

/* Handle operators for `HANDLE_TYPE_DIRHANDLEX' (`struct dirhandlex') */
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_dirhandlex_refcnt)(struct dirhandlex const *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_dirhandlex_incref)(struct dirhandlex *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_dirhandlex_decref)(REF struct dirhandlex *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL NOTHROW(FCALL handle_dirhandlex_tryincref)(struct dirhandlex *__restrict self);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) WEAK REF void *NOTHROW(FCALL handle_dirhandlex_weakgetref)(struct dirhandlex *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) REF struct dirhandlex *NOTHROW(FCALL handle_dirhandlex_weaklckref)(void *__restrict weakref_ptr);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_dirhandlex_weakdecref)(WEAK REF void *__restrict weakref_ptr);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_dirhandlex_read(struct dirhandlex *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_dirhandlex_write(struct dirhandlex *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_dirhandlex_pread(struct dirhandlex *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) size_t KCALL handle_dirhandlex_pwrite(struct dirhandlex *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_dirhandlex_readv(struct dirhandlex *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_dirhandlex_writev(struct dirhandlex *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL handle_dirhandlex_preadv(struct dirhandlex *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) size_t KCALL handle_dirhandlex_pwritev(struct dirhandlex *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL handle_dirhandlex_readdir(struct dirhandlex *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_dirhandlex_seek(struct dirhandlex *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF BLOCKING NONNULL((1)) syscall_slong_t KCALL handle_dirhandlex_ioctl(struct dirhandlex *__restrict self, ioctl_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_dirhandlex_truncate(struct dirhandlex *__restrict self, pos_t new_size) THROWS(...);
INTDEF BLOCKING NONNULL((1, 2)) void KCALL handle_dirhandlex_mmap(struct dirhandlex *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
INTDEF BLOCKING NONNULL((1)) pos_t KCALL handle_dirhandlex_allocate(struct dirhandlex *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_dirhandlex_sync(struct dirhandlex *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_dirhandlex_datasync(struct dirhandlex *__restrict self) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_dirhandlex_stat(struct dirhandlex *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF BLOCKING NONNULL((1)) void KCALL handle_dirhandlex_pollconnect(struct dirhandlex *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL handle_dirhandlex_polltest(struct dirhandlex *__restrict self, poll_mode_t what) THROWS(...);
INTDEF BLOCKING NONNULL((1)) REF void *KCALL handle_dirhandlex_tryas(struct dirhandlex *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);
INTDEF BLOCKING NONNULL((1, 2)) ssize_t KCALL handle_dirhandlex_printlink(struct dirhandlex *__restrict self, pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...);

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
