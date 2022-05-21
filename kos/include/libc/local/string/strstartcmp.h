/* HASH CRC-32:0xce762f70 */
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
#ifndef __local_strstartcmp_defined
#define __local_strstartcmp_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strstartcmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strstartcmp))(char const *__str, char const *__startswith) {
	char __c1, __c2;
	do {
		__c2 = *__startswith++;
		if (!__c2) {
			/* When the end of the RHS-string is reached, then we
			 * know  that  `str'  has `startswith'  as  a leading
			 * prefix. */
			return 0;
		}
		__c1 = *__str++;
		if __unlikely(__c1 != __c2)
			return (int)((unsigned char)__c1 - (unsigned char)__c2);
	} while (__c1);

	/* The given `str' has a  length less than `strlen(startswith)',  meaning
	 * that we're expected to return the result of a compare `NUL - NON_NUL',
	 * which  means  we must  return  -1. Note  that  the NON_NUL  is kind-of
	 * assumed here,  since  `startswith'  may contain  only  NUL  characters
	 * from  here on out,  however that is both  unlikely, wouldn't even make
	 * much sense. */
	return -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strstartcmp_defined
#define __local___localdep_strstartcmp_defined
#define __localdep_strstartcmp __LIBC_LOCAL_NAME(strstartcmp)
#endif /* !__local___localdep_strstartcmp_defined */
#endif /* !__local_strstartcmp_defined */
