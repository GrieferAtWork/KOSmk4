/* HASH CRC-32:0xc776ecbb */
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
#ifndef __local_copysign_defined
#define __local_copysign_defined
#include <__crt.h>
#include <libm/copysign.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(copysign) __ATTR_CONST __ATTR_WUNUSED double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(copysign))(double __num, double __sign) {
#ifdef __LIBM_MATHFUN2
	return __LIBM_MATHFUN2(copysign, __num, __sign);
#else /* __LIBM_MATHFUN2 */
	if ((__num < 0.0) != (__sign < 0.0))
		__num = -__num;
	return __num;
#endif /* !__LIBM_MATHFUN2 */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_copysign_defined
#define __local___localdep_copysign_defined
#define __localdep_copysign __LIBC_LOCAL_NAME(copysign)
#endif /* !__local___localdep_copysign_defined */
#endif /* !__local_copysign_defined */
