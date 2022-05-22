/* HASH CRC-32:0xb2ee1903 */
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
#ifndef __local__loaddll_defined
#define __local__loaddll_defined
#include <__crt.h>
#include <libdl/asm/dlfcn.h>
#ifdef __CRT_HAVE_dlopen
#include <kos/anno.h>
#include <features.h>
#include <bits/types.h>
#include <dlfcn.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_loaddll) __ATTR_IN_OPT(1) __INTPTR_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(_loaddll))(char __KOS_FIXED_CONST *__file) __THROWS(...) {
#ifdef RTLD_LOCAL
	return (__INTPTR_TYPE__)(__UINTPTR_TYPE__)dlopen(__file, RTLD_LOCAL);
#elif defined(RTLD_GLOBAL)
	return (__INTPTR_TYPE__)(__UINTPTR_TYPE__)dlopen(__file, RTLD_GLOBAL);
#else /* ... */
	return (__INTPTR_TYPE__)(__UINTPTR_TYPE__)dlopen(__file, 0);
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__loaddll_defined
#define __local___localdep__loaddll_defined
#define __localdep__loaddll __LIBC_LOCAL_NAME(_loaddll)
#endif /* !__local___localdep__loaddll_defined */
#else /* __CRT_HAVE_dlopen */
#undef __local__loaddll_defined
#endif /* !__CRT_HAVE_dlopen */
#endif /* !__local__loaddll_defined */
