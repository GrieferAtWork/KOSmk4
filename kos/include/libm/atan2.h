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
#ifndef _LIBM_ATAN2_H
#define _LIBM_ATAN2_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/asm/atan2.h>
#include <libm/atan.h>
#include <libm/fabs.h>
#include <libm/fdlibm.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
#ifndef __ieee754_atan2f
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
#ifndef __libm_tinyf_defined
#define __libm_tinyf_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, tinyf, __IEEE754_FLOAT_C(1.0e-30))
#endif /* !__libm_tinyf_defined */
#ifndef __libm_zerof_defined
#define __libm_zerof_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, zerof, __IEEE754_FLOAT_C(0.0))
#endif /* !__libm_zerof_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, pi_o_4f, __IEEE754_FLOAT_C(7.8539818525e-01)) /* 0x3f490fdb */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, pi_o_2f, __IEEE754_FLOAT_C(1.5707963705e+00)) /* 0x3fc90fdb */
#ifndef __libm_pif_defined
#define __libm_pif_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, pif, __IEEE754_FLOAT_C(3.1415927410e+00))     /* 0x40490fdb */
#endif /* !__libm_pif_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, pi_lof, __IEEE754_FLOAT_C(-8.7422776573e-08)) /* 0xb3bbbd2e */
__LIBM_LOCAL_DECLARE_END

__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_atan2f)(__IEEE754_FLOAT_TYPE__ __y,
                              __IEEE754_FLOAT_TYPE__ __x) {
	__IEEE754_FLOAT_TYPE__ __z;
	__int32_t __k, __m, __hx, __hy, __ix, __iy;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__ix = __hx & 0x7fffffff;
	__LIBM_GET_FLOAT_WORD(__hy, __y);
	__iy = __hy & 0x7fffffff;
	if (__LIBM_FLT_UWORD_IS_NAN(__ix) ||
	    __LIBM_FLT_UWORD_IS_NAN(__iy)) /* x or y is NaN */
		return __x + __y;
	if (__hx == 0x3f800000)
		return __ieee754_atanf(__y); /* x = 1.0 */
	__m = ((__hy >> 31) & 1) | ((__hx >> 30) & 2); /* 2 * sign(x) + sign(y) */

	/* when y = 0 */
	if (__LIBM_FLT_UWORD_IS_ZERO(__iy)) {
		switch (__m) {
		case 0:
		case 1: return __y;                                                  /* atan(+-0, +anything)=+-0 */
		case 2: return __LIBM_LOCAL_VALUE(pif) + __LIBM_LOCAL_VALUE(tinyf);  /* atan(+0, -anything) = pi */
		case 3: return -__LIBM_LOCAL_VALUE(pif) - __LIBM_LOCAL_VALUE(tinyf); /* atan(-0, -anything) =-pi */
		}
	}
	/* when x = 0 */
	if (__LIBM_FLT_UWORD_IS_ZERO(__ix))
		return (__hy < 0) ? -__LIBM_LOCAL_VALUE(pi_o_2f) - __LIBM_LOCAL_VALUE(tinyf)
		                  : __LIBM_LOCAL_VALUE(pi_o_2f) + __LIBM_LOCAL_VALUE(tinyf);

	/* when x is INF */
	if (__LIBM_FLT_UWORD_IS_INFINITE(__ix)) {
		if (__LIBM_FLT_UWORD_IS_INFINITE(__iy)) {
			switch (__m) {
			case 0: return __LIBM_LOCAL_VALUE(pi_o_4f) + __LIBM_LOCAL_VALUE(tinyf);                           /* atan(+INF, +INF) */
			case 1: return -__LIBM_LOCAL_VALUE(pi_o_4f) - __LIBM_LOCAL_VALUE(tinyf);                          /* atan(-INF, +INF) */
			case 2: return __IEEE754_FLOAT_C(3.0) * __LIBM_LOCAL_VALUE(pi_o_4f) + __LIBM_LOCAL_VALUE(tinyf);  /* atan(+INF, -INF) */
			case 3: return __IEEE754_FLOAT_C(-3.0) * __LIBM_LOCAL_VALUE(pi_o_4f) - __LIBM_LOCAL_VALUE(tinyf); /* atan(-INF, -INF) */
			}
		} else {
			switch (__m) {
			case 0: return __LIBM_LOCAL_VALUE(zerof);                            /* atan(+..., +INF) */
			case 1: return -__LIBM_LOCAL_VALUE(zerof);                           /* atan(-..., +INF) */
			case 2: return __LIBM_LOCAL_VALUE(pif) + __LIBM_LOCAL_VALUE(tinyf);  /* atan(+..., -INF) */
			case 3: return -__LIBM_LOCAL_VALUE(pif) - __LIBM_LOCAL_VALUE(tinyf); /* atan(-..., -INF) */
			}
		}
	}
	/* when y is INF */
	if (__LIBM_FLT_UWORD_IS_INFINITE(__iy))
		return (__hy < 0) ? -__LIBM_LOCAL_VALUE(pi_o_2f) - __LIBM_LOCAL_VALUE(tinyf)
		                  : __LIBM_LOCAL_VALUE(pi_o_2f) + __LIBM_LOCAL_VALUE(tinyf);

	/* compute y / x */
	__k = (__iy - __ix) >> 23;
	if (__k > 60)
		__z = __LIBM_LOCAL_VALUE(pi_o_2f) + (float)0.5 * __LIBM_LOCAL_VALUE(pi_lof); /* |y / x| >  2 ** 60 */
	else if (__hx < 0 && __k < -60)
		__z = 0.0; /* |y|/x < -2 ** 60 */
	else {
		__z = __ieee754_atanf(__ieee754_fabsf(__y / __x)); /* safe to do y / x */
	}
	switch (__m) {
	case 0:
		return __z; /* atan(+,+) */

	case 1: {
		__uint32_t zh;
		__LIBM_GET_FLOAT_WORD(zh, __z);
		__LIBM_SET_FLOAT_WORD(__z, zh ^ 0x80000000);
		return __z; /* atan(-,+) */
	}	break;

	case 2:
		return __LIBM_LOCAL_VALUE(pif) - (__z - __LIBM_LOCAL_VALUE(pi_lof)); /* atan(+, -) */

	default:
/*	case 3: */
		return (__z - __LIBM_LOCAL_VALUE(pi_lof)) - __LIBM_LOCAL_VALUE(pif); /* atan(-, -) */
	}
}
#endif /* !__ieee754_atan2f */
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
#ifndef __ieee754_atan2
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
#ifndef __libm_tiny_defined
#define __libm_tiny_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, tiny, __IEEE754_DOUBLE_C(1.0e-300))
#endif /* !__libm_tiny_defined */
#ifndef __libm_zero_defined
#define __libm_zero_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, zero, __IEEE754_DOUBLE_C(0.0))
#endif /* !__libm_zero_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pi_o_4, __IEEE754_DOUBLE_C(7.8539816339744827900E-01)) /* 0x3FE921FB, 0x54442D18 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pi_o_2, __IEEE754_DOUBLE_C(1.5707963267948965580E+00)) /* 0x3FF921FB, 0x54442D18 */
#ifndef __libm_pi_defined
#define __libm_pi_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pi, __IEEE754_DOUBLE_C(3.1415926535897931160E+00))     /* 0x400921FB, 0x54442D18 */
#endif /* !__libm_pi_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, pi_lo, __IEEE754_DOUBLE_C(1.2246467991473531772E-16))  /* 0x3CA1A626, 0x33145C07 */
__LIBM_LOCAL_DECLARE_END

__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_atan2)(__IEEE754_DOUBLE_TYPE__ __y,
                             __IEEE754_DOUBLE_TYPE__ __x) {
	__IEEE754_DOUBLE_TYPE__ __z;
	__int32_t __k, __m, __hx, __hy, __ix, __iy;
	__uint32_t __lx, __ly;
	__LIBM_EXTRACT_WORDS(__hx, __lx, __x);
	__ix = __hx & 0x7fffffff;
	__LIBM_EXTRACT_WORDS(__hy, __ly, __y);
	__iy = __hy & 0x7fffffff;
	if (((__ix | ((__lx | -__lx) >> 31)) > 0x7ff00000) ||
	    ((__iy | ((__ly | -__ly) >> 31)) > 0x7ff00000)) /* x or y is NaN */
		return __x + __y;
	if (((__hx - 0x3ff00000) | __lx) == 0)
		return __ieee754_atan(__y); /* x = 1.0 */
	__m = ((__hy >> 31) & 1) | ((__hx >> 30) & 2); /* 2 * sign(x) + sign(y) */

	/* when y = 0 */
	if ((__iy | __ly) == 0) {
		switch (__m) {
		case 0:
		case 1: return __y;          /* atan(+-0, +anything)=+-0 */
		case 2: return __LIBM_LOCAL_VALUE(pi) + __LIBM_LOCAL_VALUE(tiny);  /* atan(+0, -anything) = pi */
		case 3: return -__LIBM_LOCAL_VALUE(pi) - __LIBM_LOCAL_VALUE(tiny); /* atan(-0, -anything) =-pi */
		}
	}
	/* when x = 0 */
	if ((__ix | __lx) == 0)
		return (__hy < 0) ? -__LIBM_LOCAL_VALUE(pi_o_2) - __LIBM_LOCAL_VALUE(tiny)
		                  : __LIBM_LOCAL_VALUE(pi_o_2) + __LIBM_LOCAL_VALUE(tiny);

	/* when x is INF */
	if (__ix == 0x7ff00000) {
		if (__iy == 0x7ff00000) {
			switch (__m) {
			case 0: return __LIBM_LOCAL_VALUE(pi_o_4) + __LIBM_LOCAL_VALUE(tiny);                            /* atan(+INF, +INF) */
			case 1: return -__LIBM_LOCAL_VALUE(pi_o_4) - __LIBM_LOCAL_VALUE(tiny);                           /* atan(-INF, +INF) */
			case 2: return __IEEE754_DOUBLE_C(3.0) * __LIBM_LOCAL_VALUE(pi_o_4) + __LIBM_LOCAL_VALUE(tiny);  /*atan(+INF, -INF)*/
			case 3: return __IEEE754_DOUBLE_C(-3.0) * __LIBM_LOCAL_VALUE(pi_o_4) - __LIBM_LOCAL_VALUE(tiny); /*atan(-INF, -INF)*/
			}
		} else {
			switch (__m) {
			case 0: return __LIBM_LOCAL_VALUE(zero);                           /* atan(+..., +INF) */
			case 1: return -__LIBM_LOCAL_VALUE(zero);                          /* atan(-..., +INF) */
			case 2: return __LIBM_LOCAL_VALUE(pi) + __LIBM_LOCAL_VALUE(tiny);  /* atan(+..., -INF) */
			case 3: return -__LIBM_LOCAL_VALUE(pi) - __LIBM_LOCAL_VALUE(tiny); /* atan(-..., -INF) */
			}
		}
	}
	/* when y is INF */
	if (__iy == 0x7ff00000)
		return (__hy < 0) ? -__LIBM_LOCAL_VALUE(pi_o_2) - __LIBM_LOCAL_VALUE(tiny)
		                  : __LIBM_LOCAL_VALUE(pi_o_2) + __LIBM_LOCAL_VALUE(tiny);

	/* compute y / x */
	__k = (__iy - __ix) >> 20;
	if (__k > 60)
		__z = __LIBM_LOCAL_VALUE(pi_o_2) + 0.5 * __LIBM_LOCAL_VALUE(pi_lo); /* |y / x| >  2 ** 60 */
	else if (__hx < 0 && __k < -60)
		__z = 0.0; /* |y|/x < -2 ** 60 */
	else {
		__z = __ieee754_atan(__ieee754_fabs(__y / __x)); /* safe to do y / x */
	}
	switch (__m) {
	case 0:
		return __z; /* atan(+,+) */

	case 1: {
		__uint32_t zh;
		__LIBM_GET_HIGH_WORD(zh, __z);
		__LIBM_SET_HIGH_WORD(__z, zh ^ 0x80000000);
		return __z; /* atan(-,+) */
	}	break;

	case 2:
		return __LIBM_LOCAL_VALUE(pi) - (__z - __LIBM_LOCAL_VALUE(pi_lo)); /* atan(+, -) */

	default:
/*	case 3: */
		return (__z - __LIBM_LOCAL_VALUE(pi_lo)) - __LIBM_LOCAL_VALUE(pi); /* atan(-, -) */
	}
}
#endif /* !__ieee754_atan2 */
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifndef __ieee854_atan2l
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
#ifndef __libm_tinyl_defined
#define __libm_tinyl_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, tinyl, __IEEE854_LONG_DOUBLE_C(1.0e-4900))
#endif /* !__libm_tinyl_defined */
#ifndef __libm_zerol_defined
#define __libm_zerol_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, zerol, __IEEE854_LONG_DOUBLE_C(0.0))
#endif /* !__libm_zerol_defined */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, pi_o_4l, __IEEE854_LONG_DOUBLE_C(7.85398163397448309628202E-01)) /* 0x3FFE, 0xC90FDAA2, 0x2168C235 */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, pi_o_2l, __IEEE854_LONG_DOUBLE_C(1.5707963267948966192564E+00))  /* 0x3FFF, 0xC90FDAA2, 0x2168C235 */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, pil, __IEEE854_LONG_DOUBLE_C(3.14159265358979323851281E+00))     /* 0x4000, 0xC90FDAA2, 0x2168C235 */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, pi_lol, __IEEE854_LONG_DOUBLE_C(-5.01655761266833202345176e-20)) /* 0xBFBE, 0xECE675D1, 0xFC8F8CBB */
__LIBM_LOCAL_DECLARE_END

__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_atan2l)(__IEEE854_LONG_DOUBLE_TYPE__ __y,
                              __IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__IEEE854_LONG_DOUBLE_TYPE__ __z;
	__int32_t __k, __m, __hx, __hy, __ix, __iy;
	__uint32_t __sx, __sy, __lx, __ly;
	__LIBM_GET_LDOUBLE_WORDS(__sx, __hx, __lx, __x);
	__ix = __sx & 0x7fff;
	__lx |= __hx & __INT32_C(0x7fffffff);
	__LIBM_GET_LDOUBLE_WORDS(__sy, __hy, __ly, __y);
	__iy = __sy & 0x7fff;
	__ly |= __hy & __INT32_C(0x7fffffff);
	if (((2 * __ix | ((__lx | -__lx) >> 31)) > __UINT32_C(0xfffe)) ||
	    ((2 * __iy | ((__ly | -__ly) >> 31)) > __UINT32_C(0xfffe))) /* x or y is NaN */
		return __x + __y;
	if (((__sx - 0x3fff) | __lx) == 0)
		return __ieee854_atanl(__y);           /* x = 1.0 */
	__m = ((__sy >> 15) & 1) | ((__sx >> 14) & 2); /* 2 * sign(x) + sign(y) */

	/* when y = 0 */
	if ((__iy | __ly) == 0) {
		switch ((int)__m) {
		case 0:
		case 1:
			return __y; /* atan(+-0, +anything)=+-0 */
		case 2:
			return __LIBM_LOCAL_VALUE(pil) + __LIBM_LOCAL_VALUE(tinyl); /* atan(+0, -anything) = pi */
		case 3:
			return -__LIBM_LOCAL_VALUE(pil) - __LIBM_LOCAL_VALUE(tinyl); /* atan(-0, -anything) =-pi */
		}
	}
	/* when x = 0 */
	if ((__ix | __lx) == 0)
		return (__sy & 0x8000) ? -__LIBM_LOCAL_VALUE(pi_o_2l) - __LIBM_LOCAL_VALUE(tinyl)
		                       : __LIBM_LOCAL_VALUE(pi_o_2l) + __LIBM_LOCAL_VALUE(tinyl);

	/* when x is INF */
	if (__ix == 0x7fff) {
		if (__iy == 0x7fff) {
			switch ((int)__m) {
			case 0:
				return __LIBM_LOCAL_VALUE(pi_o_4l) + __LIBM_LOCAL_VALUE(tinyl); /* atan(+INF, +INF) */
			case 1:
				return -__LIBM_LOCAL_VALUE(pi_o_4l) - __LIBM_LOCAL_VALUE(tinyl); /* atan(-INF, +INF) */
			case 2:
				return 3.0 * __LIBM_LOCAL_VALUE(pi_o_4l) + __LIBM_LOCAL_VALUE(tinyl); /*atan(+INF, -INF) */
			case 3:
				return -3.0 * __LIBM_LOCAL_VALUE(pi_o_4l) - __LIBM_LOCAL_VALUE(tinyl); /*atan(-INF, -INF) */
			}
		} else {
			switch ((int)__m) {
			case 0:
				return __LIBM_LOCAL_VALUE(zerol); /* atan(+..., +INF) */
			case 1:
				return -__LIBM_LOCAL_VALUE(zerol); /* atan(-..., +INF) */
			case 2:
				return __LIBM_LOCAL_VALUE(pil) + __LIBM_LOCAL_VALUE(tinyl); /* atan(+..., -INF) */
			case 3:
				return -__LIBM_LOCAL_VALUE(pil) - __LIBM_LOCAL_VALUE(tinyl); /* atan(-..., -INF) */
			}
		}
	}
	/* when y is INF */
	if (__iy == 0x7fff)
		return (__sy & 0x8000) ? -__LIBM_LOCAL_VALUE(pi_o_2l) - __LIBM_LOCAL_VALUE(tinyl)
		                       : __LIBM_LOCAL_VALUE(pi_o_2l) + __LIBM_LOCAL_VALUE(tinyl);

	/* compute y / x */
	__k = __iy - __ix;
	if (__k > 70)
		__z = __LIBM_LOCAL_VALUE(pi_o_2l) + 0.5L * __LIBM_LOCAL_VALUE(pi_lol); /* |y / x| >  2 ** 70 */
	else if ((__sx & 0x8000) && __k < -70)
		__z = 0.0; /* |y|/x < -2 ** 70 */
	else {
		__z = __ieee854_atanl(__ieee854_fabsl(__y / __x)); /* safe to do y / x */
	}
	switch ((int)__m) {

	case 0:
		return __z; /* atan(+,+) */

	case 1: {
		__uint32_t __sz;
		__LIBM_GET_LDOUBLE_EXP(__sz, __z);
		__LIBM_SET_LDOUBLE_EXP(__z, __sz ^ __UINT32_C(0x8000));
		return __z; /* atan(-,+) */
	}	break;

	case 2:
		return __LIBM_LOCAL_VALUE(pil) - (__z - __LIBM_LOCAL_VALUE(pi_lol)); /* atan(+, -) */

	default:
/*	case 3: */
		return (__z - __LIBM_LOCAL_VALUE(pi_lol)) - __LIBM_LOCAL_VALUE(pil); /* atan(-, -) */
	}
}
#endif /* !__ieee854_atan2l */
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_ATAN2_H */
