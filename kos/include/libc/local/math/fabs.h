/* HASH CRC-32:0xe2157694 */
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
#ifndef __local_fabs_defined
#define __local_fabs_defined 1
#include <__crt.h>
#include <libm/fabs.h>
__NAMESPACE_LOCAL_BEGIN
/* Absolute value of X */
__LOCAL_LIBC(fabs) __ATTR_CONST __ATTR_WUNUSED double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(fabs))(double __x) {
#ifdef __LIBM_MATHFUN
	return __LIBM_MATHFUN(fabs, __x);
#else /* __LIBM_MATHFUN */
	return __x < 0.0 ? -__x : __x;
#endif /* !__LIBM_MATHFUN */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fabs_defined
#define __local___localdep_fabs_defined 1
#define __localdep_fabs __LIBC_LOCAL_NAME(fabs)
#endif /* !__local___localdep_fabs_defined */
#endif /* !__local_fabs_defined */
