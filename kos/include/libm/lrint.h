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
#ifndef _LIBM_LRINT_H
#define _LIBM_LRINT_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/limitcore.h>
#include <hybrid/typecore.h>

#include <bits/crt/fenv.h>
#include <bits/types.h>

#include <libc/fenv.h>
#include <libm/asm/lrint.h>
#include <libm/fdlibm.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
#ifndef __ieee754_lrintf
/* <<<No copyright notice found in the original file, but was part of fdlibm>>> */

__LIBM_LOCAL_FUNC(lrintf) __ATTR_WUNUSED __ATTR_CONST long int
(__LIBCCALL __ieee754_lrintf)(__IEEE754_FLOAT_TYPE__ __x) {
	__int32_t __j0;
	__uint32_t __i0;
	long int __result;
	__int32_t __sx;
	int __rm;
	__rm = __libc_fegetround();
	__LIBM_GET_FLOAT_WORD(__i0, __x);
	__sx = __i0 & __INT32_C(0x80000000);
	__j0 = ((__i0 >> IEEE754_FLOAT_SHIFT) & IEEE754_FLOAT_MAXEXP) - IEEE754_FLOAT_BIAS;
	__i0 &= __UINT32_C(0x7fffff);
	if (__j0 < (__int32_t)(sizeof(long int) * 8) - 1) {
		if (__j0 == -IEEE754_FLOAT_BIAS)
			return 0;
		/* Raise inexact if x != 0. */
		if (__j0 < 0 || __i0 != 0)
			__libc_feraiseexcept(FE_INEXACT);
		if (__j0 < 0) {
			switch (__rm) {
			case FE_TOWARDZERO: return 0;
			case FE_DOWNWARD: return __sx ? -1 : 0;
			case FE_UPWARD: return __sx ? 0 : 1;
			}
			/* case FE_TONEAREST: */
			if (__j0 == -1 && __i0 != 0)
				return __sx ? -1 : 1;
			return 0;
		}
		if (__j0 >= IEEE754_FLOAT_SHIFT) {
			__i0 |= __UINT32_C(0x800000);
			__result = (long int)__i0 << (__j0 - IEEE754_FLOAT_SHIFT);
		} else {
			__uint32_t __i = __UINT32_C(0x007fffff) >> __j0;
			switch (__rm) {
			case FE_TOWARDZERO:
				__i0 |= __UINT32_C(0x800000);
				break;
			case FE_DOWNWARD:
				__i0 |= __UINT32_C(0x800000);
				if (__sx && (__i0 & __i) != 0)
					__i0 += __UINT32_C(0x00800000) >> __j0;
				break;
			case FE_UPWARD:
				__i0 |= __UINT32_C(0x800000);
				if (!__sx && (__i0 & __i) != 0)
					__i0 += __UINT32_C(0x00800000) >> __j0;
				break;
			case FE_TONEAREST:
			default:
				__i0 |= __UINT32_C(0x800000);
				if ((__i0 & (__i >> 1)) != 0 || (__i0 & (__UINT32_C(0x00800000) >> __j0))) {
					__i0 += __UINT32_C(0x00400000) >> __j0;
				}
				break;
			}
			__i0 &= (~__i);
			__result = __i0 >> (IEEE754_FLOAT_SHIFT - __j0);
		}
	} else {
		/* The number is too large.
		 * It is left implementation defined what happens. */
		__libc_feraiseexcept(FE_INVALID | FE_INEXACT);
		if (__j0 == (IEEE754_FLOAT_MAXEXP - IEEE754_FLOAT_BIAS)) {
			/* inf or nan */
			return __LONG_MIN__;
		}
		return (long int)__x;
	}
	return __sx ? -__result : __result;
}
#endif /* !__ieee754_lrintf */

#ifdef __COMPILER_HAVE_LONGLONG
#ifndef __ieee754_llrintf
__LIBM_LOCAL_FUNC(llrintf) __ATTR_WUNUSED __ATTR_CONST __LONGLONG
(__LIBCCALL __ieee754_llrintf)(__IEEE754_FLOAT_TYPE__ __x) {
	__int32_t __j0;
	__uint32_t __i0;
	__LONGLONG __result;
	__int32_t __sx;
	int __rm;
	__rm = __libc_fegetround();
	__LIBM_GET_FLOAT_WORD(__i0, __x);
	__sx = __i0 & __INT32_C(0x80000000);
	__j0 = ((__i0 >> IEEE754_FLOAT_SHIFT) & IEEE754_FLOAT_MAXEXP) - IEEE754_FLOAT_BIAS;
	__i0 &= __UINT32_C(0x7fffff);
	if (__j0 < (__int32_t)(sizeof(__LONGLONG) * 8) - 1) {
		if (__j0 == -IEEE754_FLOAT_BIAS)
			return 0;
		/* Raise inexact if x != 0. */
		if (__j0 < 0 || __i0 != 0)
			__libc_feraiseexcept(FE_INEXACT);
		if (__j0 < 0) {
			switch (__rm) {
			case FE_TOWARDZERO: return 0;
			case FE_DOWNWARD: return __sx ? -1 : 0;
			case FE_UPWARD: return __sx ? 0 : 1;
			}
			/* case FE_TONEAREST: */
			if (__j0 == -1 && __i0 != 0)
				return __sx ? -1 : 1;
			return 0;
		}
		if (__j0 >= IEEE754_FLOAT_SHIFT) {
			__i0 |= __UINT32_C(0x800000);
			__result = (__LONGLONG)__i0 << (__j0 - IEEE754_FLOAT_SHIFT);
		} else {
			__uint32_t __i = __UINT32_C(0x007fffff) >> __j0;
			switch (__rm) {
			case FE_TOWARDZERO:
				__i0 |= __UINT32_C(0x800000);
				break;
			case FE_DOWNWARD:
				__i0 |= __UINT32_C(0x800000);
				if (__sx && (__i0 & __i) != 0)
					__i0 += __UINT32_C(0x00800000) >> __j0;
				break;
			case FE_UPWARD:
				__i0 |= __UINT32_C(0x800000);
				if (!__sx && (__i0 & __i) != 0)
					__i0 += __UINT32_C(0x00800000) >> __j0;
				break;
			case FE_TONEAREST:
			default:
				__i0 |= __UINT32_C(0x800000);
				if ((__i0 & (__i >> 1)) != 0 || (__i0 & (__UINT32_C(0x00800000) >> __j0))) {
					__i0 += __UINT32_C(0x00400000) >> __j0;
				}
				break;
			}
			__i0 &= (~__i);
			__result = __i0 >> (IEEE754_FLOAT_SHIFT - __j0);
		}
	} else {
		/* The number is too large.
		 * It is left implementation defined what happens. */
		__libc_feraiseexcept(FE_INVALID | FE_INEXACT);
		if (__j0 == (IEEE754_FLOAT_MAXEXP - IEEE754_FLOAT_BIAS)) {
			/* inf or nan */
			return __LONG_LONG_MIN__;
		}
		return (__LONGLONG)__x;
	}
	return __sx ? -__result : __result;
}
#endif /* !__ieee754_llrintf */
#endif /* __COMPILER_HAVE_LONGLONG */
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
#ifndef __ieee754_lrint
/* <<<No copyright notice found in the original file, but was part of fdlibm>>> */

__LIBM_LOCAL_FUNC(lrint) __ATTR_WUNUSED __ATTR_CONST long int
(__LIBCCALL __ieee754_lrint)(__IEEE754_DOUBLE_TYPE__ __x) {
	__int32_t __j0;
	__uint32_t __i0, __i1;
	long int __result;
	__int32_t __sx;
	int __rm;
	__rm = __libc_fegetround();
	__LIBM_GET_DOUBLE_WORDS(__i0, __i1, __x);
	__j0 = ((__i0 >> IEEE754_DOUBLE_SHIFT) & IEEE754_DOUBLE_MAXEXP) - IEEE754_DOUBLE_BIAS;
	__sx = __i0 & __INT32_C(0x80000000);
	__i0 &= __UINT32_C(0xfffff);
	if (__j0 < IEEE754_DOUBLE_SHIFT) {
		__uint32_t __i;
		if (__j0 == -IEEE754_DOUBLE_BIAS)
			return 0;
		/* Raise inexact if x != 0. */
		if (__j0 < 0 || (__i0 | __i1) != 0)
			__libc_feraiseexcept(FE_INEXACT);
		if (__j0 < 0) {
			switch (__rm) {
			case FE_TOWARDZERO: return 0;
			case FE_DOWNWARD: return __sx ? -1 : 0;
			case FE_UPWARD: return __sx ? 0 : 1;
			}
			/* case FE_TONEAREST: */
			if (__j0 == -1 && (__i0 | __i1) != 0)
				return __sx ? -1 : 1;
			return 0;
		}
		switch (__rm) {
		case FE_TOWARDZERO:
			__i0 |= __UINT32_C(0x100000);
			break;
		case FE_DOWNWARD:
			__i = __UINT32_C(0x000fffff) >> __j0;
			__i0 |= __UINT32_C(0x100000);
			if (__sx && ((__i0 & __i) | __i1) != 0)
				__i0 += __UINT32_C(0x00100000) >> __j0;
			break;
		case FE_UPWARD:
			__i = __UINT32_C(0x000fffff) >> __j0;
			__i0 |= __UINT32_C(0x100000);
			if (!__sx && ((__i0 & __i) | __i1) != 0)
				__i0 += __INT32_C(0x00100000) >> __j0;
			break;
		case FE_TONEAREST:
		default:
			__i = __UINT32_C(0x000fffff) >> __j0;
			__i0 |= __UINT32_C(0x100000);
			if ((__i0 & (__i >> 1)) != 0 || __i1 != 0 || (__i0 & (__UINT32_C(0x00100000) >> __j0))) {
				__i0 += __UINT32_C(0x00080000) >> __j0;
			}
			break;
		}
		__result = __i0 >> (IEEE754_DOUBLE_SHIFT - __j0);
	} else if (__j0 < (__int32_t)(8 * sizeof(long int)) - 1) {
		if (__j0 >= 52) {
			__i0 |= __UINT32_C(0x100000);
			if ((__j0 - IEEE754_DOUBLE_SHIFT) >= (__int32_t)(8 * sizeof(long int))) {
				__result = 0;
			} else {
				__result = (long int)__i0 << (__j0 - IEEE754_DOUBLE_SHIFT);
			}
			if ((__j0 - 52) < 32)
				__result |= (unsigned long int)__i1 << (__j0 - 52);
		} else {
			__uint32_t __i = __UINT32_C(0xffffffff) >> (__j0 - IEEE754_DOUBLE_SHIFT);
			__uint32_t __j;
			switch (__rm) {
			case FE_TOWARDZERO:
				__i0 |= __UINT32_C(0x100000);
				break;
			case FE_DOWNWARD:
				__i0 |= __UINT32_C(0x100000);
				if (__sx && (__i1 & __i) != 0) {
					if (__j0 == IEEE754_DOUBLE_SHIFT) {
						__i0 += 1;
					} else {
						__j = __i1 + (__UINT32_C(1) << (52 - __j0));
						if (__j < __i1)
							__i0 += 1; /* got a carry */
						__i1 = __j;
					}
				}
				break;
			case FE_UPWARD:
				__i0 |= __UINT32_C(0x100000);
				if (!__sx && (__i1 & __i) != 0) {
					if (__j0 == IEEE754_DOUBLE_SHIFT) {
						__i0 += 1;
					} else {
						__j = __i1 + (__UINT32_C(1) << (52 - __j0));
						if (__j < __i1)
							__i0 += 1; /* got a carry */
						__i1 = __j;
					}
				}
				break;
			case FE_TONEAREST:
			default:
				__i0 |= __UINT32_C(0x100000);
				if ((__i1 & (__i >> 1)) != 0 ||
				    (__j0 == IEEE754_DOUBLE_SHIFT && (__i0 & 1)) ||
				    (__i1 & (__UINT32_C(1) << (52 - __j0)))) {
					__j = __i1 + (__UINT32_C(1) << (51 - __j0));
					if (__j < __i1)
						__i0 += 1;
					__i1 = __j;
				}
				break;
			}
			__i1 &= ~__i;
			if (__j0 == IEEE754_DOUBLE_SHIFT) {
				__result = (long int)__i0;
			} else {
				__result = ((long int)__i0 << (__j0 - IEEE754_DOUBLE_SHIFT)) |
				         (__i1 >> (52 - __j0));
			}
		}
	} else {
		/* The number is too large.
		 * It is left implementation defined what happens. */
		__libc_feraiseexcept(FE_INVALID | FE_INEXACT);
		if (__j0 == (IEEE754_DOUBLE_MAXEXP - IEEE754_DOUBLE_BIAS)) {
			/* inf or nan */
			return __LONG_MIN__;
		}
		return (long int)__x;
	}
	return __sx ? -__result : __result;
}
#endif /* !__ieee754_lrint */

#ifdef __COMPILER_HAVE_LONGLONG
#ifndef __ieee754_llrint
__LIBM_LOCAL_FUNC(llrint) __ATTR_WUNUSED __ATTR_CONST __LONGLONG
(__LIBCCALL __ieee754_llrint)(__IEEE754_DOUBLE_TYPE__ __x) {
	__int32_t __j0;
	__uint32_t __i0, __i1;
	__LONGLONG __result;
	__int32_t __sx;
	int __rm;
	__rm = __libc_fegetround();
	__LIBM_GET_DOUBLE_WORDS(__i0, __i1, __x);
	__j0 = ((__i0 >> IEEE754_DOUBLE_SHIFT) & IEEE754_DOUBLE_MAXEXP) - IEEE754_DOUBLE_BIAS;
	__sx = __i0 & __INT32_C(0x80000000);
	__i0 &= __UINT32_C(0xfffff);
	if (__j0 < IEEE754_DOUBLE_SHIFT) {
		__uint32_t __i;
		if (__j0 == -IEEE754_DOUBLE_BIAS)
			return 0;
		/* Raise inexact if x != 0. */
		if (__j0 < 0 || (__i0 | __i1) != 0)
			__libc_feraiseexcept(FE_INEXACT);
		if (__j0 < 0) {
			switch (__rm) {
			case FE_TOWARDZERO: return 0;
			case FE_DOWNWARD: return __sx ? -1 : 0;
			case FE_UPWARD: return __sx ? 0 : 1;
			}
			/* case FE_TONEAREST: */
			if (__j0 == -1 && (__i0 | __i1) != 0)
				return __sx ? -1 : 1;
			return 0;
		}
		switch (__rm) {
		case FE_TOWARDZERO:
			__i0 |= __UINT32_C(0x100000);
			break;
		case FE_DOWNWARD:
			__i = __UINT32_C(0x000fffff) >> __j0;
			__i0 |= __UINT32_C(0x100000);
			if (__sx && ((__i0 & __i) | __i1) != 0)
				__i0 += __UINT32_C(0x00100000) >> __j0;
			break;
		case FE_UPWARD:
			__i = __UINT32_C(0x000fffff) >> __j0;
			__i0 |= __UINT32_C(0x100000);
			if (!__sx && ((__i0 & __i) | __i1) != 0)
				__i0 += __INT32_C(0x00100000) >> __j0;
			break;
		case FE_TONEAREST:
		default:
			__i = __UINT32_C(0x000fffff) >> __j0;
			__i0 |= __UINT32_C(0x100000);
			if ((__i0 & (__i >> 1)) != 0 || __i1 != 0 || (__i0 & (__UINT32_C(0x00100000) >> __j0))) {
				__i0 += __UINT32_C(0x00080000) >> __j0;
			}
			break;
		}
		__result = __i0 >> (IEEE754_DOUBLE_SHIFT - __j0);
	} else if (__j0 < (__int32_t)(8 * sizeof(__LONGLONG)) - 1) {
		if (__j0 >= 52) {
			__i0 |= __UINT32_C(0x100000);
			if ((__j0 - IEEE754_DOUBLE_SHIFT) >= (__int32_t)(8 * sizeof(__LONGLONG))) {
				__result = 0;
			} else {
				__result = (__LONGLONG)__i0 << (__j0 - IEEE754_DOUBLE_SHIFT);
			}
			if ((__j0 - 52) < 32)
				__result |= (__ULONGLONG)__i1 << (__j0 - 52);
		} else {
			__uint32_t __i = __UINT32_C(0xffffffff) >> (__j0 - IEEE754_DOUBLE_SHIFT);
			__uint32_t __j;
			switch (__rm) {
			case FE_TOWARDZERO:
				__i0 |= __UINT32_C(0x100000);
				break;
			case FE_DOWNWARD:
				__i0 |= __UINT32_C(0x100000);
				if (__sx && (__i1 & __i) != 0) {
					if (__j0 == IEEE754_DOUBLE_SHIFT) {
						__i0 += 1;
					} else {
						__j = __i1 + (__UINT32_C(1) << (52 - __j0));
						if (__j < __i1)
							__i0 += 1; /* got a carry */
						__i1 = __j;
					}
				}
				break;
			case FE_UPWARD:
				__i0 |= __UINT32_C(0x100000);
				if (!__sx && (__i1 & __i) != 0) {
					if (__j0 == IEEE754_DOUBLE_SHIFT) {
						__i0 += 1;
					} else {
						__j = __i1 + (__UINT32_C(1) << (52 - __j0));
						if (__j < __i1)
							__i0 += 1; /* got a carry */
						__i1 = __j;
					}
				}
				break;
			case FE_TONEAREST:
			default:
				__i0 |= __UINT32_C(0x100000);
				if ((__i1 & (__i >> 1)) != 0 ||
				    (__j0 == IEEE754_DOUBLE_SHIFT && (__i0 & 1)) ||
				    (__i1 & (__UINT32_C(1) << (52 - __j0)))) {
					__j = __i1 + (__UINT32_C(1) << (51 - __j0));
					if (__j < __i1)
						__i0 += 1;
					__i1 = __j;
				}
				break;
			}
			__i1 &= ~__i;
			if (__j0 == IEEE754_DOUBLE_SHIFT) {
				__result = (__LONGLONG)__i0;
			} else {
				__result = ((__LONGLONG)__i0 << (__j0 - IEEE754_DOUBLE_SHIFT)) |
				         (__i1 >> (52 - __j0));
			}
		}
	} else {
		/* The number is too large.
		 * It is left implementation defined what happens. */
		__libc_feraiseexcept(FE_INVALID | FE_INEXACT);
		if (__j0 == (IEEE754_DOUBLE_MAXEXP - IEEE754_DOUBLE_BIAS)) {
			/* inf or nan */
			return __LONG_LONG_MIN__;
		}
		return (__LONGLONG)__x;
	}
	return __sx ? -__result : __result;
}
#endif /* !__ieee754_llrint */
#endif /* __COMPILER_HAVE_LONGLONG */
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifndef __ieee854_lrintl
/* <<<No copyright notice found in the original file, but was part of fdlibm>>> */

__LIBM_LOCAL_FUNC(lrintl) __ATTR_WUNUSED __ATTR_CONST long int
(__LIBCCALL __ieee854_lrintl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__int32_t __se, __j0;
	__uint32_t __i0, __i1;
	long int __result;
	__int32_t __sx;
	int __rm;
	__rm = __libc_fegetround();
	__LIBM_GET_LDOUBLE_WORDS(__se, __i0, __i1, __x);
	__sx = __se & 0x8000;
	__j0 = (__se & IEEE854_LONG_DOUBLE_MAXEXP) - IEEE854_LONG_DOUBLE_BIAS;
	if (__j0 < 31) {
		__uint32_t __i, __j;
		if (__j0 == -IEEE854_LONG_DOUBLE_BIAS)
			return 0;
		/* Raise inexact if x != 0. */
		if (__j0 < 0 || ((__i0 & __INT32_C(0x7fffffff)) | __i1) != 0)
			__libc_feraiseexcept(FE_INEXACT);
		if (__j0 < 0) {
			switch (__rm) {
			case FE_TOWARDZERO: return 0;
			case FE_DOWNWARD: return __sx ? -1 : 0;
			case FE_UPWARD: return __sx ? 0 : 1;
			}
			/* case FE_TONEAREST: */
			if (__j0 == -1 && ((__i0 & __INT32_C(0x7fffffff)) | __i1) != 0)
				return __sx ? -1 : 1;
			return 0;
		}
		__i = __UINT32_C(0x7fffffff) >> __j0;
		__j = __i0;
		switch (__rm) {
		case FE_TOWARDZERO:
			break;
		case FE_DOWNWARD:
			if (__sx && ((__i0 & __i) | __i1) != 0) {
				__j += __UINT32_C(0x80000000) >> __j0;
				if (__j < __i0) {
					__i = __UINT32_C(0x7fffffff);
					__j += __j;
					++__j0;
				}
			}
			break;
		case FE_UPWARD:
			if (!__sx && ((__i0 & __i) | __i1) != 0) {
				__j += __UINT32_C(0x80000000) >> __j0;
				if (__j < __i0) {
					__i = __UINT32_C(0x7fffffff);
					__j += __j;
					++__j0;
				}
			}
			break;
		case FE_TONEAREST:
		default:
			if ((__i0 & (__i >> 1)) != 0 || __i1 != 0 ||
			    (__i0 & (__UINT32_C(0x80000000) >> __j0))) {
				__j += (__UINT32_C(0x40000000) >> __j0);
				if (__j < __i0) {
					__j += __j;
					++__j0;
				}
			}
			break;
		}
		__i0     = (__j & ~__i) | __INT32_C(0x80000000);
		__result = __i0 >> (31 - __j0);
	} else if (__j0 < (__int32_t)(8 * sizeof(long int)) - 1) {
		if (__j0 >= 63) {
			__result = (long int)__i0 << (__j0 - 31);
			if ((__j0 - 63) < 32)
				__result |= (unsigned long int)__i1 << (__j0 - 63);
		} else {
			__uint32_t __i = __UINT32_C(0xffffffff) >> (__j0 - 31);
			__uint32_t __j;
			switch (__rm) {
			case FE_TOWARDZERO:
				break;
			case FE_DOWNWARD:
				if (__sx && (__i1 & __i) != 0) {
					if (__j0 == 31) {
						__i0 += 1;
					} else {
						__j = __i1 + (__UINT32_C(1) << (63 - __j0));
						if (__j < __i1) {
							__i0 += 1; /* got a carry */
							if (__i0 == 0) {
								__i0 = __UINT32_C(0x80000000);
								++__j0;
							}
						}
						__i1 = __j;
					}
				}
				break;
			case FE_UPWARD:
				if (!__sx && (__i1 & __i) != 0) {
					if (__j0 == 31) {
						__i0 += 1;
					} else {
						__j = __i1 + (__UINT32_C(1) << (63 - __j0));
						if (__j < __i1) {
							__i0 += 1; /* got a carry */
							if (__i0 == 0) {
								__i0 = __UINT32_C(0x80000000);
								__j0++;
							}
						}
						__i1 = __j;
					}
				}
				break;
			case FE_TONEAREST:
			default:
				if ((__i1 & (__i >> 1)) != 0 ||
				    (__j0 == 32 && (__i0 & 1)) ||
				    (__i1 & (__UINT32_C(1) << (63 - __j0)))) {
					__j = __i1 + (__UINT32_C(1) << (62 - __j0));
					if (__j < __i1) {
						__uint32_t __k = __i0 + 1;
						if (__k < __i0) {
							__j += __j;
							++__j0;
							__k |= __UINT32_C(0x80000000);
						}
						__i0 = __k;
					}
					__i1 = __j;
				}
				break;
			}
			__i1 &= ~__i;
			if (__j0 == 31) {
				__result = (long int)__i0;
			} else {
				__result = ((long int)__i0 << (__j0 - 31)) | (__i1 >> (63 - __j0));
			}
		}
	} else {
		/* The number is too large.
		 * It is left implementation defined what happens. */
		__libc_feraiseexcept(FE_INVALID | FE_INEXACT);
		if (__j0 == (IEEE854_LONG_DOUBLE_MAXEXP - IEEE854_LONG_DOUBLE_BIAS)) {
			/* inf or nan */
			return __LONG_MIN__;
		}
		return (long int)__x;
	}
	return __sx ? -__result : __result;
}
#endif /* !__ieee854_lrintl */

#ifdef __COMPILER_HAVE_LONGLONG
#ifndef __ieee854_llrintl
__LIBM_LOCAL_FUNC(llrintl) __ATTR_WUNUSED __ATTR_CONST __LONGLONG
(__LIBCCALL __ieee854_llrintl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__int32_t __se, __j0;
	__uint32_t __i0, __i1;
	__LONGLONG __result;
	__int32_t __sx;
	int __rm;
	__rm = __libc_fegetround();
	__LIBM_GET_LDOUBLE_WORDS(__se, __i0, __i1, __x);
	__sx = __se & 0x8000;
	__j0 = (__se & IEEE854_LONG_DOUBLE_MAXEXP) - IEEE854_LONG_DOUBLE_BIAS;
	if (__j0 < 31) {
		__uint32_t __i, __j;
		if (__j0 == -IEEE854_LONG_DOUBLE_BIAS)
			return 0;
		/* Raise inexact if x != 0. */
		if (__j0 < 0 || ((__i0 & __INT32_C(0x7fffffff)) | __i1) != 0)
			__libc_feraiseexcept(FE_INEXACT);
		if (__j0 < 0) {
			switch (__rm) {
			case FE_TOWARDZERO: return 0;
			case FE_DOWNWARD: return __sx ? -1 : 0;
			case FE_UPWARD: return __sx ? 0 : 1;
			}
			/* case FE_TONEAREST: */
			if (__j0 == -1 && ((__i0 & __INT32_C(0x7fffffff)) | __i1) != 0)
				return __sx ? -1 : 1;
			return 0;
		}
		__i = __UINT32_C(0x7fffffff) >> __j0;
		__j = __i0;
		switch (__rm) {
		case FE_TOWARDZERO:
			break;
		case FE_DOWNWARD:
			if (__sx && ((__i0 & __i) | __i1) != 0) {
				__j += __UINT32_C(0x80000000) >> __j0;
				if (__j < __i0) {
					__i = __UINT32_C(0x7fffffff);
					__j += __j;
					++__j0;
				}
			}
			break;
		case FE_UPWARD:
			if (!__sx && ((__i0 & __i) | __i1) != 0) {
				__j += __UINT32_C(0x80000000) >> __j0;
				if (__j < __i0) {
					__i = __UINT32_C(0x7fffffff);
					__j += __j;
					++__j0;
				}
			}
			break;
		case FE_TONEAREST:
		default:
			if ((__i0 & (__i >> 1)) != 0 || __i1 != 0 ||
			    (__i0 & (__UINT32_C(0x80000000) >> __j0))) {
				__j += (__UINT32_C(0x40000000) >> __j0);
				if (__j < __i0) {
					__j += __j;
					++__j0;
				}
			}
			break;
		}
		__i0     = (__j & ~__i) | __INT32_C(0x80000000);
		__result = __i0 >> (31 - __j0);
	} else if (__j0 < (__int32_t)(8 * sizeof(__LONGLONG)) - 1) {
		if (__j0 >= 63) {
			__result = (__LONGLONG)__i0 << (__j0 - 31);
			if ((__j0 - 63) < 32)
				__result |= (__ULONGLONG)__i1 << (__j0 - 63);
		} else {
			__uint32_t __i = __UINT32_C(0xffffffff) >> (__j0 - 31);
			__uint32_t __j;
			switch (__rm) {
			case FE_TOWARDZERO:
				break;
			case FE_DOWNWARD:
				if (__sx && (__i1 & __i) != 0) {
					if (__j0 == 31) {
						__i0 += 1;
					} else {
						__j = __i1 + (__UINT32_C(1) << (63 - __j0));
						if (__j < __i1) {
							__i0 += 1; /* got a carry */
							if (__i0 == 0) {
								__i0 = __UINT32_C(0x80000000);
								++__j0;
							}
						}
						__i1 = __j;
					}
				}
				break;
			case FE_UPWARD:
				if (!__sx && (__i1 & __i) != 0) {
					if (__j0 == 31) {
						__i0 += 1;
					} else {
						__j = __i1 + (__UINT32_C(1) << (63 - __j0));
						if (__j < __i1) {
							__i0 += 1; /* got a carry */
							if (__i0 == 0) {
								__i0 = __UINT32_C(0x80000000);
								__j0++;
							}
						}
						__i1 = __j;
					}
				}
				break;
			case FE_TONEAREST:
			default:
				if ((__i1 & (__i >> 1)) != 0 ||
				    (__j0 == 32 && (__i0 & 1)) ||
				    (__i1 & (__UINT32_C(1) << (63 - __j0)))) {
					__j = __i1 + (__UINT32_C(1) << (62 - __j0));
					if (__j < __i1) {
						__uint32_t __k = __i0 + 1;
						if (__k < __i0) {
							__j += __j;
							++__j0;
							__k |= __UINT32_C(0x80000000);
						}
						__i0 = __k;
					}
					__i1 = __j;
				}
				break;
			}
			__i1 &= ~__i;
			if (__j0 == 31) {
				__result = (__LONGLONG)__i0;
			} else {
				__result = ((__LONGLONG)__i0 << (__j0 - 31)) | (__i1 >> (63 - __j0));
			}
		}
	} else {
		/* The number is too large.
		 * It is left implementation defined what happens. */
		__libc_feraiseexcept(FE_INVALID | FE_INEXACT);
		if (__j0 == (IEEE854_LONG_DOUBLE_MAXEXP - IEEE854_LONG_DOUBLE_BIAS)) {
			/* inf or nan */
			return __LONG_LONG_MIN__;
		}
		return (__LONGLONG)__x;
	}
	return __sx ? -__result : __result;
}
#endif /* !__ieee854_llrintl */
#endif /* __COMPILER_HAVE_LONGLONG */
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_LRINT_H */
