/* HASH CRC-32:0x42b54c2f */
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
#ifndef _PARTS_WCHAR_PROCESS_H
#define _PARTS_WCHAR_PROCESS_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#ifndef _PROCESS_H
#include <process.h>
#endif /* !_PROCESS_H */
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */
#include <bits/types.h>

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __TWARGV
#ifdef __USE_DOS
#define __TWARGV wchar_t const *const *__restrict ___argv
#define __TWENVP wchar_t const *const *__restrict ___envp
#else /* __USE_DOS */
#define __TWARGV wchar_t *const ___argv[__restrict_arr]
#define __TWENVP wchar_t *const ___envp[__restrict_arr]
#endif /* !__USE_DOS */
#endif /* !__TWARGV */
#ifndef __wexecv_defined
#define __wexecv_defined 1
#ifdef __CRT_HAVE_wexecv
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,wexecv,(wchar_t const *__restrict __path, __TWARGV),(__path,))
#elif defined(__CRT_HAVE_DOS$wexecv) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,wexecv,(char32_t const *__restrict __path, __T32ARGV),wexecv,(__path,))
#elif defined(__CRT_HAVE_DOS$_wexecv) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,wexecv,(char16_t const *__restrict __path, __T16ARGV),_wexecv,(__path,))
#else /* ... */
#undef __wexecv_defined
#endif /* !... */
#endif /* !__wexecv_defined */
#ifndef __wexecve_defined
#define __wexecve_defined 1
#ifdef __CRT_HAVE_wexecve
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,wexecve,(wchar_t const *__restrict __path, __TWARGV, __TWENVP),(__path,,))
#elif defined(__CRT_HAVE_DOS$wexecve) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,wexecve,(char32_t const *__restrict __path, __T32ARGV, __T32ENVP),wexecve,(__path,,))
#elif defined(__CRT_HAVE_DOS$_wexecve) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,wexecve,(char16_t const *__restrict __path, __T16ARGV, __T16ENVP),_wexecve,(__path,,))
#else /* ... */
#undef __wexecve_defined
#endif /* !... */
#endif /* !__wexecve_defined */
#ifndef __wexecvp_defined
#define __wexecvp_defined 1
#ifdef __CRT_HAVE_wexecvp
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,wexecvp,(wchar_t const *__restrict __file, __TWARGV),(__file,))
#elif defined(__CRT_HAVE_DOS$wexecvp) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,wexecvp,(char32_t const *__restrict __file, __T32ARGV),wexecvp,(__file,))
#elif defined(__CRT_HAVE_DOS$_wexecvp) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,wexecvp,(char16_t const *__restrict __file, __T16ARGV),_wexecvp,(__file,))
#else /* ... */
#undef __wexecvp_defined
#endif /* !... */
#endif /* !__wexecvp_defined */
#ifndef __wexecvpe_defined
#define __wexecvpe_defined 1
#ifdef __CRT_HAVE_wexecvpe
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,wexecvpe,(wchar_t const *__restrict __file, __TWARGV, __TWENVP),(__file,,))
#elif defined(__CRT_HAVE_DOS$wexecvpe) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,wexecvpe,(char32_t const *__restrict __file, __T32ARGV, __T32ENVP),wexecvpe,(__file,,))
#elif defined(__CRT_HAVE_DOS$_wexecvpe) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,wexecvpe,(char16_t const *__restrict __file, __T16ARGV, __T16ENVP),_wexecvpe,(__file,,))
#else /* ... */
#undef __wexecvpe_defined
#endif /* !... */
#endif /* !__wexecvpe_defined */
#ifndef __wexecl_defined
#define __wexecl_defined 1
#ifdef __CRT_HAVE_wexecl
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexecl)(wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME_SAME("wexecl");
#elif defined(__CRT_HAVE_DOS$wexecl) && __SIZEOF_WCHAR_T__ == 4
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL wexecl)(char32_t const *__restrict __path, char32_t const *__args, ...) __CASMNAME_KOS("wexecl");
#elif defined(__CRT_HAVE_DOS$_wexecl) && __SIZEOF_WCHAR_T__ == 2
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL wexecl)(char16_t const *__restrict __path, char16_t const *__args, ...) __CASMNAME_DOS("_wexecl");
#elif defined(__CRT_HAVE_wexecv) || (defined(__CRT_HAVE_DOS$wexecv) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wexecv) && __SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.process/wexecl.h>
#define wexecl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexecl))
#else /* ... */
#undef __wexecl_defined
#endif /* !... */
#endif /* !__wexecl_defined */
#ifndef __wexeclp_defined
#define __wexeclp_defined 1
#ifdef __CRT_HAVE_wexeclp
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexeclp)(wchar_t const *__restrict __file, wchar_t const *__args, ...) __CASMNAME_SAME("wexeclp");
#elif defined(__CRT_HAVE_DOS$wexeclp) && __SIZEOF_WCHAR_T__ == 4
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL wexeclp)(char32_t const *__restrict __file, char32_t const *__args, ...) __CASMNAME_KOS("wexeclp");
#elif defined(__CRT_HAVE_DOS$_wexeclp) && __SIZEOF_WCHAR_T__ == 2
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL wexeclp)(char16_t const *__restrict __file, char16_t const *__args, ...) __CASMNAME_DOS("_wexeclp");
#elif defined(__CRT_HAVE_wexecvp) || (defined(__CRT_HAVE_DOS$wexecvp) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wexecvp) && __SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.process/wexeclp.h>
#define wexeclp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexeclp))
#else /* ... */
#undef __wexeclp_defined
#endif /* !... */
#endif /* !__wexeclp_defined */
#ifndef __wexecle_defined
#define __wexecle_defined 1
#ifdef __CRT_HAVE_wexecle
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexecle)(wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME_SAME("wexecle");
#elif defined(__CRT_HAVE_DOS$wexecle) && __SIZEOF_WCHAR_T__ == 4
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL wexecle)(char32_t const *__restrict __path, char32_t const *__args, ...) __CASMNAME_KOS("wexecle");
#elif defined(__CRT_HAVE_DOS$_wexecle) && __SIZEOF_WCHAR_T__ == 2
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL wexecle)(char16_t const *__restrict __path, char16_t const *__args, ...) __CASMNAME_DOS("_wexecle");
#elif defined(__CRT_HAVE_wexecve) || (defined(__CRT_HAVE_DOS$wexecve) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wexecve) && __SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.process/wexecle.h>
#define wexecle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexecle))
#else /* ... */
#undef __wexecle_defined
#endif /* !... */
#endif /* !__wexecle_defined */
#ifndef __wexeclpe_defined
#define __wexeclpe_defined 1
#ifdef __CRT_HAVE_wexeclpe
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexeclpe)(wchar_t const *__restrict __file, wchar_t const *__args, ...) __CASMNAME_SAME("wexeclpe");
#elif defined(__CRT_HAVE_DOS$wexeclpe) && __SIZEOF_WCHAR_T__ == 4
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBKCALL wexeclpe)(char32_t const *__restrict __file, char32_t const *__args, ...) __CASMNAME_KOS("wexeclpe");
#elif defined(__CRT_HAVE_DOS$_wexecle) && __SIZEOF_WCHAR_T__ == 2
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBDCALL wexeclpe)(char16_t const *__restrict __file, char16_t const *__args, ...) __CASMNAME_DOS("_wexecle");
#elif defined(__CRT_HAVE_wexecvpe) || (defined(__CRT_HAVE_DOS$wexecvpe) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wexecvpe) && __SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.process/wexeclpe.h>
#define wexeclpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexeclpe))
#else /* ... */
#undef __wexeclpe_defined
#endif /* !... */
#endif /* !__wexeclpe_defined */
#ifndef __wspawnv_defined
#define __wspawnv_defined 1
#ifdef __CRT_HAVE_wspawnv
__CDECLARE(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,wspawnv,(int __mode, wchar_t const *__restrict __path, __TWARGV),(__mode,__path,))
#elif defined(__CRT_HAVE_DOS$wspawnv) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,wspawnv,(int __mode, char32_t const *__restrict __path, __T32ARGV),wspawnv,(__mode,__path,))
#elif defined(__CRT_HAVE_DOS$_wspawnv) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,wspawnv,(int __mode, char16_t const *__restrict __path, __T16ARGV),_wspawnv,(__mode,__path,))
#else /* ... */
#undef __wspawnv_defined
#endif /* !... */
#endif /* !__wspawnv_defined */
#ifndef __wspawnve_defined
#define __wspawnve_defined 1
#ifdef __CRT_HAVE_wspawnve
__CDECLARE(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,wspawnve,(int __mode, wchar_t const *__restrict __path, __TWARGV, __TWENVP),(__mode,__path,,))
#elif defined(__CRT_HAVE_DOS$wspawnve) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,wspawnve,(int __mode, char32_t const *__restrict __path, __T32ARGV, __T32ENVP),wspawnve,(__mode,__path,,))
#elif defined(__CRT_HAVE_DOS$_wspawnve) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,wspawnve,(int __mode, char16_t const *__restrict __path, __T16ARGV, __T16ENVP),_wspawnve,(__mode,__path,,))
#else /* ... */
#undef __wspawnve_defined
#endif /* !... */
#endif /* !__wspawnve_defined */
#ifndef __wspawnvp_defined
#define __wspawnvp_defined 1
#ifdef __CRT_HAVE_wspawnvp
__CDECLARE(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,wspawnvp,(int __mode, wchar_t const *__restrict __file, __TWARGV),(__mode,__file,))
#elif defined(__CRT_HAVE_DOS$wspawnvp) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,wspawnvp,(int __mode, char32_t const *__restrict __file, __T32ARGV),wspawnvp,(__mode,__file,))
#elif defined(__CRT_HAVE_DOS$_wspawnvp) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,wspawnvp,(int __mode, char16_t const *__restrict __file, __T16ARGV),_wspawnvp,(__mode,__file,))
#else /* ... */
#undef __wspawnvp_defined
#endif /* !... */
#endif /* !__wspawnvp_defined */
#ifndef __wspawnvpe_defined
#define __wspawnvpe_defined 1
#ifdef __CRT_HAVE_wspawnvpe
__CDECLARE(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,wspawnvpe,(int __mode, wchar_t const *__restrict __file, __TWARGV, __TWENVP),(__mode,__file,,))
#elif defined(__CRT_HAVE_DOS$wspawnvpe) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,wspawnvpe,(int __mode, char32_t const *__restrict __file, __T32ARGV, __T32ENVP),wspawnvpe,(__mode,__file,,))
#elif defined(__CRT_HAVE_DOS$_wspawnvpe) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,wspawnvpe,(int __mode, char16_t const *__restrict __file, __T16ARGV, __T16ENVP),_wspawnvpe,(__mode,__file,,))
#else /* ... */
#undef __wspawnvpe_defined
#endif /* !... */
#endif /* !__wspawnvpe_defined */
#ifndef __wspawnl_defined
#define __wspawnl_defined 1
#ifdef __CRT_HAVE_wspawnl
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnl)(int __mode, wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME_SAME("wspawnl");
#elif defined(__CRT_HAVE_DOS$wspawnl) && __SIZEOF_WCHAR_T__ == 4
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBKCALL wspawnl)(int __mode, char32_t const *__restrict __path, char32_t const *__args, ...) __CASMNAME_KOS("wspawnl");
#elif defined(__CRT_HAVE_DOS$_wspawnl) && __SIZEOF_WCHAR_T__ == 2
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL wspawnl)(int __mode, char16_t const *__restrict __path, char16_t const *__args, ...) __CASMNAME_DOS("_wspawnl");
#elif defined(__CRT_HAVE_wspawnv) || (defined(__CRT_HAVE_DOS$wspawnv) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wspawnv) && __SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.process/wspawnl.h>
#define wspawnl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnl))
#else /* ... */
#undef __wspawnl_defined
#endif /* !... */
#endif /* !__wspawnl_defined */
#ifndef __wspawnlp_defined
#define __wspawnlp_defined 1
#ifdef __CRT_HAVE_wspawnlp
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnlp)(int __mode, wchar_t const *__restrict __file, wchar_t const *__args, ...) __CASMNAME_SAME("wspawnlp");
#elif defined(__CRT_HAVE_DOS$wspawnlp) && __SIZEOF_WCHAR_T__ == 4
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBKCALL wspawnlp)(int __mode, char32_t const *__restrict __file, char32_t const *__args, ...) __CASMNAME_KOS("wspawnlp");
#elif defined(__CRT_HAVE_DOS$_wspawnlp) && __SIZEOF_WCHAR_T__ == 2
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL wspawnlp)(int __mode, char16_t const *__restrict __file, char16_t const *__args, ...) __CASMNAME_DOS("_wspawnlp");
#elif defined(__CRT_HAVE_wspawnvp) || (defined(__CRT_HAVE_DOS$wspawnvp) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wspawnvp) && __SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.process/wspawnlp.h>
#define wspawnlp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnlp))
#else /* ... */
#undef __wspawnlp_defined
#endif /* !... */
#endif /* !__wspawnlp_defined */
#ifndef __wspawnle_defined
#define __wspawnle_defined 1
#ifdef __CRT_HAVE_wspawnle
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnle)(int __mode, wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME_SAME("wspawnle");
#elif defined(__CRT_HAVE_DOS$wspawnle) && __SIZEOF_WCHAR_T__ == 4
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBKCALL wspawnle)(int __mode, char32_t const *__restrict __path, char32_t const *__args, ...) __CASMNAME_KOS("wspawnle");
#elif defined(__CRT_HAVE_DOS$_wspawnle) && __SIZEOF_WCHAR_T__ == 2
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL wspawnle)(int __mode, char16_t const *__restrict __path, char16_t const *__args, ...) __CASMNAME_DOS("_wspawnle");
#elif defined(__CRT_HAVE_wspawnve) || (defined(__CRT_HAVE_DOS$wspawnve) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wspawnve) && __SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.process/wspawnle.h>
#define wspawnle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnle))
#else /* ... */
#undef __wspawnle_defined
#endif /* !... */
#endif /* !__wspawnle_defined */
#ifndef __wspawnlpe_defined
#define __wspawnlpe_defined 1
#ifdef __CRT_HAVE_wspawnlpe
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnlpe)(int __mode, wchar_t const *__restrict __file, wchar_t const *__args, ...) __CASMNAME_SAME("wspawnlpe");
#elif defined(__CRT_HAVE_DOS$wspawnlpe) && __SIZEOF_WCHAR_T__ == 4
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBKCALL wspawnlpe)(int __mode, char32_t const *__restrict __file, char32_t const *__args, ...) __CASMNAME_KOS("wspawnlpe");
#elif defined(__CRT_HAVE_DOS$_wspawnle) && __SIZEOF_WCHAR_T__ == 2
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBDCALL wspawnlpe)(int __mode, char16_t const *__restrict __file, char16_t const *__args, ...) __CASMNAME_DOS("_wspawnle");
#elif defined(__CRT_HAVE_wspawnvpe) || (defined(__CRT_HAVE_DOS$wspawnvpe) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wspawnvpe) && __SIZEOF_WCHAR_T__ == 2)
#include <local/parts.wchar.process/wspawnlpe.h>
#define wspawnlpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnlpe))
#else /* ... */
#undef __wspawnlpe_defined
#endif /* !... */
#endif /* !__wspawnlpe_defined */
#ifndef __wsystem_defined
#define __wsystem_defined 1
#ifdef __CRT_HAVE_wsystem
__CDECLARE(,int,__NOTHROW_RPC,wsystem,(wchar_t const *__cmd),(__cmd))
#elif defined(__CRT_HAVE_DOS$wsystem) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(,int,__NOTHROW_RPC,wsystem,(char32_t const *__cmd),wsystem,(__cmd))
#elif defined(__CRT_HAVE_DOS$_wsystem) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(,int,__NOTHROW_RPC,wsystem,(char16_t const *__cmd),_wsystem,(__cmd))
#else /* ... */
#undef __wsystem_defined
#endif /* !... */
#endif /* !__wsystem_defined */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PARTS_WCHAR_PROCESS_H */
