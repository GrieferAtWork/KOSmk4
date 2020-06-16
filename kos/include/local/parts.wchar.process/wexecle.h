/* HASH CRC-32:0xe9fbce29 */
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
#ifndef __local_wexecle_defined
#define __local_wexecle_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_wexecve
__NAMESPACE_LOCAL_BEGIN
/* Dependency: wexecve from parts.wchar.process */
#ifndef __local___localdep_wexecve_defined
#define __local___localdep_wexecve_defined 1
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_wexecve,(__WCHAR_TYPE__ const *__restrict __path, __TWARGV, __TWENVP),wexecve,(__path,___argv,___envp))
#endif /* !__local___localdep_wexecve_defined */
__NAMESPACE_LOCAL_END
#include <parts/redirect-exec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wexecle) __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(wexecle))(__WCHAR_TYPE__ const *__restrict __path, __WCHAR_TYPE__ const *__args, ...) {
	__REDIRECT_EXECLE(__WCHAR_TYPE__, __localdep_wexecve, __path, __args)
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wexecle_defined
#define __local___localdep_wexecle_defined 1
#define __localdep_wexecle __LIBC_LOCAL_NAME(wexecle)
#endif /* !__local___localdep_wexecle_defined */
#else /* __CRT_HAVE_wexecve */
#undef __local_wexecle_defined
#endif /* !__CRT_HAVE_wexecve */
#endif /* !__local_wexecle_defined */
