/* HASH CRC-32:0xfb8beeab */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_strstartcmpz_defined
#define __local_strstartcmpz_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strstartcmpz) __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strstartcmpz))(char const *__str, char const *__startswith, __SIZE_TYPE__ __startswith_len) {
	char __c1, __c2;
	do {
		if (!__startswith_len--) {
			/* When the end of the RHS-string is reached, then we
			 * know  that  `str'  has `startswith'  as  a leading
			 * prefix. */
			return 0;
		}
		__c1 = *__str++;
		__c2 = *__startswith++;
		if __unlikely(__c1 != __c2)
			return (int)((unsigned char)__c1 - (unsigned char)__c2);
	} while (__c1);

	/* The  given  `str' has  a  length less  than  `startswith_len', meaning
	 * that we're expected to return the result of a compare `NUL - NON_NUL',
	 * which  means  we must  return  -1. Note  that  the NON_NUL  is kind-of
	 * assumed here,  since  `startswith'  may contain  only  NUL  characters
	 * from  here on out,  however that is both  unlikely, wouldn't even make
	 * much sense. */
	return -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strstartcmpz_defined
#define __local___localdep_strstartcmpz_defined
#define __localdep_strstartcmpz __LIBC_LOCAL_NAME(strstartcmpz)
#endif /* !__local___localdep_strstartcmpz_defined */
#endif /* !__local_strstartcmpz_defined */
