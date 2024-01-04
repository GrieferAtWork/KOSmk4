/* HASH CRC-32:0x5d20eb21 */
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
#ifndef __local_a64l_defined
#define __local_a64l_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(a64l) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) long
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(a64l))(char const *__s) {
	unsigned long __digit, __result = 0;
	__SHIFT_TYPE__ __shift = 0;
	for (;; ++__s) {
		char __ch = *__s;
		if ((unsigned char)__ch <= '\0') {
			break;
		} else if ((unsigned char)__ch <= '/') {
			__digit = (unsigned long)(unsigned int)(__ch - '.' + 0);
		} else if ((unsigned char)__ch <= '9') {
			__digit = (unsigned long)(unsigned int)(__ch - '0' + 2);
		} else if ((unsigned char)__ch <= 'Z') {
			__digit = (unsigned long)(unsigned int)(__ch - 'A' + 12);
		} else {
			__digit = (unsigned long)(unsigned int)(__ch - 'a' + 38);
		}
		__digit <<= __shift;
		__result |= __digit;
		__shift += 6;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_a64l_defined
#define __local___localdep_a64l_defined
#define __localdep_a64l __LIBC_LOCAL_NAME(a64l)
#endif /* !__local___localdep_a64l_defined */
#endif /* !__local_a64l_defined */
