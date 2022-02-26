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
#ifndef _LIBM_REMQUO_H
#define _LIBM_REMQUO_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/fdlibm.h>
#include <libm/fmod.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
/* Compute remainder and a congruent to the quotient.
   Copyright (C) 1997-2013 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1997.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

__LIBM_LOCAL_DECLARE_BEGIN
#ifndef __libm_zerof_defined
#define __libm_zerof_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, zerof, __IEEE754_FLOAT_C(0.0000000000e+00)) /* 0x00000000 */
#endif /* !__libm_zerof_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(remquof) __ATTR_WUNUSED __ATTR_NONNULL((3)) __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_remquof)(__IEEE754_FLOAT_TYPE__ __x,
                               __IEEE754_FLOAT_TYPE__ __y, int *__pexponent) {
	__int32_t __hx, __hy;
	__uint32_t __sx;
	int __cquo;
	__int32_t __qs;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__LIBM_GET_FLOAT_WORD(__hy, __y);
	__sx = __hx & __INT32_C(0x80000000);
	__qs = __sx ^ (__hy & __INT32_C(0x80000000));
	__hy &= __INT32_C(0x7fffffff);
	__hx &= __INT32_C(0x7fffffff);

	/* Purge off exception values.  */
	if (__hy == 0)
		return (__x * __y) / (__x * __y);  /* y = 0 */
	if ((__hx >= __INT32_C(0x7f800000))    /* x not finite */
	    || (__hy > __INT32_C(0x7f800000))) /* y is NaN */
		return (__x * __y) / (__x * __y);
	if (__hy <= __INT32_C(0x7dffffff))
		__x = __ieee754_fmodf(__x, 8 * __y); /* now x < 8y */
	if ((__hx - __hy) == 0) {
		*__pexponent = __qs ? -1 : 1;
		return __LIBM_LOCAL_VALUE(zero) * __x;
	}
	__x    = __ieee754_fabsf(__x);
	__y    = __ieee754_fabsf(__y);
	__cquo = 0;
	if (__x >= 4 * __y) {
		__x -= 4 * __y;
		__cquo += 4;
	}
	if (__x >= 2 * __y) {
		__x -= 2 * __y;
		__cquo += 2;
	}
	if (__hy < __INT32_C(0x01000000)) {
		if (__x + __x > __y) {
			__x -= __y;
			++__cquo;
			if (__x + __x >= __y) {
				__x -= __y;
				++__cquo;
			}
		}
	} else {
		__IEEE754_FLOAT_TYPE__ __y_half;
		__y_half = __IEEE754_FLOAT_C(0.5) * __y;
		if (__x > __y_half) {
			__x -= __y;
			++__cquo;
			if (__x >= __y_half) {
				__x -= __y;
				++__cquo;
			}
		}
	}
	*__pexponent = __qs ? -__cquo : __cquo;
	if (__sx)
		__x = -__x;
	return __x;
}
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
/* Compute remainder and a congruent to the quotient.
   Copyright (C) 1997-2013 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1997.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

__LIBM_LOCAL_DECLARE_BEGIN
#ifndef __libm_zero_defined
#define __libm_zero_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, zero, __IEEE754_DOUBLE_C(0.00000000000000000000e+00)) /* 0x00000000, 0x00000000 */
#endif /* !__libm_zero_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(remquo) __ATTR_WUNUSED __ATTR_NONNULL((3)) __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_remquo)(__IEEE754_DOUBLE_TYPE__ __x,
                              __IEEE754_DOUBLE_TYPE__ __y, int *__pexponent) {
	__int32_t __hx, __hy;
	__uint32_t __sx, __lx, __ly;
	__int32_t __qs;
	int __cquo;
	__LIBM_GET_DOUBLE_WORDS(__hx, __lx, __x);
	__LIBM_GET_DOUBLE_WORDS(__hy, __ly, __y);
	__sx = __hx & __INT32_C(0x80000000);
	__qs = __sx ^ (__hy & __INT32_C(0x80000000));
	__hy &= __INT32_C(0x7fffffff);
	__hx &= __INT32_C(0x7fffffff);
	/* Purge off exception values.  */
	if ((__hy | __ly) == 0)
		return (__x * __y) / (__x * __y);   /* y = 0 */
	if ((__hx >= __INT32_C(0x7ff00000))     /* x not finite */
	    || ((__hy >= __INT32_C(0x7ff00000)) /* p is NaN */
	        && (((__hy - __INT32_C(0x7ff00000)) | __ly) != 0)))
		return (__x * __y) / (__x * __y);
	if (__hy <= __INT32_C(0x7fbfffff))
		__x = __ieee754_fmod(__x, 8 * __y); /* now x < 8y */
	if (((__hx - __hy) | (__lx - __ly)) == 0) {
		*__pexponent = __qs ? -1 : 1;
		return __LIBM_LOCAL_VALUE(zero) * __x;
	}
	__x    = __ieee754_fabs(__x);
	__y    = __ieee754_fabs(__y);
	__cquo = 0;
	if (__x >= 4 * __y) {
		__x -= 4 * __y;
		__cquo += 4;
	}
	if (__x >= 2 * __y) {
		__x -= 2 * __y;
		__cquo += 2;
	}
	if (__hy < __INT32_C(0x00200000)) {
		if (__x + __x > __y) {
			__x -= __y;
			++__cquo;
			if (__x + __x >= __y) {
				__x -= __y;
				++__cquo;
			}
		}
	} else {
		__IEEE754_DOUBLE_TYPE__ __y_half;
		__y_half = __IEEE754_DOUBLE_C(0.5) * __y;
		if (__x > __y_half) {
			__x -= __y;
			++__cquo;
			if (__x >= __y_half) {
				__x -= __y;
				++__cquo;
			}
		}
	}
	*__pexponent = __qs ? -__cquo : __cquo;
	if (__sx)
		__x = -__x;
	return __x;
}
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
/* Compute remainder and a congruent to the quotient.
   Copyright (C) 1997-2013 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1997.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

__LIBM_LOCAL_DECLARE_BEGIN
#ifndef __libm_zerol_defined
#define __libm_zerol_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, zerol, __IEEE854_LONG_DOUBLE_C(0.0))
#endif /* !__libm_zerol_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(remquol) __ATTR_WUNUSED __ATTR_NONNULL((3)) __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_remquol)(__IEEE854_LONG_DOUBLE_TYPE__ __x,
                               __IEEE854_LONG_DOUBLE_TYPE__ __y, int *__pexponent) {
	__int32_t __ex, __ep, __hx, __hp;
	__uint32_t __sx, __lx, __lp;
	int __cquo;
	__int32_t __qs;
	__LIBM_GET_LDOUBLE_WORDS(__ex, __hx, __lx, __x);
	__LIBM_GET_LDOUBLE_WORDS(__ep, __hp, __lp, __y);
	__sx = __ex & 0x8000;
	__qs = (__sx ^ (__ep & 0x8000)) >> 15;
	__ep &= IEEE854_LONG_DOUBLE_MAXEXP;
	__ex &= IEEE854_LONG_DOUBLE_MAXEXP;

	/* Purge off exception values.  */
	if ((__ep | __hp | __lp) == 0)
		return (__x * __y) / (__x * __y);        /* p = 0 */
	if ((__ex == IEEE854_LONG_DOUBLE_MAXEXP)     /* x not finite */
	    || ((__ep == IEEE854_LONG_DOUBLE_MAXEXP) /* p is NaN */
	        && ((__hp | __lp) != 0)))
		return (__x * __y) / (__x * __y);
	if (__ep <= 0x7ffb)
		__x = __ieee854_fmodl(__x, 8 * __y); /* now x < 8p */
	if (((__ex - __ep) | (__hx - __hp) | (__lx - __lp)) == 0) {
		*__pexponent = __qs ? -1 : 1;
		return __LIBM_LOCAL_VALUE(zerol) * __x;
	}
	__x    = __ieee854_fabsl(__x);
	__y    = __ieee854_fabsl(__y);
	__cquo = 0;
	if (__x >= 4 * __y) {
		__x -= 4 * __y;
		__cquo += 4;
	}
	if (__x >= 2 * __y) {
		__x -= 2 * __y;
		__cquo += 2;
	}
	if (__ep < 0x0002) {
		if (__x + __x > __y) {
			__x -= __y;
			++__cquo;
			if (__x + __x >= __y) {
				__x -= __y;
				++__cquo;
			}
		}
	} else {
		__IEEE854_LONG_DOUBLE_TYPE__ __p_half;
		__p_half = __IEEE854_LONG_DOUBLE_C(0.5) * __y;
		if (__x > __p_half) {
			__x -= __y;
			++__cquo;
			if (__x >= __p_half) {
				__x -= __y;
				++__cquo;
			}
		}
	}
	*__pexponent = __qs ? -__cquo : __cquo;
	if (__sx)
		__x = -__x;
	return __x;
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_REMQUO_H */
