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
#ifndef _LIBM_ISCANONICAL_H
#define _LIBM_ISCANONICAL_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/floatcore.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/fdlibm.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE854_LONG_DOUBLE_TYPE__
/* Test whether long double value is canonical.  ldbl-96 version.
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

__LIBM_LOCAL_FUNC(iscanonicall) __ATTR_WUNUSED __ATTR_CONST int
(__LIBCCALL __ieee854_iscanonicall)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__uint32_t __se, __i0, __i1;
	__int32_t __ix;
	__BOOL __mant_high;
	__LIBM_GET_LDOUBLE_WORDS(__se, __i0, __i1, __x);
	__ix        = __se & 0x7fff;
	__mant_high = (__i0 & 0x80000000) != 0;
#if __LDBL_MIN_EXP__ == -16381
	return __ix > 0 ? __mant_high : !__mant_high;
#else /* __LDBL_MIN_EXP__ == -16381 */
	return __ix == 0 || __ix == 0x7fff || __mant_high;
#endif /* __LDBL_MIN_EXP__ != -16381 */
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_ISCANONICAL_H */
