/* HASH CRC-32:0xb9a57586 */
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
#ifndef _UNISTD_H
#define _UNISTD_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <hybrid/typecore.h>

#include <asm/stdio.h>
#include <bits/confname.h>
#include <bits/posix_opt.h>
#include <bits/types.h>
#include <kos/anno.h>

#if defined(__CRT_GLC) || defined(__CRT_KOS) || defined(__CRT_KOS_KERNEL)
#include <asm/unistd.h>
#endif /* __CRT_GLC || __CRT_KOS || __CRT_KOS_KERNEL */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
#include <bits/environments.h>
#endif /* __USE_UNIX98 || __USE_XOPEN2K */

__SYSDECL_BEGIN

#ifdef __USE_XOPEN2K8
#define _POSIX_VERSION 200809L
#elif defined(__USE_XOPEN2K)
#define _POSIX_VERSION 200112L
#elif defined(__USE_POSIX199506)
#define _POSIX_VERSION 199506L
#elif defined(__USE_POSIX199309)
#define _POSIX_VERSION 199309L
#else /* ... */
#define _POSIX_VERSION 199009L
#endif /* !... */

#ifdef __USE_XOPEN2K8
#define __POSIX2_THIS_VERSION 200809L
#elif defined(__USE_XOPEN2K)
#define __POSIX2_THIS_VERSION 200112L
#elif defined(__USE_POSIX199506)
#define __POSIX2_THIS_VERSION 199506L
#else /* ... */
#define __POSIX2_THIS_VERSION 199209L
#endif /* !... */

#define _POSIX2_VERSION   __POSIX2_THIS_VERSION
#define _POSIX2_C_VERSION __POSIX2_THIS_VERSION
#define _POSIX2_C_BIND    __POSIX2_THIS_VERSION
#define _POSIX2_C_DEV     __POSIX2_THIS_VERSION
#define _POSIX2_SW_DEV    __POSIX2_THIS_VERSION
#define _POSIX2_LOCALEDEF __POSIX2_THIS_VERSION

#ifdef __USE_XOPEN2K8
#define _XOPEN_VERSION 700
#elif defined(__USE_XOPEN2K)
#define _XOPEN_VERSION 600
#elif defined(__USE_UNIX98)
#define _XOPEN_VERSION 500
#else /* ... */
#define _XOPEN_VERSION 4
#endif /* !... */
#define _XOPEN_XCU_VERSION 4
#define _XOPEN_XPG2        1
#define _XOPEN_XPG3        1
#define _XOPEN_XPG4        1
#define _XOPEN_UNIX        1
#define _XOPEN_CRYPT       1
#define _XOPEN_ENH_I18N    1
#define _XOPEN_LEGACY      1

#define STDIN_FILENO  __STDIN_FILENO  /* Standard input. */
#define STDOUT_FILENO __STDOUT_FILENO /* Standard output. */
#define STDERR_FILENO __STDERR_FILENO /* Standard error output. */

#define F_OK __F_OK /* Test for existence. */
#define X_OK __X_OK /* Test for execute permission. */
#define W_OK __W_OK /* Test for write permission. */
#define R_OK __R_OK /* Test for read permission. */

#ifndef SEEK_SET
#define SEEK_SET __SEEK_SET /* Seek from beginning of file. */
#define SEEK_CUR __SEEK_CUR /* Seek from current position. */
#define SEEK_END __SEEK_END /* Seek from end of file. */
#ifdef __USE_GNU
#ifdef __SEEK_DATA
#define SEEK_DATA __SEEK_DATA /* Seek to next data. */
#endif /* __SEEK_DATA */
#ifdef __SEEK_HOLE
#define SEEK_HOLE __SEEK_HOLE /* Seek to next hole. */
#endif /* __SEEK_HOLE */
#endif /* __USE_GNU */
#endif /* !SEEK_SET */

#ifdef __USE_MISC
#ifndef L_SET
#define L_SET  SEEK_SET /* Seek from beginning of file. */
#define L_CURR SEEK_CUR /* Seek from current position. */
#define L_INCR SEEK_CUR /* Seek from current position. */
#define L_XTND SEEK_END /* Seek from end of file. */
#endif /* !L_SET */
#endif /* __USE_MISC */

#ifdef __CC__
#ifndef __ssize_t_defined
#define __ssize_t_defined 1
typedef __ssize_t ssize_t;
#endif /* !__ssize_t_defined */

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#ifndef __gid_t_defined
#define __gid_t_defined 1
typedef __gid_t gid_t;
#endif /* !__gid_t_defined */
#ifndef __uid_t_defined
#define __uid_t_defined 1
typedef __uid_t uid_t;
#endif /* !__uid_t_defined */
#ifndef __off_t_defined
#define __off_t_defined
typedef __typedef_off_t off_t;
#endif /* !__off_t_defined */
#ifndef __useconds_t_defined
#define __useconds_t_defined 1
typedef __useconds_t useconds_t;
#endif /* !__useconds_t_defined */
#ifndef __pid_t_defined
#define __pid_t_defined 1
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */
#ifdef __USE_LARGEFILE64
#ifndef __off64_t_defined
#define __off64_t_defined 1
typedef __off64_t off64_t;
#endif /* !__off64_t_defined */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN || __USE_XOPEN2K */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
#ifndef __intptr_t_defined
#define __intptr_t_defined 1
typedef __intptr_t intptr_t;
#endif /* !__intptr_t_defined */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifndef __socklen_t_defined
#define __socklen_t_defined 1
typedef __socklen_t socklen_t;
#endif /* !__socklen_t_defined */
#endif /* __USE_MISC || __USE_XOPEN */

#ifndef __TARGV
#ifdef __USE_DOS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS */
#endif /* !__TARGV */

#ifndef ____environ_defined
#define ____environ_defined 1
#undef __environ
#if defined(__CRT_HAVE_environ) && !defined(__NO_ASMNAME)
__LIBC char **__environ __ASMNAME("environ");
#elif defined(__CRT_HAVE__environ) && !defined(__NO_ASMNAME)
__LIBC char **__environ __ASMNAME("_environ");
#define __environ __environ
#define __environ __environ
#elif defined(__CRT_HAVE__environ)
#undef _environ
#ifndef ___environ_defined
#define ___environ_defined 1
__LIBC char **_environ;
#endif /* !___environ_defined */
#define __environ _environ
#elif defined(__CRT_HAVE_environ)
#undef environ
#ifndef __environ_defined
#define __environ_defined 1
__LIBC char **environ;
#endif /* !__environ_defined */
#define __environ environ
#elif defined(__CRT_HAVE___p__environ)
#ifndef ____p__environ_defined
#define ____p__environ_defined 1
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,char ***,__NOTHROW,__p__environ,(void),())
#endif /* !____p__environ_defined */
#define __environ (*__p__environ())
#else /* ... */
#undef ____environ_defined
#endif /* !... */
#endif /* !____environ_defined */

#ifndef __execv_defined
#define __execv_defined 1
#if __has_builtin(__builtin_execv) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execv)
/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CEIDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,execv,(char const *__restrict __path, __TARGV),{ return __builtin_execv(__path, (char *const *)___argv); })
#elif defined(__CRT_HAVE_execv)
/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,execv,(char const *__restrict __path, __TARGV),(__path,___argv))
#elif defined(__CRT_HAVE__execv)
/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,execv,(char const *__restrict __path, __TARGV),_execv,(__path,___argv))
#else /* ... */
#undef __execv_defined
#endif /* !... */
#endif /* !__execv_defined */
#ifndef __execve_defined
#define __execve_defined 1
#if __has_builtin(__builtin_execve) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execve)
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CEIDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,execve,(char const *__restrict __path, __TARGV, __TENVP),{ return __builtin_execve(__path, (char *const *)___argv, (char *const *)___envp); })
#elif defined(__CRT_HAVE_execve)
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,execve,(char const *__restrict __path, __TARGV, __TENVP),(__path,___argv,___envp))
#elif defined(__CRT_HAVE__execve)
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,execve,(char const *__restrict __path, __TARGV, __TENVP),_execve,(__path,___argv,___envp))
#else /* ... */
#undef __execve_defined
#endif /* !... */
#endif /* !__execve_defined */
#ifndef __execvp_defined
#define __execvp_defined 1
#if __has_builtin(__builtin_execvp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execvp)
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CEIDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,execvp,(char const *__restrict __file, __TARGV),{ return __builtin_execvp(__file, (char *const *)___argv); })
#elif defined(__CRT_HAVE_execvp)
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,execvp,(char const *__restrict __file, __TARGV),(__file,___argv))
#elif defined(__CRT_HAVE__execvp)
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,execvp,(char const *__restrict __file, __TARGV),_execvp,(__file,___argv))
#else /* ... */
#undef __execvp_defined
#endif /* !... */
#endif /* !__execvp_defined */
#ifndef __execl_defined
#define __execl_defined 1
#if __has_builtin(__builtin_execl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execl) && __has_builtin(__builtin_va_arg_pack)
/* >> execl(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
__CEIDECLARE(__ATTR_SENTINEL __ATTR_NONNULL((1)),int,__NOTHROW_RPC,execl,(char const *__restrict __path, char const *__args, ...),{ return __builtin_execl(__path, __args, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_execl)
/* >> execl(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL execl)(char const *__restrict __path, char const *__args, ...) __CASMNAME_SAME("execl");
#elif defined(__CRT_HAVE__execl)
/* >> execl(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL execl)(char const *__restrict __path, char const *__args, ...) __CASMNAME("_execl");
#elif defined(__CRT_HAVE_execv) || defined(__CRT_HAVE__execv)
#include <local/unistd/execl.h>
/* >> execl(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(execl)
#else /* __cplusplus */
#define execl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execl))
#endif /* !__cplusplus */
#else /* ... */
#undef __execl_defined
#endif /* !... */
#endif /* !__execl_defined */
#ifndef __execle_defined
#define __execle_defined 1
#if __has_builtin(__builtin_execle) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execle) && __has_builtin(__builtin_va_arg_pack)
/* >> execle(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
__CEIDECLARE(__ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)),int,__NOTHROW_RPC,execle,(char const *__restrict __path, char const *__args, ...),{ return __builtin_execle(__path, __args, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_execle)
/* >> execle(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL execle)(char const *__restrict __path, char const *__args, ...) __CASMNAME_SAME("execle");
#elif defined(__CRT_HAVE__execle)
/* >> execle(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL execle)(char const *__restrict __path, char const *__args, ...) __CASMNAME("_execle");
#elif defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve)
#include <local/unistd/execle.h>
/* >> execle(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(execle)
#else /* __cplusplus */
#define execle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execle))
#endif /* !__cplusplus */
#else /* ... */
#undef __execle_defined
#endif /* !... */
#endif /* !__execle_defined */
#ifndef __execlp_defined
#define __execlp_defined 1
#if __has_builtin(__builtin_execlp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execlp) && __has_builtin(__builtin_va_arg_pack)
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
__CEIDECLARE(__ATTR_SENTINEL __ATTR_NONNULL((1)),int,__NOTHROW_RPC,execlp,(char const *__restrict __file, char const *__args, ...),{ return __builtin_execlp(__file, __args, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_execlp)
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL execlp)(char const *__restrict __file, char const *__args, ...) __CASMNAME_SAME("execlp");
#elif defined(__CRT_HAVE__execlp)
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL execlp)(char const *__restrict __file, char const *__args, ...) __CASMNAME("_execlp");
#elif defined(__CRT_HAVE_execvp) || defined(__CRT_HAVE__execvp)
#include <local/unistd/execlp.h>
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(execlp)
#else /* __cplusplus */
#define execlp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execlp))
#endif /* !__cplusplus */
#else /* ... */
#undef __execlp_defined
#endif /* !... */
#endif /* !__execlp_defined */
#if defined(__USE_KOS) || defined(__USE_DOS) || defined(__USE_GNU)
#ifndef __execvpe_defined
#define __execvpe_defined 1
#ifdef __CRT_HAVE_execvpe
/* >> execvpe(3)
 * Replace the calling process with the application image referred to by `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,execvpe,(char const *__restrict __file, __TARGV, __TENVP),(__file,___argv,___envp))
#elif defined(__CRT_HAVE__execvpe)
/* >> execvpe(3)
 * Replace the calling process with the application image referred to by `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,execvpe,(char const *__restrict __file, __TARGV, __TENVP),_execvpe,(__file,___argv,___envp))
#else /* ... */
#undef __execvpe_defined
#endif /* !... */
#endif /* !__execvpe_defined */
#endif /* __USE_KOS || __USE_DOS || __USE_GNU */
#if defined(__USE_KOS) || defined(__USE_DOS)
#ifndef __execlpe_defined
#define __execlpe_defined 1
#ifdef __CRT_HAVE_execlpe
/* >> execlpe(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list, and setting `environ' to a `char **' passed after the NULL sentinel */
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL execlpe)(char const *__restrict __file, char const *__args, ...) __CASMNAME_SAME("execlpe");
#elif defined(__CRT_HAVE__execlpe)
/* >> execlpe(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list, and setting `environ' to a `char **' passed after the NULL sentinel */
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL execlpe)(char const *__restrict __file, char const *__args, ...) __CASMNAME("_execlpe");
#elif defined(__CRT_HAVE_execvpe) || defined(__CRT_HAVE__execvpe)
#include <local/unistd/execlpe.h>
/* >> execlpe(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list, and setting `environ' to a `char **' passed after the NULL sentinel */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(execlpe)
#else /* __cplusplus */
#define execlpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execlpe))
#endif /* !__cplusplus */
#else /* ... */
#undef __execlpe_defined
#endif /* !... */
#endif /* !__execlpe_defined */
#endif /* __USE_KOS || __USE_DOS */

#ifndef __getpid_defined
#define __getpid_defined 1
#ifdef __CRT_HAVE_getpid
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
__CDECLARE(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,getpid,(void),())
#elif defined(__CRT_HAVE__getpid)
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,getpid,(void),_getpid,())
#elif defined(__CRT_HAVE___getpid)
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,getpid,(void),__getpid,())
#else /* ... */
#undef __getpid_defined
#endif /* !... */
#endif /* !__getpid_defined */

#ifdef __USE_KOS
#ifndef __gettid_defined
#define __gettid_defined 1
#ifdef __CRT_HAVE_gettid
/* >> gettid(2)
 * Return the TID of the calling thread
 * THIS_THREAD->PID */
__CDECLARE(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,gettid,(void),())
#else /* __CRT_HAVE_gettid */
#undef __gettid_defined
#endif /* !__CRT_HAVE_gettid */
#endif /* !__gettid_defined */
#endif /* __USE_KOS */

#ifdef __CRT_HAVE_pipe
/* >> pipe(2)
 * Create a new pair of connected pipes ([0] = reader, [1] = writer) */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pipe,(__fd_t __pipedes[2]),(__pipedes))
#elif defined(__CRT_HAVE___pipe)
/* >> pipe(2)
 * Create a new pair of connected pipes ([0] = reader, [1] = writer) */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pipe,(__fd_t __pipedes[2]),__pipe,(__pipedes))
#elif defined(__CRT_HAVE__pipe)
#include <local/unistd/pipe.h>
/* >> pipe(2)
 * Create a new pair of connected pipes ([0] = reader, [1] = writer) */
__NAMESPACE_LOCAL_USING_OR_IMPL(pipe, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL pipe)(__fd_t __pipedes[2]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pipe))(__pipedes); })
#endif /* ... */

#ifndef __sleep_defined
#define __sleep_defined 1
#ifdef __CRT_HAVE_sleep
/* >> sleep(3)
 * Sleep for up to `SECONDS' seconds */
__CDECLARE(,unsigned int,__NOTHROW_RPC,sleep,(unsigned int __seconds),(__seconds))
#elif defined(__CRT_HAVE__sleep) || defined(__CRT_HAVE_sleep)
#include <local/unistd/sleep.h>
/* >> sleep(3)
 * Sleep for up to `SECONDS' seconds */
__NAMESPACE_LOCAL_USING_OR_IMPL(sleep, __FORCELOCAL unsigned int __NOTHROW_RPC(__LIBCCALL sleep)(unsigned int __seconds) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sleep))(__seconds); })
#else /* ... */
#undef __sleep_defined
#endif /* !... */
#endif /* !__sleep_defined */

#ifdef __CRT_HAVE_fsync
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning that changes to its data and/or descriptor are written to disk */
__CDECLARE(,int,__NOTHROW_RPC,fsync,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE__commit)
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning that changes to its data and/or descriptor are written to disk */
__CREDIRECT(,int,__NOTHROW_RPC,fsync,(__fd_t __fd),_commit,(__fd))
#elif defined(__CRT_HAVE_fdatasync)
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning that changes to its data and/or descriptor are written to disk */
__CREDIRECT(,int,__NOTHROW_RPC,fsync,(__fd_t __fd),fdatasync,(__fd))
#else /* ... */
#include <local/unistd/fsync.h>
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning that changes to its data and/or descriptor are written to disk */
__NAMESPACE_LOCAL_USING_OR_IMPL(fsync, __FORCELOCAL int __NOTHROW_RPC(__LIBCCALL fsync)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fsync))(__fd); })
#endif /* !... */

#ifdef __CRT_HAVE_getppid
/* >> getppid(2)
 * Return the PID of the calling process's parent.
 * (That is the TID of the leader of the parent of the calling thread's leader)
 * THIS_THREAD->LEADER->PARENT->LEADER->PID */
__CDECLARE(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,getppid,(void),())
#endif /* __CRT_HAVE_getppid */

#ifdef __CRT_HAVE_getpgrp
/* >> getpgrp(2)
 * Return the ID of the calling process's process group.
 * (That is the TID of the leader of the process group of the calling thread's leader)
 * THIS_THREAD->LEADER->GROUP_LEADER->PID */
__CDECLARE(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,getpgrp,(void),())
#endif /* __CRT_HAVE_getpgrp */

#ifdef __CRT_HAVE_getpgid
/* >> getpgid(2)
 * Return the ID of the process group associated with `PID's process.
 * (That is the TID of the leader of the process group of `PID's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER->PID
 * When `PID' is ZERO(0), use `gettid()' for it instead */
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__getpgid,(__pid_t __pid),getpgid,(__pid))
#elif defined(__CRT_HAVE___getpgid)
/* >> getpgid(2)
 * Return the ID of the process group associated with `PID's process.
 * (That is the TID of the leader of the process group of `PID's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER->PID
 * When `PID' is ZERO(0), use `gettid()' for it instead */
__CDECLARE(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__getpgid,(__pid_t __pid),(__pid))
#endif /* ... */

#ifdef __CRT_HAVE_setpgid
/* >> setpgid(2)
 * Change the ID of the process group associated with `PID's process.
 * (That is the TID of the leader of the process group of `PID's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER = THREAD[PGID]
 * When `PID' is ZERO(0), use `gettid()' for it instead.
 * When `PGID' is ZERO(0), use `PID' (after it was substituted) for instead */
__CDECLARE(,int,__NOTHROW_NCX,setpgid,(__pid_t __pid, __pid_t __pgid),(__pid,__pgid))
#elif defined(__CRT_HAVE___setpgid)
/* >> setpgid(2)
 * Change the ID of the process group associated with `PID's process.
 * (That is the TID of the leader of the process group of `PID's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER = THREAD[PGID]
 * When `PID' is ZERO(0), use `gettid()' for it instead.
 * When `PGID' is ZERO(0), use `PID' (after it was substituted) for instead */
__CREDIRECT(,int,__NOTHROW_NCX,setpgid,(__pid_t __pid, __pid_t __pgid),__setpgid,(__pid,__pgid))
#endif /* ... */

#ifdef __CRT_HAVE_setsid
/* >> setsid(2)
 * Make the calling thread's process the leader of its associated
 * process group, before also making it its own session leader.
 * Then return the TID of that new session leader, which is also the PID of the calling process.
 *  - THIS_THREAD->LEADER->GROUP_LEADER                 = THIS_THREAD->LEADER;
 *  - THIS_THREAD->LEADER->GROUP_LEADER->SESSION_LEADER = THIS_THREAD->LEADER->GROUP_LEADER;
 *  - return THIS_THREAD->LEADER->PID; */
__CDECLARE(,__pid_t,__NOTHROW_NCX,setsid,(void),())
#endif /* __CRT_HAVE_setsid */

#ifdef __CRT_HAVE_getuid
/* >> getuid(2)
 * Return the real user ID of the calling process */
__CDECLARE(__ATTR_WUNUSED,__uid_t,__NOTHROW_NCX,getuid,(void),())
#endif /* __CRT_HAVE_getuid */

#ifdef __CRT_HAVE_geteuid
/* >> geteuid(2)
 * Return the effective user ID of the calling process */
__CDECLARE(__ATTR_WUNUSED,__uid_t,__NOTHROW_NCX,geteuid,(void),())
#endif /* __CRT_HAVE_geteuid */

#ifdef __CRT_HAVE_getgid
/* >> getgid(2)
 * Return the real group ID of the calling process */
__CDECLARE(__ATTR_WUNUSED,__gid_t,__NOTHROW_NCX,getgid,(void),())
#endif /* __CRT_HAVE_getgid */

#ifdef __CRT_HAVE_getegid
/* >> getegid(2)
 * Return the effective group ID of the calling process */
__CDECLARE(__ATTR_WUNUSED,__gid_t,__NOTHROW_NCX,getegid,(void),())
#endif /* __CRT_HAVE_getegid */

/* ... */
#ifdef __CRT_HAVE_getgroups
__CDECLARE(,int,__NOTHROW_NCX,getgroups,(int __size, __gid_t __list[]),(__size,__list))
#endif /* __CRT_HAVE_getgroups */

#ifdef __CRT_HAVE_setuid
/* >> setuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `UID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
__CDECLARE(,int,__NOTHROW_NCX,setuid,(__uid_t __uid),(__uid))
#endif /* __CRT_HAVE_setuid */

#ifdef __CRT_HAVE_setgid
/* >> setgid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `GID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
__CDECLARE(,int,__NOTHROW_NCX,setgid,(__gid_t __gid),(__gid))
#endif /* __CRT_HAVE_setgid */

#if __has_builtin(__builtin_fork) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fork)
/* >> fork(2)
 * Clone the calling thread into a second process and return twice, once
 * in the parent process where this function returns the (non-zero) PID
 * of the forked child process, and a second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with that of another program that the original
 * parent can then `wait(2)' for */
__CEIDECLARE(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,fork,(void),{ return __builtin_fork(); })
#elif defined(__CRT_HAVE_fork)
/* >> fork(2)
 * Clone the calling thread into a second process and return twice, once
 * in the parent process where this function returns the (non-zero) PID
 * of the forked child process, and a second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with that of another program that the original
 * parent can then `wait(2)' for */
__CDECLARE(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,fork,(void),())
#elif defined(__CRT_HAVE___fork)
/* >> fork(2)
 * Clone the calling thread into a second process and return twice, once
 * in the parent process where this function returns the (non-zero) PID
 * of the forked child process, and a second time in the child process
 * itself, where ZERO(0) is returned.
 * The child then usually proceeds by calling `exec(2)' to replace its
 * application image with that of another program that the original
 * parent can then `wait(2)' for */
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,fork,(void),__fork,())
#endif /* ... */

#ifdef __CRT_HAVE_alarm
/* >> alarm(2)
 * @return: 0 : No alarm was scheduled before.
 * @return: * : The number of seconds yet to pass before a previous alarm would have elapsed.
 * Schedule an to deliver a `SIGALRM' after letting `seconds' elapse.
 * You may pass ZERO(0) for SECONDS to disable a previously scheduled alarm */
__CDECLARE(,unsigned int,__NOTHROW_NCX,alarm,(unsigned int __seconds),(__seconds))
#endif /* __CRT_HAVE_alarm */

#ifdef __CRT_HAVE_pause
/* >> pause(2)
 * Suspend execution until the delivery of a POSIX_SIGNAL */
__CDECLARE(,int,__NOTHROW_RPC,pause,(void),())
#endif /* __CRT_HAVE_pause */

#ifdef __CRT_HAVE_fpathconf
/* >> fpathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `FD'
 * return: * : The configuration limit associated with `NAME' for `FD'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `FD'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
__CDECLARE(__ATTR_WUNUSED,__LONGPTR_TYPE__,__NOTHROW_RPC,fpathconf,(__fd_t __fd, int __name),(__fd,__name))
#endif /* __CRT_HAVE_fpathconf */

#ifdef __CRT_HAVE_ttyname
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_RPC,ttyname,(__fd_t __fd),(__fd))
#endif /* __CRT_HAVE_ttyname */
#ifdef __CRT_HAVE_ttyname_r
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,ttyname_r,(__fd_t __fd, char *__buf, size_t __buflen),(__fd,__buf,__buflen))
#endif /* __CRT_HAVE_ttyname_r */

#ifdef __CRT_HAVE_tcgetpgrp
/* >> tcgetpgrp(2)
 * Return the foreground process group of a given TTY file descriptor */
__CDECLARE(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,tcgetpgrp,(__fd_t __fd),(__fd))
#endif /* __CRT_HAVE_tcgetpgrp */

#ifdef __CRT_HAVE_tcsetpgrp
/* >> tcsetpgrp(2)
 * Set the foreground process group of a given TTY file descriptor */
__CDECLARE(,int,__NOTHROW_NCX,tcsetpgrp,(__fd_t __fd, __pid_t __pgrp_id),(__fd,__pgrp_id))
#endif /* __CRT_HAVE_tcsetpgrp */

/* ... */
#ifdef __CRT_HAVE_getlogin
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_NCX,getlogin,(void),())
#endif /* __CRT_HAVE_getlogin */

#ifdef __CRT_HAVE_chown
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,chown,(char const *__file, __uid_t __owner, __gid_t __group),(__file,__owner,__group))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_fchownat)
#include <local/unistd/chown.h>
/* >> chown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER' */
__NAMESPACE_LOCAL_USING_OR_IMPL(chown, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL chown)(char const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(chown))(__file, __owner, __group); })
#endif /* ... */

#ifdef __CRT_HAVE_pathconf
/* >> pathconf(2)
 * @param: NAME: One of `_PC_*' from <bits/confname.h>
 * Return a path configuration value associated with `NAME' for `PATH'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] The configuration specified by `NAME' is unlimited for `PATH'
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
__CDECLARE(__ATTR_NONNULL((1)),__LONGPTR_TYPE__,__NOTHROW_RPC,pathconf,(char const *__path, __STDC_INT_AS_UINT_T __name),(__path,__name))
#endif /* __CRT_HAVE_pathconf */

#ifdef __CRT_HAVE_link
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,link,(char const *__from, char const *__to),(__from,__to))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_linkat)
#include <local/unistd/link.h>
/* >> link(2)
 * Create a hard link from `FROM', leading to `TO' */
__NAMESPACE_LOCAL_USING_OR_IMPL(link, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL link)(char const *__from, char const *__to) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(link))(__from, __to); })
#endif /* ... */
#ifndef __exit_defined
#define __exit_defined 1
#ifdef __std_exit_defined
__NAMESPACE_STD_USING(exit)
#elif __has_builtin(__builtin_exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exit)
__CEIDECLARE(__ATTR_NORETURN,void,__THROWING,exit,(int __status),{ return __builtin_exit(__status); })
#elif defined(__CRT_HAVE_exit)
__CDECLARE_VOID(__ATTR_NORETURN,__THROWING,exit,(int __status),(__status))
#elif defined(__CRT_HAVE_quick_exit)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,exit,(int __status),quick_exit,(__status))
#elif defined(__CRT_HAVE__exit)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,exit,(int __status),_exit,(__status))
#elif defined(__CRT_HAVE__Exit)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,exit,(int __status),_Exit,(__status))
#else /* ... */
#undef __exit_defined
#endif /* !... */
#endif /* !__exit_defined */

#ifndef __read_defined
#define __read_defined 1
#ifdef __CRT_HAVE_read
/* >> read(2)
 * Read data from a given file descriptor `FD' and return the number of bytes read.
 * A return value of ZERO(0) is indicative of EOF */
__CDECLARE(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,read,(__fd_t __fd, void *__buf, size_t __bufsize),(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__read)
/* >> read(2)
 * Read data from a given file descriptor `FD' and return the number of bytes read.
 * A return value of ZERO(0) is indicative of EOF */
__CREDIRECT(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,read,(__fd_t __fd, void *__buf, size_t __bufsize),_read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___read)
/* >> read(2)
 * Read data from a given file descriptor `FD' and return the number of bytes read.
 * A return value of ZERO(0) is indicative of EOF */
__CREDIRECT(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,read,(__fd_t __fd, void *__buf, size_t __bufsize),__read,(__fd,__buf,__bufsize))
#else /* ... */
#undef __read_defined
#endif /* !... */
#endif /* !__read_defined */

#ifndef __write_defined
#define __write_defined 1
#ifdef __CRT_HAVE_write
/* >> write(2)
 * Write data to a given file descriptor `FD' and return the number of bytes written */
__CDECLARE(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,write,(__fd_t __fd, void const *__buf, size_t __bufsize),(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__write)
/* >> write(2)
 * Write data to a given file descriptor `FD' and return the number of bytes written */
__CREDIRECT(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,write,(__fd_t __fd, void const *__buf, size_t __bufsize),_write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___write)
/* >> write(2)
 * Write data to a given file descriptor `FD' and return the number of bytes written */
__CREDIRECT(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,write,(__fd_t __fd, void const *__buf, size_t __bufsize),__write,(__fd,__buf,__bufsize))
#else /* ... */
#undef __write_defined
#endif /* !... */
#endif /* !__write_defined */

#ifdef __USE_KOS
#ifndef __readall_defined
#define __readall_defined 1
#ifdef __CRT_HAVE_readall
/* >> readall(3)
 * Same as `read(2)', however keep on reading until `read()' indicates EOF (causing
 * `readall()' to immediately return `0') or the entirety of the given buffer has been
 * filled (in which case `bufsize' is returned).
 * If an error occurrs before all data could be read, try to use SEEK_CUR to rewind
 * the file descriptor by the amount of data that had already been loaded. - Errors
 * during this phase are silently ignored and don't cause `errno' to change */
__CDECLARE(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,readall,(__fd_t __fd, void *__buf, size_t __bufsize),(__fd,__buf,__bufsize))
#elif (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && (defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64))
#include <local/unistd/readall.h>
/* >> readall(3)
 * Same as `read(2)', however keep on reading until `read()' indicates EOF (causing
 * `readall()' to immediately return `0') or the entirety of the given buffer has been
 * filled (in which case `bufsize' is returned).
 * If an error occurrs before all data could be read, try to use SEEK_CUR to rewind
 * the file descriptor by the amount of data that had already been loaded. - Errors
 * during this phase are silently ignored and don't cause `errno' to change */
__NAMESPACE_LOCAL_USING_OR_IMPL(readall, __FORCELOCAL __ATTR_NONNULL((2)) ssize_t __NOTHROW_RPC(__LIBCCALL readall)(__fd_t __fd, void *__buf, size_t __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(readall))(__fd, __buf, __bufsize); })
#else /* ... */
#undef __readall_defined
#endif /* !... */
#endif /* !__readall_defined */
#ifndef __writeall_defined
#define __writeall_defined 1
#ifdef __CRT_HAVE_writeall
/* >> writeall(3)
 * Same as `write(2)', however keep on writing until `write()' indicates EOF (causing
 * `writeall()' to immediately return `0') or the entirety of the given buffer has been
 * written (in which case `bufsize' is returned). */
__CDECLARE(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,writeall,(__fd_t __fd, void const *__buf, size_t __bufsize),(__fd,__buf,__bufsize))
#elif (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && (defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64))
#include <local/unistd/writeall.h>
/* >> writeall(3)
 * Same as `write(2)', however keep on writing until `write()' indicates EOF (causing
 * `writeall()' to immediately return `0') or the entirety of the given buffer has been
 * written (in which case `bufsize' is returned). */
__NAMESPACE_LOCAL_USING_OR_IMPL(writeall, __FORCELOCAL __ATTR_NONNULL((2)) ssize_t __NOTHROW_RPC(__LIBCCALL writeall)(__fd_t __fd, void const *__buf, size_t __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(writeall))(__fd, __buf, __bufsize); })
#else /* ... */
#undef __writeall_defined
#endif /* !... */
#endif /* !__writeall_defined */
#endif /* __USE_KOS */

#ifndef __lseek_defined
#define __lseek_defined 1
#if defined(__CRT_HAVE_lseek64) && defined(__USE_FILE_OFFSET64)
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,lseek,(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence),lseek64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseeki64) && defined(__USE_FILE_OFFSET64)
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,lseek,(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence),_lseeki64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek) && !defined(__USE_FILE_OFFSET64)
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CDECLARE(,__FS_TYPE(off),__NOTHROW_NCX,lseek,(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence),(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseek) && !defined(__USE_FILE_OFFSET64)
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,lseek,(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence),_lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___lseek) && !defined(__USE_FILE_OFFSET64)
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__FS_TYPE(off),__NOTHROW_NCX,lseek,(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence),__lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64)
#include <local/unistd/lseek.h>
/* >> lseek(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__NAMESPACE_LOCAL_USING_OR_IMPL(lseek, __FORCELOCAL __FS_TYPE(off) __NOTHROW_NCX(__LIBCCALL lseek)(__fd_t __fd, __FS_TYPE(off) __offset, __STDC_INT_AS_UINT_T __whence) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lseek))(__fd, __offset, __whence); })
#else /* ... */
#undef __lseek_defined
#endif /* !... */
#endif /* !__lseek_defined */

#ifndef __isatty_defined
#define __isatty_defined 1
#ifdef __CRT_HAVE_isatty
/* >> isatty(2)
 * @return: 1: Is a tty
 * @return: 0: Not a tty
 * Check if the given file handle `FD' refers to a TTY */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,isatty,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE__isatty)
/* >> isatty(2)
 * @return: 1: Is a tty
 * @return: 0: Not a tty
 * Check if the given file handle `FD' refers to a TTY */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,isatty,(__fd_t __fd),_isatty,(__fd))
#else /* ... */
#undef __isatty_defined
#endif /* !... */
#endif /* !__isatty_defined */

#ifndef __dup2_defined
#define __dup2_defined 1
#ifdef __CRT_HAVE_dup2
/* >> dup2(2)
 * @return: NEWFD: Returns the new handle upon success.
 * Duplicate a file referred to by `OLDFD' into `NEWFD' */
__CDECLARE(,__fd_t,__NOTHROW_NCX,dup2,(__fd_t __oldfd, __fd_t __newfd),(__oldfd,__newfd))
#elif defined(__CRT_HAVE__dup2)
/* >> dup2(2)
 * @return: NEWFD: Returns the new handle upon success.
 * Duplicate a file referred to by `OLDFD' into `NEWFD' */
__CREDIRECT(,__fd_t,__NOTHROW_NCX,dup2,(__fd_t __oldfd, __fd_t __newfd),_dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE___dup2)
/* >> dup2(2)
 * @return: NEWFD: Returns the new handle upon success.
 * Duplicate a file referred to by `OLDFD' into `NEWFD' */
__CREDIRECT(,__fd_t,__NOTHROW_NCX,dup2,(__fd_t __oldfd, __fd_t __newfd),__dup2,(__oldfd,__newfd))
#else /* ... */
#undef __dup2_defined
#endif /* !... */
#endif /* !__dup2_defined */

#ifndef __dup_defined
#define __dup_defined 1
#ifdef __CRT_HAVE_dup
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `FD' and return its duplicated handle number */
__CDECLARE(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,dup,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE__dup)
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `FD' and return its duplicated handle number */
__CREDIRECT(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,dup,(__fd_t __fd),_dup,(__fd))
#else /* ... */
#undef __dup_defined
#endif /* !... */
#endif /* !__dup_defined */

#ifndef __close_defined
#define __close_defined 1
#ifdef __CRT_HAVE_close
/* >> close(2)
 * Close a file handle */
__CDECLARE(,int,__NOTHROW_NCX,close,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE__close)
/* >> close(2)
 * Close a file handle */
__CREDIRECT(,int,__NOTHROW_NCX,close,(__fd_t __fd),_close,(__fd))
#elif defined(__CRT_HAVE___close)
/* >> close(2)
 * Close a file handle */
__CREDIRECT(,int,__NOTHROW_NCX,close,(__fd_t __fd),__close,(__fd))
#else /* ... */
#undef __close_defined
#endif /* !... */
#endif /* !__close_defined */

#ifndef __access_defined
#define __access_defined 1
#ifdef __CRT_HAVE_access
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,access,(char const *__file, __STDC_INT_AS_UINT_T __type),(__file,__type))
#elif defined(__CRT_HAVE__access)
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,access,(char const *__file, __STDC_INT_AS_UINT_T __type),_access,(__file,__type))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_faccessat)
#include <local/unistd/access.h>
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(access, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL access)(char const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(access))(__file, __type); })
#else /* ... */
#undef __access_defined
#endif /* !... */
#endif /* !__access_defined */

#ifndef __chdir_defined
#define __chdir_defined 1
#ifdef __CRT_HAVE_chdir
/* >> chdir(2)
 * Change the current working directory to `PATH' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,chdir,(char const *__path),(__path))
#elif defined(__CRT_HAVE__chdir)
/* >> chdir(2)
 * Change the current working directory to `PATH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,chdir,(char const *__path),_chdir,(__path))
#else /* ... */
#undef __chdir_defined
#endif /* !... */
#endif /* !__chdir_defined */

#ifndef __getcwd_defined
#define __getcwd_defined 1
#ifdef __CRT_HAVE_getcwd
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CDECLARE(,char *,__NOTHROW_RPC,getcwd,(char *__buf, size_t __bufsize),(__buf,__bufsize))
#elif defined(__CRT_HAVE__getcwd)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT(,char *,__NOTHROW_RPC,getcwd,(char *__buf, size_t __bufsize),_getcwd,(__buf,__bufsize))
#else /* ... */
#undef __getcwd_defined
#endif /* !... */
#endif /* !__getcwd_defined */

#ifndef __unlink_defined
#define __unlink_defined 1
#ifdef __CRT_HAVE_unlink
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,unlink,(char const *__file),(__file))
#elif defined(__CRT_HAVE__unlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,unlink,(char const *__file),_unlink,(__file))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
#include <local/unistd/unlink.h>
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(unlink, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL unlink)(char const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unlink))(__file); })
#else /* ... */
#undef __unlink_defined
#endif /* !... */
#endif /* !__unlink_defined */

#ifndef __rmdir_defined
#define __rmdir_defined 1
#ifdef __CRT_HAVE_rmdir
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,rmdir,(char const *__path),(__path))
#elif defined(__CRT_HAVE__rmdir)
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,rmdir,(char const *__path),_rmdir,(__path))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
#include <local/unistd/rmdir.h>
/* >> rmdir(2)
 * Remove a directory referred to by `PATH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rmdir, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL rmdir)(char const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rmdir))(__path); })
#else /* ... */
#undef __rmdir_defined
#endif /* !... */
#endif /* !__rmdir_defined */

#ifdef __USE_GNU
#ifdef __CRT_HAVE_euidaccess
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,euidaccess,(char const *__file, __STDC_INT_AS_UINT_T __type),(__file,__type))
#elif defined(__CRT_HAVE_eaccess)
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,euidaccess,(char const *__file, __STDC_INT_AS_UINT_T __type),eaccess,(__file,__type))
#elif defined(__CRT_HAVE__access) && defined(__CRT_DOS)
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,euidaccess,(char const *__file, __STDC_INT_AS_UINT_T __type),_access,(__file,__type))
#else /* ... */
#include <asm/fcntl.h>
#if defined(__CRT_AT_FDCWD) && defined(__AT_EACCESS) && defined(__CRT_HAVE_faccessat)
#include <local/unistd/euidaccess.h>
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__NAMESPACE_LOCAL_USING_OR_IMPL(euidaccess, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL euidaccess)(char const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(euidaccess))(__file, __type); })
#endif /* __CRT_AT_FDCWD && __AT_EACCESS && __CRT_HAVE_faccessat */
#endif /* !... */

#ifdef __CRT_HAVE_euidaccess
/* >> eaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,eaccess,(char const *__file, __STDC_INT_AS_UINT_T __type),euidaccess,(__file,__type))
#elif defined(__CRT_HAVE_eaccess)
/* >> eaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,eaccess,(char const *__file, __STDC_INT_AS_UINT_T __type),(__file,__type))
#elif defined(__CRT_HAVE__access) && defined(__CRT_DOS)
/* >> eaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_RPC,eaccess,(char const *__file, __STDC_INT_AS_UINT_T __type),_access,(__file,__type))
#else /* ... */
#include <asm/fcntl.h>
#if defined(__CRT_AT_FDCWD) && defined(__AT_EACCESS) && defined(__CRT_HAVE_faccessat)
#include <local/unistd/euidaccess.h>
/* >> eaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL eaccess)(char const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(euidaccess))(__file, __type); }
#endif /* __CRT_AT_FDCWD && __AT_EACCESS && __CRT_HAVE_faccessat */
#endif /* !... */
#endif /* __USE_GNU */

#ifdef __USE_ATFILE
#ifdef __CRT_HAVE_faccessat
/* >> faccessat(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,faccessat,(__fd_t __dfd, char const *__file, __STDC_INT_AS_UINT_T __type, __atflag_t __flags),(__dfd,__file,__type,__flags))
#endif /* __CRT_HAVE_faccessat */

#ifdef __CRT_HAVE_fchownat
/* >> fchownat(2)
 * Change the ownership of a given `DFD:FILE' to `GROUP:OWNER' */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,fchownat,(__fd_t __dfd, char const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),(__dfd,__file,__owner,__group,__flags))
#endif /* __CRT_HAVE_fchownat */

#ifdef __CRT_HAVE_linkat
/* >> linkat(2)
 * Create a hard link from `FROMFD:FROM', leading to `TOFD:TO' */
__CDECLARE(__ATTR_NONNULL((2, 4)),int,__NOTHROW_RPC,linkat,(__fd_t __fromfd, char const *__from, __fd_t __tofd, char const *__to, __atflag_t __flags),(__fromfd,__from,__tofd,__to,__flags))
#endif /* __CRT_HAVE_linkat */

#ifdef __CRT_HAVE_symlinkat
/* >> symlinkat(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TOFD:TARGET_PATH' */
__CDECLARE(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,symlinkat,(char const *__link_text, __fd_t __tofd, char const *__target_path),(__link_text,__tofd,__target_path))
#endif /* __CRT_HAVE_symlinkat */

#ifdef __CRT_HAVE_readlinkat
/* >> readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__CDECLARE(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,readlinkat,(__fd_t __dfd, char const *__restrict __path, char *__restrict __buf, size_t __buflen),(__dfd,__path,__buf,__buflen))
#endif /* __CRT_HAVE_readlinkat */

#ifdef __USE_KOS
#ifdef __CRT_HAVE_freadlinkat
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH|AT_READLINK_REQSIZE' */
__CDECLARE(__ATTR_NONNULL((2, 3)),ssize_t,__NOTHROW_RPC,freadlinkat,(__fd_t __dfd, char const *__restrict __path, char *__restrict __buf, size_t __buflen, __atflag_t __flags),(__dfd,__path,__buf,__buflen,__flags))
#endif /* __CRT_HAVE_freadlinkat */
#endif /* __USE_KOS */

#ifdef __CRT_HAVE_unlinkat
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,unlinkat,(__fd_t __dfd, char const *__name, __atflag_t __flags),(__dfd,__name,__flags))
#endif /* __CRT_HAVE_unlinkat */
#endif /* __USE_ATFILE */


#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_lseek64
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CDECLARE(,__off64_t,__NOTHROW_NCX,lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseeki64)
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),_lseeki64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek)
#include <local/unistd/lseek64.h>
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__NAMESPACE_LOCAL_USING_OR_IMPL(lseek64, __FORCELOCAL __off64_t __NOTHROW_NCX(__LIBCCALL lseek64)(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lseek64))(__fd, __offset, __whence); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */


#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#ifndef __PIO_OFFSET
#ifdef __USE_KOS
#define __PIO_OFFSET     __FS_TYPE(pos)
#define __PIO_OFFSET64   __pos64_t
#else /* __USE_KOS */
#define __PIO_OFFSET     __FS_TYPE(off)
#define __PIO_OFFSET64   __off64_t
#endif /* !__USE_KOS */
#endif /* !__PIO_OFFSET */

#if defined(__CRT_HAVE_pread64) && defined(__USE_FILE_OFFSET64)
/* >> pread(2)
 * Read data from a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,pread,(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET __offset),pread64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pread) && !defined(__USE_FILE_OFFSET64)
/* >> pread(2)
 * Read data from a file at a specific offset */
__CDECLARE(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,pread,(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET __offset),(__fd,__buf,__bufsize,__offset))
#else /* ... */
#include <asm/stdio.h>
#if defined(__CRT_HAVE_pread64) || defined(__CRT_HAVE___pread64) || defined(__CRT_HAVE_pread) || ((defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64)) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && defined(__SEEK_CUR) && defined(__SEEK_SET)) || ((defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64)) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && defined(__SEEK_SET) && defined(__SEEK_CUR))
#include <local/unistd/pread.h>
/* >> pread(2)
 * Read data from a file at a specific offset */
__NAMESPACE_LOCAL_USING_OR_IMPL(pread, __FORCELOCAL __ATTR_NONNULL((2)) ssize_t __NOTHROW_RPC(__LIBCCALL pread)(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pread))(__fd, __buf, __bufsize, __offset); })
#endif /* __CRT_HAVE_pread64 || __CRT_HAVE___pread64 || __CRT_HAVE_pread || ((__CRT_HAVE_lseek || __CRT_HAVE__lseek || __CRT_HAVE___lseek || __CRT_HAVE_lseek64 || __CRT_HAVE__lseeki64) && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read) && __SEEK_CUR && __SEEK_SET) || ((__CRT_HAVE_lseek || __CRT_HAVE__lseek || __CRT_HAVE___lseek || __CRT_HAVE_lseek64 || __CRT_HAVE__lseeki64) && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read) && __SEEK_SET && __SEEK_CUR) */
#endif /* !... */
#if defined(__CRT_HAVE_pwrite64) && defined(__USE_FILE_OFFSET64)
/* >> pwrite(2)
 * Write data to a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,pwrite,(__fd_t __fd, void const *__buf, size_t __bufsize, __PIO_OFFSET __offset),pwrite64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pwrite) && !defined(__USE_FILE_OFFSET64)
/* >> pwrite(2)
 * Write data to a file at a specific offset */
__CDECLARE(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,pwrite,(__fd_t __fd, void const *__buf, size_t __bufsize, __PIO_OFFSET __offset),(__fd,__buf,__bufsize,__offset))
#else /* ... */
#include <asm/stdio.h>
#if defined(__CRT_HAVE_pwrite64) || defined(__CRT_HAVE___pwrite64) || defined(__CRT_HAVE_pwrite) || ((defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && defined(__SEEK_CUR) && defined(__SEEK_SET)) || ((defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && defined(__SEEK_SET) && defined(__SEEK_CUR))
#include <local/unistd/pwrite.h>
/* >> pwrite(2)
 * Write data to a file at a specific offset */
__NAMESPACE_LOCAL_USING_OR_IMPL(pwrite, __FORCELOCAL __ATTR_NONNULL((2)) ssize_t __NOTHROW_RPC(__LIBCCALL pwrite)(__fd_t __fd, void const *__buf, size_t __bufsize, __PIO_OFFSET __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pwrite))(__fd, __buf, __bufsize, __offset); })
#endif /* __CRT_HAVE_pwrite64 || __CRT_HAVE___pwrite64 || __CRT_HAVE_pwrite || ((__CRT_HAVE_lseek || __CRT_HAVE__lseek || __CRT_HAVE___lseek || __CRT_HAVE_lseek64 || __CRT_HAVE__lseeki64) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write) && __SEEK_CUR && __SEEK_SET) || ((__CRT_HAVE_lseek || __CRT_HAVE__lseek || __CRT_HAVE___lseek || __CRT_HAVE_lseek64 || __CRT_HAVE__lseeki64) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write) && __SEEK_SET && __SEEK_CUR) */
#endif /* !... */

#ifdef __USE_KOS
#if defined(__CRT_HAVE_preadall64) && defined(__USE_FILE_OFFSET64)
/* >> preadall(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
__CREDIRECT(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,preadall,(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET __offset),preadall64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_preadall) && !defined(__USE_FILE_OFFSET64)
/* >> preadall(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
__CDECLARE(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,preadall,(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_preadall64) || (defined(__CRT_HAVE_preadall) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) || defined(__CRT_HAVE_pread64) || defined(__CRT_HAVE___pread64) || defined(__CRT_HAVE_pread) || ((defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64)) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && defined(__SEEK_CUR) && defined(__SEEK_SET))
#include <local/unistd/preadall.h>
/* >> preadall(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(preadall, __FORCELOCAL __ATTR_NONNULL((2)) ssize_t __NOTHROW_RPC(__LIBCCALL preadall)(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(preadall))(__fd, __buf, __bufsize, __offset); })
#endif /* ... */
#if defined(__CRT_HAVE_pwriteall64) && defined(__USE_FILE_OFFSET64)
/* >> pwriteall(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
__CREDIRECT(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,pwriteall,(__fd_t __fd, void const *__buf, size_t __bufsize, __PIO_OFFSET __offset),pwriteall64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pwriteall) && !defined(__USE_FILE_OFFSET64)
/* >> pwriteall(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
__CDECLARE(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,pwriteall,(__fd_t __fd, void const *__buf, size_t __bufsize, __PIO_OFFSET __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pwriteall64) || (defined(__CRT_HAVE_pwriteall) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) || defined(__CRT_HAVE_pwrite64) || defined(__CRT_HAVE___pwrite64) || defined(__CRT_HAVE_pwrite) || ((defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && defined(__SEEK_CUR) && defined(__SEEK_SET))
#include <local/unistd/pwriteall.h>
/* >> pwriteall(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(pwriteall, __FORCELOCAL __ATTR_NONNULL((2)) ssize_t __NOTHROW_RPC(__LIBCCALL pwriteall)(__fd_t __fd, void const *__buf, size_t __bufsize, __PIO_OFFSET __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pwriteall))(__fd, __buf, __bufsize, __offset); })
#endif /* ... */
#endif /* __USE_KOS */

#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_pread64
/* >> pread64(2)
 * Read data from a file at a specific offset */
__CDECLARE(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,pread64,(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET64 __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pread) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> pread64(2)
 * Read data from a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,pread64,(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET64 __offset),pread,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE___pread64)
/* >> pread64(2)
 * Read data from a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,pread64,(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET64 __offset),__pread64,(__fd,__buf,__bufsize,__offset))
#else /* ... */
#include <asm/stdio.h>
#if defined(__CRT_HAVE_pread) || ((defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64)) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && defined(__SEEK_CUR) && defined(__SEEK_SET))
#include <local/unistd/pread64.h>
/* >> pread64(2)
 * Read data from a file at a specific offset */
__NAMESPACE_LOCAL_USING_OR_IMPL(pread64, __FORCELOCAL __ATTR_NONNULL((2)) ssize_t __NOTHROW_RPC(__LIBCCALL pread64)(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET64 __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pread64))(__fd, __buf, __bufsize, __offset); })
#endif /* __CRT_HAVE_pread || ((__CRT_HAVE_lseek || __CRT_HAVE__lseek || __CRT_HAVE___lseek || __CRT_HAVE_lseek64 || __CRT_HAVE__lseeki64) && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read) && __SEEK_CUR && __SEEK_SET) */
#endif /* !... */
#ifdef __CRT_HAVE_pwrite64
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
__CDECLARE(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,pwrite64,(__fd_t __fd, void const *__buf, size_t __bufsize, __PIO_OFFSET64 __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pwrite) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,pwrite64,(__fd_t __fd, void const *__buf, size_t __bufsize, __PIO_OFFSET64 __offset),pwrite,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE___pwrite64)
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,pwrite64,(__fd_t __fd, void const *__buf, size_t __bufsize, __PIO_OFFSET64 __offset),__pwrite64,(__fd,__buf,__bufsize,__offset))
#else /* ... */
#include <asm/stdio.h>
#if defined(__CRT_HAVE_pwrite) || ((defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && defined(__SEEK_CUR) && defined(__SEEK_SET))
#include <local/unistd/pwrite64.h>
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
__NAMESPACE_LOCAL_USING_OR_IMPL(pwrite64, __FORCELOCAL __ATTR_NONNULL((2)) ssize_t __NOTHROW_RPC(__LIBCCALL pwrite64)(__fd_t __fd, void const *__buf, size_t __bufsize, __PIO_OFFSET64 __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pwrite64))(__fd, __buf, __bufsize, __offset); })
#endif /* __CRT_HAVE_pwrite || ((__CRT_HAVE_lseek || __CRT_HAVE__lseek || __CRT_HAVE___lseek || __CRT_HAVE_lseek64 || __CRT_HAVE__lseeki64) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write) && __SEEK_CUR && __SEEK_SET) */
#endif /* !... */

#ifdef __USE_KOS
#ifdef __CRT_HAVE_preadall64
/* >> preadall64(3)
 * Same as `readall(3)', but using `pread64(2)' instead of `read()' */
__CDECLARE(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,preadall64,(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET64 __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_preadall) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> preadall64(3)
 * Same as `readall(3)', but using `pread64(2)' instead of `read()' */
__CREDIRECT(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,preadall64,(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET64 __offset),preadall,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pread64) || defined(__CRT_HAVE___pread64) || defined(__CRT_HAVE_pread) || ((defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64)) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && defined(__SEEK_CUR) && defined(__SEEK_SET))
#include <local/unistd/preadall64.h>
/* >> preadall64(3)
 * Same as `readall(3)', but using `pread64(2)' instead of `read()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(preadall64, __FORCELOCAL __ATTR_NONNULL((2)) ssize_t __NOTHROW_RPC(__LIBCCALL preadall64)(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET64 __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(preadall64))(__fd, __buf, __bufsize, __offset); })
#endif /* ... */
#ifdef __CRT_HAVE_pwriteall64
/* >> pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite64(2)' instead of `write()' */
__CDECLARE(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,pwriteall64,(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET64 __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pwriteall) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite64(2)' instead of `write()' */
__CREDIRECT(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,pwriteall64,(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET64 __offset),pwriteall,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pwrite64) || defined(__CRT_HAVE___pwrite64) || defined(__CRT_HAVE_pwrite) || ((defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && defined(__SEEK_CUR) && defined(__SEEK_SET))
#include <local/unistd/pwriteall64.h>
/* >> pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite64(2)' instead of `write()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(pwriteall64, __FORCELOCAL __ATTR_NONNULL((2)) ssize_t __NOTHROW_RPC(__LIBCCALL pwriteall64)(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET64 __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pwriteall64))(__fd, __buf, __bufsize, __offset); })
#endif /* ... */
#endif /* __USE_KOS */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */


#ifdef __USE_GNU
#ifndef __environ_defined
#define __environ_defined 1
#undef environ
#if defined(__CRT_HAVE_environ)
__LIBC char **environ;
#define environ environ
#elif defined(__CRT_HAVE__environ) && !defined(__NO_ASMNAME)
__LIBC char **environ __ASMNAME("_environ");
#define environ environ
#elif defined(__CRT_HAVE__environ)
#undef _environ
#ifndef ___environ_defined
#define ___environ_defined 1
__LIBC char **_environ;
#endif /* !___environ_defined */
#define environ _environ
#elif defined(__CRT_HAVE___p__environ)
#ifndef ____p__environ_defined
#define ____p__environ_defined 1
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,char ***,__NOTHROW,__p__environ,(void),())
#endif /* !____p__environ_defined */
#define environ   (*__p__environ())
#else
#undef __environ_defined
#endif
#endif /* !__environ_defined */
#ifdef __CRT_HAVE_pipe2
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,pipe2,(__fd_t __pipedes[2], __oflag_t __flags),(__pipedes,__flags))
#elif defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE__pipe)
#include <local/unistd/pipe2.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(pipe2, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL pipe2)(__fd_t __pipedes[2], __oflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pipe2))(__pipedes, __flags); })
#endif /* ... */
#ifdef __CRT_HAVE_dup3
__CDECLARE(,__fd_t,__NOTHROW_NCX,dup3,(__fd_t __oldfd, __fd_t __newfd, __oflag_t __flags),(__oldfd,__newfd,__flags))
#elif defined(__CRT_HAVE_dup2) || defined(__CRT_HAVE__dup2) || defined(__CRT_HAVE___dup2)
#include <local/unistd/dup3.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(dup3, __FORCELOCAL __fd_t __NOTHROW_NCX(__LIBCCALL dup3)(__fd_t __oldfd, __fd_t __newfd, __oflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dup3))(__oldfd, __newfd, __flags); })
#endif /* ... */
#ifdef __CRT_HAVE_get_current_dir_name
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_RPC,get_current_dir_name,(void),())
#elif defined(__CRT_HAVE_getcwd) || defined(__CRT_HAVE__getcwd)
#include <local/unistd/get_current_dir_name.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(get_current_dir_name, __FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED char *__NOTHROW_RPC(__LIBCCALL get_current_dir_name)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(get_current_dir_name))(); })
#endif /* ... */
#ifdef __CRT_HAVE_syncfs
__CDECLARE(,int,__NOTHROW_RPC,syncfs,(__fd_t __fd),(__fd))
#else /* __CRT_HAVE_syncfs */
#include <local/unistd/syncfs.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(syncfs, __FORCELOCAL int __NOTHROW_RPC(__LIBCCALL syncfs)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(syncfs))(__fd); })
#endif /* !__CRT_HAVE_syncfs */
#ifdef __CRT_HAVE_group_member
__CDECLARE(,int,__NOTHROW_NCX,group_member,(__gid_t __gid),(__gid))
#endif /* __CRT_HAVE_group_member */
#ifdef __CRT_HAVE_getresuid
__CDECLARE(,int,__NOTHROW_NCX,getresuid,(__uid_t *__ruid, __uid_t *__euid, __uid_t *__suid),(__ruid,__euid,__suid))
#endif /* __CRT_HAVE_getresuid */
#ifdef __CRT_HAVE_getresgid
__CDECLARE(,int,__NOTHROW_NCX,getresgid,(__gid_t *__rgid, __gid_t *__egid, __gid_t *__sgid),(__rgid,__egid,__sgid))
#endif /* __CRT_HAVE_getresgid */
#ifdef __CRT_HAVE_setresuid
__CDECLARE(,int,__NOTHROW_NCX,setresuid,(__uid_t __ruid, __uid_t __euid, __uid_t __suid),(__ruid,__euid,__suid))
#endif /* __CRT_HAVE_setresuid */
#ifdef __CRT_HAVE_setresgid
__CDECLARE(,int,__NOTHROW_NCX,setresgid,(__gid_t __rgid, __gid_t __egid, __gid_t __sgid),(__rgid,__egid,__sgid))
#endif /* __CRT_HAVE_setresgid */
#endif /* __USE_GNU */
#if (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8)) || \
     defined(__USE_MISC)
#ifdef __CRT_HAVE_usleep
/* Sleep for `useconds' microseconds (1/1.000.000 seconds) */
__CDECLARE(,int,__NOTHROW_RPC,usleep,(__useconds_t __useconds),(__useconds))
#elif defined(__CRT_HAVE___crtSleep) || defined(__CRT_HAVE_delay)
#include <local/unistd/usleep.h>
/* Sleep for `useconds' microseconds (1/1.000.000 seconds) */
__NAMESPACE_LOCAL_USING_OR_IMPL(usleep, __FORCELOCAL int __NOTHROW_RPC(__LIBCCALL usleep)(__useconds_t __useconds) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(usleep))(__useconds); })
#endif /* ... */
#ifdef __CRT_HAVE_getwd
__CDECLARE(__ATTR_DEPRECATED("Use getcwd()") __ATTR_NONNULL((1)),char *,__NOTHROW_RPC,getwd,(char *__buf),(__buf))
#elif defined(__CRT_HAVE_getcwd) || defined(__CRT_HAVE__getcwd)
#include <local/unistd/getwd.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(getwd, __FORCELOCAL __ATTR_DEPRECATED("Use getcwd()") __ATTR_NONNULL((1)) char *__NOTHROW_RPC(__LIBCCALL getwd)(char *__buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getwd))(__buf); })
#endif /* ... */
#ifdef __CRT_HAVE_ualarm
__CDECLARE(,__useconds_t,__NOTHROW_NCX,ualarm,(__useconds_t __value, __useconds_t __interval),(__value,__interval))
#endif /* __CRT_HAVE_ualarm */

#ifndef __vfork_defined
#define __vfork_defined 1
#ifdef __CRT_HAVE_vfork
/* >> vfork(2)
 * Same as `fork(2)', but possibly suspend the calling process until the
 * child process either calls `exit(2)' or one of the many `exec(2)' functions */
__CDECLARE(__ATTR_RETURNS_TWICE __ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,vfork,(void),())
#elif defined(__CRT_HAVE___vfork)
/* >> vfork(2)
 * Same as `fork(2)', but possibly suspend the calling process until the
 * child process either calls `exit(2)' or one of the many `exec(2)' functions */
__CREDIRECT(__ATTR_RETURNS_TWICE __ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,vfork,(void),__vfork,())
#else /* ... */
#undef __vfork_defined
#endif /* !... */
#endif /* !__vfork_defined */
#endif /* (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K8) || __USE_MISC */

#ifdef __CRT_HAVE_fchown
/* >> fchown(2)
 * Change the ownership of a given `FD' to `GROUP:OWNER' */
__CDECLARE(,int,__NOTHROW_RPC,fchown,(__fd_t __fd, __uid_t __owner, __gid_t __group),(__fd,__owner,__group))
#endif /* __CRT_HAVE_fchown */

#ifdef __CRT_HAVE_fchdir
/* >> chdir(2)
 * Change the current working directory to `PATH' */
__CDECLARE(,int,__NOTHROW_RPC,fchdir,(__fd_t __fd),(__fd))
#endif /* __CRT_HAVE_fchdir */

#ifdef __CRT_HAVE_getpgid
/* >> getpgid(2)
 * Return the ID of the process group associated with `PID's process.
 * (That is the TID of the leader of the process group of `PID's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER->PID
 * When `PID' is ZERO(0), use `gettid()' for it instead */
__CDECLARE(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,getpgid,(__pid_t __pid),(__pid))
#elif defined(__CRT_HAVE___getpgid)
/* >> getpgid(2)
 * Return the ID of the process group associated with `PID's process.
 * (That is the TID of the leader of the process group of `PID's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER->PID
 * When `PID' is ZERO(0), use `gettid()' for it instead */
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,getpgid,(__pid_t __pid),__getpgid,(__pid))
#endif /* ... */

#ifdef __CRT_HAVE_getsid
/* >> getsid(2)
 * Return the ID of the session which a process `PID' is apart of.
 * return THREAD[PID]->LEADER->GROUP_LEADER->SESSION_LEADER->PID; */
__CDECLARE(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,getsid,(__pid_t __pid),(__pid))
#endif /* __CRT_HAVE_getsid */

#ifdef __CRT_HAVE_lchown
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,lchown,(char const *__file, __uid_t __owner, __gid_t __group),(__file,__owner,__group))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_fchownat)
#include <local/unistd/lchown.h>
/* >> lchown(2)
 * Change the ownership of a given `FILE' to `GROUP:OWNER',
 * but don't reference it if that file is a symbolic link */
__NAMESPACE_LOCAL_USING_OR_IMPL(lchown, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL lchown)(char const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lchown))(__file, __owner, __group); })
#endif /* ... */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#ifndef __PIO_OFFSET
#ifdef __USE_KOS
#define __PIO_OFFSET   __FS_TYPE(pos)
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS */
#define __PIO_OFFSET   __FS_TYPE(off)
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS */
#endif /* !__PIO_OFFSET */

#if defined(__CRT_HAVE_truncate64) && defined(__USE_FILE_OFFSET64)
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,truncate,(char const *__file, __PIO_OFFSET __length),truncate64,(__file,__length))
#elif defined(__CRT_HAVE_truncate) && !defined(__USE_FILE_OFFSET64)
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,truncate,(char const *__file, __PIO_OFFSET __length),(__file,__length))
#elif defined(__CRT_HAVE_truncate64) || defined(__CRT_HAVE_truncate) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate))) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && ((defined(__CRT_HAVE__chsize) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_chsize) && !defined(__USE_FILE_OFFSET64)) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s)))
#include <local/unistd/truncate.h>
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(truncate, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL truncate)(char const *__file, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(truncate))(__file, __length); })
#endif /* ... */

#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_truncate64
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,truncate64,(char const *__file, __PIO_OFFSET64 __length),(__file,__length))
#elif defined(__CRT_HAVE_truncate) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,truncate64,(char const *__file, __PIO_OFFSET64 __length),truncate,(__file,__length))
#elif defined(__CRT_HAVE_truncate) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate)))
#include <local/unistd/truncate64.h>
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(truncate64, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL truncate64)(char const *__file, __PIO_OFFSET64 __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(truncate64))(__file, __length); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

#ifdef __USE_XOPEN2K8

#ifndef __fexecve_defined
#define __fexecve_defined 1
#ifdef __CRT_HAVE_fexecve
/* >> fexecve(2)
 * Replace the calling process with the application image referred to by `FD' and
 * execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CDECLARE(__ATTR_NONNULL((2, 3)),int,__NOTHROW_RPC,fexecve,(__fd_t __fd, __TARGV, __TENVP),(__fd,___argv,___envp))
#else /* __CRT_HAVE_fexecve */
#undef __fexecve_defined
#endif /* !__CRT_HAVE_fexecve */
#endif /* !__fexecve_defined */
#endif /* __USE_XOPEN2K8 */

#ifdef __USE_GNU
#ifndef __execvpe_defined
#define __execvpe_defined 1
#ifdef __CRT_HAVE_execvpe
/* >> execvpe(3)
 * Replace the calling process with the application image referred to by `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,execvpe,(char const *__restrict __file, __TARGV, __TENVP),(__file,___argv,___envp))
#elif defined(__CRT_HAVE__execvpe)
/* >> execvpe(3)
 * Replace the calling process with the application image referred to by `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,execvpe,(char const *__restrict __file, __TARGV, __TENVP),_execvpe,(__file,___argv,___envp))
#else /* ... */
#undef __execvpe_defined
#endif /* !... */
#endif /* !__execvpe_defined */
#endif /* __USE_GNU */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifdef __CRT_HAVE_nice
__CDECLARE(,int,__NOTHROW_NCX,nice,(int __inc),(__inc))
#else /* __CRT_HAVE_nice */
#include <local/unistd/nice.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(nice, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL nice)(int __inc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nice))(__inc); })
#endif /* !__CRT_HAVE_nice */
#endif /* __USE_MISC || __USE_XOPEN */

#ifndef ___exit_defined
#define ___exit_defined 1
#if __has_builtin(__builtin__Exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE__Exit)
__CEIREDIRECT(__ATTR_NORETURN,void,__THROWING,_exit,(int __status),_Exit,{ return __builtin__Exit(__status); })
#elif __has_builtin(__builtin__exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE__exit)
__CEIDECLARE(__ATTR_NORETURN,void,__THROWING,_exit,(int __status),{ __builtin__exit(__status); })
#elif defined(__CRT_HAVE__Exit)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,_exit,(int __status),_Exit,(__status))
#elif defined(__CRT_HAVE__exit)
__CDECLARE_VOID(__ATTR_NORETURN,__THROWING,_exit,(int __status),(__status))
#elif defined(__CRT_HAVE_quick_exit)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,_exit,(int __status),quick_exit,(__status))
#elif defined(__CRT_HAVE_exit)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,_exit,(int __status),exit,(__status))
#else /* ... */
#undef ___exit_defined
#endif /* !... */
#endif /* !___exit_defined */

#ifdef __USE_POSIX2
#ifdef __CRT_HAVE_confstr
/* Retrieve a system configuration string specified by `name'
 * @param: name:   One of `_CS_*' from <bits/confname.h>
 * @param: buf:    Target buffer
 * @param: buflen: Available buffer size (including a trailing \0-character)
 * @return: * :    Required buffer size (including a trailing \0-character)
 * @return: 1 :    Empty configuration string.
 * @return: 0 :    [errno=EINVAL] Bad configuration `name'. */
__CDECLARE(,size_t,__NOTHROW_NCX,confstr,(__STDC_INT_AS_UINT_T __name, char *__buf, size_t __buflen),(__name,__buf,__buflen))
#endif /* __CRT_HAVE_confstr */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("optarg")
#pragma push_macro("optind")
#pragma push_macro("opterr")
#pragma push_macro("optopt")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef optarg
#undef optind
#undef opterr
#undef optopt
#ifdef __CRT_HAVE_optarg
__LIBC char *optarg;
#endif /* __CRT_HAVE_optarg */
#ifdef __CRT_HAVE_optind
__LIBC int optind;
#endif /* __CRT_HAVE_optind */
#ifdef __CRT_HAVE_opterr
__LIBC int opterr;
#endif /* __CRT_HAVE_opterr */
#ifdef __CRT_HAVE_optopt
__LIBC int optopt;
#endif /* __CRT_HAVE_optopt */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("optopt")
#pragma pop_macro("opterr")
#pragma pop_macro("optind")
#pragma pop_macro("optarg")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#ifndef __getopt_defined
#define __getopt_defined 1
#if defined(__CRT_HAVE___posix_getopt) && defined(__USE_POSIX2) && !defined(__USE_POSIX_IMPLICITLY) && !defined(__USE_GNU)
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,getopt,(int ___argc, char *const ___argv[], char const *__shortopts),__posix_getopt,(___argc,___argv,__shortopts))
#elif defined(__CRT_HAVE_getopt)
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,getopt,(int ___argc, char *const ___argv[], char const *__shortopts),(___argc,___argv,__shortopts))
#else /* ... */
#undef __getopt_defined
#endif /* !... */
#endif /* !__getopt_defined */
#endif /* __USE_POSIX2 */

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)

#ifdef __CRT_HAVE_sync
/* >> sync(2)
 * Synchronize all disk operations of all mounted file systems and flush
 * unwritten buffers down to the hardware layer, ensuring that modifications
 * made become visible on the underlying, persistent media */
__CDECLARE_VOID(,__NOTHROW_RPC,sync,(void),())
#else /* __CRT_HAVE_sync */
#include <local/unistd/sync.h>
/* >> sync(2)
 * Synchronize all disk operations of all mounted file systems and flush
 * unwritten buffers down to the hardware layer, ensuring that modifications
 * made become visible on the underlying, persistent media */
__NAMESPACE_LOCAL_USING_OR_IMPL(sync, __FORCELOCAL void __NOTHROW_RPC(__LIBCCALL sync)(void) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sync))(); })
#endif /* !__CRT_HAVE_sync */

#ifdef __CRT_HAVE_setpgrp
/* >> setpgrp(3)
 * Move the calling process into its own process group.
 * Equivalent to `setpgid(0, 0)' */
__CDECLARE(,int,__NOTHROW_NCX,setpgrp,(void),())
#endif /* __CRT_HAVE_setpgrp */

/* ... */
#ifdef __CRT_HAVE_setreuid
__CDECLARE(,int,__NOTHROW_NCX,setreuid,(__uid_t __ruid, __uid_t __euid),(__ruid,__euid))
#endif /* __CRT_HAVE_setreuid */

/* ... */
#ifdef __CRT_HAVE_setregid
__CDECLARE(,int,__NOTHROW_NCX,setregid,(__gid_t __rgid, __gid_t __egid),(__rgid,__egid))
#endif /* __CRT_HAVE_setregid */

/* ... */
#ifdef __CRT_HAVE_gethostid
__CDECLARE(__ATTR_WUNUSED,__LONGPTR_TYPE__,__NOTHROW_NCX,gethostid,(void),())
#endif /* __CRT_HAVE_gethostid */
#if defined(__USE_MISC) || !defined(__USE_XOPEN2K)
#ifdef __CRT_HAVE_getpagesize
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,getpagesize,(void),())
#elif defined(__CRT_HAVE___getpagesize)
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,getpagesize,(void),__getpagesize,())
#else /* ... */
#include <asm/pagesize.h>
#ifdef __ARCH_PAGESIZE
#include <local/unistd/getpagesize.h>
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
__NAMESPACE_LOCAL_USING_OR_IMPL(getpagesize, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL getpagesize)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getpagesize))(); })
#endif /* __ARCH_PAGESIZE */
#endif /* !... */

/* ... */
#ifdef __CRT_HAVE_getdtablesize
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,getdtablesize,(void),())
#else /* __CRT_HAVE_getdtablesize */
#include <local/unistd/getdtablesize.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(getdtablesize, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL getdtablesize)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getdtablesize))(); })
#endif /* !__CRT_HAVE_getdtablesize */
#endif /* __USE_MISC || !__USE_XOPEN2K */
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

#ifdef __USE_XOPEN2K
#ifdef __CRT_HAVE_seteuid
/* >> seteuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `EUID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
__CDECLARE(,int,__NOTHROW_NCX,seteuid,(__uid_t __euid),(__euid))
#endif /* __CRT_HAVE_seteuid */

#ifdef __CRT_HAVE_setegid
/* >> setegid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `EGID' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
__CDECLARE(,int,__NOTHROW_NCX,setegid,(__gid_t __egid),(__egid))
#endif /* __CRT_HAVE_setegid */
#endif /* __USE_XOPEN2K */

#if defined(__USE_MISC) || \
   (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_UNIX98))
/* ... */
#ifdef __CRT_HAVE_ttyslot
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,ttyslot,(void),())
#endif /* __CRT_HAVE_ttyslot */
#endif

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
#ifdef __CRT_HAVE_symlink
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,symlink,(char const *__link_text, char const *__target_path),(__link_text,__target_path))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_symlinkat)
#include <local/unistd/symlink.h>
/* >> symlink(3)
 * Create a new symbolic link loaded with `LINK_TEXT' as link
 * text, at the filesystem location referred to by `TARGET_PATH'.
 * Same as `symlinkat(LINK_TEXT, AT_FDCWD, TARGET_PATH)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(symlink, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL symlink)(char const *__link_text, char const *__target_path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(symlink))(__link_text, __target_path); })
#endif /* ... */

#ifdef __CRT_HAVE_readlink
/* >> readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__CDECLARE(__ATTR_NONNULL((1, 2)),ssize_t,__NOTHROW_RPC,readlink,(char const *__restrict __path, char *__restrict __buf, size_t __buflen),(__path,__buf,__buflen))
#elif defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_readlinkat)
#include <local/unistd/readlink.h>
/* >> readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(readlink, __FORCELOCAL __ATTR_NONNULL((1, 2)) ssize_t __NOTHROW_RPC(__LIBCCALL readlink)(char const *__restrict __path, char *__restrict __buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(readlink))(__path, __buf, __buflen); })
#endif /* ... */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

#if defined(__USE_REENTRANT) || defined(__USE_POSIX199506)
#ifdef __CRT_HAVE_getlogin_r
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,getlogin_r,(char *__name, size_t __name_len),(__name,__name_len))
#endif /* __CRT_HAVE_getlogin_r */
#endif /* __USE_REENTRANT || __USE_POSIX199506 */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
#ifdef __CRT_HAVE_gethostname
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,gethostname,(char *__name, size_t __buflen),(__name,__buflen))
#endif /* __CRT_HAVE_gethostname */
#endif /* __USE_UNIX98 || __USE_XOPEN2K */

#ifdef __USE_MISC
/* ... */
#ifdef __CRT_HAVE_setlogin
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,setlogin,(char const *__name),(__name))
#endif /* __CRT_HAVE_setlogin */

#ifdef __CRT_HAVE_sethostname
/* >> sethostname(2)
 * Set the name of the hosting machine */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sethostname,(char const *__name, size_t __len),(__name,__len))
#endif /* __CRT_HAVE_sethostname */

/* ... */
#ifdef __CRT_HAVE_sethostid
__CDECLARE(,int,__NOTHROW_NCX,sethostid,(__LONGPTR_TYPE__ __id),(__id))
#endif /* __CRT_HAVE_sethostid */

#ifdef __CRT_HAVE_getdomainname
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,getdomainname,(char *__name, size_t __buflen),(__name,__buflen))
#endif /* __CRT_HAVE_getdomainname */

#ifdef __CRT_HAVE_setdomainname
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,setdomainname,(char const *__name, size_t __len),(__name,__len))
#endif /* __CRT_HAVE_setdomainname */

/* ... */
#ifdef __CRT_HAVE_vhangup
__CDECLARE(,int,__NOTHROW_NCX,vhangup,(void),())
#endif /* __CRT_HAVE_vhangup */

/* ... */
#ifdef __CRT_HAVE_profil
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,profil,(__UINT16_TYPE__ *__sample_buffer, size_t __size, size_t __offset, unsigned int __scale),(__sample_buffer,__size,__offset,__scale))
#endif /* __CRT_HAVE_profil */

/* ... */
#ifdef __CRT_HAVE_getusershell
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_RPC,getusershell,(void),())
#endif /* __CRT_HAVE_getusershell */

/* ... */
#ifdef __CRT_HAVE_endusershell
__CDECLARE_VOID(,__NOTHROW_NCX,endusershell,(void),())
#endif /* __CRT_HAVE_endusershell */

/* ... */
#ifdef __CRT_HAVE_setusershell
__CDECLARE_VOID(,__NOTHROW_RPC,setusershell,(void),())
#endif /* __CRT_HAVE_setusershell */

/* ... */
#ifdef __CRT_HAVE_daemon
__CDECLARE(,int,__NOTHROW_RPC,daemon,(__STDC_INT_AS_UINT_T __nochdir, __STDC_INT_AS_UINT_T __noclose),(__nochdir,__noclose))
#endif /* __CRT_HAVE_daemon */

/* ... */
#ifdef __CRT_HAVE_revoke
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,revoke,(char const *__file),(__file))
#endif /* __CRT_HAVE_revoke */

#if !defined(__acct_defined) && defined(__CRT_HAVE_acct)
#define __acct_defined 1
/* Switch process accounting on and off */
__CDECLARE(,int,__NOTHROW_RPC,acct,(const char *__filename),(__filename))
#endif /* !__acct_defined && __CRT_HAVE_acct */
#ifdef __CRT_HAVE_syscall
__LIBC __LONGPTR_TYPE__ __NOTHROW_RPC(__VLIBCCALL syscall)(__LONGPTR_TYPE__ __sysno, ...) __CASMNAME_SAME("syscall");
#endif /* __CRT_HAVE_syscall */

#ifdef __USE_KOS
#ifdef __CRT_HAVE_syscall
__LIBC __LONG64_TYPE__ __NOTHROW_RPC(__VLIBCCALL syscall64)(__syscall_ulong_t __sysno, ...) __CASMNAME("syscall");
#elif defined(__CRT_HAVE_syscall64)
__LIBC __LONG64_TYPE__ __NOTHROW_RPC(__VLIBCCALL syscall64)(__syscall_ulong_t __sysno, ...) __CASMNAME_SAME("syscall64");
#endif /* ... */
#endif /* __USE_KOS */

#ifndef __getentropy_defined
#define __getentropy_defined 1
#ifdef __CRT_HAVE_getentropy
/* Similar to `getrandom(BUF, NUM_BYTES, GRND_RANDOM)', however
 * the case where the calling thread is interrupted, causing an
 * less than `NUM_BYTES' of data to be read is handled by reading
 * more random data until all of `NUM_BYTES' have been read.
 * Note that portable applications should be aware that certain
 * implementations of this function disallow calls where `NUM_BYTES'
 * is larger than `256'
 * Also note that any other than `EFAULT' and `ENOSYS' are translated into `EIO'
 * @return:  0: Success
 * @return: -1: Error (see `errno') */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,getentropy,(void *__buf, size_t __num_bytes),(__buf,__num_bytes))
#else /* __CRT_HAVE_getentropy */
#include <asm/random.h>
#if defined(__GRND_RANDOM) && defined(__CRT_HAVE_getrandom)
#include <local/sys.random/getentropy.h>
/* Similar to `getrandom(BUF, NUM_BYTES, GRND_RANDOM)', however
 * the case where the calling thread is interrupted, causing an
 * less than `NUM_BYTES' of data to be read is handled by reading
 * more random data until all of `NUM_BYTES' have been read.
 * Note that portable applications should be aware that certain
 * implementations of this function disallow calls where `NUM_BYTES'
 * is larger than `256'
 * Also note that any other than `EFAULT' and `ENOSYS' are translated into `EIO'
 * @return:  0: Success
 * @return: -1: Error (see `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(getentropy, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL getentropy)(void *__buf, size_t __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getentropy))(__buf, __num_bytes); })
#else /* __GRND_RANDOM && __CRT_HAVE_getrandom */
#undef __getentropy_defined
#endif /* !__GRND_RANDOM || !__CRT_HAVE_getrandom */
#endif /* !__CRT_HAVE_getentropy */
#endif /* !__getentropy_defined */
#endif /* __USE_MISC */

#if defined(__USE_MISC) || \
   (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
#ifdef __CRT_HAVE_chroot
/* >> chroot(2)
 * Change the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `PATH' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,chroot,(char const *__restrict __path),(__path))
#endif /* __CRT_HAVE_chroot */

/* ... */
#ifdef __CRT_HAVE_getpass
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_RPC,getpass,(char const *__restrict __prompt),(__prompt))
#endif /* __CRT_HAVE_getpass */
#endif /* ... */

#if defined(__USE_POSIX199309) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
#if defined(__CRT_HAVE_ftruncate64) && defined(__USE_FILE_OFFSET64)
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,ftruncate,(__fd_t __fd, __PIO_OFFSET __length),ftruncate64,(__fd,__length))
#elif defined(__CRT_HAVE__chsize_s) && defined(__USE_FILE_OFFSET64)
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,ftruncate,(__fd_t __fd, __PIO_OFFSET __length),_chsize_s,(__fd,__length))
#elif defined(__CRT_HAVE_ftruncate) && !defined(__USE_FILE_OFFSET64)
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CDECLARE(,int,__NOTHROW_NCX,ftruncate,(__fd_t __fd, __PIO_OFFSET __length),(__fd,__length))
#elif defined(__CRT_HAVE__chsize) && !defined(__USE_FILE_OFFSET64)
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,ftruncate,(__fd_t __fd, __PIO_OFFSET __length),_chsize,(__fd,__length))
#elif defined(__CRT_HAVE_chsize) && !defined(__USE_FILE_OFFSET64)
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,ftruncate,(__fd_t __fd, __PIO_OFFSET __length),chsize,(__fd,__length))
#elif defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s)
#include <local/unistd/ftruncate.h>
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ftruncate, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL ftruncate)(__fd_t __fd, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftruncate))(__fd, __length); })
#endif /* ... */

#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_ftruncate64
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CDECLARE(,int,__NOTHROW_NCX,ftruncate64,(__fd_t __fd, __PIO_OFFSET64 __length),(__fd,__length))
#elif defined(__CRT_HAVE_ftruncate) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,ftruncate64,(__fd_t __fd, __PIO_OFFSET64 __length),ftruncate,(__fd,__length))
#elif defined(__CRT_HAVE__chsize_s)
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,ftruncate64,(__fd_t __fd, __PIO_OFFSET64 __length),_chsize_s,(__fd,__length))
#elif defined(__CRT_HAVE_ftruncate)
#include <local/unistd/ftruncate64.h>
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ftruncate64, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL ftruncate64)(__fd_t __fd, __PIO_OFFSET64 __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftruncate64))(__fd, __length); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_POSIX199309 || __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

#if (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K)) || \
     defined(__USE_MISC)
#ifdef __CRT_HAVE_brk
/* >> brk(2), sbrk(2)
 * Change the program break, allowing for a rudimentary implementation of a heap.
 * It is recommended to use the much more advanced functions found in <sys/mman.h> instead */
__CDECLARE(,int,__NOTHROW_NCX,brk,(void *__addr),(__addr))
#endif /* __CRT_HAVE_brk */
#ifdef __CRT_HAVE_sbrk
__CDECLARE(,void *,__NOTHROW_NCX,sbrk,(intptr_t __delta),(__delta))
#elif defined(__CRT_HAVE___sbrk)
__CREDIRECT(,void *,__NOTHROW_NCX,sbrk,(intptr_t __delta),__sbrk,(__delta))
#endif /* ... */
#endif

#if defined(__USE_POSIX199309) || defined(__USE_UNIX98)
#ifdef __CRT_HAVE_fdatasync
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps, and its size), meaning that changes are written to disk */
__CDECLARE(,int,__NOTHROW_RPC,fdatasync,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE_fsync)
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps, and its size), meaning that changes are written to disk */
__CREDIRECT(,int,__NOTHROW_RPC,fdatasync,(__fd_t __fd),fsync,(__fd))
#elif defined(__CRT_HAVE__commit)
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps, and its size), meaning that changes are written to disk */
__CREDIRECT(,int,__NOTHROW_RPC,fdatasync,(__fd_t __fd),_commit,(__fd))
#else /* ... */
#include <local/unistd/fdatasync.h>
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps, and its size), meaning that changes are written to disk */
__NAMESPACE_LOCAL_USING_OR_IMPL(fdatasync, __FORCELOCAL int __NOTHROW_RPC(__LIBCCALL fdatasync)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fdatasync))(__fd); })
#endif /* !... */
#endif /* __USE_POSIX199309 || __USE_UNIX98 */

#ifdef __USE_XOPEN
#ifndef __crypt_defined
#define __crypt_defined 1
#ifdef __CRT_HAVE_crypt
/* Encrypt at most 8 characters from KEY using salt to perturb DES */
__CDECLARE(__ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,crypt,(char const *__key, char const *__salt),(__key,__salt))
#else /* __CRT_HAVE_crypt */
#undef __crypt_defined
#endif /* !__CRT_HAVE_crypt */
#endif /* !__crypt_defined */
#ifndef __encrypt_defined
#define __encrypt_defined 1
#ifdef __CRT_HAVE_encrypt
/* Encrypt data in BLOCK in place if EDFLAG is zero; otherwise decrypt block in place */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,encrypt,(char *__glibc_block, int __edflag),(__glibc_block,__edflag))
#else /* __CRT_HAVE_encrypt */
#undef __encrypt_defined
#endif /* !__CRT_HAVE_encrypt */
#endif /* !__encrypt_defined */

#ifndef __swab_defined
#define __swab_defined 1
#ifdef __CRT_HAVE_swab
/* Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
__CDECLARE_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,swab,(void const *__restrict __from, void *__restrict __to, __STDC_INT_AS_SSIZE_T __n_bytes),(__from,__to,__n_bytes))
#elif defined(__CRT_HAVE__swab)
/* Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
__CREDIRECT_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,swab,(void const *__restrict __from, void *__restrict __to, __STDC_INT_AS_SSIZE_T __n_bytes),_swab,(__from,__to,__n_bytes))
#else /* ... */
#include <local/unistd/swab.h>
/* Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
__NAMESPACE_LOCAL_USING_OR_IMPL(swab, __FORCELOCAL __ATTR_NONNULL((1, 2)) void __NOTHROW_NCX(__LIBCCALL swab)(void const *__restrict __from, void *__restrict __to, __STDC_INT_AS_SSIZE_T __n_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swab))(__from, __to, __n_bytes); })
#endif /* !... */
#endif /* !__swab_defined */
#endif /* __USE_XOPEN */


#if (defined(_EVERY_SOURCE) || \
     (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K)))
/* ... */
#ifndef __ctermid_defined
#define __ctermid_defined 1
#ifdef __CRT_HAVE_ctermid
__CDECLARE(,char *,__NOTHROW_NCX,ctermid,(char *__s),(__s))
#else /* __CRT_HAVE_ctermid */
#undef __ctermid_defined
#endif /* !__CRT_HAVE_ctermid */
#endif /* !__ctermid_defined */
#ifndef __cuserid_defined
#define __cuserid_defined 1
#ifdef __CRT_HAVE_cuserid
/* Return the name of the current user (`getpwuid(geteuid())'), storing
 * that name in `S'. When `S' is NULL, a static buffer is used instead */
__CDECLARE(,char *,__NOTHROW_NCX,cuserid,(char *__s),(__s))
#else /* __CRT_HAVE_cuserid */
#undef __cuserid_defined
#endif /* !__CRT_HAVE_cuserid */
#endif /* !__cuserid_defined */
#endif /* _EVERY_SOURCE || (__USE_XOPEN && !__USE_XOPEN2K) */


#if (defined(_EVERY_SOURCE) || \
     (defined(__USE_UNIX98) && !defined(__USE_XOPEN2K)))
#ifndef ____pthread_atfork_func_t_defined
#define ____pthread_atfork_func_t_defined 1
typedef void (__LIBCCALL *__pthread_atfork_func_t)(void);
#endif /* !____pthread_atfork_func_t_defined */

#ifndef __pthread_atfork_defined
#define __pthread_atfork_defined 1
#ifdef __CRT_HAVE_pthread_atfork
/* Install handlers to be called when a new process is created with FORK.
 * The PREPARE handler is called in the parent process just before performing
 * FORK. The PARENT handler is called in the parent process just after FORK.
 * The CHILD handler is called in the child process. Each of the three
 * handlers can be NULL, meaning that no handler needs to be called at that
 * point.
 * PTHREAD_ATFORK can be called several times, in which case the PREPARE
 * handlers are called in LIFO order (last added with PTHREAD_ATFORK,
 * first called before FORK), and the PARENT and CHILD handlers are called
 * in FIFO (first added, first called) */
__CDECLARE(,int,__NOTHROW_NCX,pthread_atfork,(__pthread_atfork_func_t __prepare, __pthread_atfork_func_t __parent, __pthread_atfork_func_t __child),(__prepare,__parent,__child))
#else /* __CRT_HAVE_pthread_atfork */
#undef __pthread_atfork_defined
#endif /* !__CRT_HAVE_pthread_atfork */
#endif /* !__pthread_atfork_defined */
#endif /* _EVERY_SOURCE || (__USE_UNIX98 && !__USE_XOPEN2K) */


#ifdef __USE_REENTRANT
#ifndef __ctermid_r_defined
#define __ctermid_r_defined 1
#ifdef __CRT_HAVE_ctermid_r
/* Same as `ctermid', but return `NULL' when `S' is `NULL' */
__CDECLARE(,char *,__NOTHROW_NCX,ctermid_r,(char *__s),(__s))
#elif defined(__CRT_HAVE_ctermid)
#include <local/unistd/ctermid_r.h>
/* Same as `ctermid', but return `NULL' when `S' is `NULL' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ctermid_r, __FORCELOCAL char *__NOTHROW_NCX(__LIBCCALL ctermid_r)(char *__s) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ctermid_r))(__s); })
#else /* ... */
#undef __ctermid_r_defined
#endif /* !... */
#endif /* !__ctermid_r_defined */
#endif /* __USE_REENTRANT */


#ifdef __CRT_HAVE_sysconf
/* >> sysconf(2)
 * @param: NAME: One of `_SC_*' from <bits/confname.h>
 * Return a system configuration value `NAME'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] `NAME' referrs to a maximum or minimum
 *                                 limit, and that limit is indeterminate
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
__CDECLARE(__ATTR_WUNUSED,__LONGPTR_TYPE__,__NOTHROW_RPC,sysconf,(__STDC_INT_AS_UINT_T __name),(__name))
#elif defined(__CRT_HAVE__sysconf)
/* >> sysconf(2)
 * @param: NAME: One of `_SC_*' from <bits/confname.h>
 * Return a system configuration value `NAME'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] `NAME' referrs to a maximum or minimum
 *                                 limit, and that limit is indeterminate
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
__CREDIRECT(__ATTR_WUNUSED,__LONGPTR_TYPE__,__NOTHROW_RPC,sysconf,(__STDC_INT_AS_UINT_T __name),_sysconf,(__name))
#elif defined(__CRT_HAVE___sysconf)
/* >> sysconf(2)
 * @param: NAME: One of `_SC_*' from <bits/confname.h>
 * Return a system configuration value `NAME'
 * return: * : The configuration limit associated with `NAME' for `PATH'
 * return: -1: [errno=<unchanged>] `NAME' referrs to a maximum or minimum
 *                                 limit, and that limit is indeterminate
 * return: -1: [errno=EINVAL]      The given `NAME' isn't a recognized config option */
__CREDIRECT(__ATTR_WUNUSED,__LONGPTR_TYPE__,__NOTHROW_RPC,sysconf,(__STDC_INT_AS_UINT_T __name),__sysconf,(__name))
#endif /* ... */


#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_POSIX))
#ifndef F_LOCK
#define F_ULOCK 0 /* Unlock a previously locked region. */
#define F_LOCK  1 /* Lock a region for exclusive use. */
#define F_TLOCK 2 /* Test and lock a region for exclusive use. */
#define F_TEST  3 /* Test a region for other processes locks. */
#endif /* !F_LOCK */
#ifndef __lockf_defined
#define __lockf_defined 1
#if defined(__CRT_HAVE_lockf64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(,int,__NOTHROW_RPC,lockf,(__fd_t __fd, int __cmd, __FS_TYPE(off) __length),lockf64,(__fd,__cmd,__length))
#elif defined(__CRT_HAVE_lockf) && !defined(__USE_FILE_OFFSET64)
__CDECLARE(,int,__NOTHROW_RPC,lockf,(__fd_t __fd, int __cmd, __FS_TYPE(off) __length),(__fd,__cmd,__length))
#elif defined(__CRT_HAVE__locking) && !defined(__USE_FILE_OFFSET64)
__CREDIRECT(,int,__NOTHROW_RPC,lockf,(__fd_t __fd, int __cmd, __FS_TYPE(off) __length),_locking,(__fd,__cmd,__length))
#elif defined(__CRT_HAVE_lockf64) || defined(__CRT_HAVE_lockf) || defined(__CRT_HAVE_locking) || defined(__CRT_HAVE__locking)
#include <local/fcntl/lockf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(lockf, __FORCELOCAL int __NOTHROW_RPC(__LIBCCALL lockf)(__fd_t __fd, int __cmd, __FS_TYPE(off) __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lockf))(__fd, __cmd, __length); })
#else /* ... */
#undef __lockf_defined
#endif /* !... */
#endif /* !__lockf_defined */
#ifdef __USE_LARGEFILE64
#ifndef __lockf64_defined
#define __lockf64_defined 1
#ifdef __CRT_HAVE_lockf64
__CDECLARE(,int,__NOTHROW_RPC,lockf64,(__fd_t __fd, int __cmd, __off64_t __length),(__fd,__cmd,__length))
#elif defined(__CRT_HAVE_lockf) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(,int,__NOTHROW_RPC,lockf64,(__fd_t __fd, int __cmd, __off64_t __length),lockf,(__fd,__cmd,__length))
#elif defined(__CRT_HAVE_lockf) || defined(__CRT_HAVE_locking) || defined(__CRT_HAVE__locking)
#include <local/fcntl/lockf64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(lockf64, __FORCELOCAL int __NOTHROW_RPC(__LIBCCALL lockf64)(__fd_t __fd, int __cmd, __off64_t __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lockf64))(__fd, __cmd, __length); })
#else /* ... */
#undef __lockf64_defined
#endif /* !... */
#endif /* !__lockf64_defined */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_POSIX) */


#ifdef __USE_GNU
#if defined(__COMPILER_HAVE_AUTOTYPE) && defined(__COMPILER_HAVE_TYPEOF)
#define TEMP_FAILURE_RETRY(expression)                     \
	__XBLOCK({                                             \
		__auto_type __result;                              \
		do {                                               \
			__result = (expression);                       \
		} while (__result == (__typeof__(__result)) - 1 && \
		         errno == EINTR);                          \
		__XRETURN __result;                                \
	})
#elif defined(__COMPILER_HAVE_TYPEOF)
#define TEMP_FAILURE_RETRY(expression)                     \
	__XBLOCK({                                             \
		__typeof__(expression) __result;                   \
		do {                                               \
			__result = (expression);                       \
		} while (__result == (__typeof__(__result)) - 1 && \
		         errno == EINTR);                          \
		__XRETURN __result;                                \
	})
#else /* __COMPILER_HAVE_TYPEOF */
#define TEMP_FAILURE_RETRY(expression)               \
	__XBLOCK({                                       \
		long int __result;                           \
		do {                                         \
			__result = (long int)(expression);       \
		} while (__result == -1L && errno == EINTR); \
		__XRETURN __result;                          \
	})
#endif /* !__COMPILER_HAVE_TYPEOF */
#endif /* __USE_GNU */

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_KOS
#if defined(_WCHAR_H) && !defined(_PARTS_WCHAR_UNISTD_H)
#include <parts/wchar/unistd.h>
#endif /* _WCHAR_H && !_PARTS_WCHAR_UNISTD_H */
#endif /* __USE_KOS */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_UNISTD_H)
#include <parts/uchar/unistd.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_UNISTD_H */
#endif /* __USE_UTF */

#endif /* !_UNISTD_H */
