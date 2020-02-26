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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_HANDLE_PROTO_H
#define GUARD_KERNEL_INCLUDE_KERNEL_HANDLE_PROTO_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <kos/io.h>

DECL_BEGIN

#ifdef __DEEMON__
#define HANDLE_OPERATOR_PROTOTYPES                                                                       \
	{                                                                                                    \
		("tryincref", "NOBLOCK NONNULL((1))", "__BOOL", "NOTHROW", "FCALL",                              \
		 { ("void *__restrict", "self") },                                                               \
		 "", "return 1;"),                                                                               \
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
struct realtime_clock_struct;
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
struct driver_section;
struct socket;



/* Handle operators for `HANDLE_TYPE_DATABLOCK' (`struct vm_datablock') */
INTDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL handle_datablock_tryincref)(struct vm_datablock *__restrict self);
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
INTDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL handle_blockdevice_tryincref)(struct basic_block_device *__restrict self);
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
INTDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL handle_directoryentry_tryincref)(struct directory_entry *__restrict self);
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
INTDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL handle_file_tryincref)(struct file *__restrict self);
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
INTDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL handle_oneshot_directory_file_tryincref)(struct oneshot_directory_file *__restrict self);
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
INTDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL handle_path_tryincref)(struct path *__restrict self);
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
INTDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL handle_fs_tryincref)(struct fs *__restrict self);
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
INTDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL handle_vm_tryincref)(struct vm *__restrict self);
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
INTDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL handle_task_tryincref)(struct taskpid *__restrict self);
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

/* Handle operators for `HANDLE_TYPE_CLOCK' (`struct realtime_clock_struct') */
INTDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL handle_clock_tryincref)(struct realtime_clock_struct *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_clock_incref)(struct realtime_clock_struct *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_clock_decref)(struct realtime_clock_struct *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_clock_refcnt)(struct realtime_clock_struct const *__restrict self);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_clock_read(struct realtime_clock_struct *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_clock_write(struct realtime_clock_struct *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_clock_pread(struct realtime_clock_struct *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_clock_pwrite(struct realtime_clock_struct *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_clock_readv(struct realtime_clock_struct *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_clock_writev(struct realtime_clock_struct *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_clock_preadv(struct realtime_clock_struct *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_clock_pwritev(struct realtime_clock_struct *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_clock_readdir(struct realtime_clock_struct *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_clock_seek(struct realtime_clock_struct *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_clock_ioctl(struct realtime_clock_struct *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_clock_truncate(struct realtime_clock_struct *__restrict self, pos_t new_size) THROWS(...);
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL handle_clock_mmap(struct realtime_clock_struct *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_clock_allocate(struct realtime_clock_struct *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_clock_sync(struct realtime_clock_struct *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_clock_datasync(struct realtime_clock_struct *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_clock_stat(struct realtime_clock_struct *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_clock_poll(struct realtime_clock_struct *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_clock_hop(struct realtime_clock_struct *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Handle operators for `HANDLE_TYPE_DRIVER' (`struct driver') */
INTDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL handle_driver_tryincref)(struct driver *__restrict self);
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
INTDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL handle_pipe_tryincref)(struct pipe *__restrict self);
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
INTDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL handle_pipe_reader_tryincref)(struct pipe_reader *__restrict self);
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
INTDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL handle_pipe_writer_tryincref)(struct pipe_writer *__restrict self);
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
INTDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL handle_pidns_tryincref)(struct pidns *__restrict self);
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
INTDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL handle_driver_state_tryincref)(struct driver_state *__restrict self);
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
INTDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL handle_characterdevice_tryincref)(struct character_device *__restrict self);
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
INTDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL handle_eventfd_fence_tryincref)(struct eventfd *__restrict self);
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
INTDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL handle_eventfd_sema_tryincref)(struct eventfd *__restrict self);
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
INTDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL handle_signalfd_tryincref)(struct signalfd *__restrict self);
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
INTDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL handle_datapart_tryincref)(struct vm_datapart *__restrict self);
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
INTDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL handle_futex_tryincref)(struct vm_futex *__restrict self);
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
INTDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL handle_futexfd_tryincref)(struct vm_futexfd *__restrict self);
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

/* Handle operators for `HANDLE_TYPE_DRIVER_SECTION' (`struct driver_section') */
INTDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL handle_driver_section_tryincref)(struct driver_section *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_driver_section_incref)(struct driver_section *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_driver_section_decref)(struct driver_section *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_driver_section_refcnt)(struct driver_section const *__restrict self);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_section_read(struct driver_section *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_section_write(struct driver_section *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_section_pread(struct driver_section *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_section_pwrite(struct driver_section *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_section_readv(struct driver_section *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_section_writev(struct driver_section *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_section_preadv(struct driver_section *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_driver_section_pwritev(struct driver_section *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_driver_section_readdir(struct driver_section *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_driver_section_seek(struct driver_section *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_driver_section_ioctl(struct driver_section *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_section_truncate(struct driver_section *__restrict self, pos_t new_size) THROWS(...);
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL handle_driver_section_mmap(struct driver_section *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_driver_section_allocate(struct driver_section *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_section_sync(struct driver_section *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_section_datasync(struct driver_section *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_driver_section_stat(struct driver_section *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_driver_section_poll(struct driver_section *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_driver_section_hop(struct driver_section *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Handle operators for `HANDLE_TYPE_SOCKET' (`struct socket') */
INTDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL handle_socket_tryincref)(struct socket *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_socket_incref)(struct socket *__restrict self);
INTDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL handle_socket_decref)(struct socket *__restrict self);
INTDEF NOBLOCK WUNUSED NONNULL((1)) refcnt_t NOTHROW(FCALL handle_socket_refcnt)(struct socket const *__restrict self);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_socket_read(struct socket *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_socket_write(struct socket *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_socket_pread(struct socket *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_socket_pwrite(struct socket *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_socket_readv(struct socket *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_socket_writev(struct socket *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_socket_preadv(struct socket *__restrict self, struct aio_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1, 2)) size_t KCALL handle_socket_pwritev(struct socket *__restrict self, struct aio_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
INTDEF WUNUSED NONNULL((1)) size_t KCALL handle_socket_readdir(struct socket *__restrict self, USER CHECKED struct dirent *buf, size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_socket_seek(struct socket *__restrict self, off_t offset, unsigned int whence) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_socket_ioctl(struct socket *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_socket_truncate(struct socket *__restrict self, pos_t new_size) THROWS(...);
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct vm_datablock *KCALL handle_socket_mmap(struct socket *__restrict self, pos_t *__restrict pminoffset, pos_t *__restrict pnumbytes) THROWS(...);
INTDEF NONNULL((1)) pos_t KCALL handle_socket_allocate(struct socket *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_socket_sync(struct socket *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_socket_datasync(struct socket *__restrict self) THROWS(...);
INTDEF NONNULL((1)) void KCALL handle_socket_stat(struct socket *__restrict self, USER CHECKED struct stat *result) THROWS(...);
INTDEF WUNUSED NONNULL((1)) poll_mode_t KCALL handle_socket_poll(struct socket *__restrict self, poll_mode_t what) THROWS(...);
INTDEF NONNULL((1)) syscall_slong_t KCALL handle_socket_hop(struct socket *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

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
	INTERN NOBLOCK NONNULL((1)) __BOOL                                \
	NOTHROW(FCALL handle_##name##_tryincref)(T *__restrict self) {    \
		return tryincref(self);                                       \
	}                                                                 \
	INTERN NOBLOCK NONNULL((1)) void                                  \
	NOTHROW(FCALL handle_##name##_incref)(T *__restrict self) {       \
		incref(self);                                                 \
	}                                                                 \
	INTERN NOBLOCK NONNULL((1)) void                                  \
	NOTHROW(FCALL handle_##name##_decref)(REF T *__restrict self) {   \
		decref(self);                                                 \
	}
#endif /* __CC__ */
#endif /* CONFIG_BUILDING_KERNEL_CORE */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_HANDLE_PROTO_H */
