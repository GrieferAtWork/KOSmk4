/* HASH CRC-32:0x60eced4b */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_UNISTD_C
#define GUARD_LIBC_AUTO_DOSABI_UNISTD_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/unistd.h"

DECL_BEGIN

/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.exec") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_execv)(char const *__restrict path,
                                 __TARGV) {
	return libc_execv(path, ___argv);
}
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.exec") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBDCALL libd_execve)(char const *__restrict path,
                                  __TARGV,
                                  __TENVP) {
	return libc_execve(path, ___argv, ___envp);
}
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.exec") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_execvp)(char const *__restrict file,
                                  __TARGV) {
	return libc_execvp(file, ___argv);
}
/* >> execvpe(3)
 * Replace the calling process with the application image referred to by `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.exec") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBDCALL libd_execvpe)(char const *__restrict file,
                                   __TARGV,
                                   __TENVP) {
	return libc_execvpe(file, ___argv, ___envp);
}
/* >> pipe(2)
 * Create a new pair of connected pipes ([0] = reader, [1] = writer) */
INTERN ATTR_SECTION(".text.crt.dos.io.access") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pipe)(fd_t pipedes[2]) {
	return libc_pipe(pipedes);
}
/* >> sleep(3)
 * Sleep for up to `SECONDS' seconds */
INTERN ATTR_SECTION(".text.crt.dos.system.utility") unsigned int
NOTHROW_RPC(LIBDCALL libd_sleep)(unsigned int seconds) {
	return libc_sleep(seconds);
}
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning that changes to its data and/or descriptor are written to disk */
INTERN ATTR_SECTION(".text.crt.dos.io.sync") int
NOTHROW_RPC(LIBDCALL libd_fsync)(fd_t fd) {
	return libc_fsync(fd);
}
/* >> setpgid(2)
 * Change the ID of the process group associated with `PID's process.
 * (That is the TID of the leader of the process group of `PID's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER = THREAD[PGID]
 * When `PID' is ZERO(0), use `gettid()' for it instead.
 * When `PGID' is ZERO(0), use `PID' (after it was substituted) for instead */
INTERN ATTR_SECTION(".text.crt.dos.sched.process") int
NOTHROW_NCX(LIBDCALL libd_setpgid)(pid_t pid,
                                   pid_t pgid) {
	return libc_setpgid(pid, pgid);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.user") int
NOTHROW_NCX(LIBDCALL libd_getgroups)(int size,
                                     gid_t list[]) {
	return libc_getgroups(size, list);
}
/* >> setuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `UID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTERN ATTR_SECTION(".text.crt.dos.sched.user") int
NOTHROW_NCX(LIBDCALL libd_setuid)(uid_t uid) {
	return libc_setuid(uid);
}
/* >> setgid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `GID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTERN ATTR_SECTION(".text.crt.dos.sched.user") int
NOTHROW_NCX(LIBDCALL libd_setgid)(gid_t gid) {
	return libc_setgid(gid);
}
/* >> alarm(2)
 * @return: 0 : No alarm was scheduled before.
 * @return: * : The number of seconds yet to pass before a previous alarm would have elapsed.
 * Schedule an to deliver a `SIGALRM' after letting `seconds' elapse.
 * You may pass ZERO(0) for SECONDS to disable a previously scheduled alarm */
INTERN ATTR_SECTION(".text.crt.dos.system.utility") unsigned int
NOTHROW_NCX(LIBDCALL libd_alarm)(unsigned int seconds) {
	return libc_alarm(seconds);
}
/* >> fpathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `FD'
 * return: * : The configuration limit associated with `NAME' for `FD'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `FD'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
INTERN ATTR_SECTION(".text.crt.dos.fs.property") WUNUSED longptr_t
NOTHROW_RPC(LIBDCALL libd_fpathconf)(fd_t fd,
                                     int name) {
	return libc_fpathconf(fd, name);
}
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
INTERN ATTR_SECTION(".text.crt.dos.io.tty") WUNUSED char *
NOTHROW_RPC(LIBDCALL libd_ttyname)(fd_t fd) {
	return libc_ttyname(fd);
}
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
INTERN ATTR_SECTION(".text.crt.dos.io.tty") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_ttyname_r)(fd_t fd,
                                     char *buf,
                                     size_t buflen) {
	return libc_ttyname_r(fd, buf, buflen);
}
/* >> tcgetpgrp(2)
 * Return the foreground process group of a given TTY file descriptor */
INTERN ATTR_SECTION(".text.crt.dos.io.tty") WUNUSED pid_t
NOTHROW_NCX(LIBDCALL libd_tcgetpgrp)(fd_t fd) {
	return libc_tcgetpgrp(fd);
}
/* >> tcsetpgrp(2)
 * Set the foreground process group of a given TTY file descriptor */
INTERN ATTR_SECTION(".text.crt.dos.io.tty") int
NOTHROW_NCX(LIBDCALL libd_tcsetpgrp)(fd_t fd,
                                     pid_t pgrp_id) {
	return libc_tcsetpgrp(fd, pgrp_id);
}
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_chown)(char const *file,
                                 uid_t owner,
                                 gid_t group) {
	return libc_chown(file, owner, group);
}
/* >> pathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `PATH'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
INTERN ATTR_SECTION(".text.crt.dos.fs.property") NONNULL((1)) longptr_t
NOTHROW_RPC(LIBDCALL libd_pathconf)(char const *path,
                                    __STDC_INT_AS_UINT_T name) {
	return libc_pathconf(path, name);
}
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_link)(char const *from,
                                char const *to) {
	return libc_link(from, to);
}
/* >> read(2)
 * Read data from a given file descriptor `FD' and return the number of bytes read.
 * A return value of ZERO(0) is indicative of EOF */
INTERN ATTR_SECTION(".text.crt.dos.io.read") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_read)(fd_t fd,
                                void *buf,
                                size_t bufsize) {
	return libc_read(fd, buf, bufsize);
}
/* >> write(2)
 * Write data to a given file descriptor `FD' and return the number of bytes written */
INTERN ATTR_SECTION(".text.crt.dos.io.write") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_write)(fd_t fd,
                                 void const *buf,
                                 size_t bufsize) {
	return libc_write(fd, buf, bufsize);
}
/* >> readall(3)
 * Same as `read(2)', however keep on reading until `read()' indicates EOF (causing
 * `readall()' to immediately return `0') or the entirety of the given buffer has been
 * filled (in which case `bufsize' is returned).
 * If an error occurrs before all data could be read, try to use SEEK_CUR to rewind
 * the file descriptor by the amount of data that had already been loaded. - Errors
 * during this phase are silently ignored and don't cause `errno' to change */
INTERN ATTR_SECTION(".text.crt.dos.io.read") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_readall)(fd_t fd,
                                   void *buf,
                                   size_t bufsize) {
	return libc_readall(fd, buf, bufsize);
}
/* >> writeall(3)
 * Same as `write(2)', however keep on writing until `write()' indicates EOF (causing
 * `writeall()' to immediately return `0') or the entirety of the given buffer has been
 * written (in which case `bufsize' is returned). */
INTERN ATTR_SECTION(".text.crt.dos.io.write") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_writeall)(fd_t fd,
                                    void const *buf,
                                    size_t bufsize) {
	return libc_writeall(fd, buf, bufsize);
}
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
INTERN ATTR_SECTION(".text.crt.dos.io.seek") off_t
NOTHROW_NCX(LIBDCALL libd_lseek)(fd_t fd,
                                 off_t offset,
                                 __STDC_INT_AS_UINT_T whence) {
	return libc_lseek(fd, offset, whence);
}
/* >> isatty(2)
 * @return: 1: Is a tty
 * @return: 0: Not a tty
 * Check if the given file handle `FD' refers to a TTY */
INTERN ATTR_SECTION(".text.crt.dos.io.tty") WUNUSED int
NOTHROW_NCX(LIBDCALL libd_isatty)(fd_t fd) {
	return libc_isatty(fd);
}
/* >> dup2(2)
 * @return: NEWFD: Returns the new handle upon success.
 * Duplicate a file referred to by `OLDFD' into `NEWFD' */
INTERN ATTR_SECTION(".text.crt.dos.io.access") fd_t
NOTHROW_NCX(LIBDCALL libd_dup2)(fd_t oldfd,
                                fd_t newfd) {
	return libc_dup2(oldfd, newfd);
}
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `FD' and return its duplicated handle number */
INTERN ATTR_SECTION(".text.crt.dos.io.access") WUNUSED fd_t
NOTHROW_NCX(LIBDCALL libd_dup)(fd_t fd) {
	return libc_dup(fd);
}
/* >> close(2)
 * Close a file handle */
INTERN ATTR_SECTION(".text.crt.dos.io.access") int
NOTHROW_NCX(LIBDCALL libd_close)(fd_t fd) {
	return libc_close(fd);
}
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
INTERN ATTR_SECTION(".text.crt.dos.fs.property") WUNUSED NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_access)(char const *file,
                                  __STDC_INT_AS_UINT_T type) {
	return libc_access(file, type);
}
/* >> chdir(2)
 * Change the current working directory to `PATH' */
INTERN ATTR_SECTION(".text.crt.dos.fs.basic_property") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_chdir)(char const *path) {
	return libc_chdir(path);
}
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
INTERN ATTR_SECTION(".text.crt.dos.fs.basic_property") char *
NOTHROW_RPC(LIBDCALL libd_getcwd)(char *buf,
                                  size_t bufsize) {
	return libc_getcwd(buf, bufsize);
}
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_unlink)(char const *file) {
	return libc_unlink(file);
}
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_rmdir)(char const *path) {
	return libc_rmdir(path);
}
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
INTERN ATTR_SECTION(".text.crt.dos.fs.property") WUNUSED NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_euidaccess)(char const *file,
                                      __STDC_INT_AS_UINT_T type) {
	return libc_euidaccess(file, type);
}
/* >> faccessat(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
INTERN ATTR_SECTION(".text.crt.dos.fs.property") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_faccessat)(fd_t dfd,
                                     char const *file,
                                     __STDC_INT_AS_UINT_T type,
                                     atflag_t flags) {
	return libc_faccessat(dfd, file, type, flags);
}
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_fchownat)(fd_t dfd,
                                    char const *file,
                                    uid_t owner,
                                    gid_t group,
                                    atflag_t flags) {
	return libc_fchownat(dfd, file, owner, group, flags);
}
/* >> linkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((2, 4)) int
NOTHROW_RPC(LIBDCALL libd_linkat)(fd_t fromfd,
                                  char const *from,
                                  fd_t tofd,
                                  char const *to,
                                  atflag_t flags) {
	return libc_linkat(fromfd, from, tofd, to, flags);
}
/* >> symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1, 3)) int
NOTHROW_RPC(LIBDCALL libd_symlinkat)(char const *link_text,
                                     fd_t tofd,
                                     char const *target_path) {
	return libc_symlinkat(link_text, tofd, target_path);
}
/* >> readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
INTERN ATTR_SECTION(".text.crt.dos.fs.property") NONNULL((2, 3)) ssize_t
NOTHROW_RPC(LIBDCALL libd_readlinkat)(fd_t dfd,
                                      char const *__restrict path,
                                      char *__restrict buf,
                                      size_t buflen) {
	return libc_readlinkat(dfd, path, buf, buflen);
}
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
INTERN ATTR_SECTION(".text.crt.dos.fs.property") NONNULL((2, 3)) ssize_t
NOTHROW_RPC(LIBDCALL libd_freadlinkat)(fd_t dfd,
                                       char const *__restrict path,
                                       char *__restrict buf,
                                       size_t buflen,
                                       atflag_t flags) {
	return libc_freadlinkat(dfd, path, buf, buflen, flags);
}
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((2)) int
NOTHROW_RPC(LIBDCALL libd_unlinkat)(fd_t dfd,
                                    char const *name,
                                    atflag_t flags) {
	return libc_unlinkat(dfd, name, flags);
}
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
INTERN ATTR_SECTION(".text.crt.dos.io.large.seek") off64_t
NOTHROW_NCX(LIBDCALL libd_lseek64)(fd_t fd,
                                   off64_t offset,
                                   __STDC_INT_AS_UINT_T whence) {
	return libc_lseek64(fd, offset, whence);
}
/* >> pread(2)
 * Read data from a file at a specific offset */
INTERN ATTR_SECTION(".text.crt.dos.io.read") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_pread)(fd_t fd,
                                 void *buf,
                                 size_t bufsize,
                                 __PIO_OFFSET offset) {
	return libc_pread(fd, buf, bufsize, offset);
}
/* >> pwrite(2)
 * Write data to a file at a specific offset */
INTERN ATTR_SECTION(".text.crt.dos.io.write") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_pwrite)(fd_t fd,
                                  void const *buf,
                                  size_t bufsize,
                                  __PIO_OFFSET offset) {
	return libc_pwrite(fd, buf, bufsize, offset);
}
/* >> preadall(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
INTERN ATTR_SECTION(".text.crt.dos.io.read") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_preadall)(fd_t fd,
                                    void *buf,
                                    size_t bufsize,
                                    __PIO_OFFSET offset) {
	return libc_preadall(fd, buf, bufsize, offset);
}
/* >> pwriteall(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
INTERN ATTR_SECTION(".text.crt.dos.io.write") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_pwriteall)(fd_t fd,
                                     void const *buf,
                                     size_t bufsize,
                                     __PIO_OFFSET offset) {
	return libc_pwriteall(fd, buf, bufsize, offset);
}
/* >> pread64(2)
 * Read data from a file at a specific offset */
INTERN ATTR_SECTION(".text.crt.dos.io.large.read") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_pread64)(fd_t fd,
                                   void *buf,
                                   size_t bufsize,
                                   __PIO_OFFSET64 offset) {
	return libc_pread64(fd, buf, bufsize, offset);
}
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
INTERN ATTR_SECTION(".text.crt.dos.io.large.write") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_pwrite64)(fd_t fd,
                                    void const *buf,
                                    size_t bufsize,
                                    __PIO_OFFSET64 offset) {
	return libc_pwrite64(fd, buf, bufsize, offset);
}
/* >> preadall64(3)
 * Same as `readall(3)', but using `pread64(2)' instead of `read()' */
INTERN ATTR_SECTION(".text.crt.dos.io.large.read") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_preadall64)(fd_t fd,
                                      void *buf,
                                      size_t bufsize,
                                      __PIO_OFFSET64 offset) {
	return libc_preadall64(fd, buf, bufsize, offset);
}
/* >> pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite64(2)' instead of `write()' */
INTERN ATTR_SECTION(".text.crt.dos.io.large.write") NONNULL((2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_pwriteall64)(fd_t fd,
                                       void *buf,
                                       size_t bufsize,
                                       __PIO_OFFSET64 offset) {
	return libc_pwriteall64(fd, buf, bufsize, offset);
}
INTERN ATTR_SECTION(".text.crt.dos.io.access") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_pipe2)(fd_t pipedes[2],
                                 oflag_t flags) {
	return libc_pipe2(pipedes, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.io.access") fd_t
NOTHROW_NCX(LIBDCALL libd_dup3)(fd_t oldfd,
                                fd_t newfd,
                                oflag_t flags) {
	return libc_dup3(oldfd, newfd, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") int
NOTHROW_RPC(LIBDCALL libd_syncfs)(fd_t fd) {
	return libc_syncfs(fd);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.user") int
NOTHROW_NCX(LIBDCALL libd_group_member)(gid_t gid) {
	return libc_group_member(gid);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.user") int
NOTHROW_NCX(LIBDCALL libd_getresuid)(uid_t *ruid,
                                     uid_t *euid,
                                     uid_t *suid) {
	return libc_getresuid(ruid, euid, suid);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.user") int
NOTHROW_NCX(LIBDCALL libd_getresgid)(gid_t *rgid,
                                     gid_t *egid,
                                     gid_t *sgid) {
	return libc_getresgid(rgid, egid, sgid);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.user") int
NOTHROW_NCX(LIBDCALL libd_setresuid)(uid_t ruid,
                                     uid_t euid,
                                     uid_t suid) {
	return libc_setresuid(ruid, euid, suid);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.user") int
NOTHROW_NCX(LIBDCALL libd_setresgid)(gid_t rgid,
                                     gid_t egid,
                                     gid_t sgid) {
	return libc_setresgid(rgid, egid, sgid);
}
/* Sleep for `useconds' microseconds (1/1.000.000 seconds) */
INTERN ATTR_SECTION(".text.crt.dos.system.utility") int
NOTHROW_RPC(LIBDCALL libd_usleep)(useconds_t useconds) {
	return libc_usleep(useconds);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.basic_property") ATTR_DEPRECATED("Use getcwd()") NONNULL((1)) char *
NOTHROW_RPC(LIBDCALL libd_getwd)(char *buf) {
	return libc_getwd(buf);
}
INTERN ATTR_SECTION(".text.crt.dos.system.utility") useconds_t
NOTHROW_NCX(LIBDCALL libd_ualarm)(useconds_t value,
                                  useconds_t interval) {
	return libc_ualarm(value, interval);
}
/* >> fchown(2)
 * Change the ownership of a given `FD' to `GROUP:OWNER' */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") int
NOTHROW_RPC(LIBDCALL libd_fchown)(fd_t fd,
                                  uid_t owner,
                                  gid_t group) {
	return libc_fchown(fd, owner, group);
}
/* >> chdir(2)
 * Change the current working directory to `PATH' */
INTERN ATTR_SECTION(".text.crt.dos.fs.basic_property") int
NOTHROW_RPC(LIBDCALL libd_fchdir)(fd_t fd) {
	return libc_fchdir(fd);
}
/* >> getpgid(2)
 * Return the ID of the process group associated with `PID's process.
 * (That is the TID of the leader of the process group of `PID's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER->PID
 * When `PID' is ZERO(0), use `gettid()' for it instead */
INTERN ATTR_SECTION(".text.crt.dos.sched.user") WUNUSED pid_t
NOTHROW_NCX(LIBDCALL libd_getpgid)(pid_t pid) {
	return libc_getpgid(pid);
}
/* >> getsid(2)
 * Return the ID of the session which a process `PID' is apart of.
 * return THREAD[PID]->LEADER->GROUP_LEADER->SESSION_LEADER->PID; */
INTERN ATTR_SECTION(".text.crt.dos.sched.process") WUNUSED pid_t
NOTHROW_NCX(LIBDCALL libd_getsid)(pid_t pid) {
	return libc_getsid(pid);
}
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_lchown)(char const *file,
                                  uid_t owner,
                                  gid_t group) {
	return libc_lchown(file, owner, group);
}
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_truncate)(char const *file,
                                    __PIO_OFFSET length) {
	return libc_truncate(file, length);
}
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_truncate64)(char const *file,
                                      __PIO_OFFSET64 length) {
	return libc_truncate64(file, length);
}
/* >> fexecve(2)
 * Replace the calling process with the application image referred to by `FD' and
 * execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.exec") NONNULL((2, 3)) int
NOTHROW_RPC(LIBDCALL libd_fexecve)(fd_t fd,
                                   __TARGV,
                                   __TENVP) {
	return libc_fexecve(fd, ___argv, ___envp);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.param") int
NOTHROW_NCX(LIBDCALL libd_nice)(int inc) {
	return libc_nice(inc);
}
/* Retrieve a system configuration string specified by `name'
 * @param: name:   One of `_CS_*' from <bits/confname.h>
 * @param: buf:    Target buffer
 * @param: buflen: Available buffer size (including a trailing \0-character)
 * @return: * :    Required buffer size (including a trailing \0-character)
 * @return: 1 :    Empty configuration string.
 * @return: 0 :    [errno=EINVAL] Bad configuration `name'. */
INTERN ATTR_SECTION(".text.crt.dos.system.configuration") size_t
NOTHROW_NCX(LIBDCALL libd_confstr)(__STDC_INT_AS_UINT_T name,
                                   char *buf,
                                   size_t buflen) {
	return libc_confstr(name, buf, buflen);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.user") int
NOTHROW_NCX(LIBDCALL libd_setreuid)(uid_t ruid,
                                    uid_t euid) {
	return libc_setreuid(ruid, euid);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.user") int
NOTHROW_NCX(LIBDCALL libd_setregid)(gid_t rgid,
                                    gid_t egid) {
	return libc_setregid(rgid, egid);
}
/* >> seteuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `EUID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTERN ATTR_SECTION(".text.crt.dos.sched.user") int
NOTHROW_NCX(LIBDCALL libd_seteuid)(uid_t euid) {
	return libc_seteuid(euid);
}
/* >> setegid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `EGID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTERN ATTR_SECTION(".text.crt.dos.sched.user") int
NOTHROW_NCX(LIBDCALL libd_setegid)(gid_t egid) {
	return libc_setegid(egid);
}
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_symlink)(char const *link_text,
                                   char const *target_path) {
	return libc_symlink(link_text, target_path);
}
/* >> readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
INTERN ATTR_SECTION(".text.crt.dos.fs.property") NONNULL((1, 2)) ssize_t
NOTHROW_RPC(LIBDCALL libd_readlink)(char const *__restrict path,
                                    char *__restrict buf,
                                    size_t buflen) {
	return libc_readlink(path, buf, buflen);
}
INTERN ATTR_SECTION(".text.crt.dos.io.tty") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_getlogin_r)(char *name,
                                      size_t name_len) {
	return libc_getlogin_r(name, name_len);
}
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
INTERN ATTR_SECTION(".text.crt.dos.system.configuration") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_gethostname)(char *name,
                                       size_t buflen) {
	return libc_gethostname(name, buflen);
}
INTERN ATTR_SECTION(".text.crt.dos.io.tty") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_setlogin)(char const *name) {
	return libc_setlogin(name);
}
/* >> sethostname(2)
 * Set the name of the hosting machine */
INTERN ATTR_SECTION(".text.crt.dos.system.configuration") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_sethostname)(char const *name,
                                       size_t len) {
	return libc_sethostname(name, len);
}
INTERN ATTR_SECTION(".text.crt.dos.system.configuration") int
NOTHROW_NCX(LIBDCALL libd_sethostid)(longptr_t id) {
	return libc_sethostid(id);
}
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
INTERN ATTR_SECTION(".text.crt.dos.system.configuration") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_getdomainname)(char *name,
                                         size_t buflen) {
	return libc_getdomainname(name, buflen);
}
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
INTERN ATTR_SECTION(".text.crt.dos.system.configuration") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_setdomainname)(char const *name,
                                         size_t len) {
	return libc_setdomainname(name, len);
}
INTERN ATTR_SECTION(".text.crt.dos.system.utility") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_profil)(uint16_t *sample_buffer,
                                  size_t size,
                                  size_t offset,
                                  unsigned int scale) {
	return libc_profil(sample_buffer, size, offset, scale);
}
INTERN ATTR_SECTION(".text.crt.dos.system.utility") int
NOTHROW_RPC(LIBDCALL libd_daemon)(__STDC_INT_AS_UINT_T nochdir,
                                  __STDC_INT_AS_UINT_T noclose) {
	return libc_daemon(nochdir, noclose);
}
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_revoke)(char const *file) {
	return libc_revoke(file);
}
/* >> chroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
INTERN ATTR_SECTION(".text.crt.dos.fs.utility") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_chroot)(char const *__restrict path) {
	return libc_chroot(path);
}
INTERN ATTR_SECTION(".text.crt.dos.io.tty") WUNUSED NONNULL((1)) char *
NOTHROW_RPC(LIBDCALL libd_getpass)(char const *__restrict prompt) {
	return libc_getpass(prompt);
}
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
INTERN ATTR_SECTION(".text.crt.dos.io.write") int
NOTHROW_NCX(LIBDCALL libd_ftruncate)(fd_t fd,
                                     __PIO_OFFSET length) {
	return libc_ftruncate(fd, length);
}
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
INTERN ATTR_SECTION(".text.crt.dos.io.large.write") int
NOTHROW_NCX(LIBDCALL libd_ftruncate64)(fd_t fd,
                                       __PIO_OFFSET64 length) {
	return libc_ftruncate64(fd, length);
}
/* >> brk(2), sbrk(2)
 * Change the program break, allowing for a rudimentary implementation of a heap.
 * It is recommended to use the much more advanced functions found in <sys/mman.h> instead */
INTERN ATTR_SECTION(".text.crt.dos.heap.utility") int
NOTHROW_NCX(LIBDCALL libd_brk)(void *addr) {
	return libc_brk(addr);
}
INTERN ATTR_SECTION(".text.crt.dos.heap.utility") void *
NOTHROW_NCX(LIBDCALL libd_sbrk)(intptr_t delta) {
	return libc_sbrk(delta);
}
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps, and its size), meaning that changes are written to disk */
INTERN ATTR_SECTION(".text.crt.dos.io.sync") int
NOTHROW_RPC(LIBDCALL libd_fdatasync)(fd_t fd) {
	return libc_fdatasync(fd);
}
/* Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
INTERN ATTR_SECTION(".text.crt.dos.string.memory") NONNULL((1, 2)) void
NOTHROW_NCX(LIBDCALL libd_swab)(void const *__restrict from,
                                void *__restrict to,
                                __STDC_INT_AS_SSIZE_T n_bytes) {
	libc_swab(from, to, n_bytes);
}
INTERN ATTR_SECTION(".text.crt.dos.io.tty") char *
NOTHROW_NCX(LIBDCALL libd_ctermid)(char *s) {
	return libc_ctermid(s);
}
/* Same as `ctermid', but return `NULL' when `S' is `NULL' */
INTERN ATTR_SECTION(".text.crt.dos.io.tty") char *
NOTHROW_NCX(LIBDCALL libd_ctermid_r)(char *s) {
	return libc_ctermid_r(s);
}
/* >> sysconf(2)
 * @param: NAME: One of `_SC_*' from <bits/confname.h>
 * Return a system configuration value `NAME'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] `NAME' referrs to a maximum or minimum
 *                                 limit, and that limit is indeterminate
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
INTERN ATTR_SECTION(".text.crt.dos.system.configuration") WUNUSED longptr_t
NOTHROW_RPC(LIBDCALL libd_sysconf)(__STDC_INT_AS_UINT_T name) {
	return libc_sysconf(name);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$_execv, libd_execv);
DEFINE_PUBLIC_ALIAS(DOS$execv, libd_execv);
DEFINE_PUBLIC_ALIAS(DOS$_execve, libd_execve);
DEFINE_PUBLIC_ALIAS(DOS$execve, libd_execve);
DEFINE_PUBLIC_ALIAS(DOS$_execvp, libd_execvp);
DEFINE_PUBLIC_ALIAS(DOS$execvp, libd_execvp);
DEFINE_PUBLIC_ALIAS(DOS$_execvpe, libd_execvpe);
DEFINE_PUBLIC_ALIAS(DOS$execvpe, libd_execvpe);
DEFINE_PUBLIC_ALIAS(DOS$__pipe, libd_pipe);
DEFINE_PUBLIC_ALIAS(DOS$pipe, libd_pipe);
DEFINE_PUBLIC_ALIAS(DOS$sleep, libd_sleep);
DEFINE_PUBLIC_ALIAS(DOS$_commit, libd_fsync);
DEFINE_PUBLIC_ALIAS(DOS$fsync, libd_fsync);
DEFINE_PUBLIC_ALIAS(DOS$__setpgid, libd_setpgid);
DEFINE_PUBLIC_ALIAS(DOS$setpgid, libd_setpgid);
DEFINE_PUBLIC_ALIAS(DOS$getgroups, libd_getgroups);
DEFINE_PUBLIC_ALIAS(DOS$setuid, libd_setuid);
DEFINE_PUBLIC_ALIAS(DOS$setgid, libd_setgid);
DEFINE_PUBLIC_ALIAS(DOS$alarm, libd_alarm);
DEFINE_PUBLIC_ALIAS(DOS$fpathconf, libd_fpathconf);
DEFINE_PUBLIC_ALIAS(DOS$ttyname, libd_ttyname);
DEFINE_PUBLIC_ALIAS(DOS$ttyname_r, libd_ttyname_r);
DEFINE_PUBLIC_ALIAS(DOS$tcgetpgrp, libd_tcgetpgrp);
DEFINE_PUBLIC_ALIAS(DOS$tcsetpgrp, libd_tcsetpgrp);
DEFINE_PUBLIC_ALIAS(DOS$chown, libd_chown);
DEFINE_PUBLIC_ALIAS(DOS$pathconf, libd_pathconf);
DEFINE_PUBLIC_ALIAS(DOS$link, libd_link);
DEFINE_PUBLIC_ALIAS(DOS$_read, libd_read);
DEFINE_PUBLIC_ALIAS(DOS$__read, libd_read);
DEFINE_PUBLIC_ALIAS(DOS$read, libd_read);
DEFINE_PUBLIC_ALIAS(DOS$_write, libd_write);
DEFINE_PUBLIC_ALIAS(DOS$__write, libd_write);
DEFINE_PUBLIC_ALIAS(DOS$write, libd_write);
DEFINE_PUBLIC_ALIAS(DOS$readall, libd_readall);
DEFINE_PUBLIC_ALIAS(DOS$writeall, libd_writeall);
DEFINE_PUBLIC_ALIAS(DOS$_lseek, libd_lseek);
DEFINE_PUBLIC_ALIAS(DOS$__lseek, libd_lseek);
DEFINE_PUBLIC_ALIAS(DOS$lseek, libd_lseek);
DEFINE_PUBLIC_ALIAS(DOS$_isatty, libd_isatty);
DEFINE_PUBLIC_ALIAS(DOS$isatty, libd_isatty);
DEFINE_PUBLIC_ALIAS(DOS$_dup2, libd_dup2);
DEFINE_PUBLIC_ALIAS(DOS$__dup2, libd_dup2);
DEFINE_PUBLIC_ALIAS(DOS$dup2, libd_dup2);
DEFINE_PUBLIC_ALIAS(DOS$_dup, libd_dup);
DEFINE_PUBLIC_ALIAS(DOS$dup, libd_dup);
DEFINE_PUBLIC_ALIAS(DOS$_close, libd_close);
DEFINE_PUBLIC_ALIAS(DOS$__close, libd_close);
DEFINE_PUBLIC_ALIAS(DOS$close, libd_close);
DEFINE_PUBLIC_ALIAS(DOS$_access, libd_access);
DEFINE_PUBLIC_ALIAS(DOS$access, libd_access);
DEFINE_PUBLIC_ALIAS(DOS$_chdir, libd_chdir);
DEFINE_PUBLIC_ALIAS(DOS$chdir, libd_chdir);
DEFINE_PUBLIC_ALIAS(DOS$_getcwd, libd_getcwd);
DEFINE_PUBLIC_ALIAS(DOS$getcwd, libd_getcwd);
DEFINE_PUBLIC_ALIAS(DOS$_unlink, libd_unlink);
DEFINE_PUBLIC_ALIAS(DOS$unlink, libd_unlink);
DEFINE_PUBLIC_ALIAS(DOS$_rmdir, libd_rmdir);
DEFINE_PUBLIC_ALIAS(DOS$rmdir, libd_rmdir);
DEFINE_PUBLIC_ALIAS(DOS$eaccess, libd_euidaccess);
DEFINE_PUBLIC_ALIAS(DOS$euidaccess, libd_euidaccess);
DEFINE_PUBLIC_ALIAS(DOS$faccessat, libd_faccessat);
DEFINE_PUBLIC_ALIAS(DOS$fchownat, libd_fchownat);
DEFINE_PUBLIC_ALIAS(DOS$linkat, libd_linkat);
DEFINE_PUBLIC_ALIAS(DOS$symlinkat, libd_symlinkat);
DEFINE_PUBLIC_ALIAS(DOS$readlinkat, libd_readlinkat);
DEFINE_PUBLIC_ALIAS(DOS$freadlinkat, libd_freadlinkat);
DEFINE_PUBLIC_ALIAS(DOS$unlinkat, libd_unlinkat);
DEFINE_PUBLIC_ALIAS(DOS$_lseeki64, libd_lseek64);
DEFINE_PUBLIC_ALIAS(DOS$lseek64, libd_lseek64);
DEFINE_PUBLIC_ALIAS(DOS$pread, libd_pread);
DEFINE_PUBLIC_ALIAS(DOS$pwrite, libd_pwrite);
DEFINE_PUBLIC_ALIAS(DOS$preadall, libd_preadall);
DEFINE_PUBLIC_ALIAS(DOS$pwriteall, libd_pwriteall);
DEFINE_PUBLIC_ALIAS(DOS$__pread64, libd_pread64);
DEFINE_PUBLIC_ALIAS(DOS$pread64, libd_pread64);
DEFINE_PUBLIC_ALIAS(DOS$__pwrite64, libd_pwrite64);
DEFINE_PUBLIC_ALIAS(DOS$pwrite64, libd_pwrite64);
DEFINE_PUBLIC_ALIAS(DOS$preadall64, libd_preadall64);
DEFINE_PUBLIC_ALIAS(DOS$pwriteall64, libd_pwriteall64);
DEFINE_PUBLIC_ALIAS(DOS$pipe2, libd_pipe2);
DEFINE_PUBLIC_ALIAS(DOS$dup3, libd_dup3);
DEFINE_PUBLIC_ALIAS(DOS$syncfs, libd_syncfs);
DEFINE_PUBLIC_ALIAS(DOS$group_member, libd_group_member);
DEFINE_PUBLIC_ALIAS(DOS$getresuid, libd_getresuid);
DEFINE_PUBLIC_ALIAS(DOS$getresgid, libd_getresgid);
DEFINE_PUBLIC_ALIAS(DOS$setresuid, libd_setresuid);
DEFINE_PUBLIC_ALIAS(DOS$setresgid, libd_setresgid);
DEFINE_PUBLIC_ALIAS(DOS$usleep, libd_usleep);
DEFINE_PUBLIC_ALIAS(DOS$getwd, libd_getwd);
DEFINE_PUBLIC_ALIAS(DOS$ualarm, libd_ualarm);
DEFINE_PUBLIC_ALIAS(DOS$fchown, libd_fchown);
DEFINE_PUBLIC_ALIAS(DOS$fchdir, libd_fchdir);
DEFINE_PUBLIC_ALIAS(DOS$__getpgid, libd_getpgid);
DEFINE_PUBLIC_ALIAS(DOS$getpgid, libd_getpgid);
DEFINE_PUBLIC_ALIAS(DOS$getsid, libd_getsid);
DEFINE_PUBLIC_ALIAS(DOS$lchown, libd_lchown);
DEFINE_PUBLIC_ALIAS(DOS$truncate, libd_truncate);
DEFINE_PUBLIC_ALIAS(DOS$truncate64, libd_truncate64);
DEFINE_PUBLIC_ALIAS(DOS$fexecve, libd_fexecve);
DEFINE_PUBLIC_ALIAS(DOS$nice, libd_nice);
DEFINE_PUBLIC_ALIAS(DOS$confstr, libd_confstr);
DEFINE_PUBLIC_ALIAS(DOS$setreuid, libd_setreuid);
DEFINE_PUBLIC_ALIAS(DOS$setregid, libd_setregid);
DEFINE_PUBLIC_ALIAS(DOS$seteuid, libd_seteuid);
DEFINE_PUBLIC_ALIAS(DOS$setegid, libd_setegid);
DEFINE_PUBLIC_ALIAS(DOS$symlink, libd_symlink);
DEFINE_PUBLIC_ALIAS(DOS$readlink, libd_readlink);
DEFINE_PUBLIC_ALIAS(DOS$getlogin_r, libd_getlogin_r);
DEFINE_PUBLIC_ALIAS(DOS$gethostname, libd_gethostname);
DEFINE_PUBLIC_ALIAS(DOS$setlogin, libd_setlogin);
DEFINE_PUBLIC_ALIAS(DOS$sethostname, libd_sethostname);
DEFINE_PUBLIC_ALIAS(DOS$sethostid, libd_sethostid);
DEFINE_PUBLIC_ALIAS(DOS$getdomainname, libd_getdomainname);
DEFINE_PUBLIC_ALIAS(DOS$setdomainname, libd_setdomainname);
DEFINE_PUBLIC_ALIAS(DOS$profil, libd_profil);
DEFINE_PUBLIC_ALIAS(DOS$daemon, libd_daemon);
DEFINE_PUBLIC_ALIAS(DOS$revoke, libd_revoke);
DEFINE_PUBLIC_ALIAS(DOS$chroot, libd_chroot);
DEFINE_PUBLIC_ALIAS(DOS$getpass, libd_getpass);
DEFINE_PUBLIC_ALIAS(DOS$_chsize, libd_ftruncate);
DEFINE_PUBLIC_ALIAS(DOS$chsize, libd_ftruncate);
DEFINE_PUBLIC_ALIAS(DOS$ftruncate, libd_ftruncate);
DEFINE_PUBLIC_ALIAS(DOS$_chsize_s, libd_ftruncate64);
DEFINE_PUBLIC_ALIAS(DOS$ftruncate64, libd_ftruncate64);
DEFINE_PUBLIC_ALIAS(DOS$brk, libd_brk);
DEFINE_PUBLIC_ALIAS(DOS$__sbrk, libd_sbrk);
DEFINE_PUBLIC_ALIAS(DOS$sbrk, libd_sbrk);
DEFINE_PUBLIC_ALIAS(DOS$fdatasync, libd_fdatasync);
DEFINE_PUBLIC_ALIAS(DOS$_swab, libd_swab);
DEFINE_PUBLIC_ALIAS(DOS$swab, libd_swab);
DEFINE_PUBLIC_ALIAS(DOS$ctermid, libd_ctermid);
DEFINE_PUBLIC_ALIAS(DOS$ctermid_r, libd_ctermid_r);
DEFINE_PUBLIC_ALIAS(DOS$_sysconf, libd_sysconf);
DEFINE_PUBLIC_ALIAS(DOS$__sysconf, libd_sysconf);
DEFINE_PUBLIC_ALIAS(DOS$sysconf, libd_sysconf);

#endif /* !GUARD_LIBC_AUTO_DOSABI_UNISTD_C */
