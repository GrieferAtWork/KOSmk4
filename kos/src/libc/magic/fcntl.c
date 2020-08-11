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
%[default:section(".text.crt{|.dos}.io.utility")]

%[define_replacement(fd_t    = __fd_t)]
%[define_replacement(off_t   = "__FS_TYPE(off)")]
%[define_replacement(pos_t   = "__FS_TYPE(pos)")]
%[define_replacement(off32_t = __off32_t)]
%[define_replacement(off64_t = __off64_t)]
%[define_replacement(pos32_t = __pos32_t)]
%[define_replacement(pos64_t = __pos64_t)]
%[define_replacement(oflag_t = __oflag_t)]



%[define_replacement(O_ACCMODE   = __O_ACCMODE)]
%[define_replacement(O_RDONLY    = __O_RDONLY)]
%[define_replacement(O_WRONLY    = __O_WRONLY)]
%[define_replacement(O_RDWR      = __O_RDWR)]
%[define_replacement(O_TRUNC     = __O_TRUNC)]
%[define_replacement(O_CREAT     = __O_CREAT)]
%[define_replacement(O_EXCL      = __O_EXCL)]
%[define_replacement(O_NOCTTY    = __O_NOCTTY)]
%[define_replacement(O_APPEND    = __O_APPEND)]
%[define_replacement(O_NONBLOCK  = __O_NONBLOCK)]
%[define_replacement(O_SYNC      = __O_SYNC)]
%[define_replacement(O_DSYNC     = __O_DSYNC)]
%[define_replacement(O_ASYNC     = __O_ASYNC)]
%[define_replacement(O_DIRECT    = __O_DIRECT)]
%[define_replacement(O_LARGEFILE = __O_LARGEFILE)]
%[define_replacement(O_DIRECTORY = __O_DIRECTORY)]
%[define_replacement(O_NOFOLLOW  = __O_NOFOLLOW)]
%[define_replacement(O_NOATIME   = __O_NOATIME)]
%[define_replacement(O_CLOEXEC   = __O_CLOEXEC)]
%[define_replacement(O_PATH      = __O_PATH)]
%[define_replacement(O_TMPFILE   = __O_TMPFILE)]
%[define_replacement(O_CLOFORK   = __O_CLOFORK)]
%[define_replacement(O_SYMLINK   = __O_SYMLINK)]
%[define_replacement(O_DOSPATH   = __O_DOSPATH)]
%[define_replacement(O_ANYTHING  = __O_ANYTHING)]



%{
#include <features.h>

#include <asm/fcntl.h>
#include <asm/oflags.h>
#include <bits/flock-struct.h>
#include <bits/types.h>

#ifdef __USE_GNU
#include <asm/limits.h> /* __IOV_MAX */
#include <bits/f_owner_ex-struct.h>
#include <bits/file_handle-struct.h>
#include <bits/iovec-struct.h>

#ifndef UIO_MAXIOV
#if !defined(__IOV_MAX) || (__IOV_MAX == -1)
#define UIO_MAXIOV 16
#else /* !__IOV_MAX || __IOV_MAX == -1 */
#define UIO_MAXIOV __IOV_MAX
#endif /* __IOV_MAX && __IOV_MAX != -1 */
#endif /* !UIO_MAXIOV */
#endif /* __USE_GNU */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#include <asm/stdio.h>
#include <bits/stat.h>
#include <bits/timespec.h>
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */

__SYSDECL_BEGIN

/* Mask for `O_RDONLY | O_WRONLY | O_RDWR' */
#if !defined(O_ACCMODE) && defined(__O_ACCMODE)
#define O_ACCMODE __O_ACCMODE
#endif /* !O_ACCMODE && __O_ACCMODE */

/* Access mode: read-only */
#if !defined(O_RDONLY) && defined(__O_RDONLY)
#define O_RDONLY __O_RDONLY
#endif /* !O_RDONLY && __O_RDONLY */

/* Access mode: write-only */
#if !defined(O_WRONLY) && defined(__O_WRONLY)
#define O_WRONLY __O_WRONLY
#endif /* !O_WRONLY && __O_WRONLY */

/* Access mode: read/write */
#if !defined(O_RDWR) && defined(__O_RDWR)
#define O_RDWR __O_RDWR
#endif /* !O_RDWR && __O_RDWR */

/* Truncate the file's size to 0 */
#if !defined(O_TRUNC) && defined(__O_TRUNC)
#define O_TRUNC __O_TRUNC
#endif /* !O_TRUNC && __O_TRUNC */

/* If missing, create a new file */
#if !defined(O_CREAT) && defined(__O_CREAT)
#define O_CREAT __O_CREAT
#endif /* !O_CREAT && __O_CREAT */

/* When used with `O_CREAT', throw an `E_FSERROR_FILE_ALREADY_EXISTS' (-EEXISTS)
 * exception if the file already exists. */
#if !defined(O_EXCL) && defined(__O_EXCL)
#define O_EXCL __O_EXCL
#endif /* !O_EXCL && __O_EXCL */

/* If the calling process does not have a controlling terminal assigned,
 * do not attempt to assign the newly opened file as terminal, even when
 * `isatty(open(...))' would be true. */
#if !defined(O_NOCTTY) && defined(__O_NOCTTY)
#define O_NOCTTY __O_NOCTTY
#endif /* !O_NOCTTY && __O_NOCTTY */

/* Always append data to the end of the file */
#if !defined(O_APPEND) && defined(__O_APPEND)
#define O_APPEND __O_APPEND
#endif /* !O_APPEND && __O_APPEND */

/* Do not block when trying to read data that hasn't been written, yet. */
#if !defined(O_NONBLOCK) && defined(__O_NONBLOCK)
#define O_NONBLOCK __O_NONBLOCK
#endif /* !O_NONBLOCK && __O_NONBLOCK */

#if !defined(O_SYNC) && defined(__O_SYNC)
#define O_SYNC __O_SYNC /* ??? */
#endif /* !O_SYNC && __O_SYNC */

#if !defined(O_ASYNC) && defined(__O_ASYNC)
#define O_ASYNC __O_ASYNC /* ??? */
#endif /* !O_ASYNC && __O_ASYNC */

#ifdef __USE_KOS
#if !defined(O_ANYTHING) && defined(__O_ANYTHING)
#define O_ANYTHING   __O_ANYTHING
#endif /* !O_ANYTHING && __O_ANYTHING */
#endif /* __USE_KOS */

#if !defined(O_FSYNC) && defined(__O_SYNC)
#define O_FSYNC __O_SYNC /* ??? */
#endif /* !O_FSYNC && __O_SYNC */

#ifdef __USE_LARGEFILE64
#if !defined(O_LARGEFILE) && defined(__O_LARGEFILE)
#define O_LARGEFILE __O_LARGEFILE /* Ignored... */
#endif /* !O_LARGEFILE && __O_LARGEFILE */
#endif /* __USE_LARGEFILE64 */

#ifdef __USE_XOPEN2K8
/* Throw an `E_FSERROR_NOT_A_DIRECTORY:E_FILESYSTEM_NOT_A_DIRECTORY_OPEN' (-ENOTDIR) exception when the
 * final path component of an open() system call turns out to be something other than a directory. */
#if !defined(O_DIRECTORY) && defined(__O_DIRECTORY)
#define O_DIRECTORY __O_DIRECTORY
#endif /* !O_DIRECTORY && __O_DIRECTORY */

/* Throw an `E_FSERROR_IS_A_SYMBOLIC_LINK:E_FILESYSTEM_IS_A_SYMBOLIC_LINK_OPEN' (-ELOOP) exception when
 * the final path component of an open() system call turns out to be a symbolic link, unless `O_SYMLINK'
 * is given, in which case the link itself is opened. */
#if !defined(O_NOFOLLOW) && defined(__O_NOFOLLOW)
#define O_NOFOLLOW __O_NOFOLLOW
#endif /* !O_NOFOLLOW && __O_NOFOLLOW */

/* Close the file during exec() */
#if !defined(O_CLOEXEC) && defined(__O_CLOEXEC)
#define O_CLOEXEC __O_CLOEXEC
#endif /* !O_CLOEXEC && __O_CLOEXEC */
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_KOS
/* Close the handle when the file descriptors are unshared (s.a. `CLONE_FILES') */
#if !defined(O_CLOFORK) && defined(__O_CLOFORK)
#define O_CLOFORK __O_CLOFORK
#endif /* !O_CLOFORK && __O_CLOFORK */

/* Interpret '\\' as '/', and ignore casing during path resolution.
 * Additionally, recognize DOS mounting points, and interpret leading
 * slashes as relative to the closest DOS mounting point. (s.a.: `AT_DOSPATH') */
#if !defined(O_DOSPATH) && defined(__O_DOSPATH)
#define O_DOSPATH __O_DOSPATH
#endif /* !O_DOSPATH && __O_DOSPATH */

/* Open a symlink itself, rather than dereferencing it. (This flag implies `O_NOFOLLOW')
 * NOTE: When combined with `O_EXCL', throw an `E_FSERROR_NOT_A_SYMBOLIC_LINK:
 *       E_FILESYSTEM_NOT_A_SYMBOLIC_LINK_OPEN' if the file isn't a symbolic link. */
#if !defined(O_SYMLINK) && defined(__O_SYMLINK)
#define O_SYMLINK __O_SYMLINK
#endif /* !O_SYMLINK && __O_SYMLINK */
#endif /* __USE_KOS */

#ifdef __USE_GNU
#if !defined(O_DIRECT) && defined(__O_DIRECT)
#define O_DIRECT __O_DIRECT /* ??? */
#endif /* !O_DIRECT && __O_DIRECT */

/* Don't update last-accessed time stamps. */
#if !defined(O_NOATIME) && defined(__O_NOATIME)
#define O_NOATIME __O_NOATIME
#endif /* !O_NOATIME && __O_NOATIME */

/* Open a path for *at system calls. */
#if !defined(O_PATH) && defined(__O_PATH)
#define O_PATH __O_PATH
#endif /* !O_PATH && __O_PATH */

#if !defined(O_TMPFILE) && defined(__O_TMPFILE)
#define O_TMPFILE __O_TMPFILE
#endif /* !O_TMPFILE && __O_TMPFILE */
#endif /* __USE_GNU */

#if defined(__USE_POSIX199309) || defined(__USE_UNIX98)
#if !defined(O_DSYNC) && defined(__O_DSYNC)
#define O_DSYNC __O_DSYNC /* ??? */
#endif /* !O_DSYNC && __O_DSYNC */
#if !defined(O_RSYNC) && defined(__O_SYNC)
#define O_RSYNC __O_SYNC /* ??? */
#endif /* !O_RSYNC && __O_SYNC */
#endif /* __USE_POSIX199309 || __USE_UNIX98 */

/* Aliases */

/* Do not block when trying to read data that hasn't been written, yet. */
#ifdef __O_NONBLOCK
#define O_NDELAY __O_NONBLOCK
#endif /* __O_NONBLOCK */

#ifdef __USE_MISC

/* Always append data to the end of the file */
#ifdef __O_APPEND
#define FAPPEND __O_APPEND
#endif /* __O_APPEND */

#ifdef __O_SYNC
#define FFSYNC __O_SYNC /* ??? */
#endif /* __O_SYNC */

#ifdef __O_ASYNC
#define FASYNC __O_ASYNC /* ??? */
#endif /* __O_ASYNC */

#ifdef __O_NONBLOCK
#define FNONBLOCK __O_NONBLOCK /* Do not block when trying to read data that hasn't been written, yet. */
#define FNDELAY   __O_NONBLOCK /* Do not block when trying to read data that hasn't been written, yet. */
#endif /* __O_NONBLOCK */
#endif /* __USE_MISC */





#ifndef __USE_FILE_OFFSET64
/* [struct flock *arg] Get record locking info. */
#ifdef __F_GETLK
#define F_GETLK __F_GETLK
#endif /* __F_GETLK */

/* [struct flock const *arg] Set record locking info (non-blocking). */
#ifdef __F_SETLK
#define F_SETLK __F_SETLK
#endif /* __F_SETLK */

/* [struct flock const *arg] Set record locking info (blocking). */
#ifdef __F_SETLKW
#define F_SETLKW __F_SETLKW
#endif /* __F_SETLKW */
#else /* __USE_FILE_OFFSET64 */
/* [struct flock *arg] Get record locking info. */
#ifdef __F_GETLK64
#define F_GETLK __F_GETLK64
#endif /* __F_GETLK64 */

/* [struct flock const *arg] Set record locking info (non-blocking). */
#ifdef __F_SETLK64
#define F_SETLK __F_SETLK64
#endif /* __F_SETLK64 */

/* [struct flock const *arg] Set record locking info (blocking). */
#ifdef __F_SETLKW64
#define F_SETLKW __F_SETLKW64
#endif /* __F_SETLKW64 */
#endif /* !__USE_FILE_OFFSET64 */


#ifdef __USE_LARGEFILE64
/* [struct flock64 *arg] Get record locking info. */
#ifdef __F_GETLK64
#define F_GETLK64   __F_GETLK64
#endif /* __F_GETLK64 */

/* [struct flock64 *arg] Set record locking info (non-blocking). */
#ifdef __F_SETLK64
#define F_SETLK64   __F_SETLK64
#endif /* __F_SETLK64 */

/* [struct flock64 *arg] Set record locking info (blocking). */
#ifdef __F_SETLKW64
#define F_SETLKW64  __F_SETLKW64
#endif /* __F_SETLKW64 */
#endif /* !__USE_LARGEFILE64 */

#ifdef __USE_GNU
/* [struct flock *arg] */
#ifdef __F_OFD_GETLK
#define F_OFD_GETLK  __F_OFD_GETLK
#endif /* __F_OFD_GETLK */

/* [struct flock const *arg] */
#ifdef __F_OFD_SETLK
#define F_OFD_SETLK  __F_OFD_SETLK
#endif /* __F_OFD_SETLK */

/* [struct flock const *arg] */
#ifdef __F_OFD_SETLKW
#define F_OFD_SETLKW __F_OFD_SETLKW
#endif /* __F_OFD_SETLKW */
#endif /* __USE_GNU */


/* [void arg] Duplicate and return file descriptor. (may be used to implement `dup(2)') */
#ifdef __F_DUPFD
#define F_DUPFD __F_DUPFD
#endif /* __F_DUPFD */

/* [void arg] Get file descriptor flags.
 * @return: * : Set of `FD_CLOEXEC | FD_CLOFORK' */
#ifdef __F_GETFD
#define F_GETFD __F_GETFD
#endif /* __F_GETFD */

/* [int arg = <set of `FD_CLOEXEC', `FD_CLOFORK'>] Set file descriptor flags. */
#ifdef __F_SETFD
#define F_SETFD __F_SETFD
#endif /* __F_SETFD */

/* [void arg] Get file status flags.
 * @return: * : Set of `O_*' */
#ifdef __F_GETFL
#define F_GETFL __F_GETFL
#endif /* __F_GETFL */

/* [oflag_t arg] Set file status flags. */
#ifdef __F_SETFL
#define F_SETFL __F_SETFL
#endif /* __F_SETFL */


#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
/* [void arg] Get owner (process receiving SIGIO).
 * @return: * : The PID of the process (warning: the PID may not
 *              fit into an int and -EOVERFLOW may be returned) */
#ifdef __F_SETOWN
#define F_SETOWN __F_SETOWN
#endif /* __F_SETOWN */

/* [pid_t arg] Set owner (process receiving SIGIO). */
#ifdef __F_GETOWN
#define F_GETOWN __F_GETOWN
#endif /* __F_GETOWN */
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */


#ifdef __USE_GNU
/* [int signo] Set number of signal to be sent. */
#ifdef __F_SETSIG
#define F_SETSIG __F_SETSIG
#endif /* __F_SETSIG */

/* [void arg] Get number of signal to be sent.
 * @return: * : One of `SIG*' */
#ifdef __F_GETSIG
#define F_GETSIG __F_GETSIG
#endif /* __F_GETSIG */

/* [struct f_owner_ex *arg] Get owner (thread receiving SIGIO). */
#ifdef __F_SETOWN_EX
#define F_SETOWN_EX __F_SETOWN_EX
#endif /* __F_SETOWN_EX */

/* [struct f_owner_ex const *arg] Set owner (thread receiving SIGIO). */
#ifdef __F_GETOWN_EX
#define F_GETOWN_EX __F_GETOWN_EX
#endif /* __F_GETOWN_EX */
#endif /* __USE_GNU */


#ifdef __USE_GNU
/* [int arg = <One of `F_RDLCK', `F_WRLCK', `F_UNLCK'>] Set a lease. */
#ifdef __F_SETLEASE
#define F_SETLEASE __F_SETLEASE
#endif /* __F_SETLEASE */

/* [void arg] Enquire what lease is active.
 * @return: * : One of `F_RDLCK', `F_WRLCK', `F_UNLCK' */
#ifdef __F_GETLEASE
#define F_GETLEASE __F_GETLEASE
#endif /* __F_GETLEASE */

/* [int arg = <Set of `DN_*'>] Request notifications on a directory. */
#ifdef __F_NOTIFY
#define F_NOTIFY __F_NOTIFY
#endif /* __F_NOTIFY */

/* [unsigned int arg] Set pipe buffer size (in bytes). */
#ifdef __F_SETPIPE_SZ
#define F_SETPIPE_SZ __F_SETPIPE_SZ
#endif /* __F_SETPIPE_SZ */

/* [void arg] Get pipe buffer size (in bytes).
 * @return: * : The buffer size (in bytes) */
#ifdef __F_GETPIPE_SZ
#define F_GETPIPE_SZ __F_GETPIPE_SZ
#endif /* __F_GETPIPE_SZ */
#endif /* __USE_GNU */

#ifdef __USE_XOPEN2K8
/* [void arg] Duplicate file descriptor with close-on-exit set.
 * @[fd_t return]: * : A new FD for the same kernel object. */
#ifdef __F_DUPFD_CLOEXEC
#define F_DUPFD_CLOEXEC __F_DUPFD_CLOEXEC
#endif /* __F_DUPFD_CLOEXEC */
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_KOS
/* [int arg = <set of `FD_CLOEXEC', `FD_CLOFORK'>] Set file descriptor flags. */
#ifdef __F_SETFD
#define F_SETFD __F_SETFD
#endif /* __F_SETFD */

/* [int flags] Same as 'F_SETFL', but return the old set of flags instead of `-EOK' upon success. */
#ifdef __F_SETFL_XCH
#define F_SETFL_XCH __F_SETFL_XCH
#endif /* __F_SETFL_XCH */

/* return the next open handle id >= the given fd, or `-EBADF' if no such FD exists.
 * https://lkml.org/lkml/2012/4/1/71 */
#ifdef __F_NEXT
#define F_NEXT __F_NEXT
#endif /* __F_NEXT */
#endif /* __USE_KOS */

#if defined(__USE_KOS) || defined(__USE_NETBSD)
/* close all handles >= to the one given */
#ifdef __F_CLOSEM
#define F_CLOSEM __F_CLOSEM
#endif /* __F_CLOSEM */

/* return the max open handle id (the given fd is ignored) */
#ifdef __F_MAXFD
#define F_MAXFD __F_MAXFD
#endif /* __F_MAXFD */
#endif /* __USE_KOS || __USE_NETBSD */


#if defined(__USE_KOS) || defined(__USE_BSD)
/* Same as `dup2()' (the target FD is given as `(int)arg') */
#ifdef __F_DUP2FD
#define F_DUP2FD __F_DUP2FD
#endif /* __F_DUP2FD */

/* Same as `F_DUP2FD', but set `FD_CLOEXEC'. */
#ifdef __F_DUP2FD_CLOEXEC
#define F_DUP2FD_CLOEXEC __F_DUP2FD_CLOEXEC
#endif /* __F_DUP2FD_CLOEXEC */
#endif /* __USE_KOS || __USE_BSD */


/* FLAG: Close the descriptor on `exec()'. */
#ifdef __FD_CLOEXEC
#define FD_CLOEXEC __FD_CLOEXEC
#endif /* __FD_CLOEXEC */

#ifdef __USE_KOS
/* FLAG: Close the descriptor during unsharing after `fork()' (Similar to `PROT_LOOSE' for memory). */
#ifdef __FD_CLOFORK
#define FD_CLOFORK __FD_CLOFORK
#endif /* __FD_CLOFORK */
#endif /* __USE_KOS */

/* Read lock. */
#ifdef __F_RDLCK
#define F_RDLCK __F_RDLCK
#endif /* __F_RDLCK */

/* Write lock. */
#ifdef __F_WRLCK
#define F_WRLCK __F_WRLCK
#endif /* __F_WRLCK */

/* Remove lock. */
#ifdef __F_UNLCK
#define F_UNLCK __F_UNLCK
#endif /* __F_UNLCK */

/* TODO: DOC */
#ifdef __F_EXLCK
#define F_EXLCK __F_EXLCK
#endif /* __F_EXLCK */

/* TODO: DOC */
#ifdef __F_SHLCK
#define F_SHLCK __F_SHLCK
#endif /* __F_SHLCK */



#ifdef __USE_MISC
/* Shared lock. */
#ifdef __LOCK_SH
#define LOCK_SH __LOCK_SH
#endif /* __LOCK_SH */

/* Exclusive lock. */
#ifdef __LOCK_EX
#define LOCK_EX __LOCK_EX
#endif /* __LOCK_EX */

/* Or'd with one of the above to prevent blocking. */
#ifdef __LOCK_NB
#define LOCK_NB __LOCK_NB
#endif /* __LOCK_NB */

/* Remove lock. */
#ifdef __LOCK_UN
#define LOCK_UN __LOCK_UN
#endif /* __LOCK_UN */
#endif /* __USE_MISC */



#ifdef __USE_XOPEN2K
/* No further special treatment. */
#ifdef __POSIX_FADV_NORMAL
#define POSIX_FADV_NORMAL __POSIX_FADV_NORMAL
#endif /* __POSIX_FADV_NORMAL */

/* Expect random page references. */
#ifdef __POSIX_FADV_RANDOM
#define POSIX_FADV_RANDOM __POSIX_FADV_RANDOM
#endif /* __POSIX_FADV_RANDOM */

/* Expect sequential page references. */
#ifdef __POSIX_FADV_SEQUENTIAL
#define POSIX_FADV_SEQUENTIAL __POSIX_FADV_SEQUENTIAL
#endif /* __POSIX_FADV_SEQUENTIAL */

/* Will need these pages. */
#ifdef __POSIX_FADV_WILLNEED
#define POSIX_FADV_WILLNEED __POSIX_FADV_WILLNEED
#endif /* __POSIX_FADV_WILLNEED */

/* Don't need these pages. */
#ifdef __POSIX_FADV_DONTNEED
#define POSIX_FADV_DONTNEED __POSIX_FADV_DONTNEED
#endif /* __POSIX_FADV_DONTNEED */

/* Data will be accessed once. */
#ifdef __POSIX_FADV_NOREUSE
#define POSIX_FADV_NOREUSE __POSIX_FADV_NOREUSE
#endif /* __POSIX_FADV_NOREUSE */
#endif /* !__USE_XOPEN2K */



#ifdef __USE_GNU
/* This is a mandatory flock: */
#ifdef __LOCK_MAND
#define LOCK_MAND __LOCK_MAND
#endif /* __LOCK_MAND */

/* ... which allows concurrent read operations. */
#ifdef __LOCK_READ
#define LOCK_READ __LOCK_READ
#endif /* __LOCK_READ */

/* ... which allows concurrent write operations. */
#ifdef __LOCK_WRITE
#define LOCK_WRITE __LOCK_WRITE
#endif /* __LOCK_WRITE */

/* ... Which allows concurrent read & write operations. */
#ifdef __LOCK_RW
#define LOCK_RW __LOCK_RW
#endif /* __LOCK_RW */

/* File accessed. */
#ifdef __DN_ACCESS
#define DN_ACCESS __DN_ACCESS
#endif /* __DN_ACCESS */

/* File modified. */
#ifdef __DN_MODIFY
#define DN_MODIFY __DN_MODIFY
#endif /* __DN_MODIFY */

/* File created. */
#ifdef __DN_CREATE
#define DN_CREATE __DN_CREATE
#endif /* __DN_CREATE */

/* File removed. */
#ifdef __DN_DELETE
#define DN_DELETE __DN_DELETE
#endif /* __DN_DELETE */

/* File renamed. */
#ifdef __DN_RENAME
#define DN_RENAME __DN_RENAME
#endif /* __DN_RENAME */

/* File changed attributes. */
#ifdef __DN_ATTRIB
#define DN_ATTRIB __DN_ATTRIB
#endif /* __DN_ATTRIB */

/* Don't remove notifier. */
#ifdef __DN_MULTISHOT
#define DN_MULTISHOT __DN_MULTISHOT
#endif /* __DN_MULTISHOT */


#if (defined(__F_OWNER_TID) || defined(__F_OWNER_PID) || \
     defined(__F_OWNER_PGRP) || defined(__F_OWNER_GID))
/*[[[enum]]]*/
#ifdef __CC__
enum __pid_type {
#ifdef __F_OWNER_TID
	F_OWNER_TID  = __F_OWNER_TID,  /* Kernel thread. */
#endif /* __F_OWNER_TID */
#ifdef __F_OWNER_PID
	F_OWNER_PID  = __F_OWNER_PID,  /* Process. */
#endif /* __F_OWNER_PID */
#ifdef __F_OWNER_PGRP
	F_OWNER_PGRP = __F_OWNER_PGRP, /* Process group. */
#endif /* __F_OWNER_PGRP */
#ifdef __F_OWNER_GID
	F_OWNER_GID  = __F_OWNER_GID   /* Alternative, obsolete name. */
#endif /* __F_OWNER_GID */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __F_OWNER_TID
#define F_OWNER_TID  F_OWNER_TID  /* Kernel thread. */
#endif /* __F_OWNER_TID */
#ifdef __F_OWNER_PID
#define F_OWNER_PID  F_OWNER_PID  /* Process. */
#endif /* __F_OWNER_PID */
#ifdef __F_OWNER_PGRP
#define F_OWNER_PGRP F_OWNER_PGRP /* Process group. */
#endif /* __F_OWNER_PGRP */
#ifdef __F_OWNER_GID
#define F_OWNER_GID  F_OWNER_GID  /* Alternative, obsolete name. */
#endif /* __F_OWNER_GID */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __F_OWNER_TID
#define F_OWNER_TID  __F_OWNER_TID  /* Kernel thread. */
#endif /* __F_OWNER_TID */
#ifdef __F_OWNER_PID
#define F_OWNER_PID  __F_OWNER_PID  /* Process. */
#endif /* __F_OWNER_PID */
#ifdef __F_OWNER_PGRP
#define F_OWNER_PGRP __F_OWNER_PGRP /* Process group. */
#endif /* __F_OWNER_PGRP */
#ifdef __F_OWNER_GID
#define F_OWNER_GID  __F_OWNER_GID  /* Alternative, obsolete name. */
#endif /* __F_OWNER_GID */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* __F_OWNER_TID || __F_OWNER_PID || __F_OWNER_PGRP || __F_OWNER_GID */

/* Wait upon writeout of all pages in the range before performing the write. */
#ifdef __SYNC_FILE_RANGE_WAIT_BEFORE
#define SYNC_FILE_RANGE_WAIT_BEFORE __SYNC_FILE_RANGE_WAIT_BEFORE
#endif /* __SYNC_FILE_RANGE_WAIT_BEFORE */

/* Initiate writeout of all those dirty pages in the range which are not presently under writeback. */
#ifdef __SYNC_FILE_RANGE_WRITE
#define SYNC_FILE_RANGE_WRITE __SYNC_FILE_RANGE_WRITE
#endif /* __SYNC_FILE_RANGE_WRITE */

/* Wait upon writeout of all pages in the range after performing the write. */
#ifdef __SYNC_FILE_RANGE_WAIT_AFTER
#define SYNC_FILE_RANGE_WAIT_AFTER __SYNC_FILE_RANGE_WAIT_AFTER
#endif /* __SYNC_FILE_RANGE_WAIT_AFTER */

/* Move pages instead of copying. */
#ifdef __SPLICE_F_MOVE
#define SPLICE_F_MOVE __SPLICE_F_MOVE
#endif /* __SPLICE_F_MOVE */

/* Don't block on the pipe splicing (but we may still block on the fd we splice from/to). */
#ifdef __SPLICE_F_NONBLOCK
#define SPLICE_F_NONBLOCK __SPLICE_F_NONBLOCK
#endif /* __SPLICE_F_NONBLOCK */

/* Expect more data. */
#ifdef __SPLICE_F_MORE
#define SPLICE_F_MORE __SPLICE_F_MORE
#endif /* __SPLICE_F_MORE */

/* Pages passed in are a gift. */
#ifdef __SPLICE_F_GIFT
#define SPLICE_F_GIFT __SPLICE_F_GIFT
#endif /* __SPLICE_F_GIFT */

/* Don't extend size of file even if offset + len is greater than file size. */
#ifdef __FALLOC_FL_KEEP_SIZE
#define FALLOC_FL_KEEP_SIZE __FALLOC_FL_KEEP_SIZE
#endif /* __FALLOC_FL_KEEP_SIZE */
/* Create a hole in the file. */
#ifdef __FALLOC_FL_PUNCH_HOLE
#define FALLOC_FL_PUNCH_HOLE __FALLOC_FL_PUNCH_HOLE
#endif /* __FALLOC_FL_PUNCH_HOLE */
/* Remove a range of a file without leaving a hole. */
#ifdef __FALLOC_FL_COLLAPSE_RANGE
#define FALLOC_FL_COLLAPSE_RANGE __FALLOC_FL_COLLAPSE_RANGE
#endif /* __FALLOC_FL_COLLAPSE_RANGE */
/* Convert a range of a file to zeros. */
#ifdef __FALLOC_FL_ZERO_RANGE
#define FALLOC_FL_ZERO_RANGE __FALLOC_FL_ZERO_RANGE
#endif /* __FALLOC_FL_ZERO_RANGE */

#ifdef __MAX_HANDLE_SZ
#define MAX_HANDLE_SZ    __MAX_HANDLE_SZ
#endif /* __MAX_HANDLE_SZ */
#endif /* __USE_GNU */



#ifdef __USE_ATFILE

/* Special value used to indicate the *at functions
 * should use the current working directory. */
#ifdef __AT_FDCWD
#define AT_FDCWD  __AT_FDCWD
#endif /* __AT_FDCWD */

/* If the last path component is a symlink, don't follow it. */
#ifdef __AT_SYMLINK_NOFOLLOW
#define AT_SYMLINK_NOFOLLOW __AT_SYMLINK_NOFOLLOW
#endif /* __AT_SYMLINK_NOFOLLOW */

/* Remove directory instead of unlinking file. */
#ifdef __AT_REMOVEDIR
#define AT_REMOVEDIR __AT_REMOVEDIR
#endif /* __AT_REMOVEDIR */

/* Test access permitted for effective IDs, not real IDs. */
#ifdef __AT_EACCESS
#define AT_EACCESS __AT_EACCESS
#endif /* __AT_EACCESS */

/* If the last path component is a symlink, follow it. (WARNING: Only used by `linkat(2)') */
#ifdef __AT_SYMLINK_FOLLOW
#define AT_SYMLINK_FOLLOW __AT_SYMLINK_FOLLOW
#endif /* __AT_SYMLINK_FOLLOW */

#if defined(__USE_GNU) || defined(__USE_KOS_KERNEL)
/* Suppress terminal automount traversal. */
#ifdef __AT_NO_AUTOMOUNT
#define AT_NO_AUTOMOUNT __AT_NO_AUTOMOUNT
#endif /* __AT_NO_AUTOMOUNT */

/* Allow empty relative pathname. */
#ifdef __AT_EMPTY_PATH
#define AT_EMPTY_PATH __AT_EMPTY_PATH
#endif /* __AT_EMPTY_PATH */
#endif /* __USE_GNU || __USE_KOS_KERNEL */

#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
/* Treat symbolic links similar to like regular files and throw
 * an `ERROR_FS_TOO_MANY_LINKS' error during the first encounter. */
#ifdef __AT_SYMLINK_REGULAR
#define AT_SYMLINK_REGULAR __AT_SYMLINK_REGULAR
#endif /* __AT_SYMLINK_REGULAR */

/* For use with `utimensat' and friends: Take `struct timespec[3]', where the 3rd entry
 * (when not equal to `UTIME_OMIT') is used to override the file creation timestamp.
 * NOTE: Passing this flag when the 3rd timespec isn't set to `UTIME_OMIT' requires
 *       that the calling thread be holding the `CAP_SYS_TIME' permission and be the
 *       owner of the file in question, or to be holding the `CAP_FOWNER' permission.
 *       Less permissions are required when `UTIME_NOW' is passed, in which case
 *      `CAP_SYS_TIME' is not required (similarly how having `CAP_FOWNER', or being
 *       the owner would allow you to copy the file (updating the timestamp), then
 *       replacing the original)
 * NOTE: This flag is used to implement full compatibility with NT's SetFileTime function. */
#ifdef __AT_CHANGE_CTIME
#define AT_CHANGE_CTIME __AT_CHANGE_CTIME
#endif /* __AT_CHANGE_CTIME */

/* For use with `freadlinkat' and friends.
 * Rather than following unix semantics and returning the amount of
 * copied bytes with no indication of whether or not everything was
 * copied, return the ~required~ buffer size (including a terminating
 * NUL-character that normally wouldn't be copied either) to user-space
 * (which may be more than the specified buffer size, which should be
 * reallocated to fit in successive calls)
 * Additionally, as already mentioned, a trailing NUL-character is
 * appended to the link text, ensuring that a valid C-style string
 * can be read so long as the provided buffer was of sufficient size. */
#ifdef __AT_READLINK_REQSIZE
#define AT_READLINK_REQSIZE __AT_READLINK_REQSIZE
#endif /* __AT_READLINK_REQSIZE */

/* Explicitly allow removing anything that unlink() removes. (Default;
 * Set in addition to `AT_REMOVEDIR' to implement `remove()' semantics
 * as an atomic kernel operation, removing any race condition that the
 * alternative of `if (unlink(x) && errno == EISDIR) rmdir(x)' would
 * introduce). */
#ifdef __AT_REMOVEREG
#define AT_REMOVEREG __AT_REMOVEREG
#endif /* __AT_REMOVEREG */

/* For `frealpath4' / `frealpathat': the specified path should
 * be printed as the reverse of the `AT_DOSPATH' flag:
 *  - 0                      : in:UNIX  out:UNIX
 *  - AT_DOSPATH             : in:DOS   out:DOS
 *  - AT_ALTPATH             : in:UNIX  out:DOS
 *  - AT_ALTPATH | AT_DOSPATH: in:DOS   out:UNIX */
#ifdef __AT_ALTPATH
#define AT_ALTPATH __AT_ALTPATH
#endif /* __AT_ALTPATH */

#ifdef __USE_KOS_KERNEL
/* Used internally by the kernel: Delete a mounting point. (Userspace must use `unmount()') */
#ifdef __AT_REMOVEMNT
#define AT_REMOVEMNT __AT_REMOVEMNT
#endif /* __AT_REMOVEMNT */
#endif /* __USE_KOS_KERNEL */

/* Interpret '\\' as '/', and ignore casing during path resolution.
 * Additionally, recognize `<LETTER>:'-style drive prefixes, as well
 * as make use of per-drive working directories, as well as drive-relative
 * path names that start with a leading slash.
 * Basically, when set: perform the system call in DOS-compatibility mode.
 * HINT: This flag can be specified with the `fsmode()' system call. */
#ifdef __AT_DOSPATH
#define AT_DOSPATH __AT_DOSPATH
#endif /* __AT_DOSPATH */

/* Same as `AT_FDCWD' but sets the filesystem root
 * (using this, you can `chroot()' with 'dup2()'!) */
#ifdef __AT_FDROOT
#define AT_FDROOT __AT_FDROOT
#endif /* __AT_FDROOT */

/* Special, symbolic file numbers.
 * These descriptors cannot be overwritten,
 * and their meaning is context-sensible. */
#ifdef __AT_THIS_TASK
#define AT_THIS_TASK __AT_THIS_TASK
#endif /* __AT_THIS_TASK */
#ifdef __AT_THIS_MMAN
#define AT_THIS_MMAN __AT_THIS_MMAN   /* DEPRECATED */
#endif /* __AT_THIS_MMAN */
#ifdef __AT_THIS_STACK
#define AT_THIS_STACK __AT_THIS_STACK /* DEPRECATED */
#endif /* __AT_THIS_STACK */

/* HANDLE_TYPE_TASK (writable, Equivalent of `getpid()') */
#ifdef __AT_THIS_PROCESS
#define AT_THIS_PROCESS __AT_THIS_PROCESS
#endif /* __AT_THIS_PROCESS */

/* HANDLE_TYPE_TASK (writable, Equivalent of `getppid()') */
#ifdef __AT_PARENT_PROCESS
#define AT_PARENT_PROCESS __AT_PARENT_PROCESS
#endif /* __AT_PARENT_PROCESS */

/* HANDLE_TYPE_TASK (writable, Equivalent of `getpgid(0)') */
#ifdef __AT_GROUP_LEADER
#define AT_GROUP_LEADER __AT_GROUP_LEADER
#endif /* __AT_GROUP_LEADER */

/* HANDLE_TYPE_TASK (writable, Equivalent of `getsid(0)') */
#ifdef __AT_SESSION_LEADER
#define AT_SESSION_LEADER __AT_SESSION_LEADER
#endif /* __AT_SESSION_LEADER */


/* DOS Drive root / current-working paths.
 * These are special file descriptors that can be written to using `dup2()',
 * where they expect to receive either a FILE or PATH descriptor.
 * Once set, these paths describe the root-paths of DOS's drives:
 * >> // Force DOS filesystem semantics for all filesystem operations.
 * >> struct fsmask mask = {0,0};
 * >> mask = fsmode(mask);
 * >> mask.fm_mask &= ~AT_DOSPATH;
 * >> mask.fm_mode |=  AT_DOSPATH;
 * >> fsmode(mask);
 * >>
 * >> // Mount some filesystem locations as DOS drives.
 * >> dup2(open("/"), AT_FDDRIVE_ROOT('C'));
 * >> dup2(open("/bin"), AT_FDDRIVE_ROOT('D'));
 * >> dup2(open("/home"), AT_FDDRIVE_ROOT('E'));
 * >>
 * >> // Open a file on a dos-path.
 * >> open("D:\\ls"); // open("/bin/ls")
 * >>
 * >> // Explicitly set the current-working directory of a specific drive.
 * >> // NOTE: Requires that the opened path be reachable from `AT_FDDRIVE_ROOT('E')'
 * >> //       If it isn't, an `ERROR_FS_CROSSDEVICE_LINK' error is thrown.
 * >> dup2(open("/home/me/Downloads"), AT_FDDRIVE_CWD('E'));
 * >>
 * >> chdir("C:\\bin"); // AT_FDCWD = "/bin"; AT_FDDRIVE_CWD('C') = AT_FDCWD;
 * >> chdir("E:");      // AT_FDCWD = AT_FDDRIVE_CWD('E'); (`/home/me/Downloads')
 * >> chdir("E:\\");    // AT_FDCWD = "/home"; AT_FDDRIVE_CWD('E') = AT_FDCWD;
 * >> chdir("C:");      // AT_FDCWD = AT_FDDRIVE_CWD('C'); (`/bin')
 * >> chdir("D:\\");    // AT_FDCWD = "/bin"; AT_FDDRIVE_CWD('D') = AT_FDCWD;
 * >> chdir("..");      // AT_FDCWD = "/bin"; AT_FDDRIVE_CWD('D') = AT_FDCWD; (Don't escape the current drive)
 * >>
 * NOTES:
 *   - Setting the root-path of a drive will not update the drive working directories of processes sharing VFS.
 *     With that in mind, you should not re-mount a DOS drive as a sub-directory of where
 *     it was located before then, unless you first unshared your VFS (using `CLONE_NEWNS').
 *     Allowing a program's current working directory to be located outside the associated
 *     drive causes weak undefined behavior. In KOS this means:
 *       - `xfdname()' will not produce the correct path
 *       - Relative path names still operate on the old directory
 *       - Navigating into parent directories is no longer restricted (except by `chroot()')
 *       - Manually navigating into a portion of the new drives mounting point fixes the problem.
 *   - DOS drive mounting points are beneath UNIX mounting points, in that they don't
 *     actually mount a superblock to some filesystem location, but rather mirror a
 *     filesystem path, meaning that DOS drives can be thought of as the equivalent
 *     of the `dfd' argument of `*at' system calls:
 *     >> open("C:\\foo.txt"); // Same as `openat(AT_FDDRIVE_ROOT('C'), "foo.txt")'
 *     If `mount()' is used to create a new (real) mounting point, it will appear
 *     in all DOS drives that are mounting the location where the mount happened,
 *     or any location further up the tree immediately (it's the same data object
 *     internally; DOS drives are merely aliasing regular paths; aka. `O_PATH')
 *   - To ~unmount~ (quote-unquote) a DOS drive, simply close() the associated root file descriptor:
 *     >> // Unmount `C:' (also closes the associated FDCWD descriptor)
 *     >> close(AT_FDDRIVE_ROOT('C'));
 *   - Mounting, or unmounting dos drives requires the same privileges as the `mount()' and `umount()' system calls.
 *   - Closing an `AT_FDDRIVE_CWD()' descriptor will revert it to match the root path of the associated drive.
 *     >> close(AT_FDDRIVE_CWD('C'));
 *     >> // Same as:
 *     >> dup2(AT_FDDRIVE_ROOT('C'),AT_FDDRIVE_CWD('C'));
 *   - Symbolic links are evaluated the same as any user-provided path.
 *     If a symbolic link starts with a '/' or '\\' character, the remainder
 *     of its text is relative to the first DOS drive mounting point
 *     encountered while walking up the chain of parent directories. */
#ifdef __AT_FDDRIVE_CWD
#define AT_FDDRIVE_CWD(drivechar) __AT_FDDRIVE_CWD(drivechar)
#endif /* __AT_FDDRIVE_CWD */
#ifdef __AT_FDDRIVE_ROOT
#define AT_FDDRIVE_ROOT(drivechar) __AT_FDDRIVE_ROOT(drivechar)
#endif /* __AT_FDDRIVE_ROOT */
#ifdef __AT_DOS_DRIVEMIN
#define AT_DOS_DRIVEMIN __AT_DOS_DRIVEMIN
#endif /* __AT_DOS_DRIVEMIN */
#ifdef __AT_DOS_DRIVEMAX
#define AT_DOS_DRIVEMAX __AT_DOS_DRIVEMAX
#endif /* __AT_DOS_DRIVEMAX */
#endif /* __USE_KOS */
#endif /* __USE_ATFILE */



#ifdef __USE_DOS
/* DOS extension flags. */
#ifdef __CRT_DOS_PRIMARY
#define O_RAW           __DOS_O_RAW
#define O_TEXT          __DOS_O_TEXT
#define O_BINARY        __DOS_O_BINARY
#define O_SEQUENTIAL    __DOS_O_SEQUENTIAL
#define O_RANDOM        __DOS_O_RANDOM
#define _O_SHORT_LIVED  __DOS_O_SHORT_LIVED
#define _O_U16TEXT      __DOS_O_U16TEXT
#define _O_U8TEXT       __DOS_O_U8TEXT
#define _O_WTEXT        __DOS_O_WTEXT
#define _O_OBTAIN_DIR   __DOS_O_OBTAIN_DIR
#define O_TEMPORARY     __DOS_O_TEMPORARY
#define _O_TEMPORARY    __DOS_O_TEMPORARY
#else /* __CRT_DOS_PRIMARY */
#define O_RAW           0
#define O_TEXT          0
#define O_BINARY        0
#define O_SEQUENTIAL    0
#define O_RANDOM        0
#define _O_SHORT_LIVED  0
#define _O_U16TEXT      0
#define _O_U8TEXT       0
#define _O_WTEXT        0
#define _O_OBTAIN_DIR   0 /* Not the same as `O_DIRECTORY'! (quite the opposite actually) */
#endif /* !__CRT_DOS_PRIMARY */

/* DOS name aliases */
#ifdef __O_RDONLY
#define _O_RDONLY __O_RDONLY
#endif /* __O_RDONLY */

#ifdef __O_WRONLY
#define _O_WRONLY __O_WRONLY
#endif /* __O_WRONLY */

#ifdef __O_RDWR
#define _O_RDWR __O_RDWR
#endif /* __O_RDWR */

#ifdef __O_APPEND
#define _O_APPEND __O_APPEND
#endif /* __O_APPEND */

#ifdef __O_CREAT
#define _O_CREAT __O_CREAT
#endif /* __O_CREAT */

#ifdef __O_EXCL
#define _O_EXCL __O_EXCL
#endif /* __O_EXCL */

#ifdef __O_TRUNC
#define _O_TRUNC __O_TRUNC
#endif /* __O_TRUNC */

#ifdef __O_CLOEXEC
#define O_NOINHERIT __O_CLOEXEC
#define _O_NOINHERIT __O_CLOEXEC
#endif /* __O_CLOEXEC */

#define _O_BINARY O_BINARY
#define _O_RANDOM O_RANDOM
#define _O_RAW O_RAW
#define _O_SEQUENTIAL O_SEQUENTIAL
#define _O_TEXT O_TEXT

#ifndef _O_TEMPORARY
/* XXX: Figure out exactly what `O_TEMPORARY' does,
 *      and check if it matches linux's `O_TMPFILE' */
//#define _O_TEMPORARY    __O_TMPFILE
//#define O_TEMPORARY     __O_TMPFILE
#endif /* !_O_TEMPORARY */
#endif /* __USE_DOS */





#ifdef __O_TMPFILE
#define __OPEN_NEEDS_MODE(oflags) (((oflags) & O_CREAT) || ((oflags) & __O_TMPFILE) == __O_TMPFILE)
#else /* __O_TMPFILE */
#define __OPEN_NEEDS_MODE(oflags) ((oflags) & O_CREAT)
#endif /* !__O_TMPFILE */

/* For XPG all symbols from <sys/stat.h> should also be available. */
#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#if !defined(S_IFMT) && defined(__S_IFMT)
#define S_IFMT  __S_IFMT /* These bits determine file type. */
#endif /* !S_IFMT && __S_IFMT */
#if !defined(S_IFDIR) && defined(__S_IFDIR)
#define S_IFDIR __S_IFDIR /* Directory. */
#endif /* !S_IFDIR && __S_IFDIR */
#if !defined(S_IFCHR) && defined(__S_IFCHR)
#define S_IFCHR __S_IFCHR /* Character device. */
#endif /* !S_IFCHR && __S_IFCHR */
#if !defined(S_IFBLK) && defined(__S_IFBLK)
#define S_IFBLK __S_IFBLK /* Block device. */
#endif /* !S_IFBLK && __S_IFBLK */
#if !defined(S_IFREG) && defined(__S_IFREG)
#define S_IFREG __S_IFREG /* Regular file. */
#endif /* !S_IFREG && __S_IFREG */
#if !defined(S_IFIFO) && defined(__S_IFIFO)
#define S_IFIFO __S_IFIFO /* FIFO. */
#endif /* !S_IFIFO && __S_IFIFO */
#if !defined(S_IFLNK) && defined(__S_IFLNK)
#define S_IFLNK __S_IFLNK /* Symbolic link. */
#endif /* !S_IFLNK && __S_IFLNK */
#if ((defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)) && \
     (!defined(S_IFSOCK) && defined(__S_IFSOCK)))
#define S_IFSOCK __S_IFSOCK /* Socket. */
#endif /* (__USE_UNIX98 || __USE_XOPEN2K8) && (!S_IFSOCK && __S_IFSOCK) */
#if !defined(S_ISUID) && defined(__S_ISUID)
#define S_ISUID __S_ISUID /* Set user ID on execution. */
#endif /* !S_ISUID && __S_ISUID */
#if !defined(S_ISGID) && defined(__S_ISGID)
#define S_ISGID __S_ISGID /* Set group ID on execution. */
#endif /* !S_ISGID && __S_ISGID */
#if ((defined(__USE_MISC) || defined(__USE_XOPEN)) && \
     (!defined(S_ISVTX) && defined(__S_ISVTX)))
#define S_ISVTX __S_ISVTX /* Save swapped text after use (sticky). */
#endif /* (__USE_MISC || __USE_XOPEN) && (!S_ISVTX && __S_ISVTX) */

#ifndef S_IRUSR
#define S_IRUSR 0400 /* Read by owner. */
#define S_IWUSR 0200 /* Write by owner. */
#define S_IXUSR 0100 /* Execute by owner. */
#define S_IRWXU 0700
#define S_IRGRP 0040 /* Read by group. */
#define S_IWGRP 0020 /* Write by group. */
#define S_IXGRP 0010 /* Execute by group. */
#define S_IRWXG 0070
#define S_IROTH 0004 /* Read by others. */
#define S_IWOTH 0002 /* Write by others. */
#define S_IXOTH 0001 /* Execute by others. */
#define S_IRWXO 0007
#endif /* !S_IRWXO */
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */


#ifdef __USE_MISC
#if !defined(R_OK) && defined(__R_OK)
#define R_OK __R_OK /* Test for read permission. */
#endif /* !R_OK && __R_OK */
#if !defined(W_OK) && defined(__W_OK)
#define W_OK __W_OK /* Test for write permission. */
#endif /* !W_OK && __W_OK */
#if !defined(X_OK) && defined(__X_OK)
#define X_OK __X_OK /* Test for execute permission. */
#endif /* !X_OK && __X_OK */
#if !defined(F_OK) && defined(__F_OK)
#define F_OK __F_OK /* Test for existence. */
#endif /* !F_OK && __F_OK */
#endif /* __USE_MISC */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#ifndef SEEK_SET
#define SEEK_SET __SEEK_SET /* Seek from beginning of file. */
#define SEEK_CUR __SEEK_CUR /* Seek from current position. */
#define SEEK_END __SEEK_END /* Seek from end of file. */
#ifdef __USE_GNU
#ifdef __SEEK_DATA
#define SEEK_DATA __SEEK_DATA /* Seek to next data. */
#endif /* __SEEK_DATA */
#ifdef __SEEK_HOLE
#define SEEK_HOLE __SEEK_HOLE /* Seek to next hole. */
#endif /* __SEEK_HOLE */
#endif /* __USE_GNU */
#endif /* !SEEK_SET */
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */


#ifdef __CC__

}



%#ifdef __USE_GNU
[[userimpl, decl_include("<bits/types.h>")]]
readahead:($fd_t fd, $off64_t offset, $size_t count) -> $ssize_t {
	(void)fd;
	(void)offset;
	return count;
}

[[userimpl, decl_include("<bits/types.h>")]]
int sync_file_range($fd_t fd, $off64_t offset, $off64_t count, unsigned int flags) {
	(void)fd;
	(void)offset;
	(void)count;
	(void)flags;
	return 0;
}

%struct iovec;

[[cp, decl_include("<bits/types.h>")]]
$ssize_t vmsplice($fd_t fdout, struct iovec const *iov, $size_t count, unsigned int flags);
[[cp, decl_include("<bits/types.h>")]]
$ssize_t splice($fd_t fdin, $off64_t *offin, $fd_t fdout, $off64_t *offout, $size_t length, unsigned int flags);
[[cp, decl_include("<bits/types.h>")]]
$ssize_t tee($fd_t fdin, $fd_t fdout, $size_t length, unsigned int flags);
[[cp, decl_include("<bits/types.h>")]]
int name_to_handle_at($fd_t dirfd, char const *name, struct file_handle *handle, int *mnt_id, int flags);
[[cp, decl_include("<bits/types.h>")]]
$fd_t open_by_handle_at($fd_t mountdirfd, struct file_handle *handle, int flags);

[[ignore, nocrt, alias(fallocate), decl_include("<bits/types.h>")]]
int fallocate32($fd_t fd, int mode, $off64_t offset, $off64_t length);

[[if(defined(__USE_FILE_OFFSET64)), preferred_alias(fallocate64)]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(fallocate)]]
[[userimpl, decl_include("<features.h>", "<bits/types.h>"), no_crt_self_import]]
int fallocate($fd_t fd, int mode, $off_t offset, $off_t length) {
@@pp_if $has_function(fallocate64)@@
	return fallocate64(fd, mode, ($off64_t)offset, ($off64_t)length);
@@pp_elif $has_function(fallocate32)@@
	return fallocate32(fd, mode, ($off32_t)offset, ($off32_t)length);
@@pp_else@@
	(void)fd;
	(void)mode;
	(void)offset;
	(void)length;
	return 0;
@@pp_endif@@
}

%#ifdef __USE_LARGEFILE64
[[userimpl, off64_variant_of(fallocate), decl_include("<bits/types.h>")]]
int fallocate64($fd_t fd, int mode, $off64_t offset, $off64_t length) {
@@pp_if $has_function(fallocate32)@@
	return fallocate32(fd, mode, ($off32_t)offset, ($off32_t)length);
@@pp_else@@
	(void)fd;
	(void)mode;
	(void)offset;
	(void)length;
	return 0;
@@pp_endif@@
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_GNU */


[[decl_include("<features.h>", "<bits/types.h>")]]
[[vartypes(void *), guard, export_alias("__fcntl")]]
__STDC_INT_AS_SSIZE_T fcntl($fd_t fd, int cmd, ...);

%[default:section(".text.crt{|.dos}.io.access")]

[[ignore, vartypes($mode_t), decl_include("<bits/types.h>")]]
[[nocrt, alias(open, _open, __open), cp, wunused]]
$fd_t open32([[nonnull]] char const *filename, $oflag_t oflags, ...);


[[cp, guard, wunused, vartypes($mode_t), no_crt_self_import]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("open64")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("open", "_open", "__open")]]
[[decl_include("<bits/types.h>"), export_as("__open")]]
[[crt_dos_variant, dos_export_as("DOS$_open")]]
[[userimpl, requires($has_function(open64) || (defined(__CRT_AT_FDCWD) && $has_function(openat)))]]
$fd_t open([[nonnull]] char const *filename, $oflag_t oflags, ...) {
	$fd_t result;
	va_list args;
	va_start(args, oflags);
@@pp_if $has_function(open64)@@
	result = open64(filename, oflags, va_arg(args, mode_t));
@@pp_else@@
	result = openat(__CRT_AT_FDCWD, filename, oflags, va_arg(args, mode_t));
@@pp_endif@@
	va_end(args);
	return result;
}

[[cp, guard, wunused, no_crt_self_import]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("creat64")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("creat", "_creat")]]
[[crt_dos_variant, dos_export_as("DOS$_creat")]]
[[alias("creat", "_creat", "creat64")]]
[[userimpl, requires_function(creat64, open)]]
[[impl_include("<asm/fcntl.h>"), decl_include("<bits/types.h>")]]
$fd_t creat([[nonnull]] char const *filename, $mode_t mode) {
	return open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode);
}

%
%#ifdef __USE_LARGEFILE64
[[vartypes($mode_t), export_alias("__open64"), largefile64_variant_of(open)]]
[[decl_include("<bits/types.h>"), impl_include("<asm/fcntl.h>")]]
[[if(!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0), alias("open", "_open")]]
[[cp, wunused, crt_dos_variant, userimpl, requires_function(open32)]]
$fd_t open64([[nonnull]] char const *filename, $oflag_t oflags, ...) {
	$fd_t result;
	va_list args;
	mode_t mode;
	va_start(args, oflags);
	mode = va_arg(args, mode_t);
@@pp_ifdef O_LARGEFILE@@
	result = open32(filename, oflags | O_LARGEFILE, mode);
@@pp_else@@
	result = open32(filename, oflags, mode);
@@pp_endif@@
	va_end(args);
	return result;
}

[[guard, largefile64_variant_of(creat)]]
[[decl_include("<bits/types.h>"), impl_include("<asm/fcntl.h>")]]
[[if(!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0), alias("creat", "_creat")]]
[[cp, wunused, userimpl, crt_dos_variant, requires_function(open64)]]
$fd_t creat64([[nonnull]] char const *filename, $mode_t mode) {
	return open64(filename, O_CREAT | O_WRONLY | O_TRUNC, mode);
}
%#endif /* __USE_LARGEFILE64 */
%
%#ifdef __USE_ATFILE

[[cp, ignore, nocrt, alias("openat")]]
[[wunused, vartypes($mode_t), decl_include("<bits/types.h>")]]
$fd_t openat32($fd_t dirfd, [[nonnull]] char const *filename, $oflag_t oflags, ...);

[[cp, wunused, guard, vartypes($mode_t), no_crt_self_import]]
[[decl_include("<bits/types.h>")]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("openat64")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("openat")]]
[[crt_dos_variant, userimpl, requires_function(openat64)]]
$fd_t openat($fd_t dirfd, [[nonnull]] char const *filename, $oflag_t oflags, ...) {
	$fd_t result;
	va_list args;
	va_start(args, oflags);
	result = openat64(dirfd, filename, oflags, va_arg(args, mode_t));
	va_end(args);
	return result;
}

%#ifdef __USE_LARGEFILE64
[[cp, wunused, guard, vartypes($mode_t)]]
[[decl_include("<bits/types.h>"), largefile64_variant_of(openat)]]
[[crt_dos_variant, userimpl, requires_function(openat32)]]
$fd_t openat64($fd_t dirfd, [[nonnull]] char const *filename, $oflag_t oflags, ...) {
	fd_t result;
	va_list args;
	mode_t mode;
	va_start(args, oflags);
	mode = va_arg(args, mode_t);
#ifdef O_LARGEFILE
	result = openat32(dirfd, filename, oflags | O_LARGEFILE, mode);
#else /* O_LARGEFILE */
	result = openat32(dirfd, filename, oflags, mode);
#endif /* !O_LARGEFILE */
	va_end(args);
	return result;
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_ATFILE */
%
%#ifdef __USE_XOPEN2K

[[decl_include("<bits/types.h>"), ignore, nocrt, alias("posix_fadvise")]]
int posix_fadvise32($fd_t fd, $off32_t offset, $off32_t length, int advise);


[[decl_include("<features.h>", "<bits/types.h>"), no_crt_self_import]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("posix_fadvise64")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("posix_fadvise")]]
[[userimpl, section(".text.crt{|.dos}.io.utility")]]
int posix_fadvise($fd_t fd, $off_t offset, $off_t length, int advise) {
@@pp_if $has_function(posix_fadvise64)@@
	return posix_fadvise64(fd, ($off64_t)offset, ($off64_t)length, advise);
@@pp_elif $has_function(posix_fadvise32)@@
	return posix_fadvise32(fd, ($off32_t)offset, ($off32_t)length, advise);
@@pp_else@@
	(void)fd;
	(void)offset;
	(void)length;
	(void)advise;
	return 0;
@@pp_endif@@
}

[[decl_include("<bits/types.h>"), ignore, nocrt, alias("posix_fallocate")]]
int posix_fallocate32($fd_t fd, $off32_t offset, $off32_t length);

[[decl_include("<features.h>", "<bits/types.h>"), no_crt_self_import]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("posix_fallocate64")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("posix_fallocate")]]
[[userimpl, section(".text.crt{|.dos}.io.utility")]]
int posix_fallocate($fd_t fd, $off_t offset, $off_t length) {
@@pp_if $has_function(posix_fallocate64)@@
	return posix_fallocate64(fd, ($off64_t)offset, ($off64_t)length);
@@pp_elif $has_function(posix_fallocate32)@@
	return posix_fallocate32(fd, ($off32_t)offset, ($off32_t)length);
@@pp_else@@
	(void)fd;
	(void)offset;
	(void)length;
	return 0;
@@pp_endif@@
}

%#ifdef __USE_LARGEFILE64
[[off64_variant_of(posix_fadvise), decl_include("<bits/types.h>")]]
[[userimpl, section(".text.crt{|.dos}.io.large.utility")]]
int posix_fadvise64($fd_t fd, $off64_t offset, $off64_t length, int advise) {
@@pp_if $has_function(posix_fadvise32)@@
	return posix_fadvise32(fd, ($off32_t)offset, ($off32_t)length, advise);
@@pp_else@@
	(void)fd;
	(void)offset;
	(void)length;
	(void)advise;
	return 0;
@@pp_endif@@
}

[[off64_variant_of(posix_fallocate), decl_include("<bits/types.h>")]]
[[userimpl, section(".text.crt{|.dos}.io.large.utility")]]
int posix_fallocate64($fd_t fd, $off64_t offset, $off64_t length) {
@@pp_if $has_function(posix_fallocate32)@@
	return posix_fallocate32(fd, ($off32_t)offset, ($off32_t)length);
@@pp_else@@
	(void)fd;
	(void)offset;
	(void)length;
	return 0;
@@pp_endif@@
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_XOPEN2K */
%

%#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_POSIX))
%#ifndef F_LOCK
%#define F_ULOCK 0 /* Unlock a previously locked region. */
%#define F_LOCK  1 /* Lock a region for exclusive use. */
%#define F_TLOCK 2 /* Test and lock a region for exclusive use. */
%#define F_TEST  3 /* Test a region for other processes locks. */
%#endif /* !F_LOCK */

[[cp, decl_include("<bits/types.h>"), ignore, nocrt, alias("locking", "_locking")]]
int crt_locking($fd_t fd, int cmd, $off32_t length);

[[cp, decl_include("<bits/types.h>"), ignore, nocrt, alias("lockf")]]
int lockf32($fd_t fd, int cmd, $off32_t length);

[[cp, guard, export_as("_locking"), no_crt_self_import]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("lockf64")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("lockf", "_locking")]]
[[decl_include("<features.h>", "<bits/types.h>"), section(".text.crt{|.dos}.io.lock")]]
[[userimpl, requires($has_function(lockf64) || $has_function(lockf32) || $has_function(crt_locking))]]
int lockf($fd_t fd, int cmd, $off_t length) {
@@pp_if $has_function(lockf64)@@
	return lockf64(fd, cmd, (off64_t)length);
@@pp_elif $has_function(lockf32)@@
	return lockf32(fd, cmd, (off32_t)length);
@@pp_elif $has_function(crt_locking)@@
	return crt_locking(fd, cmd, (off32_t)length);
@@pp_endif@@
}

%#ifdef __USE_LARGEFILE64
[[cp, guard, off64_variant_of(lockf)]]
[[decl_include("<bits/types.h>"), section(".text.crt{|.dos}.io.large.lock")]]
[[userimpl, requires($has_function(lockf32) || $has_function(crt_locking))]]
int lockf64($fd_t fd, int cmd, $off64_t length) {
@@pp_if $has_function(lockf32)@@
	return lockf32(fd, cmd, (off64_t)length);
@@pp_else@@
	return crt_locking(fd, cmd, (off32_t)length);
@@pp_endif@@
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_POSIX) */


%{

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_FCNTL_H)
#include <parts/uchar/fcntl.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_FCNTL_H */
#endif /* __USE_UTF */

}

