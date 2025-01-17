/* HASH CRC-32:0xf2a47fb5 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__unloaddll_defined
#define __local__unloaddll_defined
#include <__crt.h>
#include <bits/types.h>
#include <dlfcn.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_unloaddll) int
(__LIBCCALL __LIBC_LOCAL_NAME(_unloaddll))(__INTPTR_TYPE__ __hnd) {
#ifdef __CRT_HAVE_dlclose
	return dlclose((void *)(__UINTPTR_TYPE__)__hnd);
#else /* __CRT_HAVE_dlclose */
	(void)__hnd;
	return 0;
#endif /* !__CRT_HAVE_dlclose */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__unloaddll_defined
#define __local___localdep__unloaddll_defined
#define __localdep__unloaddll __LIBC_LOCAL_NAME(_unloaddll)
#endif /* !__local___localdep__unloaddll_defined */
#endif /* !__local__unloaddll_defined */
