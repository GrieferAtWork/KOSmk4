/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Linux (/usr/include/linux/fcntl.h) */
#ifndef _LINUX_FCNTL_H
#define _LINUX_FCNTL_H 1

#include <__stdinc.h>

#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <bits/os/f_owner_ex.h>
#include <bits/os/flock.h>

#if !defined(O_ACCMODE) && defined(__O_ACCMODE)
#define O_ACCMODE __O_ACCMODE /* Mask for access modes (O_RDONLY, O_WRONLY, O_RDWR) */
#endif /* !O_ACCMODE && __O_ACCMODE */
#if !defined(O_RDONLY) && defined(__O_RDONLY)
#define O_RDONLY __O_RDONLY /* Read-only file access */
#endif /* !O_RDONLY && __O_RDONLY */
#if !defined(O_WRONLY) && defined(__O_WRONLY)
#define O_WRONLY __O_WRONLY /* Write-only file access */
#endif /* !O_WRONLY && __O_WRONLY */
#if !defined(O_RDWR) && defined(__O_RDWR)
#define O_RDWR __O_RDWR /* Read/Write file access */
#endif /* !O_RDWR && __O_RDWR */
#if !defined(O_CREAT) && defined(__O_CREAT)
#define O_CREAT __O_CREAT /* If missing, create a new file */
#endif /* !O_CREAT && __O_CREAT */
#if !defined(O_EXCL) && defined(__O_EXCL)
#define O_EXCL __O_EXCL /* When used with `O_CREAT', throw an `E_FSERROR_FILE_ALREADY_EXISTS'
                         * exception if the file already exists. */
#endif /* !O_EXCL && __O_EXCL */
#if !defined(O_NOCTTY) && defined(__O_NOCTTY)
#define O_NOCTTY __O_NOCTTY /* If the calling process does not have a controlling terminal assigned,
                             * do not attempt to assign the newly opened file as terminal, even when
                             * `isatty(open(...))' would be true. */
#endif /* !O_NOCTTY && __O_NOCTTY */
#if !defined(O_TRUNC) && defined(__O_TRUNC)
#define O_TRUNC __O_TRUNC /* Truncate (clear) the named file if it already exists,
                           * and  `O_WRONLY'  or  `O_RDWR'  access  is  specified. */
#endif /* !O_TRUNC && __O_TRUNC */
#if !defined(O_APPEND) && defined(__O_APPEND)
#define O_APPEND __O_APPEND /* Always append data to the end of the file */
#endif /* !O_APPEND && __O_APPEND */
#if !defined(O_NONBLOCK) && defined(__O_NONBLOCK)
#define O_NONBLOCK __O_NONBLOCK /* Do not block when trying to read data that hasn't been written, yet. */
#endif /* !O_NONBLOCK && __O_NONBLOCK */
#if !defined(O_DSYNC) && defined(__O_DSYNC)
#define O_DSYNC __O_DSYNC /* ??? */
#endif /* !O_DSYNC && __O_DSYNC */
#if !defined(FASYNC) && defined(__O_ASYNC)
#define FASYNC __O_ASYNC /* ??? */
#endif /* !FASYNC && __O_ASYNC */
#if !defined(O_DIRECT) && defined(__O_DIRECT)
#define O_DIRECT __O_DIRECT /* ??? */
#endif /* !O_DIRECT && __O_DIRECT */
#if !defined(O_LARGEFILE) && defined(__O_LARGEFILE)
#define O_LARGEFILE __O_LARGEFILE /* Ignored... */
#endif /* !O_LARGEFILE && __O_LARGEFILE */
#if !defined(O_DIRECTORY) && defined(__O_DIRECTORY)
#define O_DIRECTORY __O_DIRECTORY /* Throw an `E_FSERROR_NOT_A_DIRECTORY:E_FILESYSTEM_NOT_A_DIRECTORY_OPEN' exception when the final
                                   * path component of  an open()  system call turns  out to  be something other  than a  directory. */
#endif /* !O_DIRECTORY && __O_DIRECTORY */
#if !defined(O_NOFOLLOW) && defined(__O_NOFOLLOW)
#define O_NOFOLLOW __O_NOFOLLOW /* Throw an `E_FSERROR_IS_A_SYMBOLIC_LINK:E_FILESYSTEM_IS_A_SYMBOLIC_LINK_OPEN'  exception
                                 * when the final path component of an open() system call turns out to be a symbolic link. */
#endif /* !O_NOFOLLOW && __O_NOFOLLOW */
#if !defined(O_NOATIME) && defined(__O_NOATIME)
#define O_NOATIME __O_NOATIME /* Don't update last-accessed time stamps. */
#endif /* !O_NOATIME && __O_NOATIME */
#if !defined(O_CLOEXEC) && defined(__O_CLOEXEC)
#define O_CLOEXEC __O_CLOEXEC /* Close the file during exec() */
#endif /* !O_CLOEXEC && __O_CLOEXEC */
#if !defined(O_SYNC) && defined(__O_SYNC)
#define O_SYNC __O_SYNC /* ??? */
#endif /* !O_SYNC && __O_SYNC */
#if !defined(O_PATH) && defined(__O_PATH)
#define O_PATH __O_PATH /* Open a path for *at system calls. */
#endif /* !O_PATH && __O_PATH */
#if !defined(O_TMPFILE) && defined(__O_TMPFILE)
#define O_TMPFILE __O_TMPFILE  /* Open a temporary file */
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



#if !defined(F_SETLEASE) && defined(__F_SETLEASE)
#define F_SETLEASE __F_SETLEASE /* [int arg = <One of `F_RDLCK', `F_WRLCK', `F_UNLCK'>] Set a lease. */
#endif /* !F_SETLEASE && __F_SETLEASE */
#if !defined(F_GETLEASE) && defined(__F_GETLEASE)
#define F_GETLEASE __F_GETLEASE /* [void arg] Enquire what lease is active.
                                 * @return: * : One of `F_RDLCK', `F_WRLCK', `F_UNLCK' */
#endif /* !F_GETLEASE && __F_GETLEASE */
#if !defined(F_CANCELLK) && defined(__F_CANCELL)
#define F_CANCELLK __F_CANCELLK /* ??? */
#endif /* !F_CANCELLK && __F_CANCELL */
#if !defined(F_DUPFD_CLOEXEC) && defined(__F_DUPFD_CLOEXEC)
#define F_DUPFD_CLOEXEC __F_DUPFD_CLOEXEC /* [fd_t minfd] Same as `F_DUPFD', but also set `FD_CLOEXEC' bit. */
#endif /* !F_DUPFD_CLOEXEC && __F_DUPFD_CLOEXEC */
#if !defined(F_NOTIFY) && defined(__F_NOTIFY)
#define F_NOTIFY __F_NOTIFY /* [int arg = <Set of `DN_*'>] Request notifications on a directory. */
#endif /* !F_NOTIFY && __F_NOTIFY */
#if !defined(F_SETPIPE_SZ) && defined(__F_SETPIPE_SZ)
#define F_SETPIPE_SZ __F_SETPIPE_SZ /* [unsigned int arg] Set pipe buffer size (in bytes). */
#endif /* !F_SETPIPE_SZ && __F_SETPIPE_SZ */
#if !defined(F_GETPIPE_SZ) && defined(__F_GETPIPE_SZ)
#define F_GETPIPE_SZ __F_GETPIPE_SZ /* [void arg] Get pipe buffer size (in bytes).
                                     * @return: * : The buffer size (in bytes) */
#endif /* !F_GETPIPE_SZ && __F_GETPIPE_SZ */
#if !defined(F_ADD_SEALS) && defined(__F_ADD_SEALS)
#define F_ADD_SEALS __F_ADD_SEALS /* [unsigned int seals] Set file seals (`seals' is a set of `F_SEAL_*') */
#endif /* !F_ADD_SEALS && __F_ADD_SEALS */
#if !defined(F_GET_SEALS) && defined(__F_GET_SEALS)
#define F_GET_SEALS __F_GET_SEALS /* [void arg] Get active file seals.
                                   * @return: * : Active seals (set of `F_SEAL_*') */
#endif /* !F_GET_SEALS && __F_GET_SEALS */

/* For use with `F_ADD_SEALS' and `F_GET_SEALS' */
#if !defined(F_SEAL_SEAL) && defined(__F_SEAL_SEAL)
#define F_SEAL_SEAL __F_SEAL_SEAL /* Prevent further modification of seals */
#endif /* !F_SEAL_SEAL && __F_SEAL_SEAL */
#if !defined(F_SEAL_SHRINK) && defined(__F_SEAL_SHRINK)
#define F_SEAL_SHRINK __F_SEAL_SHRINK /* Prevent the file's size from being truncated */
#endif /* !F_SEAL_SHRINK && __F_SEAL_SHRINK */
#if !defined(F_SEAL_GROW) && defined(__F_SEAL_GROW)
#define F_SEAL_GROW __F_SEAL_GROW /* Prevent the file's size from being increased */
#endif /* !F_SEAL_GROW && __F_SEAL_GROW */
#if !defined(F_SEAL_WRITE) && defined(__F_SEAL_WRITE)
#define F_SEAL_WRITE __F_SEAL_WRITE /* Prevent any modifications to the file's contents.
                                     * If  writable memory mappings exist, trying to set
                                     * this flag fails with TODO:EXCEPTION_FOR_EBUSY */
#endif /* !F_SEAL_WRITE && __F_SEAL_WRITE */


#if !defined(DN_ACCESS) && defined(__DN_ACCESS)
#define DN_ACCESS __DN_ACCESS /* File accessed. */
#endif /* !DN_ACCESS && __DN_ACCESS */
#if !defined(DN_MODIFY) && defined(__DN_MODIFY)
#define DN_MODIFY __DN_MODIFY /* File modified. */
#endif /* !DN_MODIFY && __DN_MODIFY */
#if !defined(DN_CREATE) && defined(__DN_CREATE)
#define DN_CREATE __DN_CREATE /* File created. */
#endif /* !DN_CREATE && __DN_CREATE */
#if !defined(DN_DELETE) && defined(__DN_DELETE)
#define DN_DELETE __DN_DELETE /* File removed. */
#endif /* !DN_DELETE && __DN_DELETE */
#if !defined(DN_RENAME) && defined(__DN_RENAME)
#define DN_RENAME __DN_RENAME /* File renamed. */
#endif /* !DN_RENAME && __DN_RENAME */
#if !defined(DN_ATTRIB) && defined(__DN_ATTRIB)
#define DN_ATTRIB __DN_ATTRIB /* File changed attributes. */
#endif /* !DN_ATTRIB && __DN_ATTRIB */
#if !defined(DN_MULTISHOT) && defined(__DN_MULTISHOT)
#define DN_MULTISHOT __DN_MULTISHOT /* Don't remove notifier. */
#endif /* !DN_MULTISHOT && __DN_MULTISHOT */

/* Special values that may be used for the `dfd' argument of `*at' functions. */
#if !defined(AT_FDCWD) && defined(__AT_FDCWD)
#define AT_FDCWD __AT_FDCWD /* The current working directory. */
#endif /* !AT_FDCWD && __AT_FDCWD */

/* *at function flags (s.a. `atflag_t') */
#if !defined(AT_SYMLINK_NOFOLLOW) && defined(__AT_SYMLINK_NOFOLLOW)
#define AT_SYMLINK_NOFOLLOW __AT_SYMLINK_NOFOLLOW /* If the last path component is a symlink, don't follow it. */
#endif /* !AT_SYMLINK_NOFOLLOW && __AT_SYMLINK_NOFOLLOW */
#if !defined(AT_REMOVEDIR) && defined(__AT_REMOVEDIR)
#define AT_REMOVEDIR __AT_REMOVEDIR /* Remove directory instead of unlinking file. */
#endif /* !AT_REMOVEDIR && __AT_REMOVEDIR */
#if !defined(AT_SYMLINK_FOLLOW) && defined(__AT_SYMLINK_FOLLOW)
#define AT_SYMLINK_FOLLOW __AT_SYMLINK_FOLLOW /* If the last path component is a symlink, follow it. (WARNING: Only used by `linkat(2)') */
#endif /* !AT_SYMLINK_FOLLOW && __AT_SYMLINK_FOLLOW */
#if !defined(AT_NO_AUTOMOUNT) && defined(__AT_NO_AUTOMOUNT)
#define AT_NO_AUTOMOUNT __AT_NO_AUTOMOUNT /* Suppress terminal automount traversal. */
#endif /* !AT_NO_AUTOMOUNT && __AT_NO_AUTOMOUNT */
#if !defined(AT_EMPTY_PATH) && defined(__AT_EMPTY_PATH)
#define AT_EMPTY_PATH __AT_EMPTY_PATH /* Allow empty relative pathname. */
#endif /* !AT_EMPTY_PATH && __AT_EMPTY_PATH */


#endif /* _LINUX_FCNTL_H */
