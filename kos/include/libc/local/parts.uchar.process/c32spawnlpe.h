/* HASH CRC-32:0xc80098b6 */
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
#ifndef __local_c32spawnlpe_defined
#define __local_c32spawnlpe_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_wspawnvpe) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wspawnvpe) || (defined(__CRT_HAVE__wspawnvpe) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_wspawnvpe)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32spawnvpe_defined
#define __local___localdep_c32spawnvpe_defined
#if defined(__CRT_HAVE_wspawnvpe) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
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
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__localdep_c32spawnvpe,(__STDC_INT_AS_UINT_T __mode, __CHAR32_TYPE__ const *__restrict __file, __T32ARGV, __T32ENVP),wspawnvpe,(__mode,__file,___argv,___envp))
#elif defined(__CRT_HAVE_KOS$wspawnvpe)
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
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__localdep_c32spawnvpe,(__STDC_INT_AS_UINT_T __mode, __CHAR32_TYPE__ const *__restrict __file, __T32ARGV, __T32ENVP),wspawnvpe,(__mode,__file,___argv,___envp))
#elif defined(__CRT_HAVE__wspawnvpe) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
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
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__localdep_c32spawnvpe,(__STDC_INT_AS_UINT_T __mode, __CHAR32_TYPE__ const *__restrict __file, __T32ARGV, __T32ENVP),_wspawnvpe,(__mode,__file,___argv,___envp))
#elif defined(__CRT_HAVE_KOS$_wspawnvpe)
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
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__localdep_c32spawnvpe,(__STDC_INT_AS_UINT_T __mode, __CHAR32_TYPE__ const *__restrict __file, __T32ARGV, __T32ENVP),_wspawnvpe,(__mode,__file,___argv,___envp))
#else /* ... */
#undef __local___localdep_c32spawnvpe_defined
#endif /* !... */
#endif /* !__local___localdep_c32spawnvpe_defined */
__NAMESPACE_LOCAL_END
#include <parts/redirect-exec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32spawnlpe) __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t
__NOTHROW_RPC(__VLIBKCALL __LIBC_LOCAL_NAME(c32spawnlpe))(__STDC_INT_AS_UINT_T __mode, __CHAR32_TYPE__ const *__restrict __file, __CHAR32_TYPE__ const *__args, ...) {
	__REDIRECT_SPAWNLE(__CHAR32_TYPE__, (__NAMESPACE_LOCAL_SYM __localdep_c32spawnvpe), __mode, __file, __args)
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32spawnlpe_defined
#define __local___localdep_c32spawnlpe_defined
#define __localdep_c32spawnlpe __LIBC_LOCAL_NAME(c32spawnlpe)
#endif /* !__local___localdep_c32spawnlpe_defined */
#else /* (__CRT_HAVE_wspawnvpe && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$wspawnvpe || (__CRT_HAVE__wspawnvpe && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$_wspawnvpe */
#undef __local_c32spawnlpe_defined
#endif /* (!__CRT_HAVE_wspawnvpe || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$wspawnvpe && (!__CRT_HAVE__wspawnvpe || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$_wspawnvpe */
#endif /* !__local_c32spawnlpe_defined */
