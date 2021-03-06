/* HASH CRC-32:0x461b75f7 */
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
#ifndef __local_c32spawnle_defined
#define __local_c32spawnle_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_wspawnve) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wspawnve) || (defined(__CRT_HAVE__wspawnve) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_wspawnve)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c32spawnve from parts.uchar.process */
#ifndef __local___localdep_c32spawnve_defined
#define __local___localdep_c32spawnve_defined 1
#if defined(__CRT_HAVE_wspawnve) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
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
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__localdep_c32spawnve,(__STDC_INT_AS_UINT_T __mode, __CHAR32_TYPE__ const *__restrict __path, __T32ARGV, __T32ENVP),wspawnve,(__mode,__path,___argv,___envp))
#elif defined(__CRT_HAVE_KOS$wspawnve)
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
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__localdep_c32spawnve,(__STDC_INT_AS_UINT_T __mode, __CHAR32_TYPE__ const *__restrict __path, __T32ARGV, __T32ENVP),wspawnve,(__mode,__path,___argv,___envp))
#elif defined(__CRT_HAVE__wspawnve) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
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
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__localdep_c32spawnve,(__STDC_INT_AS_UINT_T __mode, __CHAR32_TYPE__ const *__restrict __path, __T32ARGV, __T32ENVP),_wspawnve,(__mode,__path,___argv,___envp))
#elif defined(__CRT_HAVE_KOS$_wspawnve)
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
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__localdep_c32spawnve,(__STDC_INT_AS_UINT_T __mode, __CHAR32_TYPE__ const *__restrict __path, __T32ARGV, __T32ENVP),_wspawnve,(__mode,__path,___argv,___envp))
#else /* ... */
#undef __local___localdep_c32spawnve_defined
#endif /* !... */
#endif /* !__local___localdep_c32spawnve_defined */
__NAMESPACE_LOCAL_END
#include <parts/redirect-exec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32spawnle) __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t
__NOTHROW_RPC(__VLIBKCALL __LIBC_LOCAL_NAME(c32spawnle))(__STDC_INT_AS_UINT_T __mode, __CHAR32_TYPE__ const *__restrict __path, __CHAR32_TYPE__ const *__args, ...) {
	__REDIRECT_SPAWNLE(__CHAR32_TYPE__, __localdep_c32spawnve, __mode, __path, __args)
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32spawnle_defined
#define __local___localdep_c32spawnle_defined 1
#define __localdep_c32spawnle __LIBC_LOCAL_NAME(c32spawnle)
#endif /* !__local___localdep_c32spawnle_defined */
#else /* (__CRT_HAVE_wspawnve && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$wspawnve || (__CRT_HAVE__wspawnve && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$_wspawnve */
#undef __local_c32spawnle_defined
#endif /* (!__CRT_HAVE_wspawnve || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$wspawnve && (!__CRT_HAVE__wspawnve || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$_wspawnve */
#endif /* !__local_c32spawnle_defined */
