/* HASH CRC-32:0x2b3cef7b */
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
#ifndef __local_mkdirat_defined
#define __local_mkdirat_defined
#include <__crt.h>
#ifdef __CRT_HAVE_fmkdirat
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fmkdirat_defined
#define __local___localdep_fmkdirat_defined
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_RPC,__localdep_fmkdirat,(__fd_t __dirfd, char const *__pathname, __mode_t __mode, __atflag_t __flags),fmkdirat,(__dirfd,__pathname,__mode,__flags))
#endif /* !__local___localdep_fmkdirat_defined */
__LOCAL_LIBC(mkdirat) __ATTR_IN(2) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(mkdirat))(__fd_t __dirfd, char const *__pathname, __mode_t __mode) {
	return (__NAMESPACE_LOCAL_SYM __localdep_fmkdirat)(__dirfd, __pathname, __mode, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mkdirat_defined
#define __local___localdep_mkdirat_defined
#define __localdep_mkdirat __LIBC_LOCAL_NAME(mkdirat)
#endif /* !__local___localdep_mkdirat_defined */
#else /* __CRT_HAVE_fmkdirat */
#undef __local_mkdirat_defined
#endif /* !__CRT_HAVE_fmkdirat */
#endif /* !__local_mkdirat_defined */
