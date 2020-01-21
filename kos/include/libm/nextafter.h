/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBM_NEXTAFTER_H
#define _LIBM_NEXTAFTER_H 1

#include <__crt.h>

#include <hybrid/typecore.h>

#include <bits/nan.h>
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

__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
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
		if (__y == __x)
			return __y;
		else {
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

__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
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
		if (__y == __x)
			return __y;
		else {
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

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBM_NEXTAFTER_H */
