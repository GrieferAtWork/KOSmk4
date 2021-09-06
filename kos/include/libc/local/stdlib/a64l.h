/* HASH CRC-32:0xfc150d27 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_a64l_defined
#define __local_a64l_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(a64l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) long
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(a64l))(char const *__s) {
	unsigned long __digit, __result = 0;
	unsigned int __shift = 0;
	for (;; ++__s) {
		char __ch = *__s;
		if (__ch <= 0) {
			break;
		} else if (__ch <= '/') {
			__digit = (__ch - '.') + 0;
		} else if (__ch <= '9') {
			__digit = (__ch - '0') + 2;
		} else if (__ch <= 'Z') {
			__digit = (__ch - 'A') + 12;
		} else {
			__digit = (__ch - 'a') + 38;
		}
		__digit <<= __shift;
		__result |= __digit;
		__shift += 6;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_a64l_defined
#define __local___localdep_a64l_defined 1
#define __localdep_a64l __LIBC_LOCAL_NAME(a64l)
#endif /* !__local___localdep_a64l_defined */
#endif /* !__local_a64l_defined */
