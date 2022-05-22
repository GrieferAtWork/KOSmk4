/* HASH CRC-32:0x958f990c */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__getdllprocaddr_defined
#define __local__getdllprocaddr_defined
#include <__crt.h>
#include <libdl/asm/dlfcn.h>
#ifdef __CRT_HAVE_dlsym
#include <kos/anno.h>
#include <features.h>
#include <bits/types.h>
#ifndef ____procfun_defined
#define ____procfun_defined
typedef int (*__procfun)(void);
#endif /* !____procfun_defined */
#include <dlfcn.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_getdllprocaddr) __ATTR_IN_OPT(2) __procfun
(__LIBCCALL __LIBC_LOCAL_NAME(_getdllprocaddr))(__INTPTR_TYPE__ __hnd, char __KOS_FIXED_CONST *__symname, __INTPTR_TYPE__ __ord) __THROWS(...) {
	(void)__ord;
	return (__procfun)dlsym((void *)(__UINTPTR_TYPE__)__hnd, __symname);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__getdllprocaddr_defined
#define __local___localdep__getdllprocaddr_defined
#define __localdep__getdllprocaddr __LIBC_LOCAL_NAME(_getdllprocaddr)
#endif /* !__local___localdep__getdllprocaddr_defined */
#else /* __CRT_HAVE_dlsym */
#undef __local__getdllprocaddr_defined
#endif /* !__CRT_HAVE_dlsym */
#endif /* !__local__getdllprocaddr_defined */
