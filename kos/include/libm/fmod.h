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
#ifndef _LIBM_FMOD_H
#define _LIBM_FMOD_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/fdlibm.h>

#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#include <libm/fabs.h>
#include <libm/isinf.h>
#include <libm/modf.h>
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

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

/*
 * __ieee754_fmod(x,y)
 * Return x mod y in exact arithmetic
 * Method: shift and subtract
 */

__LIBM_LOCAL_DECLARE_BEGIN
#ifndef __libm_onef_defined
#define __libm_onef_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, onef, __IEEE754_FLOAT_C(1.0))
#endif /* !__libm_onef_defined */
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_FLOAT_TYPE__, zero2f, 2) {
	__IEEE754_FLOAT_C(0.0),
	__IEEE754_FLOAT_C(-0.0)
};
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(fmodf) __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_fmodf)(__IEEE754_FLOAT_TYPE__ __x,
                             __IEEE754_FLOAT_TYPE__ __y) {
	__int32_t __n, __hx, __hy, __hz, __ix, __iy, __sx, __i;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__LIBM_GET_FLOAT_WORD(__hy, __y);
	__sx = __hx & 0x80000000; /* sign of x */
	__hx ^= __sx;             /* |x| */
	__hy &= 0x7fffffff;       /* |y| */

	/* purge off exception values */
	if (__LIBM_FLT_UWORD_IS_ZERO(__hy) ||
	    !__LIBM_FLT_UWORD_IS_FINITE(__hx) ||
	    __LIBM_FLT_UWORD_IS_NAN(__hy))
		return (__x * __y) / (__x * __y);
	if (__hx < __hy)
		return __x; /* |x| < |y| return x */
	if (__hx == __hy)
		return __LIBM_LOCAL_VALUE(zero2f)[(__uint32_t)__sx >> 31]; /* |x|=|y| return x*0*/

	/* Note: y cannot be zero if we reach here. */

	/* determine ix = ilogb(x) */
#ifndef _FLT_NO_DENORMALS
	if (__LIBM_FLT_UWORD_IS_SUBNORMAL(__hx)) { /* subnormal x */
		for (__ix = -126, __i = (__hx << 8); __i > 0; __i <<= 1)
			__ix -= 1;
	} else
#endif /* !_FLT_NO_DENORMALS */
	{
		__ix = (__hx >> 23) - 127;
	}

	/* determine iy = ilogb(y) */
#ifndef _FLT_NO_DENORMALS
	if (__LIBM_FLT_UWORD_IS_SUBNORMAL(__hy)) { /* subnormal y */
		for (__iy = -126, __i = (__hy << 8); __i >= 0; __i <<= 1)
			__iy -= 1;
	} else
#endif /* !_FLT_NO_DENORMALS */
	{
		__iy = (__hy >> 23) - 127;
	}

	/* set up {hx,lx}, {hy,ly} and align y to x */
	if (__ix >= -126) {
		__hx = 0x00800000 | (0x007fffff & __hx);
	} else { /* subnormal x, shift x to normal */
		__n  = -126 - __ix;
		__hx = __hx << __n;
	}
	if (__iy >= -126) {
		__hy = 0x00800000 | (0x007fffff & __hy);
	} else { /* subnormal y, shift y to normal */
		__n  = -126 - __iy;
		__hy = __hy << __n;
	}

	/* fix point fmod */
	__n = __ix - __iy;
	while (__n--) {
		__hz = __hx - __hy;
		if (__hz < 0) {
			__hx = __hx + __hx;
		} else {
			if (__hz == 0) /* return sign(x)*0 */
				return __LIBM_LOCAL_VALUE(zero2f)[(__uint32_t)__sx >> 31];
			__hx = __hz + __hz;
		}
	}
	__hz = __hx - __hy;
	if (__hz >= 0) {
		__hx = __hz;
	}

	/* convert back to floating value and restore the sign */
	if (__hx == 0) /* return sign(x)*0 */
		return __LIBM_LOCAL_VALUE(zero2f)[(__uint32_t)__sx >> 31];
	while (__hx < 0x00800000) { /* normalize x */
		__hx = __hx + __hx;
		__iy -= 1;
	}
	if (__iy >= -126) { /* normalize output */
		__hx = ((__hx - 0x00800000) | ((__iy + 127) << 23));
		__LIBM_SET_FLOAT_WORD(__x, __hx | __sx);
	} else { /* subnormal output */
		/* If denormals are not supported, this code will generate a zero representation.  */
		__n = -126 - __iy;
		__hx >>= __n;
		__LIBM_SET_FLOAT_WORD(__x, __hx | __sx);
		__x *= __LIBM_LOCAL_VALUE(onef); /* create necessary signal */
	}
	return __x; /* exact output */
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

/*
 * __ieee754_fmod(x,y)
 * Return x mod y in exact arithmetic
 * Method: shift and subtract
 */

__LIBM_LOCAL_DECLARE_BEGIN
#ifndef __libm_one_defined
#define __libm_one_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, one, __IEEE754_DOUBLE_C(1.0))
#endif /* !__libm_one_defined */
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_DOUBLE_TYPE__, zero2, 2) {
	__IEEE754_DOUBLE_C(0.0),
	__IEEE754_DOUBLE_C(-0.0)
};
__LIBM_LOCAL_DECLARE_END


__LIBM_LOCAL_FUNC(fmod) __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_fmod)(__IEEE754_DOUBLE_TYPE__ __x,
                            __IEEE754_DOUBLE_TYPE__ __y) {
	__int32_t __n, __hx, __hy, __hz, __ix, __iy, __sx, __i;
	__uint32_t __lx, __ly, __lz;
	__LIBM_EXTRACT_WORDS(__hx, __lx, __x);
	__LIBM_EXTRACT_WORDS(__hy, __ly, __y);
	__sx = __hx & 0x80000000; /* sign of x */
	__hx ^= __sx;             /* |x| */
	__hy &= 0x7fffffff;       /* |y| */

	/* purge off exception values */
	if ((__hy | __ly) == 0 || (__hx >= 0x7ff00000) || /* y=0,or x not finite */
	    ((__hy | ((__ly | -__ly) >> 31)) > 0x7ff00000)) /* or y is NaN */
		return (__x * __y) / (__x * __y);
	if (__hx <= __hy) {
		if ((__hx < __hy) || (__lx < __ly))
			return __x; /* |x| < |y| return x */
		if (__lx == __ly)
			return __LIBM_LOCAL_VALUE(zero2)[(__uint32_t)__sx >> 31]; /* |x|=|y| return x*0*/
	}

	/* determine ix = ilogb(x) */
	if (__hx < 0x00100000) { /* subnormal x */
		if (__hx == 0) {
			for (__ix = -1043, __i = __lx; __i > 0; __i <<= 1)
				__ix -= 1;
		} else {
			for (__ix = -1022, __i = (__hx << 11); __i > 0; __i <<= 1)
				__ix -= 1;
		}
	} else {
		__ix = (__hx >> 20) - 1023;
	}

	/* determine iy = ilogb(y) */
	if (__hy < 0x00100000) { /* subnormal y */
		if (__hy == 0) {
			for (__iy = -1043, __i = __ly; __i > 0; __i <<= 1)
				__iy -= 1;
		} else {
			for (__iy = -1022, __i = (__hy << 11); __i > 0; __i <<= 1)
				__iy -= 1;
		}
	} else {
		__iy = (__hy >> 20) - 1023;
	}

	/* set up {hx,lx}, {hy,ly} and align y to x */
	if (__ix >= -1022) {
		__hx = 0x00100000 | (0x000fffff & __hx);
	} else { /* subnormal x, shift x to normal */
		__n = -1022 - __ix;
		if (__n <= 31) {
			__hx = (__hx << __n) | (__lx >> (32 - __n));
			__lx <<= __n;
		} else {
			__hx = __lx << (__n - 32);
			__lx   = 0;
		}
	}
	if (__iy >= -1022) {
		__hy = 0x00100000 | (0x000fffff & __hy);
	} else { /* subnormal y, shift y to normal */
		__n = -1022 - __iy;
		if (__n <= 31) {
			__hy = (__hy << __n) | (__ly >> (32 - __n));
			__ly <<= __n;
		} else {
			__hy = __ly << (__n - 32);
			__ly   = 0;
		}
	}

	/* fix point fmod */
	__n = __ix - __iy;
	while (__n--) {
		__hz = __hx - __hy;
		__lz   = __lx - __ly;
		if (__lx < __ly)
			__hz -= 1;
		if (__hz < 0) {
			__hx = __hx + __hx + (__lx >> 31);
			__lx   = __lx + __lx;
		} else {
			if ((__hz | __lz) == 0) /* return sign(x)*0 */
				return __LIBM_LOCAL_VALUE(zero2)[(__uint32_t)__sx >> 31];
			__hx = __hz + __hz + (__lz >> 31);
			__lx   = __lz + __lz;
		}
	}
	__hz = __hx - __hy;
	__lz   = __lx - __ly;
	if (__lx < __ly)
		__hz -= 1;
	if (__hz >= 0) {
		__hx = __hz;
		__lx   = __lz;
	}

	/* convert back to floating value and restore the sign */
	if ((__hx | __lx) == 0) /* return sign(x)*0 */
		return __LIBM_LOCAL_VALUE(zero2)[(__uint32_t)__sx >> 31];
	while (__hx < 0x00100000) { /* normalize x */
		__hx = __hx + __hx + (__lx >> 31);
		__lx   = __lx + __lx;
		__iy -= 1;
	}
	if (__iy >= -1022) { /* normalize output */
		__hx = ((__hx - 0x00100000) | ((__iy + 1023) << 20));
		__LIBM_INSERT_WORDS(__x, __hx | __sx, __lx);
	} else { /* subnormal output */
		__n = -1022 - __iy;
		if (__n <= 20) {
			__lx = (__lx >> __n) | ((__uint32_t)__hx << (32 - __n));
			__hx >>= __n;
		} else if (__n <= 31) {
			__lx   = (__hx << (32 - __n)) | (__lx >> __n);
			__hx = __sx;
		} else {
			__lx   = __hx >> (__n - 32);
			__hx = __sx;
		}
		__LIBM_INSERT_WORDS(__x, __hx | __sx, __lx);
		__x *= __LIBM_LOCAL_VALUE(one); /* create necessary signal */
	}
	return __x; /* exact output */
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

__LIBM_LOCAL_FUNC(fmodl) __ATTR_WUNUSED __ATTR_CONST __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_fmodl)(__IEEE854_LONG_DOUBLE_TYPE__ __x,
                             __IEEE854_LONG_DOUBLE_TYPE__ __y) {
	__IEEE854_LONG_DOUBLE_TYPE__ __intpart;
	if (__ieee854_isinfl(__y)) {
		if (__ieee854_isinfl(__x))
			return __x < 0 ? -0.0L : 0.0L;
		return __x;
	}
	if (__ieee854_fabsl(__x) <= __ieee854_fabsl(__y))
		return __x;
	__COMPILER_UNUSED(__ieee854_modfl(__x / __y, &__intpart));
	return __x - __y * __intpart;
}

#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_FMOD_H */
