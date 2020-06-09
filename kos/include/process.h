/* HASH CRC-32:0x3c7413df */
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
#ifndef _PROCESS_H
#define _PROCESS_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>

__SYSDECL_BEGIN

/* `MODE' argument values for spawn() functions. */
#define P_WAIT    0
#define P_NOWAIT  1
#define P_OVERLAY 2
#define P_NOWAITO 3
#define P_DETACH  4

/* `ACTION' argument values for cwait() functions. */
#define WAIT_CHILD      0
#define WAIT_GRANDCHILD 1


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

typedef void (__LIBCCALL *__dos_beginthread_entry_t)(void *__arg);
typedef __UINT32_TYPE__ (__ATTR_STDCALL *__dos_beginthreadex_entry_t)(void *__arg);

#ifdef __CRT_HAVE__beginthread
__CDECLARE(,uintptr_t,__NOTHROW_NCX,_beginthread,(__dos_beginthread_entry_t __entry, __UINT32_TYPE__ __stacksz, void *__arg),(__entry,__stacksz,__arg))
#endif /* __CRT_HAVE__beginthread */
#ifdef __CRT_HAVE__beginthreadex
__CDECLARE(,uintptr_t,__NOTHROW_NCX,_beginthreadex,(void *__sec, __UINT32_TYPE__ __stacksz, __dos_beginthreadex_entry_t __entry, void *__arg, __UINT32_TYPE__ __flags, __UINT32_TYPE__ *__threadaddr),(__sec,__stacksz,__entry,__arg,__flags,__threadaddr))
#endif /* __CRT_HAVE__beginthreadex */
#ifdef __CRT_HAVE__endthread
__CDECLARE_VOID(,__NOTHROW_NCX,_endthread,(void),())
#elif defined(__CRT_HAVE__endthreadex)
#include <local/process/_endthread.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_endthread, __FORCELOCAL void __NOTHROW_NCX(__LIBCCALL _endthread)(void) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_endthread))(); })
#endif /* ... */
#ifdef __CRT_HAVE__endthreadex
__CDECLARE_VOID(,__NOTHROW_NCX,_endthreadex,(__UINT32_TYPE__ __exitcode),(__exitcode))
#endif /* __CRT_HAVE__endthreadex */

#ifndef _CRT_TERMINATE_DEFINED
#define _CRT_TERMINATE_DEFINED 1
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
#ifndef __abort_defined
#define __abort_defined 1
#ifdef __std_abort_defined
__NAMESPACE_STD_USING(abort)
#elif __has_builtin(__builtin_abort) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_abort)
__CEIDECLARE(__ATTR_NORETURN,void,__THROWING,abort,(void),{ return __builtin_abort(); })
#elif defined(__CRT_HAVE_abort)
__CDECLARE_VOID(__ATTR_NORETURN,__THROWING,abort,(void),())
#elif defined(__CRT_HAVE__ZSt9terminatev)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,abort,(void),_ZSt9terminatev,())
#elif defined(__CRT_HAVE_$Qterminate$A$AYAXXZ)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,abort,(void),?terminate@@YAXXZ,())
#else /* ... */
#undef __abort_defined
#endif /* !... */
#endif /* !__abort_defined */
#if __has_builtin(__builtin__Exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE__Exit)
__CEIREDIRECT(__ATTR_NORETURN,void,__THROWING,_exit,(int __status),_Exit,{ return __builtin__Exit(__status); })
#elif defined(__CRT_HAVE__Exit)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,_exit,(int __status),_Exit,(__status))
#elif defined(__CRT_HAVE__exit)
__CDECLARE_VOID(__ATTR_NORETURN,__THROWING,_exit,(int __status),(__status))
#elif defined(__CRT_HAVE_quick_exit)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,_exit,(int __status),quick_exit,(__status))
#elif defined(__CRT_HAVE_exit)
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,_exit,(int __status),exit,(__status))
#endif /* ... */
#endif /* !_CRT_TERMINATE_DEFINED */
#ifdef __CRT_HAVE__cexit
__CDECLARE_VOID(,__THROWING,_cexit,(void),())
#endif /* __CRT_HAVE__cexit */
#ifdef __CRT_HAVE__c_exit
__CDECLARE_VOID(,__THROWING,_c_exit,(void),())
#else /* __CRT_HAVE__c_exit */
#include <local/process/_c_exit.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_c_exit, __FORCELOCAL void (__LIBCCALL _c_exit)(void) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_c_exit))(); })
#endif /* !__CRT_HAVE__c_exit */
#ifndef ___getpid_defined
#define ___getpid_defined 1
#ifdef __CRT_HAVE_getpid
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,_getpid,(void),getpid,())
#elif defined(__CRT_HAVE__getpid)
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
__CDECLARE(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,_getpid,(void),())
#elif defined(__CRT_HAVE___getpid)
/* >> getpid(2)
 * Return the PID of the calling process (that is the TID of the calling thread group's leader)
 * THIS_THREAD->LEADER->PID */
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,_getpid,(void),__getpid,())
#else /* ... */
#undef ___getpid_defined
#endif /* !... */
#endif /* !___getpid_defined */
#if __has_builtin(__builtin_execv) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execv)
/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CEIREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,_execv,(char const *__restrict __path, __TARGV),execv,{ return __builtin_execv(__path, ); })
#elif defined(__CRT_HAVE_execv)
/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,_execv,(char const *__restrict __path, __TARGV),execv,(__path,))
#elif defined(__CRT_HAVE__execv)
/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,_execv,(char const *__restrict __path, __TARGV),(__path,))
#endif /* ... */
#if __has_builtin(__builtin_execvp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execvp)
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CEIREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,_execvp,(char const *__restrict __file, __TARGV),execvp,{ return __builtin_execvp(__file, ); })
#elif defined(__CRT_HAVE_execvp)
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,_execvp,(char const *__restrict __file, __TARGV),execvp,(__file,))
#elif defined(__CRT_HAVE__execvp)
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,_execvp,(char const *__restrict __file, __TARGV),(__file,))
#endif /* ... */
#if __has_builtin(__builtin_execve) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execve)
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CEIREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,_execve,(char const *__restrict __path, __TARGV, __TENVP),execve,{ return __builtin_execve(__path, , ); })
#elif defined(__CRT_HAVE_execve)
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,_execve,(char const *__restrict __path, __TARGV, __TENVP),execve,(__path,,))
#elif defined(__CRT_HAVE__execve)
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,_execve,(char const *__restrict __path, __TARGV, __TENVP),(__path,,))
#endif /* ... */
#ifdef __CRT_HAVE_execvpe
/* >> execvpe(3)
 * Replace the calling process with the application image referred to by `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,_execvpe,(char const *__restrict __file, __TARGV, __TENVP),execvpe,(__file,,))
#elif defined(__CRT_HAVE__execvpe)
/* >> execvpe(3)
 * Replace the calling process with the application image referred to by `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,_execvpe,(char const *__restrict __file, __TARGV, __TENVP),(__file,,))
#endif /* ... */
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
#elif defined(__CRT_HAVE_execv) || defined(__CRT_HAVE__execv)
#include <local/unistd/execl.h>
/* >> execl(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
#define _execl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execl))
#endif /* ... */
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
#elif defined(__CRT_HAVE_execvp) || defined(__CRT_HAVE__execvp)
#include <local/unistd/execlp.h>
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
#define _execlp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execlp))
#endif /* ... */
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
#include <local/unistd/execle.h>
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
#elif defined(__CRT_HAVE_execvpe) || defined(__CRT_HAVE__execvpe)
#include <local/unistd/execlpe.h>
/* >> execlpe(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list, and setting `environ' to a `char **' passed after the NULL sentinel */
#define _execlpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(execlpe))
#endif /* ... */
#ifdef __CRT_HAVE_cwait
__CREDIRECT(,__pid_t,__NOTHROW_RPC,_cwait,(int *__tstat, __pid_t __pid, int __action),cwait,(__tstat,__pid,__action))
#elif defined(__CRT_HAVE__cwait)
__CDECLARE(,__pid_t,__NOTHROW_RPC,_cwait,(int *__tstat, __pid_t __pid, int __action),(__tstat,__pid,__action))
#endif /* ... */
#ifdef __CRT_HAVE_spawnv
__CREDIRECT(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_spawnv,(int __mode, char const *__restrict __path, __TARGV),spawnv,(__mode,__path,))
#elif defined(__CRT_HAVE__spawnv)
__CDECLARE(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_spawnv,(int __mode, char const *__restrict __path, __TARGV),(__mode,__path,))
#endif /* ... */
#ifdef __CRT_HAVE_spawnvp
__CREDIRECT(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_spawnvp,(int __mode, char const *__restrict __file, __TARGV),spawnvp,(__mode,__file,))
#elif defined(__CRT_HAVE__spawnvp)
__CDECLARE(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_spawnvp,(int __mode, char const *__restrict __file, __TARGV),(__mode,__file,))
#endif /* ... */
#ifdef __CRT_HAVE_spawnve
__CREDIRECT(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_spawnve,(int __mode, char const *__restrict __path, __TARGV, __TENVP),spawnve,(__mode,__path,,))
#elif defined(__CRT_HAVE__spawnve)
__CDECLARE(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_spawnve,(int __mode, char const *__restrict __path, __TARGV, __TENVP),(__mode,__path,,))
#endif /* ... */
#ifdef __CRT_HAVE_spawnvpe
__CREDIRECT(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_spawnvpe,(int __mode, char const *__restrict __file, __TARGV, __TENVP),spawnvpe,(__mode,__file,,))
#elif defined(__CRT_HAVE__spawnvpe)
__CDECLARE(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_spawnvpe,(int __mode, char const *__restrict __file, __TARGV, __TENVP),(__mode,__file,,))
#endif /* ... */
#ifdef __CRT_HAVE_spawnl
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _spawnl)(int __mode, char const *__restrict __path, char const *__args, ...) __CASMNAME("spawnl");
#elif defined(__CRT_HAVE__spawnl)
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _spawnl)(int __mode, char const *__restrict __path, char const *__args, ...) __CASMNAME_SAME("_spawnl");
#elif defined(__CRT_HAVE_spawnv) || defined(__CRT_HAVE__spawnv)
#include <local/process/spawnl.h>
#define _spawnl(mode, path, args, ) (__INTPTR_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnl))(mode, path, args, , (...)0)
#endif /* ... */
#ifdef __CRT_HAVE_spawnlp
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _spawnlp)(int __mode, char const *__restrict __file, char const *__args, ...) __CASMNAME("spawnlp");
#elif defined(__CRT_HAVE__spawnlp)
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _spawnlp)(int __mode, char const *__restrict __file, char const *__args, ...) __CASMNAME_SAME("_spawnlp");
#elif defined(__CRT_HAVE_spawnvp) || defined(__CRT_HAVE__spawnvp)
#include <local/process/spawnlp.h>
#define _spawnlp(mode, file, args, ) (__INTPTR_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnlp))(mode, file, args, , (...)0)
#endif /* ... */
#ifdef __CRT_HAVE_spawnle
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _spawnle)(int __mode, char const *__restrict __path, char const *__args, ...) __CASMNAME("spawnle");
#elif defined(__CRT_HAVE__spawnle)
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _spawnle)(int __mode, char const *__restrict __path, char const *__args, ...) __CASMNAME_SAME("_spawnle");
#elif defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve)
#include <local/process/spawnle.h>
#define _spawnle(mode, path, args, ) (__INTPTR_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnle))(mode, path, args, , (...)0)
#endif /* ... */
#ifdef __CRT_HAVE_spawnlpe
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _spawnlpe)(int __mode, char const *__restrict __file, char const *__args, ...) __CASMNAME("spawnlpe");
#elif defined(__CRT_HAVE__spawnlpe)
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _spawnlpe)(int __mode, char const *__restrict __file, char const *__args, ...) __CASMNAME_SAME("_spawnlpe");
#elif defined(__CRT_HAVE_spawnvpe) || defined(__CRT_HAVE__spawnvpe)
#include <local/process/spawnlpe.h>
#define _spawnlpe(mode, file, args, ) (__INTPTR_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnlpe))(mode, file, args, , (...)0)
#endif /* ... */
#ifndef __system_defined
#define __system_defined 1
#ifdef __std_system_defined
__NAMESPACE_STD_USING(system)
#elif defined(__CRT_HAVE_system)
__CDECLARE(,int,__NOTHROW_RPC,system,(char const *__command),(__command))
#else /* ... */
#undef __system_defined
#endif /* !... */
#endif /* !__system_defined */



#ifdef __CRT_HAVE__loaddll
__CDECLARE(,intptr_t,__THROWING,_loaddll,(char __KOS_FIXED_CONST *__file),(__file))
#endif /* __CRT_HAVE__loaddll */
#ifdef __CRT_HAVE__unloaddll
__CDECLARE(,int,__THROWING,_unloaddll,(intptr_t __hnd),(__hnd))
#endif /* __CRT_HAVE__unloaddll */

typedef int (__LIBCCALL *__procfun)(void);
#ifdef __CRT_HAVE__getdllprocaddr
__CDECLARE(,__procfun,__THROWING,_getdllprocaddr,(intptr_t __hnd, char __KOS_FIXED_CONST *__symname, intptr_t __ord),(__hnd,__symname,__ord))
#endif /* __CRT_HAVE__getdllprocaddr */

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
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,_wexecv,(wchar_t const *__restrict __path, __TWARGV),wexecv,(__path,))
#elif defined(__CRT_HAVE_DOS$wexecv) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,_wexecv,(char32_t const *__restrict __path, __T32ARGV),wexecv,(__path,))
#elif defined(__CRT_HAVE_DOS$_wexecv) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,_wexecv,(char16_t const *__restrict __path, __T16ARGV),_wexecv,(__path,))
#endif /* ... */
#ifdef __CRT_HAVE_wexecvp
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,_wexecvp,(wchar_t const *__restrict __file, __TWARGV),wexecvp,(__file,))
#elif defined(__CRT_HAVE_DOS$wexecvp) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,_wexecvp,(char32_t const *__restrict __file, __T32ARGV),wexecvp,(__file,))
#elif defined(__CRT_HAVE_DOS$_wexecvp) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,_wexecvp,(char16_t const *__restrict __file, __T16ARGV),_wexecvp,(__file,))
#endif /* ... */
#ifdef __CRT_HAVE_wexecve
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,_wexecve,(wchar_t const *__restrict __path, __TWARGV, __TWENVP),wexecve,(__path,,))
#elif defined(__CRT_HAVE_DOS$wexecve) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,_wexecve,(char32_t const *__restrict __path, __T32ARGV, __T32ENVP),wexecve,(__path,,))
#elif defined(__CRT_HAVE_DOS$_wexecve) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,_wexecve,(char16_t const *__restrict __path, __T16ARGV, __T16ENVP),_wexecve,(__path,,))
#endif /* ... */
#ifdef __CRT_HAVE_wexecvpe
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,_wexecvpe,(wchar_t const *__restrict __file, __TWARGV, __TWENVP),wexecvpe,(__file,,))
#elif defined(__CRT_HAVE_DOS$wexecvpe) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,_wexecvpe,(char32_t const *__restrict __file, __T32ARGV, __T32ENVP),wexecvpe,(__file,,))
#elif defined(__CRT_HAVE_DOS$_wexecvpe) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,_wexecvpe,(char16_t const *__restrict __file, __T16ARGV, __T16ENVP),_wexecvpe,(__file,,))
#endif /* ... */
#ifdef __CRT_HAVE_wexecl
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL _wexecl)(wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME("wexecl");
#elif defined(__CRT_HAVE_DOS$wexecl) && __SIZEOF_WCHAR_T__ == 4
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL _wexecl)(char32_t const *__restrict __path, char32_t const *__args, ...) __CASMNAME_KOS("wexecl");
#elif defined(__CRT_HAVE_DOS$_wexecl) && __SIZEOF_WCHAR_T__ == 2
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL _wexecl)(char16_t const *__restrict __path, char16_t const *__args, ...) __CASMNAME_DOS("_wexecl");
#elif defined(__CRT_HAVE_wexecv) || (defined(__CRT_HAVE_DOS$wexecv) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wexecv) && __SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.process/wexecl.h>
#define _wexecl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexecl))
#endif /* ... */
#ifdef __CRT_HAVE_wexeclp
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL _wexeclp)(wchar_t const *__restrict __file, wchar_t const *__args, ...) __CASMNAME("wexeclp");
#elif defined(__CRT_HAVE_DOS$wexeclp) && __SIZEOF_WCHAR_T__ == 4
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL _wexeclp)(char32_t const *__restrict __file, char32_t const *__args, ...) __CASMNAME_KOS("wexeclp");
#elif defined(__CRT_HAVE_DOS$_wexeclp) && __SIZEOF_WCHAR_T__ == 2
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL _wexeclp)(char16_t const *__restrict __file, char16_t const *__args, ...) __CASMNAME_DOS("_wexeclp");
#elif defined(__CRT_HAVE_wexecvp) || (defined(__CRT_HAVE_DOS$wexecvp) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wexecvp) && __SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.process/wexeclp.h>
#define _wexeclp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexeclp))
#endif /* ... */
#ifdef __CRT_HAVE_wexecle
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL _wexecle)(wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME("wexecle");
#elif defined(__CRT_HAVE_DOS$wexecle) && __SIZEOF_WCHAR_T__ == 4
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL _wexecle)(char32_t const *__restrict __path, char32_t const *__args, ...) __CASMNAME_KOS("wexecle");
#elif defined(__CRT_HAVE_DOS$_wexecle) && __SIZEOF_WCHAR_T__ == 2
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL _wexecle)(char16_t const *__restrict __path, char16_t const *__args, ...) __CASMNAME_DOS("_wexecle");
#elif defined(__CRT_HAVE_wexecve) || (defined(__CRT_HAVE_DOS$wexecve) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wexecve) && __SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.process/wexecle.h>
#define _wexecle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexecle))
#endif /* ... */
#ifdef __CRT_HAVE_wexeclpe
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL _wexeclpe)(wchar_t const *__restrict __file, wchar_t const *__args, ...) __CASMNAME("wexeclpe");
#elif defined(__CRT_HAVE_DOS$wexeclpe) && __SIZEOF_WCHAR_T__ == 4
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL _wexeclpe)(char32_t const *__restrict __file, char32_t const *__args, ...) __CASMNAME_KOS("wexeclpe");
#elif defined(__CRT_HAVE_DOS$_wexecle) && __SIZEOF_WCHAR_T__ == 2
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL _wexeclpe)(char16_t const *__restrict __file, char16_t const *__args, ...) __CASMNAME_DOS("_wexecle");
#elif defined(__CRT_HAVE_wexecvpe) || (defined(__CRT_HAVE_DOS$wexecvpe) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wexecvpe) && __SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.process/wexeclpe.h>
#define _wexeclpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexeclpe))
#endif /* ... */
#ifdef __CRT_HAVE_wspawnv
__CREDIRECT(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_wspawnv,(int __mode, wchar_t const *__restrict __path, __TWARGV),wspawnv,(__mode,__path,))
#elif defined(__CRT_HAVE_DOS$wspawnv) && __SIZEOF_WCHAR_T__ == 4
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,__LIBCCALL,_wspawnv,(int __mode, wchar_t const *__restrict __path, __TWARGV),KOS$wspawnv,(__mode,__path,))
#elif defined(__CRT_HAVE_DOS$_wspawnv) && __SIZEOF_WCHAR_T__ == 2
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,__LIBCCALL,_wspawnv,(int __mode, wchar_t const *__restrict __path, __TWARGV),DOS$_wspawnv,(__mode,__path,))
#endif /* ... */
#ifdef __CRT_HAVE_wspawnvp
__CREDIRECT(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_wspawnvp,(int __mode, wchar_t const *__restrict __path, __TWARGV),wspawnvp,(__mode,__path,))
#elif defined(__CRT_HAVE_DOS$wspawnvp) && __SIZEOF_WCHAR_T__ == 4
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,__LIBCCALL,_wspawnvp,(int __mode, wchar_t const *__restrict __path, __TWARGV),KOS$wspawnvp,(__mode,__path,))
#elif defined(__CRT_HAVE_DOS$_wspawnvp) && __SIZEOF_WCHAR_T__ == 2
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,__LIBCCALL,_wspawnvp,(int __mode, wchar_t const *__restrict __path, __TWARGV),DOS$_wspawnvp,(__mode,__path,))
#endif /* ... */
#ifdef __CRT_HAVE_wspawnve
__CREDIRECT(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_wspawnve,(int __mode, wchar_t const *__restrict __path, __TWARGV, __TWENVP),wspawnve,(__mode,__path,,))
#elif defined(__CRT_HAVE_DOS$wspawnve) && __SIZEOF_WCHAR_T__ == 4
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,__LIBCCALL,_wspawnve,(int __mode, wchar_t const *__restrict __path, __TWARGV, __TWENVP),KOS$wspawnve,(__mode,__path,,))
#elif defined(__CRT_HAVE_DOS$_wspawnve) && __SIZEOF_WCHAR_T__ == 2
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,__LIBCCALL,_wspawnve,(int __mode, wchar_t const *__restrict __path, __TWARGV, __TWENVP),DOS$_wspawnve,(__mode,__path,,))
#endif /* ... */
#ifdef __CRT_HAVE_wspawnvpe
__CREDIRECT(__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,_wspawnvpe,(int __mode, wchar_t const *__restrict __path, __TWARGV, __TWENVP),wspawnvpe,(__mode,__path,,))
#elif defined(__CRT_HAVE_DOS$wspawnvpe) && __SIZEOF_WCHAR_T__ == 4
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,__LIBCCALL,_wspawnvpe,(int __mode, wchar_t const *__restrict __path, __TWARGV, __TWENVP),KOS$wspawnvpe,(__mode,__path,,))
#elif defined(__CRT_HAVE_DOS$_wspawnvpe) && __SIZEOF_WCHAR_T__ == 2
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),intptr_t,__NOTHROW_NCX,__LIBCCALL,_wspawnvpe,(int __mode, wchar_t const *__restrict __path, __TWARGV, __TWENVP),DOS$_wspawnvpe,(__mode,__path,,))
#endif /* ... */
#ifdef __CRT_HAVE_wspawnl
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _wspawnl)(int __mode, wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME("wspawnl");
#elif defined(__CRT_HAVE_DOS$wspawnl) && __SIZEOF_WCHAR_T__ == 4
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _wspawnl)(int __mode, wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME_KOS("wspawnl");
#elif defined(__CRT_HAVE_DOS$_wspawnl) && __SIZEOF_WCHAR_T__ == 2
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _wspawnl)(int __mode, wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME_DOS("_wspawnl");
#elif defined(__CRT_HAVE_wspawnv) || (defined(__CRT_HAVE_DOS$wspawnv) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wspawnv) && __SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.process/wspawnl.h>
#define _wspawnl(mode, path, args, ) (__INTPTR_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnl))(mode, path, args, , (...)0)
#endif /* ... */
#ifdef __CRT_HAVE_wspawnlp
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _wspawnlp)(int __mode, wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME("wspawnlp");
#elif defined(__CRT_HAVE_DOS$wspawnlp) && __SIZEOF_WCHAR_T__ == 4
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _wspawnlp)(int __mode, wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME_KOS("wspawnlp");
#elif defined(__CRT_HAVE_DOS$_wspawnlp) && __SIZEOF_WCHAR_T__ == 2
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _wspawnlp)(int __mode, wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME_DOS("_wspawnlp");
#elif defined(__CRT_HAVE_wspawnvp) || (defined(__CRT_HAVE_DOS$wspawnvp) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wspawnvp) && __SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.process/wspawnlp.h>
#define _wspawnlp(mode, path, args, ) (__INTPTR_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnlp))(mode, path, args, , (...)0)
#endif /* ... */
#ifdef __CRT_HAVE_wspawnle
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _wspawnle)(int __mode, wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME("wspawnle");
#elif defined(__CRT_HAVE_DOS$wspawnle) && __SIZEOF_WCHAR_T__ == 4
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _wspawnle)(int __mode, wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME_KOS("wspawnle");
#elif defined(__CRT_HAVE_DOS$_wspawnle) && __SIZEOF_WCHAR_T__ == 2
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _wspawnle)(int __mode, wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME_DOS("_wspawnle");
#elif defined(__CRT_HAVE_wspawnve) || (defined(__CRT_HAVE_DOS$wspawnve) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wspawnve) && __SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.process/wspawnle.h>
#define _wspawnle(mode, path, args, ) (__INTPTR_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnle))(mode, path, args, , (...)0)
#endif /* ... */
#ifdef __CRT_HAVE_wspawnlpe
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _wspawnlpe)(int __mode, wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME("wspawnlpe");
#elif defined(__CRT_HAVE_DOS$wspawnlpe) && __SIZEOF_WCHAR_T__ == 4
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _wspawnlpe)(int __mode, wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME_KOS("wspawnlpe");
#elif defined(__CRT_HAVE_DOS$_wspawnle) && __SIZEOF_WCHAR_T__ == 2
__LIBC __ATTR_NONNULL((2)) intptr_t __NOTHROW_NCX(__VLIBCCALL _wspawnlpe)(int __mode, wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME_DOS("_wspawnle");
#elif defined(__CRT_HAVE_wspawnvpe) || (defined(__CRT_HAVE_DOS$wspawnvpe) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wspawnvpe) && __SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.process/wspawnlpe.h>
#define _wspawnlpe(mode, path, args, ) (__INTPTR_TYPE__)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnlpe))(mode, path, args, , (...)0)
#endif /* ... */
#endif /* !_WPROCESS_DEFINED */

#ifndef _CRT_WSYSTEM_DEFINED
#define _CRT_WSYSTEM_DEFINED 1
#ifndef ___wsystem_defined
#define ___wsystem_defined 1
#ifdef __CRT_HAVE_wsystem
__CREDIRECT(,int,__NOTHROW_RPC,_wsystem,(wchar_t const *__cmd),wsystem,(__cmd))
#elif defined(__CRT_HAVE_DOS$wsystem) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(,int,__NOTHROW_RPC,_wsystem,(char32_t const *__cmd),wsystem,(__cmd))
#elif defined(__CRT_HAVE_DOS$_wsystem) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(,int,__NOTHROW_RPC,_wsystem,(char16_t const *__cmd),_wsystem,(__cmd))
#else /* ... */
#undef ___wsystem_defined
#endif /* !... */
#endif /* !___wsystem_defined */
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
#ifndef __execv_defined
#define __execv_defined 1
#if __has_builtin(__builtin_execv) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execv)
/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CEIDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,execv,(char const *__restrict __path, __TARGV),{ return __builtin_execv(__path, ); })
#elif defined(__CRT_HAVE_execv)
/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,execv,(char const *__restrict __path, __TARGV),(__path,))
#elif defined(__CRT_HAVE__execv)
/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,execv,(char const *__restrict __path, __TARGV),_execv,(__path,))
#else /* ... */
#undef __execv_defined
#endif /* !... */
#endif /* !__execv_defined */
#ifndef __execvp_defined
#define __execvp_defined 1
#if __has_builtin(__builtin_execvp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execvp)
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CEIDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,execvp,(char const *__restrict __file, __TARGV),{ return __builtin_execvp(__file, ); })
#elif defined(__CRT_HAVE_execvp)
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,execvp,(char const *__restrict __file, __TARGV),(__file,))
#elif defined(__CRT_HAVE__execvp)
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,execvp,(char const *__restrict __file, __TARGV),_execvp,(__file,))
#else /* ... */
#undef __execvp_defined
#endif /* !... */
#endif /* !__execvp_defined */
#ifndef __execve_defined
#define __execve_defined 1
#if __has_builtin(__builtin_execve) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execve)
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CEIDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,execve,(char const *__restrict __path, __TARGV, __TENVP),{ return __builtin_execve(__path, , ); })
#elif defined(__CRT_HAVE_execve)
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,execve,(char const *__restrict __path, __TARGV, __TENVP),(__path,,))
#elif defined(__CRT_HAVE__execve)
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,execve,(char const *__restrict __path, __TARGV, __TENVP),_execve,(__path,,))
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
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,execvpe,(char const *__restrict __file, __TARGV, __TENVP),(__file,,))
#elif defined(__CRT_HAVE__execvpe)
/* >> execvpe(3)
 * Replace the calling process with the application image referred to by `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,execvpe,(char const *__restrict __file, __TARGV, __TENVP),_execvpe,(__file,,))
#else /* ... */
#undef __execvpe_defined
#endif /* !... */
#endif /* !__execvpe_defined */
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
#ifdef __CRT_HAVE_cwait
__CDECLARE(,__pid_t,__NOTHROW_RPC,cwait,(int *__tstat, __pid_t __pid, int __action),(__tstat,__pid,__action))
#elif defined(__CRT_HAVE__cwait)
__CREDIRECT(,__pid_t,__NOTHROW_RPC,cwait,(int *__tstat, __pid_t __pid, int __action),_cwait,(__tstat,__pid,__action))
#endif /* ... */
#ifndef __spawnv_defined
#define __spawnv_defined 1
#ifdef __CRT_HAVE_spawnv
__CDECLARE(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,spawnv,(int __mode, char const *__restrict __path, __TARGV),(__mode,__path,))
#elif defined(__CRT_HAVE__spawnv)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,spawnv,(int __mode, char const *__restrict __path, __TARGV),_spawnv,(__mode,__path,))
#else /* ... */
#undef __spawnv_defined
#endif /* !... */
#endif /* !__spawnv_defined */
#ifndef __spawnvp_defined
#define __spawnvp_defined 1
#ifdef __CRT_HAVE_spawnvp
__CDECLARE(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,spawnvp,(int __mode, char const *__restrict __file, __TARGV),(__mode,__file,))
#elif defined(__CRT_HAVE__spawnvp)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,spawnvp,(int __mode, char const *__restrict __file, __TARGV),_spawnvp,(__mode,__file,))
#else /* ... */
#undef __spawnvp_defined
#endif /* !... */
#endif /* !__spawnvp_defined */
#ifndef __spawnve_defined
#define __spawnve_defined 1
#ifdef __CRT_HAVE_spawnve
__CDECLARE(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,spawnve,(int __mode, char const *__restrict __path, __TARGV, __TENVP),(__mode,__path,,))
#elif defined(__CRT_HAVE__spawnve)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,spawnve,(int __mode, char const *__restrict __path, __TARGV, __TENVP),_spawnve,(__mode,__path,,))
#else /* ... */
#undef __spawnve_defined
#endif /* !... */
#endif /* !__spawnve_defined */
#ifndef __spawnvpe_defined
#define __spawnvpe_defined 1
#ifdef __CRT_HAVE_spawnvpe
__CDECLARE(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,spawnvpe,(int __mode, char const *__restrict __file, __TARGV, __TENVP),(__mode,__file,,))
#elif defined(__CRT_HAVE__spawnvpe)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,spawnvpe,(int __mode, char const *__restrict __file, __TARGV, __TENVP),_spawnvpe,(__mode,__file,,))
#else /* ... */
#undef __spawnvpe_defined
#endif /* !... */
#endif /* !__spawnvpe_defined */
#ifndef __spawnl_defined
#define __spawnl_defined 1
#ifdef __CRT_HAVE_spawnl
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnl)(int __mode, char const *__restrict __path, char const *__args, ...) __CASMNAME_SAME("spawnl");
#elif defined(__CRT_HAVE__spawnl)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnl)(int __mode, char const *__restrict __path, char const *__args, ...) __CASMNAME("_spawnl");
#elif defined(__CRT_HAVE_spawnv) || defined(__CRT_HAVE__spawnv)
#include <local/process/spawnl.h>
#define spawnl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnl))
#else /* ... */
#undef __spawnl_defined
#endif /* !... */
#endif /* !__spawnl_defined */
#ifndef __spawnlp_defined
#define __spawnlp_defined 1
#ifdef __CRT_HAVE_spawnlp
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnlp)(int __mode, char const *__restrict __file, char const *__args, ...) __CASMNAME_SAME("spawnlp");
#elif defined(__CRT_HAVE__spawnlp)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnlp)(int __mode, char const *__restrict __file, char const *__args, ...) __CASMNAME("_spawnlp");
#elif defined(__CRT_HAVE_spawnvp) || defined(__CRT_HAVE__spawnvp)
#include <local/process/spawnlp.h>
#define spawnlp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnlp))
#else /* ... */
#undef __spawnlp_defined
#endif /* !... */
#endif /* !__spawnlp_defined */
#ifndef __spawnle_defined
#define __spawnle_defined 1
#ifdef __CRT_HAVE_spawnle
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnle)(int __mode, char const *__restrict __path, char const *__args, ...) __CASMNAME_SAME("spawnle");
#elif defined(__CRT_HAVE__spawnle)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnle)(int __mode, char const *__restrict __path, char const *__args, ...) __CASMNAME("_spawnle");
#elif defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve)
#include <local/process/spawnle.h>
#define spawnle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnle))
#else /* ... */
#undef __spawnle_defined
#endif /* !... */
#endif /* !__spawnle_defined */
#ifndef __spawnlpe_defined
#define __spawnlpe_defined 1
#ifdef __CRT_HAVE_spawnlpe
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnlpe)(int __mode, char const *__restrict __file, char const *__args, ...) __CASMNAME_SAME("spawnlpe");
#elif defined(__CRT_HAVE__spawnlpe)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL spawnlpe)(int __mode, char const *__restrict __file, char const *__args, ...) __CASMNAME("_spawnlpe");
#elif defined(__CRT_HAVE_spawnvpe) || defined(__CRT_HAVE__spawnvpe)
#include <local/process/spawnlpe.h>
#define spawnlpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(spawnlpe))
#else /* ... */
#undef __spawnlpe_defined
#endif /* !... */
#endif /* !__spawnlpe_defined */
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
