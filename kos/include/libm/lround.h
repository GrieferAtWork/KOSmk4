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
#ifndef _LIBM_LROUND_H
#define _LIBM_LROUND_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/asm/lround.h>
#include <libm/fdlibm.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
#ifndef __ieee754_lroundf
/* Round double value to long int.
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

__LIBM_LOCAL_FUNC(lroundf) __ATTR_WUNUSED __ATTR_CONST long int
(__LIBCCALL __ieee754_lroundf)(__IEEE754_FLOAT_TYPE__ __x) {
	__int32_t __j0;
	__uint32_t __i;
	long int __result;
	__int32_t __sign;
	__LIBM_GET_FLOAT_WORD(__i, __x);
	__j0   = ((__i >> __LIBM_IEEE754_FLOAT_SHIFT) & __LIBM_IEEE754_FLOAT_MAXEXP) - __LIBM_IEEE754_FLOAT_BIAS;
	__sign = (__i & __INT32_C(0x80000000)) != 0 ? -1 : 1;
	__i &= __UINT32_C(0x7fffff);
	__i |= __UINT32_C(0x800000);
	if (__j0 < (__int32_t)(8 * sizeof(long int)) - 1) {
		if (__j0 < 0) {
			return __j0 < -1 ? 0 : __sign;
		} else if (__j0 >= __LIBM_IEEE754_FLOAT_SHIFT) {
			__result = (long int)__i << (__j0 - __LIBM_IEEE754_FLOAT_SHIFT);
		} else {
			__i += __UINT32_C(0x400000) >> __j0;
			__result = __i >> (__LIBM_IEEE754_FLOAT_SHIFT - __j0);
		}
	} else {
		/* The number is too large. It is left implementation defined what happens. */
		return (long int)__x;
	}
	if (__sign < 0)
		__result = -__result;
	return __result;
}
#endif /* !__ieee754_lroundf */

#ifdef __COMPILER_HAVE_LONGLONG
#ifndef __ieee754_llroundf
__LIBM_LOCAL_FUNC(llroundf) __ATTR_WUNUSED __ATTR_CONST __LONGLONG
(__LIBCCALL __ieee754_llroundf)(__IEEE754_FLOAT_TYPE__ __x) {
	__int32_t __j0;
	__uint32_t __i;
	__LONGLONG __result;
	__int32_t __sign;
	__LIBM_GET_FLOAT_WORD(__i, __x);
	__j0   = ((__i >> __LIBM_IEEE754_FLOAT_SHIFT) & __LIBM_IEEE754_FLOAT_MAXEXP) - __LIBM_IEEE754_FLOAT_BIAS;
	__sign = (__i & __INT32_C(0x80000000)) != 0 ? -1 : 1;
	__i &= __UINT32_C(0x7fffff);
	__i |= __UINT32_C(0x800000);
	if (__j0 < (__int32_t)(8 * sizeof(__LONGLONG)) - 1) {
		if (__j0 < 0) {
			return __j0 < -1 ? 0 : __sign;
		} else if (__j0 >= __LIBM_IEEE754_FLOAT_SHIFT) {
			__result = (__LONGLONG)__i << (__j0 - __LIBM_IEEE754_FLOAT_SHIFT);
		} else {
			__i += __UINT32_C(0x400000) >> __j0;
			__result = __i >> (__LIBM_IEEE754_FLOAT_SHIFT - __j0);
		}
	} else {
		/* The number is too large.
		 * It is left implementation defined what happens. */
		return (__LONGLONG)__x;
	}
	if (__sign < 0)
		__result = -__result;
	return __result;
}
#endif /* !__ieee754_llroundf */
#endif /* __COMPILER_HAVE_LONGLONG */
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
#ifndef __ieee754_lround
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

__LIBM_LOCAL_FUNC(lround) __ATTR_WUNUSED __ATTR_CONST long int
(__LIBCCALL __ieee754_lround)(__IEEE754_DOUBLE_TYPE__ __x) {
	__int32_t __j0;
	__uint32_t __i1, __i0;
	long int __result;
	__int32_t __sign;
	__LIBM_GET_DOUBLE_WORDS(__i0, __i1, __x);
	/* Extract exponent field. */
	__j0 = ((__i0 >> __LIBM_IEEE754_DOUBLE_SHIFT) & __LIBM_IEEE754_DOUBLE_MAXEXP) - __LIBM_IEEE754_DOUBLE_BIAS;
	/* Extract sign. */
	__sign = (__i0 & __INT32_C(0x80000000)) != 0 ? -1 : 1;
	__i0 &= __UINT32_C(0x000fffff);
	__i0 |= __UINT32_C(0x00100000);
	/* j0 in [-1023,1024] */
	if (__j0 < __LIBM_IEEE754_DOUBLE_SHIFT) {
		/* j0 in [-1023,19] */
		if (__j0 < 0) {
			return __j0 < -1 ? 0 : __sign;
		} else {
			/* j0 in [0,19] */
			/* shift amt in [0,19] */
			__i0 += __UINT32_C(0x80000) >> __j0;
			/* shift amt in [20,1] */
			__result = __i0 >> (__LIBM_IEEE754_DOUBLE_SHIFT - __j0);
		}
	} else if (__j0 < (__int32_t)(8 * sizeof(long int)) - 1) {
		/* 32bit long: j0 in [20,30] */
		/* 64bit long: j0 in [20,62] */
		if (__j0 >= 52) {
			/* 64bit long: j0 in [52,62] */
			/* 64bit long: shift amt in [32,42] */
			if ((__j0 - __LIBM_IEEE754_DOUBLE_SHIFT) >= (__int32_t)(8 * sizeof(long int))) {
				__result = 0;
			} else {
				__result = (long int)__i0 << (__j0 - __LIBM_IEEE754_DOUBLE_SHIFT);
			}
			if ((__j0 - 52) < 32)
				__result |= (unsigned long int)__i1 << (__j0 - 52);
		} else {
			/* 32bit long: j0 in [20,30] */
			/* 64bit long: j0 in [20,51] */
			__uint32_t j = __i1 + (__UINT32_C(0x80000000) >> (__j0 - __LIBM_IEEE754_DOUBLE_SHIFT));
			if (j < __i1)
				++__i0;
			if (__j0 == __LIBM_IEEE754_DOUBLE_SHIFT) {
				__result = (long int)__i0;
			} else {
				__result = ((long int)__i0 << (__j0 - __LIBM_IEEE754_DOUBLE_SHIFT)) | (j >> (52 - __j0));
			}
		}
	} else {
		/* The number is too large.
		 * It is left implementation defined what happens. */
		return (long int)__x;
	}
	if (__sign < 0)
		__result = -__result;
	return __result;
}
#endif /* !__ieee754_lround */

#ifdef __COMPILER_HAVE_LONGLONG
#ifndef __ieee754_llround
__LIBM_LOCAL_FUNC(llround) __ATTR_WUNUSED __ATTR_CONST __LONGLONG
(__LIBCCALL __ieee754_llround)(__IEEE754_DOUBLE_TYPE__ __x) {
	__int32_t __j0;
	__uint32_t __i1, __i0;
	__LONGLONG __result;
	__int32_t __sign;
	__LIBM_GET_DOUBLE_WORDS(__i0, __i1, __x);
	/* Extract exponent field. */
	__j0 = ((__i0 >> __LIBM_IEEE754_DOUBLE_SHIFT) & __LIBM_IEEE754_DOUBLE_MAXEXP) - __LIBM_IEEE754_DOUBLE_BIAS;
	/* Extract sign. */
	__sign = (__i0 & __INT32_C(0x80000000)) != 0 ? -1 : 1;
	__i0 &= __UINT32_C(0x000fffff);
	__i0 |= __UINT32_C(0x00100000);
	/* j0 in [-1023,1024] */
	if (__j0 < __LIBM_IEEE754_DOUBLE_SHIFT) {
		/* j0 in [-1023,19] */
		if (__j0 < 0) {
			return __j0 < -1 ? 0 : __sign;
		} else {
			/* j0 in [0,19] */
			/* shift amt in [0,19] */
			__i0 += __UINT32_C(0x80000) >> __j0;
			/* shift amt in [20,1] */
			__result = __i0 >> (__LIBM_IEEE754_DOUBLE_SHIFT - __j0);
		}
	} else if (__j0 < (__int32_t)(8 * sizeof(__LONGLONG)) - 1) {
		/* 32bit long: j0 in [20,30] */
		/* 64bit long: j0 in [20,62] */
		if (__j0 >= 52) {
			/* 64bit long: j0 in [52,62] */
			/* 64bit long: shift amt in [32,42] */
			if ((__j0 - __LIBM_IEEE754_DOUBLE_SHIFT) >= (__int32_t)(8 * sizeof(__LONGLONG))) {
				__result = 0;
			} else {
				__result = (__LONGLONG)__i0 << (__j0 - __LIBM_IEEE754_DOUBLE_SHIFT);
			}
			if ((__j0 - 52) < 32)
				__result |= (__ULONGLONG)__i1 << (__j0 - 52);
		} else {
			/* 32bit long: j0 in [20,30] */
			/* 64bit long: j0 in [20,51] */
			__uint32_t j = __i1 + (__UINT32_C(0x80000000) >> (__j0 - __LIBM_IEEE754_DOUBLE_SHIFT));
			if (j < __i1)
				++__i0;
			if (__j0 == __LIBM_IEEE754_DOUBLE_SHIFT) {
				__result = (__LONGLONG)__i0;
			} else {
				__result = ((__LONGLONG)__i0 << (__j0 - __LIBM_IEEE754_DOUBLE_SHIFT)) | (j >> (52 - __j0));
			}
		}
	} else {
		/* The number is too large.
		 * It is left implementation defined what happens. */
		return (__LONGLONG)__x;
	}
	if (__sign < 0)
		__result = -__result;
	return __result;
}
#endif /* !__ieee754_llround */
#endif /* __COMPILER_HAVE_LONGLONG */
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifndef __ieee854_lroundl
/* Round double value to long int.
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

__LIBM_LOCAL_FUNC(lroundl) __ATTR_WUNUSED __ATTR_CONST long int
(__LIBCCALL __ieee854_lroundl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__int32_t __j0;
	__uint32_t __se, __i1, __i0;
	long int __result;
	__int32_t __sign;
	__LIBM_GET_LDOUBLE_WORDS(__se, __i0, __i1, __x);
	__j0   = (__se & IEEE854_LONG_DOUBLE_MAXEXP) - IEEE854_LONG_DOUBLE_BIAS;
	__sign = (__se & 0x8000) != 0 ? -1 : 1;
	if (__j0 < 31) {
		if (__j0 < 0) {
			return __j0 < -1 ? 0 : __sign;
		} else {
			__uint32_t j = __i0 + (__UINT32_C(0x40000000) >> __j0);
			if (j < __i0) {
				j >>= 1;
				j |= __UINT32_C(0x80000000);
				++__j0;
			}
			__result = j >> (31 - __j0);
		}
	} else if (__j0 < (__int32_t)(8 * sizeof(long int)) - 1) {
		if (__j0 >= 63) {
			__result = (long int)__i0 << (__j0 - 31);
			if ((__j0 - 63) < 32)
				__result |= (unsigned long int)__i1 << (__j0 - 63);
		} else {
			__uint32_t j = __i1 + (__UINT32_C(0x80000000) >> (__j0 - 31));
			if (j < __i1)
				++__i0;
			if (__j0 == 31) {
				__result = (long int)__i0;
			} else {
				__result = ((long int)__i0 << (__j0 - 31)) | (j >> (63 - __j0));
			}
		}
	} else {
		/* The number is too large.
		 * It is left implementation defined what happens. */
		return (long int)__x;
	}
	if (__sign < 0)
		__result = -__result;
	return __result;
}
#endif /* !__ieee854_lroundl */

#ifdef __COMPILER_HAVE_LONGLONG
#ifndef __ieee854_llroundl
__LIBM_LOCAL_FUNC(llroundl) __ATTR_WUNUSED __ATTR_CONST __LONGLONG
(__LIBCCALL __ieee854_llroundl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__int32_t __j0;
	__uint32_t __se, __i1, __i0;
	__LONGLONG __result;
	__int32_t __sign;
	__LIBM_GET_LDOUBLE_WORDS(__se, __i0, __i1, __x);
	__j0   = (__se & IEEE854_LONG_DOUBLE_MAXEXP) - IEEE854_LONG_DOUBLE_BIAS;
	__sign = (__se & 0x8000) != 0 ? -1 : 1;
	if (__j0 < 31) {
		if (__j0 < 0) {
			return __j0 < -1 ? 0 : __sign;
		} else {
			__uint32_t j = __i0 + (__UINT32_C(0x40000000) >> __j0);
			if (j < __i0) {
				j >>= 1;
				j |= __UINT32_C(0x80000000);
				++__j0;
			}
			__result = j >> (31 - __j0);
		}
	} else if (__j0 < (__int32_t)(8 * sizeof(__LONGLONG)) - 1) {
		if (__j0 >= 63) {
			__result = (__LONGLONG)__i0 << (__j0 - 31);
			if ((__j0 - 63) < 32)
				__result |= (__ULONGLONG)__i1 << (__j0 - 63);
		} else {
			__uint32_t j = __i1 + (__UINT32_C(0x80000000) >> (__j0 - 31));
			if (j < __i1)
				++__i0;
			if (__j0 == 31) {
				__result = (__LONGLONG)__i0;
			} else {
				__result = ((__LONGLONG)__i0 << (__j0 - 31)) | (j >> (63 - __j0));
			}
		}
	} else {
		/* The number is too large.
		 * It is left implementation defined what happens. */
		return (__LONGLONG)__x;
	}
	if (__sign < 0)
		__result = -__result;
	return __result;
}
#endif /* !__ieee854_llroundl */
#endif /* __COMPILER_HAVE_LONGLONG */
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_LROUND_H */
