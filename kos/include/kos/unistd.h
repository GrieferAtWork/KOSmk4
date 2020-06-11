/* HASH CRC-32:0xed6ad756 */
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
#ifndef _KOS_UNISTD_H
#define _KOS_UNISTD_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <unistd.h>

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __pos_t_defined
#define __pos_t_defined 1
typedef __FS_TYPE(pos) pos_t; /* File/device position */
#endif /* !__pos_t_defined */

#ifdef __USE_LARGEFILE64
#ifndef __pos64_t_defined
#define __pos64_t_defined 1
typedef __pos64_t pos64_t; /* File/device position */
#endif /* !__pos64_t_defined */
#endif /* __USE_LARGEFILE64 */

#ifdef __CRT_HAVE_Execv
/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CDECLARE_VOID(__ATTR_NORETURN __ATTR_NONNULL((1, 2)),__THROWING,Execv,(char const *__restrict __path, __TARGV),(__path,___argv))
#endif /* __CRT_HAVE_Execv */
#ifdef __CRT_HAVE_Execve
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CDECLARE_VOID(__ATTR_NORETURN __ATTR_NONNULL((1, 2, 3)),__THROWING,Execve,(char const *__restrict __path, __TARGV, __TENVP),(__path,___argv,___envp))
#endif /* __CRT_HAVE_Execve */
#ifdef __CRT_HAVE_Execvp
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CDECLARE_VOID(__ATTR_NORETURN __ATTR_NONNULL((1, 2)),__THROWING,Execvp,(char const *__restrict __file, __TARGV),(__file,___argv))
#endif /* __CRT_HAVE_Execvp */
#ifdef __CRT_HAVE_Execl
/* >> execl(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
__LIBC __ATTR_NORETURN __ATTR_SENTINEL __ATTR_NONNULL((1)) void (__VLIBCCALL Execl)(char const *__restrict __path, char const *__args, ...) __THROWS(...) __CASMNAME_SAME("Execl");
#elif defined(__CRT_HAVE_Execv)
#include <local/kos.unistd/Execl.h>
/* >> execl(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(Execl)
#else /* __cplusplus */
#define Execl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Execl))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE_Execle
/* >> execle(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
__LIBC __ATTR_NORETURN __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) void (__VLIBCCALL Execle)(char const *__restrict __path, char const *__args, ...) __THROWS(...) __CASMNAME_SAME("Execle");
#elif defined(__CRT_HAVE_Execve)
#include <local/kos.unistd/Execle.h>
/* >> execle(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(Execle)
#else /* __cplusplus */
#define Execle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Execle))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE_Execpl
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
__LIBC __ATTR_NORETURN __ATTR_SENTINEL __ATTR_NONNULL((1)) void (__VLIBCCALL Execpl)(char const *__restrict __file, char const *__args, ...) __THROWS(...) __CASMNAME_SAME("Execpl");
#elif defined(__CRT_HAVE_Execvp)
#include <local/kos.unistd/Execpl.h>
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(Execpl)
#else /* __cplusplus */
#define Execpl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Execpl))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE_Execlpe
/* >> execle(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
__LIBC __ATTR_NORETURN __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) void (__VLIBCCALL Execlpe)(char const *__restrict __file, char const *__args, ...) __THROWS(...) __CASMNAME_SAME("Execlpe");
#elif defined(__CRT_HAVE_Execvpe)
#include <local/kos.unistd/Execlpe.h>
/* >> execle(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(Execlpe)
#else /* __cplusplus */
#define Execlpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Execlpe))
#endif /* !__cplusplus */
#endif /* ... */

#ifdef __CRT_HAVE_Pipe
/* >> pipe(2)
 * Create a new pair of connected pipes ([0] = reader, [1] = writer) */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__THROWING,Pipe,(__fd_t __pipedes[2]),(__pipedes))
#endif /* __CRT_HAVE_Pipe */

#ifdef __CRT_HAVE_FSync
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning that changes to its data and/or descriptor are written to disk */
__CDECLARE_VOID(,__THROWING,FSync,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE_FDataSync)
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning that changes to its data and/or descriptor are written to disk */
__CREDIRECT_VOID(,__THROWING,FSync,(__fd_t __fd),FDataSync,(__fd))
#else /* ... */
#include <local/kos.unistd/FSync.h>
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning that changes to its data and/or descriptor are written to disk */
__NAMESPACE_LOCAL_USING_OR_IMPL(FSync, __FORCELOCAL void (__LIBCCALL FSync)(__fd_t __fd) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(FSync))(__fd); })
#endif /* !... */

#ifdef __CRT_HAVE_SetPGid
/* >> setpgid(2)
 * Change the ID of the process group associated with `PID's process.
 * (That is the TID of the leader of the process group of `PID's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER = THREAD[PGID]
 * When `PID' is ZERO(0), use `gettid()' for it instead.
 * When `PGID' is ZERO(0), use `PID' (after it was substituted) for instead */
__CDECLARE_VOID(,__THROWING,SetPGid,(__pid_t __pid, __pid_t __pgid),(__pid,__pgid))
#endif /* __CRT_HAVE_SetPGid */

#ifdef __CRT_HAVE_SetSid
/* >> setsid(2)
 * Make the calling thread's process the leader of its associated
 * process group, before also making it its own session leader.
 * Then return the TID of that new session leader, which is also the PID of the calling process.
 *  - THIS_THREAD->LEADER->GROUP_LEADER                 = THIS_THREAD->LEADER;
 *  - THIS_THREAD->LEADER->GROUP_LEADER->SESSION_LEADER = THIS_THREAD->LEADER->GROUP_LEADER;
 *  - return THIS_THREAD->LEADER->PID; */
__CDECLARE(,__pid_t,__THROWING,SetSid,(void),())
#endif /* __CRT_HAVE_SetSid */

#ifdef __CRT_HAVE_SetUid
/* >> setuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `UID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
__CDECLARE_VOID(,__THROWING,SetUid,(__uid_t __uid),(__uid))
#endif /* __CRT_HAVE_SetUid */

#ifdef __CRT_HAVE_SetGid
/* >> setgid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `GID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
__CDECLARE_VOID(,__THROWING,SetGid,(__gid_t __gid),(__gid))
#endif /* __CRT_HAVE_SetGid */

#ifdef __CRT_HAVE_Fork
/* >> fork(2)
 * Clone the calling thread into a second process and return twice, once
 * in the parent process where this function returns the (non-zero) PID
 * of the forked child process, and a second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with that of another program that the original
 * parent can then `wait(2)' for */
__CDECLARE(__ATTR_WUNUSED,__pid_t,__THROWING,Fork,(void),())
#endif /* __CRT_HAVE_Fork */

#ifdef __CRT_HAVE_FPathConf
/* >> fpathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `FD'
 * return: * : The configuration limit associated with `NAME' for `FD'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `FD'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
__CDECLARE(__ATTR_WUNUSED,long int,__THROWING,FPathConf,(__fd_t __fd, int __name),(__fd,__name))
#endif /* __CRT_HAVE_FPathConf */

#ifdef __CRT_HAVE_Chown
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__THROWING,Chown,(char const *__file, __uid_t __owner, __gid_t __group),(__file,__owner,__group))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_FChownAt)
#include <local/kos.unistd/Chown.h>
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__NAMESPACE_LOCAL_USING_OR_IMPL(Chown, __FORCELOCAL __ATTR_NONNULL((1)) void (__LIBCCALL Chown)(char const *__file, __uid_t __owner, __gid_t __group) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Chown))(__file, __owner, __group); })
#endif /* ... */

#ifdef __CRT_HAVE_PathConf
/* >> pathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `PATH'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
__CDECLARE(__ATTR_NONNULL((1)),long int,__THROWING,PathConf,(char const *__path, int __name),(__path,__name))
#endif /* __CRT_HAVE_PathConf */

#ifdef __CRT_HAVE_Link
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
__CDECLARE_VOID(__ATTR_NONNULL((1, 2)),__THROWING,Link,(char const *__from, char const *__to),(__from,__to))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_LinkAt)
#include <local/kos.unistd/Link.h>
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
__NAMESPACE_LOCAL_USING_OR_IMPL(Link, __FORCELOCAL __ATTR_NONNULL((1, 2)) void (__LIBCCALL Link)(char const *__from, char const *__to) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Link))(__from, __to); })
#endif /* ... */

#ifdef __CRT_HAVE_Read
/* >> read(2)
 * Read data from a given file descriptor `FD' and return the number of bytes read.
 * A return value of ZERO(0) is indicative of EOF */
__CDECLARE(__ATTR_NONNULL((2)),size_t,__THROWING,Read,(__fd_t __fd, void *__buf, size_t __bufsize),(__fd,__buf,__bufsize))
#endif /* __CRT_HAVE_Read */

#ifdef __CRT_HAVE_Write
/* >> write(2)
 * Write data to a given file descriptor `FD' and return the number of bytes written */
__CDECLARE(__ATTR_NONNULL((2)),size_t,__THROWING,Write,(__fd_t __fd, void const *__buf, size_t __bufsize),(__fd,__buf,__bufsize))
#endif /* __CRT_HAVE_Write */

#ifdef __USE_KOS
#ifdef __CRT_HAVE_ReadAll
/* >> readall(3)
 * Same as `read(2)', however keep on reading until `read()' indicates EOF (causing
 * `readall()' to immediately return `0') or the entirety of the given buffer has been
 * filled (in which case `bufsize' is returned).
 * If an error occurrs before all data could be read, try to use SEEK_CUR to rewind
 * the file descriptor by the amount of data that had already been loaded. - Errors
 * during this phase are silently ignored and don't cause `errno' to change */
__CDECLARE(__ATTR_NONNULL((2)),size_t,__THROWING,ReadAll,(__fd_t __fd, void *__buf, size_t __bufsize),(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE_Read) && (defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64))
#include <local/kos.unistd/ReadAll.h>
/* >> readall(3)
 * Same as `read(2)', however keep on reading until `read()' indicates EOF (causing
 * `readall()' to immediately return `0') or the entirety of the given buffer has been
 * filled (in which case `bufsize' is returned).
 * If an error occurrs before all data could be read, try to use SEEK_CUR to rewind
 * the file descriptor by the amount of data that had already been loaded. - Errors
 * during this phase are silently ignored and don't cause `errno' to change */
__NAMESPACE_LOCAL_USING_OR_IMPL(ReadAll, __FORCELOCAL __ATTR_NONNULL((2)) size_t (__LIBCCALL ReadAll)(__fd_t __fd, void *__buf, size_t __bufsize) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ReadAll))(__fd, __buf, __bufsize); })
#endif /* ... */
#endif /* __USE_KOS */

#if defined(__CRT_HAVE_LSeek64) && defined(__USE_FILE_OFFSET64)
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__FS_TYPE(pos),__THROWING,LSeek,(__fd_t __fd, __FS_TYPE(off) __offset, int __whence),LSeek64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_LSeek) && !defined(__USE_FILE_OFFSET64)
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CDECLARE(,__FS_TYPE(pos),__THROWING,LSeek,(__fd_t __fd, __FS_TYPE(off) __offset, int __whence),(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_LSeek) || defined(__CRT_HAVE_LSeek64)
#include <local/kos.unistd/LSeek.h>
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__NAMESPACE_LOCAL_USING_OR_IMPL(LSeek, __FORCELOCAL __FS_TYPE(pos) (__LIBCCALL LSeek)(__fd_t __fd, __FS_TYPE(off) __offset, int __whence) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(LSeek))(__fd, __offset, __whence); })
#endif /* ... */

#ifdef __CRT_HAVE_Dup2
/* >> dup2(2)
 * @return: NEWFD: Returns the new handle upon success.
 * Duplicate a file referred to by `OLDFD' into `NEWFD' */
__CDECLARE(,__fd_t,__THROWING,Dup2,(__fd_t __oldfd, __fd_t __newfd),(__oldfd,__newfd))
#endif /* __CRT_HAVE_Dup2 */

#ifdef __CRT_HAVE_Dup
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `FD' and return its duplicated handle number */
__CDECLARE(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,Dup,(__fd_t __fd),(__fd))
#endif /* __CRT_HAVE_Dup */

#ifdef __CRT_HAVE_Chdir
/* >> chdir(2)
 * Change the current working directory to `PATH' */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__THROWING,Chdir,(char const *__path),(__path))
#endif /* __CRT_HAVE_Chdir */

#ifdef __CRT_HAVE_GetCwd
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CDECLARE(,char *,__THROWING,GetCwd,(char *__buf, size_t __bufsize),(__buf,__bufsize))
#endif /* __CRT_HAVE_GetCwd */

#ifdef __CRT_HAVE_Unlink
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__THROWING,Unlink,(char const *__file),(__file))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_UnlinkAt)
#include <local/kos.unistd/Unlink.h>
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(Unlink, __FORCELOCAL __ATTR_NONNULL((1)) void (__LIBCCALL Unlink)(char const *__file) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Unlink))(__file); })
#endif /* ... */

#ifdef __CRT_HAVE_Rmdir
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__THROWING,Rmdir,(char const *__path),(__path))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_UnlinkAt)
#include <local/kos.unistd/Rmdir.h>
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(Rmdir, __FORCELOCAL __ATTR_NONNULL((1)) void (__LIBCCALL Rmdir)(char const *__path) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Rmdir))(__path); })
#endif /* ... */

#ifdef __USE_ATFILE

#ifdef __CRT_HAVE_FChownAt
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
__CDECLARE_VOID(__ATTR_NONNULL((2)),__THROWING,FChownAt,(__fd_t __dfd, char const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),(__dfd,__file,__owner,__group,__flags))
#endif /* __CRT_HAVE_FChownAt */

#ifdef __CRT_HAVE_LinkAt
/* >> linkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
__CDECLARE_VOID(__ATTR_NONNULL((2, 4)),__THROWING,LinkAt,(__fd_t __fromfd, char const *__from, __fd_t __tofd, char const *__to, __atflag_t __flags),(__fromfd,__from,__tofd,__to,__flags))
#endif /* __CRT_HAVE_LinkAt */

#ifdef __CRT_HAVE_SymlinkAt
/* >> symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
__CDECLARE_VOID(__ATTR_NONNULL((1, 3)),__THROWING,SymlinkAt,(char const *__link_text, __fd_t __tofd, char const *__target_path),(__link_text,__tofd,__target_path))
#endif /* __CRT_HAVE_SymlinkAt */

#ifdef __CRT_HAVE_ReadlinkAt
/* >> readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__CDECLARE(__ATTR_NONNULL((2, 3)),size_t,__THROWING,ReadlinkAt,(__fd_t __dfd, char const *__restrict __path, char *__restrict __buf, size_t __buflen),(__dfd,__path,__buf,__buflen))
#endif /* __CRT_HAVE_ReadlinkAt */

#ifdef __USE_KOS
#ifdef __CRT_HAVE_FReadlinkAt
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
__CDECLARE(__ATTR_NONNULL((2, 3)),size_t,__THROWING,FReadlinkAt,(__fd_t __dfd, char const *__restrict __path, char *__restrict __buf, size_t __buflen, __atflag_t __flags),(__dfd,__path,__buf,__buflen,__flags))
#endif /* __CRT_HAVE_FReadlinkAt */
#endif /* __USE_KOS */

#ifdef __CRT_HAVE_UnlinkAt
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
__CDECLARE_VOID(__ATTR_NONNULL((2)),__THROWING,UnlinkAt,(__fd_t __dfd, char const *__name, __atflag_t __flags),(__dfd,__name,__flags))
#endif /* __CRT_HAVE_UnlinkAt */
#endif /* __USE_ATFILE */


#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_LSeek64
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CDECLARE(,__pos64_t,__THROWING,LSeek64,(__fd_t __fd, __off64_t __offset, int __whence),(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_LSeek) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__pos64_t,__THROWING,LSeek64,(__fd_t __fd, __off64_t __offset, int __whence),LSeek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_LSeek)
#include <local/kos.unistd/LSeek64.h>
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__NAMESPACE_LOCAL_USING_OR_IMPL(LSeek64, __FORCELOCAL __pos64_t (__LIBCCALL LSeek64)(__fd_t __fd, __off64_t __offset, int __whence) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(LSeek64))(__fd, __offset, __whence); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */


#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)

#if defined(__CRT_HAVE_PRead64) && defined(__USE_FILE_OFFSET64)
/* >> pread(2)
 * Read data from a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),size_t,__THROWING,PRead,(__fd_t __fd, void *__buf, size_t __bufsize, pos_t __offset),PRead64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PRead) && !defined(__USE_FILE_OFFSET64)
/* >> pread(2)
 * Read data from a file at a specific offset */
__CDECLARE(__ATTR_NONNULL((2)),size_t,__THROWING,PRead,(__fd_t __fd, void *__buf, size_t __bufsize, pos_t __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PRead) || defined(__CRT_HAVE_PRead64)
#include <local/kos.unistd/PRead.h>
/* >> pread(2)
 * Read data from a file at a specific offset */
__NAMESPACE_LOCAL_USING_OR_IMPL(PRead, __FORCELOCAL __ATTR_NONNULL((2)) size_t (__LIBCCALL PRead)(__fd_t __fd, void *__buf, size_t __bufsize, pos_t __offset) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(PRead))(__fd, __buf, __bufsize, __offset); })
#endif /* ... */
#if defined(__CRT_HAVE_PWrite64) && defined(__USE_FILE_OFFSET64)
/* >> pwrite(2)
 * Write data to a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),size_t,__THROWING,PWrite,(__fd_t __fd, void const *__buf, size_t __bufsize, pos_t __offset),PWrite64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PWrite) && !defined(__USE_FILE_OFFSET64)
/* >> pwrite(2)
 * Write data to a file at a specific offset */
__CDECLARE(__ATTR_NONNULL((2)),size_t,__THROWING,PWrite,(__fd_t __fd, void const *__buf, size_t __bufsize, pos_t __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PWrite) || defined(__CRT_HAVE_PWrite64)
#include <local/kos.unistd/PWrite.h>
/* >> pwrite(2)
 * Write data to a file at a specific offset */
__NAMESPACE_LOCAL_USING_OR_IMPL(PWrite, __FORCELOCAL __ATTR_NONNULL((2)) size_t (__LIBCCALL PWrite)(__fd_t __fd, void const *__buf, size_t __bufsize, pos_t __offset) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(PWrite))(__fd, __buf, __bufsize, __offset); })
#endif /* ... */

#ifdef __USE_KOS
#if defined(__CRT_HAVE_PReadAll64) && defined(__USE_FILE_OFFSET64)
/* >> preadall(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
__CREDIRECT(__ATTR_NONNULL((2)),size_t,__THROWING,PReadAll,(__fd_t __fd, void *__buf, size_t __bufsize, pos_t __offset),PReadAll64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PReadAll) && !defined(__USE_FILE_OFFSET64)
/* >> preadall(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
__CDECLARE(__ATTR_NONNULL((2)),size_t,__THROWING,PReadAll,(__fd_t __fd, void *__buf, size_t __bufsize, pos_t __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PReadAll) || defined(__CRT_HAVE_PReadAll64) || defined(__CRT_HAVE_PRead64) || defined(__CRT_HAVE_PRead)
#include <local/kos.unistd/PReadAll.h>
/* >> preadall(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(PReadAll, __FORCELOCAL __ATTR_NONNULL((2)) size_t (__LIBCCALL PReadAll)(__fd_t __fd, void *__buf, size_t __bufsize, pos_t __offset) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(PReadAll))(__fd, __buf, __bufsize, __offset); })
#endif /* ... */
#endif /* __USE_KOS */

#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_PRead64
/* >> pread64(2)
 * Read data from a file at a specific offset */
__CDECLARE(__ATTR_NONNULL((2)),size_t,__THROWING,PRead64,(__fd_t __fd, void *__buf, size_t __bufsize, pos64_t __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PRead) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> pread64(2)
 * Read data from a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),size_t,__THROWING,PRead64,(__fd_t __fd, void *__buf, size_t __bufsize, pos64_t __offset),PRead,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PRead)
#include <local/kos.unistd/PRead64.h>
/* >> pread64(2)
 * Read data from a file at a specific offset */
__NAMESPACE_LOCAL_USING_OR_IMPL(PRead64, __FORCELOCAL __ATTR_NONNULL((2)) size_t (__LIBCCALL PRead64)(__fd_t __fd, void *__buf, size_t __bufsize, pos64_t __offset) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(PRead64))(__fd, __buf, __bufsize, __offset); })
#endif /* ... */
#ifdef __CRT_HAVE_PWrite64
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
__CDECLARE(__ATTR_NONNULL((2)),size_t,__THROWING,PWrite64,(__fd_t __fd, void *__buf, size_t __bufsize, pos64_t __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PWrite) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),size_t,__THROWING,PWrite64,(__fd_t __fd, void *__buf, size_t __bufsize, pos64_t __offset),PWrite,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PWrite)
#include <local/kos.unistd/PWrite64.h>
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
__NAMESPACE_LOCAL_USING_OR_IMPL(PWrite64, __FORCELOCAL __ATTR_NONNULL((2)) size_t (__LIBCCALL PWrite64)(__fd_t __fd, void *__buf, size_t __bufsize, pos64_t __offset) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(PWrite64))(__fd, __buf, __bufsize, __offset); })
#endif /* ... */

#ifdef __USE_KOS
#ifdef __CRT_HAVE_PReadAll64
/* >> preadall64(3)
 * Same as `readall(3)', but using `pread64(2)' instead of `read()' */
__CDECLARE(__ATTR_NONNULL((2)),size_t,__THROWING,PReadAll64,(__fd_t __fd, void *__buf, size_t __bufsize, pos64_t __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PReadAll) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> preadall64(3)
 * Same as `readall(3)', but using `pread64(2)' instead of `read()' */
__CREDIRECT(__ATTR_NONNULL((2)),size_t,__THROWING,PReadAll64,(__fd_t __fd, void *__buf, size_t __bufsize, pos64_t __offset),PReadAll,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PRead64) || defined(__CRT_HAVE_PRead)
#include <local/kos.unistd/PReadAll64.h>
/* >> preadall64(3)
 * Same as `readall(3)', but using `pread64(2)' instead of `read()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(PReadAll64, __FORCELOCAL __ATTR_NONNULL((2)) size_t (__LIBCCALL PReadAll64)(__fd_t __fd, void *__buf, size_t __bufsize, pos64_t __offset) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(PReadAll64))(__fd, __buf, __bufsize, __offset); })
#endif /* ... */
#endif /* __USE_KOS */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */


#ifdef __USE_GNU
#ifdef __CRT_HAVE_Pipe2
__CDECLARE_VOID(__ATTR_NONNULL((1)),__THROWING,Pipe2,(__fd_t __pipedes[2], __oflag_t __flags),(__pipedes,__flags))
#endif /* __CRT_HAVE_Pipe2 */
#ifdef __CRT_HAVE_Dup3
__CDECLARE(,__fd_t,__THROWING,Dup3,(__fd_t __oldfd, __fd_t __newfd, __oflag_t __flags),(__oldfd,__newfd,__flags))
#endif /* __CRT_HAVE_Dup3 */
#ifdef __CRT_HAVE_GetCurrentDirName
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED,char *,__THROWING,GetCurrentDirName,(void),())
#elif defined(__CRT_HAVE_GetCwd)
#include <local/kos.unistd/GetCurrentDirName.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(GetCurrentDirName, __FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED char *(__LIBCCALL GetCurrentDirName)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(GetCurrentDirName))(); })
#endif /* ... */
#ifdef __CRT_HAVE_SyncFs
__CDECLARE_VOID(,__THROWING,SyncFs,(__fd_t __fd),(__fd))
#else /* __CRT_HAVE_SyncFs */
#include <local/kos.unistd/SyncFs.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(SyncFs, __FORCELOCAL void (__LIBCCALL SyncFs)(__fd_t __fd) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(SyncFs))(__fd); })
#endif /* !__CRT_HAVE_SyncFs */
#ifdef __CRT_HAVE_GetResUid
__CDECLARE_VOID(,__NOTHROW_NCX,GetResUid,(__uid_t *__ruid, __uid_t *__euid, __uid_t *__suid),(__ruid,__euid,__suid))
#endif /* __CRT_HAVE_GetResUid */
#ifdef __CRT_HAVE_GetResGid
__CDECLARE_VOID(,__NOTHROW_NCX,GetResGid,(__gid_t *__rgid, __gid_t *__egid, __gid_t *__sgid),(__rgid,__egid,__sgid))
#endif /* __CRT_HAVE_GetResGid */
#ifdef __CRT_HAVE_SetResUid
__CDECLARE_VOID(,__NOTHROW_NCX,SetResUid,(__uid_t __ruid, __uid_t __euid, __uid_t __suid),(__ruid,__euid,__suid))
#endif /* __CRT_HAVE_SetResUid */
#ifdef __CRT_HAVE_SetResGid
__CDECLARE_VOID(,__NOTHROW_NCX,SetResGid,(__gid_t __rgid, __gid_t __egid, __gid_t __sgid),(__rgid,__egid,__sgid))
#endif /* __CRT_HAVE_SetResGid */
#endif /* __USE_GNU */
#if (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8)) || \
     defined(__USE_MISC)
#ifdef __CRT_HAVE_VFork
/* >> vfork(2)
 * Same as `fork(2)', but possibly suspend the calling process until the
 * child process either calls `exit(2)' or one of the many `exec(2)' functions */
__CDECLARE(__ATTR_RETURNS_TWICE __ATTR_WUNUSED,__pid_t,__THROWING,VFork,(void),())
#endif /* __CRT_HAVE_VFork */
#endif

#ifdef __CRT_HAVE_FChown
/* >> fchown(2)
 * Change the ownership of a given `FD' to `GROUP:OWNER' */
__CDECLARE_VOID(,__THROWING,FChown,(__fd_t __fd, __uid_t __owner, __gid_t __group),(__fd,__owner,__group))
#endif /* __CRT_HAVE_FChown */

#ifdef __CRT_HAVE_FChdir
/* >> chdir(2)
 * Change the current working directory to `PATH' */
__CDECLARE_VOID(,__THROWING,FChdir,(__fd_t __fd),(__fd))
#endif /* __CRT_HAVE_FChdir */

#ifdef __CRT_HAVE_GetPGid
/* >> getpgid(2)
 * Return the ID of the process group associated with `PID's process.
 * (That is the TID of the leader of the process group of `PID's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER->PID
 * When `PID' is ZERO(0), use `gettid()' for it instead */
__CDECLARE(__ATTR_WUNUSED,__pid_t,__THROWING,GetPGid,(__pid_t __pid),(__pid))
#endif /* __CRT_HAVE_GetPGid */

#ifdef __CRT_HAVE_GetSid
/* >> getsid(2)
 * Return the ID of the session which a process `PID' is apart of.
 * return THREAD[PID]->LEADER->GROUP_LEADER->SESSION_LEADER->PID; */
__CDECLARE(__ATTR_WUNUSED,__pid_t,__THROWING,GetSid,(__pid_t __pid),(__pid))
#endif /* __CRT_HAVE_GetSid */

#ifdef __CRT_HAVE_LChown
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__THROWING,LChown,(char const *__file, __uid_t __owner, __gid_t __group),(__file,__owner,__group))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_FChownAt)
#include <local/kos.unistd/LChown.h>
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__NAMESPACE_LOCAL_USING_OR_IMPL(LChown, __FORCELOCAL __ATTR_NONNULL((1)) void (__LIBCCALL LChown)(char const *__file, __uid_t __owner, __gid_t __group) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(LChown))(__file, __owner, __group); })
#endif /* ... */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)

#if defined(__CRT_HAVE_Truncate64) && defined(__USE_FILE_OFFSET64)
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__THROWING,Truncate,(char const *__file, pos_t __length),Truncate64,(__file,__length))
#elif defined(__CRT_HAVE_Truncate) && !defined(__USE_FILE_OFFSET64)
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__THROWING,Truncate,(char const *__file, pos_t __length),(__file,__length))
#elif defined(__CRT_HAVE_Truncate) || defined(__CRT_HAVE_Truncate64)
#include <local/kos.unistd/Truncate.h>
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(Truncate, __FORCELOCAL __ATTR_NONNULL((1)) void (__LIBCCALL Truncate)(char const *__file, pos_t __length) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Truncate))(__file, __length); })
#endif /* ... */

#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_Truncate64
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__THROWING,Truncate64,(char const *__file, pos64_t __length),(__file,__length))
#elif defined(__CRT_HAVE_Truncate) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__THROWING,Truncate64,(char const *__file, pos64_t __length),Truncate,(__file,__length))
#elif defined(__CRT_HAVE_Truncate)
#include <local/kos.unistd/Truncate64.h>
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(Truncate64, __FORCELOCAL __ATTR_NONNULL((1)) void (__LIBCCALL Truncate64)(char const *__file, pos64_t __length) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Truncate64))(__file, __length); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

#ifdef __USE_XOPEN2K8

#ifndef __FExecve_defined
#define __FExecve_defined 1
#ifdef __CRT_HAVE_FExecve
/* >> fexecve(2)
 * Replace the calling process with the application image referred to by `FD' and
 * execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CDECLARE_VOID(__ATTR_NORETURN __ATTR_NONNULL((2, 3)),__THROWING,FExecve,(__fd_t __fd, __TARGV, __TENVP),(__fd,___argv,___envp))
#else /* __CRT_HAVE_FExecve */
#undef __FExecve_defined
#endif /* !__CRT_HAVE_FExecve */
#endif /* !__FExecve_defined */
#endif /* __USE_XOPEN2K8 */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_Execvpe
/* >> execvpe(3)
 * Replace the calling process with the application image referred to by `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CDECLARE_VOID(__ATTR_NORETURN __ATTR_NONNULL((1, 2, 3)),__THROWING,Execvpe,(char const *__restrict __file, __TARGV, __TENVP),(__fd,___argv,___envp))
#endif /* __CRT_HAVE_Execvpe */
#endif /* __USE_GNU */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifdef __CRT_HAVE_Nice
__CDECLARE(,int,__THROWING,Nice,(int __inc),(__inc))
#else /* __CRT_HAVE_Nice */
#include <local/kos.unistd/Nice.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(Nice, __FORCELOCAL int (__LIBCCALL Nice)(int __inc) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Nice))(__inc); })
#endif /* !__CRT_HAVE_Nice */
#endif /* __USE_MISC || __USE_XOPEN */

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
#ifdef __CRT_HAVE_SetPGrp
/* >> setpgrp(3)
 * Move the calling process into its own process group.
 * Equivalent to `setpgid(0, 0)' */
__CDECLARE_VOID(,__THROWING,SetPGrp,(void),())
#endif /* __CRT_HAVE_SetPGrp */
#ifdef __CRT_HAVE_SetReUid
__CDECLARE_VOID(,__THROWING,SetReUid,(__uid_t __ruid, __uid_t __euid),(__ruid,__euid))
#endif /* __CRT_HAVE_SetReUid */
#ifdef __CRT_HAVE_SetReGid
__CDECLARE_VOID(,__THROWING,SetReGid,(__gid_t __rgid, __gid_t __egid),(__rgid,__egid))
#endif /* __CRT_HAVE_SetReGid */
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

#ifdef __USE_XOPEN2K
#ifdef __CRT_HAVE_SetEUid
/* >> seteuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `EUID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
__CDECLARE_VOID(,__THROWING,SetEUid,(__uid_t __euid),(__euid))
#endif /* __CRT_HAVE_SetEUid */
#ifdef __CRT_HAVE_SetEGid
/* >> setegid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `EGID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
__CDECLARE_VOID(,__THROWING,SetEGid,(__gid_t __egid),(__egid))
#endif /* __CRT_HAVE_SetEGid */
#endif /* __USE_XOPEN2K */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
#ifdef __CRT_HAVE_Symlink
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__CDECLARE_VOID(__ATTR_NONNULL((1, 2)),__THROWING,Symlink,(char const *__link_text, char const *__target_path),(__link_text,__target_path))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_SymlinkAt)
#include <local/kos.unistd/Symlink.h>
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(Symlink, __FORCELOCAL __ATTR_NONNULL((1, 2)) void (__LIBCCALL Symlink)(char const *__link_text, char const *__target_path) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Symlink))(__link_text, __target_path); })
#endif /* ... */

#ifdef __CRT_HAVE_Readlink
/* >> readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__CDECLARE(__ATTR_NONNULL((1, 2)),size_t,__THROWING,Readlink,(char const *__restrict __path, char *__restrict __buf, size_t __buflen),(__path,__buf,__buflen))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_ReadlinkAt)
#include <local/kos.unistd/Readlink.h>
/* >> readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(Readlink, __FORCELOCAL __ATTR_NONNULL((1, 2)) size_t (__LIBCCALL Readlink)(char const *__restrict __path, char *__restrict __buf, size_t __buflen) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Readlink))(__path, __buf, __buflen); })
#endif /* ... */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
#ifdef __CRT_HAVE_GetHostName
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__THROWING,GetHostName,(char *__name, size_t __buflen),(__name,__buflen))
#endif /* __CRT_HAVE_GetHostName */
#endif /* __USE_UNIX98 || __USE_XOPEN2K */

#ifdef __USE_MISC

#ifdef __CRT_HAVE_SetHostName
/* >> sethostname(2)
 * Set the name of the hosting machine */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__THROWING,SetHostName,(char const *__name, size_t __len),(__name,__len))
#endif /* __CRT_HAVE_SetHostName */

#ifdef __CRT_HAVE_GetDomainName
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__THROWING,GetDomainName,(char *__name, size_t __buflen),(__name,__buflen))
#endif /* __CRT_HAVE_GetDomainName */

#ifdef __CRT_HAVE_SetDomainName
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__THROWING,SetDomainName,(char const *__name, size_t __len),(__name,__len))
#endif /* __CRT_HAVE_SetDomainName */
#ifdef __CRT_HAVE_Syscall
__LIBC __syscall_slong_t (__VLIBCCALL Syscall)(__syscall_ulong_t __sysno, ...) __THROWS(...) __CASMNAME_SAME("Syscall");
#endif /* __CRT_HAVE_Syscall */
#ifdef __USE_KOS
#ifdef __CRT_HAVE_Syscall
__LIBC __LONG64_TYPE__ (__VLIBCCALL Syscall64)(__syscall_ulong_t __sysno, ...) __THROWS(...) __CASMNAME("Syscall");
#elif defined(__CRT_HAVE_Syscall64)
__LIBC __LONG64_TYPE__ (__VLIBCCALL Syscall64)(__syscall_ulong_t __sysno, ...) __THROWS(...) __CASMNAME_SAME("Syscall64");
#endif /* ... */
#endif /* __USE_KOS */
#endif /* __USE_MISC */

#if defined(__USE_MISC) || \
   (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
#ifdef __CRT_HAVE_ChRoot
/* >> chroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__THROWING,ChRoot,(char const *__restrict __path),(__path))
#endif /* __CRT_HAVE_ChRoot */
#endif /* ... */

#if defined(__USE_POSIX199309) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
#if defined(__CRT_HAVE_FTruncate64) && defined(__USE_FILE_OFFSET64)
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT_VOID(,__THROWING,FTruncate,(__fd_t __fd, pos_t __length),FTruncate64,(__fd,__length))
#elif defined(__CRT_HAVE_FTruncate) && !defined(__USE_FILE_OFFSET64)
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CDECLARE_VOID(,__THROWING,FTruncate,(__fd_t __fd, pos_t __length),(__fd,__length))
#elif defined(__CRT_HAVE_FTruncate) || defined(__CRT_HAVE_FTruncate64)
#include <local/kos.unistd/FTruncate.h>
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(FTruncate, __FORCELOCAL void (__LIBCCALL FTruncate)(__fd_t __fd, pos_t __length) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(FTruncate))(__fd, __length); })
#endif /* ... */

#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_FTruncate64
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CDECLARE_VOID(,__THROWING,FTruncate64,(__fd_t __fd, pos64_t __length),(__fd,__length))
#elif defined(__CRT_HAVE_FTruncate) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT_VOID(,__THROWING,FTruncate64,(__fd_t __fd, pos64_t __length),FTruncate,(__fd,__length))
#elif defined(__CRT_HAVE_FTruncate)
#include <local/kos.unistd/FTruncate64.h>
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(FTruncate64, __FORCELOCAL void (__LIBCCALL FTruncate64)(__fd_t __fd, pos64_t __length) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(FTruncate64))(__fd, __length); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_POSIX199309 || __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

#if defined(__USE_POSIX199309) || defined(__USE_UNIX98)
#ifdef __CRT_HAVE_FDataSync
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps, and its size), meaning that changes are written to disk */
__CDECLARE_VOID(,__THROWING,FDataSync,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE_FSync)
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps, and its size), meaning that changes are written to disk */
__CREDIRECT_VOID(,__THROWING,FDataSync,(__fd_t __fd),FSync,(__fd))
#else /* ... */
#include <local/kos.unistd/FDataSync.h>
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps, and its size), meaning that changes are written to disk */
__NAMESPACE_LOCAL_USING_OR_IMPL(FDataSync, __FORCELOCAL void (__LIBCCALL FDataSync)(__fd_t __fd) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(FDataSync))(__fd); })
#endif /* !... */
#endif /* __USE_POSIX199309 || __USE_UNIX98 */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_KOS_UNISTD_H */
