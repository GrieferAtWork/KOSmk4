/* HASH CRC-32:0x9e35b66b */
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
#ifndef __local_wspawnlpe_defined
#define __local_wspawnlpe_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_wspawnvpe
__NAMESPACE_LOCAL_BEGIN
/* Dependency: wspawnvpe from parts.wchar.process */
#ifndef __local___localdep_wspawnvpe_defined
#define __local___localdep_wspawnvpe_defined 1
#ifdef __CRT_HAVE_wspawnvpe
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__localdep_wspawnvpe,(int __mode, __WCHAR_TYPE__ const *__restrict __file, __TWARGV, __TWENVP),wspawnvpe,(__mode,__file,___argv,___envp))
#else /* __CRT_HAVE_wspawnvpe */
#undef __local___localdep_wspawnvpe_defined
#endif /* !__CRT_HAVE_wspawnvpe */
#endif /* !__local___localdep_wspawnvpe_defined */
__NAMESPACE_LOCAL_END
#include <parts/redirect-exec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wspawnlpe) __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(wspawnlpe))(int __mode, __WCHAR_TYPE__ const *__restrict __file, __WCHAR_TYPE__ const *__args, ...) {
	__REDIRECT_SPAWNLE(__WCHAR_TYPE__, __localdep_wspawnvpe, __mode, __file, __args)
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wspawnlpe_defined
#define __local___localdep_wspawnlpe_defined 1
#define __localdep_wspawnlpe __LIBC_LOCAL_NAME(wspawnlpe)
#endif /* !__local___localdep_wspawnlpe_defined */
#else /* __CRT_HAVE_wspawnvpe */
#undef __local_wspawnlpe_defined
#endif /* !__CRT_HAVE_wspawnvpe */
#endif /* !__local_wspawnlpe_defined */
