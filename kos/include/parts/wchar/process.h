/* HASH CRC-32:0x833f7de3 */
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
#   define __TWARGV wchar_t const *const *__restrict ___argv
#   define __TWENVP wchar_t const *const *__restrict ___envp
#else
#   define __TWARGV wchar_t *const ___argv[__restrict_arr]
#   define __TWENVP wchar_t *const ___envp[__restrict_arr]
#endif
#endif /* !__TWARGV */
#ifndef __wexecv_defined
#define __wexecv_defined 1
#ifdef __CRT_HAVE_wexecv
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,wexecv,(wchar_t const *__restrict __path, __TWARGV),(__path,____TWARGV))
#elif defined(__CRT_HAVE__wexecv)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,wexecv,(wchar_t const *__restrict __path, __TWARGV),_wexecv,(__path,____TWARGV))
#else /* LIBC: wexecv */
#undef __wexecv_defined
#endif /* wexecv... */
#endif /* !__wexecv_defined */
#ifndef __wexecve_defined
#define __wexecve_defined 1
#ifdef __CRT_HAVE_wexecve
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,wexecve,(wchar_t const *__restrict __path, __TWARGV, __TWENVP),(__path,____TWARGV,____TWENVP))
#elif defined(__CRT_HAVE__wexecve)
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,wexecve,(wchar_t const *__restrict __path, __TWARGV, __TWENVP),_wexecve,(__path,____TWARGV,____TWENVP))
#else /* LIBC: wexecve */
#undef __wexecve_defined
#endif /* wexecve... */
#endif /* !__wexecve_defined */
#ifndef __wexecvp_defined
#define __wexecvp_defined 1
#ifdef __CRT_HAVE_wexecvp
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,wexecvp,(wchar_t const *__restrict __file, __TWARGV),(__file,____TWARGV))
#elif defined(__CRT_HAVE__wexecvp)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,wexecvp,(wchar_t const *__restrict __file, __TWARGV),_wexecvp,(__file,____TWARGV))
#else /* LIBC: wexecvp */
#undef __wexecvp_defined
#endif /* wexecvp... */
#endif /* !__wexecvp_defined */
#ifndef __wexecvpe_defined
#define __wexecvpe_defined 1
#ifdef __CRT_HAVE_wexecvpe
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,wexecvpe,(wchar_t const *__restrict __file, __TWARGV, __TWENVP),(__file,____TWARGV,____TWENVP))
#elif defined(__CRT_HAVE__wexecvpe)
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,wexecvpe,(wchar_t const *__restrict __file, __TWARGV, __TWENVP),_wexecvpe,(__file,____TWARGV,____TWENVP))
#else /* LIBC: wexecvpe */
#undef __wexecvpe_defined
#endif /* wexecvpe... */
#endif /* !__wexecvpe_defined */
#ifndef __wexecl_defined
#define __wexecl_defined 1
#ifdef __CRT_HAVE_wexecl
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexecl)(wchar_t const *__restrict __path, wchar_t const *__args, ... /*, (wchar_t *)NULL*/) __CASMNAME_SAME("wexecl");
#elif defined(__CRT_HAVE__wexecl) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexecl)(wchar_t const *__restrict __path, wchar_t const *__args, ... /*, (wchar_t *)NULL*/) __CASMNAME("_wexecl");
#elif defined(__CRT_HAVE_wexecv) || defined(__CRT_HAVE__wexecv)
#include <local/parts.wchar.process/wexecl.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wexecl)
#else /* __cplusplus */
#define wexecl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexecl))
#endif /* !__cplusplus */
#else /* CUSTOM: wexecl */
#undef __wexecl_defined
#endif /* wexecl... */
#endif /* !__wexecl_defined */
#ifndef __wexecle_defined
#define __wexecle_defined 1
#ifdef __CRT_HAVE_wexecle
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexecle)(wchar_t const *__restrict __path, wchar_t const *__args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) __CASMNAME_SAME("wexecle");
#elif defined(__CRT_HAVE__wexecle) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexecle)(wchar_t const *__restrict __path, wchar_t const *__args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) __CASMNAME("_wexecle");
#elif defined(__CRT_HAVE_wexecve) || defined(__CRT_HAVE__wexecve)
#include <local/parts.wchar.process/wexecle.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wexecle)
#else /* __cplusplus */
#define wexecle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexecle))
#endif /* !__cplusplus */
#else /* CUSTOM: wexecle */
#undef __wexecle_defined
#endif /* wexecle... */
#endif /* !__wexecle_defined */
#ifndef __wexeclp_defined
#define __wexeclp_defined 1
#ifdef __CRT_HAVE_wexeclp
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexeclp)(wchar_t const *__restrict __file, wchar_t const *__args, ... /*, (wchar_t *)NULL*/) __CASMNAME_SAME("wexeclp");
#elif defined(__CRT_HAVE__wexeclp) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexeclp)(wchar_t const *__restrict __file, wchar_t const *__args, ... /*, (wchar_t *)NULL*/) __CASMNAME("_wexeclp");
#elif defined(__CRT_HAVE_wexecvp) || defined(__CRT_HAVE__wexecvp)
#include <local/parts.wchar.process/wexeclp.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wexeclp)
#else /* __cplusplus */
#define wexeclp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexeclp))
#endif /* !__cplusplus */
#else /* CUSTOM: wexeclp */
#undef __wexeclp_defined
#endif /* wexeclp... */
#endif /* !__wexeclp_defined */
#ifndef __wexeclpe_defined
#define __wexeclpe_defined 1
#ifdef __CRT_HAVE_wexeclpe
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexeclpe)(wchar_t const *__restrict __file, wchar_t const *__args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) __CASMNAME_SAME("wexeclpe");
#elif defined(__CRT_HAVE__wexecle) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexeclpe)(wchar_t const *__restrict __file, wchar_t const *__args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) __CASMNAME("_wexecle");
#elif defined(__CRT_HAVE_wexecvpe) || defined(__CRT_HAVE__wexecvpe)
#include <local/parts.wchar.process/wexeclpe.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wexeclpe)
#else /* __cplusplus */
#define wexeclpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexeclpe))
#endif /* !__cplusplus */
#else /* CUSTOM: wexeclpe */
#undef __wexeclpe_defined
#endif /* wexeclpe... */
#endif /* !__wexeclpe_defined */
#ifndef __wspawnv_defined
#define __wspawnv_defined 1
#ifdef __CRT_HAVE_wspawnv
__CDECLARE(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,wspawnv,(int __mode, wchar_t const *__restrict __path, __TWARGV),(__mode,__path,____TWARGV))
#elif defined(__CRT_HAVE__wspawnv)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,wspawnv,(int __mode, wchar_t const *__restrict __path, __TWARGV),_wspawnv,(__mode,__path,____TWARGV))
#else /* LIBC: wspawnv */
#undef __wspawnv_defined
#endif /* wspawnv... */
#endif /* !__wspawnv_defined */
#ifndef __wspawnve_defined
#define __wspawnve_defined 1
#ifdef __CRT_HAVE_wspawnve
__CDECLARE(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,wspawnve,(int __mode, wchar_t const *__restrict __path, __TWARGV, __TWENVP),(__mode,__path,____TWARGV,____TWENVP))
#elif defined(__CRT_HAVE__wspawnve)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,wspawnve,(int __mode, wchar_t const *__restrict __path, __TWARGV, __TWENVP),_wspawnve,(__mode,__path,____TWARGV,____TWENVP))
#else /* LIBC: wspawnve */
#undef __wspawnve_defined
#endif /* wspawnve... */
#endif /* !__wspawnve_defined */
#ifndef __wspawnvp_defined
#define __wspawnvp_defined 1
#ifdef __CRT_HAVE_wspawnvp
__CDECLARE(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,wspawnvp,(int __mode, wchar_t const *__restrict __file, __TWARGV),(__mode,__file,____TWARGV))
#elif defined(__CRT_HAVE__wspawnvp)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,wspawnvp,(int __mode, wchar_t const *__restrict __file, __TWARGV),_wspawnvp,(__mode,__file,____TWARGV))
#else /* LIBC: wspawnvp */
#undef __wspawnvp_defined
#endif /* wspawnvp... */
#endif /* !__wspawnvp_defined */
#ifndef __wspawnvpe_defined
#define __wspawnvpe_defined 1
#ifdef __CRT_HAVE_wspawnvpe
__CDECLARE(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,wspawnvpe,(int __mode, wchar_t const *__restrict __file, __TWARGV, __TWENVP),(__mode,__file,____TWARGV,____TWENVP))
#elif defined(__CRT_HAVE__wspawnvpe)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,wspawnvpe,(int __mode, wchar_t const *__restrict __file, __TWARGV, __TWENVP),_wspawnvpe,(__mode,__file,____TWARGV,____TWENVP))
#else /* LIBC: wspawnvpe */
#undef __wspawnvpe_defined
#endif /* wspawnvpe... */
#endif /* !__wspawnvpe_defined */
#ifndef __wspawnl_defined
#define __wspawnl_defined 1
#ifdef __CRT_HAVE_wspawnl
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnl)(int __mode, wchar_t const *__restrict __path, wchar_t const *__args, ... /*, (wchar_t *)NULL*/) __CASMNAME_SAME("wspawnl");
#elif defined(__CRT_HAVE__wspawnl) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnl)(int __mode, wchar_t const *__restrict __path, wchar_t const *__args, ... /*, (wchar_t *)NULL*/) __CASMNAME("_wspawnl");
#elif defined(__CRT_HAVE_wspawnv) || defined(__CRT_HAVE__wspawnv)
#include <local/parts.wchar.process/wspawnl.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wspawnl)
#else /* __cplusplus */
#define wspawnl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnl))
#endif /* !__cplusplus */
#else /* CUSTOM: wspawnl */
#undef __wspawnl_defined
#endif /* wspawnl... */
#endif /* !__wspawnl_defined */
#ifndef __wspawnle_defined
#define __wspawnle_defined 1
#ifdef __CRT_HAVE_wspawnle
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnle)(int __mode, wchar_t const *__restrict __path, wchar_t const *__args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) __CASMNAME_SAME("wspawnle");
#elif defined(__CRT_HAVE__wspawnle) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnle)(int __mode, wchar_t const *__restrict __path, wchar_t const *__args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) __CASMNAME("_wspawnle");
#elif defined(__CRT_HAVE_wspawnve) || defined(__CRT_HAVE__wspawnve)
#include <local/parts.wchar.process/wspawnle.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wspawnle)
#else /* __cplusplus */
#define wspawnle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnle))
#endif /* !__cplusplus */
#else /* CUSTOM: wspawnle */
#undef __wspawnle_defined
#endif /* wspawnle... */
#endif /* !__wspawnle_defined */
#ifndef __wspawnlp_defined
#define __wspawnlp_defined 1
#ifdef __CRT_HAVE_wspawnlp
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnlp)(int __mode, wchar_t const *__restrict __file, wchar_t const *__args, ... /*, (wchar_t *)NULL*/) __CASMNAME_SAME("wspawnlp");
#elif defined(__CRT_HAVE__wspawnlp) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnlp)(int __mode, wchar_t const *__restrict __file, wchar_t const *__args, ... /*, (wchar_t *)NULL*/) __CASMNAME("_wspawnlp");
#elif defined(__CRT_HAVE_wspawnvp) || defined(__CRT_HAVE__wspawnvp)
#include <local/parts.wchar.process/wspawnlp.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wspawnlp)
#else /* __cplusplus */
#define wspawnlp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnlp))
#endif /* !__cplusplus */
#else /* CUSTOM: wspawnlp */
#undef __wspawnlp_defined
#endif /* wspawnlp... */
#endif /* !__wspawnlp_defined */
#ifndef __wspawnlpe_defined
#define __wspawnlpe_defined 1
#ifdef __CRT_HAVE_wspawnlpe
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnlpe)(int __mode, wchar_t const *__restrict __file, wchar_t const *__args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) __CASMNAME_SAME("wspawnlpe");
#elif defined(__CRT_HAVE__wspawnle) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnlpe)(int __mode, wchar_t const *__restrict __file, wchar_t const *__args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) __CASMNAME("_wspawnle");
#elif defined(__CRT_HAVE_wspawnvpe) || defined(__CRT_HAVE__wspawnvpe)
#include <local/parts.wchar.process/wspawnlpe.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wspawnlpe)
#else /* __cplusplus */
#define wspawnlpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnlpe))
#endif /* !__cplusplus */
#else /* CUSTOM: wspawnlpe */
#undef __wspawnlpe_defined
#endif /* wspawnlpe... */
#endif /* !__wspawnlpe_defined */
#ifndef __wsystem_defined
#define __wsystem_defined 1
#ifdef __CRT_HAVE_wsystem
__CDECLARE(,int,__NOTHROW_RPC,wsystem,(wchar_t const *__cmd),(__cmd))
#elif defined(__CRT_HAVE__wsystem)
__CREDIRECT(,int,__NOTHROW_RPC,wsystem,(wchar_t const *__cmd),_wsystem,(__cmd))
#else /* LIBC: wsystem */
#undef __wsystem_defined
#endif /* wsystem... */
#endif /* !__wsystem_defined */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PARTS_WCHAR_PROCESS_H */
