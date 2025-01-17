/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Linux (/usr/include/[...]/asm/fcntl.h) */
#ifndef _ASM_FCNTL_H
#define _ASM_FCNTL_H 1

#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <bits/os/f_owner_ex.h>
#include <bits/os/flock.h>
#include <linux/types.h>

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

#if !defined(O_DSYNC) && defined(__O_DSYNC)
#define O_DSYNC __O_DSYNC /* ??? */
#endif /* !O_DSYNC && __O_DSYNC */

#if !defined(FASYNC) && defined(__O_ASYNC)
#define FASYNC __O_ASYNC /* ??? */
#endif /* !FASYNC && __O_ASYNC */

/* Bypass unified I/O buffers. Directly read-from / write-to hardware (s.a. `FILE_IOC_BLKSHIFT'). */
#if !defined(O_DIRECT) && defined(__O_DIRECT)
#define O_DIRECT __O_DIRECT
#endif /* !O_DIRECT && __O_DIRECT */

#if !defined(O_LARGEFILE) && defined(__O_LARGEFILE)
#define O_LARGEFILE __O_LARGEFILE /* Ignored... */
#endif /* !O_LARGEFILE && __O_LARGEFILE */

/* Throw an `E_FSERROR_NOT_A_DIRECTORY:E_FILESYSTEM_NOT_A_DIRECTORY_OPEN' (-ENOTDIR) exception when the
 * final path component of  an open() system  call turns out  to be something  other than a  directory. */
#if !defined(O_DIRECTORY) && defined(__O_DIRECTORY)
#define O_DIRECTORY __O_DIRECTORY
#endif /* !O_DIRECTORY && __O_DIRECTORY */

/* Throw an `E_FSERROR_IS_A_SYMBOLIC_LINK:E_FILESYSTEM_IS_A_SYMBOLIC_LINK_OPEN'  exception
 * when the final path component of an open() system call turns out to be a symbolic link. */
#if !defined(O_NOFOLLOW) && defined(__O_NOFOLLOW)
#define O_NOFOLLOW __O_NOFOLLOW
#endif /* !O_NOFOLLOW && __O_NOFOLLOW */

/* Don't update last-accessed time stamps. */
#if !defined(O_NOATIME) && defined(__O_NOATIME)
#define O_NOATIME __O_NOATIME
#endif /* !O_NOATIME && __O_NOATIME */

/* Close the file during exec() */
#if !defined(O_CLOEXEC) && defined(__O_CLOEXEC)
#define O_CLOEXEC __O_CLOEXEC
#endif /* !O_CLOEXEC && __O_CLOEXEC */

/* Open a path for *at system calls. */
#if !defined(O_PATH) && defined(__O_PATH)
#define O_PATH __O_PATH
#endif /* !O_PATH && __O_PATH */

#if !defined(O_TMPFILE) && defined(__O_TMPFILE)
#define O_TMPFILE __O_TMPFILE
#endif /* !O_TMPFILE && __O_TMPFILE */

#if !defined(O_TMPFILE_MASK) && defined(__O_TMPFILE_MASK)
#define O_TMPFILE_MASK __O_TMPFILE_MASK
#endif /* !O_TMPFILE_MASK && __O_TMPFILE_MASK */

#if !defined(O_NDELAY) && defined(__O_NONBLOCK)
#define O_NDELAY __O_NONBLOCK /* Do not block when trying to read data that hasn't been written, yet. */
#endif /* !O_NDELAY && __O_NONBLOCK */

#if !defined(F_DUPFD) && defined(__F_DUPFD)
#define F_DUPFD __F_DUPFD /* [fd_t minfd] Same as `dup(2)', but returned FD is guarantied `>= minfd' */
#endif /* !F_DUPFD && __F_DUPFD */
#if !defined(F_GETFD) && defined(__F_GETFD)
#define F_GETFD __F_GETFD /* [void arg] Get file descriptor flags.
                           * @return: * : Set of `FD_CLOEXEC | FD_CLOFORK' */
#endif /* !F_GETFD && __F_GETFD */
#if !defined(F_SETFD) && defined(__F_SETFD)
#define F_SETFD __F_SETFD /* [int arg = <set of `FD_CLOEXEC', `FD_CLOFORK'>] Set file descriptor flags. */
#endif /* !F_SETFD && __F_SETFD */
#if !defined(F_GETFL) && defined(__F_GETFL)
#define F_GETFL __F_GETFL /* [void arg] Get file status flags (set of `O_APPEND | O_NONBLOCK | O_DSYNC | O_ASYNC | O_DIRECT') */
#endif /* !F_GETFL && __F_GETFL */
#if !defined(F_SETFL) && defined(__F_SETFL)
#define F_SETFL __F_SETFL /* [oflag_t arg] Set file status flags. */
#endif /* !F_SETFL && __F_SETFL */
#if !defined(F_GETLK) && defined(__F_GETLK)
#define F_GETLK __F_GETLK /* [struct flock *arg] Get record locking info. */
#endif /* !F_GETLK && __F_GETLK */
#if !defined(F_SETLK) && defined(__F_SETLK)
#define F_SETLK __F_SETLK /* [struct flock const *arg] Set record locking info (non-blocking). */
#endif /* !F_SETLK && __F_SETLK */
#if !defined(F_SETLKW) && defined(__F_SETLKW)
#define F_SETLKW __F_SETLKW /* [struct flock const *arg] Set record locking info (blocking). */
#endif /* !F_SETLKW && __F_SETLKW */
#if !defined(F_SETOWN) && defined(__F_SETOWN)
#define F_SETOWN __F_SETOWN /* [pid_t arg] Set owner (process receiving SIGIO). */
#endif /* !F_SETOWN && __F_SETOWN */
#if !defined(F_GETOWN) && defined(__F_GETOWN)
#define F_GETOWN __F_GETOWN /* [void arg] Get owner (process receiving SIGIO).
                             * @return: * : The PID of the process (warning: the PID may not
                             *              fit into an int and -EOVERFLOW may be  returned) */
#endif /* !F_GETOWN && __F_GETOWN */
#if !defined(F_SETSIG) && defined(__F_SETSIG)
#define F_SETSIG __F_SETSIG /* [int signo] Set number of signal to be sent. */
#endif /* !F_SETSIG && __F_SETSIG */
#if !defined(F_GETSIG) && defined(__F_GETSIG)
#define F_GETSIG __F_GETSIG /* [void arg] Get number of signal to be sent.
                             * @return: * : One of `SIG*' */
#endif /* !F_GETSIG && __F_GETSIG */
#if !defined(F_GETLK64) && defined(__F_GETLK64)
#define F_GETLK64 __F_GETLK64 /* [struct flock64 *arg] Get record locking info. */
#endif /* !F_GETLK64 && __F_GETLK64 */
#if !defined(F_SETLK64) && defined(__F_SETLK64)
#define F_SETLK64 __F_SETLK64 /* [struct flock64 const *arg] Set record locking info (non-blocking). */
#endif /* !F_SETLK64 && __F_SETLK64 */
#if !defined(F_SETLKW64) && defined(__F_SETLKW64)
#define F_SETLKW64 __F_SETLKW64 /* [struct flock64 const *arg] Set record locking info (blocking). */
#endif /* !F_SETLKW64 && __F_SETLKW64 */
#if !defined(F_SETOWN_EX) && defined(__F_SETOWN_EX)
#define F_SETOWN_EX __F_SETOWN_EX /* [struct f_owner_ex const *arg] Set owner (thread receiving SIGIO). */
#endif /* !F_SETOWN_EX && __F_SETOWN_EX */
#if !defined(F_GETOWN_EX) && defined(__F_GETOWN_EX)
#define F_GETOWN_EX __F_GETOWN_EX /* [struct f_owner_ex *arg] Get owner (thread receiving SIGIO). */
#endif /* !F_GETOWN_EX && __F_GETOWN_EX */
#if !defined(F_GETOWNER_UIDS) && defined(__F_GETOWNER_UIDS)
#define F_GETOWNER_UIDS __F_GETOWNER_UIDS /* TODO */
#endif /* !F_GETOWNER_UIDS && __F_GETOWNER_UIDS */
#if !defined(F_OFD_GETLK) && defined(__F_OFD_GETLK)
#define F_OFD_GETLK __F_OFD_GETLK /* [struct flock *arg] */
#endif /* !F_OFD_GETLK && __F_OFD_GETLK */
#if !defined(F_OFD_SETLK) && defined(__F_OFD_SETLK)
#define F_OFD_SETLK __F_OFD_SETLK /* [struct flock const *arg] */
#endif /* !F_OFD_SETLK && __F_OFD_SETLK */
#if !defined(F_OFD_SETLKW) && defined(__F_OFD_SETLKW)
#define F_OFD_SETLKW __F_OFD_SETLKW /* [struct flock const *arg] */
#endif /* !F_OFD_SETLKW && __F_OFD_SETLKW */
#if !defined(F_LINUX_SPECIFIC_BASE) && defined(__F_LINUX_SPECIFIC_BASE)
#define F_LINUX_SPECIFIC_BASE __F_LINUX_SPECIFIC_BASE /* Base ID for linux-specific fcntl codes */
#endif /* !F_LINUX_SPECIFIC_BASE && __F_LINUX_SPECIFIC_BASE */

#if !defined(F_OWNER_TID) && defined(__F_OWNER_TID)
#define F_OWNER_TID __F_OWNER_TID /* Kernel thread. */
#endif /* !F_OWNER_TID && __F_OWNER_TID */
#if !defined(F_OWNER_PID) && defined(__F_OWNER_PID)
#define F_OWNER_PID __F_OWNER_PID /* Process. */
#endif /* !F_OWNER_PID && __F_OWNER_PID */
#if !defined(F_OWNER_PGRP) && defined(__F_OWNER_PGRP)
#define F_OWNER_PGRP __F_OWNER_PGRP /* Process group. */
#endif /* !F_OWNER_PGRP && __F_OWNER_PGRP */

#if !defined(FD_CLOEXEC) && defined(__FD_CLOEXEC)
#define FD_CLOEXEC __FD_CLOEXEC /* FLAG: Close the descriptor on `exec()'. */
#endif /* !FD_CLOEXEC && __FD_CLOEXEC */

#if !defined(F_RDLCK) && defined(__F_RDLCK)
#define F_RDLCK __F_RDLCK /* Read lock. */
#endif /* !F_RDLCK && __F_RDLCK */
#if !defined(F_WRLCK) && defined(__F_WRLCK)
#define F_WRLCK __F_WRLCK /* Write lock. */
#endif /* !F_WRLCK && __F_WRLCK */
#if !defined(F_UNLCK) && defined(__F_UNLCK)
#define F_UNLCK __F_UNLCK /* Remove lock. */
#endif /* !F_UNLCK && __F_UNLCK */
#if !defined(F_EXLCK) && defined(__F_EXLCK)
#define F_EXLCK __F_EXLCK /* TODO: DOC */
#endif /* !F_EXLCK && __F_EXLCK */
#if !defined(F_SHLCK) && defined(__F_SHLCK)
#define F_SHLCK __F_SHLCK /* TODO: DOC */
#endif /* !F_SHLCK && __F_SHLCK */

#if !defined(LOCK_SH) && defined(__LOCK_SH)
#define LOCK_SH __LOCK_SH /* Shared lock. */
#endif /* !LOCK_SH && __LOCK_SH */
#if !defined(LOCK_EX) && defined(__LOCK_EX)
#define LOCK_EX __LOCK_EX /* Exclusive lock. */
#endif /* !LOCK_EX && __LOCK_EX */
#if !defined(LOCK_NB) && defined(__LOCK_NB)
#define LOCK_NB __LOCK_NB /* Or'd with one of the above to prevent blocking. */
#endif /* !LOCK_NB && __LOCK_NB */
#if !defined(LOCK_UN) && defined(__LOCK_UN)
#define LOCK_UN __LOCK_UN /* Remove lock. */
#endif /* !LOCK_UN && __LOCK_UN */
#if !defined(LOCK_MAND) && defined(__LOCK_MAND)
#define LOCK_MAND __LOCK_MAND /* This is a mandatory flock: */
#endif /* !LOCK_MAND && __LOCK_MAND */
#if !defined(LOCK_READ) && defined(__LOCK_READ)
#define LOCK_READ __LOCK_READ /* ... which allows concurrent read operations. */
#endif /* !LOCK_READ && __LOCK_READ */
#if !defined(LOCK_WRITE) && defined(__LOCK_WRITE)
#define LOCK_WRITE __LOCK_WRITE /* ... which allows concurrent write operations. */
#endif /* !LOCK_WRITE && __LOCK_WRITE */
#if !defined(LOCK_RW) && defined(__LOCK_RW)
#define LOCK_RW __LOCK_RW /* ... Which allows concurrent read & write operations. */
#endif /* !LOCK_RW && __LOCK_RW */

#endif /* !_ASM_FCNTL_H */
