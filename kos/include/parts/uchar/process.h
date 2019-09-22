/* HASH CRC-32:0xfe0f5209 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _PARTS_UCHAR_PROCESS_H
#define _PARTS_UCHAR_PROCESS_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <process.h>
#include <uchar.h>
#include <bits/types.h>

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __T16ARGV
#ifdef __USE_DOS
#   define __T16ARGV char16_t const *const *__restrict ___argv
#   define __T16ENVP char16_t const *const *__restrict ___envp
#else /* __USE_DOS */
#   define __T16ARGV char16_t *const ___argv[__restrict_arr]
#   define __T16ENVP char16_t *const ___envp[__restrict_arr]
#endif /* !__USE_DOS */
#endif /* !__T16ARGV */
#ifndef __T32ARGV
#ifdef __USE_DOS
#   define __T32ARGV char32_t const *const *__restrict ___argv
#   define __T32ENVP char32_t const *const *__restrict ___envp
#else /* __USE_DOS */
#   define __T32ARGV char32_t *const ___argv[__restrict_arr]
#   define __T32ENVP char32_t *const ___envp[__restrict_arr]
#endif /* !__USE_DOS */
#endif /* !__T32ARGV */
#if defined(__CRT_HAVE_wexecv) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2)) __ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16execv,(char16_t const *__restrict __path, __T16ARGV),wexecv,(__path, ___argv))
#elif defined(__CRT_HAVE__wexecv) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2)) __ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16execv,(char16_t const *__restrict __path, __T16ARGV),_wexecv,(__path, ___argv))
#elif defined(__CRT_HAVE_DOS$_wexecv)
__CREDIRECT_DOS(__ATTR_NONNULL((2)) __ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16execv,(char16_t const *__restrict __path, __T16ARGV),_wexecv,(__path, ___argv))
#elif defined(__CRT_HAVE_DOS$_wexecv)
__CREDIRECT_DOS(__ATTR_NONNULL((2)) __ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16execv,(char16_t const *__restrict __path, __T16ARGV),_wexecv,(__path, ___argv))
#endif /* c16execv... */
#if defined(__CRT_HAVE_wexecv) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)) __ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c32execv,(char32_t const *__restrict __path, __T32ARGV),wexecv,(__path, ___argv))
#elif defined(__CRT_HAVE__wexecv) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)) __ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c32execv,(char32_t const *__restrict __path, __T32ARGV),_wexecv,(__path, ___argv))
#endif /* c32execv... */
#if defined(__CRT_HAVE_wexecve) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c16execve,(char16_t const *__restrict __path, __T16ARGV, __T16ENVP),wexecve,(__path, ___argv, ___envp))
#elif defined(__CRT_HAVE__wexecve) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c16execve,(char16_t const *__restrict __path, __T16ARGV, __T16ENVP),_wexecve,(__path, ___argv, ___envp))
#elif defined(__CRT_HAVE_DOS$_wexecve)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c16execve,(char16_t const *__restrict __path, __T16ARGV, __T16ENVP),_wexecve,(__path, ___argv, ___envp))
#elif defined(__CRT_HAVE_DOS$_wexecve)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c16execve,(char16_t const *__restrict __path, __T16ARGV, __T16ENVP),_wexecve,(__path, ___argv, ___envp))
#endif /* c16execve... */
#if defined(__CRT_HAVE_wexecve) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c32execve,(char32_t const *__restrict __path, __T32ARGV, __T32ENVP),wexecve,(__path, ___argv, ___envp))
#elif defined(__CRT_HAVE__wexecve) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c32execve,(char32_t const *__restrict __path, __T32ARGV, __T32ENVP),_wexecve,(__path, ___argv, ___envp))
#endif /* c32execve... */
#if defined(__CRT_HAVE_wexecvp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2)) __ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16execvp,(char16_t const *__restrict __path, __T16ARGV),wexecvp,(__path, ___argv))
#elif defined(__CRT_HAVE__wexecvp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2)) __ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16execvp,(char16_t const *__restrict __path, __T16ARGV),_wexecvp,(__path, ___argv))
#elif defined(__CRT_HAVE_DOS$_wexecvp)
__CREDIRECT_DOS(__ATTR_NONNULL((2)) __ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16execvp,(char16_t const *__restrict __path, __T16ARGV),_wexecvp,(__path, ___argv))
#elif defined(__CRT_HAVE_DOS$_wexecvp)
__CREDIRECT_DOS(__ATTR_NONNULL((2)) __ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16execvp,(char16_t const *__restrict __path, __T16ARGV),_wexecvp,(__path, ___argv))
#endif /* c16execvp... */
#if defined(__CRT_HAVE_wexecvp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)) __ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c32execvp,(char32_t const *__restrict __path, __T32ARGV),wexecvp,(__path, ___argv))
#elif defined(__CRT_HAVE__wexecvp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2)) __ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c32execvp,(char32_t const *__restrict __path, __T32ARGV),_wexecvp,(__path, ___argv))
#endif /* c32execvp... */
#if defined(__CRT_HAVE_wexecvpe) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c16execvpe,(char16_t const *__restrict __path, __T16ARGV, __T16ENVP),wexecvpe,(__path, ___argv, ___envp))
#elif defined(__CRT_HAVE__wexecvpe) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c16execvpe,(char16_t const *__restrict __path, __T16ARGV, __T16ENVP),_wexecvpe,(__path, ___argv, ___envp))
#elif defined(__CRT_HAVE_DOS$_wexecvpe)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c16execvpe,(char16_t const *__restrict __path, __T16ARGV, __T16ENVP),_wexecvpe,(__path, ___argv, ___envp))
#elif defined(__CRT_HAVE_DOS$_wexecvpe)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c16execvpe,(char16_t const *__restrict __path, __T16ARGV, __T16ENVP),_wexecvpe,(__path, ___argv, ___envp))
#endif /* c16execvpe... */
#if defined(__CRT_HAVE_wexecvpe) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c32execvpe,(char32_t const *__restrict __path, __T32ARGV, __T32ENVP),wexecvpe,(__path, ___argv, ___envp))
#elif defined(__CRT_HAVE__wexecvpe) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c32execvpe,(char32_t const *__restrict __path, __T32ARGV, __T32ENVP),_wexecvpe,(__path, ___argv, ___envp))
#endif /* c32execvpe... */
#if defined(__CRT_HAVE_wexecl) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL c16execl)(char16_t const *__restrict __path, char16_t const *__args, ... /*, (char16_t *)NULL*/) __CASMNAME("wexecl");
#elif defined(__CRT_HAVE__wexecl) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL c16execl)(char16_t const *__restrict __path, char16_t const *__args, ... /*, (char16_t *)NULL*/) __CASMNAME("_wexecl");
#elif defined(__CRT_HAVE_DOS$_wexecl) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL c16execl)(char16_t const *__restrict __path, char16_t const *__args, ... /*, (char16_t *)NULL*/) __CASMNAME_DOS("_wexecl");
#elif (defined(__CRT_HAVE_wexecv) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE__wexecv) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$_wexecv) || defined(__CRT_HAVE_DOS$_wexecv)
#include <local/parts.uchar.process/c16execl.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c16execl)
#else /* __cplusplus */
#define c16execl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16execl))
#endif /* !__cplusplus */
#endif /* c16execl... */
#if defined(__CRT_HAVE_wexecl) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL c32execl)(char32_t const *__restrict __path, char32_t const *__args, ... /*, (char32_t *)NULL*/) __CASMNAME("wexecl");
#elif defined(__CRT_HAVE__wexecl) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL c32execl)(char32_t const *__restrict __path, char32_t const *__args, ... /*, (char32_t *)NULL*/) __CASMNAME("_wexecl");
#elif (defined(__CRT_HAVE_wexecv) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE__wexecv) && __SIZEOF_WCHAR_T__ == 4)
#include <local/parts.uchar.process/c32execl.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c32execl)
#else /* __cplusplus */
#define c32execl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32execl))
#endif /* !__cplusplus */
#endif /* c32execl... */
#if defined(__CRT_HAVE_wexeclp) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL c16execlp)(char16_t const *__restrict __file, char16_t const *__args, ... /*, (char16_t *)NULL*/) __CASMNAME("wexeclp");
#elif defined(__CRT_HAVE__wexeclp) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL c16execlp)(char16_t const *__restrict __file, char16_t const *__args, ... /*, (char16_t *)NULL*/) __CASMNAME("_wexeclp");
#elif defined(__CRT_HAVE_DOS$_wexeclp) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL c16execlp)(char16_t const *__restrict __file, char16_t const *__args, ... /*, (char16_t *)NULL*/) __CASMNAME_DOS("_wexeclp");
#elif (defined(__CRT_HAVE_wexecvp) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE__wexecvp) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$_wexecvp) || defined(__CRT_HAVE_DOS$_wexecvp)
#include <local/parts.uchar.process/c16execlp.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c16execlp)
#else /* __cplusplus */
#define c16execlp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16execlp))
#endif /* !__cplusplus */
#endif /* c16execlp... */
#if defined(__CRT_HAVE_wexeclp) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL c32execlp)(char32_t const *__restrict __file, char32_t const *__args, ... /*, (char32_t *)NULL*/) __CASMNAME("wexeclp");
#elif defined(__CRT_HAVE__wexeclp) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL c32execlp)(char32_t const *__restrict __file, char32_t const *__args, ... /*, (char32_t *)NULL*/) __CASMNAME("_wexeclp");
#elif (defined(__CRT_HAVE_wexecvp) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE__wexecvp) && __SIZEOF_WCHAR_T__ == 4)
#include <local/parts.uchar.process/c32execlp.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c32execlp)
#else /* __cplusplus */
#define c32execlp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32execlp))
#endif /* !__cplusplus */
#endif /* c32execlp... */
#if defined(__CRT_HAVE_wexecle) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL c16execle)(char16_t const *__restrict __path, char16_t const *__args, ... /*, (char16_t *)NULL, char16_t **environ*/) __CASMNAME("wexecle");
#elif defined(__CRT_HAVE__wexecle) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL c16execle)(char16_t const *__restrict __path, char16_t const *__args, ... /*, (char16_t *)NULL, char16_t **environ*/) __CASMNAME("_wexecle");
#elif defined(__CRT_HAVE_DOS$_wexecle) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL c16execle)(char16_t const *__restrict __path, char16_t const *__args, ... /*, (char16_t *)NULL, char16_t **environ*/) __CASMNAME_DOS("_wexecle");
#elif (defined(__CRT_HAVE_wexecve) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE__wexecve) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$_wexecve) || defined(__CRT_HAVE_DOS$_wexecve)
#include <local/parts.uchar.process/c16execle.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c16execle)
#else /* __cplusplus */
#define c16execle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16execle))
#endif /* !__cplusplus */
#endif /* c16execle... */
#if defined(__CRT_HAVE_wexecle) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL c32execle)(char32_t const *__restrict __path, char32_t const *__args, ... /*, (char32_t *)NULL, char32_t **environ*/) __CASMNAME("wexecle");
#elif defined(__CRT_HAVE__wexecle) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL c32execle)(char32_t const *__restrict __path, char32_t const *__args, ... /*, (char32_t *)NULL, char32_t **environ*/) __CASMNAME("_wexecle");
#elif (defined(__CRT_HAVE_wexecve) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE__wexecve) && __SIZEOF_WCHAR_T__ == 4)
#include <local/parts.uchar.process/c32execle.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c32execle)
#else /* __cplusplus */
#define c32execle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32execle))
#endif /* !__cplusplus */
#endif /* c32execle... */
#if defined(__CRT_HAVE_wexeclpe) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL c16execlpe)(char16_t const *__restrict __file, char16_t const *__args, ... /*, (char16_t *)NULL, char16_t **environ*/) __CASMNAME("wexeclpe");
#elif defined(__CRT_HAVE__wexeclpe) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL c16execlpe)(char16_t const *__restrict __file, char16_t const *__args, ... /*, (char16_t *)NULL, char16_t **environ*/) __CASMNAME("_wexeclpe");
#elif defined(__CRT_HAVE_DOS$_wexeclpe) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL c16execlpe)(char16_t const *__restrict __file, char16_t const *__args, ... /*, (char16_t *)NULL, char16_t **environ*/) __CASMNAME_DOS("_wexeclpe");
#elif (defined(__CRT_HAVE_wexecvpe) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE__wexecvpe) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$_wexecvpe) || defined(__CRT_HAVE_DOS$_wexecvpe)
#include <local/parts.uchar.process/c16execlpe.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c16execlpe)
#else /* __cplusplus */
#define c16execlpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16execlpe))
#endif /* !__cplusplus */
#endif /* c16execlpe... */
#if defined(__CRT_HAVE_wexeclpe) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL c32execlpe)(char32_t const *__restrict __file, char32_t const *__args, ... /*, (char32_t *)NULL, char32_t **environ*/) __CASMNAME("wexeclpe");
#elif defined(__CRT_HAVE__wexeclpe) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL c32execlpe)(char32_t const *__restrict __file, char32_t const *__args, ... /*, (char32_t *)NULL, char32_t **environ*/) __CASMNAME("_wexeclpe");
#elif (defined(__CRT_HAVE_wexecvpe) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE__wexecvpe) && __SIZEOF_WCHAR_T__ == 4)
#include <local/parts.uchar.process/c32execlpe.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c32execlpe)
#else /* __cplusplus */
#define c32execlpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32execlpe))
#endif /* !__cplusplus */
#endif /* c32execlpe... */
#if defined(__CRT_HAVE_wspawnv) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c16spawnv,(int __mode, char16_t const *__restrict __path, __T16ARGV),wspawnv,(__mode,__path, ___argv))
#elif defined(__CRT_HAVE__wspawnv) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c16spawnv,(int __mode, char16_t const *__restrict __path, __T16ARGV),_wspawnv,(__mode,__path, ___argv))
#elif defined(__CRT_HAVE_DOS$_wspawnv)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c16spawnv,(int __mode, char16_t const *__restrict __path, __T16ARGV),_wspawnv,(__mode,__path, ___argv))
#elif defined(__CRT_HAVE_DOS$_wspawnv)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c16spawnv,(int __mode, char16_t const *__restrict __path, __T16ARGV),_wspawnv,(__mode,__path, ___argv))
#endif /* c16spawnv... */
#if defined(__CRT_HAVE_wspawnv) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c32spawnv,(int __mode, char32_t const *__restrict __path, __T32ARGV),wspawnv,(__mode,__path, ___argv))
#elif defined(__CRT_HAVE__wspawnv) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c32spawnv,(int __mode, char32_t const *__restrict __path, __T32ARGV),_wspawnv,(__mode,__path, ___argv))
#endif /* c32spawnv... */
#if defined(__CRT_HAVE_wspawnve) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)) __ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c16spawnve,(int __mode, char16_t const *__restrict __path, __T16ARGV, __T16ENVP),wspawnve,(__mode,__path, ___argv, ___envp))
#elif defined(__CRT_HAVE__wspawnve) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)) __ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c16spawnve,(int __mode, char16_t const *__restrict __path, __T16ARGV, __T16ENVP),_wspawnve,(__mode,__path, ___argv, ___envp))
#elif defined(__CRT_HAVE_DOS$_wspawnve)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3, 4)) __ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c16spawnve,(int __mode, char16_t const *__restrict __path, __T16ARGV, __T16ENVP),_wspawnve,(__mode,__path, ___argv, ___envp))
#elif defined(__CRT_HAVE_DOS$_wspawnve)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3, 4)) __ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c16spawnve,(int __mode, char16_t const *__restrict __path, __T16ARGV, __T16ENVP),_wspawnve,(__mode,__path, ___argv, ___envp))
#endif /* c16spawnve... */
#if defined(__CRT_HAVE_wspawnve) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)) __ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c32spawnve,(int __mode, char32_t const *__restrict __path, __T32ARGV, __T32ENVP),wspawnve,(__mode,__path, ___argv, ___envp))
#elif defined(__CRT_HAVE__wspawnve) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)) __ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c32spawnve,(int __mode, char32_t const *__restrict __path, __T32ARGV, __T32ENVP),_wspawnve,(__mode,__path, ___argv, ___envp))
#endif /* c32spawnve... */
#if defined(__CRT_HAVE_wspawnvp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c16spawnvp,(int __mode, char16_t const *__restrict __path, __T16ARGV),wspawnvp,(__mode,__path, ___argv))
#elif defined(__CRT_HAVE__wspawnvp) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c16spawnvp,(int __mode, char16_t const *__restrict __path, __T16ARGV),_wspawnvp,(__mode,__path, ___argv))
#elif defined(__CRT_HAVE_DOS$_wspawnvp)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c16spawnvp,(int __mode, char16_t const *__restrict __path, __T16ARGV),_wspawnvp,(__mode,__path, ___argv))
#elif defined(__CRT_HAVE_DOS$_wspawnvp)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c16spawnvp,(int __mode, char16_t const *__restrict __path, __T16ARGV),_wspawnvp,(__mode,__path, ___argv))
#endif /* c16spawnvp... */
#if defined(__CRT_HAVE_wspawnvp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c32spawnvp,(int __mode, char32_t const *__restrict __path, __T32ARGV),wspawnvp,(__mode,__path, ___argv))
#elif defined(__CRT_HAVE__wspawnvp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2, 3)) __ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c32spawnvp,(int __mode, char32_t const *__restrict __path, __T32ARGV),_wspawnvp,(__mode,__path, ___argv))
#endif /* c32spawnvp... */
#if defined(__CRT_HAVE_wspawnvpe) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)) __ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c16spawnvpe,(int __mode, char16_t const *__restrict __path, __T16ARGV, __T16ENVP),wspawnvpe,(__mode,__path, ___argv, ___envp))
#elif defined(__CRT_HAVE__wspawnvpe) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)) __ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c16spawnvpe,(int __mode, char16_t const *__restrict __path, __T16ARGV, __T16ENVP),_wspawnvpe,(__mode,__path, ___argv, ___envp))
#elif defined(__CRT_HAVE_DOS$_wspawnvpe)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3, 4)) __ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c16spawnvpe,(int __mode, char16_t const *__restrict __path, __T16ARGV, __T16ENVP),_wspawnvpe,(__mode,__path, ___argv, ___envp))
#elif defined(__CRT_HAVE_DOS$_wspawnvpe)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3, 4)) __ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c16spawnvpe,(int __mode, char16_t const *__restrict __path, __T16ARGV, __T16ENVP),_wspawnvpe,(__mode,__path, ___argv, ___envp))
#endif /* c16spawnvpe... */
#if defined(__CRT_HAVE_wspawnvpe) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)) __ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c32spawnvpe,(int __mode, char32_t const *__restrict __path, __T32ARGV, __T32ENVP),wspawnvpe,(__mode,__path, ___argv, ___envp))
#elif defined(__CRT_HAVE__wspawnvpe) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)) __ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c32spawnvpe,(int __mode, char32_t const *__restrict __path, __T32ARGV, __T32ENVP),_wspawnvpe,(__mode,__path, ___argv, ___envp))
#endif /* c32spawnvpe... */
#if defined(__CRT_HAVE_wspawnl) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL c16spawnl)(int __mode, char16_t const *__restrict __path, char16_t const *__args, ... /*, (char16_t *)NULL*/) __CASMNAME("wspawnl");
#elif defined(__CRT_HAVE__wspawnl) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL c16spawnl)(int __mode, char16_t const *__restrict __path, char16_t const *__args, ... /*, (char16_t *)NULL*/) __CASMNAME("_wspawnl");
#elif defined(__CRT_HAVE_DOS$_wspawnl) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL c16spawnl)(int __mode, char16_t const *__restrict __path, char16_t const *__args, ... /*, (char16_t *)NULL*/) __CASMNAME_DOS("_wspawnl");
#elif (defined(__CRT_HAVE_wspawnv) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE__wspawnv) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$_wspawnv) || defined(__CRT_HAVE_DOS$_wspawnv)
#include <local/parts.uchar.process/c16spawnl.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c16spawnl)
#else /* __cplusplus */
#define c16spawnl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16spawnl))
#endif /* !__cplusplus */
#endif /* c16spawnl... */
#if defined(__CRT_HAVE_wspawnl) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL c32spawnl)(int __mode, char32_t const *__restrict __path, char32_t const *__args, ... /*, (char32_t *)NULL*/) __CASMNAME("wspawnl");
#elif defined(__CRT_HAVE__wspawnl) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL c32spawnl)(int __mode, char32_t const *__restrict __path, char32_t const *__args, ... /*, (char32_t *)NULL*/) __CASMNAME("_wspawnl");
#elif (defined(__CRT_HAVE_wspawnv) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE__wspawnv) && __SIZEOF_WCHAR_T__ == 4)
#include <local/parts.uchar.process/c32spawnl.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c32spawnl)
#else /* __cplusplus */
#define c32spawnl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32spawnl))
#endif /* !__cplusplus */
#endif /* c32spawnl... */
#if defined(__CRT_HAVE_wspawnlp) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL c16spawnlp)(int __mode, char16_t const *__restrict __file, char16_t const *__args, ... /*, (char16_t *)NULL*/) __CASMNAME("wspawnlp");
#elif defined(__CRT_HAVE__wspawnlp) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL c16spawnlp)(int __mode, char16_t const *__restrict __file, char16_t const *__args, ... /*, (char16_t *)NULL*/) __CASMNAME("_wspawnlp");
#elif defined(__CRT_HAVE_DOS$_wspawnlp) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL c16spawnlp)(int __mode, char16_t const *__restrict __file, char16_t const *__args, ... /*, (char16_t *)NULL*/) __CASMNAME_DOS("_wspawnlp");
#elif (defined(__CRT_HAVE_wspawnvp) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE__wspawnvp) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$_wspawnvp) || defined(__CRT_HAVE_DOS$_wspawnvp)
#include <local/parts.uchar.process/c16spawnlp.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c16spawnlp)
#else /* __cplusplus */
#define c16spawnlp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16spawnlp))
#endif /* !__cplusplus */
#endif /* c16spawnlp... */
#if defined(__CRT_HAVE_wspawnlp) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL c32spawnlp)(int __mode, char32_t const *__restrict __file, char32_t const *__args, ... /*, (char32_t *)NULL*/) __CASMNAME("wspawnlp");
#elif defined(__CRT_HAVE__wspawnlp) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL c32spawnlp)(int __mode, char32_t const *__restrict __file, char32_t const *__args, ... /*, (char32_t *)NULL*/) __CASMNAME("_wspawnlp");
#elif (defined(__CRT_HAVE_wspawnvp) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE__wspawnvp) && __SIZEOF_WCHAR_T__ == 4)
#include <local/parts.uchar.process/c32spawnlp.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c32spawnlp)
#else /* __cplusplus */
#define c32spawnlp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32spawnlp))
#endif /* !__cplusplus */
#endif /* c32spawnlp... */
#if defined(__CRT_HAVE_wspawnle) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL c16spawnle)(int __mode, char16_t const *__restrict __path, char16_t const *__args, ... /*, (char16_t *)NULL, char16_t **environ*/) __CASMNAME("wspawnle");
#elif defined(__CRT_HAVE__wspawnle) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL c16spawnle)(int __mode, char16_t const *__restrict __path, char16_t const *__args, ... /*, (char16_t *)NULL, char16_t **environ*/) __CASMNAME("_wspawnle");
#elif defined(__CRT_HAVE_DOS$_wspawnle) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL c16spawnle)(int __mode, char16_t const *__restrict __path, char16_t const *__args, ... /*, (char16_t *)NULL, char16_t **environ*/) __CASMNAME_DOS("_wspawnle");
#elif (defined(__CRT_HAVE_wspawnve) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE__wspawnve) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$_wspawnve) || defined(__CRT_HAVE_DOS$_wspawnve)
#include <local/parts.uchar.process/c16spawnle.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c16spawnle)
#else /* __cplusplus */
#define c16spawnle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16spawnle))
#endif /* !__cplusplus */
#endif /* c16spawnle... */
#if defined(__CRT_HAVE_wspawnle) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL c32spawnle)(int __mode, char32_t const *__restrict __path, char32_t const *__args, ... /*, (char32_t *)NULL, char32_t **environ*/) __CASMNAME("wspawnle");
#elif defined(__CRT_HAVE__wspawnle) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL c32spawnle)(int __mode, char32_t const *__restrict __path, char32_t const *__args, ... /*, (char32_t *)NULL, char32_t **environ*/) __CASMNAME("_wspawnle");
#elif (defined(__CRT_HAVE_wspawnve) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE__wspawnve) && __SIZEOF_WCHAR_T__ == 4)
#include <local/parts.uchar.process/c32spawnle.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c32spawnle)
#else /* __cplusplus */
#define c32spawnle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32spawnle))
#endif /* !__cplusplus */
#endif /* c32spawnle... */
#if defined(__CRT_HAVE_wspawnlpe) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL c16spawnlpe)(int __mode, char16_t const *__restrict __file, char16_t const *__args, ... /*, (char16_t *)NULL, char16_t **environ*/) __CASMNAME("wspawnlpe");
#elif defined(__CRT_HAVE__wspawnlpe) && (__SIZEOF_WCHAR_T__ == 2) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL c16spawnlpe)(int __mode, char16_t const *__restrict __file, char16_t const *__args, ... /*, (char16_t *)NULL, char16_t **environ*/) __CASMNAME("_wspawnlpe");
#elif defined(__CRT_HAVE_DOS$_wspawnlpe) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL c16spawnlpe)(int __mode, char16_t const *__restrict __file, char16_t const *__args, ... /*, (char16_t *)NULL, char16_t **environ*/) __CASMNAME_DOS("_wspawnlpe");
#elif (defined(__CRT_HAVE_wspawnvpe) && __SIZEOF_WCHAR_T__ == 2) || (defined(__CRT_HAVE__wspawnvpe) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$_wspawnvpe) || defined(__CRT_HAVE_DOS$_wspawnvpe)
#include <local/parts.uchar.process/c16spawnlpe.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c16spawnlpe)
#else /* __cplusplus */
#define c16spawnlpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16spawnlpe))
#endif /* !__cplusplus */
#endif /* c16spawnlpe... */
#if defined(__CRT_HAVE_wspawnlpe) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL c32spawnlpe)(int __mode, char32_t const *__restrict __file, char32_t const *__args, ... /*, (char32_t *)NULL, char32_t **environ*/) __CASMNAME("wspawnlpe");
#elif defined(__CRT_HAVE__wspawnlpe) && (__SIZEOF_WCHAR_T__ == 4) && !defined(__NO_ASMNAME)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL c32spawnlpe)(int __mode, char32_t const *__restrict __file, char32_t const *__args, ... /*, (char32_t *)NULL, char32_t **environ*/) __CASMNAME("_wspawnlpe");
#elif (defined(__CRT_HAVE_wspawnvpe) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE__wspawnvpe) && __SIZEOF_WCHAR_T__ == 4)
#include <local/parts.uchar.process/c32spawnlpe.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c32spawnlpe)
#else /* __cplusplus */
#define c32spawnlpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32spawnlpe))
#endif /* !__cplusplus */
#endif /* c32spawnlpe... */
#if defined(__CRT_HAVE_wsystem) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(,int,__NOTHROW_RPC,c16system,(char16_t const *__cmd),wsystem,(__cmd))
#elif defined(__CRT_HAVE__wsystem) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(,int,__NOTHROW_RPC,c16system,(char16_t const *__cmd),_wsystem,(__cmd))
#elif defined(__CRT_HAVE_DOS$_wsystem)
__CREDIRECT_DOS(,int,__NOTHROW_RPC,c16system,(char16_t const *__cmd),_wsystem,(__cmd))
#elif defined(__CRT_HAVE_DOS$_wsystem)
__CREDIRECT_DOS(,int,__NOTHROW_RPC,c16system,(char16_t const *__cmd),_wsystem,(__cmd))
#endif /* c16system... */
#if defined(__CRT_HAVE_wsystem) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(,int,__NOTHROW_RPC,c32system,(char32_t const *__cmd),wsystem,(__cmd))
#elif defined(__CRT_HAVE__wsystem) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(,int,__NOTHROW_RPC,c32system,(char32_t const *__cmd),_wsystem,(__cmd))
#endif /* c32system... */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PARTS_UCHAR_PROCESS_H */
