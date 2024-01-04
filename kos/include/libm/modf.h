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
#ifndef _LIBM_MODF_H
#define _LIBM_MODF_H 1

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

__LIBM_LOCAL_DECLARE_BEGIN
#ifndef __libm_onef_defined
#define __libm_onef_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, onef, __IEEE754_FLOAT_C(1.0))
#endif /* !__libm_onef_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(modff) __ATTR_WUNUSED __ATTR_NONNULL((2)) __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_modff)(__IEEE754_FLOAT_TYPE__ __x,
                             __IEEE754_FLOAT_TYPE__ *__iptr) {
	__int32_t __i0, __j0;
	__uint32_t __i;
	__LIBM_GET_FLOAT_WORD(__i0, __x);
	__j0 = ((__i0 >> IEEE754_FLOAT_SHIFT) & IEEE754_FLOAT_MAXEXP) - IEEE754_FLOAT_BIAS; /* exponent of x */
	if (__j0 < IEEE754_FLOAT_SHIFT) {                                                   /* integer part in x */
		if (__j0 < 0) {                                                                 /* |x| < 1 */
			__LIBM_SET_FLOAT_WORD(*__iptr, __i0 & __UINT32_C(0x80000000));              /* *iptr = +-0 */
			return __x;
		} else {
			__i = __UINT32_C(0x007fffff) >> __j0;
			if ((__i0 & __i) == 0) { /* x is integral */
				__uint32_t __ix;
				*__iptr = __x;
				__LIBM_GET_FLOAT_WORD(__ix, __x);
				__LIBM_SET_FLOAT_WORD(__x, __ix & __UINT32_C(0x80000000)); /* return +-0 */
				return __x;
			} else {
				__LIBM_SET_FLOAT_WORD(*__iptr, __i0 & (~__i));
				return __x - *__iptr;
			}
		}
	} else { /* no fraction part */
		*__iptr = __x * __LIBM_LOCAL_VALUE(onef);
		/* We must handle NaNs separately.  */
		if (__j0 == (IEEE754_FLOAT_MAXEXP - IEEE754_FLOAT_BIAS) && (__i0 & __UINT32_C(0x7fffff)) != 0)
			return __x * __LIBM_LOCAL_VALUE(onef);
		__LIBM_SET_FLOAT_WORD(__x, __i0 & __UINT32_C(0x80000000)); /* return +-0 */
		return __x;
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
#ifndef __libm_one_defined
#define __libm_one_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, one, __IEEE754_DOUBLE_C(1.0))
#endif /* !__libm_one_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(modf) __ATTR_WUNUSED __ATTR_NONNULL((2)) __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_modf)(__IEEE754_DOUBLE_TYPE__ __x,
                            __IEEE754_DOUBLE_TYPE__ *__iptr) {
	__int32_t __i0, __i1, __j0;
	__uint32_t __i;
	__LIBM_GET_DOUBLE_WORDS(__i0, __i1, __x);
	__j0 = ((__i0 >> IEEE754_DOUBLE_SHIFT) & IEEE754_DOUBLE_MAXEXP) - IEEE754_DOUBLE_BIAS; /* exponent of x */
	if (__j0 < IEEE754_DOUBLE_SHIFT) {                                                     /* integer part in high x */
		if (__j0 < 0) {                                                                    /* |x| < 1 */
			__LIBM_INSERT_WORDS(*__iptr, __i0 & __UINT32_C(0x80000000), 0);                /* *iptr = +-0 */
			return __x;
		} else {
			__i = __UINT32_C(0x000fffff) >> __j0;
			if (((__i0 & __i) | __i1) == 0) { /* x is integral */
				*__iptr = __x;
				__LIBM_INSERT_WORDS(__x, __i0 & __UINT32_C(0x80000000), 0); /* return +-0 */
				return __x;
			} else {
				__LIBM_INSERT_WORDS(*__iptr, __i0 & (~__i), 0);
				return __x - *__iptr;
			}
		}
	} else if (__j0 > 51) { /* no fraction part */
		*__iptr = __x * __LIBM_LOCAL_VALUE(one);
		/* We must handle NaNs separately.  */
		if (__j0 == (IEEE754_DOUBLE_MAXEXP - IEEE754_DOUBLE_BIAS) && ((__i0 & __UINT32_C(0xfffff)) | __i1) != 0)
			return __x * __LIBM_LOCAL_VALUE(one);
		__LIBM_INSERT_WORDS(__x, __i0 & __UINT32_C(0x80000000), 0); /* return +-0 */
		return __x;
	} else { /* fraction part in low x */
		__i = __UINT32_C(0xffffffff) >> (__j0 - IEEE754_DOUBLE_SHIFT);
		if ((__i1 & __i) == 0) { /* x is integral */
			*__iptr = __x;
			__LIBM_INSERT_WORDS(__x, __i0 & __UINT32_C(0x80000000), 0); /* return +-0 */
			return __x;
		} else {
			__LIBM_INSERT_WORDS(*__iptr, __i0, __i1 & (~__i));
			return __x - *__iptr;
		}
	}
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
#ifndef __libm_onel_defined
#define __libm_onel_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, onel, __IEEE854_LONG_DOUBLE_C(1.0))
#endif /* !__libm_onel_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(modfl) __ATTR_WUNUSED __ATTR_NONNULL((2)) __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_modfl)(__IEEE854_LONG_DOUBLE_TYPE__ __x,
                             __IEEE854_LONG_DOUBLE_TYPE__ *__iptr) {
	__int32_t __i0, __i1, __j0;
	__uint32_t __i, __se;
	__LIBM_GET_LDOUBLE_WORDS(__se, __i0, __i1, __x);
	__j0 = (__se & IEEE854_LONG_DOUBLE_MAXEXP) - IEEE854_LONG_DOUBLE_BIAS; /* exponent of x */
	if (__j0 < 32) {                                                     /* integer part in high x */
		if (__j0 < 0) {                                                  /* |x| < 1 */
			__LIBM_SET_LDOUBLE_WORDS(*__iptr, __se & 0x8000, 0, 0);      /* *iptr = +-0 */
			return __x;
		} else {
			__i = __UINT32_C(0x7fffffff) >> __j0;
			if (((__i0 & __i) | __i1) == 0) { /* x is integral */
				*__iptr = __x;
				__LIBM_SET_LDOUBLE_WORDS(__x, __se & 0x8000, 0, 0); /* return +-0 */
				return __x;
			} else {
				__LIBM_SET_LDOUBLE_WORDS(*__iptr, __se, __i0 & (~__i), 0);
				return __x - *__iptr;
			}
		}
	} else if (__j0 > 63) { /* no fraction part */
		*__iptr = __x * __LIBM_LOCAL_VALUE(one);
		/* We must handle NaNs separately.  */
		if (__j0 == (IEEE854_LONG_DOUBLE_MAXEXP - IEEE854_LONG_DOUBLE_BIAS) && ((__i0 & __UINT32_C(0x7fffffff)) | __i1) != 0)
			return __x * __LIBM_LOCAL_VALUE(onel);
		__LIBM_SET_LDOUBLE_WORDS(__x, __se & 0x8000, 0, 0); /* return +-0 */
		return __x;
	} else { /* fraction part in low x */
		__i = __UINT32_C(0x7fffffff) >> (__j0 - 32);
		if ((__i1 & __i) == 0) { /* x is integral */
			*__iptr = __x;
			__LIBM_SET_LDOUBLE_WORDS(__x, __se & 0x8000, 0, 0); /* return +-0 */
			return __x;
		} else {
			__LIBM_SET_LDOUBLE_WORDS(*__iptr, __se, __i0, __i1 & (~__i));
			return __x - *__iptr;
		}
	}
}

#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_MODF_H */
