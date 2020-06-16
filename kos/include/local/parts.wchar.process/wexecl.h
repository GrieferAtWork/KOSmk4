/* HASH CRC-32:0xb5d197be */
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
#ifndef __local_wexecl_defined
#define __local_wexecl_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_wexecv
__NAMESPACE_LOCAL_BEGIN
/* Dependency: wexecv from parts.wchar.process */
#ifndef __local___localdep_wexecv_defined
#define __local___localdep_wexecv_defined 1
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_wexecv,(__WCHAR_TYPE__ const *__restrict __path, __TWARGV),wexecv,(__path,___argv))
#endif /* !__local___localdep_wexecv_defined */
__NAMESPACE_LOCAL_END
#include <parts/redirect-exec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wexecl) __ATTR_SENTINEL __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(wexecl))(__WCHAR_TYPE__ const *__restrict __path, __WCHAR_TYPE__ const *__args, ...) {
	__REDIRECT_EXECL(__WCHAR_TYPE__, __localdep_wexecv, __path, __args)
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wexecl_defined
#define __local___localdep_wexecl_defined 1
#define __localdep_wexecl __LIBC_LOCAL_NAME(wexecl)
#endif /* !__local___localdep_wexecl_defined */
#else /* __CRT_HAVE_wexecv */
#undef __local_wexecl_defined
#endif /* !__CRT_HAVE_wexecv */
#endif /* !__local_wexecl_defined */
