/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_BITS_MATHDEF_H
#define _I386_KOS_BITS_MATHDEF_H 1

/* Copyright (C) 2001-2016 Free Software Foundation, Inc.
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
   <http://www.gnu.org/licenses/>.  */

#include <__stdinc.h>
#include <features.h>

#ifdef __CC__
#ifdef __USE_ISOC99
__SYSDECL_BEGIN

#if defined(__x86_64__) || \
   (defined(__FLT_EVAL_METHOD__) && __FLT_EVAL_METHOD__ == 0)
typedef float       float_t;  /* `float' expressions are evaluated as `float'.  */
typedef double      double_t; /* `double' expressions are evaluated as `double'.  */
#else
typedef long double float_t;  /* `float' expressions are evaluated as `long double'.  */
typedef long double double_t; /* `double' expressions are evaluated as `long double'.  */
#endif
/* The values returned by `ilogb' for 0 and NaN respectively.  */
#   define FP_ILOGB0    (-2147483647-1)
#   define FP_ILOGBNAN  (-2147483647-1)
#ifdef __FP_FAST_FMA
#   define FP_FAST_FMA  1
#endif
#ifdef __FP_FAST_FMAF
#   define FP_FAST_FMAF 1
#endif
#ifdef __FP_FAST_FMAL
#   define FP_FAST_FMAL 1
#endif

__SYSDECL_END
#endif /* __USE_ISOC99 */
#endif /* __CC__ */

#endif /* !_I386_KOS_BITS_MATHDEF_H */
