/* HASH CRC-32:0x7e6bd3f */
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
#ifndef __local_wcsftime_defined
#define __local_wcsftime_defined
#include <__crt.h>
#include <hybrid/typecore.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wcsftime) __ATTR_ACCESS_RO(3) __ATTR_ACCESS_RO(4) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_WCSFTIME(3, 0) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcsftime))(__WCHAR_TYPE__ *__restrict __buf, __SIZE_TYPE__ __buflen, __WCHAR_TYPE__ const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp) {
	if (__buflen)
		*__buf = 0;
	/* TODO */
	(void)__format;
	(void)__tp;
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcsftime_defined
#define __local___localdep_wcsftime_defined
#define __localdep_wcsftime __LIBC_LOCAL_NAME(wcsftime)
#endif /* !__local___localdep_wcsftime_defined */
#endif /* !__local_wcsftime_defined */
