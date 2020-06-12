/* HASH CRC-32:0x381e9da2 */
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
#ifndef __local_wspawnl_defined
#define __local_wspawnl_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_wspawnv) || (defined(__CRT_HAVE_DOS$wspawnv) && __SIZEOF_WCHAR_T__ == 4) || (defined(__CRT_HAVE_DOS$_wspawnv) && __SIZEOF_WCHAR_T__ == 2)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: wspawnv from parts.wchar.process */
#ifndef __local___localdep_wspawnv_defined
#define __local___localdep_wspawnv_defined 1
#ifdef __CRT_HAVE_wspawnv
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_wspawnv,(int __mode, __WCHAR_TYPE__ const *__restrict __path, __TWARGV),wspawnv,(__mode,__path,___argv))
#elif defined(__CRT_HAVE_DOS$wspawnv) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_wspawnv,(int __mode, __CHAR32_TYPE__ const *__restrict __path, __T32ARGV),wspawnv,(__mode,__path,___argv))
#elif defined(__CRT_HAVE_DOS$_wspawnv) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_wspawnv,(int __mode, __CHAR16_TYPE__ const *__restrict __path, __T16ARGV),_wspawnv,(__mode,__path,___argv))
#else /* ... */
#undef __local___localdep_wspawnv_defined
#endif /* !... */
#endif /* !__local___localdep_wspawnv_defined */
__NAMESPACE_LOCAL_END
#include <parts/redirect-exec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wspawnl) __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(wspawnl))(int __mode, __WCHAR_TYPE__ const *__restrict __path, __WCHAR_TYPE__ const *__args, ...) {
	__REDIRECT_SPAWNL(__WCHAR_TYPE__, __localdep_wspawnv, __mode, __path, __args)
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wspawnl_defined
#define __local___localdep_wspawnl_defined 1
#define __localdep_wspawnl __LIBC_LOCAL_NAME(wspawnl)
#endif /* !__local___localdep_wspawnl_defined */
#else /* __CRT_HAVE_wspawnv || (__CRT_HAVE_DOS$wspawnv && __SIZEOF_WCHAR_T__ == 4) || (__CRT_HAVE_DOS$_wspawnv && __SIZEOF_WCHAR_T__ == 2) */
#undef __local_wspawnl_defined
#endif /* !__CRT_HAVE_wspawnv && (!__CRT_HAVE_DOS$wspawnv || !__SIZEOF_WCHAR_T__ == 4) && (!__CRT_HAVE_DOS$_wspawnv || !__SIZEOF_WCHAR_T__ == 2) */
#endif /* !__local_wspawnl_defined */
