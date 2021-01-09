/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __GUARD_HYBRID_FLOATCORE_H
#define __GUARD_HYBRID_FLOATCORE_H 1

#include "../__stdinc.h"
//#include "typecore.h"

#ifndef __FLT_EVAL_METHOD__
#if defined(_M_FP_FAST)
#define __FLT_EVAL_METHOD__ (-1)
#elif defined(_M_IX86)
#if defined(_M_IX86_FP) && (_M_IX86_FP + 0) == 2
#define __FLT_EVAL_METHOD__ 0
#else /* _M_IX86_FP == 2 */
#define __FLT_EVAL_METHOD__ 2
#endif /* _M_IX86_FP != 2 */
#else /* ... */
#define __FLT_EVAL_METHOD__ 0
#endif /* !... */
#endif /* !__FLT_EVAL_METHOD__ */

#if __FLT_EVAL_METHOD__ < 0
#include "host.h"
#ifdef __x86_64__
#undef __FLT_EVAL_METHOD__
#define __FLT_EVAL_METHOD__ 0
#elif defined(__i386__)
#undef __FLT_EVAL_METHOD__
#define __FLT_EVAL_METHOD__ 2
#endif /* ... */
#endif /* __FLT_EVAL_METHOD__ < 0 */

#ifndef __FLT_DECIMAL_DIG__
#define __FLT_DECIMAL_DIG__        9
#endif /* !__FLT_DECIMAL_DIG__ */
#ifndef __FLT_DENORM_MIN__
#define __FLT_DENORM_MIN__         1.40129846432481707092e-45F
#endif /* !__FLT_DENORM_MIN__ */
#ifndef __FLT_DIG__
#define __FLT_DIG__                6
#endif /* !__FLT_DIG__ */
#ifndef __FLT_EPSILON__
#define __FLT_EPSILON__            1.19209289550781250000e-7F
#endif /* !__FLT_EPSILON__ */
#ifndef __FLT_HAS_DENORM__
#define __FLT_HAS_DENORM__         1
#endif /* !__FLT_HAS_DENORM__ */
#ifndef __FLT_HAS_INFINITY__
#define __FLT_HAS_INFINITY__       1
#endif /* !__FLT_HAS_INFINITY__ */
#ifndef __FLT_HAS_QUIET_NAN__
#define __FLT_HAS_QUIET_NAN__      1
#endif /* !__FLT_HAS_QUIET_NAN__ */
#ifndef __FLT_MANT_DIG__
#define __FLT_MANT_DIG__           24
#endif /* !__FLT_MANT_DIG__ */
#ifndef __FLT_MAX_10_EXP__
#define __FLT_MAX_10_EXP__         38
#endif /* !__FLT_MAX_10_EXP__ */
#ifndef __FLT_MAX_EXP__
#define __FLT_MAX_EXP__            128
#endif /* !__FLT_MAX_EXP__ */
#ifndef __FLT_MAX__
#define __FLT_MAX__                3.40282346638528859812e+38F
#endif /* !__FLT_MAX__ */
#ifndef __FLT_MIN_10_EXP__
#define __FLT_MIN_10_EXP__       (-37)
#endif /* !__FLT_MIN_10_EXP__ */
#ifndef __FLT_MIN_EXP__
#define __FLT_MIN_EXP__          (-125)
#endif /* !__FLT_MIN_EXP__ */
#ifndef __FLT_MIN__
#define __FLT_MIN__                1.17549435082228750797e-38F
#endif /* !__FLT_MIN__ */
#ifndef __FLT_RADIX__
#define __FLT_RADIX__              2
#endif /* !__FLT_RADIX__ */

#ifndef __DBL_DECIMAL_DIG__
#define __DBL_DECIMAL_DIG__        17
#endif /* !__DBL_DECIMAL_DIG__ */
#ifndef __DBL_DENORM_MIN__
#define __DBL_DENORM_MIN__         __CCAST(double)4.94065645841246544177e-324L
#endif /* !__DBL_DENORM_MIN__ */
#ifndef __DBL_DIG__
#define __DBL_DIG__                15
#endif /* !__DBL_DIG__ */
#ifndef __DBL_EPSILON__
#define __DBL_EPSILON__            __CCAST(double)2.22044604925031308085e-16L
#endif /* !__DBL_EPSILON__ */
#ifndef __DBL_HAS_DENORM__
#define __DBL_HAS_DENORM__         1
#endif /* !__DBL_HAS_DENORM__ */
#ifndef __DBL_HAS_INFINITY__
#define __DBL_HAS_INFINITY__       1
#endif /* !__DBL_HAS_INFINITY__ */
#ifndef __DBL_HAS_QUIET_NAN__
#define __DBL_HAS_QUIET_NAN__      1
#endif /* !__DBL_HAS_QUIET_NAN__ */
#ifndef __DBL_MANT_DIG__
#define __DBL_MANT_DIG__           53
#endif /* !__DBL_MANT_DIG__ */
#ifndef __DBL_MAX_10_EXP__
#define __DBL_MAX_10_EXP__         308
#endif /* !__DBL_MAX_10_EXP__ */
#ifndef __DBL_MAX_EXP__
#define __DBL_MAX_EXP__            1024
#endif /* !__DBL_MAX_EXP__ */
#ifndef __DBL_MIN__
#define __DBL_MIN__                __CCAST(double)2.22507385850720138309e-308L
#endif /* !__DBL_MIN__ */
#ifndef __DBL_MAX__
#define __DBL_MAX__                __CCAST(double)1.79769313486231570815e+308L
#endif /* !__DBL_MAX__ */
#ifndef __DBL_MIN_10_EXP__
#define __DBL_MIN_10_EXP__       (-307)
#endif /* !__DBL_MIN_10_EXP__ */
#ifndef __DBL_MIN_EXP__
#define __DBL_MIN_EXP__          (-1021)
#endif /* !__DBL_MIN_EXP__ */

#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifdef _MSC_VER
#define __LDBL_DENORM_MIN__        __DBL_DENORM_MIN__
#define __LDBL_DIG__               __DBL_DIG__
#define __LDBL_EPSILON__           __DBL_EPSILON__
#define __LDBL_HAS_DENORM__        __DBL_HAS_DENORM__
#define __LDBL_HAS_INFINITY__      __DBL_HAS_INFINITY__
#define __LDBL_HAS_QUIET_NAN__     __DBL_HAS_QUIET_NAN__
#define __LDBL_MANT_DIG__          __DBL_MANT_DIG__
#define __LDBL_MAX_10_EXP__        __DBL_MAX_10_EXP__
#define __LDBL_MAX_EXP__           __DBL_MAX_EXP__
#define __LDBL_MAX__               __DBL_MAX__
#define __LDBL_MIN_10_EXP__        __DBL_MIN_10_EXP__
#define __LDBL_MIN_EXP__           __DBL_MIN_EXP__
#define __LDBL_MIN__               __DBL_MIN__
#else /* _MSC_VER */
#ifndef __LDBL_DENORM_MIN__
#define __LDBL_DENORM_MIN__        3.64519953188247460253e-4951L
#endif /* !__LDBL_DENORM_MIN__ */
#ifndef __LDBL_DIG__
#define __LDBL_DIG__               18
#endif /* !__LDBL_DIG__ */
#ifndef __LDBL_EPSILON__
#define __LDBL_EPSILON__           1.08420217248550443401e-19L
#endif /* !__LDBL_EPSILON__ */
#ifndef __LDBL_HAS_DENORM__
#define __LDBL_HAS_DENORM__        1
#endif /* !__LDBL_HAS_DENORM__ */
#ifndef __LDBL_HAS_INFINITY__
#define __LDBL_HAS_INFINITY__      1
#endif /* !__LDBL_HAS_INFINITY__ */
#ifndef __LDBL_HAS_QUIET_NAN__
#define __LDBL_HAS_QUIET_NAN__     1
#endif /* !__LDBL_HAS_QUIET_NAN__ */
#ifndef __LDBL_MANT_DIG__
#define __LDBL_MANT_DIG__          64
#endif /* !__LDBL_MANT_DIG__ */
#ifndef __LDBL_MAX_10_EXP__
#define __LDBL_MAX_10_EXP__        4932
#endif /* !__LDBL_MAX_10_EXP__ */
#ifndef __LDBL_MAX_EXP__
#define __LDBL_MAX_EXP__           16384
#endif /* !__LDBL_MAX_EXP__ */
#ifndef __LDBL_MAX__
#define __LDBL_MAX__               1.18973149535723176502e+4932L
#endif /* !__LDBL_MAX__ */
#ifndef __LDBL_MIN_10_EXP__
#define __LDBL_MIN_10_EXP__        (-4931)
#endif /* !__LDBL_MIN_10_EXP__ */
#ifndef __LDBL_MIN_EXP__
#define __LDBL_MIN_EXP__           (-16381)
#endif /* !__LDBL_MIN_EXP__ */
#ifndef __LDBL_MIN__
#define __LDBL_MIN__               3.36210314311209350626e-4932L
#endif /* !__LDBL_MIN__ */
#endif /* !_MSC_VER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#ifndef __DECIMAL_DIG__
#ifdef _MSC_VER
#define __DECIMAL_DIG__            10
#else /* _MSC_VER */
#define __DECIMAL_DIG__            21
#endif /* !_MSC_VER */
#endif /* !__DECIMAL_DIG__ */
#ifndef __DEC_EVAL_METHOD__
#define __DEC_EVAL_METHOD__        2
#endif /* !__DEC_EVAL_METHOD__ */

#ifdef __STDC_WANT_DEC_FP__
#ifndef __DEC128_EPSILON__
#define __DEC128_EPSILON__         1E-33DL
#endif /* !__DEC128_EPSILON__ */
#ifndef __DEC128_MANT_DIG__
#define __DEC128_MANT_DIG__        34
#endif /* !__DEC128_MANT_DIG__ */
#ifndef __DEC128_MAX_EXP__
#define __DEC128_MAX_EXP__         6145
#endif /* !__DEC128_MAX_EXP__ */
#ifndef __DEC128_MAX__
#define __DEC128_MAX__             9.999999999999999999999999999999999E6144DL
#endif /* !__DEC128_MAX__ */
#ifndef __DEC128_MIN_EXP__
#define __DEC128_MIN_EXP__         (-6142)
#endif /* !__DEC128_MIN_EXP__ */
#ifndef __DEC128_MIN__
#define __DEC128_MIN__             1E-6143DL
#endif /* !__DEC128_MIN__ */
#ifndef __DEC128_SUBNORMAL_MIN__
#define __DEC128_SUBNORMAL_MIN__   0.000000000000000000000000000000001E-6143DL
#endif /* !__DEC128_SUBNORMAL_MIN__ */

#ifndef __DEC32_EPSILON__
#define __DEC32_EPSILON__          1E-6DF
#endif /* !__DEC32_EPSILON__ */
#ifndef __DEC32_MANT_DIG__
#define __DEC32_MANT_DIG__         7
#endif /* !__DEC32_MANT_DIG__ */
#ifndef __DEC32_MAX_EXP__
#define __DEC32_MAX_EXP__          97
#endif /* !__DEC32_MAX_EXP__ */
#ifndef __DEC32_MAX__
#define __DEC32_MAX__              9.999999E96DF
#endif /* !__DEC32_MAX__ */
#ifndef __DEC32_MIN_EXP__
#define __DEC32_MIN_EXP__          (-94)
#endif /* !__DEC32_MIN_EXP__ */
#ifndef __DEC32_MIN__
#define __DEC32_MIN__              1E-95DF
#endif /* !__DEC32_MIN__ */
#ifndef __DEC32_SUBNORMAL_MIN__
#define __DEC32_SUBNORMAL_MIN__    0.000001E-95DF
#endif /* !__DEC32_SUBNORMAL_MIN__ */

#ifndef __DEC64_EPSILON__
#define __DEC64_EPSILON__          1E-15DD
#endif /* !__DEC64_EPSILON__ */
#ifndef __DEC64_MANT_DIG__
#define __DEC64_MANT_DIG__         16
#endif /* !__DEC64_MANT_DIG__ */
#ifndef __DEC64_MAX_EXP__
#define __DEC64_MAX_EXP__          385
#endif /* !__DEC64_MAX_EXP__ */
#ifndef __DEC64_MAX__
#define __DEC64_MAX__              9.999999999999999E384DD
#endif /* !__DEC64_MAX__ */
#ifndef __DEC64_MIN_EXP__
#define __DEC64_MIN_EXP__          (-382)
#endif /* !__DEC64_MIN_EXP__ */
#ifndef __DEC64_MIN__
#define __DEC64_MIN__              1E-383DD
#endif /* !__DEC64_MIN__ */
#ifndef __DEC64_SUBNORMAL_MIN__
#define __DEC64_SUBNORMAL_MIN__    0.000000000000001E-383DD
#endif /* !__DEC64_SUBNORMAL_MIN__ */
#endif /* __STDC_WANT_DEC_FP__ */

#endif /* !__GUARD_HYBRID_FLOATCORE_H */
