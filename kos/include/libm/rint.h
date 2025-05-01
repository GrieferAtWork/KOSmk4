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
#ifndef _LIBM_RINT_H
#define _LIBM_RINT_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <bits/crt/fenv.h>
#include <bits/types.h>

#include <libc/fenv.h>
#include <libm/asm/rint.h>
#include <libm/ceil.h>
#include <libm/fdlibm.h>
#include <libm/floor.h>
#include <libm/roundeven.h>
#include <libm/trunc.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
#ifndef __ieee754_rintf
/* <<<No copyright notice found in the original file, but was part of fdlibm>>> */

__LIBM_LOCAL_FUNC(rintf) __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_rintf)(__IEEE754_FLOAT_TYPE__ __x) {
	/* above code relies on a FPU doing the rounding,
	 * and  using   round-to-even  for   FE_TONEAREST */
	switch (__libc_fegetround()) {

	case __FE_UPWARD:
		return __ieee754_ceilf(__x);

	case __FE_DOWNWARD:
		return __ieee754_floorf(__x);

	case __FE_TOWARDZERO:
		return __ieee754_truncf(__x);

/*	case __FE_TONEAREST: */
	default: break;
	}
	return __ieee754_roundevenf(__x);
}
#endif /* !__ieee754_rintf */
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
#ifndef __ieee754_rint
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

__LIBM_LOCAL_FUNC(rint) __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_rint)(__IEEE754_DOUBLE_TYPE__ __x) {
	/* above code relies on a FPU doing the rounding,
	 * and  using   round-to-even  for   FE_TONEAREST */
	switch (__libc_fegetround()) {

	case __FE_UPWARD:
		return __ieee754_ceil(__x);

	case __FE_DOWNWARD:
		return __ieee754_floor(__x);

	case __FE_TOWARDZERO:
		return __ieee754_trunc(__x);
/*	case __FE_TONEAREST: */
	default: break;
	}
	return __ieee754_roundeven(__x);
}
#endif /* !__ieee754_rint */
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifndef __ieee854_rintl
/* <<<No copyright notice found in the original file, but was part of fdlibm>>> */

__LIBM_LOCAL_FUNC(rintl) __ATTR_WUNUSED __ATTR_CONST __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_rintl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	/* above code relies on a FPU doing the rounding,
	 * and  using   round-to-even  for   FE_TONEAREST */
	switch (__libc_fegetround()) {

	case __FE_UPWARD:
		return __ieee854_ceill(__x);

	case __FE_DOWNWARD:
		return __ieee854_floorl(__x);

	case __FE_TOWARDZERO:
		return __ieee854_truncl(__x);
/*	case __FE_TONEAREST: */
	default: break;
	}
	return __ieee854_roundevenl(__x);
}
#endif /* !__ieee854_rintl */
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_RINT_H */
