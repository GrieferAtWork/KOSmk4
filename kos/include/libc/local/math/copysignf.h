/* HASH CRC-32:0xed2ada1d */
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
#ifndef __local_copysignf_defined
#define __local_copysignf_defined
#include <__crt.h>
#include <libm/copysign.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(copysignf) __ATTR_CONST __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(copysignf))(float __num, float __sign) {
#ifdef __LIBM_MATHFUN2F
	return __LIBM_MATHFUN2F(copysign, __num, __sign);
#else /* __LIBM_MATHFUN2F */
	if ((__num < 0.0f) != (__sign < 0.0f))
		__num = -__num;
	return __num;
#endif /* !__LIBM_MATHFUN2F */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_copysignf_defined
#define __local___localdep_copysignf_defined
#define __localdep_copysignf __LIBC_LOCAL_NAME(copysignf)
#endif /* !__local___localdep_copysignf_defined */
#endif /* !__local_copysignf_defined */
