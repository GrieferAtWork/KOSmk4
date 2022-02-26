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
#ifndef _LIBM_HYPOT_H
#define _LIBM_HYPOT_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/fdlibm.h>
#include <libm/scalbn.h>
#include <libm/sqrt.h>

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

__LIBM_LOCAL_FUNC(hypotf) __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_hypotf)(__IEEE754_FLOAT_TYPE__ __x,
                              __IEEE754_FLOAT_TYPE__ __y) {
	__IEEE754_FLOAT_TYPE__ __a, __b, __t1, __t2, __y1, __y2, __w;
	__int32_t __j, __k, __ha, __hb;
	__LIBM_GET_FLOAT_WORD(__ha, __x);
	__ha &= __INT32_C(0x7fffffff);
	__LIBM_GET_FLOAT_WORD(__hb, __y);
	__hb &= __INT32_C(0x7fffffff);
	if (__hb > __ha) {
		__a  = __y;
		__b  = __x;
		__j  = __ha;
		__ha = __hb;
		__hb = __j;
	} else {
		__a = __x;
		__b = __y;
	}
	__LIBM_SET_FLOAT_WORD(__a, __ha); /* a <- |a| */
	__LIBM_SET_FLOAT_WORD(__b, __hb); /* b <- |b| */
	if ((__ha - __hb) > __INT32_C(0x0f000000))
		return __a + __b; /* x/y > 2**30 */
	__k = 0;
	if (__ha > __INT32_C(0x58800000)) {          /* a>2**50 */
		if (!__LIBM_FLT_UWORD_IS_FINITE(__ha)) { /* Inf or NaN */
			__w = __a + __b;                     /* for sNaN */
			if (__LIBM_FLT_UWORD_IS_INFINITE(__ha))
				__w = __a;
			if (__LIBM_FLT_UWORD_IS_INFINITE(__hb))
				__w = __b;
			return __w;
		}
		/* scale a and b by 2**-68 */
		__ha -= __INT32_C(0x22000000);
		__hb -= __INT32_C(0x22000000);
		__k += 68;
		__LIBM_SET_FLOAT_WORD(__a, __ha);
		__LIBM_SET_FLOAT_WORD(__b, __hb);
	}
	if (__hb < __INT32_C(0x26800000)) { /* b < 2**-50 */
		if (__LIBM_FLT_UWORD_IS_ZERO(__hb)) {
			return __a;
		} else if (__LIBM_FLT_UWORD_IS_SUBNORMAL(__hb)) {
			__LIBM_SET_FLOAT_WORD(__t1, __INT32_C(0x7e800000)); /* t1=2^126 */
			__b *= __t1;
			__a *= __t1;
			__k -= 126;
		} else {                           /* scale a and b by 2^68 */
			__ha += __INT32_C(0x22000000); /* a *= 2^68 */
			__hb += __INT32_C(0x22000000); /* b *= 2^68 */
			__k -= 68;
			__LIBM_SET_FLOAT_WORD(__a, __ha);
			__LIBM_SET_FLOAT_WORD(__b, __hb);
		}
	}
	/* medium size a and b */
	__w = __a - __b;
	if (__w > __b) {
		__LIBM_SET_FLOAT_WORD(__t1, __ha & __INT32_C(0xfffff000));
		__t2 = __a - __t1;
		__w  = __ieee754_sqrtf(__t1 * __t1 - (__b * (-__b) - __t2 * (__a + __t1)));
	} else {
		__a = __a + __a;
		__LIBM_SET_FLOAT_WORD(__y1, __hb & __INT32_C(0xfffff000));
		__y2 = __b - __y1;
		__LIBM_SET_FLOAT_WORD(__t1, __ha + __INT32_C(0x00800000));
		__t2 = __a - __t1;
		__w  = __ieee754_sqrtf(__t1 * __y1 - (__w * (-__w) - (__t1 * __y2 + __t2 * __b)));
	}
	if (__k != 0) {
		__LIBM_SET_FLOAT_WORD(__t1, __INT32_C(0x3f800000) + (__k << 23));
		return __t1 * __w;
	}
	return __w;
}
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
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

__LIBM_LOCAL_FUNC(hypot) __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_hypot)(__IEEE754_DOUBLE_TYPE__ __x,
                             __IEEE754_DOUBLE_TYPE__ __y) {
	__IEEE754_DOUBLE_TYPE__ __a, __b, __t1, __t2, __y1, __y2, __w;
	__int32_t __j, __k, __ha, __hb;
	__LIBM_GET_HIGH_WORD(__ha, __x);
	__ha &= __INT32_C(0x7fffffff);
	__LIBM_GET_HIGH_WORD(__hb, __y);
	__hb &= __INT32_C(0x7fffffff);
	if (__hb > __ha) {
		__a  = __y;
		__b  = __x;
		__j  = __ha;
		__ha = __hb;
		__hb = __j;
	} else {
		__a = __x;
		__b = __y;
	}
	__LIBM_SET_HIGH_WORD(__a, __ha); /* a <- |a| */
	__LIBM_SET_HIGH_WORD(__b, __hb); /* b <- |b| */
	if ((__ha - __hb) > __INT32_C(0x3c00000))
		return __a + __b; /* x/y > 2**60 */
	__k = 0;
	if (__ha > __INT32_C(0x5f300000)) {      /* a>2**500 */
		if (__ha >= __INT32_C(0x7ff00000)) { /* Inf or NaN */
			__uint32_t __low;
			__w = __a + __b; /* for sNaN */
			__LIBM_GET_LOW_WORD(__low, __a);
			if (((__ha & __INT32_C(0xfffff)) | __low) == 0)
				__w = __a;
			__LIBM_GET_LOW_WORD(__low, __b);
			if (((__hb ^ __INT32_C(0x7ff00000)) | __low) == 0)
				__w = __b;
			return __w;
		}
		/* scale a and b by 2**-600 */
		__ha -= __INT32_C(0x25800000);
		__hb -= __INT32_C(0x25800000);
		__k += 600;
		__LIBM_SET_HIGH_WORD(__a, __ha);
		__LIBM_SET_HIGH_WORD(__b, __hb);
	}
	if (__hb < __INT32_C(0x20b00000)) {      /* b < 2**-500 */
		if (__hb <= __INT32_C(0x000fffff)) { /* subnormal b or 0 */
			__uint32_t __low;
			__LIBM_GET_LOW_WORD(__low, __b);
			if ((__hb | __low) == 0)
				return __a;
			__t1 = 0;
			__LIBM_SET_HIGH_WORD(__t1, __INT32_C(0x7fd00000)); /* t1=2^1022 */
			__b *= __t1;
			__a *= __t1;
			__k -= 1022;
		} else {                           /* scale a and b by 2^600 */
			__ha += __INT32_C(0x25800000); /* a *= 2^600 */
			__hb += __INT32_C(0x25800000); /* b *= 2^600 */
			__k -= 600;
			__LIBM_SET_HIGH_WORD(__a, __ha);
			__LIBM_SET_HIGH_WORD(__b, __hb);
		}
	}
	/* medium size a and b */
	__w = __a - __b;
	if (__w > __b) {
		__t1 = 0;
		__LIBM_SET_HIGH_WORD(__t1, __ha);
		__t2 = __a - __t1;
		__w  = __ieee754_sqrt(__t1 * __t1 - (__b * (-__b) - __t2 * (__a + __t1)));
	} else {
		__a  = __a + __a;
		__y1 = 0;
		__LIBM_SET_HIGH_WORD(__y1, __hb);
		__y2 = __b - __y1;
		__t1 = 0;
		__LIBM_SET_HIGH_WORD(__t1, __ha + __INT32_C(0x00100000));
		__t2 = __a - __t1;
		__w  = __ieee754_sqrt(__t1 * __y1 - (__w * (-__w) - (__t1 * __y2 + __t2 * __b)));
	}
	if (__k != 0)
		return __ieee754_scalbn(__w, (int)__k);
	return __w;
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

__LIBM_LOCAL_FUNC(hypotl) __ATTR_WUNUSED __ATTR_CONST __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_hypotl)(__IEEE854_LONG_DOUBLE_TYPE__ __x,
                              __IEEE854_LONG_DOUBLE_TYPE__ __y) {
	__IEEE854_LONG_DOUBLE_TYPE__ __a, __b, __t1, __t2, __y1, __y2, __w;
	__uint32_t __j, __k, __ea_, __eb_;
	__LIBM_GET_LDOUBLE_EXP(__ea_, __x);
	__ea_ &= 0x7fff;
	__LIBM_GET_LDOUBLE_EXP(__eb_, __y);
	__eb_ &= 0x7fff;
	if (__eb_ > __ea_) {
		__a   = __y;
		__b   = __x;
		__j   = __ea_;
		__ea_ = __eb_;
		__eb_ = __j;
	} else {
		__a = __x;
		__b = __y;
	}
	__LIBM_SET_LDOUBLE_EXP(__a, __ea_); /* a <- |a| */
	__LIBM_SET_LDOUBLE_EXP(__b, __eb_); /* b <- |b| */
	if ((__ea_ - __eb_) > 0x46) {
		return __a + __b;
	} /* x/y > 2**70 */
	__k = 0;
	if (__ea_ > 0x5f3f) {      /* a>2**8000 */
		if (__ea_ == 0x7fff) { /* Inf or NaN */
			__uint32_t __high, __low;
			__w = __a + __b; /* for sNaN */
			__LIBM_GET_LDOUBLE_WORDS(__ea_, __high, __low, __a);
			if (((__high & __INT32_C(0x7fffffff)) | __low) == 0)
				__w = __a;
			__LIBM_GET_LDOUBLE_WORDS(__eb_, __high, __low, __b);
			if (((__eb_ ^ 0x7fff) | (__high & __INT32_C(0x7fffffff)) | __low) == 0)
				__w = __b;
			return __w;
		}
		/* scale a and b by 2**-9600 */
		__ea_ -= 0x2580;
		__eb_ -= 0x2580;
		__k += 9600;
		__LIBM_SET_LDOUBLE_EXP(__a, __ea_);
		__LIBM_SET_LDOUBLE_EXP(__b, __eb_);
	}
	if (__eb_ < 0x20bf) { /* b < 2**-8000 */
		if (__eb_ == 0) { /* subnormal b or 0 */
			__uint32_t __high, __low;
			__LIBM_GET_LDOUBLE_WORDS(__eb_, __high, __low, __b);
			if ((__high | __low) == 0)
				return __a;
			__LIBM_SET_LDOUBLE_WORDS(__t1, 0x7ffd, __UINT32_C(0x80000000), 0); /* t1=2^16382 */
			__b *= __t1;
			__a *= __t1;
			__k -= 16382;
			__LIBM_GET_LDOUBLE_EXP(__ea_, __a);
			__LIBM_GET_LDOUBLE_EXP(__eb_, __b);
			if (__eb_ > __ea_) {
				__t1  = __a;
				__a   = __b;
				__b   = __t1;
				__j   = __ea_;
				__ea_ = __eb_;
				__eb_ = __j;
			}
		} else {             /* scale a and b by 2^9600 */
			__ea_ += 0x2580; /* a *= 2^9600 */
			__eb_ += 0x2580; /* b *= 2^9600 */
			__k -= 9600;
			__LIBM_SET_LDOUBLE_EXP(__a, __ea_);
			__LIBM_SET_LDOUBLE_EXP(__b, __eb_);
		}
	}
	/* medium size a and b */
	__w = __a - __b;
	if (__w > __b) {
		__uint32_t __high;
		__LIBM_GET_LDOUBLE_MSW(__high, __a);
		__LIBM_SET_LDOUBLE_WORDS(__t1, __ea_, __high, 0);
		__t2 = __a - __t1;
		__w  = __ieee854_sqrtl(__t1 * __t1 - (__b * (-__b) - __t2 * (__a + __t1)));
	} else {
		__uint32_t __high;
		__LIBM_GET_LDOUBLE_MSW(__high, __b);
		__a = __a + __a;
		__LIBM_SET_LDOUBLE_WORDS(__y1, __eb_, __high, 0);
		__y2 = __b - __y1;
		__LIBM_GET_LDOUBLE_MSW(__high, __a);
		__LIBM_SET_LDOUBLE_WORDS(__t1, __ea_ + 1, __high, 0);
		__t2 = __a - __t1;
		__w  = __ieee854_sqrtl(__t1 * __y1 - (__w * (-__w) - (__t1 * __y2 + __t2 * __b)));
	}
	if (__k != 0) {
		return __ieee854_scalbnl(__w, (int)__k);
	}
	return __w;
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_HYPOT_H */
