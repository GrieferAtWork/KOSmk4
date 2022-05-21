/* HASH CRC-32:0xa4e108e */
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
#ifndef __local_c16ncmp_defined
#define __local_c16ncmp_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16ncmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_ROS(1, 3) __ATTR_ACCESS_ROS(2, 3) __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16ncmp))(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen) {
	__CHAR16_TYPE__ __c1, __c2;
	do {
		if (!__maxlen--)
			break;
		if ((__c1 = *__s1++) != (__c2 = *__s2++))
			return (int)((__CHAR16_TYPE__)__c1 - (__CHAR16_TYPE__)__c2);
	} while (__c1);
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16ncmp_defined
#define __local___localdep_c16ncmp_defined
#define __localdep_c16ncmp __LIBC_LOCAL_NAME(c16ncmp)
#endif /* !__local___localdep_c16ncmp_defined */
#endif /* !__local_c16ncmp_defined */
