/* HASH CRC-32:0x76f915d2 */
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
/* (>) Standard: POSIX.1-2004 (Issue 6, IEEE Std 1003.1-2004) */
/* (#) Portability: Cygwin        (/newlib/libc/include/spawn.h) */
/* (#) Portability: DragonFly BSD (/include/spawn.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/spawn.h) */
/* (#) Portability: FreeBSD       (/include/spawn.h) */
/* (#) Portability: GNU C Library (/posix/spawn.h) */
/* (#) Portability: GNU Hurd      (/usr/include/spawn.h) */
/* (#) Portability: NetBSD        (/include/spawn.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/spawn.h) */
/* (#) Portability: OpenBSD       (/include/spawn.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/spawn.h) */
/* (#) Portability: libc6         (/include/spawn.h) */
/* (#) Portability: musl libc     (/include/spawn.h) */
/* (#) Portability: uClibc        (/include/spawn.h) */
#ifndef _SPAWN_H
#define _SPAWN_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <asm/crt/posix_spawn.h>
#include <bits/crt/posix_spawn.h>
#include <bits/os/sched.h>
#include <bits/os/sigset.h>
#include <bits/types.h>
#include <sys/types.h>

#ifdef __USE_GLIBC_BLOAT
#include <sched.h>
#endif /* __USE_GLIBC_BLOAT */

__SYSDECL_BEGIN

/* Flags to be set in the `posix_spawnattr_t'. */

#ifdef __POSIX_SPAWN_RESETIDS
#define POSIX_SPAWN_RESETIDS __POSIX_SPAWN_RESETIDS /* Perform 2 calls `seteuid(getuid())' and `setegid(getgid())' */
#endif /* __POSIX_SPAWN_RESETIDS */
#ifdef __POSIX_SPAWN_SETPGROUP
#define POSIX_SPAWN_SETPGROUP __POSIX_SPAWN_SETPGROUP /* s.a. `posix_spawnattr_setpgroup(3)' */
#endif /* __POSIX_SPAWN_SETPGROUP */
#ifdef __POSIX_SPAWN_SETSIGDEF
#define POSIX_SPAWN_SETSIGDEF __POSIX_SPAWN_SETSIGDEF /* s.a. `posix_spawnattr_setsigdefault(3)' */
#endif /* __POSIX_SPAWN_SETSIGDEF */
#ifdef __POSIX_SPAWN_SETSIGMASK
#define POSIX_SPAWN_SETSIGMASK __POSIX_SPAWN_SETSIGMASK /* s.a. `posix_spawnattr_setsigmask(3)' */
#endif /* __POSIX_SPAWN_SETSIGMASK */
#ifdef __POSIX_SPAWN_SETSCHEDPARAM
#define POSIX_SPAWN_SETSCHEDPARAM __POSIX_SPAWN_SETSCHEDPARAM /* s.a. `posix_spawnattr_setschedparam(3)' */
#endif /* __POSIX_SPAWN_SETSCHEDPARAM */
#ifdef __POSIX_SPAWN_SETSCHEDULER
#define POSIX_SPAWN_SETSCHEDULER __POSIX_SPAWN_SETSCHEDULER /* s.a. `posix_spawnattr_setschedpolicy(3)' */
#endif /* __POSIX_SPAWN_SETSCHEDULER */
#ifdef __USE_GNU
#ifdef __POSIX_SPAWN_USEVFORK
#define POSIX_SPAWN_USEVFORK __POSIX_SPAWN_USEVFORK /* Ignored on KOS, which always uses vfork(2) */
#endif /* __POSIX_SPAWN_USEVFORK */
#ifdef __POSIX_SPAWN_SETSID
#define POSIX_SPAWN_SETSID __POSIX_SPAWN_SETSID /* Call `setsid(2)' within the context of the new process */
#endif /* __POSIX_SPAWN_SETSID */
#ifdef __POSIX_SPAWN_SETCGROUP
#define POSIX_SPAWN_SETCGROUP __POSIX_SPAWN_SETCGROUP /* Set `CLONE_INTO_CGROUP' when spawning a new process (Not implemented on KOS) */
#endif /* __POSIX_SPAWN_SETCGROUP */
#endif /* __USE_GNU */

#ifdef __POSIX_SPAWN_NOEXECERR
#define POSIX_SPAWN_NOEXECERR_NP __POSIX_SPAWN_NOEXECERR /* Don't propagate exec() error, and leave the
                                                          * child as  unreaped with  exit status  `127' */
#endif /* __POSIX_SPAWN_NOEXECERR */


#ifdef __CC__

#ifndef __sigset_t_defined
#define __sigset_t_defined
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */

#ifndef __pid_t_defined
#define __pid_t_defined
typedef __pid_t pid_t;
#endif /* !pid_t_defined */

#ifndef __TARGV
#ifdef __USE_DOS_ALTERATIONS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS_ALTERATIONS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__TARGV */

typedef struct __posix_spawnattr posix_spawnattr_t;
typedef struct __posix_spawn_file_actions posix_spawn_file_actions_t;

#ifdef __USE_KOS
#ifdef __CRT_HAVE_posix_fspawn_np
/* >> posix_fspawn_np(3)
 * Implementation for the fastest possible  method of (safely) doing  fork(2)+fexecve(2)
 * in  order  to  spawn  a  new  process  from  the  given  `execfd'  file   descriptor.
 * For this purpose, any error that may happen during either the fork(3), the fexecve(2)
 * or  any of the numerous additional system calls that may be performed in-between will
 * be returned by this function to the  parent process, while the function itself  never
 * actually returns in the child process.
 * For this  purpose,  this  function tries  to  make  use of  `vfork(2)'  in  combination
 * with  `__ARCH_HAVE_SHARED_VM_VFORK',  and if  that  isn't available,  a  temporary pipe
 * is  used to communicate process initialization errors, as well as to await a successful
 * exec call by using the  fact that a successful exec  will close all `O_CLOEXEC'  files,
 * with the pipe having been given that flag, and that a pipe without both ends still open
 * will always  have its  read immediately  return  (which is  used to  indicate  success)
 * @param: pid:          Store the PID of the newly spawned child process here
 * @param: execfd:       The file descriptor pointing to the file that should be executed
 * @param: file_actions: [0..1] A set of additional actions to perform in regards to file-
 *                              handle operations. Can be used to (e.g.) re-direct  stdout
 *                              for the new process
 * @param: attrp:        [0..1] Additional process attributes to set for the child process
 * @param: argv:         Same as the `argv' accepted by `fexecve(2)'
 * @param: envp:         Same as the `envp' accepted by `fexecve(2)'
 * @return: 0 :          Success. (The child process's PID has been stored in `*pid')
 * @return: * :          Error (errno-code describing the reason of failure) */
__CDECLARE(__ATTR_FDREAD(2) __ATTR_IN(5) __ATTR_IN(6) __ATTR_IN_OPT(3) __ATTR_IN_OPT(4) __ATTR_OUT(1),__errno_t,__NOTHROW_RPC,posix_fspawn_np,(pid_t *__restrict __pid, __fd_t __execfd, posix_spawn_file_actions_t const *__file_actions, posix_spawnattr_t const *__attrp, __TARGV, __TENVP),(__pid,__execfd,__file_actions,__attrp,___argv,___envp))
#else /* __CRT_HAVE_posix_fspawn_np */
#include <asm/os/vfork.h>
#include <asm/os/features.h>
#if (defined(__POSIX_SPAWN_USE_KOS) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)))) && defined(__CRT_HAVE_fexecve) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid))) || (defined(__OS_HAVE_PROCFS_SELF_FD) && defined(__CRT_HAVE_posix_spawn))
#include <libc/local/spawn/posix_fspawn_np.h>
/* >> posix_fspawn_np(3)
 * Implementation for the fastest possible  method of (safely) doing  fork(2)+fexecve(2)
 * in  order  to  spawn  a  new  process  from  the  given  `execfd'  file   descriptor.
 * For this purpose, any error that may happen during either the fork(3), the fexecve(2)
 * or  any of the numerous additional system calls that may be performed in-between will
 * be returned by this function to the  parent process, while the function itself  never
 * actually returns in the child process.
 * For this  purpose,  this  function tries  to  make  use of  `vfork(2)'  in  combination
 * with  `__ARCH_HAVE_SHARED_VM_VFORK',  and if  that  isn't available,  a  temporary pipe
 * is  used to communicate process initialization errors, as well as to await a successful
 * exec call by using the  fact that a successful exec  will close all `O_CLOEXEC'  files,
 * with the pipe having been given that flag, and that a pipe without both ends still open
 * will always  have its  read immediately  return  (which is  used to  indicate  success)
 * @param: pid:          Store the PID of the newly spawned child process here
 * @param: execfd:       The file descriptor pointing to the file that should be executed
 * @param: file_actions: [0..1] A set of additional actions to perform in regards to file-
 *                              handle operations. Can be used to (e.g.) re-direct  stdout
 *                              for the new process
 * @param: attrp:        [0..1] Additional process attributes to set for the child process
 * @param: argv:         Same as the `argv' accepted by `fexecve(2)'
 * @param: envp:         Same as the `envp' accepted by `fexecve(2)'
 * @return: 0 :          Success. (The child process's PID has been stored in `*pid')
 * @return: * :          Error (errno-code describing the reason of failure) */
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_fspawn_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDREAD(2) __ATTR_IN(5) __ATTR_IN(6) __ATTR_IN_OPT(3) __ATTR_IN_OPT(4) __ATTR_OUT(1) __errno_t __NOTHROW_RPC(__LIBCCALL posix_fspawn_np)(pid_t *__restrict __pid, __fd_t __execfd, posix_spawn_file_actions_t const *__file_actions, posix_spawnattr_t const *__attrp, __TARGV, __TENVP) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_fspawn_np))(__pid, __execfd, __file_actions, __attrp, ___argv, ___envp); })
#endif /* (__POSIX_SPAWN_USE_KOS && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close))) && __CRT_HAVE_fexecve && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid)) || (__OS_HAVE_PROCFS_SELF_FD && __CRT_HAVE_posix_spawn) */
#endif /* !__CRT_HAVE_posix_fspawn_np */
#endif /* __USE_KOS */
#ifdef __CRT_HAVE_posix_spawn
/* >> posix_spawn(3)
 * Implementation for the fastest possible method of (safely) doing fork(2)+execve(2)
 * in  order   to   spawn   a   new  process   from   the   given   `path'   program.
 * For this purpose, any error that may happen during either the fork(3), the execve(2)
 * or any of the numerous additional system calls that may be performed in-between will
 * be  returned by this function to the parent process, while the function itself never
 * actually returns in the child process.
 * For this  purpose,  this  function tries  to  make  use of  `vfork(2)'  in  combination
 * with  `__ARCH_HAVE_SHARED_VM_VFORK',  and if  that  isn't available,  a  temporary pipe
 * is  used to communicate process initialization errors, as well as to await a successful
 * exec call by using the  fact that a successful exec  will close all `O_CLOEXEC'  files,
 * with the pipe having been given that flag, and that a pipe without both ends still open
 * will always  have its  read immediately  return  (which is  used to  indicate  success)
 * @param: pid:          Store the PID of the newly spawned child process here
 * @param: path:         The pathname of the program that should be executed
 * @param: file_actions: [0..1] A set of additional actions to perform in regards to file-
 *                              handle operations. Can be used to (e.g.) re-direct  stdout
 *                              for the new process
 * @param: attrp:        [0..1] Additional process attributes to set for the child process
 * @param: argv:         Same as the `argv' accepted by `execve(2)'
 * @param: envp:         Same as the `envp' accepted by `execve(2)'
 * @return: 0 :          Success. (The child process's PID has been stored in `*pid')
 * @return: * :          Error (errno-code describing the reason of failure) */
__CDECLARE(__ATTR_IN(2) __ATTR_IN(5) __ATTR_IN(6) __ATTR_IN_OPT(3) __ATTR_IN_OPT(4) __ATTR_OUT(1),__errno_t,__NOTHROW_RPC,posix_spawn,(pid_t *__restrict __pid, char const *__restrict __path, posix_spawn_file_actions_t const *__file_actions, posix_spawnattr_t const *__attrp, __TARGV, __TENVP),(__pid,__path,__file_actions,__attrp,___argv,___envp))
#else /* __CRT_HAVE_posix_spawn */
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#include <asm/os/vfork.h>
#include <asm/os/features.h>
#if (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_posix_fspawn_np) || (defined(__POSIX_SPAWN_USE_KOS) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)))) && defined(__CRT_HAVE_fexecve) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid))))
#include <libc/local/spawn/posix_spawn.h>
/* >> posix_spawn(3)
 * Implementation for the fastest possible method of (safely) doing fork(2)+execve(2)
 * in  order   to   spawn   a   new  process   from   the   given   `path'   program.
 * For this purpose, any error that may happen during either the fork(3), the execve(2)
 * or any of the numerous additional system calls that may be performed in-between will
 * be  returned by this function to the parent process, while the function itself never
 * actually returns in the child process.
 * For this  purpose,  this  function tries  to  make  use of  `vfork(2)'  in  combination
 * with  `__ARCH_HAVE_SHARED_VM_VFORK',  and if  that  isn't available,  a  temporary pipe
 * is  used to communicate process initialization errors, as well as to await a successful
 * exec call by using the  fact that a successful exec  will close all `O_CLOEXEC'  files,
 * with the pipe having been given that flag, and that a pipe without both ends still open
 * will always  have its  read immediately  return  (which is  used to  indicate  success)
 * @param: pid:          Store the PID of the newly spawned child process here
 * @param: path:         The pathname of the program that should be executed
 * @param: file_actions: [0..1] A set of additional actions to perform in regards to file-
 *                              handle operations. Can be used to (e.g.) re-direct  stdout
 *                              for the new process
 * @param: attrp:        [0..1] Additional process attributes to set for the child process
 * @param: argv:         Same as the `argv' accepted by `execve(2)'
 * @param: envp:         Same as the `envp' accepted by `execve(2)'
 * @return: 0 :          Success. (The child process's PID has been stored in `*pid')
 * @return: * :          Error (errno-code describing the reason of failure) */
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_spawn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_IN(5) __ATTR_IN(6) __ATTR_IN_OPT(3) __ATTR_IN_OPT(4) __ATTR_OUT(1) __errno_t __NOTHROW_RPC(__LIBCCALL posix_spawn)(pid_t *__restrict __pid, char const *__restrict __path, posix_spawn_file_actions_t const *__file_actions, posix_spawnattr_t const *__attrp, __TARGV, __TENVP) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_spawn))(__pid, __path, __file_actions, __attrp, ___argv, ___envp); })
#endif /* (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_posix_fspawn_np || (__POSIX_SPAWN_USE_KOS && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close))) && __CRT_HAVE_fexecve && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))) */
#endif /* !__CRT_HAVE_posix_spawn */
#ifdef __CRT_HAVE_posix_spawnp
/* >> posix_spawnp(3)
 * Same  as  `posix_spawn(3)',  but  search  `getenv("PATH")'  for  `file',  rather  than
 * directly making  use of  `file'  as the  absolute filename  of  the file  to  execute.
 * Note however  that  when  `file'  contains any  slashes,  `$PATH'  won't  be  searched
 * either, but instead, `file' is used as-is. (same as with `execve(2)' vs. `execvpe(3)') */
__CDECLARE(__ATTR_IN(2) __ATTR_IN(5) __ATTR_IN(6) __ATTR_IN_OPT(3) __ATTR_IN_OPT(4) __ATTR_OUT(1),__errno_t,__NOTHROW_RPC,posix_spawnp,(pid_t *__restrict __pid, const char *__restrict __file, posix_spawn_file_actions_t const *__file_actions, posix_spawnattr_t const *__attrp, __TARGV, __TENVP),(__pid,__file,__file_actions,__attrp,___argv,___envp))
#else /* __CRT_HAVE_posix_spawnp */
#include <hybrid/__alloca.h>
#include <libc/template/environ.h>
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#include <asm/os/vfork.h>
#include <asm/os/features.h>
#if (defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_posix_spawn) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_posix_fspawn_np) || (defined(__POSIX_SPAWN_USE_KOS) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)))) && defined(__CRT_HAVE_fexecve) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))) && defined(__hybrid_alloca)
#include <libc/local/spawn/posix_spawnp.h>
/* >> posix_spawnp(3)
 * Same  as  `posix_spawn(3)',  but  search  `getenv("PATH")'  for  `file',  rather  than
 * directly making  use of  `file'  as the  absolute filename  of  the file  to  execute.
 * Note however  that  when  `file'  contains any  slashes,  `$PATH'  won't  be  searched
 * either, but instead, `file' is used as-is. (same as with `execve(2)' vs. `execvpe(3)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_spawnp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_IN(5) __ATTR_IN(6) __ATTR_IN_OPT(3) __ATTR_IN_OPT(4) __ATTR_OUT(1) __errno_t __NOTHROW_RPC(__LIBCCALL posix_spawnp)(pid_t *__restrict __pid, const char *__restrict __file, posix_spawn_file_actions_t const *__file_actions, posix_spawnattr_t const *__attrp, __TARGV, __TENVP) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_spawnp))(__pid, __file, __file_actions, __attrp, ___argv, ___envp); })
#endif /* (__CRT_HAVE_getenv || __LOCAL_environ) && (__CRT_HAVE_posix_spawn || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_posix_fspawn_np || (__POSIX_SPAWN_USE_KOS && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close))) && __CRT_HAVE_fexecve && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))))) && __hybrid_alloca */
#endif /* !__CRT_HAVE_posix_spawnp */
#ifdef __CRT_HAVE_posix_spawnattr_init
/* >> posix_spawnattr_init(3)
 * Initialize a given set of spawn attributes to all zero
 * @return: 0 : Success */
__CDECLARE(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,posix_spawnattr_init,(posix_spawnattr_t *__restrict __attr),(__attr))
#else /* __CRT_HAVE_posix_spawnattr_init */
#include <libc/local/spawn/posix_spawnattr_init.h>
/* >> posix_spawnattr_init(3)
 * Initialize a given set of spawn attributes to all zero
 * @return: 0 : Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_spawnattr_init, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL posix_spawnattr_init)(posix_spawnattr_t *__restrict __attr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_spawnattr_init))(__attr); })
#endif /* !__CRT_HAVE_posix_spawnattr_init */
#ifdef __CRT_HAVE_posix_spawnattr_destroy
/* >> posix_spawnattr_destroy(3)
 * Destroy a given set of spawn attributes
 * @return: 0 : Success */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,posix_spawnattr_destroy,(posix_spawnattr_t *__restrict __attr),(__attr))
#else /* __CRT_HAVE_posix_spawnattr_destroy */
#include <libc/local/spawn/posix_spawnattr_destroy.h>
/* >> posix_spawnattr_destroy(3)
 * Destroy a given set of spawn attributes
 * @return: 0 : Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_spawnattr_destroy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL posix_spawnattr_destroy)(posix_spawnattr_t *__restrict __attr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_spawnattr_destroy))(__attr); })
#endif /* !__CRT_HAVE_posix_spawnattr_destroy */
#ifdef __CRT_HAVE_posix_spawnattr_getflags
/* >> posix_spawnattr_setflags(3)
 * Get the set of flags previously specified by `posix_spawnattr_setflags()'
 * @return: 0 : Success */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,posix_spawnattr_getflags,(posix_spawnattr_t const *__restrict __attr, short int *__restrict __pflags),(__attr,__pflags))
#elif defined(__POSIX_SPAWN_USE_KOS)
#include <libc/local/spawn/posix_spawnattr_getflags.h>
/* >> posix_spawnattr_setflags(3)
 * Get the set of flags previously specified by `posix_spawnattr_setflags()'
 * @return: 0 : Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_spawnattr_getflags, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) __errno_t __NOTHROW_NCX(__LIBCCALL posix_spawnattr_getflags)(posix_spawnattr_t const *__restrict __attr, short int *__restrict __pflags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_spawnattr_getflags))(__attr, __pflags); })
#endif /* ... */
#ifdef __CRT_HAVE_posix_spawnattr_setflags
/* >> posix_spawnattr_setflags(3)
 * Specify the  set of  additional operations  to-be performed  by  the
 * child process prior to being started. The given `flags' is a set of:
 *   - POSIX_SPAWN_RESETIDS:      Perform 2 calls `seteuid(getuid())' and `setegid(getgid())'
 *   - POSIX_SPAWN_SETSIGDEF:     s.a. posix_spawnattr_setsigdefault(3)
 *   - POSIX_SPAWN_SETSIGMASK:    s.a. posix_spawnattr_setsigmask(3)
 *   - POSIX_SPAWN_SETPGROUP:     s.a. posix_spawnattr_setpgroup(3)
 *   - POSIX_SPAWN_SETSCHEDULER:  s.a. posix_spawnattr_setschedpolicy(3)
 *   - POSIX_SPAWN_SETSCHEDPARAM: s.a. posix_spawnattr_setschedparam(3)
 * @return: 0 : Success
 * @return: EINVAL: The given `flags' has unknown/unsupported bits set */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,posix_spawnattr_setflags,(posix_spawnattr_t *__restrict __attr, short int __flags),(__attr,__flags))
#elif defined(__POSIX_SPAWN_USE_KOS)
#include <libc/local/spawn/posix_spawnattr_setflags.h>
/* >> posix_spawnattr_setflags(3)
 * Specify the  set of  additional operations  to-be performed  by  the
 * child process prior to being started. The given `flags' is a set of:
 *   - POSIX_SPAWN_RESETIDS:      Perform 2 calls `seteuid(getuid())' and `setegid(getgid())'
 *   - POSIX_SPAWN_SETSIGDEF:     s.a. posix_spawnattr_setsigdefault(3)
 *   - POSIX_SPAWN_SETSIGMASK:    s.a. posix_spawnattr_setsigmask(3)
 *   - POSIX_SPAWN_SETPGROUP:     s.a. posix_spawnattr_setpgroup(3)
 *   - POSIX_SPAWN_SETSCHEDULER:  s.a. posix_spawnattr_setschedpolicy(3)
 *   - POSIX_SPAWN_SETSCHEDPARAM: s.a. posix_spawnattr_setschedparam(3)
 * @return: 0 : Success
 * @return: EINVAL: The given `flags' has unknown/unsupported bits set */
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_spawnattr_setflags, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL posix_spawnattr_setflags)(posix_spawnattr_t *__restrict __attr, short int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_spawnattr_setflags))(__attr, __flags); })
#endif /* ... */
#ifdef __CRT_HAVE_posix_spawnattr_getsigdefault
/* >> posix_spawnattr_getsigdefault(3)
 * Get the set of signal handler that are reset of `SIG_DFL' by
 * the  child  process  when  `POSIX_SPAWN_SETSIGDEF'  is  set.
 * @return: 0 : Success */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,posix_spawnattr_getsigdefault,(posix_spawnattr_t const *__restrict __attr, sigset_t *__restrict __sigdefault),(__attr,__sigdefault))
#elif defined(__POSIX_SPAWN_USE_KOS)
#include <libc/local/spawn/posix_spawnattr_getsigdefault.h>
/* >> posix_spawnattr_getsigdefault(3)
 * Get the set of signal handler that are reset of `SIG_DFL' by
 * the  child  process  when  `POSIX_SPAWN_SETSIGDEF'  is  set.
 * @return: 0 : Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_spawnattr_getsigdefault, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) __errno_t __NOTHROW_NCX(__LIBCCALL posix_spawnattr_getsigdefault)(posix_spawnattr_t const *__restrict __attr, sigset_t *__restrict __sigdefault) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_spawnattr_getsigdefault))(__attr, __sigdefault); })
#endif /* ... */
#ifdef __CRT_HAVE_posix_spawnattr_setsigdefault
/* >> posix_spawnattr_setsigdefault(3)
 * Set the set of signal handler that are reset of `SIG_DFL' by
 * the  child  process  when  `POSIX_SPAWN_SETSIGDEF'  is  set.
 * @return: 0 : Success */
__CDECLARE(__ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,posix_spawnattr_setsigdefault,(posix_spawnattr_t *__restrict __attr, sigset_t const *__restrict __sigdefault),(__attr,__sigdefault))
#elif defined(__POSIX_SPAWN_USE_KOS)
#include <libc/local/spawn/posix_spawnattr_setsigdefault.h>
/* >> posix_spawnattr_setsigdefault(3)
 * Set the set of signal handler that are reset of `SIG_DFL' by
 * the  child  process  when  `POSIX_SPAWN_SETSIGDEF'  is  set.
 * @return: 0 : Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_spawnattr_setsigdefault, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL posix_spawnattr_setsigdefault)(posix_spawnattr_t *__restrict __attr, sigset_t const *__restrict __sigdefault) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_spawnattr_setsigdefault))(__attr, __sigdefault); })
#endif /* ... */
#ifdef __CRT_HAVE_posix_spawnattr_getsigmask
/* >> posix_spawnattr_getsigmask(3)
 * Get the `sigmask' argument of a call `sigprocmask(SIG_SETMASK, sigmask, NULL)'
 * that the  child process  will perform  when `POSIX_SPAWN_SETSIGMASK'  is  set.
 * @return: 0 : Success */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,posix_spawnattr_getsigmask,(posix_spawnattr_t const *__restrict __attr, sigset_t *__restrict __sigmask),(__attr,__sigmask))
#elif defined(__POSIX_SPAWN_USE_KOS)
#include <libc/local/spawn/posix_spawnattr_getsigmask.h>
/* >> posix_spawnattr_getsigmask(3)
 * Get the `sigmask' argument of a call `sigprocmask(SIG_SETMASK, sigmask, NULL)'
 * that the  child process  will perform  when `POSIX_SPAWN_SETSIGMASK'  is  set.
 * @return: 0 : Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_spawnattr_getsigmask, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) __errno_t __NOTHROW_NCX(__LIBCCALL posix_spawnattr_getsigmask)(posix_spawnattr_t const *__restrict __attr, sigset_t *__restrict __sigmask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_spawnattr_getsigmask))(__attr, __sigmask); })
#endif /* ... */
#ifdef __CRT_HAVE_posix_spawnattr_setsigmask
/* >> posix_spawnattr_getsigmask(3)
 * Set the `sigmask' argument of a call `sigprocmask(SIG_SETMASK, sigmask, NULL)'
 * that the  child process  will perform  when `POSIX_SPAWN_SETSIGMASK'  is  set.
 * @return: 0 : Success */
__CDECLARE(__ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,posix_spawnattr_setsigmask,(posix_spawnattr_t *__restrict __attr, sigset_t const *__restrict __sigmask),(__attr,__sigmask))
#elif defined(__POSIX_SPAWN_USE_KOS)
#include <libc/local/spawn/posix_spawnattr_setsigmask.h>
/* >> posix_spawnattr_getsigmask(3)
 * Set the `sigmask' argument of a call `sigprocmask(SIG_SETMASK, sigmask, NULL)'
 * that the  child process  will perform  when `POSIX_SPAWN_SETSIGMASK'  is  set.
 * @return: 0 : Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_spawnattr_setsigmask, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL posix_spawnattr_setsigmask)(posix_spawnattr_t *__restrict __attr, sigset_t const *__restrict __sigmask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_spawnattr_setsigmask))(__attr, __sigmask); })
#endif /* ... */
#ifdef __CRT_HAVE_posix_spawnattr_getpgroup
/* >> posix_spawnattr_getpgroup(3)
 * Get the `pgid'  argument of a  call `setpgid(getpid(), pgid)'  that
 * the child process will perform when `POSIX_SPAWN_SETPGROUP' is set.
 * @return: 0 : Success */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,posix_spawnattr_getpgroup,(posix_spawnattr_t const *__restrict __attr, pid_t *__restrict __pgroup),(__attr,__pgroup))
#elif defined(__POSIX_SPAWN_USE_KOS)
#include <libc/local/spawn/posix_spawnattr_getpgroup.h>
/* >> posix_spawnattr_getpgroup(3)
 * Get the `pgid'  argument of a  call `setpgid(getpid(), pgid)'  that
 * the child process will perform when `POSIX_SPAWN_SETPGROUP' is set.
 * @return: 0 : Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_spawnattr_getpgroup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) __errno_t __NOTHROW_NCX(__LIBCCALL posix_spawnattr_getpgroup)(posix_spawnattr_t const *__restrict __attr, pid_t *__restrict __pgroup) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_spawnattr_getpgroup))(__attr, __pgroup); })
#endif /* ... */
#ifdef __CRT_HAVE_posix_spawnattr_setpgroup
/* >> posix_spawnattr_getschedparam(3)
 * Set the `pgid'  argument of a  call `setpgid(getpid(), pgid)'  that
 * the child process will perform when `POSIX_SPAWN_SETPGROUP' is set.
 * HINT: A call `setpgid(getpid(), 0)' is the same as `setpgid(getpid(), getpid())'!
 * @return: 0 : Success */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,posix_spawnattr_setpgroup,(posix_spawnattr_t *__restrict __attr, pid_t __pgroup),(__attr,__pgroup))
#elif defined(__POSIX_SPAWN_USE_KOS)
#include <libc/local/spawn/posix_spawnattr_setpgroup.h>
/* >> posix_spawnattr_getschedparam(3)
 * Set the `pgid'  argument of a  call `setpgid(getpid(), pgid)'  that
 * the child process will perform when `POSIX_SPAWN_SETPGROUP' is set.
 * HINT: A call `setpgid(getpid(), 0)' is the same as `setpgid(getpid(), getpid())'!
 * @return: 0 : Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_spawnattr_setpgroup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL posix_spawnattr_setpgroup)(posix_spawnattr_t *__restrict __attr, pid_t __pgroup) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_spawnattr_setpgroup))(__attr, __pgroup); })
#endif /* ... */
#ifdef __CRT_HAVE_posix_spawnattr_getschedpolicy
/* >> posix_spawnattr_getschedparam(3)
 * Get the `policy' argument of a call `sched_setscheduler(getpid(), policy, param)'
 * that  the  child process  will  perform when  `POSIX_SPAWN_SETSCHEDULER'  is set.
 * @return: 0 : Success */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,posix_spawnattr_getschedpolicy,(posix_spawnattr_t const *__restrict __attr, int *__restrict __schedpolicy),(__attr,__schedpolicy))
#elif defined(__POSIX_SPAWN_USE_KOS)
#include <libc/local/spawn/posix_spawnattr_getschedpolicy.h>
/* >> posix_spawnattr_getschedparam(3)
 * Get the `policy' argument of a call `sched_setscheduler(getpid(), policy, param)'
 * that  the  child process  will  perform when  `POSIX_SPAWN_SETSCHEDULER'  is set.
 * @return: 0 : Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_spawnattr_getschedpolicy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) __errno_t __NOTHROW_NCX(__LIBCCALL posix_spawnattr_getschedpolicy)(posix_spawnattr_t const *__restrict __attr, int *__restrict __schedpolicy) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_spawnattr_getschedpolicy))(__attr, __schedpolicy); })
#endif /* ... */
#ifdef __CRT_HAVE_posix_spawnattr_setschedpolicy
/* >> posix_spawnattr_getschedparam(3)
 * Set the `policy' argument of a call `sched_setscheduler(getpid(), policy, param)'
 * that  the  child process  will  perform when  `POSIX_SPAWN_SETSCHEDULER'  is set.
 * @return: 0 : Success */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,posix_spawnattr_setschedpolicy,(posix_spawnattr_t *__restrict __attr, int __schedpolicy),(__attr,__schedpolicy))
#elif defined(__POSIX_SPAWN_USE_KOS)
#include <libc/local/spawn/posix_spawnattr_setschedpolicy.h>
/* >> posix_spawnattr_getschedparam(3)
 * Set the `policy' argument of a call `sched_setscheduler(getpid(), policy, param)'
 * that  the  child process  will  perform when  `POSIX_SPAWN_SETSCHEDULER'  is set.
 * @return: 0 : Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_spawnattr_setschedpolicy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL posix_spawnattr_setschedpolicy)(posix_spawnattr_t *__restrict __attr, int __schedpolicy) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_spawnattr_setschedpolicy))(__attr, __schedpolicy); })
#endif /* ... */
#ifdef __CRT_HAVE_posix_spawnattr_getschedparam
/* >> posix_spawnattr_getschedparam(3)
 * Get the `param' argument of a call `sched_setscheduler(getpid(), policy, param)'
 * that  the child  process will  perform when  `POSIX_SPAWN_SETSCHEDPARAM' is set.
 * @return: 0 : Success */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),__errno_t,__NOTHROW_NCX,posix_spawnattr_getschedparam,(posix_spawnattr_t const *__restrict __attr, struct sched_param *__restrict __schedparam),(__attr,__schedparam))
#elif defined(__POSIX_SPAWN_USE_KOS)
#include <libc/local/spawn/posix_spawnattr_getschedparam.h>
/* >> posix_spawnattr_getschedparam(3)
 * Get the `param' argument of a call `sched_setscheduler(getpid(), policy, param)'
 * that  the child  process will  perform when  `POSIX_SPAWN_SETSCHEDPARAM' is set.
 * @return: 0 : Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_spawnattr_getschedparam, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) __errno_t __NOTHROW_NCX(__LIBCCALL posix_spawnattr_getschedparam)(posix_spawnattr_t const *__restrict __attr, struct sched_param *__restrict __schedparam) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_spawnattr_getschedparam))(__attr, __schedparam); })
#endif /* ... */
#ifdef __CRT_HAVE_posix_spawnattr_setschedparam
/* >> posix_spawnattr_setschedparam(3)
 * Set the `param' argument of a call `sched_setscheduler(getpid(), policy, param)'
 * that  the child  process will  perform when  `POSIX_SPAWN_SETSCHEDPARAM' is set.
 * @return: 0 : Success */
__CDECLARE(__ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,posix_spawnattr_setschedparam,(posix_spawnattr_t *__restrict __attr, struct sched_param const *__restrict __schedparam),(__attr,__schedparam))
#elif defined(__POSIX_SPAWN_USE_KOS)
#include <libc/local/spawn/posix_spawnattr_setschedparam.h>
/* >> posix_spawnattr_setschedparam(3)
 * Set the `param' argument of a call `sched_setscheduler(getpid(), policy, param)'
 * that  the child  process will  perform when  `POSIX_SPAWN_SETSCHEDPARAM' is set.
 * @return: 0 : Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_spawnattr_setschedparam, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL posix_spawnattr_setschedparam)(posix_spawnattr_t *__restrict __attr, struct sched_param const *__restrict __schedparam) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_spawnattr_setschedparam))(__attr, __schedparam); })
#endif /* ... */
#ifdef __CRT_HAVE_posix_spawn_file_actions_init
/* >> posix_spawn_file_actions_init(3)
 * Initialize the given spawn-file-actions object `file_actions'
 * @return: 0 : Success */
__CDECLARE(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,posix_spawn_file_actions_init,(posix_spawn_file_actions_t *__restrict __file_actions),(__file_actions))
#else /* __CRT_HAVE_posix_spawn_file_actions_init */
#include <libc/local/spawn/posix_spawn_file_actions_init.h>
/* >> posix_spawn_file_actions_init(3)
 * Initialize the given spawn-file-actions object `file_actions'
 * @return: 0 : Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_spawn_file_actions_init, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL posix_spawn_file_actions_init)(posix_spawn_file_actions_t *__restrict __file_actions) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_spawn_file_actions_init))(__file_actions); })
#endif /* !__CRT_HAVE_posix_spawn_file_actions_init */
#ifdef __CRT_HAVE_posix_spawn_file_actions_destroy
/* >> posix_spawn_file_actions_destroy(3)
 * Finalize the given spawn-file-actions object `file_actions'
 * @return: 0 : Success */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,posix_spawn_file_actions_destroy,(posix_spawn_file_actions_t *__restrict __file_actions),(__file_actions))
#elif defined(__POSIX_SPAWN_USE_KOS)
#include <libc/local/spawn/posix_spawn_file_actions_destroy.h>
/* >> posix_spawn_file_actions_destroy(3)
 * Finalize the given spawn-file-actions object `file_actions'
 * @return: 0 : Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_spawn_file_actions_destroy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL posix_spawn_file_actions_destroy)(posix_spawn_file_actions_t *__restrict __file_actions) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_spawn_file_actions_destroy))(__file_actions); })
#endif /* ... */
#ifdef __CRT_HAVE_posix_spawn_file_actions_addopen
/* >> posix_spawn_file_actions_addopen(3)
 * Enqueue a call `dup2(open(path, oflags, mode), fd)' to be performed by the child process
 * Note though  that the  intermediate file  returned by  `open(2)' will  not remain  open!
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
__CDECLARE(__ATTR_IN(3) __ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,posix_spawn_file_actions_addopen,(posix_spawn_file_actions_t *__restrict __file_actions, __fd_t __fd, char const *__restrict __path, __oflag_t __oflags, mode_t __mode),(__file_actions,__fd,__path,__oflags,__mode))
#elif defined(__POSIX_SPAWN_USE_KOS) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/spawn/posix_spawn_file_actions_addopen.h>
/* >> posix_spawn_file_actions_addopen(3)
 * Enqueue a call `dup2(open(path, oflags, mode), fd)' to be performed by the child process
 * Note though  that the  intermediate file  returned by  `open(2)' will  not remain  open!
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_spawn_file_actions_addopen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_INOUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL posix_spawn_file_actions_addopen)(posix_spawn_file_actions_t *__restrict __file_actions, __fd_t __fd, char const *__restrict __path, __oflag_t __oflags, mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_spawn_file_actions_addopen))(__file_actions, __fd, __path, __oflags, __mode); })
#endif /* ... */
#ifdef __CRT_HAVE_posix_spawn_file_actions_addclose
/* >> posix_spawn_file_actions_addclose(3)
 * Enqueue a call `close(fd)' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
__CDECLARE(__ATTR_FDARG(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,posix_spawn_file_actions_addclose,(posix_spawn_file_actions_t *__restrict __file_actions, __fd_t __fd),(__file_actions,__fd))
#elif defined(__POSIX_SPAWN_USE_KOS) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/spawn/posix_spawn_file_actions_addclose.h>
/* >> posix_spawn_file_actions_addclose(3)
 * Enqueue a call `close(fd)' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_spawn_file_actions_addclose, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(2) __ATTR_INOUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL posix_spawn_file_actions_addclose)(posix_spawn_file_actions_t *__restrict __file_actions, __fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_spawn_file_actions_addclose))(__file_actions, __fd); })
#endif /* ... */
#ifdef __CRT_HAVE_posix_spawn_file_actions_adddup2
/* >> posix_spawn_file_actions_adddup2(3)
 * Enqueue a call `dup2(oldfd, newfd)' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
__CDECLARE(__ATTR_FDARG(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,posix_spawn_file_actions_adddup2,(posix_spawn_file_actions_t *__restrict __file_actions, __fd_t __oldfd, __fd_t __newfd),(__file_actions,__oldfd,__newfd))
#elif defined(__POSIX_SPAWN_USE_KOS) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/spawn/posix_spawn_file_actions_adddup2.h>
/* >> posix_spawn_file_actions_adddup2(3)
 * Enqueue a call `dup2(oldfd, newfd)' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_spawn_file_actions_adddup2, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(2) __ATTR_INOUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL posix_spawn_file_actions_adddup2)(posix_spawn_file_actions_t *__restrict __file_actions, __fd_t __oldfd, __fd_t __newfd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_spawn_file_actions_adddup2))(__file_actions, __oldfd, __newfd); })
#endif /* ... */

#if defined(__USE_MISC) || defined(__USE_KOS)
#ifdef __CRT_HAVE_posix_spawn_file_actions_addtcsetpgrp_np
/* >> posix_spawn_file_actions_addtcsetpgrp_np(3)
 * Enqueue a call `tcsetpgrp(fd, getpid())' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
__CDECLARE(__ATTR_FDARG(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,posix_spawn_file_actions_addtcsetpgrp_np,(posix_spawn_file_actions_t *__restrict __file_actions, __fd_t __fd),(__file_actions,__fd))
#elif defined(__POSIX_SPAWN_ACTION_TCSETPGRP) && defined(__POSIX_SPAWN_USE_KOS) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/spawn/posix_spawn_file_actions_addtcsetpgrp_np.h>
/* >> posix_spawn_file_actions_addtcsetpgrp_np(3)
 * Enqueue a call `tcsetpgrp(fd, getpid())' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_spawn_file_actions_addtcsetpgrp_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(2) __ATTR_INOUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL posix_spawn_file_actions_addtcsetpgrp_np)(posix_spawn_file_actions_t *__restrict __file_actions, __fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_spawn_file_actions_addtcsetpgrp_np))(__file_actions, __fd); })
#endif /* ... */
#endif /* __USE_MISC || __USE_KOS */

#if defined(__USE_MISC) || defined(__USE_SOLARIS)
#ifdef __CRT_HAVE_posix_spawn_file_actions_addclosefrom_np
/* >> posix_spawn_file_actions_addclosefrom_np(3)
 * Enqueue a call `closefrom(lowfd)' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
__CDECLARE(__ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,posix_spawn_file_actions_addclosefrom_np,(posix_spawn_file_actions_t *__restrict __file_actions, __fd_t __lowfd),(__file_actions,__lowfd))
#elif defined(__POSIX_SPAWN_ACTION_CLOSEFROM) && defined(__POSIX_SPAWN_USE_KOS) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/spawn/posix_spawn_file_actions_addclosefrom_np.h>
/* >> posix_spawn_file_actions_addclosefrom_np(3)
 * Enqueue a call `closefrom(lowfd)' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_spawn_file_actions_addclosefrom_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL posix_spawn_file_actions_addclosefrom_np)(posix_spawn_file_actions_t *__restrict __file_actions, __fd_t __lowfd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_spawn_file_actions_addclosefrom_np))(__file_actions, __lowfd); })
#endif /* ... */
#endif /* __USE_MISC || __USE_SOLARIS */

#if defined(__USE_MISC) || defined(__USE_GNU)
#ifdef __CRT_HAVE_posix_spawn_file_actions_addchdir_np
/* >> posix_spawn_file_actions_addchdir_np(3)
 * Enqueue a call `chdir(path)' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
__CDECLARE(__ATTR_IN(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,posix_spawn_file_actions_addchdir_np,(posix_spawn_file_actions_t *__restrict __file_actions, const char *__restrict __path),(__file_actions,__path))
#elif defined(__POSIX_SPAWN_USE_KOS) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/spawn/posix_spawn_file_actions_addchdir_np.h>
/* >> posix_spawn_file_actions_addchdir_np(3)
 * Enqueue a call `chdir(path)' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_spawn_file_actions_addchdir_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL posix_spawn_file_actions_addchdir_np)(posix_spawn_file_actions_t *__restrict __file_actions, const char *__restrict __path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_spawn_file_actions_addchdir_np))(__file_actions, __path); })
#endif /* ... */
#ifdef __CRT_HAVE_posix_spawn_file_actions_addfchdir_np
/* >> posix_spawn_file_actions_addfchdir_np(3)
 * Enqueue a call `fchdir(dfd)' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
__CDECLARE(__ATTR_FDARG(2) __ATTR_INOUT(1),__errno_t,__NOTHROW_NCX,posix_spawn_file_actions_addfchdir_np,(posix_spawn_file_actions_t *__restrict __file_actions, __fd_t __dfd),(__file_actions,__dfd))
#elif defined(__POSIX_SPAWN_USE_KOS) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/spawn/posix_spawn_file_actions_addfchdir_np.h>
/* >> posix_spawn_file_actions_addfchdir_np(3)
 * Enqueue a call `fchdir(dfd)' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_spawn_file_actions_addfchdir_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(2) __ATTR_INOUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL posix_spawn_file_actions_addfchdir_np)(posix_spawn_file_actions_t *__restrict __file_actions, __fd_t __dfd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_spawn_file_actions_addfchdir_np))(__file_actions, __dfd); })
#endif /* ... */
#endif /* __USE_MISC || __USE_GNU */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SPAWN_H */
