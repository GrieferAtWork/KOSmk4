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
#ifndef GUARD_MODGDBSERVER_FSIO_H
#define GUARD_MODGDBSERVER_FSIO_H 1

#include <kernel/compiler.h>

#include <kernel/handle.h>
#include <kernel/types.h>

#include <stdbool.h>

DECL_BEGIN

/* From: https://sourceware.org/gdb/onlinedocs/gdb/Open-Flags.html#Open-Flags */
#define GDB_O_RDONLY  0x000
#define GDB_O_WRONLY  0x001
#define GDB_O_RDWR    0x002
#define GDB_O_ACCMODE 0x003
#define GDB_O_APPEND  0x008
#define GDB_O_CREAT   0x200
#define GDB_O_TRUNC   0x400
#define GDB_O_EXCL    0x800

#define GDB_O_MASK                              \
	(GDB_O_RDONLY | GDB_O_WRONLY | GDB_O_RDWR | \
	 GDB_O_APPEND | GDB_O_CREAT | GDB_O_TRUNC | \
	 GDB_O_EXCL)

/* https://sourceware.org/gdb/onlinedocs/gdb/mode_005ft-Values.html#mode_005ft-Values */
#define GDB_S_IXOTH 0000001
#define GDB_S_IWOTH 0000002
#define GDB_S_IROTH 0000004
#define GDB_S_IXGRP 0000010
#define GDB_S_IWGRP 0000020
#define GDB_S_IRGRP 0000040
#define GDB_S_IXUSR 0000100
#define GDB_S_IWUSR 0000200
#define GDB_S_IRUSR 0000400
#define GDB_S_IFDIR 0040000
#define GDB_S_IFREG 0100000


/* From: https://sourceware.org/gdb/onlinedocs/gdb/Errno-Values.html#Errno-Values */
#define GDB_EPERM         1
#define GDB_ENOENT        2
#define GDB_EINTR         4
#define GDB_EBADF         9
#define GDB_EACCES       13
#define GDB_EFAULT       14
#define GDB_EBUSY        16
#define GDB_EEXIST       17
#define GDB_ENODEV       19
#define GDB_ENOTDIR      20
#define GDB_EISDIR       21
#define GDB_EINVAL       22
#define GDB_ENFILE       23
#define GDB_EMFILE       24
#define GDB_EFBIG        27
#define GDB_ENOSPC       28
#define GDB_ESPIPE       29
#define GDB_EROFS        30
#define GDB_ENAMETOOLONG 91
#define GDB_EUNKNOWN     9999

/* https://sourceware.org/gdb/onlinedocs/gdb/Lseek-Flags.html#Lseek-Flags */
#define GDB_SEEK_SET 0
#define GDB_SEEK_CUR 1
#define GDB_SEEK_END 2


#ifdef __CC__

/* From https://sourceware.org/gdb/onlinedocs/gdb/Integral-Datatypes.html#Integral-Datatypes */
typedef int32_t gdb_int_t, gdb_mode_t, gdb_time_t;
typedef uint32_t gdb_uint_t;
typedef int64_t gdb_long_t;
typedef uint64_t gdb_ulong_t;
typedef uintptr_t gdb_oflag_t;
typedef unsigned int gdb_errno_t;

/* From https://sourceware.org/gdb/onlinedocs/gdb/struct-stat.html#struct-stat */
struct ATTR_PACKED gdb_stat {
	gdb_uint_t  st_dev;     /* device */
	gdb_uint_t  st_ino;     /* inode */
	gdb_mode_t  st_mode;    /* protection */
	gdb_uint_t  st_nlink;   /* number of hard links */
	gdb_uint_t  st_uid;     /* user ID of owner */
	gdb_uint_t  st_gid;     /* group ID of owner */
	gdb_uint_t  st_rdev;    /* device type (if inode device) */
	gdb_ulong_t st_size;    /* total size, in bytes */
	gdb_ulong_t st_blksize; /* blocksize for filesystem I/O */
	gdb_ulong_t st_blocks;  /* number of blocks allocated */
	gdb_time_t  st_atime;   /* time of last access */
	gdb_time_t  st_mtime;   /* time of last modification */
	gdb_time_t  st_ctime;   /* time of last change */
};

/* From https://sourceware.org/gdb/onlinedocs/gdb/struct-timeval.html#struct-timeval */
struct ATTR_PACKED gdb_timeval {
	gdb_time_t tv_sec;  /* second */
	gdb_long_t tv_usec; /* microsecond */
};


struct fs;
struct handle;

struct fsio_struct {
	/* NOTE: Elements of this structure are implicitly guarded by `GDBServer_Host' */
	REF struct fs *fi_fs;      /* [0..1] The bound filesystem (s.a. `vFile:setfs:<pid>'). */
	unsigned int   fi_halloc;  /* Allocated number of handles. */
	struct handle *fi_hvector; /* [0..hm_alloc][owned] Vector of handles. (index == fd_t) */
#define GDBFS_HANDLE_RESIZE_THRESHOLD 8
};

/* GDB filesystem access control. */
INTDEF struct fsio_struct GDBFs;

/* Lookup and return a pointer to the given GDB `fdno'
 * if no such  handle exists,  return `NULL'  instead. */
LOCAL NOBLOCK ATTR_PURE WUNUSED struct handle *
NOTHROW(KCALL GDBFs_LookupHandle)(fd_t fdno) {
	if ((unsigned int)fdno >= GDBFs.fi_halloc)
		return __NULLPTR;
	return &GDBFs.fi_hvector[(unsigned int)fdno];
}

/* Returns -1 memory could not be allocated. */
INTDEF WUNUSED fd_t NOTHROW(KCALL GDBFs_RegisterHandle)(/*inherit(on_success)*/ REF struct handle const *__restrict hnd);

/* Delete a previously registered handle. */
INTERN bool NOTHROW(KCALL GDBFs_DeleteHandle)(fd_t fdno);

/* Finalize the file-system sub-system */
INTDEF NOBLOCK void NOTHROW(KCALL GDBFs_Fini)(void);

/* Open a file handle for GDB (returns 0 on success) */
INTDEF WUNUSED gdb_errno_t
NOTHROW(KCALL GDBFs_Open)(char const *filename,
                          gdb_oflag_t oflags, gdb_mode_t mode,
                          struct handle *__restrict result);

/* Delete the file associated with `filename' */
INTDEF WUNUSED gdb_errno_t
NOTHROW(KCALL GDBFs_Unlink)(char const *filename);

/* Resolve a symbolic link (don't include trailing NUL-characters, though...)
 * @param: pbuflen: [IN]  Available buffer size in `buf'
 *                  [OUT] Number of bytes written to `buf' */
INTDEF WUNUSED gdb_errno_t
NOTHROW(KCALL GDBFs_Readlink)(char const *filename,
                              char *buf,
                              size_t *__restrict pbuflen);


/* Encode a given KOS errno for GDB */
INTDEF NOBLOCK ATTR_CONST gdb_errno_t
NOTHROW(KCALL GDB_ErrnoEncode)(errno_t error);


#endif /* __CC__ */


DECL_END

#endif /* !GUARD_MODGDBSERVER_FSIO_H */
