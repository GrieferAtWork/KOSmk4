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
#ifndef _LIBM_NEXTUP_H
#define _LIBM_NEXTUP_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/floatcore.h>
#include <hybrid/typecore.h>

#include <bits/math-constants.h>
#include <bits/types.h>

#include <libm/fdlibm.h>
#include <libm/isinf.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
/* Return the least floating-point number greater than X.
   Copyright (C) 2016-2020 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

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
   <https://www.gnu.org/licenses/>.  */

__LIBM_LOCAL_FUNC(nextupf) __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_nextupf)(__IEEE754_FLOAT_TYPE__ __x) {
	__int32_t __hx, __ix;
	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__ix = __hx & __INT32_C(0x7fffffff);
	if (__ix == 0)
		return __IEEE754_FLOAT_C(1.40129846432481707092e-45); /* FLT_TRUE_MIN */
	if (__ix > __INT32_C(0x7f800000)) /* x is nan. */
		return __x + __x;
	if (__hx >= 0) { /* x > 0. */
		if (__ieee754_isinf(__x))
			return __x;
		__hx += 1;
	} else {
		__hx -= 1;
	}
	__LIBM_SET_FLOAT_WORD(__x, __hx);
	return __x;
}
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
/* Return the least floating-point number greater than X.
   Copyright (C) 2016-2020 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

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
   <https://www.gnu.org/licenses/>.  */

__LIBM_LOCAL_FUNC(nextup) __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_nextup)(__IEEE754_DOUBLE_TYPE__ __x) {
	__int32_t __hx, __ix;
	__uint32_t __lx;
	__LIBM_EXTRACT_WORDS(__hx, __lx, __x);
	__ix = __hx & __INT32_C(0x7fffffff);
	if (__ix >= __INT32_C(0x7ff00000) &&
	    ((__ix - __INT32_C(0x7ff00000)) | __lx) != 0) /* x is nan. */
		return __x + __x;
	if ((__ix | __lx) == 0)
		return ((__IEEE754_DOUBLE_TYPE__)4.94065645841246544177e-324L); /* DBL_TRUE_MIN */
	if (__hx >= 0) { /* __x > 0.  */
		if (__ieee754_isinf(__x))
			return __x;
		__lx += 1;
		if (__lx == 0)
			__hx += 1;
	} else { /* __x < 0.  */
		if (__lx == 0)
			__hx -= 1;
		__lx -= 1;
	}
	__LIBM_INSERT_WORDS(__x, __hx, __lx);
	return __x;
}
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
/* Return the least floating-point number greater than X.
   Copyright (C) 2016-2020 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

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
   <https://www.gnu.org/licenses/>.  */

__LIBM_LOCAL_FUNC(nextupl) __ATTR_WUNUSED __ATTR_CONST __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_nextupl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__uint32_t __hx, __ix, __lx;
	__int32_t __esx;
	__LIBM_GET_LDOUBLE_WORDS(__esx, __hx, __lx, __x);
	__ix = __esx & 0x7fff;
	if (__ix == 0x7fff && ((__hx & 0x7fffffff) | __lx) != 0) /* x is nan. */
		return __x + __x;
	if ((__ix | __hx | __lx) == 0)
		return __LDBL_DENORM_MIN__; /* LDBL_TRUE_MIN */
	if (__esx >= 0) { /* __x > 0.  */
		if (__ieee854_isinfl(__x))
			return __x;
		__lx += 1;
		if (__lx == 0) {
			__hx += 1;
#if __LDBL_MIN_EXP__ == -16381
			if (__hx == 0 || (__esx == 0 && __hx == 0x80000000))
#else /* __LDBL_MIN_EXP__ == -16381 */
			if (__hx == 0)
#endif /* __LDBL_MIN_EXP__ != -16381 */
			{
				__esx += 1;
				__hx |= 0x80000000;
			}
		}
	} else { /* __x < 0.  */
		if (__lx == 0) {
#if __LDBL_MIN_EXP__ == -16381
			if (__hx <= 0x80000000 && __esx != 0xffff8000) {
				__esx -= 1;
				__hx = __hx - 1;
				if ((__esx & 0x7fff) > 0)
					__hx |= 0x80000000;
			} else {
				__hx -= 1;
			}
#else /* __LDBL_MIN_EXP__ == -16381 */
			if (__ix != 0 && __hx == 0x80000000)
				__hx = 0;
			if (__hx == 0)
				__esx -= 1;
			__hx -= 1;
#endif /* __LDBL_MIN_EXP__ != -16381 */
		}
		__lx -= 1;
	}
	__LIBM_SET_LDOUBLE_WORDS(__x, __esx, __hx, __lx);
	return __x;
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_NEXTUP_H */
