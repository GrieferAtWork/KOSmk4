/* HASH CRC-32:0xa9446631 */
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
#ifndef __local_c16execlpe_defined
#define __local_c16execlpe_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_wexecvpe) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wexecvpe) || (defined(__CRT_HAVE__wexecvpe) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wexecvpe)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c16execvpe from parts.uchar.process */
#ifndef __local___localdep_c16execvpe_defined
#define __local___localdep_c16execvpe_defined 1
#if defined(__CRT_HAVE_wexecvpe) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__NAMESPACE_LOCAL_END
#include <features.h>
#ifndef __TARGV
#ifdef __USE_DOS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS */
#endif /* !__TARGV */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_c16execvpe,(__CHAR16_TYPE__ const *__restrict __file, __T16ARGV, __T16ENVP),wexecvpe,(__path,___argv,___envp))
#elif defined(__CRT_HAVE_DOS$wexecvpe)
__NAMESPACE_LOCAL_END
#include <features.h>
#ifndef __TARGV
#ifdef __USE_DOS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS */
#endif /* !__TARGV */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_c16execvpe,(__CHAR16_TYPE__ const *__restrict __file, __T16ARGV, __T16ENVP),wexecvpe,(__path,___argv,___envp))
#elif defined(__CRT_HAVE__wexecvpe) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__NAMESPACE_LOCAL_END
#include <features.h>
#ifndef __TARGV
#ifdef __USE_DOS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS */
#endif /* !__TARGV */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_c16execvpe,(__CHAR16_TYPE__ const *__restrict __file, __T16ARGV, __T16ENVP),_wexecvpe,(__path,___argv,___envp))
#elif defined(__CRT_HAVE_DOS$_wexecvpe)
__NAMESPACE_LOCAL_END
#include <features.h>
#ifndef __TARGV
#ifdef __USE_DOS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS */
#endif /* !__TARGV */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_c16execvpe,(__CHAR16_TYPE__ const *__restrict __file, __T16ARGV, __T16ENVP),_wexecvpe,(__path,___argv,___envp))
#else /* ... */
#undef __local___localdep_c16execvpe_defined
#endif /* !... */
#endif /* !__local___localdep_c16execvpe_defined */
__NAMESPACE_LOCAL_END
#include <parts/redirect-exec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16execlpe) __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__VLIBDCALL __LIBC_LOCAL_NAME(c16execlpe))(__CHAR16_TYPE__ const *__restrict __file, __CHAR16_TYPE__ const *__args, ...) {
	__REDIRECT_EXECLE(__CHAR16_TYPE__, __localdep_c16execvpe, __file, __args)
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16execlpe_defined
#define __local___localdep_c16execlpe_defined 1
#define __localdep_c16execlpe __LIBC_LOCAL_NAME(c16execlpe)
#endif /* !__local___localdep_c16execlpe_defined */
#else /* (__CRT_HAVE_wexecvpe && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$wexecvpe || (__CRT_HAVE__wexecvpe && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$_wexecvpe */
#undef __local_c16execlpe_defined
#endif /* (!__CRT_HAVE_wexecvpe || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$wexecvpe && (!__CRT_HAVE__wexecvpe || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$_wexecvpe */
#endif /* !__local_c16execlpe_defined */
