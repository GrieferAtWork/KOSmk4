/* HASH CRC-32:0x81e99a4e */
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
#ifndef GUARD_LIBC_USER_KOS_UNISTD_H
#define GUARD_LIBC_USER_KOS_UNISTD_H 1

#include "../api.h"
#include <kos/anno.h>
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/unistd.h>

DECL_BEGIN

/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTDEF ATTR_NORETURN NONNULL((1, 2)) void (LIBCCALL libc_Execv)(char const *__restrict path, __TARGV) __THROWS(...);
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTDEF ATTR_NORETURN NONNULL((1, 2, 3)) void (LIBCCALL libc_Execve)(char const *__restrict path, __TARGV, __TENVP) __THROWS(...);
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTDEF ATTR_NORETURN NONNULL((1, 2)) void (LIBCCALL libc_Execvp)(char const *__restrict file, __TARGV) __THROWS(...);
/* >> execl(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
INTDEF ATTR_NORETURN ATTR_SENTINEL NONNULL((1)) void (VLIBCCALL libc_Execl)(char const *__restrict path, char const *args, ... /*, (char *)NULL*/) __THROWS(...);
/* >> execle(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list, and setting `environ' to a `char **' passed after the NULL sentinel */
INTDEF ATTR_NORETURN NONNULL((1)) ATTR_SENTINEL_O(1) void (VLIBCCALL libc_Execle)(char const *__restrict path, char const *args, ... /*, (char *)NULL, (char **)environ*/) __THROWS(...);
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
INTDEF ATTR_NORETURN ATTR_SENTINEL NONNULL((1)) void (VLIBCCALL libc_Execpl)(char const *__restrict file, char const *args, ... /*, (char *)NULL*/) __THROWS(...);
/* >> execle(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list, and setting `environ' to a `char **' passed after the NULL sentinel */
INTDEF ATTR_NORETURN NONNULL((1)) ATTR_SENTINEL_O(1) void (VLIBCCALL libc_Execlpe)(char const *__restrict file, char const *args, ... /*, (char *)NULL, (char **)environ*/) __THROWS(...);
/* >> pipe(2)
 * Create a new pair of connected pipes ([0] = reader, [1] = writer) */
INTDEF NONNULL((1)) void (LIBCCALL libc_Pipe)(fd_t pipedes[2]) __THROWS(...);
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning that changes to its data and/or descriptor are written to disk */
INTDEF void (LIBCCALL libc_FSync)(fd_t fd) __THROWS(...);
/* >> setpgid(2)
 * Change the ID of the process group associated with `PID's process.
 * (That is the TID of the leader of the process group of `PID's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER = THREAD[PGID]
 * When `PID' is ZERO(0), use `gettid()' for it instead.
 * When `PGID' is ZERO(0), use `PID' (after it was substituted) for instead */
INTDEF void (LIBCCALL libc_SetPGid)(pid_t pid, pid_t pgid) __THROWS(...);
/* >> setsid(2)
 * Make the calling thread's process the leader of its associated
 * process group, before also making it its own session leader.
 * Then return the TID of that new session leader, which is also the PID of the calling process.
 * THIS_THREAD->LEADER->GROUP_LEADER                 = THIS_THREAD->LEADER;
 * THIS_THREAD->LEADER->GROUP_LEADER->SESSION_LEADER = THIS_THREAD->LEADER->GROUP_LEADER;
 * return THIS_THREAD->LEADER->PID; */
INTDEF pid_t (LIBCCALL libc_SetSid)(void) __THROWS(...);
/* >> setuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `UID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF void (LIBCCALL libc_SetUid)(uid_t uid) __THROWS(...);
/* >> setgid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `GID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF void (LIBCCALL libc_SetGid)(gid_t gid) __THROWS(...);
/* >> fork(2)
 * Clone the calling thread into a second process and return twice, once
 * in the parent process where this function returns the (non-zero) PID
 * of the forked child process, and a second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with that of another program that the original
 * parent can then `wait(2)' for */
INTDEF WUNUSED pid_t (LIBCCALL libc_Fork)(void) __THROWS(...);
/* >> fpathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `FD'
 * return: * : The configuration limit associated with `NAME' for `FD'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `FD'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
INTDEF WUNUSED long int (LIBCCALL libc_FPathConf)(fd_t fd, int name) __THROWS(...);
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
INTDEF NONNULL((1)) void (LIBCCALL libc_Chown)(char const *file, uid_t owner, gid_t group) __THROWS(...);
/* >> pathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `PATH'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
INTDEF NONNULL((1)) long int (LIBCCALL libc_PathConf)(char const *path, int name) __THROWS(...);
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
INTDEF NONNULL((1, 2)) void (LIBCCALL libc_Link)(char const *from, char const *to) __THROWS(...);
/* >> read(2)
 * Read data from a given file descriptor `FD' and return the number of bytes read.
 * A return value of ZERO(0) is indicative of EOF */
INTDEF NONNULL((2)) size_t (LIBCCALL libc_Read)(fd_t fd, void *buf, size_t bufsize) __THROWS(...);
/* >> write(2)
 * Write data to a given file descriptor `FD' and return the number of bytes written */
INTDEF NONNULL((2)) size_t (LIBCCALL libc_Write)(fd_t fd, void const *buf, size_t bufsize) __THROWS(...);
/* >> readall(3)
 * Same as `read(2)', however keep on reading until `read()' indicates EOF (causing
 * `readall()' to immediately return `0') or the entirety of the given buffer has been
 * filled (in which case `bufsize' is returned).
 * If an error occurrs before all data could be read, try to use SEEK_CUR to rewind
 * the file descriptor by the amount of data that had already been loaded. - Errors
 * during this phase are silently ignored and don't cause `errno' to change */
INTDEF NONNULL((2)) size_t (LIBCCALL libc_ReadAll)(fd_t fd, void *buf, size_t bufsize) __THROWS(...);
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
INTDEF pos_t (LIBCCALL libc_LSeek)(fd_t fd, off_t offset, int whence) __THROWS(...);
/* >> dup2(2)
 * @return: NEWFD: Returns the new handle upon success.
 * Duplicate a file referred to by `OLDFD' into `NEWFD' */
INTDEF fd_t (LIBCCALL libc_Dup2)(fd_t oldfd, fd_t newfd) __THROWS(...);
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `FD' and return its duplicated handle number */
INTDEF WUNUSED fd_t NOTHROW_NCX(LIBCCALL libc_Dup)(fd_t fd);
/* >> chdir(2)
 * Change the current working directory to `PATH' */
INTDEF NONNULL((1)) void (LIBCCALL libc_Chdir)(char const *path) __THROWS(...);
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
INTDEF char *(LIBCCALL libc_GetCwd)(char *buf, size_t bufsize) __THROWS(...);
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
INTDEF NONNULL((1)) void (LIBCCALL libc_Unlink)(char const *file) __THROWS(...);
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
INTDEF NONNULL((1)) void (LIBCCALL libc_Rmdir)(char const *path) __THROWS(...);
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
INTDEF NONNULL((2)) void (LIBCCALL libc_FChownAt)(fd_t dfd, char const *file, uid_t owner, gid_t group, atflag_t flags) __THROWS(...);
/* >> linkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
INTDEF NONNULL((2, 4)) void (LIBCCALL libc_LinkAt)(fd_t fromfd, char const *from, fd_t tofd, char const *to, atflag_t flags) __THROWS(...);
/* >> symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
INTDEF NONNULL((1, 3)) void (LIBCCALL libc_SymlinkAt)(char const *link_text, fd_t tofd, char const *target_path) __THROWS(...);
/* >> readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
INTDEF NONNULL((2, 3)) size_t (LIBCCALL libc_ReadlinkAt)(fd_t dfd, char const *__restrict path, char *__restrict buf, size_t buflen) __THROWS(...);
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
INTDEF NONNULL((2, 3)) size_t (LIBCCALL libc_FReadlinkAt)(fd_t dfd, char const *__restrict path, char *__restrict buf, size_t buflen, atflag_t flags) __THROWS(...);
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
INTDEF NONNULL((2)) void (LIBCCALL libc_UnlinkAt)(fd_t dfd, char const *name, atflag_t flags) __THROWS(...);
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
INTDEF pos64_t (LIBCCALL libc_LSeek64)(fd_t fd, off64_t offset, int whence) __THROWS(...);
/* >> pread(2)
 * Read data from a file at a specific offset */
INTDEF NONNULL((2)) size_t (LIBCCALL libc_PRead)(fd_t fd, void *buf, size_t bufsize, pos_t offset) __THROWS(...);
/* >> pwrite(2)
 * Write data to a file at a specific offset */
INTDEF NONNULL((2)) size_t (LIBCCALL libc_PWrite)(fd_t fd, void const *buf, size_t bufsize, pos_t offset) __THROWS(...);
/* >> preadall(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
INTDEF NONNULL((2)) size_t (LIBCCALL libc_PReadAll)(fd_t fd, void *buf, size_t bufsize, pos_t offset) __THROWS(...);
/* >> pread64(2)
 * Read data from a file at a specific offset */
INTDEF NONNULL((2)) size_t (LIBCCALL libc_PRead64)(fd_t fd, void *buf, size_t bufsize, pos64_t offset) __THROWS(...);
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
INTDEF NONNULL((2)) size_t (LIBCCALL libc_PWrite64)(fd_t fd, void *buf, size_t bufsize, pos64_t offset) __THROWS(...);
/* >> preadall64(3)
 * Same as `readall(3)', but using `pread64(2)' instead of `read()' */
INTDEF NONNULL((2)) size_t (LIBCCALL libc_PReadAll64)(fd_t fd, void *buf, size_t bufsize, pos64_t offset) __THROWS(...);
INTDEF NONNULL((1)) void (LIBCCALL libc_Pipe2)(fd_t pipedes[2], oflag_t flags) __THROWS(...);
INTDEF fd_t (LIBCCALL libc_Dup3)(fd_t oldfd, fd_t newfd, oflag_t flags) __THROWS(...);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED char *(LIBCCALL libc_GetCurrentDirName)(void) __THROWS(...);
INTDEF void (LIBCCALL libc_SyncFs)(fd_t fd) __THROWS(...);
INTDEF void NOTHROW_NCX(LIBCCALL libc_GetResUid)(uid_t *ruid, uid_t *euid, uid_t *suid);
INTDEF void NOTHROW_NCX(LIBCCALL libc_GetResGid)(gid_t *rgid, gid_t *egid, gid_t *sgid);
INTDEF void NOTHROW_NCX(LIBCCALL libc_SetResUid)(uid_t ruid, uid_t euid, uid_t suid);
INTDEF void NOTHROW_NCX(LIBCCALL libc_SetResGid)(gid_t rgid, gid_t egid, gid_t sgid);
/* >> vfork(2)
 * Same as `fork(2)', but possibly suspend the calling process until the
 * child process either calls `exit(2)' or one of the many `exec(2)' functions */
INTDEF ATTR_RETURNS_TWICE WUNUSED pid_t (LIBCCALL libc_VFork)(void) __THROWS(...);
/* >> fchown(2)
 * Change the ownership of a given `FD' to `GROUP:OWNER' */
INTDEF void (LIBCCALL libc_FChown)(fd_t fd, uid_t owner, gid_t group) __THROWS(...);
/* >> chdir(2)
 * Change the current working directory to `PATH' */
INTDEF void (LIBCCALL libc_FChdir)(fd_t fd) __THROWS(...);
/* >> getpgid(2)
 * Return the ID of the process group associated with `PID's process.
 * (That is the TID of the leader of the process group of `PID's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER->PID
 * When `PID' is ZERO(0), use `gettid()' for it instead */
INTDEF WUNUSED pid_t (LIBCCALL libc_GetPGid)(pid_t pid) __THROWS(...);
/* >> getsid(2)
 * Return the ID of the session which a process `PID' is apart of.
 * return THREAD[PID]->LEADER->GROUP_LEADER->SESSION_LEADER->PID; */
INTDEF WUNUSED pid_t (LIBCCALL libc_GetSid)(pid_t pid) __THROWS(...);
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
INTDEF NONNULL((1)) void (LIBCCALL libc_LChown)(char const *file, uid_t owner, gid_t group) __THROWS(...);
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
INTDEF NONNULL((1)) void (LIBCCALL libc_Truncate)(char const *file, pos_t length) __THROWS(...);
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
INTDEF NONNULL((1)) void (LIBCCALL libc_Truncate64)(char const *file, pos64_t length) __THROWS(...);
/* >> fexecve(2)
 * Replace the calling process with the application image referred to by `FD' and
 * execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTDEF ATTR_NORETURN NONNULL((2, 3)) void (LIBCCALL libc_FExecve)(fd_t fd, __TARGV, __TENVP) __THROWS(...);
/* >> execvpe(3)
 * Replace the calling process with the application image referred to by `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTDEF ATTR_NORETURN NONNULL((1, 2, 3)) void (LIBCCALL libc_Execvpe)(char const *__restrict file, __TARGV, __TENVP) __THROWS(...);
INTDEF int (LIBCCALL libc_Nice)(int inc) __THROWS(...);
/* >> setpgrp(3)
 * Move the calling process into its own process group.
 * Equivalent to `setpgid(0, 0)' */
INTDEF void (LIBCCALL libc_SetPGrp)(void) __THROWS(...);
INTDEF void (LIBCCALL libc_SetReUid)(uid_t ruid, uid_t euid) __THROWS(...);
INTDEF void (LIBCCALL libc_SetReGid)(gid_t rgid, gid_t egid) __THROWS(...);
/* >> seteuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `EUID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF void (LIBCCALL libc_SetEUid)(uid_t euid) __THROWS(...);
/* >> setegid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `EGID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF void (LIBCCALL libc_SetEGid)(gid_t egid) __THROWS(...);
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
INTDEF NONNULL((1, 2)) void (LIBCCALL libc_Symlink)(char const *link_text, char const *target_path) __THROWS(...);
/* >> readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
INTDEF NONNULL((1, 2)) size_t (LIBCCALL libc_Readlink)(char const *__restrict path, char *__restrict buf, size_t buflen) __THROWS(...);
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
INTDEF NONNULL((1)) void (LIBCCALL libc_GetHostName)(char *name, size_t buflen) __THROWS(...);
/* >> sethostname(2)
 * Set the name of the hosting machine */
INTDEF NONNULL((1)) void (LIBCCALL libc_SetHostName)(char const *name, size_t len) __THROWS(...);
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
INTDEF NONNULL((1)) void (LIBCCALL libc_GetDomainName)(char *name, size_t buflen) __THROWS(...);
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
INTDEF NONNULL((1)) void (LIBCCALL libc_SetDomainName)(char const *name, size_t len) __THROWS(...);
INTDEF __syscall_slong_t (VLIBCCALL libc_Syscall)(__syscall_ulong_t sysno, ...) __THROWS(...);
INTDEF __LONG64_TYPE__ (VLIBCCALL libc_Syscall64)(__syscall_ulong_t sysno, ...) __THROWS(...);
/* >> chroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
INTDEF NONNULL((1)) void (LIBCCALL libc_ChRoot)(char const *__restrict path) __THROWS(...);
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
INTDEF void (LIBCCALL libc_FTruncate)(fd_t fd, pos_t length) __THROWS(...);
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
INTDEF void (LIBCCALL libc_FTruncate64)(fd_t fd, pos64_t length) __THROWS(...);
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps, and its size), meaning that changes are written to disk */
INTDEF void (LIBCCALL libc_FDataSync)(fd_t fd) __THROWS(...);

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_UNISTD_H */
