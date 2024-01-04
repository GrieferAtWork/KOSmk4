/* HASH CRC-32:0xd1451bd5 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_strverscmp_defined
#define __local_strverscmp_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strverscmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strverscmp))(char const *__s1, char const *__s2) {
	char const *__s1_start = __s1;
	char __c1, __c2;
	do {
		if ((__c1 = *__s1) != (__c2 = *__s2)) {
			unsigned int __vala, __valb;

			/* Unwind common digits. */
			while (__s1 != __s1_start) {
				if (__s1[-1] < '0' || __s1[-1] > '9')
					break;
				__c2 = __c1 = *--__s1, --__s2;
			}

			/* Check if both strings have digit sequences in the same places. */
			if ((__c1 < '0' || __c1 > '9') &&
			    (__c2 < '0' || __c2 > '9'))
				return (int)((unsigned char)__c1 - (unsigned char)__c2);

			/* Deal with leading zeros. */
			if (__c1 == '0')
				return -1;
			if (__c2 == '0')
				return 1;

			/* Compare digits. */
			__vala = __c1 - '0';
			__valb = __c2 - '0';
			for (;;) {
				__c1 = *__s1++;
				if (__c1 < '0' || __c1 > '9')
					break;
				__vala *= 10;
				__vala += __c1 - '0';
			}
			for (;;) {
				__c2 = *__s2++;
				if (__c2 < '0' || __c2 > '9')
					break;
				__valb *= 10;
				__valb += __c2 - '0';
			}

			/* Return difference between digits. */
			return (int)__vala - (int)__valb;
		}
		++__s1;
		++__s2;
	} while (__c1 != '\0');
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strverscmp_defined
#define __local___localdep_strverscmp_defined
#define __localdep_strverscmp __LIBC_LOCAL_NAME(strverscmp)
#endif /* !__local___localdep_strverscmp_defined */
#endif /* !__local_strverscmp_defined */
