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
#ifndef _LIBM_LOG10_H
#define _LIBM_LOG10_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/expm1.h>
#include <libm/fabs.h>
#include <libm/fdlibm.h>
#include <libm/frexp.h>
#include <libm/log.h>

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
#ifndef __libm_two25f_defined
#define __libm_two25f_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, two25f, __IEEE754_FLOAT_C(3.355443200e+07)) /* 0x4c000000 */
#endif /* !__libm_two25f_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, ivln10f, __IEEE754_FLOAT_C(4.3429449201e-01))    /* 0x3ede5bd9 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, log10_2hif, __IEEE754_FLOAT_C(3.0102920532e-01)) /* 0x3e9a2080 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, log10_2lof, __IEEE754_FLOAT_C(7.9034151668e-07)) /* 0x355427db */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(log10f) __ATTR_WUNUSED __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_log10f)(__IEEE754_FLOAT_TYPE__ __x) {
	__IEEE754_FLOAT_TYPE__ __y, __z;
	__int32_t __i, __k, __hx;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__k = 0;
	if (__hx < __INT32_C(0x00800000)) { /* x < 2**-126  */
		if ((__hx & __INT32_C(0x7fffffff)) == 0)
			return -__LIBM_LOCAL_VALUE(two25f) / (__x - __x); /* log(+-0)=-inf */
		if (__hx < 0)
			return (__x - __x) / (__x - __x); /* log(-#) = NaN */
		__k -= 25;
		__x *= __LIBM_LOCAL_VALUE(two25f); /* subnormal number, scale up x */
		__LIBM_GET_FLOAT_WORD(__hx, __x);
	}
	if (__hx >= __INT32_C(0x7f800000))
		return __x + __x;
	__k += (__hx >> 23) - 127;
	__i  = ((__uint32_t)__k & __UINT32_C(0x80000000)) >> 31;
	__hx = (__hx & __INT32_C(0x007fffff)) | ((0x7f - __i) << 23);
	__y  = (__IEEE754_FLOAT_TYPE__)(__k + __i);
	__LIBM_SET_FLOAT_WORD(__x, __hx);
	__z = __y * __LIBM_LOCAL_VALUE(log10_2lof) + __LIBM_LOCAL_VALUE(ivln10f) * __ieee754_logf(__x);
	return __z + __y * __LIBM_LOCAL_VALUE(log10_2hif);
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
#ifndef __libm_two54_defined
#define __libm_two54_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, two54, __IEEE754_DOUBLE_C(1.80143985094819840000e+16)) /* 0x43500000, 0x00000000 */
#endif /* !__libm_two54_defined */
#ifndef __libm_zero_defined
#define __libm_zero_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, zero, __IEEE754_DOUBLE_C(0.00000000000000000000e+00)) /* 0x00000000, 0x00000000 */
#endif /* !__libm_zero_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, ivln10, __IEEE754_DOUBLE_C(4.34294481903251816668e-01))    /* 0x3FDBCB7B, 0x1526E50E */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, log10_2hi, __IEEE754_DOUBLE_C(3.01029995663611771306e-01)) /* 0x3FD34413, 0x509F6000 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, log10_2lo, __IEEE754_DOUBLE_C(3.69423907715893078616e-13)) /* 0x3D59FEF3, 0x11F12B36 */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(log10) __ATTR_WUNUSED __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_log10)(__IEEE754_DOUBLE_TYPE__ __x) {
	__IEEE754_DOUBLE_TYPE__ __y, __z;
	__int32_t __i, __k, __hx;
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
	__i  = ((__uint32_t)__k & __UINT32_C(0x80000000)) >> 31;
	__hx = (__hx & __INT32_C(0x000fffff)) | ((0x3ff - __i) << 20);
	__y  = (__IEEE754_DOUBLE_TYPE__)(__k + __i);
	__LIBM_SET_HIGH_WORD(__x, __hx);
	__z = __y * __LIBM_LOCAL_VALUE(log10_2lo) + __LIBM_LOCAL_VALUE(ivln10) * __ieee754_log(__x);
	return __z + __y * __LIBM_LOCAL_VALUE(log10_2hi);
}
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
/*
   Cephes Math Library Release 2.2:  January, 1991
   Copyright 1984, 1991 by Stephen L. Moshier
   Adapted for glibc November, 2001

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

__LIBM_LOCAL_DECLARE_BEGIN
/* Coefficients for ln(1+x) = x - x**2/2 + x**3 P(x)/Q(x)
 * 1/sqrt(2) <= x < sqrt(2)
 * Theoretical peak relative error = 5.3e-37,
 * relative  peak  error  spread  =   2.3e-14 */
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE854_LONG_DOUBLE_TYPE__, log10Pl, 13) {
	__IEEE854_LONG_DOUBLE_C(1.313572404063446165910279910527789794488E4),
	__IEEE854_LONG_DOUBLE_C(7.771154681358524243729929227226708890930E4),
	__IEEE854_LONG_DOUBLE_C(2.014652742082537582487669938141683759923E5),
	__IEEE854_LONG_DOUBLE_C(3.007007295140399532324943111654767187848E5),
	__IEEE854_LONG_DOUBLE_C(2.854829159639697837788887080758954924001E5),
	__IEEE854_LONG_DOUBLE_C(1.797628303815655343403735250238293741397E5),
	__IEEE854_LONG_DOUBLE_C(7.594356839258970405033155585486712125861E4),
	__IEEE854_LONG_DOUBLE_C(2.128857716871515081352991964243375186031E4),
	__IEEE854_LONG_DOUBLE_C(3.824952356185897735160588078446136783779E3),
	__IEEE854_LONG_DOUBLE_C(4.114517881637811823002128927449878962058E2),
	__IEEE854_LONG_DOUBLE_C(2.321125933898420063925789532045674660756E1),
	__IEEE854_LONG_DOUBLE_C(4.998469661968096229986658302195402690910E-1),
	__IEEE854_LONG_DOUBLE_C(1.538612243596254322971797716843006400388E-6),
};

__LIBM_LOCAL_DECLARE_ARRAY(__IEEE854_LONG_DOUBLE_TYPE__, log10Ql, 12) {
	__IEEE854_LONG_DOUBLE_C(3.940717212190338497730839731583397586124E4),
	__IEEE854_LONG_DOUBLE_C(2.626900195321832660448791748036714883242E5),
	__IEEE854_LONG_DOUBLE_C(7.777690340007566932935753241556479363645E5),
	__IEEE854_LONG_DOUBLE_C(1.347518538384329112529391120390701166528E6),
	__IEEE854_LONG_DOUBLE_C(1.514882452993549494932585972882995548426E6),
	__IEEE854_LONG_DOUBLE_C(1.158019977462989115839826904108208787040E6),
	__IEEE854_LONG_DOUBLE_C(6.132189329546557743179177159925690841200E5),
	__IEEE854_LONG_DOUBLE_C(2.248234257620569139969141618556349415120E5),
	__IEEE854_LONG_DOUBLE_C(5.605842085972455027590989944010492125825E4),
	__IEEE854_LONG_DOUBLE_C(9.147150349299596453976674231612674085381E3),
	__IEEE854_LONG_DOUBLE_C(9.104928120962988414618126155557301584078E2),
	__IEEE854_LONG_DOUBLE_C(4.839208193348159620282142911143429644326E1),
	/* __IEEE854_LONG_DOUBLE_C(1.000000000000000000000000000000000000000E0), */
};
/* Coefficients for log(x) = z + z^3 P(z^2)/Q(z^2),
 * where z = 2(x-1)/(x+1)
 * 1/sqrt(2) <= x < sqrt(2)
 * Theoretical peak relative error = 1.1e-35,
 * relative   peak   error   spread    1.1e-9 */
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE854_LONG_DOUBLE_TYPE__, log10Rl, 6) {
	__IEEE854_LONG_DOUBLE_C(1.418134209872192732479751274970992665513E5),
	__IEEE854_LONG_DOUBLE_C(-8.977257995689735303686582344659576526998E4),
	__IEEE854_LONG_DOUBLE_C(2.048819892795278657810231591630928516206E4),
	__IEEE854_LONG_DOUBLE_C(-2.024301798136027039250415126250455056397E3),
	__IEEE854_LONG_DOUBLE_C(8.057002716646055371965756206836056074715E1),
	__IEEE854_LONG_DOUBLE_C(-8.828896441624934385266096344596648080902E-1),
};
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE854_LONG_DOUBLE_TYPE__, log10Sl, 6) {
	__IEEE854_LONG_DOUBLE_C(1.701761051846631278975701529965589676574E6),
	__IEEE854_LONG_DOUBLE_C(-1.332535117259762928288745111081235577029E6),
	__IEEE854_LONG_DOUBLE_C(4.001557694070773974936904547424676279307E5),
	__IEEE854_LONG_DOUBLE_C(-5.748542087379434595104154610899551484314E4),
	__IEEE854_LONG_DOUBLE_C(3.998526750980007367835804959888064681098E3),
	__IEEE854_LONG_DOUBLE_C(-1.186359407982897997337150403816839480438E2),
	/* __IEEE854_LONG_DOUBLE_C(1.000000000000000000000000000000000000000E0) */
};
/* log10(2) */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, L102Al, __IEEE854_LONG_DOUBLE_C(0.3125))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, L102Bl, __IEEE854_LONG_DOUBLE_C(-1.14700043360188047862611052755069732318101185E-2))
/* log10(e) */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, L10EAl, __IEEE854_LONG_DOUBLE_C(0.5))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, L10EBl, __IEEE854_LONG_DOUBLE_C(-6.570551809674817234887108108339491770560299E-2))
/* sqrt(2)/2 */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, SQRTHl, __IEEE854_LONG_DOUBLE_C(7.071067811865475244008443621048490392848359E-1))
__LIBM_LOCAL_DECLARE_END

/* Evaluate P[n] x^n  +  P[n-1] x^(n-1)  +  ...  +  P[0] */
__LIBM_LOCAL_FUNC(log10l_neval) __ATTR_NONNULL((2)) __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __libm_log10l_neval)(__IEEE854_LONG_DOUBLE_TYPE__ __x,
                                 __IEEE854_LONG_DOUBLE_TYPE__ const *__p, int __n) {
	__IEEE854_LONG_DOUBLE_TYPE__ __y;
	__p += __n;
	__y = *__p--;
	do {
		__y = __y * __x + *__p--;
	} while (--__n > 0);
	return __y;
}


/* Evaluate x^n+1  +  P[n] x^(n)  +  P[n-1] x^(n-1)  +  ...  +  P[0] */
__LIBM_LOCAL_FUNC(log10l_deval) __ATTR_NONNULL((2)) __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __libm_log10l_deval)(__IEEE854_LONG_DOUBLE_TYPE__ __x,
                                 __IEEE854_LONG_DOUBLE_TYPE__ const *__p, int __n) {
	__IEEE854_LONG_DOUBLE_TYPE__ __y;
	__p += __n;
	__y = __x + *__p--;
	do {
		__y = __y * __x + *__p--;
	} while (--__n > 0);
	return __y;
}


__LIBM_LOCAL_FUNC(log10l) __ATTR_WUNUSED __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_log10l)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__IEEE854_LONG_DOUBLE_TYPE__ __z;
	__IEEE854_LONG_DOUBLE_TYPE__ __y;
	int __e;
	__uint32_t __exp;

	/* Test for domain */
	__LIBM_GET_LDOUBLE_EXP(__exp, __x);
	if ((__exp & 0x7fff) == 0)
		return (-__IEEE854_LONG_DOUBLE_C(1.0) / (__x - __x));
	if (__exp & 0x8000)
		return (__x - __x) / (__x - __x);
	if (__exp >= 0x7fff)
		return __x + __x;

	/* separate mantissa from exponent */

	/* Note, frexp is used so that denormal numbers will be handled properly. */
	__x = __ieee854_frexpl(__x, &__e);

	/* logarithm using log(x) = z + z**3 P(z)/Q(z), where z = 2(x-1)/x+1) */
	if ((__e > 2) || (__e < -2)) {
		if (__x < __LIBM_LOCAL_VALUE(SQRTHl)) { /* 2( 2x-1 )/( 2x+1 ) */
			__e -= 1;
			__z = __x - __IEEE854_LONG_DOUBLE_C(0.5);
			__y = __IEEE854_LONG_DOUBLE_C(0.5) * __z + __IEEE854_LONG_DOUBLE_C(0.5);
		} else { /*  2 (x-1)/(x+1)   */
			__z = __x - __IEEE854_LONG_DOUBLE_C(0.5);
			__z -= __IEEE854_LONG_DOUBLE_C(0.5);
			__y = __IEEE854_LONG_DOUBLE_C(0.5) * __x + __IEEE854_LONG_DOUBLE_C(0.5);
		}
		__x = __z / __y;
		__z = __x * __x;
		__y = __x * (__z * __libm_log10l_neval(__z, __LIBM_LOCAL_VALUE(log10Rl), 5) /
		             __libm_log10l_deval(__z, __LIBM_LOCAL_VALUE(log10Sl), 5));
		goto __done;
	}

	/* logarithm using log(1+x) = x - .5x**2 + x**3 P(x)/Q(x) */
	if (__x < __LIBM_LOCAL_VALUE(SQRTHl)) {
		__e -= 1;
		__x = __IEEE854_LONG_DOUBLE_C(2.0) * __x -
		      __IEEE854_LONG_DOUBLE_C(1.0); /* 2x - 1 */
	} else {
		__x = __x - __IEEE854_LONG_DOUBLE_C(1.0);
	}
	__z = __x * __x;
	__y = __x * (__z * __libm_log10l_neval(__x, __LIBM_LOCAL_VALUE(log10Pl), 12) /
	             __libm_log10l_deval(__x, __LIBM_LOCAL_VALUE(log10Ql), 11));
	__y = __y - __IEEE854_LONG_DOUBLE_C(0.5) * __z;

__done:
	/* Multiply log of fraction by log10(e) and base 2 exponent by log10(2). */
	__z = __y * __LIBM_LOCAL_VALUE(L10EBl);
	__z += __x * __LIBM_LOCAL_VALUE(L10EBl);
	__z += __e * __LIBM_LOCAL_VALUE(L102Bl);
	__z += __y * __LIBM_LOCAL_VALUE(L10EAl);
	__z += __x * __LIBM_LOCAL_VALUE(L10EAl);
	__z += __e * __LIBM_LOCAL_VALUE(L102Al);
	return __z;
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_LOG10_H */
