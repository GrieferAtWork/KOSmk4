/* HASH CRC-32:0xb493fb39 */
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
#ifndef __local_c16execle_defined
#define __local_c16execle_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_wexecve) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wexecve) || (defined(__CRT_HAVE__wexecve) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wexecve)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c16execve from parts.uchar.process */
#ifndef __local___localdep_c16execve_defined
#define __local___localdep_c16execve_defined 1
#if defined(__CRT_HAVE_wexecve) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
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
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_c16execve,(__CHAR16_TYPE__ const *__restrict __path, __T16ARGV, __T16ENVP),wexecve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE_DOS$wexecve)
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
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_c16execve,(__CHAR16_TYPE__ const *__restrict __path, __T16ARGV, __T16ENVP),wexecve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE__wexecve) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
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
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_c16execve,(__CHAR16_TYPE__ const *__restrict __path, __T16ARGV, __T16ENVP),_wexecve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE_DOS$_wexecve)
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
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_c16execve,(__CHAR16_TYPE__ const *__restrict __path, __T16ARGV, __T16ENVP),_wexecve,(__path,___argv,___envp))
#else /* ... */
#undef __local___localdep_c16execve_defined
#endif /* !... */
#endif /* !__local___localdep_c16execve_defined */
__NAMESPACE_LOCAL_END
#include <parts/redirect-exec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16execle) __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__VLIBDCALL __LIBC_LOCAL_NAME(c16execle))(__CHAR16_TYPE__ const *__restrict __path, __CHAR16_TYPE__ const *__args, ...) {
	__REDIRECT_EXECLE(__CHAR16_TYPE__, __localdep_c16execve, __path, __args)
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16execle_defined
#define __local___localdep_c16execle_defined 1
#define __localdep_c16execle __LIBC_LOCAL_NAME(c16execle)
#endif /* !__local___localdep_c16execle_defined */
#else /* (__CRT_HAVE_wexecve && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$wexecve || (__CRT_HAVE__wexecve && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$_wexecve */
#undef __local_c16execle_defined
#endif /* (!__CRT_HAVE_wexecve || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$wexecve && (!__CRT_HAVE__wexecve || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$_wexecve */
#endif /* !__local_c16execle_defined */
