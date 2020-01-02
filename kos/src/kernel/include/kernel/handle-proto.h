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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_HANDLE_PROTO_H
#define GUARD_KERNEL_INCLUDE_KERNEL_HANDLE_PROTO_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <kos/io.h>

DECL_BEGIN

#ifdef __DEEMON__
#define HANDLE_OPERATOR_PROTOTYPES                                                                       \
	{                                                                                                    \
		("incref", "NOBLOCK NONNULL((1))", "void", "NOTHROW", "FCALL",                                   \
		 { ("void *__restrict", "self") },                                                               \
		 "", ""),                                                                                        \
		("decref", "NOBLOCK NONNULL((1))", "void", "NOTHROW", "FCALL",                                   \
		 { ("void *__restrict", "self") },                                                               \
		 "", ""),                                                                                        \
		("refcnt", "NOBLOCK WUNUSED NONNULL((1))", "refcnt_t", "NOTHROW", "FCALL",                       \
		 { ("void const *__restrict", "self") },                                                         \
		 "", "return 0;"),                                                                               \
		("read", "WUNUSED NONNULL((1))", "size_t", "", "KCALL",                                          \
		 { ("void *__restrict", "self"),                                                                 \
		   ("USER CHECKED void *", "dst"),                                                               \
		   ("size_t", "num_bytes"),                                                                      \
		   ("iomode_t", "mode") },                                                                       \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ);"),                        \
		("write", "WUNUSED NONNULL((1))", "size_t", "", "KCALL",                                         \
		 { ("void *__restrict", "self"),                                                                 \
		   ("USER CHECKED void const *", "src"),                                                         \
		   ("size_t", "num_bytes"),                                                                      \
		   ("iomode_t", "mode") },                                                                       \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE);"),                       \
		("pread", "WUNUSED NONNULL((1))", "size_t", "", "KCALL",                                         \
		 { ("void *__restrict", "self"),                                                                 \
		   ("USER CHECKED void *", "dst"),                                                               \
		   ("size_t", "num_bytes"),                                                                      \
		   ("pos_t", "addr"),                                                                            \
		   ("iomode_t", "mode") },                                                                       \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ);"),                        \
		("pwrite", "WUNUSED NONNULL((1))", "size_t", "", "KCALL",                                        \
		 { ("void *__restrict", "self"),                                                                 \
		   ("USER CHECKED void const *", "src"),                                                         \
		   ("size_t", "num_bytes"),                                                                      \
		   ("pos_t", "addr"),                                                                            \
		   ("iomode_t", "mode") },                                                                       \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE);"),                       \
		("readv", "WUNUSED NONNULL((1, 2))", "size_t", "", "KCALL",                                      \
		 { ("void *__restrict", "self"),                                                                 \
		   ("struct aio_buffer *__restrict", "dst"),                                                     \
		   ("size_t", "num_bytes"),                                                                      \
		   ("iomode_t", "mode") },                                                                       \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ);"),                        \
		("writev", "WUNUSED NONNULL((1, 2))", "size_t", "", "KCALL",                                     \
		 { ("void *__restrict", "self"),                                                                 \
		   ("struct aio_buffer *__restrict", "src"),                                                     \
		   ("size_t", "num_bytes"),                                                                      \
		   ("iomode_t", "mode") },                                                                       \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE);"),                       \
		("preadv", "WUNUSED NONNULL((1, 2))", "size_t", "", "KCALL",                                     \
		 { ("void *__restrict", "self"),                                                                 \
		   ("struct aio_buffer *__restrict", "dst"),                                                     \
		   ("size_t", "num_bytes"),                                                                      \
		   ("pos_t", "addr"),                                                                            \
		   ("iomode_t", "mode") },                                                                       \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ);"),                        \
		("pwritev", "WUNUSED NONNULL((1, 2))", "size_t", "", "KCALL",                                    \
		 { ("void *__restrict", "self"),                                                                 \
		   ("struct aio_buffer *__restrict", "src"),                                                     \
		   ("size_t", "num_bytes"),                                                                      \
		   ("pos_t", "addr"),                                                                            \
		   ("iomode_t", "mode") },                                                                       \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE);"),                       \
		("aread", "WUNUSED NONNULL((1, 5))", "size_t", "", "KCALL",                                      \
		 { ("void *__restrict", "self"),                                                                 \
		   ("USER CHECKED void *", "dst"),                                                               \
		   ("size_t", "num_bytes"),                                                                      \
		   ("iomode_t", "mode"),                                                                         \
		   ("struct aio_multihandle *__restrict", "aio") },                                              \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ);"),                        \
		("awrite", "WUNUSED NONNULL((1, 5))", "size_t", "", "KCALL",                                     \
		 { ("void *__restrict", "self"),                                                                 \
		   ("USER CHECKED void const *", "src"),                                                         \
		   ("size_t", "num_bytes"),                                                                      \
		   ("iomode_t", "mode"),                                                                         \
		   ("struct aio_multihandle *__restrict", "aio") },                                              \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE);"),                       \
		("apread", "WUNUSED NONNULL((1, 6))", "size_t", "", "KCALL",                                     \
		 { ("void *__restrict", "self"),                                                                 \
		   ("USER CHECKED void *", "dst"),                                                               \
		   ("size_t", "num_bytes"),                                                                      \
		   ("pos_t", "addr"),                                                                            \
		   ("iomode_t", "mode"),                                                                         \
		   ("struct aio_multihandle *__restrict", "aio") },                                              \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ);"),                        \
		("apwrite", "WUNUSED NONNULL((1, 6))", "size_t", "", "KCALL",                                    \
		 { ("void *__restrict", "self"),                                                                 \
		   ("USER CHECKED void const *", "src"),                                                         \
		   ("size_t", "num_bytes"),                                                                      \
		   ("pos_t", "addr"),                                                                            \
		   ("iomode_t", "mode"),                                                                         \
		   ("struct aio_multihandle *__restrict", "aio") },                                              \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE);"),                       \
		("areadv", "WUNUSED NONNULL((1, 2, 5))", "size_t", "", "KCALL",                                  \
		 { ("void *__restrict", "self"),                                                                 \
		   ("struct aio_buffer *__restrict", "dst"),                                                     \
		   ("size_t", "num_bytes"),                                                                      \
		   ("iomode_t", "mode"),                                                                         \
		   ("struct aio_multihandle *__restrict", "aio") },                                              \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ);"),                        \
		("awritev", "WUNUSED NONNULL((1, 2, 5))", "size_t", "", "KCALL",                                 \
		 { ("void *__restrict", "self"),                                                                 \
		   ("struct aio_buffer *__restrict", "src"),                                                     \
		   ("size_t", "num_bytes"),                                                                      \
		   ("iomode_t", "mode"),                                                                         \
		   ("struct aio_multihandle *__restrict", "aio") },                                              \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE);"),                       \
		("apreadv", "WUNUSED NONNULL((1, 2, 6))", "size_t", "", "KCALL",                                 \
		 { ("void *__restrict", "self"),                                                                 \
		   ("struct aio_buffer *__restrict", "dst"),                                                     \
		   ("size_t", "num_bytes"),                                                                      \
		   ("pos_t", "addr"),                                                                            \
		   ("iomode_t", "mode"),                                                                         \
		   ("struct aio_multihandle *__restrict", "aio") },                                              \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READ);"),                        \
		("apwritev", "WUNUSED NONNULL((1, 2, 6))", "size_t", "", "KCALL",                                \
		 { ("void *__restrict", "self"),                                                                 \
		   ("struct aio_buffer *__restrict", "src"),                                                     \
		   ("size_t", "num_bytes"),                                                                      \
		   ("pos_t", "addr"),                                                                            \
		   ("iomode_t", "mode"),                                                                         \
		   ("struct aio_multihandle *__restrict", "aio") },                                              \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_WRITE);"),                       \
		("readdir", "WUNUSED NONNULL((1))", "size_t", "", "KCALL",                                       \
		 { ("void *__restrict", "self"),                                                                 \
		   ("USER CHECKED struct dirent *", "buf"),                                                      \
		   ("size_t", "bufsize"),                                                                        \
		   ("readdir_mode_t", "readdir_mode"),                                                           \
		   ("iomode_t", "mode") },                                                                       \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_READDIR);"),                     \
		("seek", "NONNULL((1))", "pos_t", "", "KCALL",                                                   \
		 { ("void *__restrict", "self"),                                                                 \
		   ("off_t", "offset"),                                                                          \
		   ("unsigned int", "whence") },                                                                 \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_SEEK);"),                        \
		("ioctl", "NONNULL((1))", "syscall_slong_t", "", "KCALL",                                        \
		 { ("void *__restrict", "self"),                                                                 \
		   ("syscall_ulong_t", "cmd"),                                                                   \
		   ("USER UNCHECKED void *", "arg"),                                                             \
		   ("iomode_t", "mode") },                                                                       \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND, cmd);"),   \
		("truncate", "NONNULL((1))", "void", "", "KCALL",                                                \
		 { ("void *__restrict", "self"),                                                                 \
		   ("pos_t", "new_size") },                                                                      \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_TRUNC);"),                       \
		("mmap", "WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3))", "REF struct vm_datablock *", "", "KCALL", \
		 { ("void *__restrict", "self"),                                                                 \
		   ("pos_t *__restrict", "pminoffset"),                                                          \
		   ("pos_t *__restrict", "pnumbytes") },                                                         \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_MMAP);"),                        \
		("allocate", "NONNULL((1))", "pos_t", "", "KCALL",                                               \
		 { ("void *__restrict", "self"),                                                                 \
		   ("fallocate_mode_t", "mode"),                                                                 \
		   ("pos_t", "start"),                                                                           \
		   ("pos_t", "length") },                                                                        \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_ALLOCATE);"),                    \
		("sync", "NONNULL((1))", "void", "", "KCALL",                                                    \
		 { ("void *__restrict", "self") },                                                               \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_SYNC);"),                        \
		("datasync", "NONNULL((1))", "void", "", "KCALL",                                                \
		 { ("void *__restrict", "self") },                                                               \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_DATASYNC);"),                    \
		("stat", "NONNULL((1))", "void", "", "KCALL",                                                    \
		 { ("void *__restrict", "self"),                                                                 \
		   ("USER CHECKED struct stat *", "result") },                                                   \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_STAT);"),                        \
		("poll", "WUNUSED NONNULL((1))", "poll_mode_t", "", "KCALL",                                     \
		 { ("void *__restrict", "self"),                                                                 \
		   ("poll_mode_t", "what") },                                                                    \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_FSERROR_UNSUPPORTED_OPERATION, E_FILESYSTEM_OPERATION_POLL);"),                        \
		("hop", "NONNULL((1))", "syscall_slong_t", "", "KCALL",                                          \
		 { ("void *__restrict", "self"),                                                                 \
		   ("syscall_ulong_t", "cmd"),                                                                   \
		   ("USER UNCHECKED void *", "arg"),                                                             \
		   ("iomode_t", "mode") },                                                                       \
		 "THROWS(...)",                                                                                  \
		 "THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND, cmd);"),     \
	}
#endif /* __DEEMON__ */

/* Prototypes for handle operators. */

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
struct vm_datablock;
struct basic_block_device;
struct directory_entry;
struct file;
struct oneshot_directory_file;
struct path;
struct fs;
struct vm;
struct taskpid;
struct wall_clock;
struct driver;
struct pipe;
struct pipe_reader;
struct pipe_writer;
struct pidns;
struct driver_state;
struct character_device;
struct eventfd;
struct signalfd;
struct vm_datapart;
struct vm_futex;
struct vm_futexfd;



/* Handle operators for `HANDLE_TYPE_DATABLOCK' (`struct vm_datablock') */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_datablock_incref)(struct vm_datablock *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_datablock_decref)(struct vm_datablock *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_datablock_refcnt)(struct vm_datablock const *__restrict self);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_datablock_read(struct vm_datablock *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_datablock_write(struct vm_datablock *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_datablock_pread(struct vm_datablock *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_datablock_pwrite(struct vm_datablock *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_datablock_readv(struct vm_datablock *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_datablock_writev(struct vm_datablock *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_datablock_preadv(struct vm_datablock *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_datablock_pwritev(struct vm_datablock *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_datablock_aread(struct vm_datablock *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_datablock_awrite(struct vm_datablock *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_datablock_apread(struct vm_datablock *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_datablock_apwrite(struct vm_datablock *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_datablock_areadv(struct vm_datablock *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_datablock_awritev(struct vm_datablock *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_datablock_apreadv(struct vm_datablock *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_datablock_apwritev(struct vm_datablock *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_datablock_readdir(struct vm_datablock *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_datablock_seek(struct vm_datablock *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_datablock_ioctl(struct vm_datablock *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_datablock_truncate(struct vm_datablock *__restrict self, pos_t new_size) THROWS(...);
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL handle_datablock_mmap(struct vm_datablock *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_datablock_allocate(struct vm_datablock *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_datablock_sync(struct vm_datablock *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_datablock_datasync(struct vm_datablock *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_datablock_stat(struct vm_datablock *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_datablock_poll(struct vm_datablock *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_datablock_hop(struct vm_datablock *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Handle operators for `HANDLE_TYPE_BLOCKDEVICE' (`struct basic_block_device') */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_blockdevice_incref)(struct basic_block_device *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_blockdevice_decref)(struct basic_block_device *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_blockdevice_refcnt)(struct basic_block_device const *__restrict self);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_blockdevice_read(struct basic_block_device *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_blockdevice_write(struct basic_block_device *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_blockdevice_pread(struct basic_block_device *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_blockdevice_pwrite(struct basic_block_device *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_blockdevice_readv(struct basic_block_device *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_blockdevice_writev(struct basic_block_device *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_blockdevice_preadv(struct basic_block_device *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_blockdevice_pwritev(struct basic_block_device *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_blockdevice_aread(struct basic_block_device *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_blockdevice_awrite(struct basic_block_device *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_blockdevice_apread(struct basic_block_device *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_blockdevice_apwrite(struct basic_block_device *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_blockdevice_areadv(struct basic_block_device *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_blockdevice_awritev(struct basic_block_device *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_blockdevice_apreadv(struct basic_block_device *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_blockdevice_apwritev(struct basic_block_device *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_blockdevice_readdir(struct basic_block_device *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_blockdevice_seek(struct basic_block_device *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_blockdevice_ioctl(struct basic_block_device *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_blockdevice_truncate(struct basic_block_device *__restrict self, pos_t new_size) THROWS(...);
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL handle_blockdevice_mmap(struct basic_block_device *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_blockdevice_allocate(struct basic_block_device *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_blockdevice_sync(struct basic_block_device *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_blockdevice_datasync(struct basic_block_device *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_blockdevice_stat(struct basic_block_device *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_blockdevice_poll(struct basic_block_device *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_blockdevice_hop(struct basic_block_device *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Handle operators for `HANDLE_TYPE_DIRECTORYENTRY' (`struct directory_entry') */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_directoryentry_incref)(struct directory_entry *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_directoryentry_decref)(struct directory_entry *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_directoryentry_refcnt)(struct directory_entry const *__restrict self);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_directoryentry_read(struct directory_entry *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_directoryentry_write(struct directory_entry *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_directoryentry_pread(struct directory_entry *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_directoryentry_pwrite(struct directory_entry *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_directoryentry_readv(struct directory_entry *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_directoryentry_writev(struct directory_entry *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_directoryentry_preadv(struct directory_entry *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_directoryentry_pwritev(struct directory_entry *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_directoryentry_aread(struct directory_entry *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_directoryentry_awrite(struct directory_entry *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_directoryentry_apread(struct directory_entry *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_directoryentry_apwrite(struct directory_entry *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_directoryentry_areadv(struct directory_entry *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_directoryentry_awritev(struct directory_entry *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_directoryentry_apreadv(struct directory_entry *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_directoryentry_apwritev(struct directory_entry *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_directoryentry_readdir(struct directory_entry *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_directoryentry_seek(struct directory_entry *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_directoryentry_ioctl(struct directory_entry *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_directoryentry_truncate(struct directory_entry *__restrict self, pos_t new_size) THROWS(...);
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL handle_directoryentry_mmap(struct directory_entry *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_directoryentry_allocate(struct directory_entry *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_directoryentry_sync(struct directory_entry *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_directoryentry_datasync(struct directory_entry *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_directoryentry_stat(struct directory_entry *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_directoryentry_poll(struct directory_entry *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_directoryentry_hop(struct directory_entry *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Handle operators for `HANDLE_TYPE_FILE' (`struct file') */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_file_incref)(struct file *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_file_decref)(struct file *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_file_refcnt)(struct file const *__restrict self);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_file_read(struct file *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_file_write(struct file *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_file_pread(struct file *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_file_pwrite(struct file *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_file_readv(struct file *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_file_writev(struct file *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_file_preadv(struct file *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_file_pwritev(struct file *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_file_aread(struct file *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_file_awrite(struct file *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_file_apread(struct file *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_file_apwrite(struct file *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_file_areadv(struct file *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_file_awritev(struct file *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_file_apreadv(struct file *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_file_apwritev(struct file *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_file_readdir(struct file *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_file_seek(struct file *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_file_ioctl(struct file *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_file_truncate(struct file *__restrict self, pos_t new_size) THROWS(...);
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL handle_file_mmap(struct file *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_file_allocate(struct file *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_file_sync(struct file *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_file_datasync(struct file *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_file_stat(struct file *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_file_poll(struct file *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_file_hop(struct file *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Handle operators for `HANDLE_TYPE_ONESHOT_DIRECTORY_FILE' (`struct oneshot_directory_file') */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_oneshot_directory_file_incref)(struct oneshot_directory_file *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_oneshot_directory_file_decref)(struct oneshot_directory_file *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_oneshot_directory_file_refcnt)(struct oneshot_directory_file const *__restrict self);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_oneshot_directory_file_read(struct oneshot_directory_file *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_oneshot_directory_file_write(struct oneshot_directory_file *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_oneshot_directory_file_pread(struct oneshot_directory_file *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_oneshot_directory_file_pwrite(struct oneshot_directory_file *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_oneshot_directory_file_readv(struct oneshot_directory_file *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_oneshot_directory_file_writev(struct oneshot_directory_file *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_oneshot_directory_file_preadv(struct oneshot_directory_file *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_oneshot_directory_file_pwritev(struct oneshot_directory_file *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_oneshot_directory_file_aread(struct oneshot_directory_file *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_oneshot_directory_file_awrite(struct oneshot_directory_file *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_oneshot_directory_file_apread(struct oneshot_directory_file *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_oneshot_directory_file_apwrite(struct oneshot_directory_file *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_oneshot_directory_file_areadv(struct oneshot_directory_file *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_oneshot_directory_file_awritev(struct oneshot_directory_file *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_oneshot_directory_file_apreadv(struct oneshot_directory_file *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_oneshot_directory_file_apwritev(struct oneshot_directory_file *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_oneshot_directory_file_readdir(struct oneshot_directory_file *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_oneshot_directory_file_seek(struct oneshot_directory_file *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_oneshot_directory_file_ioctl(struct oneshot_directory_file *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_oneshot_directory_file_truncate(struct oneshot_directory_file *__restrict self, pos_t new_size) THROWS(...);
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL handle_oneshot_directory_file_mmap(struct oneshot_directory_file *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_oneshot_directory_file_allocate(struct oneshot_directory_file *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_oneshot_directory_file_sync(struct oneshot_directory_file *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_oneshot_directory_file_datasync(struct oneshot_directory_file *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_oneshot_directory_file_stat(struct oneshot_directory_file *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_oneshot_directory_file_poll(struct oneshot_directory_file *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_oneshot_directory_file_hop(struct oneshot_directory_file *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Handle operators for `HANDLE_TYPE_PATH' (`struct path') */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_path_incref)(struct path *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_path_decref)(struct path *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_path_refcnt)(struct path const *__restrict self);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_path_read(struct path *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_path_write(struct path *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_path_pread(struct path *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_path_pwrite(struct path *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_path_readv(struct path *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_path_writev(struct path *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_path_preadv(struct path *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_path_pwritev(struct path *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_path_aread(struct path *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_path_awrite(struct path *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_path_apread(struct path *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_path_apwrite(struct path *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_path_areadv(struct path *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_path_awritev(struct path *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_path_apreadv(struct path *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_path_apwritev(struct path *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_path_readdir(struct path *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_path_seek(struct path *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_path_ioctl(struct path *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_path_truncate(struct path *__restrict self, pos_t new_size) THROWS(...);
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL handle_path_mmap(struct path *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_path_allocate(struct path *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_path_sync(struct path *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_path_datasync(struct path *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_path_stat(struct path *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_path_poll(struct path *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_path_hop(struct path *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Handle operators for `HANDLE_TYPE_FS' (`struct fs') */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_fs_incref)(struct fs *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_fs_decref)(struct fs *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_fs_refcnt)(struct fs const *__restrict self);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_fs_read(struct fs *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_fs_write(struct fs *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_fs_pread(struct fs *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_fs_pwrite(struct fs *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_fs_readv(struct fs *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_fs_writev(struct fs *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_fs_preadv(struct fs *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_fs_pwritev(struct fs *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_fs_aread(struct fs *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_fs_awrite(struct fs *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_fs_apread(struct fs *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_fs_apwrite(struct fs *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_fs_areadv(struct fs *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_fs_awritev(struct fs *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_fs_apreadv(struct fs *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_fs_apwritev(struct fs *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_fs_readdir(struct fs *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_fs_seek(struct fs *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_fs_ioctl(struct fs *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_fs_truncate(struct fs *__restrict self, pos_t new_size) THROWS(...);
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL handle_fs_mmap(struct fs *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_fs_allocate(struct fs *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_fs_sync(struct fs *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_fs_datasync(struct fs *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_fs_stat(struct fs *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_fs_poll(struct fs *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_fs_hop(struct fs *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Handle operators for `HANDLE_TYPE_VM' (`struct vm') */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_vm_incref)(struct vm *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_vm_decref)(struct vm *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_vm_refcnt)(struct vm const *__restrict self);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_vm_read(struct vm *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_vm_write(struct vm *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_vm_pread(struct vm *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_vm_pwrite(struct vm *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_vm_readv(struct vm *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_vm_writev(struct vm *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_vm_preadv(struct vm *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_vm_pwritev(struct vm *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_vm_aread(struct vm *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_vm_awrite(struct vm *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_vm_apread(struct vm *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_vm_apwrite(struct vm *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_vm_areadv(struct vm *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_vm_awritev(struct vm *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_vm_apreadv(struct vm *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_vm_apwritev(struct vm *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_vm_readdir(struct vm *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_vm_seek(struct vm *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_vm_ioctl(struct vm *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_vm_truncate(struct vm *__restrict self, pos_t new_size) THROWS(...);
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL handle_vm_mmap(struct vm *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_vm_allocate(struct vm *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_vm_sync(struct vm *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_vm_datasync(struct vm *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_vm_stat(struct vm *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_vm_poll(struct vm *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_vm_hop(struct vm *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Handle operators for `HANDLE_TYPE_TASK' (`struct taskpid') */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_task_incref)(struct taskpid *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_task_decref)(struct taskpid *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_task_refcnt)(struct taskpid const *__restrict self);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_task_read(struct taskpid *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_task_write(struct taskpid *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_task_pread(struct taskpid *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_task_pwrite(struct taskpid *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_task_readv(struct taskpid *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_task_writev(struct taskpid *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_task_preadv(struct taskpid *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_task_pwritev(struct taskpid *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_task_aread(struct taskpid *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_task_awrite(struct taskpid *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_task_apread(struct taskpid *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_task_apwrite(struct taskpid *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_task_areadv(struct taskpid *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_task_awritev(struct taskpid *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_task_apreadv(struct taskpid *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_task_apwritev(struct taskpid *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_task_readdir(struct taskpid *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_task_seek(struct taskpid *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_task_ioctl(struct taskpid *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_task_truncate(struct taskpid *__restrict self, pos_t new_size) THROWS(...);
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL handle_task_mmap(struct taskpid *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_task_allocate(struct taskpid *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_task_sync(struct taskpid *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_task_datasync(struct taskpid *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_task_stat(struct taskpid *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_task_poll(struct taskpid *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_task_hop(struct taskpid *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Handle operators for `HANDLE_TYPE_CLOCK' (`struct wall_clock') */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_clock_incref)(struct wall_clock *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_clock_decref)(struct wall_clock *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_clock_refcnt)(struct wall_clock const *__restrict self);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_clock_read(struct wall_clock *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_clock_write(struct wall_clock *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_clock_pread(struct wall_clock *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_clock_pwrite(struct wall_clock *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_clock_readv(struct wall_clock *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_clock_writev(struct wall_clock *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_clock_preadv(struct wall_clock *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_clock_pwritev(struct wall_clock *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_clock_aread(struct wall_clock *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_clock_awrite(struct wall_clock *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_clock_apread(struct wall_clock *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_clock_apwrite(struct wall_clock *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_clock_areadv(struct wall_clock *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_clock_awritev(struct wall_clock *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_clock_apreadv(struct wall_clock *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_clock_apwritev(struct wall_clock *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_clock_readdir(struct wall_clock *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_clock_seek(struct wall_clock *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_clock_ioctl(struct wall_clock *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_clock_truncate(struct wall_clock *__restrict self, pos_t new_size) THROWS(...);
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL handle_clock_mmap(struct wall_clock *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_clock_allocate(struct wall_clock *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_clock_sync(struct wall_clock *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_clock_datasync(struct wall_clock *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_clock_stat(struct wall_clock *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_clock_poll(struct wall_clock *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_clock_hop(struct wall_clock *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Handle operators for `HANDLE_TYPE_DRIVER' (`struct driver') */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_driver_incref)(struct driver *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_driver_decref)(struct driver *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_driver_refcnt)(struct driver const *__restrict self);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_read(struct driver *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_write(struct driver *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_pread(struct driver *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_pwrite(struct driver *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_readv(struct driver *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_writev(struct driver *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_preadv(struct driver *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_pwritev(struct driver *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_driver_aread(struct driver *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_driver_awrite(struct driver *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_driver_apread(struct driver *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_driver_apwrite(struct driver *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_driver_areadv(struct driver *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_driver_awritev(struct driver *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_driver_apreadv(struct driver *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_driver_apwritev(struct driver *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_readdir(struct driver *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_driver_seek(struct driver *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_driver_ioctl(struct driver *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_truncate(struct driver *__restrict self, pos_t new_size) THROWS(...);
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL handle_driver_mmap(struct driver *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_driver_allocate(struct driver *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_sync(struct driver *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_datasync(struct driver *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_stat(struct driver *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_driver_poll(struct driver *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_driver_hop(struct driver *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Handle operators for `HANDLE_TYPE_PIPE' (`struct pipe') */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_incref)(struct pipe *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_decref)(struct pipe *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_pipe_refcnt)(struct pipe const *__restrict self);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_read(struct pipe *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_write(struct pipe *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_pread(struct pipe *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_pwrite(struct pipe *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_readv(struct pipe *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_writev(struct pipe *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_preadv(struct pipe *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_pwritev(struct pipe *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_pipe_aread(struct pipe *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_pipe_awrite(struct pipe *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_pipe_apread(struct pipe *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_pipe_apwrite(struct pipe *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_pipe_areadv(struct pipe *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_pipe_awritev(struct pipe *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_pipe_apreadv(struct pipe *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_pipe_apwritev(struct pipe *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_readdir(struct pipe *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_pipe_seek(struct pipe *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_pipe_ioctl(struct pipe *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_truncate(struct pipe *__restrict self, pos_t new_size) THROWS(...);
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL handle_pipe_mmap(struct pipe *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_pipe_allocate(struct pipe *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_sync(struct pipe *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_datasync(struct pipe *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_stat(struct pipe *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_pipe_poll(struct pipe *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_pipe_hop(struct pipe *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Handle operators for `HANDLE_TYPE_PIPE_READER' (`struct pipe_reader') */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_reader_incref)(struct pipe_reader *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_reader_decref)(struct pipe_reader *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_pipe_reader_refcnt)(struct pipe_reader const *__restrict self);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_reader_read(struct pipe_reader *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_reader_write(struct pipe_reader *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_reader_pread(struct pipe_reader *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_reader_pwrite(struct pipe_reader *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_reader_readv(struct pipe_reader *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_reader_writev(struct pipe_reader *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_reader_preadv(struct pipe_reader *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_reader_pwritev(struct pipe_reader *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_pipe_reader_aread(struct pipe_reader *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_pipe_reader_awrite(struct pipe_reader *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_pipe_reader_apread(struct pipe_reader *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_pipe_reader_apwrite(struct pipe_reader *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_pipe_reader_areadv(struct pipe_reader *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_pipe_reader_awritev(struct pipe_reader *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_pipe_reader_apreadv(struct pipe_reader *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_pipe_reader_apwritev(struct pipe_reader *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_reader_readdir(struct pipe_reader *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_pipe_reader_seek(struct pipe_reader *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_pipe_reader_ioctl(struct pipe_reader *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_reader_truncate(struct pipe_reader *__restrict self, pos_t new_size) THROWS(...);
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL handle_pipe_reader_mmap(struct pipe_reader *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_pipe_reader_allocate(struct pipe_reader *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_reader_sync(struct pipe_reader *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_reader_datasync(struct pipe_reader *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_reader_stat(struct pipe_reader *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_pipe_reader_poll(struct pipe_reader *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_pipe_reader_hop(struct pipe_reader *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Handle operators for `HANDLE_TYPE_PIPE_WRITER' (`struct pipe_writer') */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_writer_incref)(struct pipe_writer *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pipe_writer_decref)(struct pipe_writer *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_pipe_writer_refcnt)(struct pipe_writer const *__restrict self);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_writer_read(struct pipe_writer *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_writer_write(struct pipe_writer *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_writer_pread(struct pipe_writer *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_writer_pwrite(struct pipe_writer *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_writer_readv(struct pipe_writer *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_writer_writev(struct pipe_writer *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_writer_preadv(struct pipe_writer *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pipe_writer_pwritev(struct pipe_writer *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_pipe_writer_aread(struct pipe_writer *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_pipe_writer_awrite(struct pipe_writer *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_pipe_writer_apread(struct pipe_writer *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_pipe_writer_apwrite(struct pipe_writer *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_pipe_writer_areadv(struct pipe_writer *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_pipe_writer_awritev(struct pipe_writer *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_pipe_writer_apreadv(struct pipe_writer *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_pipe_writer_apwritev(struct pipe_writer *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pipe_writer_readdir(struct pipe_writer *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_pipe_writer_seek(struct pipe_writer *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_pipe_writer_ioctl(struct pipe_writer *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_writer_truncate(struct pipe_writer *__restrict self, pos_t new_size) THROWS(...);
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL handle_pipe_writer_mmap(struct pipe_writer *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_pipe_writer_allocate(struct pipe_writer *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_writer_sync(struct pipe_writer *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_writer_datasync(struct pipe_writer *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pipe_writer_stat(struct pipe_writer *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_pipe_writer_poll(struct pipe_writer *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_pipe_writer_hop(struct pipe_writer *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Handle operators for `HANDLE_TYPE_PIDNS' (`struct pidns') */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pidns_incref)(struct pidns *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_pidns_decref)(struct pidns *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_pidns_refcnt)(struct pidns const *__restrict self);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pidns_read(struct pidns *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pidns_write(struct pidns *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pidns_pread(struct pidns *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pidns_pwrite(struct pidns *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pidns_readv(struct pidns *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pidns_writev(struct pidns *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pidns_preadv(struct pidns *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_pidns_pwritev(struct pidns *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_pidns_aread(struct pidns *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_pidns_awrite(struct pidns *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_pidns_apread(struct pidns *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_pidns_apwrite(struct pidns *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_pidns_areadv(struct pidns *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_pidns_awritev(struct pidns *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_pidns_apreadv(struct pidns *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_pidns_apwritev(struct pidns *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_pidns_readdir(struct pidns *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_pidns_seek(struct pidns *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_pidns_ioctl(struct pidns *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pidns_truncate(struct pidns *__restrict self, pos_t new_size) THROWS(...);
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL handle_pidns_mmap(struct pidns *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_pidns_allocate(struct pidns *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pidns_sync(struct pidns *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pidns_datasync(struct pidns *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_pidns_stat(struct pidns *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_pidns_poll(struct pidns *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_pidns_hop(struct pidns *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Handle operators for `HANDLE_TYPE_DRIVER_STATE' (`struct driver_state') */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_driver_state_incref)(struct driver_state *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_driver_state_decref)(struct driver_state *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_driver_state_refcnt)(struct driver_state const *__restrict self);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_state_read(struct driver_state *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_state_write(struct driver_state *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_state_pread(struct driver_state *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_state_pwrite(struct driver_state *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_state_readv(struct driver_state *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_state_writev(struct driver_state *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_state_preadv(struct driver_state *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_state_pwritev(struct driver_state *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_driver_state_aread(struct driver_state *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_driver_state_awrite(struct driver_state *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_driver_state_apread(struct driver_state *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_driver_state_apwrite(struct driver_state *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_driver_state_areadv(struct driver_state *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_driver_state_awritev(struct driver_state *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_driver_state_apreadv(struct driver_state *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_driver_state_apwritev(struct driver_state *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_state_readdir(struct driver_state *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_driver_state_seek(struct driver_state *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_driver_state_ioctl(struct driver_state *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_state_truncate(struct driver_state *__restrict self, pos_t new_size) THROWS(...);
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL handle_driver_state_mmap(struct driver_state *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_driver_state_allocate(struct driver_state *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_state_sync(struct driver_state *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_state_datasync(struct driver_state *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_state_stat(struct driver_state *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_driver_state_poll(struct driver_state *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_driver_state_hop(struct driver_state *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Handle operators for `HANDLE_TYPE_CHARACTERDEVICE' (`struct character_device') */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_characterdevice_incref)(struct character_device *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_characterdevice_decref)(struct character_device *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_characterdevice_refcnt)(struct character_device const *__restrict self);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_characterdevice_read(struct character_device *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_characterdevice_write(struct character_device *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_characterdevice_pread(struct character_device *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_characterdevice_pwrite(struct character_device *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_characterdevice_readv(struct character_device *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_characterdevice_writev(struct character_device *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_characterdevice_preadv(struct character_device *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_characterdevice_pwritev(struct character_device *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_characterdevice_aread(struct character_device *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_characterdevice_awrite(struct character_device *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_characterdevice_apread(struct character_device *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_characterdevice_apwrite(struct character_device *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_characterdevice_areadv(struct character_device *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_characterdevice_awritev(struct character_device *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_characterdevice_apreadv(struct character_device *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_characterdevice_apwritev(struct character_device *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_characterdevice_readdir(struct character_device *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_characterdevice_seek(struct character_device *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_characterdevice_ioctl(struct character_device *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_characterdevice_truncate(struct character_device *__restrict self, pos_t new_size) THROWS(...);
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL handle_characterdevice_mmap(struct character_device *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_characterdevice_allocate(struct character_device *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_characterdevice_sync(struct character_device *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_characterdevice_datasync(struct character_device *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_characterdevice_stat(struct character_device *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_characterdevice_poll(struct character_device *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_characterdevice_hop(struct character_device *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Handle operators for `HANDLE_TYPE_EVENTFD_FENCE' (`struct eventfd') */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_eventfd_fence_incref)(struct eventfd *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_eventfd_fence_decref)(struct eventfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_eventfd_fence_refcnt)(struct eventfd const *__restrict self);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_fence_read(struct eventfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_fence_write(struct eventfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_fence_pread(struct eventfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_fence_pwrite(struct eventfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_fence_readv(struct eventfd *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_fence_writev(struct eventfd *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_fence_preadv(struct eventfd *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_fence_pwritev(struct eventfd *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_eventfd_fence_aread(struct eventfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_eventfd_fence_awrite(struct eventfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_eventfd_fence_apread(struct eventfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_eventfd_fence_apwrite(struct eventfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_eventfd_fence_areadv(struct eventfd *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_eventfd_fence_awritev(struct eventfd *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_eventfd_fence_apreadv(struct eventfd *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_eventfd_fence_apwritev(struct eventfd *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_fence_readdir(struct eventfd *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_eventfd_fence_seek(struct eventfd *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_eventfd_fence_ioctl(struct eventfd *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_fence_truncate(struct eventfd *__restrict self, pos_t new_size) THROWS(...);
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL handle_eventfd_fence_mmap(struct eventfd *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_eventfd_fence_allocate(struct eventfd *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_fence_sync(struct eventfd *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_fence_datasync(struct eventfd *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_fence_stat(struct eventfd *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_eventfd_fence_poll(struct eventfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_eventfd_fence_hop(struct eventfd *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Handle operators for `HANDLE_TYPE_EVENTFD_SEMA' (`struct eventfd') */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_eventfd_sema_incref)(struct eventfd *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_eventfd_sema_decref)(struct eventfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_eventfd_sema_refcnt)(struct eventfd const *__restrict self);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_sema_read(struct eventfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_sema_write(struct eventfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_sema_pread(struct eventfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_sema_pwrite(struct eventfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_sema_readv(struct eventfd *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_sema_writev(struct eventfd *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_sema_preadv(struct eventfd *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_eventfd_sema_pwritev(struct eventfd *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_eventfd_sema_aread(struct eventfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_eventfd_sema_awrite(struct eventfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_eventfd_sema_apread(struct eventfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_eventfd_sema_apwrite(struct eventfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_eventfd_sema_areadv(struct eventfd *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_eventfd_sema_awritev(struct eventfd *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_eventfd_sema_apreadv(struct eventfd *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_eventfd_sema_apwritev(struct eventfd *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_eventfd_sema_readdir(struct eventfd *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_eventfd_sema_seek(struct eventfd *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_eventfd_sema_ioctl(struct eventfd *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_sema_truncate(struct eventfd *__restrict self, pos_t new_size) THROWS(...);
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL handle_eventfd_sema_mmap(struct eventfd *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_eventfd_sema_allocate(struct eventfd *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_sema_sync(struct eventfd *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_sema_datasync(struct eventfd *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_eventfd_sema_stat(struct eventfd *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_eventfd_sema_poll(struct eventfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_eventfd_sema_hop(struct eventfd *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Handle operators for `HANDLE_TYPE_SIGNALFD' (`struct signalfd') */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_signalfd_incref)(struct signalfd *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_signalfd_decref)(struct signalfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_signalfd_refcnt)(struct signalfd const *__restrict self);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_signalfd_read(struct signalfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_signalfd_write(struct signalfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_signalfd_pread(struct signalfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_signalfd_pwrite(struct signalfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_signalfd_readv(struct signalfd *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_signalfd_writev(struct signalfd *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_signalfd_preadv(struct signalfd *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_signalfd_pwritev(struct signalfd *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_signalfd_aread(struct signalfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_signalfd_awrite(struct signalfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_signalfd_apread(struct signalfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_signalfd_apwrite(struct signalfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_signalfd_areadv(struct signalfd *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_signalfd_awritev(struct signalfd *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_signalfd_apreadv(struct signalfd *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_signalfd_apwritev(struct signalfd *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_signalfd_readdir(struct signalfd *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_signalfd_seek(struct signalfd *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_signalfd_ioctl(struct signalfd *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_signalfd_truncate(struct signalfd *__restrict self, pos_t new_size) THROWS(...);
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL handle_signalfd_mmap(struct signalfd *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_signalfd_allocate(struct signalfd *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_signalfd_sync(struct signalfd *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_signalfd_datasync(struct signalfd *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_signalfd_stat(struct signalfd *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_signalfd_poll(struct signalfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_signalfd_hop(struct signalfd *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Handle operators for `HANDLE_TYPE_DATAPART' (`struct vm_datapart') */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_datapart_incref)(struct vm_datapart *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_datapart_decref)(struct vm_datapart *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_datapart_refcnt)(struct vm_datapart const *__restrict self);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_datapart_read(struct vm_datapart *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_datapart_write(struct vm_datapart *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_datapart_pread(struct vm_datapart *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_datapart_pwrite(struct vm_datapart *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_datapart_readv(struct vm_datapart *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_datapart_writev(struct vm_datapart *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_datapart_preadv(struct vm_datapart *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_datapart_pwritev(struct vm_datapart *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_datapart_aread(struct vm_datapart *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_datapart_awrite(struct vm_datapart *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_datapart_apread(struct vm_datapart *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_datapart_apwrite(struct vm_datapart *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_datapart_areadv(struct vm_datapart *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_datapart_awritev(struct vm_datapart *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_datapart_apreadv(struct vm_datapart *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_datapart_apwritev(struct vm_datapart *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_datapart_readdir(struct vm_datapart *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_datapart_seek(struct vm_datapart *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_datapart_ioctl(struct vm_datapart *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_datapart_truncate(struct vm_datapart *__restrict self, pos_t new_size) THROWS(...);
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL handle_datapart_mmap(struct vm_datapart *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_datapart_allocate(struct vm_datapart *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_datapart_sync(struct vm_datapart *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_datapart_datasync(struct vm_datapart *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_datapart_stat(struct vm_datapart *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_datapart_poll(struct vm_datapart *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_datapart_hop(struct vm_datapart *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Handle operators for `HANDLE_TYPE_FUTEX' (`struct vm_futex') */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_futex_incref)(struct vm_futex *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_futex_decref)(struct vm_futex *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_futex_refcnt)(struct vm_futex const *__restrict self);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futex_read(struct vm_futex *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futex_write(struct vm_futex *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futex_pread(struct vm_futex *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futex_pwrite(struct vm_futex *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_futex_readv(struct vm_futex *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_futex_writev(struct vm_futex *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_futex_preadv(struct vm_futex *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_futex_pwritev(struct vm_futex *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_futex_aread(struct vm_futex *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_futex_awrite(struct vm_futex *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_futex_apread(struct vm_futex *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_futex_apwrite(struct vm_futex *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_futex_areadv(struct vm_futex *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_futex_awritev(struct vm_futex *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_futex_apreadv(struct vm_futex *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_futex_apwritev(struct vm_futex *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futex_readdir(struct vm_futex *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_futex_seek(struct vm_futex *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_futex_ioctl(struct vm_futex *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futex_truncate(struct vm_futex *__restrict self, pos_t new_size) THROWS(...);
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL handle_futex_mmap(struct vm_futex *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_futex_allocate(struct vm_futex *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futex_sync(struct vm_futex *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futex_datasync(struct vm_futex *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futex_stat(struct vm_futex *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_futex_poll(struct vm_futex *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_futex_hop(struct vm_futex *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Handle operators for `HANDLE_TYPE_FUTEXFD' (`struct vm_futexfd') */
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_futexfd_incref)(struct vm_futexfd *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_futexfd_decref)(struct vm_futexfd *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_futexfd_refcnt)(struct vm_futexfd const *__restrict self);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futexfd_read(struct vm_futexfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futexfd_write(struct vm_futexfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futexfd_pread(struct vm_futexfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futexfd_pwrite(struct vm_futexfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_futexfd_readv(struct vm_futexfd *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_futexfd_writev(struct vm_futexfd *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_futexfd_preadv(struct vm_futexfd *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_futexfd_pwritev(struct vm_futexfd *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_futexfd_aread(struct vm_futexfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 5)) size_t KCALL handle_futexfd_awrite(struct vm_futexfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_futexfd_apread(struct vm_futexfd *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 6)) size_t KCALL handle_futexfd_apwrite(struct vm_futexfd *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_futexfd_areadv(struct vm_futexfd *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 5)) size_t KCALL handle_futexfd_awritev(struct vm_futexfd *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_futexfd_apreadv(struct vm_futexfd *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2, 6)) size_t KCALL handle_futexfd_apwritev(struct vm_futexfd *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode, struct aio_multihandle *__restrict aio) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_futexfd_readdir(struct vm_futexfd *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_futexfd_seek(struct vm_futexfd *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_futexfd_ioctl(struct vm_futexfd *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futexfd_truncate(struct vm_futexfd *__restrict self, pos_t new_size) THROWS(...);
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL handle_futexfd_mmap(struct vm_futexfd *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_futexfd_allocate(struct vm_futexfd *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futexfd_sync(struct vm_futexfd *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futexfd_datasync(struct vm_futexfd *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_futexfd_stat(struct vm_futexfd *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_futexfd_poll(struct vm_futexfd *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_futexfd_hop(struct vm_futexfd *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

#endif /* __CC__ */
#endif /* CONFIG_BUILDING_KERNEL_CORE */
//[[[end]]]

#ifdef CONFIG_BUILDING_KERNEL_CORE
#ifdef __CC__





/* `name' must be the lower-case form of the `*' in one of the `HANDLE_TYPE_*' macros.
 * `T' must be the actual object type (one implementing the refcnt protocol or deriving from another that does) */
#define DEFINE_HANDLE_REFCNT_FUNCTIONS(name, T)                       \
	INTERN NOBLOCK WUNUSED NONNULL((1)) refcnt_t                      \
	NOTHROW(FCALL handle_##name##_refcnt)(T const *__restrict self) { \
		return getrefcnt(self);                                       \
	}                                                                 \
	INTERN NOBLOCK NONNULL((1)) void                                  \
	NOTHROW(FCALL handle_##name##_incref)(T *__restrict self) {       \
		incref(self);                                                 \
	}                                                                 \
	INTERN NOBLOCK NONNULL((1)) void                                  \
	NOTHROW(FCALL handle_##name##_decref)(REF T *__restrict self) {   \
		decref(self);                                                 \
	}

/* Handle operator implementation helpers. */
#define DEFINE_HANDLE_READV_FROM_READ(name, T)                                 \
	INTERN WUNUSED NONNULL((1, 2)) size_t KCALL                                \
	handle_##name##_readv(T *__restrict self,                                  \
	                      struct aio_buffer *__restrict dst,                   \
	                      size_t num_bytes, iomode_t mode) THROWS(...) {       \
		size_t temp, result = 0;                                               \
		struct aio_buffer_entry ent;                                           \
		assert(aio_buffer_size(dst) == num_bytes);                             \
		(void)num_bytes;                                                       \
		AIO_BUFFER_FOREACH(ent, dst) {                                         \
			temp = handle_##name##_read(self, ent.ab_base, ent.ab_size, mode); \
			result += temp;                                                    \
			if (temp != ent.ab_size)                                           \
				break;                                                         \
		}                                                                      \
		return result;                                                         \
	}
#define DEFINE_HANDLE_WRITEV_FROM_WRITE(name, T)                                \
	INTERN WUNUSED NONNULL((1, 2)) size_t KCALL                                 \
	handle_##name##_writev(T *__restrict self,                                  \
	                       struct aio_buffer *__restrict src,                   \
	                       size_t num_bytes, iomode_t mode) THROWS(...) {       \
		size_t temp, result = 0;                                                \
		struct aio_buffer_entry ent;                                            \
		assert(aio_buffer_size(src) == num_bytes);                              \
		(void)num_bytes;                                                        \
		AIO_BUFFER_FOREACH(ent, src) {                                          \
			temp = handle_##name##_write(self, ent.ab_base, ent.ab_size, mode); \
			result += temp;                                                     \
			if (temp != ent.ab_size)                                            \
				break;                                                          \
		}                                                                       \
		return result;                                                          \
	}

#define DEFINE_HANDLE_PREADV_FROM_PREAD(name, T)                   \
	INTERN WUNUSED NONNULL((1, 2)) size_t KCALL                    \
	handle_##name##_preadv(T *__restrict self,                     \
	                       struct aio_buffer *__restrict dst,      \
	                       size_t num_bytes, pos_t addr,           \
	                       iomode_t mode) THROWS(...) {            \
		size_t temp, result = 0;                                   \
		struct aio_buffer_entry ent;                               \
		assert(aio_buffer_size(dst) == num_bytes);                 \
		(void)num_bytes;                                           \
		AIO_BUFFER_FOREACH(ent, dst) {                             \
			temp = handle_##name##_pread(self, ent.ab_base,        \
			                             ent.ab_size, addr, mode); \
			result += temp;                                        \
			if (temp != ent.ab_size)                               \
				break;                                             \
			addr += temp;                                          \
		}                                                          \
		return result;                                             \
	}
#define DEFINE_HANDLE_PWRITEV_FROM_PWRITE(name, T)                  \
	INTERN WUNUSED NONNULL((1, 2)) size_t KCALL                     \
	handle_##name##_pwritev(T *__restrict self,                     \
	                        struct aio_buffer *__restrict src,      \
	                        size_t num_bytes, pos_t addr,           \
	                        iomode_t mode) THROWS(...) {            \
		size_t temp, result = 0;                                    \
		struct aio_buffer_entry ent;                                \
		assert(aio_buffer_size(src) == num_bytes);                  \
		(void)num_bytes;                                            \
		AIO_BUFFER_FOREACH(ent, src) {                              \
			temp = handle_##name##_pwrite(self, ent.ab_base,        \
			                              ent.ab_size, addr, mode); \
			result += temp;                                         \
			if (temp != ent.ab_size)                                \
				break;                                              \
			addr += temp;                                           \
		}                                                           \
		return result;                                              \
	}

#define DEFINE_HANDLE_AREAD_FROM_READ(name, T)                              \
	INTERN WUNUSED NONNULL((1, 5)) size_t KCALL                             \
	handle_##name##_aread(T *__restrict self, USER CHECKED void *dst,       \
	                      size_t num_bytes, iomode_t mode,                  \
	                      struct aio_multihandle *__restrict UNUSED(aio)) { \
		size_t result;                                                      \
		result = handle_##name##_read(self, dst, num_bytes, mode);          \
		return result;                                                      \
	}

#define DEFINE_HANDLE_AWRITE_FROM_WRITE(name, T)                             \
	INTERN WUNUSED NONNULL((1, 5)) size_t KCALL                              \
	handle_##name##_awrite(T *__restrict self, USER CHECKED void const *src, \
	                       size_t num_bytes, iomode_t mode,                  \
	                       struct aio_multihandle *__restrict UNUSED(aio)) { \
		size_t result;                                                       \
		result = handle_##name##_write(self, src, num_bytes, mode);          \
		return result;                                                       \
	}

#define DEFINE_HANDLE_AREADV_FROM_READV(name, T)                                  \
	INTERN WUNUSED NONNULL((1, 2, 5)) size_t KCALL                                \
	handle_##name##_areadv(T *__restrict self, struct aio_buffer *__restrict dst, \
	                       size_t num_bytes, iomode_t mode,                       \
	                       struct aio_multihandle *__restrict UNUSED(aio)) {      \
		size_t result;                                                            \
		result = handle_##name##_readv(self, dst, num_bytes, mode);               \
		return result;                                                            \
	}

#define DEFINE_HANDLE_AWRITEV_FROM_WRITEV(name, T)                                 \
	INTERN WUNUSED NONNULL((1, 2, 5)) size_t KCALL                                 \
	handle_##name##_awritev(T *__restrict self, struct aio_buffer *__restrict src, \
	                        size_t num_bytes, iomode_t mode,                       \
	                        struct aio_multihandle *__restrict UNUSED(aio)) {      \
		size_t result;                                                             \
		result = handle_##name##_writev(self, src, num_bytes, mode);               \
		return result;                                                             \
	}

#define DEFINE_HANDLE_APREAD_FROM_PREAD(name, T)                             \
	INTERN WUNUSED NONNULL((1, 6)) size_t KCALL                              \
	handle_##name##_apread(T *__restrict self, USER CHECKED void *dst,       \
	                       size_t num_bytes, pos_t addr, iomode_t mode,      \
	                       struct aio_multihandle *__restrict UNUSED(aio)) { \
		size_t result;                                                       \
		result = handle_##name##_pread(self, dst, num_bytes, addr, mode);    \
		return result;                                                       \
	}

#define DEFINE_HANDLE_APWRITE_FROM_PWRITE(name, T)                            \
	INTERN WUNUSED NONNULL((1, 6)) size_t KCALL                               \
	handle_##name##_apwrite(T *__restrict self, USER CHECKED void const *src, \
	                        size_t num_bytes, pos_t addr, iomode_t mode,      \
	                        struct aio_multihandle *__restrict UNUSED(aio)) { \
		size_t result;                                                        \
		result = handle_##name##_pwrite(self, src, num_bytes, addr, mode);    \
		return result;                                                        \
	}

#define DEFINE_HANDLE_APREADV_FROM_PREADV(name, T)                                 \
	INTERN WUNUSED NONNULL((1, 2, 6)) size_t KCALL                                 \
	handle_##name##_apreadv(T *__restrict self, struct aio_buffer *__restrict dst, \
	                        size_t num_bytes, pos_t addr, iomode_t mode,           \
	                        struct aio_multihandle *__restrict UNUSED(aio)) {      \
		size_t result;                                                             \
		result = handle_##name##_preadv(self, dst, num_bytes, addr, mode);         \
		return result;                                                             \
	}

#define DEFINE_HANDLE_APWRITEV_FROM_PWRITEV(name, T)                           \
	INTERN WUNUSED NONNULL((1, 2, 6)) size_t KCALL                             \
	handle_##name##_apwritev(T *__restrict self,                               \
	                         struct aio_buffer *__restrict src,                \
	                         size_t num_bytes, pos_t addr, iomode_t mode,      \
	                         struct aio_multihandle *__restrict UNUSED(aio)) { \
		size_t result;                                                         \
		result = handle_##name##_pwritev(self, src, num_bytes, addr, mode);    \
		return result;                                                         \
	}

#endif /* __CC__ */
#endif /* CONFIG_BUILDING_KERNEL_CORE */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_HANDLE_PROTO_H */
