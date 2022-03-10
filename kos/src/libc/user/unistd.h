/* HASH CRC-32:0x77d0749b */
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
#ifndef GUARD_LIBC_USER_UNISTD_H
#define GUARD_LIBC_USER_UNISTD_H 1

#include "../api.h"
#include "../auto/unistd.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <unistd.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char ***NOTHROW(LIBCCALL libc_p_environ)(void);
#endif /* !__KERNEL__ */
#ifndef __KERNEL__
/* >> execve(2)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTDEF NONNULL((1, 2, 3)) int NOTHROW_RPC(LIBCCALL libc_execve)(char const *__restrict path, __TARGV, __TENVP);
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
INTDEF ATTR_CONST WUNUSED pid_t NOTHROW(LIBCCALL libc_getpid)(void);
/* >> gettid(2)
 * Return the TID of the calling thread
 * THIS_THREAD->PID */
INTDEF ATTR_CONST WUNUSED pid_t NOTHROW(LIBCCALL libc_gettid)(void);
/* >> pipe(2)
 * Create a new pair of connected pipes ([0] = reader, [1] = writer)
 * @param: pipedes: Output for pipe fds: [0]: reader; [1]: writer
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_pipe)(fd_t pipedes[2]);
/* >> sleep(3)
 * Sleep for up to `seconds' seconds */
INTDEF unsigned int NOTHROW_RPC(LIBCCALL libc_sleep)(unsigned int seconds);
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
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
 * Change  the ID of  the process group  associated with `pid's process.
 * (That is the TID of the leader of the process group of `pid's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER = THREAD[PGID]
 * When `pid' is ZERO(0), use `gettid()' for it instead.
 * When `pgid' is ZERO(0), use `pid' (after it was substituted) for instead */
INTDEF int NOTHROW_NCX(LIBCCALL libc_setpgid)(pid_t pid, pid_t pgid);
/* >> setsid(2)
 * Make the calling thread's process the leader of its associated
 * process group, before also making  it its own session  leader.
 * Then return the TID of that new session leader, which is also the PID of the calling process.
 *  - THIS_THREAD->LEADER->GROUP_LEADER                 = THIS_THREAD->LEADER;
 *  - THIS_THREAD->LEADER->GROUP_LEADER->SESSION_LEADER = THIS_THREAD->LEADER->GROUP_LEADER;
 *  - return THIS_THREAD->LEADER->PID; */
INTDEF pid_t NOTHROW_NCX(LIBCCALL libc_setsid)(void);
/* >> getuid(2)
 * Return the real user ID of the calling process */
INTDEF WUNUSED uid_t NOTHROW_NCX(LIBCCALL libc_getuid)(void);
/* >> getgid(2)
 * Return the real group ID of the calling process */
INTDEF WUNUSED gid_t NOTHROW_NCX(LIBCCALL libc_getgid)(void);
/* >> geteuid(2)
 * Return the effective user ID of the calling process */
INTDEF WUNUSED uid_t NOTHROW_NCX(LIBCCALL libc_geteuid)(void);
/* >> getegid(2)
 * Return the effective group ID of the calling process */
INTDEF WUNUSED gid_t NOTHROW_NCX(LIBCCALL libc_getegid)(void);
/* >> getgroups(2)
 * @return: * : [count == 0] The required number of groups
 * @return: * : [count != 0] The number of groups that were actually returned
 * @return: -1: [errno == -EINVAL && count != 0] There are more than `count' groups */
INTDEF int NOTHROW_NCX(LIBCCALL libc_getgroups)(int size, gid_t list[]);
/* >> setuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `uid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF int NOTHROW_NCX(LIBCCALL libc_setuid)(uid_t uid);
/* >> setgid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `gid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF int NOTHROW_NCX(LIBCCALL libc_setgid)(gid_t gid);
/* >> fork(2)
 * Clone the calling thread into a second process and return twice, once
 * in  the parent process where this function returns the (non-zero) PID
 * of  the forked child process, and a  second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with  that of another  program that the  original
 * parent can then `wait(2)' for. (s.a. `vfork(2)')
 * @return: 0 : You're the new process that was created
 * @return: * : The `return' value is the pid of your new child process */
INTDEF WUNUSED pid_t NOTHROW_NCX(LIBCCALL libc_fork)(void);
/* >> alarm(2)
 * @return: 0 : No alarm was scheduled before.
 * @return: * : The number of seconds yet to pass before a previous alarm would have elapsed.
 * Schedule an to deliver a `SIGALRM' after letting `seconds' elapse.
 * You may pass `0' for `seconds' to disable a previously scheduled alarm */
INTDEF unsigned int NOTHROW_NCX(LIBCCALL libc_alarm)(unsigned int seconds);
/* >> pause(2)
 * Suspend execution until the delivery of a POSIX_SIGNAL */
INTDEF int NOTHROW_RPC(LIBCCALL libc_pause)(void);
/* >> fpathconf(2)
 * @param: name: One   of    `_PC_*'    from    <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `fd'
 * return: * : The configuration limit associated with `name' for `fd'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `fd'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
INTDEF WUNUSED longptr_t NOTHROW_RPC(LIBCCALL libc_fpathconf)(fd_t fd, __STDC_INT_AS_UINT_T name);
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_ttyname_r)(fd_t fd, char *buf, size_t buflen);
/* >> tcgetpgrp(2)
 * Return the foreground process group of a given TTY file descriptor */
INTDEF WUNUSED pid_t NOTHROW_NCX(LIBCCALL libc_tcgetpgrp)(fd_t fd);
/* >> tcsetpgrp(2)
 * Set the foreground process group of a given TTY file descriptor */
INTDEF int NOTHROW_NCX(LIBCCALL libc_tcsetpgrp)(fd_t fd, pid_t pgrp_id);
/* >> chown(2)
 * Change the ownership of a given `file' to `group:owner' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_chown)(char const *file, uid_t owner, gid_t group);
/* >> chown(2)
 * Change the ownership of a given `file' to `group:owner' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_chown)(char const *file, uid_t owner, gid_t group);
/* >> pathconf(2)
 * @param: name: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `path'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `path'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
INTDEF NONNULL((1)) longptr_t NOTHROW_RPC(LIBDCALL libd_pathconf)(char const *path, __STDC_INT_AS_UINT_T name);
/* >> pathconf(2)
 * @param: name: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `path'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `path'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
INTDEF NONNULL((1)) longptr_t NOTHROW_RPC(LIBCCALL libc_pathconf)(char const *path, __STDC_INT_AS_UINT_T name);
/* >> link(2)
 * Create a hard link from `from', leading to `to' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBDCALL libd_link)(char const *from, char const *to);
/* >> link(2)
 * Create a hard link from `from', leading to `to' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_link)(char const *from, char const *to);
/* >> read(2)
 * Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the  `O_NONBLOCK' flag set,  only read as  much data as  was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_read)(fd_t fd, void *buf, size_t bufsize);
/* >> write(2)
 * Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much  data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_write)(fd_t fd, void const *buf, size_t bufsize);
/* >> readall(3)
 * Same  as `read(2)', however  keep on reading until  `read()' indicates EOF (causing
 * `readall()' to immediately return `0') or the entirety of the given buffer has been
 * filled (in which case `bufsize' is returned).
 * If  an error occurs before all data could be read, try to use SEEK_CUR to rewind
 * the file descriptor by the amount of data that had already been loaded. - Errors
 * during this phase are silently ignored and don't cause `errno' to change */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_readall)(fd_t fd, void *buf, size_t bufsize);
/* >> writeall(3)
 * Same as `write(2)', however keep on  writing until `write()' indicates EOF  (causing
 * `writeall()' to immediately return `0') or the entirety of the given buffer has been
 * written (in which case `bufsize' is returned). */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_writeall)(fd_t fd, void const *buf, size_t bufsize);
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
INTDEF off_t NOTHROW_NCX(LIBCCALL libc_lseek)(fd_t fd, off_t offset, __STDC_INT_AS_UINT_T whence);
/* >> dup2(2)
 * @return: newfd: Returns the new handle upon success.
 * Duplicate a file referred to by `oldfd' into `newfd' */
INTDEF fd_t NOTHROW_NCX(LIBDCALL libd_dup2)(fd_t oldfd, fd_t newfd);
/* >> dup2(2)
 * @return: newfd: Returns the new handle upon success.
 * Duplicate a file referred to by `oldfd' into `newfd' */
INTDEF fd_t NOTHROW_NCX(LIBCCALL libc_dup2)(fd_t oldfd, fd_t newfd);
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `fd' and return its duplicated handle number */
INTDEF WUNUSED fd_t NOTHROW_NCX(LIBCCALL libc_dup)(fd_t fd);
/* >> close(2)
 * Close a given file descriptor/handle `fd' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_close)(fd_t fd);
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type' */
INTDEF WUNUSED NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_access)(char const *file, __STDC_INT_AS_UINT_T type);
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type' */
INTDEF WUNUSED NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_access)(char const *file, __STDC_INT_AS_UINT_T type);
/* >> chdir(2)
 * Change the current working directory to `path' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_chdir)(char const *path);
/* >> chdir(2)
 * Change the current working directory to `path' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_chdir)(char const *path);
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
INTDEF char *NOTHROW_RPC(LIBDCALL libd_getcwd)(char *buf, size_t bufsize);
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
INTDEF char *NOTHROW_RPC(LIBCCALL libc_getcwd)(char *buf, size_t bufsize);
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_unlink)(char const *file);
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_unlink)(char const *file);
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_rmdir)(char const *path);
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_rmdir)(char const *path);
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
INTDEF WUNUSED NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_euidaccess)(char const *file, __STDC_INT_AS_UINT_T type);
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
INTDEF WUNUSED NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_euidaccess)(char const *file, __STDC_INT_AS_UINT_T type);
/* >> faccessat(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `dfd:file', testing for `type' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBDCALL libd_faccessat)(fd_t dfd, char const *file, __STDC_INT_AS_UINT_T type, atflag_t flags);
/* >> faccessat(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `dfd:file', testing for `type' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_faccessat)(fd_t dfd, char const *file, __STDC_INT_AS_UINT_T type, atflag_t flags);
/* >> fchownat(2)
 * Change the ownership of a given `dfd:file' to `group:owner' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBDCALL libd_fchownat)(fd_t dfd, char const *file, uid_t owner, gid_t group, atflag_t flags);
/* >> fchownat(2)
 * Change the ownership of a given `dfd:file' to `group:owner' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_fchownat)(fd_t dfd, char const *file, uid_t owner, gid_t group, atflag_t flags);
/* >> linkat(2)
 * Create a hard link from `fromfd:from', leading to `tofd:to' */
INTDEF NONNULL((2, 4)) int NOTHROW_RPC(LIBDCALL libd_linkat)(fd_t fromfd, char const *from, fd_t tofd, char const *to, atflag_t flags);
/* >> linkat(2)
 * Create a hard link from `fromfd:from', leading to `tofd:to' */
INTDEF NONNULL((2, 4)) int NOTHROW_RPC(LIBCCALL libc_linkat)(fd_t fromfd, char const *from, fd_t tofd, char const *to, atflag_t flags);
/* >> symlinkat(3)
 * Create  a  new  symbolic  link  loaded  with  `link_text'  as link
 * text, at the filesystem location referred to by `tofd:target_path' */
INTDEF NONNULL((1, 3)) int NOTHROW_RPC(LIBDCALL libd_symlinkat)(char const *link_text, fd_t tofd, char const *target_path);
/* >> symlinkat(3)
 * Create  a  new  symbolic  link  loaded  with  `link_text'  as link
 * text, at the filesystem location referred to by `tofd:target_path' */
INTDEF NONNULL((1, 3)) int NOTHROW_RPC(LIBCCALL libc_symlinkat)(char const *link_text, fd_t tofd, char const *target_path);
/* >> readlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
INTDEF NONNULL((2, 3)) ssize_t NOTHROW_RPC(LIBDCALL libd_readlinkat)(fd_t dfd, char const *path, char *buf, size_t buflen);
/* >> readlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
INTDEF NONNULL((2, 3)) ssize_t NOTHROW_RPC(LIBCCALL libc_readlinkat)(fd_t dfd, char const *path, char *buf, size_t buflen);
/* >> fsymlinkat(3)
 * Create  a  new  symbolic  link  loaded  with  `link_text'  as link
 * text, at the filesystem location referred to by `tofd:target_path'
 * @param flags: Set of `0 | AT_DOSPATH' */
INTDEF NONNULL((1, 3)) int NOTHROW_RPC(LIBDCALL libd_fsymlinkat)(char const *link_text, fd_t tofd, char const *target_path, atflag_t flags);
/* >> fsymlinkat(3)
 * Create  a  new  symbolic  link  loaded  with  `link_text'  as link
 * text, at the filesystem location referred to by `tofd:target_path'
 * @param flags: Set of `0 | AT_DOSPATH' */
INTDEF NONNULL((1, 3)) int NOTHROW_RPC(LIBCCALL libc_fsymlinkat)(char const *link_text, fd_t tofd, char const *target_path, atflag_t flags);
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH | AT_READLINK_REQSIZE' */
INTDEF NONNULL((2, 3)) ssize_t NOTHROW_RPC(LIBDCALL libd_freadlinkat)(fd_t dfd, char const *path, char *buf, size_t buflen, atflag_t flags);
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH | AT_READLINK_REQSIZE' */
INTDEF NONNULL((2, 3)) ssize_t NOTHROW_RPC(LIBCCALL libc_freadlinkat)(fd_t dfd, char const *path, char *buf, size_t buflen, atflag_t flags);
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `dfd:name' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBDCALL libd_unlinkat)(fd_t dfd, char const *name, atflag_t flags);
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `dfd:name' */
INTDEF NONNULL((2)) int NOTHROW_RPC(LIBCCALL libc_unlinkat)(fd_t dfd, char const *name, atflag_t flags);
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
INTDEF off64_t NOTHROW_NCX(LIBCCALL libc_lseek64)(fd_t fd, off64_t offset, __STDC_INT_AS_UINT_T whence);
/* >> pread(2), pread64(2)
 * Read data from a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of read bytes */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_pread)(fd_t fd, void *buf, size_t bufsize, __PIO_OFFSET offset);
/* >> pwrite(2), pwrite64(2)
 * Write data to a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of written bytes */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_pwrite)(fd_t fd, void const *buf, size_t bufsize, __PIO_OFFSET offset);
/* >> preadall(3), preadall64(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_preadall)(fd_t fd, void *buf, size_t bufsize, __PIO_OFFSET offset);
/* >> pwriteall(3), pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_pwriteall)(fd_t fd, void const *buf, size_t bufsize, __PIO_OFFSET offset);
/* >> pread(2), pread64(2)
 * Read data from a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of read bytes */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_pread64)(fd_t fd, void *buf, size_t bufsize, __PIO_OFFSET64 offset);
/* >> pwrite(2), pwrite64(2)
 * Write data to a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of written bytes */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_pwrite64)(fd_t fd, void const *buf, size_t bufsize, __PIO_OFFSET64 offset);
/* >> preadall(3), preadall64(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_preadall64)(fd_t fd, void *buf, size_t bufsize, __PIO_OFFSET64 offset);
/* >> pwriteall(3), pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(LIBCCALL libc_pwriteall64)(fd_t fd, void const *buf, size_t bufsize, __PIO_OFFSET64 offset);
INTDEF fd_t NOTHROW_NCX(LIBDCALL libd_dup3)(fd_t oldfd, fd_t newfd, oflag_t flags);
INTDEF fd_t NOTHROW_NCX(LIBCCALL libc_dup3)(fd_t oldfd, fd_t newfd, oflag_t flags);
/* >> pipe2(2)
 * Construct a [reader,writer]-pair of pipes
 * @param: pipedes: Output for pipe fds: [0]: reader; [1]: writer
 * @param: flags:   Set of `O_CLOEXEC | O_CLOFORK | O_NONBLOCK | O_DIRECT'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_pipe2)(fd_t pipedes[2], oflag_t flags);
INTDEF int NOTHROW_RPC(LIBCCALL libc_syncfs)(fd_t fd);
/* >> getresuid(2)
 * Get the real, effective, and saved UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBCCALL libc_getresuid)(uid_t *ruid, uid_t *euid, uid_t *suid);
/* >> getresgid(2)
 * Get the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBCCALL libc_getresgid)(gid_t *rgid, gid_t *egid, gid_t *sgid);
/* >> setresuid(2)
 * @return: 0 : Success
 * Set the real, effective, and saved UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBCCALL libc_setresuid)(uid_t ruid, uid_t euid, uid_t suid);
/* >> setresgid(2)
 * Set the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBCCALL libc_setresgid)(gid_t rgid, gid_t egid, gid_t sgid);
/* >> vfork(2)
 * Same as `fork(2)', but the child process may be executed within in the same VM
 * as the parent process, with the  parent process remaining suspended until  the
 * child process invokes one of the following system calls:
 *   - `_exit(2)'  Terminate the child process. Be sure to use `_exit' (or `_Exit')
 *                 instead of the regular `exit(3)', since the later would  include
 *                 the invocation of `atexit(3)' handlers, which would then run  in
 *                 the context of a VM that isn't actually about to be destroyed.
 *   - `execve(2)' Create a new VM that is populated with the specified process
 *                 image. The parent process will  only be resumed in case  the
 *                 new  program image could  be loaded successfully. Otherwise,
 *                 the call  to  `execve(2)'  returns normally  in  the  child.
 *                 Other functions from the exec()-family behave the same
 *
 * Care  must be taken when using this system call, since you have to make sure that
 * the  child process doesn't clobber any part of its (shared) stack that may be re-
 * used once execution resumes in  the parent process. The  same also goes for  heap
 * functions,  but generally speaking:  you really shouldn't  do anything that isn't
 * reentrant after calling any one of the fork() functions (since anything but would
 * rely on underlying implementations making proper use of pthread_atfork(3),  which
 * is something that KOS intentionally doesn't do,  since I feel like doing so  only
 * adds unnecessary bloat to code that doesn't rely on this)
 *
 * Additionally, this system call may be implemented as an alias for `fork(2)', in
 * which  case the parent process will not  actually get suspended until the child
 * process performs any of the actions above. */
INTDEF ATTR_RETURNS_TWICE WUNUSED pid_t NOTHROW_NCX(LIBCCALL libc_vfork)(void);
/* >> fchown(2)
 * Change the ownership of a given `fd' to `group:owner' */
INTDEF int NOTHROW_RPC(LIBCCALL libc_fchown)(fd_t fd, uid_t owner, gid_t group);
/* >> chdir(2)
 * Change the current working directory to `path' */
INTDEF int NOTHROW_RPC(LIBCCALL libc_fchdir)(fd_t fd);
/* >> getpgid(2)
 * Return  the ID of  the process group  associated with `pid's process.
 * (That is the TID of the leader of the process group of `pid's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER->PID
 * When `pid' is ZERO(0), use `gettid()' for it instead */
INTDEF WUNUSED pid_t NOTHROW_NCX(LIBCCALL libc_getpgid)(pid_t pid);
/* >> getsid(2)
 * Return the ID of the session which a process `pid' is apart of.
 * return  THREAD[PID]->LEADER->GROUP_LEADER->SESSION_LEADER->PID; */
INTDEF WUNUSED pid_t NOTHROW_NCX(LIBCCALL libc_getsid)(pid_t pid);
/* >> lchown(2)
 * Change the ownership of a given `file' to `group:owner',
 * but don't reference it if  that file is a symbolic  link */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_lchown)(char const *file, uid_t owner, gid_t group);
/* >> lchown(2)
 * Change the ownership of a given `file' to `group:owner',
 * but don't reference it if  that file is a symbolic  link */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_lchown)(char const *file, uid_t owner, gid_t group);
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_truncate)(char const *file, __PIO_OFFSET length);
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_truncate)(char const *file, __PIO_OFFSET length);
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_truncate64)(char const *file, __PIO_OFFSET64 length);
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_truncate64)(char const *file, __PIO_OFFSET64 length);
/* >> fexecve(2)
 * Replace the  calling  process  with the  application  image  referred to  by  `fd'  and
 * execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
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
 * Synchronize all disk  operations of  all mounted file  systems and  flush
 * unwritten buffers down to the hardware layer, ensuring that modifications
 * made become visible on the underlying, persistent media */
INTDEF void NOTHROW_RPC(LIBCCALL libc_sync)(void);
/* >> setpgrp(3)
 * Move the calling process into its own process group.
 * Equivalent to `setpgid(0, 0)' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_setpgrp)(void);
/* >> setreuid(2)
 * Set the real and effective UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBCCALL libc_setreuid)(uid_t ruid, uid_t euid);
/* >> setregid(2)
 * Set the real and effective GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBCCALL libc_setregid)(gid_t rgid, gid_t egid);
/* >> gethostid(3) */
INTDEF WUNUSED longptr_t NOTHROW_NCX(LIBCCALL libc_gethostid)(void);
/* >> seteuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `euid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF int NOTHROW_NCX(LIBCCALL libc_seteuid)(uid_t euid);
/* >> setegid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `egid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF int NOTHROW_NCX(LIBCCALL libc_setegid)(gid_t egid);
/* >> ttyslot(3) */
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc_ttyslot)(void);
/* >> symlink(3)
 * Create  a new  symbolic link  loaded with  `link_text' as link
 * text, at the filesystem location referred to by `target_path'.
 * Same as `symlinkat(link_text, AT_FDCWD, target_path)' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBDCALL libd_symlink)(char const *link_text, char const *target_path);
/* >> symlink(3)
 * Create  a new  symbolic link  loaded with  `link_text' as link
 * text, at the filesystem location referred to by `target_path'.
 * Same as `symlinkat(link_text, AT_FDCWD, target_path)' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_symlink)(char const *link_text, char const *target_path);
/* >> readlink(3)
 * Read the text of a symbolic link under `path' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, path, buf, buflen)'
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
INTDEF NONNULL((1, 2)) ssize_t NOTHROW_RPC(LIBDCALL libd_readlink)(char const *path, char *buf, size_t buflen);
/* >> readlink(3)
 * Read the text of a symbolic link under `path' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, path, buf, buflen)'
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
INTDEF NONNULL((1, 2)) ssize_t NOTHROW_RPC(LIBCCALL libc_readlink)(char const *path, char *buf, size_t buflen);
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_gethostname)(char *name, size_t buflen);
/* >> setlogin(3) */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_setlogin)(char const *name);
/* >> sethostname(2)
 * Set the name of the hosting machine */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_sethostname)(char const *name, size_t len);
/* >> sethostid(3) */
INTDEF int NOTHROW_NCX(LIBCCALL libc_sethostid)(longptr_t id);
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_getdomainname)(char *name, size_t buflen);
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_setdomainname)(char const *name, size_t len);
/* >> vhangup(3) */
INTDEF int NOTHROW_NCX(LIBCCALL libc_vhangup)(void);
/* >> profil(3) */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_profil)(uint16_t *sample_buffer, size_t size, size_t offset, unsigned int scale);
/* >> getusershell(3) */
INTDEF WUNUSED char *NOTHROW_RPC(LIBCCALL libc_getusershell)(void);
/* >> endusershell(3) */
INTDEF void NOTHROW_NCX(LIBCCALL libc_endusershell)(void);
/* >> setusershell(3) */
INTDEF void NOTHROW_RPC(LIBCCALL libc_setusershell)(void);
/* >> daemon(3) */
INTDEF int NOTHROW_RPC(LIBCCALL libc_daemon)(__STDC_INT_AS_UINT_T nochdir, __STDC_INT_AS_UINT_T noclose);
/* >> revoke(3) */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_revoke)(char const *file);
/* >> syscall(2), syscall64(2) */
INTDEF longptr_t NOTHROW_RPC(VLIBCCALL libc_syscall)(longptr_t sysno, ...);
/* >> syscall(2), syscall64(2) */
INTDEF __LONG64_TYPE__ NOTHROW_RPC(VLIBCCALL libc_syscall64)(syscall_ulong_t sysno, ...);
/* >> chroot(2)
 * Change  the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `path' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_chroot)(char const *__restrict path);
/* >> chroot(2)
 * Change  the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `path' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_chroot)(char const *__restrict path);
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_ftruncate)(fd_t fd, __PIO_OFFSET length);
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_ftruncate64)(fd_t fd, __PIO_OFFSET64 length);
/* >> brk(2), sbrk(2)
 * Change the  program  break,  allowing  for a  rudimentary  implementation  of  a  heap.
 * It is recommended to use the much more advanced functions found in <sys/mman.h> instead */
INTDEF int NOTHROW_NCX(LIBCCALL libc_brk)(void *addr);
/* >> brk(2), sbrk(2)
 * Change the  program  break,  allowing  for a  rudimentary  implementation  of  a  heap.
 * It is recommended to use the much more advanced functions found in <sys/mman.h> instead */
INTDEF void *NOTHROW_NCX(LIBCCALL libc_sbrk)(intptr_t delta);
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps,  and its size),  meaning that changes  are written to disk */
INTDEF int NOTHROW_RPC(LIBCCALL libc_fdatasync)(fd_t fd);
/* >> setmode(3), getmode(3) */
INTDEF WUNUSED NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_setmode)(char const *mode_str);
/* >> setmode(3), getmode(3) */
INTDEF WUNUSED NONNULL((1)) mode_t NOTHROW_NCX(LIBCCALL libc_getmode)(void const *bbox, mode_t mode);
/* >> ctermid_r(3)
 * Same as `ctermid', but return `NULL' when `s' is `NULL' */
INTDEF char *NOTHROW_NCX(LIBCCALL libc_ctermid_r)(char *s);
/* >> sysconf(2)
 * @param: name: One of `_SC_*' from <asm/crt/confname.h>
 * Return   a   system    configuration   value    `name'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] `name'  refers to a maximum or minimum
 *                                 limit, and that limit is indeterminate
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
INTDEF WUNUSED longptr_t NOTHROW_RPC(LIBCCALL libc_sysconf)(__STDC_INT_AS_UINT_T name);
/* >> close_range(2)
 * Close all files handles `>= minfd && <= maxfd' (but see `flags')
 * @param: flags: Set of `0 | CLOSE_RANGE_UNSHARE | CLOSE_RANGE_CLOEXEC'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBCCALL libc_close_range)(unsigned int minfd, unsigned int maxfd, unsigned int flags);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_UNISTD_H */
