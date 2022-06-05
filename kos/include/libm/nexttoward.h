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
#ifndef _LIBM_NEXTTOWARD_H
#define _LIBM_NEXTTOWARD_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <bits/math-constants.h>
#include <bits/types.h>

#include <libm/fdlibm.h>

#ifdef __IEEE754_DOUBLE_TYPE__
#if ((!defined(__NANF) && defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)) || \
     (!defined(__NAN) && defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__)) || \
     (!defined(__NANL) && defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)))
#include <libm/nan.h>
#endif /* ... */
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE854_LONG_DOUBLE_TYPE__
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

__LIBM_LOCAL_FUNC(nexttowardf) __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_nexttowardf)(__IEEE754_FLOAT_TYPE__ __x,
                                   __IEEE854_LONG_DOUBLE_TYPE__ __y) {
	__int32_t __hx, __ix, __iy;
	__uint32_t __hy, __ly, __esy;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__LIBM_GET_LDOUBLE_WORDS(__esy, __hy, __ly, __y);
	__ix = __hx & __INT32_C(0x7fffffff);              /* |x| */
	__iy = __esy & IEEE854_LONG_DOUBLE_MAXEXP; /* |y| */
	/* Intel's extended format has the normally implicit 1 explicit present. Sigh! */
	if ((__ix > __INT32_C(0x7f800000)) ||                                                        /* x is nan */
	    (__iy >= IEEE854_LONG_DOUBLE_MAXEXP && (((__hy & __UINT32_C(0x7fffffff)) | __ly) != 0))) /* y is nan */
		return __x + __y;
	if ((__IEEE854_LONG_DOUBLE_TYPE__)__x == __y)
		return __y;  /* x=y, return y */
	if (__ix == 0) { /* x == 0 */
		__IEEE754_FLOAT_TYPE__ __u;
		__LIBM_SET_FLOAT_WORD(__x, ((__esy & 0x8000) << 16) | 1); /* return +-minsub */
		__libm_math_opt_barrier(__x, __u);
		__u = __u * __u;
		__libm_math_force_eval(__u); /* raise underflow flag */
		return __x;
	}
	if (__hx >= 0) { /* x > 0 */
		if (__x > __y) { /* x -= ulp */
			__hx -= 1;
		} else { /* x < y, x += ulp */
			__hx += 1;
		}
	} else { /* x < 0 */
		if (__x < __y) { /* x -= ulp */
			__hx -= 1;
		} else { /* x > y, x += ulp */
			__hx += 1;
		}
	}
	__hy = __hx & __UINT32_C(0x7f800000);
	if (__hy >= __UINT32_C(0x7f800000)) {
		__x = __x + __x; /* overflow  */
		__libm_math_force_eval(__x); /* Force conversion to float. */
		return __x;
	}
	if (__hy < __UINT32_C(0x00800000))
		__libm_math_force_eval_r(__IEEE754_FLOAT_TYPE__, __x * __x); /* raise underflow flag */
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

__LIBM_LOCAL_FUNC(nexttoward) __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_nexttoward)(__IEEE754_DOUBLE_TYPE__ __x,
                                  __IEEE854_LONG_DOUBLE_TYPE__ __y) {
	__int32_t __hx, __ix, __iy;
	__uint32_t __lx, __hy, __ly, __esy;
	__LIBM_GET_DOUBLE_WORDS(__hx, __lx, __x);
	__LIBM_GET_LDOUBLE_WORDS(__esy, __hy, __ly, __y);
	__ix = __hx & __INT32_C(0x7fffffff);       /* |x| */
	__iy = __esy & IEEE854_LONG_DOUBLE_MAXEXP; /* |y| */
	/* Intel's extended format has the normally implicit 1 explicit present. Sigh! */
	if (((__ix >= __INT32_C(0x7ff00000)) && ((__ix - __INT32_C(0x7ff00000)) | __lx) != 0) ||       /* x is nan */
	    ((__iy >= IEEE854_LONG_DOUBLE_MAXEXP) && ((__hy & __UINT32_C(0x7fffffff)) | __ly) != 0)) { /* y is nan */
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
	if ((__IEEE854_LONG_DOUBLE_TYPE__)__x == __y)
		return __y; /* x=y, return y */
	if ((__ix | __lx) == 0) { /* x == 0 */
		__IEEE754_DOUBLE_TYPE__ __u;
		__LIBM_INSERT_WORDS(__x, (__esy & 0x8000) << 16, 1); /* return +-minsub */
		__libm_math_opt_barrier(__x, __u);
		__libm_math_force_eval_r(__IEEE754_DOUBLE_TYPE__, __u * __u); /* raise underflow flag */
		return __x;
	}
	if (__hx >= 0) { /* x > 0 */
		if (__x > __y) { /* x -= ulp */
			if (__lx == 0)
				__hx -= 1;
			__lx -= 1;
		} else { /* x < y, x += ulp */
			__lx += 1;
			if (__lx == 0)
				__hx += 1;
		}
	} else { /* x < 0 */
		if (__x < __y) { /* x -= ulp */
			if (__lx == 0)
				__hx -= 1;
			__lx -= 1;
		} else { /* x > y, x += ulp */
			__lx += 1;
			if (__lx == 0)
				__hx += 1;
		}
	}
	__hy = __hx & __UINT32_C(0x7ff00000);
	if (__hy >= __UINT32_C(0x7ff00000)) {
		__x = __x + __x; /* overflow  */
		/* Force conversion to double. */
		__libm_math_force_eval(__x);
		return __x;
	}
	if (__hy < __UINT32_C(0x00100000))
		__libm_math_force_eval_r(__IEEE754_DOUBLE_TYPE__, __x * __x); /* raise underflow flag */
	__LIBM_INSERT_WORDS(__x, __hx, __lx);
	return __x;
}

#endif /* __IEEE754_DOUBLE_TYPE__ */

#elif defined(__clang_tidy__)
/* Prevent compiler errors when clang-tidy doesn't have `long double' */
#define __ieee754_nexttowardf(x, y) (x)
#define __ieee754_nexttoward(x, y)  (x)
#endif /* ... */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_NEXTTOWARD_H */
