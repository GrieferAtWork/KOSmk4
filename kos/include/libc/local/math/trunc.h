/* HASH CRC-32:0x9d4236ab */
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
#ifndef __local_trunc_defined
#define __local_trunc_defined
#include <__crt.h>
#include <hybrid/typecore.h>
#include <libm/trunc.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(trunc) __ATTR_CONST __ATTR_WUNUSED double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(trunc))(double __x) {
#ifdef __LIBM_MATHFUN
	return __LIBM_MATHFUN(trunc, __x);
#else /* __LIBM_MATHFUN */
	return (double)(__INTMAX_TYPE__)__x;
#endif /* !__LIBM_MATHFUN */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_trunc_defined
#define __local___localdep_trunc_defined
#define __localdep_trunc __LIBC_LOCAL_NAME(trunc)
#endif /* !__local___localdep_trunc_defined */
#endif /* !__local_trunc_defined */
