/* HASH CRC-32:0xed6b8a41 */
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
#ifndef GUARD_LIBC_AUTO_UNISTD_H
#define GUARD_LIBC_AUTO_UNISTD_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <unistd.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBDCALL libd_execv)(char const *__restrict path, __TARGV);
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTDEF NONNULL((1, 2, 3)) int NOTHROW_RPC(LIBDCALL libd_execve)(char const *__restrict path, __TARGV, __TENVP);
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBDCALL libd_execvp)(char const *__restrict file, __TARGV);
/* >> execvpe(3)
 * Replace the calling process with the application image referred to by `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTDEF NONNULL((1, 2, 3)) int NOTHROW_RPC(LIBDCALL libd_execvpe)(char const *__restrict file, __TARGV, __TENVP);
/* >> pipe(2)
 * Create a new pair of connected pipes ([0] = reader, [1] = writer) */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_pipe)(fd_t pipedes[2]);
/* >> sleep(3)
 * Sleep for up to `SECONDS' seconds */
INTDEF unsigned int NOTHROW_RPC(LIBDCALL libd_sleep)(unsigned int seconds);
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning that changes to its data and/or descriptor are written to disk */
INTDEF int NOTHROW_RPC(LIBDCALL libd_fsync)(fd_t fd);
/* >> setpgid(2)
 * Change the ID of the process group associated with `PID's process.
 * (That is the TID of the leader of the process group of `PID's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER = THREAD[PGID]
 * When `PID' is ZERO(0), use `gettid()' for it instead.
 * When `PGID' is ZERO(0), use `PID' (after it was substituted) for instead */
INTDEF int NOTHROW_NCX(LIBDCALL libd_setpgid)(pid_t pid, pid_t pgid);
INTDEF int NOTHROW_NCX(LIBDCALL libd_getgroups)(int size, gid_t list[]);
/* >> setuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `UID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF int NOTHROW_NCX(LIBDCALL libd_setuid)(uid_t uid);
/* >> setgid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `GID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF int NOTHROW_NCX(LIBDCALL libd_setgid)(gid_t gid);
/* >> alarm(2)
 * @return: 0 : No alarm was scheduled before.
 * @return: * : The number of seconds yet to pass before a previous alarm would have elapsed.
 * Schedule an to deliver a `SIGALRM' after letting `seconds' elapse.
 * You may pass ZERO(0) for SECONDS to disable a previously scheduled alarm */
INTDEF unsigned int NOTHROW_NCX(LIBDCALL libd_alarm)(unsigned int seconds);
/* >> fpathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `FD'
 * return: * : The configuration limit associated with `NAME' for `FD'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `FD'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
INTDEF WUNUSED longptr_t NOTHROW_RPC(LIBDCALL libd_fpathconf)(fd_t fd, int name);
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
INTDEF WUNUSED char *NOTHROW_RPC(LIBDCALL libd_ttyname)(fd_t fd);
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBDCALL libd_ttyname_r)(fd_t fd, char *buf, size_t buflen);
/* >> tcgetpgrp(2)
 * Return the foreground process group of a given TTY file descriptor */
INTDEF WUNUSED pid_t NOTHROW_NCX(LIBDCALL libd_tcgetpgrp)(fd_t fd);
/* >> tcsetpgrp(2)
 * Set the foreground process group of a given TTY file descriptor */
INTDEF int NOTHROW_NCX(LIBDCALL libd_tcsetpgrp)(fd_t fd, pid_t pgrp_id);
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_chown)(char const *file, uid_t owner, gid_t group);
/* >> pathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `PATH'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
INTDEF NONNULL((1)) longptr_t NOTHROW_RPC(LIBDCALL libd_pathconf)(char const *path, __STDC_INT_AS_UINT_T name);
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBDCALL libd_link)(char const *from, char const *to);
/* >> read(2)
 * Read data from a given file descriptor `FD' and return the number of bytes read.
 * A return value of ZERO(0) is indicative of EOF */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBDCALL libd_read)(fd_t fd, void *buf, size_t bufsize);
/* >> write(2)
 * Write data to a given file descriptor `FD' and return the number of bytes written */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBDCALL libd_write)(fd_t fd, void const *buf, size_t bufsize);
/* >> readall(3)
 * Same as `read(2)', however keep on reading until `read()' indicates EOF (causing
 * `readall()' to immediately return `0') or the entirety of the given buffer has been
 * filled (in which case `bufsize' is returned).
 * If an error occurrs before all data could be read, try to use SEEK_CUR to rewind
 * the file descriptor by the amount of data that had already been loaded. - Errors
 * during this phase are silently ignored and don't cause `errno' to change */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBDCALL libd_readall)(fd_t fd, void *buf, size_t bufsize);
/* >> writeall(3)
 * Same as `write(2)', however keep on writing until `write()' indicates EOF (causing
 * `writeall()' to immediately return `0') or the entirety of the given buffer has been
 * written (in which case `bufsize' is returned). */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBDCALL libd_writeall)(fd_t fd, void const *buf, size_t bufsize);
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
INTDEF off_t NOTHROW_NCX(LIBDCALL libd_lseek)(fd_t fd, off_t offset, __STDC_INT_AS_UINT_T whence);
/* >> isatty(2)
 * @return: 1: Is a tty
 * @return: 0: Not a tty
 * Check if the given file handle `FD' refers to a TTY */
INTDEF WUNUSED int NOTHROW_NCX(LIBDCALL libd_isatty)(fd_t fd);
/* >> dup2(2)
 * @return: NEWFD: Returns the new handle upon success.
 * Duplicate a file referred to by `OLDFD' into `NEWFD' */
INTDEF fd_t NOTHROW_NCX(LIBDCALL libd_dup2)(fd_t oldfd, fd_t newfd);
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `FD' and return its duplicated handle number */
INTDEF WUNUSED fd_t NOTHROW_NCX(LIBDCALL libd_dup)(fd_t fd);
/* >> close(2)
 * Close a file handle */
INTDEF int NOTHROW_NCX(LIBDCALL libd_close)(fd_t fd);
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
INTDEF WUNUSED NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_access)(char const *file, __STDC_INT_AS_UINT_T type);
/* >> chdir(2)
 * Change the current working directory to `PATH' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_chdir)(char const *path);
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
INTDEF char *NOTHROW_RPC(LIBDCALL libd_getcwd)(char *buf, size_t bufsize);
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_unlink)(char const *file);
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_rmdir)(char const *path);
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
INTDEF WUNUSED NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_euidaccess)(char const *file, __STDC_INT_AS_UINT_T type);
/* >> faccessat(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBDCALL libd_faccessat)(fd_t dfd, char const *file, __STDC_INT_AS_UINT_T type, atflag_t flags);
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBDCALL libd_fchownat)(fd_t dfd, char const *file, uid_t owner, gid_t group, atflag_t flags);
/* >> linkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
INTDEF NONNULL((2, 4)) int NOTHROW_RPC(LIBDCALL libd_linkat)(fd_t fromfd, char const *from, fd_t tofd, char const *to, atflag_t flags);
/* >> symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
INTDEF NONNULL((1, 3)) int NOTHROW_RPC(LIBDCALL libd_symlinkat)(char const *link_text, fd_t tofd, char const *target_path);
/* >> readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
INTDEF NONNULL((2, 3)) ssize_t NOTHROW_RPC(LIBDCALL libd_readlinkat)(fd_t dfd, char const *__restrict path, char *__restrict buf, size_t buflen);
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
INTDEF NONNULL((2, 3)) ssize_t NOTHROW_RPC(LIBDCALL libd_freadlinkat)(fd_t dfd, char const *__restrict path, char *__restrict buf, size_t buflen, atflag_t flags);
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBDCALL libd_unlinkat)(fd_t dfd, char const *name, atflag_t flags);
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
INTDEF off64_t NOTHROW_NCX(LIBDCALL libd_lseek64)(fd_t fd, off64_t offset, __STDC_INT_AS_UINT_T whence);
/* >> pread(2)
 * Read data from a file at a specific offset */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBDCALL libd_pread)(fd_t fd, void *buf, size_t bufsize, __PIO_OFFSET offset);
/* >> pwrite(2)
 * Write data to a file at a specific offset */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBDCALL libd_pwrite)(fd_t fd, void const *buf, size_t bufsize, __PIO_OFFSET offset);
/* >> preadall(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBDCALL libd_preadall)(fd_t fd, void *buf, size_t bufsize, __PIO_OFFSET offset);
/* >> pwriteall(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBDCALL libd_pwriteall)(fd_t fd, void const *buf, size_t bufsize, __PIO_OFFSET offset);
/* >> pread64(2)
 * Read data from a file at a specific offset */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBDCALL libd_pread64)(fd_t fd, void *buf, size_t bufsize, __PIO_OFFSET64 offset);
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBDCALL libd_pwrite64)(fd_t fd, void const *buf, size_t bufsize, __PIO_OFFSET64 offset);
/* >> preadall64(3)
 * Same as `readall(3)', but using `pread64(2)' instead of `read()' */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBDCALL libd_preadall64)(fd_t fd, void *buf, size_t bufsize, __PIO_OFFSET64 offset);
/* >> pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite64(2)' instead of `write()' */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBDCALL libd_pwriteall64)(fd_t fd, void *buf, size_t bufsize, __PIO_OFFSET64 offset);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_pipe2)(fd_t pipedes[2], oflag_t flags);
INTDEF fd_t NOTHROW_NCX(LIBDCALL libd_dup3)(fd_t oldfd, fd_t newfd, oflag_t flags);
INTDEF int NOTHROW_RPC(LIBDCALL libd_syncfs)(fd_t fd);
INTDEF int NOTHROW_NCX(LIBDCALL libd_group_member)(gid_t gid);
INTDEF int NOTHROW_NCX(LIBDCALL libd_getresuid)(uid_t *ruid, uid_t *euid, uid_t *suid);
INTDEF int NOTHROW_NCX(LIBDCALL libd_getresgid)(gid_t *rgid, gid_t *egid, gid_t *sgid);
INTDEF int NOTHROW_NCX(LIBDCALL libd_setresuid)(uid_t ruid, uid_t euid, uid_t suid);
INTDEF int NOTHROW_NCX(LIBDCALL libd_setresgid)(gid_t rgid, gid_t egid, gid_t sgid);
/* Sleep for `useconds' microseconds (1/1.000.000 seconds) */
INTDEF int NOTHROW_RPC(LIBDCALL libd_usleep)(useconds_t useconds);
INTDEF ATTR_DEPRECATED("Use getcwd()") NONNULL((1)) char *NOTHROW_RPC(LIBDCALL libd_getwd)(char *buf);
INTDEF useconds_t NOTHROW_NCX(LIBDCALL libd_ualarm)(useconds_t value, useconds_t interval);
/* >> fchown(2)
 * Change the ownership of a given `FD' to `GROUP:OWNER' */
INTDEF int NOTHROW_RPC(LIBDCALL libd_fchown)(fd_t fd, uid_t owner, gid_t group);
/* >> chdir(2)
 * Change the current working directory to `PATH' */
INTDEF int NOTHROW_RPC(LIBDCALL libd_fchdir)(fd_t fd);
/* >> getpgid(2)
 * Return the ID of the process group associated with `PID's process.
 * (That is the TID of the leader of the process group of `PID's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER->PID
 * When `PID' is ZERO(0), use `gettid()' for it instead */
INTDEF WUNUSED pid_t NOTHROW_NCX(LIBDCALL libd_getpgid)(pid_t pid);
/* >> getsid(2)
 * Return the ID of the session which a process `PID' is apart of.
 * return THREAD[PID]->LEADER->GROUP_LEADER->SESSION_LEADER->PID; */
INTDEF WUNUSED pid_t NOTHROW_NCX(LIBDCALL libd_getsid)(pid_t pid);
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_lchown)(char const *file, uid_t owner, gid_t group);
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_truncate)(char const *file, __PIO_OFFSET length);
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_truncate64)(char const *file, __PIO_OFFSET64 length);
/* >> fexecve(2)
 * Replace the calling process with the application image referred to by `FD' and
 * execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTDEF NONNULL((2, 3)) int NOTHROW_RPC(LIBDCALL libd_fexecve)(fd_t fd, __TARGV, __TENVP);
INTDEF int NOTHROW_NCX(LIBDCALL libd_nice)(int inc);
/* Retrieve a system configuration string specified by `name'
 * @param: name:   One of `_CS_*' from <bits/confname.h>
 * @param: buf:    Target buffer
 * @param: buflen: Available buffer size (including a trailing \0-character)
 * @return: * :    Required buffer size (including a trailing \0-character)
 * @return: 1 :    Empty configuration string.
 * @return: 0 :    [errno=EINVAL] Bad configuration `name'. */
INTDEF size_t NOTHROW_NCX(LIBDCALL libd_confstr)(__STDC_INT_AS_UINT_T name, char *buf, size_t buflen);
INTDEF int NOTHROW_NCX(LIBDCALL libd_setreuid)(uid_t ruid, uid_t euid);
INTDEF int NOTHROW_NCX(LIBDCALL libd_setregid)(gid_t rgid, gid_t egid);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
INTDEF ATTR_CONST WUNUSED __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc_getpagesize)(void);
INTDEF ATTR_CONST WUNUSED __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc_getdtablesize)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> seteuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `EUID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF int NOTHROW_NCX(LIBDCALL libd_seteuid)(uid_t euid);
/* >> setegid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `EGID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF int NOTHROW_NCX(LIBDCALL libd_setegid)(gid_t egid);
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBDCALL libd_symlink)(char const *link_text, char const *target_path);
/* >> readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
INTDEF NONNULL((1, 2)) ssize_t NOTHROW_RPC(LIBDCALL libd_readlink)(char const *__restrict path, char *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_getlogin_r)(char *name, size_t name_len);
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_gethostname)(char *name, size_t buflen);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_setlogin)(char const *name);
/* >> sethostname(2)
 * Set the name of the hosting machine */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_sethostname)(char const *name, size_t len);
INTDEF int NOTHROW_NCX(LIBDCALL libd_sethostid)(longptr_t id);
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_getdomainname)(char *name, size_t buflen);
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_setdomainname)(char const *name, size_t len);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_profil)(uint16_t *sample_buffer, size_t size, size_t offset, unsigned int scale);
INTDEF int NOTHROW_RPC(LIBDCALL libd_daemon)(__STDC_INT_AS_UINT_T nochdir, __STDC_INT_AS_UINT_T noclose);
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_revoke)(char const *file);
/* >> chroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_chroot)(char const *__restrict path);
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_RPC(LIBDCALL libd_getpass)(char const *__restrict prompt);
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_ftruncate)(fd_t fd, __PIO_OFFSET length);
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_ftruncate64)(fd_t fd, __PIO_OFFSET64 length);
/* >> brk(2), sbrk(2)
 * Change the program break, allowing for a rudimentary implementation of a heap.
 * It is recommended to use the much more advanced functions found in <sys/mman.h> instead */
INTDEF int NOTHROW_NCX(LIBDCALL libd_brk)(void *addr);
INTDEF void *NOTHROW_NCX(LIBDCALL libd_sbrk)(intptr_t delta);
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps, and its size), meaning that changes are written to disk */
INTDEF int NOTHROW_RPC(LIBDCALL libd_fdatasync)(fd_t fd);
/* Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
INTDEF NONNULL((1, 2)) void NOTHROW_NCX(LIBDCALL libd_swab)(void const *__restrict from, void *__restrict to, __STDC_INT_AS_SSIZE_T n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
INTDEF NONNULL((1, 2)) void NOTHROW_NCX(LIBCCALL libc_swab)(void const *__restrict from, void *__restrict to, __STDC_INT_AS_SSIZE_T n_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF char *NOTHROW_NCX(LIBDCALL libd_ctermid)(char *s);
/* Same as `ctermid', but return `NULL' when `S' is `NULL' */
INTDEF char *NOTHROW_NCX(LIBDCALL libd_ctermid_r)(char *s);
/* >> sysconf(2)
 * @param: NAME: One of `_SC_*' from <bits/confname.h>
 * Return a system configuration value `NAME'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] `NAME' referrs to a maximum or minimum
 *                                 limit, and that limit is indeterminate
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
INTDEF WUNUSED longptr_t NOTHROW_RPC(LIBDCALL libd_sysconf)(__STDC_INT_AS_UINT_T name);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_UNISTD_H */
