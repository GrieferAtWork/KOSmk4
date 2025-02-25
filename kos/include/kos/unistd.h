/* HASH CRC-32:0x8b292f28 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
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

#include <kos/anno.h>

#include <unistd.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __pos_t_defined
#define __pos_t_defined
typedef __pos_t pos_t; /* File/device position */
#endif /* !__pos_t_defined */

#ifdef __USE_LARGEFILE64
#ifndef __pos64_t_defined
#define __pos64_t_defined
typedef __pos64_t pos64_t; /* File/device position */
#endif /* !__pos64_t_defined */
#endif /* __USE_LARGEFILE64 */

/* >> execv(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CDECLARE_VOID_OPT(__ATTR_NORETURN __ATTR_IN(1) __ATTR_IN(2),__THROWING(...),Execv,(char const *__restrict __path, __TARGV),(__path,___argv))
/* >> execve(2)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CDECLARE_VOID_OPT(__ATTR_NORETURN __ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),__THROWING(...),Execve,(char const *__restrict __path, __TARGV, __TENVP),(__path,___argv,___envp))
/* >> execvp(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CDECLARE_VOID_OPT(__ATTR_NORETURN __ATTR_IN(1) __ATTR_IN(2),__THROWING(...),Execvp,(char const *__restrict __file, __TARGV),(__file,___argv))
#ifdef __CRT_HAVE_Execl
/* >> execl(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
__LIBC __ATTR_NORETURN __ATTR_SENTINEL __ATTR_IN(1) __ATTR_IN_OPT(2) void (__VLIBCCALL Execl)(char const *__restrict __path, char const *__args, ...) __THROWS(...) __CASMNAME_SAME("Execl");
#elif defined(__CRT_HAVE_Execv)
#include <libc/local/kos.unistd/Execl.h>
/* >> execl(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(Execl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NORETURN __ATTR_SENTINEL __ATTR_IN(1) __ATTR_IN_OPT(2) void (__VLIBCCALL Execl)(char const *__restrict __path, char const *__args, ...) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Execl))(__path, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define Execl(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Execl))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE_Execle
/* >> execle(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
__LIBC __ATTR_NORETURN __ATTR_IN(1) __ATTR_IN_OPT(2) __ATTR_SENTINEL_O(1) void (__VLIBCCALL Execle)(char const *__restrict __path, char const *__args, ...) __THROWS(...) __CASMNAME_SAME("Execle");
#elif defined(__CRT_HAVE_Execve)
#include <libc/local/kos.unistd/Execle.h>
/* >> execle(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(Execle, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NORETURN __ATTR_IN(1) __ATTR_IN_OPT(2) __ATTR_SENTINEL_O(1) void (__VLIBCCALL Execle)(char const *__restrict __path, char const *__args, ...) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Execle))(__path, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define Execle(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Execle))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE_Execpl
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
__LIBC __ATTR_NORETURN __ATTR_SENTINEL __ATTR_IN(1) __ATTR_IN_OPT(2) void (__VLIBCCALL Execpl)(char const *__restrict __file, char const *__args, ...) __THROWS(...) __CASMNAME_SAME("Execpl");
#elif defined(__CRT_HAVE_Execvp)
#include <libc/local/kos.unistd/Execpl.h>
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(Execpl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NORETURN __ATTR_SENTINEL __ATTR_IN(1) __ATTR_IN_OPT(2) void (__VLIBCCALL Execpl)(char const *__restrict __file, char const *__args, ...) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Execpl))(__file, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define Execpl(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Execpl))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE_Execlpe
/* >> execle(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
__LIBC __ATTR_NORETURN __ATTR_IN(1) __ATTR_IN_OPT(2) __ATTR_SENTINEL_O(1) void (__VLIBCCALL Execlpe)(char const *__restrict __file, char const *__args, ...) __THROWS(...) __CASMNAME_SAME("Execlpe");
#elif defined(__CRT_HAVE_Execvpe)
#include <libc/local/kos.unistd/Execlpe.h>
/* >> execle(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(Execlpe, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NORETURN __ATTR_IN(1) __ATTR_IN_OPT(2) __ATTR_SENTINEL_O(1) void (__VLIBCCALL Execlpe)(char const *__restrict __file, char const *__args, ...) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Execlpe))(__file, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define Execlpe(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Execlpe))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
/* >> pipe(2)
 * Create a new pair of connected pipes ([0] = reader, [1] = writer)
 * @param: pipedes: Output for pipe fds: [0]: reader; [1]: writer
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_VOID_OPT(__ATTR_OUT(1),__THROWING(...),Pipe,(__fd_t __pipedes[2]),(__pipedes))
#ifdef __CRT_HAVE_FSync
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
__CDECLARE_VOID(__ATTR_FDWRITE(1),__THROWING(...),FSync,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE_FDataSync)
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
__CREDIRECT_VOID(__ATTR_FDWRITE(1),__THROWING(...),FSync,(__fd_t __fd),FDataSync,(__fd))
#else /* ... */
#include <libc/local/kos.unistd/FSync.h>
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
__NAMESPACE_LOCAL_USING_OR_IMPL(FSync, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDWRITE(1) void (__LIBCCALL FSync)(__fd_t __fd) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(FSync))(__fd); })
#endif /* !... */
/* >> setpgid(2)
 * Change  the ID of  the process group  associated with `pid's process.
 * (That is the TID of the leader of the process group of `pid's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER = THREAD[PGID]
 * When `pid' is ZERO(0), use `gettid()' for it instead.
 * When `pgid' is ZERO(0), use `pid' (after it was substituted) for instead */
__CDECLARE_VOID_OPT(,__THROWING(...),SetPGid,(__pid_t __pid, __pid_t __pgid),(__pid,__pgid))
/* >> setsid(2)
 * Make the calling thread's process the leader of its associated
 * process group, before also making  it its own session  leader.
 * Then return the TID of that new session leader, which is also the PID of the calling process.
 *  - THIS_THREAD->LEADER->GROUP_LEADER                 = THIS_THREAD->LEADER;
 *  - THIS_THREAD->LEADER->GROUP_LEADER->SESSION_LEADER = THIS_THREAD->LEADER->GROUP_LEADER;
 *  - return THIS_THREAD->LEADER->PID; */
__CDECLARE_OPT(,__pid_t,__THROWING(...),SetSid,(void),())
/* >> setuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `uid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
__CDECLARE_VOID_OPT(,__THROWING(...),SetUid,(__uid_t __uid),(__uid))
/* >> setgid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `gid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
__CDECLARE_VOID_OPT(,__THROWING(...),SetGid,(__gid_t __gid),(__gid))
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
__CDECLARE_OPT(__ATTR_WUNUSED,__pid_t,__THROWING(...),Fork,(void),())
/* >> fpathconf(3)
 * @param: name: One   of    `_PC_*'    from    <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `fd'
 * return: * : The configuration limit associated with `name' for `fd'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `fd'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_FDARG(1),__LONGPTR_TYPE__,__THROWING(...),FPathConf,(__fd_t __fd, __STDC_INT_AS_UINT_T __name),(__fd,__name))
#ifdef __CRT_HAVE_TCGetPGrp
/* >> tcgetpgrp(2)
 * Return the foreground process group of a given TTY file descriptor */
__CDECLARE(__ATTR_WUNUSED __ATTR_FDARG(1),__pid_t,__THROWING(...),TCGetPGrp,(__fd_t __fd),(__fd))
#else /* __CRT_HAVE_TCGetPGrp */
#include <asm/os/tty.h>
#if defined(__CRT_HAVE_Ioctl) && defined(__TIOCGPGRP)
#include <libc/local/kos.unistd/TCGetPGrp.h>
/* >> tcgetpgrp(2)
 * Return the foreground process group of a given TTY file descriptor */
__NAMESPACE_LOCAL_USING_OR_IMPL(TCGetPGrp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_FDARG(1) __pid_t (__LIBCCALL TCGetPGrp)(__fd_t __fd) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(TCGetPGrp))(__fd); })
#endif /* __CRT_HAVE_Ioctl && __TIOCGPGRP */
#endif /* !__CRT_HAVE_TCGetPGrp */
#ifdef __CRT_HAVE_TCSetPGrp
/* >> tcsetpgrp(2)
 * Set the foreground process group of a given TTY file descriptor */
__CDECLARE_VOID(__ATTR_FDARG(1),__THROWING(...),TCSetPGrp,(__fd_t __fd, __pid_t __pgrp_id),(__fd,__pgrp_id))
#else /* __CRT_HAVE_TCSetPGrp */
#include <asm/os/tty.h>
#if defined(__CRT_HAVE_Ioctl) && defined(__TIOCSPGRP)
#include <libc/local/kos.unistd/TCSetPGrp.h>
/* >> tcsetpgrp(2)
 * Set the foreground process group of a given TTY file descriptor */
__NAMESPACE_LOCAL_USING_OR_IMPL(TCSetPGrp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) void (__LIBCCALL TCSetPGrp)(__fd_t __fd, __pid_t __pgrp_id) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(TCSetPGrp))(__fd, __pgrp_id); })
#endif /* __CRT_HAVE_Ioctl && __TIOCSPGRP */
#endif /* !__CRT_HAVE_TCSetPGrp */
#ifdef __CRT_HAVE_PathConf
/* >> pathconf(3)
 * @param: name: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `path'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `path'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
__CDECLARE(__ATTR_IN(1),__LONGPTR_TYPE__,__THROWING(...),PathConf,(char const *__path, __STDC_INT_AS_UINT_T __name),(__path,__name))
#else /* __CRT_HAVE_PathConf */
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_FPathConf) && (defined(__CRT_HAVE_Open64) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_OpenAt64) || defined(__CRT_HAVE_OpenAt))) || defined(__CRT_HAVE_Open)) && defined(__O_RDONLY)
#include <libc/local/kos.unistd/PathConf.h>
/* >> pathconf(3)
 * @param: name: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `path'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `path'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
__NAMESPACE_LOCAL_USING_OR_IMPL(PathConf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __LONGPTR_TYPE__ (__LIBCCALL PathConf)(char const *__path, __STDC_INT_AS_UINT_T __name) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(PathConf))(__path, __name); })
#endif /* __CRT_HAVE_FPathConf && (__CRT_HAVE_Open64 || (__AT_FDCWD && (__CRT_HAVE_OpenAt64 || __CRT_HAVE_OpenAt)) || __CRT_HAVE_Open) && __O_RDONLY */
#endif /* !__CRT_HAVE_PathConf */
#ifdef __CRT_HAVE_ChOwn
/* >> chown(2)
 * Change the ownership of a given `file' to `group:owner' */
__CDECLARE_VOID(__ATTR_IN(1),__THROWING(...),ChOwn,(char const *__file, __uid_t __owner, __gid_t __group),(__file,__owner,__group))
#else /* __CRT_HAVE_ChOwn */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_FChOwnAt)
#include <libc/local/kos.unistd/ChOwn.h>
/* >> chown(2)
 * Change the ownership of a given `file' to `group:owner' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ChOwn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) void (__LIBCCALL ChOwn)(char const *__file, __uid_t __owner, __gid_t __group) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ChOwn))(__file, __owner, __group); })
#endif /* __AT_FDCWD && __CRT_HAVE_FChOwnAt */
#endif /* !__CRT_HAVE_ChOwn */
#ifdef __CRT_HAVE_Link
/* >> link(2)
 * Create a hard link from `from', leading to `to' */
__CDECLARE_VOID(__ATTR_IN(1) __ATTR_IN(2),__THROWING(...),Link,(char const *__from, char const *__to),(__from,__to))
#else /* __CRT_HAVE_Link */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_LinkAt)
#include <libc/local/kos.unistd/Link.h>
/* >> link(2)
 * Create a hard link from `from', leading to `to' */
__NAMESPACE_LOCAL_USING_OR_IMPL(Link, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN(2) void (__LIBCCALL Link)(char const *__from, char const *__to) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Link))(__from, __to); })
#endif /* __AT_FDCWD && __CRT_HAVE_LinkAt */
#endif /* !__CRT_HAVE_Link */
/* >> read(2)
 * Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the  `O_NONBLOCK' flag set,  only read as  much data as  was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
__CDECLARE_OPT(__ATTR_FDREAD(1) __ATTR_OUTS(2, 3),size_t,__THROWING(...),Read,(__fd_t __fd, void *__buf, size_t __bufsize),(__fd,__buf,__bufsize))
/* >> write(2)
 * Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much  data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
__CDECLARE_OPT(__ATTR_FDWRITE(1) __ATTR_INS(2, 3),size_t,__THROWING(...),Write,(__fd_t __fd, void const *__buf, size_t __bufsize),(__fd,__buf,__bufsize))
#ifdef __USE_KOS
#ifdef __CRT_HAVE_ReadAll
/* >> readall(3)
 * Same  as `read(2)', however  keep on reading until  `read()' indicates EOF (causing
 * `readall()' to immediately return `0') or the entirety of the given buffer has been
 * filled (in which case `bufsize' is returned).
 * If  an error occurs before all data could be read, try to use SEEK_CUR to rewind
 * the file descriptor by the amount of data that had already been loaded. - Errors
 * during this phase are silently ignored and don't cause `errno' to change */
__CDECLARE(__ATTR_FDREAD(1) __ATTR_OUTS(2, 3),size_t,__THROWING(...),ReadAll,(__fd_t __fd, void *__buf, size_t __bufsize),(__fd,__buf,__bufsize))
#else /* __CRT_HAVE_ReadAll */
#include <bits/types.h>
#if defined(__CRT_HAVE_Read) && (defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek))
#include <libc/local/kos.unistd/ReadAll.h>
/* >> readall(3)
 * Same  as `read(2)', however  keep on reading until  `read()' indicates EOF (causing
 * `readall()' to immediately return `0') or the entirety of the given buffer has been
 * filled (in which case `bufsize' is returned).
 * If  an error occurs before all data could be read, try to use SEEK_CUR to rewind
 * the file descriptor by the amount of data that had already been loaded. - Errors
 * during this phase are silently ignored and don't cause `errno' to change */
__NAMESPACE_LOCAL_USING_OR_IMPL(ReadAll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDREAD(1) __ATTR_OUTS(2, 3) size_t (__LIBCCALL ReadAll)(__fd_t __fd, void *__buf, size_t __bufsize) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ReadAll))(__fd, __buf, __bufsize); })
#endif /* __CRT_HAVE_Read && (__CRT_HAVE_lseek64 || __CRT_HAVE__lseeki64 || __CRT_HAVE_llseek || __CRT_HAVE___llseek || __CRT_HAVE_lseek || __CRT_HAVE__lseek || __CRT_HAVE___lseek || __CRT_HAVE___libc_lseek) */
#endif /* !__CRT_HAVE_ReadAll */
#ifdef __CRT_HAVE_WriteAll
/* >> writeall(3)
 * Same as `write(2)', however keep on  writing until `write()' indicates EOF  (causing
 * `writeall()' to immediately return `0') or the entirety of the given buffer has been
 * written (in which case `bufsize' is returned). */
__CDECLARE(__ATTR_FDWRITE(1) __ATTR_INS(2, 3),size_t,__THROWING(...),WriteAll,(__fd_t __fd, void const *__buf, size_t __bufsize),(__fd,__buf,__bufsize))
#else /* __CRT_HAVE_WriteAll */
#include <hybrid/typecore.h>
#include <bits/crt/format-printer.h>
#if defined(__CRT_HAVE_WritePrinter) && defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_INT__ == __SIZEOF_POINTER__
/* >> writeall(3)
 * Same as `write(2)', however keep on  writing until `write()' indicates EOF  (causing
 * `writeall()' to immediately return `0') or the entirety of the given buffer has been
 * written (in which case `bufsize' is returned). */
__CREDIRECT(__ATTR_FDWRITE(1) __ATTR_INS(2, 3),size_t,__THROWING(...),WriteAll,(__fd_t __fd, void const *__buf, size_t __bufsize),WritePrinter,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE_Write)
#include <libc/local/kos.unistd/WriteAll.h>
/* >> writeall(3)
 * Same as `write(2)', however keep on  writing until `write()' indicates EOF  (causing
 * `writeall()' to immediately return `0') or the entirety of the given buffer has been
 * written (in which case `bufsize' is returned). */
__NAMESPACE_LOCAL_USING_OR_IMPL(WriteAll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDWRITE(1) __ATTR_INS(2, 3) size_t (__LIBCCALL WriteAll)(__fd_t __fd, void const *__buf, size_t __bufsize) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(WriteAll))(__fd, __buf, __bufsize); })
#endif /* ... */
#endif /* !__CRT_HAVE_WriteAll */
#include <hybrid/typecore.h>
#include <bits/crt/format-printer.h>
#if defined(__CRT_HAVE_WriteAll) && defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_INT__ == __SIZEOF_POINTER__
/* >> write_printer(3)
 * A pformatprinter-compatible consumer that dumps all input data into `fd' by use
 * of `writeall(3)'. The given `fd' should be encoded by  `WRITE_PRINTER_ARG(fd)'.
 * @return: * : Same as `writeall(3)' */
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3),ssize_t,__THROWING(...),__FORMATPRINTER_CC,WritePrinter,(void *__fd, char const *__restrict __buf, size_t __bufsize),WriteAll,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE_WritePrinter)
/* >> write_printer(3)
 * A pformatprinter-compatible consumer that dumps all input data into `fd' by use
 * of `writeall(3)'. The given `fd' should be encoded by  `WRITE_PRINTER_ARG(fd)'.
 * @return: * : Same as `writeall(3)' */
__LIBC __ATTR_INS(2, 3) ssize_t (__FORMATPRINTER_CC WritePrinter)(void *__fd, char const *__restrict __buf, size_t __bufsize) __THROWS(...) __CASMNAME_SAME("WritePrinter");
#elif defined(__CRT_HAVE_WriteAll) || defined(__CRT_HAVE_Write)
#include <libc/local/kos.unistd/WritePrinter.h>
/* >> write_printer(3)
 * A pformatprinter-compatible consumer that dumps all input data into `fd' by use
 * of `writeall(3)'. The given `fd' should be encoded by  `WRITE_PRINTER_ARG(fd)'.
 * @return: * : Same as `writeall(3)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(WritePrinter, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) ssize_t (__FORMATPRINTER_CC WritePrinter)(void *__fd, char const *__restrict __buf, size_t __bufsize) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(WritePrinter))(__fd, __buf, __bufsize); })
#endif /* ... */

#ifndef WRITE_PRINTER_ARG
/* >> void *WRITE_PRINTER_ARG([[fdwrite]] fd_t fd);
 * Encode a given `fd' as an argument to `write_printer(3)' */
#define WRITE_PRINTER_ARG(fd) ((void *)(__UINTPTR_TYPE__)(__CRT_PRIVATE_UINT(__SIZEOF_FD_T__))(fd))
#endif /* !WRITE_PRINTER_ARG */
#endif /* __USE_KOS */
#include <bits/types.h>
#if defined(__CRT_HAVE_LSeek) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CDECLARE(__ATTR_FDARG(1),__pos_t,__THROWING(...),LSeek,(__fd_t __fd, __off_t __offset, int __whence),(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_LSeek64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(__ATTR_FDARG(1),__pos_t,__THROWING(...),LSeek,(__fd_t __fd, __off_t __offset, int __whence),LSeek64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_LSeek64) || defined(__CRT_HAVE_LSeek)
#include <libc/local/kos.unistd/LSeek.h>
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__NAMESPACE_LOCAL_USING_OR_IMPL(LSeek, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) __pos_t (__LIBCCALL LSeek)(__fd_t __fd, __off_t __offset, int __whence) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(LSeek))(__fd, __offset, __whence); })
#endif /* ... */
/* >> dup2(2)
 * @return: newfd: Returns the new handle upon success.
 * Duplicate a file referred to by `oldfd' into `newfd' */
__CDECLARE_OPT(__ATTR_FDARG(1),__fd_t,__THROWING(...),Dup2,(__fd_t __oldfd, __fd_t __newfd),(__oldfd,__newfd))
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `fd' and return its duplicated handle number */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_FDARG(1),__fd_t,__THROWING(...),Dup,(__fd_t __fd),(__fd))
/* >> chdir(2)
 * Change the current working directory to `path' */
__CDECLARE_VOID_OPT(__ATTR_IN(1),__THROWING(...),ChDir,(char const *__path),(__path))
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CDECLARE_OPT(__ATTR_OUTS(1, 2),char *,__THROWING(...),GetCwd,(char *__buf, size_t __bufsize),(__buf,__bufsize))
#ifdef __CRT_HAVE_Unlink
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CDECLARE_VOID(__ATTR_IN(1),__THROWING(...),Unlink,(char const *__file),(__file))
#else /* __CRT_HAVE_Unlink */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_UnlinkAt)
#include <libc/local/kos.unistd/Unlink.h>
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__NAMESPACE_LOCAL_USING_OR_IMPL(Unlink, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) void (__LIBCCALL Unlink)(char const *__file) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Unlink))(__file); })
#endif /* __AT_FDCWD && __CRT_HAVE_UnlinkAt */
#endif /* !__CRT_HAVE_Unlink */
#ifdef __CRT_HAVE_RmDir
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
__CDECLARE_VOID(__ATTR_IN(1),__THROWING(...),RmDir,(char const *__path),(__path))
#else /* __CRT_HAVE_RmDir */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_UnlinkAt)
#include <libc/local/kos.unistd/RmDir.h>
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
__NAMESPACE_LOCAL_USING_OR_IMPL(RmDir, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) void (__LIBCCALL RmDir)(char const *__path) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(RmDir))(__path); })
#endif /* __AT_FDCWD && __CRT_HAVE_UnlinkAt */
#endif /* !__CRT_HAVE_RmDir */
#ifdef __USE_ATFILE
/* >> fchownat(2)
 * Change the ownership of a given `dfd:file' to `group:owner' */
__CDECLARE_VOID_OPT(__ATTR_IN(2),__THROWING(...),FChOwnAt,(__fd_t __dfd, char const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),(__dfd,__file,__owner,__group,__flags))
/* >> linkat(2)
 * Create a hard link from `fromfd:from', leading to `tofd:to' */
__CDECLARE_VOID_OPT(__ATTR_IN(2) __ATTR_IN(4),__THROWING(...),LinkAt,(__fd_t __fromfd, char const *__from, __fd_t __tofd, char const *__to, __atflag_t __flags),(__fromfd,__from,__tofd,__to,__flags))
/* >> symlinkat(3)
 * Create  a  new  symbolic  link  loaded  with  `link_text'  as link
 * text, at the filesystem location referred to by `tofd:target_path' */
__CDECLARE_VOID_OPT(__ATTR_IN(1) __ATTR_IN(3),__THROWING(...),SymlinkAt,(char const *__link_text, __fd_t __tofd, char const *__target_path),(__link_text,__tofd,__target_path))
/* >> readlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__CDECLARE_OPT(__ATTR_IN(2) __ATTR_OUTS(3, 4),size_t,__THROWING(...),ReadLinkAt,(__fd_t __dfd, char const *__restrict __path, char *__restrict __buf, size_t __buflen),(__dfd,__path,__buf,__buflen))
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `dfd:name' */
__CDECLARE_VOID_OPT(__ATTR_IN(2),__THROWING(...),UnlinkAt,(__fd_t __dfd, char const *__name, __atflag_t __flags),(__dfd,__name,__flags))
#ifdef __USE_KOS
/* >> fchdirat(2)
 * Change the current working directory to `dfd:path'
 * @param: flags: Set of `0 | AT_DOSPATH' */
__CDECLARE_VOID_OPT(__ATTR_IN(2),__THROWING(...),FChDirAt,(__fd_t __dfd, char const *__path, __atflag_t __flags),(__dfd,__path,__flags))
/* >> fsymlinkat(3)
 * Create  a  new  symbolic  link  loaded  with  `link_text'  as link
 * text, at the filesystem location referred to by `tofd:target_path'
 * @param flags: Set of `0 | AT_DOSPATH' */
__CDECLARE_VOID_OPT(__ATTR_IN(1) __ATTR_IN(3),__THROWING(...),FSymlinkAt,(char const *__link_text, __fd_t __tofd, char const *__target_path, __atflag_t __flags),(__link_text,__tofd,__target_path,__flags))
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH | AT_READLINK_REQSIZE' */
__CDECLARE_OPT(__ATTR_IN(2) __ATTR_OUTS(3, 4),size_t,__THROWING(...),FReadLinkAt,(__fd_t __dfd, char const *__restrict __path, char *__restrict __buf, size_t __buflen, __atflag_t __flags),(__dfd,__path,__buf,__buflen,__flags))
#endif /* __USE_KOS */
#endif /* __USE_ATFILE */


#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_LSeek) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(__ATTR_FDARG(1),__pos64_t,__THROWING(...),LSeek64,(__fd_t __fd, __off64_t __offset, int __whence),LSeek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_LSeek64)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CDECLARE(__ATTR_FDARG(1),__pos64_t,__THROWING(...),LSeek64,(__fd_t __fd, __off64_t __offset, int __whence),(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_LSeek)
#include <libc/local/kos.unistd/LSeek64.h>
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__NAMESPACE_LOCAL_USING_OR_IMPL(LSeek64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) __pos64_t (__LIBCCALL LSeek64)(__fd_t __fd, __off64_t __offset, int __whence) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(LSeek64))(__fd, __offset, __whence); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */


#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#if defined(__CRT_HAVE_PRead) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> pread(2), pread64(2)
 * Read data from a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of read bytes */
__CDECLARE(__ATTR_FDREAD(1) __ATTR_OUTS(2, 3),size_t,__THROWING(...),PRead,(__fd_t __fd, void *__buf, size_t __bufsize, pos_t __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PRead64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> pread(2), pread64(2)
 * Read data from a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of read bytes */
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_OUTS(2, 3),size_t,__THROWING(...),PRead,(__fd_t __fd, void *__buf, size_t __bufsize, pos_t __offset),PRead64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PRead64) || defined(__CRT_HAVE_PRead)
#include <libc/local/kos.unistd/PRead.h>
/* >> pread(2), pread64(2)
 * Read data from a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of read bytes */
__NAMESPACE_LOCAL_USING_OR_IMPL(PRead, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDREAD(1) __ATTR_OUTS(2, 3) size_t (__LIBCCALL PRead)(__fd_t __fd, void *__buf, size_t __bufsize, pos_t __offset) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(PRead))(__fd, __buf, __bufsize, __offset); })
#endif /* ... */
#if defined(__CRT_HAVE_PWrite) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> pwrite(2), pwrite64(2)
 * Write data to a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of written bytes */
__CDECLARE(__ATTR_FDWRITE(1) __ATTR_INS(2, 3),size_t,__THROWING(...),PWrite,(__fd_t __fd, void const *__buf, size_t __bufsize, pos_t __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PWrite64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> pwrite(2), pwrite64(2)
 * Write data to a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of written bytes */
__CREDIRECT(__ATTR_FDWRITE(1) __ATTR_INS(2, 3),size_t,__THROWING(...),PWrite,(__fd_t __fd, void const *__buf, size_t __bufsize, pos_t __offset),PWrite64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PWrite64) || defined(__CRT_HAVE_PWrite)
#include <libc/local/kos.unistd/PWrite.h>
/* >> pwrite(2), pwrite64(2)
 * Write data to a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of written bytes */
__NAMESPACE_LOCAL_USING_OR_IMPL(PWrite, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDWRITE(1) __ATTR_INS(2, 3) size_t (__LIBCCALL PWrite)(__fd_t __fd, void const *__buf, size_t __bufsize, pos_t __offset) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(PWrite))(__fd, __buf, __bufsize, __offset); })
#endif /* ... */
#ifdef __USE_KOS
#if defined(__CRT_HAVE_PReadAll) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> preadall(3), preadall64(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
__CDECLARE(__ATTR_FDREAD(1) __ATTR_OUTS(2, 3),size_t,__THROWING(...),PReadAll,(__fd_t __fd, void *__buf, size_t __bufsize, pos_t __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PReadAll64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> preadall(3), preadall64(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_OUTS(2, 3),size_t,__THROWING(...),PReadAll,(__fd_t __fd, void *__buf, size_t __bufsize, pos_t __offset),PReadAll64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PRead64) || defined(__CRT_HAVE_PRead)
#include <libc/local/kos.unistd/PReadAll.h>
/* >> preadall(3), preadall64(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(PReadAll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDREAD(1) __ATTR_OUTS(2, 3) size_t (__LIBCCALL PReadAll)(__fd_t __fd, void *__buf, size_t __bufsize, pos_t __offset) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(PReadAll))(__fd, __buf, __bufsize, __offset); })
#endif /* ... */
#if defined(__CRT_HAVE_PWriteAll) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> pwriteall(3), pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
__CDECLARE(__ATTR_FDWRITE(1) __ATTR_INS(2, 3),size_t,__THROWING(...),PWriteAll,(__fd_t __fd, void const *__buf, size_t __bufsize, pos_t __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PWriteAll64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> pwriteall(3), pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
__CREDIRECT(__ATTR_FDWRITE(1) __ATTR_INS(2, 3),size_t,__THROWING(...),PWriteAll,(__fd_t __fd, void const *__buf, size_t __bufsize, pos_t __offset),PWriteAll64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PWrite64) || defined(__CRT_HAVE_PWrite)
#include <libc/local/kos.unistd/PWriteAll.h>
/* >> pwriteall(3), pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(PWriteAll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDWRITE(1) __ATTR_INS(2, 3) size_t (__LIBCCALL PWriteAll)(__fd_t __fd, void const *__buf, size_t __bufsize, pos_t __offset) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(PWriteAll))(__fd, __buf, __bufsize, __offset); })
#endif /* ... */
#endif /* __USE_KOS */
#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_PRead) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> pread(2), pread64(2)
 * Read data from a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of read bytes */
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_OUTS(2, 3),size_t,__THROWING(...),PRead64,(__fd_t __fd, void *__buf, size_t __bufsize, pos64_t __offset),PRead,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PRead64)
/* >> pread(2), pread64(2)
 * Read data from a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of read bytes */
__CDECLARE(__ATTR_FDREAD(1) __ATTR_OUTS(2, 3),size_t,__THROWING(...),PRead64,(__fd_t __fd, void *__buf, size_t __bufsize, pos64_t __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PRead)
#include <libc/local/kos.unistd/PRead64.h>
/* >> pread(2), pread64(2)
 * Read data from a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of read bytes */
__NAMESPACE_LOCAL_USING_OR_IMPL(PRead64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDREAD(1) __ATTR_OUTS(2, 3) size_t (__LIBCCALL PRead64)(__fd_t __fd, void *__buf, size_t __bufsize, pos64_t __offset) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(PRead64))(__fd, __buf, __bufsize, __offset); })
#endif /* ... */
#if defined(__CRT_HAVE_PWrite) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> pwrite(2), pwrite64(2)
 * Write data to a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of written bytes */
__CREDIRECT(__ATTR_FDWRITE(1) __ATTR_INS(2, 3),size_t,__THROWING(...),PWrite64,(__fd_t __fd, void const *__buf, size_t __bufsize, pos64_t __offset),PWrite,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PWrite64)
/* >> pwrite(2), pwrite64(2)
 * Write data to a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of written bytes */
__CDECLARE(__ATTR_FDWRITE(1) __ATTR_INS(2, 3),size_t,__THROWING(...),PWrite64,(__fd_t __fd, void const *__buf, size_t __bufsize, pos64_t __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PWrite)
#include <libc/local/kos.unistd/PWrite64.h>
/* >> pwrite(2), pwrite64(2)
 * Write data to a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of written bytes */
__NAMESPACE_LOCAL_USING_OR_IMPL(PWrite64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDWRITE(1) __ATTR_INS(2, 3) size_t (__LIBCCALL PWrite64)(__fd_t __fd, void const *__buf, size_t __bufsize, pos64_t __offset) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(PWrite64))(__fd, __buf, __bufsize, __offset); })
#endif /* ... */
#ifdef __USE_KOS
#if defined(__CRT_HAVE_PReadAll) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> preadall(3), preadall64(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_OUTS(2, 3),size_t,__THROWING(...),PReadAll64,(__fd_t __fd, void *__buf, size_t __bufsize, pos64_t __offset),PReadAll,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PReadAll64)
/* >> preadall(3), preadall64(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
__CDECLARE(__ATTR_FDREAD(1) __ATTR_OUTS(2, 3),size_t,__THROWING(...),PReadAll64,(__fd_t __fd, void *__buf, size_t __bufsize, pos64_t __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PRead64) || defined(__CRT_HAVE_PRead)
#include <libc/local/kos.unistd/PReadAll64.h>
/* >> preadall(3), preadall64(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(PReadAll64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDREAD(1) __ATTR_OUTS(2, 3) size_t (__LIBCCALL PReadAll64)(__fd_t __fd, void *__buf, size_t __bufsize, pos64_t __offset) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(PReadAll64))(__fd, __buf, __bufsize, __offset); })
#endif /* ... */
#if defined(__CRT_HAVE_PWriteAll) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> pwriteall(3), pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
__CREDIRECT(__ATTR_FDWRITE(1) __ATTR_INS(2, 3),size_t,__THROWING(...),PWriteAll64,(__fd_t __fd, void const *__buf, size_t __bufsize, pos64_t __offset),PWriteAll,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PWriteAll64)
/* >> pwriteall(3), pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
__CDECLARE(__ATTR_FDWRITE(1) __ATTR_INS(2, 3),size_t,__THROWING(...),PWriteAll64,(__fd_t __fd, void const *__buf, size_t __bufsize, pos64_t __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_PWrite64) || defined(__CRT_HAVE_PWrite)
#include <libc/local/kos.unistd/PWriteAll64.h>
/* >> pwriteall(3), pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(PWriteAll64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDWRITE(1) __ATTR_INS(2, 3) size_t (__LIBCCALL PWriteAll64)(__fd_t __fd, void const *__buf, size_t __bufsize, pos64_t __offset) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(PWriteAll64))(__fd, __buf, __bufsize, __offset); })
#endif /* ... */
#endif /* __USE_KOS */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */


#ifdef __USE_GNU
/* >> pipe2(2)
 * Construct a [reader,writer]-pair of pipes
 * @param: pipedes: Output for pipe fds: [0]: reader; [1]: writer
 * @param: flags:   Set of `O_CLOEXEC | O_CLOFORK | O_NONBLOCK | O_DIRECT'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_VOID_OPT(__ATTR_OUT(1),__THROWING(...),Pipe2,(__fd_t __pipedes[2], __oflag_t __flags),(__pipedes,__flags))
__CDECLARE_OPT(__ATTR_FDARG(1),__fd_t,__THROWING(...),Dup3,(__fd_t __oldfd, __fd_t __newfd, __oflag_t __flags),(__oldfd,__newfd,__flags))
#ifdef __CRT_HAVE_GetCurrentDirName
/* >> GetCurrentDirName(3)
 * Alias for `GetCwd(NULL, 0)' */
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED,char *,__THROWING(...),GetCurrentDirName,(void),())
#elif defined(__CRT_HAVE_GetCwd)
#include <libc/local/kos.unistd/GetCurrentDirName.h>
/* >> GetCurrentDirName(3)
 * Alias for `GetCwd(NULL, 0)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(GetCurrentDirName, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED char *(__LIBCCALL GetCurrentDirName)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(GetCurrentDirName))(); })
#endif /* ... */
#ifdef __CRT_HAVE_SyncFS
__CDECLARE_VOID(__ATTR_FDWRITE(1),__THROWING(...),SyncFS,(__fd_t __fd),(__fd))
#else /* __CRT_HAVE_SyncFS */
#include <libc/local/kos.unistd/SyncFS.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(SyncFS, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDWRITE(1) void (__LIBCCALL SyncFS)(__fd_t __fd) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(SyncFS))(__fd); })
#endif /* !__CRT_HAVE_SyncFS */
/* >> getresuid(2)
 * Get the real, effective, and saved UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_VOID_OPT(__ATTR_OUT_OPT(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(3),__THROWING(...),GetRESUid,(__uid_t *__ruid, __uid_t *__euid, __uid_t *__suid),(__ruid,__euid,__suid))
/* >> getresgid(2)
 * Get the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_VOID_OPT(__ATTR_OUT_OPT(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(3),__THROWING(...),GetRESGid,(__gid_t *__rgid, __gid_t *__egid, __gid_t *__sgid),(__rgid,__egid,__sgid))
/* >> setresuid(2)
 * Set the real, effective, and saved UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_VOID_OPT(,__THROWING(...),SetRESUid,(__uid_t __ruid, __uid_t __euid, __uid_t __suid),(__ruid,__euid,__suid))
/* >> setresgid(2)
 * Set the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_VOID_OPT(,__THROWING(...),SetRESGid,(__gid_t __rgid, __gid_t __egid, __gid_t __sgid),(__rgid,__egid,__sgid))
#endif /* __USE_GNU */
#if (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8)) || defined(__USE_MISC)
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
__CDECLARE_OPT(__ATTR_RETURNS_TWICE __ATTR_WUNUSED,__pid_t,__THROWING(...),VFork,(void),())
#endif
/* >> fchown(2)
 * Change the ownership of a given `fd' to `group:owner' */
__CDECLARE_VOID_OPT(__ATTR_FDARG(1),__THROWING(...),FChOwn,(__fd_t __fd, __uid_t __owner, __gid_t __group),(__fd,__owner,__group))
/* >> fchdir(2)
 * Change the current working directory to `path' */
__CDECLARE_VOID_OPT(__ATTR_FDARG(1),__THROWING(...),FChDir,(__fd_t __fd),(__fd))
/* >> getpgid(2)
 * Return  the ID of  the process group  associated with `pid's process.
 * (That is the TID of the leader of the process group of `pid's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER->PID
 * When `pid' is ZERO(0), use `gettid()' for it instead */
__CDECLARE_OPT(__ATTR_WUNUSED,__pid_t,__THROWING(...),GetPGid,(__pid_t __pid),(__pid))
/* >> getsid(2)
 * Return the ID of the session which a process `pid' is apart of.
 * return  THREAD[PID]->LEADER->GROUP_LEADER->SESSION_LEADER->PID; */
__CDECLARE_OPT(__ATTR_WUNUSED,__pid_t,__THROWING(...),GetSid,(__pid_t __pid),(__pid))
#ifdef __CRT_HAVE_LChOwn
/* >> lchown(2)
 * Change the ownership of a given `file' to `group:owner',
 * but don't reference it if  that file is a symbolic  link */
__CDECLARE_VOID(__ATTR_IN(1),__THROWING(...),LChOwn,(char const *__file, __uid_t __owner, __gid_t __group),(__file,__owner,__group))
#else /* __CRT_HAVE_LChOwn */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && defined(__CRT_HAVE_FChOwnAt)
#include <libc/local/kos.unistd/LChOwn.h>
/* >> lchown(2)
 * Change the ownership of a given `file' to `group:owner',
 * but don't reference it if  that file is a symbolic  link */
__NAMESPACE_LOCAL_USING_OR_IMPL(LChOwn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) void (__LIBCCALL LChOwn)(char const *__file, __uid_t __owner, __gid_t __group) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(LChOwn))(__file, __owner, __group); })
#endif /* __AT_FDCWD && __AT_SYMLINK_NOFOLLOW && __CRT_HAVE_FChOwnAt */
#endif /* !__CRT_HAVE_LChOwn */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#if defined(__CRT_HAVE_Truncate) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CDECLARE_VOID(__ATTR_IN(1),__THROWING(...),Truncate,(char const *__file, pos_t __length),(__file,__length))
#elif defined(__CRT_HAVE_Truncate64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CREDIRECT_VOID(__ATTR_IN(1),__THROWING(...),Truncate,(char const *__file, pos_t __length),Truncate64,(__file,__length))
#elif defined(__CRT_HAVE_Truncate64) || defined(__CRT_HAVE_Truncate)
#include <libc/local/kos.unistd/Truncate.h>
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__NAMESPACE_LOCAL_USING_OR_IMPL(Truncate, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) void (__LIBCCALL Truncate)(char const *__file, pos_t __length) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Truncate))(__file, __length); })
#endif /* ... */
#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_Truncate) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CREDIRECT_VOID(__ATTR_IN(1),__THROWING(...),Truncate64,(char const *__file, pos64_t __length),Truncate,(__file,__length))
#elif defined(__CRT_HAVE_Truncate64)
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CDECLARE_VOID(__ATTR_IN(1),__THROWING(...),Truncate64,(char const *__file, pos64_t __length),(__file,__length))
#elif defined(__CRT_HAVE_Truncate)
#include <libc/local/kos.unistd/Truncate64.h>
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__NAMESPACE_LOCAL_USING_OR_IMPL(Truncate64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) void (__LIBCCALL Truncate64)(char const *__file, pos64_t __length) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Truncate64))(__file, __length); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

#ifdef __USE_XOPEN2K8
/* >> fexecve(2)
 * Replace the calling process with the application image referred
 * to by `execfd'  and execute it's  `main()' method, passing  the
 * given `argv', and setting `environ' to `envp'. */
__CDECLARE_VOID_OPT(__ATTR_NORETURN __ATTR_FDREAD(1) __ATTR_IN(2) __ATTR_IN(3),__THROWING(...),FExecve,(__fd_t __fd, __TARGV, __TENVP),(__fd,___argv,___envp))
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_GNU
/* >> execvpe(3)
 * Replace the  calling process  with the  application  image referred  to by  `file'  and
 * execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CDECLARE_VOID_OPT(__ATTR_NORETURN __ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),__THROWING(...),Execvpe,(char const *__restrict __file, __TARGV, __TENVP),(__file,___argv,___envp))
#endif /* __USE_GNU */

#ifdef __USE_POSIX2
/* >> confstr(3)
 * Retrieve a system configuration string specified by `name'
 * @param: name:   One of `_CS_*' from <asm/crt/confname.h>
 * @param: buf:    Target buffer
 * @param: buflen: Available buffer size (including a trailing \0-character)
 * @return: * :    Required buffer size (including a trailing \0-character)
 * @return: 1 :    Empty configuration string.
 * @return: 0 :    [errno=EINVAL] Bad configuration `name'. */
__CDECLARE_OPT(__ATTR_OUTS(2, 3),size_t,__THROWING(...),ConfStr,(__STDC_INT_AS_UINT_T __name, char *__buf, size_t __buflen),(__name,__buf,__buflen))
#endif /* __USE_POSIX2 */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifdef __CRT_HAVE_Nice
__CDECLARE(,int,__THROWING(...),Nice,(int __inc),(__inc))
#else /* __CRT_HAVE_Nice */
#include <libc/local/kos.unistd/Nice.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(Nice, __FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL Nice)(int __inc) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Nice))(__inc); })
#endif /* !__CRT_HAVE_Nice */
#endif /* __USE_MISC || __USE_XOPEN */

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
/* >> setpgrp(3)
 * Move the calling process into its own process group.
 * Equivalent to `setpgid(0, 0)' */
__CDECLARE_VOID_OPT(,__THROWING(...),SetPGrp,(void),())
/* >> setreuid(2)
 * Set the real and effective UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_VOID_OPT(,__THROWING(...),SetREUid,(__uid_t __ruid, __uid_t __euid),(__ruid,__euid))
/* >> setregid(2)
 * Set the real and effective GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_VOID_OPT(,__THROWING(...),SetREGid,(__gid_t __rgid, __gid_t __egid),(__rgid,__egid))
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

#ifdef __USE_XOPEN2K
/* >> seteuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `euid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
__CDECLARE_VOID_OPT(,__THROWING(...),SetEUid,(__uid_t __euid),(__euid))
/* >> setegid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `egid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
__CDECLARE_VOID_OPT(,__THROWING(...),SetEGid,(__gid_t __egid),(__egid))
#endif /* __USE_XOPEN2K */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
#ifdef __CRT_HAVE_Symlink
/* >> symlink(3)
 * Create  a new  symbolic link  loaded with  `link_text' as link
 * text, at the filesystem location referred to by `target_path'.
 * Same as `symlinkat(link_text, AT_FDCWD, target_path)' */
__CDECLARE_VOID(__ATTR_IN(1) __ATTR_IN(2),__THROWING(...),Symlink,(char const *__link_text, char const *__target_path),(__link_text,__target_path))
#else /* __CRT_HAVE_Symlink */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_SymlinkAt)
#include <libc/local/kos.unistd/Symlink.h>
/* >> symlink(3)
 * Create  a new  symbolic link  loaded with  `link_text' as link
 * text, at the filesystem location referred to by `target_path'.
 * Same as `symlinkat(link_text, AT_FDCWD, target_path)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(Symlink, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN(2) void (__LIBCCALL Symlink)(char const *__link_text, char const *__target_path) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Symlink))(__link_text, __target_path); })
#endif /* __AT_FDCWD && __CRT_HAVE_SymlinkAt */
#endif /* !__CRT_HAVE_Symlink */
#ifdef __CRT_HAVE_ReadLink
/* >> readlink(3)
 * Read the text of a symbolic link under `path' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, path, buf, buflen)'
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__CDECLARE(__ATTR_IN(1) __ATTR_OUTS(2, 3),size_t,__THROWING(...),ReadLink,(char const *__restrict __path, char *__restrict __buf, size_t __buflen),(__path,__buf,__buflen))
#else /* __CRT_HAVE_ReadLink */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_ReadLinkAt)
#include <libc/local/kos.unistd/ReadLink.h>
/* >> readlink(3)
 * Read the text of a symbolic link under `path' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, path, buf, buflen)'
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ReadLink, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUTS(2, 3) size_t (__LIBCCALL ReadLink)(char const *__restrict __path, char *__restrict __buf, size_t __buflen) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ReadLink))(__path, __buf, __buflen); })
#endif /* __AT_FDCWD && __CRT_HAVE_ReadLinkAt */
#endif /* !__CRT_HAVE_ReadLink */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
__CDECLARE_VOID_OPT(__ATTR_OUTS(1, 2),__THROWING(...),GetHostName,(char *__name, size_t __buflen),(__name,__buflen))
#endif /* __USE_UNIX98 || __USE_XOPEN2K */

#ifdef __USE_MISC
/* >> sethostname(2)
 * Set the name of the hosting machine */
__CDECLARE_VOID_OPT(__ATTR_INS(1, 2),__THROWING(...),SetHostName,(char const *__name, size_t __len),(__name,__len))
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
__CDECLARE_VOID_OPT(__ATTR_OUTS(1, 2),__THROWING(...),GetDomainName,(char *__name, size_t __buflen),(__name,__buflen))
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
__CDECLARE_VOID_OPT(__ATTR_INS(1, 2),__THROWING(...),SetDomainName,(char const *__name, size_t __len),(__name,__len))
#ifdef __CRT_HAVE_Syscall
__LIBC __syscall_slong_t (__VLIBCCALL Syscall)(__syscall_ulong_t __sysno, ...) __THROWS(...) __CASMNAME_SAME("Syscall");
#endif /* __CRT_HAVE_Syscall */
#ifdef __USE_KOS
#ifdef __CRT_HAVE_Syscall
__CVREDIRECT(,__LONG64_TYPE__,__THROWING(...),Syscall64,(__syscall_ulong_t __sysno),Syscall,(__sysno),__sysno,6,(__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t))
#elif defined(__CRT_HAVE_Syscall64)
__LIBC __LONG64_TYPE__ (__VLIBCCALL Syscall64)(__syscall_ulong_t __sysno, ...) __THROWS(...) __CASMNAME_SAME("Syscall64");
#endif /* ... */
#endif /* __USE_KOS */
#endif /* __USE_MISC */

#if defined(__USE_MISC) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
/* >> chroot(2)
 * Change  the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `path' */
__CDECLARE_VOID_OPT(__ATTR_IN(1),__THROWING(...),ChRoot,(char const *__restrict __path),(__path))
#endif /* __USE_MISC || (__USE_XOPEN && !__USE_XOPEN2K) */

#if defined(__USE_POSIX199309) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
#if defined(__CRT_HAVE_FTruncate) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CDECLARE_VOID(__ATTR_FDWRITE(1),__THROWING(...),FTruncate,(__fd_t __fd, pos_t __length),(__fd,__length))
#elif defined(__CRT_HAVE_FTruncate64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT_VOID(__ATTR_FDWRITE(1),__THROWING(...),FTruncate,(__fd_t __fd, pos_t __length),FTruncate64,(__fd,__length))
#elif defined(__CRT_HAVE_FTruncate64) || defined(__CRT_HAVE_FTruncate)
#include <libc/local/kos.unistd/FTruncate.h>
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__NAMESPACE_LOCAL_USING_OR_IMPL(FTruncate, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDWRITE(1) void (__LIBCCALL FTruncate)(__fd_t __fd, pos_t __length) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(FTruncate))(__fd, __length); })
#endif /* ... */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_FTruncate) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT_VOID(__ATTR_FDWRITE(1),__THROWING(...),FTruncate64,(__fd_t __fd, pos64_t __length),FTruncate,(__fd,__length))
#elif defined(__CRT_HAVE_FTruncate64)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CDECLARE_VOID(__ATTR_FDWRITE(1),__THROWING(...),FTruncate64,(__fd_t __fd, pos64_t __length),(__fd,__length))
#elif defined(__CRT_HAVE_FTruncate)
#include <libc/local/kos.unistd/FTruncate64.h>
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__NAMESPACE_LOCAL_USING_OR_IMPL(FTruncate64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDWRITE(1) void (__LIBCCALL FTruncate64)(__fd_t __fd, pos64_t __length) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(FTruncate64))(__fd, __length); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_POSIX199309 || __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

#if defined(__USE_POSIX199309) || defined(__USE_UNIX98)
#ifdef __CRT_HAVE_FDataSync
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps,  and its size),  meaning that changes  are written to disk */
__CDECLARE_VOID(__ATTR_FDWRITE(1),__THROWING(...),FDataSync,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE_FSync)
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps,  and its size),  meaning that changes  are written to disk */
__CREDIRECT_VOID(__ATTR_FDWRITE(1),__THROWING(...),FDataSync,(__fd_t __fd),FSync,(__fd))
#else /* ... */
#include <libc/local/kos.unistd/FDataSync.h>
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps,  and its size),  meaning that changes  are written to disk */
__NAMESPACE_LOCAL_USING_OR_IMPL(FDataSync, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDWRITE(1) void (__LIBCCALL FDataSync)(__fd_t __fd) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(FDataSync))(__fd); })
#endif /* !... */
#endif /* __USE_POSIX199309 || __USE_UNIX98 */

#ifdef __USE_NETBSD
#ifdef __CRT_HAVE_LPathConf
/* >> lpathconf(3)
 * Same as `pathconf(3)', but don't dereference `path' if it's a symbolic link */
__CDECLARE(__ATTR_IN(1),__LONGPTR_TYPE__,__THROWING(...),LPathConf,(char const *__path, __STDC_INT_AS_UINT_T __name),(__path,__name))
#else /* __CRT_HAVE_LPathConf */
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_FPathConf) && (defined(__CRT_HAVE_Open64) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_OpenAt64) || defined(__CRT_HAVE_OpenAt))) || defined(__CRT_HAVE_Open)) && defined(__O_RDONLY) && defined(__O_PATH) && defined(__O_NOFOLLOW)
#include <libc/local/kos.unistd/LPathConf.h>
/* >> lpathconf(3)
 * Same as `pathconf(3)', but don't dereference `path' if it's a symbolic link */
__NAMESPACE_LOCAL_USING_OR_IMPL(LPathConf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __LONGPTR_TYPE__ (__LIBCCALL LPathConf)(char const *__path, __STDC_INT_AS_UINT_T __name) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(LPathConf))(__path, __name); })
#endif /* __CRT_HAVE_FPathConf && (__CRT_HAVE_Open64 || (__AT_FDCWD && (__CRT_HAVE_OpenAt64 || __CRT_HAVE_OpenAt)) || __CRT_HAVE_Open) && __O_RDONLY && __O_PATH && __O_NOFOLLOW */
#endif /* !__CRT_HAVE_LPathConf */
#ifdef __CRT_HAVE_SetRUid
/* >> setruid(3)
 * Set only the real UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_VOID(,__THROWING(...),SetRUid,(uid_t __ruid),(__ruid))
#elif defined(__CRT_HAVE_SetREUid)
#include <libc/local/kos.unistd/SetRUid.h>
/* >> setruid(3)
 * Set only the real UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(SetRUid, __FORCELOCAL __ATTR_ARTIFICIAL void (__LIBCCALL SetRUid)(uid_t __ruid) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(SetRUid))(__ruid); })
#endif /* ... */
#ifdef __CRT_HAVE_SetRGid
/* >> setrgid(3)
 * Set only the real GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_VOID(,__THROWING(...),SetRGid,(gid_t __rgid),(__rgid))
#elif defined(__CRT_HAVE_SetREGid)
#include <libc/local/kos.unistd/SetRGid.h>
/* >> setrgid(3)
 * Set only the real GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(SetRGid, __FORCELOCAL __ATTR_ARTIFICIAL void (__LIBCCALL SetRGid)(gid_t __rgid) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(SetRGid))(__rgid); })
#endif /* ... */
#endif /* __USE_NETBSD */
/* >> sysconf(2)
 * @param: name: One of `_SC_*' from <asm/crt/confname.h>
 * Return   a   system    configuration   value    `name'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] `name'  refers to a maximum or minimum
 *                                 limit, and that limit is indeterminate
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
__CDECLARE_OPT(__ATTR_WUNUSED,__LONGPTR_TYPE__,__THROWING(...),SysConf,(__STDC_INT_AS_UINT_T __name),(__name))

#ifdef __USE_BSD
/* >> close_range(2)
 * Close all files handles `>= minfd && <= maxfd' (but see `flags')
 * @param: flags: Set of `0 | CLOSE_RANGE_UNSHARE | CLOSE_RANGE_CLOEXEC'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_VOID_OPT(,__THROWING(...),CloseRange,(unsigned int __minfd, unsigned int __maxfd, unsigned int __flags),(__minfd,__maxfd,__flags))
#endif /* __USE_BSD */

#if defined(__USE_SOLARIS) || defined(__USE_NETBSD)
#ifdef __CRT_HAVE_FChRoot
/* >> fchroot(2)
 * Change the root directory to  `fd'. If `fd' was opened  before a prior call to  `chroot()',
 * and referrs to  a directory,  then this function  can be  used to escape  a chroot()  jail.
 * No special permissions  are required to  use this function,  since a malicious  application
 * could achieve the same behavior by use of `*at' system calls, using `fd' as `dfd' argument. */
__CDECLARE_VOID(__ATTR_FDARG(1),__THROWING(...),FChRoot,(__fd_t __fd),(__fd))
#else /* __CRT_HAVE_FChRoot */
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_Dup2) && defined(__AT_FDROOT)
#include <libc/local/kos.unistd/FChRoot.h>
/* >> fchroot(2)
 * Change the root directory to  `fd'. If `fd' was opened  before a prior call to  `chroot()',
 * and referrs to  a directory,  then this function  can be  used to escape  a chroot()  jail.
 * No special permissions  are required to  use this function,  since a malicious  application
 * could achieve the same behavior by use of `*at' system calls, using `fd' as `dfd' argument. */
__NAMESPACE_LOCAL_USING_OR_IMPL(FChRoot, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) void (__LIBCCALL FChRoot)(__fd_t __fd) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(FChRoot))(__fd); })
#endif /* __CRT_HAVE_Dup2 && __AT_FDROOT */
#endif /* !__CRT_HAVE_FChRoot */
#endif /* __USE_SOLARIS || __USE_NETBSD */

#ifdef __USE_SOLARIS
#if defined(__CRT_HAVE_Tell) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__CDECLARE(__ATTR_WUNUSED __ATTR_FDARG(1),__pos_t,__THROWING(...),Tell,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE_Tell64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__CREDIRECT(__ATTR_WUNUSED __ATTR_FDARG(1),__pos_t,__THROWING(...),Tell,(__fd_t __fd),Tell64,(__fd))
#else /* ... */
#include <asm/os/stdio.h>
#if (defined(__CRT_HAVE_LSeek64) || defined(__CRT_HAVE_LSeek)) && defined(__SEEK_CUR)
#include <libc/local/kos.unistd/Tell.h>
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(Tell, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_FDARG(1) __pos_t (__LIBCCALL Tell)(__fd_t __fd) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Tell))(__fd); })
#endif /* (__CRT_HAVE_LSeek64 || __CRT_HAVE_LSeek) && __SEEK_CUR */
#endif /* !... */
#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_Tell) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__CREDIRECT(__ATTR_WUNUSED __ATTR_FDARG(1),__pos64_t,__THROWING(...),Tell64,(__fd_t __fd),Tell,(__fd))
#elif defined(__CRT_HAVE_Tell64)
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__CDECLARE(__ATTR_WUNUSED __ATTR_FDARG(1),__pos64_t,__THROWING(...),Tell64,(__fd_t __fd),(__fd))
#else /* ... */
#include <asm/os/stdio.h>
#if (defined(__CRT_HAVE_LSeek64) || defined(__CRT_HAVE_LSeek)) && defined(__SEEK_CUR)
#include <libc/local/kos.unistd/Tell64.h>
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(Tell64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_FDARG(1) __pos64_t (__LIBCCALL Tell64)(__fd_t __fd) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Tell64))(__fd); })
#endif /* (__CRT_HAVE_LSeek64 || __CRT_HAVE_LSeek) && __SEEK_CUR */
#endif /* !... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_SOLARIS */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_KOS_UNISTD_H */
