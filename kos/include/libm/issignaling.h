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
#ifndef _LIBM_ISSIGNALING_H
#define _LIBM_ISSIGNALING_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/fdlibm.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
/* <<<No copyright notice found in the original file, but was part of fdlibm>>> */

__LIBM_LOCAL_FUNC(issignalingf) __ATTR_WUNUSED __ATTR_CONST int
(__LIBCCALL __ieee754_issignalingf)(__IEEE754_FLOAT_TYPE__ __x) {
	__uint32_t __xi;
	__LIBM_GET_FLOAT_WORD(__xi, __x);
#ifdef __LIBM_HIGH_ORDER_BIT_IS_SET_FOR_SNAN
	/* We only have to care about the high-order bit of x's significand, because
	 * having  it set (sNaN)  already makes the  significand different from that
	 * used to designate infinity. */
	return (__xi & __UINT32_C(0x7fc00000)) == __UINT32_C(0x7fc00000);
#else /* __LIBM_HIGH_ORDER_BIT_IS_SET_FOR_SNAN */
	/* To keep the following comparison simple, toggle the quiet/signaling  bit,
	 * so that it is set for sNaNs. This is inverse to IEEE 754-2008 (as well as
	 * common practice for IEEE 754-1985). */
	__xi ^= __UINT32_C(0x00400000);
	/* We have to compare for greater (instead of greater or equal), because x's
	 * significand    being    all-zero    designates    infinity    not    NaN. */
	return (__xi & __UINT32_C(0x7fffffff)) > __UINT32_C(0x7fc00000);
#endif /* !__LIBM_HIGH_ORDER_BIT_IS_SET_FOR_SNAN */
}
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
/* <<<No copyright notice found in the original file, but was part of fdlibm>>> */

__LIBM_LOCAL_FUNC(issignaling) __ATTR_WUNUSED __ATTR_CONST int
(__LIBCCALL __ieee754_issignaling)(__IEEE754_DOUBLE_TYPE__ __x) {
#ifdef __LIBM_HIGH_ORDER_BIT_IS_SET_FOR_SNAN
	__uint32_t __hxi;
	__LIBM_GET_HIGH_WORD(__hxi, __x);
	/* We only have to care about the high-order bit of x's significand, because
	   having it set (sNaN) already makes the significand different from that
	   used to designate infinity. */
	return (__hxi & __UINT32_C(0x7ff80000)) == __UINT32_C(0x7ff80000);
#else /* __LIBM_HIGH_ORDER_BIT_IS_SET_FOR_SNAN */
	__uint32_t __hxi, __lxi;
	__LIBM_GET_DOUBLE_WORDS(__hxi, __lxi, __x);
	/* To keep the following comparison simple, toggle the quiet/signaling  bit,
	 * so that it is set for sNaNs. This is inverse to IEEE 754-2008 (as well as
	 * common practice for IEEE 754-1985). */
	__hxi ^= __UINT32_C(0x00080000);
	/* If lxi != 0, then set any suitable bit of the significand in hxi. */
	__hxi |= (__lxi | -__lxi) >> 31;
	/* We have to compare for greater (instead of greater or equal), because x's
	 * significand    being    all-zero    designates    infinity    not    NaN. */
	return (__hxi & __UINT32_C(0x7fffffff)) > __UINT32_C(0x7ff80000);
#endif /* !__LIBM_HIGH_ORDER_BIT_IS_SET_FOR_SNAN */
}
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
/* <<<No copyright notice found in the original file, but was part of fdlibm>>> */

__LIBM_LOCAL_FUNC(issignalingl) __ATTR_WUNUSED __ATTR_CONST int
(__LIBCCALL __ieee854_issignalingl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__uint32_t __exi, __hxi, __lxi;
	__LIBM_GET_LDOUBLE_WORDS(__exi, __hxi, __lxi, __x);
#ifdef __LIBM_HIGH_ORDER_BIT_IS_SET_FOR_SNAN
#error not implemented
#else /* __LIBM_HIGH_ORDER_BIT_IS_SET_FOR_SNAN */
	/* To keep the following comparison simple, toggle the quiet/signaling  bit,
	 * so that it is set for sNaNs. This is inverse to IEEE 754-2008 (as well as
	 * common practice for IEEE 754-1985). */
	__hxi ^= __UINT32_C(0x40000000);
	/* If lxi != 0, then set any suitable bit of the significand in hxi. */
	__hxi |= (__lxi | -__lxi) >> 31;
	/* We do not recognize a pseudo NaN as sNaN; they're invalid on 80387 and later. */
	/* We have to compare for greater (instead of greater or equal), because x's
	 * significand    being    all-zero    designates    infinity    not    NaN. */
	return ((__exi & 0x7fff) == 0x7fff) && (__hxi > __UINT32_C(0xc0000000));
#endif /* !__LIBM_HIGH_ORDER_BIT_IS_SET_FOR_SNAN */
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_ISSIGNALING_H */
