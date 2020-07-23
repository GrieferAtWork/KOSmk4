/* HASH CRC-32:0xb9ddf737 */
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
#ifndef GUARD_LIBC_USER_UNISTD_H
#define GUARD_LIBC_USER_UNISTD_H 1

#include "../api.h"
#include "../auto/unistd.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <unistd.h>

DECL_BEGIN

INTDEF WUNUSED ATTR_CONST ATTR_RETNONNULL char ***NOTHROW(LIBCCALL libc_p_environ)(void);
#ifndef __KERNEL__
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTDEF NONNULL((1, 2, 3)) int NOTHROW_RPC(LIBCCALL libc_execve)(char const *__restrict path, __TARGV, __TENVP);
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
INTDEF WUNUSED pid_t NOTHROW_NCX(LIBCCALL libc_getpid)(void);
/* >> gettid(2)
 * Return the TID of the calling thread
 * THIS_THREAD->PID */
INTDEF WUNUSED pid_t NOTHROW_NCX(LIBCCALL libc_gettid)(void);
/* >> pipe(2)
 * Create a new pair of connected pipes ([0] = reader, [1] = writer) */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_pipe)(fd_t pipedes[2]);
/* >> sleep(3)
 * Sleep for up to `SECONDS' seconds */
INTDEF unsigned int NOTHROW_RPC(LIBCCALL libc_sleep)(unsigned int seconds);
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning that changes to its data and/or descriptor are written to disk */
INTDEF int NOTHROW_RPC(LIBCCALL libc_fsync)(fd_t fd);
/* >> getppid(2)
 * Return the PID of the calling process's parent.
 * (That is the TID of the leader of the parent of the calling thread's leader)
 * THIS_THREAD->LEADER->PARENT->LEADER->PID */
INTDEF WUNUSED pid_t NOTHROW_NCX(LIBCCALL libc_getppid)(void);
/* >> getpgrp(2)
 * Return the ID of the calling process's process group.
 * (That is the TID of the leader of the process group of the calling thread's leader)
 * THIS_THREAD->LEADER->GROUP_LEADER->PID */
INTDEF WUNUSED pid_t NOTHROW_NCX(LIBCCALL libc_getpgrp)(void);
/* >> setpgid(2)
 * Change the ID of the process group associated with `PID's process.
 * (That is the TID of the leader of the process group of `PID's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER = THREAD[PGID]
 * When `PID' is ZERO(0), use `gettid()' for it instead.
 * When `PGID' is ZERO(0), use `PID' (after it was substituted) for instead */
INTDEF int NOTHROW_NCX(LIBCCALL libc_setpgid)(pid_t pid, pid_t pgid);
/* >> setsid(2)
 * Make the calling thread's process the leader of its associated
 * process group, before also making it its own session leader.
 * Then return the TID of that new session leader, which is also the PID of the calling process.
 *  - THIS_THREAD->LEADER->GROUP_LEADER                 = THIS_THREAD->LEADER;
 *  - THIS_THREAD->LEADER->GROUP_LEADER->SESSION_LEADER = THIS_THREAD->LEADER->GROUP_LEADER;
 *  - return THIS_THREAD->LEADER->PID; */
INTDEF pid_t NOTHROW_NCX(LIBCCALL libc_setsid)(void);
/* >> getuid(2)
 * Return the real user ID of the calling process */
INTDEF WUNUSED uid_t NOTHROW_NCX(LIBCCALL libc_getuid)(void);
/* >> geteuid(2)
 * Return the effective user ID of the calling process */
INTDEF WUNUSED uid_t NOTHROW_NCX(LIBCCALL libc_geteuid)(void);
/* >> getgid(2)
 * Return the real group ID of the calling process */
INTDEF WUNUSED gid_t NOTHROW_NCX(LIBCCALL libc_getgid)(void);
/* >> getegid(2)
 * Return the effective group ID of the calling process */
INTDEF WUNUSED gid_t NOTHROW_NCX(LIBCCALL libc_getegid)(void);
INTDEF int NOTHROW_NCX(LIBCCALL libc_getgroups)(int size, gid_t list[]);
/* >> setuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `UID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF int NOTHROW_NCX(LIBCCALL libc_setuid)(uid_t uid);
/* >> setgid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `GID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF int NOTHROW_NCX(LIBCCALL libc_setgid)(gid_t gid);
/* >> fork(2)
 * Clone the calling thread into a second process and return twice, once
 * in the parent process where this function returns the (non-zero) PID
 * of the forked child process, and a second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with that of another program that the original
 * parent can then `wait(2)' for */
INTDEF WUNUSED pid_t NOTHROW_NCX(LIBCCALL libc_fork)(void);
/* >> alarm(2)
 * @return: 0 : No alarm was scheduled before.
 * @return: * : The number of seconds yet to pass before a previous alarm would have elapsed.
 * Schedule an to deliver a `SIGALRM' after letting `seconds' elapse.
 * You may pass ZERO(0) for SECONDS to disable a previously scheduled alarm */
INTDEF unsigned int NOTHROW_NCX(LIBCCALL libc_alarm)(unsigned int seconds);
/* >> pause(2)
 * Suspend execution until the delivery of a POSIX_SIGNAL */
INTDEF int NOTHROW_RPC(LIBCCALL libc_pause)(void);
/* >> fpathconf(2)
 * @param: NAME: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `NAME' for `FD'
 * return: * : The configuration limit associated with `NAME' for `FD'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `FD'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
INTDEF WUNUSED longptr_t NOTHROW_RPC(LIBCCALL libc_fpathconf)(fd_t fd, __STDC_INT_AS_UINT_T name);
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
INTDEF WUNUSED char *NOTHROW_RPC(LIBCCALL libc_ttyname)(fd_t fd);
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_ttyname_r)(fd_t fd, char *buf, size_t buflen);
/* >> tcgetpgrp(2)
 * Return the foreground process group of a given TTY file descriptor */
INTDEF WUNUSED pid_t NOTHROW_NCX(LIBCCALL libc_tcgetpgrp)(fd_t fd);
/* >> tcsetpgrp(2)
 * Set the foreground process group of a given TTY file descriptor */
INTDEF int NOTHROW_NCX(LIBCCALL libc_tcsetpgrp)(fd_t fd, pid_t pgrp_id);
INTDEF WUNUSED char *NOTHROW_NCX(LIBCCALL libc_getlogin)(void);
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_chown)(char const *file, uid_t owner, gid_t group);
/* >> pathconf(2)
 * @param: NAME: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `PATH'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
INTDEF NONNULL((1)) longptr_t NOTHROW_RPC(LIBCCALL libc_pathconf)(char const *path, __STDC_INT_AS_UINT_T name);
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_link)(char const *from, char const *to);
/* >> read(2)
 * Read data from a given file descriptor `FD' and return the number of bytes read.
 * A return value of ZERO(0) is indicative of EOF */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_read)(fd_t fd, void *buf, size_t bufsize);
/* >> write(2)
 * Write data to a given file descriptor `FD' and return the number of bytes written */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_write)(fd_t fd, void const *buf, size_t bufsize);
/* >> readall(3)
 * Same as `read(2)', however keep on reading until `read()' indicates EOF (causing
 * `readall()' to immediately return `0') or the entirety of the given buffer has been
 * filled (in which case `bufsize' is returned).
 * If an error occurs before all data could be read, try to use SEEK_CUR to rewind
 * the file descriptor by the amount of data that had already been loaded. - Errors
 * during this phase are silently ignored and don't cause `errno' to change */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_readall)(fd_t fd, void *buf, size_t bufsize);
/* >> writeall(3)
 * Same as `write(2)', however keep on writing until `write()' indicates EOF (causing
 * `writeall()' to immediately return `0') or the entirety of the given buffer has been
 * written (in which case `bufsize' is returned). */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_writeall)(fd_t fd, void const *buf, size_t bufsize);
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
INTDEF off_t NOTHROW_NCX(LIBCCALL libc_lseek)(fd_t fd, off_t offset, __STDC_INT_AS_UINT_T whence);
/* >> isatty(2)
 * @return: 1: Is a tty
 * @return: 0: Not a tty
 * Check if the given file handle `FD' refers to a TTY */
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc_isatty)(fd_t fd);
/* >> dup2(2)
 * @return: NEWFD: Returns the new handle upon success.
 * Duplicate a file referred to by `OLDFD' into `NEWFD' */
INTDEF fd_t NOTHROW_NCX(LIBCCALL libc_dup2)(fd_t oldfd, fd_t newfd);
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `FD' and return its duplicated handle number */
INTDEF WUNUSED fd_t NOTHROW_NCX(LIBCCALL libc_dup)(fd_t fd);
/* >> close(2)
 * Close a file handle */
INTDEF int NOTHROW_NCX(LIBCCALL libc_close)(fd_t fd);
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
INTDEF WUNUSED NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_access)(char const *file, __STDC_INT_AS_UINT_T type);
/* >> chdir(2)
 * Change the current working directory to `PATH' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_chdir)(char const *path);
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
INTDEF char *NOTHROW_RPC(LIBCCALL libc_getcwd)(char *buf, size_t bufsize);
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_unlink)(char const *file);
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_rmdir)(char const *path);
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
INTDEF WUNUSED NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_euidaccess)(char const *file, __STDC_INT_AS_UINT_T type);
/* >> faccessat(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_faccessat)(fd_t dfd, char const *file, __STDC_INT_AS_UINT_T type, atflag_t flags);
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_fchownat)(fd_t dfd, char const *file, uid_t owner, gid_t group, atflag_t flags);
/* >> linkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
INTDEF NONNULL((2, 4)) int NOTHROW_RPC(LIBCCALL libc_linkat)(fd_t fromfd, char const *from, fd_t tofd, char const *to, atflag_t flags);
/* >> symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
INTDEF NONNULL((1, 3)) int NOTHROW_RPC(LIBCCALL libc_symlinkat)(char const *link_text, fd_t tofd, char const *target_path);
/* >> readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
INTDEF NONNULL((2, 3)) ssize_t NOTHROW_RPC(LIBCCALL libc_readlinkat)(fd_t dfd, char const *__restrict path, char *__restrict buf, size_t buflen);
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
INTDEF NONNULL((2, 3)) ssize_t NOTHROW_RPC(LIBCCALL libc_freadlinkat)(fd_t dfd, char const *__restrict path, char *__restrict buf, size_t buflen, atflag_t flags);
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_unlinkat)(fd_t dfd, char const *name, atflag_t flags);
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
INTDEF off64_t NOTHROW_NCX(LIBCCALL libc_lseek64)(fd_t fd, off64_t offset, __STDC_INT_AS_UINT_T whence);
/* >> pread(2)
 * Read data from a file at a specific offset */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_pread)(fd_t fd, void *buf, size_t bufsize, __PIO_OFFSET offset);
/* >> pwrite(2)
 * Write data to a file at a specific offset */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_pwrite)(fd_t fd, void const *buf, size_t bufsize, __PIO_OFFSET offset);
/* >> preadall(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_preadall)(fd_t fd, void *buf, size_t bufsize, __PIO_OFFSET offset);
/* >> pwriteall(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_pwriteall)(fd_t fd, void const *buf, size_t bufsize, __PIO_OFFSET offset);
/* >> pread64(2)
 * Read data from a file at a specific offset */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_pread64)(fd_t fd, void *buf, size_t bufsize, __PIO_OFFSET64 offset);
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_pwrite64)(fd_t fd, void const *buf, size_t bufsize, __PIO_OFFSET64 offset);
/* >> preadall64(3)
 * Same as `readall(3)', but using `pread64(2)' instead of `read()' */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_preadall64)(fd_t fd, void *buf, size_t bufsize, __PIO_OFFSET64 offset);
/* >> pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite64(2)' instead of `write()' */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_pwriteall64)(fd_t fd, void *buf, size_t bufsize, __PIO_OFFSET64 offset);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_pipe2)(fd_t pipedes[2], oflag_t flags);
INTDEF fd_t NOTHROW_NCX(LIBCCALL libc_dup3)(fd_t oldfd, fd_t newfd, oflag_t flags);
INTDEF ATTR_MALLOC WUNUSED char *NOTHROW_RPC(LIBCCALL libc_get_current_dir_name)(void);
INTDEF int NOTHROW_RPC(LIBCCALL libc_syncfs)(fd_t fd);
INTDEF int NOTHROW_NCX(LIBCCALL libc_group_member)(gid_t gid);
INTDEF int NOTHROW_NCX(LIBCCALL libc_getresuid)(uid_t *ruid, uid_t *euid, uid_t *suid);
INTDEF int NOTHROW_NCX(LIBCCALL libc_getresgid)(gid_t *rgid, gid_t *egid, gid_t *sgid);
INTDEF int NOTHROW_NCX(LIBCCALL libc_setresuid)(uid_t ruid, uid_t euid, uid_t suid);
INTDEF int NOTHROW_NCX(LIBCCALL libc_setresgid)(gid_t rgid, gid_t egid, gid_t sgid);
/* Sleep for `useconds' microseconds (1/1.000.000 seconds) */
INTDEF int NOTHROW_RPC(LIBCCALL libc_usleep)(useconds_t useconds);
INTDEF ATTR_DEPRECATED("Use getcwd()") NONNULL((1)) char *NOTHROW_RPC(LIBCCALL libc_getwd)(char *buf);
INTDEF useconds_t NOTHROW_NCX(LIBCCALL libc_ualarm)(useconds_t value, useconds_t interval);
/* >> vfork(2)
 * Same as `fork(2)', but possibly suspend the calling process until the
 * child process either calls `exit(2)' or one of the many `exec(2)' functions */
INTDEF ATTR_RETURNS_TWICE WUNUSED pid_t NOTHROW_NCX(LIBCCALL libc_vfork)(void);
/* >> fchown(2)
 * Change the ownership of a given `FD' to `GROUP:OWNER' */
INTDEF int NOTHROW_RPC(LIBCCALL libc_fchown)(fd_t fd, uid_t owner, gid_t group);
/* >> chdir(2)
 * Change the current working directory to `PATH' */
INTDEF int NOTHROW_RPC(LIBCCALL libc_fchdir)(fd_t fd);
/* >> getpgid(2)
 * Return the ID of the process group associated with `PID's process.
 * (That is the TID of the leader of the process group of `PID's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER->PID
 * When `PID' is ZERO(0), use `gettid()' for it instead */
INTDEF WUNUSED pid_t NOTHROW_NCX(LIBCCALL libc_getpgid)(pid_t pid);
/* >> getsid(2)
 * Return the ID of the session which a process `PID' is apart of.
 * return THREAD[PID]->LEADER->GROUP_LEADER->SESSION_LEADER->PID; */
INTDEF WUNUSED pid_t NOTHROW_NCX(LIBCCALL libc_getsid)(pid_t pid);
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_lchown)(char const *file, uid_t owner, gid_t group);
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_truncate)(char const *file, __PIO_OFFSET length);
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_truncate64)(char const *file, __PIO_OFFSET64 length);
/* >> fexecve(2)
 * Replace the calling process with the application image referred to by `FD' and
 * execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTDEF NONNULL((2, 3)) int NOTHROW_RPC(LIBCCALL libc_fexecve)(fd_t fd, __TARGV, __TENVP);
INTDEF int NOTHROW_NCX(LIBCCALL libc_nice)(int inc);
/* Retrieve a system configuration string specified by `name'
 * @param: name:   One of `_CS_*' from <asm/crt/confname.h>
 * @param: buf:    Target buffer
 * @param: buflen: Available buffer size (including a trailing \0-character)
 * @return: * :    Required buffer size (including a trailing \0-character)
 * @return: 1 :    Empty configuration string.
 * @return: 0 :    [errno=EINVAL] Bad configuration `name'. */
INTDEF size_t NOTHROW_NCX(LIBCCALL libc_confstr)(__STDC_INT_AS_UINT_T name, char *buf, size_t buflen);
/* >> sync(2)
 * Synchronize all disk operations of all mounted file systems and flush
 * unwritten buffers down to the hardware layer, ensuring that modifications
 * made become visible on the underlying, persistent media */
INTDEF void NOTHROW_RPC(LIBCCALL libc_sync)(void);
/* >> setpgrp(3)
 * Move the calling process into its own process group.
 * Equivalent to `setpgid(0, 0)' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_setpgrp)(void);
INTDEF int NOTHROW_NCX(LIBCCALL libc_setreuid)(uid_t ruid, uid_t euid);
INTDEF int NOTHROW_NCX(LIBCCALL libc_setregid)(gid_t rgid, gid_t egid);
INTDEF WUNUSED longptr_t NOTHROW_NCX(LIBCCALL libc_gethostid)(void);
/* >> seteuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `EUID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF int NOTHROW_NCX(LIBCCALL libc_seteuid)(uid_t euid);
/* >> setegid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `EGID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF int NOTHROW_NCX(LIBCCALL libc_setegid)(gid_t egid);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc_ttyslot)(void);
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_symlink)(char const *link_text, char const *target_path);
/* >> readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
INTDEF NONNULL((1, 2)) ssize_t NOTHROW_RPC(LIBCCALL libc_readlink)(char const *__restrict path, char *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_getlogin_r)(char *name, size_t name_len);
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_gethostname)(char *name, size_t buflen);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_setlogin)(char const *name);
/* >> sethostname(2)
 * Set the name of the hosting machine */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_sethostname)(char const *name, size_t len);
INTDEF int NOTHROW_NCX(LIBCCALL libc_sethostid)(longptr_t id);
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_getdomainname)(char *name, size_t buflen);
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_setdomainname)(char const *name, size_t len);
INTDEF int NOTHROW_NCX(LIBCCALL libc_vhangup)(void);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_profil)(uint16_t *sample_buffer, size_t size, size_t offset, unsigned int scale);
INTDEF WUNUSED char *NOTHROW_RPC(LIBCCALL libc_getusershell)(void);
INTDEF void NOTHROW_NCX(LIBCCALL libc_endusershell)(void);
INTDEF void NOTHROW_RPC(LIBCCALL libc_setusershell)(void);
INTDEF int NOTHROW_RPC(LIBCCALL libc_daemon)(__STDC_INT_AS_UINT_T nochdir, __STDC_INT_AS_UINT_T noclose);
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_revoke)(char const *file);
INTDEF longptr_t NOTHROW_RPC(VLIBCCALL libc_syscall)(longptr_t sysno, ...);
INTDEF __LONG64_TYPE__ NOTHROW_RPC(VLIBCCALL libc_syscall64)(syscall_ulong_t sysno, ...);
/* >> chroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_chroot)(char const *__restrict path);
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_RPC(LIBCCALL libc_getpass)(char const *__restrict prompt);
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_ftruncate)(fd_t fd, __PIO_OFFSET length);
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_ftruncate64)(fd_t fd, __PIO_OFFSET64 length);
/* >> brk(2), sbrk(2)
 * Change the program break, allowing for a rudimentary implementation of a heap.
 * It is recommended to use the much more advanced functions found in <sys/mman.h> instead */
INTDEF int NOTHROW_NCX(LIBCCALL libc_brk)(void *addr);
INTDEF void *NOTHROW_NCX(LIBCCALL libc_sbrk)(intptr_t delta);
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps, and its size), meaning that changes are written to disk */
INTDEF int NOTHROW_RPC(LIBCCALL libc_fdatasync)(fd_t fd);
INTDEF char *NOTHROW_NCX(LIBCCALL libc_ctermid)(char *s);
/* Same as `ctermid', but return `NULL' when `S' is `NULL' */
INTDEF char *NOTHROW_NCX(LIBCCALL libc_ctermid_r)(char *s);
/* >> sysconf(2)
 * @param: NAME: One of `_SC_*' from <asm/crt/confname.h>
 * Return a system configuration value `NAME'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] `NAME' refers to a maximum or minimum
 *                                 limit, and that limit is indeterminate
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
INTDEF WUNUSED longptr_t NOTHROW_RPC(LIBCCALL libc_sysconf)(__STDC_INT_AS_UINT_T name);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_UNISTD_H */
