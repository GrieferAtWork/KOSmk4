/* HASH CRC-32:0x317ddeed */
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
#ifndef __local_wexeclpe_defined
#define __local_wexeclpe_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_wexecvpe
__NAMESPACE_LOCAL_BEGIN
/* Dependency: wexecvpe from parts.wchar.process */
#ifndef __local___localdep_wexecvpe_defined
#define __local___localdep_wexecvpe_defined 1
#ifdef __CRT_HAVE_wexecvpe
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_wexecvpe,(__WCHAR_TYPE__ const *__restrict __file, __TWARGV, __TWENVP),wexecvpe,(__path,___argv,___envp))
#else /* __CRT_HAVE_wexecvpe */
#undef __local___localdep_wexecvpe_defined
#endif /* !__CRT_HAVE_wexecvpe */
#endif /* !__local___localdep_wexecvpe_defined */
__NAMESPACE_LOCAL_END
#include <parts/redirect-exec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wexeclpe) __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(wexeclpe))(__WCHAR_TYPE__ const *__restrict __file, __WCHAR_TYPE__ const *__args, ...) {
	__REDIRECT_EXECLE(__WCHAR_TYPE__, __localdep_wexecvpe, __file, __args)
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wexeclpe_defined
#define __local___localdep_wexeclpe_defined 1
#define __localdep_wexeclpe __LIBC_LOCAL_NAME(wexeclpe)
#endif /* !__local___localdep_wexeclpe_defined */
#else /* __CRT_HAVE_wexecvpe */
#undef __local_wexeclpe_defined
#endif /* !__CRT_HAVE_wexecvpe */
#endif /* !__local_wexeclpe_defined */
