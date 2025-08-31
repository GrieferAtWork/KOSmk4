/* HASH CRC-32:0x1d3379c1 */
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
#ifndef __local_posix_spawn_child_defined
#define __local_posix_spawn_child_defined
#include <__crt.h>
#include <asm/crt/posix_spawn.h>
#ifdef __POSIX_SPAWN_USE_KOS
#include <bits/crt/posix_spawn.h>
#include <bits/types.h>
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
#ifndef __local___localdep_chdir_defined
#define __local___localdep_chdir_defined
#ifdef __CRT_HAVE_chdir
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_chdir,(char const *__path),chdir,(__path))
#elif defined(__CRT_HAVE__chdir)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_chdir,(char const *__path),_chdir,(__path))
#elif defined(__CRT_HAVE___chdir)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_chdir,(char const *__path),__chdir,(__path))
#elif defined(__CRT_HAVE___libc_chdir)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_chdir,(char const *__path),__libc_chdir,(__path))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <asm/os/fcntl.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_fchdirat)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/chdir.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_chdir __LIBC_LOCAL_NAME(chdir)
#else /* __AT_FDCWD && __CRT_HAVE_fchdirat */
#undef __local___localdep_chdir_defined
#endif /* !__AT_FDCWD || !__CRT_HAVE_fchdirat */
#endif /* !... */
#endif /* !__local___localdep_chdir_defined */
#ifndef __local___localdep_close_defined
#define __local___localdep_close_defined
#ifdef __CRT_HAVE_close
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),close,(__fd))
#elif defined(__CRT_HAVE__close)
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),_close,(__fd))
#elif defined(__CRT_HAVE___close)
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__close,(__fd))
#elif defined(__CRT_HAVE___libc_close)
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__libc_close,(__fd))
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
#ifndef __local___localdep_dup2_defined
#define __local___localdep_dup2_defined
#ifdef __CRT_HAVE_dup2
__CREDIRECT(__ATTR_FDARG(1),__fd_t,__NOTHROW_NCX,__localdep_dup2,(__fd_t __oldfd, __fd_t __newfd),dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE__dup2)
__CREDIRECT(__ATTR_FDARG(1),__fd_t,__NOTHROW_NCX,__localdep_dup2,(__fd_t __oldfd, __fd_t __newfd),_dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE___dup2)
__CREDIRECT(__ATTR_FDARG(1),__fd_t,__NOTHROW_NCX,__localdep_dup2,(__fd_t __oldfd, __fd_t __newfd),__dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE___libc_dup2)
__CREDIRECT(__ATTR_FDARG(1),__fd_t,__NOTHROW_NCX,__localdep_dup2,(__fd_t __oldfd, __fd_t __newfd),__libc_dup2,(__oldfd,__newfd))
#else /* ... */
#undef __local___localdep_dup2_defined
#endif /* !... */
#endif /* !__local___localdep_dup2_defined */
#ifndef __local___localdep_execve_defined
#define __local___localdep_execve_defined
#if __has_builtin(__builtin_execve) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execve)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_RPC,__localdep_execve,(char const *__restrict __path, __TARGV, __TENVP),execve,{ return __builtin_execve(__path, (char *const *)___argv, (char *const *)___envp); })
#elif defined(__CRT_HAVE_execve)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_RPC,__localdep_execve,(char const *__restrict __path, __TARGV, __TENVP),execve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE__execve)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_RPC,__localdep_execve,(char const *__restrict __path, __TARGV, __TENVP),_execve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE___execve)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_RPC,__localdep_execve,(char const *__restrict __path, __TARGV, __TENVP),__execve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE___libc_execve)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_RPC,__localdep_execve,(char const *__restrict __path, __TARGV, __TENVP),__libc_execve,(__path,___argv,___envp))
#else /* ... */
#undef __local___localdep_execve_defined
#endif /* !... */
#endif /* !__local___localdep_execve_defined */
#ifndef __local___localdep_execvpe_defined
#define __local___localdep_execvpe_defined
#ifdef __CRT_HAVE_execvpe
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_RPC,__localdep_execvpe,(char const *__restrict __file, __TARGV, __TENVP),execvpe,(__file,___argv,___envp))
#elif defined(__CRT_HAVE__execvpe)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_RPC,__localdep_execvpe,(char const *__restrict __file, __TARGV, __TENVP),_execvpe,(__file,___argv,___envp))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <hybrid/__alloca.h>
#include <libc/template/environ.h>
__NAMESPACE_LOCAL_BEGIN
#if (defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__hybrid_alloca)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/execvpe.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_execvpe __LIBC_LOCAL_NAME(execvpe)
#else /* (__CRT_HAVE_getenv || __LOCAL_environ) && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) && __hybrid_alloca */
#undef __local___localdep_execvpe_defined
#endif /* (!__CRT_HAVE_getenv && !__LOCAL_environ) || (!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve) || !__hybrid_alloca */
#endif /* !... */
#endif /* !__local___localdep_execvpe_defined */
#ifndef __local___localdep_fchdir_defined
#define __local___localdep_fchdir_defined
#ifdef __CRT_HAVE_fchdir
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_RPC,__localdep_fchdir,(__fd_t __fd),fchdir,(__fd))
#elif defined(__CRT_HAVE___fchdir)
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_RPC,__localdep_fchdir,(__fd_t __fd),__fchdir,(__fd))
#elif defined(__CRT_HAVE___libc_fchdir)
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_RPC,__localdep_fchdir,(__fd_t __fd),__libc_fchdir,(__fd))
#else /* ... */
#undef __local___localdep_fchdir_defined
#endif /* !... */
#endif /* !__local___localdep_fchdir_defined */
#ifndef __local___localdep_fexecve_defined
#define __local___localdep_fexecve_defined
#ifdef __CRT_HAVE_fexecve
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDREAD(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_RPC,__localdep_fexecve,(__fd_t __execfd, __TARGV, __TENVP),fexecve,(__execfd,___argv,___envp))
#else /* __CRT_HAVE_fexecve */
__NAMESPACE_LOCAL_END
#include <asm/os/features.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve))
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/fexecve.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fexecve __LIBC_LOCAL_NAME(fexecve)
#else /* __OS_HAVE_PROCFS_SELF_FD && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) */
#undef __local___localdep_fexecve_defined
#endif /* !__OS_HAVE_PROCFS_SELF_FD || (!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve) */
#endif /* !__CRT_HAVE_fexecve */
#endif /* !__local___localdep_fexecve_defined */
#ifndef __local___localdep_getgid_defined
#define __local___localdep_getgid_defined
#ifdef __CRT_HAVE_getgid
__CREDIRECT(__ATTR_WUNUSED,__gid_t,__NOTHROW_NCX,__localdep_getgid,(void),getgid,())
#elif defined(__CRT_HAVE___getgid)
__CREDIRECT(__ATTR_WUNUSED,__gid_t,__NOTHROW_NCX,__localdep_getgid,(void),__getgid,())
#elif defined(__CRT_HAVE___libc_getgid)
__CREDIRECT(__ATTR_WUNUSED,__gid_t,__NOTHROW_NCX,__localdep_getgid,(void),__libc_getgid,())
#elif defined(__CRT_HAVE_getresgid)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/getgid.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_getgid __LIBC_LOCAL_NAME(getgid)
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
#elif defined(__CRT_HAVE_getresuid)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/getuid.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_getuid __LIBC_LOCAL_NAME(getuid)
#else /* ... */
#undef __local___localdep_getuid_defined
#endif /* !... */
#endif /* !__local___localdep_getuid_defined */
#ifndef __local___localdep_open_defined
#define __local___localdep_open_defined
__NAMESPACE_LOCAL_END
#include <features.h>
#include <asm/os/oflags.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___libc_open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__libc_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__open64,(__filename,__oflags),__oflags,1,(__mode_t))
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
#ifndef __local___localdep_sched_getparam_defined
#define __local___localdep_sched_getparam_defined
#ifdef __CRT_HAVE_sched_getparam
__NAMESPACE_LOCAL_END
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_sched_getparam,(__pid_t __pid, struct sched_param *__param),sched_getparam,(__pid,__param))
#elif defined(__CRT_HAVE___sched_getparam)
__NAMESPACE_LOCAL_END
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_sched_getparam,(__pid_t __pid, struct sched_param *__param),__sched_getparam,(__pid,__param))
#elif defined(__CRT_HAVE___libc_sched_getparam)
__NAMESPACE_LOCAL_END
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_sched_getparam,(__pid_t __pid, struct sched_param *__param),__libc_sched_getparam,(__pid,__param))
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
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_NCX,__localdep_sched_setparam,(__pid_t __pid, struct sched_param const *__param),sched_setparam,(__pid,__param))
#elif defined(__CRT_HAVE___sched_setparam)
__NAMESPACE_LOCAL_END
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_NCX,__localdep_sched_setparam,(__pid_t __pid, struct sched_param const *__param),__sched_setparam,(__pid,__param))
#elif defined(__CRT_HAVE___libc_sched_setparam)
__NAMESPACE_LOCAL_END
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_NCX,__localdep_sched_setparam,(__pid_t __pid, struct sched_param const *__param),__libc_sched_setparam,(__pid,__param))
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
__CREDIRECT(__ATTR_IN(3),int,__NOTHROW_NCX,__localdep_sched_setscheduler,(__pid_t __pid, int __policy, struct sched_param const *__param),sched_setscheduler,(__pid,__policy,__param))
#elif defined(__CRT_HAVE___sched_setscheduler)
__NAMESPACE_LOCAL_END
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(3),int,__NOTHROW_NCX,__localdep_sched_setscheduler,(__pid_t __pid, int __policy, struct sched_param const *__param),__sched_setscheduler,(__pid,__policy,__param))
#elif defined(__CRT_HAVE___libc_sched_setscheduler)
__NAMESPACE_LOCAL_END
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(3),int,__NOTHROW_NCX,__localdep_sched_setscheduler,(__pid_t __pid, int __policy, struct sched_param const *__param),__libc_sched_setscheduler,(__pid,__policy,__param))
#else /* ... */
#undef __local___localdep_sched_setscheduler_defined
#endif /* !... */
#endif /* !__local___localdep_sched_setscheduler_defined */
#ifndef __local___localdep_setegid_defined
#define __local___localdep_setegid_defined
#ifdef __CRT_HAVE_setegid
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_setegid,(__gid_t __egid),setegid,(__egid))
#elif defined(__CRT_HAVE_setregid) || defined(__CRT_HAVE___setregid) || defined(__CRT_HAVE___libc_setregid) || defined(__CRT_HAVE_setresgid)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/setegid.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_setegid __LIBC_LOCAL_NAME(setegid)
#else /* ... */
#undef __local___localdep_setegid_defined
#endif /* !... */
#endif /* !__local___localdep_setegid_defined */
#ifndef __local___localdep_seteuid_defined
#define __local___localdep_seteuid_defined
#ifdef __CRT_HAVE_seteuid
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_seteuid,(__uid_t __euid),seteuid,(__euid))
#elif defined(__CRT_HAVE_setreuid) || defined(__CRT_HAVE___setreuid) || defined(__CRT_HAVE___libc_setreuid) || defined(__CRT_HAVE_setresuid)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/seteuid.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_seteuid __LIBC_LOCAL_NAME(seteuid)
#else /* ... */
#undef __local___localdep_seteuid_defined
#endif /* !... */
#endif /* !__local___localdep_seteuid_defined */
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
#ifndef __local___localdep_setsid_defined
#define __local___localdep_setsid_defined
#ifdef __CRT_HAVE_setsid
__CREDIRECT(,__pid_t,__NOTHROW_NCX,__localdep_setsid,(void),setsid,())
#elif defined(__CRT_HAVE___setsid)
__CREDIRECT(,__pid_t,__NOTHROW_NCX,__localdep_setsid,(void),__setsid,())
#elif defined(__CRT_HAVE___libc_setsid)
__CREDIRECT(,__pid_t,__NOTHROW_NCX,__localdep_setsid,(void),__libc_setsid,())
#else /* ... */
#undef __local___localdep_setsid_defined
#endif /* !... */
#endif /* !__local___localdep_setsid_defined */
#ifndef __local___localdep_sigaction_defined
#define __local___localdep_sigaction_defined
#ifdef __CRT_HAVE_sigaction
__NAMESPACE_LOCAL_END
struct sigaction;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_sigaction,(__signo_t __signo, struct sigaction const *__act, struct sigaction *__oact),sigaction,(__signo,__act,__oact))
#elif defined(__CRT_HAVE___sigaction)
__NAMESPACE_LOCAL_END
struct sigaction;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_sigaction,(__signo_t __signo, struct sigaction const *__act, struct sigaction *__oact),__sigaction,(__signo,__act,__oact))
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
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,__localdep_sigemptyset,(struct __sigset_struct *__set),sigemptyset,(__set))
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
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,__localdep_sigismember,(struct __sigset_struct const *__set, __signo_t __signo),sigismember,{ __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); return (__set->__val[__word] & __mask) __PRIVATE_SIGSET_ISMEMBER_EXT; })
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
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,__localdep_sigismember,(struct __sigset_struct const *__set, __signo_t __signo),__sigismember,{ __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); return (__set->__val[__word] & __mask) __PRIVATE_SIGSET_ISMEMBER_EXT; })
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
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL __localdep_sigismember)(struct __sigset_struct const *__set, __signo_t __signo) { __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); return (__set->__val[__word] & __mask) __PRIVATE_SIGSET_ISMEMBER_EXT; }
#endif /* !... */
#endif /* !__local___localdep_sigismember_defined */
#ifndef __local___localdep_sigprocmask_defined
#define __local___localdep_sigprocmask_defined
#ifdef __CRT_HAVE_sigprocmask
__NAMESPACE_LOCAL_END
struct __sigset_struct;
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),sigprocmask,(__how,__set,__oset))
#elif defined(__CRT_HAVE___sigprocmask)
__NAMESPACE_LOCAL_END
struct __sigset_struct;
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),__sigprocmask,(__how,__set,__oset))
#elif defined(__CRT_HAVE___libc_sigprocmask)
__NAMESPACE_LOCAL_END
struct __sigset_struct;
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),__libc_sigprocmask,(__how,__set,__oset))
#elif defined(__CRT_HAVE_pthread_sigmask)
__NAMESPACE_LOCAL_END
struct __sigset_struct;
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),pthread_sigmask,(__how,__set,__oset))
#elif defined(__CRT_HAVE_thr_sigsetmask)
__NAMESPACE_LOCAL_END
struct __sigset_struct;
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),thr_sigsetmask,(__how,__set,__oset))
#else /* ... */
#undef __local___localdep_sigprocmask_defined
#endif /* !... */
#endif /* !__local___localdep_sigprocmask_defined */
#ifndef __local___localdep_tcsetpgrp_defined
#define __local___localdep_tcsetpgrp_defined
#ifdef __CRT_HAVE_tcsetpgrp
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_tcsetpgrp,(__fd_t __fd, __pid_t __pgrp_id),tcsetpgrp,(__fd,__pgrp_id))
#else /* __CRT_HAVE_tcsetpgrp */
__NAMESPACE_LOCAL_END
#include <asm/os/tty.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#if (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl) || defined(__CRT_HAVE___ioctl_time64)) && defined(__TIOCSPGRP)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/tcsetpgrp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tcsetpgrp __LIBC_LOCAL_NAME(tcsetpgrp)
#else /* (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl || __CRT_HAVE___ioctl_time64) && __TIOCSPGRP */
#undef __local___localdep_tcsetpgrp_defined
#endif /* (!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl && !__CRT_HAVE___ioctl_time64) || !__TIOCSPGRP */
#endif /* !__CRT_HAVE_tcsetpgrp */
#endif /* !__local___localdep_tcsetpgrp_defined */
__NAMESPACE_LOCAL_END
#include <bits/os/sigaction.h>
#include <libc/errno.h>
#include <hybrid/typecore.h>
#include <asm/os/oflags.h>
#include <asm/os/signal.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(posix_spawn_child) __ATTR_IN(5) __ATTR_IN(6) __ATTR_IN_OPT(3) __ATTR_IN_OPT(4) __errno_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(posix_spawn_child))(unsigned int __exec_type, void *__exec_arg, struct __posix_spawn_file_actions const *__file_actions, struct __posix_spawnattr const *__attrp, __TARGV, __TENVP) {

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
					goto __err_errno;
				break;
#endif /* __CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close */


#if !defined(__CRT_HAVE_dup2) && !defined(__CRT_HAVE__dup2) && !defined(__CRT_HAVE___dup2) && !defined(__CRT_HAVE___libc_dup2)
#define __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION
#else /* !__CRT_HAVE_dup2 && !__CRT_HAVE__dup2 && !__CRT_HAVE___dup2 && !__CRT_HAVE___libc_dup2 */
			case __POSIX_SPAWN_ACTION_DUP2:
				/* Duplicate a file handle */
				if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_dup2)(__act->__sa_action.__sa_dup2_action.__sa_oldfd,
				                 __act->__sa_action.__sa_dup2_action.__sa_newfd))
					goto __err_errno;
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
					goto __err_errno;
				if __likely(__tempfd != __act->__sa_action.__sa_open_action.__sa_fd) {
					if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_dup2)(__tempfd, __act->__sa_action.__sa_open_action.__sa_fd))
						goto __err_errno;
					(void)(__NAMESPACE_LOCAL_SYM __localdep_close)(__tempfd);
				}
			}	break;
#endif /* (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_dup2 || __CRT_HAVE__dup2 || __CRT_HAVE___dup2 || __CRT_HAVE___libc_dup2) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close) */


#ifdef __POSIX_SPAWN_ACTION_CHDIR
#if !defined(__CRT_HAVE_chdir) && !defined(__CRT_HAVE__chdir) && !defined(__CRT_HAVE___chdir) && !defined(__CRT_HAVE___libc_chdir) && (!defined(__AT_FDCWD) || !defined(__CRT_HAVE_fchdirat))
#define __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION 1
#else /* !__CRT_HAVE_chdir && !__CRT_HAVE__chdir && !__CRT_HAVE___chdir && !__CRT_HAVE___libc_chdir && (!__AT_FDCWD || !__CRT_HAVE_fchdirat) */
			case __POSIX_SPAWN_ACTION_CHDIR: {
				/* Change direction using `chdir(2)' */
				if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_chdir)(__act->__sa_action.__sa_chdir_action.__sa_path))
					goto __err_errno;
			}	break;
#endif /* __CRT_HAVE_chdir || __CRT_HAVE__chdir || __CRT_HAVE___chdir || __CRT_HAVE___libc_chdir || (__AT_FDCWD && __CRT_HAVE_fchdirat) */
#endif /* __POSIX_SPAWN_ACTION_CHDIR */


#ifdef __POSIX_SPAWN_ACTION_FCHDIR
#if !defined(__CRT_HAVE_fchdir) && !defined(__CRT_HAVE___fchdir) && !defined(__CRT_HAVE___libc_fchdir)
#define __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION 1
#else /* !__CRT_HAVE_fchdir && !__CRT_HAVE___fchdir && !__CRT_HAVE___libc_fchdir */
			case __POSIX_SPAWN_ACTION_FCHDIR: {
				/* Change direction using `fchdir(2)' */
				if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_fchdir)(__act->__sa_action.__sa_fchdir_action.__sa_fd))
					goto __err_errno;
			}	break;
#endif /* __CRT_HAVE_fchdir || __CRT_HAVE___fchdir || __CRT_HAVE___libc_fchdir */
#endif /* __POSIX_SPAWN_ACTION_FCHDIR */


#ifdef __POSIX_SPAWN_ACTION_TCSETPGRP
#if !defined(__CRT_HAVE_tcsetpgrp) && ((!defined(__CRT_HAVE_ioctl) && !defined(__CRT_HAVE___ioctl) && !defined(__CRT_HAVE___libc_ioctl) && !defined(__CRT_HAVE___ioctl_time64)) || !defined(__TIOCSPGRP))
#define __POSIX_SPAWN_HAVE_UNSUPPORTED_FILE_ACTION 1
#else /* !__CRT_HAVE_tcsetpgrp && ((!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl && !__CRT_HAVE___ioctl_time64) || !__TIOCSPGRP) */
			case __POSIX_SPAWN_ACTION_TCSETPGRP:
				/* NOTE: Passing `0' as second argument to `tcsetpgrp()' is the same as `getpid()' */
				if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_tcsetpgrp)(__act->__sa_action.__sa_tcsetpgrp_action.__sa_fd, 0))
					goto __err_errno;
				break;
#endif /* __CRT_HAVE_tcsetpgrp || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl || __CRT_HAVE___ioctl_time64) && __TIOCSPGRP) */
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
				return __ENOSYS;
#elif defined(__EPERM)
				return __EPERM;
#else /* ... */
				return 1;
#endif /* !... */
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
#if ((defined(__CRT_HAVE_seteuid) || defined(__CRT_HAVE_setreuid) || defined(__CRT_HAVE___setreuid) || defined(__CRT_HAVE___libc_setreuid) || defined(__CRT_HAVE_setresuid)) && (defined(__CRT_HAVE_getuid) || defined(__CRT_HAVE___getuid) || defined(__CRT_HAVE___libc_getuid) || defined(__CRT_HAVE_getresuid))) || ((defined(__CRT_HAVE_setegid) || defined(__CRT_HAVE_setregid) || defined(__CRT_HAVE___setregid) || defined(__CRT_HAVE___libc_setregid) || defined(__CRT_HAVE_setresgid)) && (defined(__CRT_HAVE_getgid) || defined(__CRT_HAVE___getgid) || defined(__CRT_HAVE___libc_getgid) || defined(__CRT_HAVE_getresgid)))
#if (defined(__CRT_HAVE_seteuid) || defined(__CRT_HAVE_setreuid) || defined(__CRT_HAVE___setreuid) || defined(__CRT_HAVE___libc_setreuid) || defined(__CRT_HAVE_setresuid)) && (defined(__CRT_HAVE_getuid) || defined(__CRT_HAVE___getuid) || defined(__CRT_HAVE___libc_getuid) || defined(__CRT_HAVE_getresuid))
			if ((__NAMESPACE_LOCAL_SYM __localdep_seteuid)((__NAMESPACE_LOCAL_SYM __localdep_getuid)()))
				goto __err_errno;
#endif /* (__CRT_HAVE_seteuid || __CRT_HAVE_setreuid || __CRT_HAVE___setreuid || __CRT_HAVE___libc_setreuid || __CRT_HAVE_setresuid) && (__CRT_HAVE_getuid || __CRT_HAVE___getuid || __CRT_HAVE___libc_getuid || __CRT_HAVE_getresuid) */
#if (defined(__CRT_HAVE_setegid) || defined(__CRT_HAVE_setregid) || defined(__CRT_HAVE___setregid) || defined(__CRT_HAVE___libc_setregid) || defined(__CRT_HAVE_setresgid)) && (defined(__CRT_HAVE_getgid) || defined(__CRT_HAVE___getgid) || defined(__CRT_HAVE___libc_getgid) || defined(__CRT_HAVE_getresgid))
			if ((__NAMESPACE_LOCAL_SYM __localdep_setegid)((__NAMESPACE_LOCAL_SYM __localdep_getgid)()))
				goto __err_errno;
#endif /* (__CRT_HAVE_setegid || __CRT_HAVE_setregid || __CRT_HAVE___setregid || __CRT_HAVE___libc_setregid || __CRT_HAVE_setresgid) && (__CRT_HAVE_getgid || __CRT_HAVE___getgid || __CRT_HAVE___libc_getgid || __CRT_HAVE_getresgid) */
#else /* ((__CRT_HAVE_seteuid || __CRT_HAVE_setreuid || __CRT_HAVE___setreuid || __CRT_HAVE___libc_setreuid || __CRT_HAVE_setresuid) && (__CRT_HAVE_getuid || __CRT_HAVE___getuid || __CRT_HAVE___libc_getuid || __CRT_HAVE_getresuid)) || ((__CRT_HAVE_setegid || __CRT_HAVE_setregid || __CRT_HAVE___setregid || __CRT_HAVE___libc_setregid || __CRT_HAVE_setresgid) && (__CRT_HAVE_getgid || __CRT_HAVE___getgid || __CRT_HAVE___libc_getgid || __CRT_HAVE_getresgid)) */
#ifdef __ENOSYS
			return __ENOSYS;
#elif defined(__EPERM)
			return __EPERM;
#else /* ... */
			return 1;
#endif /* !... */
#endif /* ((!__CRT_HAVE_seteuid && !__CRT_HAVE_setreuid && !__CRT_HAVE___setreuid && !__CRT_HAVE___libc_setreuid && !__CRT_HAVE_setresuid) || (!__CRT_HAVE_getuid && !__CRT_HAVE___getuid && !__CRT_HAVE___libc_getuid && !__CRT_HAVE_getresuid)) && ((!__CRT_HAVE_setegid && !__CRT_HAVE_setregid && !__CRT_HAVE___setregid && !__CRT_HAVE___libc_setregid && !__CRT_HAVE_setresgid) || (!__CRT_HAVE_getgid && !__CRT_HAVE___getgid && !__CRT_HAVE___libc_getgid && !__CRT_HAVE_getresgid)) */
		}
		if (__attrp->__flags & __POSIX_SPAWN_SETPGROUP) {
#if defined(__CRT_HAVE_setpgid) || defined(__CRT_HAVE___setpgid) || defined(__CRT_HAVE___libc_setpgid)
			/* HINT: Passing `0' as first argument is the same as passing `getpid()'! */
			if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_setpgid)(0, __attrp->__pgrp))
				goto __err_errno;
#else /* __CRT_HAVE_setpgid || __CRT_HAVE___setpgid || __CRT_HAVE___libc_setpgid */
#ifdef __ENOSYS
			return __ENOSYS;
#elif defined(__EPERM)
			return __EPERM;
#else /* ... */
			return 1;
#endif /* !... */
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
					goto __err_errno;
			}
#else /* (__CRT_HAVE_sigaction || __CRT_HAVE___sigaction) && __SIG_DFL */
#ifdef __ENOSYS
			return __ENOSYS;
#elif defined(__EPERM)
			return __EPERM;
#else /* ... */
			return 1;
#endif /* !... */
#endif /* (!__CRT_HAVE_sigaction && !__CRT_HAVE___sigaction) || !__SIG_DFL */
		}
		if (__attrp->__flags & __POSIX_SPAWN_SETSIGMASK) {
#if (defined(__CRT_HAVE_sigprocmask) || defined(__CRT_HAVE___sigprocmask) || defined(__CRT_HAVE___libc_sigprocmask) || defined(__CRT_HAVE_pthread_sigmask) || defined(__CRT_HAVE_thr_sigsetmask)) && defined(__SIG_SETMASK)
			if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_sigprocmask)(__SIG_SETMASK, &__attrp->__ss, __NULLPTR))
				goto __err_errno;
#else /* (__CRT_HAVE_sigprocmask || __CRT_HAVE___sigprocmask || __CRT_HAVE___libc_sigprocmask || __CRT_HAVE_pthread_sigmask || __CRT_HAVE_thr_sigsetmask) && __SIG_SETMASK */
#ifdef __ENOSYS
			return __ENOSYS;
#elif defined(__EPERM)
			return __EPERM;
#else /* ... */
			return 1;
#endif /* !... */
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
				goto __err_errno;
#else /* (__CRT_HAVE_sched_setscheduler || __CRT_HAVE___sched_setscheduler || __CRT_HAVE___libc_sched_setscheduler) && (__CRT_HAVE_sched_setparam || __CRT_HAVE___sched_setparam || __CRT_HAVE___libc_sched_setparam) && (__CRT_HAVE_sched_getparam || __CRT_HAVE___sched_getparam || __CRT_HAVE___libc_sched_getparam) */
#ifdef __ENOSYS
			return __ENOSYS;
#elif defined(__EPERM)
			return __EPERM;
#else /* ... */
			return 1;
#endif /* !... */
#endif /* (!__CRT_HAVE_sched_setscheduler && !__CRT_HAVE___sched_setscheduler && !__CRT_HAVE___libc_sched_setscheduler) || (!__CRT_HAVE_sched_setparam && !__CRT_HAVE___sched_setparam && !__CRT_HAVE___libc_sched_setparam) || (!__CRT_HAVE_sched_getparam && !__CRT_HAVE___sched_getparam && !__CRT_HAVE___libc_sched_getparam) */
		}
#if defined(__POSIX_SPAWN_SETSID) && (defined(__CRT_HAVE_setsid) || defined(__CRT_HAVE___setsid) || defined(__CRT_HAVE___libc_setsid))
		if (__attrp->__flags & __POSIX_SPAWN_SETSID) {
			if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_setsid)() < 0)
				goto __err_errno;
		}
#endif /* __POSIX_SPAWN_SETSID && (__CRT_HAVE_setsid || __CRT_HAVE___setsid || __CRT_HAVE___libc_setsid) */
	}

	switch (__exec_type) {
#if defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)
	case 0:
		(__NAMESPACE_LOCAL_SYM __localdep_execve)((char const *)__exec_arg, ___argv, ___envp);
		break;
#endif /* __CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve */
#if defined(__CRT_HAVE_execvpe) || defined(__CRT_HAVE__execvpe) || ((defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__hybrid_alloca))
	case 1:
		(__NAMESPACE_LOCAL_SYM __localdep_execvpe)((char const *)__exec_arg, ___argv, ___envp);
		break;
#endif /* __CRT_HAVE_execvpe || __CRT_HAVE__execvpe || ((__CRT_HAVE_getenv || __LOCAL_environ) && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) && __hybrid_alloca) */
#if defined(__CRT_HAVE_fexecve) || (defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)))
	case 2:
		(__NAMESPACE_LOCAL_SYM __localdep_fexecve)((__fd_t)(__UINTPTR_TYPE__)__exec_arg, ___argv, ___envp);
		break;
#endif /* __CRT_HAVE_fexecve || (__OS_HAVE_PROCFS_SELF_FD && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve)) */
	case 3: {
		__errno_t __error;
		__error = (*(__errno_t (__LIBCCALL *)(void *))__exec_arg)((void *)___argv);
#ifdef __POSIX_SPAWN_NOEXECERR
		if (__attrp && __attrp->__flags & __POSIX_SPAWN_NOEXECERR)
			__error = 0; /* Suppress the exec error. */
#endif /* __POSIX_SPAWN_NOEXECERR */
		return __error;
	}	break;
	default: __builtin_unreachable();
	}

#ifdef __POSIX_SPAWN_NOEXECERR
	if (__attrp && __attrp->__flags & __POSIX_SPAWN_NOEXECERR)
		return 0; /* Suppress the exec error. */
#endif /* __POSIX_SPAWN_NOEXECERR */

__err_errno:
#ifdef __ENOENT
	return __libc_geterrno_or(__ENOENT);
#else /* __ENOENT */
	return __libc_geterrno_or(1);
#endif /* !__ENOENT */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_posix_spawn_child_defined
#define __local___localdep_posix_spawn_child_defined
#define __localdep_posix_spawn_child __LIBC_LOCAL_NAME(posix_spawn_child)
#endif /* !__local___localdep_posix_spawn_child_defined */
#else /* __POSIX_SPAWN_USE_KOS */
#undef __local_posix_spawn_child_defined
#endif /* !__POSIX_SPAWN_USE_KOS */
#endif /* !__local_posix_spawn_child_defined */
