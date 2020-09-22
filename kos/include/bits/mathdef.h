/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_MATHDEF_H
#define _BITS_MATHDEF_H 1

#include <__stdinc.h>

#include <hybrid/limitcore.h>

#ifdef __CC__
__DECL_BEGIN

#if (defined(__FLT_EVAL_METHOD__) && (__FLT_EVAL_METHOD__ + 0) == 2)
#ifdef __COMPILER_HAVE_LONGDOUBLE
typedef __LONGDOUBLE __float_t;
typedef __LONGDOUBLE __double_t;
#else /* __COMPILER_HAVE_LONGDOUBLE */
typedef double __float_t;
typedef double __double_t;
#endif /* !__COMPILER_HAVE_LONGDOUBLE */
#elif (defined(__FLT_EVAL_METHOD__) && (__FLT_EVAL_METHOD__ + 0) == 1)
typedef double __float_t;
typedef double __double_t;
#else /* __FLT_EVAL_METHOD__ == ... */
typedef float  __float_t;
typedef double __double_t;
#endif /* __FLT_EVAL_METHOD__ != ... */

__DECL_END
#endif /* __CC__ */

/* The values returned by `ilogb' for 0 and NaN respectively. */
#define __FP_ILOGB0   __INT_MIN__
#define __FP_ILOGBNAN __INT_MAX__

/* #define __FP_FAST_FMA 1 */
/* #define __FP_FAST_FMAF 1 */
/* #define __FP_FAST_FMAL 1 */

#endif /* !_BITS_MATHDEF_H */
