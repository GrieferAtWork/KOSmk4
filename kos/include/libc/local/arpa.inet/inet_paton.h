/* HASH CRC-32:0x6b9c5c68 */
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
#ifndef __local_inet_paton_defined
#define __local_inet_paton_defined
#include <__crt.h>
#include <netinet/bits/in.h>
#include <hybrid/__byteswap.h>
#include <libc/template/hex.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(inet_paton) __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(inet_paton))(char const **__restrict __pcp, struct in_addr *__restrict __inp, int __network_addr) {
	__UINT32_TYPE__ __result;
	__UINT32_TYPE__ __parts[4];
	char const *__cp = *__pcp;
	unsigned int __i;
	for (__i = 0;;) {
		char __ch = *__cp;
		__UINT32_TYPE__ __part, __new_part;
		if (__ch != '0') {
			/* Decimal. */
			if __unlikely(!(__ch >= '0' && __ch <= '9'))
				goto __err; /* Bad format. */
			__part = __ch - '0';
			++__cp;
			for (;;) {
				__ch = *__cp;
				if (!(__ch >= '0' && __ch <= '9'))
					break;
				__new_part = __part * 10;
				__new_part += __ch - '0';
				if __unlikely(__new_part < __part)
					goto __err; /* Overflow */
				__part = __new_part;
				++__cp;
			}
		} else {
			++__cp;
			__ch = *__cp;
			if (__ch == 'x' || __ch == 'X') {
				/* Hex-part */
				__part = 0;
				++__cp;
				for (;;) {
					__UINT8_TYPE__ __digit;
					__ch = *__cp;
					if (!__libc_hex2int(__ch, &__digit))
						break;
					__new_part = __part * 16;
					__new_part += __digit;
					if __unlikely(__new_part < __part)
						goto __err; /* Overflow */
					__part = __new_part;
					++__cp;
				}
			} else if (__ch >= '0' && __ch <= '7') {
				/* Oct-part */
				__part = __ch - '0';
				++__cp;
				for (;;) {
					__ch = *__cp;
					if (!(__ch >= '0' && __ch <= '7'))
						break;
					__new_part = __part * 8;
					__new_part += __ch - '0';
					if __unlikely(__new_part < __part)
						goto __err; /* Overflow */
					__part = __new_part;
					++__cp;
				}
			} else {
				/* Zero-part */
				__part = 0;
			}
		}
		__parts[__i] = __part;
		++__i;
		if (__i >= 4) {
			if __unlikely(*__cp == '.')
				goto __err; /* Bad format. */
			break;
		}
		if (*__cp != '.')
			break;
		if __unlikely(__part > 0xff)
			goto __err; /* Only the last part can be > 255 */
		++__cp;
	}
	switch (__builtin_expect(__i, 4)) {

	case 4:
		if __unlikely(__parts[3] > 0xff)
			goto __err;
		__result = __parts[0] << 24 |
		         __parts[1] << 16 |
		         __parts[2] << 8 |
		         __parts[3];
		break;

	case 3:
		if (__network_addr) {
			if __unlikely(__parts[2] > 0xff)
				goto __err;
			__result = __parts[0] << 16 |
			         __parts[1] << 8 |
			         __parts[2];
		} else {
			if __unlikely(__parts[2] > 0xffff)
				goto __err;
			__result = __parts[0] << 24 |
			         __parts[1] << 16 |
			         __parts[2];
		}
		break;

	case 2:
		if (__network_addr) {
			if __unlikely(__parts[1] > 0xff)
				goto __err;
			__result = __parts[0] << 8 |
			         __parts[1];
		} else {
			if __unlikely(__parts[1] > 0xffffff)
				goto __err;
			__result = __parts[0] << 24 |
			         __parts[1];
		}
		break;

	case 1:
		if (__network_addr) {
			if __unlikely(__parts[0] > 0xff)
				goto __err;
		}
		__result = __parts[0];
		break;

	default: __builtin_unreachable();
	}
	__inp->s_addr = __hybrid_htobe32(__result);
	*__pcp = __cp;
	return 1;
__err:
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_inet_paton_defined
#define __local___localdep_inet_paton_defined
#define __localdep_inet_paton __LIBC_LOCAL_NAME(inet_paton)
#endif /* !__local___localdep_inet_paton_defined */
#endif /* !__local_inet_paton_defined */
