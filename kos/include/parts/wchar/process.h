/* HASH CRC-32:0xa56f8965 */
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
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,wexecv,(wchar_t const *__restrict __path, __TWARGV),(__path,___argv))
#elif defined(__CRT_HAVE__wexecv)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,wexecv,(wchar_t const *__restrict __path, __TWARGV),_wexecv,(__path,___argv))
#else /* ... */
#undef __wexecv_defined
#endif /* !... */
#endif /* !__wexecv_defined */
#ifndef __wexecve_defined
#define __wexecve_defined 1
#ifdef __CRT_HAVE_wexecve
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,wexecve,(wchar_t const *__restrict __path, __TWARGV, __TWENVP),(__path,___argv,___envp))
#elif defined(__CRT_HAVE__wexecve)
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,wexecve,(wchar_t const *__restrict __path, __TWARGV, __TWENVP),_wexecve,(__path,___argv,___envp))
#else /* ... */
#undef __wexecve_defined
#endif /* !... */
#endif /* !__wexecve_defined */
#ifndef __wexecvp_defined
#define __wexecvp_defined 1
#ifdef __CRT_HAVE_wexecvp
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,wexecvp,(wchar_t const *__restrict __file, __TWARGV),(__path,___argv))
#elif defined(__CRT_HAVE__wexecvp)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,wexecvp,(wchar_t const *__restrict __file, __TWARGV),_wexecvp,(__path,___argv))
#else /* ... */
#undef __wexecvp_defined
#endif /* !... */
#endif /* !__wexecvp_defined */
#ifndef __wexecvpe_defined
#define __wexecvpe_defined 1
#ifdef __CRT_HAVE_wexecvpe
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,wexecvpe,(wchar_t const *__restrict __file, __TWARGV, __TWENVP),(__path,___argv,___envp))
#elif defined(__CRT_HAVE__wexecvpe)
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,wexecvpe,(wchar_t const *__restrict __file, __TWARGV, __TWENVP),_wexecvpe,(__path,___argv,___envp))
#else /* ... */
#undef __wexecvpe_defined
#endif /* !... */
#endif /* !__wexecvpe_defined */
#ifndef __wexecl_defined
#define __wexecl_defined 1
#ifdef __CRT_HAVE_wexecl
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexecl)(wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME_SAME("wexecl");
#elif defined(__CRT_HAVE__wexecl)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexecl)(wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME("_wexecl");
#elif defined(__CRT_HAVE_wexecv) || defined(__CRT_HAVE__wexecv)
#include <local/parts.wchar.process/wexecl.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wexecl)
#else /* __cplusplus */
#define wexecl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexecl))
#endif /* !__cplusplus */
#else /* ... */
#undef __wexecl_defined
#endif /* !... */
#endif /* !__wexecl_defined */
#ifndef __wexeclp_defined
#define __wexeclp_defined 1
#ifdef __CRT_HAVE_wexeclp
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexeclp)(wchar_t const *__restrict __file, wchar_t const *__args, ...) __CASMNAME_SAME("wexeclp");
#elif defined(__CRT_HAVE__wexeclp)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexeclp)(wchar_t const *__restrict __file, wchar_t const *__args, ...) __CASMNAME("_wexeclp");
#elif defined(__CRT_HAVE_wexecvp) || defined(__CRT_HAVE__wexecvp)
#include <local/parts.wchar.process/wexeclp.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wexeclp)
#else /* __cplusplus */
#define wexeclp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexeclp))
#endif /* !__cplusplus */
#else /* ... */
#undef __wexeclp_defined
#endif /* !... */
#endif /* !__wexeclp_defined */
#ifndef __wexecle_defined
#define __wexecle_defined 1
#ifdef __CRT_HAVE_wexecle
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexecle)(wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME_SAME("wexecle");
#elif defined(__CRT_HAVE__wexecle)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexecle)(wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME("_wexecle");
#elif defined(__CRT_HAVE_wexecve) || defined(__CRT_HAVE__wexecve)
#include <local/parts.wchar.process/wexecle.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wexecle)
#else /* __cplusplus */
#define wexecle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexecle))
#endif /* !__cplusplus */
#else /* ... */
#undef __wexecle_defined
#endif /* !... */
#endif /* !__wexecle_defined */
#ifndef __wexeclpe_defined
#define __wexeclpe_defined 1
#ifdef __CRT_HAVE_wexeclpe
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexeclpe)(wchar_t const *__restrict __file, wchar_t const *__args, ...) __CASMNAME_SAME("wexeclpe");
#elif defined(__CRT_HAVE__wexeclpe)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexeclpe)(wchar_t const *__restrict __file, wchar_t const *__args, ...) __CASMNAME("_wexeclpe");
#elif defined(__CRT_HAVE_wexecvpe) || defined(__CRT_HAVE__wexecvpe)
#include <local/parts.wchar.process/wexeclpe.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wexeclpe)
#else /* __cplusplus */
#define wexeclpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexeclpe))
#endif /* !__cplusplus */
#else /* ... */
#undef __wexeclpe_defined
#endif /* !... */
#endif /* !__wexeclpe_defined */
#ifndef __wspawnv_defined
#define __wspawnv_defined 1
#ifdef __CRT_HAVE_wspawnv
__CDECLARE(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,wspawnv,(int __mode, wchar_t const *__restrict __path, __TWARGV),(__mode,__path,___argv))
#elif defined(__CRT_HAVE__wspawnv)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,wspawnv,(int __mode, wchar_t const *__restrict __path, __TWARGV),_wspawnv,(__mode,__path,___argv))
#else /* ... */
#undef __wspawnv_defined
#endif /* !... */
#endif /* !__wspawnv_defined */
#ifndef __wspawnve_defined
#define __wspawnve_defined 1
#ifdef __CRT_HAVE_wspawnve
__CDECLARE(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,wspawnve,(int __mode, wchar_t const *__restrict __path, __TWARGV, __TWENVP),(__mode,__path,___argv,___envp))
#elif defined(__CRT_HAVE__wspawnve)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,wspawnve,(int __mode, wchar_t const *__restrict __path, __TWARGV, __TWENVP),_wspawnve,(__mode,__path,___argv,___envp))
#else /* ... */
#undef __wspawnve_defined
#endif /* !... */
#endif /* !__wspawnve_defined */
#ifndef __wspawnvp_defined
#define __wspawnvp_defined 1
#ifdef __CRT_HAVE_wspawnvp
__CDECLARE(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,wspawnvp,(int __mode, wchar_t const *__restrict __file, __TWARGV),(__mode,__file,___argv))
#elif defined(__CRT_HAVE__wspawnvp)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,wspawnvp,(int __mode, wchar_t const *__restrict __file, __TWARGV),_wspawnvp,(__mode,__file,___argv))
#else /* ... */
#undef __wspawnvp_defined
#endif /* !... */
#endif /* !__wspawnvp_defined */
#ifndef __wspawnvpe_defined
#define __wspawnvpe_defined 1
#ifdef __CRT_HAVE_wspawnvpe
__CDECLARE(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,wspawnvpe,(int __mode, wchar_t const *__restrict __file, __TWARGV, __TWENVP),(__mode,__file,___argv,___envp))
#elif defined(__CRT_HAVE__wspawnvpe)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,wspawnvpe,(int __mode, wchar_t const *__restrict __file, __TWARGV, __TWENVP),_wspawnvpe,(__mode,__file,___argv,___envp))
#else /* ... */
#undef __wspawnvpe_defined
#endif /* !... */
#endif /* !__wspawnvpe_defined */
#ifndef __wspawnl_defined
#define __wspawnl_defined 1
#ifdef __CRT_HAVE_wspawnl
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnl)(int __mode, wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME_SAME("wspawnl");
#elif defined(__CRT_HAVE__wspawnl)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnl)(int __mode, wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME("_wspawnl");
#elif defined(__CRT_HAVE_wspawnv) || defined(__CRT_HAVE__wspawnv)
#include <local/parts.wchar.process/wspawnl.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wspawnl)
#else /* __cplusplus */
#define wspawnl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnl))
#endif /* !__cplusplus */
#else /* ... */
#undef __wspawnl_defined
#endif /* !... */
#endif /* !__wspawnl_defined */
#ifndef __wspawnlp_defined
#define __wspawnlp_defined 1
#ifdef __CRT_HAVE_wspawnlp
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnlp)(int __mode, wchar_t const *__restrict __file, wchar_t const *__args, ...) __CASMNAME_SAME("wspawnlp");
#elif defined(__CRT_HAVE__wspawnlp)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnlp)(int __mode, wchar_t const *__restrict __file, wchar_t const *__args, ...) __CASMNAME("_wspawnlp");
#elif defined(__CRT_HAVE_wspawnvp) || defined(__CRT_HAVE__wspawnvp)
#include <local/parts.wchar.process/wspawnlp.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wspawnlp)
#else /* __cplusplus */
#define wspawnlp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnlp))
#endif /* !__cplusplus */
#else /* ... */
#undef __wspawnlp_defined
#endif /* !... */
#endif /* !__wspawnlp_defined */
#ifndef __wspawnle_defined
#define __wspawnle_defined 1
#ifdef __CRT_HAVE_wspawnle
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnle)(int __mode, wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME_SAME("wspawnle");
#elif defined(__CRT_HAVE__wspawnle)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnle)(int __mode, wchar_t const *__restrict __path, wchar_t const *__args, ...) __CASMNAME("_wspawnle");
#elif defined(__CRT_HAVE_wspawnve) || defined(__CRT_HAVE__wspawnve)
#include <local/parts.wchar.process/wspawnle.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wspawnle)
#else /* __cplusplus */
#define wspawnle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnle))
#endif /* !__cplusplus */
#else /* ... */
#undef __wspawnle_defined
#endif /* !... */
#endif /* !__wspawnle_defined */
#ifndef __wspawnlpe_defined
#define __wspawnlpe_defined 1
#ifdef __CRT_HAVE_wspawnlpe
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnlpe)(int __mode, wchar_t const *__restrict __file, wchar_t const *__args, ...) __CASMNAME_SAME("wspawnlpe");
#elif defined(__CRT_HAVE__wspawnlpe)
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnlpe)(int __mode, wchar_t const *__restrict __file, wchar_t const *__args, ...) __CASMNAME("_wspawnlpe");
#elif defined(__CRT_HAVE_wspawnvpe) || defined(__CRT_HAVE__wspawnvpe)
#include <local/parts.wchar.process/wspawnlpe.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wspawnlpe)
#else /* __cplusplus */
#define wspawnlpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnlpe))
#endif /* !__cplusplus */
#else /* ... */
#undef __wspawnlpe_defined
#endif /* !... */
#endif /* !__wspawnlpe_defined */
#ifndef __wsystem_defined
#define __wsystem_defined 1
#ifdef __CRT_HAVE_wsystem
__CDECLARE(,int,__NOTHROW_RPC,wsystem,(wchar_t const *__cmd),(__cmd))
#elif defined(__CRT_HAVE__wsystem)
__CREDIRECT(,int,__NOTHROW_RPC,wsystem,(wchar_t const *__cmd),_wsystem,(__cmd))
#else /* ... */
#undef __wsystem_defined
#endif /* !... */
#endif /* !__wsystem_defined */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PARTS_WCHAR_PROCESS_H */
