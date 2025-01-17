/* HASH CRC-32:0xade65423 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_ceilf_defined
#define __local_ceilf_defined
#include <__crt.h>
#include <hybrid/typecore.h>
#include <libm/ceil.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ceilf) __ATTR_CONST __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(ceilf))(float __x) {
#ifdef __LIBM_MATHFUNF
	return __LIBM_MATHFUNF(ceil, __x);
#else /* __LIBM_MATHFUNF */
	float __result;
	__result = (float)(__INTMAX_TYPE__)__x; /* Round towards 0 */
	if (__result < __x)
		__result += 1.0f;
	return __result;
#endif /* !__LIBM_MATHFUNF */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ceilf_defined
#define __local___localdep_ceilf_defined
#define __localdep_ceilf __LIBC_LOCAL_NAME(ceilf)
#endif /* !__local___localdep_ceilf_defined */
#endif /* !__local_ceilf_defined */
