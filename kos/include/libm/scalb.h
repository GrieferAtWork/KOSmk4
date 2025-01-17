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
#ifndef _LIBM_SCALB_H
#define _LIBM_SCALB_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/limitcore.h> /* __INT_MAX__ */
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libc/fenv.h>
#include <libm/fdlibm.h>
#include <libm/finite.h>
#include <libm/isnan.h>
#include <libm/nan.h>
#include <libm/rint.h>
#include <libm/scalbn.h>

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

__LIBM_LOCAL_FUNC(scalbf) __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_scalbf)(__IEEE754_FLOAT_TYPE__ __x,
                              __IEEE754_FLOAT_TYPE__ __fn) {
	if (__ieee754_isnanf(__x) || __ieee754_isnanf(__fn))
		return __x * __fn;
	if (!__ieee754_finitef(__fn)) {
		if (__fn > __IEEE754_FLOAT_C(0.0)) {
			return __x * __fn;
		} else {
			return __x / (-__fn);
		}
	}
	if (__ieee754_rintf(__fn) != __fn)
		return (__fn - __fn) / (__fn - __fn);
#if __INT_MAX__ > 65000
	if (__fn > __IEEE754_FLOAT_C(65000.0))
		return __ieee754_scalbnf(__x, 65000);
	if (-__fn > __IEEE754_FLOAT_C(65000.0))
		return __ieee754_scalbnf(__x, -65000);
#else /* __INT_MAX__ > 65000 */
	if (__fn > __IEEE754_FLOAT_C(32000.0))
		return __ieee754_scalbnf(__x, 32000);
	if (-__fn > __IEEE754_FLOAT_C(32000.0))
		return __ieee754_scalbnf(__x, -32000);
#endif /* __INT_MAX__ <= 65000 */
	return __ieee754_scalbnf(__x, (int)__fn);
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

__LIBM_LOCAL_FUNC(scalb) __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_scalb)(__IEEE754_DOUBLE_TYPE__ __x,
                             __IEEE754_DOUBLE_TYPE__ __fn) {
	if (__ieee754_isnan(__x) || __ieee754_isnan(__fn))
		return __x * __fn;
	if (!__ieee754_finite(__fn)) {
		if (__fn > __IEEE754_DOUBLE_C(0.0)) {
			return __x * __fn;
		} else {
			return __x / (-__fn);
		}
	}
	if (__ieee754_rint(__fn) != __fn)
		return (__fn - __fn) / (__fn - __fn);
#if __INT_MAX__ == 32767
	if (__fn > __IEEE754_DOUBLE_C(65000.0))
		return __ieee754_scalbln(__x, 65000);
	if (-__fn > __IEEE754_DOUBLE_C(65000.0))
		return __ieee754_scalbln(__x, -65000);
#else /* __INT_MAX__ == 32767 */
	if (__fn > __IEEE754_DOUBLE_C(65000.0))
		return __ieee754_scalbn(__x, 65000);
	if (-__fn > __IEEE754_DOUBLE_C(65000.0))
		return __ieee754_scalbn(__x, -65000);
#endif /* __INT_MAX__ != 32767 */
	return __ieee754_scalbn(__x, (int)__fn);
}

#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
/* Copyright (C) 2011-2013 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@gmail.com>, 2011.

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

__LIBM_LOCAL_FUNC(scalbl) __ATTR_WUNUSED __ATTR_CONST __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_scalbl)(__IEEE854_LONG_DOUBLE_TYPE__ __x,
                              __IEEE854_LONG_DOUBLE_TYPE__ __fn) {
	__int64_t __ifn;
	if (__ieee854_isnanl(__x))
		return __x * __fn;
	if (!__ieee854_finitel(__fn)) {
		if (__ieee854_isnanl(__fn) || __fn > __IEEE854_LONG_DOUBLE_C(0.0))
			return __x * __fn;
		if (__x == __IEEE854_LONG_DOUBLE_C(0.0))
			return __x;
		return __x / -__fn;
	}
	__ifn = (__int64_t)__fn;
	if ((__IEEE854_LONG_DOUBLE_TYPE__)__ifn != __fn) {
		if (__ieee854_rintl(__fn) != __fn) {
			__libc_feraiseexcept(FE_INVALID);
			return __ieee854_nanl("");
		}
		if (__ifn > 65000l)
			return __ieee854_scalblnl(__x, 65000l);
		return __ieee854_scalblnl(__x, -65000l);
	}
	return __ieee854_scalblnl(__x, __ifn);
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_SCALB_H */
