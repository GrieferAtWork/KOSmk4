/* HASH CRC-32:0x5bd30610 */
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
#ifndef __local_posix_fspawn_np_defined
#define __local_posix_fspawn_np_defined
#include <__crt.h>
#include <asm/crt/posix_spawn.h>
#include <asm/os/vfork.h>
#include <asm/os/features.h>
#if (defined(__POSIX_SPAWN_USE_KOS) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)))) && defined(__CRT_HAVE_fexecve) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid))) || (defined(__OS_HAVE_PROCFS_SELF_FD) && defined(__CRT_HAVE_posix_spawn))
#include <bits/crt/posix_spawn.h>
#include <bits/types.h>
#include <features.h>
#ifndef __TARGV
#ifdef __USE_DOS_ALTERATIONS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS_ALTERATIONS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__TARGV */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__Exit_defined
#define __local___localdep__Exit_defined
#if __has_builtin(__builtin__Exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE__Exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_NORETURN,void,__THROWING,__localdep__Exit,(int __status),_Exit,{ __builtin__Exit(__status); })
#elif __has_builtin(__builtin__exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE__exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_NORETURN,void,__THROWING,__localdep__Exit,(int __status),_exit,{ __builtin__exit(__status); })
#elif defined(__CRT_HAVE__Exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep__Exit,(int __status),_Exit,(__status))
#elif defined(__CRT_HAVE__exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep__Exit,(int __status),_exit,(__status))
#elif defined(__CRT_HAVE_quick_exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep__Exit,(int __status),quick_exit,(__status))
#elif defined(__CRT_HAVE_exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep__Exit,(int __status),exit,(__status))
#else /* ... */
#undef __local___localdep__Exit_defined
#endif /* !... */
#endif /* !__local___localdep__Exit_defined */
#ifndef __local___localdep_chdir_defined
#define __local___localdep_chdir_defined
#ifdef __CRT_HAVE_chdir
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_chdir,(char const *__path),chdir,(__path))
#elif defined(__CRT_HAVE__chdir)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_chdir,(char const *__path),_chdir,(__path))
#elif defined(__CRT_HAVE___chdir)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_chdir,(char const *__path),__chdir,(__path))
#elif defined(__CRT_HAVE___libc_chdir)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_chdir,(char const *__path),__libc_chdir,(__path))
#else /* ... */
#undef __local___localdep_chdir_defined
#endif /* !... */
#endif /* !__local___localdep_chdir_defined */
#ifndef __local___localdep_close_defined
#define __local___localdep_close_defined
#ifdef __CRT_HAVE_close
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),close,(__fd))
#elif defined(__CRT_HAVE__close)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),_close,(__fd))
#elif defined(__CRT_HAVE___close)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__close,(__fd))
#elif defined(__CRT_HAVE___libc_close)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__libc_close,(__fd))
#else /* ... */
#undef __local___localdep_close_defined
#endif /* !... */
#endif /* !__local___localdep_close_defined */
#ifndef __local___localdep_closefrom_defined
#define __local___localdep_closefrom_defined
#ifdef __CRT_HAVE_closefrom
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_closefrom,(__fd_t __lowfd),closefrom,(__lowfd))
#else /* __CRT_HAVE_closefrom */
__NAMESPACE_LOCAL_END
#include <asm/os/fcntl.h>
__NAMESPACE_LOCAL_BEGIN
#if ((defined(__CRT_HAVE_fcntl) || defined(__CRT_HAVE___fcntl) || defined(__CRT_HAVE___libc_fcntl)) && defined(__F_CLOSEM)) || defined(__CRT_HAVE_close_range)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/closefrom.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_closefrom __LIBC_LOCAL_NAME(closefrom)
#else /* ((__CRT_HAVE_fcntl || __CRT_HAVE___fcntl || __CRT_HAVE___libc_fcntl) && __F_CLOSEM) || __CRT_HAVE_close_range */
#undef __local___localdep_closefrom_defined
#endif /* ((!__CRT_HAVE_fcntl && !__CRT_HAVE___fcntl && !__CRT_HAVE___libc_fcntl) || !__F_CLOSEM) && !__CRT_HAVE_close_range */
#endif /* !__CRT_HAVE_closefrom */
#endif /* !__local___localdep_closefrom_defined */
#if !defined(__local___localdep_crt_posix_spawn_defined) && defined(__CRT_HAVE_posix_spawn)
#define __local___localdep_crt_posix_spawn_defined
__CREDIRECT(__ATTR_NONNULL((1, 2, 5, 6)),__errno_t,__NOTHROW_RPC,__localdep_crt_posix_spawn,(__pid_t *__restrict __pid, char const *__restrict __path, struct __posix_spawn_file_actions const *__file_actions, struct __posix_spawnattr const *__attrp, __TARGV, __TENVP),posix_spawn,(__pid,__path,__file_actions,__attrp,___argv,___envp))
#endif /* !__local___localdep_crt_posix_spawn_defined && __CRT_HAVE_posix_spawn */
#ifndef __local___localdep_dup2_defined
#define __local___localdep_dup2_defined
#ifdef __CRT_HAVE_dup2
__CREDIRECT(,__fd_t,__NOTHROW_NCX,__localdep_dup2,(__fd_t __oldfd, __fd_t __newfd),dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE__dup2)
__CREDIRECT(,__fd_t,__NOTHROW_NCX,__localdep_dup2,(__fd_t __oldfd, __fd_t __newfd),_dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE___dup2)
__CREDIRECT(,__fd_t,__NOTHROW_NCX,__localdep_dup2,(__fd_t __oldfd, __fd_t __newfd),__dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE___libc_dup2)
__CREDIRECT(,__fd_t,__NOTHROW_NCX,__localdep_dup2,(__fd_t __oldfd, __fd_t __newfd),__libc_dup2,(__oldfd,__newfd))
#else /* ... */
#undef __local___localdep_dup2_defined
#endif /* !... */
#endif /* !__local___localdep_dup2_defined */
#ifndef __local___localdep_fchdir_defined
#define __local___localdep_fchdir_defined
#ifdef __CRT_HAVE_fchdir
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_fchdir,(__fd_t __fd),fchdir,(__fd))
#elif defined(__CRT_HAVE___fchdir)
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_fchdir,(__fd_t __fd),__fchdir,(__fd))
#elif defined(__CRT_HAVE___libc_fchdir)
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_fchdir,(__fd_t __fd),__libc_fchdir,(__fd))
#else /* ... */
#undef __local___localdep_fchdir_defined
#endif /* !... */
#endif /* !__local___localdep_fchdir_defined */
#ifndef __local___localdep_fexecve_defined
#define __local___localdep_fexecve_defined
#ifdef __CRT_HAVE_fexecve
__CREDIRECT(__ATTR_NONNULL((2, 3)),int,__NOTHROW_RPC,__localdep_fexecve,(__fd_t __execfd, __TARGV, __TENVP),fexecve,(__execfd,___argv,___envp))
#elif defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve))
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/fexecve.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fexecve __LIBC_LOCAL_NAME(fexecve)
#else /* ... */
#undef __local___localdep_fexecve_defined
#endif /* !... */
#endif /* !__local___localdep_fexecve_defined */
#ifndef __local___localdep_fork_defined
#define __local___localdep_fork_defined
#if __has_builtin(__builtin_fork) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fork)
__CEIREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_fork,(void),fork,{ return __builtin_fork(); })
#elif defined(__CRT_HAVE_fork)
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_fork,(void),fork,())
#elif defined(__CRT_HAVE___fork)
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_fork,(void),__fork,())
#elif defined(__CRT_HAVE___libc_fork)
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_fork,(void),__libc_fork,())
#else /* ... */
#undef __local___localdep_fork_defined
#endif /* !... */
#endif /* !__local___localdep_fork_defined */
#ifndef __local___localdep_getgid_defined
#define __local___localdep_getgid_defined
#ifdef __CRT_HAVE_getgid
__CREDIRECT(__ATTR_WUNUSED,__gid_t,__NOTHROW_NCX,__localdep_getgid,(void),getgid,())
#elif defined(__CRT_HAVE___getgid)
__CREDIRECT(__ATTR_WUNUSED,__gid_t,__NOTHROW_NCX,__localdep_getgid,(void),__getgid,())
#elif defined(__CRT_HAVE___libc_getgid)
__CREDIRECT(__ATTR_WUNUSED,__gid_t,__NOTHROW_NCX,__localdep_getgid,(void),__libc_getgid,())
#else /* ... */
#undef __local___localdep_getgid_defined
#endif /* !... */
#endif /* !__local___localdep_getgid_defined */
#ifndef __local___localdep_getuid_defined
#define __local___localdep_getuid_defined
#ifdef __CRT_HAVE_getuid
__CREDIRECT(__ATTR_WUNUSED,__uid_t,__NOTHROW_NCX,__localdep_getuid,(void),getuid,())
#elif defined(__CRT_HAVE___getuid)
__CREDIRECT(__ATTR_WUNUSED,__uid_t,__NOTHROW_NCX,__localdep_getuid,(void),__getuid,())
#elif defined(__CRT_HAVE___libc_getuid)
__CREDIRECT(__ATTR_WUNUSED,__uid_t,__NOTHROW_NCX,__localdep_getuid,(void),__libc_getuid,())
#else /* ... */
#undef __local___localdep_getuid_defined
#endif /* !... */
#endif /* !__local___localdep_getuid_defined */
#ifndef __local___localdep_open_defined
#define __local___localdep_open_defined
__NAMESPACE_LOCAL_END
#include <asm/os/oflags.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___libc_open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__libc_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__open64,(__filename,__oflags),__oflags,1,(__mode_t))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <asm/os/fcntl.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
__NAMESPACE_LOCAL_END
#include <libc/local/fcntl/open.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_open __LIBC_LOCAL_NAME(open)
#else /* __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
#undef __local___localdep_open_defined
#endif /* !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)) */
#endif /* !... */
#endif /* !__local___localdep_open_defined */
#ifndef __local___localdep_pipe2_defined
#define __local___localdep_pipe2_defined
#ifdef __CRT_HAVE_pipe2
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_pipe2,(__fd_t __pipedes[2], __oflag_t __flags),pipe2,(__pipedes,__flags))
#elif defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/pipe2.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_pipe2 __LIBC_LOCAL_NAME(pipe2)
#else /* ... */
#undef __local___localdep_pipe2_defined
#endif /* !... */
#endif /* !__local___localdep_pipe2_defined */
#ifndef __local___localdep_read_defined
#define __local___localdep_read_defined
#ifdef __CRT_HAVE_read
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__read)
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),_read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___read)
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),__read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___libc_read)
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),__libc_read,(__fd,__buf,__bufsize))
#else /* ... */
#undef __local___localdep_read_defined
#endif /* !... */
#endif /* !__local___localdep_read_defined */
#ifndef __local___localdep_sched_getparam_defined
#define __local___localdep_sched_getparam_defined
#ifdef __CRT_HAVE_sched_getparam
__NAMESPACE_LOCAL_END
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sched_getparam,(__pid_t __pid, struct sched_param *__param),sched_getparam,(__pid,__param))
#elif defined(__CRT_HAVE___sched_getparam)
__NAMESPACE_LOCAL_END
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sched_getparam,(__pid_t __pid, struct sched_param *__param),__sched_getparam,(__pid,__param))
#elif defined(__CRT_HAVE___libc_sched_getparam)
__NAMESPACE_LOCAL_END
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sched_getparam,(__pid_t __pid, struct sched_param *__param),__libc_sched_getparam,(__pid,__param))
#else /* ... */
#undef __local___localdep_sched_getparam_defined
#endif /* !... */
#endif /* !__local___localdep_sched_getparam_defined */
#ifndef __local___localdep_sched_setparam_defined
#define __local___localdep_sched_setparam_defined
#ifdef __CRT_HAVE_sched_setparam
__NAMESPACE_LOCAL_END
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sched_setparam,(__pid_t __pid, struct sched_param const *__param),sched_setparam,(__pid,__param))
#elif defined(__CRT_HAVE___sched_setparam)
__NAMESPACE_LOCAL_END
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sched_setparam,(__pid_t __pid, struct sched_param const *__param),__sched_setparam,(__pid,__param))
#elif defined(__CRT_HAVE___libc_sched_setparam)
__NAMESPACE_LOCAL_END
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sched_setparam,(__pid_t __pid, struct sched_param const *__param),__libc_sched_setparam,(__pid,__param))
#else /* ... */
#undef __local___localdep_sched_setparam_defined
#endif /* !... */
#endif /* !__local___localdep_sched_setparam_defined */
#ifndef __local___localdep_sched_setscheduler_defined
#define __local___localdep_sched_setscheduler_defined
#ifdef __CRT_HAVE_sched_setscheduler
__NAMESPACE_LOCAL_END
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sched_setscheduler,(__pid_t __pid, int __policy, struct sched_param const *__param),sched_setscheduler,(__pid,__policy,__param))
#elif defined(__CRT_HAVE___sched_setscheduler)
__NAMESPACE_LOCAL_END
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sched_setscheduler,(__pid_t __pid, int __policy, struct sched_param const *__param),__sched_setscheduler,(__pid,__policy,__param))
#elif defined(__CRT_HAVE___libc_sched_setscheduler)
__NAMESPACE_LOCAL_END
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sched_setscheduler,(__pid_t __pid, int __policy, struct sched_param const *__param),__libc_sched_setscheduler,(__pid,__policy,__param))
#else /* ... */
#undef __local___localdep_sched_setscheduler_defined
#endif /* !... */
#endif /* !__local___localdep_sched_setscheduler_defined */
#if !defined(__local___localdep_setegid_defined) && defined(__CRT_HAVE_setegid)
#define __local___localdep_setegid_defined
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_setegid,(__gid_t __egid),setegid,(__egid))
#endif /* !__local___localdep_setegid_defined && __CRT_HAVE_setegid */
#if !defined(__local___localdep_seteuid_defined) && defined(__CRT_HAVE_seteuid)
#define __local___localdep_seteuid_defined
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_seteuid,(__uid_t __euid),seteuid,(__euid))
#endif /* !__local___localdep_seteuid_defined && __CRT_HAVE_seteuid */
#ifndef __local___localdep_setpgid_defined
#define __local___localdep_setpgid_defined
#ifdef __CRT_HAVE_setpgid
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_setpgid,(__pid_t __pid, __pid_t __pgid),setpgid,(__pid,__pgid))
#elif defined(__CRT_HAVE___setpgid)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_setpgid,(__pid_t __pid, __pid_t __pgid),__setpgid,(__pid,__pgid))
#elif defined(__CRT_HAVE___libc_setpgid)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_setpgid,(__pid_t __pid, __pid_t __pgid),__libc_setpgid,(__pid,__pgid))
#else /* ... */
#undef __local___localdep_setpgid_defined
#endif /* !... */
#endif /* !__local___localdep_setpgid_defined */
#ifndef __local___localdep_sigaction_defined
#define __local___localdep_sigaction_defined
#ifdef __CRT_HAVE_sigaction
__NAMESPACE_LOCAL_END
struct sigaction;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sigaction,(__signo_t __signo, struct sigaction const *__act, struct sigaction *__oact),sigaction,(__signo,__act,__oact))
#elif defined(__CRT_HAVE___sigaction)
__NAMESPACE_LOCAL_END
struct sigaction;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sigaction,(__signo_t __signo, struct sigaction const *__act, struct sigaction *__oact),__sigaction,(__signo,__act,__oact))
#else /* ... */
#undef __local___localdep_sigaction_defined
#endif /* !... */
#endif /* !__local___localdep_sigaction_defined */
#ifndef __local___localdep_sigemptyset_defined
#define __local___localdep_sigemptyset_defined
#ifdef __CRT_HAVE_sigemptyset
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_sigemptyset,(struct __sigset_struct *__set),sigemptyset,(__set))
#else /* __CRT_HAVE_sigemptyset */
__NAMESPACE_LOCAL_END
#include <libc/local/signal/sigemptyset.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sigemptyset __LIBC_LOCAL_NAME(sigemptyset)
#endif /* !__CRT_HAVE_sigemptyset */
#endif /* !__local___localdep_sigemptyset_defined */
#ifndef __local___localdep_sigismember_defined
#define __local___localdep_sigismember_defined
#ifdef __CRT_HAVE_sigismember
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
#include <hybrid/typecore.h>
#ifndef __PRIVATE_SIGSET_VALIDATE_SIGNO
#if defined(__KERNEL__) && __SIZEOF_INT__ >= __SIZEOF_POINTER__
#define __PRIVATE_SIGSET_ISMEMBER_EXT /* nothing */
#else /* __KERNEL__ && __SIZEOF_INT__ >= __SIZEOF_POINTER__ */
#define __PRIVATE_SIGSET_ISMEMBER_EXT != 0
#endif /* !__KERNEL__ && __SIZEOF_INT__ < __SIZEOF_POINTER__ */
#if defined(__KERNEL__) && defined(__KOS__)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) /* nothing */
#elif defined(__NSIG) && defined(__EINVAL)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo)     \
	if __unlikely(signo <= 0 || signo >= __NSIG) { \
		return __libc_seterrno(__EINVAL);          \
	}
#elif defined(__NSIG)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo)     \
	if __unlikely(signo <= 0 || signo >= __NSIG) { \
		return __libc_seterrno(1);                 \
	}
#elif defined(__EINVAL)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) \
	if __unlikely(signo <= 0) {                \
		return __libc_seterrno(__EINVAL);      \
	}
#else /* ... */
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) \
	if __unlikely(signo <= 0) {                \
		return __libc_seterrno(1);             \
	}
#endif /* !... */
#endif /* !__PRIVATE_SIGSET_VALIDATE_SIGNO */
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_sigismember,(struct __sigset_struct const *__set, __signo_t __signo),sigismember,{ __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); return (__set->__val[__word] & __mask) __PRIVATE_SIGSET_ISMEMBER_EXT; })
#elif defined(__CRT_HAVE___sigismember)
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
#include <hybrid/typecore.h>
#ifndef __PRIVATE_SIGSET_VALIDATE_SIGNO
#if defined(__KERNEL__) && __SIZEOF_INT__ >= __SIZEOF_POINTER__
#define __PRIVATE_SIGSET_ISMEMBER_EXT /* nothing */
#else /* __KERNEL__ && __SIZEOF_INT__ >= __SIZEOF_POINTER__ */
#define __PRIVATE_SIGSET_ISMEMBER_EXT != 0
#endif /* !__KERNEL__ && __SIZEOF_INT__ < __SIZEOF_POINTER__ */
#if defined(__KERNEL__) && defined(__KOS__)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) /* nothing */
#elif defined(__NSIG) && defined(__EINVAL)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo)     \
	if __unlikely(signo <= 0 || signo >= __NSIG) { \
		return __libc_seterrno(__EINVAL);          \
	}
#elif defined(__NSIG)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo)     \
	if __unlikely(signo <= 0 || signo >= __NSIG) { \
		return __libc_seterrno(1);                 \
	}
#elif defined(__EINVAL)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) \
	if __unlikely(signo <= 0) {                \
		return __libc_seterrno(__EINVAL);      \
	}
#else /* ... */
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) \
	if __unlikely(signo <= 0) {                \
		return __libc_seterrno(1);             \
	}
#endif /* !... */
#endif /* !__PRIVATE_SIGSET_VALIDATE_SIGNO */
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_sigismember,(struct __sigset_struct const *__set, __signo_t __signo),__sigismember,{ __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); return (__set->__val[__word] & __mask) __PRIVATE_SIGSET_ISMEMBER_EXT; })
#else /* ... */
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
#include <hybrid/typecore.h>
#ifndef __PRIVATE_SIGSET_VALIDATE_SIGNO
#if defined(__KERNEL__) && __SIZEOF_INT__ >= __SIZEOF_POINTER__
#define __PRIVATE_SIGSET_ISMEMBER_EXT /* nothing */
#else /* __KERNEL__ && __SIZEOF_INT__ >= __SIZEOF_POINTER__ */
#define __PRIVATE_SIGSET_ISMEMBER_EXT != 0
#endif /* !__KERNEL__ && __SIZEOF_INT__ < __SIZEOF_POINTER__ */
#if defined(__KERNEL__) && defined(__KOS__)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) /* nothing */
#elif defined(__NSIG) && defined(__EINVAL)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo)     \
	if __unlikely(signo <= 0 || signo >= __NSIG) { \
		return __libc_seterrno(__EINVAL);          \
	}
#elif defined(__NSIG)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo)     \
	if __unlikely(signo <= 0 || signo >= __NSIG) { \
		return __libc_seterrno(1);                 \
	}
#elif defined(__EINVAL)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) \
	if __unlikely(signo <= 0) {                \
		return __libc_seterrno(__EINVAL);      \
	}
#else /* ... */
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) \
	if __unlikely(signo <= 0) {                \
		return __libc_seterrno(1);             \
	}
#endif /* !... */
#endif /* !__PRIVATE_SIGSET_VALIDATE_SIGNO */
__NAMESPACE_LOCAL_BEGIN
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL __localdep_sigismember)(struct __sigset_struct const *__set, __signo_t __signo) { __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); return (__set->__val[__word] & __mask) __PRIVATE_SIGSET_ISMEMBER_EXT; }
#endif /* !... */
#endif /* !__local___localdep_sigismember_defined */
#ifndef __local___localdep_sigprocmask_defined
#define __local___localdep_sigprocmask_defined
#ifdef __CRT_HAVE_sigprocmask
__NAMESPACE_LOCAL_END
struct __sigset_struct;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),sigprocmask,(__how,__set,__oset))
#elif defined(__CRT_HAVE___sigprocmask)
__NAMESPACE_LOCAL_END
struct __sigset_struct;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),__sigprocmask,(__how,__set,__oset))
#elif defined(__CRT_HAVE___libc_sigprocmask)
__NAMESPACE_LOCAL_END
struct __sigset_struct;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),__libc_sigprocmask,(__how,__set,__oset))
#elif defined(__CRT_HAVE_pthread_sigmask)
__NAMESPACE_LOCAL_END
struct __sigset_struct;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),pthread_sigmask,(__how,__set,__oset))
#elif defined(__CRT_HAVE_thr_sigsetmask)
__NAMESPACE_LOCAL_END
struct __sigset_struct;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),thr_sigsetmask,(__how,__set,__oset))
#else /* ... */
#undef __local___localdep_sigprocmask_defined
#endif /* !... */
#endif /* !__local___localdep_sigprocmask_defined */
#ifndef __local___localdep_sprintf_defined
#define __local___localdep_sprintf_defined
#if __has_builtin(__builtin_sprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sprintf) && __has_builtin(__builtin_va_arg_pack)
__CEIREDIRECT(__ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_sprintf,(char *__restrict __buf, char const *__restrict __format, ...),sprintf,{ return __builtin_sprintf(__buf, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_sprintf)
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME("sprintf");
#elif defined(__CRT_HAVE__IO_sprintf)
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME("_IO_sprintf");
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/sprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sprintf __LIBC_LOCAL_NAME(sprintf)
#endif /* !... */
#endif /* !__local___localdep_sprintf_defined */
#if !defined(__local___localdep_tcsetpgrp_defined) && defined(__CRT_HAVE_tcsetpgrp)
#define __local___localdep_tcsetpgrp_defined
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_tcsetpgrp,(__fd_t __fd, __pid_t __pgrp_id),tcsetpgrp,(__fd,__pgrp_id))
#endif /* !__local___localdep_tcsetpgrp_defined && __CRT_HAVE_tcsetpgrp */
#ifndef __local___localdep_vfork_defined
#define __local___localdep_vfork_defined
#ifdef __CRT_HAVE_vfork
__CREDIRECT(__ATTR_RETURNS_TWICE __ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_vfork,(void),vfork,())
#elif defined(__CRT_HAVE___vfork)
__CREDIRECT(__ATTR_RETURNS_TWICE __ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_vfork,(void),__vfork,())
#elif defined(__CRT_HAVE___libc_vfork)
__CREDIRECT(__ATTR_RETURNS_TWICE __ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_vfork,(void),__libc_vfork,())
#else /* ... */
#undef __local___localdep_vfork_defined
#endif /* !... */
#endif /* !__local___localdep_vfork_defined */
#ifndef __local___localdep_waitpid_defined
#define __local___localdep_waitpid_defined
#ifdef __CRT_HAVE_waitpid
__NAMESPACE_LOCAL_END
#include <parts/waitmacros.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__pid_t,__NOTHROW_RPC,__localdep_waitpid,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options),waitpid,(__pid,__stat_loc,__options))
#elif defined(__CRT_HAVE___waitpid)
__NAMESPACE_LOCAL_END
#include <parts/waitmacros.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__pid_t,__NOTHROW_RPC,__localdep_waitpid,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options),__waitpid,(__pid,__stat_loc,__options))
#else /* ... */
#undef __local___localdep_waitpid_defined
#endif /* !... */
#endif /* !__local___localdep_waitpid_defined */
#ifndef __local___localdep_write_defined
#define __local___localdep_write_defined
#ifdef __CRT_HAVE_write
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__write)
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),_write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___write)
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),__write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___libc_write)
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),__libc_write,(__fd,__buf,__bufsize))
#else /* ... */
#undef __local___localdep_write_defined
#endif /* !... */
#endif /* !__local___localdep_write_defined */
__NAMESPACE_LOCAL_END
#include <bits/os/sigaction.h>
#include <libc/errno.h>
#include <hybrid/typecore.h>
#include <asm/os/oflags.h>
#include <asm/os/signal.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(posix_fspawn_np) __ATTR_NONNULL((1, 5, 6)) __errno_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(posix_fspawn_np))(__pid_t *__restrict __pid, __fd_t __execfd, struct __posix_spawn_file_actions const *__file_actions, struct __posix_spawnattr const *__attrp, __TARGV, __TENVP) {
#if defined(__POSIX_SPAWN_USE_KOS) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)))) && defined(__CRT_HAVE_fexecve) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid))




	int __status;
#if !defined(__ARCH_HAVE_SHARED_VM_VFORK) || (!defined(__CRT_HAVE_vfork) && !defined(__CRT_HAVE___vfork) && !defined(__CRT_HAVE___libc_vfork))
	__fd_t __pipes[2];
	__SSIZE_TYPE__ __temp;
#endif /* !__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork) */
	__errno_t __result, __old_errno;
	__pid_t __child;
	__old_errno = __libc_geterrno_or(0);
#if defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))
	(void)__libc_seterrno(0);
	__child = (__NAMESPACE_LOCAL_SYM __localdep_vfork)();
	if (__child == 0)
		goto __do_exec;
	/* Check if the vfork() from  the child returned success, but  left
	 * our (vm-shared) errno as non-zero (which would indicate that the
	 * child encountered an error at  some point after vfork()  already
	 * succeeded) */
	__result = __libc_geterrno_or(0);
	if (__result != 0) {
		if (__child < 0) {
			/* The vfork() itself failed. */
			(void)__libc_seterrno(__old_errno);
			return __result;
		}
		/* Something within the child failed after vfork(). */
		goto __err_join_zombie_child;
	}
	/* Restore the old errno */
	(void)__libc_seterrno(__old_errno);
	/* Write back the child's PID */
	*__pid = __child;
	return __result;
#else /* __ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork) */
	/* Create a pair of pipes for temporary communication. */
	if ((__NAMESPACE_LOCAL_SYM __localdep_pipe2)(__pipes, __O_CLOEXEC)) {
__err_without_child:
		__result = __libc_geterrno_or(0);
		(void)__libc_seterrno(__old_errno);
		return __result;
	}
	__child = (__NAMESPACE_LOCAL_SYM __localdep_fork)();
	if (__child == 0)
		goto __do_exec;
	if (__child < 0)
		goto __err_without_child; /* The fork() itself failed. */
	/* Read from the communication pipe
	 * (NOTE: If exec() succeeds, the pipe will be
	 *        closed and  read() returns  ZERO(0)) */
	(__NAMESPACE_LOCAL_SYM __localdep_close)(__pipes[1]); /* Close the writer. */
	__temp = (__NAMESPACE_LOCAL_SYM __localdep_read)(__pipes[0], &__result, sizeof(__result));
	(__NAMESPACE_LOCAL_SYM __localdep_close)(__pipes[0]); /* Close the reader. */
	if (__temp < 0)
		goto __err_join_zombie_child;
	/* This means that `fexecve()' below closed the pipe during a successful exec(). */
	if (__temp != sizeof(__result)) {
		*__pid = __child;
		(void)__libc_seterrno(__old_errno);
		return 0;
	}
#endif /* !__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork) */
__err_join_zombie_child:
	/* Unless the child was already spawned as detached,
	 * we still have to re-join  it, or else it will  be
	 * left dangling as a zombie process! */
	if ((__NAMESPACE_LOCAL_SYM __localdep_waitpid)(__child, &__status, 0) < 0) {
#ifdef __EINTR
		if (__libc_geterrno() == __EINTR)
			goto __err_join_zombie_child;
#endif /* __EINTR */
	}
	(void)__libc_seterrno(__old_errno);
	return __result;
__do_exec:
	/* Perform additional actions within the child. */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("__used")
#pragma push_macro("__actions")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef __used
#undef __actions
	if (__file_actions) {
		unsigned int __i;
		for (__i = 0; __i < __file_actions->__used; ++__i) {
			struct __spawn_action *__act;
			__act = &__file_actions->__actions[__i];
			switch (__act->__sa_tag) {
#undef __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION

#if !defined(__CRT_HAVE_close) && !defined(__CRT_HAVE__close) && !defined(__CRT_HAVE___close) && !defined(__CRT_HAVE___libc_close)
#define __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION
#else /* !__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close && !__CRT_HAVE___libc_close */
			case __POSIX_SPAWN_ACTION_CLOSE:
				/* Close a file handle */
				if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_close)(__act->__sa_action.__sa_close_action.__sa_fd))
					goto __child_error;
				break;
#endif /* __CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close */


#if !defined(__CRT_HAVE_dup2) && !defined(__CRT_HAVE__dup2) && !defined(__CRT_HAVE___dup2) && !defined(__CRT_HAVE___libc_dup2)
#define __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION
#else /* !__CRT_HAVE_dup2 && !__CRT_HAVE__dup2 && !__CRT_HAVE___dup2 && !__CRT_HAVE___libc_dup2 */
			case __POSIX_SPAWN_ACTION_DUP2:
				/* Duplicate a file handle */
				if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_dup2)(__act->__sa_action.__sa_dup2_action.__sa_oldfd,
				                 __act->__sa_action.__sa_dup2_action.__sa_newfd))
					goto __child_error;
				break;
#endif /* __CRT_HAVE_dup2 || __CRT_HAVE__dup2 || __CRT_HAVE___dup2 || __CRT_HAVE___libc_dup2 */


#if (!defined(__CRT_HAVE_open64) && !defined(__CRT_HAVE___open64) && !defined(__CRT_HAVE_open) && !defined(__CRT_HAVE__open) && !defined(__CRT_HAVE___open) && !defined(__CRT_HAVE___libc_open) && (!defined(__AT_FDCWD) || (!defined(__CRT_HAVE_openat64) && !defined(__CRT_HAVE_openat)))) || (!defined(__CRT_HAVE_dup2) && !defined(__CRT_HAVE__dup2) && !defined(__CRT_HAVE___dup2) && !defined(__CRT_HAVE___libc_dup2)) || (!defined(__CRT_HAVE_close) && !defined(__CRT_HAVE__close) && !defined(__CRT_HAVE___close) && !defined(__CRT_HAVE___libc_close))
#define __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION 1
#else /* (!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_dup2 && !__CRT_HAVE__dup2 && !__CRT_HAVE___dup2 && !__CRT_HAVE___libc_dup2) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close && !__CRT_HAVE___libc_close) */
			case __POSIX_SPAWN_ACTION_OPEN: {
				/* Open a file using `open(2)' */
				__fd_t __tempfd;
				__tempfd = (__NAMESPACE_LOCAL_SYM __localdep_open)(__act->__sa_action.__sa_open_action.__sa_path,
				              __act->__sa_action.__sa_open_action.__sa_oflag,
				              __act->__sa_action.__sa_open_action.__sa_mode);
				if __unlikely(__tempfd < 0)
					goto __child_error;
				if __likely(__tempfd != __act->__sa_action.__sa_open_action.__sa_fd) {
					if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_dup2)(__tempfd, __act->__sa_action.__sa_open_action.__sa_fd))
						goto __child_error;
					(__NAMESPACE_LOCAL_SYM __localdep_close)(__tempfd);
				}
			}	break;
#endif /* (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_dup2 || __CRT_HAVE__dup2 || __CRT_HAVE___dup2 || __CRT_HAVE___libc_dup2) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close) */


#if !defined(__CRT_HAVE_chdir) && !defined(__CRT_HAVE__chdir) && !defined(__CRT_HAVE___chdir) && !defined(__CRT_HAVE___libc_chdir)
#define __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION 1
#else /* !__CRT_HAVE_chdir && !__CRT_HAVE__chdir && !__CRT_HAVE___chdir && !__CRT_HAVE___libc_chdir */
			case __POSIX_SPAWN_ACTION_CHDIR: {
				/* Change direction using `chdir(2)' */
				int __error;
				__error = (__NAMESPACE_LOCAL_SYM __localdep_chdir)(__act->__sa_action.__sa_chdir_action.__sa_path);
				if __unlikely(__error != 0)
					goto __child_error;
			}	break;
#endif /* __CRT_HAVE_chdir || __CRT_HAVE__chdir || __CRT_HAVE___chdir || __CRT_HAVE___libc_chdir */


#if !defined(__CRT_HAVE_fchdir) && !defined(__CRT_HAVE___fchdir) && !defined(__CRT_HAVE___libc_fchdir)
#define __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION 1
#else /* !__CRT_HAVE_fchdir && !__CRT_HAVE___fchdir && !__CRT_HAVE___libc_fchdir */
			case __POSIX_SPAWN_ACTION_FCHDIR: {
				/* Change direction using `fchdir(2)' */
				int __error;
				__error = (__NAMESPACE_LOCAL_SYM __localdep_fchdir)(__act->__sa_action.__sa_fchdir_action.__sa_fd);
				if __unlikely(__error != 0)
					goto __child_error;
			}	break;
#endif /* __CRT_HAVE_fchdir || __CRT_HAVE___fchdir || __CRT_HAVE___libc_fchdir */


#ifdef __POSIX_SPAWN_ACTION_TCSETPGRP
#ifndef __CRT_HAVE_tcsetpgrp
#define __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION 1
#else /* !__CRT_HAVE_tcsetpgrp */
			case __POSIX_SPAWN_ACTION_TCSETPGRP:
				/* NOTE: Passing `0' as second argument to `tcsetpgrp()' is the same as `getpid()' */
				if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_tcsetpgrp)(__act->__sa_action.__sa_tcsetpgrp_action.__sa_fd, 0))
					goto __child_error;
				break;
#endif /* __CRT_HAVE_tcsetpgrp */
#endif /* __POSIX_SPAWN_ACTION_TCSETPGRP */


#ifdef __POSIX_SPAWN_ACTION_CLOSEFROM
#if !defined(__CRT_HAVE_closefrom) && ((!defined(__CRT_HAVE_fcntl) && !defined(__CRT_HAVE___fcntl) && !defined(__CRT_HAVE___libc_fcntl)) || !defined(__F_CLOSEM)) && !defined(__CRT_HAVE_close_range)
#define __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION 1
#else /* !__CRT_HAVE_closefrom && ((!__CRT_HAVE_fcntl && !__CRT_HAVE___fcntl && !__CRT_HAVE___libc_fcntl) || !__F_CLOSEM) && !__CRT_HAVE_close_range */
			case __POSIX_SPAWN_ACTION_CLOSEFROM:
				(__NAMESPACE_LOCAL_SYM __localdep_closefrom)(__act->__sa_action.__sa_closefrom_action.__sa_fd);
				break;
#endif /* __CRT_HAVE_closefrom || ((__CRT_HAVE_fcntl || __CRT_HAVE___fcntl || __CRT_HAVE___libc_fcntl) && __F_CLOSEM) || __CRT_HAVE_close_range */
#endif /* __POSIX_SPAWN_ACTION_CLOSEFROM */


#ifdef __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION
#undef __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION
			default:
#ifdef __ENOSYS
				(void)__libc_seterrno(__ENOSYS);
#elif defined(__EPERM)
				(void)__libc_seterrno(__EPERM);
#else /* ... */
				(void)__libc_seterrno(1);
#endif /* !... */
				goto __child_error;
#else /* __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION */
			default:
				__builtin_unreachable();
#endif /* !__POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION */
			}
		}
	}
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("__actions")
#pragma pop_macro("__used")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
	if (__attrp) {
		if (__attrp->__flags & __POSIX_SPAWN_RESETIDS) {
#if (defined(__CRT_HAVE_seteuid) && (defined(__CRT_HAVE_getuid) || defined(__CRT_HAVE___getuid) || defined(__CRT_HAVE___libc_getuid))) || (defined(__CRT_HAVE_setegid) && (defined(__CRT_HAVE_getgid) || defined(__CRT_HAVE___getgid) || defined(__CRT_HAVE___libc_getgid)))
#if defined(__CRT_HAVE_seteuid) && (defined(__CRT_HAVE_getuid) || defined(__CRT_HAVE___getuid) || defined(__CRT_HAVE___libc_getuid))
			if ((__NAMESPACE_LOCAL_SYM __localdep_seteuid)((__NAMESPACE_LOCAL_SYM __localdep_getuid)()))
				goto __child_error;
#endif /* __CRT_HAVE_seteuid && (__CRT_HAVE_getuid || __CRT_HAVE___getuid || __CRT_HAVE___libc_getuid) */
#if defined(__CRT_HAVE_setegid) && (defined(__CRT_HAVE_getgid) || defined(__CRT_HAVE___getgid) || defined(__CRT_HAVE___libc_getgid))
			if ((__NAMESPACE_LOCAL_SYM __localdep_setegid)((__NAMESPACE_LOCAL_SYM __localdep_getgid)()))
				goto __child_error;
#endif /* __CRT_HAVE_setegid && (__CRT_HAVE_getgid || __CRT_HAVE___getgid || __CRT_HAVE___libc_getgid) */
#else /* (__CRT_HAVE_seteuid && (__CRT_HAVE_getuid || __CRT_HAVE___getuid || __CRT_HAVE___libc_getuid)) || (__CRT_HAVE_setegid && (__CRT_HAVE_getgid || __CRT_HAVE___getgid || __CRT_HAVE___libc_getgid)) */
#ifdef __ENOSYS
			(void)__libc_seterrno(__ENOSYS);
#elif defined(__EPERM)
			(void)__libc_seterrno(__EPERM);
#else /* ... */
			(void)__libc_seterrno(1);
#endif /* !... */
			goto __child_error;
#endif /* (!__CRT_HAVE_seteuid || (!__CRT_HAVE_getuid && !__CRT_HAVE___getuid && !__CRT_HAVE___libc_getuid)) && (!__CRT_HAVE_setegid || (!__CRT_HAVE_getgid && !__CRT_HAVE___getgid && !__CRT_HAVE___libc_getgid)) */
		}
		if (__attrp->__flags & __POSIX_SPAWN_SETPGROUP) {
#if defined(__CRT_HAVE_setpgid) || defined(__CRT_HAVE___setpgid) || defined(__CRT_HAVE___libc_setpgid)
			/* HINT: Passing `0' as first argument is the same as passing `getpid()'! */
			if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_setpgid)(0, __attrp->__pgrp))
				goto __child_error;
#else /* __CRT_HAVE_setpgid || __CRT_HAVE___setpgid || __CRT_HAVE___libc_setpgid */
#ifdef __ENOSYS
			(void)__libc_seterrno(__ENOSYS);
#elif defined(__EPERM)
			(void)__libc_seterrno(__EPERM);
#else /* ... */
			(void)__libc_seterrno(1);
#endif /* !... */
			goto __child_error;
#endif /* !__CRT_HAVE_setpgid && !__CRT_HAVE___setpgid && !__CRT_HAVE___libc_setpgid */
		}
		if (__attrp->__flags & __POSIX_SPAWN_SETSIGDEF) {
#if (defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction)) && defined(__SIG_DFL)
			__signo_t __i;
			struct sigaction __sa;
			__sa.sa_handler = (__sighandler_t)__SIG_DFL;
			__sa.sa_flags   = 0;
			(__NAMESPACE_LOCAL_SYM __localdep_sigemptyset)(&__sa.sa_mask);
			for (__i = 0; (unsigned int)__i < (unsigned int)(sizeof(__attrp->__sd) / 8); ++__i) {
				if (!(__NAMESPACE_LOCAL_SYM __localdep_sigismember)(&__attrp->__sd, __i))
					continue;
				if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_sigaction)(__i, &__sa, __NULLPTR))
					goto __child_error;
			}
#else /* (__CRT_HAVE_sigaction || __CRT_HAVE___sigaction) && __SIG_DFL */
#ifdef __ENOSYS
			(void)__libc_seterrno(__ENOSYS);
#elif defined(__EPERM)
			(void)__libc_seterrno(__EPERM);
#else /* ... */
			(void)__libc_seterrno(1);
#endif /* !... */
			goto __child_error;
#endif /* (!__CRT_HAVE_sigaction && !__CRT_HAVE___sigaction) || !__SIG_DFL */
		}
		if (__attrp->__flags & __POSIX_SPAWN_SETSIGMASK) {
#if (defined(__CRT_HAVE_sigprocmask) || defined(__CRT_HAVE___sigprocmask) || defined(__CRT_HAVE___libc_sigprocmask) || defined(__CRT_HAVE_pthread_sigmask) || defined(__CRT_HAVE_thr_sigsetmask)) && defined(__SIG_SETMASK)
			if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_sigprocmask)(__SIG_SETMASK, &__attrp->__ss, __NULLPTR))
				goto __child_error;
#else /* (__CRT_HAVE_sigprocmask || __CRT_HAVE___sigprocmask || __CRT_HAVE___libc_sigprocmask || __CRT_HAVE_pthread_sigmask || __CRT_HAVE_thr_sigsetmask) && __SIG_SETMASK */
#ifdef __ENOSYS
			(void)__libc_seterrno(__ENOSYS);
#elif defined(__EPERM)
			(void)__libc_seterrno(__EPERM);
#else /* ... */
			(void)__libc_seterrno(1);
#endif /* !... */
			goto __child_error;
#endif /* (!__CRT_HAVE_sigprocmask && !__CRT_HAVE___sigprocmask && !__CRT_HAVE___libc_sigprocmask && !__CRT_HAVE_pthread_sigmask && !__CRT_HAVE_thr_sigsetmask) || !__SIG_SETMASK */
		}
		if (__attrp->__flags & (__POSIX_SPAWN_SETSCHEDPARAM | __POSIX_SPAWN_SETSCHEDULER)) {
#if (defined(__CRT_HAVE_sched_setscheduler) || defined(__CRT_HAVE___sched_setscheduler) || defined(__CRT_HAVE___libc_sched_setscheduler)) && (defined(__CRT_HAVE_sched_setparam) || defined(__CRT_HAVE___sched_setparam) || defined(__CRT_HAVE___libc_sched_setparam)) && (defined(__CRT_HAVE_sched_getparam) || defined(__CRT_HAVE___sched_getparam) || defined(__CRT_HAVE___libc_sched_getparam))
			int __error;
			if ((__attrp->__flags & (__POSIX_SPAWN_SETSCHEDPARAM | __POSIX_SPAWN_SETSCHEDULER)) ==
			    /*               */ (__POSIX_SPAWN_SETSCHEDPARAM | __POSIX_SPAWN_SETSCHEDULER)) {
				__error = (__NAMESPACE_LOCAL_SYM __localdep_sched_setscheduler)(0, __attrp->__policy, &__attrp->__sp);
			} else if (__attrp->__flags & __POSIX_SPAWN_SETSCHEDPARAM) {
				__error = (__NAMESPACE_LOCAL_SYM __localdep_sched_setparam)(0, &__attrp->__sp);
			} else {
				struct sched_param __param;
				__error = (__NAMESPACE_LOCAL_SYM __localdep_sched_getparam)(0, &__param);
				if __likely(__error == 0)
					__error = (__NAMESPACE_LOCAL_SYM __localdep_sched_setscheduler)(0, __attrp->__policy, &__param);
			}
			if __unlikely(__error)
				goto __child_error;
#else /* (__CRT_HAVE_sched_setscheduler || __CRT_HAVE___sched_setscheduler || __CRT_HAVE___libc_sched_setscheduler) && (__CRT_HAVE_sched_setparam || __CRT_HAVE___sched_setparam || __CRT_HAVE___libc_sched_setparam) && (__CRT_HAVE_sched_getparam || __CRT_HAVE___sched_getparam || __CRT_HAVE___libc_sched_getparam) */
#ifdef __ENOSYS
			(void)__libc_seterrno(__ENOSYS);
#elif defined(__EPERM)
			(void)__libc_seterrno(__EPERM);
#else /* ... */
			(void)__libc_seterrno(1);
#endif /* !... */
			goto __child_error;
#endif /* (!__CRT_HAVE_sched_setscheduler && !__CRT_HAVE___sched_setscheduler && !__CRT_HAVE___libc_sched_setscheduler) || (!__CRT_HAVE_sched_setparam && !__CRT_HAVE___sched_setparam && !__CRT_HAVE___libc_sched_setparam) || (!__CRT_HAVE_sched_getparam && !__CRT_HAVE___sched_getparam && !__CRT_HAVE___libc_sched_getparam) */
		}
	}
	/* When the exec succeeds, the pipe is auto-
	 * closed because it's marked as  O_CLOEXEC! */
	(__NAMESPACE_LOCAL_SYM __localdep_fexecve)(__execfd, ___argv, ___envp);
#ifdef __POSIX_SPAWN_NOEXECERR
	if (__attrp && __attrp->__flags & __POSIX_SPAWN_NOEXECERR) {
		/* Suppress the exec error. */
#if defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))
		(void)__libc_seterrno(0);
#endif /* __ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork) */
	} else
#endif /* __POSIX_SPAWN_NOEXECERR */
	{
__child_error:
#if defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))
		/* If the exec fails, it will have modified `errno' to indicate this fact.
		 * And since we're sharing VMs with  our parent process, the error  reason
		 * will have already  been written  back to  our parent's  VM, so  there's
		 * actually nothing left for us to do, but to simply exit! */
		;
#else /* __ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork) */
		/* Write the exec-error back to our parent. */
#ifdef __ENOENT
		__error = __libc_geterrno_or(__ENOENT);
#else /* __ENOENT */
		__error = __libc_geterrno_or(1);
#endif /* !__ENOENT */
		/* Communicate back why this failed. */
		(__NAMESPACE_LOCAL_SYM __localdep_write)(__pipes[1], &__error, sizeof(__error));
		/* No need to close the pipe, it's auto-closed by the kernel! */
#endif /* !__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork) */
	}
	(__NAMESPACE_LOCAL_SYM __localdep__Exit)(127);
#else /* __POSIX_SPAWN_USE_KOS && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close))) && __CRT_HAVE_fexecve && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid) */
#if __SIZEOF_INT__ == 4
	char __buf[__COMPILER_LNEOF("/proc/self/fd/-2147483648")];
#elif __SIZEOF_INT__ == 8
	char __buf[__COMPILER_LNEOF("/proc/self/fd/-9223372036854775808")];
#elif __SIZEOF_INT__ == 2
	char __buf[__COMPILER_LNEOF("/proc/self/fd/-32768")];
#else /* ... */
	char __buf[__COMPILER_LNEOF("/proc/self/fd/-128")];
#endif /* !... */
	(__NAMESPACE_LOCAL_SYM __localdep_sprintf)(__buf, "/proc/self/fd/%d", __execfd);
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_posix_spawn)(__pid, __buf, __file_actions, __attrp, ___argv, ___envp);
#endif /* !__POSIX_SPAWN_USE_KOS || ((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork && !__CRT_HAVE___libc_fork) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE___libc_pipe && !__CRT_HAVE__pipe) || !__O_CLOEXEC || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write && !__CRT_HAVE___libc_write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close && !__CRT_HAVE___libc_close))) || !__CRT_HAVE_fexecve || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_posix_fspawn_np_defined
#define __local___localdep_posix_fspawn_np_defined
#define __localdep_posix_fspawn_np __LIBC_LOCAL_NAME(posix_fspawn_np)
#endif /* !__local___localdep_posix_fspawn_np_defined */
#else /* (__POSIX_SPAWN_USE_KOS && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close))) && __CRT_HAVE_fexecve && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid)) || (__OS_HAVE_PROCFS_SELF_FD && __CRT_HAVE_posix_spawn) */
#undef __local_posix_fspawn_np_defined
#endif /* (!__POSIX_SPAWN_USE_KOS || ((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork && !__CRT_HAVE___libc_fork) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE___libc_pipe && !__CRT_HAVE__pipe) || !__O_CLOEXEC || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write && !__CRT_HAVE___libc_write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close && !__CRT_HAVE___libc_close))) || !__CRT_HAVE_fexecve || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid)) && (!__OS_HAVE_PROCFS_SELF_FD || !__CRT_HAVE_posix_spawn) */
#endif /* !__local_posix_fspawn_np_defined */
