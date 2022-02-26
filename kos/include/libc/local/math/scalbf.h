/* HASH CRC-32:0x8130e674 */
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
#ifndef __local_scalbf_defined
#define __local_scalbf_defined
#include <__crt.h>
#include <ieee754.h>
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_scalb) || defined(__CRT_HAVE__scalb) || defined(__CRT_HAVE___scalb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_scalb_defined
#define __local___localdep_scalb_defined
#if __has_builtin(__builtin_scalb) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalb)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_scalb,(double __x, double __fn),scalb,{ return __builtin_scalb(__x, __fn); })
#elif defined(__CRT_HAVE_scalb)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_scalb,(double __x, double __fn),scalb,(__x,__fn))
#elif defined(__CRT_HAVE__scalb)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_scalb,(double __x, double __fn),_scalb,(__x,__fn))
#elif defined(__CRT_HAVE___scalb)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__localdep_scalb,(double __x, double __fn),__scalb,(__x,__fn))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_LOCAL_END
#include <libc/local/math/scalb.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_scalb __LIBC_LOCAL_NAME(scalb)
#else /* ... */
#undef __local___localdep_scalb_defined
#endif /* !... */
#endif /* !__local___localdep_scalb_defined */
__NAMESPACE_LOCAL_END
#include <libm/isnan.h>
#include <libm/finite.h>
#include <libm/isinf.h>
#include <libm/matherr.h>
#include <libc/errno.h>
#include <libm/scalb.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(scalbf) __ATTR_WUNUSED float
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(scalbf))(float __x, float __fn) {
#if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)


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
	float __result;
	__result = __LIBM_MATHFUN2F(scalb, __x, __fn);
	if (__LIBM_LIB_VERSION == __LIBM_SVID) {
		if (__LIBM_MATHFUNIF(isinf, __result)) {
			if (__LIBM_MATHFUNIF(finite, __x)) {
				return __kernel_standard_f(__x, __fn, __result, __LIBM_KMATHERRF_SCALB_OVERFLOW); /* scalb overflow */
			} else {
#ifdef __ERANGE
				(void)__libc_seterrno(__ERANGE);
#endif /* __ERANGE */
			}
		} else if (__result == 0.0f && __result != __x) {
			return __kernel_standard_f(__x, __fn, __result, __LIBM_KMATHERRF_SCALB_UNDERFLOW); /* scalb underflow */
		}
	} else {
		if (!__LIBM_MATHFUNIF(finite, __result) || __result == 0.0f) {
			if (__LIBM_MATHFUNIF(isnan, __result)) {
				if (!__LIBM_MATHFUNIF(isnan, __x) && !__LIBM_MATHFUNIF(isnan, __fn))
					__result = __kernel_standard_f(__x, __fn, __result, __LIBM_KMATHERRF_SCALB_INVALID);
			} else if (__LIBM_MATHFUNIF(isinf, __result)) {
				if (!__LIBM_MATHFUNIF(isinf, __x) && !__LIBM_MATHFUNIF(isinf, __fn))
					__result = __kernel_standard_f(__x, __fn, __result, __LIBM_KMATHERRF_SCALB_OVERFLOW);
			} else {
				/* result == 0. */
				if (__x != 0.0f && !__LIBM_MATHFUNIF(isinf, __fn))
					__result = __kernel_standard_f(__x, __fn, __result, __LIBM_KMATHERRF_SCALB_UNDERFLOW);
			}
		}
	}
	return __result;
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
	return (float)(__NAMESPACE_LOCAL_SYM __localdep_scalb)((double)__x, (double)__fn);
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_scalbf_defined
#define __local___localdep_scalbf_defined
#define __localdep_scalbf __LIBC_LOCAL_NAME(scalbf)
#endif /* !__local___localdep_scalbf_defined */
#else /* __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_scalb || __CRT_HAVE__scalb || __CRT_HAVE___scalb || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#undef __local_scalbf_defined
#endif /* !__IEEE754_DOUBLE_TYPE_IS_FLOAT__ && !__IEEE754_FLOAT_TYPE_IS_FLOAT__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ && !__CRT_HAVE_scalb && !__CRT_HAVE__scalb && !__CRT_HAVE___scalb && !__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ && !__IEEE754_FLOAT_TYPE_IS_DOUBLE__ && !__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__local_scalbf_defined */
