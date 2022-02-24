/* HASH CRC-32:0x41e1a761 */
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
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/math.h) */
/* (#) Portability: DJGPP         (/include/math.h) */
/* (#) Portability: GNU C Library (/math/math.h) */
/* (#) Portability: MSVC          (/include/math.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/math.h) */
/* (#) Portability: NetBSD        (/include/math.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/math.h) */
/* (#) Portability: OpenBSD       (/include/math.h) */
/* (#) Portability: OpenSolaris   (/usr/src/lib/libbc/inc/include/math.h) */
/* (#) Portability: Windows Kits  (/ucrt/math.h) */
/* (#) Portability: diet libc     (/include/math.h) */
/* (#) Portability: libc4/5       (/include/math.h) */
/* (#) Portability: libc6         (/include/math.h) */
/* (#) Portability: musl libc     (/include/math.h) */
/* (#) Portability: uClibc        (/include/math.h) */
#ifndef _MATH_H
#define _MATH_H 1

#ifdef _CXX_STDONLY_CMATH
#ifdef __CXX_SYSTEM_HEADER
#undef _MATH_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "math.h" after "cmath" */
#ifndef __NO_FPU
#if defined(__CRT_HAVE_acos) || defined(__CRT_HAVE___acos)
__NAMESPACE_STD_USING(acos)
#endif /* __CRT_HAVE_acos || __CRT_HAVE___acos */
#if defined(__CRT_HAVE_asin) || defined(__CRT_HAVE___asin)
__NAMESPACE_STD_USING(asin)
#endif /* __CRT_HAVE_asin || __CRT_HAVE___asin */
#include <ieee754.h>
#if defined(__CRT_HAVE_atan) || defined(__CRT_HAVE___atan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(atan)
#endif /* __CRT_HAVE_atan || __CRT_HAVE___atan || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(atan2)
#endif /* __CRT_HAVE_atan2 || __CRT_HAVE___atan2 || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos)
__NAMESPACE_STD_USING(cos)
#endif /* __CRT_HAVE_cos || __CRT_HAVE___cos */
#if defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)
__NAMESPACE_STD_USING(sin)
#endif /* __CRT_HAVE_sin || __CRT_HAVE___sin */
#if defined(__CRT_HAVE_tan) || defined(__CRT_HAVE___tan)
__NAMESPACE_STD_USING(tan)
#endif /* __CRT_HAVE_tan || __CRT_HAVE___tan */
#if defined(__CRT_HAVE_acosf) || defined(__CRT_HAVE___acosf) || defined(__CRT_HAVE_acos) || defined(__CRT_HAVE___acos)
__NAMESPACE_STD_USING(acosf)
#endif /* __CRT_HAVE_acosf || __CRT_HAVE___acosf || __CRT_HAVE_acos || __CRT_HAVE___acos */
#if defined(__CRT_HAVE_asinf) || defined(__CRT_HAVE___asinf) || defined(__CRT_HAVE_asin) || defined(__CRT_HAVE___asin)
__NAMESPACE_STD_USING(asinf)
#endif /* __CRT_HAVE_asinf || __CRT_HAVE___asinf || __CRT_HAVE_asin || __CRT_HAVE___asin */
#if defined(__CRT_HAVE_atanf) || defined(__CRT_HAVE___atanf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_atan) || defined(__CRT_HAVE___atan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(atanf)
#endif /* __CRT_HAVE_atanf || __CRT_HAVE___atanf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_atan || __CRT_HAVE___atan || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_atan2f) || defined(__CRT_HAVE___atan2f) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(atan2f)
#endif /* __CRT_HAVE_atan2f || __CRT_HAVE___atan2f || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_atan2 || __CRT_HAVE___atan2 || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_cosf) || defined(__CRT_HAVE___cosf) || defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos)
__NAMESPACE_STD_USING(cosf)
#endif /* __CRT_HAVE_cosf || __CRT_HAVE___cosf || __CRT_HAVE_cos || __CRT_HAVE___cos */
#if defined(__CRT_HAVE_sinf) || defined(__CRT_HAVE___sinf) || defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)
__NAMESPACE_STD_USING(sinf)
#endif /* __CRT_HAVE_sinf || __CRT_HAVE___sinf || __CRT_HAVE_sin || __CRT_HAVE___sin */
#if defined(__CRT_HAVE_tanf) || defined(__CRT_HAVE___tanf) || defined(__CRT_HAVE_tan) || defined(__CRT_HAVE___tan)
__NAMESPACE_STD_USING(tanf)
#endif /* __CRT_HAVE_tanf || __CRT_HAVE___tanf || __CRT_HAVE_tan || __CRT_HAVE___tan */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if defined(__CRT_HAVE_acosl) || defined(__CRT_HAVE___acosl) || defined(__CRT_HAVE_acos) || defined(__CRT_HAVE___acos)
__NAMESPACE_STD_USING(acosl)
#endif /* __CRT_HAVE_acosl || __CRT_HAVE___acosl || __CRT_HAVE_acos || __CRT_HAVE___acos */
#if defined(__CRT_HAVE_asinl) || defined(__CRT_HAVE___asinl) || defined(__CRT_HAVE_asin) || defined(__CRT_HAVE___asin)
__NAMESPACE_STD_USING(asinl)
#endif /* __CRT_HAVE_asinl || __CRT_HAVE___asinl || __CRT_HAVE_asin || __CRT_HAVE___asin */
#if defined(__CRT_HAVE_atanl) || defined(__CRT_HAVE___atanl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_atan) || defined(__CRT_HAVE___atan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(atanl)
#endif /* __CRT_HAVE_atanl || __CRT_HAVE___atanl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_atan || __CRT_HAVE___atan || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_atan2l) || defined(__CRT_HAVE___atan2l) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(atan2l)
#endif /* __CRT_HAVE_atan2l || __CRT_HAVE___atan2l || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_atan2 || __CRT_HAVE___atan2 || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_cosl) || defined(__CRT_HAVE___cosl) || defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos)
__NAMESPACE_STD_USING(cosl)
#endif /* __CRT_HAVE_cosl || __CRT_HAVE___cosl || __CRT_HAVE_cos || __CRT_HAVE___cos */
#if defined(__CRT_HAVE_sinl) || defined(__CRT_HAVE___sinl) || defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)
__NAMESPACE_STD_USING(sinl)
#endif /* __CRT_HAVE_sinl || __CRT_HAVE___sinl || __CRT_HAVE_sin || __CRT_HAVE___sin */
#if defined(__CRT_HAVE_tanl) || defined(__CRT_HAVE___tanl) || defined(__CRT_HAVE_tan) || defined(__CRT_HAVE___tan)
__NAMESPACE_STD_USING(tanl)
#endif /* __CRT_HAVE_tanl || __CRT_HAVE___tanl || __CRT_HAVE_tan || __CRT_HAVE___tan */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#if defined(__CRT_HAVE_cosh) || defined(__CRT_HAVE___cosh)
__NAMESPACE_STD_USING(cosh)
#endif /* __CRT_HAVE_cosh || __CRT_HAVE___cosh */
#if defined(__CRT_HAVE_sinh) || defined(__CRT_HAVE___sinh)
__NAMESPACE_STD_USING(sinh)
#endif /* __CRT_HAVE_sinh || __CRT_HAVE___sinh */
#if defined(__CRT_HAVE_tanh) || defined(__CRT_HAVE___tanh)
__NAMESPACE_STD_USING(tanh)
#endif /* __CRT_HAVE_tanh || __CRT_HAVE___tanh */
#if defined(__CRT_HAVE_coshf) || defined(__CRT_HAVE___coshf) || defined(__CRT_HAVE_cosh) || defined(__CRT_HAVE___cosh)
__NAMESPACE_STD_USING(coshf)
#endif /* __CRT_HAVE_coshf || __CRT_HAVE___coshf || __CRT_HAVE_cosh || __CRT_HAVE___cosh */
#if defined(__CRT_HAVE_sinhf) || defined(__CRT_HAVE___sinhf) || defined(__CRT_HAVE_sinh) || defined(__CRT_HAVE___sinh)
__NAMESPACE_STD_USING(sinhf)
#endif /* __CRT_HAVE_sinhf || __CRT_HAVE___sinhf || __CRT_HAVE_sinh || __CRT_HAVE___sinh */
#if defined(__CRT_HAVE_tanhf) || defined(__CRT_HAVE___tanhf) || defined(__CRT_HAVE_tanh) || defined(__CRT_HAVE___tanh)
__NAMESPACE_STD_USING(tanhf)
#endif /* __CRT_HAVE_tanhf || __CRT_HAVE___tanhf || __CRT_HAVE_tanh || __CRT_HAVE___tanh */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if defined(__CRT_HAVE_coshl) || defined(__CRT_HAVE___coshl) || defined(__CRT_HAVE_cosh) || defined(__CRT_HAVE___cosh)
__NAMESPACE_STD_USING(coshl)
#endif /* __CRT_HAVE_coshl || __CRT_HAVE___coshl || __CRT_HAVE_cosh || __CRT_HAVE___cosh */
#if defined(__CRT_HAVE_sinhl) || defined(__CRT_HAVE___sinhl) || defined(__CRT_HAVE_sinh) || defined(__CRT_HAVE___sinh)
__NAMESPACE_STD_USING(sinhl)
#endif /* __CRT_HAVE_sinhl || __CRT_HAVE___sinhl || __CRT_HAVE_sinh || __CRT_HAVE___sinh */
#if defined(__CRT_HAVE_tanhl) || defined(__CRT_HAVE___tanhl) || defined(__CRT_HAVE_tanh) || defined(__CRT_HAVE___tanh)
__NAMESPACE_STD_USING(tanhl)
#endif /* __CRT_HAVE_tanhl || __CRT_HAVE___tanhl || __CRT_HAVE_tanh || __CRT_HAVE___tanh */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#if defined(__CRT_HAVE_acosh) || defined(__CRT_HAVE___acosh)
__NAMESPACE_STD_USING(acosh)
#endif /* __CRT_HAVE_acosh || __CRT_HAVE___acosh */
#if defined(__CRT_HAVE_asinh) || defined(__CRT_HAVE___asinh)
__NAMESPACE_STD_USING(asinh)
#endif /* __CRT_HAVE_asinh || __CRT_HAVE___asinh */
#if defined(__CRT_HAVE_atanh) || defined(__CRT_HAVE___atanh)
__NAMESPACE_STD_USING(atanh)
#endif /* __CRT_HAVE_atanh || __CRT_HAVE___atanh */
#if defined(__CRT_HAVE_acoshf) || defined(__CRT_HAVE___acoshf) || defined(__CRT_HAVE_acosh) || defined(__CRT_HAVE___acosh)
__NAMESPACE_STD_USING(acoshf)
#endif /* __CRT_HAVE_acoshf || __CRT_HAVE___acoshf || __CRT_HAVE_acosh || __CRT_HAVE___acosh */
#if defined(__CRT_HAVE_asinhf) || defined(__CRT_HAVE___asinhf) || defined(__CRT_HAVE_asinh) || defined(__CRT_HAVE___asinh)
__NAMESPACE_STD_USING(asinhf)
#endif /* __CRT_HAVE_asinhf || __CRT_HAVE___asinhf || __CRT_HAVE_asinh || __CRT_HAVE___asinh */
#if defined(__CRT_HAVE_atanhf) || defined(__CRT_HAVE___atanhf) || defined(__CRT_HAVE_atanh) || defined(__CRT_HAVE___atanh)
__NAMESPACE_STD_USING(atanhf)
#endif /* __CRT_HAVE_atanhf || __CRT_HAVE___atanhf || __CRT_HAVE_atanh || __CRT_HAVE___atanh */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if defined(__CRT_HAVE_acoshl) || defined(__CRT_HAVE___acoshl) || defined(__CRT_HAVE_acosh) || defined(__CRT_HAVE___acosh)
__NAMESPACE_STD_USING(acoshl)
#endif /* __CRT_HAVE_acoshl || __CRT_HAVE___acoshl || __CRT_HAVE_acosh || __CRT_HAVE___acosh */
#if defined(__CRT_HAVE_asinhl) || defined(__CRT_HAVE___asinhl) || defined(__CRT_HAVE_asinh) || defined(__CRT_HAVE___asinh)
__NAMESPACE_STD_USING(asinhl)
#endif /* __CRT_HAVE_asinhl || __CRT_HAVE___asinhl || __CRT_HAVE_asinh || __CRT_HAVE___asinh */
#if defined(__CRT_HAVE_atanhl) || defined(__CRT_HAVE___atanhl) || defined(__CRT_HAVE_atanh) || defined(__CRT_HAVE___atanh)
__NAMESPACE_STD_USING(atanhl)
#endif /* __CRT_HAVE_atanhl || __CRT_HAVE___atanhl || __CRT_HAVE_atanh || __CRT_HAVE___atanh */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */
#if defined(__CRT_HAVE_exp) || defined(__CRT_HAVE___exp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(exp)
#endif /* __CRT_HAVE_exp || __CRT_HAVE___exp || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_frexp) || defined(__CRT_HAVE___frexp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(frexp)
#endif /* __CRT_HAVE_frexp || __CRT_HAVE___frexp || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_ldexp) || defined(__CRT_HAVE___ldexp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(ldexp)
#endif /* __CRT_HAVE_ldexp || __CRT_HAVE___ldexp || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log)
__NAMESPACE_STD_USING(log)
#endif /* __CRT_HAVE_log || __CRT_HAVE___log */
#if defined(__CRT_HAVE_log10) || defined(__CRT_HAVE___log10)
__NAMESPACE_STD_USING(log10)
#endif /* __CRT_HAVE_log10 || __CRT_HAVE___log10 */
#if defined(__CRT_HAVE_modf) || defined(__CRT_HAVE___modf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(modf)
#endif /* __CRT_HAVE_modf || __CRT_HAVE___modf || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_expf) || defined(__CRT_HAVE___expf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_exp) || defined(__CRT_HAVE___exp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(expf)
#endif /* __CRT_HAVE_expf || __CRT_HAVE___expf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_exp || __CRT_HAVE___exp || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_frexpf) || defined(__CRT_HAVE___frexpf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_frexp) || defined(__CRT_HAVE___frexp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(frexpf)
#endif /* __CRT_HAVE_frexpf || __CRT_HAVE___frexpf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_frexp || __CRT_HAVE___frexp || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_ldexpf) || defined(__CRT_HAVE___ldexpf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_ldexp) || defined(__CRT_HAVE___ldexp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(ldexpf)
#endif /* __CRT_HAVE_ldexpf || __CRT_HAVE___ldexpf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_ldexp || __CRT_HAVE___ldexp || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_logf) || defined(__CRT_HAVE___logf) || defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log)
__NAMESPACE_STD_USING(logf)
#endif /* __CRT_HAVE_logf || __CRT_HAVE___logf || __CRT_HAVE_log || __CRT_HAVE___log */
#if defined(__CRT_HAVE_log10f) || defined(__CRT_HAVE___log10f) || defined(__CRT_HAVE_log10) || defined(__CRT_HAVE___log10)
__NAMESPACE_STD_USING(log10f)
#endif /* __CRT_HAVE_log10f || __CRT_HAVE___log10f || __CRT_HAVE_log10 || __CRT_HAVE___log10 */
#if defined(__CRT_HAVE_modff) || defined(__CRT_HAVE___modff) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_modf) || defined(__CRT_HAVE___modf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(modff)
#endif /* __CRT_HAVE_modff || __CRT_HAVE___modff || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_modf || __CRT_HAVE___modf || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if defined(__CRT_HAVE_expl) || defined(__CRT_HAVE___expl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_exp) || defined(__CRT_HAVE___exp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(expl)
#endif /* __CRT_HAVE_expl || __CRT_HAVE___expl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_exp || __CRT_HAVE___exp || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_frexpl) || defined(__CRT_HAVE___frexpl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_frexp) || defined(__CRT_HAVE___frexp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(frexpl)
#endif /* __CRT_HAVE_frexpl || __CRT_HAVE___frexpl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_frexp || __CRT_HAVE___frexp || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_ldexpl) || defined(__CRT_HAVE___ldexpl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_ldexp) || defined(__CRT_HAVE___ldexp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(ldexpl)
#endif /* __CRT_HAVE_ldexpl || __CRT_HAVE___ldexpl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_ldexp || __CRT_HAVE___ldexp || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_logl) || defined(__CRT_HAVE___logl) || defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log)
__NAMESPACE_STD_USING(logl)
#endif /* __CRT_HAVE_logl || __CRT_HAVE___logl || __CRT_HAVE_log || __CRT_HAVE___log */
#if defined(__CRT_HAVE_log10l) || defined(__CRT_HAVE___log10l) || defined(__CRT_HAVE_log10) || defined(__CRT_HAVE___log10)
__NAMESPACE_STD_USING(log10l)
#endif /* __CRT_HAVE_log10l || __CRT_HAVE___log10l || __CRT_HAVE_log10 || __CRT_HAVE___log10 */
#if defined(__CRT_HAVE_modfl) || defined(__CRT_HAVE___modfl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_modf) || defined(__CRT_HAVE___modf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(modfl)
#endif /* __CRT_HAVE_modfl || __CRT_HAVE___modfl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_modf || __CRT_HAVE___modf || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#if defined(__CRT_HAVE_expm1) || defined(__CRT_HAVE___expm1) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(expm1)
#endif /* __CRT_HAVE_expm1 || __CRT_HAVE___expm1 || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_log1p) || defined(__CRT_HAVE___log1p)
__NAMESPACE_STD_USING(log1p)
#endif /* __CRT_HAVE_log1p || __CRT_HAVE___log1p */
#if defined(__CRT_HAVE_logb) || defined(__CRT_HAVE___logb) || defined(__CRT_HAVE__logb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(logb)
#endif /* __CRT_HAVE_logb || __CRT_HAVE___logb || __CRT_HAVE__logb || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_expm1f) || defined(__CRT_HAVE___expm1f) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_expm1) || defined(__CRT_HAVE___expm1) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(expm1f)
#endif /* __CRT_HAVE_expm1f || __CRT_HAVE___expm1f || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_expm1 || __CRT_HAVE___expm1 || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_log1pf) || defined(__CRT_HAVE___log1pf) || defined(__CRT_HAVE_log1p) || defined(__CRT_HAVE___log1p)
__NAMESPACE_STD_USING(log1pf)
#endif /* __CRT_HAVE_log1pf || __CRT_HAVE___log1pf || __CRT_HAVE_log1p || __CRT_HAVE___log1p */
#if defined(__CRT_HAVE_logbf) || defined(__CRT_HAVE___logbf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_logb) || defined(__CRT_HAVE___logb) || defined(__CRT_HAVE__logb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(logbf)
#endif /* __CRT_HAVE_logbf || __CRT_HAVE___logbf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_logb || __CRT_HAVE___logb || __CRT_HAVE__logb || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if defined(__CRT_HAVE_expm1l) || defined(__CRT_HAVE___expm1l) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_expm1) || defined(__CRT_HAVE___expm1) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(expm1l)
#endif /* __CRT_HAVE_expm1l || __CRT_HAVE___expm1l || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_expm1 || __CRT_HAVE___expm1 || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_log1pl) || defined(__CRT_HAVE___log1pl) || defined(__CRT_HAVE_log1p) || defined(__CRT_HAVE___log1p)
__NAMESPACE_STD_USING(log1pl)
#endif /* __CRT_HAVE_log1pl || __CRT_HAVE___log1pl || __CRT_HAVE_log1p || __CRT_HAVE___log1p */
#if defined(__CRT_HAVE_logbl) || defined(__CRT_HAVE___logbl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_logb) || defined(__CRT_HAVE___logb) || defined(__CRT_HAVE__logb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(logbl)
#endif /* __CRT_HAVE_logbl || __CRT_HAVE___logbl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_logb || __CRT_HAVE___logb || __CRT_HAVE__logb || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */
#ifdef __USE_ISOC99
#if defined(__CRT_HAVE_exp2) || defined(__CRT_HAVE___exp2)
__NAMESPACE_STD_USING(exp2)
#endif /* __CRT_HAVE_exp2 || __CRT_HAVE___exp2 */
#if defined(__CRT_HAVE_log2) || defined(__CRT_HAVE___log2)
__NAMESPACE_STD_USING(log2)
#endif /* __CRT_HAVE_log2 || __CRT_HAVE___log2 */
#if defined(__CRT_HAVE_exp2f) || defined(__CRT_HAVE___exp2f) || defined(__CRT_HAVE_exp2) || defined(__CRT_HAVE___exp2)
__NAMESPACE_STD_USING(exp2f)
#endif /* __CRT_HAVE_exp2f || __CRT_HAVE___exp2f || __CRT_HAVE_exp2 || __CRT_HAVE___exp2 */
#if defined(__CRT_HAVE_log2f) || defined(__CRT_HAVE___log2f) || defined(__CRT_HAVE_log2) || defined(__CRT_HAVE___log2)
__NAMESPACE_STD_USING(log2f)
#endif /* __CRT_HAVE_log2f || __CRT_HAVE___log2f || __CRT_HAVE_log2 || __CRT_HAVE___log2 */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if defined(__CRT_HAVE_exp2l) || defined(__CRT_HAVE___exp2l) || defined(__CRT_HAVE_exp2) || defined(__CRT_HAVE___exp2)
__NAMESPACE_STD_USING(exp2l)
#endif /* __CRT_HAVE_exp2l || __CRT_HAVE___exp2l || __CRT_HAVE_exp2 || __CRT_HAVE___exp2 */
#if defined(__CRT_HAVE_log2l) || defined(__CRT_HAVE___log2l) || defined(__CRT_HAVE_log2) || defined(__CRT_HAVE___log2)
__NAMESPACE_STD_USING(log2l)
#endif /* __CRT_HAVE_log2l || __CRT_HAVE___log2l || __CRT_HAVE_log2 || __CRT_HAVE___log2 */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */
#if defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(pow)
#endif /* __CRT_HAVE_pow || __CRT_HAVE___pow || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(sqrt)
#endif /* __CRT_HAVE_sqrt || __CRT_HAVE___sqrt || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_powf) || defined(__CRT_HAVE___powf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(powf)
#endif /* __CRT_HAVE_powf || __CRT_HAVE___powf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_pow || __CRT_HAVE___pow || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_sqrtf) || defined(__CRT_HAVE___sqrtf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(sqrtf)
#endif /* __CRT_HAVE_sqrtf || __CRT_HAVE___sqrtf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_sqrt || __CRT_HAVE___sqrt || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if defined(__CRT_HAVE_powl) || defined(__CRT_HAVE___powl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(powl)
#endif /* __CRT_HAVE_powl || __CRT_HAVE___powl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_pow || __CRT_HAVE___pow || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_sqrtl) || defined(__CRT_HAVE___sqrtl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(sqrtl)
#endif /* __CRT_HAVE_sqrtl || __CRT_HAVE___sqrtl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_sqrt || __CRT_HAVE___sqrt || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
#if defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE___hypot)
__NAMESPACE_STD_USING(hypot)
#endif /* __CRT_HAVE_hypot || __CRT_HAVE___hypot */
#if defined(__CRT_HAVE_hypotf) || defined(__CRT_HAVE___hypotf) || defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE___hypot)
__NAMESPACE_STD_USING(hypotf)
#endif /* __CRT_HAVE_hypotf || __CRT_HAVE___hypotf || __CRT_HAVE_hypot || __CRT_HAVE___hypot */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if defined(__CRT_HAVE_hypotl) || defined(__CRT_HAVE___hypotl) || defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE___hypot)
__NAMESPACE_STD_USING(hypotl)
#endif /* __CRT_HAVE_hypotl || __CRT_HAVE___hypotl || __CRT_HAVE_hypot || __CRT_HAVE___hypot */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN || __USE_ISOC99 */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#if defined(__CRT_HAVE_cbrt) || defined(__CRT_HAVE___cbrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(cbrt)
#endif /* __CRT_HAVE_cbrt || __CRT_HAVE___cbrt || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_cbrtf) || defined(__CRT_HAVE___cbrtf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_cbrt) || defined(__CRT_HAVE___cbrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(cbrtf)
#endif /* __CRT_HAVE_cbrtf || __CRT_HAVE___cbrtf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_cbrt || __CRT_HAVE___cbrt || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if defined(__CRT_HAVE_cbrtl) || defined(__CRT_HAVE___cbrtl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_cbrt) || defined(__CRT_HAVE___cbrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(cbrtl)
#endif /* __CRT_HAVE_cbrtl || __CRT_HAVE___cbrtl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_cbrt || __CRT_HAVE___cbrt || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */
__NAMESPACE_STD_USING(ceil)
__NAMESPACE_STD_USING(fabs)
__NAMESPACE_STD_USING(floor)
#if defined(__CRT_HAVE_fmod) || defined(__CRT_HAVE___fmod) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(fmod)
#endif /* __CRT_HAVE_fmod || __CRT_HAVE___fmod || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
__NAMESPACE_STD_USING(ceilf)
__NAMESPACE_STD_USING(fabsf)
__NAMESPACE_STD_USING(floorf)
#if defined(__CRT_HAVE_fmodf) || defined(__CRT_HAVE___fmodf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_fmod) || defined(__CRT_HAVE___fmod) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(fmodf)
#endif /* __CRT_HAVE_fmodf || __CRT_HAVE___fmodf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_fmod || __CRT_HAVE___fmod || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#ifdef __COMPILER_HAVE_LONGDOUBLE
__NAMESPACE_STD_USING(ceill)
__NAMESPACE_STD_USING(fabsl)
__NAMESPACE_STD_USING(floorl)
#if defined(__CRT_HAVE_fmodl) || defined(__CRT_HAVE___fmodl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_fmod) || defined(__CRT_HAVE___fmod) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(fmodl)
#endif /* __CRT_HAVE_fmodl || __CRT_HAVE___fmodl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_fmod || __CRT_HAVE___fmod || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#ifdef __USE_ISOC99
__NAMESPACE_STD_USING(copysign)
#if defined(__CRT_HAVE_nan) || defined(__CRT_HAVE___nan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(nan)
#endif /* __CRT_HAVE_nan || __CRT_HAVE___nan || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
__NAMESPACE_STD_USING(copysignf)
#if defined(__CRT_HAVE_nanf) || defined(__CRT_HAVE___nanf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_nan) || defined(__CRT_HAVE___nan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(nanf)
#endif /* __CRT_HAVE_nanf || __CRT_HAVE___nanf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_nan || __CRT_HAVE___nan || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#ifdef __COMPILER_HAVE_LONGDOUBLE
__NAMESPACE_STD_USING(copysignl)
#if defined(__CRT_HAVE_nanl) || defined(__CRT_HAVE___nanl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_nan) || defined(__CRT_HAVE___nan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(nanl)
#endif /* __CRT_HAVE_nanl || __CRT_HAVE___nanl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_nan || __CRT_HAVE___nan || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */
#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
#if defined(__CRT_HAVE_erf) || defined(__CRT_HAVE___erf)
__NAMESPACE_STD_USING(erf)
#endif /* __CRT_HAVE_erf || __CRT_HAVE___erf */
#if defined(__CRT_HAVE_erfc) || defined(__CRT_HAVE___erfc)
__NAMESPACE_STD_USING(erfc)
#endif /* __CRT_HAVE_erfc || __CRT_HAVE___erfc */
#if defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE_gamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma)
__NAMESPACE_STD_USING(lgamma)
#endif /* __CRT_HAVE_lgamma || __CRT_HAVE_gamma || __CRT_HAVE___lgamma || __CRT_HAVE___gamma */
#if defined(__CRT_HAVE_erff) || defined(__CRT_HAVE___erff) || defined(__CRT_HAVE_erf) || defined(__CRT_HAVE___erf)
__NAMESPACE_STD_USING(erff)
#endif /* __CRT_HAVE_erff || __CRT_HAVE___erff || __CRT_HAVE_erf || __CRT_HAVE___erf */
#if defined(__CRT_HAVE_erfcf) || defined(__CRT_HAVE___erfcf) || defined(__CRT_HAVE_erfc) || defined(__CRT_HAVE___erfc)
__NAMESPACE_STD_USING(erfcf)
#endif /* __CRT_HAVE_erfcf || __CRT_HAVE___erfcf || __CRT_HAVE_erfc || __CRT_HAVE___erfc */
#if defined(__CRT_HAVE_lgammaf) || defined(__CRT_HAVE_gammaf) || defined(__CRT_HAVE___lgammaf) || defined(__CRT_HAVE___gammaf) || defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE_gamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma)
__NAMESPACE_STD_USING(lgammaf)
#endif /* __CRT_HAVE_lgammaf || __CRT_HAVE_gammaf || __CRT_HAVE___lgammaf || __CRT_HAVE___gammaf || __CRT_HAVE_lgamma || __CRT_HAVE_gamma || __CRT_HAVE___lgamma || __CRT_HAVE___gamma */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if defined(__CRT_HAVE_erfl) || defined(__CRT_HAVE___erfl) || defined(__CRT_HAVE_erf) || defined(__CRT_HAVE___erf)
__NAMESPACE_STD_USING(erfl)
#endif /* __CRT_HAVE_erfl || __CRT_HAVE___erfl || __CRT_HAVE_erf || __CRT_HAVE___erf */
#if defined(__CRT_HAVE_erfcl) || defined(__CRT_HAVE___erfcl) || defined(__CRT_HAVE_erfc) || defined(__CRT_HAVE___erfc)
__NAMESPACE_STD_USING(erfcl)
#endif /* __CRT_HAVE_erfcl || __CRT_HAVE___erfcl || __CRT_HAVE_erfc || __CRT_HAVE___erfc */
#if defined(__CRT_HAVE_lgammal) || defined(__CRT_HAVE_gammal) || defined(__CRT_HAVE___lgammal) || defined(__CRT_HAVE___gammal) || defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE_gamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma)
__NAMESPACE_STD_USING(lgammal)
#endif /* __CRT_HAVE_lgammal || __CRT_HAVE_gammal || __CRT_HAVE___lgammal || __CRT_HAVE___gammal || __CRT_HAVE_lgamma || __CRT_HAVE_gamma || __CRT_HAVE___lgamma || __CRT_HAVE___gamma */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN || __USE_ISOC99 */
#ifdef __USE_ISOC99
#if defined(__CRT_HAVE_tgamma) || defined(__CRT_HAVE___tgamma)
__NAMESPACE_STD_USING(tgamma)
#endif /* __CRT_HAVE_tgamma || __CRT_HAVE___tgamma */
#if defined(__CRT_HAVE_tgammaf) || defined(__CRT_HAVE___tgammaf) || defined(__CRT_HAVE_tgamma) || defined(__CRT_HAVE___tgamma)
__NAMESPACE_STD_USING(tgammaf)
#endif /* __CRT_HAVE_tgammaf || __CRT_HAVE___tgammaf || __CRT_HAVE_tgamma || __CRT_HAVE___tgamma */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if defined(__CRT_HAVE_tgammal) || defined(__CRT_HAVE___tgammal) || defined(__CRT_HAVE_tgamma) || defined(__CRT_HAVE___tgamma)
__NAMESPACE_STD_USING(tgammal)
#endif /* __CRT_HAVE_tgammal || __CRT_HAVE___tgammal || __CRT_HAVE_tgamma || __CRT_HAVE___tgamma */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#if defined(__CRT_HAVE_rint) || defined(__CRT_HAVE_nearbyint) || defined(__CRT_HAVE___rint) || defined(__CRT_HAVE___nearbyint) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(rint)
#endif /* __CRT_HAVE_rint || __CRT_HAVE_nearbyint || __CRT_HAVE___rint || __CRT_HAVE___nearbyint || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE___nexttoward) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(nextafter)
#endif /* __CRT_HAVE_nextafter || __CRT_HAVE_nexttoward || __CRT_HAVE___nextafter || __CRT_HAVE__nextafter || __CRT_HAVE___nexttoward || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE___drem) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(remainder)
#endif /* __CRT_HAVE_remainder || __CRT_HAVE_drem || __CRT_HAVE___remainder || __CRT_HAVE___drem || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_ilogb) || defined(__CRT_HAVE___ilogb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(ilogb)
#endif /* __CRT_HAVE_ilogb || __CRT_HAVE___ilogb || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_rintf) || defined(__CRT_HAVE_nearbyintf) || defined(__CRT_HAVE___rintf) || defined(__CRT_HAVE___nearbyintf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE_nearbyint) || defined(__CRT_HAVE___rint) || defined(__CRT_HAVE___nearbyint) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(rintf)
#endif /* __CRT_HAVE_rintf || __CRT_HAVE_nearbyintf || __CRT_HAVE___rintf || __CRT_HAVE___nearbyintf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_rint || __CRT_HAVE_nearbyint || __CRT_HAVE___rint || __CRT_HAVE___nearbyint || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_nextafterf) || defined(__CRT_HAVE_nexttowardf) || defined(__CRT_HAVE___nextafterf) || defined(__CRT_HAVE___nexttowardf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE___nexttoward) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(nextafterf)
#endif /* __CRT_HAVE_nextafterf || __CRT_HAVE_nexttowardf || __CRT_HAVE___nextafterf || __CRT_HAVE___nexttowardf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_nextafter || __CRT_HAVE_nexttoward || __CRT_HAVE___nextafter || __CRT_HAVE__nextafter || __CRT_HAVE___nexttoward || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_remainderf) || defined(__CRT_HAVE_dremf) || defined(__CRT_HAVE___remainderf) || defined(__CRT_HAVE___dremf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE___drem) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(remainderf)
#endif /* __CRT_HAVE_remainderf || __CRT_HAVE_dremf || __CRT_HAVE___remainderf || __CRT_HAVE___dremf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_remainder || __CRT_HAVE_drem || __CRT_HAVE___remainder || __CRT_HAVE___drem || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_ilogbf) || defined(__CRT_HAVE___ilogbf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_ilogb) || defined(__CRT_HAVE___ilogb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(ilogbf)
#endif /* __CRT_HAVE_ilogbf || __CRT_HAVE___ilogbf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __CRT_HAVE_ilogb || __CRT_HAVE___ilogb || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if defined(__CRT_HAVE_rintl) || defined(__CRT_HAVE_nearbyintl) || defined(__CRT_HAVE___rintl) || defined(__CRT_HAVE___nearbyintl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE_nearbyint) || defined(__CRT_HAVE___rint) || defined(__CRT_HAVE___nearbyint) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(rintl)
#endif /* __CRT_HAVE_rintl || __CRT_HAVE_nearbyintl || __CRT_HAVE___rintl || __CRT_HAVE___nearbyintl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_rint || __CRT_HAVE_nearbyint || __CRT_HAVE___rint || __CRT_HAVE___nearbyint || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_nextafterl) || defined(__CRT_HAVE_nexttowardl) || defined(__CRT_HAVE___nextafterl) || defined(__CRT_HAVE___nexttowardl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE___nexttoward) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(nextafterl)
#endif /* __CRT_HAVE_nextafterl || __CRT_HAVE_nexttowardl || __CRT_HAVE___nextafterl || __CRT_HAVE___nexttowardl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_nextafter || __CRT_HAVE_nexttoward || __CRT_HAVE___nextafter || __CRT_HAVE__nextafter || __CRT_HAVE___nexttoward || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_remainderl) || defined(__CRT_HAVE_dreml) || defined(__CRT_HAVE___remainderl) || defined(__CRT_HAVE___dreml) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE___drem) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(remainderl)
#endif /* __CRT_HAVE_remainderl || __CRT_HAVE_dreml || __CRT_HAVE___remainderl || __CRT_HAVE___dreml || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_remainder || __CRT_HAVE_drem || __CRT_HAVE___remainder || __CRT_HAVE___drem || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_ilogbl) || defined(__CRT_HAVE___ilogbl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_ilogb) || defined(__CRT_HAVE___ilogb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(ilogbl)
#endif /* __CRT_HAVE_ilogbl || __CRT_HAVE___ilogbl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_ilogb || __CRT_HAVE___ilogb || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */
#ifdef __USE_ISOC99
#if defined(__CRT_HAVE_nextafterl) || defined(__CRT_HAVE_nexttowardl) || defined(__CRT_HAVE___nextafterl) || defined(__CRT_HAVE___nexttowardl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE___nexttoward) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(nexttoward)
#endif /* __CRT_HAVE_nextafterl || __CRT_HAVE_nexttowardl || __CRT_HAVE___nextafterl || __CRT_HAVE___nexttowardl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_nextafter || __CRT_HAVE_nexttoward || __CRT_HAVE___nextafter || __CRT_HAVE__nextafter || __CRT_HAVE___nexttoward || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#include <hybrid/typecore.h>
#if defined(__CRT_HAVE_scalbn) || defined(__CRT_HAVE___scalbn) || (defined(__CRT_HAVE_scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(scalbn)
#endif /* __CRT_HAVE_scalbn || __CRT_HAVE___scalbn || (__CRT_HAVE_scalbln && __SIZEOF_INT__ == __SIZEOF_LONG__) || (__CRT_HAVE___scalbln && __SIZEOF_INT__ == __SIZEOF_LONG__) || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_scalbln) || defined(__CRT_HAVE___scalbln) || (defined(__CRT_HAVE_scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(scalbln)
#endif /* __CRT_HAVE_scalbln || __CRT_HAVE___scalbln || (__CRT_HAVE_scalbn && __SIZEOF_INT__ == __SIZEOF_LONG__) || (__CRT_HAVE___scalbn && __SIZEOF_INT__ == __SIZEOF_LONG__) || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_nearbyint) || defined(__CRT_HAVE___nearbyint) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE___rint) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(nearbyint)
#endif /* __CRT_HAVE_nearbyint || __CRT_HAVE___nearbyint || __CRT_HAVE_rint || __CRT_HAVE___rint || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
__NAMESPACE_STD_USING(round)
__NAMESPACE_STD_USING(trunc)
#if defined(__CRT_HAVE_remquo) || defined(__CRT_HAVE___remquo)
__NAMESPACE_STD_USING(remquo)
#endif /* __CRT_HAVE_remquo || __CRT_HAVE___remquo */
__NAMESPACE_STD_USING(lrint)
__NAMESPACE_STD_USING(lround)
__NAMESPACE_STD_USING(fdim)
__NAMESPACE_STD_USING(fmax)
__NAMESPACE_STD_USING(fmin)
__NAMESPACE_STD_USING(fma)
#ifdef __COMPILER_HAVE_LONGLONG
__NAMESPACE_STD_USING(llrint)
__NAMESPACE_STD_USING(llround)
#endif /* __COMPILER_HAVE_LONGLONG */
#if defined(__CRT_HAVE_nexttowardf) || defined(__CRT_HAVE___nexttowardf) || ((defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)) && defined(__IEEE854_LONG_DOUBLE_TYPE__)) || defined(__CRT_HAVE_nextafterl) || defined(__CRT_HAVE_nexttowardl) || defined(__CRT_HAVE___nextafterl) || defined(__CRT_HAVE___nexttowardl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE___nexttoward) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(nexttowardf)
#endif /* __CRT_HAVE_nexttowardf || __CRT_HAVE___nexttowardf || ((__IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE754_DOUBLE_TYPE_IS_FLOAT__) && __IEEE854_LONG_DOUBLE_TYPE__) || __CRT_HAVE_nextafterl || __CRT_HAVE_nexttowardl || __CRT_HAVE___nextafterl || __CRT_HAVE___nexttowardl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_nextafter || __CRT_HAVE_nexttoward || __CRT_HAVE___nextafter || __CRT_HAVE__nextafter || __CRT_HAVE___nexttoward || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_scalbnf) || defined(__CRT_HAVE___scalbnf) || (defined(__CRT_HAVE_scalblnf) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalblnf) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_scalbn) || defined(__CRT_HAVE___scalbn) || (defined(__CRT_HAVE_scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(scalbnf)
#endif /* __CRT_HAVE_scalbnf || __CRT_HAVE___scalbnf || (__CRT_HAVE_scalblnf && __SIZEOF_INT__ == __SIZEOF_LONG__) || (__CRT_HAVE___scalblnf && __SIZEOF_INT__ == __SIZEOF_LONG__) || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_scalbn || __CRT_HAVE___scalbn || (__CRT_HAVE_scalbln && __SIZEOF_INT__ == __SIZEOF_LONG__) || (__CRT_HAVE___scalbln && __SIZEOF_INT__ == __SIZEOF_LONG__) || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_scalblnf) || defined(__CRT_HAVE___scalblnf) || (defined(__CRT_HAVE_scalbnf) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbnf) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_scalbln) || defined(__CRT_HAVE___scalbln) || (defined(__CRT_HAVE_scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(scalblnf)
#endif /* __CRT_HAVE_scalblnf || __CRT_HAVE___scalblnf || (__CRT_HAVE_scalbnf && __SIZEOF_INT__ == __SIZEOF_LONG__) || (__CRT_HAVE___scalbnf && __SIZEOF_INT__ == __SIZEOF_LONG__) || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_scalbln || __CRT_HAVE___scalbln || (__CRT_HAVE_scalbn && __SIZEOF_INT__ == __SIZEOF_LONG__) || (__CRT_HAVE___scalbn && __SIZEOF_INT__ == __SIZEOF_LONG__) || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_nearbyintf) || defined(__CRT_HAVE___nearbyintf) || defined(__CRT_HAVE_rintf) || defined(__CRT_HAVE___rintf) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
__NAMESPACE_STD_USING(nearbyintf)
#endif /* __CRT_HAVE_nearbyintf || __CRT_HAVE___nearbyintf || __CRT_HAVE_rintf || __CRT_HAVE___rintf || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
__NAMESPACE_STD_USING(roundf)
__NAMESPACE_STD_USING(truncf)
#if defined(__CRT_HAVE_remquof) || defined(__CRT_HAVE___remquof) || defined(__CRT_HAVE_remquo) || defined(__CRT_HAVE___remquo)
__NAMESPACE_STD_USING(remquof)
#endif /* __CRT_HAVE_remquof || __CRT_HAVE___remquof || __CRT_HAVE_remquo || __CRT_HAVE___remquo */
__NAMESPACE_STD_USING(lrintf)
__NAMESPACE_STD_USING(lroundf)
__NAMESPACE_STD_USING(fdimf)
__NAMESPACE_STD_USING(fmaxf)
__NAMESPACE_STD_USING(fminf)
__NAMESPACE_STD_USING(fmaf)
#ifdef __COMPILER_HAVE_LONGLONG
__NAMESPACE_STD_USING(llrintf)
__NAMESPACE_STD_USING(llroundf)
#endif /* __COMPILER_HAVE_LONGLONG */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if defined(__CRT_HAVE_nextafterl) || defined(__CRT_HAVE_nexttowardl) || defined(__CRT_HAVE___nextafterl) || defined(__CRT_HAVE___nexttowardl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE___nexttoward) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(nexttowardl)
#endif /* __CRT_HAVE_nextafterl || __CRT_HAVE_nexttowardl || __CRT_HAVE___nextafterl || __CRT_HAVE___nexttowardl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_nextafter || __CRT_HAVE_nexttoward || __CRT_HAVE___nextafter || __CRT_HAVE__nextafter || __CRT_HAVE___nexttoward || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_scalbnl) || defined(__CRT_HAVE___scalbnl) || (defined(__CRT_HAVE_scalblnl) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalblnl) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_scalbn) || defined(__CRT_HAVE___scalbn) || (defined(__CRT_HAVE_scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(scalbnl)
#endif /* __CRT_HAVE_scalbnl || __CRT_HAVE___scalbnl || (__CRT_HAVE_scalblnl && __SIZEOF_INT__ == __SIZEOF_LONG__) || (__CRT_HAVE___scalblnl && __SIZEOF_INT__ == __SIZEOF_LONG__) || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_scalbn || __CRT_HAVE___scalbn || (__CRT_HAVE_scalbln && __SIZEOF_INT__ == __SIZEOF_LONG__) || (__CRT_HAVE___scalbln && __SIZEOF_INT__ == __SIZEOF_LONG__) || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_scalblnl) || defined(__CRT_HAVE___scalblnl) || (defined(__CRT_HAVE_scalbnl) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbnl) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_scalbln) || defined(__CRT_HAVE___scalbln) || (defined(__CRT_HAVE_scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(scalblnl)
#endif /* __CRT_HAVE_scalblnl || __CRT_HAVE___scalblnl || (__CRT_HAVE_scalbnl && __SIZEOF_INT__ == __SIZEOF_LONG__) || (__CRT_HAVE___scalbnl && __SIZEOF_INT__ == __SIZEOF_LONG__) || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_scalbln || __CRT_HAVE___scalbln || (__CRT_HAVE_scalbn && __SIZEOF_INT__ == __SIZEOF_LONG__) || (__CRT_HAVE___scalbn && __SIZEOF_INT__ == __SIZEOF_LONG__) || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_nearbyintl) || defined(__CRT_HAVE___nearbyintl) || defined(__CRT_HAVE_rintl) || defined(__CRT_HAVE___rintl) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
__NAMESPACE_STD_USING(nearbyintl)
#endif /* __CRT_HAVE_nearbyintl || __CRT_HAVE___nearbyintl || __CRT_HAVE_rintl || __CRT_HAVE___rintl || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ */
__NAMESPACE_STD_USING(roundl)
__NAMESPACE_STD_USING(truncl)
#if defined(__CRT_HAVE_remquol) || defined(__CRT_HAVE___remquol) || defined(__CRT_HAVE_remquo) || defined(__CRT_HAVE___remquo)
__NAMESPACE_STD_USING(remquol)
#endif /* __CRT_HAVE_remquol || __CRT_HAVE___remquol || __CRT_HAVE_remquo || __CRT_HAVE___remquo */
__NAMESPACE_STD_USING(lrintl)
__NAMESPACE_STD_USING(lroundl)
__NAMESPACE_STD_USING(fdiml)
__NAMESPACE_STD_USING(fmaxl)
__NAMESPACE_STD_USING(fminl)
__NAMESPACE_STD_USING(fmal)
#ifdef __COMPILER_HAVE_LONGLONG
__NAMESPACE_STD_USING(llrintl)
__NAMESPACE_STD_USING(llroundl)
#endif /* __COMPILER_HAVE_LONGLONG */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */
#ifdef __std_fpclassify_defined
__NAMESPACE_STD_USING(fpclassify)
#endif /* __std_fpclassify_defined */
#ifdef __std_signbit_defined
__NAMESPACE_STD_USING(signbit)
#endif /* __std_signbit_defined */
#ifdef __std_isnormal_defined
__NAMESPACE_STD_USING(isnormal)
#endif /* __std_isnormal_defined */
#ifdef __std_isfinite_defined
__NAMESPACE_STD_USING(isfinite)
#endif /* __std_isfinite_defined */
#ifdef __std_isnan_defined
__NAMESPACE_STD_USING(isnan)
#endif /* __std_isnan_defined */
#ifdef __std_isinf_defined
__NAMESPACE_STD_USING(isinf)
#endif /* __std_isinf_defined */
#ifdef __std_isunordered_defined
__NAMESPACE_STD_USING(isunordered)
#endif /* __std_isunordered_defined */
#ifdef __std_isgreater_defined
__NAMESPACE_STD_USING(isgreater)
#endif /* __std_isgreater_defined */
#ifdef __std_isgreaterequal_defined
__NAMESPACE_STD_USING(isgreaterequal)
#endif /* __std_isgreaterequal_defined */
#ifdef __std_isless_defined
__NAMESPACE_STD_USING(isless)
#endif /* __std_isless_defined */
#ifdef __std_islessequal_defined
__NAMESPACE_STD_USING(islessequal)
#endif /* __std_islessequal_defined */
#ifdef __std_islessgreater_defined
__NAMESPACE_STD_USING(islessgreater)
#endif /* __std_islessgreater_defined */
#endif /* !__NO_FPU */
#undef _CXX_STDONLY_CMATH
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CMATH */
#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#ifndef __NO_FPU
#include <features.h>

#include <hybrid/typecore.h>
#include <hybrid/floatcore.h>

#include <bits/math-constants.h>
#include <bits/crt/math-vector.h>

#include <ieee754.h>

#ifdef __USE_ISOC99
#include <asm/crt/fp_type.h>  /* __FP_NAN, __FP_INFINITE, ... */
#include <bits/crt/mathdef.h> /* __FLT_EVAL_METHOD__, __FP_ILOGB0, __FP_ILOGBNAN */
#endif /* __USE_ISOC99 */

#ifdef __USE_MISC
#include <asm/crt/math-exception.h>
#include <asm/crt/math-libc_version.h>
#endif /* __USE_MISC */


/* Math constants (`_USE_MATH_DEFINES' is the DOS feature macro to expose these) */
#if defined(__USE_MISC) || defined(__USE_XOPEN) || defined(_USE_MATH_DEFINES)
#define M_E        2.7182818284590452354  /* e */
#define M_LOG2E    1.4426950408889634074  /* log_2 e */
#define M_LOG10E   0.43429448190325182765 /* log_10 e */
#define M_LN2      0.69314718055994530942 /* log_e 2 */
#define M_LN10     2.30258509299404568402 /* log_e 10 */
#define M_PI       3.14159265358979323846 /* pi */
#define M_PI_2     1.57079632679489661923 /* pi/2 */
#define M_PI_4     0.78539816339744830962 /* pi/4 */
#define M_1_PI     0.31830988618379067154 /* 1/pi */
#define M_2_PI     0.63661977236758134308 /* 2/pi */
#define M_2_SQRTPI 1.12837916709551257390 /* 2/sqrt(pi) */
#define M_SQRT2    1.41421356237309504880 /* sqrt(2) */
#define M_SQRT1_2  0.70710678118654752440 /* 1/sqrt(2) */
#endif /* __USE_MISC || __USE_XOPEN || _USE_MATH_DEFINES */

/* Math constants with long-double precision. */
#if defined(__USE_GNU) && defined(__COMPILER_HAVE_LONGDOUBLE)
#define M_El        2.718281828459045235360287471352662498L /* e */
#define M_LOG2El    1.442695040888963407359924681001892137L /* log_2 e */
#define M_LOG10El   0.434294481903251827651128918916605082L /* log_10 e */
#define M_LN2l      0.693147180559945309417232121458176568L /* log_e 2 */
#define M_LN10l     2.302585092994045684017991454684364208L /* log_e 10 */
#define M_PIl       3.141592653589793238462643383279502884L /* pi */
#define M_PI_2l     1.570796326794896619231321691639751442L /* pi/2 */
#define M_PI_4l     0.785398163397448309615660845819875721L /* pi/4 */
#define M_1_PIl     0.318309886183790671537767526745028724L /* 1/pi */
#define M_2_PIl     0.636619772367581343075535053490057448L /* 2/pi */
#define M_2_SQRTPIl 1.128379167095512573896158903121545172L /* 2/sqrt(pi) */
#define M_SQRT2l    1.414213562373095048801688724209698079L /* sqrt(2) */
#define M_SQRT1_2l  0.707106781186547524400844362104849039L /* 1/sqrt(2) */
#endif /* __USE_GNU && __COMPILER_HAVE_LONGDOUBLE */


#if !defined(HUGE_VAL) && defined(__HUGE_VAL)
#define HUGE_VAL __HUGE_VAL /* double HUGE_VAL; */
#endif /* !HUGE_VAL && __HUGE_VAL */

#ifdef __USE_ISOC99
#if !defined(HUGE_VALF) && defined(__HUGE_VALF)
#define HUGE_VALF __HUGE_VALF /* double HUGE_VALF; */
#endif /* !HUGE_VALF && __HUGE_VALF */

#if !defined(HUGE_VALL) && defined(__HUGE_VALL)
#define HUGE_VALL __HUGE_VALL /* double HUGE_VALL; */
#endif /* !HUGE_VALL && __HUGE_VALL */

#if !defined(INFINITY) && defined(__INFINITYF)
#define INFINITY __INFINITYF /* float INFINITY; */
#endif /* !INFINITY && __INFINITYF */

#if !defined(NAN) && defined(__NANF)
#define NAN __NANF /* float NAN; */
#endif /* !NAN && __NANF */

/* This value is returned by `ilogb(0)'. */
#ifdef __FP_ILOGB0
#define FP_ILOGB0 __FP_ILOGB0 /* int FP_ILOGB0; */
#endif /* __FP_ILOGB0 */

/* This value is returned by `ilogb(NAN)'. */
#ifdef __FP_ILOGBNAN
#define FP_ILOGBNAN __FP_ILOGBNAN /* int FP_ILOGBNAN; */
#endif /* __FP_ILOGBNAN */

/* Define if fma(x, y, z) is at least as ~fast~ as `x * y + z' */
#ifdef __FP_FAST_FMA
#define FP_FAST_FMA 1
#endif /* __FP_FAST_FMA */

/* Define if fmaf(x, y, z) is at least as ~fast~ as `x * y + z' */
#ifdef __FP_FAST_FMAF
#define FP_FAST_FMAF 1
#endif /* __FP_FAST_FMAF */

/* Define if fmal(x, y, z) is at least as ~fast~ as `x * y + z' */
#ifdef __FP_FAST_FMAL
#define FP_FAST_FMAL 1
#endif /* __FP_FAST_FMAL */

#endif /* __USE_ISOC99 */


#ifdef __CC__
__SYSDECL_BEGIN

__NAMESPACE_STD_BEGIN
#if __has_builtin(__builtin_acos) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acos)
/* Arc cosine of `x' */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,acos,(double __x),{ return __builtin_acos(__x); })
#elif defined(__CRT_HAVE_acos)
/* Arc cosine of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,acos,(double __x),(__x))
#elif defined(__CRT_HAVE___acos)
/* Arc cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,acos,(double __x),__acos,(__x))
#endif /* ... */
#if __has_builtin(__builtin_asin) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asin)
/* Arc sine of `x' */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,asin,(double __x),{ return __builtin_asin(__x); })
#elif defined(__CRT_HAVE_asin)
/* Arc sine of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,asin,(double __x),(__x))
#elif defined(__CRT_HAVE___asin)
/* Arc sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,asin,(double __x),__asin,(__x))
#endif /* ... */
#if __has_builtin(__builtin_atan) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan)
/* Arc tangent of `x' */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,atan,(double __x),{ return __builtin_atan(__x); })
#elif defined(__CRT_HAVE_atan)
/* Arc tangent of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,atan,(double __x),(__x))
#elif defined(__CRT_HAVE___atan)
/* Arc tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,atan,(double __x),__atan,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/atan.h>
__NAMESPACE_STD_BEGIN
/* Arc tangent of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(atan, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL atan)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atan))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_atan2) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan2)
/* Arc tangent of `y / x' */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,atan2,(double __y, double __x),{ return __builtin_atan2(__y, __x); })
#elif defined(__CRT_HAVE_atan2)
/* Arc tangent of `y / x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,atan2,(double __y, double __x),(__y,__x))
#elif defined(__CRT_HAVE___atan2)
/* Arc tangent of `y / x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,atan2,(double __y, double __x),__atan2,(__y,__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/atan2.h>
__NAMESPACE_STD_BEGIN
/* Arc tangent of `y / x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(atan2, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL atan2)(double __y, double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atan2))(__y, __x); })
#endif /* ... */
#if __has_builtin(__builtin_cos) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cos)
/* Cosine of `x' */
__CEIDECLARE(__ATTR_WUNUSED __DECL_SIMD_cos,double,__NOTHROW,cos,(double __x),{ return __builtin_cos(__x); })
#elif defined(__CRT_HAVE_cos)
/* Cosine of `x' */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_cos,double,__NOTHROW,cos,(double __x),(__x))
#elif defined(__CRT_HAVE___cos)
/* Cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cos,double,__NOTHROW,cos,(double __x),__cos,(__x))
#endif /* ... */
#if __has_builtin(__builtin_sin) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sin)
/* Sine of `x' */
__CEIDECLARE(__ATTR_WUNUSED __DECL_SIMD_sin,double,__NOTHROW,sin,(double __x),{ return __builtin_sin(__x); })
#elif defined(__CRT_HAVE_sin)
/* Sine of `x' */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_sin,double,__NOTHROW,sin,(double __x),(__x))
#elif defined(__CRT_HAVE___sin)
/* Sine of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sin,double,__NOTHROW,sin,(double __x),__sin,(__x))
#endif /* ... */
#if __has_builtin(__builtin_tan) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tan)
/* Tangent of `x' */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,tan,(double __x),{ return __builtin_tan(__x); })
#elif defined(__CRT_HAVE_tan)
/* Tangent of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,tan,(double __x),(__x))
#elif defined(__CRT_HAVE___tan)
/* Tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,tan,(double __x),__tan,(__x))
#endif /* ... */
#if __has_builtin(__builtin_acosf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acosf)
/* Arc cosine of `x' */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,acosf,(float __x),{ return __builtin_acosf(__x); })
#elif defined(__CRT_HAVE_acosf)
/* Arc cosine of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,acosf,(float __x),(__x))
#elif defined(__CRT_HAVE___acosf)
/* Arc cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,acosf,(float __x),__acosf,(__x))
#elif defined(__CRT_HAVE_acos) || defined(__CRT_HAVE___acos)
__NAMESPACE_STD_END
#include <libc/local/math/acosf.h>
__NAMESPACE_STD_BEGIN
/* Arc cosine of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(acosf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL acosf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(acosf))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_asinf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinf)
/* Arc sine of `x' */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,asinf,(float __x),{ return __builtin_asinf(__x); })
#elif defined(__CRT_HAVE_asinf)
/* Arc sine of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,asinf,(float __x),(__x))
#elif defined(__CRT_HAVE___asinf)
/* Arc sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,asinf,(float __x),__asinf,(__x))
#elif defined(__CRT_HAVE_asin) || defined(__CRT_HAVE___asin)
__NAMESPACE_STD_END
#include <libc/local/math/asinf.h>
__NAMESPACE_STD_BEGIN
/* Arc sine of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(asinf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL asinf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asinf))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_atanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanf)
/* Arc tangent of `x' */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,atanf,(float __x),{ return __builtin_atanf(__x); })
#elif defined(__CRT_HAVE_atanf)
/* Arc tangent of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,atanf,(float __x),(__x))
#elif defined(__CRT_HAVE___atanf)
/* Arc tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,atanf,(float __x),__atanf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_atan) || defined(__CRT_HAVE___atan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/atanf.h>
__NAMESPACE_STD_BEGIN
/* Arc tangent of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(atanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL atanf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atanf))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_atan2f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan2f)
/* Arc tangent of `y / x' */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,atan2f,(float __y, float __x),{ return __builtin_atan2f(__y, __x); })
#elif defined(__CRT_HAVE_atan2f)
/* Arc tangent of `y / x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,atan2f,(float __y, float __x),(__y,__x))
#elif defined(__CRT_HAVE___atan2f)
/* Arc tangent of `y / x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,atan2f,(float __y, float __x),__atan2f,(__y,__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/atan2f.h>
__NAMESPACE_STD_BEGIN
/* Arc tangent of `y / x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(atan2f, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL atan2f)(float __y, float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atan2f))(__y, __x); })
#endif /* ... */
#if __has_builtin(__builtin_cosf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cosf)
/* Cosine of `x' */
__CEIDECLARE(__ATTR_WUNUSED __DECL_SIMD_cosf,float,__NOTHROW,cosf,(float __x),{ return __builtin_cosf(__x); })
#elif defined(__CRT_HAVE_cosf)
/* Cosine of `x' */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_cosf,float,__NOTHROW,cosf,(float __x),(__x))
#elif defined(__CRT_HAVE___cosf)
/* Cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cosf,float,__NOTHROW,cosf,(float __x),__cosf,(__x))
#elif defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos)
__NAMESPACE_STD_END
#include <libc/local/math/cosf.h>
__NAMESPACE_STD_BEGIN
/* Cosine of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(cosf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_cosf float __NOTHROW(__LIBCCALL cosf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cosf))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_sinf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinf)
/* Sine of `x' */
__CEIDECLARE(__ATTR_WUNUSED __DECL_SIMD_sinf,float,__NOTHROW,sinf,(float __x),{ return __builtin_sinf(__x); })
#elif defined(__CRT_HAVE_sinf)
/* Sine of `x' */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_sinf,float,__NOTHROW,sinf,(float __x),(__x))
#elif defined(__CRT_HAVE___sinf)
/* Sine of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sinf,float,__NOTHROW,sinf,(float __x),__sinf,(__x))
#elif defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)
__NAMESPACE_STD_END
#include <libc/local/math/sinf.h>
__NAMESPACE_STD_BEGIN
/* Sine of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(sinf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_sinf float __NOTHROW(__LIBCCALL sinf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sinf))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_tanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanf)
/* Tangent of `x' */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,tanf,(float __x),{ return __builtin_tanf(__x); })
#elif defined(__CRT_HAVE_tanf)
/* Tangent of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,tanf,(float __x),(__x))
#elif defined(__CRT_HAVE___tanf)
/* Tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,tanf,(float __x),__tanf,(__x))
#elif defined(__CRT_HAVE_tan) || defined(__CRT_HAVE___tan)
__NAMESPACE_STD_END
#include <libc/local/math/tanf.h>
__NAMESPACE_STD_BEGIN
/* Tangent of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(tanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL tanf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tanf))(__x); })
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_acosl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acosl)
/* Arc cosine of `x' */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acosl,(__LONGDOUBLE __x),{ return __builtin_acosl(__x); })
#elif defined(__CRT_HAVE_acosl)
/* Arc cosine of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acosl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___acosl)
/* Arc cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acosl,(__LONGDOUBLE __x),__acosl,(__x))
#elif defined(__CRT_HAVE_acos) || defined(__CRT_HAVE___acos)
__NAMESPACE_STD_END
#include <libc/local/math/acosl.h>
__NAMESPACE_STD_BEGIN
/* Arc cosine of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(acosl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL acosl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(acosl))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_asinl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinl)
/* Arc sine of `x' */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asinl,(__LONGDOUBLE __x),{ return __builtin_asinl(__x); })
#elif defined(__CRT_HAVE_asinl)
/* Arc sine of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asinl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___asinl)
/* Arc sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asinl,(__LONGDOUBLE __x),__asinl,(__x))
#elif defined(__CRT_HAVE_asin) || defined(__CRT_HAVE___asin)
__NAMESPACE_STD_END
#include <libc/local/math/asinl.h>
__NAMESPACE_STD_BEGIN
/* Arc sine of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(asinl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL asinl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asinl))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_atanl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanl)
/* Arc tangent of `x' */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atanl,(__LONGDOUBLE __x),{ return __builtin_atanl(__x); })
#elif defined(__CRT_HAVE_atanl)
/* Arc tangent of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atanl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___atanl)
/* Arc tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atanl,(__LONGDOUBLE __x),__atanl,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_atan) || defined(__CRT_HAVE___atan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/atanl.h>
__NAMESPACE_STD_BEGIN
/* Arc tangent of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(atanl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL atanl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atanl))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_atan2l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan2l)
/* Arc tangent of `y / x' */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atan2l,(__LONGDOUBLE __y, __LONGDOUBLE __x),{ return __builtin_atan2l(__y, __x); })
#elif defined(__CRT_HAVE_atan2l)
/* Arc tangent of `y / x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atan2l,(__LONGDOUBLE __y, __LONGDOUBLE __x),(__y,__x))
#elif defined(__CRT_HAVE___atan2l)
/* Arc tangent of `y / x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atan2l,(__LONGDOUBLE __y, __LONGDOUBLE __x),__atan2l,(__y,__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/atan2l.h>
__NAMESPACE_STD_BEGIN
/* Arc tangent of `y / x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(atan2l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL atan2l)(__LONGDOUBLE __y, __LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atan2l))(__y, __x); })
#endif /* ... */
#if __has_builtin(__builtin_cosl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cosl)
/* Cosine of `x' */
__CEIDECLARE(__ATTR_WUNUSED __DECL_SIMD_cosl,__LONGDOUBLE,__NOTHROW,cosl,(__LONGDOUBLE __x),{ return __builtin_cosl(__x); })
#elif defined(__CRT_HAVE_cosl)
/* Cosine of `x' */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_cosl,__LONGDOUBLE,__NOTHROW,cosl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___cosl)
/* Cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cosl,__LONGDOUBLE,__NOTHROW,cosl,(__LONGDOUBLE __x),__cosl,(__x))
#elif defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos)
__NAMESPACE_STD_END
#include <libc/local/math/cosl.h>
__NAMESPACE_STD_BEGIN
/* Cosine of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(cosl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_cosl __LONGDOUBLE __NOTHROW(__LIBCCALL cosl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cosl))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_sinl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinl)
/* Sine of `x' */
__CEIDECLARE(__ATTR_WUNUSED __DECL_SIMD_sinl,__LONGDOUBLE,__NOTHROW,sinl,(__LONGDOUBLE __x),{ return __builtin_sinl(__x); })
#elif defined(__CRT_HAVE_sinl)
/* Sine of `x' */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_sinl,__LONGDOUBLE,__NOTHROW,sinl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___sinl)
/* Sine of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sinl,__LONGDOUBLE,__NOTHROW,sinl,(__LONGDOUBLE __x),__sinl,(__x))
#elif defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)
__NAMESPACE_STD_END
#include <libc/local/math/sinl.h>
__NAMESPACE_STD_BEGIN
/* Sine of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(sinl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_sinl __LONGDOUBLE __NOTHROW(__LIBCCALL sinl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sinl))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_tanl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanl)
/* Tangent of `x' */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tanl,(__LONGDOUBLE __x),{ return __builtin_tanl(__x); })
#elif defined(__CRT_HAVE_tanl)
/* Tangent of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tanl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___tanl)
/* Tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tanl,(__LONGDOUBLE __x),__tanl,(__x))
#elif defined(__CRT_HAVE_tan) || defined(__CRT_HAVE___tan)
__NAMESPACE_STD_END
#include <libc/local/math/tanl.h>
__NAMESPACE_STD_BEGIN
/* Tangent of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(tanl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL tanl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tanl))(__x); })
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

/* Hyperbolic functions. */
#if __has_builtin(__builtin_cosh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cosh)
/* Hyperbolic cosine of `x' */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,cosh,(double __x),{ return __builtin_cosh(__x); })
#elif defined(__CRT_HAVE_cosh)
/* Hyperbolic cosine of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,cosh,(double __x),(__x))
#elif defined(__CRT_HAVE___cosh)
/* Hyperbolic cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,cosh,(double __x),__cosh,(__x))
#endif /* ... */
#if __has_builtin(__builtin_sinh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinh)
/* Hyperbolic sine of `x' */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,sinh,(double __x),{ return __builtin_sinh(__x); })
#elif defined(__CRT_HAVE_sinh)
/* Hyperbolic sine of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,sinh,(double __x),(__x))
#elif defined(__CRT_HAVE___sinh)
/* Hyperbolic sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,sinh,(double __x),__sinh,(__x))
#endif /* ... */
#if __has_builtin(__builtin_tanh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanh)
/* Hyperbolic tangent of `x' */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,tanh,(double __x),{ return __builtin_tanh(__x); })
#elif defined(__CRT_HAVE_tanh)
/* Hyperbolic tangent of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,tanh,(double __x),(__x))
#elif defined(__CRT_HAVE___tanh)
/* Hyperbolic tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,tanh,(double __x),__tanh,(__x))
#endif /* ... */
#if __has_builtin(__builtin_coshf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_coshf)
/* Hyperbolic cosine of `x' */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,coshf,(float __x),{ return __builtin_coshf(__x); })
#elif defined(__CRT_HAVE_coshf)
/* Hyperbolic cosine of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,coshf,(float __x),(__x))
#elif defined(__CRT_HAVE___coshf)
/* Hyperbolic cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,coshf,(float __x),__coshf,(__x))
#elif defined(__CRT_HAVE_cosh) || defined(__CRT_HAVE___cosh)
__NAMESPACE_STD_END
#include <libc/local/math/coshf.h>
__NAMESPACE_STD_BEGIN
/* Hyperbolic cosine of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(coshf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL coshf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(coshf))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_sinhf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinhf)
/* Hyperbolic sine of `x' */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,sinhf,(float __x),{ return __builtin_sinhf(__x); })
#elif defined(__CRT_HAVE_sinhf)
/* Hyperbolic sine of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,sinhf,(float __x),(__x))
#elif defined(__CRT_HAVE___sinhf)
/* Hyperbolic sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,sinhf,(float __x),__sinhf,(__x))
#elif defined(__CRT_HAVE_sinh) || defined(__CRT_HAVE___sinh)
__NAMESPACE_STD_END
#include <libc/local/math/sinhf.h>
__NAMESPACE_STD_BEGIN
/* Hyperbolic sine of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(sinhf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL sinhf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sinhf))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_tanhf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanhf)
/* Hyperbolic tangent of `x' */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,tanhf,(float __x),{ return __builtin_tanhf(__x); })
#elif defined(__CRT_HAVE_tanhf)
/* Hyperbolic tangent of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,tanhf,(float __x),(__x))
#elif defined(__CRT_HAVE___tanhf)
/* Hyperbolic tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,tanhf,(float __x),__tanhf,(__x))
#elif defined(__CRT_HAVE_tanh) || defined(__CRT_HAVE___tanh)
__NAMESPACE_STD_END
#include <libc/local/math/tanhf.h>
__NAMESPACE_STD_BEGIN
/* Hyperbolic tangent of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(tanhf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL tanhf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tanhf))(__x); })
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_coshl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_coshl)
/* Hyperbolic cosine of `x' */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,coshl,(__LONGDOUBLE __x),{ return __builtin_coshl(__x); })
#elif defined(__CRT_HAVE_coshl)
/* Hyperbolic cosine of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,coshl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___coshl)
/* Hyperbolic cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,coshl,(__LONGDOUBLE __x),__coshl,(__x))
#elif defined(__CRT_HAVE_cosh) || defined(__CRT_HAVE___cosh)
__NAMESPACE_STD_END
#include <libc/local/math/coshl.h>
__NAMESPACE_STD_BEGIN
/* Hyperbolic cosine of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(coshl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL coshl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(coshl))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_sinhl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinhl)
/* Hyperbolic sine of `x' */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sinhl,(__LONGDOUBLE __x),{ return __builtin_sinhl(__x); })
#elif defined(__CRT_HAVE_sinhl)
/* Hyperbolic sine of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sinhl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___sinhl)
/* Hyperbolic sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sinhl,(__LONGDOUBLE __x),__sinhl,(__x))
#elif defined(__CRT_HAVE_sinh) || defined(__CRT_HAVE___sinh)
__NAMESPACE_STD_END
#include <libc/local/math/sinhl.h>
__NAMESPACE_STD_BEGIN
/* Hyperbolic sine of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(sinhl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL sinhl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sinhl))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_tanhl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanhl)
/* Hyperbolic tangent of `x' */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tanhl,(__LONGDOUBLE __x),{ return __builtin_tanhl(__x); })
#elif defined(__CRT_HAVE_tanhl)
/* Hyperbolic tangent of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tanhl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___tanhl)
/* Hyperbolic tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tanhl,(__LONGDOUBLE __x),__tanhl,(__x))
#elif defined(__CRT_HAVE_tanh) || defined(__CRT_HAVE___tanh)
__NAMESPACE_STD_END
#include <libc/local/math/tanhl.h>
__NAMESPACE_STD_BEGIN
/* Hyperbolic tangent of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(tanhl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL tanhl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tanhl))(__x); })
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#if __has_builtin(__builtin_acosh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acosh)
/* Hyperbolic arc cosine of `x' */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,acosh,(double __x),{ return __builtin_acosh(__x); })
#elif defined(__CRT_HAVE_acosh)
/* Hyperbolic arc cosine of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,acosh,(double __x),(__x))
#elif defined(__CRT_HAVE___acosh)
/* Hyperbolic arc cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,acosh,(double __x),__acosh,(__x))
#endif /* ... */
#if __has_builtin(__builtin_asinh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinh)
/* Hyperbolic arc sine of `x' */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,asinh,(double __x),{ return __builtin_asinh(__x); })
#elif defined(__CRT_HAVE_asinh)
/* Hyperbolic arc sine of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,asinh,(double __x),(__x))
#elif defined(__CRT_HAVE___asinh)
/* Hyperbolic arc sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,asinh,(double __x),__asinh,(__x))
#endif /* ... */
#if __has_builtin(__builtin_atanh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanh)
/* Hyperbolic arc tangent of `x' */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,atanh,(double __x),{ return __builtin_atanh(__x); })
#elif defined(__CRT_HAVE_atanh)
/* Hyperbolic arc tangent of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,atanh,(double __x),(__x))
#elif defined(__CRT_HAVE___atanh)
/* Hyperbolic arc tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,atanh,(double __x),__atanh,(__x))
#endif /* ... */
#if __has_builtin(__builtin_acoshf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acoshf)
/* Hyperbolic arc cosine of `x' */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,acoshf,(float __x),{ return __builtin_acoshf(__x); })
#elif defined(__CRT_HAVE_acoshf)
/* Hyperbolic arc cosine of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,acoshf,(float __x),(__x))
#elif defined(__CRT_HAVE___acoshf)
/* Hyperbolic arc cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,acoshf,(float __x),__acoshf,(__x))
#elif defined(__CRT_HAVE_acosh) || defined(__CRT_HAVE___acosh)
__NAMESPACE_STD_END
#include <libc/local/math/acoshf.h>
__NAMESPACE_STD_BEGIN
/* Hyperbolic arc cosine of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(acoshf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL acoshf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(acoshf))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_asinhf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinhf)
/* Hyperbolic arc sine of `x' */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,asinhf,(float __x),{ return __builtin_asinhf(__x); })
#elif defined(__CRT_HAVE_asinhf)
/* Hyperbolic arc sine of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,asinhf,(float __x),(__x))
#elif defined(__CRT_HAVE___asinhf)
/* Hyperbolic arc sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,asinhf,(float __x),__asinhf,(__x))
#elif defined(__CRT_HAVE_asinh) || defined(__CRT_HAVE___asinh)
__NAMESPACE_STD_END
#include <libc/local/math/asinhf.h>
__NAMESPACE_STD_BEGIN
/* Hyperbolic arc sine of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(asinhf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL asinhf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asinhf))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_atanhf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanhf)
/* Hyperbolic arc tangent of `x' */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,atanhf,(float __x),{ return __builtin_atanhf(__x); })
#elif defined(__CRT_HAVE_atanhf)
/* Hyperbolic arc tangent of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,atanhf,(float __x),(__x))
#elif defined(__CRT_HAVE___atanhf)
/* Hyperbolic arc tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,atanhf,(float __x),__atanhf,(__x))
#elif defined(__CRT_HAVE_atanh) || defined(__CRT_HAVE___atanh)
__NAMESPACE_STD_END
#include <libc/local/math/atanhf.h>
__NAMESPACE_STD_BEGIN
/* Hyperbolic arc tangent of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(atanhf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL atanhf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atanhf))(__x); })
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_acoshl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acoshl)
/* Hyperbolic arc cosine of `x' */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acoshl,(__LONGDOUBLE __x),{ return __builtin_acoshl(__x); })
#elif defined(__CRT_HAVE_acoshl)
/* Hyperbolic arc cosine of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acoshl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___acoshl)
/* Hyperbolic arc cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acoshl,(__LONGDOUBLE __x),__acoshl,(__x))
#elif defined(__CRT_HAVE_acosh) || defined(__CRT_HAVE___acosh)
__NAMESPACE_STD_END
#include <libc/local/math/acoshl.h>
__NAMESPACE_STD_BEGIN
/* Hyperbolic arc cosine of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(acoshl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL acoshl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(acoshl))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_asinhl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinhl)
/* Hyperbolic arc sine of `x' */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asinhl,(__LONGDOUBLE __x),{ return __builtin_asinhl(__x); })
#elif defined(__CRT_HAVE_asinhl)
/* Hyperbolic arc sine of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asinhl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___asinhl)
/* Hyperbolic arc sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asinhl,(__LONGDOUBLE __x),__asinhl,(__x))
#elif defined(__CRT_HAVE_asinh) || defined(__CRT_HAVE___asinh)
__NAMESPACE_STD_END
#include <libc/local/math/asinhl.h>
__NAMESPACE_STD_BEGIN
/* Hyperbolic arc sine of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(asinhl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL asinhl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asinhl))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_atanhl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanhl)
/* Hyperbolic arc tangent of `x' */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atanhl,(__LONGDOUBLE __x),{ return __builtin_atanhl(__x); })
#elif defined(__CRT_HAVE_atanhl)
/* Hyperbolic arc tangent of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atanhl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___atanhl)
/* Hyperbolic arc tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atanhl,(__LONGDOUBLE __x),__atanhl,(__x))
#elif defined(__CRT_HAVE_atanh) || defined(__CRT_HAVE___atanh)
__NAMESPACE_STD_END
#include <libc/local/math/atanhl.h>
__NAMESPACE_STD_BEGIN
/* Hyperbolic arc tangent of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(atanhl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL atanhl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atanhl))(__x); })
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

/* Exponential and logarithmic functions. */
#if __has_builtin(__builtin_exp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp)
/* Exponential function of `x' */
__CEIDECLARE(__ATTR_WUNUSED __DECL_SIMD_exp,double,__NOTHROW,exp,(double __x),{ return __builtin_exp(__x); })
#elif defined(__CRT_HAVE_exp)
/* Exponential function of `x' */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_exp,double,__NOTHROW,exp,(double __x),(__x))
#elif defined(__CRT_HAVE___exp)
/* Exponential function of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_exp,double,__NOTHROW,exp,(double __x),__exp,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/exp.h>
__NAMESPACE_STD_BEGIN
/* Exponential function of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(exp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_exp double __NOTHROW(__LIBCCALL exp)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(exp))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_frexp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_frexp)
/* Break `value' into a normalized fraction and an integral power of 2 */
__CEIDECLARE(__ATTR_NONNULL((2)),double,__NOTHROW_NCX,frexp,(double __x, int *__pexponent),{ return __builtin_frexp(__x, __pexponent); })
#elif defined(__CRT_HAVE_frexp)
/* Break `value' into a normalized fraction and an integral power of 2 */
__CDECLARE(__ATTR_NONNULL((2)),double,__NOTHROW_NCX,frexp,(double __x, int *__pexponent),(__x,__pexponent))
#elif defined(__CRT_HAVE___frexp)
/* Break `value' into a normalized fraction and an integral power of 2 */
__CREDIRECT(__ATTR_NONNULL((2)),double,__NOTHROW_NCX,frexp,(double __x, int *__pexponent),__frexp,(__x,__pexponent))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/frexp.h>
__NAMESPACE_STD_BEGIN
/* Break `value' into a normalized fraction and an integral power of 2 */
__NAMESPACE_LOCAL_USING_OR_IMPL(frexp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) double __NOTHROW_NCX(__LIBCCALL frexp)(double __x, int *__pexponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(frexp))(__x, __pexponent); })
#endif /* ... */
#if __has_builtin(__builtin_ldexp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ldexp)
/* `x' times (two to the `exponent' power) */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,ldexp,(double __x, int __exponent),{ return __builtin_ldexp(__x, __exponent); })
#elif defined(__CRT_HAVE_ldexp)
/* `x' times (two to the `exponent' power) */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,ldexp,(double __x, int __exponent),(__x,__exponent))
#elif defined(__CRT_HAVE___ldexp)
/* `x' times (two to the `exponent' power) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,ldexp,(double __x, int __exponent),__ldexp,(__x,__exponent))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/ldexp.h>
__NAMESPACE_STD_BEGIN
/* `x' times (two to the `exponent' power) */
__NAMESPACE_LOCAL_USING_OR_IMPL(ldexp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL ldexp)(double __x, int __exponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ldexp))(__x, __exponent); })
#endif /* ... */
#if __has_builtin(__builtin_log) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log)
/* Natural logarithm of `x' */
__CEIDECLARE(__ATTR_WUNUSED __DECL_SIMD_log,double,__NOTHROW,log,(double __x),{ return __builtin_log(__x); })
#elif defined(__CRT_HAVE_log)
/* Natural logarithm of `x' */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_log,double,__NOTHROW,log,(double __x),(__x))
#elif defined(__CRT_HAVE___log)
/* Natural logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_log,double,__NOTHROW,log,(double __x),__log,(__x))
#endif /* ... */
#if __has_builtin(__builtin_log10) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log10)
/* Base-ten logarithm of `x' */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,log10,(double __x),{ return __builtin_log10(__x); })
#elif defined(__CRT_HAVE_log10)
/* Base-ten logarithm of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,log10,(double __x),(__x))
#elif defined(__CRT_HAVE___log10)
/* Base-ten logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,log10,(double __x),__log10,(__x))
#endif /* ... */
#if __has_builtin(__builtin_modf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_modf)
/* Break `value' into integral and fractional parts */
__CEIDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),double,__NOTHROW_NCX,modf,(double __x, double *__iptr),{ return __builtin_modf(__x, __iptr); })
#elif defined(__CRT_HAVE_modf)
/* Break `value' into integral and fractional parts */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),double,__NOTHROW_NCX,modf,(double __x, double *__iptr),(__x,__iptr))
#elif defined(__CRT_HAVE___modf)
/* Break `value' into integral and fractional parts */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),double,__NOTHROW_NCX,modf,(double __x, double *__iptr),__modf,(__x,__iptr))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/modf.h>
__NAMESPACE_STD_BEGIN
/* Break `value' into integral and fractional parts */
__NAMESPACE_LOCAL_USING_OR_IMPL(modf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) double __NOTHROW_NCX(__LIBCCALL modf)(double __x, double *__iptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(modf))(__x, __iptr); })
#endif /* ... */
#if __has_builtin(__builtin_expf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expf)
/* Exponential function of `x' */
__CEIDECLARE(__ATTR_WUNUSED __DECL_SIMD_expf,float,__NOTHROW,expf,(float __x),{ return __builtin_expf(__x); })
#elif defined(__CRT_HAVE_expf)
/* Exponential function of `x' */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_expf,float,__NOTHROW,expf,(float __x),(__x))
#elif defined(__CRT_HAVE___expf)
/* Exponential function of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_expf,float,__NOTHROW,expf,(float __x),__expf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_exp) || defined(__CRT_HAVE___exp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/expf.h>
__NAMESPACE_STD_BEGIN
/* Exponential function of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(expf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_expf float __NOTHROW(__LIBCCALL expf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expf))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_frexpf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_frexpf)
/* Break `value' into a normalized fraction and an integral power of 2 */
__CEIDECLARE(__ATTR_NONNULL((2)),float,__NOTHROW_NCX,frexpf,(float __x, int *__pexponent),{ return __builtin_frexpf(__x, __pexponent); })
#elif defined(__CRT_HAVE_frexpf)
/* Break `value' into a normalized fraction and an integral power of 2 */
__CDECLARE(__ATTR_NONNULL((2)),float,__NOTHROW_NCX,frexpf,(float __x, int *__pexponent),(__x,__pexponent))
#elif defined(__CRT_HAVE___frexpf)
/* Break `value' into a normalized fraction and an integral power of 2 */
__CREDIRECT(__ATTR_NONNULL((2)),float,__NOTHROW_NCX,frexpf,(float __x, int *__pexponent),__frexpf,(__x,__pexponent))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_frexp) || defined(__CRT_HAVE___frexp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/frexpf.h>
__NAMESPACE_STD_BEGIN
/* Break `value' into a normalized fraction and an integral power of 2 */
__NAMESPACE_LOCAL_USING_OR_IMPL(frexpf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) float __NOTHROW_NCX(__LIBCCALL frexpf)(float __x, int *__pexponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(frexpf))(__x, __pexponent); })
#endif /* ... */
#if __has_builtin(__builtin_ldexpf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ldexpf)
/* `x' times (two to the `exponent' power) */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,ldexpf,(float __x, int __exponent),{ return __builtin_ldexpf(__x, __exponent); })
#elif defined(__CRT_HAVE_ldexpf)
/* `x' times (two to the `exponent' power) */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,ldexpf,(float __x, int __exponent),(__x,__exponent))
#elif defined(__CRT_HAVE___ldexpf)
/* `x' times (two to the `exponent' power) */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,ldexpf,(float __x, int __exponent),__ldexpf,(__x,__exponent))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_ldexp) || defined(__CRT_HAVE___ldexp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/ldexpf.h>
__NAMESPACE_STD_BEGIN
/* `x' times (two to the `exponent' power) */
__NAMESPACE_LOCAL_USING_OR_IMPL(ldexpf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL ldexpf)(float __x, int __exponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ldexpf))(__x, __exponent); })
#endif /* ... */
#if __has_builtin(__builtin_logf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logf)
/* Natural logarithm of `x' */
__CEIDECLARE(__ATTR_WUNUSED __DECL_SIMD_logf,float,__NOTHROW,logf,(float __x),{ return __builtin_logf(__x); })
#elif defined(__CRT_HAVE_logf)
/* Natural logarithm of `x' */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_logf,float,__NOTHROW,logf,(float __x),(__x))
#elif defined(__CRT_HAVE___logf)
/* Natural logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_logf,float,__NOTHROW,logf,(float __x),__logf,(__x))
#elif defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log)
__NAMESPACE_STD_END
#include <libc/local/math/logf.h>
__NAMESPACE_STD_BEGIN
/* Natural logarithm of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(logf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_logf float __NOTHROW(__LIBCCALL logf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logf))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_log10f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log10f)
/* Base-ten logarithm of `x' */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,log10f,(float __x),{ return __builtin_log10f(__x); })
#elif defined(__CRT_HAVE_log10f)
/* Base-ten logarithm of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,log10f,(float __x),(__x))
#elif defined(__CRT_HAVE___log10f)
/* Base-ten logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,log10f,(float __x),__log10f,(__x))
#elif defined(__CRT_HAVE_log10) || defined(__CRT_HAVE___log10)
__NAMESPACE_STD_END
#include <libc/local/math/log10f.h>
__NAMESPACE_STD_BEGIN
/* Base-ten logarithm of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(log10f, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL log10f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log10f))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_modff) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_modff)
/* Break `value' into integral and fractional parts */
__CEIDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),float,__NOTHROW_NCX,modff,(float __x, float *__iptr),{ return __builtin_modff(__x, __iptr); })
#elif defined(__CRT_HAVE_modff)
/* Break `value' into integral and fractional parts */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),float,__NOTHROW_NCX,modff,(float __x, float *__iptr),(__x,__iptr))
#elif defined(__CRT_HAVE___modff)
/* Break `value' into integral and fractional parts */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),float,__NOTHROW_NCX,modff,(float __x, float *__iptr),__modff,(__x,__iptr))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_modf) || defined(__CRT_HAVE___modf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/modff.h>
__NAMESPACE_STD_BEGIN
/* Break `value' into integral and fractional parts */
__NAMESPACE_LOCAL_USING_OR_IMPL(modff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) float __NOTHROW_NCX(__LIBCCALL modff)(float __x, float *__iptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(modff))(__x, __iptr); })
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_expl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expl)
/* Exponential function of `x' */
__CEIDECLARE(__ATTR_WUNUSED __DECL_SIMD_expl,__LONGDOUBLE,__NOTHROW,expl,(__LONGDOUBLE __x),{ return __builtin_expl(__x); })
#elif defined(__CRT_HAVE_expl)
/* Exponential function of `x' */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_expl,__LONGDOUBLE,__NOTHROW,expl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___expl)
/* Exponential function of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_expl,__LONGDOUBLE,__NOTHROW,expl,(__LONGDOUBLE __x),__expl,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_exp) || defined(__CRT_HAVE___exp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/expl.h>
__NAMESPACE_STD_BEGIN
/* Exponential function of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(expl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_expl __LONGDOUBLE __NOTHROW(__LIBCCALL expl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expl))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_frexpl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_frexpl)
/* Break `value' into a normalized fraction and an integral power of 2 */
__CEIDECLARE(__ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,frexpl,(__LONGDOUBLE __x, int *__pexponent),{ return __builtin_frexpl(__x, __pexponent); })
#elif defined(__CRT_HAVE_frexpl)
/* Break `value' into a normalized fraction and an integral power of 2 */
__CDECLARE(__ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,frexpl,(__LONGDOUBLE __x, int *__pexponent),(__x,__pexponent))
#elif defined(__CRT_HAVE___frexpl)
/* Break `value' into a normalized fraction and an integral power of 2 */
__CREDIRECT(__ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,frexpl,(__LONGDOUBLE __x, int *__pexponent),__frexpl,(__x,__pexponent))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_frexp) || defined(__CRT_HAVE___frexp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/frexpl.h>
__NAMESPACE_STD_BEGIN
/* Break `value' into a normalized fraction and an integral power of 2 */
__NAMESPACE_LOCAL_USING_OR_IMPL(frexpl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL frexpl)(__LONGDOUBLE __x, int *__pexponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(frexpl))(__x, __pexponent); })
#endif /* ... */
#if __has_builtin(__builtin_ldexpl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ldexpl)
/* `x' times (two to the `exponent' power) */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ldexpl,(__LONGDOUBLE __x, int __exponent),{ return __builtin_ldexpl(__x, __exponent); })
#elif defined(__CRT_HAVE_ldexpl)
/* `x' times (two to the `exponent' power) */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ldexpl,(__LONGDOUBLE __x, int __exponent),(__x,__exponent))
#elif defined(__CRT_HAVE___ldexpl)
/* `x' times (two to the `exponent' power) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ldexpl,(__LONGDOUBLE __x, int __exponent),__ldexpl,(__x,__exponent))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_ldexp) || defined(__CRT_HAVE___ldexp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/ldexpl.h>
__NAMESPACE_STD_BEGIN
/* `x' times (two to the `exponent' power) */
__NAMESPACE_LOCAL_USING_OR_IMPL(ldexpl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL ldexpl)(__LONGDOUBLE __x, int __exponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ldexpl))(__x, __exponent); })
#endif /* ... */
#if __has_builtin(__builtin_logl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logl)
/* Natural logarithm of `x' */
__CEIDECLARE(__ATTR_WUNUSED __DECL_SIMD_logl,__LONGDOUBLE,__NOTHROW,logl,(__LONGDOUBLE __x),{ return __builtin_logl(__x); })
#elif defined(__CRT_HAVE_logl)
/* Natural logarithm of `x' */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_logl,__LONGDOUBLE,__NOTHROW,logl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___logl)
/* Natural logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_logl,__LONGDOUBLE,__NOTHROW,logl,(__LONGDOUBLE __x),__logl,(__x))
#elif defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log)
__NAMESPACE_STD_END
#include <libc/local/math/logl.h>
__NAMESPACE_STD_BEGIN
/* Natural logarithm of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(logl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_logl __LONGDOUBLE __NOTHROW(__LIBCCALL logl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logl))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_log10l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log10l)
/* Base-ten logarithm of `x' */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log10l,(__LONGDOUBLE __x),{ return __builtin_log10l(__x); })
#elif defined(__CRT_HAVE_log10l)
/* Base-ten logarithm of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log10l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___log10l)
/* Base-ten logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log10l,(__LONGDOUBLE __x),__log10l,(__x))
#elif defined(__CRT_HAVE_log10) || defined(__CRT_HAVE___log10)
__NAMESPACE_STD_END
#include <libc/local/math/log10l.h>
__NAMESPACE_STD_BEGIN
/* Base-ten logarithm of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(log10l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL log10l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log10l))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_modfl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_modfl)
/* Break `value' into integral and fractional parts */
__CEIDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,modfl,(__LONGDOUBLE __x, __LONGDOUBLE *__iptr),{ return __builtin_modfl(__x, __iptr); })
#elif defined(__CRT_HAVE_modfl)
/* Break `value' into integral and fractional parts */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,modfl,(__LONGDOUBLE __x, __LONGDOUBLE *__iptr),(__x,__iptr))
#elif defined(__CRT_HAVE___modfl)
/* Break `value' into integral and fractional parts */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,modfl,(__LONGDOUBLE __x, __LONGDOUBLE *__iptr),__modfl,(__x,__iptr))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_modf) || defined(__CRT_HAVE___modf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/modfl.h>
__NAMESPACE_STD_BEGIN
/* Break `value' into integral and fractional parts */
__NAMESPACE_LOCAL_USING_OR_IMPL(modfl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL modfl)(__LONGDOUBLE __x, __LONGDOUBLE *__iptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(modfl))(__x, __iptr); })
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#if __has_builtin(__builtin_expm1) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expm1)
/* Return `exp(x) - 1' */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,expm1,(double __x),{ return __builtin_expm1(__x); })
#elif defined(__CRT_HAVE_expm1)
/* Return `exp(x) - 1' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,expm1,(double __x),(__x))
#elif defined(__CRT_HAVE___expm1)
/* Return `exp(x) - 1' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,expm1,(double __x),__expm1,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/expm1.h>
__NAMESPACE_STD_BEGIN
/* Return `exp(x) - 1' */
__NAMESPACE_LOCAL_USING_OR_IMPL(expm1, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL expm1)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expm1))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_log1p) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log1p)
/* Return `log(1 + x)' */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,log1p,(double __x),{ return __builtin_log1p(__x); })
#elif defined(__CRT_HAVE_log1p)
/* Return `log(1 + x)' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,log1p,(double __x),(__x))
#elif defined(__CRT_HAVE___log1p)
/* Return `log(1 + x)' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,log1p,(double __x),__log1p,(__x))
#endif /* ... */
#if __has_builtin(__builtin_logb) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logb)
/* Return the base 2 signed integral exponent of `x' */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,logb,(double __x),{ return __builtin_logb(__x); })
#elif defined(__CRT_HAVE_logb)
/* Return the base 2 signed integral exponent of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,logb,(double __x),(__x))
#elif defined(__CRT_HAVE___logb)
/* Return the base 2 signed integral exponent of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,logb,(double __x),__logb,(__x))
#elif defined(__CRT_HAVE__logb)
/* Return the base 2 signed integral exponent of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,logb,(double __x),_logb,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/logb.h>
__NAMESPACE_STD_BEGIN
/* Return the base 2 signed integral exponent of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(logb, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL logb)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logb))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_expm1f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expm1f)
/* Return `exp(x) - 1' */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,expm1f,(float __x),{ return __builtin_expm1f(__x); })
#elif defined(__CRT_HAVE_expm1f)
/* Return `exp(x) - 1' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,expm1f,(float __x),(__x))
#elif defined(__CRT_HAVE___expm1f)
/* Return `exp(x) - 1' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,expm1f,(float __x),__expm1f,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_expm1) || defined(__CRT_HAVE___expm1) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/expm1f.h>
__NAMESPACE_STD_BEGIN
/* Return `exp(x) - 1' */
__NAMESPACE_LOCAL_USING_OR_IMPL(expm1f, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL expm1f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expm1f))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_log1pf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log1pf)
/* Return `log(1 + x)' */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,log1pf,(float __x),{ return __builtin_log1pf(__x); })
#elif defined(__CRT_HAVE_log1pf)
/* Return `log(1 + x)' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,log1pf,(float __x),(__x))
#elif defined(__CRT_HAVE___log1pf)
/* Return `log(1 + x)' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,log1pf,(float __x),__log1pf,(__x))
#elif defined(__CRT_HAVE_log1p) || defined(__CRT_HAVE___log1p)
__NAMESPACE_STD_END
#include <libc/local/math/log1pf.h>
__NAMESPACE_STD_BEGIN
/* Return `log(1 + x)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(log1pf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL log1pf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log1pf))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_logbf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logbf)
/* Return the base 2 signed integral exponent of `x' */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,logbf,(float __x),{ return __builtin_logbf(__x); })
#elif defined(__CRT_HAVE_logbf)
/* Return the base 2 signed integral exponent of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,logbf,(float __x),(__x))
#elif defined(__CRT_HAVE___logbf)
/* Return the base 2 signed integral exponent of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,logbf,(float __x),__logbf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_logb) || defined(__CRT_HAVE___logb) || defined(__CRT_HAVE__logb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/logbf.h>
__NAMESPACE_STD_BEGIN
/* Return the base 2 signed integral exponent of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(logbf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL logbf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logbf))(__x); })
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_expm1l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expm1l)
/* Return `exp(x) - 1' */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,expm1l,(__LONGDOUBLE __x),{ return __builtin_expm1l(__x); })
#elif defined(__CRT_HAVE_expm1l)
/* Return `exp(x) - 1' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,expm1l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___expm1l)
/* Return `exp(x) - 1' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,expm1l,(__LONGDOUBLE __x),__expm1l,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_expm1) || defined(__CRT_HAVE___expm1) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/expm1l.h>
__NAMESPACE_STD_BEGIN
/* Return `exp(x) - 1' */
__NAMESPACE_LOCAL_USING_OR_IMPL(expm1l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL expm1l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expm1l))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_log1pl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log1pl)
/* Return `log(1 + x)' */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log1pl,(__LONGDOUBLE __x),{ return __builtin_log1pl(__x); })
#elif defined(__CRT_HAVE_log1pl)
/* Return `log(1 + x)' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log1pl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___log1pl)
/* Return `log(1 + x)' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log1pl,(__LONGDOUBLE __x),__log1pl,(__x))
#elif defined(__CRT_HAVE_log1p) || defined(__CRT_HAVE___log1p)
__NAMESPACE_STD_END
#include <libc/local/math/log1pl.h>
__NAMESPACE_STD_BEGIN
/* Return `log(1 + x)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(log1pl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL log1pl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log1pl))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_logbl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logbl)
/* Return the base 2 signed integral exponent of `x' */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,logbl,(__LONGDOUBLE __x),{ return __builtin_logbl(__x); })
#elif defined(__CRT_HAVE_logbl)
/* Return the base 2 signed integral exponent of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,logbl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___logbl)
/* Return the base 2 signed integral exponent of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,logbl,(__LONGDOUBLE __x),__logbl,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_logb) || defined(__CRT_HAVE___logb) || defined(__CRT_HAVE__logb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/logbl.h>
__NAMESPACE_STD_BEGIN
/* Return the base 2 signed integral exponent of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(logbl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL logbl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logbl))(__x); })
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

#ifdef __USE_ISOC99
#if __has_builtin(__builtin_exp2) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp2)
/* Compute base-2 exponential of `x' */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,exp2,(double __x),{ return __builtin_exp2(__x); })
#elif defined(__CRT_HAVE_exp2)
/* Compute base-2 exponential of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,exp2,(double __x),(__x))
#elif defined(__CRT_HAVE___exp2)
/* Compute base-2 exponential of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,exp2,(double __x),__exp2,(__x))
#endif /* ... */
#if __has_builtin(__builtin_log2) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log2)
/* Compute base-2 logarithm of `x' */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,log2,(double __x),{ return __builtin_log2(__x); })
#elif defined(__CRT_HAVE_log2)
/* Compute base-2 logarithm of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,log2,(double __x),(__x))
#elif defined(__CRT_HAVE___log2)
/* Compute base-2 logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,log2,(double __x),__log2,(__x))
#endif /* ... */
#if __has_builtin(__builtin_exp2f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp2f)
/* Compute base-2 exponential of `x' */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,exp2f,(float __x),{ return __builtin_exp2f(__x); })
#elif defined(__CRT_HAVE_exp2f)
/* Compute base-2 exponential of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,exp2f,(float __x),(__x))
#elif defined(__CRT_HAVE___exp2f)
/* Compute base-2 exponential of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,exp2f,(float __x),__exp2f,(__x))
#elif defined(__CRT_HAVE_exp2) || defined(__CRT_HAVE___exp2)
__NAMESPACE_STD_END
#include <libc/local/math/exp2f.h>
__NAMESPACE_STD_BEGIN
/* Compute base-2 exponential of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(exp2f, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL exp2f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(exp2f))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_log2f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log2f)
/* Compute base-2 logarithm of `x' */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,log2f,(float __x),{ return __builtin_log2f(__x); })
#elif defined(__CRT_HAVE_log2f)
/* Compute base-2 logarithm of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,log2f,(float __x),(__x))
#elif defined(__CRT_HAVE___log2f)
/* Compute base-2 logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,log2f,(float __x),__log2f,(__x))
#elif defined(__CRT_HAVE_log2) || defined(__CRT_HAVE___log2)
__NAMESPACE_STD_END
#include <libc/local/math/log2f.h>
__NAMESPACE_STD_BEGIN
/* Compute base-2 logarithm of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(log2f, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL log2f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log2f))(__x); })
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_exp2l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp2l)
/* Compute base-2 exponential of `x' */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp2l,(__LONGDOUBLE __x),{ return __builtin_exp2l(__x); })
#elif defined(__CRT_HAVE_exp2l)
/* Compute base-2 exponential of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp2l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___exp2l)
/* Compute base-2 exponential of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp2l,(__LONGDOUBLE __x),__exp2l,(__x))
#elif defined(__CRT_HAVE_exp2) || defined(__CRT_HAVE___exp2)
__NAMESPACE_STD_END
#include <libc/local/math/exp2l.h>
__NAMESPACE_STD_BEGIN
/* Compute base-2 exponential of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(exp2l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL exp2l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(exp2l))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_log2l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log2l)
/* Compute base-2 logarithm of `x' */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log2l,(__LONGDOUBLE __x),{ return __builtin_log2l(__x); })
#elif defined(__CRT_HAVE_log2l)
/* Compute base-2 logarithm of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log2l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___log2l)
/* Compute base-2 logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log2l,(__LONGDOUBLE __x),__log2l,(__x))
#elif defined(__CRT_HAVE_log2) || defined(__CRT_HAVE___log2)
__NAMESPACE_STD_END
#include <libc/local/math/log2l.h>
__NAMESPACE_STD_BEGIN
/* Compute base-2 logarithm of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(log2l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL log2l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log2l))(__x); })
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */

/* Power functions. */
#if __has_builtin(__builtin_pow) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_pow)
/* Return `x' to the `y' power */
__CEIDECLARE(__ATTR_WUNUSED __DECL_SIMD_pow,double,__NOTHROW,pow,(double __x, double __y),{ return __builtin_pow(__x, __y); })
#elif defined(__CRT_HAVE_pow)
/* Return `x' to the `y' power */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_pow,double,__NOTHROW,pow,(double __x, double __y),(__x,__y))
#elif defined(__CRT_HAVE___pow)
/* Return `x' to the `y' power */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_pow,double,__NOTHROW,pow,(double __x, double __y),__pow,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/pow.h>
__NAMESPACE_STD_BEGIN
/* Return `x' to the `y' power */
__NAMESPACE_LOCAL_USING_OR_IMPL(pow, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_pow double __NOTHROW(__LIBCCALL pow)(double __x, double __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pow))(__x, __y); })
#endif /* ... */
#if __has_builtin(__builtin_sqrt) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sqrt)
/* Return the square root of `x' */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,sqrt,(double __x),{ return __builtin_sqrt(__x); })
#elif defined(__CRT_HAVE_sqrt)
/* Return the square root of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,sqrt,(double __x),(__x))
#elif defined(__CRT_HAVE___sqrt)
/* Return the square root of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,sqrt,(double __x),__sqrt,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/sqrt.h>
__NAMESPACE_STD_BEGIN
/* Return the square root of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(sqrt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL sqrt)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sqrt))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_powf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_powf)
/* Return `x' to the `y' power */
__CEIDECLARE(__ATTR_WUNUSED __DECL_SIMD_powf,float,__NOTHROW,powf,(float __x, float __y),{ return __builtin_powf(__x, __y); })
#elif defined(__CRT_HAVE_powf)
/* Return `x' to the `y' power */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_powf,float,__NOTHROW,powf,(float __x, float __y),(__x,__y))
#elif defined(__CRT_HAVE___powf)
/* Return `x' to the `y' power */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_powf,float,__NOTHROW,powf,(float __x, float __y),__powf,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/powf.h>
__NAMESPACE_STD_BEGIN
/* Return `x' to the `y' power */
__NAMESPACE_LOCAL_USING_OR_IMPL(powf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_powf float __NOTHROW(__LIBCCALL powf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(powf))(__x, __y); })
#endif /* ... */
#if __has_builtin(__builtin_sqrtf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sqrtf)
/* Return the square root of `x' */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,sqrtf,(float __x),{ return __builtin_sqrtf(__x); })
#elif defined(__CRT_HAVE_sqrtf)
/* Return the square root of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,sqrtf,(float __x),(__x))
#elif defined(__CRT_HAVE___sqrtf)
/* Return the square root of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,sqrtf,(float __x),__sqrtf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/sqrtf.h>
__NAMESPACE_STD_BEGIN
/* Return the square root of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(sqrtf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL sqrtf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sqrtf))(__x); })
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_powl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_powl)
/* Return `x' to the `y' power */
__CEIDECLARE(__ATTR_WUNUSED __DECL_SIMD_powl,__LONGDOUBLE,__NOTHROW,powl,(__LONGDOUBLE __x, __LONGDOUBLE __y),{ return __builtin_powl(__x, __y); })
#elif defined(__CRT_HAVE_powl)
/* Return `x' to the `y' power */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_powl,__LONGDOUBLE,__NOTHROW,powl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__CRT_HAVE___powl)
/* Return `x' to the `y' power */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_powl,__LONGDOUBLE,__NOTHROW,powl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__powl,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/powl.h>
__NAMESPACE_STD_BEGIN
/* Return `x' to the `y' power */
__NAMESPACE_LOCAL_USING_OR_IMPL(powl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_powl __LONGDOUBLE __NOTHROW(__LIBCCALL powl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(powl))(__x, __y); })
#endif /* ... */
#if __has_builtin(__builtin_sqrtl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sqrtl)
/* Return the square root of `x' */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sqrtl,(__LONGDOUBLE __x),{ return __builtin_sqrtl(__x); })
#elif defined(__CRT_HAVE_sqrtl)
/* Return the square root of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sqrtl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___sqrtl)
/* Return the square root of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sqrtl,(__LONGDOUBLE __x),__sqrtl,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/sqrtl.h>
__NAMESPACE_STD_BEGIN
/* Return the square root of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(sqrtl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL sqrtl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sqrtl))(__x); })
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
#if __has_builtin(__builtin_hypot) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_hypot)
/* Return `sqrt(x*x + y*y)' */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,hypot,(double __x, double __y),{ return __builtin_hypot(__x, __y); })
#elif defined(__CRT_HAVE_hypot)
/* Return `sqrt(x*x + y*y)' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,hypot,(double __x, double __y),(__x,__y))
#elif defined(__CRT_HAVE___hypot)
/* Return `sqrt(x*x + y*y)' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,hypot,(double __x, double __y),__hypot,(__x,__y))
#endif /* ... */
#if __has_builtin(__builtin_hypotf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_hypotf)
/* Return `sqrt(x*x + y*y)' */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,hypotf,(float __x, float __y),{ return __builtin_hypotf(__x, __y); })
#elif defined(__CRT_HAVE_hypotf)
/* Return `sqrt(x*x + y*y)' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,hypotf,(float __x, float __y),(__x,__y))
#elif defined(__CRT_HAVE___hypotf)
/* Return `sqrt(x*x + y*y)' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,hypotf,(float __x, float __y),__hypotf,(__x,__y))
#elif defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE___hypot)
__NAMESPACE_STD_END
#include <libc/local/math/hypotf.h>
__NAMESPACE_STD_BEGIN
/* Return `sqrt(x*x + y*y)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(hypotf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL hypotf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hypotf))(__x, __y); })
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_hypotl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_hypotl)
/* Return `sqrt(x*x + y*y)' */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,hypotl,(__LONGDOUBLE __x, __LONGDOUBLE __y),{ return __builtin_hypotl(__x, __y); })
#elif defined(__CRT_HAVE_hypotl)
/* Return `sqrt(x*x + y*y)' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,hypotl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__CRT_HAVE___hypotl)
/* Return `sqrt(x*x + y*y)' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,hypotl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__hypotl,(__x,__y))
#elif defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE___hypot)
__NAMESPACE_STD_END
#include <libc/local/math/hypotl.h>
__NAMESPACE_STD_BEGIN
/* Return `sqrt(x*x + y*y)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(hypotl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL hypotl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hypotl))(__x, __y); })
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN || __USE_ISOC99 */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#if __has_builtin(__builtin_cbrt) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cbrt)
/* Return the cube root of `x' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,cbrt,(double __x),{ return __builtin_cbrt(__x); })
#elif defined(__CRT_HAVE_cbrt)
/* Return the cube root of `x' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,cbrt,(double __x),(__x))
#elif defined(__CRT_HAVE___cbrt)
/* Return the cube root of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,cbrt,(double __x),__cbrt,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/cbrt.h>
__NAMESPACE_STD_BEGIN
/* Return the cube root of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(cbrt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL cbrt)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cbrt))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_cbrtf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cbrtf)
/* Return the cube root of `x' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,cbrtf,(float __x),{ return __builtin_cbrtf(__x); })
#elif defined(__CRT_HAVE_cbrtf)
/* Return the cube root of `x' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,cbrtf,(float __x),(__x))
#elif defined(__CRT_HAVE___cbrtf)
/* Return the cube root of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,cbrtf,(float __x),__cbrtf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_cbrt) || defined(__CRT_HAVE___cbrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/cbrtf.h>
__NAMESPACE_STD_BEGIN
/* Return the cube root of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(cbrtf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL cbrtf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cbrtf))(__x); })
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_cbrtl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cbrtl)
/* Return the cube root of `x' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cbrtl,(__LONGDOUBLE __x),{ return __builtin_cbrtl(__x); })
#elif defined(__CRT_HAVE_cbrtl)
/* Return the cube root of `x' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cbrtl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___cbrtl)
/* Return the cube root of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cbrtl,(__LONGDOUBLE __x),__cbrtl,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_cbrt) || defined(__CRT_HAVE___cbrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/cbrtl.h>
__NAMESPACE_STD_BEGIN
/* Return the cube root of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(cbrtl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL cbrtl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cbrtl))(__x); })
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

/* Nearest integer, absolute value, and remainder functions. */
#if __has_builtin(__builtin_ceil) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ceil)
/* Smallest integral value not less than `x' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,ceil,(double __x),{ return __builtin_ceil(__x); })
#elif defined(__CRT_HAVE_ceil)
/* Smallest integral value not less than `x' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,ceil,(double __x),(__x))
#elif defined(__CRT_HAVE___ceil)
/* Smallest integral value not less than `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,ceil,(double __x),__ceil,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/ceil.h>
__NAMESPACE_STD_BEGIN
/* Smallest integral value not less than `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ceil, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL ceil)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ceil))(__x); })
#endif /* !... */
#if __has_builtin(__builtin_fabs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabs)
/* Absolute value of `x' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fabs,(double __x),{ return __builtin_fabs(__x); })
#elif defined(__CRT_HAVE_fabs)
/* Absolute value of `x' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fabs,(double __x),(__x))
#elif defined(__CRT_HAVE___fabs)
/* Absolute value of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fabs,(double __x),__fabs,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/fabs.h>
__NAMESPACE_STD_BEGIN
/* Absolute value of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fabs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL fabs)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabs))(__x); })
#endif /* !... */
#if __has_builtin(__builtin_floor) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_floor)
/* Largest integer not greater than `x' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,floor,(double __x),{ return __builtin_floor(__x); })
#elif defined(__CRT_HAVE_floor)
/* Largest integer not greater than `x' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,floor,(double __x),(__x))
#elif defined(__CRT_HAVE___floor)
/* Largest integer not greater than `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,floor,(double __x),__floor,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/floor.h>
__NAMESPACE_STD_BEGIN
/* Largest integer not greater than `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(floor, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL floor)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(floor))(__x); })
#endif /* !... */
#if __has_builtin(__builtin_fmod) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmod)
/* Floating-point modulo remainder of `x / y' */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,fmod,(double __x, double __y),{ return __builtin_fmod(__x, __y); })
#elif defined(__CRT_HAVE_fmod)
/* Floating-point modulo remainder of `x / y' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,fmod,(double __x, double __y),(__x,__y))
#elif defined(__CRT_HAVE___fmod)
/* Floating-point modulo remainder of `x / y' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,fmod,(double __x, double __y),__fmod,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/fmod.h>
__NAMESPACE_STD_BEGIN
/* Floating-point modulo remainder of `x / y' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fmod, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL fmod)(double __x, double __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmod))(__x, __y); })
#endif /* ... */
#if __has_builtin(__builtin_ceilf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ceilf)
/* Smallest integral value not less than `x' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,ceilf,(float __x),{ return __builtin_ceilf(__x); })
#elif defined(__CRT_HAVE_ceilf)
/* Smallest integral value not less than `x' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,ceilf,(float __x),(__x))
#elif defined(__CRT_HAVE___ceilf)
/* Smallest integral value not less than `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,ceilf,(float __x),__ceilf,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/ceilf.h>
__NAMESPACE_STD_BEGIN
/* Smallest integral value not less than `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ceilf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL ceilf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ceilf))(__x); })
#endif /* !... */
#if __has_builtin(__builtin_fabsf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabsf)
/* Absolute value of `x' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fabsf,(float __x),{ return __builtin_fabsf(__x); })
#elif defined(__CRT_HAVE_fabsf)
/* Absolute value of `x' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fabsf,(float __x),(__x))
#elif defined(__CRT_HAVE___fabsf)
/* Absolute value of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fabsf,(float __x),__fabsf,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/fabsf.h>
__NAMESPACE_STD_BEGIN
/* Absolute value of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fabsf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL fabsf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabsf))(__x); })
#endif /* !... */
#if __has_builtin(__builtin_floorf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_floorf)
/* Largest integer not greater than `x' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,floorf,(float __x),{ return __builtin_floorf(__x); })
#elif defined(__CRT_HAVE_floorf)
/* Largest integer not greater than `x' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,floorf,(float __x),(__x))
#elif defined(__CRT_HAVE___floorf)
/* Largest integer not greater than `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,floorf,(float __x),__floorf,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/floorf.h>
__NAMESPACE_STD_BEGIN
/* Largest integer not greater than `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(floorf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL floorf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(floorf))(__x); })
#endif /* !... */
#if __has_builtin(__builtin_fmodf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmodf)
/* Floating-point modulo remainder of `x / y' */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,fmodf,(float __x, float __y),{ return __builtin_fmodf(__x, __y); })
#elif defined(__CRT_HAVE_fmodf)
/* Floating-point modulo remainder of `x / y' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,fmodf,(float __x, float __y),(__x,__y))
#elif defined(__CRT_HAVE___fmodf)
/* Floating-point modulo remainder of `x / y' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,fmodf,(float __x, float __y),__fmodf,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_fmod) || defined(__CRT_HAVE___fmod) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/fmodf.h>
__NAMESPACE_STD_BEGIN
/* Floating-point modulo remainder of `x / y' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fmodf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL fmodf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmodf))(__x, __y); })
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_ceill) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ceill)
/* Smallest integral value not less than `x' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ceill,(__LONGDOUBLE __x),{ return __builtin_ceill(__x); })
#elif defined(__CRT_HAVE_ceill)
/* Smallest integral value not less than `x' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ceill,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___ceill)
/* Smallest integral value not less than `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ceill,(__LONGDOUBLE __x),__ceill,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/ceill.h>
__NAMESPACE_STD_BEGIN
/* Smallest integral value not less than `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(ceill, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL ceill)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ceill))(__x); })
#endif /* !... */
#if __has_builtin(__builtin_fabsl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabsl)
/* Absolute value of `x' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fabsl,(__LONGDOUBLE __x),{ return __builtin_fabsl(__x); })
#elif defined(__CRT_HAVE_fabsl)
/* Absolute value of `x' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fabsl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___fabsl)
/* Absolute value of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fabsl,(__LONGDOUBLE __x),__fabsl,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/fabsl.h>
__NAMESPACE_STD_BEGIN
/* Absolute value of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fabsl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL fabsl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabsl))(__x); })
#endif /* !... */
#if __has_builtin(__builtin_floorl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_floorl)
/* Largest integer not greater than `x' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,floorl,(__LONGDOUBLE __x),{ return __builtin_floorl(__x); })
#elif defined(__CRT_HAVE_floorl)
/* Largest integer not greater than `x' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,floorl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___floorl)
/* Largest integer not greater than `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,floorl,(__LONGDOUBLE __x),__floorl,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/floorl.h>
__NAMESPACE_STD_BEGIN
/* Largest integer not greater than `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(floorl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL floorl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(floorl))(__x); })
#endif /* !... */
#if __has_builtin(__builtin_fmodl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmodl)
/* Floating-point modulo remainder of `x / y' */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmodl,(__LONGDOUBLE __x, __LONGDOUBLE __y),{ return __builtin_fmodl(__x, __y); })
#elif defined(__CRT_HAVE_fmodl)
/* Floating-point modulo remainder of `x / y' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmodl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__CRT_HAVE___fmodl)
/* Floating-point modulo remainder of `x / y' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmodl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__fmodl,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_fmod) || defined(__CRT_HAVE___fmod) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/fmodl.h>
__NAMESPACE_STD_BEGIN
/* Floating-point modulo remainder of `x / y' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fmodl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL fmodl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmodl))(__x, __y); })
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#ifdef __USE_ISOC99
#if __has_builtin(__builtin_copysign) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_copysign)
/* Return `x' with its signed changed to `y's */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,copysign,(double __num, double __sign),{ return __builtin_copysign(__num, __sign); })
#elif defined(__CRT_HAVE_copysign)
/* Return `x' with its signed changed to `y's */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,copysign,(double __num, double __sign),(__num,__sign))
#elif defined(__CRT_HAVE___copysign)
/* Return `x' with its signed changed to `y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,copysign,(double __num, double __sign),__copysign,(__num,__sign))
#elif defined(__CRT_HAVE__copysign)
/* Return `x' with its signed changed to `y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,copysign,(double __num, double __sign),_copysign,(__num,__sign))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/copysign.h>
__NAMESPACE_STD_BEGIN
/* Return `x' with its signed changed to `y's */
__NAMESPACE_LOCAL_USING_OR_IMPL(copysign, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL copysign)(double __num, double __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(copysign))(__num, __sign); })
#endif /* !... */
#if __has_builtin(__builtin_nan) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nan)
/* Return representation of qNaN for double type */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nan,(char const *__tagb),{ return __builtin_nan(__tagb); })
#elif defined(__CRT_HAVE_nan)
/* Return representation of qNaN for double type */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nan,(char const *__tagb),(__tagb))
#elif defined(__CRT_HAVE___nan)
/* Return representation of qNaN for double type */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nan,(char const *__tagb),__nan,(__tagb))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/nan.h>
__NAMESPACE_STD_BEGIN
/* Return representation of qNaN for double type */
__NAMESPACE_LOCAL_USING_OR_IMPL(nan, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL nan)(char const *__tagb) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nan))(__tagb); })
#endif /* ... */
#if __has_builtin(__builtin_copysignf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_copysignf)
/* Return `x' with its signed changed to `y's */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,copysignf,(float __num, float __sign),{ return __builtin_copysignf(__num, __sign); })
#elif defined(__CRT_HAVE_copysignf)
/* Return `x' with its signed changed to `y's */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,copysignf,(float __num, float __sign),(__num,__sign))
#elif defined(__CRT_HAVE___copysignf)
/* Return `x' with its signed changed to `y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,copysignf,(float __num, float __sign),__copysignf,(__num,__sign))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/copysignf.h>
__NAMESPACE_STD_BEGIN
/* Return `x' with its signed changed to `y's */
__NAMESPACE_LOCAL_USING_OR_IMPL(copysignf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL copysignf)(float __num, float __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(copysignf))(__num, __sign); })
#endif /* !... */
#if __has_builtin(__builtin_nanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nanf)
/* Return representation of qNaN for double type */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nanf,(char const *__tagb),{ return __builtin_nanf(__tagb); })
#elif defined(__CRT_HAVE_nanf)
/* Return representation of qNaN for double type */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nanf,(char const *__tagb),(__tagb))
#elif defined(__CRT_HAVE___nanf)
/* Return representation of qNaN for double type */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nanf,(char const *__tagb),__nanf,(__tagb))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_nan) || defined(__CRT_HAVE___nan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/nanf.h>
__NAMESPACE_STD_BEGIN
/* Return representation of qNaN for double type */
__NAMESPACE_LOCAL_USING_OR_IMPL(nanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL nanf)(char const *__tagb) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nanf))(__tagb); })
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_copysignl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_copysignl)
/* Return `x' with its signed changed to `y's */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,copysignl,(__LONGDOUBLE __num, __LONGDOUBLE __sign),{ return __builtin_copysignl(__num, __sign); })
#elif defined(__CRT_HAVE_copysignl)
/* Return `x' with its signed changed to `y's */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,copysignl,(__LONGDOUBLE __num, __LONGDOUBLE __sign),(__num,__sign))
#elif defined(__CRT_HAVE___copysignl)
/* Return `x' with its signed changed to `y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,copysignl,(__LONGDOUBLE __num, __LONGDOUBLE __sign),__copysignl,(__num,__sign))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/copysignl.h>
__NAMESPACE_STD_BEGIN
/* Return `x' with its signed changed to `y's */
__NAMESPACE_LOCAL_USING_OR_IMPL(copysignl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL copysignl)(__LONGDOUBLE __num, __LONGDOUBLE __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(copysignl))(__num, __sign); })
#endif /* !... */
#if __has_builtin(__builtin_nanl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nanl)
/* Return representation of qNaN for double type */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nanl,(char const *__tagb),{ return __builtin_nanl(__tagb); })
#elif defined(__CRT_HAVE_nanl)
/* Return representation of qNaN for double type */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nanl,(char const *__tagb),(__tagb))
#elif defined(__CRT_HAVE___nanl)
/* Return representation of qNaN for double type */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nanl,(char const *__tagb),__nanl,(__tagb))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_nan) || defined(__CRT_HAVE___nan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/nanl.h>
__NAMESPACE_STD_BEGIN
/* Return representation of qNaN for double type */
__NAMESPACE_LOCAL_USING_OR_IMPL(nanl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL nanl)(char const *__tagb) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nanl))(__tagb); })
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */

/* Error and gamma functions. */
#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
#if __has_builtin(__builtin_erf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erf)
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,erf,(double __x),{ return __builtin_erf(__x); })
#elif defined(__CRT_HAVE_erf)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,erf,(double __x),(__x))
#elif defined(__CRT_HAVE___erf)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,erf,(double __x),__erf,(__x))
#endif /* ... */
#if __has_builtin(__builtin_erfc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erfc)
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,erfc,(double __x),{ return __builtin_erfc(__x); })
#elif defined(__CRT_HAVE_erfc)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,erfc,(double __x),(__x))
#elif defined(__CRT_HAVE___erfc)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,erfc,(double __x),__erfc,(__x))
#endif /* ... */
#if __has_builtin(__builtin_lgamma) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgamma)
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,lgamma,(double __x),{ return __builtin_lgamma(__x); })
#elif __has_builtin(__builtin_gamma) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_gamma)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,lgamma,(double __x),gamma,{ return __builtin_gamma(__x); })
#elif defined(__CRT_HAVE_lgamma)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,lgamma,(double __x),(__x))
#elif defined(__CRT_HAVE_gamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,lgamma,(double __x),gamma,(__x))
#elif defined(__CRT_HAVE___lgamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,lgamma,(double __x),__lgamma,(__x))
#elif defined(__CRT_HAVE___gamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,lgamma,(double __x),__gamma,(__x))
#endif /* ... */
#if __has_builtin(__builtin_erff) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erff)
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,erff,(float __x),{ return __builtin_erff(__x); })
#elif defined(__CRT_HAVE_erff)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,erff,(float __x),(__x))
#elif defined(__CRT_HAVE___erff)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,erff,(float __x),__erff,(__x))
#elif defined(__CRT_HAVE_erf) || defined(__CRT_HAVE___erf)
__NAMESPACE_STD_END
#include <libc/local/math/erff.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(erff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL erff)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(erff))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_erfcf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erfcf)
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,erfcf,(float __x),{ return __builtin_erfcf(__x); })
#elif defined(__CRT_HAVE_erfcf)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,erfcf,(float __x),(__x))
#elif defined(__CRT_HAVE___erfcf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,erfcf,(float __x),__erfcf,(__x))
#elif defined(__CRT_HAVE_erfc) || defined(__CRT_HAVE___erfc)
__NAMESPACE_STD_END
#include <libc/local/math/erfcf.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(erfcf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL erfcf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(erfcf))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_lgammaf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgammaf)
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,lgammaf,(float __x),{ return __builtin_lgammaf(__x); })
#elif __has_builtin(__builtin_gammaf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_gammaf)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,lgammaf,(float __x),gammaf,{ return __builtin_gammaf(__x); })
#elif defined(__CRT_HAVE_lgammaf)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,lgammaf,(float __x),(__x))
#elif defined(__CRT_HAVE_gammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,lgammaf,(float __x),gammaf,(__x))
#elif defined(__CRT_HAVE___lgammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,lgammaf,(float __x),__lgammaf,(__x))
#elif defined(__CRT_HAVE___gammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,lgammaf,(float __x),__gammaf,(__x))
#elif defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE_gamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma)
__NAMESPACE_STD_END
#include <libc/local/math/lgammaf.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(lgammaf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL lgammaf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammaf))(__x); })
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_erfl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erfl)
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erfl,(__LONGDOUBLE __x),{ return __builtin_erfl(__x); })
#elif defined(__CRT_HAVE_erfl)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erfl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___erfl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erfl,(__LONGDOUBLE __x),__erfl,(__x))
#elif defined(__CRT_HAVE_erf) || defined(__CRT_HAVE___erf)
__NAMESPACE_STD_END
#include <libc/local/math/erfl.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(erfl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL erfl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(erfl))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_erfcl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erfcl)
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erfcl,(__LONGDOUBLE __x),{ return __builtin_erfcl(__x); })
#elif defined(__CRT_HAVE_erfcl)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erfcl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___erfcl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erfcl,(__LONGDOUBLE __x),__erfcl,(__x))
#elif defined(__CRT_HAVE_erfc) || defined(__CRT_HAVE___erfc)
__NAMESPACE_STD_END
#include <libc/local/math/erfcl.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(erfcl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL erfcl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(erfcl))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_lgammal) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgammal)
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgammal,(__LONGDOUBLE __x),{ return __builtin_lgammal(__x); })
#elif __has_builtin(__builtin_gammal) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_gammal)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgammal,(__LONGDOUBLE __x),gammal,{ return __builtin_gammal(__x); })
#elif defined(__CRT_HAVE_lgammal)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgammal,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_gammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgammal,(__LONGDOUBLE __x),gammal,(__x))
#elif defined(__CRT_HAVE___lgammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgammal,(__LONGDOUBLE __x),__lgammal,(__x))
#elif defined(__CRT_HAVE___gammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgammal,(__LONGDOUBLE __x),__gammal,(__x))
#elif defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE_gamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma)
__NAMESPACE_STD_END
#include <libc/local/math/lgammal.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(lgammal, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL lgammal)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammal))(__x); })
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN || __USE_ISOC99 */
#ifdef __USE_ISOC99
#if __has_builtin(__builtin_tgamma) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tgamma)
/* True gamma function */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,tgamma,(double __x),{ return __builtin_tgamma(__x); })
#elif defined(__CRT_HAVE_tgamma)
/* True gamma function */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,tgamma,(double __x),(__x))
#elif defined(__CRT_HAVE___tgamma)
/* True gamma function */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,tgamma,(double __x),__tgamma,(__x))
#endif /* ... */
#if __has_builtin(__builtin_tgammaf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tgammaf)
/* True gamma function */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,tgammaf,(float __x),{ return __builtin_tgammaf(__x); })
#elif defined(__CRT_HAVE_tgammaf)
/* True gamma function */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,tgammaf,(float __x),(__x))
#elif defined(__CRT_HAVE___tgammaf)
/* True gamma function */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,tgammaf,(float __x),__tgammaf,(__x))
#elif defined(__CRT_HAVE_tgamma) || defined(__CRT_HAVE___tgamma)
__NAMESPACE_STD_END
#include <libc/local/math/tgammaf.h>
__NAMESPACE_STD_BEGIN
/* True gamma function */
__NAMESPACE_LOCAL_USING_OR_IMPL(tgammaf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL tgammaf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tgammaf))(__x); })
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_tgammal) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tgammal)
/* True gamma function */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tgammal,(__LONGDOUBLE __x),{ return __builtin_tgammal(__x); })
#elif defined(__CRT_HAVE_tgammal)
/* True gamma function */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tgammal,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___tgammal)
/* True gamma function */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tgammal,(__LONGDOUBLE __x),__tgammal,(__x))
#elif defined(__CRT_HAVE_tgamma) || defined(__CRT_HAVE___tgamma)
__NAMESPACE_STD_END
#include <libc/local/math/tgammal.h>
__NAMESPACE_STD_BEGIN
/* True gamma function */
__NAMESPACE_LOCAL_USING_OR_IMPL(tgammal, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL tgammal)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tgammal))(__x); })
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#if __has_builtin(__builtin_rint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,rint,(double __x),{ return __builtin_rint(__x); })
#elif __has_builtin(__builtin_nearbyint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nearbyint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,rint,(double __x),nearbyint,{ return __builtin_nearbyint(__x); })
#elif defined(__CRT_HAVE_rint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,rint,(double __x),(__x))
#elif defined(__CRT_HAVE_nearbyint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,rint,(double __x),nearbyint,(__x))
#elif defined(__CRT_HAVE___rint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,rint,(double __x),__rint,(__x))
#elif defined(__CRT_HAVE___nearbyint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,rint,(double __x),__nearbyint,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/rint.h>
__NAMESPACE_STD_BEGIN
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__NAMESPACE_LOCAL_USING_OR_IMPL(rint, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL rint)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rint))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_nextafter) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nextafter)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nextafter,(double __x, double __y),{ return __builtin_nextafter(__x, __y); })
#elif __has_builtin(__builtin_nexttoward) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nexttoward)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nextafter,(double __x, double __y),nexttoward,{ return __builtin_nexttoward(__x); })
#elif defined(__CRT_HAVE_nextafter)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nextafter,(double __x, double __y),(__x,__y))
#elif defined(__CRT_HAVE_nexttoward)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nextafter,(double __x, double __y),nexttoward,(__x,__y))
#elif defined(__CRT_HAVE___nextafter)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nextafter,(double __x, double __y),__nextafter,(__x,__y))
#elif defined(__CRT_HAVE__nextafter)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nextafter,(double __x, double __y),_nextafter,(__x,__y))
#elif defined(__CRT_HAVE___nexttoward)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nextafter,(double __x, double __y),__nexttoward,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/nextafter.h>
__NAMESPACE_STD_BEGIN
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__NAMESPACE_LOCAL_USING_OR_IMPL(nextafter, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL nextafter)(double __x, double __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nextafter))(__x, __y); })
#endif /* ... */
#if __has_builtin(__builtin_remainder) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainder)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,remainder,(double __x, double __p),{ return __builtin_remainder(__x, __p); })
#elif __has_builtin(__builtin_drem) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_drem)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,remainder,(double __x, double __p),drem,{ return __builtin_drem(__x, __p); })
#elif defined(__CRT_HAVE_remainder)
/* Return the remainder of integer division `x / p' with infinite precision */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,remainder,(double __x, double __p),(__x,__p))
#elif defined(__CRT_HAVE_drem)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,remainder,(double __x, double __p),drem,(__x,__p))
#elif defined(__CRT_HAVE___remainder)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,remainder,(double __x, double __p),__remainder,(__x,__p))
#elif defined(__CRT_HAVE___drem)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,remainder,(double __x, double __p),__drem,(__x,__p))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/remainder.h>
__NAMESPACE_STD_BEGIN
/* Return the remainder of integer division `x / p' with infinite precision */
__NAMESPACE_LOCAL_USING_OR_IMPL(remainder, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL remainder)(double __x, double __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainder))(__x, __p); })
#endif /* ... */
#if __has_builtin(__builtin_ilogb) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ilogb)
/* Return the binary exponent of `x', which must be nonzero */
__CEIDECLARE(__ATTR_WUNUSED,int,__NOTHROW,ilogb,(double __x),{ return __builtin_ilogb(__x); })
#elif defined(__CRT_HAVE_ilogb)
/* Return the binary exponent of `x', which must be nonzero */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW,ilogb,(double __x),(__x))
#elif defined(__CRT_HAVE___ilogb)
/* Return the binary exponent of `x', which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,ilogb,(double __x),__ilogb,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/ilogb.h>
__NAMESPACE_STD_BEGIN
/* Return the binary exponent of `x', which must be nonzero */
__NAMESPACE_LOCAL_USING_OR_IMPL(ilogb, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED int __NOTHROW(__LIBCCALL ilogb)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ilogb))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_rintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,rintf,(float __x),{ return __builtin_rintf(__x); })
#elif __has_builtin(__builtin_nearbyintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nearbyintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,rintf,(float __x),nearbyintf,{ return __builtin_nearbyintf(__x); })
#elif defined(__CRT_HAVE_rintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,rintf,(float __x),(__x))
#elif defined(__CRT_HAVE_nearbyintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,rintf,(float __x),nearbyintf,(__x))
#elif defined(__CRT_HAVE___rintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,rintf,(float __x),__rintf,(__x))
#elif defined(__CRT_HAVE___nearbyintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,rintf,(float __x),__nearbyintf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE_nearbyint) || defined(__CRT_HAVE___rint) || defined(__CRT_HAVE___nearbyint) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/rintf.h>
__NAMESPACE_STD_BEGIN
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__NAMESPACE_LOCAL_USING_OR_IMPL(rintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL rintf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rintf))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_nextafterf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nextafterf)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nextafterf,(float __x, float __y),{ return __builtin_nextafterf(__x, __y); })
#elif __has_builtin(__builtin_nexttowardf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nexttowardf)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nextafterf,(float __x, float __y),nexttowardf,{ return __builtin_nexttowardf(__x); })
#elif defined(__CRT_HAVE_nextafterf)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nextafterf,(float __x, float __y),(__x,__y))
#elif defined(__CRT_HAVE_nexttowardf)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nextafterf,(float __x, float __y),nexttowardf,(__x,__y))
#elif defined(__CRT_HAVE___nextafterf)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nextafterf,(float __x, float __y),__nextafterf,(__x,__y))
#elif defined(__CRT_HAVE___nexttowardf)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nextafterf,(float __x, float __y),__nexttowardf,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE___nexttoward) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/nextafterf.h>
__NAMESPACE_STD_BEGIN
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__NAMESPACE_LOCAL_USING_OR_IMPL(nextafterf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL nextafterf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nextafterf))(__x, __y); })
#endif /* ... */
#if __has_builtin(__builtin_remainderf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainderf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,remainderf,(float __x, float __p),{ return __builtin_remainderf(__x, __p); })
#elif __has_builtin(__builtin_dremf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_dremf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,remainderf,(float __x, float __p),dremf,{ return __builtin_dremf(__x, __p); })
#elif defined(__CRT_HAVE_remainderf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,remainderf,(float __x, float __p),(__x,__p))
#elif defined(__CRT_HAVE_dremf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,remainderf,(float __x, float __p),dremf,(__x,__p))
#elif defined(__CRT_HAVE___remainderf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,remainderf,(float __x, float __p),__remainderf,(__x,__p))
#elif defined(__CRT_HAVE___dremf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,remainderf,(float __x, float __p),__dremf,(__x,__p))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE___drem) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/remainderf.h>
__NAMESPACE_STD_BEGIN
/* Return the remainder of integer division `x / p' with infinite precision */
__NAMESPACE_LOCAL_USING_OR_IMPL(remainderf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL remainderf)(float __x, float __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainderf))(__x, __p); })
#endif /* ... */
#if __has_builtin(__builtin_ilogbf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ilogbf)
/* Return the binary exponent of `x', which must be nonzero */
__CEIDECLARE(__ATTR_WUNUSED,int,__NOTHROW,ilogbf,(float __x),{ return __builtin_ilogbf(__x); })
#elif defined(__CRT_HAVE_ilogbf)
/* Return the binary exponent of `x', which must be nonzero */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW,ilogbf,(float __x),(__x))
#elif defined(__CRT_HAVE___ilogbf)
/* Return the binary exponent of `x', which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,ilogbf,(float __x),__ilogbf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_ilogb) || defined(__CRT_HAVE___ilogb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/ilogbf.h>
__NAMESPACE_STD_BEGIN
/* Return the binary exponent of `x', which must be nonzero */
__NAMESPACE_LOCAL_USING_OR_IMPL(ilogbf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED int __NOTHROW(__LIBCCALL ilogbf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ilogbf))(__x); })
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_rintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,rintl,(__LONGDOUBLE __x),{ return __builtin_rintl(__x); })
#elif __has_builtin(__builtin_nearbyintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nearbyintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,rintl,(__LONGDOUBLE __x),nearbyintl,{ return __builtin_nearbyintl(__x); })
#elif defined(__CRT_HAVE_rintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,rintl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_nearbyintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,rintl,(__LONGDOUBLE __x),nearbyintl,(__x))
#elif defined(__CRT_HAVE___rintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,rintl,(__LONGDOUBLE __x),__rintl,(__x))
#elif defined(__CRT_HAVE___nearbyintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,rintl,(__LONGDOUBLE __x),__nearbyintl,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE_nearbyint) || defined(__CRT_HAVE___rint) || defined(__CRT_HAVE___nearbyint) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/rintl.h>
__NAMESPACE_STD_BEGIN
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__NAMESPACE_LOCAL_USING_OR_IMPL(rintl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL rintl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rintl))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_nextafterl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nextafterl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),{ return __builtin_nextafterl(__x, __y); })
#elif __has_builtin(__builtin_nexttowardl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nexttowardl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),nexttowardl,{ return __builtin_nexttowardl(__x); })
#elif defined(__CRT_HAVE_nextafterl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__CRT_HAVE_nexttowardl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),nexttowardl,(__x,__y))
#elif defined(__CRT_HAVE___nextafterl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__nextafterl,(__x,__y))
#elif defined(__CRT_HAVE___nexttowardl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__nexttowardl,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE___nexttoward) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/nextafterl.h>
__NAMESPACE_STD_BEGIN
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__NAMESPACE_LOCAL_USING_OR_IMPL(nextafterl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL nextafterl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nextafterl))(__x, __y); })
#endif /* ... */
#if __has_builtin(__builtin_remainderl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainderl)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remainderl,(__LONGDOUBLE __x, __LONGDOUBLE __p),{ return __builtin_remainderl(__x, __p); })
#elif __has_builtin(__builtin_dreml) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_dreml)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remainderl,(__LONGDOUBLE __x, __LONGDOUBLE __p),dreml,{ return __builtin_dreml(__x, __p); })
#elif defined(__CRT_HAVE_remainderl)
/* Return the remainder of integer division `x / p' with infinite precision */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remainderl,(__LONGDOUBLE __x, __LONGDOUBLE __p),(__x,__p))
#elif defined(__CRT_HAVE_dreml)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remainderl,(__LONGDOUBLE __x, __LONGDOUBLE __p),dreml,(__x,__p))
#elif defined(__CRT_HAVE___remainderl)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remainderl,(__LONGDOUBLE __x, __LONGDOUBLE __p),__remainderl,(__x,__p))
#elif defined(__CRT_HAVE___dreml)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remainderl,(__LONGDOUBLE __x, __LONGDOUBLE __p),__dreml,(__x,__p))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE___drem) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/remainderl.h>
__NAMESPACE_STD_BEGIN
/* Return the remainder of integer division `x / p' with infinite precision */
__NAMESPACE_LOCAL_USING_OR_IMPL(remainderl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL remainderl)(__LONGDOUBLE __x, __LONGDOUBLE __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainderl))(__x, __p); })
#endif /* ... */
#if __has_builtin(__builtin_ilogbl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ilogbl)
/* Return the binary exponent of `x', which must be nonzero */
__CEIDECLARE(__ATTR_WUNUSED,int,__NOTHROW,ilogbl,(__LONGDOUBLE __x),{ return __builtin_ilogbl(__x); })
#elif defined(__CRT_HAVE_ilogbl)
/* Return the binary exponent of `x', which must be nonzero */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW,ilogbl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___ilogbl)
/* Return the binary exponent of `x', which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,ilogbl,(__LONGDOUBLE __x),__ilogbl,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_ilogb) || defined(__CRT_HAVE___ilogb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/ilogbl.h>
__NAMESPACE_STD_BEGIN
/* Return the binary exponent of `x', which must be nonzero */
__NAMESPACE_LOCAL_USING_OR_IMPL(ilogbl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED int __NOTHROW(__LIBCCALL ilogbl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ilogbl))(__x); })
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

#ifdef __USE_ISOC99
#if __has_builtin(__builtin_nexttoward) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nexttoward)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nexttoward,(double __x, __LONGDOUBLE __y),{ return __builtin_nexttoward(__x, __y); })
#elif defined(__CRT_HAVE_nexttoward)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nexttoward,(double __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__CRT_HAVE___nexttoward)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nexttoward,(double __x, __LONGDOUBLE __y),__nexttoward,(__x,__y))
#elif defined(__CRT_HAVE_nextafterl) || defined(__CRT_HAVE_nexttowardl) || defined(__CRT_HAVE___nextafterl) || defined(__CRT_HAVE___nexttowardl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/nexttoward.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(nexttoward, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL nexttoward)(double __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nexttoward))(__x, __y); })
#endif /* ... */
#if __has_builtin(__builtin_scalbn) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbn)
/* Return `x' times (2 to the Nth power) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,scalbn,(double __x, int __n),{ return __builtin_scalbn(__x, __n); })
#elif defined(__CRT_HAVE_scalbn)
/* Return `x' times (2 to the Nth power) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,scalbn,(double __x, int __n),(__x,__n))
#elif defined(__CRT_HAVE___scalbn)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,scalbn,(double __x, int __n),__scalbn,(__x,__n))
#elif defined(__CRT_HAVE_scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,scalbn,(double __x, int __n),scalbln,(__x,__n))
#elif defined(__CRT_HAVE___scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,scalbn,(double __x, int __n),__scalbln,(__x,__n))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/scalbn.h>
__NAMESPACE_STD_BEGIN
/* Return `x' times (2 to the Nth power) */
__NAMESPACE_LOCAL_USING_OR_IMPL(scalbn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL scalbn)(double __x, int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbn))(__x, __n); })
#endif /* ... */
#if __has_builtin(__builtin_scalbln) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbln)
/* Return `x' times (2 to the Nth power) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,scalbln,(double __x, long int __n),{ return __builtin_scalbln(__x, __n); })
#elif defined(__CRT_HAVE_scalbln)
/* Return `x' times (2 to the Nth power) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,scalbln,(double __x, long int __n),(__x,__n))
#elif defined(__CRT_HAVE___scalbln)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,scalbln,(double __x, long int __n),__scalbln,(__x,__n))
#elif defined(__CRT_HAVE_scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,scalbln,(double __x, long int __n),scalbn,(__x,__n))
#elif defined(__CRT_HAVE___scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,scalbln,(double __x, long int __n),__scalbn,(__x,__n))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/scalbln.h>
__NAMESPACE_STD_BEGIN
/* Return `x' times (2 to the Nth power) */
__NAMESPACE_LOCAL_USING_OR_IMPL(scalbln, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL scalbln)(double __x, long int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbln))(__x, __n); })
#endif /* ... */
#if __has_builtin(__builtin_nearbyint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nearbyint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode
 * This function is similar to `rint()', but does not tend to produce wrong results (so use this one) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nearbyint,(double __x),{ return __builtin_nearbyint(__x); })
#elif defined(__CRT_HAVE_nearbyint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode
 * This function is similar to `rint()', but does not tend to produce wrong results (so use this one) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nearbyint,(double __x),(__x))
#elif defined(__CRT_HAVE___nearbyint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode
 * This function is similar to `rint()', but does not tend to produce wrong results (so use this one) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nearbyint,(double __x),__nearbyint,(__x))
#elif defined(__CRT_HAVE_rint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode
 * This function is similar to `rint()', but does not tend to produce wrong results (so use this one) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nearbyint,(double __x),rint,(__x))
#elif defined(__CRT_HAVE___rint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode
 * This function is similar to `rint()', but does not tend to produce wrong results (so use this one) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,nearbyint,(double __x),__rint,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/rint.h>
__NAMESPACE_STD_BEGIN
/* Return the integer nearest `x' in the direction of the prevailing rounding mode
 * This function is similar to `rint()', but does not tend to produce wrong results (so use this one) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL nearbyint)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rint))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_round) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_round)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,round,(double __x),{ return __builtin_round(__x); })
#elif defined(__CRT_HAVE_round)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,round,(double __x),(__x))
#elif defined(__CRT_HAVE___round)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,round,(double __x),__round,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/round.h>
__NAMESPACE_STD_BEGIN
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__NAMESPACE_LOCAL_USING_OR_IMPL(round, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL round)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(round))(__x); })
#endif /* !... */
#if __has_builtin(__builtin_trunc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_trunc)
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,trunc,(double __x),{ return __builtin_trunc(__x); })
#elif defined(__CRT_HAVE_trunc)
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,trunc,(double __x),(__x))
#elif defined(__CRT_HAVE___trunc)
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,trunc,(double __x),__trunc,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/trunc.h>
__NAMESPACE_STD_BEGIN
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__NAMESPACE_LOCAL_USING_OR_IMPL(trunc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL trunc)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(trunc))(__x); })
#endif /* !... */
#if __has_builtin(__builtin_remquo) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remquo)
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__CEIDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3)),double,__NOTHROW,remquo,(double __x, double __y, int *__pquo),{ return __builtin_remquo(__x, __y, __pquo); })
#elif defined(__CRT_HAVE_remquo)
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3)),double,__NOTHROW,remquo,(double __x, double __y, int *__pquo),(__x,__y,__pquo))
#elif defined(__CRT_HAVE___remquo)
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),double,__NOTHROW,remquo,(double __x, double __y, int *__pquo),__remquo,(__x,__y,__pquo))
#endif /* ... */
#if __has_builtin(__builtin_lrint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lrint)
/* Round `x' to nearest integral value according to current rounding direction */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lrint,(double __x),{ return __builtin_lrint(__x); })
#elif defined(__CRT_HAVE_lrint)
/* Round `x' to nearest integral value according to current rounding direction */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lrint,(double __x),(__x))
#elif defined(__CRT_HAVE___lrint)
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lrint,(double __x),__lrint,(__x))
#elif defined(__CRT_HAVE_llrint) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lrint,(double __x),llrint,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/lrint.h>
__NAMESPACE_STD_BEGIN
/* Round `x' to nearest integral value according to current rounding direction */
__NAMESPACE_LOCAL_USING_OR_IMPL(lrint, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL lrint)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lrint))(__x); })
#endif /* !... */
#if __has_builtin(__builtin_lround) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lround)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lround,(double __x),{ return __builtin_lround(__x); })
#elif defined(__CRT_HAVE_lround)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lround,(double __x),(__x))
#elif defined(__CRT_HAVE___lround)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lround,(double __x),__lround,(__x))
#elif defined(__CRT_HAVE_llround) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lround,(double __x),llround,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/lround.h>
__NAMESPACE_STD_BEGIN
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__NAMESPACE_LOCAL_USING_OR_IMPL(lround, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL lround)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lround))(__x); })
#endif /* !... */
#if __has_builtin(__builtin_fdim) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fdim)
/* Return positive difference between `x' and `y' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fdim,(double __x, double __y),{ return __builtin_fdim(__x, __y); })
#elif defined(__CRT_HAVE_fdim)
/* Return positive difference between `x' and `y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fdim,(double __x, double __y),(__x,__y))
#elif defined(__CRT_HAVE___fdim)
/* Return positive difference between `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fdim,(double __x, double __y),__fdim,(__x,__y))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/fdim.h>
__NAMESPACE_STD_BEGIN
/* Return positive difference between `x' and `y' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fdim, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL fdim)(double __x, double __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fdim))(__x, __y); })
#endif /* !... */
#if __has_builtin(__builtin_fmax) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmax)
/* Return maximum numeric value from `x' and `y' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fmax,(double __x, double __y),{ return __builtin_fmax(__x, __y); })
#elif defined(__CRT_HAVE_fmax)
/* Return maximum numeric value from `x' and `y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fmax,(double __x, double __y),(__x,__y))
#elif defined(__CRT_HAVE___fmax)
/* Return maximum numeric value from `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fmax,(double __x, double __y),__fmax,(__x,__y))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/fmax.h>
__NAMESPACE_STD_BEGIN
/* Return maximum numeric value from `x' and `y' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fmax, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL fmax)(double __x, double __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmax))(__x, __y); })
#endif /* !... */
#if __has_builtin(__builtin_fmin) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmin)
/* Return minimum numeric value from `x' and `y' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fmin,(double __x, double __y),{ return __builtin_fmin(__x, __y); })
#elif defined(__CRT_HAVE_fmin)
/* Return minimum numeric value from `x' and `y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fmin,(double __x, double __y),(__x,__y))
#elif defined(__CRT_HAVE___fmin)
/* Return minimum numeric value from `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fmin,(double __x, double __y),__fmin,(__x,__y))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/fmin.h>
__NAMESPACE_STD_BEGIN
/* Return minimum numeric value from `x' and `y' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fmin, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL fmin)(double __x, double __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmin))(__x, __y); })
#endif /* !... */
#if __has_builtin(__builtin_fma) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fma)
/* Multiply-add function computed as a ternary operation */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fma,(double __x, double __y, double __z),{ return __builtin_fma(__x, __y, __z); })
#elif defined(__CRT_HAVE_fma)
/* Multiply-add function computed as a ternary operation */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fma,(double __x, double __y, double __z),(__x,__y,__z))
#elif defined(__CRT_HAVE___fma)
/* Multiply-add function computed as a ternary operation */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,fma,(double __x, double __y, double __z),__fma,(__x,__y,__z))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/fma.h>
__NAMESPACE_STD_BEGIN
/* Multiply-add function computed as a ternary operation */
__NAMESPACE_LOCAL_USING_OR_IMPL(fma, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL fma)(double __x, double __y, double __z) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fma))(__x, __y, __z); })
#endif /* !... */
#ifdef __COMPILER_HAVE_LONGLONG
#if __has_builtin(__builtin_llrint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llrint)
/* Round `x' to nearest integral value according to current rounding direction */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrint,(double __x),{ return __builtin_llrint(__x); })
#elif defined(__CRT_HAVE_llrint)
/* Round `x' to nearest integral value according to current rounding direction */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrint,(double __x),(__x))
#elif defined(__CRT_HAVE___llrint)
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrint,(double __x),__llrint,(__x))
#elif defined(__CRT_HAVE_lrint) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrint,(double __x),lrint,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/llrint.h>
__NAMESPACE_STD_BEGIN
/* Round `x' to nearest integral value according to current rounding direction */
__NAMESPACE_LOCAL_USING_OR_IMPL(llrint, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL llrint)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llrint))(__x); })
#endif /* !... */
#if __has_builtin(__builtin_llround) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llround)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llround,(double __x),{ return __builtin_llround(__x); })
#elif defined(__CRT_HAVE_llround)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llround,(double __x),(__x))
#elif defined(__CRT_HAVE___llround)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llround,(double __x),__llround,(__x))
#elif defined(__CRT_HAVE_lround) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llround,(double __x),lround,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/llround.h>
__NAMESPACE_STD_BEGIN
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__NAMESPACE_LOCAL_USING_OR_IMPL(llround, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL llround)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llround))(__x); })
#endif /* !... */
#endif /* __COMPILER_HAVE_LONGLONG */
#if __has_builtin(__builtin_nexttowardf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nexttowardf)
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nexttowardf,(float __x, __LONGDOUBLE __y),{ return __builtin_nexttowardf(__x, __y); })
#elif defined(__CRT_HAVE_nexttowardf)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nexttowardf,(float __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__CRT_HAVE___nexttowardf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nexttowardf,(float __x, __LONGDOUBLE __y),__nexttowardf,(__x,__y))
#elif ((defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)) && defined(__IEEE854_LONG_DOUBLE_TYPE__)) || defined(__CRT_HAVE_nextafterl) || defined(__CRT_HAVE_nexttowardl) || defined(__CRT_HAVE___nextafterl) || defined(__CRT_HAVE___nexttowardl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE___nexttoward) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/nexttowardf.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(nexttowardf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL nexttowardf)(float __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nexttowardf))(__x, __y); })
#endif /* ... */
#if __has_builtin(__builtin_scalbnf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbnf)
/* Return `x' times (2 to the Nth power) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbnf,(float __x, int __n),{ return __builtin_scalbnf(__x, __n); })
#elif defined(__CRT_HAVE_scalbnf)
/* Return `x' times (2 to the Nth power) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbnf,(float __x, int __n),(__x,__n))
#elif defined(__CRT_HAVE___scalbnf)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbnf,(float __x, int __n),__scalbnf,(__x,__n))
#elif defined(__CRT_HAVE_scalblnf) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbnf,(float __x, int __n),scalblnf,(__x,__n))
#elif defined(__CRT_HAVE___scalblnf) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbnf,(float __x, int __n),__scalblnf,(__x,__n))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_scalbn) || defined(__CRT_HAVE___scalbn) || (defined(__CRT_HAVE_scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/scalbnf.h>
__NAMESPACE_STD_BEGIN
/* Return `x' times (2 to the Nth power) */
__NAMESPACE_LOCAL_USING_OR_IMPL(scalbnf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL scalbnf)(float __x, int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbnf))(__x, __n); })
#endif /* ... */
#if __has_builtin(__builtin_scalblnf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalblnf)
/* Return `x' times (2 to the Nth power) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalblnf,(float __x, long int __n),{ return __builtin_scalblnf(__x, __n); })
#elif defined(__CRT_HAVE_scalblnf)
/* Return `x' times (2 to the Nth power) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalblnf,(float __x, long int __n),(__x,__n))
#elif defined(__CRT_HAVE___scalblnf)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalblnf,(float __x, long int __n),__scalblnf,(__x,__n))
#elif defined(__CRT_HAVE_scalbnf) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalblnf,(float __x, long int __n),scalbnf,(__x,__n))
#elif defined(__CRT_HAVE___scalbnf) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalblnf,(float __x, long int __n),__scalbnf,(__x,__n))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_scalbln) || defined(__CRT_HAVE___scalbln) || (defined(__CRT_HAVE_scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/scalblnf.h>
__NAMESPACE_STD_BEGIN
/* Return `x' times (2 to the Nth power) */
__NAMESPACE_LOCAL_USING_OR_IMPL(scalblnf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL scalblnf)(float __x, long int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalblnf))(__x, __n); })
#endif /* ... */
#if __has_builtin(__builtin_nearbyintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nearbyintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode
 * This function is similar to `rint()', but does not tend to produce wrong results (so use this one) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nearbyintf,(float __x),{ return __builtin_nearbyintf(__x); })
#elif defined(__CRT_HAVE_nearbyintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode
 * This function is similar to `rint()', but does not tend to produce wrong results (so use this one) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nearbyintf,(float __x),(__x))
#elif defined(__CRT_HAVE___nearbyintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode
 * This function is similar to `rint()', but does not tend to produce wrong results (so use this one) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nearbyintf,(float __x),__nearbyintf,(__x))
#elif defined(__CRT_HAVE_rintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode
 * This function is similar to `rint()', but does not tend to produce wrong results (so use this one) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nearbyintf,(float __x),rintf,(__x))
#elif defined(__CRT_HAVE___rintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode
 * This function is similar to `rint()', but does not tend to produce wrong results (so use this one) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nearbyintf,(float __x),__rintf,(__x))
#elif defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
__NAMESPACE_STD_END
#include <libc/local/math/rintf.h>
__NAMESPACE_STD_BEGIN
/* Return the integer nearest `x' in the direction of the prevailing rounding mode
 * This function is similar to `rint()', but does not tend to produce wrong results (so use this one) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL nearbyintf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rintf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_roundf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_roundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,roundf,(float __x),{ return __builtin_roundf(__x); })
#elif defined(__CRT_HAVE_roundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,roundf,(float __x),(__x))
#elif defined(__CRT_HAVE___roundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,roundf,(float __x),__roundf,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/roundf.h>
__NAMESPACE_STD_BEGIN
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__NAMESPACE_LOCAL_USING_OR_IMPL(roundf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL roundf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(roundf))(__x); })
#endif /* !... */
#if __has_builtin(__builtin_truncf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_truncf)
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,truncf,(float __x),{ return __builtin_truncf(__x); })
#elif defined(__CRT_HAVE_truncf)
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,truncf,(float __x),(__x))
#elif defined(__CRT_HAVE___truncf)
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,truncf,(float __x),__truncf,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/truncf.h>
__NAMESPACE_STD_BEGIN
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__NAMESPACE_LOCAL_USING_OR_IMPL(truncf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL truncf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(truncf))(__x); })
#endif /* !... */
#if __has_builtin(__builtin_remquof) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remquof)
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__CEIDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3)),float,__NOTHROW,remquof,(float __x, float __y, int *__pquo),{ return __builtin_remquof(__x, __y, __pquo); })
#elif defined(__CRT_HAVE_remquof)
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3)),float,__NOTHROW,remquof,(float __x, float __y, int *__pquo),(__x,__y,__pquo))
#elif defined(__CRT_HAVE___remquof)
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),float,__NOTHROW,remquof,(float __x, float __y, int *__pquo),__remquof,(__x,__y,__pquo))
#elif defined(__CRT_HAVE_remquo) || defined(__CRT_HAVE___remquo)
__NAMESPACE_STD_END
#include <libc/local/math/remquof.h>
__NAMESPACE_STD_BEGIN
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__NAMESPACE_LOCAL_USING_OR_IMPL(remquof, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) float __NOTHROW(__LIBCCALL remquof)(float __x, float __y, int *__pquo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remquof))(__x, __y, __pquo); })
#endif /* ... */
#if __has_builtin(__builtin_lrintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lrintf)
/* Round `x' to nearest integral value according to current rounding direction */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lrintf,(float __x),{ return __builtin_lrintf(__x); })
#elif defined(__CRT_HAVE_lrintf)
/* Round `x' to nearest integral value according to current rounding direction */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lrintf,(float __x),(__x))
#elif defined(__CRT_HAVE___lrintf)
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lrintf,(float __x),__lrintf,(__x))
#elif defined(__CRT_HAVE_llrintf) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lrintf,(float __x),llrintf,(__x))
#elif defined(__CRT_HAVE___llrintf) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lrintf,(float __x),__llrintf,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/lrintf.h>
__NAMESPACE_STD_BEGIN
/* Round `x' to nearest integral value according to current rounding direction */
__NAMESPACE_LOCAL_USING_OR_IMPL(lrintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL lrintf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lrintf))(__x); })
#endif /* !... */
#if __has_builtin(__builtin_lroundf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lroundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lroundf,(float __x),{ return __builtin_lroundf(__x); })
#elif defined(__CRT_HAVE_lroundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lroundf,(float __x),(__x))
#elif defined(__CRT_HAVE___lroundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lroundf,(float __x),__lroundf,(__x))
#elif defined(__CRT_HAVE_llroundf) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lroundf,(float __x),llroundf,(__x))
#elif defined(__CRT_HAVE___llroundf) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lroundf,(float __x),__llroundf,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/lroundf.h>
__NAMESPACE_STD_BEGIN
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__NAMESPACE_LOCAL_USING_OR_IMPL(lroundf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL lroundf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lroundf))(__x); })
#endif /* !... */
#if __has_builtin(__builtin_fdimf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fdimf)
/* Return positive difference between `x' and `y' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fdimf,(float __x, float __y),{ return __builtin_fdimf(__x, __y); })
#elif defined(__CRT_HAVE_fdimf)
/* Return positive difference between `x' and `y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fdimf,(float __x, float __y),(__x,__y))
#elif defined(__CRT_HAVE___fdimf)
/* Return positive difference between `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fdimf,(float __x, float __y),__fdimf,(__x,__y))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/fdimf.h>
__NAMESPACE_STD_BEGIN
/* Return positive difference between `x' and `y' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fdimf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL fdimf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fdimf))(__x, __y); })
#endif /* !... */
#if __has_builtin(__builtin_fmaxf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmaxf)
/* Return maximum numeric value from `x' and `y' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fmaxf,(float __x, float __y),{ return __builtin_fmaxf(__x, __y); })
#elif defined(__CRT_HAVE_fmaxf)
/* Return maximum numeric value from `x' and `y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fmaxf,(float __x, float __y),(__x,__y))
#elif defined(__CRT_HAVE___fmaxf)
/* Return maximum numeric value from `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fmaxf,(float __x, float __y),__fmaxf,(__x,__y))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/fmaxf.h>
__NAMESPACE_STD_BEGIN
/* Return maximum numeric value from `x' and `y' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fmaxf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL fmaxf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmaxf))(__x, __y); })
#endif /* !... */
#if __has_builtin(__builtin_fminf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fminf)
/* Return minimum numeric value from `x' and `y' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fminf,(float __x, float __y),{ return __builtin_fminf(__x, __y); })
#elif defined(__CRT_HAVE_fminf)
/* Return minimum numeric value from `x' and `y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fminf,(float __x, float __y),(__x,__y))
#elif defined(__CRT_HAVE___fminf)
/* Return minimum numeric value from `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fminf,(float __x, float __y),__fminf,(__x,__y))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/fminf.h>
__NAMESPACE_STD_BEGIN
/* Return minimum numeric value from `x' and `y' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fminf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL fminf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fminf))(__x, __y); })
#endif /* !... */
#if __has_builtin(__builtin_fmaf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmaf)
/* Multiply-add function computed as a ternary operation */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fmaf,(float __x, float __y, float __z),{ return __builtin_fmaf(__x, __y, __z); })
#elif defined(__CRT_HAVE_fmaf)
/* Multiply-add function computed as a ternary operation */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fmaf,(float __x, float __y, float __z),(__x,__y,__z))
#elif defined(__CRT_HAVE___fmaf)
/* Multiply-add function computed as a ternary operation */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fmaf,(float __x, float __y, float __z),__fmaf,(__x,__y,__z))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/fmaf.h>
__NAMESPACE_STD_BEGIN
/* Multiply-add function computed as a ternary operation */
__NAMESPACE_LOCAL_USING_OR_IMPL(fmaf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL fmaf)(float __x, float __y, float __z) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmaf))(__x, __y, __z); })
#endif /* !... */
#ifdef __COMPILER_HAVE_LONGLONG
#if __has_builtin(__builtin_llrintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llrintf)
/* Round `x' to nearest integral value according to current rounding direction */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrintf,(float __x),{ return __builtin_llrintf(__x); })
#elif defined(__CRT_HAVE_llrintf)
/* Round `x' to nearest integral value according to current rounding direction */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrintf,(float __x),(__x))
#elif defined(__CRT_HAVE___llrintf)
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrintf,(float __x),__llrintf,(__x))
#elif defined(__CRT_HAVE_lrintf) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrintf,(float __x),lrintf,(__x))
#elif defined(__CRT_HAVE___lrintf) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrintf,(float __x),__lrintf,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/llrintf.h>
__NAMESPACE_STD_BEGIN
/* Round `x' to nearest integral value according to current rounding direction */
__NAMESPACE_LOCAL_USING_OR_IMPL(llrintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL llrintf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llrintf))(__x); })
#endif /* !... */
#if __has_builtin(__builtin_llroundf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llroundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llroundf,(float __x),{ return __builtin_llroundf(__x); })
#elif defined(__CRT_HAVE_llroundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llroundf,(float __x),(__x))
#elif defined(__CRT_HAVE___llroundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llroundf,(float __x),__llroundf,(__x))
#elif defined(__CRT_HAVE_lroundf) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llroundf,(float __x),lroundf,(__x))
#elif defined(__CRT_HAVE___lroundf) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llroundf,(float __x),__lroundf,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/llroundf.h>
__NAMESPACE_STD_BEGIN
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__NAMESPACE_LOCAL_USING_OR_IMPL(llroundf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL llroundf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llroundf))(__x); })
#endif /* !... */
#endif /* __COMPILER_HAVE_LONGLONG */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_nextafterl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nextafterl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nexttowardl,(__LONGDOUBLE __x, __LONGDOUBLE __y),nextafterl,{ return __builtin_nextafterl(__x, __y); })
#elif __has_builtin(__builtin_nexttowardl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nexttowardl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nexttowardl,(__LONGDOUBLE __x, __LONGDOUBLE __y),{ return __builtin_nexttowardl(__x); })
#elif defined(__CRT_HAVE_nextafterl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nexttowardl,(__LONGDOUBLE __x, __LONGDOUBLE __y),nextafterl,(__x,__y))
#elif defined(__CRT_HAVE_nexttowardl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nexttowardl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__CRT_HAVE___nextafterl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nexttowardl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__nextafterl,(__x,__y))
#elif defined(__CRT_HAVE___nexttowardl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nexttowardl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__nexttowardl,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE___nexttoward) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/nextafterl.h>
__NAMESPACE_STD_BEGIN
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL nexttowardl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nextafterl))(__x, __y); }
#endif /* ... */
#if __has_builtin(__builtin_scalbnl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbnl)
/* Return `x' times (2 to the Nth power) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbnl,(__LONGDOUBLE __x, int __n),{ return __builtin_scalbnl(__x, __n); })
#elif defined(__CRT_HAVE_scalbnl)
/* Return `x' times (2 to the Nth power) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbnl,(__LONGDOUBLE __x, int __n),(__x,__n))
#elif defined(__CRT_HAVE___scalbnl)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbnl,(__LONGDOUBLE __x, int __n),__scalbnl,(__x,__n))
#elif defined(__CRT_HAVE_scalblnl) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbnl,(__LONGDOUBLE __x, int __n),scalblnl,(__x,__n))
#elif defined(__CRT_HAVE___scalblnl) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbnl,(__LONGDOUBLE __x, int __n),__scalblnl,(__x,__n))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_scalbn) || defined(__CRT_HAVE___scalbn) || (defined(__CRT_HAVE_scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/scalbnl.h>
__NAMESPACE_STD_BEGIN
/* Return `x' times (2 to the Nth power) */
__NAMESPACE_LOCAL_USING_OR_IMPL(scalbnl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL scalbnl)(__LONGDOUBLE __x, int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbnl))(__x, __n); })
#endif /* ... */
#if __has_builtin(__builtin_scalblnl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalblnl)
/* Return `x' times (2 to the Nth power) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalblnl,(__LONGDOUBLE __x, long int __n),{ return __builtin_scalblnl(__x, __n); })
#elif defined(__CRT_HAVE_scalblnl)
/* Return `x' times (2 to the Nth power) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalblnl,(__LONGDOUBLE __x, long int __n),(__x,__n))
#elif defined(__CRT_HAVE___scalblnl)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalblnl,(__LONGDOUBLE __x, long int __n),__scalblnl,(__x,__n))
#elif defined(__CRT_HAVE_scalbnl) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalblnl,(__LONGDOUBLE __x, long int __n),scalbnl,(__x,__n))
#elif defined(__CRT_HAVE___scalbnl) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalblnl,(__LONGDOUBLE __x, long int __n),__scalbnl,(__x,__n))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_scalbln) || defined(__CRT_HAVE___scalbln) || (defined(__CRT_HAVE_scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/scalblnl.h>
__NAMESPACE_STD_BEGIN
/* Return `x' times (2 to the Nth power) */
__NAMESPACE_LOCAL_USING_OR_IMPL(scalblnl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL scalblnl)(__LONGDOUBLE __x, long int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalblnl))(__x, __n); })
#endif /* ... */
#if __has_builtin(__builtin_nearbyintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nearbyintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode
 * This function is similar to `rint()', but does not tend to produce wrong results (so use this one) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nearbyintl,(__LONGDOUBLE __x),{ return __builtin_nearbyintl(__x); })
#elif defined(__CRT_HAVE_nearbyintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode
 * This function is similar to `rint()', but does not tend to produce wrong results (so use this one) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nearbyintl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___nearbyintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode
 * This function is similar to `rint()', but does not tend to produce wrong results (so use this one) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nearbyintl,(__LONGDOUBLE __x),__nearbyintl,(__x))
#elif defined(__CRT_HAVE_rintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode
 * This function is similar to `rint()', but does not tend to produce wrong results (so use this one) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nearbyintl,(__LONGDOUBLE __x),rintl,(__x))
#elif defined(__CRT_HAVE___rintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode
 * This function is similar to `rint()', but does not tend to produce wrong results (so use this one) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nearbyintl,(__LONGDOUBLE __x),__rintl,(__x))
#elif defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
__NAMESPACE_STD_END
#include <libc/local/math/rintl.h>
__NAMESPACE_STD_BEGIN
/* Return the integer nearest `x' in the direction of the prevailing rounding mode
 * This function is similar to `rint()', but does not tend to produce wrong results (so use this one) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL nearbyintl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rintl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_roundl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_roundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,roundl,(__LONGDOUBLE __x),{ return __builtin_roundl(__x); })
#elif defined(__CRT_HAVE_roundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,roundl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___roundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,roundl,(__LONGDOUBLE __x),__roundl,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/roundl.h>
__NAMESPACE_STD_BEGIN
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__NAMESPACE_LOCAL_USING_OR_IMPL(roundl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL roundl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(roundl))(__x); })
#endif /* !... */
#if __has_builtin(__builtin_truncl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_truncl)
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,truncl,(__LONGDOUBLE __x),{ return __builtin_truncl(__x); })
#elif defined(__CRT_HAVE_truncl)
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,truncl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___truncl)
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,truncl,(__LONGDOUBLE __x),__truncl,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/truncl.h>
__NAMESPACE_STD_BEGIN
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__NAMESPACE_LOCAL_USING_OR_IMPL(truncl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL truncl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(truncl))(__x); })
#endif /* !... */
#if __has_builtin(__builtin_remquol) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remquol)
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__CEIDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3)),__LONGDOUBLE,__NOTHROW,remquol,(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo),{ return __builtin_remquol(__x, __y, __pquo); })
#elif defined(__CRT_HAVE_remquol)
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3)),__LONGDOUBLE,__NOTHROW,remquol,(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo),(__x,__y,__pquo))
#elif defined(__CRT_HAVE___remquol)
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),__LONGDOUBLE,__NOTHROW,remquol,(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo),__remquol,(__x,__y,__pquo))
#elif defined(__CRT_HAVE_remquo) || defined(__CRT_HAVE___remquo)
__NAMESPACE_STD_END
#include <libc/local/math/remquol.h>
__NAMESPACE_STD_BEGIN
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__NAMESPACE_LOCAL_USING_OR_IMPL(remquol, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __LONGDOUBLE __NOTHROW(__LIBCCALL remquol)(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remquol))(__x, __y, __pquo); })
#endif /* ... */
#if __has_builtin(__builtin_lrintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lrintl)
/* Round `x' to nearest integral value according to current rounding direction */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lrintl,(__LONGDOUBLE __x),{ return __builtin_lrintl(__x); })
#elif defined(__CRT_HAVE_lrintl)
/* Round `x' to nearest integral value according to current rounding direction */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lrintl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___lrintl)
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lrintl,(__LONGDOUBLE __x),__lrintl,(__x))
#elif defined(__CRT_HAVE_llrintl) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lrintl,(__LONGDOUBLE __x),llrintl,(__x))
#elif defined(__CRT_HAVE___llrintl) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lrintl,(__LONGDOUBLE __x),__llrintl,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/lrintl.h>
__NAMESPACE_STD_BEGIN
/* Round `x' to nearest integral value according to current rounding direction */
__NAMESPACE_LOCAL_USING_OR_IMPL(lrintl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL lrintl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lrintl))(__x); })
#endif /* !... */
#if __has_builtin(__builtin_lroundl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lroundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lroundl,(__LONGDOUBLE __x),{ return __builtin_lroundl(__x); })
#elif defined(__CRT_HAVE_lroundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lroundl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___lroundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lroundl,(__LONGDOUBLE __x),__lroundl,(__x))
#elif defined(__CRT_HAVE_llroundl) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lroundl,(__LONGDOUBLE __x),llroundl,(__x))
#elif defined(__CRT_HAVE___llroundl) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lroundl,(__LONGDOUBLE __x),__llroundl,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/lroundl.h>
__NAMESPACE_STD_BEGIN
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__NAMESPACE_LOCAL_USING_OR_IMPL(lroundl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL lroundl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lroundl))(__x); })
#endif /* !... */
#if __has_builtin(__builtin_fdiml) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fdiml)
/* Return positive difference between `x' and `y' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fdiml,(__LONGDOUBLE __x, __LONGDOUBLE __y),{ return __builtin_fdiml(__x, __y); })
#elif defined(__CRT_HAVE_fdiml)
/* Return positive difference between `x' and `y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fdiml,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__CRT_HAVE___fdiml)
/* Return positive difference between `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fdiml,(__LONGDOUBLE __x, __LONGDOUBLE __y),__fdiml,(__x,__y))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/fdiml.h>
__NAMESPACE_STD_BEGIN
/* Return positive difference between `x' and `y' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fdiml, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL fdiml)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fdiml))(__x, __y); })
#endif /* !... */
#if __has_builtin(__builtin_fmaxl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmaxl)
/* Return maximum numeric value from `x' and `y' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmaxl,(__LONGDOUBLE __x, __LONGDOUBLE __y),{ return __builtin_fmaxl(__x, __y); })
#elif defined(__CRT_HAVE_fmaxl)
/* Return maximum numeric value from `x' and `y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmaxl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__CRT_HAVE___fmaxl)
/* Return maximum numeric value from `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmaxl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__fmaxl,(__x,__y))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/fmaxl.h>
__NAMESPACE_STD_BEGIN
/* Return maximum numeric value from `x' and `y' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fmaxl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL fmaxl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmaxl))(__x, __y); })
#endif /* !... */
#if __has_builtin(__builtin_fminl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fminl)
/* Return minimum numeric value from `x' and `y' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fminl,(__LONGDOUBLE __x, __LONGDOUBLE __y),{ return __builtin_fminl(__x, __y); })
#elif defined(__CRT_HAVE_fminl)
/* Return minimum numeric value from `x' and `y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fminl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__CRT_HAVE___fminl)
/* Return minimum numeric value from `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fminl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__fminl,(__x,__y))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/fminl.h>
__NAMESPACE_STD_BEGIN
/* Return minimum numeric value from `x' and `y' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fminl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL fminl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fminl))(__x, __y); })
#endif /* !... */
#if __has_builtin(__builtin_fmal) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmal)
/* Multiply-add function computed as a ternary operation */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmal,(__LONGDOUBLE __x, __LONGDOUBLE __y, __LONGDOUBLE __z),{ return __builtin_fmal(__x, __y, __z); })
#elif defined(__CRT_HAVE_fmal)
/* Multiply-add function computed as a ternary operation */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmal,(__LONGDOUBLE __x, __LONGDOUBLE __y, __LONGDOUBLE __z),(__x,__y,__z))
#elif defined(__CRT_HAVE___fmal)
/* Multiply-add function computed as a ternary operation */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmal,(__LONGDOUBLE __x, __LONGDOUBLE __y, __LONGDOUBLE __z),__fmal,(__x,__y,__z))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/fmal.h>
__NAMESPACE_STD_BEGIN
/* Multiply-add function computed as a ternary operation */
__NAMESPACE_LOCAL_USING_OR_IMPL(fmal, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL fmal)(__LONGDOUBLE __x, __LONGDOUBLE __y, __LONGDOUBLE __z) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmal))(__x, __y, __z); })
#endif /* !... */
#ifdef __COMPILER_HAVE_LONGLONG
#if __has_builtin(__builtin_llrintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llrintl)
/* Round `x' to nearest integral value according to current rounding direction */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrintl,(__LONGDOUBLE __x),{ return __builtin_llrintl(__x); })
#elif defined(__CRT_HAVE_llrintl)
/* Round `x' to nearest integral value according to current rounding direction */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrintl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___llrintl)
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrintl,(__LONGDOUBLE __x),__llrintl,(__x))
#elif defined(__CRT_HAVE_lrintl) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrintl,(__LONGDOUBLE __x),lrintl,(__x))
#elif defined(__CRT_HAVE___lrintl) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrintl,(__LONGDOUBLE __x),__lrintl,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/llrintl.h>
__NAMESPACE_STD_BEGIN
/* Round `x' to nearest integral value according to current rounding direction */
__NAMESPACE_LOCAL_USING_OR_IMPL(llrintl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL llrintl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llrintl))(__x); })
#endif /* !... */
#if __has_builtin(__builtin_llroundl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llroundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llroundl,(__LONGDOUBLE __x),{ return __builtin_llroundl(__x); })
#elif defined(__CRT_HAVE_llroundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llroundl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___llroundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llroundl,(__LONGDOUBLE __x),__llroundl,(__x))
#elif defined(__CRT_HAVE_lroundl) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llroundl,(__LONGDOUBLE __x),lroundl,(__x))
#elif defined(__CRT_HAVE___lroundl) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llroundl,(__LONGDOUBLE __x),__lroundl,(__x))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/math/llroundl.h>
__NAMESPACE_STD_BEGIN
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__NAMESPACE_LOCAL_USING_OR_IMPL(llroundl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL llroundl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llroundl))(__x); })
#endif /* !... */
#endif /* __COMPILER_HAVE_LONGLONG */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_MATH_H_PROTO)
extern "C++" {
#if __has_builtin(__builtin_acosf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acosf)
/* Arc cosine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,acos,(float __x),acosf,{ return __builtin_acosf(__x); })
#elif defined(__CRT_HAVE_acosf)
/* Arc cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,acos,(float __x),acosf,(__x))
#elif defined(__CRT_HAVE___acosf)
/* Arc cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,acos,(float __x),__acosf,(__x))
#elif defined(__CRT_HAVE_acos) || defined(__CRT_HAVE___acos)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/acosf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Arc cosine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL acos)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(acosf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_asinf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinf)
/* Arc sine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,asin,(float __x),asinf,{ return __builtin_asinf(__x); })
#elif defined(__CRT_HAVE_asinf)
/* Arc sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,asin,(float __x),asinf,(__x))
#elif defined(__CRT_HAVE___asinf)
/* Arc sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,asin,(float __x),__asinf,(__x))
#elif defined(__CRT_HAVE_asin) || defined(__CRT_HAVE___asin)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/asinf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Arc sine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL asin)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asinf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_atanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanf)
/* Arc tangent of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,atan,(float __x),atanf,{ return __builtin_atanf(__x); })
#elif defined(__CRT_HAVE_atanf)
/* Arc tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,atan,(float __x),atanf,(__x))
#elif defined(__CRT_HAVE___atanf)
/* Arc tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,atan,(float __x),__atanf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_atan) || defined(__CRT_HAVE___atan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/atanf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Arc tangent of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL atan)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atanf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_atan2f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan2f)
/* Arc tangent of `y / x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,atan2,(float __y, float __x),atan2f,{ return __builtin_atan2f(__y, __x); })
#elif defined(__CRT_HAVE_atan2f)
/* Arc tangent of `y / x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,atan2,(float __y, float __x),atan2f,(__y,__x))
#elif defined(__CRT_HAVE___atan2f)
/* Arc tangent of `y / x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,atan2,(float __y, float __x),__atan2f,(__y,__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/atan2f.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Arc tangent of `y / x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL atan2)(float __y, float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atan2f))(__y, __x); }
#endif /* ... */
#if __has_builtin(__builtin_cosf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cosf)
/* Cosine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cosf,float,__NOTHROW,cos,(float __x),cosf,{ return __builtin_cosf(__x); })
#elif defined(__CRT_HAVE_cosf)
/* Cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cosf,float,__NOTHROW,cos,(float __x),cosf,(__x))
#elif defined(__CRT_HAVE___cosf)
/* Cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cosf,float,__NOTHROW,cos,(float __x),__cosf,(__x))
#elif defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/cosf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Cosine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_cosf float __NOTHROW(__LIBCCALL cos)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cosf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_sinf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinf)
/* Sine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sinf,float,__NOTHROW,sin,(float __x),sinf,{ return __builtin_sinf(__x); })
#elif defined(__CRT_HAVE_sinf)
/* Sine of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sinf,float,__NOTHROW,sin,(float __x),sinf,(__x))
#elif defined(__CRT_HAVE___sinf)
/* Sine of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sinf,float,__NOTHROW,sin,(float __x),__sinf,(__x))
#elif defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/sinf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Sine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_sinf float __NOTHROW(__LIBCCALL sin)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sinf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_tanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanf)
/* Tangent of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,tan,(float __x),tanf,{ return __builtin_tanf(__x); })
#elif defined(__CRT_HAVE_tanf)
/* Tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,tan,(float __x),tanf,(__x))
#elif defined(__CRT_HAVE___tanf)
/* Tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,tan,(float __x),__tanf,(__x))
#elif defined(__CRT_HAVE_tan) || defined(__CRT_HAVE___tan)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/tanf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Tangent of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL tan)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tanf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_coshf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_coshf)
/* Hyperbolic cosine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,cosh,(float __x),coshf,{ return __builtin_coshf(__x); })
#elif defined(__CRT_HAVE_coshf)
/* Hyperbolic cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,cosh,(float __x),coshf,(__x))
#elif defined(__CRT_HAVE___coshf)
/* Hyperbolic cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,cosh,(float __x),__coshf,(__x))
#elif defined(__CRT_HAVE_cosh) || defined(__CRT_HAVE___cosh)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/coshf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Hyperbolic cosine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL cosh)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(coshf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_sinhf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinhf)
/* Hyperbolic sine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,sinh,(float __x),sinhf,{ return __builtin_sinhf(__x); })
#elif defined(__CRT_HAVE_sinhf)
/* Hyperbolic sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,sinh,(float __x),sinhf,(__x))
#elif defined(__CRT_HAVE___sinhf)
/* Hyperbolic sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,sinh,(float __x),__sinhf,(__x))
#elif defined(__CRT_HAVE_sinh) || defined(__CRT_HAVE___sinh)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/sinhf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Hyperbolic sine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL sinh)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sinhf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_tanhf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanhf)
/* Hyperbolic tangent of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,tanh,(float __x),tanhf,{ return __builtin_tanhf(__x); })
#elif defined(__CRT_HAVE_tanhf)
/* Hyperbolic tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,tanh,(float __x),tanhf,(__x))
#elif defined(__CRT_HAVE___tanhf)
/* Hyperbolic tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,tanh,(float __x),__tanhf,(__x))
#elif defined(__CRT_HAVE_tanh) || defined(__CRT_HAVE___tanh)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/tanhf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Hyperbolic tangent of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL tanh)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tanhf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_expf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expf)
/* Exponential function of `x' */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_expf,float,__NOTHROW,exp,(float __x),expf,{ return __builtin_expf(__x); })
#elif defined(__CRT_HAVE_expf)
/* Exponential function of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_expf,float,__NOTHROW,exp,(float __x),expf,(__x))
#elif defined(__CRT_HAVE___expf)
/* Exponential function of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_expf,float,__NOTHROW,exp,(float __x),__expf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_exp) || defined(__CRT_HAVE___exp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/expf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Exponential function of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_expf float __NOTHROW(__LIBCCALL exp)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_frexpf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_frexpf)
/* Break `value' into a normalized fraction and an integral power of 2 */
__CEIREDIRECT(__ATTR_NONNULL((2)),float,__NOTHROW_NCX,frexp,(float __x, int *__pexponent),frexpf,{ return __builtin_frexpf(__x, __pexponent); })
#elif defined(__CRT_HAVE_frexpf)
/* Break `value' into a normalized fraction and an integral power of 2 */
__CREDIRECT(__ATTR_NONNULL((2)),float,__NOTHROW_NCX,frexp,(float __x, int *__pexponent),frexpf,(__x,__pexponent))
#elif defined(__CRT_HAVE___frexpf)
/* Break `value' into a normalized fraction and an integral power of 2 */
__CREDIRECT(__ATTR_NONNULL((2)),float,__NOTHROW_NCX,frexp,(float __x, int *__pexponent),__frexpf,(__x,__pexponent))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_frexp) || defined(__CRT_HAVE___frexp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/frexpf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Break `value' into a normalized fraction and an integral power of 2 */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) float __NOTHROW_NCX(__LIBCCALL frexp)(float __x, int *__pexponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(frexpf))(__x, __pexponent); }
#endif /* ... */
#if __has_builtin(__builtin_ldexpf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ldexpf)
/* `x' times (two to the `exponent' power) */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,ldexp,(float __x, int __exponent),ldexpf,{ return __builtin_ldexpf(__x, __exponent); })
#elif defined(__CRT_HAVE_ldexpf)
/* `x' times (two to the `exponent' power) */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,ldexp,(float __x, int __exponent),ldexpf,(__x,__exponent))
#elif defined(__CRT_HAVE___ldexpf)
/* `x' times (two to the `exponent' power) */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,ldexp,(float __x, int __exponent),__ldexpf,(__x,__exponent))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_ldexp) || defined(__CRT_HAVE___ldexp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/ldexpf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* `x' times (two to the `exponent' power) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL ldexp)(float __x, int __exponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ldexpf))(__x, __exponent); }
#endif /* ... */
#if __has_builtin(__builtin_logf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logf)
/* Natural logarithm of `x' */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_logf,float,__NOTHROW,log,(float __x),logf,{ return __builtin_logf(__x); })
#elif defined(__CRT_HAVE_logf)
/* Natural logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_logf,float,__NOTHROW,log,(float __x),logf,(__x))
#elif defined(__CRT_HAVE___logf)
/* Natural logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_logf,float,__NOTHROW,log,(float __x),__logf,(__x))
#elif defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/logf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Natural logarithm of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_logf float __NOTHROW(__LIBCCALL log)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_log10f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log10f)
/* Base-ten logarithm of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,log10,(float __x),log10f,{ return __builtin_log10f(__x); })
#elif defined(__CRT_HAVE_log10f)
/* Base-ten logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,log10,(float __x),log10f,(__x))
#elif defined(__CRT_HAVE___log10f)
/* Base-ten logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,log10,(float __x),__log10f,(__x))
#elif defined(__CRT_HAVE_log10) || defined(__CRT_HAVE___log10)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/log10f.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Base-ten logarithm of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL log10)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log10f))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_modff) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_modff)
/* Break `value' into integral and fractional parts */
__CEIREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),float,__NOTHROW_NCX,modf,(float __x, float *__iptr),modff,{ return __builtin_modff(__x, __iptr); })
#elif defined(__CRT_HAVE_modff)
/* Break `value' into integral and fractional parts */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),float,__NOTHROW_NCX,modf,(float __x, float *__iptr),modff,(__x,__iptr))
#elif defined(__CRT_HAVE___modff)
/* Break `value' into integral and fractional parts */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),float,__NOTHROW_NCX,modf,(float __x, float *__iptr),__modff,(__x,__iptr))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_modf) || defined(__CRT_HAVE___modf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/modff.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Break `value' into integral and fractional parts */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) float __NOTHROW_NCX(__LIBCCALL modf)(float __x, float *__iptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(modff))(__x, __iptr); }
#endif /* ... */
#if __has_builtin(__builtin_powf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_powf)
/* Return `x' to the `y' power */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_powf,float,__NOTHROW,pow,(float __x, float __y),powf,{ return __builtin_powf(__x, __y); })
#elif defined(__CRT_HAVE_powf)
/* Return `x' to the `y' power */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_powf,float,__NOTHROW,pow,(float __x, float __y),powf,(__x,__y))
#elif defined(__CRT_HAVE___powf)
/* Return `x' to the `y' power */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_powf,float,__NOTHROW,pow,(float __x, float __y),__powf,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/powf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return `x' to the `y' power */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_powf float __NOTHROW(__LIBCCALL pow)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(powf))(__x, __y); }
#endif /* ... */
#if __has_builtin(__builtin_sqrtf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sqrtf)
/* Return the square root of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,sqrt,(float __x),sqrtf,{ return __builtin_sqrtf(__x); })
#elif defined(__CRT_HAVE_sqrtf)
/* Return the square root of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,sqrt,(float __x),sqrtf,(__x))
#elif defined(__CRT_HAVE___sqrtf)
/* Return the square root of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,sqrt,(float __x),__sqrtf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/sqrtf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the square root of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL sqrt)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sqrtf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_ceilf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ceilf)
/* Smallest integral value not less than `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,ceil,(float __x),ceilf,{ return __builtin_ceilf(__x); })
#elif defined(__CRT_HAVE_ceilf)
/* Smallest integral value not less than `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,ceil,(float __x),ceilf,(__x))
#elif defined(__CRT_HAVE___ceilf)
/* Smallest integral value not less than `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,ceil,(float __x),__ceilf,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/ceilf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Smallest integral value not less than `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL ceil)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ceilf))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_fabsf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabsf)
/* Absolute value of `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fabs,(float __x),fabsf,{ return __builtin_fabsf(__x); })
#elif defined(__CRT_HAVE_fabsf)
/* Absolute value of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fabs,(float __x),fabsf,(__x))
#elif defined(__CRT_HAVE___fabsf)
/* Absolute value of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fabs,(float __x),__fabsf,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/fabsf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Absolute value of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL fabs)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabsf))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_floorf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_floorf)
/* Largest integer not greater than `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,floor,(float __x),floorf,{ return __builtin_floorf(__x); })
#elif defined(__CRT_HAVE_floorf)
/* Largest integer not greater than `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,floor,(float __x),floorf,(__x))
#elif defined(__CRT_HAVE___floorf)
/* Largest integer not greater than `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,floor,(float __x),__floorf,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/floorf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Largest integer not greater than `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL floor)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(floorf))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_fmodf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmodf)
/* Floating-point modulo remainder of `x / y' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,fmod,(float __x, float __y),fmodf,{ return __builtin_fmodf(__x, __y); })
#elif defined(__CRT_HAVE_fmodf)
/* Floating-point modulo remainder of `x / y' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,fmod,(float __x, float __y),fmodf,(__x,__y))
#elif defined(__CRT_HAVE___fmodf)
/* Floating-point modulo remainder of `x / y' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,fmod,(float __x, float __y),__fmodf,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_fmod) || defined(__CRT_HAVE___fmod) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/fmodf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Floating-point modulo remainder of `x / y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL fmod)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmodf))(__x, __y); }
#endif /* ... */
} /* extern "C++" */
#ifdef __COMPILER_HAVE_LONGDOUBLE
extern "C++" {
#if __has_builtin(__builtin_acosl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acosl)
/* Arc cosine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acos,(__LONGDOUBLE __x),acosl,{ return __builtin_acosl(__x); })
#elif defined(__CRT_HAVE_acosl)
/* Arc cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acos,(__LONGDOUBLE __x),acosl,(__x))
#elif defined(__CRT_HAVE___acosl)
/* Arc cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acos,(__LONGDOUBLE __x),__acosl,(__x))
#elif defined(__CRT_HAVE_acos) || defined(__CRT_HAVE___acos)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/acosl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Arc cosine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL acos)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(acosl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_asinl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinl)
/* Arc sine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asin,(__LONGDOUBLE __x),asinl,{ return __builtin_asinl(__x); })
#elif defined(__CRT_HAVE_asinl)
/* Arc sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asin,(__LONGDOUBLE __x),asinl,(__x))
#elif defined(__CRT_HAVE___asinl)
/* Arc sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asin,(__LONGDOUBLE __x),__asinl,(__x))
#elif defined(__CRT_HAVE_asin) || defined(__CRT_HAVE___asin)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/asinl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Arc sine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL asin)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asinl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_atanl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanl)
/* Arc tangent of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atan,(__LONGDOUBLE __x),atanl,{ return __builtin_atanl(__x); })
#elif defined(__CRT_HAVE_atanl)
/* Arc tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atan,(__LONGDOUBLE __x),atanl,(__x))
#elif defined(__CRT_HAVE___atanl)
/* Arc tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atan,(__LONGDOUBLE __x),__atanl,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_atan) || defined(__CRT_HAVE___atan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/atanl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Arc tangent of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL atan)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atanl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_atan2l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan2l)
/* Arc tangent of `y / x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atan2,(__LONGDOUBLE __y, __LONGDOUBLE __x),atan2l,{ return __builtin_atan2l(__y, __x); })
#elif defined(__CRT_HAVE_atan2l)
/* Arc tangent of `y / x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atan2,(__LONGDOUBLE __y, __LONGDOUBLE __x),atan2l,(__y,__x))
#elif defined(__CRT_HAVE___atan2l)
/* Arc tangent of `y / x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atan2,(__LONGDOUBLE __y, __LONGDOUBLE __x),__atan2l,(__y,__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/atan2l.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Arc tangent of `y / x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL atan2)(__LONGDOUBLE __y, __LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atan2l))(__y, __x); }
#endif /* ... */
#if __has_builtin(__builtin_cosl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cosl)
/* Cosine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cosl,__LONGDOUBLE,__NOTHROW,cos,(__LONGDOUBLE __x),cosl,{ return __builtin_cosl(__x); })
#elif defined(__CRT_HAVE_cosl)
/* Cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cosl,__LONGDOUBLE,__NOTHROW,cos,(__LONGDOUBLE __x),cosl,(__x))
#elif defined(__CRT_HAVE___cosl)
/* Cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cosl,__LONGDOUBLE,__NOTHROW,cos,(__LONGDOUBLE __x),__cosl,(__x))
#elif defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/cosl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Cosine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_cosl __LONGDOUBLE __NOTHROW(__LIBCCALL cos)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cosl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_sinl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinl)
/* Sine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sinl,__LONGDOUBLE,__NOTHROW,sin,(__LONGDOUBLE __x),sinl,{ return __builtin_sinl(__x); })
#elif defined(__CRT_HAVE_sinl)
/* Sine of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sinl,__LONGDOUBLE,__NOTHROW,sin,(__LONGDOUBLE __x),sinl,(__x))
#elif defined(__CRT_HAVE___sinl)
/* Sine of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sinl,__LONGDOUBLE,__NOTHROW,sin,(__LONGDOUBLE __x),__sinl,(__x))
#elif defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/sinl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Sine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_sinl __LONGDOUBLE __NOTHROW(__LIBCCALL sin)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sinl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_tanl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanl)
/* Tangent of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tan,(__LONGDOUBLE __x),tanl,{ return __builtin_tanl(__x); })
#elif defined(__CRT_HAVE_tanl)
/* Tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tan,(__LONGDOUBLE __x),tanl,(__x))
#elif defined(__CRT_HAVE___tanl)
/* Tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tan,(__LONGDOUBLE __x),__tanl,(__x))
#elif defined(__CRT_HAVE_tan) || defined(__CRT_HAVE___tan)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/tanl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Tangent of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL tan)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tanl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_coshl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_coshl)
/* Hyperbolic cosine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cosh,(__LONGDOUBLE __x),coshl,{ return __builtin_coshl(__x); })
#elif defined(__CRT_HAVE_coshl)
/* Hyperbolic cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cosh,(__LONGDOUBLE __x),coshl,(__x))
#elif defined(__CRT_HAVE___coshl)
/* Hyperbolic cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cosh,(__LONGDOUBLE __x),__coshl,(__x))
#elif defined(__CRT_HAVE_cosh) || defined(__CRT_HAVE___cosh)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/coshl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Hyperbolic cosine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL cosh)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(coshl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_sinhl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinhl)
/* Hyperbolic sine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sinh,(__LONGDOUBLE __x),sinhl,{ return __builtin_sinhl(__x); })
#elif defined(__CRT_HAVE_sinhl)
/* Hyperbolic sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sinh,(__LONGDOUBLE __x),sinhl,(__x))
#elif defined(__CRT_HAVE___sinhl)
/* Hyperbolic sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sinh,(__LONGDOUBLE __x),__sinhl,(__x))
#elif defined(__CRT_HAVE_sinh) || defined(__CRT_HAVE___sinh)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/sinhl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Hyperbolic sine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL sinh)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sinhl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_tanhl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanhl)
/* Hyperbolic tangent of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tanh,(__LONGDOUBLE __x),tanhl,{ return __builtin_tanhl(__x); })
#elif defined(__CRT_HAVE_tanhl)
/* Hyperbolic tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tanh,(__LONGDOUBLE __x),tanhl,(__x))
#elif defined(__CRT_HAVE___tanhl)
/* Hyperbolic tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tanh,(__LONGDOUBLE __x),__tanhl,(__x))
#elif defined(__CRT_HAVE_tanh) || defined(__CRT_HAVE___tanh)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/tanhl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Hyperbolic tangent of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL tanh)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tanhl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_expl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expl)
/* Exponential function of `x' */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_expl,__LONGDOUBLE,__NOTHROW,exp,(__LONGDOUBLE __x),expl,{ return __builtin_expl(__x); })
#elif defined(__CRT_HAVE_expl)
/* Exponential function of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_expl,__LONGDOUBLE,__NOTHROW,exp,(__LONGDOUBLE __x),expl,(__x))
#elif defined(__CRT_HAVE___expl)
/* Exponential function of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_expl,__LONGDOUBLE,__NOTHROW,exp,(__LONGDOUBLE __x),__expl,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_exp) || defined(__CRT_HAVE___exp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/expl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Exponential function of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_expl __LONGDOUBLE __NOTHROW(__LIBCCALL exp)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_frexpl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_frexpl)
/* Break `value' into a normalized fraction and an integral power of 2 */
__CEIREDIRECT(__ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,frexp,(__LONGDOUBLE __x, int *__pexponent),frexpl,{ return __builtin_frexpl(__x, __pexponent); })
#elif defined(__CRT_HAVE_frexpl)
/* Break `value' into a normalized fraction and an integral power of 2 */
__CREDIRECT(__ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,frexp,(__LONGDOUBLE __x, int *__pexponent),frexpl,(__x,__pexponent))
#elif defined(__CRT_HAVE___frexpl)
/* Break `value' into a normalized fraction and an integral power of 2 */
__CREDIRECT(__ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,frexp,(__LONGDOUBLE __x, int *__pexponent),__frexpl,(__x,__pexponent))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_frexp) || defined(__CRT_HAVE___frexp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/frexpl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Break `value' into a normalized fraction and an integral power of 2 */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL frexp)(__LONGDOUBLE __x, int *__pexponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(frexpl))(__x, __pexponent); }
#endif /* ... */
#if __has_builtin(__builtin_ldexpl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ldexpl)
/* `x' times (two to the `exponent' power) */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ldexp,(__LONGDOUBLE __x, int __exponent),ldexpl,{ return __builtin_ldexpl(__x, __exponent); })
#elif defined(__CRT_HAVE_ldexpl)
/* `x' times (two to the `exponent' power) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ldexp,(__LONGDOUBLE __x, int __exponent),ldexpl,(__x,__exponent))
#elif defined(__CRT_HAVE___ldexpl)
/* `x' times (two to the `exponent' power) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ldexp,(__LONGDOUBLE __x, int __exponent),__ldexpl,(__x,__exponent))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_ldexp) || defined(__CRT_HAVE___ldexp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/ldexpl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* `x' times (two to the `exponent' power) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL ldexp)(__LONGDOUBLE __x, int __exponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ldexpl))(__x, __exponent); }
#endif /* ... */
#if __has_builtin(__builtin_logl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logl)
/* Natural logarithm of `x' */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_logl,__LONGDOUBLE,__NOTHROW,log,(__LONGDOUBLE __x),logl,{ return __builtin_logl(__x); })
#elif defined(__CRT_HAVE_logl)
/* Natural logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_logl,__LONGDOUBLE,__NOTHROW,log,(__LONGDOUBLE __x),logl,(__x))
#elif defined(__CRT_HAVE___logl)
/* Natural logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_logl,__LONGDOUBLE,__NOTHROW,log,(__LONGDOUBLE __x),__logl,(__x))
#elif defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/logl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Natural logarithm of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_logl __LONGDOUBLE __NOTHROW(__LIBCCALL log)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_log10l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log10l)
/* Base-ten logarithm of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log10,(__LONGDOUBLE __x),log10l,{ return __builtin_log10l(__x); })
#elif defined(__CRT_HAVE_log10l)
/* Base-ten logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log10,(__LONGDOUBLE __x),log10l,(__x))
#elif defined(__CRT_HAVE___log10l)
/* Base-ten logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log10,(__LONGDOUBLE __x),__log10l,(__x))
#elif defined(__CRT_HAVE_log10) || defined(__CRT_HAVE___log10)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/log10l.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Base-ten logarithm of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL log10)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log10l))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_modfl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_modfl)
/* Break `value' into integral and fractional parts */
__CEIREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,modf,(__LONGDOUBLE __x, __LONGDOUBLE *__iptr),modfl,{ return __builtin_modfl(__x, __iptr); })
#elif defined(__CRT_HAVE_modfl)
/* Break `value' into integral and fractional parts */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,modf,(__LONGDOUBLE __x, __LONGDOUBLE *__iptr),modfl,(__x,__iptr))
#elif defined(__CRT_HAVE___modfl)
/* Break `value' into integral and fractional parts */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,modf,(__LONGDOUBLE __x, __LONGDOUBLE *__iptr),__modfl,(__x,__iptr))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_modf) || defined(__CRT_HAVE___modf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/modfl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Break `value' into integral and fractional parts */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL modf)(__LONGDOUBLE __x, __LONGDOUBLE *__iptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(modfl))(__x, __iptr); }
#endif /* ... */
#if __has_builtin(__builtin_powl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_powl)
/* Return `x' to the `y' power */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_powl,__LONGDOUBLE,__NOTHROW,pow,(__LONGDOUBLE __x, __LONGDOUBLE __y),powl,{ return __builtin_powl(__x, __y); })
#elif defined(__CRT_HAVE_powl)
/* Return `x' to the `y' power */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_powl,__LONGDOUBLE,__NOTHROW,pow,(__LONGDOUBLE __x, __LONGDOUBLE __y),powl,(__x,__y))
#elif defined(__CRT_HAVE___powl)
/* Return `x' to the `y' power */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_powl,__LONGDOUBLE,__NOTHROW,pow,(__LONGDOUBLE __x, __LONGDOUBLE __y),__powl,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/powl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return `x' to the `y' power */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_powl __LONGDOUBLE __NOTHROW(__LIBCCALL pow)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(powl))(__x, __y); }
#endif /* ... */
#if __has_builtin(__builtin_sqrtl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sqrtl)
/* Return the square root of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sqrt,(__LONGDOUBLE __x),sqrtl,{ return __builtin_sqrtl(__x); })
#elif defined(__CRT_HAVE_sqrtl)
/* Return the square root of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sqrt,(__LONGDOUBLE __x),sqrtl,(__x))
#elif defined(__CRT_HAVE___sqrtl)
/* Return the square root of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,sqrt,(__LONGDOUBLE __x),__sqrtl,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/sqrtl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the square root of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL sqrt)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sqrtl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_ceill) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ceill)
/* Smallest integral value not less than `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ceil,(__LONGDOUBLE __x),ceill,{ return __builtin_ceill(__x); })
#elif defined(__CRT_HAVE_ceill)
/* Smallest integral value not less than `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ceil,(__LONGDOUBLE __x),ceill,(__x))
#elif defined(__CRT_HAVE___ceill)
/* Smallest integral value not less than `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ceil,(__LONGDOUBLE __x),__ceill,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/ceill.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Smallest integral value not less than `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL ceil)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ceill))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_fabsl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabsl)
/* Absolute value of `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fabs,(__LONGDOUBLE __x),fabsl,{ return __builtin_fabsl(__x); })
#elif defined(__CRT_HAVE_fabsl)
/* Absolute value of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fabs,(__LONGDOUBLE __x),fabsl,(__x))
#elif defined(__CRT_HAVE___fabsl)
/* Absolute value of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fabs,(__LONGDOUBLE __x),__fabsl,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/fabsl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Absolute value of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL fabs)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabsl))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_floorl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_floorl)
/* Largest integer not greater than `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,floor,(__LONGDOUBLE __x),floorl,{ return __builtin_floorl(__x); })
#elif defined(__CRT_HAVE_floorl)
/* Largest integer not greater than `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,floor,(__LONGDOUBLE __x),floorl,(__x))
#elif defined(__CRT_HAVE___floorl)
/* Largest integer not greater than `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,floor,(__LONGDOUBLE __x),__floorl,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/floorl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Largest integer not greater than `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL floor)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(floorl))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_fmodl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmodl)
/* Floating-point modulo remainder of `x / y' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmod,(__LONGDOUBLE __x, __LONGDOUBLE __y),fmodl,{ return __builtin_fmodl(__x, __y); })
#elif defined(__CRT_HAVE_fmodl)
/* Floating-point modulo remainder of `x / y' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmod,(__LONGDOUBLE __x, __LONGDOUBLE __y),fmodl,(__x,__y))
#elif defined(__CRT_HAVE___fmodl)
/* Floating-point modulo remainder of `x / y' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmod,(__LONGDOUBLE __x, __LONGDOUBLE __y),__fmodl,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_fmod) || defined(__CRT_HAVE___fmod) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/fmodl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Floating-point modulo remainder of `x / y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL fmod)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmodl))(__x, __y); }
#endif /* ... */
} /* extern "C++" */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
extern "C++" {
#if __has_builtin(__builtin_acoshf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acoshf)
/* Hyperbolic arc cosine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,acosh,(float __x),acoshf,{ return __builtin_acoshf(__x); })
#elif defined(__CRT_HAVE_acoshf)
/* Hyperbolic arc cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,acosh,(float __x),acoshf,(__x))
#elif defined(__CRT_HAVE___acoshf)
/* Hyperbolic arc cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,acosh,(float __x),__acoshf,(__x))
#elif defined(__CRT_HAVE_acosh) || defined(__CRT_HAVE___acosh)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/acoshf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Hyperbolic arc cosine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL acosh)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(acoshf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_asinhf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinhf)
/* Hyperbolic arc sine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,asinh,(float __x),asinhf,{ return __builtin_asinhf(__x); })
#elif defined(__CRT_HAVE_asinhf)
/* Hyperbolic arc sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,asinh,(float __x),asinhf,(__x))
#elif defined(__CRT_HAVE___asinhf)
/* Hyperbolic arc sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,asinh,(float __x),__asinhf,(__x))
#elif defined(__CRT_HAVE_asinh) || defined(__CRT_HAVE___asinh)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/asinhf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Hyperbolic arc sine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL asinh)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asinhf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_atanhf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanhf)
/* Hyperbolic arc tangent of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,atanh,(float __x),atanhf,{ return __builtin_atanhf(__x); })
#elif defined(__CRT_HAVE_atanhf)
/* Hyperbolic arc tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,atanh,(float __x),atanhf,(__x))
#elif defined(__CRT_HAVE___atanhf)
/* Hyperbolic arc tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,atanh,(float __x),__atanhf,(__x))
#elif defined(__CRT_HAVE_atanh) || defined(__CRT_HAVE___atanh)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/atanhf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Hyperbolic arc tangent of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL atanh)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atanhf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_expm1f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expm1f)
/* Return `exp(x) - 1' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,expm1,(float __x),expm1f,{ return __builtin_expm1f(__x); })
#elif defined(__CRT_HAVE_expm1f)
/* Return `exp(x) - 1' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,expm1,(float __x),expm1f,(__x))
#elif defined(__CRT_HAVE___expm1f)
/* Return `exp(x) - 1' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,expm1,(float __x),__expm1f,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_expm1) || defined(__CRT_HAVE___expm1) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/expm1f.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return `exp(x) - 1' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL expm1)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expm1f))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_log1pf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log1pf)
/* Return `log(1 + x)' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,log1p,(float __x),log1pf,{ return __builtin_log1pf(__x); })
#elif defined(__CRT_HAVE_log1pf)
/* Return `log(1 + x)' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,log1p,(float __x),log1pf,(__x))
#elif defined(__CRT_HAVE___log1pf)
/* Return `log(1 + x)' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,log1p,(float __x),__log1pf,(__x))
#elif defined(__CRT_HAVE_log1p) || defined(__CRT_HAVE___log1p)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/log1pf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return `log(1 + x)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL log1p)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log1pf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_logbf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logbf)
/* Return the base 2 signed integral exponent of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,logb,(float __x),logbf,{ return __builtin_logbf(__x); })
#elif defined(__CRT_HAVE_logbf)
/* Return the base 2 signed integral exponent of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,logb,(float __x),logbf,(__x))
#elif defined(__CRT_HAVE___logbf)
/* Return the base 2 signed integral exponent of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,logb,(float __x),__logbf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_logb) || defined(__CRT_HAVE___logb) || defined(__CRT_HAVE__logb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/logbf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the base 2 signed integral exponent of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL logb)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logbf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_cbrtf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cbrtf)
/* Return the cube root of `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,cbrt,(float __x),cbrtf,{ return __builtin_cbrtf(__x); })
#elif defined(__CRT_HAVE_cbrtf)
/* Return the cube root of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,cbrt,(float __x),cbrtf,(__x))
#elif defined(__CRT_HAVE___cbrtf)
/* Return the cube root of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,cbrt,(float __x),__cbrtf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_cbrt) || defined(__CRT_HAVE___cbrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/cbrtf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the cube root of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL cbrt)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cbrtf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_rintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,rint,(float __x),rintf,{ return __builtin_rintf(__x); })
#elif __has_builtin(__builtin_nearbyintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nearbyintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,rint,(float __x),nearbyintf,{ return __builtin_nearbyintf(__x); })
#elif defined(__CRT_HAVE_rintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,rint,(float __x),rintf,(__x))
#elif defined(__CRT_HAVE_nearbyintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,rint,(float __x),nearbyintf,(__x))
#elif defined(__CRT_HAVE___rintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,rint,(float __x),__rintf,(__x))
#elif defined(__CRT_HAVE___nearbyintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,rint,(float __x),__nearbyintf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE_nearbyint) || defined(__CRT_HAVE___rint) || defined(__CRT_HAVE___nearbyint) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/rintf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL rint)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rintf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_nextafterf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nextafterf)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nextafter,(float __x, float __y),nextafterf,{ return __builtin_nextafterf(__x, __y); })
#elif __has_builtin(__builtin_nexttowardf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nexttowardf)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nextafter,(float __x, float __y),nexttowardf,{ return __builtin_nexttowardf(__x); })
#elif defined(__CRT_HAVE_nextafterf)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nextafter,(float __x, float __y),nextafterf,(__x,__y))
#elif defined(__CRT_HAVE_nexttowardf)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nextafter,(float __x, float __y),nexttowardf,(__x,__y))
#elif defined(__CRT_HAVE___nextafterf)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nextafter,(float __x, float __y),__nextafterf,(__x,__y))
#elif defined(__CRT_HAVE___nexttowardf)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nextafter,(float __x, float __y),__nexttowardf,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE___nexttoward) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/nextafterf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL nextafter)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nextafterf))(__x, __y); }
#endif /* ... */
#if __has_builtin(__builtin_remainderf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainderf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,remainder,(float __x, float __p),remainderf,{ return __builtin_remainderf(__x, __p); })
#elif __has_builtin(__builtin_dremf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_dremf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,remainder,(float __x, float __p),dremf,{ return __builtin_dremf(__x, __p); })
#elif defined(__CRT_HAVE_remainderf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,remainder,(float __x, float __p),remainderf,(__x,__p))
#elif defined(__CRT_HAVE_dremf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,remainder,(float __x, float __p),dremf,(__x,__p))
#elif defined(__CRT_HAVE___remainderf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,remainder,(float __x, float __p),__remainderf,(__x,__p))
#elif defined(__CRT_HAVE___dremf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,remainder,(float __x, float __p),__dremf,(__x,__p))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE___drem) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/remainderf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the remainder of integer division `x / p' with infinite precision */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL remainder)(float __x, float __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainderf))(__x, __p); }
#endif /* ... */
#if __has_builtin(__builtin_ilogbf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ilogbf)
/* Return the binary exponent of `x', which must be nonzero */
__CEIREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,ilogb,(float __x),ilogbf,{ return __builtin_ilogbf(__x); })
#elif defined(__CRT_HAVE_ilogbf)
/* Return the binary exponent of `x', which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,ilogb,(float __x),ilogbf,(__x))
#elif defined(__CRT_HAVE___ilogbf)
/* Return the binary exponent of `x', which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,ilogb,(float __x),__ilogbf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_ilogb) || defined(__CRT_HAVE___ilogb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/ilogbf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the binary exponent of `x', which must be nonzero */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED int __NOTHROW(__LIBCCALL ilogb)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ilogbf))(__x); }
#endif /* ... */
} /* extern "C++" */
#ifdef __COMPILER_HAVE_LONGDOUBLE
extern "C++" {
#if __has_builtin(__builtin_acoshl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acoshl)
/* Hyperbolic arc cosine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acosh,(__LONGDOUBLE __x),acoshl,{ return __builtin_acoshl(__x); })
#elif defined(__CRT_HAVE_acoshl)
/* Hyperbolic arc cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acosh,(__LONGDOUBLE __x),acoshl,(__x))
#elif defined(__CRT_HAVE___acoshl)
/* Hyperbolic arc cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,acosh,(__LONGDOUBLE __x),__acoshl,(__x))
#elif defined(__CRT_HAVE_acosh) || defined(__CRT_HAVE___acosh)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/acoshl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Hyperbolic arc cosine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL acosh)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(acoshl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_asinhl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinhl)
/* Hyperbolic arc sine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asinh,(__LONGDOUBLE __x),asinhl,{ return __builtin_asinhl(__x); })
#elif defined(__CRT_HAVE_asinhl)
/* Hyperbolic arc sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asinh,(__LONGDOUBLE __x),asinhl,(__x))
#elif defined(__CRT_HAVE___asinhl)
/* Hyperbolic arc sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,asinh,(__LONGDOUBLE __x),__asinhl,(__x))
#elif defined(__CRT_HAVE_asinh) || defined(__CRT_HAVE___asinh)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/asinhl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Hyperbolic arc sine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL asinh)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asinhl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_atanhl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanhl)
/* Hyperbolic arc tangent of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atanh,(__LONGDOUBLE __x),atanhl,{ return __builtin_atanhl(__x); })
#elif defined(__CRT_HAVE_atanhl)
/* Hyperbolic arc tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atanh,(__LONGDOUBLE __x),atanhl,(__x))
#elif defined(__CRT_HAVE___atanhl)
/* Hyperbolic arc tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,atanh,(__LONGDOUBLE __x),__atanhl,(__x))
#elif defined(__CRT_HAVE_atanh) || defined(__CRT_HAVE___atanh)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/atanhl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Hyperbolic arc tangent of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL atanh)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atanhl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_expm1l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expm1l)
/* Return `exp(x) - 1' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,expm1,(__LONGDOUBLE __x),expm1l,{ return __builtin_expm1l(__x); })
#elif defined(__CRT_HAVE_expm1l)
/* Return `exp(x) - 1' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,expm1,(__LONGDOUBLE __x),expm1l,(__x))
#elif defined(__CRT_HAVE___expm1l)
/* Return `exp(x) - 1' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,expm1,(__LONGDOUBLE __x),__expm1l,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_expm1) || defined(__CRT_HAVE___expm1) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/expm1l.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return `exp(x) - 1' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL expm1)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expm1l))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_log1pl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log1pl)
/* Return `log(1 + x)' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log1p,(__LONGDOUBLE __x),log1pl,{ return __builtin_log1pl(__x); })
#elif defined(__CRT_HAVE_log1pl)
/* Return `log(1 + x)' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log1p,(__LONGDOUBLE __x),log1pl,(__x))
#elif defined(__CRT_HAVE___log1pl)
/* Return `log(1 + x)' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log1p,(__LONGDOUBLE __x),__log1pl,(__x))
#elif defined(__CRT_HAVE_log1p) || defined(__CRT_HAVE___log1p)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/log1pl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return `log(1 + x)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL log1p)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log1pl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_logbl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logbl)
/* Return the base 2 signed integral exponent of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,logb,(__LONGDOUBLE __x),logbl,{ return __builtin_logbl(__x); })
#elif defined(__CRT_HAVE_logbl)
/* Return the base 2 signed integral exponent of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,logb,(__LONGDOUBLE __x),logbl,(__x))
#elif defined(__CRT_HAVE___logbl)
/* Return the base 2 signed integral exponent of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,logb,(__LONGDOUBLE __x),__logbl,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_logb) || defined(__CRT_HAVE___logb) || defined(__CRT_HAVE__logb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/logbl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the base 2 signed integral exponent of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL logb)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logbl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_cbrtl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cbrtl)
/* Return the cube root of `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cbrt,(__LONGDOUBLE __x),cbrtl,{ return __builtin_cbrtl(__x); })
#elif defined(__CRT_HAVE_cbrtl)
/* Return the cube root of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cbrt,(__LONGDOUBLE __x),cbrtl,(__x))
#elif defined(__CRT_HAVE___cbrtl)
/* Return the cube root of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,cbrt,(__LONGDOUBLE __x),__cbrtl,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_cbrt) || defined(__CRT_HAVE___cbrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/cbrtl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the cube root of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL cbrt)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cbrtl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_rintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,rint,(__LONGDOUBLE __x),rintl,{ return __builtin_rintl(__x); })
#elif __has_builtin(__builtin_nearbyintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nearbyintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,rint,(__LONGDOUBLE __x),nearbyintl,{ return __builtin_nearbyintl(__x); })
#elif defined(__CRT_HAVE_rintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,rint,(__LONGDOUBLE __x),rintl,(__x))
#elif defined(__CRT_HAVE_nearbyintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,rint,(__LONGDOUBLE __x),nearbyintl,(__x))
#elif defined(__CRT_HAVE___rintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,rint,(__LONGDOUBLE __x),__rintl,(__x))
#elif defined(__CRT_HAVE___nearbyintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,rint,(__LONGDOUBLE __x),__nearbyintl,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE_nearbyint) || defined(__CRT_HAVE___rint) || defined(__CRT_HAVE___nearbyint) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/rintl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL rint)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rintl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_nextafterl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nextafterl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nextafter,(__LONGDOUBLE __x, __LONGDOUBLE __y),nextafterl,{ return __builtin_nextafterl(__x, __y); })
#elif __has_builtin(__builtin_nexttowardl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nexttowardl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nextafter,(__LONGDOUBLE __x, __LONGDOUBLE __y),nexttowardl,{ return __builtin_nexttowardl(__x); })
#elif defined(__CRT_HAVE_nextafterl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nextafter,(__LONGDOUBLE __x, __LONGDOUBLE __y),nextafterl,(__x,__y))
#elif defined(__CRT_HAVE_nexttowardl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nextafter,(__LONGDOUBLE __x, __LONGDOUBLE __y),nexttowardl,(__x,__y))
#elif defined(__CRT_HAVE___nextafterl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nextafter,(__LONGDOUBLE __x, __LONGDOUBLE __y),__nextafterl,(__x,__y))
#elif defined(__CRT_HAVE___nexttowardl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nextafter,(__LONGDOUBLE __x, __LONGDOUBLE __y),__nexttowardl,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE___nexttoward) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/nextafterl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL nextafter)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nextafterl))(__x, __y); }
#endif /* ... */
#if __has_builtin(__builtin_remainderl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainderl)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remainder,(__LONGDOUBLE __x, __LONGDOUBLE __p),remainderl,{ return __builtin_remainderl(__x, __p); })
#elif __has_builtin(__builtin_dreml) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_dreml)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remainder,(__LONGDOUBLE __x, __LONGDOUBLE __p),dreml,{ return __builtin_dreml(__x, __p); })
#elif defined(__CRT_HAVE_remainderl)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remainder,(__LONGDOUBLE __x, __LONGDOUBLE __p),remainderl,(__x,__p))
#elif defined(__CRT_HAVE_dreml)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remainder,(__LONGDOUBLE __x, __LONGDOUBLE __p),dreml,(__x,__p))
#elif defined(__CRT_HAVE___remainderl)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remainder,(__LONGDOUBLE __x, __LONGDOUBLE __p),__remainderl,(__x,__p))
#elif defined(__CRT_HAVE___dreml)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,remainder,(__LONGDOUBLE __x, __LONGDOUBLE __p),__dreml,(__x,__p))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE___drem) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/remainderl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the remainder of integer division `x / p' with infinite precision */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL remainder)(__LONGDOUBLE __x, __LONGDOUBLE __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainderl))(__x, __p); }
#endif /* ... */
#if __has_builtin(__builtin_ilogbl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ilogbl)
/* Return the binary exponent of `x', which must be nonzero */
__CEIREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,ilogb,(__LONGDOUBLE __x),ilogbl,{ return __builtin_ilogbl(__x); })
#elif defined(__CRT_HAVE_ilogbl)
/* Return the binary exponent of `x', which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,ilogb,(__LONGDOUBLE __x),ilogbl,(__x))
#elif defined(__CRT_HAVE___ilogbl)
/* Return the binary exponent of `x', which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,ilogb,(__LONGDOUBLE __x),__ilogbl,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_ilogb) || defined(__CRT_HAVE___ilogb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/ilogbl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the binary exponent of `x', which must be nonzero */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED int __NOTHROW(__LIBCCALL ilogb)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ilogbl))(__x); }
#endif /* ... */
} /* extern "C++" */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */
#ifdef __USE_ISOC99
extern "C++" {
#if __has_builtin(__builtin_exp2f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp2f)
/* Compute base-2 exponential of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,exp2,(float __x),exp2f,{ return __builtin_exp2f(__x); })
#elif defined(__CRT_HAVE_exp2f)
/* Compute base-2 exponential of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,exp2,(float __x),exp2f,(__x))
#elif defined(__CRT_HAVE___exp2f)
/* Compute base-2 exponential of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,exp2,(float __x),__exp2f,(__x))
#elif defined(__CRT_HAVE_exp2) || defined(__CRT_HAVE___exp2)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/exp2f.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Compute base-2 exponential of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL exp2)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(exp2f))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_log2f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log2f)
/* Compute base-2 logarithm of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,log2,(float __x),log2f,{ return __builtin_log2f(__x); })
#elif defined(__CRT_HAVE_log2f)
/* Compute base-2 logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,log2,(float __x),log2f,(__x))
#elif defined(__CRT_HAVE___log2f)
/* Compute base-2 logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,log2,(float __x),__log2f,(__x))
#elif defined(__CRT_HAVE_log2) || defined(__CRT_HAVE___log2)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/log2f.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Compute base-2 logarithm of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL log2)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log2f))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_copysignf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_copysignf)
/* Return `x' with its signed changed to `y's */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,copysign,(float __num, float __sign),copysignf,{ return __builtin_copysignf(__num, __sign); })
#elif defined(__CRT_HAVE_copysignf)
/* Return `x' with its signed changed to `y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,copysign,(float __num, float __sign),copysignf,(__num,__sign))
#elif defined(__CRT_HAVE___copysignf)
/* Return `x' with its signed changed to `y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,copysign,(float __num, float __sign),__copysignf,(__num,__sign))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/copysignf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return `x' with its signed changed to `y's */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL copysign)(float __num, float __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(copysignf))(__num, __sign); }
#endif /* !... */
#if __has_builtin(__builtin_tgammaf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tgammaf)
/* True gamma function */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,tgamma,(float __x),tgammaf,{ return __builtin_tgammaf(__x); })
#elif defined(__CRT_HAVE_tgammaf)
/* True gamma function */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,tgamma,(float __x),tgammaf,(__x))
#elif defined(__CRT_HAVE___tgammaf)
/* True gamma function */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,tgamma,(float __x),__tgammaf,(__x))
#elif defined(__CRT_HAVE_tgamma) || defined(__CRT_HAVE___tgamma)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/tgammaf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* True gamma function */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL tgamma)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tgammaf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_nexttowardf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nexttowardf)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nexttoward,(float __x, __LONGDOUBLE __y),nexttowardf,{ return __builtin_nexttowardf(__x, __y); })
#elif defined(__CRT_HAVE_nexttowardf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nexttoward,(float __x, __LONGDOUBLE __y),nexttowardf,(__x,__y))
#elif defined(__CRT_HAVE___nexttowardf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nexttoward,(float __x, __LONGDOUBLE __y),__nexttowardf,(__x,__y))
#elif ((defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)) && defined(__IEEE854_LONG_DOUBLE_TYPE__)) || defined(__CRT_HAVE_nextafterl) || defined(__CRT_HAVE_nexttowardl) || defined(__CRT_HAVE___nextafterl) || defined(__CRT_HAVE___nexttowardl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE___nexttoward) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/nexttowardf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL nexttoward)(float __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nexttowardf))(__x, __y); }
#endif /* ... */
#if __has_builtin(__builtin_scalbnf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbnf)
/* Return `x' times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbn,(float __x, int __n),scalbnf,{ return __builtin_scalbnf(__x, __n); })
#elif defined(__CRT_HAVE_scalbnf)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbn,(float __x, int __n),scalbnf,(__x,__n))
#elif defined(__CRT_HAVE___scalbnf)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbn,(float __x, int __n),__scalbnf,(__x,__n))
#elif defined(__CRT_HAVE_scalblnf) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbn,(float __x, int __n),scalblnf,(__x,__n))
#elif defined(__CRT_HAVE___scalblnf) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbn,(float __x, int __n),__scalblnf,(__x,__n))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_scalbn) || defined(__CRT_HAVE___scalbn) || (defined(__CRT_HAVE_scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/scalbnf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return `x' times (2 to the Nth power) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL scalbn)(float __x, int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbnf))(__x, __n); }
#endif /* ... */
#if __has_builtin(__builtin_scalblnf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalblnf)
/* Return `x' times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbln,(float __x, long int __n),scalblnf,{ return __builtin_scalblnf(__x, __n); })
#elif defined(__CRT_HAVE_scalblnf)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbln,(float __x, long int __n),scalblnf,(__x,__n))
#elif defined(__CRT_HAVE___scalblnf)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbln,(float __x, long int __n),__scalblnf,(__x,__n))
#elif defined(__CRT_HAVE_scalbnf) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbln,(float __x, long int __n),scalbnf,(__x,__n))
#elif defined(__CRT_HAVE___scalbnf) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,scalbln,(float __x, long int __n),__scalbnf,(__x,__n))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_scalbln) || defined(__CRT_HAVE___scalbln) || (defined(__CRT_HAVE_scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/scalblnf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return `x' times (2 to the Nth power) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL scalbln)(float __x, long int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalblnf))(__x, __n); }
#endif /* ... */
#if __has_builtin(__builtin_rintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nearbyint,(float __x),rintf,{ return __builtin_rintf(__x); })
#elif __has_builtin(__builtin_nearbyintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nearbyintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nearbyint,(float __x),nearbyintf,{ return __builtin_nearbyintf(__x); })
#elif defined(__CRT_HAVE_rintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nearbyint,(float __x),rintf,(__x))
#elif defined(__CRT_HAVE_nearbyintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nearbyint,(float __x),nearbyintf,(__x))
#elif defined(__CRT_HAVE___rintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nearbyint,(float __x),__rintf,(__x))
#elif defined(__CRT_HAVE___nearbyintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,nearbyint,(float __x),__nearbyintf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE_nearbyint) || defined(__CRT_HAVE___rint) || defined(__CRT_HAVE___nearbyint) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/rintf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL nearbyint)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rintf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_roundf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_roundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,round,(float __x),roundf,{ return __builtin_roundf(__x); })
#elif defined(__CRT_HAVE_roundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,round,(float __x),roundf,(__x))
#elif defined(__CRT_HAVE___roundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,round,(float __x),__roundf,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/roundf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL round)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(roundf))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_truncf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_truncf)
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,trunc,(float __x),truncf,{ return __builtin_truncf(__x); })
#elif defined(__CRT_HAVE_truncf)
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,trunc,(float __x),truncf,(__x))
#elif defined(__CRT_HAVE___truncf)
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,trunc,(float __x),__truncf,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/truncf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL trunc)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(truncf))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_remquof) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remquof)
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__CEIREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),float,__NOTHROW,remquo,(float __x, float __y, int *__pquo),remquof,{ return __builtin_remquof(__x, __y, __pquo); })
#elif defined(__CRT_HAVE_remquof)
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),float,__NOTHROW,remquo,(float __x, float __y, int *__pquo),remquof,(__x,__y,__pquo))
#elif defined(__CRT_HAVE___remquof)
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),float,__NOTHROW,remquo,(float __x, float __y, int *__pquo),__remquof,(__x,__y,__pquo))
#elif defined(__CRT_HAVE_remquo) || defined(__CRT_HAVE___remquo)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/remquof.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) float __NOTHROW(__LIBCCALL remquo)(float __x, float __y, int *__pquo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remquof))(__x, __y, __pquo); }
#endif /* ... */
#if __has_builtin(__builtin_lrintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lrintf)
/* Round `x' to nearest integral value according to current rounding direction */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lrint,(float __x),lrintf,{ return __builtin_lrintf(__x); })
#elif defined(__CRT_HAVE_lrintf)
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lrint,(float __x),lrintf,(__x))
#elif defined(__CRT_HAVE___lrintf)
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lrint,(float __x),__lrintf,(__x))
#elif defined(__CRT_HAVE_llrintf) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lrint,(float __x),llrintf,(__x))
#elif defined(__CRT_HAVE___llrintf) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lrint,(float __x),__llrintf,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/lrintf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Round `x' to nearest integral value according to current rounding direction */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL lrint)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lrintf))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_lroundf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lroundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lround,(float __x),lroundf,{ return __builtin_lroundf(__x); })
#elif defined(__CRT_HAVE_lroundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lround,(float __x),lroundf,(__x))
#elif defined(__CRT_HAVE___lroundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lround,(float __x),__lroundf,(__x))
#elif defined(__CRT_HAVE_llroundf) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lround,(float __x),llroundf,(__x))
#elif defined(__CRT_HAVE___llroundf) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lround,(float __x),__llroundf,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/lroundf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL lround)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lroundf))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_fdimf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fdimf)
/* Return positive difference between `x' and `y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fdim,(float __x, float __y),fdimf,{ return __builtin_fdimf(__x, __y); })
#elif defined(__CRT_HAVE_fdimf)
/* Return positive difference between `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fdim,(float __x, float __y),fdimf,(__x,__y))
#elif defined(__CRT_HAVE___fdimf)
/* Return positive difference between `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fdim,(float __x, float __y),__fdimf,(__x,__y))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/fdimf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return positive difference between `x' and `y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL fdim)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fdimf))(__x, __y); }
#endif /* !... */
#if __has_builtin(__builtin_fmaxf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmaxf)
/* Return maximum numeric value from `x' and `y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fmax,(float __x, float __y),fmaxf,{ return __builtin_fmaxf(__x, __y); })
#elif defined(__CRT_HAVE_fmaxf)
/* Return maximum numeric value from `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fmax,(float __x, float __y),fmaxf,(__x,__y))
#elif defined(__CRT_HAVE___fmaxf)
/* Return maximum numeric value from `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fmax,(float __x, float __y),__fmaxf,(__x,__y))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/fmaxf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return maximum numeric value from `x' and `y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL fmax)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmaxf))(__x, __y); }
#endif /* !... */
#if __has_builtin(__builtin_fminf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fminf)
/* Return minimum numeric value from `x' and `y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fmin,(float __x, float __y),fminf,{ return __builtin_fminf(__x, __y); })
#elif defined(__CRT_HAVE_fminf)
/* Return minimum numeric value from `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fmin,(float __x, float __y),fminf,(__x,__y))
#elif defined(__CRT_HAVE___fminf)
/* Return minimum numeric value from `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fmin,(float __x, float __y),__fminf,(__x,__y))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/fminf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return minimum numeric value from `x' and `y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL fmin)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fminf))(__x, __y); }
#endif /* !... */
#if __has_builtin(__builtin_fmaf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmaf)
/* Multiply-add function computed as a ternary operation */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fma,(float __x, float __y, float __z),fmaf,{ return __builtin_fmaf(__x, __y, __z); })
#elif defined(__CRT_HAVE_fmaf)
/* Multiply-add function computed as a ternary operation */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fma,(float __x, float __y, float __z),fmaf,(__x,__y,__z))
#elif defined(__CRT_HAVE___fmaf)
/* Multiply-add function computed as a ternary operation */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,fma,(float __x, float __y, float __z),__fmaf,(__x,__y,__z))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/fmaf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Multiply-add function computed as a ternary operation */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL fma)(float __x, float __y, float __z) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmaf))(__x, __y, __z); }
#endif /* !... */
} /* extern "C++" */
#ifdef __COMPILER_HAVE_LONGLONG
extern "C++" {
#if __has_builtin(__builtin_llrintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llrintf)
/* Round `x' to nearest integral value according to current rounding direction */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrint,(float __x),llrintf,{ return __builtin_llrintf(__x); })
#elif defined(__CRT_HAVE_llrintf)
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrint,(float __x),llrintf,(__x))
#elif defined(__CRT_HAVE___llrintf)
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrint,(float __x),__llrintf,(__x))
#elif defined(__CRT_HAVE_lrintf) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrint,(float __x),lrintf,(__x))
#elif defined(__CRT_HAVE___lrintf) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrint,(float __x),__lrintf,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/llrintf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Round `x' to nearest integral value according to current rounding direction */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL llrint)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llrintf))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_llroundf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llroundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llround,(float __x),llroundf,{ return __builtin_llroundf(__x); })
#elif defined(__CRT_HAVE_llroundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llround,(float __x),llroundf,(__x))
#elif defined(__CRT_HAVE___llroundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llround,(float __x),__llroundf,(__x))
#elif defined(__CRT_HAVE_lroundf) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llround,(float __x),lroundf,(__x))
#elif defined(__CRT_HAVE___lroundf) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llround,(float __x),__lroundf,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/llroundf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL llround)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llroundf))(__x); }
#endif /* !... */
} /* extern "C++" */
#endif /* __COMPILER_HAVE_LONGLONG */
#ifdef __COMPILER_HAVE_LONGDOUBLE
extern "C++" {
#if __has_builtin(__builtin_exp2l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp2l)
/* Compute base-2 exponential of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp2,(__LONGDOUBLE __x),exp2l,{ return __builtin_exp2l(__x); })
#elif defined(__CRT_HAVE_exp2l)
/* Compute base-2 exponential of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp2,(__LONGDOUBLE __x),exp2l,(__x))
#elif defined(__CRT_HAVE___exp2l)
/* Compute base-2 exponential of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp2,(__LONGDOUBLE __x),__exp2l,(__x))
#elif defined(__CRT_HAVE_exp2) || defined(__CRT_HAVE___exp2)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/exp2l.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Compute base-2 exponential of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL exp2)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(exp2l))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_log2l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log2l)
/* Compute base-2 logarithm of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log2,(__LONGDOUBLE __x),log2l,{ return __builtin_log2l(__x); })
#elif defined(__CRT_HAVE_log2l)
/* Compute base-2 logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log2,(__LONGDOUBLE __x),log2l,(__x))
#elif defined(__CRT_HAVE___log2l)
/* Compute base-2 logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,log2,(__LONGDOUBLE __x),__log2l,(__x))
#elif defined(__CRT_HAVE_log2) || defined(__CRT_HAVE___log2)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/log2l.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Compute base-2 logarithm of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL log2)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log2l))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_copysignl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_copysignl)
/* Return `x' with its signed changed to `y's */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,copysign,(__LONGDOUBLE __num, __LONGDOUBLE __sign),copysignl,{ return __builtin_copysignl(__num, __sign); })
#elif defined(__CRT_HAVE_copysignl)
/* Return `x' with its signed changed to `y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,copysign,(__LONGDOUBLE __num, __LONGDOUBLE __sign),copysignl,(__num,__sign))
#elif defined(__CRT_HAVE___copysignl)
/* Return `x' with its signed changed to `y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,copysign,(__LONGDOUBLE __num, __LONGDOUBLE __sign),__copysignl,(__num,__sign))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/copysignl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return `x' with its signed changed to `y's */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL copysign)(__LONGDOUBLE __num, __LONGDOUBLE __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(copysignl))(__num, __sign); }
#endif /* !... */
#if __has_builtin(__builtin_tgammal) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tgammal)
/* True gamma function */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tgamma,(__LONGDOUBLE __x),tgammal,{ return __builtin_tgammal(__x); })
#elif defined(__CRT_HAVE_tgammal)
/* True gamma function */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tgamma,(__LONGDOUBLE __x),tgammal,(__x))
#elif defined(__CRT_HAVE___tgammal)
/* True gamma function */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,tgamma,(__LONGDOUBLE __x),__tgammal,(__x))
#elif defined(__CRT_HAVE_tgamma) || defined(__CRT_HAVE___tgamma)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/tgammal.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* True gamma function */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL tgamma)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tgammal))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_nextafterl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nextafterl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nexttoward,(__LONGDOUBLE __x, __LONGDOUBLE __y),nextafterl,{ return __builtin_nextafterl(__x, __y); })
#elif __has_builtin(__builtin_nexttowardl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nexttowardl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nexttoward,(__LONGDOUBLE __x, __LONGDOUBLE __y),nexttowardl,{ return __builtin_nexttowardl(__x); })
#elif defined(__CRT_HAVE_nextafterl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nexttoward,(__LONGDOUBLE __x, __LONGDOUBLE __y),nextafterl,(__x,__y))
#elif defined(__CRT_HAVE_nexttowardl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nexttoward,(__LONGDOUBLE __x, __LONGDOUBLE __y),nexttowardl,(__x,__y))
#elif defined(__CRT_HAVE___nextafterl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nexttoward,(__LONGDOUBLE __x, __LONGDOUBLE __y),__nextafterl,(__x,__y))
#elif defined(__CRT_HAVE___nexttowardl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nexttoward,(__LONGDOUBLE __x, __LONGDOUBLE __y),__nexttowardl,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE___nexttoward) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/nextafterl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL nexttoward)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nextafterl))(__x, __y); }
#endif /* ... */
#if __has_builtin(__builtin_scalbnl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbnl)
/* Return `x' times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbn,(__LONGDOUBLE __x, int __n),scalbnl,{ return __builtin_scalbnl(__x, __n); })
#elif defined(__CRT_HAVE_scalbnl)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbn,(__LONGDOUBLE __x, int __n),scalbnl,(__x,__n))
#elif defined(__CRT_HAVE___scalbnl)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbn,(__LONGDOUBLE __x, int __n),__scalbnl,(__x,__n))
#elif defined(__CRT_HAVE_scalblnl) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbn,(__LONGDOUBLE __x, int __n),scalblnl,(__x,__n))
#elif defined(__CRT_HAVE___scalblnl) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbn,(__LONGDOUBLE __x, int __n),__scalblnl,(__x,__n))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_scalbn) || defined(__CRT_HAVE___scalbn) || (defined(__CRT_HAVE_scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/scalbnl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return `x' times (2 to the Nth power) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL scalbn)(__LONGDOUBLE __x, int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbnl))(__x, __n); }
#endif /* ... */
#if __has_builtin(__builtin_scalblnl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalblnl)
/* Return `x' times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbln,(__LONGDOUBLE __x, long int __n),scalblnl,{ return __builtin_scalblnl(__x, __n); })
#elif defined(__CRT_HAVE_scalblnl)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbln,(__LONGDOUBLE __x, long int __n),scalblnl,(__x,__n))
#elif defined(__CRT_HAVE___scalblnl)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbln,(__LONGDOUBLE __x, long int __n),__scalblnl,(__x,__n))
#elif defined(__CRT_HAVE_scalbnl) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbln,(__LONGDOUBLE __x, long int __n),scalbnl,(__x,__n))
#elif defined(__CRT_HAVE___scalbnl) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbln,(__LONGDOUBLE __x, long int __n),__scalbnl,(__x,__n))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_scalbln) || defined(__CRT_HAVE___scalbln) || (defined(__CRT_HAVE_scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/scalblnl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return `x' times (2 to the Nth power) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL scalbln)(__LONGDOUBLE __x, long int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalblnl))(__x, __n); }
#endif /* ... */
#if __has_builtin(__builtin_rintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nearbyint,(__LONGDOUBLE __x),rintl,{ return __builtin_rintl(__x); })
#elif __has_builtin(__builtin_nearbyintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nearbyintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nearbyint,(__LONGDOUBLE __x),nearbyintl,{ return __builtin_nearbyintl(__x); })
#elif defined(__CRT_HAVE_rintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nearbyint,(__LONGDOUBLE __x),rintl,(__x))
#elif defined(__CRT_HAVE_nearbyintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nearbyint,(__LONGDOUBLE __x),nearbyintl,(__x))
#elif defined(__CRT_HAVE___rintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nearbyint,(__LONGDOUBLE __x),__rintl,(__x))
#elif defined(__CRT_HAVE___nearbyintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,nearbyint,(__LONGDOUBLE __x),__nearbyintl,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE_nearbyint) || defined(__CRT_HAVE___rint) || defined(__CRT_HAVE___nearbyint) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/rintl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL nearbyint)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rintl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_roundl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_roundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,round,(__LONGDOUBLE __x),roundl,{ return __builtin_roundl(__x); })
#elif defined(__CRT_HAVE_roundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,round,(__LONGDOUBLE __x),roundl,(__x))
#elif defined(__CRT_HAVE___roundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,round,(__LONGDOUBLE __x),__roundl,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/roundl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL round)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(roundl))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_truncl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_truncl)
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,trunc,(__LONGDOUBLE __x),truncl,{ return __builtin_truncl(__x); })
#elif defined(__CRT_HAVE_truncl)
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,trunc,(__LONGDOUBLE __x),truncl,(__x))
#elif defined(__CRT_HAVE___truncl)
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,trunc,(__LONGDOUBLE __x),__truncl,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/truncl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL trunc)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(truncl))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_remquol) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remquol)
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__CEIREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),__LONGDOUBLE,__NOTHROW,remquo,(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo),remquol,{ return __builtin_remquol(__x, __y, __pquo); })
#elif defined(__CRT_HAVE_remquol)
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),__LONGDOUBLE,__NOTHROW,remquo,(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo),remquol,(__x,__y,__pquo))
#elif defined(__CRT_HAVE___remquol)
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),__LONGDOUBLE,__NOTHROW,remquo,(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo),__remquol,(__x,__y,__pquo))
#elif defined(__CRT_HAVE_remquo) || defined(__CRT_HAVE___remquo)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/remquol.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __LONGDOUBLE __NOTHROW(__LIBCCALL remquo)(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remquol))(__x, __y, __pquo); }
#endif /* ... */
#if __has_builtin(__builtin_lrintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lrintl)
/* Round `x' to nearest integral value according to current rounding direction */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lrint,(__LONGDOUBLE __x),lrintl,{ return __builtin_lrintl(__x); })
#elif defined(__CRT_HAVE_lrintl)
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lrint,(__LONGDOUBLE __x),lrintl,(__x))
#elif defined(__CRT_HAVE___lrintl)
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lrint,(__LONGDOUBLE __x),__lrintl,(__x))
#elif defined(__CRT_HAVE_llrintl) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lrint,(__LONGDOUBLE __x),llrintl,(__x))
#elif defined(__CRT_HAVE___llrintl) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lrint,(__LONGDOUBLE __x),__llrintl,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/lrintl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Round `x' to nearest integral value according to current rounding direction */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL lrint)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lrintl))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_lroundl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lroundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lround,(__LONGDOUBLE __x),lroundl,{ return __builtin_lroundl(__x); })
#elif defined(__CRT_HAVE_lroundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lround,(__LONGDOUBLE __x),lroundl,(__x))
#elif defined(__CRT_HAVE___lroundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lround,(__LONGDOUBLE __x),__lroundl,(__x))
#elif defined(__CRT_HAVE_llroundl) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lround,(__LONGDOUBLE __x),llroundl,(__x))
#elif defined(__CRT_HAVE___llroundl) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,lround,(__LONGDOUBLE __x),__llroundl,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/lroundl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL lround)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lroundl))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_fdiml) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fdiml)
/* Return positive difference between `x' and `y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fdim,(__LONGDOUBLE __x, __LONGDOUBLE __y),fdiml,{ return __builtin_fdiml(__x, __y); })
#elif defined(__CRT_HAVE_fdiml)
/* Return positive difference between `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fdim,(__LONGDOUBLE __x, __LONGDOUBLE __y),fdiml,(__x,__y))
#elif defined(__CRT_HAVE___fdiml)
/* Return positive difference between `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fdim,(__LONGDOUBLE __x, __LONGDOUBLE __y),__fdiml,(__x,__y))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/fdiml.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return positive difference between `x' and `y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL fdim)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fdiml))(__x, __y); }
#endif /* !... */
#if __has_builtin(__builtin_fmaxl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmaxl)
/* Return maximum numeric value from `x' and `y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmax,(__LONGDOUBLE __x, __LONGDOUBLE __y),fmaxl,{ return __builtin_fmaxl(__x, __y); })
#elif defined(__CRT_HAVE_fmaxl)
/* Return maximum numeric value from `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmax,(__LONGDOUBLE __x, __LONGDOUBLE __y),fmaxl,(__x,__y))
#elif defined(__CRT_HAVE___fmaxl)
/* Return maximum numeric value from `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmax,(__LONGDOUBLE __x, __LONGDOUBLE __y),__fmaxl,(__x,__y))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/fmaxl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return maximum numeric value from `x' and `y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL fmax)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmaxl))(__x, __y); }
#endif /* !... */
#if __has_builtin(__builtin_fminl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fminl)
/* Return minimum numeric value from `x' and `y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmin,(__LONGDOUBLE __x, __LONGDOUBLE __y),fminl,{ return __builtin_fminl(__x, __y); })
#elif defined(__CRT_HAVE_fminl)
/* Return minimum numeric value from `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmin,(__LONGDOUBLE __x, __LONGDOUBLE __y),fminl,(__x,__y))
#elif defined(__CRT_HAVE___fminl)
/* Return minimum numeric value from `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fmin,(__LONGDOUBLE __x, __LONGDOUBLE __y),__fminl,(__x,__y))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/fminl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return minimum numeric value from `x' and `y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL fmin)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fminl))(__x, __y); }
#endif /* !... */
#if __has_builtin(__builtin_fmal) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmal)
/* Multiply-add function computed as a ternary operation */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fma,(__LONGDOUBLE __x, __LONGDOUBLE __y, __LONGDOUBLE __z),fmal,{ return __builtin_fmal(__x, __y, __z); })
#elif defined(__CRT_HAVE_fmal)
/* Multiply-add function computed as a ternary operation */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fma,(__LONGDOUBLE __x, __LONGDOUBLE __y, __LONGDOUBLE __z),fmal,(__x,__y,__z))
#elif defined(__CRT_HAVE___fmal)
/* Multiply-add function computed as a ternary operation */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,fma,(__LONGDOUBLE __x, __LONGDOUBLE __y, __LONGDOUBLE __z),__fmal,(__x,__y,__z))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/fmal.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Multiply-add function computed as a ternary operation */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL fma)(__LONGDOUBLE __x, __LONGDOUBLE __y, __LONGDOUBLE __z) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmal))(__x, __y, __z); }
#endif /* !... */
} /* extern "C++" */
#ifdef __COMPILER_HAVE_LONGLONG
extern "C++" {
#if __has_builtin(__builtin_llrintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llrintl)
/* Round `x' to nearest integral value according to current rounding direction */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrint,(__LONGDOUBLE __x),llrintl,{ return __builtin_llrintl(__x); })
#elif defined(__CRT_HAVE_llrintl)
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrint,(__LONGDOUBLE __x),llrintl,(__x))
#elif defined(__CRT_HAVE___llrintl)
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrint,(__LONGDOUBLE __x),__llrintl,(__x))
#elif defined(__CRT_HAVE_lrintl) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrint,(__LONGDOUBLE __x),lrintl,(__x))
#elif defined(__CRT_HAVE___lrintl) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llrint,(__LONGDOUBLE __x),__lrintl,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/llrintl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Round `x' to nearest integral value according to current rounding direction */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL llrint)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llrintl))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_llroundl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llroundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llround,(__LONGDOUBLE __x),llroundl,{ return __builtin_llroundl(__x); })
#elif defined(__CRT_HAVE_llroundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llround,(__LONGDOUBLE __x),llroundl,(__x))
#elif defined(__CRT_HAVE___llroundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llround,(__LONGDOUBLE __x),__llroundl,(__x))
#elif defined(__CRT_HAVE_lroundl) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llround,(__LONGDOUBLE __x),lroundl,(__x))
#elif defined(__CRT_HAVE___lroundl) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,llround,(__LONGDOUBLE __x),__lroundl,(__x))
#else /* ... */
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/llroundl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL llround)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llroundl))(__x); }
#endif /* !... */
} /* extern "C++" */
#endif /* __COMPILER_HAVE_LONGLONG */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */
#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
extern "C++" {
#if __has_builtin(__builtin_hypotf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_hypotf)
/* Return `sqrt(x*x + y*y)' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,hypot,(float __x, float __y),hypotf,{ return __builtin_hypotf(__x, __y); })
#elif defined(__CRT_HAVE_hypotf)
/* Return `sqrt(x*x + y*y)' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,hypot,(float __x, float __y),hypotf,(__x,__y))
#elif defined(__CRT_HAVE___hypotf)
/* Return `sqrt(x*x + y*y)' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,hypot,(float __x, float __y),__hypotf,(__x,__y))
#elif defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE___hypot)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/hypotf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return `sqrt(x*x + y*y)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL hypot)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hypotf))(__x, __y); }
#endif /* ... */
#if __has_builtin(__builtin_erff) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erff)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,erf,(float __x),erff,{ return __builtin_erff(__x); })
#elif defined(__CRT_HAVE_erff)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,erf,(float __x),erff,(__x))
#elif defined(__CRT_HAVE___erff)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,erf,(float __x),__erff,(__x))
#elif defined(__CRT_HAVE_erf) || defined(__CRT_HAVE___erf)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/erff.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL erf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(erff))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_erfcf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erfcf)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,erfc,(float __x),erfcf,{ return __builtin_erfcf(__x); })
#elif defined(__CRT_HAVE_erfcf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,erfc,(float __x),erfcf,(__x))
#elif defined(__CRT_HAVE___erfcf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,erfc,(float __x),__erfcf,(__x))
#elif defined(__CRT_HAVE_erfc) || defined(__CRT_HAVE___erfc)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/erfcf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL erfc)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(erfcf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_lgammaf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgammaf)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,lgamma,(float __x),lgammaf,{ return __builtin_lgammaf(__x); })
#elif __has_builtin(__builtin_gammaf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_gammaf)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,lgamma,(float __x),gammaf,{ return __builtin_gammaf(__x); })
#elif defined(__CRT_HAVE_lgammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,lgamma,(float __x),lgammaf,(__x))
#elif defined(__CRT_HAVE_gammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,lgamma,(float __x),gammaf,(__x))
#elif defined(__CRT_HAVE___lgammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,lgamma,(float __x),__lgammaf,(__x))
#elif defined(__CRT_HAVE___gammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,lgamma,(float __x),__gammaf,(__x))
#elif defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE_gamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/lgammaf.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL lgamma)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammaf))(__x); }
#endif /* ... */
} /* extern "C++" */
#ifdef __COMPILER_HAVE_LONGDOUBLE
extern "C++" {
#if __has_builtin(__builtin_hypotl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_hypotl)
/* Return `sqrt(x*x + y*y)' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,hypot,(__LONGDOUBLE __x, __LONGDOUBLE __y),hypotl,{ return __builtin_hypotl(__x, __y); })
#elif defined(__CRT_HAVE_hypotl)
/* Return `sqrt(x*x + y*y)' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,hypot,(__LONGDOUBLE __x, __LONGDOUBLE __y),hypotl,(__x,__y))
#elif defined(__CRT_HAVE___hypotl)
/* Return `sqrt(x*x + y*y)' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,hypot,(__LONGDOUBLE __x, __LONGDOUBLE __y),__hypotl,(__x,__y))
#elif defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE___hypot)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/hypotl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return `sqrt(x*x + y*y)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL hypot)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hypotl))(__x, __y); }
#endif /* ... */
#if __has_builtin(__builtin_erfl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erfl)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erf,(__LONGDOUBLE __x),erfl,{ return __builtin_erfl(__x); })
#elif defined(__CRT_HAVE_erfl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erf,(__LONGDOUBLE __x),erfl,(__x))
#elif defined(__CRT_HAVE___erfl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erf,(__LONGDOUBLE __x),__erfl,(__x))
#elif defined(__CRT_HAVE_erf) || defined(__CRT_HAVE___erf)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/erfl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL erf)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(erfl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_erfcl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erfcl)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erfc,(__LONGDOUBLE __x),erfcl,{ return __builtin_erfcl(__x); })
#elif defined(__CRT_HAVE_erfcl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erfc,(__LONGDOUBLE __x),erfcl,(__x))
#elif defined(__CRT_HAVE___erfcl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,erfc,(__LONGDOUBLE __x),__erfcl,(__x))
#elif defined(__CRT_HAVE_erfc) || defined(__CRT_HAVE___erfc)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/erfcl.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL erfc)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(erfcl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_lgammal) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgammal)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgamma,(__LONGDOUBLE __x),lgammal,{ return __builtin_lgammal(__x); })
#elif __has_builtin(__builtin_gammal) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_gammal)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgamma,(__LONGDOUBLE __x),gammal,{ return __builtin_gammal(__x); })
#elif defined(__CRT_HAVE_lgammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgamma,(__LONGDOUBLE __x),lgammal,(__x))
#elif defined(__CRT_HAVE_gammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgamma,(__LONGDOUBLE __x),gammal,(__x))
#elif defined(__CRT_HAVE___lgammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgamma,(__LONGDOUBLE __x),__lgammal,(__x))
#elif defined(__CRT_HAVE___gammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,lgamma,(__LONGDOUBLE __x),__gammal,(__x))
#elif defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE_gamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma)
} /* extern "C++" */
__NAMESPACE_STD_END
#include <libc/local/math/lgammal.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL lgamma)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammal))(__x); }
#endif /* ... */
} /* extern "C++" */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN || __USE_ISOC99 */
#endif /* __cplusplus && __CORRECT_ISO_CPP_MATH_H_PROTO */
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_acos) || defined(__CRT_HAVE___acos)
__NAMESPACE_STD_USING(acos)
#endif /* __CRT_HAVE_acos || __CRT_HAVE___acos */
#if defined(__CRT_HAVE_asin) || defined(__CRT_HAVE___asin)
__NAMESPACE_STD_USING(asin)
#endif /* __CRT_HAVE_asin || __CRT_HAVE___asin */
#if defined(__CRT_HAVE_atan) || defined(__CRT_HAVE___atan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(atan)
#endif /* __CRT_HAVE_atan || __CRT_HAVE___atan || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(atan2)
#endif /* __CRT_HAVE_atan2 || __CRT_HAVE___atan2 || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos)
__NAMESPACE_STD_USING(cos)
#endif /* __CRT_HAVE_cos || __CRT_HAVE___cos */
#if defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)
__NAMESPACE_STD_USING(sin)
#endif /* __CRT_HAVE_sin || __CRT_HAVE___sin */
#if defined(__CRT_HAVE_tan) || defined(__CRT_HAVE___tan)
__NAMESPACE_STD_USING(tan)
#endif /* __CRT_HAVE_tan || __CRT_HAVE___tan */
#if defined(__CRT_HAVE_acosf) || defined(__CRT_HAVE___acosf) || defined(__CRT_HAVE_acos) || defined(__CRT_HAVE___acos)
__NAMESPACE_STD_USING(acosf)
#endif /* __CRT_HAVE_acosf || __CRT_HAVE___acosf || __CRT_HAVE_acos || __CRT_HAVE___acos */
#if defined(__CRT_HAVE_asinf) || defined(__CRT_HAVE___asinf) || defined(__CRT_HAVE_asin) || defined(__CRT_HAVE___asin)
__NAMESPACE_STD_USING(asinf)
#endif /* __CRT_HAVE_asinf || __CRT_HAVE___asinf || __CRT_HAVE_asin || __CRT_HAVE___asin */
#if defined(__CRT_HAVE_atanf) || defined(__CRT_HAVE___atanf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_atan) || defined(__CRT_HAVE___atan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(atanf)
#endif /* __CRT_HAVE_atanf || __CRT_HAVE___atanf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_atan || __CRT_HAVE___atan || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_atan2f) || defined(__CRT_HAVE___atan2f) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(atan2f)
#endif /* __CRT_HAVE_atan2f || __CRT_HAVE___atan2f || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_atan2 || __CRT_HAVE___atan2 || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_cosf) || defined(__CRT_HAVE___cosf) || defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos)
__NAMESPACE_STD_USING(cosf)
#endif /* __CRT_HAVE_cosf || __CRT_HAVE___cosf || __CRT_HAVE_cos || __CRT_HAVE___cos */
#if defined(__CRT_HAVE_sinf) || defined(__CRT_HAVE___sinf) || defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)
__NAMESPACE_STD_USING(sinf)
#endif /* __CRT_HAVE_sinf || __CRT_HAVE___sinf || __CRT_HAVE_sin || __CRT_HAVE___sin */
#if defined(__CRT_HAVE_tanf) || defined(__CRT_HAVE___tanf) || defined(__CRT_HAVE_tan) || defined(__CRT_HAVE___tan)
__NAMESPACE_STD_USING(tanf)
#endif /* __CRT_HAVE_tanf || __CRT_HAVE___tanf || __CRT_HAVE_tan || __CRT_HAVE___tan */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_acosl) || defined(__CRT_HAVE___acosl) || defined(__CRT_HAVE_acos) || defined(__CRT_HAVE___acos)
__NAMESPACE_STD_USING(acosl)
#endif /* __CRT_HAVE_acosl || __CRT_HAVE___acosl || __CRT_HAVE_acos || __CRT_HAVE___acos */
#if defined(__CRT_HAVE_asinl) || defined(__CRT_HAVE___asinl) || defined(__CRT_HAVE_asin) || defined(__CRT_HAVE___asin)
__NAMESPACE_STD_USING(asinl)
#endif /* __CRT_HAVE_asinl || __CRT_HAVE___asinl || __CRT_HAVE_asin || __CRT_HAVE___asin */
#if defined(__CRT_HAVE_atanl) || defined(__CRT_HAVE___atanl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_atan) || defined(__CRT_HAVE___atan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(atanl)
#endif /* __CRT_HAVE_atanl || __CRT_HAVE___atanl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_atan || __CRT_HAVE___atan || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_atan2l) || defined(__CRT_HAVE___atan2l) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(atan2l)
#endif /* __CRT_HAVE_atan2l || __CRT_HAVE___atan2l || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_atan2 || __CRT_HAVE___atan2 || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_cosl) || defined(__CRT_HAVE___cosl) || defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos)
__NAMESPACE_STD_USING(cosl)
#endif /* __CRT_HAVE_cosl || __CRT_HAVE___cosl || __CRT_HAVE_cos || __CRT_HAVE___cos */
#if defined(__CRT_HAVE_sinl) || defined(__CRT_HAVE___sinl) || defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)
__NAMESPACE_STD_USING(sinl)
#endif /* __CRT_HAVE_sinl || __CRT_HAVE___sinl || __CRT_HAVE_sin || __CRT_HAVE___sin */
#if defined(__CRT_HAVE_tanl) || defined(__CRT_HAVE___tanl) || defined(__CRT_HAVE_tan) || defined(__CRT_HAVE___tan)
__NAMESPACE_STD_USING(tanl)
#endif /* __CRT_HAVE_tanl || __CRT_HAVE___tanl || __CRT_HAVE_tan || __CRT_HAVE___tan */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

/* Hyperbolic functions. */
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_cosh) || defined(__CRT_HAVE___cosh)
__NAMESPACE_STD_USING(cosh)
#endif /* __CRT_HAVE_cosh || __CRT_HAVE___cosh */
#if defined(__CRT_HAVE_sinh) || defined(__CRT_HAVE___sinh)
__NAMESPACE_STD_USING(sinh)
#endif /* __CRT_HAVE_sinh || __CRT_HAVE___sinh */
#if defined(__CRT_HAVE_tanh) || defined(__CRT_HAVE___tanh)
__NAMESPACE_STD_USING(tanh)
#endif /* __CRT_HAVE_tanh || __CRT_HAVE___tanh */
#if defined(__CRT_HAVE_coshf) || defined(__CRT_HAVE___coshf) || defined(__CRT_HAVE_cosh) || defined(__CRT_HAVE___cosh)
__NAMESPACE_STD_USING(coshf)
#endif /* __CRT_HAVE_coshf || __CRT_HAVE___coshf || __CRT_HAVE_cosh || __CRT_HAVE___cosh */
#if defined(__CRT_HAVE_sinhf) || defined(__CRT_HAVE___sinhf) || defined(__CRT_HAVE_sinh) || defined(__CRT_HAVE___sinh)
__NAMESPACE_STD_USING(sinhf)
#endif /* __CRT_HAVE_sinhf || __CRT_HAVE___sinhf || __CRT_HAVE_sinh || __CRT_HAVE___sinh */
#if defined(__CRT_HAVE_tanhf) || defined(__CRT_HAVE___tanhf) || defined(__CRT_HAVE_tanh) || defined(__CRT_HAVE___tanh)
__NAMESPACE_STD_USING(tanhf)
#endif /* __CRT_HAVE_tanhf || __CRT_HAVE___tanhf || __CRT_HAVE_tanh || __CRT_HAVE___tanh */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_coshl) || defined(__CRT_HAVE___coshl) || defined(__CRT_HAVE_cosh) || defined(__CRT_HAVE___cosh)
__NAMESPACE_STD_USING(coshl)
#endif /* __CRT_HAVE_coshl || __CRT_HAVE___coshl || __CRT_HAVE_cosh || __CRT_HAVE___cosh */
#if defined(__CRT_HAVE_sinhl) || defined(__CRT_HAVE___sinhl) || defined(__CRT_HAVE_sinh) || defined(__CRT_HAVE___sinh)
__NAMESPACE_STD_USING(sinhl)
#endif /* __CRT_HAVE_sinhl || __CRT_HAVE___sinhl || __CRT_HAVE_sinh || __CRT_HAVE___sinh */
#if defined(__CRT_HAVE_tanhl) || defined(__CRT_HAVE___tanhl) || defined(__CRT_HAVE_tanh) || defined(__CRT_HAVE___tanh)
__NAMESPACE_STD_USING(tanhl)
#endif /* __CRT_HAVE_tanhl || __CRT_HAVE___tanhl || __CRT_HAVE_tanh || __CRT_HAVE___tanh */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_acosh) || defined(__CRT_HAVE___acosh)
__NAMESPACE_STD_USING(acosh)
#endif /* __CRT_HAVE_acosh || __CRT_HAVE___acosh */
#if defined(__CRT_HAVE_asinh) || defined(__CRT_HAVE___asinh)
__NAMESPACE_STD_USING(asinh)
#endif /* __CRT_HAVE_asinh || __CRT_HAVE___asinh */
#if defined(__CRT_HAVE_atanh) || defined(__CRT_HAVE___atanh)
__NAMESPACE_STD_USING(atanh)
#endif /* __CRT_HAVE_atanh || __CRT_HAVE___atanh */
#if defined(__CRT_HAVE_acoshf) || defined(__CRT_HAVE___acoshf) || defined(__CRT_HAVE_acosh) || defined(__CRT_HAVE___acosh)
__NAMESPACE_STD_USING(acoshf)
#endif /* __CRT_HAVE_acoshf || __CRT_HAVE___acoshf || __CRT_HAVE_acosh || __CRT_HAVE___acosh */
#if defined(__CRT_HAVE_asinhf) || defined(__CRT_HAVE___asinhf) || defined(__CRT_HAVE_asinh) || defined(__CRT_HAVE___asinh)
__NAMESPACE_STD_USING(asinhf)
#endif /* __CRT_HAVE_asinhf || __CRT_HAVE___asinhf || __CRT_HAVE_asinh || __CRT_HAVE___asinh */
#if defined(__CRT_HAVE_atanhf) || defined(__CRT_HAVE___atanhf) || defined(__CRT_HAVE_atanh) || defined(__CRT_HAVE___atanh)
__NAMESPACE_STD_USING(atanhf)
#endif /* __CRT_HAVE_atanhf || __CRT_HAVE___atanhf || __CRT_HAVE_atanh || __CRT_HAVE___atanh */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_acoshl) || defined(__CRT_HAVE___acoshl) || defined(__CRT_HAVE_acosh) || defined(__CRT_HAVE___acosh)
__NAMESPACE_STD_USING(acoshl)
#endif /* __CRT_HAVE_acoshl || __CRT_HAVE___acoshl || __CRT_HAVE_acosh || __CRT_HAVE___acosh */
#if defined(__CRT_HAVE_asinhl) || defined(__CRT_HAVE___asinhl) || defined(__CRT_HAVE_asinh) || defined(__CRT_HAVE___asinh)
__NAMESPACE_STD_USING(asinhl)
#endif /* __CRT_HAVE_asinhl || __CRT_HAVE___asinhl || __CRT_HAVE_asinh || __CRT_HAVE___asinh */
#if defined(__CRT_HAVE_atanhl) || defined(__CRT_HAVE___atanhl) || defined(__CRT_HAVE_atanh) || defined(__CRT_HAVE___atanh)
__NAMESPACE_STD_USING(atanhl)
#endif /* __CRT_HAVE_atanhl || __CRT_HAVE___atanhl || __CRT_HAVE_atanh || __CRT_HAVE___atanh */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

/* Exponential and logarithmic functions. */
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_exp) || defined(__CRT_HAVE___exp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(exp)
#endif /* __CRT_HAVE_exp || __CRT_HAVE___exp || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_frexp) || defined(__CRT_HAVE___frexp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(frexp)
#endif /* __CRT_HAVE_frexp || __CRT_HAVE___frexp || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_ldexp) || defined(__CRT_HAVE___ldexp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(ldexp)
#endif /* __CRT_HAVE_ldexp || __CRT_HAVE___ldexp || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log)
__NAMESPACE_STD_USING(log)
#endif /* __CRT_HAVE_log || __CRT_HAVE___log */
#if defined(__CRT_HAVE_log10) || defined(__CRT_HAVE___log10)
__NAMESPACE_STD_USING(log10)
#endif /* __CRT_HAVE_log10 || __CRT_HAVE___log10 */
#if defined(__CRT_HAVE_modf) || defined(__CRT_HAVE___modf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(modf)
#endif /* __CRT_HAVE_modf || __CRT_HAVE___modf || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_expf) || defined(__CRT_HAVE___expf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_exp) || defined(__CRT_HAVE___exp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(expf)
#endif /* __CRT_HAVE_expf || __CRT_HAVE___expf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_exp || __CRT_HAVE___exp || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_frexpf) || defined(__CRT_HAVE___frexpf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_frexp) || defined(__CRT_HAVE___frexp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(frexpf)
#endif /* __CRT_HAVE_frexpf || __CRT_HAVE___frexpf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_frexp || __CRT_HAVE___frexp || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_ldexpf) || defined(__CRT_HAVE___ldexpf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_ldexp) || defined(__CRT_HAVE___ldexp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(ldexpf)
#endif /* __CRT_HAVE_ldexpf || __CRT_HAVE___ldexpf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_ldexp || __CRT_HAVE___ldexp || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_logf) || defined(__CRT_HAVE___logf) || defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log)
__NAMESPACE_STD_USING(logf)
#endif /* __CRT_HAVE_logf || __CRT_HAVE___logf || __CRT_HAVE_log || __CRT_HAVE___log */
#if defined(__CRT_HAVE_log10f) || defined(__CRT_HAVE___log10f) || defined(__CRT_HAVE_log10) || defined(__CRT_HAVE___log10)
__NAMESPACE_STD_USING(log10f)
#endif /* __CRT_HAVE_log10f || __CRT_HAVE___log10f || __CRT_HAVE_log10 || __CRT_HAVE___log10 */
#if defined(__CRT_HAVE_modff) || defined(__CRT_HAVE___modff) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_modf) || defined(__CRT_HAVE___modf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(modff)
#endif /* __CRT_HAVE_modff || __CRT_HAVE___modff || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_modf || __CRT_HAVE___modf || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_expl) || defined(__CRT_HAVE___expl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_exp) || defined(__CRT_HAVE___exp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(expl)
#endif /* __CRT_HAVE_expl || __CRT_HAVE___expl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_exp || __CRT_HAVE___exp || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_frexpl) || defined(__CRT_HAVE___frexpl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_frexp) || defined(__CRT_HAVE___frexp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(frexpl)
#endif /* __CRT_HAVE_frexpl || __CRT_HAVE___frexpl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_frexp || __CRT_HAVE___frexp || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_ldexpl) || defined(__CRT_HAVE___ldexpl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_ldexp) || defined(__CRT_HAVE___ldexp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(ldexpl)
#endif /* __CRT_HAVE_ldexpl || __CRT_HAVE___ldexpl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_ldexp || __CRT_HAVE___ldexp || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_logl) || defined(__CRT_HAVE___logl) || defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log)
__NAMESPACE_STD_USING(logl)
#endif /* __CRT_HAVE_logl || __CRT_HAVE___logl || __CRT_HAVE_log || __CRT_HAVE___log */
#if defined(__CRT_HAVE_log10l) || defined(__CRT_HAVE___log10l) || defined(__CRT_HAVE_log10) || defined(__CRT_HAVE___log10)
__NAMESPACE_STD_USING(log10l)
#endif /* __CRT_HAVE_log10l || __CRT_HAVE___log10l || __CRT_HAVE_log10 || __CRT_HAVE___log10 */
#if defined(__CRT_HAVE_modfl) || defined(__CRT_HAVE___modfl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_modf) || defined(__CRT_HAVE___modf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(modfl)
#endif /* __CRT_HAVE_modfl || __CRT_HAVE___modfl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_modf || __CRT_HAVE___modf || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_expm1) || defined(__CRT_HAVE___expm1) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(expm1)
#endif /* __CRT_HAVE_expm1 || __CRT_HAVE___expm1 || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_log1p) || defined(__CRT_HAVE___log1p)
__NAMESPACE_STD_USING(log1p)
#endif /* __CRT_HAVE_log1p || __CRT_HAVE___log1p */
#if defined(__CRT_HAVE_logb) || defined(__CRT_HAVE___logb) || defined(__CRT_HAVE__logb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(logb)
#endif /* __CRT_HAVE_logb || __CRT_HAVE___logb || __CRT_HAVE__logb || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_expm1f) || defined(__CRT_HAVE___expm1f) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_expm1) || defined(__CRT_HAVE___expm1) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(expm1f)
#endif /* __CRT_HAVE_expm1f || __CRT_HAVE___expm1f || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_expm1 || __CRT_HAVE___expm1 || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_log1pf) || defined(__CRT_HAVE___log1pf) || defined(__CRT_HAVE_log1p) || defined(__CRT_HAVE___log1p)
__NAMESPACE_STD_USING(log1pf)
#endif /* __CRT_HAVE_log1pf || __CRT_HAVE___log1pf || __CRT_HAVE_log1p || __CRT_HAVE___log1p */
#if defined(__CRT_HAVE_logbf) || defined(__CRT_HAVE___logbf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_logb) || defined(__CRT_HAVE___logb) || defined(__CRT_HAVE__logb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(logbf)
#endif /* __CRT_HAVE_logbf || __CRT_HAVE___logbf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_logb || __CRT_HAVE___logb || __CRT_HAVE__logb || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_expm1l) || defined(__CRT_HAVE___expm1l) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_expm1) || defined(__CRT_HAVE___expm1) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(expm1l)
#endif /* __CRT_HAVE_expm1l || __CRT_HAVE___expm1l || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_expm1 || __CRT_HAVE___expm1 || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_log1pl) || defined(__CRT_HAVE___log1pl) || defined(__CRT_HAVE_log1p) || defined(__CRT_HAVE___log1p)
__NAMESPACE_STD_USING(log1pl)
#endif /* __CRT_HAVE_log1pl || __CRT_HAVE___log1pl || __CRT_HAVE_log1p || __CRT_HAVE___log1p */
#if defined(__CRT_HAVE_logbl) || defined(__CRT_HAVE___logbl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_logb) || defined(__CRT_HAVE___logb) || defined(__CRT_HAVE__logb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(logbl)
#endif /* __CRT_HAVE_logbl || __CRT_HAVE___logbl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_logb || __CRT_HAVE___logb || __CRT_HAVE__logb || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

#ifdef __USE_ISOC99
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_exp2) || defined(__CRT_HAVE___exp2)
__NAMESPACE_STD_USING(exp2)
#endif /* __CRT_HAVE_exp2 || __CRT_HAVE___exp2 */
#if defined(__CRT_HAVE_log2) || defined(__CRT_HAVE___log2)
__NAMESPACE_STD_USING(log2)
#endif /* __CRT_HAVE_log2 || __CRT_HAVE___log2 */
#if defined(__CRT_HAVE_exp2f) || defined(__CRT_HAVE___exp2f) || defined(__CRT_HAVE_exp2) || defined(__CRT_HAVE___exp2)
__NAMESPACE_STD_USING(exp2f)
#endif /* __CRT_HAVE_exp2f || __CRT_HAVE___exp2f || __CRT_HAVE_exp2 || __CRT_HAVE___exp2 */
#if defined(__CRT_HAVE_log2f) || defined(__CRT_HAVE___log2f) || defined(__CRT_HAVE_log2) || defined(__CRT_HAVE___log2)
__NAMESPACE_STD_USING(log2f)
#endif /* __CRT_HAVE_log2f || __CRT_HAVE___log2f || __CRT_HAVE_log2 || __CRT_HAVE___log2 */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_exp2l) || defined(__CRT_HAVE___exp2l) || defined(__CRT_HAVE_exp2) || defined(__CRT_HAVE___exp2)
__NAMESPACE_STD_USING(exp2l)
#endif /* __CRT_HAVE_exp2l || __CRT_HAVE___exp2l || __CRT_HAVE_exp2 || __CRT_HAVE___exp2 */
#if defined(__CRT_HAVE_log2l) || defined(__CRT_HAVE___log2l) || defined(__CRT_HAVE_log2) || defined(__CRT_HAVE___log2)
__NAMESPACE_STD_USING(log2l)
#endif /* __CRT_HAVE_log2l || __CRT_HAVE___log2l || __CRT_HAVE_log2 || __CRT_HAVE___log2 */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */

/* Power functions. */
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(pow)
#endif /* __CRT_HAVE_pow || __CRT_HAVE___pow || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(sqrt)
#endif /* __CRT_HAVE_sqrt || __CRT_HAVE___sqrt || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_powf) || defined(__CRT_HAVE___powf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(powf)
#endif /* __CRT_HAVE_powf || __CRT_HAVE___powf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_pow || __CRT_HAVE___pow || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_sqrtf) || defined(__CRT_HAVE___sqrtf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(sqrtf)
#endif /* __CRT_HAVE_sqrtf || __CRT_HAVE___sqrtf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_sqrt || __CRT_HAVE___sqrt || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_powl) || defined(__CRT_HAVE___powl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(powl)
#endif /* __CRT_HAVE_powl || __CRT_HAVE___powl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_pow || __CRT_HAVE___pow || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_sqrtl) || defined(__CRT_HAVE___sqrtl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(sqrtl)
#endif /* __CRT_HAVE_sqrtl || __CRT_HAVE___sqrtl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_sqrt || __CRT_HAVE___sqrt || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE___hypot)
__NAMESPACE_STD_USING(hypot)
#endif /* __CRT_HAVE_hypot || __CRT_HAVE___hypot */
#if defined(__CRT_HAVE_hypotf) || defined(__CRT_HAVE___hypotf) || defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE___hypot)
__NAMESPACE_STD_USING(hypotf)
#endif /* __CRT_HAVE_hypotf || __CRT_HAVE___hypotf || __CRT_HAVE_hypot || __CRT_HAVE___hypot */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_hypotl) || defined(__CRT_HAVE___hypotl) || defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE___hypot)
__NAMESPACE_STD_USING(hypotl)
#endif /* __CRT_HAVE_hypotl || __CRT_HAVE___hypotl || __CRT_HAVE_hypot || __CRT_HAVE___hypot */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN || __USE_ISOC99 */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_cbrt) || defined(__CRT_HAVE___cbrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(cbrt)
#endif /* __CRT_HAVE_cbrt || __CRT_HAVE___cbrt || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_cbrtf) || defined(__CRT_HAVE___cbrtf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_cbrt) || defined(__CRT_HAVE___cbrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(cbrtf)
#endif /* __CRT_HAVE_cbrtf || __CRT_HAVE___cbrtf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_cbrt || __CRT_HAVE___cbrt || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_cbrtl) || defined(__CRT_HAVE___cbrtl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_cbrt) || defined(__CRT_HAVE___cbrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(cbrtl)
#endif /* __CRT_HAVE_cbrtl || __CRT_HAVE___cbrtl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_cbrt || __CRT_HAVE___cbrt || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

/* Nearest integer, absolute value, and remainder functions. */
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(ceil)
__NAMESPACE_STD_USING(fabs)
__NAMESPACE_STD_USING(floor)
#if defined(__CRT_HAVE_fmod) || defined(__CRT_HAVE___fmod) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(fmod)
#endif /* __CRT_HAVE_fmod || __CRT_HAVE___fmod || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
__NAMESPACE_STD_USING(ceilf)
__NAMESPACE_STD_USING(fabsf)
__NAMESPACE_STD_USING(floorf)
#if defined(__CRT_HAVE_fmodf) || defined(__CRT_HAVE___fmodf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_fmod) || defined(__CRT_HAVE___fmod) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(fmodf)
#endif /* __CRT_HAVE_fmodf || __CRT_HAVE___fmodf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_fmod || __CRT_HAVE___fmod || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(ceill)
__NAMESPACE_STD_USING(fabsl)
__NAMESPACE_STD_USING(floorl)
#if defined(__CRT_HAVE_fmodl) || defined(__CRT_HAVE___fmodl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_fmod) || defined(__CRT_HAVE___fmod) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(fmodl)
#endif /* __CRT_HAVE_fmodl || __CRT_HAVE___fmodl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_fmod || __CRT_HAVE___fmod || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#ifdef __USE_ISOC99
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(copysign)
#if defined(__CRT_HAVE_nan) || defined(__CRT_HAVE___nan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(nan)
#endif /* __CRT_HAVE_nan || __CRT_HAVE___nan || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
__NAMESPACE_STD_USING(copysignf)
#if defined(__CRT_HAVE_nanf) || defined(__CRT_HAVE___nanf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_nan) || defined(__CRT_HAVE___nan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(nanf)
#endif /* __CRT_HAVE_nanf || __CRT_HAVE___nanf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_nan || __CRT_HAVE___nan || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(copysignl)
#if defined(__CRT_HAVE_nanl) || defined(__CRT_HAVE___nanl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_nan) || defined(__CRT_HAVE___nan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(nanl)
#endif /* __CRT_HAVE_nanl || __CRT_HAVE___nanl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_nan || __CRT_HAVE___nan || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */

/* Error and gamma functions. */
#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_erf) || defined(__CRT_HAVE___erf)
__NAMESPACE_STD_USING(erf)
#endif /* __CRT_HAVE_erf || __CRT_HAVE___erf */
#if defined(__CRT_HAVE_erfc) || defined(__CRT_HAVE___erfc)
__NAMESPACE_STD_USING(erfc)
#endif /* __CRT_HAVE_erfc || __CRT_HAVE___erfc */
#if defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE_gamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma)
__NAMESPACE_STD_USING(lgamma)
#endif /* __CRT_HAVE_lgamma || __CRT_HAVE_gamma || __CRT_HAVE___lgamma || __CRT_HAVE___gamma */
#if defined(__CRT_HAVE_erff) || defined(__CRT_HAVE___erff) || defined(__CRT_HAVE_erf) || defined(__CRT_HAVE___erf)
__NAMESPACE_STD_USING(erff)
#endif /* __CRT_HAVE_erff || __CRT_HAVE___erff || __CRT_HAVE_erf || __CRT_HAVE___erf */
#if defined(__CRT_HAVE_erfcf) || defined(__CRT_HAVE___erfcf) || defined(__CRT_HAVE_erfc) || defined(__CRT_HAVE___erfc)
__NAMESPACE_STD_USING(erfcf)
#endif /* __CRT_HAVE_erfcf || __CRT_HAVE___erfcf || __CRT_HAVE_erfc || __CRT_HAVE___erfc */
#if defined(__CRT_HAVE_lgammaf) || defined(__CRT_HAVE_gammaf) || defined(__CRT_HAVE___lgammaf) || defined(__CRT_HAVE___gammaf) || defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE_gamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma)
__NAMESPACE_STD_USING(lgammaf)
#endif /* __CRT_HAVE_lgammaf || __CRT_HAVE_gammaf || __CRT_HAVE___lgammaf || __CRT_HAVE___gammaf || __CRT_HAVE_lgamma || __CRT_HAVE_gamma || __CRT_HAVE___lgamma || __CRT_HAVE___gamma */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_erfl) || defined(__CRT_HAVE___erfl) || defined(__CRT_HAVE_erf) || defined(__CRT_HAVE___erf)
__NAMESPACE_STD_USING(erfl)
#endif /* __CRT_HAVE_erfl || __CRT_HAVE___erfl || __CRT_HAVE_erf || __CRT_HAVE___erf */
#if defined(__CRT_HAVE_erfcl) || defined(__CRT_HAVE___erfcl) || defined(__CRT_HAVE_erfc) || defined(__CRT_HAVE___erfc)
__NAMESPACE_STD_USING(erfcl)
#endif /* __CRT_HAVE_erfcl || __CRT_HAVE___erfcl || __CRT_HAVE_erfc || __CRT_HAVE___erfc */
#if defined(__CRT_HAVE_lgammal) || defined(__CRT_HAVE_gammal) || defined(__CRT_HAVE___lgammal) || defined(__CRT_HAVE___gammal) || defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE_gamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma)
__NAMESPACE_STD_USING(lgammal)
#endif /* __CRT_HAVE_lgammal || __CRT_HAVE_gammal || __CRT_HAVE___lgammal || __CRT_HAVE___gammal || __CRT_HAVE_lgamma || __CRT_HAVE_gamma || __CRT_HAVE___lgamma || __CRT_HAVE___gamma */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN || __USE_ISOC99 */
#ifdef __USE_ISOC99
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_tgamma) || defined(__CRT_HAVE___tgamma)
__NAMESPACE_STD_USING(tgamma)
#endif /* __CRT_HAVE_tgamma || __CRT_HAVE___tgamma */
#if defined(__CRT_HAVE_tgammaf) || defined(__CRT_HAVE___tgammaf) || defined(__CRT_HAVE_tgamma) || defined(__CRT_HAVE___tgamma)
__NAMESPACE_STD_USING(tgammaf)
#endif /* __CRT_HAVE_tgammaf || __CRT_HAVE___tgammaf || __CRT_HAVE_tgamma || __CRT_HAVE___tgamma */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_tgammal) || defined(__CRT_HAVE___tgammal) || defined(__CRT_HAVE_tgamma) || defined(__CRT_HAVE___tgamma)
__NAMESPACE_STD_USING(tgammal)
#endif /* __CRT_HAVE_tgammal || __CRT_HAVE___tgammal || __CRT_HAVE_tgamma || __CRT_HAVE___tgamma */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_rint) || defined(__CRT_HAVE_nearbyint) || defined(__CRT_HAVE___rint) || defined(__CRT_HAVE___nearbyint) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(rint)
#endif /* __CRT_HAVE_rint || __CRT_HAVE_nearbyint || __CRT_HAVE___rint || __CRT_HAVE___nearbyint || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE___nexttoward) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(nextafter)
#endif /* __CRT_HAVE_nextafter || __CRT_HAVE_nexttoward || __CRT_HAVE___nextafter || __CRT_HAVE__nextafter || __CRT_HAVE___nexttoward || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE___drem) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(remainder)
#endif /* __CRT_HAVE_remainder || __CRT_HAVE_drem || __CRT_HAVE___remainder || __CRT_HAVE___drem || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_ilogb) || defined(__CRT_HAVE___ilogb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(ilogb)
#endif /* __CRT_HAVE_ilogb || __CRT_HAVE___ilogb || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_rintf) || defined(__CRT_HAVE_nearbyintf) || defined(__CRT_HAVE___rintf) || defined(__CRT_HAVE___nearbyintf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE_nearbyint) || defined(__CRT_HAVE___rint) || defined(__CRT_HAVE___nearbyint) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(rintf)
#endif /* __CRT_HAVE_rintf || __CRT_HAVE_nearbyintf || __CRT_HAVE___rintf || __CRT_HAVE___nearbyintf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_rint || __CRT_HAVE_nearbyint || __CRT_HAVE___rint || __CRT_HAVE___nearbyint || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_nextafterf) || defined(__CRT_HAVE_nexttowardf) || defined(__CRT_HAVE___nextafterf) || defined(__CRT_HAVE___nexttowardf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE___nexttoward) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(nextafterf)
#endif /* __CRT_HAVE_nextafterf || __CRT_HAVE_nexttowardf || __CRT_HAVE___nextafterf || __CRT_HAVE___nexttowardf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_nextafter || __CRT_HAVE_nexttoward || __CRT_HAVE___nextafter || __CRT_HAVE__nextafter || __CRT_HAVE___nexttoward || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_remainderf) || defined(__CRT_HAVE_dremf) || defined(__CRT_HAVE___remainderf) || defined(__CRT_HAVE___dremf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE___drem) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(remainderf)
#endif /* __CRT_HAVE_remainderf || __CRT_HAVE_dremf || __CRT_HAVE___remainderf || __CRT_HAVE___dremf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_remainder || __CRT_HAVE_drem || __CRT_HAVE___remainder || __CRT_HAVE___drem || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_ilogbf) || defined(__CRT_HAVE___ilogbf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_ilogb) || defined(__CRT_HAVE___ilogb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(ilogbf)
#endif /* __CRT_HAVE_ilogbf || __CRT_HAVE___ilogbf || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __CRT_HAVE_ilogb || __CRT_HAVE___ilogb || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_rintl) || defined(__CRT_HAVE_nearbyintl) || defined(__CRT_HAVE___rintl) || defined(__CRT_HAVE___nearbyintl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE_nearbyint) || defined(__CRT_HAVE___rint) || defined(__CRT_HAVE___nearbyint) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(rintl)
#endif /* __CRT_HAVE_rintl || __CRT_HAVE_nearbyintl || __CRT_HAVE___rintl || __CRT_HAVE___nearbyintl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_rint || __CRT_HAVE_nearbyint || __CRT_HAVE___rint || __CRT_HAVE___nearbyint || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_nextafterl) || defined(__CRT_HAVE_nexttowardl) || defined(__CRT_HAVE___nextafterl) || defined(__CRT_HAVE___nexttowardl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE___nexttoward) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(nextafterl)
#endif /* __CRT_HAVE_nextafterl || __CRT_HAVE_nexttowardl || __CRT_HAVE___nextafterl || __CRT_HAVE___nexttowardl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_nextafter || __CRT_HAVE_nexttoward || __CRT_HAVE___nextafter || __CRT_HAVE__nextafter || __CRT_HAVE___nexttoward || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_remainderl) || defined(__CRT_HAVE_dreml) || defined(__CRT_HAVE___remainderl) || defined(__CRT_HAVE___dreml) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE___drem) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(remainderl)
#endif /* __CRT_HAVE_remainderl || __CRT_HAVE_dreml || __CRT_HAVE___remainderl || __CRT_HAVE___dreml || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_remainder || __CRT_HAVE_drem || __CRT_HAVE___remainder || __CRT_HAVE___drem || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_ilogbl) || defined(__CRT_HAVE___ilogbl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_ilogb) || defined(__CRT_HAVE___ilogb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(ilogbl)
#endif /* __CRT_HAVE_ilogbl || __CRT_HAVE___ilogbl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_ilogb || __CRT_HAVE___ilogb || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

#ifdef __USE_ISOC99
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_nextafterl) || defined(__CRT_HAVE_nexttowardl) || defined(__CRT_HAVE___nextafterl) || defined(__CRT_HAVE___nexttowardl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE___nexttoward) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(nexttoward)
#endif /* __CRT_HAVE_nextafterl || __CRT_HAVE_nexttowardl || __CRT_HAVE___nextafterl || __CRT_HAVE___nexttowardl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_nextafter || __CRT_HAVE_nexttoward || __CRT_HAVE___nextafter || __CRT_HAVE__nextafter || __CRT_HAVE___nexttoward || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_scalbn) || defined(__CRT_HAVE___scalbn) || (defined(__CRT_HAVE_scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(scalbn)
#endif /* __CRT_HAVE_scalbn || __CRT_HAVE___scalbn || (__CRT_HAVE_scalbln && __SIZEOF_INT__ == __SIZEOF_LONG__) || (__CRT_HAVE___scalbln && __SIZEOF_INT__ == __SIZEOF_LONG__) || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_scalbln) || defined(__CRT_HAVE___scalbln) || (defined(__CRT_HAVE_scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(scalbln)
#endif /* __CRT_HAVE_scalbln || __CRT_HAVE___scalbln || (__CRT_HAVE_scalbn && __SIZEOF_INT__ == __SIZEOF_LONG__) || (__CRT_HAVE___scalbn && __SIZEOF_INT__ == __SIZEOF_LONG__) || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_nearbyint) || defined(__CRT_HAVE___nearbyint) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE___rint) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(nearbyint)
#endif /* __CRT_HAVE_nearbyint || __CRT_HAVE___nearbyint || __CRT_HAVE_rint || __CRT_HAVE___rint || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
__NAMESPACE_STD_USING(round)
__NAMESPACE_STD_USING(trunc)
#if defined(__CRT_HAVE_remquo) || defined(__CRT_HAVE___remquo)
__NAMESPACE_STD_USING(remquo)
#endif /* __CRT_HAVE_remquo || __CRT_HAVE___remquo */
__NAMESPACE_STD_USING(lrint)
__NAMESPACE_STD_USING(lround)
__NAMESPACE_STD_USING(fdim)
__NAMESPACE_STD_USING(fmax)
__NAMESPACE_STD_USING(fmin)
__NAMESPACE_STD_USING(fma)
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGLONG
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(llrint)
__NAMESPACE_STD_USING(llround)
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGLONG */
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_nexttowardf) || defined(__CRT_HAVE___nexttowardf) || ((defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)) && defined(__IEEE854_LONG_DOUBLE_TYPE__)) || defined(__CRT_HAVE_nextafterl) || defined(__CRT_HAVE_nexttowardl) || defined(__CRT_HAVE___nextafterl) || defined(__CRT_HAVE___nexttowardl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE___nexttoward) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(nexttowardf)
#endif /* __CRT_HAVE_nexttowardf || __CRT_HAVE___nexttowardf || ((__IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE754_DOUBLE_TYPE_IS_FLOAT__) && __IEEE854_LONG_DOUBLE_TYPE__) || __CRT_HAVE_nextafterl || __CRT_HAVE_nexttowardl || __CRT_HAVE___nextafterl || __CRT_HAVE___nexttowardl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_nextafter || __CRT_HAVE_nexttoward || __CRT_HAVE___nextafter || __CRT_HAVE__nextafter || __CRT_HAVE___nexttoward || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_scalbnf) || defined(__CRT_HAVE___scalbnf) || (defined(__CRT_HAVE_scalblnf) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalblnf) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_scalbn) || defined(__CRT_HAVE___scalbn) || (defined(__CRT_HAVE_scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(scalbnf)
#endif /* __CRT_HAVE_scalbnf || __CRT_HAVE___scalbnf || (__CRT_HAVE_scalblnf && __SIZEOF_INT__ == __SIZEOF_LONG__) || (__CRT_HAVE___scalblnf && __SIZEOF_INT__ == __SIZEOF_LONG__) || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_scalbn || __CRT_HAVE___scalbn || (__CRT_HAVE_scalbln && __SIZEOF_INT__ == __SIZEOF_LONG__) || (__CRT_HAVE___scalbln && __SIZEOF_INT__ == __SIZEOF_LONG__) || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_scalblnf) || defined(__CRT_HAVE___scalblnf) || (defined(__CRT_HAVE_scalbnf) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbnf) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_scalbln) || defined(__CRT_HAVE___scalbln) || (defined(__CRT_HAVE_scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(scalblnf)
#endif /* __CRT_HAVE_scalblnf || __CRT_HAVE___scalblnf || (__CRT_HAVE_scalbnf && __SIZEOF_INT__ == __SIZEOF_LONG__) || (__CRT_HAVE___scalbnf && __SIZEOF_INT__ == __SIZEOF_LONG__) || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ || __CRT_HAVE_scalbln || __CRT_HAVE___scalbln || (__CRT_HAVE_scalbn && __SIZEOF_INT__ == __SIZEOF_LONG__) || (__CRT_HAVE___scalbn && __SIZEOF_INT__ == __SIZEOF_LONG__) || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_nearbyintf) || defined(__CRT_HAVE___nearbyintf) || defined(__CRT_HAVE_rintf) || defined(__CRT_HAVE___rintf) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)
__NAMESPACE_STD_USING(nearbyintf)
#endif /* __CRT_HAVE_nearbyintf || __CRT_HAVE___nearbyintf || __CRT_HAVE_rintf || __CRT_HAVE___rintf || __IEEE754_FLOAT_TYPE_IS_FLOAT__ || __IEEE754_DOUBLE_TYPE_IS_FLOAT__ || __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__ */
__NAMESPACE_STD_USING(roundf)
__NAMESPACE_STD_USING(truncf)
#if defined(__CRT_HAVE_remquof) || defined(__CRT_HAVE___remquof) || defined(__CRT_HAVE_remquo) || defined(__CRT_HAVE___remquo)
__NAMESPACE_STD_USING(remquof)
#endif /* __CRT_HAVE_remquof || __CRT_HAVE___remquof || __CRT_HAVE_remquo || __CRT_HAVE___remquo */
__NAMESPACE_STD_USING(lrintf)
__NAMESPACE_STD_USING(lroundf)
__NAMESPACE_STD_USING(fdimf)
__NAMESPACE_STD_USING(fmaxf)
__NAMESPACE_STD_USING(fminf)
__NAMESPACE_STD_USING(fmaf)
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGLONG
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(llrintf)
__NAMESPACE_STD_USING(llroundf)
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGLONG */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_nextafterl) || defined(__CRT_HAVE_nexttowardl) || defined(__CRT_HAVE___nextafterl) || defined(__CRT_HAVE___nexttowardl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE___nexttoward) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(nexttowardl)
#endif /* __CRT_HAVE_nextafterl || __CRT_HAVE_nexttowardl || __CRT_HAVE___nextafterl || __CRT_HAVE___nexttowardl || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_nextafter || __CRT_HAVE_nexttoward || __CRT_HAVE___nextafter || __CRT_HAVE__nextafter || __CRT_HAVE___nexttoward || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_scalbnl) || defined(__CRT_HAVE___scalbnl) || (defined(__CRT_HAVE_scalblnl) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalblnl) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_scalbn) || defined(__CRT_HAVE___scalbn) || (defined(__CRT_HAVE_scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(scalbnl)
#endif /* __CRT_HAVE_scalbnl || __CRT_HAVE___scalbnl || (__CRT_HAVE_scalblnl && __SIZEOF_INT__ == __SIZEOF_LONG__) || (__CRT_HAVE___scalblnl && __SIZEOF_INT__ == __SIZEOF_LONG__) || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_scalbn || __CRT_HAVE___scalbn || (__CRT_HAVE_scalbln && __SIZEOF_INT__ == __SIZEOF_LONG__) || (__CRT_HAVE___scalbln && __SIZEOF_INT__ == __SIZEOF_LONG__) || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_scalblnl) || defined(__CRT_HAVE___scalblnl) || (defined(__CRT_HAVE_scalbnl) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbnl) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_scalbln) || defined(__CRT_HAVE___scalbln) || (defined(__CRT_HAVE_scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
__NAMESPACE_STD_USING(scalblnl)
#endif /* __CRT_HAVE_scalblnl || __CRT_HAVE___scalblnl || (__CRT_HAVE_scalbnl && __SIZEOF_INT__ == __SIZEOF_LONG__) || (__CRT_HAVE___scalbnl && __SIZEOF_INT__ == __SIZEOF_LONG__) || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __CRT_HAVE_scalbln || __CRT_HAVE___scalbln || (__CRT_HAVE_scalbn && __SIZEOF_INT__ == __SIZEOF_LONG__) || (__CRT_HAVE___scalbn && __SIZEOF_INT__ == __SIZEOF_LONG__) || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */
#if defined(__CRT_HAVE_nearbyintl) || defined(__CRT_HAVE___nearbyintl) || defined(__CRT_HAVE_rintl) || defined(__CRT_HAVE___rintl) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)
__NAMESPACE_STD_USING(nearbyintl)
#endif /* __CRT_HAVE_nearbyintl || __CRT_HAVE___nearbyintl || __CRT_HAVE_rintl || __CRT_HAVE___rintl || __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__ */
__NAMESPACE_STD_USING(roundl)
__NAMESPACE_STD_USING(truncl)
#if defined(__CRT_HAVE_remquol) || defined(__CRT_HAVE___remquol) || defined(__CRT_HAVE_remquo) || defined(__CRT_HAVE___remquo)
__NAMESPACE_STD_USING(remquol)
#endif /* __CRT_HAVE_remquol || __CRT_HAVE___remquol || __CRT_HAVE_remquo || __CRT_HAVE___remquo */
__NAMESPACE_STD_USING(lrintl)
__NAMESPACE_STD_USING(lroundl)
__NAMESPACE_STD_USING(fdiml)
__NAMESPACE_STD_USING(fmaxl)
__NAMESPACE_STD_USING(fminl)
__NAMESPACE_STD_USING(fmal)
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGLONG
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(llrintl)
__NAMESPACE_STD_USING(llroundl)
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGLONG */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */

#ifdef __USE_GNU
#if __has_builtin(__builtin_sincos) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sincos)
/* Cosine and sine of `x' */
__CEIDECLARE(__DECL_SIMD_sincos __ATTR_NONNULL((2, 3)),void,__NOTHROW,sincos,(double __x, double *__psinx, double *__pcosx),{ __builtin_sincos(__x, __psinx, __pcosx); })
#elif defined(__CRT_HAVE_sincos)
/* Cosine and sine of `x' */
__CDECLARE_VOID(__DECL_SIMD_sincos __ATTR_NONNULL((2, 3)),__NOTHROW,sincos,(double __x, double *__psinx, double *__pcosx),(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE___sincos)
/* Cosine and sine of `x' */
__CREDIRECT_VOID(__DECL_SIMD_sincos __ATTR_NONNULL((2, 3)),__NOTHROW,sincos,(double __x, double *__psinx, double *__pcosx),__sincos,(__x,__psinx,__pcosx))
#endif /* ... */
#if __has_builtin(__builtin_exp10) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp10)
/* A function missing in all standards: compute exponent to base ten */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,exp10,(double __x),{ return __builtin_exp10(__x); })
#elif defined(__CRT_HAVE_exp10)
/* A function missing in all standards: compute exponent to base ten */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,exp10,(double __x),(__x))
#elif defined(__CRT_HAVE___exp10)
/* A function missing in all standards: compute exponent to base ten */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,exp10,(double __x),__exp10,(__x))
#endif /* ... */
#if __has_builtin(__builtin_pow10) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_pow10)
/* Another name occasionally used */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,pow10,(double __x),{ return __builtin_pow10(__x); })
#elif defined(__CRT_HAVE_pow10)
/* Another name occasionally used */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,pow10,(double __x),(__x))
#elif defined(__CRT_HAVE___pow10)
/* Another name occasionally used */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,pow10,(double __x),__pow10,(__x))
#elif defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/pow10.h>
/* Another name occasionally used */
__NAMESPACE_LOCAL_USING_OR_IMPL(pow10, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL pow10)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pow10))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_sincosf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sincosf)
/* Cosine and sine of `x' */
__CEIDECLARE(__DECL_SIMD_sincosf __ATTR_NONNULL((2, 3)),void,__NOTHROW,sincosf,(float __x, float *__psinx, float *__pcosx),{ __builtin_sincosf(__x, __psinx, __pcosx); })
#elif defined(__CRT_HAVE_sincosf)
/* Cosine and sine of `x' */
__CDECLARE_VOID(__DECL_SIMD_sincosf __ATTR_NONNULL((2, 3)),__NOTHROW,sincosf,(float __x, float *__psinx, float *__pcosx),(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE___sincosf)
/* Cosine and sine of `x' */
__CREDIRECT_VOID(__DECL_SIMD_sincosf __ATTR_NONNULL((2, 3)),__NOTHROW,sincosf,(float __x, float *__psinx, float *__pcosx),__sincosf,(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE_sincos) || defined(__CRT_HAVE___sincos)
#include <libc/local/math/sincosf.h>
/* Cosine and sine of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(sincosf, __FORCELOCAL __ATTR_ARTIFICIAL __DECL_SIMD_sincosf __ATTR_NONNULL((2, 3)) void __NOTHROW(__LIBCCALL sincosf)(float __x, float *__psinx, float *__pcosx) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sincosf))(__x, __psinx, __pcosx); })
#endif /* ... */
#if __has_builtin(__builtin_exp10f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp10f)
/* A function missing in all standards: compute exponent to base ten */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,exp10f,(float __x),{ return __builtin_exp10f(__x); })
#elif defined(__CRT_HAVE_exp10f)
/* A function missing in all standards: compute exponent to base ten */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,exp10f,(float __x),(__x))
#elif defined(__CRT_HAVE___exp10f)
/* A function missing in all standards: compute exponent to base ten */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,exp10f,(float __x),__exp10f,(__x))
#elif defined(__CRT_HAVE_exp10) || defined(__CRT_HAVE___exp10)
#include <libc/local/math/exp10f.h>
/* A function missing in all standards: compute exponent to base ten */
__NAMESPACE_LOCAL_USING_OR_IMPL(exp10f, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL exp10f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(exp10f))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_pow10f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_pow10f)
/* Another name occasionally used */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,pow10f,(float __x),{ return __builtin_pow10f(__x); })
#elif defined(__CRT_HAVE_pow10f)
/* Another name occasionally used */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,pow10f,(float __x),(__x))
#elif defined(__CRT_HAVE___pow10f)
/* Another name occasionally used */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,pow10f,(float __x),__pow10f,(__x))
#elif defined(__CRT_HAVE_powf) || defined(__CRT_HAVE___powf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_pow10) || defined(__CRT_HAVE___pow10) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/pow10f.h>
/* Another name occasionally used */
__NAMESPACE_LOCAL_USING_OR_IMPL(pow10f, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL pow10f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pow10f))(__x); })
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_sincosl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sincosl)
/* Cosine and sine of `x' */
__CEIDECLARE(__DECL_SIMD_sincosl __ATTR_NONNULL((2, 3)),void,__NOTHROW,sincosl,(__LONGDOUBLE __x, __LONGDOUBLE *__psinx, __LONGDOUBLE *__pcosx),{ __builtin_sincosl(__x, __psinx, __pcosx); })
#elif defined(__CRT_HAVE_sincosl)
/* Cosine and sine of `x' */
__CDECLARE_VOID(__DECL_SIMD_sincosl __ATTR_NONNULL((2, 3)),__NOTHROW,sincosl,(__LONGDOUBLE __x, __LONGDOUBLE *__psinx, __LONGDOUBLE *__pcosx),(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE___sincosl)
/* Cosine and sine of `x' */
__CREDIRECT_VOID(__DECL_SIMD_sincosl __ATTR_NONNULL((2, 3)),__NOTHROW,sincosl,(__LONGDOUBLE __x, __LONGDOUBLE *__psinx, __LONGDOUBLE *__pcosx),__sincosl,(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE___sincos) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Cosine and sine of `x' */
__CREDIRECT_VOID(__DECL_SIMD_sincosl __ATTR_NONNULL((2, 3)),__NOTHROW,sincosl,(__LONGDOUBLE __x, __LONGDOUBLE *__psinx, __LONGDOUBLE *__pcosx),__sincos,(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE_sincos) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Cosine and sine of `x' */
__CREDIRECT_VOID(__DECL_SIMD_sincosl __ATTR_NONNULL((2, 3)),__NOTHROW,sincosl,(__LONGDOUBLE __x, __LONGDOUBLE *__psinx, __LONGDOUBLE *__pcosx),sincos,(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE_sincos) || defined(__CRT_HAVE___sincos)
#include <libc/local/math/sincosl.h>
/* Cosine and sine of `x' */
__NAMESPACE_LOCAL_USING_OR_IMPL(sincosl, __FORCELOCAL __ATTR_ARTIFICIAL __DECL_SIMD_sincosl __ATTR_NONNULL((2, 3)) void __NOTHROW(__LIBCCALL sincosl)(__LONGDOUBLE __x, __LONGDOUBLE *__psinx, __LONGDOUBLE *__pcosx) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sincosl))(__x, __psinx, __pcosx); })
#endif /* ... */
#if __has_builtin(__builtin_exp10l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp10l)
/* A function missing in all standards: compute exponent to base ten */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp10l,(__LONGDOUBLE __x),{ return __builtin_exp10l(__x); })
#elif defined(__CRT_HAVE_exp10l)
/* A function missing in all standards: compute exponent to base ten */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp10l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___exp10l)
/* A function missing in all standards: compute exponent to base ten */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,exp10l,(__LONGDOUBLE __x),__exp10l,(__x))
#elif defined(__CRT_HAVE_exp10) || defined(__CRT_HAVE___exp10)
#include <libc/local/math/exp10l.h>
/* A function missing in all standards: compute exponent to base ten */
__NAMESPACE_LOCAL_USING_OR_IMPL(exp10l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL exp10l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(exp10l))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_pow10l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_pow10l)
/* Another name occasionally used */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,pow10l,(__LONGDOUBLE __x),{ return __builtin_pow10l(__x); })
#elif defined(__CRT_HAVE_pow10l)
/* Another name occasionally used */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,pow10l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___pow10l)
/* Another name occasionally used */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,pow10l,(__LONGDOUBLE __x),__pow10l,(__x))
#elif defined(__CRT_HAVE_powl) || defined(__CRT_HAVE___powl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_pow10) || defined(__CRT_HAVE___pow10) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/pow10l.h>
/* Another name occasionally used */
__NAMESPACE_LOCAL_USING_OR_IMPL(pow10l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL pow10l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pow10l))(__x); })
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_GNU */

#ifdef __USE_MISC
#if !defined(__cplusplus) || !defined(__CORRECT_ISO_CPP11_MATH_H_PROTO_FP) /* isinf conflicts with C++11. */
#if __has_builtin(__builtin_isinf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinf)
/* Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isinf,(double __x),{ return __builtin_isinf(__x); })
#elif defined(__CRT_HAVE_isinf)
/* Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isinf,(double __x),(__x))
#elif defined(__CRT_HAVE___isinf)
/* Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isinf,(double __x),__isinf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL)
#include <libc/local/math/isinf.h>
/* Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__NAMESPACE_LOCAL_USING_OR_IMPL(isinf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isinf)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isinf))(__x); })
#endif /* ... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP11_MATH_H_PROTO_FP */
#if __has_builtin(__builtin_isinff) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinff)
/* Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isinff,(float __x),{ return __builtin_isinff(__x); })
#elif defined(__CRT_HAVE_isinff)
/* Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isinff,(float __x),(__x))
#elif defined(__CRT_HAVE___isinff)
/* Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isinff,(float __x),__isinff,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__INFINITYF) || defined(__HUGE_VALF) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL)
#include <libc/local/math/isinff.h>
/* Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__NAMESPACE_LOCAL_USING_OR_IMPL(isinff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isinff)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isinff))(__x); })
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_isinfl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinfl)
/* Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isinfl,(__LONGDOUBLE __x),{ return __builtin_isinfl(__x); })
#elif defined(__CRT_HAVE_isinfl)
/* Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isinfl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___isinfl)
/* Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isinfl,(__LONGDOUBLE __x),__isinfl,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__INFINITYL) || defined(__HUGE_VALL) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL)
#include <libc/local/math/isinfl.h>
/* Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__NAMESPACE_LOCAL_USING_OR_IMPL(isinfl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isinfl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isinfl))(__x); })
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#if __has_builtin(__builtin_finite) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_finite)
/* Return nonzero if `value' is finite and not NaN */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,finite,(double __x),{ return __builtin_finite(__x); })
#elif defined(__CRT_HAVE_finite)
/* Return nonzero if `value' is finite and not NaN */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,finite,(double __x),(__x))
#elif defined(__CRT_HAVE___finite)
/* Return nonzero if `value' is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,finite,(double __x),__finite,(__x))
#elif defined(__CRT_HAVE__finite)
/* Return nonzero if `value' is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,finite,(double __x),_finite,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || ((defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__INFINITY) || defined(__HUGE_VAL)) && (defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan)))
#include <libc/local/math/finite.h>
/* Return nonzero if `value' is finite and not NaN */
__NAMESPACE_LOCAL_USING_OR_IMPL(finite, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL finite)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(finite))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_remainder) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainder)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,drem,(double __x, double __p),remainder,{ return __builtin_remainder(__x, __p); })
#elif __has_builtin(__builtin_drem) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_drem)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,drem,(double __x, double __p),{ return __builtin_drem(__x, __p); })
#elif defined(__CRT_HAVE_remainder)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,drem,(double __x, double __p),remainder,(__x,__p))
#elif defined(__CRT_HAVE_drem)
/* Return the remainder of integer division `x / p' with infinite precision */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,drem,(double __x, double __p),(__x,__p))
#elif defined(__CRT_HAVE___remainder)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,drem,(double __x, double __p),__remainder,(__x,__p))
#elif defined(__CRT_HAVE___drem)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,drem,(double __x, double __p),__drem,(__x,__p))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/remainder.h>
/* Return the remainder of integer division `x / p' with infinite precision */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL drem)(double __x, double __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainder))(__x, __p); }
#endif /* ... */
#if __has_builtin(__builtin_significand) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_significand)
/* Return the fractional part of `x' after dividing out `ilogb(x)' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,significand,(double __x),{ return __builtin_significand(__x); })
#elif defined(__CRT_HAVE_significand)
/* Return the fractional part of `x' after dividing out `ilogb(x)' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,significand,(double __x),(__x))
#elif defined(__CRT_HAVE___significand)
/* Return the fractional part of `x' after dividing out `ilogb(x)' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,significand,(double __x),__significand,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/significand.h>
/* Return the fractional part of `x' after dividing out `ilogb(x)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(significand, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL significand)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(significand))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_finitef) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_finitef)
/* Return nonzero if `value' is finite and not NaN */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,finitef,(float __x),{ return __builtin_finitef(__x); })
#elif defined(__CRT_HAVE_finitef)
/* Return nonzero if `value' is finite and not NaN */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,finitef,(float __x),(__x))
#elif defined(__CRT_HAVE___finitef)
/* Return nonzero if `value' is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,finitef,(float __x),__finitef,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || ((defined(__CRT_HAVE_isinff) || defined(__CRT_HAVE___isinff) || defined(__INFINITYF) || defined(__HUGE_VALF) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__INFINITY) || defined(__HUGE_VAL)) && (defined(__CRT_HAVE_isnanf) || defined(__CRT_HAVE___isnanf) || defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan))) || defined(__CRT_HAVE_finite) || defined(__CRT_HAVE___finite) || defined(__CRT_HAVE__finite) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || ((defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__INFINITY) || defined(__HUGE_VAL)) && (defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan)))
#include <libc/local/math/finitef.h>
/* Return nonzero if `value' is finite and not NaN */
__NAMESPACE_LOCAL_USING_OR_IMPL(finitef, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL finitef)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(finitef))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_remainderf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainderf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,dremf,(float __x, float __p),remainderf,{ return __builtin_remainderf(__x, __p); })
#elif __has_builtin(__builtin_dremf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_dremf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,dremf,(float __x, float __p),{ return __builtin_dremf(__x, __p); })
#elif defined(__CRT_HAVE_remainderf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,dremf,(float __x, float __p),remainderf,(__x,__p))
#elif defined(__CRT_HAVE_dremf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,dremf,(float __x, float __p),(__x,__p))
#elif defined(__CRT_HAVE___remainderf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,dremf,(float __x, float __p),__remainderf,(__x,__p))
#elif defined(__CRT_HAVE___dremf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,dremf,(float __x, float __p),__dremf,(__x,__p))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE___drem) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/remainderf.h>
/* Return the remainder of integer division `x / p' with infinite precision */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL dremf)(float __x, float __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainderf))(__x, __p); }
#endif /* ... */
#if __has_builtin(__builtin_significandf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_significandf)
/* Return the fractional part of `x' after dividing out `ilogb(x)' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,significandf,(float __x),{ return __builtin_significandf(__x); })
#elif defined(__CRT_HAVE_significandf)
/* Return the fractional part of `x' after dividing out `ilogb(x)' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,significandf,(float __x),(__x))
#elif defined(__CRT_HAVE___significandf)
/* Return the fractional part of `x' after dividing out `ilogb(x)' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,significandf,(float __x),__significandf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_significand) || defined(__CRT_HAVE___significand) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/significandf.h>
/* Return the fractional part of `x' after dividing out `ilogb(x)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(significandf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL significandf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(significandf))(__x); })
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_finitel) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_finitel)
/* Return nonzero if `value' is finite and not NaN */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,finitel,(__LONGDOUBLE __x),{ return __builtin_finitel(__x); })
#elif defined(__CRT_HAVE_finitel)
/* Return nonzero if `value' is finite and not NaN */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,finitel,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___finitel)
/* Return nonzero if `value' is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,finitel,(__LONGDOUBLE __x),__finitel,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || ((defined(__CRT_HAVE_isinfl) || defined(__CRT_HAVE___isinfl) || defined(__INFINITYL) || defined(__HUGE_VALL) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__INFINITY) || defined(__HUGE_VAL)) && (defined(__CRT_HAVE_isnanl) || defined(__CRT_HAVE___isnanl) || defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan))) || defined(__CRT_HAVE_finite) || defined(__CRT_HAVE___finite) || defined(__CRT_HAVE__finite) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || ((defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__INFINITY) || defined(__HUGE_VAL)) && (defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan)))
#include <libc/local/math/finitel.h>
/* Return nonzero if `value' is finite and not NaN */
__NAMESPACE_LOCAL_USING_OR_IMPL(finitel, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL finitel)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(finitel))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_remainderl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainderl)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,dreml,(__LONGDOUBLE __x, __LONGDOUBLE __p),remainderl,{ return __builtin_remainderl(__x, __p); })
#elif __has_builtin(__builtin_dreml) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_dreml)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,dreml,(__LONGDOUBLE __x, __LONGDOUBLE __p),{ return __builtin_dreml(__x, __p); })
#elif defined(__CRT_HAVE_remainderl)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,dreml,(__LONGDOUBLE __x, __LONGDOUBLE __p),remainderl,(__x,__p))
#elif defined(__CRT_HAVE_dreml)
/* Return the remainder of integer division `x / p' with infinite precision */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,dreml,(__LONGDOUBLE __x, __LONGDOUBLE __p),(__x,__p))
#elif defined(__CRT_HAVE___remainderl)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,dreml,(__LONGDOUBLE __x, __LONGDOUBLE __p),__remainderl,(__x,__p))
#elif defined(__CRT_HAVE___dreml)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,dreml,(__LONGDOUBLE __x, __LONGDOUBLE __p),__dreml,(__x,__p))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE___drem) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/remainderl.h>
/* Return the remainder of integer division `x / p' with infinite precision */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL dreml)(__LONGDOUBLE __x, __LONGDOUBLE __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainderl))(__x, __p); }
#endif /* ... */
#if __has_builtin(__builtin_significandl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_significandl)
/* Return the fractional part of `x' after dividing out `ilogb(x)' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,significandl,(__LONGDOUBLE __x),{ return __builtin_significandl(__x); })
#elif defined(__CRT_HAVE_significandl)
/* Return the fractional part of `x' after dividing out `ilogb(x)' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,significandl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___significandl)
/* Return the fractional part of `x' after dividing out `ilogb(x)' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,significandl,(__LONGDOUBLE __x),__significandl,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_significand) || defined(__CRT_HAVE___significand) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/significandl.h>
/* Return the fractional part of `x' after dividing out `ilogb(x)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(significandl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL significandl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(significandl))(__x); })
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_MISC */

#if defined(__USE_MISC) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
#if !defined(__cplusplus) || !defined(__CORRECT_ISO_CPP11_MATH_H_PROTO_FP) /* isnan conflicts with C++11. */
#if __has_builtin(__builtin_isnan) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isnan)
/* Return nonzero if `value' is not a number */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isnan,(double __x),{ return __builtin_isnan(__x); })
#elif defined(__CRT_HAVE_isnan)
/* Return nonzero if `value' is not a number */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isnan,(double __x),(__x))
#elif defined(__CRT_HAVE__isnan)
/* Return nonzero if `value' is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isnan,(double __x),_isnan,(__x))
#elif defined(__CRT_HAVE___isnan)
/* Return nonzero if `value' is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isnan,(double __x),__isnan,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/isnan.h>
/* Return nonzero if `value' is not a number */
__NAMESPACE_LOCAL_USING_OR_IMPL(isnan, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isnan)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isnan))(__x); })
#endif /* ... */
#endif /* !cplusplus || !__CORRECT_ISO_CPP11_MATH_H_PROTO_FP */
#if __has_builtin(__builtin_isnanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isnanf)
/* Return nonzero if `value' is not a number */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isnanf,(float __x),{ return __builtin_isnanf(__x); })
#elif defined(__CRT_HAVE_isnanf)
/* Return nonzero if `value' is not a number */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isnanf,(float __x),(__x))
#elif defined(__CRT_HAVE___isnanf)
/* Return nonzero if `value' is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isnanf,(float __x),__isnanf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/isnanf.h>
/* Return nonzero if `value' is not a number */
__NAMESPACE_LOCAL_USING_OR_IMPL(isnanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isnanf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isnanf))(__x); })
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_isnanl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isnanl)
/* Return nonzero if `value' is not a number */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isnanl,(__LONGDOUBLE __x),{ return __builtin_isnanl(__x); })
#elif defined(__CRT_HAVE_isnanl)
/* Return nonzero if `value' is not a number */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isnanl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___isnanl)
/* Return nonzero if `value' is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isnanl,(__LONGDOUBLE __x),__isnanl,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/isnanl.h>
/* Return nonzero if `value' is not a number */
__NAMESPACE_LOCAL_USING_OR_IMPL(isnanl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isnanl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isnanl))(__x); })
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_MISC || (__USE_XOPEN && !__USE_XOPEN2K) */

/* Bessel functions. */
#if defined(__USE_MISC) || (defined(__USE_XOPEN) && __MATH_DECLARING_DOUBLE)
#if __has_builtin(__builtin_j0) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_j0)
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,j0,(double __x),{ return __builtin_j0(__x); })
#elif defined(__CRT_HAVE_j0)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,j0,(double __x),(__x))
#elif defined(__CRT_HAVE___j0)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,j0,(double __x),__j0,(__x))
#endif /* ... */
#if __has_builtin(__builtin_j1) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_j1)
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,j1,(double __x),{ return __builtin_j1(__x); })
#elif defined(__CRT_HAVE_j1)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,j1,(double __x),(__x))
#elif defined(__CRT_HAVE___j1)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,j1,(double __x),__j1,(__x))
#endif /* ... */
#if __has_builtin(__builtin_jn) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_jn)
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,jn,(int __n, double __x),{ return __builtin_jn(__n, __x); })
#elif defined(__CRT_HAVE_jn)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,jn,(int __n, double __x),(__n,__x))
#elif defined(__CRT_HAVE___jn)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,jn,(int __n, double __x),__jn,(__n,__x))
#endif /* ... */
#if __has_builtin(__builtin_y0) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_y0)
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,y0,(double __x),{ return __builtin_y0(__x); })
#elif defined(__CRT_HAVE_y0)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,y0,(double __x),(__x))
#elif defined(__CRT_HAVE___y0)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,y0,(double __x),__y0,(__x))
#endif /* ... */
#if __has_builtin(__builtin_y1) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_y1)
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,y1,(double __x),{ return __builtin_y1(__x); })
#elif defined(__CRT_HAVE_y1)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,y1,(double __x),(__x))
#elif defined(__CRT_HAVE___y1)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,y1,(double __x),__y1,(__x))
#endif /* ... */
#if __has_builtin(__builtin_yn) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_yn)
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,yn,(int __n, double __x),{ return __builtin_yn(__n, __x); })
#elif defined(__CRT_HAVE_yn)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,yn,(int __n, double __x),(__n,__x))
#elif defined(__CRT_HAVE___yn)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,yn,(int __n, double __x),__yn,(__n,__x))
#endif /* ... */
#if __has_builtin(__builtin_j0f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_j0f)
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,j0f,(float __x),{ return __builtin_j0f(__x); })
#elif defined(__CRT_HAVE_j0f)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,j0f,(float __x),(__x))
#elif defined(__CRT_HAVE___j0f)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,j0f,(float __x),__j0f,(__x))
#elif defined(__CRT_HAVE_j0) || defined(__CRT_HAVE___j0)
#include <libc/local/math/j0f.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(j0f, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL j0f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(j0f))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_j1f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_j1f)
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,j1f,(float __x),{ return __builtin_j1f(__x); })
#elif defined(__CRT_HAVE_j1f)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,j1f,(float __x),(__x))
#elif defined(__CRT_HAVE___j1f)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,j1f,(float __x),__j1f,(__x))
#elif defined(__CRT_HAVE_j1) || defined(__CRT_HAVE___j1)
#include <libc/local/math/j1f.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(j1f, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL j1f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(j1f))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_jnf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_jnf)
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,jnf,(int __n, float __x),{ return __builtin_jnf(__n, __x); })
#elif defined(__CRT_HAVE_jnf)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,jnf,(int __n, float __x),(__n,__x))
#elif defined(__CRT_HAVE___jnf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,jnf,(int __n, float __x),__jnf,(__n,__x))
#elif defined(__CRT_HAVE_jn) || defined(__CRT_HAVE___jn)
#include <libc/local/math/jnf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(jnf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL jnf)(int __n, float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(jnf))(__n, __x); })
#endif /* ... */
#if __has_builtin(__builtin_y0f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_y0f)
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,y0f,(float __x),{ return __builtin_y0f(__x); })
#elif defined(__CRT_HAVE_y0f)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,y0f,(float __x),(__x))
#elif defined(__CRT_HAVE___y0f)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,y0f,(float __x),__y0f,(__x))
#elif defined(__CRT_HAVE_y0) || defined(__CRT_HAVE___y0)
#include <libc/local/math/y0f.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(y0f, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL y0f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(y0f))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_y1f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_y1f)
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,y1f,(float __x),{ return __builtin_y1f(__x); })
#elif defined(__CRT_HAVE_y1f)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,y1f,(float __x),(__x))
#elif defined(__CRT_HAVE___y1f)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,y1f,(float __x),__y1f,(__x))
#elif defined(__CRT_HAVE_y1) || defined(__CRT_HAVE___y1)
#include <libc/local/math/y1f.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(y1f, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL y1f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(y1f))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_ynf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ynf)
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,ynf,(int __n, float __x),{ return __builtin_ynf(__n, __x); })
#elif defined(__CRT_HAVE_ynf)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,ynf,(int __n, float __x),(__n,__x))
#elif defined(__CRT_HAVE___ynf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,ynf,(int __n, float __x),__ynf,(__n,__x))
#elif defined(__CRT_HAVE_yn) || defined(__CRT_HAVE___yn)
#include <libc/local/math/ynf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ynf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL ynf)(int __n, float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ynf))(__n, __x); })
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_j0l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_j0l)
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,j0l,(__LONGDOUBLE __x),{ return __builtin_j0l(__x); })
#elif defined(__CRT_HAVE_j0l)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,j0l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___j0l)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,j0l,(__LONGDOUBLE __x),__j0l,(__x))
#elif defined(__CRT_HAVE_j0) || defined(__CRT_HAVE___j0)
#include <libc/local/math/j0l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(j0l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL j0l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(j0l))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_j1l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_j1l)
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,j1l,(__LONGDOUBLE __x),{ return __builtin_j1l(__x); })
#elif defined(__CRT_HAVE_j1l)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,j1l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___j1l)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,j1l,(__LONGDOUBLE __x),__j1l,(__x))
#elif defined(__CRT_HAVE_j1) || defined(__CRT_HAVE___j1)
#include <libc/local/math/j1l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(j1l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL j1l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(j1l))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_jnl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_jnl)
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,jnl,(int __n, __LONGDOUBLE __x),{ return __builtin_jnl(__n, __x); })
#elif defined(__CRT_HAVE_jnl)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,jnl,(int __n, __LONGDOUBLE __x),(__n,__x))
#elif defined(__CRT_HAVE___jnl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,jnl,(int __n, __LONGDOUBLE __x),__jnl,(__n,__x))
#elif defined(__CRT_HAVE_jn) || defined(__CRT_HAVE___jn)
#include <libc/local/math/jnl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(jnl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL jnl)(int __n, __LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(jnl))(__n, __x); })
#endif /* ... */
#if __has_builtin(__builtin_y0l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_y0l)
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,y0l,(__LONGDOUBLE __x),{ return __builtin_y0l(__x); })
#elif defined(__CRT_HAVE_y0l)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,y0l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___y0l)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,y0l,(__LONGDOUBLE __x),__y0l,(__x))
#elif defined(__CRT_HAVE_y0) || defined(__CRT_HAVE___y0)
#include <libc/local/math/y0l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(y0l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL y0l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(y0l))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_y1l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_y1l)
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,y1l,(__LONGDOUBLE __x),{ return __builtin_y1l(__x); })
#elif defined(__CRT_HAVE_y1l)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,y1l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___y1l)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,y1l,(__LONGDOUBLE __x),__y1l,(__x))
#elif defined(__CRT_HAVE_y1) || defined(__CRT_HAVE___y1)
#include <libc/local/math/y1l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(y1l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL y1l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(y1l))(__x); })
#endif /* ... */
#if __has_builtin(__builtin_ynl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ynl)
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ynl,(int __n, __LONGDOUBLE __x),{ return __builtin_ynl(__n, __x); })
#elif defined(__CRT_HAVE_ynl)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ynl,(int __n, __LONGDOUBLE __x),(__n,__x))
#elif defined(__CRT_HAVE___ynl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,ynl,(int __n, __LONGDOUBLE __x),__ynl,(__n,__x))
#elif defined(__CRT_HAVE_yn) || defined(__CRT_HAVE___yn)
#include <libc/local/math/ynl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ynl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL ynl)(int __n, __LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ynl))(__n, __x); })
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_MISC || (__USE_XOPEN && __MATH_DECLARING_DOUBLE) */

#if defined(__USE_MISC) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
#if __has_builtin(__builtin_lgamma) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgamma)
/* Obsolete export_alias for `lgamma' */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,gamma,(double __x),lgamma,{ return __builtin_lgamma(__x); })
#elif __has_builtin(__builtin_gamma) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_gamma)
/* Obsolete export_alias for `lgamma' */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,gamma,(double __x),{ return __builtin_gamma(__x); })
#elif defined(__CRT_HAVE_lgamma)
/* Obsolete export_alias for `lgamma' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,gamma,(double __x),lgamma,(__x))
#elif defined(__CRT_HAVE_gamma)
/* Obsolete export_alias for `lgamma' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,gamma,(double __x),(__x))
#elif defined(__CRT_HAVE___lgamma)
/* Obsolete export_alias for `lgamma' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,gamma,(double __x),__lgamma,(__x))
#elif defined(__CRT_HAVE___gamma)
/* Obsolete export_alias for `lgamma' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,gamma,(double __x),__gamma,(__x))
#endif /* ... */
#if __has_builtin(__builtin_lgammaf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgammaf)
/* Obsolete export_alias for `lgammaf' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,gammaf,(float __x),lgammaf,{ return __builtin_lgammaf(__x); })
#elif __has_builtin(__builtin_gammaf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_gammaf)
/* Obsolete export_alias for `lgammaf' */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,gammaf,(float __x),{ return __builtin_gammaf(__x); })
#elif defined(__CRT_HAVE_lgammaf)
/* Obsolete export_alias for `lgammaf' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,gammaf,(float __x),lgammaf,(__x))
#elif defined(__CRT_HAVE_gammaf)
/* Obsolete export_alias for `lgammaf' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,gammaf,(float __x),(__x))
#elif defined(__CRT_HAVE___lgammaf)
/* Obsolete export_alias for `lgammaf' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,gammaf,(float __x),__lgammaf,(__x))
#elif defined(__CRT_HAVE___gammaf)
/* Obsolete export_alias for `lgammaf' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,gammaf,(float __x),__gammaf,(__x))
#elif defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE_gamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma)
#include <libc/local/math/lgammaf.h>
/* Obsolete export_alias for `lgammaf' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL gammaf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammaf))(__x); }
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_lgammal) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgammal)
/* Obsolete export_alias for `lgammal' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,gammal,(__LONGDOUBLE __x),lgammal,{ return __builtin_lgammal(__x); })
#elif __has_builtin(__builtin_gammal) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_gammal)
/* Obsolete export_alias for `lgammal' */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,gammal,(__LONGDOUBLE __x),{ return __builtin_gammal(__x); })
#elif defined(__CRT_HAVE_lgammal)
/* Obsolete export_alias for `lgammal' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,gammal,(__LONGDOUBLE __x),lgammal,(__x))
#elif defined(__CRT_HAVE_gammal)
/* Obsolete export_alias for `lgammal' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,gammal,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___lgammal)
/* Obsolete export_alias for `lgammal' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,gammal,(__LONGDOUBLE __x),__lgammal,(__x))
#elif defined(__CRT_HAVE___gammal)
/* Obsolete export_alias for `lgammal' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,gammal,(__LONGDOUBLE __x),__gammal,(__x))
#elif defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE_gamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma)
#include <libc/local/math/lgammal.h>
/* Obsolete export_alias for `lgammal' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL gammal)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammal))(__x); }
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_MISC || (__USE_XOPEN && !__USE_XOPEN2K) */
#ifdef __USE_MISC
#if __has_builtin(__builtin_lgamma_r) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgamma_r)
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW_NCX,lgamma_r,(double __x, int *__signgamp),{ return __builtin_lgamma_r(__x, __signgamp); })
#elif defined(__CRT_HAVE_lgamma_r)
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW_NCX,lgamma_r,(double __x, int *__signgamp),(__x,__signgamp))
#elif defined(__CRT_HAVE___lgamma_r)
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW_NCX,lgamma_r,(double __x, int *__signgamp),__lgamma_r,(__x,__signgamp))
#endif /* ... */
#if __has_builtin(__builtin_lgammaf_r) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgammaf_r)
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW_NCX,lgammaf_r,(float __x, int *__signgamp),{ return __builtin_lgammaf_r(__x, __signgamp); })
#elif defined(__CRT_HAVE_lgammaf_r)
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW_NCX,lgammaf_r,(float __x, int *__signgamp),(__x,__signgamp))
#elif defined(__CRT_HAVE___lgammaf_r)
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW_NCX,lgammaf_r,(float __x, int *__signgamp),__lgammaf_r,(__x,__signgamp))
#elif defined(__CRT_HAVE_lgamma_r) || defined(__CRT_HAVE___lgamma_r)
#include <libc/local/math/lgammaf_r.h>
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__NAMESPACE_LOCAL_USING_OR_IMPL(lgammaf_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW_NCX(__LIBCCALL lgammaf_r)(float __x, int *__signgamp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammaf_r))(__x, __signgamp); })
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_lgammal_r) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgammal_r)
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW_NCX,lgammal_r,(__LONGDOUBLE __x, int *__signgamp),{ return __builtin_lgammal_r(__x, __signgamp); })
#elif defined(__CRT_HAVE_lgammal_r)
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW_NCX,lgammal_r,(__LONGDOUBLE __x, int *__signgamp),(__x,__signgamp))
#elif defined(__CRT_HAVE___lgammal_r)
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW_NCX,lgammal_r,(__LONGDOUBLE __x, int *__signgamp),__lgammal_r,(__x,__signgamp))
#elif defined(__CRT_HAVE_lgamma_r) || defined(__CRT_HAVE___lgamma_r)
#include <libc/local/math/lgammal_r.h>
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__NAMESPACE_LOCAL_USING_OR_IMPL(lgammal_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL lgammal_r)(__LONGDOUBLE __x, int *__signgamp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammal_r))(__x, __signgamp); })
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_MISC */

#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8))
#if __has_builtin(__builtin_scalb) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalb)
/* Return `x' times (2 to the Nth power) */
__CEIDECLARE(__ATTR_WUNUSED,double,__NOTHROW,scalb,(double __x, double __fn),{ return __builtin_scalb(__x, __fn); })
#elif defined(__CRT_HAVE_scalb)
/* Return `x' times (2 to the Nth power) */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,scalb,(double __x, double __fn),(__x,__fn))
#elif defined(__CRT_HAVE__scalb)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,scalb,(double __x, double __fn),_scalb,(__x,__fn))
#elif defined(__CRT_HAVE___scalb)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,scalb,(double __x, double __fn),__scalb,(__x,__fn))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/scalb.h>
/* Return `x' times (2 to the Nth power) */
__NAMESPACE_LOCAL_USING_OR_IMPL(scalb, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL scalb)(double __x, double __fn) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalb))(__x, __fn); })
#endif /* ... */
#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K8) */
#ifdef __USE_MISC
#if __has_builtin(__builtin_scalbf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbf)
/* Return `x' times (2 to the Nth power) */
__CEIDECLARE(__ATTR_WUNUSED,float,__NOTHROW,scalbf,(float __x, float __fn),{ return __builtin_scalbf(__x, __fn); })
#elif defined(__CRT_HAVE_scalbf)
/* Return `x' times (2 to the Nth power) */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,scalbf,(float __x, float __fn),(__x,__fn))
#elif defined(__CRT_HAVE__scalbf)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,scalbf,(float __x, float __fn),_scalbf,(__x,__fn))
#elif defined(__CRT_HAVE___scalbf)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,scalbf,(float __x, float __fn),__scalbf,(__x,__fn))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_scalb) || defined(__CRT_HAVE__scalb) || defined(__CRT_HAVE___scalb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/scalbf.h>
/* Return `x' times (2 to the Nth power) */
__NAMESPACE_LOCAL_USING_OR_IMPL(scalbf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL scalbf)(float __x, float __fn) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbf))(__x, __fn); })
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_scalbl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbl)
/* Return `x' times (2 to the Nth power) */
__CEIDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbl,(__LONGDOUBLE __x, __LONGDOUBLE __fn),{ return __builtin_scalbl(__x, __fn); })
#elif defined(__CRT_HAVE_scalbl)
/* Return `x' times (2 to the Nth power) */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbl,(__LONGDOUBLE __x, __LONGDOUBLE __fn),(__x,__fn))
#elif defined(__CRT_HAVE___scalbl)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,scalbl,(__LONGDOUBLE __x, __LONGDOUBLE __fn),__scalbl,(__x,__fn))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_scalb) || defined(__CRT_HAVE__scalb) || defined(__CRT_HAVE___scalb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/scalbl.h>
/* Return `x' times (2 to the Nth power) */
__NAMESPACE_LOCAL_USING_OR_IMPL(scalbl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL scalbl)(__LONGDOUBLE __x, __LONGDOUBLE __fn) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbl))(__x, __fn); })
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_MISC */



#if 1 /* GLIBc aliases */
#if __has_builtin(__builtin_acos) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acos)
/* Arc cosine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__acos,(double __x),acos,{ return __builtin_acos(__x); })
#elif defined(__CRT_HAVE_acos)
/* Arc cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__acos,(double __x),acos,(__x))
#elif defined(__CRT_HAVE___acos)
/* Arc cosine of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__acos,(double __x),(__x))
#endif /* ... */
#if __has_builtin(__builtin_asin) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asin)
/* Arc sine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__asin,(double __x),asin,{ return __builtin_asin(__x); })
#elif defined(__CRT_HAVE_asin)
/* Arc sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__asin,(double __x),asin,(__x))
#elif defined(__CRT_HAVE___asin)
/* Arc sine of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__asin,(double __x),(__x))
#endif /* ... */
#if __has_builtin(__builtin_atan) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan)
/* Arc tangent of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__atan,(double __x),atan,{ return __builtin_atan(__x); })
#elif defined(__CRT_HAVE_atan)
/* Arc tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__atan,(double __x),atan,(__x))
#elif defined(__CRT_HAVE___atan)
/* Arc tangent of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__atan,(double __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/atan.h>
/* Arc tangent of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __atan)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atan))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_atan2) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan2)
/* Arc tangent of `y / x' */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__atan2,(double __y, double __x),atan2,{ return __builtin_atan2(__y, __x); })
#elif defined(__CRT_HAVE_atan2)
/* Arc tangent of `y / x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__atan2,(double __y, double __x),atan2,(__y,__x))
#elif defined(__CRT_HAVE___atan2)
/* Arc tangent of `y / x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__atan2,(double __y, double __x),(__y,__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/atan2.h>
/* Arc tangent of `y / x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __atan2)(double __y, double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atan2))(__y, __x); }
#endif /* ... */
#if __has_builtin(__builtin_cos) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cos)
/* Cosine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cos,double,__NOTHROW,__cos,(double __x),cos,{ return __builtin_cos(__x); })
#elif defined(__CRT_HAVE_cos)
/* Cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cos,double,__NOTHROW,__cos,(double __x),cos,(__x))
#elif defined(__CRT_HAVE___cos)
/* Cosine of `x' */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_cos,double,__NOTHROW,__cos,(double __x),(__x))
#endif /* ... */
#if __has_builtin(__builtin_sin) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sin)
/* Sine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sin,double,__NOTHROW,__sin,(double __x),sin,{ return __builtin_sin(__x); })
#elif defined(__CRT_HAVE_sin)
/* Sine of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sin,double,__NOTHROW,__sin,(double __x),sin,(__x))
#elif defined(__CRT_HAVE___sin)
/* Sine of `x' */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_sin,double,__NOTHROW,__sin,(double __x),(__x))
#endif /* ... */
#if __has_builtin(__builtin_tan) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tan)
/* Tangent of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__tan,(double __x),tan,{ return __builtin_tan(__x); })
#elif defined(__CRT_HAVE_tan)
/* Tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__tan,(double __x),tan,(__x))
#elif defined(__CRT_HAVE___tan)
/* Tangent of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__tan,(double __x),(__x))
#endif /* ... */
#if __has_builtin(__builtin_cosh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cosh)
/* Hyperbolic cosine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__cosh,(double __x),cosh,{ return __builtin_cosh(__x); })
#elif defined(__CRT_HAVE_cosh)
/* Hyperbolic cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__cosh,(double __x),cosh,(__x))
#elif defined(__CRT_HAVE___cosh)
/* Hyperbolic cosine of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__cosh,(double __x),(__x))
#endif /* ... */
#if __has_builtin(__builtin_sinh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinh)
/* Hyperbolic sine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__sinh,(double __x),sinh,{ return __builtin_sinh(__x); })
#elif defined(__CRT_HAVE_sinh)
/* Hyperbolic sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__sinh,(double __x),sinh,(__x))
#elif defined(__CRT_HAVE___sinh)
/* Hyperbolic sine of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__sinh,(double __x),(__x))
#endif /* ... */
#if __has_builtin(__builtin_tanh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanh)
/* Hyperbolic tangent of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__tanh,(double __x),tanh,{ return __builtin_tanh(__x); })
#elif defined(__CRT_HAVE_tanh)
/* Hyperbolic tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__tanh,(double __x),tanh,(__x))
#elif defined(__CRT_HAVE___tanh)
/* Hyperbolic tangent of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__tanh,(double __x),(__x))
#endif /* ... */
#if __has_builtin(__builtin_acosf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acosf)
/* Arc cosine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__acosf,(float __x),acosf,{ return __builtin_acosf(__x); })
#elif defined(__CRT_HAVE_acosf)
/* Arc cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__acosf,(float __x),acosf,(__x))
#elif defined(__CRT_HAVE___acosf)
/* Arc cosine of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__acosf,(float __x),(__x))
#elif defined(__CRT_HAVE_acos) || defined(__CRT_HAVE___acos)
#include <libc/local/math/acosf.h>
/* Arc cosine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __acosf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(acosf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_asinf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinf)
/* Arc sine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__asinf,(float __x),asinf,{ return __builtin_asinf(__x); })
#elif defined(__CRT_HAVE_asinf)
/* Arc sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__asinf,(float __x),asinf,(__x))
#elif defined(__CRT_HAVE___asinf)
/* Arc sine of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__asinf,(float __x),(__x))
#elif defined(__CRT_HAVE_asin) || defined(__CRT_HAVE___asin)
#include <libc/local/math/asinf.h>
/* Arc sine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __asinf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asinf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_atanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanf)
/* Arc tangent of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__atanf,(float __x),atanf,{ return __builtin_atanf(__x); })
#elif defined(__CRT_HAVE_atanf)
/* Arc tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__atanf,(float __x),atanf,(__x))
#elif defined(__CRT_HAVE___atanf)
/* Arc tangent of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__atanf,(float __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_atan) || defined(__CRT_HAVE___atan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/atanf.h>
/* Arc tangent of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __atanf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atanf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_atan2f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan2f)
/* Arc tangent of `y / x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__atan2f,(float __y, float __x),atan2f,{ return __builtin_atan2f(__y, __x); })
#elif defined(__CRT_HAVE_atan2f)
/* Arc tangent of `y / x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__atan2f,(float __y, float __x),atan2f,(__y,__x))
#elif defined(__CRT_HAVE___atan2f)
/* Arc tangent of `y / x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__atan2f,(float __y, float __x),(__y,__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/atan2f.h>
/* Arc tangent of `y / x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __atan2f)(float __y, float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atan2f))(__y, __x); }
#endif /* ... */
#if __has_builtin(__builtin_cosf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cosf)
/* Cosine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cosf,float,__NOTHROW,__cosf,(float __x),cosf,{ return __builtin_cosf(__x); })
#elif defined(__CRT_HAVE_cosf)
/* Cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cosf,float,__NOTHROW,__cosf,(float __x),cosf,(__x))
#elif defined(__CRT_HAVE___cosf)
/* Cosine of `x' */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_cosf,float,__NOTHROW,__cosf,(float __x),(__x))
#elif defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos)
#include <libc/local/math/cosf.h>
/* Cosine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_cosf float __NOTHROW(__LIBCCALL __cosf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cosf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_sinf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinf)
/* Sine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sinf,float,__NOTHROW,__sinf,(float __x),sinf,{ return __builtin_sinf(__x); })
#elif defined(__CRT_HAVE_sinf)
/* Sine of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sinf,float,__NOTHROW,__sinf,(float __x),sinf,(__x))
#elif defined(__CRT_HAVE___sinf)
/* Sine of `x' */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_sinf,float,__NOTHROW,__sinf,(float __x),(__x))
#elif defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)
#include <libc/local/math/sinf.h>
/* Sine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_sinf float __NOTHROW(__LIBCCALL __sinf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sinf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_tanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanf)
/* Tangent of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__tanf,(float __x),tanf,{ return __builtin_tanf(__x); })
#elif defined(__CRT_HAVE_tanf)
/* Tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__tanf,(float __x),tanf,(__x))
#elif defined(__CRT_HAVE___tanf)
/* Tangent of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__tanf,(float __x),(__x))
#elif defined(__CRT_HAVE_tan) || defined(__CRT_HAVE___tan)
#include <libc/local/math/tanf.h>
/* Tangent of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __tanf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tanf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_coshf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_coshf)
/* Hyperbolic cosine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__coshf,(float __x),coshf,{ return __builtin_coshf(__x); })
#elif defined(__CRT_HAVE_coshf)
/* Hyperbolic cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__coshf,(float __x),coshf,(__x))
#elif defined(__CRT_HAVE___coshf)
/* Hyperbolic cosine of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__coshf,(float __x),(__x))
#elif defined(__CRT_HAVE_cosh) || defined(__CRT_HAVE___cosh)
#include <libc/local/math/coshf.h>
/* Hyperbolic cosine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __coshf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(coshf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_sinhf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinhf)
/* Hyperbolic sine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__sinhf,(float __x),sinhf,{ return __builtin_sinhf(__x); })
#elif defined(__CRT_HAVE_sinhf)
/* Hyperbolic sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__sinhf,(float __x),sinhf,(__x))
#elif defined(__CRT_HAVE___sinhf)
/* Hyperbolic sine of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__sinhf,(float __x),(__x))
#elif defined(__CRT_HAVE_sinh) || defined(__CRT_HAVE___sinh)
#include <libc/local/math/sinhf.h>
/* Hyperbolic sine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __sinhf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sinhf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_tanhf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanhf)
/* Hyperbolic tangent of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__tanhf,(float __x),tanhf,{ return __builtin_tanhf(__x); })
#elif defined(__CRT_HAVE_tanhf)
/* Hyperbolic tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__tanhf,(float __x),tanhf,(__x))
#elif defined(__CRT_HAVE___tanhf)
/* Hyperbolic tangent of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__tanhf,(float __x),(__x))
#elif defined(__CRT_HAVE_tanh) || defined(__CRT_HAVE___tanh)
#include <libc/local/math/tanhf.h>
/* Hyperbolic tangent of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __tanhf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tanhf))(__x); }
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_acosl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acosl)
/* Arc cosine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__acosl,(__LONGDOUBLE __x),acosl,{ return __builtin_acosl(__x); })
#elif defined(__CRT_HAVE_acosl)
/* Arc cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__acosl,(__LONGDOUBLE __x),acosl,(__x))
#elif defined(__CRT_HAVE___acosl)
/* Arc cosine of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__acosl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_acos) || defined(__CRT_HAVE___acos)
#include <libc/local/math/acosl.h>
/* Arc cosine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __acosl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(acosl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_asinl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinl)
/* Arc sine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__asinl,(__LONGDOUBLE __x),asinl,{ return __builtin_asinl(__x); })
#elif defined(__CRT_HAVE_asinl)
/* Arc sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__asinl,(__LONGDOUBLE __x),asinl,(__x))
#elif defined(__CRT_HAVE___asinl)
/* Arc sine of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__asinl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_asin) || defined(__CRT_HAVE___asin)
#include <libc/local/math/asinl.h>
/* Arc sine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __asinl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asinl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_atanl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanl)
/* Arc tangent of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__atanl,(__LONGDOUBLE __x),atanl,{ return __builtin_atanl(__x); })
#elif defined(__CRT_HAVE_atanl)
/* Arc tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__atanl,(__LONGDOUBLE __x),atanl,(__x))
#elif defined(__CRT_HAVE___atanl)
/* Arc tangent of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__atanl,(__LONGDOUBLE __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_atan) || defined(__CRT_HAVE___atan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/atanl.h>
/* Arc tangent of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __atanl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atanl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_atan2l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atan2l)
/* Arc tangent of `y / x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__atan2l,(__LONGDOUBLE __y, __LONGDOUBLE __x),atan2l,{ return __builtin_atan2l(__y, __x); })
#elif defined(__CRT_HAVE_atan2l)
/* Arc tangent of `y / x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__atan2l,(__LONGDOUBLE __y, __LONGDOUBLE __x),atan2l,(__y,__x))
#elif defined(__CRT_HAVE___atan2l)
/* Arc tangent of `y / x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__atan2l,(__LONGDOUBLE __y, __LONGDOUBLE __x),(__y,__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_atan2) || defined(__CRT_HAVE___atan2) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/atan2l.h>
/* Arc tangent of `y / x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __atan2l)(__LONGDOUBLE __y, __LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atan2l))(__y, __x); }
#endif /* ... */
#if __has_builtin(__builtin_cosl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cosl)
/* Cosine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cosl,__LONGDOUBLE,__NOTHROW,__cosl,(__LONGDOUBLE __x),cosl,{ return __builtin_cosl(__x); })
#elif defined(__CRT_HAVE_cosl)
/* Cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_cosl,__LONGDOUBLE,__NOTHROW,__cosl,(__LONGDOUBLE __x),cosl,(__x))
#elif defined(__CRT_HAVE___cosl)
/* Cosine of `x' */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_cosl,__LONGDOUBLE,__NOTHROW,__cosl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_cos) || defined(__CRT_HAVE___cos)
#include <libc/local/math/cosl.h>
/* Cosine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_cosl __LONGDOUBLE __NOTHROW(__LIBCCALL __cosl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cosl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_sinl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinl)
/* Sine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sinl,__LONGDOUBLE,__NOTHROW,__sinl,(__LONGDOUBLE __x),sinl,{ return __builtin_sinl(__x); })
#elif defined(__CRT_HAVE_sinl)
/* Sine of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_sinl,__LONGDOUBLE,__NOTHROW,__sinl,(__LONGDOUBLE __x),sinl,(__x))
#elif defined(__CRT_HAVE___sinl)
/* Sine of `x' */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_sinl,__LONGDOUBLE,__NOTHROW,__sinl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_sin) || defined(__CRT_HAVE___sin)
#include <libc/local/math/sinl.h>
/* Sine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_sinl __LONGDOUBLE __NOTHROW(__LIBCCALL __sinl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sinl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_tanl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanl)
/* Tangent of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__tanl,(__LONGDOUBLE __x),tanl,{ return __builtin_tanl(__x); })
#elif defined(__CRT_HAVE_tanl)
/* Tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__tanl,(__LONGDOUBLE __x),tanl,(__x))
#elif defined(__CRT_HAVE___tanl)
/* Tangent of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__tanl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_tan) || defined(__CRT_HAVE___tan)
#include <libc/local/math/tanl.h>
/* Tangent of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __tanl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tanl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_coshl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_coshl)
/* Hyperbolic cosine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__coshl,(__LONGDOUBLE __x),coshl,{ return __builtin_coshl(__x); })
#elif defined(__CRT_HAVE_coshl)
/* Hyperbolic cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__coshl,(__LONGDOUBLE __x),coshl,(__x))
#elif defined(__CRT_HAVE___coshl)
/* Hyperbolic cosine of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__coshl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_cosh) || defined(__CRT_HAVE___cosh)
#include <libc/local/math/coshl.h>
/* Hyperbolic cosine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __coshl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(coshl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_sinhl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sinhl)
/* Hyperbolic sine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__sinhl,(__LONGDOUBLE __x),sinhl,{ return __builtin_sinhl(__x); })
#elif defined(__CRT_HAVE_sinhl)
/* Hyperbolic sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__sinhl,(__LONGDOUBLE __x),sinhl,(__x))
#elif defined(__CRT_HAVE___sinhl)
/* Hyperbolic sine of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__sinhl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_sinh) || defined(__CRT_HAVE___sinh)
#include <libc/local/math/sinhl.h>
/* Hyperbolic sine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __sinhl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sinhl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_tanhl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tanhl)
/* Hyperbolic tangent of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__tanhl,(__LONGDOUBLE __x),tanhl,{ return __builtin_tanhl(__x); })
#elif defined(__CRT_HAVE_tanhl)
/* Hyperbolic tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__tanhl,(__LONGDOUBLE __x),tanhl,(__x))
#elif defined(__CRT_HAVE___tanhl)
/* Hyperbolic tangent of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__tanhl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_tanh) || defined(__CRT_HAVE___tanh)
#include <libc/local/math/tanhl.h>
/* Hyperbolic tangent of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __tanhl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tanhl))(__x); }
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#ifdef __USE_GNU
#if __has_builtin(__builtin_sincos) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sincos)
/* Cosine and sine of `x' */
__CEIREDIRECT(__DECL_SIMD_sincos __ATTR_NONNULL((2, 3)),void,__NOTHROW,__sincos,(double __x, double *__psinx, double *__pcosx),sincos,{ __builtin_sincos(__x, __psinx, __pcosx); })
#elif defined(__CRT_HAVE_sincos)
/* Cosine and sine of `x' */
__CREDIRECT_VOID(__DECL_SIMD_sincos __ATTR_NONNULL((2, 3)),__NOTHROW,__sincos,(double __x, double *__psinx, double *__pcosx),sincos,(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE___sincos)
/* Cosine and sine of `x' */
__CDECLARE_VOID(__DECL_SIMD_sincos __ATTR_NONNULL((2, 3)),__NOTHROW,__sincos,(double __x, double *__psinx, double *__pcosx),(__x,__psinx,__pcosx))
#endif /* ... */
#if __has_builtin(__builtin_sincosf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sincosf)
/* Cosine and sine of `x' */
__CEIREDIRECT(__DECL_SIMD_sincosf __ATTR_NONNULL((2, 3)),void,__NOTHROW,__sincosf,(float __x, float *__psinx, float *__pcosx),sincosf,{ __builtin_sincosf(__x, __psinx, __pcosx); })
#elif defined(__CRT_HAVE_sincosf)
/* Cosine and sine of `x' */
__CREDIRECT_VOID(__DECL_SIMD_sincosf __ATTR_NONNULL((2, 3)),__NOTHROW,__sincosf,(float __x, float *__psinx, float *__pcosx),sincosf,(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE___sincosf)
/* Cosine and sine of `x' */
__CDECLARE_VOID(__DECL_SIMD_sincosf __ATTR_NONNULL((2, 3)),__NOTHROW,__sincosf,(float __x, float *__psinx, float *__pcosx),(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE_sincos) || defined(__CRT_HAVE___sincos)
#include <libc/local/math/sincosf.h>
/* Cosine and sine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __DECL_SIMD_sincosf __ATTR_NONNULL((2, 3)) void __NOTHROW(__LIBCCALL __sincosf)(float __x, float *__psinx, float *__pcosx) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sincosf))(__x, __psinx, __pcosx); }
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_sincosl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sincosl)
/* Cosine and sine of `x' */
__CEIREDIRECT(__DECL_SIMD_sincosl __ATTR_NONNULL((2, 3)),void,__NOTHROW,__sincosl,(__LONGDOUBLE __x, __LONGDOUBLE *__psinx, __LONGDOUBLE *__pcosx),sincosl,{ __builtin_sincosl(__x, __psinx, __pcosx); })
#elif defined(__CRT_HAVE_sincosl)
/* Cosine and sine of `x' */
__CREDIRECT_VOID(__DECL_SIMD_sincosl __ATTR_NONNULL((2, 3)),__NOTHROW,__sincosl,(__LONGDOUBLE __x, __LONGDOUBLE *__psinx, __LONGDOUBLE *__pcosx),sincosl,(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE___sincosl)
/* Cosine and sine of `x' */
__CDECLARE_VOID(__DECL_SIMD_sincosl __ATTR_NONNULL((2, 3)),__NOTHROW,__sincosl,(__LONGDOUBLE __x, __LONGDOUBLE *__psinx, __LONGDOUBLE *__pcosx),(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE___sincos) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Cosine and sine of `x' */
__CREDIRECT_VOID(__DECL_SIMD_sincosl __ATTR_NONNULL((2, 3)),__NOTHROW,__sincosl,(__LONGDOUBLE __x, __LONGDOUBLE *__psinx, __LONGDOUBLE *__pcosx),__sincos,(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE_sincos) && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)
/* Cosine and sine of `x' */
__CREDIRECT_VOID(__DECL_SIMD_sincosl __ATTR_NONNULL((2, 3)),__NOTHROW,__sincosl,(__LONGDOUBLE __x, __LONGDOUBLE *__psinx, __LONGDOUBLE *__pcosx),sincos,(__x,__psinx,__pcosx))
#elif defined(__CRT_HAVE_sincos) || defined(__CRT_HAVE___sincos)
#include <libc/local/math/sincosl.h>
/* Cosine and sine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __DECL_SIMD_sincosl __ATTR_NONNULL((2, 3)) void __NOTHROW(__LIBCCALL __sincosl)(__LONGDOUBLE __x, __LONGDOUBLE *__psinx, __LONGDOUBLE *__pcosx) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sincosl))(__x, __psinx, __pcosx); }
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_GNU */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#if __has_builtin(__builtin_acosh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acosh)
/* Hyperbolic arc cosine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__acosh,(double __x),acosh,{ return __builtin_acosh(__x); })
#elif defined(__CRT_HAVE_acosh)
/* Hyperbolic arc cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__acosh,(double __x),acosh,(__x))
#elif defined(__CRT_HAVE___acosh)
/* Hyperbolic arc cosine of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__acosh,(double __x),(__x))
#endif /* ... */
#if __has_builtin(__builtin_asinh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinh)
/* Hyperbolic arc sine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__asinh,(double __x),asinh,{ return __builtin_asinh(__x); })
#elif defined(__CRT_HAVE_asinh)
/* Hyperbolic arc sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__asinh,(double __x),asinh,(__x))
#elif defined(__CRT_HAVE___asinh)
/* Hyperbolic arc sine of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__asinh,(double __x),(__x))
#endif /* ... */
#if __has_builtin(__builtin_atanh) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanh)
/* Hyperbolic arc tangent of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__atanh,(double __x),atanh,{ return __builtin_atanh(__x); })
#elif defined(__CRT_HAVE_atanh)
/* Hyperbolic arc tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__atanh,(double __x),atanh,(__x))
#elif defined(__CRT_HAVE___atanh)
/* Hyperbolic arc tangent of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__atanh,(double __x),(__x))
#endif /* ... */
#if __has_builtin(__builtin_acoshf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acoshf)
/* Hyperbolic arc cosine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__acoshf,(float __x),acoshf,{ return __builtin_acoshf(__x); })
#elif defined(__CRT_HAVE_acoshf)
/* Hyperbolic arc cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__acoshf,(float __x),acoshf,(__x))
#elif defined(__CRT_HAVE___acoshf)
/* Hyperbolic arc cosine of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__acoshf,(float __x),(__x))
#elif defined(__CRT_HAVE_acosh) || defined(__CRT_HAVE___acosh)
#include <libc/local/math/acoshf.h>
/* Hyperbolic arc cosine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __acoshf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(acoshf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_asinhf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinhf)
/* Hyperbolic arc sine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__asinhf,(float __x),asinhf,{ return __builtin_asinhf(__x); })
#elif defined(__CRT_HAVE_asinhf)
/* Hyperbolic arc sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__asinhf,(float __x),asinhf,(__x))
#elif defined(__CRT_HAVE___asinhf)
/* Hyperbolic arc sine of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__asinhf,(float __x),(__x))
#elif defined(__CRT_HAVE_asinh) || defined(__CRT_HAVE___asinh)
#include <libc/local/math/asinhf.h>
/* Hyperbolic arc sine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __asinhf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asinhf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_atanhf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanhf)
/* Hyperbolic arc tangent of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__atanhf,(float __x),atanhf,{ return __builtin_atanhf(__x); })
#elif defined(__CRT_HAVE_atanhf)
/* Hyperbolic arc tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__atanhf,(float __x),atanhf,(__x))
#elif defined(__CRT_HAVE___atanhf)
/* Hyperbolic arc tangent of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__atanhf,(float __x),(__x))
#elif defined(__CRT_HAVE_atanh) || defined(__CRT_HAVE___atanh)
#include <libc/local/math/atanhf.h>
/* Hyperbolic arc tangent of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __atanhf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atanhf))(__x); }
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_acoshl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_acoshl)
/* Hyperbolic arc cosine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__acoshl,(__LONGDOUBLE __x),acoshl,{ return __builtin_acoshl(__x); })
#elif defined(__CRT_HAVE_acoshl)
/* Hyperbolic arc cosine of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__acoshl,(__LONGDOUBLE __x),acoshl,(__x))
#elif defined(__CRT_HAVE___acoshl)
/* Hyperbolic arc cosine of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__acoshl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_acosh) || defined(__CRT_HAVE___acosh)
#include <libc/local/math/acoshl.h>
/* Hyperbolic arc cosine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __acoshl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(acoshl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_asinhl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_asinhl)
/* Hyperbolic arc sine of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__asinhl,(__LONGDOUBLE __x),asinhl,{ return __builtin_asinhl(__x); })
#elif defined(__CRT_HAVE_asinhl)
/* Hyperbolic arc sine of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__asinhl,(__LONGDOUBLE __x),asinhl,(__x))
#elif defined(__CRT_HAVE___asinhl)
/* Hyperbolic arc sine of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__asinhl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_asinh) || defined(__CRT_HAVE___asinh)
#include <libc/local/math/asinhl.h>
/* Hyperbolic arc sine of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __asinhl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asinhl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_atanhl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_atanhl)
/* Hyperbolic arc tangent of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__atanhl,(__LONGDOUBLE __x),atanhl,{ return __builtin_atanhl(__x); })
#elif defined(__CRT_HAVE_atanhl)
/* Hyperbolic arc tangent of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__atanhl,(__LONGDOUBLE __x),atanhl,(__x))
#elif defined(__CRT_HAVE___atanhl)
/* Hyperbolic arc tangent of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__atanhl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_atanh) || defined(__CRT_HAVE___atanh)
#include <libc/local/math/atanhl.h>
/* Hyperbolic arc tangent of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __atanhl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atanhl))(__x); }
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */
#if __has_builtin(__builtin_exp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp)
/* Exponential function of `x' */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_exp,double,__NOTHROW,__exp,(double __x),exp,{ return __builtin_exp(__x); })
#elif defined(__CRT_HAVE_exp)
/* Exponential function of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_exp,double,__NOTHROW,__exp,(double __x),exp,(__x))
#elif defined(__CRT_HAVE___exp)
/* Exponential function of `x' */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_exp,double,__NOTHROW,__exp,(double __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/exp.h>
/* Exponential function of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_exp double __NOTHROW(__LIBCCALL __exp)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(exp))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_frexp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_frexp)
/* Break `value' into a normalized fraction and an integral power of 2 */
__CEIREDIRECT(__ATTR_NONNULL((2)),double,__NOTHROW_NCX,__frexp,(double __x, int *__pexponent),frexp,{ return __builtin_frexp(__x, __pexponent); })
#elif defined(__CRT_HAVE_frexp)
/* Break `value' into a normalized fraction and an integral power of 2 */
__CREDIRECT(__ATTR_NONNULL((2)),double,__NOTHROW_NCX,__frexp,(double __x, int *__pexponent),frexp,(__x,__pexponent))
#elif defined(__CRT_HAVE___frexp)
/* Break `value' into a normalized fraction and an integral power of 2 */
__CDECLARE(__ATTR_NONNULL((2)),double,__NOTHROW_NCX,__frexp,(double __x, int *__pexponent),(__x,__pexponent))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/frexp.h>
/* Break `value' into a normalized fraction and an integral power of 2 */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) double __NOTHROW_NCX(__LIBCCALL __frexp)(double __x, int *__pexponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(frexp))(__x, __pexponent); }
#endif /* ... */
#if __has_builtin(__builtin_ldexp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ldexp)
/* `x' times (two to the `exponent' power) */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__ldexp,(double __x, int __exponent),ldexp,{ return __builtin_ldexp(__x, __exponent); })
#elif defined(__CRT_HAVE_ldexp)
/* `x' times (two to the `exponent' power) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__ldexp,(double __x, int __exponent),ldexp,(__x,__exponent))
#elif defined(__CRT_HAVE___ldexp)
/* `x' times (two to the `exponent' power) */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__ldexp,(double __x, int __exponent),(__x,__exponent))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/ldexp.h>
/* `x' times (two to the `exponent' power) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __ldexp)(double __x, int __exponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ldexp))(__x, __exponent); }
#endif /* ... */
#if __has_builtin(__builtin_log) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log)
/* Natural logarithm of `x' */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_log,double,__NOTHROW,__log,(double __x),log,{ return __builtin_log(__x); })
#elif defined(__CRT_HAVE_log)
/* Natural logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_log,double,__NOTHROW,__log,(double __x),log,(__x))
#elif defined(__CRT_HAVE___log)
/* Natural logarithm of `x' */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_log,double,__NOTHROW,__log,(double __x),(__x))
#endif /* ... */
#if __has_builtin(__builtin_log10) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log10)
/* Base-ten logarithm of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__log10,(double __x),log10,{ return __builtin_log10(__x); })
#elif defined(__CRT_HAVE_log10)
/* Base-ten logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__log10,(double __x),log10,(__x))
#elif defined(__CRT_HAVE___log10)
/* Base-ten logarithm of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__log10,(double __x),(__x))
#endif /* ... */
#if __has_builtin(__builtin_modf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_modf)
/* Break `value' into integral and fractional parts */
__CEIREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),double,__NOTHROW_NCX,__modf,(double __x, double *__iptr),modf,{ return __builtin_modf(__x, __iptr); })
#elif defined(__CRT_HAVE_modf)
/* Break `value' into integral and fractional parts */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),double,__NOTHROW_NCX,__modf,(double __x, double *__iptr),modf,(__x,__iptr))
#elif defined(__CRT_HAVE___modf)
/* Break `value' into integral and fractional parts */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),double,__NOTHROW_NCX,__modf,(double __x, double *__iptr),(__x,__iptr))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/modf.h>
/* Break `value' into integral and fractional parts */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) double __NOTHROW_NCX(__LIBCCALL __modf)(double __x, double *__iptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(modf))(__x, __iptr); }
#endif /* ... */
#if __has_builtin(__builtin_expf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expf)
/* Exponential function of `x' */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_expf,float,__NOTHROW,__expf,(float __x),expf,{ return __builtin_expf(__x); })
#elif defined(__CRT_HAVE_expf)
/* Exponential function of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_expf,float,__NOTHROW,__expf,(float __x),expf,(__x))
#elif defined(__CRT_HAVE___expf)
/* Exponential function of `x' */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_expf,float,__NOTHROW,__expf,(float __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_exp) || defined(__CRT_HAVE___exp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/expf.h>
/* Exponential function of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_expf float __NOTHROW(__LIBCCALL __expf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_frexpf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_frexpf)
/* Break `value' into a normalized fraction and an integral power of 2 */
__CEIREDIRECT(__ATTR_NONNULL((2)),float,__NOTHROW_NCX,__frexpf,(float __x, int *__pexponent),frexpf,{ return __builtin_frexpf(__x, __pexponent); })
#elif defined(__CRT_HAVE_frexpf)
/* Break `value' into a normalized fraction and an integral power of 2 */
__CREDIRECT(__ATTR_NONNULL((2)),float,__NOTHROW_NCX,__frexpf,(float __x, int *__pexponent),frexpf,(__x,__pexponent))
#elif defined(__CRT_HAVE___frexpf)
/* Break `value' into a normalized fraction and an integral power of 2 */
__CDECLARE(__ATTR_NONNULL((2)),float,__NOTHROW_NCX,__frexpf,(float __x, int *__pexponent),(__x,__pexponent))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_frexp) || defined(__CRT_HAVE___frexp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/frexpf.h>
/* Break `value' into a normalized fraction and an integral power of 2 */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) float __NOTHROW_NCX(__LIBCCALL __frexpf)(float __x, int *__pexponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(frexpf))(__x, __pexponent); }
#endif /* ... */
#if __has_builtin(__builtin_ldexpf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ldexpf)
/* `x' times (two to the `exponent' power) */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__ldexpf,(float __x, int __exponent),ldexpf,{ return __builtin_ldexpf(__x, __exponent); })
#elif defined(__CRT_HAVE_ldexpf)
/* `x' times (two to the `exponent' power) */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__ldexpf,(float __x, int __exponent),ldexpf,(__x,__exponent))
#elif defined(__CRT_HAVE___ldexpf)
/* `x' times (two to the `exponent' power) */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__ldexpf,(float __x, int __exponent),(__x,__exponent))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_ldexp) || defined(__CRT_HAVE___ldexp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/ldexpf.h>
/* `x' times (two to the `exponent' power) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __ldexpf)(float __x, int __exponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ldexpf))(__x, __exponent); }
#endif /* ... */
#if __has_builtin(__builtin_logf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logf)
/* Natural logarithm of `x' */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_logf,float,__NOTHROW,__logf,(float __x),logf,{ return __builtin_logf(__x); })
#elif defined(__CRT_HAVE_logf)
/* Natural logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_logf,float,__NOTHROW,__logf,(float __x),logf,(__x))
#elif defined(__CRT_HAVE___logf)
/* Natural logarithm of `x' */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_logf,float,__NOTHROW,__logf,(float __x),(__x))
#elif defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log)
#include <libc/local/math/logf.h>
/* Natural logarithm of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_logf float __NOTHROW(__LIBCCALL __logf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_log10f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log10f)
/* Base-ten logarithm of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__log10f,(float __x),log10f,{ return __builtin_log10f(__x); })
#elif defined(__CRT_HAVE_log10f)
/* Base-ten logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__log10f,(float __x),log10f,(__x))
#elif defined(__CRT_HAVE___log10f)
/* Base-ten logarithm of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__log10f,(float __x),(__x))
#elif defined(__CRT_HAVE_log10) || defined(__CRT_HAVE___log10)
#include <libc/local/math/log10f.h>
/* Base-ten logarithm of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __log10f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log10f))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_modff) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_modff)
/* Break `value' into integral and fractional parts */
__CEIREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),float,__NOTHROW_NCX,__modff,(float __x, float *__iptr),modff,{ return __builtin_modff(__x, __iptr); })
#elif defined(__CRT_HAVE_modff)
/* Break `value' into integral and fractional parts */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),float,__NOTHROW_NCX,__modff,(float __x, float *__iptr),modff,(__x,__iptr))
#elif defined(__CRT_HAVE___modff)
/* Break `value' into integral and fractional parts */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),float,__NOTHROW_NCX,__modff,(float __x, float *__iptr),(__x,__iptr))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_modf) || defined(__CRT_HAVE___modf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/modff.h>
/* Break `value' into integral and fractional parts */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) float __NOTHROW_NCX(__LIBCCALL __modff)(float __x, float *__iptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(modff))(__x, __iptr); }
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_expl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expl)
/* Exponential function of `x' */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_expl,__LONGDOUBLE,__NOTHROW,__expl,(__LONGDOUBLE __x),expl,{ return __builtin_expl(__x); })
#elif defined(__CRT_HAVE_expl)
/* Exponential function of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_expl,__LONGDOUBLE,__NOTHROW,__expl,(__LONGDOUBLE __x),expl,(__x))
#elif defined(__CRT_HAVE___expl)
/* Exponential function of `x' */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_expl,__LONGDOUBLE,__NOTHROW,__expl,(__LONGDOUBLE __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_exp) || defined(__CRT_HAVE___exp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/expl.h>
/* Exponential function of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_expl __LONGDOUBLE __NOTHROW(__LIBCCALL __expl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_frexpl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_frexpl)
/* Break `value' into a normalized fraction and an integral power of 2 */
__CEIREDIRECT(__ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,__frexpl,(__LONGDOUBLE __x, int *__pexponent),frexpl,{ return __builtin_frexpl(__x, __pexponent); })
#elif defined(__CRT_HAVE_frexpl)
/* Break `value' into a normalized fraction and an integral power of 2 */
__CREDIRECT(__ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,__frexpl,(__LONGDOUBLE __x, int *__pexponent),frexpl,(__x,__pexponent))
#elif defined(__CRT_HAVE___frexpl)
/* Break `value' into a normalized fraction and an integral power of 2 */
__CDECLARE(__ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,__frexpl,(__LONGDOUBLE __x, int *__pexponent),(__x,__pexponent))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_frexp) || defined(__CRT_HAVE___frexp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/frexpl.h>
/* Break `value' into a normalized fraction and an integral power of 2 */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL __frexpl)(__LONGDOUBLE __x, int *__pexponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(frexpl))(__x, __pexponent); }
#endif /* ... */
#if __has_builtin(__builtin_ldexpl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ldexpl)
/* `x' times (two to the `exponent' power) */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__ldexpl,(__LONGDOUBLE __x, int __exponent),ldexpl,{ return __builtin_ldexpl(__x, __exponent); })
#elif defined(__CRT_HAVE_ldexpl)
/* `x' times (two to the `exponent' power) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__ldexpl,(__LONGDOUBLE __x, int __exponent),ldexpl,(__x,__exponent))
#elif defined(__CRT_HAVE___ldexpl)
/* `x' times (two to the `exponent' power) */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__ldexpl,(__LONGDOUBLE __x, int __exponent),(__x,__exponent))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_ldexp) || defined(__CRT_HAVE___ldexp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/ldexpl.h>
/* `x' times (two to the `exponent' power) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __ldexpl)(__LONGDOUBLE __x, int __exponent) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ldexpl))(__x, __exponent); }
#endif /* ... */
#if __has_builtin(__builtin_logl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logl)
/* Natural logarithm of `x' */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_logl,__LONGDOUBLE,__NOTHROW,__logl,(__LONGDOUBLE __x),logl,{ return __builtin_logl(__x); })
#elif defined(__CRT_HAVE_logl)
/* Natural logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_logl,__LONGDOUBLE,__NOTHROW,__logl,(__LONGDOUBLE __x),logl,(__x))
#elif defined(__CRT_HAVE___logl)
/* Natural logarithm of `x' */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_logl,__LONGDOUBLE,__NOTHROW,__logl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_log) || defined(__CRT_HAVE___log)
#include <libc/local/math/logl.h>
/* Natural logarithm of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_logl __LONGDOUBLE __NOTHROW(__LIBCCALL __logl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_log10l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log10l)
/* Base-ten logarithm of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__log10l,(__LONGDOUBLE __x),log10l,{ return __builtin_log10l(__x); })
#elif defined(__CRT_HAVE_log10l)
/* Base-ten logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__log10l,(__LONGDOUBLE __x),log10l,(__x))
#elif defined(__CRT_HAVE___log10l)
/* Base-ten logarithm of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__log10l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_log10) || defined(__CRT_HAVE___log10)
#include <libc/local/math/log10l.h>
/* Base-ten logarithm of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __log10l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log10l))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_modfl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_modfl)
/* Break `value' into integral and fractional parts */
__CEIREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,__modfl,(__LONGDOUBLE __x, __LONGDOUBLE *__iptr),modfl,{ return __builtin_modfl(__x, __iptr); })
#elif defined(__CRT_HAVE_modfl)
/* Break `value' into integral and fractional parts */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,__modfl,(__LONGDOUBLE __x, __LONGDOUBLE *__iptr),modfl,(__x,__iptr))
#elif defined(__CRT_HAVE___modfl)
/* Break `value' into integral and fractional parts */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),__LONGDOUBLE,__NOTHROW_NCX,__modfl,(__LONGDOUBLE __x, __LONGDOUBLE *__iptr),(__x,__iptr))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_modf) || defined(__CRT_HAVE___modf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/modfl.h>
/* Break `value' into integral and fractional parts */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL __modfl)(__LONGDOUBLE __x, __LONGDOUBLE *__iptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(modfl))(__x, __iptr); }
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#ifdef __USE_GNU
#if __has_builtin(__builtin_exp10) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp10)
/* A function missing in all standards: compute exponent to base ten */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__exp10,(double __x),exp10,{ return __builtin_exp10(__x); })
#elif defined(__CRT_HAVE_exp10)
/* A function missing in all standards: compute exponent to base ten */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__exp10,(double __x),exp10,(__x))
#elif defined(__CRT_HAVE___exp10)
/* A function missing in all standards: compute exponent to base ten */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__exp10,(double __x),(__x))
#endif /* ... */
#if __has_builtin(__builtin_pow10) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_pow10)
/* Another name occasionally used */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__pow10,(double __x),pow10,{ return __builtin_pow10(__x); })
#elif defined(__CRT_HAVE_pow10)
/* Another name occasionally used */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__pow10,(double __x),pow10,(__x))
#elif defined(__CRT_HAVE___pow10)
/* Another name occasionally used */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__pow10,(double __x),(__x))
#elif defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/pow10.h>
/* Another name occasionally used */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __pow10)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pow10))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_exp10f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp10f)
/* A function missing in all standards: compute exponent to base ten */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__exp10f,(float __x),exp10f,{ return __builtin_exp10f(__x); })
#elif defined(__CRT_HAVE_exp10f)
/* A function missing in all standards: compute exponent to base ten */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__exp10f,(float __x),exp10f,(__x))
#elif defined(__CRT_HAVE___exp10f)
/* A function missing in all standards: compute exponent to base ten */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__exp10f,(float __x),(__x))
#elif defined(__CRT_HAVE_exp10) || defined(__CRT_HAVE___exp10)
#include <libc/local/math/exp10f.h>
/* A function missing in all standards: compute exponent to base ten */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __exp10f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(exp10f))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_pow10f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_pow10f)
/* Another name occasionally used */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__pow10f,(float __x),pow10f,{ return __builtin_pow10f(__x); })
#elif defined(__CRT_HAVE_pow10f)
/* Another name occasionally used */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__pow10f,(float __x),pow10f,(__x))
#elif defined(__CRT_HAVE___pow10f)
/* Another name occasionally used */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__pow10f,(float __x),(__x))
#elif defined(__CRT_HAVE_powf) || defined(__CRT_HAVE___powf) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_pow10) || defined(__CRT_HAVE___pow10) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/pow10f.h>
/* Another name occasionally used */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __pow10f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pow10f))(__x); }
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_exp10l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp10l)
/* A function missing in all standards: compute exponent to base ten */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__exp10l,(__LONGDOUBLE __x),exp10l,{ return __builtin_exp10l(__x); })
#elif defined(__CRT_HAVE_exp10l)
/* A function missing in all standards: compute exponent to base ten */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__exp10l,(__LONGDOUBLE __x),exp10l,(__x))
#elif defined(__CRT_HAVE___exp10l)
/* A function missing in all standards: compute exponent to base ten */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__exp10l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_exp10) || defined(__CRT_HAVE___exp10)
#include <libc/local/math/exp10l.h>
/* A function missing in all standards: compute exponent to base ten */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __exp10l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(exp10l))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_pow10l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_pow10l)
/* Another name occasionally used */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__pow10l,(__LONGDOUBLE __x),pow10l,{ return __builtin_pow10l(__x); })
#elif defined(__CRT_HAVE_pow10l)
/* Another name occasionally used */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__pow10l,(__LONGDOUBLE __x),pow10l,(__x))
#elif defined(__CRT_HAVE___pow10l)
/* Another name occasionally used */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__pow10l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_powl) || defined(__CRT_HAVE___powl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_pow10) || defined(__CRT_HAVE___pow10) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/pow10l.h>
/* Another name occasionally used */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __pow10l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pow10l))(__x); }
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_GNU */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#if __has_builtin(__builtin_expm1) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expm1)
/* Return `exp(x) - 1' */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__expm1,(double __x),expm1,{ return __builtin_expm1(__x); })
#elif defined(__CRT_HAVE_expm1)
/* Return `exp(x) - 1' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__expm1,(double __x),expm1,(__x))
#elif defined(__CRT_HAVE___expm1)
/* Return `exp(x) - 1' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__expm1,(double __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/expm1.h>
/* Return `exp(x) - 1' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __expm1)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expm1))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_log1p) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log1p)
/* Return `log(1 + x)' */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__log1p,(double __x),log1p,{ return __builtin_log1p(__x); })
#elif defined(__CRT_HAVE_log1p)
/* Return `log(1 + x)' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__log1p,(double __x),log1p,(__x))
#elif defined(__CRT_HAVE___log1p)
/* Return `log(1 + x)' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__log1p,(double __x),(__x))
#endif /* ... */
#if __has_builtin(__builtin_logb) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logb)
/* Return the base 2 signed integral exponent of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__logb,(double __x),logb,{ return __builtin_logb(__x); })
#elif defined(__CRT_HAVE_logb)
/* Return the base 2 signed integral exponent of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__logb,(double __x),logb,(__x))
#elif defined(__CRT_HAVE___logb)
/* Return the base 2 signed integral exponent of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__logb,(double __x),(__x))
#elif defined(__CRT_HAVE__logb)
/* Return the base 2 signed integral exponent of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__logb,(double __x),_logb,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/logb.h>
/* Return the base 2 signed integral exponent of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __logb)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logb))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_expm1f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expm1f)
/* Return `exp(x) - 1' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__expm1f,(float __x),expm1f,{ return __builtin_expm1f(__x); })
#elif defined(__CRT_HAVE_expm1f)
/* Return `exp(x) - 1' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__expm1f,(float __x),expm1f,(__x))
#elif defined(__CRT_HAVE___expm1f)
/* Return `exp(x) - 1' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__expm1f,(float __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_expm1) || defined(__CRT_HAVE___expm1) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/expm1f.h>
/* Return `exp(x) - 1' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __expm1f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expm1f))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_log1pf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log1pf)
/* Return `log(1 + x)' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__log1pf,(float __x),log1pf,{ return __builtin_log1pf(__x); })
#elif defined(__CRT_HAVE_log1pf)
/* Return `log(1 + x)' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__log1pf,(float __x),log1pf,(__x))
#elif defined(__CRT_HAVE___log1pf)
/* Return `log(1 + x)' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__log1pf,(float __x),(__x))
#elif defined(__CRT_HAVE_log1p) || defined(__CRT_HAVE___log1p)
#include <libc/local/math/log1pf.h>
/* Return `log(1 + x)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __log1pf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log1pf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_logbf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logbf)
/* Return the base 2 signed integral exponent of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__logbf,(float __x),logbf,{ return __builtin_logbf(__x); })
#elif defined(__CRT_HAVE_logbf)
/* Return the base 2 signed integral exponent of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__logbf,(float __x),logbf,(__x))
#elif defined(__CRT_HAVE___logbf)
/* Return the base 2 signed integral exponent of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__logbf,(float __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_logb) || defined(__CRT_HAVE___logb) || defined(__CRT_HAVE__logb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/logbf.h>
/* Return the base 2 signed integral exponent of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __logbf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logbf))(__x); }
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_expm1l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_expm1l)
/* Return `exp(x) - 1' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__expm1l,(__LONGDOUBLE __x),expm1l,{ return __builtin_expm1l(__x); })
#elif defined(__CRT_HAVE_expm1l)
/* Return `exp(x) - 1' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__expm1l,(__LONGDOUBLE __x),expm1l,(__x))
#elif defined(__CRT_HAVE___expm1l)
/* Return `exp(x) - 1' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__expm1l,(__LONGDOUBLE __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_expm1) || defined(__CRT_HAVE___expm1) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/expm1l.h>
/* Return `exp(x) - 1' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __expm1l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(expm1l))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_log1pl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log1pl)
/* Return `log(1 + x)' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__log1pl,(__LONGDOUBLE __x),log1pl,{ return __builtin_log1pl(__x); })
#elif defined(__CRT_HAVE_log1pl)
/* Return `log(1 + x)' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__log1pl,(__LONGDOUBLE __x),log1pl,(__x))
#elif defined(__CRT_HAVE___log1pl)
/* Return `log(1 + x)' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__log1pl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_log1p) || defined(__CRT_HAVE___log1p)
#include <libc/local/math/log1pl.h>
/* Return `log(1 + x)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __log1pl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log1pl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_logbl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_logbl)
/* Return the base 2 signed integral exponent of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__logbl,(__LONGDOUBLE __x),logbl,{ return __builtin_logbl(__x); })
#elif defined(__CRT_HAVE_logbl)
/* Return the base 2 signed integral exponent of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__logbl,(__LONGDOUBLE __x),logbl,(__x))
#elif defined(__CRT_HAVE___logbl)
/* Return the base 2 signed integral exponent of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__logbl,(__LONGDOUBLE __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_logb) || defined(__CRT_HAVE___logb) || defined(__CRT_HAVE__logb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/logbl.h>
/* Return the base 2 signed integral exponent of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __logbl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(logbl))(__x); }
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

#ifdef __USE_ISOC99
#if __has_builtin(__builtin_exp2) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp2)
/* Compute base-2 exponential of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__exp2,(double __x),exp2,{ return __builtin_exp2(__x); })
#elif defined(__CRT_HAVE_exp2)
/* Compute base-2 exponential of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__exp2,(double __x),exp2,(__x))
#elif defined(__CRT_HAVE___exp2)
/* Compute base-2 exponential of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__exp2,(double __x),(__x))
#endif /* ... */
#if __has_builtin(__builtin_log2) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log2)
/* Compute base-2 logarithm of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__log2,(double __x),log2,{ return __builtin_log2(__x); })
#elif defined(__CRT_HAVE_log2)
/* Compute base-2 logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__log2,(double __x),log2,(__x))
#elif defined(__CRT_HAVE___log2)
/* Compute base-2 logarithm of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__log2,(double __x),(__x))
#endif /* ... */
#if __has_builtin(__builtin_exp2f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp2f)
/* Compute base-2 exponential of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__exp2f,(float __x),exp2f,{ return __builtin_exp2f(__x); })
#elif defined(__CRT_HAVE_exp2f)
/* Compute base-2 exponential of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__exp2f,(float __x),exp2f,(__x))
#elif defined(__CRT_HAVE___exp2f)
/* Compute base-2 exponential of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__exp2f,(float __x),(__x))
#elif defined(__CRT_HAVE_exp2) || defined(__CRT_HAVE___exp2)
#include <libc/local/math/exp2f.h>
/* Compute base-2 exponential of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __exp2f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(exp2f))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_log2f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log2f)
/* Compute base-2 logarithm of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__log2f,(float __x),log2f,{ return __builtin_log2f(__x); })
#elif defined(__CRT_HAVE_log2f)
/* Compute base-2 logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__log2f,(float __x),log2f,(__x))
#elif defined(__CRT_HAVE___log2f)
/* Compute base-2 logarithm of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__log2f,(float __x),(__x))
#elif defined(__CRT_HAVE_log2) || defined(__CRT_HAVE___log2)
#include <libc/local/math/log2f.h>
/* Compute base-2 logarithm of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __log2f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log2f))(__x); }
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_exp2l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_exp2l)
/* Compute base-2 exponential of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__exp2l,(__LONGDOUBLE __x),exp2l,{ return __builtin_exp2l(__x); })
#elif defined(__CRT_HAVE_exp2l)
/* Compute base-2 exponential of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__exp2l,(__LONGDOUBLE __x),exp2l,(__x))
#elif defined(__CRT_HAVE___exp2l)
/* Compute base-2 exponential of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__exp2l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_exp2) || defined(__CRT_HAVE___exp2)
#include <libc/local/math/exp2l.h>
/* Compute base-2 exponential of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __exp2l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(exp2l))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_log2l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_log2l)
/* Compute base-2 logarithm of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__log2l,(__LONGDOUBLE __x),log2l,{ return __builtin_log2l(__x); })
#elif defined(__CRT_HAVE_log2l)
/* Compute base-2 logarithm of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__log2l,(__LONGDOUBLE __x),log2l,(__x))
#elif defined(__CRT_HAVE___log2l)
/* Compute base-2 logarithm of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__log2l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_log2) || defined(__CRT_HAVE___log2)
#include <libc/local/math/log2l.h>
/* Compute base-2 logarithm of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __log2l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(log2l))(__x); }
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */
#if __has_builtin(__builtin_pow) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_pow)
/* Return `x' to the `y' power */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_pow,double,__NOTHROW,__pow,(double __x, double __y),pow,{ return __builtin_pow(__x, __y); })
#elif defined(__CRT_HAVE_pow)
/* Return `x' to the `y' power */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_pow,double,__NOTHROW,__pow,(double __x, double __y),pow,(__x,__y))
#elif defined(__CRT_HAVE___pow)
/* Return `x' to the `y' power */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_pow,double,__NOTHROW,__pow,(double __x, double __y),(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/pow.h>
/* Return `x' to the `y' power */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_pow double __NOTHROW(__LIBCCALL __pow)(double __x, double __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pow))(__x, __y); }
#endif /* ... */
#if __has_builtin(__builtin_sqrt) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sqrt)
/* Return the square root of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__sqrt,(double __x),sqrt,{ return __builtin_sqrt(__x); })
#elif defined(__CRT_HAVE_sqrt)
/* Return the square root of `x' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__sqrt,(double __x),sqrt,(__x))
#elif defined(__CRT_HAVE___sqrt)
/* Return the square root of `x' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__sqrt,(double __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/sqrt.h>
/* Return the square root of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __sqrt)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sqrt))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_powf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_powf)
/* Return `x' to the `y' power */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_powf,float,__NOTHROW,__powf,(float __x, float __y),powf,{ return __builtin_powf(__x, __y); })
#elif defined(__CRT_HAVE_powf)
/* Return `x' to the `y' power */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_powf,float,__NOTHROW,__powf,(float __x, float __y),powf,(__x,__y))
#elif defined(__CRT_HAVE___powf)
/* Return `x' to the `y' power */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_powf,float,__NOTHROW,__powf,(float __x, float __y),(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/powf.h>
/* Return `x' to the `y' power */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_powf float __NOTHROW(__LIBCCALL __powf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(powf))(__x, __y); }
#endif /* ... */
#if __has_builtin(__builtin_sqrtf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sqrtf)
/* Return the square root of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__sqrtf,(float __x),sqrtf,{ return __builtin_sqrtf(__x); })
#elif defined(__CRT_HAVE_sqrtf)
/* Return the square root of `x' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__sqrtf,(float __x),sqrtf,(__x))
#elif defined(__CRT_HAVE___sqrtf)
/* Return the square root of `x' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__sqrtf,(float __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/sqrtf.h>
/* Return the square root of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __sqrtf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sqrtf))(__x); }
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_powl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_powl)
/* Return `x' to the `y' power */
__CEIREDIRECT(__ATTR_WUNUSED __DECL_SIMD_powl,__LONGDOUBLE,__NOTHROW,__powl,(__LONGDOUBLE __x, __LONGDOUBLE __y),powl,{ return __builtin_powl(__x, __y); })
#elif defined(__CRT_HAVE_powl)
/* Return `x' to the `y' power */
__CREDIRECT(__ATTR_WUNUSED __DECL_SIMD_powl,__LONGDOUBLE,__NOTHROW,__powl,(__LONGDOUBLE __x, __LONGDOUBLE __y),powl,(__x,__y))
#elif defined(__CRT_HAVE___powl)
/* Return `x' to the `y' power */
__CDECLARE(__ATTR_WUNUSED __DECL_SIMD_powl,__LONGDOUBLE,__NOTHROW,__powl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/powl.h>
/* Return `x' to the `y' power */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __DECL_SIMD_powl __LONGDOUBLE __NOTHROW(__LIBCCALL __powl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(powl))(__x, __y); }
#endif /* ... */
#if __has_builtin(__builtin_sqrtl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sqrtl)
/* Return the square root of `x' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__sqrtl,(__LONGDOUBLE __x),sqrtl,{ return __builtin_sqrtl(__x); })
#elif defined(__CRT_HAVE_sqrtl)
/* Return the square root of `x' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__sqrtl,(__LONGDOUBLE __x),sqrtl,(__x))
#elif defined(__CRT_HAVE___sqrtl)
/* Return the square root of `x' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__sqrtl,(__LONGDOUBLE __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_sqrt) || defined(__CRT_HAVE___sqrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/sqrtl.h>
/* Return the square root of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __sqrtl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sqrtl))(__x); }
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
#if __has_builtin(__builtin_hypot) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_hypot)
/* Return `sqrt(x*x + y*y)' */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__hypot,(double __x, double __y),hypot,{ return __builtin_hypot(__x, __y); })
#elif defined(__CRT_HAVE_hypot)
/* Return `sqrt(x*x + y*y)' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__hypot,(double __x, double __y),hypot,(__x,__y))
#elif defined(__CRT_HAVE___hypot)
/* Return `sqrt(x*x + y*y)' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__hypot,(double __x, double __y),(__x,__y))
#endif /* ... */
#if __has_builtin(__builtin_hypotf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_hypotf)
/* Return `sqrt(x*x + y*y)' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__hypotf,(float __x, float __y),hypotf,{ return __builtin_hypotf(__x, __y); })
#elif defined(__CRT_HAVE_hypotf)
/* Return `sqrt(x*x + y*y)' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__hypotf,(float __x, float __y),hypotf,(__x,__y))
#elif defined(__CRT_HAVE___hypotf)
/* Return `sqrt(x*x + y*y)' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__hypotf,(float __x, float __y),(__x,__y))
#elif defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE___hypot)
#include <libc/local/math/hypotf.h>
/* Return `sqrt(x*x + y*y)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __hypotf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hypotf))(__x, __y); }
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_hypotl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_hypotl)
/* Return `sqrt(x*x + y*y)' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__hypotl,(__LONGDOUBLE __x, __LONGDOUBLE __y),hypotl,{ return __builtin_hypotl(__x, __y); })
#elif defined(__CRT_HAVE_hypotl)
/* Return `sqrt(x*x + y*y)' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__hypotl,(__LONGDOUBLE __x, __LONGDOUBLE __y),hypotl,(__x,__y))
#elif defined(__CRT_HAVE___hypotl)
/* Return `sqrt(x*x + y*y)' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__hypotl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__CRT_HAVE_hypot) || defined(__CRT_HAVE___hypot)
#include <libc/local/math/hypotl.h>
/* Return `sqrt(x*x + y*y)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __hypotl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(hypotl))(__x, __y); }
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN || __USE_ISOC99 */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#if __has_builtin(__builtin_cbrt) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cbrt)
/* Return the cube root of `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__cbrt,(double __x),cbrt,{ return __builtin_cbrt(__x); })
#elif defined(__CRT_HAVE_cbrt)
/* Return the cube root of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__cbrt,(double __x),cbrt,(__x))
#elif defined(__CRT_HAVE___cbrt)
/* Return the cube root of `x' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__cbrt,(double __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/cbrt.h>
/* Return the cube root of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __cbrt)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cbrt))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_cbrtf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cbrtf)
/* Return the cube root of `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__cbrtf,(float __x),cbrtf,{ return __builtin_cbrtf(__x); })
#elif defined(__CRT_HAVE_cbrtf)
/* Return the cube root of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__cbrtf,(float __x),cbrtf,(__x))
#elif defined(__CRT_HAVE___cbrtf)
/* Return the cube root of `x' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__cbrtf,(float __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_cbrt) || defined(__CRT_HAVE___cbrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/cbrtf.h>
/* Return the cube root of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __cbrtf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cbrtf))(__x); }
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_cbrtl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_cbrtl)
/* Return the cube root of `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__cbrtl,(__LONGDOUBLE __x),cbrtl,{ return __builtin_cbrtl(__x); })
#elif defined(__CRT_HAVE_cbrtl)
/* Return the cube root of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__cbrtl,(__LONGDOUBLE __x),cbrtl,(__x))
#elif defined(__CRT_HAVE___cbrtl)
/* Return the cube root of `x' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__cbrtl,(__LONGDOUBLE __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_cbrt) || defined(__CRT_HAVE___cbrt) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/cbrtl.h>
/* Return the cube root of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __cbrtl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cbrtl))(__x); }
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */
#if __has_builtin(__builtin_ceil) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ceil)
/* Smallest integral value not less than `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__ceil,(double __x),ceil,{ return __builtin_ceil(__x); })
#elif defined(__CRT_HAVE_ceil)
/* Smallest integral value not less than `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__ceil,(double __x),ceil,(__x))
#elif defined(__CRT_HAVE___ceil)
/* Smallest integral value not less than `x' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__ceil,(double __x),(__x))
#else /* ... */
#include <libc/local/math/ceil.h>
/* Smallest integral value not less than `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __ceil)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ceil))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_fabs) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabs)
/* Absolute value of `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fabs,(double __x),fabs,{ return __builtin_fabs(__x); })
#elif defined(__CRT_HAVE_fabs)
/* Absolute value of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fabs,(double __x),fabs,(__x))
#elif defined(__CRT_HAVE___fabs)
/* Absolute value of `x' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fabs,(double __x),(__x))
#else /* ... */
#include <libc/local/math/fabs.h>
/* Absolute value of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __fabs)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabs))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_floor) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_floor)
/* Largest integer not greater than `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__floor,(double __x),floor,{ return __builtin_floor(__x); })
#elif defined(__CRT_HAVE_floor)
/* Largest integer not greater than `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__floor,(double __x),floor,(__x))
#elif defined(__CRT_HAVE___floor)
/* Largest integer not greater than `x' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__floor,(double __x),(__x))
#else /* ... */
#include <libc/local/math/floor.h>
/* Largest integer not greater than `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __floor)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(floor))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_fmod) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmod)
/* Floating-point modulo remainder of `x / y' */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__fmod,(double __x, double __y),fmod,{ return __builtin_fmod(__x, __y); })
#elif defined(__CRT_HAVE_fmod)
/* Floating-point modulo remainder of `x / y' */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__fmod,(double __x, double __y),fmod,(__x,__y))
#elif defined(__CRT_HAVE___fmod)
/* Floating-point modulo remainder of `x / y' */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__fmod,(double __x, double __y),(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/fmod.h>
/* Floating-point modulo remainder of `x / y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __fmod)(double __x, double __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmod))(__x, __y); }
#endif /* ... */
#if __has_builtin(__builtin_isinf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinf)
/* Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isinf,(double __x),isinf,{ return __builtin_isinf(__x); })
#elif defined(__CRT_HAVE_isinf)
/* Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isinf,(double __x),isinf,(__x))
#elif defined(__CRT_HAVE___isinf)
/* Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isinf,(double __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL)
#include <libc/local/math/isinf.h>
/* Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __isinf)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isinf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_finite) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_finite)
/* Return nonzero if `value' is finite and not NaN */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__finite,(double __x),finite,{ return __builtin_finite(__x); })
#elif defined(__CRT_HAVE_finite)
/* Return nonzero if `value' is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__finite,(double __x),finite,(__x))
#elif defined(__CRT_HAVE___finite)
/* Return nonzero if `value' is finite and not NaN */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__finite,(double __x),(__x))
#elif defined(__CRT_HAVE__finite)
/* Return nonzero if `value' is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__finite,(double __x),_finite,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || ((defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__INFINITY) || defined(__HUGE_VAL)) && (defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan)))
#include <libc/local/math/finite.h>
/* Return nonzero if `value' is finite and not NaN */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __finite)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(finite))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_ceilf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ceilf)
/* Smallest integral value not less than `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__ceilf,(float __x),ceilf,{ return __builtin_ceilf(__x); })
#elif defined(__CRT_HAVE_ceilf)
/* Smallest integral value not less than `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__ceilf,(float __x),ceilf,(__x))
#elif defined(__CRT_HAVE___ceilf)
/* Smallest integral value not less than `x' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__ceilf,(float __x),(__x))
#else /* ... */
#include <libc/local/math/ceilf.h>
/* Smallest integral value not less than `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __ceilf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ceilf))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_fabsf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabsf)
/* Absolute value of `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fabsf,(float __x),fabsf,{ return __builtin_fabsf(__x); })
#elif defined(__CRT_HAVE_fabsf)
/* Absolute value of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fabsf,(float __x),fabsf,(__x))
#elif defined(__CRT_HAVE___fabsf)
/* Absolute value of `x' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fabsf,(float __x),(__x))
#else /* ... */
#include <libc/local/math/fabsf.h>
/* Absolute value of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __fabsf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabsf))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_floorf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_floorf)
/* Largest integer not greater than `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__floorf,(float __x),floorf,{ return __builtin_floorf(__x); })
#elif defined(__CRT_HAVE_floorf)
/* Largest integer not greater than `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__floorf,(float __x),floorf,(__x))
#elif defined(__CRT_HAVE___floorf)
/* Largest integer not greater than `x' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__floorf,(float __x),(__x))
#else /* ... */
#include <libc/local/math/floorf.h>
/* Largest integer not greater than `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __floorf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(floorf))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_fmodf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmodf)
/* Floating-point modulo remainder of `x / y' */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__fmodf,(float __x, float __y),fmodf,{ return __builtin_fmodf(__x, __y); })
#elif defined(__CRT_HAVE_fmodf)
/* Floating-point modulo remainder of `x / y' */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__fmodf,(float __x, float __y),fmodf,(__x,__y))
#elif defined(__CRT_HAVE___fmodf)
/* Floating-point modulo remainder of `x / y' */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__fmodf,(float __x, float __y),(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_fmod) || defined(__CRT_HAVE___fmod) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/fmodf.h>
/* Floating-point modulo remainder of `x / y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __fmodf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmodf))(__x, __y); }
#endif /* ... */
#if __has_builtin(__builtin_isinff) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinff)
/* Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isinff,(float __x),isinff,{ return __builtin_isinff(__x); })
#elif defined(__CRT_HAVE_isinff)
/* Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isinff,(float __x),isinff,(__x))
#elif defined(__CRT_HAVE___isinff)
/* Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isinff,(float __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__INFINITYF) || defined(__HUGE_VALF) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL)
#include <libc/local/math/isinff.h>
/* Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __isinff)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isinff))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_finitef) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_finitef)
/* Return nonzero if `value' is finite and not NaN */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__finitef,(float __x),finitef,{ return __builtin_finitef(__x); })
#elif defined(__CRT_HAVE_finitef)
/* Return nonzero if `value' is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__finitef,(float __x),finitef,(__x))
#elif defined(__CRT_HAVE___finitef)
/* Return nonzero if `value' is finite and not NaN */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__finitef,(float __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || ((defined(__CRT_HAVE_isinff) || defined(__CRT_HAVE___isinff) || defined(__INFINITYF) || defined(__HUGE_VALF) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__INFINITY) || defined(__HUGE_VAL)) && (defined(__CRT_HAVE_isnanf) || defined(__CRT_HAVE___isnanf) || defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan))) || defined(__CRT_HAVE_finite) || defined(__CRT_HAVE___finite) || defined(__CRT_HAVE__finite) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || ((defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__INFINITY) || defined(__HUGE_VAL)) && (defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan)))
#include <libc/local/math/finitef.h>
/* Return nonzero if `value' is finite and not NaN */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __finitef)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(finitef))(__x); }
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_ceill) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ceill)
/* Smallest integral value not less than `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__ceill,(__LONGDOUBLE __x),ceill,{ return __builtin_ceill(__x); })
#elif defined(__CRT_HAVE_ceill)
/* Smallest integral value not less than `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__ceill,(__LONGDOUBLE __x),ceill,(__x))
#elif defined(__CRT_HAVE___ceill)
/* Smallest integral value not less than `x' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__ceill,(__LONGDOUBLE __x),(__x))
#else /* ... */
#include <libc/local/math/ceill.h>
/* Smallest integral value not less than `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __ceill)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ceill))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_fabsl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fabsl)
/* Absolute value of `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fabsl,(__LONGDOUBLE __x),fabsl,{ return __builtin_fabsl(__x); })
#elif defined(__CRT_HAVE_fabsl)
/* Absolute value of `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fabsl,(__LONGDOUBLE __x),fabsl,(__x))
#elif defined(__CRT_HAVE___fabsl)
/* Absolute value of `x' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fabsl,(__LONGDOUBLE __x),(__x))
#else /* ... */
#include <libc/local/math/fabsl.h>
/* Absolute value of `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __fabsl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fabsl))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_floorl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_floorl)
/* Largest integer not greater than `x' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__floorl,(__LONGDOUBLE __x),floorl,{ return __builtin_floorl(__x); })
#elif defined(__CRT_HAVE_floorl)
/* Largest integer not greater than `x' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__floorl,(__LONGDOUBLE __x),floorl,(__x))
#elif defined(__CRT_HAVE___floorl)
/* Largest integer not greater than `x' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__floorl,(__LONGDOUBLE __x),(__x))
#else /* ... */
#include <libc/local/math/floorl.h>
/* Largest integer not greater than `x' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __floorl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(floorl))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_fmodl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmodl)
/* Floating-point modulo remainder of `x / y' */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fmodl,(__LONGDOUBLE __x, __LONGDOUBLE __y),fmodl,{ return __builtin_fmodl(__x, __y); })
#elif defined(__CRT_HAVE_fmodl)
/* Floating-point modulo remainder of `x / y' */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fmodl,(__LONGDOUBLE __x, __LONGDOUBLE __y),fmodl,(__x,__y))
#elif defined(__CRT_HAVE___fmodl)
/* Floating-point modulo remainder of `x / y' */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fmodl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_fmod) || defined(__CRT_HAVE___fmod) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/fmodl.h>
/* Floating-point modulo remainder of `x / y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __fmodl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmodl))(__x, __y); }
#endif /* ... */
#if __has_builtin(__builtin_isinfl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isinfl)
/* Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isinfl,(__LONGDOUBLE __x),isinfl,{ return __builtin_isinfl(__x); })
#elif defined(__CRT_HAVE_isinfl)
/* Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isinfl,(__LONGDOUBLE __x),isinfl,(__x))
#elif defined(__CRT_HAVE___isinfl)
/* Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isinfl,(__LONGDOUBLE __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__INFINITYL) || defined(__HUGE_VALL) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__INFINITY) || defined(__HUGE_VAL)
#include <libc/local/math/isinfl.h>
/* Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __isinfl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isinfl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_finitel) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_finitel)
/* Return nonzero if `value' is finite and not NaN */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__finitel,(__LONGDOUBLE __x),finitel,{ return __builtin_finitel(__x); })
#elif defined(__CRT_HAVE_finitel)
/* Return nonzero if `value' is finite and not NaN */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__finitel,(__LONGDOUBLE __x),finitel,(__x))
#elif defined(__CRT_HAVE___finitel)
/* Return nonzero if `value' is finite and not NaN */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__finitel,(__LONGDOUBLE __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || ((defined(__CRT_HAVE_isinfl) || defined(__CRT_HAVE___isinfl) || defined(__INFINITYL) || defined(__HUGE_VALL) || defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__INFINITY) || defined(__HUGE_VAL)) && (defined(__CRT_HAVE_isnanl) || defined(__CRT_HAVE___isnanl) || defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan))) || defined(__CRT_HAVE_finite) || defined(__CRT_HAVE___finite) || defined(__CRT_HAVE__finite) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || ((defined(__CRT_HAVE_isinf) || defined(__CRT_HAVE___isinf) || defined(__INFINITY) || defined(__HUGE_VAL)) && (defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan)))
#include <libc/local/math/finitel.h>
/* Return nonzero if `value' is finite and not NaN */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __finitel)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(finitel))(__x); }
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#ifdef __USE_MISC
#if __has_builtin(__builtin_remainder) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainder)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__drem,(double __x, double __p),remainder,{ return __builtin_remainder(__x, __p); })
#elif __has_builtin(__builtin_drem) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_drem)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__drem,(double __x, double __p),drem,{ return __builtin_drem(__x, __p); })
#elif defined(__CRT_HAVE_remainder)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__drem,(double __x, double __p),remainder,(__x,__p))
#elif defined(__CRT_HAVE_drem)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__drem,(double __x, double __p),drem,(__x,__p))
#elif defined(__CRT_HAVE___remainder)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__drem,(double __x, double __p),__remainder,(__x,__p))
#elif defined(__CRT_HAVE___drem)
/* Return the remainder of integer division `x / p' with infinite precision */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__drem,(double __x, double __p),(__x,__p))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/remainder.h>
/* Return the remainder of integer division `x / p' with infinite precision */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __drem)(double __x, double __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainder))(__x, __p); }
#endif /* ... */
#if __has_builtin(__builtin_significand) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_significand)
/* Return the fractional part of `x' after dividing out `ilogb(x)' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__significand,(double __x),significand,{ return __builtin_significand(__x); })
#elif defined(__CRT_HAVE_significand)
/* Return the fractional part of `x' after dividing out `ilogb(x)' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__significand,(double __x),significand,(__x))
#elif defined(__CRT_HAVE___significand)
/* Return the fractional part of `x' after dividing out `ilogb(x)' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__significand,(double __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/significand.h>
/* Return the fractional part of `x' after dividing out `ilogb(x)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __significand)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(significand))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_remainderf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainderf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__dremf,(float __x, float __p),remainderf,{ return __builtin_remainderf(__x, __p); })
#elif __has_builtin(__builtin_dremf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_dremf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__dremf,(float __x, float __p),dremf,{ return __builtin_dremf(__x, __p); })
#elif defined(__CRT_HAVE_remainderf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__dremf,(float __x, float __p),remainderf,(__x,__p))
#elif defined(__CRT_HAVE_dremf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__dremf,(float __x, float __p),dremf,(__x,__p))
#elif defined(__CRT_HAVE___remainderf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__dremf,(float __x, float __p),__remainderf,(__x,__p))
#elif defined(__CRT_HAVE___dremf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__dremf,(float __x, float __p),(__x,__p))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE___drem) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/remainderf.h>
/* Return the remainder of integer division `x / p' with infinite precision */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __dremf)(float __x, float __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainderf))(__x, __p); }
#endif /* ... */
#if __has_builtin(__builtin_significandf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_significandf)
/* Return the fractional part of `x' after dividing out `ilogb(x)' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__significandf,(float __x),significandf,{ return __builtin_significandf(__x); })
#elif defined(__CRT_HAVE_significandf)
/* Return the fractional part of `x' after dividing out `ilogb(x)' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__significandf,(float __x),significandf,(__x))
#elif defined(__CRT_HAVE___significandf)
/* Return the fractional part of `x' after dividing out `ilogb(x)' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__significandf,(float __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_significand) || defined(__CRT_HAVE___significand) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/significandf.h>
/* Return the fractional part of `x' after dividing out `ilogb(x)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __significandf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(significandf))(__x); }
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_remainderl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainderl)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__dreml,(__LONGDOUBLE __x, __LONGDOUBLE __p),remainderl,{ return __builtin_remainderl(__x, __p); })
#elif __has_builtin(__builtin_dreml) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_dreml)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__dreml,(__LONGDOUBLE __x, __LONGDOUBLE __p),dreml,{ return __builtin_dreml(__x, __p); })
#elif defined(__CRT_HAVE_remainderl)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__dreml,(__LONGDOUBLE __x, __LONGDOUBLE __p),remainderl,(__x,__p))
#elif defined(__CRT_HAVE_dreml)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__dreml,(__LONGDOUBLE __x, __LONGDOUBLE __p),dreml,(__x,__p))
#elif defined(__CRT_HAVE___remainderl)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__dreml,(__LONGDOUBLE __x, __LONGDOUBLE __p),__remainderl,(__x,__p))
#elif defined(__CRT_HAVE___dreml)
/* Return the remainder of integer division `x / p' with infinite precision */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__dreml,(__LONGDOUBLE __x, __LONGDOUBLE __p),(__x,__p))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE___drem) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/remainderl.h>
/* Return the remainder of integer division `x / p' with infinite precision */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __dreml)(__LONGDOUBLE __x, __LONGDOUBLE __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainderl))(__x, __p); }
#endif /* ... */
#if __has_builtin(__builtin_significandl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_significandl)
/* Return the fractional part of `x' after dividing out `ilogb(x)' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__significandl,(__LONGDOUBLE __x),significandl,{ return __builtin_significandl(__x); })
#elif defined(__CRT_HAVE_significandl)
/* Return the fractional part of `x' after dividing out `ilogb(x)' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__significandl,(__LONGDOUBLE __x),significandl,(__x))
#elif defined(__CRT_HAVE___significandl)
/* Return the fractional part of `x' after dividing out `ilogb(x)' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__significandl,(__LONGDOUBLE __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_significand) || defined(__CRT_HAVE___significand) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/significandl.h>
/* Return the fractional part of `x' after dividing out `ilogb(x)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __significandl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(significandl))(__x); }
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_MISC */

#ifdef __USE_ISOC99
#if __has_builtin(__builtin_copysign) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_copysign)
/* Return `x' with its signed changed to `y's */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__copysign,(double __num, double __sign),copysign,{ return __builtin_copysign(__num, __sign); })
#elif defined(__CRT_HAVE_copysign)
/* Return `x' with its signed changed to `y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__copysign,(double __num, double __sign),copysign,(__num,__sign))
#elif defined(__CRT_HAVE___copysign)
/* Return `x' with its signed changed to `y's */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__copysign,(double __num, double __sign),(__num,__sign))
#elif defined(__CRT_HAVE__copysign)
/* Return `x' with its signed changed to `y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__copysign,(double __num, double __sign),_copysign,(__num,__sign))
#else /* ... */
#include <libc/local/math/copysign.h>
/* Return `x' with its signed changed to `y's */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __copysign)(double __num, double __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(copysign))(__num, __sign); }
#endif /* !... */
#if __has_builtin(__builtin_nan) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nan)
/* Return representation of qNaN for double type */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nan,(char const *__tagb),nan,{ return __builtin_nan(__tagb); })
#elif defined(__CRT_HAVE_nan)
/* Return representation of qNaN for double type */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nan,(char const *__tagb),nan,(__tagb))
#elif defined(__CRT_HAVE___nan)
/* Return representation of qNaN for double type */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nan,(char const *__tagb),(__tagb))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/nan.h>
/* Return representation of qNaN for double type */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __nan)(char const *__tagb) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nan))(__tagb); }
#endif /* ... */
#if __has_builtin(__builtin_copysignf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_copysignf)
/* Return `x' with its signed changed to `y's */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__copysignf,(float __num, float __sign),copysignf,{ return __builtin_copysignf(__num, __sign); })
#elif defined(__CRT_HAVE_copysignf)
/* Return `x' with its signed changed to `y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__copysignf,(float __num, float __sign),copysignf,(__num,__sign))
#elif defined(__CRT_HAVE___copysignf)
/* Return `x' with its signed changed to `y's */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__copysignf,(float __num, float __sign),(__num,__sign))
#else /* ... */
#include <libc/local/math/copysignf.h>
/* Return `x' with its signed changed to `y's */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __copysignf)(float __num, float __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(copysignf))(__num, __sign); }
#endif /* !... */
#if __has_builtin(__builtin_nanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nanf)
/* Return representation of qNaN for double type */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nanf,(char const *__tagb),nanf,{ return __builtin_nanf(__tagb); })
#elif defined(__CRT_HAVE_nanf)
/* Return representation of qNaN for double type */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nanf,(char const *__tagb),nanf,(__tagb))
#elif defined(__CRT_HAVE___nanf)
/* Return representation of qNaN for double type */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nanf,(char const *__tagb),(__tagb))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_nan) || defined(__CRT_HAVE___nan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/nanf.h>
/* Return representation of qNaN for double type */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __nanf)(char const *__tagb) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nanf))(__tagb); }
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_copysignl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_copysignl)
/* Return `x' with its signed changed to `y's */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__copysignl,(__LONGDOUBLE __num, __LONGDOUBLE __sign),copysignl,{ return __builtin_copysignl(__num, __sign); })
#elif defined(__CRT_HAVE_copysignl)
/* Return `x' with its signed changed to `y's */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__copysignl,(__LONGDOUBLE __num, __LONGDOUBLE __sign),copysignl,(__num,__sign))
#elif defined(__CRT_HAVE___copysignl)
/* Return `x' with its signed changed to `y's */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__copysignl,(__LONGDOUBLE __num, __LONGDOUBLE __sign),(__num,__sign))
#else /* ... */
#include <libc/local/math/copysignl.h>
/* Return `x' with its signed changed to `y's */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __copysignl)(__LONGDOUBLE __num, __LONGDOUBLE __sign) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(copysignl))(__num, __sign); }
#endif /* !... */
#if __has_builtin(__builtin_nanl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nanl)
/* Return representation of qNaN for double type */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nanl,(char const *__tagb),nanl,{ return __builtin_nanl(__tagb); })
#elif defined(__CRT_HAVE_nanl)
/* Return representation of qNaN for double type */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nanl,(char const *__tagb),nanl,(__tagb))
#elif defined(__CRT_HAVE___nanl)
/* Return representation of qNaN for double type */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nanl,(char const *__tagb),(__tagb))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_nan) || defined(__CRT_HAVE___nan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/nanl.h>
/* Return representation of qNaN for double type */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __nanl)(char const *__tagb) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nanl))(__tagb); }
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */

#if __has_builtin(__builtin_isnan) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isnan)
/* Return nonzero if `value' is not a number */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isnan,(double __x),isnan,{ return __builtin_isnan(__x); })
#elif defined(__CRT_HAVE_isnan)
/* Return nonzero if `value' is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isnan,(double __x),isnan,(__x))
#elif defined(__CRT_HAVE__isnan)
/* Return nonzero if `value' is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isnan,(double __x),_isnan,(__x))
#elif defined(__CRT_HAVE___isnan)
/* Return nonzero if `value' is not a number */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isnan,(double __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/isnan.h>
/* Return nonzero if `value' is not a number */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __isnan)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isnan))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_isnanf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isnanf)
/* Return nonzero if `value' is not a number */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isnanf,(float __x),isnanf,{ return __builtin_isnanf(__x); })
#elif defined(__CRT_HAVE_isnanf)
/* Return nonzero if `value' is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isnanf,(float __x),isnanf,(__x))
#elif defined(__CRT_HAVE___isnanf)
/* Return nonzero if `value' is not a number */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isnanf,(float __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/isnanf.h>
/* Return nonzero if `value' is not a number */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __isnanf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isnanf))(__x); }
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_isnanl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isnanl)
/* Return nonzero if `value' is not a number */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isnanl,(__LONGDOUBLE __x),isnanl,{ return __builtin_isnanl(__x); })
#elif defined(__CRT_HAVE_isnanl)
/* Return nonzero if `value' is not a number */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isnanl,(__LONGDOUBLE __x),isnanl,(__x))
#elif defined(__CRT_HAVE___isnanl)
/* Return nonzero if `value' is not a number */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__isnanl,(__LONGDOUBLE __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_isnan) || defined(__CRT_HAVE__isnan) || defined(__CRT_HAVE___isnan) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/isnanl.h>
/* Return nonzero if `value' is not a number */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __isnanl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isnanl))(__x); }
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */

/* Bessel functions. */
#if defined(__USE_MISC) || defined(__USE_XOPEN)
#if __has_builtin(__builtin_j0) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_j0)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__j0,(double __x),j0,{ return __builtin_j0(__x); })
#elif defined(__CRT_HAVE_j0)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__j0,(double __x),j0,(__x))
#elif defined(__CRT_HAVE___j0)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__j0,(double __x),(__x))
#endif /* ... */
#if __has_builtin(__builtin_j1) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_j1)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__j1,(double __x),j1,{ return __builtin_j1(__x); })
#elif defined(__CRT_HAVE_j1)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__j1,(double __x),j1,(__x))
#elif defined(__CRT_HAVE___j1)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__j1,(double __x),(__x))
#endif /* ... */
#if __has_builtin(__builtin_jn) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_jn)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__jn,(int __n, double __x),jn,{ return __builtin_jn(__n, __x); })
#elif defined(__CRT_HAVE_jn)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__jn,(int __n, double __x),jn,(__n,__x))
#elif defined(__CRT_HAVE___jn)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__jn,(int __n, double __x),(__n,__x))
#endif /* ... */
#if __has_builtin(__builtin_y0) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_y0)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__y0,(double __x),y0,{ return __builtin_y0(__x); })
#elif defined(__CRT_HAVE_y0)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__y0,(double __x),y0,(__x))
#elif defined(__CRT_HAVE___y0)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__y0,(double __x),(__x))
#endif /* ... */
#if __has_builtin(__builtin_y1) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_y1)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__y1,(double __x),y1,{ return __builtin_y1(__x); })
#elif defined(__CRT_HAVE_y1)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__y1,(double __x),y1,(__x))
#elif defined(__CRT_HAVE___y1)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__y1,(double __x),(__x))
#endif /* ... */
#if __has_builtin(__builtin_yn) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_yn)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__yn,(int __n, double __x),yn,{ return __builtin_yn(__n, __x); })
#elif defined(__CRT_HAVE_yn)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__yn,(int __n, double __x),yn,(__n,__x))
#elif defined(__CRT_HAVE___yn)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__yn,(int __n, double __x),(__n,__x))
#endif /* ... */
#endif /* __USE_MISC || __USE_XOPEN */
#ifdef __USE_MISC
#if __has_builtin(__builtin_j0f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_j0f)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__j0f,(float __x),j0f,{ return __builtin_j0f(__x); })
#elif defined(__CRT_HAVE_j0f)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__j0f,(float __x),j0f,(__x))
#elif defined(__CRT_HAVE___j0f)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__j0f,(float __x),(__x))
#elif defined(__CRT_HAVE_j0) || defined(__CRT_HAVE___j0)
#include <libc/local/math/j0f.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __j0f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(j0f))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_j1f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_j1f)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__j1f,(float __x),j1f,{ return __builtin_j1f(__x); })
#elif defined(__CRT_HAVE_j1f)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__j1f,(float __x),j1f,(__x))
#elif defined(__CRT_HAVE___j1f)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__j1f,(float __x),(__x))
#elif defined(__CRT_HAVE_j1) || defined(__CRT_HAVE___j1)
#include <libc/local/math/j1f.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __j1f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(j1f))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_jnf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_jnf)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__jnf,(int __n, float __x),jnf,{ return __builtin_jnf(__n, __x); })
#elif defined(__CRT_HAVE_jnf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__jnf,(int __n, float __x),jnf,(__n,__x))
#elif defined(__CRT_HAVE___jnf)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__jnf,(int __n, float __x),(__n,__x))
#elif defined(__CRT_HAVE_jn) || defined(__CRT_HAVE___jn)
#include <libc/local/math/jnf.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __jnf)(int __n, float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(jnf))(__n, __x); }
#endif /* ... */
#if __has_builtin(__builtin_y0f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_y0f)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__y0f,(float __x),y0f,{ return __builtin_y0f(__x); })
#elif defined(__CRT_HAVE_y0f)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__y0f,(float __x),y0f,(__x))
#elif defined(__CRT_HAVE___y0f)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__y0f,(float __x),(__x))
#elif defined(__CRT_HAVE_y0) || defined(__CRT_HAVE___y0)
#include <libc/local/math/y0f.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __y0f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(y0f))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_y1f) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_y1f)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__y1f,(float __x),y1f,{ return __builtin_y1f(__x); })
#elif defined(__CRT_HAVE_y1f)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__y1f,(float __x),y1f,(__x))
#elif defined(__CRT_HAVE___y1f)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__y1f,(float __x),(__x))
#elif defined(__CRT_HAVE_y1) || defined(__CRT_HAVE___y1)
#include <libc/local/math/y1f.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __y1f)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(y1f))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_ynf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ynf)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__ynf,(int __n, float __x),ynf,{ return __builtin_ynf(__n, __x); })
#elif defined(__CRT_HAVE_ynf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__ynf,(int __n, float __x),ynf,(__n,__x))
#elif defined(__CRT_HAVE___ynf)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__ynf,(int __n, float __x),(__n,__x))
#elif defined(__CRT_HAVE_yn) || defined(__CRT_HAVE___yn)
#include <libc/local/math/ynf.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __ynf)(int __n, float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ynf))(__n, __x); }
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_j0l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_j0l)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__j0l,(__LONGDOUBLE __x),j0l,{ return __builtin_j0l(__x); })
#elif defined(__CRT_HAVE_j0l)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__j0l,(__LONGDOUBLE __x),j0l,(__x))
#elif defined(__CRT_HAVE___j0l)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__j0l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_j0) || defined(__CRT_HAVE___j0)
#include <libc/local/math/j0l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __j0l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(j0l))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_j1l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_j1l)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__j1l,(__LONGDOUBLE __x),j1l,{ return __builtin_j1l(__x); })
#elif defined(__CRT_HAVE_j1l)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__j1l,(__LONGDOUBLE __x),j1l,(__x))
#elif defined(__CRT_HAVE___j1l)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__j1l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_j1) || defined(__CRT_HAVE___j1)
#include <libc/local/math/j1l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __j1l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(j1l))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_jnl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_jnl)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__jnl,(int __n, __LONGDOUBLE __x),jnl,{ return __builtin_jnl(__n, __x); })
#elif defined(__CRT_HAVE_jnl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__jnl,(int __n, __LONGDOUBLE __x),jnl,(__n,__x))
#elif defined(__CRT_HAVE___jnl)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__jnl,(int __n, __LONGDOUBLE __x),(__n,__x))
#elif defined(__CRT_HAVE_jn) || defined(__CRT_HAVE___jn)
#include <libc/local/math/jnl.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __jnl)(int __n, __LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(jnl))(__n, __x); }
#endif /* ... */
#if __has_builtin(__builtin_y0l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_y0l)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__y0l,(__LONGDOUBLE __x),y0l,{ return __builtin_y0l(__x); })
#elif defined(__CRT_HAVE_y0l)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__y0l,(__LONGDOUBLE __x),y0l,(__x))
#elif defined(__CRT_HAVE___y0l)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__y0l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_y0) || defined(__CRT_HAVE___y0)
#include <libc/local/math/y0l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __y0l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(y0l))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_y1l) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_y1l)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__y1l,(__LONGDOUBLE __x),y1l,{ return __builtin_y1l(__x); })
#elif defined(__CRT_HAVE_y1l)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__y1l,(__LONGDOUBLE __x),y1l,(__x))
#elif defined(__CRT_HAVE___y1l)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__y1l,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_y1) || defined(__CRT_HAVE___y1)
#include <libc/local/math/y1l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __y1l)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(y1l))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_ynl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ynl)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__ynl,(int __n, __LONGDOUBLE __x),ynl,{ return __builtin_ynl(__n, __x); })
#elif defined(__CRT_HAVE_ynl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__ynl,(int __n, __LONGDOUBLE __x),ynl,(__n,__x))
#elif defined(__CRT_HAVE___ynl)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__ynl,(int __n, __LONGDOUBLE __x),(__n,__x))
#elif defined(__CRT_HAVE_yn) || defined(__CRT_HAVE___yn)
#include <libc/local/math/ynl.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __ynl)(int __n, __LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ynl))(__n, __x); }
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_MISC */

#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
#if __has_builtin(__builtin_erf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erf)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__erf,(double __x),erf,{ return __builtin_erf(__x); })
#elif defined(__CRT_HAVE_erf)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__erf,(double __x),erf,(__x))
#elif defined(__CRT_HAVE___erf)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__erf,(double __x),(__x))
#endif /* ... */
#if __has_builtin(__builtin_erfc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erfc)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__erfc,(double __x),erfc,{ return __builtin_erfc(__x); })
#elif defined(__CRT_HAVE_erfc)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__erfc,(double __x),erfc,(__x))
#elif defined(__CRT_HAVE___erfc)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__erfc,(double __x),(__x))
#endif /* ... */
#if __has_builtin(__builtin_lgamma) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgamma)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__lgamma,(double __x),lgamma,{ return __builtin_lgamma(__x); })
#elif __has_builtin(__builtin_gamma) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_gamma)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__lgamma,(double __x),gamma,{ return __builtin_gamma(__x); })
#elif defined(__CRT_HAVE_lgamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__lgamma,(double __x),lgamma,(__x))
#elif defined(__CRT_HAVE_gamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__lgamma,(double __x),gamma,(__x))
#elif defined(__CRT_HAVE___lgamma)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__lgamma,(double __x),(__x))
#elif defined(__CRT_HAVE___gamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__lgamma,(double __x),__gamma,(__x))
#endif /* ... */
#if __has_builtin(__builtin_erff) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erff)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__erff,(float __x),erff,{ return __builtin_erff(__x); })
#elif defined(__CRT_HAVE_erff)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__erff,(float __x),erff,(__x))
#elif defined(__CRT_HAVE___erff)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__erff,(float __x),(__x))
#elif defined(__CRT_HAVE_erf) || defined(__CRT_HAVE___erf)
#include <libc/local/math/erff.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __erff)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(erff))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_erfcf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erfcf)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__erfcf,(float __x),erfcf,{ return __builtin_erfcf(__x); })
#elif defined(__CRT_HAVE_erfcf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__erfcf,(float __x),erfcf,(__x))
#elif defined(__CRT_HAVE___erfcf)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__erfcf,(float __x),(__x))
#elif defined(__CRT_HAVE_erfc) || defined(__CRT_HAVE___erfc)
#include <libc/local/math/erfcf.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __erfcf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(erfcf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_lgammaf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgammaf)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__lgammaf,(float __x),lgammaf,{ return __builtin_lgammaf(__x); })
#elif __has_builtin(__builtin_gammaf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_gammaf)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__lgammaf,(float __x),gammaf,{ return __builtin_gammaf(__x); })
#elif defined(__CRT_HAVE_lgammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__lgammaf,(float __x),lgammaf,(__x))
#elif defined(__CRT_HAVE_gammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__lgammaf,(float __x),gammaf,(__x))
#elif defined(__CRT_HAVE___lgammaf)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__lgammaf,(float __x),(__x))
#elif defined(__CRT_HAVE___gammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__lgammaf,(float __x),__gammaf,(__x))
#elif defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE_gamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma)
#include <libc/local/math/lgammaf.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __lgammaf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammaf))(__x); }
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_erfl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erfl)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__erfl,(__LONGDOUBLE __x),erfl,{ return __builtin_erfl(__x); })
#elif defined(__CRT_HAVE_erfl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__erfl,(__LONGDOUBLE __x),erfl,(__x))
#elif defined(__CRT_HAVE___erfl)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__erfl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_erf) || defined(__CRT_HAVE___erf)
#include <libc/local/math/erfl.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __erfl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(erfl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_erfcl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_erfcl)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__erfcl,(__LONGDOUBLE __x),erfcl,{ return __builtin_erfcl(__x); })
#elif defined(__CRT_HAVE_erfcl)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__erfcl,(__LONGDOUBLE __x),erfcl,(__x))
#elif defined(__CRT_HAVE___erfcl)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__erfcl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_erfc) || defined(__CRT_HAVE___erfc)
#include <libc/local/math/erfcl.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __erfcl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(erfcl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_lgammal) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgammal)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__lgammal,(__LONGDOUBLE __x),lgammal,{ return __builtin_lgammal(__x); })
#elif __has_builtin(__builtin_gammal) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_gammal)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__lgammal,(__LONGDOUBLE __x),gammal,{ return __builtin_gammal(__x); })
#elif defined(__CRT_HAVE_lgammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__lgammal,(__LONGDOUBLE __x),lgammal,(__x))
#elif defined(__CRT_HAVE_gammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__lgammal,(__LONGDOUBLE __x),gammal,(__x))
#elif defined(__CRT_HAVE___lgammal)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__lgammal,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___gammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__lgammal,(__LONGDOUBLE __x),__gammal,(__x))
#elif defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE_gamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma)
#include <libc/local/math/lgammal.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __lgammal)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammal))(__x); }
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN || __USE_ISOC99 */

#ifdef __USE_ISOC99
#if __has_builtin(__builtin_tgamma) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tgamma)
/* True gamma function */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__tgamma,(double __x),tgamma,{ return __builtin_tgamma(__x); })
#elif defined(__CRT_HAVE_tgamma)
/* True gamma function */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__tgamma,(double __x),tgamma,(__x))
#elif defined(__CRT_HAVE___tgamma)
/* True gamma function */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__tgamma,(double __x),(__x))
#endif /* ... */
#if __has_builtin(__builtin_tgammaf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tgammaf)
/* True gamma function */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__tgammaf,(float __x),tgammaf,{ return __builtin_tgammaf(__x); })
#elif defined(__CRT_HAVE_tgammaf)
/* True gamma function */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__tgammaf,(float __x),tgammaf,(__x))
#elif defined(__CRT_HAVE___tgammaf)
/* True gamma function */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__tgammaf,(float __x),(__x))
#elif defined(__CRT_HAVE_tgamma) || defined(__CRT_HAVE___tgamma)
#include <libc/local/math/tgammaf.h>
/* True gamma function */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __tgammaf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tgammaf))(__x); }
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_tgammal) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tgammal)
/* True gamma function */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__tgammal,(__LONGDOUBLE __x),tgammal,{ return __builtin_tgammal(__x); })
#elif defined(__CRT_HAVE_tgammal)
/* True gamma function */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__tgammal,(__LONGDOUBLE __x),tgammal,(__x))
#elif defined(__CRT_HAVE___tgammal)
/* True gamma function */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__tgammal,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_tgamma) || defined(__CRT_HAVE___tgamma)
#include <libc/local/math/tgammal.h>
/* True gamma function */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __tgammal)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tgammal))(__x); }
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */

#if defined(__USE_MISC) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
#if __has_builtin(__builtin_lgamma) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgamma)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__gamma,(double __x),lgamma,{ return __builtin_lgamma(__x); })
#elif __has_builtin(__builtin_gamma) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_gamma)
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__gamma,(double __x),gamma,{ return __builtin_gamma(__x); })
#elif defined(__CRT_HAVE_lgamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__gamma,(double __x),lgamma,(__x))
#elif defined(__CRT_HAVE_gamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__gamma,(double __x),gamma,(__x))
#elif defined(__CRT_HAVE___lgamma)
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__gamma,(double __x),__lgamma,(__x))
#elif defined(__CRT_HAVE___gamma)
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__gamma,(double __x),(__x))
#endif /* ... */
#if __has_builtin(__builtin_lgammaf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgammaf)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__gammaf,(float __x),lgammaf,{ return __builtin_lgammaf(__x); })
#elif __has_builtin(__builtin_gammaf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_gammaf)
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__gammaf,(float __x),gammaf,{ return __builtin_gammaf(__x); })
#elif defined(__CRT_HAVE_lgammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__gammaf,(float __x),lgammaf,(__x))
#elif defined(__CRT_HAVE_gammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__gammaf,(float __x),gammaf,(__x))
#elif defined(__CRT_HAVE___lgammaf)
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__gammaf,(float __x),__lgammaf,(__x))
#elif defined(__CRT_HAVE___gammaf)
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__gammaf,(float __x),(__x))
#elif defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE_gamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma)
#include <libc/local/math/lgammaf.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __gammaf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammaf))(__x); }
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_lgammal) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgammal)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__gammal,(__LONGDOUBLE __x),lgammal,{ return __builtin_lgammal(__x); })
#elif __has_builtin(__builtin_gammal) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_gammal)
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__gammal,(__LONGDOUBLE __x),gammal,{ return __builtin_gammal(__x); })
#elif defined(__CRT_HAVE_lgammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__gammal,(__LONGDOUBLE __x),lgammal,(__x))
#elif defined(__CRT_HAVE_gammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__gammal,(__LONGDOUBLE __x),gammal,(__x))
#elif defined(__CRT_HAVE___lgammal)
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__gammal,(__LONGDOUBLE __x),__lgammal,(__x))
#elif defined(__CRT_HAVE___gammal)
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__gammal,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_lgamma) || defined(__CRT_HAVE_gamma) || defined(__CRT_HAVE___lgamma) || defined(__CRT_HAVE___gamma)
#include <libc/local/math/lgammal.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __gammal)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammal))(__x); }
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_MISC || (__USE_XOPEN && !__USE_XOPEN2K) */
#ifdef __USE_MISC
#if __has_builtin(__builtin_lgamma_r) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgamma_r)
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW_NCX,__lgamma_r,(double __x, int *__signgamp),lgamma_r,{ return __builtin_lgamma_r(__x, __signgamp); })
#elif defined(__CRT_HAVE_lgamma_r)
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW_NCX,__lgamma_r,(double __x, int *__signgamp),lgamma_r,(__x,__signgamp))
#elif defined(__CRT_HAVE___lgamma_r)
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW_NCX,__lgamma_r,(double __x, int *__signgamp),(__x,__signgamp))
#endif /* ... */
#if __has_builtin(__builtin_lgammaf_r) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgammaf_r)
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW_NCX,__lgammaf_r,(float __x, int *__signgamp),lgammaf_r,{ return __builtin_lgammaf_r(__x, __signgamp); })
#elif defined(__CRT_HAVE_lgammaf_r)
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW_NCX,__lgammaf_r,(float __x, int *__signgamp),lgammaf_r,(__x,__signgamp))
#elif defined(__CRT_HAVE___lgammaf_r)
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW_NCX,__lgammaf_r,(float __x, int *__signgamp),(__x,__signgamp))
#elif defined(__CRT_HAVE_lgamma_r) || defined(__CRT_HAVE___lgamma_r)
#include <libc/local/math/lgammaf_r.h>
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW_NCX(__LIBCCALL __lgammaf_r)(float __x, int *__signgamp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammaf_r))(__x, __signgamp); }
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_lgammal_r) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lgammal_r)
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW_NCX,__lgammal_r,(__LONGDOUBLE __x, int *__signgamp),lgammal_r,{ return __builtin_lgammal_r(__x, __signgamp); })
#elif defined(__CRT_HAVE_lgammal_r)
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW_NCX,__lgammal_r,(__LONGDOUBLE __x, int *__signgamp),lgammal_r,(__x,__signgamp))
#elif defined(__CRT_HAVE___lgammal_r)
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW_NCX,__lgammal_r,(__LONGDOUBLE __x, int *__signgamp),(__x,__signgamp))
#elif defined(__CRT_HAVE_lgamma_r) || defined(__CRT_HAVE___lgamma_r)
#include <libc/local/math/lgammal_r.h>
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL __lgammal_r)(__LONGDOUBLE __x, int *__signgamp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lgammal_r))(__x, __signgamp); }
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_MISC */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
#if __has_builtin(__builtin_rint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__rint,(double __x),rint,{ return __builtin_rint(__x); })
#elif __has_builtin(__builtin_nearbyint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nearbyint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__rint,(double __x),nearbyint,{ return __builtin_nearbyint(__x); })
#elif defined(__CRT_HAVE_rint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__rint,(double __x),rint,(__x))
#elif defined(__CRT_HAVE_nearbyint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__rint,(double __x),nearbyint,(__x))
#elif defined(__CRT_HAVE___rint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__rint,(double __x),(__x))
#elif defined(__CRT_HAVE___nearbyint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__rint,(double __x),__nearbyint,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/rint.h>
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __rint)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rint))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_nextafter) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nextafter)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nextafter,(double __x, double __y),nextafter,{ return __builtin_nextafter(__x, __y); })
#elif __has_builtin(__builtin_nexttoward) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nexttoward)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nextafter,(double __x, double __y),nexttoward,{ return __builtin_nexttoward(__x); })
#elif defined(__CRT_HAVE_nextafter)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nextafter,(double __x, double __y),nextafter,(__x,__y))
#elif defined(__CRT_HAVE_nexttoward)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nextafter,(double __x, double __y),nexttoward,(__x,__y))
#elif defined(__CRT_HAVE___nextafter)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nextafter,(double __x, double __y),(__x,__y))
#elif defined(__CRT_HAVE__nextafter)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nextafter,(double __x, double __y),_nextafter,(__x,__y))
#elif defined(__CRT_HAVE___nexttoward)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nextafter,(double __x, double __y),__nexttoward,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/nextafter.h>
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __nextafter)(double __x, double __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nextafter))(__x, __y); }
#endif /* ... */
#if __has_builtin(__builtin_remainder) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainder)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__remainder,(double __x, double __p),remainder,{ return __builtin_remainder(__x, __p); })
#elif __has_builtin(__builtin_drem) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_drem)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__remainder,(double __x, double __p),drem,{ return __builtin_drem(__x, __p); })
#elif defined(__CRT_HAVE_remainder)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__remainder,(double __x, double __p),remainder,(__x,__p))
#elif defined(__CRT_HAVE_drem)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__remainder,(double __x, double __p),drem,(__x,__p))
#elif defined(__CRT_HAVE___remainder)
/* Return the remainder of integer division `x / p' with infinite precision */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__remainder,(double __x, double __p),(__x,__p))
#elif defined(__CRT_HAVE___drem)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__remainder,(double __x, double __p),__drem,(__x,__p))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/remainder.h>
/* Return the remainder of integer division `x / p' with infinite precision */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __remainder)(double __x, double __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainder))(__x, __p); }
#endif /* ... */
#if __has_builtin(__builtin_ilogb) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ilogb)
/* Return the binary exponent of `x', which must be nonzero */
__CEIREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__ilogb,(double __x),ilogb,{ return __builtin_ilogb(__x); })
#elif defined(__CRT_HAVE_ilogb)
/* Return the binary exponent of `x', which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__ilogb,(double __x),ilogb,(__x))
#elif defined(__CRT_HAVE___ilogb)
/* Return the binary exponent of `x', which must be nonzero */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW,__ilogb,(double __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
#include <libc/local/math/ilogb.h>
/* Return the binary exponent of `x', which must be nonzero */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __ilogb)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ilogb))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_rintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__rintf,(float __x),rintf,{ return __builtin_rintf(__x); })
#elif __has_builtin(__builtin_nearbyintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nearbyintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__rintf,(float __x),nearbyintf,{ return __builtin_nearbyintf(__x); })
#elif defined(__CRT_HAVE_rintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__rintf,(float __x),rintf,(__x))
#elif defined(__CRT_HAVE_nearbyintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__rintf,(float __x),nearbyintf,(__x))
#elif defined(__CRT_HAVE___rintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__rintf,(float __x),(__x))
#elif defined(__CRT_HAVE___nearbyintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__rintf,(float __x),__nearbyintf,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE_nearbyint) || defined(__CRT_HAVE___rint) || defined(__CRT_HAVE___nearbyint) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/rintf.h>
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __rintf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rintf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_nextafterf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nextafterf)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nextafterf,(float __x, float __y),nextafterf,{ return __builtin_nextafterf(__x, __y); })
#elif __has_builtin(__builtin_nexttowardf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nexttowardf)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nextafterf,(float __x, float __y),nexttowardf,{ return __builtin_nexttowardf(__x); })
#elif defined(__CRT_HAVE_nextafterf)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nextafterf,(float __x, float __y),nextafterf,(__x,__y))
#elif defined(__CRT_HAVE_nexttowardf)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nextafterf,(float __x, float __y),nexttowardf,(__x,__y))
#elif defined(__CRT_HAVE___nextafterf)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nextafterf,(float __x, float __y),(__x,__y))
#elif defined(__CRT_HAVE___nexttowardf)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nextafterf,(float __x, float __y),__nexttowardf,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE___nexttoward) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/nextafterf.h>
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __nextafterf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nextafterf))(__x, __y); }
#endif /* ... */
#if __has_builtin(__builtin_remainderf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainderf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__remainderf,(float __x, float __p),remainderf,{ return __builtin_remainderf(__x, __p); })
#elif __has_builtin(__builtin_dremf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_dremf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__remainderf,(float __x, float __p),dremf,{ return __builtin_dremf(__x, __p); })
#elif defined(__CRT_HAVE_remainderf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__remainderf,(float __x, float __p),remainderf,(__x,__p))
#elif defined(__CRT_HAVE_dremf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__remainderf,(float __x, float __p),dremf,(__x,__p))
#elif defined(__CRT_HAVE___remainderf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__remainderf,(float __x, float __p),(__x,__p))
#elif defined(__CRT_HAVE___dremf)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__remainderf,(float __x, float __p),__dremf,(__x,__p))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE___drem) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/remainderf.h>
/* Return the remainder of integer division `x / p' with infinite precision */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __remainderf)(float __x, float __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainderf))(__x, __p); }
#endif /* ... */
#if __has_builtin(__builtin_ilogbf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ilogbf)
/* Return the binary exponent of `x', which must be nonzero */
__CEIREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__ilogbf,(float __x),ilogbf,{ return __builtin_ilogbf(__x); })
#elif defined(__CRT_HAVE_ilogbf)
/* Return the binary exponent of `x', which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__ilogbf,(float __x),ilogbf,(__x))
#elif defined(__CRT_HAVE___ilogbf)
/* Return the binary exponent of `x', which must be nonzero */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW,__ilogbf,(float __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_ilogb) || defined(__CRT_HAVE___ilogb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
#include <libc/local/math/ilogbf.h>
/* Return the binary exponent of `x', which must be nonzero */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __ilogbf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ilogbf))(__x); }
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_rintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__rintl,(__LONGDOUBLE __x),rintl,{ return __builtin_rintl(__x); })
#elif __has_builtin(__builtin_nearbyintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nearbyintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__rintl,(__LONGDOUBLE __x),nearbyintl,{ return __builtin_nearbyintl(__x); })
#elif defined(__CRT_HAVE_rintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__rintl,(__LONGDOUBLE __x),rintl,(__x))
#elif defined(__CRT_HAVE_nearbyintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__rintl,(__LONGDOUBLE __x),nearbyintl,(__x))
#elif defined(__CRT_HAVE___rintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__rintl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE___nearbyintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__rintl,(__LONGDOUBLE __x),__nearbyintl,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE_nearbyint) || defined(__CRT_HAVE___rint) || defined(__CRT_HAVE___nearbyint) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/rintl.h>
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __rintl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rintl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_nextafterl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nextafterl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),nextafterl,{ return __builtin_nextafterl(__x, __y); })
#elif __has_builtin(__builtin_nexttowardl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nexttowardl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),nexttowardl,{ return __builtin_nexttowardl(__x); })
#elif defined(__CRT_HAVE_nextafterl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),nextafterl,(__x,__y))
#elif defined(__CRT_HAVE_nexttowardl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),nexttowardl,(__x,__y))
#elif defined(__CRT_HAVE___nextafterl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__CRT_HAVE___nexttowardl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nextafterl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__nexttowardl,(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE___nexttoward) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/nextafterl.h>
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __nextafterl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nextafterl))(__x, __y); }
#endif /* ... */
#if __has_builtin(__builtin_remainderl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remainderl)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__remainderl,(__LONGDOUBLE __x, __LONGDOUBLE __p),remainderl,{ return __builtin_remainderl(__x, __p); })
#elif __has_builtin(__builtin_dreml) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_dreml)
/* Return the remainder of integer division `x / p' with infinite precision */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__remainderl,(__LONGDOUBLE __x, __LONGDOUBLE __p),dreml,{ return __builtin_dreml(__x, __p); })
#elif defined(__CRT_HAVE_remainderl)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__remainderl,(__LONGDOUBLE __x, __LONGDOUBLE __p),remainderl,(__x,__p))
#elif defined(__CRT_HAVE_dreml)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__remainderl,(__LONGDOUBLE __x, __LONGDOUBLE __p),dreml,(__x,__p))
#elif defined(__CRT_HAVE___remainderl)
/* Return the remainder of integer division `x / p' with infinite precision */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__remainderl,(__LONGDOUBLE __x, __LONGDOUBLE __p),(__x,__p))
#elif defined(__CRT_HAVE___dreml)
/* Return the remainder of integer division `x / p' with infinite precision */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__remainderl,(__LONGDOUBLE __x, __LONGDOUBLE __p),__dreml,(__x,__p))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_remainder) || defined(__CRT_HAVE_drem) || defined(__CRT_HAVE___remainder) || defined(__CRT_HAVE___drem) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/remainderl.h>
/* Return the remainder of integer division `x / p' with infinite precision */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __remainderl)(__LONGDOUBLE __x, __LONGDOUBLE __p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remainderl))(__x, __p); }
#endif /* ... */
#if __has_builtin(__builtin_ilogbl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ilogbl)
/* Return the binary exponent of `x', which must be nonzero */
__CEIREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__ilogbl,(__LONGDOUBLE __x),ilogbl,{ return __builtin_ilogbl(__x); })
#elif defined(__CRT_HAVE_ilogbl)
/* Return the binary exponent of `x', which must be nonzero */
__CREDIRECT(__ATTR_WUNUSED,int,__NOTHROW,__ilogbl,(__LONGDOUBLE __x),ilogbl,(__x))
#elif defined(__CRT_HAVE___ilogbl)
/* Return the binary exponent of `x', which must be nonzero */
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW,__ilogbl,(__LONGDOUBLE __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_ilogb) || defined(__CRT_HAVE___ilogb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)
#include <libc/local/math/ilogbl.h>
/* Return the binary exponent of `x', which must be nonzero */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __ilogbl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ilogbl))(__x); }
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

#ifdef __USE_ISOC99
#if __has_builtin(__builtin_nexttoward) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nexttoward)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nexttoward,(double __x, __LONGDOUBLE __y),nexttoward,{ return __builtin_nexttoward(__x, __y); })
#elif defined(__CRT_HAVE_nexttoward)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nexttoward,(double __x, __LONGDOUBLE __y),nexttoward,(__x,__y))
#elif defined(__CRT_HAVE___nexttoward)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nexttoward,(double __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__CRT_HAVE_nextafterl) || defined(__CRT_HAVE_nexttowardl) || defined(__CRT_HAVE___nextafterl) || defined(__CRT_HAVE___nexttowardl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/nexttoward.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __nexttoward)(double __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nexttoward))(__x, __y); }
#endif /* ... */
#if __has_builtin(__builtin_scalbn) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbn)
/* Return `x' times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__scalbn,(double __x, int __n),scalbn,{ return __builtin_scalbn(__x, __n); })
#elif defined(__CRT_HAVE_scalbn)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__scalbn,(double __x, int __n),scalbn,(__x,__n))
#elif defined(__CRT_HAVE___scalbn)
/* Return `x' times (2 to the Nth power) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__scalbn,(double __x, int __n),(__x,__n))
#elif defined(__CRT_HAVE_scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__scalbn,(double __x, int __n),scalbln,(__x,__n))
#elif defined(__CRT_HAVE___scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__scalbn,(double __x, int __n),__scalbln,(__x,__n))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/scalbn.h>
/* Return `x' times (2 to the Nth power) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __scalbn)(double __x, int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbn))(__x, __n); }
#endif /* ... */
#if __has_builtin(__builtin_scalbln) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbln)
/* Return `x' times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__scalbln,(double __x, long int __n),scalbln,{ return __builtin_scalbln(__x, __n); })
#elif defined(__CRT_HAVE_scalbln)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__scalbln,(double __x, long int __n),scalbln,(__x,__n))
#elif defined(__CRT_HAVE___scalbln)
/* Return `x' times (2 to the Nth power) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__scalbln,(double __x, long int __n),(__x,__n))
#elif defined(__CRT_HAVE_scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__scalbln,(double __x, long int __n),scalbn,(__x,__n))
#elif defined(__CRT_HAVE___scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__scalbln,(double __x, long int __n),__scalbn,(__x,__n))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/scalbln.h>
/* Return `x' times (2 to the Nth power) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __scalbln)(double __x, long int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbln))(__x, __n); }
#endif /* ... */
#if __has_builtin(__builtin_rint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nearbyint,(double __x),rint,{ return __builtin_rint(__x); })
#elif __has_builtin(__builtin_nearbyint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nearbyint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nearbyint,(double __x),nearbyint,{ return __builtin_nearbyint(__x); })
#elif defined(__CRT_HAVE_rint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nearbyint,(double __x),rint,(__x))
#elif defined(__CRT_HAVE_nearbyint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nearbyint,(double __x),nearbyint,(__x))
#elif defined(__CRT_HAVE___rint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nearbyint,(double __x),__rint,(__x))
#elif defined(__CRT_HAVE___nearbyint)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__nearbyint,(double __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/rint.h>
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __nearbyint)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rint))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_round) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_round)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__round,(double __x),round,{ return __builtin_round(__x); })
#elif defined(__CRT_HAVE_round)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__round,(double __x),round,(__x))
#elif defined(__CRT_HAVE___round)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__round,(double __x),(__x))
#else /* ... */
#include <libc/local/math/round.h>
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __round)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(round))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_trunc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_trunc)
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__trunc,(double __x),trunc,{ return __builtin_trunc(__x); })
#elif defined(__CRT_HAVE_trunc)
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__trunc,(double __x),trunc,(__x))
#elif defined(__CRT_HAVE___trunc)
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__trunc,(double __x),(__x))
#else /* ... */
#include <libc/local/math/trunc.h>
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __trunc)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(trunc))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_remquo) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remquo)
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__CEIREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),double,__NOTHROW,__remquo,(double __x, double __y, int *__pquo),remquo,{ return __builtin_remquo(__x, __y, __pquo); })
#elif defined(__CRT_HAVE_remquo)
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),double,__NOTHROW,__remquo,(double __x, double __y, int *__pquo),remquo,(__x,__y,__pquo))
#elif defined(__CRT_HAVE___remquo)
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3)),double,__NOTHROW,__remquo,(double __x, double __y, int *__pquo),(__x,__y,__pquo))
#endif /* ... */
#if __has_builtin(__builtin_lrint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lrint)
/* Round `x' to nearest integral value according to current rounding direction */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lrint,(double __x),lrint,{ return __builtin_lrint(__x); })
#elif defined(__CRT_HAVE_lrint)
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lrint,(double __x),lrint,(__x))
#elif defined(__CRT_HAVE___lrint)
/* Round `x' to nearest integral value according to current rounding direction */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lrint,(double __x),(__x))
#elif defined(__CRT_HAVE_llrint) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lrint,(double __x),llrint,(__x))
#else /* ... */
#include <libc/local/math/lrint.h>
/* Round `x' to nearest integral value according to current rounding direction */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL __lrint)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lrint))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_lround) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lround)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lround,(double __x),lround,{ return __builtin_lround(__x); })
#elif defined(__CRT_HAVE_lround)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lround,(double __x),lround,(__x))
#elif defined(__CRT_HAVE___lround)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lround,(double __x),(__x))
#elif defined(__CRT_HAVE_llround) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lround,(double __x),llround,(__x))
#else /* ... */
#include <libc/local/math/lround.h>
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL __lround)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lround))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_fdim) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fdim)
/* Return positive difference between `x' and `y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fdim,(double __x, double __y),fdim,{ return __builtin_fdim(__x, __y); })
#elif defined(__CRT_HAVE_fdim)
/* Return positive difference between `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fdim,(double __x, double __y),fdim,(__x,__y))
#elif defined(__CRT_HAVE___fdim)
/* Return positive difference between `x' and `y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fdim,(double __x, double __y),(__x,__y))
#else /* ... */
#include <libc/local/math/fdim.h>
/* Return positive difference between `x' and `y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __fdim)(double __x, double __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fdim))(__x, __y); }
#endif /* !... */
#if __has_builtin(__builtin_fmax) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmax)
/* Return maximum numeric value from `x' and `y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fmax,(double __x, double __y),fmax,{ return __builtin_fmax(__x, __y); })
#elif defined(__CRT_HAVE_fmax)
/* Return maximum numeric value from `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fmax,(double __x, double __y),fmax,(__x,__y))
#elif defined(__CRT_HAVE___fmax)
/* Return maximum numeric value from `x' and `y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fmax,(double __x, double __y),(__x,__y))
#else /* ... */
#include <libc/local/math/fmax.h>
/* Return maximum numeric value from `x' and `y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __fmax)(double __x, double __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmax))(__x, __y); }
#endif /* !... */
#if __has_builtin(__builtin_fmin) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmin)
/* Return minimum numeric value from `x' and `y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fmin,(double __x, double __y),fmin,{ return __builtin_fmin(__x, __y); })
#elif defined(__CRT_HAVE_fmin)
/* Return minimum numeric value from `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fmin,(double __x, double __y),fmin,(__x,__y))
#elif defined(__CRT_HAVE___fmin)
/* Return minimum numeric value from `x' and `y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fmin,(double __x, double __y),(__x,__y))
#else /* ... */
#include <libc/local/math/fmin.h>
/* Return minimum numeric value from `x' and `y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __fmin)(double __x, double __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmin))(__x, __y); }
#endif /* !... */
#if __has_builtin(__builtin_fma) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fma)
/* Multiply-add function computed as a ternary operation */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fma,(double __x, double __y, double __z),fma,{ return __builtin_fma(__x, __y, __z); })
#elif defined(__CRT_HAVE_fma)
/* Multiply-add function computed as a ternary operation */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fma,(double __x, double __y, double __z),fma,(__x,__y,__z))
#elif defined(__CRT_HAVE___fma)
/* Multiply-add function computed as a ternary operation */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,double,__NOTHROW,__fma,(double __x, double __y, double __z),(__x,__y,__z))
#else /* ... */
#include <libc/local/math/fma.h>
/* Multiply-add function computed as a ternary operation */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __fma)(double __x, double __y, double __z) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fma))(__x, __y, __z); }
#endif /* !... */
#if __has_builtin(__builtin_nexttowardf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nexttowardf)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nexttowardf,(float __x, __LONGDOUBLE __y),nexttowardf,{ return __builtin_nexttowardf(__x, __y); })
#elif defined(__CRT_HAVE_nexttowardf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nexttowardf,(float __x, __LONGDOUBLE __y),nexttowardf,(__x,__y))
#elif defined(__CRT_HAVE___nexttowardf)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nexttowardf,(float __x, __LONGDOUBLE __y),(__x,__y))
#elif ((defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)) && defined(__IEEE854_LONG_DOUBLE_TYPE__)) || defined(__CRT_HAVE_nextafterl) || defined(__CRT_HAVE_nexttowardl) || defined(__CRT_HAVE___nextafterl) || defined(__CRT_HAVE___nexttowardl) || defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE___nexttoward) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/nexttowardf.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __nexttowardf)(float __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nexttowardf))(__x, __y); }
#endif /* ... */
#if __has_builtin(__builtin_scalbnf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbnf)
/* Return `x' times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__scalbnf,(float __x, int __n),scalbnf,{ return __builtin_scalbnf(__x, __n); })
#elif defined(__CRT_HAVE_scalbnf)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__scalbnf,(float __x, int __n),scalbnf,(__x,__n))
#elif defined(__CRT_HAVE___scalbnf)
/* Return `x' times (2 to the Nth power) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__scalbnf,(float __x, int __n),(__x,__n))
#elif defined(__CRT_HAVE_scalblnf) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__scalbnf,(float __x, int __n),scalblnf,(__x,__n))
#elif defined(__CRT_HAVE___scalblnf) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__scalbnf,(float __x, int __n),__scalblnf,(__x,__n))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_scalbn) || defined(__CRT_HAVE___scalbn) || (defined(__CRT_HAVE_scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/scalbnf.h>
/* Return `x' times (2 to the Nth power) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __scalbnf)(float __x, int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbnf))(__x, __n); }
#endif /* ... */
#if __has_builtin(__builtin_scalblnf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalblnf)
/* Return `x' times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__scalblnf,(float __x, long int __n),scalblnf,{ return __builtin_scalblnf(__x, __n); })
#elif defined(__CRT_HAVE_scalblnf)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__scalblnf,(float __x, long int __n),scalblnf,(__x,__n))
#elif defined(__CRT_HAVE___scalblnf)
/* Return `x' times (2 to the Nth power) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__scalblnf,(float __x, long int __n),(__x,__n))
#elif defined(__CRT_HAVE_scalbnf) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__scalblnf,(float __x, long int __n),scalbnf,(__x,__n))
#elif defined(__CRT_HAVE___scalbnf) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__scalblnf,(float __x, long int __n),__scalbnf,(__x,__n))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_scalbln) || defined(__CRT_HAVE___scalbln) || (defined(__CRT_HAVE_scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/scalblnf.h>
/* Return `x' times (2 to the Nth power) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __scalblnf)(float __x, long int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalblnf))(__x, __n); }
#endif /* ... */
#if __has_builtin(__builtin_rintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nearbyintf,(float __x),rintf,{ return __builtin_rintf(__x); })
#elif __has_builtin(__builtin_nearbyintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nearbyintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nearbyintf,(float __x),nearbyintf,{ return __builtin_nearbyintf(__x); })
#elif defined(__CRT_HAVE_rintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nearbyintf,(float __x),rintf,(__x))
#elif defined(__CRT_HAVE_nearbyintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nearbyintf,(float __x),nearbyintf,(__x))
#elif defined(__CRT_HAVE___rintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nearbyintf,(float __x),__rintf,(__x))
#elif defined(__CRT_HAVE___nearbyintf)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__nearbyintf,(float __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE_nearbyint) || defined(__CRT_HAVE___rint) || defined(__CRT_HAVE___nearbyint) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/rintf.h>
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __nearbyintf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rintf))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_roundf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_roundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__roundf,(float __x),roundf,{ return __builtin_roundf(__x); })
#elif defined(__CRT_HAVE_roundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__roundf,(float __x),roundf,(__x))
#elif defined(__CRT_HAVE___roundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__roundf,(float __x),(__x))
#else /* ... */
#include <libc/local/math/roundf.h>
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __roundf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(roundf))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_truncf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_truncf)
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__truncf,(float __x),truncf,{ return __builtin_truncf(__x); })
#elif defined(__CRT_HAVE_truncf)
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__truncf,(float __x),truncf,(__x))
#elif defined(__CRT_HAVE___truncf)
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__truncf,(float __x),(__x))
#else /* ... */
#include <libc/local/math/truncf.h>
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __truncf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(truncf))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_remquof) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remquof)
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__CEIREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),float,__NOTHROW,__remquof,(float __x, float __y, int *__pquo),remquof,{ return __builtin_remquof(__x, __y, __pquo); })
#elif defined(__CRT_HAVE_remquof)
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),float,__NOTHROW,__remquof,(float __x, float __y, int *__pquo),remquof,(__x,__y,__pquo))
#elif defined(__CRT_HAVE___remquof)
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3)),float,__NOTHROW,__remquof,(float __x, float __y, int *__pquo),(__x,__y,__pquo))
#elif defined(__CRT_HAVE_remquo) || defined(__CRT_HAVE___remquo)
#include <libc/local/math/remquof.h>
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) float __NOTHROW(__LIBCCALL __remquof)(float __x, float __y, int *__pquo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remquof))(__x, __y, __pquo); }
#endif /* ... */
#if __has_builtin(__builtin_lrintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lrintf)
/* Round `x' to nearest integral value according to current rounding direction */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lrintf,(float __x),lrintf,{ return __builtin_lrintf(__x); })
#elif defined(__CRT_HAVE_lrintf)
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lrintf,(float __x),lrintf,(__x))
#elif defined(__CRT_HAVE___lrintf)
/* Round `x' to nearest integral value according to current rounding direction */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lrintf,(float __x),(__x))
#elif defined(__CRT_HAVE_llrintf) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lrintf,(float __x),llrintf,(__x))
#elif defined(__CRT_HAVE___llrintf) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lrintf,(float __x),__llrintf,(__x))
#else /* ... */
#include <libc/local/math/lrintf.h>
/* Round `x' to nearest integral value according to current rounding direction */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL __lrintf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lrintf))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_lroundf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lroundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lroundf,(float __x),lroundf,{ return __builtin_lroundf(__x); })
#elif defined(__CRT_HAVE_lroundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lroundf,(float __x),lroundf,(__x))
#elif defined(__CRT_HAVE___lroundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lroundf,(float __x),(__x))
#elif defined(__CRT_HAVE_llroundf) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lroundf,(float __x),llroundf,(__x))
#elif defined(__CRT_HAVE___llroundf) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lroundf,(float __x),__llroundf,(__x))
#else /* ... */
#include <libc/local/math/lroundf.h>
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL __lroundf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lroundf))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_fdimf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fdimf)
/* Return positive difference between `x' and `y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fdimf,(float __x, float __y),fdimf,{ return __builtin_fdimf(__x, __y); })
#elif defined(__CRT_HAVE_fdimf)
/* Return positive difference between `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fdimf,(float __x, float __y),fdimf,(__x,__y))
#elif defined(__CRT_HAVE___fdimf)
/* Return positive difference between `x' and `y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fdimf,(float __x, float __y),(__x,__y))
#else /* ... */
#include <libc/local/math/fdimf.h>
/* Return positive difference between `x' and `y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __fdimf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fdimf))(__x, __y); }
#endif /* !... */
#if __has_builtin(__builtin_fmaxf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmaxf)
/* Return maximum numeric value from `x' and `y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fmaxf,(float __x, float __y),fmaxf,{ return __builtin_fmaxf(__x, __y); })
#elif defined(__CRT_HAVE_fmaxf)
/* Return maximum numeric value from `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fmaxf,(float __x, float __y),fmaxf,(__x,__y))
#elif defined(__CRT_HAVE___fmaxf)
/* Return maximum numeric value from `x' and `y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fmaxf,(float __x, float __y),(__x,__y))
#else /* ... */
#include <libc/local/math/fmaxf.h>
/* Return maximum numeric value from `x' and `y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __fmaxf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmaxf))(__x, __y); }
#endif /* !... */
#if __has_builtin(__builtin_fminf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fminf)
/* Return minimum numeric value from `x' and `y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fminf,(float __x, float __y),fminf,{ return __builtin_fminf(__x, __y); })
#elif defined(__CRT_HAVE_fminf)
/* Return minimum numeric value from `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fminf,(float __x, float __y),fminf,(__x,__y))
#elif defined(__CRT_HAVE___fminf)
/* Return minimum numeric value from `x' and `y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fminf,(float __x, float __y),(__x,__y))
#else /* ... */
#include <libc/local/math/fminf.h>
/* Return minimum numeric value from `x' and `y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __fminf)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fminf))(__x, __y); }
#endif /* !... */
#if __has_builtin(__builtin_fmaf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmaf)
/* Multiply-add function computed as a ternary operation */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fmaf,(float __x, float __y, float __z),fmaf,{ return __builtin_fmaf(__x, __y, __z); })
#elif defined(__CRT_HAVE_fmaf)
/* Multiply-add function computed as a ternary operation */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fmaf,(float __x, float __y, float __z),fmaf,(__x,__y,__z))
#elif defined(__CRT_HAVE___fmaf)
/* Multiply-add function computed as a ternary operation */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,float,__NOTHROW,__fmaf,(float __x, float __y, float __z),(__x,__y,__z))
#else /* ... */
#include <libc/local/math/fmaf.h>
/* Multiply-add function computed as a ternary operation */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __fmaf)(float __x, float __y, float __z) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmaf))(__x, __y, __z); }
#endif /* !... */
#ifdef __COMPILER_HAVE_LONGLONG
#if __has_builtin(__builtin_llrint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llrint)
/* Round `x' to nearest integral value according to current rounding direction */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llrint,(double __x),llrint,{ return __builtin_llrint(__x); })
#elif defined(__CRT_HAVE_llrint)
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llrint,(double __x),llrint,(__x))
#elif defined(__CRT_HAVE___llrint)
/* Round `x' to nearest integral value according to current rounding direction */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llrint,(double __x),(__x))
#elif defined(__CRT_HAVE_lrint) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llrint,(double __x),lrint,(__x))
#else /* ... */
#include <libc/local/math/llrint.h>
/* Round `x' to nearest integral value according to current rounding direction */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL __llrint)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llrint))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_llround) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llround)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llround,(double __x),llround,{ return __builtin_llround(__x); })
#elif defined(__CRT_HAVE_llround)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llround,(double __x),llround,(__x))
#elif defined(__CRT_HAVE___llround)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llround,(double __x),(__x))
#elif defined(__CRT_HAVE_lround) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llround,(double __x),lround,(__x))
#else /* ... */
#include <libc/local/math/llround.h>
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL __llround)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llround))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_llrintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llrintf)
/* Round `x' to nearest integral value according to current rounding direction */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llrintf,(float __x),llrintf,{ return __builtin_llrintf(__x); })
#elif defined(__CRT_HAVE_llrintf)
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llrintf,(float __x),llrintf,(__x))
#elif defined(__CRT_HAVE___llrintf)
/* Round `x' to nearest integral value according to current rounding direction */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llrintf,(float __x),(__x))
#elif defined(__CRT_HAVE_lrintf) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llrintf,(float __x),lrintf,(__x))
#elif defined(__CRT_HAVE___lrintf) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llrintf,(float __x),__lrintf,(__x))
#else /* ... */
#include <libc/local/math/llrintf.h>
/* Round `x' to nearest integral value according to current rounding direction */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL __llrintf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llrintf))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_llroundf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llroundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llroundf,(float __x),llroundf,{ return __builtin_llroundf(__x); })
#elif defined(__CRT_HAVE_llroundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llroundf,(float __x),llroundf,(__x))
#elif defined(__CRT_HAVE___llroundf)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llroundf,(float __x),(__x))
#elif defined(__CRT_HAVE_lroundf) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llroundf,(float __x),lroundf,(__x))
#elif defined(__CRT_HAVE___lroundf) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llroundf,(float __x),__lroundf,(__x))
#else /* ... */
#include <libc/local/math/llroundf.h>
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL __llroundf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llroundf))(__x); }
#endif /* !... */
#endif /* __COMPILER_HAVE_LONGLONG */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_nextafterl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nextafterl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nexttowardl,(__LONGDOUBLE __x, __LONGDOUBLE __y),nextafterl,{ return __builtin_nextafterl(__x, __y); })
#elif __has_builtin(__builtin_nexttowardl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nexttowardl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nexttowardl,(__LONGDOUBLE __x, __LONGDOUBLE __y),nexttowardl,{ return __builtin_nexttowardl(__x); })
#elif defined(__CRT_HAVE_nextafterl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nexttowardl,(__LONGDOUBLE __x, __LONGDOUBLE __y),nextafterl,(__x,__y))
#elif defined(__CRT_HAVE_nexttowardl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nexttowardl,(__LONGDOUBLE __x, __LONGDOUBLE __y),nexttowardl,(__x,__y))
#elif defined(__CRT_HAVE___nextafterl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nexttowardl,(__LONGDOUBLE __x, __LONGDOUBLE __y),__nextafterl,(__x,__y))
#elif defined(__CRT_HAVE___nexttowardl)
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nexttowardl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_nextafter) || defined(__CRT_HAVE_nexttoward) || defined(__CRT_HAVE___nextafter) || defined(__CRT_HAVE__nextafter) || defined(__CRT_HAVE___nexttoward) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/nextafterl.h>
/* Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __nexttowardl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(nextafterl))(__x, __y); }
#endif /* ... */
#if __has_builtin(__builtin_scalbnl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbnl)
/* Return `x' times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalbnl,(__LONGDOUBLE __x, int __n),scalbnl,{ return __builtin_scalbnl(__x, __n); })
#elif defined(__CRT_HAVE_scalbnl)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalbnl,(__LONGDOUBLE __x, int __n),scalbnl,(__x,__n))
#elif defined(__CRT_HAVE___scalbnl)
/* Return `x' times (2 to the Nth power) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalbnl,(__LONGDOUBLE __x, int __n),(__x,__n))
#elif defined(__CRT_HAVE_scalblnl) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalbnl,(__LONGDOUBLE __x, int __n),scalblnl,(__x,__n))
#elif defined(__CRT_HAVE___scalblnl) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalbnl,(__LONGDOUBLE __x, int __n),__scalblnl,(__x,__n))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_scalbn) || defined(__CRT_HAVE___scalbn) || (defined(__CRT_HAVE_scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbln) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/scalbnl.h>
/* Return `x' times (2 to the Nth power) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __scalbnl)(__LONGDOUBLE __x, int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbnl))(__x, __n); }
#endif /* ... */
#if __has_builtin(__builtin_scalblnl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalblnl)
/* Return `x' times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalblnl,(__LONGDOUBLE __x, long int __n),scalblnl,{ return __builtin_scalblnl(__x, __n); })
#elif defined(__CRT_HAVE_scalblnl)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalblnl,(__LONGDOUBLE __x, long int __n),scalblnl,(__x,__n))
#elif defined(__CRT_HAVE___scalblnl)
/* Return `x' times (2 to the Nth power) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalblnl,(__LONGDOUBLE __x, long int __n),(__x,__n))
#elif defined(__CRT_HAVE_scalbnl) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalblnl,(__LONGDOUBLE __x, long int __n),scalbnl,(__x,__n))
#elif defined(__CRT_HAVE___scalbnl) && __SIZEOF_INT__ == __SIZEOF_LONG__
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalblnl,(__LONGDOUBLE __x, long int __n),__scalbnl,(__x,__n))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_scalbln) || defined(__CRT_HAVE___scalbln) || (defined(__CRT_HAVE_scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE___scalbn) && __SIZEOF_INT__ == __SIZEOF_LONG__) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/scalblnl.h>
/* Return `x' times (2 to the Nth power) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __scalblnl)(__LONGDOUBLE __x, long int __n) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalblnl))(__x, __n); }
#endif /* ... */
#if __has_builtin(__builtin_rintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_rintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nearbyintl,(__LONGDOUBLE __x),rintl,{ return __builtin_rintl(__x); })
#elif __has_builtin(__builtin_nearbyintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_nearbyintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nearbyintl,(__LONGDOUBLE __x),nearbyintl,{ return __builtin_nearbyintl(__x); })
#elif defined(__CRT_HAVE_rintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nearbyintl,(__LONGDOUBLE __x),rintl,(__x))
#elif defined(__CRT_HAVE_nearbyintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nearbyintl,(__LONGDOUBLE __x),nearbyintl,(__x))
#elif defined(__CRT_HAVE___rintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nearbyintl,(__LONGDOUBLE __x),__rintl,(__x))
#elif defined(__CRT_HAVE___nearbyintl)
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__nearbyintl,(__LONGDOUBLE __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_rint) || defined(__CRT_HAVE_nearbyint) || defined(__CRT_HAVE___rint) || defined(__CRT_HAVE___nearbyint) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/rintl.h>
/* Return the integer nearest `x' in the direction of the prevailing rounding mode */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __nearbyintl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rintl))(__x); }
#endif /* ... */
#if __has_builtin(__builtin_roundl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_roundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__roundl,(__LONGDOUBLE __x),roundl,{ return __builtin_roundl(__x); })
#elif defined(__CRT_HAVE_roundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__roundl,(__LONGDOUBLE __x),roundl,(__x))
#elif defined(__CRT_HAVE___roundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__roundl,(__LONGDOUBLE __x),(__x))
#else /* ... */
#include <libc/local/math/roundl.h>
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __roundl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(roundl))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_truncl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_truncl)
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__truncl,(__LONGDOUBLE __x),truncl,{ return __builtin_truncl(__x); })
#elif defined(__CRT_HAVE_truncl)
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__truncl,(__LONGDOUBLE __x),truncl,(__x))
#elif defined(__CRT_HAVE___truncl)
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__truncl,(__LONGDOUBLE __x),(__x))
#else /* ... */
#include <libc/local/math/truncl.h>
/* Round `x' to the integral value in floating-point
 * format   nearest  but  not  larger  in  magnitude */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __truncl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(truncl))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_remquol) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_remquol)
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__CEIREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),__LONGDOUBLE,__NOTHROW,__remquol,(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo),remquol,{ return __builtin_remquol(__x, __y, __pquo); })
#elif defined(__CRT_HAVE_remquol)
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((3)),__LONGDOUBLE,__NOTHROW,__remquol,(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo),remquol,(__x,__y,__pquo))
#elif defined(__CRT_HAVE___remquol)
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((3)),__LONGDOUBLE,__NOTHROW,__remquol,(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo),(__x,__y,__pquo))
#elif defined(__CRT_HAVE_remquo) || defined(__CRT_HAVE___remquo)
#include <libc/local/math/remquol.h>
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((3)) __LONGDOUBLE __NOTHROW(__LIBCCALL __remquol)(__LONGDOUBLE __x, __LONGDOUBLE __y, int *__pquo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(remquol))(__x, __y, __pquo); }
#endif /* ... */
#if __has_builtin(__builtin_lrintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lrintl)
/* Round `x' to nearest integral value according to current rounding direction */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lrintl,(__LONGDOUBLE __x),lrintl,{ return __builtin_lrintl(__x); })
#elif defined(__CRT_HAVE_lrintl)
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lrintl,(__LONGDOUBLE __x),lrintl,(__x))
#elif defined(__CRT_HAVE___lrintl)
/* Round `x' to nearest integral value according to current rounding direction */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lrintl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_llrintl) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lrintl,(__LONGDOUBLE __x),llrintl,(__x))
#elif defined(__CRT_HAVE___llrintl) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lrintl,(__LONGDOUBLE __x),__llrintl,(__x))
#else /* ... */
#include <libc/local/math/lrintl.h>
/* Round `x' to nearest integral value according to current rounding direction */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL __lrintl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lrintl))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_lroundl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_lroundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lroundl,(__LONGDOUBLE __x),lroundl,{ return __builtin_lroundl(__x); })
#elif defined(__CRT_HAVE_lroundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lroundl,(__LONGDOUBLE __x),lroundl,(__x))
#elif defined(__CRT_HAVE___lroundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lroundl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_llroundl) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lroundl,(__LONGDOUBLE __x),llroundl,(__x))
#elif defined(__CRT_HAVE___llroundl) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,long int,__NOTHROW,__lroundl,(__LONGDOUBLE __x),__llroundl,(__x))
#else /* ... */
#include <libc/local/math/lroundl.h>
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED long int __NOTHROW(__LIBCCALL __lroundl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lroundl))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_fdiml) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fdiml)
/* Return positive difference between `x' and `y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fdiml,(__LONGDOUBLE __x, __LONGDOUBLE __y),fdiml,{ return __builtin_fdiml(__x, __y); })
#elif defined(__CRT_HAVE_fdiml)
/* Return positive difference between `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fdiml,(__LONGDOUBLE __x, __LONGDOUBLE __y),fdiml,(__x,__y))
#elif defined(__CRT_HAVE___fdiml)
/* Return positive difference between `x' and `y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fdiml,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#else /* ... */
#include <libc/local/math/fdiml.h>
/* Return positive difference between `x' and `y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __fdiml)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fdiml))(__x, __y); }
#endif /* !... */
#if __has_builtin(__builtin_fmaxl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmaxl)
/* Return maximum numeric value from `x' and `y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fmaxl,(__LONGDOUBLE __x, __LONGDOUBLE __y),fmaxl,{ return __builtin_fmaxl(__x, __y); })
#elif defined(__CRT_HAVE_fmaxl)
/* Return maximum numeric value from `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fmaxl,(__LONGDOUBLE __x, __LONGDOUBLE __y),fmaxl,(__x,__y))
#elif defined(__CRT_HAVE___fmaxl)
/* Return maximum numeric value from `x' and `y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fmaxl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#else /* ... */
#include <libc/local/math/fmaxl.h>
/* Return maximum numeric value from `x' and `y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __fmaxl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmaxl))(__x, __y); }
#endif /* !... */
#if __has_builtin(__builtin_fminl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fminl)
/* Return minimum numeric value from `x' and `y' */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fminl,(__LONGDOUBLE __x, __LONGDOUBLE __y),fminl,{ return __builtin_fminl(__x, __y); })
#elif defined(__CRT_HAVE_fminl)
/* Return minimum numeric value from `x' and `y' */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fminl,(__LONGDOUBLE __x, __LONGDOUBLE __y),fminl,(__x,__y))
#elif defined(__CRT_HAVE___fminl)
/* Return minimum numeric value from `x' and `y' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fminl,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#else /* ... */
#include <libc/local/math/fminl.h>
/* Return minimum numeric value from `x' and `y' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __fminl)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fminl))(__x, __y); }
#endif /* !... */
#if __has_builtin(__builtin_fmal) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fmal)
/* Multiply-add function computed as a ternary operation */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fmal,(__LONGDOUBLE __x, __LONGDOUBLE __y, __LONGDOUBLE __z),fmal,{ return __builtin_fmal(__x, __y, __z); })
#elif defined(__CRT_HAVE_fmal)
/* Multiply-add function computed as a ternary operation */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fmal,(__LONGDOUBLE __x, __LONGDOUBLE __y, __LONGDOUBLE __z),fmal,(__x,__y,__z))
#elif defined(__CRT_HAVE___fmal)
/* Multiply-add function computed as a ternary operation */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__fmal,(__LONGDOUBLE __x, __LONGDOUBLE __y, __LONGDOUBLE __z),(__x,__y,__z))
#else /* ... */
#include <libc/local/math/fmal.h>
/* Multiply-add function computed as a ternary operation */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __fmal)(__LONGDOUBLE __x, __LONGDOUBLE __y, __LONGDOUBLE __z) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fmal))(__x, __y, __z); }
#endif /* !... */
#ifdef __COMPILER_HAVE_LONGLONG
#if __has_builtin(__builtin_llrintl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llrintl)
/* Round `x' to nearest integral value according to current rounding direction */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llrintl,(__LONGDOUBLE __x),llrintl,{ return __builtin_llrintl(__x); })
#elif defined(__CRT_HAVE_llrintl)
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llrintl,(__LONGDOUBLE __x),llrintl,(__x))
#elif defined(__CRT_HAVE___llrintl)
/* Round `x' to nearest integral value according to current rounding direction */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llrintl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_lrintl) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llrintl,(__LONGDOUBLE __x),lrintl,(__x))
#elif defined(__CRT_HAVE___lrintl) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value according to current rounding direction */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llrintl,(__LONGDOUBLE __x),__lrintl,(__x))
#else /* ... */
#include <libc/local/math/llrintl.h>
/* Round `x' to nearest integral value according to current rounding direction */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL __llrintl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llrintl))(__x); }
#endif /* !... */
#if __has_builtin(__builtin_llroundl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_llroundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llroundl,(__LONGDOUBLE __x),llroundl,{ return __builtin_llroundl(__x); })
#elif defined(__CRT_HAVE_llroundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llroundl,(__LONGDOUBLE __x),llroundl,(__x))
#elif defined(__CRT_HAVE___llroundl)
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llroundl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_lroundl) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llroundl,(__LONGDOUBLE __x),lroundl,(__x))
#elif defined(__CRT_HAVE___lroundl) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__LONGLONG,__NOTHROW,__llroundl,(__LONGDOUBLE __x),__lroundl,(__x))
#else /* ... */
#include <libc/local/math/llroundl.h>
/* Round `x' to nearest integral value, rounding halfway cases away from zero */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __LONGLONG __NOTHROW(__LIBCCALL __llroundl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(llroundl))(__x); }
#endif /* !... */
#endif /* __COMPILER_HAVE_LONGLONG */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */

#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8))
#if __has_builtin(__builtin_scalb) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalb)
/* Return `x' times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__scalb,(double __x, double __fn),scalb,{ return __builtin_scalb(__x, __fn); })
#elif defined(__CRT_HAVE_scalb)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__scalb,(double __x, double __fn),scalb,(__x,__fn))
#elif defined(__CRT_HAVE__scalb)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,double,__NOTHROW,__scalb,(double __x, double __fn),_scalb,(__x,__fn))
#elif defined(__CRT_HAVE___scalb)
/* Return `x' times (2 to the Nth power) */
__CDECLARE(__ATTR_WUNUSED,double,__NOTHROW,__scalb,(double __x, double __fn),(__x,__fn))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/scalb.h>
/* Return `x' times (2 to the Nth power) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED double __NOTHROW(__LIBCCALL __scalb)(double __x, double __fn) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalb))(__x, __fn); }
#endif /* ... */
#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K8) */
#ifdef __USE_MISC
#if __has_builtin(__builtin_scalbf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbf)
/* Return `x' times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__scalbf,(float __x, float __fn),scalbf,{ return __builtin_scalbf(__x, __fn); })
#elif defined(__CRT_HAVE_scalbf)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__scalbf,(float __x, float __fn),scalbf,(__x,__fn))
#elif defined(__CRT_HAVE__scalbf)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,float,__NOTHROW,__scalbf,(float __x, float __fn),_scalbf,(__x,__fn))
#elif defined(__CRT_HAVE___scalbf)
/* Return `x' times (2 to the Nth power) */
__CDECLARE(__ATTR_WUNUSED,float,__NOTHROW,__scalbf,(float __x, float __fn),(__x,__fn))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_scalb) || defined(__CRT_HAVE__scalb) || defined(__CRT_HAVE___scalb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/scalbf.h>
/* Return `x' times (2 to the Nth power) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED float __NOTHROW(__LIBCCALL __scalbf)(float __x, float __fn) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbf))(__x, __fn); }
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if __has_builtin(__builtin_scalbl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_scalbl)
/* Return `x' times (2 to the Nth power) */
__CEIREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalbl,(__LONGDOUBLE __x, __LONGDOUBLE __fn),scalbl,{ return __builtin_scalbl(__x, __fn); })
#elif defined(__CRT_HAVE_scalbl)
/* Return `x' times (2 to the Nth power) */
__CREDIRECT(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalbl,(__LONGDOUBLE __x, __LONGDOUBLE __fn),scalbl,(__x,__fn))
#elif defined(__CRT_HAVE___scalbl)
/* Return `x' times (2 to the Nth power) */
__CDECLARE(__ATTR_WUNUSED,__LONGDOUBLE,__NOTHROW,__scalbl,(__LONGDOUBLE __x, __LONGDOUBLE __fn),(__x,__fn))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_scalb) || defined(__CRT_HAVE__scalb) || defined(__CRT_HAVE___scalb) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/scalbl.h>
/* Return `x' times (2 to the Nth power) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __LONGDOUBLE __NOTHROW(__LIBCCALL __scalbl)(__LONGDOUBLE __x, __LONGDOUBLE __fn) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(scalbl))(__x, __fn); }
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_MISC */
#endif /* GLIBc aliases */


/* Floating point classification */
#ifdef __USE_ISOC99
#ifdef __CRT_HAVE___fpclassify
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__fpclassify,(double __x),(__x))
#elif defined(__CRT_HAVE_fpclassify)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__fpclassify,(double __x),fpclassify,(__x))
#elif defined(__CRT_HAVE__dclass)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__fpclassify,(double __x),_dclass,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/__fpclassify.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__fpclassify, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __fpclassify)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__fpclassify))(__x); })
#endif /* ... */
#ifdef __CRT_HAVE___signbit
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__signbit,(double __x),(__x))
#elif defined(__CRT_HAVE__dsign)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__signbit,(double __x),_dsign,(__x))
#else /* ... */
#include <libc/local/math/__signbit.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__signbit, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __signbit)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__signbit))(__x); })
#endif /* !... */
#ifdef __CRT_HAVE___fpclassifyf
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__fpclassifyf,(float __x),(__x))
#elif defined(__CRT_HAVE_fpclassifyf)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__fpclassifyf,(float __x),fpclassifyf,(__x))
#elif defined(__CRT_HAVE__fdclass)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__fpclassifyf,(float __x),_fdclass,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE___fpclassify) || defined(__CRT_HAVE_fpclassify) || defined(__CRT_HAVE__dclass) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/__fpclassifyf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__fpclassifyf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __fpclassifyf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__fpclassifyf))(__x); })
#endif /* ... */
#ifdef __CRT_HAVE___signbitf
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__signbitf,(float __x),(__x))
#elif defined(__CRT_HAVE__fdsign)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__signbitf,(float __x),_fdsign,(__x))
#else /* ... */
#include <libc/local/math/__signbitf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__signbitf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __signbitf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__signbitf))(__x); })
#endif /* !... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifdef __CRT_HAVE___fpclassifyl
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__fpclassifyl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE_fpclassifyl)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__fpclassifyl,(__LONGDOUBLE __x),fpclassifyl,(__x))
#elif defined(__CRT_HAVE__ldclass)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__fpclassifyl,(__LONGDOUBLE __x),_ldclass,(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE___fpclassify) || defined(__CRT_HAVE_fpclassify) || defined(__CRT_HAVE__dclass) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/__fpclassifyl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__fpclassifyl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __fpclassifyl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__fpclassifyl))(__x); })
#endif /* ... */
#ifdef __CRT_HAVE___signbitl
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__signbitl,(__LONGDOUBLE __x),(__x))
#elif defined(__CRT_HAVE__ldsign)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__signbitl,(__LONGDOUBLE __x),_ldsign,(__x))
#else /* ... */
#include <libc/local/math/__signbitl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__signbitl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __signbitl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__signbitl))(__x); })
#endif /* !... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_ISOC99 */

#ifdef __USE_GNU
#ifdef __CRT_HAVE_issignaling
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__issignaling,(double __x),issignaling,(__x))
#elif defined(__CRT_HAVE___issignaling)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__issignaling,(double __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/__issignaling.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__issignaling, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __issignaling)(double __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__issignaling))(__x); })
#endif /* ... */
#ifdef __CRT_HAVE_issignalingf
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__issignalingf,(float __x),issignalingf,(__x))
#elif defined(__CRT_HAVE___issignalingf)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__issignalingf,(float __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__) || defined(__CRT_HAVE_issignaling) || defined(__CRT_HAVE___issignaling) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/__issignalingf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__issignalingf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __issignalingf)(float __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__issignalingf))(__x); })
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifdef __CRT_HAVE_issignalingl
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__issignalingl,(__LONGDOUBLE __x),issignalingl,(__x))
#elif defined(__CRT_HAVE___issignalingl)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__issignalingl,(__LONGDOUBLE __x),(__x))
#elif defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__CRT_HAVE_issignaling) || defined(__CRT_HAVE___issignaling) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#include <libc/local/math/__issignalingl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(__issignalingl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __issignalingl)(__LONGDOUBLE __x) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__issignalingl))(__x); })
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* __USE_GNU */
#ifdef __CRT_HAVE__dpcomp
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__dos_dpcomp,(double __x, double __y),_dpcomp,(__x,__y))
#endif /* __CRT_HAVE__dpcomp */
#ifdef __CRT_HAVE__fdpcomp
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__dos_fdpcomp,(float __x, float __y),_fdpcomp,(__x,__y))
#elif defined(__CRT_HAVE__dpcomp)
#include <libc/local/math/_fdpcomp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL __dos_fdpcomp)(float __x, float __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fdpcomp))(__x, __y); }
#endif /* ... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifdef __CRT_HAVE__ldpcomp
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__dos_ldpcomp,(__LONGDOUBLE __x, __LONGDOUBLE __y),_ldpcomp,(__x,__y))
#elif defined(__CRT_HAVE__dpcomp)
#include <libc/local/math/_ldpcomp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL __dos_ldpcomp)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ldpcomp))(__x, __y); }
#endif /* ... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */


#if defined(__USE_MISC) || defined(__USE_XOPEN)
/* This variable is used by `gamma' and `lgamma'. */
#ifdef __CRT_HAVE_signgam
#undef signgam
__LIBC int signgam;
#endif /* __CRT_HAVE_signgam */
#endif /* __USE_MISC || __USE_XOPEN */

#ifdef __COMPILER_HAVE_C11_GENERIC
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __FPFUNC(x, f, d, l)      _Generic(x, float: f(x), double: d(x), default: l(x))
#define __FPFUNC2(x, y, f, d, l)  _Generic((x) + (y), float: f(x, y), double: d(x, y), default: l(x, y))
#else /* __COMPILER_HAVE_LONGDOUBLE */
#define __FPFUNC(x, f, d, l)      _Generic(x, float: f(x), default: d(x))
#define __FPFUNC2(x, y, f, d, l)  _Generic((x) + (y), float: f(x, y), default: d(x, y))
#endif /* !__COMPILER_HAVE_LONGDOUBLE */
#elif (!defined(__NO_builtin_choose_expr) &&        \
       !defined(__NO_builtin_types_compatible_p) && \
       defined(__COMPILER_HAVE_TYPEOF))
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __FPFUNC(x, f, d, l)                                                                     \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (float)0), float), f(x), \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (double)0), double), d(x), l(x)))
#define __FPFUNC2(x, y, f, d, l)                                                                          \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (y) + (float)0), float), f(x, y), \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (y) + (double)0), double), d(x, y), l(x, y)))
#else /* __COMPILER_HAVE_LONGDOUBLE */
#define __FPFUNC(x, f, d, l) \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (float)0), float), f(x), d(x))
#define __FPFUNC2(x, y, f, d, l) \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (y) + (float)0), float), f(x, y), d(x, y))
#endif /* !__COMPILER_HAVE_LONGDOUBLE */
#elif !defined(__NO_builtin_types_compatible_p) && defined(__COMPILER_HAVE_TYPEOF)
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __FPFUNC(x, f, d, l)                                             \
	(__builtin_types_compatible_p(__typeof__((x) + (float)0), float)     \
	 ? f((float)(x))                                                     \
	 : __builtin_types_compatible_p(__typeof__((x) + (double)0), double) \
	   ? d((double)(x))                                                  \
	   : l((__LONGDOUBLE)(x)))
#define __FPFUNC2(x, y, f, d, l)                                               \
	(__builtin_types_compatible_p(__typeof__((x) + (y) + (float)0), float)     \
	 ? f((float)(x), (float)(y))                                               \
	 : __builtin_types_compatible_p(__typeof__((x) + (y) + (double)0), double) \
	   ? d((double)(x), (double)(y))                                           \
	   : l((__LONGDOUBLE)(x), (__LONGDOUBLE)(y)))
#else /* __COMPILER_HAVE_LONGDOUBLE */
#define __FPFUNC(x, f, d, l) \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (float)0), float), f(x), d(x))
#define __FPFUNC2(x, y, f, d, l) \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (y) + (float)0), float), f(x, y), d(x, y))
#endif /* !__COMPILER_HAVE_LONGDOUBLE */
#elif defined(__COMPILER_HAVE_LONGDOUBLE)
#define __FPFUNC(x, f, d, l)                     \
	(sizeof((x) + (float)0) == sizeof(float)     \
	 ? f((float)(x))                             \
	 : sizeof((x) + (double)0) == sizeof(double) \
	   ? d((double)(x))                          \
	   : l((__LONGDOUBLE)(x)))
#define __FPFUNC2(x, y, f, d, l)                       \
	(sizeof((x) + (y) + (float)0) == sizeof(float)     \
	 ? f((float)(x), (float)(y))                       \
	 : sizeof((x) + (y) + (double)0) == sizeof(double) \
	   ? d((double)(x), (double)(y))                   \
	   : l((__LONGDOUBLE)(x), (__LONGDOUBLE)(y)))
#else /* ... */
#define __FPFUNC(x, f, d, l)                 \
	(sizeof((x) + (float)0) == sizeof(float) \
	 ? f((float)(x))                         \
	 : d((double)(x)))
#define __FPFUNC2(x, y, f, d, l)                   \
	(sizeof((x) + (y) + (float)0) == sizeof(float) \
	 ? f((float)(x), (float)(y))                   \
	 : d((double)(x), (double)(y)))
#endif /* ... */

#ifdef __USE_ISOC99
/*
 * float_t:    float-type at least as wide  as `float'; used to eval  `float'-expressions
 * double_t:   float-type at least as wide as `double'; used to eval `double'-expressions
 *
 * FLT_EVAL_METHOD:
 *    0:    `float_t' <=> `float',       `double_t' <=> `double'
 *    1:    `float_t' <=> `double',      `double_t' <=> `double'
 *    2:    `float_t' <=> `long double', `double_t' <=> `long double'
 *    else: Mapping of `float_t' and `double_t' is unspecified
 */
#if (defined(__FP_NAN) || defined(__FP_INFINITE) ||   \
     defined(__FP_ZERO) || defined(__FP_SUBNORMAL) || \
     defined(__FP_NORMAL))
/* Categories for floating-point numbers. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __FP_NAN
	FP_NAN = __FP_NAN, /* ... */
#endif /* __FP_NAN */
#ifdef __FP_INFINITE
	FP_INFINITE = __FP_INFINITE, /* ... */
#endif /* __FP_INFINITE */
#ifdef __FP_ZERO
	FP_ZERO = __FP_ZERO, /* ... */
#endif /* __FP_ZERO */
#ifdef __FP_SUBNORMAL
	FP_SUBNORMAL = __FP_SUBNORMAL, /* ... */
#endif /* __FP_SUBNORMAL */
#ifdef __FP_NORMAL
	FP_NORMAL = __FP_NORMAL /* ... */
#endif /* __FP_NORMAL */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __FP_NAN
#define FP_NAN       FP_NAN       /* ... */
#endif /* __FP_NAN */
#ifdef __FP_INFINITE
#define FP_INFINITE  FP_INFINITE  /* ... */
#endif /* __FP_INFINITE */
#ifdef __FP_ZERO
#define FP_ZERO      FP_ZERO      /* ... */
#endif /* __FP_ZERO */
#ifdef __FP_SUBNORMAL
#define FP_SUBNORMAL FP_SUBNORMAL /* ... */
#endif /* __FP_SUBNORMAL */
#ifdef __FP_NORMAL
#define FP_NORMAL    FP_NORMAL    /* ... */
#endif /* __FP_NORMAL */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __FP_NAN
#define FP_NAN       __FP_NAN       /* ... */
#endif /* __FP_NAN */
#ifdef __FP_INFINITE
#define FP_INFINITE  __FP_INFINITE  /* ... */
#endif /* __FP_INFINITE */
#ifdef __FP_ZERO
#define FP_ZERO      __FP_ZERO      /* ... */
#endif /* __FP_ZERO */
#ifdef __FP_SUBNORMAL
#define FP_SUBNORMAL __FP_SUBNORMAL /* ... */
#endif /* __FP_SUBNORMAL */
#ifdef __FP_NORMAL
#define FP_NORMAL    __FP_NORMAL    /* ... */
#endif /* __FP_NORMAL */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */

/* Figure out defaults for `float_t' and `double_t' if those
 * haven't  already  been defined  by `<bits/crt/mathdef.h>' */
#if !defined(__float_t) || !defined(__double_t)
#if (defined(__FLT_EVAL_METHOD__) && (__FLT_EVAL_METHOD__ + 0) == 2)
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __float_t  __LONGDOUBLE
#define __double_t __LONGDOUBLE
#else /* __COMPILER_HAVE_LONGDOUBLE */
#define __float_t  double
#define __double_t double
#endif /* !__COMPILER_HAVE_LONGDOUBLE */
#elif (defined(__FLT_EVAL_METHOD__) && (__FLT_EVAL_METHOD__ + 0) == 1)
#define __float_t  double
#define __double_t double
#else /* __FLT_EVAL_METHOD__ == ... */
#define __float_t  float
#define __double_t double
#endif /* __FLT_EVAL_METHOD__ != ... */
#endif /* !__float_t || !__double_t */

/* `float' expressions are evaluated as this. */
typedef __float_t float_t;

/* `double' expressions are evaluated as this. */
typedef __double_t double_t;


#ifndef __OPTIMIZE_SIZE__
#if __has_builtin(__builtin_signbitf) && __has_builtin(__builtin_signbit) && __has_builtin(__builtin_signbitl)
#define signbit(x) __FPFUNC(x, __builtin_signbitf, __builtin_signbit, __builtin_signbitl)
#endif /* __builtin_signbitf && __builtin_signbit && __builtin_signbitl */
#ifndef __SUPPORT_SNAN__
#if (__has_builtin(__builtin_fpclassify) &&             \
     defined(__FP_NAN) && defined(__FP_INFINITE) &&     \
     defined(__FP_NORMAL) && defined(__FP_SUBNORMAL) && \
     defined(__FP_ZERO))
#define fpclassify(x) __builtin_fpclassify(__FP_NAN, __FP_INFINITE, __FP_NORMAL, __FP_SUBNORMAL, __FP_ZERO, x)
#endif /* __builtin_fpclassify && defined(__FP_...) */
#if __has_builtin(__builtin_isfinite)
#define isfinite(x) __builtin_isfinite(x)
#endif /* __builtin_isfinite */
#if __has_builtin(__builtin_isnormal)
#define isnormal(x) __builtin_isnormal(x)
#endif /* __builtin_isnormal */
#if __has_builtin(__builtin_isnan)
#define isnan(x) __builtin_isnan(x)
#endif /* __builtin_isnan */
#if __has_builtin(__builtin_isinf_sign)
#define isinf(x) __builtin_isinf_sign(x)
#endif /* __builtin_isinf_sign */
#endif /* !__SUPPORT_SNAN__ */
#endif /* !__OPTIMIZE_SIZE__ */

#ifndef fpclassify
#define fpclassify(x) __FPFUNC(x, __fpclassifyf, __fpclassify, __fpclassifyl)
#endif /* !fpclassify */

#ifndef signbit
#define signbit(x) __FPFUNC(x, __signbitf, __signbit, __signbitl)
#endif /* !signbit */

#ifndef isnormal
#ifdef fpclassify
#ifdef __FP_NORMAL
#define isnormal(x) (fpclassify(x) == __FP_NORMAL)
#endif /* __FP_NORMAL */
#endif /* fpclassify */
#endif /* !isnormal */

#ifndef isfinite
#define isfinite(x) __FPFUNC(x, __finitef, __finite, __finitel)
#endif /* !isfinite */

#ifndef isnan
#define isnan(x) __FPFUNC(x, __isnanf, __isnan, __isnanl)
#endif /* !isnan */

#ifndef isinf
#define isinf(x) __FPFUNC(x, __isinff, __isinf, __isinfl)
#endif /* !isinf */


#ifdef __USE_ISOC99
#if __has_builtin(__builtin_isunordered) && \
   (!defined(__DOS_COMPAT__) || !defined(__OPTIMIZE_SIZE__))
#define isunordered(u, v)    __builtin_isunordered(u, v)
#define isgreater(x, y)      __builtin_isgreater(x, y)
#define isgreaterequal(x, y) __builtin_isgreaterequal(x, y)
#define isless(x, y)         __builtin_isless(x, y)
#define islessequal(x, y)    __builtin_islessequal(x, y)
#define islessgreater(x, y)  __builtin_islessgreater(x, y)
#elif defined(__CRT_HAVE__dpcomp)
#define __DOS_FPCOMPARE(x, y) __FPFUNC2(x, y, __dos_fdpcomp, __dos_dpcomp, __dos_ldpcomp)
#define isgreater(x, y)      ((__DOS_FPCOMPARE(x, y)&4) != 0)
#define isgreaterequal(x, y) ((__DOS_FPCOMPARE(x, y)&6) != 0)
#define isless(x, y)         ((__DOS_FPCOMPARE(x, y)&1) != 0)
#define islessequal(x, y)    ((__DOS_FPCOMPARE(x, y)&3) != 0)
#define islessgreater(x, y)  ((__DOS_FPCOMPARE(x, y)&5) != 0)
#define isunordered(x, y)    (__DOS_FPCOMPARE(x, y) == 0)
#endif /* ... */


/* Generic... */
#ifndef isunordered
#if defined(fpclassify) && defined(__FP_NAN)
#define isunordered(u, v) (fpclassify(u) == __FP_NAN || fpclassify(v) == __FP_NAN)
#else /* fpclassify && __FP_NAN */
#define isunordered(u, v) 0
#endif /* !fpclassify || !__FP_NAN */
#endif /* !isunordered */

#ifndef isgreater
#if defined(__NO_XBLOCK) || !defined(__COMPILER_HAVE_TYPEOF)
#define isgreater(x, y) (!isunordered(x, y) && (x) > (y))
#else /* __NO_XBLOCK || !__COMPILER_HAVE_TYPEOF */
#define isgreater(x, y) __XBLOCK({ __typeof__(x) __isg_x = (x); __typeof__(y) __isg_y = (y); __XRETURN !isunordered(__isg_x, __isg_y) && __isg_x > __isg_y; })
#endif /* !__NO_XBLOCK && __COMPILER_HAVE_TYPEOF */
#endif /* !isgreater */

#ifndef isgreaterequal
#if defined(__NO_XBLOCK) || !defined(__COMPILER_HAVE_TYPEOF)
#define isgreaterequal(x, y) (!isunordered(x, y) && (x) >= (y))
#else /* __NO_XBLOCK || !__COMPILER_HAVE_TYPEOF */
#define isgreaterequal(x, y) __XBLOCK({ __typeof__(x) __isge_x = (x); __typeof__(y) __isge_y = (y); __XRETURN !isunordered(__isge_x, __isge_y) && __isge_x >= __isge_y; })
#endif /* !__NO_XBLOCK && __COMPILER_HAVE_TYPEOF */
#endif /* !isgreaterequal */

#ifndef isless
#if defined(__NO_XBLOCK) || !defined(__COMPILER_HAVE_TYPEOF)
#define isless(x, y) (!isunordered(x, y) && (x) < (y))
#else /* __NO_XBLOCK || !__COMPILER_HAVE_TYPEOF */
#define isless(x, y) __XBLOCK({ __typeof__(x) __isl_x = (x); __typeof__(y) __isl_y = (y); __XRETURN !isunordered(__isl_x, __isl_y) && __isl_x < __isl_y; })
#endif /* !__NO_XBLOCK && __COMPILER_HAVE_TYPEOF */
#endif /* !isless */

#ifndef islessequal
#if defined(__NO_XBLOCK) || !defined(__COMPILER_HAVE_TYPEOF)
#define islessequal(x, y) (!isunordered(x, y) && (x) <= (y))
#else /* __NO_XBLOCK || !__COMPILER_HAVE_TYPEOF */
#define islessequal(x, y) __XBLOCK({ __typeof__(x) __isle_x = (x); __typeof__(y) __isle_y = (y); __XRETURN !isunordered(__isle_x, __isle_y) && __isle_x <= __isle_y; })
#endif /* !__NO_XBLOCK && __COMPILER_HAVE_TYPEOF */
#endif /* !islessequal */

#ifndef islessgreater
#if defined(__NO_XBLOCK) || !defined(__COMPILER_HAVE_TYPEOF)
#define islessgreater(x, y) (!isunordered(x, y) && ((x) < (y) || (y) < (x)))
#else /* __NO_XBLOCK || !__COMPILER_HAVE_TYPEOF */
#define islessgreater(x, y) __XBLOCK({ __typeof__(x) __islg_x = (x); __typeof__(y) __islg_y = (y); __XRETURN !isunordered(__islg_x, __islg_y) && (__islg_x < __islg_y || __y < __x); })
#endif /* !__NO_XBLOCK && __COMPILER_HAVE_TYPEOF */
#endif /* !islessgreater */
#endif /* __USE_ISOC99 */




#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP11_MATH_H_PROTO_FP)
/* Libstdc++ headers need us to define these as functions when also
 * defining `__CORRECT_ISO_CPP11_MATH_H_PROTO_FP', which we need to
 * do in order to get it to stop re-declaring other functions  such
 * as `acosh'... *ugh* */
__NAMESPACE_STD_BEGIN
extern "C++" {
#ifdef fpclassify
#ifndef __std_fpclassify_defined
#define __std_fpclassify_defined
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST int __NOTHROW(fpclassify)(float __x) { return fpclassify(__x); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST int __NOTHROW(fpclassify)(double __x) { return fpclassify(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST int __NOTHROW(fpclassify)(__LONGDOUBLE __x) { return fpclassify(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_fpclassify_defined */
#undef fpclassify
#endif /* fpclassify */
#ifdef signbit
#ifndef __std_signbit_defined
#define __std_signbit_defined
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(signbit)(float __x) { return signbit(__x); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(signbit)(double __x) { return signbit(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(signbit)(__LONGDOUBLE __x) { return signbit(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_signbit_defined */
#undef signbit
#endif /* signbit */
#ifdef isnormal
#ifndef __std_isnormal_defined
#define __std_isnormal_defined
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isnormal)(float __x) { return isnormal(__x); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isnormal)(double __x) { return isnormal(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isnormal)(__LONGDOUBLE __x) { return isnormal(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isnormal_defined */
#undef isnormal
#endif /* isnormal */
#ifdef isfinite
#ifndef __std_isfinite_defined
#define __std_isfinite_defined
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isfinite)(float __x) { return isfinite(__x); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isfinite)(double __x) { return isfinite(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isfinite)(__LONGDOUBLE __x) { return isfinite(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isfinite_defined */
#undef isfinite
#endif /* isfinite */
#ifdef isnan
#ifndef __std_isnan_defined
#define __std_isnan_defined
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isnan)(float __x) { return isnan(__x); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isnan)(double __x) { return isnan(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isnan)(__LONGDOUBLE __x) { return isnan(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isnan_defined */
#undef isnan
#endif /* isnan */
#ifdef isinf
#ifndef __std_isinf_defined
#define __std_isinf_defined
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isinf)(float __x) { return isinf(__x); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isinf)(double __x) { return isinf(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isinf)(__LONGDOUBLE __x) { return isinf(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isinf_defined */
#undef isinf
#endif /* isinf */
#ifdef isunordered
#ifndef __std_isunordered_defined
#define __std_isunordered_defined
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isunordered)(float __x, float __y) { return isunordered(__x, __y); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isunordered)(double __x, double __y) { return isunordered(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isunordered)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return isunordered(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isunordered_defined */
#undef isunordered
#endif /* isunordered */
#ifdef isgreater
#ifndef __std_isgreater_defined
#define __std_isgreater_defined
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isgreater)(float __x, float __y) { return isgreater(__x, __y); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isgreater)(double __x, double __y) { return isgreater(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isgreater)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return isgreater(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isgreater_defined */
#undef isgreater
#endif /* isgreater */
#ifdef isgreaterequal
#ifndef __std_isgreaterequal_defined
#define __std_isgreaterequal_defined
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isgreaterequal)(float __x, float __y) { return isgreaterequal(__x, __y); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isgreaterequal)(double __x, double __y) { return isgreaterequal(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isgreaterequal)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return isgreaterequal(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isgreaterequal_defined */
#undef isgreaterequal
#endif /* isgreaterequal */
#ifdef isless
#ifndef __std_isless_defined
#define __std_isless_defined
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isless)(float __x, float __y) { return isless(__x, __y); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isless)(double __x, double __y) { return isless(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(isless)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return isless(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isless_defined */
#undef isless
#endif /* isless */
#ifdef islessequal
#ifndef __std_islessequal_defined
#define __std_islessequal_defined
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(islessequal)(float __x, float __y) { return islessequal(__x, __y); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(islessequal)(double __x, double __y) { return islessequal(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(islessequal)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return islessequal(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_islessequal_defined */
#undef islessequal
#endif /* islessequal */
#ifdef islessgreater
#ifndef __std_islessgreater_defined
#define __std_islessgreater_defined
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(islessgreater)(float __x, float __y) { return islessgreater(__x, __y); }
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(islessgreater)(double __x, double __y) { return islessgreater(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST __BOOL __NOTHROW(islessgreater)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return islessgreater(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_islessgreater_defined */
#undef islessgreater
#endif /* islessgreater */
} /* extern "C++" */
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
#ifdef __std_fpclassify_defined
__NAMESPACE_STD_USING(fpclassify)
#endif /* __std_fpclassify_defined */
#ifdef __std_signbit_defined
__NAMESPACE_STD_USING(signbit)
#endif /* __std_signbit_defined */
#ifdef __std_isnormal_defined
__NAMESPACE_STD_USING(isnormal)
#endif /* __std_isnormal_defined */
#ifdef __std_isfinite_defined
__NAMESPACE_STD_USING(isfinite)
#endif /* __std_isfinite_defined */
#ifdef __std_isnan_defined
__NAMESPACE_STD_USING(isnan)
#endif /* __std_isnan_defined */
#ifdef __std_isinf_defined
__NAMESPACE_STD_USING(isinf)
#endif /* __std_isinf_defined */
#ifdef __std_isunordered_defined
__NAMESPACE_STD_USING(isunordered)
#endif /* __std_isunordered_defined */
#ifdef __std_isgreater_defined
__NAMESPACE_STD_USING(isgreater)
#endif /* __std_isgreater_defined */
#ifdef __std_isgreaterequal_defined
__NAMESPACE_STD_USING(isgreaterequal)
#endif /* __std_isgreaterequal_defined */
#ifdef __std_isless_defined
__NAMESPACE_STD_USING(isless)
#endif /* __std_isless_defined */
#ifdef __std_islessequal_defined
__NAMESPACE_STD_USING(islessequal)
#endif /* __std_islessequal_defined */
#ifdef __std_islessgreater_defined
__NAMESPACE_STD_USING(islessgreater)
#endif /* __std_islessgreater_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __cplusplus && __CORRECT_ISO_CPP11_MATH_H_PROTO_FP */

/* Bit values for `math_errhandling'. */
#define MATH_ERRNO     1 /* Errno is set by math functions. */
#define MATH_ERREXCEPT 2 /* Exceptions are raised by math functions. */

/* By   default,   all  functions   support   both  errno   and   exception  handling.
 * In gcc's fast math mode and if inline functions are defined this might not be true. */
#ifndef __FAST_MATH__
#define math_errhandling (MATH_ERRNO | MATH_ERREXCEPT)
#endif /* !__FAST_MATH__ */
#endif /* __USE_ISOC99 */


#ifdef __USE_GNU
#ifndef issignaling
#define issignaling(x) __FPFUNC(x, __issignalingf, __issignaling, __issignalingl)
#endif /* !issignaling */
#endif /* __USE_GNU */


#ifdef __USE_MISC
#if (defined(___IEEE_) || defined(___SVID_) ||   \
     defined(___XOPEN_) || defined(___POSIX_) || \
     defined(___ISOC_))
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("_IEEE_")
#pragma push_macro("_SVID_")
#pragma push_macro("_XOPEN_")
#pragma push_macro("_POSIX_")
#pragma push_macro("_ISOC_")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef _IEEE_
#undef _SVID_
#undef _XOPEN_
#undef _POSIX_
#undef _ISOC_
/* Possible behavior for math standard error handling. */
typedef enum {
#ifdef ___IEEE_
	_IEEE_ = ___IEEE_,   /* s.a. IEEE 754/IEEE 854. */
#endif /* ___IEEE_ */
#ifdef ___SVID_
	_SVID_ = ___SVID_,   /* s.a. SysV, release 4. */
#endif /* ___SVID_ */
#ifdef ___XOPEN_
	_XOPEN_ = ___XOPEN_, /* aka. Unix98. */
#endif /* ___XOPEN_ */
#ifdef ___POSIX_
	_POSIX_ = ___POSIX_, /* ... */
#endif /* ___POSIX_ */
#ifdef ___ISOC_
	_ISOC_ = ___ISOC_    /* ISO C99. */
#endif /* ___ISOC_ */
} _LIB_VERSION_TYPE;
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("_ISOC_")
#pragma pop_macro("_POSIX_")
#pragma pop_macro("_XOPEN_")
#pragma pop_macro("_SVID_")
#pragma pop_macro("_IEEE_")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

/* One of `_LIB_VERSION_TYPE': The current math error behavior */
#ifdef __CRT_HAVE__LIB_VERSION
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("_LIB_VERSION")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef _LIB_VERSION
__LIBC _LIB_VERSION_TYPE _LIB_VERSION;
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("_LIB_VERSION")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __CRT_HAVE__LIB_VERSION */
#endif /* ... */


/* With SVID error handling, `matherr(3)' gets called with struct on error */
#ifdef __cplusplus
struct __exception
#else /* __cplusplus */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("exception")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef exception
struct exception
#endif /* !__cplusplus */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("type")
#pragma push_macro("name")
#pragma push_macro("arg1")
#pragma push_macro("arg2")
#pragma push_macro("retval")
#pragma push_macro("err")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef type
#undef name
#undef arg1
#undef arg2
#undef retval
#undef err
{
	int    type;
	char  *name;
	double arg1;
	double arg2;
	double retval;
	int    err;
#ifdef __CRT_DOS
	int    __pad;
#endif /* __CRT_DOS */
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("err")
#pragma pop_macro("retval")
#pragma pop_macro("arg2")
#pragma pop_macro("arg1")
#pragma pop_macro("name")
#pragma pop_macro("type")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#ifdef __CRT_HAVE_matherr
#ifdef __cplusplus
__CDECLARE(,int,__NOTHROW,matherr,(struct __exception *__exc),(__exc))
#else /* __cplusplus */
__CDECLARE(,int,__NOTHROW,matherr,(struct exception *__exc),(__exc))
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("exception")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* !__cplusplus */
#endif /* __CRT_HAVE_matherr */

#define X_TLOSS 1.41484755040568800000e+16

/* Values for `exception::type' */
#ifdef __MATH_EXCEPT_DOMAIN
#define DOMAIN __MATH_EXCEPT_DOMAIN /* ... */
#endif /* __MATH_EXCEPT_DOMAIN */
#ifdef __MATH_EXCEPT_SING
#define SING __MATH_EXCEPT_SING /* ... */
#endif /* __MATH_EXCEPT_SING */
#ifdef __MATH_EXCEPT_OVERFLOW
#define OVERFLOW __MATH_EXCEPT_OVERFLOW /* ... */
#endif /* __MATH_EXCEPT_OVERFLOW */
#ifdef __MATH_EXCEPT_UNDERFLOW
#define UNDERFLOW __MATH_EXCEPT_UNDERFLOW /* ... */
#endif /* __MATH_EXCEPT_UNDERFLOW */
#ifdef __MATH_EXCEPT_TLOSS
#define TLOSS __MATH_EXCEPT_TLOSS /* ... */
#endif /* __MATH_EXCEPT_TLOSS */
#ifdef __MATH_EXCEPT_PLOSS
#define PLOSS __MATH_EXCEPT_PLOSS /* ... */
#endif /* __MATH_EXCEPT_PLOSS */

#define HUGE 3.40282347e+38F /* SVID-specific constant */
#else /* __USE_MISC */
#ifdef __USE_XOPEN
#define MAXFLOAT 3.40282347e+38F /* X/Open-specific constant */
#endif /* __USE_XOPEN */
#endif /* !__USE_MISC */


__SYSDECL_END
#endif /* __CC__ */

#ifdef __USE_DOS
#if !defined(_INFCODE) && defined(__FP_INFINITE)
#define _INFCODE __FP_INFINITE
#endif /* !_INFCODE && __FP_INFINITE */
#if !defined(_NANCODE) && defined(__FP_NAN)
#define _NANCODE __FP_NAN
#endif /* !_NANCODE && __FP_NAN */
#if !defined(_FINITE) && defined(__FP_NORMAL)
#define _FINITE  __FP_NORMAL
#endif /* !_FINITE && __FP_NORMAL */
#if !defined(_DENORM) && defined(__FP_SUBNORMAL)
#define _DENORM  __FP_SUBNORMAL
#endif /* !_DENORM && __FP_SUBNORMAL */

#ifdef __CC__
__SYSDECL_BEGIN
#ifdef __CRT_HAVE__dtest
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),short,__NOTHROW_NCX,_dtest,(double __KOS_FIXED_CONST *__px),(__px))
#else /* __CRT_HAVE__dtest */
#include <libc/local/math/_dtest.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_dtest, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) short __NOTHROW_NCX(__LIBCCALL _dtest)(double __KOS_FIXED_CONST *__px) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_dtest))(__px); })
#endif /* !__CRT_HAVE__dtest */
#ifdef __CRT_HAVE__fdtest
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),short,__NOTHROW_NCX,_fdtest,(float __KOS_FIXED_CONST *__px),(__px))
#else /* __CRT_HAVE__fdtest */
#include <libc/local/math/_fdtest.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_fdtest, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) short __NOTHROW_NCX(__LIBCCALL _fdtest)(float __KOS_FIXED_CONST *__px) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fdtest))(__px); })
#endif /* !__CRT_HAVE__fdtest */
#ifdef __CRT_HAVE__ldtest
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),short,__NOTHROW_NCX,_ldtest,(__LONGDOUBLE __KOS_FIXED_CONST *__px),(__px))
#else /* __CRT_HAVE__ldtest */
#include <libc/local/math/_ldtest.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ldtest, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) short __NOTHROW_NCX(__LIBCCALL _ldtest)(__LONGDOUBLE __KOS_FIXED_CONST *__px) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ldtest))(__px); })
#endif /* !__CRT_HAVE__ldtest */
__SYSDECL_END
#endif /* __CC__ */
#endif /* __USE_DOS */

#endif /* !__NO_FPU */
#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CMATH
#undef _MATH_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CMATH */
#endif /* !_MATH_H */
