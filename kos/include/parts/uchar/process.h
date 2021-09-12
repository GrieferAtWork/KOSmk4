/* HASH CRC-32:0x79421075 */
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
#ifndef _PARTS_UCHAR_PROCESS_H
#define _PARTS_UCHAR_PROCESS_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#ifndef _PROCESS_H
#include <process.h>
#endif /* !_PROCESS_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */

#include <bits/types.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __T16ARGV
#ifdef __USE_DOS_ALTERATIONS
#define __T16ARGV char16_t const *const *__restrict ___argv
#define __T16ENVP char16_t const *const *__restrict ___envp
#else /* __USE_DOS_ALTERATIONS */
#define __T16ARGV char16_t *const ___argv[__restrict_arr]
#define __T16ENVP char16_t *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__T16ARGV */
#ifndef __T32ARGV
#ifdef __USE_DOS_ALTERATIONS
#define __T32ARGV char32_t const *const *__restrict ___argv
#define __T32ENVP char32_t const *const *__restrict ___envp
#else /* __USE_DOS_ALTERATIONS */
#define __T32ARGV char32_t *const ___argv[__restrict_arr]
#define __T32ENVP char32_t *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__T32ARGV */
#if defined(__CRT_HAVE_wexecv) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16execv,(char16_t const *__restrict __path, __T16ARGV),wexecv,(__path,___argv))
#elif defined(__CRT_HAVE_DOS$wexecv)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16execv,(char16_t const *__restrict __path, __T16ARGV),wexecv,(__path,___argv))
#elif defined(__CRT_HAVE__wexecv) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16execv,(char16_t const *__restrict __path, __T16ARGV),_wexecv,(__path,___argv))
#elif defined(__CRT_HAVE_DOS$_wexecv)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16execv,(char16_t const *__restrict __path, __T16ARGV),_wexecv,(__path,___argv))
#endif /* ... */
#if defined(__CRT_HAVE_wexecv) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c32execv,(char32_t const *__restrict __path, __T32ARGV),wexecv,(__path,___argv))
#elif defined(__CRT_HAVE_KOS$wexecv)
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c32execv,(char32_t const *__restrict __path, __T32ARGV),wexecv,(__path,___argv))
#elif defined(__CRT_HAVE__wexecv) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c32execv,(char32_t const *__restrict __path, __T32ARGV),_wexecv,(__path,___argv))
#elif defined(__CRT_HAVE_KOS$_wexecv)
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c32execv,(char32_t const *__restrict __path, __T32ARGV),_wexecv,(__path,___argv))
#endif /* ... */
#if defined(__CRT_HAVE_wexecve) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c16execve,(char16_t const *__restrict __path, __T16ARGV, __T16ENVP),wexecve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE_DOS$wexecve)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c16execve,(char16_t const *__restrict __path, __T16ARGV, __T16ENVP),wexecve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE__wexecve) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c16execve,(char16_t const *__restrict __path, __T16ARGV, __T16ENVP),_wexecve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE_DOS$_wexecve)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c16execve,(char16_t const *__restrict __path, __T16ARGV, __T16ENVP),_wexecve,(__path,___argv,___envp))
#endif /* ... */
#if defined(__CRT_HAVE_wexecve) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c32execve,(char32_t const *__restrict __path, __T32ARGV, __T32ENVP),wexecve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE_KOS$wexecve)
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c32execve,(char32_t const *__restrict __path, __T32ARGV, __T32ENVP),wexecve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE__wexecve) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c32execve,(char32_t const *__restrict __path, __T32ARGV, __T32ENVP),_wexecve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE_KOS$_wexecve)
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c32execve,(char32_t const *__restrict __path, __T32ARGV, __T32ENVP),_wexecve,(__path,___argv,___envp))
#endif /* ... */
#if defined(__CRT_HAVE_wexecvp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16execvp,(char16_t const *__restrict __file, __T16ARGV),wexecvp,(__path,___argv))
#elif defined(__CRT_HAVE_DOS$wexecvp)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16execvp,(char16_t const *__restrict __file, __T16ARGV),wexecvp,(__path,___argv))
#elif defined(__CRT_HAVE__wexecvp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16execvp,(char16_t const *__restrict __file, __T16ARGV),_wexecvp,(__path,___argv))
#elif defined(__CRT_HAVE_DOS$_wexecvp)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c16execvp,(char16_t const *__restrict __file, __T16ARGV),_wexecvp,(__path,___argv))
#endif /* ... */
#if defined(__CRT_HAVE_wexecvp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c32execvp,(char32_t const *__restrict __file, __T32ARGV),wexecvp,(__path,___argv))
#elif defined(__CRT_HAVE_KOS$wexecvp)
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c32execvp,(char32_t const *__restrict __file, __T32ARGV),wexecvp,(__path,___argv))
#elif defined(__CRT_HAVE__wexecvp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c32execvp,(char32_t const *__restrict __file, __T32ARGV),_wexecvp,(__path,___argv))
#elif defined(__CRT_HAVE_KOS$_wexecvp)
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,c32execvp,(char32_t const *__restrict __file, __T32ARGV),_wexecvp,(__path,___argv))
#endif /* ... */
#if defined(__CRT_HAVE_wexecvpe) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c16execvpe,(char16_t const *__restrict __file, __T16ARGV, __T16ENVP),wexecvpe,(__path,___argv,___envp))
#elif defined(__CRT_HAVE_DOS$wexecvpe)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c16execvpe,(char16_t const *__restrict __file, __T16ARGV, __T16ENVP),wexecvpe,(__path,___argv,___envp))
#elif defined(__CRT_HAVE__wexecvpe) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c16execvpe,(char16_t const *__restrict __file, __T16ARGV, __T16ENVP),_wexecvpe,(__path,___argv,___envp))
#elif defined(__CRT_HAVE_DOS$_wexecvpe)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c16execvpe,(char16_t const *__restrict __file, __T16ARGV, __T16ENVP),_wexecvpe,(__path,___argv,___envp))
#endif /* ... */
#if defined(__CRT_HAVE_wexecvpe) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c32execvpe,(char32_t const *__restrict __file, __T32ARGV, __T32ENVP),wexecvpe,(__path,___argv,___envp))
#elif defined(__CRT_HAVE_KOS$wexecvpe)
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c32execvpe,(char32_t const *__restrict __file, __T32ARGV, __T32ENVP),wexecvpe,(__path,___argv,___envp))
#elif defined(__CRT_HAVE__wexecvpe) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c32execvpe,(char32_t const *__restrict __file, __T32ARGV, __T32ENVP),_wexecvpe,(__path,___argv,___envp))
#elif defined(__CRT_HAVE_KOS$_wexecvpe)
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,c32execvpe,(char32_t const *__restrict __file, __T32ARGV, __T32ENVP),_wexecvpe,(__path,___argv,___envp))
#endif /* ... */
#if defined(__CRT_HAVE_wexecl) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL c16execl)(char16_t const *__restrict __path, char16_t const *__args, ...) __CASMNAME("wexecl");
#elif defined(__CRT_HAVE__wexecl) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL c16execl)(char16_t const *__restrict __path, char16_t const *__args, ...) __CASMNAME("_wexecl");
#elif (defined(__CRT_HAVE_wexecv) || defined(__CRT_HAVE__wexecv)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.process/wexecl.h>
#define c16execl __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexecl)
#elif (defined(__CRT_HAVE_wexecv) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wexecv) || (defined(__CRT_HAVE__wexecv) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wexecv)
#include <libc/local/parts.uchar.process/c16execl.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(c16execl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL c16execl)(char16_t const *__restrict __path, char16_t const *__args, ...) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16execl)(__path, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define c16execl __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16execl)
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wexecl) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL c32execl)(char32_t const *__restrict __path, char32_t const *__args, ...) __CASMNAME("wexecl");
#elif defined(__CRT_HAVE__wexecl) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL c32execl)(char32_t const *__restrict __path, char32_t const *__args, ...) __CASMNAME("_wexecl");
#elif (defined(__CRT_HAVE_wexecv) || defined(__CRT_HAVE__wexecv)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.process/wexecl.h>
#define c32execl __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexecl)
#elif (defined(__CRT_HAVE_wexecv) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wexecv) || (defined(__CRT_HAVE__wexecv) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_wexecv)
#include <libc/local/parts.uchar.process/c32execl.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(c32execl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL c32execl)(char32_t const *__restrict __path, char32_t const *__args, ...) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32execl)(__path, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define c32execl __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32execl)
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wexeclp) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL c16execlp)(char16_t const *__restrict __file, char16_t const *__args, ...) __CASMNAME("wexeclp");
#elif defined(__CRT_HAVE__wexeclp) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL c16execlp)(char16_t const *__restrict __file, char16_t const *__args, ...) __CASMNAME("_wexeclp");
#elif (defined(__CRT_HAVE_wexecvp) || defined(__CRT_HAVE__wexecvp)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.process/wexeclp.h>
#define c16execlp __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexeclp)
#elif (defined(__CRT_HAVE_wexecvp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wexecvp) || (defined(__CRT_HAVE__wexecvp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wexecvp)
#include <libc/local/parts.uchar.process/c16execlp.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(c16execlp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL c16execlp)(char16_t const *__restrict __file, char16_t const *__args, ...) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16execlp)(__file, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define c16execlp __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16execlp)
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wexeclp) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL c32execlp)(char32_t const *__restrict __file, char32_t const *__args, ...) __CASMNAME("wexeclp");
#elif defined(__CRT_HAVE__wexeclp) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL c32execlp)(char32_t const *__restrict __file, char32_t const *__args, ...) __CASMNAME("_wexeclp");
#elif (defined(__CRT_HAVE_wexecvp) || defined(__CRT_HAVE__wexecvp)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.process/wexeclp.h>
#define c32execlp __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexeclp)
#elif (defined(__CRT_HAVE_wexecvp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wexecvp) || (defined(__CRT_HAVE__wexecvp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_wexecvp)
#include <libc/local/parts.uchar.process/c32execlp.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(c32execlp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL c32execlp)(char32_t const *__restrict __file, char32_t const *__args, ...) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32execlp)(__file, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define c32execlp __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32execlp)
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wexecle) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL c16execle)(char16_t const *__restrict __path, char16_t const *__args, ...) __CASMNAME("wexecle");
#elif defined(__CRT_HAVE__wexecle) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL c16execle)(char16_t const *__restrict __path, char16_t const *__args, ...) __CASMNAME("_wexecle");
#elif (defined(__CRT_HAVE_wexecve) || defined(__CRT_HAVE__wexecve)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.process/wexecle.h>
#define c16execle __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexecle)
#elif (defined(__CRT_HAVE_wexecve) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wexecve) || (defined(__CRT_HAVE__wexecve) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wexecve)
#include <libc/local/parts.uchar.process/c16execle.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(c16execle, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL c16execle)(char16_t const *__restrict __path, char16_t const *__args, ...) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16execle)(__path, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define c16execle __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16execle)
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wexecle) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL c32execle)(char32_t const *__restrict __path, char32_t const *__args, ...) __CASMNAME("wexecle");
#elif defined(__CRT_HAVE__wexecle) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL c32execle)(char32_t const *__restrict __path, char32_t const *__args, ...) __CASMNAME("_wexecle");
#elif (defined(__CRT_HAVE_wexecve) || defined(__CRT_HAVE__wexecve)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.process/wexecle.h>
#define c32execle __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexecle)
#elif (defined(__CRT_HAVE_wexecve) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wexecve) || (defined(__CRT_HAVE__wexecve) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_wexecve)
#include <libc/local/parts.uchar.process/c32execle.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(c32execle, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL c32execle)(char32_t const *__restrict __path, char32_t const *__args, ...) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32execle)(__path, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define c32execle __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32execle)
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wexeclpe) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL c16execlpe)(char16_t const *__restrict __file, char16_t const *__args, ...) __CASMNAME("wexeclpe");
#elif defined(__CRT_HAVE__wexeclpe) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL c16execlpe)(char16_t const *__restrict __file, char16_t const *__args, ...) __CASMNAME("_wexeclpe");
#elif (defined(__CRT_HAVE_wexecvpe) || defined(__CRT_HAVE__wexecvpe)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.process/wexeclpe.h>
#define c16execlpe __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexeclpe)
#elif (defined(__CRT_HAVE_wexecvpe) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wexecvpe) || (defined(__CRT_HAVE__wexecvpe) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wexecvpe)
#include <libc/local/parts.uchar.process/c16execlpe.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(c16execlpe, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL c16execlpe)(char16_t const *__restrict __file, char16_t const *__args, ...) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16execlpe)(__file, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define c16execlpe __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16execlpe)
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wexeclpe) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL c32execlpe)(char32_t const *__restrict __file, char32_t const *__args, ...) __CASMNAME("wexeclpe");
#elif defined(__CRT_HAVE__wexeclpe) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL c32execlpe)(char32_t const *__restrict __file, char32_t const *__args, ...) __CASMNAME("_wexeclpe");
#elif (defined(__CRT_HAVE_wexecvpe) || defined(__CRT_HAVE__wexecvpe)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.process/wexeclpe.h>
#define c32execlpe __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexeclpe)
#elif (defined(__CRT_HAVE_wexecvpe) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wexecvpe) || (defined(__CRT_HAVE__wexecvpe) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_wexecvpe)
#include <libc/local/parts.uchar.process/c32execlpe.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(c32execlpe, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL c32execlpe)(char32_t const *__restrict __file, char32_t const *__args, ...) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32execlpe)(__file, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define c32execlpe __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32execlpe)
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wspawnv) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c16spawnv,(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __path, __T16ARGV),wspawnv,(__mode,__path,___argv))
#elif defined(__CRT_HAVE_DOS$wspawnv)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c16spawnv,(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __path, __T16ARGV),wspawnv,(__mode,__path,___argv))
#elif defined(__CRT_HAVE__wspawnv) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c16spawnv,(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __path, __T16ARGV),_wspawnv,(__mode,__path,___argv))
#elif defined(__CRT_HAVE_DOS$_wspawnv)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c16spawnv,(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __path, __T16ARGV),_wspawnv,(__mode,__path,___argv))
#endif /* ... */
#if defined(__CRT_HAVE_wspawnv) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c32spawnv,(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __path, __T32ARGV),wspawnv,(__mode,__path,___argv))
#elif defined(__CRT_HAVE_KOS$wspawnv)
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c32spawnv,(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __path, __T32ARGV),wspawnv,(__mode,__path,___argv))
#elif defined(__CRT_HAVE__wspawnv) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c32spawnv,(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __path, __T32ARGV),_wspawnv,(__mode,__path,___argv))
#elif defined(__CRT_HAVE_KOS$_wspawnv)
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c32spawnv,(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __path, __T32ARGV),_wspawnv,(__mode,__path,___argv))
#endif /* ... */
#if defined(__CRT_HAVE_wspawnve) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c16spawnve,(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __path, __T16ARGV, __T16ENVP),wspawnve,(__mode,__path,___argv,___envp))
#elif defined(__CRT_HAVE_DOS$wspawnve)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c16spawnve,(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __path, __T16ARGV, __T16ENVP),wspawnve,(__mode,__path,___argv,___envp))
#elif defined(__CRT_HAVE__wspawnve) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c16spawnve,(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __path, __T16ARGV, __T16ENVP),_wspawnve,(__mode,__path,___argv,___envp))
#elif defined(__CRT_HAVE_DOS$_wspawnve)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c16spawnve,(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __path, __T16ARGV, __T16ENVP),_wspawnve,(__mode,__path,___argv,___envp))
#endif /* ... */
#if defined(__CRT_HAVE_wspawnve) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c32spawnve,(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __path, __T32ARGV, __T32ENVP),wspawnve,(__mode,__path,___argv,___envp))
#elif defined(__CRT_HAVE_KOS$wspawnve)
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c32spawnve,(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __path, __T32ARGV, __T32ENVP),wspawnve,(__mode,__path,___argv,___envp))
#elif defined(__CRT_HAVE__wspawnve) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c32spawnve,(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __path, __T32ARGV, __T32ENVP),_wspawnve,(__mode,__path,___argv,___envp))
#elif defined(__CRT_HAVE_KOS$_wspawnve)
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c32spawnve,(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __path, __T32ARGV, __T32ENVP),_wspawnve,(__mode,__path,___argv,___envp))
#endif /* ... */
#if defined(__CRT_HAVE_wspawnvp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c16spawnvp,(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __file, __T16ARGV),wspawnvp,(__mode,__file,___argv))
#elif defined(__CRT_HAVE_DOS$wspawnvp)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c16spawnvp,(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __file, __T16ARGV),wspawnvp,(__mode,__file,___argv))
#elif defined(__CRT_HAVE__wspawnvp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c16spawnvp,(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __file, __T16ARGV),_wspawnvp,(__mode,__file,___argv))
#elif defined(__CRT_HAVE_DOS$_wspawnvp)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c16spawnvp,(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __file, __T16ARGV),_wspawnvp,(__mode,__file,___argv))
#endif /* ... */
#if defined(__CRT_HAVE_wspawnvp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c32spawnvp,(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __file, __T32ARGV),wspawnvp,(__mode,__file,___argv))
#elif defined(__CRT_HAVE_KOS$wspawnvp)
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c32spawnvp,(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __file, __T32ARGV),wspawnvp,(__mode,__file,___argv))
#elif defined(__CRT_HAVE__wspawnvp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c32spawnvp,(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __file, __T32ARGV),_wspawnvp,(__mode,__file,___argv))
#elif defined(__CRT_HAVE_KOS$_wspawnvp)
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,c32spawnvp,(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __file, __T32ARGV),_wspawnvp,(__mode,__file,___argv))
#endif /* ... */
#if defined(__CRT_HAVE_wspawnvpe) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c16spawnvpe,(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __file, __T16ARGV, __T16ENVP),wspawnvpe,(__mode,__file,___argv,___envp))
#elif defined(__CRT_HAVE_DOS$wspawnvpe)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c16spawnvpe,(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __file, __T16ARGV, __T16ENVP),wspawnvpe,(__mode,__file,___argv,___envp))
#elif defined(__CRT_HAVE__wspawnvpe) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c16spawnvpe,(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __file, __T16ARGV, __T16ENVP),_wspawnvpe,(__mode,__file,___argv,___envp))
#elif defined(__CRT_HAVE_DOS$_wspawnvpe)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c16spawnvpe,(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __file, __T16ARGV, __T16ENVP),_wspawnvpe,(__mode,__file,___argv,___envp))
#endif /* ... */
#if defined(__CRT_HAVE_wspawnvpe) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c32spawnvpe,(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __file, __T32ARGV, __T32ENVP),wspawnvpe,(__mode,__file,___argv,___envp))
#elif defined(__CRT_HAVE_KOS$wspawnvpe)
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c32spawnvpe,(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __file, __T32ARGV, __T32ENVP),wspawnvpe,(__mode,__file,___argv,___envp))
#elif defined(__CRT_HAVE__wspawnvpe) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c32spawnvpe,(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __file, __T32ARGV, __T32ENVP),_wspawnvpe,(__mode,__file,___argv,___envp))
#elif defined(__CRT_HAVE_KOS$_wspawnvpe)
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,c32spawnvpe,(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __file, __T32ARGV, __T32ENVP),_wspawnvpe,(__mode,__file,___argv,___envp))
#endif /* ... */
#if defined(__CRT_HAVE_wspawnl) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL c16spawnl)(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __path, char16_t const *__args, ...) __CASMNAME("wspawnl");
#elif defined(__CRT_HAVE__wspawnl) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL c16spawnl)(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __path, char16_t const *__args, ...) __CASMNAME("_wspawnl");
#elif (defined(__CRT_HAVE_wspawnv) || defined(__CRT_HAVE__wspawnv)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.process/wspawnl.h>
#define c16spawnl __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnl)
#elif (defined(__CRT_HAVE_wspawnv) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wspawnv) || (defined(__CRT_HAVE__wspawnv) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wspawnv)
#include <libc/local/parts.uchar.process/c16spawnl.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(c16spawnl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL c16spawnl)(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __path, char16_t const *__args, ...) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16spawnl)(__mode, __path, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define c16spawnl __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16spawnl)
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wspawnl) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBKCALL c32spawnl)(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __path, char32_t const *__args, ...) __CASMNAME("wspawnl");
#elif defined(__CRT_HAVE__wspawnl) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBKCALL c32spawnl)(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __path, char32_t const *__args, ...) __CASMNAME("_wspawnl");
#elif (defined(__CRT_HAVE_wspawnv) || defined(__CRT_HAVE__wspawnv)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.process/wspawnl.h>
#define c32spawnl __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnl)
#elif (defined(__CRT_HAVE_wspawnv) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wspawnv) || (defined(__CRT_HAVE__wspawnv) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_wspawnv)
#include <libc/local/parts.uchar.process/c32spawnl.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(c32spawnl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBKCALL c32spawnl)(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __path, char32_t const *__args, ...) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32spawnl)(__mode, __path, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define c32spawnl __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32spawnl)
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wspawnlp) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL c16spawnlp)(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __file, char16_t const *__args, ...) __CASMNAME("wspawnlp");
#elif defined(__CRT_HAVE__wspawnlp) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL c16spawnlp)(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __file, char16_t const *__args, ...) __CASMNAME("_wspawnlp");
#elif (defined(__CRT_HAVE_wspawnvp) || defined(__CRT_HAVE__wspawnvp)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.process/wspawnlp.h>
#define c16spawnlp __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnlp)
#elif (defined(__CRT_HAVE_wspawnvp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wspawnvp) || (defined(__CRT_HAVE__wspawnvp) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wspawnvp)
#include <libc/local/parts.uchar.process/c16spawnlp.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(c16spawnlp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL c16spawnlp)(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __file, char16_t const *__args, ...) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16spawnlp)(__mode, __file, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define c16spawnlp __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16spawnlp)
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wspawnlp) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBKCALL c32spawnlp)(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __file, char32_t const *__args, ...) __CASMNAME("wspawnlp");
#elif defined(__CRT_HAVE__wspawnlp) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBKCALL c32spawnlp)(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __file, char32_t const *__args, ...) __CASMNAME("_wspawnlp");
#elif (defined(__CRT_HAVE_wspawnvp) || defined(__CRT_HAVE__wspawnvp)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.process/wspawnlp.h>
#define c32spawnlp __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnlp)
#elif (defined(__CRT_HAVE_wspawnvp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wspawnvp) || (defined(__CRT_HAVE__wspawnvp) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_wspawnvp)
#include <libc/local/parts.uchar.process/c32spawnlp.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(c32spawnlp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBKCALL c32spawnlp)(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __file, char32_t const *__args, ...) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32spawnlp)(__mode, __file, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define c32spawnlp __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32spawnlp)
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wspawnle) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL c16spawnle)(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __path, char16_t const *__args, ...) __CASMNAME("wspawnle");
#elif defined(__CRT_HAVE__wspawnle) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL c16spawnle)(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __path, char16_t const *__args, ...) __CASMNAME("_wspawnle");
#elif (defined(__CRT_HAVE_wspawnve) || defined(__CRT_HAVE__wspawnve)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.process/wspawnle.h>
#define c16spawnle __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnle)
#elif (defined(__CRT_HAVE_wspawnve) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wspawnve) || (defined(__CRT_HAVE__wspawnve) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wspawnve)
#include <libc/local/parts.uchar.process/c16spawnle.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(c16spawnle, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL c16spawnle)(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __path, char16_t const *__args, ...) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16spawnle)(__mode, __path, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define c16spawnle __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16spawnle)
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wspawnle) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBKCALL c32spawnle)(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __path, char32_t const *__args, ...) __CASMNAME("wspawnle");
#elif defined(__CRT_HAVE__wspawnle) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBKCALL c32spawnle)(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __path, char32_t const *__args, ...) __CASMNAME("_wspawnle");
#elif (defined(__CRT_HAVE_wspawnve) || defined(__CRT_HAVE__wspawnve)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.process/wspawnle.h>
#define c32spawnle __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnle)
#elif (defined(__CRT_HAVE_wspawnve) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wspawnve) || (defined(__CRT_HAVE__wspawnve) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_wspawnve)
#include <libc/local/parts.uchar.process/c32spawnle.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(c32spawnle, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBKCALL c32spawnle)(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __path, char32_t const *__args, ...) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32spawnle)(__mode, __path, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define c32spawnle __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32spawnle)
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wspawnlpe) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL c16spawnlpe)(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __file, char16_t const *__args, ...) __CASMNAME("wspawnlpe");
#elif defined(__CRT_HAVE__wspawnlpe) && __SIZEOF_WCHAR_T__ == 2 && defined(__VLIBCCALL_IS_VLIBDCALL)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL c16spawnlpe)(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __file, char16_t const *__args, ...) __CASMNAME("_wspawnlpe");
#elif (defined(__CRT_HAVE_wspawnvpe) || defined(__CRT_HAVE__wspawnvpe)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/parts.wchar.process/wspawnlpe.h>
#define c16spawnlpe __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnlpe)
#elif (defined(__CRT_HAVE_wspawnvpe) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wspawnvpe) || (defined(__CRT_HAVE__wspawnvpe) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wspawnvpe)
#include <libc/local/parts.uchar.process/c16spawnlpe.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(c16spawnlpe, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL c16spawnlpe)(__STDC_INT_AS_UINT_T __mode, char16_t const *__restrict __file, char16_t const *__args, ...) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16spawnlpe)(__mode, __file, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define c16spawnlpe __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16spawnlpe)
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wspawnlpe) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBKCALL c32spawnlpe)(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __file, char32_t const *__args, ...) __CASMNAME("wspawnlpe");
#elif defined(__CRT_HAVE__wspawnlpe) && __SIZEOF_WCHAR_T__ == 4 && defined(__VLIBCCALL_IS_VLIBKCALL)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBKCALL c32spawnlpe)(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __file, char32_t const *__args, ...) __CASMNAME("_wspawnlpe");
#elif (defined(__CRT_HAVE_wspawnvpe) || defined(__CRT_HAVE__wspawnvpe)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/parts.wchar.process/wspawnlpe.h>
#define c32spawnlpe __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnlpe)
#elif (defined(__CRT_HAVE_wspawnvpe) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wspawnvpe) || (defined(__CRT_HAVE__wspawnvpe) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_wspawnvpe)
#include <libc/local/parts.uchar.process/c32spawnlpe.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(c32spawnlpe, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBKCALL c32spawnlpe)(__STDC_INT_AS_UINT_T __mode, char32_t const *__restrict __file, char32_t const *__args, ...) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32spawnlpe)(__mode, __file, __args, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define c32spawnlpe __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32spawnlpe)
#endif /* !__cplusplus */
#endif /* ... */
#if defined(__CRT_HAVE_wsystem) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(,int,__NOTHROW_RPC,c16system,(char16_t const *__cmd),wsystem,(__cmd))
#elif defined(__CRT_HAVE_DOS$wsystem)
__CREDIRECT_DOS(,int,__NOTHROW_RPC,c16system,(char16_t const *__cmd),wsystem,(__cmd))
#elif defined(__CRT_HAVE__wsystem) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(,int,__NOTHROW_RPC,c16system,(char16_t const *__cmd),_wsystem,(__cmd))
#elif defined(__CRT_HAVE_DOS$_wsystem)
__CREDIRECT_DOS(,int,__NOTHROW_RPC,c16system,(char16_t const *__cmd),_wsystem,(__cmd))
#endif /* ... */
#if defined(__CRT_HAVE_wsystem) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(,int,__NOTHROW_RPC,c32system,(char32_t const *__cmd),wsystem,(__cmd))
#elif defined(__CRT_HAVE_KOS$wsystem)
__CREDIRECT_KOS(,int,__NOTHROW_RPC,c32system,(char32_t const *__cmd),wsystem,(__cmd))
#elif defined(__CRT_HAVE__wsystem) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(,int,__NOTHROW_RPC,c32system,(char32_t const *__cmd),_wsystem,(__cmd))
#elif defined(__CRT_HAVE_KOS$_wsystem)
__CREDIRECT_KOS(,int,__NOTHROW_RPC,c32system,(char32_t const *__cmd),_wsystem,(__cmd))
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_PARTS_UCHAR_PROCESS_H */
