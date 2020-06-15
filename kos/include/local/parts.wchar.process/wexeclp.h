/* HASH CRC-32:0x1a44b00d */
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
#ifndef __local_wexeclp_defined
#define __local_wexeclp_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_wexecvp
__NAMESPACE_LOCAL_BEGIN
/* Dependency: wexecvp from parts.wchar.process */
#ifndef __local___localdep_wexecvp_defined
#define __local___localdep_wexecvp_defined 1
#ifdef __CRT_HAVE_wexecvp
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_wexecvp,(__WCHAR_TYPE__ const *__restrict __file, __TWARGV),wexecvp,(__path,___argv))
#else /* __CRT_HAVE_wexecvp */
#undef __local___localdep_wexecvp_defined
#endif /* !__CRT_HAVE_wexecvp */
#endif /* !__local___localdep_wexecvp_defined */
__NAMESPACE_LOCAL_END
#include <parts/redirect-exec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wexeclp) __ATTR_SENTINEL __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(wexeclp))(__WCHAR_TYPE__ const *__restrict __file, __WCHAR_TYPE__ const *__args, ...) {
	__REDIRECT_EXECL(__WCHAR_TYPE__, __localdep_wexecvp, __file, __args)
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wexeclp_defined
#define __local___localdep_wexeclp_defined 1
#define __localdep_wexeclp __LIBC_LOCAL_NAME(wexeclp)
#endif /* !__local___localdep_wexeclp_defined */
#else /* __CRT_HAVE_wexecvp */
#undef __local_wexeclp_defined
#endif /* !__CRT_HAVE_wexecvp */
#endif /* !__local_wexeclp_defined */
