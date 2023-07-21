/* HASH CRC-32:0xfa5bc951 */
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
/* (#) Portability: Cygwin       (/winsup/cygwin/include/process.h) */
/* (#) Portability: DJGPP        (/include/process.h) */
/* (#) Portability: EMX kLIBC    (/libc/include/process.h) */
/* (#) Portability: MSVC         (/include/process.h) */
/* (#) Portability: MinGW        (/mingw-w64-headers/crt/process.h) */
/* (#) Portability: Windows Kits (/ucrt/process.h) */
/* (#) Portability: mintlib      (/include/process.h) */
#ifndef _PROCESS_H
#define _PROCESS_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/crt/process.h>
#include <bits/types.h>
#include <kos/anno.h>
#if defined(__USE_DOS) && !defined(__USE_DOS_CLEAN)
#include <corecrt_wprocess.h> /* Include <wchar.h> instead */
#endif /* __USE_DOS && !__USE_DOS_CLEAN */


/* `mode' argument values for spawn() functions. */
#if !defined(P_WAIT) && defined(__P_WAIT)
#define P_WAIT    __P_WAIT    /* Wait for the process to terminate, and return its exit status */
#endif /* !P_WAIT && __P_WAIT */
#if !defined(P_NOWAIT) && defined(__P_NOWAIT)
#define P_NOWAIT  __P_NOWAIT  /* Spawn the process asynchronously, and return its PID */
#endif /* !P_NOWAIT && __P_NOWAIT */
#if !defined(P_OVERLAY) && defined(__P_OVERLAY)
#define P_OVERLAY __P_OVERLAY /* Don't spawn, but rather try to exec() the new program */
#endif /* !P_OVERLAY && __P_OVERLAY */
#if !defined(P_NOWAITO) && defined(__P_NOWAITO)
#define P_NOWAITO __P_NOWAITO /* Same as `P_NOWAIT' */
#endif /* !P_NOWAITO && __P_NOWAITO */
#if !defined(P_DETACH) && defined(__P_DETACH)
#define P_DETACH  __P_DETACH  /* Create the new process as detached and return `0' */
#endif /* !P_DETACH && __P_DETACH */

/* `action' argument values for cwait() functions. */
#if !defined(WAIT_CHILD) && defined(__WAIT_CHILD)
#define WAIT_CHILD      __WAIT_CHILD      /* Ignored */
#endif /* !WAIT_CHILD && __WAIT_CHILD */
#if !defined(WAIT_GRANDCHILD) && defined(__WAIT_GRANDCHILD)
#define WAIT_GRANDCHILD __WAIT_GRANDCHILD /* Ignored */
#endif /* !WAIT_GRANDCHILD && __WAIT_GRANDCHILD */


/* Aliases that are expected by some programs */
#if !defined(_P_WAIT) && defined(__P_WAIT)
#define _P_WAIT __P_WAIT
#endif /* !_P_WAIT && __P_WAIT */
#if !defined(_P_NOWAIT) && defined(__P_NOWAIT)
#define _P_NOWAIT __P_NOWAIT
#endif /* !_P_NOWAIT && __P_NOWAIT */
#if !defined(_P_OVERLAY) && defined(__P_OVERLAY)
#define _P_OVERLAY __P_OVERLAY
#endif /* !_P_OVERLAY && __P_OVERLAY */
#if !defined(_P_NOWAITO) && defined(__P_NOWAITO)
#define _P_NOWAITO __P_NOWAITO
#endif /* !_P_NOWAITO && __P_NOWAITO */
#if !defined(_P_DETACH) && defined(__P_DETACH)
#define _P_DETACH __P_DETACH
#endif /* !_P_DETACH && __P_DETACH */
#if !defined(_WAIT_CHILD) && defined(__WAIT_CHILD)
#define _WAIT_CHILD __WAIT_CHILD
#endif /* !_WAIT_CHILD && __WAIT_CHILD */
#if !defined(_WAIT_GRANDCHILD) && defined(__WAIT_GRANDCHILD)
#define _WAIT_GRANDCHILD __WAIT_GRANDCHILD
#endif /* !_WAIT_GRANDCHILD && __WAIT_GRANDCHILD */


#ifdef __USE_DOS
/* Weird DOS aliases. */
#if !defined(_OLD_P_OVERLAY) && defined(__P_OVERLAY)
#define _OLD_P_OVERLAY __P_OVERLAY
#endif /* !_OLD_P_OVERLAY && __P_OVERLAY */
#if !defined(OLD_P_OVERLAY) && defined(__P_OVERLAY)
#define OLD_P_OVERLAY  __P_OVERLAY
#endif /* !OLD_P_OVERLAY && __P_OVERLAY */
#endif /* __USE_DOS */


#ifndef __TARGV
#ifdef __USE_DOS_ALTERATIONS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS_ALTERATIONS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__TARGV */

#ifdef __CC__
__SYSDECL_BEGIN

/************************************************************************/
/* Standard (as per Cygwin)                                             */
/************************************************************************/

#ifndef __spawnl_defined
#define __spawnl_defined
#ifdef __CRT_HAVE_spawnl
__LIBC __ATTR_SENTINEL __ATTR_IN(2) __ATTR_IN_OPT(3) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnl)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, char const *__args, ...) __CASMNAME_SAME("spawnl");
#elif defined(__CRT_HAVE__spawnl)
__LIBC __ATTR_SENTINEL __ATTR_IN(2) __ATTR_IN_OPT(3) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnl)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, char const *__args, ...) __CASMNAME("_spawnl");
#else /* ... */
#include <libc/template/environ.h>
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#include <asm/os/vfork.h>
#include <asm/os/features.h>
#if defined(__CRT_HAVE_spawnv) || defined(__CRT_HAVE__spawnv) || ((defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)))) && (defined(__CRT_HAVE_fexecve) || (defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)))) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))) && defined(__LOCAL_environ))
#include <libc/local/process/spawnl.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(spawnl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL __ATTR_IN(2) __ATTR_IN_OPT(3) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnl)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, char const *__args, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnl))(__mode, __path, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define spawnl(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnl))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#else /* __CRT_HAVE_spawnv || __CRT_HAVE__spawnv || ((__CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close))) && (__CRT_HAVE_fexecve || (__OS_HAVE_PROCFS_SELF_FD && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve))) && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))))) && __LOCAL_environ) */
#undef __spawnl_defined
#endif /* !__CRT_HAVE_spawnv && !__CRT_HAVE__spawnv && ((!__CRT_HAVE_spawnve && !__CRT_HAVE__spawnve && ((!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_fspawnve && ((!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || ((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork && !__CRT_HAVE___libc_fork) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE___libc_pipe && !__CRT_HAVE__pipe) || !__O_CLOEXEC || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write && !__CRT_HAVE___libc_write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close && !__CRT_HAVE___libc_close))) || (!__CRT_HAVE_fexecve && (!__OS_HAVE_PROCFS_SELF_FD || (!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve))) || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid))))) || !__LOCAL_environ) */
#endif /* !... */
#endif /* !__spawnl_defined */
#ifndef __spawnlp_defined
#define __spawnlp_defined
#ifdef __CRT_HAVE_spawnlp
__LIBC __ATTR_SENTINEL __ATTR_IN(2) __ATTR_IN_OPT(3) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnlp)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, char const *__args, ...) __CASMNAME_SAME("spawnlp");
#elif defined(__CRT_HAVE__spawnlp)
__LIBC __ATTR_SENTINEL __ATTR_IN(2) __ATTR_IN_OPT(3) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnlp)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, char const *__args, ...) __CASMNAME("_spawnlp");
#else /* ... */
#include <libc/template/environ.h>
#include <hybrid/__alloca.h>
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#include <asm/os/vfork.h>
#include <asm/os/features.h>
#if defined(__CRT_HAVE_spawnvp) || defined(__CRT_HAVE__spawnvp) || ((defined(__CRT_HAVE_spawnvpe) || defined(__CRT_HAVE__spawnvpe) || ((defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)))) && (defined(__CRT_HAVE_fexecve) || (defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)))) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))) && defined(__hybrid_alloca))) && defined(__LOCAL_environ))
#include <libc/local/process/spawnlp.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(spawnlp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL __ATTR_IN(2) __ATTR_IN_OPT(3) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnlp)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, char const *__args, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnlp))(__mode, __file, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define spawnlp(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnlp))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#else /* __CRT_HAVE_spawnvp || __CRT_HAVE__spawnvp || ((__CRT_HAVE_spawnvpe || __CRT_HAVE__spawnvpe || ((__CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close))) && (__CRT_HAVE_fexecve || (__OS_HAVE_PROCFS_SELF_FD && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve))) && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))))) && __hybrid_alloca)) && __LOCAL_environ) */
#undef __spawnlp_defined
#endif /* !__CRT_HAVE_spawnvp && !__CRT_HAVE__spawnvp && ((!__CRT_HAVE_spawnvpe && !__CRT_HAVE__spawnvpe && ((!__CRT_HAVE_spawnve && !__CRT_HAVE__spawnve && ((!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_fspawnve && ((!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || ((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork && !__CRT_HAVE___libc_fork) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE___libc_pipe && !__CRT_HAVE__pipe) || !__O_CLOEXEC || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write && !__CRT_HAVE___libc_write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close && !__CRT_HAVE___libc_close))) || (!__CRT_HAVE_fexecve && (!__OS_HAVE_PROCFS_SELF_FD || (!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve))) || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid))))) || !__hybrid_alloca)) || !__LOCAL_environ) */
#endif /* !... */
#endif /* !__spawnlp_defined */
#ifndef __spawnle_defined
#define __spawnle_defined
#ifdef __CRT_HAVE_spawnle
__LIBC __ATTR_IN(2) __ATTR_IN_OPT(3) __ATTR_SENTINEL_O(1) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnle)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, char const *__args, ...) __CASMNAME_SAME("spawnle");
#elif defined(__CRT_HAVE__spawnle)
__LIBC __ATTR_IN(2) __ATTR_IN_OPT(3) __ATTR_SENTINEL_O(1) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnle)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, char const *__args, ...) __CASMNAME("_spawnle");
#else /* ... */
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#include <asm/os/vfork.h>
#include <asm/os/features.h>
#if defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)))) && (defined(__CRT_HAVE_fexecve) || (defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)))) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))
#include <libc/local/process/spawnle.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(spawnle, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_IN_OPT(3) __ATTR_SENTINEL_O(1) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnle)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, char const *__args, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnle))(__mode, __path, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define spawnle(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnle))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#else /* __CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close))) && (__CRT_HAVE_fexecve || (__OS_HAVE_PROCFS_SELF_FD && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve))) && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid)))) */
#undef __spawnle_defined
#endif /* !__CRT_HAVE_spawnve && !__CRT_HAVE__spawnve && ((!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_fspawnve && ((!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || ((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork && !__CRT_HAVE___libc_fork) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE___libc_pipe && !__CRT_HAVE__pipe) || !__O_CLOEXEC || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write && !__CRT_HAVE___libc_write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close && !__CRT_HAVE___libc_close))) || (!__CRT_HAVE_fexecve && (!__OS_HAVE_PROCFS_SELF_FD || (!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve))) || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid)))) */
#endif /* !... */
#endif /* !__spawnle_defined */
#ifndef __spawnlpe_defined
#define __spawnlpe_defined
#ifdef __CRT_HAVE_spawnlpe
__LIBC __ATTR_IN(2) __ATTR_IN_OPT(3) __ATTR_SENTINEL_O(1) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnlpe)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, char const *__args, ...) __CASMNAME_SAME("spawnlpe");
#elif defined(__CRT_HAVE__spawnlpe)
__LIBC __ATTR_IN(2) __ATTR_IN_OPT(3) __ATTR_SENTINEL_O(1) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnlpe)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, char const *__args, ...) __CASMNAME("_spawnlpe");
#else /* ... */
#include <hybrid/__alloca.h>
#include <libc/template/environ.h>
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#include <asm/os/vfork.h>
#include <asm/os/features.h>
#if defined(__CRT_HAVE_spawnvpe) || defined(__CRT_HAVE__spawnvpe) || ((defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)))) && (defined(__CRT_HAVE_fexecve) || (defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)))) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))) && defined(__hybrid_alloca))
#include <libc/local/process/spawnlpe.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(spawnlpe, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_IN_OPT(3) __ATTR_SENTINEL_O(1) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnlpe)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, char const *__args, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnlpe))(__mode, __file, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define spawnlpe(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnlpe))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#else /* __CRT_HAVE_spawnvpe || __CRT_HAVE__spawnvpe || ((__CRT_HAVE_getenv || __LOCAL_environ) && (__CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close))) && (__CRT_HAVE_fexecve || (__OS_HAVE_PROCFS_SELF_FD && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve))) && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))))) && __hybrid_alloca) */
#undef __spawnlpe_defined
#endif /* !__CRT_HAVE_spawnvpe && !__CRT_HAVE__spawnvpe && ((!__CRT_HAVE_getenv && !__LOCAL_environ) || (!__CRT_HAVE_spawnve && !__CRT_HAVE__spawnve && ((!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_fspawnve && ((!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || ((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork && !__CRT_HAVE___libc_fork) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE___libc_pipe && !__CRT_HAVE__pipe) || !__O_CLOEXEC || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write && !__CRT_HAVE___libc_write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close && !__CRT_HAVE___libc_close))) || (!__CRT_HAVE_fexecve && (!__OS_HAVE_PROCFS_SELF_FD || (!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve))) || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid))))) || !__hybrid_alloca) */
#endif /* !... */
#endif /* !__spawnlpe_defined */
#ifndef __spawnv_defined
#define __spawnv_defined
#ifdef __CRT_HAVE_spawnv
__CDECLARE(__ATTR_IN(2) __ATTR_IN(3),__pid_t,__NOTHROW_RPC,spawnv,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, __TARGV),(__mode,__path,___argv))
#elif defined(__CRT_HAVE__spawnv)
__CREDIRECT(__ATTR_IN(2) __ATTR_IN(3),__pid_t,__NOTHROW_RPC,spawnv,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, __TARGV),_spawnv,(__mode,__path,___argv))
#else /* ... */
#include <libc/template/environ.h>
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#include <asm/os/vfork.h>
#include <asm/os/features.h>
#if (defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)))) && (defined(__CRT_HAVE_fexecve) || (defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)))) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))) && defined(__LOCAL_environ)
#include <libc/local/process/spawnv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(spawnv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_IN(3) __pid_t __NOTHROW_RPC(__LIBCCALL spawnv)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, __TARGV) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnv))(__mode, __path, ___argv); })
#else /* (__CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close))) && (__CRT_HAVE_fexecve || (__OS_HAVE_PROCFS_SELF_FD && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve))) && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))))) && __LOCAL_environ */
#undef __spawnv_defined
#endif /* (!__CRT_HAVE_spawnve && !__CRT_HAVE__spawnve && ((!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_fspawnve && ((!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || ((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork && !__CRT_HAVE___libc_fork) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE___libc_pipe && !__CRT_HAVE__pipe) || !__O_CLOEXEC || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write && !__CRT_HAVE___libc_write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close && !__CRT_HAVE___libc_close))) || (!__CRT_HAVE_fexecve && (!__OS_HAVE_PROCFS_SELF_FD || (!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve))) || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid))))) || !__LOCAL_environ */
#endif /* !... */
#endif /* !__spawnv_defined */
#ifndef __spawnvp_defined
#define __spawnvp_defined
#ifdef __CRT_HAVE_spawnvp
__CDECLARE(__ATTR_IN(2) __ATTR_IN(3),__pid_t,__NOTHROW_RPC,spawnvp,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, __TARGV),(__mode,__file,___argv))
#elif defined(__CRT_HAVE__spawnvp)
__CREDIRECT(__ATTR_IN(2) __ATTR_IN(3),__pid_t,__NOTHROW_RPC,spawnvp,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, __TARGV),_spawnvp,(__mode,__file,___argv))
#else /* ... */
#include <libc/template/environ.h>
#include <hybrid/__alloca.h>
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#include <asm/os/vfork.h>
#include <asm/os/features.h>
#if (defined(__CRT_HAVE_spawnvpe) || defined(__CRT_HAVE__spawnvpe) || ((defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)))) && (defined(__CRT_HAVE_fexecve) || (defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)))) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))) && defined(__hybrid_alloca))) && defined(__LOCAL_environ)
#include <libc/local/process/spawnvp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(spawnvp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_IN(3) __pid_t __NOTHROW_RPC(__LIBCCALL spawnvp)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, __TARGV) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnvp))(__mode, __file, ___argv); })
#else /* (__CRT_HAVE_spawnvpe || __CRT_HAVE__spawnvpe || ((__CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close))) && (__CRT_HAVE_fexecve || (__OS_HAVE_PROCFS_SELF_FD && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve))) && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))))) && __hybrid_alloca)) && __LOCAL_environ */
#undef __spawnvp_defined
#endif /* (!__CRT_HAVE_spawnvpe && !__CRT_HAVE__spawnvpe && ((!__CRT_HAVE_spawnve && !__CRT_HAVE__spawnve && ((!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_fspawnve && ((!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || ((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork && !__CRT_HAVE___libc_fork) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE___libc_pipe && !__CRT_HAVE__pipe) || !__O_CLOEXEC || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write && !__CRT_HAVE___libc_write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close && !__CRT_HAVE___libc_close))) || (!__CRT_HAVE_fexecve && (!__OS_HAVE_PROCFS_SELF_FD || (!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve))) || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid))))) || !__hybrid_alloca)) || !__LOCAL_environ */
#endif /* !... */
#endif /* !__spawnvp_defined */
#ifndef __spawnve_defined
#define __spawnve_defined
#ifdef __CRT_HAVE_spawnve
__CDECLARE(__ATTR_IN(2) __ATTR_IN(3) __ATTR_IN(4),__pid_t,__NOTHROW_RPC,spawnve,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, __TARGV, __TENVP),(__mode,__path,___argv,___envp))
#elif defined(__CRT_HAVE__spawnve)
__CREDIRECT(__ATTR_IN(2) __ATTR_IN(3) __ATTR_IN(4),__pid_t,__NOTHROW_RPC,spawnve,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, __TARGV, __TENVP),_spawnve,(__mode,__path,___argv,___envp))
#else /* ... */
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#include <asm/os/vfork.h>
#include <asm/os/features.h>
#if (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)))) && (defined(__CRT_HAVE_fexecve) || (defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)))) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid))))
#include <libc/local/process/spawnve.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(spawnve, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_IN(3) __ATTR_IN(4) __pid_t __NOTHROW_RPC(__LIBCCALL spawnve)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, __TARGV, __TENVP) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnve))(__mode, __path, ___argv, ___envp); })
#else /* (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close))) && (__CRT_HAVE_fexecve || (__OS_HAVE_PROCFS_SELF_FD && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve))) && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))) */
#undef __spawnve_defined
#endif /* (!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_fspawnve && ((!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || ((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork && !__CRT_HAVE___libc_fork) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE___libc_pipe && !__CRT_HAVE__pipe) || !__O_CLOEXEC || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write && !__CRT_HAVE___libc_write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close && !__CRT_HAVE___libc_close))) || (!__CRT_HAVE_fexecve && (!__OS_HAVE_PROCFS_SELF_FD || (!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve))) || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid))) */
#endif /* !... */
#endif /* !__spawnve_defined */
#ifndef __spawnvpe_defined
#define __spawnvpe_defined
#ifdef __CRT_HAVE_spawnvpe
__CDECLARE(__ATTR_IN(2) __ATTR_IN(3) __ATTR_IN(4),__pid_t,__NOTHROW_RPC,spawnvpe,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, __TARGV, __TENVP),(__mode,__file,___argv,___envp))
#elif defined(__CRT_HAVE__spawnvpe)
__CREDIRECT(__ATTR_IN(2) __ATTR_IN(3) __ATTR_IN(4),__pid_t,__NOTHROW_RPC,spawnvpe,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, __TARGV, __TENVP),_spawnvpe,(__mode,__file,___argv,___envp))
#else /* ... */
#include <hybrid/__alloca.h>
#include <libc/template/environ.h>
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#include <asm/os/vfork.h>
#include <asm/os/features.h>
#if (defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)))) && (defined(__CRT_HAVE_fexecve) || (defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)))) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))) && defined(__hybrid_alloca)
#include <libc/local/process/spawnvpe.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(spawnvpe, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_IN(3) __ATTR_IN(4) __pid_t __NOTHROW_RPC(__LIBCCALL spawnvpe)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, __TARGV, __TENVP) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnvpe))(__mode, __file, ___argv, ___envp); })
#else /* (__CRT_HAVE_getenv || __LOCAL_environ) && (__CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close))) && (__CRT_HAVE_fexecve || (__OS_HAVE_PROCFS_SELF_FD && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve))) && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))))) && __hybrid_alloca */
#undef __spawnvpe_defined
#endif /* (!__CRT_HAVE_getenv && !__LOCAL_environ) || (!__CRT_HAVE_spawnve && !__CRT_HAVE__spawnve && ((!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_fspawnve && ((!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || ((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork && !__CRT_HAVE___libc_fork) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE___libc_pipe && !__CRT_HAVE__pipe) || !__O_CLOEXEC || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write && !__CRT_HAVE___libc_write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close && !__CRT_HAVE___libc_close))) || (!__CRT_HAVE_fexecve && (!__OS_HAVE_PROCFS_SELF_FD || (!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve))) || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid))))) || !__hybrid_alloca */
#endif /* !... */
#endif /* !__spawnvpe_defined */
#ifdef __CRT_HAVE_cwait
/* >> cwait(3)
 * DOS name for `waitpid(2)', except that `action' is ignored. Use
 * this function together with the `spawn(3)' family of functions.
 * @return: pid: Child process exited.
 * @return: -1:  Error (s.a. `errno') */
__CDECLARE(__ATTR_OUT_OPT(1),__pid_t,__NOTHROW_RPC,cwait,(int *__tstat, __pid_t __pid, __STDC_INT_AS_UINT_T __action),(__tstat,__pid,__action))
#elif defined(__CRT_HAVE__cwait)
/* >> cwait(3)
 * DOS name for `waitpid(2)', except that `action' is ignored. Use
 * this function together with the `spawn(3)' family of functions.
 * @return: pid: Child process exited.
 * @return: -1:  Error (s.a. `errno') */
__CREDIRECT(__ATTR_OUT_OPT(1),__pid_t,__NOTHROW_RPC,cwait,(int *__tstat, __pid_t __pid, __STDC_INT_AS_UINT_T __action),_cwait,(__tstat,__pid,__action))
#elif defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)
#include <libc/local/process/cwait.h>
/* >> cwait(3)
 * DOS name for `waitpid(2)', except that `action' is ignored. Use
 * this function together with the `spawn(3)' family of functions.
 * @return: pid: Child process exited.
 * @return: -1:  Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(cwait, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT_OPT(1) __pid_t __NOTHROW_RPC(__LIBCCALL cwait)(int *__tstat, __pid_t __pid, __STDC_INT_AS_UINT_T __action) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cwait))(__tstat, __pid, __action); })
#endif /* ... */


/************************************************************************/
/* KOS extensions                                                       */
/************************************************************************/
#if defined(__USE_DOS) || defined(__USE_KOS)
#ifndef __getpid_defined
#define __getpid_defined
#ifdef __CRT_HAVE_getpid
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,getpid,(void),())
#elif defined(__CRT_HAVE__getpid)
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,getpid,(void),_getpid,())
#elif defined(__CRT_HAVE___getpid)
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,getpid,(void),__getpid,())
#elif defined(__CRT_HAVE___libc_getpid)
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,getpid,(void),__libc_getpid,())
#else /* ... */
#undef __getpid_defined
#endif /* !... */
#endif /* !__getpid_defined */
#ifndef __execv_defined
#define __execv_defined
#if __has_builtin(__builtin_execv) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execv)
/* >> execv(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CEIDECLARE_GCCNCX(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_RPC,execv,(char const *__restrict __path, __TARGV),{ return __builtin_execv(__path, (char *const *)___argv); })
#elif defined(__CRT_HAVE_execv)
/* >> execv(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CDECLARE_GCCNCX(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_RPC,execv,(char const *__restrict __path, __TARGV),(__path,___argv))
#elif defined(__CRT_HAVE__execv)
/* >> execv(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CREDIRECT_GCCNCX(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_RPC,execv,(char const *__restrict __path, __TARGV),_execv,(__path,___argv))
#else /* ... */
#include <libc/template/environ.h>
#if (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__LOCAL_environ)
#include <libc/local/unistd/execv.h>
/* >> execv(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__NAMESPACE_LOCAL_USING_OR_IMPL(execv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_RPC(__LIBCCALL execv)(char const *__restrict __path, __TARGV) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execv))(__path, ___argv); })
#else /* (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) && __LOCAL_environ */
#undef __execv_defined
#endif /* (!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve) || !__LOCAL_environ */
#endif /* !... */
#endif /* !__execv_defined */
#ifndef __execvp_defined
#define __execvp_defined
#if __has_builtin(__builtin_execvp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execvp)
/* >> execvp(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CEIDECLARE_GCCNCX(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_RPC,execvp,(char const *__restrict __file, __TARGV),{ return __builtin_execvp(__file, (char *const *)___argv); })
#elif defined(__CRT_HAVE_execvp)
/* >> execvp(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CDECLARE_GCCNCX(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_RPC,execvp,(char const *__restrict __file, __TARGV),(__file,___argv))
#elif defined(__CRT_HAVE__execvp)
/* >> execvp(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CREDIRECT_GCCNCX(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_RPC,execvp,(char const *__restrict __file, __TARGV),_execvp,(__file,___argv))
#else /* ... */
#include <libc/template/environ.h>
#include <hybrid/__alloca.h>
#if (defined(__CRT_HAVE_execvpe) || defined(__CRT_HAVE__execvpe) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__hybrid_alloca))) && defined(__LOCAL_environ)
#include <libc/local/unistd/execvp.h>
/* >> execvp(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__NAMESPACE_LOCAL_USING_OR_IMPL(execvp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_RPC(__LIBCCALL execvp)(char const *__restrict __file, __TARGV) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execvp))(__file, ___argv); })
#else /* (__CRT_HAVE_execvpe || __CRT_HAVE__execvpe || ((__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) && __hybrid_alloca)) && __LOCAL_environ */
#undef __execvp_defined
#endif /* (!__CRT_HAVE_execvpe && !__CRT_HAVE__execvpe && ((!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve) || !__hybrid_alloca)) || !__LOCAL_environ */
#endif /* !... */
#endif /* !__execvp_defined */
#ifndef __execve_defined
#define __execve_defined
#if __has_builtin(__builtin_execve) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execve)
/* >> execve(2)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CEIDECLARE_GCCNCX(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_RPC,execve,(char const *__restrict __path, __TARGV, __TENVP),{ return __builtin_execve(__path, (char *const *)___argv, (char *const *)___envp); })
#elif defined(__CRT_HAVE_execve)
/* >> execve(2)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CDECLARE_GCCNCX(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_RPC,execve,(char const *__restrict __path, __TARGV, __TENVP),(__path,___argv,___envp))
#elif defined(__CRT_HAVE__execve)
/* >> execve(2)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CREDIRECT_GCCNCX(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_RPC,execve,(char const *__restrict __path, __TARGV, __TENVP),_execve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE___execve)
/* >> execve(2)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CREDIRECT_GCCNCX(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_RPC,execve,(char const *__restrict __path, __TARGV, __TENVP),__execve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE___libc_execve)
/* >> execve(2)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CREDIRECT_GCCNCX(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_RPC,execve,(char const *__restrict __path, __TARGV, __TENVP),__libc_execve,(__path,___argv,___envp))
#else /* ... */
#undef __execve_defined
#endif /* !... */
#endif /* !__execve_defined */
#ifndef __execvpe_defined
#define __execvpe_defined
#ifdef __CRT_HAVE_execvpe
/* >> execvpe(3)
 * Replace the  calling process  with the  application  image referred  to by  `file'  and
 * execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CDECLARE(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_RPC,execvpe,(char const *__restrict __file, __TARGV, __TENVP),(__file,___argv,___envp))
#elif defined(__CRT_HAVE__execvpe)
/* >> execvpe(3)
 * Replace the  calling process  with the  application  image referred  to by  `file'  and
 * execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_RPC,execvpe,(char const *__restrict __file, __TARGV, __TENVP),_execvpe,(__file,___argv,___envp))
#else /* ... */
#include <hybrid/__alloca.h>
#include <libc/template/environ.h>
#if (defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__hybrid_alloca)
#include <libc/local/unistd/execvpe.h>
/* >> execvpe(3)
 * Replace the  calling process  with the  application  image referred  to by  `file'  and
 * execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__NAMESPACE_LOCAL_USING_OR_IMPL(execvpe, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3) int __NOTHROW_RPC(__LIBCCALL execvpe)(char const *__restrict __file, __TARGV, __TENVP) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execvpe))(__file, ___argv, ___envp); })
#else /* (__CRT_HAVE_getenv || __LOCAL_environ) && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) && __hybrid_alloca */
#undef __execvpe_defined
#endif /* (!__CRT_HAVE_getenv && !__LOCAL_environ) || (!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve) || !__hybrid_alloca */
#endif /* !... */
#endif /* !__execvpe_defined */
#ifndef __execl_defined
#define __execl_defined
#if __has_builtin(__builtin_execl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execl) && __has_builtin(__builtin_va_arg_pack)
/* >> execl(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
__CEIDECLARE_GCCNCX(__ATTR_SENTINEL __ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,execl,(char const *__restrict __path, char const *__args, ...),{ return __builtin_execl(__path, __args, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_execl)
/* >> execl(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
extern "C++" {
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
__LIBC __ATTR_SENTINEL __ATTR_IN(1) __ATTR_IN_OPT(2) int __NOTHROW_RPC(__VLIBCCALL execl)(char const *__restrict __path, char const *__args, ...) __CASMNAME_SAME_GCCNCX("execl");
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
} /* extern "C++" */
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
#elif defined(__CRT_HAVE__execl)
/* >> execl(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
extern "C++" {
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
__LIBC __ATTR_SENTINEL __ATTR_IN(1) __ATTR_IN_OPT(2) int __NOTHROW_RPC(__VLIBCCALL execl)(char const *__restrict __path, char const *__args, ...) __CASMNAME_GCCNCX("_execl");
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
} /* extern "C++" */
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
#else /* ... */
#include <libc/template/environ.h>
#if defined(__CRT_HAVE_execv) || defined(__CRT_HAVE__execv) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__LOCAL_environ))
#include <libc/local/unistd/execl.h>
/* >> execl(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(execl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL __ATTR_IN(1) __ATTR_IN_OPT(2) int __NOTHROW_RPC(__VLIBCCALL execl)(char const *__restrict __path, char const *__args, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execl))(__path, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define execl(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execl))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#else /* __CRT_HAVE_execv || __CRT_HAVE__execv || ((__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) && __LOCAL_environ) */
#undef __execl_defined
#endif /* !__CRT_HAVE_execv && !__CRT_HAVE__execv && ((!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve) || !__LOCAL_environ) */
#endif /* !... */
#endif /* !__execl_defined */
#ifndef __execlp_defined
#define __execlp_defined
#if __has_builtin(__builtin_execlp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execlp) && __has_builtin(__builtin_va_arg_pack)
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
__CEIDECLARE_GCCNCX(__ATTR_SENTINEL __ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,execlp,(char const *__restrict __file, char const *__args, ...),{ return __builtin_execlp(__file, __args, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_execlp)
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
extern "C++" {
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
__LIBC __ATTR_SENTINEL __ATTR_IN(1) __ATTR_IN_OPT(2) int __NOTHROW_RPC(__VLIBCCALL execlp)(char const *__restrict __file, char const *__args, ...) __CASMNAME_SAME_GCCNCX("execlp");
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
} /* extern "C++" */
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
#elif defined(__CRT_HAVE__execlp)
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
extern "C++" {
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
__LIBC __ATTR_SENTINEL __ATTR_IN(1) __ATTR_IN_OPT(2) int __NOTHROW_RPC(__VLIBCCALL execlp)(char const *__restrict __file, char const *__args, ...) __CASMNAME_GCCNCX("_execlp");
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
} /* extern "C++" */
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
#else /* ... */
#include <libc/template/environ.h>
#include <hybrid/__alloca.h>
#if defined(__CRT_HAVE_execvp) || defined(__CRT_HAVE__execvp) || ((defined(__CRT_HAVE_execvpe) || defined(__CRT_HAVE__execvpe) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__hybrid_alloca))) && defined(__LOCAL_environ))
#include <libc/local/unistd/execlp.h>
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(execlp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL __ATTR_IN(1) __ATTR_IN_OPT(2) int __NOTHROW_RPC(__VLIBCCALL execlp)(char const *__restrict __file, char const *__args, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execlp))(__file, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define execlp(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execlp))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#else /* __CRT_HAVE_execvp || __CRT_HAVE__execvp || ((__CRT_HAVE_execvpe || __CRT_HAVE__execvpe || ((__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) && __hybrid_alloca)) && __LOCAL_environ) */
#undef __execlp_defined
#endif /* !__CRT_HAVE_execvp && !__CRT_HAVE__execvp && ((!__CRT_HAVE_execvpe && !__CRT_HAVE__execvpe && ((!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve) || !__hybrid_alloca)) || !__LOCAL_environ) */
#endif /* !... */
#endif /* !__execlp_defined */
#ifndef __execle_defined
#define __execle_defined
#if __has_builtin(__builtin_execle) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execle) && __has_builtin(__builtin_va_arg_pack)
/* >> execle(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
__CEIDECLARE_GCCNCX(__ATTR_IN(1) __ATTR_IN_OPT(2) __ATTR_SENTINEL_O(1),int,__NOTHROW_RPC,execle,(char const *__restrict __path, char const *__args, ...),{ return __builtin_execle(__path, __args, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_execle)
/* >> execle(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
extern "C++" {
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
__LIBC __ATTR_IN(1) __ATTR_IN_OPT(2) __ATTR_SENTINEL_O(1) int __NOTHROW_RPC(__VLIBCCALL execle)(char const *__restrict __path, char const *__args, ...) __CASMNAME_SAME_GCCNCX("execle");
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
} /* extern "C++" */
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
#elif defined(__CRT_HAVE__execle)
/* >> execle(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
extern "C++" {
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
__LIBC __ATTR_IN(1) __ATTR_IN_OPT(2) __ATTR_SENTINEL_O(1) int __NOTHROW_RPC(__VLIBCCALL execle)(char const *__restrict __path, char const *__args, ...) __CASMNAME_GCCNCX("_execle");
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
} /* extern "C++" */
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
#elif defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)
#include <libc/local/unistd/execle.h>
/* >> execle(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(execle, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN_OPT(2) __ATTR_SENTINEL_O(1) int __NOTHROW_RPC(__VLIBCCALL execle)(char const *__restrict __path, char const *__args, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execle))(__path, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define execle(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execle))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#else /* ... */
#undef __execle_defined
#endif /* !... */
#endif /* !__execle_defined */
#ifndef __execlpe_defined
#define __execlpe_defined
#ifdef __CRT_HAVE_execlpe
/* >> execlpe(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
__LIBC __ATTR_IN(1) __ATTR_IN_OPT(2) __ATTR_SENTINEL_O(1) int __NOTHROW_RPC(__VLIBCCALL execlpe)(char const *__restrict __file, char const *__args, ...) __CASMNAME_SAME("execlpe");
#elif defined(__CRT_HAVE__execlpe)
/* >> execlpe(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
__LIBC __ATTR_IN(1) __ATTR_IN_OPT(2) __ATTR_SENTINEL_O(1) int __NOTHROW_RPC(__VLIBCCALL execlpe)(char const *__restrict __file, char const *__args, ...) __CASMNAME("_execlpe");
#else /* ... */
#include <hybrid/__alloca.h>
#include <libc/template/environ.h>
#if defined(__CRT_HAVE_execvpe) || defined(__CRT_HAVE__execvpe) || ((defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__hybrid_alloca))
#include <libc/local/unistd/execlpe.h>
/* >> execlpe(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(execlpe, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN_OPT(2) __ATTR_SENTINEL_O(1) int __NOTHROW_RPC(__VLIBCCALL execlpe)(char const *__restrict __file, char const *__args, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execlpe))(__file, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define execlpe(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execlpe))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#else /* __CRT_HAVE_execvpe || __CRT_HAVE__execvpe || ((__CRT_HAVE_getenv || __LOCAL_environ) && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) && __hybrid_alloca) */
#undef __execlpe_defined
#endif /* !__CRT_HAVE_execvpe && !__CRT_HAVE__execvpe && ((!__CRT_HAVE_getenv && !__LOCAL_environ) || (!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve) || !__hybrid_alloca) */
#endif /* !... */
#endif /* !__execlpe_defined */
#ifdef __USE_KOS
#ifndef __fspawnve_defined
#define __fspawnve_defined
#ifdef __CRT_HAVE_fspawnve
__CDECLARE(__ATTR_IN(3) __ATTR_IN(4),__pid_t,__NOTHROW_RPC,fspawnve,(__STDC_INT_AS_UINT_T __mode, __fd_t __execfd, __TARGV, __TENVP),(__mode,__path,___argv,___envp))
#else /* __CRT_HAVE_fspawnve */
#include <asm/os/oflags.h>
#include <asm/os/vfork.h>
#include <asm/os/features.h>
#if (defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)))) && (defined(__CRT_HAVE_fexecve) || (defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)))) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid))
#include <libc/local/process/fspawnve.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fspawnve, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_IN(4) __pid_t __NOTHROW_RPC(__LIBCCALL fspawnve)(__STDC_INT_AS_UINT_T __mode, __fd_t __execfd, __TARGV, __TENVP) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fspawnve))(__mode, __path, ___argv, ___envp); })
#else /* (__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close))) && (__CRT_HAVE_fexecve || (__OS_HAVE_PROCFS_SELF_FD && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve))) && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid) */
#undef __fspawnve_defined
#endif /* (!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || ((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork && !__CRT_HAVE___libc_fork) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE___libc_pipe && !__CRT_HAVE__pipe) || !O_CLOEXEC || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write && !__CRT_HAVE___libc_write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close && !__CRT_HAVE___libc_close))) || (!__CRT_HAVE_fexecve && (!__OS_HAVE_PROCFS_SELF_FD || (!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve))) || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid) */
#endif /* !__CRT_HAVE_fspawnve */
#endif /* !__fspawnve_defined */
#ifndef __fexecve_defined
#define __fexecve_defined
#ifdef __CRT_HAVE_fexecve
/* >> fexecve(2)
 * Replace the calling process with the application image referred
 * to by `execfd'  and execute it's  `main()' method, passing  the
 * given `argv', and setting `environ' to `envp'. */
__CDECLARE(__ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_RPC,fexecve,(__fd_t __execfd, __TARGV, __TENVP),(__execfd,___argv,___envp))
#else /* __CRT_HAVE_fexecve */
#include <asm/os/features.h>
#if defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve))
#include <libc/local/unistd/fexecve.h>
/* >> fexecve(2)
 * Replace the calling process with the application image referred
 * to by `execfd'  and execute it's  `main()' method, passing  the
 * given `argv', and setting `environ' to `envp'. */
__NAMESPACE_LOCAL_USING_OR_IMPL(fexecve, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_IN(3) int __NOTHROW_RPC(__LIBCCALL fexecve)(__fd_t __execfd, __TARGV, __TENVP) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fexecve))(__execfd, ___argv, ___envp); })
#else /* __OS_HAVE_PROCFS_SELF_FD && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) */
#undef __fexecve_defined
#endif /* !__OS_HAVE_PROCFS_SELF_FD || (!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve) */
#endif /* !__CRT_HAVE_fexecve */
#endif /* !__fexecve_defined */
#endif /* __USE_KOS */
#endif /* __USE_DOS || __USE_KOS */

/************************************************************************/
/* DOS extensions                                                       */
/************************************************************************/
#ifdef __USE_DOS
#ifndef __intptr_t_defined
#define __intptr_t_defined
typedef __intptr_t intptr_t;
#endif /* !__intptr_t_defined */
#ifndef __uintptr_t_defined
#define __uintptr_t_defined
typedef __uintptr_t uintptr_t;
#endif /* !__uintptr_t_defined */

#ifndef ____dos_beginthreadex_entry_t_defined
#define ____dos_beginthreadex_entry_t_defined
#ifdef __NO_ATTR_STDCALL
typedef __UINT32_TYPE__ (__LIBDCALL *__dos_beginthreadex_entry_t)(void *__arg);
#else /* __NO_ATTR_STDCALL */
typedef __UINT32_TYPE__ (__ATTR_STDCALL *__dos_beginthreadex_entry_t)(void *__arg);
#endif /* !__NO_ATTR_STDCALL */
#endif /* !____dos_beginthreadex_entry_t_defined */

__NAMESPACE_STD_BEGIN
#ifndef __std_exit_defined
#define __std_exit_defined
#ifdef __exit_defined
__NAMESPACE_GLB_USING_OR_IMPL(exit, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NORETURN void (__LIBCCALL exit)(int __status) { :: exit(__status); })
#elif __has_builtin(__builtin_exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exit)
__CEIDECLARE_GCCNCX(__ATTR_NORETURN,void,,exit,(int __status),{ __builtin_exit(__status); })
#elif defined(__CRT_HAVE_exit)
__CDECLARE_VOID_GCCNCX(__ATTR_NORETURN,,exit,(int __status),(__status))
#elif defined(__CRT_HAVE_quick_exit)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,,exit,(int __status),quick_exit,(__status))
#elif defined(__CRT_HAVE__exit)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,,exit,(int __status),_exit,(__status))
#elif defined(__CRT_HAVE__Exit)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,,exit,(int __status),_Exit,(__status))
#elif defined(__CRT_HAVE_xexit)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,,exit,(int __status),xexit,(__status))
#else /* ... */
#undef __std_exit_defined
#endif /* !... */
#endif /* !__std_exit_defined */
#ifndef __std_abort_defined
#define __std_abort_defined
#ifdef __abort_defined
__NAMESPACE_GLB_USING_OR_IMPL(abort, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NORETURN void (__LIBCCALL abort)(void) { :: abort(); })
#elif __has_builtin(__builtin_abort) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_abort)
__CEIDECLARE_GCCNCX(__ATTR_NORETURN,void,,abort,(void),{ __builtin_abort(); })
#elif defined(__CRT_HAVE_abort)
__CDECLARE_VOID_GCCNCX(__ATTR_NORETURN,,abort,(void),())
#elif defined(__CRT_HAVE__ZSt9terminatev)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,,abort,(void),_ZSt9terminatev,())
#elif defined(__CRT_HAVE_terminate)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,,abort,(void),terminate,())
#elif defined(__CRT_HAVE___chk_fail)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,,abort,(void),__chk_fail,())
#elif defined(__CRT_HAVE_$Qterminate$A$AYAXXZ)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,,abort,(void),?terminate@@YAXXZ,())
#elif defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)
__NAMESPACE_STD_END
#include <libc/local/stdlib/abort.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(abort, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NORETURN void (__LIBCCALL abort)(void) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(abort))(); })
#else /* ... */
#undef __std_abort_defined
#endif /* !... */
#endif /* !__std_abort_defined */
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__exit_defined) && defined(__std_exit_defined)
#define __exit_defined
__NAMESPACE_STD_USING(exit)
#endif /* !__exit_defined && __std_exit_defined */
#if !defined(__abort_defined) && defined(__std_abort_defined)
#define __abort_defined
__NAMESPACE_STD_USING(abort)
#endif /* !__abort_defined && __std_abort_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifndef ___exit_defined
#define ___exit_defined
#if __has_builtin(__builtin__Exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE__Exit)
__CEIREDIRECT_GCCNCX(__ATTR_NORETURN,void,,_exit,(int __status),_Exit,{ __builtin__Exit(__status); })
#elif __has_builtin(__builtin__exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE__exit)
__CEIDECLARE_GCCNCX(__ATTR_NORETURN,void,,_exit,(int __status),{ __builtin__exit(__status); })
#elif defined(__CRT_HAVE__Exit)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,,_exit,(int __status),_Exit,(__status))
#elif defined(__CRT_HAVE__exit)
__CDECLARE_VOID_GCCNCX(__ATTR_NORETURN,,_exit,(int __status),(__status))
#elif defined(__CRT_HAVE_quick_exit)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,,_exit,(int __status),quick_exit,(__status))
#elif defined(__CRT_HAVE_exit)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,,_exit,(int __status),exit,(__status))
#else /* ... */
#undef ___exit_defined
#endif /* !... */
#endif /* !___exit_defined */
__CDECLARE_OPT(,uintptr_t,__NOTHROW_NCX,_beginthread,(void (__LIBDCALL *__entry)(void *__arg), __UINT32_TYPE__ __stacksz, void *__arg),(__entry,__stacksz,__arg))
__CDECLARE_OPT(,uintptr_t,__NOTHROW_NCX,_beginthreadex,(void *__sec, __UINT32_TYPE__ __stacksz, __dos_beginthreadex_entry_t __entry, void *__arg, __UINT32_TYPE__ __flags, __UINT32_TYPE__ *__threadaddr),(__sec,__stacksz,__entry,__arg,__flags,__threadaddr))
#ifdef __CRT_HAVE__endthread
__CDECLARE_VOID(,__NOTHROW_NCX,_endthread,(void),())
#elif defined(__CRT_HAVE__endthreadex)
#include <libc/local/process/_endthread.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_endthread, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL _endthread)(void) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_endthread))(); })
#endif /* ... */
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,_endthreadex,(__UINT32_TYPE__ __exitcode),(__exitcode))
__CDECLARE_VOID_OPT(,,_cexit,(void),())
#ifdef __CRT_HAVE__c_exit
__CDECLARE_VOID(,,_c_exit,(void),())
#else /* __CRT_HAVE__c_exit */
#include <libc/local/process/_c_exit.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_c_exit, __FORCELOCAL __ATTR_ARTIFICIAL void (__LIBCCALL _c_exit)(void) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_c_exit))(); })
#endif /* !__CRT_HAVE__c_exit */
#ifndef ___tls_callback_type_defined
#define ___tls_callback_type_defined
#ifdef __NO_ATTR_STDCALL
typedef void (__ATTR_MSABI *_tls_callback_type)(void * /*???*/, __ULONG32_TYPE__ /*???*/, void * /*???*/);
#else /* __NO_ATTR_STDCALL */
typedef void (__ATTR_STDCALL *_tls_callback_type)(void * /*???*/, __ULONG32_TYPE__ /*???*/, void * /*???*/);
#endif /* !__NO_ATTR_STDCALL */
#endif /* !___tls_callback_type_defined */
#ifdef __CRT_HAVE__register_thread_local_exe_atexit_callback
__LIBC __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBDCALL _register_thread_local_exe_atexit_callback)(_tls_callback_type __callback) __CASMNAME_SAME("_register_thread_local_exe_atexit_callback");
#endif /* __CRT_HAVE__register_thread_local_exe_atexit_callback */
#ifdef __CRT_HAVE_getpid
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,_getpid,(void),getpid,())
#elif defined(__CRT_HAVE__getpid)
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,_getpid,(void),())
#elif defined(__CRT_HAVE___getpid)
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,_getpid,(void),__getpid,())
#elif defined(__CRT_HAVE___libc_getpid)
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,_getpid,(void),__libc_getpid,())
#endif /* ... */
#if __has_builtin(__builtin_execv) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execv)
/* >> execv(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CEIREDIRECT(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_execv,(char const *__restrict __path, char const *const *___argv),execv,{ return __builtin_execv(__path, (char *const *)___argv); })
#elif defined(__CRT_HAVE_execv)
/* >> execv(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_execv,(char const *__restrict __path, char const *const *___argv),execv,(__path,___argv))
#elif defined(__CRT_HAVE__execv)
/* >> execv(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CDECLARE(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_execv,(char const *__restrict __path, char const *const *___argv),(__path,___argv))
#else /* ... */
#include <libc/template/environ.h>
#if (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__LOCAL_environ)
#include <libc/local/unistd/execv.h>
/* >> execv(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL _execv)(char const *__restrict __path, char const *const *___argv) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execv))(__path, (__TARGV)___argv); }
#endif /* (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) && __LOCAL_environ */
#endif /* !... */
#if __has_builtin(__builtin_execvp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execvp)
/* >> execvp(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CEIREDIRECT(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_execvp,(char const *__restrict __file, char const *const *___argv),execvp,{ return __builtin_execvp(__file, (char *const *)___argv); })
#elif defined(__CRT_HAVE_execvp)
/* >> execvp(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_execvp,(char const *__restrict __file, char const *const *___argv),execvp,(__file,___argv))
#elif defined(__CRT_HAVE__execvp)
/* >> execvp(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CDECLARE(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,_execvp,(char const *__restrict __file, char const *const *___argv),(__file,___argv))
#else /* ... */
#include <libc/template/environ.h>
#include <hybrid/__alloca.h>
#if (defined(__CRT_HAVE_execvpe) || defined(__CRT_HAVE__execvpe) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__hybrid_alloca))) && defined(__LOCAL_environ)
#include <libc/local/unistd/execvp.h>
/* >> execvp(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL _execvp)(char const *__restrict __file, char const *const *___argv) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execvp))(__file, (__TARGV)___argv); }
#endif /* (__CRT_HAVE_execvpe || __CRT_HAVE__execvpe || ((__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) && __hybrid_alloca)) && __LOCAL_environ */
#endif /* !... */
#if __has_builtin(__builtin_execve) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execve)
/* >> execve(2)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CEIREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_NCX,_execve,(char const *__restrict __path, char const *const *___argv, char const *const *___envp),execve,{ return __builtin_execve(__path, (char *const *)___argv, (char *const *)___envp); })
#elif defined(__CRT_HAVE_execve)
/* >> execve(2)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_NCX,_execve,(char const *__restrict __path, char const *const *___argv, char const *const *___envp),execve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE__execve)
/* >> execve(2)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CDECLARE(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_NCX,_execve,(char const *__restrict __path, char const *const *___argv, char const *const *___envp),(__path,___argv,___envp))
#elif defined(__CRT_HAVE___execve)
/* >> execve(2)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_NCX,_execve,(char const *__restrict __path, char const *const *___argv, char const *const *___envp),__execve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE___libc_execve)
/* >> execve(2)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_NCX,_execve,(char const *__restrict __path, char const *const *___argv, char const *const *___envp),__libc_execve,(__path,___argv,___envp))
#endif /* ... */
#ifdef __CRT_HAVE_execvpe
/* >> execvpe(3)
 * Replace the  calling process  with the  application  image referred  to by  `file'  and
 * execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_NCX,_execvpe,(char const *__restrict __file, char const *const *___argv, char const *const *___envp),execvpe,(__file,___argv,___envp))
#elif defined(__CRT_HAVE__execvpe)
/* >> execvpe(3)
 * Replace the  calling process  with the  application  image referred  to by  `file'  and
 * execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CDECLARE(__ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3),int,__NOTHROW_NCX,_execvpe,(char const *__restrict __file, char const *const *___argv, char const *const *___envp),(__file,___argv,___envp))
#else /* ... */
#include <hybrid/__alloca.h>
#include <libc/template/environ.h>
#if (defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__hybrid_alloca)
#include <libc/local/unistd/execvpe.h>
/* >> execvpe(3)
 * Replace the  calling process  with the  application  image referred  to by  `file'  and
 * execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN(2) __ATTR_IN(3) int __NOTHROW_NCX(__LIBCCALL _execvpe)(char const *__restrict __file, char const *const *___argv, char const *const *___envp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execvpe))(__file, (__TARGV)___argv, (__TENVP)___envp); }
#endif /* (__CRT_HAVE_getenv || __LOCAL_environ) && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) && __hybrid_alloca */
#endif /* !... */
#if __has_builtin(__builtin_execl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execl) && __has_builtin(__builtin_va_arg_pack)
/* >> execl(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
__CEIREDIRECT(__ATTR_SENTINEL __ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_execl,(char const *__restrict __path, char const *__args, ...),execl,{ return __builtin_execl(__path, __args, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_execl)
/* >> execl(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
__LIBC __ATTR_SENTINEL __ATTR_IN(1) __ATTR_IN_OPT(2) int __NOTHROW_RPC(__VLIBCCALL _execl)(char const *__restrict __path, char const *__args, ...) __CASMNAME("execl");
#elif defined(__CRT_HAVE__execl)
/* >> execl(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
__LIBC __ATTR_SENTINEL __ATTR_IN(1) __ATTR_IN_OPT(2) int __NOTHROW_RPC(__VLIBCCALL _execl)(char const *__restrict __path, char const *__args, ...) __CASMNAME_SAME("_execl");
#else /* ... */
#include <libc/template/environ.h>
#if defined(__CRT_HAVE_execv) || defined(__CRT_HAVE__execv) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__LOCAL_environ))
#include <libc/local/unistd/execl.h>
/* >> execl(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
#define _execl(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execl))(__VA_ARGS__)
#endif /* __CRT_HAVE_execv || __CRT_HAVE__execv || ((__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) && __LOCAL_environ) */
#endif /* !... */
#if __has_builtin(__builtin_execlp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execlp) && __has_builtin(__builtin_va_arg_pack)
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
__CEIREDIRECT(__ATTR_SENTINEL __ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_execlp,(char const *__restrict __file, char const *__args, ...),execlp,{ return __builtin_execlp(__file, __args, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_execlp)
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
__LIBC __ATTR_SENTINEL __ATTR_IN(1) __ATTR_IN_OPT(2) int __NOTHROW_RPC(__VLIBCCALL _execlp)(char const *__restrict __file, char const *__args, ...) __CASMNAME("execlp");
#elif defined(__CRT_HAVE__execlp)
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
__LIBC __ATTR_SENTINEL __ATTR_IN(1) __ATTR_IN_OPT(2) int __NOTHROW_RPC(__VLIBCCALL _execlp)(char const *__restrict __file, char const *__args, ...) __CASMNAME_SAME("_execlp");
#else /* ... */
#include <libc/template/environ.h>
#include <hybrid/__alloca.h>
#if defined(__CRT_HAVE_execvp) || defined(__CRT_HAVE__execvp) || ((defined(__CRT_HAVE_execvpe) || defined(__CRT_HAVE__execvpe) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__hybrid_alloca))) && defined(__LOCAL_environ))
#include <libc/local/unistd/execlp.h>
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
#define _execlp(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execlp))(__VA_ARGS__)
#endif /* __CRT_HAVE_execvp || __CRT_HAVE__execvp || ((__CRT_HAVE_execvpe || __CRT_HAVE__execvpe || ((__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) && __hybrid_alloca)) && __LOCAL_environ) */
#endif /* !... */
#if __has_builtin(__builtin_execle) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execle) && __has_builtin(__builtin_va_arg_pack)
/* >> execle(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
__CEIREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2) __ATTR_SENTINEL_O(1),int,__NOTHROW_RPC,_execle,(char const *__restrict __path, char const *__args, ...),execle,{ return __builtin_execle(__path, __args, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_execle)
/* >> execle(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
__LIBC __ATTR_IN(1) __ATTR_IN_OPT(2) __ATTR_SENTINEL_O(1) int __NOTHROW_RPC(__VLIBCCALL _execle)(char const *__restrict __path, char const *__args, ...) __CASMNAME("execle");
#elif defined(__CRT_HAVE__execle)
/* >> execle(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
__LIBC __ATTR_IN(1) __ATTR_IN_OPT(2) __ATTR_SENTINEL_O(1) int __NOTHROW_RPC(__VLIBCCALL _execle)(char const *__restrict __path, char const *__args, ...) __CASMNAME_SAME("_execle");
#elif defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)
#include <libc/local/unistd/execle.h>
/* >> execle(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
#define _execle(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execle))(__VA_ARGS__)
#endif /* ... */
#ifdef __CRT_HAVE_execlpe
/* >> execlpe(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
__LIBC __ATTR_IN(1) __ATTR_IN_OPT(2) __ATTR_SENTINEL_O(1) int __NOTHROW_RPC(__VLIBCCALL _execlpe)(char const *__restrict __file, char const *__args, ...) __CASMNAME("execlpe");
#elif defined(__CRT_HAVE__execlpe)
/* >> execlpe(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
__LIBC __ATTR_IN(1) __ATTR_IN_OPT(2) __ATTR_SENTINEL_O(1) int __NOTHROW_RPC(__VLIBCCALL _execlpe)(char const *__restrict __file, char const *__args, ...) __CASMNAME_SAME("_execlpe");
#else /* ... */
#include <hybrid/__alloca.h>
#include <libc/template/environ.h>
#if defined(__CRT_HAVE_execvpe) || defined(__CRT_HAVE__execvpe) || ((defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__hybrid_alloca))
#include <libc/local/unistd/execlpe.h>
/* >> execlpe(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
#define _execlpe(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execlpe))(__VA_ARGS__)
#endif /* __CRT_HAVE_execvpe || __CRT_HAVE__execvpe || ((__CRT_HAVE_getenv || __LOCAL_environ) && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) && __hybrid_alloca) */
#endif /* !... */
#ifdef __CRT_HAVE_cwait
/* >> cwait(3)
 * DOS name for `waitpid(2)', except that `action' is ignored. Use
 * this function together with the `spawn(3)' family of functions.
 * @return: pid: Child process exited.
 * @return: -1:  Error (s.a. `errno') */
__CREDIRECT(__ATTR_OUT_OPT(1),__pid_t,__NOTHROW_RPC,_cwait,(int *__tstat, __pid_t __pid, __STDC_INT_AS_UINT_T __action),cwait,(__tstat,__pid,__action))
#elif defined(__CRT_HAVE__cwait)
/* >> cwait(3)
 * DOS name for `waitpid(2)', except that `action' is ignored. Use
 * this function together with the `spawn(3)' family of functions.
 * @return: pid: Child process exited.
 * @return: -1:  Error (s.a. `errno') */
__CDECLARE(__ATTR_OUT_OPT(1),__pid_t,__NOTHROW_RPC,_cwait,(int *__tstat, __pid_t __pid, __STDC_INT_AS_UINT_T __action),(__tstat,__pid,__action))
#elif defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)
#include <libc/local/process/cwait.h>
/* >> cwait(3)
 * DOS name for `waitpid(2)', except that `action' is ignored. Use
 * this function together with the `spawn(3)' family of functions.
 * @return: pid: Child process exited.
 * @return: -1:  Error (s.a. `errno') */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT_OPT(1) __pid_t __NOTHROW_RPC(__LIBCCALL _cwait)(int *__tstat, __pid_t __pid, __STDC_INT_AS_UINT_T __action) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cwait))(__tstat, __pid, __action); }
#endif /* ... */
#ifdef __CRT_HAVE_spawnv
__CREDIRECT(__ATTR_IN(2) __ATTR_IN(3),intptr_t,__NOTHROW_NCX,_spawnv,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, char const *const *___argv),spawnv,(__mode,__path,___argv))
#elif defined(__CRT_HAVE__spawnv)
__CDECLARE(__ATTR_IN(2) __ATTR_IN(3),intptr_t,__NOTHROW_NCX,_spawnv,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, char const *const *___argv),(__mode,__path,___argv))
#else /* ... */
#include <libc/template/environ.h>
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#include <asm/os/vfork.h>
#include <asm/os/features.h>
#if (defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)))) && (defined(__CRT_HAVE_fexecve) || (defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)))) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))) && defined(__LOCAL_environ)
#include <libc/local/process/spawnv.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_IN(3) intptr_t __NOTHROW_NCX(__LIBCCALL _spawnv)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, char const *const *___argv) { return (__INTPTR_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnv))(__mode, __path, (__TARGV)___argv); }
#endif /* (__CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close))) && (__CRT_HAVE_fexecve || (__OS_HAVE_PROCFS_SELF_FD && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve))) && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))))) && __LOCAL_environ */
#endif /* !... */
#ifdef __CRT_HAVE_spawnvp
__CREDIRECT(__ATTR_IN(2) __ATTR_IN(3),intptr_t,__NOTHROW_NCX,_spawnvp,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, char const *const *___argv),spawnvp,(__mode,__file,___argv))
#elif defined(__CRT_HAVE__spawnvp)
__CDECLARE(__ATTR_IN(2) __ATTR_IN(3),intptr_t,__NOTHROW_NCX,_spawnvp,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, char const *const *___argv),(__mode,__file,___argv))
#else /* ... */
#include <libc/template/environ.h>
#include <hybrid/__alloca.h>
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#include <asm/os/vfork.h>
#include <asm/os/features.h>
#if (defined(__CRT_HAVE_spawnvpe) || defined(__CRT_HAVE__spawnvpe) || ((defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)))) && (defined(__CRT_HAVE_fexecve) || (defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)))) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))) && defined(__hybrid_alloca))) && defined(__LOCAL_environ)
#include <libc/local/process/spawnvp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_IN(3) intptr_t __NOTHROW_NCX(__LIBCCALL _spawnvp)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, char const *const *___argv) { return (__INTPTR_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnvp))(__mode, __file, (__TARGV)___argv); }
#endif /* (__CRT_HAVE_spawnvpe || __CRT_HAVE__spawnvpe || ((__CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close))) && (__CRT_HAVE_fexecve || (__OS_HAVE_PROCFS_SELF_FD && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve))) && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))))) && __hybrid_alloca)) && __LOCAL_environ */
#endif /* !... */
#ifdef __CRT_HAVE_spawnve
__CREDIRECT(__ATTR_IN(2) __ATTR_IN(3) __ATTR_IN(4),intptr_t,__NOTHROW_NCX,_spawnve,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, char const *const *___argv, char const *const *___envp),spawnve,(__mode,__path,___argv,___envp))
#elif defined(__CRT_HAVE__spawnve)
__CDECLARE(__ATTR_IN(2) __ATTR_IN(3) __ATTR_IN(4),intptr_t,__NOTHROW_NCX,_spawnve,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, char const *const *___argv, char const *const *___envp),(__mode,__path,___argv,___envp))
#else /* ... */
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#include <asm/os/vfork.h>
#include <asm/os/features.h>
#if (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)))) && (defined(__CRT_HAVE_fexecve) || (defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)))) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid))))
#include <libc/local/process/spawnve.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_IN(3) __ATTR_IN(4) intptr_t __NOTHROW_NCX(__LIBCCALL _spawnve)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, char const *const *___argv, char const *const *___envp) { return (__INTPTR_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnve))(__mode, __path, (__TARGV)___argv, (__TENVP)___envp); }
#endif /* (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close))) && (__CRT_HAVE_fexecve || (__OS_HAVE_PROCFS_SELF_FD && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve))) && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))) */
#endif /* !... */
#ifdef __CRT_HAVE_spawnvpe
__CREDIRECT(__ATTR_IN(2) __ATTR_IN(3) __ATTR_IN(4),intptr_t,__NOTHROW_NCX,_spawnvpe,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, char const *const *___argv, char const *const *___envp),spawnvpe,(__mode,__file,___argv,___envp))
#elif defined(__CRT_HAVE__spawnvpe)
__CDECLARE(__ATTR_IN(2) __ATTR_IN(3) __ATTR_IN(4),intptr_t,__NOTHROW_NCX,_spawnvpe,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, char const *const *___argv, char const *const *___envp),(__mode,__file,___argv,___envp))
#else /* ... */
#include <hybrid/__alloca.h>
#include <libc/template/environ.h>
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#include <asm/os/vfork.h>
#include <asm/os/features.h>
#if (defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)))) && (defined(__CRT_HAVE_fexecve) || (defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)))) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))) && defined(__hybrid_alloca)
#include <libc/local/process/spawnvpe.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_IN(3) __ATTR_IN(4) intptr_t __NOTHROW_NCX(__LIBCCALL _spawnvpe)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, char const *const *___argv, char const *const *___envp) { return (__INTPTR_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnvpe))(__mode, __file, (__TARGV)___argv, (__TENVP)___envp); }
#endif /* (__CRT_HAVE_getenv || __LOCAL_environ) && (__CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close))) && (__CRT_HAVE_fexecve || (__OS_HAVE_PROCFS_SELF_FD && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve))) && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))))) && __hybrid_alloca */
#endif /* !... */
#ifdef __CRT_HAVE_spawnl
__LIBC __ATTR_SENTINEL __ATTR_IN(2) __ATTR_IN_OPT(3) intptr_t __NOTHROW_NCX(__VLIBCCALL _spawnl)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, char const *__args, ...) __CASMNAME("spawnl");
#elif defined(__CRT_HAVE__spawnl)
__LIBC __ATTR_SENTINEL __ATTR_IN(2) __ATTR_IN_OPT(3) intptr_t __NOTHROW_NCX(__VLIBCCALL _spawnl)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, char const *__args, ...) __CASMNAME_SAME("_spawnl");
#else /* ... */
#include <libc/template/environ.h>
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#include <asm/os/vfork.h>
#include <asm/os/features.h>
#if defined(__CRT_HAVE_spawnv) || defined(__CRT_HAVE__spawnv) || ((defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)))) && (defined(__CRT_HAVE_fexecve) || (defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)))) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))) && defined(__LOCAL_environ))
#include <libc/local/process/spawnl.h>
#define _spawnl(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnl))(__VA_ARGS__)
#endif /* __CRT_HAVE_spawnv || __CRT_HAVE__spawnv || ((__CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close))) && (__CRT_HAVE_fexecve || (__OS_HAVE_PROCFS_SELF_FD && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve))) && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))))) && __LOCAL_environ) */
#endif /* !... */
#ifdef __CRT_HAVE_spawnlp
__LIBC __ATTR_SENTINEL __ATTR_IN(2) __ATTR_IN_OPT(3) intptr_t __NOTHROW_NCX(__VLIBCCALL _spawnlp)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, char const *__args, ...) __CASMNAME("spawnlp");
#elif defined(__CRT_HAVE__spawnlp)
__LIBC __ATTR_SENTINEL __ATTR_IN(2) __ATTR_IN_OPT(3) intptr_t __NOTHROW_NCX(__VLIBCCALL _spawnlp)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, char const *__args, ...) __CASMNAME_SAME("_spawnlp");
#else /* ... */
#include <libc/template/environ.h>
#include <hybrid/__alloca.h>
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#include <asm/os/vfork.h>
#include <asm/os/features.h>
#if defined(__CRT_HAVE_spawnvp) || defined(__CRT_HAVE__spawnvp) || ((defined(__CRT_HAVE_spawnvpe) || defined(__CRT_HAVE__spawnvpe) || ((defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)))) && (defined(__CRT_HAVE_fexecve) || (defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)))) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))) && defined(__hybrid_alloca))) && defined(__LOCAL_environ))
#include <libc/local/process/spawnlp.h>
#define _spawnlp(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnlp))(__VA_ARGS__)
#endif /* __CRT_HAVE_spawnvp || __CRT_HAVE__spawnvp || ((__CRT_HAVE_spawnvpe || __CRT_HAVE__spawnvpe || ((__CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close))) && (__CRT_HAVE_fexecve || (__OS_HAVE_PROCFS_SELF_FD && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve))) && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))))) && __hybrid_alloca)) && __LOCAL_environ) */
#endif /* !... */
#ifdef __CRT_HAVE_spawnle
__LIBC __ATTR_IN(2) __ATTR_IN_OPT(3) __ATTR_SENTINEL_O(1) intptr_t __NOTHROW_NCX(__VLIBCCALL _spawnle)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, char const *__args, ...) __CASMNAME("spawnle");
#elif defined(__CRT_HAVE__spawnle)
__LIBC __ATTR_IN(2) __ATTR_IN_OPT(3) __ATTR_SENTINEL_O(1) intptr_t __NOTHROW_NCX(__VLIBCCALL _spawnle)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, char const *__args, ...) __CASMNAME_SAME("_spawnle");
#else /* ... */
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#include <asm/os/vfork.h>
#include <asm/os/features.h>
#if defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)))) && (defined(__CRT_HAVE_fexecve) || (defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)))) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))
#include <libc/local/process/spawnle.h>
#define _spawnle(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnle))(__VA_ARGS__)
#endif /* __CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close))) && (__CRT_HAVE_fexecve || (__OS_HAVE_PROCFS_SELF_FD && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve))) && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid)))) */
#endif /* !... */
#ifdef __CRT_HAVE_spawnlpe
__LIBC __ATTR_IN(2) __ATTR_IN_OPT(3) __ATTR_SENTINEL_O(1) intptr_t __NOTHROW_NCX(__VLIBCCALL _spawnlpe)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, char const *__args, ...) __CASMNAME("spawnlpe");
#elif defined(__CRT_HAVE__spawnlpe)
__LIBC __ATTR_IN(2) __ATTR_IN_OPT(3) __ATTR_SENTINEL_O(1) intptr_t __NOTHROW_NCX(__VLIBCCALL _spawnlpe)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, char const *__args, ...) __CASMNAME_SAME("_spawnlpe");
#else /* ... */
#include <hybrid/__alloca.h>
#include <libc/template/environ.h>
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#include <asm/os/vfork.h>
#include <asm/os/features.h>
#if defined(__CRT_HAVE_spawnvpe) || defined(__CRT_HAVE__spawnvpe) || ((defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)))) && (defined(__CRT_HAVE_fexecve) || (defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)))) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))) && defined(__hybrid_alloca))
#include <libc/local/process/spawnlpe.h>
#define _spawnlpe(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnlpe))(__VA_ARGS__)
#endif /* __CRT_HAVE_spawnvpe || __CRT_HAVE__spawnvpe || ((__CRT_HAVE_getenv || __LOCAL_environ) && (__CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close))) && (__CRT_HAVE_fexecve || (__OS_HAVE_PROCFS_SELF_FD && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve))) && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))))) && __hybrid_alloca) */
#endif /* !... */
#ifndef __system_defined
#define __system_defined
#ifdef __std_system_defined
/* >> system(3)
 * Execute a given `command' on the system interpreter (as in `sh -c $command')
 * The   return   value   is   the   exit   status   after   running  `command'
 * When `command' is `NULL' only check if a system interpreter is available.
 * When  no   system   interpreter   is  available,   `127'   is   returned. */
__NAMESPACE_STD_USING(system)
#elif defined(__CRT_HAVE_system)
/* >> system(3)
 * Execute a given `command' on the system interpreter (as in `sh -c $command')
 * The   return   value   is   the   exit   status   after   running  `command'
 * When `command' is `NULL' only check if a system interpreter is available.
 * When  no   system   interpreter   is  available,   `127'   is   returned. */
__CDECLARE(__ATTR_IN_OPT(1),int,__NOTHROW_RPC,system,(char const *__command),(__command))
#elif defined(__CRT_HAVE___libc_system)
/* >> system(3)
 * Execute a given `command' on the system interpreter (as in `sh -c $command')
 * The   return   value   is   the   exit   status   after   running  `command'
 * When `command' is `NULL' only check if a system interpreter is available.
 * When  no   system   interpreter   is  available,   `127'   is   returned. */
__CREDIRECT(__ATTR_IN_OPT(1),int,__NOTHROW_RPC,system,(char const *__command),__libc_system,(__command))
#else /* ... */
#include <libc/template/environ.h>
#if (defined(__CRT_HAVE_shexec) || defined(__CRT_HAVE_execl) || defined(__CRT_HAVE__execl) || defined(__CRT_HAVE_execv) || defined(__CRT_HAVE__execv) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__LOCAL_environ))) && (defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork) || defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork))
#include <libc/local/stdlib/system.h>
/* >> system(3)
 * Execute a given `command' on the system interpreter (as in `sh -c $command')
 * The   return   value   is   the   exit   status   after   running  `command'
 * When `command' is `NULL' only check if a system interpreter is available.
 * When  no   system   interpreter   is  available,   `127'   is   returned. */
__NAMESPACE_LOCAL_USING_OR_IMPL(system, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(1) int __NOTHROW_RPC(__LIBCCALL system)(char const *__command) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(system))(__command); })
#else /* (__CRT_HAVE_shexec || __CRT_HAVE_execl || __CRT_HAVE__execl || __CRT_HAVE_execv || __CRT_HAVE__execv || ((__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) && __LOCAL_environ)) && (__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid) && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork || __CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) */
#undef __system_defined
#endif /* (!__CRT_HAVE_shexec && !__CRT_HAVE_execl && !__CRT_HAVE__execl && !__CRT_HAVE_execv && !__CRT_HAVE__execv && ((!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve) || !__LOCAL_environ)) || (!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid) || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork && !__CRT_HAVE_fork && !__CRT_HAVE___fork && !__CRT_HAVE___libc_fork) */
#endif /* !... */
#endif /* !__system_defined */

#ifdef __CRT_HAVE__loaddll
__CDECLARE(__ATTR_IN_OPT(1),intptr_t,,_loaddll,(char __KOS_FIXED_CONST *__file),(__file))
#else /* __CRT_HAVE__loaddll */
#include <libdl/asm/dlfcn.h>
#ifdef __CRT_HAVE_dlopen
#include <libc/local/process/_loaddll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_loaddll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(1) intptr_t (__LIBCCALL _loaddll)(char __KOS_FIXED_CONST *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_loaddll))(__file); })
#endif /* __CRT_HAVE_dlopen */
#endif /* !__CRT_HAVE__loaddll */
#ifdef __CRT_HAVE__unloaddll
__CDECLARE(,int,,_unloaddll,(intptr_t __hnd),(__hnd))
#else /* __CRT_HAVE__unloaddll */
#include <libc/local/process/_unloaddll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_unloaddll, __FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL _unloaddll)(intptr_t __hnd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_unloaddll))(__hnd); })
#endif /* !__CRT_HAVE__unloaddll */

#ifndef ____procfun_defined
#define ____procfun_defined
typedef int (*__procfun)(void);
#endif /* !____procfun_defined */
#ifdef __CRT_HAVE__getdllprocaddr
__CDECLARE(__ATTR_IN_OPT(2),__procfun,,_getdllprocaddr,(intptr_t __hnd, char __KOS_FIXED_CONST *__symname, intptr_t __ord),(__hnd,__symname,__ord))
#else /* __CRT_HAVE__getdllprocaddr */
#include <libdl/asm/dlfcn.h>
#ifdef __CRT_HAVE_dlsym
#include <libc/local/process/_getdllprocaddr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_getdllprocaddr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(2) __procfun (__LIBCCALL _getdllprocaddr)(intptr_t __hnd, char __KOS_FIXED_CONST *__symname, intptr_t __ord) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_getdllprocaddr))(__hnd, __symname, __ord); })
#endif /* __CRT_HAVE_dlsym */
#endif /* !__CRT_HAVE__getdllprocaddr */
#endif /* __USE_DOS */

__SYSDECL_END
#endif /* __CC__ */

#ifdef __USE_KOS
#if defined(_WCHAR_H) && !defined(_PARTS_WCHAR_PROCESS_H)
#include <parts/wchar/process.h>
#endif /* _WCHAR_H && !_PARTS_WCHAR_PROCESS_H */
#endif /* __USE_KOS */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_PROCESS_H)
#include <parts/uchar/process.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_PROCESS_H */
#endif /* __USE_UTF */

#endif /* !_PROCESS_H */
