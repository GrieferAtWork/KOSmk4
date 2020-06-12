/* HASH CRC-32:0x6653e0b7 */
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
#ifndef __local_wspawnle_defined
#define __local_wspawnle_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_wspawnve) || (defined(__CRT_HAVE_DOS$wspawnve) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wspawnve) && __SIZEOF_WCHAR_T__ == 2)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: wspawnve from parts.wchar.process */
#ifndef __local___localdep_wspawnve_defined
#define __local___localdep_wspawnve_defined 1
#ifdef __CRT_HAVE_wspawnve
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__localdep_wspawnve,(int __mode, __WCHAR_TYPE__ const *__restrict __path, __TWARGV, __TWENVP),wspawnve,(__mode,__path,___argv,___envp))
#elif defined(__CRT_HAVE_DOS$wspawnve) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__localdep_wspawnve,(int __mode, __CHAR32_TYPE__ const *__restrict __path, __T32ARGV, __T32ENVP),wspawnve,(__mode,__path,___argv,___envp))
#elif defined(__CRT_HAVE_DOS$_wspawnve) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__localdep_wspawnve,(int __mode, __CHAR16_TYPE__ const *__restrict __path, __T16ARGV, __T16ENVP),_wspawnve,(__mode,__path,___argv,___envp))
#else /* ... */
#undef __local___localdep_wspawnve_defined
#endif /* !... */
#endif /* !__local___localdep_wspawnve_defined */
__NAMESPACE_LOCAL_END
#include <parts/redirect-exec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wspawnle) __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(wspawnle))(int __mode, __WCHAR_TYPE__ const *__restrict __path, __WCHAR_TYPE__ const *__args, ...) {
	__REDIRECT_SPAWNLE(__WCHAR_TYPE__, __localdep_wspawnve, __mode, __path, __args)
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wspawnle_defined
#define __local___localdep_wspawnle_defined 1
#define __localdep_wspawnle __LIBC_LOCAL_NAME(wspawnle)
#endif /* !__local___localdep_wspawnle_defined */
#else /* __CRT_HAVE_wspawnve || (__CRT_HAVE_DOS$wspawnve && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_DOS$_wspawnve && __SIZEOF_WCHAR_T__ == 2) */
#undef __local_wspawnle_defined
#endif /* !__CRT_HAVE_wspawnve && (!__CRT_HAVE_DOS$wspawnve || !__SIZEOF_WCHAR_T__ == 4) && (!__CRT_HAVE_DOS$_wspawnve || !__SIZEOF_WCHAR_T__ == 2) */
#endif /* !__local_wspawnle_defined */
