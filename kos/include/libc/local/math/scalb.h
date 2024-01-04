/* HASH CRC-32:0x67637056 */
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
#ifndef __local_scalb_defined
#define __local_scalb_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libm/isnan.h>
#include <libm/finite.h>
#include <libm/isinf.h>
#include <libm/matherr.h>
#include <libc/errno.h>
#include <libm/scalb.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(scalb) __ATTR_WUNUSED double
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(scalb))(double __x, double __fn) {
	/*
	 * ====================================================
	 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
	 *
	 * Developed at SunSoft, a Sun Microsystems, Inc. business.
	 * Permission  to  use, copy,  modify, and  distribute this
	 * software is freely  granted, provided  that this  notice
	 * is preserved.
	 * ====================================================
	 */
	double __result;
	__result = __LIBM_MATHFUN2(scalb, __x, __fn);
	if (__LIBM_LIB_VERSION == __LIBM_SVID) {
		if (__LIBM_MATHFUNI(isinf, __result)) {
			if (__LIBM_MATHFUNI(finite, __x)) {
				return __kernel_standard(__x, __fn, __result, __LIBM_KMATHERR_SCALB_OVERFLOW); /* scalb overflow */
			} else {
#ifdef __ERANGE
				(void)__libc_seterrno(__ERANGE);
#endif /* __ERANGE */
			}
		} else if (__result == 0.0 && __result != __x) {
			return __kernel_standard(__x, __fn, __result, __LIBM_KMATHERR_SCALB_UNDERFLOW); /* scalb underflow */
		}
	} else {
		if (!__LIBM_MATHFUNI(finite, __result) || __result == 0.0) {
			if (__LIBM_MATHFUNI(isnan, __result)) {
				if (!__LIBM_MATHFUNI(isnan, __x) && !__LIBM_MATHFUNI(isnan, __fn))
					__result = __kernel_standard(__x, __fn, __result, __LIBM_KMATHERR_SCALB_INVALID);
			} else if (__LIBM_MATHFUNI(isinf, __result)) {
				if (!__LIBM_MATHFUNI(isinf, __x) && !__LIBM_MATHFUNI(isinf, __fn))
					__result = __kernel_standard(__x, __fn, __result, __LIBM_KMATHERR_SCALB_OVERFLOW);
			} else {
				/* result == 0. */
				if (__x != 0.0 && !__LIBM_MATHFUNI(isinf, __fn))
					__result = __kernel_standard(__x, __fn, __result, __LIBM_KMATHERR_SCALB_UNDERFLOW);
			}
		}
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_scalb_defined
#define __local___localdep_scalb_defined
#define __localdep_scalb __LIBC_LOCAL_NAME(scalb)
#endif /* !__local___localdep_scalb_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_scalb_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_scalb_defined */
