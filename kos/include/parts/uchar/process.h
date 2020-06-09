/* HASH CRC-32:0xa25a7895 */
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
#if defined(__CRT_HAVE_wexecv) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__LIBDCALL,c16execv,(char16_t const *__restrict __path, __T16ARGV),wexecv,(__path,))
#elif defined(__CRT_HAVE_DOS$_wexecv)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16execv,(char16_t const *__restrict __path, __T16ARGV),_wexecv,(__path,))
#endif /* ... */
#if defined(__CRT_HAVE_wexecv) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__LIBKCALL,c32execv,(char32_t const *__restrict __path, __T32ARGV),wexecv,(__path,))
#elif defined(__CRT_HAVE_DOS$wexecv)
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c32execv,(char32_t const *__restrict __path, __T32ARGV),wexecv,(__path,))
#endif /* ... */
#if defined(__CRT_HAVE_wexecve) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__LIBDCALL,c16execve,(char16_t const *__restrict __path, __T16ARGV, __T16ENVP),wexecve,(__path,,))
#elif defined(__CRT_HAVE_DOS$_wexecve)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c16execve,(char16_t const *__restrict __path, __T16ARGV, __T16ENVP),_wexecve,(__path,,))
#endif /* ... */
#if defined(__CRT_HAVE_wexecve) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__LIBKCALL,c32execve,(char32_t const *__restrict __path, __T32ARGV, __T32ENVP),wexecve,(__path,,))
#elif defined(__CRT_HAVE_DOS$wexecve)
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c32execve,(char32_t const *__restrict __path, __T32ARGV, __T32ENVP),wexecve,(__path,,))
#endif /* ... */
#if defined(__CRT_HAVE_wexecvp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__LIBDCALL,c16execvp,(char16_t const *__restrict __file, __T16ARGV),wexecvp,(__file,))
#elif defined(__CRT_HAVE_DOS$_wexecvp)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16execvp,(char16_t const *__restrict __file, __T16ARGV),_wexecvp,(__file,))
#endif /* ... */
#if defined(__CRT_HAVE_wexecvp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__LIBKCALL,c32execvp,(char32_t const *__restrict __file, __T32ARGV),wexecvp,(__file,))
#elif defined(__CRT_HAVE_DOS$wexecvp)
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c32execvp,(char32_t const *__restrict __file, __T32ARGV),wexecvp,(__file,))
#endif /* ... */
#if defined(__CRT_HAVE_wexecvpe) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__LIBDCALL,c16execvpe,(char16_t const *__restrict __file, __T16ARGV, __T16ENVP),wexecvpe,(__file,,))
#elif defined(__CRT_HAVE_DOS$_wexecvpe)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c16execvpe,(char16_t const *__restrict __file, __T16ARGV, __T16ENVP),_wexecvpe,(__file,,))
#endif /* ... */
#if defined(__CRT_HAVE_wexecvpe) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__LIBKCALL,c32execvpe,(char32_t const *__restrict __file, __T32ARGV, __T32ENVP),wexecvpe,(__file,,))
#elif defined(__CRT_HAVE_DOS$wexecvpe)
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c32execvpe,(char32_t const *__restrict __file, __T32ARGV, __T32ENVP),wexecvpe,(__file,,))
#endif /* ... */
#if defined(__CRT_HAVE_wexecl) && (__SIZEOF_WCHAR_T__ == 2) && defined(__VLIBCCALL_IS_VLIBDCALL)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL c16execl)(char16_t const *__restrict __path, char16_t const *__args, ...) __ASMNAME("wexecl");
#elif defined(__CRT_HAVE_DOS$_wexecl)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL c16execl)(char16_t const *__restrict __path, char16_t const *__args, ...) __CASMNAME_DOS("_wexecl");
#elif (defined(__CRT_HAVE_wexecv) || (defined(__CRT_HAVE_DOS$wexecv) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wexecv) && __SIZEOF_WCHAR_T__ == 2)) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.process/wexecl.h>
#define c16execl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexecl))
#elif (defined(__CRT_HAVE_wexecv) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wexecv)
#include <local/parts.wchar.process/c16execl.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c16execl)
#else /* __cplusplus */
#define c16execl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16execl))
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wexecl) && (__SIZEOF_WCHAR_T__ == 4) && defined(__VLIBCCALL_IS_VLIBKCALL)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL c32execl)(char32_t const *__restrict __path, char32_t const *__args, ...) __ASMNAME("wexecl");
#elif defined(__CRT_HAVE_DOS$wexecl)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL c32execl)(char32_t const *__restrict __path, char32_t const *__args, ...) __CASMNAME_KOS("wexecl");
#elif (defined(__CRT_HAVE_wexecv) || (defined(__CRT_HAVE_DOS$wexecv) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wexecv) && __SIZEOF_WCHAR_T__ == 2)) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/parts.wchar.process/wexecl.h>
#define c32execl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexecl))
#elif (defined(__CRT_HAVE_wexecv) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_DOS$wexecv)
#include <local/parts.wchar.process/c32execl.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c32execl)
#else /* __cplusplus */
#define c32execl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32execl))
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wexeclp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__VLIBCCALL_IS_VLIBDCALL)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL c16execlp)(char16_t const *__restrict __file, char16_t const *__args, ...) __ASMNAME("wexeclp");
#elif defined(__CRT_HAVE_DOS$_wexeclp)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL c16execlp)(char16_t const *__restrict __file, char16_t const *__args, ...) __CASMNAME_DOS("_wexeclp");
#elif (defined(__CRT_HAVE_wexecvp) || (defined(__CRT_HAVE_DOS$wexecvp) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wexecvp) && __SIZEOF_WCHAR_T__ == 2)) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.process/wexeclp.h>
#define c16execlp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexeclp))
#elif (defined(__CRT_HAVE_wexecvp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wexecvp)
#include <local/parts.wchar.process/c16execlp.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c16execlp)
#else /* __cplusplus */
#define c16execlp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16execlp))
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wexeclp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__VLIBCCALL_IS_VLIBKCALL)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL c32execlp)(char32_t const *__restrict __file, char32_t const *__args, ...) __ASMNAME("wexeclp");
#elif defined(__CRT_HAVE_DOS$wexeclp)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL c32execlp)(char32_t const *__restrict __file, char32_t const *__args, ...) __CASMNAME_KOS("wexeclp");
#elif (defined(__CRT_HAVE_wexecvp) || (defined(__CRT_HAVE_DOS$wexecvp) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wexecvp) && __SIZEOF_WCHAR_T__ == 2)) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/parts.wchar.process/wexeclp.h>
#define c32execlp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexeclp))
#elif (defined(__CRT_HAVE_wexecvp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_DOS$wexecvp)
#include <local/parts.wchar.process/c32execlp.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c32execlp)
#else /* __cplusplus */
#define c32execlp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32execlp))
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wexecle) && (__SIZEOF_WCHAR_T__ == 2) && defined(__VLIBCCALL_IS_VLIBDCALL)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL c16execle)(char16_t const *__restrict __path, char16_t const *__args, ...) __ASMNAME("wexecle");
#elif defined(__CRT_HAVE_DOS$_wexecle)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL c16execle)(char16_t const *__restrict __path, char16_t const *__args, ...) __CASMNAME_DOS("_wexecle");
#elif (defined(__CRT_HAVE_wexecve) || (defined(__CRT_HAVE_DOS$wexecve) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wexecve) && __SIZEOF_WCHAR_T__ == 2)) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.process/wexecle.h>
#define c16execle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexecle))
#elif (defined(__CRT_HAVE_wexecve) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wexecve)
#include <local/parts.wchar.process/c16execle.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c16execle)
#else /* __cplusplus */
#define c16execle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16execle))
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wexecle) && (__SIZEOF_WCHAR_T__ == 4) && defined(__VLIBCCALL_IS_VLIBKCALL)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL c32execle)(char32_t const *__restrict __path, char32_t const *__args, ...) __ASMNAME("wexecle");
#elif defined(__CRT_HAVE_DOS$wexecle)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL c32execle)(char32_t const *__restrict __path, char32_t const *__args, ...) __CASMNAME_KOS("wexecle");
#elif (defined(__CRT_HAVE_wexecve) || (defined(__CRT_HAVE_DOS$wexecve) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wexecve) && __SIZEOF_WCHAR_T__ == 2)) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/parts.wchar.process/wexecle.h>
#define c32execle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexecle))
#elif (defined(__CRT_HAVE_wexecve) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_DOS$wexecve)
#include <local/parts.wchar.process/c32execle.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c32execle)
#else /* __cplusplus */
#define c32execle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32execle))
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wexeclpe) && (__SIZEOF_WCHAR_T__ == 2) && defined(__VLIBCCALL_IS_VLIBDCALL)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL c16execlpe)(char16_t const *__restrict __file, char16_t const *__args, ...) __ASMNAME("wexeclpe");
#elif defined(__CRT_HAVE_DOS$_wexecle)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL c16execlpe)(char16_t const *__restrict __file, char16_t const *__args, ...) __CASMNAME_DOS("_wexecle");
#elif (defined(__CRT_HAVE_wexecvpe) || (defined(__CRT_HAVE_DOS$wexecvpe) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wexecvpe) && __SIZEOF_WCHAR_T__ == 2)) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.process/wexeclpe.h>
#define c16execlpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexeclpe))
#elif (defined(__CRT_HAVE_wexecvpe) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wexecvpe)
#include <local/parts.wchar.process/c16execlpe.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c16execlpe)
#else /* __cplusplus */
#define c16execlpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16execlpe))
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wexeclpe) && (__SIZEOF_WCHAR_T__ == 4) && defined(__VLIBCCALL_IS_VLIBKCALL)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL c32execlpe)(char32_t const *__restrict __file, char32_t const *__args, ...) __ASMNAME("wexeclpe");
#elif defined(__CRT_HAVE_DOS$wexeclpe)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL c32execlpe)(char32_t const *__restrict __file, char32_t const *__args, ...) __CASMNAME_KOS("wexeclpe");
#elif (defined(__CRT_HAVE_wexecvpe) || (defined(__CRT_HAVE_DOS$wexecvpe) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wexecvpe) && __SIZEOF_WCHAR_T__ == 2)) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/parts.wchar.process/wexeclpe.h>
#define c32execlpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexeclpe))
#elif (defined(__CRT_HAVE_wexecvpe) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_DOS$wexecvpe)
#include <local/parts.wchar.process/c32execlpe.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c32execlpe)
#else /* __cplusplus */
#define c32execlpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32execlpe))
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wspawnv) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__LIBDCALL,c16spawnv,(int __mode, char16_t const *__restrict __path, __T16ARGV),wspawnv,(__mode,__path,))
#elif defined(__CRT_HAVE_DOS$_wspawnv)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c16spawnv,(int __mode, char16_t const *__restrict __path, __T16ARGV),_wspawnv,(__mode,__path,))
#endif /* ... */
#if defined(__CRT_HAVE_wspawnv) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__LIBKCALL,c32spawnv,(int __mode, char32_t const *__restrict __path, __T32ARGV),wspawnv,(__mode,__path,))
#elif defined(__CRT_HAVE_DOS$wspawnv)
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c32spawnv,(int __mode, char32_t const *__restrict __path, __T32ARGV),wspawnv,(__mode,__path,))
#endif /* ... */
#if defined(__CRT_HAVE_wspawnve) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__LIBDCALL,c16spawnve,(int __mode, char16_t const *__restrict __path, __T16ARGV, __T16ENVP),wspawnve,(__mode,__path,,))
#elif defined(__CRT_HAVE_DOS$_wspawnve)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c16spawnve,(int __mode, char16_t const *__restrict __path, __T16ARGV, __T16ENVP),_wspawnve,(__mode,__path,,))
#endif /* ... */
#if defined(__CRT_HAVE_wspawnve) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__LIBKCALL,c32spawnve,(int __mode, char32_t const *__restrict __path, __T32ARGV, __T32ENVP),wspawnve,(__mode,__path,,))
#elif defined(__CRT_HAVE_DOS$wspawnve)
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c32spawnve,(int __mode, char32_t const *__restrict __path, __T32ARGV, __T32ENVP),wspawnve,(__mode,__path,,))
#endif /* ... */
#if defined(__CRT_HAVE_wspawnvp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__LIBDCALL,c16spawnvp,(int __mode, char16_t const *__restrict __file, __T16ARGV),wspawnvp,(__mode,__file,))
#elif defined(__CRT_HAVE_DOS$_wspawnvp)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c16spawnvp,(int __mode, char16_t const *__restrict __file, __T16ARGV),_wspawnvp,(__mode,__file,))
#endif /* ... */
#if defined(__CRT_HAVE_wspawnvp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__LIBKCALL,c32spawnvp,(int __mode, char32_t const *__restrict __file, __T32ARGV),wspawnvp,(__mode,__file,))
#elif defined(__CRT_HAVE_DOS$wspawnvp)
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c32spawnvp,(int __mode, char32_t const *__restrict __file, __T32ARGV),wspawnvp,(__mode,__file,))
#endif /* ... */
#if defined(__CRT_HAVE_wspawnvpe) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__LIBDCALL,c16spawnvpe,(int __mode, char16_t const *__restrict __file, __T16ARGV, __T16ENVP),wspawnvpe,(__mode,__file,,))
#elif defined(__CRT_HAVE_DOS$_wspawnvpe)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c16spawnvpe,(int __mode, char16_t const *__restrict __file, __T16ARGV, __T16ENVP),_wspawnvpe,(__mode,__file,,))
#endif /* ... */
#if defined(__CRT_HAVE_wspawnvpe) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__LIBKCALL,c32spawnvpe,(int __mode, char32_t const *__restrict __file, __T32ARGV, __T32ENVP),wspawnvpe,(__mode,__file,,))
#elif defined(__CRT_HAVE_DOS$wspawnvpe)
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c32spawnvpe,(int __mode, char32_t const *__restrict __file, __T32ARGV, __T32ENVP),wspawnvpe,(__mode,__file,,))
#endif /* ... */
#if defined(__CRT_HAVE_wspawnl) && (__SIZEOF_WCHAR_T__ == 2) && defined(__VLIBCCALL_IS_VLIBDCALL)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL c16spawnl)(int __mode, char16_t const *__restrict __path, char16_t const *__args, ...) __ASMNAME("wspawnl");
#elif defined(__CRT_HAVE_DOS$_wspawnl)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL c16spawnl)(int __mode, char16_t const *__restrict __path, char16_t const *__args, ...) __CASMNAME_DOS("_wspawnl");
#elif (defined(__CRT_HAVE_wspawnv) || (defined(__CRT_HAVE_DOS$wspawnv) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wspawnv) && __SIZEOF_WCHAR_T__ == 2)) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.process/wspawnl.h>
#define c16spawnl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnl))
#elif (defined(__CRT_HAVE_wspawnv) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wspawnv)
#include <local/parts.wchar.process/c16spawnl.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c16spawnl)
#else /* __cplusplus */
#define c16spawnl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16spawnl))
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wspawnl) && (__SIZEOF_WCHAR_T__ == 4) && defined(__VLIBCCALL_IS_VLIBKCALL)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBKCALL c32spawnl)(int __mode, char32_t const *__restrict __path, char32_t const *__args, ...) __ASMNAME("wspawnl");
#elif defined(__CRT_HAVE_DOS$wspawnl)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBKCALL c32spawnl)(int __mode, char32_t const *__restrict __path, char32_t const *__args, ...) __CASMNAME_KOS("wspawnl");
#elif (defined(__CRT_HAVE_wspawnv) || (defined(__CRT_HAVE_DOS$wspawnv) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wspawnv) && __SIZEOF_WCHAR_T__ == 2)) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/parts.wchar.process/wspawnl.h>
#define c32spawnl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnl))
#elif (defined(__CRT_HAVE_wspawnv) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_DOS$wspawnv)
#include <local/parts.wchar.process/c32spawnl.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c32spawnl)
#else /* __cplusplus */
#define c32spawnl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32spawnl))
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wspawnlp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__VLIBCCALL_IS_VLIBDCALL)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL c16spawnlp)(int __mode, char16_t const *__restrict __file, char16_t const *__args, ...) __ASMNAME("wspawnlp");
#elif defined(__CRT_HAVE_DOS$_wspawnlp)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL c16spawnlp)(int __mode, char16_t const *__restrict __file, char16_t const *__args, ...) __CASMNAME_DOS("_wspawnlp");
#elif (defined(__CRT_HAVE_wspawnvp) || (defined(__CRT_HAVE_DOS$wspawnvp) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wspawnvp) && __SIZEOF_WCHAR_T__ == 2)) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.process/wspawnlp.h>
#define c16spawnlp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnlp))
#elif (defined(__CRT_HAVE_wspawnvp) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wspawnvp)
#include <local/parts.wchar.process/c16spawnlp.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c16spawnlp)
#else /* __cplusplus */
#define c16spawnlp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16spawnlp))
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wspawnlp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__VLIBCCALL_IS_VLIBKCALL)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBKCALL c32spawnlp)(int __mode, char32_t const *__restrict __file, char32_t const *__args, ...) __ASMNAME("wspawnlp");
#elif defined(__CRT_HAVE_DOS$wspawnlp)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBKCALL c32spawnlp)(int __mode, char32_t const *__restrict __file, char32_t const *__args, ...) __CASMNAME_KOS("wspawnlp");
#elif (defined(__CRT_HAVE_wspawnvp) || (defined(__CRT_HAVE_DOS$wspawnvp) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wspawnvp) && __SIZEOF_WCHAR_T__ == 2)) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/parts.wchar.process/wspawnlp.h>
#define c32spawnlp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnlp))
#elif (defined(__CRT_HAVE_wspawnvp) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_DOS$wspawnvp)
#include <local/parts.wchar.process/c32spawnlp.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c32spawnlp)
#else /* __cplusplus */
#define c32spawnlp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32spawnlp))
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wspawnle) && (__SIZEOF_WCHAR_T__ == 2) && defined(__VLIBCCALL_IS_VLIBDCALL)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL c16spawnle)(int __mode, char16_t const *__restrict __path, char16_t const *__args, ...) __ASMNAME("wspawnle");
#elif defined(__CRT_HAVE_DOS$_wspawnle)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL c16spawnle)(int __mode, char16_t const *__restrict __path, char16_t const *__args, ...) __CASMNAME_DOS("_wspawnle");
#elif (defined(__CRT_HAVE_wspawnve) || (defined(__CRT_HAVE_DOS$wspawnve) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wspawnve) && __SIZEOF_WCHAR_T__ == 2)) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.process/wspawnle.h>
#define c16spawnle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnle))
#elif (defined(__CRT_HAVE_wspawnve) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wspawnve)
#include <local/parts.wchar.process/c16spawnle.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c16spawnle)
#else /* __cplusplus */
#define c16spawnle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16spawnle))
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wspawnle) && (__SIZEOF_WCHAR_T__ == 4) && defined(__VLIBCCALL_IS_VLIBKCALL)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBKCALL c32spawnle)(int __mode, char32_t const *__restrict __path, char32_t const *__args, ...) __ASMNAME("wspawnle");
#elif defined(__CRT_HAVE_DOS$wspawnle)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBKCALL c32spawnle)(int __mode, char32_t const *__restrict __path, char32_t const *__args, ...) __CASMNAME_KOS("wspawnle");
#elif (defined(__CRT_HAVE_wspawnve) || (defined(__CRT_HAVE_DOS$wspawnve) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wspawnve) && __SIZEOF_WCHAR_T__ == 2)) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/parts.wchar.process/wspawnle.h>
#define c32spawnle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnle))
#elif (defined(__CRT_HAVE_wspawnve) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_DOS$wspawnve)
#include <local/parts.wchar.process/c32spawnle.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c32spawnle)
#else /* __cplusplus */
#define c32spawnle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32spawnle))
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wspawnlpe) && (__SIZEOF_WCHAR_T__ == 2) && defined(__VLIBCCALL_IS_VLIBDCALL)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL c16spawnlpe)(int __mode, char16_t const *__restrict __file, char16_t const *__args, ...) __ASMNAME("wspawnlpe");
#elif defined(__CRT_HAVE_DOS$_wspawnle)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL c16spawnlpe)(int __mode, char16_t const *__restrict __file, char16_t const *__args, ...) __CASMNAME_DOS("_wspawnle");
#elif (defined(__CRT_HAVE_wspawnvpe) || (defined(__CRT_HAVE_DOS$wspawnvpe) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wspawnvpe) && __SIZEOF_WCHAR_T__ == 2)) && (__SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.process/wspawnlpe.h>
#define c16spawnlpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnlpe))
#elif (defined(__CRT_HAVE_wspawnvpe) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wspawnvpe)
#include <local/parts.wchar.process/c16spawnlpe.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c16spawnlpe)
#else /* __cplusplus */
#define c16spawnlpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16spawnlpe))
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wspawnlpe) && (__SIZEOF_WCHAR_T__ == 4) && defined(__VLIBCCALL_IS_VLIBKCALL)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBKCALL c32spawnlpe)(int __mode, char32_t const *__restrict __file, char32_t const *__args, ...) __ASMNAME("wspawnlpe");
#elif defined(__CRT_HAVE_DOS$wspawnlpe)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBKCALL c32spawnlpe)(int __mode, char32_t const *__restrict __file, char32_t const *__args, ...) __CASMNAME_KOS("wspawnlpe");
#elif (defined(__CRT_HAVE_wspawnvpe) || (defined(__CRT_HAVE_DOS$wspawnvpe) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wspawnvpe) && __SIZEOF_WCHAR_T__ == 2)) && (__SIZEOF_WCHAR_T__ == 4)
#include <local/parts.wchar.process/wspawnlpe.h>
#define c32spawnlpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnlpe))
#elif (defined(__CRT_HAVE_wspawnvpe) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_DOS$wspawnvpe)
#include <local/parts.wchar.process/c32spawnlpe.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(c32spawnlpe)
#else /* __cplusplus */
#define c32spawnlpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32spawnlpe))
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wsystem) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_REDIRECT(__LIBC,,int,__NOTHROW_RPC,__LIBDCALL,c16system,(char16_t const *__cmd),wsystem,(__cmd))
#elif defined(__CRT_HAVE_DOS$_wsystem)
__CREDIRECT_DOS(,int,__NOTHROW_RPC,c16system,(char16_t const *__cmd),_wsystem,(__cmd))
#endif /* ... */
#if defined(__CRT_HAVE_wsystem) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_REDIRECT(__LIBC,,int,__NOTHROW_RPC,__LIBKCALL,c32system,(char32_t const *__cmd),wsystem,(__cmd))
#elif defined(__CRT_HAVE_DOS$wsystem)
__CREDIRECT_KOS(,int,__NOTHROW_RPC,c32system,(char32_t const *__cmd),wsystem,(__cmd))
#endif /* ... */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PARTS_UCHAR_PROCESS_H */
