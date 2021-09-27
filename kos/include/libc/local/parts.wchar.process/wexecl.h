/* HASH CRC-32:0xaa92f37a */
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
#ifndef __local_wexecl_defined
#define __local_wexecl_defined
#include <__crt.h>
#if defined(__CRT_HAVE_wexecv) || defined(__CRT_HAVE__wexecv)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wexecv_defined
#define __local___localdep_wexecv_defined
#ifdef __CRT_HAVE_wexecv
__NAMESPACE_LOCAL_END
#include <features.h>
#ifndef __TARGV
#ifdef __USE_DOS_ALTERATIONS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS_ALTERATIONS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__TARGV */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_wexecv,(__WCHAR_TYPE__ const *__restrict __path, __TWARGV),wexecv,(__path,___argv))
#elif defined(__CRT_HAVE__wexecv)
__NAMESPACE_LOCAL_END
#include <features.h>
#ifndef __TARGV
#ifdef __USE_DOS_ALTERATIONS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS_ALTERATIONS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__TARGV */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_wexecv,(__WCHAR_TYPE__ const *__restrict __path, __TWARGV),_wexecv,(__path,___argv))
#else /* ... */
#undef __local___localdep_wexecv_defined
#endif /* !... */
#endif /* !__local___localdep_wexecv_defined */
__NAMESPACE_LOCAL_END
#include <parts/redirect-exec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wexecl) __ATTR_SENTINEL __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(wexecl))(__WCHAR_TYPE__ const *__restrict __path, __WCHAR_TYPE__ const *__args, ...) {
	__REDIRECT_EXECL(__WCHAR_TYPE__, (__NAMESPACE_LOCAL_SYM __localdep_wexecv), __path, __args)
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wexecl_defined
#define __local___localdep_wexecl_defined
#define __localdep_wexecl __LIBC_LOCAL_NAME(wexecl)
#endif /* !__local___localdep_wexecl_defined */
#else /* __CRT_HAVE_wexecv || __CRT_HAVE__wexecv */
#undef __local_wexecl_defined
#endif /* !__CRT_HAVE_wexecv && !__CRT_HAVE__wexecv */
#endif /* !__local_wexecl_defined */
