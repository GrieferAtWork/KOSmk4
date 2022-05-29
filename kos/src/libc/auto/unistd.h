/* HASH CRC-32:0x9dc2a044 */
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
#ifndef GUARD_LIBC_AUTO_UNISTD_H
#define GUARD_LIBC_AUTO_UNISTD_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <unistd.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> execv(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTDEF ATTR_IN(1) ATTR_IN(2) int NOTHROW_RPC(LIBDCALL libd_execv)(char const *__restrict path, __TARGV);
/* >> execv(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTDEF ATTR_IN(1) ATTR_IN(2) int NOTHROW_RPC(LIBCCALL libc_execv)(char const *__restrict path, __TARGV);
/* >> execvp(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTDEF ATTR_IN(1) ATTR_IN(2) int NOTHROW_RPC(LIBDCALL libd_execvp)(char const *__restrict file, __TARGV);
/* >> execvp(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTDEF ATTR_IN(1) ATTR_IN(2) int NOTHROW_RPC(LIBCCALL libc_execvp)(char const *__restrict file, __TARGV);
/* >> execl(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
INTDEF ATTR_SENTINEL ATTR_IN(1) ATTR_IN_OPT(2) int NOTHROW_RPC(VLIBDCALL libd_execl)(char const *__restrict path, char const *args, ...);
/* >> execl(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
INTDEF ATTR_SENTINEL ATTR_IN(1) ATTR_IN_OPT(2) int NOTHROW_RPC(VLIBCCALL libc_execl)(char const *__restrict path, char const *args, ...);
/* >> execle(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
INTDEF ATTR_IN(1) ATTR_IN_OPT(2) ATTR_SENTINEL_O(1) int NOTHROW_RPC(VLIBDCALL libd_execle)(char const *__restrict path, char const *args, ...);
/* >> execle(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
INTDEF ATTR_IN(1) ATTR_IN_OPT(2) ATTR_SENTINEL_O(1) int NOTHROW_RPC(VLIBCCALL libc_execle)(char const *__restrict path, char const *args, ...);
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
INTDEF ATTR_SENTINEL ATTR_IN(1) ATTR_IN_OPT(2) int NOTHROW_RPC(VLIBDCALL libd_execlp)(char const *__restrict file, char const *args, ...);
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
INTDEF ATTR_SENTINEL ATTR_IN(1) ATTR_IN_OPT(2) int NOTHROW_RPC(VLIBCCALL libc_execlp)(char const *__restrict file, char const *args, ...);
/* >> execvpe(3)
 * Replace the  calling process  with the  application  image referred  to by  `file'  and
 * execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) int NOTHROW_RPC(LIBDCALL libd_execvpe)(char const *__restrict file, __TARGV, __TENVP);
/* >> execvpe(3)
 * Replace the  calling process  with the  application  image referred  to by  `file'  and
 * execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) int NOTHROW_RPC(LIBCCALL libc_execvpe)(char const *__restrict file, __TARGV, __TENVP);
/* >> execlpe(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
INTDEF ATTR_IN(1) ATTR_IN_OPT(2) ATTR_SENTINEL_O(1) int NOTHROW_RPC(VLIBDCALL libd_execlpe)(char const *__restrict file, char const *args, ...);
/* >> execlpe(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
INTDEF ATTR_IN(1) ATTR_IN_OPT(2) ATTR_SENTINEL_O(1) int NOTHROW_RPC(VLIBCCALL libc_execlpe)(char const *__restrict file, char const *args, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> pipe(2)
 * Create a new pair of connected pipes ([0] = reader, [1] = writer)
 * @param: pipedes: Output for pipe fds: [0]: reader; [1]: writer
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_pipe)(fd_t pipedes[2]);
/* >> sleep(3)
 * Sleep for up to `seconds' seconds
 * @return: 0 : Timeout expired
 * @return: * : You were interrupted, and this many seconds were still left on the timeout */
INTDEF unsigned int NOTHROW_RPC(LIBDCALL libd_sleep)(unsigned int seconds);
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
INTDEF int NOTHROW_RPC(LIBDCALL libd_fsync)(fd_t fd);
/* >> setpgid(2)
 * Change  the ID of  the process group  associated with `pid's process.
 * (That is the TID of the leader of the process group of `pid's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER = THREAD[PGID]
 * When `pid' is ZERO(0), use `gettid()' for it instead.
 * When `pgid' is ZERO(0), use `pid' (after it was substituted) for instead */
INTDEF int NOTHROW_NCX(LIBDCALL libd_setpgid)(pid_t pid, pid_t pgid);
/* >> getgroups(2)
 * @return: * : [count == 0] The required number of groups
 * @return: * : [count != 0] The number of groups that were actually returned
 * @return: -1: [errno == -EINVAL && count != 0] There are more than `count' groups */
INTDEF ATTR_OUTS(2, 1) int NOTHROW_NCX(LIBDCALL libd_getgroups)(int size, gid_t list[]);
/* >> setuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `uid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF int NOTHROW_NCX(LIBDCALL libd_setuid)(uid_t uid);
/* >> setgid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `gid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF int NOTHROW_NCX(LIBDCALL libd_setgid)(gid_t gid);
/* >> alarm(2)
 * @return: 0 : No alarm was scheduled before.
 * @return: * : The number of seconds yet to pass before a previous alarm would have elapsed.
 * Schedule an to deliver a `SIGALRM' after letting `seconds' elapse.
 * You may pass `0' for `seconds' to disable a previously scheduled alarm */
INTDEF unsigned int NOTHROW_NCX(LIBDCALL libd_alarm)(unsigned int seconds);
/* >> fpathconf(3)
 * @param: name: One   of    `_PC_*'    from    <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `fd'
 * return: * : The configuration limit associated with `name' for `fd'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `fd'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
INTDEF WUNUSED longptr_t NOTHROW_RPC(LIBDCALL libd_fpathconf)(fd_t fd, __STDC_INT_AS_UINT_T name);
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
INTDEF WUNUSED char *NOTHROW_RPC(LIBDCALL libd_ttyname)(fd_t fd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
INTDEF WUNUSED char *NOTHROW_RPC(LIBCCALL libc_ttyname)(fd_t fd);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
INTDEF ATTR_OUTS(2, 3) errno_t NOTHROW_RPC(LIBDCALL libd_ttyname_r)(fd_t fd, char *buf, size_t buflen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
INTDEF ATTR_OUTS(2, 3) errno_t NOTHROW_RPC(LIBCCALL libc_ttyname_r)(fd_t fd, char *buf, size_t buflen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> tcgetpgrp(2)
 * Return the foreground process group of a given TTY file descriptor */
INTDEF WUNUSED pid_t NOTHROW_NCX(LIBDCALL libd_tcgetpgrp)(fd_t fd);
/* >> tcsetpgrp(2)
 * Set the foreground process group of a given TTY file descriptor */
INTDEF int NOTHROW_NCX(LIBDCALL libd_tcsetpgrp)(fd_t fd, pid_t pgrp_id);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> getlogin(3)
 * Return the login name for the current user, or `NULL' on error.
 * s.a. `getlogin_r()' and `cuserid()' */
INTDEF WUNUSED char *NOTHROW_NCX(LIBCCALL libc_getlogin)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> read(2)
 * Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the  `O_NONBLOCK' flag set,  only read as  much data as  was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
INTDEF ATTR_OUTS(2, 3) ssize_t NOTHROW_RPC(LIBDCALL libd_read)(fd_t fd, void *buf, size_t bufsize);
/* >> write(2)
 * Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much  data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
INTDEF ATTR_INS(2, 3) ssize_t NOTHROW_RPC(LIBDCALL libd_write)(fd_t fd, void const *buf, size_t bufsize);
/* >> readall(3)
 * Same  as `read(2)', however  keep on reading until  `read()' indicates EOF (causing
 * `readall()' to immediately return `0') or the entirety of the given buffer has been
 * filled (in which case `bufsize' is returned).
 * If  an error occurs before all data could be read, try to use SEEK_CUR to rewind
 * the file descriptor by the amount of data that had already been loaded. - Errors
 * during this phase are silently ignored and don't cause `errno' to change */
INTDEF ATTR_OUTS(2, 3) ssize_t NOTHROW_RPC(LIBDCALL libd_readall)(fd_t fd, void *buf, size_t bufsize);
/* >> writeall(3)
 * Same as `write(2)', however keep on  writing until `write()' indicates EOF  (causing
 * `writeall()' to immediately return `0') or the entirety of the given buffer has been
 * written (in which case `bufsize' is returned). */
INTDEF ATTR_INS(2, 3) ssize_t NOTHROW_RPC(LIBDCALL libd_writeall)(fd_t fd, void const *buf, size_t bufsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#include <hybrid/typecore.h>
#include <bits/crt/format-printer.h>
#if !defined(__KERNEL__) && (!defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_INT__ != __SIZEOF_POINTER__)
/* >> write_printer(3)
 * A pformatprinter-compatible consumer that dumps all input data into `fd' by use
 * of `writeall(3)'. The given `fd' should be encoded by  `WRITE_PRINTER_ARG(fd)'.
 * @return: * : Same as `writeall(3)' */
INTDEF ATTR_INS(2, 3) ssize_t NOTHROW_RPC(__FORMATPRINTER_CC libc_write_printer)(void *fd, char const *__restrict buf, size_t bufsize);
#endif /* !__KERNEL__ && (!__LIBCCALL_IS_FORMATPRINTER_CC || __SIZEOF_INT__ != __SIZEOF_POINTER__) */
#if !defined(__KERNEL__) && (defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_INT__ == __SIZEOF_POINTER__)
/* Define the libc internal header variant as an alias for writeall() when it would otherwise not be defined. */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(__FORMATPRINTER_CC libc_write_printer)(void *fd, char const *__restrict buf, size_t bufsize) ASMNAME("libc_writeall");
#endif /* !__KERNEL__ && (__LIBCCALL_IS_FORMATPRINTER_CC && __SIZEOF_INT__ == __SIZEOF_POINTER__) */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
INTDEF off_t NOTHROW_NCX(LIBDCALL libd_lseek)(fd_t fd, off_t offset, __STDC_INT_AS_UINT_T whence);
/* >> isatty(2)
 * Check if the given file handle `fd' refers to a TTY
 * @return: 1: Is a tty
 * @return: 0: Not a tty (`errno' was modified, and is usually set to `ENOTTY') */
INTDEF WUNUSED int NOTHROW_NCX(LIBDCALL libd_isatty)(fd_t fd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> isatty(2)
 * Check if the given file handle `fd' refers to a TTY
 * @return: 1: Is a tty
 * @return: 0: Not a tty (`errno' was modified, and is usually set to `ENOTTY') */
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc_isatty)(fd_t fd);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `fd' and return its duplicated handle number */
INTDEF WUNUSED fd_t NOTHROW_NCX(LIBDCALL libd_dup)(fd_t fd);
/* >> close(2)
 * Close a given file descriptor/handle `fd' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_close)(fd_t fd);
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
INTDEF off64_t NOTHROW_NCX(LIBDCALL libd_lseek64)(fd_t fd, off64_t offset, __STDC_INT_AS_UINT_T whence);
/* >> pread(2), pread64(2)
 * Read data from a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of read bytes */
INTDEF ATTR_OUTS(2, 3) ssize_t NOTHROW_RPC(LIBDCALL libd_pread)(fd_t fd, void *buf, size_t bufsize, __PIO_OFFSET offset);
/* >> pwrite(2), pwrite64(2)
 * Write data to a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of written bytes */
INTDEF ATTR_INS(2, 3) ssize_t NOTHROW_RPC(LIBDCALL libd_pwrite)(fd_t fd, void const *buf, size_t bufsize, __PIO_OFFSET offset);
/* >> preadall(3), preadall64(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
INTDEF ATTR_OUTS(2, 3) ssize_t NOTHROW_RPC(LIBDCALL libd_preadall)(fd_t fd, void *buf, size_t bufsize, __PIO_OFFSET offset);
/* >> pwriteall(3), pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
INTDEF ATTR_INS(2, 3) ssize_t NOTHROW_RPC(LIBDCALL libd_pwriteall)(fd_t fd, void const *buf, size_t bufsize, __PIO_OFFSET offset);
/* >> pread(2), pread64(2)
 * Read data from a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of read bytes */
INTDEF ATTR_OUTS(2, 3) ssize_t NOTHROW_RPC(LIBDCALL libd_pread64)(fd_t fd, void *buf, size_t bufsize, __PIO_OFFSET64 offset);
/* >> pwrite(2), pwrite64(2)
 * Write data to a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of written bytes */
INTDEF ATTR_INS(2, 3) ssize_t NOTHROW_RPC(LIBDCALL libd_pwrite64)(fd_t fd, void const *buf, size_t bufsize, __PIO_OFFSET64 offset);
/* >> preadall(3), preadall64(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
INTDEF ATTR_OUTS(2, 3) ssize_t NOTHROW_RPC(LIBDCALL libd_preadall64)(fd_t fd, void *buf, size_t bufsize, __PIO_OFFSET64 offset);
/* >> pwriteall(3), pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
INTDEF ATTR_INS(2, 3) ssize_t NOTHROW_RPC(LIBDCALL libd_pwriteall64)(fd_t fd, void const *buf, size_t bufsize, __PIO_OFFSET64 offset);
/* >> pipe2(2)
 * Construct a [reader,writer]-pair of pipes
 * @param: pipedes: Output for pipe fds: [0]: reader; [1]: writer
 * @param: flags:   Set of `O_CLOEXEC | O_CLOFORK | O_NONBLOCK | O_DIRECT'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_pipe2)(fd_t pipedes[2], oflag_t flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> get_current_dir_name(3)
 * Return an malloc(3)'d string  representing the current working  directory
 * This is usually the same  as `getcwd(NULL, 0)', however standards  caused
 * this function to be badly designed, as iff `$PWD' is defined and correct,
 * it is strdup(3)'d  and returned (correctness  is determined by  comparing
 * `stat($PWD)' against `stat(".")').
 * Due to the mandatory dependency on `getenv(3)', this function can't be
 * made thread-safe, so try not to use this one. */
INTDEF ATTR_MALLOC WUNUSED char *NOTHROW_RPC(LIBDCALL libd_get_current_dir_name)(void);
/* >> get_current_dir_name(3)
 * Return an malloc(3)'d string  representing the current working  directory
 * This is usually the same  as `getcwd(NULL, 0)', however standards  caused
 * this function to be badly designed, as iff `$PWD' is defined and correct,
 * it is strdup(3)'d  and returned (correctness  is determined by  comparing
 * `stat($PWD)' against `stat(".")').
 * Due to the mandatory dependency on `getenv(3)', this function can't be
 * made thread-safe, so try not to use this one. */
INTDEF ATTR_MALLOC WUNUSED char *NOTHROW_RPC(LIBCCALL libc_get_current_dir_name)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF int NOTHROW_RPC(LIBDCALL libd_syncfs)(fd_t fd);
/* >> group_member(3)
 * Check if `gid' is an element of `getgroups(2)'
 * @return:  1: Yes, it's a member
 * @return:  0: No, it's not a member
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBDCALL libd_group_member)(gid_t gid);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> group_member(3)
 * Check if `gid' is an element of `getgroups(2)'
 * @return:  1: Yes, it's a member
 * @return:  0: No, it's not a member
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBCCALL libc_group_member)(gid_t gid);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> getresuid(2)
 * Get the real, effective, and saved UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_OUT_OPT(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(3) int NOTHROW_NCX(LIBDCALL libd_getresuid)(uid_t *ruid, uid_t *euid, uid_t *suid);
/* >> getresgid(2)
 * Get the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_OUT_OPT(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(3) int NOTHROW_NCX(LIBDCALL libd_getresgid)(gid_t *rgid, gid_t *egid, gid_t *sgid);
/* >> setresuid(2)
 * Set the real, effective, and saved UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBDCALL libd_setresuid)(uid_t ruid, uid_t euid, uid_t suid);
/* >> setresgid(2)
 * Set the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBDCALL libd_setresgid)(gid_t rgid, gid_t egid, gid_t sgid);
/* >> usleep(3)
 * Sleep for `useconds' microseconds (1/1.000.000 seconds) */
INTDEF int NOTHROW_RPC(LIBDCALL libd_usleep)(useconds_t useconds);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> usleep(3)
 * Sleep for `useconds' microseconds (1/1.000.000 seconds) */
INTDEF int NOTHROW_RPC(LIBCCALL libc_usleep)(useconds_t useconds);
/* >> getwd(3)
 * Deprecated, alternate variant  of `getcwd()'.  It
 * should be obvious why you shouldn't use this one.
 * And  if it isn't, take a look at the arguments of
 * this function, compared to `getcwd()' */
INTDEF ATTR_DEPRECATED("Use getcwd()") ATTR_OUT(1) char *NOTHROW_RPC(LIBDCALL libd_getwd)(char *buf);
/* >> getwd(3)
 * Deprecated, alternate variant  of `getcwd()'.  It
 * should be obvious why you shouldn't use this one.
 * And  if it isn't, take a look at the arguments of
 * this function, compared to `getcwd()' */
INTDEF ATTR_DEPRECATED("Use getcwd()") ATTR_OUT(1) char *NOTHROW_RPC(LIBCCALL libc_getwd)(char *buf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF useconds_t NOTHROW_NCX(LIBDCALL libd_ualarm)(useconds_t value, useconds_t interval);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF useconds_t NOTHROW_NCX(LIBCCALL libc_ualarm)(useconds_t value, useconds_t interval);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fchown(2)
 * Change the ownership of a given `fd' to `group:owner' */
INTDEF int NOTHROW_RPC(LIBDCALL libd_fchown)(fd_t fd, uid_t owner, gid_t group);
/* >> chdir(2)
 * Change the current working directory to `path' */
INTDEF int NOTHROW_RPC(LIBDCALL libd_fchdir)(fd_t fd);
/* >> getpgid(2)
 * Return  the ID of  the process group  associated with `pid's process.
 * (That is the TID of the leader of the process group of `pid's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER->PID
 * When `pid' is ZERO(0), use `gettid()' for it instead */
INTDEF WUNUSED pid_t NOTHROW_NCX(LIBDCALL libd_getpgid)(pid_t pid);
/* >> getsid(2)
 * Return the ID of the session which a process `pid' is apart of.
 * return  THREAD[PID]->LEADER->GROUP_LEADER->SESSION_LEADER->PID; */
INTDEF WUNUSED pid_t NOTHROW_NCX(LIBDCALL libd_getsid)(pid_t pid);
/* >> fexecve(2)
 * Replace the calling process with the application image referred
 * to by `execfd'  and execute it's  `main()' method, passing  the
 * given `argv', and setting `environ' to `envp'. */
INTDEF ATTR_IN(2) ATTR_IN(3) int NOTHROW_RPC(LIBDCALL libd_fexecve)(fd_t execfd, __TARGV, __TENVP);
INTDEF int NOTHROW_NCX(LIBDCALL libd_nice)(int inc);
/* Retrieve a system configuration string specified by `name'
 * @param: name:   One of `_CS_*' from <asm/crt/confname.h>
 * @param: buf:    Target buffer
 * @param: buflen: Available buffer size (including a trailing \0-character)
 * @return: * :    Required buffer size (including a trailing \0-character)
 * @return: 1 :    Empty configuration string.
 * @return: 0 :    [errno=EINVAL] Bad configuration `name'. */
INTDEF ATTR_OUTS(2, 3) size_t NOTHROW_NCX(LIBDCALL libd_confstr)(__STDC_INT_AS_UINT_T name, char *buf, size_t buflen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> setpgrp(3)
 * Move the calling process into its own process group.
 * Equivalent to `setpgid(0, 0)' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_setpgrp)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> setreuid(2)
 * Set the real and effective UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBDCALL libd_setreuid)(uid_t ruid, uid_t euid);
/* >> setregid(2)
 * Set the real and effective GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBDCALL libd_setregid)(gid_t rgid, gid_t egid);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> gethostid(3)
 * Get the machine's "host id" (the contents of a 4-byte file "/etc/hostid") */
INTDEF WUNUSED longptr_t NOTHROW_NCX(LIBCCALL libc_gethostid)(void);
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
INTDEF ATTR_CONST WUNUSED __STDC_INT_AS_SIZE_T NOTHROW(LIBCCALL libc_getpagesize)(void);
/* >> getdtablesize(3) */
INTDEF ATTR_CONST WUNUSED __STDC_INT_AS_SIZE_T NOTHROW(LIBCCALL libc_getdtablesize)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> seteuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `euid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF int NOTHROW_NCX(LIBDCALL libd_seteuid)(uid_t euid);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> seteuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `euid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF int NOTHROW_NCX(LIBCCALL libc_seteuid)(uid_t euid);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> setegid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `egid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF int NOTHROW_NCX(LIBDCALL libd_setegid)(gid_t egid);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> setegid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `egid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF int NOTHROW_NCX(LIBCCALL libc_setegid)(gid_t egid);
/* >> ttyslot(3)
 * Returns the (1-based) index into  ttys returned by `getttyent(3)'  of
 * the terminal currently associated with the caller (~ala `ttyname(3)')
 * On  error, or if caller's terminal isn't listed by `getttyent(3)', we
 * instead return `0' */
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc_ttyslot)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> getlogin_r(3)
 * Reentrant version of `getlogin()'. May truncate the name if it's longer than `name_len'
 * s.a. `getlogin()' and `cuserid()' */
INTDEF ATTR_OUTS(1, 2) int NOTHROW_RPC(LIBDCALL libd_getlogin_r)(char *name, size_t name_len);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> getlogin_r(3)
 * Reentrant version of `getlogin()'. May truncate the name if it's longer than `name_len'
 * s.a. `getlogin()' and `cuserid()' */
INTDEF ATTR_OUTS(1, 2) int NOTHROW_RPC(LIBCCALL libc_getlogin_r)(char *name, size_t name_len);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
INTDEF ATTR_OUTS(1, 2) int NOTHROW_NCX(LIBDCALL libd_gethostname)(char *name, size_t buflen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
INTDEF ATTR_OUTS(1, 2) int NOTHROW_NCX(LIBCCALL libc_gethostname)(char *name, size_t buflen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> setlogin(3) */
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd_setlogin)(char const *name);
/* >> sethostname(2)
 * Set the name of the hosting machine */
INTDEF ATTR_INS(1, 2) int NOTHROW_NCX(LIBDCALL libd_sethostname)(char const *name, size_t len);
/* >> sethostid(3)
 * Set the machine's "host id" (the contents of a 4-byte file "/etc/hostid") */
INTDEF int NOTHROW_NCX(LIBDCALL libd_sethostid)(longptr_t id);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> sethostid(3)
 * Set the machine's "host id" (the contents of a 4-byte file "/etc/hostid") */
INTDEF int NOTHROW_NCX(LIBCCALL libc_sethostid)(longptr_t id);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
INTDEF ATTR_OUTS(1, 2) int NOTHROW_NCX(LIBDCALL libd_getdomainname)(char *name, size_t buflen);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
INTDEF ATTR_OUTS(1, 2) int NOTHROW_NCX(LIBCCALL libc_getdomainname)(char *name, size_t buflen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
INTDEF ATTR_INS(1, 2) int NOTHROW_NCX(LIBDCALL libd_setdomainname)(char const *name, size_t len);
/* >> profil(3) */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_profil)(uint16_t *sample_buffer, size_t size, size_t offset, unsigned int scale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> daemon_setup(3)
 * Do the common setup required by `daemon(3)' and `daemonfd(3)' */
INTDEF int NOTHROW_RPC(LIBCCALL libc_daemon_setup)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> daemon(3), daemonfd(3) */
INTDEF int NOTHROW_RPC(LIBDCALL libd_daemon)(int nochdir, int noclose);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> daemon(3), daemonfd(3) */
INTDEF int NOTHROW_RPC(LIBCCALL libc_daemon)(int nochdir, int noclose);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> revoke(3) */
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBDCALL libd_revoke)(char const *file);
/* >> syscall(2), syscall64(2) */
INTDEF longptr_t NOTHROW_RPC(VLIBDCALL libd_syscall)(longptr_t sysno, ...);
/* >> syscall(2), syscall64(2) */
INTDEF __LONG64_TYPE__ NOTHROW_RPC(VLIBDCALL libd_syscall64)(syscall_ulong_t sysno, ...);
/* >> getpass(3), getpassphrase(3) */
INTDEF WUNUSED char *NOTHROW_RPC(LIBDCALL libd_getpass)(char const *__restrict prompt);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> getpass(3), getpassphrase(3) */
INTDEF WUNUSED char *NOTHROW_RPC(LIBCCALL libc_getpass)(char const *__restrict prompt);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_ftruncate)(fd_t fd, __PIO_OFFSET length);
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_ftruncate64)(fd_t fd, __PIO_OFFSET64 length);
/* >> brk(2), sbrk(2)
 * Change the  program  break,  allowing  for a  rudimentary  implementation  of  a  heap.
 * It is recommended to use the much more advanced functions found in <sys/mman.h> instead */
INTDEF int NOTHROW_NCX(LIBDCALL libd_brk)(void *addr);
/* >> brk(2), sbrk(2)
 * Change the  program  break,  allowing  for a  rudimentary  implementation  of  a  heap.
 * It is recommended to use the much more advanced functions found in <sys/mman.h> instead */
INTDEF void *NOTHROW_NCX(LIBDCALL libd_sbrk)(intptr_t delta);
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps,  and its size),  meaning that changes  are written to disk */
INTDEF int NOTHROW_RPC(LIBDCALL libd_fdatasync)(fd_t fd);
/* >> swab(3)
 * Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
INTDEF ATTR_INS(1, 3) ATTR_OUTS(2, 3) void NOTHROW_NCX(LIBDCALL libd_swab)(void const *__restrict from, void *__restrict to, __STDC_INT_AS_SSIZE_T n_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> swab(3)
 * Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
INTDEF ATTR_INS(1, 3) ATTR_OUTS(2, 3) void NOTHROW_NCX(LIBCCALL libc_swab)(void const *__restrict from, void *__restrict to, __STDC_INT_AS_SSIZE_T n_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> ctermid(3)
 * Writes the string "/dev/tty" to `s', or returns a pointer to
 * a writable  data location  that contains  that same  string. */
INTDEF ATTR_RETNONNULL char *NOTHROW_NCX(LIBDCALL libd_ctermid)(char *s);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> ctermid(3)
 * Writes the string "/dev/tty" to `s', or returns a pointer to
 * a writable  data location  that contains  that same  string. */
INTDEF ATTR_RETNONNULL char *NOTHROW_NCX(LIBCCALL libc_ctermid)(char *s);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> cuserid(3)
 * Return the name of the current user (`$LOGNAME' or `getpwuid(geteuid())'), storing
 * that  name  in  `s'.  When  `s'  is   NULL,  a  static  buffer  is  used   instead
 * When  given,   `s'   must  be   a   buffer   of  at   least   `L_cuserid'   bytes.
 * If the actual  username is longer  than this,  it may be  truncated, and  programs
 * that wish to support longer usernames  should make use of `getlogin_r()'  instead.
 * s.a. `getlogin()' and `getlogin_r()' */
INTDEF ATTR_OUT_OPT(1) char *NOTHROW_NCX(LIBDCALL libd_cuserid)(char *s);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> cuserid(3)
 * Return the name of the current user (`$LOGNAME' or `getpwuid(geteuid())'), storing
 * that  name  in  `s'.  When  `s'  is   NULL,  a  static  buffer  is  used   instead
 * When  given,   `s'   must  be   a   buffer   of  at   least   `L_cuserid'   bytes.
 * If the actual  username is longer  than this,  it may be  truncated, and  programs
 * that wish to support longer usernames  should make use of `getlogin_r()'  instead.
 * s.a. `getlogin()' and `getlogin_r()' */
INTDEF ATTR_OUT_OPT(1) char *NOTHROW_NCX(LIBCCALL libc_cuserid)(char *s);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> getpassfd(3)
 * This function behaves  similar to `readpassphrase(3)',  but is  still
 * quite  distinct from that  function in how this  one behaves, vs. how
 * that other function behaves. In general, this function is a bit  more
 * user-friendly, in  that it  offers more  (but different)  `flags'  to
 * control how the password prompt is generated, with the main advantage
 * of this function  being that it  implements some "advanced"  readline
 * functionality, such as deleting  typed characters without relying  on
 * the  system  TTY canonical  buffer (which  `readpassphrase(3)' needs,
 * since it doesn't include support  for _any_ control characters  other
 * that CR/LF as indicators to stop reading text)
 * Which of the 2 functions should be used is a matter of taste, but
 * personally,   I   prefer  this   one   over  `readpassphrase(3)'.
 * @param: prompt:  [0..1]      Text-prompt to display to the user, or `NULL'
 * @param: buf:     [0..buflen] Buffer that will receive the user's password.
 *                              When set to  `NULL', a dynamically  allocated
 *                              buffer will be used and returned.
 * @param: buflen:              Size of `buf' (in characters) (ignored when `buf == NULL')
 * @param: fds:     [0..1]      When non-NULL,  an [stdin,stdout,stderr]  triple
 *                              of files, used for [read,write,beep] operations.
 *                              When  `NULL', try to use `/dev/tty' instead, and
 *                              if that fails, use  `STDIN_FILENO,STDERR_FILENO,
 *                              STDERR_FILENO' as final fallback.
 *                              When `GETPASS_NEED_TTY' is set, the  function
 *                              will fail with `errno=ENOTTY' if the actually
 *                              used `fds[0]' (iow: stdin) isn't a TTY device
 *                              s.a. `isatty(3)'
 * @param: flags:               Set of `GETPASS_*' flags (from <unistd.h>)
 * @param: timeout_in_seconds:  When non-0, timeout (in  seconds) to wait for  the
 *                              user to type each character of their password.  If
 *                              this timeout expires, fail with  `errno=ETIMEDOUT'
 *                              Negative values result in weak undefined behavior.
 * @return: * :   [buf == NULL] Success (dynamically allocated buffer; must be `free(3)'d)
 * @return: buf:                Success
 * @return: NULL: [ETIMEDOUT]   The given `timeout_in_seconds' has expired.
 * @return: NULL: [EINVAL]      `buf' is non-`NULL', but `buflen' is `0'
 * @return: NULL: [ENOTTY]      `GETPASS_NEED_TTY' was given, but not a tty
 * @return: NULL: [ENOMEM]      Insufficient memory
 * @return: NULL: [ENODATA]     End-of-file while reading, and `GETPASS_FAIL_EOF' was set.
 * @return: NULL: [*]           Error */
INTDEF WUNUSED ATTR_IN_OPT(1) ATTR_IN_OPT(4) ATTR_OUT_OPT(2) char *NOTHROW_RPC(LIBDCALL libd_getpassfd)(char const *prompt, char *buf, size_t buflen, fd_t fds[3], __STDC_INT_AS_UINT_T flags, int timeout_in_seconds);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> getpassfd(3)
 * This function behaves  similar to `readpassphrase(3)',  but is  still
 * quite  distinct from that  function in how this  one behaves, vs. how
 * that other function behaves. In general, this function is a bit  more
 * user-friendly, in  that it  offers more  (but different)  `flags'  to
 * control how the password prompt is generated, with the main advantage
 * of this function  being that it  implements some "advanced"  readline
 * functionality, such as deleting  typed characters without relying  on
 * the  system  TTY canonical  buffer (which  `readpassphrase(3)' needs,
 * since it doesn't include support  for _any_ control characters  other
 * that CR/LF as indicators to stop reading text)
 * Which of the 2 functions should be used is a matter of taste, but
 * personally,   I   prefer  this   one   over  `readpassphrase(3)'.
 * @param: prompt:  [0..1]      Text-prompt to display to the user, or `NULL'
 * @param: buf:     [0..buflen] Buffer that will receive the user's password.
 *                              When set to  `NULL', a dynamically  allocated
 *                              buffer will be used and returned.
 * @param: buflen:              Size of `buf' (in characters) (ignored when `buf == NULL')
 * @param: fds:     [0..1]      When non-NULL,  an [stdin,stdout,stderr]  triple
 *                              of files, used for [read,write,beep] operations.
 *                              When  `NULL', try to use `/dev/tty' instead, and
 *                              if that fails, use  `STDIN_FILENO,STDERR_FILENO,
 *                              STDERR_FILENO' as final fallback.
 *                              When `GETPASS_NEED_TTY' is set, the  function
 *                              will fail with `errno=ENOTTY' if the actually
 *                              used `fds[0]' (iow: stdin) isn't a TTY device
 *                              s.a. `isatty(3)'
 * @param: flags:               Set of `GETPASS_*' flags (from <unistd.h>)
 * @param: timeout_in_seconds:  When non-0, timeout (in  seconds) to wait for  the
 *                              user to type each character of their password.  If
 *                              this timeout expires, fail with  `errno=ETIMEDOUT'
 *                              Negative values result in weak undefined behavior.
 * @return: * :   [buf == NULL] Success (dynamically allocated buffer; must be `free(3)'d)
 * @return: buf:                Success
 * @return: NULL: [ETIMEDOUT]   The given `timeout_in_seconds' has expired.
 * @return: NULL: [EINVAL]      `buf' is non-`NULL', but `buflen' is `0'
 * @return: NULL: [ENOTTY]      `GETPASS_NEED_TTY' was given, but not a tty
 * @return: NULL: [ENOMEM]      Insufficient memory
 * @return: NULL: [ENODATA]     End-of-file while reading, and `GETPASS_FAIL_EOF' was set.
 * @return: NULL: [*]           Error */
INTDEF WUNUSED ATTR_IN_OPT(1) ATTR_IN_OPT(4) ATTR_OUT_OPT(2) char *NOTHROW_RPC(LIBCCALL libc_getpassfd)(char const *prompt, char *buf, size_t buflen, fd_t fds[3], __STDC_INT_AS_UINT_T flags, int timeout_in_seconds);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> getpass_r(3) */
INTDEF WUNUSED ATTR_IN_OPT(1) ATTR_OUT_OPT(2) char *NOTHROW_RPC(LIBDCALL libd_getpass_r)(char const *prompt, char *buf, size_t bufsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> getpass_r(3) */
INTDEF WUNUSED ATTR_IN_OPT(1) ATTR_OUT_OPT(2) char *NOTHROW_RPC(LIBCCALL libc_getpass_r)(char const *prompt, char *buf, size_t bufsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> setmode(3), getmode(3) */
INTDEF WUNUSED ATTR_IN(1) void *NOTHROW_NCX(LIBDCALL libd_setmode)(char const *mode_str);
/* >> setmode(3), getmode(3) */
INTDEF WUNUSED ATTR_IN(1) mode_t NOTHROW_NCX(LIBDCALL libd_getmode)(void const *bbox, mode_t mode);
/* >> getpeereid(3)
 * Convenience wrapper for `getsockopt(sockfd, SOL_SOCKET, SO_PEERCRED)' */
INTDEF ATTR_OUT(2) ATTR_OUT(3) int NOTHROW_NCX(LIBDCALL libd_getpeereid)(fd_t sockfd, uid_t *euid, gid_t *egid);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> getpeereid(3)
 * Convenience wrapper for `getsockopt(sockfd, SOL_SOCKET, SO_PEERCRED)' */
INTDEF ATTR_OUT(2) ATTR_OUT(3) int NOTHROW_NCX(LIBCCALL libc_getpeereid)(fd_t sockfd, uid_t *euid, gid_t *egid);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> setruid(3)
 * Set only the real UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBDCALL libd_setruid)(uid_t ruid);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> setruid(3)
 * Set only the real UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBCCALL libc_setruid)(uid_t ruid);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> setrgid(3)
 * Set only the real GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBDCALL libd_setrgid)(gid_t rgid);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> setrgid(3)
 * Set only the real GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBCCALL libc_setrgid)(gid_t rgid);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> ctermid_r(3)
 * Same as `ctermid', but return `NULL' when `s' is `NULL' */
INTDEF ATTR_OUT_OPT(1) char *NOTHROW_NCX(LIBDCALL libd_ctermid_r)(char *s);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> ctermid_r(3)
 * Same as `ctermid', but return `NULL' when `s' is `NULL' */
INTDEF ATTR_OUT_OPT(1) char *NOTHROW_NCX(LIBCCALL libc_ctermid_r)(char *s);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sysconf(2)
 * @param: name: One of `_SC_*' from <asm/crt/confname.h>
 * Return   a   system    configuration   value    `name'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] `name'  refers to a maximum or minimum
 *                                 limit, and that limit is indeterminate
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
INTDEF WUNUSED longptr_t NOTHROW_RPC(LIBDCALL libd_sysconf)(__STDC_INT_AS_UINT_T name);
/* >> closefrom(2)
 * Close all file descriptors with indices `>= lowfd' (s.a. `fcntl(F_CLOSEM)') */
INTDEF void NOTHROW_NCX(LIBDCALL libd_closefrom)(fd_t lowfd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> closefrom(2)
 * Close all file descriptors with indices `>= lowfd' (s.a. `fcntl(F_CLOSEM)') */
INTDEF void NOTHROW_NCX(LIBCCALL libc_closefrom)(fd_t lowfd);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> close_range(2)
 * Close all files handles `>= minfd && <= maxfd' (but see `flags')
 * @param: flags: Set of `0 | CLOSE_RANGE_UNSHARE | CLOSE_RANGE_CLOEXEC'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBDCALL libd_close_range)(unsigned int minfd, unsigned int maxfd, unsigned int flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> issetugid(3)
 * Check if the calling program is running under setuid-mode
 * Hint: simply returns the value of `__libc_enable_secure(3)'. */
INTDEF ATTR_PURE WUNUSED int NOTHROW_NCX(LIBCCALL libc_issetugid)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fchroot(2)
 * Change the root directory to  `fd'. If `fd' was opened  before a prior call to  `chroot()',
 * and referrs to  a directory,  then this function  can be  used to escape  a chroot()  jail.
 * No special permissions  are required to  use this function,  since a malicious  application
 * could achieve the same behavior by use of `*at' system calls, using `fd' as `dfd' argument. */
INTDEF int NOTHROW_NCX(LIBDCALL libd_fchroot)(fd_t fd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fchroot(2)
 * Change the root directory to  `fd'. If `fd' was opened  before a prior call to  `chroot()',
 * and referrs to  a directory,  then this function  can be  used to escape  a chroot()  jail.
 * No special permissions  are required to  use this function,  since a malicious  application
 * could achieve the same behavior by use of `*at' system calls, using `fd' as `dfd' argument. */
INTDEF int NOTHROW_NCX(LIBCCALL libc_fchroot)(fd_t fd);
/* >> resolvepath(3)
 * Similar  to  `frealpathat(2)'  (though  use  the  later  for  more   options)
 * Also note that this function appears to  have a weird rule (which KOS  simply
 * ignores)  that is related  to this function not  writing more than `PATH_MAX'
 * bytes to `buf'. (Why??? I mean: The whole point of having a `buflen' argument
 * is to be able to handle names of arbitrary lengths)
 * Additionally, the online docs don't mention what happens when `buflen' is  too
 * small, so I guess I can just make up what's supposed to happen, and I say that
 * the function will set errno=ERANGE and return -1
 * @return: * : Used buffer size (possibly including a NUL-byte, but maybe not)
 * @return: -1: Error. (s.a. `errno') */
INTDEF ATTR_IN(1) ATTR_OUTS(2, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd_resolvepath)(char const *filename, char *resolved, size_t buflen);
/* >> resolvepath(3)
 * Similar  to  `frealpathat(2)'  (though  use  the  later  for  more   options)
 * Also note that this function appears to  have a weird rule (which KOS  simply
 * ignores)  that is related  to this function not  writing more than `PATH_MAX'
 * bytes to `buf'. (Why??? I mean: The whole point of having a `buflen' argument
 * is to be able to handle names of arbitrary lengths)
 * Additionally, the online docs don't mention what happens when `buflen' is  too
 * small, so I guess I can just make up what's supposed to happen, and I say that
 * the function will set errno=ERANGE and return -1
 * @return: * : Used buffer size (possibly including a NUL-byte, but maybe not)
 * @return: -1: Error. (s.a. `errno') */
INTDEF ATTR_IN(1) ATTR_OUTS(2, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc_resolvepath)(char const *filename, char *resolved, size_t buflen);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
INTDEF WUNUSED off_t NOTHROW_NCX(LIBDCALL libd_tell)(fd_t fd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
INTDEF WUNUSED off_t NOTHROW_NCX(LIBCCALL libc_tell)(fd_t fd);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
INTDEF WUNUSED off64_t NOTHROW_NCX(LIBDCALL libd_tell64)(fd_t fd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
INTDEF WUNUSED off64_t NOTHROW_NCX(LIBCCALL libc_tell64)(fd_t fd);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_UNISTD_H */
