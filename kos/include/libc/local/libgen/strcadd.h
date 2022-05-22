/* HASH CRC-32:0xff074c66 */
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
#ifndef __local_strcadd_defined
#define __local_strcadd_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strcadd) __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strcadd))(char *__dstbuf, char const *__string) {
	for (;;) {
		char __ch = *__string++;
		if (__ch == '\0')
			break;
		if (__ch == '\\') {
			__ch = *__string++;
			switch (__ch) {

			case '\0': goto __done;

			case 'a': __ch = 7; break;  /* BEL */
			case 'b': __ch = 8; break;  /* BS */
			case 't': __ch = 9; break;  /* TAB */
			case 'n': __ch = 10; break; /* LF */
			case 'v': __ch = 11; break; /* VT */
			case 'f': __ch = 12; break; /* FF */
			case 'r': __ch = 13; break; /* CR */
//			case '\\': break; /* Unnecessary; already done by default case */

			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7': {
				/* Octal character */
				__BYTE_TYPE__ __outb = (__BYTE_TYPE__)(__ch - '0');
				unsigned int __count = 1;
				for (; __count < 3; ++__string, ++__count) {
					__ch = *__string;
					if (!(__ch >= '0' && __ch <= '7'))
						break;
					__outb <<= 3;
					__outb |= (__BYTE_TYPE__)(__ch - '0');
				}
				__ch = (char )__outb;
			}	break;

			/* XXX: '\xAB' */
			/* XXX: '\u0014' */
			/* XXX: '\U00000014' */

			default:
				break;
			}
		}
		*__dstbuf++ = __ch;
	}
__done:
	*__dstbuf = '\0'; /* NUL-terminate */
	return __dstbuf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strcadd_defined
#define __local___localdep_strcadd_defined
#define __localdep_strcadd __LIBC_LOCAL_NAME(strcadd)
#endif /* !__local___localdep_strcadd_defined */
#endif /* !__local_strcadd_defined */
