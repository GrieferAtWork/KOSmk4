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
#ifndef _I386_KOS_BITS_MATHDEF_H
#define _I386_KOS_BITS_MATHDEF_H 1

#include <__stdinc.h>
#include <hybrid/limitcore.h> /* __INT_MIN__ */

#ifdef __CC__
__DECL_BEGIN
#if (defined(__x86_64__) || \
     (defined(__FLT_EVAL_METHOD__) && __FLT_EVAL_METHOD__ == 0))
typedef float  __float_t;  /* `float' expressions are evaluated as `float'.  */
typedef double __double_t; /* `double' expressions are evaluated as `double'.  */
#else /* __x86_64__ || __FLT_EVAL_METHOD__ == 0 */
typedef __LONGDOUBLE __float_t;  /* `float' expressions are evaluated as `long double'.  */
typedef __LONGDOUBLE __double_t; /* `double' expressions are evaluated as `long double'.  */
#endif /* !__x86_64__ && __FLT_EVAL_METHOD__ != 0 */
__DECL_END
#endif /* __CC__ */

/* The values returned by `ilogb' for 0 and NaN respectively. */
#define __FP_ILOGB0   __INT_MIN__
#define __FP_ILOGBNAN __INT_MIN__

#endif /* !_I386_KOS_BITS_MATHDEF_H */
