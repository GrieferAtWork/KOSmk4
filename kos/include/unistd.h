/* HASH CRC-32:0x25be2d42 */
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
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/unistd.h) */
/* (#) Portability: DJGPP         (/include/unistd.h) */
/* (#) Portability: DragonFly BSD (/include/unistd.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/unistd.h) */
/* (#) Portability: FreeBSD       (/include/unistd.h) */
/* (#) Portability: GNU C Library (/posix/unistd.h) */
/* (#) Portability: GNU Hurd      (/usr/include/unistd.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/unistd.h) */
/* (#) Portability: NetBSD        (/include/unistd.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/unistd.h) */
/* (#) Portability: OpenBSD       (/include/unistd.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/unistd.h) */
/* (#) Portability: avr-libc      (/include/unistd.h) */
/* (#) Portability: diet libc     (/include/unistd.h) */
/* (#) Portability: libbsd        (/include/bsd/unistd.h) */
/* (#) Portability: libc4/5       (/include/unistd.h) */
/* (#) Portability: libc6         (/include/unistd.h) */
/* (#) Portability: libcmini      (/include/unistd.h) */
/* (#) Portability: mintlib       (/include/unistd.h) */
/* (#) Portability: musl libc     (/include/unistd.h) */
/* (#) Portability: uClibc        (/include/unistd.h) */
#ifndef _UNISTD_H
#define _UNISTD_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <hybrid/typecore.h>

#include <asm/crt/confname.h>
#include <asm/os/stdio.h>
#include <asm/os/vfork.h> /* os-specific vfork(2) caveats: __ARCH_HAVE_*_VFORK */
#include <asm/pagesize.h>
#include <bits/posix_opt.h>
#include <bits/crt/sys_errlist.h>
#include <bits/types.h>
#include <kos/anno.h>

#ifdef __USE_GNU
#include <linux/close_range.h>
#endif /* __USE_GNU */

#if defined(__CRT_GLC) || defined(__CRT_KOS) || defined(__CRT_KOS_KERNEL)
#include <asm/unistd.h>
#endif /* __CRT_GLC || __CRT_KOS || __CRT_KOS_KERNEL */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
#include <bits/crt/environments.h>
#endif /* __USE_UNIX98 || __USE_XOPEN2K */

#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_POSIX))
#include <asm/os/fcntl.h> /* __F_ULOCK, __F_LOCK, __F_TLOCK, __F_TEST */
#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_POSIX) */

#ifdef __USE_NETBSD
#include <asm/os/signal.h> /* __NSIG */
#include <asm/crt/getpassfd.h> /* __GETPASS_* */
#endif /* __USE_NETBSD */

#ifdef __USE_KOS
#include <bits/crt/format-printer.h> /* __FORMATPRINTER_CC */
#endif /* __USE_KOS */

#ifdef __USE_SOLARIS
#define GF_PATH "/etc/group"
#define PF_PATH "/etc/passwd"
#endif /* __USE_SOLARIS */


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


#ifdef __STDIN_FILENO
#define STDIN_FILENO  __STDIN_FILENO  /* Standard input. */
#endif /* __STDIN_FILENO */
#ifdef __STDOUT_FILENO
#define STDOUT_FILENO __STDOUT_FILENO /* Standard output. */
#endif /* __STDOUT_FILENO */
#ifdef __STDERR_FILENO
#define STDERR_FILENO __STDERR_FILENO /* Standard error output. */
#endif /* __STDERR_FILENO */

#if !defined(R_OK) && defined(__R_OK)
#define R_OK __R_OK /* Test for read permission. */
#endif /* !R_OK && __R_OK */
#if !defined(W_OK) && defined(__W_OK)
#define W_OK __W_OK /* Test for write permission. */
#endif /* !W_OK && __W_OK */
#if !defined(X_OK) && defined(__X_OK)
#define X_OK __X_OK /* Test for execute permission. */
#endif /* !X_OK && __X_OK */
#if !defined(F_OK) && defined(__F_OK)
#define F_OK __F_OK /* Test for existence. */
#endif /* !F_OK && __F_OK */

#if !defined(SEEK_SET) && defined(__SEEK_SET)
#define SEEK_SET __SEEK_SET /* Seek from beginning of file. */
#endif /* !SEEK_SET && __SEEK_SET */
#if !defined(SEEK_CUR) && defined(__SEEK_CUR)
#define SEEK_CUR __SEEK_CUR /* Seek from current position. */
#endif /* !SEEK_CUR && __SEEK_CUR */
#if !defined(SEEK_END) && defined(__SEEK_END)
#define SEEK_END __SEEK_END /* Seek from end of file. */
#endif /* !SEEK_END && __SEEK_END */
#if defined(__USE_GNU) || defined(__USE_SOLARIS)
#if !defined(SEEK_DATA) && defined(__SEEK_DATA)
#define SEEK_DATA __SEEK_DATA /* Seek to next data. */
#endif /* !SEEK_DATA && __SEEK_DATA */
#if !defined(SEEK_HOLE) && defined(__SEEK_HOLE)
#define SEEK_HOLE __SEEK_HOLE /* Seek to next hole. */
#endif /* !SEEK_HOLE && __SEEK_HOLE */
#endif /* __USE_GNU || __USE_SOLARIS */

#ifdef __USE_MISC
#if !defined(L_SET) && defined(__SEEK_SET)
#define L_SET  __SEEK_SET /* Seek from beginning of file. */
#endif /* !L_SET && __SEEK_SET */
#if !defined(L_CURR) && defined(__SEEK_CUR)
#define L_CURR __SEEK_CUR /* Seek from current position. */
#endif /* !L_CURR && __SEEK_CUR */
#if !defined(L_INCR) && defined(__SEEK_CUR)
#define L_INCR __SEEK_CUR /* Seek from current position. */
#endif /* !L_INCR && __SEEK_CUR */
#if !defined(L_XTND) && defined(__SEEK_END)
#define L_XTND __SEEK_END /* Seek from end of file. */
#endif /* !L_XTND && __SEEK_END */
#endif /* __USE_MISC */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __ssize_t_defined
#define __ssize_t_defined
typedef __ssize_t ssize_t;
#endif /* !__ssize_t_defined */

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#ifndef __gid_t_defined
#define __gid_t_defined
typedef __gid_t gid_t;
#endif /* !__gid_t_defined */
#ifndef __uid_t_defined
#define __uid_t_defined
typedef __uid_t uid_t;
#endif /* !__uid_t_defined */
#ifndef __off_t_defined
#define __off_t_defined
typedef __off_t off_t;
#endif /* !__off_t_defined */
#ifndef __useconds_t_defined
#define __useconds_t_defined
typedef __useconds_t useconds_t;
#endif /* !__useconds_t_defined */
#ifndef __pid_t_defined
#define __pid_t_defined
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */
#ifdef __USE_LARGEFILE64
#ifndef __off64_t_defined
#define __off64_t_defined
typedef __off64_t off64_t;
#endif /* !__off64_t_defined */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN || __USE_XOPEN2K */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
#ifndef __intptr_t_defined
#define __intptr_t_defined
typedef __intptr_t intptr_t;
#endif /* !__intptr_t_defined */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifndef __socklen_t_defined
#define __socklen_t_defined
typedef __socklen_t socklen_t;
#endif /* !__socklen_t_defined */
#endif /* __USE_MISC || __USE_XOPEN */

#ifndef __TARGV
#ifdef __USE_DOS_ALTERATIONS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS_ALTERATIONS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__TARGV */

#ifndef __environ
#if defined(environ)
#define __environ environ
#elif defined(_environ)
#define __environ _environ
#elif defined(__LOCAL_environ)
#define __environ __LOCAL_environ
#elif defined(__CRT_HAVE_environ)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,char **,environ)
#define environ   environ
#define __environ environ
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,char **,__environ,environ)
#define __environ __environ
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE__environ)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,char **,_environ)
#define _environ  _environ
#define __environ _environ
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,char **,__environ,_environ)
#define __environ __environ
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE___environ)
__CSDECLARE(,char **,__environ)
#define __environ __environ
#elif defined(____p__environ_defined)
#define __environ (*__p__environ())
#elif defined(__CRT_HAVE___p__environ)
#define ____p__environ_defined
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,char ***,__NOTHROW,__p__environ,(void),())
#define __environ (*__p__environ())
#elif defined(__CRT_HAVE__get_environ)
#ifndef ___get_environ_defined
#define ___get_environ_defined
__CDECLARE(,int,__NOTHROW,_get_environ,(char ***__p_environ),())
#endif /* !___get_environ_defined */
#ifndef _____get_environ_wrapper_defined
#define _____get_environ_wrapper_defined
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST char **
__NOTHROW(__LIBCCALL ___get_environ_wrapper)(void) {
	char **__result;
	if __unlikely(_get_environ(&__result) != 0)
		__result = __NULLPTR;
	return __result;
}
#endif /* !_____get_environ_wrapper_defined */
#define __environ ___get_environ_wrapper()
#endif /* !... */
#endif /* !__environ */

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

#if defined(__USE_KOS) || defined(__USE_DOS) || defined(__USE_GNU) || defined(__USE_NETBSD)
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
#endif /* __USE_KOS || __USE_DOS || __USE_GNU || __USE_NETBSD */

#if defined(__USE_KOS) || defined(__USE_DOS) || defined(__USE_NETBSD)
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
#endif /* __USE_KOS || __USE_DOS || __USE_NETBSD */
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
#ifdef __USE_KOS
#ifndef __gettid_defined
#define __gettid_defined
#ifdef __CRT_HAVE_gettid
/* >> gettid(2)
 * Return the TID of the calling thread
 * THIS_THREAD->PID */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,gettid,(void),())
#elif defined(__CRT_HAVE___threadid)
/* >> gettid(2)
 * Return the TID of the calling thread
 * THIS_THREAD->PID */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,gettid,(void),__threadid,())
#elif defined(__CRT_HAVE_$QGetCurrentThreadId$Aplatform$Adetails$AConcurrency$A$AYAJXZ)
/* >> gettid(2)
 * Return the TID of the calling thread
 * THIS_THREAD->PID */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__pid_t,__NOTHROW,gettid,(void),?GetCurrentThreadId@platform@details@Concurrency@@YAJXZ,())
#else /* ... */
#undef __gettid_defined
#endif /* !... */
#endif /* !__gettid_defined */
#endif /* __USE_KOS */
#ifdef __CRT_HAVE_pipe
/* >> pipe(2)
 * Create a new pair of connected pipes ([0] = reader, [1] = writer)
 * @param: pipedes: Output for pipe fds: [0]: reader; [1]: writer
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(__ATTR_OUT(1),int,__NOTHROW_NCX,pipe,(__fd_t __pipedes[2]),(__pipedes))
#elif defined(__CRT_HAVE___pipe)
/* >> pipe(2)
 * Create a new pair of connected pipes ([0] = reader, [1] = writer)
 * @param: pipedes: Output for pipe fds: [0]: reader; [1]: writer
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,pipe,(__fd_t __pipedes[2]),__pipe,(__pipedes))
#elif defined(__CRT_HAVE___libc_pipe)
/* >> pipe(2)
 * Create a new pair of connected pipes ([0] = reader, [1] = writer)
 * @param: pipedes: Output for pipe fds: [0]: reader; [1]: writer
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,pipe,(__fd_t __pipedes[2]),__libc_pipe,(__pipedes))
#elif defined(__CRT_HAVE__pipe)
#include <libc/local/unistd/pipe.h>
/* >> pipe(2)
 * Create a new pair of connected pipes ([0] = reader, [1] = writer)
 * @param: pipedes: Output for pipe fds: [0]: reader; [1]: writer
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(pipe, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) int __NOTHROW_NCX(__LIBCCALL pipe)(__fd_t __pipedes[2]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pipe))(__pipedes); })
#endif /* ... */
#ifndef __sleep_defined
#define __sleep_defined
#ifdef __CRT_HAVE_sleep
/* >> sleep(3)
 * Sleep for up to `seconds' seconds
 * @return: 0 : Timeout expired
 * @return: * : You were interrupted, and this many seconds were still left on the timeout */
__CDECLARE(,unsigned int,__NOTHROW_RPC,sleep,(unsigned int __seconds),(__seconds))
#elif defined(__CRT_HAVE__sleep) || defined(__CRT_HAVE___crtSleep) || defined(__CRT_HAVE_nanosleep64) || defined(__CRT_HAVE_nanosleep) || defined(__CRT_HAVE___nanosleep) || defined(__CRT_HAVE___libc_nanosleep)
#include <libc/local/unistd/sleep.h>
/* >> sleep(3)
 * Sleep for up to `seconds' seconds
 * @return: 0 : Timeout expired
 * @return: * : You were interrupted, and this many seconds were still left on the timeout */
__NAMESPACE_LOCAL_USING_OR_IMPL(sleep, __FORCELOCAL __ATTR_ARTIFICIAL unsigned int __NOTHROW_RPC(__LIBCCALL sleep)(unsigned int __seconds) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sleep))(__seconds); })
#else /* ... */
#undef __sleep_defined
#endif /* !... */
#endif /* !__sleep_defined */
#ifdef __CRT_HAVE_fsync
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
__CDECLARE(,int,__NOTHROW_RPC,fsync,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE__commit)
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
__CREDIRECT(,int,__NOTHROW_RPC,fsync,(__fd_t __fd),_commit,(__fd))
#elif defined(__CRT_HAVE___fsync)
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
__CREDIRECT(,int,__NOTHROW_RPC,fsync,(__fd_t __fd),__fsync,(__fd))
#elif defined(__CRT_HAVE___libc_fsync)
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
__CREDIRECT(,int,__NOTHROW_RPC,fsync,(__fd_t __fd),__libc_fsync,(__fd))
#elif defined(__CRT_HAVE_fdatasync)
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
__CREDIRECT(,int,__NOTHROW_RPC,fsync,(__fd_t __fd),fdatasync,(__fd))
#elif defined(__CRT_HAVE___fdatasync)
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
__CREDIRECT(,int,__NOTHROW_RPC,fsync,(__fd_t __fd),__fdatasync,(__fd))
#else /* ... */
#include <libc/local/unistd/fsync.h>
/* >> fsync(2)
 * Synchronize a file (including its descriptor which contains timestamps, and its size),
 * meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk */
__NAMESPACE_LOCAL_USING_OR_IMPL(fsync, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL fsync)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fsync))(__fd); })
#endif /* !... */
#ifdef __CRT_HAVE_getppid
/* >> getppid(2)
 * Return the PID of the calling process's parent.
 * (That is the TID of the leader of the parent of the calling thread's leader)
 * THIS_THREAD->LEADER->PARENT->LEADER->PID */
__CDECLARE(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,getppid,(void),())
#elif defined(__CRT_HAVE___getppid)
/* >> getppid(2)
 * Return the PID of the calling process's parent.
 * (That is the TID of the leader of the parent of the calling thread's leader)
 * THIS_THREAD->LEADER->PARENT->LEADER->PID */
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,getppid,(void),__getppid,())
#elif defined(__CRT_HAVE___libc_getppid)
/* >> getppid(2)
 * Return the PID of the calling process's parent.
 * (That is the TID of the leader of the parent of the calling thread's leader)
 * THIS_THREAD->LEADER->PARENT->LEADER->PID */
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,getppid,(void),__libc_getppid,())
#endif /* ... */
#ifdef __CRT_HAVE_getpgrp
/* >> getpgrp(2)
 * Return the ID of the calling process's process group.
 * (That is the TID of the leader of the process group of the calling thread's leader)
 * THIS_THREAD->LEADER->GROUP_LEADER->PID */
__CDECLARE(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,getpgrp,(void),())
#elif defined(__CRT_HAVE___getpgrp)
/* >> getpgrp(2)
 * Return the ID of the calling process's process group.
 * (That is the TID of the leader of the process group of the calling thread's leader)
 * THIS_THREAD->LEADER->GROUP_LEADER->PID */
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,getpgrp,(void),__getpgrp,())
#elif defined(__CRT_HAVE___libc_getpgrp)
/* >> getpgrp(2)
 * Return the ID of the calling process's process group.
 * (That is the TID of the leader of the process group of the calling thread's leader)
 * THIS_THREAD->LEADER->GROUP_LEADER->PID */
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,getpgrp,(void),__libc_getpgrp,())
#endif /* ... */
#ifdef __CRT_HAVE_getpgid
/* >> getpgid(2)
 * Return  the ID of  the process group  associated with `pid's process.
 * (That is the TID of the leader of the process group of `pid's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER->PID
 * When `pid' is ZERO(0), use `gettid()' for it instead */
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__getpgid,(__pid_t __pid),getpgid,(__pid))
#elif defined(__CRT_HAVE___getpgid)
/* >> getpgid(2)
 * Return  the ID of  the process group  associated with `pid's process.
 * (That is the TID of the leader of the process group of `pid's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER->PID
 * When `pid' is ZERO(0), use `gettid()' for it instead */
__CDECLARE(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__getpgid,(__pid_t __pid),(__pid))
#elif defined(__CRT_HAVE___libc_getpgid)
/* >> getpgid(2)
 * Return  the ID of  the process group  associated with `pid's process.
 * (That is the TID of the leader of the process group of `pid's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER->PID
 * When `pid' is ZERO(0), use `gettid()' for it instead */
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__getpgid,(__pid_t __pid),__libc_getpgid,(__pid))
#elif defined(__CRT_HAVE___bsd_getpgrp)
/* >> getpgid(2)
 * Return  the ID of  the process group  associated with `pid's process.
 * (That is the TID of the leader of the process group of `pid's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER->PID
 * When `pid' is ZERO(0), use `gettid()' for it instead */
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__getpgid,(__pid_t __pid),__bsd_getpgrp,(__pid))
#endif /* ... */
#ifdef __CRT_HAVE_setpgid
/* >> setpgid(2)
 * Change  the ID of  the process group  associated with `pid's process.
 * (That is the TID of the leader of the process group of `pid's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER = THREAD[PGID]
 * When `pid' is ZERO(0), use `gettid()' for it instead.
 * When `pgid' is ZERO(0), use `pid' (after it was substituted) for instead */
__CDECLARE(,int,__NOTHROW_NCX,setpgid,(__pid_t __pid, __pid_t __pgid),(__pid,__pgid))
#elif defined(__CRT_HAVE___setpgid)
/* >> setpgid(2)
 * Change  the ID of  the process group  associated with `pid's process.
 * (That is the TID of the leader of the process group of `pid's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER = THREAD[PGID]
 * When `pid' is ZERO(0), use `gettid()' for it instead.
 * When `pgid' is ZERO(0), use `pid' (after it was substituted) for instead */
__CREDIRECT(,int,__NOTHROW_NCX,setpgid,(__pid_t __pid, __pid_t __pgid),__setpgid,(__pid,__pgid))
#elif defined(__CRT_HAVE___libc_setpgid)
/* >> setpgid(2)
 * Change  the ID of  the process group  associated with `pid's process.
 * (That is the TID of the leader of the process group of `pid's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER = THREAD[PGID]
 * When `pid' is ZERO(0), use `gettid()' for it instead.
 * When `pgid' is ZERO(0), use `pid' (after it was substituted) for instead */
__CREDIRECT(,int,__NOTHROW_NCX,setpgid,(__pid_t __pid, __pid_t __pgid),__libc_setpgid,(__pid,__pgid))
#endif /* ... */
#ifdef __CRT_HAVE_setsid
/* >> setsid(2)
 * Make the calling thread's process the leader of its associated
 * process group, before also making  it its own session  leader.
 * Then return the TID of that new session leader, which is also the PID of the calling process.
 *  - THIS_THREAD->LEADER->GROUP_LEADER                 = THIS_THREAD->LEADER;
 *  - THIS_THREAD->LEADER->GROUP_LEADER->SESSION_LEADER = THIS_THREAD->LEADER->GROUP_LEADER;
 *  - return THIS_THREAD->LEADER->PID; */
__CDECLARE(,__pid_t,__NOTHROW_NCX,setsid,(void),())
#elif defined(__CRT_HAVE___setsid)
/* >> setsid(2)
 * Make the calling thread's process the leader of its associated
 * process group, before also making  it its own session  leader.
 * Then return the TID of that new session leader, which is also the PID of the calling process.
 *  - THIS_THREAD->LEADER->GROUP_LEADER                 = THIS_THREAD->LEADER;
 *  - THIS_THREAD->LEADER->GROUP_LEADER->SESSION_LEADER = THIS_THREAD->LEADER->GROUP_LEADER;
 *  - return THIS_THREAD->LEADER->PID; */
__CREDIRECT(,__pid_t,__NOTHROW_NCX,setsid,(void),__setsid,())
#elif defined(__CRT_HAVE___libc_setsid)
/* >> setsid(2)
 * Make the calling thread's process the leader of its associated
 * process group, before also making  it its own session  leader.
 * Then return the TID of that new session leader, which is also the PID of the calling process.
 *  - THIS_THREAD->LEADER->GROUP_LEADER                 = THIS_THREAD->LEADER;
 *  - THIS_THREAD->LEADER->GROUP_LEADER->SESSION_LEADER = THIS_THREAD->LEADER->GROUP_LEADER;
 *  - return THIS_THREAD->LEADER->PID; */
__CREDIRECT(,__pid_t,__NOTHROW_NCX,setsid,(void),__libc_setsid,())
#endif /* ... */
#ifdef __CRT_HAVE_getuid
/* >> getuid(2)
 * Return the real user ID of the calling process */
__CDECLARE(__ATTR_WUNUSED,__uid_t,__NOTHROW_NCX,getuid,(void),())
#elif defined(__CRT_HAVE___getuid)
/* >> getuid(2)
 * Return the real user ID of the calling process */
__CREDIRECT(__ATTR_WUNUSED,__uid_t,__NOTHROW_NCX,getuid,(void),__getuid,())
#elif defined(__CRT_HAVE___libc_getuid)
/* >> getuid(2)
 * Return the real user ID of the calling process */
__CREDIRECT(__ATTR_WUNUSED,__uid_t,__NOTHROW_NCX,getuid,(void),__libc_getuid,())
#elif defined(__CRT_HAVE_getresuid)
#include <libc/local/unistd/getuid.h>
/* >> getuid(2)
 * Return the real user ID of the calling process */
__NAMESPACE_LOCAL_USING_OR_IMPL(getuid, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __uid_t __NOTHROW_NCX(__LIBCCALL getuid)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getuid))(); })
#endif /* ... */
#ifdef __CRT_HAVE_getgid
/* >> getgid(2)
 * Return the real group ID of the calling process */
__CDECLARE(__ATTR_WUNUSED,__gid_t,__NOTHROW_NCX,getgid,(void),())
#elif defined(__CRT_HAVE___getgid)
/* >> getgid(2)
 * Return the real group ID of the calling process */
__CREDIRECT(__ATTR_WUNUSED,__gid_t,__NOTHROW_NCX,getgid,(void),__getgid,())
#elif defined(__CRT_HAVE___libc_getgid)
/* >> getgid(2)
 * Return the real group ID of the calling process */
__CREDIRECT(__ATTR_WUNUSED,__gid_t,__NOTHROW_NCX,getgid,(void),__libc_getgid,())
#elif defined(__CRT_HAVE_getresgid)
#include <libc/local/unistd/getgid.h>
/* >> getgid(2)
 * Return the real group ID of the calling process */
__NAMESPACE_LOCAL_USING_OR_IMPL(getgid, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __gid_t __NOTHROW_NCX(__LIBCCALL getgid)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getgid))(); })
#endif /* ... */
#ifdef __CRT_HAVE_geteuid
/* >> geteuid(2)
 * Return the effective user ID of the calling process */
__CDECLARE(__ATTR_WUNUSED,__uid_t,__NOTHROW_NCX,geteuid,(void),())
#elif defined(__CRT_HAVE___geteuid)
/* >> geteuid(2)
 * Return the effective user ID of the calling process */
__CREDIRECT(__ATTR_WUNUSED,__uid_t,__NOTHROW_NCX,geteuid,(void),__geteuid,())
#elif defined(__CRT_HAVE___libc_geteuid)
/* >> geteuid(2)
 * Return the effective user ID of the calling process */
__CREDIRECT(__ATTR_WUNUSED,__uid_t,__NOTHROW_NCX,geteuid,(void),__libc_geteuid,())
#elif defined(__CRT_HAVE_getresuid)
#include <libc/local/unistd/geteuid.h>
/* >> geteuid(2)
 * Return the effective user ID of the calling process */
__NAMESPACE_LOCAL_USING_OR_IMPL(geteuid, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __uid_t __NOTHROW_NCX(__LIBCCALL geteuid)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(geteuid))(); })
#endif /* ... */
#ifdef __CRT_HAVE_getegid
/* >> getegid(2)
 * Return the effective group ID of the calling process */
__CDECLARE(__ATTR_WUNUSED,__gid_t,__NOTHROW_NCX,getegid,(void),())
#elif defined(__CRT_HAVE___getegid)
/* >> getegid(2)
 * Return the effective group ID of the calling process */
__CREDIRECT(__ATTR_WUNUSED,__gid_t,__NOTHROW_NCX,getegid,(void),__getegid,())
#elif defined(__CRT_HAVE___libc_getegid)
/* >> getegid(2)
 * Return the effective group ID of the calling process */
__CREDIRECT(__ATTR_WUNUSED,__gid_t,__NOTHROW_NCX,getegid,(void),__libc_getegid,())
#elif defined(__CRT_HAVE_getresgid)
#include <libc/local/unistd/getegid.h>
/* >> getegid(2)
 * Return the effective group ID of the calling process */
__NAMESPACE_LOCAL_USING_OR_IMPL(getegid, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __gid_t __NOTHROW_NCX(__LIBCCALL getegid)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getegid))(); })
#endif /* ... */
#ifdef __CRT_HAVE_getgroups
/* >> getgroups(2)
 * @return: * : [count == 0] The required number of groups
 * @return: * : [count != 0] The number of groups that were actually returned
 * @return: -1: [errno == -EINVAL && count != 0] There are more than `count' groups */
__CDECLARE(__ATTR_OUTS(2, 1),int,__NOTHROW_NCX,getgroups,(int __size, __gid_t __list[]),(__size,__list))
#elif defined(__CRT_HAVE___getgroups)
/* >> getgroups(2)
 * @return: * : [count == 0] The required number of groups
 * @return: * : [count != 0] The number of groups that were actually returned
 * @return: -1: [errno == -EINVAL && count != 0] There are more than `count' groups */
__CREDIRECT(__ATTR_OUTS(2, 1),int,__NOTHROW_NCX,getgroups,(int __size, __gid_t __list[]),__getgroups,(__size,__list))
#elif defined(__CRT_HAVE___libc_getgroups)
/* >> getgroups(2)
 * @return: * : [count == 0] The required number of groups
 * @return: * : [count != 0] The number of groups that were actually returned
 * @return: -1: [errno == -EINVAL && count != 0] There are more than `count' groups */
__CREDIRECT(__ATTR_OUTS(2, 1),int,__NOTHROW_NCX,getgroups,(int __size, __gid_t __list[]),__libc_getgroups,(__size,__list))
#endif /* ... */
#ifdef __CRT_HAVE_setuid
/* >> setuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `uid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
__CDECLARE(,int,__NOTHROW_NCX,setuid,(__uid_t __uid),(__uid))
#elif defined(__CRT_HAVE___setuid)
/* >> setuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `uid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
__CREDIRECT(,int,__NOTHROW_NCX,setuid,(__uid_t __uid),__setuid,(__uid))
#elif defined(__CRT_HAVE___libc_setuid)
/* >> setuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `uid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
__CREDIRECT(,int,__NOTHROW_NCX,setuid,(__uid_t __uid),__libc_setuid,(__uid))
#elif defined(__CRT_HAVE_setreuid) || defined(__CRT_HAVE___setreuid) || defined(__CRT_HAVE___libc_setreuid) || defined(__CRT_HAVE_setresuid)
#include <libc/local/unistd/setuid.h>
/* >> setuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `uid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
__NAMESPACE_LOCAL_USING_OR_IMPL(setuid, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL setuid)(__uid_t __uid) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setuid))(__uid); })
#endif /* ... */
#ifdef __CRT_HAVE_setgid
/* >> setgid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `gid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
__CDECLARE(,int,__NOTHROW_NCX,setgid,(__gid_t __gid),(__gid))
#elif defined(__CRT_HAVE___setgid)
/* >> setgid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `gid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
__CREDIRECT(,int,__NOTHROW_NCX,setgid,(__gid_t __gid),__setgid,(__gid))
#elif defined(__CRT_HAVE___libc_setgid)
/* >> setgid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `gid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
__CREDIRECT(,int,__NOTHROW_NCX,setgid,(__gid_t __gid),__libc_setgid,(__gid))
#elif defined(__CRT_HAVE_setreuid) || defined(__CRT_HAVE___setreuid) || defined(__CRT_HAVE___libc_setreuid) || defined(__CRT_HAVE_setresuid)
#include <libc/local/unistd/setgid.h>
/* >> setgid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `gid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
__NAMESPACE_LOCAL_USING_OR_IMPL(setgid, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL setgid)(__gid_t __gid) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setgid))(__gid); })
#endif /* ... */
#if __has_builtin(__builtin_fork) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fork)
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
__CEIDECLARE_GCCNCX(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,fork,(void),{ return __builtin_fork(); })
#elif defined(__CRT_HAVE_fork)
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
__CDECLARE_GCCNCX(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,fork,(void),())
#elif defined(__CRT_HAVE___fork)
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
__CREDIRECT_GCCNCX(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,fork,(void),__fork,())
#elif defined(__CRT_HAVE___libc_fork)
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
__CREDIRECT_GCCNCX(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,fork,(void),__libc_fork,())
#endif /* ... */
#ifdef __CRT_HAVE_alarm
/* >> alarm(2)
 * @return: 0 : No alarm was scheduled before.
 * @return: * : The number of seconds yet to pass before a previous alarm would have elapsed.
 * Schedule an to deliver a `SIGALRM' after letting `seconds' elapse.
 * You may pass `0' for `seconds' to disable a previously scheduled alarm */
__CDECLARE(,unsigned int,__NOTHROW_NCX,alarm,(unsigned int __seconds),(__seconds))
#elif defined(__CRT_HAVE___alarm)
/* >> alarm(2)
 * @return: 0 : No alarm was scheduled before.
 * @return: * : The number of seconds yet to pass before a previous alarm would have elapsed.
 * Schedule an to deliver a `SIGALRM' after letting `seconds' elapse.
 * You may pass `0' for `seconds' to disable a previously scheduled alarm */
__CREDIRECT(,unsigned int,__NOTHROW_NCX,alarm,(unsigned int __seconds),__alarm,(__seconds))
#elif defined(__CRT_HAVE___libc_alarm)
/* >> alarm(2)
 * @return: 0 : No alarm was scheduled before.
 * @return: * : The number of seconds yet to pass before a previous alarm would have elapsed.
 * Schedule an to deliver a `SIGALRM' after letting `seconds' elapse.
 * You may pass `0' for `seconds' to disable a previously scheduled alarm */
__CREDIRECT(,unsigned int,__NOTHROW_NCX,alarm,(unsigned int __seconds),__libc_alarm,(__seconds))
#endif /* ... */
#ifdef __CRT_HAVE_pause
/* >> pause(2)
 * Suspend execution until the delivery of a POSIX_SIGNAL */
__CDECLARE(,int,__NOTHROW_RPC,pause,(void),())
#elif defined(__CRT_HAVE___pause)
/* >> pause(2)
 * Suspend execution until the delivery of a POSIX_SIGNAL */
__CREDIRECT(,int,__NOTHROW_RPC,pause,(void),__pause,())
#elif defined(__CRT_HAVE___libc_pause)
/* >> pause(2)
 * Suspend execution until the delivery of a POSIX_SIGNAL */
__CREDIRECT(,int,__NOTHROW_RPC,pause,(void),__libc_pause,())
#endif /* ... */
#ifdef __CRT_HAVE_fpathconf
/* >> fpathconf(3)
 * @param: name: One   of    `_PC_*'    from    <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `fd'
 * return: * : The configuration limit associated with `name' for `fd'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `fd'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
__CDECLARE(__ATTR_WUNUSED,__LONGPTR_TYPE__,__NOTHROW_RPC,fpathconf,(__fd_t __fd, __STDC_INT_AS_UINT_T __name),(__fd,__name))
#elif defined(__CRT_HAVE___fpathconf)
/* >> fpathconf(3)
 * @param: name: One   of    `_PC_*'    from    <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `fd'
 * return: * : The configuration limit associated with `name' for `fd'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `fd'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
__CREDIRECT(__ATTR_WUNUSED,__LONGPTR_TYPE__,__NOTHROW_RPC,fpathconf,(__fd_t __fd, __STDC_INT_AS_UINT_T __name),__fpathconf,(__fd,__name))
#endif /* ... */
#ifndef __ttyname_defined
#define __ttyname_defined
#ifdef __CRT_HAVE_ttyname
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_RPC,ttyname,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE___ttyname)
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
__CREDIRECT(__ATTR_WUNUSED,char *,__NOTHROW_RPC,ttyname,(__fd_t __fd),__ttyname,(__fd))
#else /* ... */
#include <paths.h>
#include <asm/os/fcntl.h>
#include <bits/os/dirent.h>
#include <asm/os/oflags.h>
#include <bits/os/stat.h>
#if defined(__CRT_HAVE_ttyname_r) || defined(__CRT_HAVE_frealpath4) || ((defined(__CRT_HAVE_opendir) || defined(__CRT_HAVE___libc_opendir) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_opendirat) || defined(__CRT_HAVE_fopendirat) || (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))) || (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))) || defined(__USE_DOS_DIRENT)) && ((defined(__CRT_HAVE_readdirk) && defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE_readdirk64) && defined(__CRT_KOS)) || (defined(__CRT_HAVE_readdir) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE___libc_readdir) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE_readdir64) && !defined(__CRT_KOS)) || (defined(__USE_DOS_DIRENT) && defined(_DIRENT_MATCHES_DIRENT64))) && ((defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__fstat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE_fstat) && defined(__STAT32_MATCHES_STAT64)) || defined(__CRT_HAVE_fstat64)) && ((defined(__CRT_HAVE_klstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_klstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE_lstat) && defined(__STAT32_MATCHES_STAT64)) || defined(__CRT_HAVE_lstat64)) && defined(_PATH_DEV))
#include <libc/local/unistd/ttyname.h>
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
__NAMESPACE_LOCAL_USING_OR_IMPL(ttyname, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED char *__NOTHROW_RPC(__LIBCCALL ttyname)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ttyname))(__fd); })
#else /* __CRT_HAVE_ttyname_r || __CRT_HAVE_frealpath4 || ((__CRT_HAVE_opendir || __CRT_HAVE___libc_opendir || (__AT_FDCWD && (__CRT_HAVE_opendirat || __CRT_HAVE_fopendirat || (__CRT_HAVE_fdopendir && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)))) || (__CRT_HAVE_fdopendir && (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)))) || __USE_DOS_DIRENT) && ((__CRT_HAVE_readdirk && __CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE_readdirk64 && __CRT_KOS) || (__CRT_HAVE_readdir && !__CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE___libc_readdir && !__CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE_readdir64 && !__CRT_KOS) || (__USE_DOS_DIRENT && _DIRENT_MATCHES_DIRENT64)) && ((__CRT_HAVE_kfstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__fstat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__fstat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__fstati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE__fstat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE_fstat && __STAT32_MATCHES_STAT64) || __CRT_HAVE_fstat64) && ((__CRT_HAVE_klstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_klstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__stat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE__stat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE_lstat && __STAT32_MATCHES_STAT64) || __CRT_HAVE_lstat64) && _PATH_DEV) */
#undef __ttyname_defined
#endif /* !__CRT_HAVE_ttyname_r && !__CRT_HAVE_frealpath4 && ((!__CRT_HAVE_opendir && !__CRT_HAVE___libc_opendir && (!__AT_FDCWD || (!__CRT_HAVE_opendirat && !__CRT_HAVE_fopendirat && (!__CRT_HAVE_fdopendir || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)))) && (!__CRT_HAVE_fdopendir || (!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)))) && !__USE_DOS_DIRENT) || ((!__CRT_HAVE_readdirk || !__CRT_KOS || !_DIRENT_MATCHES_DIRENT64) && (!__CRT_HAVE_readdirk64 || !__CRT_KOS) && (!__CRT_HAVE_readdir || __CRT_KOS || !_DIRENT_MATCHES_DIRENT64) && (!__CRT_HAVE___libc_readdir || __CRT_KOS || !_DIRENT_MATCHES_DIRENT64) && (!__CRT_HAVE_readdir64 || __CRT_KOS) && (!__USE_DOS_DIRENT || !_DIRENT_MATCHES_DIRENT64)) || ((!__CRT_HAVE_kfstat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kfstat64 || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE__fstat64 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__fstat64i32 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__fstati64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64) && (!__CRT_HAVE__fstat32i64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64) && (!__CRT_HAVE_fstat || !__STAT32_MATCHES_STAT64) && !__CRT_HAVE_fstat64) || ((!__CRT_HAVE_klstat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_klstat64 || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE__stat64 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__stat64i32 || !__CRT_DOS_PRIMARY || !__USE_TIME_BITS64) && (!__CRT_HAVE__stati64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64) && (!__CRT_HAVE__stat32i64 || !__CRT_DOS_PRIMARY || __USE_TIME_BITS64) && (!__CRT_HAVE_lstat || !__STAT32_MATCHES_STAT64) && !__CRT_HAVE_lstat64) || !_PATH_DEV) */
#endif /* !... */
#endif /* !__ttyname_defined */
#ifdef __CRT_HAVE_ttyname_r
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
__CDECLARE(__ATTR_OUTS(2, 3),__errno_t,__NOTHROW_RPC,ttyname_r,(__fd_t __fd, char *__buf, size_t __buflen),(__fd,__buf,__buflen))
#else /* __CRT_HAVE_ttyname_r */
#include <paths.h>
#include <asm/os/fcntl.h>
#include <bits/os/dirent.h>
#include <asm/os/oflags.h>
#include <bits/os/stat.h>
#if defined(__CRT_HAVE_frealpath4) || ((defined(__CRT_HAVE_opendir) || defined(__CRT_HAVE___libc_opendir) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_opendirat) || defined(__CRT_HAVE_fopendirat) || (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))) || (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))) || defined(__USE_DOS_DIRENT)) && ((defined(__CRT_HAVE_readdirk) && defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE_readdirk64) && defined(__CRT_KOS)) || (defined(__CRT_HAVE_readdir) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE___libc_readdir) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE_readdir64) && !defined(__CRT_KOS)) || (defined(__USE_DOS_DIRENT) && defined(_DIRENT_MATCHES_DIRENT64))) && ((defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__fstat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE_fstat) && defined(__STAT32_MATCHES_STAT64)) || defined(__CRT_HAVE_fstat64)) && ((defined(__CRT_HAVE_klstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_klstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE_lstat) && defined(__STAT32_MATCHES_STAT64)) || defined(__CRT_HAVE_lstat64)) && defined(_PATH_DEV))
#include <libc/local/unistd/ttyname_r.h>
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
__NAMESPACE_LOCAL_USING_OR_IMPL(ttyname_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(2, 3) __errno_t __NOTHROW_RPC(__LIBCCALL ttyname_r)(__fd_t __fd, char *__buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ttyname_r))(__fd, __buf, __buflen); })
#endif /* __CRT_HAVE_frealpath4 || ((__CRT_HAVE_opendir || __CRT_HAVE___libc_opendir || (__AT_FDCWD && (__CRT_HAVE_opendirat || __CRT_HAVE_fopendirat || (__CRT_HAVE_fdopendir && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)))) || (__CRT_HAVE_fdopendir && (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)))) || __USE_DOS_DIRENT) && ((__CRT_HAVE_readdirk && __CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE_readdirk64 && __CRT_KOS) || (__CRT_HAVE_readdir && !__CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE___libc_readdir && !__CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE_readdir64 && !__CRT_KOS) || (__USE_DOS_DIRENT && _DIRENT_MATCHES_DIRENT64)) && ((__CRT_HAVE_kfstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__fstat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__fstat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__fstati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE__fstat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE_fstat && __STAT32_MATCHES_STAT64) || __CRT_HAVE_fstat64) && ((__CRT_HAVE_klstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_klstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__stat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE__stat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE_lstat && __STAT32_MATCHES_STAT64) || __CRT_HAVE_lstat64) && _PATH_DEV) */
#endif /* !__CRT_HAVE_ttyname_r */
#ifdef __CRT_HAVE_tcgetpgrp
/* >> tcgetpgrp(2)
 * Return the foreground process group of a given TTY file descriptor */
__CDECLARE(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,tcgetpgrp,(__fd_t __fd),(__fd))
#else /* __CRT_HAVE_tcgetpgrp */
#include <asm/os/tty.h>
#if (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TIOCGPGRP)
#include <libc/local/unistd/tcgetpgrp.h>
/* >> tcgetpgrp(2)
 * Return the foreground process group of a given TTY file descriptor */
__NAMESPACE_LOCAL_USING_OR_IMPL(tcgetpgrp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __pid_t __NOTHROW_NCX(__LIBCCALL tcgetpgrp)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tcgetpgrp))(__fd); })
#endif /* (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TIOCGPGRP */
#endif /* !__CRT_HAVE_tcgetpgrp */
#ifdef __CRT_HAVE_tcsetpgrp
/* >> tcsetpgrp(2)
 * Set the foreground process group of a given TTY file descriptor */
__CDECLARE(,int,__NOTHROW_NCX,tcsetpgrp,(__fd_t __fd, __pid_t __pgrp_id),(__fd,__pgrp_id))
#else /* __CRT_HAVE_tcsetpgrp */
#include <asm/os/tty.h>
#if (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TIOCSPGRP)
#include <libc/local/unistd/tcsetpgrp.h>
/* >> tcsetpgrp(2)
 * Set the foreground process group of a given TTY file descriptor */
__NAMESPACE_LOCAL_USING_OR_IMPL(tcsetpgrp, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL tcsetpgrp)(__fd_t __fd, __pid_t __pgrp_id) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tcsetpgrp))(__fd, __pgrp_id); })
#endif /* (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TIOCSPGRP */
#endif /* !__CRT_HAVE_tcsetpgrp */
#ifndef __getlogin_defined
#define __getlogin_defined
#ifdef __CRT_HAVE_getlogin
/* >> getlogin(3)
 * Return the login name for the current user, or `NULL' on error.
 * s.a. `getlogin_r()' and `cuserid()' */
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_NCX,getlogin,(void),())
#else /* __CRT_HAVE_getlogin */
#include <libc/template/environ.h>
#if defined(__CRT_HAVE_cuserid) || defined(__CRT_HAVE_getlogin_r) || defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ) || (defined(__CRT_HAVE_getpwuid_r) && (defined(__CRT_HAVE_geteuid) || defined(__CRT_HAVE___geteuid) || defined(__CRT_HAVE___libc_geteuid) || defined(__CRT_HAVE_getresuid)))
#include <libc/local/unistd/getlogin.h>
/* >> getlogin(3)
 * Return the login name for the current user, or `NULL' on error.
 * s.a. `getlogin_r()' and `cuserid()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(getlogin, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL getlogin)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getlogin))(); })
#else /* __CRT_HAVE_cuserid || __CRT_HAVE_getlogin_r || __CRT_HAVE_getenv || __LOCAL_environ || (__CRT_HAVE_getpwuid_r && (__CRT_HAVE_geteuid || __CRT_HAVE___geteuid || __CRT_HAVE___libc_geteuid || __CRT_HAVE_getresuid)) */
#undef __getlogin_defined
#endif /* !__CRT_HAVE_cuserid && !__CRT_HAVE_getlogin_r && !__CRT_HAVE_getenv && !__LOCAL_environ && (!__CRT_HAVE_getpwuid_r || (!__CRT_HAVE_geteuid && !__CRT_HAVE___geteuid && !__CRT_HAVE___libc_geteuid && !__CRT_HAVE_getresuid)) */
#endif /* !__CRT_HAVE_getlogin */
#endif /* !__getlogin_defined */
#ifdef __CRT_HAVE_chown
/* >> chown(2)
 * Change the ownership of a given `file' to `group:owner' */
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,chown,(char const *__file, __uid_t __owner, __gid_t __group),(__file,__owner,__group))
#elif defined(__CRT_HAVE___chown)
/* >> chown(2)
 * Change the ownership of a given `file' to `group:owner' */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,chown,(char const *__file, __uid_t __owner, __gid_t __group),__chown,(__file,__owner,__group))
#elif defined(__CRT_HAVE___libc_chown)
/* >> chown(2)
 * Change the ownership of a given `file' to `group:owner' */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,chown,(char const *__file, __uid_t __owner, __gid_t __group),__libc_chown,(__file,__owner,__group))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_fchownat)
#include <libc/local/unistd/chown.h>
/* >> chown(2)
 * Change the ownership of a given `file' to `group:owner' */
__NAMESPACE_LOCAL_USING_OR_IMPL(chown, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL chown)(char const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(chown))(__file, __owner, __group); })
#endif /* __AT_FDCWD && __CRT_HAVE_fchownat */
#endif /* !... */
#ifdef __CRT_HAVE_pathconf
/* >> pathconf(3)
 * @param: name: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `path'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `path'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
__CDECLARE(__ATTR_IN(1),__LONGPTR_TYPE__,__NOTHROW_RPC,pathconf,(char const *__path, __STDC_INT_AS_UINT_T __name),(__path,__name))
#elif defined(__CRT_HAVE___pathconf)
/* >> pathconf(3)
 * @param: name: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `path'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `path'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
__CREDIRECT(__ATTR_IN(1),__LONGPTR_TYPE__,__NOTHROW_RPC,pathconf,(char const *__path, __STDC_INT_AS_UINT_T __name),__pathconf,(__path,__name))
#else /* ... */
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_fpathconf) || defined(__CRT_HAVE___fpathconf)) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && defined(__O_RDONLY)
#include <libc/local/unistd/pathconf.h>
/* >> pathconf(3)
 * @param: name: One of `_PC_*' from <asm/crt/confname.h>
 * Return a path configuration value associated with `name' for `path'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `path'
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
__NAMESPACE_LOCAL_USING_OR_IMPL(pathconf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __LONGPTR_TYPE__ __NOTHROW_RPC(__LIBCCALL pathconf)(char const *__path, __STDC_INT_AS_UINT_T __name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pathconf))(__path, __name); })
#endif /* (__CRT_HAVE_fpathconf || __CRT_HAVE___fpathconf) && (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && __O_RDONLY */
#endif /* !... */
#ifdef __CRT_HAVE_link
/* >> link(2)
 * Create a hard link from `from', leading to `to' */
__CDECLARE(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_RPC,link,(char const *__from, char const *__to),(__from,__to))
#elif defined(__CRT_HAVE___link)
/* >> link(2)
 * Create a hard link from `from', leading to `to' */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_RPC,link,(char const *__from, char const *__to),__link,(__from,__to))
#elif defined(__CRT_HAVE___libc_link)
/* >> link(2)
 * Create a hard link from `from', leading to `to' */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_RPC,link,(char const *__from, char const *__to),__libc_link,(__from,__to))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_linkat)
#include <libc/local/unistd/link.h>
/* >> link(2)
 * Create a hard link from `from', leading to `to' */
__NAMESPACE_LOCAL_USING_OR_IMPL(link, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_RPC(__LIBCCALL link)(char const *__from, char const *__to) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(link))(__from, __to); })
#endif /* __AT_FDCWD && __CRT_HAVE_linkat */
#endif /* !... */
#ifndef __exit_defined
#define __exit_defined
#ifdef __std_exit_defined
__NAMESPACE_STD_USING(exit)
#elif __has_builtin(__builtin_exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exit)
__CEIDECLARE_GCCNCX(__ATTR_NORETURN,void,__THROWING,exit,(int __status),{ __builtin_exit(__status); })
#elif defined(__CRT_HAVE_exit)
__CDECLARE_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,exit,(int __status),(__status))
#elif defined(__CRT_HAVE_quick_exit)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,exit,(int __status),quick_exit,(__status))
#elif defined(__CRT_HAVE__exit)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,exit,(int __status),_exit,(__status))
#elif defined(__CRT_HAVE__Exit)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,exit,(int __status),_Exit,(__status))
#elif defined(__CRT_HAVE_xexit)
__CREDIRECT_VOID_GCCNCX(__ATTR_NORETURN,__THROWING,exit,(int __status),xexit,(__status))
#else /* ... */
#undef __exit_defined
#endif /* !... */
#endif /* !__exit_defined */
#ifndef __read_defined
#define __read_defined
#ifdef __CRT_HAVE_read
/* >> read(2)
 * Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the  `O_NONBLOCK' flag set,  only read as  much data as  was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
__CDECLARE(__ATTR_OUTS(2, 3),ssize_t,__NOTHROW_RPC,read,(__fd_t __fd, void *__buf, size_t __bufsize),(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__read)
/* >> read(2)
 * Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the  `O_NONBLOCK' flag set,  only read as  much data as  was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
__CREDIRECT(__ATTR_OUTS(2, 3),ssize_t,__NOTHROW_RPC,read,(__fd_t __fd, void *__buf, size_t __bufsize),_read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___read)
/* >> read(2)
 * Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the  `O_NONBLOCK' flag set,  only read as  much data as  was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
__CREDIRECT(__ATTR_OUTS(2, 3),ssize_t,__NOTHROW_RPC,read,(__fd_t __fd, void *__buf, size_t __bufsize),__read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___libc_read)
/* >> read(2)
 * Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the  `O_NONBLOCK' flag set,  only read as  much data as  was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
__CREDIRECT(__ATTR_OUTS(2, 3),ssize_t,__NOTHROW_RPC,read,(__fd_t __fd, void *__buf, size_t __bufsize),__libc_read,(__fd,__buf,__bufsize))
#else /* ... */
#undef __read_defined
#endif /* !... */
#endif /* !__read_defined */
#ifndef __write_defined
#define __write_defined
#ifdef __CRT_HAVE_write
/* >> write(2)
 * Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much  data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
__CDECLARE(__ATTR_INS(2, 3),ssize_t,__NOTHROW_RPC,write,(__fd_t __fd, void const *__buf, size_t __bufsize),(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__write)
/* >> write(2)
 * Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much  data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
__CREDIRECT(__ATTR_INS(2, 3),ssize_t,__NOTHROW_RPC,write,(__fd_t __fd, void const *__buf, size_t __bufsize),_write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___write)
/* >> write(2)
 * Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much  data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
__CREDIRECT(__ATTR_INS(2, 3),ssize_t,__NOTHROW_RPC,write,(__fd_t __fd, void const *__buf, size_t __bufsize),__write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___libc_write)
/* >> write(2)
 * Write up to `bufsize' bytes from `buf' into `fd'
 * When `fd' has the `O_NONBLOCK' flag set, only write as much  data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= bufsize: The actual amount of written bytes
 * @return: 0         : No more data can be written */
__CREDIRECT(__ATTR_INS(2, 3),ssize_t,__NOTHROW_RPC,write,(__fd_t __fd, void const *__buf, size_t __bufsize),__libc_write,(__fd,__buf,__bufsize))
#else /* ... */
#undef __write_defined
#endif /* !... */
#endif /* !__write_defined */
#ifdef __USE_KOS
#ifndef __readall_defined
#define __readall_defined
#ifdef __CRT_HAVE_readall
/* >> readall(3)
 * Same  as `read(2)', however  keep on reading until  `read()' indicates EOF (causing
 * `readall()' to immediately return `0') or the entirety of the given buffer has been
 * filled (in which case `bufsize' is returned).
 * If  an error occurs before all data could be read, try to use SEEK_CUR to rewind
 * the file descriptor by the amount of data that had already been loaded. - Errors
 * during this phase are silently ignored and don't cause `errno' to change */
__CDECLARE(__ATTR_OUTS(2, 3),ssize_t,__NOTHROW_RPC,readall,(__fd_t __fd, void *__buf, size_t __bufsize),(__fd,__buf,__bufsize))
#elif (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)) && defined(__SEEK_CUR)
#include <libc/local/unistd/readall.h>
/* >> readall(3)
 * Same  as `read(2)', however  keep on reading until  `read()' indicates EOF (causing
 * `readall()' to immediately return `0') or the entirety of the given buffer has been
 * filled (in which case `bufsize' is returned).
 * If  an error occurs before all data could be read, try to use SEEK_CUR to rewind
 * the file descriptor by the amount of data that had already been loaded. - Errors
 * during this phase are silently ignored and don't cause `errno' to change */
__NAMESPACE_LOCAL_USING_OR_IMPL(readall, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(2, 3) ssize_t __NOTHROW_RPC(__LIBCCALL readall)(__fd_t __fd, void *__buf, size_t __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(readall))(__fd, __buf, __bufsize); })
#else /* ... */
#undef __readall_defined
#endif /* !... */
#endif /* !__readall_defined */
#ifndef __writeall_defined
#define __writeall_defined
#ifdef __CRT_HAVE_writeall
/* >> writeall(3)
 * Same as `write(2)', however keep on  writing until `write()' indicates EOF  (causing
 * `writeall()' to immediately return `0') or the entirety of the given buffer has been
 * written (in which case `bufsize' is returned). */
__CDECLARE(__ATTR_INS(2, 3),ssize_t,__NOTHROW_RPC,writeall,(__fd_t __fd, void const *__buf, size_t __bufsize),(__fd,__buf,__bufsize))
#else /* __CRT_HAVE_writeall */
#include <bits/crt/format-printer.h>
#if defined(__CRT_HAVE_write_printer) && defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_INT__ == __SIZEOF_POINTER__
/* >> writeall(3)
 * Same as `write(2)', however keep on  writing until `write()' indicates EOF  (causing
 * `writeall()' to immediately return `0') or the entirety of the given buffer has been
 * written (in which case `bufsize' is returned). */
__CREDIRECT(__ATTR_INS(2, 3),ssize_t,__NOTHROW_RPC,writeall,(__fd_t __fd, void const *__buf, size_t __bufsize),write_printer,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)
#include <libc/local/unistd/writeall.h>
/* >> writeall(3)
 * Same as `write(2)', however keep on  writing until `write()' indicates EOF  (causing
 * `writeall()' to immediately return `0') or the entirety of the given buffer has been
 * written (in which case `bufsize' is returned). */
__NAMESPACE_LOCAL_USING_OR_IMPL(writeall, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) ssize_t __NOTHROW_RPC(__LIBCCALL writeall)(__fd_t __fd, void const *__buf, size_t __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(writeall))(__fd, __buf, __bufsize); })
#else /* ... */
#undef __writeall_defined
#endif /* !... */
#endif /* !__CRT_HAVE_writeall */
#endif /* !__writeall_defined */
#include <bits/crt/format-printer.h>
#if defined(__CRT_HAVE_writeall) && defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_INT__ == __SIZEOF_POINTER__
/* >> write_printer(3)
 * A pformatprinter-compatible consumer that dumps all input data into `fd' by use
 * of `writeall(3)'. The given `fd' should be encoded by  `WRITE_PRINTER_ARG(fd)'.
 * @return: * : Same as `writeall(3)' */
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3),ssize_t,__NOTHROW_RPC,__FORMATPRINTER_CC,write_printer,(void *__fd, char const *__restrict __buf, size_t __bufsize),writeall,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE_write_printer)
/* >> write_printer(3)
 * A pformatprinter-compatible consumer that dumps all input data into `fd' by use
 * of `writeall(3)'. The given `fd' should be encoded by  `WRITE_PRINTER_ARG(fd)'.
 * @return: * : Same as `writeall(3)' */
__LIBC __ATTR_INS(2, 3) ssize_t __NOTHROW_RPC(__FORMATPRINTER_CC write_printer)(void *__fd, char const *__restrict __buf, size_t __bufsize) __CASMNAME_SAME("write_printer");
#elif defined(__CRT_HAVE_writeall) || defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)
#include <libc/local/unistd/write_printer.h>
/* >> write_printer(3)
 * A pformatprinter-compatible consumer that dumps all input data into `fd' by use
 * of `writeall(3)'. The given `fd' should be encoded by  `WRITE_PRINTER_ARG(fd)'.
 * @return: * : Same as `writeall(3)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(write_printer, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) ssize_t __NOTHROW_RPC(__FORMATPRINTER_CC write_printer)(void *__fd, char const *__restrict __buf, size_t __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(write_printer))(__fd, __buf, __bufsize); })
#endif /* ... */

/* >> void *WRITE_PRINTER_ARG(fd_t fd);
 * Encode a given `fd' as an argument to `write_printer(3)' */
#define WRITE_PRINTER_ARG(fd) ((void *)(__UINTPTR_TYPE__)(__CRT_PRIVATE_UINT(__SIZEOF_FD_T__))(fd))
#endif /* __USE_KOS */

#ifndef __lseek_defined
#define __lseek_defined
#if defined(__CRT_HAVE_lseek) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CDECLARE(,__off_t,__NOTHROW_NCX,lseek,(__fd_t __fd, __off_t __offset, __STDC_INT_AS_UINT_T __whence),(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseek) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__off_t,__NOTHROW_NCX,lseek,(__fd_t __fd, __off_t __offset, __STDC_INT_AS_UINT_T __whence),_lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___lseek) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__off_t,__NOTHROW_NCX,lseek,(__fd_t __fd, __off_t __offset, __STDC_INT_AS_UINT_T __whence),__lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___libc_lseek) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__off_t,__NOTHROW_NCX,lseek,(__fd_t __fd, __off_t __offset, __STDC_INT_AS_UINT_T __whence),__libc_lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__off_t,__NOTHROW_NCX,lseek,(__fd_t __fd, __off_t __offset, __STDC_INT_AS_UINT_T __whence),lseek64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_llseek) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__off_t,__NOTHROW_NCX,lseek,(__fd_t __fd, __off_t __offset, __STDC_INT_AS_UINT_T __whence),llseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___llseek) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__off_t,__NOTHROW_NCX,lseek,(__fd_t __fd, __off_t __offset, __STDC_INT_AS_UINT_T __whence),__llseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseeki64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__off_t,__NOTHROW_NCX,lseek,(__fd_t __fd, __off_t __offset, __STDC_INT_AS_UINT_T __whence),_lseeki64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)
#include <libc/local/unistd/lseek.h>
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__NAMESPACE_LOCAL_USING_OR_IMPL(lseek, __FORCELOCAL __ATTR_ARTIFICIAL __off_t __NOTHROW_NCX(__LIBCCALL lseek)(__fd_t __fd, __off_t __offset, __STDC_INT_AS_UINT_T __whence) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lseek))(__fd, __offset, __whence); })
#else /* ... */
#undef __lseek_defined
#endif /* !... */
#endif /* !__lseek_defined */
#ifndef __isatty_defined
#define __isatty_defined
#ifdef __CRT_HAVE_isatty
/* >> isatty(2)
 * Check if the given file handle `fd' refers to a TTY
 * @return: 1: Is a tty
 * @return: 0: Not a tty (`errno' was modified, and is usually set to `ENOTTY') */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,isatty,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE__isatty)
/* >> isatty(2)
 * Check if the given file handle `fd' refers to a TTY
 * @return: 1: Is a tty
 * @return: 0: Not a tty (`errno' was modified, and is usually set to `ENOTTY') */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,isatty,(__fd_t __fd),_isatty,(__fd))
#elif defined(__CRT_HAVE___isatty)
/* >> isatty(2)
 * Check if the given file handle `fd' refers to a TTY
 * @return: 1: Is a tty
 * @return: 0: Not a tty (`errno' was modified, and is usually set to `ENOTTY') */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,isatty,(__fd_t __fd),__isatty,(__fd))
#else /* ... */
#include <asm/os/tty.h>
#if defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))
#include <libc/local/unistd/isatty.h>
/* >> isatty(2)
 * Check if the given file handle `fd' refers to a TTY
 * @return: 1: Is a tty
 * @return: 0: Not a tty (`errno' was modified, and is usually set to `ENOTTY') */
__NAMESPACE_LOCAL_USING_OR_IMPL(isatty, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isatty)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isatty))(__fd); })
#else /* __CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA) */
#undef __isatty_defined
#endif /* !__CRT_HAVE_tcgetattr && !__CRT_HAVE___tcgetattr && ((!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl) || !__TCGETA) */
#endif /* !... */
#endif /* !__isatty_defined */
#ifndef __dup2_defined
#define __dup2_defined
#ifdef __CRT_HAVE_dup2
/* >> dup2(2)
 * @return: newfd: Returns the new handle upon success.
 * Duplicate a file referred to by `oldfd' into `newfd' */
__CDECLARE(,__fd_t,__NOTHROW_NCX,dup2,(__fd_t __oldfd, __fd_t __newfd),(__oldfd,__newfd))
#elif defined(__CRT_HAVE__dup2)
/* >> dup2(2)
 * @return: newfd: Returns the new handle upon success.
 * Duplicate a file referred to by `oldfd' into `newfd' */
__CREDIRECT(,__fd_t,__NOTHROW_NCX,dup2,(__fd_t __oldfd, __fd_t __newfd),_dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE___dup2)
/* >> dup2(2)
 * @return: newfd: Returns the new handle upon success.
 * Duplicate a file referred to by `oldfd' into `newfd' */
__CREDIRECT(,__fd_t,__NOTHROW_NCX,dup2,(__fd_t __oldfd, __fd_t __newfd),__dup2,(__oldfd,__newfd))
#elif defined(__CRT_HAVE___libc_dup2)
/* >> dup2(2)
 * @return: newfd: Returns the new handle upon success.
 * Duplicate a file referred to by `oldfd' into `newfd' */
__CREDIRECT(,__fd_t,__NOTHROW_NCX,dup2,(__fd_t __oldfd, __fd_t __newfd),__libc_dup2,(__oldfd,__newfd))
#else /* ... */
#undef __dup2_defined
#endif /* !... */
#endif /* !__dup2_defined */
#ifndef __dup_defined
#define __dup_defined
#ifdef __CRT_HAVE_dup
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `fd' and return its duplicated handle number */
__CDECLARE(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,dup,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE__dup)
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `fd' and return its duplicated handle number */
__CREDIRECT(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,dup,(__fd_t __fd),_dup,(__fd))
#elif defined(__CRT_HAVE___dup)
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `fd' and return its duplicated handle number */
__CREDIRECT(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,dup,(__fd_t __fd),__dup,(__fd))
#elif defined(__CRT_HAVE___libc_dup)
/* >> dup(2)
 * @return: * : Returns the new handle upon success.
 * Duplicate a file referred to by `fd' and return its duplicated handle number */
__CREDIRECT(__ATTR_WUNUSED,__fd_t,__NOTHROW_NCX,dup,(__fd_t __fd),__libc_dup,(__fd))
#else /* ... */
#undef __dup_defined
#endif /* !... */
#endif /* !__dup_defined */
#ifndef __close_defined
#define __close_defined
#ifdef __CRT_HAVE_close
/* >> close(2)
 * Close a given file descriptor/handle `fd' */
__CDECLARE(,int,__NOTHROW_NCX,close,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE__close)
/* >> close(2)
 * Close a given file descriptor/handle `fd' */
__CREDIRECT(,int,__NOTHROW_NCX,close,(__fd_t __fd),_close,(__fd))
#elif defined(__CRT_HAVE___close)
/* >> close(2)
 * Close a given file descriptor/handle `fd' */
__CREDIRECT(,int,__NOTHROW_NCX,close,(__fd_t __fd),__close,(__fd))
#elif defined(__CRT_HAVE___libc_close)
/* >> close(2)
 * Close a given file descriptor/handle `fd' */
__CREDIRECT(,int,__NOTHROW_NCX,close,(__fd_t __fd),__libc_close,(__fd))
#else /* ... */
#undef __close_defined
#endif /* !... */
#endif /* !__close_defined */
#ifndef __access_defined
#define __access_defined
#ifdef __CRT_HAVE_access
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type'
 * @return: 0 : Access would be granted
 * @return: -1: Access would be denied (s.a. `errno') */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_RPC,access,(char const *__file, __STDC_INT_AS_UINT_T __type),(__file,__type))
#elif defined(__CRT_HAVE__access)
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type'
 * @return: 0 : Access would be granted
 * @return: -1: Access would be denied (s.a. `errno') */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_RPC,access,(char const *__file, __STDC_INT_AS_UINT_T __type),_access,(__file,__type))
#elif defined(__CRT_HAVE___access)
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type'
 * @return: 0 : Access would be granted
 * @return: -1: Access would be denied (s.a. `errno') */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_RPC,access,(char const *__file, __STDC_INT_AS_UINT_T __type),__access,(__file,__type))
#elif defined(__CRT_HAVE___libc_access)
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type'
 * @return: 0 : Access would be granted
 * @return: -1: Access would be denied (s.a. `errno') */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_RPC,access,(char const *__file, __STDC_INT_AS_UINT_T __type),__libc_access,(__file,__type))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_faccessat)
#include <libc/local/unistd/access.h>
/* >> access(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type'
 * @return: 0 : Access would be granted
 * @return: -1: Access would be denied (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(access, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL access)(char const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(access))(__file, __type); })
#else /* __AT_FDCWD && __CRT_HAVE_faccessat */
#undef __access_defined
#endif /* !__AT_FDCWD || !__CRT_HAVE_faccessat */
#endif /* !... */
#endif /* !__access_defined */
#ifndef __chdir_defined
#define __chdir_defined
#ifdef __CRT_HAVE_chdir
/* >> chdir(2)
 * Change the current working directory to `path' */
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,chdir,(char const *__path),(__path))
#elif defined(__CRT_HAVE__chdir)
/* >> chdir(2)
 * Change the current working directory to `path' */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,chdir,(char const *__path),_chdir,(__path))
#elif defined(__CRT_HAVE___chdir)
/* >> chdir(2)
 * Change the current working directory to `path' */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,chdir,(char const *__path),__chdir,(__path))
#elif defined(__CRT_HAVE___libc_chdir)
/* >> chdir(2)
 * Change the current working directory to `path' */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,chdir,(char const *__path),__libc_chdir,(__path))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_fchdirat)
#include <libc/local/unistd/chdir.h>
/* >> chdir(2)
 * Change the current working directory to `path' */
__NAMESPACE_LOCAL_USING_OR_IMPL(chdir, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL chdir)(char const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(chdir))(__path); })
#else /* __AT_FDCWD && __CRT_HAVE_fchdirat */
#undef __chdir_defined
#endif /* !__AT_FDCWD || !__CRT_HAVE_fchdirat */
#endif /* !... */
#endif /* !__chdir_defined */
#ifndef __getcwd_defined
#define __getcwd_defined
#ifdef __CRT_HAVE_getcwd
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CDECLARE(__ATTR_OUT_OPT(1),char *,__NOTHROW_RPC,getcwd,(char *__buf, size_t __bufsize),(__buf,__bufsize))
#elif defined(__CRT_HAVE__getcwd)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT(__ATTR_OUT_OPT(1),char *,__NOTHROW_RPC,getcwd,(char *__buf, size_t __bufsize),_getcwd,(__buf,__bufsize))
#else /* ... */
#undef __getcwd_defined
#endif /* !... */
#endif /* !__getcwd_defined */
#ifndef __unlink_defined
#define __unlink_defined
#ifdef __CRT_HAVE_unlink
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,unlink,(char const *__file),(__file))
#elif defined(__CRT_HAVE__unlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,unlink,(char const *__file),_unlink,(__file))
#elif defined(__CRT_HAVE___unlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,unlink,(char const *__file),__unlink,(__file))
#elif defined(__CRT_HAVE___libc_unlink)
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,unlink,(char const *__file),__libc_unlink,(__file))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
#include <libc/local/unistd/unlink.h>
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `file' */
__NAMESPACE_LOCAL_USING_OR_IMPL(unlink, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL unlink)(char const *__file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unlink))(__file); })
#else /* __AT_FDCWD && __CRT_HAVE_unlinkat */
#undef __unlink_defined
#endif /* !__AT_FDCWD || !__CRT_HAVE_unlinkat */
#endif /* !... */
#endif /* !__unlink_defined */
#ifndef __rmdir_defined
#define __rmdir_defined
#ifdef __CRT_HAVE_rmdir
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,rmdir,(char const *__path),(__path))
#elif defined(__CRT_HAVE__rmdir)
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,rmdir,(char const *__path),_rmdir,(__path))
#elif defined(__CRT_HAVE___rmdir)
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,rmdir,(char const *__path),__rmdir,(__path))
#elif defined(__CRT_HAVE___libc_rmdir)
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,rmdir,(char const *__path),__libc_rmdir,(__path))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat)
#include <libc/local/unistd/rmdir.h>
/* >> rmdir(2)
 * Remove a directory referred to by `path' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rmdir, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL rmdir)(char const *__path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rmdir))(__path); })
#else /* __AT_FDCWD && __AT_REMOVEDIR && __CRT_HAVE_unlinkat */
#undef __rmdir_defined
#endif /* !__AT_FDCWD || !__AT_REMOVEDIR || !__CRT_HAVE_unlinkat */
#endif /* !... */
#endif /* !__rmdir_defined */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_euidaccess
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_RPC,euidaccess,(char const *__file, __STDC_INT_AS_UINT_T __type),(__file,__type))
#elif defined(__CRT_HAVE_eaccess)
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_RPC,euidaccess,(char const *__file, __STDC_INT_AS_UINT_T __type),eaccess,(__file,__type))
#elif defined(__CRT_HAVE__access) && defined(__CRT_DOS)
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_RPC,euidaccess,(char const *__file, __STDC_INT_AS_UINT_T __type),_access,(__file,__type))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__AT_EACCESS) && defined(__CRT_HAVE_faccessat)
#include <libc/local/unistd/euidaccess.h>
/* >> euidaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__NAMESPACE_LOCAL_USING_OR_IMPL(euidaccess, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL euidaccess)(char const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(euidaccess))(__file, __type); })
#endif /* __AT_FDCWD && __AT_EACCESS && __CRT_HAVE_faccessat */
#endif /* !... */
#ifndef __eaccess_defined
#define __eaccess_defined
#ifdef __CRT_HAVE_euidaccess
/* >> eaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_RPC,eaccess,(char const *__file, __STDC_INT_AS_UINT_T __type),euidaccess,(__file,__type))
#elif defined(__CRT_HAVE_eaccess)
/* >> eaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_RPC,eaccess,(char const *__file, __STDC_INT_AS_UINT_T __type),(__file,__type))
#elif defined(__CRT_HAVE__access) && defined(__CRT_DOS)
/* >> eaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_RPC,eaccess,(char const *__file, __STDC_INT_AS_UINT_T __type),_access,(__file,__type))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__AT_EACCESS) && defined(__CRT_HAVE_faccessat)
#include <libc/local/unistd/euidaccess.h>
/* >> eaccess(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `file', testing for `type', using the effective filesystem ids */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL eaccess)(char const *__file, __STDC_INT_AS_UINT_T __type) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(euidaccess))(__file, __type); }
#else /* __AT_FDCWD && __AT_EACCESS && __CRT_HAVE_faccessat */
#undef __eaccess_defined
#endif /* !__AT_FDCWD || !__AT_EACCESS || !__CRT_HAVE_faccessat */
#endif /* !... */
#endif /* !__eaccess_defined */
#endif /* __USE_GNU */

#ifdef __USE_ATFILE
/* >> faccessat(2)
 * @param: type: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `dfd:file', testing for `type' */
__CDECLARE_OPT(__ATTR_IN(2),int,__NOTHROW_RPC,faccessat,(__fd_t __dfd, char const *__file, __STDC_INT_AS_UINT_T __type, __atflag_t __flags),(__dfd,__file,__type,__flags))
/* >> fchownat(2)
 * Change the ownership of a given `dfd:file' to `group:owner' */
__CDECLARE_OPT(__ATTR_IN(2),int,__NOTHROW_RPC,fchownat,(__fd_t __dfd, char const *__file, __uid_t __owner, __gid_t __group, __atflag_t __flags),(__dfd,__file,__owner,__group,__flags))
/* >> linkat(2)
 * Create a hard link from `fromfd:from', leading to `tofd:to' */
__CDECLARE_OPT(__ATTR_IN(2) __ATTR_IN(4),int,__NOTHROW_RPC,linkat,(__fd_t __fromfd, char const *__from, __fd_t __tofd, char const *__to, __atflag_t __flags),(__fromfd,__from,__tofd,__to,__flags))
#ifdef __CRT_HAVE_symlinkat
/* >> symlinkat(3)
 * Create  a  new  symbolic  link  loaded  with  `link_text'  as link
 * text, at the filesystem location referred to by `tofd:target_path' */
__CDECLARE(__ATTR_IN(1) __ATTR_IN(3),int,__NOTHROW_RPC,symlinkat,(char const *__link_text, __fd_t __tofd, char const *__target_path),(__link_text,__tofd,__target_path))
#elif defined(__CRT_HAVE_fsymlinkat)
#include <libc/local/unistd/symlinkat.h>
/* >> symlinkat(3)
 * Create  a  new  symbolic  link  loaded  with  `link_text'  as link
 * text, at the filesystem location referred to by `tofd:target_path' */
__NAMESPACE_LOCAL_USING_OR_IMPL(symlinkat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN(3) int __NOTHROW_RPC(__LIBCCALL symlinkat)(char const *__link_text, __fd_t __tofd, char const *__target_path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(symlinkat))(__link_text, __tofd, __target_path); })
#endif /* ... */
#ifdef __CRT_HAVE_readlinkat
/* >> readlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__CDECLARE(__ATTR_IN(2) __ATTR_OUTS(3, 4),ssize_t,__NOTHROW_RPC,readlinkat,(__fd_t __dfd, char const *__path, char *__buf, size_t __buflen),(__dfd,__path,__buf,__buflen))
#elif defined(__CRT_HAVE_freadlinkat)
#include <libc/local/unistd/readlinkat.h>
/* >> readlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__NAMESPACE_LOCAL_USING_OR_IMPL(readlinkat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_OUTS(3, 4) ssize_t __NOTHROW_RPC(__LIBCCALL readlinkat)(__fd_t __dfd, char const *__path, char *__buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(readlinkat))(__dfd, __path, __buf, __buflen); })
#endif /* ... */
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `dfd:name' */
__CDECLARE_OPT(__ATTR_IN(2),int,__NOTHROW_RPC,unlinkat,(__fd_t __dfd, char const *__name, __atflag_t __flags),(__dfd,__name,__flags))
#ifdef __USE_KOS
/* >> fchdirat(2)
 * Change the current working directory to `dfd:path'
 * @param: flags: Set of `0 | AT_DOSPATH' */
__CDECLARE_OPT(__ATTR_IN(2),int,__NOTHROW_RPC,fchdirat,(__fd_t __dfd, char const *__path, __atflag_t __flags),(__dfd,__path,__flags))
/* >> fsymlinkat(3)
 * Create  a  new  symbolic  link  loaded  with  `link_text'  as link
 * text, at the filesystem location referred to by `tofd:target_path'
 * @param flags: Set of `0 | AT_DOSPATH' */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_IN(3),int,__NOTHROW_RPC,fsymlinkat,(char const *__link_text, __fd_t __tofd, char const *__target_path, __atflag_t __flags),(__link_text,__tofd,__target_path,__flags))
/* >> freadlinkat(2)
 * Read the text of a symbolic link under `dfd:path' into the provided buffer.
 * @param flags: Set of `AT_DOSPATH | AT_READLINK_REQSIZE' */
__CDECLARE_OPT(__ATTR_IN(2) __ATTR_OUTS(3, 4),ssize_t,__NOTHROW_RPC,freadlinkat,(__fd_t __dfd, char const *__path, char *__buf, size_t __buflen, __atflag_t __flags),(__dfd,__path,__buf,__buflen,__flags))
#endif /* __USE_KOS */
#endif /* __USE_ATFILE */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_lseek) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseek) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),_lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___lseek) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),__lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___libc_lseek) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),__libc_lseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek64)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CDECLARE(,__off64_t,__NOTHROW_NCX,lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),(__fd,__offset,__whence))
#elif defined(__CRT_HAVE__lseeki64)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),_lseeki64,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_llseek)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),llseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE___llseek)
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__CREDIRECT(,__off64_t,__NOTHROW_NCX,lseek64,(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence),__llseek,(__fd,__offset,__whence))
#elif defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)
#include <libc/local/unistd/lseek64.h>
/* >> lseek(2), lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `fd' */
__NAMESPACE_LOCAL_USING_OR_IMPL(lseek64, __FORCELOCAL __ATTR_ARTIFICIAL __off64_t __NOTHROW_NCX(__LIBCCALL lseek64)(__fd_t __fd, __off64_t __offset, __STDC_INT_AS_UINT_T __whence) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lseek64))(__fd, __offset, __whence); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
#if defined(__CRT_HAVE_pread) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> pread(2), pread64(2)
 * Read data from a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of read bytes */
__CDECLARE(__ATTR_OUTS(2, 3),ssize_t,__NOTHROW_RPC,pread,(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE___libc_pread) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> pread(2), pread64(2)
 * Read data from a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of read bytes */
__CREDIRECT(__ATTR_OUTS(2, 3),ssize_t,__NOTHROW_RPC,pread,(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET __offset),__libc_pread,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pread64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> pread(2), pread64(2)
 * Read data from a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of read bytes */
__CREDIRECT(__ATTR_OUTS(2, 3),ssize_t,__NOTHROW_RPC,pread,(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET __offset),pread64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE___pread64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> pread(2), pread64(2)
 * Read data from a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of read bytes */
__CREDIRECT(__ATTR_OUTS(2, 3),ssize_t,__NOTHROW_RPC,pread,(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET __offset),__pread64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pread64) || defined(__CRT_HAVE___pread64) || defined(__CRT_HAVE_pread) || ((defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && defined(__SEEK_CUR) && defined(__SEEK_SET))
#include <libc/local/unistd/pread.h>
/* >> pread(2), pread64(2)
 * Read data from a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of read bytes */
__NAMESPACE_LOCAL_USING_OR_IMPL(pread, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(2, 3) ssize_t __NOTHROW_RPC(__LIBCCALL pread)(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pread))(__fd, __buf, __bufsize, __offset); })
#endif /* ... */
#if defined(__CRT_HAVE_pwrite) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> pwrite(2), pwrite64(2)
 * Write data to a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of written bytes */
__CDECLARE(__ATTR_INS(2, 3),ssize_t,__NOTHROW_RPC,pwrite,(__fd_t __fd, void const *__buf, size_t __bufsize, __PIO_OFFSET __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE___libc_pwrite) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> pwrite(2), pwrite64(2)
 * Write data to a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of written bytes */
__CREDIRECT(__ATTR_INS(2, 3),ssize_t,__NOTHROW_RPC,pwrite,(__fd_t __fd, void const *__buf, size_t __bufsize, __PIO_OFFSET __offset),__libc_pwrite,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pwrite64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> pwrite(2), pwrite64(2)
 * Write data to a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of written bytes */
__CREDIRECT(__ATTR_INS(2, 3),ssize_t,__NOTHROW_RPC,pwrite,(__fd_t __fd, void const *__buf, size_t __bufsize, __PIO_OFFSET __offset),pwrite64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE___pwrite64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> pwrite(2), pwrite64(2)
 * Write data to a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of written bytes */
__CREDIRECT(__ATTR_INS(2, 3),ssize_t,__NOTHROW_RPC,pwrite,(__fd_t __fd, void const *__buf, size_t __bufsize, __PIO_OFFSET __offset),__pwrite64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pwrite64) || defined(__CRT_HAVE___pwrite64) || defined(__CRT_HAVE_pwrite) || ((defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && defined(__SEEK_CUR) && defined(__SEEK_SET))
#include <libc/local/unistd/pwrite.h>
/* >> pwrite(2), pwrite64(2)
 * Write data to a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of written bytes */
__NAMESPACE_LOCAL_USING_OR_IMPL(pwrite, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) ssize_t __NOTHROW_RPC(__LIBCCALL pwrite)(__fd_t __fd, void const *__buf, size_t __bufsize, __PIO_OFFSET __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pwrite))(__fd, __buf, __bufsize, __offset); })
#endif /* ... */

#ifdef __USE_KOS
#if defined(__CRT_HAVE_preadall) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> preadall(3), preadall64(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
__CDECLARE(__ATTR_OUTS(2, 3),ssize_t,__NOTHROW_RPC,preadall,(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_preadall64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> preadall(3), preadall64(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
__CREDIRECT(__ATTR_OUTS(2, 3),ssize_t,__NOTHROW_RPC,preadall,(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET __offset),preadall64,(__fd,__buf,__bufsize,__offset))
#elif (defined(__CRT_HAVE___libc_pread) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) || defined(__CRT_HAVE_pread64) || defined(__CRT_HAVE___pread64) || defined(__CRT_HAVE_pread) || ((defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && defined(__SEEK_CUR) && defined(__SEEK_SET))
#include <libc/local/unistd/preadall.h>
/* >> preadall(3), preadall64(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(preadall, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(2, 3) ssize_t __NOTHROW_RPC(__LIBCCALL preadall)(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(preadall))(__fd, __buf, __bufsize, __offset); })
#endif /* ... */
#if defined(__CRT_HAVE_pwriteall) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> pwriteall(3), pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
__CDECLARE(__ATTR_INS(2, 3),ssize_t,__NOTHROW_RPC,pwriteall,(__fd_t __fd, void const *__buf, size_t __bufsize, __PIO_OFFSET __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pwriteall64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> pwriteall(3), pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
__CREDIRECT(__ATTR_INS(2, 3),ssize_t,__NOTHROW_RPC,pwriteall,(__fd_t __fd, void const *__buf, size_t __bufsize, __PIO_OFFSET __offset),pwriteall64,(__fd,__buf,__bufsize,__offset))
#elif (defined(__CRT_HAVE___libc_pwrite) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) || defined(__CRT_HAVE_pwrite64) || defined(__CRT_HAVE___pwrite64) || defined(__CRT_HAVE_pwrite) || ((defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && defined(__SEEK_CUR) && defined(__SEEK_SET))
#include <libc/local/unistd/pwriteall.h>
/* >> pwriteall(3), pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(pwriteall, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) ssize_t __NOTHROW_RPC(__LIBCCALL pwriteall)(__fd_t __fd, void const *__buf, size_t __bufsize, __PIO_OFFSET __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pwriteall))(__fd, __buf, __bufsize, __offset); })
#endif /* ... */
#endif /* __USE_KOS */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_pread) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> pread(2), pread64(2)
 * Read data from a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of read bytes */
__CREDIRECT(__ATTR_OUTS(2, 3),ssize_t,__NOTHROW_RPC,pread64,(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET64 __offset),pread,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pread64)
/* >> pread(2), pread64(2)
 * Read data from a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of read bytes */
__CDECLARE(__ATTR_OUTS(2, 3),ssize_t,__NOTHROW_RPC,pread64,(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET64 __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE___pread64)
/* >> pread(2), pread64(2)
 * Read data from a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of read bytes */
__CREDIRECT(__ATTR_OUTS(2, 3),ssize_t,__NOTHROW_RPC,pread64,(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET64 __offset),__pread64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pread) || ((defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && defined(__SEEK_CUR) && defined(__SEEK_SET))
#include <libc/local/unistd/pread64.h>
/* >> pread(2), pread64(2)
 * Read data from a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of read bytes */
__NAMESPACE_LOCAL_USING_OR_IMPL(pread64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(2, 3) ssize_t __NOTHROW_RPC(__LIBCCALL pread64)(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET64 __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pread64))(__fd, __buf, __bufsize, __offset); })
#endif /* ... */
#if defined(__CRT_HAVE_pwrite) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> pwrite(2), pwrite64(2)
 * Write data to a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of written bytes */
__CREDIRECT(__ATTR_INS(2, 3),ssize_t,__NOTHROW_RPC,pwrite64,(__fd_t __fd, void const *__buf, size_t __bufsize, __PIO_OFFSET64 __offset),pwrite,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pwrite64)
/* >> pwrite(2), pwrite64(2)
 * Write data to a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of written bytes */
__CDECLARE(__ATTR_INS(2, 3),ssize_t,__NOTHROW_RPC,pwrite64,(__fd_t __fd, void const *__buf, size_t __bufsize, __PIO_OFFSET64 __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE___pwrite64)
/* >> pwrite(2), pwrite64(2)
 * Write data to a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of written bytes */
__CREDIRECT(__ATTR_INS(2, 3),ssize_t,__NOTHROW_RPC,pwrite64,(__fd_t __fd, void const *__buf, size_t __bufsize, __PIO_OFFSET64 __offset),__pwrite64,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pwrite) || ((defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && defined(__SEEK_CUR) && defined(__SEEK_SET))
#include <libc/local/unistd/pwrite64.h>
/* >> pwrite(2), pwrite64(2)
 * Write data to a file at a specific `offset', rather than the current R/W position
 * @return: <= bufsize: The actual amount of written bytes */
__NAMESPACE_LOCAL_USING_OR_IMPL(pwrite64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) ssize_t __NOTHROW_RPC(__LIBCCALL pwrite64)(__fd_t __fd, void const *__buf, size_t __bufsize, __PIO_OFFSET64 __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pwrite64))(__fd, __buf, __bufsize, __offset); })
#endif /* ... */

#ifdef __USE_KOS
#if defined(__CRT_HAVE_preadall) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> preadall(3), preadall64(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
__CREDIRECT(__ATTR_OUTS(2, 3),ssize_t,__NOTHROW_RPC,preadall64,(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET64 __offset),preadall,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_preadall64)
/* >> preadall(3), preadall64(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
__CDECLARE(__ATTR_OUTS(2, 3),ssize_t,__NOTHROW_RPC,preadall64,(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET64 __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pread64) || defined(__CRT_HAVE___pread64) || defined(__CRT_HAVE_pread) || ((defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && defined(__SEEK_CUR) && defined(__SEEK_SET))
#include <libc/local/unistd/preadall64.h>
/* >> preadall(3), preadall64(3)
 * Same as `readall(3)', but using `pread(2)' instead of `read()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(preadall64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(2, 3) ssize_t __NOTHROW_RPC(__LIBCCALL preadall64)(__fd_t __fd, void *__buf, size_t __bufsize, __PIO_OFFSET64 __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(preadall64))(__fd, __buf, __bufsize, __offset); })
#endif /* ... */
#if defined(__CRT_HAVE_pwriteall) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> pwriteall(3), pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
__CREDIRECT(__ATTR_INS(2, 3),ssize_t,__NOTHROW_RPC,pwriteall64,(__fd_t __fd, void const *__buf, size_t __bufsize, __PIO_OFFSET64 __offset),pwriteall,(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pwriteall64)
/* >> pwriteall(3), pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
__CDECLARE(__ATTR_INS(2, 3),ssize_t,__NOTHROW_RPC,pwriteall64,(__fd_t __fd, void const *__buf, size_t __bufsize, __PIO_OFFSET64 __offset),(__fd,__buf,__bufsize,__offset))
#elif defined(__CRT_HAVE_pwrite64) || defined(__CRT_HAVE___pwrite64) || defined(__CRT_HAVE_pwrite) || ((defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && defined(__SEEK_CUR) && defined(__SEEK_SET))
#include <libc/local/unistd/pwriteall64.h>
/* >> pwriteall(3), pwriteall64(3)
 * Same as `writeall(3)', but using `pwrite(2)' instead of `write()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(pwriteall64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) ssize_t __NOTHROW_RPC(__LIBCCALL pwriteall64)(__fd_t __fd, void const *__buf, size_t __bufsize, __PIO_OFFSET64 __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pwriteall64))(__fd, __buf, __bufsize, __offset); })
#endif /* ... */
#endif /* __USE_KOS */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

#if defined(__USE_GNU) || defined(__USE_NETBSD)
#ifdef __CRT_HAVE_dup3
__CDECLARE(,__fd_t,__NOTHROW_NCX,dup3,(__fd_t __oldfd, __fd_t __newfd, __oflag_t __flags),(__oldfd,__newfd,__flags))
#elif defined(__CRT_HAVE_dup2) || defined(__CRT_HAVE__dup2) || defined(__CRT_HAVE___dup2) || defined(__CRT_HAVE___libc_dup2)
#include <libc/local/unistd/dup3.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(dup3, __FORCELOCAL __ATTR_ARTIFICIAL __fd_t __NOTHROW_NCX(__LIBCCALL dup3)(__fd_t __oldfd, __fd_t __newfd, __oflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dup3))(__oldfd, __newfd, __flags); })
#endif /* ... */
#ifdef __CRT_HAVE_pipe2
/* >> pipe2(2)
 * Construct a [reader,writer]-pair of pipes
 * @param: pipedes: Output for pipe fds: [0]: reader; [1]: writer
 * @param: flags:   Set of `O_CLOEXEC | O_CLOFORK | O_NONBLOCK | O_DIRECT'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(__ATTR_OUT(1),int,__NOTHROW_NCX,pipe2,(__fd_t __pipedes[2], __oflag_t __flags),(__pipedes,__flags))
#elif defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)
#include <libc/local/unistd/pipe2.h>
/* >> pipe2(2)
 * Construct a [reader,writer]-pair of pipes
 * @param: pipedes: Output for pipe fds: [0]: reader; [1]: writer
 * @param: flags:   Set of `O_CLOEXEC | O_CLOFORK | O_NONBLOCK | O_DIRECT'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(pipe2, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) int __NOTHROW_NCX(__LIBCCALL pipe2)(__fd_t __pipedes[2], __oflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pipe2))(__pipedes, __flags); })
#endif /* ... */
#endif /* __USE_GNU || __USE_NETBSD */

#ifdef __USE_GNU
#ifndef environ
#ifdef __CRT_HAVE_environ
__CSDECLARE(,char **,environ)
#define environ environ
#elif defined(_environ)
#define environ _environ
#elif defined(__environ)
#define environ __environ
#elif defined(__LOCAL_environ)
#define environ __LOCAL_environ
#elif defined(__CRT_HAVE__environ)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,char **,_environ)
#define _environ _environ
#define environ  _environ
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,char **,environ,_environ)
#define environ environ
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE___environ)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,char **,__environ)
#define __environ _environ
#define environ   __environ
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,char **,environ,__environ)
#define environ environ
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(____p__environ_defined)
#define environ (*__p__environ())
#elif defined(__CRT_HAVE___p__environ)
#define ____p__environ_defined
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,char ***,__NOTHROW,__p__environ,(void),())
#define environ (*__p__environ())
#elif defined(__CRT_HAVE__get_environ)
#ifndef ___get_environ_defined
#define ___get_environ_defined
__CDECLARE(,int,__NOTHROW,_get_environ,(char ***__p_environ),())
#endif /* !___get_environ_defined */
#ifndef _____get_environ_wrapper_defined
#define _____get_environ_wrapper_defined
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST char **
__NOTHROW(__LIBCCALL ___get_environ_wrapper)(void) {
	char const **__result;
	if __unlikely(_get_environ(&__result) != 0)
		__result = __NULLPTR;
	return __result;
}
#endif /* !_____get_environ_wrapper_defined */
#define environ ___get_environ_wrapper()
#endif /* !... */
#endif /* !environ */
#ifdef __CRT_HAVE_get_current_dir_name
/* >> get_current_dir_name(3)
 * Return an malloc(3)'d string  representing the current working  directory
 * This is usually the same  as `getcwd(NULL, 0)', however standards  caused
 * this function to be badly designed, as iff `$PWD' is defined and correct,
 * it is strdup(3)'d  and returned (correctness  is determined by  comparing
 * `stat($PWD)' against `stat(".")').
 * Due to the mandatory dependency on `getenv(3)', this function can't be
 * made thread-safe, so try not to use this one. */
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_RPC,get_current_dir_name,(void),())
#elif defined(__CRT_HAVE_getcwd) || defined(__CRT_HAVE__getcwd)
#include <libc/local/unistd/get_current_dir_name.h>
/* >> get_current_dir_name(3)
 * Return an malloc(3)'d string  representing the current working  directory
 * This is usually the same  as `getcwd(NULL, 0)', however standards  caused
 * this function to be badly designed, as iff `$PWD' is defined and correct,
 * it is strdup(3)'d  and returned (correctness  is determined by  comparing
 * `stat($PWD)' against `stat(".")').
 * Due to the mandatory dependency on `getenv(3)', this function can't be
 * made thread-safe, so try not to use this one. */
__NAMESPACE_LOCAL_USING_OR_IMPL(get_current_dir_name, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED char *__NOTHROW_RPC(__LIBCCALL get_current_dir_name)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(get_current_dir_name))(); })
#endif /* ... */
#ifdef __CRT_HAVE_syncfs
__CDECLARE(,int,__NOTHROW_RPC,syncfs,(__fd_t __fd),(__fd))
#else /* __CRT_HAVE_syncfs */
#include <libc/local/unistd/syncfs.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(syncfs, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL syncfs)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(syncfs))(__fd); })
#endif /* !__CRT_HAVE_syncfs */
#ifdef __CRT_HAVE_group_member
/* >> group_member(3)
 * Check if `gid' is an element of `getgroups(2)'
 * @return:  1: Yes, it's a member
 * @return:  0: No, it's not a member
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(,int,__NOTHROW_NCX,group_member,(__gid_t __gid),(__gid))
#else /* __CRT_HAVE_group_member */
#include <hybrid/__alloca.h>
#include <libc/errno.h>
#if (defined(__CRT_HAVE_getgroups) || defined(__CRT_HAVE___getgroups) || defined(__CRT_HAVE___libc_getgroups)) && defined(__hybrid_alloca) && defined(__libc_geterrno) && defined(__EINVAL)
#include <libc/local/unistd/group_member.h>
/* >> group_member(3)
 * Check if `gid' is an element of `getgroups(2)'
 * @return:  1: Yes, it's a member
 * @return:  0: No, it's not a member
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(group_member, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL group_member)(__gid_t __gid) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(group_member))(__gid); })
#endif /* (__CRT_HAVE_getgroups || __CRT_HAVE___getgroups || __CRT_HAVE___libc_getgroups) && __hybrid_alloca && __libc_geterrno && __EINVAL */
#endif /* !__CRT_HAVE_group_member */
/* >> getresuid(2)
 * Get the real, effective, and saved UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_OPT(__ATTR_OUT_OPT(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,getresuid,(__uid_t *__ruid, __uid_t *__euid, __uid_t *__suid),(__ruid,__euid,__suid))
/* >> getresgid(2)
 * Get the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_OPT(__ATTR_OUT_OPT(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,getresgid,(__gid_t *__rgid, __gid_t *__egid, __gid_t *__sgid),(__rgid,__egid,__sgid))
/* >> setresuid(2)
 * Set the real, effective, and saved UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_OPT(,int,__NOTHROW_NCX,setresuid,(__uid_t __ruid, __uid_t __euid, __uid_t __suid),(__ruid,__euid,__suid))
/* >> setresgid(2)
 * Set the real, effective, and saved GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_OPT(,int,__NOTHROW_NCX,setresgid,(__gid_t __rgid, __gid_t __egid, __gid_t __sgid),(__rgid,__egid,__sgid))
#endif /* __USE_GNU */
#if (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8)) || defined(__USE_MISC)
#ifdef __CRT_HAVE_usleep
/* >> usleep(3)
 * Sleep for `useconds' microseconds (1/1.000.000 seconds) */
__CDECLARE(,int,__NOTHROW_RPC,usleep,(__useconds_t __useconds),(__useconds))
#elif defined(__CRT_HAVE_nanosleep64) || defined(__CRT_HAVE_nanosleep) || defined(__CRT_HAVE___nanosleep) || defined(__CRT_HAVE___libc_nanosleep) || defined(__CRT_HAVE___crtSleep) || defined(__CRT_HAVE_delay)
#include <libc/local/unistd/usleep.h>
/* >> usleep(3)
 * Sleep for `useconds' microseconds (1/1.000.000 seconds) */
__NAMESPACE_LOCAL_USING_OR_IMPL(usleep, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL usleep)(__useconds_t __useconds) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(usleep))(__useconds); })
#endif /* ... */
#ifdef __CRT_HAVE_getwd
/* >> getwd(3)
 * Deprecated, alternate variant  of `getcwd()'.  It
 * should be obvious why you shouldn't use this one.
 * And  if it isn't, take a look at the arguments of
 * this function, compared to `getcwd()' */
__CDECLARE(__ATTR_DEPRECATED("Use getcwd()") __ATTR_OUT(1),char *,__NOTHROW_RPC,getwd,(char *__buf),(__buf))
#elif defined(__CRT_HAVE_getcwd) || defined(__CRT_HAVE__getcwd)
#include <libc/local/unistd/getwd.h>
/* >> getwd(3)
 * Deprecated, alternate variant  of `getcwd()'.  It
 * should be obvious why you shouldn't use this one.
 * And  if it isn't, take a look at the arguments of
 * this function, compared to `getcwd()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(getwd, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_DEPRECATED("Use getcwd()") __ATTR_OUT(1) char *__NOTHROW_RPC(__LIBCCALL getwd)(char *__buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getwd))(__buf); })
#endif /* ... */
#ifdef __CRT_HAVE_ualarm
__CDECLARE(,__useconds_t,__NOTHROW_NCX,ualarm,(__useconds_t ___value, __useconds_t __interval),(___value,__interval))
#else /* __CRT_HAVE_ualarm */
#include <asm/os/itimer.h>
#if defined(__ITIMER_REAL) && (defined(__CRT_HAVE_setitimer64) || defined(__CRT_HAVE_setitimer) || defined(__CRT_HAVE___setitimer) || defined(__CRT_HAVE___libc_setitimer))
#include <libc/local/unistd/ualarm.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ualarm, __FORCELOCAL __ATTR_ARTIFICIAL __useconds_t __NOTHROW_NCX(__LIBCCALL ualarm)(__useconds_t ___value, __useconds_t __interval) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ualarm))(___value, __interval); })
#endif /* __ITIMER_REAL && (__CRT_HAVE_setitimer64 || __CRT_HAVE_setitimer || __CRT_HAVE___setitimer || __CRT_HAVE___libc_setitimer) */
#endif /* !__CRT_HAVE_ualarm */
#ifndef __vfork_defined
#define __vfork_defined
#ifdef __CRT_HAVE_vfork
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
__CDECLARE(__ATTR_RETURNS_TWICE __ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,vfork,(void),())
#elif defined(__CRT_HAVE___vfork)
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
__CREDIRECT(__ATTR_RETURNS_TWICE __ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,vfork,(void),__vfork,())
#elif defined(__CRT_HAVE___libc_vfork)
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
__CREDIRECT(__ATTR_RETURNS_TWICE __ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,vfork,(void),__libc_vfork,())
#else /* ... */
#undef __vfork_defined
#endif /* !... */
#endif /* !__vfork_defined */
#endif /* (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K8) || __USE_MISC */
#ifdef __CRT_HAVE_fchown
/* >> fchown(2)
 * Change the ownership of a given `fd' to `group:owner' */
__CDECLARE(,int,__NOTHROW_RPC,fchown,(__fd_t __fd, __uid_t __owner, __gid_t __group),(__fd,__owner,__group))
#elif defined(__CRT_HAVE___fchown)
/* >> fchown(2)
 * Change the ownership of a given `fd' to `group:owner' */
__CREDIRECT(,int,__NOTHROW_RPC,fchown,(__fd_t __fd, __uid_t __owner, __gid_t __group),__fchown,(__fd,__owner,__group))
#elif defined(__CRT_HAVE___libc_fchown)
/* >> fchown(2)
 * Change the ownership of a given `fd' to `group:owner' */
__CREDIRECT(,int,__NOTHROW_RPC,fchown,(__fd_t __fd, __uid_t __owner, __gid_t __group),__libc_fchown,(__fd,__owner,__group))
#endif /* ... */
#ifdef __CRT_HAVE_fchdir
/* >> fchdir(2)
 * Change the current working directory to `path' */
__CDECLARE(,int,__NOTHROW_RPC,fchdir,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE___fchdir)
/* >> fchdir(2)
 * Change the current working directory to `path' */
__CREDIRECT(,int,__NOTHROW_RPC,fchdir,(__fd_t __fd),__fchdir,(__fd))
#elif defined(__CRT_HAVE___libc_fchdir)
/* >> fchdir(2)
 * Change the current working directory to `path' */
__CREDIRECT(,int,__NOTHROW_RPC,fchdir,(__fd_t __fd),__libc_fchdir,(__fd))
#endif /* ... */
#ifdef __CRT_HAVE_getpgid
/* >> getpgid(2)
 * Return  the ID of  the process group  associated with `pid's process.
 * (That is the TID of the leader of the process group of `pid's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER->PID
 * When `pid' is ZERO(0), use `gettid()' for it instead */
__CDECLARE(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,getpgid,(__pid_t __pid),(__pid))
#elif defined(__CRT_HAVE___getpgid)
/* >> getpgid(2)
 * Return  the ID of  the process group  associated with `pid's process.
 * (That is the TID of the leader of the process group of `pid's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER->PID
 * When `pid' is ZERO(0), use `gettid()' for it instead */
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,getpgid,(__pid_t __pid),__getpgid,(__pid))
#elif defined(__CRT_HAVE___libc_getpgid)
/* >> getpgid(2)
 * Return  the ID of  the process group  associated with `pid's process.
 * (That is the TID of the leader of the process group of `pid's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER->PID
 * When `pid' is ZERO(0), use `gettid()' for it instead */
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,getpgid,(__pid_t __pid),__libc_getpgid,(__pid))
#elif defined(__CRT_HAVE___bsd_getpgrp)
/* >> getpgid(2)
 * Return  the ID of  the process group  associated with `pid's process.
 * (That is the TID of the leader of the process group of `pid's leader)
 * THREAD[PID]->LEADER->GROUP_LEADER->PID
 * When `pid' is ZERO(0), use `gettid()' for it instead */
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,getpgid,(__pid_t __pid),__bsd_getpgrp,(__pid))
#endif /* ... */
#ifdef __CRT_HAVE_getsid
/* >> getsid(2)
 * Return the ID of the session which a process `pid' is apart of.
 * return  THREAD[PID]->LEADER->GROUP_LEADER->SESSION_LEADER->PID; */
__CDECLARE(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,getsid,(__pid_t __pid),(__pid))
#elif defined(__CRT_HAVE___getsid)
/* >> getsid(2)
 * Return the ID of the session which a process `pid' is apart of.
 * return  THREAD[PID]->LEADER->GROUP_LEADER->SESSION_LEADER->PID; */
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,getsid,(__pid_t __pid),__getsid,(__pid))
#elif defined(__CRT_HAVE___libc_getsid)
/* >> getsid(2)
 * Return the ID of the session which a process `pid' is apart of.
 * return  THREAD[PID]->LEADER->GROUP_LEADER->SESSION_LEADER->PID; */
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,getsid,(__pid_t __pid),__libc_getsid,(__pid))
#endif /* ... */
#ifdef __CRT_HAVE_lchown
/* >> lchown(2)
 * Change the ownership of a given `file' to `group:owner',
 * but don't reference it if  that file is a symbolic  link */
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,lchown,(char const *__file, __uid_t __owner, __gid_t __group),(__file,__owner,__group))
#else /* __CRT_HAVE_lchown */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && defined(__CRT_HAVE_fchownat)
#include <libc/local/unistd/lchown.h>
/* >> lchown(2)
 * Change the ownership of a given `file' to `group:owner',
 * but don't reference it if  that file is a symbolic  link */
__NAMESPACE_LOCAL_USING_OR_IMPL(lchown, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL lchown)(char const *__file, __uid_t __owner, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lchown))(__file, __owner, __group); })
#endif /* __AT_FDCWD && __AT_SYMLINK_NOFOLLOW && __CRT_HAVE_fchownat */
#endif /* !__CRT_HAVE_lchown */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
#if defined(__CRT_HAVE_truncate) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_NCX,truncate,(char const *__file, __PIO_OFFSET __length),(__file,__length))
#elif defined(__CRT_HAVE___truncate) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_NCX,truncate,(char const *__file, __PIO_OFFSET __length),__truncate,(__file,__length))
#elif defined(__CRT_HAVE___libc_truncate) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_NCX,truncate,(char const *__file, __PIO_OFFSET __length),__libc_truncate,(__file,__length))
#elif defined(__CRT_HAVE_truncate64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_NCX,truncate,(char const *__file, __PIO_OFFSET __length),truncate64,(__file,__length))
#else /* ... */
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_truncate64) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize))) || defined(__CRT_HAVE_truncate) || defined(__CRT_HAVE___truncate) || defined(__CRT_HAVE___libc_truncate) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize)) && defined(__O_WRONLY))
#include <libc/local/unistd/truncate.h>
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__NAMESPACE_LOCAL_USING_OR_IMPL(truncate, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL truncate)(char const *__file, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(truncate))(__file, __length); })
#endif /* __CRT_HAVE_truncate64 || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open) && (__CRT_HAVE_ftruncate64 || __CRT_HAVE__chsize_s || __CRT_HAVE_ftruncate || __CRT_HAVE___ftruncate || __CRT_HAVE___libc_ftruncate || __CRT_HAVE__chsize || __CRT_HAVE_chsize)) || __CRT_HAVE_truncate || __CRT_HAVE___truncate || __CRT_HAVE___libc_truncate || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_ftruncate64 || __CRT_HAVE__chsize_s || __CRT_HAVE_ftruncate || __CRT_HAVE___ftruncate || __CRT_HAVE___libc_ftruncate || __CRT_HAVE__chsize || __CRT_HAVE_chsize) && __O_WRONLY) */
#endif /* !... */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_truncate) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_NCX,truncate64,(char const *__file, __PIO_OFFSET64 __length),truncate,(__file,__length))
#elif defined(__CRT_HAVE___truncate) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_NCX,truncate64,(char const *__file, __PIO_OFFSET64 __length),__truncate,(__file,__length))
#elif defined(__CRT_HAVE___libc_truncate) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_NCX,truncate64,(char const *__file, __PIO_OFFSET64 __length),__libc_truncate,(__file,__length))
#elif defined(__CRT_HAVE_truncate64)
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_NCX,truncate64,(char const *__file, __PIO_OFFSET64 __length),(__file,__length))
#else /* ... */
#include <asm/os/oflags.h>
#if defined(__CRT_HAVE_truncate) || defined(__CRT_HAVE___truncate) || defined(__CRT_HAVE___libc_truncate) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize)))
#include <libc/local/unistd/truncate64.h>
/* >> truncate(2), truncate64(2)
 * Truncate the given file `file' to a length of `length' */
__NAMESPACE_LOCAL_USING_OR_IMPL(truncate64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL truncate64)(char const *__file, __PIO_OFFSET64 __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(truncate64))(__file, __length); })
#endif /* __CRT_HAVE_truncate || __CRT_HAVE___truncate || __CRT_HAVE___libc_truncate || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open) && (__CRT_HAVE_ftruncate64 || __CRT_HAVE__chsize_s || __CRT_HAVE_ftruncate || __CRT_HAVE___ftruncate || __CRT_HAVE___libc_ftruncate || __CRT_HAVE__chsize || __CRT_HAVE_chsize)) */
#endif /* !... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

#ifdef __USE_XOPEN2K8
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
#endif /* __USE_XOPEN2K8 */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifdef __CRT_HAVE_nice
__CDECLARE(,int,__NOTHROW_NCX,nice,(int __inc),(__inc))
#elif defined(__CRT_HAVE___nice)
__CREDIRECT(,int,__NOTHROW_NCX,nice,(int __inc),__nice,(__inc))
#elif defined(__CRT_HAVE___libc_nice)
__CREDIRECT(,int,__NOTHROW_NCX,nice,(int __inc),__libc_nice,(__inc))
#else /* ... */
#include <libc/local/unistd/nice.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(nice, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL nice)(int __inc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nice))(__inc); })
#endif /* !... */
#endif /* __USE_MISC || __USE_XOPEN */

#ifndef ___exit_defined
#define ___exit_defined
#if __has_builtin(__builtin__Exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE__Exit)
__CEIREDIRECT_GCCNCX(__ATTR_NORETURN,void,__THROWING,_exit,(int __status),_Exit,{ __builtin__Exit(__status); })
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

#ifdef __USE_POSIX2
/* Retrieve a system configuration string specified by `name'
 * @param: name:   One of `_CS_*' from <asm/crt/confname.h>
 * @param: buf:    Target buffer
 * @param: buflen: Available buffer size (including a trailing \0-character)
 * @return: * :    Required buffer size (including a trailing \0-character)
 * @return: 1 :    Empty configuration string.
 * @return: 0 :    [errno=EINVAL] Bad configuration `name'. */
__CDECLARE_OPT(__ATTR_OUTS(2, 3),size_t,__NOTHROW_NCX,confstr,(__STDC_INT_AS_UINT_T __name, char *__buf, size_t __buflen),(__name,__buf,__buflen))

/* >> optarg(3)
 * Set to the argument of the option returned by `getopt(3)' (and friends).
 * When returning an option that doesn't take an argument, `optarg' is  set
 * to `NULL'.
 *
 * Pre-initialized to `NULL' */
#ifndef optarg
#ifdef __LOCAL_optarg
#define optarg __LOCAL_optarg
#elif defined(__CRT_HAVE_optarg)
__CSDECLARE(,char *,optarg)
#define optarg optarg
#endif /* ... */
#endif /* !optarg */

/* >> optind(3)
 * Index of the next `argv'-element that `getopt(3)' (and friends) should parse.
 * In order for parsing to  start over, this should be  set to `1'. In order  to
 * fully re-initialize the getopt-parser, it should be set to `0' (in which case
 * libc will re-load flags from `optstring[0]', and `$POSIXLY_CORRECT').
 *
 * Once all arguments have been processed, `getopt(3)' returns `-1', and `optind'
 * is set to the value of the first non-argument argv-element (when all  elements
 * of `argv' are arguments, it is set to `argc')
 *
 * Pre-initialized to `1' */
#ifndef optind
#ifdef __LOCAL_optind
#define optind __LOCAL_optind
#elif defined(__CRT_HAVE_optind)
__CSDECLARE(,int,optind)
#define optind optind
#endif /* ... */
#endif /* !optind */

/* >> opterr(3)
 * When non-zero, `getopt(3)' will print error messages to `stderr', unless the
 * first character of `optstring' is `:'.  Setting this global variable to  `0'
 * will suppress error messages being  printed, allowing the application to  do
 * its own error-handling without libc doing anything extra.
 *
 * Pre-initialized to `1' */
#ifndef opterr
#ifdef __LOCAL_opterr
#define opterr __LOCAL_opterr
#elif defined(__CRT_HAVE_opterr)
__CSDECLARE(,int,opterr)
#define opterr opterr
#endif /* ... */
#endif /* !opterr */

/* >> optopt(3)
 * Filled in by `getopt(3)' (and friends) with the character-code of a malformed
 * option when one is encountered (this is done alongside an error being printed
 * to `stderr' (but see `opterr'), and `?' being returned by `getopt(3)').
 *
 * In the case of long options (s.a. `getopt_long(3)'), a malformed long option
 * results in that option's `struct option::val' being written to this  global.
 *
 * Pre-initialized to `(unsigned char)'?'' */
#ifndef optopt
#ifdef __LOCAL_optopt
#define optopt __LOCAL_optopt
#elif defined(__CRT_HAVE_optopt)
__CSDECLARE(,int,optopt)
#define optopt optopt
#endif /* ... */
#endif /* !optopt */


#ifndef __getopt_defined
#define __getopt_defined
#if defined(__CRT_HAVE___posix_getopt) && defined(__USE_POSIX2) && !defined(__USE_POSIX_IMPLICITLY) && !defined(__USE_GNU)
/* >> getopt(3), getopt_long(3), getopt_long_only(3)
 * Parse options from arguments, as passed to `main()', and specified by `optstring'.
 * Arguments in `argv' appear in one of the following forms:
 *  - "-x":        Returns "x"                      (assuming `optstring' contains "x")
 *  - "-x -y":     Returns "x"                      (assuming `optstring' contains "x" and "y")
 *  - "-xyz":      Returns "x", "y", and then "z"   (assuming `optstring' contains "x", "y" and "z")
 *  - "-ofoo":     Returns "o", with `optarg="foo"' (assuming `optstring' contains "o:")
 *  - "-o", "foo": Returns "o", with `optarg="foo"' (assuming `optstring' contains "o:")
 * Long options (`getopt_long(3)'-only)appear in the following formats:
 *  - "--out":        Returns `longopts["out"].val'                      (assuming `longopts["out"].has_arg != required_argument')
 *  - "--out=foo":    Returns `longopts["out"].val', with `optarg="foo"' (assuming `longopts["out"].has_arg != no_argument')
 *  - "--out", "foo": Returns `longopts["out"].val', with `optarg="foo"' (assuming `longopts["out"].has_arg != no_argument')
 * When `getopt_long_only(3)' is used, long options may also be written with a single leading "-".
 *
 * This function interacts with the globals variables `optarg', `optind', `opterr' and `optopt'.
 * For  more information on  how these variables/are-used-by `getopt(3)'  (and friends), see the
 * documentation of the respective variable.
 *
 * The first character of `optstring' can be used to affect the behavior of this function:
 *  - '-': Each  non-option argument will be handled as though it was the argument of an option '\1'
 *         In other words: ["/bin/myapp", "-x", "foo", "bar"] (with `optstring="-x:"') would then be
 *         enumerated as  {[getopt:'x',optarg="foo"],  [getopt:1,optarg="bar"],  [getopt:-1]}.  Note
 *         that the special "--" argument still causes `getopt(3)' to return `-1' (with `optind' set
 *         to the 1 plus  the index of the  "--"-argument), even when this  option is used,  meaning
 *         that  when  using  this  option,  the  caller  must  handle  non-option  arguments  like:
 *         >> int opt;
 *         >> while ((opt = getopt(argc, argv, "-xy:z")) != -1) {
 *         >>     if (opt == 1)
 *         >>         handle_non_option_argument(optarg);
 *         >>     ...
 *         >> }
 *         >> while (optind < argc)
 *         >>     handle_non_option_argument(argv[optind++]);
 *         In this case, elements of `argv' are never permutated (and `argv' can be const).
 *  - '+': Stop parsing as soon as the first non-option argument is encountered. This is also the
 *         behavior when `optstring[0]' isn't a special character, and "$POSIXLY_CORRECT" is set,
 *         or `__posix_getopt(3)' was used.
 *         In this case, elements of `argv' are never permutated (and `argv' can be const).
 *  - ...: Default behavior (`optstring[0]'  isn't '-' or  '+'). In this  case, scanning of  `argv'
 *         does not stop at the first non-option argument, but only once the actual end is reached,
 *         or  an argument "--" is encountered. Once that is done, `getopt(3)' will return with the
 *         elements of `argv'  permutated such  that all  non-option arguments  appear (in  correct
 *         order) within `argv', starting at `argv[optind]'.
 *         e.g. Once option processing  is done, ["-afoo", "bar", "-c", "--", "-x"]  will
 *              result in `argv[optind...argc-1]' to be the array ["bar", "-x"] (assuming
 *              an `optstring' similar to "a:cx")
 *  - ':': Same as setting `opterr = 0' (may be combined with any of the other special flags by
 *         writing it _AFTER_ the other special flag; e.g. "+:xy:z")
 *
 * @param: argc: Number of arguments in `argv'
 * @param: argv: Argument vector from `main()' -- Shouldn't  actually be `const' here, since  this
 *               function may permute the  order of elements in  `argv' (to gather all  non-option
 *               arguments at the end), unless `optstring[0] == '+'', `__posix_getopt(3)' is used,
 *               or "$POSIXLY_CORRECT" is defined.
 * @param: optstring: [1..1] Options string (see above)
 * @param: longopts:  [0..1] Long options array (terminated by an all-NULL/0 element)
 * @param: longindex: [0..1] When non-NULL, set to the index of the matched long-option,
 *                           if  one was matched.  If none was (i.e.  a short option was
 *                           matched), the contents of this pointer are left  unchanged.
 * @return: 1 : The given `optstring' starts with '-', and a non-option argument `optarg' was encountered.
 * @return:'?': Error while processing options, or '?' appears in `optstring' (or as an `struct option::val')
 *              In the case of an error (and unless disabled by ':' or `opterr'), a message has already  been
 *              written to `stderr'.
 * @return: 0 : A long option was matched with `struct option::flag != NULL'.
 * @return: * : Either  a short option (return is that option's character-code), or a long-long (return is
 *              that option's `struct option::val', so-long as `struct option::flag == NULL') was matched.
 * @return: -1: Argument processing is done. Non-option arguments are in `argv[optind...argc-1]' */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW_NCX,getopt,(int ___argc, char *const ___argv[], char const *__shortopts),__posix_getopt,(___argc,___argv,__shortopts))
#elif defined(__CRT_HAVE_getopt)
/* >> getopt(3), getopt_long(3), getopt_long_only(3)
 * Parse options from arguments, as passed to `main()', and specified by `optstring'.
 * Arguments in `argv' appear in one of the following forms:
 *  - "-x":        Returns "x"                      (assuming `optstring' contains "x")
 *  - "-x -y":     Returns "x"                      (assuming `optstring' contains "x" and "y")
 *  - "-xyz":      Returns "x", "y", and then "z"   (assuming `optstring' contains "x", "y" and "z")
 *  - "-ofoo":     Returns "o", with `optarg="foo"' (assuming `optstring' contains "o:")
 *  - "-o", "foo": Returns "o", with `optarg="foo"' (assuming `optstring' contains "o:")
 * Long options (`getopt_long(3)'-only)appear in the following formats:
 *  - "--out":        Returns `longopts["out"].val'                      (assuming `longopts["out"].has_arg != required_argument')
 *  - "--out=foo":    Returns `longopts["out"].val', with `optarg="foo"' (assuming `longopts["out"].has_arg != no_argument')
 *  - "--out", "foo": Returns `longopts["out"].val', with `optarg="foo"' (assuming `longopts["out"].has_arg != no_argument')
 * When `getopt_long_only(3)' is used, long options may also be written with a single leading "-".
 *
 * This function interacts with the globals variables `optarg', `optind', `opterr' and `optopt'.
 * For  more information on  how these variables/are-used-by `getopt(3)'  (and friends), see the
 * documentation of the respective variable.
 *
 * The first character of `optstring' can be used to affect the behavior of this function:
 *  - '-': Each  non-option argument will be handled as though it was the argument of an option '\1'
 *         In other words: ["/bin/myapp", "-x", "foo", "bar"] (with `optstring="-x:"') would then be
 *         enumerated as  {[getopt:'x',optarg="foo"],  [getopt:1,optarg="bar"],  [getopt:-1]}.  Note
 *         that the special "--" argument still causes `getopt(3)' to return `-1' (with `optind' set
 *         to the 1 plus  the index of the  "--"-argument), even when this  option is used,  meaning
 *         that  when  using  this  option,  the  caller  must  handle  non-option  arguments  like:
 *         >> int opt;
 *         >> while ((opt = getopt(argc, argv, "-xy:z")) != -1) {
 *         >>     if (opt == 1)
 *         >>         handle_non_option_argument(optarg);
 *         >>     ...
 *         >> }
 *         >> while (optind < argc)
 *         >>     handle_non_option_argument(argv[optind++]);
 *         In this case, elements of `argv' are never permutated (and `argv' can be const).
 *  - '+': Stop parsing as soon as the first non-option argument is encountered. This is also the
 *         behavior when `optstring[0]' isn't a special character, and "$POSIXLY_CORRECT" is set,
 *         or `__posix_getopt(3)' was used.
 *         In this case, elements of `argv' are never permutated (and `argv' can be const).
 *  - ...: Default behavior (`optstring[0]'  isn't '-' or  '+'). In this  case, scanning of  `argv'
 *         does not stop at the first non-option argument, but only once the actual end is reached,
 *         or  an argument "--" is encountered. Once that is done, `getopt(3)' will return with the
 *         elements of `argv'  permutated such  that all  non-option arguments  appear (in  correct
 *         order) within `argv', starting at `argv[optind]'.
 *         e.g. Once option processing  is done, ["-afoo", "bar", "-c", "--", "-x"]  will
 *              result in `argv[optind...argc-1]' to be the array ["bar", "-x"] (assuming
 *              an `optstring' similar to "a:cx")
 *  - ':': Same as setting `opterr = 0' (may be combined with any of the other special flags by
 *         writing it _AFTER_ the other special flag; e.g. "+:xy:z")
 *
 * @param: argc: Number of arguments in `argv'
 * @param: argv: Argument vector from `main()' -- Shouldn't  actually be `const' here, since  this
 *               function may permute the  order of elements in  `argv' (to gather all  non-option
 *               arguments at the end), unless `optstring[0] == '+'', `__posix_getopt(3)' is used,
 *               or "$POSIXLY_CORRECT" is defined.
 * @param: optstring: [1..1] Options string (see above)
 * @param: longopts:  [0..1] Long options array (terminated by an all-NULL/0 element)
 * @param: longindex: [0..1] When non-NULL, set to the index of the matched long-option,
 *                           if  one was matched.  If none was (i.e.  a short option was
 *                           matched), the contents of this pointer are left  unchanged.
 * @return: 1 : The given `optstring' starts with '-', and a non-option argument `optarg' was encountered.
 * @return:'?': Error while processing options, or '?' appears in `optstring' (or as an `struct option::val')
 *              In the case of an error (and unless disabled by ':' or `opterr'), a message has already  been
 *              written to `stderr'.
 * @return: 0 : A long option was matched with `struct option::flag != NULL'.
 * @return: * : Either  a short option (return is that option's character-code), or a long-long (return is
 *              that option's `struct option::val', so-long as `struct option::flag == NULL') was matched.
 * @return: -1: Argument processing is done. Non-option arguments are in `argv[optind...argc-1]' */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,getopt,(int ___argc, char *const ___argv[], char const *__shortopts),(___argc,___argv,__shortopts))
#else /* ... */
#undef __getopt_defined
#endif /* !... */
#endif /* !__getopt_defined */
#endif /* __USE_POSIX2 */

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
#ifdef __CRT_HAVE_sync
/* >> sync(2)
 * Synchronize all disk  operations of  all mounted file  systems and  flush
 * unwritten buffers down to the hardware layer, ensuring that modifications
 * made become visible on the underlying, persistent media */
__CDECLARE_VOID(,__NOTHROW_RPC,sync,(void),())
#elif defined(__CRT_HAVE___sync)
/* >> sync(2)
 * Synchronize all disk  operations of  all mounted file  systems and  flush
 * unwritten buffers down to the hardware layer, ensuring that modifications
 * made become visible on the underlying, persistent media */
__CREDIRECT_VOID(,__NOTHROW_RPC,sync,(void),__sync,())
#elif defined(__CRT_HAVE___libc_sync)
/* >> sync(2)
 * Synchronize all disk  operations of  all mounted file  systems and  flush
 * unwritten buffers down to the hardware layer, ensuring that modifications
 * made become visible on the underlying, persistent media */
__CREDIRECT_VOID(,__NOTHROW_RPC,sync,(void),__libc_sync,())
#else /* ... */
#include <libc/local/unistd/sync.h>
/* >> sync(2)
 * Synchronize all disk  operations of  all mounted file  systems and  flush
 * unwritten buffers down to the hardware layer, ensuring that modifications
 * made become visible on the underlying, persistent media */
__NAMESPACE_LOCAL_USING_OR_IMPL(sync, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_RPC(__LIBCCALL sync)(void) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sync))(); })
#endif /* !... */
#ifdef __CRT_HAVE_setpgrp
/* >> setpgrp(3)
 * Move the calling process into its own process group.
 * Equivalent to `setpgid(0, 0)' */
__CDECLARE(,int,__NOTHROW_NCX,setpgrp,(void),())
#elif defined(__CRT_HAVE_setpgid) || defined(__CRT_HAVE___setpgid) || defined(__CRT_HAVE___libc_setpgid)
#include <libc/local/unistd/setpgrp.h>
/* >> setpgrp(3)
 * Move the calling process into its own process group.
 * Equivalent to `setpgid(0, 0)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(setpgrp, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL setpgrp)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setpgrp))(); })
#endif /* ... */
#ifdef __CRT_HAVE_setreuid
/* >> setreuid(2)
 * Set the real and effective UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(,int,__NOTHROW_NCX,setreuid,(__uid_t __ruid, __uid_t __euid),(__ruid,__euid))
#elif defined(__CRT_HAVE___setreuid)
/* >> setreuid(2)
 * Set the real and effective UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(,int,__NOTHROW_NCX,setreuid,(__uid_t __ruid, __uid_t __euid),__setreuid,(__ruid,__euid))
#elif defined(__CRT_HAVE___libc_setreuid)
/* >> setreuid(2)
 * Set the real and effective UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(,int,__NOTHROW_NCX,setreuid,(__uid_t __ruid, __uid_t __euid),__libc_setreuid,(__ruid,__euid))
#elif defined(__CRT_HAVE_setresuid)
#include <libc/local/unistd/setreuid.h>
/* >> setreuid(2)
 * Set the real and effective UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(setreuid, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL setreuid)(__uid_t __ruid, __uid_t __euid) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setreuid))(__ruid, __euid); })
#endif /* ... */
#ifdef __CRT_HAVE_setregid
/* >> setregid(2)
 * Set the real and effective GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(,int,__NOTHROW_NCX,setregid,(__gid_t __rgid, __gid_t __egid),(__rgid,__egid))
#elif defined(__CRT_HAVE___setregid)
/* >> setregid(2)
 * Set the real and effective GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(,int,__NOTHROW_NCX,setregid,(__gid_t __rgid, __gid_t __egid),__setregid,(__rgid,__egid))
#elif defined(__CRT_HAVE___libc_setregid)
/* >> setregid(2)
 * Set the real and effective GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(,int,__NOTHROW_NCX,setregid,(__gid_t __rgid, __gid_t __egid),__libc_setregid,(__rgid,__egid))
#elif defined(__CRT_HAVE_setresgid)
#include <libc/local/unistd/setregid.h>
/* >> setregid(2)
 * Set the real and effective GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(setregid, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL setregid)(__gid_t __rgid, __gid_t __egid) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setregid))(__rgid, __egid); })
#endif /* ... */
#ifdef __CRT_HAVE_gethostid
/* >> gethostid(3)
 * Get the machine's "host id" (the contents of a 4-byte file "/etc/hostid") */
__CDECLARE(__ATTR_WUNUSED,__LONGPTR_TYPE__,__NOTHROW_NCX,gethostid,(void),())
#else /* __CRT_HAVE_gethostid */
#include <paths.h>
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_readall) || ((defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)) && defined(__SEEK_CUR))) && defined(_PATH_HOSTID)
#include <libc/local/unistd/gethostid.h>
/* >> gethostid(3)
 * Get the machine's "host id" (the contents of a 4-byte file "/etc/hostid") */
__NAMESPACE_LOCAL_USING_OR_IMPL(gethostid, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGPTR_TYPE__ __NOTHROW_NCX(__LIBCCALL gethostid)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gethostid))(); })
#endif /* (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_readall || ((__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_lseek64 || __CRT_HAVE__lseeki64 || __CRT_HAVE_llseek || __CRT_HAVE___llseek || __CRT_HAVE_lseek || __CRT_HAVE__lseek || __CRT_HAVE___lseek || __CRT_HAVE___libc_lseek) && __SEEK_CUR)) && _PATH_HOSTID */
#endif /* !__CRT_HAVE_gethostid */
#if defined(__USE_MISC) || !defined(__USE_XOPEN2K)
#if defined(__ARCH_PAGESIZE) && defined(__CRT_HAVE_getpagesize)
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW,getpagesize,(void),{ return __ARCH_PAGESIZE; })
#elif defined(__ARCH_PAGESIZE) && defined(__CRT_HAVE___getpagesize)
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW,getpagesize,(void),__getpagesize,{ return __ARCH_PAGESIZE; })
#elif defined(__CRT_HAVE_getpagesize)
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW,getpagesize,(void),())
#elif defined(__CRT_HAVE___getpagesize)
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW,getpagesize,(void),__getpagesize,())
#elif defined(__ARCH_PAGESIZE)
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __STDC_INT_AS_SIZE_T __NOTHROW(__LIBCCALL getpagesize)(void) { return __ARCH_PAGESIZE; }
#endif /* ... */
#ifdef __ARCH_PAGESIZE
/* If known to be a compile-time  constant, use macros to make  sure
 * that our `getpagesize()' function is _as_ _fast_ as possible, and
 * also allows for _as_ _many_ compiler optimization as possible! */
#define getpagesize() __ARCH_PAGESIZE
#endif /* __ARCH_PAGESIZE */
#ifdef __CRT_HAVE_getdtablesize
/* >> getdtablesize(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW,getdtablesize,(void),())
#elif defined(__CRT_HAVE___getdtablesize)
/* >> getdtablesize(3) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__STDC_INT_AS_SIZE_T,__NOTHROW,getdtablesize,(void),__getdtablesize,())
#else /* ... */
#include <libc/local/unistd/getdtablesize.h>
/* >> getdtablesize(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(getdtablesize, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __STDC_INT_AS_SIZE_T __NOTHROW(__LIBCCALL getdtablesize)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getdtablesize))(); })
#endif /* !... */
#endif /* __USE_MISC || !__USE_XOPEN2K */
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

#ifdef __USE_XOPEN2K
#ifdef __CRT_HAVE_seteuid
/* >> seteuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `euid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
__CDECLARE(,int,__NOTHROW_NCX,seteuid,(__uid_t __euid),(__euid))
#elif defined(__CRT_HAVE_setreuid) || defined(__CRT_HAVE___setreuid) || defined(__CRT_HAVE___libc_setreuid) || defined(__CRT_HAVE_setresuid)
#include <libc/local/unistd/seteuid.h>
/* >> seteuid(2)
 * Set the effective user ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `euid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
__NAMESPACE_LOCAL_USING_OR_IMPL(seteuid, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL seteuid)(__uid_t __euid) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(seteuid))(__euid); })
#endif /* ... */
#ifdef __CRT_HAVE_setegid
/* >> setegid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `egid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
__CDECLARE(,int,__NOTHROW_NCX,setegid,(__gid_t __egid),(__egid))
#elif defined(__CRT_HAVE_setregid) || defined(__CRT_HAVE___setregid) || defined(__CRT_HAVE___libc_setregid) || defined(__CRT_HAVE_setresgid)
#include <libc/local/unistd/setegid.h>
/* >> setegid(2)
 * Set the effective group ID of the calling process
 * @return: 0 : Success
 * @return: -1: [errno=EINVAL] : The given `egid' is invalid
 * @return: -1: [errno=EPERM]  : The current user is not privileged */
__NAMESPACE_LOCAL_USING_OR_IMPL(setegid, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL setegid)(__gid_t __egid) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setegid))(__egid); })
#endif /* ... */
#endif /* __USE_XOPEN2K */
#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_UNIX98))
#ifdef __CRT_HAVE_ttyslot
/* >> ttyslot(3)
 * Returns the (1-based) index into  ttys returned by `getttyent(3)'  of
 * the terminal currently associated with the caller (~ala `ttyname(3)')
 * On  error, or if caller's terminal isn't listed by `getttyent(3)', we
 * instead return `0' */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,ttyslot,(void),())
#else /* __CRT_HAVE_ttyslot */
#include <paths.h>
#include <asm/os/fcntl.h>
#include <bits/os/dirent.h>
#include <asm/os/oflags.h>
#include <bits/os/stat.h>
#if (defined(__CRT_HAVE_ttyname) || defined(__CRT_HAVE___ttyname) || defined(__CRT_HAVE_ttyname_r) || defined(__CRT_HAVE_frealpath4) || ((defined(__CRT_HAVE_opendir) || defined(__CRT_HAVE___libc_opendir) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_opendirat) || defined(__CRT_HAVE_fopendirat) || (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))) || (defined(__CRT_HAVE_fdopendir) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))) || defined(__USE_DOS_DIRENT)) && ((defined(__CRT_HAVE_readdirk) && defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE_readdirk64) && defined(__CRT_KOS)) || (defined(__CRT_HAVE_readdir) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE___libc_readdir) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE_readdir64) && !defined(__CRT_KOS)) || (defined(__USE_DOS_DIRENT) && defined(_DIRENT_MATCHES_DIRENT64))) && ((defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__fstat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__fstat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE_fstat) && defined(__STAT32_MATCHES_STAT64)) || defined(__CRT_HAVE_fstat64)) && ((defined(__CRT_HAVE_klstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_klstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE_lstat) && defined(__STAT32_MATCHES_STAT64)) || defined(__CRT_HAVE_lstat64)) && defined(_PATH_DEV))) && defined(__CRT_HAVE_setttyent) && defined(__CRT_HAVE_getttyent)
#include <libc/local/unistd/ttyslot.h>
/* >> ttyslot(3)
 * Returns the (1-based) index into  ttys returned by `getttyent(3)'  of
 * the terminal currently associated with the caller (~ala `ttyname(3)')
 * On  error, or if caller's terminal isn't listed by `getttyent(3)', we
 * instead return `0' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ttyslot, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL ttyslot)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ttyslot))(); })
#endif /* (__CRT_HAVE_ttyname || __CRT_HAVE___ttyname || __CRT_HAVE_ttyname_r || __CRT_HAVE_frealpath4 || ((__CRT_HAVE_opendir || __CRT_HAVE___libc_opendir || (__AT_FDCWD && (__CRT_HAVE_opendirat || __CRT_HAVE_fopendirat || (__CRT_HAVE_fdopendir && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)))) || (__CRT_HAVE_fdopendir && (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)))) || __USE_DOS_DIRENT) && ((__CRT_HAVE_readdirk && __CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE_readdirk64 && __CRT_KOS) || (__CRT_HAVE_readdir && !__CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE___libc_readdir && !__CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE_readdir64 && !__CRT_KOS) || (__USE_DOS_DIRENT && _DIRENT_MATCHES_DIRENT64)) && ((__CRT_HAVE_kfstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__fstat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__fstat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__fstati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE__fstat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE_fstat && __STAT32_MATCHES_STAT64) || __CRT_HAVE_fstat64) && ((__CRT_HAVE_klstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_klstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__stat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE__stat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64) || (__CRT_HAVE_lstat && __STAT32_MATCHES_STAT64) || __CRT_HAVE_lstat64) && _PATH_DEV)) && __CRT_HAVE_setttyent && __CRT_HAVE_getttyent */
#endif /* !__CRT_HAVE_ttyslot */
#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_UNIX98) */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
#ifdef __CRT_HAVE_symlink
/* >> symlink(3)
 * Create  a new  symbolic link  loaded with  `link_text' as link
 * text, at the filesystem location referred to by `target_path'.
 * Same as `symlinkat(link_text, AT_FDCWD, target_path)' */
__CDECLARE(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_RPC,symlink,(char const *__link_text, char const *__target_path),(__link_text,__target_path))
#elif defined(__CRT_HAVE___symlink)
/* >> symlink(3)
 * Create  a new  symbolic link  loaded with  `link_text' as link
 * text, at the filesystem location referred to by `target_path'.
 * Same as `symlinkat(link_text, AT_FDCWD, target_path)' */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_RPC,symlink,(char const *__link_text, char const *__target_path),__symlink,(__link_text,__target_path))
#elif defined(__CRT_HAVE___libc_symlink)
/* >> symlink(3)
 * Create  a new  symbolic link  loaded with  `link_text' as link
 * text, at the filesystem location referred to by `target_path'.
 * Same as `symlinkat(link_text, AT_FDCWD, target_path)' */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_RPC,symlink,(char const *__link_text, char const *__target_path),__libc_symlink,(__link_text,__target_path))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && (defined(__CRT_HAVE_symlinkat) || defined(__CRT_HAVE_fsymlinkat))
#include <libc/local/unistd/symlink.h>
/* >> symlink(3)
 * Create  a new  symbolic link  loaded with  `link_text' as link
 * text, at the filesystem location referred to by `target_path'.
 * Same as `symlinkat(link_text, AT_FDCWD, target_path)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(symlink, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_RPC(__LIBCCALL symlink)(char const *__link_text, char const *__target_path) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(symlink))(__link_text, __target_path); })
#endif /* __AT_FDCWD && (__CRT_HAVE_symlinkat || __CRT_HAVE_fsymlinkat) */
#endif /* !... */
#ifdef __CRT_HAVE_readlink
/* >> readlink(3)
 * Read the text of a symbolic link under `path' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, path, buf, buflen)'
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__CDECLARE(__ATTR_IN(1) __ATTR_OUTS(2, 3),ssize_t,__NOTHROW_RPC,readlink,(char const *__path, char *__buf, size_t __buflen),(__path,__buf,__buflen))
#elif defined(__CRT_HAVE___readlink)
/* >> readlink(3)
 * Read the text of a symbolic link under `path' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, path, buf, buflen)'
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUTS(2, 3),ssize_t,__NOTHROW_RPC,readlink,(char const *__path, char *__buf, size_t __buflen),__readlink,(__path,__buf,__buflen))
#elif defined(__CRT_HAVE___libc_readlink)
/* >> readlink(3)
 * Read the text of a symbolic link under `path' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, path, buf, buflen)'
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUTS(2, 3),ssize_t,__NOTHROW_RPC,readlink,(char const *__path, char *__buf, size_t __buflen),__libc_readlink,(__path,__buf,__buflen))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && (defined(__CRT_HAVE_readlinkat) || defined(__CRT_HAVE_freadlinkat))
#include <libc/local/unistd/readlink.h>
/* >> readlink(3)
 * Read the text of a symbolic link under `path' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, path, buf, buflen)'
 * WARNING: This  function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(readlink, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUTS(2, 3) ssize_t __NOTHROW_RPC(__LIBCCALL readlink)(char const *__path, char *__buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(readlink))(__path, __buf, __buflen); })
#endif /* __AT_FDCWD && (__CRT_HAVE_readlinkat || __CRT_HAVE_freadlinkat) */
#endif /* !... */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

#if defined(__USE_REENTRANT) || defined(__USE_POSIX199506)
#ifdef __CRT_HAVE_getlogin_r
/* >> getlogin_r(3)
 * Reentrant version of `getlogin()'. May truncate the name if it's longer than `name_len'
 * s.a. `getlogin()' and `cuserid()' */
__CDECLARE(__ATTR_OUTS(1, 2),int,__NOTHROW_RPC,getlogin_r,(char *__name, size_t __name_len),(__name,__name_len))
#else /* __CRT_HAVE_getlogin_r */
#include <libc/template/environ.h>
#if defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ) || (defined(__CRT_HAVE_getpwuid_r) && (defined(__CRT_HAVE_geteuid) || defined(__CRT_HAVE___geteuid) || defined(__CRT_HAVE___libc_geteuid) || defined(__CRT_HAVE_getresuid)))
#include <libc/local/unistd/getlogin_r.h>
/* >> getlogin_r(3)
 * Reentrant version of `getlogin()'. May truncate the name if it's longer than `name_len'
 * s.a. `getlogin()' and `cuserid()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(getlogin_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(1, 2) int __NOTHROW_RPC(__LIBCCALL getlogin_r)(char *__name, size_t __name_len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getlogin_r))(__name, __name_len); })
#endif /* __CRT_HAVE_getenv || __LOCAL_environ || (__CRT_HAVE_getpwuid_r && (__CRT_HAVE_geteuid || __CRT_HAVE___geteuid || __CRT_HAVE___libc_geteuid || __CRT_HAVE_getresuid)) */
#endif /* !__CRT_HAVE_getlogin_r */
#endif /* __USE_REENTRANT || __USE_POSIX199506 */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
#ifdef __CRT_HAVE_gethostname
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
__CDECLARE(__ATTR_OUTS(1, 2),int,__NOTHROW_NCX,gethostname,(char *__name, size_t __buflen),(__name,__buflen))
#elif defined(__CRT_HAVE___gethostname)
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
__CREDIRECT(__ATTR_OUTS(1, 2),int,__NOTHROW_NCX,gethostname,(char *__name, size_t __buflen),__gethostname,(__name,__buflen))
#else /* ... */
#include <bits/os/utsname.h>
#if (defined(__CRT_HAVE_uname) || defined(__CRT_HAVE___uname) || defined(__CRT_HAVE___libc_uname)) && defined(__OFFSET_UTSNAME_NODENAME) && defined(_UTSNAME_NODENAME_LENGTH) && _UTSNAME_NODENAME_LENGTH
#include <libc/local/unistd/gethostname.h>
/* >> gethostname(3)
 * Return the name assigned to the hosting machine, as set by `sethostname(2)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(gethostname, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(1, 2) int __NOTHROW_NCX(__LIBCCALL gethostname)(char *__name, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gethostname))(__name, __buflen); })
#endif /* (__CRT_HAVE_uname || __CRT_HAVE___uname || __CRT_HAVE___libc_uname) && __OFFSET_UTSNAME_NODENAME && _UTSNAME_NODENAME_LENGTH && _UTSNAME_NODENAME_LENGTH */
#endif /* !... */
#endif /* __USE_UNIX98 || __USE_XOPEN2K */

#ifdef __USE_MISC
/* >> setlogin(3) */
__CDECLARE_OPT(__ATTR_IN(1),int,__NOTHROW_NCX,setlogin,(char const *__name),(__name))
#ifdef __CRT_HAVE_sethostname
/* >> sethostname(2)
 * Set the name of the hosting machine */
__CDECLARE(__ATTR_INS(1, 2),int,__NOTHROW_NCX,sethostname,(char const *__name, size_t __len),(__name,__len))
#elif defined(__CRT_HAVE___sethostname)
/* >> sethostname(2)
 * Set the name of the hosting machine */
__CREDIRECT(__ATTR_INS(1, 2),int,__NOTHROW_NCX,sethostname,(char const *__name, size_t __len),__sethostname,(__name,__len))
#elif defined(__CRT_HAVE___libc_sethostname)
/* >> sethostname(2)
 * Set the name of the hosting machine */
__CREDIRECT(__ATTR_INS(1, 2),int,__NOTHROW_NCX,sethostname,(char const *__name, size_t __len),__libc_sethostname,(__name,__len))
#endif /* ... */
#ifdef __CRT_HAVE_sethostid
/* >> sethostid(3)
 * Set the machine's "host id" (the contents of a 4-byte file "/etc/hostid") */
__CDECLARE(,int,__NOTHROW_NCX,sethostid,(__LONGPTR_TYPE__ __id),(__id))
#else /* __CRT_HAVE_sethostid */
#include <asm/os/oflags.h>
#include <paths.h>
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_writeall) || (defined(__CRT_HAVE_write_printer) && defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_INT__ == __SIZEOF_POINTER__) || defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && defined(__O_WRONLY) && defined(__O_CREAT) && defined(__O_TRUNC) && defined(_PATH_HOSTID)
#include <libc/local/unistd/sethostid.h>
/* >> sethostid(3)
 * Set the machine's "host id" (the contents of a 4-byte file "/etc/hostid") */
__NAMESPACE_LOCAL_USING_OR_IMPL(sethostid, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL sethostid)(__LONGPTR_TYPE__ __id) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sethostid))(__id); })
#endif /* (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_writeall || (__CRT_HAVE_write_printer && __LIBCCALL_IS_FORMATPRINTER_CC && __SIZEOF_INT__ == __SIZEOF_POINTER__) || __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && __O_WRONLY && __O_CREAT && __O_TRUNC && _PATH_HOSTID */
#endif /* !__CRT_HAVE_sethostid */
#ifdef __CRT_HAVE_getdomainname
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
__CDECLARE(__ATTR_OUTS(1, 2),int,__NOTHROW_NCX,getdomainname,(char *__name, size_t __buflen),(__name,__buflen))
#else /* __CRT_HAVE_getdomainname */
#include <bits/os/utsname.h>
#if (defined(__CRT_HAVE_uname) || defined(__CRT_HAVE___uname) || defined(__CRT_HAVE___libc_uname)) && defined(__OFFSET_UTSNAME_DOMAINNAME) && defined(_UTSNAME_DOMAIN_LENGTH) && _UTSNAME_DOMAIN_LENGTH
#include <libc/local/unistd/getdomainname.h>
/* >> getdomainname(3)
 * Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(getdomainname, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(1, 2) int __NOTHROW_NCX(__LIBCCALL getdomainname)(char *__name, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getdomainname))(__name, __buflen); })
#endif /* (__CRT_HAVE_uname || __CRT_HAVE___uname || __CRT_HAVE___libc_uname) && __OFFSET_UTSNAME_DOMAINNAME && _UTSNAME_DOMAIN_LENGTH && _UTSNAME_DOMAIN_LENGTH */
#endif /* !__CRT_HAVE_getdomainname */
#ifdef __CRT_HAVE_setdomainname
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
__CDECLARE(__ATTR_INS(1, 2),int,__NOTHROW_NCX,setdomainname,(char const *__name, size_t __len),(__name,__len))
#elif defined(__CRT_HAVE___setdomainname)
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
__CREDIRECT(__ATTR_INS(1, 2),int,__NOTHROW_NCX,setdomainname,(char const *__name, size_t __len),__setdomainname,(__name,__len))
#elif defined(__CRT_HAVE___libc_setdomainname)
/* >> setdomainname(2)
 * Set the name of the hosting machine's domain */
__CREDIRECT(__ATTR_INS(1, 2),int,__NOTHROW_NCX,setdomainname,(char const *__name, size_t __len),__libc_setdomainname,(__name,__len))
#endif /* ... */
#ifdef __CRT_HAVE_vhangup
/* >> vhangup(3) */
__CDECLARE(,int,__NOTHROW_NCX,vhangup,(void),())
#elif defined(__CRT_HAVE___vhangup)
/* >> vhangup(3) */
__CREDIRECT(,int,__NOTHROW_NCX,vhangup,(void),__vhangup,())
#elif defined(__CRT_HAVE___libc_vhangup)
/* >> vhangup(3) */
__CREDIRECT(,int,__NOTHROW_NCX,vhangup,(void),__libc_vhangup,())
#endif /* ... */
/* >> profil(3) */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,profil,(__UINT16_TYPE__ *__sample_buffer, size_t __size, size_t __offset, unsigned int __scale),(__sample_buffer,__size,__offset,__scale))
/* >> getusershell(3) */
__CDECLARE_OPT(__ATTR_WUNUSED,char *,__NOTHROW_RPC,getusershell,(void),())
/* >> endusershell(3) */
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,endusershell,(void),())
/* >> setusershell(3) */
__CDECLARE_VOID_OPT(,__NOTHROW_RPC,setusershell,(void),())
#ifndef __daemon_defined
#define __daemon_defined
#ifdef __CRT_HAVE_daemon
/* >> daemon(3), daemonfd(3) */
__CDECLARE(,int,__NOTHROW_RPC,daemon,(int __nochdir, int __noclose),(__nochdir,__noclose))
#else /* __CRT_HAVE_daemon */
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#if (defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && (defined(__CRT_HAVE_setsid) || defined(__CRT_HAVE___setsid) || defined(__CRT_HAVE___libc_setsid)) && (defined(__CRT_HAVE_chdir) || defined(__CRT_HAVE__chdir) || defined(__CRT_HAVE___chdir) || defined(__CRT_HAVE___libc_chdir) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_fchdirat))) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_dup2) || defined(__CRT_HAVE__dup2) || defined(__CRT_HAVE___dup2) || defined(__CRT_HAVE___libc_dup2))
#include <libc/local/unistd/daemon.h>
/* >> daemon(3), daemonfd(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(daemon, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL daemon)(int __nochdir, int __noclose) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(daemon))(__nochdir, __noclose); })
#else /* (__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && (__CRT_HAVE_setsid || __CRT_HAVE___setsid || __CRT_HAVE___libc_setsid) && (__CRT_HAVE_chdir || __CRT_HAVE__chdir || __CRT_HAVE___chdir || __CRT_HAVE___libc_chdir || (__AT_FDCWD && __CRT_HAVE_fchdirat)) && (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_dup2 || __CRT_HAVE__dup2 || __CRT_HAVE___dup2 || __CRT_HAVE___libc_dup2) */
#undef __daemon_defined
#endif /* (!__CRT_HAVE_fork && !__CRT_HAVE___fork && !__CRT_HAVE___libc_fork) || (!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || (!__CRT_HAVE_setsid && !__CRT_HAVE___setsid && !__CRT_HAVE___libc_setsid) || (!__CRT_HAVE_chdir && !__CRT_HAVE__chdir && !__CRT_HAVE___chdir && !__CRT_HAVE___libc_chdir && (!__AT_FDCWD || !__CRT_HAVE_fchdirat)) || (!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_dup2 && !__CRT_HAVE__dup2 && !__CRT_HAVE___dup2 && !__CRT_HAVE___libc_dup2) */
#endif /* !__CRT_HAVE_daemon */
#endif /* !__daemon_defined */
/* >> revoke(3) */
__CDECLARE_OPT(__ATTR_IN(1),int,__NOTHROW_RPC,revoke,(char const *__file),(__file))
#ifndef __acct_defined
#define __acct_defined
#ifdef __CRT_HAVE_acct
/* Switch process accounting on and off */
__CDECLARE(__ATTR_IN_OPT(1),int,__NOTHROW_RPC,acct,(const char *__filename),(__filename))
#elif defined(__CRT_HAVE___acct)
/* Switch process accounting on and off */
__CREDIRECT(__ATTR_IN_OPT(1),int,__NOTHROW_RPC,acct,(const char *__filename),__acct,(__filename))
#elif defined(__CRT_HAVE___libc_acct)
/* Switch process accounting on and off */
__CREDIRECT(__ATTR_IN_OPT(1),int,__NOTHROW_RPC,acct,(const char *__filename),__libc_acct,(__filename))
#else /* ... */
#undef __acct_defined
#endif /* !... */
#endif /* !__acct_defined */
#ifdef __CRT_HAVE_syscall
/* >> syscall(2), syscall64(2) */
__LIBC __LONGPTR_TYPE__ __NOTHROW_RPC(__VLIBCCALL syscall)(__LONGPTR_TYPE__ __sysno, ...) __CASMNAME_SAME("syscall");
#endif /* __CRT_HAVE_syscall */

#ifdef __USE_KOS
#ifdef __CRT_HAVE_syscall
/* >> syscall(2), syscall64(2) */
__CVREDIRECT(,__LONG64_TYPE__,__NOTHROW_RPC,syscall64,(__syscall_ulong_t __sysno),syscall,(__sysno),__sysno,6,(__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t))
#elif defined(__CRT_HAVE_syscall64)
/* >> syscall(2), syscall64(2) */
__LIBC __LONG64_TYPE__ __NOTHROW_RPC(__VLIBCCALL syscall64)(__syscall_ulong_t __sysno, ...) __CASMNAME_SAME("syscall64");
#elif defined(__CRT_HAVE___syscall)
/* >> syscall(2), syscall64(2) */
__CVREDIRECT(,__LONG64_TYPE__,__NOTHROW_RPC,syscall64,(__syscall_ulong_t __sysno),__syscall,(__sysno),__sysno,6,(__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t,__syscall_ulong_t))
#endif /* ... */
#endif /* __USE_KOS */

#ifndef __getentropy_defined
#define __getentropy_defined
#ifdef __CRT_HAVE_getentropy
/* >> getentropy(3)
 * Similar   to   `getrandom(buf, num_bytes, GRND_RANDOM)',  however
 * the  case  where  the  calling  thread  is  interrupted,  causing
 * less  than `num_bytes' of  data to be read  is handled by reading
 * more  random  data  until  all  of  `num_bytes'  have  been read.
 * Note that  portable applications  should  be aware  that  certain
 * implementations of this function disallow calls where `num_bytes'
 * is larger than `256'
 * Also note that any error other than `EFAULT'
 * and `ENOSYS'  may be  translated into  `EIO'
 * @return:  0: Success
 * @return: -1: Error (see `errno') */
__CDECLARE(__ATTR_WUNUSED __ATTR_OUTS(1, 2),int,__NOTHROW_NCX,getentropy,(void *__buf, size_t __num_bytes),(__buf,__num_bytes))
#else /* __CRT_HAVE_getentropy */
#include <asm/os/random.h>
#if defined(__GRND_RANDOM) && defined(__CRT_HAVE_getrandom)
#include <libc/local/sys.random/getentropy.h>
/* >> getentropy(3)
 * Similar   to   `getrandom(buf, num_bytes, GRND_RANDOM)',  however
 * the  case  where  the  calling  thread  is  interrupted,  causing
 * less  than `num_bytes' of  data to be read  is handled by reading
 * more  random  data  until  all  of  `num_bytes'  have  been read.
 * Note that  portable applications  should  be aware  that  certain
 * implementations of this function disallow calls where `num_bytes'
 * is larger than `256'
 * Also note that any error other than `EFAULT'
 * and `ENOSYS'  may be  translated into  `EIO'
 * @return:  0: Success
 * @return: -1: Error (see `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(getentropy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUTS(1, 2) int __NOTHROW_NCX(__LIBCCALL getentropy)(void *__buf, size_t __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getentropy))(__buf, __num_bytes); })
#else /* __GRND_RANDOM && __CRT_HAVE_getrandom */
#undef __getentropy_defined
#endif /* !__GRND_RANDOM || !__CRT_HAVE_getrandom */
#endif /* !__CRT_HAVE_getentropy */
#endif /* !__getentropy_defined */
#endif /* __USE_MISC */

#if (defined(__USE_MISC) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K)))
#ifdef __CRT_HAVE_chroot
/* >> chroot(2)
 * Change  the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `path' */
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,chroot,(char const *__restrict __path),(__path))
#elif defined(__CRT_HAVE___chroot)
/* >> chroot(2)
 * Change  the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `path' */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,chroot,(char const *__restrict __path),__chroot,(__path))
#elif defined(__CRT_HAVE___libc_chroot)
/* >> chroot(2)
 * Change  the root directory of the calling `CLONE_FS' group of threads
 * (usually the process) to a path that was previously address by `path' */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,chroot,(char const *__restrict __path),__libc_chroot,(__path))
#endif /* ... */
#ifndef __getpass_defined
#define __getpass_defined
#ifdef __CRT_HAVE_getpass
/* >> getpass(3), getpassphrase(3) */
__CDECLARE(__ATTR_WUNUSED,char *,__NOTHROW_RPC,getpass,(char const *__restrict __prompt),(__prompt))
#elif defined(__CRT_HAVE_getpassphrase)
/* >> getpass(3), getpassphrase(3) */
__CREDIRECT(__ATTR_WUNUSED,char *,__NOTHROW_RPC,getpass,(char const *__restrict __prompt),getpassphrase,(__prompt))
#elif defined(__CRT_HAVE_getpass_r) || defined(__CRT_HAVE_getpassfd) || defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read) || defined(__CRT_HAVE_readpassphrase)
#include <libc/local/unistd/getpass.h>
/* >> getpass(3), getpassphrase(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(getpass, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED char *__NOTHROW_RPC(__LIBCCALL getpass)(char const *__restrict __prompt) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getpass))(__prompt); })
#else /* ... */
#undef __getpass_defined
#endif /* !... */
#endif /* !__getpass_defined */
#endif /* __USE_MISC || (__USE_XOPEN && !__USE_XOPEN2K) */

#if defined(__USE_POSIX199309) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
#if defined(__CRT_HAVE_ftruncate) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CDECLARE(,int,__NOTHROW_NCX,ftruncate,(__fd_t __fd, __PIO_OFFSET __length),(__fd,__length))
#elif defined(__CRT_HAVE___ftruncate) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,ftruncate,(__fd_t __fd, __PIO_OFFSET __length),__ftruncate,(__fd,__length))
#elif defined(__CRT_HAVE___libc_ftruncate) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,ftruncate,(__fd_t __fd, __PIO_OFFSET __length),__libc_ftruncate,(__fd,__length))
#elif defined(__CRT_HAVE__chsize) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,ftruncate,(__fd_t __fd, __PIO_OFFSET __length),_chsize,(__fd,__length))
#elif defined(__CRT_HAVE_chsize) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,ftruncate,(__fd_t __fd, __PIO_OFFSET __length),chsize,(__fd,__length))
#elif defined(__CRT_HAVE_ftruncate64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,ftruncate,(__fd_t __fd, __PIO_OFFSET __length),ftruncate64,(__fd,__length))
#elif defined(__CRT_HAVE__chsize_s) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,ftruncate,(__fd_t __fd, __PIO_OFFSET __length),_chsize_s,(__fd,__length))
#elif defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize)
#include <libc/local/unistd/ftruncate.h>
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ftruncate, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL ftruncate)(__fd_t __fd, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftruncate))(__fd, __length); })
#endif /* ... */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_ftruncate) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,ftruncate64,(__fd_t __fd, __PIO_OFFSET64 __length),ftruncate,(__fd,__length))
#elif defined(__CRT_HAVE___ftruncate) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,ftruncate64,(__fd_t __fd, __PIO_OFFSET64 __length),__ftruncate,(__fd,__length))
#elif defined(__CRT_HAVE___libc_ftruncate) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,ftruncate64,(__fd_t __fd, __PIO_OFFSET64 __length),__libc_ftruncate,(__fd,__length))
#elif defined(__CRT_HAVE__chsize) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,ftruncate64,(__fd_t __fd, __PIO_OFFSET64 __length),_chsize,(__fd,__length))
#elif defined(__CRT_HAVE_chsize) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,ftruncate64,(__fd_t __fd, __PIO_OFFSET64 __length),chsize,(__fd,__length))
#elif defined(__CRT_HAVE_ftruncate64)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CDECLARE(,int,__NOTHROW_NCX,ftruncate64,(__fd_t __fd, __PIO_OFFSET64 __length),(__fd,__length))
#elif defined(__CRT_HAVE__chsize_s)
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__CREDIRECT(,int,__NOTHROW_NCX,ftruncate64,(__fd_t __fd, __PIO_OFFSET64 __length),_chsize_s,(__fd,__length))
#elif defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize)
#include <libc/local/unistd/ftruncate64.h>
/* >> ftruncate(2), ftruncate64(2)
 * Truncate the given file `fd' to a length of `length' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ftruncate64, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL ftruncate64)(__fd_t __fd, __PIO_OFFSET64 __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftruncate64))(__fd, __length); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_POSIX199309 || __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

#if (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K)) || defined(__USE_MISC)
#ifdef __CRT_HAVE_brk
/* >> brk(2), sbrk(2)
 * Change the  program  break,  allowing  for a  rudimentary  implementation  of  a  heap.
 * It is recommended to use the much more advanced functions found in <sys/mman.h> instead */
__CDECLARE(,int,__NOTHROW_NCX,brk,(void *__addr),(__addr))
#elif defined(__CRT_HAVE___brk)
/* >> brk(2), sbrk(2)
 * Change the  program  break,  allowing  for a  rudimentary  implementation  of  a  heap.
 * It is recommended to use the much more advanced functions found in <sys/mman.h> instead */
__CREDIRECT(,int,__NOTHROW_NCX,brk,(void *__addr),__brk,(__addr))
#endif /* ... */
#ifdef __CRT_HAVE_sbrk
/* >> brk(2), sbrk(2)
 * Change the  program  break,  allowing  for a  rudimentary  implementation  of  a  heap.
 * It is recommended to use the much more advanced functions found in <sys/mman.h> instead */
__CDECLARE(,void *,__NOTHROW_NCX,sbrk,(intptr_t __delta),(__delta))
#elif defined(__CRT_HAVE___sbrk)
/* >> brk(2), sbrk(2)
 * Change the  program  break,  allowing  for a  rudimentary  implementation  of  a  heap.
 * It is recommended to use the much more advanced functions found in <sys/mman.h> instead */
__CREDIRECT(,void *,__NOTHROW_NCX,sbrk,(intptr_t __delta),__sbrk,(__delta))
#endif /* ... */
#endif /* (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K) || __USE_MISC */

#if defined(__USE_POSIX199309) || defined(__USE_UNIX98)
#ifdef __CRT_HAVE_fdatasync
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps,  and its size),  meaning that changes  are written to disk */
__CDECLARE(,int,__NOTHROW_RPC,fdatasync,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE___fdatasync)
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps,  and its size),  meaning that changes  are written to disk */
__CREDIRECT(,int,__NOTHROW_RPC,fdatasync,(__fd_t __fd),__fdatasync,(__fd))
#elif defined(__CRT_HAVE___libc_fdatasync)
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps,  and its size),  meaning that changes  are written to disk */
__CREDIRECT(,int,__NOTHROW_RPC,fdatasync,(__fd_t __fd),__libc_fdatasync,(__fd))
#elif defined(__CRT_HAVE_fsync)
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps,  and its size),  meaning that changes  are written to disk */
__CREDIRECT(,int,__NOTHROW_RPC,fdatasync,(__fd_t __fd),fsync,(__fd))
#elif defined(__CRT_HAVE___fsync)
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps,  and its size),  meaning that changes  are written to disk */
__CREDIRECT(,int,__NOTHROW_RPC,fdatasync,(__fd_t __fd),__fsync,(__fd))
#elif defined(__CRT_HAVE__commit)
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps,  and its size),  meaning that changes  are written to disk */
__CREDIRECT(,int,__NOTHROW_RPC,fdatasync,(__fd_t __fd),_commit,(__fd))
#else /* ... */
#include <libc/local/unistd/fdatasync.h>
/* >> fdatasync(2)
 * Synchronize only the data of a file (not its descriptor which contains
 * timestamps,  and its size),  meaning that changes  are written to disk */
__NAMESPACE_LOCAL_USING_OR_IMPL(fdatasync, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL fdatasync)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fdatasync))(__fd); })
#endif /* !... */
#endif /* __USE_POSIX199309 || __USE_UNIX98 */

#ifdef __USE_XOPEN
#if !defined(__crypt_defined) && defined(__CRT_HAVE_crypt)
#define __crypt_defined
/* >> crypt(3), crypt_r(3) */
__CDECLARE(__ATTR_IN(1) __ATTR_IN(2),char *,__NOTHROW_NCX,crypt,(char const *__key, char const *__salt),(__key,__salt))
#endif /* !__crypt_defined && __CRT_HAVE_crypt */
#if !defined(__encrypt_defined) && defined(__CRT_HAVE_encrypt)
#define __encrypt_defined
/* >> encrypt(3), encrypt_r(3) */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,encrypt,(char *__glibc_block, __STDC_INT_AS_UINT_T __edflag),(__glibc_block,__edflag))
#endif /* !__encrypt_defined && __CRT_HAVE_encrypt */
#ifndef __swab_defined
#define __swab_defined
#ifdef __CRT_HAVE_swab
/* >> swab(3)
 * Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
__CDECLARE_VOID(__ATTR_INS(1, 3) __ATTR_OUTS(2, 3),__NOTHROW_NCX,swab,(void const *__restrict __from, void *__restrict __to, __STDC_INT_AS_SSIZE_T __n_bytes),(__from,__to,__n_bytes))
#elif defined(__CRT_HAVE__swab)
/* >> swab(3)
 * Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
__CREDIRECT_VOID(__ATTR_INS(1, 3) __ATTR_OUTS(2, 3),__NOTHROW_NCX,swab,(void const *__restrict __from, void *__restrict __to, __STDC_INT_AS_SSIZE_T __n_bytes),_swab,(__from,__to,__n_bytes))
#else /* ... */
#include <libc/local/unistd/swab.h>
/* >> swab(3)
 * Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
__NAMESPACE_LOCAL_USING_OR_IMPL(swab, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(1, 3) __ATTR_OUTS(2, 3) void __NOTHROW_NCX(__LIBCCALL swab)(void const *__restrict __from, void *__restrict __to, __STDC_INT_AS_SSIZE_T __n_bytes) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swab))(__from, __to, __n_bytes); })
#endif /* !... */
#endif /* !__swab_defined */
#endif /* __USE_XOPEN */


#if defined(_EVERY_SOURCE) || defined(__USE_SOLARIS) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
#ifndef __ctermid_defined
#define __ctermid_defined
#ifdef __CRT_HAVE_ctermid
/* >> ctermid(3)
 * Writes the string "/dev/tty" to `s', or returns a pointer to
 * a writable  data location  that contains  that same  string. */
__CDECLARE(__ATTR_RETNONNULL,char *,__NOTHROW_NCX,ctermid,(char *__s),(__s))
#else /* __CRT_HAVE_ctermid */
#include <libc/local/unistd/ctermid.h>
/* >> ctermid(3)
 * Writes the string "/dev/tty" to `s', or returns a pointer to
 * a writable  data location  that contains  that same  string. */
__NAMESPACE_LOCAL_USING_OR_IMPL(ctermid, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL char *__NOTHROW_NCX(__LIBCCALL ctermid)(char *__s) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ctermid))(__s); })
#endif /* !__CRT_HAVE_ctermid */
#endif /* !__ctermid_defined */
#ifndef __cuserid_defined
#define __cuserid_defined
#ifdef __CRT_HAVE_cuserid
/* >> cuserid(3)
 * Return the name of the current user (`$LOGNAME' or `getpwuid(geteuid())'), storing
 * that  name  in  `s'.  When  `s'  is   NULL,  a  static  buffer  is  used   instead
 * When  given,   `s'   must  be   a   buffer   of  at   least   `L_cuserid'   bytes.
 * If the actual  username is longer  than this,  it may be  truncated, and  programs
 * that wish to support longer usernames  should make use of `getlogin_r()'  instead.
 * s.a. `getlogin()' and `getlogin_r()' */
__CDECLARE(__ATTR_OUT_OPT(1),char *,__NOTHROW_NCX,cuserid,(char *__s),(__s))
#else /* __CRT_HAVE_cuserid */
#include <libc/template/environ.h>
#if defined(__CRT_HAVE_getlogin_r) || defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ) || (defined(__CRT_HAVE_getpwuid_r) && (defined(__CRT_HAVE_geteuid) || defined(__CRT_HAVE___geteuid) || defined(__CRT_HAVE___libc_geteuid) || defined(__CRT_HAVE_getresuid)))
#include <libc/local/unistd/cuserid.h>
/* >> cuserid(3)
 * Return the name of the current user (`$LOGNAME' or `getpwuid(geteuid())'), storing
 * that  name  in  `s'.  When  `s'  is   NULL,  a  static  buffer  is  used   instead
 * When  given,   `s'   must  be   a   buffer   of  at   least   `L_cuserid'   bytes.
 * If the actual  username is longer  than this,  it may be  truncated, and  programs
 * that wish to support longer usernames  should make use of `getlogin_r()'  instead.
 * s.a. `getlogin()' and `getlogin_r()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(cuserid, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT_OPT(1) char *__NOTHROW_NCX(__LIBCCALL cuserid)(char *__s) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cuserid))(__s); })
#else /* __CRT_HAVE_getlogin_r || __CRT_HAVE_getenv || __LOCAL_environ || (__CRT_HAVE_getpwuid_r && (__CRT_HAVE_geteuid || __CRT_HAVE___geteuid || __CRT_HAVE___libc_geteuid || __CRT_HAVE_getresuid)) */
#undef __cuserid_defined
#endif /* !__CRT_HAVE_getlogin_r && !__CRT_HAVE_getenv && !__LOCAL_environ && (!__CRT_HAVE_getpwuid_r || (!__CRT_HAVE_geteuid && !__CRT_HAVE___geteuid && !__CRT_HAVE___libc_geteuid && !__CRT_HAVE_getresuid)) */
#endif /* !__CRT_HAVE_cuserid */
#endif /* !__cuserid_defined */
#endif /* _EVERY_SOURCE || __USE_SOLARIS || (__USE_XOPEN && !__USE_XOPEN2K) */

#ifdef __USE_NETBSD
#ifndef sys_siglist
#ifdef _sys_siglist
#define sys_siglist _sys_siglist
#else /* _sys_siglist */
#if !defined(____p_sys_siglist_defined) && defined(__CRT_HAVE___p_sys_siglist)
#define ____p_sys_siglist_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char const *const *,__NOTHROW,__p_sys_siglist,(void),())
#endif /* !____p_sys_siglist_defined && __CRT_HAVE___p_sys_siglist */
#ifdef ____p_sys_siglist_defined
#define sys_siglist  __p_sys_siglist()
#define _sys_siglist __p_sys_siglist()
#endif /* ____p_sys_siglist_defined */
#ifndef _sys_siglist
#ifdef __CRT_HAVE_sys_siglist
#ifdef __NSIG
__CSDECLARE2(,char const *const sys_siglist[__NSIG],sys_siglist)
#else /* __NSIG */
__CSDECLARE2(,char const *const sys_siglist[],sys_siglist)
#endif /* !__NSIG */
#define sys_siglist  sys_siglist
#define _sys_siglist sys_siglist
#elif defined(__CRT_HAVE__sys_siglist)
#ifdef __NSIG
__CSDECLARE2(,char const *const _sys_siglist[__NSIG],_sys_siglist)
#else /* __NSIG */
__CSDECLARE2(,char const *const _sys_siglist[],_sys_siglist)
#endif /* !__NSIG */
#define sys_siglist  _sys_siglist
#define _sys_siglist _sys_siglist
#endif /* sys_siglist... */
#endif /* !_sys_siglist */
#endif /* !_sys_siglist */
#endif /* !sys_siglist */

#ifndef __sa_family_t_defined
#define __sa_family_t_defined
typedef __sa_family_t sa_family_t; /* One of `AF_*' */
#endif /* !__sa_family_t_defined */
#ifndef __getgrouplist_defined
#define __getgrouplist_defined
#ifdef __CRT_HAVE_getgrouplist
/* >> getgrouplist(3)
 * Use the groups database to find the GIDs of all of the groups which `user'
 * is apart of. In case this list doesn't already include `group', it will be
 * inserted into the list (thus making sure that it is always a member).
 * @param: user:    The name to seach for in the member lists of groups.
 * @param: group:   Usually, the default group of `user' (as retrieved from  the
 *                  functions from `<pwd.h>'). This group will always be made to
 *                  be a member of the list of GIDs written to `*groups'
 * @param: groups:  Output buffer for GIDs
 * @param: ngroups: [in]  The buffer length (max #  of elements) that can be  stored
 *                        in the given buffer before it become full. When this limit
 *                  [out] The required buffer size (in elements). Upon success, the
 *                        value written  here is  identical  to the  return  value.
 * @return: * : [== *ngroups] The number of items written to `groups'
 * @return: -1: More than `IN(*ngroups)' elements would have been written to  `groups'.
 *              In this case, `OUT(*ngroups)' specifies the number of required elements
 *              in terms of buffer  size to write  all groups (use  this to resize  the
 *              buffer you're passing for `groups').
 *              Note that standards don't say anything about `errno' in this case,
 *              so the KOS implementation of this function simply leaves its value
 *              untouched when this happens (other implementations might set it to
 *              `ERANGE' for example...) */
__CDECLARE(__ATTR_IN(1) __ATTR_INOUT(4) __ATTR_OUT(3),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,getgrouplist,(char const *__user, __gid_t __group, __gid_t *__groups, __STDC_INT_AS_SIZE_T *__ngroups),(__user,__group,__groups,__ngroups))
#elif defined(__CRT_HAVE_setgrent) && defined(__CRT_HAVE_getgrent)
#include <libc/local/grp/getgrouplist.h>
/* >> getgrouplist(3)
 * Use the groups database to find the GIDs of all of the groups which `user'
 * is apart of. In case this list doesn't already include `group', it will be
 * inserted into the list (thus making sure that it is always a member).
 * @param: user:    The name to seach for in the member lists of groups.
 * @param: group:   Usually, the default group of `user' (as retrieved from  the
 *                  functions from `<pwd.h>'). This group will always be made to
 *                  be a member of the list of GIDs written to `*groups'
 * @param: groups:  Output buffer for GIDs
 * @param: ngroups: [in]  The buffer length (max #  of elements) that can be  stored
 *                        in the given buffer before it become full. When this limit
 *                  [out] The required buffer size (in elements). Upon success, the
 *                        value written  here is  identical  to the  return  value.
 * @return: * : [== *ngroups] The number of items written to `groups'
 * @return: -1: More than `IN(*ngroups)' elements would have been written to  `groups'.
 *              In this case, `OUT(*ngroups)' specifies the number of required elements
 *              in terms of buffer  size to write  all groups (use  this to resize  the
 *              buffer you're passing for `groups').
 *              Note that standards don't say anything about `errno' in this case,
 *              so the KOS implementation of this function simply leaves its value
 *              untouched when this happens (other implementations might set it to
 *              `ERANGE' for example...) */
__NAMESPACE_LOCAL_USING_OR_IMPL(getgrouplist, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_INOUT(4) __ATTR_OUT(3) __STDC_INT_AS_SSIZE_T __NOTHROW_RPC(__LIBCCALL getgrouplist)(char const *__user, __gid_t __group, __gid_t *__groups, __STDC_INT_AS_SIZE_T *__ngroups) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getgrouplist))(__user, __group, __groups, __ngroups); })
#else /* ... */
#undef __getgrouplist_defined
#endif /* !... */
#endif /* !__getgrouplist_defined */
#ifndef __initgroups_defined
#define __initgroups_defined
#ifdef __CRT_HAVE_initgroups
/* >> initgroups(3)
 * A helper function that combines `getgrouplist(3)' with `setgroups(2)',
 * and can be used to set the calling process's group list to that of the
 * given user, whilst always being guarantied to also include `group'!
 * @return: 0 : Success
 * @return: -1: [errno=ENOMEM] Out of member
 * @return: -1: [errno=EPERM]  You're not allowed  to call  `setgroups(2)',
 *                             or at least not in the way you're trying to. */
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,initgroups,(char const *__user, __gid_t __group),(__user,__group))
#elif (defined(__CRT_HAVE_getgrouplist) || (defined(__CRT_HAVE_setgrent) && defined(__CRT_HAVE_getgrent))) && (defined(__CRT_HAVE_setgroups) || defined(__CRT_HAVE___setgroups) || defined(__CRT_HAVE___libc_setgroups)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/grp/initgroups.h>
/* >> initgroups(3)
 * A helper function that combines `getgrouplist(3)' with `setgroups(2)',
 * and can be used to set the calling process's group list to that of the
 * given user, whilst always being guarantied to also include `group'!
 * @return: 0 : Success
 * @return: -1: [errno=ENOMEM] Out of member
 * @return: -1: [errno=EPERM]  You're not allowed  to call  `setgroups(2)',
 *                             or at least not in the way you're trying to. */
__NAMESPACE_LOCAL_USING_OR_IMPL(initgroups, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL initgroups)(char const *__user, __gid_t __group) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(initgroups))(__user, __group); })
#else /* ... */
#undef __initgroups_defined
#endif /* !... */
#endif /* !__initgroups_defined */
#ifndef __mkstemps_defined
#define __mkstemps_defined
#include <asm/os/oflags.h>
#if defined(__CRT_HAVE_mkstemps) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
/* >> mkstemps(3), mkstemps64(3)
 * Replace the last 6 characters of `template_' (which are followed by exactly
 * `suffixlen' more characters that are left alone), which must be filled with
 * all  'X'-characters before the  call (else errno=EINVAL  + return -1), with
 * random  characters such that the filename described by `template_' will not
 * already  exists. Then, create a new file  with `O_RDWR' and return the file
 * descriptor of that file.
 * @param: suffixlen: The #  of trailing  characters to-be  ignored
 *                    after the required 6 trailing 'X'-characters. */
__CDECLARE(__ATTR_WUNUSED __ATTR_INOUT(1),__fd_t,__NOTHROW_RPC,mkstemps,(char *__template_, __STDC_INT_AS_SIZE_T __suffixlen),(__template_,__suffixlen))
#elif defined(__CRT_HAVE_mkstemps64)
/* >> mkstemps(3), mkstemps64(3)
 * Replace the last 6 characters of `template_' (which are followed by exactly
 * `suffixlen' more characters that are left alone), which must be filled with
 * all  'X'-characters before the  call (else errno=EINVAL  + return -1), with
 * random  characters such that the filename described by `template_' will not
 * already  exists. Then, create a new file  with `O_RDWR' and return the file
 * descriptor of that file.
 * @param: suffixlen: The #  of trailing  characters to-be  ignored
 *                    after the required 6 trailing 'X'-characters. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),__fd_t,__NOTHROW_RPC,mkstemps,(char *__template_, __STDC_INT_AS_SIZE_T __suffixlen),mkstemps64,(__template_,__suffixlen))
#else /* ... */
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_mkostemps) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_mkostemps64) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#include <libc/local/stdlib/mkstemps.h>
/* >> mkstemps(3), mkstemps64(3)
 * Replace the last 6 characters of `template_' (which are followed by exactly
 * `suffixlen' more characters that are left alone), which must be filled with
 * all  'X'-characters before the  call (else errno=EINVAL  + return -1), with
 * random  characters such that the filename described by `template_' will not
 * already  exists. Then, create a new file  with `O_RDWR' and return the file
 * descriptor of that file.
 * @param: suffixlen: The #  of trailing  characters to-be  ignored
 *                    after the required 6 trailing 'X'-characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(mkstemps, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_INOUT(1) __fd_t __NOTHROW_RPC(__LIBCCALL mkstemps)(char *__template_, __STDC_INT_AS_SIZE_T __suffixlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mkstemps))(__template_, __suffixlen); })
#else /* (__CRT_HAVE_mkostemps && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_mkostemps64 || __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
#undef __mkstemps_defined
#endif /* (!__CRT_HAVE_mkostemps || (__USE_FILE_OFFSET64 && __O_LARGEFILE && __O_LARGEFILE)) && !__CRT_HAVE_mkostemps64 && !__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)) */
#endif /* !... */
#endif /* !__mkstemps_defined */
#ifndef __psignal_defined
#define __psignal_defined
#ifdef __CRT_HAVE_psignal
/* >> psignal(3)
 * Same as `fprintf(stderr, "%s: %s\n", s, sigabbrev_np(signo) ? "SIG"+. : strdupf("Unknown signal %d", signo))'
 * When `s' is `NULL' or an empty string, omit the leading "%s: " from the format. */
__CDECLARE_VOID(,__NOTHROW_NCX,psignal,(__signo_t __signo, char const *__s),(__signo,__s))
#else /* __CRT_HAVE_psignal */
#include <libc/template/stdstreams.h>
#if defined(__LOCAL_stderr) && (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <libc/local/signal/psignal.h>
/* >> psignal(3)
 * Same as `fprintf(stderr, "%s: %s\n", s, sigabbrev_np(signo) ? "SIG"+. : strdupf("Unknown signal %d", signo))'
 * When `s' is `NULL' or an empty string, omit the leading "%s: " from the format. */
__NAMESPACE_LOCAL_USING_OR_IMPL(psignal, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL psignal)(__signo_t __signo, char const *__s) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(psignal))(__signo, __s); })
#else /* __LOCAL_stderr && (__CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) */
#undef __psignal_defined
#endif /* !__LOCAL_stderr || (!__CRT_HAVE_fprintf && !__CRT_HAVE__IO_fprintf && !__CRT_HAVE_fprintf_s && !__CRT_HAVE_fprintf_unlocked && !__CRT_HAVE_vfprintf && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock) */
#endif /* !__CRT_HAVE_psignal */
#endif /* !__psignal_defined */
#if !defined(__rcmd_defined) && defined(__CRT_HAVE_rcmd)
#define __rcmd_defined
/* Call `rshd' at port `rport' on remote machine `*ahost' to execute `cmd'.
 * The  local  user is  `locuser',  on the  remote  machine the  command is
 * executed as `remuser'. In `*fd2p' the  descriptor to the socket for  the
 * connection is  returned.  The  caller  must have  the  right  to  use  a
 * reserved  port.  When  the   function  returns  `*ahost'  contains   the
 * official host name.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE(,int,__NOTHROW_RPC,rcmd,(char **__restrict __ahost, __UINT16_TYPE__ __rport, char const *__restrict __locuser, char const *__restrict __remuser, char const *__restrict __cmd, int *__restrict __fd2p),(__ahost,__rport,__locuser,__remuser,__cmd,__fd2p))
#endif /* !__rcmd_defined && __CRT_HAVE_rcmd */
#if !defined(__rresvport_defined) && defined(__CRT_HAVE_rresvport)
#define __rresvport_defined
/* Try to allocate reserved port, returning a descriptor for a socket opened
 * at this port  or -1  if unsuccessful. The  search for  an available  port
 * will   start   at   `alport'   and   continues   with   lower    numbers.
 * This   function  is  not   part  of  POSIX   and  therefore  no  official
 * cancellation point */
__CDECLARE(,int,__NOTHROW_RPC,rresvport,(int *__alport),(__alport))
#endif /* !__rresvport_defined && __CRT_HAVE_rresvport */
#ifndef __setgroups_defined
#define __setgroups_defined
#ifdef __CRT_HAVE_setgroups
/* >> setgroups(2) */
__CDECLARE(__ATTR_INS(2, 1),int,__NOTHROW_RPC,setgroups,(size_t __count, __gid_t const *__groups),(__count,__groups))
#elif defined(__CRT_HAVE___setgroups)
/* >> setgroups(2) */
__CREDIRECT(__ATTR_INS(2, 1),int,__NOTHROW_RPC,setgroups,(size_t __count, __gid_t const *__groups),__setgroups,(__count,__groups))
#elif defined(__CRT_HAVE___libc_setgroups)
/* >> setgroups(2) */
__CREDIRECT(__ATTR_INS(2, 1),int,__NOTHROW_RPC,setgroups,(size_t __count, __gid_t const *__groups),__libc_setgroups,(__count,__groups))
#else /* ... */
#undef __setgroups_defined
#endif /* !... */
#endif /* !__setgroups_defined */
#if !defined(__ruserok_defined) && defined(__CRT_HAVE_ruserok)
#define __ruserok_defined
/* Check whether user `remuser' on system `rhost' is allowed to login
 * as `locuser'. If  `suser' is  not zero  the user  tries to  become
 * superuser. Return 0 if it is possible.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE(,int,__NOTHROW_RPC,ruserok,(char const *__rhost, int __suser, char const *__remuser, char const *__locuser),(__rhost,__suser,__remuser,__locuser))
#endif /* !__ruserok_defined && __CRT_HAVE_ruserok */
#ifndef __strmode_defined
#define __strmode_defined
#ifdef __CRT_HAVE_strmode
/* Generate  a file mode representation similar to what's printed by `ls -l'
 * The representation is written to `p', and `mode' is the value as returned
 * by `stat(2)' in `struct stat::st_mode'
 * The format written is:
 *    p[0]  = <mode & S_IFMT>: { S_IFDIR: 'd', S_IFCHR: 'c', S_IFBLK:  'b',
 *                               S_IFREG: '-', S_IFLNK: 'l', S_IFSOCK: 's',
 *                               S_IFIFO: 'p' }, else: '?';
 *    p[1]  = mode & S_IRUSR ? 'r' : '-';
 *    p[2]  = mode & S_IWUSR ? 'w' : '-';
 *    p[3]  = <mode & S_IXUSR | S_ISUID>: { 0: '-', S_IXUSR: 'x', S_ISUID: 'S',
 *                                          S_IXUSR | S_ISUID: 's' };
 *    p[4] = mode & S_IRGRP ? 'r' : '-';
 *    p[5] = mode & S_IWGRP ? 'w' : '-';
 *    p[6]  = <mode & S_IXGRP | S_ISGID>: { 0: '-', S_IXGRP: 'x', S_ISGID: 'S',
 *                                          S_IXGRP | S_ISGID: 's' };
 *    p[7] = mode & S_IROTH ? 'r' : '-';
 *    p[8] = mode & S_IWOTH ? 'w' : '-';
 *    p[9]  = <mode & S_IXOTH | S_ISVTX>: { 0: '-', S_IXOTH: 'x', S_ISVTX: 'T',
 *                                          S_IXOTH | S_ISVTX: 't' };
 *    p[10] = ' '; // '+', if "alternate or additional access control
 *                 //          methods associated with the inode"
 *    p[11] = '\0'; */
__CDECLARE_VOID(__ATTR_OUT(2),__NOTHROW_NCX,strmode,(__mode_t __mode, char __p[12]),(__mode,__p))
#else /* __CRT_HAVE_strmode */
#include <libc/local/string/strmode.h>
/* Generate  a file mode representation similar to what's printed by `ls -l'
 * The representation is written to `p', and `mode' is the value as returned
 * by `stat(2)' in `struct stat::st_mode'
 * The format written is:
 *    p[0]  = <mode & S_IFMT>: { S_IFDIR: 'd', S_IFCHR: 'c', S_IFBLK:  'b',
 *                               S_IFREG: '-', S_IFLNK: 'l', S_IFSOCK: 's',
 *                               S_IFIFO: 'p' }, else: '?';
 *    p[1]  = mode & S_IRUSR ? 'r' : '-';
 *    p[2]  = mode & S_IWUSR ? 'w' : '-';
 *    p[3]  = <mode & S_IXUSR | S_ISUID>: { 0: '-', S_IXUSR: 'x', S_ISUID: 'S',
 *                                          S_IXUSR | S_ISUID: 's' };
 *    p[4] = mode & S_IRGRP ? 'r' : '-';
 *    p[5] = mode & S_IWGRP ? 'w' : '-';
 *    p[6]  = <mode & S_IXGRP | S_ISGID>: { 0: '-', S_IXGRP: 'x', S_ISGID: 'S',
 *                                          S_IXGRP | S_ISGID: 's' };
 *    p[7] = mode & S_IROTH ? 'r' : '-';
 *    p[8] = mode & S_IWOTH ? 'w' : '-';
 *    p[9]  = <mode & S_IXOTH | S_ISVTX>: { 0: '-', S_IXOTH: 'x', S_ISVTX: 'T',
 *                                          S_IXOTH | S_ISVTX: 't' };
 *    p[10] = ' '; // '+', if "alternate or additional access control
 *                 //          methods associated with the inode"
 *    p[11] = '\0'; */
__NAMESPACE_LOCAL_USING_OR_IMPL(strmode, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(2) void __NOTHROW_NCX(__LIBCCALL strmode)(__mode_t __mode, char __p[12]) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strmode))(__mode, __p); })
#endif /* !__CRT_HAVE_strmode */
#endif /* !__strmode_defined */
#ifndef __strsignal_defined
#define __strsignal_defined
#ifdef __CRT_HAVE_strsignal
__CDECLARE(__ATTR_COLD __ATTR_RETNONNULL __ATTR_WUNUSED,char *,__NOTHROW_NCX,strsignal,(__signo_t __signo),(__signo))
#else /* __CRT_HAVE_strsignal */
#include <libc/local/string/strsignal.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(strsignal, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_COLD __ATTR_RETNONNULL __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL strsignal)(__signo_t __signo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strsignal))(__signo); })
#endif /* !__CRT_HAVE_strsignal */
#endif /* !__strsignal_defined */
#if !defined(__rcmd_af_defined) && defined(__CRT_HAVE_rcmd_af)
#define __rcmd_af_defined
/* This is the equivalent function where the protocol can be selected
 * and which therefore can be used for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE(,int,__NOTHROW_RPC,rcmd_af,(char **__restrict __ahost, __UINT16_TYPE__ __rport, char const *__restrict __locuser, char const *__restrict __remuser, char const *__restrict __cmd, int *__restrict __fd2p, sa_family_t __af),(__ahost,__rport,__locuser,__remuser,__cmd,__fd2p,__af))
#endif /* !__rcmd_af_defined && __CRT_HAVE_rcmd_af */

/* Flags for NetBSD's `getpassfd(3)' function */
#if !defined(GETPASS_NEED_TTY) && defined(__GETPASS_NEED_TTY)
#define GETPASS_NEED_TTY    __GETPASS_NEED_TTY    /* RPP_REQUIRE_TTY: Error out if `!isatty()' */
#endif /* !GETPASS_NEED_TTY && __GETPASS_NEED_TTY */
#if !defined(GETPASS_FAIL_EOF) && defined(__GETPASS_FAIL_EOF)
#define GETPASS_FAIL_EOF    __GETPASS_FAIL_EOF    /* Input EOF is an error */
#endif /* !GETPASS_FAIL_EOF && __GETPASS_FAIL_EOF */
#if !defined(GETPASS_BUF_LIMIT) && defined(__GETPASS_BUF_LIMIT)
#define GETPASS_BUF_LIMIT   __GETPASS_BUF_LIMIT   /* BEEP when typing after buffer limit is reached */
#endif /* !GETPASS_BUF_LIMIT && __GETPASS_BUF_LIMIT */
#if !defined(GETPASS_NO_SIGNAL) && defined(__GETPASS_NO_SIGNAL)
#define GETPASS_NO_SIGNAL   __GETPASS_NO_SIGNAL   /* When a control character (such as ^C) causes password
                                                   * reading  to  be aborted  (with  `errno=EINTR'), don't
                                                   * raise(3) the  signal associated  with that  character
                                                   * before returning from `getpassfd()' */
#endif /* !GETPASS_NO_SIGNAL && __GETPASS_NO_SIGNAL */
#if !defined(GETPASS_NO_BEEP) && defined(__GETPASS_NO_BEEP)
#define GETPASS_NO_BEEP     __GETPASS_NO_BEEP     /* Don't BEEP */
#endif /* !GETPASS_NO_BEEP && __GETPASS_NO_BEEP */
#if !defined(GETPASS_ECHO) && defined(__GETPASS_ECHO)
#define GETPASS_ECHO        __GETPASS_ECHO        /* RPP_ECHO_ON: Don't disable echo (but leave it on). */
#endif /* !GETPASS_ECHO && __GETPASS_ECHO */
#if !defined(GETPASS_ECHO_STAR) && defined(__GETPASS_ECHO_STAR)
#define GETPASS_ECHO_STAR   __GETPASS_ECHO_STAR   /* Print '*' instead for typed characters */
#endif /* !GETPASS_ECHO_STAR && __GETPASS_ECHO_STAR */
#if !defined(GETPASS_7BIT) && defined(__GETPASS_7BIT)
#define GETPASS_7BIT        __GETPASS_7BIT        /* RPP_SEVENBIT: Mask input with `0x7f' */
#endif /* !GETPASS_7BIT && __GETPASS_7BIT */
#if !defined(GETPASS_FORCE_LOWER) && defined(__GETPASS_FORCE_LOWER)
#define GETPASS_FORCE_LOWER __GETPASS_FORCE_LOWER /* RPP_FORCELOWER: Force all input to be lower-case. */
#endif /* !GETPASS_FORCE_LOWER && __GETPASS_FORCE_LOWER */
#if !defined(GETPASS_FORCE_UPPER) && defined(__GETPASS_FORCE_UPPER)
#define GETPASS_FORCE_UPPER __GETPASS_FORCE_UPPER /* RPP_FORCEUPPER: Force all input to be upper-case. */
#endif /* !GETPASS_FORCE_UPPER && __GETPASS_FORCE_UPPER */
#if !defined(GETPASS_ECHO_NL) && defined(__GETPASS_ECHO_NL)
#define GETPASS_ECHO_NL     __GETPASS_ECHO_NL     /* Print a '\n' after the password was read */
#endif /* !GETPASS_ECHO_NL && __GETPASS_ECHO_NL */
#ifdef __CRT_HAVE_getpassfd
/* >> getpassfd(3)
 * This function behaves  similar to `readpassphrase(3)',  but is  still
 * quite  distinct from that  function in how this  one behaves, vs. how
 * that other function behaves. In general, this function is a bit  more
 * user-friendly, in  that it  offers more  (but different)  `flags'  to
 * control how the password prompt is generated, with the main advantage
 * of this function  being that it  implements some "advanced"  readline
 * functionality, such as deleting  typed characters without relying  on
 * the  system  TTY canonical  buffer (which  `readpassphrase(3)' needs,
 * since it doesn't include support  for _any_ control characters  other
 * that CR/LF as indicators to stop reading text)
 * Which of the 2 functions should be used is a matter of taste, but
 * personally,   I   prefer  this   one   over  `readpassphrase(3)'.
 * @param: prompt:  [0..1]      Text-prompt to display to the user, or `NULL'
 * @param: buf:     [0..buflen] Buffer that will receive the user's password.
 *                              When set to  `NULL', a dynamically  allocated
 *                              buffer will be used and returned.
 * @param: buflen:              Size of `buf' (in characters) (ignored when `buf == NULL')
 * @param: fds:     [0..1]      When non-NULL,  an [stdin,stdout,stderr]  triple
 *                              of files, used for [read,write,beep] operations.
 *                              When  `NULL', try to use `/dev/tty' instead, and
 *                              if that fails, use  `STDIN_FILENO,STDERR_FILENO,
 *                              STDERR_FILENO' as final fallback.
 *                              When `GETPASS_NEED_TTY' is set, the  function
 *                              will fail with `errno=ENOTTY' if the actually
 *                              used `fds[0]' (iow: stdin) isn't a TTY device
 *                              s.a. `isatty(3)'
 * @param: flags:               Set of `GETPASS_*' flags (from <unistd.h>)
 * @param: timeout_in_seconds:  When non-0, timeout (in  seconds) to wait for  the
 *                              user to type each character of their password.  If
 *                              this timeout expires, fail with  `errno=ETIMEDOUT'
 *                              Negative values result in weak undefined behavior.
 * @return: * :   [buf == NULL] Success (dynamically allocated buffer; must be `free(3)'d)
 * @return: buf:                Success
 * @return: NULL: [ETIMEDOUT]   The given `timeout_in_seconds' has expired.
 * @return: NULL: [EINVAL]      `buf' is non-`NULL', but `buflen' is `0'
 * @return: NULL: [ENOTTY]      `GETPASS_NEED_TTY' was given, but not a tty
 * @return: NULL: [ENOMEM]      Insufficient memory
 * @return: NULL: [ENODATA]     End-of-file while reading, and `GETPASS_FAIL_EOF' was set.
 * @return: NULL: [*]           Error */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN_OPT(1) __ATTR_IN_OPT(4) __ATTR_OUT_OPT(2),char *,__NOTHROW_RPC,getpassfd,(char const *__prompt, char *__buf, size_t __buflen, __fd_t __fds[3], __STDC_INT_AS_UINT_T __flags, int __timeout_in_seconds),(__prompt,__buf,__buflen,__fds,__flags,__timeout_in_seconds))
#elif defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)
#include <libc/local/unistd/getpassfd.h>
/* >> getpassfd(3)
 * This function behaves  similar to `readpassphrase(3)',  but is  still
 * quite  distinct from that  function in how this  one behaves, vs. how
 * that other function behaves. In general, this function is a bit  more
 * user-friendly, in  that it  offers more  (but different)  `flags'  to
 * control how the password prompt is generated, with the main advantage
 * of this function  being that it  implements some "advanced"  readline
 * functionality, such as deleting  typed characters without relying  on
 * the  system  TTY canonical  buffer (which  `readpassphrase(3)' needs,
 * since it doesn't include support  for _any_ control characters  other
 * that CR/LF as indicators to stop reading text)
 * Which of the 2 functions should be used is a matter of taste, but
 * personally,   I   prefer  this   one   over  `readpassphrase(3)'.
 * @param: prompt:  [0..1]      Text-prompt to display to the user, or `NULL'
 * @param: buf:     [0..buflen] Buffer that will receive the user's password.
 *                              When set to  `NULL', a dynamically  allocated
 *                              buffer will be used and returned.
 * @param: buflen:              Size of `buf' (in characters) (ignored when `buf == NULL')
 * @param: fds:     [0..1]      When non-NULL,  an [stdin,stdout,stderr]  triple
 *                              of files, used for [read,write,beep] operations.
 *                              When  `NULL', try to use `/dev/tty' instead, and
 *                              if that fails, use  `STDIN_FILENO,STDERR_FILENO,
 *                              STDERR_FILENO' as final fallback.
 *                              When `GETPASS_NEED_TTY' is set, the  function
 *                              will fail with `errno=ENOTTY' if the actually
 *                              used `fds[0]' (iow: stdin) isn't a TTY device
 *                              s.a. `isatty(3)'
 * @param: flags:               Set of `GETPASS_*' flags (from <unistd.h>)
 * @param: timeout_in_seconds:  When non-0, timeout (in  seconds) to wait for  the
 *                              user to type each character of their password.  If
 *                              this timeout expires, fail with  `errno=ETIMEDOUT'
 *                              Negative values result in weak undefined behavior.
 * @return: * :   [buf == NULL] Success (dynamically allocated buffer; must be `free(3)'d)
 * @return: buf:                Success
 * @return: NULL: [ETIMEDOUT]   The given `timeout_in_seconds' has expired.
 * @return: NULL: [EINVAL]      `buf' is non-`NULL', but `buflen' is `0'
 * @return: NULL: [ENOTTY]      `GETPASS_NEED_TTY' was given, but not a tty
 * @return: NULL: [ENOMEM]      Insufficient memory
 * @return: NULL: [ENODATA]     End-of-file while reading, and `GETPASS_FAIL_EOF' was set.
 * @return: NULL: [*]           Error */
__NAMESPACE_LOCAL_USING_OR_IMPL(getpassfd, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN_OPT(1) __ATTR_IN_OPT(4) __ATTR_OUT_OPT(2) char *__NOTHROW_RPC(__LIBCCALL getpassfd)(char const *__prompt, char *__buf, size_t __buflen, __fd_t __fds[3], __STDC_INT_AS_UINT_T __flags, int __timeout_in_seconds) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getpassfd))(__prompt, __buf, __buflen, __fds, __flags, __timeout_in_seconds); })
#endif /* ... */
#ifdef __CRT_HAVE_getpass_r
/* >> getpass_r(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN_OPT(1) __ATTR_OUT_OPT(2),char *,__NOTHROW_RPC,getpass_r,(char const *__prompt, char *__buf, size_t __bufsize),(__prompt,__buf,__bufsize))
#elif defined(__CRT_HAVE_getpassfd) || defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read) || defined(__CRT_HAVE_readpassphrase)
#include <libc/local/unistd/getpass_r.h>
/* >> getpass_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(getpass_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN_OPT(1) __ATTR_OUT_OPT(2) char *__NOTHROW_RPC(__LIBCCALL getpass_r)(char const *__prompt, char *__buf, size_t __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getpass_r))(__prompt, __buf, __bufsize); })
#endif /* ... */

/* WARNING: `setmode(3)' is also a completely different DOS-specific function in <io.h>! */
#if !defined(__setmode_defined) && defined(__CRT_HAVE_setmode)
#define __setmode_defined
/* >> setmode(3), getmode(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),void *,__NOTHROW_NCX,setmode,(char const *__mode_str),(__mode_str))
#endif /* !__setmode_defined && __CRT_HAVE_setmode */
/* >> setmode(3), getmode(3) */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_IN(1),__mode_t,__NOTHROW_NCX,getmode,(void const *__bbox, __mode_t __mode),(__bbox,__mode))
#ifndef __getpeereid_defined
#define __getpeereid_defined
#ifdef __CRT_HAVE_getpeereid
/* >> getpeereid(3)
 * Convenience wrapper for `getsockopt(sockfd, SOL_SOCKET, SO_PEERCRED)' */
__CDECLARE(__ATTR_OUT(2) __ATTR_OUT(3),int,__NOTHROW_NCX,getpeereid,(__fd_t __sockfd, uid_t *__euid, gid_t *__egid),(__sockfd,__euid,__egid))
#else /* __CRT_HAVE_getpeereid */
#include <asm/os/socket.h>
#if defined(__CRT_HAVE_getsockopt) && defined(__SOL_SOCKET) && defined(__SO_PEERCRED)
#include <libc/local/unistd/getpeereid.h>
/* >> getpeereid(3)
 * Convenience wrapper for `getsockopt(sockfd, SOL_SOCKET, SO_PEERCRED)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(getpeereid, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(2) __ATTR_OUT(3) int __NOTHROW_NCX(__LIBCCALL getpeereid)(__fd_t __sockfd, uid_t *__euid, gid_t *__egid) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getpeereid))(__sockfd, __euid, __egid); })
#else /* __CRT_HAVE_getsockopt && __SOL_SOCKET && __SO_PEERCRED */
#undef __getpeereid_defined
#endif /* !__CRT_HAVE_getsockopt || !__SOL_SOCKET || !__SO_PEERCRED */
#endif /* !__CRT_HAVE_getpeereid */
#endif /* !__getpeereid_defined */
#ifdef __CRT_HAVE_lpathconf
/* >> lpathconf(3)
 * Same as `pathconf(3)', but don't dereference `path' if it's a symbolic link */
__CDECLARE(__ATTR_IN(1),__LONGPTR_TYPE__,__NOTHROW_RPC,lpathconf,(char const *__path, __STDC_INT_AS_UINT_T __name),(__path,__name))
#else /* __CRT_HAVE_lpathconf */
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_fpathconf) || defined(__CRT_HAVE___fpathconf)) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && defined(__O_RDONLY) && defined(__O_PATH) && defined(__O_NOFOLLOW)
#include <libc/local/unistd/lpathconf.h>
/* >> lpathconf(3)
 * Same as `pathconf(3)', but don't dereference `path' if it's a symbolic link */
__NAMESPACE_LOCAL_USING_OR_IMPL(lpathconf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __LONGPTR_TYPE__ __NOTHROW_RPC(__LIBCCALL lpathconf)(char const *__path, __STDC_INT_AS_UINT_T __name) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lpathconf))(__path, __name); })
#endif /* (__CRT_HAVE_fpathconf || __CRT_HAVE___fpathconf) && (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && __O_RDONLY && __O_PATH && __O_NOFOLLOW */
#endif /* !__CRT_HAVE_lpathconf */
#ifdef __CRT_HAVE_setruid
/* >> setruid(3)
 * Set only the real UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(,int,__NOTHROW_NCX,setruid,(uid_t __ruid),(__ruid))
#elif defined(__CRT_HAVE_setreuid) || defined(__CRT_HAVE___setreuid) || defined(__CRT_HAVE___libc_setreuid) || defined(__CRT_HAVE_setresuid)
#include <libc/local/unistd/setruid.h>
/* >> setruid(3)
 * Set only the real UID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(setruid, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL setruid)(uid_t __ruid) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setruid))(__ruid); })
#endif /* ... */
#ifdef __CRT_HAVE_setrgid
/* >> setrgid(3)
 * Set only the real GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(,int,__NOTHROW_NCX,setrgid,(gid_t __rgid),(__rgid))
#elif defined(__CRT_HAVE_setregid) || defined(__CRT_HAVE___setregid) || defined(__CRT_HAVE___libc_setregid) || defined(__CRT_HAVE_setresgid)
#include <libc/local/unistd/setrgid.h>
/* >> setrgid(3)
 * Set only the real GID of the calling thread.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(setrgid, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL setrgid)(gid_t __rgid) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setrgid))(__rgid); })
#endif /* ... */
#endif /* __USE_NETBSD */


#if defined(_EVERY_SOURCE) || defined(__USE_SOLARIS) || (defined(__USE_UNIX98) && !defined(__USE_XOPEN2K))
#if !defined(__pthread_atfork_defined) && defined(__CRT_HAVE_pthread_atfork)
#define __pthread_atfork_defined
/* >> pthread_atfork(3)
 * Install handlers to be called when a new process is created with  `fork(2)'.
 * The `prepare' handler is called in the parent process just before performing
 * `fork(2)'. The `parent' handler is called  in the parent process just  after
 * `fork(2)'.  The `child' handler is called in  the child process. Each of the
 * three  handlers can be `NULL', meaning that no handler needs to be called at
 * that point.
 * `pthread_atfork(3)' can be called several times, in which case the `prepare'
 * handlers are  called in  LIFO order  (last added  with  `pthread_atfork(3)',
 * first  called before `fork(2)'),  and the `parent'  and `child' handlers are
 * called in FIFO order (first added -> first called)
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to register callbacks */
__CDECLARE(,__errno_t,__NOTHROW_NCX,pthread_atfork,(void (__LIBCCALL *__prepare)(void), void (__LIBCCALL *__parent)(void), void (__LIBCCALL *__child)(void)),(__prepare,__parent,__child))
#endif /* !__pthread_atfork_defined && __CRT_HAVE_pthread_atfork */
#endif /* _EVERY_SOURCE || __USE_SOLARIS || (__USE_UNIX98 && !__USE_XOPEN2K) */


#if defined(__USE_REENTRANT) || defined(__USE_SOLARIS)
#ifndef __ctermid_r_defined
#define __ctermid_r_defined
#ifdef __CRT_HAVE_ctermid_r
/* >> ctermid_r(3)
 * Same as `ctermid', but return `NULL' when `s' is `NULL' */
__CDECLARE(__ATTR_OUT_OPT(1),char *,__NOTHROW_NCX,ctermid_r,(char *__s),(__s))
#else /* __CRT_HAVE_ctermid_r */
#include <libc/local/unistd/ctermid_r.h>
/* >> ctermid_r(3)
 * Same as `ctermid', but return `NULL' when `s' is `NULL' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ctermid_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT_OPT(1) char *__NOTHROW_NCX(__LIBCCALL ctermid_r)(char *__s) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ctermid_r))(__s); })
#endif /* !__CRT_HAVE_ctermid_r */
#endif /* !__ctermid_r_defined */
#endif /* __USE_REENTRANT || __USE_SOLARIS */


#ifdef __CRT_HAVE_sysconf
/* >> sysconf(2)
 * @param: name: One of `_SC_*' from <asm/crt/confname.h>
 * Return   a   system    configuration   value    `name'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] `name'  refers to a maximum or minimum
 *                                 limit, and that limit is indeterminate
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
__CDECLARE(__ATTR_WUNUSED,__LONGPTR_TYPE__,__NOTHROW_RPC,sysconf,(__STDC_INT_AS_UINT_T __name),(__name))
#elif defined(__CRT_HAVE___sysconf)
/* >> sysconf(2)
 * @param: name: One of `_SC_*' from <asm/crt/confname.h>
 * Return   a   system    configuration   value    `name'
 * return: * : The configuration limit associated with `name' for `path'
 * return: -1: [errno=<unchanged>] `name'  refers to a maximum or minimum
 *                                 limit, and that limit is indeterminate
 * return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option */
__CREDIRECT(__ATTR_WUNUSED,__LONGPTR_TYPE__,__NOTHROW_RPC,sysconf,(__STDC_INT_AS_UINT_T __name),__sysconf,(__name))
#endif /* ... */


#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_POSIX))
#if !defined(F_ULOCK) && defined(__F_ULOCK)
#define F_ULOCK __F_ULOCK /* Unlock a previously locked region. */
#endif /* !F_ULOCK && __F_ULOCK */
#if !defined(F_LOCK) && defined(__F_LOCK)
#define F_LOCK  __F_LOCK  /* Lock a region for exclusive use. */
#endif /* !F_LOCK && __F_LOCK */
#if !defined(F_TLOCK) && defined(__F_TLOCK)
#define F_TLOCK __F_TLOCK /* Test and lock a region for exclusive use. */
#endif /* !F_TLOCK && __F_TLOCK */
#if !defined(F_TEST) && defined(__F_TEST)
#define F_TEST  __F_TEST  /* Test a region for other processes locks. */
#endif /* !F_TEST && __F_TEST */
#ifndef __lockf_defined
#define __lockf_defined
#if defined(__CRT_HAVE_lockf) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CDECLARE(,int,__NOTHROW_RPC,lockf,(__fd_t __fd, __STDC_INT_AS_UINT_T __cmd, __PIO_OFFSET __length),(__fd,__cmd,__length))
#elif defined(__CRT_HAVE__locking) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(,int,__NOTHROW_RPC,lockf,(__fd_t __fd, __STDC_INT_AS_UINT_T __cmd, __PIO_OFFSET __length),_locking,(__fd,__cmd,__length))
#elif defined(__CRT_HAVE_lockf64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(,int,__NOTHROW_RPC,lockf,(__fd_t __fd, __STDC_INT_AS_UINT_T __cmd, __PIO_OFFSET __length),lockf64,(__fd,__cmd,__length))
#elif defined(__CRT_HAVE_lockf64) || defined(__CRT_HAVE_lockf) || defined(__CRT_HAVE_locking) || defined(__CRT_HAVE__locking)
#include <libc/local/fcntl/lockf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(lockf, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL lockf)(__fd_t __fd, __STDC_INT_AS_UINT_T __cmd, __PIO_OFFSET __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lockf))(__fd, __cmd, __length); })
#else /* ... */
#undef __lockf_defined
#endif /* !... */
#endif /* !__lockf_defined */
#ifdef __USE_LARGEFILE64
#ifndef __lockf64_defined
#define __lockf64_defined
#if defined(__CRT_HAVE_lockf) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(,int,__NOTHROW_RPC,lockf64,(__fd_t __fd, __STDC_INT_AS_UINT_T __cmd, __PIO_OFFSET64 __length),lockf,(__fd,__cmd,__length))
#elif defined(__CRT_HAVE_lockf64)
__CDECLARE(,int,__NOTHROW_RPC,lockf64,(__fd_t __fd, __STDC_INT_AS_UINT_T __cmd, __PIO_OFFSET64 __length),(__fd,__cmd,__length))
#elif defined(__CRT_HAVE_lockf) || defined(__CRT_HAVE_locking) || defined(__CRT_HAVE__locking)
#include <libc/local/fcntl/lockf64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(lockf64, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL lockf64)(__fd_t __fd, __STDC_INT_AS_UINT_T __cmd, __PIO_OFFSET64 __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lockf64))(__fd, __cmd, __length); })
#else /* ... */
#undef __lockf64_defined
#endif /* !... */
#endif /* !__lockf64_defined */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_POSIX) */


#if defined(__USE_GNU) && !defined(__NO_XBLOCK)
#ifdef __COMPILER_HAVE_TYPEOF
#define TEMP_FAILURE_RETRY(expression)                           \
	__XBLOCK({                                                   \
		__typeof__(expression) __tfr_result;                     \
		do {                                                     \
			__tfr_result = (expression);                         \
		} while (__tfr_result == (__typeof__(__tfr_result))-1 && \
		         errno == EINTR);                                \
		__XRETURN __tfr_result;                                  \
	})
#else /* __COMPILER_HAVE_TYPEOF */
#define TEMP_FAILURE_RETRY(expression)                   \
	__XBLOCK({                                           \
		long int __tfr_result;                           \
		do {                                             \
			__tfr_result = (long int)(expression);       \
		} while (__tfr_result == -1L && errno == EINTR); \
		__XRETURN __tfr_result;                          \
	})
#endif /* !__COMPILER_HAVE_TYPEOF */
#endif /* __USE_GNU && !__NO_XBLOCK */


#ifdef __USE_BSD
#ifndef __closefrom_defined
#define __closefrom_defined
#ifdef __CRT_HAVE_closefrom
/* >> closefrom(2)
 * Close all file descriptors with indices `>= lowfd' (s.a. `fcntl(F_CLOSEM)') */
__CDECLARE_VOID(,__NOTHROW_NCX,closefrom,(__fd_t __lowfd),(__lowfd))
#else /* __CRT_HAVE_closefrom */
#include <asm/os/fcntl.h>
#if ((defined(__CRT_HAVE_fcntl) || defined(__CRT_HAVE___fcntl) || defined(__CRT_HAVE___libc_fcntl)) && defined(__F_CLOSEM)) || defined(__CRT_HAVE_close_range)
#include <libc/local/unistd/closefrom.h>
/* >> closefrom(2)
 * Close all file descriptors with indices `>= lowfd' (s.a. `fcntl(F_CLOSEM)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(closefrom, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL closefrom)(__fd_t __lowfd) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(closefrom))(__lowfd); })
#else /* ((__CRT_HAVE_fcntl || __CRT_HAVE___fcntl || __CRT_HAVE___libc_fcntl) && __F_CLOSEM) || __CRT_HAVE_close_range */
#undef __closefrom_defined
#endif /* ((!__CRT_HAVE_fcntl && !__CRT_HAVE___fcntl && !__CRT_HAVE___libc_fcntl) || !__F_CLOSEM) && !__CRT_HAVE_close_range */
#endif /* !__CRT_HAVE_closefrom */
#endif /* !__closefrom_defined */
#if !defined(__close_range_defined) && defined(__CRT_HAVE_close_range)
#define __close_range_defined
/* >> close_range(2)
 * Close all files handles `>= minfd && <= maxfd' (but see `flags')
 * @param: flags: Set of `0 | CLOSE_RANGE_UNSHARE | CLOSE_RANGE_CLOEXEC'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(,int,__NOTHROW_NCX,close_range,(unsigned int __minfd, unsigned int __maxfd, unsigned int __flags),(__minfd,__maxfd,__flags))
#endif /* !__close_range_defined && __CRT_HAVE_close_range */
#ifndef __issetugid_defined
#define __issetugid_defined
#ifdef __CRT_HAVE_issetugid
/* >> issetugid(3)
 * Check if the calling program is running under setuid-mode
 * Hint: simply returns the value of `__libc_enable_secure(3)'. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,issetugid,(void),())
#else /* __CRT_HAVE_issetugid */
#include <libc/template/__libc_enable_secure.h>
#ifdef __LOCAL___libc_enable_secure
#include <libc/local/unistd/issetugid.h>
/* >> issetugid(3)
 * Check if the calling program is running under setuid-mode
 * Hint: simply returns the value of `__libc_enable_secure(3)'. */
__NAMESPACE_LOCAL_USING_OR_IMPL(issetugid, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL issetugid)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(issetugid))(); })
#else /* __LOCAL___libc_enable_secure */
#undef __issetugid_defined
#endif /* !__LOCAL___libc_enable_secure */
#endif /* !__CRT_HAVE_issetugid */
#endif /* !__issetugid_defined */
#endif /* __USE_BSD */

#if defined(__USE_SOLARIS) || defined(__USE_NETBSD)
#ifdef __CRT_HAVE_fchroot
/* >> fchroot(2)
 * Change the root directory to  `fd'. If `fd' was opened  before a prior call to  `chroot()',
 * and referrs to  a directory,  then this function  can be  used to escape  a chroot()  jail.
 * No special permissions  are required to  use this function,  since a malicious  application
 * could achieve the same behavior by use of `*at' system calls, using `fd' as `dfd' argument. */
__CDECLARE(,int,__NOTHROW_NCX,fchroot,(__fd_t __fd),(__fd))
#else /* __CRT_HAVE_fchroot */
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_dup2) || defined(__CRT_HAVE__dup2) || defined(__CRT_HAVE___dup2) || defined(__CRT_HAVE___libc_dup2)) && defined(__AT_FDROOT)
#include <libc/local/unistd/fchroot.h>
/* >> fchroot(2)
 * Change the root directory to  `fd'. If `fd' was opened  before a prior call to  `chroot()',
 * and referrs to  a directory,  then this function  can be  used to escape  a chroot()  jail.
 * No special permissions  are required to  use this function,  since a malicious  application
 * could achieve the same behavior by use of `*at' system calls, using `fd' as `dfd' argument. */
__NAMESPACE_LOCAL_USING_OR_IMPL(fchroot, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL fchroot)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fchroot))(__fd); })
#endif /* (__CRT_HAVE_dup2 || __CRT_HAVE__dup2 || __CRT_HAVE___dup2 || __CRT_HAVE___libc_dup2) && __AT_FDROOT */
#endif /* !__CRT_HAVE_fchroot */
#if !defined(__rresvport_af_defined) && defined(__CRT_HAVE_rresvport_af)
#define __rresvport_af_defined
/* This is the equivalent function where the protocol can be selected
 * and which therefore can be used for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE(,int,__NOTHROW_RPC,rresvport_af,(int *__alport, __UINT16_TYPE__ __af),(__alport,__af))
#endif /* !__rresvport_af_defined && __CRT_HAVE_rresvport_af */
#endif /* __USE_SOLARIS || __USE_NETBSD */

#ifdef __USE_SOLARIS
#if !defined(__fattach_defined) && defined(__CRT_HAVE_fattach)
#define __fattach_defined
__CDECLARE(__ATTR_IN(2),int,__NOTHROW_RPC_KOS,fattach,(__fd_t __fd, char const *__restrict __path),(__fd,__path))
#endif /* !__fattach_defined && __CRT_HAVE_fattach */
#if !defined(__fdetach_defined) && defined(__CRT_HAVE_fdetach)
#define __fdetach_defined
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC_KOS,fdetach,(char const *__restrict __path),(__path))
#endif /* !__fdetach_defined && __CRT_HAVE_fdetach */
#ifndef __ioctl_defined
#define __ioctl_defined
#ifdef __CRT_HAVE_ioctl
/* >> ioctl(2)
 * Perform the  I/O control  operation specified  by `request'  on  `fd'.
 * Many I/O  control operations  except  an additional  argument,  though
 * this argument's type and meaning  depends on `REQUEST'. If used,  it's
 * usually either a pointer to a larger argument structure, or an integer
 * that fits into a single register.
 * @return: * : The return value depends on the given `request'.
 * @return: 0 : A zero return-value usually indicates success.
 * @return: -1: All ioctl operations use this to indicate error (s.a. `errno') */
__LIBC __STDC_INT_AS_SSIZE_T __NOTHROW_RPC(__VLIBCCALL ioctl)(__fd_t __fd, __ioctl_t __request, ...) __CASMNAME_SAME("ioctl");
#elif defined(__CRT_HAVE___ioctl)
/* >> ioctl(2)
 * Perform the  I/O control  operation specified  by `request'  on  `fd'.
 * Many I/O  control operations  except  an additional  argument,  though
 * this argument's type and meaning  depends on `REQUEST'. If used,  it's
 * usually either a pointer to a larger argument structure, or an integer
 * that fits into a single register.
 * @return: * : The return value depends on the given `request'.
 * @return: 0 : A zero return-value usually indicates success.
 * @return: -1: All ioctl operations use this to indicate error (s.a. `errno') */
__CVREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,ioctl,(__fd_t __fd, __ioctl_t __request),__ioctl,(__fd,__request),__request,1,(void *))
#elif defined(__CRT_HAVE___libc_ioctl)
/* >> ioctl(2)
 * Perform the  I/O control  operation specified  by `request'  on  `fd'.
 * Many I/O  control operations  except  an additional  argument,  though
 * this argument's type and meaning  depends on `REQUEST'. If used,  it's
 * usually either a pointer to a larger argument structure, or an integer
 * that fits into a single register.
 * @return: * : The return value depends on the given `request'.
 * @return: 0 : A zero return-value usually indicates success.
 * @return: -1: All ioctl operations use this to indicate error (s.a. `errno') */
__CVREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,ioctl,(__fd_t __fd, __ioctl_t __request),__libc_ioctl,(__fd,__request),__request,1,(void *))
#else /* ... */
#undef __ioctl_defined
#endif /* !... */
#endif /* !__ioctl_defined */
#if !defined(__rexec_af_defined) && defined(__CRT_HAVE_rexec_af)
#define __rexec_af_defined
/* This is the equivalent function where the protocol can be selected
 * and which therefore can be used for IPv6.
 * This function is not part of POSIX and therefore no official
 * cancellation point */
__CDECLARE(,int,__NOTHROW_RPC,rexec_af,(char **__restrict __ahost, int __rport, char const *__restrict __name, char const *__restrict __pass, char const *__restrict __cmd, int *__restrict __fd2p, __UINT16_TYPE__ __af),(__ahost,__rport,__name,__pass,__cmd,__fd2p,__af))
#endif /* !__rexec_af_defined && __CRT_HAVE_rexec_af */
#ifndef __stime_defined
#define __stime_defined
#if defined(__CRT_HAVE_stime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> stime(2), stime64(2)
 * Set the system time to `*when'. This call is restricted to the superuser */
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_NCX,stime,(__time_t const *__when),(__when))
#elif defined(__CRT_HAVE___stime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> stime(2), stime64(2)
 * Set the system time to `*when'. This call is restricted to the superuser */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_NCX,stime,(__time_t const *__when),__stime,(__when))
#elif defined(__CRT_HAVE___libc_stime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> stime(2), stime64(2)
 * Set the system time to `*when'. This call is restricted to the superuser */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_NCX,stime,(__time_t const *__when),__libc_stime,(__when))
#elif defined(__CRT_HAVE_stime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> stime(2), stime64(2)
 * Set the system time to `*when'. This call is restricted to the superuser */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_NCX,stime,(__time_t const *__when),stime64,(__when))
#elif defined(__CRT_HAVE_stime64) || defined(__CRT_HAVE_stime) || defined(__CRT_HAVE___stime) || defined(__CRT_HAVE___libc_stime)
#include <libc/local/time/stime.h>
/* >> stime(2), stime64(2)
 * Set the system time to `*when'. This call is restricted to the superuser */
__NAMESPACE_LOCAL_USING_OR_IMPL(stime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL stime)(__time_t const *__when) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stime))(__when); })
#else /* ... */
#undef __stime_defined
#endif /* !... */
#endif /* !__stime_defined */
#ifndef __tell_defined
#define __tell_defined
#if defined(__CRT_HAVE_tell) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__CDECLARE(__ATTR_WUNUSED,__off_t,__NOTHROW_NCX,tell,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE__tell) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__CREDIRECT(__ATTR_WUNUSED,__off_t,__NOTHROW_NCX,tell,(__fd_t __fd),_tell,(__fd))
#elif defined(__CRT_HAVE_tell64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__CREDIRECT(__ATTR_WUNUSED,__off_t,__NOTHROW_NCX,tell,(__fd_t __fd),tell64,(__fd))
#elif defined(__CRT_HAVE__telli64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__CREDIRECT(__ATTR_WUNUSED,__off_t,__NOTHROW_NCX,tell,(__fd_t __fd),_telli64,(__fd))
#elif (defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)) && defined(__SEEK_CUR)
#include <libc/local/unistd/tell.h>
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(tell, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __off_t __NOTHROW_NCX(__LIBCCALL tell)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tell))(__fd); })
#else /* ... */
#undef __tell_defined
#endif /* !... */
#endif /* !__tell_defined */
#ifdef __CRT_HAVE_sched_yield
/* >> thrd_yield(3)
 * Yield execution to another thread (s.a. `pthread_yield(3)') */
__CREDIRECT_VOID(,__NOTHROW,yield,(void),sched_yield,())
#elif defined(__CRT_HAVE_thrd_yield)
/* >> thrd_yield(3)
 * Yield execution to another thread (s.a. `pthread_yield(3)') */
__CREDIRECT_VOID(,__NOTHROW,yield,(void),thrd_yield,())
#elif defined(__CRT_HAVE_pthread_yield)
/* >> thrd_yield(3)
 * Yield execution to another thread (s.a. `pthread_yield(3)') */
__CREDIRECT_VOID(,__NOTHROW,yield,(void),pthread_yield,())
#elif defined(__CRT_HAVE___sched_yield)
/* >> thrd_yield(3)
 * Yield execution to another thread (s.a. `pthread_yield(3)') */
__CREDIRECT_VOID(,__NOTHROW,yield,(void),__sched_yield,())
#elif defined(__CRT_HAVE___libc_sched_yield)
/* >> thrd_yield(3)
 * Yield execution to another thread (s.a. `pthread_yield(3)') */
__CREDIRECT_VOID(,__NOTHROW,yield,(void),__libc_sched_yield,())
#elif defined(__CRT_HAVE_yield)
/* >> thrd_yield(3)
 * Yield execution to another thread (s.a. `pthread_yield(3)') */
__CDECLARE_VOID(,__NOTHROW,yield,(void),())
#elif defined(__CRT_HAVE_thr_yield)
/* >> thrd_yield(3)
 * Yield execution to another thread (s.a. `pthread_yield(3)') */
__CREDIRECT_VOID(,__NOTHROW,yield,(void),thr_yield,())
#elif defined(__CRT_HAVE_cthread_yield)
/* >> thrd_yield(3)
 * Yield execution to another thread (s.a. `pthread_yield(3)') */
__CREDIRECT_VOID(,__NOTHROW,yield,(void),cthread_yield,())
#endif /* ... */
#ifdef __CRT_HAVE_resolvepath
/* >> resolvepath(3)
 * Similar  to  `frealpathat(2)'  (though  use  the  later  for  more   options)
 * Also note that this function appears to  have a weird rule (which KOS  simply
 * ignores)  that is related  to this function not  writing more than `PATH_MAX'
 * bytes to `buf'. (Why??? I mean: The whole point of having a `buflen' argument
 * is to be able to handle names of arbitrary lengths)
 * Additionally, the online docs don't mention what happens when `buflen' is  too
 * small, so I guess I can just make up what's supposed to happen, and I say that
 * the function will set errno=ERANGE and return -1
 * @return: * : Used buffer size (possibly including a NUL-byte, but maybe not)
 * @return: -1: Error. (s.a. `errno') */
__CDECLARE(__ATTR_IN(1) __ATTR_OUTS(2, 3),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,resolvepath,(char const *__filename, char *__resolved, __SIZE_TYPE__ __buflen),(__filename,__resolved,__buflen))
#else /* __CRT_HAVE_resolvepath */
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_frealpathat) && defined(__AT_FDCWD)
#include <libc/local/unistd/resolvepath.h>
/* >> resolvepath(3)
 * Similar  to  `frealpathat(2)'  (though  use  the  later  for  more   options)
 * Also note that this function appears to  have a weird rule (which KOS  simply
 * ignores)  that is related  to this function not  writing more than `PATH_MAX'
 * bytes to `buf'. (Why??? I mean: The whole point of having a `buflen' argument
 * is to be able to handle names of arbitrary lengths)
 * Additionally, the online docs don't mention what happens when `buflen' is  too
 * small, so I guess I can just make up what's supposed to happen, and I say that
 * the function will set errno=ERANGE and return -1
 * @return: * : Used buffer size (possibly including a NUL-byte, but maybe not)
 * @return: -1: Error. (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(resolvepath, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUTS(2, 3) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL resolvepath)(char const *__filename, char *__resolved, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(resolvepath))(__filename, __resolved, __buflen); })
#endif /* __CRT_HAVE_frealpathat && __AT_FDCWD */
#endif /* !__CRT_HAVE_resolvepath */
#ifndef __tell_defined
#define __tell_defined
#if defined(__CRT_HAVE_tell) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__CDECLARE(__ATTR_WUNUSED,__off_t,__NOTHROW_NCX,tell,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE__tell) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__CREDIRECT(__ATTR_WUNUSED,__off_t,__NOTHROW_NCX,tell,(__fd_t __fd),_tell,(__fd))
#elif defined(__CRT_HAVE_tell64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__CREDIRECT(__ATTR_WUNUSED,__off_t,__NOTHROW_NCX,tell,(__fd_t __fd),tell64,(__fd))
#elif defined(__CRT_HAVE__telli64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__CREDIRECT(__ATTR_WUNUSED,__off_t,__NOTHROW_NCX,tell,(__fd_t __fd),_telli64,(__fd))
#elif (defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)) && defined(__SEEK_CUR)
#include <libc/local/unistd/tell.h>
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(tell, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __off_t __NOTHROW_NCX(__LIBCCALL tell)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tell))(__fd); })
#else /* ... */
#undef __tell_defined
#endif /* !... */
#endif /* !__tell_defined */
#ifdef __USE_LARGEFILE64
#ifndef __tell64_defined
#define __tell64_defined
#if defined(__CRT_HAVE_tell) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__CREDIRECT(__ATTR_WUNUSED,__off64_t,__NOTHROW_NCX,tell64,(__fd_t __fd),tell,(__fd))
#elif defined(__CRT_HAVE_tell64)
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__CDECLARE(__ATTR_WUNUSED,__off64_t,__NOTHROW_NCX,tell64,(__fd_t __fd),(__fd))
#elif defined(__CRT_HAVE__telli64)
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__CREDIRECT(__ATTR_WUNUSED,__off64_t,__NOTHROW_NCX,tell64,(__fd_t __fd),_telli64,(__fd))
#elif (defined(__CRT_HAVE_lseek64) || defined(__CRT_HAVE__lseeki64) || defined(__CRT_HAVE_llseek) || defined(__CRT_HAVE___llseek) || defined(__CRT_HAVE_lseek) || defined(__CRT_HAVE__lseek) || defined(__CRT_HAVE___lseek) || defined(__CRT_HAVE___libc_lseek)) && defined(__SEEK_CUR)
#include <libc/local/unistd/tell64.h>
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(tell64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __off64_t __NOTHROW_NCX(__LIBCCALL tell64)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tell64))(__fd); })
#else /* ... */
#undef __tell64_defined
#endif /* !... */
#endif /* !__tell64_defined */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_SOLARIS */

__SYSDECL_END
#endif /* __CC__ */

#if defined(__USE_SOLARIS) || defined(__USE_NETBSD)
#include <getopt.h>
#endif /* __USE_SOLARIS || __USE_NETBSD */

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
