/* HASH CRC-32:0xf9884365 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_KOS_UNISTD_H
#define GUARD_LIBC_USER_KOS_UNISTD_H 1

#include "../api.h"
#include "../auto/kos.unistd.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/unistd.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> execv(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTDEF ATTR_NORETURN ATTR_IN(1) ATTR_IN(2) void (LIBCCALL libc_Execv)(char const *__restrict path, __TARGV) THROWS(...);
/* >> execve(2)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTDEF ATTR_NORETURN ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) void (LIBCCALL libc_Execve)(char const *__restrict path, __TARGV, __TENVP) THROWS(...);
/* >> execvp(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTDEF ATTR_NORETURN ATTR_IN(1) ATTR_IN(2) void (LIBCCALL libc_Execvp)(char const *__restrict file, __TARGV) THROWS(...);
/* >> pipe(2)
 * Create a new pair of connected pipes ([0] = reader, [1] = writer)
 * @param: pipedes: Output for pipe fds: [0]: reader; [1]: writer
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_OUT(1) void (LIBCCALL libc_Pipe)(fd_t pipedes[2]) THROWS(...);
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
INTDEF void (LIBCCALL libc_FSync)(fd_t fd) THROWS(...);
/* >> setpgid(2)
 * Change  the ID of  the process group  associated with `pid's process.
 * (That is the TID of the leader of the process group of `pid's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER = THREAD[PGID]
 * When `pid' is ZERO(0), use `gettid()' for it instead.
 * When `pgid' is ZERO(0), use `pid' (after it was substituted) for instead */
INTDEF void (LIBCCALL libc_SetPGid)(pid_t pid, pid_t pgid) THROWS(...);
/* >> setsid(2)
 * Make the calling thread's process the leader of its associated
 * process group, before also making  it its own session  leader.
 * Then return the TID of that new session leader, which is also the PID of the calling process.
 *  - THIS_THREAD->LEADER->GROUP_LEADER                 = THIS_THREAD->LEADER;
 *  - THIS_THREAD->LEADER->GROUP_LEADER->SESSION_LEADER = THIS_THREAD->LEADER->GROUP_LEADER;
 *  - return THIS_THREAD->LEADER->PID; */
INTDEF pid_t (LIBCCALL libc_SetSid)(void) THROWS(...);
/* >> setuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `uid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF void (LIBCCALL libc_SetUid)(uid_t uid) THROWS(...);
/* >> setgid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `gid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF void (LIBCCALL libc_SetGid)(gid_t gid) THROWS(...);
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
INTDEF WUNUSED pid_t (LIBCCALL libc_Fork)(void) THROWS(...);
/* >> fpathconf(3)
 * @param: name: One   of    `_PC_*'    from    <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `fd'
 * return: * : The configuration limit associated with `name' for `fd'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `fd'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
INTDEF WUNUSED longptr_t (LIBCCALL libc_FPathConf)(fd_t fd, __STDC_INT_AS_UINT_T name) THROWS(...);
/* >> pathconf(3)
 * @param: name: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `path'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `path'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
INTDEF ATTR_IN(1) longptr_t (LIBCCALL libc_PathConf)(char const *path, __STDC_INT_AS_UINT_T name) THROWS(...);
/* >> chown(2)
 * Change the ownership of a given `file' to `group:owner' */
INTDEF ATTR_IN(1) void (LIBCCALL libc_ChOwn)(char const *file, uid_t owner, gid_t group) THROWS(...);
/* >> link(2)
 * Create a hard link from `from', leading to `to' */
INTDEF ATTR_IN(1) ATTR_IN(2) void (LIBCCALL libc_Link)(char const *from, char const *to) THROWS(...);
/* >> read(2)
 * Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the  `O_NONBLOCK' flag set,  only read as  much data as  was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
INTDEF ATTR_OUTS(2, 3) size_t (LIBCCALL libc_Read)(fd_t fd, void *buf, size_t bufsize) THROWS(...);
/* >> write(2)
 * Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much  data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
INTDEF ATTR_INS(2, 3) size_t (LIBCCALL libc_Write)(fd_t fd, void const *buf, size_t bufsize) THROWS(...);
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
INTDEF pos_t (LIBCCALL libc_LSeek)(fd_t fd, off_t offset, int whence) THROWS(...);
/* >> dup2(2)
 * @return: newfd: Returns the new handle upon success.
 * Duplicate a file referred to by `oldfd' into `newfd' */
INTDEF fd_t (LIBCCALL libc_Dup2)(fd_t oldfd, fd_t newfd) THROWS(...);
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `fd' and return its duplicated handle number */
INTDEF WUNUSED fd_t (LIBCCALL libc_Dup)(fd_t fd) THROWS(...);
/* >> chdir(2)
 * Change the current working directory to `path' */
INTDEF ATTR_IN(1) void (LIBCCALL libc_ChDir)(char const *path) THROWS(...);
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
INTDEF ATTR_OUTS(1, 2) char *(LIBCCALL libc_GetCwd)(char *buf, size_t bufsize) THROWS(...);
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
INTDEF ATTR_IN(1) void (LIBCCALL libc_Unlink)(char const *file) THROWS(...);
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
INTDEF ATTR_IN(1) void (LIBCCALL libc_RmDir)(char const *path) THROWS(...);
/* >> fchownat(2)
 * Change the ownership of a given `dfd:file' to `group:owner' */
INTDEF ATTR_IN(2) void (LIBCCALL libc_FChOwnAt)(fd_t dfd, char const *file, uid_t owner, gid_t group, atflag_t flags) THROWS(...);
/* >> linkat(2)
 * Create a hard link from `fromfd:from', leading to `tofd:to' */
INTDEF ATTR_IN(2) ATTR_IN(4) void (LIBCCALL libc_LinkAt)(fd_t fromfd, char const *from, fd_t tofd, char const *to, atflag_t flags) THROWS(...);
/* >> symlinkat(3)
 * Create  a  new  symbolic  link  loaded  with  `link_text'  as link
 * text, at the filesystem location referred to by `tofd:target_path' */
INTDEF ATTR_IN(1) ATTR_IN(3) void (LIBCCALL libc_SymlinkAt)(char const *link_text, fd_t tofd, char const *target_path) THROWS(...);
/* >> readlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
INTDEF ATTR_IN(2) ATTR_OUTS(3, 4) size_t (LIBCCALL libc_ReadLinkAt)(fd_t dfd, char const *__restrict path, char *__restrict buf, size_t buflen) THROWS(...);
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `dfd:name' */
INTDEF ATTR_IN(2) void (LIBCCALL libc_UnlinkAt)(fd_t dfd, char const *name, atflag_t flags) THROWS(...);
/* >> fchdirat(2)
 * Change the current working directory to `dfd:path'
 * @param: flags: Set of `0 | AT_DOSPATH' */
INTDEF ATTR_IN(2) void (LIBCCALL libc_FChDirAt)(fd_t dfd, char const *path, atflag_t flags) THROWS(...);
/* >> fsymlinkat(3)
 * Create  a  new  symbolic  link  loaded  with  `link_text'  as link
 * text, at the filesystem location referred to by `tofd:target_path'
 * @param flags: Set of `0 | AT_DOSPATH' */
INTDEF ATTR_IN(1) ATTR_IN(3) void (LIBCCALL libc_FSymlinkAt)(char const *link_text, fd_t tofd, char const *target_path, atflag_t flags) THROWS(...);
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH | AT_READLINK_REQSIZE' */
INTDEF ATTR_IN(2) ATTR_OUTS(3, 4) size_t (LIBCCALL libc_FReadLinkAt)(fd_t dfd, char const *__restrict path, char *__restrict buf, size_t buflen, atflag_t flags) THROWS(...);
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
INTDEF pos64_t (LIBCCALL libc_LSeek64)(fd_t fd, off64_t offset, int whence) THROWS(...);
/* >> pread(2), pread64(2)
 * Read data from a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of read bytes */
INTDEF ATTR_OUTS(2, 3) size_t (LIBCCALL libc_PRead)(fd_t fd, void *buf, size_t bufsize, pos_t offset) THROWS(...);
/* >> pwrite(2), pwrite64(2)
 * Write data to a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of written bytes */
INTDEF ATTR_INS(2, 3) size_t (LIBCCALL libc_PWrite)(fd_t fd, void const *buf, size_t bufsize, pos_t offset) THROWS(...);
/* >> pread(2), pread64(2)
 * Read data from a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of read bytes */
INTDEF ATTR_OUTS(2, 3) size_t (LIBCCALL libc_PRead64)(fd_t fd, void *buf, size_t bufsize, pos64_t offset) THROWS(...);
/* >> pwrite(2), pwrite64(2)
 * Write data to a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of written bytes */
INTDEF ATTR_INS(2, 3) size_t (LIBCCALL libc_PWrite64)(fd_t fd, void const *buf, size_t bufsize, pos64_t offset) THROWS(...);
/* >> pipe2(2)
 * Construct a [reader,writer]-pair of pipes
 * @param: pipedes: Output for pipe fds: [0]: reader; [1]: writer
 * @param: flags:   Set of `O_CLOEXEC | O_CLOFORK | O_NONBLOCK | O_DIRECT'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_OUT(1) void (LIBCCALL libc_Pipe2)(fd_t pipedes[2], oflag_t flags) THROWS(...);
INTDEF fd_t (LIBCCALL libc_Dup3)(fd_t oldfd, fd_t newfd, oflag_t flags) THROWS(...);
INTDEF void (LIBCCALL libc_SyncFS)(fd_t fd) THROWS(...);
/* >> getresuid(2)
 * Get the real, effective, and saved UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_OUT_OPT(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(3) void (LIBCCALL libc_GetRESUid)(uid_t *ruid, uid_t *euid, uid_t *suid) THROWS(...);
/* >> getresgid(2)
 * Get the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_OUT_OPT(1) ATTR_OUT_OPT(2) ATTR_OUT_OPT(3) void (LIBCCALL libc_GetRESGid)(gid_t *rgid, gid_t *egid, gid_t *sgid) THROWS(...);
/* >> setresuid(2)
 * Set the real, effective, and saved UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF void (LIBCCALL libc_SetRESUid)(uid_t ruid, uid_t euid, uid_t suid) THROWS(...);
/* >> setresgid(2)
 * Set the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF void (LIBCCALL libc_SetRESGid)(gid_t rgid, gid_t egid, gid_t sgid) THROWS(...);
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
INTDEF ATTR_RETURNS_TWICE WUNUSED pid_t (LIBCCALL libc_VFork)(void) THROWS(...);
/* >> fchown(2)
 * Change the ownership of a given `fd' to `group:owner' */
INTDEF void (LIBCCALL libc_FChOwn)(fd_t fd, uid_t owner, gid_t group) THROWS(...);
/* >> fchdir(2)
 * Change the current working directory to `path' */
INTDEF void (LIBCCALL libc_FChDir)(fd_t fd) THROWS(...);
/* >> getpgid(2)
 * Return  the ID of  the process group  associated with `pid's process.
 * (That is the TID of the leader of the process group of `pid's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER->PID
 * When `pid' is ZERO(0), use `gettid()' for it instead */
INTDEF WUNUSED pid_t (LIBCCALL libc_GetPGid)(pid_t pid) THROWS(...);
/* >> getsid(2)
 * Return the ID of the session which a process `pid' is apart of.
 * return  THREAD[PID]->LEADER->GROUP_LEADER->SESSION_LEADER->PID; */
INTDEF WUNUSED pid_t (LIBCCALL libc_GetSid)(pid_t pid) THROWS(...);
/* >> lchown(2)
 * Change the ownership of a given `file' to `group:owner',
 * but don't reference it if  that file is a symbolic  link */
INTDEF ATTR_IN(1) void (LIBCCALL libc_LChOwn)(char const *file, uid_t owner, gid_t group) THROWS(...);
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
INTDEF ATTR_IN(1) void (LIBCCALL libc_Truncate)(char const *file, pos_t length) THROWS(...);
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
INTDEF ATTR_IN(1) void (LIBCCALL libc_Truncate64)(char const *file, pos64_t length) THROWS(...);
/* >> fexecve(2)
 * Replace the calling process with the application image referred
 * to by `execfd'  and execute it's  `main()' method, passing  the
 * given `argv', and setting `environ' to `envp'. */
INTDEF ATTR_NORETURN ATTR_IN(2) ATTR_IN(3) void (LIBCCALL libc_FExecve)(fd_t fd, __TARGV, __TENVP) THROWS(...);
/* >> execvpe(3)
 * Replace the  calling process  with the  application  image referred  to by  `file'  and
 * execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTDEF ATTR_NORETURN ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) void (LIBCCALL libc_Execvpe)(char const *__restrict file, __TARGV, __TENVP) THROWS(...);
/* >> confstr(3)
 * Retrieve a system configuration string specified by `name'
 * @param: name:   One of `_CS_*' from <asm/crt/confname.h>
 * @param: buf:    Target buffer
 * @param: buflen: Available buffer size (including a trailing \0-character)
 * @return: * :    Required buffer size (including a trailing \0-character)
 * @return: 1 :    Empty configuration string.
 * @return: 0 :    [errno=EINVAL] Bad configuration `name'. */
INTDEF ATTR_OUTS(2, 3) size_t (LIBCCALL libc_ConfStr)(__STDC_INT_AS_UINT_T name, char *buf, size_t buflen) THROWS(...);
INTDEF int (LIBCCALL libc_Nice)(int inc) THROWS(...);
/* >> setpgrp(3)
 * Move the calling process into its own process group.
 * Equivalent to `setpgid(0, 0)' */
INTDEF void (LIBCCALL libc_SetPGrp)(void) THROWS(...);
/* >> setreuid(2)
 * Set the real and effective UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF void (LIBCCALL libc_SetREUid)(uid_t ruid, uid_t euid) THROWS(...);
/* >> setregid(2)
 * Set the real and effective GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF void (LIBCCALL libc_SetREGid)(gid_t rgid, gid_t egid) THROWS(...);
/* >> seteuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `euid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF void (LIBCCALL libc_SetEUid)(uid_t euid) THROWS(...);
/* >> setegid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `egid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
INTDEF void (LIBCCALL libc_SetEGid)(gid_t egid) THROWS(...);
/* >> symlink(3)
 * Create  a new  symbolic link  loaded with  `link_text' as link
 * text, at the filesystem location referred to by `target_path'.
 * Same as `symlinkat(link_text, AT_FDCWD, target_path)' */
INTDEF ATTR_IN(1) ATTR_IN(2) void (LIBCCALL libc_Symlink)(char const *link_text, char const *target_path) THROWS(...);
/* >> readlink(3)
 * Read the text of a symbolic link under `path' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, path, buf, buflen)'
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
INTDEF ATTR_IN(1) ATTR_OUTS(2, 3) size_t (LIBCCALL libc_ReadLink)(char const *__restrict path, char *__restrict buf, size_t buflen) THROWS(...);
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
INTDEF ATTR_OUTS(1, 2) void (LIBCCALL libc_GetHostName)(char *name, size_t buflen) THROWS(...);
/* >> sethostname(2)
 * Set the name of the hosting machine */
INTDEF ATTR_INS(1, 2) void (LIBCCALL libc_SetHostName)(char const *name, size_t len) THROWS(...);
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
INTDEF ATTR_OUTS(1, 2) void (LIBCCALL libc_GetDomainName)(char *name, size_t buflen) THROWS(...);
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
INTDEF ATTR_INS(1, 2) void (LIBCCALL libc_SetDomainName)(char const *name, size_t len) THROWS(...);
INTDEF __syscall_slong_t (VLIBCCALL libc_Syscall)(syscall_ulong_t sysno, ...) THROWS(...);
INTDEF __LONG64_TYPE__ (VLIBCCALL libc_Syscall64)(syscall_ulong_t sysno, ...) THROWS(...);
/* >> chroot(2)
 * Change  the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `path' */
INTDEF ATTR_IN(1) void (LIBCCALL libc_ChRoot)(char const *__restrict path) THROWS(...);
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
INTDEF void (LIBCCALL libc_FTruncate)(fd_t fd, pos_t length) THROWS(...);
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
INTDEF void (LIBCCALL libc_FTruncate64)(fd_t fd, pos64_t length) THROWS(...);
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps,  and its size),  meaning that changes  are written to disk */
INTDEF void (LIBCCALL libc_FDataSync)(fd_t fd) THROWS(...);
/* >> lpathconf(3)
 * Same as `pathconf(3)', but don't dereference `path' if it's a symbolic link */
INTDEF ATTR_IN(1) longptr_t (LIBCCALL libc_LPathConf)(char const *path, __STDC_INT_AS_UINT_T name) THROWS(...);
/* >> sysconf(2)
 * @param: name: One of `_SC_*' from <asm/crt/confname.h>
 * Return   a   system    configuration   value    `name'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] `name'  refers to a maximum or minimum
 *                                 limit, and that limit is indeterminate
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
INTDEF WUNUSED longptr_t (LIBCCALL libc_SysConf)(__STDC_INT_AS_UINT_T name) THROWS(...);
/* >> close_range(2)
 * Close all files handles `>= minfd && <= maxfd' (but see `flags')
 * @param: flags: Set of `0 | CLOSE_RANGE_UNSHARE | CLOSE_RANGE_CLOEXEC'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF void (LIBCCALL libc_CloseRange)(unsigned int minfd, unsigned int maxfd, unsigned int flags) THROWS(...);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_UNISTD_H */
