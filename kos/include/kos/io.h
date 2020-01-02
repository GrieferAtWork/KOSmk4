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
#ifndef _KOS_IO_H
#define _KOS_IO_H 1

#include <__stdinc.h>
#include <features.h>
#include <bits/types.h>

#ifndef __KOS__
#error "KOS-only system header"
#endif /* !__KOS__ */

__DECL_BEGIN

#ifdef __CC__
#ifndef __iomode_t_defined
#define __iomode_t_defined 1
typedef __iomode_t iomode_t; /* Set of `IO_*' */
#endif /* !__iomode_t_defined */

#ifndef __readdir_mode_t_defined
#define __readdir_mode_t_defined 1
typedef unsigned int readdir_mode_t; /* Set of `READDIR_*' */
#endif /* !__readdir_mode_t_defined */

#ifndef __fallocate_mode_t_defined
#define __fallocate_mode_t_defined 1
typedef unsigned int fallocate_mode_t; /* TODO */
#endif /* !__fallocate_mode_t_defined */

#ifndef __poll_mode_t_defined
#define __poll_mode_t_defined 1
typedef unsigned int poll_mode_t; /* Set of `POLL*' */
#endif /* !poll_mode_t_defined */
#endif /* __CC__ */


/* Poll flags (`poll_mode_t' / `struct pollfd') */
#ifndef POLLIN
#define POLLIN           0x001 /* There is data to read. (`read' & friends won't block when invoked) */
#define POLLPRI          0x002 /* There is urgent data to read. */
#define POLLOUT          0x004 /* Writing now will not block. (`write' & friends won't block when invoked) */
#endif /* !POLLOUT */



/* File status flags (`struct stat::st_mode') */
#ifndef S_IFMT
#define S_IFMT   0170000 /* These bits determine file type. */
#define S_IFDIR  0040000 /* Directory. */
#define S_IFCHR  0020000 /* Character device. */
#define S_IFBLK  0060000 /* Block device. */
#define S_IFREG  0100000 /* Regular file. */
#define S_IFIFO  0010000 /* FIFO. */
#define S_IFLNK  0120000 /* Symbolic link. */
#define S_IFSOCK 0140000 /* Socket. */
#define S_ISUID  0004000 /* Set user ID on execution. */
#define S_ISGID  0002000 /* Set group ID on execution. */
#define S_ISVTX  0001000 /* Save swapped text after use (sticky). */
#define S_IREAD  0000400 /* Read by owner. */
#define S_IWRITE 0000200 /* Write by owner. */
#define S_IEXEC  0000100 /* Execute by owner. */
#endif /* !S_IFMT */

#ifndef S_ISDIR
#define S_ISDIR(x)  (((x) & S_IFMT) == S_IFDIR)
#define S_ISCHR(x)  (((x) & S_IFMT) == S_IFCHR)
#define S_ISBLK(x)  (((x) & S_IFMT) == S_IFBLK)
#define S_ISREG(x)  (((x) & S_IFMT) == S_IFREG)
#define S_ISFIFO(x) (((x) & S_IFMT) == S_IFIFO)
#define S_ISLNK(x)  (((x) & S_IFMT) == S_IFLNK)
#endif /* !S_ISDIR */
#ifndef S_ISDEV
#define S_ISDEV(x)  (((x) & 0130000) == 0020000) /* S_IFCHR|S_IFBLK */
#endif /* !S_ISDEV */


/* Directory entry types (`struct dirent::d_type'). */
#ifndef DT_UNKNOWN
#define DT_UNKNOWN 0
#define DT_FIFO    1
#define DT_CHR     2
#define DT_DIR     4
#define DT_BLK     6
#define DT_REG     8
#define DT_LNK     10
#define DT_SOCK    12
#define DT_WHT     14
#endif /* DT_UNKNOWN */

/* Convert between stat structure types and directory types. */
#ifndef IFTODT
#define IFTODT(mode)    (((mode) & 0170000) >> 12)
#define DTTOIF(dirtype) ((dirtype) << 12)
#endif /* !IFTODT */


/* File system mode (`atflag_t') */
#ifndef FS_MODE_FNORMAL
#define FS_MODE_FNORMAL                   0x00000000 /* Operate normally. */
#define FS_MODE_FIGNORE_TRAILING_SLASHES  0x00000002 /* Ignore empty trailing path segments. */
#define FS_MODE_FSYMLINK_NOFOLLOW         0x00000100 /* If the last path component is a symlink, don't follow it. */
#define FS_MODE_FNO_AUTOMOUNT             0x00000800 /* Suppress terminal automount traversal. */
#define FS_MODE_FEMPTY_PATH               0x00001000 /* Allow empty relative pathname. */
#define FS_MODE_FSYMLINK_REGULAR          0x00002000 /* Treat symbolic links similar to like regular files and throw an
                                                      * `E_FSERROR_TOO_MANY_SYMBOLIC_LINKS' error during the first encounter. */
#define FS_MODE_FDOSPATH                  0x00100000 /* Interpret '\\' as '/', and ignore casing during path resolution. */

#define FS_MODE_FALWAYS0MASK              0xffefc7ff /* Mask of bits always 0 in `struct fs::f_atmask' */
#define FS_MODE_FALWAYS1MASK              0x00000100 /* Mask of bits always 1 in `struct fs::f_atmask' */
#define FS_MODE_FALWAYS0FLAG              0xffefc7ff /* Mask of bits always 0 in `struct fs::f_atflag' */
#define FS_MODE_FALWAYS1FLAG              0x00000000 /* Mask of bits always 1 in `struct fs::f_atflag' */
#endif /* !FS_MODE_FNORMAL */



/* Open flags (`oflag_t') */
#ifndef O_ACCMODE
#define O_ACCMODE    0x0000003 /* Mask for ACCessMODE. */
#define O_RDONLY     0x0000000 /* Read */
#define O_WRONLY     0x0000001 /* Write */
#define O_RDWR       0x0000002 /* Read + write */
/*      O_RDWR       0x0000003 /* Implemented as an alias! */
#define O_CREAT      0x0000040 /* If missing, create a new file */
#define O_EXCL       0x0000080 /* When used with `O_CREAT', throw an `E_FSERROR_FILE_ALREADY_EXISTS'
                                * exception if the file already exists. */
#define O_NOCTTY     0x0000100 /* If the calling process does not have a controlling terminal assigned,
                                * do not attempt to assign the newly opened file as terminal, even when
                                * `isatty(open(...))' would be true. */
#define O_TRUNC      0x0000200 /* Truncate existing files to 0 when opened. */
#define O_APPEND     0x0000400 /* Always append data to the end of the file */
#define O_NONBLOCK   0x0000800 /* Do not block when trying to read data that hasn't been written, yet. */
#define O_SYNC       0x0001000 /* ??? */
#define O_DSYNC      0x0001000 /* ??? */
#define O_ASYNC      0x0002000 /* ??? */
#define O_DIRECT     0x0004000 /* ??? */
#define O_LARGEFILE  0x0008000 /* Ignored... */
#define O_DIRECTORY  0x0010000 /* Throw an `E_FSERROR_NOT_A_DIRECTORY:E_FILESYSTEM_NOT_A_DIRECTORY_OPEN' exception when the final
                                * path component of an open() system call turns out to be something other than a directory. */
#define O_NOFOLLOW   0x0020000 /* Throw an `E_FSERROR_IS_A_SYMBOLIC_LINK:E_FILESYSTEM_IS_A_SYMBOLIC_LINK_OPEN' exception when the
                                * final path component of an open() system call turns out to be a symbolic link. Otherwise, when
                                * one of two things will happen: When `O_SYMLINK' is set, open the link itself, else walk
                                * the link and open the file that it is pointing to instead. */
#define O_NOATIME    0x0040000 /* Don't update last-accessed time stamps. */
#define O_CLOEXEC    0x0080000 /* Close the file during exec() */
#define O_CLOFORK    0x0100000 /* Close the handle when the file descriptors are unshared (s.a. `CLONE_FILES') */
#define O_PATH       0x0200000 /* Open a path for *at system calls. */
#define O_TMPFILE   (0x0400000 | O_DIRECTORY)
#define O_SYMLINK    0x2000000 /* Open a symlink itself, rather than dereferencing it.
                                * NOTE: When combined with `O_EXCL', throw an `E_FSERROR_NOT_A_SYMBOLIC_LINK:
                                *       E_FILESYSTEM_NOT_A_SYMBOLIC_LINK_OPEN' if the file isn't a symbolic link.
                                * NOTE: When used alongside `O_NOFOLLOW', throw an `E_INVALID_ARGUMENT' */
#define O_DOSPATH    0x4000000 /* Interpret '\\' as '/', and ignore casing during path resolution.
                                * Additionally, recognize DOS mounting points, and interpret leading
                                * slashes as relative to the closest DOS mounting point. (s.a.: `AT_DOSPATH') */
#endif /* !O_ACCMODE */




#ifndef READDIR_DEFAULT
#define READDIR_DEFAULT  0x0000 /* Yield to next entry when `buf' was of sufficient size. */
#define READDIR_CONTINUE 0x0001 /* Always yield to next entry. */
#define READDIR_PEEK     0x0002 /* Never yield to next entry. */
#if __KOS_VERSION__ >= 300
#define READDIR_SKIPREL  0x4000 /* Skip reading the `.' and `..' directory entries. */
#define READDIR_WANTEOF  0x8000 /* Minor optimization for `READDIR_MULTIPLE':
                                 * The system is allowed to append an empty directory entry
                                 * (with `d_namlen = 0' and `d_name[0] = '\0''; other fields are undefined).
                                 * If there isn't enough space for such an entry, no such entry will be emit.
                                 * Since no other directory entry can ever have a length of ZERO(0),
                                 * this allows user-space to detect end-of-directory without the need
                                 * of re-invoking the kreaddir() system call and inspecting its return
                                 * value for being equal to ZERO(0).
                                 * However, that check is still required, as this flag may be ignored
                                 * for no reason immediately apparent (if the EOF entry can't fit into
                                 * the buffer, there's no way of knowing if there's a missing entry that's
                                 * supposed to go into the buffer, or if it was actually an EOF entry).
                                 * Additionally, no eof entry may be written if kreaddir() is invoked
                                 * on a directory handle who's stream position is at the end of the directory.
                                 * For usage, see the example below, as well as `READDIR_MULTIPLE_ISEOF()' */
#define READDIR_MODEMASK 0x001f /* Mask for the kreaddir() mode. */
#define READDIR_FLAGMASK 0xc000 /* Mask of known kreaddir() flags. */
#define READDIR_MODEMAX  0x0003 /* Mask recognized mode ID. */
#define READDIR_MULTIPLE 0x0003 /* Read as many directory entries as can fit into the buffer.
                                 * If at least one entry could be read, return the combined size
                                 * of all read entries (in bytes) (in this case, `return <= bufsize')
                                 * If the buffer was too small to contain the next entry,
                                 * return the required size to house that pending entry,
                                 * but don't yield it, the same way `READDIR_DEFAULT' wouldn't.
                                 * To enumerate multiple directories in some buffer, use the
                                 * macros below. */
#ifdef __CC__
/* READDIR_MULTIPLE buffer helpers:
 * >> for (;;) {
 * >> 	char buffer[2048]; size_t bufsize;
 * >> 	struct dirent *iter = (struct dirent *)buffer;
 * >> 	// Read as many entries as our buffer can fit
 * >> 	bufsize = kreaddir(fd,iter,sizeof(buffer),
 * >> 	                   READDIR_MULTIPLE|
 * >> 	                   READDIR_WANTEOF);
 * >> 	if (!bufsize)
 * >> 		break; // End of directory
 * >> 	if (bufsize > sizeof(buffer)) {
 * >> 		printf("The next directory entry is too larger for the buffer\n");
 * >> 		break;
 * >> 	}
 * >> 	// Process successfully read entries
 * >> 	do {
 * >> 		// This check is only required when `READDIR_WANTEOF' is passed.
 * >> 		if (READDIR_MULTIPLE_ISEOF(iter))
 * >> 			goto done;
 * >> 		printf("Entry: %q\n",iter->d_name);
 * >> 		iter = READDIR_MULTIPLE_GETNEXT(iter);
 * >> 	} while (READDIR_MULTIPLE_ISVALID(iter,buffer,bufsize));
 * >> }
 * >>done:
 */
#define READDIR_MULTIPLE_GETNEXT(p) \
	((struct dirent *)(((uintptr_t)((p)->d_name+((p)->d_namlen+1))+ \
	                    (sizeof(__ino64_t)-1)) & ~(sizeof(__ino64_t)-1)))
#define READDIR_MULTIPLE_ISVALID(p,buf,bufsize) \
	(((__BYTE_TYPE__ *)((p)->d_name)) < ((__BYTE_TYPE__ *)(buf)+(bufsize)) && \
	 ((__BYTE_TYPE__ *)((p)->d_name+(p)->d_namlen)) < ((__BYTE_TYPE__ *)(buf)+(bufsize)))
#define READDIR_MULTIPLE_ISEOF(p) ((p)->d_namlen == 0)
#ifdef __USE_LARGEFILE64
#define READDIR_MULTIPLE_GETNEXT64(p) ((struct dirent64 *)READDIR_MULTIPLE_GETNEXT(p))
#endif /* __USE_LARGEFILE64 */
#endif /* __CC__ */
#endif /* __KOS_VERSION__ >= 300 */
#endif /* !READDIR_DEFAULT */




/* fcntl() commands */
#ifndef F_DUPFD
#define F_DUPFD            0 /* Duplicate file descriptor. */
#define F_GETFD            1 /* Get file descriptor flags (as a set of `O_CLOFORK | O_CLOEXEC'). */
#define F_SETFD            2 /* Set file descriptor flags (as a set of `O_CLOFORK | O_CLOEXEC'). */
#define F_GETFL            3 /* Get file status flags (as a set of `O_APPEND | O_NONBLOCK | O_SYNC | O_ASYNC | O_DIRECT'). */
#define F_SETFL            4 /* Set file status flags (as a set of `O_APPEND | O_NONBLOCK | O_SYNC | O_ASYNC | O_DIRECT'). */
#define F_GETLK32          5 /* Get record locking info. */
#define F_SETLK32          6 /* Set record locking info (non-blocking). */
#define F_SETLKW32         7 /* Set record locking info (blocking).    */
#define F_SETOWN           8 /* Get owner (process receiving SIGIO). */
#define F_GETOWN           9 /* Set owner (process receiving SIGIO). */
#define F_SETSIG          10 /* Set number of signal to be sent. */
#define F_GETSIG          11 /* Get number of signal to be sent. */
#define F_GETLK64         12 /* Get record locking info. */
#define F_SETLK64         13 /* Set record locking info (non-blocking). */
#define F_SETLKW64        14 /* Set record locking info (blocking). */
#define F_SETOWN_EX       15 /* Get owner (thread receiving SIGIO). */
#define F_GETOWN_EX       16 /* Set owner (thread receiving SIGIO). */
#define F_SETLEASE      1024 /* Set a lease. */
#define F_GETLEASE      1025 /* Enquire what lease is active. */
#define F_NOTIFY        1026 /* Request notifications on a directory. */
#define F_SETPIPE_SZ    1031 /* Set pipe page size array. */
#define F_GETPIPE_SZ    1032 /* Get pipe page size array. */
#define F_DUPFD_CLOEXEC 1030 /* Duplicate file descriptor with close-on-exit set. */
#define F_SETFL_XCH     5163 /* Same as 'F_SETFL', but return the old set of flags instead of `0' upon success.
                              * (as a set of `O_APPEND|O_NONBLOCK|O_SYNC|O_ASYNC|O_DIRECT'). */
#endif /* !F_DUPFD */



/* File descriptor flags */
#ifndef FD_CLOEXEC
#define FD_CLOEXEC   0x01 /* FLAG: Close the descriptor on `exec()'. */
#define FD_CLOFORK   0x02 /* FLAG: Close the descriptor during unsharing after `fork()'
                           *      (Similar to `PROT_LOOSE' for memory). */
#endif /* !FD_CLOEXEC */




/* Universal I/O mode & handle access flags. */
#ifndef IO_GENERIC
#define IO_GENERIC     0x0000 /* Generic I/O access. */
#define IO_ACCMODE     0x0003 /* Access mode mask */
#define IO_RDONLY      0x0000 /* Read-only access */
#define IO_WRONLY      0x0001 /* Write-only access */
#define IO_RDWR        0x0002 /* Read/write access */
#define IO_RDWR_ALT    0x0003 /* Read/write access */
#define IO_CLOEXEC     0x0004 /* Close during exec() */
#define IO_CLOFORK     0x0008 /* Close during fork() */
#define IO_APPEND      0x0400 /* Append newly written data at the end */
#define IO_NONBLOCK    0x0800 /* Don't block in I/O */
#define IO_SYNC        0x1000 /* Ensure that all modified caches are flushed during write() */
#define IO_ASYNC       0x2000 /* Use asynchronous I/O and generate SIGIO upon completion. */
#define IO_DIRECT      0x4000 /* Bypass input/output buffers if possible. - Try to read/write data directly to/from provided buffers. */

/* Check if reading/writing is possible with a given I/O mode. */
#define IO_CANREAD(mode)      (((mode) & IO_ACCMODE) != IO_WRONLY)
#define IO_CANWRITE(mode)     (((mode) & IO_ACCMODE) != IO_RDONLY)
#define IO_CANREADWRITE(mode) (((mode) & IO_ACCMODE) == IO_RDWR)

/* Mask of flags accepted by the kos extension functions:
 *  `readf', `writef', `preadf', `pwritef', `ioctlf()', `hopf()' */
#define IO_USERF_MASK (IO_APPEND | IO_NONBLOCK | IO_SYNC | IO_ASYNC | IO_DIRECT)

/* Mask of flags modifiable via `F_SETFD' / `F_SETFL' */
#define IO_SETFL_MASK (IO_APPEND | IO_NONBLOCK | IO_SYNC | IO_ASYNC | IO_DIRECT)

/* Mask for handle flags (flags not inherited during `dup()'). */
#define IO_SETFD_MASK (IO_CLOEXEC | IO_CLOFORK)

/* NOTE: The following flags don't affect I/O, but are stored in the same field.
 *       Additionally, their `O_*' equivalent have different values. */
#define IO_HANDLE_CLOEXEC           IO_CLOEXEC /* Close during exec() */
#define IO_HANDLE_CLOFORK           IO_CLOFORK /* Close during fork() */
#define IO_HANDLE_FFROM_OPENFLAG(x) (__CCAST(__iomode_t)(((x) & 0x180000) >> 17))
#define IO_HANDLE_FTO_OPENFLAG(x)   ((__CCAST(__oflag_t)(x) & 0xc) << 17)
/* Similar to `IO_HANDLE_FFROM_O()' / `IO_HANDLE_FTO_O()', but used for converting `FD_*' flags. */
#define IO_HANDLE_FFROM_FD(x) (__CCAST(__iomode_t)((x) << 2))
#define IO_HANDLE_FTO_FD(x)   (__CCAST(__oflag_t)(x) >> 2)

/* Convert I/O flags to/from `O_*' flags. */
#define IO_FROM_OPENFLAG(x)          (((x) & 0xfff3) | IO_HANDLE_FFROM_OPENFLAG(x))
#define IO_TO_OPENFLAG(x)            (((x) & 0xfff3) | IO_HANDLE_FTO_OPENFLAG(x))
#define IO_FROM_OPENFLAG_NOHANDLE(x) ((x) & 0xfff3)
#define IO_TO_OPENFLAG_NOHANDLE(x)   ((x) & 0xfff3)
#endif /* !IO_GENERIC */



__DECL_END

#endif /* !_KOS_IO_H */
