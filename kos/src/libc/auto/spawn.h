/* HASH CRC-32:0xdef8ce33 */
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
#ifndef GUARD_LIBC_AUTO_SPAWN_H
#define GUARD_LIBC_AUTO_SPAWN_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <spawn.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_IN(5) ATTR_IN(6) ATTR_IN_OPT(3) ATTR_IN_OPT(4) errno_t NOTHROW_RPC(LIBCCALL libc_posix_spawn_child)(unsigned int exec_type, void *exec_arg, posix_spawn_file_actions_t const *file_actions, posix_spawnattr_t const *attrp, __TARGV, __TENVP);
INTDEF ATTR_IN(6) ATTR_IN(7) ATTR_IN_OPT(4) ATTR_IN_OPT(5) ATTR_OUT(1) errno_t NOTHROW_RPC(LIBCCALL libc_posix_spawn_impl)(pid_t *__restrict pid, unsigned int exec_type, void *exec_arg, posix_spawn_file_actions_t const *file_actions, posix_spawnattr_t const *attrp, __TARGV, __TENVP);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF ATTR_FDREAD(2) ATTR_IN(5) ATTR_IN(6) ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_OUT(1) errno_t NOTHROW_RPC(LIBDCALL libd_posix_fspawn_np)(pid_t *__restrict pid, fd_t execfd, posix_spawn_file_actions_t const *file_actions, posix_spawnattr_t const *attrp, __TARGV, __TENVP);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
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
INTDEF ATTR_FDREAD(2) ATTR_IN(5) ATTR_IN(6) ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_OUT(1) errno_t NOTHROW_RPC(LIBCCALL libc_posix_fspawn_np)(pid_t *__restrict pid, fd_t execfd, posix_spawn_file_actions_t const *file_actions, posix_spawnattr_t const *attrp, __TARGV, __TENVP);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> posix_xspawn_np(3)
 * Wholly non-portable spawn function which, rather than doing  `execve(2)',
 * `fexecve(2)' or `execvpe(2)' within the newly spawned child process, will
 * instead invoke `(*exec_fn)(exec_arg)'  and (if  non-zero) propagate  that
 * function's return value as an error then-returned by `posix_xspawn_np(3)'
 * When `exec_fn' returns `0', the child process will `_Exit(127)'.
 *
 * @param: exec_fn:  Exec function for the child process
 * @param: exec_arg: Cookie argument passed to `exec_fn'
 * @return: 0 : Success. (The child process's PID has been stored in `*pid')
 * @return: * : Error (errno-code describing the reason of failure) */
INTDEF ATTR_IN_OPT(2) ATTR_IN_OPT(3) ATTR_IN_OPT(5) ATTR_OUT(1) NONNULL((4)) errno_t NOTHROW_RPC(LIBDCALL libd_posix_xspawn_np)(pid_t *__restrict pid, posix_spawn_file_actions_t const *file_actions, posix_spawnattr_t const *attrp, errno_t (LIBDCALL *exec_fn)(void *), void *exec_arg);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> posix_xspawn_np(3)
 * Wholly non-portable spawn function which, rather than doing  `execve(2)',
 * `fexecve(2)' or `execvpe(2)' within the newly spawned child process, will
 * instead invoke `(*exec_fn)(exec_arg)'  and (if  non-zero) propagate  that
 * function's return value as an error then-returned by `posix_xspawn_np(3)'
 * When `exec_fn' returns `0', the child process will `_Exit(127)'.
 *
 * @param: exec_fn:  Exec function for the child process
 * @param: exec_arg: Cookie argument passed to `exec_fn'
 * @return: 0 : Success. (The child process's PID has been stored in `*pid')
 * @return: * : Error (errno-code describing the reason of failure) */
INTDEF ATTR_IN_OPT(2) ATTR_IN_OPT(3) ATTR_IN_OPT(5) ATTR_OUT(1) NONNULL((4)) errno_t NOTHROW_RPC(LIBCCALL libc_posix_xspawn_np)(pid_t *__restrict pid, posix_spawn_file_actions_t const *file_actions, posix_spawnattr_t const *attrp, errno_t (LIBCCALL *exec_fn)(void *), void *exec_arg);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF ATTR_IN(2) ATTR_IN(5) ATTR_IN(6) ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_OUT(1) errno_t NOTHROW_RPC(LIBDCALL libd_posix_spawn)(pid_t *__restrict pid, char const *__restrict path, posix_spawn_file_actions_t const *file_actions, posix_spawnattr_t const *attrp, __TARGV, __TENVP);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
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
INTDEF ATTR_IN(2) ATTR_IN(5) ATTR_IN(6) ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_OUT(1) errno_t NOTHROW_RPC(LIBCCALL libc_posix_spawn)(pid_t *__restrict pid, char const *__restrict path, posix_spawn_file_actions_t const *file_actions, posix_spawnattr_t const *attrp, __TARGV, __TENVP);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> posix_spawnp(3)
 * Same  as  `posix_spawn(3)',  but  search  `getenv("PATH")'  for  `file',  rather  than
 * directly making  use of  `file'  as the  absolute filename  of  the file  to  execute.
 * Note however  that  when  `file'  contains any  slashes,  `$PATH'  won't  be  searched
 * either, but instead, `file' is used as-is. (same as with `execve(2)' vs. `execvpe(3)') */
INTDEF ATTR_IN(2) ATTR_IN(5) ATTR_IN(6) ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_OUT(1) errno_t NOTHROW_RPC(LIBDCALL libd_posix_spawnp)(pid_t *__restrict pid, char const *__restrict file, posix_spawn_file_actions_t const *file_actions, posix_spawnattr_t const *attrp, __TARGV, __TENVP);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> posix_spawnp(3)
 * Same  as  `posix_spawn(3)',  but  search  `getenv("PATH")'  for  `file',  rather  than
 * directly making  use of  `file'  as the  absolute filename  of  the file  to  execute.
 * Note however  that  when  `file'  contains any  slashes,  `$PATH'  won't  be  searched
 * either, but instead, `file' is used as-is. (same as with `execve(2)' vs. `execvpe(3)') */
INTDEF ATTR_IN(2) ATTR_IN(5) ATTR_IN(6) ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_OUT(1) errno_t NOTHROW_RPC(LIBCCALL libc_posix_spawnp)(pid_t *__restrict pid, char const *__restrict file, posix_spawn_file_actions_t const *file_actions, posix_spawnattr_t const *attrp, __TARGV, __TENVP);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> posix_spawnattr_init(3)
 * Initialize a given set of spawn attributes to all zero
 * @return: 0 : Success */
INTDEF ATTR_OUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_init)(posix_spawnattr_t *__restrict attr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> posix_spawnattr_init(3)
 * Initialize a given set of spawn attributes to all zero
 * @return: 0 : Success */
INTDEF ATTR_OUT(1) errno_t NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_init)(posix_spawnattr_t *__restrict attr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> posix_spawnattr_destroy(3)
 * Destroy a given set of spawn attributes
 * @return: 0 : Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_destroy)(posix_spawnattr_t *__restrict attr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> posix_spawnattr_destroy(3)
 * Destroy a given set of spawn attributes
 * @return: 0 : Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_destroy)(posix_spawnattr_t *__restrict attr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> posix_spawnattr_setflags(3)
 * Get the set of flags previously specified by `posix_spawnattr_setflags()'
 * @return: 0 : Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_getflags)(posix_spawnattr_t const *__restrict attr, short int *__restrict pflags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> posix_spawnattr_setflags(3)
 * Get the set of flags previously specified by `posix_spawnattr_setflags()'
 * @return: 0 : Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getflags)(posix_spawnattr_t const *__restrict attr, short int *__restrict pflags);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_setflags)(posix_spawnattr_t *__restrict attr, short int flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
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
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setflags)(posix_spawnattr_t *__restrict attr, short int flags);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> posix_spawnattr_getsigdefault(3)
 * Get the set of signal handler that are reset of `SIG_DFL' by
 * the  child  process  when  `POSIX_SPAWN_SETSIGDEF'  is  set.
 * @return: 0 : Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_getsigdefault)(posix_spawnattr_t const *__restrict attr, sigset_t *__restrict sigdefault);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> posix_spawnattr_getsigdefault(3)
 * Get the set of signal handler that are reset of `SIG_DFL' by
 * the  child  process  when  `POSIX_SPAWN_SETSIGDEF'  is  set.
 * @return: 0 : Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getsigdefault)(posix_spawnattr_t const *__restrict attr, sigset_t *__restrict sigdefault);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> posix_spawnattr_setsigdefault(3)
 * Set the set of signal handler that are reset of `SIG_DFL' by
 * the  child  process  when  `POSIX_SPAWN_SETSIGDEF'  is  set.
 * @return: 0 : Success */
INTDEF ATTR_IN(2) ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_setsigdefault)(posix_spawnattr_t *__restrict attr, sigset_t const *__restrict sigdefault);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> posix_spawnattr_setsigdefault(3)
 * Set the set of signal handler that are reset of `SIG_DFL' by
 * the  child  process  when  `POSIX_SPAWN_SETSIGDEF'  is  set.
 * @return: 0 : Success */
INTDEF ATTR_IN(2) ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setsigdefault)(posix_spawnattr_t *__restrict attr, sigset_t const *__restrict sigdefault);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> posix_spawnattr_getsigmask(3)
 * Get the `sigmask' argument of a call `sigprocmask(SIG_SETMASK, sigmask, NULL)'
 * that the  child process  will perform  when `POSIX_SPAWN_SETSIGMASK'  is  set.
 * @return: 0 : Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_getsigmask)(posix_spawnattr_t const *__restrict attr, sigset_t *__restrict sigmask);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> posix_spawnattr_getsigmask(3)
 * Get the `sigmask' argument of a call `sigprocmask(SIG_SETMASK, sigmask, NULL)'
 * that the  child process  will perform  when `POSIX_SPAWN_SETSIGMASK'  is  set.
 * @return: 0 : Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getsigmask)(posix_spawnattr_t const *__restrict attr, sigset_t *__restrict sigmask);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> posix_spawnattr_getsigmask(3)
 * Set the `sigmask' argument of a call `sigprocmask(SIG_SETMASK, sigmask, NULL)'
 * that the  child process  will perform  when `POSIX_SPAWN_SETSIGMASK'  is  set.
 * @return: 0 : Success */
INTDEF ATTR_IN(2) ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_setsigmask)(posix_spawnattr_t *__restrict attr, sigset_t const *__restrict sigmask);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> posix_spawnattr_getsigmask(3)
 * Set the `sigmask' argument of a call `sigprocmask(SIG_SETMASK, sigmask, NULL)'
 * that the  child process  will perform  when `POSIX_SPAWN_SETSIGMASK'  is  set.
 * @return: 0 : Success */
INTDEF ATTR_IN(2) ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setsigmask)(posix_spawnattr_t *__restrict attr, sigset_t const *__restrict sigmask);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> posix_spawnattr_getpgroup(3)
 * Get the `pgid'  argument of a  call `setpgid(getpid(), pgid)'  that
 * the child process will perform when `POSIX_SPAWN_SETPGROUP' is set.
 * @return: 0 : Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_getpgroup)(posix_spawnattr_t const *__restrict attr, pid_t *__restrict pgroup);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> posix_spawnattr_getpgroup(3)
 * Get the `pgid'  argument of a  call `setpgid(getpid(), pgid)'  that
 * the child process will perform when `POSIX_SPAWN_SETPGROUP' is set.
 * @return: 0 : Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getpgroup)(posix_spawnattr_t const *__restrict attr, pid_t *__restrict pgroup);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> posix_spawnattr_getschedparam(3)
 * Set the `pgid'  argument of a  call `setpgid(getpid(), pgid)'  that
 * the child process will perform when `POSIX_SPAWN_SETPGROUP' is set.
 * HINT: A call `setpgid(getpid(), 0)' is the same as `setpgid(getpid(), getpid())'!
 * @return: 0 : Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_setpgroup)(posix_spawnattr_t *__restrict attr, pid_t pgroup);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> posix_spawnattr_getschedparam(3)
 * Set the `pgid'  argument of a  call `setpgid(getpid(), pgid)'  that
 * the child process will perform when `POSIX_SPAWN_SETPGROUP' is set.
 * HINT: A call `setpgid(getpid(), 0)' is the same as `setpgid(getpid(), getpid())'!
 * @return: 0 : Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setpgroup)(posix_spawnattr_t *__restrict attr, pid_t pgroup);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> posix_spawnattr_getschedparam(3)
 * Get the `policy' argument of a call `sched_setscheduler(getpid(), policy, param)'
 * that  the  child process  will  perform when  `POSIX_SPAWN_SETSCHEDULER'  is set.
 * @return: 0 : Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_getschedpolicy)(posix_spawnattr_t const *__restrict attr, int *__restrict schedpolicy);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> posix_spawnattr_getschedparam(3)
 * Get the `policy' argument of a call `sched_setscheduler(getpid(), policy, param)'
 * that  the  child process  will  perform when  `POSIX_SPAWN_SETSCHEDULER'  is set.
 * @return: 0 : Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getschedpolicy)(posix_spawnattr_t const *__restrict attr, int *__restrict schedpolicy);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> posix_spawnattr_getschedparam(3)
 * Set the `policy' argument of a call `sched_setscheduler(getpid(), policy, param)'
 * that  the  child process  will  perform when  `POSIX_SPAWN_SETSCHEDULER'  is set.
 * @return: 0 : Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_setschedpolicy)(posix_spawnattr_t *__restrict attr, int schedpolicy);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> posix_spawnattr_getschedparam(3)
 * Set the `policy' argument of a call `sched_setscheduler(getpid(), policy, param)'
 * that  the  child process  will  perform when  `POSIX_SPAWN_SETSCHEDULER'  is set.
 * @return: 0 : Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setschedpolicy)(posix_spawnattr_t *__restrict attr, int schedpolicy);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> posix_spawnattr_getschedparam(3)
 * Get the `param' argument of a call `sched_setscheduler(getpid(), policy, param)'
 * that  the child  process will  perform when  `POSIX_SPAWN_SETSCHEDPARAM' is set.
 * @return: 0 : Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_getschedparam)(posix_spawnattr_t const *__restrict attr, struct sched_param *__restrict schedparam);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> posix_spawnattr_getschedparam(3)
 * Get the `param' argument of a call `sched_setscheduler(getpid(), policy, param)'
 * that  the child  process will  perform when  `POSIX_SPAWN_SETSCHEDPARAM' is set.
 * @return: 0 : Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) errno_t NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_getschedparam)(posix_spawnattr_t const *__restrict attr, struct sched_param *__restrict schedparam);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> posix_spawnattr_setschedparam(3)
 * Set the `param' argument of a call `sched_setscheduler(getpid(), policy, param)'
 * that  the child  process will  perform when  `POSIX_SPAWN_SETSCHEDPARAM' is set.
 * @return: 0 : Success */
INTDEF ATTR_IN(2) ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_posix_spawnattr_setschedparam)(posix_spawnattr_t *__restrict attr, struct sched_param const *__restrict schedparam);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> posix_spawnattr_setschedparam(3)
 * Set the `param' argument of a call `sched_setscheduler(getpid(), policy, param)'
 * that  the child  process will  perform when  `POSIX_SPAWN_SETSCHEDPARAM' is set.
 * @return: 0 : Success */
INTDEF ATTR_IN(2) ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBCCALL libc_posix_spawnattr_setschedparam)(posix_spawnattr_t *__restrict attr, struct sched_param const *__restrict schedparam);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> posix_spawn_file_actions_init(3)
 * Initialize the given spawn-file-actions object `file_actions'
 * @return: 0 : Success */
INTDEF ATTR_OUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_posix_spawn_file_actions_init)(posix_spawn_file_actions_t *__restrict file_actions);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> posix_spawn_file_actions_init(3)
 * Initialize the given spawn-file-actions object `file_actions'
 * @return: 0 : Success */
INTDEF ATTR_OUT(1) errno_t NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_init)(posix_spawn_file_actions_t *__restrict file_actions);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> posix_spawn_file_actions_destroy(3)
 * Finalize the given spawn-file-actions object `file_actions'
 * @return: 0 : Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_posix_spawn_file_actions_destroy)(posix_spawn_file_actions_t *__restrict file_actions);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> posix_spawn_file_actions_destroy(3)
 * Finalize the given spawn-file-actions object `file_actions'
 * @return: 0 : Success */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_destroy)(posix_spawn_file_actions_t *__restrict file_actions);
/* Helper functions for allocating an a new file-spawn action entry */
INTDEF WUNUSED ATTR_INOUT(1) struct __spawn_action *NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_alloc)(posix_spawn_file_actions_t *__restrict file_actions);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> posix_spawn_file_actions_addopen(3)
 * Enqueue a call `dup2(open(path, oflags, mode), fd)' to be performed by the child process
 * Note though  that the  intermediate file  returned by  `open(2)' will  not remain  open!
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
INTDEF ATTR_IN(3) ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_posix_spawn_file_actions_addopen)(posix_spawn_file_actions_t *__restrict file_actions, fd_t fd, char const *__restrict path, oflag_t oflags, mode_t mode);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> posix_spawn_file_actions_addopen(3)
 * Enqueue a call `dup2(open(path, oflags, mode), fd)' to be performed by the child process
 * Note though  that the  intermediate file  returned by  `open(2)' will  not remain  open!
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
INTDEF ATTR_IN(3) ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_addopen)(posix_spawn_file_actions_t *__restrict file_actions, fd_t fd, char const *__restrict path, oflag_t oflags, mode_t mode);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> posix_spawn_file_actions_addclose(3)
 * Enqueue a call `close(fd)' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
INTDEF ATTR_FDARG(2) ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_posix_spawn_file_actions_addclose)(posix_spawn_file_actions_t *__restrict file_actions, fd_t fd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> posix_spawn_file_actions_addclose(3)
 * Enqueue a call `close(fd)' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
INTDEF ATTR_FDARG(2) ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_addclose)(posix_spawn_file_actions_t *__restrict file_actions, fd_t fd);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> posix_spawn_file_actions_adddup2(3)
 * Enqueue a call `dup2(oldfd, newfd)' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
INTDEF ATTR_FDARG(2) ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_posix_spawn_file_actions_adddup2)(posix_spawn_file_actions_t *__restrict file_actions, fd_t oldfd, fd_t newfd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> posix_spawn_file_actions_adddup2(3)
 * Enqueue a call `dup2(oldfd, newfd)' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
INTDEF ATTR_FDARG(2) ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_adddup2)(posix_spawn_file_actions_t *__restrict file_actions, fd_t oldfd, fd_t newfd);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> posix_spawn_file_actions_addtcsetpgrp_np(3)
 * Enqueue a call `tcsetpgrp(fd, getpid())' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
INTDEF ATTR_FDARG(2) ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_posix_spawn_file_actions_addtcsetpgrp_np)(posix_spawn_file_actions_t *__restrict file_actions, fd_t fd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> posix_spawn_file_actions_addtcsetpgrp_np(3)
 * Enqueue a call `tcsetpgrp(fd, getpid())' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
INTDEF ATTR_FDARG(2) ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_addtcsetpgrp_np)(posix_spawn_file_actions_t *__restrict file_actions, fd_t fd);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> posix_spawn_file_actions_addclosefrom_np(3)
 * Enqueue a call `closefrom(lowfd)' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_posix_spawn_file_actions_addclosefrom_np)(posix_spawn_file_actions_t *__restrict file_actions, fd_t lowfd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> posix_spawn_file_actions_addclosefrom_np(3)
 * Enqueue a call `closefrom(lowfd)' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
INTDEF ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_addclosefrom_np)(posix_spawn_file_actions_t *__restrict file_actions, fd_t lowfd);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> posix_spawn_file_actions_addchdir_np(3)
 * Enqueue a call `chdir(path)' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
INTDEF ATTR_IN(2) ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_posix_spawn_file_actions_addchdir_np)(posix_spawn_file_actions_t *__restrict file_actions, char const *__restrict path);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> posix_spawn_file_actions_addchdir_np(3)
 * Enqueue a call `chdir(path)' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
INTDEF ATTR_IN(2) ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_addchdir_np)(posix_spawn_file_actions_t *__restrict file_actions, char const *__restrict path);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> posix_spawn_file_actions_addfchdir_np(3)
 * Enqueue a call `fchdir(dfd)' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
INTDEF ATTR_FDARG(2) ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBDCALL libd_posix_spawn_file_actions_addfchdir_np)(posix_spawn_file_actions_t *__restrict file_actions, fd_t dfd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> posix_spawn_file_actions_addfchdir_np(3)
 * Enqueue a call `fchdir(dfd)' to be performed by the child process
 * @return: 0     : Success
 * @return: ENOMEM: Insufficient memory to enqueue the action */
INTDEF ATTR_FDARG(2) ATTR_INOUT(1) errno_t NOTHROW_NCX(LIBCCALL libc_posix_spawn_file_actions_addfchdir_np)(posix_spawn_file_actions_t *__restrict file_actions, fd_t dfd);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> pidfd_spawn(3)
 * Same as `posix_spawn(3)', except that the linux/kos-specific "PIDfd" mechanism is
 * used  to return a reference to the child process in the form of a file descriptor
 * stored in `*pidfd'.
 * @param: pidfd:        Store the PIDfd of the newly spawned child process here
 * @param: path:         The pathname of the program that should be executed
 * @param: file_actions: [0..1] A set of additional actions to perform in regards to file-
 *                              handle operations. Can be used to (e.g.) re-direct  stdout
 *                              for the new process
 * @param: attrp:        [0..1] Additional process attributes to set for the child process
 * @param: argv:         Same as the `argv' accepted by `execve(2)'
 * @param: envp:         Same as the `envp' accepted by `execve(2)'
 * @return: 0 :          Success. (The child process's PID has been stored in `*pid')
 * @return: * :          Error (errno-code describing the reason of failure) */
INTDEF ATTR_IN(2) ATTR_IN(5) ATTR_IN(6) ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_OUT(1) errno_t NOTHROW_RPC(LIBDCALL libd_pidfd_spawn)(fd_t *__restrict pidfd, char const *__restrict path, posix_spawn_file_actions_t const *file_actions, posix_spawnattr_t const *attrp, __TARGV, __TENVP);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> pidfd_spawn(3)
 * Same as `posix_spawn(3)', except that the linux/kos-specific "PIDfd" mechanism is
 * used  to return a reference to the child process in the form of a file descriptor
 * stored in `*pidfd'.
 * @param: pidfd:        Store the PIDfd of the newly spawned child process here
 * @param: path:         The pathname of the program that should be executed
 * @param: file_actions: [0..1] A set of additional actions to perform in regards to file-
 *                              handle operations. Can be used to (e.g.) re-direct  stdout
 *                              for the new process
 * @param: attrp:        [0..1] Additional process attributes to set for the child process
 * @param: argv:         Same as the `argv' accepted by `execve(2)'
 * @param: envp:         Same as the `envp' accepted by `execve(2)'
 * @return: 0 :          Success. (The child process's PID has been stored in `*pid')
 * @return: * :          Error (errno-code describing the reason of failure) */
INTDEF ATTR_IN(2) ATTR_IN(5) ATTR_IN(6) ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_OUT(1) errno_t NOTHROW_RPC(LIBCCALL libc_pidfd_spawn)(fd_t *__restrict pidfd, char const *__restrict path, posix_spawn_file_actions_t const *file_actions, posix_spawnattr_t const *attrp, __TARGV, __TENVP);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> pidfd_spawnp(3)
 * Same as `posix_spawnp(3)', but use a "PIDfd" like `pidfd_spawn(3)' */
INTDEF ATTR_IN(2) ATTR_IN(5) ATTR_IN(6) ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_OUT(1) errno_t NOTHROW_RPC(LIBDCALL libd_pidfd_spawnp)(fd_t *__restrict pidfd, char const *__restrict file, posix_spawn_file_actions_t const *file_actions, posix_spawnattr_t const *attrp, __TARGV, __TENVP);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> pidfd_spawnp(3)
 * Same as `posix_spawnp(3)', but use a "PIDfd" like `pidfd_spawn(3)' */
INTDEF ATTR_IN(2) ATTR_IN(5) ATTR_IN(6) ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_OUT(1) errno_t NOTHROW_RPC(LIBCCALL libc_pidfd_spawnp)(fd_t *__restrict pidfd, char const *__restrict file, posix_spawn_file_actions_t const *file_actions, posix_spawnattr_t const *attrp, __TARGV, __TENVP);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> pidfd_fspawn_np(3)
 * Same as `posix_fspawn_np(3)', but use a "PIDfd" like `pidfd_spawn(3)' */
INTDEF ATTR_FDREAD(2) ATTR_IN(5) ATTR_IN(6) ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_OUT(1) errno_t NOTHROW_RPC(LIBDCALL libd_pidfd_fspawn_np)(fd_t *__restrict pidfd, fd_t execfd, posix_spawn_file_actions_t const *file_actions, posix_spawnattr_t const *attrp, __TARGV, __TENVP);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> pidfd_fspawn_np(3)
 * Same as `posix_fspawn_np(3)', but use a "PIDfd" like `pidfd_spawn(3)' */
INTDEF ATTR_FDREAD(2) ATTR_IN(5) ATTR_IN(6) ATTR_IN_OPT(3) ATTR_IN_OPT(4) ATTR_OUT(1) errno_t NOTHROW_RPC(LIBCCALL libc_pidfd_fspawn_np)(fd_t *__restrict pidfd, fd_t execfd, posix_spawn_file_actions_t const *file_actions, posix_spawnattr_t const *attrp, __TARGV, __TENVP);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> pidfd_fspawn_np(3)
 * Same as `posix_xspawn_np(3)', but use a "PIDfd" like `pidfd_spawn(3)' */
INTDEF ATTR_IN_OPT(2) ATTR_IN_OPT(3) ATTR_IN_OPT(5) ATTR_OUT(1) NONNULL((4)) errno_t NOTHROW_RPC(LIBDCALL libd_pidfd_xspawn_np)(fd_t *__restrict pidfd, posix_spawn_file_actions_t const *file_actions, posix_spawnattr_t const *attrp, errno_t (LIBDCALL *exec_fn)(void *), void *exec_arg);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> pidfd_fspawn_np(3)
 * Same as `posix_xspawn_np(3)', but use a "PIDfd" like `pidfd_spawn(3)' */
INTDEF ATTR_IN_OPT(2) ATTR_IN_OPT(3) ATTR_IN_OPT(5) ATTR_OUT(1) NONNULL((4)) errno_t NOTHROW_RPC(LIBCCALL libc_pidfd_xspawn_np)(fd_t *__restrict pidfd, posix_spawn_file_actions_t const *file_actions, posix_spawnattr_t const *attrp, errno_t (LIBCCALL *exec_fn)(void *), void *exec_arg);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SPAWN_H */
