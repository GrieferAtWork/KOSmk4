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
#ifndef __GUARD_HYBRID_FLOATCORE_H
#define __GUARD_HYBRID_FLOATCORE_H 1

#include "../__stdinc.h"
//#include "typecore.h"

#ifndef __FLT_EVAL_METHOD__
#if defined(_M_FP_FAST)
#   define __FLT_EVAL_METHOD__ (-1)
#elif defined(_M_IX86)
#if defined(_M_IX86_FP) && _M_IX86_FP == 2
#   define __FLT_EVAL_METHOD__   0
#else
#   define __FLT_EVAL_METHOD__   2
#endif
#else
#   define __FLT_EVAL_METHOD__   0
#endif
#endif /* !__FLT_EVAL_METHOD__ */

#ifndef __FLT_DECIMAL_DIG__
#define __FLT_DECIMAL_DIG__        9
#endif
#ifndef __FLT_DENORM_MIN__
#define __FLT_DENORM_MIN__         1.40129846432481707092e-45F
#endif
#ifndef __FLT_DIG__
#define __FLT_DIG__                6
#endif
#ifndef __FLT_EPSILON__
#define __FLT_EPSILON__            1.19209289550781250000e-7F
#endif
#ifndef __FLT_HAS_DENORM__
#define __FLT_HAS_DENORM__         1
#endif
#ifndef __FLT_HAS_INFINITY__
#define __FLT_HAS_INFINITY__       1
#endif
#ifndef __FLT_HAS_QUIET_NAN__
#define __FLT_HAS_QUIET_NAN__      1
#endif
#ifndef __FLT_MANT_DIG__
#define __FLT_MANT_DIG__           24
#endif
#ifndef __FLT_MAX_10_EXP__
#define __FLT_MAX_10_EXP__         38
#endif
#ifndef __FLT_MAX_EXP__
#define __FLT_MAX_EXP__            128
#endif
#ifndef __FLT_MAX__
#define __FLT_MAX__                3.40282346638528859812e+38F
#endif
#ifndef __FLT_MIN_10_EXP__
#define __FLT_MIN_10_EXP__       (-37)
#endif
#ifndef __FLT_MIN_EXP__
#define __FLT_MIN_EXP__          (-125)
#endif
#ifndef __FLT_MIN__
#define __FLT_MIN__                1.17549435082228750797e-38F
#endif
#ifndef __FLT_RADIX__
#define __FLT_RADIX__              2
#endif

#ifndef __DBL_DECIMAL_DIG__
#define __DBL_DECIMAL_DIG__        17
#endif
#ifndef __DBL_DENORM_MIN__
#define __DBL_DENORM_MIN__       ((double)4.94065645841246544177e-324L)
#endif
#ifndef __DBL_DIG__
#define __DBL_DIG__                15
#endif
#ifndef __DBL_EPSILON__
#define __DBL_EPSILON__          ((double)2.22044604925031308085e-16L)
#endif
#ifndef __DBL_HAS_DENORM__
#define __DBL_HAS_DENORM__         1
#endif
#ifndef __DBL_HAS_INFINITY__
#define __DBL_HAS_INFINITY__       1
#endif
#ifndef __DBL_HAS_QUIET_NAN__
#define __DBL_HAS_QUIET_NAN__      1
#endif
#ifndef __DBL_MANT_DIG__
#define __DBL_MANT_DIG__           53
#endif
#ifndef __DBL_MAX_10_EXP__
#define __DBL_MAX_10_EXP__         308
#endif
#ifndef __DBL_MAX_EXP__
#define __DBL_MAX_EXP__            1024
#endif
#ifndef __DBL_MIN__
#define __DBL_MIN__              ((double)2.22507385850720138309e-308L)
#endif
#ifndef __DBL_MAX__
#define __DBL_MAX__              ((double)1.79769313486231570815e+308L)
#endif
#ifndef __DBL_MIN_10_EXP__
#define __DBL_MIN_10_EXP__       (-307)
#endif
#ifndef __DBL_MIN_EXP__
#define __DBL_MIN_EXP__          (-1021)
#endif

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
#else
#ifndef __LDBL_DENORM_MIN__
#define __LDBL_DENORM_MIN__        3.64519953188247460253e-4951L
#endif
#ifndef __LDBL_DIG__
#define __LDBL_DIG__               18
#endif
#ifndef __LDBL_EPSILON__
#define __LDBL_EPSILON__           1.08420217248550443401e-19L
#endif
#ifndef __LDBL_HAS_DENORM__
#define __LDBL_HAS_DENORM__        1
#endif
#ifndef __LDBL_HAS_INFINITY__
#define __LDBL_HAS_INFINITY__      1
#endif
#ifndef __LDBL_HAS_QUIET_NAN__
#define __LDBL_HAS_QUIET_NAN__     1
#endif
#ifndef __LDBL_MANT_DIG__
#define __LDBL_MANT_DIG__          64
#endif
#ifndef __LDBL_MAX_10_EXP__
#define __LDBL_MAX_10_EXP__        4932
#endif
#ifndef __LDBL_MAX_EXP__
#define __LDBL_MAX_EXP__           16384
#endif
#ifndef __LDBL_MAX__
#define __LDBL_MAX__               1.18973149535723176502e+4932L
#endif
#ifndef __LDBL_MIN_10_EXP__
#define __LDBL_MIN_10_EXP__      (-4931)
#endif
#ifndef __LDBL_MIN_EXP__
#define __LDBL_MIN_EXP__         (-16381)
#endif
#ifndef __LDBL_MIN__
#define __LDBL_MIN__               3.36210314311209350626e-4932L
#endif
#endif
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#ifndef __DECIMAL_DIG__
#ifdef _MSC_VER
#define __DECIMAL_DIG__            10
#else
#define __DECIMAL_DIG__            21
#endif
#endif /* !__DECIMAL_DIG__ */
#ifndef __DEC_EVAL_METHOD__
#define __DEC_EVAL_METHOD__        2
#endif

#ifdef __STDC_WANT_DEC_FP__
#ifndef __DEC128_EPSILON__
#define __DEC128_EPSILON__         1E-33DL
#endif
#ifndef __DEC128_MANT_DIG__
#define __DEC128_MANT_DIG__        34
#endif
#ifndef __DEC128_MAX_EXP__
#define __DEC128_MAX_EXP__         6145
#endif
#ifndef __DEC128_MAX__
#define __DEC128_MAX__             9.999999999999999999999999999999999E6144DL
#endif
#ifndef __DEC128_MIN_EXP__
#define __DEC128_MIN_EXP__       (-6142)
#endif
#ifndef __DEC128_MIN__
#define __DEC128_MIN__             1E-6143DL
#endif
#ifndef __DEC128_SUBNORMAL_MIN__
#define __DEC128_SUBNORMAL_MIN__   0.000000000000000000000000000000001E-6143DL
#endif

#ifndef __DEC32_EPSILON__
#define __DEC32_EPSILON__          1E-6DF
#endif
#ifndef __DEC32_MANT_DIG__
#define __DEC32_MANT_DIG__         7
#endif
#ifndef __DEC32_MAX_EXP__
#define __DEC32_MAX_EXP__          97
#endif
#ifndef __DEC32_MAX__
#define __DEC32_MAX__              9.999999E96DF
#endif
#ifndef __DEC32_MIN_EXP__
#define __DEC32_MIN_EXP__        (-94)
#endif
#ifndef __DEC32_MIN__
#define __DEC32_MIN__              1E-95DF
#endif
#ifndef __DEC32_SUBNORMAL_MIN__
#define __DEC32_SUBNORMAL_MIN__    0.000001E-95DF
#endif

#ifndef __DEC64_EPSILON__
#define __DEC64_EPSILON__          1E-15DD
#endif
#ifndef __DEC64_MANT_DIG__
#define __DEC64_MANT_DIG__         16
#endif
#ifndef __DEC64_MAX_EXP__
#define __DEC64_MAX_EXP__          385
#endif
#ifndef __DEC64_MAX__
#define __DEC64_MAX__              9.999999999999999E384DD
#endif
#ifndef __DEC64_MIN_EXP__
#define __DEC64_MIN_EXP__        (-382)
#endif
#ifndef __DEC64_MIN__
#define __DEC64_MIN__              1E-383DD
#endif
#ifndef __DEC64_SUBNORMAL_MIN__
#define __DEC64_SUBNORMAL_MIN__    0.000000000000001E-383DD
#endif
#endif /* __STDC_WANT_DEC_FP__ */

#endif /* !__GUARD_HYBRID_FLOATCORE_H */
