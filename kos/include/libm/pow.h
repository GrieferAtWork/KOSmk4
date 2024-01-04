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
#ifndef _LIBM_POW_H
#define _LIBM_POW_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <ieee754.h>

#include <bits/math-constants.h>
#include <bits/types.h>

#include <libm/fabs.h>
#include <libm/fdlibm.h>
#include <libm/scalbn.h>
#include <libm/sqrt.h>

#if defined(__IEEE754_FLOAT_TYPE__) || defined(__IEEE754_DOUBLE_TYPE__)
#if ((!defined(__NANF) && (defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) ||       \
                           defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__))) ||    \
     (!defined(__NAN) && (defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||       \
                          defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__))) ||    \
     (!defined(__NANL) && (defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || \
                           defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__))))
#include <libm/nan.h>
#endif /* ... */
#endif /* __IEEE754_FLOAT_TYPE__ || __IEEE754_DOUBLE_TYPE__ */

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
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_FLOAT_TYPE__, bpf, 2) { __IEEE754_FLOAT_C(1.0), __IEEE754_FLOAT_C(1.5) };
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_FLOAT_TYPE__, dp_hf, 2) { __IEEE754_FLOAT_C(0.0), __IEEE754_FLOAT_C(5.84960938e-01) }; /* 0x3f15c000 */
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_FLOAT_TYPE__, dp_lf, 2) { __IEEE754_FLOAT_C(0.0), __IEEE754_FLOAT_C(1.56322085e-06) }; /* 0x35d1cfdc */
#ifndef __libm_zerof_defined
#define __libm_zerof_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, zerof, __IEEE754_FLOAT_C(0.0000000000e+00)) /* 0x00000000 */
#endif /* !__libm_zerof_defined */
#ifndef __libm_onef_defined
#define __libm_onef_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, onef, __IEEE754_FLOAT_C(1.0))
#endif /* !__libm_onef_defined */
#ifndef __libm_twof_defined
#define __libm_twof_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, twof, __IEEE754_FLOAT_C(2.0))
#endif /* !__libm_twof_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, two24f, __IEEE754_FLOAT_C(16777216.0)) /* 0x4b800000 */
#ifndef __libm_hugef_defined
#define __libm_hugef_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, hugef, __IEEE754_FLOAT_C(1.0e30))
#endif /* !__libm_hugef_defined */
#ifndef __libm_tinyf_defined
#define __libm_tinyf_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, tinyf, __IEEE754_FLOAT_C(1.0e-30))
#endif /* !__libm_tinyf_defined */
/* poly coefs for (3/2)*(log(x)-2s-2/3*s**3 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, L1f, __IEEE754_FLOAT_C(6.0000002384e-01))      /* 0x3f19999a */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, L2f, __IEEE754_FLOAT_C(4.2857143283e-01))      /* 0x3edb6db7 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, L3f, __IEEE754_FLOAT_C(3.3333334327e-01))      /* 0x3eaaaaab */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, L4f, __IEEE754_FLOAT_C(2.7272811532e-01))      /* 0x3e8ba305 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, L5f, __IEEE754_FLOAT_C(2.3066075146e-01))      /* 0x3e6c3255 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, L6f, __IEEE754_FLOAT_C(2.0697501302e-01))      /* 0x3e53f142 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, P1f, __IEEE754_FLOAT_C(1.6666667163e-01))      /* 0x3e2aaaab */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, P2f, __IEEE754_FLOAT_C(-2.7777778450e-03))     /* 0xbb360b61 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, P3f, __IEEE754_FLOAT_C(6.6137559770e-05))      /* 0x388ab355 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, P4f, __IEEE754_FLOAT_C(-1.6533901999e-06))     /* 0xb5ddea0e */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, P5f, __IEEE754_FLOAT_C(4.1381369442e-08))      /* 0x3331bb4c */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, lg2f, __IEEE754_FLOAT_C(6.9314718246e-01))     /* 0x3f317218 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, lg2_hf, __IEEE754_FLOAT_C(6.93145752e-01))     /* 0x3f317200 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, lg2_lf, __IEEE754_FLOAT_C(1.42860654e-06))     /* 0x35bfbe8c */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, ovtf, __IEEE754_FLOAT_C(4.2995665694e-08))     /* -(128-log2(ovfl+.5ulp)) */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, cpf, __IEEE754_FLOAT_C(9.6179670095e-01))      /* 0x3f76384f =2/(3ln2) */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, cp_hf, __IEEE754_FLOAT_C(9.6179199219e-01))    /* 0x3f763800 =head of cp */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, cp_lf, __IEEE754_FLOAT_C(4.7017383622e-06))    /* 0x369dc3a0 =tail of cp_h */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, ivln2f, __IEEE754_FLOAT_C(1.4426950216e+00))   /* 0x3fb8aa3b =1/ln2 */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, ivln2_hf, __IEEE754_FLOAT_C(1.4426879883e+00)) /* 0x3fb8aa00 =16b 1/ln2*/
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, ivln2_lf, __IEEE754_FLOAT_C(7.0526075433e-06)) /* 0x36eca570 =1/ln2 tail*/
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(powf) __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_powf)(__IEEE754_FLOAT_TYPE__ __x,
                            __IEEE754_FLOAT_TYPE__ __y) {
	__IEEE754_FLOAT_TYPE__ __z, __ax, __z_h, __z_l, __p_h, __p_l;
	__IEEE754_FLOAT_TYPE__ __y1, __t1, __t2, __r, __s, __t, __u, __v, __w;
	__int32_t __i, __j, __k, __yisint, __n;
	__int32_t __hx, __hy, __ix, __iy, __is;

	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__LIBM_GET_FLOAT_WORD(__hy, __y);
	__ix = __hx & 0x7fffffff;
	__iy = __hy & 0x7fffffff;

	/* y==zero: x**0 = 1 */
	if (__LIBM_FLT_UWORD_IS_ZERO(__iy))
		return __LIBM_LOCAL_VALUE(onef);

	/* x|y==NaN return NaN unless x==1 then return 1 */
	if (__LIBM_FLT_UWORD_IS_NAN(__ix) ||
	    __LIBM_FLT_UWORD_IS_NAN(__iy)) {
		if (__ix == 0x3f800000) {
			return __LIBM_LOCAL_VALUE(onef);
		} else {
#if defined(__NANF) && defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)
			return __NANF;
#elif defined(__NAN) && defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
			return __NAN;
#elif defined(__NANL) && defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
			return __NANL;
#else /* ... */
			return __ieee754_nanf("");
#endif /* !... */
		}
	}

	/* determine if y is an odd int when x < 0
	 * yisint = 0   ... y is not an integer
	 * yisint = 1   ... y is an odd int
	 * yisint = 2   ... y is an even int */
	__yisint = 0;
	if (__hx < 0) {
		if (__iy >= 0x4b800000) {
			__yisint = 2; /* even integer y */
		} else if (__iy >= 0x3f800000) {
			__k = (__iy >> 23) - 0x7f; /* exponent */
			__j = __iy >> (23 - __k);
			if ((__j << (23 - __k)) == __iy)
				__yisint = 2 - (__j & 1);
		}
	}

	/* special value of y */
	if (__LIBM_FLT_UWORD_IS_INFINITE(__iy)) { /* y is +-inf */
		if (__ix == 0x3f800000) {
			return __LIBM_LOCAL_VALUE(onef); /* +-1**+-inf = 1 */
		} else if (__ix > 0x3f800000) { /* (|x|>1)**+-inf = inf,0 */
			return (__hy >= 0) ? __y : __LIBM_LOCAL_VALUE(zerof);
		} else { /* (|x| < 1)**-,+inf = inf,0 */
			return (__hy < 0) ? -__y : __LIBM_LOCAL_VALUE(zerof);
		}
	}
	if (__iy == 0x3f800000) { /* y is  +-1 */
		if (__hy < 0) {
			return __LIBM_LOCAL_VALUE(onef) / __x;
		} else {
			return __x;
		}
	}
	if (__hy == 0x40000000)
		return __x * __x;       /* y is  2 */
	if (__hy == 0x3f000000) { /* y is  0.5 */
		if (__hx >= 0)        /* x >= +0 */
			return __ieee754_sqrtf(__x);
	}

	__ax = __ieee754_fabsf(__x);
	/* special value of x */
	if (__LIBM_FLT_UWORD_IS_INFINITE(__ix) ||
	    __LIBM_FLT_UWORD_IS_ZERO(__ix) ||
	    __ix == 0x3f800000) {
		__z = __ax; /*x is +-0,+-inf,+-1*/
		if (__hy < 0)
			__z = __LIBM_LOCAL_VALUE(onef) / __z; /* z = (1/|x|) */
		if (__hx < 0) {
			if (((__ix - 0x3f800000) | __yisint) == 0) {
				__z = (__z - __z) / (__z - __z); /* (-1)**non-int is NaN */
			} else if (__yisint == 1)
				__z = -__z; /* (x<0)**odd = -(|x|**odd) */
		}
		return __z;
	}

	/* (x<0)**(non-int) is NaN */
	if (((((__uint32_t)__hx >> 31) - 1) | __yisint) == 0)
		return (__x - __x) / (__x - __x);

	/* |y| is huge */
	if (__iy > 0x4d000000) { /* if |y| > 2 ** 27 */
		                   /* over/underflow if x is not close to one */
		if (__ix < 0x3f7ffff8)
			return (__hy < 0) ? __LIBM_LOCAL_VALUE(hugef) * __LIBM_LOCAL_VALUE(hugef)
			                  : __LIBM_LOCAL_VALUE(tinyf) * __LIBM_LOCAL_VALUE(tinyf);
		if (__ix > 0x3f800007)
			return (__hy > 0) ? __LIBM_LOCAL_VALUE(hugef) * __LIBM_LOCAL_VALUE(hugef)
			                  : __LIBM_LOCAL_VALUE(tinyf) * __LIBM_LOCAL_VALUE(tinyf);
		/* now |1-x| is tiny <= 2 ** -20, suffice to compute
	   log(x) by x-x^2/2+x^3/3-x^4/4 */
		__t  = __ax - 1; /* t has 20 trailing zeros */
		__w  = (__t * __t) * (__IEEE754_FLOAT_C(0.5) - __t * (__IEEE754_FLOAT_C(0.333333333333) - __t * __IEEE754_FLOAT_C(0.25)));
		__u  = __LIBM_LOCAL_VALUE(ivln2_hf) * __t; /* ivln2_h has 16 sig. bits */
		__v  = __t * __LIBM_LOCAL_VALUE(ivln2_lf) - __w * __LIBM_LOCAL_VALUE(ivln2f);
		__t1 = __u + __v;
		__LIBM_GET_FLOAT_WORD(__is, __t1);
		__LIBM_SET_FLOAT_WORD(__t1, __is & 0xfffff000);
		__t2 = __v - (__t1 - __u);
	} else {
		__IEEE754_FLOAT_TYPE__ s2, s_h, s_l, t_h, t_l;
		__n = 0;
#ifndef _FLT_NO_DENORMALS
		/* take care subnormal number */
		if (__LIBM_FLT_UWORD_IS_SUBNORMAL(__ix)) {
			__ax *= __LIBM_LOCAL_VALUE(two24f);
			__n -= 24;
			__LIBM_GET_FLOAT_WORD(__ix, __ax);
		}
#endif /* !_FLT_NO_DENORMALS */
		__n += ((__ix) >> 23) - 0x7f;
		__j = __ix & 0x007fffff;
		/* determine interval */
		__ix = __j | 0x3f800000; /* normalize ix */
		if (__j <= 0x1cc471) {
			__k = 0; /* |x| < sqrt(3/2) */
		} else if (__j < 0x5db3d7) {
			__k = 1; /* |x| < sqrt(3)   */
		} else {
			__k = 0;
			__n += 1;
			__ix -= 0x00800000;
		}
		__LIBM_SET_FLOAT_WORD(__ax, __ix);

		/* compute s = s_h+s_l = (x-1)/(x+1) or (x-1.5)/(x+1.5) */
		__u   = __ax - __LIBM_LOCAL_VALUE(bpf)[__k]; /* bp[0]=1.0, bp[1]=1.5 */
		__v   = __LIBM_LOCAL_VALUE(onef) / (__ax + __LIBM_LOCAL_VALUE(bpf)[__k]);
		__s   = __u * __v;
		s_h = __s;
		__LIBM_GET_FLOAT_WORD(__is, s_h);
		__LIBM_SET_FLOAT_WORD(s_h, __is & 0xfffff000);
		/* t_h=ax+bp[k] High */
		__LIBM_SET_FLOAT_WORD(t_h, ((__ix >> 1) | 0x20000000) + 0x0040000 + (__k << 21));
		t_l = __ax - (t_h - __LIBM_LOCAL_VALUE(bpf)[__k]);
		s_l = __v * ((__u - s_h * t_h) - s_h * t_l);
		/* compute log(ax) */
		s2 = __s * __s;
		__r  = s2 * s2 *
		      (__LIBM_LOCAL_VALUE(L1f) +
		       s2 * (__LIBM_LOCAL_VALUE(L2f) +
		             s2 * (__LIBM_LOCAL_VALUE(L3f) +
		                   s2 * (__LIBM_LOCAL_VALUE(L4f) +
		                         s2 * (__LIBM_LOCAL_VALUE(L5f) +
		                               s2 * __LIBM_LOCAL_VALUE(L6f))))));
		__r += s_l * (s_h + __s);
		s2  = s_h * s_h;
		t_h = __IEEE754_FLOAT_C(3.0) + s2 + __r;
		__LIBM_GET_FLOAT_WORD(__is, t_h);
		__LIBM_SET_FLOAT_WORD(t_h, __is & 0xfffff000);
		t_l = __r - ((t_h - __IEEE754_FLOAT_C(3.0)) - s2);
		/* u+v = s*(1+...) */
		__u = s_h * t_h;
		__v = s_l * t_h + t_l * __s;
		/* 2/(3log2)*(s+...) */
		__p_h = __u + __v;
		__LIBM_GET_FLOAT_WORD(__is, __p_h);
		__LIBM_SET_FLOAT_WORD(__p_h, __is & 0xfffff000);
		__p_l = __v - (__p_h - __u);
		__z_h = __LIBM_LOCAL_VALUE(cp_hf) * __p_h; /* cp_h+cp_l = 2/(3*log2) */
		__z_l = __LIBM_LOCAL_VALUE(cp_lf) * __p_h + __p_l * __LIBM_LOCAL_VALUE(cpf) + __LIBM_LOCAL_VALUE(dp_lf)[__k];
		/* log2(ax) = (s+..)*2/(3*log2) = n + dp_h + z_h + z_l */
		__t  = (__IEEE754_FLOAT_TYPE__)__n;
		__t1 = (((__z_h + __z_l) + __LIBM_LOCAL_VALUE(dp_hf)[__k]) + __t);
		__LIBM_GET_FLOAT_WORD(__is, __t1);
		__LIBM_SET_FLOAT_WORD(__t1, __is & 0xfffff000);
		__t2 = __z_l - (((__t1 - __t) - __LIBM_LOCAL_VALUE(dp_hf)[__k]) - __z_h);
	}

	__s = __LIBM_LOCAL_VALUE(onef); /* s (sign of result -ve**odd) = -1 else = 1 */
	if (((((__uint32_t)__hx >> 31) - 1) | (__yisint - 1)) == 0)
		__s = -__LIBM_LOCAL_VALUE(onef); /* (-ve)**(odd int) */

	/* split up y into y1+y2 and compute (y1+y2)*(t1+t2) */
	__LIBM_GET_FLOAT_WORD(__is, __y);
	__LIBM_SET_FLOAT_WORD(__y1, __is & 0xfffff000);
	__p_l = (__y - __y1) * __t1 + __y * __t2;
	__p_h = __y1 * __t1;
	__z   = __p_l + __p_h;
	__LIBM_GET_FLOAT_WORD(__j, __z);
	__i = __j & 0x7fffffff;
	if (__j > 0) {
		if (__i > __LIBM_FLT_UWORD_EXP_MAX) {
			return __s * __LIBM_LOCAL_VALUE(hugef) * __LIBM_LOCAL_VALUE(hugef); /* overflow */
		} else if (__i == __LIBM_FLT_UWORD_EXP_MAX) {
			if (__p_l + __LIBM_LOCAL_VALUE(ovtf) > __z - __p_h)
				return __s * __LIBM_LOCAL_VALUE(hugef) * __LIBM_LOCAL_VALUE(hugef); /* overflow */
		}
	} else {
		if (__i > __LIBM_FLT_UWORD_EXP_MIN) {
			return __s * __LIBM_LOCAL_VALUE(tinyf) * __LIBM_LOCAL_VALUE(tinyf); /* underflow */
		} else if (__i == __LIBM_FLT_UWORD_EXP_MIN) {
			if (__p_l <= __z - __p_h)
				return __s * __LIBM_LOCAL_VALUE(tinyf) * __LIBM_LOCAL_VALUE(tinyf); /* underflow */
		}
	}
	/* compute 2 ** (p_h+p_l) */
	__k = (__i >> 23) - 0x7f;
	__n = 0;
	if (__i > 0x3f000000) { /* if |z| > 0.5, set n = [z+0.5] */
		__n = __j + (0x00800000 >> (__k + 1));
		__k = ((__n & 0x7fffffff) >> 23) - 0x7f; /* new k for n */
		__LIBM_SET_FLOAT_WORD(__t, __n & ~(0x007fffff >> __k));
		__n = ((__n & 0x007fffff) | 0x00800000) >> (23 - __k);
		if (__j < 0)
			__n = -__n;
		__p_h -= __t;
	}
	__t = __p_l + __p_h;
	__LIBM_GET_FLOAT_WORD(__is, __t);
	__LIBM_SET_FLOAT_WORD(__t, __is & 0xfffff000);
	__u  = __t * __LIBM_LOCAL_VALUE(lg2_hf);
	__v  = (__p_l - (__t - __p_h)) * __LIBM_LOCAL_VALUE(lg2f) + __t * __LIBM_LOCAL_VALUE(lg2_lf);
	__z  = __u + __v;
	__w  = __v - (__z - __u);
	__t  = __z * __z;
	__t1 = __z - __t * (__LIBM_LOCAL_VALUE(P1f) +
	                    __t * (__LIBM_LOCAL_VALUE(P2f) +
	                           __t * (__LIBM_LOCAL_VALUE(P3f) +
	                                  __t * (__LIBM_LOCAL_VALUE(P4f) +
	                                         __t * __LIBM_LOCAL_VALUE(P5f)))));
	__r  = (__z * __t1) / (__t1 - __LIBM_LOCAL_VALUE(twof)) - (__w + __z * __w);
	__z  = __LIBM_LOCAL_VALUE(onef) - (__r - __z);
	__LIBM_GET_FLOAT_WORD(__j, __z);
	__j += (__n << 23);
	if ((__j >> 23) <= 0) {
		__z = __ieee754_scalbnf(__z, (int)__n); /* subnormal output */
	} else {
		__LIBM_SET_FLOAT_WORD(__z, __j);
	}
	return __s * __z;
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

__LIBM_LOCAL_DECLARE_BEGIN
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_DOUBLE_TYPE__, bp, 2) { __IEEE754_DOUBLE_C(1.0), __IEEE754_DOUBLE_C(1.5) };
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_DOUBLE_TYPE__, dp_h, 2) { __IEEE754_DOUBLE_C(0.0), __IEEE754_DOUBLE_C(5.84962487220764160156e-01) }; /* 0x3FE2B803, 0x40000000 */
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_DOUBLE_TYPE__, dp_l, 2) { __IEEE754_DOUBLE_C(0.0), __IEEE754_DOUBLE_C(1.35003920212974897128e-08) }; /* 0x3E4CFDEB, 0x43CFD006 */
#ifndef __libm_zero_defined
#define __libm_zero_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, zero, __IEEE754_DOUBLE_C(0.00000000000000000000e+00)) /* 0x00000000, 0x00000000 */
#endif /* !__libm_zero_defined */
#ifndef __libm_one_defined
#define __libm_one_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, one, __IEEE754_DOUBLE_C(1.0))
#endif /* !__libm_one_defined */
#ifndef __libm_two_defined
#define __libm_two_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, two, __IEEE754_DOUBLE_C(2.0))
#endif /* !__libm_two_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, two53, __IEEE754_DOUBLE_C(9007199254740992.0)) /* 0x43400000, 0x00000000 */
#ifndef __libm_huge_defined
#define __libm_huge_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, huge, __IEEE754_DOUBLE_C(1.0e300))
#endif /* !__libm_huge_defined */
#ifndef __libm_tiny_defined
#define __libm_tiny_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, tiny, __IEEE754_DOUBLE_C(1.0e-300))
#endif /* !__libm_tiny_defined */
/* poly coefs for (3/2)*(log(x)-2s-2/3*s**3 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, L1, __IEEE754_DOUBLE_C(5.99999999999994648725e-01)) /* 0x3FE33333, 0x33333303 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, L2, __IEEE754_DOUBLE_C(4.28571428578550184252e-01)) /* 0x3FDB6DB6, 0xDB6FABFF */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, L3, __IEEE754_DOUBLE_C(3.33333329818377432918e-01)) /* 0x3FD55555, 0x518F264D */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, L4, __IEEE754_DOUBLE_C(2.72728123808534006489e-01)) /* 0x3FD17460, 0xA91D4101 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, L5, __IEEE754_DOUBLE_C(2.30660745775561754067e-01)) /* 0x3FCD864A, 0x93C9DB65 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, L6, __IEEE754_DOUBLE_C(2.06975017800338417784e-01)) /* 0x3FCA7E28, 0x4A454EEF */
#ifndef __libm_P12345_defined
#define __libm_P12345_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, P1, __IEEE754_DOUBLE_C(1.66666666666666019037e-01))  /* 0x3FC55555, 0x5555553E */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, P2, __IEEE754_DOUBLE_C(-2.77777777770155933842e-03)) /* 0xBF66C16C, 0x16BEBD93 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, P3, __IEEE754_DOUBLE_C(6.61375632143793436117e-05))  /* 0x3F11566A, 0xAF25DE2C */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, P4, __IEEE754_DOUBLE_C(-1.65339022054652515390e-06)) /* 0xBEBBBD41, 0xC5D26BF1 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, P5, __IEEE754_DOUBLE_C(4.13813679705723846039e-08))  /* 0x3E663769, 0x72BEA4D0 */
#endif /* !__libm_P12345_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, lg2, __IEEE754_DOUBLE_C(6.93147180559945286227e-01))     /* 0x3FE62E42, 0xFEFA39EF */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, lg2_h, __IEEE754_DOUBLE_C(6.93147182464599609375e-01))   /* 0x3FE62E43, 0x00000000 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, lg2_l, __IEEE754_DOUBLE_C(-1.90465429995776804525e-09))  /* 0xBE205C61, 0x0CA86C39 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, ovt, __IEEE754_DOUBLE_C(8.0085662595372944372e-0017))    /* -(1024-log2(ovfl+.5ulp)) */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, cp, __IEEE754_DOUBLE_C(9.61796693925975554329e-01))      /* 0x3FEEC709, 0xDC3A03FD =2/(3ln2) */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, cp_h, __IEEE754_DOUBLE_C(9.61796700954437255859e-01))    /* 0x3FEEC709, 0xE0000000 =(float)cp */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, cp_l, __IEEE754_DOUBLE_C(-7.02846165095275826516e-09))   /* 0xBE3E2FE0, 0x145B01F5 =tail of cp_h*/
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, ivln2, __IEEE754_DOUBLE_C(1.44269504088896338700e+00))   /* 0x3FF71547, 0x652B82FE =1/ln2 */
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, ivln2_h, __IEEE754_DOUBLE_C(1.44269502162933349609e+00)) /* 0x3FF71547, 0x60000000 =24b 1/ln2*/
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, ivln2_l, __IEEE754_DOUBLE_C(1.92596299112661746887e-08)) /* 0x3E54AE0B, 0xF85DDF44 =1/ln2 tail*/
__LIBM_LOCAL_DECLARE_END


__LIBM_LOCAL_FUNC(pow) __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_pow)(__IEEE754_DOUBLE_TYPE__ __x,
                           __IEEE754_DOUBLE_TYPE__ __y) {
	__IEEE754_DOUBLE_TYPE__ __z, __ax, __z_h, __z_l, __p_h, __p_l;
	__IEEE754_DOUBLE_TYPE__ __y1, __t1, __t2, __r, __s, __t, __u, __v, __w;
	__int32_t __i, __j, __k, __yisint, __n;
	__int32_t __hx, __hy, __ix, __iy;
	__uint32_t __lx, __ly;
	__LIBM_EXTRACT_WORDS(__hx, __lx, __x);
	__LIBM_EXTRACT_WORDS(__hy, __ly, __y);
	__ix = __hx & 0x7fffffff;
	__iy = __hy & 0x7fffffff;

	/* y==zero: x**0 = 1 */
	if ((__iy | __ly) == 0)
		return __LIBM_LOCAL_VALUE(one);

	/* x|y==NaN return NaN unless x==1 then return 1 */
	if (__ix > 0x7ff00000 || ((__ix == 0x7ff00000) && (__lx != 0)) ||
	    __iy > 0x7ff00000 || ((__iy == 0x7ff00000) && (__ly != 0))) {
		if (((__ix - 0x3ff00000) | __lx) == 0) {
			return __LIBM_LOCAL_VALUE(one);
		} else {
#if defined(__NAN) && defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__)
			return __NAN;
#elif defined(__NANF) && defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)
			return __NANF;
#elif defined(__NANL) && defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)
			return __NANL;
#else /* ... */
			return __ieee754_nan("");
#endif /* !... */
		}
	}

	/* determine if y is an odd int when x < 0
	 * yisint = 0    ... y is not an integer
	 * yisint = 1    ... y is an odd int
	 * yisint = 2    ... y is an even int */
	__yisint = 0;
	if (__hx < 0) {
		if (__iy >= 0x43400000) {
			__yisint = 2; /* even integer y */
		} else if (__iy >= 0x3ff00000) {
			__k = (__iy >> 20) - 0x3ff; /* exponent */
			if (__k > 20) {
				__j = __ly >> (52 - __k);
				if ((__j << (52 - __k)) == __ly)
					__yisint = 2 - (__j & 1);
			} else if (__ly == 0) {
				__j = __iy >> (20 - __k);
				if ((__j << (20 - __k)) == __iy)
					__yisint = 2 - (__j & 1);
			}
		}
	}

	/* special value of y */
	if (__ly == 0) {
		if (__iy == 0x7ff00000) { /* y is +-inf */
			if (((__ix - 0x3ff00000) | __lx) == 0) {
				return __LIBM_LOCAL_VALUE(one); /* +-1**+-inf = 1 */
			} else if (__ix >= 0x3ff00000) { /* (|x|>1)**+-inf = inf,0 */
				return (__hy >= 0) ? __y : __LIBM_LOCAL_VALUE(zero);
			} else {
				/* (|x| < 1)**-,+inf = inf,0 */
				return (__hy < 0) ? -__y : __LIBM_LOCAL_VALUE(zero);
			}
		}
		if (__iy == 0x3ff00000) { /* y is  +-1 */
			if (__hy < 0) {
				return __LIBM_LOCAL_VALUE(one) / __x;
			} else {
				return __x;
			}
		}
		if (__hy == 0x40000000)
			return __x * __x;       /* y is  2 */
		if (__hy == 0x3fe00000) { /* y is  0.5 */
			if (__hx >= 0)        /* x >= +0 */
				return __ieee754_sqrt(__x);
		}
	}

	__ax = __ieee754_fabs(__x);
	/* special value of x */
	if (__lx == 0) {
		if (__ix == 0x7ff00000 || __ix == 0 || __ix == 0x3ff00000) {
			__z = __ax; /*x is +-0,+-inf,+-1*/
			if (__hy < 0)
				__z = __LIBM_LOCAL_VALUE(one) / __z; /* z = (1/|x|) */
			if (__hx < 0) {
				if (((__ix - 0x3ff00000) | __yisint) == 0) {
					__z = (__z - __z) / (__z - __z); /* (-1)**non-int is NaN */
				} else if (__yisint == 1)
					__z = -__z; /* (x<0)**odd = -(|x|**odd) */
			}
			return __z;
		}
	}

	/* (x<0)**(non-int) is NaN */
	if (((((__uint32_t)__hx >> 31) - 1) | __yisint) == 0)
		return (__x - __x) / (__x - __x);

	/* |y| is huge */
	if (__iy > 0x41e00000) {     /* if |y| > 2 ** 31 */
		if (__iy > 0x43f00000) { /* if |y| > 2 ** 64, must o/uflow */
			if (__ix <= 0x3fefffff)
				return (__hy < 0) ? __LIBM_LOCAL_VALUE(huge) * __LIBM_LOCAL_VALUE(huge)
				                  : __LIBM_LOCAL_VALUE(tiny) * __LIBM_LOCAL_VALUE(tiny);
			if (__ix >= 0x3ff00000)
				return (__hy > 0) ? __LIBM_LOCAL_VALUE(huge) * __LIBM_LOCAL_VALUE(huge)
				                  : __LIBM_LOCAL_VALUE(tiny) * __LIBM_LOCAL_VALUE(tiny);
		}
		/* over/underflow if x is not close to one */
		if (__ix < 0x3fefffff)
			return (__hy < 0) ? __LIBM_LOCAL_VALUE(huge) * __LIBM_LOCAL_VALUE(huge)
			                  : __LIBM_LOCAL_VALUE(tiny) * __LIBM_LOCAL_VALUE(tiny);
		if (__ix > 0x3ff00000)
			return (__hy > 0) ? __LIBM_LOCAL_VALUE(huge) * __LIBM_LOCAL_VALUE(huge)
			                  : __LIBM_LOCAL_VALUE(tiny) * __LIBM_LOCAL_VALUE(tiny);
		/* now |1-x| is tiny <= 2 ** -20, suffice to compute log(x) by x-x^2/2+x^3/3-x^4/4 */
		__t  = __ax - 1; /* t has 20 trailing zeros */
		__w  = (__t * __t) * (0.5 - __t * (0.3333333333333333333333 - __t * 0.25));
		__u  = __LIBM_LOCAL_VALUE(ivln2_h) * __t; /* ivln2_h has 21 sig. bits */
		__v  = __t * __LIBM_LOCAL_VALUE(ivln2_l) - __w * __LIBM_LOCAL_VALUE(ivln2);
		__t1 = __u + __v;
		__LIBM_SET_LOW_WORD(__t1, 0);
		__t2 = __v - (__t1 - __u);
	} else {
		double s2, s_h, s_l, t_h, t_l;
		__n = 0;
		/* take care subnormal number */
		if (__ix < 0x00100000) {
			__ax *= __LIBM_LOCAL_VALUE(two53);
			__n -= 53;
			__LIBM_GET_HIGH_WORD(__ix, __ax);
		}
		__n += ((__ix) >> 20) - 0x3ff;
		__j = __ix & 0x000fffff;
		/* determine interval */
		__ix = __j | 0x3ff00000; /* normalize ix */
		if (__j <= 0x3988E) {
			__k = 0; /* |x| < sqrt(3/2) */
		} else if (__j < 0xBB67A) {
			__k = 1; /* |x| < sqrt(3)   */
		} else {
			__k = 0;
			__n += 1;
			__ix -= 0x00100000;
		}
		__LIBM_SET_HIGH_WORD(__ax, __ix);

		/* compute s = s_h+s_l = (x-1)/(x+1) or (x-1.5)/(x+1.5) */
		__u   = __ax - __LIBM_LOCAL_VALUE(bp)[__k]; /* bp[0]=1.0, bp[1]=1.5 */
		__v   = __LIBM_LOCAL_VALUE(one) / (__ax + __LIBM_LOCAL_VALUE(bp)[__k]);
		__s   = __u * __v;
		s_h = __s;
		__LIBM_SET_LOW_WORD(s_h, 0);
		/* t_h=ax+bp[k] High */
		t_h = __LIBM_LOCAL_VALUE(zero);
		__LIBM_SET_HIGH_WORD(t_h, ((__ix >> 1) | 0x20000000) + 0x00080000 + (__k << 18));
		t_l = __ax - (t_h - __LIBM_LOCAL_VALUE(bp)[__k]);
		s_l = __v * ((__u - s_h * t_h) - s_h * t_l);
		/* compute log(ax) */
		s2  = __s * __s;
		__r = s2 * s2 *
		     (__LIBM_LOCAL_VALUE(L1) +
		      s2 * (__LIBM_LOCAL_VALUE(L2) +
		            s2 * (__LIBM_LOCAL_VALUE(L3) +
		                  s2 * (__LIBM_LOCAL_VALUE(L4) +
		                        s2 * (__LIBM_LOCAL_VALUE(L5) +
		                              s2 * __LIBM_LOCAL_VALUE(L6))))));
		__r += s_l * (s_h + __s);
		s2  = s_h * s_h;
		t_h = 3.0 + s2 + __r;
		__LIBM_SET_LOW_WORD(t_h, 0);
		t_l = __r - ((t_h - 3.0) - s2);
		/* u+v = s*(1+...) */
		__u = s_h * t_h;
		__v = s_l * t_h + t_l * __s;
		/* 2/(3log2)*(s+...) */
		__p_h = __u + __v;
		__LIBM_SET_LOW_WORD(__p_h, 0);
		__p_l = __v - (__p_h - __u);
		__z_h = __LIBM_LOCAL_VALUE(cp_h) * __p_h; /* cp_h+cp_l = 2/(3*log2) */
		__z_l = __LIBM_LOCAL_VALUE(cp_l) * __p_h +
		        __p_l * __LIBM_LOCAL_VALUE(cp) +
		        __LIBM_LOCAL_VALUE(dp_l)[__k];
		/* log2(ax) = (s+..)*2/(3*log2) = n + dp_h + z_h + z_l */
		__t  = (double)__n;
		__t1 = (((__z_h + __z_l) + __LIBM_LOCAL_VALUE(dp_h)[__k]) + __t);
		__LIBM_SET_LOW_WORD(__t1, 0);
		__t2 = __z_l - (((__t1 - __t) - __LIBM_LOCAL_VALUE(dp_h)[__k]) - __z_h);
	}

	__s = __LIBM_LOCAL_VALUE(one); /* s (sign of result -ve**odd) = -1 else = 1 */
	if (((((__uint32_t)__hx >> 31) - 1) | (__yisint - 1)) == 0)
		__s = -__LIBM_LOCAL_VALUE(one); /* (-ve)**(odd int) */

	/* split up y into y1+y2 and compute (y1+y2)*(t1+t2) */
	__y1 = __y;
	__LIBM_SET_LOW_WORD(__y1, 0);
	__p_l = (__y - __y1) * __t1 + __y * __t2;
	__p_h = __y1 * __t1;
	__z   = __p_l + __p_h;
	__LIBM_EXTRACT_WORDS(__j, __i, __z);
	if (__j >= 0x40900000) {                   /* z >= 1024 */
		if (((__j - 0x40900000) | __i) != 0) { /* if z > 1024 */
			return __s * __LIBM_LOCAL_VALUE(huge) * __LIBM_LOCAL_VALUE(huge); /* overflow */
		} else {
			if (__p_l + __LIBM_LOCAL_VALUE(ovt) > __z - __p_h)
				return __s * __LIBM_LOCAL_VALUE(huge) * __LIBM_LOCAL_VALUE(huge); /* overflow */
		}
	} else if ((__j & 0x7fffffff) >= 0x4090cc00) { /* z <= -1075 */
		if (((__j - 0xc090cc00) | __i) != 0) {     /* z < -1075 */
			return __s * __LIBM_LOCAL_VALUE(tiny) * __LIBM_LOCAL_VALUE(tiny); /* underflow */
		} else {
			if (__p_l <= __z - __p_h)
				return __s * __LIBM_LOCAL_VALUE(tiny) * __LIBM_LOCAL_VALUE(tiny); /* underflow */
		}
	}
	/* compute 2 ** (p_h+p_l) */
	__i = __j & 0x7fffffff;
	__k = (__i >> 20) - 0x3ff;
	__n = 0;
	if (__i > 0x3fe00000) { /* if |z| > 0.5, set n = [z+0.5] */
		__n = __j + (0x00100000 >> (__k + 1));
		__k = ((__n & 0x7fffffff) >> 20) - 0x3ff; /* new k for n */
		__t = __LIBM_LOCAL_VALUE(zero);
		__LIBM_SET_HIGH_WORD(__t, __n & ~(0x000fffff >> __k));
		__n = ((__n & 0x000fffff) | 0x00100000) >> (20 - __k);
		if (__j < 0)
			__n = -__n;
		__p_h -= __t;
	}
	__t = __p_l + __p_h;
	__LIBM_SET_LOW_WORD(__t, 0);
	__u  = __t * __LIBM_LOCAL_VALUE(lg2_h);
	__v  = (__p_l - (__t - __p_h)) * __LIBM_LOCAL_VALUE(lg2) + __t * __LIBM_LOCAL_VALUE(lg2_l);
	__z  = __u + __v;
	__w  = __v - (__z - __u);
	__t  = __z * __z;
	__t1 = __z - __t * (__LIBM_LOCAL_VALUE(P1) +
	                    __t * (__LIBM_LOCAL_VALUE(P2) +
	                           __t * (__LIBM_LOCAL_VALUE(P3) +
	                                  __t * (__LIBM_LOCAL_VALUE(P4) +
	                                         __t * __LIBM_LOCAL_VALUE(P5)))));
	__r  = (__z * __t1) / (__t1 - __LIBM_LOCAL_VALUE(two)) - (__w + __z * __w);
	__z  = __LIBM_LOCAL_VALUE(one) - (__r - __z);
	__LIBM_GET_HIGH_WORD(__j, __z);
	__j += (__n << 20);
	if ((__j >> 20) <= 0) {
		__z = __ieee754_scalbn(__z, (int)__n); /* subnormal output */
	} else {
		__LIBM_SET_HIGH_WORD(__z, __j);
	}
	return __s * __z;
}

#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
__LIBM_LOCAL_FUNC(powl) __ATTR_WUNUSED __ATTR_CONST __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_powl)(__IEEE854_LONG_DOUBLE_TYPE__ __x,
                            __IEEE854_LONG_DOUBLE_TYPE__ __y) {
	/* TODO */
	return (__IEEE854_LONG_DOUBLE_TYPE__)__ieee754_pow((__IEEE754_DOUBLE_TYPE__)__x,
	                                                   (__IEEE754_DOUBLE_TYPE__)__y);
}

#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_POW_H */
