/* HASH CRC-32:0x7efc951f */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Cygwin (/winsup/cygwin/include/process.h) */
/* (#) Portability: DJGPP  (/include/process.h) */
/* (#) Portability: MSVC   (/include/process.h) */
/* (#) Portability: MinGW  (/mingw-w64-headers/crt/process.h) */
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

__SYSDECL_BEGIN

/* `MODE' argument values for spawn() functions. */
#ifdef __P_WAIT
#define P_WAIT    __P_WAIT    /* Wait for the process to terminate, and return its exit status */
#endif /* __P_WAIT */
#ifdef __P_NOWAIT
#define P_NOWAIT  __P_NOWAIT  /* Spawn the process asynchronously, and return its PID */
#endif /* __P_NOWAIT */
#ifdef __P_OVERLAY
#define P_OVERLAY __P_OVERLAY /* Don't spawn, but rather try to exec() the new program */
#endif /* __P_OVERLAY */
#ifdef __P_NOWAITO
#define P_NOWAITO __P_NOWAITO /* Same as `P_NOWAIT' */
#endif /* __P_NOWAITO */
#ifdef __P_DETACH
#define P_DETACH  __P_DETACH  /* Create the new process as detached and return `0' */
#endif /* __P_DETACH */

/* `ACTION' argument values for cwait() functions. */
#ifdef __WAIT_CHILD
#define WAIT_CHILD      __WAIT_CHILD      /* Ignored */
#endif /* __WAIT_CHILD */
#ifdef __WAIT_GRANDCHILD
#define WAIT_GRANDCHILD __WAIT_GRANDCHILD /* Ignored */
#endif /* __WAIT_GRANDCHILD */


#ifndef __TARGV
#ifdef __USE_DOS
#define __TARGV  char const *const *___argv
#define __TENVP  char const *const *___envp
#else /* __USE_DOS */
#define __TARGV  char *const ___argv[__restrict_arr]
#define __TENVP  char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS */
#endif /* !__TARGV */

/* DOS */
#ifdef __USE_DOS
#define _P_WAIT          P_WAIT
#define _P_NOWAIT        P_NOWAIT
#define _P_OVERLAY       P_OVERLAY
#define _P_NOWAITO       P_NOWAITO
#define _P_DETACH        P_DETACH
#define _OLD_P_OVERLAY   P_OVERLAY
#define _WAIT_CHILD      WAIT_CHILD
#define _WAIT_GRANDCHILD WAIT_GRANDCHILD
#define OLD_P_OVERLAY    _OLD_P_OVERLAY


#ifdef __CC__

#ifndef __intptr_t_defined
#define __intptr_t_defined 1
typedef __intptr_t intptr_t;
#endif /* !__intptr_t_defined */
#ifndef __uintptr_t_defined
#define __uintptr_t_defined 1
typedef __uintptr_t uintptr_t;
#endif /* !__uintptr_t_defined */
#ifndef __wchar_t_defined
#define __wchar_t_defined 1
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

#ifndef ____dos_beginthread_entry_t_defined
#define ____dos_beginthread_entry_t_defined 1
typedef void (__LIBDCALL *__dos_beginthread_entry_t)(void *__arg);
#endif /* !____dos_beginthread_entry_t_defined */
#ifndef ____dos_beginthreadex_entry_t_defined
#define ____dos_beginthreadex_entry_t_defined 1
#ifdef __NO_ATTR_STDCALL
typedef __UINT32_TYPE__ (__LIBDCALL *__dos_beginthreadex_entry_t)(void *__arg);
#else /* __NO_ATTR_STDCALL */
typedef __UINT32_TYPE__ (__ATTR_STDCALL *__dos_beginthreadex_entry_t)(void *__arg);
#endif /* !__NO_ATTR_STDCALL */
#endif /* !____dos_beginthreadex_entry_t_defined */

__CDECLARE_OPT(,uintptr_t,__NOTHROW_NCX,_beginthread,(__dos_beginthread_entry_t __entry, __UINT32_TYPE__ __stacksz, void *__arg),(__entry,__stacksz,__arg))
__CDECLARE_OPT(,uintptr_t,__NOTHROW_NCX,_beginthreadex,(void *__sec, __UINT32_TYPE__ __stacksz, __dos_beginthreadex_entry_t __entry, void *__arg, __UINT32_TYPE__ __flags, __UINT32_TYPE__ *__threadaddr),(__sec,__stacksz,__entry,__arg,__flags,__threadaddr))
#ifdef __CRT_HAVE__endthread
__CDECLARE_VOID(,__NOTHROW_NCX,_endthread,(void),())
#elif defined(__CRT_HAVE__endthreadex)
#include <libc/local/process/_endthread.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_endthread, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL _endthread)(void) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_endthread))(); })
#endif /* ... */
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,_endthreadex,(__UINT32_TYPE__ __exitcode),(__exitcode))

#ifndef _CRT_TERMINATE_DEFINED
#define _CRT_TERMINATE_DEFINED 1
#ifndef __exit_defined
#define __exit_defined 1
#ifdef __std_exit_defined
__NAMESPACE_STD_USING(exit)
#elif __has_builtin(__builtin_exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exit)
__CEIDECLARE_GCCNCX(__ATTR_NORETURN,void,__THROWING,exit,(int __status),{ return __builtin_exit(__status); })
#elif defined(__CRT_HAVE_exit)
__CDECLARE_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,exit,(int __status),(__status))
#elif defined(__CRT_HAVE_quick_exit)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,exit,(int __status),quick_exit,(__status))
#elif defined(__CRT_HAVE__exit)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,exit,(int __status),_exit,(__status))
#elif defined(__CRT_HAVE__Exit)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,exit,(int __status),_Exit,(__status))
#else /* ... */
#undef __exit_defined
#endif /* !... */
#endif /* !__exit_defined */
#ifndef __abort_defined
#define __abort_defined 1
#ifdef __std_abort_defined
__NAMESPACE_STD_USING(abort)
#elif __has_builtin(__builtin_abort) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_abort)
__CEIDECLARE_GCCNCX(__ATTR_NORETURN,void,__THROWING,abort,(void),{ return __builtin_abort(); })
#elif defined(__CRT_HAVE_abort)
__CDECLARE_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,abort,(void),())
#elif defined(__CRT_HAVE__ZSt9terminatev)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,abort,(void),_ZSt9terminatev,())
#elif defined(__CRT_HAVE_$Qterminate$A$AYAXXZ)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,abort,(void),?terminate@@YAXXZ,())
#elif defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)
#include <libc/local/stdlib/abort.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(abort, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NORETURN void (__LIBCCALL abort)(void) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(abort))(); })
#else /* ... */
#undef __abort_defined
#endif /* !... */
#endif /* !__abort_defined */
#ifndef ___exit_defined
#define ___exit_defined 1
#if __has_builtin(__builtin__Exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE__Exit)
__CEIREDIRECT_GCCNCX(__ATTR_NORETURN,void,__THROWING,_exit,(int __status),_Exit,{ return __builtin__Exit(__status); })
#elif __has_builtin(__builtin__exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE__exit)
__CEIDECLARE_GCCNCX(__ATTR_NORETURN,void,__THROWING,_exit,(int __status),{ __builtin__exit(__status); })
#elif defined(__CRT_HAVE__Exit)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,_exit,(int __status),_Exit,(__status))
#elif defined(__CRT_HAVE__exit)
__CDECLARE_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,_exit,(int __status),(__status))
#elif defined(__CRT_HAVE_quick_exit)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,_exit,(int __status),quick_exit,(__status))
#elif defined(__CRT_HAVE_exit)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,_exit,(int __status),exit,(__status))
#else /* ... */
#undef ___exit_defined
#endif /* !... */
#endif /* !___exit_defined */
#endif /* !_CRT_TERMINATE_DEFINED */
__CDECLARE_VOID_OPT(,__THROWING,_cexit,(void),())
#ifdef __CRT_HAVE__c_exit
__CDECLARE_VOID(,__THROWING,_c_exit,(void),())
#else /* __CRT_HAVE__c_exit */
#include <libc/local/process/_c_exit.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_c_exit, __FORCELOCAL __ATTR_ARTIFICIAL void (__LIBCCALL _c_exit)(void) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_c_exit))(); })
#endif /* !__CRT_HAVE__c_exit */
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
#endif /* ... */
#if __has_builtin(__builtin_execv) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execv)
/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CEIREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,_execv,(char const *__restrict __path, __TARGV),execv,{ return __builtin_execv(__path, (char *const *)___argv); })
#elif defined(__CRT_HAVE_execv)
/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,_execv,(char const *__restrict __path, __TARGV),execv,(__path,___argv))
#elif defined(__CRT_HAVE__execv)
/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,_execv,(char const *__restrict __path, __TARGV),(__path,___argv))
#else /* ... */
#include <libc/local/environ.h>
#if (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve)) && defined(__LOCAL_environ)
#include <libc/local/unistd/execv.h>
/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL _execv)(char const *__restrict __path, __TARGV) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execv))(__path, ___argv); }
#endif /* (__CRT_HAVE_execve || __CRT_HAVE__execve) && __LOCAL_environ */
#endif /* !... */
#if __has_builtin(__builtin_execvp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execvp)
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CEIREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,_execvp,(char const *__restrict __file, __TARGV),execvp,{ return __builtin_execvp(__file, (char *const *)___argv); })
#elif defined(__CRT_HAVE_execvp)
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,_execvp,(char const *__restrict __file, __TARGV),execvp,(__file,___argv))
#elif defined(__CRT_HAVE__execvp)
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,_execvp,(char const *__restrict __file, __TARGV),(__file,___argv))
#else /* ... */
#include <libc/local/environ.h>
#include <hybrid/__alloca.h>
#if (defined(__CRT_HAVE_execvpe) || defined(__CRT_HAVE__execvpe) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve)) && defined(__hybrid_alloca))) && defined(__LOCAL_environ)
#include <libc/local/unistd/execvp.h>
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL _execvp)(char const *__restrict __file, __TARGV) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execvp))(__file, ___argv); }
#endif /* (__CRT_HAVE_execvpe || __CRT_HAVE__execvpe || ((__CRT_HAVE_execve || __CRT_HAVE__execve) && __hybrid_alloca)) && __LOCAL_environ */
#endif /* !... */
#if __has_builtin(__builtin_execve) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execve)
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CEIREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,_execve,(char const *__restrict __path, __TARGV, __TENVP),execve,{ return __builtin_execve(__path, (char *const *)___argv, (char *const *)___envp); })
#elif defined(__CRT_HAVE_execve)
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,_execve,(char const *__restrict __path, __TARGV, __TENVP),execve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE__execve)
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,_execve,(char const *__restrict __path, __TARGV, __TENVP),(__path,___argv,___envp))
#endif /* ... */
#ifdef __CRT_HAVE_execvpe
/* >> execvpe(3)
 * Replace the calling process with the application image referred to by `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,_execvpe,(char const *__restrict __file, __TARGV, __TENVP),execvpe,(__file,___argv,___envp))
#elif defined(__CRT_HAVE__execvpe)
/* >> execvpe(3)
 * Replace the calling process with the application image referred to by `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,_execvpe,(char const *__restrict __file, __TARGV, __TENVP),(__file,___argv,___envp))
#else /* ... */
#include <hybrid/__alloca.h>
#include <libc/local/environ.h>
#if (defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve)) && defined(__hybrid_alloca)
#include <libc/local/unistd/execvpe.h>
/* >> execvpe(3)
 * Replace the calling process with the application image referred to by `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) int __NOTHROW_RPC(__LIBCCALL _execvpe)(char const *__restrict __file, __TARGV, __TENVP) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execvpe))(__file, ___argv, ___envp); }
#endif /* (__CRT_HAVE_getenv || __LOCAL_environ) && (__CRT_HAVE_execve || __CRT_HAVE__execve) && __hybrid_alloca */
#endif /* !... */
#if __has_builtin(__builtin_execl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execl) && __has_builtin(__builtin_va_arg_pack)
/* >> execl(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
__CEIREDIRECT(__ATTR_SENTINEL __ATTR_NONNULL((1)),int,__NOTHROW_RPC,_execl,(char const *__restrict __path, char const *__args, ...),execl,{ return __builtin_execl(__path, __args, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_execl)
/* >> execl(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL _execl)(char const *__restrict __path, char const *__args, ...) __CASMNAME("execl");
#elif defined(__CRT_HAVE__execl)
/* >> execl(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL _execl)(char const *__restrict __path, char const *__args, ...) __CASMNAME_SAME("_execl");
#else /* ... */
#include <libc/local/environ.h>
#if defined(__CRT_HAVE_execv) || defined(__CRT_HAVE__execv) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve)) && defined(__LOCAL_environ))
#include <libc/local/unistd/execl.h>
/* >> execl(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
#define _execl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execl))
#endif /* __CRT_HAVE_execv || __CRT_HAVE__execv || ((__CRT_HAVE_execve || __CRT_HAVE__execve) && __LOCAL_environ) */
#endif /* !... */
#if __has_builtin(__builtin_execlp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execlp) && __has_builtin(__builtin_va_arg_pack)
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
__CEIREDIRECT(__ATTR_SENTINEL __ATTR_NONNULL((1)),int,__NOTHROW_RPC,_execlp,(char const *__restrict __file, char const *__args, ...),execlp,{ return __builtin_execlp(__file, __args, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_execlp)
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL _execlp)(char const *__restrict __file, char const *__args, ...) __CASMNAME("execlp");
#elif defined(__CRT_HAVE__execlp)
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL _execlp)(char const *__restrict __file, char const *__args, ...) __CASMNAME_SAME("_execlp");
#else /* ... */
#include <libc/local/environ.h>
#include <hybrid/__alloca.h>
#if defined(__CRT_HAVE_execvp) || defined(__CRT_HAVE__execvp) || ((defined(__CRT_HAVE_execvpe) || defined(__CRT_HAVE__execvpe) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve)) && defined(__hybrid_alloca))) && defined(__LOCAL_environ))
#include <libc/local/unistd/execlp.h>
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
#define _execlp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execlp))
#endif /* __CRT_HAVE_execvp || __CRT_HAVE__execvp || ((__CRT_HAVE_execvpe || __CRT_HAVE__execvpe || ((__CRT_HAVE_execve || __CRT_HAVE__execve) && __hybrid_alloca)) && __LOCAL_environ) */
#endif /* !... */
#if __has_builtin(__builtin_execle) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execle) && __has_builtin(__builtin_va_arg_pack)
/* >> execle(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
__CEIREDIRECT(__ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)),int,__NOTHROW_RPC,_execle,(char const *__restrict __path, char const *__args, ...),execle,{ return __builtin_execle(__path, __args, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_execle)
/* >> execle(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL _execle)(char const *__restrict __path, char const *__args, ...) __CASMNAME("execle");
#elif defined(__CRT_HAVE__execle)
/* >> execle(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL _execle)(char const *__restrict __path, char const *__args, ...) __CASMNAME_SAME("_execle");
#elif defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve)
#include <libc/local/unistd/execle.h>
/* >> execle(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
#define _execle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execle))
#endif /* ... */
#ifdef __CRT_HAVE_execlpe
/* >> execlpe(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list, and setting `environ' to a `char **' passed after the NULL sentinel */
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL _execlpe)(char const *__restrict __file, char const *__args, ...) __CASMNAME("execlpe");
#elif defined(__CRT_HAVE__execlpe)
/* >> execlpe(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list, and setting `environ' to a `char **' passed after the NULL sentinel */
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL _execlpe)(char const *__restrict __file, char const *__args, ...) __CASMNAME_SAME("_execlpe");
#else /* ... */
#include <hybrid/__alloca.h>
#include <libc/local/environ.h>
#if defined(__CRT_HAVE_execvpe) || defined(__CRT_HAVE__execvpe) || ((defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve)) && defined(__hybrid_alloca))
#include <libc/local/unistd/execlpe.h>
/* >> execlpe(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list, and setting `environ' to a `char **' passed after the NULL sentinel */
#define _execlpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execlpe))
#endif /* __CRT_HAVE_execvpe || __CRT_HAVE__execvpe || ((__CRT_HAVE_getenv || __LOCAL_environ) && (__CRT_HAVE_execve || __CRT_HAVE__execve) && __hybrid_alloca) */
#endif /* !... */
#ifdef __CRT_HAVE_cwait
__CREDIRECT(,__pid_t,__NOTHROW_RPC,_cwait,(int *__tstat, __pid_t __pid, __STDC_INT_AS_UINT_T __action),cwait,(__tstat,__pid,__action))
#elif defined(__CRT_HAVE__cwait)
__CDECLARE(,__pid_t,__NOTHROW_RPC,_cwait,(int *__tstat, __pid_t __pid, __STDC_INT_AS_UINT_T __action),(__tstat,__pid,__action))
#elif defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)
#include <libc/local/process/cwait.h>
__FORCELOCAL __ATTR_ARTIFICIAL __pid_t __NOTHROW_RPC(__LIBCCALL _cwait)(int *__tstat, __pid_t __pid, __STDC_INT_AS_UINT_T __action) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cwait))(__tstat, __pid, __action); }
#endif /* ... */
#ifdef __CRT_HAVE_spawnv
__CREDIRECT(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_spawnv,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, __TARGV),spawnv,(__mode,__path,___argv))
#elif defined(__CRT_HAVE__spawnv)
__CDECLARE(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_spawnv,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, __TARGV),(__mode,__path,___argv))
#else /* ... */
#include <libc/local/environ.h>
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <asm/os/vfork.h>
#if (defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)))) && defined(__CRT_HAVE_fexecve) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))) && defined(__LOCAL_environ)
#include <libc/local/process/spawnv.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__LIBCCALL _spawnv)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, __TARGV) { return (__INTPTR_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnv))(__mode, __path, ___argv); }
#endif /* (__CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close))) && __CRT_HAVE_fexecve && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))))) && __LOCAL_environ */
#endif /* !... */
#ifdef __CRT_HAVE_spawnvp
__CREDIRECT(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_spawnvp,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, __TARGV),spawnvp,(__mode,__file,___argv))
#elif defined(__CRT_HAVE__spawnvp)
__CDECLARE(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_spawnvp,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, __TARGV),(__mode,__file,___argv))
#else /* ... */
#include <libc/local/environ.h>
#include <hybrid/__alloca.h>
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <asm/os/vfork.h>
#if (defined(__CRT_HAVE_spawnvpe) || defined(__CRT_HAVE__spawnvpe) || ((defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)))) && defined(__CRT_HAVE_fexecve) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))) && defined(__hybrid_alloca))) && defined(__LOCAL_environ)
#include <libc/local/process/spawnvp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__LIBCCALL _spawnvp)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, __TARGV) { return (__INTPTR_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnvp))(__mode, __file, ___argv); }
#endif /* (__CRT_HAVE_spawnvpe || __CRT_HAVE__spawnvpe || ((__CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close))) && __CRT_HAVE_fexecve && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))))) && __hybrid_alloca)) && __LOCAL_environ */
#endif /* !... */
#ifdef __CRT_HAVE_spawnve
__CREDIRECT(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_spawnve,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, __TARGV, __TENVP),spawnve,(__mode,__path,___argv,___envp))
#elif defined(__CRT_HAVE__spawnve)
__CDECLARE(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_spawnve,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, __TARGV, __TENVP),(__mode,__path,___argv,___envp))
#else /* ... */
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <asm/os/vfork.h>
#if (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)))) && defined(__CRT_HAVE_fexecve) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid))))
#include <libc/local/process/spawnve.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__LIBCCALL _spawnve)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, __TARGV, __TENVP) { return (__INTPTR_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnve))(__mode, __path, ___argv, ___envp); }
#endif /* (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close))) && __CRT_HAVE_fexecve && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))) */
#endif /* !... */
#ifdef __CRT_HAVE_spawnvpe
__CREDIRECT(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_spawnvpe,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, __TARGV, __TENVP),spawnvpe,(__mode,__file,___argv,___envp))
#elif defined(__CRT_HAVE__spawnvpe)
__CDECLARE(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_spawnvpe,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, __TARGV, __TENVP),(__mode,__file,___argv,___envp))
#else /* ... */
#include <hybrid/__alloca.h>
#include <libc/local/environ.h>
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <asm/os/vfork.h>
#if (defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)))) && defined(__CRT_HAVE_fexecve) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))) && defined(__hybrid_alloca)
#include <libc/local/process/spawnvpe.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__LIBCCALL _spawnvpe)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, __TARGV, __TENVP) { return (__INTPTR_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnvpe))(__mode, __file, ___argv, ___envp); }
#endif /* (__CRT_HAVE_getenv || __LOCAL_environ) && (__CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close))) && __CRT_HAVE_fexecve && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))))) && __hybrid_alloca */
#endif /* !... */
#ifdef __CRT_HAVE_spawnl
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _spawnl)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, char const *__args, ...) __CASMNAME("spawnl");
#elif defined(__CRT_HAVE__spawnl)
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _spawnl)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, char const *__args, ...) __CASMNAME_SAME("_spawnl");
#else /* ... */
#include <libc/local/environ.h>
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <asm/os/vfork.h>
#if defined(__CRT_HAVE_spawnv) || defined(__CRT_HAVE__spawnv) || ((defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)))) && defined(__CRT_HAVE_fexecve) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))) && defined(__LOCAL_environ))
#include <libc/local/process/spawnl.h>
#define _spawnl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnl))
#endif /* __CRT_HAVE_spawnv || __CRT_HAVE__spawnv || ((__CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close))) && __CRT_HAVE_fexecve && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))))) && __LOCAL_environ) */
#endif /* !... */
#ifdef __CRT_HAVE_spawnlp
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _spawnlp)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, char const *__args, ...) __CASMNAME("spawnlp");
#elif defined(__CRT_HAVE__spawnlp)
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _spawnlp)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, char const *__args, ...) __CASMNAME_SAME("_spawnlp");
#else /* ... */
#include <libc/local/environ.h>
#include <hybrid/__alloca.h>
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <asm/os/vfork.h>
#if defined(__CRT_HAVE_spawnvp) || defined(__CRT_HAVE__spawnvp) || ((defined(__CRT_HAVE_spawnvpe) || defined(__CRT_HAVE__spawnvpe) || ((defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)))) && defined(__CRT_HAVE_fexecve) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))) && defined(__hybrid_alloca))) && defined(__LOCAL_environ))
#include <libc/local/process/spawnlp.h>
#define _spawnlp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnlp))
#endif /* __CRT_HAVE_spawnvp || __CRT_HAVE__spawnvp || ((__CRT_HAVE_spawnvpe || __CRT_HAVE__spawnvpe || ((__CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close))) && __CRT_HAVE_fexecve && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))))) && __hybrid_alloca)) && __LOCAL_environ) */
#endif /* !... */
#ifdef __CRT_HAVE_spawnle
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _spawnle)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, char const *__args, ...) __CASMNAME("spawnle");
#elif defined(__CRT_HAVE__spawnle)
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _spawnle)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, char const *__args, ...) __CASMNAME_SAME("_spawnle");
#else /* ... */
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <asm/os/vfork.h>
#if defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)))) && defined(__CRT_HAVE_fexecve) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))
#include <libc/local/process/spawnle.h>
#define _spawnle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnle))
#endif /* __CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close))) && __CRT_HAVE_fexecve && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid)))) */
#endif /* !... */
#ifdef __CRT_HAVE_spawnlpe
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _spawnlpe)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, char const *__args, ...) __CASMNAME("spawnlpe");
#elif defined(__CRT_HAVE__spawnlpe)
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _spawnlpe)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, char const *__args, ...) __CASMNAME_SAME("_spawnlpe");
#else /* ... */
#include <hybrid/__alloca.h>
#include <libc/local/environ.h>
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <asm/os/vfork.h>
#if defined(__CRT_HAVE_spawnvpe) || defined(__CRT_HAVE__spawnvpe) || ((defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)))) && defined(__CRT_HAVE_fexecve) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))) && defined(__hybrid_alloca))
#include <libc/local/process/spawnlpe.h>
#define _spawnlpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnlpe))
#endif /* __CRT_HAVE_spawnvpe || __CRT_HAVE__spawnvpe || ((__CRT_HAVE_getenv || __LOCAL_environ) && (__CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close))) && __CRT_HAVE_fexecve && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))))) && __hybrid_alloca) */
#endif /* !... */
#ifndef __system_defined
#define __system_defined 1
#ifdef __std_system_defined
/* >> system(3)
 * Execute a given `command' on the system interpreter (as in `sh -c $command')
 * The return value is the exit status after running `command'
 * When `command' is `NULL' only check if a system interpreter is available.
 * When no system interpreter is available, `127' is returned. */
__NAMESPACE_STD_USING(system)
#elif defined(__CRT_HAVE_system)
/* >> system(3)
 * Execute a given `command' on the system interpreter (as in `sh -c $command')
 * The return value is the exit status after running `command'
 * When `command' is `NULL' only check if a system interpreter is available.
 * When no system interpreter is available, `127' is returned. */
__CDECLARE(,int,__NOTHROW_RPC,system,(char const *__command),(__command))
#else /* ... */
#include <libc/local/environ.h>
#if (defined(__CRT_HAVE_shexec) || defined(__CRT_HAVE_execl) || defined(__CRT_HAVE__execl) || defined(__CRT_HAVE_execv) || defined(__CRT_HAVE__execv) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve)) && defined(__LOCAL_environ))) && (defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork))
#include <libc/local/stdlib/system.h>
/* >> system(3)
 * Execute a given `command' on the system interpreter (as in `sh -c $command')
 * The return value is the exit status after running `command'
 * When `command' is `NULL' only check if a system interpreter is available.
 * When no system interpreter is available, `127' is returned. */
__NAMESPACE_LOCAL_USING_OR_IMPL(system, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL system)(char const *__command) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(system))(__command); })
#else /* (__CRT_HAVE_shexec || __CRT_HAVE_execl || __CRT_HAVE__execl || __CRT_HAVE_execv || __CRT_HAVE__execv || ((__CRT_HAVE_execve || __CRT_HAVE__execve) && __LOCAL_environ)) && (__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid) && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE_fork || __CRT_HAVE___fork) */
#undef __system_defined
#endif /* (!__CRT_HAVE_shexec && !__CRT_HAVE_execl && !__CRT_HAVE__execl && !__CRT_HAVE_execv && !__CRT_HAVE__execv && ((!__CRT_HAVE_execve && !__CRT_HAVE__execve) || !__LOCAL_environ)) || (!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid) || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE_fork && !__CRT_HAVE___fork) */
#endif /* !... */
#endif /* !__system_defined */



#ifdef __CRT_HAVE__loaddll
__CDECLARE(,intptr_t,__THROWING,_loaddll,(char __KOS_FIXED_CONST *__file),(__file))
#else /* __CRT_HAVE__loaddll */
#include <libdl/asm/dlfcn.h>
#ifdef __CRT_HAVE_dlopen
#include <libc/local/process/_loaddll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_loaddll, __FORCELOCAL __ATTR_ARTIFICIAL intptr_t (__LIBCCALL _loaddll)(char __KOS_FIXED_CONST *__file) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_loaddll))(__file); })
#endif /* __CRT_HAVE_dlopen */
#endif /* !__CRT_HAVE__loaddll */
#ifdef __CRT_HAVE__unloaddll
__CDECLARE(,int,__THROWING,_unloaddll,(intptr_t __hnd),(__hnd))
#else /* __CRT_HAVE__unloaddll */
#include <libc/local/process/_unloaddll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_unloaddll, __FORCELOCAL __ATTR_ARTIFICIAL int (__LIBCCALL _unloaddll)(intptr_t __hnd) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_unloaddll))(__hnd); })
#endif /* !__CRT_HAVE__unloaddll */

#ifndef ____procfun_defined
#define ____procfun_defined 1
typedef int (*__procfun)(void);
#endif /* !____procfun_defined */
#ifdef __CRT_HAVE__getdllprocaddr
__CDECLARE(,__procfun,__THROWING,_getdllprocaddr,(intptr_t __hnd, char __KOS_FIXED_CONST *__symname, intptr_t __ord),(__hnd,__symname,__ord))
#else /* __CRT_HAVE__getdllprocaddr */
#include <libdl/asm/dlfcn.h>
#ifdef __CRT_HAVE_dlsym
#include <libc/local/process/_getdllprocaddr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_getdllprocaddr, __FORCELOCAL __ATTR_ARTIFICIAL __procfun (__LIBCCALL _getdllprocaddr)(intptr_t __hnd, char __KOS_FIXED_CONST *__symname, intptr_t __ord) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_getdllprocaddr))(__hnd, __symname, __ord); })
#endif /* __CRT_HAVE_dlsym */
#endif /* !__CRT_HAVE__getdllprocaddr */

#ifndef __wchar_t_defined
#define __wchar_t_defined 1
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

#ifndef __intptr_t_defined
#define __intptr_t_defined 1
typedef __intptr_t intptr_t;
#endif /* !__intptr_t_defined */

#ifndef __TWARGV
#ifdef __USE_DOS
#define __TWARGV wchar_t const *const *__restrict ___argv
#define __TWENVP wchar_t const *const *__restrict ___envp
#else /* __USE_DOS */
#define __TWARGV wchar_t *const ___argv[__restrict_arr]
#define __TWENVP wchar_t *const ___envp[__restrict_arr]
#endif /* !__USE_DOS */
#endif /* !__TWARGV */


#ifndef _WPROCESS_DEFINED
#define _WPROCESS_DEFINED 1
#ifdef __CRT_HAVE_wexecv
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,_wexecv,(wchar_t const *__restrict __path, __TWARGV),wexecv,(__path,___argv))
#elif defined(__CRT_HAVE__wexecv)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,_wexecv,(wchar_t const *__restrict __path, __TWARGV),(__path,___argv))
#endif /* ... */
#ifdef __CRT_HAVE_wexecvp
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,_wexecvp,(wchar_t const *__restrict __file, __TWARGV),wexecvp,(__path,___argv))
#elif defined(__CRT_HAVE__wexecvp)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,_wexecvp,(wchar_t const *__restrict __file, __TWARGV),(__path,___argv))
#endif /* ... */
#ifdef __CRT_HAVE_wexecve
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,_wexecve,(wchar_t const *__restrict __path, __TWARGV, __TWENVP),wexecve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE__wexecve)
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,_wexecve,(wchar_t const *__restrict __path, __TWARGV, __TWENVP),(__path,___argv,___envp))
#endif /* ... */
#ifdef __CRT_HAVE_wexecvpe
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,_wexecvpe,(wchar_t const *__restrict __file, __TWARGV, __TWENVP),wexecvpe,(__path,___argv,___envp))
#elif defined(__CRT_HAVE__wexecvpe)
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,_wexecvpe,(wchar_t const *__restrict __file, __TWARGV, __TWENVP),(__path,___argv,___envp))
#endif /* ... */
#ifdef __CRT_HAVE_wexecl
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL _wexecl)(wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME("wexecl");
#elif defined(__CRT_HAVE__wexecl)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL _wexecl)(wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME_SAME("_wexecl");
#elif defined(__CRT_HAVE_wexecv) || defined(__CRT_HAVE__wexecv)
#include <libc/local/parts.wchar.process/wexecl.h>
#define _wexecl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexecl))
#endif /* ... */
#ifdef __CRT_HAVE_wexeclp
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL _wexeclp)(wchar_t const *__restrict __file, wchar_t const *__args, ...) __CASMNAME("wexeclp");
#elif defined(__CRT_HAVE__wexeclp)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL _wexeclp)(wchar_t const *__restrict __file, wchar_t const *__args, ...) __CASMNAME_SAME("_wexeclp");
#elif defined(__CRT_HAVE_wexecvp) || defined(__CRT_HAVE__wexecvp)
#include <libc/local/parts.wchar.process/wexeclp.h>
#define _wexeclp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexeclp))
#endif /* ... */
#ifdef __CRT_HAVE_wexecle
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL _wexecle)(wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME("wexecle");
#elif defined(__CRT_HAVE__wexecle)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL _wexecle)(wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME_SAME("_wexecle");
#elif defined(__CRT_HAVE_wexecve) || defined(__CRT_HAVE__wexecve)
#include <libc/local/parts.wchar.process/wexecle.h>
#define _wexecle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexecle))
#endif /* ... */
#ifdef __CRT_HAVE_wexeclpe
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL _wexeclpe)(wchar_t const *__restrict __file, wchar_t const *__args, ...) __CASMNAME("wexeclpe");
#elif defined(__CRT_HAVE__wexeclpe)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL _wexeclpe)(wchar_t const *__restrict __file, wchar_t const *__args, ...) __CASMNAME_SAME("_wexeclpe");
#elif defined(__CRT_HAVE_wexecvpe) || defined(__CRT_HAVE__wexecvpe)
#include <libc/local/parts.wchar.process/wexeclpe.h>
#define _wexeclpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexeclpe))
#endif /* ... */
#ifdef __CRT_HAVE_wspawnv
__CREDIRECT(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_wspawnv,(__STDC_INT_AS_UINT_T __mode, wchar_t const *__restrict __path, __TWARGV),wspawnv,(__mode,__path,___argv))
#elif defined(__CRT_HAVE__wspawnv)
__CDECLARE(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_wspawnv,(__STDC_INT_AS_UINT_T __mode, wchar_t const *__restrict __path, __TWARGV),(__mode,__path,___argv))
#endif /* ... */
#ifdef __CRT_HAVE_wspawnvp
__CREDIRECT(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_wspawnvp,(__STDC_INT_AS_UINT_T __mode, wchar_t const *__restrict __path, __TWARGV),wspawnvp,(__mode,__path,___argv))
#elif defined(__CRT_HAVE__wspawnvp)
__CDECLARE(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_wspawnvp,(__STDC_INT_AS_UINT_T __mode, wchar_t const *__restrict __path, __TWARGV),(__mode,__path,___argv))
#endif /* ... */
#ifdef __CRT_HAVE_wspawnve
__CREDIRECT(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_wspawnve,(__STDC_INT_AS_UINT_T __mode, wchar_t const *__restrict __path, __TWARGV, __TWENVP),wspawnve,(__mode,__path,___argv,___envp))
#elif defined(__CRT_HAVE__wspawnve)
__CDECLARE(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_wspawnve,(__STDC_INT_AS_UINT_T __mode, wchar_t const *__restrict __path, __TWARGV, __TWENVP),(__mode,__path,___argv,___envp))
#endif /* ... */
#ifdef __CRT_HAVE_wspawnvpe
__CREDIRECT(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_wspawnvpe,(__STDC_INT_AS_UINT_T __mode, wchar_t const *__restrict __path, __TWARGV, __TWENVP),wspawnvpe,(__mode,__path,___argv,___envp))
#elif defined(__CRT_HAVE__wspawnvpe)
__CDECLARE(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_wspawnvpe,(__STDC_INT_AS_UINT_T __mode, wchar_t const *__restrict __path, __TWARGV, __TWENVP),(__mode,__path,___argv,___envp))
#endif /* ... */
#ifdef __CRT_HAVE_wspawnl
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _wspawnl)(__STDC_INT_AS_UINT_T __mode, wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME("wspawnl");
#elif defined(__CRT_HAVE__wspawnl)
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _wspawnl)(__STDC_INT_AS_UINT_T __mode, wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME_SAME("_wspawnl");
#elif defined(__CRT_HAVE_wspawnv) || defined(__CRT_HAVE__wspawnv)
#include <libc/local/parts.wchar.process/wspawnl.h>
#define _wspawnl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnl))
#endif /* ... */
#ifdef __CRT_HAVE_wspawnlp
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _wspawnlp)(__STDC_INT_AS_UINT_T __mode, wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME("wspawnlp");
#elif defined(__CRT_HAVE__wspawnlp)
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _wspawnlp)(__STDC_INT_AS_UINT_T __mode, wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME_SAME("_wspawnlp");
#elif defined(__CRT_HAVE_wspawnvp) || defined(__CRT_HAVE__wspawnvp)
#include <libc/local/parts.wchar.process/wspawnlp.h>
#define _wspawnlp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnlp))
#endif /* ... */
#ifdef __CRT_HAVE_wspawnle
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _wspawnle)(__STDC_INT_AS_UINT_T __mode, wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME("wspawnle");
#elif defined(__CRT_HAVE__wspawnle)
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _wspawnle)(__STDC_INT_AS_UINT_T __mode, wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME_SAME("_wspawnle");
#elif defined(__CRT_HAVE_wspawnve) || defined(__CRT_HAVE__wspawnve)
#include <libc/local/parts.wchar.process/wspawnle.h>
#define _wspawnle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnle))
#endif /* ... */
#ifdef __CRT_HAVE_wspawnlpe
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _wspawnlpe)(__STDC_INT_AS_UINT_T __mode, wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME("wspawnlpe");
#elif defined(__CRT_HAVE__wspawnlpe)
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _wspawnlpe)(__STDC_INT_AS_UINT_T __mode, wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME_SAME("_wspawnlpe");
#elif defined(__CRT_HAVE_wspawnvpe) || defined(__CRT_HAVE__wspawnvpe)
#include <libc/local/parts.wchar.process/wspawnlpe.h>
#define _wspawnlpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnlpe))
#endif /* ... */
#endif /* !_WPROCESS_DEFINED */

#ifndef _CRT_WSYSTEM_DEFINED
#define _CRT_WSYSTEM_DEFINED 1
#ifdef __CRT_HAVE_wsystem
__CREDIRECT(,int,__NOTHROW_RPC,_wsystem,(wchar_t const *__cmd),wsystem,(__cmd))
#elif defined(__CRT_HAVE__wsystem)
__CDECLARE(,int,__NOTHROW_RPC,_wsystem,(wchar_t const *__cmd),(__cmd))
#else /* ... */
#undef _CRT_WSYSTEM_DEFINED
#endif /* !... */
#endif /* !_CRT_WSYSTEM_DEFINED */

#endif /* __CC__ */
#endif /* __USE_DOS */


#if defined(__USE_DOS) || defined(__USE_KOS)
#ifndef __getpid_defined
#define __getpid_defined 1
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
#else /* ... */
#undef __getpid_defined
#endif /* !... */
#endif /* !__getpid_defined */
#ifndef __execv_defined
#define __execv_defined 1
#if __has_builtin(__builtin_execv) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execv)
/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CEIDECLARE_GCCNCX(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,execv,(char const *__restrict __path, __TARGV),{ return __builtin_execv(__path, (char *const *)___argv); })
#elif defined(__CRT_HAVE_execv)
/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CDECLARE_GCCNCX(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,execv,(char const *__restrict __path, __TARGV),(__path,___argv))
#elif defined(__CRT_HAVE__execv)
/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT_GCCNCX(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,execv,(char const *__restrict __path, __TARGV),_execv,(__path,___argv))
#else /* ... */
#include <libc/local/environ.h>
#if (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve)) && defined(__LOCAL_environ)
#include <libc/local/unistd/execv.h>
/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__NAMESPACE_LOCAL_USING_OR_IMPL(execv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL execv)(char const *__restrict __path, __TARGV) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execv))(__path, ___argv); })
#else /* (__CRT_HAVE_execve || __CRT_HAVE__execve) && __LOCAL_environ */
#undef __execv_defined
#endif /* (!__CRT_HAVE_execve && !__CRT_HAVE__execve) || !__LOCAL_environ */
#endif /* !... */
#endif /* !__execv_defined */
#ifndef __execvp_defined
#define __execvp_defined 1
#if __has_builtin(__builtin_execvp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execvp)
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CEIDECLARE_GCCNCX(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,execvp,(char const *__restrict __file, __TARGV),{ return __builtin_execvp(__file, (char *const *)___argv); })
#elif defined(__CRT_HAVE_execvp)
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CDECLARE_GCCNCX(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,execvp,(char const *__restrict __file, __TARGV),(__file,___argv))
#elif defined(__CRT_HAVE__execvp)
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT_GCCNCX(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,execvp,(char const *__restrict __file, __TARGV),_execvp,(__file,___argv))
#else /* ... */
#include <libc/local/environ.h>
#include <hybrid/__alloca.h>
#if (defined(__CRT_HAVE_execvpe) || defined(__CRT_HAVE__execvpe) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve)) && defined(__hybrid_alloca))) && defined(__LOCAL_environ)
#include <libc/local/unistd/execvp.h>
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__NAMESPACE_LOCAL_USING_OR_IMPL(execvp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL execvp)(char const *__restrict __file, __TARGV) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execvp))(__file, ___argv); })
#else /* (__CRT_HAVE_execvpe || __CRT_HAVE__execvpe || ((__CRT_HAVE_execve || __CRT_HAVE__execve) && __hybrid_alloca)) && __LOCAL_environ */
#undef __execvp_defined
#endif /* (!__CRT_HAVE_execvpe && !__CRT_HAVE__execvpe && ((!__CRT_HAVE_execve && !__CRT_HAVE__execve) || !__hybrid_alloca)) || !__LOCAL_environ */
#endif /* !... */
#endif /* !__execvp_defined */
#ifndef __execve_defined
#define __execve_defined 1
#if __has_builtin(__builtin_execve) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execve)
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CEIDECLARE_GCCNCX(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,execve,(char const *__restrict __path, __TARGV, __TENVP),{ return __builtin_execve(__path, (char *const *)___argv, (char *const *)___envp); })
#elif defined(__CRT_HAVE_execve)
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CDECLARE_GCCNCX(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,execve,(char const *__restrict __path, __TARGV, __TENVP),(__path,___argv,___envp))
#elif defined(__CRT_HAVE__execve)
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT_GCCNCX(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,execve,(char const *__restrict __path, __TARGV, __TENVP),_execve,(__path,___argv,___envp))
#else /* ... */
#undef __execve_defined
#endif /* !... */
#endif /* !__execve_defined */
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
#include <hybrid/__alloca.h>
#include <libc/local/environ.h>
#if (defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve)) && defined(__hybrid_alloca)
#include <libc/local/unistd/execvpe.h>
/* >> execvpe(3)
 * Replace the calling process with the application image referred to by `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__NAMESPACE_LOCAL_USING_OR_IMPL(execvpe, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) int __NOTHROW_RPC(__LIBCCALL execvpe)(char const *__restrict __file, __TARGV, __TENVP) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execvpe))(__file, ___argv, ___envp); })
#else /* (__CRT_HAVE_getenv || __LOCAL_environ) && (__CRT_HAVE_execve || __CRT_HAVE__execve) && __hybrid_alloca */
#undef __execvpe_defined
#endif /* (!__CRT_HAVE_getenv && !__LOCAL_environ) || (!__CRT_HAVE_execve && !__CRT_HAVE__execve) || !__hybrid_alloca */
#endif /* !... */
#endif /* !__execvpe_defined */
#ifndef __execl_defined
#define __execl_defined 1
#if __has_builtin(__builtin_execl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execl) && __has_builtin(__builtin_va_arg_pack)
/* >> execl(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
__CEIDECLARE_GCCNCX(__ATTR_SENTINEL __ATTR_NONNULL((1)),int,__NOTHROW_RPC,execl,(char const *__restrict __path, char const *__args, ...),{ return __builtin_execl(__path, __args, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_execl)
/* >> execl(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
extern "C++" {
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL execl)(char const *__restrict __path, char const *__args, ...) __CASMNAME_SAME_GCCNCX("execl");
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
} /* extern "C++" */
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
#elif defined(__CRT_HAVE__execl)
/* >> execl(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
extern "C++" {
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL execl)(char const *__restrict __path, char const *__args, ...) __CASMNAME_GCCNCX("_execl");
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
} /* extern "C++" */
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
#else /* ... */
#include <libc/local/environ.h>
#if defined(__CRT_HAVE_execv) || defined(__CRT_HAVE__execv) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve)) && defined(__LOCAL_environ))
#include <libc/local/unistd/execl.h>
/* >> execl(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(execl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL execl)(char const *__restrict __path, char const *__args, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execl))(__path, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define execl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execl))
#endif /* !__cplusplus */
#else /* __CRT_HAVE_execv || __CRT_HAVE__execv || ((__CRT_HAVE_execve || __CRT_HAVE__execve) && __LOCAL_environ) */
#undef __execl_defined
#endif /* !__CRT_HAVE_execv && !__CRT_HAVE__execv && ((!__CRT_HAVE_execve && !__CRT_HAVE__execve) || !__LOCAL_environ) */
#endif /* !... */
#endif /* !__execl_defined */
#ifndef __execlp_defined
#define __execlp_defined 1
#if __has_builtin(__builtin_execlp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execlp) && __has_builtin(__builtin_va_arg_pack)
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
__CEIDECLARE_GCCNCX(__ATTR_SENTINEL __ATTR_NONNULL((1)),int,__NOTHROW_RPC,execlp,(char const *__restrict __file, char const *__args, ...),{ return __builtin_execlp(__file, __args, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_execlp)
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
extern "C++" {
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL execlp)(char const *__restrict __file, char const *__args, ...) __CASMNAME_SAME_GCCNCX("execlp");
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
} /* extern "C++" */
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
#elif defined(__CRT_HAVE__execlp)
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
extern "C++" {
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL execlp)(char const *__restrict __file, char const *__args, ...) __CASMNAME_GCCNCX("_execlp");
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
} /* extern "C++" */
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
#else /* ... */
#include <libc/local/environ.h>
#include <hybrid/__alloca.h>
#if defined(__CRT_HAVE_execvp) || defined(__CRT_HAVE__execvp) || ((defined(__CRT_HAVE_execvpe) || defined(__CRT_HAVE__execvpe) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve)) && defined(__hybrid_alloca))) && defined(__LOCAL_environ))
#include <libc/local/unistd/execlp.h>
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(execlp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL execlp)(char const *__restrict __file, char const *__args, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execlp))(__file, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define execlp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execlp))
#endif /* !__cplusplus */
#else /* __CRT_HAVE_execvp || __CRT_HAVE__execvp || ((__CRT_HAVE_execvpe || __CRT_HAVE__execvpe || ((__CRT_HAVE_execve || __CRT_HAVE__execve) && __hybrid_alloca)) && __LOCAL_environ) */
#undef __execlp_defined
#endif /* !__CRT_HAVE_execvp && !__CRT_HAVE__execvp && ((!__CRT_HAVE_execvpe && !__CRT_HAVE__execvpe && ((!__CRT_HAVE_execve && !__CRT_HAVE__execve) || !__hybrid_alloca)) || !__LOCAL_environ) */
#endif /* !... */
#endif /* !__execlp_defined */
#ifndef __execle_defined
#define __execle_defined 1
#if __has_builtin(__builtin_execle) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execle) && __has_builtin(__builtin_va_arg_pack)
/* >> execle(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
__CEIDECLARE_GCCNCX(__ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)),int,__NOTHROW_RPC,execle,(char const *__restrict __path, char const *__args, ...),{ return __builtin_execle(__path, __args, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_execle)
/* >> execle(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
extern "C++" {
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL execle)(char const *__restrict __path, char const *__args, ...) __CASMNAME_SAME_GCCNCX("execle");
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
} /* extern "C++" */
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
#elif defined(__CRT_HAVE__execle)
/* >> execle(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
extern "C++" {
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL execle)(char const *__restrict __path, char const *__args, ...) __CASMNAME_GCCNCX("_execle");
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
} /* extern "C++" */
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
#elif defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve)
#include <libc/local/unistd/execle.h>
/* >> execle(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(execle, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL execle)(char const *__restrict __path, char const *__args, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execle))(__path, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define execle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execle))
#endif /* !__cplusplus */
#else /* ... */
#undef __execle_defined
#endif /* !... */
#endif /* !__execle_defined */
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
#else /* ... */
#include <hybrid/__alloca.h>
#include <libc/local/environ.h>
#if defined(__CRT_HAVE_execvpe) || defined(__CRT_HAVE__execvpe) || ((defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve)) && defined(__hybrid_alloca))
#include <libc/local/unistd/execlpe.h>
/* >> execlpe(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list, and setting `environ' to a `char **' passed after the NULL sentinel */
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(execlpe, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL execlpe)(char const *__restrict __file, char const *__args, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execlpe))(__file, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define execlpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execlpe))
#endif /* !__cplusplus */
#else /* __CRT_HAVE_execvpe || __CRT_HAVE__execvpe || ((__CRT_HAVE_getenv || __LOCAL_environ) && (__CRT_HAVE_execve || __CRT_HAVE__execve) && __hybrid_alloca) */
#undef __execlpe_defined
#endif /* !__CRT_HAVE_execvpe && !__CRT_HAVE__execvpe && ((!__CRT_HAVE_getenv && !__LOCAL_environ) || (!__CRT_HAVE_execve && !__CRT_HAVE__execve) || !__hybrid_alloca) */
#endif /* !... */
#endif /* !__execlpe_defined */
#ifdef __CRT_HAVE_cwait
__CDECLARE(,__pid_t,__NOTHROW_RPC,cwait,(int *__tstat, __pid_t __pid, __STDC_INT_AS_UINT_T __action),(__tstat,__pid,__action))
#elif defined(__CRT_HAVE__cwait)
__CREDIRECT(,__pid_t,__NOTHROW_RPC,cwait,(int *__tstat, __pid_t __pid, __STDC_INT_AS_UINT_T __action),_cwait,(__tstat,__pid,__action))
#elif defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)
#include <libc/local/process/cwait.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(cwait, __FORCELOCAL __ATTR_ARTIFICIAL __pid_t __NOTHROW_RPC(__LIBCCALL cwait)(int *__tstat, __pid_t __pid, __STDC_INT_AS_UINT_T __action) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cwait))(__tstat, __pid, __action); })
#endif /* ... */
#ifndef __spawnv_defined
#define __spawnv_defined 1
#ifdef __CRT_HAVE_spawnv
__CDECLARE(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,spawnv,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, __TARGV),(__mode,__path,___argv))
#elif defined(__CRT_HAVE__spawnv)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,spawnv,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, __TARGV),_spawnv,(__mode,__path,___argv))
#else /* ... */
#include <libc/local/environ.h>
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <asm/os/vfork.h>
#if (defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)))) && defined(__CRT_HAVE_fexecve) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))) && defined(__LOCAL_environ)
#include <libc/local/process/spawnv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(spawnv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2, 3)) __pid_t __NOTHROW_RPC(__LIBCCALL spawnv)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, __TARGV) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnv))(__mode, __path, ___argv); })
#else /* (__CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close))) && __CRT_HAVE_fexecve && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))))) && __LOCAL_environ */
#undef __spawnv_defined
#endif /* (!__CRT_HAVE_spawnve && !__CRT_HAVE__spawnve && ((!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_fspawnve && ((!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || ((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE__pipe) || !__O_CLOEXEC || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close))) || !__CRT_HAVE_fexecve || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid))))) || !__LOCAL_environ */
#endif /* !... */
#endif /* !__spawnv_defined */
#ifndef __spawnvp_defined
#define __spawnvp_defined 1
#ifdef __CRT_HAVE_spawnvp
__CDECLARE(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,spawnvp,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, __TARGV),(__mode,__file,___argv))
#elif defined(__CRT_HAVE__spawnvp)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,spawnvp,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, __TARGV),_spawnvp,(__mode,__file,___argv))
#else /* ... */
#include <libc/local/environ.h>
#include <hybrid/__alloca.h>
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <asm/os/vfork.h>
#if (defined(__CRT_HAVE_spawnvpe) || defined(__CRT_HAVE__spawnvpe) || ((defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)))) && defined(__CRT_HAVE_fexecve) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))) && defined(__hybrid_alloca))) && defined(__LOCAL_environ)
#include <libc/local/process/spawnvp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(spawnvp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2, 3)) __pid_t __NOTHROW_RPC(__LIBCCALL spawnvp)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, __TARGV) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnvp))(__mode, __file, ___argv); })
#else /* (__CRT_HAVE_spawnvpe || __CRT_HAVE__spawnvpe || ((__CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close))) && __CRT_HAVE_fexecve && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))))) && __hybrid_alloca)) && __LOCAL_environ */
#undef __spawnvp_defined
#endif /* (!__CRT_HAVE_spawnvpe && !__CRT_HAVE__spawnvpe && ((!__CRT_HAVE_spawnve && !__CRT_HAVE__spawnve && ((!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_fspawnve && ((!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || ((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE__pipe) || !__O_CLOEXEC || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close))) || !__CRT_HAVE_fexecve || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid))))) || !__hybrid_alloca)) || !__LOCAL_environ */
#endif /* !... */
#endif /* !__spawnvp_defined */
#ifndef __spawnve_defined
#define __spawnve_defined 1
#ifdef __CRT_HAVE_spawnve
__CDECLARE(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,spawnve,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, __TARGV, __TENVP),(__mode,__path,___argv,___envp))
#elif defined(__CRT_HAVE__spawnve)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,spawnve,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, __TARGV, __TENVP),_spawnve,(__mode,__path,___argv,___envp))
#else /* ... */
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <asm/os/vfork.h>
#if (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)))) && defined(__CRT_HAVE_fexecve) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid))))
#include <libc/local/process/spawnve.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(spawnve, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2, 3, 4)) __pid_t __NOTHROW_RPC(__LIBCCALL spawnve)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, __TARGV, __TENVP) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnve))(__mode, __path, ___argv, ___envp); })
#else /* (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close))) && __CRT_HAVE_fexecve && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))) */
#undef __spawnve_defined
#endif /* (!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_fspawnve && ((!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || ((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE__pipe) || !__O_CLOEXEC || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close))) || !__CRT_HAVE_fexecve || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid))) */
#endif /* !... */
#endif /* !__spawnve_defined */
#ifndef __spawnvpe_defined
#define __spawnvpe_defined 1
#ifdef __CRT_HAVE_spawnvpe
__CDECLARE(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,spawnvpe,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, __TARGV, __TENVP),(__mode,__file,___argv,___envp))
#elif defined(__CRT_HAVE__spawnvpe)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,spawnvpe,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, __TARGV, __TENVP),_spawnvpe,(__mode,__file,___argv,___envp))
#else /* ... */
#include <hybrid/__alloca.h>
#include <libc/local/environ.h>
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <asm/os/vfork.h>
#if (defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)))) && defined(__CRT_HAVE_fexecve) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))) && defined(__hybrid_alloca)
#include <libc/local/process/spawnvpe.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(spawnvpe, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2, 3, 4)) __pid_t __NOTHROW_RPC(__LIBCCALL spawnvpe)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, __TARGV, __TENVP) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnvpe))(__mode, __file, ___argv, ___envp); })
#else /* (__CRT_HAVE_getenv || __LOCAL_environ) && (__CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close))) && __CRT_HAVE_fexecve && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))))) && __hybrid_alloca */
#undef __spawnvpe_defined
#endif /* (!__CRT_HAVE_getenv && !__LOCAL_environ) || (!__CRT_HAVE_spawnve && !__CRT_HAVE__spawnve && ((!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_fspawnve && ((!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || ((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE__pipe) || !__O_CLOEXEC || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close))) || !__CRT_HAVE_fexecve || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid))))) || !__hybrid_alloca */
#endif /* !... */
#endif /* !__spawnvpe_defined */
#ifndef __spawnl_defined
#define __spawnl_defined 1
#ifdef __CRT_HAVE_spawnl
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnl)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, char const *__args, ...) __CASMNAME_SAME("spawnl");
#elif defined(__CRT_HAVE__spawnl)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnl)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, char const *__args, ...) __CASMNAME("_spawnl");
#else /* ... */
#include <libc/local/environ.h>
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <asm/os/vfork.h>
#if defined(__CRT_HAVE_spawnv) || defined(__CRT_HAVE__spawnv) || ((defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)))) && defined(__CRT_HAVE_fexecve) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))) && defined(__LOCAL_environ))
#include <libc/local/process/spawnl.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(spawnl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnl)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, char const *__args, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnl))(__mode, __path, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define spawnl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnl))
#endif /* !__cplusplus */
#else /* __CRT_HAVE_spawnv || __CRT_HAVE__spawnv || ((__CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close))) && __CRT_HAVE_fexecve && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))))) && __LOCAL_environ) */
#undef __spawnl_defined
#endif /* !__CRT_HAVE_spawnv && !__CRT_HAVE__spawnv && ((!__CRT_HAVE_spawnve && !__CRT_HAVE__spawnve && ((!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_fspawnve && ((!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || ((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE__pipe) || !__O_CLOEXEC || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close))) || !__CRT_HAVE_fexecve || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid))))) || !__LOCAL_environ) */
#endif /* !... */
#endif /* !__spawnl_defined */
#ifndef __spawnlp_defined
#define __spawnlp_defined 1
#ifdef __CRT_HAVE_spawnlp
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnlp)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, char const *__args, ...) __CASMNAME_SAME("spawnlp");
#elif defined(__CRT_HAVE__spawnlp)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnlp)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, char const *__args, ...) __CASMNAME("_spawnlp");
#else /* ... */
#include <libc/local/environ.h>
#include <hybrid/__alloca.h>
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <asm/os/vfork.h>
#if defined(__CRT_HAVE_spawnvp) || defined(__CRT_HAVE__spawnvp) || ((defined(__CRT_HAVE_spawnvpe) || defined(__CRT_HAVE__spawnvpe) || ((defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)))) && defined(__CRT_HAVE_fexecve) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))) && defined(__hybrid_alloca))) && defined(__LOCAL_environ))
#include <libc/local/process/spawnlp.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(spawnlp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnlp)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, char const *__args, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnlp))(__mode, __file, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define spawnlp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnlp))
#endif /* !__cplusplus */
#else /* __CRT_HAVE_spawnvp || __CRT_HAVE__spawnvp || ((__CRT_HAVE_spawnvpe || __CRT_HAVE__spawnvpe || ((__CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close))) && __CRT_HAVE_fexecve && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))))) && __hybrid_alloca)) && __LOCAL_environ) */
#undef __spawnlp_defined
#endif /* !__CRT_HAVE_spawnvp && !__CRT_HAVE__spawnvp && ((!__CRT_HAVE_spawnvpe && !__CRT_HAVE__spawnvpe && ((!__CRT_HAVE_spawnve && !__CRT_HAVE__spawnve && ((!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_fspawnve && ((!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || ((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE__pipe) || !__O_CLOEXEC || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close))) || !__CRT_HAVE_fexecve || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid))))) || !__hybrid_alloca)) || !__LOCAL_environ) */
#endif /* !... */
#endif /* !__spawnlp_defined */
#ifndef __spawnle_defined
#define __spawnle_defined 1
#ifdef __CRT_HAVE_spawnle
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnle)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, char const *__args, ...) __CASMNAME_SAME("spawnle");
#elif defined(__CRT_HAVE__spawnle)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnle)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, char const *__args, ...) __CASMNAME("_spawnle");
#else /* ... */
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <asm/os/vfork.h>
#if defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)))) && defined(__CRT_HAVE_fexecve) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))
#include <libc/local/process/spawnle.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(spawnle, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnle)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, char const *__args, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnle))(__mode, __path, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define spawnle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnle))
#endif /* !__cplusplus */
#else /* __CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close))) && __CRT_HAVE_fexecve && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid)))) */
#undef __spawnle_defined
#endif /* !__CRT_HAVE_spawnve && !__CRT_HAVE__spawnve && ((!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_fspawnve && ((!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || ((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE__pipe) || !__O_CLOEXEC || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close))) || !__CRT_HAVE_fexecve || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid)))) */
#endif /* !... */
#endif /* !__spawnle_defined */
#ifndef __spawnlpe_defined
#define __spawnlpe_defined 1
#ifdef __CRT_HAVE_spawnlpe
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnlpe)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, char const *__args, ...) __CASMNAME_SAME("spawnlpe");
#elif defined(__CRT_HAVE__spawnlpe)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnlpe)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, char const *__args, ...) __CASMNAME("_spawnlpe");
#else /* ... */
#include <hybrid/__alloca.h>
#include <libc/local/environ.h>
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <asm/os/vfork.h>
#if defined(__CRT_HAVE_spawnvpe) || defined(__CRT_HAVE__spawnvpe) || ((defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)))) && defined(__CRT_HAVE_fexecve) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))) && defined(__hybrid_alloca))
#include <libc/local/process/spawnlpe.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(spawnlpe, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnlpe)(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, char const *__args, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnlpe))(__mode, __file, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define spawnlpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnlpe))
#endif /* !__cplusplus */
#else /* __CRT_HAVE_spawnvpe || __CRT_HAVE__spawnvpe || ((__CRT_HAVE_getenv || __LOCAL_environ) && (__CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close))) && __CRT_HAVE_fexecve && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))))) && __hybrid_alloca) */
#undef __spawnlpe_defined
#endif /* !__CRT_HAVE_spawnvpe && !__CRT_HAVE__spawnvpe && ((!__CRT_HAVE_getenv && !__LOCAL_environ) || (!__CRT_HAVE_spawnve && !__CRT_HAVE__spawnve && ((!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_fspawnve && ((!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || ((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE__pipe) || !__O_CLOEXEC || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close))) || !__CRT_HAVE_fexecve || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid))))) || !__hybrid_alloca) */
#endif /* !... */
#endif /* !__spawnlpe_defined */
#ifdef __USE_KOS
#ifndef __fspawnve_defined
#define __fspawnve_defined 1
#ifdef __CRT_HAVE_fspawnve
__CDECLARE(__ATTR_NONNULL((3, 4)),__pid_t,__NOTHROW_RPC,fspawnve,(__STDC_INT_AS_UINT_T __mode, __fd_t __execfd, __TARGV, __TENVP),(__mode,__path,___argv,___envp))
#elif defined(__CRT_HAVE__spawnve)
__CREDIRECT(__ATTR_NONNULL((3, 4)),__pid_t,__NOTHROW_RPC,fspawnve,(__STDC_INT_AS_UINT_T __mode, __fd_t __execfd, __TARGV, __TENVP),_spawnve,(__mode,__path,___argv,___envp))
#else /* ... */
#include <asm/os/oflags.h>
#include <asm/os/vfork.h>
#if (defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE__pipe)) && defined(O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)))) && defined(__CRT_HAVE_fexecve) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid))
#include <libc/local/process/fspawnve.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fspawnve, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((3, 4)) __pid_t __NOTHROW_RPC(__LIBCCALL fspawnve)(__STDC_INT_AS_UINT_T __mode, __fd_t __execfd, __TARGV, __TENVP) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fspawnve))(__mode, __path, ___argv, ___envp); })
#else /* (__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE__pipe) && O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close))) && __CRT_HAVE_fexecve && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid) */
#undef __fspawnve_defined
#endif /* (!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || ((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE__pipe) || !O_CLOEXEC || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close))) || !__CRT_HAVE_fexecve || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid) */
#endif /* !... */
#endif /* !__fspawnve_defined */
#endif /* __USE_KOS */
#endif /* __USE_DOS || __USE_KOS */

__SYSDECL_END

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
