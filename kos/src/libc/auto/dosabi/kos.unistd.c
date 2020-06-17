/* HASH CRC-32:0xc7d78453 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_KOS_UNISTD_C
#define GUARD_LIBC_AUTO_DOSABI_KOS_UNISTD_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/kos.unistd.h"

DECL_BEGIN

/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.exec.exec") ATTR_NORETURN NONNULL((1, 2)) void
(LIBDCALL libd_Execv)(char const *__restrict path,
                      __TARGV) THROWS(...) {
	libc_Execv(path, ___argv);
}
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.exec.exec") ATTR_NORETURN NONNULL((1, 2, 3)) void
(LIBDCALL libd_Execve)(char const *__restrict path,
                       __TARGV,
                       __TENVP) THROWS(...) {
	libc_Execve(path, ___argv, ___envp);
}
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.exec.exec") ATTR_NORETURN NONNULL((1, 2)) void
(LIBDCALL libd_Execvp)(char const *__restrict file,
                       __TARGV) THROWS(...) {
	libc_Execvp(file, ___argv);
}
/* >> pipe(2)
 * Create a new pair of connected pipes ([0] = reader, [1] = writer) */
INTERN ATTR_SECTION(".text.crt.dos.except.io.access") NONNULL((1)) void
(LIBDCALL libd_Pipe)(fd_t pipedes[2]) THROWS(...) {
	libc_Pipe(pipedes);
}
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning that changes to its data and/or descriptor are written to disk */
INTERN ATTR_SECTION(".text.crt.dos.except.io.sync") void
(LIBDCALL libd_FSync)(fd_t fd) THROWS(...) {
	libc_FSync(fd);
}
/* >> setpgid(2)
 * Change the ID of the process group associated with `PID's process.
 * (That is the TID of the leader of the process group of `PID's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER = THREAD[PGID]
 * When `PID' is ZERO(0), use `gettid()' for it instead.
 * When `PGID' is ZERO(0), use `PID' (after it was substituted) for instead */
INTERN ATTR_SECTION(".text.crt.dos.except.sched.process") void
(LIBDCALL libd_SetPGid)(pid_t pid,
                        pid_t pgid) THROWS(...) {
	libc_SetPGid(pid, pgid);
}
/* >> setuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `UID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTERN ATTR_SECTION(".text.crt.dos.except.sched.process") void
(LIBDCALL libd_SetUid)(uid_t uid) THROWS(...) {
	libc_SetUid(uid);
}
/* >> setgid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `GID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTERN ATTR_SECTION(".text.crt.dos.except.sched.process") void
(LIBDCALL libd_SetGid)(gid_t gid) THROWS(...) {
	libc_SetGid(gid);
}
/* >> fpathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `FD'
 * return: * : The configuration limit associated with `NAME' for `FD'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `FD'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.property") WUNUSED long int
(LIBDCALL libd_FPathConf)(fd_t fd,
                          int name) THROWS(...) {
	return libc_FPathConf(fd, name);
}
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify") NONNULL((1)) void
(LIBDCALL libd_Chown)(char const *file,
                      uid_t owner,
                      gid_t group) THROWS(...) {
	libc_Chown(file, owner, group);
}
/* >> pathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `PATH'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.property") NONNULL((1)) long int
(LIBDCALL libd_PathConf)(char const *path,
                         int name) THROWS(...) {
	return libc_PathConf(path, name);
}
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify") NONNULL((1, 2)) void
(LIBDCALL libd_Link)(char const *from,
                     char const *to) THROWS(...) {
	libc_Link(from, to);
}
/* >> read(2)
 * Read data from a given file descriptor `FD' and return the number of bytes read.
 * A return value of ZERO(0) is indicative of EOF */
INTERN ATTR_SECTION(".text.crt.dos.except.io.read") NONNULL((2)) size_t
(LIBDCALL libd_Read)(fd_t fd,
                     void *buf,
                     size_t bufsize) THROWS(...) {
	return libc_Read(fd, buf, bufsize);
}
/* >> write(2)
 * Write data to a given file descriptor `FD' and return the number of bytes written */
INTERN ATTR_SECTION(".text.crt.dos.except.io.write") NONNULL((2)) size_t
(LIBDCALL libd_Write)(fd_t fd,
                      void const *buf,
                      size_t bufsize) THROWS(...) {
	return libc_Write(fd, buf, bufsize);
}
/* >> readall(3)
 * Same as `read(2)', however keep on reading until `read()' indicates EOF (causing
 * `readall()' to immediately return `0') or the entirety of the given buffer has been
 * filled (in which case `bufsize' is returned).
 * If an error occurrs before all data could be read, try to use SEEK_CUR to rewind
 * the file descriptor by the amount of data that had already been loaded. - Errors
 * during this phase are silently ignored and don't cause `errno' to change */
INTERN ATTR_SECTION(".text.crt.dos.except.io.read") NONNULL((2)) size_t
(LIBDCALL libd_ReadAll)(fd_t fd,
                        void *buf,
                        size_t bufsize) THROWS(...) {
	return libc_ReadAll(fd, buf, bufsize);
}
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
INTERN ATTR_SECTION(".text.crt.dos.except.io.seek") pos_t
(LIBDCALL libd_LSeek)(fd_t fd,
                      off_t offset,
                      int whence) THROWS(...) {
	return libc_LSeek(fd, offset, whence);
}
/* >> dup2(2)
 * @return: NEWFD: Returns the new handle upon success.
 * Duplicate a file referred to by `OLDFD' into `NEWFD' */
INTERN ATTR_SECTION(".text.crt.dos.except.io.access") fd_t
(LIBDCALL libd_Dup2)(fd_t oldfd,
                     fd_t newfd) THROWS(...) {
	return libc_Dup2(oldfd, newfd);
}
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `FD' and return its duplicated handle number */
INTERN ATTR_SECTION(".text.crt.dos.except.io.access") WUNUSED fd_t
NOTHROW_NCX(LIBDCALL libd_Dup)(fd_t fd) {
	return libc_Dup(fd);
}
/* >> chdir(2)
 * Change the current working directory to `PATH' */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.basic_property") NONNULL((1)) void
(LIBDCALL libd_Chdir)(char const *path) THROWS(...) {
	libc_Chdir(path);
}
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.basic_property") char *
(LIBDCALL libd_GetCwd)(char *buf,
                       size_t bufsize) THROWS(...) {
	return libc_GetCwd(buf, bufsize);
}
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) void
(LIBDCALL libd_Unlink)(char const *file) THROWS(...) {
	libc_Unlink(file);
}
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) void
(LIBDCALL libd_Rmdir)(char const *path) THROWS(...) {
	libc_Rmdir(path);
}
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify") NONNULL((2)) void
(LIBDCALL libd_FChownAt)(fd_t dfd,
                         char const *file,
                         uid_t owner,
                         gid_t group,
                         atflag_t flags) THROWS(...) {
	libc_FChownAt(dfd, file, owner, group, flags);
}
/* >> linkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify") NONNULL((2, 4)) void
(LIBDCALL libd_LinkAt)(fd_t fromfd,
                       char const *from,
                       fd_t tofd,
                       char const *to,
                       atflag_t flags) THROWS(...) {
	libc_LinkAt(fromfd, from, tofd, to, flags);
}
/* >> symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify") NONNULL((1, 3)) void
(LIBDCALL libd_SymlinkAt)(char const *link_text,
                          fd_t tofd,
                          char const *target_path) THROWS(...) {
	libc_SymlinkAt(link_text, tofd, target_path);
}
/* >> readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.property") NONNULL((2, 3)) size_t
(LIBDCALL libd_ReadlinkAt)(fd_t dfd,
                           char const *__restrict path,
                           char *__restrict buf,
                           size_t buflen) THROWS(...) {
	return libc_ReadlinkAt(dfd, path, buf, buflen);
}
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.property") NONNULL((2, 3)) size_t
(LIBDCALL libd_FReadlinkAt)(fd_t dfd,
                            char const *__restrict path,
                            char *__restrict buf,
                            size_t buflen,
                            atflag_t flags) THROWS(...) {
	return libc_FReadlinkAt(dfd, path, buf, buflen, flags);
}
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify") NONNULL((2)) void
(LIBDCALL libd_UnlinkAt)(fd_t dfd,
                         char const *name,
                         atflag_t flags) THROWS(...) {
	libc_UnlinkAt(dfd, name, flags);
}
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
INTERN ATTR_SECTION(".text.crt.dos.except.io.large.seek") pos64_t
(LIBDCALL libd_LSeek64)(fd_t fd,
                        off64_t offset,
                        int whence) THROWS(...) {
	return libc_LSeek64(fd, offset, whence);
}
/* >> pread(2)
 * Read data from a file at a specific offset */
INTERN ATTR_SECTION(".text.crt.dos.except.io.read") NONNULL((2)) size_t
(LIBDCALL libd_PRead)(fd_t fd,
                      void *buf,
                      size_t bufsize,
                      pos_t offset) THROWS(...) {
	return libc_PRead(fd, buf, bufsize, offset);
}
/* >> pwrite(2)
 * Write data to a file at a specific offset */
INTERN ATTR_SECTION(".text.crt.dos.except.io.write") NONNULL((2)) size_t
(LIBDCALL libd_PWrite)(fd_t fd,
                       void const *buf,
                       size_t bufsize,
                       pos_t offset) THROWS(...) {
	return libc_PWrite(fd, buf, bufsize, offset);
}
/* >> preadall(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
INTERN ATTR_SECTION(".text.crt.dos.except.io.read") NONNULL((2)) size_t
(LIBDCALL libd_PReadAll)(fd_t fd,
                         void *buf,
                         size_t bufsize,
                         pos_t offset) THROWS(...) {
	return libc_PReadAll(fd, buf, bufsize, offset);
}
/* >> pread64(2)
 * Read data from a file at a specific offset */
INTERN ATTR_SECTION(".text.crt.dos.except.io.large.read") NONNULL((2)) size_t
(LIBDCALL libd_PRead64)(fd_t fd,
                        void *buf,
                        size_t bufsize,
                        pos64_t offset) THROWS(...) {
	return libc_PRead64(fd, buf, bufsize, offset);
}
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
INTERN ATTR_SECTION(".text.crt.dos.except.io.large.write") NONNULL((2)) size_t
(LIBDCALL libd_PWrite64)(fd_t fd,
                         void *buf,
                         size_t bufsize,
                         pos64_t offset) THROWS(...) {
	return libc_PWrite64(fd, buf, bufsize, offset);
}
/* >> preadall64(3)
 * Same as `readall(3)', but using `pread64(2)' instead of `read()' */
INTERN ATTR_SECTION(".text.crt.dos.except.io.large.read") NONNULL((2)) size_t
(LIBDCALL libd_PReadAll64)(fd_t fd,
                           void *buf,
                           size_t bufsize,
                           pos64_t offset) THROWS(...) {
	return libc_PReadAll64(fd, buf, bufsize, offset);
}
INTERN ATTR_SECTION(".text.crt.dos.except.io.access") NONNULL((1)) void
(LIBDCALL libd_Pipe2)(fd_t pipedes[2],
                      oflag_t flags) THROWS(...) {
	libc_Pipe2(pipedes, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.except.io.access") fd_t
(LIBDCALL libd_Dup3)(fd_t oldfd,
                     fd_t newfd,
                     oflag_t flags) THROWS(...) {
	return libc_Dup3(oldfd, newfd, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify") void
(LIBDCALL libd_SyncFs)(fd_t fd) THROWS(...) {
	libc_SyncFs(fd);
}
INTERN ATTR_SECTION(".text.crt.dos.except.sched.user") void
NOTHROW_NCX(LIBDCALL libd_GetResUid)(uid_t *ruid,
                                     uid_t *euid,
                                     uid_t *suid) {
	libc_GetResUid(ruid, euid, suid);
}
INTERN ATTR_SECTION(".text.crt.dos.except.sched.user") void
NOTHROW_NCX(LIBDCALL libd_GetResGid)(gid_t *rgid,
                                     gid_t *egid,
                                     gid_t *sgid) {
	libc_GetResGid(rgid, egid, sgid);
}
INTERN ATTR_SECTION(".text.crt.dos.except.sched.user") void
NOTHROW_NCX(LIBDCALL libd_SetResUid)(uid_t ruid,
                                     uid_t euid,
                                     uid_t suid) {
	libc_SetResUid(ruid, euid, suid);
}
INTERN ATTR_SECTION(".text.crt.dos.except.sched.user") void
NOTHROW_NCX(LIBDCALL libd_SetResGid)(gid_t rgid,
                                     gid_t egid,
                                     gid_t sgid) {
	libc_SetResGid(rgid, egid, sgid);
}
/* >> fchown(2)
 * Change the ownership of a given `FD' to `GROUP:OWNER' */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify") void
(LIBDCALL libd_FChown)(fd_t fd,
                       uid_t owner,
                       gid_t group) THROWS(...) {
	libc_FChown(fd, owner, group);
}
/* >> chdir(2)
 * Change the current working directory to `PATH' */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.basic_property") void
(LIBDCALL libd_FChdir)(fd_t fd) THROWS(...) {
	libc_FChdir(fd);
}
/* >> getpgid(2)
 * Return the ID of the process group associated with `PID's process.
 * (That is the TID of the leader of the process group of `PID's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER->PID
 * When `PID' is ZERO(0), use `gettid()' for it instead */
INTERN ATTR_SECTION(".text.crt.dos.except.sched.user") WUNUSED pid_t
(LIBDCALL libd_GetPGid)(pid_t pid) THROWS(...) {
	return libc_GetPGid(pid);
}
/* >> getsid(2)
 * Return the ID of the session which a process `PID' is apart of.
 * return THREAD[PID]->LEADER->GROUP_LEADER->SESSION_LEADER->PID; */
INTERN ATTR_SECTION(".text.crt.dos.except.sched.process") WUNUSED pid_t
(LIBDCALL libd_GetSid)(pid_t pid) THROWS(...) {
	return libc_GetSid(pid);
}
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify") NONNULL((1)) void
(LIBDCALL libd_LChown)(char const *file,
                       uid_t owner,
                       gid_t group) THROWS(...) {
	libc_LChown(file, owner, group);
}
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify") NONNULL((1)) void
(LIBDCALL libd_Truncate)(char const *file,
                         pos_t length) THROWS(...) {
	libc_Truncate(file, length);
}
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify") NONNULL((1)) void
(LIBDCALL libd_Truncate64)(char const *file,
                           pos64_t length) THROWS(...) {
	libc_Truncate64(file, length);
}
/* >> fexecve(2)
 * Replace the calling process with the application image referred to by `FD' and
 * execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.exec.exec") ATTR_NORETURN NONNULL((2, 3)) void
(LIBDCALL libd_FExecve)(fd_t fd,
                        __TARGV,
                        __TENVP) THROWS(...) {
	libc_FExecve(fd, ___argv, ___envp);
}
/* >> execvpe(3)
 * Replace the calling process with the application image referred to by `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.exec.exec") ATTR_NORETURN NONNULL((1, 2, 3)) void
(LIBDCALL libd_Execvpe)(char const *__restrict file,
                        __TARGV,
                        __TENVP) THROWS(...) {
	libc_Execvpe(file, ___argv, ___envp);
}
INTERN ATTR_SECTION(".text.crt.dos.except.sched.param") int
(LIBDCALL libd_Nice)(int inc) THROWS(...) {
	return libc_Nice(inc);
}
INTERN ATTR_SECTION(".text.crt.dos.except.sched.user") void
(LIBDCALL libd_SetReUid)(uid_t ruid,
                         uid_t euid) THROWS(...) {
	libc_SetReUid(ruid, euid);
}
INTERN ATTR_SECTION(".text.crt.dos.except.sched.user") void
(LIBDCALL libd_SetReGid)(gid_t rgid,
                         gid_t egid) THROWS(...) {
	libc_SetReGid(rgid, egid);
}
/* >> seteuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `EUID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTERN ATTR_SECTION(".text.crt.dos.except.sched.user") void
(LIBDCALL libd_SetEUid)(uid_t euid) THROWS(...) {
	libc_SetEUid(euid);
}
/* >> setegid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `EGID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTERN ATTR_SECTION(".text.crt.dos.except.sched.user") void
(LIBDCALL libd_SetEGid)(gid_t egid) THROWS(...) {
	libc_SetEGid(egid);
}
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.modify") NONNULL((1, 2)) void
(LIBDCALL libd_Symlink)(char const *link_text,
                        char const *target_path) THROWS(...) {
	libc_Symlink(link_text, target_path);
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
INTERN ATTR_SECTION(".text.crt.dos.except.fs.property") NONNULL((1, 2)) size_t
(LIBDCALL libd_Readlink)(char const *__restrict path,
                         char *__restrict buf,
                         size_t buflen) THROWS(...) {
	return libc_Readlink(path, buf, buflen);
}
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
INTERN ATTR_SECTION(".text.crt.dos.except.system.configuration") NONNULL((1)) void
(LIBDCALL libd_GetHostName)(char *name,
                            size_t buflen) THROWS(...) {
	libc_GetHostName(name, buflen);
}
/* >> sethostname(2)
 * Set the name of the hosting machine */
INTERN ATTR_SECTION(".text.crt.dos.except.system.configuration") NONNULL((1)) void
(LIBDCALL libd_SetHostName)(char const *name,
                            size_t len) THROWS(...) {
	libc_SetHostName(name, len);
}
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
INTERN ATTR_SECTION(".text.crt.dos.except.system.configuration") NONNULL((1)) void
(LIBDCALL libd_GetDomainName)(char *name,
                              size_t buflen) THROWS(...) {
	libc_GetDomainName(name, buflen);
}
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
INTERN ATTR_SECTION(".text.crt.dos.except.system.configuration") NONNULL((1)) void
(LIBDCALL libd_SetDomainName)(char const *name,
                              size_t len) THROWS(...) {
	libc_SetDomainName(name, len);
}
/* >> chroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
INTERN ATTR_SECTION(".text.crt.dos.except.fs.utility") NONNULL((1)) void
(LIBDCALL libd_ChRoot)(char const *__restrict path) THROWS(...) {
	libc_ChRoot(path);
}
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
INTERN ATTR_SECTION(".text.crt.dos.except.io.write") void
(LIBDCALL libd_FTruncate)(fd_t fd,
                          pos_t length) THROWS(...) {
	libc_FTruncate(fd, length);
}
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
INTERN ATTR_SECTION(".text.crt.dos.except.io.large.write") void
(LIBDCALL libd_FTruncate64)(fd_t fd,
                            pos64_t length) THROWS(...) {
	libc_FTruncate64(fd, length);
}
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps, and its size), meaning that changes are written to disk */
INTERN ATTR_SECTION(".text.crt.dos.except.io.sync") void
(LIBDCALL libd_FDataSync)(fd_t fd) THROWS(...) {
	libc_FDataSync(fd);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$Execv, libd_Execv);
DEFINE_PUBLIC_ALIAS(DOS$Execve, libd_Execve);
DEFINE_PUBLIC_ALIAS(DOS$Execvp, libd_Execvp);
DEFINE_PUBLIC_ALIAS(DOS$Pipe, libd_Pipe);
DEFINE_PUBLIC_ALIAS(DOS$FSync, libd_FSync);
DEFINE_PUBLIC_ALIAS(DOS$SetPGid, libd_SetPGid);
DEFINE_PUBLIC_ALIAS(DOS$SetUid, libd_SetUid);
DEFINE_PUBLIC_ALIAS(DOS$SetGid, libd_SetGid);
DEFINE_PUBLIC_ALIAS(DOS$FPathConf, libd_FPathConf);
DEFINE_PUBLIC_ALIAS(DOS$Chown, libd_Chown);
DEFINE_PUBLIC_ALIAS(DOS$PathConf, libd_PathConf);
DEFINE_PUBLIC_ALIAS(DOS$Link, libd_Link);
DEFINE_PUBLIC_ALIAS(DOS$Read, libd_Read);
DEFINE_PUBLIC_ALIAS(DOS$Write, libd_Write);
DEFINE_PUBLIC_ALIAS(DOS$ReadAll, libd_ReadAll);
DEFINE_PUBLIC_ALIAS(DOS$LSeek, libd_LSeek);
DEFINE_PUBLIC_ALIAS(DOS$Dup2, libd_Dup2);
DEFINE_PUBLIC_ALIAS(DOS$Dup, libd_Dup);
DEFINE_PUBLIC_ALIAS(DOS$Chdir, libd_Chdir);
DEFINE_PUBLIC_ALIAS(DOS$GetCwd, libd_GetCwd);
DEFINE_PUBLIC_ALIAS(DOS$Unlink, libd_Unlink);
DEFINE_PUBLIC_ALIAS(DOS$Rmdir, libd_Rmdir);
DEFINE_PUBLIC_ALIAS(DOS$FChownAt, libd_FChownAt);
DEFINE_PUBLIC_ALIAS(DOS$LinkAt, libd_LinkAt);
DEFINE_PUBLIC_ALIAS(DOS$SymlinkAt, libd_SymlinkAt);
DEFINE_PUBLIC_ALIAS(DOS$ReadlinkAt, libd_ReadlinkAt);
DEFINE_PUBLIC_ALIAS(DOS$FReadlinkAt, libd_FReadlinkAt);
DEFINE_PUBLIC_ALIAS(DOS$UnlinkAt, libd_UnlinkAt);
DEFINE_PUBLIC_ALIAS(DOS$LSeek64, libd_LSeek64);
DEFINE_PUBLIC_ALIAS(DOS$PRead, libd_PRead);
DEFINE_PUBLIC_ALIAS(DOS$PWrite, libd_PWrite);
DEFINE_PUBLIC_ALIAS(DOS$PReadAll, libd_PReadAll);
DEFINE_PUBLIC_ALIAS(DOS$PRead64, libd_PRead64);
DEFINE_PUBLIC_ALIAS(DOS$PWrite64, libd_PWrite64);
DEFINE_PUBLIC_ALIAS(DOS$PReadAll64, libd_PReadAll64);
DEFINE_PUBLIC_ALIAS(DOS$Pipe2, libd_Pipe2);
DEFINE_PUBLIC_ALIAS(DOS$Dup3, libd_Dup3);
DEFINE_PUBLIC_ALIAS(DOS$SyncFs, libd_SyncFs);
DEFINE_PUBLIC_ALIAS(DOS$GetResUid, libd_GetResUid);
DEFINE_PUBLIC_ALIAS(DOS$GetResGid, libd_GetResGid);
DEFINE_PUBLIC_ALIAS(DOS$SetResUid, libd_SetResUid);
DEFINE_PUBLIC_ALIAS(DOS$SetResGid, libd_SetResGid);
DEFINE_PUBLIC_ALIAS(DOS$FChown, libd_FChown);
DEFINE_PUBLIC_ALIAS(DOS$FChdir, libd_FChdir);
DEFINE_PUBLIC_ALIAS(DOS$GetPGid, libd_GetPGid);
DEFINE_PUBLIC_ALIAS(DOS$GetSid, libd_GetSid);
DEFINE_PUBLIC_ALIAS(DOS$LChown, libd_LChown);
DEFINE_PUBLIC_ALIAS(DOS$Truncate, libd_Truncate);
DEFINE_PUBLIC_ALIAS(DOS$Truncate64, libd_Truncate64);
DEFINE_PUBLIC_ALIAS(DOS$FExecve, libd_FExecve);
DEFINE_PUBLIC_ALIAS(DOS$Execvpe, libd_Execvpe);
DEFINE_PUBLIC_ALIAS(DOS$Nice, libd_Nice);
DEFINE_PUBLIC_ALIAS(DOS$SetReUid, libd_SetReUid);
DEFINE_PUBLIC_ALIAS(DOS$SetReGid, libd_SetReGid);
DEFINE_PUBLIC_ALIAS(DOS$SetEUid, libd_SetEUid);
DEFINE_PUBLIC_ALIAS(DOS$SetEGid, libd_SetEGid);
DEFINE_PUBLIC_ALIAS(DOS$Symlink, libd_Symlink);
DEFINE_PUBLIC_ALIAS(DOS$Readlink, libd_Readlink);
DEFINE_PUBLIC_ALIAS(DOS$GetHostName, libd_GetHostName);
DEFINE_PUBLIC_ALIAS(DOS$SetHostName, libd_SetHostName);
DEFINE_PUBLIC_ALIAS(DOS$GetDomainName, libd_GetDomainName);
DEFINE_PUBLIC_ALIAS(DOS$SetDomainName, libd_SetDomainName);
DEFINE_PUBLIC_ALIAS(DOS$ChRoot, libd_ChRoot);
DEFINE_PUBLIC_ALIAS(DOS$FTruncate, libd_FTruncate);
DEFINE_PUBLIC_ALIAS(DOS$FTruncate64, libd_FTruncate64);
DEFINE_PUBLIC_ALIAS(DOS$FDataSync, libd_FDataSync);

#endif /* !GUARD_LIBC_AUTO_DOSABI_KOS_UNISTD_C */
