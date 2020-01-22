/* HASH CRC-32:0x8f435837 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_roundl_defined
#define __local_roundl_defined 1
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Round X to nearest integral value, rounding halfway cases away from zero */
__LOCAL_LIBC(roundl) __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(roundl))(__LONGDOUBLE __x) {
#line 1212 "kos/src/libc/magic/math.c"
	__LONGDOUBLE __result;
	__result = (__LONGDOUBLE)(__INTMAX_TYPE__)__x;
	if (__x < 0) {
		/* result >= x */
		if ((__result - __x) >= 0.5)
			__result -= 1.0;
	} else {
		/* result <= x */
		if ((__x - __result) >= 0.5)
			__result += 1.0;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_roundl_defined */
