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
#ifndef _LIBM_NEXTAFTER_H
#define _LIBM_NEXTAFTER_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <bits/types.h>

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

__LIBM_LOCAL_FUNC(nextafterf) __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_nextafterf)(__IEEE754_FLOAT_TYPE__ __x,
                                  __IEEE754_FLOAT_TYPE__ __y) {
	__int32_t __hx, __hy, __ix, __iy;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__LIBM_GET_FLOAT_WORD(__hy, __y);
	__ix = __hx & 0x7fffffff; /* |x| */
	__iy = __hy & 0x7fffffff; /* |y| */
	if (__LIBM_FLT_UWORD_IS_NAN(__ix) ||
	    __LIBM_FLT_UWORD_IS_NAN(__iy))
		return __x + __y;
	if (__x == __y)
		return __x;                /* x=y, return x */
	if (__LIBM_FLT_UWORD_IS_ZERO(__ix)) { /* x == 0 */
		__LIBM_SET_FLOAT_WORD(__x, (__hy & 0x80000000) | __LIBM_FLT_UWORD_MIN);
		__y = __x * __x;
		if (__y == __x) {
			return __y;
		} else {
			return __x; /* raise underflow flag */
		}
	}
	if (__hx >= 0) {     /* x > 0 */
		if (__hx > __hy) { /* x > y, x -= ulp */
			__hx -= 1;
		} else { /* x < y, x += ulp */
			__hx += 1;
		}
	} else {
		/* x < 0 */
		if (__hy >= 0 || __hx > __hy) { /* x < y, x -= ulp */
			__hx -= 1;
		} else { /* x > y, x += ulp */
			__hx += 1;
		}
	}
	__hy = __hx & 0x7f800000;
	if (__hy > __LIBM_FLT_UWORD_MAX)
		return __x + __x;      /* overflow  */
	if (__hy < 0x00800000) { /* underflow */
		__y = __x * __x;
		if (__y != __x) { /* raise underflow flag */
			__LIBM_SET_FLOAT_WORD(__y, __hx);
			return __y;
		}
	}
	__LIBM_SET_FLOAT_WORD(__x, __hx);
	return __x;
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

__LIBM_LOCAL_FUNC(nextafter) __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_nextafter)(__IEEE754_DOUBLE_TYPE__ __x,
                                 __IEEE754_DOUBLE_TYPE__ __y) {
	__int32_t __hx, __hy, __ix, __iy;
	__uint32_t __lx, __ly;
	__LIBM_EXTRACT_WORDS(__hx, __lx, __x);
	__LIBM_EXTRACT_WORDS(__hy, __ly, __y);
	__ix = __hx & 0x7fffffff; /* |x| */
	__iy = __hy & 0x7fffffff; /* |y| */
	if (((__ix >= 0x7ff00000) && ((__ix - 0x7ff00000) | __lx) != 0) || /* x is nan */
	    ((__iy >= 0x7ff00000) && ((__iy - 0x7ff00000) | __ly) != 0))   /* y is nan */
		return __x + __y;
	if (__x == __y)
		return __x; /* x=y, return x */
	if ((__ix | __lx) == 0) { /* x == 0 */
		__LIBM_INSERT_WORDS(__x, __hy & 0x80000000, 1); /* return +-minsubnormal */
		__y = __x * __x;
		if (__y == __x) {
			return __y;
		} else {
			return __x; /* raise underflow flag */
		}
	}
	if (__hx >= 0) {
		/* x > 0 */
		if (__hx > __hy || ((__hx == __hy) && (__lx > __ly))) { /* x > y, x -= ulp */
			if (__lx == 0)
				__hx -= 1;
			__lx -= 1;
		} else { /* x < y, x += ulp */
			__lx += 1;
			if (__lx == 0)
				__hx += 1;
		}
	} else {
		/* x < 0 */
		if (__hy >= 0 || __hx > __hy || ((__hx == __hy) && (__lx > __ly))) { /* x < y, x -= ulp */
			if (__lx == 0)
				__hx -= 1;
			__lx -= 1;
		} else { /* x > y, x += ulp */
			__lx += 1;
			if (__lx == 0)
				__hx += 1;
		}
	}
	__hy = __hx & 0x7ff00000;
	if (__hy >= 0x7ff00000)
		return __x + __x;      /* overflow  */
	if (__hy < 0x00100000) { /* underflow */
		__y = __x * __x;
		if (__y != __x) { /* raise underflow flag */
			__LIBM_INSERT_WORDS(__y, __hx, __lx);
			return __y;
		}
	}
	__LIBM_INSERT_WORDS(__x, __hx, __lx);
	return __x;
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

__LIBM_LOCAL_FUNC(nextafterl) __ATTR_WUNUSED __ATTR_CONST __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_nextafterl)(__IEEE854_LONG_DOUBLE_TYPE__ __x,
                                  __IEEE854_LONG_DOUBLE_TYPE__ __y) {
	__int32_t __ix, __iy;
	__int32_t __esx, __esy;
	__uint32_t __hx, __hy, __lx, __ly;

	__LIBM_GET_LDOUBLE_WORDS(__esx, __hx, __lx, __x);
	__LIBM_GET_LDOUBLE_WORDS(__esy, __hy, __ly, __y);
	__ix = __esx & IEEE854_LONG_DOUBLE_MAXEXP; /* |x| */
	__iy = __esy & IEEE854_LONG_DOUBLE_MAXEXP; /* |y| */

	/* Intel's extended format has the normally implicit 1 explicit present. Sigh! */
	if (((__ix == IEEE854_LONG_DOUBLE_MAXEXP) && (((__hx & __INT32_C(0x7fffffff)) | __lx) != 0)) || /* x is nan */
	    ((__iy == IEEE854_LONG_DOUBLE_MAXEXP) && (((__hy & __INT32_C(0x7fffffff)) | __ly) != 0)))   /* y is nan */
		return __x + __y;
	if (__x == __y)
		return __y; /* x=y, return y */
	if ((__ix | __hx | __lx) == 0) { /* x == 0 */
		__IEEE854_LONG_DOUBLE_TYPE__ __u;
		__LIBM_SET_LDOUBLE_WORDS(__x, __esy & 0x8000, 0, 1); /* return +-minsubnormal */
		__libm_math_opt_barrier(__x, __u); /* XXX: What's the point of this? */
		__u = __u * __u;
		__libm_math_force_eval_r(__IEEE854_LONG_DOUBLE_TYPE__, __u * __u); /* raise underflow flag */
		return __x;
	}
	if (__esx >= 0) { /* x > 0 */
		if (__esx > __esy || ((__esx == __esy) && (__hx > __hy || ((__hx == __hy) && (__lx > __ly))))) {
			/* x > y, x -= ulp */
			if (__lx == 0) {
				if (__hx <= __UINT32_C(0x80000000)) {
					if (__esx == 0) {
						--__hx;
					} else {
						__esx -= 1;
						__hx = __hx - 1;
						if (__esx > 0)
							__hx |= __UINT32_C(0x80000000);
					}
				} else {
					__hx -= 1;
				}
			}
			__lx -= 1;
		} else { /* x < y, x += ulp */
			__lx += 1;
			if (__lx == 0) {
				__hx += 1;
				if (__hx == 0 || (__esx == 0 && __hx == __UINT32_C(0x80000000))) {
					__esx += 1;
					__hx |= __UINT32_C(0x80000000);
				}
			}
		}
	} else { /* x < 0 */
		if (__esy >= 0 || (__esx > __esy || ((__esx == __esy) && (__hx > __hy || ((__hx == __hy) && (__lx > __ly)))))) {
			/* x < y, x -= ulp */
			if (__lx == 0) {
				if (__hx <= __UINT32_C(0x80000000)) {
					__esx -= 1;
					__hx = __hx - 1;
					if ((__esx & IEEE854_LONG_DOUBLE_MAXEXP) > 0)
						__hx |= __UINT32_C(0x80000000);
				} else {
					__hx -= 1;
				}
			}
			__lx -= 1;
		} else { /* x > y, x += ulp */
			__lx += 1;
			if (__lx == 0) {
				__hx += 1;
				if (__hx == 0 || (__esx == __INT32_C(0xffff8000) && __hx == __UINT32_C(0x80000000))) {
					__esx += 1;
					__hx |= __UINT32_C(0x80000000);
				}
			}
		}
	}
	__esy = __esx & IEEE854_LONG_DOUBLE_MAXEXP;
	if (__esy == IEEE854_LONG_DOUBLE_MAXEXP)
		return __x + __x; /* overflow  */
	if (__esy == 0)
		__libm_math_force_eval_r(__IEEE854_LONG_DOUBLE_TYPE__, __x * __x); /* raise underflow flag */
	__LIBM_SET_LDOUBLE_WORDS(__x, __esx, __hx, __lx);
	return __x;
}

#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_NEXTAFTER_H */
