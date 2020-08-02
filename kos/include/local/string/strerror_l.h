/* HASH CRC-32:0x37d4541d */
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
#ifndef __local_strerror_l_defined
#define __local_strerror_l_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: strerror from string */
#ifndef __local___localdep_strerror_defined
#define __local___localdep_strerror_defined 1
#ifdef __CRT_HAVE_strerror
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_COLD __ATTR_RETNONNULL __ATTR_WUNUSED,char *,__NOTHROW_NCX,__localdep_strerror,(__errno_t __errnum),strerror,(__errnum))
#else /* __CRT_HAVE_strerror */
__NAMESPACE_LOCAL_END
#include <local/string/strerror.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strerror __LIBC_LOCAL_NAME(strerror)
#endif /* !__CRT_HAVE_strerror */
#endif /* !__local___localdep_strerror_defined */
__LOCAL_LIBC(strerror_l) __ATTR_COLD __ATTR_WUNUSED char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strerror_l))(int __errnum, __locale_t __locale) {
	(void)__locale;
	return __localdep_strerror(__errnum);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strerror_l_defined
#define __local___localdep_strerror_l_defined 1
#define __localdep_strerror_l __LIBC_LOCAL_NAME(strerror_l)
#endif /* !__local___localdep_strerror_l_defined */
#endif /* !__local_strerror_l_defined */
