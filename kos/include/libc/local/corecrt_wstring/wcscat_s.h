/* HASH CRC-32:0x9ac48756 */
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
#ifndef __local_wcscat_s_defined
#define __local_wcscat_s_defined
#include <__crt.h>
#include <bits/types.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wcscat_s) __ATTR_ACCESS_RO_OPT(3) __ATTR_ACCESS_RW_OPT(1) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcscat_s))(__WCHAR_TYPE__ *__dst, __SIZE_TYPE__ __dstsize, __WCHAR_TYPE__ const *__src) {
	if (!__dst || !__src)
		return 22;
	while (__dstsize && *__dst) {
		++__dst;
		--__dstsize;
	}
	if (!__dstsize)
		return 22;
	while ((*__dst++ = *__src++) != 0 && --__dstsize)
		;
	if (!__dstsize)
		return 34;
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcscat_s_defined
#define __local___localdep_wcscat_s_defined
#define __localdep_wcscat_s __LIBC_LOCAL_NAME(wcscat_s)
#endif /* !__local___localdep_wcscat_s_defined */
#endif /* !__local_wcscat_s_defined */
