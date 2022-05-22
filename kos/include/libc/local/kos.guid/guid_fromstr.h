/* HASH CRC-32:0x4dd02ee4 */
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
#ifndef __local_guid_fromstr_defined
#define __local_guid_fromstr_defined
#include <__crt.h>
#include <libc/template/hex.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(guid_fromstr) __ATTR_IN(1) __ATTR_OUT(2) char const *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(guid_fromstr))(char const __string[GUID_STRLEN], guid_t *__restrict __result) {
	unsigned int __i;
	for (__i = 0; __i < 16; ++__i) {
		__BYTE_TYPE__ __nibbles[2];
		unsigned int __j;

		/* [05][4b][1d][ef]-[b2][ae]-[4d][99]-[a9][9c]-[54][b9][73][0c][3d][c3]
		 *  0   1   2   3    4   5    6   7    8   9    10  11  12  13  14  15
		 *
		 * There are mandatory '-' characters before bytes: 4, 6, 8 and 10 */
		if (!(__i & 1) && __i >= 4 && __i <= 10) {
			if (*__string != '-')
				goto __inval;
			++__string;
		}

		/* Decode nibbles */
		for (__j = 0; __j < 2; ++__j) {
			char __ch = *__string++;
			if (!__libc_hex2int(__ch, &__nibbles[__j]))
				goto __inval;
		}

		/* Convert nibbles to byte */
		__nibbles[0] <<= 4;
		__nibbles[0] |= __nibbles[1];

		/* Write byte to result GUID */
		((__BYTE_TYPE__ *)__result)[__i] = __nibbles[0];
	}
	return __string;
__inval:
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_guid_fromstr_defined
#define __local___localdep_guid_fromstr_defined
#define __localdep_guid_fromstr __LIBC_LOCAL_NAME(guid_fromstr)
#endif /* !__local___localdep_guid_fromstr_defined */
#endif /* !__local_guid_fromstr_defined */
