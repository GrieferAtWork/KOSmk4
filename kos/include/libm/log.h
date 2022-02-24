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
#ifndef _LIBM_LOG_H
#define _LIBM_LOG_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/fabs.h>
#include <libm/fdlibm.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */
__LIBM_LOCAL_DECLARE_BEGIN
#ifndef __libm_ln2_hif_defined
#define __libm_ln2_hif_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, ln2_hif, __IEEE754_FLOAT_C(6.9313812256e-01)) /* 0x3f317180 */
#endif /* !__libm_ln2_hif_defined */
#ifndef __libm_ln2_lof_defined
#define __libm_ln2_lof_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, ln2_lof, __IEEE754_FLOAT_C(9.0580006145e-06)) /* 0x3717f7d1 */
#endif /* !__libm_ln2_lof_defined */
#ifndef __libm_two25f_defined
#define __libm_two25f_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, two25f, __IEEE754_FLOAT_C(3.355443200e+07)) /* 0x4c000000 */
#endif /* !__libm_two25f_defined */
#ifndef __libm_Lg1f_defined
#define __libm_Lg1f_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, Lg1f, __IEEE754_FLOAT_C(6.6666668653e-01))    /* 3F2AAAAB */
#endif /* !__libm_Lg1f_defined */
#ifndef __libm_Lg2f_defined
#define __libm_Lg2f_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, Lg2f, __IEEE754_FLOAT_C(4.0000000596e-01))    /* 3ECCCCCD */
#endif /* !__libm_Lg2f_defined */
#ifndef __libm_Lg3f_defined
#define __libm_Lg3f_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, Lg3f, __IEEE754_FLOAT_C(2.8571429849e-01))    /* 3E924925 */
#endif /* !__libm_Lg3f_defined */
#ifndef __libm_Lg4f_defined
#define __libm_Lg4f_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, Lg4f, __IEEE754_FLOAT_C(2.2222198546e-01))    /* 3E638E29 */
#endif /* !__libm_Lg4f_defined */
#ifndef __libm_Lg5f_defined
#define __libm_Lg5f_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, Lg5f, __IEEE754_FLOAT_C(1.8183572590e-01))    /* 3E3A3325 */
#endif /* !__libm_Lg5f_defined */
#ifndef __libm_Lg6f_defined
#define __libm_Lg6f_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, Lg6f, __IEEE754_FLOAT_C(1.5313838422e-01))    /* 3E1CD04F */
#endif /* !__libm_Lg6f_defined */
#ifndef __libm_Lg7f_defined
#define __libm_Lg7f_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, Lg7f, __IEEE754_FLOAT_C(1.4798198640e-01))    /* 3E178897 */
#endif /* !__libm_Lg7f_defined */

#ifndef __libm_zerof_defined
#define __libm_zerof_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, zerof, __IEEE754_FLOAT_C(0.0))
#endif /* !__libm_zerof_defined */
__LIBM_LOCAL_DECLARE_END

__LOCAL __ATTR_WUNUSED __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_logf)(__IEEE754_FLOAT_TYPE__ __x) {
	__IEEE754_FLOAT_TYPE__ __hfsq, __f, __s, __z;
	__IEEE754_FLOAT_TYPE__ __R, __w, __t1, __t2, __dk;
	__int32_t __k, __ix, __i, __j;
	__LIBM_GET_FLOAT_WORD(__ix, __x);
	__k = 0;
	if (__ix < __INT32_C(0x00800000)) { /* x < 2**-126  */
		if ((__ix & __INT32_C(0x7fffffff)) == 0)
			return -__LIBM_LOCAL_VALUE(two25f) / (__x - __x); /* log(+-0)=-inf */
		if (__ix < 0)
			return (__x - __x) / (__x - __x); /* log(-#) = NaN */
		__k -= 25;
		__x *= __LIBM_LOCAL_VALUE(two25f); /* subnormal number, scale up x */
		__LIBM_GET_FLOAT_WORD(__ix, __x);
	}
	if (__ix >= __INT32_C(0x7f800000))
		return __x + __x;
	__k += (__ix >> 23) - 127;
	__ix &= __INT32_C(0x007fffff);
	__i = (__ix + (__INT32_C(0x95f64) << 3)) & __INT32_C(0x800000);
	__LIBM_SET_FLOAT_WORD(__x, __ix | (__i ^ __INT32_C(0x3f800000))); /* normalize x or x/2 */
	__k += (__i >> 23);
	__f = __x - (__IEEE754_FLOAT_TYPE__)__IEEE754_FLOAT_C(1.0);
	if ((__INT32_C(0x007fffff) & (15 + __ix)) < 16) { /* |f| < 2**-20 */
		if (__f == __LIBM_LOCAL_VALUE(zerof)) {
			if (__k == 0) {
				return __LIBM_LOCAL_VALUE(zerof);
			} else {
				__dk = (__IEEE754_FLOAT_TYPE__)__k;
				return __dk * __LIBM_LOCAL_VALUE(ln2_hif) + __dk * __LIBM_LOCAL_VALUE(ln2_lof);
			}
		}
		__R = __f * __f * ((__IEEE754_FLOAT_TYPE__)__IEEE754_FLOAT_C(0.5) -
		                   ((__IEEE754_FLOAT_TYPE__)(0.33333333333333333) * __f));
		if (__k == 0) {
			return __f - __R;
		} else {
			__dk = (__IEEE754_FLOAT_TYPE__)__k;
			return __dk * __LIBM_LOCAL_VALUE(ln2_hif) - ((__R - __dk * __LIBM_LOCAL_VALUE(ln2_lof)) - __f);
		}
	}
	__s  = __f / ((__IEEE754_FLOAT_TYPE__)__IEEE754_FLOAT_C(2.0) + __f);
	__dk = (__IEEE754_FLOAT_TYPE__)__k;
	__z  = __s * __s;
	__i  = __ix - (__INT32_C(0x6147a) << 3);
	__w  = __z * __z;
	__j  = (__INT32_C(0x6b851) << 3) - __ix;
	__t1 = __w * (__LIBM_LOCAL_VALUE(Lg2f) + __w * (__LIBM_LOCAL_VALUE(Lg4f) + __w * __LIBM_LOCAL_VALUE(Lg6f)));
	__t2 = __z * (__LIBM_LOCAL_VALUE(Lg1f) + __w * (__LIBM_LOCAL_VALUE(Lg3f) + __w * (__LIBM_LOCAL_VALUE(Lg5f) + __w * __LIBM_LOCAL_VALUE(Lg7f))));
	__i |= __j;
	__R = __t2 + __t1;
	if (__i > 0) {
		__hfsq = __IEEE754_FLOAT_C(0.5) * __f * __f;
		if (__k == 0) {
			return __f - (__hfsq - __s * (__hfsq + __R));
		} else {
			return __dk * __LIBM_LOCAL_VALUE(ln2_hif) - ((__hfsq - (__s * (__hfsq + __R) + __dk * __LIBM_LOCAL_VALUE(ln2_lof))) - __f);
		}
	} else {
		if (__k == 0) {
			return __f - __s * (__f - __R);
		} else {
			return __dk * __LIBM_LOCAL_VALUE(ln2_hif) - ((__s * (__f - __R) - __dk * __LIBM_LOCAL_VALUE(ln2_lof)) - __f);
		}
	}
}
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */
__LIBM_LOCAL_DECLARE_BEGIN
#ifndef __libm_ln2_hi_defined
#define __libm_ln2_hi_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, ln2_hi, __IEEE754_DOUBLE_C(6.93147180369123816490e-01)) /* 0x3fe62e42, 0xfee00000 */
#endif /* !__libm_ln2_hi_defined */
#ifndef __libm_ln2_lo_defined
#define __libm_ln2_lo_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, ln2_lo, __IEEE754_DOUBLE_C(1.90821492927058770002e-10)) /* 0x3dea39ef, 0x35793c76 */
#endif /* !__libm_ln2_lo_defined */
#ifndef __libm_two54_defined
#define __libm_two54_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, two54, __IEEE754_DOUBLE_C(1.80143985094819840000e+16)) /* 0x43500000, 0x00000000 */
#endif /* !__libm_two54_defined */
#ifndef __libm_zero_defined
#define __libm_zero_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, zero, __IEEE754_DOUBLE_C(0.0))
#endif /* !__libm_zero_defined */
#ifndef __libm_Lg1_defined
#define __libm_Lg1_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, Lg1, __IEEE754_DOUBLE_C(6.666666666666735130e-01)) /* 3FE55555 55555593 */
#endif /* !__libm_Lg1_defined */
#ifndef __libm_Lg2_defined
#define __libm_Lg2_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, Lg2, __IEEE754_DOUBLE_C(3.999999999940941908e-01)) /* 3FD99999 9997FA04 */
#endif /* !__libm_Lg2_defined */
#ifndef __libm_Lg3_defined
#define __libm_Lg3_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, Lg3, __IEEE754_DOUBLE_C(2.857142874366239149e-01)) /* 3FD24924 94229359 */
#endif /* !__libm_Lg3_defined */
#ifndef __libm_Lg4_defined
#define __libm_Lg4_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, Lg4, __IEEE754_DOUBLE_C(2.222219843214978396e-01)) /* 3FCC71C5 1D8E78AF */
#endif /* !__libm_Lg4_defined */
#ifndef __libm_Lg5_defined
#define __libm_Lg5_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, Lg5, __IEEE754_DOUBLE_C(1.818357216161805012e-01)) /* 3FC74664 96CB03DE */
#endif /* !__libm_Lg5_defined */
#ifndef __libm_Lg6_defined
#define __libm_Lg6_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, Lg6, __IEEE754_DOUBLE_C(1.531383769920937332e-01)) /* 3FC39A09 D078C69F */
#endif /* !__libm_Lg6_defined */
#ifndef __libm_Lg7_defined
#define __libm_Lg7_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, Lg7, __IEEE754_DOUBLE_C(1.479819860511658591e-01)) /* 3FC2F112 DF3E5244 */
#endif /* !__libm_Lg7_defined */
__LIBM_LOCAL_DECLARE_END

__LOCAL __ATTR_WUNUSED __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_log)(__IEEE754_DOUBLE_TYPE__ __x) {
	__IEEE754_DOUBLE_TYPE__ __hfsq, __f, __s, __z, __R;
	__IEEE754_DOUBLE_TYPE__ __w, __t1, __t2, __dk;
	__int32_t __k, __hx, __i, __j;
	__uint32_t __lx;
	__LIBM_GET_DOUBLE_WORDS(__hx, __lx, __x);
	__k = 0;
	if (__hx < __INT32_C(0x00100000)) { /* x < 2**-1022  */
		if (((__hx & __INT32_C(0x7fffffff)) | __lx) == 0)
			return -__LIBM_LOCAL_VALUE(two54) / __LIBM_LOCAL_VALUE(zero); /* log(+-0)=-inf */
		if (__hx < 0)
			return (__x - __x) / __LIBM_LOCAL_VALUE(zero); /* log(-#) = NaN */
		__k -= 54;
		__x *= __LIBM_LOCAL_VALUE(two54); /* subnormal number, scale up x */
		__LIBM_GET_HIGH_WORD(__hx, __x);
	}
	if (__hx >= __INT32_C(0x7ff00000))
		return __x + __x;
	__k += (__hx >> 20) - 1023;
	__hx &= __INT32_C(0x000fffff);
	__i = (__hx + __INT32_C(0x95f64)) & __INT32_C(0x100000);
	__LIBM_SET_HIGH_WORD(__x, __hx | (__i ^ __INT32_C(0x3ff00000))); /* normalize x or x/2 */
	__k += (__i >> 20);
	__f = __x - __IEEE754_DOUBLE_C(1.0);
	if ((__INT32_C(0x000fffff) & (2 + __hx)) < 3) { /* |f| < 2**-20 */
		if (__f == __LIBM_LOCAL_VALUE(zero)) {
			if (__k == 0)
				return __LIBM_LOCAL_VALUE(zero);
			__dk = (__IEEE754_DOUBLE_TYPE__)__k;
			return __dk * __LIBM_LOCAL_VALUE(ln2_hi) + __dk * __LIBM_LOCAL_VALUE(ln2_lo);
		}
		__R = __f * __f * (__IEEE754_DOUBLE_C(0.5) - __IEEE754_DOUBLE_C(0.33333333333333333) * __f);
		if (__k == 0)
			return __f - __R;
		__dk = (__IEEE754_DOUBLE_TYPE__)__k;
		return __dk * __LIBM_LOCAL_VALUE(ln2_hi) -
		       ((__R - __dk * __LIBM_LOCAL_VALUE(ln2_lo)) - __f);
	}
	__s  = __f / (__IEEE754_DOUBLE_C(2.0) + __f);
	__dk = (__IEEE754_DOUBLE_TYPE__)__k;
	__z  = __s * __s;
	__i  = __hx - __INT32_C(0x6147a);
	__w  = __z * __z;
	__j  = __INT32_C(0x6b851) - __hx;
	__t1 = __w * (__LIBM_LOCAL_VALUE(Lg2) + __w * (__LIBM_LOCAL_VALUE(Lg4) + __w * __LIBM_LOCAL_VALUE(Lg6)));
	__t2 = __z * (__LIBM_LOCAL_VALUE(Lg1) + __w * (__LIBM_LOCAL_VALUE(Lg3) + __w * (__LIBM_LOCAL_VALUE(Lg5) + __w * __LIBM_LOCAL_VALUE(Lg7))));
	__i |= __j;
	__R = __t2 + __t1;
	if (__i > 0) {
		__hfsq = __IEEE754_DOUBLE_C(0.5) * __f * __f;
		if (__k == 0)
			return __f - (__hfsq - __s * (__hfsq + __R));
		return __dk * __LIBM_LOCAL_VALUE(ln2_hi) -
		       ((__hfsq - (__s * (__hfsq + __R) + __dk * __LIBM_LOCAL_VALUE(ln2_lo))) - __f);
	}
	if (__k == 0)
		return __f - __s * (__f - __R);
	return __dk * __LIBM_LOCAL_VALUE(ln2_hi) -
	       ((__s * (__f - __R) - __dk * __LIBM_LOCAL_VALUE(ln2_lo)) - __f);
}
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */
__LIBM_LOCAL_DECLARE_BEGIN
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, ln2_hil, __IEEE854_LONG_DOUBLE_C(6.93145751953125e-1))
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, ln2_lol, __IEEE854_LONG_DOUBLE_C(1.4286068203094172321214581765680755001344E-6))
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, Lg1l, __IEEE854_LONG_DOUBLE_C(6.666666666666735130e-01)) /* 3FE55555 55555593 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, Lg2l, __IEEE854_LONG_DOUBLE_C(3.999999999940941908e-01)) /* 3FD99999 9997FA04 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, Lg3l, __IEEE854_LONG_DOUBLE_C(2.857142874366239149e-01)) /* 3FD24924 94229359 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, Lg4l, __IEEE854_LONG_DOUBLE_C(2.222219843214978396e-01)) /* 3FCC71C5 1D8E78AF */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, Lg5l, __IEEE854_LONG_DOUBLE_C(1.818357216161805012e-01)) /* 3FC74664 96CB03DE */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, Lg6l, __IEEE854_LONG_DOUBLE_C(1.531383769920937332e-01)) /* 3FC39A09 D078C69F */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, Lg7l, __IEEE854_LONG_DOUBLE_C(1.479819860511658591e-01)) /* 3FC2F112 DF3E5244 */
#ifndef __libm_zerol_defined
#define __libm_zerol_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, zerol, __IEEE854_LONG_DOUBLE_C(0.0))
#endif /* !__libm_zerol_defined */
__LIBM_LOCAL_DECLARE_END

__LOCAL __ATTR_WUNUSED __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_logl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__IEEE854_LONG_DOUBLE_TYPE__ __hfsq, __f, __s, __z;
	__IEEE854_LONG_DOUBLE_TYPE__ __R, __w, __t1, __t2, __dk;
	__int32_t __k, __hx, __i, __j;
	__uint32_t __lx;
	__uint32_t __m;
	__LIBM_GET_LDOUBLE_WORDS(__m, __hx, __lx, __x);
	__k = __m & 0x7fff;
	/* log(0) = -infinity. */
	if ((__k | (__hx & __UINT32_C(0x7fffffff)) | __lx) == 0) {
		return -0.5L / __LIBM_LOCAL_VALUE(zerol);
	}
	if (__m & 0x8000)
		return (__x - __x) / __LIBM_LOCAL_VALUE(zerol); /* log(-#) = NaN */
	/* log (infinity or NaN) */
	if (__k >= 0x7fff)
		return __x + __x;
	__k -= 0x3fff;
	__hx &= __INT32_C(0x7fffffff);
	__i = (((__hx >> 11) + __INT32_C(0x95f64)) & __INT32_C(0x100000)) >> 20;
	__LIBM_SET_LDOUBLE_EXP(__x, __i ^ 0x3fff); /* normalize x or x/2 */
	__k += __i;
	__f  = __x - 1.0;
	__s  = __f / (2.0 + __f);
	__dk = (__IEEE854_LONG_DOUBLE_TYPE__)__k;
	__z  = __s * __s;
	__i  = __hx - __INT32_C(0x6147a000);
	__w  = __z * __z;
	__j  = __INT32_C(0x6b851000) - __hx;
	__t1 = __w * (__LIBM_LOCAL_VALUE(Lg2l) + __w * (__LIBM_LOCAL_VALUE(Lg4l) + __w * __LIBM_LOCAL_VALUE(Lg6l)));
	__t2 = __z * (__LIBM_LOCAL_VALUE(Lg1l) + __w * (__LIBM_LOCAL_VALUE(Lg3l) + __w * (__LIBM_LOCAL_VALUE(Lg5l) + __w * __LIBM_LOCAL_VALUE(Lg7l))));
	__i |= __j;
	__R = __t2 + __t1;
	if (__i > 0) {
		__hfsq = 0.5 * __f * __f;
		if (__k == 0)
			return __f - (__hfsq - __s * (__hfsq + __R));
		return __dk * __LIBM_LOCAL_VALUE(ln2_hil) -
		       ((__hfsq - (__s * (__hfsq + __R) + __dk * __LIBM_LOCAL_VALUE(ln2_lol))) - __f);
	}
	if (__k == 0)
		return __f - __s * (__f - __R);
	return __dk * __LIBM_LOCAL_VALUE(ln2_hil) -
	       ((__s * (__f - __R) - __dk * __LIBM_LOCAL_VALUE(ln2_lol)) - __f);
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_LOG_H */
